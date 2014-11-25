//
// GDIMuons.h
//
// $Author: ibloch $
// $Date: 2007/01/04 22:34:45 $
// $Revision: 1.27 $
//

#ifndef GUT_GDIMuons
#define GUT_GDIMuons

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif
#ifndef ROOT_TRandom3
#include <TRandom3.h>
#endif

class GDIMuons : public GPhysObj {

 private:

  TClonesArray   *fDIMuons;                              // holds dimuon objects per event 
  Int_t           fNDIMuons;                             // number of dimuons
  
  Bool_t          fInvMassCut;                           // flag if one dimuon fulfills invarant mass cuts
  Bool_t          fSqSumIsolationCut;                    // flag if one dimuon fulfills requirement to be called isolated
  Bool_t          fDeltaRCut;                            // flag if one dimuon fulfills delta R cut
  Bool_t          fDeltaPhiCut;                          // flag if one dimuon fulfills delta phi cut
  Bool_t          fDeltaThetaCut;                        // flag if one dimuon fulfills delta theta cut
  Bool_t          fDeltaEtaCut;                          // flag if one dimuon fulfills delta eta cut
  Bool_t          fPtAsymetryCut;                        // flag if one dimuon fulfills pt asymetry cut
  Bool_t          fEtFractionHighCut;                    // flag if one dimuon fulfills upper dimumass dependent et fraction cut
  Bool_t          fEtFractionLowCut;                     // flag if one dimuon fulfills lower et fraction cut
  Bool_t          fDifChargeCut;                         // flag if one dimuon fulfills different charge cut
  Bool_t          fCharmMCJpsiCut;                       // flag if muons in dimuon come from jpsi in ccbar MC
  Bool_t          fCharmMCPsiprimeCut;                   // flag if muons in dimuon come from Psiprime in ccbar MC

  Bool_t          fAllCuts;                              // flag if one dimuon fulfills all cuts

/// 

  Bool_t 	  DL_cut;
  Bool_t 	  Chi2Ndof_cut;

  Bool_t   	  case_var01;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var02;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var03;				 // flag fo defining jet-muons relations 

  Bool_t   	  case_var11;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var12;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var13;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var14;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var15;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var16;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var17;				 // flag fo defining jet-muons relations 

  Bool_t   	  case_var21;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var22;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var23;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var24;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var25;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var26;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var27;				 // flag fo defining jet-muons relations 

  Bool_t   	  case_var31;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var32;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var33;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var34;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var35;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var36;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var37;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var38;				 // flag fo defining jet-muons relations 

  Bool_t   	  case_var21_1;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var21_2;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var24_1;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var24_2;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var31_1;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var31_2;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var34_1;				 // flag fo defining jet-muons relations 
  Bool_t   	  case_var34_2;				 // flag fo defining jet-muons relations 


///

  Bool_t          fDoCalcIsolation;                      // flag if one dimuon fulfills all cuts to enable isolation calculation

  Int_t           fSelectedIndex;                        // index for determination of best dimuon fulfilling cuts

  Int_t           fNGoodDIMuons;                         // number of good dimuons per event 
  Int_t           fNChosenDIMuons;                       // number of chosen dimuons per event 

  Double_t        fSecvtx_DL2;                           // Decay length
  Double_t        fSecvtx_DL2_err;                       // Decay length error
  Double_t        fSecvtx_DL2_sign;                      // Decay length significance
  Double_t        fSecvtx_DL2_signp;                     // Positive Decay length significance
  Double_t        fSecvtx_DL2_signm;                     // Negative Decay length significance

  Double_t        fMuonJetEt;
  Double_t        fMuonJetEta;
  Double_t        fMuonJetE;
  Double_t        fMuonJetTheta;
  Double_t        fMuonJetP;
  Double_t        fMuonJetPt;

  Double_t        fMuonJetMass;
  
// general plots

  TH1D    *fGeneralNperEv_uncut;                     // uncut dimuon per event
  TH1D    *fGeneralDIMuonMass_uncut;                 // uncut dimuon mass
  TH1D    *fGeneralDIMuonMassLow_uncut;              // uncut low dimuon mass
  TH1D    *fGeneralDIMuonMassHigh_uncut;             // uncut high dimuon mass
  TH1D    *fGeneralDIMuonMass_LikeSign_uncut;        // uncut dimuon mass for like sign dimuons
  TH1D    *fGeneralDIMuonMassLow_LikeSign_uncut;     // uncut low dimuon mass for like sign dimuons
  TH1D    *fGeneralDIMuonMassHigh_LikeSign_uncut;    // uncut high dimuon mass for like sign dimuons
  TH1D    *fGeneralDIMuonMass_UnlikeSign_uncut;      // uncut dimuon mass for unlike sign dimuons
  TH1D    *fGeneralDIMuonMassLow_UnlikeSign_uncut;   // uncut low dimuon mass for unlike sign dimuons
  TH1D    *fGeneralDIMuonMassHigh_UnlikeSign_uncut;  // uncut high dimuon mass for unlike sign dimuons

  TH1D    *fGeneralMass_lu_is_uncut;                 // uncut dimuon mass low like sign isolated
  TH1D    *fGeneralMass_ll_is_uncut;                 // uncut dimuon mass low like sign isolated
  TH1D    *fGeneralMass_hu_is_uncut;                 // uncut dimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_hl_is_uncut;                 // uncut dimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_lu_nis_uncut;                // uncut dimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_ll_nis_uncut;                // uncut dimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_hu_nis_uncut;                // uncut dimuon mass high unlike sign non-isolated
  TH1D    *fGeneralMass_hl_nis_uncut;                // uncut dimuon mass high unlike sign non-isolated

  TH1D    *fGeneralDeltaR_uncut;                     // uncut dimuon delta R
  TH1D    *fGeneralDeltaR_lu_is_uncut;               // uncut dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_is_uncut;               // uncut dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_is_uncut;               // uncut dimuon delta R high mass, like sign 
  TH1D    *fGeneralDeltaR_hl_is_uncut;               // uncut dimuon delta R high mass, like sign 
  TH1D    *fGeneralDeltaR_lu_nis_uncut;              // uncut dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_nis_uncut;              // uncut dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_nis_uncut;              // uncut dimuon delta R high mass, like sign 
  TH1D    *fGeneralDeltaR_hl_nis_uncut;              // uncut dimuon delta R high mass, like sign 

  TH1D    *fGeneralDeltaPhi_uncut;                   // uncut dimuon delta Phi
  TH1D    *fGeneralDeltaPhi_lu_is_uncut;             // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_is_uncut;             // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_is_uncut;             // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_is_uncut;             // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_lu_nis_uncut;            // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_nis_uncut;            // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_nis_uncut;            // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_nis_uncut;            // uncut dimuon delta Phi high mass, like sign 

  TH1D    *fGeneralDeltaEta_uncut;                   // uncut dimuon delta Eta
  TH1D    *fGeneralDeltaTheta_uncut;                 // uncut dimuon delta Theta
  TH1D    *fGeneraldimuphi_uncut;                    // uncut dimuon dimuphi
  TH1D    *fGeneraldimuphi_lu_is_uncut;              // uncut dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_ll_is_uncut;              // uncut dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_hu_is_uncut;              // uncut dimuon dimuphi high mass, like sign	
  TH1D    *fGeneraldimuphi_hl_is_uncut;              // uncut dimuon dimuphi high mass, like sign 
  TH1D    *fGeneraldimuphi_lu_nis_uncut;             // uncut dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_ll_nis_uncut;             // uncut dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_hu_nis_uncut;             // uncut dimuon dimuphi high mass, like sign	
  TH1D    *fGeneraldimuphi_hl_nis_uncut;             // uncut dimuon dimuphi high mass, like sign 
  TH1D    *fGeneraldimueta_uncut;                    // uncut dimuon dimueta
  TH1D    *fGeneraldimueta_lu_is_uncut;              // uncut dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_ll_is_uncut;              // uncut dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_hu_is_uncut;              // uncut dimuon dimueta high mass, like sign	
  TH1D    *fGeneraldimueta_hl_is_uncut;              // uncut dimuon dimueta high mass, like sign 
  TH1D    *fGeneraldimueta_lu_nis_uncut;             // uncut dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_ll_nis_uncut;             // uncut dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_hu_nis_uncut;             // uncut dimuon dimueta high mass, like sign	
  TH1D    *fGeneraldimueta_hl_nis_uncut;             // uncut dimuon dimueta high mass, like sign 
  TH1D    *fGeneralPtAsymetry_uncut;                 // uncut dimuon pt Asymetry
  TH1D    *fGeneralPtAsymetry_lu_is_uncut;           // uncut dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_is_uncut;           // uncut dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_is_uncut;           // uncut dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_is_uncut;           // uncut dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_lu_nis_uncut;          // uncut dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_nis_uncut;          // uncut dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_nis_uncut;          // uncut dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_nis_uncut;          // uncut dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralpt_uncut;                         // uncut dimuon pt
  TH1D    *fGeneralpt_lu_is_uncut;                   // uncut dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_is_uncut;                   // uncut dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_is_uncut;                   // uncut dimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_is_uncut;                   // uncut dimuon pt high mass, like sign 
  TH1D    *fGeneralpt_lu_nis_uncut;                  // uncut dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_nis_uncut;                  // uncut dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_nis_uncut;                  // uncut dimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_nis_uncut;                  // uncut dimuon pt high mass, like sign 
  TH1D    *fGeneraldimupt_uncut;                     // uncut dimuon dimupt
  TH1D    *fGeneraldimupt_lu_is_uncut;               // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_ll_is_uncut;               // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_hu_is_uncut;               // uncut dimuon dimupt high mass, like sign	
  TH1D    *fGeneraldimupt_hl_is_uncut;               // uncut dimuon dimupt high mass, like sign 
  TH1D    *fGeneraldimupt_lu_nis_uncut;              // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_ll_nis_uncut;              // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_hu_nis_uncut;              // uncut dimuon dimupt high mass, like sign	
  TH1D    *fGeneraldimupt_hl_nis_uncut;              // uncut dimuon dimupt high mass, like sign 
  TH1D    *fGeneraleta_uncut;                        // uncut dimuon eta
  TH1D    *fGeneraleta_lu_is_uncut;                  // uncut dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_is_uncut;                  // uncut dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_is_uncut;                  // uncut dimuon eta high mass, like sign
  TH1D    *fGeneraleta_hl_is_uncut;                  // uncut dimuon eta high mass, like sign  
  TH1D    *fGeneraleta_lu_nis_uncut;                 // uncut dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_nis_uncut;                 // uncut dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_nis_uncut;                 // uncut dimuon eta high mass, like sign
  TH1D    *fGeneraleta_hl_nis_uncut;                 // uncut dimuon eta high mass, like sign  

  TH1D    *fGeneralphi_uncut;                        // uncut single muon phi
  TH1D    *fGeneralphi_lu_is_uncut;                  // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_is_uncut;                  // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_is_uncut;                  // uncut single muon phi high mass, like sign
  TH1D    *fGeneralphi_hl_is_uncut;                  // uncut single muon phi high mass, like sign  
  TH1D    *fGeneralphi_lu_nis_uncut;                 // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_nis_uncut;                 // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_nis_uncut;                 // uncut single muon phi high mass, like sign
  TH1D    *fGeneralphi_hl_nis_uncut;                 // uncut single muon phi high mass, like sign  
  TH1D    *fGeneralmuqual_uncut;                     // uncut single muon muqual
  TH1D    *fGeneralmuqual_lu_is_uncut;               // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_is_uncut;               // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_is_uncut;               // uncut single muon muqual high mass, like sign
  TH1D    *fGeneralmuqual_hl_is_uncut;               // uncut single muon muqual high mass, like sign  
  TH1D    *fGeneralmuqual_lu_nis_uncut;              // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_nis_uncut;              // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_nis_uncut;              // uncut single muon muqual high mass, like sign
  TH1D    *fGeneralmuqual_hl_nis_uncut;              // uncut single muon muqual high mass, like sign  

  TH1D    *fGeneralVtxMass_uncut  ;                  // uncut dimuon VtxMass
  TH1D    *fGeneralVtxMass_is_lu_uncut;              // uncut dimuon VtxMass, low mass, unlike sign
  TH1D    *fGeneralVtxMass_is_ll_uncut;              // uncut dimuon VtxMass, low mass, like sign
  TH1D    *fGeneralVtxMass_is_hu_uncut;              // uncut dimuon VtxMass, high mass, unlike sign
  TH1D    *fGeneralVtxMass_is_hl_uncut;              // uncut dimuon VtxMass, high mass, like sign
  TH1D    *fGeneralVtxMass_nis_lu_uncut;             // uncut dimuon VtxMass, low mass, unlike sign
  TH1D    *fGeneralVtxMass_nis_ll_uncut;             // uncut dimuon VtxMass, low mass, like sign
  TH1D    *fGeneralVtxMass_nis_hu_uncut;             // uncut dimuon VtxMass, high mass, unlike sign
  TH1D    *fGeneralVtxMass_nis_hl_uncut;             // uncut dimuon VtxMass, high mass, like sign

  TH1D    *fGeneralChi2_uncut  ;                     // uncut dimuon Chi2
  TH1D    *fGeneralChi2_is_lu_uncut;                 // uncut dimuon Chi2, low mass, unlike sign
  TH1D    *fGeneralChi2_is_ll_uncut;                 // uncut dimuon Chi2, low mass, like sign
  TH1D    *fGeneralChi2_is_hu_uncut;                 // uncut dimuon Chi2, high mass, unlike sign
  TH1D    *fGeneralChi2_is_hl_uncut;                 // uncut dimuon Chi2, high mass, like sign
  TH1D    *fGeneralChi2_nis_lu_uncut;                // uncut dimuon Chi2, low mass, unlike sign
  TH1D    *fGeneralChi2_nis_ll_uncut;                // uncut dimuon Chi2, low mass, like sign
  TH1D    *fGeneralChi2_nis_hu_uncut;                // uncut dimuon Chi2, high mass, unlike sign
  TH1D    *fGeneralChi2_nis_hl_uncut;                // uncut dimuon Chi2, high mass, like sign
 
  TH1D    *fGeneralNdof_uncut  ;                     // uncut dimuon Ndof
  TH1D    *fGeneralNdof_is_lu_uncut;                 // uncut dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneralNdof_is_ll_uncut;                 // uncut dimuon Ndof, low mass, like sign
  TH1D    *fGeneralNdof_is_hu_uncut;                 // uncut dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneralNdof_is_hl_uncut;                 // uncut dimuon Ndof, high mass, like sign
  TH1D    *fGeneralNdof_nis_lu_uncut;                // uncut dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneralNdof_nis_ll_uncut;                // uncut dimuon Ndof, low mass, like sign
  TH1D    *fGeneralNdof_nis_hu_uncut;                // uncut dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneralNdof_nis_hl_uncut;                // uncut dimuon Ndof, high mass, like sign

  TH1D    *fGeneralMulti_uncut  ;                    // uncut dimuon Multi
  TH1D    *fGeneralMulti_is_lu_uncut;                // uncut dimuon Multi, low mass, unlike sign
  TH1D    *fGeneralMulti_is_ll_uncut;                // uncut dimuon Multi, low mass, like sign
  TH1D    *fGeneralMulti_is_hu_uncut;                // uncut dimuon Multi, high mass, unlike sign
  TH1D    *fGeneralMulti_is_hl_uncut;                // uncut dimuon Multi, high mass, like sign
  TH1D    *fGeneralMulti_nis_lu_uncut;               // uncut dimuon Multi, low mass, unlike sign
  TH1D    *fGeneralMulti_nis_ll_uncut;               // uncut dimuon Multi, low mass, like sign
  TH1D    *fGeneralMulti_nis_hu_uncut;               // uncut dimuon Multi, high mass, unlike sign
  TH1D    *fGeneralMulti_nis_hl_uncut;               // uncut dimuon Multi, high mass, like sign

  TH1D    *fGeneralNrsecvtx_uncut  ;                 // uncut dimuon Nrsecvtx
  TH1D    *fGeneralNrsecvtx_is_lu_uncut;             // uncut dimuon Nrsecvtx, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_is_ll_uncut;             // uncut dimuon Nrsecvtx, low mass, like sign
  TH1D    *fGeneralNrsecvtx_is_hu_uncut;             // uncut dimuon Nrsecvtx, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_is_hl_uncut;             // uncut dimuon Nrsecvtx, high mass, like sign
  TH1D    *fGeneralNrsecvtx_nis_lu_uncut;            // uncut dimuon Nrsecvtx, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_nis_ll_uncut;            // uncut dimuon Nrsecvtx, low mass, like sign
  TH1D    *fGeneralNrsecvtx_nis_hu_uncut;            // uncut dimuon Nrsecvtx, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_nis_hl_uncut;            // uncut dimuon Nrsecvtx, high mass, like sign

  TH1D    *fGeneralMunphi_uncut  ;                   // uncut dimuon Munphi
  TH1D    *fGeneralMunphi_is_lu_uncut;               // uncut dimuon Munphi, low mass, unlike sign
  TH1D    *fGeneralMunphi_is_ll_uncut;               // uncut dimuon Munphi, low mass, like sign
  TH1D    *fGeneralMunphi_is_hu_uncut;               // uncut dimuon Munphi, high mass, unlike sign
  TH1D    *fGeneralMunphi_is_hl_uncut;               // uncut dimuon Munphi, high mass, like sign
  TH1D    *fGeneralMunphi_nis_lu_uncut;              // uncut dimuon Munphi, low mass, unlike sign
  TH1D    *fGeneralMunphi_nis_ll_uncut;              // uncut dimuon Munphi, low mass, like sign
  TH1D    *fGeneralMunphi_nis_hu_uncut;              // uncut dimuon Munphi, high mass, unlike sign
  TH1D    *fGeneralMunphi_nis_hl_uncut;              // uncut dimuon Munphi, high mass, like sign

  TH1D    *fGeneralMuz_uncut  ;                      // uncut dimuon Muz
  TH1D    *fGeneralMuz_is_lu_uncut;                  // uncut dimuon Muz, low mass, unlike sign
  TH1D    *fGeneralMuz_is_ll_uncut;                  // uncut dimuon Muz, low mass, like sign
  TH1D    *fGeneralMuz_is_hu_uncut;                  // uncut dimuon Muz, high mass, unlike sign
  TH1D    *fGeneralMuz_is_hl_uncut;                  // uncut dimuon Muz, high mass, like sign
  TH1D    *fGeneralMuz_nis_lu_uncut;                 // uncut dimuon Muz, low mass, unlike sign
  TH1D    *fGeneralMuz_nis_ll_uncut;                 // uncut dimuon Muz, low mass, like sign
  TH1D    *fGeneralMuz_nis_hu_uncut;                 // uncut dimuon Muz, high mass, unlike sign
  TH1D    *fGeneralMuz_nis_hl_uncut;                 // uncut dimuon Muz, high mass, like sign

  TH1D    *fGeneralMundof_uncut  ;                   // uncut dimuon Mundof
  TH1D    *fGeneralMundof_is_lu_uncut;               // uncut dimuon Mundof, low mass, unlike sign
  TH1D    *fGeneralMundof_is_ll_uncut;               // uncut dimuon Mundof, low mass, like sign
  TH1D    *fGeneralMundof_is_hu_uncut;               // uncut dimuon Mundof, high mass, unlike sign
  TH1D    *fGeneralMundof_is_hl_uncut;               // uncut dimuon Mundof, high mass, like sign
  TH1D    *fGeneralMundof_nis_lu_uncut;              // uncut dimuon Mundof, low mass, unlike sign
  TH1D    *fGeneralMundof_nis_ll_uncut;              // uncut dimuon Mundof, low mass, like sign
  TH1D    *fGeneralMundof_nis_hu_uncut;              // uncut dimuon Mundof, high mass, unlike sign
  TH1D    *fGeneralMundof_nis_hl_uncut;              // uncut dimuon Mundof, high mass, like sign

  TH1D    *fGeneralMupmat_uncut  ;                   // uncut dimuon Mupmat
  TH1D    *fGeneralMupmat_is_lu_uncut;               // uncut dimuon Mupmat, low mass, unlike sign
  TH1D    *fGeneralMupmat_is_ll_uncut;               // uncut dimuon Mupmat, low mass, like sign
  TH1D    *fGeneralMupmat_is_hu_uncut;               // uncut dimuon Mupmat, high mass, unlike sign
  TH1D    *fGeneralMupmat_is_hl_uncut;               // uncut dimuon Mupmat, high mass, like sign
  TH1D    *fGeneralMupmat_nis_lu_uncut;              // uncut dimuon Mupmat, low mass, unlike sign
  TH1D    *fGeneralMupmat_nis_ll_uncut;              // uncut dimuon Mupmat, low mass, like sign
  TH1D    *fGeneralMupmat_nis_hu_uncut;              // uncut dimuon Mupmat, high mass, unlike sign
  TH1D    *fGeneralMupmat_nis_hl_uncut;              // uncut dimuon Mupmat, high mass, like sign

  TH1D    *fGeneralMPMatchID_uncut  ;                // uncut dimuon MPMatchID
  TH1D    *fGeneralMPMatchID_is_lu_uncut;            // uncut dimuon MPMatchID, low mass, unlike sign
  TH1D    *fGeneralMPMatchID_is_ll_uncut;            // uncut dimuon MPMatchID, low mass, like sign
  TH1D    *fGeneralMPMatchID_is_hu_uncut;            // uncut dimuon MPMatchID, high mass, unlike sign
  TH1D    *fGeneralMPMatchID_is_hl_uncut;            // uncut dimuon MPMatchID, high mass, like sign
  TH1D    *fGeneralMPMatchID_nis_lu_uncut;           // uncut dimuon MPMatchID, low mass, unlike sign
  TH1D    *fGeneralMPMatchID_nis_ll_uncut;           // uncut dimuon MPMatchID, low mass, like sign
  TH1D    *fGeneralMPMatchID_nis_hu_uncut;           // uncut dimuon MPMatchID, high mass, unlike sign
  TH1D    *fGeneralMPMatchID_nis_hl_uncut;           // uncut dimuon MPMatchID, high mass, like sign

