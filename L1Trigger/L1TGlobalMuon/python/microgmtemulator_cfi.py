import FWCore.ParameterSet.Config as cms

microGMTEmulator = cms.EDProducer('MicroGMTEmulator',
    barrelTFInput = cms.InputTag("microGMTInputProducer", "BarrelTFMuons"),
    overlapTFInput = cms.InputTag("microGMTInputProducer", "OverlapTFMuons"),
    forwardTFInput = cms.InputTag("microGMTInputProducer", "ForwardTFMuons"),
    triggerTowerInput = cms.InputTag("microGMTInputProducer", "TriggerTowerSums"),
 
    AbsIsoCheckMemLUTSettings = cms.PSet (
     	areaSum_in_width = cms.int32(5), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/AbsIsoCheckMem.lut'),
     ) ,
      
    IdxSelMemPhiLUTSettings = cms.PSet (
     	phi_in_width = cms.int32(10), 
     	out_width = cms.int32(6),
     	filename = cms.string('data/IdxSelMemPhi.lut'),
     ) ,
      
    FwdPosSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/FwdPosSingleMatchQual.lut'),
     ) ,
      
    BONegMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/BONegMatchQual.lut'),
     ) ,
      
    OvlNegSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/OvlNegSingleMatchQual.lut'),
     ) ,
      
    IdxSelMemEtaLUTSettings = cms.PSet (
     	eta_in_width = cms.int32(9), 
     	out_width = cms.int32(5),
     	filename = cms.string('data/IdxSelMemEta.lut'),
     ) ,
      
    FOPosMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/FOPosMatchQual.lut'),
     ) ,
      
    FwdNegSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/FwdNegSingleMatchQual.lut'),
     ) ,
      
    BPhiExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbs_in_width = cms.int32(8), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('data/BPhiExtrapolation.lut'),
     ) ,
      
    BrlSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/BrlSingleMatchQual.lut'),
     ) ,
      
    RelIsoCheckMemLUTSettings = cms.PSet (
     	areaSum_in_width = cms.int32(5), 
     	pT_in_width = cms.int32(9), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/RelIsoCheckMem.lut'),
     ) ,
      
    OPhiExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbs_in_width = cms.int32(8), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('data/OPhiExtrapolation.lut'),
     ) ,
      
    OvlPosSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/OvlPosSingleMatchQual.lut'),
     ) ,
      
    FEtaExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbsRed_in_width = cms.int32(7), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('data/FEtaExtrapolation.lut'),
     ) ,
      
    BOPosMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/BOPosMatchQual.lut'),
     ) ,
      
    OEtaExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbsRed_in_width = cms.int32(7), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('data/OEtaExtrapolation.lut'),
     ) ,
      
    BEtaExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbsRed_in_width = cms.int32(7), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('data/BEtaExtrapolation.lut'),
     ) ,
      
    FPhiExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbs_in_width = cms.int32(8), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('data/FPhiExtrapolation.lut'),
     ) ,
      
    FONegMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('data/FONegMatchQual.lut'),
     ) ,
      
    SortRankLUTSettings = cms.PSet (
     	pT_in_width = cms.int32(9), 
     	qual_in_width = cms.int32(4), 
     	out_width = cms.int32(10),
     	filename = cms.string('data/SortRank.lut'),
     )
)
  
