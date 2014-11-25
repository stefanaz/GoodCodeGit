//
// GMuons.h
//
// $Author: dbot $
// $Date: 2010/04/12 08:00:43 $
// $Revision: 1.50 $
//

#ifndef GUT_GMuons
#define GUT_GMuons

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#include <algorithm>
#endif
#ifndef ROOT_TRandom
#include <TRandom.h>
#endif

class GMuonEfficiency;

class GMuons : public GPhysObj {

 private:

  GMuonEfficiency *fMuonEfficiency;                                   // muon efficiency object
  TRandom         *randgen;                                           // random number generator object

  Int_t            fBarrelMuons;                                      // counter for barrel muons
  Int_t            fRearMuons;                                        // counter for rear muons
  Int_t            fForwardMuons;                                     // counter for forward muons

  Int_t            fNMuons;                                           // number of muons
  TClonesArray    *fMuons;                                            // array of muons

  Int_t            fMuonsCut;                                         // counter for available muons which passed muon identification
  Bool_t           fMuonsMinIsolation10Veto;                          // flag for minimum isolation for cone 1.0, if one good muon of event has a smaller isolation, veto event
  Bool_t           fGlomus;                                           // set if at least 1 muon with glomuid  
  Double_t         fMuonImp;                                          // Muon 2D impact parameter using Tracking Block
  Double_t         fMuonImperr;                                       // Muon 2D impact parameter error using Tracking Block
  Double_t         fMuonDCA_x;                                        // Muon Distance of closest approach in x using Tracking Block
  Double_t         fMuonDCA_y;                                        // Muon Distance of closest approach in y using Tracking Block
  Double_t         fMuonDCA_z;                                        // Muon Distance of closest approach in z using Tracking Block
  Double_t         fMuonImpSig;                                       // Muon 2D impact parameter significance using Tracking Block
  Double_t         fMuonJetMass;                                      // Mass of Jet containing Muon
  Double_t         fMuonJetEt;                                        // Et of Muon Jet
  Double_t         fMuonMuz;                                          // Muon Z
  Int_t            fMuonMundof;                                       // Muon Ndf