  TH1D    *fGeneralMuMvID_uncut  ;                   // uncut dimuon MuMvID
  TH1D    *fGeneralMuMvID_is_lu_uncut;               // uncut dimuon MuMvID, low mass, unlike sign
  TH1D    *fGeneralMuMvID_is_ll_uncut;               // uncut dimuon MuMvID, low mass, like sign
  TH1D    *fGeneralMuMvID_is_hu_uncut;               // uncut dimuon MuMvID, high mass, unlike sign
  TH1D    *fGeneralMuMvID_is_hl_uncut;               // uncut dimuon MuMvID, high mass, like sign
  TH1D    *fGeneralMuMvID_nis_lu_uncut;              // uncut dimuon MuMvID, low mass, unlike sign
  TH1D    *fGeneralMuMvID_nis_ll_uncut;              // uncut dimuon MuMvID, low mass, like sign
  TH1D    *fGeneralMuMvID_nis_hu_uncut;              // uncut dimuon MuMvID, high mass, unlike sign
  TH1D    *fGeneralMuMvID_nis_hl_uncut;              // uncut dimuon MuMvID, high mass, like sign

  TH1D    *fGeneralMuMufoID_uncut  ;                 // uncut dimuon MuMufoID
  TH1D    *fGeneralMuMufoID_is_lu_uncut;             // uncut dimuon MuMufoID, low mass, unlike sign
  TH1D    *fGeneralMuMufoID_is_ll_uncut;             // uncut dimuon MuMufoID, low mass, like sign
  TH1D    *fGeneralMuMufoID_is_hu_uncut;             // uncut dimuon MuMufoID, high mass, unlike sign
  TH1D    *fGeneralMuMufoID_is_hl_uncut;             // uncut dimuon MuMufoID, high mass, like sign
  TH1D    *fGeneralMuMufoID_nis_lu_uncut;            // uncut dimuon MuMufoID, low mass, unlike sign
  TH1D    *fGeneralMuMufoID_nis_ll_uncut;            // uncut dimuon MuMufoID, low mass, like sign
  TH1D    *fGeneralMuMufoID_nis_hu_uncut;            // uncut dimuon MuMufoID, high mass, unlike sign
  TH1D    *fGeneralMuMufoID_nis_hl_uncut;            // uncut dimuon MuMufoID, high mass, like sign

  TH1D    *fGeneralMuBacMatID_uncut  ;               // uncut dimuon MuBacMatID
  TH1D    *fGeneralMuBacMatID_is_lu_uncut;           // uncut dimuon MuBacMatID, low mass, unlike sign
  TH1D    *fGeneralMuBacMatID_is_ll_uncut;           // uncut dimuon MuBacMatID, low mass, like sign
  TH1D    *fGeneralMuBacMatID_is_hu_uncut;           // uncut dimuon MuBacMatID, high mass, unlike sign
  TH1D    *fGeneralMuBacMatID_is_hl_uncut;           // uncut dimuon MuBacMatID, high mass, like sign
  TH1D    *fGeneralMuBacMatID_nis_lu_uncut;          // uncut dimuon MuBacMatID, low mass, unlike sign
  TH1D    *fGeneralMuBacMatID_nis_ll_uncut;          // uncut dimuon MuBacMatID, low mass, like sign
  TH1D    *fGeneralMuBacMatID_nis_hu_uncut;          // uncut dimuon MuBacMatID, high mass, unlike sign
  TH1D    *fGeneralMuBacMatID_nis_hl_uncut;          // uncut dimuon MuBacMatID, high mass, like sign

  TH1D    *fGeneralNBacMat_uncut  ;                  // uncut dimuon NBacMat
  TH1D    *fGeneralNBacMat_is_lu_uncut;              // uncut dimuon NBacMat, low mass, unlike sign
  TH1D    *fGeneralNBacMat_is_ll_uncut;              // uncut dimuon NBacMat, low mass, like sign
  TH1D    *fGeneralNBacMat_is_hu_uncut;              // uncut dimuon NBacMat, high mass, unlike sign
  TH1D    *fGeneralNBacMat_is_hl_uncut;              // uncut dimuon NBacMat, high mass, like sign
  TH1D    *fGeneralNBacMat_nis_lu_uncut;             // uncut dimuon NBacMat, low mass, unlike sign
  TH1D    *fGeneralNBacMat_nis_ll_uncut;             // uncut dimuon NBacMat, low mass, like sign
  TH1D    *fGeneralNBacMat_nis_hu_uncut;             // uncut dimuon NBacMat, high mass, unlike sign
  TH1D    *fGeneralNBacMat_nis_hl_uncut;             // uncut dimuon NBacMat, high mass, like sign

  TH1D    *fGeneralBacMat_VCID_uncut  ;              // uncut dimuon BacMat_VCID
  TH1D    *fGeneralBacMat_VCID_is_lu_uncut;          // uncut dimuon BacMat_VCID, low mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_is_ll_uncut;          // uncut dimuon BacMat_VCID, low mass, like sign
  TH1D    *fGeneralBacMat_VCID_is_hu_uncut;          // uncut dimuon BacMat_VCID, high mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_is_hl_uncut;          // uncut dimuon BacMat_VCID, high mass, like sign
  TH1D    *fGeneralBacMat_VCID_nis_lu_uncut;         // uncut dimuon BacMat_VCID, low mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_nis_ll_uncut;         // uncut dimuon BacMat_VCID, low mass, like sign
  TH1D    *fGeneralBacMat_VCID_nis_hu_uncut;         // uncut dimuon BacMat_VCID, high mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_nis_hl_uncut;         // uncut dimuon BacMat_VCID, high mass, like sign

  TH1D    *fGeneralBacMat_MuBacID_uncut  ;           // uncut dimuon BacMat_MuBacID
  TH1D    *fGeneralBacMat_MuBacID_is_lu_uncut;       // uncut dimuon BacMat_MuBacID, low mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_is_ll_uncut;       // uncut dimuon BacMat_MuBacID, low mass, like sign
  TH1D    *fGeneralBacMat_MuBacID_is_hu_uncut;       // uncut dimuon BacMat_MuBacID, high mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_is_hl_uncut;       // uncut dimuon BacMat_MuBacID, high mass, like sign
  TH1D    *fGeneralBacMat_MuBacID_nis_lu_uncut;      // uncut dimuon BacMat_MuBacID, low mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_nis_ll_uncut;      // uncut dimuon BacMat_MuBacID, low mass, like sign
  TH1D    *fGeneralBacMat_MuBacID_nis_hu_uncut;      // uncut dimuon BacMat_MuBacID, high mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_nis_hl_uncut;      // uncut dimuon BacMat_MuBacID, high mass, like sign

  TH1D    *fGeneralBacMat_Istop_uncut  ;             // uncut dimuon BacMat_Istop
  TH1D    *fGeneralBacMat_Istop_is_lu_uncut;         // uncut dimuon BacMat_Istop, low mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_is_ll_uncut;         // uncut dimuon BacMat_Istop, low mass, like sign
  TH1D    *fGeneralBacMat_Istop_is_hu_uncut;         // uncut dimuon BacMat_Istop, high mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_is_hl_uncut;         // uncut dimuon BacMat_Istop, high mass, like sign
  TH1D    *fGeneralBacMat_Istop_nis_lu_uncut;        // uncut dimuon BacMat_Istop, low mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_nis_ll_uncut;        // uncut dimuon BacMat_Istop, low mass, like sign
  TH1D    *fGeneralBacMat_Istop_nis_hu_uncut;        // uncut dimuon BacMat_Istop, high mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_nis_hl_uncut;        // uncut dimuon BacMat_Istop, high mass, like sign

  TH1D    *fGeneralBacMat_Error_uncut  ;             // uncut dimuon BacMat_Error
  TH1D    *fGeneralBacMat_Error_is_lu_uncut;         // uncut dimuon BacMat_Error, low mass, unlike sign
  TH1D    *fGeneralBacMat_Error_is_ll_uncut;         // uncut dimuon BacMat_Error, low mass, like sign
  TH1D    *fGeneralBacMat_Error_is_hu_uncut;         // uncut dimuon BacMat_Error, high mass, unlike sign
  TH1D    *fGeneralBacMat_Error_is_hl_uncut;         // uncut dimuon BacMat_Error, high mass, like sign
  TH1D    *fGeneralBacMat_Error_nis_lu_uncut;        // uncut dimuon BacMat_Error, low mass, unlike sign
  TH1D    *fGeneralBacMat_Error_nis_ll_uncut;        // uncut dimuon BacMat_Error, low mass, like sign
  TH1D    *fGeneralBacMat_Error_nis_hu_uncut;        // uncut dimuon BacMat_Error, high mass, unlike sign
  TH1D    *fGeneralBacMat_Error_nis_hl_uncut;        // uncut dimuon BacMat_Error, high mass, like sign

  TH1D    *fGeneralBacMat_Readout_uncut  ;           // uncut dimuon BacMat_Readout
  TH1D    *fGeneralBacMat_Readout_is_lu_uncut;       // uncut dimuon BacMat_Readout, low mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_is_ll_uncut;       // uncut dimuon BacMat_Readout, low mass, like sign
  TH1D    *fGeneralBacMat_Readout_is_hu_uncut;       // uncut dimuon BacMat_Readout, high mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_is_hl_uncut;       // uncut dimuon BacMat_Readout, high mass, like sign
  TH1D    *fGeneralBacMat_Readout_nis_lu_uncut;      // uncut dimuon BacMat_Readout, low mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_nis_ll_uncut;      // uncut dimuon BacMat_Readout, low mass, like sign
  TH1D    *fGeneralBacMat_Readout_nis_hu_uncut;      // uncut dimuon BacMat_Readout, high mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_nis_hl_uncut;      // uncut dimuon BacMat_Readout, high mass, like sign

  TH1D    *fGeneralImpact2D_uncut  ;                 // uncut dimuon 2D Impact Parameter
  TH1D    *fGeneralImpact2D_is_lu_uncut;             // uncut dimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_is_ll_uncut;             // uncut dimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_is_hu_uncut;             // uncut dimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_is_hl_uncut;             // uncut dimuon 2D Impact Parameter, high mass, like sign
  TH1D    *fGeneralImpact2D_nis_lu_uncut;            // uncut dimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_ll_uncut;            // uncut dimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_nis_hu_uncut;            // uncut dimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_hl_uncut;            // uncut dimuon 2D Impact Parameter, high mass, like sign

  TH1D    *fGeneralImpact2D_Sign_uncut  ;            // uncut dimuon 2D Impact Parameter Significance
  TH1D    *fGeneralImpact2D_Sign_is_lu_uncut;        // uncut dimuon 2D Impact Parameter Significance, low mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_is_ll_uncut;        // uncut dimuon 2D Impact Parameter Significance, low mass, like sign
  TH1D    *fGeneralImpact2D_Sign_is_hu_uncut;        // uncut dimuon 2D Impact Parameter Significance, high mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_is_hl_uncut;        // uncut dimuon 2D Impact Parameter Significance, high mass, like sign
  TH1D    *fGeneralImpact2D_Sign_nis_lu_uncut;       // uncut dimuon 2D Impact Parameter Significance, low mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_nis_ll_uncut;       // uncut dimuon 2D Impact Parameter Significance, low mass, like sign
  TH1D    *fGeneralImpact2D_Sign_nis_hu_uncut;       // uncut dimuon 2D Impact Parameter Significance, high mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_nis_hl_uncut;       // uncut dimuon 2D Impact Parameter Significance, high mass, like sign

  TH1D    *fGeneralDL2_uncut  ;                      // uncut dimuon Decay Length
  TH1D    *fGeneralDL2_is_lu_uncut;                  // uncut dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_is_ll_uncut;                  // uncut dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_is_hu_uncut;                  // uncut dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_is_hl_uncut;                  // uncut dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_nis_lu_uncut;                 // uncut dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_nis_ll_uncut;                 // uncut dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_nis_hu_uncut;                 // uncut dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_nis_hl_uncut;                 // uncut dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_uncut  ;                 // uncut dimuon Decay Length Significance
  TH1D    *fGeneralDL2_Sign_is_lu_uncut;             // uncut dimuon Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_is_ll_uncut;             // uncut dimuon Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_is_hu_uncut;             // uncut dimuon Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_is_hl_uncut;             // uncut dimuon Decay Length Significance, high mass, like sign
  TH1D    *fGeneralDL2_Sign_nis_lu_uncut;            // uncut dimuon Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_nis_ll_uncut;            // uncut dimuon Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_nis_hu_uncut;            // uncut dimuon Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_nis_hl_uncut;            // uncut dimuon Decay Length Significance, high mass, like sign

  TH1D    *fGeneralDL2_Sign_Mirrp_uncut  ;           // uncut dimuon mirrored Decay Length Significance
  TH1D    *fGeneralDL2_Sign_Mirrp_is_lu_uncut;       // uncut dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_is_ll_uncut;       // uncut dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrp_is_hu_uncut;       // uncut dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_is_hl_uncut;       // uncut dimuon mirrored Decay Length Significance, high mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_lu_uncut;      // uncut dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_ll_uncut;      // uncut dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_hu_uncut;      // uncut dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_hl_uncut;      // uncut dimuon mirrored Decay Length Significance, high mass, like sign

  TH1D    *fGeneralDL2_Sign_Mirrm_uncut  ;           // uncut dimuon mirrored Decay Length Significance
  TH1D    *fGeneralDL2_Sign_Mirrm_is_lu_uncut;       // uncut dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_is_ll_uncut;       // uncut dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrm_is_hu_uncut;       // uncut dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_is_hl_uncut;       // uncut dimuon mirrored Decay Length Significance, high mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_lu_uncut;      // uncut dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_ll_uncut;      // uncut dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_hu_uncut;      // uncut dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_hl_uncut;      // uncut dimuon mirrored Decay Length Significance, high mass, like sign

  TH1D    *fGeneralMuJetDeltaR_uncut  ;              // uncut dimuon DeltaR Muon-Jet
  TH1D    *fGeneralMuJetDeltaR_is_lu_uncut;          // uncut dimuon DeltaR Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_is_ll_uncut;          // uncut dimuon DeltaR Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetDeltaR_is_hu_uncut;          // uncut dimuon DeltaR Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_is_hl_uncut;          // uncut dimuon DeltaR Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetDeltaR_nis_lu_uncut;         // uncut dimuon DeltaR Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_nis_ll_uncut;         // uncut dimuon DeltaR Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetDeltaR_nis_hu_uncut;         // uncut dimuon DeltaR Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_nis_hl_uncut;         // uncut dimuon DeltaR Muon-Jet, high mass, like sign

  TH1D    *fGeneralMuJetPt_uncut  ;                  // uncut dimuon Pt Muon-Jet
  TH1D    *fGeneralMuJetPt_is_lu_uncut;              // uncut dimuon Pt Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetPt_is_ll_uncut;              // uncut dimuon Pt Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetPt_is_hu_uncut;              // uncut dimuon Pt Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetPt_is_hl_uncut;              // uncut dimuon Pt Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetPt_nis_lu_uncut;             // uncut dimuon Pt Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetPt_nis_ll_uncut;             // uncut dimuon Pt Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetPt_nis_hu_uncut;             // uncut dimuon Pt Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetPt_nis_hl_uncut;             // uncut dimuon Pt Muon-Jet, high mass, like sign

  TH1D    *fGeneralMuJetEt_uncut  ;                  // uncut dimuon Et Muon-Jet
  TH1D    *fGeneralMuJetEt_is_lu_uncut;              // uncut dimuon Et Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEt_is_ll_uncut;              // uncut dimuon Et Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEt_is_hu_uncut;              // uncut dimuon Et Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEt_is_hl_uncut;              // uncut dimuon Et Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetEt_nis_lu_uncut;             // uncut dimuon Et Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEt_nis_ll_uncut;             // uncut dimuon Et Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEt_nis_hu_uncut;             // uncut dimuon Et Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEt_nis_hl_uncut;             // uncut dimuon Et Muon-Jet, high mass, like sign

  TH1D    *fGeneralMuJetEta_uncut  ;                 // uncut dimuon Eta Muon-Jet
  TH1D    *fGeneralMuJetEta_is_lu_uncut;             // uncut dimuon Eta Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEta_is_ll_uncut;             // uncut dimuon Eta Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEta_is_hu_uncut;             // uncut dimuon Eta Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEta_is_hl_uncut;             // uncut dimuon Eta Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetEta_nis_lu_uncut;            // uncut dimuon Eta Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEta_nis_ll_uncut;            // uncut dimuon Eta Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEta_nis_hu_uncut;            // uncut dimuon Eta Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEta_nis_hl_uncut;            // uncut dimuon Eta Muon-Jet, high mass, like sign

  TH1D    *fGeneralMassJet_uncut  ;                  // uncut dimuon MassJet
  TH1D    *fGeneralMassJet_is_lu_uncut;              // uncut dimuon MassJet, low mass, unlike sign
  TH1D    *fGeneralMassJet_is_ll_uncut;              // uncut dimuon MassJet, low mass, like sign
  TH1D    *fGeneralMassJet_is_hu_uncut;              // uncut dimuon MassJet, high mass, unlike sign
  TH1D    *fGeneralMassJet_is_hl_uncut;              // uncut dimuon MassJet, high mass, like sign
  TH1D    *fGeneralMassJet_nis_lu_uncut;             // uncut dimuon MassJet, low mass, unlike sign
  TH1D    *fGeneralMassJet_nis_ll_uncut;             // uncut dimuon MassJet, low mass, like sign
  TH1D    *fGeneralMassJet_nis_hu_uncut;             // uncut dimuon MassJet, high mass, unlike sign
  TH1D    *fGeneralMassJet_nis_hl_uncut;             // uncut dimuon MassJet, high mass, like sign

  TH1D    *fGeneralNJets_uncut  ;                    // uncut dimuon NJets
  TH1D    *fGeneralNJets_is_lu_uncut;                // uncut dimuon NJets, low mass, unlike sign
  TH1D    *fGeneralNJets_is_ll_uncut;                // uncut dimuon NJets, low mass, like sign
  TH1D    *fGeneralNJets_is_hu_uncut;                // uncut dimuon NJets, high mass, unlike sign
  TH1D    *fGeneralNJets_is_hl_uncut;                // uncut dimuon NJets, high mass, like sign
  TH1D    *fGeneralNJets_nis_lu_uncut;               // uncut dimuon NJets, low mass, unlike sign
  TH1D    *fGeneralNJets_nis_ll_uncut;               // uncut dimuon NJets, low mass, like sign
  TH1D    *fGeneralNJets_nis_hu_uncut;               // uncut dimuon NJets, high mass, unlike sign
  TH1D    *fGeneralNJets_nis_hl_uncut;               // uncut dimuon NJets, high mass, like sign

  TH1D    *fGeneralsqisol_10_uncut   ;               // dimuon sqared isolation sum in DeltaR come of 1.0	      	    
  TH1D    *fGeneralsqisol_10_is_lu_uncut;            // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_ll_uncut;            // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_hu_uncut;            // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_is_hl_uncut;            // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_lu_uncut;           // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_ll_uncut;           // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_hu_uncut;           // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_hl_uncut;           // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D    *fGeneralthrust_uncut   ;                  // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_lu_uncut;               // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_ll_uncut;               // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_hu_uncut;               // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_hl_uncut;               // thrust of event, classified by muon pair    
  TH1D    *fGeneralthrust_nis_lu_uncut;              // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_ll_uncut;              // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hu_uncut;              // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hl_uncut;              // thrust of event, classified by muon pair 

  TH1D    *fGeneralsphericity_uncut  ;               // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_lu_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_ll_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hu_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hl_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_lu_uncut;          // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_ll_uncut;          // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hu_uncut;          // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hl_uncut;          // sphericity of event, classified by muon pair

  TH1D    *fGeneralisotropy_uncut  ;                 // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_lu_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_ll_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hu_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hl_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_lu_uncut;            // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_ll_uncut;            // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hu_uncut;            // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hl_uncut;            // isotropy of event, classified by muon pair
    
  TH1D    *fGeneralmultiplicity_uncut  ;             // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_lu_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_ll_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hu_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hl_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_lu_uncut;        // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_ll_uncut;        // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hu_uncut;        // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hl_uncut;        // multiplicity of event, classified by muon pair

  TH1D    *fGeneralQ2Prime_uncut  ;                  // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_lu_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_ll_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hu_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hl_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_lu_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_ll_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_hu_uncut;             // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fGeneralQ2Prime_nis_hl_uncut;             // Virtuality Q'2 of event, classified by muon pair

  TH1D    *fGeneralcal_et_uncut   ;                  // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_lu_uncut;               // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_ll_uncut;               // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_hu_uncut;               // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_hl_uncut;               // cal_et of event, classified by muon pair    
  TH1D    *fGeneralcal_et_nis_lu_uncut;              // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_ll_uncut;              // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hu_uncut;              // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hl_uncut;              // cal_et of event, classified by muon pair 

  TH1D    *fGeneraletex2ir_uncut   ;                 // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_lu_uncut;              // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_ll_uncut;              // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_hu_uncut;              // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_hl_uncut;              // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraletex2ir_nis_lu_uncut;             // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_ll_uncut;             // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hu_uncut;             // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hl_uncut;             // etex2ir of event, classified by muon pair 

  TH1D    *fGeneralcal_et_m_et2ir_uncut   ;          // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_lu_uncut;       // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_ll_uncut;       // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_hu_uncut;       // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_hl_uncut;       // cal_et_m_et2ir of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_et2ir_nis_lu_uncut;      // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_ll_uncut;      // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hu_uncut;      // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hl_uncut;      // cal_et_m_et2ir of event, classified by muon pair 

  TH1D    *fGeneralcal_et_m_cal_et_10_uncut   ;      // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_lu_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_ll_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hu_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hl_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_lu_uncut;  // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_ll_uncut;  // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hu_uncut;  // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hl_uncut;  // cal_et_m_cal_et_10 of event, classified by muon pair 

  TH1D    *fGeneralTriggerType_uncut;                // uncut trigger type

