#ifndef __l1microgmtcanceloutunit_h
#define __l1microgmtcanceloutunit_h

#include "MicroGMTConfiguration.h"
#include "MicroGMTMatchQualLUT.h"

namespace l1t {
  class MicroGMTCancelOutUnit {
    public: 
      explicit MicroGMTCancelOutUnit (const edm::ParameterSet&);
      virtual ~MicroGMTCancelOutUnit ();
      
      void setCancelOutBits(OutputCollection&);
      void getCancelOutBits( std::vector<OutputCollection::iterator> &, std::vector<OutputCollection::iterator> &);
    private:
      MicroGMTMatchQualLUT m_boPosMatchQualLUT;
      MicroGMTMatchQualLUT m_boNegMatchQualLUT;
      MicroGMTMatchQualLUT m_foPosMatchQualLUT;
      MicroGMTMatchQualLUT m_foNegMatchQualLUT;
      MicroGMTMatchQualLUT m_brlSingleMatchQualLUT;
      MicroGMTMatchQualLUT m_ovlPosSingleMatchQualLUT;
      MicroGMTMatchQualLUT m_ovlNegSingleMatchQualLUT;
      MicroGMTMatchQualLUT m_fwdPosSingleMatchQualLUT;
      MicroGMTMatchQualLUT m_fwdNegSingleMatchQualLUT;
      std::map<int, MicroGMTMatchQualLUT*> m_lutDict;
  };
}
#endif /* defined(__l1microgmtcanceloutunit_h) */