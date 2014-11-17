// -*- C++ -*-
//
// Package:    uGMTInputProducerFromGen
// Class:      uGMTInputProducerFromGen
// 
/**\class uGMTInputProducerFromGen uGMTInputProducerFromGen.cc L1Trigger/L1TGlobalMuon/plugins/uGMTInputProducerFromGen.cc

 Description: takes generated muons and fills them in the expected collections for the uGMT

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Joschka Philip Lingemann,40 3-B01,+41227671598,
//         Created:  Thu Oct  3 10:12:30 CEST 2013
// $Id$
//
//


// system include files
#include <memory>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/L1TMuon/interface/L1TRegionalMuonCandidateFwd.h"
#include "DataFormats/L1TMuon/interface/L1TRegionalMuonCandidate.h"
#include "DataFormats/L1TMuon/interface/L1TGMTInputCaloSumFwd.h"
#include "DataFormats/L1TMuon/interface/L1TGMTInputCaloSum.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//
// class declaration
//
namespace l1t {
class uGMTInputProducerFromGen : public edm::EDProducer {
   public:
      explicit uGMTInputProducerFromGen(const edm::ParameterSet&);
      ~uGMTInputProducerFromGen();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      int linkNo(const float phi, const int type, const int offset) const;
      
      // ----------member data ---------------------------
      edm::EDGetTokenT <reco::GenParticleCollection> genParticlesToken;
      int m_currEvt;
      const float m_phiToLink = 1.90985931710274404f;
      const static int m_maxMuons = 108;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
uGMTInputProducerFromGen::uGMTInputProducerFromGen(const edm::ParameterSet& iConfig) : 
  m_currEvt(0)
{
  //register your inputs:
  genParticlesToken = consumes <reco::GenParticleCollection> (std::string("genParticles"));
  //register your products
  produces<L1TRegionalMuonCandidateCollection>("BarrelTFMuons");
  produces<L1TRegionalMuonCandidateCollection>("OverlapTFMuons");
  produces<L1TRegionalMuonCandidateCollection>("ForwardTFMuons");
  produces<L1TGMTInputCaloSumCollection>("TriggerTowerSums");
}


uGMTInputProducerFromGen::~uGMTInputProducerFromGen()
{
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//





// ------------ method called to produce the data  ------------
void
uGMTInputProducerFromGen::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  std::auto_ptr<l1t::L1TRegionalMuonCandidateCollection> barrelMuons (new l1t::L1TRegionalMuonCandidateCollection());
  std::auto_ptr<l1t::L1TRegionalMuonCandidateCollection> overlapMuons (new l1t::L1TRegionalMuonCandidateCollection());
  std::auto_ptr<l1t::L1TRegionalMuonCandidateCollection> endcapMuons (new l1t::L1TRegionalMuonCandidateCollection());
  std::auto_ptr<l1t::L1TGMTInputCaloSumCollection> towerSums (new L1TGMTInputCaloSumCollection());


  std::vector<int> muIndices;
  edm::Handle<reco::GenParticleCollection> genParticles;
  // Make sure that you can get genParticles
  if (iEvent.getByToken(genParticlesToken, genParticles)) { 
    int cntr = 0;
    for (auto it = genParticles->cbegin(); it != genParticles->cend(); ++it) {
      const reco::Candidate& mcParticle = *it;
      if( abs(mcParticle.pdgId()) == 13 && mcParticle.status() == 1 )  muIndices.push_back(cntr);
      cntr++;
    }
  }
  else {
    LogTrace("GlobalMuon") << " GenParticleCollection not found." << std::endl;
  }

  l1t::L1TRegionalMuonCandidate mu;
  l1t::L1TGMTInputCaloSum tSum;
  const float phiToInt = 163.4521265553765f; 
  const float etaToInt = 100.0f;
  const int maxPt = (1 << 9)-1;
  int muCntr = 0;

  for (auto it = muIndices.begin(); it != muIndices.end(); ++it) {
    // don't really care which muons are taken... 
    // guess there ain't 108 generated anyways
    if (muCntr == m_maxMuons) break;
    int gen_idx = *it;
    const reco::Candidate& mcMuon = genParticles->at(gen_idx);
    double eta = mcMuon.eta();
    if (fabs(eta) > 2.4) continue; // out of acceptance
    int hwPt = int(mcMuon.pt() * 2);
    hwPt = (hwPt < maxPt ? hwPt : maxPt);
    int hwEta = int(eta * etaToInt);
    int hwPhi = int(mcMuon.phi() * phiToInt);
    int hwQual = 8;
    int hwCharge = (mcMuon.charge() > 0) ? 0 : 1;
    int hwChargeValid = 1;
    
    mu.setHwPt(hwPt);
    mu.setHwPhi(hwPhi);

    int type = 0;
    int offset = 12;
    if (fabs(eta) > 0.8) {
      type = 1;
      if (fabs(eta) < 1.2) {
        offset = (eta > 0 ? 6 : 24);
      } else {
        offset = (eta > 0 ? 0 : 30);
      }
    } 
    int link = linkNo(mcMuon.phi(), type, offset);
    mu.setLink(link);

    mu.setHwEta(hwEta);
    mu.setHwSign(hwCharge);
    mu.setHwSignValid(hwChargeValid);
    mu.setHwQual(hwQual);

    if (fabs(eta) < 0.8 && barrelMuons->size() < 36) {
      barrelMuons->push_back(mu);
      muCntr++;
    } else if (fabs(eta) < 1.2  && overlapMuons->size() < 36) {
      overlapMuons->push_back(mu);
      muCntr++;
    } else if (endcapMuons->size() < 36) {
      endcapMuons->push_back(mu);
      muCntr++;
    }
  }

  while (towerSums->size() < 1008) {
    // from where could I take the tower energies?
    towerSums->emplace_back();
  }
  iEvent.put(barrelMuons, "BarrelTFMuons");
  iEvent.put(overlapMuons, "OverlapTFMuons");
  iEvent.put(endcapMuons, "ForwardTFMuons");
  iEvent.put(towerSums, "TriggerTowerSums");
  m_currEvt++;
 
}

int uGMTInputProducerFromGen::linkNo(const float phi, const int type, const int offset) const {
  if (type == 0) {
    return int(phi*m_phiToLink)+offset;
  }
  return int(phi*m_phiToLink/2.)+offset;
}

// ------------ method called once each job just before starting event loop  ------------
void 
uGMTInputProducerFromGen::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
uGMTInputProducerFromGen::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
uGMTInputProducerFromGen::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
uGMTInputProducerFromGen::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
uGMTInputProducerFromGen::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
uGMTInputProducerFromGen::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
uGMTInputProducerFromGen::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
}
//define this as a plug-in
DEFINE_FWK_MODULE(l1t::uGMTInputProducerFromGen);
