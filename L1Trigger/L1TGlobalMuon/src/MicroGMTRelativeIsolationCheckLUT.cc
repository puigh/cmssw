#include "../interface/MicroGMTRelativeIsolationCheckLUT.h"

MicroGMTRelativeIsolationCheckLUT::MicroGMTRelativeIsolationCheckLUT (const edm::ParameterSet& iConfig, const std::string& setName) 
{
  getParameters(iConfig, setName.c_str());
}

MicroGMTRelativeIsolationCheckLUT::MicroGMTRelativeIsolationCheckLUT (const edm::ParameterSet& iConfig, const char* setName) 
{
  getParameters(iConfig, setName);
}

void 
MicroGMTRelativeIsolationCheckLUT::getParameters (const edm::ParameterSet& iConfig, const char* setName) 
{
  edm::ParameterSet config = iConfig.getParameter<edm::ParameterSet>(setName);
  m_energySumInWidth = config.getParameter<int>("areaSum_in_width");
  m_ptInWidth = config.getParameter<int>("pT_in_width");
  
  m_totalInWidth = m_ptInWidth + m_energySumInWidth;

  m_energySumMask = (1 << m_energySumInWidth) - 1;
  m_ptMask = (1 << (m_totalInWidth - 1)) - m_energySumInWidth;
  std::string m_fname = config.getParameter<std::string>("filename");
  if (m_fname != std::string("")) {
    load(m_fname);
  } 
  m_inputs.push_back(PT);
  m_inputs.push_back(ETA);
}


MicroGMTRelativeIsolationCheckLUT::~MicroGMTRelativeIsolationCheckLUT ()
{

}

int 
MicroGMTRelativeIsolationCheckLUT::lookup(int energySum, int pt) const 
{
  // normalize these two to the same scale and then calculate?
  return lookupPacked(hashInput(energySum, pt));
}

int 
MicroGMTRelativeIsolationCheckLUT::hashInput(int energySum, int pT) const
{
  int result = 0;
  result += energySum;
  result += pT << m_energySumInWidth;
  return result;
}

void 
MicroGMTRelativeIsolationCheckLUT::unHashInput(int input, int& energySum, int& pt) const 
{
  energySum = input & m_energySumMask;
  pt = (input & m_ptMask) >> m_energySumInWidth;
} 