#ifndef __l1microgmtconfiguration_h
#define __l1microgmtconfiguration_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTInputMuon.h"
#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTMuonCandidate.h"

#include <map>
#include <utility>

enum input_t { 
  PT, PT_COARSE, PHI, ETA, ETA_COARSE, QUALITY, DELTA_ETA_RED, DELTA_PHI_RED
};

enum muon_t {
    BARRELTF = 0, OVERLAPTF_NEG = 1, OVERLAPTF_POS = 2, FORWARDTF_NEG = 3, FORWARDTF_POS = 4, ALL
};

typedef std::pair<input_t, int> PortType; 
typedef std::vector<std::vector<bool> > ResultMatrix;
typedef GMTInputMuonCollection InputCollection;
typedef std::list<GMTMuonCandidate> OutputCollection;
typedef GMTMuonCandidate outMuon;

class MicroGMTConfiguration {
  public:
    static unsigned getInputWidth(const std::string &inputname) { return instance().getInputWidth(inputname); };
    static unsigned getInputWidth(input_t input) { return instance().getInputWidth(input); };
    static std::string& getInputName(const input_t input) { return instance().getInputName(input); };
    static void initialize(const edm::ParameterSet& iConfig);
    static void finalize();
    static unsigned getTwosComp(const int signed_int, const int width);

  private:
    class MicroGMTConfigInstance {
      public:
        explicit MicroGMTConfigInstance(const edm::ParameterSet& iConfig);
        ~MicroGMTConfigInstance();

        unsigned getInputWidth(const std::string &inputname);
        unsigned getInputWidth(input_t input);
        std::string& getInputName(const input_t input) { return m_inputToString[input]; };

      private:
        MicroGMTConfigInstance();
        MicroGMTConfigInstance(const MicroGMTConfiguration&);
        MicroGMTConfigInstance& operator=(const MicroGMTConfiguration&);

        // information stored for LUTs:
        std::map<input_t, std::string> m_inputToString;
        std::map<std::string, input_t> m_stringToInput;
        std::map<input_t, unsigned> m_inputToWidth;
        bool m_initialized;
    };

    MicroGMTConfiguration();
    MicroGMTConfiguration(const MicroGMTConfiguration&);
    MicroGMTConfiguration& operator=(const MicroGMTConfiguration&);

    static MicroGMTConfigInstance& instance() {return *m_instance; };

    static MicroGMTConfigInstance* m_instance;

    
};

#endif /* defined (__l1microgmtconfiguration_h) */ 