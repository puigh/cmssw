#ifndef __l1microgmtisolationunit_h
#define __l1microgmtisolationunit_h

#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTInputCaloSum.h"
#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTInputMuon.h"
#include "UserCode/L1MicroGlobalMuonTriggerDataFormats/interface/GMTMuonCandidate.h"

#include "MicroGMTConfiguration.h"
#include "MicroGMTExtrapolationLUT.h"
#include "MicroGMTCaloIndexSelectionLUT.h"
#include "MicroGMTRelativeIsolationCheckLUT.h"
#include "MicroGMTAbsoluteIsolationCheckLUT.h"

namespace l1t {
  class MicroGMTIsolationUnit {
    public: 
      explicit MicroGMTIsolationUnit (const edm::ParameterSet&);
      virtual ~MicroGMTIsolationUnit ();

      // returns the index corresponding to the calo tower sum 
      int getCaloIndex(outMuon&) const;

      void calculate5by1Sums(const GMTInputCaloSumCollection&);
      int calculate5by5Sum(unsigned index) const;

      void isolate(OutputCollection&) const;
      void extrapolateMuons(OutputCollection&, const InputCollection&) const;

    private:
      MicroGMTExtrapolationLUT m_BEtaExtrapolation;
      MicroGMTExtrapolationLUT m_BPhiExtrapolation;
      MicroGMTExtrapolationLUT m_OEtaExtrapolation;
      MicroGMTExtrapolationLUT m_OPhiExtrapolation;
      MicroGMTExtrapolationLUT m_FEtaExtrapolation;
      MicroGMTExtrapolationLUT m_FPhiExtrapolation;

      std::map<muon_t, MicroGMTExtrapolationLUT*> m_phiExtrapolationLUTs;
      std::map<muon_t, MicroGMTExtrapolationLUT*> m_etaExtrapolationLUTs;

      MicroGMTCaloIndexSelectionLUT m_IdxSelMemEta;
      MicroGMTCaloIndexSelectionLUT m_IdxSelMemPhi;
      
      MicroGMTRelativeIsolationCheckLUT m_RelIsoCheckMem;
      MicroGMTAbsoluteIsolationCheckLUT m_AbsIsoCheckMem;

      std::vector<int> m_5by1TowerSums;
      bool m_initialSums;
  };
}

#endif /* defined(__l1microgmtisolationunit_h) */