  // general uncut plots
  TH1D             *fGeneralNMU_uncut;                                // uncut number of muons
  TH1D             *fGeneralNMUForward_uncut;                         // uncut number of forward muons
  TH1D             *fGeneralNMUBarrel_uncut;                          // uncut number of barrel muons
  TH1D             *fGeneralNMURear_uncut;                            // uncut number of rear muons
  TH1D             *fGeneralRegions_uncut;                            // uncut muon regions
  TH1D             *fGeneralWeight_uncut;                             // uncut weight of muons
  TH1D             *fGeneralWeightForward_uncut;                      // uncut weight of muons
  TH1D             *fGeneralWeightBarrel_uncut;                       // uncut weight of muons
  TH1D             *fGeneralWeightRear_uncut;                         // uncut weight of muons
  TH1D             *fGeneralWeightMUBAC_uncut;                        // uncut weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightMUBACForward_uncut;                 // uncut weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightMUBACBarrel_uncut;                  // uncut weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightMUBACRear_uncut;                    // uncut weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightBREMAT_uncut;                       // uncut weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightBREMATForward_uncut;                // uncut weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightBREMATBarrel_uncut;                 // uncut weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightBREMATRear_uncut;                   // uncut weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightMPMATCH_uncut;                      // uncut weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightMPMATCHForward_uncut;               // uncut weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightMPMATCHBarrel_uncut;                // uncut weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightMPMATCHRear_uncut;                  // uncut weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightBREMATMUBAC_uncut;                  // uncut weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightBREMATMUBACForward_uncut;           // uncut weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightBREMATMUBACBarrel_uncut;            // uncut weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightBREMATMUBACRear_uncut;              // uncut weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBAC_uncut;                 // uncut weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBACForward_uncut;          // uncut weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBACBarrel_uncut;           // uncut weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBACRear_uncut;             // uncut weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralProb_uncut;                               // uncut muon probability distribution
  TH1D             *fGeneralProbForward_uncut;                        // uncut forward muon probability distribution
  TH1D             *fGeneralProbBarrel_uncut;                         // uncut barrel muon probability distribution
  TH1D             *fGeneralProbRear_uncut;                           // uncut rear muon probability distribution
  TH1D             *fGeneralP_uncut;                                  // uncut muon momentum
  TH1D             *fGeneralPForward_uncut;                           // uncut forward muon momentum
  TH1D             *fGeneralPBarrel_uncut;                            // uncut barrel muon momentum
  TH1D             *fGeneralPRear_uncut;                              // uncut rear muon momentum
  TH1D             *fGeneralPt_uncut;                                 // uncut muon transverse momentum
  TH1D             *fGeneralPtForward_uncut;                          // uncut forward muon transverse momentum
  TH1D             *fGeneralPtBarrel_uncut;                           // uncut barrel muon transverse momentum
  TH1D             *fGeneralPtRear_uncut;                             // uncut rear muon transverse momentum
  TH1D             *fGeneralPtSpecial_uncut;                          // uncut muon transverse momentum with special binning
  TH1D             *fGeneralPtSpecialForward_uncut;                   // uncut forward muon transverse momentum with special binning
  TH1D             *fGeneralPtSpecialBarrel_uncut;                    // uncut barrel muon transverse momentum with special binning
  TH1D             *fGeneralPtSpecialRear_uncut;                      // uncut rear muon transverse momentum with special binning
  TH1D             *fGeneralPx_uncut;                                 // uncut muon x momentum
  TH1D             *fGeneralPxForward_uncut;                          // uncut forward muon x momentum
  TH1D             *fGeneralPxBarrel_uncut;                           // uncut barrel muon x momentum
  TH1D             *fGeneralPxRear_uncut;                             // uncut rear muon x momentum
  TH1D             *fGeneralPy_uncut;                                 // uncut muon y momentum
  TH1D             *fGeneralPyForward_uncut;                          // uncut forward muon y momentum
  TH1D             *fGeneralPyBarrel_uncut;                           // uncut barrel muon y momentum
  TH1D             *fGeneralPyRear_uncut;                             // uncut rear muon y momentum
  TH1D             *fGeneralPz_uncut;                                 // uncut muon z momentum
  TH1D             *fGeneralPzForward_uncut;                          // uncut forward muon z momentum
  TH1D             *fGeneralPzBarrel_uncut;                           // uncut barrel muon z momentum
  TH1D             *fGeneralPzRear_uncut;                             // uncut rear muon z momentum
  TH1D             *fGeneralPhi_uncut;                                // uncut muon phi distribution
  TH1D             *fGeneralPhiForward_uncut;                         // uncut forward muon phi distribution
  TH1D             *fGeneralPhiBarrel_uncut;                          // uncut barrel muon phi distribution
  TH1D             *fGeneralPhiRear_uncut;                            // uncut rear muon phi distribution
  TH1D             *fGeneralPhiMUBAC_uncut;                           // uncut phi distribution of muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiMUBACForward_uncut;                    // uncut phi distribution of forward muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiMUBACBarrel_uncut;                     // uncut phi distribution of barrel muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiMUBACRear_uncut;                       // uncut phi distribution of rear muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiBREMAT_uncut;                          // uncut phi distribution of muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiBREMATForward_uncut;                   // uncut phi distribution of forward muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiBREMATBarrel_uncut;                    // uncut phi distribution of barrel muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiBREMATRear_uncut;                      // uncut phi distribution of rear muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiMPMATCH_uncut;                         // uncut phi distribution of muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiMPMATCHForward_uncut;                  // uncut phi distribution of forward muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiMPMATCHBarrel_uncut;                   // uncut phi distribution of barrel muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiMPMATCHRear_uncut;                     // uncut phi distribution of rear muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiBREMATMUBAC_uncut;                     // uncut phi distribution of muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiBREMATMUBACForward_uncut;              // uncut phi distribution of forward muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiBREMATMUBACBarrel_uncut;               // uncut phi distribution of barrel muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiBREMATMUBACRear_uncut;                 // uncut phi distribution of rear muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBAC_uncut;                    // uncut phi distribution of muon found by MPMATCH and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBACForward_uncut;             // uncut phi distribution of forward muon found by MPMATCH and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBACBarrel_uncut;              // uncut phi distribution of barrel muon found by MPMATCH and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBACRear_uncut;                // uncut phi distribution of rear muon found by MPMATCH and MUBAC
  TH1D             *fGeneralTheta_uncut;                              // uncut muon theta distribution
  TH1D             *fGeneralThetaForward_uncut;                       // uncut forward muon theta distribution
  TH1D             *fGeneralThetaBarrel_uncut;                        // uncut barrel muon theta distribution
  TH1D             *fGeneralThetaRear_uncut;                          // uncut rear muon theta distribution
  TH1D             *fGeneralEta_uncut;                                // uncut muon eta distribution
  TH1D             *fGeneralEtaForward_uncut;                         // uncut forward muon eta distribution
  TH1D             *fGeneralEtaBarrel_uncut;                          // uncut barrel muon eta distribution
  TH1D             *fGeneralEtaRear_uncut;                            // uncut rear muon eta distribution
  TH1D             *fGeneralCharge_uncut;                             // uncut muon charge distribution
  TH1D             *fGeneralChargeForward_uncut;                      // uncut forward muon charge distribution
  TH1D             *fGeneralChargeBarrel_uncut;                       // uncut barrel muon charge distribution
  TH1D             *fGeneralChargeRear_uncut;                         // uncut rear muon charge distribution
  TH1D             *fGeneralMuonFinder_uncut;                         // uncut muon found by which muon finder
  TH1D             *fGeneralMuonFinder4_uncut;                        // uncut muon found by which muon finder for muon quality 4
  TH1D             *fGeneralMuonFinder5_uncut;                        // uncut muon found by which muon finder for muon quality 5
  TH1D             *fGeneralMuonFinder6_uncut;                        // uncut muon found by which muon finder for muon quality 6
  TH1D             *fGeneralSpecialFinder_uncut;                      // uncut muon found by which muon finder with special categories
  TH1D             *fGeneralSpecialFinderForward_uncut;               // uncut forward muon found by which muon finder with special categories
  TH1D             *fGeneralSpecialFinderBarrel_uncut;                // uncut barrel muon found by which muon finder with special categories
  TH1D             *fGeneralSpecialFinderRear_uncut;                  // uncut rear muon found by which muon finder with special categories
  TH1D             *fGeneralPMCTRUE_uncut;                            // uncut true muon momentum from MC info
  TH1D             *fGeneralPXMCTRUE_uncut;                           // uncut true x muon momentum from MC info
  TH1D             *fGeneralPYMCTRUE_uncut;                           // uncut true y muon momentum from MC info
  TH1D             *fGeneralPZMCTRUE_uncut;                           // uncut true z muon momentum from MC info
  TH1D             *fGeneralQuality_uncut;                            // uncut muon quality
  TH1D             *fGeneralQualityAndTrue_uncut;                     // uncut muon quality for muons reconstructed and true
  TH1D             *fGeneralQualityForward_uncut;                     // uncut forward muon quality
  TH1D             *fGeneralQualityBarrel_uncut;                      // uncut barrel muon quality
  TH1D             *fGeneralQualityRear_uncut;                        // uncut rear muon quality
  TH2D             *fGeneralPvsPMCTRUE_uncut;                         // uncut muon momentum vs. uncut true muon momentum from MC info
  TH2D             *fGeneralPXvsPXMCTRUE_uncut;                       // uncut x muon momentum vs. uncut true x muon momentum from MC info
  TH2D             *fGeneralPYvsPYMCTRUE_uncut;                       // uncut y muon momentum vs. uncut true y muon momentum from MC info
  TH2D             *fGeneralPZvsPZMCTRUE_uncut;                       // uncut z muon momentum vs. uncut true z muon momentum from MC info
  TH1D             *fGeneralPMCTRUEpos_uncut;                         // uncut true muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPXMCTRUEpos_uncut;                        // uncut true x muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPYMCTRUEpos_uncut;                        // uncut true y muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPZMCTRUEpos_uncut;                        // uncut true z muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPvsPMCTRUEpos_uncut;                      // uncut muon momentum vs. uncut true muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPXvsPXMCTRUEpos_uncut;                    // uncut x muon momentum vs. uncut true x muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPYvsPYMCTRUEpos_uncut;                    // uncut y muon momentum vs. uncut true y muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPZvsPZMCTRUEpos_uncut;                    // uncut z muon momentum vs. uncut true z muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPMCTRUEneg_uncut;                         // uncut true muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralPXMCTRUEneg_uncut;                        // uncut true x muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralPYMCTRUEneg_uncut;                        // uncut true y muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralPZMCTRUEneg_uncut;                        // uncut true z muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPvsPMCTRUEneg_uncut;                      // uncut muon momentum vs. uncut true muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPXvsPXMCTRUEneg_uncut;                    // uncut x muon momentum vs. uncut true x muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPYvsPYMCTRUEneg_uncut;                    // uncut y muon momentum vs. uncut true y muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPZvsPZMCTRUEneg_uncut;                    // uncut z muon momentum vs. uncut true z muon momentum from MC info for negative FMCKIN IDs
  
  TH1D             *fGeneral2DBeamSpotImpactParameter_uncut;          // uncut 2D impact parameter to beamspot
  TH1D             *fGeneral2DBeamSpotImpactSignificance_uncut;       // uncut 2D impact parameter to beamspot significance
  TH1D             *fGeneral2DMCBeamSpotImpactParameter_uncut;        // uncut true 2D impact parameter to nominal MC beamspot
  TH1D             *fGeneral2DTrueImpactParameter_uncut;              // uncut 2D impact parameter to nominal MC true vertex
  TH1D             *fGeneral2DMCTrueImpactParameter_uncut;            // uncut 2D MC true impact parameter
  TH2D             *fGeneral2DTrueImpactParamaterRecVsTrue_uncut;     // uncut 2D impact parameter to MC true vertex vs uncut true 2D impact parameter to MC true vertex
  TH2D             *fGeneral2DBeamSpotImpactParamaterRecVsTrue_uncut; // uncut 2D impact parameter to beamspot vs uncut true 2D impact parameter to nominal MC beamspot
  TH2D             *fGeneralGMuonPVsZTTP_uncut;                       // uncut momentum from gmuon vs. momentum from ztt

