#include "../interface/MicroGMTIsolationUnit.h"

l1t::MicroGMTIsolationUnit::MicroGMTIsolationUnit (const edm::ParameterSet& iConfig) :
  m_BEtaExtrapolation(iConfig, "BEtaExtrapolationLUTSettings", 0), m_BPhiExtrapolation(iConfig, "BPhiExtrapolationLUTSettings", 1), m_OEtaExtrapolation(iConfig, "OEtaExtrapolationLUTSettings", 0),
  m_OPhiExtrapolation(iConfig, "OPhiExtrapolationLUTSettings", 1), m_FEtaExtrapolation(iConfig, "FEtaExtrapolationLUTSettings", 0), m_FPhiExtrapolation(iConfig, "FPhiExtrapolationLUTSettings", 1),
  m_IdxSelMemEta(iConfig, "IdxSelMemEtaLUTSettings", 0), m_IdxSelMemPhi(iConfig, "IdxSelMemPhiLUTSettings", 1), m_RelIsoCheckMem(iConfig, "RelIsoCheckMemLUTSettings"),  
  m_AbsIsoCheckMem(iConfig, "AbsIsoCheckMemLUTSettings"), m_initialSums(false) 
{
  m_etaExtrapolationLUTs[BARRELTF] = &m_BEtaExtrapolation;
  m_phiExtrapolationLUTs[BARRELTF] = &m_BPhiExtrapolation;
  m_etaExtrapolationLUTs[OVERLAPTF_POS] = &m_OEtaExtrapolation;
  m_etaExtrapolationLUTs[OVERLAPTF_NEG] = &m_OEtaExtrapolation;
  m_phiExtrapolationLUTs[OVERLAPTF_POS] = &m_OPhiExtrapolation;
  m_phiExtrapolationLUTs[OVERLAPTF_NEG] = &m_OPhiExtrapolation;
  m_etaExtrapolationLUTs[FORWARDTF_POS] = &m_FEtaExtrapolation;
  m_etaExtrapolationLUTs[FORWARDTF_NEG] = &m_FEtaExtrapolation;
  m_phiExtrapolationLUTs[FORWARDTF_POS] = &m_FPhiExtrapolation;
  m_phiExtrapolationLUTs[FORWARDTF_NEG] = &m_FPhiExtrapolation;
}

l1t::MicroGMTIsolationUnit::~MicroGMTIsolationUnit ()
{

}

int 
l1t::MicroGMTIsolationUnit::getCaloIndex(outMuon& mu) const 
{
  int phiIndex = m_IdxSelMemPhi.lookup(mu.extrapolatedPhiBits());  

  int eta = mu.extrapolatedEtaBits();
  //if (eta < 0) eta = ~eta+1; // twos complement
  eta = MicroGMTConfiguration::getTwosComp(eta, 9);
  int etaIndex = m_IdxSelMemEta.lookup(eta);
  // FIXME: pretty sure this is nonesense, need to fix in calculate 5by1, too
  return phiIndex + phiIndex*28 + etaIndex; 
}

void 
l1t::MicroGMTIsolationUnit::extrapolateMuons(OutputCollection& result, const InputCollection& inputmuons) const {
  InputCollection::const_iterator mu;
  for (mu = inputmuons.begin(); mu != inputmuons.end(); ++mu) {
    GMTMuonCandidate internalMu(*mu);
    
    // shift by difference of "normal" width and reduced width
    int ptRed = internalMu.ptBits() >> 4;
    int etaAbsRed = std::abs(internalMu.etaBits()) >> 2;
    int etaAbs = abs(internalMu.etaBits()) >> 1;

    int deltaPhi = m_phiExtrapolationLUTs.at((muon_t)internalMu.type())->lookup(internalMu.signBits(), etaAbs, ptRed);
    int deltaEta = m_etaExtrapolationLUTs.at((muon_t)internalMu.type())->lookup(internalMu.signBits(), etaAbsRed, ptRed);
    internalMu.setExtrapolation(deltaPhi, deltaEta);
    result.push_back(internalMu);
  }
}

void
l1t::MicroGMTIsolationUnit::calculate5by1Sums(const GMTInputCaloSumCollection& inputs) 
{
  m_5by1TowerSums.clear();
  if (inputs.size() == 0) return;

  for (int iphi = 0; iphi < 36; ++iphi) {
    int iphiIndexOffset = iphi*28;
    m_5by1TowerSums.push_back(inputs[iphiIndexOffset].etBits()+inputs[iphiIndexOffset+1].etBits()+inputs[iphiIndexOffset+2].etBits());//ieta = 0 (tower -28)
    m_5by1TowerSums.push_back(inputs[iphiIndexOffset-1].etBits()+inputs[iphiIndexOffset].etBits()+inputs[iphiIndexOffset+1].etBits()+inputs[iphiIndexOffset+2].etBits()); // 
    for (int ieta = 2; ieta < 26; ++ieta) {
      int sum = 0;
      for (int dIEta = -2; dIEta <= 2; ++dIEta) {
        sum += inputs[iphiIndexOffset+dIEta].etBits();
      }
      m_5by1TowerSums.push_back(sum);
    }
    m_5by1TowerSums.push_back(inputs[iphiIndexOffset+1].etBits()+inputs[iphiIndexOffset].etBits()+inputs[iphiIndexOffset-1].etBits()+inputs[iphiIndexOffset-2].etBits());
    m_5by1TowerSums.push_back(inputs[iphiIndexOffset].etBits()+inputs[iphiIndexOffset-1].etBits()+inputs[iphiIndexOffset-2].etBits());//ieta = 0 (tower 28)
  }

  m_initialSums = true;
}


int 
l1t::MicroGMTIsolationUnit::calculate5by5Sum(unsigned index) const
{
  if (index > m_5by1TowerSums.size()) {
      std::cout << "warning, energysum out of bounds!" << std::endl;
    return 0;
  }
  // phi wrap around:
  int returnSum = 0; 
  for (int dIPhi = -2; dIPhi <= 2; ++dIPhi) {
    int currIndex = (index + dIPhi*28)%1008; // wrap-around at top
    if (currIndex < 0) currIndex = 1008+currIndex;
    if ((unsigned)currIndex < m_5by1TowerSums.size()) {
      returnSum += m_5by1TowerSums[currIndex];
    } else {
      std::cout << "warning, energysum out of bounds!" << std::endl;
    }
  } 
  return returnSum;
}

void 
l1t::MicroGMTIsolationUnit::isolate(OutputCollection& muons) const
{
  OutputCollection::iterator muIt;
  for (muIt = muons.begin(); muIt != muons.end(); ++muIt) {
    int caloIndex = getCaloIndex(*muIt);
    int energySum = calculate5by5Sum(caloIndex);
    muIt->setIsolationSumBits(energySum);

    int absIso = m_AbsIsoCheckMem.lookup(energySum);
    int relIso = m_RelIsoCheckMem.lookup(energySum, muIt->ptBits());
    muIt->setRelIsolationBits(relIso);
    muIt->setAbsIsolationBits(absIso);
  }
}