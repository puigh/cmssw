import FWCore.ParameterSet.Config as cms

process = cms.Process("L1MicroGMTEmulator")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(91) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
            'file:test.root'
    )
)

process.load("UserCode.MicroGMTEmulator.microgmtemulator_cfi")

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root')
)

#process.content = cms.EDAnalyzer("EventContentAnalyzer")
process.p = cms.Path(process.microGMTEmulator)

process.e = cms.EndPath(process.out)