  // general plots
  TH1D             *fGeneralNMU;                                      // number of muons
  TH1D             *fGeneralNMUForward;                               // number of forward muons
  TH1D             *fGeneralNMUBarrel;                                // number of barrel muons
  TH1D             *fGeneralNMURear;                                  // number of rear muons
  TH1D             *fGeneralRegions;                                  // muon region
  TH1D             *fGeneralWeight;                                   // weight of muons
  TH1D             *fGeneralWeightForward;                            // weight of muons
  TH1D             *fGeneralWeightBarrel;                             // weight of muons
  TH1D             *fGeneralWeightRear;                               // weight of muons
  TH1D             *fGeneralWeightMUBAC;                              // weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightMUBACForward;                       // weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightMUBACBarrel;                        // weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightMUBACRear;                          // weight of muons for by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralWeightBREMAT;                             // weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightBREMATForward;                      // weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightBREMATBarrel;                       // weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightBREMATRear;                         // weight of muons for by BREMAT and not by MUBAC
  TH1D             *fGeneralWeightMPMATCH;                            // weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightMPMATCHForward;                     // weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightMPMATCHBarrel;                      // weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightMPMATCHRear;                        // weight of muons for by MPMATCH and not by MUBAC
  TH1D             *fGeneralWeightBREMATMUBAC;                        // weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightBREMATMUBACForward;                 // weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightBREMATMUBACBarrel;                  // weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightBREMATMUBACRear;                    // weight of muons for by BREMAT and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBAC;                       // weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBACForward;                // weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBACBarrel;                 // weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralWeightMPMATCHMUBACRear;                   // weight of muons for by MPMATCH and by MUBAC
  TH1D             *fGeneralProb;                                     // probability distribution
  TH1D             *fGeneralProbForward;                              // probability distribution for forward muons
  TH1D             *fGeneralProbBarrel;                               // probability distribution for barrel muons
  TH1D             *fGeneralProbRear;                                 // probability distribution for rear muons
  TH1D             *fGeneralP;                                        // muon momentum
  TH1D             *fGeneralPForward;                                 // forward muon momentum
  TH1D             *fGeneralPBarrel;                                  // barrel muon momentum
  TH1D             *fGeneralPRear;                                    // rear muon momentum
  TH1D             *fGeneralPt;                                       // muon transverse momentum
  TH1D             *fGeneralPtChosen;                                 // muon transverse momentum of muon from the chosen match
  TH1D             *fGeneralPtChosenFine2;                            // muon transverse momentum of muon from the chosen match in finer binning of 0.5 GeV
  TH1D             *fGeneralPtChosenFine4;                            // muon transverse momentum of muon from the chosen match in finer binning of 0.25 GeV
  TH1D             *fGeneralPtChosenFine8;                            // muon transverse momentum of muon from the chosen match in finer binning of 0.125 GeV
  TH1D             *fGeneralPtChosenFine16;                           // muon transverse momentum of muon from the chosen match in finer binning of 0.0625 GeV
  TH1D             *fGeneralPtChosenMC;                               // muon transverse momentum of muon from the chosen match which is a true MC muon
  TH1D             *fGeneralPtChosenFineMC;                           // muon transverse momentum of muon from the chosen match in finer binning which is a true MC muon
  TH1D             *fGeneralPtForward;                                // forward muon transverse momentum
  TH1D             *fGeneralPtBarrel;                                 // barrel muon transverse momentum
  TH1D             *fGeneralPtRear;                                   // rear muon transverse momentum
  TH1D             *fGeneralPtSpecial;                                // muon transverse momentum
  TH1D             *fGeneralPtSpecialForward;                         // forward muon transverse momentum
  TH1D             *fGeneralPtSpecialBarrel;                          // barrel muon transverse momentum
  TH1D             *fGeneralPtSpecialRear;                            // rear muon transverse momentum
  TH1D             *fGeneralPx;                                       // muon x momentum
  TH1D             *fGeneralPxForward;                                // forward muon x momentum
  TH1D             *fGeneralPxBarrel;                                 // barrel muon x momentum
  TH1D             *fGeneralPxRear;                                   // rear muon x momentum
  TH1D             *fGeneralPy;                                       // muon y momentum
  TH1D             *fGeneralPyForward;                                // forward muon y momentum
  TH1D             *fGeneralPyBarrel;                                 // barrel muon y momentum
  TH1D             *fGeneralPyRear;                                   // rear muon y momentum
  TH1D             *fGeneralPz;                                       // muon z momentum
  TH1D             *fGeneralPzForward;                                // forward muon z momentum
  TH1D             *fGeneralPzBarrel;                                 // barrel muon z momentum 
  TH1D             *fGeneralPzRear;                                   // rear muon z momentum
  TH1D             *fGeneralPhi;                                      // muon phi distribution
  TH1D             *fGeneralPhiForward;                               // forward muon phi distribution
  TH1D             *fGeneralPhiBarrel;                                // barrel muon phi distribution
  TH1D             *fGeneralPhiRear;                                  // rear muon phi distribution
  TH1D             *fGeneralPhiMUBAC;                                 // phi distribution of muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiMUBACForward;                          // phi distribution of forward muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiMUBACBarrel;                           // phi distribution of barrel muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiMUBACRear;                             // phi distribution of rear muon found by MUBAC and not by BREMAT or MPMATCH
  TH1D             *fGeneralPhiBREMAT;                                // phi distribution of muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiBREMATForward;                         // phi distribution of forward muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiBREMATBarrel;                          // phi distribution of barrel muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiBREMATRear;                            // phi distribution of rear muon found by BREMAT and not by MUBAC
  TH1D             *fGeneralPhiMPMATCH;                               // phi distribution of muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiMPMATCHForward;                        // phi distribution of forward muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiMPMATCHBarrel;                         // phi distribution of barrel muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiMPMATCHRear;                           // phi distribution of rear muon found by MPMATCH and not by MUBAC
  TH1D             *fGeneralPhiBREMATMUBAC;                           // phi distribution of muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiBREMATMUBACForward;                    // phi distribution of forward muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiBREMATMUBACBarrel;                     // phi distribution of barrel muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiBREMATMUBACRear;                       // phi distribution of rear muon found by BREMAT and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBAC;                          // phi distribution of muon found by MPMATCH and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBACForward;                   // phi distribution of forward muon found by MPMATCH and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBACBarrel;                    // phi distribution of barrel muon found by MPMATCH and MUBAC
  TH1D             *fGeneralPhiMPMATCHMUBACRear;                      // phi distribution of rear muon found by MPMATCH and MUBAC
  TH1D             *fGeneralTheta;                                    // muon theta distribution
  TH1D             *fGeneralThetaForward;                             // forward muon theta distribution
  TH1D             *fGeneralThetaBarrel;                              // barrel muon theta distribution
  TH1D             *fGeneralThetaRear;                                // rear muon theta distribution
  TH1D             *fGeneralEta;                                      // muon eta distribution
  TH1D             *fGeneralEtaChosen;                                // muon eta distribution of muon from the chosen match
  TH1D             *fGeneralEtaChosenLarge;                           // muon eta distribution of muon from the chosen match in large eta range
  TH1D             *fGeneralEtaChosenMC;                              // muon eta distribution of muon from the chosen match which is a true MC muon
  TH1D             *fGeneralEtaChosenLargeMC;                         // muon eta distribution of muon from the chosen match in large eta range which is a true MC muon
  TH1D             *fGeneralEtaForward;                               // forward muon eta distribution
  TH1D             *fGeneralEtaBarrel;                                // barrel muon eta distribution
  TH1D             *fGeneralEtaRear;                                  // rear muon eta distribution
  TH1D             *fGeneralCharge;                                   // muon charge distribution
  TH1D             *fGeneralChargeForward;                            // forward muon charge distribution
  TH1D             *fGeneralChargeBarrel;                             // barrel muon charge distribution
  TH1D             *fGeneralChargeRear;                               // rear muon charge distribution
  TH1D             *fGeneralMuonFinder;                               // muon found by which muon finder
  TH1D             *fGeneralMuonFinder4;                              // muon found by which muon finder for muon quality 4
  TH1D             *fGeneralMuonFinder5;                              // muon found by which muon finder for muon quality 5
  TH1D             *fGeneralMuonFinder6;                              // muon found by which muon finder for muon quality 6
  TH1D             *fGeneralSpecialFinder;                            // muon found by which muon finder with special categories
  TH1D             *fGeneralSpecialFinder4;                           // muon found in special categories by which muon finder for muon quality 4
  TH1D             *fGeneralSpecialFinder5;                           // muon found in special categories by which muon finder for muon quality 5
  TH1D             *fGeneralSpecialFinder6;                           // muon found in special categories by which muon finder for muon quality 6
  TH1D             *fGeneralSpecialFinder4Forward;                    // muon found in special categories by which muon finder for muon quality 4
  TH1D             *fGeneralSpecialFinder5Forward;                    // muon found in special categories by which muon finder for muon quality 5
  TH1D             *fGeneralSpecialFinder6Forward;                    // muon found in special categories by which muon finder for muon quality 6
  TH1D             *fGeneralSpecialFinder4Barrel;                     // muon found in special categories by which muon finder for muon quality 4
  TH1D             *fGeneralSpecialFinder5Barrel;                     // muon found in special categories by which muon finder for muon quality 5
  TH1D             *fGeneralSpecialFinder6Barrel;                     // muon found in special categories by which muon finder for muon quality 6
  TH1D             *fGeneralSpecialFinder4Rear;                       // muon found in special categories by which muon finder for muon quality 4
  TH1D             *fGeneralSpecialFinder5Rear;                       // muon found in special categories by which muon finder for muon quality 5
  TH1D             *fGeneralSpecialFinder6Rear;                       // muon found in special categories by which muon finder for muon quality 6
  TH1D             *fGeneralSpecialFinderForward;                     // forward muon found by which muon finder with special categories
  TH1D             *fGeneralSpecialFinderBarrel;                      // barrel muon found by which muon finder with special categories
  TH1D             *fGeneralSpecialFinderRear;                        // rear muon found by which muon finder with special categories
  TH1D             *fGeneralPMCTRUE;                                  // true muon momentum from MC info
  TH1D             *fGeneralPXMCTRUE;                                 // true x muon momentum from MC info
  TH1D             *fGeneralPYMCTRUE;                                 // true y muon momentum from MC info
  TH1D             *fGeneralPZMCTRUE;                                 // true z muon momentum from MC info
  TH2D             *fGeneralPvsPMCTRUE;                               // muon momentum vs. true muon momentum from MC info
  TH2D             *fGeneralPXvsPXMCTRUE;                             // x muon momentum vs. true x muon momentum from MC info
  TH2D             *fGeneralPYvsPYMCTRUE;                             // y muon momentum vs. true y muon momentum from MC info
  TH2D             *fGeneralPZvsPZMCTRUE;                             // z muon momentum vs. true z muon momentum from MC info
  TH1D             *fGeneralPMCTRUEpos;                               // true muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPXMCTRUEpos;                              // true x muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPYMCTRUEpos;                              // true y muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPZMCTRUEpos;                              // true z muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralQuality;                                  // muon quality
  TH1D             *fGeneralQualityAndTrue;                           // muon quality reconstructed and true
  TH1D             *fGeneralQualityForward;                           // forward muon quality
  TH1D             *fGeneralQualityBarrel;                            // barrel muon quality
  TH1D             *fGeneralQualityRear;                              // rear muon quality
  TH2D             *fGeneralPvsPMCTRUEpos;                            // muon momentum vs. true muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPXvsPXMCTRUEpos;                          // x muon momentum vs. true x muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPYvsPYMCTRUEpos;                          // y muon momentum vs. true y muon momentum from MC info for positive FMCKIN IDs
  TH2D             *fGeneralPZvsPZMCTRUEpos;                          // z muon momentum vs. true z muon momentum from MC info for positive FMCKIN IDs
  TH1D             *fGeneralPMCTRUEneg;                               // true muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralPXMCTRUEneg;                              // true x muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralPYMCTRUEneg;                              // true y muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralPZMCTRUEneg;                              // true z muon momentum from MC info for negative FMCKIN IDs
  TH1D             *fGeneralChosenIso01;                              // isolation of chosen muons in cone 0.1
  TH1D             *fGeneralChosenIso02;                              // isolation of chosen muons in cone 0.2
  TH1D             *fGeneralChosenIso03;                              // isolation of chosen muons in cone 0.3
  TH1D             *fGeneralChosenIso04;                              // isolation of chosen muons in cone 0.4
  TH1D             *fGeneralChosenIso05;                              // isolation of chosen muons in cone 0.5
  TH1D             *fGeneralChosenIso06;                              // isolation of chosen muons in cone 0.6
  TH1D             *fGeneralChosenIso07;                              // isolation of chosen muons in cone 0.7
  TH1D             *fGeneralChosenIso08;                              // isolation of chosen muons in cone 0.8
  TH1D             *fGeneralChosenIso09;                              // isolation of chosen muons in cone 0.9
  TH1D             *fGeneralChosenIso10;                              // isolation of chosen muons in cone 1.0
  TH2D             *fGeneralPvsPMCTRUEneg;                            // muon momentum vs. true muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPXvsPXMCTRUEneg;                          // x muon momentum vs. true x muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPYvsPYMCTRUEneg;                          // y muon momentum vs. true y muon momentum from MC info for negative FMCKIN IDs
  TH2D             *fGeneralPZvsPZMCTRUEneg;                          // z muon momentum vs. true z muon momentum from MC info for negative FMCKIN IDs

