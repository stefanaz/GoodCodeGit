//
// GTriMuons.h
//
// $Author: dbot $
// $Date: 2010/04/15 7:36:45 $
// $Revision: 1.00 $
//

#ifndef GUT_GTriMuons
#define GUT_GTriMuons

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GTriMuons : public GPhysObj {

 private:

  TClonesArray   *fTriMuons;                                    // holds trimuon objects per event 
  Int_t           fNTriMuons;                                   // number of trimuons
  
  Bool_t          fInvMassCut;                                  // flag if one trimuon fulfills invarant mass cuts
  Bool_t          fSqSumIsolationCut;                           // flag if one trimuon fulfills requirement to be called isolated
  Bool_t          fDeltaRCut;                                   // flag if one trimuon fulfills delta R cut
  Bool_t          fDeltaPhiCut;                                 // flag if one trimuon fulfills delta phi cut
  Bool_t          fDeltaThetaCut;                               // flag if one trimuon fulfills delta theta cut
  Bool_t          fDeltaEtaCut;                                 // flag if one trimuon fulfills delta eta cut
  Bool_t          fPtAsymetryCut;                               // flag if one trimuon fulfills pt asymetry cut
  Bool_t          fEtFractionHighCut;                           // flag if one trimuon fulfills upper trimumass dependent et fraction cut
  Bool_t          fEtFractionLowCut;                            // flag if one trimuon fulfills lower et fraction cut
  Bool_t          fDifChargeCut;                                // flag if one trimuon fulfills different charge cut
  Bool_t          fCharmMCJpsiCut;                              // flag if muons in trimuon come from jpsi in ccbar MC
  Bool_t          fCharmMCPsiprimeCut;                          // flag if muons in trimuon come from psiprime in ccbar MC

  Bool_t          fAllCuts;                                     // flag if one trimuon fulfills all cuts

  Bool_t          fDoCalcIsolation;                             // flag if one trimuon fulfills all cuts to enable isolation calculation

  Int_t           fSelectedIndex;                               // index for determination of best trimuon fulfilling cuts

  Int_t           fNGoodTriMuons;                               // number of good trimuons per event 
  Int_t           fNChosenTriMuons;                             // number of chosen trimuons per event 
  
// general plots

  TH1D    *fGeneralNperEv_uncut;                      // uncut trimuon per event
  TH1D    *fGeneralTriMuonMass_uncut;                 // uncut trimuon mass
  TH1D    *fGeneralTriMuonMassLow_uncut;              // uncut low trimuon mass
  TH1D    *fGeneralTriMuonMassHigh_uncut;             // uncut high trimuon mass
  TH1D    *fGeneralTriMuonMass_LikeSign_uncut;        // uncut trimuon mass for like sign trimuons
  TH1D    *fGeneralTriMuonMassLow_LikeSign_uncut;     // uncut low trimuon mass for like sign trimuons
  TH1D    *fGeneralTriMuonMassHigh_LikeSign_uncut;    // uncut high trimuon mass for like sign trimuons
  TH1D    *fGeneralTriMuonMass_UnlikeSign_uncut;      // uncut trimuon mass for unlike sign trimuons
  TH1D    *fGeneralTriMuonMassLow_UnlikeSign_uncut;   // uncut low trimuon mass for unlike sign trimuons
  TH1D    *fGeneralTriMuonMassHigh_UnlikeSign_uncut;  // uncut high trimuon mass for unlike sign trimuons

  TH1D    *fGeneralMass_lu_is_uncut;                  // uncut trimuon mass low like sign isolated
  TH1D    *fGeneralMass_ll_is_uncut;                  // uncut trimuon mass low like sign isolated
  TH1D    *fGeneralMass_hu_is_uncut;                  // uncut trimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_hl_is_uncut;                  // uncut trimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_lu_nis_uncut;                 // uncut trimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_ll_nis_uncut;                 // uncut trimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_hu_nis_uncut;                 // uncut trimuon mass high unlike sign non-isolated
  TH1D    *fGeneralMass_hl_nis_uncut;                 // uncut trimuon mass high unlike sign non-isolated

  TH1D    *fGeneralDeltaR_uncut;                      // uncut trimuon delta R
  TH1D    *fGeneralDeltaR_lu_is_uncut;                // uncut trimuon delta R  low mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_is_uncut;                // uncut trimuon delta R  low mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_is_uncut;                // uncut trimuon delta R  high mass, like sign 
  TH1D    *fGeneralDeltaR_hl_is_uncut;                // uncut trimuon delta R  high mass, like sign 
  TH1D    *fGeneralDeltaR_lu_nis_uncut;               // uncut trimuon delta R  low mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_nis_uncut;               // uncut trimuon delta R  low mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_nis_uncut;               // uncut trimuon delta R  high mass, like sign 
  TH1D    *fGeneralDeltaR_hl_nis_uncut;               // uncut trimuon delta R  high mass, like sign 

  TH1D    *fGeneralDeltaPhi_uncut;                    // uncut trimuon delta Phi
  TH1D    *fGeneralDeltaPhi_lu_is_uncut;              // uncut trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_is_uncut;              // uncut trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_is_uncut;              // uncut trimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_is_uncut;              // uncut trimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_lu_nis_uncut;             // uncut trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_nis_uncut;             // uncut trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_nis_uncut;             // uncut trimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_nis_uncut;             // uncut trimuon delta Phi high mass, like sign 

  TH1D    *fGeneralDeltaEta_uncut;                    // uncut trimuon delta Eta
  TH1D    *fGeneralDeltaTheta_uncut;                  // uncut trimuon delta Theta

  TH1D    *fGeneraltrimuphi_uncut;                    // uncut trimuon trimuphi
  TH1D    *fGeneraltrimuphi_lu_is_uncut;              // uncut trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_ll_is_uncut;              // uncut trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_hu_is_uncut;              // uncut trimuon trimuphi high mass, like sign	
  TH1D    *fGeneraltrimuphi_hl_is_uncut;              // uncut trimuon trimuphi high mass, like sign 
  TH1D    *fGeneraltrimuphi_lu_nis_uncut;             // uncut trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_ll_nis_uncut;             // uncut trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_hu_nis_uncut;             // uncut trimuon trimuphi high mass, like sign	
  TH1D    *fGeneraltrimuphi_hl_nis_uncut;             // uncut trimuon trimuphi high mass, like sign 

  TH1D    *fGeneraltrimueta_uncut;                    // uncut trimuon trimueta
  TH1D    *fGeneraltrimueta_lu_is_uncut;              // uncut trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_ll_is_uncut;              // uncut trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_hu_is_uncut;              // uncut trimuon trimueta high mass, like sign	
  TH1D    *fGeneraltrimueta_hl_is_uncut;              // uncut trimuon trimueta high mass, like sign 
  TH1D    *fGeneraltrimueta_lu_nis_uncut;             // uncut trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_ll_nis_uncut;             // uncut trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_hu_nis_uncut;             // uncut trimuon trimueta high mass, like sign	
  TH1D    *fGeneraltrimueta_hl_nis_uncut;             // uncut trimuon trimueta high mass, like sign 

  TH1D    *fGeneralPtAsymetry_uncut;                  // uncut trimuon pt Asymetry
  TH1D    *fGeneralPtAsymetry_lu_is_uncut;            // uncut trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_is_uncut;            // uncut trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_is_uncut;            // uncut trimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_is_uncut;            // uncut trimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_lu_nis_uncut;           // uncut trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_nis_uncut;           // uncut trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_nis_uncut;           // uncut trimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_nis_uncut;           // uncut trimuon pt Asymetry high mass, like sign 

  TH1D    *fGeneralpt_uncut;                          // uncut trimuon pt
  TH1D    *fGeneralpt_lu_is_uncut;                    // uncut trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_is_uncut;                    // uncut trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_is_uncut;                    // uncut trimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_is_uncut;                    // uncut trimuon pt high mass, like sign 
  TH1D    *fGeneralpt_lu_nis_uncut;                   // uncut trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_nis_uncut;                   // uncut trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_nis_uncut;                   // uncut trimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_nis_uncut;                   // uncut trimuon pt high mass, like sign 

  TH1D    *fGeneraleta_uncut;                         // uncut trimuon eta
  TH1D    *fGeneraleta_lu_is_uncut;                   // uncut trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_is_uncut;                   // uncut trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_is_uncut;                   // uncut trimuon eta high mass, like sign
  TH1D    *fGeneraleta_hl_is_uncut;                   // uncut trimuon eta high mass, like sign  
  TH1D    *fGeneraleta_lu_nis_uncut;                  // uncut trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_nis_uncut;                  // uncut trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_nis_uncut;                  // uncut trimuon eta high mass, like sign
  TH1D    *fGeneraleta_hl_nis_uncut;                  // uncut trimuon eta high mass, like sign  

  TH1D    *fGeneralphi_uncut;                         // uncut single muon phi
  TH1D    *fGeneralphi_lu_is_uncut;                   // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_is_uncut;                   // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_is_uncut;                   // uncut single muon phi high mass, like sign
  TH1D    *fGeneralphi_hl_is_uncut;                   // uncut single muon phi high mass, like sign  
  TH1D    *fGeneralphi_lu_nis_uncut;                  // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_nis_uncut;                  // uncut single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_nis_uncut;                  // uncut single muon phi high mass, like sign
  TH1D    *fGeneralphi_hl_nis_uncut;                  // uncut single muon phi high mass, like sign  

  TH1D    *fGeneralmuqual_uncut;                      // uncut single muon muqual
  TH1D    *fGeneralmuqual_lu_is_uncut;                // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_is_uncut;                // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_is_uncut;                // uncut single muon muqual high mass, like sign
  TH1D    *fGeneralmuqual_hl_is_uncut;                // uncut single muon muqual high mass, like sign  
  TH1D    *fGeneralmuqual_lu_nis_uncut;               // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_nis_uncut;               // uncut single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_nis_uncut;               // uncut single muon muqual high mass, like sign
  TH1D    *fGeneralmuqual_hl_nis_uncut;               // uncut single muon muqual high mass, like sign  

  TH1D    *fGeneralImpact2D_uncut  ;                  // uncut trimuon 2D Impact Parameter
  TH1D    *fGeneralImpact2D_is_lu_uncut;              // uncut trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_is_ll_uncut;              // uncut trimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_is_hu_uncut;              // uncut trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_is_hl_uncut;              // uncut trimuon 2D Impact Parameter, high mass, like sign
  TH1D    *fGeneralImpact2D_nis_lu_uncut;             // uncut trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_ll_uncut;             // uncut trimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_nis_hu_uncut;             // uncut trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_hl_uncut;             // uncut trimuon 2D Impact Parameter, high mass, like sign

  TH1D    *fGeneralsqisol_10_uncut   ;                // trimuon sqared isolation sum in DeltaR come of 1.0	      	    
  TH1D    *fGeneralsqisol_10_is_lu_uncut;             // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_ll_uncut;             // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_hu_uncut;             // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_is_hl_uncut;             // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_lu_uncut;            // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_ll_uncut;            // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_hu_uncut;            // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_hl_uncut;            // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D    *fGeneralthrust_uncut   ;                   // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_lu_uncut;                // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_ll_uncut;                // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_hu_uncut;                // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_hl_uncut;                // thrust of event, classified by muon pair    
  TH1D    *fGeneralthrust_nis_lu_uncut;               // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_ll_uncut;               // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hu_uncut;               // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hl_uncut;               // thrust of event, classified by muon pair 

  TH1D    *fGeneralsphericity_uncut  ;                // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_lu_uncut;            // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_ll_uncut;            // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hu_uncut;            // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hl_uncut;            // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_lu_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_ll_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hu_uncut;           // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hl_uncut;           // sphericity of event, classified by muon pair

  TH1D    *fGeneralisotropy_uncut  ;                  // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_lu_uncut;              // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_ll_uncut;              // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hu_uncut;              // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hl_uncut;              // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_lu_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_ll_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hu_uncut;             // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hl_uncut;             // isotropy of event, classified by muon pair
    
  TH1D    *fGeneralmultiplicity_uncut  ;              // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_lu_uncut;          // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_ll_uncut;          // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hu_uncut;          // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hl_uncut;          // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_lu_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_ll_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hu_uncut;         // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hl_uncut;         // multiplicity of event, classified by muon pair

  TH1D    *fGeneralQ2Prime_uncut  ;                   // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_lu_uncut;               // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_ll_uncut;               // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hu_uncut;               // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hl_uncut;               // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_lu_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_ll_uncut;              // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_hu_uncut;              // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fGeneralQ2Prime_nis_hl_uncut;              // Virtuality Q'2 of event, classified by muon pair

  TH1D    *fGeneralcal_et_uncut   ;                   // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_lu_uncut;                // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_ll_uncut;                // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_hu_uncut;                // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_hl_uncut;                // cal_et of event, classified by muon pair    
  TH1D    *fGeneralcal_et_nis_lu_uncut;               // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_ll_uncut;               // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hu_uncut;               // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hl_uncut;               // cal_et of event, classified by muon pair 

  TH1D    *fGeneraletex2ir_uncut   ;                  // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_lu_uncut;               // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_ll_uncut;               // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_hu_uncut;               // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_hl_uncut;               // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraletex2ir_nis_lu_uncut;              // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_ll_uncut;              // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hu_uncut;              // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hl_uncut;              // etex2ir of event, classified by muon pair 

  TH1D    *fGeneralcal_et_m_et2ir_uncut   ;           // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_lu_uncut;        // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_ll_uncut;        // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_hu_uncut;        // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_hl_uncut;        // cal_et_m_et2ir of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_et2ir_nis_lu_uncut;       // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_ll_uncut;       // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hu_uncut;       // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hl_uncut;       // cal_et_m_et2ir of event, classified by muon pair 

  TH1D    *fGeneralcal_et_m_cal_et_10_uncut   ;       // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_lu_uncut;    // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_ll_uncut;    // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hu_uncut;    // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hl_uncut;    // cal_et_m_cal_et_10 of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_lu_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_ll_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hu_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hl_uncut;   // cal_et_m_cal_et_10 of event, classified by muon pair 

  TH1D    *fGeneralTriggerType_uncut;                 // uncut trigger type

  TH1D    *fGeneralNperEv;                            // trimuon per event
  TH1D    *fGeneralTriMuonMass;                       // trimuon mass
  TH1D    *fGeneralTriMuonMassLow;                    // low trimuon mass
  TH1D    *fGeneralTriMuonMassHigh;                   // high trimuon mass
  TH1D    *fGeneralTriMuonMass_LikeSign;              // trimuon mass for like sign trimuons
  TH1D    *fGeneralTriMuonMassLow_LikeSign;           // low trimuon mass for like sign trimuons
  TH1D    *fGeneralTriMuonMassHigh_LikeSign;          // high trimuon mass for like sign trimuons
  TH1D    *fGeneralTriMuonMass_UnlikeSign;            // trimuon mass for unlike sign trimuons
  TH1D    *fGeneralTriMuonMassLow_UnlikeSign;         // low trimuon mass for unlike sign trimuons
  TH1D    *fGeneralTriMuonMassHigh_UnlikeSign;        // high trimuon mass for unlike sign trimuons

  TH1D    *fGeneralMass_lu_is ;                       // trimuon mass low like sign isolated
  TH1D    *fGeneralMass_ll_is ;                       // trimuon mass low like sign isolated
  TH1D    *fGeneralMass_hu_is ;                       // trimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_hl_is ;                       // trimuon mass high unlike sign isolated
  TH1D    *fGeneralMass_lu_nis;                       // trimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_ll_nis;                       // trimuon mass low like sign non-isolated
  TH1D    *fGeneralMass_hu_nis;                       // trimuon mass high unlike sign non-isolated
  TH1D    *fGeneralMass_hl_nis;                       // trimuon mass high unlike sign non-isolated

  TH1D    *fGeneralDeltaR;                            // trimuon delta R
  TH1D    *fGeneralDeltaR_lu_is;                      // trimuon delta R low mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_is;                      // trimuon delta R low mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_is;                      // trimuon delta R high mass, like sign 
  TH1D    *fGeneralDeltaR_hl_is;                      // trimuon delta R high mass, like sign 
  TH1D    *fGeneralDeltaR_lu_nis;                     // trimuon delta R low mass, unlike sign
  TH1D    *fGeneralDeltaR_ll_nis;                     // trimuon delta R low mass, unlike sign
  TH1D    *fGeneralDeltaR_hu_nis;                     // trimuon delta R high mass, like sign 
  TH1D    *fGeneralDeltaR_hl_nis;                     // trimuon delta R high mass, like sign 

  TH1D    *fGeneralDeltaPhi;                          // trimuon delta Phi
  TH1D    *fGeneralDeltaPhi_lu_is;                    // trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_is;                    // trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_is;                    // trimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_is;                    // trimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_lu_nis;                   // trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_ll_nis;                   // trimuon delta Phi low mass, unlike sign
  TH1D    *fGeneralDeltaPhi_hu_nis;                   // trimuon delta Phi high mass, like sign 
  TH1D    *fGeneralDeltaPhi_hl_nis;                   // trimuon delta Phi high mass, like sign 

  TH1D    *fGeneralDeltaEta;                          // trimuon delta Eta
  TH1D    *fGeneralDeltaTheta;                        // trimuon delta Theta

  TH1D    *fGeneraltrimuphi;                          // trimuon trimuphi
  TH1D    *fGeneraltrimuphi_lu_is;                    // trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_ll_is;                    // trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_hu_is;                    // trimuon trimuphi high mass, like sign	
  TH1D    *fGeneraltrimuphi_hl_is;                    // trimuon trimuphi high mass, like sign 
  TH1D    *fGeneraltrimuphi_lu_nis;                   // trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_ll_nis;                   // trimuon trimuphi low mass, unlike sign
  TH1D    *fGeneraltrimuphi_hu_nis;                   // trimuon trimuphi high mass, like sign	
  TH1D    *fGeneraltrimuphi_hl_nis;                   // trimuon trimuphi high mass, like sign 

  TH1D    *fGeneraltrimueta;                          // trimuon trimueta
  TH1D    *fGeneraltrimueta_lu_is;                    // trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_ll_is;                    // trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_hu_is;                    // trimuon trimueta high mass, like sign	
  TH1D    *fGeneraltrimueta_hl_is;                    // trimuon trimueta high mass, like sign 
  TH1D    *fGeneraltrimueta_lu_nis;                   // trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_ll_nis;                   // trimuon trimueta low mass, unlike sign
  TH1D    *fGeneraltrimueta_hu_nis;                   // trimuon trimueta high mass, like sign	
  TH1D    *fGeneraltrimueta_hl_nis;                   // trimuon trimueta high mass, like sign 

  TH1D    *fGeneralPtAsymetry;                        // trimuon pt Asymetry
  TH1D    *fGeneralPtAsymetry_lu_is;                  // trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_is;                  // trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_is;                  // trimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_is;                  // trimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_lu_nis;                 // trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_ll_nis;                 // trimuon pt Asymetry low mass, unlike sign
  TH1D    *fGeneralPtAsymetry_hu_nis;                 // trimuon pt Asymetry high mass, like sign 
  TH1D    *fGeneralPtAsymetry_hl_nis;                 // trimuon pt Asymetry high mass, like sign 

  TH1D    *fGeneralpt;                                // trimuon pt
  TH1D    *fGeneralpt_lu_is;                          // trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_is;                          // trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_is;                          // trimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_is;                          // trimuon pt high mass, like sign 
  TH1D    *fGeneralpt_lu_nis;                         // trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_ll_nis;                         // trimuon pt low mass, unlike sign
  TH1D    *fGeneralpt_hu_nis;                         // trimuon pt high mass, like sign	
  TH1D    *fGeneralpt_hl_nis;                         // trimuon pt high mass, like sign 

  TH1D    *fGeneraleta;                               // trimuon eta
  TH1D    *fGeneraleta_lu_is;                         // trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_is;                         // trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_is;                         // trimuon eta high mass, like sign	
  TH1D    *fGeneraleta_hl_is;                         // trimuon eta high mass, like sign 
  TH1D    *fGeneraleta_lu_nis;                        // trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_ll_nis;                        // trimuon eta low mass, unlike sign
  TH1D    *fGeneraleta_hu_nis;                        // trimuon eta high mass, like sign	
  TH1D    *fGeneraleta_hl_nis;                        // trimuon eta high mass, like sign 

  TH1D    *fGeneralphi;                               // trimuon phi
  TH1D    *fGeneralphi_lu_is;                         // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_is;                         // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_is;                         // single muon phi high mass, like sign	
  TH1D    *fGeneralphi_hl_is;                         // single muon phi high mass, like sign 
  TH1D    *fGeneralphi_lu_nis;                        // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_ll_nis;                        // single muon phi low mass, unlike sign
  TH1D    *fGeneralphi_hu_nis;                        // single muon phi high mass, like sign	
  TH1D    *fGeneralphi_hl_nis;                        // single muon phi high mass, like sign 

  TH1D    *fGeneralmuqual;                            // single muon muqual
  TH1D    *fGeneralmuqual_lu_is;                      // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_is;                      // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_is;                      // single muon muqual high mass, like sign	
  TH1D    *fGeneralmuqual_hl_is;                      // single muon muqual high mass, like sign 
  TH1D    *fGeneralmuqual_lu_nis;                     // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_ll_nis;                     // single muon muqual low mass, unlike sign
  TH1D    *fGeneralmuqual_hu_nis;                     // single muon muqual high mass, like sign	
  TH1D    *fGeneralmuqual_hl_nis;                     // single muon muqual high mass, like sign 

  TH1D    *fGeneralImpact2D  ;                        // trimuon 2D Impact Parameter
  TH1D    *fGeneralImpact2D_is_lu;                    // trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_is_ll;                    // trimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_is_hu;                    // trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_is_hl;                    // trimuon 2D Impact Parameter, high mass, like sign
  TH1D    *fGeneralImpact2D_nis_lu;                   // trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_ll;                   // trimuon 2D Impact Parameter, low mass, like sign
  TH1D    *fGeneralImpact2D_nis_hu;                   // trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D    *fGeneralImpact2D_nis_hl;                   // trimuon 2D Impact Parameter, high mass, like sign

  TH1D    *fGeneralsqisol_10   ;                      // trimuon sqared isolation sum in DeltaR come of 1.0	      	     
  TH1D    *fGeneralsqisol_10_is_lu;                   // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_ll;                   // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_is_hu;                   // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_is_hl;                   // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_lu;                  // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_ll;                  // trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D    *fGeneralsqisol_10_nis_hu;                  // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D    *fGeneralsqisol_10_nis_hl;                  // trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D    *fGeneralthrust   ;                         // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_lu;                      // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_ll;                      // thrust of event, classified by muon pair  
  TH1D    *fGeneralthrust_is_hu;                      // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_is_hl;                      // thrust of event, classified by muon pair    
  TH1D    *fGeneralthrust_nis_lu;                     // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_ll;                     // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hu;                     // thrust of event, classified by muon pair
  TH1D    *fGeneralthrust_nis_hl;                     // thrust of event, classified by muon pair 

  TH1D    *fGeneralsphericity  ;                      // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_lu;                  // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_ll;                  // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hu;                  // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_is_hl;                  // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_lu;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_ll;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hu;                 // sphericity of event, classified by muon pair
  TH1D    *fGeneralsphericity_nis_hl;                 // sphericity of event, classified by muon pair

  TH1D    *fGeneralisotropy  ;                        // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_lu;                    // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_ll;                    // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hu;                    // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_is_hl;                    // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_lu;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_ll;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hu;                   // isotropy of event, classified by muon pair
  TH1D    *fGeneralisotropy_nis_hl;                   // isotropy of event, classified by muon pair
    
  TH1D    *fGeneralmultiplicity  ;                    // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_lu;                // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_ll;                // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hu;                // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_is_hl;                // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_lu;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_ll;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hu;               // multiplicity of event, classified by muon pair
  TH1D    *fGeneralmultiplicity_nis_hl;               // multiplicity of event, classified by muon pair

  TH1D    *fGeneralQ2Prime  ;                         // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_lu;                     // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_ll;                     // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hu;                     // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_is_hl;                     // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_lu;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_ll;                    // Virtuality Q'2 of event, classified by muon pair
  TH1D    *fGeneralQ2Prime_nis_hu;                    // Virtuality Q'2 of event, classified by muon pair 
  TH1D    *fGeneralQ2Prime_nis_hl;                    // Virtuality Q'2 of event, classified by muon pair

  TH1D    *fGeneralempz   ;                           // empz of event, classified by muon pair
  TH1D    *fGeneralempz_is_lu;                        // empz of event, classified by muon pair  
  TH1D    *fGeneralempz_is_ll;                        // empz of event, classified by muon pair  
  TH1D    *fGeneralempz_is_hu;                        // empz of event, classified by muon pair
  TH1D    *fGeneralempz_is_hl;                        // empz of event, classified by muon pair    
  TH1D    *fGeneralempz_nis_lu;                       // empz of event, classified by muon pair
  TH1D    *fGeneralempz_nis_ll;                       // empz of event, classified by muon pair
  TH1D    *fGeneralempz_nis_hu;                       // empz of event, classified by muon pair
  TH1D    *fGeneralempz_nis_hl;                       // empz of event, classified by muon pair 

  TH1D    *fGeneralcal_et   ;                         // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_lu;                      // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_ll;                      // cal_et of event, classified by muon pair  
  TH1D    *fGeneralcal_et_is_hu;                      // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_is_hl;                      // cal_et of event, classified by muon pair    
  TH1D    *fGeneralcal_et_nis_lu;                     // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_ll;                     // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hu;                     // cal_et of event, classified by muon pair
  TH1D    *fGeneralcal_et_nis_hl;                     // cal_et of event, classified by muon pair 

  TH1D    *fGeneraletex2ir   ;                        // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_lu;                     // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_ll;                     // etex2ir of event, classified by muon pair  
  TH1D    *fGeneraletex2ir_is_hu;                     // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_is_hl;                     // etex2ir of event, classified by muon pair    
  TH1D    *fGeneraletex2ir_nis_lu;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_ll;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hu;                    // etex2ir of event, classified by muon pair
  TH1D    *fGeneraletex2ir_nis_hl;                    // etex2ir of event, classified by muon pair 

  TH1D    *fGeneraltrimuxsecpt       ;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_is_lu ;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_is_ll ;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_is_hu ;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_is_hl ;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_nis_lu;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_nis_ll;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_nis_hu;                // plot for trimuon muon trimuxsec in pt
  TH1D    *fGeneraltrimuxsecpt_nis_hl;

  TH1D    *fGeneraltrimuxseceta       ;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_is_lu ;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_is_ll ;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_is_hu ;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_is_hl ;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_nis_lu;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_nis_ll;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_nis_hu;               // plot for trimuon muon trimuxsec in eta
  TH1D    *fGeneraltrimuxseceta_nis_hl;               // plot for trimuon muon trimuxsec in eta

  TH1D    *fGeneraltrimuxsecfinders       ;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_is_lu ;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_is_ll ;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_is_hu ;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_is_hl ;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_nis_lu;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_nis_ll;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_nis_hu;           // plot for trimuon muon trimuxsec in finders
  TH1D    *fGeneraltrimuxsecfinders_nis_hl;           // plot for trimuon muon trimuxsec in finders

  TH1D    *fGeneraltrimuxsecdr       ;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_is_lu ;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_is_ll ;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_is_hu ;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_is_hl ;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_nis_lu;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_nis_ll;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_nis_hu;                // plot for trimuon muon trimuxsec in dr
  TH1D    *fGeneraltrimuxsecdr_nis_hl;

  TH1D    *fGeneraltrimuxsecdphi       ;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_is_lu ;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_is_ll ;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_is_hu ;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_is_hl ;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_nis_lu;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_nis_ll;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_nis_hu;              // plot for trimuon muon trimuxsec in dphi
  TH1D    *fGeneraltrimuxsecdphi_nis_hl;

  TH1D    *fGeneraltrimuxsecptb       ;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_is_lu ;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_is_ll ;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_is_hu ;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_is_hl ;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_nis_lu;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_nis_ll;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_nis_hu;               // plot for trimuon muon trimuxsec in ptb
  TH1D    *fGeneraltrimuxsecptb_nis_hl;               // plot for trimuon muon trimuxsec in ptb

  TH1D    *fGeneraltrimuxsecptb_sameb       ;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_is_lu ;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_is_ll ;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_is_hu ;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_is_hl ;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_nis_lu;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_nis_ll;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_nis_hu;         // plot for trimuon muon trimuxsec in ptb_sameb
  TH1D    *fGeneraltrimuxsecptb_sameb_nis_hl;

  TH1D    *fGeneraltrimuxsecptb_diffb       ;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_is_lu ;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_is_ll ;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_is_hu ;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_is_hl ;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_nis_lu;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_nis_ll;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_nis_hu;         // plot for trimuon muon trimuxsec in ptb_diffb
  TH1D    *fGeneraltrimuxsecptb_diffb_nis_hl;

  TH1D    *fGeneraltrimuxsecptb_samecone       ;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_is_lu ;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_is_ll ;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_is_hu ;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_is_hl ;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_nis_lu;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_nis_ll;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_nis_hu;      // plot for trimuon muon trimuxsec in ptb_samecone
  TH1D    *fGeneraltrimuxsecptb_samecone_nis_hl;

  TH1D    *fGeneraltrimuxsecptb_asym       ;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_is_lu ;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_is_ll ;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_is_hu ;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_is_hl ;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_nis_lu;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_nis_ll;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_nis_hu;          // plot for trimuon muon trimuxsec in ptb_asym
  TH1D    *fGeneraltrimuxsecptb_asym_nis_hl;

  TH1D    *fGeneralcal_et_m_et2ir   ;                 // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_lu;              // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_ll;              // cal_et_m_et2ir of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_et2ir_is_hu;              // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_is_hl;              // cal_et_m_et2ir of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_et2ir_nis_lu;             // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_ll;             // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hu;             // cal_et_m_et2ir of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_et2ir_nis_hl;             // cal_et_m_et2ir of event, classified by muon pair 

  TH1D    *fGeneralcal_et_m_cal_et_10   ;             // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_lu;          // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_ll;          // cal_et_m_cal_et_10 of event, classified by muon pair  
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hu;          // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_is_hl;          // cal_et_m_cal_et_10 of event, classified by muon pair    
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_lu;         // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_ll;         // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hu;         // cal_et_m_cal_et_10 of event, classified by muon pair
  TH1D    *fGeneralcal_et_m_cal_et_10_nis_hl;         // cal_et_m_cal_et_10 of event, classified by muon pair 

  TH1D  *fGeneralTriggerType;                    // trigger type

// control plots
  TH1D  *fControlNperEv_uncut;                    // uncut trimuon per event
  TH1D  *fControlTriMuonMass_uncut;               // uncut trimuon mass
  TH1D  *fControlTriMuonMassLow_uncut;            // uncut low trimuon mass
  TH1D  *fControlTriMuonMassHigh_uncut;           // uncut high trimuon mass

  TH1D  *fControlMass_lu_is_uncut ;               // uncut trimuon mass low like sign isolated
  TH1D  *fControlMass_ll_is_uncut ;               // uncut trimuon mass low like sign isolated
  TH1D  *fControlMass_hu_is_uncut ;               // uncut trimuon mass high unlike sign isolated
  TH1D  *fControlMass_hl_is_uncut ;               // uncut trimuon mass high unlike sign isolated
  TH1D  *fControlMass_lu_nis_uncut;               // uncut trimuon mass low like sign non-isolated
  TH1D  *fControlMass_ll_nis_uncut;               // uncut trimuon mass low like sign non-isolated
  TH1D  *fControlMass_hu_nis_uncut;               // uncut trimuon mass high unlike sign non-isolated
  TH1D  *fControlMass_hl_nis_uncut;               // uncut trimuon mass high unlike sign non-isolated

  TH1D  *fControlDeltaR_uncut;                    // uncut trimuon delta R
  TH1D  *fControlDeltaR_lu_is_uncut;              // uncut trimuon delta R low mass, unlike sign
  TH1D  *fControlDeltaR_ll_is_uncut;              // uncut trimuon delta R low mass, unlike sign
  TH1D  *fControlDeltaR_hu_is_uncut;              // uncut trimuon delta R high mass, like sign 
  TH1D  *fControlDeltaR_hl_is_uncut;              // uncut trimuon delta R high mass, like sign 
  TH1D  *fControlDeltaR_lu_nis_uncut;             // uncut trimuon delta R low mass, unlike sign
  TH1D  *fControlDeltaR_ll_nis_uncut;             // uncut trimuon delta R low mass, unlike sign
  TH1D  *fControlDeltaR_hu_nis_uncut;             // uncut trimuon delta R high mass, like sign 
  TH1D  *fControlDeltaR_hl_nis_uncut;             // uncut trimuon delta R high mass, like sign 

  TH1D  *fControlDeltaPhi_uncut;                  // uncut trimuon delta Phi
  TH1D  *fControlDeltaPhi_lu_is_uncut;            // uncut trimuon delta Phi low mass, unlike sign
  TH1D  *fControlDeltaPhi_ll_is_uncut;            // uncut trimuon delta Phi low mass, unlike sign
  TH1D  *fControlDeltaPhi_hu_is_uncut;            // uncut trimuon delta Phi high mass, like sign 
  TH1D  *fControlDeltaPhi_hl_is_uncut;            // uncut trimuon delta Phi high mass, like sign 
  TH1D  *fControlDeltaPhi_lu_nis_uncut;           // uncut trimuon delta Phi low mass, unlike sign
  TH1D  *fControlDeltaPhi_ll_nis_uncut;           // uncut trimuon delta Phi low mass, unlike sign
  TH1D  *fControlDeltaPhi_hu_nis_uncut;           // uncut trimuon delta Phi high mass, like sign 
  TH1D  *fControlDeltaPhi_hl_nis_uncut;           // uncut trimuon delta Phi high mass, like sign 

  TH1D  *fControlDeltaEta_uncut;                  // uncut trimuon delta Eta
  TH1D  *fControlDeltaTheta_uncut;                // uncut trimuon delta Theta

  TH1D  *fControlPtAsymetry_uncut;                // uncut trimuon pt asymetry
  TH1D  *fControlPtAsymetry_lu_is_uncut;          // uncut trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlPtAsymetry_ll_is_uncut;          // uncut trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlPtAsymetry_hu_is_uncut;          // uncut trimuon pt asymetry high mass, like sign 
  TH1D  *fControlPtAsymetry_hl_is_uncut;          // uncut trimuon pt asymetry high mass, like sign 
  TH1D  *fControlPtAsymetry_lu_nis_uncut;         // uncut trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlPtAsymetry_ll_nis_uncut;         // uncut trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlPtAsymetry_hu_nis_uncut;         // uncut trimuon pt asymetry high mass, like sign 
  TH1D  *fControlPtAsymetry_hl_nis_uncut;         // uncut trimuon pt asymetry high mass, like sign 

  TH1D  *fControlpt_uncut;                        // uncut trimuon pt
  TH1D  *fControlpt_lu_is_uncut;                  // uncut trimuon pt low mass, unlike sign
  TH1D  *fControlpt_ll_is_uncut;                  // uncut trimuon pt low mass, unlike sign
  TH1D  *fControlpt_hu_is_uncut;                  // uncut trimuon pt high mass, like sign 
  TH1D  *fControlpt_hl_is_uncut;                  // uncut trimuon pt high mass, like sign 
  TH1D  *fControlpt_lu_nis_uncut;                 // uncut trimuon pt low mass, unlike sign
  TH1D  *fControlpt_ll_nis_uncut;                 // uncut trimuon pt low mass, unlike sign
  TH1D  *fControlpt_hu_nis_uncut;                 // uncut trimuon pt high mass, like sign 
  TH1D  *fControlpt_hl_nis_uncut;                 // uncut trimuon pt high mass, like sign 

  TH1D  *fControleta_uncut   ;                    // uncut trimuon eta
  TH1D  *fControleta_lu_is_uncut;                 // uncut trimuon eta low mass, unlike sign
  TH1D  *fControleta_ll_is_uncut;                 // uncut trimuon eta low mass, unlike sign
  TH1D  *fControleta_hu_is_uncut;                 // uncut trimuon eta high mass, like sign 
  TH1D  *fControleta_hl_is_uncut;                 // uncut trimuon eta high mass, like sign 
  TH1D  *fControleta_lu_nis_uncut;                // uncut trimuon eta low mass, unlike sign
  TH1D  *fControleta_ll_nis_uncut;                // uncut trimuon eta low mass, unlike sign
  TH1D  *fControleta_hu_nis_uncut;                // uncut trimuon eta high mass, like sign 
  TH1D  *fControleta_hl_nis_uncut;                // uncut trimuon eta high mass, like sign 

  TH1D  *fControlImpact2D_uncut  ;                // uncut trimuon 2D Impact Parameter
  TH1D  *fControlImpact2D_is_lu_uncut;            // uncut trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D  *fControlImpact2D_is_ll_uncut;            // uncut trimuon 2D Impact Parameter, low mass, like sign
  TH1D  *fControlImpact2D_is_hu_uncut;            // uncut trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D  *fControlImpact2D_is_hl_uncut;            // uncut trimuon 2D Impact Parameter, high mass, like sign
  TH1D  *fControlImpact2D_nis_lu_uncut;           // uncut trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D  *fControlImpact2D_nis_ll_uncut;           // uncut trimuon 2D Impact Parameter, low mass, like sign
  TH1D  *fControlImpact2D_nis_hu_uncut;           // uncut trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D  *fControlImpact2D_nis_hl_uncut;           // uncut trimuon 2D Impact Parameter, high mass, like sign

  TH1D  *fControlsqisol_10_uncut   ;              // uncut trimuon sqared isolation sum in DeltaR come of 1.0	      
  TH1D  *fControlsqisol_10_is_lu_uncut;           // uncut trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlsqisol_10_is_ll_uncut;           // uncut trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlsqisol_10_is_hu_uncut;           // uncut trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlsqisol_10_is_hl_uncut;           // uncut trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlsqisol_10_nis_lu_uncut;          // uncut trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlsqisol_10_nis_ll_uncut;          // uncut trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlsqisol_10_nis_hu_uncut;          // uncut trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlsqisol_10_nis_hl_uncut;          // uncut trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D  *fControlthrust_uncut   ;                 // thrust of event, classified by muon pair
  TH1D  *fControlthrust_is_lu_uncut;              // thrust of event, classified by muon pair  
  TH1D  *fControlthrust_is_ll_uncut;              // thrust of event, classified by muon pair  
  TH1D  *fControlthrust_is_hu_uncut;              // thrust of event, classified by muon pair
  TH1D  *fControlthrust_is_hl_uncut;              // thrust of event, classified by muon pair    
  TH1D  *fControlthrust_nis_lu_uncut;             // thrust of event, classified by muon pair
  TH1D  *fControlthrust_nis_ll_uncut;             // thrust of event, classified by muon pair
  TH1D  *fControlthrust_nis_hu_uncut;             // thrust of event, classified by muon pair
  TH1D  *fControlthrust_nis_hl_uncut;             // thrust of event, classified by muon pair 

  TH1D  *fControlsphericity_uncut  ;              // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_is_lu_uncut;          // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_is_ll_uncut;          // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_is_hu_uncut;          // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_is_hl_uncut;          // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_nis_lu_uncut;         // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_nis_ll_uncut;         // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_nis_hu_uncut;         // sphericity of event, classified by muon pair
  TH1D  *fControlsphericity_nis_hl_uncut;         // sphericity of event, classified by muon pair

  TH1D  *fControlisotropy_uncut  ;                // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_is_lu_uncut;            // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_is_ll_uncut;            // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_is_hu_uncut;            // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_is_hl_uncut;            // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_nis_lu_uncut;           // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_nis_ll_uncut;           // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_nis_hu_uncut;           // isotropy of event, classified by muon pair
  TH1D  *fControlisotropy_nis_hl_uncut;           // isotropy of event, classified by muon pair
    
  TH1D  *fControlmultiplicity_uncut  ;            // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_is_lu_uncut;        // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_is_ll_uncut;        // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_is_hu_uncut;        // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_is_hl_uncut;        // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_nis_lu_uncut;       // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_nis_ll_uncut;       // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_nis_hu_uncut;       // multiplicity of event, classified by muon pair
  TH1D  *fControlmultiplicity_nis_hl_uncut;       // multiplicity of event, classified by muon pair

  TH1D  *fControlQ2Prime_uncut  ;                 // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_is_lu_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_is_ll_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_is_hu_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_is_hl_uncut;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_nis_lu_uncut;            // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_nis_ll_uncut;            // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlQ2Prime_nis_hu_uncut;            // Virtuality Q'2 of event, classified by muon pair 
  TH1D  *fControlQ2Prime_nis_hl_uncut;            // Virtuality Q'2 of event, classified by muon pair

  TH1D  *fControlNperEvGood;                      // good trimuon per event
  TH1D  *fControlGoodTriMuonMass;                 // good trimuon mass
  TH1D  *fControlGoodTriMuonMassLow;              // low good trimuon mass
  TH1D  *fControlGoodTriMuonMassHigh;             // high good trimuon mass

  TH1D  *fControlGoodMass_lu_is ;                 // trimuon mass low like sign isolated
  TH1D  *fControlGoodMass_ll_is ;                 // trimuon mass low like sign isolated
  TH1D  *fControlGoodMass_hu_is ;                 // trimuon mass high unlike sign isolated
  TH1D  *fControlGoodMass_hl_is ;                 // trimuon mass high unlike sign isolated
  TH1D  *fControlGoodMass_lu_nis;                 // trimuon mass low like sign non-isolated
  TH1D  *fControlGoodMass_ll_nis;                 // trimuon mass low like sign non-isolated
  TH1D  *fControlGoodMass_hu_nis;                 // trimuon mass high unlike sign non-isolated
  TH1D  *fControlGoodMass_hl_nis;                 // trimuon mass high unlike sign non-isolated

  TH1D  *fControlGoodDeltaR;                      // good trimuon delta R
  TH1D  *fControlGoodDeltaR_lu_is;                // good trimuon delta R low mass, unlike sign
  TH1D  *fControlGoodDeltaR_ll_is;                // good trimuon delta R low mass, unlike sign
  TH1D  *fControlGoodDeltaR_hu_is;                // good trimuon delta R high mass, like sign 
  TH1D  *fControlGoodDeltaR_hl_is;                // good trimuon delta R high mass, like sign 
  TH1D  *fControlGoodDeltaR_lu_nis;               // good trimuon delta R low mass, unlike sign
  TH1D  *fControlGoodDeltaR_ll_nis;               // good trimuon delta R low mass, unlike sign
  TH1D  *fControlGoodDeltaR_hu_nis;               // good trimuon delta R high mass, like sign 
  TH1D  *fControlGoodDeltaR_hl_nis;               // good trimuon delta R high mass, like sign 

  TH1D  *fControlGoodDeltaPhi;                    // good trimuon delta Phi
  TH1D  *fControlGoodDeltaPhi_lu_is;              // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlGoodDeltaPhi_ll_is;              // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlGoodDeltaPhi_hu_is;              // trimuon delta Phi high mass, like sign 
  TH1D  *fControlGoodDeltaPhi_hl_is;              // trimuon delta Phi high mass, like sign 
  TH1D  *fControlGoodDeltaPhi_lu_nis;             // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlGoodDeltaPhi_ll_nis;             // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlGoodDeltaPhi_hu_nis;             // trimuon delta Phi high mass, like sign 
  TH1D  *fControlGoodDeltaPhi_hl_nis;             // trimuon delta Phi high mass, like sign 

  TH1D  *fControlGoodDeltaEta;                    // good trimuon delta Eta
  TH1D  *fControlGoodDeltaTheta;                  // good trimuon delta Theta  

  TH1D  *fControlGoodPtAsymetry;                  // good trimuon pt asymetry
  TH1D  *fControlGoodPtAsymetry_lu_is;            // good trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlGoodPtAsymetry_ll_is;            // good trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlGoodPtAsymetry_hu_is;            // good trimuon pt asymetry high mass, like sign 
  TH1D  *fControlGoodPtAsymetry_hl_is;            // good trimuon pt asymetry high mass, like sign 
  TH1D  *fControlGoodPtAsymetry_lu_nis;           // good trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlGoodPtAsymetry_ll_nis;           // good trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlGoodPtAsymetry_hu_nis;           // good trimuon pt asymetry high mass, like sign 
  TH1D  *fControlGoodPtAsymetry_hl_nis;           // good trimuon pt asymetry high mass, like sign 

  TH1D  *fControlGoodpt;                          // good trimuon pt
  TH1D  *fControlGoodpt_lu_is;                    // good trimuon pt low mass, unlike sign
  TH1D  *fControlGoodpt_ll_is;                    // good trimuon pt low mass, unlike sign
  TH1D  *fControlGoodpt_hu_is;                    // good trimuon pt high mass, like sign 
  TH1D  *fControlGoodpt_hl_is;                    // good trimuon pt high mass, like sign 
  TH1D  *fControlGoodpt_lu_nis;                   // good trimuon pt low mass, unlike sign
  TH1D  *fControlGoodpt_ll_nis;                   // good trimuon pt low mass, unlike sign
  TH1D  *fControlGoodpt_hu_nis;                   // good trimuon pt high mass, like sign 
  TH1D  *fControlGoodpt_hl_nis;                   // good trimuon pt high mass, like sign 

  TH1D  *fControlGoodeta   ;                      // good trimuon eta
  TH1D  *fControlGoodeta_lu_is;                   // good trimuon eta low mass, unlike sign
  TH1D  *fControlGoodeta_ll_is;                   // good trimuon eta low mass, unlike sign
  TH1D  *fControlGoodeta_hu_is;                   // good trimuon eta high mass, like sign 
  TH1D  *fControlGoodeta_hl_is;                   // good trimuon eta high mass, like sign 
  TH1D  *fControlGoodeta_lu_nis;                  // good trimuon eta low mass, unlike sign
  TH1D  *fControlGoodeta_ll_nis;                  // good trimuon eta low mass, unlike sign
  TH1D  *fControlGoodeta_hu_nis;                  // good trimuon eta high mass, like sign 
  TH1D  *fControlGoodeta_hl_nis;                  // good trimuon eta high mass, like sign 

  TH1D  *fControlGoodImpact2D  ;                  // good trimuon 2D Impact Parameter
  TH1D  *fControlGoodImpact2D_is_lu;              // good trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D  *fControlGoodImpact2D_is_ll;              // good trimuon 2D Impact Parameter, low mass, like sign
  TH1D  *fControlGoodImpact2D_is_hu;              // good trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D  *fControlGoodImpact2D_is_hl;              // good trimuon 2D Impact Parameter, high mass, like sign
  TH1D  *fControlGoodImpact2D_nis_lu;             // good trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D  *fControlGoodImpact2D_nis_ll;             // good trimuon 2D Impact Parameter, low mass, like sign
  TH1D  *fControlGoodImpact2D_nis_hu;             // good trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D  *fControlGoodImpact2D_nis_hl;             // good trimuon 2D Impact Parameter, high mass, like sign

  TH1D  *fControlGoodsqisol_10   ;                // good trimuon sqared isolation sum in DeltaR come of 1.0
  TH1D  *fControlGoodsqisol_10_is_lu;             // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlGoodsqisol_10_is_ll;             // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlGoodsqisol_10_is_hu;             // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlGoodsqisol_10_is_hl;             // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlGoodsqisol_10_nis_lu;            // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlGoodsqisol_10_nis_ll;            // good sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlGoodsqisol_10_nis_hu;            // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlGoodsqisol_10_nis_hl;            // good sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D  *fControlGoodthrust   ;                   // thrust of event, classified by muon pair
  TH1D  *fControlGoodthrust_is_lu;                // thrust of event, classified by muon pair  
  TH1D  *fControlGoodthrust_is_ll;                // thrust of event, classified by muon pair  
  TH1D  *fControlGoodthrust_is_hu;                // thrust of event, classified by muon pair
  TH1D  *fControlGoodthrust_is_hl;                // thrust of event, classified by muon pair    
  TH1D  *fControlGoodthrust_nis_lu;               // thrust of event, classified by muon pair
  TH1D  *fControlGoodthrust_nis_ll;               // thrust of event, classified by muon pair
  TH1D  *fControlGoodthrust_nis_hu;               // thrust of event, classified by muon pair
  TH1D  *fControlGoodthrust_nis_hl;               // thrust of event, classified by muon pair 

  TH1D  *fControlGoodsphericity  ;                // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_is_lu;            // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_is_ll;            // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_is_hu;            // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_is_hl;            // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_nis_lu;           // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_nis_ll;           // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_nis_hu;           // sphericity of event, classified by muon pair
  TH1D  *fControlGoodsphericity_nis_hl;           // sphericity of event, classified by muon pair

  TH1D  *fControlGoodisotropy  ;                  // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_is_lu;              // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_is_ll;              // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_is_hu;              // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_is_hl;              // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_nis_lu;             // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_nis_ll;             // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_nis_hu;             // isotropy of event, classified by muon pair
  TH1D  *fControlGoodisotropy_nis_hl;             // isotropy of event, classified by muon pair
    
  TH1D  *fControlGoodmultiplicity  ;              // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_is_lu;          // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_is_ll;          // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_is_hu;          // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_is_hl;          // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_nis_lu;         // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_nis_ll;         // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_nis_hu;         // multiplicity of event, classified by muon pair
  TH1D  *fControlGoodmultiplicity_nis_hl;         // multiplicity of event, classified by muon pair

  TH1D  *fControlGoodQ2Prime  ;                   // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_is_lu;               // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_is_ll;               // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_is_hu;               // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_is_hl;               // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_nis_lu;              // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_nis_ll;              // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlGoodQ2Prime_nis_hu;              // Virtuality Q'2 of event, classified by muon pair 
  TH1D  *fControlGoodQ2Prime_nis_hl;              // Virtuality Q'2 of event, classified by muon pair

  TH1D  *fControlNperEvChosen;                    // chosen trimuon per event
  TH1D  *fControlChosenTriMuonMass;               // chosen trimuon mass
  TH1D  *fControlChosenTriMuonMassLow;            // low chosen trimuon mass
  TH1D  *fControlChosenTriMuonMassHigh;           // high chosen trimuon mass

  TH1D  *fControlChosenMass_lu_is ;               // trimuon mass low like sign isolated
  TH1D  *fControlChosenMass_ll_is ;               // trimuon mass low like sign isolated
  TH1D  *fControlChosenMass_hu_is ;               // trimuon mass high unlike sign isolated
  TH1D  *fControlChosenMass_hl_is ;               // trimuon mass high unlike sign isolated
  TH1D  *fControlChosenMass_lu_nis;               // trimuon mass low like sign non-isolated
  TH1D  *fControlChosenMass_ll_nis;               // trimuon mass low like sign non-isolated
  TH1D  *fControlChosenMass_hu_nis;               // trimuon mass high unlike sign non-isolated
  TH1D  *fControlChosenMass_hl_nis;               // trimuon mass high unlike sign non-isolated

  TH1D  *fControlChosenDeltaR;                    // chosen trimuon delta R
  TH1D  *fControlChosenDeltaR_lu_is;              // chosen trimuon delta R low mass, unlike sign
  TH1D  *fControlChosenDeltaR_ll_is;              // chosen trimuon delta R low mass, unlike sign
  TH1D  *fControlChosenDeltaR_hu_is;              // chosen trimuon delta R high mass, like sign 
  TH1D  *fControlChosenDeltaR_hl_is;              // chosen trimuon delta R high mass, like sign 
  TH1D  *fControlChosenDeltaR_lu_nis;             // chosen trimuon delta R low mass, unlike sign
  TH1D  *fControlChosenDeltaR_ll_nis;             // chosen trimuon delta R low mass, unlike sign
  TH1D  *fControlChosenDeltaR_hu_nis;             // chosen trimuon delta R high mass, like sign 
  TH1D  *fControlChosenDeltaR_hl_nis;             // chosen trimuon delta R high mass, like sign 

  TH1D  *fControlChosenDeltaPhi;                  // chosen trimuon delta Phi
  TH1D  *fControlChosenDeltaPhi_lu_is;            // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlChosenDeltaPhi_ll_is;            // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlChosenDeltaPhi_hu_is;            // trimuon delta Phi high mass, like sign 
  TH1D  *fControlChosenDeltaPhi_hl_is;            // trimuon delta Phi high mass, like sign 
  TH1D  *fControlChosenDeltaPhi_lu_nis;           // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlChosenDeltaPhi_ll_nis;           // trimuon delta Phi low mass, unlike sign
  TH1D  *fControlChosenDeltaPhi_hu_nis;           // trimuon delta Phi high mass, like sign 
  TH1D  *fControlChosenDeltaPhi_hl_nis;           // trimuon delta Phi high mass, like sign 
  TH1D  *fControlChosenDeltaEta;                  // chosen trimuon delta Eta
  TH1D  *fControlChosenDeltaTheta;                // chosen trimuon delta Theta
  TH1D  *fControlChosenPtAsymetry;                // chosen trimuon pt asymetry
  TH1D  *fControlChosenPtAsymetry_lu_is;          // chosen trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlChosenPtAsymetry_ll_is;          // chosen trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlChosenPtAsymetry_hu_is;          // chosen trimuon pt asymetry high mass, like sign 
  TH1D  *fControlChosenPtAsymetry_hl_is;          // chosen trimuon pt asymetry high mass, like sign 
  TH1D  *fControlChosenPtAsymetry_lu_nis;         // chosen trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlChosenPtAsymetry_ll_nis;         // chosen trimuon pt asymetry low mass, unlike sign
  TH1D  *fControlChosenPtAsymetry_hu_nis;         // chosen trimuon pt asymetry high mass, like sign 
  TH1D  *fControlChosenPtAsymetry_hl_nis;         // chosen trimuon pt asymetry high mass, like sign 

  TH1D  *fControlChosenpt;                        // chosen trimuon pt
  TH1D  *fControlChosenpt_lu_is;                  // chosen trimuon pt low mass, unlike sign
  TH1D  *fControlChosenpt_ll_is;                  // chosen trimuon pt low mass, unlike sign
  TH1D  *fControlChosenpt_hu_is;                  // chosen trimuon pt high mass, like sign 
  TH1D  *fControlChosenpt_hl_is;                  // chosen trimuon pt high mass, like sign 
  TH1D  *fControlChosenpt_lu_nis;                 // chosen trimuon pt low mass, unlike sign
  TH1D  *fControlChosenpt_ll_nis;                 // chosen trimuon pt low mass, unlike sign
  TH1D  *fControlChosenpt_hu_nis;                 // chosen trimuon pt high mass, like sign 
  TH1D  *fControlChosenpt_hl_nis;                 // chosen trimuon pt high mass, like sign 

  TH1D  *fControlChoseneta   ;                    // chosen trimuon eta
  TH1D  *fControlChoseneta_lu_is;                 // chosen trimuon eta low mass, unlike sign
  TH1D  *fControlChoseneta_ll_is;                 // chosen trimuon eta low mass, unlike sign
  TH1D  *fControlChoseneta_hu_is;                 // chosen trimuon eta high mass, like sign 
  TH1D  *fControlChoseneta_hl_is;                 // chosen trimuon eta high mass, like sign 
  TH1D  *fControlChoseneta_lu_nis;                // chosen trimuon eta low mass, unlike sign
  TH1D  *fControlChoseneta_ll_nis;                // chosen trimuon eta low mass, unlike sign
  TH1D  *fControlChoseneta_hu_nis;                // chosen trimuon eta high mass, like sign 
  TH1D  *fControlChoseneta_hl_nis;                // chosen trimuon eta high mass, like sign 

  TH1D  *fControlChosenImpact2D  ;                // chosen trimuon 2D Impact Parameter
  TH1D  *fControlChosenImpact2D_is_lu;            // chosen trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D  *fControlChosenImpact2D_is_ll;            // chosen trimuon 2D Impact Parameter, low mass, like sign
  TH1D  *fControlChosenImpact2D_is_hu;            // chosen trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D  *fControlChosenImpact2D_is_hl;            // chosen trimuon 2D Impact Parameter, high mass, like sign
  TH1D  *fControlChosenImpact2D_nis_lu;           // chosen trimuon 2D Impact Parameter, low mass, unlike sign
  TH1D  *fControlChosenImpact2D_nis_ll;           // chosen trimuon 2D Impact Parameter, low mass, like sign
  TH1D  *fControlChosenImpact2D_nis_hu;           // chosen trimuon 2D Impact Parameter, high mass, unlike sign
  TH1D  *fControlChosenImpact2D_nis_hl;           // chosen trimuon 2D Impact Parameter, high mass, like sign

  TH1D  *fControlChosensqisol_10   ;              // chosen trimuon sqared isolation sum in DeltaR come of 1.0  	      
  TH1D  *fControlChosensqisol_10_is_lu;           // chosen trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlChosensqisol_10_is_ll;           // chosen trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlChosensqisol_10_is_hu;           // chosen trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlChosensqisol_10_is_hl;           // chosen trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlChosensqisol_10_nis_lu;          // chosen trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlChosensqisol_10_nis_ll;          // chosen trimuon sqared isolation sum in DeltaR come of 1.0 low mass, unlike sign
  TH1D  *fControlChosensqisol_10_nis_hu;          // chosen trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 
  TH1D  *fControlChosensqisol_10_nis_hl;          // chosen trimuon sqared isolation sum in DeltaR come of 1.0 high mass, like sign 

  TH1D  *fControlChosenthrust   ;                 // thrust of event, classified by muon pair
  TH1D  *fControlChosenthrust_is_lu;              // thrust of event, classified by muon pair  
  TH1D  *fControlChosenthrust_is_ll;              // thrust of event, classified by muon pair  
  TH1D  *fControlChosenthrust_is_hu;              // thrust of event, classified by muon pair
  TH1D  *fControlChosenthrust_is_hl;              // thrust of event, classified by muon pair    
  TH1D  *fControlChosenthrust_nis_lu;             // thrust of event, classified by muon pair
  TH1D  *fControlChosenthrust_nis_ll;             // thrust of event, classified by muon pair
  TH1D  *fControlChosenthrust_nis_hu;             // thrust of event, classified by muon pair
  TH1D  *fControlChosenthrust_nis_hl;             // thrust of event, classified by muon pair 

  TH1D  *fControlChosensphericity  ;              // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_is_lu;          // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_is_ll;          // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_is_hu;          // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_is_hl;          // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_nis_lu;         // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_nis_ll;         // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_nis_hu;         // sphericity of event, classified by muon pair
  TH1D  *fControlChosensphericity_nis_hl;         // sphericity of event, classified by muon pair

  TH1D  *fControlChosenisotropy  ;                // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_is_lu;            // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_is_ll;            // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_is_hu;            // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_is_hl;            // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_nis_lu;           // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_nis_ll;           // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_nis_hu;           // isotropy of event, classified by muon pair
  TH1D  *fControlChosenisotropy_nis_hl;           // isotropy of event, classified by muon pair
    
  TH1D  *fControlChosenmultiplicity  ;            // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_is_lu;        // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_is_ll;        // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_is_hu;        // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_is_hl;        // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_nis_lu;       // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_nis_ll;       // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_nis_hu;       // multiplicity of event, classified by muon pair
  TH1D  *fControlChosenmultiplicity_nis_hl;       // multiplicity of event, classified by muon pair
 
  TH1D  *fControlChosenQ2Prime  ;                 // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_is_lu;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_is_ll;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_is_hu;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_is_hl;             // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_nis_lu;            // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_nis_ll;            // Virtuality Q'2 of event, classified by muon pair
  TH1D  *fControlChosenQ2Prime_nis_hu;            // Virtuality Q'2 of event, classified by muon pair 
  TH1D  *fControlChosenQ2Prime_nis_hl;            // Virtuality Q'2 of event, classified by muon pair


 public:
  GTriMuons();
  GTriMuons(Int_t dummy);
  virtual ~GTriMuons();

  virtual Bool_t   Reset();
  virtual Bool_t   Do();
  virtual Bool_t   Fill();

  virtual Bool_t   CheckMuonsAllCut(GTriMuon *match);
  virtual Bool_t   CheckMuonsMVCut(GTriMuon *match);
  virtual Bool_t   CheckInvMassCut(GTriMuon *match);
  virtual Bool_t   CheckSqSumIsolationCut(GTriMuon *match);
  virtual Bool_t   CheckDeltaRCut(GTriMuon *match);
  virtual Bool_t   CheckDeltaPhiCut(GTriMuon *match);
  virtual Bool_t   CheckDeltaThetaCut(GTriMuon *match);
  virtual Bool_t   CheckDeltaEtaCut(GTriMuon *match);
  virtual Bool_t   CheckPtAsymetryCut(GTriMuon *match);
  virtual Bool_t   CheckEtFractionHighCut(GTriMuon *match);
  virtual Bool_t   CheckEtFractionLowCut(GTriMuon *match);
  virtual Bool_t   CheckDifChargeCut(GTriMuon *match);
  virtual Bool_t   CheckCharmMCJpsiCut(GTriMuon *match);
  virtual Bool_t   CheckCharmMCPsiprimeCut(GTriMuon *match);
  virtual Bool_t   CheckTrigger(GTriMuon *match);
  virtual Bool_t   CheckAllCuts(GTriMuon *match, Int_t flag = 0 );
  virtual Bool_t   CheckBestTriMuon(GTriMuon *match, Int_t index);
  virtual Bool_t   DetSelectedCand(Int_t index);

  virtual Bool_t   FillHistos();
  virtual Bool_t   FillGeneral();
  virtual Bool_t   FillControl();

  virtual Bool_t   CreateControl();
  virtual Bool_t   CreateGeneral();

  virtual Bool_t   ObjectsFillHistos();

  virtual Bool_t   ObjectsFillGeneral(GTriMuon *trimuon); 
  virtual Bool_t   ObjectsFillControl(GTriMuon *trimuon); 

  virtual Bool_t   GetAllCuts();

  virtual GTriMuon* GetTriMuon(Int_t id);

  virtual GTriMuon* GetChosen();

  virtual TString  PrintMessage(TString option);
  virtual Bool_t   Print(TString option);

  virtual Bool_t   FillPlotMuonPt(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonP(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonPz(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonEta(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonPhi(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99);
  virtual Bool_t   FillPlotMuonEtaPtBins(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonPhiPtBins(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonEtaPBins(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonPhiPBins(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonEtaPzBins(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);
  virtual Bool_t   FillPlotMuonPhiPzBins(GTriMuon *trimuon, TH1D *histo, TString option, Double_t min = -9999.99, Double_t max = 9999.99, Int_t currentBin = 0, Int_t maxBin = 999);

  virtual Bool_t   InitVariables();

  inline virtual Int_t     GetNTriMuons()           { return fNTriMuons;                  }

  ClassDef(GTriMuons,0) // match object for jet-muon match
};

R__EXTERN GTriMuons *gTriMuons;

#endif
