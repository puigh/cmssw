import FWCore.ParameterSet.Config as cms

microGMTEmulator = cms.EDProducer('MicroGMTEmulator',
    barrelTFInput = cms.InputTag("microGMTInputProducer", "BarrelTFMuons"),
    overlapTFInput = cms.InputTag("microGMTInputProducer", "OverlapTFMuons"),
    forwardTFInput = cms.InputTag("microGMTInputProducer", "ForwardTFMuons"),
    triggerTowerInput = cms.InputTag("microGMTInputProducer", "TriggerTowerSums"),
 
    AbsIsoCheckMemLUTSettings = cms.PSet (
     	areaSum_in_width = cms.int32(5), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/AbsIsoCheckMem.lut'),
     ) ,
      
    IdxSelMemPhiLUTSettings = cms.PSet (
     	phi_in_width = cms.int32(10), 
     	out_width = cms.int32(6),
     	filename = cms.string('test/IdxSelMemPhi.lut'),
     ) ,
      
    FwdPosSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/FwdPosSingleMatchQual.lut'),
     ) ,
      
    BONegMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/BONegMatchQual.lut'),
     ) ,
      
    OvlNegSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/OvlNegSingleMatchQual.lut'),
     ) ,
      
    IdxSelMemEtaLUTSettings = cms.PSet (
     	eta_in_width = cms.int32(9), 
     	out_width = cms.int32(5),
     	filename = cms.string('test/IdxSelMemEta.lut'),
     ) ,
      
    FOPosMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/FOPosMatchQual.lut'),
     ) ,
      
    FwdNegSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/FwdNegSingleMatchQual.lut'),
     ) ,
      
    BPhiExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbs_in_width = cms.int32(8), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('test/BPhiExtrapolation.lut'),
     ) ,
      
    BrlSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/BrlSingleMatchQual.lut'),
     ) ,
      
    RelIsoCheckMemLUTSettings = cms.PSet (
     	areaSum_in_width = cms.int32(5), 
     	pT_in_width = cms.int32(9), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/RelIsoCheckMem.lut'),
     ) ,
      
    OPhiExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbs_in_width = cms.int32(8), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('test/OPhiExtrapolation.lut'),
     ) ,
      
    OvlPosSingleMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/OvlPosSingleMatchQual.lut'),
     ) ,
      
    FEtaExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbsRed_in_width = cms.int32(7), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('test/FEtaExtrapolation.lut'),
     ) ,
      
    BOPosMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/BOPosMatchQual.lut'),
     ) ,
      
    OEtaExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbsRed_in_width = cms.int32(7), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('test/OEtaExtrapolation.lut'),
     ) ,
      
    BEtaExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbsRed_in_width = cms.int32(7), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('test/BEtaExtrapolation.lut'),
     ) ,
      
    FPhiExtrapolationLUTSettings = cms.PSet (
     	charge_in_width = cms.int32(1), 
     	etaAbs_in_width = cms.int32(8), 
     	pTred_in_width = cms.int32(5), 
     	out_width = cms.int32(4),
     	filename = cms.string('test/FPhiExtrapolation.lut'),
     ) ,
      
    FONegMatchQualLUTSettings = cms.PSet (
     	deltaEtaRed_in_width = cms.int32(4), 
     	deltaPhiRed_in_width = cms.int32(3), 
     	out_width = cms.int32(1),
     	filename = cms.string('test/FONegMatchQual.lut'),
     ) ,
      
    SortRankLUTSettings = cms.PSet (
     	pT_in_width = cms.int32(9), 
     	qual_in_width = cms.int32(4), 
     	out_width = cms.int32(10),
     	filename = cms.string('test/SortRank.lut'),
     )
)
  