  TH1D    *fGeneralNperEv;                           // dimuon per event
  TH1D    *fGeneralDIMuonMass;                       // dimuon mass
  TH1D    *fGeneralDIMuonMassLow;                    // low dimuon mass
  TH1D    *fGeneralDIMuonMassHigh;                   // high dimuon mass
  TH1D    *fGeneralDIMuonMass_LikeSign;              // dimuon mass for like sign dimuons
  TH1D    *fGeneralDIMuonMassLow_LikeSign;           // low dimuon mass for like sign dimuons
  TH1D    *fGeneralDIMuonMassHigh_LikeSign;          // high dimuon mass for like sign dimuons
  TH1D    *fGeneralDIMuonMass_UnlikeSign;            // dimuon mass for unlike sign dimuons
  TH1D    *fGeneralDIMuonMassLow_UnlikeSign;         // low dimuon mass for unlike sign dimuons
  TH1D    *fGeneralDIMuonMassHigh_UnlikeSign;        // high dimuon mass for unlike sign dimuons

  TH1D    *fGeneralMass_lu_is ;                      // dimuon mass low like sign isolated
  TH1D    *fGeneralMass_ll_is ;                      // dimuon mass low like sign isolated
  TH1D    *fGeneralMass_hu_is ;                      // dimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_hl_is ;                      // dimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_lu_nis;                      // dimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_ll_nis;                      // dimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_hu_nis;                      // dimuon mass high unlike sign non-isolated
  TH1D    *fGeneralMass_hl_nis;                      // dimuon mass high unlike sign non-isolated 

  TH1D    *fGeneralDeltaR;                           // dimuon delta R
  TH1D    *fGeneralDeltaR_lu_is;                     // dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_is;                     // dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_is;                     // dimuon delta R high mass, like   sign 
  TH1D    *fGeneralDeltaR_hl_is;                     // dimuon delta R high mass, like   sign 
  TH1D    *fGeneralDeltaR_lu_nis;                    // dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_nis;                    // dimuon delta R low  mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_nis;                    // dimuon delta R high mass, like   sign 
  TH1D    *fGeneralDeltaR_hl_nis;                    // dimuon delta R high mass, like   sign 

  TH1D    *fGeneralDeltaPhi;                         // dimuon delta Phi
  TH1D    *fGeneralDeltaPhi_lu_is;                   // dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_is;                   // dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_is;                   // dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_is;                   // dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_lu_nis;                  // dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_nis;                  // dimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_nis;                  // dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_nis;                  // dimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaEta;                         // dimuon delta Eta
  TH1D    *fGeneralDeltaEta_lu_is;                   // dimuon delta Eta low mass, unlike sign
  TH1D    *fGeneralDeltaEta_ll_is;                   // dimuon delta Eta low mass, unlike sign
  TH1D    *fGeneralDeltaEta_hu_is;                   // dimuon delta Eta high mass, like sign 
  TH1D    *fGeneralDeltaEta_hl_is;                   // dimuon delta Eta high mass, like sign 
  TH1D    *fGeneralDeltaEta_lu_nis;                  // dimuon delta Eta low mass, unlike sign
  TH1D    *fGeneralDeltaEta_ll_nis;                  // dimuon delta Eta low mass, unlike sign
  TH1D    *fGeneralDeltaEta_hu_nis;                  // dimuon delta Eta high mass, like sign 
  TH1D    *fGeneralDeltaEta_hl_nis;                  // dimuon delta Eta high mass, like sign 
  TH1D    *fGeneralDeltaTheta;                       // dimuon delta Theta
  TH1D    *fGeneraldimuphi;                          // dimuon dimuphi
  TH1D    *fGeneraldimuphi_lu_is;                    // dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_ll_is;                    // dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_hu_is;                    // dimuon dimuphi high mass, like sign	
  TH1D    *fGeneraldimuphi_hl_is;                    // dimuon dimuphi high mass, like sign 
  TH1D    *fGeneraldimuphi_lu_nis;                   // dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_ll_nis;                   // dimuon dimuphi low mass, unlike sign
  TH1D    *fGeneraldimuphi_hu_nis;                   // dimuon dimuphi high mass, like sign	
  TH1D    *fGeneraldimuphi_hl_nis;                   // dimuon dimuphi high mass, like sign 
  TH1D    *fGeneraldimueta;                          // dimuon dimueta
  TH1D    *fGeneraldimueta_lu_is;                    // dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_ll_is;                    // dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_hu_is;                    // dimuon dimueta high mass, like sign	
  TH1D    *fGeneraldimueta_hl_is;                    // dimuon dimueta high mass, like sign 
  TH1D    *fGeneraldimueta_lu_nis;                   // dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_ll_nis;                   // dimuon dimueta low mass, unlike sign
  TH1D    *fGeneraldimueta_hu_nis;                   // dimuon dimueta high mass, like sign	
  TH1D    *fGeneraldimueta_hl_nis;                   // dimuon dimueta high mass, like sign 
  TH1D    *fGeneralPtAsymetry;                       // dimuon pt Asymetry
  TH1D    *fGeneralPtAsymetry_lu_is;                 // dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_is;                 // dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_is;                 // dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_is;                 // dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_lu_nis;                // dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_nis;                // dimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_nis;                // dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_nis;                // dimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralpt;                               // dimuon pt
  TH1D    *fGeneralpt_lu_is;                         // dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_is;                         // dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_is;                         // dimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_is;                         // dimuon pt high mass, like sign 
  TH1D    *fGeneralpt_lu_nis;                        // dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_nis;                        // dimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_nis;                        // dimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_nis;                        // dimuon pt high mass, like sign 
  TH1D    *fGeneraldimupt;                           // dimuon dimupt
  TH1D    *fGeneraldimupt_lu_is;                     // dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_ll_is;                     // dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_hu_is;                     // dimuon dimupt high mass, like sign	
  TH1D    *fGeneraldimupt_hl_is;                     // dimuon dimupt high mass, like sign 
  TH1D    *fGeneraldimupt_lu_nis;                    // dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_ll_nis;                    // dimuon dimupt low mass, unlike sign
  TH1D    *fGeneraldimupt_hu_nis;                    // dimuon dimupt high mass, like sign	
  TH1D    *fGeneraldimupt_hl_nis;                    // dimuon dimupt high mass, like sign 
  TH1D    *fGeneraleta;                              // dimuon eta
  TH1D    *fGeneraleta_lu_is;                        // dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_is;                        // dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_is;                        // dimuon eta high mass, like sign	
  TH1D    *fGeneraleta_hl_is;                        // dimuon eta high mass, like sign 
  TH1D    *fGeneraleta_lu_nis;                       // dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_nis;                       // dimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_nis;                       // dimuon eta high mass, like sign	
  TH1D    *fGeneraleta_hl_nis;                       // dimuon eta high mass, like sign 

  TH1D    *fGeneralphi;                              // dimuon phi
  TH1D    *fGeneralphi_lu_is;                        // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_is;                        // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_is;                        // single muon phi high mass, like sign	
  TH1D    *fGeneralphi_hl_is;                        // single muon phi high mass, like sign 
  TH1D    *fGeneralphi_lu_nis;                       // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_nis;                       // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_nis;                       // single muon phi high mass, like sign	
  TH1D    *fGeneralphi_hl_nis;                       // single muon phi high mass, like sign 
  TH1D    *fGeneralmuqual;                           // single muon muqual
  TH1D    *fGeneralmuqual_lu_is;                     // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_is;                     // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_is;                     // single muon muqual high mass, like sign	
  TH1D    *fGeneralmuqual_hl_is;                     // single muon muqual high mass, like sign 
  TH1D    *fGeneralmuqual_lu_nis;                    // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_nis;                    // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_nis;                    // single muon muqual high mass, like sign	
  TH1D    *fGeneralmuqual_hl_nis;                    // single muon muqual high mass, like sign 

  TH1D    *fGeneralCharge_Like;

  TH1D    *fGeneralVertexOvNTracks  ;                // dimuon VertexOvNTracks
  TH1D    *fGeneralVertexOvNTracks_is_lu;            // dimuon VertexOvNTracks, low mass, unlike sign
  TH1D    *fGeneralVertexOvNTracks_is_ll;            // dimuon VertexOvNTracks, low mass, like sign
  TH1D    *fGeneralVertexOvNTracks_is_hu;            // dimuon VertexOvNTracks, high mass, unlike sign
  TH1D    *fGeneralVertexOvNTracks_is_hl;            // dimuon VertexOvNTracks, high mass, like sign
  TH1D    *fGeneralVertexOvNTracks_nis_lu;           // dimuon VertexOvNTracks, low mass, unlike sign
  TH1D    *fGeneralVertexOvNTracks_nis_ll;           // dimuon VertexOvNTracks, low mass, like sign
  TH1D    *fGeneralVertexOvNTracks_nis_hu;           // dimuon VertexOvNTracks, high mass, unlike sign
  TH1D    *fGeneralVertexOvNTracks_nis_hl;           // dimuon VertexOvNTracks, high mass, like sign

  TH1D    *fGeneralVtxMass  ;                        // dimuon VtxMass
  TH1D    *fGeneralVtxMass_is_lu;                    // dimuon VtxMass, low mass, unlike sign
  TH1D    *fGeneralVtxMass_is_ll;                    // dimuon VtxMass, low mass, like sign
  TH1D    *fGeneralVtxMass_is_hu;                    // dimuon VtxMass, high mass, unlike sign
  TH1D    *fGeneralVtxMass_is_hl;                    // dimuon VtxMass, high mass, like sign
  TH1D    *fGeneralVtxMass_nis_lu;                   // dimuon VtxMass, low mass, unlike sign
  TH1D    *fGeneralVtxMass_nis_ll;                   // dimuon VtxMass, low mass, like sign
  TH1D    *fGeneralVtxMass_nis_hu;                   // dimuon VtxMass, high mass, unlike sign
  TH1D    *fGeneralVtxMass_nis_hl;                   // dimuon VtxMass, high mass, like sign

  TH1D    *fGeneralChi2;                             // dimuon Chi2
  TH1D    *fGeneralChi2_is_lu;                       // dimuon Chi2, low mass, unlike sign
  TH1D    *fGeneralChi2_is_ll;                       // dimuon Chi2, low mass, like sign
  TH1D    *fGeneralChi2_is_hu;                       // dimuon Chi2, high mass, unlike sign
  TH1D    *fGeneralChi2_is_hl;                       // dimuon Chi2, high mass, like sign
  TH1D    *fGeneralChi2_nis_lu;                      // dimuon Chi2, low mass, unlike sign
  TH1D    *fGeneralChi2_nis_ll;                      // dimuon Chi2, low mass, like sign
  TH1D    *fGeneralChi2_nis_hu;                      // dimuon Chi2, high mass, unlike sign
  TH1D    *fGeneralChi2_nis_hl;                      // dimuon Chi2, high mass, like sign
 
  TH1D    *fGeneralNdof;                             // dimuon Ndof
  TH1D    *fGeneralNdof_is_lu;                       // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneralNdof_is_ll;                       // dimuon Ndof, low mass, like sign
  TH1D    *fGeneralNdof_is_hu;                       // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneralNdof_is_hl;                       // dimuon Ndof, high mass, like sign
  TH1D    *fGeneralNdof_nis_lu;                      // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneralNdof_nis_ll;                      // dimuon Ndof, low mass, like sign
  TH1D    *fGeneralNdof_nis_hu;                      // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneralNdof_nis_hl;                      // dimuon Ndof, high mass, like sign

  TH1D    *fGeneralChi2Ndof;                         // dimuon Ndof
  TH1D    *fGeneralChi2Ndof_is_lu;                   // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_is_ll;                   // dimuon Ndof, low mass, like sign
  TH1D    *fGeneralChi2Ndof_is_hu;                   // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_is_hl;                   // dimuon Ndof, high mass, like sign
  TH1D    *fGeneralChi2Ndof_nis_lu;                  // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_nis_ll;                  // dimuon Ndof, low mass, like sign
  TH1D    *fGeneralChi2Ndof_nis_hu;                  // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_nis_hl;                  // dimuon Ndof, high mass, like sign

  TH1D    *fGeneralMulti;                            // dimuon Multi
  TH1D    *fGeneralMulti_is_lu;                      // dimuon Multi, low mass, unlike sign
  TH1D    *fGeneralMulti_is_ll;                      // dimuon Multi, low mass, like sign
  TH1D    *fGeneralMulti_is_hu;                      // dimuon Multi, high mass, unlike sign
  TH1D    *fGeneralMulti_is_hl;                      // dimuon Multi, high mass, like sign
  TH1D    *fGeneralMulti_nis_lu;                     // dimuon Multi, low mass, unlike sign
  TH1D    *fGeneralMulti_nis_ll;                     // dimuon Multi, low mass, like sign
  TH1D    *fGeneralMulti_nis_hu;                     // dimuon Multi, high mass, unlike sign
  TH1D    *fGeneralMulti_nis_hl;                     // dimuon Multi, high mass, like sign

  TH1D    *fGeneral_mvtx2_VtxMass  ;                 // dimuon VtxMass
  TH1D    *fGeneral_mvtx2_VtxMass_is_lu;             // dimuon VtxMass, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_VtxMass_is_ll;             // dimuon VtxMass, low mass, like sign
  TH1D    *fGeneral_mvtx2_VtxMass_is_hu;             // dimuon VtxMass, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_VtxMass_is_hl;             // dimuon VtxMass, high mass, like sign
  TH1D    *fGeneral_mvtx2_VtxMass_nis_lu;            // dimuon VtxMass, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_VtxMass_nis_ll;            // dimuon VtxMass, low mass, like sign
  TH1D    *fGeneral_mvtx2_VtxMass_nis_hu;            // dimuon VtxMass, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_VtxMass_nis_hl;            // dimuon VtxMass, high mass, like sign

  TH1D    *fGeneral_mvtx2_Chi2;                      // dimuon Chi2
  TH1D    *fGeneral_mvtx2_Chi2_is_lu;                // dimuon Chi2, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2_is_ll;                // dimuon Chi2, low mass, like sign
  TH1D    *fGeneral_mvtx2_Chi2_is_hu;                // dimuon Chi2, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2_is_hl;                // dimuon Chi2, high mass, like sign
  TH1D    *fGeneral_mvtx2_Chi2_nis_lu;               // dimuon Chi2, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2_nis_ll;               // dimuon Chi2, low mass, like sign
  TH1D    *fGeneral_mvtx2_Chi2_nis_hu;               // dimuon Chi2, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2_nis_hl;               // dimuon Chi2, high mass, like sign
 
  TH1D    *fGeneral_mvtx2_Ndof;                      // dimuon Ndof
  TH1D    *fGeneral_mvtx2_Ndof_is_lu;                // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Ndof_is_ll;                // dimuon Ndof, low mass, like sign
  TH1D    *fGeneral_mvtx2_Ndof_is_hu;                // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Ndof_is_hl;                // dimuon Ndof, high mass, like sign
  TH1D    *fGeneral_mvtx2_Ndof_nis_lu;               // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Ndof_nis_ll;               // dimuon Ndof, low mass, like sign
  TH1D    *fGeneral_mvtx2_Ndof_nis_hu;               // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Ndof_nis_hl;               // dimuon Ndof, high mass, like sign

  TH1D    *fGeneral_mvtx2_Chi2Ndof;                  // dimuon Ndof
  TH1D    *fGeneral_mvtx2_Chi2Ndof_is_lu;            // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_is_ll;            // dimuon Ndof, low mass, like sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_is_hu;            // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_is_hl;            // dimuon Ndof, high mass, like sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_nis_lu;           // dimuon Ndof, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_nis_ll;           // dimuon Ndof, low mass, like sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_nis_hu;           // dimuon Ndof, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Chi2Ndof_nis_hl;           // dimuon Ndof, high mass, like sign

  TH1D    *fGeneral_mvtx2_Multi;                     // dimuon Multi
  TH1D    *fGeneral_mvtx2_Multi_is_lu;               // dimuon Multi, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Multi_is_ll;               // dimuon Multi, low mass, like sign
  TH1D    *fGeneral_mvtx2_Multi_is_hu;               // dimuon Multi, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Multi_is_hl;               // dimuon Multi, high mass, like sign
  TH1D    *fGeneral_mvtx2_Multi_nis_lu;              // dimuon Multi, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_Multi_nis_ll;              // dimuon Multi, low mass, like sign
  TH1D    *fGeneral_mvtx2_Multi_nis_hu;              // dimuon Multi, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_Multi_nis_hl;              // dimuon Multi, high mass, like sign

  TH1D    *fGeneralNrsecvtx;                         // dimuon Nrsecvtx
  TH1D    *fGeneralNrsecvtx_is_lu;                   // dimuon Nrsecvtx, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_is_ll;                   // dimuon Nrsecvtx, low mass, like sign
  TH1D    *fGeneralNrsecvtx_is_hu;                   // dimuon Nrsecvtx, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_is_hl;                   // dimuon Nrsecvtx, high mass, like sign
  TH1D    *fGeneralNrsecvtx_nis_lu;                  // dimuon Nrsecvtx, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_nis_ll;                  // dimuon Nrsecvtx, low mass, like sign
  TH1D    *fGeneralNrsecvtx_nis_hu;                  // dimuon Nrsecvtx, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_nis_hl;                  // dimuon Nrsecvtx, high mass, like sign

  TH1D    *fGeneralMunphi  ;                         // dimuon Munphi
  TH1D    *fGeneralMunphi_is_lu;                     // dimuon Munphi, low mass, unlike sign
  TH1D    *fGeneralMunphi_is_ll;                     // dimuon Munphi, low mass, like sign
  TH1D    *fGeneralMunphi_is_hu;                     // dimuon Munphi, high mass, unlike sign
  TH1D    *fGeneralMunphi_is_hl;                     // dimuon Munphi, high mass, like sign
  TH1D    *fGeneralMunphi_nis_lu;                    // dimuon Munphi, low mass, unlike sign
  TH1D    *fGeneralMunphi_nis_ll;                    // dimuon Munphi, low mass, like sign
  TH1D    *fGeneralMunphi_nis_hu;                    // dimuon Munphi, high mass, unlike sign
  TH1D    *fGeneralMunphi_nis_hl;                    // dimuon Munphi, high mass, like sign

  TH1D    *fGeneralMuz  ;                            // dimuon Muz
  TH1D    *fGeneralMuz_is_lu;                        // dimuon Muz, low mass, unlike sign
  TH1D    *fGeneralMuz_is_ll;                        // dimuon Muz, low mass, like sign
  TH1D    *fGeneralMuz_is_hu;                        // dimuon Muz, high mass, unlike sign
  TH1D    *fGeneralMuz_is_hl;                        // dimuon Muz, high mass, like sign
  TH1D    *fGeneralMuz_nis_lu;                       // dimuon Muz, low mass, unlike sign
  TH1D    *fGeneralMuz_nis_ll;                       // dimuon Muz, low mass, like sign
  TH1D    *fGeneralMuz_nis_hu;                       // dimuon Muz, high mass, unlike sign
  TH1D    *fGeneralMuz_nis_hl;                       // dimuon Muz, high mass, like sign

  TH1D    *fGeneralMundof  ;                         // dimuon Mundof
  TH1D    *fGeneralMundof_is_lu;                     // dimuon Mundof, low mass, unlike sign
  TH1D    *fGeneralMundof_is_ll;                     // dimuon Mundof, low mass, like sign
  TH1D    *fGeneralMundof_is_hu;                     // dimuon Mundof, high mass, unlike sign
  TH1D    *fGeneralMundof_is_hl;                     // dimuon Mundof, high mass, like sign
  TH1D    *fGeneralMundof_nis_lu;                    // dimuon Mundof, low mass, unlike sign
  TH1D    *fGeneralMundof_nis_ll;                    // dimuon Mundof, low mass, like sign
  TH1D    *fGeneralMundof_nis_hu;                    // dimuon Mundof, high mass, unlike sign
  TH1D    *fGeneralMundof_nis_hl;                    // dimuon Mundof, high mass, like sign

  TH1D    *fGeneralMupmat  ;                         // dimuon Mupmat
  TH1D    *fGeneralMupmat_is_lu;                     // dimuon Mupmat, low mass, unlike sign
  TH1D    *fGeneralMupmat_is_ll;                     // dimuon Mupmat, low mass, like sign
  TH1D    *fGeneralMupmat_is_hu;                     // dimuon Mupmat, high mass, unlike sign
  TH1D    *fGeneralMupmat_is_hl;                     // dimuon Mupmat, high mass, like sign
  TH1D    *fGeneralMupmat_nis_lu;                    // dimuon Mupmat, low mass, unlike sign
  TH1D    *fGeneralMupmat_nis_ll;                    // dimuon Mupmat, low mass, like sign
  TH1D    *fGeneralMupmat_nis_hu;                    // dimuon Mupmat, high mass, unlike sign
  TH1D    *fGeneralMupmat_nis_hl;                    // dimuon Mupmat, high mass, like sign

  TH1D    *fGeneralMPMatchID  ;                      // dimuon MPMatchID
  TH1D    *fGeneralMPMatchID_is_lu;                  // dimuon MPMatchID, low mass, unlike sign
  TH1D    *fGeneralMPMatchID_is_ll;                  // dimuon MPMatchID, low mass, like sign
  TH1D    *fGeneralMPMatchID_is_hu;                  // dimuon MPMatchID, high mass, unlike sign
  TH1D    *fGeneralMPMatchID_is_hl;                  // dimuon MPMatchID, high mass, like sign
  TH1D    *fGeneralMPMatchID_nis_lu;                 // dimuon MPMatchID, low mass, unlike sign
  TH1D    *fGeneralMPMatchID_nis_ll;                 // dimuon MPMatchID, low mass, like sign
  TH1D    *fGeneralMPMatchID_nis_hu;                 // dimuon MPMatchID, high mass, unlike sign
  TH1D    *fGeneralMPMatchID_nis_hl;                 // dimuon MPMatchID, high mass, like sign

