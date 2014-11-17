#include "../interface/MicroGMTExtrapolationLUT.h"

l1t::MicroGMTExtrapolationLUT::MicroGMTExtrapolationLUT (const edm::ParameterSet& iConfig, const std::string& setName, const int type) {
  getParameters(iConfig, setName.c_str(), type);
}

l1t::MicroGMTExtrapolationLUT::MicroGMTExtrapolationLUT (const edm::ParameterSet& iConfig, const char* setName, const int type) {
  getParameters(iConfig, setName, type);
}

void 
l1t::MicroGMTExtrapolationLUT::getParameters (const edm::ParameterSet& iConfig, const char* setName, const int type) {
  edm::ParameterSet config = iConfig.getParameter<edm::ParameterSet>(setName);
  m_chrgInWidth = config.getParameter<int>("charge_in_width");

  if (type == 1) {
    m_angleInWidth = config.getParameter<int>("etaAbs_in_width");
  } else {
    m_angleInWidth = config.getParameter<int>("etaAbsRed_in_width");
  }
  m_ptRedInWidth = config.getParameter<int>("pTred_in_width");
  
  m_totalInWidth = m_ptRedInWidth + m_angleInWidth + m_chrgInWidth;

  m_chrgMask = (1 << m_ptRedInWidth) - 1;
  m_angleMask = (1 << (m_ptRedInWidth + m_angleInWidth - 1)) - m_chrgMask;
  m_ptRedMask = (1 << (m_totalInWidth - 1)) - m_chrgMask - m_angleMask;
  std::string m_fname = config.getParameter<std::string>("filename");
  if (m_fname != std::string("")) {
    load(m_fname);
  } 
  m_inputs.push_back(MicroGMTConfiguration::PT);
  m_inputs.push_back(MicroGMTConfiguration::ETA);
}


l1t::MicroGMTExtrapolationLUT::~MicroGMTExtrapolationLUT ()
{

}


int 
l1t::MicroGMTExtrapolationLUT::lookup(int charge, int angle, int pt) const 
{
  // normalize these two to the same scale and then calculate?
  if (m_initialized) {
    unsigned myAngle = MicroGMTConfiguration::getTwosComp(angle, m_angleInWidth);
    return lookupPacked(hashInput(checkedInput(charge, m_chrgInWidth), checkedInput(myAngle, m_angleInWidth), checkedInput(pt, m_ptRedInWidth)));
  }
  int result = 0;
  // normalize to out width
  return result;
}

int 
l1t::MicroGMTExtrapolationLUT::hashInput(int charge, int angle, int pt) const
{
  int result = 0;
  result += charge;
  result += angle << m_chrgInWidth;
  result += pt << (m_chrgInWidth + m_angleInWidth);
  return result;
}

void 
l1t::MicroGMTExtrapolationLUT::unHashInput(int input, int& charge, int& angle, int& pt) const 
{
  charge = input & m_chrgMask;
  angle = (input & m_angleMask) >> m_chrgInWidth;
  pt = (input & m_ptRedMask) >> (m_chrgInWidth+m_angleInWidth);
} 