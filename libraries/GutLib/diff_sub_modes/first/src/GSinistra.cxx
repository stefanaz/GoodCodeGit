//
// GSinistra.cxx
//
// $Author: ibloch $
// $Date: 2007/01/04 22:34:46 $
// $Revision: 1.42 $
//

#include <GSinistra.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GSinistra)
#endif

  GSinistra *gSinistra = 0;

//_____________________________________________________________
// GSinistra
// Sinistra class for everything which is related only to Sinistra
//
//
GSinistra::GSinistra() : GPhysObj() {
  //
  // GSinistra default constructor
  if ( gDebug ) cout << endl << "GSinistra::GSinistra ctor called" << endl << endl;

  gSinistra = this;

  // initialize variables
  fEEnergyCut          = kFALSE;
  fQ2LowCut            = kFALSE;
  fYELCut              = kFALSE;
  fSiNCandCut          = kFALSE;
  fBoxCut              = kFALSE;
  fY                   = -9999.99;
  fX                   = -9999.99;
  fXlog                = -9999.99;
  fQ2                  = -9999.99;
  fQ2log               = -9999.99;
  fXpos                =  9999.99;
  fYpos                =  9999.99;
  fThetaE              = -9999.99;
  fEmpz_had            = -9999.99;
  fEmpzCut             = kFALSE;
  
  // general plots
  fGeneralYEL_uncut     = 0;
  fGeneralYEL           = 0;
  fGeneralEE_uncut      = 0;
  fGeneralEE            = 0;
  fGeneralXlog          = 0;
  fGeneralThetaE_uncut  = 0;
  fGeneralThetaE        = 0;
  fGeneralThetaE_0_10_uncut   = 0;
  fGeneralThetaE_0_10         = 0;
  fGeneralThetaE_10_200_uncut = 0;
  fGeneralThetaE_10_200       = 0;
  fGeneralThetaE_200_uncut    = 0;
  fGeneralThetaE_200          = 0;
  fGeneralQ2            = 0;
  fGeneralQ2_uncut      = 0;
  fGeneralQ2log         = 0;
  fGeneralQ2log_uncut   = 0;
  fGeneralQ2x           = 0;
  fGeneralQ2x_uncut     = 0;
  fGeneralXY            = 0;
  fGeneralXY_uncut      = 0;

//   fGeneraldimuphi_uncut = 0;
//   fGeneraldimuphi_lu_is_uncut = 0;
//   fGeneraldimuphi_ll_is_uncut = 0;
//   fGeneraldimuphi_hu_is_uncut = 0;
//   fGeneraldimuphi_hl_is_uncut = 0;
//   fGeneraldimuphi_lu_nis_uncut = 0;
//   fGeneraldimuphi_ll_nis_uncut = 0;
//   fGeneraldimuphi_hu_nis_uncut = 0;
//   fGeneraldimuphi_hl_nis_uncut = 0;

  fGeneraldimuq2si_uncut = 0;
  fGeneraldimuq2si_lu_is_uncut = 0;
  fGeneraldimuq2si_ll_is_uncut = 0;
  fGeneraldimuq2si_hu_is_uncut = 0;
  fGeneraldimuq2si_hl_is_uncut = 0;
  fGeneraldimuq2si_lu_nis_uncut = 0;
  fGeneraldimuq2si_ll_nis_uncut = 0;
  fGeneraldimuq2si_hu_nis_uncut = 0;
  fGeneraldimuq2si_hl_nis_uncut = 0;

  fGeneraldimulog10q2si_uncut = 0;
  fGeneraldimulog10q2si_lu_is_uncut = 0;
  fGeneraldimulog10q2si_ll_is_uncut = 0;
  fGeneraldimulog10q2si_hu_is_uncut = 0;
  fGeneraldimulog10q2si_hl_is_uncut = 0;
  fGeneraldimulog10q2si_lu_nis_uncut = 0;
  fGeneraldimulog10q2si_ll_nis_uncut = 0;
  fGeneraldimulog10q2si_hu_nis_uncut = 0;
  fGeneraldimulog10q2si_hl_nis_uncut = 0;

//   fGeneraldimuphi = 0;
//   fGeneraldimuphi_lu_is = 0;
//   fGeneraldimuphi_ll_is = 0;
//   fGeneraldimuphi_hu_is = 0;
//   fGeneraldimuphi_hl_is = 0;
//   fGeneraldimuphi_lu_nis = 0;
//   fGeneraldimuphi_ll_nis = 0;
//   fGeneraldimuphi_hu_nis = 0;
//   fGeneraldimuphi_hl_nis = 0;

  fGeneraldimuq2si = 0;
  fGeneraldimuq2si_lu_is = 0;
  fGeneraldimuq2si_ll_is = 0;
  fGeneraldimuq2si_hu_is = 0;
  fGeneraldimuq2si_hl_is = 0;
  fGeneraldimuq2si_lu_nis = 0;
  fGeneraldimuq2si_ll_nis = 0;
  fGeneraldimuq2si_hu_nis = 0;
  fGeneraldimuq2si_hl_nis = 0;

  fGeneraldimulog10q2si = 0;
  fGeneraldimulog10q2si_lu_is = 0;
  fGeneraldimulog10q2si_ll_is = 0;
  fGeneraldimulog10q2si_hu_is = 0;
  fGeneraldimulog10q2si_hl_is = 0;
  fGeneraldimulog10q2si_lu_nis = 0;
  fGeneraldimulog10q2si_ll_nis = 0;
  fGeneraldimulog10q2si_hu_nis = 0;
  fGeneraldimulog10q2si_hl_nis = 0;

  // control plots
  fControlYEL_uncut     = 0;
  fControlYEL           = 0;
  fControlEE_uncut      = 0;
  fControlEE            = 0;
  fControlSiNCand_uncut = 0;
  fControlSiNCand       = 0;
  fControlQ2log         = 0;
  fControlQ2log_uncut   = 0;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GSinistra::~GSinistra() {
  //
  // GSinistra default destructor
  if ( gDebug ) cout << endl << "GSinistra::~GSinistra dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GSinistra::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GSinistra::Do() called" << endl << endl;

  SiNCandCheck();

  Errors();

  YELCheck();
  
  BoxCheck();

  Q2Check();

  EEnergyCheck();

  CheckEmpzCut();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::Errors() {
  //
  // fill error list for error flags given by sierror
  if ( gDebug ) cout << endl << "GSinistra::Errors() called" << endl << endl;

  if ( gCards->GetListsErrorList() ) {
    // only fill if one or more candidate
    if ( GetSiNCandCut() ) {
      if ( gData->Getsierror() == 1 )
	gLister->FillErrorList("Sinistra: Islands: number of Towers exceed maximum");
      if ( gData->Getsierror() == 2 )
	gLister->FillErrorList("Sinistra: Islands: number of Cells exceed maximum");
      if ( gData->Getsierror() == 100 )
	gLister->FillErrorList("Sinistra: more than 100 candidates found");
      if ( gData->Getsierror() == 101 )
	gLister->FillErrorList("Sinistra: no clusters found by islands");
      if ( gData->Getsierror() == 102 )
	gLister->FillErrorList("Sinistra: more than 600 cells in caltru");
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::YELCheck() {
  //
  // check if event passes cut on y_el for highest probable electron candidate
  if ( gDebug ) cout << endl << "GSinistra::ProbCheck() called" << endl << endl;

  if ( GetSiNCandCut() ) {
    if (gCards->GetSinistraDIS() == kFALSE) { 
      if (gData->Getsiyel(0) < gCards->GetSinistraYELCut()) 
	fYELCut = kTRUE;
      else 
	fYELCut = kFALSE;
    }
    if ( gCards->GetSinistraDIS()){
      if (gData->Getsiyel(0) < gCards->GetSinistraYELHighCut() 
	  && gData->Getsiyjb(0) > gCards->GetSinistraYELLowCut() )
	fYELCut = kTRUE;
      else 
	fYELCut = kFALSE;
    }
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::EEnergyCheck() {
  //
  // check if event passes cut on electron energy for highest probable candidate 


  if ( gDebug ) cout << endl << "GSinistra::ProbCheck() called" << endl << endl;

  if ( GetSiNCandCut() ) {
    if ( gData->Getsicalene(0) > gCards->GetSinistraEnergyCut())
      fEEnergyCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::Q2Check() {
  //
  // check if event passes cut on Q2 for highest probable candidate 
  
  
  if ( gDebug ) cout << endl << "GSinistra::Q2Check() called" << endl << endl;
  
  if ( GetSiNCandCut() ) {
    if ( fQ2 > gCards->GetSinistraQ2LowCut())
    fQ2LowCut = kTRUE;
  }
  
  return kTRUE;
}
//_____________________________________________________________

Bool_t GSinistra::BoxCheck() {
  //
  // check if event passes box cut on X and Y position 
  
  
  if ( gDebug ) cout << endl << "GSinistra::BoxCheck() called" << endl << endl;
  
  if ( gCards->GetSinistraBoxCut() == kFALSE ) {
    fBoxCut = kTRUE;
  }
  else if ( GetSiNCandCut() ) {
    if 	(TMath::Abs(GetXpos()) < gCards->GetSinistraBoxXCut() 
	 && TMath::Abs(GetYpos()) < gCards->GetSinistraBoxYCut())
      fBoxCut = kFALSE; // e is inside box
    else  
      fBoxCut = kTRUE;
    
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::CheckEmpzCut() {
  //
  // check if event fulfils Empz cut
  if ( gDebug ) cout << endl << "GSinistra::CheckEmpzCut() called" << endl << endl;
  fEmpz_had = gData->Getv_h_e_zu()-gData->Getv_h_pz_zu();
  if ( ( fEmpz_had >= gCards->GetZUFOEMPZLOWCut() ) && ( fEmpz_had <= gCards->GetZUFOEMPZUPCut() ) )
    fEmpzCut = kTRUE;
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GSinistra::CreateControl() called" << endl << endl;

  if ( gCards->GetSinistraControl() ) {
    
    TString histogram_title_sin;
    histogram_title_sin = "uncut Sinistra: y_{zufo,el} for E_{e,cal}>";
    histogram_title_sin += gCards->GetSinistraEnergyCut();
    histogram_title_sin += "GeV";
     fControlYEL_uncut = gHistogrammer->TH1DFactory("Sinistra_Control","YEL_uncut",histogram_title_sin,50,0.,1.,"y_{zufo,el}","Events");
    
    histogram_title_sin = "Sinistra: y_{zufo,el} for E_{e,cal}>";
    histogram_title_sin += gCards->GetSinistraEnergyCut();
    histogram_title_sin += "GeV";
    fControlYEL       = gHistogrammer->TH1DFactory("Sinistra_Control","YEL",histogram_title_sin,50,0.,1.,"y_{zufo,el}","Events");
    
    histogram_title_sin = "uncut Sinistra: E_{e,cal} for ";
    histogram_title_sin += gCards->GetSinistraYELLowCut();
    histogram_title_sin += " < y_{zufo,el}<";
    histogram_title_sin += gCards->GetSinistraYELHighCut();
    fControlEE_uncut = gHistogrammer->TH1DFactory("Sinistra_Control","EE_uncut",histogram_title_sin,100,0.,300.,"E_{e,cal} [GeV]","Events");

    histogram_title_sin = "Sinistra: E_{e,cal} for ";
    histogram_title_sin += gCards->GetSinistraYELLowCut();
    histogram_title_sin += " < y_{zufo,el}<";
    histogram_title_sin += gCards->GetSinistraYELHighCut();
    fControlEE       = gHistogrammer->TH1DFactory("Sinistra_Control","EE",histogram_title_sin,100,0.,300.,"E_{e,cal} [GeV]","Events");
     
    fControlSiNCand_uncut = gHistogrammer->TH1DFactory("Sinistra_Control","SiNCand_uncut","uncut Sinistra candidates",3,0.,3.,"candidates","Events");
    fControlSiNCand       = gHistogrammer->TH1DFactory("Sinistra_Control","SiNCand","Sinistra candidates",3,0.,3.,"candidates","Events");

    histogram_title_sin = "Sinistra: Q^{2} [GeV^{2}]";
    fControlQ2log = gHistogrammer->TH1DFactory("Sinistra_Control","Q2log",histogram_title_sin,500,0.,5.,"log(Q^{2} [GeV^{2}])","Events");

    histogram_title_sin = "uncut Sinistra: Q^{2} [GeV^{2}]";
    fControlQ2log_uncut = gHistogrammer->TH1DFactory("Sinistra_Control","Q2log_uncut",histogram_title_sin,500,0.,5.,"log(Q^{2} [GeV^{2}])","Events");

  }  

  return kTRUE;
}

    
//_____________________________________________________________

Bool_t GSinistra::CreateGeneral() {
  //
  // create general plots
  if ( gDebug ) cout << endl << "GSinistra::CreateGeneral() called" << endl << endl;
  
  Int_t thetaE_nbin=30;
  Double_t thetaE_low=1.5707;
  Double_t thetaE_high=3.1415;

//   Int_t dimuphibins = 0;
//   Double_t dimuphilow = 0;
//   Double_t dimuphihigh = 0;
  Int_t dimuq2sibins = 100;
  Double_t dimuq2silow = 0;
  Double_t dimuq2sihigh = 10000;

  Int_t dimulog10q2sibins = 7;
  Double_t dimulog10q2silow = -2;
  Double_t dimulog10q2sihigh = 5;

  if ( gCards->GetSinistraGeneral() ) {
    TString histogram_title_sin;
    histogram_title_sin = "uncut Sinistra: y_{zufo,el} for E_{e,cal}>";
    histogram_title_sin += gCards->GetSinistraEnergyCut();
    histogram_title_sin += "GeV";
    fGeneralYEL_uncut = gHistogrammer->TH1DFactory("Sinistra","YEL_uncut",histogram_title_sin,50,0.,1.,"y_{zufo,el}","Events");

    histogram_title_sin = "Sinistra: y_{zufo,el} for E_{e,cal}>";
    histogram_title_sin += gCards->GetSinistraEnergyCut();
    histogram_title_sin += "GeV";
    fGeneralYEL       = gHistogrammer->TH1DFactory("Sinistra","YEL",histogram_title_sin ,50,0.,1.,"y_{zufo,el}","Events");
    
    histogram_title_sin = "uncut Sinistra: E_{e,cal} for ";
    histogram_title_sin += gCards->GetSinistraYELLowCut();
    histogram_title_sin += " < y_{zufo,el}<";
    histogram_title_sin += gCards->GetSinistraYELHighCut();
    fGeneralEE_uncut = gHistogrammer->TH1DFactory("Sinistra","EE_uncut",histogram_title_sin,50,0.,50.,"E_{e,cal} [GeV]","Events");

    histogram_title_sin = "Sinistra: E_{e,cal} for ";
    histogram_title_sin += gCards->GetSinistraYELLowCut();
    histogram_title_sin += " < y_{zufo,el}<";
    histogram_title_sin += gCards->GetSinistraYELHighCut();
    fGeneralEE       = gHistogrammer->TH1DFactory("Sinistra","EE",histogram_title_sin,50,0.,50.,"E_{e,cal} [GeV]","Events");

    histogram_title_sin = "Sinistra: x_{el}";
    fGeneralXlog  = gHistogrammer->TH1DFactory("Sinistra","Xlog",histogram_title_sin,10,-5.,0.,"log10(x_{el})","Events");

    histogram_title_sin = "Sinistra: Q^{2} [GeV^{2}]";
    fGeneralQ2log  = gHistogrammer->TH1DFactory("Sinistra","Q2log",histogram_title_sin,16,0,4.,"log10(Q^{2} [GeV^{2}])","Events");

    histogram_title_sin = "uncut Sinistra: Q^{2} [GeV^{2}]";
    fGeneralQ2log_uncut = gHistogrammer->TH1DFactory("Sinistra","Q2log_uncut",histogram_title_sin,8,0,4.,"log10(Q^{2} [GeV^{2}])","Events");
    
    histogram_title_sin = "Sinistra: Q^{2} [GeV^{2}]";
    fGeneralQ2 = gHistogrammer->TH1DFactory("Sinistra","Q2",histogram_title_sin,20,0.,2000.,"Q^{2} [GeV^{2}]","Events");

    histogram_title_sin = "uncut Sinistra: Q^{2} [GeV^{2}]";
    fGeneralQ2_uncut = gHistogrammer->TH1DFactory("Sinistra","Q2_uncut",histogram_title_sin,20,0.,2000.,"Q^{2} [GeV^{2}]","Events");
    
    histogram_title_sin = "Sinistra: Theta e";
    fGeneralThetaE = gHistogrammer->TH1DFactory("Sinistra","ThetaE",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");

    histogram_title_sin = "uncut Sinistra: Theta e";
    fGeneralThetaE_uncut = gHistogrammer->TH1DFactory("Sinistra","ThetaE_uncut",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");
    
    histogram_title_sin = "Sinistra: Theta e Q^{2}<10";
    fGeneralThetaE_0_10 = gHistogrammer->TH1DFactory("Sinistra","ThetaE_0_10",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");

    histogram_title_sin = "uncut Sinistra: Theta e Q^{2}<10";
    fGeneralThetaE_0_10_uncut = gHistogrammer->TH1DFactory("Sinistra","ThetaE_0_10_uncut",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");

    histogram_title_sin = "Sinistra: Theta e 10<Q^{2}<200";
    fGeneralThetaE_10_200 = gHistogrammer->TH1DFactory("Sinistra","ThetaE_10_200",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");

    histogram_title_sin = "uncut Sinistra: Theta e 10<Q^{2}<200";
    fGeneralThetaE_10_200_uncut = gHistogrammer->TH1DFactory("Sinistra","ThetaE_10_200_uncut",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");

    histogram_title_sin = "Sinistra: Theta e 200<Q^{2}";
    fGeneralThetaE_200 = gHistogrammer->TH1DFactory("Sinistra","ThetaE_200",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");

    histogram_title_sin = "uncut Sinistra: Theta e 200<Q^{2}";
    fGeneralThetaE_200_uncut = gHistogrammer->TH1DFactory("Sinistra","ThetaE_200_uncut",histogram_title_sin,thetaE_nbin,thetaE_low,thetaE_high,"Theta e","Events");
    
    histogram_title_sin = "Sinistra: kinematic plane";
    fGeneralQ2x = gHistogrammer->TH2DFactory("Sinistra","Q2x",histogram_title_sin,500,-5.,0.,350,0.,3.5,"log(x)","log(Q^{2} [GeV^{2}])","Events");

    histogram_title_sin = "uncut Sinistra: kinematic plane";
    fGeneralQ2x_uncut = gHistogrammer->TH2DFactory("Sinistra","Q2x_uncut",histogram_title_sin,500,-5.,0.,350,0.,3.5,"log(x)","log(Q^{2} [GeV^{2}])","Events");

    histogram_title_sin = "Sinistra: Electron position";
    fGeneralXY = gHistogrammer->TH2DFactory("Sinistra","XY",histogram_title_sin,400,-40.,40.,400,-40.,40.,"X-position [cm]","Y-position [cm]","Events");

    histogram_title_sin = "Sinistra: Electron position";
    fGeneralXY_uncut = gHistogrammer->TH2DFactory("Sinistra","XY_uncut",histogram_title_sin,400,-40.,40.,400,-40.,40.,"X-position [cm]","Y-position [cm]","Events");

//     fGeneraldimuphi_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_uncut","uncut phi ",dimuphibins,dimuphilow,dimuphihigh,"phi dimu","Events");
//     fGeneraldimuphi_lu_is_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_lu_is_uncut","uncut #dimuphi_{#mu}_lu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_is","Events");
//     fGeneraldimuphi_ll_is_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_ll_is_uncut","uncut #dimuphi_{#mu}_ll_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_is","Events");
//     fGeneraldimuphi_hu_is_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hu_is_uncut","uncut #dimuphi_{#mu}_hu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_is","Events");
//     fGeneraldimuphi_hl_is_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hl_is_uncut","uncut #dimuphi_{#mu}_hl_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_is","Events");
//     fGeneraldimuphi_lu_nis_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_lu_nis_uncut","uncut #dimuphi_{#mu}_lu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_nis","Events");
//     fGeneraldimuphi_ll_nis_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_ll_nis_uncut","uncut #dimuphi_{#mu}_ll_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_nis","Events");
//     fGeneraldimuphi_hu_nis_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hu_nis_uncut","uncut #dimuphi_{#mu}_hu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_nis","Events");
//     fGeneraldimuphi_hl_nis_uncut = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hl_nis_uncut","uncut #dimuphi_{#mu}_hl_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_nis","Events");

    fGeneraldimuq2si_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_uncut","uncut q2si ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"q2si dimu","Events");
    fGeneraldimuq2si_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_lu_is_uncut","uncut #dimuq2si_{#mu}_lu_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_lu_is","Events");
    fGeneraldimuq2si_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_ll_is_uncut","uncut #dimuq2si_{#mu}_ll_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_ll_is","Events");
    fGeneraldimuq2si_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hu_is_uncut","uncut #dimuq2si_{#mu}_hu_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hu_is","Events");
    fGeneraldimuq2si_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hl_is_uncut","uncut #dimuq2si_{#mu}_hl_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hl_is","Events");
    fGeneraldimuq2si_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_lu_nis_uncut","uncut #dimuq2si_{#mu}_lu_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_lu_nis","Events");
    fGeneraldimuq2si_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_ll_nis_uncut","uncut #dimuq2si_{#mu}_ll_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_ll_nis","Events");
    fGeneraldimuq2si_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hu_nis_uncut","uncut #dimuq2si_{#mu}_hu_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hu_nis","Events");
    fGeneraldimuq2si_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hl_nis_uncut","uncut #dimuq2si_{#mu}_hl_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hl_nis","Events");

    fGeneraldimulog10q2si_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_uncut","uncut log10q2si ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"log10q2si dimu","Events");
    fGeneraldimulog10q2si_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_lu_is_uncut","uncut #dimulog10q2si_{#mu}_lu_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_lu_is","Events");
    fGeneraldimulog10q2si_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_ll_is_uncut","uncut #dimulog10q2si_{#mu}_ll_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_ll_is","Events");
    fGeneraldimulog10q2si_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hu_is_uncut","uncut #dimulog10q2si_{#mu}_hu_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hu_is","Events");
    fGeneraldimulog10q2si_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hl_is_uncut","uncut #dimulog10q2si_{#mu}_hl_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hl_is","Events");
    fGeneraldimulog10q2si_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_lu_nis_uncut","uncut #dimulog10q2si_{#mu}_lu_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_lu_nis","Events");
    fGeneraldimulog10q2si_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_ll_nis_uncut","uncut #dimulog10q2si_{#mu}_ll_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_ll_nis","Events");
    fGeneraldimulog10q2si_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hu_nis_uncut","uncut #dimulog10q2si_{#mu}_hu_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hu_nis","Events");
    fGeneraldimulog10q2si_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hl_nis_uncut","uncut #dimulog10q2si_{#mu}_hl_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hl_nis","Events");

//     fGeneraldimuphi = gHistogrammer->TH1DFactory("Sinistra","dimuphi","#varphi ",dimuphibins,dimuphilow,dimuphihigh,"#varphi dimu ","Events");
//     fGeneraldimuphi_lu_is = gHistogrammer->TH1DFactory("Sinistra","dimuphi_lu_is","#dimuphi_{#mu}_lu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_is ","Events");
//     fGeneraldimuphi_ll_is = gHistogrammer->TH1DFactory("Sinistra","dimuphi_ll_is","#dimuphi_{#mu}_ll_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_is ","Events");
//     fGeneraldimuphi_hu_is = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hu_is","#dimuphi_{#mu}_hu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_is ","Events");
//     fGeneraldimuphi_hl_is = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hl_is","#dimuphi_{#mu}_hl_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_is ","Events");
//     fGeneraldimuphi_lu_nis = gHistogrammer->TH1DFactory("Sinistra","dimuphi_lu_nis","#dimuphi_{#mu}_lu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_nis ","Events");
//     fGeneraldimuphi_ll_nis = gHistogrammer->TH1DFactory("Sinistra","dimuphi_ll_nis","#dimuphi_{#mu}_ll_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_nis ","Events");
//     fGeneraldimuphi_hu_nis = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hu_nis","#dimuphi_{#mu}_hu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_nis ","Events");
//     fGeneraldimuphi_hl_nis = gHistogrammer->TH1DFactory("Sinistra","dimuphi_hl_nis","#dimuphi_{#mu}_hl_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_nis ","Events");

    fGeneraldimuq2si = gHistogrammer->TH1DFactory("DIMuon","dimuq2si","#varq2si ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#varq2si dimu ","Events");
    fGeneraldimuq2si_lu_is = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_lu_is","#dimuq2si_{#mu}_lu_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_lu_is ","Events");
    fGeneraldimuq2si_ll_is = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_ll_is","#dimuq2si_{#mu}_ll_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_ll_is ","Events");
    fGeneraldimuq2si_hu_is = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hu_is","#dimuq2si_{#mu}_hu_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hu_is ","Events");
    fGeneraldimuq2si_hl_is = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hl_is","#dimuq2si_{#mu}_hl_is ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hl_is ","Events");
    fGeneraldimuq2si_lu_nis = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_lu_nis","#dimuq2si_{#mu}_lu_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_lu_nis ","Events");
    fGeneraldimuq2si_ll_nis = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_ll_nis","#dimuq2si_{#mu}_ll_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_ll_nis ","Events");
    fGeneraldimuq2si_hu_nis = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hu_nis","#dimuq2si_{#mu}_hu_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hu_nis ","Events");
    fGeneraldimuq2si_hl_nis = gHistogrammer->TH1DFactory("DIMuon","dimuq2si_hl_nis","#dimuq2si_{#mu}_hl_nis ",dimuq2sibins,dimuq2silow,dimuq2sihigh,"#dimuq2si_{#mu}_hl_nis ","Events");

    fGeneraldimulog10q2si = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si","#varlog10q2si ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#varlog10q2si dimu ","Events");
    fGeneraldimulog10q2si_lu_is = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_lu_is","#dimulog10q2si_{#mu}_lu_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_lu_is ","Events");
    fGeneraldimulog10q2si_ll_is = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_ll_is","#dimulog10q2si_{#mu}_ll_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_ll_is ","Events");
    fGeneraldimulog10q2si_hu_is = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hu_is","#dimulog10q2si_{#mu}_hu_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hu_is ","Events");
    fGeneraldimulog10q2si_hl_is = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hl_is","#dimulog10q2si_{#mu}_hl_is ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hl_is ","Events");
    fGeneraldimulog10q2si_lu_nis = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_lu_nis","#dimulog10q2si_{#mu}_lu_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_lu_nis ","Events");
    fGeneraldimulog10q2si_ll_nis = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_ll_nis","#dimulog10q2si_{#mu}_ll_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_ll_nis ","Events");
    fGeneraldimulog10q2si_hu_nis = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hu_nis","#dimulog10q2si_{#mu}_hu_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hu_nis ","Events");
    fGeneraldimulog10q2si_hl_nis = gHistogrammer->TH1DFactory("DIMuon","dimulog10q2si_hl_nis","#dimulog10q2si_{#mu}_hl_nis ",dimulog10q2sibins,dimulog10q2silow,dimulog10q2sihigh,"#dimulog10q2si_{#mu}_hl_nis ","Events");

  }  

  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::FillControl() {
  //
  // fill control plots
  if ( gDebug ) cout << endl << "GSinistra::FillControl() called" << endl << endl;

  if ( gCards->GetSinistraControl() ) {

    fControlSiNCand_uncut->Fill(gData->Getsincand());

    if ( GetSiNCandCut() ) {
      fControlSiNCand->Fill(gData->Getsincand());

      fControlQ2log_uncut->Fill(fQ2log);
      if ( gHeader->GetAllCuts() && ((gCards->GetSinistraDIS()== kFALSE &&  GetDISRemovalCut()==kFALSE) || (gCards->GetSinistraDIS() && GetDISSelectionCut() ) ))
	fControlQ2log->Fill(fQ2log);

      if ( GetEEnergyCut() ) {
	fControlYEL_uncut->Fill(gData->Getsiyel(0));
	if ( GetYELCut() )
	  fControlYEL->Fill(gData->Getsiyel(0));
      }

      if ( GetYELCut() ) {
	fControlEE_uncut->Fill(gData->Getsicalene(0));
	if ( GetEEnergyCut() )
	  fControlEE->Fill(gData->Getsicalene(0));
      }

    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::FillGeneral() {
  //
  // fill general plots
  if ( gDebug ) cout << endl << "GSinistra::FillGeneral() called" << endl << endl;
  
  if ( gCards->GetSinistraGeneral() ) {
    
    // ingo's dimuon selected DIS plots start:
    if ( gHeader->GetAllCuts()){
      
      // get the first dimuon for dimuon plots (check for valid pointer when using it):
      GDIMuon * dimuon = 0; 
      if( gDIMuons->GetNDIMuons() > 0 ) dimuon = gDIMuons->GetDIMuon(0);
      if( dimuon != 0 ){
	//	  Double_t IsolationSqSum10 = dimuon->GetIsolationSqSum10();
	  Double_t invMass = dimuon->GetInvMass();
	  Double_t dimuq2si = fQ2;
	  //	  Double_t dimulog10q2si = fQ2log;
	  Double_t dimulog10q2si;
	  if(GetSiNCandCut()){
	    if(gCards->GetSinistraDIS() && GetDISSelectionCut() ) dimulog10q2si = fQ2log;
	    else if(!(gCards->GetSinistraDIS() && gSinistra->GetDISSelectionCut()) ) dimulog10q2si = -1.;
	  }
	  else dimulog10q2si = -2.;
	  
	  
	  //after cuts:
	  // 	  fGeneraldimuphi->Fill(dimuphi,gHeader->GetWeight());
	  // 	  if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut() ) {
	  // 	    if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuphi_lu_is->Fill(dimuphi,gHeader->GetWeight());
	  // 	    if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuphi_ll_is->Fill(dimuphi,gHeader->GetWeight());
	  // 	    if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuphi_hu_is->Fill(dimuphi,gHeader->GetWeight());
	  // 	    if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuphi_hl_is->Fill(dimuphi,gHeader->GetWeight());
	  // 	  }
	  // 	  else{
	  // 	    if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuphi_lu_nis->Fill(dimuphi,gHeader->GetWeight());
	  // 	    if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuphi_ll_nis->Fill(dimuphi,gHeader->GetWeight());
	  // 	    if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuphi_hu_nis->Fill(dimuphi,gHeader->GetWeight());
	  // 	    if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuphi_hl_nis->Fill(dimuphi,gHeader->GetWeight());
	  // 	  }
	  fGeneraldimuq2si->Fill(dimuq2si,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut() ) {      
	    //	  if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut() ) {
	    if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_lu_is->Fill(dimuq2si,gHeader->GetWeight());
	    if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuq2si_ll_is->Fill(dimuq2si,gHeader->GetWeight());
	    if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_hu_is->Fill(dimuq2si,gHeader->GetWeight());
	    if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuq2si_hl_is->Fill(dimuq2si,gHeader->GetWeight());
	  }
	  else{
	    if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_lu_nis->Fill(dimuq2si,gHeader->GetWeight());
	    if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuq2si_ll_nis->Fill(dimuq2si,gHeader->GetWeight());
	    if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_hu_nis->Fill(dimuq2si,gHeader->GetWeight());
	    if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuq2si_hl_nis->Fill(dimuq2si,gHeader->GetWeight());
	  }
	  fGeneraldimulog10q2si->Fill(dimulog10q2si,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut() ) {      
	    //	  if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut() ) {
	    if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_lu_is->Fill(dimulog10q2si,gHeader->GetWeight());
	    if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_ll_is->Fill(dimulog10q2si,gHeader->GetWeight());
	    if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hu_is->Fill(dimulog10q2si,gHeader->GetWeight());
	    if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hl_is->Fill(dimulog10q2si,gHeader->GetWeight());
	  }
	  else{
	    if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_lu_nis->Fill(dimulog10q2si,gHeader->GetWeight());
	    if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_ll_nis->Fill(dimulog10q2si,gHeader->GetWeight());
	    if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hu_nis->Fill(dimulog10q2si,gHeader->GetWeight());
	    if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hl_nis->Fill(dimulog10q2si,gHeader->GetWeight());
	  }
 	}
	// ingo's dimuon selected DIS plots end.
      }
    if ( GetSiNCandCut() ) {

	// ingo's dimuon uncut DIS plots start:
      GDIMuon * dimuon = 0; 
      if( gDIMuons->GetNDIMuons() > 0 ) dimuon = gDIMuons->GetDIMuon(0);
      if( dimuon != 0 ){
	//	Double_t IsolationSqSum10 = dimuon->GetIsolationSqSum10();
	Double_t invMass = dimuon->GetInvMass();
	Double_t dimuq2si = fQ2;
	Double_t dimulog10q2si;
	if(gCards->GetSinistraDIS() && GetDISSelectionCut() ) dimulog10q2si = fQ2log;
	else if(fQ2>2. && !(gCards->GetSinistraDIS() && gSinistra->GetDISSelectionCut()) ) dimulog10q2si = -2.;
	else dimulog10q2si = -1.;

    	// uncut dimuon
// 	fGeneraldimuphi_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut() ) {
// 	  if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuphi_lu_is_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	  if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuphi_ll_is_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	  if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuphi_hu_is_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	  if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuphi_hl_is_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	}
// 	else{
// 	  if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuphi_lu_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	  if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuphi_ll_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	  if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuphi_hu_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	  if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuphi_hl_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
// 	}

	fGeneraldimuq2si_uncut->Fill(dimuq2si,gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut() ) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut() ) {
	  if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_lu_is_uncut->Fill(dimuq2si,gHeader->GetWeight());
	  if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuq2si_ll_is_uncut->Fill(dimuq2si,gHeader->GetWeight());
	  if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_hu_is_uncut->Fill(dimuq2si,gHeader->GetWeight());
	  if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuq2si_hl_is_uncut->Fill(dimuq2si,gHeader->GetWeight());
	}
	else{
	  if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_lu_nis_uncut->Fill(dimuq2si,gHeader->GetWeight());
	  if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimuq2si_ll_nis_uncut->Fill(dimuq2si,gHeader->GetWeight());
	  if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimuq2si_hu_nis_uncut->Fill(dimuq2si,gHeader->GetWeight());
	  if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimuq2si_hl_nis_uncut->Fill(dimuq2si,gHeader->GetWeight());
	}
	fGeneraldimulog10q2si_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut() ) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut() ) {
	  if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_lu_is_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	  if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_ll_is_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	  if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hu_is_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	  if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hl_is_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	}
	else{
	  if ( invMass <= 4 &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_lu_nis_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	  if ( invMass <= 4 && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_ll_nis_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	  if ( invMass > 4  &&  dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hu_nis_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	  if ( invMass > 4  && !dimuon->GetDifCharge() )      fGeneraldimulog10q2si_hl_nis_uncut->Fill(dimulog10q2si,gHeader->GetWeight());
	}
      }
      // ingo's dimuon uncut DIS plots end.

      if (GetEEnergyCut()&&GetYELCut()&&GetQ2LowCut()&&GetEmpzCut()) {
	fGeneralXY_uncut->Fill(fXpos,fYpos,gHeader->GetWeight());
      }
      if (GetEEnergyCut()&&GetYELCut()&&GetQ2LowCut()&&GetBoxCut()&&GetEmpzCut()) {
   	fGeneralThetaE_uncut->Fill(GetThetaE(),gHeader->GetWeight());
	if (fQ2<10.)
	  fGeneralThetaE_0_10_uncut->Fill(GetThetaE(),gHeader->GetWeight());
	else if (fQ2<200.)
	  fGeneralThetaE_10_200_uncut->Fill(GetThetaE(),gHeader->GetWeight());
	else
	  fGeneralThetaE_200_uncut->Fill(GetThetaE(),gHeader->GetWeight());  
      }
      if (GetEEnergyCut()&&GetYELCut()&&GetBoxCut()&&GetEmpzCut()) {
	fGeneralQ2_uncut->Fill(fQ2,gHeader->GetWeight());
	fGeneralQ2log_uncut->Fill(fQ2log,gHeader->GetWeight());
	fGeneralQ2x_uncut->Fill(fXlog,fQ2log,gHeader->GetWeight());
      }
      if (GetEEnergyCut()&&GetBoxCut()&&GetQ2LowCut()&&GetEmpzCut()) {
	fGeneralYEL_uncut->Fill(gData->Getsiyel(0),gHeader->GetWeight());
      }
      if (GetYELCut()&&GetBoxCut()&&GetQ2LowCut()&&GetEmpzCut()) {
	fGeneralEE_uncut->Fill(gData->Getsicalene(0),gHeader->GetWeight()); 
      }
      if ( gHeader->GetAllCuts() && ((gCards->GetSinistraDIS()== kFALSE &&  GetDISRemovalCut()==kFALSE) || (gCards->GetSinistraDIS() && GetDISSelectionCut() ) )) {

// 	cout<<"************************* Sinistra bei Ben run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
// 	cout<<"************************* Sinistra bei Ben DISDISDISDIS: gData->Getsipt(0): "<<gData->Getsipt(0)<<endl;
	fGeneralXY->Fill(fXpos,fYpos,gHeader->GetWeight());
	fGeneralXlog->Fill(fXlog,gHeader->GetWeight());
	fGeneralQ2->Fill(fQ2,gHeader->GetWeight());
	fGeneralQ2log->Fill(fQ2log,gHeader->GetWeight());
	fGeneralQ2x->Fill(fXlog,fQ2log,gHeader->GetWeight());      
	fGeneralYEL->Fill(gData->Getsiyel(0),gHeader->GetWeight());
	fGeneralEE->Fill(gData->Getsicalene(0),gHeader->GetWeight());
  	fGeneralThetaE->Fill(GetThetaE(),gHeader->GetWeight());
	if (fQ2<10.)
	  fGeneralThetaE_0_10->Fill(GetThetaE(),gHeader->GetWeight());
	else if (fQ2<200.)
	  fGeneralThetaE_10_200->Fill(GetThetaE(),gHeader->GetWeight());
	else
	  fGeneralThetaE_200->Fill(GetThetaE(),gHeader->GetWeight());  
      }
    }
  }
  return kTRUE;
}
    
//_____________________________________________________________

Bool_t GSinistra::SiNCandCheck() {
  //
  // 
  // consider all event with >= 1 sinistra candidate with prob > 0.9 as candidate with >= one sinistra electron
  // check for >= 1 sinistra electron
  if ( gDebug ) cout << endl << "GSinistra::SiNCandCheck() called" << endl << endl;

  if ( gData->Getsincand() > 0 ) {
    for ( Int_t i = 0; i < gData->Getsincand(); ++i ) {
      if ( gData->Getsiprob(i) >= gCards->GetSinistraProbCut() )
	fSiNCandCut          = kTRUE;
    }
  } else {
    fSiNCandCut = kFALSE;
  }

  if ( fSiNCandCut ) {
    fY                 = gData->Getsiyel(0);
    fX                 = gData->Getsixel(0);
    fXlog              = TMath::Log10(fX);
    fQ2                = gData->Getsiq2el(0);
    fQ2log             = TMath::Log10(fQ2);
    fXpos              = gData->Getsipos(0,0);
    fYpos              = gData->Getsipos(0,1);
    fThetaE            = gData->Getsith(0);
  }

  return kTRUE;
  
}
    
//_____________________________________________________________

Bool_t GSinistra::Reset() {
  //
  // reset on event by event basis
  if ( gDebug ) cout << endl << "GSinistra::Reset() called" << endl << endl;

  // reset variable
  fEEnergyCut = kFALSE;
  fYELCut     = kFALSE;
  fQ2LowCut   = kFALSE;
  fSiNCandCut = kFALSE;
  fBoxCut     = kFALSE;
  fY          = -9999.99;
  fX          = -9999.99;
  fXlog       = -9999.99;
  fQ2         = -9999.99;
  fQ2log      = -9999.99;
  fXpos       =  9999.99;
  fYpos       =  9999.99;
  fThetaE     = -9999.99;

  fEmpz_had   = -9999.99;
  fEmpzCut    = kFALSE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GSinistra::GetDISRemovalCut() {
  //
  // return true, if DIS removal cut is valid
  //
  // consider all event with >= 1 sinistra candidate with prob > 0.90 as candidate with >= one sinistra electron
  // first return true for all events with no sinistra electron,
  // return false for event if sinistra electron fullfills EnergyCut and y_el cut
  if ( gDebug ) cout << endl << "GSinistra::GetDISRemovalCut() called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( GetSiNCandCut() && GetEEnergyCut() && GetYELCut() )

    returny = kFALSE;

  return returny;
}

//_____________________________________________________________

Bool_t GSinistra::GetDISSelectionCut() {
  //
  // return true, if DIS electron found
  //
  // consider all event with >= 1 sinistra candidate with prob > 0.90 as candidate with >= one sinistra electron
  // first return fales for all events with no sinistra electron,
  // return true for event if sinistra electron fullfills EnergyCuu, y_el and ... cut
  if ( gDebug ) cout << endl << "GSinistra::GetDISSelectionCut() called" << endl << endl;
  
  Bool_t returny = kFALSE;
  
  if ( GetSiNCandCut() && GetEEnergyCut() && GetYELCut() && GetQ2LowCut() && GetBoxCut() && GetEmpzCut()) 
    
    returny = kTRUE;
  
  return returny;
}


//_____________________________________________________________

Bool_t GSinistra::GetAllCuts() {
  //
  // return flag if event passes all sinistra cuts
  //
  if ( gDebug ) cout << endl << "GSinistra::GetAllCuts() called" << endl << endl;
  // no sinistra cut
  if (gCards->GetSinistraNoCut()==kTRUE)
    return kTRUE;
  // remove DIS events
  if (gCards->GetSinistraDIS()== kFALSE && GetDISRemovalCut())
    return kTRUE;
  //        else
  //  	return kFALSE;
  // select DIS events
  if (gCards->GetSinistraDIS()== kTRUE && GetDISSelectionCut())
    return kTRUE;
  //        else
  //  	return kFALSE;
  return kFALSE;
}

//_____________________________________________________________

Int_t GSinistra::GetDISPHPCut(){
  //
  // returns 1 if event passes hardcoded DIS cuts for kt_jet finder
  //
  if ( gDebug ) cout << endl << "GSinistra::GetDISPHPCuts() called" << endl << endl;
  fEmpz_had = gData->Getv_h_e_zu()-gData->Getv_h_pz_zu();
  // DIS
  if (gData->Getsincand()>0 && fEmpz_had > 40. && gData->Getsiq2el(0)>2. && gData->Getsicalene(0) > 10. ) {
    return 2;
  }
  //PHP
  if (gData->Getsincand()==0 || fEmpz_had < 40. || gData->Getsiq2el(0) < 2. || gData->Getsicalene(0) < 10.) {
    return 1;
  }
  //dunno
  gLister->FillErrorList("GSinistra::GetDISPHPCuts: event is not DIS and not PhP: what else can it be?");
  cout << endl << "GSinistra::GetDISPHPCuts() error " << endl << endl;
  return 3;

}

//_____________________________________________________________

TString GSinistra::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GSinistra::PrintMessage() called" << endl << endl;

  TString dummy = "Electrons:\n\n";

  for ( Int_t i = 0; i < gData->Getsincand(); ++i ) {

    dummy.Append("Electron: ");
  
    dummy.Append(gInclude->FormatedChar(" id: ",5));
    dummy.Append(gInclude->FormatedInt(i,2,0," "));
    dummy.Append(gInclude->FormatedChar(" siprob: ",9));
    dummy.Append(gInclude->FormatedDouble(gData->Getsiprob(i),1,2));
    dummy.Append(gInclude->FormatedChar(" siyel: ",13));
    dummy.Append(gInclude->FormatedDouble(gData->Getsiyel(i),1,2));
    dummy.Append(gInclude->FormatedChar(" sicalene: ",11));
    dummy.Append(gInclude->FormatedDouble(gData->Getsicalene(i),4,2));
    dummy.Append(gInclude->FormatedChar(" sith: ",11));
    dummy.Append(gInclude->FormatedDouble(gData->Getsicalene(i),4,2));

    dummy.Append("\n");

  }
  
  dummy.Append("Electron-Event: ");
  dummy.Append(gInclude->FormatedChar(" candidates: ",14));
  dummy.Append(gInclude->FormatedInt((Int_t)gData->Getsincand(),2,0," "));
  dummy.Append(gInclude->FormatedChar(" all cuts: ",11));
  dummy.Append(gInclude->FormatedBool(GetAllCuts()));

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GSinistra::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GSinistra::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("SINISTRA") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}