  TH1D    *fGeneralMuMvID  ;                         // dimuon MuMvID
  TH1D    *fGeneralMuMvID_is_lu;                     // dimuon MuMvID, low mass, unlike sign
  TH1D    *fGeneralMuMvID_is_ll;                     // dimuon MuMvID, low mass, like sign
  TH1D    *fGeneralMuMvID_is_hu;                     // dimuon MuMvID, high mass, unlike sign
  TH1D    *fGeneralMuMvID_is_hl;                     // dimuon MuMvID, high mass, like sign
  TH1D    *fGeneralMuMvID_nis_lu;                    // dimuon MuMvID, low mass, unlike sign
  TH1D    *fGeneralMuMvID_nis_ll;                    // dimuon MuMvID, low mass, like sign
  TH1D    *fGeneralMuMvID_nis_hu;                    // dimuon MuMvID, high mass, unlike sign
  TH1D    *fGeneralMuMvID_nis_hl;                    // dimuon MuMvID, high mass, like sign

  TH1D    *fGeneralMuMufoID  ;                       // dimuon MuMufoID
  TH1D    *fGeneralMuMufoID_is_lu;                   // dimuon MuMufoID, low mass, unlike sign
  TH1D    *fGeneralMuMufoID_is_ll;                   // dimuon MuMufoID, low mass, like sign
  TH1D    *fGeneralMuMufoID_is_hu;                   // dimuon MuMufoID, high mass, unlike sign
  TH1D    *fGeneralMuMufoID_is_hl;                   // dimuon MuMufoID, high mass, like sign
  TH1D    *fGeneralMuMufoID_nis_lu;                  // dimuon MuMufoID, low mass, unlike sign
  TH1D    *fGeneralMuMufoID_nis_ll;                  // dimuon MuMufoID, low mass, like sign
  TH1D    *fGeneralMuMufoID_nis_hu;                  // dimuon MuMufoID, high mass, unlike sign
  TH1D    *fGeneralMuMufoID_nis_hl;                  // dimuon MuMufoID, high mass, like sign

  TH1D    *fGeneralMuBacMatID  ;                     // dimuon MuBacMatID
  TH1D    *fGeneralMuBacMatID_is_lu;                 // dimuon MuBacMatID, low mass, unlike sign
  TH1D    *fGeneralMuBacMatID_is_ll;                 // dimuon MuBacMatID, low mass, like sign
  TH1D    *fGeneralMuBacMatID_is_hu;                 // dimuon MuBacMatID, high mass, unlike sign
  TH1D    *fGeneralMuBacMatID_is_hl;                 // dimuon MuBacMatID, high mass, like sign
  TH1D    *fGeneralMuBacMatID_nis_lu;                // dimuon MuBacMatID, low mass, unlike sign
  TH1D    *fGeneralMuBacMatID_nis_ll;                // dimuon MuBacMatID, low mass, like sign
  TH1D    *fGeneralMuBacMatID_nis_hu;                // dimuon MuBacMatID, high mass, unlike sign
  TH1D    *fGeneralMuBacMatID_nis_hl;                // dimuon MuBacMatID, high mass, like sign

  TH1D    *fGeneralNBacMat  ;                        // dimuon NBacMat
  TH1D    *fGeneralNBacMat_is_lu;                    // dimuon NBacMat, low mass, unlike sign
  TH1D    *fGeneralNBacMat_is_ll;                    // dimuon NBacMat, low mass, like sign
  TH1D    *fGeneralNBacMat_is_hu;                    // dimuon NBacMat, high mass, unlike sign
  TH1D    *fGeneralNBacMat_is_hl;                    // dimuon NBacMat, high mass, like sign
  TH1D    *fGeneralNBacMat_nis_lu;                   // dimuon NBacMat, low mass, unlike sign
  TH1D    *fGeneralNBacMat_nis_ll;                   // dimuon NBacMat, low mass, like sign
  TH1D    *fGeneralNBacMat_nis_hu;                   // dimuon NBacMat, high mass, unlike sign
  TH1D    *fGeneralNBacMat_nis_hl;                   // dimuon NBacMat, high mass, like sign

  TH1D    *fGeneralBacMat_VCID  ;                    // dimuon BacMat_VCID
  TH1D    *fGeneralBacMat_VCID_is_lu;                // dimuon BacMat_VCID, low mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_is_ll;                // dimuon BacMat_VCID, low mass, like sign
  TH1D    *fGeneralBacMat_VCID_is_hu;                // dimuon BacMat_VCID, high mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_is_hl;                // dimuon BacMat_VCID, high mass, like sign
  TH1D    *fGeneralBacMat_VCID_nis_lu;               // dimuon BacMat_VCID, low mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_nis_ll;               // dimuon BacMat_VCID, low mass, like sign
  TH1D    *fGeneralBacMat_VCID_nis_hu;               // dimuon BacMat_VCID, high mass, unlike sign
  TH1D    *fGeneralBacMat_VCID_nis_hl;               // dimuon BacMat_VCID, high mass, like sign

  TH1D    *fGeneralBacMat_MuBacID  ;                 // dimuon BacMat_MuBacID
  TH1D    *fGeneralBacMat_MuBacID_is_lu;             // dimuon BacMat_MuBacID, low mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_is_ll;             // dimuon BacMat_MuBacID, low mass, like sign
  TH1D    *fGeneralBacMat_MuBacID_is_hu;             // dimuon BacMat_MuBacID, high mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_is_hl;             // dimuon BacMat_MuBacID, high mass, like sign
  TH1D    *fGeneralBacMat_MuBacID_nis_lu;            // dimuon BacMat_MuBacID, low mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_nis_ll;            // dimuon BacMat_MuBacID, low mass, like sign
  TH1D    *fGeneralBacMat_MuBacID_nis_hu;            // dimuon BacMat_MuBacID, high mass, unlike sign
  TH1D    *fGeneralBacMat_MuBacID_nis_hl;            // dimuon BacMat_MuBacID, high mass, like sign

  TH1D    *fGeneralBacMat_Istop  ;                   // dimuon BacMat_Istop
  TH1D    *fGeneralBacMat_Istop_is_lu;               // dimuon BacMat_Istop, low mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_is_ll;               // dimuon BacMat_Istop, low mass, like sign
  TH1D    *fGeneralBacMat_Istop_is_hu;               // dimuon BacMat_Istop, high mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_is_hl;               // dimuon BacMat_Istop, high mass, like sign
  TH1D    *fGeneralBacMat_Istop_nis_lu;              // dimuon BacMat_Istop, low mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_nis_ll;              // dimuon BacMat_Istop, low mass, like sign
  TH1D    *fGeneralBacMat_Istop_nis_hu;              // dimuon BacMat_Istop, high mass, unlike sign
  TH1D    *fGeneralBacMat_Istop_nis_hl;              // dimuon BacMat_Istop, high mass, like sign

  TH1D    *fGeneralBacMat_Error  ;                   // dimuon BacMat_Error
  TH1D    *fGeneralBacMat_Error_is_lu;               // dimuon BacMat_Error, low mass, unlike sign
  TH1D    *fGeneralBacMat_Error_is_ll;               // dimuon BacMat_Error, low mass, like sign
  TH1D    *fGeneralBacMat_Error_is_hu;               // dimuon BacMat_Error, high mass, unlike sign
  TH1D    *fGeneralBacMat_Error_is_hl;               // dimuon BacMat_Error, high mass, like sign
  TH1D    *fGeneralBacMat_Error_nis_lu;              // dimuon BacMat_Error, low mass, unlike sign
  TH1D    *fGeneralBacMat_Error_nis_ll;              // dimuon BacMat_Error, low mass, like sign
  TH1D    *fGeneralBacMat_Error_nis_hu;              // dimuon BacMat_Error, high mass, unlike sign
  TH1D    *fGeneralBacMat_Error_nis_hl;              // dimuon BacMat_Error, high mass, like sign

  TH1D    *fGeneralBacMat_Readout  ;                 // dimuon BacMat_Readout
  TH1D    *fGeneralBacMat_Readout_is_lu;             // dimuon BacMat_Readout, low mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_is_ll;             // dimuon BacMat_Readout, low mass, like sign
  TH1D    *fGeneralBacMat_Readout_is_hu;             // dimuon BacMat_Readout, high mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_is_hl;             // dimuon BacMat_Readout, high mass, like sign
  TH1D    *fGeneralBacMat_Readout_nis_lu;            // dimuon BacMat_Readout, low mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_nis_ll;            // dimuon BacMat_Readout, low mass, like sign
  TH1D    *fGeneralBacMat_Readout_nis_hu;            // dimuon BacMat_Readout, high mass, unlike sign
  TH1D    *fGeneralBacMat_Readout_nis_hl;            // dimuon BacMat_Readout, high mass, like sign

  TH1D    *fGeneralImpact2D  ;                       // dimuon 2D Impact Parameter
  TH1D    *fGeneralImpact2D_is_lu;                   // dimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_is_ll;                   // dimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_is_hu;                   // dimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_is_hl;                   // dimuon 2D Impact Parameter, high mass, like sign
  TH1D    *fGeneralImpact2D_nis_lu;                  // dimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_ll;                  // dimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_nis_hu;                  // dimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_hl;                  // dimuon 2D Impact Parameter, high mass, like sign

  TH1D    *fGeneralImpact2D_Sign;                    // dimuon 2D Impact Parameter Significance
  TH1D    *fGeneralImpact2D_Sign_is_lu;              // dimuon 2D Impact Parameter Significance, low mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_is_ll;              // dimuon 2D Impact Parameter Significance, low mass, like sign
  TH1D    *fGeneralImpact2D_Sign_is_hu;              // dimuon 2D Impact Parameter Significance, high mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_is_hl;              // dimuon 2D Impact Parameter Significance, high mass, like sign
  TH1D    *fGeneralImpact2D_Sign_nis_lu;             // dimuon 2D Impact Parameter Significance, low mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_nis_ll;             // dimuon 2D Impact Parameter Significance, low mass, like sign
  TH1D    *fGeneralImpact2D_Sign_nis_hu;             // dimuon 2D Impact Parameter Significance, high mass, unlike sign
  TH1D    *fGeneralImpact2D_Sign_nis_hl;             // dimuon 2D Impact Parameter Significance, high mass, like sign

  TH1D    *fGeneralDL2;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_nis_hl;                       // dimuon Decay Length, high mass, like sign

/// Add new histos

  TH1D    *fGeneralDL2_mvtx1;
  TH1D    *fGeneralDL2_mvtx2;
  TH1D    *fGeneralDL2_mvtx3;
  TH1D    *fGeneralDL2_mvtx4;
  TH1D    *fGeneralDL2_mvtx5;
  TH1D    *fGeneralDL2_mvtx6;
  TH1D    *fGeneralDL2_mvtx7;
  TH1D    *fGeneralDL2_mvtx8;

  TH1D    *fGeneralDL2_mvtx1_is_lu;
  TH1D    *fGeneralDL2_mvtx2_is_lu;
  TH1D    *fGeneralDL2_mvtx3_is_lu;
  TH1D    *fGeneralDL2_mvtx4_is_lu;
  TH1D    *fGeneralDL2_mvtx5_is_lu;
  TH1D    *fGeneralDL2_mvtx6_is_lu;
  TH1D    *fGeneralDL2_mvtx7_is_lu;
  TH1D    *fGeneralDL2_mvtx8_is_lu;

  TH1D    *fGeneralDL2_mvtx1_is_ll;
  TH1D    *fGeneralDL2_mvtx2_is_ll;
  TH1D    *fGeneralDL2_mvtx3_is_ll;
  TH1D    *fGeneralDL2_mvtx4_is_ll;
  TH1D    *fGeneralDL2_mvtx5_is_ll;
  TH1D    *fGeneralDL2_mvtx6_is_ll;
  TH1D    *fGeneralDL2_mvtx7_is_ll;
  TH1D    *fGeneralDL2_mvtx8_is_ll;

  TH1D    *fGeneralDL2_mvtx1_is_hu;
  TH1D    *fGeneralDL2_mvtx2_is_hu;
  TH1D    *fGeneralDL2_mvtx3_is_hu;
  TH1D    *fGeneralDL2_mvtx4_is_hu;
  TH1D    *fGeneralDL2_mvtx5_is_hu;
  TH1D    *fGeneralDL2_mvtx6_is_hu;
  TH1D    *fGeneralDL2_mvtx7_is_hu;
  TH1D    *fGeneralDL2_mvtx8_is_hu;

  TH1D    *fGeneralDL2_mvtx1_is_hl;
  TH1D    *fGeneralDL2_mvtx2_is_hl;
  TH1D    *fGeneralDL2_mvtx3_is_hl;
  TH1D    *fGeneralDL2_mvtx4_is_hl;
  TH1D    *fGeneralDL2_mvtx5_is_hl;
  TH1D    *fGeneralDL2_mvtx6_is_hl;
  TH1D    *fGeneralDL2_mvtx7_is_hl;
  TH1D    *fGeneralDL2_mvtx8_is_hl;

  TH1D    *fGeneralDL2_mvtx1_nis_lu;
  TH1D    *fGeneralDL2_mvtx2_nis_lu;
  TH1D    *fGeneralDL2_mvtx3_nis_lu;
  TH1D    *fGeneralDL2_mvtx4_nis_lu;
  TH1D    *fGeneralDL2_mvtx5_nis_lu;
  TH1D    *fGeneralDL2_mvtx6_nis_lu;
  TH1D    *fGeneralDL2_mvtx7_nis_lu;
  TH1D    *fGeneralDL2_mvtx8_nis_lu;

  TH1D    *fGeneralDL2_mvtx1_nis_ll;
  TH1D    *fGeneralDL2_mvtx2_nis_ll;
  TH1D    *fGeneralDL2_mvtx3_nis_ll;
  TH1D    *fGeneralDL2_mvtx4_nis_ll;
  TH1D    *fGeneralDL2_mvtx5_nis_ll;
  TH1D    *fGeneralDL2_mvtx6_nis_ll;
  TH1D    *fGeneralDL2_mvtx7_nis_ll;
  TH1D    *fGeneralDL2_mvtx8_nis_ll;

  TH1D    *fGeneralDL2_mvtx1_nis_hu;
  TH1D    *fGeneralDL2_mvtx2_nis_hu;
  TH1D    *fGeneralDL2_mvtx3_nis_hu;
  TH1D    *fGeneralDL2_mvtx4_nis_hu;
  TH1D    *fGeneralDL2_mvtx5_nis_hu;
  TH1D    *fGeneralDL2_mvtx6_nis_hu;
  TH1D    *fGeneralDL2_mvtx7_nis_hu;
  TH1D    *fGeneralDL2_mvtx8_nis_hu;

  TH1D    *fGeneralDL2_mvtx1_nis_hl;
  TH1D    *fGeneralDL2_mvtx2_nis_hl;
  TH1D    *fGeneralDL2_mvtx3_nis_hl;
  TH1D    *fGeneralDL2_mvtx4_nis_hl;
  TH1D    *fGeneralDL2_mvtx5_nis_hl;
  TH1D    *fGeneralDL2_mvtx6_nis_hl;
  TH1D    *fGeneralDL2_mvtx7_nis_hl;
  TH1D    *fGeneralDL2_mvtx8_nis_hl;


///
  TH1D    *fGeneralDL2_1;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_1_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_1_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_1_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_1_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_1_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_1_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_1_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_1_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_2;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_2_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_3;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_3_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_3_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_3_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_3_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_3_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_3_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_3_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_3_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_4;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_4_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_4_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_4_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_4_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_4_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_4_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_4_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_4_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_5;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_5_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_5_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_5_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_5_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_5_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_5_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_5_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_5_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_6;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_6_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_6_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_6_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_6_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_6_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_6_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_6_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_6_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_7;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_7_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_7_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_7_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_7_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_7_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_7_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_7_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_7_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_8;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_8_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_8_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_8_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_8_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_8_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_8_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_8_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_8_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_9;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_9_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_9_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_9_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_9_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_9_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_9_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_9_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_9_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_10;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_10_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_10_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_10_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_10_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_10_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_10_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_10_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_10_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_11;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_11_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_11_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_11_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_11_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_11_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_11_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_11_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_11_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_12;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_12_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_12_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_12_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_12_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_12_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_12_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_12_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_12_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_13;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_13_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_13_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_13_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_13_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_13_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_13_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_13_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_13_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_14;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_14_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_14_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_14_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_14_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_14_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_14_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_14_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_14_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_15;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_15_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_15_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_15_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_15_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_15_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_15_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_15_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_15_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralDL2_16;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_16_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_16_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_16_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_16_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_16_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_16_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_16_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_16_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_17;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_17_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_17_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_17_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_17_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_17_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_17_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_17_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_17_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_18;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_18_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_18_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_18_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_18_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_18_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_18_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_18_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_18_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_19;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_19_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_19_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_19_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_19_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_19_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_19_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_19_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_19_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_20;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_20_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_20_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_20_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_20_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_20_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_20_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_20_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_20_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_21;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_21_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_21_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_21_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_21_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_21_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_21_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_21_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_21_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_22;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_22_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_22_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_22_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_22_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_22_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_22_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_22_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_22_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_23;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_23_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_23_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_23_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_23_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_23_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_23_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_23_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_23_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_24;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_24_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_24_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_24_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_24_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_24_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_24_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_24_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_24_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_121;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_121_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_121_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_121_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_121_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_121_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_121_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_121_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_121_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_141;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_141_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_141_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_141_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_141_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_141_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_141_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_141_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_141_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_171;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_171_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_171_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_171_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_171_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_171_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_171_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_171_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_171_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_191;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_191_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_191_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_191_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_191_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_191_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_191_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_191_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_191_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_231;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_231_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_231_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_231_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_231_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_231_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_231_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_231_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_231_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_25;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_25_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_25_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_25_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_25_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_25_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_25_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_25_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_25_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_251;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_251_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_251_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_251_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_251_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_251_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_251_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_251_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_251_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_26;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_26_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_26_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_26_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_26_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_26_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_26_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_26_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_26_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_27;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_27_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_27_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_27_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_27_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_27_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_27_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_27_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_27_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_28;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_28_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_28_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_28_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_28_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_28_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_28_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_28_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_28_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_29;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_29_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_29_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_29_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_29_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_29_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_29_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_29_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_29_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_281;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_281_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_281_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_281_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_281_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_281_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_281_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_281_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_281_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_30;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_30_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_30_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_30_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_30_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_30_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_30_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_30_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_30_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_301;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_301_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_301_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_301_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_301_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_301_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_301_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_301_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_301_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_31;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_31_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_31_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_31_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_31_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_31_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_31_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_31_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_31_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_32;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_32_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_32_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_32_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_32_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_32_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_32_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_32_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_32_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_122;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_122_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_122_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_122_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_122_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_122_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_122_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_122_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_122_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_142;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_142_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_142_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_142_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_142_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_142_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_142_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_142_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_142_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_172;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_172_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_172_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_172_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_172_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_172_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_172_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_172_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_172_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_192;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_192_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_192_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_192_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_192_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_192_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_192_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_192_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_192_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_232;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_232_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_232_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_232_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_232_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_232_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_232_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_232_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_232_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_252;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_252_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_252_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_252_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_252_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_252_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_252_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_252_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_252_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_282;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_282_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_282_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_282_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_282_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_282_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_282_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_282_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_282_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_302;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_302_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_302_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_302_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_302_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_302_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_302_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_302_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_302_nis_hl;                       // dimuon Decay Length, high mass, like sign



/// for Vtxmass
  TH1D    *fGeneralVtxMass_1;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_1_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_1_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_1_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_1_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_1_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_1_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_1_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_1_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_2;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_2_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_3;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_3_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_3_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_3_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_3_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_3_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_3_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_3_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_3_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_4;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_4_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_4_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_4_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_4_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_4_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_4_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_4_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_4_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_5;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_5_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_5_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_5_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_5_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_5_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_5_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_5_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_5_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_6;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_6_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_6_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_6_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_6_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_6_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_6_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_6_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_6_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_7;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_7_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_7_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_7_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_7_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_7_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_7_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_7_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_7_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_8;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_8_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_8_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_8_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_8_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_8_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_8_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_8_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_8_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_9;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_9_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_9_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_9_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_9_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_9_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_9_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_9_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_9_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_10;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_10_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_10_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_10_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_10_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_10_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_10_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_10_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_10_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_11;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_11_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_11_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_11_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_11_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_11_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_11_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_11_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_11_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_12;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_12_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_12_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_12_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_12_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_12_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_12_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_12_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_12_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_13;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_13_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_13_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_13_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_13_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_13_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_13_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_13_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_13_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_14;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_14_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_14_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_14_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_14_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_14_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_14_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_14_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_14_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_15;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_15_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_15_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_15_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_15_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_15_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_15_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_15_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_15_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralVtxMass_16;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_16_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_16_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_16_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_16_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_16_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_16_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_16_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_16_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_17;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_17_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_17_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_17_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_17_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_17_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_17_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_17_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_17_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_18;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_18_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_18_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_18_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_18_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_18_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_18_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_18_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_18_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_19;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_19_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_19_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_19_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_19_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_19_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_19_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_19_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_19_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_20;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_20_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_20_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_20_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_20_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_20_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_20_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_20_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_20_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_21;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_21_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_21_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_21_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_21_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_21_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_21_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_21_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_21_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_22;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_22_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_22_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_22_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_22_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_22_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_22_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_22_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_22_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_23;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_23_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_23_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_23_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_23_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_23_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_23_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_23_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_23_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_24;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_24_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_24_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_24_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_24_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_24_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_24_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_24_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_24_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_121;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_121_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_121_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_121_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_121_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_121_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_121_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_121_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_121_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_141;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_141_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_141_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_141_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_141_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_141_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_141_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_141_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_141_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_171;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_171_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_171_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_171_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_171_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_171_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_171_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_171_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_171_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_191;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_191_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_191_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_191_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_191_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_191_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_191_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_191_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_191_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_231;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_231_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_231_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_231_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_231_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_231_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_231_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_231_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_231_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_25;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_25_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_25_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_25_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_25_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_25_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_25_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_25_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_25_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_251;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_251_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_251_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_251_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_251_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_251_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_251_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_251_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_251_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_26;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_26_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_26_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_26_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_26_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_26_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_26_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_26_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_26_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_27;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_27_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_27_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_27_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_27_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_27_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_27_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_27_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_27_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_28;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_28_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_28_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_28_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_28_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_28_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_28_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_28_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_28_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_29;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_29_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_29_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_29_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_29_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_29_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_29_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_29_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_29_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_281;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_281_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_281_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_281_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_281_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_281_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_281_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_281_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_281_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_30;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_30_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_30_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_30_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_30_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_30_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_30_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_30_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_30_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_301;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_301_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_301_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_301_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_301_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_301_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_301_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_301_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_301_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_31;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_31_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_31_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_31_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_31_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_31_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_31_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_31_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_31_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_32;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_32_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_32_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_32_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_32_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_32_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_32_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_32_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_32_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_122;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_122_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_122_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_122_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_122_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_122_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_122_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_122_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_122_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_142;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_142_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_142_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_142_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_142_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_142_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_142_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_142_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_142_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_172;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_172_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_172_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_172_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_172_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_172_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_172_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_172_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_172_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_192;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_192_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_192_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_192_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_192_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_192_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_192_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_192_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_192_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_232;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_232_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_232_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_232_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_232_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_232_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_232_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_232_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_232_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_252;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_252_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_252_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_252_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_252_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_252_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_252_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_252_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_252_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_282;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_282_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_282_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_282_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_282_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_282_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_282_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_282_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_282_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralVtxMass_302;                              // dimuon Decay Length
  TH1D    *fGeneralVtxMass_302_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_302_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_302_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_302_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralVtxMass_302_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralVtxMass_302_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralVtxMass_302_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralVtxMass_302_nis_hl;                       // dimuon Decay Length, high mass, like sign


///

/// for fGeneralNrsecvtx

