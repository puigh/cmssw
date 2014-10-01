#ifndef __l1microgmtconfiguration_h
#define __l1microgmtconfiguration_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTInputMuon.h"
#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTMuonCandidate.h"

#include <map>
#include <utility>

namespace l1t {
  typedef std::pair<input_t, int> PortType; 
  typedef std::vector<std::vector<bool> > ResultMatrix;
  typedef GMTInputMuonCollection InputCollection;
  typedef std::list<GMTMuonCandidate> OutputCollection;
  typedef GMTMuonCandidate outMuon;

  enum input_t { 
    PT, PT_COARSE, PHI, ETA, ETA_COARSE, QUALITY, DELTA_ETA_RED, DELTA_PHI_RED
  };

  enum muon_t {
    BARRELTF = 0, OVERLAPTF_NEG = 1, OVERLAPTF_POS = 2, FORWARDTF_NEG = 3, FORWARDTF_POS = 4, ALL
  };

  class MicroGMTConfiguration {
    public:
      static unsigned getTwosComp(const int signed_int, const int width);

      
  };
}
#endif /* defined (__l1microgmtconfiguration_h) */ 