#include "../interface/MicroGMTConfiguration.h"

MicroGMTConfiguration::MicroGMTConfigInstance::MicroGMTConfigInstance(const edm::ParameterSet& iConfig) 
{
  m_inputToString[PT] = "pt";
  m_inputToString[PT_COARSE] = "pt_coarse";
  m_inputToString[ETA] = "eta";
  m_inputToString[ETA_COARSE] = "eta_coarse";
  m_inputToString[PHI] = "phi";
  m_inputToString[QUALITY] = "quality";

  m_stringToInput["pt"] = PT;
  m_stringToInput["pt_coarse"] = PT_COARSE;
  m_stringToInput["eta"] = ETA;
  m_stringToInput["eta_coarse"] = ETA_COARSE;
  m_stringToInput["phi"] = PHI;
  m_stringToInput["quality"] = QUALITY;


  // std::map<std::string, input_t>::iterator inpIt;
  // for (inpIt = m_stringToInput.begin(); inpIt != m_stringToInput.end(); ++inpIt) {
  //   m_inputToWidth[inpIt->second] = iConfig.getParameter<int>(inpIt->first+"_width");
  // }
}

MicroGMTConfiguration::MicroGMTConfigInstance::~MicroGMTConfigInstance() 
{

}
unsigned MicroGMTConfiguration::getTwosComp(const int signed_int, const int width) {
  if (signed_int >= 0) {
    return (unsigned)signed_int;
  }
  int all_one = (1 << width)-1;
  return ((-signed_int) ^ all_one) + 1;
}

unsigned 
MicroGMTConfiguration::MicroGMTConfigInstance::getInputWidth(const std::string &inputname) 
{
  input_t input = m_stringToInput[inputname];
  return getInputWidth(input);
}

unsigned 
MicroGMTConfiguration::MicroGMTConfigInstance::getInputWidth(const input_t input) 
{
  return m_inputToWidth[input];
}

MicroGMTConfiguration::MicroGMTConfigInstance* MicroGMTConfiguration::m_instance = 0;

void 
MicroGMTConfiguration::initialize(const edm::ParameterSet& iConfig) 
{
  m_instance = new MicroGMTConfigInstance(iConfig);
}

void 
MicroGMTConfiguration::finalize() 
{
  delete m_instance;
}