  TH1D    *fGeneralNrsecvtx_1;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_1_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_1_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_1_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_1_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_1_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_1_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_1_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_1_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_2;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_2_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_3;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_3_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_3_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_3_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_3_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_3_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_3_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_3_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_3_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_4;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_4_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_4_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_4_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_4_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_4_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_4_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_4_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_4_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_5;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_5_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_5_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_5_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_5_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_5_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_5_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_5_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_5_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_6;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_6_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_6_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_6_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_6_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_6_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_6_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_6_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_6_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_7;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_7_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_7_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_7_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_7_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_7_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_7_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_7_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_7_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_8;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_8_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_8_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_8_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_8_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_8_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_8_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_8_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_8_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_9;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_9_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_9_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_9_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_9_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_9_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_9_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_9_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_9_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_10;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_10_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_10_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_10_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_10_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_10_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_10_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_10_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_10_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_11;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_11_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_11_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_11_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_11_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_11_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_11_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_11_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_11_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_12;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_12_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_12_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_12_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_12_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_12_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_12_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_12_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_12_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_13;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_13_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_13_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_13_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_13_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_13_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_13_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_13_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_13_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_14;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_14_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_14_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_14_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_14_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_14_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_14_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_14_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_14_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_15;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_15_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_15_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_15_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_15_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_15_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_15_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_15_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_15_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralNrsecvtx_16;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_16_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_16_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_16_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_16_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_16_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_16_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_16_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_16_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_17;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_17_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_17_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_17_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_17_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_17_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_17_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_17_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_17_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_18;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_18_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_18_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_18_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_18_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_18_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_18_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_18_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_18_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_19;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_19_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_19_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_19_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_19_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_19_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_19_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_19_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_19_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_20;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_20_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_20_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_20_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_20_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_20_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_20_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_20_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_20_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_21;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_21_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_21_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_21_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_21_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_21_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_21_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_21_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_21_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_22;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_22_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_22_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_22_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_22_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_22_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_22_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_22_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_22_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_23;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_23_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_23_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_23_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_23_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_23_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_23_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_23_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_23_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_24;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_24_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_24_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_24_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_24_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_24_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_24_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_24_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_24_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralNrsecvtx_121;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_121_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_121_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_121_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_121_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_121_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_121_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_121_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_121_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_141;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_141_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_141_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_141_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_141_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_141_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_141_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_141_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_141_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_171;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_171_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_171_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_171_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_171_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_171_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_171_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_171_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_171_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_191;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_191_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_191_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_191_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_191_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_191_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_191_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_191_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_191_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_231;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_231_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_231_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_231_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_231_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_231_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_231_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_231_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_231_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_25;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_25_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_25_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_25_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_25_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_25_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_25_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_25_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_25_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_251;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_251_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_251_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_251_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_251_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_251_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_251_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_251_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_251_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_26;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_26_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_26_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_26_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_26_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_26_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_26_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_26_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_26_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_27;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_27_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_27_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_27_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_27_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_27_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_27_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_27_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_27_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_28;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_28_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_28_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_28_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_28_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_28_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_28_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_28_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_28_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_29;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_29_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_29_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_29_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_29_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_29_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_29_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_29_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_29_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_281;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_281_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_281_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_281_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_281_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_281_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_281_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_281_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_281_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_30;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_30_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_30_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_30_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_30_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_30_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_30_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_30_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_30_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_301;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_301_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_301_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_301_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_301_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_301_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_301_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_301_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_301_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_31;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_31_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_31_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_31_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_31_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_31_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_31_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_31_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_31_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_32;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_32_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_32_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_32_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_32_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_32_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_32_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_32_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_32_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_122;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_122_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_122_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_122_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_122_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_122_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_122_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_122_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_122_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_142;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_142_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_142_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_142_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_142_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_142_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_142_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_142_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_142_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_172;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_172_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_172_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_172_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_172_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_172_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_172_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_172_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_172_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_192;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_192_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_192_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_192_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_192_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_192_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_192_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_192_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_192_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_232;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_232_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_232_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_232_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_232_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_232_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_232_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_232_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_232_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_252;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_252_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_252_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_252_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_252_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_252_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_252_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_252_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_252_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_282;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_282_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_282_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_282_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_282_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_282_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_282_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_282_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_282_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralNrsecvtx_302;                              // dimuon Decay Length
  TH1D    *fGeneralNrsecvtx_302_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_302_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_302_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_302_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralNrsecvtx_302_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralNrsecvtx_302_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralNrsecvtx_302_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralNrsecvtx_302_nis_hl;                       // dimuon Decay Length, high mass, like sign





/// fGeneralChi2Ndof

/// for fGeneralChi2Ndof

  TH1D    *fGeneralChi2Ndof_1;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_1_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_1_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_1_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_1_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_1_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_1_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_1_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_1_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_2;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_2_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_3;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_3_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_3_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_3_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_3_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_3_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_3_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_3_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_3_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_4;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_4_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_4_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_4_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_4_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_4_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_4_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_4_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_4_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_5;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_5_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_5_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_5_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_5_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_5_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_5_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_5_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_5_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_6;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_6_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_6_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_6_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_6_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_6_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_6_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_6_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_6_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_7;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_7_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_7_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_7_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_7_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_7_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_7_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_7_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_7_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_8;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_8_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_8_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_8_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_8_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_8_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_8_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_8_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_8_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_9;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_9_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_9_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_9_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_9_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_9_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_9_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_9_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_9_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_10;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_10_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_10_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_10_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_10_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_10_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_10_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_10_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_10_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_11;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_11_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_11_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_11_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_11_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_11_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_11_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_11_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_11_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_12;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_12_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_12_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_12_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_12_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_12_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_12_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_12_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_12_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_13;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_13_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_13_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_13_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_13_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_13_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_13_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_13_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_13_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_14;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_14_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_14_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_14_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_14_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_14_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_14_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_14_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_14_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_15;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_15_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_15_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_15_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_15_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_15_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_15_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_15_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_15_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralChi2Ndof_16;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_16_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_16_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_16_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_16_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_16_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_16_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_16_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_16_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_17;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_17_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_17_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_17_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_17_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_17_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_17_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_17_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_17_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_18;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_18_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_18_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_18_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_18_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_18_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_18_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_18_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_18_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_19;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_19_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_19_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_19_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_19_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_19_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_19_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_19_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_19_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_20;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_20_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_20_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_20_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_20_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_20_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_20_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_20_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_20_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_21;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_21_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_21_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_21_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_21_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_21_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_21_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_21_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_21_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_22;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_22_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_22_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_22_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_22_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_22_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_22_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_22_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_22_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_23;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_23_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_23_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_23_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_23_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_23_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_23_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_23_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_23_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_24;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_24_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_24_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_24_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_24_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_24_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_24_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_24_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_24_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_121;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_121_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_121_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_121_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_121_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_121_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_121_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_121_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_121_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_141;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_141_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_141_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_141_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_141_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_141_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_141_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_141_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_141_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_171;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_171_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_171_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_171_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_171_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_171_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_171_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_171_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_171_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_191;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_191_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_191_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_191_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_191_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_191_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_191_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_191_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_191_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_231;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_231_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_231_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_231_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_231_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_231_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_231_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_231_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_231_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_25;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_25_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_25_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_25_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_25_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_25_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_25_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_25_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_25_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_251;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_251_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_251_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_251_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_251_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_251_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_251_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_251_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_251_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_26;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_26_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_26_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_26_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_26_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_26_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_26_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_26_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_26_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_27;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_27_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_27_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_27_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_27_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_27_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_27_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_27_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_27_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_28;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_28_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_28_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_28_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_28_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_28_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_28_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_28_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_28_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_29;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_29_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_29_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_29_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_29_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_29_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_29_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_29_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_29_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_281;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_281_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_281_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_281_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_281_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_281_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_281_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_281_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_281_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_30;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_30_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_30_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_30_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_30_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_30_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_30_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_30_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_30_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_301;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_301_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_301_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_301_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_301_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_301_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_301_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_301_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_301_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_31;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_31_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_31_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_31_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_31_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_31_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_31_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_31_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_31_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_32;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_32_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_32_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_32_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_32_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_32_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_32_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_32_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_32_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_122;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_122_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_122_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_122_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_122_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_122_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_122_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_122_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_122_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_142;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_142_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_142_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_142_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_142_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_142_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_142_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_142_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_142_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_172;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_172_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_172_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_172_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_172_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_172_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_172_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_172_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_172_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_192;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_192_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_192_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_192_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_192_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_192_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_192_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_192_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_192_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_232;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_232_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_232_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_232_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_232_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_232_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_232_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_232_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_232_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_252;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_252_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_252_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_252_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_252_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_252_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_252_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_252_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_252_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_282;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_282_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_282_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_282_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_282_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_282_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_282_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_282_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_282_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralChi2Ndof_302;                              // dimuon Decay Length
  TH1D    *fGeneralChi2Ndof_302_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_302_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_302_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_302_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralChi2Ndof_302_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralChi2Ndof_302_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralChi2Ndof_302_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralChi2Ndof_302_nis_hl;                       // dimuon Decay Length, high mass, like sign




/// for fGeneralMulti

  TH1D    *fGeneralMulti_1;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_1_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_1_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_1_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_1_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_1_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_1_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_1_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_1_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_2;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_2_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_3;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_3_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_3_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_3_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_3_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_3_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_3_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_3_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_3_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_4;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_4_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_4_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_4_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_4_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_4_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_4_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_4_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_4_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_5;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_5_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_5_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_5_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_5_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_5_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_5_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_5_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_5_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_6;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_6_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_6_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_6_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_6_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_6_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_6_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_6_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_6_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_7;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_7_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_7_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_7_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_7_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_7_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_7_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_7_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_7_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_8;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_8_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_8_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_8_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_8_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_8_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_8_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_8_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_8_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_9;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_9_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_9_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_9_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_9_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_9_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_9_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_9_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_9_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_10;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_10_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_10_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_10_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_10_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_10_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_10_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_10_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_10_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_11;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_11_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_11_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_11_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_11_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_11_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_11_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_11_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_11_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_12;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_12_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_12_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_12_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_12_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_12_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_12_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_12_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_12_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_13;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_13_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_13_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_13_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_13_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_13_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_13_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_13_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_13_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_14;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_14_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_14_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_14_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_14_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_14_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_14_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_14_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_14_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_15;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_15_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_15_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_15_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_15_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_15_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_15_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_15_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_15_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralMulti_16;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_16_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_16_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_16_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_16_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_16_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_16_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_16_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_16_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_17;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_17_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_17_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_17_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_17_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_17_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_17_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_17_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_17_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_18;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_18_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_18_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_18_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_18_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_18_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_18_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_18_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_18_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_19;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_19_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_19_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_19_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_19_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_19_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_19_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_19_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_19_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_20;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_20_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_20_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_20_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_20_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_20_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_20_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_20_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_20_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_21;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_21_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_21_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_21_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_21_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_21_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_21_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_21_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_21_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_22;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_22_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_22_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_22_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_22_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_22_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_22_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_22_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_22_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_23;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_23_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_23_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_23_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_23_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_23_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_23_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_23_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_23_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_24;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_24_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_24_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_24_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_24_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_24_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_24_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_24_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_24_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_121;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_121_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_121_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_121_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_121_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_121_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_121_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_121_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_121_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_141;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_141_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_141_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_141_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_141_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_141_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_141_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_141_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_141_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_171;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_171_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_171_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_171_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_171_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_171_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_171_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_171_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_171_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_191;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_191_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_191_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_191_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_191_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_191_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_191_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_191_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_191_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_231;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_231_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_231_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_231_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_231_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_231_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_231_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_231_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_231_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_25;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_25_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_25_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_25_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_25_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_25_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_25_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_25_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_25_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_251;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_251_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_251_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_251_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_251_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_251_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_251_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_251_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_251_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_26;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_26_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_26_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_26_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_26_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_26_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_26_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_26_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_26_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_27;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_27_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_27_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_27_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_27_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_27_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_27_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_27_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_27_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_28;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_28_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_28_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_28_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_28_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_28_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_28_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_28_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_28_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_29;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_29_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_29_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_29_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_29_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_29_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_29_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_29_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_29_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_281;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_281_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_281_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_281_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_281_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_281_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_281_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_281_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_281_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_30;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_30_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_30_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_30_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_30_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_30_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_30_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_30_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_30_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_301;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_301_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_301_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_301_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_301_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_301_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_301_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_301_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_301_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_31;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_31_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_31_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_31_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_31_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_31_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_31_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_31_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_31_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_32;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_32_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_32_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_32_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_32_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_32_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_32_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_32_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_32_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralMulti_122;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_122_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_122_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_122_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_122_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_122_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_122_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_122_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_122_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_142;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_142_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_142_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_142_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_142_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_142_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_142_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_142_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_142_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_172;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_172_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_172_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_172_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_172_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_172_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_172_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_172_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_172_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_192;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_192_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_192_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_192_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_192_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_192_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_192_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_192_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_192_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_232;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_232_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_232_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_232_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_232_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_232_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_232_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_232_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_232_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_252;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_252_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_252_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_252_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_252_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_252_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_252_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_252_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_252_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_282;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_282_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_282_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_282_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_282_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_282_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_282_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_282_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_282_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralMulti_302;                              // dimuon Decay Length
  TH1D    *fGeneralMulti_302_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_302_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_302_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_302_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralMulti_302_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralMulti_302_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralMulti_302_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralMulti_302_nis_hl;                       // dimuon Decay Length, high mass, like sign



/// for fGeneralDL2_Sign

///

  TH1D    *fGeneralDL2_Sign_mvtx1;
  TH1D    *fGeneralDL2_Sign_mvtx2;
  TH1D    *fGeneralDL2_Sign_mvtx3;
  TH1D    *fGeneralDL2_Sign_mvtx4;
  TH1D    *fGeneralDL2_Sign_mvtx5;
  TH1D    *fGeneralDL2_Sign_mvtx6;
  TH1D    *fGeneralDL2_Sign_mvtx7;
  TH1D    *fGeneralDL2_Sign_mvtx8;

  TH1D    *fGeneralDL2_Sign_mvtx1_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx2_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx3_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx4_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx5_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx6_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx7_is_lu;
  TH1D    *fGeneralDL2_Sign_mvtx8_is_lu;

  TH1D    *fGeneralDL2_Sign_mvtx1_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx2_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx3_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx4_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx5_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx6_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx7_is_ll;
  TH1D    *fGeneralDL2_Sign_mvtx8_is_ll;

  TH1D    *fGeneralDL2_Sign_mvtx1_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx2_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx3_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx4_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx5_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx6_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx7_is_hu;
  TH1D    *fGeneralDL2_Sign_mvtx8_is_hu;

  TH1D    *fGeneralDL2_Sign_mvtx1_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx2_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx3_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx4_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx5_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx6_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx7_is_hl;
  TH1D    *fGeneralDL2_Sign_mvtx8_is_hl;

  TH1D    *fGeneralDL2_Sign_mvtx1_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx2_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx3_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx4_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx5_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx6_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx7_nis_lu;
  TH1D    *fGeneralDL2_Sign_mvtx8_nis_lu;

  TH1D    *fGeneralDL2_Sign_mvtx1_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx2_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx3_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx4_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx5_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx6_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx7_nis_ll;
  TH1D    *fGeneralDL2_Sign_mvtx8_nis_ll;

  TH1D    *fGeneralDL2_Sign_mvtx1_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx2_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx3_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx4_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx5_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx6_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx7_nis_hu;
  TH1D    *fGeneralDL2_Sign_mvtx8_nis_hu;

  TH1D    *fGeneralDL2_Sign_mvtx1_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx2_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx3_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx4_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx5_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx6_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx7_nis_hl;
  TH1D    *fGeneralDL2_Sign_mvtx8_nis_hl;

///

  TH1D    *fGeneralDL2_Sign_1;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_1_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_1_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_1_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_1_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_1_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_1_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_1_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_1_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_2;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_2_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_2_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_2_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_2_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_2_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_2_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_2_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_2_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_3;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_3_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_3_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_3_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_3_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_3_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_3_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_3_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_3_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_4;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_4_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_4_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_4_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_4_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_4_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_4_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_4_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_4_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_5;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_5_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_5_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_5_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_5_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_5_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_5_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_5_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_5_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_6;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_6_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_6_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_6_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_6_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_6_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_6_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_6_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_6_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_7;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_7_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_7_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_7_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_7_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_7_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_7_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_7_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_7_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_8;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_8_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_8_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_8_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_8_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_8_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_8_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_8_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_8_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_9;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_9_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_9_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_9_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_9_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_9_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_9_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_9_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_9_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_10;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_10_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_10_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_10_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_10_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_10_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_10_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_10_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_10_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_11;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_11_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_11_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_11_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_11_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_11_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_11_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_11_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_11_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_12;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_12_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_12_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_12_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_12_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_12_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_12_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_12_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_12_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_13;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_13_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_13_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_13_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_13_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_13_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_13_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_13_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_13_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_14;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_14_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_14_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_14_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_14_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_14_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_14_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_14_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_14_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_15;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_15_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_15_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_15_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_15_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_15_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_15_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_15_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_15_nis_hl;                       // dimuon Decay Length, high mass, like sign


  TH1D    *fGeneralDL2_Sign_16;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_16_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_16_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_16_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_16_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_16_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_16_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_16_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_16_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_17;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_17_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_17_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_17_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_17_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_17_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_17_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_17_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_17_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_18;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_18_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_18_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_18_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_18_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_18_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_18_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_18_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_18_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_19;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_19_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_19_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_19_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_19_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_19_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_19_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_19_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_19_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_20;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_20_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_20_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_20_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_20_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_20_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_20_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_20_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_20_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_21;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_21_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_21_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_21_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_21_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_21_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_21_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_21_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_21_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_22;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_22_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_22_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_22_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_22_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_22_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_22_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_22_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_22_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_23;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_23_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_23_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_23_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_23_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_23_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_23_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_23_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_23_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_24;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_24_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_24_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_24_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_24_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_24_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_24_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_24_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_24_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_121;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_121_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_121_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_121_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_121_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_121_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_121_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_121_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_121_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_141;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_141_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_141_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_141_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_141_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_141_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_141_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_141_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_141_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_171;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_171_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_171_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_171_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_171_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_171_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_171_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_171_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_171_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_191;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_191_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_191_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_191_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_191_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_191_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_191_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_191_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_191_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_231;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_231_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_231_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_231_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_231_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_231_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_231_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_231_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_231_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_25;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_25_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_25_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_25_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_25_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_25_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_25_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_25_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_25_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_251;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_251_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_251_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_251_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_251_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_251_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_251_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_251_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_251_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_26;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_26_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_26_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_26_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_26_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_26_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_26_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_26_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_26_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_27;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_27_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_27_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_27_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_27_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_27_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_27_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_27_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_27_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_28;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_28_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_28_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_28_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_28_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_28_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_28_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_28_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_28_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_29;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_29_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_29_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_29_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_29_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_29_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_29_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_29_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_29_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_281;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_281_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_281_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_281_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_281_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_281_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_281_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_281_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_281_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_30;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_30_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_30_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_30_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_30_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_30_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_30_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_30_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_30_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_301;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_301_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_301_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_301_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_301_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_301_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_301_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_301_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_301_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_31;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_31_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_31_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_31_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_31_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_31_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_31_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_31_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_31_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_32;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_32_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_32_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_32_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_32_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_32_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_32_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_32_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_32_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_122;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_122_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_122_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_122_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_122_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_122_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_122_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_122_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_122_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_142;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_142_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_142_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_142_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_142_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_142_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_142_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_142_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_142_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_172;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_172_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_172_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_172_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_172_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_172_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_172_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_172_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_172_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_192;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_192_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_192_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_192_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_192_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_192_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_192_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_192_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_192_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_232;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_232_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_232_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_232_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_232_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_232_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_232_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_232_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_232_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_252;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_252_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_252_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_252_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_252_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_252_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_252_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_252_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_252_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_282;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_282_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_282_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_282_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_282_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_282_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_282_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_282_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_282_nis_hl;                       // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign_302;                              // dimuon Decay Length
  TH1D    *fGeneralDL2_Sign_302_is_lu;                        // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_302_is_ll;                        // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_302_is_hu;                        // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_302_is_hl;                        // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_Sign_302_nis_lu;                       // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_302_nis_ll;                       // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_Sign_302_nis_hu;                       // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_302_nis_hl;                       // dimuon Decay Length, high mass, like sign



/// End Nazar's editing