  TH1D             *fGeneralCrossTotal;                               // total cross section
  TH1D             *fGeneralCrossTotalRecNTrue;                       // total rec and true cross section
  TH1D             *fGeneralCrossTotalMuChamber;                      // total cross section using muon chambers info only
  TH1D             *fGeneralCrossTotalMuChamberRecNTrue;         
  TH1D             *fGeneralCrossTotalBAC;                            // total cross section using bac info only
  TH1D             *fGeneralCrossTotalBACRecNTrue;

  TH1D             *fGeneralCrossRegions;                             // muon region for cross section
  TH1D             *fGeneralCrossRegionsRecNTrue;                     // muon regions rec and true for cross section
  TH1D             *fGeneralCrossFinder;                              // special  muon finder for cross section
  TH1D             *fGeneralCrossFinderRecNTrue;                      // muon finder rec and true for cross section

  TH1D             *fGeneralCrossPt;                                  // muon pt for cross section
  TH1D             *fGeneralCrossPtRecNTrue;                          // muon pt  rec and true for cross section

  TH1D             *fGeneralCrossEta;                                 // muon eta for cross section
  TH1D             *fGeneralCrossEtaRecNTrue;                         // muon eta  rec and true for cross section

  TH1D             *fGeneralCrossPtFine;                              // fine muon pt for cross section
  TH1D             *fGeneralCrossPtFineRecNTrue;                      // fine muon pt  rec and true for cross section

