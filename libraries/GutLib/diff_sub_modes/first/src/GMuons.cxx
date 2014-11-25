//
// GMuons.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 08:20:51 $
// $Revision: 1.84 $
//

#include <GMuons.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMuons)
#endif

GMuons *gMuons = 0;

//_____________________________________________________________
// GMuons
// Muon Class for everything which is related only to Muons
//
//
GMuons::GMuons() : GPhysObj() {
  //
  // GMuons default constructor
  if ( gDebug ) cout << endl << "GMuons::GMuons ctor called" << endl << endl;

  // initialize global pointer
  gMuons = this;

  // inizialize clonesarray
  fNMuons = 0;
  fMuons = new TClonesArray("GMuon",1024);

  // initialize cut flags
  fMuonsCut = 0;
  fMuonsMinIsolation10Veto = kFALSE;

  // reset muon counters
  fBarrelMuons     = 0;
  fForwardMuons    = 0;
  fRearMuons       = 0;
  fGlomus          = kFALSE;   //set if at least 1 muon with glomu in event;
  // initialize general histograms

  // general uncut plots
  fGeneralWeight_uncut = 0;
  fGeneralWeightForward_uncut = 0;
  fGeneralWeightBarrel_uncut = 0;
  fGeneralWeightRear_uncut = 0;
  fGeneralWeightMUBAC_uncut = 0;
  fGeneralWeightMUBACForward_uncut = 0;
  fGeneralWeightMUBACBarrel_uncut = 0;
  fGeneralWeightMUBACRear_uncut = 0;
  fGeneralWeightBREMAT_uncut = 0;
  fGeneralWeightBREMATForward_uncut = 0;
  fGeneralWeightBREMATBarrel_uncut = 0;
  fGeneralWeightBREMATRear_uncut = 0;
  fGeneralWeightMPMATCH_uncut = 0;
  fGeneralWeightMPMATCHForward_uncut = 0;
  fGeneralWeightMPMATCHBarrel_uncut = 0;
  fGeneralWeightMPMATCHRear_uncut = 0;
  fGeneralWeightBREMATMUBAC_uncut = 0;
  fGeneralWeightBREMATMUBACForward_uncut = 0;
  fGeneralWeightBREMATMUBACBarrel_uncut = 0;
  fGeneralWeightBREMATMUBACRear_uncut = 0;
  fGeneralWeightMPMATCHMUBAC_uncut = 0;
  fGeneralWeightMPMATCHMUBACForward_uncut = 0;
  fGeneralWeightMPMATCHMUBACBarrel_uncut = 0;
  fGeneralWeightMPMATCHMUBACRear_uncut = 0;
  fGeneralNMU_uncut = 0;
  fGeneralRegions_uncut = 0;
  fGeneralProb_uncut = 0;
  fGeneralP_uncut = 0;
  fGeneralPt_uncut = 0;
  fGeneralPtSpecial_uncut = 0;
  fGeneralPx_uncut = 0;
  fGeneralPy_uncut = 0;
  fGeneralPz_uncut = 0;
  fGeneralPhi_uncut = 0;
  fGeneralTheta_uncut = 0;
  fGeneralEta_uncut = 0;
  fGeneralCharge_uncut = 0;

  fGeneralNMUForward_uncut = 0;
  fGeneralProbForward_uncut = 0;
  fGeneralPForward_uncut = 0;
  fGeneralPtForward_uncut = 0;
  fGeneralPtSpecialForward_uncut = 0;
  fGeneralPxForward_uncut = 0;
  fGeneralPyForward_uncut = 0;
  fGeneralPzForward_uncut = 0;
  fGeneralPhiForward_uncut = 0;
  fGeneralThetaForward_uncut = 0;
  fGeneralEtaForward_uncut = 0;
  fGeneralChargeForward_uncut = 0;

  fGeneralNMUBarrel_uncut = 0;
  fGeneralProbBarrel_uncut = 0;
  fGeneralPBarrel_uncut = 0;
  fGeneralPtBarrel_uncut = 0;
  fGeneralPtSpecialBarrel_uncut = 0;
  fGeneralPxBarrel_uncut = 0;
  fGeneralPyBarrel_uncut = 0;
  fGeneralPzBarrel_uncut = 0;
  fGeneralPhiBarrel_uncut = 0;
  fGeneralThetaBarrel_uncut = 0;
  fGeneralEtaBarrel_uncut = 0;
  fGeneralChargeBarrel_uncut = 0;

  fGeneralNMURear_uncut = 0;
  fGeneralProbRear_uncut = 0;
  fGeneralPRear_uncut = 0;
  fGeneralPtRear_uncut = 0;
  fGeneralPtSpecialRear_uncut = 0;
  fGeneralPxRear_uncut = 0;
  fGeneralPyRear_uncut = 0;
  fGeneralPzRear_uncut = 0;
  fGeneralPhiRear_uncut = 0;
  fGeneralThetaRear_uncut = 0;
  fGeneralEtaRear_uncut = 0;
  fGeneralChargeRear_uncut = 0;
  fGeneralMuonFinder_uncut = 0;
  fGeneralMuonFinder4_uncut = 0;
  fGeneralMuonFinder5_uncut = 0;
  fGeneralMuonFinder6_uncut = 0;
  fGeneralSpecialFinder_uncut = 0;
  fGeneralSpecialFinderForward_uncut = 0;
  fGeneralSpecialFinderBarrel_uncut = 0;
  fGeneralSpecialFinderRear_uncut = 0;

  fGeneralPhiMUBAC_uncut = 0;
  fGeneralPhiMUBACForward_uncut = 0;
  fGeneralPhiMUBACBarrel_uncut = 0;
  fGeneralPhiMUBACRear_uncut = 0;
  fGeneralPhiBREMAT_uncut = 0;
  fGeneralPhiBREMATForward_uncut = 0;
  fGeneralPhiBREMATBarrel_uncut = 0;
  fGeneralPhiBREMATRear_uncut = 0;
  fGeneralPhiMPMATCH_uncut = 0;
  fGeneralPhiMPMATCHForward_uncut = 0;
  fGeneralPhiMPMATCHBarrel_uncut = 0;
  fGeneralPhiMPMATCHRear_uncut = 0;
  fGeneralPhiBREMATMUBAC_uncut = 0;
  fGeneralPhiBREMATMUBACForward_uncut = 0;
  fGeneralPhiBREMATMUBACBarrel_uncut = 0;
  fGeneralPhiBREMATMUBACRear_uncut = 0;
  fGeneralPhiMPMATCHMUBAC_uncut = 0;
  fGeneralPhiMPMATCHMUBACForward_uncut = 0;
  fGeneralPhiMPMATCHMUBACBarrel_uncut = 0;
  fGeneralPhiMPMATCHMUBACRear_uncut = 0;

  fGeneralPMCTRUE_uncut = 0;
  fGeneralPXMCTRUE_uncut = 0;
  fGeneralPYMCTRUE_uncut = 0;
  fGeneralPZMCTRUE_uncut = 0;
  fGeneralQuality_uncut = 0;
  fGeneralQualityAndTrue_uncut = 0;
  fGeneralQualityForward_uncut = 0;
  fGeneralQualityBarrel_uncut = 0;
  fGeneralQualityRear_uncut = 0;
  fGeneralPvsPMCTRUE_uncut = 0;
  fGeneralPXvsPXMCTRUE_uncut = 0;
  fGeneralPYvsPYMCTRUE_uncut = 0;
  fGeneralPZvsPZMCTRUE_uncut = 0;
  fGeneralPMCTRUEpos_uncut = 0;
  fGeneralPXMCTRUEpos_uncut = 0;
  fGeneralPYMCTRUEpos_uncut = 0;
  fGeneralPZMCTRUEpos_uncut = 0;
  fGeneralPvsPMCTRUEpos_uncut = 0;
  fGeneralPXvsPXMCTRUEpos_uncut = 0;
  fGeneralPYvsPYMCTRUEpos_uncut = 0;
  fGeneralPZvsPZMCTRUEpos_uncut = 0;
  fGeneralPMCTRUEneg_uncut = 0;
  fGeneralPXMCTRUEneg_uncut = 0;
  fGeneralPYMCTRUEneg_uncut = 0;
  fGeneralPZMCTRUEneg_uncut = 0;
  fGeneralPvsPMCTRUEneg_uncut = 0;
  fGeneralPXvsPXMCTRUEneg_uncut = 0;
  fGeneralPYvsPYMCTRUEneg_uncut = 0;
  fGeneralPZvsPZMCTRUEneg_uncut = 0;

  fGeneral2DBeamSpotImpactParameter_uncut = 0;
  fGeneral2DBeamSpotImpactSignificance_uncut = 0;
  fGeneral2DMCBeamSpotImpactParameter_uncut = 0;
  fGeneral2DTrueImpactParameter_uncut = 0;
  fGeneral2DMCTrueImpactParameter_uncut = 0;
  fGeneral2DTrueImpactParamaterRecVsTrue_uncut = 0;
  fGeneral2DBeamSpotImpactParamaterRecVsTrue_uncut = 0;
  fGeneralGMuonPVsZTTP_uncut = 0;

  // general plots
  fGeneralWeight = 0;
  fGeneralWeightForward = 0;
  fGeneralWeightBarrel = 0;
  fGeneralWeightRear = 0;
  fGeneralWeightMUBAC = 0;
  fGeneralWeightMUBACForward = 0;
  fGeneralWeightMUBACBarrel = 0;
  fGeneralWeightMUBACRear = 0;
  fGeneralWeightBREMAT = 0;
  fGeneralWeightBREMATForward = 0;
  fGeneralWeightBREMATBarrel = 0;
  fGeneralWeightBREMATRear = 0;
  fGeneralWeightMPMATCH = 0;
  fGeneralWeightMPMATCHForward = 0;
  fGeneralWeightMPMATCHBarrel = 0;
  fGeneralWeightMPMATCHRear = 0;
  fGeneralWeightBREMATMUBAC = 0;
  fGeneralWeightBREMATMUBACForward = 0;
  fGeneralWeightBREMATMUBACBarrel = 0;
  fGeneralWeightBREMATMUBACRear = 0;
  fGeneralWeightMPMATCHMUBAC = 0;
  fGeneralWeightMPMATCHMUBACForward = 0;
  fGeneralWeightMPMATCHMUBACBarrel = 0;
  fGeneralWeightMPMATCHMUBACRear = 0;
  fGeneralNMU = 0;
  fGeneralRegions = 0;
  fGeneralNMUForward = 0;
  fGeneralNMUBarrel = 0;
  fGeneralNMURear = 0;
  fGeneralProb = 0;
  fGeneralProbForward = 0;
  fGeneralProbBarrel = 0;
  fGeneralProbRear = 0;
  fGeneralP = 0;
  fGeneralPForward = 0;
  fGeneralPBarrel = 0;
  fGeneralPRear = 0;
  fGeneralPt = 0;
  fGeneralPtChosen = 0;
  fGeneralPtChosenFine2 = 0;
  fGeneralPtChosenFine4 = 0;
  fGeneralPtChosenFine8 = 0;
  fGeneralPtChosenFine16 = 0;
  fGeneralPtChosenMC = 0;
  fGeneralPtChosenFineMC = 0;
  fGeneralChosenIso01 = 0;
  fGeneralChosenIso02 = 0;
  fGeneralChosenIso03 = 0;
  fGeneralChosenIso04 = 0;
  fGeneralChosenIso05 = 0;
  fGeneralChosenIso06 = 0;
  fGeneralChosenIso07 = 0;
  fGeneralChosenIso08 = 0;
  fGeneralChosenIso09 = 0;
  fGeneralChosenIso10 = 0;
  fGeneralPtForward = 0;
  fGeneralPtBarrel = 0;
  fGeneralPtRear = 0;
  fGeneralPtSpecial = 0;
  fGeneralPtSpecialForward = 0;
  fGeneralPtSpecialBarrel = 0;
  fGeneralPtSpecialRear = 0;
  fGeneralPx = 0;
  fGeneralPxForward = 0;
  fGeneralPxBarrel = 0;
  fGeneralPxRear = 0;
  fGeneralPy = 0;
  fGeneralPyForward = 0;
  fGeneralPyBarrel = 0;
  fGeneralPyRear = 0;
  fGeneralPz = 0;
  fGeneralPzForward = 0;
  fGeneralPzBarrel = 0;
  fGeneralPzRear = 0;
  fGeneralPhi = 0;
  fGeneralPhiForward = 0;
  fGeneralPhiBarrel = 0;
  fGeneralPhiRear = 0;
  fGeneralTheta = 0;
  fGeneralThetaForward = 0;
  fGeneralThetaBarrel = 0;
  fGeneralThetaRear = 0;
  fGeneralEta = 0;
  fGeneralEtaChosen = 0;
  fGeneralEtaChosenLarge = 0;
  fGeneralEtaChosenMC = 0;
  fGeneralEtaChosenLargeMC = 0;
  fGeneralEtaForward = 0;
  fGeneralEtaBarrel = 0;
  fGeneralEtaRear = 0;
  fGeneralCharge = 0;
  fGeneralChargeForward = 0;
  fGeneralChargeBarrel = 0;
  fGeneralChargeRear = 0;
  fGeneralMuonFinder = 0;
  fGeneralMuonFinder4 = 0;
  fGeneralMuonFinder5 = 0;
  fGeneralMuonFinder6 = 0;
  fGeneralSpecialFinder = 0;
  fGeneralSpecialFinder4 = 0;
  fGeneralSpecialFinder5 = 0;
  fGeneralSpecialFinder6 = 0;
  fGeneralSpecialFinder4Forward = 0;
  fGeneralSpecialFinder5Forward = 0;
  fGeneralSpecialFinder6Forward = 0;
  fGeneralSpecialFinder4Barrel = 0;
  fGeneralSpecialFinder5Barrel = 0;
  fGeneralSpecialFinder6Barrel = 0;
  fGeneralSpecialFinder4Rear = 0;
  fGeneralSpecialFinder5Rear = 0;
  fGeneralSpecialFinder6Rear = 0;
  fGeneralSpecialFinderForward = 0;
  fGeneralSpecialFinderBarrel = 0;
  fGeneralSpecialFinderRear = 0;

  fGeneralCrossTotal = 0;
  fGeneralCrossTotalRecNTrue = 0;
  fGeneralCrossTotalMuChamber = 0;
  fGeneralCrossTotalMuChamberRecNTrue = 0;
  fGeneralCrossTotalBAC = 0;
  fGeneralCrossTotalBACRecNTrue = 0;

  fGeneralCrossRegions = 0;
  fGeneralCrossRegionsRecNTrue = 0;
  fGeneralCrossFinder = 0;
  fGeneralCrossFinderRecNTrue = 0;

  fGeneralCrossPt = 0;
  fGeneralCrossPtRecNTrue = 0;

  fGeneralCrossEta = 0;
  fGeneralCrossEtaRecNTrue = 0;

  fGeneralCrossPtFine = 0;
  fGeneralCrossPtFineRecNTrue = 0;

  fGeneralCrossEtaFine = 0;
  fGeneralCrossEtaFineRecNTrue = 0;

  fGeneralCrossPtMassimo = 0;
  fGeneralCrossPtMassimoRecNTrue = 0;

  fGeneralCrossEtaMassimo = 0;
  fGeneralCrossEtaMassimoRecNTrue = 0;

  fGeneralPhiMUBAC = 0;
  fGeneralPhiMUBACForward = 0;
  fGeneralPhiMUBACBarrel = 0;
  fGeneralPhiMUBACRear = 0;
  fGeneralPhiBREMAT = 0;
  fGeneralPhiBREMATForward = 0;
  fGeneralPhiBREMATBarrel = 0;
  fGeneralPhiBREMATRear = 0;
  fGeneralPhiMPMATCH = 0;
  fGeneralPhiMPMATCHForward = 0;
  fGeneralPhiMPMATCHBarrel = 0;
  fGeneralPhiMPMATCHRear = 0;
  fGeneralPhiBREMATMUBAC = 0;
  fGeneralPhiBREMATMUBACForward = 0;
  fGeneralPhiBREMATMUBACBarrel = 0;
  fGeneralPhiBREMATMUBACRear = 0;
  fGeneralPhiMPMATCHMUBAC = 0;
  fGeneralPhiMPMATCHMUBACForward = 0;
  fGeneralPhiMPMATCHMUBACBarrel = 0;
  fGeneralPhiMPMATCHMUBACRear = 0;

  fGeneralQuality = 0;
  fGeneralQualityAndTrue = 0;
  fGeneralQualityForward = 0;
  fGeneralQualityBarrel = 0;
  fGeneralQualityRear = 0;

  fGeneralPMCTRUE = 0;
  fGeneralPXMCTRUE = 0;
  fGeneralPYMCTRUE = 0;
  fGeneralPZMCTRUE = 0;
  fGeneralPvsPMCTRUE = 0;
  fGeneralPXvsPXMCTRUE = 0;
  fGeneralPYvsPYMCTRUE = 0;
  fGeneralPZvsPZMCTRUE = 0;
  fGeneralPMCTRUEpos = 0;
  fGeneralPXMCTRUEpos = 0;
  fGeneralPYMCTRUEpos = 0;
  fGeneralPZMCTRUEpos = 0;
  fGeneralPvsPMCTRUEpos = 0;
  fGeneralPXvsPXMCTRUEpos = 0;
  fGeneralPYvsPYMCTRUEpos = 0;
  fGeneralPZvsPZMCTRUEpos = 0;
  fGeneralPMCTRUEneg = 0;
  fGeneralPXMCTRUEneg = 0;
  fGeneralPYMCTRUEneg = 0;
  fGeneralPZMCTRUEneg = 0;
  fGeneralPvsPMCTRUEneg = 0;
  fGeneralPXvsPXMCTRUEneg = 0;
  fGeneralPYvsPYMCTRUEneg = 0;
  fGeneralPZvsPZMCTRUEneg = 0;

  fGeneral2DBeamSpotImpactParameter = 0;
  fGeneral2DBeamSpotImpactParameter_Mirrored = 0;
  fGeneral2DBeamSpotImpactSignificance = 0;
  fGeneral2DMCBeamSpotImpactParameter = 0;
  fGeneral2DTrueImpactParameter = 0;
  fGeneral2DMCTrueImpactParameter = 0;
  fGeneral2DTrueImpactParamaterRecVsTrue = 0;
  fGeneral2DBeamSpotImpactParamaterRecVsTrue = 0;
  fGeneralGMuonPVsZTTP = 0;

  //fakemuon plots
  fPt_fakebin = 0;
  fEta_lowPt_fakebin = 0;
  fEta_highPt_fakebin = 0;
  fPhi_lowPt_fakebin = 0;
  fPhi_highPt_fakebin = 0;

  //fakemuon plots
  fMuonProbabilityAllPt         = 0;
  fMuonProbabilityAllEta_lowPt  = 0;
  fMuonProbabilityAllPhi_lowPt  = 0;
  fMuonProbabilityAllEta_highPt = 0;
  fMuonProbabilityAllPhi_highPt = 0;
  
  fRecTrueMuonMother     = 0;
  fFakePxvsPxMCTRUE      = 0;
  fFakePyvsPyMCTRUE      = 0;
  fFakePzvsPzMCTRUE      = 0;
  fFakePtvsPtMCTRUE      = 0;
  fFakeEtavsEtaMCTRUE    = 0;

  fFakeMuonAllPt         = 0;            
  fFakeMuonAllPhi_lowPt  = 0;            
  fFakeMuonAllEta_lowPt  = 0;           
  fFakeMuonAllPhi_highPt = 0;           
  fFakeMuonAllEta_highPt = 0;           

 fFakeMuonKaonPt         = 0;            
 fFakeMuonKaonPhi_lowPt  = 0;            
 fFakeMuonKaonEta_lowPt  = 0;           
 fFakeMuonKaonPhi_highPt = 0;           
 fFakeMuonKaonEta_highPt = 0;           
 fFakeMuonPionPt         = 0;           
 fFakeMuonPionEta_lowPt  = 0;           
 fFakeMuonPionPhi_lowPt  = 0;           
 fFakeMuonPionEta_highPt = 0;           
 fFakeMuonPionPhi_highPt = 0;           
 
 fFakeDecayMuonPt         = 0;            
 fFakeDecayMuonPhi_lowPt  = 0;            
 fFakeDecayMuonEta_lowPt  = 0;           
 fFakeDecayMuonPhi_highPt = 0;           
 fFakeDecayMuonEta_highPt = 0;           
 
 fFakeDecayMuonKaonPt         = 0;            
 fFakeDecayMuonKaonPhi_lowPt  = 0;            
 fFakeDecayMuonKaonEta_lowPt  = 0;           
 fFakeDecayMuonKaonPhi_highPt = 0;           
 fFakeDecayMuonKaonEta_highPt = 0;           
 fFakeDecayMuonPionPt         = 0;           
 fFakeDecayMuonPionEta_lowPt  = 0;           
 fFakeDecayMuonPionPhi_lowPt  = 0;           
 fFakeDecayMuonPionEta_highPt = 0;           
 fFakeDecayMuonPionPhi_highPt = 0;           
 
 fFakePunchMuonPt         = 0;            
 fFakePunchMuonPhi_lowPt  = 0;            
 fFakePunchMuonEta_lowPt  = 0;           
 fFakePunchMuonPhi_highPt = 0;           
 fFakePunchMuonEta_highPt = 0;           
 fFakePunchMuonKaonPt         = 0;            
 fFakePunchMuonKaonPhi_lowPt  = 0;            
 fFakePunchMuonKaonEta_lowPt  = 0;           
 fFakePunchMuonKaonPhi_highPt = 0;           
 fFakePunchMuonKaonEta_highPt = 0;           
 fFakePunchMuonPionPt         = 0;           
 fFakePunchMuonPionEta_lowPt  = 0;           
 fFakePunchMuonPionPhi_lowPt  = 0;           
 fFakePunchMuonPionEta_highPt = 0;           
 fFakePunchMuonPionPhi_highPt = 0;           
// probability plots that reconstr. track is a fake muon from decays)
 fMuonDecayProbabilityAllPt = 0;        
 fMuonDecayProbabilityAllEta_lowPt = 0;
 fMuonDecayProbabilityAllPhi_lowPt = 0;
 fMuonDecayProbabilityAllEta_highPt = 0;
 fMuonDecayProbabilityAllPhi_highPt = 0;
 fMuonDecayPionProbabilityAllPt = 0;        
 fMuonDecayPionProbabilityAllEta_lowPt = 0;
 fMuonDecayPionProbabilityAllPhi_lowPt = 0;
 fMuonDecayPionProbabilityAllEta_highPt = 0;
 fMuonDecayPionProbabilityAllPhi_highPt = 0;
 fMuonDecayKaonProbabilityAllPt = 0;        
 fMuonDecayKaonProbabilityAllEta_lowPt = 0;
 fMuonDecayKaonProbabilityAllPhi_lowPt = 0;
 fMuonDecayKaonProbabilityAllEta_highPt = 0;
 fMuonDecayKaonProbabilityAllPhi_highPt = 0;
 // probability plots that reconstr. track is a fake muon from punch trough)
 fMuonPunchProbabilityAllPt = 0;        
 fMuonPunchProbabilityAllEta_lowPt = 0;
 fMuonPunchProbabilityAllPhi_lowPt = 0;
 fMuonPunchProbabilityAllEta_highPt = 0;
 fMuonPunchProbabilityAllPhi_highPt = 0;
 fMuonPunchPionProbabilityAllPt = 0;        
 fMuonPunchPionProbabilityAllEta_lowPt = 0;
 fMuonPunchPionProbabilityAllPhi_lowPt = 0;
 fMuonPunchPionProbabilityAllEta_highPt = 0;
 fMuonPunchPionProbabilityAllPhi_highPt = 0;
 fMuonPunchKaonProbabilityAllPt = 0;        
 fMuonPunchKaonProbabilityAllEta_lowPt = 0;
 fMuonPunchKaonProbabilityAllPhi_lowPt = 0;
 fMuonPunchKaonProbabilityAllEta_highPt = 0;
 fMuonPunchKaonProbabilityAllPhi_highPt = 0;
 fFakePionProbabilityAllPt = 0;        
 fFakePionProbabilityAllEta_lowPt= 0;        
 fFakePionProbabilityAllPhi_lowPt= 0;        
 fFakePionProbabilityAllEta_highPt= 0;        
 fFakePionProbabilityAllPhi_highPt = 0;        
// probability plots for fake muons from kaon (punch & decay)
 fFakeKaonProbabilityAllPt = 0;       
 fFakeKaonProbabilityAllEta_lowPt = 0;        
 fFakeKaonProbabilityAllPhi_lowPt= 0;        
 fFakeKaonProbabilityAllEta_highPt = 0;        
 fFakeKaonProbabilityAllPhi_highPt = 0;        

 fPrec_PtruevsDecdistPion_rear    = 0;
 fPrec_PtruevsDecdistPion_central = 0;
 fPrec_PtruevsDecdistPion_forward = 0;  
 fPrec_PtruevsDecdistKaon_rear    = 0;
 fPrec_PtruevsDecdistKaon_central = 0;
 fPrec_PtruevsDecdistKaon_forward = 0;  
 fPrec_PtruevsDecdistMuon_rear    = 0;
 fPrec_PtruevsDecdistMuon_central = 0;
 fPrec_PtruevsDecdistMuon_forward = 0;  

 fFake2DMuonAll_PtEta             = 0;
 fFake2DMuonDecay_PtEta           = 0;
 fFake2DMuonPunch_PtEta           = 0;
 fProbability2DMuonAll_PtEta      = 0;
 fProbability2DMuonDecay_PtEta    = 0;
 fProbability2DMuonPunch_PtEta    = 0;
 fFake2DMuonAll_PtEta_Bremat      = 0;
 fFake2DMuonAll_PtEta_MPMatch     = 0;
 fFake2DMuonAll_PtEta_Bac         = 0;
 fFake2DProbMuonAll_PtEta_Bremat  = 0;
 fFake2DProbMuonAll_PtEta_MPMatch = 0;
 fFake2DProbMuonAll_PtEta_Bac     = 0;
 fFake2DMuonAll_PtEta             = 0;
 

  // initialize control plots

  // uncut control plots
  fControlProb_uncut = 0;
  fControlEta_uncut = 0;
  fControlP_uncut = 0;
  fControlPt_uncut = 0;
  fControlChFlg_uncut = 0;
  fControlMuonFinder_uncut = 0;
  fControlMuonMfpro_uncut = 0;
  fControlMuonMfndf_uncut = 0;
  fControlMuonMfz_uncut = 0;
  fControlQuality_uncut = 0;
  fControlWeight_uncut = 0;

  // control plots
  fControlProbForward = 0;
  fControlProbBarrel = 0;
  fControlProbRear = 0;
  fControlEtaForward = 0;
  fControlEtaBarrel = 0;
  fControlEtaRear = 0;
  fControlPForward = 0;
  fControlPBarrel = 0;
  fControlPRear = 0;
  fControlPtForward = 0;
  fControlPtBarrel = 0;
  fControlPtRear = 0;
  fControlChFlgForward = 0;
  fControlChFlgBarrel = 0;
  fControlChFlgRear = 0;
  fControlMuonFinderForward = 0;
  fControlMuonFinderBarrel = 0;
  fControlMuonFinderRear = 0;
  fControlMuonMfproForward = 0;
  fControlMuonMfproBarrel = 0;
  fControlMuonMfproRear = 0;
  fControlMuonMfndfForward = 0;
  fControlMuonMfndfBarrel = 0;
  fControlMuonMfndfRear = 0;
  fControlMuonMfzForward = 0;
  fControlMuonMfzBarrel = 0;
  fControlMuonMfzRear = 0;
  fControlQualityForward = 0;
  fControlQualityBarrel = 0;
  fControlQualityRear = 0;
  fControlWeight = 0;

  // create histograms
  fOK = CreateHistograms();

  // initialize muon efficiency object
  fMuonEfficiency = new GMuonEfficiency();
  fOK = fMuonEfficiency->IsOK();

  // instanciate random number generator
  randgen = new TRandom();

}

//_____________________________________________________________

GMuons::~GMuons() {
  //
  // GMuons default destructor
  if ( gDebug ) cout << endl << "GMuons::~GMuons dtor called" << endl << endl;

  // delete clonesarray
  fMuons->Delete();
  delete fMuons;

  if(randgen){
    randgen->Delete();
    delete randgen;
  }

}

//_____________________________________________________________

Bool_t GMuons::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GMuons::Do() called" << endl << endl;

  // fill clonesarray
  Fill();

  // count muons
  CountMuons();
  // check if muon with glomu in event
  CheckGlomu();
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMuons::Reset() {
  //
  // reset object on event by event basis 
  if ( gDebug ) cout << endl << "GMuons::Reset() called" << endl << endl;

  // reset muon counters
  fBarrelMuons     = 0;
  fForwardMuons    = 0;
  fRearMuons       = 0;
  fGlomus          = kFALSE;   
  // reset cut flags
  fMuonsCut = 0;
  fMuonsMinIsolation10Veto = kFALSE;

  // reset clonesarray
  fMuons->Clear();
  fNMuons = 0;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::GetAllCuts() {
  //
  // returns flag for physics object if event passes all object cuts
  if ( gDebug ) cout << endl << "GMuons::GetAllCuts() called" << endl << endl;
  
  Bool_t returny = kFALSE;

  // if one good muon veto event
  if ( fMuonsMinIsolation10Veto )
    return kFALSE;

  // if enough muons have been found
  if ( GetMuonsCut() >= gCards->GetMUONNCut() )
    returny = kTRUE;

  return returny;
}

//_____________________________________________________________

GMuon* GMuons::GetMuon(Int_t index) {
  //
  // returns muon object for index
  if ( gDebug ) cout << endl << "GMuons::GetMuon called" << endl << endl;
  
  if ( index < fNMuons ) {
    return ((GMuon*)(fMuons->At(index)));
  } else {
    TString msg = "GMuons::GetMuon: requested muon index: ";
    msg += index;
    msg.Append("is larger that total number of muons: ");
    msg += fNMuons;
    gLister->FillErrorList(msg.Data());
    return 0;
  }

}

//_____________________________________________________________

Bool_t GMuons::CountMuons() {
  //
  // count found muons in different sections
  // count also muons which pass MVCuts if muon efficiency calculation is activated
  if ( gDebug ) cout << endl << "GMuons::CountMuons called" << endl << endl;

  for ( Int_t i = 0; i < fNMuons; i++ ) {
    GMuon * muon = (GMuon*)fMuons->At(i);
    if ( muon->GetType() == kBarrel ) {
      if ( gCards->GetDoEfficiency() ) {
	if ( muon->GetAllCuts() || muon->GetMVCuts() ) {
	  fBarrelMuons++;
	  fMuonsCut += 1;
	}
      } else {
	if ( muon->GetAllCuts() ) {
	  fBarrelMuons++;
	  fMuonsCut += 1;
	}
      }
    } else if ( muon->GetType() == kRear ) {
      if ( gCards->GetDoEfficiency() ) {
	if ( muon->GetAllCuts() || muon->GetMVCuts() ) {
	  fRearMuons++;
	  fMuonsCut += 1;
	}
      } else {
	if ( muon->GetAllCuts() ) {
	  fRearMuons++;
	  fMuonsCut += 1;
	}
      }
    } else if ( muon->GetType() == kForward ) {
      if ( gCards->GetDoEfficiency() ) {
	if ( muon->GetAllCuts() || muon->GetMVCuts() ) {
	  fForwardMuons++;
	  fMuonsCut += 1;
	}
      } else {
	if ( muon->GetAllCuts() ) {
	  fForwardMuons++;
	  fMuonsCut += 1;
	}
      }
    }
  }

  return kTRUE;
}
//____________________________________________________________________

Bool_t GMuons::CheckGlomu(){
  if (gDebug) cout << endl << "GMuons::CheckGlomu() called " << endl << endl;

  for ( Int_t i = 0; i < fNMuons; i++ ) {
    GMuon * muon = (GMuon*)fMuons->At(i);
    
    if (muon->GetGlomuID()>0) fGlomus = kTRUE;
  }
  return kTRUE;
}

//_____________________________________________________________

TString GMuons::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GMuonss::PrintMessage() called" << endl << endl;

  TString dummy = "Muons:\n\n";

  GMuon *muon = 0;

  for ( Int_t i = 0; i < fNMuons; i++ ) {
    muon = ((GMuon*)(fMuons->At(i)));
    dummy.Append(muon->PrintMessage(option));
  }


  return dummy;
}

//_____________________________________________________________