  TH1D    *fGeneralDL2_err;                          // dimuon Decay Length
  TH1D    *fGeneralDL2_err_is_lu;                    // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_err_is_ll;                    // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_err_is_hu;                    // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_err_is_hl;                    // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneralDL2_err_nis_lu;                   // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneralDL2_err_nis_ll;                   // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneralDL2_err_nis_hu;                   // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneralDL2_err_nis_hl;                   // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneralDL2_Sign;                         // dimuon Decay Length Significance
  TH1D    *fGeneralDL2_Sign_is_lu;                   // dimuon Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_is_ll;                   // dimuon Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_is_hu;                   // dimuon Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_is_hl;                   // dimuon Decay Length Significance, high mass, like sign
  TH1D    *fGeneralDL2_Sign_nis_lu;                  // dimuon Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_nis_ll;                  // dimuon Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_nis_hu;                  // dimuon Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_nis_hl;                  // dimuon Decay Length Significance, high mass, like sign

  TH1D    *fGeneralDL2_Sign_Mirrp;                   // dimuon mirrored Decay Length Significance
  TH1D    *fGeneralDL2_Sign_Mirrp_is_lu;             // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_is_ll;             // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrp_is_hu;             // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_is_hl;             // dimuon mirrored Decay Length Significance, high mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_lu;            // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_ll;            // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_hu;            // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrp_nis_hl;            // dimuon mirrored Decay Length Significance, high mass, like sign

  TH1D    *fGeneralDL2_Sign_Mirrm;                   // dimuon mirrored Decay Length Significance
  TH1D    *fGeneralDL2_Sign_Mirrm_is_lu;             // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_is_ll;             // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrm_is_hu;             // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_is_hl;             // dimuon mirrored Decay Length Significance, high mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_lu;            // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_ll;            // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_hu;            // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneralDL2_Sign_Mirrm_nis_hl;            // dimuon mirrored Decay Length Significance, high mass, like sign

  TH1D    *fGeneral_mvtx2_DL2;                       // dimuon Decay Length
  TH1D    *fGeneral_mvtx2_DL2_is_lu;                 // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_is_ll;                 // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_is_hu;                 // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_is_hl;                 // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_nis_lu;                // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_nis_ll;                // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_nis_hu;                // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_nis_hl;                // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneral_mvtx2_DL2_err;                   // dimuon Decay Length
  TH1D    *fGeneral_mvtx2_DL2_err_is_lu;             // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_err_is_ll;             // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_err_is_hu;             // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_err_is_hl;             // dimuon Decay Length, high mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_err_nis_lu;            // dimuon Decay Length, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_err_nis_ll;            // dimuon Decay Length, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_err_nis_hu;            // dimuon Decay Length, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_err_nis_hl;            // dimuon Decay Length, high mass, like sign

  TH1D    *fGeneral_mvtx2_DL2_Sign;                  // dimuon Decay Length Significance
  TH1D    *fGeneral_mvtx2_DL2_Sign_is_lu;            // dimuon Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_is_ll;            // dimuon Decay Length Significance, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_is_hu;            // dimuon Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_is_hl;            // dimuon Decay Length Significance, high mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_nis_lu;           // dimuon Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_nis_ll;           // dimuon Decay Length Significance, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_nis_hu;           // dimuon Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_nis_hl;           // dimuon Decay Length Significance, high mass, like sign

  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp;            // dimuon mirrored Decay Length Significance
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_is_lu;      // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_is_ll;      // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_is_hu;      // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_is_hl;      // dimuon mirrored Decay Length Significance, high mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_nis_lu;     // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_nis_ll;     // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hu;     // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hl;     // dimuon mirrored Decay Length Significance, high mass, like sign

  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm;            // dimuon mirrored Decay Length Significance
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_is_lu;      // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_is_ll;      // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_is_hu;      // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_is_hl;      // dimuon mirrored Decay Length Significance, high mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_nis_lu;     // dimuon mirrored Decay Length Significance, low mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_nis_ll;     // dimuon mirrored Decay Length Significance, low mass, like sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hu;     // dimuon mirrored Decay Length Significance, high mass, unlike sign
  TH1D    *fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hl;     // dimuon mirrored Decay Length Significance, high mass, like sign

  TH1D    *fGeneralMuJetDeltaR  ;                    // dimuon DeltaR Muon-Jet
  TH1D    *fGeneralMuJetDeltaR_is_lu;                // dimuon DeltaR Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_is_ll;                // dimuon DeltaR Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetDeltaR_is_hu;                // dimuon DeltaR Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_is_hl;                // dimuon DeltaR Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetDeltaR_nis_lu;               // dimuon DeltaR Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_nis_ll;               // dimuon DeltaR Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetDeltaR_nis_hu;               // dimuon DeltaR Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetDeltaR_nis_hl;               // dimuon DeltaR Muon-Jet, high mass, like sign

  TH1D    *fGeneralMuJetPt  ;                        // dimuon Pt Muon-Jet
  TH1D    *fGeneralMuJetPt_is_lu;                    // dimuon Pt Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetPt_is_ll;                    // dimuon Pt Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetPt_is_hu;                    // dimuon Pt Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetPt_is_hl;                    // dimuon Pt Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetPt_nis_lu;                   // dimuon Pt Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetPt_nis_ll;                   // dimuon Pt Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetPt_nis_hu;                   // dimuon Pt Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetPt_nis_hl;                   // dimuon Pt Muon-Jet, high mass, like sign

  TH1D    *fGeneralMuJetEt  ;                        // dimuon Et Muon-Jet
  TH1D    *fGeneralMuJetEt_is_lu;                    // dimuon Et Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEt_is_ll;                    // dimuon Et Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEt_is_hu;                    // dimuon Et Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEt_is_hl;                    // dimuon Et Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetEt_nis_lu;                   // dimuon Et Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEt_nis_ll;                   // dimuon Et Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEt_nis_hu;                   // dimuon Et Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEt_nis_hl;                   // dimuon Et Muon-Jet, high mass, like sign

  TH1D    *fGeneralMuJetEta  ;                       // dimuon Eta Muon-Jet
  TH1D    *fGeneralMuJetEta_is_lu;                   // dimuon Eta Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEta_is_ll;                   // dimuon Eta Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEta_is_hu;                   // dimuon Eta Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEta_is_hl;                   // dimuon Eta Muon-Jet, high mass, like sign
  TH1D    *fGeneralMuJetEta_nis_lu;                  // dimuon Eta Muon-Jet, low mass, unlike sign
  TH1D    *fGeneralMuJetEta_nis_ll;                  // dimuon Eta Muon-Jet, low mass, like sign
  TH1D    *fGeneralMuJetEta_nis_hu;                  // dimuon Eta Muon-Jet, high mass, unlike sign
  TH1D    *fGeneralMuJetEta_nis_hl;                  // dimuon Eta Muon-Jet, high mass, like sign

  TH1D    *fGeneralMassJet  ;                        // dimuon MassJet
  TH1D    *fGeneralMassJet_is_lu;                    // dimuon MassJet, low mass, unlike sign
  TH1D    *fGeneralMassJet_is_ll;                    // dimuon MassJet, low mass, like sign
  TH1D    *fGeneralMassJet_is_hu;                    // dimuon MassJet, high mass, unlike sign
  TH1D    *fGeneralMassJet_is_hl;                    // dimuon MassJet, high mass, like sign
  TH1D    *fGeneralMassJet_nis_lu;                   // dimuon MassJet, low mass, unlike sign
  TH1D    *fGeneralMassJet_nis_ll;                   // dimuon MassJet, low mass, like sign
  TH1D    *fGeneralMassJet_nis_hu;                   // dimuon MassJet, high mass, unlike sign
  TH1D    *fGeneralMassJet_nis_hl;                   // dimuon MassJet, high mass, like sign

  TH1D    *fGeneralNJets  ;                          // dimuon NJets
  TH1D    *fGeneralNJets_is_lu;                      // dimuon NJets, low mass, unlike sign
  TH1D    *fGeneralNJets_is_ll;                      // dimuon NJets, low mass, like sign
  TH1D    *fGeneralNJets_is_hu;                      // dimuon NJets, high mass, unlike sign
  TH1D    *fGeneralNJets_is_hl;                      // dimuon NJets, high mass, like sign
  TH1D    *fGeneralNJets_nis_lu;                     // dimuon NJets, low mass, unlike sign
  TH1D    *fGeneralNJets_nis_ll;                     // dimuon NJets, low mass, like sign
  TH1D    *fGeneralNJets_nis_hu;                     // dimuon NJets, high mass, unlike sign
  TH1D    *fGeneralNJets_nis_hl;                     // dimuon NJets, high mass, like sign

  TH1D    *fGeneralsqisol_10   ;                     // dimuon sqared isolation sum in DeltaR come of 1.0	      	     
  TH1D    *fGeneralsqisol_10_is_lu;                  // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_ll;                  // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_hu;                  // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_is_hl;                  // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_lu;                 // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_ll;                 // dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_hu;                 // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_hl;                 // dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D    *fGeneralthrust   ;                        // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_lu;                     // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_ll;                     // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_hu;                     // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_hl;                     // thrust of event, classified by muon pair    
  TH1D    *fGeneralthrust_nis_lu;                    // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_ll;                    // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hu;                    // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hl;                    // thrust of event, classified by muon pair 

  TH1D    *fGeneralsphericity  ;                     // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_lu;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_ll;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hu;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hl;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_lu;                // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_ll;                // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hu;                // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hl;                // sphericity of event, classified by muon pair

  TH1D    *fGeneralisotropy  ;                       // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_lu;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_ll;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hu;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hl;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_lu;                  // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_ll;                  // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hu;                  // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hl;                  // isotropy of event, classified by muon pair
    
  TH1D    *fGeneralmultiplicity  ;                   // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_lu;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_ll;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hu;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hl;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_lu;              // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_ll;              // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hu;              // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hl;              // multiplicity of event, classified by muon pair

  TH1D    *fGeneralQ2Prime  ;                        // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_lu;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_ll;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hu;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hl;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_lu;                   // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_ll;                   // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_hu;                   // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fGeneralQ2Prime_nis_hl;                   // Virtuality Q'2 of event, classified by muon pair

  TH1D    *fGeneralempz   ;                          // empz of event, classified by muon pair
  TH1D    *fGeneralempz_is_lu;                       // empz of event, classified by muon pair  
  TH1D    *fGeneralempz_is_ll;                       // empz of event, classified by muon pair  
  TH1D    *fGeneralempz_is_hu;                       // empz of event, classified by muon pair
  TH1D    *fGeneralempz_is_hl;                       // empz of event, classified by muon pair    
  TH1D    *fGeneralempz_nis_lu;                      // empz of event, classified by muon pair
  TH1D    *fGeneralempz_nis_ll;                      // empz of event, classified by muon pair
  TH1D    *fGeneralempz_nis_hu;                      // empz of event, classified by muon pair
  TH1D    *fGeneralempz_nis_hl;                      // empz of event, classified by muon pair 

  TH1D    *fGeneralcal_et   ;                        // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_lu;                     // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_ll;                     // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_hu;                     // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_hl;                     // cal_et of event, classified by muon pair    
  TH1D    *fGeneralcal_et_nis_lu;                    // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_ll;                    // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hu;                    // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hl;                    // cal_et of event, classified by muon pair 

/* DB: Cross Section Dijet Selection */

  TH1D    *fGeneraldijetbothetex2ir   ;                       // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetbothetex2ir_is_lu;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraldijetbothetex2ir_is_ll;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraldijetbothetex2ir_is_hu;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetbothetex2ir_is_hl;                    // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraldijetbothetex2ir_nis_lu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetbothetex2ir_nis_ll;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetbothetex2ir_nis_hu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetbothetex2ir_nis_hl;                   // etex2ir of event, classified by muon pair 

  TH1D    *fGeneraldijetbothdimuxsecpt       ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_is_lu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_is_ll ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_is_hu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_is_hl ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_nis_lu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_nis_ll;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_nis_hu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetbothdimuxsecpt_nis_hl;                // plot for dimuon muon dimuxsec in pt

  TH1D    *fGeneraldijetbothdimuxseceta       ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_is_lu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_is_ll ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_is_hu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_is_hl ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_nis_lu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_nis_ll;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_nis_hu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetbothdimuxseceta_nis_hl;               // plot for dimuon muon dimuxsec in eta

  TH1D    *fGeneraldijetbothdimuxsecdphi       ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_is_lu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_is_ll ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_is_hu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_is_hl ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_nis_lu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_nis_ll;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_nis_hu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetbothdimuxsecdphi_nis_hl;              // plot for dimuon muon dimuxsec in dphi

  TH1D    *fGeneraldijetoneetex2ir   ;                       // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetoneetex2ir_is_lu;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraldijetoneetex2ir_is_ll;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraldijetoneetex2ir_is_hu;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetoneetex2ir_is_hl;                    // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraldijetoneetex2ir_nis_lu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetoneetex2ir_nis_ll;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetoneetex2ir_nis_hu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetoneetex2ir_nis_hl;                   // etex2ir of event, classified by muon pair 

  TH1D    *fGeneraldijetonedimuxsecpt       ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_is_lu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_is_ll ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_is_hu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_is_hl ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_nis_lu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_nis_ll;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_nis_hu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetonedimuxsecpt_nis_hl;                // plot for dimuon muon dimuxsec in pt

  TH1D    *fGeneraldijetonedimuxseceta       ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_is_lu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_is_ll ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_is_hu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_is_hl ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_nis_lu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_nis_ll;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_nis_hu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetonedimuxseceta_nis_hl;               // plot for dimuon muon dimuxsec in eta

  TH1D    *fGeneraldijetonedimuxsecdphi       ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_is_lu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_is_ll ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_is_hu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_is_hl ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_nis_lu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_nis_ll;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_nis_hu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetonedimuxsecdphi_nis_hl;              // plot for dimuon muon dimuxsec in dphi

  TH1D    *fGeneraldijetnoneetex2ir   ;                       // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetnoneetex2ir_is_lu;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraldijetnoneetex2ir_is_ll;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraldijetnoneetex2ir_is_hu;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetnoneetex2ir_is_hl;                    // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraldijetnoneetex2ir_nis_lu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetnoneetex2ir_nis_ll;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetnoneetex2ir_nis_hu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraldijetnoneetex2ir_nis_hl;                   // etex2ir of event, classified by muon pair 

  TH1D    *fGeneraldijetnonedimuxsecpt       ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_is_lu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_is_ll ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_is_hu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_is_hl ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_nis_lu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_nis_ll;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_nis_hu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldijetnonedimuxsecpt_nis_hl;                // plot for dimuon muon dimuxsec in pt

  TH1D    *fGeneraldijetnonedimuxseceta       ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_is_lu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_is_ll ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_is_hu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_is_hl ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_nis_lu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_nis_ll;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_nis_hu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldijetnonedimuxseceta_nis_hl;               // plot for dimuon muon dimuxsec in eta

  TH1D    *fGeneraldijetnonedimuxsecdphi       ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_is_lu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_is_ll ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_is_hu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_is_hl ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_nis_lu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_nis_ll;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_nis_hu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldijetnonedimuxsecdphi_nis_hl;              // plot for dimuon muon dimuxsec in dphi

/* End of Dijet Selection */

  TH1D    *fGeneraletex2ir   ;                       // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_lu;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_ll;                    // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_hu;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_hl;                    // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraletex2ir_nis_lu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_ll;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hu;                   // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hl;                   // etex2ir of event, classified by muon pair 

  TH1D    *fGeneraldimuxsecpt       ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_is_lu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_is_ll ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_is_hu ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_is_hl ;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_nis_lu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_nis_ll;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_nis_hu;                // plot for dimuon muon dimuxsec in pt
  TH1D    *fGeneraldimuxsecpt_nis_hl;                // plot for dimuon muon dimuxsec in pt

  TH1D    *fGeneraldimuxseceta       ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_is_lu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_is_ll ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_is_hu ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_is_hl ;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_nis_lu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_nis_ll;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_nis_hu;               // plot for dimuon muon dimuxsec in eta
  TH1D    *fGeneraldimuxseceta_nis_hl;               // plot for dimuon muon dimuxsec in eta

  TH1D    *fGeneraldimuxsecfinders       ;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_is_lu ;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_is_ll ;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_is_hu ;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_is_hl ;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_nis_lu;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_nis_ll;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_nis_hu;           // plot for dimuon muon dimuxsec in finders
  TH1D    *fGeneraldimuxsecfinders_nis_hl;           // plot for dimuon muon dimuxsec in finders

  TH1D    *fGeneraldimuxsecdr       ;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_is_lu ;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_is_ll ;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_is_hu ;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_is_hl ;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_nis_lu;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_nis_ll;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_nis_hu;                // plot for dimuon muon dimuxsec in dr
  TH1D    *fGeneraldimuxsecdr_nis_hl;                // plot for dimuon muon dimuxsec in dr

  TH1D    *fGeneraldimuxsecdphi       ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_is_lu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_is_ll ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_is_hu ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_is_hl ;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_nis_lu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_nis_ll;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_nis_hu;              // plot for dimuon muon dimuxsec in dphi
  TH1D    *fGeneraldimuxsecdphi_nis_hl;              // plot for dimuon muon dimuxsec in dphi

  TH1D    *fGeneraldimuxsecptb       ;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_is_lu ;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_is_ll ;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_is_hu ;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_is_hl ;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_nis_lu;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_nis_ll;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_nis_hu;               // plot for dimuon muon dimuxsec in ptb
  TH1D    *fGeneraldimuxsecptb_nis_hl;               // plot for dimuon muon dimuxsec in ptb

  TH1D    *fGeneraldimuxsecptb_sameb       ;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_is_lu ;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_is_ll ;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_is_hu ;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_is_hl ;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_nis_lu;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_nis_ll;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_nis_hu;         // plot for dimuon muon dimuxsec in ptb_sameb
  TH1D    *fGeneraldimuxsecptb_sameb_nis_hl;         // plot for dimuon muon dimuxsec in ptb_sameb

  TH1D    *fGeneraldimuxsecptb_diffb       ;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_is_lu ;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_is_ll ;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_is_hu ;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_is_hl ;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_nis_lu;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_nis_ll;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_nis_hu;         // plot for dimuon muon dimuxsec in ptb_diffb
  TH1D    *fGeneraldimuxsecptb_diffb_nis_hl;         // plot for dimuon muon dimuxsec in ptb_diffb

  TH1D    *fGeneraldimuxsecptb_samecone       ;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_is_lu ;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_is_ll ;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_is_hu ;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_is_hl ;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_nis_lu;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_nis_ll;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_nis_hu;      // plot for dimuon muon dimuxsec in ptb_samecone
  TH1D    *fGeneraldimuxsecptb_samecone_nis_hl;      // plot for dimuon muon dimuxsec in ptb_samecone

  TH1D    *fGeneraldimuxsecptb_asym       ;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_is_lu ;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_is_ll ;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_is_hu ;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_is_hl ;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_nis_lu;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_nis_ll;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_nis_hu;          // plot for dimuon muon dimuxsec in ptb_asym
  TH1D    *fGeneraldimuxsecptb_asym_nis_hl;          // plot for dimuon muon dimuxsec in ptb_asym

  TH1D    *fGeneralcal_et_m_et2ir   ;                // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_lu;             // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_ll;             // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_hu;             // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_hl;             // cal_et_m_et2ir of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_et2ir_nis_lu;            // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_ll;            // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hu;            // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hl;            // cal_et_m_et2ir of event, classified by muon pair 

  TH1D    *fGeneralcal_et_m_cal_et_10   ;            // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_lu;         // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_ll;         // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hu;         // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hl;         // cal_et_m_cal_et_10 of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_lu;        // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_ll;        // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hu;        // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hl;        // cal_et_m_cal_et_10 of event, classified by muon pair 

  TH1D    *fGeneralTriggerType;                      // trigger type

  Int_t        fGeneralMuonP_NBins_MPMATCH;          // number of bins for MuonP plots for MPMATCH plots
  Double_t    *fGeneralMuonP_Bins_MPMATCH;           // array for bin borders with dimension fGeneralMuonP_NBins+1 for MPMATCH plots

  Int_t        fGeneralMuonP_NBins_MUBAC;            // number of bins for MuonP plots for MUBAC plots
  Double_t    *fGeneralMuonP_Bins_MUBAC;             // array for bin borders with dimension fGeneralMuonP_NBins+1 for MUBAC plots

  Int_t        fGeneralMuonP_NBins_MV;               // number of bins for MuonP plots for MV plots
  Double_t    *fGeneralMuonP_Bins_MV;                // array for bin borders with dimension fGeneralMuonP_NBins+1 for MV plots

  Int_t        fGeneralMuonPt_NBins_BREMAT;          // number of bins for MuonPt plots for BREMAT plots
  Double_t    *fGeneralMuonPt_Bins_BREMAT;           // array for bin borders with dimension fGeneralMuonPt_NBins+1 for BREMAT plots

  Int_t        fGeneralMuonPt_NBins_MUBAC;           // number of bins for MuonPt plots for MUBAC plots
  Double_t    *fGeneralMuonPt_Bins_MUBAC;            // array for bin borders with dimension fGeneralMuonPt_NBins+1 for MUBAC plots

  Int_t        fGeneralMuonPt_NBins_MV;              // number of bins for MuonPt plots for MV plots
  Double_t    *fGeneralMuonPt_Bins_MV;               // array for bin borders with dimension fGeneralMuonPt_NBins+1 for MV plots

  Int_t        fGeneralMuonPz_NBins_BREMAT;          // number of bins for MuonPz plots for BREMAT muons
  Double_t    *fGeneralMuonPz_Bins_BREMAT;           // array for bin borders with dimension fGeneralMuonPz_NBins+1 for BREMAT muons

  Int_t        fGeneralMuonPz_NBins_MUBAC;           // number of bins for MuonPz plots for MUBAC muons
  Double_t    *fGeneralMuonPz_Bins_MUBAC;            // array for bin borders with dimension fGeneralMuonPz_NBins+1 for MUBAC muons