  TH1D             *fGeneralCrossEtaFine;                             // fine muon eta for cross section
  TH1D             *fGeneralCrossEtaFineRecNTrue;                     // fine muon eta  rec and true for cross section

  TH1D             *fGeneralCrossPtMassimo;                           // muon pt for cross section in massimo's binning
  TH1D             *fGeneralCrossPtMassimoRecNTrue;                   // muon pt rec and true for cross section in massimo's binning

  TH1D             *fGeneralCrossEtaMassimo;                          // muon eta for cross section in massimo's binning
  TH1D             *fGeneralCrossEtaMassimoRecNTrue;                  // muon eta  rec and true for cross section in massimo's binning

  TH1D             *fGeneral2DBeamSpotImpactParameter;                // 2D impact parameter to beamspot
  TH1D             *fGeneral2DBeamSpotImpactParameter_Mirrored;       // 2D impact parameter to beamspot
  TH1D             *fGeneral2DBeamSpotImpactSignificance;             // 2D impact parameter to beamspot significance
  TH1D             *fGeneral2DMCBeamSpotImpactParameter;              // true 2D impact parameter to nominal MC beamspot
  TH1D             *fGeneral2DTrueImpactParameter;                    // 2D impact parameter to MC true vertex
  TH1D             *fGeneral2DMCTrueImpactParameter;                  // 2D MC true impact parameter
  TH2D             *fGeneral2DTrueImpactParamaterRecVsTrue;           // 2D impact parameter to MC true vertex vs true 2D impact parameter to MC true vertex
  TH2D             *fGeneral2DBeamSpotImpactParamaterRecVsTrue;       // 2D impact parameter to beamspot vs true 2D impact parameter to nominal MC beamspot
  TH2D             *fGeneralGMuonPVsZTTP;                             // momentum from gmuon vs. momentum from ztt

  // uncut control plots
  TH1D             *fControlProb_uncut;                               // uncut probability distribution
  TH1D             *fControlEta_uncut;                                // uncut muon eta distribution
  TH1D             *fControlP_uncut;                                  // uncut muon momentum
  TH1D             *fControlPt_uncut;                                 // uncut muon transverse momentum
  TH1D             *fControlChFlg_uncut;                              // uncut Chamber flag for barrel muons
  TH1D             *fControlMuonFinder_uncut;                         // uncut muon found by which muon finder
  TH1D             *fControlMuonMfpro_uncut;                          // uncut kalman filter probability for associated mfrtz track
  TH1D             *fControlMuonMfndf_uncut;                          // uncut kalman filter degrees of freedom
  TH1D             *fControlMuonMfz_uncut;                            // uncut kalman filter starting from internal plane (<500)
  TH1D             *fControlQuality_uncut;                            // uncut gmuon quality
  TH1D             *fControlQualityForwardBAC_uncut;                  // uncut gmuon quality for forward muons found by mubac
  TH1D             *fControlWeight_uncut;                             // uncut weight of muons

  // control plots
  TH1D             *fControlProbForward;                              // forward probability distribution
  TH1D             *fControlProbBarrel;                               // barrel probability distribution
  TH1D             *fControlProbRear;                                 // rear probability distribution
  TH1D             *fControlEtaForward;                               // forward eta distribution
  TH1D             *fControlEtaBarrel;                                // barrel eta distribution
  TH1D             *fControlEtaRear;                                  // rear eta distribution
  TH1D             *fControlPForward;                                 // forward momentum distribution
  TH1D             *fControlPBarrel;                                  // barrel momentum distribution
  TH1D             *fControlPRear;                                    // rear momentum distribution
  TH1D             *fControlPtForward;                                // forward transverse momentum distribution
  TH1D             *fControlPtBarrel;                                 // barrel transverse momentum distribution
  TH1D             *fControlPtRear;                                   // rear transverse momentum distribution
  TH1D             *fControlChFlgForward;                             // Chamber flag for forward muons
  TH1D             *fControlChFlgBarrel;                              // Chamber flag for barrel muons
  TH1D             *fControlChFlgRear;                                // Chamber flag for rear muons
  TH1D             *fControlMuonFinderForward;                        // forward muon found by which muon finder
  TH1D             *fControlMuonFinderBarrel;                         // barrel muon found by which muon finder
  TH1D             *fControlMuonFinderRear;                           // rear muon found by which muon finder
  TH1D             *fControlMuonMfproForward;                         // kalman filter probability for associated mfrtz track for forward muons
  TH1D             *fControlMuonMfproBarrel;                          // kalman filter probability for associated mfrtz track for barrel muons
  TH1D             *fControlMuonMfproRear;                            // kalman filter probability for associated mfrtz track for rear muons
  TH1D             *fControlMuonMfndfForward;                         // kalman filter degrees of freedom for forward muons
  TH1D             *fControlMuonMfndfBarrel;                          // kalman filter degrees of freedom for barrel muons
  TH1D             *fControlMuonMfndfRear;                            // kalman filter degrees of freedom for rear muons
  TH1D             *fControlMuonMfzForward;                           // kalman filter starting from internal plane (<500) for forward muons
  TH1D             *fControlMuonMfzBarrel;                            // kalman filter starting from internal plane (<500) for barrel muons
  TH1D             *fControlMuonMfzRear;                              // kalman filter starting from internal plane (<500) for rear muons
  TH1D             *fControlQualityForward;                           // gmuon quality for forward muons
  TH1D             *fControlQualityForwardBAC;                        // gmuon quality for forward muons found by mubac
  TH1D             *fControlQualityBarrel;                            // gmuon quality for barrel muons
  TH1D             *fControlQualityRear;                              // gmuon quality for rear muons
  TH1D             *fControlWeight;                                   // weight of muons passing all cuts
  TH2D             *fControlChamberFlag;

