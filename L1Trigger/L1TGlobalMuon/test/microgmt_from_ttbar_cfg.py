import FWCore.ParameterSet.Config as cms

process = cms.Process("L1MicroGMTEmulator")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50) )

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/2088E3F2-5842-E411-A614-0025905A6080.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/26782EF3-5842-E411-AAD0-0025905B85A2.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/26A7E8F0-5842-E411-A53A-00261894398D.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/32B26189-5D42-E411-97D8-002618943976.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/6AB614F9-5842-E411-9C66-002618943870.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/6C874C8A-5D42-E411-A03D-0026189438B9.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/80FFAD28-5942-E411-8AF6-00261894392F.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/82F1577B-5942-E411-8D8E-002618943986.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/94BD99F2-5842-E411-80AC-003048FFCC2C.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/A6C5A67A-5942-E411-ABCD-00261894397A.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/B8F19FEE-5842-E411-B24C-0026189438E7.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/D249C9F3-5842-E411-B1C8-0025905B858E.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/DCAE702D-5942-E411-86B8-0026189438E0.root',
        '/store/relval/CMSSW_7_2_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_PRE_LS172_V12-v1/00000/ECBAC728-5942-E411-AF08-0026189438F8.root',
    ),
)

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgradePLS1', '')

process.uGMTInputProducer = cms.EDProducer("l1t::uGMTInputProducerFromGen",
)



process.load("L1Trigger.L1TGlobalMuon.microgmtemulator_cfi")


process.microGMTEmulator.barrelTFInput = cms.InputTag("uGMTInputProducer", "BarrelTFMuons")
process.microGMTEmulator.overlapTFInput = cms.InputTag("uGMTInputProducer", "OverlapTFMuons")
process.microGMTEmulator.forwardTFInput = cms.InputTag("uGMTInputProducer", "ForwardTFMuons")
process.microGMTEmulator.triggerTowerInput = cms.InputTag("uGMTInputProducer", "TriggerTowerSums")

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('ttbar_test.root')
)


#process.content = cms.EDAnalyzer("EventContentAnalyzer")
process.p = cms.Path(process.uGMTInputProducer
    *process.microGMTEmulator)

process.e = cms.EndPath(process.out)
