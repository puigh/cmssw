import FWCore.ParameterSet.Config as cms
import UserCode.MicroGMTEmulator.microgmtemulator_cfi as defaults

gmtTest = cms.EDAnalyzer('MicroGMTTest',

    etaExtrapolationLUTSettings = cms.PSet(
        test_file = "test/etaExtrapolation.lut"
    ).extend(defaults),
    phiExtrapolationLUTSettings = cms.PSet(
        test_file = "test/phiExtrapolation.lut"
    ).extend(defaults),

    rankPtQualLUTSettings = cms.PSet (
        pt_in_width = cms.int32(9),
        quality_in_width = cms.int32(4),
        out_width = cms.int32(10),
        test_file = "rankPtQual.lut"
    ).extend(defaults)
).extend(defaults)