  Int_t        fGeneralMuonPz_NBins_MV;              // number of bins for MuonPz plots for MV muons
  Double_t    *fGeneralMuonPz_Bins_MV;               // array for bin borders with dimension fGeneralMuonPz_NBins+1 for MV muons

  TH1D    *fGeneralMV_MuonPt;                        // Pt  for all muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPt;                 // Pt  for all muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPt;                  // Pt  for all muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonP;                         // P   for all muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_MPMATCH_MuonP;                 // P   for all muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonP;                   // P   for all muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonPz;                        // Pz  for all muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPz;                 // Pz  for all muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPz;                  // Pz  for all muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonEta;                       // Eta for all muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonEta;                // Eta for all muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MPMATCH_MuonEta;               // Eta for all muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonEta;                 // Eta for all muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonEtaPtBins;                 // Eta for all muons from chosen dimuon found by mv in bins of pt
  TH1D   **fGeneralMV_BREMAT_MuonEtaPtBins;          // Eta for all muons from chosen dimuon found by mv and bremat in bins of pt
  TH1D   **fGeneralMV_MPMATCH_MuonEtaPtBins;         // Eta for all muons from chosen dimuon found by mv and mpmatch in bins of pt
  TH1D   **fGeneralMV_MUBAC_MuonEtaPtBins;           // Eta for all muons from chosen dimuon found by mv and mubac in bins of pt
  TH1D    *fGeneralMV_MuonPhi;                       // Phi for all muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPhi;                // Phi for all muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MPMATCH_MuonPhi;               // Phi for all muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonPhi;                 // Phi for all muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonPhiPtBins;                 // Phi for all muons from chosen dimuon found by mv in bins of pt
  TH1D   **fGeneralMV_BREMAT_MuonPhiPtBins;          // Phi for all muons from chosen dimuon found by mv and bremat in bins of pt
  TH1D   **fGeneralMV_MPMATCH_MuonPhiPtBins;         // Phi for all muons from chosen dimuon found by mv and mpmatch in bins of pt
  TH1D   **fGeneralMV_MUBAC_MuonPhiPtBins;           // Phi for all muons from chosen dimuon found by mv and mubac in bins of pt

  TH1D    *fGeneralMV_MuonP_Forward;                 // P   for all forward muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_MPMATCH_MuonP_Forward;         // P   for all forward muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonP_Forward;           // P   for all forward muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonPt_Forward;                // Pt  for all forward muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_MPMATCH_MuonPt_Forward;        // Pt  for all forward muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonPt_Forward;          // Pt  for all forward muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonEta_Forward;               // Eta for all forward muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_MPMATCH_MuonEta_Forward;       // Eta for all forward muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonEta_Forward;         // Eta for all forward muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonEtaPBins_Forward;          // Eta for all forward muons from chosen dimuon found by mv in bins of p
  TH1D   **fGeneralMV_MPMATCH_MuonEtaPBins_Forward;  // Eta for all forward muons from chosen dimuon found by mv and mpmatch in bins of p
  TH1D   **fGeneralMV_MUBAC_MuonEtaPBins_Forward;    // Eta for all forward muons from chosen dimuon found by mv and mubac in bins of p
  TH1D    *fGeneralMV_MuonPhi_Forward;               // Phi for all forward muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_MPMATCH_MuonPhi_Forward;       // Phi for all forward muons from chosen dimuon found by mv and mpmatch
  TH1D    *fGeneralMV_MUBAC_MuonPhi_Forward;         // Phi for all forward muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonPhiPBins_Forward;          // Phi for all forward muons from chosen dimuon found by mv in bins of p
  TH1D   **fGeneralMV_MPMATCH_MuonPhiPBins_Forward;  // Phi for all forward muons from chosen dimuon found by mv and mpmatch in bins of p
  TH1D   **fGeneralMV_MUBAC_MuonPhiPBins_Forward;    // Phi for all forward muons from chosen dimuon found by mv and mubac in bins of p

  TH1D    *fGeneralMV_MuonPt_Barrel;                 // Pt  for all barrel muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPt_Barrel;          // Pt  for all barrel muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPt_Barrel;           // Pt  for all barrel muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonEta_Barrel;                // Eta for all barrel muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonEta_Barrel;         // Eta for all barrel muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonEta_Barrel;          // Eta for all barrel muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonEtaPtBins_Barrel;          // Eta for all barrel muons from chosen dimuon found by mv in bins of pt
  TH1D   **fGeneralMV_BREMAT_MuonEtaPtBins_Barrel;   // Eta for all barrel muons from chosen dimuon found by mv and bremat in bins of pt
  TH1D   **fGeneralMV_MUBAC_MuonEtaPtBins_Barrel;    // Eta for all barrel muons from chosen dimuon found by mv and mubac in bins of pt
  TH1D    *fGeneralMV_MuonPhi_Barrel;                // Phi for all barrel muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPhi_Barrel;         // Phi for all barrel muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPhi_Barrel;          // Phi for all barrel muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonPhiPtBins_Barrel;          // Phi for all barrel muons from chosen dimuon found by mv in bins of pt
  TH1D   **fGeneralMV_BREMAT_MuonPhiPtBins_Barrel;   // Phi for all barrel muons from chosen dimuon found by mv and bremat in bins of pt
  TH1D   **fGeneralMV_MUBAC_MuonPhiPtBins_Barrel;    // Phi for all barrel muons from chosen dimuon found by mv and mubac in bins of pt

  TH1D    *fGeneralMV_MuonPz_Rear;                   // Pz  for all rear muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPz_Rear;            // Pz  for all rear muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPz_Rear;             // Pz  for all rear muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonPt_Rear;                   // Pt  for all rear muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPt_Rear;            // Pt  for all rear muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPt_Rear;             // Pt  for all rear muons from chosen dimuon found by mv and mubac
  TH1D    *fGeneralMV_MuonEta_Rear;                  // Eta for all rear muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonEta_Rear;           // Eta for all rear muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonEta_Rear;            // Eta for all rear muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonEtaPzBins_Rear;            // Eta for all rear muons from chosen dimuon found by mv in bins of pz
  TH1D   **fGeneralMV_BREMAT_MuonEtaPzBins_Rear;     // Eta for all rear muons from chosen dimuon found by mv and bremat in bins of pz
  TH1D   **fGeneralMV_MUBAC_MuonEtaPzBins_Rear;      // Eta for all rear muons from chosen dimuon found by mv and mubac in bins of pz
  TH1D    *fGeneralMV_MuonPhi_Rear;                  // Phi for all rear muons from chosen dimuon found by mv
  TH1D    *fGeneralMV_BREMAT_MuonPhi_Rear;           // Phi for all rear muons from chosen dimuon found by mv and bremat
  TH1D    *fGeneralMV_MUBAC_MuonPhi_Rear;            // Phi for all rear muons from chosen dimuon found by mv and mubac
  TH1D   **fGeneralMV_MuonPhiPzBins_Rear;            // Phi for all rear muons from chosen dimuon found by mv in bins of pz
  TH1D   **fGeneralMV_BREMAT_MuonPhiPzBins_Rear;     // Phi for all rear muons from chosen dimuon found by mv and bremat in bins of pz
  TH1D   **fGeneralMV_MUBAC_MuonPhiPzBins_Rear;      // Phi for all rear muons from chosen dimuon found by mv and mubac in bins of pz


  // control plots
  TH1D    *fControlNperEv_uncut;                     // uncut dimuon per event
  TH1D    *fControlDIMuonMass_uncut;                 // uncut dimuon mass
  TH1D    *fControlDIMuonMassLow_uncut;              // uncut low dimuon mass
  TH1D    *fControlDIMuonMassHigh_uncut;             // uncut high dimuon mass

  TH1D    *fControlMass_lu_is_uncut ;                // uncut dimuon mass low like sign isolated
  TH1D    *fControlMass_ll_is_uncut ;                // uncut dimuon mass low like sign isolated
  TH1D    *fControlMass_hu_is_uncut ;                // uncut dimuon mass high unlike sign isolated
  TH1D    *fControlMass_hl_is_uncut ;                // uncut dimuon mass high unlike sign isolated
  TH1D    *fControlMass_lu_nis_uncut;                // uncut dimuon mass low like sign non-isolated
  TH1D    *fControlMass_ll_nis_uncut;                // uncut dimuon mass low like sign non-isolated
  TH1D    *fControlMass_hu_nis_uncut;                // uncut dimuon mass high unlike sign non-isolated
  TH1D    *fControlMass_hl_nis_uncut;                // uncut dimuon mass high unlike sign non-isolated

  TH1D    *fControlDeltaR_uncut;                     // uncut dimuon delta R
  TH1D    *fControlDeltaR_lu_is_uncut;               // uncut dimuon delta R low mass, unlike sign
  TH1D    *fControlDeltaR_ll_is_uncut;               // uncut dimuon delta R low mass, unlike sign
  TH1D    *fControlDeltaR_hu_is_uncut;               // uncut dimuon delta R high mass, like sign 
  TH1D    *fControlDeltaR_hl_is_uncut;               // uncut dimuon delta R high mass, like sign 
  TH1D    *fControlDeltaR_lu_nis_uncut;              // uncut dimuon delta R low mass, unlike sign
  TH1D    *fControlDeltaR_ll_nis_uncut;              // uncut dimuon delta R low mass, unlike sign
  TH1D    *fControlDeltaR_hu_nis_uncut;              // uncut dimuon delta R high mass, like sign 
  TH1D    *fControlDeltaR_hl_nis_uncut;              // uncut dimuon delta R high mass, like sign 

  TH1D    *fControlDeltaPhi_uncut;                   // uncut dimuon delta Phi
  TH1D    *fControlDeltaPhi_lu_is_uncut;             // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fControlDeltaPhi_ll_is_uncut;             // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fControlDeltaPhi_hu_is_uncut;             // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fControlDeltaPhi_hl_is_uncut;             // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fControlDeltaPhi_lu_nis_uncut;            // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fControlDeltaPhi_ll_nis_uncut;            // uncut dimuon delta Phi low mass, unlike sign
  TH1D    *fControlDeltaPhi_hu_nis_uncut;            // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fControlDeltaPhi_hl_nis_uncut;            // uncut dimuon delta Phi high mass, like sign 
  TH1D    *fControlDeltaEta_uncut;                   // uncut dimuon delta Eta
  TH1D    *fControlDeltaTheta_uncut;                 // uncut dimuon delta Theta
  TH1D    *fControlPtAsymetry_uncut;                 // uncut dimuon pt asymetry
  TH1D    *fControlPtAsymetry_lu_is_uncut;           // uncut dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlPtAsymetry_ll_is_uncut;           // uncut dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlPtAsymetry_hu_is_uncut;           // uncut dimuon pt asymetry high mass, like sign 
  TH1D    *fControlPtAsymetry_hl_is_uncut;           // uncut dimuon pt asymetry high mass, like sign 
  TH1D    *fControlPtAsymetry_lu_nis_uncut;          // uncut dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlPtAsymetry_ll_nis_uncut;          // uncut dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlPtAsymetry_hu_nis_uncut;          // uncut dimuon pt asymetry high mass, like sign 
  TH1D    *fControlPtAsymetry_hl_nis_uncut;          // uncut dimuon pt asymetry high mass, like sign 
  TH1D    *fControlpt_uncut;                         // uncut dimuon pt
  TH1D    *fControlpt_lu_is_uncut;                   // uncut dimuon pt low mass, unlike sign
  TH1D    *fControlpt_ll_is_uncut;                   // uncut dimuon pt low mass, unlike sign
  TH1D    *fControlpt_hu_is_uncut;                   // uncut dimuon pt high mass, like sign 
  TH1D    *fControlpt_hl_is_uncut;                   // uncut dimuon pt high mass, like sign 
  TH1D    *fControlpt_lu_nis_uncut;                  // uncut dimuon pt low mass, unlike sign
  TH1D    *fControlpt_ll_nis_uncut;                  // uncut dimuon pt low mass, unlike sign
  TH1D    *fControlpt_hu_nis_uncut;                  // uncut dimuon pt high mass, like sign 
  TH1D    *fControlpt_hl_nis_uncut;                  // uncut dimuon pt high mass, like sign 
  TH1D    *fControldimupt_uncut;                     // uncut dimuon dimupt 
  TH1D    *fControldimupt_lu_is_uncut;               // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fControldimupt_ll_is_uncut;               // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fControldimupt_hu_is_uncut;               // uncut dimuon dimupt high mass, like sign 
  TH1D    *fControldimupt_hl_is_uncut;               // uncut dimuon dimupt high mass, like sign 
  TH1D    *fControldimupt_lu_nis_uncut;              // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fControldimupt_ll_nis_uncut;              // uncut dimuon dimupt low mass, unlike sign
  TH1D    *fControldimupt_hu_nis_uncut;              // uncut dimuon dimupt high mass, like sign 
  TH1D    *fControldimupt_hl_nis_uncut;              // uncut dimuon dimupt high mass, like sign 
  TH1D    *fControleta_uncut   ;                     // uncut dimuon eta
  TH1D    *fControleta_lu_is_uncut;                  // uncut dimuon eta low mass, unlike sign
  TH1D    *fControleta_ll_is_uncut;                  // uncut dimuon eta low mass, unlike sign
  TH1D    *fControleta_hu_is_uncut;                  // uncut dimuon eta high mass, like sign 
  TH1D    *fControleta_hl_is_uncut;                  // uncut dimuon eta high mass, like sign 
  TH1D    *fControleta_lu_nis_uncut;                 // uncut dimuon eta low mass, unlike sign
  TH1D    *fControleta_ll_nis_uncut;                 // uncut dimuon eta low mass, unlike sign
  TH1D    *fControleta_hu_nis_uncut;                 // uncut dimuon eta high mass, like sign 
  TH1D    *fControleta_hl_nis_uncut;                 // uncut dimuon eta high mass, like sign 

  TH1D    *fControlsqisol_10_uncut   ;               // uncut dimuon sqared isolation sum in DeltaR come of 1.0	      
  TH1D    *fControlsqisol_10_is_lu_uncut;            // uncut dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlsqisol_10_is_ll_uncut;            // uncut dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlsqisol_10_is_hu_uncut;            // uncut dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlsqisol_10_is_hl_uncut;            // uncut dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlsqisol_10_nis_lu_uncut;           // uncut dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlsqisol_10_nis_ll_uncut;           // uncut dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlsqisol_10_nis_hu_uncut;           // uncut dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlsqisol_10_nis_hl_uncut;           // uncut dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D    *fControlthrust_uncut   ;                  // thrust of event, classified by muon pair
  TH1D    *fControlthrust_is_lu_uncut;               // thrust of event, classified by muon pair  
  TH1D    *fControlthrust_is_ll_uncut;               // thrust of event, classified by muon pair  
  TH1D    *fControlthrust_is_hu_uncut;               // thrust of event, classified by muon pair
  TH1D    *fControlthrust_is_hl_uncut;               // thrust of event, classified by muon pair    
  TH1D    *fControlthrust_nis_lu_uncut;              // thrust of event, classified by muon pair
  TH1D    *fControlthrust_nis_ll_uncut;              // thrust of event, classified by muon pair
  TH1D    *fControlthrust_nis_hu_uncut;              // thrust of event, classified by muon pair
  TH1D    *fControlthrust_nis_hl_uncut;              // thrust of event, classified by muon pair 

  TH1D    *fControlsphericity_uncut  ;               // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_is_lu_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_is_ll_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_is_hu_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_is_hl_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_nis_lu_uncut;          // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_nis_ll_uncut;          // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_nis_hu_uncut;          // sphericity of event, classified by muon pair
  TH1D    *fControlsphericity_nis_hl_uncut;          // sphericity of event, classified by muon pair

  TH1D    *fControlisotropy_uncut  ;                 // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_is_lu_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_is_ll_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_is_hu_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_is_hl_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_nis_lu_uncut;            // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_nis_ll_uncut;            // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_nis_hu_uncut;            // isotropy of event, classified by muon pair
  TH1D    *fControlisotropy_nis_hl_uncut;            // isotropy of event, classified by muon pair
    
  TH1D    *fControlmultiplicity_uncut  ;             // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_is_lu_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_is_ll_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_is_hu_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_is_hl_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_nis_lu_uncut;        // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_nis_ll_uncut;        // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_nis_hu_uncut;        // multiplicity of event, classified by muon pair
  TH1D    *fControlmultiplicity_nis_hl_uncut;        // multiplicity of event, classified by muon pair

  TH1D    *fControlQ2Prime_uncut  ;                  // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_is_lu_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_is_ll_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_is_hu_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_is_hl_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_nis_lu_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_nis_ll_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlQ2Prime_nis_hu_uncut;             // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fControlQ2Prime_nis_hl_uncut;             // Virtuality Q'2 of event, classified by muon pair

  TH1D    *fControlNperEvGood;                       // good dimuon per event
  TH1D    *fControlGoodDIMuonMass;                   // good dimuon mass
  TH1D    *fControlGoodDIMuonMassLow;                // low good dimuon mass
  TH1D    *fControlGoodDIMuonMassHigh;               // high good dimuon mass

  TH1D    *fControlGoodMass_lu_is ;                  // dimuon mass low like sign isolated
  TH1D    *fControlGoodMass_ll_is ;                  // dimuon mass low like sign isolated
  TH1D    *fControlGoodMass_hu_is ;                  // dimuon mass high unlike sign isolated
  TH1D    *fControlGoodMass_hl_is ;                  // dimuon mass high unlike sign isolated
  TH1D    *fControlGoodMass_lu_nis;                  // dimuon mass low like sign non-isolated
  TH1D    *fControlGoodMass_ll_nis;                  // dimuon mass low like sign non-isolated
  TH1D    *fControlGoodMass_hu_nis;                  // dimuon mass high unlike sign non-isolated
  TH1D    *fControlGoodMass_hl_nis;                  // dimuon mass high unlike sign non-isolated

///
//   TH1D    *fControlGoodSubsets_test; 
  TH1D    *fControlGoodSubsets;                         // for Nevnt subsets
  TH1D    *fControlGoodSubsets_lu_is ;                  // 
  TH1D    *fControlGoodSubsets_ll_is ;                  // 
  TH1D    *fControlGoodSubsets_hu_is ;                  // 
  TH1D    *fControlGoodSubsets_hl_is ;                  // 
  TH1D    *fControlGoodSubsets_lu_nis;                  // 
  TH1D    *fControlGoodSubsets_ll_nis;                  // 
  TH1D    *fControlGoodSubsets_hu_nis;                  // 
  TH1D    *fControlGoodSubsets_hl_nis;                  // 

///

  TH1D    *fControlGoodDeltaR;                       // good dimuon delta R
  TH1D    *fControlGoodDeltaR_lu_is;                 // good dimuon delta R low mass, unlike sign
  TH1D    *fControlGoodDeltaR_ll_is;                 // good dimuon delta R low mass, unlike sign
  TH1D    *fControlGoodDeltaR_hu_is;                 // good dimuon delta R high mass, like sign 
  TH1D    *fControlGoodDeltaR_hl_is;                 // good dimuon delta R high mass, like sign 
  TH1D    *fControlGoodDeltaR_lu_nis;                // good dimuon delta R low mass, unlike sign
  TH1D    *fControlGoodDeltaR_ll_nis;                // good dimuon delta R low mass, unlike sign
  TH1D    *fControlGoodDeltaR_hu_nis;                // good dimuon delta R high mass, like sign 
  TH1D    *fControlGoodDeltaR_hl_nis;                // good dimuon delta R high mass, like sign 

  TH1D    *fControlGoodDeltaPhi;                     // good dimuon delta Phi
  TH1D    *fControlGoodDeltaPhi_lu_is;               // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlGoodDeltaPhi_ll_is;               // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlGoodDeltaPhi_hu_is;               // dimuon delta Phi high mass, like sign 
  TH1D    *fControlGoodDeltaPhi_hl_is;               // dimuon delta Phi high mass, like sign 
  TH1D    *fControlGoodDeltaPhi_lu_nis;              // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlGoodDeltaPhi_ll_nis;              // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlGoodDeltaPhi_hu_nis;              // dimuon delta Phi high mass, like sign 
  TH1D    *fControlGoodDeltaPhi_hl_nis;              // dimuon delta Phi high mass, like sign 