  TH1D *fPt_fakebin;       // special binning for fake muon  plots
  TH1D *fEta_lowPt_fakebin;
  TH1D *fEta_highPt_fakebin;
  TH1D *fPhi_lowPt_fakebin;
  TH1D *fPhi_highPt_fakebin;

  TH2D *fFakePxvsPxMCTRUE;                 //px vs pxtrue for fake muons
  TH2D *fFakePyvsPyMCTRUE;                 //py vs pytrue for fake muons
  TH2D *fFakePzvsPzMCTRUE;                 //pz vs pztrue for fake muons
  TH2D *fFakePtvsPtMCTRUE;                 //pt vs pttrue for fake muons
  TH2D *fFakeEtavsEtaMCTRUE;               //eta vs etatrue for fake muons
  TH1D *fFakeMuonAllPt;                    // pt dependence of particles identified as muons
  TH1D *fFakeMuonAllEta_lowPt;             // eta dependence of  particles identified as muons
  TH1D *fFakeMuonAllPhi_lowPt;             // phi dependence of  particles identified as muons
  TH1D *fFakeMuonAllEta_highPt;            // eta dependence of  particles identified as muons
  TH1D *fFakeMuonAllPhi_highPt;            // phi dependence of  particles identified as muons

//-------------------------------------------------------

  TH1D *fFakeMuonPionPt;                   // pt dependence of pions identified as muons
  TH1D *fFakeMuonPionEta_lowPt;            // eta dependence of pions identified as muons
  TH1D *fFakeMuonPionPhi_lowPt;            // phi dependence of pions identified as muons
  TH1D *fFakeMuonPionEta_highPt;           // eta dependence of pions identified as muons
  TH1D *fFakeMuonPionPhi_highPt;           // phi dependence of pions identified as muons
  TH1D *fFakeMuonKaonPt;                   // pt dependence of kaons identified as muons
  TH1D *fFakeMuonKaonEta_lowPt;            // eta dependence of kaons identified as muons
  TH1D *fFakeMuonKaonPhi_lowPt;            // phi dependence of kaons identified as muons
  TH1D *fFakeMuonKaonEta_highPt;           // eta dependence of kaons identified as muons
  TH1D *fFakeMuonKaonPhi_highPt;           // phi dependence of kaons identified as muons

//-------------------------------------------------------

  TH1D *fFakeDecayMuonPt;                  // pt dependence of  identified as muons from decays
  TH1D *fFakeDecayMuonEta_lowPt;           // eta dependence of K/P identified as muons from decays
  TH1D *fFakeDecayMuonPhi_lowPt;           // phi dependence of  K/P identified as muons from decays
  TH1D *fFakeDecayMuonEta_highPt;          // eta dependence of  K/P identified as muons from decays
  TH1D *fFakeDecayMuonPhi_highPt;          // phi dependence of  K/P identified as muons from decays
  TH1D *fFakeDecayMuonPionPt;              // pt dependence of pions  K/P identified as muons from decays
  TH1D *fFakeDecayMuonPionEta_lowPt;       // eta dependence   of pions identified as muons from decays
  TH1D *fFakeDecayMuonPionPhi_lowPt;       // phi dependence   of pions identified as muons from decays
  TH1D *fFakeDecayMuonPionEta_highPt;      // eta dependence of pions identified as muons from decays
  TH1D *fFakeDecayMuonPionPhi_highPt;      // phi dependence of pions identified as muons from decays
  TH1D *fFakeDecayMuonKaonPt;              // pt dependence of kaons identified as muons from decays
  TH1D *fFakeDecayMuonKaonEta_lowPt;       // eta dependence of kaons identified as muons from decays
  TH1D *fFakeDecayMuonKaonPhi_lowPt;       // phi dependence of kaons identified as muons from decays
  TH1D *fFakeDecayMuonKaonEta_highPt;      // eta dependence of kaons identified as muons from decays
  TH1D *fFakeDecayMuonKaonPhi_highPt;      // phi dependence of kaons identified as muons from decays

//-----------------------------------------------------------------

  TH1D *fFakePunchMuonPt;                  // pt dependence of K/P identified as muons from punch through
  TH1D *fFakePunchMuonEta_lowPt;           // eta dependence of K/P identified as muons from punch through
  TH1D *fFakePunchMuonPhi_lowPt;           // phi dependence of K/P identified as muons from punch through
  TH1D *fFakePunchMuonEta_highPt;          // eta dependence of K/P identified as muons from punch through
  TH1D *fFakePunchMuonPhi_highPt;          // phi dependence of K/P identified as muons from punch through
  TH1D *fFakePunchMuonPionPt;              // pt dependence of pions identified as muons from punch through
  TH1D *fFakePunchMuonPionEta_lowPt;       // eta dependence of pionsidentified as muons from punch through
  TH1D *fFakePunchMuonPionPhi_lowPt;       // phi dependence of pions identified as muons from punch through
  TH1D *fFakePunchMuonPionEta_highPt;      // eta dependence of pions identified as muons from punch through
  TH1D *fFakePunchMuonPionPhi_highPt;      // phi dependence of pions identified as muons from punch through
  TH1D *fFakePunchMuonKaonPt;              // pt dependence of kaons identified as muons from punch through
  TH1D *fFakePunchMuonKaonEta_lowPt;       // eta dependence of kaons identified as muons from punch through
  TH1D *fFakePunchMuonKaonPhi_lowPt;       // phi dependence of kaons identified as muons from punch through
  TH1D *fFakePunchMuonKaonEta_highPt;      // eta dependence of kaons identified as muons from punch through
  TH1D *fFakePunchMuonKaonPhi_highPt;      // phi dependence of kaons identified as muons from punch through

// probability plots that reconstr. track is reconstructed as muon)
  TH1D *fMuonProbabilityAllPt;        
  TH1D *fMuonProbabilityAllEta_lowPt;
  TH1D *fMuonProbabilityAllPhi_lowPt;
  TH1D *fMuonProbabilityAllEta_highPt;
  TH1D *fMuonProbabilityAllPhi_highPt;

  TH1D *fFakePionProbabilityAllPt;        
  TH1D *fFakePionProbabilityAllEta_lowPt;
  TH1D *fFakePionProbabilityAllPhi_lowPt;
  TH1D *fFakePionProbabilityAllEta_highPt;
  TH1D *fFakePionProbabilityAllPhi_highPt;
  TH1D *fFakeKaonProbabilityAllPt;        
  TH1D *fFakeKaonProbabilityAllEta_lowPt;
  TH1D *fFakeKaonProbabilityAllPhi_lowPt;
  TH1D *fFakeKaonProbabilityAllEta_highPt;
  TH1D *fFakeKaonProbabilityAllPhi_highPt;

// probability plots that reconstr. track is a fake muon from decays)
  TH1D *fMuonDecayProbabilityAllPt;        
  TH1D *fMuonDecayProbabilityAllEta_lowPt;
  TH1D *fMuonDecayProbabilityAllPhi_lowPt;
  TH1D *fMuonDecayProbabilityAllEta_highPt;
  TH1D *fMuonDecayProbabilityAllPhi_highPt;

