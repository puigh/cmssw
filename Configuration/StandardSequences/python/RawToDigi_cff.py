import FWCore.ParameterSet.Config as cms

# This object is used to selectively make changes for different running
# scenarios. In this case it makes changes for Run 2.
from Configuration.StandardSequences.Eras import eras

from CondCore.DBCommon.CondDBSetup_cfi import *

import EventFilter.CSCTFRawToDigi.csctfunpacker_cfi
csctfDigis = EventFilter.CSCTFRawToDigi.csctfunpacker_cfi.csctfunpacker.clone()

import EventFilter.DTTFRawToDigi.dttfunpacker_cfi
dttfDigis = EventFilter.DTTFRawToDigi.dttfunpacker_cfi.dttfunpacker.clone()

import EventFilter.GctRawToDigi.l1GctHwDigis_cfi
gctDigis = EventFilter.GctRawToDigi.l1GctHwDigis_cfi.l1GctHwDigis.clone()

import EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi
gtDigis = EventFilter.L1GlobalTriggerRawToDigi.l1GtUnpack_cfi.l1GtUnpack.clone()

import EventFilter.L1GlobalTriggerRawToDigi.l1GtEvmUnpack_cfi
gtEvmDigis = EventFilter.L1GlobalTriggerRawToDigi.l1GtEvmUnpack_cfi.l1GtEvmUnpack.clone()

from EventFilter.SiPixelRawToDigi.SiPixelRawToDigi_cfi import *

from EventFilter.SiStripRawToDigi.SiStripDigis_cfi import *

from SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_cff import *

import EventFilter.EcalRawToDigi.EcalUnpackerData_cfi
ecalDigis = EventFilter.EcalRawToDigi.EcalUnpackerData_cfi.ecalEBunpacker.clone()

import EventFilter.ESRawToDigi.esRawToDigi_cfi
ecalPreshowerDigis = EventFilter.ESRawToDigi.esRawToDigi_cfi.esRawToDigi.clone()

import EventFilter.HcalRawToDigi.HcalRawToDigi_cfi
hcalDigis = EventFilter.HcalRawToDigi.HcalRawToDigi_cfi.hcalDigis.clone()

import EventFilter.CSCRawToDigi.cscUnpacker_cfi
muonCSCDigis = EventFilter.CSCRawToDigi.cscUnpacker_cfi.muonCSCDigis.clone()

import EventFilter.DTRawToDigi.dtunpacker_cfi
muonDTDigis = EventFilter.DTRawToDigi.dtunpacker_cfi.muonDTDigis.clone()

import EventFilter.RPCRawToDigi.rpcUnpacker_cfi
muonRPCDigis = EventFilter.RPCRawToDigi.rpcUnpacker_cfi.rpcunpacker.clone()

from EventFilter.CastorRawToDigi.CastorRawToDigi_cff import *
castorDigis = EventFilter.CastorRawToDigi.CastorRawToDigi_cfi.castorDigis.clone( FEDs = cms.untracked.vint32(690,691,692) )

from EventFilter.ScalersRawToDigi.ScalersRawToDigi_cfi import *

from EventFilter.Utilities.tcdsRawToDigi_cfi import *
tcdsDigis = EventFilter.Utilities.tcdsRawToDigi_cfi.tcdsRawToDigi.clone()

from EventFilter.L1TRawToDigi.caloStage1Digis_cfi import *

from EventFilter.L1TRawToDigi.caloStage2Digis_cfi import *

from L1Trigger.L1TCalorimeter.simCaloStage1LegacyFormatDigis_cfi import *
caloStage1LegacyFormatDigis = L1Trigger.L1TCalorimeter.simCaloStage1LegacyFormatDigis_cfi.clone()
caloStage1LegacyFormatDigis.InputCollection = cms.InputTag("caloStage1Digis")
caloStage1LegacyFormatDigis.InputRlxTauCollection = cms.InputTag("caloStage1Digis:rlxTaus")
caloStage1LegacyFormatDigis.InputIsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus")
caloStage1LegacyFormatDigis.InputHFSumsCollection = cms.InputTag("caloStage1Digis:HFRingSums")
caloStage1LegacyFormatDigis.InputHFCountsCollection = cms.InputTag("caloStage1Digis:HFBitCounts")


RawToDigi = cms.Sequence(csctfDigis
                         +dttfDigis
                         +gctDigis
                         +gtDigis
                         +gtEvmDigis
                         +siPixelDigis
                         +siStripDigis
                         +ecalDigis
                         +ecalPreshowerDigis
                         +hcalDigis
                         +muonCSCDigis
                         +muonDTDigis
                         +muonRPCDigis
                         +castorDigis
                         +scalersRawToDigi
                         +tcdsDigis)

RawToDigi_noTk = cms.Sequence(csctfDigis
                              +dttfDigis
                              +gctDigis
                              +gtDigis
                              +gtEvmDigis
                              +ecalDigis
                              +ecalPreshowerDigis
                              +hcalDigis
                              +muonCSCDigis
                              +muonDTDigis
                              +muonRPCDigis
                              +castorDigis
                              +scalersRawToDigi
                              +tcdsDigis)
    
scalersRawToDigi.scalersInputTag = 'rawDataCollector'
csctfDigis.producer = 'rawDataCollector'
dttfDigis.DTTF_FED_Source = 'rawDataCollector'
gctDigis.inputLabel = 'rawDataCollector'
gtDigis.DaqGtInputTag = 'rawDataCollector'
siPixelDigis.InputLabel = 'rawDataCollector'
#false by default anyways ecalDigis.DoRegional = False
ecalDigis.InputLabel = 'rawDataCollector'
ecalPreshowerDigis.sourceTag = 'rawDataCollector'
hcalDigis.InputLabel = 'rawDataCollector'
muonCSCDigis.InputObjects = 'rawDataCollector'
muonDTDigis.inputLabel = 'rawDataCollector'
muonRPCDigis.InputLabel = 'rawDataCollector'
gtEvmDigis.EvmGtInputTag = 'rawDataCollector'
castorDigis.InputLabel = 'rawDataCollector'

##
## Make changes for Run 2
##
def _modifyRawToDigiForRun2( RawToDigi_object ) :
    RawToDigi_object.remove(gtEvmDigis)

eras.run2_common.toModify( RawToDigi, func=_modifyRawToDigiForRun2 )


def _modifyRawToDigiForStage1Trigger( RawToDigi_object ) :
    L1Stage1RawToDigiSeq = cms.Sequence( gctDigis 
                                         +caloStage1Digis
                                         +caloStage1LegacyFormatDigis)
    RawToDigi_object.replace( gctDigis, L1Stage1RawToDigiSeq )

eras.stage1L1Trigger.toModify( RawToDigi, func=_modifyRawToDigiForStage1Trigger )

def _modifyRawToDigiForStage2Trigger( RawToDigi_object ) :
    L1Stage2RawToDigiSeq = cms.Sequence( caloStage2Digis )
    RawToDigi_object.replace( gctDigis, L1Stage2RawToDigiSeq )

eras.stage2L1Trigger.toModify( RawToDigi, func=_modifyRawToDigiForStage2Trigger )

# A unique name is required for this object, so I'll call it "modify<python filename>ForRun2_"