  TH1D    *fControlGoodDeltaEta;                     // good dimuon delta Eta
  TH1D    *fControlGoodDeltaTheta;                   // good dimuon delta Theta
  TH1D    *fControlGoodPtAsymetry;                   // good dimuon pt asymetry
  TH1D    *fControlGoodPtAsymetry_lu_is;             // good dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlGoodPtAsymetry_ll_is;             // good dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlGoodPtAsymetry_hu_is;             // good dimuon pt asymetry high mass, like sign 
  TH1D    *fControlGoodPtAsymetry_hl_is;             // good dimuon pt asymetry high mass, like sign 
  TH1D    *fControlGoodPtAsymetry_lu_nis;            // good dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlGoodPtAsymetry_ll_nis;            // good dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlGoodPtAsymetry_hu_nis;            // good dimuon pt asymetry high mass, like sign 
  TH1D    *fControlGoodPtAsymetry_hl_nis;            // good dimuon pt asymetry high mass, like sign 
  TH1D    *fControlGoodpt;                           // good dimuon pt
  TH1D    *fControlGoodpt_lu_is;                     // good dimuon pt low mass, unlike sign
  TH1D    *fControlGoodpt_ll_is;                     // good dimuon pt low mass, unlike sign
  TH1D    *fControlGoodpt_hu_is;                     // good dimuon pt high mass, like sign 
  TH1D    *fControlGoodpt_hl_is;                     // good dimuon pt high mass, like sign 
  TH1D    *fControlGoodpt_lu_nis;                    // good dimuon pt low mass, unlike sign
  TH1D    *fControlGoodpt_ll_nis;                    // good dimuon pt low mass, unlike sign
  TH1D    *fControlGoodpt_hu_nis;                    // good dimuon pt high mass, like sign 
  TH1D    *fControlGoodpt_hl_nis;                    // good dimuon pt high mass, like sign 
  TH1D    *fControlGooddimupt;                       // good dimuon dimupt 
  TH1D    *fControlGooddimupt_lu_is;                 // good dimuon dimupt low mass, unlike sign
  TH1D    *fControlGooddimupt_ll_is;                 // good dimuon dimupt low mass, unlike sign
  TH1D    *fControlGooddimupt_hu_is;                 // good dimuon dimupt high mass, like sign 
  TH1D    *fControlGooddimupt_hl_is;                 // good dimuon dimupt high mass, like sign 
  TH1D    *fControlGooddimupt_lu_nis;                // good dimuon dimupt low mass, unlike sign
  TH1D    *fControlGooddimupt_ll_nis;                // good dimuon dimupt low mass, unlike sign
  TH1D    *fControlGooddimupt_hu_nis;                // good dimuon dimupt high mass, like sign 
  TH1D    *fControlGooddimupt_hl_nis;                // good dimuon dimupt high mass, like sign 
  TH1D    *fControlGoodeta   ;                       // good dimuon eta
  TH1D    *fControlGoodeta_lu_is;                    // good dimuon eta low mass, unlike sign
  TH1D    *fControlGoodeta_ll_is;                    // good dimuon eta low mass, unlike sign
  TH1D    *fControlGoodeta_hu_is;                    // good dimuon eta high mass, like sign 
  TH1D    *fControlGoodeta_hl_is;                    // good dimuon eta high mass, like sign 
  TH1D    *fControlGoodeta_lu_nis;                   // good dimuon eta low mass, unlike sign
  TH1D    *fControlGoodeta_ll_nis;                   // good dimuon eta low mass, unlike sign
  TH1D    *fControlGoodeta_hu_nis;                   // good dimuon eta high mass, like sign 
  TH1D    *fControlGoodeta_hl_nis;                   // good dimuon eta high mass, like sign 

  TH1D    *fControlGoodsqisol_10   ;                 // good dimuon sqared isolation sum in DeltaR come of 1.0
  TH1D    *fControlGoodsqisol_10_is_lu;              // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlGoodsqisol_10_is_ll;              // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlGoodsqisol_10_is_hu;              // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlGoodsqisol_10_is_hl;              // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlGoodsqisol_10_nis_lu;             // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlGoodsqisol_10_nis_ll;             // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlGoodsqisol_10_nis_hu;             // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlGoodsqisol_10_nis_hl;             // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D    *fControlGoodthrust   ;                    // thrust of event, classified by muon pair
  TH1D    *fControlGoodthrust_is_lu;                 // thrust of event, classified by muon pair  
  TH1D    *fControlGoodthrust_is_ll;                 // thrust of event, classified by muon pair  
  TH1D    *fControlGoodthrust_is_hu;                 // thrust of event, classified by muon pair
  TH1D    *fControlGoodthrust_is_hl;                 // thrust of event, classified by muon pair    
  TH1D    *fControlGoodthrust_nis_lu;                // thrust of event, classified by muon pair
  TH1D    *fControlGoodthrust_nis_ll;                // thrust of event, classified by muon pair
  TH1D    *fControlGoodthrust_nis_hu;                // thrust of event, classified by muon pair
  TH1D    *fControlGoodthrust_nis_hl;                // thrust of event, classified by muon pair 

  TH1D    *fControlGoodsphericity  ;                 // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_is_lu;             // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_is_ll;             // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_is_hu;             // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_is_hl;             // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_nis_lu;            // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_nis_ll;            // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_nis_hu;            // sphericity of event, classified by muon pair
  TH1D    *fControlGoodsphericity_nis_hl;            // sphericity of event, classified by muon pair

  TH1D    *fControlGoodisotropy  ;                   // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_is_lu;               // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_is_ll;               // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_is_hu;               // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_is_hl;               // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_nis_lu;              // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_nis_ll;              // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_nis_hu;              // isotropy of event, classified by muon pair
  TH1D    *fControlGoodisotropy_nis_hl;              // isotropy of event, classified by muon pair
    
  TH1D    *fControlGoodmultiplicity  ;               // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_is_lu;           // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_is_ll;           // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_is_hu;           // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_is_hl;           // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_nis_lu;          // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_nis_ll;          // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_nis_hu;          // multiplicity of event, classified by muon pair
  TH1D    *fControlGoodmultiplicity_nis_hl;          // multiplicity of event, classified by muon pair

  TH1D    *fControlGoodQ2Prime  ;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_is_lu;                // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_is_ll;                // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_is_hu;                // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_is_hl;                // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_nis_lu;               // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_nis_ll;               // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlGoodQ2Prime_nis_hu;               // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fControlGoodQ2Prime_nis_hl;               // Virtuality Q'2 of event, classified by muon pair

  TH1D    *fControlNperEvChosen;                     // chosen dimuon per event
  TH1D    *fControlChosenDIMuonMass;                 // chosen dimuon mass
  TH1D    *fControlChosenDIMuonMassLow;              // low chosen dimuon mass
  TH1D    *fControlChosenDIMuonMassHigh;             // high chosen dimuon mass

  TH1D    *fControlChosenMass_lu_is ;                // dimuon mass low like sign isolated
  TH1D    *fControlChosenMass_ll_is ;                // dimuon mass low like sign isolated
  TH1D    *fControlChosenMass_hu_is ;                // dimuon mass high unlike sign isolated
  TH1D    *fControlChosenMass_hl_is ;                // dimuon mass high unlike sign isolated
  TH1D    *fControlChosenMass_lu_nis;                // dimuon mass low like sign non-isolated
  TH1D    *fControlChosenMass_ll_nis;                // dimuon mass low like sign non-isolated
  TH1D    *fControlChosenMass_hu_nis;                // dimuon mass high unlike sign non-isolated
  TH1D    *fControlChosenMass_hl_nis;                // dimuon mass high unlike sign non-isolated

  TH1D    *fControlChosenDeltaR;                     // chosen dimuon delta R
  TH1D    *fControlChosenDeltaR_lu_is;               // chosen dimuon delta R low mass, unlike sign
  TH1D    *fControlChosenDeltaR_ll_is;               // chosen dimuon delta R low mass, unlike sign
  TH1D    *fControlChosenDeltaR_hu_is;               // chosen dimuon delta R high mass, like sign 
  TH1D    *fControlChosenDeltaR_hl_is;               // chosen dimuon delta R high mass, like sign 
  TH1D    *fControlChosenDeltaR_lu_nis;              // chosen dimuon delta R low mass, unlike sign
  TH1D    *fControlChosenDeltaR_ll_nis;              // chosen dimuon delta R low mass, unlike sign
  TH1D    *fControlChosenDeltaR_hu_nis;              // chosen dimuon delta R high mass, like sign 
  TH1D    *fControlChosenDeltaR_hl_nis;              // chosen dimuon delta R high mass, like sign 

  TH1D    *fControlChosenDeltaPhi;                   // chosen dimuon delta Phi
  TH1D    *fControlChosenDeltaPhi_lu_is;             // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlChosenDeltaPhi_ll_is;             // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlChosenDeltaPhi_hu_is;             // dimuon delta Phi high mass, like sign 
  TH1D    *fControlChosenDeltaPhi_hl_is;             // dimuon delta Phi high mass, like sign 
  TH1D    *fControlChosenDeltaPhi_lu_nis;            // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlChosenDeltaPhi_ll_nis;            // dimuon delta Phi low mass, unlike sign
  TH1D    *fControlChosenDeltaPhi_hu_nis;            // dimuon delta Phi high mass, like sign 
  TH1D    *fControlChosenDeltaPhi_hl_nis;            // dimuon delta Phi high mass, like sign 
  TH1D    *fControlChosenDeltaEta;                   // chosen dimuon delta Eta
  TH1D    *fControlChosenDeltaTheta;                 // chosen dimuon delta Theta
  TH1D    *fControlChosenPtAsymetry;                 // chosen dimuon pt asymetry
  TH1D    *fControlChosenPtAsymetry_lu_is;           // chosen dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlChosenPtAsymetry_ll_is;           // chosen dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlChosenPtAsymetry_hu_is;           // chosen dimuon pt asymetry high mass, like sign 
  TH1D    *fControlChosenPtAsymetry_hl_is;           // chosen dimuon pt asymetry high mass, like sign 
  TH1D    *fControlChosenPtAsymetry_lu_nis;          // chosen dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlChosenPtAsymetry_ll_nis;          // chosen dimuon pt asymetry low mass, unlike sign
  TH1D    *fControlChosenPtAsymetry_hu_nis;          // chosen dimuon pt asymetry high mass, like sign 
  TH1D    *fControlChosenPtAsymetry_hl_nis;          // chosen dimuon pt asymetry high mass, like sign 
  TH1D    *fControlChosenpt;                         // chosen dimuon pt
  TH1D    *fControlChosenpt_lu_is;                   // chosen dimuon pt low mass, unlike sign
  TH1D    *fControlChosenpt_ll_is;                   // chosen dimuon pt low mass, unlike sign
  TH1D    *fControlChosenpt_hu_is;                   // chosen dimuon pt high mass, like sign 
  TH1D    *fControlChosenpt_hl_is;                   // chosen dimuon pt high mass, like sign 
  TH1D    *fControlChosenpt_lu_nis;                  // chosen dimuon pt low mass, unlike sign
  TH1D    *fControlChosenpt_ll_nis;                  // chosen dimuon pt low mass, unlike sign
  TH1D    *fControlChosenpt_hu_nis;                  // chosen dimuon pt high mass, like sign 
  TH1D    *fControlChosenpt_hl_nis;                  // chosen dimuon pt high mass, like sign 
  TH1D    *fControlChosendimupt;                     // chosen dimuon dimupt 
  TH1D    *fControlChosendimupt_lu_is;               // chosen dimuon dimupt low mass, unlike sign 
  TH1D    *fControlChosendimupt_ll_is;               // chosen dimuon dimupt low mass, unlike sign 
  TH1D    *fControlChosendimupt_hu_is;               // chosen dimuon dimupt high mass, like sign  
  TH1D    *fControlChosendimupt_hl_is;               // chosen dimuon dimupt high mass, like sign  
  TH1D    *fControlChosendimupt_lu_nis;              // chosen dimuon dimupt low mass, unlike sign 
  TH1D    *fControlChosendimupt_ll_nis;              // chosen dimuon dimupt low mass, unlike sign 
  TH1D    *fControlChosendimupt_hu_nis;              // chosen dimuon dimupt high mass, like sign  
  TH1D    *fControlChosendimupt_hl_nis;              // chosen dimuon dimupt high mass, like sign  
  TH1D    *fControlChoseneta   ;                     // chosen dimuon eta
  TH1D    *fControlChoseneta_lu_is;                  // chosen dimuon eta low mass, unlike sign
  TH1D    *fControlChoseneta_ll_is;                  // chosen dimuon eta low mass, unlike sign
  TH1D    *fControlChoseneta_hu_is;                  // chosen dimuon eta high mass, like sign 
  TH1D    *fControlChoseneta_hl_is;                  // chosen dimuon eta high mass, like sign 
  TH1D    *fControlChoseneta_lu_nis;                 // chosen dimuon eta low mass, unlike sign
  TH1D    *fControlChoseneta_ll_nis;                 // chosen dimuon eta low mass, unlike sign
  TH1D    *fControlChoseneta_hu_nis;                 // chosen dimuon eta high mass, like sign 
  TH1D    *fControlChoseneta_hl_nis;                 // chosen dimuon eta high mass, like sign 

  TH1D    *fControlChosensqisol_10   ;               // chosen dimuon sqared isolation sum in DeltaR come of 1.0  	      
  TH1D    *fControlChosensqisol_10_is_lu;            // chosen dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlChosensqisol_10_is_ll;            // chosen dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlChosensqisol_10_is_hu;            // chosen dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlChosensqisol_10_is_hl;            // chosen dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlChosensqisol_10_nis_lu;           // chosen dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlChosensqisol_10_nis_ll;           // chosen dimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fControlChosensqisol_10_nis_hu;           // chosen dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlChosensqisol_10_nis_hl;           // chosen dimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fControlChosenthrust   ;                  // thrust of event, classified by muon pair
  TH1D    *fControlChosenthrust_is_lu;               // thrust of event, classified by muon pair  
  TH1D    *fControlChosenthrust_is_ll;               // thrust of event, classified by muon pair  
  TH1D    *fControlChosenthrust_is_hu;               // thrust of event, classified by muon pair
  TH1D    *fControlChosenthrust_is_hl;               // thrust of event, classified by muon pair    
  TH1D    *fControlChosenthrust_nis_lu;              // thrust of event, classified by muon pair
  TH1D    *fControlChosenthrust_nis_ll;              // thrust of event, classified by muon pair
  TH1D    *fControlChosenthrust_nis_hu;              // thrust of event, classified by muon pair
  TH1D    *fControlChosenthrust_nis_hl;              // thrust of event, classified by muon pair 

  TH1D    *fControlChosensphericity  ;               // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_is_lu;           // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_is_ll;           // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_is_hu;           // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_is_hl;           // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_nis_lu;          // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_nis_ll;          // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_nis_hu;          // sphericity of event, classified by muon pair
  TH1D    *fControlChosensphericity_nis_hl;          // sphericity of event, classified by muon pair

  TH1D    *fControlChosenisotropy  ;                 // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_is_lu;             // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_is_ll;             // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_is_hu;             // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_is_hl;             // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_nis_lu;            // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_nis_ll;            // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_nis_hu;            // isotropy of event, classified by muon pair
  TH1D    *fControlChosenisotropy_nis_hl;            // isotropy of event, classified by muon pair
    
  TH1D    *fControlChosenmultiplicity  ;             // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_is_lu;         // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_is_ll;         // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_is_hu;         // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_is_hl;         // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_nis_lu;        // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_nis_ll;        // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_nis_hu;        // multiplicity of event, classified by muon pair
  TH1D    *fControlChosenmultiplicity_nis_hl;        // multiplicity of event, classified by muon pair
 
  TH1D    *fControlChosenQ2Prime  ;                  // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_is_lu;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_is_ll;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_is_hu;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_is_hl;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_nis_lu;             // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_nis_ll;             // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fControlChosenQ2Prime_nis_hu;             // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fControlChosenQ2Prime_nis_hl;             // Virtuality Q'2 of event, classified by muon pair



 public:
  GDIMuons();
  GDIMuons(Int_t dummy);
  virtual ~GDIMuons();

  virtual Bool_t   Reset();
  virtual Bool_t   Do();
  virtual Bool_t   Fill();

  virtual Bool_t   CheckMuonsAllCut(GDIMuon *match);
  virtual Bool_t   CheckMuonsMVCut(GDIMuon *match);
  virtual Bool_t   CheckInvMassCut(GDIMuon *match);
  virtual Bool_t   CheckSqSumIsolationCut(GDIMuon *match);
  virtual Bool_t   CheckDeltaRCut(GDIMuon *match);
  virtual Bool_t   CheckDeltaPhiCut(GDIMuon *match);
  virtual Bool_t   CheckDeltaThetaCut(GDIMuon *match);
  virtual Bool_t   CheckDeltaEtaCut(GDIMuon *match);
  virtual Bool_t   CheckPtAsymetryCut(GDIMuon *match);
  virtual Bool_t   CheckEtFractionHighCut(GDIMuon *match);
  virtual Bool_t   CheckEtFractionLowCut(GDIMuon *match);
  virtual Bool_t   CheckDifChargeCut(GDIMuon *match);
  virtual Bool_t   CheckCharmMCJpsiCut(GDIMuon *match);
  virtual Bool_t   CheckCharmMCPsiprimeCut(GDIMuon *match);
  virtual Bool_t   CheckTrigger(GDIMuon *match);
  virtual Bool_t   CheckAllCuts(GDIMuon *match, Int_t flag = 0 );
  virtual Bool_t   CheckBestDIMuon(GDIMuon *match, Int_t index);
  virtual Bool_t   DetSelectedCand(Int_t index);

  virtual Bool_t   FillHistos();
  virtual Bool_t   FillGeneral();
  virtual Bool_t   FillControl();

  virtual Bool_t   CreateControl();
  virtual Bool_t   CreateGeneral();

  virtual Bool_t   ObjectsFillHistos();

  virtual Bool_t   ObjectsFillGeneral(GDIMuon *dimuon); 
  virtual Bool_t   ObjectsFillControl(GDIMuon *dimuon); 

  virtual Bool_t   GetAllCuts();
 
  Int_t   Neventsubset;
  Int_t   temp_var;
  Int_t   Evnr_ck;

  Int_t   Nsubs_211;
  Int_t   Nsubs_212;
  Int_t   Nsubs_221;
  Int_t   Nsubs_222;

  Int_t   Nsubs_241;
  Int_t   Nsubs_242;
  Int_t   Nsubs_251;
  Int_t   Nsubs_252;

  Int_t   Nsubs_311;
  Int_t   Nsubs_312;
  Int_t   Nsubs_321;
  Int_t   Nsubs_322;

  Int_t   Nsubs_341;
  Int_t   Nsubs_342;
  Int_t   Nsubs_351;
  Int_t   Nsubs_352;

  Bool_t fix_chi2ndof;
	
  ///
  virtual Bool_t   GetJetMuonStatus(GDIMuon *match, TH1D *, Double_t); 
  virtual Bool_t   FillHistosSubsets(GDIMuon *match, TH1D *,TH1D *,TH1D *,TH1D *,TH1D *,TH1D *,TH1D *,TH1D *,TH1D *, Double_t);

  virtual Bool_t   SetSubsetlogic();

  ///
  virtual Bool_t   GetAllCuts_mod11();
  virtual Bool_t   GetAllCuts_mod12();
  virtual Bool_t   GetAllCuts_mod13();

  virtual Bool_t   GetAllCuts_mod21();
  virtual Bool_t   GetAllCuts_mod22();
  virtual Bool_t   GetAllCuts_mod23();
  virtual Bool_t   GetAllCuts_mod24();
  virtual Bool_t   GetAllCuts_mod25();
  virtual Bool_t   GetAllCuts_mod26();
  virtual Bool_t   GetAllCuts_mod27();
///
  virtual Bool_t   GetAllCuts_mod31();
  virtual Bool_t   GetAllCuts_mod32();
  virtual Bool_t   GetAllCuts_mod33();
  virtual Bool_t   GetAllCuts_mod34();
  virtual Bool_t   GetAllCuts_mod35();
  virtual Bool_t   GetAllCuts_mod36();
  virtual Bool_t   GetAllCuts_mod37();
///
  virtual Bool_t   GetAllCuts_mod41();
  virtual Bool_t   GetAllCuts_mod42();
  virtual Bool_t   GetAllCuts_mod43();
  virtual Bool_t   GetAllCuts_mod44();
  virtual Bool_t   GetAllCuts_mod45();
  virtual Bool_t   GetAllCuts_mod46();
  virtual Bool_t   GetAllCuts_mod47();

  virtual GDIMuon* GetDIMuon(Int_t id);

  virtual GDIMuon* GetChosen();

  virtual TString  PrintMessage(TString option);
  virtual Bool_t   Print(TString option);

  virtual Bool_t   FillPlotMuonPt(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonP(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonPz(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonEta(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonPhi(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonEtaPtBins(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonPhiPtBins(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonEtaPBins(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonPhiPBins(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonEtaPzBins(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonPhiPzBins(GDIMuon *dimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);

  virtual Bool_t   InitVariables();
  virtual Bool_t   InitArrays();



  inline virtual Int_t     GetNDIMuons()            { return fNDIMuons;                   }

  inline virtual Int_t     GetMuonP_NBins_MV()      { return fGeneralMuonP_NBins_MV;      }
  inline virtual Double_t* GetMuonP_Bins_MV()       { return fGeneralMuonP_Bins_MV;       }
  inline virtual Int_t     GetMuonP_NBins_MPMATCH() { return fGeneralMuonP_NBins_MPMATCH; }
  inline virtual Double_t* GetMuonP_Bins_MPMATCH()  { return fGeneralMuonP_Bins_MPMATCH;  }
  inline virtual Int_t     GetMuonP_NBins_MUBAC()   { return fGeneralMuonP_NBins_MUBAC;   }
  inline virtual Double_t* GetMuonP_Bins_MUBAC()    { return fGeneralMuonP_Bins_MUBAC;    }

  inline virtual Int_t     GetMuonPt_NBins_MV()     { return fGeneralMuonPt_NBins_MV;     }
  inline virtual Double_t* GetMuonPt_Bins_MV()      { return fGeneralMuonPt_Bins_MV;      }
  inline virtual Int_t     GetMuonPt_NBins_BREMAT() { return fGeneralMuonPt_NBins_BREMAT; }
  inline virtual Double_t* GetMuonPt_Bins_BREMAT()  { return fGeneralMuonPt_Bins_BREMAT;  }
  inline virtual Int_t     GetMuonPt_NBins_MUBAC()  { return fGeneralMuonPt_NBins_MUBAC;  }
  inline virtual Double_t* GetMuonPt_Bins_MUBAC()   { return fGeneralMuonPt_Bins_MUBAC;   }

  inline virtual Int_t     GetMuonPz_NBins_MV()     { return fGeneralMuonPz_NBins_MV;     }
  inline virtual Double_t* GetMuonPz_Bins_MV()      { return fGeneralMuonPz_Bins_MV;      }
  inline virtual Int_t     GetMuonPz_NBins_BREMAT() { return fGeneralMuonPz_NBins_BREMAT; }
  inline virtual Double_t* GetMuonPz_Bins_BREMAT()  { return fGeneralMuonPz_Bins_BREMAT;  }
  inline virtual Int_t     GetMuonPz_NBins_MUBAC()  { return fGeneralMuonPz_NBins_MUBAC;  }
  inline virtual Double_t* GetMuonPz_Bins_MUBAC()   { return fGeneralMuonPz_Bins_MUBAC;   }

 // TH1D    *fGeneralNeventsubset;                     // dimuon per event in diferent subsets

  ClassDef(GDIMuons,0) // match object for jet-muon match
};

R__EXTERN GDIMuons *gDIMuons;

#endif