  TH1D *fMuonDecayPionProbabilityAllPt;        
  TH1D *fMuonDecayPionProbabilityAllEta_lowPt;
  TH1D *fMuonDecayPionProbabilityAllPhi_lowPt;
  TH1D *fMuonDecayPionProbabilityAllEta_highPt;
  TH1D *fMuonDecayPionProbabilityAllPhi_highPt;
  TH1D *fMuonDecayKaonProbabilityAllPt;        
  TH1D *fMuonDecayKaonProbabilityAllEta_lowPt;
  TH1D *fMuonDecayKaonProbabilityAllPhi_lowPt;
  TH1D *fMuonDecayKaonProbabilityAllEta_highPt;
  TH1D *fMuonDecayKaonProbabilityAllPhi_highPt;

// probability plots that reconstr. track is a fake muon from punch trough)
  TH1D *fMuonPunchProbabilityAllPt;        
  TH1D *fMuonPunchProbabilityAllEta_lowPt;
  TH1D *fMuonPunchProbabilityAllPhi_lowPt;
  TH1D *fMuonPunchProbabilityAllEta_highPt;
  TH1D *fMuonPunchProbabilityAllPhi_highPt;
  TH1D *fMuonPunchPionProbabilityAllPt;        
  TH1D *fMuonPunchPionProbabilityAllEta_lowPt;
  TH1D *fMuonPunchPionProbabilityAllPhi_lowPt;
  TH1D *fMuonPunchPionProbabilityAllEta_highPt;
  TH1D *fMuonPunchPionProbabilityAllPhi_highPt;
  TH1D *fMuonPunchKaonProbabilityAllPt;        
  TH1D *fMuonPunchKaonProbabilityAllEta_lowPt;
  TH1D *fMuonPunchKaonProbabilityAllPhi_lowPt;
  TH1D *fMuonPunchKaonProbabilityAllEta_highPt;
  TH1D *fMuonPunchKaonProbabilityAllPhi_highPt;

  TH2D *fPrec_PtruevsDecdistPion_rear;       // pt reconstr. - pttrue (muonmother) vs scalar distance from prim vertex
  TH2D *fPrec_PtruevsDecdistPion_central;
  TH2D *fPrec_PtruevsDecdistPion_forward;  
  TH2D *fPrec_PtruevsDecdistKaon_rear;
  TH2D *fPrec_PtruevsDecdistKaon_central;
  TH2D *fPrec_PtruevsDecdistKaon_forward;  
  TH2D *fPrec_PtruevsDecdistMuon_rear;       // pt reconstr. - pttrue (muon) vs scalar distance from prim vertex
  TH2D *fPrec_PtruevsDecdistMuon_central;
  TH2D *fPrec_PtruevsDecdistMuon_forward;  
 
  TH2D *fFake2DMuonAll_PtEta;            // pt vs eta all fake muons 
  TH2D *fFake2DMuonDecay_PtEta;          // pt vs eta all decays from pi/k
  TH2D *fFake2DMuonPunch_PtEta;          // punch+missmatch
  TH2D *fProbability2DMuonAll_PtEta;     // pt vs eta all fake muons 
  TH2D *fProbability2DMuonDecay_PtEta;   // pt vs eta all decays from pi/k
  TH2D *fProbability2DMuonPunch_PtEta;   // punch+missmatch
  TH1D *fRecTrueMuonMother;              //    muon mother of true muon e.g. no decay muon

//----------------------------------------------------------------------------

  TH1D *fFakeProbabilityAllPt;            // pt dependence of probability to identify pion as muon
  TH1D *fFakeProbabilityAllEta_lowPt;     // eta dependence of probability to identify charged particle as muon
  TH1D *fFakeProbabilityAllPhi_lowPt;     // phi dependence of probability to identify charged particle as muon low Pt
  TH1D *fFakeProbabilityAllEta_highPt;    // eta dependence of probability to identify charged particle as muon
  TH1D *fFakeProbabilityAllPhi_highPt;    // phi dependence of probability to identify charged particle as muon low Pt
  TH2D *fFake2DMuonAll_PtEta_Bremat;      // 2D fakes for special finders
  TH2D *fFake2DMuonAll_PtEta_MPMatch;
  TH2D *fFake2DMuonAll_PtEta_Bac;
  TH2D *fFake2DProbMuonAll_PtEta_Bremat;  // 2D fakes probabilities for special finders
  TH2D *fFake2DProbMuonAll_PtEta_MPMatch;
  TH2D *fFake2DProbMuonAll_PtEta_Bac;


 public:
  GMuons();
  virtual ~GMuons();

  virtual Bool_t Do();
  virtual Bool_t Reset();
  virtual Bool_t Fill();
  virtual Bool_t GetAllCuts();
  virtual Bool_t Finalize();

  virtual Bool_t FillHistos();
  virtual Bool_t CreateGeneral();
  virtual Bool_t CreateFake();
  virtual Bool_t FillGeneral();
  virtual Bool_t CreateControl();
  virtual Bool_t ObjectsFillHistos();
  virtual Bool_t ObjectsFillGeneral(GMuon *muon);
  virtual Bool_t ObjectsFillControl(GMuon *muon);
  virtual Bool_t ObjectsFillFake(GMuon *muon);

  virtual Bool_t FillMuonFinderHisto(GMuon *muon, TH1D* histo, Double_t weight = 1.0);

  virtual Bool_t CountMuons();
  virtual Bool_t CheckGlomu();

  virtual Bool_t CheckForwardTrackMuon(GMuon *muon);
  virtual Bool_t ModifyMuonQuality(GMuon *muon);
  virtual Bool_t CheckFinderCut(GMuon *muon);
  virtual Bool_t CheckQualityCut(GMuon *muon);
  virtual Bool_t CheckForwardTrackMuonCut(GMuon *muon);
  virtual Bool_t CheckBACFQualityCut(GMuon *muon);
  virtual Bool_t CheckEtaCut(GMuon *muon);
  virtual Bool_t CheckTakeCut(GMuon *muon);
  virtual Bool_t CheckEfficiencyCorrection(GMuon *muon);
  virtual Bool_t CheckPCut(GMuon *muon);
  virtual Bool_t CheckPtCut(GMuon *muon);
  virtual Bool_t CheckVcidLowCut(GMuon *muon);
  virtual Bool_t CheckVcidUpCut(GMuon *muon);
  virtual Bool_t CheckBrematCut(GMuon *muon);
  virtual Bool_t CheckMPMatchCut(GMuon *muon);
  virtual Bool_t CheckMUBACCut(GMuon *muon);
  virtual Bool_t CheckOnlyVertexFittedCut(GMuon *muon);
  virtual Bool_t CheckAllCuts(GMuon *muon);
  virtual Bool_t CalcBeamSpotImpactParameter(GMuon *muon);
  virtual Bool_t CalcMuonIsolation(GMuon *muon);
  virtual Bool_t CalcMuonImpactParameter(GMuon *muon);
  virtual Bool_t CalcMuonJetMass(GMuon *muon);
  virtual Bool_t FillMuonNdofandZ(GMuon *muon);
  virtual Bool_t CheckMVCuts(GMuon *muon);
  virtual Bool_t FakeAlreadyStored(GMuon *muon);
  virtual Bool_t FillSpecialFinderHisto(TH1D* histo, GMuon *muon);
  virtual Int_t  GetSpecialFinderBin(GMuon *muon);
  virtual Bool_t ProduceMirroredPlot();

