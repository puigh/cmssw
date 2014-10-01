// -*- C++ -*-
//
// Package:    MicroGMTEmulator
// Class:      MicroGMTEmulator
// 
/**\class MicroGMTEmulator MicroGMTEmulator.cc L1Trigger/L1TGlobalMuon/src/MicroGMTEmulator.cc

 Description: Takes txt-file input and produces barrel- / overlap- / forward TF muons 

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Joschka Philip Lingemann,40 3-B01,+41227671598,
//         Created:  Thu Oct  3 16:31:34 CEST 2013
// $Id$
//
//


// system include files
#include <memory>
#include <fstream>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "L1Trigger/L1TGlobalMuon/interface/MicroGMTRankPtQualLUT.h"
#include "L1Trigger/L1TGlobalMuon/interface/MicroGMTIsolationUnit.h"
#include "L1Trigger/L1TGlobalMuon/interface/MicroGMTCancelOutUnit.h"


//
// class declaration
//
namespace l1t {
  class MicroGMTEmulator : public edm::EDProducer {
     public:
        explicit MicroGMTEmulator(const edm::ParameterSet&);
        ~MicroGMTEmulator();

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

     private:
        virtual void beginJob() ;
        virtual void produce(edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;
        
        virtual void beginRun(edm::Run&, edm::EventSetup const&);
        virtual void endRun(edm::Run&, edm::EventSetup const&);
        virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
        virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

        void rankMuons(OutputCollection& results, InputCollection const& muons) const;
        void rankMuons(OutputCollection& results, OutputCollection const& muons) const;
        void sortMuons(OutputCollection&, unsigned, muon_t) const;
        void calculateRank(InputCollection const& muons, std::vector<unsigned>& ranks, ResultMatrix& resMat) const;
        void calculateRankSplit(InputCollection const& muons, std::vector<unsigned>& ranks, ResultMatrix& resMat) const;
        void calculateRank(OutputCollection& muons) const;
        void matrixToStream(ResultMatrix& mat, std::vector<unsigned>& ranks, bool symmetric, std::stringstream&) const;
        // ----------member data ---------------------------
        edm::InputTag m_barrelTfInputTag;
        edm::InputTag m_overlapTfInputTag;
        edm::InputTag m_forwardTfInputTag;
        edm::InputTag m_trigTowerTag;
        MicroGMTRankPtQualLUT m_rankPtQualityLUT;
        MicroGMTIsolationUnit m_isolationUnit;
        MicroGMTCancelOutUnit m_cancelOutUnit;

  };
}
//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
l1t::MicroGMTEmulator::MicroGMTEmulator(const edm::ParameterSet& iConfig) : m_rankPtQualityLUT(iConfig), m_isolationUnit(iConfig), m_cancelOutUnit(iConfig)
{
  // edm::InputTag barrelTfInputTag = iConfig.getParameter<edm::InputTag>("barrelTFInput");
  // edm::InputTag overlapTfInputTag = iConfig.getParameter<edm::InputTag>("overlapTFInput");
  // edm::InputTag forwardTfInputTag = iConfig.getParameter<edm::InputTag>("forwardTFInput");

  // m_barrelTfInputToken = consumes<InputCollection>(barrelTfInputTag);
  // m_overlapTfInputToken = consumes<InputCollection>(overlapTfInputTag);
  // m_forwardTfInputToken = consumes<InputCollection>(forwardTfInputTag);
   //register your products
  produces<GMTMuonCandidateCollection>();
  produces<GMTMuonCandidateCollection>("intermediateMuons");

  m_barrelTfInputTag = iConfig.getParameter<edm::InputTag>("barrelTFInput");
  m_overlapTfInputTag = iConfig.getParameter<edm::InputTag>("overlapTFInput");
  m_forwardTfInputTag = iConfig.getParameter<edm::InputTag>("forwardTFInput");
  m_trigTowerTag = iConfig.getParameter<edm::InputTag>("triggerTowerInput");

  MicroGMTConfiguration::initialize(iConfig);

  //m_rankPtQualityLUT.initialize();
  
  std::ofstream fstream;
  fstream.open("test.lut");
  m_rankPtQualityLUT.save(fstream);
  fstream.close();


  // test:
  int pt = 10;
  int q = 5;
  int hashed = m_rankPtQualityLUT.hashInput(pt, q);

  int ptTest, qTest;
  m_rankPtQualityLUT.unHashInput(hashed, ptTest, qTest);

  int resultHashed = m_rankPtQualityLUT.lookupPacked(hashed);
  int resultUnHashed = m_rankPtQualityLUT.lookup(pt, q);

  std::cout << " ------------------------ MINI TEST ------------------------------ " << std::endl;
  std::cout << " - result(pt, q) = result(" << pt << ", " << q << ") = "  << resultUnHashed << std::endl;
  std::cout << " - result(ptq) = result(" << hashed << ") = "  << resultHashed << std::endl;
  std::cout << " - unHash(ptq) = pt: " << ptTest << " q: " << qTest << std::endl;
  std::cout << " ----------------------------------------------------------------- " << std::endl;

}


l1t::MicroGMTEmulator::~MicroGMTEmulator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//



// ------------ method called to produce the data  ------------
void
l1t::MicroGMTEmulator::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  std::auto_ptr<GMTMuonCandidateCollection> outMuons (new GMTMuonCandidateCollection());
  std::auto_ptr<GMTMuonCandidateCollection> intermediateMuons (new GMTMuonCandidateCollection());

  Handle<InputCollection> barrelMuons;
  Handle<InputCollection> forwardMuons;
  Handle<InputCollection> overlapMuons;
  Handle<GMTInputCaloSumCollection> trigTowers;

  // iEvent.getByToken(m_barrelTfInputToken, barrelMuons);
  iEvent.getByLabel(m_barrelTfInputTag, barrelMuons);
  iEvent.getByLabel(m_forwardTfInputTag, forwardMuons);
  iEvent.getByLabel(m_overlapTfInputTag, overlapMuons);
  iEvent.getByLabel(m_trigTowerTag, trigTowers);
  

  m_isolationUnit.calculate5by1Sums(*trigTowers);
  OutputCollection internalMuons;

  m_isolationUnit.extrapolateMuons(internalMuons, *barrelMuons);
  m_isolationUnit.extrapolateMuons(internalMuons, *forwardMuons);
  m_isolationUnit.extrapolateMuons(internalMuons, *overlapMuons);
  std::cout << "total in: " << internalMuons.size() << std::endl;
  //m_cancelOutUnit.setCancelOutBits(internalMuons);

  calculateRank(internalMuons);

  // // rank muons only does push_back
  // rankMuons(sort0Candidates, *barrelMuons);
  // rankMuons(sort0Candidates, *overlapMuons);
  // rankMuons(sort0Candidates, *forwardMuons);

  // FIXME cancellation should happen before this

  sortMuons(internalMuons, 8, muon_t::BARRELTF);
  sortMuons(internalMuons, 4, muon_t::OVERLAPTF_POS);
  sortMuons(internalMuons, 4, muon_t::OVERLAPTF_NEG);
  sortMuons(internalMuons, 4, muon_t::FORWARDTF_POS);
  sortMuons(internalMuons, 4, muon_t::FORWARDTF_NEG);

  for (auto mu = internalMuons.begin(); mu != internalMuons.end(); ++mu) {
    intermediateMuons->push_back(*mu);
  }
  std::cout << "first sort: " << internalMuons.size() << std::endl;
  // OutputCollection sort1Candidates;
  // rank muons only does push_back
  sortMuons(internalMuons, 8, muon_t::ALL);

  std::cout << "second sort: " << internalMuons.size() << std::endl;

  m_isolationUnit.isolate(internalMuons);

  // sort out-muons by n(wins)...
    for (auto mu = internalMuons.begin(); mu != internalMuons.end(); ++mu) {
        outMuons->push_back(*mu);
    }
  

  iEvent.put(outMuons);
  iEvent.put(intermediateMuons, "intermediateMuons");
}

void
l1t::MicroGMTEmulator::matrixToStream(ResultMatrix& mat, std::vector<unsigned>& ranks, bool symmetric, std::stringstream& out) const
{
  if (mat.size() == 0) return;
  out << "    ";
  for (size_t j = 0; j < mat[0].size(); ++j) {
    if (j < 10) out << "  ";
    else out << " ";
    out << j;
  }
  out  << " SUM" << std::endl;
  for (size_t i = 0; i < mat.size(); ++i) {
    if (i < 10) {
      out << i << "  :";
    } else {
      out << i << " :";
    }
    if (symmetric) {
      for (size_t j = 0; j < i+1; ++j) out << "  -";
      for (size_t j = i+1; j < mat[i].size(); ++j) {
        out << "  " << mat[i][j];
      }
    }
    else {
      for (size_t j = 0; j < mat[i].size(); ++j) {
        out << "  " << mat[i][j];
      }
    }
    out << " " << ranks[i];
    out << std::endl;
  }
  out << std::endl;
}

void
l1t::MicroGMTEmulator::rankMuons(OutputCollection& results, InputCollection const& muons) const
{
  if (muons.size() == 0) return;
  std::vector<bool> line(muons.size(), false);
  std::vector<std::vector<bool> > resultMat(muons.size(), line);

  std::vector<unsigned> winSums(muons.size(), 0);

  unsigned offset = 0;
  unsigned maxRank = 0;
  if (muons[0].type() == 0) {
    calculateRank(muons, winSums, resultMat);
    offset = 9;
    maxRank = muons.size();
  }
  else {
    calculateRankSplit(muons, winSums, resultMat);
    offset = 5;
    maxRank = muons.size()/2;
  }

  std::stringstream resMStream;
  if (muons[0].type() == 0) resMStream << "-------------------------- BARREL RESULTS --------------------------" << std::endl;
  if (muons[0].type() == 1) resMStream << "-------------------------- OVERLAP RESULTS -------------------------" << std::endl;
  if (muons[0].type() == 2) resMStream << "-------------------------- FORWARD RESULTS -------------------------" << std::endl;
  matrixToStream(resultMat, winSums, true, resMStream);
  std::cout << resMStream.str() << std::endl;

  for (unsigned i = 0; i < muons.size(); ++i) {
    for (unsigned j = 1; j < offset; ++j) {
      if (winSums[i] == maxRank-j) {
        results.push_back(GMTMuonCandidate(muons.at(i)));
        results.back().setRank(m_rankPtQualityLUT.lookup(muons[i].ptBits(), muons[i].qualityBits()));
      }
    }
  }
}

void 
l1t::MicroGMTEmulator::sortMuons(OutputCollection& muons, unsigned nSurvivors, muon_t type) const {
  OutputCollection::iterator mu1;
  OutputCollection::iterator mu2;

  for (mu1 = muons.begin(); mu1 != muons.end(); ++mu1) {
    mu1->setInternalSort(0);
  }
  
  for (mu1 = muons.begin(); mu1 != muons.end(); ++mu1) {
    if (mu1->type() != (int)type && type != muon_t::ALL) continue;
    mu2 = mu1;
    mu2++;
    for ( ; mu2 != muons.end(); ++mu2) {
      if (mu2->type() != (int)type && type != muon_t::ALL) continue;
      if (mu1->rank() >= mu2->rank() && mu1->cancelBit() != 1) {
        mu1->setInternalSort(mu1->internalSort()+1);
      } else {
        mu2->setInternalSort(mu2->internalSort()+1);
      }
    }
  }

  unsigned nMuonsBefore = 18;
  if (type == BARRELTF) nMuonsBefore = 36;
  if (type == ALL) nMuonsBefore = 24;
  mu1 = muons.begin();
  while (mu1 != muons.end()) {
    if (mu1->internalSort() < (int)(nMuonsBefore-nSurvivors) && (mu1->type() == (int)type || type == muon_t::ALL) ) {
      muons.erase(mu1);
    }
    ++mu1;
  }
}

void
l1t::MicroGMTEmulator::rankMuons(OutputCollection& results, OutputCollection const& muons) const
{
  if (muons.size() == 0) return;
  std::vector<bool> line(muons.size(), false);
  std::vector<std::vector<bool> > resultMat(muons.size(), line);

  std::vector<unsigned> winSums(muons.size(), 0);

  // unsigned offset = 0;
  // unsigned maxRank = 0;
  // for (size_t mu1 = 0; mu1 < muons.size(); ++mu1) {
  //   for (size_t mu2 = mu1+1; mu2 < muons.size(); ++mu2) {
  //     if (muons[mu1].rank() >= muons[mu2].rank()) {
  //       resultMat[mu1][mu2] = true;
  //       winSums[mu1] += 1;
  //     } else {
  //       winSums[mu2] += 1;
  //     }
  //   }
  // }

  std::stringstream resMStream;
  resMStream << "-------------------------- STAGE1 RESULTS --------------------------" << std::endl;

  matrixToStream(resultMat, winSums, true, resMStream);
  std::cout << resMStream.str() << std::endl;

  for (unsigned i = 0; i < muons.size(); ++i) {
    for (unsigned j = 1; j < 9; ++j) {
      if (winSums[i] == muons.size()-j) { // this actually sorts!
        // results.push_back(GMTMuonCandidate(muons.at(i)));
        continue;
      }
    }
  }

}

void 
l1t::MicroGMTEmulator::calculateRank(OutputCollection& muons) const 
{
  OutputCollection::iterator mu1;
  for (mu1 = muons.begin(); mu1 != muons.end(); ++mu1) {
    int rank = m_rankPtQualityLUT.lookup(mu1->ptBits(), mu1->qualityBits());
    mu1->setRank(rank);
  }
}

void 
l1t::MicroGMTEmulator::calculateRank(InputCollection const& muons, std::vector<unsigned>& rank, ResultMatrix& resMat) const 
{
  for (size_t mu1 = 0; mu1 < muons.size(); ++mu1) {
    int rank1 = m_rankPtQualityLUT.lookup(muons[mu1].ptBits(), muons[mu1].qualityBits());

    for (size_t mu2 = mu1+1; mu2 < muons.size(); ++mu2) {
      int rank2 = m_rankPtQualityLUT.lookup(muons[mu2].ptBits(), muons[mu2].qualityBits());
      if (rank1 >= rank2) {
        resMat[mu1][mu2] = true;
        rank[mu1] += 1;
      } else {
        rank[mu2] += 1;
      }
    }
  }
}

void 
l1t::MicroGMTEmulator::calculateRankSplit(InputCollection const& muons, std::vector<unsigned>& rank, ResultMatrix& resMat) const 
{
  for (size_t mu1 = 0; mu1 < muons.size()/2; ++mu1) {
    int rank1 = m_rankPtQualityLUT.lookup(muons[mu1].ptBits(), muons[mu1].qualityBits());

    for (size_t mu2 = mu1+1; mu2 < muons.size()/2; ++mu2) {
      int rank2 = m_rankPtQualityLUT.lookup(muons[mu2].ptBits(), muons[mu2].qualityBits());
      if (rank1 >= rank2) {
        resMat[mu1][mu2] = true;
        rank[mu1] += 1;
      } else {
        rank[mu2] += 1;
      }
    }
  }

  for (size_t mu1 = muons.size()/2; mu1 < muons.size(); ++mu1) {
    int rank1 = m_rankPtQualityLUT.lookup(muons[mu1].ptBits(), muons[mu1].qualityBits());

    for (size_t mu2 = mu1+1; mu2 < muons.size(); ++mu2) {
      int rank2 = m_rankPtQualityLUT.lookup(muons[mu2].ptBits(), muons[mu2].qualityBits());
      if (rank1 >= rank2) {
        resMat[mu1][mu2] = true;
        rank[mu1] += 1;
      } else {
        rank[mu2] += 1;
      }
    }
  }
}
// ------------ method called once each job just before starting event loop  ------------
void 
l1t::MicroGMTEmulator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
l1t::MicroGMTEmulator::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
l1t::MicroGMTEmulator::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
l1t::MicroGMTEmulator::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
l1t::MicroGMTEmulator::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
l1t::MicroGMTEmulator::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
l1t::MicroGMTEmulator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MicroGMTEmulator);
