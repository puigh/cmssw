#include "../interface/MicroGMTMatchQualLUT.h"

MicroGMTMatchQualLUT::MicroGMTMatchQualLUT (const edm::ParameterSet& iConfig, std::string prefix) {
  edm::ParameterSet config = iConfig.getParameter<edm::ParameterSet>(prefix+"MatchQualLUTSettings");
  m_dPhiRedInWidth = config.getParameter<int>("deltaPhiRed_in_width");
  m_dEtaRedInWidth = config.getParameter<int>("deltaEtaRed_in_width");
  
  m_totalInWidth = m_dPhiRedInWidth + m_dEtaRedInWidth;

  m_dEtaRedMask = (1 << m_dEtaRedInWidth) - 1;
  m_dPhiRedMask = (1 << (m_totalInWidth - 1)) - m_dEtaRedMask - 1;
  
  m_inputs.push_back(DELTA_ETA_RED);
  m_inputs.push_back(DELTA_PHI_RED);
  std::string m_fname = config.getParameter<std::string>("filename");
  if (m_fname != std::string("")) {
    load(m_fname);
  } 
}

MicroGMTMatchQualLUT::~MicroGMTMatchQualLUT ()
{

}


int 
MicroGMTMatchQualLUT::lookup(int dEtaRed, int dPhiRed) const 
{
  // normalize these two to the same scale and then calculate?
  if (m_initialized) {
    return lookupPacked(hashInput(dEtaRed, dPhiRed));
  }

  return -1; 
}

int 
MicroGMTMatchQualLUT::hashInput(int dEtaRed, int dPhiRed) const
{

  int result = 0;
  result += dEtaRed;
  result += dPhiRed << m_dEtaRedInWidth;
  return result;
}

void 
MicroGMTMatchQualLUT::unHashInput(int input, int& dEtaRed, int& dPhiRed) const 
{
  dEtaRed = input & m_dEtaRedMask;
  dPhiRed = (input & m_dPhiRedMask) >> m_dEtaRedInWidth;
} 