  virtual GMuon* GetMuon(Int_t index);

  virtual TString PrintMessage(TString option);
  virtual Bool_t  Print(TString option);

  inline virtual Int_t    GetNMuons()                    { return fNMuons;                      }
  inline virtual Int_t    GetMuonsCut()                  { return fMuonsCut;                    }
  inline virtual Int_t    GetBarrelMuons()               { return fBarrelMuons;                 }
  inline virtual Int_t    GetRearMuons()                 { return fRearMuons;                   }
  inline virtual Int_t    GetForwardMuons()              { return fForwardMuons;                }
  inline virtual Bool_t   GetGlomus()                    { return fGlomus;                      }
  inline virtual Double_t GetMuonImp()                   { return fMuonImp;                     }
  inline virtual Double_t GetMuonImperr()                { return fMuonImperr;                  }
  inline virtual Double_t GetMuonDCA_x()                 { return fMuonDCA_x;                   }
  inline virtual Double_t GetMuonDCA_y()                 { return fMuonDCA_y;                   }
  inline virtual Double_t GetMuonDCA_z()                 { return fMuonDCA_z;                   }
  inline virtual Double_t GetMuonImpSig()                { return fMuonImpSig;                  }
  inline virtual Double_t GetMuonJetMass()               { return fMuonJetMass;                 }
  inline virtual Double_t GetMuonJetEt()                 { return fMuonJetEt;                   }
  inline virtual Double_t GetMuonMuz()                   { return fMuonMuz;                     }
  inline virtual Int_t    GetMuonMundof()                { return fMuonMundof;                  }

  inline virtual TH1D*  GetFakeMuonAllPt()               { return fFakeMuonAllPt;               }
  inline virtual TH1D*  GetFakeMuonAllEta_lowPt()        { return fFakeMuonAllEta_lowPt;        }
  inline virtual TH1D*  GetFakeMuonAllPhi_lowPt()        { return fFakeMuonAllPhi_lowPt;        }
  inline virtual TH1D*  GetFakeMuonAllEta_highPt()       { return fFakeMuonAllEta_highPt;       }
  inline virtual TH1D*  GetFakeMuonAllPhi_highPt()       { return fFakeMuonAllPhi_highPt;       }

  inline virtual TH1D*  GetFakeMuonPionPt()              { return fFakeMuonPionPt;              }
  inline virtual TH1D*  GetFakeMuonPionEta_lowPt()       { return fFakeMuonPionEta_lowPt;       }
  inline virtual TH1D*  GetFakeMuonPionPhi_lowPt()       { return fFakeMuonPionPhi_lowPt;       }
  inline virtual TH1D*  GetFakeMuonPionEta_highPt()      { return fFakeMuonPionEta_highPt;      }
  inline virtual TH1D*  GetFakeMuonPionPhi_highPt()      { return fFakeMuonPionPhi_highPt;      }
  inline virtual TH1D*  GetFakeMuonKaonPt()              { return fFakeMuonKaonPt;              }        
  inline virtual TH1D*  GetFakeMuonKaonEta_lowPt()       { return fFakeMuonKaonEta_lowPt;       } 
  inline virtual TH1D*  GetFakeMuonKaonPhi_lowPt()       { return fFakeMuonKaonPhi_lowPt;       } 
  inline virtual TH1D*  GetFakeMuonKaonEta_highPt()      { return fFakeMuonKaonEta_highPt;      }
  inline virtual TH1D*  GetFakeMuonKaonPhi_highPt()      { return fFakeMuonKaonPhi_highPt;      }


  inline virtual TH1D*  GetFakeDecayMuonPionPt()         { return fFakeDecayMuonPionPt;         }
  inline virtual TH1D*  GetFakeDecayMuonPionEta_lowPt()  { return fFakeDecayMuonPionEta_lowPt;  }
  inline virtual TH1D*  GetFakeDecayMuonPionPhi_lowPt()  { return fFakeDecayMuonPionPhi_lowPt;  }
  inline virtual TH1D*  GetFakeDecayMuonPionEta_highPt() { return fFakeDecayMuonPionEta_highPt; }
  inline virtual TH1D*  GetFakeDecayMuonPionPhi_highPt() { return fFakeDecayMuonPionPhi_highPt; }
  inline virtual TH1D*  GetFakeDecayMuonKaonPt()         { return fFakeDecayMuonKaonPt;         }        
  inline virtual TH1D*  GetFakeDecayMuonKaonEta_lowPt()  { return fFakeDecayMuonKaonEta_lowPt;  } 
  inline virtual TH1D*  GetFakeDecayMuonKaonPhi_lowPt()  { return fFakeDecayMuonKaonPhi_lowPt;  } 
  inline virtual TH1D*  GetFakeDecayMuonKaonEta_highPt() { return fFakeDecayMuonKaonEta_highPt; }
  inline virtual TH1D*  GetFakeDecayMuonKaonPhi_highPt() { return fFakeDecayMuonKaonPhi_highPt; }
  
  inline virtual TH1D*  GetFakePunchMuonPionPt()         { return fFakePunchMuonPionPt;         }
  inline virtual TH1D*  GetFakePunchMuonPionEta_lowPt()  { return fFakePunchMuonPionEta_lowPt;  }
  inline virtual TH1D*  GetFakePunchMuonPionPhi_lowPt()  { return fFakePunchMuonPionPhi_lowPt;  }
  inline virtual TH1D*  GetFakePunchMuonPionEta_highPt() { return fFakePunchMuonPionEta_highPt; }
  inline virtual TH1D*  GetFakePunchMuonPionPhi_highPt() { return fFakePunchMuonPionPhi_highPt; }
  inline virtual TH1D*  GetFakePunchMuonKaonPt()         { return fFakePunchMuonKaonPt;         }        
  inline virtual TH1D*  GetFakePunchMuonKaonEta_lowPt()  { return fFakePunchMuonKaonEta_lowPt;  } 
  inline virtual TH1D*  GetFakePunchMuonKaonPhi_lowPt()  { return fFakePunchMuonKaonPhi_lowPt;  } 
  inline virtual TH1D*  GetFakePunchMuonKaonEta_highPt() { return fFakePunchMuonKaonEta_highPt; }
  inline virtual TH1D*  GetFakePunchMuonKaonPhi_highPt() { return fFakePunchMuonKaonPhi_highPt; }


 ClassDef(GMuons,0) // Muon Class for everything which is related only to Muons
};
R__EXTERN GMuons *gMuons;

#endif