Bool_t GMuons::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMuons::Print() called" << endl << endl;

  option.ToUpper();

  GMuon *muon = 0;

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("MUONS") || option.Contains("ALL") ) {
      gLister->FillOutputList("Muons:\n\n");
      for ( Int_t i = 0; i < fNMuons; i++ ) {
	muon = ((GMuon*)(fMuons->At(i)));
	muon->Print(option);
      }
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "Muons:" << endl << endl;
    for ( Int_t i = 0; i < fNMuons; i++ ) {
      muon = ((GMuon*)(fMuons->At(i)));
      muon->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CreateGeneral() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GMuons::CreateGeneral() called" << endl << endl;

  if ( gCards->GetMUONGeneral() ) {

    Int_t    weightbins = 100;
    Double_t weightlow  = 0.0;
    Double_t weighthigh = 10.0;
    Int_t    qualitybins = 7;
    Double_t qualitylow  = 0.;
    Double_t qualityhigh = 7.;
    Int_t nmubins = 10;
    Double_t nmulow = 0.;
    Double_t nmuhigh = 10.;
    Int_t probbins = 100;
    Double_t problow = 0.;
    Double_t probhigh = 1.;
    Int_t pbins = 15;
    Double_t plow = 0.;
    Double_t phigh = 15.;
    Int_t pspecialbins = 30;
    Double_t pspeciallow = 0.;
    Double_t pspecialhigh = 15.;
    Int_t ptbins = 14;
    Double_t ptlow = 0.5;
    Double_t pthigh = 14.5;

    Int_t ptfine2bins = 30;
    Double_t ptfine2low = 0.;
    Double_t ptfine2high = 15.;
    Int_t ptfine4bins = 60;
    Double_t ptfine4low = 0.;
    Double_t ptfine4high = 15.;
    Int_t ptfine8bins = 120;
    Double_t ptfine8low = 0.;
    Double_t ptfine8high = 15.;
    Int_t ptfine16bins = 240;
    Double_t ptfine16low = 0.;
    Double_t ptfine16high = 15.;

    Int_t ptspecialbins = 150;
    Double_t ptspeciallow = 0.;
    Double_t ptspecialhigh = 15.;
    Int_t pxbins = 30;
    Double_t pxlow = -15.;
    Double_t pxhigh = 15.;
    Int_t pybins = 30;
    Double_t pylow = -15.;
    Double_t pyhigh = 15.;
    Int_t pzbins = 30;
    Double_t pzlow = -15.;
    Double_t pzhigh = 15.;
    Int_t pxspecialbins = 300;
    Double_t pxspeciallow = -15.;
    Double_t pxspecialhigh = 15.;
    Int_t pyspecialbins = 300;
    Double_t pyspeciallow = -15.;
    Double_t pyspecialhigh = 15.;
    Int_t pzspecialbins = 300;
    Double_t pzspeciallow = -15.;
    Double_t pzspecialhigh = 15.;
    Int_t phibins = 72;
    Double_t philow = -TMath::Pi();
    Double_t phihigh = TMath::Pi();
    Int_t thetabins = 36;
    Double_t thetalow = 0.;
    Double_t thetahigh = TMath::Pi();
    Int_t etabins = 23;
    Double_t etalow = -2.0;
    Double_t etahigh = 2.6;
    Int_t etalargebins = 40;
    Double_t etalargelow = -4.0;
    Double_t etalargehigh = 4.0;
    Int_t chargebins = 3;
    Double_t chargelow = -1.5;
    Double_t chargehigh = 1.5;
    TString  muonfinder  = "Glomu,Bremat,BacMat,MuBac,Mamma,MPMatch,Mufo,Mip,Mv";
    //   TString  muonfinder  = "Glomu,Bremat,MuBac,Mamma,MPMatch,Mufo,Mip,Mv";
    Int_t impact2Dbins = 20;
    Double_t impact2Dlow = -0.1;
    Double_t impact2Dhigh = 0.1;
    Int_t signi2Dbins = 60;
    Double_t signi2Dlow = -30.;
    Double_t signi2Dhigh = 30.;
    Int_t mcimpact2Dbins = 40;
    Double_t mcimpact2Dlow =  0.0;
    Double_t mcimpact2Dhigh = 0.2;
    Int_t    iso01bins = 250;
    Double_t iso01low  = 0.;
    Double_t iso01high = 25.;
    Int_t    iso02bins = 250;
    Double_t iso02low  = 0.;
    Double_t iso02high = 25.;
    Int_t    iso03bins = 250;
    Double_t iso03low  = 0.;
    Double_t iso03high = 25.;
    Int_t    iso04bins = 250;
    Double_t iso04low  = 0.;
    Double_t iso04high = 25.;
    Int_t    iso05bins = 250;
    Double_t iso05low  = 0.;
    Double_t iso05high = 25.;
    Int_t    iso06bins = 250;
    Double_t iso06low  = 0.;
    Double_t iso06high = 25.;
    Int_t    iso07bins = 250;
    Double_t iso07low  = 0.;
    Double_t iso07high = 25.;
    Int_t    iso08bins = 250;
    Double_t iso08low  = 0.;
    Double_t iso08high = 25.;
    Int_t    iso09bins = 250;
    Double_t iso09low  = 0.;
    Double_t iso09high = 25.;
    Int_t    iso10bins = 250;
    Double_t iso10low  = 0.;
    Double_t iso10high = 25.;

    Int_t    regionbins = 3;
    Double_t regionlow  = 0.;
    Double_t regionhigh = 3.;

    Int_t    crosstotalbins = 1;
    Double_t crosstotallow  = 0.;
    Double_t crosstotalhigh = 1.;

    Int_t    crossregionbins = 3;
    Double_t crossregionlow  = 0.;
    Double_t crossregionhigh = 3.;

    Int_t    crosspt_nbins = 4;
    Double_t *crosspt_bins = new Double_t[crosspt_nbins+1];
    crosspt_bins[0] = 1.5;
    crosspt_bins[1] = 3.0;
    crosspt_bins[2] = 5.0;
    crosspt_bins[3] = 7.5;
    crosspt_bins[4] = 11.0;

    Int_t    crosseta_nbins = 4;
    Double_t *crosseta_bins = new Double_t[crosseta_nbins+1];
    crosseta_bins[0]  = -2.0;
    crosseta_bins[1]  = -0.9;
    crosseta_bins[2]  =  0.0;
    crosseta_bins[3]  =  1.2;
    crosseta_bins[4]  =  2.5;

    Int_t    crossptfine_nbins = 8;
    Double_t *crossptfine_bins = new Double_t[crossptfine_nbins+1];
    crossptfine_bins[0]  =  1.5;
    crossptfine_bins[1]  =  2.5;
    crossptfine_bins[2]  =  3.5;
    crossptfine_bins[3]  =  4.5;
    crossptfine_bins[4]  =  5.5;
    crossptfine_bins[5]  =  6.5;
    crossptfine_bins[6]  =  7.5;
    crossptfine_bins[7]  =  8.5;
    crossptfine_bins[8]  = 11.5;

    Int_t    crossetafine_nbins = 8;
    Double_t *crossetafine_bins = new Double_t[crossetafine_nbins+1];
    crossetafine_bins[0]  = -1.5;
    crossetafine_bins[1]  = -1.0;
    crossetafine_bins[2]  = -0.50;
    crossetafine_bins[3]  = 0.0;
    crossetafine_bins[4]  = 0.50;
    crossetafine_bins[5]  = 1.0;
    crossetafine_bins[6] =  1.50;
    crossetafine_bins[7] =  2.0;
    crossetafine_bins[8] =  2.50;

    Int_t    crossptmassimo_nbins = 3;
    Double_t *crossptmassimo_bins = new Double_t[crossptmassimo_nbins+1];
    crossptmassimo_bins[0]  =  2.5;
    crossptmassimo_bins[1]  =  4.0;
    crossptmassimo_bins[2]  =  6.0;
    crossptmassimo_bins[3]  = 10.0;

    Int_t    crossetamassimo_nbins = 4;
    Double_t *crossetamassimo_bins = new Double_t[crossetamassimo_nbins+1];
    crossetamassimo_bins[0] = -1.6;
    crossetamassimo_bins[1] = -0.75;
    crossetamassimo_bins[2] = 0.25;
    crossetamassimo_bins[3] = 1.3;
    crossetamassimo_bins[4] = 2.3;

    // special finder bins
    // 0: barrel bremat plus (mubac and not mv)
    // 1: barrel bremat plus (mubac and mv)
    // 2: barrel bremat plus not mubac
    // 3: barrel not bremat plus (mubac and not mv)
    // 4: barrel not bremat plus (mubac and mv)
    // 5: rear bremat plus (mubac and not mv)
    // 6: rear bremat plus (mubac and mv)
    // 7: rear bremat plus not mubac
    // 8: rear not bremat plus  (mubac and not mv)
    // 9: rear not bremat plus (mubac and mv)
    // 10: forward mpmatch or mufo plus (mubac and not mv)
    // 11: forward mpmatch or mufo plus (mubac and mv)
    // 12: forward mpmatch or mufo plus not mubac
    // 13: forward not mpmatch or mufo plus (mubac and not mv)
    // 14: forward not mpmatch or mufo plus (mubac and mv)
    Int_t    specialfinderbins = 18;
    Double_t specialfinderlow  = 0.;
    Double_t specialfinderhigh = 18.;

    // special finder bins for quality 6
    // 0: bremat
    // 1: mpmatch prob > 0.05
    // 2: mufo prob > 0.05
    // 3: mpmatch prob <= 0.05
    // 4: mufo prob < 0.05
    Int_t    specialfinder6bins = 5;
    Double_t specialfinder6low  = 0.;
    Double_t specialfinder6high = 5.;

    // special finder bins for quality 5
    // 0: mpmatch
    // 1: mufo
    // 2: mamma
    // 3: bremat
    // 4: MV + Mubac
    Int_t    specialfinder5bins = 5;
    Double_t specialfinder5low  = 0.;
    Double_t specialfinder5high = 5.;

    // special finder bins for quality 4
    // 0: bremat
    // 1: mufo
    // 2: mamma
    // 3: mubac
    // 4: mv but not mpmatch or mufo
    // 5: mubac, glomu
    // 6: mubac, mv
    // 7: mubac, mip
    Int_t    specialfinder4bins = 8;
    Double_t specialfinder4low  = 0.;
    Double_t specialfinder4high = 8.;

    // general uncut plots
    fGeneralWeight_uncut = gHistogrammer->TH1DFactory("Muons","Weight_uncut","uncut weight of #mu",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightForward_uncut = gHistogrammer->TH1DFactory("Muons","WeightForward_uncut","uncut weight of forward #mu",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightBarrel_uncut = gHistogrammer->TH1DFactory("Muons","WeightBarrel_uncut","uncut weight of barrel #mu",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightRear_uncut = gHistogrammer->TH1DFactory("Muons","WeightRear_uncut","uncut weight of rear #mu",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightMUBAC_uncut = gHistogrammer->TH1DFactory("Muons","WeightMUBAC_uncut","uncut weight of #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightMUBACForward_uncut = gHistogrammer->TH1DFactory("Muons","WeightMUBACForward_uncut","uncut weight of forward #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightMUBACBarrel_uncut = gHistogrammer->TH1DFactory("Muons","WeightMUBACBarrel_uncut","uncut weight of barrel #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightMUBACRear_uncut = gHistogrammer->TH1DFactory("Muons","WeightMUBACRear_uncut","uncut weight of rear #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightBREMAT_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMAT_uncut","uncut weight of #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightBREMATForward_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATForward_uncut","uncut weight of forward #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightBREMATBarrel_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATBarrel_uncut","uncut weight of barrel #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightBREMATRear_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATRear_uncut","uncut weight of rear #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightMPMATCH_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCH_uncut","uncut weight of #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightMPMATCHForward_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHForward_uncut","uncut weight of forward #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightMPMATCHBarrel_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHBarrel_uncut","uncut weight of barrel #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightMPMATCHRear_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHRear_uncut","uncut weight of rear #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightBREMATMUBAC_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBAC_uncut","uncut weight of #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightBREMATMUBACForward_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBACForward_uncut","uncut weight of forward #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightBREMATMUBACBarrel_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBACBarrel_uncut","uncut weight of barrel #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightBREMATMUBACRear_uncut = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBACRear_uncut","uncut weight of rear #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightMPMATCHMUBAC_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBAC_uncut","uncut weight of #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightMPMATCHMUBACForward_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBACForward_uncut","uncut weight of forward #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightMPMATCHMUBACBarrel_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBACBarrel_uncut","uncut weight of barrel #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightMPMATCHMUBACRear_uncut = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBACRear_uncut","uncut weight of rear #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");

    fGeneralNMU_uncut = gHistogrammer->TH1DFactory("Muons","NMU_uncut","uncut number of: #mu",nmubins,nmulow,nmuhigh,"number of #mu","Events");
    fGeneralRegions_uncut = gHistogrammer->TH1DFactory("Muons","Regions_uncut","uncut #mu regions",regionbins,regionlow,regionhigh,"#mu region","Events");
    fGeneralProb_uncut = gHistogrammer->TH1DFactory("Muons","Prob_uncut","uncut #mu probability distribution",probbins,problow,probhigh,"#mu probability","Events");
    fGeneralP_uncut = gHistogrammer->TH1DFactory("Muons","P_uncut","uncut #mu momentum",pspecialbins,pspeciallow,pspecialhigh,"p_{#mu} [GeV]","Events");
    fGeneralPt_uncut = gHistogrammer->TH1DFactory("Muons","Pt_uncut","uncut transverse #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtSpecial_uncut = gHistogrammer->TH1DFactory("Muons","PtSpecial_uncut","uncut transverse #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPx_uncut = gHistogrammer->TH1DFactory("Muons","Px_uncut","uncut #mu x-momentum",pxspecialbins,pxspeciallow,pxspecialhigh,"p^{#mu}_{x} [GeV]","Events");
    fGeneralPy_uncut = gHistogrammer->TH1DFactory("Muons","Py_uncut","uncut #mu y-momentum",pyspecialbins,pyspeciallow,pyspecialhigh,"p^{#mu}_{y} [GeV]","Events");
    fGeneralPz_uncut = gHistogrammer->TH1DFactory("Muons","Pz_uncut","uncut #mu z-momentum",pzspecialbins,pzspeciallow,pzspecialhigh,"p^{#mu}_{z} [GeV]","Events");
    fGeneralPhi_uncut = gHistogrammer->TH1DFactory("Muons","Phi_uncut","uncut #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralTheta_uncut = gHistogrammer->TH1DFactory("Muons","Theta_uncut","uncut #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu}","Events");
    fGeneralEta_uncut = gHistogrammer->TH1DFactory("Muons","Eta_uncut","uncut #mu #eta-distribution",etalargebins,etalargelow,etalargehigh,"#eta_{#mu}","Events");
    fGeneralCharge_uncut = gHistogrammer->TH1DFactory("Muons","Charge_uncut","uncut #mu charge distribution",chargebins,chargelow,chargehigh,"#mu charge","Events");

    fGeneralNMUForward_uncut = gHistogrammer->TH1DFactory("Muons","NMUForward_uncut","uncut number of: forward #mu",nmubins,nmulow,nmuhigh,"number of forward #mu","Events");
    fGeneralProbForward_uncut = gHistogrammer->TH1DFactory("Muons","ProbForward_uncut","uncut forward #mu probability distribution",probbins,problow,probhigh,"forward #mu probability","Events");
    fGeneralPForward_uncut = gHistogrammer->TH1DFactory("Muons","PForward_uncut","uncut forward #mu momentum",pbins,plow,phigh,"p_{#mu,forward} [GeV]","Events");
    fGeneralPtForward_uncut = gHistogrammer->TH1DFactory("Muons","PtForward_uncut","uncut transverse forward #mu momentum",ptbins,ptlow,pthigh,"p^{#mu,forward}_{T} [GeV]","Events");
    fGeneralPtSpecialForward_uncut = gHistogrammer->TH1DFactory("Muons","PtSpecialForward_uncut","uncut transverse forward #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu,forward}_{T} [GeV]","Events");
    fGeneralPxForward_uncut = gHistogrammer->TH1DFactory("Muons","PxForward_uncut","uncut forward #mu x-momentum",pxbins,pxlow,pxhigh,"p^{#mu,forward}_{x} [GeV]","Events");
    fGeneralPyForward_uncut = gHistogrammer->TH1DFactory("Muons","PyForward_uncut","uncut forward #mu y-momentum",pybins,pylow,pyhigh,"p^{#mu,forward}_{y} [GeV]","Events");
    fGeneralPzForward_uncut = gHistogrammer->TH1DFactory("Muons","PzForward_uncut","uncut forward #mu z-momentum",pzbins,pzlow,pzhigh,"p^{#mu,forward}_{z} [GeV]","Events");
    fGeneralPhiForward_uncut = gHistogrammer->TH1DFactory("Muons","PhiForward_uncut","uncut forward #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralThetaForward_uncut = gHistogrammer->TH1DFactory("Muons","ThetaForward_uncut","uncut forward #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu,forward}","Events");
    fGeneralEtaForward_uncut = gHistogrammer->TH1DFactory("Muons","EtaForward_uncut","uncut forward #mu #eta-distribution",etalargebins,etalargelow,etalargehigh,"#eta_{#mu,forward}","Events");
    fGeneralChargeForward_uncut = gHistogrammer->TH1DFactory("Muons","ChargeForward_uncut","uncut forward #mu charge distribution",chargebins,chargelow,chargehigh,"forward #mu charge","Events");

    fGeneralNMUBarrel_uncut = gHistogrammer->TH1DFactory("Muons","NMUBarrel_uncut","uncut number of: barrel #mu",nmubins,nmulow,nmuhigh,"number of barrel #mu","Events");
    fGeneralProbBarrel_uncut = gHistogrammer->TH1DFactory("Muons","ProbBarrel_uncut","uncut barrel #mu probability distribution",probbins,problow,probhigh,"barrel #mu probability","Events");
    fGeneralPBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PBarrel_uncut","uncut barrel #mu momentum",pbins,plow,phigh,"p_{#mu,barrel} [GeV]","Events");
    fGeneralPtBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PtBarrel_uncut","uncut transverse barrel #mu momentum",ptbins,ptlow,pthigh,"p^{#mu,barrel}_{T} [GeV]","Events");
    fGeneralPtSpecialBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PtSpecialBarrel_uncut","uncut transverse barrel #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu,barrel}_{T} [GeV]","Events");
    fGeneralPxBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PxBarrel_uncut","uncut barrel #mu x-momentum",pxbins,pxlow,pxhigh,"p^{#mu,barrel}_{x} [GeV]","Events");
    fGeneralPyBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PyBarrel_uncut","uncut barrel #mu y-momentum",pybins,pylow,pyhigh,"p^{#mu,barrel}_{y} [GeV]","Events");
    fGeneralPzBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PzBarrel_uncut","uncut barrel #mu z-momentum",pzbins,pzlow,pzhigh,"p^{#mu,barrel}_{z} [GeV]","Events");
    fGeneralPhiBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PhiBarrel_uncut","uncut barrel #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralThetaBarrel_uncut = gHistogrammer->TH1DFactory("Muons","ThetaBarrel_uncut","uncut barrel #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu,barrel}","Events");
    fGeneralEtaBarrel_uncut = gHistogrammer->TH1DFactory("Muons","EtaBarrel_uncut","uncut barrel #mu #eta-distribution",etalargebins,etalargelow,etalargehigh,"#eta_{#mu,barrel}","Events");
    fGeneralChargeBarrel_uncut = gHistogrammer->TH1DFactory("Muons","ChargeBarrel_uncut","uncut barrel #mu charge distribution",chargebins,chargelow,chargehigh,"barrel #mu charge","Events");

    fGeneralNMURear_uncut = gHistogrammer->TH1DFactory("Muons","NMURear_uncut","uncut number of: rear #mu",nmubins,nmulow,nmuhigh,"number of rear #mu","Events");
    fGeneralProbRear_uncut = gHistogrammer->TH1DFactory("Muons","ProbRear_uncut","uncut rear #mu probability distribution",probbins,problow,probhigh,"rear #mu probability","Events");
    fGeneralPRear_uncut = gHistogrammer->TH1DFactory("Muons","PRear_uncut","uncut rear #mu momentum",pbins,plow,phigh,"p_{#mu,rear} [GeV]","Events");
    fGeneralPtRear_uncut = gHistogrammer->TH1DFactory("Muons","PtRear_uncut","uncut transverse rear #mu momentum",ptbins,ptlow,pthigh,"p^{#mu,rear}_{T} [GeV]","Events");
    fGeneralPtSpecialRear_uncut = gHistogrammer->TH1DFactory("Muons","PtSpecialRear_uncut","uncut transverse rear #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu,rear}_{T} [GeV]","Events");
    fGeneralPxRear_uncut = gHistogrammer->TH1DFactory("Muons","PxRear_uncut","uncut rear #mu x-momentum",pxbins,pxlow,pxhigh,"p^{#mu,rear}_{x} [GeV]","Events");
    fGeneralPyRear_uncut = gHistogrammer->TH1DFactory("Muons","PyRear_uncut","uncut rear #mu y-momentum",pybins,pylow,pyhigh,"p^{#mu,rear}_{y} [GeV]","Events");
    fGeneralPzRear_uncut = gHistogrammer->TH1DFactory("Muons","PzRear_uncut","uncut rear #mu z-momentum",pzbins,pzlow,pzhigh,"p^{#mu,rear}_{z} [GeV]","Events");
    fGeneralPhiRear_uncut = gHistogrammer->TH1DFactory("Muons","PhiRear_uncut","uncut rear #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralThetaRear_uncut = gHistogrammer->TH1DFactory("Muons","ThetaRear_uncut","uncut rear #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu,rear}","Events");
    fGeneralEtaRear_uncut = gHistogrammer->TH1DFactory("Muons","EtaRear_uncut","uncut rear #mu #eta-distribution",etalargebins,etalargelow,etalargehigh,"#eta_{#mu,rear}","Events");
    fGeneralChargeRear_uncut = gHistogrammer->TH1DFactory("Muons","ChargeRear_uncut","uncut rear #mu charge distribution",chargebins,chargelow,chargehigh,"rear #mu charge","Events");

    fGeneralPhiMUBAC_uncut = gHistogrammer->TH1DFactory("Muons","PhiMUBAC_uncut","uncut #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiMUBACForward_uncut = gHistogrammer->TH1DFactory("Muons","PhiMUBACForward_uncut","uncut forward #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiMUBACBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PhiMUBACBarrel_uncut","uncut barrel #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiMUBACRear_uncut = gHistogrammer->TH1DFactory("Muons","PhiMUBACRear_uncut","uncut rear #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiBREMAT_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMAT_uncut","uncut #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiBREMATForward_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATForward_uncut","uncut forward #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiBREMATBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATBarrel_uncut","uncut barrel #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiBREMATRear_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATRear_uncut","uncut rear #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiMPMATCH_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCH_uncut","uncut #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiMPMATCHForward_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHForward_uncut","uncut forward #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiMPMATCHBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHBarrel_uncut","uncut barrel #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiMPMATCHRear_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHRear_uncut","uncut rear #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiBREMATMUBAC_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBAC_uncut","uncut #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiBREMATMUBACForward_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBACForward_uncut","uncut forward #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiBREMATMUBACBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBACBarrel_uncut","uncut barrel #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiBREMATMUBACRear_uncut = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBACRear_uncut","uncut rear #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiMPMATCHMUBAC_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBAC_uncut","uncut #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiMPMATCHMUBACForward_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBACForward_uncut","uncut forward #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiMPMATCHMUBACBarrel_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBACBarrel_uncut","uncut barrel #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiMPMATCHMUBACRear_uncut = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBACRear_uncut","uncut rear #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");

    fGeneralMuonFinder_uncut = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder_uncut","uncut muon found by which finder",muonfinder.Data(),"","Events");
    fGeneralMuonFinder4_uncut = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder4_uncut","uncut muon found by which finder for muon quality 4",muonfinder.Data(),"","Events");
    fGeneralMuonFinder5_uncut = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder5_uncut","uncut muon found by which finder for muon quality 5",muonfinder.Data(),"","Events");
    fGeneralMuonFinder6_uncut = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder6_uncut","uncut muon found by which finder for muon quality 6",muonfinder.Data(),"","Events");

    fGeneralSpecialFinder_uncut = gHistogrammer->TH1DFactory("Muons","SpecialFinder_uncut","uncut special muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");
    fGeneralSpecialFinderForward_uncut = gHistogrammer->TH1DFactory("Muons","SpecialFinderForward_uncut","uncut special forward muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");
    fGeneralSpecialFinderBarrel_uncut = gHistogrammer->TH1DFactory("Muons","SpecialFinderBarrel_uncut","uncut special barrel muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");
    fGeneralSpecialFinderRear_uncut = gHistogrammer->TH1DFactory("Muons","SpecialFinderRear_uncut","uncut special rear muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");

    fGeneralQuality_uncut = gHistogrammer->TH1DFactory("Muons","Quality_uncut","uncut muon quality",qualitybins,qualitylow,qualityhigh,"muon quality","Events");
    fGeneralQualityAndTrue_uncut = gHistogrammer->TH1DFactory("Muons","QualityAndTrue_uncut","uncut muon quality reconstructed and true",qualitybins,qualitylow,qualityhigh,"muon quality","Events");
    fGeneralQualityForward_uncut = gHistogrammer->TH1DFactory("Muons","QualityForward_uncut","uncut forward muon quality",qualitybins,qualitylow,qualityhigh,"forward muon quality","Events");
    fGeneralQualityBarrel_uncut = gHistogrammer->TH1DFactory("Muons","QualityBarrel_uncut","uncut barrel muon quality",qualitybins,qualitylow,qualityhigh,"barrel muon quality","Events");
    fGeneralQualityRear_uncut = gHistogrammer->TH1DFactory("Muons","QualityRear_uncut","uncut rear muon quality",qualitybins,qualitylow,qualityhigh,"rear muon quality","Events");

    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
      fGeneralPMCTRUE_uncut = gHistogrammer->TH1DFactory("Muons","PMCTRUE_uncut","uncut true #mu momentum from MC info",pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","Events");
      fGeneralPXMCTRUE_uncut = gHistogrammer->TH1DFactory("Muons","PXMCTRUE_uncut","uncut true x #mu momentum from MC info",pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","Events");
      fGeneralPYMCTRUE_uncut = gHistogrammer->TH1DFactory("Muons","PYMCTRUE_uncut","uncut true y #mu momentum from MC info",pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","Events");
      fGeneralPZMCTRUE_uncut = gHistogrammer->TH1DFactory("Muons","PZMCTRUE_uncut","uncut true z #mu momentum from MC info",pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","Events");
      fGeneralPvsPMCTRUE_uncut = gHistogrammer->TH2DFactory("Muons","PvsPMCTRUE_uncut","uncut #mu momentum vs. uncut true #mu momentum from MC info",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","p^{#mu,true} [GeV]","Events");
      fGeneralPXvsPXMCTRUE_uncut = gHistogrammer->TH2DFactory("Muons","PXvsPXMCTRUE_uncut","uncut x #mu momentum vs. uncut true x #mu momentum from MC info",pxspecialbins,pxspeciallow,pxspecialhigh,pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fGeneralPYvsPYMCTRUE_uncut = gHistogrammer->TH2DFactory("Muons","PYvsPYMCTRUE_uncut","uncut y #mu momentum vs. uncut true y #mu momentum from MC info",pyspecialbins,pyspeciallow,pyspecialhigh,pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fGeneralPZvsPZMCTRUE_uncut = gHistogrammer->TH2DFactory("Muons","PZvsPZMCTRUE_uncut","uncut z #mu momentum vs. uncut true z #mu momentum from MC info",pzspecialbins,pzspeciallow,pzspecialhigh,pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");

      fGeneralPMCTRUEpos_uncut = gHistogrammer->TH1DFactory("Muons","PMCTRUEpos_uncut","uncut true #mu momentum from MC info with positive FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","Events");
      fGeneralPXMCTRUEpos_uncut = gHistogrammer->TH1DFactory("Muons","PXMCTRUEpos_uncut","uncut true x #mu momentum from MC info with positive FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","Events");
      fGeneralPYMCTRUEpos_uncut = gHistogrammer->TH1DFactory("Muons","PYMCTRUEpos_uncut","uncut true y #mu momentum from MC info with positive FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","Events");
      fGeneralPZMCTRUEpos_uncut = gHistogrammer->TH1DFactory("Muons","PZMCTRUEpos_uncut","uncut true z #mu momentum from MC info with positive FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","Events");
      fGeneralPvsPMCTRUEpos_uncut = gHistogrammer->TH2DFactory("Muons","PvsPMCTRUEpos_uncut","uncut #mu momentum vs. uncut true #mu momentum from MC info with positive FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","p^{#mu,true} [GeV]","Events");
      fGeneralPXvsPXMCTRUEpos_uncut = gHistogrammer->TH2DFactory("Muons","PXvsPXMCTRUEpos_uncut","uncut x #mu momentum vs. uncut true x #mu momentum from MC info with positive FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fGeneralPYvsPYMCTRUEpos_uncut = gHistogrammer->TH2DFactory("Muons","PYvsPYMCTRUEpos_uncut","uncut y #mu momentum vs. uncut true y #mu momentum from MC info with positive FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fGeneralPZvsPZMCTRUEpos_uncut = gHistogrammer->TH2DFactory("Muons","PZvsPZMCTRUEpos_uncut","uncut z #mu momentum vs. uncut true z #mu momentum from MC info with positive FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");

      fGeneralPMCTRUEneg_uncut = gHistogrammer->TH1DFactory("Muons","PMCTRUEneg_uncut","uncut true #mu momentum from MC info with negative FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","Events");
      fGeneralPXMCTRUEneg_uncut = gHistogrammer->TH1DFactory("Muons","PXMCTRUEneg_uncut","uncut true x #mu momentum from MC info with negative FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","Events");
      fGeneralPYMCTRUEneg_uncut = gHistogrammer->TH1DFactory("Muons","PYMCTRUEneg_uncut","uncut true y #mu momentum from MC info with negative FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","Events");
      fGeneralPZMCTRUEneg_uncut = gHistogrammer->TH1DFactory("Muons","PZMCTRUEneg_uncut","uncut true z #mu momentum from MC info with negative FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","Events");
      fGeneralPvsPMCTRUEneg_uncut = gHistogrammer->TH2DFactory("Muons","PvsPMCTRUEneg_uncut","uncut #mu momentum vs. uncut true #mu momentum from MC info with negative FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","p^{#mu,true} [GeV]","Events");
      fGeneralPXvsPXMCTRUEneg_uncut = gHistogrammer->TH2DFactory("Muons","PXvsPXMCTRUEneg_uncut","uncut x #mu momentum vs. uncut true x #mu momentum from MC info with negative FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fGeneralPYvsPYMCTRUEneg_uncut = gHistogrammer->TH2DFactory("Muons","PYvsPYMCTRUEneg_uncut","uncut y #mu momentum vs. uncut true y #mu momentum from MC info with negative FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fGeneralPZvsPZMCTRUEneg_uncut = gHistogrammer->TH2DFactory("Muons","PZvsPZMCTRUEneg_uncut","uncut z #mu momentum vs. uncut true z #mu momentum from MC info with negative FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");

    }

    fGeneral2DBeamSpotImpactParameter_uncut = gHistogrammer->TH1DFactory("Muons","2DBeamSpotImpact_uncut","uncut 2D beamspot impact parameter",impact2Dbins,impact2Dlow,impact2Dhigh,"#delta [cm]","Events");
    fGeneral2DBeamSpotImpactSignificance_uncut = gHistogrammer->TH1DFactory("Muons","2DBeamSpotSignificance_uncut","uncut 2D beamspot impact parameter significance",signi2Dbins,signi2Dlow,signi2Dhigh,"#delta/#sigma#delta [cm]","Events");

    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
      fGeneral2DMCBeamSpotImpactParameter_uncut = gHistogrammer->TH1DFactory("Muons","2DMCBeamSpotImpact_uncut","uncut true 2D beamspot impact parameter",mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","Events");
      fGeneral2DTrueImpactParameter_uncut = gHistogrammer->TH1DFactory("Muons","2DTrueImpact_uncut","uncut 2D MC true vertex impact parameter",impact2Dbins,impact2Dlow,impact2Dhigh,"#delta [cm]","Events");
      fGeneral2DMCTrueImpactParameter_uncut = gHistogrammer->TH1DFactory("Muons","2DMCTrueImpact_uncut","uncut 2D MC true impact parameter",mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","Events");
      fGeneral2DTrueImpactParamaterRecVsTrue_uncut = gHistogrammer->TH2DFactory("Muons","2DTrueImpactParameterRecVsTrue_uncut","uncut 2D MC true vertex impact parameter Rec vs. True",impact2Dbins,impact2Dlow,impact2Dhigh,mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","#delta [cm]","Events");
      fGeneral2DBeamSpotImpactParamaterRecVsTrue_uncut = gHistogrammer->TH2DFactory("Muons","2DBeamSpotImpactParameterRecVsTrue_uncut","uncut 2D beamspot impact parameter Rec vs. True",impact2Dbins,impact2Dlow,impact2Dhigh,mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","#delta [cm]","Events");
    }

    fGeneralGMuonPVsZTTP_uncut = gHistogrammer->TH2DFactory("Muons","GMuonPVsZTTP_uncut","uncut gmuon p vs. ztt p",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p_{GMUON} [GeV]","p_{ZTT} [GeV]","Events");
   


    // general plots
    fGeneralWeight = gHistogrammer->TH1DFactory("Muons","Weight","weight of #mu",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightForward = gHistogrammer->TH1DFactory("Muons","WeightForward","weight of forward #mu",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightBarrel = gHistogrammer->TH1DFactory("Muons","WeightBarrel","weight of barrel #mu",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightRear = gHistogrammer->TH1DFactory("Muons","WeightRear","weight of rear #mu",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightMUBAC = gHistogrammer->TH1DFactory("Muons","WeightMUBAC","weight of #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightMUBACForward = gHistogrammer->TH1DFactory("Muons","WeightMUBACForward","weight of forward #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightMUBACBarrel = gHistogrammer->TH1DFactory("Muons","WeightMUBACBarrel","weight of barrel #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightMUBACRear = gHistogrammer->TH1DFactory("Muons","WeightMUBACRear","weight of rear #mu found excl. by MUBAC",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightBREMAT = gHistogrammer->TH1DFactory("Muons","WeightBREMAT","weight of #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightBREMATForward = gHistogrammer->TH1DFactory("Muons","WeightBREMATForward","weight of forward #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightBREMATBarrel = gHistogrammer->TH1DFactory("Muons","WeightBREMATBarrel","weight of barrel #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightBREMATRear = gHistogrammer->TH1DFactory("Muons","WeightBREMATRear","weight of rear #mu found excl. by BREMAT",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightMPMATCH = gHistogrammer->TH1DFactory("Muons","WeightMPMATCH","weight of #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightMPMATCHForward = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHForward","weight of forward #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightMPMATCHBarrel = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHBarrel","weight of barrel #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightMPMATCHRear = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHRear","weight of rear #mu found excl. by MPMATCH",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightBREMATMUBAC = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBAC","weight of #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightBREMATMUBACForward = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBACForward","weight of forward #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightBREMATMUBACBarrel = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBACBarrel","weight of barrel #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightBREMATMUBACRear = gHistogrammer->TH1DFactory("Muons","WeightBREMATMUBACRear","weight of rear #mu found by BREMAT and MUBAC",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");
    fGeneralWeightMPMATCHMUBAC = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBAC","weight of #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fGeneralWeightMPMATCHMUBACForward = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBACForward","weight of forward #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of forward #mu","Events");
    fGeneralWeightMPMATCHMUBACBarrel = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBACBarrel","weight of barrel #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of barrel #mu","Events");
    fGeneralWeightMPMATCHMUBACRear = gHistogrammer->TH1DFactory("Muons","WeightMPMATCHMUBACRear","weight of rear #mu found by MPMATCH and MUBAC",weightbins,weightlow,weighthigh,"weight of rear #mu","Events");

    fGeneralNMU = gHistogrammer->TH1DFactory("Muons","NMU","number of: #mu",nmubins,nmulow,nmuhigh,"number of #mu","Events");
    fGeneralRegions = gHistogrammer->TH1DFactory("Muons","Regions","#mu regions",regionbins,regionlow,regionhigh,"#mu region","Events");
    fGeneralNMUForward = gHistogrammer->TH1DFactory("Muons","NMUForward","number of: forward #mu",nmubins,nmulow,nmuhigh,"number of forward #mu","Events");
    fGeneralNMUBarrel = gHistogrammer->TH1DFactory("Muons","NMUBarrel","number of: barrel #mu",nmubins,nmulow,nmuhigh,"number of barrel #mu","Events");
    fGeneralNMURear = gHistogrammer->TH1DFactory("Muons","NMURear","number of: rear #mu",nmubins,nmulow,nmuhigh,"number of rear #mu","Events");
    fGeneralProb = gHistogrammer->TH1DFactory("Muons","Prob","#mu probability distribution",probbins,problow,probhigh,"#mu probability","Events");
    fGeneralProbForward = gHistogrammer->TH1DFactory("Muons","ProbForward","forward #mu probability distribution",probbins,problow,probhigh,"forward #mu probability","Events");
    fGeneralProbBarrel = gHistogrammer->TH1DFactory("Muons","ProbBarrel","barrel #mu probability distribution",probbins,problow,probhigh,"barrel #mu probability","Events");
    fGeneralProbRear = gHistogrammer->TH1DFactory("Muons","ProbRear","rear #mu probability distribution",probbins,problow,probhigh,"rear #mu probability","Events");
    fGeneralP = gHistogrammer->TH1DFactory("Muons","P","#mu momentum",pspecialbins,pspeciallow,pspecialhigh,"p_{#mu} [GeV]","Events");
    fGeneralPForward = gHistogrammer->TH1DFactory("Muons","PForward","forward #mu momentum",pbins,plow,phigh,"p_{#mu,forward} [GeV]","Events");
    fGeneralPBarrel = gHistogrammer->TH1DFactory("Muons","PBarrel","barrel #mu momentum",pbins,plow,phigh,"p_{#mu,barrel} [GeV]","Events");
    fGeneralPRear = gHistogrammer->TH1DFactory("Muons","PRear","rear #mu momentum",pbins,plow,phigh,"p_{#mu,rear} [GeV]","Events");
    fGeneralPt = gHistogrammer->TH1DFactory("Muons","Pt","transverse #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosen = gHistogrammer->TH1DFactory("Muons","PtChosen","transverse #mu momentum of the chosen muon",ptbins,ptlow,pthigh,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosenFine2 = gHistogrammer->TH1DFactory("Muons","PtChosenFine2","transverse #mu momentum of the chosen muon",ptfine2bins,ptfine2low,ptfine2high,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosenFine4 = gHistogrammer->TH1DFactory("Muons","PtChosenFine4","transverse #mu momentum of the chosen muon",ptfine4bins,ptfine4low,ptfine4high,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosenFine8 = gHistogrammer->TH1DFactory("Muons","PtChosenFine8","transverse #mu momentum of the chosen muon",ptfine8bins,ptfine8low,ptfine8high,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosenFine16 = gHistogrammer->TH1DFactory("Muons","PtChosenFine16","transverse #mu momentum of the chosen muon",ptfine16bins,ptfine16low,ptfine16high,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosenMC = gHistogrammer->TH1DFactory("Muons","PtChosenMC","transverse #mu momentum of the chosen muon which is a true MC muon",ptbins,ptlow,pthigh,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtChosenFineMC = gHistogrammer->TH1DFactory("Muons","PtChosenFineMC","transverse #mu momentum of the chosen muon which is a true MC muon",ptfine2bins,ptfine2low,ptfine2high,"p^{#mu}_{T} [GeV]","Events");

    if ( gCards->GetMUONCalculateMuonIsolation() ) {
      fGeneralChosenIso01 = gHistogrammer->TH1DFactory("Muons","ChosenIso01","#mu isolation in cone of 0.1 of chosen muon",iso01bins,iso01low,iso01high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso02 = gHistogrammer->TH1DFactory("Muons","ChosenIso02","#mu isolation in cone of 0.2 of chosen muon",iso02bins,iso02low,iso02high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso03 = gHistogrammer->TH1DFactory("Muons","ChosenIso03","#mu isolation in cone of 0.3 of chosen muon",iso03bins,iso03low,iso03high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso04 = gHistogrammer->TH1DFactory("Muons","ChosenIso04","#mu isolation in cone of 0.4 of chosen muon",iso04bins,iso04low,iso04high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso05 = gHistogrammer->TH1DFactory("Muons","ChosenIso05","#mu isolation in cone of 0.5 of chosen muon",iso05bins,iso05low,iso05high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso06 = gHistogrammer->TH1DFactory("Muons","ChosenIso06","#mu isolation in cone of 0.6 of chosen muon",iso06bins,iso06low,iso06high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso07 = gHistogrammer->TH1DFactory("Muons","ChosenIso07","#mu isolation in cone of 0.7 of chosen muon",iso07bins,iso07low,iso07high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso08 = gHistogrammer->TH1DFactory("Muons","ChosenIso08","#mu isolation in cone of 0.8 of chosen muon",iso08bins,iso08low,iso08high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso09 = gHistogrammer->TH1DFactory("Muons","ChosenIso09","#mu isolation in cone of 0.9 of chosen muon",iso09bins,iso09low,iso09high,"#mu isolation [GeV]","Events");
      fGeneralChosenIso10 = gHistogrammer->TH1DFactory("Muons","ChosenIso10","#mu isolation in cone of 1.0 of chosen muon",iso10bins,iso10low,iso10high,"#mu isolation [GeV]","Events");
    }

    fGeneralPtForward = gHistogrammer->TH1DFactory("Muons","PtForward","transverse forward #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T,forward} [GeV]","Events");
    fGeneralPtBarrel = gHistogrammer->TH1DFactory("Muons","PtBarrel","transverse barrel #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T,barrel} [GeV]","Events");
    fGeneralPtRear = gHistogrammer->TH1DFactory("Muons","PtRear","transverse rear #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T,rear} [GeV]","Events");
    fGeneralPtSpecial = gHistogrammer->TH1DFactory("Muons","PtSpecial","transverse #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu}_{T} [GeV]","Events");
    fGeneralPtSpecialForward = gHistogrammer->TH1DFactory("Muons","PtSpecialForward","transverse forward #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu}_{T,forward} [GeV]","Events");
    fGeneralPtSpecialBarrel = gHistogrammer->TH1DFactory("Muons","PtSpecialBarrel","transverse barrel #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu}_{T,barrel} [GeV]","Events");
    fGeneralPtSpecialRear = gHistogrammer->TH1DFactory("Muons","PtSpecialRear","transverse rear #mu momentum",ptspecialbins,ptspeciallow,ptspecialhigh,"p^{#mu}_{T,rear} [GeV]","Events");
    fGeneralPx = gHistogrammer->TH1DFactory("Muons","Px","#mu x-momentum",pxspecialbins,pxspeciallow,pxspecialhigh,"p^{#mu}_{x} [GeV]","Events");
    fGeneralPxForward = gHistogrammer->TH1DFactory("Muons","PxForward","forward #mu x-momentum",pxbins,pxlow,pxhigh,"p^{#mu}_{x,forward} [GeV]","Events");
    fGeneralPxBarrel = gHistogrammer->TH1DFactory("Muons","PxBarrel","barrel #mu x-momentum",pxbins,pxlow,pxhigh,"p^{#mu}_{x,barrel} [GeV]","Events");
    fGeneralPxRear = gHistogrammer->TH1DFactory("Muons","PxRear","rear #mu x-momentum",pxbins,pxlow,pxhigh,"p^{#mu}_{x,rear} [GeV]","Events");
    fGeneralPy = gHistogrammer->TH1DFactory("Muons","Py","#mu y-momentum",pyspecialbins,pyspeciallow,pyspecialhigh,"p^{#mu}_{y} [GeV]","Events");
    fGeneralPyForward = gHistogrammer->TH1DFactory("Muons","PyForward","forward #mu y-momentum",pybins,pylow,pyhigh,"p^{#mu}_{y,forward} [GeV]","Events");
    fGeneralPyBarrel = gHistogrammer->TH1DFactory("Muons","PyBarrel","barrel #mu y-momentum",pybins,pylow,pyhigh,"p^{#mu}_{y,barrel} [GeV]","Events");
    fGeneralPyRear = gHistogrammer->TH1DFactory("Muons","PyRear","rear #mu y-momentum",pybins,pylow,pyhigh,"p^{#mu}_{y,rear} [GeV]","Events");
    fGeneralPz = gHistogrammer->TH1DFactory("Muons","Pz","#mu z-momentum",pzspecialbins,pzspeciallow,pzspecialhigh,"p^{#mu}_{z} [GeV]","Events");
    fGeneralPzForward = gHistogrammer->TH1DFactory("Muons","PzForward","forward #mu z-momentum",pzbins,pzlow,pzhigh,"p^{#mu}_{z,forward} [GeV]","Events");
    fGeneralPzBarrel = gHistogrammer->TH1DFactory("Muons","PzBarrel","barrel #mu z-momentum",pzbins,pzlow,pzhigh,"p^{#mu}_{z,barrel} [GeV]","Events");
    fGeneralPzRear = gHistogrammer->TH1DFactory("Muons","PzRear","rear #mu z-momentum",pzbins,pzlow,pzhigh,"p^{#mu}_{z,rear} [GeV]","Events");
    fGeneralPhi = gHistogrammer->TH1DFactory("Muons","Phi","#mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiForward = gHistogrammer->TH1DFactory("Muons","PhiForward","forward #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiBarrel = gHistogrammer->TH1DFactory("Muons","PhiBarrel","barrel #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiRear = gHistogrammer->TH1DFactory("Muons","PhiRear","rear #mu #phi-distribution",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralTheta = gHistogrammer->TH1DFactory("Muons","Theta","#mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu}","Events");
    fGeneralThetaForward = gHistogrammer->TH1DFactory("Muons","ThetaForward","forward #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu,forward}","Events");
    fGeneralThetaBarrel = gHistogrammer->TH1DFactory("Muons","ThetaBarrel","barrel #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu,barrel}","Events");
    fGeneralThetaRear = gHistogrammer->TH1DFactory("Muons","ThetaRear","rear #mu #theta-distribution",thetabins,thetalow,thetahigh,"#theta_{#mu,rear}","Events");
    fGeneralEta = gHistogrammer->TH1DFactory("Muons","Eta","#mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fGeneralEtaChosen = gHistogrammer->TH1DFactory("Muons","EtaChosen","#mu #eta-distribution of the chosen muon",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fGeneralEtaChosenLarge = gHistogrammer->TH1DFactory("Muons","EtaChosenLarge","#mu #eta-distribution of the chosen muon",etalargebins,etalargelow,etalargehigh,"#eta_{#mu}","Events");
    fGeneralEtaChosenMC = gHistogrammer->TH1DFactory("Muons","EtaChosenMC","#mu #eta-distribution of the chosen muon which is a true MC muon",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fGeneralEtaChosenLargeMC = gHistogrammer->TH1DFactory("Muons","EtaChosenLargeMC","#mu #eta-distribution of the chosen muon which is a true MC muon",etalargebins,etalargelow,etalargehigh,"#eta_{#mu}","Events");
    fGeneralEtaForward = gHistogrammer->TH1DFactory("Muons","EtaForward","forward #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu,forward}","Events");
    fGeneralEtaBarrel = gHistogrammer->TH1DFactory("Muons","EtaBarrel","barrel #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu,barrel}","Events");
    fGeneralEtaRear = gHistogrammer->TH1DFactory("Muons","EtaRear","rear #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu,rear}","Events");
    fGeneralCharge = gHistogrammer->TH1DFactory("Muons","Charge","#mu charge distribution",chargebins,chargelow,chargehigh,"#mu charge","Events");
    fGeneralChargeForward = gHistogrammer->TH1DFactory("Muons","ChargeForward","forward #mu charge distribution",chargebins,chargelow,chargehigh,"forward #mu charge","Events");
    fGeneralChargeBarrel = gHistogrammer->TH1DFactory("Muons","ChargeBarrel","barrel #mu charge distribution",chargebins,chargelow,chargehigh,"barrel #mu charge","Events");
    fGeneralChargeRear = gHistogrammer->TH1DFactory("Muons","ChargeRear","rear #mu charge distribution",chargebins,chargelow,chargehigh,"rear #mu charge","Events");
    fGeneralMuonFinder = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder","muon found by which finder",muonfinder.Data(),"","Events");
    fGeneralMuonFinder4 = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder4","muon found by which finder for muon quality 4",muonfinder.Data(),"","Events");
    fGeneralMuonFinder5 = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder5","muon found by which finder for muon quality 5",muonfinder.Data(),"","Events");
    fGeneralMuonFinder6 = gHistogrammer->TH1DLabelFactory("Muons","MuonFinder6","muon found by which finder for muon quality 6",muonfinder.Data(),"","Events");

    fGeneralSpecialFinder4 = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder4","muon found by which finder combination for muon quality 4",specialfinder4bins,specialfinder4low,specialfinder4high,"combination","Events");
    fGeneralSpecialFinder5 = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder5","muon found by which finder combination for muon quality 5",specialfinder5bins,specialfinder5low,specialfinder5high,"combination","Events");
    fGeneralSpecialFinder6 = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder6","muon found by which finder combination for muon quality 6",specialfinder6bins,specialfinder6low,specialfinder6high,"combination","Events");

    fGeneralSpecialFinder4Forward = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder4Forward","forward muon found by which finder combination for muon quality 4",specialfinder4bins,specialfinder4low,specialfinder4high,"combination","Events");
    fGeneralSpecialFinder5Forward = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder5Forward","forward muon found by which finder combination for muon quality 5",specialfinder5bins,specialfinder5low,specialfinder5high,"combination","Events");
    fGeneralSpecialFinder6Forward = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder6Forward","forward muon found by which finder combination for muon quality 6",specialfinder6bins,specialfinder6low,specialfinder6high,"combination","Events");

    fGeneralSpecialFinder4Barrel = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder4Barrel","barrel muon found by which finder combination for muon quality 4",specialfinder4bins,specialfinder4low,specialfinder4high,"combination","Events");
    fGeneralSpecialFinder5Barrel = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder5Barrel","barrel muon found by which finder combination for muon quality 5",specialfinder5bins,specialfinder5low,specialfinder5high,"combination","Events");
    fGeneralSpecialFinder6Barrel = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder6Barrel","barrel muon found by which finder combination for muon quality 6",specialfinder6bins,specialfinder6low,specialfinder6high,"combination","Events");

    fGeneralSpecialFinder4Rear = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder4Rear","rear muon found by which finder combination for muon quality 4",specialfinder4bins,specialfinder4low,specialfinder4high,"combination","Events");
    fGeneralSpecialFinder5Rear = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder5Rear","rear muon found by which finder combination for muon quality 5",specialfinder5bins,specialfinder5low,specialfinder5high,"combination","Events");
    fGeneralSpecialFinder6Rear = gHistogrammer->TH1DFactory("Muons","MuonSpecialFinder6Rear","rear muon found by which finder combination for muon quality 6",specialfinder6bins,specialfinder6low,specialfinder6high,"combination","Events");

    fGeneralSpecialFinder = gHistogrammer->TH1DFactory("Muons","SpecialFinder","special muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");
    fGeneralSpecialFinderForward = gHistogrammer->TH1DFactory("Muons","SpecialFinderForward","special forward muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");
    fGeneralSpecialFinderBarrel = gHistogrammer->TH1DFactory("Muons","SpecialFinderBarrel","special barrel muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");
    fGeneralSpecialFinderRear = gHistogrammer->TH1DFactory("Muons","SpecialFinderRear","special rear muon finder",specialfinderbins,specialfinderlow,specialfinderhigh,"special","Events");

    fGeneralPhiMUBAC = gHistogrammer->TH1DFactory("Muons","PhiMUBAC","#mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiMUBACForward = gHistogrammer->TH1DFactory("Muons","PhiMUBACForward","forward #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiMUBACBarrel = gHistogrammer->TH1DFactory("Muons","PhiMUBACBarrel","barrel #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiMUBACRear = gHistogrammer->TH1DFactory("Muons","PhiMUBACRear","rear #mu #phi-distribution found excl. by MUBAC",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiBREMAT = gHistogrammer->TH1DFactory("Muons","PhiBREMAT","#mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiBREMATForward = gHistogrammer->TH1DFactory("Muons","PhiBREMATForward","forward #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiBREMATBarrel = gHistogrammer->TH1DFactory("Muons","PhiBREMATBarrel","barrel #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiBREMATRear = gHistogrammer->TH1DFactory("Muons","PhiBREMATRear","rear #mu #phi-distribution found excl. by BREMAT",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiMPMATCH = gHistogrammer->TH1DFactory("Muons","PhiMPMATCH","#mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiMPMATCHForward = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHForward","forward #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiMPMATCHBarrel = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHBarrel","barrel #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiMPMATCHRear = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHRear","rear #mu #phi-distribution found excl. by MPMATCH",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiBREMATMUBAC = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBAC","#mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiBREMATMUBACForward = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBACForward","forward #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiBREMATMUBACBarrel = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBACBarrel","barrel #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiBREMATMUBACRear = gHistogrammer->TH1DFactory("Muons","PhiBREMATMUBACRear","rear #mu #phi-distribution found by BREMAT and MUBAC",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");
    fGeneralPhiMPMATCHMUBAC = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBAC","#mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralPhiMPMATCHMUBACForward = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBACForward","forward #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu,forward}","Events");
    fGeneralPhiMPMATCHMUBACBarrel = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBACBarrel","barrel #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu,barrel}","Events");
    fGeneralPhiMPMATCHMUBACRear = gHistogrammer->TH1DFactory("Muons","PhiMPMATCHMUBACRear","rear #mu #phi-distribution found by MPMATCH and MUBAC",phibins,philow,phihigh,"#phi_{#mu,rear}","Events");

    fGeneralQuality = gHistogrammer->TH1DFactory("Muons","Quality","muon quality",qualitybins,qualitylow,qualityhigh,"muon quality","Events");
    fGeneralQualityAndTrue = gHistogrammer->TH1DFactory("Muons","QualityAndTrue","muon quality reconstructed and true",qualitybins,qualitylow,qualityhigh,"muon quality","Events");
    fGeneralQualityForward = gHistogrammer->TH1DFactory("Muons","QualityForward","forward muon quality",qualitybins,qualitylow,qualityhigh,"forward muon quality","Events");
    fGeneralQualityBarrel = gHistogrammer->TH1DFactory("Muons","QualityBarrel","barrel muon quality",qualitybins,qualitylow,qualityhigh,"barrel muon quality","Events");
    fGeneralQualityRear = gHistogrammer->TH1DFactory("Muons","QualityRear","rear muon quality",qualitybins,qualitylow,qualityhigh,"rear muon quality","Events");

    fGeneralCrossTotal = gHistogrammer->TH1DFactory("Muons","CrossTotal","total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
  fGeneralCrossTotalMuChamber = gHistogrammer->TH1DFactory("Muons","CrossTotalMuChamber","total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
  fGeneralCrossTotalBAC = gHistogrammer->TH1DFactory("Muons","CrossTotalBAC","total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
    fGeneralCrossRegions = gHistogrammer->TH1DFactory("Muons","CrossRegions","#mu regions",crossregionbins,crossregionlow,crossregionhigh,"#mu region","Events");
    fGeneralCrossFinder = gHistogrammer->TH1DFactory("Muons","CrossFinder","#mu special finder",specialfinderbins,specialfinderlow,specialfinderhigh,"#mu finder","Events");
    fGeneralCrossPt = gHistogrammer->TH1DVarFactory("Muons","CrossPt","p_{T}^{#mu}",crosspt_nbins,crosspt_bins,"p_{T}^{#mu} [GeV]","Events");
    fGeneralCrossEta = gHistogrammer->TH1DVarFactory("Muons","CrossEta","#eta^{#mu}",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");
    fGeneralCrossPtFine = gHistogrammer->TH1DVarFactory("Muons","CrossPtFine","p_{T}^{#mu}",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu} [GeV]","Events");
    fGeneralCrossEtaFine = gHistogrammer->TH1DVarFactory("Muons","CrossEtaFine","#eta^{#mu}",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");
    fGeneralCrossPtMassimo = gHistogrammer->TH1DVarFactory("Muons","CrossPtMassimo","p_{T}^{#mu}",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu} [GeV]","Events");
    fGeneralCrossEtaMassimo = gHistogrammer->TH1DVarFactory("Muons","CrossEtaMassimo","#eta^{#mu}",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");

    if ( gCards->GetMC() ) {
      fGeneralPMCTRUE = gHistogrammer->TH1DFactory("Muons","PMCTRUE","true #mu momentum from MC info",pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","Events");
      fGeneralPXMCTRUE = gHistogrammer->TH1DFactory("Muons","PXMCTRUE","true x #mu momentum from MC info",pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","Events");
      fGeneralPYMCTRUE = gHistogrammer->TH1DFactory("Muons","PYMCTRUE","true y #mu momentum from MC info",pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","Events");
      fGeneralPZMCTRUE = gHistogrammer->TH1DFactory("Muons","PZMCTRUE","true z #mu momentum from MC info",pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","Events");
      fGeneralPvsPMCTRUE = gHistogrammer->TH2DFactory("Muons","PvsPMCTRUE","#mu momentum vs. true #mu momentum from MC info",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","p^{#mu,true} [GeV]","Events");
      fGeneralPXvsPXMCTRUE = gHistogrammer->TH2DFactory("Muons","PXvsPXMCTRUE","x #mu momentum vs. true x #mu momentum from MC info",pxspecialbins,pxspeciallow,pxspecialhigh,pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fGeneralPYvsPYMCTRUE = gHistogrammer->TH2DFactory("Muons","PYvsPYMCTRUE","y #mu momentum vs. true y #mu momentum from MC info",pyspecialbins,pyspeciallow,pyspecialhigh,pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fGeneralPZvsPZMCTRUE = gHistogrammer->TH2DFactory("Muons","PZvsPZMCTRUE","z #mu momentum vs. true z #mu momentum from MC info",pzspecialbins,pzspeciallow,pzspecialhigh,pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");

      fGeneralPMCTRUEpos = gHistogrammer->TH1DFactory("Muons","PMCTRUEpos","true #mu momentum from MC info with positive FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","Events");
      fGeneralPXMCTRUEpos = gHistogrammer->TH1DFactory("Muons","PXMCTRUEpos","true x #mu momentum from MC info with positive FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","Events");
      fGeneralPYMCTRUEpos = gHistogrammer->TH1DFactory("Muons","PYMCTRUEpos","true y #mu momentum from MC info with positive FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","Events");
      fGeneralPZMCTRUEpos = gHistogrammer->TH1DFactory("Muons","PZMCTRUEpos","true z #mu momentum from MC info with positive FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","Events");
      fGeneralPvsPMCTRUEpos = gHistogrammer->TH2DFactory("Muons","PvsPMCTRUEpos","#mu momentum vs. true #mu momentum from MC info with positive FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","p^{#mu,true} [GeV]","Events");
      fGeneralPXvsPXMCTRUEpos = gHistogrammer->TH2DFactory("Muons","PXvsPXMCTRUEpos","x #mu momentum vs. true x #mu momentum from MC info with positive FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fGeneralPYvsPYMCTRUEpos = gHistogrammer->TH2DFactory("Muons","PYvsPYMCTRUEpos","y #mu momentum vs. true y #mu momentum from MC info with positive FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fGeneralPZvsPZMCTRUEpos = gHistogrammer->TH2DFactory("Muons","PZvsPZMCTRUEpos","z #mu momentum vs. true z #mu momentum from MC info with positive FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");

      fGeneralPMCTRUEneg = gHistogrammer->TH1DFactory("Muons","PMCTRUEneg","true #mu momentum from MC info with negative FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","Events");
      fGeneralPXMCTRUEneg = gHistogrammer->TH1DFactory("Muons","PXMCTRUEneg","true x #mu momentum from MC info with negative FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","Events");
      fGeneralPYMCTRUEneg = gHistogrammer->TH1DFactory("Muons","PYMCTRUEneg","true y #mu momentum from MC info with negative FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","Events");
      fGeneralPZMCTRUEneg = gHistogrammer->TH1DFactory("Muons","PZMCTRUEneg","true z #mu momentum from MC info with negative FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","Events");
      fGeneralPvsPMCTRUEneg = gHistogrammer->TH2DFactory("Muons","PvsPMCTRUEneg","#mu momentum vs. true #mu momentum from MC info with negative FMCKIN ID",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p^{#mu} [GeV]","p^{#mu,true} [GeV]","Events");
      fGeneralPXvsPXMCTRUEneg = gHistogrammer->TH2DFactory("Muons","PXvsPXMCTRUEneg","x #mu momentum vs. true x #mu momentum from MC info with negative FMCKIN ID",pxspecialbins,pxspeciallow,pxspecialhigh,pxspecialbins,pxspeciallow,pxspecialhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fGeneralPYvsPYMCTRUEneg = gHistogrammer->TH2DFactory("Muons","PYvsPYMCTRUEneg","y #mu momentum vs. true y #mu momentum from MC info with negative FMCKIN ID",pyspecialbins,pyspeciallow,pyspecialhigh,pyspecialbins,pyspeciallow,pyspecialhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fGeneralPZvsPZMCTRUEneg = gHistogrammer->TH2DFactory("Muons","PZvsPZMCTRUEneg","z #mu momentum vs. true z #mu momentum from MC info with negative FMCKIN ID",pzspecialbins,pzspeciallow,pzspecialhigh,pzspecialbins,pzspeciallow,pzspecialhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");

      fGeneralCrossTotalRecNTrue = gHistogrammer->TH1DFactory("Muons","CrossTotalRecNTrue","total rec. and true",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
      fGeneralCrossTotalBACRecNTrue = gHistogrammer->TH1DFactory("Muons","CrossTotalBACRecNTrue","total rec. and true",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
      fGeneralCrossTotalMuChamberRecNTrue = gHistogrammer->TH1DFactory("Muons","CrossTotalMuChamberRecNTrue","total rec. and true",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");

    fGeneralCrossFinderRecNTrue = gHistogrammer->TH1DFactory("Muons","CrossFinderRecNTrue","#mu special finder rec. and true",specialfinderbins,specialfinderlow,specialfinderhigh,"#mu finder","Events");
      fGeneralCrossRegionsRecNTrue = gHistogrammer->TH1DFactory("Muons","CrossRegionsRecNTrue","regions of rec. and true #mu",crossregionbins,crossregionlow,crossregionhigh,"#mu region","Events");
      fGeneralCrossPtRecNTrue = gHistogrammer->TH1DVarFactory("Muons","CrossPtRecNTrue","rec. and true p_{T}^{#mu}",crosspt_nbins,crosspt_bins,"p_{T}^{#mu} [GeV]","Events");
      fGeneralCrossEtaRecNTrue = gHistogrammer->TH1DVarFactory("Muons","CrossEtaRecNTrue","rec. and true #eta^{#mu}",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");
      fGeneralCrossPtFineRecNTrue = gHistogrammer->TH1DVarFactory("Muons","CrossPtFineRecNTrue","rec. and true p_{T}^{#mu}",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu} [GeV]","Events");
      fGeneralCrossEtaFineRecNTrue = gHistogrammer->TH1DVarFactory("Muons","CrossEtaFineRecNTrue","rec. and true #eta^{#mu}",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");
      fGeneralCrossPtMassimoRecNTrue = gHistogrammer->TH1DVarFactory("Muons","CrossPtMassimoRecNTrue","rec. and true p_{T}^{#mu}",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu} [GeV]","Events");
      fGeneralCrossEtaMassimoRecNTrue = gHistogrammer->TH1DVarFactory("Muons","CrossEtaMassimoRecNTrue","rec. and true #eta^{#mu}",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");

    }

    fGeneral2DBeamSpotImpactParameter = gHistogrammer->TH1DFactory("Muons","2DBeamSpotImpact","2D beamspot impact parameter",impact2Dbins,impact2Dlow,impact2Dhigh,"#delta [cm]","Events");
  fGeneral2DBeamSpotImpactParameter_Mirrored = gHistogrammer->TH1DFactory("Muons","2DBeamSpotImpact_Mirrowed","2D beamspot impact parameter",impact2Dbins,impact2Dlow,impact2Dhigh,"#delta [cm]","Events");
    fGeneral2DBeamSpotImpactSignificance = gHistogrammer->TH1DFactory("Muons","2DBeamSpotSignificance","2D beamspot impact parameter significance",signi2Dbins,signi2Dlow,signi2Dhigh,"#delta/#sigma#delta [cm]","Events");
    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
      fGeneral2DMCBeamSpotImpactParameter = gHistogrammer->TH1DFactory("Muons","2DMCBeamSpotImpact","true 2D beamspot impact parameter",mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","Events");
      fGeneral2DTrueImpactParameter = gHistogrammer->TH1DFactory("Muons","2DTrueImpact","2D MC true vertex impact parameter",impact2Dbins,impact2Dlow,impact2Dhigh,"#delta [cm]","Events");
      fGeneral2DMCTrueImpactParameter = gHistogrammer->TH1DFactory("Muons","2DMCTrueImpact","2D MC true vertex impact parameter",mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","Events");
      fGeneral2DTrueImpactParamaterRecVsTrue = gHistogrammer->TH2DFactory("Muons","2DTrueImpactParameterRecVsTrue","2D MC true vertex impact parameter Rec vs. True",impact2Dbins,impact2Dlow,impact2Dhigh,mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","#delta [cm]","Events");
      fGeneral2DBeamSpotImpactParamaterRecVsTrue = gHistogrammer->TH2DFactory("Muons","2DBeamSpotImpactParameterRecVsTrue","2D beamspot impact parameter Rec vs. True",impact2Dbins,impact2Dlow,impact2Dhigh,mcimpact2Dbins,mcimpact2Dlow,mcimpact2Dhigh,"#delta [cm]","#delta [cm]","Events");
    }
    fGeneralGMuonPVsZTTP = gHistogrammer->TH2DFactory("Muons","GMuonPVsZTTP","uncut gmuon p vs. ztt p",pspecialbins,pspeciallow,pspecialhigh,pspecialbins,pspeciallow,pspecialhigh,"p_{GMUON} [GeV]","p_{ZTT} [GeV]","Events");

  }
  if(gCards->GetProduceFakeMuon() ) CreateFake();
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CreateControl() {
  //
  // create control histograms
  if ( gDebug ) cout << endl << "GMuons::CreateControl() called" << endl << endl;

  if ( gCards->GetMUONControl() ) {
    
    Int_t    weightbins = 100;
    Double_t weightlow  = 0.0;
    Double_t weighthigh = 10.0;
    Int_t    probbins    = 100;
    Double_t problow     = 0.;
    Double_t probhigh    = 1.;
    Int_t    pbins       = 30;
    Double_t plow        = 0.;
    Double_t phigh       = 15.;
    Int_t    ptbins      = 30;
    Double_t ptlow       = 0.;
    Double_t pthigh      = 15.;
    Int_t    etabins     = 120;
    Double_t etalow      = -6.0;
    Double_t etahigh     = 6.0;
    Int_t    chflgbins   = 7;
    Double_t chflglow    = 0.;
    Double_t chflghigh   = 7.;
    //    TString  muonfinder  = "Glomu,Bremat,MuBac,Mamma,MPMatch,Mufo,Mip,Mv";
    TString  muonfinder  = "Glomu,Bremat,BacMat,MuBac,Mamma,MPMatch,Mufo,Mip,Mv";
    Int_t    mfprobins   = 100;
    Double_t mfprolow    = 0.;
    Double_t mfprohigh   = 1.;
    Int_t    mfndfbins   = 15;
    Double_t mfndflow    = 0.;
    Double_t mfndfhigh   = 15.;
    Int_t    mfzbins     = 1000;
    Double_t mfzlow      = 0.;
    Double_t mfzhigh     = 1000.;
    Int_t    qualitybins = 7;
    Double_t qualitylow  = 0.;
    Double_t qualityhigh = 7.;
    Int_t    chamberbins = 20;
    Double_t chamberxlow = 0.;
    Double_t chamberxhigh= 20.;
    Double_t chamberylow = 0.;
    Double_t chamberyhigh= 20.;
    
    // uncut control plots
    fControlProb_uncut = gHistogrammer->TH1DFactory("Muons_Control","Prob_uncut","uncut #mu probability distribution",probbins,problow,probhigh,"#mu probability","Events");
    fControlEta_uncut = gHistogrammer->TH1DFactory("Muons_Control","Eta_uncut","uncut #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fControlP_uncut = gHistogrammer->TH1DFactory("Muons_Control","P_uncut","uncut #mu momentum",pbins,plow,phigh,"p_{#mu} [GeV]","Events");
    fControlPt_uncut = gHistogrammer->TH1DFactory("Muons_Control","Pt_uncut","uncut transverse #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T} [GeV]","Events");
    fControlChFlg_uncut = gHistogrammer->TH1DFactory("Muons_Control","ChFlg_uncut","uncut #mu chamberflag",chflgbins,chflglow,chflghigh,"chamberflag","Events");
    fControlMuonFinder_uncut = gHistogrammer->TH1DLabelFactory("Muons_Control","MuonFinder_uncut","Muon finder",muonfinder.Data(),"","Events");
    fControlMuonMfpro_uncut = gHistogrammer->TH1DFactory("Muons_Control","Mfpro_uncut","uncut probability of kalman filter for MPMATCH",mfprobins,mfprolow,mfprohigh,"probability","Events"); 
    fControlMuonMfndf_uncut = gHistogrammer->TH1DFactory("Muons_Control","Mfndf_uncut","uncut degrees of freedom of kalman filter for MPMATCH",mfndfbins,mfndflow,mfndfhigh,"degrees of freedom","Events");
    fControlMuonMfz_uncut = gHistogrammer->TH1DFactory("Muons_Control","Mfz_uncut","uncut internal camber requirement for MPMATCH",mfzbins,mfzlow,mfzhigh,"internal chamber requirement","Events");
    fControlQuality_uncut = gHistogrammer->TH1DFactory("Muons_Control","Quality_uncut","uncut gmuon quality",qualitybins,qualitylow,qualityhigh,"quality","Events");
    fControlQualityForwardBAC_uncut = gHistogrammer->TH1DFactory("Muons_Control","QualityForwardBAC_uncut","uncut gmuon quality for forward muons found only by mubac",qualitybins,qualitylow,qualityhigh,"quality","Events");
    fControlWeight_uncut = gHistogrammer->TH1DFactory("Muons_Control","Weight_uncut","uncut weight of #mu",weightbins,weightlow,weighthigh,"weight of #mu","Events");

    // control plots
    fControlProbForward = gHistogrammer->TH1DFactory("Muons_Control","ProbForward","forward #mu probability distribution",probbins,problow,probhigh,"forward #mu probability","Events");
    fControlProbBarrel = gHistogrammer->TH1DFactory("Muons_Control","ProbBarrel","barrel #mu probability distribution",probbins,problow,probhigh,"barrel #mu probability","Events");
    fControlProbRear = gHistogrammer->TH1DFactory("Muons_Control","ProbRear","rear #mu probability distribution",probbins,problow,probhigh,"rear #mu probability","Events");
    fControlEtaForward = gHistogrammer->TH1DFactory("Muons_Control","EtaForward","forward #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu,forward}","Events");
    fControlEtaBarrel = gHistogrammer->TH1DFactory("Muons_Control","EtaBarrel","barrel #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu,barrel}","Events");
    fControlEtaRear = gHistogrammer->TH1DFactory("Muons_Control","EtaRear","rear #mu #eta-distribution",etabins,etalow,etahigh,"#eta_{#mu,rear}","Events");
    fControlPForward = gHistogrammer->TH1DFactory("Muons_Control","PForward","forward #mu momentum",pbins,plow,phigh,"p_{#mu,forward} [GeV]","Events");
    fControlPBarrel = gHistogrammer->TH1DFactory("Muons_Control","PBarrel","barrel #mu momentum",pbins,plow,phigh,"p_{#mu,barrel} [GeV]","Events");
    fControlPRear = gHistogrammer->TH1DFactory("Muons_Control","PRear","rear #mu momentum",pbins,plow,phigh,"p_{#mu,rear} [GeV]","Events");
    fControlPtForward = gHistogrammer->TH1DFactory("Muons_Control","PtForward","forward transverse #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T,forward} [GeV]","Events");
    fControlPtBarrel = gHistogrammer->TH1DFactory("Muons_Control","PtBarrel","barrel transverse #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T,barrel} [GeV]","Events");
    fControlPtRear = gHistogrammer->TH1DFactory("Muons_Control","PtRear","rear transverse #mu momentum",ptbins,ptlow,pthigh,"p^{#mu}_{T,rear} [GeV]","Events");
    fControlChFlgForward = gHistogrammer->TH1DFactory("Muons_Control","ChFlgForward","forward #mu chamberflag",chflgbins,chflglow,chflghigh,"chamberflag","Events");
    fControlChFlgBarrel = gHistogrammer->TH1DFactory("Muons_Control","ChFlgBarrel","barrel #mu chamberflag",chflgbins,chflglow,chflghigh,"chamberflag","Events");
    fControlChFlgRear = gHistogrammer->TH1DFactory("Muons_Control","ChFlgRear","rear #mu chamberflag",chflgbins,chflglow,chflghigh,"chamberflag","Events");
    fControlMuonFinderForward = gHistogrammer->TH1DLabelFactory("Muons_Control","MuonFinderForward","Muon finder for forward #mu",muonfinder.Data(),"","Events");
    fControlMuonFinderBarrel = gHistogrammer->TH1DLabelFactory("Muons_Control","MuonFinderBarrel","Muon finder for barrel #mu",muonfinder.Data(),"","Events");
    fControlMuonFinderRear = gHistogrammer->TH1DLabelFactory("Muons_Control","MuonFinderRear","Muon finder for rear #mu",muonfinder.Data(),"","Events");
    fControlMuonMfproForward = gHistogrammer->TH1DFactory("Muons_Control","MfproForward","uncut probability of kalman filter for forward muons",mfprobins,mfprolow,mfprohigh,"probability","Events"); 
    fControlMuonMfproBarrel = gHistogrammer->TH1DFactory("Muons_Control","MfproBarrel","uncut probability of kalman filter for barrel muons",mfprobins,mfprolow,mfprohigh,"probability","Events"); 
    fControlMuonMfproRear = gHistogrammer->TH1DFactory("Muons_Control","MfproRear","uncut probability of kalman filter for rear muons",mfprobins,mfprolow,mfprohigh,"probability","Events"); 
    fControlMuonMfndfForward = gHistogrammer->TH1DFactory("Muons_Control","MfndfForward","uncut degrees of freedom of kalman filter for forward muons",mfndfbins,mfndflow,mfndfhigh,"degrees of freedom","Events");
    fControlMuonMfndfBarrel = gHistogrammer->TH1DFactory("Muons_Control","MfndfBarrel","uncut degrees of freedom of kalman filter for barrel muons",mfndfbins,mfndflow,mfndfhigh,"degrees of freedom","Events");
    fControlMuonMfndfRear = gHistogrammer->TH1DFactory("Muons_Control","MfndfRear","uncut degrees of freedom of kalman filter for rear muons",mfndfbins,mfndflow,mfndfhigh,"degrees of freedom","Events");
    fControlMuonMfzForward = gHistogrammer->TH1DFactory("Muons_Control","MfzForward","uncut internal camber requirement for forward muons",mfzbins,mfzlow,mfzhigh,"internal chamber requirement","Events");
    fControlMuonMfzBarrel = gHistogrammer->TH1DFactory("Muons_Control","MfzBarrel","uncut internal camber requirement for barrel muons",mfzbins,mfzlow,mfzhigh,"internal chamber requirement","Events");
    fControlMuonMfzRear = gHistogrammer->TH1DFactory("Muons_Control","MfzRear","uncut internal camber requirement for rear muons",mfzbins,mfzlow,mfzhigh,"internal chamber requirement","Events");
    fControlQualityForward = gHistogrammer->TH1DFactory("Muons_Control","QualityForward","gmuon quality for forward muons",qualitybins,qualitylow,qualityhigh,"quality","Events");
    fControlQualityBarrel = gHistogrammer->TH1DFactory("Muons_Control","QualityBarrel","gmuon quality for barrel muons",qualitybins,qualitylow,qualityhigh,"quality","Events");
    fControlQualityRear = gHistogrammer->TH1DFactory("Muons_Control","QualityRear","gmuon quality for rear muons",qualitybins,qualitylow,qualityhigh,"quality","Events");
    fControlQualityForwardBAC = gHistogrammer->TH1DFactory("Muons_Control","QualityForwardBAC","uncut gmuon quality for forward muons found only by mubac",qualitybins,qualitylow,qualityhigh,"quality","Events");
    fControlWeight = gHistogrammer->TH1DFactory("Muons_Control","Weight","weight of #mu",weightbins,weightlow,weighthigh,"weight of #mu","Events");
    fControlChamberFlag = gHistogrammer->TH2DFactory("Muons_Control","ChamberFlag","chamber-flag vs. fmufi for mpmatch candidates",chamberbins,chamberxlow,chamberxhigh,chamberbins,chamberylow,chamberyhigh,"muchid","fmufi(mumpmat)","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CreateFake() {
  //
  // create fakemuon histograms
  if ( gDebug ) cout << endl << "GMCs::CreateFake() called" << endl << endl;



    Int_t    pxbins     = 120;
    Double_t pxlow      = -15.;
    Double_t pxhigh     = 15.;
    Int_t    pzbins     = 30;
    Double_t pzlow      = -15.;
    Double_t pzhigh     = 15.;
    Int_t    ptbins     = 30;
    Double_t ptlow      = 0.;
    Double_t pthigh     = 15.;
    Int_t    etabins    = 40;
    Double_t etalow     = -4.;
    Double_t etahigh    = 4.;
    Int_t    phibins    = 36;   
    Double_t philow     = -TMath::Pi();    
    Double_t phihigh    =  TMath::Pi();
    Int_t    motherbins = 3000;
    Double_t motherlow  = 0;
    Double_t motherhigh = 3000;    
    Int_t    decaydist_bins = 200;
    Double_t decaydistlow   = 0;
    Double_t decaydisthigh  = 400;
    Int_t    deltaptbins    = 40;
    Double_t deltaptlow     = -2;
    Double_t deltapthigh    =  2;
    Int_t      fakePtNBins    = 6; 
    Double_t   fakePtBins[fakePtNBins+1];
    fakePtBins[0]  = 1.5;
    fakePtBins[1]  = 2.0;
    fakePtBins[2]  = 3.0;
    fakePtBins[3]  = 4.0;
    fakePtBins[4]  = 6.0;
    fakePtBins[5]  = 10.0;
    fakePtBins[6]  = 15.0;

    Int_t      fakeEtaNBins   = 8;
    Double_t   fakeEtaBins[fakeEtaNBins+1];
    fakeEtaBins[0]  = -2.4;
    fakeEtaBins[1]  = -1.6;
    fakeEtaBins[2]  = -1.1;
    fakeEtaBins[3]  = -0.75;
    fakeEtaBins[4]  =  0.25;
    fakeEtaBins[5]  =  0.75;
    fakeEtaBins[6]  =  1.3;
    fakeEtaBins[7]  =  2.3;
    fakeEtaBins[8]  =  3.0;


   fMuonProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");

  //----------------------------------------------------------------------

 fPt_fakebin                =  gHistogrammer->TH1DFactory("Fake","RecMuonPt","Pt of Muon ",ptbins,ptlow,pthigh,"Pt_{rec}","Events");
  fEta_lowPt_fakebin               =  gHistogrammer->TH1DFactory("Fake","RecMuonEta_lowPt","Eta of Muon low pt ",etabins,etalow,etahigh,"Eta_{rec}","Events");
 fEta_highPt_fakebin        =  gHistogrammer->TH1DFactory("Fake","RecMuonEta_highPt","Eta of Muon high pt",etabins,etalow,etahigh,"Eta_{rec}","Events");
 fPhi_lowPt_fakebin           =  gHistogrammer->TH1DFactory("Fake","RecMuonPhi_lowPt","phi of Muon low pt",phibins,philow,phihigh,"Phi_{rec}","Events");
  fPhi_highPt_fakebin          =  gHistogrammer->TH1DFactory("Fake","RecMuonPhi_highPt","Phi of  Muon high pt",phibins,philow,phihigh,"Phi_{rec}","Events");

  //----------------------------------------------------------------------------------------
    if (gCards->GetProduceFakeMuon() ) {
   fMuonDecayProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonDecayProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonDecayProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonDecayProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonDecayProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonDecayProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonDecayProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonDecayProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonDecayProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonDecayProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  //----------------------------------------------------------------------------------------
   fMuonDecayPionProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonDecayPionProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonDecayPionProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonDecayPionProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonDecayPionProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonDecayPionProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonDecayPionProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonDecayPionProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonDecayPionProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonDecayPionProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  //----------------------------------------------------------------------------------------
   fMuonDecayKaonProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonDecayKaonProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonDecayKaonProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonDecayKaonProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonDecayKaonProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonDecayKaonProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonDecayKaonProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonDecayKaonProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonDecayKaonProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonDecayKaonProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  //----------------------------------------------------------------------------------------
   fMuonPunchProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonPunchProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonPunchProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonPunchProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonPunchProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonPunchProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonPunchProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonPunchProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonPunchProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonPunchProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  //----------------------------------------------------------------------------------------
   fMuonPunchPionProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonPunchPionProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonPunchPionProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonPunchPionProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonPunchPionProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonPunchPionProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonPunchPionProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonPunchPionProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonPunchPionProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonPunchPionProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  //----------------------------------------------------------------------------------------
   fMuonPunchKaonProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","MuonPunchKaonProbabilityPt","Muon Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{rec}","Muon Probability");
  fMuonPunchKaonProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","MuonPunchKaonProbabilityEtalow","MuonProbability Eta dependence low pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonPunchKaonProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","MuonPunchKaonProbabilityPhilow","Muon Probability Phi dependence low phi ",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");
  fMuonPunchKaonProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","MuonPunchKaonProbabilityEtahigh","MuonProbability Eta dependence high pt ",etabins,etalow,etahigh,"Eta_{rec}","Muon Probability");
  fMuonPunchKaonProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","MuonPunchKaonProbabilityPhihigh","Muon Probability Phi dependence high pt",phibins,philow,phihigh,"Phi_{rec}","Muon Probability");

  //--------------------------------------------------------------------------------------------------
      fFakePxvsPxMCTRUE = gHistogrammer->TH2DFactory("Fake","PxvsPxMCTRUE_fake","fake px #mu  vs.  true px #mu  from MC info",pxbins,pxlow,pxhigh,pxbins,pxlow,pxhigh,"p_{x}^{#mu} [GeV]","p_{x}^{#mu,true} [GeV]","Events");
      fFakePyvsPyMCTRUE = gHistogrammer->TH2DFactory("Fake","PyvsPyMCTRUE_fake","fake py #mu momentum vs.  true py #mu from MC info",pxbins,pxlow,pxhigh,pxbins,pxlow,pxhigh,"p_{y}^{#mu} [GeV]","p_{y}^{#mu,true} [GeV]","Events");
      fFakePzvsPzMCTRUE = gHistogrammer->TH2DFactory("Fake","PzvsPzMCTRUE_fake","fake pz #mu vs.  true pz #mu  from MC info",pzbins,pzlow,pzhigh,pzbins,pzlow,pzhigh,"p_{z}^{#mu} [GeV]","p_{z}^{#mu,true} [GeV]","Events");
      fFakePtvsPtMCTRUE = gHistogrammer->TH2DFactory("Fake","PtvsPtMCTRUE_fake","fake pt #mu  vs.  true pt #mu from MC info",ptbins,ptlow,pthigh,ptbins,ptlow,pthigh,"p_{t}^{#mu} [GeV]","p_{t}^{#mu,true} [GeV]","Events");
      fFakeEtavsEtaMCTRUE = gHistogrammer->TH2DFactory("Fake","EtavsEtaMCTRUE_fake","fake Eta #mu  vs.  true Eta #mu from MC info",etabins,etalow,etahigh,etabins,etalow,etahigh,"#eta^{#mu} ","#eta^{#mu,true} ","Events");
 fFakeMuonAllPt                =  gHistogrammer->TH1DFactory("Fake","FakeMuonAllPt","Pt of Fake Muon ",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeMuonAllEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","FakeMuonAllEtalowPt","Eta of Fake Muon ",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeMuonAllPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","FakeMuonAllPhilowPt","Phi of Fake Muon ",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeMuonAllEta_highPt               =  gHistogrammer->TH1DFactory("Fake","FakeMuonAllEtahighPt","Eta of Fake Muon ",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeMuonAllPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","FakeMuonAllPhihighPt","Phi of Fake Muon ",phibins,philow,phihigh,"Phi_{true}","Events");
  //--------
  fFakePunchMuonPt                =  gHistogrammer->TH1DFactory("Fake","PunchMuonPt","Pt of Fake Muon FakePunch",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakePunchMuonEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonEtalowPt","Eta of Fake Muon ",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakePunchMuonPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonPhilowPt","Phi of Fake Muon ",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakePunchMuonEta_highPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonEtahighPt","Eta of Fake Muon ",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakePunchMuonPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonPhihighPt","Phi of Fake Muon ",phibins,philow,phihigh,"Phi_{true}","Events");

  fFakeDecayMuonPt                =  gHistogrammer->TH1DFactory("Fake","DecayMuonPt","Pt of Fake Muon",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeDecayMuonEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonEtalowPt","Eta of Fake Muon ",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeDecayMuonPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonPhilowPt","Phi of Fake Muon ",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeDecayMuonEta_highPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonEtahighPt","Eta of Fake Muon ",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeDecayMuonPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonPhihighPt","Phi of Fake Muon ",phibins,philow,phihigh,"Phi_{true}","Events");

  fFakeMuonPionPt                =  gHistogrammer->TH1DFactory("Fake","MuonPionPt","Pt of Fake Muon Pion",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeMuonPionEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","MuonPionEtalowPt","Eta of Fake Muon Pion",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeMuonPionPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","MuonPionPhilowPt","Phi of Fake Muon Pion",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeMuonPionEta_highPt               =  gHistogrammer->TH1DFactory("Fake","MuonPionEtahighPt","Eta of Fake Muon Pion",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeMuonPionPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","MuonPionPhihighPt","Phi of Fake Muon Pion",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeMuonKaonPt                =  gHistogrammer->TH1DFactory("Fake","MuonKaonPt","Pt of Fake Kaon Pion",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeMuonKaonEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","MuonKaonEtalowPt","Eta of Kaon Muon Pion",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeMuonKaonPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","MuonKaonPhilowPt","Phi of Kaon Muon Pion",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeMuonKaonEta_highPt               =  gHistogrammer->TH1DFactory("Fake","MuonKaonEtahighPt","Eta of Kaon Muon Pion",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeMuonKaonPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","MuonKaonPhihighPt","Phi of Kaon Muon Pion",phibins,philow,phihigh,"Phi_{true}","Events");
  //-------- decay plots

 fFakeDecayMuonPionPt                =  gHistogrammer->TH1DFactory("Fake","DecayMuonPionPt","Pt of Fake Muon Pion  from decay",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeDecayMuonPionEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonPionEtalowPt","Eta of Fake Muon Pion  from decay",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeDecayMuonPionPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonPionPhilowPt","Phi of Fake Muon Pion  from decay",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeDecayMuonPionEta_highPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonPionEtahighPt","Eta of Fake Muon Pion  from decay",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeDecayMuonPionPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonPionPhihighPt","Phi of Fake Muon Pion  from decay",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeDecayMuonKaonPt                =  gHistogrammer->TH1DFactory("Fake","DecayMuonKaonPt","Pt of Fake Kaon Pion  from decay",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeDecayMuonKaonEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonKaonEtalowPt","Eta of Kaon Muon Pion  from decay",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeDecayMuonKaonPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonKaonPhilowPt","Phi of Kaon Muon Pion  from decay",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeDecayMuonKaonEta_highPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonKaonEtahighPt","Eta of Kaon Muon Pion  from decay",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeDecayMuonKaonPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","DecayMuonKaonPhihighPt","Phi of Kaon Muon Pion from decay",phibins,philow,phihigh,"Phi_{true}","Events");
  //--------

 fFakePunchMuonPionPt                =  gHistogrammer->TH1DFactory("Fake","PunchMuonPionPt","Pt of Fake Muon Pion from Punch through",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakePunchMuonPionEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonPionEtalowPt","Eta of Fake Muon Pion from Punch through",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakePunchMuonPionPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonPionPhilowPt","Phi of Fake Muon Pion from Punch through",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakePunchMuonPionEta_highPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonPionEtahighPt","Eta of Fake Muon Pion from Punch through",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakePunchMuonPionPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonPionPhihighPt","Phi of Fake Muon Pion from Punch through",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakePunchMuonKaonPt  =  gHistogrammer->TH1DFactory("Fake","PunchMuonKaonPt","Pt of Fake Kaon Pion from Punch through",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakePunchMuonKaonEta_lowPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonKaonEtalowPt","Eta of Kaon Muon Pion from Punch through",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakePunchMuonKaonPhi_lowPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonKaonPhilowPt","Phi of Kaon Muon Pion from Punch through",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakePunchMuonKaonEta_highPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonKaonEtahighPt","Eta of Kaon Muon Pion from Punch through",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakePunchMuonKaonPhi_highPt               =  gHistogrammer->TH1DFactory("Fake","PunchMuonKaonPhihighPt","Phi of Kaon Muon Pion from Punch through",phibins,philow,phihigh,"Phi_{true}","Events");
 fRecTrueMuonMother     = gHistogrammer->TH1DFactory("Fake","RecTrueMuonMother","Partid of true muon mother (no pi/K decay)",motherbins,motherlow,motherhigh,"fmckin_partyp","events");
  //------------------------------------------------------------------------

  fPrec_PtruevsDecdistPion_rear = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistPionr","Pt_rec-pt_true vs decay distance rear region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistPion_central = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistPionc","Pt_rec-pt_true vs decay distance central region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistPion_forward = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistPionf","Pt_rec-pt_true vs decay distance forward region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistKaon_rear = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistKaonr","Pt_rec-pt_true vs decay distance rear region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistKaon_central = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistKaonc","Pt_rec-pt_true vs decay distance central region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistKaon_forward = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistKaonf","Pt_rec-pt_true vs decay distance forward region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistMuon_rear = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistMuonr","Pt_rec-pt_true vs decay distance rear region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistMuon_central = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistMuonc","Pt_rec-pt_true vs decay distance central region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");
  fPrec_PtruevsDecdistMuon_forward = gHistogrammer->TH2DFactory("Fake","Prec-PtruevsDecdistMuonf","Pt_rec-pt_true vs decay distance forward region",decaydist_bins,decaydistlow,decaydisthigh,deltaptbins,deltaptlow,deltapthigh,"Decay Distance","Delta Pt","Events");

  //-----------------------------------------------------------------
  // fFake2DMuonAll_PtEta   = gHistogrammer->TH2DFactory("Fake","Fake2DMuonAll_PtEta","Pt vs Eta for all fakes",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  //fFake2DMuonDecay_PtEta = gHistogrammer->TH2DFactory("Fake","Fake2DMuonDecay_PtEta","Pt vs Eta for decay fakes",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  //fFake2DMuonPunch_PtEta = gHistogrammer->TH2DFactory("Fake","Fake2DMuonPunch_PtEta","Pt vs Eta for punch+missmatch fakes",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  // fProbability2DMuonAll_PtEta   = gHistogrammer->TH2DFactory("Fake","FakeProbability2DMuonAll_PtEta","Pt vs Eta for all fakes",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  // fProbability2DMuonDecay_PtEta = gHistogrammer->TH2DFactory("Fake","FakeProbability2DMuonDecay_PtEta","Pt vs Eta for decay fakes",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  // fProbability2DMuonPunch_PtEta = gHistogrammer->TH2DFactory("Fake","FakeProbability2DMuonPunch_PtEta","Pt vs Eta for punch+missmatch fakes",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
 fFake2DMuonAll_PtEta   = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonAll_PtEta","Pt vs Eta for all fakes",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
fFake2DMuonAll_PtEta   = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonAll_PtEta","Pt vs Eta for all fakes",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
fFake2DMuonAll_PtEta_Bremat   = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonAll_PtEta_Bremat","Pt vs Eta for all fakes from Bremat",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
fFake2DMuonAll_PtEta_MPMatch   = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonAll_PtEta_MPMatch","Pt vs Eta for all fakes from MPMatch",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
fFake2DMuonAll_PtEta_Bac   = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonAll_PtEta_MuBac","Pt vs Eta for all fakes from MuBac",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fFake2DMuonDecay_PtEta = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonDecay_PtEta","Pt vs Eta for decay fakes ",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fFake2DMuonPunch_PtEta = gHistogrammer->TH2DVarFactory("Fake","Fake2DMuonPunch_PtEta","Pt vs Eta for punch+missmatch fakes",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fProbability2DMuonAll_PtEta   = gHistogrammer->TH2DVarFactory("Fake","FakeProbability2DMuonAll_PtEta","Pt vs Eta for all fakes",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fFake2DProbMuonAll_PtEta_Bremat   = gHistogrammer->TH2DVarFactory("Fake","FakeProbability2DMuonAll_PtEta_Bremat","Pt vs Eta for all fakes from Bremat",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fFake2DProbMuonAll_PtEta_MPMatch   = gHistogrammer->TH2DVarFactory("Fake","FakeProbability2DMuonAll_PtEta_MPMatch","Pt vs Eta for all fakes from MPMatch",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fFake2DProbMuonAll_PtEta_Bac   = gHistogrammer->TH2DVarFactory("Fake","FakeProbability2DMuonAll_PtEta_Bac","Pt vs Eta for all fakes from Bac",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fProbability2DMuonDecay_PtEta = gHistogrammer->TH2DVarFactory("Fake","FakeProbability2DMuonDecay_PtEta","Pt vs Eta for decay fakes",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
 fProbability2DMuonPunch_PtEta = gHistogrammer->TH2DVarFactory("Fake","FakeProbability2DMuonPunch_PtEta","Pt vs Eta for punch+missmatch fakes",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");


 //----------------------------------------------------------------------------------

 fFakeProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityAllPt","Fake Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","FakeProbabilityAllEtalow","Fake Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityAllPhilow","Fake Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","FakeProbabilityAllEtahigh","Fake Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityAllPhihigh","Fake Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
 
fFakePionProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityPionAllPt","Fake Muon from Pion Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakePionProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","FakeProbabilityPionAllEtalow","Fake Muon from Pion Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakePionProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityPionAllPhilow","Fake Muon from Pion Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakePionProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","FakeProbabilityPionAllEtahigh","Fake Muon from Pion Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakePionProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityPionAllPhihigh","Fake Muon from Pion Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
 
fFakeKaonProbabilityAllPt         =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityKaonAllPt","Fake Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeKaonProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("Fake","FakeProbabilityKaonAllEtalow","Fake Muon from Kaon Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeKaonProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityKaonAllPhilow","Fake Muon from Kaon Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeKaonProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("Fake","FakeProbabilityKaonAllEtahigh","Fake Muon from Kaon Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeKaonProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("Fake","FakeProbabilityKaonAllPhihigh","Fake Muon from Kaon Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
 

  }
  return kTRUE;
}



//_____________________________________________________________

Bool_t GMuons::Fill() {
  //
  // fill muons in clonesarray and perfom cut check
  if ( gDebug ) cout << endl << "GMuons::Fill() called" << endl << endl;

  TClonesArray &muons = *fMuons;

  Int_t end = gData->Getnmu();

  for ( Int_t i = 0; i < end; i++ ) {
    GMuon *muon = 0;
    muon = new(muons[fNMuons++]) GMuon(i+1,kNowhere,                                                                                                                             gData->Getmuqual(i),gData->Getmucharge(i),                                                                                                gData->Getmup(i,0)   , gData->Getmup(i,1)    , gData->Getmup(i,2) ,                                                                       gData->Getmuperr(i) , gData->Getmutrfl(i)   , gData->Getmutrid(i) ,                                                                       gData->Getmuvcid(i) , gData->Getmuvtxfl(i)  , gData->Getmuvtxid(i),                                                                       gData->Getmuglomu(i), gData->Getmubremat(i) , gData->Getmubacmat(i),                                                                      gData->Getmumubac(i), gData->Getmumamma(i)  , gData->Getmumpmat(i),                                                                       gData->Getmumufo(i) , gData->Getmumip(i)    , gData->Getmumv(i),                                                                          gData->Getmuztid(i),  gData->Getmucalfl(i)  , gData->Getmuhac2(i),                                                                        gData->Getmuzufid(i), gData->Getmupmip(i)   , gData->Getmuchfl(i),                                                                        gData->Getmuchid(i),  gData->Getmupmat(i)   , gData->Getmubacfl(i),                                                                       gData->Getmubacid(i), gData->Getmunphi(i)   , gData->Getmujetfl(i),                                                                       gData->Getmujetid_a(i), gData->Getmujetdr_a(i), gData->Getmujetpt(i),                                                                     gData->Getmutruefl(i) , gData->Getmudecdist(i));
    // remove filled muon object if not ok, else perform cut checks
    if ( !muon->IsOK() ) {
      muons.RemoveAt(fNMuons-1);
      fNMuons -= 1;
    } else {

      // add mc info
      if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	gMCs->AddMuonMCInfo(muon,gData->Getmuick(i),gData->Getmupartyp(i),
			    gData->Getmumc_p(i,0),gData->Getmumc_p(i,1),gData->Getmumc_p(i,2),gData->Getmumc_p(i,3),
			    gData->Getmuqtyp(i),
			    gData->Getmumc_q(i,0),gData->Getmumc_q(i,1),gData->Getmumc_q(i,2),gData->Getmumc_q(i,3),
			    gData->Getmudirtyp(i),
			    gData->Getmumc_d(i,0),gData->Getmumc_d(i,1),gData->Getmumc_d(i,2),gData->Getmumc_d(i,3));
      }
      CheckForwardTrackMuon(muon);
      ModifyMuonQuality(muon);
      CheckEtaCut(muon);
      CheckTakeCut(muon);
      CheckFinderCut(muon);
      CheckQualityCut(muon);
      CheckPCut(muon);
      CheckPtCut(muon);
      CheckBrematCut(muon);
      CheckMPMatchCut(muon);
      CheckMUBACCut(muon);
      CheckForwardTrackMuonCut(muon);
      CheckBACFQualityCut(muon);
      CheckVcidLowCut(muon);
      CheckVcidUpCut(muon);
      CheckMVCuts(muon);
      CheckOnlyVertexFittedCut(muon);
      CheckAllCuts(muon);
      CheckEfficiencyCorrection(muon);
      CalcBeamSpotImpactParameter(muon);
      CalcMuonIsolation(muon);
      CalcMuonJetMass(muon);
      CalcMuonImpactParameter(muon);
      FillMuonNdofandZ(muon);
    }
  }

  // redo MC cut checks because list has changed
  if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
    gMCs->CheckAllCuts();
  }
  if ( gCards->GetMC() && gCards->GetMCLF() && gCards->GetDoFake() && gTracks->GetFakeMuCand()!= 0) {
    GMuon *muon = 0;
    
    
    muon = new(muons[fNMuons++])GMuon(fNMuons+1,kNowhere,99,int(gTracks->GetFakeMuCand()->Charge()),gTracks->GetFakeMuCand()->Px(),gTracks->GetFakeMuCand()->Py(),gTracks->GetFakeMuCand()->Pz(),0.,1,gTracks->GetFakeMuCand()->GetID(),gTracks->GetFakeMuCand()->GetID(),gTracks->GetFakeMuCand()->GetID(),0,gTracks->GetFakeMuCand()->GetVertexID(),50,50,50,50,50,50,50,50,50,0,0.,0,0.,0,0,0.,0,0,0,0,0,0.,0.,0,0.);
    // cout << " muon->GetTrackID() "<< muon->GetTrackID() << endl;
    if ( !muon->IsOK() ) {
      muons.RemoveAt(fNMuons-1);
      fNMuons -= 1;
    }
    
    
    if( FakeAlreadyStored(muon)){
      muons.RemoveAt(fNMuons-1);
      fNMuons -= 1;
    }
    else{
      muon->AssociateJetByDeltaR();
      // CheckForwardTrackMuon(muon);// ->looks for chamberflag
      ModifyMuonQuality(muon); // -> never changed if 99
      CheckEtaCut(muon); //       ->Set type forw/barrel/rear
      CheckTakeCut(muon);//       ->Cut auf FMUON takeevent 
      CheckFinderCut(muon); // ->immer true muesste man beim erzeugen der WS beachten
      CheckQualityCut(muon); //->is ok quality/pt schnitt
      CheckPCut(muon);
      CheckPtCut(muon);
      CheckBrematCut(muon); // always true ??
      CheckMPMatchCut(muon);// always true ??
      CheckForwardTrackMuonCut(muon); // ->only applied if CheckForwardTrackMuon
      CheckBACFQualityCut(muon); //   
      CheckVcidLowCut(muon);
      CheckVcidUpCut(muon);
      CheckMVCuts(muon);  // set to true 
      CheckOnlyVertexFittedCut(muon); // ???
      CheckAllCuts(muon);
      CheckEfficiencyCorrection(muon);// ->SetWeight aus effcor 
      CalcBeamSpotImpactParameter(muon); // warum impactpar nur von ztt
      CalcMuonIsolation(muon);
      CalcMuonImpactParameter(muon);
      CalcMuonJetMass(muon);
      FillMuonNdofandZ(muon);
    }
  }  
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMuons::FakeAlreadyStored(GMuon *muon) {
  //
  Bool_t flag = kFALSE;
  // check eta cut and define region for muon
  if ( gDebug ) cout << endl << "GMuons::FakeAlreadyStored() called" << endl << endl;
  for ( Int_t i = 0; i < fNMuons-1; i++ ) {
    GMuon *muon2 = ((GMuon*)(fMuons->At(i)));
    //    cout << " muon2->GetTrackID() "<< muon2->GetTrackID() << endl;
    if (muon->GetTrackID()==muon2->GetTrackID()){
      flag = kTRUE;
    }

  }
  //  cout << "flag " << flag << endl;
  return flag;
}

//_____________________________________________________________

Bool_t GMuons::CheckEtaCut(GMuon *muon) {
  //
  // check eta cut and define region for muon
  if ( gDebug ) cout << endl << "GMuons::CheckEtaCut() called" << endl << endl;

  if ( ( muon->Eta() >= gCards->GetFMUONEtaLow() ) && ( muon->Eta() <= gCards->GetFMUONEtaUp() ) ) {
    muon->SetEtaCut(kTRUE);
    muon->SetType(kForward);
  } else if ( ( muon->Eta() >= gCards->GetBMUONEtaLow() ) && ( muon->Eta() <= gCards->GetBMUONEtaUp() ) ) {
    muon->SetEtaCut(kTRUE);
    muon->SetType(kBarrel);
  } else if ( ( muon->Eta() >= gCards->GetRMUONEtaLow() ) && ( muon->Eta() <= gCards->GetRMUONEtaUp() ) ) {
    muon->SetEtaCut(kTRUE);
    muon->SetType(kRear);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckTakeCut(GMuon *muon) {
  //
  // check take cut of fmuon chambers
  if ( gDebug ) cout << endl << "GMuons::CheckTakeCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    if ( gRuns->CheckFMUTake() ) {
      muon->SetTakeCut(kTRUE);
    } else {
      muon->SetTakeCut(kFALSE);
    }
  } else {
    muon->SetTakeCut(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckEfficiencyCorrection(GMuon *muon) {
  //
  // check efficienciy correction for muon
  if ( gDebug ) cout << endl << "GMuons::CheckEfficiencyCorrection() called" << endl << endl;

//   cout << gMuonEfficiency->PrintEfficiencyInfo(muon) << endl;
  muon->SetWeight(gMuonEfficiency->GetWeight(muon));

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckFinderCut(GMuon *muon) {
  //
  // muon finder bits:
  // 0: glomu
  // 1: bremat
  // 2: mubac
  // 3: mamma
  // 4: mpmatch
  // 5: mufo
  // 6: mip
  // 7: mv
  //
  if ( gDebug ) cout << endl << "GMuons::CheckFinderCut() called" << endl << endl;

  Bool_t result = kFALSE;

  if ( muon->GetType() == kForward ) {
    
    // check "and" requirements
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,0))
      result = result || muon->GetGlomu();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,1))
      result = result || muon->GetBremat();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,2))
      result = result || muon->GetMuBac();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,3))
      result = result || muon->GetMamma();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,4))
      result = result || muon->GetMPMatch();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,5))
      result = result || muon->GetMufo();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,6))
      result = result || muon->GetMip();
    if (gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,7))
      result = result || muon->GetMv();

    muon->SetFinderCut(result);

  } else if ( muon->GetType() == kBarrel ) {
    
    // check "and" requirements
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,0))
      result = result || muon->GetGlomu();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,1))
      result = result || muon->GetBremat();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,2))
      result = result || muon->GetMuBac();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,3))
      result = result || muon->GetMamma();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,4))
      result = result || muon->GetMPMatch();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,5))
      result = result || muon->GetMufo();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,6))
      result = result || muon->GetMip();
    if (gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,7))
      result = result || muon->GetMv();

    muon->SetFinderCut(result);

  } else if ( muon->GetType() == kRear ) {
    
    // check "and" requirements
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,0))
      result = result || muon->GetGlomu();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,1))
      result = result || muon->GetBremat();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,2))
      result = result || muon->GetMuBac();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,3))
      result = result || muon->GetMamma();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,4))
      result = result || muon->GetMPMatch();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,5))
      result = result || muon->GetMufo();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,6))
      result = result || muon->GetMip();
    if (gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,7))
      result = result || muon->GetMv();

    muon->SetFinderCut(result);

  }
  if (muon->GetQuality()== 99) muon->SetFinderCut(kTRUE); 
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckQualityCut(GMuon *muon) {
  //
  // check tow pairs of quality-p_T cuts separate for the three different muon regions
  if ( gDebug ) cout << endl << "GMuons::CheckQualityCut() called" << endl << endl;

  Bool_t result = kFALSE;

  if ( muon->GetType() == kForward ) {
    if ( muon->GetQuality() >= gCards->GetFMUONQualCut1() ) {
      if ( muon->Pt() >= gCards->GetFMUONPTCut1() ) {
	result = kTRUE;
      }
    } else if ( muon->GetQuality() >= gCards->GetFMUONQualCut2() ) {
      if ( muon->Pt() >= gCards->GetFMUONPTCut2() ) {
	result = kTRUE;
      }
    } 
  } else if ( muon->GetType() == kBarrel ) {
    if ( muon->GetQuality() >= gCards->GetBMUONQualCut1() ) {
      if ( muon->Pt() >= gCards->GetBMUONPTCut1() ) {
	result = kTRUE;
      }
    } else if ( muon->GetQuality() >= gCards->GetBMUONQualCut2() ) {
      if ( muon->Pt() >= gCards->GetBMUONPTCut2() ) {
	result = kTRUE;
      }
    } 
  } else if ( muon->GetType() == kRear ) {
    if ( muon->GetQuality() >= gCards->GetRMUONQualCut1() ) {
      if ( muon->Pt() >= gCards->GetRMUONPTCut1() ) {
	result = kTRUE;
      }
    } else if ( muon->GetQuality() >= gCards->GetRMUONQualCut2() ) {
      if ( muon->Pt() >= gCards->GetRMUONPTCut2() ) {
	result = kTRUE;
      }
    } 
  }

  muon->SetQualityCut(result);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckPCut(GMuon *muon) {
  //
  // check p cut
  if ( gDebug ) cout << endl << "GMuons::CheckPCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    if ( muon->P() >= gCards->GetFMUONP() )
      muon->SetPCut(kTRUE);
  } else if ( muon->GetType() == kBarrel ) {
    if ( muon->P() >= gCards->GetBMUONP() )
      muon->SetPCut(kTRUE);
  } else if ( muon->GetType() == kRear ) {
    if ( muon->P() >= gCards->GetRMUONP() )
      muon->SetPCut(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckPtCut(GMuon *muon) {
  //
  // check pt cut
  if ( gDebug ) cout << endl << "GMuons::CheckPtCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    if ( muon->Pt() >= gCards->GetFMUONPt() )
      muon->SetPtCut(kTRUE);
  } else if ( muon->GetType() == kBarrel ) {
    if ( muon->Pt() >= gCards->GetBMUONPt() )
      muon->SetPtCut(kTRUE);
  } else if ( muon->GetType() == kRear ) {
    if ( muon->Pt() >= gCards->GetRMUONPt() )
      muon->SetPtCut(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckBrematCut(GMuon *muon) {
  //
  // check BREMAT specific cuts
  if ( gDebug ) cout << endl << "GMuons::CheckBrematCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    // check if bremat requirement is activated
    if ( gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,1)) {
      // check if muon is found by bremat
      if ( muon->GetBremat() ) {
	if ( (muon->GetProbability() >= gCards->GetMUONBremProb() ) && 
	     (muon->GetProbability() <= 1. ) ) {
	  if ( gCards->GetMUONBremChamberFlag() > -99 ) {
	    if ( TMath::Abs(muon->GetChamberFlag()) == gCards->GetMUONBremChamberFlag() ) {
	      muon->SetBrematCut(kTRUE);
	    }
	  } else {
	    muon->SetBrematCut(kTRUE);
	  }
	}
      }
    }
  } else if ( muon->GetType() == kBarrel ) {
    // check if bremat requirement is activated
    if ( gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,1) ) {
      // check if muon is found by bremat
      if ( muon->GetBremat() ) {
	if ( ( muon->GetProbability() >= gCards->GetMUONBremProb() ) && 
	     ( muon->GetProbability() <= 1. ) ) {
	  if ( gCards->GetMUONBremChamberFlag() > -99 ) {
	    if ( TMath::Abs(muon->GetChamberFlag()) == gCards->GetMUONBremChamberFlag()) {
	      muon->SetBrematCut(kTRUE);
	    }
	  } else {
	    muon->SetBrematCut(kTRUE);
	  }
	}
      }
    }
  } else if ( muon->GetType() == kRear ) {
    // check if bremat requirement is activated
    if ( gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,1) ) {
      // check if muon is found by bremat
      if ( muon->GetBremat() ) {
	if ( (muon->GetProbability() >= gCards->GetMUONBremProb() ) && 
	     (muon->GetProbability() <= 1. ) ) {
	  if ( gCards->GetMUONBremChamberFlag() > -99 ) {
	    if (muon->GetChamberFlag()==gCards->GetMUONBremChamberFlag()) {
	      muon->SetBrematCut(kTRUE);
	    }
	  } else {
	    muon->SetBrematCut(kTRUE);
	  }
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckMPMatchCut(GMuon *muon) {
  //
  // check MPMATCH specific cuts
  if ( gDebug ) cout << endl << "GMuons::CheckMPMatchCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    // check if mpmatch requirement is activated
    if ( gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,4) ) {
      // check if muon is found by mpmatch
      if ( muon->GetMPMatch() ) {
	// prob cut
	if ( ( muon->GetProbability() >= gCards->GetMUONMPMProb() ) && 
	     ( muon->GetProbability() <= 1. ) ) {
	  muon->SetMPMatchCut(kTRUE);
	}
      }
    }
  } else if ( muon->GetType() == kBarrel ) {
    // check if mpmatch requirement is activated
    if ( gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,4) ) {
      // check if muon is found by mpmatch
      if ( muon->GetMPMatch() ) {
	if ( ( muon->GetProbability() >= gCards->GetMUONMPMProb() ) && 
	     ( muon->GetProbability() <= 1. ) ) {
	  muon->SetMPMatchCut(kTRUE);
	}
      }
    }
  } else if ( muon->GetType() == kRear ) {
    // check if mpmatch requirement is activated
    if ( gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,4) ) {
      // check if muon is found by mpmatch
      if ( muon->GetMPMatch() ) {
	if ( ( muon->GetProbability() >= gCards->GetMUONMPMProb() ) && 
	     ( muon->GetProbability() <= 1. ) ) {
	  muon->SetMPMatchCut(kTRUE);
	}
      }
    }
  }
  if (muon->GetQuality()== 99) muon->SetBrematCut(kTRUE);
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckMUBACCut(GMuon *muon) {
  //
  // check MUBAC specific cuts
  if ( gDebug ) cout << endl << "GMuons::CheckMUBACCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    // check if mubac requirement is activated
    if ( gCards->GetFMUONFinder() & (Int_t)TMath::Power(2,2) ) {
      // check if muon is found by MUBAC
      if ( muon->GetMuBac() ) {
	// bac flag cut
	if ( muon->GetBacFlag() < gCards->GetMUONMUBACBacFlag() ) {
	  muon->SetMUBACCut(kTRUE);
	}
      }
    }
  } else if ( muon->GetType() == kBarrel ) {
    // check if MUBAC requirement is activated
    if ( gCards->GetBMUONFinder() & (Int_t)TMath::Power(2,2) ) {
      // check if muon is found by MUBAC
      if ( muon->GetMuBac() ) {
	// bac flag cut
	if ( muon->GetBacFlag() < gCards->GetMUONMUBACBacFlag() ) {
	  muon->SetMUBACCut(kTRUE);
	}
      }
    }
  } else if ( muon->GetType() == kRear ) {
    // check if MUBAC requirement is activated
    if ( gCards->GetRMUONFinder() & (Int_t)TMath::Power(2,2) ) {
      // check if muon is found by MUBAC
      if ( muon->GetMuBac() ) {
	// bac flag cut
	if ( muon->GetBacFlag() < gCards->GetMUONMUBACBacFlag() ) {
	  muon->SetMUBACCut(kTRUE);
	}
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckForwardTrackMuonCut(GMuon *muon) {
  //
  // check forward muon specific cuts
  if ( gDebug ) cout << endl << "GMuons::CheckForwardTrackMuonCut() called" << endl << endl;

  if ( muon->GetForwardTrackMuon() ) {
    // cut on fmufi entry if fmufi is reasonable, only 10 entries filled in special blocks
    if ( (muon->GetFmufiCID() >= 0) && (muon->GetFmufiCID() < 10) ) {
      if ( ( gData->Getmfpro(muon->GetFmufiCID()) >= gCards->GetMUONMfpro() ) && 
	   ( gData->Getmfpro(muon->GetFmufiCID()) <= 1. ) ) {
	// kalman filter degrees of freedom
	if ( gData->Getmfndf(muon->GetFmufiCID()) >= gCards->GetMUONMfndf() ) {
	  // track must start from internal plane
	  if ( gData->Getmfz(muon->GetFmufiCID()) <= gCards->GetMUONMfz() ) {
	    muon->SetForwardTrackMuonCut(kTRUE);
	  }
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckBACFQualityCut(GMuon *muon) {
  //
  // check quality cut for forward muons only found by mubac (chamber-flag = 0)
  if ( gDebug ) cout << endl << "GMuons::CheckBACFQualityCut() called" << endl << endl;

  // identify forward muon found only by mubac
  if ( (muon->GetType() == kForward) && muon->GetMuBac() && (muon->GetChamberFlag() == 0) )
    muon->SetBACFMuon(kTRUE);

  if ( muon->GetBACFMuon() )
    if ( muon->GetQuality() >= gCards->GetMUONBACFQuality() )
      muon->SetBACFQualityCut(kTRUE);

  return kTRUE;
}


//_____________________________________________________________

Bool_t GMuons::CheckVcidLowCut(GMuon *muon) {
  //
  // check VcidLow cut
  if ( gDebug ) cout << endl << "GMuons::CheckLowCut() called" << endl << endl;
  if ( muon->GetVctrhlID() >= gCards->GetMUONVcidLowCut() )
      muon->SetVcidLowCut(kTRUE);

  
  

  return kTRUE;
}
//_____________________________________________________________

Bool_t GMuons::CheckVcidUpCut(GMuon *muon) {
  //
  // check VcidUp cut
  if ( gDebug ) cout << endl << "GMuons::CheckVcidUpCut() called" << endl << endl;

    if ( muon->GetVctrhlID() <= gCards->GetMUONVcidUpCut() )
      muon->SetVcidUpCut(kTRUE);
  

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckAllCuts(GMuon *muon) {
  //
  // check all cuts
  if ( gDebug ) cout << endl << "GMuons::CheckAllCuts() called" << endl << endl;

  Bool_t result = kTRUE;
  
  result = result && muon->GetEtaCut();
  result = result && muon->GetTakeCut();
  result = result && muon->GetFinderCut();
  result = result && muon->GetQualityCut();
  result = result && muon->GetPCut();
  result = result && muon->GetPtCut();
  result = result && muon->GetVcidLowCut();
  result = result && muon->GetVcidUpCut();
  result = result && muon->GetOnlyVertexFittedCut();
  if ( muon->GetForwardTrackMuon() )
    result = result && muon->GetForwardTrackMuonCut();
  if ( muon->GetBACFMuon() )
    result = result && muon->GetBACFQualityCut();

  //  if ( !(muon->GetBremat()||muon->GetMPMatch()|| muon->GetMufo())) 
  //    result=kFALSE;

  muon->SetAllCuts(result);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CalcBeamSpotImpactParameter(GMuon *muon) {
  //
  // if the muon fulfills all cuts, calc impact parameter to beamspot
  if ( gDebug ) cout << endl << "GMuons::CalcBeamSpotImactParameter() called" << endl << endl;


  muon->CalcBeamSpotImpactParameter();
  if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
    muon->CalcMCBeamSpotImpactParameter();
    muon->CalcTrueImpactParameter();
  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CalcMuonIsolation(GMuon *muon) {
  //
  // calc muon isolation if all other cuts are fullfilled
  if ( gDebug ) cout << endl << "GMuons::CalcMuonIsolation() called" << endl << endl;

  if ( gCards->GetMUONCalculateMuonIsolation() ) {

    // calculate isolation for all good muons
    if ( muon->GetAllCuts() ) {
      gZufo->CalcIsolation(muon);
      // check if muon isolation is smaller than veto cut
      if ( muon->GetIsolation10() <= gCards->GetMUONMinIsolation10Veto() ) {
	fMuonsMinIsolation10Veto = kTRUE;
	muon->SetAllCuts(kFALSE);
      }
    }
    
  }

  return kTRUE;
}

//____________________________________________________________

Bool_t GMuons::CalcMuonImpactParameter(GMuon *muon) {

  if (gDebug) cout << endl << "GMuon::CalcMuonImpactParameter called" << endl << endl;

//Calculate Impact Parameter by use of Tracking Block

  Double_t fMuon_Track_id  = 0;
  Double_t fTrack_id       = 0;
  Double_t fMuonJetPhi     = 0;

  TVector3 r2d_v, upt_v;
  
  fMuon_Track_id = muon->GetVctrhlID();

  if(muon->GetJetID()!=0){

  fMuonJetPhi = gData->Getkt_phijet_a(muon->GetJetID()-1);

    for( Int_t j = 0; j < gData->Gettrk_ntracks(); j++ ){
 
      fTrack_id = gData->Gettrk_id(j);

      if( fTrack_id == fMuon_Track_id ) { 

	fMuonDCA_x = gData->Gettrk_pca(j,0);
	fMuonDCA_y = gData->Gettrk_pca(j,1);
	fMuonDCA_z = gData->Gettrk_pca(j,2);

	r2d_v.SetXYZ(fMuonDCA_x-gData->Getxvtx(), fMuonDCA_y-gData->Getyvtx(), 0);
	//	r2d_v.SetXYZ(fMuonDCA_x - gData->Getbspt_x(), fMuonDCA_y-gData->Getbspt_y(), 0);
	upt_v.SetXYZ(TMath::Cos(fMuonJetPhi),TMath::Sin(fMuonJetPhi), 0);
	fMuonImp = r2d_v.Dot(upt_v);
      
      //      fMuonImp = gData->Gettrk_imppar(j);
      //      if(fMuonDCA_z > 0) fMuonImp    =  gData->Gettrk_imppar(j);
      //      if(fMuonDCA_z < 0) fMuonImp    = -gData->Gettrk_imppar(j);
	fMuonImperr = gData->Gettrk_imperr(j);
	fMuonImpSig = fMuonImp/fMuonImperr;
      }
    }
    
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CalcMuonJetMass(GMuon *muon) {

  if (gDebug) cout << endl << "GMuon::CalcMuonJetMass called" << endl << endl;

// Get mass of Jet containing muon

  Double_t fMuonJetID   = 0;

  fMuonJetID     = muon->GetJetID();

  for ( Int_t j = 0; j < gData->Getkt_njet_a(); j++  ) {
    
    if( j+1 == fMuonJetID && fMuonJetID != 0) {

      fMuonJetMass  = gData->Getkt_masjet_a(j);
      fMuonJetEt    = gData->Getkt_etjet_a(j);
    }

  }

  return kTRUE;
}
//_____________________________________________________________

Bool_t GMuons::FillMuonNdofandZ(GMuon *muon) {

  if (gDebug) cout << endl << "GMuon::FillMuonNdofandZ called" << endl << endl;

// Fill Muon Histograms with Mundof and Muz

  for ( Int_t j = 0; j < gData->Getnmu(); j++  ) {
    
    fMuonMuz    = gData->Getmuz(j);
    fMuonMundof = gData->Getmundof(j);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckMVCuts(GMuon *muon) {
  //
  // check if muon fulfills relaxed specific MV cuts for muon efficiency denominator
  // quality >=1, found by MV and vertex fitted track
  if ( gDebug ) cout << endl << "GMuons::CheckMVCut() called" << endl << endl;

  if ( muon->GetMv() && (muon->GetQuality() >= 1) && ( (muon->GetTrackFlag() == 2) || (muon->GetTrackFlag() == 3) ) )  
    muon->SetMVCuts(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckOnlyVertexFittedCut(GMuon *muon) {
  //
  // check if muon is only reconstructed from vertex fitted track
  if ( gDebug ) cout << endl << "GMuons::CheckOnlyVertexFittedCut() called" << endl << endl;

  if ( muon->GetType() == kForward ) {
    if ( gCards->GetFMUONOnlyVertexFitted() ) {
      if ( (muon->GetTrackFlag() == 2) || (muon->GetTrackFlag() == 3) ) {
	muon->SetOnlyVertexFittedCut(kTRUE);
      }
    } else {
      muon->SetOnlyVertexFittedCut(kTRUE);
    }
  } else if ( muon->GetType() == kBarrel ) {
    if ( gCards->GetBMUONOnlyVertexFitted() ) {
      if ( (muon->GetTrackFlag() == 2) || (muon->GetTrackFlag() == 3) ) {
	muon->SetOnlyVertexFittedCut(kTRUE);
      }
    } else {
      muon->SetOnlyVertexFittedCut(kTRUE);
    }
  } else if ( muon->GetType() == kRear ) {
    if ( gCards->GetRMUONOnlyVertexFitted() ) {
      if ( (muon->GetTrackFlag() == 2) || (muon->GetTrackFlag() == 3) ) {
	muon->SetOnlyVertexFittedCut(kTRUE);
      }
    } else {
      muon->SetOnlyVertexFittedCut(kTRUE);
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GMuons::FillHistos() called" << endl << endl;

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMuons::ObjectsFillHistos() called" << endl << endl;

  // loop over array
  for ( Int_t i = 0; i < fNMuons; i++ ) {
    GMuon *muon = ((GMuon*)(fMuons->At(i)));

    // fill general plots
    ObjectsFillGeneral(muon);
    
    // fill control plots
    ObjectsFillControl(muon);

    //fill fake histos
   if(gCards->GetProduceFakeMuon() ) {

    ObjectsFillFake(muon);
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::ObjectsFillGeneral(GMuon *muon) {
  //
  // fill general histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMuons::ObjectsFillGeneral() called" << endl << endl;

  if ( gCards->GetMUONGeneral() ) {

    fGeneralWeight_uncut->Fill(muon->GetOriginalWeight());
    fGeneralQuality_uncut->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      GMC *mc = muon->GetMC();
      if ( mc != 0 ) {
	if ( mc->GetType() == kMuon ) {
	  fGeneralQualityAndTrue_uncut->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
	}
      }
    }
    if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
      fGeneralWeightMUBAC_uncut->Fill(muon->GetOriginalWeight());
      fGeneralPhiMUBAC_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
    }
    if ( muon->GetBremat() && !muon->GetMuBac() ) {
      fGeneralWeightBREMAT_uncut->Fill(muon->GetOriginalWeight());
      fGeneralPhiBREMAT_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
    }
    if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
      fGeneralWeightMPMATCH_uncut->Fill(muon->GetOriginalWeight());
      fGeneralPhiMPMATCH_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
    }
    if ( muon->GetBremat() && muon->GetMuBac() ) {
      fGeneralWeightBREMATMUBAC_uncut->Fill(muon->GetOriginalWeight());
      fGeneralPhiBREMATMUBAC_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
    }
    if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
      fGeneralWeightMPMATCHMUBAC_uncut->Fill(muon->GetOriginalWeight());
      fGeneralPhiMPMATCHMUBAC_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
    }
    fGeneralProb_uncut->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
    fGeneralP_uncut->Fill(muon->P(),gHeader->GetWeight(muon));
    fGeneralPt_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
    fGeneralPtSpecial_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
    fGeneralPx_uncut->Fill(muon->Px(),gHeader->GetWeight(muon));
    fGeneralPy_uncut->Fill(muon->Py(),gHeader->GetWeight(muon));
    fGeneralPz_uncut->Fill(muon->Pz(),gHeader->GetWeight(muon));
    fGeneralPhi_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
    fGeneralTheta_uncut->Fill(muon->Theta(),gHeader->GetWeight(muon));
    fGeneralEta_uncut->Fill(muon->Eta(),gHeader->GetWeight(muon));
    fGeneralCharge_uncut->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

    FillSpecialFinderHisto(fGeneralSpecialFinder_uncut,muon);

    if ( muon->Get2DBeamSpotImpactParameter() != -9999.99 ) {
      fGeneral2DBeamSpotImpactParameter_uncut->Fill(muon->Get2DBeamSpotImpactParameter(),gHeader->GetWeight(muon));
      fGeneral2DBeamSpotImpactSignificance_uncut->Fill(muon->Get2DBeamSpotImpactParameterSignificance(),gHeader->GetWeight(muon));
      fGeneralGMuonPVsZTTP_uncut->Fill(muon->P(),muon->GetZTTTrack()->Mag(),gHeader->GetWeight(muon));
    }
    if ( gCards->GetMC() && (muon->GetMC() != 0) ) {
      fGeneralPMCTRUE_uncut->Fill(muon->GetMC()->P(),gHeader->GetWeight(muon));
      fGeneralPXMCTRUE_uncut->Fill(muon->GetMC()->Px(),gHeader->GetWeight(muon));
      fGeneralPYMCTRUE_uncut->Fill(muon->GetMC()->Py(),gHeader->GetWeight(muon));
      fGeneralPZMCTRUE_uncut->Fill(muon->GetMC()->Pz(),gHeader->GetWeight(muon));
      fGeneralPvsPMCTRUE_uncut->Fill(muon->P(),muon->GetMC()->P(),gHeader->GetWeight(muon));
      fGeneralPXvsPXMCTRUE_uncut->Fill(muon->Px(),muon->GetMC()->Px(),gHeader->GetWeight(muon));
      fGeneralPYvsPYMCTRUE_uncut->Fill(muon->Py(),muon->GetMC()->Py(),gHeader->GetWeight(muon));
      fGeneralPZvsPZMCTRUE_uncut->Fill(muon->Pz(),muon->GetMC()->Pz(),gHeader->GetWeight(muon));

      fGeneral2DMCBeamSpotImpactParameter_uncut->Fill(muon->Get2DMCBeamSpotImpactParameter(),gHeader->GetWeight(muon));
      fGeneral2DTrueImpactParameter_uncut->Fill(muon->Get2DTrueImpactParameter(),gHeader->GetWeight(muon));
      if ( muon->GetMC()->GetType() == kMuon ) 
	fGeneral2DMCTrueImpactParameter_uncut->Fill(muon->GetMC()->GetImpact2D(),gHeader->GetWeight(muon));
      fGeneral2DTrueImpactParamaterRecVsTrue_uncut->Fill(muon->Get2DTrueImpactParameter(),muon->GetMC()->GetImpact2D(),gHeader->GetWeight(muon));
      fGeneral2DBeamSpotImpactParamaterRecVsTrue_uncut->Fill(muon->Get2DBeamSpotImpactParameter(),muon->Get2DMCBeamSpotImpactParameter(),gHeader->GetWeight(muon));

      if ( muon->GetMC()->GetFMCKINID() >= 0 ) {
	fGeneralPMCTRUEpos_uncut->Fill(muon->GetMC()->P(),gHeader->GetWeight(muon));
	fGeneralPXMCTRUEpos_uncut->Fill(muon->GetMC()->Px(),gHeader->GetWeight(muon));
	fGeneralPYMCTRUEpos_uncut->Fill(muon->GetMC()->Py(),gHeader->GetWeight(muon));
	fGeneralPZMCTRUEpos_uncut->Fill(muon->GetMC()->Pz(),gHeader->GetWeight(muon));
	fGeneralPvsPMCTRUEpos_uncut->Fill(muon->P(),muon->GetMC()->P(),gHeader->GetWeight(muon));
	fGeneralPXvsPXMCTRUEpos_uncut->Fill(muon->Px(),muon->GetMC()->Px(),gHeader->GetWeight(muon));
	fGeneralPYvsPYMCTRUEpos_uncut->Fill(muon->Py(),muon->GetMC()->Py(),gHeader->GetWeight(muon));
	fGeneralPZvsPZMCTRUEpos_uncut->Fill(muon->Pz(),muon->GetMC()->Pz(),gHeader->GetWeight(muon));
      }

      if ( muon->GetMC()->GetFMCKINID() < 0 ) {
	fGeneralPMCTRUEneg_uncut->Fill(muon->GetMC()->P(),gHeader->GetWeight(muon));
	fGeneralPXMCTRUEneg_uncut->Fill(muon->GetMC()->Px(),gHeader->GetWeight(muon));
	fGeneralPYMCTRUEneg_uncut->Fill(muon->GetMC()->Py(),gHeader->GetWeight(muon));
	fGeneralPZMCTRUEneg_uncut->Fill(muon->GetMC()->Pz(),gHeader->GetWeight(muon));
	fGeneralPvsPMCTRUEneg_uncut->Fill(muon->P(),muon->GetMC()->P(),gHeader->GetWeight(muon));
	fGeneralPXvsPXMCTRUEneg_uncut->Fill(muon->Px(),muon->GetMC()->Px(),gHeader->GetWeight(muon));
	fGeneralPYvsPYMCTRUEneg_uncut->Fill(muon->Py(),muon->GetMC()->Py(),gHeader->GetWeight(muon));
	fGeneralPZvsPZMCTRUEneg_uncut->Fill(muon->Pz(),muon->GetMC()->Pz(),gHeader->GetWeight(muon));
      }

    }

    FillMuonFinderHisto(muon,fGeneralMuonFinder_uncut,gHeader->GetWeight(muon));
    if ( muon->GetQuality() == 4 ) {
      FillMuonFinderHisto(muon,fGeneralMuonFinder4_uncut,gHeader->GetWeight(muon));
    }
    if ( muon->GetQuality() == 5 ) {
      FillMuonFinderHisto(muon,fGeneralMuonFinder5_uncut,gHeader->GetWeight(muon));
    }
    if ( muon->GetQuality() == 6 ) {
      FillMuonFinderHisto(muon,fGeneralMuonFinder6_uncut,gHeader->GetWeight(muon));
    }

    if ( muon->GetType() == kForward ) {
      fGeneralWeightForward_uncut->Fill(muon->GetOriginalWeight());
      fGeneralRegions_uncut->Fill(2.5,gHeader->GetWeight(muon));
      FillSpecialFinderHisto(fGeneralSpecialFinderForward_uncut,muon);
      fGeneralQualityForward_uncut->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
      fGeneralProbForward_uncut->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
      fGeneralPForward_uncut->Fill(muon->P(),gHeader->GetWeight(muon));
      fGeneralPtForward_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
      fGeneralPtSpecialForward_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
      fGeneralPxForward_uncut->Fill(muon->Px(),gHeader->GetWeight(muon));
      fGeneralPyForward_uncut->Fill(muon->Py(),gHeader->GetWeight(muon));
      fGeneralPzForward_uncut->Fill(muon->Pz(),gHeader->GetWeight(muon));
      fGeneralPhiForward_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      fGeneralThetaForward_uncut->Fill(muon->Theta(),gHeader->GetWeight(muon));
      fGeneralEtaForward_uncut->Fill(muon->Eta(),gHeader->GetWeight(muon));
      fGeneralChargeForward_uncut->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

      if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	fGeneralWeightMUBACForward_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMUBACForward_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetBremat() && !muon->GetMuBac() ) {
	fGeneralWeightBREMATForward_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiBREMATForward_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	fGeneralWeightMPMATCHForward_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMPMATCHForward_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetBremat() && muon->GetMuBac() ) {
	fGeneralWeightBREMATMUBACForward_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiBREMATMUBACForward_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	fGeneralWeightMPMATCHMUBACForward_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMPMATCHMUBACForward_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }

    }

    if ( muon->GetType() == kBarrel ) {
      fGeneralWeightBarrel_uncut->Fill(muon->GetOriginalWeight());
      fGeneralRegions_uncut->Fill(1.5,gHeader->GetWeight(muon));
      FillSpecialFinderHisto(fGeneralSpecialFinderBarrel_uncut,muon);
      fGeneralQualityBarrel_uncut->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
      fGeneralProbBarrel_uncut->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
      fGeneralPBarrel_uncut->Fill(muon->P(),gHeader->GetWeight(muon));
      fGeneralPtBarrel_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
      fGeneralPtSpecialBarrel_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
      fGeneralPxBarrel_uncut->Fill(muon->Px(),gHeader->GetWeight(muon));
      fGeneralPyBarrel_uncut->Fill(muon->Py(),gHeader->GetWeight(muon));
      fGeneralPzBarrel_uncut->Fill(muon->Pz(),gHeader->GetWeight(muon));
      fGeneralPhiBarrel_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      fGeneralThetaBarrel_uncut->Fill(muon->Theta(),gHeader->GetWeight(muon));
      fGeneralEtaBarrel_uncut->Fill(muon->Eta(),gHeader->GetWeight(muon));
      fGeneralChargeBarrel_uncut->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

      if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	fGeneralWeightMUBACBarrel_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMUBACBarrel_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetBremat() && !muon->GetMuBac() ) {
	fGeneralWeightBREMATBarrel_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiBREMATBarrel_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	fGeneralWeightMPMATCHBarrel_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMPMATCHBarrel_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetBremat() && muon->GetMuBac() ) {
	fGeneralWeightBREMATMUBACBarrel_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiBREMATMUBACBarrel_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	fGeneralWeightMPMATCHMUBACBarrel_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMPMATCHMUBACBarrel_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }

    }

    if ( muon->GetType() == kRear ) {
      fGeneralWeightRear_uncut->Fill(muon->GetOriginalWeight());
      FillSpecialFinderHisto(fGeneralSpecialFinderRear_uncut,muon);
      fGeneralRegions_uncut->Fill(0.5,gHeader->GetWeight(muon));
      fGeneralQualityRear_uncut->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
      fGeneralProbRear_uncut->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
      fGeneralPRear_uncut->Fill(muon->P(),gHeader->GetWeight(muon));
      fGeneralPtRear_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
      fGeneralPtSpecialRear_uncut->Fill(muon->Pt(),gHeader->GetWeight(muon));
      fGeneralPxRear_uncut->Fill(muon->Px(),gHeader->GetWeight(muon));
      fGeneralPyRear_uncut->Fill(muon->Py(),gHeader->GetWeight(muon));
      fGeneralPzRear_uncut->Fill(muon->Pz(),gHeader->GetWeight(muon));
      fGeneralPhiRear_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      fGeneralThetaRear_uncut->Fill(muon->Theta(),gHeader->GetWeight(muon));
      fGeneralEtaRear_uncut->Fill(muon->Eta(),gHeader->GetWeight(muon));
      fGeneralChargeRear_uncut->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

      if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	fGeneralWeightMUBACRear_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMUBACRear_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetBremat() && !muon->GetMuBac() ) {
	fGeneralWeightBREMATRear_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiBREMATRear_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	fGeneralWeightMPMATCHRear_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMPMATCHRear_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetBremat() && muon->GetMuBac() ) {
	fGeneralWeightBREMATMUBACRear_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiBREMATMUBACRear_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }
      if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	fGeneralWeightMPMATCHMUBACRear_uncut->Fill(muon->GetOriginalWeight());
	fGeneralPhiMPMATCHMUBACRear_uncut->Fill(muon->Phi(),gHeader->GetWeight(muon));
      }

    }


    if ( gHeader->GetAllCuts() ) {

      if ( muon->GetMatched() || (muon->GetAllCuts() && gCards->GetMUONFillAll()) ) {

	fGeneralWeight->Fill(muon->GetOriginalWeight());
 	fGeneralQuality->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
	if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
	  GMC *mc = muon->GetMC();
	  if ( mc != 0 ) {
	    if ( mc->GetType() == kMuon ) {
	      fGeneralQualityAndTrue->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
	    }
	  }
	}
	if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	  fGeneralWeightMUBAC->Fill(muon->GetOriginalWeight());
	  fGeneralPhiMUBAC->Fill(muon->Phi(),gHeader->GetWeight(muon));
	}
	if ( muon->GetBremat() && !muon->GetMuBac() ) {
	  fGeneralWeightBREMAT->Fill(muon->GetOriginalWeight());
	  fGeneralPhiBREMAT->Fill(muon->Phi(),gHeader->GetWeight(muon));
	}
	if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	  fGeneralWeightMPMATCH->Fill(muon->GetOriginalWeight());
	  fGeneralPhiMPMATCH->Fill(muon->Phi(),gHeader->GetWeight(muon));
	}
	if ( muon->GetBremat() && muon->GetMuBac() ) {
	  fGeneralWeightBREMATMUBAC->Fill(muon->GetOriginalWeight());
	  fGeneralPhiBREMATMUBAC->Fill(muon->Phi(),gHeader->GetWeight(muon));
	}
	if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	  fGeneralWeightMPMATCHMUBAC->Fill(muon->GetOriginalWeight());
	  fGeneralPhiMPMATCHMUBAC->Fill(muon->Phi(),gHeader->GetWeight(muon));
	}
	  
	FillSpecialFinderHisto(fGeneralSpecialFinder,muon);

	fGeneralProb->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
	fGeneralP->Fill(muon->P(),gHeader->GetWeight(muon));
	fGeneralPt->Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralPtSpecial->Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralPtChosen->Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralPtChosenFine2->Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralPtChosenFine4->Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralPtChosenFine8->Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralPtChosenFine16->Fill(muon->Pt(),gHeader->GetWeight(muon));

	if ( gCards->GetMUONCalculateMuonIsolation() ) {
	  fGeneralChosenIso01->Fill(muon->GetIsolation01(),gHeader->GetWeight(muon));
	  fGeneralChosenIso02->Fill(muon->GetIsolation02(),gHeader->GetWeight(muon));
	  fGeneralChosenIso03->Fill(muon->GetIsolation03(),gHeader->GetWeight(muon));
	  fGeneralChosenIso04->Fill(muon->GetIsolation04(),gHeader->GetWeight(muon));
	  fGeneralChosenIso05->Fill(muon->GetIsolation05(),gHeader->GetWeight(muon));
	  fGeneralChosenIso06->Fill(muon->GetIsolation06(),gHeader->GetWeight(muon));
	  fGeneralChosenIso07->Fill(muon->GetIsolation07(),gHeader->GetWeight(muon));
	  fGeneralChosenIso08->Fill(muon->GetIsolation08(),gHeader->GetWeight(muon));
	  fGeneralChosenIso09->Fill(muon->GetIsolation09(),gHeader->GetWeight(muon));
	  fGeneralChosenIso10->Fill(muon->GetIsolation10(),gHeader->GetWeight(muon));
	}

	fGeneralEtaChosen->Fill(muon->Eta(),gHeader->GetWeight(muon));
	fGeneralEtaChosenLarge->Fill(muon->Eta(),gHeader->GetWeight(muon));

	//require calculated impact parameter
	if ( muon->Get2DBeamSpotImpactParameter() != -9999.99 ) {
	  fGeneral2DBeamSpotImpactParameter    -> Fill(muon->Get2DBeamSpotImpactParameter(),gHeader->GetWeight(muon));
	  fGeneral2DBeamSpotImpactSignificance -> Fill(muon->Get2DBeamSpotImpactParameterSignificance(),gHeader->GetWeight(muon));
	  fGeneralGMuonPVsZTTP                 -> Fill(muon->P(),muon->GetZTTTrack()->Mag(),gHeader->GetWeight(muon));
	}

	GMC *mcmuon = muon->GetMC();
	if ( gCards->GetMC() && (mcmuon != 0) && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	  if ( (mcmuon->GetType() == kMuon) && gMCs->GetAllMCCuts() ) {
	    fGeneralPtChosenMC       -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	    fGeneralPtChosenFineMC   -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	    fGeneralEtaChosenMC      -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	    fGeneralEtaChosenLargeMC -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	    if ( muon->GetType() == kForward ) {
	      fGeneralCrossRegionsRecNTrue->Fill(2.5,gHeader->GetWeight(muon));
	    } else if ( muon->GetType() == kBarrel ) {
	      fGeneralCrossRegionsRecNTrue->Fill(1.5,gHeader->GetWeight(muon));
	    } else if ( muon->GetType() == kRear ) {
	      fGeneralCrossRegionsRecNTrue->Fill(0.5,gHeader->GetWeight(muon));
	    }
	    fGeneralCrossPtRecNTrue         -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	    fGeneralCrossEtaRecNTrue        -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	    fGeneralCrossPtFineRecNTrue     -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	    fGeneralCrossEtaFineRecNTrue    -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	    fGeneralCrossPtMassimoRecNTrue  -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	    fGeneralCrossEtaMassimoRecNTrue -> Fill(muon->Eta(),gHeader->GetWeight(muon));

	    FillSpecialFinderHisto(fGeneralCrossFinderRecNTrue,muon);
	  } 

	  fGeneralPMCTRUE      -> Fill(mcmuon->P(),gHeader->GetWeight(muon));
	  fGeneralPXMCTRUE     -> Fill(mcmuon->Px(),gHeader->GetWeight(muon));
	  fGeneralPYMCTRUE     -> Fill(mcmuon->Py(),gHeader->GetWeight(muon));
	  fGeneralPZMCTRUE     -> Fill(mcmuon->Pz(),gHeader->GetWeight(muon));
	  fGeneralPvsPMCTRUE   -> Fill(muon->P(),mcmuon->P(),gHeader->GetWeight(muon));
	  fGeneralPXvsPXMCTRUE -> Fill(muon->Px(),mcmuon->Px(),gHeader->GetWeight(muon));
	  fGeneralPYvsPYMCTRUE -> Fill(muon->Py(),mcmuon->Py(),gHeader->GetWeight(muon));
	  fGeneralPZvsPZMCTRUE -> Fill(muon->Pz(),mcmuon->Pz(),gHeader->GetWeight(muon));

	  fGeneral2DMCBeamSpotImpactParameter        -> Fill(muon->Get2DMCBeamSpotImpactParameter(),gHeader->GetWeight(muon));
	  fGeneral2DTrueImpactParameter              -> Fill(muon->Get2DTrueImpactParameter(),gHeader->GetWeight(muon));
	  fGeneral2DMCTrueImpactParameter            -> Fill(mcmuon->GetImpact2D(),gHeader->GetWeight(muon));
	  fGeneral2DTrueImpactParamaterRecVsTrue     -> Fill(muon->Get2DTrueImpactParameter(),mcmuon->GetImpact2D(),gHeader->GetWeight(muon));
	  fGeneral2DBeamSpotImpactParamaterRecVsTrue ->Fill(muon->Get2DBeamSpotImpactParameter(),muon->Get2DMCBeamSpotImpactParameter(),gHeader->GetWeight(muon));

	  if ( mcmuon->GetFMCKINID() >= 0 ) {
	    fGeneralPMCTRUEpos      -> Fill(mcmuon->P(),gHeader->GetWeight(muon));
	    fGeneralPXMCTRUEpos     -> Fill(mcmuon->Px(),gHeader->GetWeight(muon));
	    fGeneralPYMCTRUEpos     -> Fill(mcmuon->Py(),gHeader->GetWeight(muon));
	    fGeneralPZMCTRUEpos     -> Fill(mcmuon->Pz(),gHeader->GetWeight(muon));
	    fGeneralPvsPMCTRUEpos   -> Fill(muon->P(),mcmuon->P(),gHeader->GetWeight(muon));
	    fGeneralPXvsPXMCTRUEpos -> Fill(muon->Px(),mcmuon->Px(),gHeader->GetWeight(muon));
	    fGeneralPYvsPYMCTRUEpos -> Fill(muon->Py(),mcmuon->Py(),gHeader->GetWeight(muon));
	    fGeneralPZvsPZMCTRUEpos -> Fill(muon->Pz(),mcmuon->Pz(),gHeader->GetWeight(muon));
	  }
	  
	  if ( mcmuon->GetFMCKINID() < 0 ) {
	    fGeneralPMCTRUEneg      -> Fill(mcmuon->P(),gHeader->GetWeight(muon));
	    fGeneralPXMCTRUEneg     -> Fill(mcmuon->Px(),gHeader->GetWeight(muon));
	    fGeneralPYMCTRUEneg     -> Fill(mcmuon->Py(),gHeader->GetWeight(muon));
	    fGeneralPZMCTRUEneg     -> Fill(mcmuon->Pz(),gHeader->GetWeight(muon));
	    fGeneralPvsPMCTRUEneg   -> Fill(muon->P(),mcmuon->P(),gHeader->GetWeight(muon));
	    fGeneralPXvsPXMCTRUEneg -> Fill(muon->Px(),mcmuon->Px(),gHeader->GetWeight(muon));
	    fGeneralPYvsPYMCTRUEneg -> Fill(muon->Py(),mcmuon->Py(),gHeader->GetWeight(muon));
	    fGeneralPZvsPZMCTRUEneg -> Fill(muon->Pz(),mcmuon->Pz(),gHeader->GetWeight(muon));
	  }
	  
	}

	fGeneralPx     -> Fill(muon->Px(),gHeader->GetWeight(muon));
	fGeneralPy     -> Fill(muon->Py(),gHeader->GetWeight(muon));
	fGeneralPz     -> Fill(muon->Pz(),gHeader->GetWeight(muon));
	fGeneralPhi    -> Fill(muon->Phi(),gHeader->GetWeight(muon));
	fGeneralTheta  -> Fill(muon->Theta(),gHeader->GetWeight(muon));
	fGeneralEta    -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	fGeneralCharge -> Fill(muon->GetCharge(),gHeader->GetWeight(muon));

	fGeneralCrossPt         -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralCrossEta        -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	fGeneralCrossPtFine     -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralCrossEtaFine    -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	fGeneralCrossPtMassimo  -> Fill(muon->Pt(),gHeader->GetWeight(muon));
	fGeneralCrossEtaMassimo -> Fill(muon->Eta(),gHeader->GetWeight(muon));
	FillSpecialFinderHisto(fGeneralCrossFinder,muon);

	fGeneralCrossTotal->Fill(0.5,gHeader->GetWeight(muon));
	if((muon->GetBremat())||(muon->GetMPMatch())||(muon->GetMufo())) fGeneralCrossTotalMuChamber->Fill(0.5,gHeader->GetWeight(muon));
	if(muon->GetMuBac()) fGeneralCrossTotalBAC->Fill(0.5,gHeader->GetWeight(muon));


	if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake()) && gMCs->GetAllMCCuts() ) {
	  fGeneralCrossTotalRecNTrue->Fill(0.5,gHeader->GetWeight(muon));
	  if((muon->GetBremat())||(muon->GetMPMatch())||(muon->GetMufo()))   fGeneralCrossTotalMuChamberRecNTrue->Fill(0.5,gHeader->GetWeight(muon));
	  if(muon->GetMuBac()) fGeneralCrossTotalBACRecNTrue->Fill(0.5,gHeader->GetWeight(muon));
	}


	// fill special finder categories plots (legend see creategeneral())
	if ( muon->GetQuality() == 6 ) {
	  if ( muon->GetBremat() ) {
	    fGeneralSpecialFinder6->Fill(0);
	  } else if ( muon->GetMPMatch() && (muon->GetProbability() > 0.05) ) {
	    fGeneralSpecialFinder6->Fill(1);
	  } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	    fGeneralSpecialFinder6->Fill(2);
	  } else if ( muon->GetMPMatch() && (muon->GetProbability() <= 0.05) ) {
	    fGeneralSpecialFinder6->Fill(3);
	  } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	    fGeneralSpecialFinder6->Fill(4);
	  }
	}
	if ( muon->GetQuality() == 5 ) {
	  if ( muon->GetMPMatch() ) {
	    fGeneralSpecialFinder5->Fill(0);
	  } else if ( muon->GetMufo() ) {
	    fGeneralSpecialFinder5->Fill(1);
	  } else if ( muon->GetMamma() ) {
	    fGeneralSpecialFinder5->Fill(2);
	  } else if ( muon->GetMv() && muon->GetMuBac() && !muon->GetMPMatch() && !muon->GetMufo() && !muon->GetBremat() ) {
	    fGeneralSpecialFinder5->Fill(4);
 	  } else if ( muon->GetMv() && muon->GetBremat() ) {
	    fGeneralSpecialFinder5->Fill(3);
	  } 
	}
	if ( muon->GetQuality() == 4 ) {
	  if ( muon->GetBremat() ) {
	    fGeneralSpecialFinder4->Fill(0);
	  } else if ( muon->GetMufo() ) {
	    fGeneralSpecialFinder4->Fill(1);
	  } else if ( muon->GetMamma() ) {
	    fGeneralSpecialFinder4->Fill(2);
	  } else if ( muon->GetMuBac() && muon->GetMv() ) {
	    fGeneralSpecialFinder4->Fill(6);
	  } else if ( muon->GetMuBac() && muon->GetMip() ) {
	    fGeneralSpecialFinder4->Fill(7);
	  } else if ( muon->GetMuBac() ) {
	    fGeneralSpecialFinder4->Fill(3);
	  } else if ( muon->GetMv() && !muon->GetMufo() && !muon->GetMPMatch() ) {
	    fGeneralSpecialFinder4->Fill(4);
	  } else if ( muon->GetMuBac() && muon->GetGlomu() ) {
	    fGeneralSpecialFinder4->Fill(5);
	  }
	}

	if ( muon->GetType() == kForward ) {
	  fGeneralWeightForward->Fill(muon->GetOriginalWeight());
	  fGeneralRegions->Fill(2.5,gHeader->GetWeight(muon));
	  FillSpecialFinderHisto(fGeneralSpecialFinderForward,muon);
	  fGeneralQualityForward->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
	  fGeneralProbForward->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
	  fGeneralPForward->Fill(muon->P(),gHeader->GetWeight(muon));
	  fGeneralPtForward->Fill(muon->Pt(),gHeader->GetWeight(muon));
	  fGeneralPtSpecialForward->Fill(muon->Pt(),gHeader->GetWeight(muon));
	  fGeneralPxForward->Fill(muon->Px(),gHeader->GetWeight(muon));
	  fGeneralPyForward->Fill(muon->Py(),gHeader->GetWeight(muon));
	  fGeneralPzForward->Fill(muon->Pz(),gHeader->GetWeight(muon));
	  fGeneralPhiForward->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  fGeneralThetaForward->Fill(muon->Theta(),gHeader->GetWeight(muon));
	  fGeneralEtaForward->Fill(muon->Eta(),gHeader->GetWeight(muon));
	  fGeneralChargeForward->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

	  fGeneralCrossRegions->Fill(2.5,gHeader->GetWeight(muon));

	  if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	    fGeneralWeightMUBACForward->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMUBACForward->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetBremat() && !muon->GetMuBac() ) {
	    fGeneralWeightBREMATForward->Fill(muon->GetOriginalWeight());
	    fGeneralPhiBREMATForward->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	    fGeneralWeightMPMATCHForward->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMPMATCHForward->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetBremat() && muon->GetMuBac() ) {
	    fGeneralWeightBREMATMUBACForward->Fill(muon->GetOriginalWeight());
	    fGeneralPhiBREMATMUBACForward->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	    fGeneralWeightMPMATCHMUBACForward->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMPMATCHMUBACForward->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  
	  // fill special finder categories plots (legend see creategeneral())
	  if ( muon->GetQuality() == 6 ) {
	    if ( muon->GetBremat() ) {
	      fGeneralSpecialFinder6Forward->Fill(0);
	    } else if ( muon->GetMPMatch() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Forward->Fill(1);
	    } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Forward->Fill(2);
	    } else if ( muon->GetMPMatch() && (muon->GetProbability() <= 0.05) ) {
	      fGeneralSpecialFinder6Forward->Fill(3);
	    } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Forward->Fill(4);
	    }
	  }
	  if ( muon->GetQuality() == 5 ) {
	    if ( muon->GetMPMatch() ) {
	      fGeneralSpecialFinder5Forward->Fill(0);
	    } else if ( muon->GetMufo() ) {
	      fGeneralSpecialFinder5Forward->Fill(1);
	    } else if ( muon->GetMamma() ) {
	      fGeneralSpecialFinder5Forward->Fill(2);
	    } else if ( muon->GetMv() && muon->GetMuBac() && !muon->GetMPMatch() && !muon->GetMufo() && !muon->GetBremat() ) {
	      fGeneralSpecialFinder5Forward->Fill(4);
	    } else if ( muon->GetMv() && muon->GetBremat() ) {
	      fGeneralSpecialFinder5Forward->Fill(3);
	    } 
	  }
	  if ( muon->GetQuality() == 4 ) {
	    if ( muon->GetBremat() ) {
	      fGeneralSpecialFinder4Forward->Fill(0);
	    } else if ( muon->GetMufo() ) {
	      fGeneralSpecialFinder4Forward->Fill(1);
	    } else if ( muon->GetMamma() ) {
	      fGeneralSpecialFinder4Forward->Fill(2);
	    } else if ( muon->GetMuBac() && muon->GetMv() ) {
	      fGeneralSpecialFinder4Forward->Fill(6);
	    } else if ( muon->GetMuBac() && muon->GetMip() ) {
	      fGeneralSpecialFinder4Forward->Fill(7);
	    } else if ( muon->GetMuBac() ) {
	      fGeneralSpecialFinder4Forward->Fill(3);
	    } else if ( muon->GetMv() && !muon->GetMufo() && !muon->GetMPMatch() ) {
	      fGeneralSpecialFinder4Forward->Fill(4);
	    } else if ( muon->GetMuBac() && muon->GetGlomu() ) {
	      fGeneralSpecialFinder4Forward->Fill(5);
	    }
	  }

	}
	if ( muon->GetType() == kBarrel ) {
	  fGeneralWeightBarrel->Fill(muon->GetOriginalWeight());
	  fGeneralRegions->Fill(1.5,gHeader->GetWeight(muon));
	  FillSpecialFinderHisto(fGeneralSpecialFinderBarrel,muon);
	  fGeneralQualityBarrel->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
	  fGeneralProbBarrel->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
	  fGeneralPBarrel->Fill(muon->P(),gHeader->GetWeight(muon));
	  fGeneralPtBarrel->Fill(muon->Pt(),gHeader->GetWeight(muon));
	  fGeneralPtSpecialBarrel->Fill(muon->Pt(),gHeader->GetWeight(muon));
	  fGeneralPxBarrel->Fill(muon->Px(),gHeader->GetWeight(muon));
	  fGeneralPyBarrel->Fill(muon->Py(),gHeader->GetWeight(muon));
	  fGeneralPzBarrel->Fill(muon->Pz(),gHeader->GetWeight(muon));
	  fGeneralPhiBarrel->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  fGeneralThetaBarrel->Fill(muon->Theta(),gHeader->GetWeight(muon));
	  fGeneralEtaBarrel->Fill(muon->Eta(),gHeader->GetWeight(muon));
	  fGeneralChargeBarrel->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

	  fGeneralCrossRegions->Fill(1.5,gHeader->GetWeight(muon));

	  if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	    fGeneralWeightMUBACBarrel->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMUBACBarrel->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetBremat() && !muon->GetMuBac() ) {
	    fGeneralWeightBREMATBarrel->Fill(muon->GetOriginalWeight());
	    fGeneralPhiBREMATBarrel->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	    fGeneralWeightMPMATCHBarrel->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMPMATCHBarrel->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetBremat() && muon->GetMuBac() ) {
	    fGeneralWeightBREMATMUBACBarrel->Fill(muon->GetOriginalWeight());
	    fGeneralPhiBREMATMUBACBarrel->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	    fGeneralWeightMPMATCHMUBACBarrel->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMPMATCHMUBACBarrel->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  
	  // fill special finder categories plots (legend see creategeneral())
	  if ( muon->GetQuality() == 6 ) {
	    if ( muon->GetBremat() ) {
	      fGeneralSpecialFinder6Barrel->Fill(0);
	    } else if ( muon->GetMPMatch() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Barrel->Fill(1);
	    } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Barrel->Fill(2);
	    } else if ( muon->GetMPMatch() && (muon->GetProbability() <= 0.05) ) {
	      fGeneralSpecialFinder6Barrel->Fill(3);
	    } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Barrel->Fill(4);
	    }
	  }
	  if ( muon->GetQuality() == 5 ) {
	    if ( muon->GetMPMatch() ) {
	      fGeneralSpecialFinder5Barrel->Fill(0);
	    } else if ( muon->GetMufo() ) {
	      fGeneralSpecialFinder5Barrel->Fill(1);
	    } else if ( muon->GetMamma() ) {
	      fGeneralSpecialFinder5Barrel->Fill(2);
	    } else if ( muon->GetMv() && muon->GetMuBac() && !muon->GetMPMatch() && !muon->GetMufo() && !muon->GetBremat() ) {
	      fGeneralSpecialFinder5Barrel->Fill(4);
	    } else if ( muon->GetMv() && muon->GetBremat() ) {
	      fGeneralSpecialFinder5Barrel->Fill(3);
	    } 
	  }
	  if ( muon->GetQuality() == 4 ) {
	    if ( muon->GetBremat() ) {
	      fGeneralSpecialFinder4Barrel->Fill(0);
	    } else if ( muon->GetMufo() ) {
	      fGeneralSpecialFinder4Barrel->Fill(1);
	    } else if ( muon->GetMamma() ) {
	      fGeneralSpecialFinder4Barrel->Fill(2);
	    } else if ( muon->GetMuBac() && muon->GetMv() ) {
	      fGeneralSpecialFinder4Barrel->Fill(6);
	    } else if ( muon->GetMuBac() && muon->GetMip() ) {
	      fGeneralSpecialFinder4Barrel->Fill(7);
	    } else if ( muon->GetMuBac() ) {
	      fGeneralSpecialFinder4Barrel->Fill(3);
	    } else if ( muon->GetMv() && !muon->GetMufo() && !muon->GetMPMatch() ) {
	      fGeneralSpecialFinder4Barrel->Fill(4);
	    } else if ( muon->GetMuBac() && muon->GetGlomu() ) {
	      fGeneralSpecialFinder4Barrel->Fill(5);
	    }
	  }
	}
	if ( muon->GetType() == kRear ) {
	  fGeneralWeightRear->Fill(muon->GetOriginalWeight());
	  fGeneralRegions->Fill(0.5,gHeader->GetWeight(muon));
	  FillSpecialFinderHisto(fGeneralSpecialFinderRear,muon);
	  fGeneralQualityRear->Fill(muon->GetQuality(),gHeader->GetWeight(muon));
	  fGeneralProbRear->Fill(muon->GetProbability(),gHeader->GetWeight(muon));
	  fGeneralPRear->Fill(muon->P(),gHeader->GetWeight(muon));
	  fGeneralPtRear->Fill(muon->Pt(),gHeader->GetWeight(muon));
	  fGeneralPtSpecialRear->Fill(muon->Pt(),gHeader->GetWeight(muon));
	  fGeneralPxRear->Fill(muon->Px(),gHeader->GetWeight(muon));
	  fGeneralPyRear->Fill(muon->Py(),gHeader->GetWeight(muon));
	  fGeneralPzRear->Fill(muon->Pz(),gHeader->GetWeight(muon));
	  fGeneralPhiRear->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  fGeneralThetaRear->Fill(muon->Theta(),gHeader->GetWeight(muon));
	  fGeneralEtaRear->Fill(muon->Eta(),gHeader->GetWeight(muon));
	  fGeneralChargeRear->Fill(muon->GetCharge(),gHeader->GetWeight(muon));

	  fGeneralCrossRegions->Fill(0.5,gHeader->GetWeight(muon));

	  if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() ) {
	    fGeneralWeightMUBACRear->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMUBACRear->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetBremat() && !muon->GetMuBac() ) {
	    fGeneralWeightBREMATRear->Fill(muon->GetOriginalWeight());
	    fGeneralPhiBREMATRear->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	    fGeneralWeightMPMATCHRear->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMPMATCHRear->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetBremat() && muon->GetMuBac() ) {
	    fGeneralWeightBREMATMUBACRear->Fill(muon->GetOriginalWeight());
	    fGeneralPhiBREMATMUBACRear->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  if ( muon->GetMPMatch() && !muon->GetMuBac() ) {
	    fGeneralWeightMPMATCHMUBACRear->Fill(muon->GetOriginalWeight());
	    fGeneralPhiMPMATCHMUBACRear->Fill(muon->Phi(),gHeader->GetWeight(muon));
	  }
	  
	  // fill special finder categories plots (legend see creategeneral())
	  if ( muon->GetQuality() == 6 ) {
	    if ( muon->GetBremat() ) {
	      fGeneralSpecialFinder6Rear->Fill(0);
	    } else if ( muon->GetMPMatch() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Rear->Fill(1);
	    } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Rear->Fill(2);
	    } else if ( muon->GetMPMatch() && (muon->GetProbability() <= 0.05) ) {
	      fGeneralSpecialFinder6Rear->Fill(3);
	    } else if ( muon->GetMufo() && (muon->GetProbability() > 0.05) ) {
	      fGeneralSpecialFinder6Rear->Fill(4);
	    }
	  }
	  if ( muon->GetQuality() == 5 ) {
	    if ( muon->GetMPMatch() ) {
	      fGeneralSpecialFinder5Rear->Fill(0);
	    } else if ( muon->GetMufo() ) {
	      fGeneralSpecialFinder5Rear->Fill(1);
	    } else if ( muon->GetMamma() ) {
	      fGeneralSpecialFinder5Rear->Fill(2);
	    } else if ( muon->GetMv() && muon->GetMuBac() && !muon->GetMPMatch() && !muon->GetMufo() && !muon->GetBremat() ) {
	      fGeneralSpecialFinder5Rear->Fill(4);
	    } else if ( muon->GetMv() && muon->GetBremat() ) {
	      fGeneralSpecialFinder5Rear->Fill(3);
	    } 
	  }
	  if ( muon->GetQuality() == 4 ) {
	    if ( muon->GetBremat() ) {
	      fGeneralSpecialFinder4Rear->Fill(0);
	    } else if ( muon->GetMufo() ) {
	      fGeneralSpecialFinder4Rear->Fill(1);
	    } else if ( muon->GetMamma() ) {
	      fGeneralSpecialFinder4Rear->Fill(2);
	    } else if ( muon->GetMuBac() && muon->GetMv() ) {
	      fGeneralSpecialFinder4Rear->Fill(6);
	    } else if ( muon->GetMuBac() && muon->GetMip() ) {
	      fGeneralSpecialFinder4Rear->Fill(7);
	    } else if ( muon->GetMuBac() ) {
	      fGeneralSpecialFinder4Rear->Fill(3);
	    } else if ( muon->GetMv() && !muon->GetMufo() && !muon->GetMPMatch() ) {
	      fGeneralSpecialFinder4Rear->Fill(4);
	    } else if ( muon->GetMuBac() && muon->GetGlomu() ) {
	      fGeneralSpecialFinder4Rear->Fill(5);
	    }
	  }
	}
	FillMuonFinderHisto(muon,fGeneralMuonFinder,gHeader->GetWeight(muon));
	if ( muon->GetQuality() == 4 ) {
	  FillMuonFinderHisto(muon,fGeneralMuonFinder4,gHeader->GetWeight(muon));
	}
	if ( muon->GetQuality() == 5 ) {
	  FillMuonFinderHisto(muon,fGeneralMuonFinder5,gHeader->GetWeight(muon));
	}
	if ( muon->GetQuality() == 6 ) {
	  FillMuonFinderHisto(muon,fGeneralMuonFinder6,gHeader->GetWeight(muon));
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::ObjectsFillControl(GMuon *muon) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMuons::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetMUONControl() ) {
    

    fControlWeight_uncut->Fill(muon->GetOriginalWeight());
    fControlProb_uncut->Fill(muon->GetProbability());
    fControlEta_uncut->Fill(muon->Eta());
    fControlPt_uncut->Fill(muon->Pt());
    fControlP_uncut->Fill(muon->P());
    fControlChFlg_uncut->Fill(muon->GetChamberFlag());
    FillMuonFinderHisto(muon,fControlMuonFinder_uncut);
    fControlQuality_uncut->Fill(muon->GetQuality());
    if ( muon->GetBACFMuon() ) {
      fControlQualityForwardBAC_uncut->Fill(muon->GetQuality());
      if ( muon->GetBACFQualityCut() )
	fControlQualityForwardBAC->Fill(muon->GetQuality());
    }
    //     if ( muon->GetFmufiCID() > 0 ) {
//       fControlMuonMfpro_uncut->Fill(gData->Getmfpro(muon->GetFmufiCID()));
//       fControlMuonMfndf_uncut->Fill(gData->Getmfndf(muon->GetFmufiCID()));
//       fControlMuonMfz_uncut->Fill(gData->Getmfz(muon->GetFmufiCID()));
//     }

    if ( muon->GetMPMatch() ) {
      fControlChamberFlag->Fill(muon->GetChamberID(),gData->Getfmufi(muon->GetMPMatchID()-1));
    }

    if ( muon->GetType() == kForward ) {
      if ( muon->GetMPMatchCut() )
	fControlProbForward->Fill(muon->GetProbability());
      if ( muon->GetEtaCut() )
	fControlEtaForward->Fill(muon->Eta());
      if ( muon->GetPtCut() )
	fControlPtForward->Fill(muon->Pt());
      if ( muon->GetPCut() )
	fControlPForward->Fill(muon->P());
      if ( muon->GetFinderCut() )
	FillMuonFinderHisto(muon,fControlMuonFinderForward);
      fControlChFlgForward->Fill(muon->GetChamberFlag());
      if ( muon->GetQualityCut() )
	fControlQualityForward->Fill(muon->GetQuality());
      if ( (muon->GetFmufiCID() > 0)&&(muon->GetFmufiCID() < 10)&&muon->GetForwardTrackMuonCut() ) {
	fControlMuonMfproForward->Fill(gData->Getmfpro(muon->GetFmufiCID()));
	fControlMuonMfndfForward->Fill(gData->Getmfndf(muon->GetFmufiCID()));
	fControlMuonMfzForward->Fill(gData->Getmfz(muon->GetFmufiCID()));
      }
    } else if ( muon->GetType() == kBarrel ) {
      if ( muon->GetBrematCut() )
	fControlProbBarrel->Fill(muon->GetProbability());
      if ( muon->GetEtaCut() )
	fControlEtaBarrel->Fill(muon->Eta());
      if ( muon->GetPtCut() )
	fControlPtBarrel->Fill(muon->Pt());
      if ( muon->GetPCut() )
	fControlPBarrel->Fill(muon->P());
      if ( muon->GetFinderCut() )
	FillMuonFinderHisto(muon,fControlMuonFinderBarrel);
      if ( muon->GetBrematCut() )
	fControlChFlgBarrel->Fill(muon->GetChamberFlag());
      if ( muon->GetQualityCut() )
	fControlQualityBarrel->Fill(muon->GetQuality());
      if ( (muon->GetFmufiCID() > 0)&&(muon->GetFmufiCID() < 10)&&muon->GetForwardTrackMuonCut() ) {
	fControlMuonMfproBarrel->Fill(gData->Getmfpro(muon->GetFmufiCID()));
	fControlMuonMfndfBarrel->Fill(gData->Getmfndf(muon->GetFmufiCID()));
	fControlMuonMfzBarrel->Fill(gData->Getmfz(muon->GetFmufiCID()));
      }
    } else if ( muon->GetType() == kRear ) {
      if ( muon->GetBrematCut() )
	fControlProbRear->Fill(muon->GetProbability());
      if ( muon->GetEtaCut() )
	fControlEtaRear->Fill(muon->Eta());
      if ( muon->GetPtCut() )
	fControlPtRear->Fill(muon->Pt());
      if ( muon->GetPCut() )
	fControlPRear->Fill(muon->P());
      if ( muon->GetFinderCut() )
	FillMuonFinderHisto(muon,fControlMuonFinderRear);
      if ( muon->GetBrematCut() )
	fControlChFlgRear->Fill(muon->GetChamberFlag());
      if ( muon->GetQualityCut() )
	fControlQualityRear->Fill(muon->GetQuality());
      if ( (muon->GetFmufiCID() > 0)&&(muon->GetFmufiCID() < 10)&&muon->GetForwardTrackMuonCut() ) {
	fControlMuonMfproRear->Fill(gData->Getmfpro(muon->GetFmufiCID()));
	fControlMuonMfndfRear->Fill(gData->Getmfndf(muon->GetFmufiCID()));
	fControlMuonMfzRear->Fill(gData->Getmfz(muon->GetFmufiCID()));
      }
    }
    if ( muon->GetAllCuts() ) {
      fControlWeight->Fill(muon->GetWeight());
    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GMuons::FillGeneral() called" << endl << endl;

  if ( gCards->GetMUONGeneral() ) {

    fGeneralNMU_uncut->Fill(fNMuons,gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {

      fGeneralNMU->Fill(fBarrelMuons+fForwardMuons+fRearMuons,gHeader->GetWeight());
      fGeneralNMUForward->Fill(fForwardMuons,gHeader->GetWeight());
      fGeneralNMUBarrel->Fill(fBarrelMuons,gHeader->GetWeight());
      fGeneralNMURear->Fill(fRearMuons,gHeader->GetWeight());

    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::ObjectsFillFake(GMuon *muon) {
  //
  // fill general histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMuons::ObjectsFillFake() called" << endl << endl;

  if(gHeader->GetAllCuts()){
  // muon distribution plots with special binning for comparison to fake plots
    if (muon->GetQuality() >3){	
      Int_t mother_id = 0;
      if(muon->GetMCDirectParent()){
	mother_id = muon->GetMCDirectParent()->GetPartID();
      }
      fPt_fakebin->Fill(muon->Pt());
      if(muon->GetMuTrueFl()==1){
	if(muon->Pt()>1.5){
	  fRecTrueMuonMother->Fill(mother_id);
	}
      }
      if(muon->GetQuality()>4){
	if(muon->Pt()>0.75 && muon->Pt()<1.5){ 
	  fEta_lowPt_fakebin->Fill(muon->Eta());
	  fPhi_lowPt_fakebin->Fill(muon->Phi());
	}
      }
      if(muon->Pt()>1.5){
	fEta_highPt_fakebin->Fill(muon->Eta());
	fPhi_highPt_fakebin->Fill(muon->Phi());
      }
      
      if (muon->GetMC()){
	if(gMCs->GetAllCuts()){    	  
	  //	  if ( gCards->GetFMCK() && !(gCards->GetMCOwn()) ) {    
	    Int_t muon_part_id = muon->GetMC()->GetPartID() ;	    
 	    if ((muon_part_id<25 || muon_part_id > 26)){
	      
	      fFakePxvsPxMCTRUE->Fill(muon->GetMC()->Px(),muon->Px(),gHeader->GetWeight(muon));
	      fFakePyvsPyMCTRUE->Fill(muon->GetMC()->Py(),muon->Py(),gHeader->GetWeight(muon));
	      fFakePzvsPzMCTRUE->Fill(muon->GetMC()->Pz(),muon->Pz(),gHeader->GetWeight(muon));
	      fFakePtvsPtMCTRUE->Fill(muon->GetMC()->Pt(),muon->Pt(),gHeader->GetWeight(muon));
	      fFakeEtavsEtaMCTRUE->Fill(muon->GetMC()->Eta(),muon->Eta(),gHeader->GetWeight(muon));
	      
	      //mismatch punch through was ist mit prompten muonen?    
	      fFakeMuonAllPt->Fill(muon->Pt());
	      if(muon->Pt()>1.5){
		fFake2DMuonAll_PtEta->Fill(muon->Eta(),muon->Pt());
		if(muon->GetBrematID()!=0)  fFake2DMuonAll_PtEta_Bremat->Fill(muon->Eta(),muon->Pt());
		if(muon->GetMPMatchID()!=0) fFake2DMuonAll_PtEta_MPMatch->Fill(muon->Eta(),muon->Pt());
		if(muon->GetMuBacID()!=0)   fFake2DMuonAll_PtEta_Bac->Fill(muon->Eta(),muon->Pt());
 
		fFake2DMuonPunch_PtEta->Fill(muon->Eta(),muon->Pt());
	      } 
	      if(muon->Pt()>0.7&&muon->Pt()<1.5 &&muon->GetQuality()>4){
		fFakeMuonAllPhi_lowPt->Fill(muon->Phi());      
		fFakeMuonAllEta_lowPt->Fill(muon->Eta());           
	      }
	      if(muon->Pt()>1.5){
		fFakeMuonAllPhi_highPt->Fill(muon->Phi());           
		fFakeMuonAllEta_highPt->Fill(muon->Eta());            
	      }
	    }
	    //------------------------------------------------------------------------
	    
	    if (muon_part_id==25 || muon_part_id == 26){
	      if (muon->GetMuTrueFl() == -1){
		// decay muonen
		
		Double_t deltapt = (muon->Pt() - muon->GetMC()->Pt())/muon->GetMC()->Pt();
		Double_t deltaptmother = 200;
		Int_t mother_id = 0;
		if(muon->GetMCDirectParent()){
		  mother_id = muon->GetMCDirectParent()->GetPartID();
		  deltaptmother = (muon->Pt()-muon->GetMCDirectParent()->Pt())/muon->GetMC()->Pt();
		}
		
		
		if(muon->Pt()>1.5){
		  if(muon->Eta()<-1.){
		    fPrec_PtruevsDecdistMuon_rear->Fill(muon->GetMuTrueDecayDist(),deltapt,gHeader->GetWeight(muon));
		  
		    if(mother_id>=54 && mother_id<=56 ){
		    fPrec_PtruevsDecdistPion_rear->Fill(muon->GetMuTrueDecayDist(),deltaptmother,gHeader->GetWeight(muon));
		    }
		    fPrec_PtruevsDecdistKaon_rear->Fill(muon->GetMuTrueDecayDist(),deltaptmother,gHeader->GetWeight(muon));
		  }
		  if((muon->Eta()>-1.) && (muon->Eta()<1.)){
		    fPrec_PtruevsDecdistMuon_central->Fill(muon->GetMuTrueDecayDist(),deltapt,gHeader->GetWeight(muon));
		    if(mother_id>=54 && mother_id<=56 ){
		      fPrec_PtruevsDecdistPion_central->Fill(muon->GetMuTrueDecayDist(),deltaptmother,gHeader->GetWeight(muon)); 
		    }
		    if(mother_id >=58 && mother_id <=59){
		      fPrec_PtruevsDecdistKaon_central->Fill(muon->GetMuTrueDecayDist(),deltaptmother,gHeader->GetWeight(muon));
		    }
		  }
		  if(muon->Eta()>1.){
		    fPrec_PtruevsDecdistMuon_forward->Fill(muon->GetMuTrueDecayDist(),deltapt,gHeader->GetWeight(muon));
		    if(mother_id>=54 && mother_id<=56 ){
		      fPrec_PtruevsDecdistPion_forward->Fill(muon->GetMuTrueDecayDist(),deltaptmother,gHeader->GetWeight(muon));
		  }
		    if(mother_id >=58 && mother_id <=59){
		      fPrec_PtruevsDecdistKaon_forward->Fill(muon->GetMuTrueDecayDist(),deltaptmother,gHeader->GetWeight(muon));
		    }
		  }
		}
		
		fFakePxvsPxMCTRUE->Fill(muon->GetMC()->Px(),muon->Px(),gHeader->GetWeight(muon));
		fFakePyvsPyMCTRUE->Fill(muon->GetMC()->Py(),muon->Py(),gHeader->GetWeight(muon));
		fFakePzvsPzMCTRUE->Fill(muon->GetMC()->Pz(),muon->Pz(),gHeader->GetWeight(muon));
		fFakePtvsPtMCTRUE->Fill(muon->GetMC()->Pt(),muon->Pt(),gHeader->GetWeight(muon));	  
		fFakeEtavsEtaMCTRUE->Fill(muon->GetMC()->Eta(),muon->Eta(),gHeader->GetWeight(muon));
		
		//-------------------------------------------------------------------------------
		fFakeMuonAllPt->Fill(muon->Pt());
		if(muon->Pt()>1.5){

		  fFake2DMuonAll_PtEta->Fill(muon->Eta(),muon->Pt());
		  if(muon->GetBrematID()!=0)  fFake2DMuonAll_PtEta_Bremat->Fill(muon->Eta(),muon->Pt());
		  if(muon->GetMPMatchID()!=0) fFake2DMuonAll_PtEta_MPMatch->Fill(muon->Eta(),muon->Pt());
		  if(muon->GetMuBacID()!=0)   fFake2DMuonAll_PtEta_Bac->Fill(muon->Eta(),muon->Pt());
		  
		  fFake2DMuonDecay_PtEta->Fill(muon->Eta(),muon->Pt());
		}
		if(muon->Pt()>0.7&&muon->Pt()<1.5 &&muon->GetQuality()>4){
		  fFakeMuonAllPhi_lowPt->Fill(muon->Phi());      
		  fFakeMuonAllEta_lowPt->Fill(muon->Eta());           
		}
		if(muon->Pt()>1.5){
		  fFakeMuonAllPhi_highPt->Fill(muon->Phi());           
		  fFakeMuonAllEta_highPt->Fill(muon->Eta());            
		}
		
		  if(mother_id>=54 && mother_id<=56 ){
		    fFakeDecayMuonPionPt->Fill(muon->Pt());
		    fFakeMuonPionPt->Fill(muon->Pt());
		    if(muon->Pt()>0.7&&muon->Pt()<1.5 &&muon->GetQuality()>4){
		      fFakeDecayMuonPionEta_lowPt->Fill(muon->Eta());   
		      fFakeDecayMuonPionPhi_lowPt->Fill(muon->Phi());
		      fFakeMuonPionEta_lowPt->Fill(muon->Eta());   
		      fFakeMuonPionPhi_lowPt->Fill(muon->Phi());
		    }   
		  if(muon->Pt()>1.5){
		    fFakeDecayMuonPionEta_highPt->Fill(muon->Eta());   
		    fFakeDecayMuonPionPhi_highPt->Fill(muon->Phi());   
		    fFakeMuonPionEta_highPt->Fill(muon->Eta());   
		    fFakeMuonPionPhi_highPt->Fill(muon->Phi());   
		  }
		}
		if(mother_id >=58 && mother_id <=59){
		  fFakeDecayMuonKaonPt->Fill(muon->Pt());
		  fFakeMuonKaonPt->Fill(muon->Pt());
		  if(muon->Pt()>0.7&&muon->Pt()<1.5 && muon->GetQuality()>4){
		    fFakeDecayMuonKaonEta_lowPt->Fill(muon->Eta());   
		    fFakeDecayMuonKaonPhi_lowPt->Fill(muon->Phi());
		    fFakeMuonKaonEta_lowPt->Fill(muon->Eta());   
		    fFakeMuonKaonPhi_lowPt->Fill(muon->Phi());
		  }
		  if(muon->Pt()>1.5){   
		    fFakeDecayMuonKaonEta_highPt->Fill(muon->Eta());   
		    fFakeDecayMuonKaonPhi_highPt->Fill(muon->Phi());   
		    fFakeMuonKaonEta_highPt->Fill(muon->Eta());   
		    fFakeMuonKaonPhi_highPt->Fill(muon->Phi());   
		  }
		}
		
	      } 
	    }
	    
	    
	    
	    //------------------------------------------------------------------------	    
	    
	    
	    if (muon_part_id!=25 && muon_part_id != 26){
	      if(muon->GetMCDirectParent()){
		// punch throughs 
		
		if(muon_part_id>=54 && muon_part_id<=56 ){
		  fFakePunchMuonPionPt->Fill(muon->Pt());
		  fFakeMuonPionPt->Fill(muon->Pt());
		  if(muon->Pt()>0.7&&muon->Pt()<1.5 &&muon->GetQuality()>4){
		    fFakePunchMuonPionEta_lowPt->Fill(muon->Eta());   
		    fFakePunchMuonPionPhi_lowPt->Fill(muon->Phi());
		    fFakeMuonPionEta_lowPt->Fill(muon->Eta());   
		    fFakeMuonPionPhi_lowPt->Fill(muon->Phi());
		  }   
		  if(muon->Pt()>1.5){
		    fFakePunchMuonPionEta_highPt->Fill(muon->Eta());   
		    fFakePunchMuonPionPhi_highPt->Fill(muon->Phi());   
		    fFakeMuonPionEta_highPt->Fill(muon->Eta());   
		    fFakeMuonPionPhi_highPt->Fill(muon->Phi());   
		  }
		}
		
		if(muon_part_id >=58 && muon_part_id <=59){
		  fFakePunchMuonKaonPt->Fill(muon->Pt());
		  fFakeMuonKaonPt->Fill(muon->Pt());
		  if(muon->Pt()>0.7&&muon->Pt()<1.5 && muon->GetQuality()>4){
		    fFakePunchMuonKaonEta_lowPt->Fill(muon->Eta());   
		    fFakePunchMuonKaonPhi_lowPt->Fill(muon->Phi());
		    fFakeMuonKaonEta_lowPt->Fill(muon->Eta());   
		    fFakeMuonKaonPhi_lowPt->Fill(muon->Phi());
		  }
		  if(muon->Pt()>1.5){   
		    fFakePunchMuonKaonEta_highPt->Fill(muon->Eta());   
		    fFakePunchMuonKaonPhi_highPt->Fill(muon->Phi());   
		    fFakeMuonKaonEta_highPt->Fill(muon->Eta());   
		    fFakeMuonKaonPhi_highPt->Fill(muon->Phi());   
		  }
		}
	      }
	    }
	  }
	}
      }
    }

  return kTRUE;
}
//_____________________________________________________________

Bool_t GMuons::FillMuonFinderHisto(GMuon *muon, TH1D* histo, Double_t weight) {
  //
  // fill muon finder histo
  if ( gDebug ) cout << endl << "GMuons::FillMuonFinderHisto called" << endl << endl;

  if ( muon->GetGlomuID() > 0 )
    histo->Fill("Glomu",weight);
  if ( muon->GetBrematID() > 0 )
    histo->Fill("Bremat",weight);
  if ( muon->GetBacMatID() > 0 )
    histo->Fill("BacMat",weight);
  if ( muon->GetMuBacID() > 0 )
    histo->Fill("MuBac",weight);
  if ( muon->GetMammaID() > 0 )
    histo->Fill("Mamma",weight);
  if ( muon->GetMPMatchID() > 0 )
    histo->Fill("MPMatch",weight);
  if ( muon->GetMufoID() > 0 )
    histo->Fill("Mufo",weight);
  if ( muon->GetMipID() > 0 )
    histo->Fill("Mip",weight);
  if ( muon->GetMvID() > 0 )
    histo->Fill("Mv",weight);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::ModifyMuonQuality(GMuon *muon) {
  //
  // modif muon quality to correct some problems in quality selection 
  if ( gDebug ) cout << endl << "GMuons::ModifyMuonQuality() called" << endl << endl;
  Double_t local_quality = muon->GetQuality();
  Double_t local_quality_save;
  Bool_t Achim = kFALSE;  // if true achims efficiency files are used

  // don't do anything if it's one of Ursulas famous fake muons 
  if (muon->GetQuality()== 99) return kTRUE;

  //  Bool_t do_achim = true;
  //Check and set flag that this muon has been run through this routine (calling twice is NOT ALLOWED! :o) )
  if(  muon->GetHasBeenQualModified() == kTRUE ) cout<<"ALARM! The quality of this Muon: run/event/muon: "<<gData->Getrunnr()<<"/"<<gData->Geteventnr()<<"/"<<muon->GetID()<<" is being corrected twice! VERY BAD!"<<endl;
  muon->SetHasBeenQualModified(kTRUE);
  //  cout<<"*************** Info: The quality of this Muon: run/event/muon: "<<gData->Getrunnr()<<"/"<<gData->Geteventnr()<<"/"<<muon->GetID()<<" is being corrected first time"<<endl;
  if(gCards->GetMuqualServicePack1()) {
    //**********************************************************************************************************;
    //******************* Achim's muquana START ****************************************************************;
    //**********************************************************************************************************;
    //       integer jj, printflag
    Int_t printflag = 0;
    Double_t randnr = -999;
    Double_t efficorrBACl = 1.;
    Double_t efficorrBACt = 1.;
    Double_t efficorrMPMATCHl = 1.;
    Double_t efficorrMPMATCHt = 1.;
    Double_t efficorrBREMATl = 1.;
    Double_t efficorrBREMATt = 1.;
    Double_t efficorrFIX = 1.;
    //    Int_t    ndf;
    //       real muquac, rvec(1), muz, muquac_save
    //       integer ndf
    // c
    //      muquac = muqual(jj)
    //      printflag = 0 
    //      if (muqual(jj).ge.4) then
    if(local_quality >= 4){
      //c
      //c       interesting muon, reproduce muon quality
      // c       same categories as below
      // c       make sure to change both simultaneously!
      // c
      //        if (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
      if(muon->GetBrematID()>0 && muon->GetProbability()>0.01
	 //     +      .and.muchfl(jj).eq.3.and.mutrfl(jj).eq.2) then
	 && muon->GetChamberFlag()==3 && muon->GetTrackFlag()==2) {
	//* (1)  BREMAT 5 dof,  very frequent;
	//          if (muquac.ne.6) printflag = 6 ;
	if(local_quality != 6) printflag = 6; 
	//        elseif ((MUMPMAT(jj).gt.0.or.MUMUFO(jj).gt.0).and.
      }
      else if((muon->GetMPMatchID()>0 || muon->GetMufoID()>0)
	      //     +          mupmat(jj).gt.0.05.and.mutrfl(jj).gt.0) then 
	      && muon->GetProbability()>0.05 && muon->GetTrackFlag()>0 ) {
	//* (2)  standard MPMATCH, frequent;
	//          if (muquac.ne.6) printflag = 6;
	if(local_quality != 6) printflag = 6; 
      
	//        elseif ((MUMPMAT(jj).gt.0.or.MUMUFO(jj).gt.0).and.
      }
      else if((muon->GetMPMatchID()>0 || muon->GetMufoID()>0)
	      //     +          mupmip(jj).gt.0.6.and.mutrfl(jj).gt.0) then
	      && muon->GetCalProbMV()>0.6 && muon->GetTrackFlag()>0 ) {
	//* (2a)  MPMATCH/MUFO with low prob but MV, very rare;
	//* ... muqual 5 part not yet understood;
	//          if (muquac.ne.6.and.muquac.ne.5) printflag = 6
	if(local_quality != 6 && local_quality != 5) printflag = 6; 

	//        elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()>0.01 
	      //     +     .and.muchfl(jj).eq.1.and.mutrfl(jj).eq.2
	      &&  muon->GetChamberFlag()==1 && muon->GetTrackFlag()==2 
	      //     +     .and.mupmip(jj).gt.0.and.muqual(jj).eq.6) then
	      &&  muon->GetCalProbMV()>0. && muon->GetQuality()==6 ) {
	//* BREMAT 4dof + low quality MV + no muth cut, very rare;
	//* not understood;
	//          if (muquac.ne.6) printflag = 4
	if(local_quality != 6) printflag = 4; 

	//        elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()>0.01 
	      //     +     .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	      && muon->GetTrackFlag()==2 &&  muon->GetCalProbMV()>0.6 
	      //     +     .and.abs(log(tan(muth(jj)/2.))).gt.0.6) then
	      && TMath::Abs(muon->Eta())>0.6)  {
	//* (3) BREMAT 4dof + MV, large angle, frequent;
	//* quality should be 5 ;
	//* due to a bug in fill_gmuon raising the quality twice for MV;
	//* it is sometimes 6, and often stays 4;
	//         if (muquac.ne.6.and.muquac.ne.5.and.muquac.ne.4) 
	//     +     printflag = 5
	if(local_quality != 6 && local_quality != 5 && local_quality != 4) printflag = 5; 

	//        elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).lt.0.01
      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()<0.01 
	      //     +     .and.muchfl(jj).eq.3.and.mutrfl(jj).eq.2
	      &&  muon->GetChamberFlag()==3 && muon->GetTrackFlag()==2 
	      //     +     .and.mupmip(jj).gt.0.6) then
	      && muon->GetCalProbMV()>0.6  ) {
	// * (1a) low probability BREMAT 5dof + MV, rare  ;
	// * quality should be 5  ("feature" of 4-dof/5-dof separation);
	// * due to a bug in fill_gmuon raising the quality twice for MV;
	// * it is sometimes 6, and often stays 4;
	//          if (muquac.ne.6.and.muquac.ne.5.and.muquac.ne.4) 
	//      +     printflag = 5
	if(local_quality != 6 && local_quality != 5 && local_quality != 4) printflag = 5; 

	//        elseif (MUBREMAT(jj).gt.0
      }
      else if(muon->GetBrematID()>0
	      //     +     .and.mutrfl(jj).eq.2.and.MUMV(jj).gt.0
	      &&  muon->GetTrackFlag()==2 && muon->GetMvID()>0 
	      //     +     .and.abs(log(tan(muth(jj)/2.))).gt.0.6
	      && TMath::Abs(muon->Eta())>0.6 
	      //     +     .and.muqual(jj).eq.6) then
	      && muon->GetQuality()==6 ) {
	// * BREMAT 4dof (sometimes low quality) + low quality MV, large angle, very rare;
	// * ... not understood,  further bug?;
	// * due to a bug in fill_gmuon raising the quality twice for MV;
	// * it is sometimes 6, and often stays 4;
	//         if (muquac.ne.6) printflag = 4
	if(local_quality != 6) printflag = 4; 

	//        elseif (MUMUBAC(jj).gt.0
      }
      else if(muon->GetMuBacID()>0 
	      //     +     .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	      &&  muon->GetTrackFlag()==2 && muon->GetCalProbMV()>0.6 
	      //     +     .and.abs(log(tan(muth(jj)/2.))).gt.0.6) then
	      &&  TMath::Abs(muon->Eta())>0.6) {
	// * (4) MUBAC + MV,   large angle,  very frequent
	// * ... muqual 4 part (rare) not understood
	//         if (muquac.ne.5.and.muquac.ne.4) printflag = 5
	if(local_quality != 5 && local_quality != 4) printflag = 5; 

	//        elseif (MUMUBAC(jj).gt.0.
      }
      else if(muon->GetMuBacID()>0 
	      //     +    .and.MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
	      && muon->GetBrematID()>0 &&  muon->GetProbability()>0.01 
	      //     +    .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	      && muon->GetTrackFlag()==2 && muon->GetCalProbMV()>0.6 
	      //     +    .and.abs(log(tan(muth(jj)/2.))).lt.0.6) then
	      //WARNING!!! .le. would be "correct" here. 050331
	      &&   TMath::Abs(muon->Eta())<0.6) {
	// * (5) BREMAT + MUBAC + MV,  low angle,  frequent;
	//          if (muquac.ne.5) printflag = 5
	if(local_quality != 5) printflag = 5; 

	//        elseif (MUMUBAC(jj).gt.0.
      }
      else if(muon->GetMuBacID()>0 
	      //     +    .and.MUBREMAT(jj).gt.0.
	      && muon->GetBrematID()>0 
	      //     +    .and.mutrfl(jj).gt.0.and.mupmip(jj).gt.0.6) then
	      && muon->GetTrackFlag()>0 && muon->GetCalProbMV()>0.6 ) {
	// * (5a) BREMAT + MUBAC + MV, not vtx ass. or bad match, frequent
	// * modify -> 4?
	//         if (muquac.ne.5) printflag = 5
	if(local_quality != 5) printflag = 5; 

	//        elseif (MUMUBAC(jj).gt.0
      }
      else if(muon->GetMuBacID()>0 
	      //     +    .and.mutrfl(jj).ne.2.and.mupmip(jj).gt.0.6
	      &&  muon->GetTrackFlag()!=2 && muon->GetCalProbMV()>0.6 
	      //     +    .and.abs(log(tan(muth(jj)/2.))).gt.0.6) then
	      && TMath::Abs(muon->Eta())>0.6 ) {
	// * (4a) MUBAC + MV large angle, no vertex association required!
	// * rare! not very clean. normal.  if forward -> 4 
	//         if (muquac.ne.5) printflag = 5
	if(local_quality != 5) printflag = 5; 
        
	//        elseif ((MUMPMAT(jj).gt.0.or.MUMUFO(jj).gt.0).and.
      }
      else if( (muon->GetMPMatchID()>0 || muon->GetMufoID()>0) 
	       //     +          mupmat(jj).lt.0.05.and.mutrfl(jj).gt.0) then
	       && muon->GetProbability()<0.05 && muon->GetTrackFlag()>0 ) {
	// * (2b) MPMATCH or MUFO with track, low prob,  rare
	// * quality often reduced later
	//          if (muquac.ne.5) printflag = 5         
	if(local_quality != 5) printflag = 5; 

	//        elseif (MUMUFO(jj).gt.0.and.mutrfl(jj).eq.0
      }
      else if(muon->GetMufoID()>0 && muon->GetTrackFlag()==0 
	      //     +      .and.muqual(jj).eq.5) then
	      && muon->GetQuality()==5 ){
	// * (9) MUFO without track with good vtx, frequent
	// * quality often reduced later
	//         if (muquac.ne.5) printflag = 5         
	if(local_quality != 5) printflag = 5; 

	//        elseif (MUMAMMA(jj).gt.0.and.mutrfl(jj).gt.0
      }
      else if(muon->GetMammaID()>0 && muon->GetTrackFlag()>0 
	      //     +      .and.muqual(jj).eq.5) then
	      && muon->GetQuality()==5 ){
	// * (10) MAMMA with track, rare
	// * quality often reduced later
	//         if (muquac.ne.5) printflag = 5 
	if(local_quality != 5) printflag = 5; 

	//        elseif (MUMUBAC(jj).gt.0.and.MUMPMAT(jj).lt.0
      }
      else if(muon->GetMuBacID()>0 && muon->GetMPMatchID()<0 
	      //     +      .and.muqual(jj).eq.5) then
	      &&  muon->GetQuality()==5 ) {
	// * MUBAC + MFRTZ, very rare
	// * ... not understood                
	//          if (muquac.ne.5) printflag = 5        
	if(local_quality != 5) printflag = 5; 

	//        elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()>0.01 
	      //     +     .and.mutrfl(jj).eq.2) then
	      && muon->GetTrackFlag()==2){
	// * (6) good BREMAT 4dof, very frequent
	//         if (muquac.ne.4) printflag = 4         
	if(local_quality != 4) printflag = 4; 

	//        elseif (MUMUBAC(jj).gt.0
      }
      else if(muon->GetMuBacID()>0 
	      //     +     .and.mutrfl(jj).eq.2.and.mubacfl(jj).lt.50) then 
	      && muon->GetTrackFlag()==2 && muon->GetBacFlag()<50){
	//* (7) good BAC, very frequent 
	  //         if (muquac.ne.4) printflag = 4
	  if(local_quality != 4) printflag = 4; 
         
	//        elseif (MUMUBAC(jj).gt.0.
      }
      else if(muon->GetMuBacID()>0 
	      //     +     .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	      &&  muon->GetTrackFlag()==2 && muon->GetCalProbMV()>0.6 
	      //     +     .and.abs(log(tan(muth(jj)/2.))).lt.0.6) then
	      && TMath::Abs(muon->Eta())<0.6){
	// * (8) reasonable central BAC + MV, frequent
	//         if (muquac.ne.4) printflag = 4
	if(local_quality != 4) printflag = 4; 

	//        elseif (MUMUBAC(jj).gt.0.
      }
      else if(muon->GetMuBacID()>0 
	      //     +      .and.mutrfl(jj).ne.2.and.mupmip(jj).gt.0.) then
	      &&  muon->GetTrackFlag()!=2 && muon->GetCalProbMV()>0. ){
	// * (4b) MUBAC + MV, not vertex associated, very rare
	//         if (muquac.ne.4) printflag = 4
	if(local_quality != 4) printflag = 4; 

	//        elseif (MUMUBAC(jj).gt.0..and.MUMIP(jj).gt.0) then
      }
      else if(muon->GetMuBacID()>0 && muon->GetMipID()>0){
	// * (4c) any BAC + MIP 
	//         if (muquac.ne.4) printflag = 4
	if(local_quality != 4) printflag = 4; 
                  
	//        elseif (MUMUFO(jj).gt.0.and.mutrfl(jj).eq.0
      }
      else if(muon->GetMufoID()>0 && muon->GetTrackFlag()==0 
	      //     +    .and.muqual(jj).eq.4) then
	      &&  muon->GetQuality()==4 ){
	// * (9a) MUFO w/o track, very rare (bug! should be more frequent)
	//         if (muquac.ne.4) printflag = 4
	if(local_quality != 4) printflag = 4; 

	//        elseif (MUMPMAT(jj).lt.0.and.mutrfl(jj).eq.0
      }
      else if(muon->GetMPMatchID()<0 && muon->GetTrackFlag()==0 
	      //     +    .and.mupmip(jj).gt.0.6.and.muqual(jj).eq.4) then
	      && muon->GetCalProbMV()>0.6 && muon->GetQuality()==4 ){
	// * (11) MFRTZ w/o track + MV, very rare (bug! should be more frequent)
	//         if (muquac.ne.4) printflag = 4
	if(local_quality != 4) printflag = 4; 
      
	//        elseif (MUMAMMA(jj).gt.0.and.mutrfl(jj).eq.0
      }
      else if(muon->GetMammaID()>0 && muon->GetTrackFlag()==0 
	      //     +    .and.muqual(jj).eq.4) then
	      && muon->GetQuality()==4 ){
	// * (10a) MAMMA, rare  (bug?) 
	//         if (muquac.ne.4) printflag = 4
	if(local_quality != 4) printflag = 4; 
      
	//        endif
      }

      //        if (printflag.gt.0) then 
      if(printflag>0){
	//           print *,'*** muqual',muqual(jj),'classified',printflag;
	//           print *,'*** run/evt',runnr, eventnr, jj;
	//       print *,'  BREMAT,    MPMAT,    MUFO,    MUBAC,    MV,   MUGLOMU,';
	// *     +           //'  MUCHFL, MUPMAT, MUTRFL';
	//           print *,MUBREMAT(jj),MUMPMAT(jj),MUMUFO(JJ),;
	//      +            MUMUBAC(jj),MUMV(jj),MUGLOMU(jj),MUCHFL(jj),;
	//      +            MUPMAT(jj),MUTRFL(jj),MUPMIP(jj);
	//           print *, 'eta:', abs(log(tan(muth(jj)/2.)));
	cout<<"*** muqual "<<muon->GetQuality()<<" classified "<<printflag<<" local_quality: "<<local_quality<<endl;
	cout<<"*** run/evt "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<muon->GetID()<<endl;
	cout<<"  BREMAT,    MPMAT,    MUFO,    MUBAC,    MV,   MUGLOMU,  MUCHFL, MUPMAT,   MUTRFL, CalProbMV"<<endl;
	cout<<"  "<<muon->GetBrematID()<<"          "<<muon->GetMPMatchID()<<"         "<<muon->GetMufoID()<<"        "<<muon->GetMuBacID()
	    <<"         "<<muon->GetMvID()<<"     "<<muon->GetGlomuID()<<"         "<<muon->GetChamberFlag()
	    <<"       "<<muon->GetProbability()<<"  "<<muon->GetTrackFlag()<<"            "<<muon->GetCalProbMV()<<endl;
	cout<<"eta: "<<muon->Eta()<<endl;
	//        endif;
      }
    
      //      endif
    }

    //3 lines below should not be needed:  
    //     // reset local muon quality after cross check (above)
    //     // to now recalculate if after efficiency simulation.
    //     local_quality = -9;
    
    // c
    // c   now change efficiencies for MC
    // c
    //      if (runnr.le.101) then
    if(gData->Getrunnr() <= 101 && gCards->GetMuqualBasedEffCorr()){ //&& (42 != 42)
      
      // Get values for efficiency corrections by finder:
      if( gCards->GetMUONReadEfficiencyFiles() ){
	  TString filename = gSystem->Getenv("GUTCODEDIR");
	  filename.Append("/analysis/efficiencies/efficomp07.root");
	  TFile *file = 0;
	  TH2D *brempmlhist = 0;
	  TH2D *mubaclhist = 0;
	  TH2D *brempmthist =0;
	  TH2D *mubacthist = 0;
	  if(Achim){
	    file = new TFile(filename);
	    brempmlhist = (TH2D*)file->Get("h10000");
	    mubaclhist = (TH2D*)file->Get("h30000");
	    brempmthist = (TH2D*)file->Get("h40000");
	    mubacthist = (TH2D*)file->Get("h60000");
	  }
	//****;
	// Get BREMAT efficiency correction values for muon:;
	//****;
	if(Achim){
	  Int_t bin = brempmlhist->FindBin(muon->Eta(),muon->Pt());
	  efficorrBREMATl = brempmlhist->GetBinContent(bin);
	  bin = brempmthist->FindBin(muon->Eta(),muon->Pt());
	  efficorrBREMATt = brempmthist->GetBinContent(bin);
	}else{
	efficorrBREMATl = gMuonEfficiency->GetLooseBarrelEfficiencyBREMATData(muon)/gMuonEfficiency->GetLooseBarrelEfficiencyBREMATMC(muon); // number from Oli
	efficorrBREMATt = gMuonEfficiency->GetTightBarrelEfficiencyBREMATData(muon)/gMuonEfficiency->GetTightBarrelEfficiencyBREMATMC(muon); // number from Oli
	// special cases when correction fails due to statistics limitation (should be very rare!):
	}
	if(efficorrBREMATl == 0. || TMath::IsNaN(efficorrBREMATl) ) {
	  if(muon->Eta() < 2.)  efficorrBREMATl = 0.60; // Achim's numbers
	  else   efficorrBREMATl = 0.80; // Achim's numbers
	}
	if(efficorrBREMATt == 0. || TMath::IsNaN(efficorrBREMATt) ) {
	  if(muon->Eta() < 2.)  efficorrBREMATt = 0.60; // Achim's numbers
	  else   efficorrBREMATt = 0.80; // Achim's numbers
	}
	//  	  cout<<"***** efficiency correction factor from oli: BREMA loose "<<setw(8)<<gMuonEfficiency->GetLooseBarrelEfficiencyBREMATData(muon)/gMuonEfficiency->GetLooseBarrelEfficiencyBREMATMC(muon)<<" use this: "<<setw(8)<<efficorr<<endl;
	//  	  cout<<"***** efficiency correction factor from oli: BREMA tight "<<setw(8)<<gMuonEfficiency->GetTightBarrelEfficiencyBREMATData(muon)/gMuonEfficiency->GetTightBarrelEfficiencyBREMATMC(muon)<<" use this: "<<setw(8)<<efficorr<<endl;
	//****;
	// Get BAC efficiency correction value for muon:;
	//****;
	if(Achim){
	  Int_t bin = mubaclhist->FindBin(muon->Eta(),muon->Pt());
	  efficorrBACl = mubaclhist->GetBinContent(bin);
	  bin = mubacthist->FindBin(muon->Eta(),muon->Pt());
	  efficorrBACt = mubacthist->GetBinContent(bin);
	}else{
	  efficorrBACl = gMuonEfficiency->GetLooseBarrelEfficiencyMUBACData(muon)/gMuonEfficiency->GetLooseBarrelEfficiencyMUBACMC(muon); // number from Oli
	  efficorrBACt = gMuonEfficiency->GetTightBarrelEfficiencyMUBACData(muon)/gMuonEfficiency->GetTightBarrelEfficiencyMUBACMC(muon); // number from Oli
	// special cases when correction fails due to statistics limitation (should be very rare!):
	}
	if(efficorrBACl == 0. || TMath::IsNaN(efficorrBACl) ) {
	  efficorrBACl = 0.80; // Achim's numbers
	}
	if(efficorrBACt == 0. || TMath::IsNaN(efficorrBACt) ) {
	  efficorrBACt = 0.80; // Achim's numbers
	}
	//  	  cout<<"***** efficiency correction factor from oli: BAC loose  "<<setw(8)<<gMuonEfficiency->GetLooseBarrelEfficiencyMUBACData(muon)/gMuonEfficiency->GetLooseBarrelEfficiencyMUBACMC(muon)<<" use this: "<<setw(8)<<efficorr<<endl;
	//  	  cout<<"***** efficiency correction factor from oli: BAC tight  "<<setw(8)<<gMuonEfficiency->GetTightBarrelEfficiencyMUBACData(muon)/gMuonEfficiency->GetTightBarrelEfficiencyMUBACMC(muon)<<" use this: "<<setw(8)<<efficorr<<endl;
	//****;
	// Get MPMATCH efficiency correction value for muon:
	//****;
	if(Achim){
	  Int_t bin = brempmlhist->FindBin(muon->Eta(),muon->Pt());
	  efficorrMPMATCHl = brempmlhist->GetBinContent(bin);
	  bin = brempmthist->FindBin(muon->Eta(),muon->Pt());
	  efficorrMPMATCHt = brempmthist->GetBinContent(bin);

	}else{
	  efficorrMPMATCHl = gMuonEfficiency->GetLooseForwardEfficiencyMPMATCHData(muon) / gMuonEfficiency->GetLooseForwardEfficiencyMPMATCHMC(muon); // number from Oli
	  efficorrMPMATCHt = gMuonEfficiency->GetTightForwardEfficiencyMPMATCHData(muon) / gMuonEfficiency->GetTightForwardEfficiencyMPMATCHMC(muon); // number from Oli
	  // special cases when correction fails due to statistics limitation (should be very rare!):
	}
	if(efficorrMPMATCHl == 0. || TMath::IsNaN(efficorrMPMATCHl) ) {
	  if(muon->Eta() < 2.)  efficorrMPMATCHl = 0.60; // Achim's numbers
	  else   efficorrMPMATCHl = 0.80; // Achim's numbers
	}
	if(efficorrMPMATCHt == 0. || TMath::IsNaN(efficorrMPMATCHt) ) {
	  if(muon->Eta() < 2.)  efficorrMPMATCHt = 0.60; // Achim's numbers
	  else   efficorrMPMATCHt = 0.80; // Achim's numbers
	}
	//  	  cout<<"***** efficiency correction factor from oli: MPMAT loose "<<setw(8)<<gMuonEfficiency->GetLooseForwardEfficiencyMPMATCHData(muon) / gMuonEfficiency->GetLooseForwardEfficiencyMPMATCHMC(muon)<<setw(8)<<" use this: "<<efficorr<<endl;
	//  	  cout<<"***** efficiency correction factor from oli: MPMAT tight "<<setw(8)<<gMuonEfficiency->GetTightForwardEfficiencyMPMATCHData(muon) / gMuonEfficiency->GetTightForwardEfficiencyMPMATCHMC(muon)<<setw(8)<<" use this: "<<efficorr<<endl;
	//****;
	// Get BREMAT outer efficiency correction value for muon: (no efficiencies from data - estimation!)
	//****;
	efficorrFIX = 0.8; // achims numbers 

	if(file) delete file;
       	//if(brempmthist != 0) delete brempmthist;
	//if(mubaclhist != 0)  delete mubaclhist;
	//if(brempmthist != 0) delete brempmthist;
	//if(mubacthist != 0)  delete mubacthist;

      }
      else {
	//	cout<<(char)27<<"[01;31m"<<"ALARM from MuqualBasedEfficiencyCorrection in GMuons.cxx: You have activated the correction, but forgot"<<endl;
	//	cout<<(char)27<<"[01;31m"<<"to activate the card READEFFICIENCYFILES, which needs to be active. Setting correction to NEUTRAL."<<endl;
	efficorrBREMATl   = 1.0;  // neutral
	efficorrBREMATt   = 1.0;  // neutral
	efficorrBACl      = 1.0;  // neutral
	efficorrBACt      = 1.0;  // neutral
	efficorrMPMATCHl  = 1.0;  // neutral
	efficorrMPMATCHt  = 1.0;  // neutral
	efficorrFIX       = 1.0;  // neutral
      }
      //*******************************************************************************;
      // Strategy for correction: 
      //    first correct BAC, depending on whether MC is set or not
      //    then correct muon chambers, depending on whether MV/BAC
      //    are set or not.
      //*******************************************************************************;
      // Correct Bac efficiency:    ;
      //         if (MUMUBAC(jj).gt.0) then;
      if(muon->GetMuBacID()>0) {
	//c    correct for BAC efficiency
	//          call ranmar(rvec,1)
	randnr = randgen->Rndm();
	//           if (mupmip(jj).ge.0.6.and.rvec(1).gt.effbaccorl .or.
	//      +        mupmip(jj).lt.0.6.and.rvec(1).gt.effbaccort) then
	if( ( muon->GetCalProbMV() >= 0.6 && randnr > efficorrBACl )
	    ||
	    ( muon->GetCalProbMV() < 0.6 && randnr > efficorrBACt )
	    ){ 
	  //            MUMUBAC(jj)=0
	  muon->SetMuBacID(0);
	  //          endif
	}
	//        endif
      }
      
      //         If (muchfl(jj).gt.0.and.muchfl(jj).lt.4) then
      if(muon->GetChamberFlag()>0 && muon->GetChamberFlag()<4){
	// c    correct for barrel/rear chamber efficiency
	//           if (muchfl(jj).eq.3) then
 	if(muon->GetChamberFlag()==3) {
	  // c    correct for outer chamber efficiency
	  //             call ranmar(rvec,1)
 	  randnr = randgen->Rndm();
	  //             if (rvec(1).gt.0.8) then
 	  if(randnr>efficorrFIX) {
	    //               muchfl(jj)=1
 	    muon->SetChamberFlag(1);	
	    //             endif
	  }
	  //           endif
	}
	//           call ranmar(rvec,1)
 	randnr = randgen->Rndm();
	// c    loose matching if outer or both MV and BAC
	// c    else tight matching
	//           if ((muchfl(jj).eq.3.and.rvec(1).gt.effmucorl) .or.
	if( ( muon->GetChamberFlag()==3 && randnr > efficorrBREMATl )
	    || 
	    //      +        (mupmip(jj).gt.0.6.and.MUMUBAC(jj).gt.0.and.rvec(1).gt.effmucorl) .or.
	    ( muon->GetCalProbMV()>0.6 && muon->GetMuBacID()>0 && randnr > efficorrBREMATl )
	    ||
	    //      +        rvec(1).gt.effmucort) then
	    ( randnr > efficorrBREMATt )
	    ) {
	  //             MUBREMAT(jj)=0
	  muon->SetBrematID(0);
	  //             if (rvec(1).gt.effmucorl) then
	  if(randnr > efficorrBREMATl ){
	    //               MUGLOMU(jj)=0
	    muon->SetGlomuID(0);
	    //               muchfl(jj)=0
	    muon->SetChamberFlag(0);
	    //             endif
	  }
	  //           endif
	}
	//         endif
      }
      
      //         if (muchfl(jj).gt.3) then
      if(muon->GetChamberFlag()>3){
	// c    correct for forward efficiency
	//           call ranmar(rvec,1)
	randnr = randgen->Rndm();
	//           if (mupmip(jj).ge.0.6.and.rvec(1).gt.effmucorl .or.
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	// ALAAARMM!!!! 050815 here should be MPMATCH efficiency!!!! shouldn't it?!?!?!?!?!?
	//	if( ( muon->GetCalProbMV() > 0.6 && randnr > efficorrBREMATl )
	if( ( muon->GetCalProbMV() > 0.6 && randnr > efficorrMPMATCHl )
	    ||
	    //      +        mupmip(jj).lt.0.6.and.rvec(1).gt.effmucort .or.
	    //	    ( muon->GetCalProbMV() < 0.6 && randnr > efficorrBREMATt )
	    ( muon->GetCalProbMV() < 0.6 && randnr > efficorrMPMATCHt )
	    //               fmutake_t.ne.1) then
	    ){
	  //             MUMPMAT(jj)=0
	  muon->SetMPMatchID(0);
	  //             MUMUFO(jj)=0
	  muon->SetMufoID(0);
	  //             MUMAMMA(jj)=0
	  muon->SetMammaID(0);
	  //             MUCHFL(jj)=0
	  muon->SetChamberFlag(0);
	  //           endif
	}
	//         endif
      }
      
      // Muon finder Bools are reevaluated after efficiency correction. (e.g. muon->GetBac() etc.)
      // These two should be all there are. Hope we did not miss any. Re-check? 050531
      muon->EvaluateFinders();
      CheckForwardTrackMuon(muon);
    }

    // c
    // c   reevaluate muon quality 
    // c     
    //      if (muqual(jj).ge.4) then
    if(muon->GetQuality()>=4 ){
      // c
      // c       same categories as above, make sure to change both simultaneously!
      // c
      //        if (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
      if(muon->GetBrematID()>0 && muon->GetProbability()>0.01 
	 //     +      .and.muchfl(jj).eq.3.and.mutrfl(jj).eq.2) then
	 && muon->GetChamberFlag()==3 && muon->GetTrackFlag()==2){
	//* (1)  BREMAT 5 dof,  very frequent;
	//          muquac = 6.1;
	local_quality = 6.1;

	//        elseif ((MUMPMAT(jj).gt.0.or.MUMUFO(jj).gt.0).and.
      }
      else if((muon->GetMPMatchID()>0 || muon->GetMufoID()>0 )
	      //     +          mupmat(jj).gt.0.05.and.mutrfl(jj).gt.0) then 
	      && muon->GetProbability()>0.05 && muon->GetTrackFlag()>0){
	//* (2)  standard MPMATCH, frequent;
	//          muquac = 6.6
	local_quality = 6.6;

      }
      else if((muon->GetMPMatchID()>0 || muon->GetMufoID()>0)
	      && muon->GetCalProbMV()>0.6 && muon->GetTrackFlag()>0 ) {
	//         elseif ((MUMPMAT(jj).gt.0.or.MUMUFO(jj).gt.0).and.
	//      +          mupmip(jj).gt.0.6.and.mutrfl(jj).gt.0) then
	// * (2a)  MPMATCH with low prob but MV, very rare
	// * ... muqual 5 part not yet understood
	//          muquac = 6.8
	local_quality = 6.8;

	// c        elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
	// c     +     .and.muchfl(jj).eq.1.and.mutrfl(jj).eq.2
	// c     +     .and.mupmip(jj).gt.0.and.muqual(jj).eq.6) then
	// c* BREMAT 4dof + low quality MV + no muth cut, very rare
	// c* not understood
	// c* not clear what to do with this
	// c          if (muquac.ne.6) printflag = 4

      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()>0.01 
	      && muon->GetTrackFlag()==2 &&  muon->GetCalProbMV()>0.6 
	      && TMath::Abs(muon->Eta())>0.6)  {
	//         elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
	//      +     .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	//      +     .and.abs(log(tan(muth(jj)/2.))).gt.0.6) then
	// * (3) BREMAT 4dof + MV, large angle, frequent
	// * quality should be 5 
	// * due to a bug in fill_gmuon raising the quality twice for MV
	// * it is sometimes 6, and often stays 4
	//         muquac = 5.2
	local_quality = 5.2;

      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()<0.01 
	      &&  muon->GetChamberFlag()==3 && muon->GetTrackFlag()==2 
	      && muon->GetCalProbMV()>0.6  ) {
	//         elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).lt.0.01
	//      +     .and.muchfl(jj).eq.3.and.mutrfl(jj).eq.2
	//      +     .and.mupmip(jj).gt.0.6) then
	// * (1a) low probability BREMAT 5dof + MV, rare  
	// * quality should be 5  ("feature" of 4-dof/5-dof separation)
	// * due to a bug in fill_gmuon raising the quality twice for MV
	// * it is sometimes 6, and often stays 4
	//          muquac = 5.1
	local_quality = 5.1;

	// c        elseif (MUBREMAT(jj).gt.0
	// c     +     .and.mutrfl(jj).eq.2.and.MUMV(jj).gt.0
	// c     +     .and.abs(log(tan(muth(jj)/2.))).gt.0.6
	// c     +     .and.muqual(jj).eq.6) then
	// c* BREMAT 4dof (sometimes low quality) + low quality MV, large angle, very rare
	// c* ... not understood,  further bug?
	// c* due to a bug in fill_gmuon raising the quality twice for MV
	// c* it is sometimes 6, and often stays 4
	// c* not clear what to do with this
	// c         if (muquac.ne.6) printflag = 4c

      }
      else if(muon->GetMuBacID()>0 
	      &&  muon->GetTrackFlag()==2 && muon->GetCalProbMV()>0.6 
	      &&  TMath::Abs(muon->Eta())>0.6) {
	//         elseif (MUMUBAC(jj).gt.0
	//      +     .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	//      +     .and.abs(log(tan(muth(jj)/2.))).gt.0.6) then
	// * (4) MUBAC + MV,   large angle,  very frequent
	// * ... muqual 4 part (rare) not understood
	//           muquac = 5.4
	local_quality = 5.4;

      }
      else if(muon->GetMuBacID()>0 
	      && muon->GetBrematID()>0 &&  muon->GetProbability()>0.01 
	      && muon->GetTrackFlag()==2 && muon->GetCalProbMV()>0.6 
	      //WARNING!!! .le. would be "correct" here. 050331
	      &&   TMath::Abs(muon->Eta())<0.6) {
	//         elseif (MUMUBAC(jj).gt.0
	//      +    .and.MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
	//      +    .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	//      +    .and.abs(log(tan(muth(jj)/2.))).lt.0.6) then
	// * (5) BREMAT + MUBAC + MV,  low angle,  frequent
	//           muquac = 5.5
	local_quality = 5.5;

      }
      else if(muon->GetMuBacID()>0 
	      && muon->GetBrematID()>0 
	      && muon->GetTrackFlag()>0 && muon->GetCalProbMV()>0.6 ) {
	//         elseif (MUMUBAC(jj).gt.0
	//      +    .and.MUBREMAT(jj).gt.0
	//      +    .and.mutrfl(jj).gt.0.and.mupmip(jj).gt.0.6) then
	// * (5a) BREMAT + MUBAC + MV, not vtx ass. or bad match, frequent
	// * modify -> 4?
	//           muquac = 4.5
	local_quality = 4.5;

      }
      else if(muon->GetMuBacID()>0 
	      &&  muon->GetTrackFlag()!=2 && muon->GetCalProbMV()>0.6 
	      && TMath::Abs(muon->Eta())>0.6 ) {
	//         elseif (MUMUBAC(jj).gt.0
	//      +    .and.mutrfl(jj).ne.2.and.mupmip(jj).gt.0.6
	//      +    .and.abs(log(tan(muth(jj)/2.))).gt.0.6) then
	// * (4a) MUBAC + MV large angle, no vertex association required!
	// * rare! not very clean. normal.  if forward -> 4 
	//           muquac = 4.5
	// WARNING!! 4.5 twice??
	local_quality = 4.5;
        
      }
      else if( (muon->GetMPMatchID()>0 || muon->GetMufoID()>0) 
	       && muon->GetProbability()<0.05 && muon->GetTrackFlag()>0 ) {
	//         elseif ((MUMPMAT(jj).gt.0.or.MUMUFO(jj).gt.0).and.
	//      +          mupmat(jj).lt.0.05.and.mutrfl(jj).gt.0) then
	// * (2b) MPMATCH or MUFO with track, low prob,  rare
	// * quality often reduced later
	// c          muquac = 5.6         
	//           muquac = 4.6         
	local_quality = 4.6;

      }
      else if(muon->GetMufoID()>0 && muon->GetTrackFlag()==0 
	      && muon->GetQuality()==5 ){
	//         elseif (MUMUFO(jj).gt.0.and.mutrfl(jj).eq.0
	//      +      .and.muqual(jj).eq.5) then
	// * (9) MUFO without track with good vtx, frequent
	// * quality often reduced later
	// c          muquac = 5.7         
	//           muquac = 4.7         
	local_quality = 4.7;

      }
      else if(muon->GetMammaID()>0 && muon->GetTrackFlag()>0 
	      && muon->GetQuality()==5 ){
	//         elseif (MUMAMMA(jj).gt.0.and.mutrfl(jj).gt.0
	//      +      .and.muqual(jj).eq.5) then
	// * (10) MAMMA with track, rare
	// * quality often reduced later
	// * do not use MAMMA to reduce systematics
	// c          muquac = 5.9 
	//           muquac = 3. 
	local_quality = 3.;

      }
      else if(muon->GetMuBacID()>0 && muon->GetMPMatchID()<0 
	      &&  muon->GetQuality()==5 ) {
	//         elseif (MUMUBAC(jj).gt.0.and.MUMPMAT(jj).lt.0
	//      +      .and.muqual(jj).eq.5) then
	// * MUBAC + MFRTZ, very rare
	// * ... not understood  
	// * do not use MFRTZ to reduce systematics              
	// * downgrade to BAC only        
	// c          muquac = 5.8
	//           muquac = 4.4        
	local_quality = 4.4;

	//C*********************************************************

      }
      else if(muon->GetBrematID()>0 && muon->GetProbability()>0.01 
	      && muon->GetTrackFlag()==2){
	//         elseif (MUBREMAT(jj).gt.0.and.mupmat(jj).gt.0.01
	//      +     .and.mutrfl(jj).eq.2) then
	// * (6) good BREMAT 4dof, very frequent
	//           muquac = 4.2         
	local_quality = 4.2;

      }
      else if(muon->GetMuBacID()>0 
	      && muon->GetTrackFlag()==2 && muon->GetBacFlag()<50){
	//         elseif (MUMUBAC(jj).gt.0
	//      +     .and.mutrfl(jj).eq.2.and.mubacfl(jj).lt.50) then 
	// * (7) good BAC, very frequent 
	//           muquac = 4.4
	local_quality = 4.4;
         
      }
      else if(muon->GetMuBacID()>0 
	      &&  muon->GetTrackFlag()==2 && muon->GetCalProbMV()>0.6 
	      && TMath::Abs(muon->Eta())<0.6){
	//         elseif (MUMUBAC(jj).gt.0
	//      +     .and.mutrfl(jj).eq.2.and.mupmip(jj).gt.0.6
	//      +     .and.abs(log(tan(muth(jj)/2.))).lt.0.6) then
	// * (8) reasonable central BAC + MV, frequent
	//           muquac = 4.5
	local_quality = 4.5;

      }
      else if(muon->GetMuBacID()>0 
	      &&  muon->GetTrackFlag()!=2 && muon->GetCalProbMV()>0. ){
	//         elseif (MUMUBAC(jj).gt.0
	//      +      .and.mutrfl(jj).ne.2.and.mupmip(jj).gt.0.) then
	// * (4b) MUBAC + MV, not vertex associated, very rare
	//           muquac = 4.5
	local_quality = 4.5;

      }
      else if(muon->GetMuBacID()>0 && muon->GetMipID()>0){
	//         elseif (MUMUBAC(jj).gt.0.and.MUMIP(jj).gt.0) then
	// * (4c) any BAC + MIP 
	//           muquac = 4.5
	local_quality = 4.5;
                  
      }
      else if(muon->GetMufoID()>0 && muon->GetTrackFlag()==0 
	      &&  muon->GetQuality()==4 ){
	//         elseif (MUMUFO(jj).gt.0.and.mutrfl(jj).eq.0
	//      +    .and.muqual(jj).eq.4) then
	// * (9a) MUFO w/o track, very rare (bug! should be more frequent)
	//           muquac = 4.7
	local_quality = 4.7;

      }
      else if(muon->GetMPMatchID()<0 && muon->GetTrackFlag()==0 
	      && muon->GetCalProbMV()>0.6 && muon->GetQuality()==4 ){
	//         elseif (MUMPMAT(jj).lt.0.and.mutrfl(jj).eq.0
	//      +    .and.mupmip(jj).gt.0.6.and.muqual(jj).eq.4) then
	// * (11) MFRTZ w/o track + MV, very rare (bug! should be more frequent)
	// * do not use MFRTZ to reduce systematics 
	// c          muquac = 4.8
	//           muquac = 3.
	local_quality = 3.;

      }
      else if(muon->GetMammaID()>0 && muon->GetTrackFlag()==0 
	      && muon->GetQuality()==4 ){
	//         elseif (MUMAMMA(jj).gt.0.and.mutrfl(jj).eq.0
	//      +    .and.muqual(jj).eq.4) then
	// * (10a) MAMMA, rare  (bug?)
	// * do not use MAMMA to reduce systematics 
	// c          muquac = 4.9
	//           muquac = 3.
	local_quality = 3.;
        
      }
      else {
	//       else
	//          muquac = -1.
	local_quality = -1.;
	// c          print *,'*** this should not happen for data'
	// c          print *, runnr, eventnr, jj          

	//        endif
      }
      //    elseif (muqual(jj).ge.2) then
    }
    else if(muon->GetQuality()>=2){
      // c
      // c try to recover MUFO candidates lost due to bug
      // c
      if(muon->GetMufoID()>0 && muon->GetTrackFlag()==0 
	 &&  muon->GetMvID()>0 ){
	//         if (MUMUFO(jj).gt.0.and.mutrfl(jj).eq.0
	//      +    .and.mumv(jj).gt.0) then
	// * (9a) MUFO w/o track
	//           muquac = 4.8
	local_quality = 4.8;
	//        endif
      }
    
      //      endif
    }

    // c   def_trk_type=2 (regular) or 3 (ztt) indicates HERA II data/new ntuples. 
    // C   change this later!
    //      if (def_trk_type.ge.2) then
    if( gCards -> GetHERA2() ) {

      if( gData->Getdef_trk_type() >= 2 ){
    // c   remove muons with no energy in HAC, except if Ok'd by MV, or seen 
    // c   in outer chambers (quality 6)
    //        if (muhac2_t(jj).lt.0.3.and.mupmip(jj).lt.0.05)muquac=muquac-2.
	if( muon->Getmuhac2() < 0.3 && muon->GetCalProbMV() < 0.05 ) local_quality -= 2;
    // c   always require muons to have a track associated (new for HERA II)
    //        if (muztid_t(jj).eq.0) muquac = min(muquac,3) 
	if( muon->Getmuztid() == 0 ) local_quality = min(local_quality,3.);
    // c   always remove forward muons with no energy in HAC
    //        if (muhac2_t(jj).lt.0.3.and.muth(jj).lt.0.5) muquac=0.
	if( muon->Getmuhac2() < 0.3 && muon->Theta() < 0.5 ){
	  muon->SetQuality(0);
	}
      }
    }
    if( local_quality == 4.1) local_quality = 4.2; // this happens due to the Muhac2 Corrections (Quality 6.1 -> 4.1)
    local_quality_save = local_quality;
    // New quality has been determined - we use it:
    //    muon->SetQuality(local_quality); // improved 050530done
    muon->SetSpecialQuality(local_quality);
    muon->SetQuality((Int_t)local_quality);

// 	cout<<"*** muqual "<<muon->GetQuality()<<" classified "<<printflag<<" local_quality: "<<local_quality<<endl;
// 	cout<<"*** run/evt "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<muon->GetID()<<endl;
// 	cout<<"  BREMAT,    MPMAT,    MUFO,    MUBAC,    MV,   MUGLOMU,  MUCHFL, MUPMAT,   MUTRFL, CalProbMV"<<endl;
// 	cout<<"  "<<muon->GetBrematID()<<"          "<<muon->GetMPMatchID()<<"         "<<muon->GetMufoID()<<"        "<<muon->GetMuBacID()
// 	    <<"         "<<muon->GetMvID()<<"     "<<muon->GetGlomuID()<<"         "<<muon->GetChamberFlag()
// 	    <<"       "<<muon->GetProbability()<<"  "<<muon->GetTrackFlag()<<"            "<<muon->GetCalProbMV()<<endl;
// 	cout<<"eta: "<<muon->Eta()<<endl;
  
    // C
    // C  muon quality modification, data and MC
    // C
    //          muquac_save = muquac
    
    //          if (muchfl(jj).ge.4) then
    //c        muon seen in forward chambers
    //            if (mumpmat(jj).ne.0.or.mumufo(jj).gt.0) then 
    //              if (muchid(jj).gt.0) then
    // c        ndf = 2*N_planes-5  (5: ndof of helix fit)
    //                 ndf = mfndf(muchid(jj))
    //                 if (ndf.gt.3) then
    // c        >4 planes, do nothing
    //                 elseif (ndf.eq.3) then
    // c         4 planes, reduce quality by 2
    //                   muquac = muquac-2.
    //                 elseif (ndf.eq.1) then
    // c         3 planes, reduce quality by 3
    //                   muquac = muquac-3.
    //                 endif            
    //                 muz = mfz(muchid(jj))
    //                 if (muz.ge.500) then
    // c         muon does not start at FMUI plane, reduce quality by 1 
    //                   muquac = muquac-1.
    //                 endif
    //                 if (mumubac(jj).gt.0) then
    // c         muon has BAC match, increase quality by 1
    //                   muquac = muquac+1.
    //                 endif
    //                 if (mumv(jj).gt.0) then
    // c         muon has MV match, increase quality by 2
    //                   muquac = muquac+2.
    //                 endif
    //                 if (muquac.gt.muquac_save) then          
    // c         quality can never be better than initial quality
    //                   muquac = muquac_save
    //                 endif 
    //               else
    //                 print *, '*** error: Fmuon with no id ***' 
    //               endif

    //             elseif (mumamma(jj).gt.0) then
    // c         muon seen by mamma
    // c         if muon was seen in outer chambers, it was already
    // c         treated above, treat inner chambers
    //               if (mumubac(jj).eq.0) then
    // c         not seen by BAC, reduce quality by 2
    //                 muquac = muquac - 2.
    //               endif                   
    //             else
    //               print *, '*** error: forward muon with no finder ***'
    //             endif

    //           elseif (muchfl(jj).eq.0.and.mumubac(jj).gt.0.and.
    //      +            muth(jj).lt.0.585) then 
    // c       generally reduce quality for forward BAC only muons
    //             muquac = muquac - 1.
    // c          elseif (muchfl(jj).eq.1) then
    // cc       undo bug for BREMAT 4dof + MV: 6 should be 5
    // c            if (muqual_t(jj).eq.6) muqual_t(jj)=5
    // c          elseif (muchfl(jj).eq.3.and.probmat_t(jj).lt..01) then
    // cc       undo bug for bad matching BREMAT 5dof +4dof OK + MV: 6 should be 5
    // c            if (muqual_t(jj).eq.6) muqual_t(jj)=5

    //           endif

    // c   the following can be used instead of muhac2, but strongly reduces 
    // c   acceptance (only >= 3sl CTD or MVD only tracks are matched so far) 
    // c        if (muth(jj).lt.0.5.and.mustid(jj).eq.0) muquac = muquac - 1.
    // c   instead, after MUHAC2 cut, increase quality if STT match found
    // c   does not work (bg)
    // c       if (mustid(jj).gt.0) muquac = muquac + 1.
    //      endif

    //      if (muquac.gt.muquac_save) then          
    // c  quality can never be better than initial quality
    //        muquac = muquac_save
    //      endif 

    //      return
    //      end
    //**********************************************************************************************************;
    //******************* Achim's muquana END ******************************************************************;
    //**********************************************************************************************************;
  }
  if ( gCards->GetMUONModifyQuality() ) {    
    //We need a reevaluation of ForwardTrackMuon here!!! repair it! 050530
    if( muon->GetForwardTrackMuon() ) {                 // require forward muon chambers 
      // correct for forward track muon found by MUFO or MPMATCH
      // if forward track muon only found by MAMMA, do nothing
      // distinguish dcache running pre-upgrade and normal running incl. dcache running post-upgrade (different variable names)
      Bool_t dcache = kFALSE;
      if ( !gCards->GetMC() ) {
	if ( !(gGeneral->GetRunPeriod() == k03p) && !(gGeneral->GetRunPeriod() == k04p) ) {
	  if ( gCards->GetdCache() ) {
	    dcache = kTRUE;
	  }
	}
      }
    
      if ( dcache ) {
	if ( muon->GetMPMatch() || muon->GetMufo() ) {
	  // check if forward muon ID is smaller than 10, because only 10 forward muons are stored in special forward muon blocks
	  if ( muon->GetID() <= 10 ) {
	    Int_t local_quality = muon->GetQuality();
	    // ndf equals 2*N_planes-5 (5: fit-degrees-of-freedom)
	    Int_t ndf =  gData->Getmundof(muon->GetID()-1);
	    if ( ndf > 4 ) {
	      local_quality = local_quality;                 // muon has more than 4 dof      - nothing done
	    } else if ( ndf == 3 ) {
	      local_quality -= 2;                            // muon has 3 dof                - -2
	    } else if( ndf == 1 ) {
	      local_quality -= 3;                            // muon has 1 dof                - -3
	    }
	    Double_t mfz = gData->Getmuz(muon->GetID()-1);

	    if( mfz >= 500 )          local_quality -= 1;             // muon starts not at 1st plane  - -1
	    if ( muon->GetMuBac() )   local_quality += 1;             // muon has bac match            - +1
	    if ( muon->GetMv() )      local_quality += 2;             // muon has mv match             - +2
			
	    if ( muon->GetQuality() > local_quality) muon->SetQuality(local_quality);
	  }
	} else if ( muon->GetMamma() ) {
	  // set to zero
	  if ( gCards->GetMUONExcludeMamma() ) {
	    muon->SetQuality(0);
	  }
	}
      } else {
	if ( muon->GetMPMatch() || muon->GetMufo() ) {
	  // safety check for pointer
	  if( gCards->GetHERA1() ){
	    if ( gData->Getnmf() > 0 ) {                     
	    // check if forward muon ID is smaller than 10, because only 10 forward muons are stored in special forward muon blocks
	      if ( muon->GetFmufiCID() < 10 ) {
	    //if ( muon->GetID() <= 10 ) {
		Int_t local_quality = muon->GetQuality();
            // ndf equals 2*N_planes-5 (5: fit-degrees-of-freedom)
	    // if(muon->GetFmufiCID()>9) cout<<(char)27<<"[01;31m"<<"I warned you!! you need to protect this!! Hallo!! Wake up!!! RIIINNGG!!! -> look at GMuons.cxx, modify muqual"<<endl;
		Int_t ndf =  gData->Getmfndf(muon->GetFmufiCID());
		//		Int_t ndf = gData->Getmundof(muon->GetID()-1);
	      
		if ( ndf > 4 ) {
		  local_quality = local_quality;                 // muon has more than 4 dof      - nothing done
		} else if ( ndf == 3 ) {
		  local_quality -= 2;                            // muon has 3 dof                - -2
		} else if( ndf == 1 ) { 
		  local_quality -= 3;                            // muon has 1 dof                - -3
		}

		Double_t mfz = gData->Getmfz(muon->GetFmufiCID());

	      //Double_t mfz = gData->Getmuz(muon->GetID()-1);
	      
		if( mfz >= 500 )        local_quality -= 1;             // muon starts not at 1st plane  - -1
		if ( muon->GetMuBac() ) local_quality += 1;             // muon has bac match            - +1 
		if ( muon->GetMv() )    local_quality += 2;             // muon has mv match             - +2
		
		if ( muon->GetQuality() > local_quality) muon->SetQuality(local_quality);
	      }
	    }
	  }
	  else if( gCards->GetHERA2() ){
           // check if forward muon ID is smaller than 10, because only 10 forward muons are stored in special forward muon blocks
	    if ( muon->GetID() <= 10 ) {
	      Int_t local_quality = muon->GetQuality();
	      Int_t ndf           = gData->Getmundof(muon->GetID()-1);
	      
	      if ( ndf > 4 ) {
		local_quality = local_quality;                 // muon has more than 4 dof      - nothing done
	      } else if ( ndf == 3 ) {
		local_quality -= 2;                            // muon has 3 dof                - -2
	      } else if( ndf == 1 ) { 
		local_quality -= 3;                            // muon has 1 dof                - -3 -> change to 4
	      }

	      Double_t mfz = gData->Getmuz(muon->GetID()-1);
	      if( mfz >= 500 )        local_quality -= 1;             // muon starts not at 1st plane  - -1
	      if( muon->GetMuBac() )  local_quality += 1;             // muon has bac match            - +1 
	      if( muon->GetMv() )     local_quality += 2;             // muon has mv match             - +2 
		
	      if ( muon->GetQuality() > local_quality) muon->SetQuality(local_quality);
	    }
	  }
	} else if ( muon->GetMamma() ) {
	  // if muon was seen in outer muon chambers, muon has already been treated above. Do not accept inner muon chamber only:
	  // check mamma muon, for BAC match - if missing: reduce by 2.
	  if ( !muon->GetMuBac() && 42 != 42 )  muon->SetQuality(muon->GetQuality()-2); // quality -= 2;
	  // set to zero if exclude card is set.
	  if ( gCards->GetMUONExcludeMamma() ) {
	    muon->SetQuality(0);
	  }
	}
      }
    } else if ( (muon->GetChamberFlag() == 0) && muon->GetMuBac() && (muon->Theta() < 0.585) ) { // 0.585 is eta = 1.2
      muon->SetQuality(muon->GetQuality()-1); // forward BAC muon correction
    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuons::CheckForwardTrackMuon(GMuon *muon) {
  //
  // check if muon is forward muon and set fmufiCID 
  if ( gDebug ) cout << endl << "GMuons::CheckForwardTrackMuon() called" << endl << endl;

  // identify forward track muons
  if ( muon->GetChamberFlag() > gCards->GetMUONChamberFlagCut() )
    muon->SetForwardTrackMuon(kTRUE);
  else 
    muon->SetForwardTrackMuon(kFALSE);

  // get fmufi entry if muon is a forward track muon
  if ( muon->GetForwardTrackMuon() ) {
    if ( muon->GetChamberID() > 0 ) {
      muon->SetFmufiCID(muon->GetChamberID()-1);
    }
  }
  
  return kTRUE;
}

//____________________________________________________________

Bool_t GMuons::FillSpecialFinderHisto(TH1D *histo, GMuon *muon) {
  //
  // fill special finder histo 
  // special finder bins
    // 0: barrel bremat plus (mubac and not mv)
    // 1: barrel bremat plus (mubac and mv)
    // 2: barrel bremat plus not mubac
    // 3: barrel not bremat plus (mubac and not mv)
    // 4: barrel not bremat plus (mubac and mv)
    // 5: rear bremat plus (mubac and not mv)
    // 6: rear bremat plus (mubac and mv)
    // 7: rear bremat plus not mubac
    // 8: rear not bremat plus  (mubac and not mv)
    // 9: rear not bremat plus (mubac and mv)
    // 10: forward mpmatch or mufo plus (mubac and not mv)
    // 11: forward mpmatch or mufo plus (mubac and mv)
    // 12: forward mpmatch or mufo plus not mubac
    // 13: forward not mpmatch or mufo plus (mubac and not mv)
    // 14: forward not mpmatch or mufo plus (mubac and mv)
    // 15: forward bacmat
    // 16: barrel bacmat
    // 17: rear bacmat
  if ( gDebug ) cout << endl << "GMuons::FillSpecialFinderHisto() called" << endl << endl;

  if ( muon->GetType() == kBarrel ) {
    if ( muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      histo->Fill(0.5,gHeader->GetWeight(muon));
      } else if ( muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      histo->Fill(1.5,gHeader->GetWeight(muon));
    } else if ( muon->GetBremat() && !muon->GetMuBac() ) {
      histo->Fill(2.5,gHeader->GetWeight(muon));
    } else if ( !muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      histo->Fill(3.5,gHeader->GetWeight(muon));
    } else if ( !muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      histo->Fill(4.5,gHeader->GetWeight(muon));
    } else if ( muon->GetBacMat() ) {
      histo->Fill(16.5,gHeader->GetWeight(muon));
    }
  } else if ( muon->GetType() == kRear ) {
    if ( muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      histo->Fill(5.5,gHeader->GetWeight(muon));
    } else if ( muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      histo->Fill(6.5,gHeader->GetWeight(muon));
    } else if ( muon->GetBremat() && !muon->GetMuBac() ) {
      histo->Fill(7.5,gHeader->GetWeight(muon));
    } else if ( !muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      histo->Fill(8.5,gHeader->GetWeight(muon));
    } else if ( !muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      histo->Fill(9.5,gHeader->GetWeight(muon));
    } else if ( muon->GetBacMat() ) {
      histo->Fill(17.5,gHeader->GetWeight(muon));
    }
  } else if ( (muon->GetType() == kForward) ) {
    if ( (muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && !muon->GetMv() ) {
      histo->Fill(10.5,gHeader->GetWeight(muon));
    } else if ( (muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && muon->GetMv() ) {
      histo->Fill(11.5,gHeader->GetWeight(muon));
    } else if ( (muon->GetMPMatch() || muon->GetMufo()) && !muon->GetMuBac() ) {
      histo->Fill(12.5,gHeader->GetWeight(muon));
    } else if ( !(muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && !muon->GetMv() ) {
      histo->Fill(13.5,gHeader->GetWeight(muon));
    } else if ( !(muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && muon->GetMv() ) {
      histo->Fill(14.5,gHeader->GetWeight(muon));
    } else if ( muon->GetBacMat() ) {
      histo->Fill(15.5,gHeader->GetWeight(muon));
    }
  } 


//   if ( muon->GetBremat() ) {
//     histo->Fill(0.5,gHeader->GetWeight(muon));
//   } else if ( muon->GetMPMatch() || muon->GetMufo() ) {
//     histo->Fill(1.5,gHeader->GetWeight(muon));
//   } else if ( muon->GetMuBac() ) {
//     histo->Fill(2.5,gHeader->GetWeight(muon));
//   }

//   if ( muon->GetMuBac() && !muon->GetBremat() && !muon->GetMPMatch() )
//     histo->Fill(0.5,gHeader->GetWeight(muon));
//   if ( !muon->GetMuBac() && muon->GetBremat() )
//     histo->Fill(1.5,gHeader->GetWeight(muon));
//   if ( !muon->GetMuBac() && muon->GetMPMatch() )
//     histo->Fill(2.5,gHeader->GetWeight(muon));
//   if ( muon->GetMuBac() && muon->GetBremat() )
//     histo->Fill(3.5,gHeader->GetWeight(muon));
//   if ( muon->GetMuBac() && muon->GetMPMatch() )
//     histo->Fill(4.5,gHeader->GetWeight(muon));

  return kTRUE;
}
//_____________________________________________________________

Int_t GMuons::GetSpecialFinderBin(GMuon *muon) {
  //
  // fill special finder histo 
  // special finder bins
    // 0: barrel bremat plus (mubac and not mv)
    // 1: barrel bremat plus (mubac and mv)
    // 2: barrel bremat plus not mubac
    // 3: barrel not bremat plus (mubac and not mv)
    // 4: barrel not bremat plus (mubac and mv)
    // 5: rear bremat plus (mubac and not mv)
    // 6: rear bremat plus (mubac and mv)
    // 7: rear bremat plus not mubac
    // 8: rear not bremat plus  (mubac and not mv)
    // 9: rear not bremat plus (mubac and mv)
    // 10: forward mpmatch or mufo plus (mubac and not mv)
    // 11: forward mpmatch or mufo plus (mubac and mv)
    // 12: forward mpmatch or mufo plus not mubac
    // 13: forward not mpmatch or mufo plus (mubac and not mv)
    // 14: forward not mpmatch or mufo plus (mubac and mv)
    // 15: forward bacmat
    // 16: barrel bacmat
    // 17: rear bacmat
  if ( gDebug ) cout << endl << "GMuons::FillSpecialFinderHisto() called" << endl << endl;
  Int_t bin = -100;
  if ( muon->GetType() == kBarrel ) {
    if ( muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      bin = 0;
    } else if ( muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      bin = 1;
    } else if ( muon->GetBremat() && !muon->GetMuBac() ) {
      bin = 2;
    } else if ( !muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      bin = 3;
    } else if ( !muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      bin = 4;
    } else if ( muon->GetBacMat() ) { 
      bin = 16;
    }
  } else if ( muon->GetType() == kRear ) {
    if ( muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      bin = 5;
    } else if ( muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      bin = 6;
    } else if ( muon->GetBremat() && !muon->GetMuBac() ) {
      bin = 7;
    } else if ( !muon->GetBremat() && muon->GetMuBac() && !muon->GetMv() ) {
      bin = 8;
    } else if ( !muon->GetBremat() && muon->GetMuBac() && muon->GetMv() ) {
      bin = 9;
    } else if ( muon->GetBacMat() ) { 
      bin = 15;
    }
  } else if ( (muon->GetType() == kForward) ) {
    if ( (muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && !muon->GetMv() ) {
      bin = 10;
    } else if ( (muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && muon->GetMv() ) {
      bin = 11;
    } else if ( (muon->GetMPMatch() || muon->GetMufo()) && !muon->GetMuBac() ) {
      bin = 12;
    } else if ( !(muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && !muon->GetMv() ) {
      bin = 13;
    } else if ( !(muon->GetMPMatch() || muon->GetMufo()) && muon->GetMuBac() && muon->GetMv() ) {
      bin = 14;
    } else if ( muon->GetBacMat() ) { 
      bin = 17;
    }

  } 

  return bin;
}
//___________________________________________________________________
Bool_t GMuons::ProduceMirroredPlot(){
  if (gDebug) cout << endl << "GMuons::ProduceMirroredPlot() called" << endl << endl;
  Int_t nbins= fGeneral2DBeamSpotImpactParameter->GetNbinsX();
  nbins =nbins/2;
  for (Int_t i=1;i<= nbins;i++){
    Double_t bincont_a = fGeneral2DBeamSpotImpactParameter->GetBinContent(i);
    Double_t bincont_b = fGeneral2DBeamSpotImpactParameter->GetBinContent(2*nbins-i+1);
    Double_t bincenter = fGeneral2DBeamSpotImpactParameter->GetBinCenter(2*nbins-i+1);
    Double_t bincont_b_a = bincont_b - bincont_a;
    Double_t binerror =sqrt(bincont_b + bincont_a);
    fGeneral2DBeamSpotImpactParameter_Mirrored->Fill(bincenter,bincont_b_a);
    Int_t   bin = 2*nbins-i+1;
    fGeneral2DBeamSpotImpactParameter_Mirrored->SetBinError(bin,binerror);
  }

  return kTRUE;
}
//____________________________________________________________________
Bool_t GMuons::Finalize() {
  //
  // finalize operations of physics object, mainly for histograms
  if (gDebug) cout << endl << "GMuons::Finalize() called" << endl << endl;

  ProduceMirroredPlot();

  if ( gCards->GetProduceFakeMuon() ) {
    double scaleAllPt = 1./gTracks->GetTrackPt()->GetEntries();
    double scaleAllEta_lowPt = 1./gTracks->GetTrackEta_lowPt()->GetEntries();
    double scaleAllPhi_lowPt = 1./gTracks->GetTrackPhi_lowPt()->GetEntries();
    double scaleAllEta_highPt = 1./gTracks->GetTrackEta_highPt()->GetEntries();
    double scaleAllPhi_highPt = 1./gTracks->GetTrackPhi_highPt()->GetEntries();
    double scaleAll2DPtEta = 1./gTracks->GetTrack2DAll_PtEta()->GetEntries();


    fMuonProbabilityAllEta_lowPt->Divide(fEta_lowPt_fakebin,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonProbabilityAllPhi_lowPt->Divide(fPhi_lowPt_fakebin,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonProbabilityAllEta_highPt->Divide(fEta_highPt_fakebin,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonProbabilityAllPhi_highPt->Divide(fPhi_highPt_fakebin,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonProbabilityAllPt->Divide(fPt_fakebin,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);
    fProbability2DMuonAll_PtEta->Divide(fFake2DMuonAll_PtEta,gTracks->GetTrack2DAll_PtEta(),scaleAll2DPtEta,scaleAll2DPtEta);
    fProbability2DMuonDecay_PtEta->Divide(fFake2DMuonDecay_PtEta,gTracks->GetTrack2DAll_PtEta(),scaleAll2DPtEta,scaleAll2DPtEta);
    fProbability2DMuonPunch_PtEta->Divide(fFake2DMuonPunch_PtEta,gTracks->GetTrack2DAll_PtEta(),scaleAll2DPtEta,scaleAll2DPtEta);
    fFake2DProbMuonAll_PtEta_Bremat->Divide(fFake2DMuonAll_PtEta_Bremat,gTracks->GetTrack2DAll_PtEta(),scaleAll2DPtEta,scaleAll2DPtEta);
    fFake2DProbMuonAll_PtEta_MPMatch->Divide(fFake2DMuonAll_PtEta_MPMatch,gTracks->GetTrack2DAll_PtEta(),scaleAll2DPtEta,scaleAll2DPtEta);
    fFake2DProbMuonAll_PtEta_Bac->Divide(fFake2DMuonAll_PtEta_Bac,gTracks->GetTrack2DAll_PtEta(),scaleAll2DPtEta,scaleAll2DPtEta);

      //--------------------------------------------------------------
    fFakePionProbabilityAllEta_lowPt->Divide(fFakeMuonPionEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fFakePionProbabilityAllPhi_lowPt->Divide(fFakeMuonPionPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);
    fFakePionProbabilityAllEta_highPt->Divide(fFakeMuonPionEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);
    fFakePionProbabilityAllPhi_highPt->Divide(fFakeMuonPionPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fFakePionProbabilityAllPt->Divide(fFakeMuonPionPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);
    //--------------------------------------------------------------
    fFakeKaonProbabilityAllEta_lowPt->Divide(fFakeMuonKaonEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fFakeKaonProbabilityAllPhi_lowPt->Divide(fFakeMuonKaonPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fFakeKaonProbabilityAllEta_highPt->Divide(fFakeMuonKaonEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fFakeKaonProbabilityAllPhi_highPt->Divide(fFakeMuonKaonPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fFakeKaonProbabilityAllPt->Divide(fFakeMuonKaonPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);
   //--------------------------------------------------------------
    fMuonDecayPionProbabilityAllEta_lowPt->Divide(fFakeDecayMuonPionEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonDecayProbabilityAllPhi_lowPt->Divide(fFakeDecayMuonPionPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonDecayPionProbabilityAllEta_highPt->Divide(fFakeDecayMuonPionEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonDecayPionProbabilityAllPhi_highPt->Divide(fFakeDecayMuonPionPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonDecayPionProbabilityAllPt->Divide(fFakeDecayMuonPionPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);
    //--------------------------------------------------------------
    fMuonDecayKaonProbabilityAllEta_lowPt->Divide(fFakeDecayMuonKaonEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonDecayKaonProbabilityAllPhi_lowPt->Divide(fFakeDecayMuonKaonPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonDecayKaonProbabilityAllEta_highPt->Divide(fFakeDecayMuonKaonEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonDecayKaonProbabilityAllPhi_highPt->Divide(fFakeDecayMuonKaonPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonDecayKaonProbabilityAllPt->Divide(fFakeDecayMuonKaonPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);

    //--------------------------------------------------------------

    fMuonPunchPionProbabilityAllEta_lowPt->Divide(fFakeMuonPionEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonPunchPionProbabilityAllPhi_lowPt->Divide(fFakeMuonPionPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonPunchPionProbabilityAllEta_highPt->Divide(fFakeMuonPionEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonPunchPionProbabilityAllPhi_highPt->Divide(fFakeMuonPionPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonPunchPionProbabilityAllPt->Divide(fFakeMuonPionPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);

    //--------------------------------------------------------------

    fMuonPunchKaonProbabilityAllEta_lowPt->Divide(fFakePunchMuonKaonEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonPunchKaonProbabilityAllPhi_lowPt->Divide(fFakePunchMuonKaonPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonPunchKaonProbabilityAllEta_highPt->Divide(fFakePunchMuonKaonEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonPunchKaonProbabilityAllPhi_highPt->Divide(fFakePunchMuonKaonPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonPunchKaonProbabilityAllPt->Divide(fFakePunchMuonKaonPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);

    //--------------------------------------------------------------

    fMuonPunchProbabilityAllEta_lowPt->Divide(fFakePunchMuonEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonPunchProbabilityAllPhi_lowPt->Divide(fFakePunchMuonPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonPunchProbabilityAllEta_highPt->Divide(fFakePunchMuonEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonPunchProbabilityAllPhi_highPt->Divide(fFakePunchMuonPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonPunchKaonProbabilityAllPt->Divide(fFakePunchMuonPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);

    //--------------------------------------------------------------

    fMuonDecayProbabilityAllEta_lowPt->Divide(fFakeDecayMuonEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fMuonDecayProbabilityAllPhi_lowPt->Divide(fFakeDecayMuonPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);

    fMuonDecayProbabilityAllEta_highPt->Divide(fFakeDecayMuonEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);

    fMuonDecayProbabilityAllPhi_highPt->Divide(fFakeDecayMuonPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fMuonDecayProbabilityAllPt->Divide(fFakeDecayMuonPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);
  
//-------------------------------------------------------------------------------------------------
      fFakeProbabilityAllEta_lowPt->Divide(fFakeMuonAllEta_lowPt,gTracks->GetTrackEta_lowPt(),scaleAllEta_lowPt,scaleAllEta_lowPt);
    fFakeProbabilityAllPhi_lowPt->Divide(fFakeMuonAllPhi_lowPt,gTracks->GetTrackPhi_lowPt(),scaleAllPhi_lowPt,scaleAllPhi_lowPt);
    fFakeProbabilityAllEta_highPt->Divide(fFakeMuonAllEta_highPt,gTracks->GetTrackEta_highPt(),scaleAllEta_highPt,scaleAllEta_highPt);
    fFakeProbabilityAllPhi_highPt->Divide(fFakeMuonAllPhi_highPt,gTracks->GetTrackPhi_highPt(),scaleAllPhi_highPt,scaleAllPhi_highPt);
    fFakeProbabilityAllPt->Divide(gMuons->fFakeMuonAllPt,gTracks->GetTrackPt(),scaleAllPt,scaleAllPt);
}	

  if(!gCards->GetMC()){
    fFake2DMuonAll_PtEta = gTracks->GetTrack2DAll_PtEta_fake();
  }
  
  return kTRUE;
}


//_____________________________________________________________
