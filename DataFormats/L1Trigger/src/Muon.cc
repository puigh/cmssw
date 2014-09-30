
#include "DataFormats/L1Trigger/interface/Muon.h"

namespace l1t {
  Muon::Muon( const LorentzVector& p4,
      int pt,
      int eta,
      int phi,
      int qual,
      int charge,
      int chargeValid,
      int iso,
      int mip,
      int tag,
      bool debug,
      int isoSum,
      int dPhi,
      int dEta,
      int rank )
    : L1Candidate(p4, pt, eta, phi, qual, iso),
      hwCharge_(charge),
      hwChargeValid_(chargeValid),
      hwMip_(mip),
      hwTag_(tag),
      debug_(debug),
      hwIsoSum_(isoSum),
      hwDPhiExtra_(dPhi),
      hwDEtaExtra_(dEta),
      hwRank_(rank)
  {
    
  }

  Muon::~Muon() 
  {

  }

  void Muon::setHwCharge(int charge)
  {
    hwCharge_ = charge;
  }

  void Muon::setHwChargeValid(int valid)
  {
    hwChargeValid_ = valid;
  }

  void Muon::setHwTag(int tag)
  {
    hwTag_ = tag;
  }

  void setHwIsoSum(int isoSum) 
  {
    hwIsoSum_ = isoSum;
  }

  void setHwDPhiExtra(int dPhi)
  {
    hwDEtaExtra_ = dPhi;
  }

  void setHwDEtaExtra(int dEta) 
  {
    hwDEtaExtra_ = dEta;
  }

  void setHwRank(int rank) 
  {
    hwRank_ = rank;
  }

  int Muon::hwCharge() const
  {
    return hwCharge_;
  }

  int Muon::hwChargeValid() const
  {
    return hwChargeValid_;
  }

  int Muon::hwMip() const
  {
    return hwMip_;
  }

  int Muon::hwTag() const
  {
    return hwTag_;
  }

  int hwIsoSum() const 
  {
    return hwIsoSum_;
  }

  int hwDPhiExtra() const
  {
    return hwDPhiExtra_;
  }

  int hwDEtaExtra() const
  {
    return hwDEtaExtra_;
  }

  int hwRank() const
  {
    return hwRank_;
  }
}