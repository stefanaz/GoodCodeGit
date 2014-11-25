//
// GCal.cxx
//
// $Author: ibloch $
// $Date: 2005/04/26 10:30:16 $
// $Revision: 1.34 $
//

#include <GCal.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GCal)
#endif

GCal *gCal = 0;

//_____________________________________________________________
// GCal
// Call class for everything which is related only to CAL
//
//
GCal::GCal() : GPhysObj() {
  //
  // GCal default constructor
  if ( gDebug ) cout << endl << "GCal::GCal ctor called" << endl << endl;

  gCal = this;

  // initialize variables
  fEmpz      = -9999.99;
  fPt        = -9999.99;
  fPtOvEt    = -9999.99;
  fYJB       = -9999.99;
  fETtocuton = -9999.99;

  fYJBCut    = kFALSE;
  fETCut     = kFALSE;
  fPtOvEtCut = kFALSE;
  fTimeCut   = kFALSE;

  // general cal histos
  fGeneralpx                  = 0;
  fGeneralpy                  = 0;
  fGeneralpz                  = 0;
  fGeneralE                   = 0;
  fGeneralEt                  = 0;
  fGeneralEtex2ir             = 0;
  fGeneralEtex2irOrange       = 0;
  fGeneralEmpz                = 0;
  fGeneralPt                  = 0;
  fGeneralPtOvEt              = 0;
  fGeneralYJB                 = 0;
  fGeneralYJBvsYTrue          = 0;

  fGeneralcal_tg          = 0;

  fGeneralpx_uncut            = 0;
  fGeneralpy_uncut            = 0;
  fGeneralpz_uncut            = 0;
  fGeneralE_uncut             = 0;
  fGeneralEt_uncut            = 0;
  fGeneralEtex2ir_uncut       = 0;
  fGeneralEtex2irOrange_uncut = 0;
  fGeneralEmpz_uncut          = 0;
  fGeneralPt_uncut            = 0;
  fGeneralPtOvEt_uncut        = 0;
  fGeneralYJB_uncut           = 0;
  fGeneralYJBvsYTrue_uncut    = 0;

  fGeneralcal_tg_uncut    = 0;


  // control plots
  fControlpx                  = 0;
  fControlpy                  = 0;
  fControlpz                  = 0;
  fControlE                   = 0;
  fControlEt                  = 0;
  fControlEmpz                = 0;
  fControlPt                  = 0;
  fControlPtOvEt              = 0;
  fControlYJB                 = 0;
  fControlTime                = 0;

  fControlpx_uncut            = 0;
  fControlpy_uncut            = 0;
  fControlpz_uncut            = 0;
  fControlE_uncut             = 0;
  fControlEt_uncut            = 0;
  fControlEmpz_uncut          = 0;
  fControlPt_uncut            = 0;
  fControlPtOvEt_uncut        = 0;
  fControlYJB_uncut           = 0;
  fControlTime_uncut          = 0;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GCal::~GCal() {
  //
  // GCal default destructor
  if ( gDebug ) cout << endl << "GCal::~GCal dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GCal::CreateGeneral() {
  //
  // create general histograms for CAL
  if ( gDebug ) cout << endl << "GCal::CreateGeneral() called" << endl << endl;

  // create general histograms
  if ( gCards->GetCALGeneral() ) {

    Int_t    pxbins     =   40;
    Double_t pxlow      =  -20.;
    Double_t pxhigh     =   20.;  
    Int_t    pybins     =   40;
    Double_t pylow      =  -20.;
    Double_t pyhigh     =   20.;  
    Int_t    pzbins     =  340;
    Double_t pzlow      =  -40.;
    Double_t pzhigh     =  300.;  
    Int_t    ebins      =  300;
    Double_t elow       =    0.;
    Double_t ehigh      =  300.;  
    Int_t    etbins     =  100;
    Double_t etlow      =    0.;
    Double_t ethigh     =  100.;  
    Int_t    empzbins   =   70;
    Double_t empzlow    =    0.;
    Double_t empzhigh   =   70.;  
    Int_t    ptbins     =   25;
    Double_t ptlow      =    0.;
    Double_t pthigh     =   25.;  
    Int_t    yjbbins    =   50;
    Double_t yjblow     =    0.;
    Double_t yjbhigh    =    1.;  
    Int_t ptovetbins =   20;
    Double_t ptovetlow  =    0.;
    Double_t ptovethigh =    1.;

    Int_t    cal_tgbins     =   40;
    Double_t cal_tglow      =  -20.;
    Double_t cal_tghigh     =   20.;  

    fGeneralpx = gHistogrammer->TH1DFactory("Cal","px","CAL: p_{x}",pxbins,pxlow,pxhigh,"p_{x} [GeV]","Events");
    fGeneralpy = gHistogrammer->TH1DFactory("Cal","py","CAL: p_{y}",pybins,pylow,pyhigh,"p_{y} [GeV]","Events");
    fGeneralpz = gHistogrammer->TH1DFactory("Cal","pz","CAL: p_{z}",pzbins,pzlow,pzhigh,"p_{z} [GeV]","Events");
    fGeneralE = gHistogrammer->TH1DFactory("Cal","E","CAL: E",ebins,elow,ehigh,"E [GeV]","Events");
    fGeneralEt = gHistogrammer->TH1DFactory("Cal","Et","CAL: E_{T}",etbins,etlow,ethigh,"E_{T} [GeV]","Events");
    fGeneralEtex2ir = gHistogrammer->TH1DFactory("Cal","Etex2ir","CAL: E_{T} exluding E_{T} of the 2 inner CAL rings",etbins,etlow,ethigh,"E_{T,ex2ir} [GeV]","Events");
    fGeneralEtex2irOrange = gHistogrammer->TH1DFactory("Cal","Etex2irOrange","CAL: E_{T} exluding E_{T} of the 2 inner CAL rings (orange)",etbins,etlow,ethigh,"E_{T,ex2ir} [GeV]","Events");
    fGeneralEmpz = gHistogrammer->TH1DFactory("Cal","Empz","CAL: E-p_{z}",empzbins,empzlow,empzhigh,"E-p_{z} [GeV]","Events");
    fGeneralPt = gHistogrammer->TH1DFactory("Cal","Pt","CAL: p_{t} ",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fGeneralPtOvEt = gHistogrammer->TH1DFactory("Cal","PtOvEt","CAL: p_{T}/E_{T} ",ptovetbins,ptovetlow,ptovethigh,"p_{T}/E_{T}","Events");
    fGeneralYJB = gHistogrammer->TH1DFactory("Cal","YJB","Cal: y_{JB}",yjbbins,yjblow,yjbhigh,"y_{JB}","Events");
    fGeneralYJBvsYTrue = gHistogrammer->TH2DFactory("Cal","YJBvsYTrue","uncut y_{JB,had} vs. y_{MC,true}",yjbbins,yjblow,yjbhigh,yjbbins,yjblow,yjbhigh,"y_{JB,had}","y_{MC,true}","Events");

    fGeneralcal_tg = gHistogrammer->TH1DFactory("Cal","cal_tg","CAL: catl{tg}",cal_tgbins,cal_tglow,cal_tghigh,"cal_{tg} [ns]","Events");

    fGeneralpx_uncut = gHistogrammer->TH1DFactory("Cal","px_uncut","uncut CAL: p_{x}",pxbins,pxlow,pxhigh,"p_{x} [GeV]","Events");
    fGeneralpy_uncut = gHistogrammer->TH1DFactory("Cal","py_uncut","uncut CAL: p_{y}",pybins,pylow,pyhigh,"p_{y} [GeV]","Events");
    fGeneralpz_uncut = gHistogrammer->TH1DFactory("Cal","pz_uncut","uncut CAL: p_{z}",pzbins,pzlow,pzhigh,"p_{z} [GeV]","Events");
    fGeneralE_uncut = gHistogrammer->TH1DFactory("Cal","E_uncut","uncut CAL: E",ebins,elow,ehigh,"E [GeV]","Events");
    fGeneralEt_uncut = gHistogrammer->TH1DFactory("Cal","Et_uncut","uncut CAL: E_{T}",etbins,etlow,ethigh,"E_{T} [GeV]","Events");
    fGeneralEtex2ir_uncut = gHistogrammer->TH1DFactory("Cal","Etex2ir_uncut","uncut CAL: E_{T} exluding E_{T} of the 2 inner CAL rings",etbins,etlow,ethigh,"E_{T,ex2ir} [GeV]","Events");
    fGeneralEtex2irOrange_uncut = gHistogrammer->TH1DFactory("Cal","Etex2irOrange_uncut","uncut CAL: E_{T} exluding E_{T} of the 2 inner CAL rings (orange)",etbins,etlow,ethigh,"E_{T,ex2ir} [GeV]","Events");
    fGeneralEmpz_uncut = gHistogrammer->TH1DFactory("Cal","Empz_uncut","uncut CAL: E-p_{z}",empzbins,empzlow,empzhigh,"E-p_{z} [GeV]","Events");
    fGeneralPt_uncut = gHistogrammer->TH1DFactory("Cal","Pt_uncut","uncut CAL: p_{t} ",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fGeneralPtOvEt_uncut = gHistogrammer->TH1DFactory("Cal","PtOvEt_uncut","uncut CAL: p_{T}/E_{T} ",ptovetbins,ptovetlow,ptovethigh,"p_{T}/E_{T}","Events");
    fGeneralYJB_uncut = gHistogrammer->TH1DFactory("Cal","YJB_uncut","uncut Cal: y_{JB}",yjbbins,yjblow,yjbhigh,"y_{JB}","Events");
    fGeneralYJBvsYTrue_uncut = gHistogrammer->TH2DFactory("Cal","YJBvsYTrue_uncut","uncut y_{JB,had} vs. y_{MC,true}",yjbbins,yjblow,yjbhigh,yjbbins,yjblow,yjbhigh,"y_{JB,had}","y_{MC,true}","Events");

    fGeneralcal_tg_uncut = gHistogrammer->TH1DFactory("Cal","cal_tg_uncut","uncut CAL: cal_{tg}",cal_tgbins,cal_tglow,cal_tghigh,"cal_{tg} []","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::FillGeneral() {
  //
  // fill general histograms for CAL
  if ( gDebug ) cout << endl << "GCal::FillGeneral() called" << endl << endl;

  if ( gCards->GetCALGeneral() ) {

    fGeneralpx_uncut->Fill(gData->Getcal_px(),gHeader->GetWeight());
    fGeneralpy_uncut->Fill(gData->Getcal_py(),gHeader->GetWeight());
    fGeneralpz_uncut->Fill(gData->Getcal_pz(),gHeader->GetWeight());
    fGeneralE_uncut->Fill(gData->Getcal_e(),gHeader->GetWeight());
    fGeneralEt_uncut->Fill(gData->Getcal_et(),gHeader->GetWeight());
    fGeneralEtex2ir_uncut->Fill(gData->Getcal_et()-gData->Getet2ir(),gHeader->GetWeight());
    fGeneralEtex2irOrange_uncut->Fill(gData->Getetex2ir(),gHeader->GetWeight());
    fGeneralEmpz_uncut->Fill(fEmpz,gHeader->GetWeight());
    fGeneralPt_uncut->Fill(fPt,gHeader->GetWeight());
    fGeneralPtOvEt_uncut->Fill(fPtOvEt,gHeader->GetWeight());
    fGeneralYJB_uncut->Fill(fYJB,gHeader->GetWeight());
    fGeneralYJBvsYTrue_uncut->Fill(fYJB,gData->Getmc_y(),gHeader->GetWeight());

    fGeneralcal_tg_uncut->Fill(gData->Getcal_tg(),gHeader->GetWeight());


    if ( gHeader->GetAllCuts() ) {
      fGeneralpx->Fill(gData->Getcal_px(),gHeader->GetWeight());
      fGeneralpy->Fill(gData->Getcal_py(),gHeader->GetWeight());
      fGeneralpz->Fill(gData->Getcal_pz(),gHeader->GetWeight());
      fGeneralE->Fill(gData->Getcal_e(),gHeader->GetWeight());
      fGeneralEt->Fill(gData->Getcal_et(),gHeader->GetWeight());
      fGeneralEtex2ir->Fill(gData->Getcal_et()-gData->Getet2ir(),gHeader->GetWeight());
      fGeneralEtex2irOrange->Fill(gData->Getetex2ir(),gHeader->GetWeight());
      fGeneralEmpz->Fill(fEmpz,gHeader->GetWeight());
      fGeneralPt->Fill(fPt,gHeader->GetWeight());
      fGeneralPtOvEt->Fill(fPtOvEt,gHeader->GetWeight());
      fGeneralYJB->Fill(fYJB,gHeader->GetWeight());
      fGeneralYJBvsYTrue->Fill(fYJB,gData->Getmc_y(),gHeader->GetWeight());

      fGeneralcal_tg->Fill(gData->Getcal_tg(),gHeader->GetWeight());

    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GCal::Do() called" << endl << endl;

  Calc();

  CheckETCut();
  CheckPtOvEtCut();
  CheckYJBCut();
  CheckTimeCut();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GCal::CreateControl() called" << endl << endl;

  if ( gCards->GetCALControl() ) {

    Int_t    pxbins     =   60;
    Double_t pxlow      =  -30.;
    Double_t pxhigh     =   30.;  
    Int_t    pybins     =   60;
    Double_t pylow      =  -30.;
    Double_t pyhigh     =   30.;  
    Int_t    pzbins     =  200;
    Double_t pzlow      =  -40.;
    Double_t pzhigh     =  600.;  
    Int_t    ebins      =  200;
    Double_t elow       =    0.;
    Double_t ehigh      =  600.;  
    Int_t    etbins     =  200;
    Double_t etlow      =    0.;
    Double_t ethigh     =  200.;  
    Int_t    empzbins   =  100;
    Double_t empzlow    =    0.;
    Double_t empzhigh   =  100.;  
    Int_t    ptbins     =   50;
    Double_t ptlow      =    0.;
    Double_t pthigh     =   50.;  
    Int_t    yjbbins    =   50;
    Double_t yjblow     =    0.;
    Double_t yjbhigh    =    1.;  
    Int_t    timebins   =  140;
    Double_t timelow    =  -70.0;
    Double_t timehigh   =   70.0;
    Int_t ptovetbins =   20;
    Double_t ptovetlow  =    0.;
    Double_t ptovethigh =    1.;
    
    fControlpx = gHistogrammer->TH1DFactory("Cal_Control","px","CAL: p_{x}",pxbins,pxlow,pxhigh,"p_{x} [GeV]","Events");
    fControlpy = gHistogrammer->TH1DFactory("Cal_Control","py","CAL: p_{y}",pybins,pylow,pyhigh,"p_{y} [GeV]","Events");
    fControlpz = gHistogrammer->TH1DFactory("Cal_Control","pz","CAL: p_{z}",pzbins,pzlow,pzhigh,"p_{z} [GeV]","Events");
    fControlE = gHistogrammer->TH1DFactory("Cal_Control","E","CAL: E",ebins,elow,ehigh,"E [GeV]","Events");
    fControlEt = gHistogrammer->TH1DFactory("Cal_Control","Et","CAL: E_{T} minus 2 inner rings",etbins,etlow,ethigh,"E_{T} [GeV]","Events");
    fControlEmpz = gHistogrammer->TH1DFactory("Cal_Control","Empz","CAL: E-p_{z}",empzbins,empzlow,empzhigh,"E-p_{z} [GeV]","Events");
    fControlPt = gHistogrammer->TH1DFactory("Cal_Control","Pt","CAL: p_{t} ",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fControlPtOvEt = gHistogrammer->TH1DFactory("Cal_Control","PtOvEt","CAL: p_{T}/E_{T} ",ptovetbins,ptovetlow,ptovethigh,"p_{T}/E_{T}","Events");
    fControlYJB = gHistogrammer->TH1DFactory("Cal_Control","YJB","Cal: y_{JB}",yjbbins,yjblow,yjbhigh,"y_{JB}","Events");
    fControlTime = gHistogrammer->TH1DFactory("Cal_Control","Time","Cal: Time(cal_tg)",timebins,timelow,timehigh,"t [ns]","Events");

    fControlpx_uncut = gHistogrammer->TH1DFactory("Cal_Control","px_uncut","uncut CAL: p_{x}",pxbins,pxlow,pxhigh,"p_{x} [GeV]","Events");
    fControlpy_uncut = gHistogrammer->TH1DFactory("Cal_Control","py_uncut","uncut CAL: p_{y}",pybins,pylow,pyhigh,"p_{y} [GeV]","Events");
    fControlpz_uncut = gHistogrammer->TH1DFactory("Cal_Control","pz_uncut","uncut CAL: p_{z}",pzbins,pzlow,pzhigh,"p_{z} [GeV]","Events");
    fControlE_uncut = gHistogrammer->TH1DFactory("Cal_Control","E_uncut","uncut CAL: E",ebins,elow,ehigh,"E [GeV]","Events");
    fControlEt_uncut = gHistogrammer->TH1DFactory("Cal_Control","Et_uncut","uncut CAL: E_{T} minus 2 inner rings",etbins,etlow,ethigh,"E_{T} [GeV]","Events");
    fControlEmpz_uncut = gHistogrammer->TH1DFactory("Cal_Control","Empz_uncut","uncut CAL: E-p_{z}",empzbins,empzlow,empzhigh,"E-p_{z} [GeV]","Events");
    fControlPt_uncut = gHistogrammer->TH1DFactory("Cal_Control","Pt_uncut","uncut CAL: p_{t} ",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fControlPtOvEt_uncut = gHistogrammer->TH1DFactory("Cal_Control","PtOvEt_uncut","uncut CAL: p_{T}/E_{T} ",ptovetbins,ptovetlow,ptovethigh,"p_{T}/E_{T}","Events");
    fControlYJB_uncut = gHistogrammer->TH1DFactory("Cal_Control","YJB_uncut","uncut Cal: y_{JB}",yjbbins,yjblow,yjbhigh,"y_{JB}","Events");
    fControlTime_uncut = gHistogrammer->TH1DFactory("Cal_Control","Time_uncut","uncut Cal: Time(cal_tg)",timebins,timelow,timehigh,"t [ns]","Events");

  }  

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::FillControl() {
  //
  // fill control plots
  if ( gDebug ) cout << endl << "GCal::FillControl() called" << endl << endl;

  if ( gCards->GetCALControl() ) {

    fControlpx_uncut->Fill(gData->Getcal_px());
    fControlpy_uncut->Fill(gData->Getcal_py());
    fControlpz_uncut->Fill(gData->Getcal_pz());
    fControlE_uncut->Fill(gData->Getcal_e());
    fControlEt_uncut->Fill(gData->Getcal_et()-gData->Getet2ir());
    fControlEmpz_uncut->Fill(fEmpz);
    fControlPt_uncut->Fill(fPt);
    fControlPtOvEt_uncut->Fill(fPtOvEt);
    fControlYJB_uncut->Fill(fYJB);
    fControlTime_uncut->Fill(gData->Getcal_tg());

    if ( GetYJBCut() ) {
      fControlpx->Fill(gData->Getcal_px());
      fControlpy->Fill(gData->Getcal_py());
      fControlpz->Fill(gData->Getcal_pz());
      fControlE->Fill(gData->Getcal_e());
      fControlEmpz->Fill(fEmpz);
      fControlPt->Fill(fPt);
      fControlYJB->Fill(fYJB);

    }

    if ( GetETCut() ) {
      fControlEt->Fill(gData->Getcal_et()-gData->Getet2ir());
    }
    if ( GetTimeCut() ) {
      fControlTime->Fill(gData->Getcal_tg());
    }
    if ( GetPtOvEtCut() ) {
      fControlPtOvEt->Fill(fPtOvEt);
    }


  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::Calc() {
  //
  // calculate jb properties
  if ( gDebug ) cout << endl << "GCal::Calc() called" << endl << endl;

  fPt     = TMath::Sqrt(TMath::Power(gData->Getcal_px(),2)+TMath::Power(gData->Getcal_py(),2));
  if ( gData->Getcal_et() != 0 )
    fPtOvEt = fPt/gData->Getcal_et();
  else
    fPtOvEt = -9999.99;
  fEmpz   = gData->Getcal_e()-gData->Getcal_pz();
  fYJB    = fEmpz / ( 2 * gCards->GetMachineEnergyLepton() );
  // calculate corrected cal_et value (e.g. subtract et in 10deg cone forward and also electron 
  // if there (cuts for sutracted electron are defined in sinstra block of the cards; use with 
  // option NOCUT if no selection is wanted.))
  if( gCards->GetCALModeETCut()==3 ) {    
    if( gCards->GetSinistraDIS() && gSinistra->GetDISSelectionCut() ){
      fETtocuton = gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10(); 
      //     cout<<"ISDIS!!"<<endl;
    }
    else{
      fETtocuton = gData->Getcal_et() - gData->Getcal_et10();
    }
  }
  else if(gCards->GetCALModeETCut()==2){
    fETtocuton = gData->Getcal_et() - gData->Getcal_et10();
  }
  else if(gCards->GetCALModeETCut()==1){
    fETtocuton = gData->Getcal_et();
  }
  else{
    fETtocuton = gData->Getcal_et() - gData->Getcal_et10();
    //    fETtocuton = gData->Getcal_et();
  }
//   cout<<endl<<"****************"<<endl<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
//   cout<<"DISDISDISDIS?: gData->Getsipt(0): "<<gData->Getsipt(0)<<endl;
//   cout<<"NO DIS?:       gData->Getsipt(0): "<<gData->Getsipt(0)<<endl;
//   cout<<"DIS check: cand:"<< gData->Getsincand()<<" y: "<<gData->Getsiyjb(0)<<" / "<<gData->Getsiyel(0)<<" q2 "<<gData->Getsiq2el(0)<<" empz: "<<gData->Getv_h_e_zu()-gData->Getv_h_pz_zu()<<endl;
//   cout<<"old method returns: "<<(gData->Getcal_et() - gData->Getcal_et10()) <<" and "<< (gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10()) <<endl;
//   cout<<"NEW method returns: "<<fETtocuton<<" and nothing!"<<endl;
  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::Reset() {
  //
  // reset on event by event basis
  if ( gDebug ) cout << endl << "GCal::Reset() called" << endl << endl;

  fPt        = -9999.99;
  fPtOvEt    = -9999.99;
  fEmpz      = -9999.99;
  fYJB       = -9999.99;
  fETtocuton = -9999.99;

  fYJBCut    = kFALSE;
  fETCut     = kFALSE;
  fPtOvEtCut = kFALSE;
  fTimeCut   = kFALSE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::CheckYJBCut() {
  //
  // check if event fulfils y_jb cut
  if ( gDebug ) cout << endl << "GCal::CheckYJBCut() called" << endl << endl;

  if ( ( fYJB >= gCards->GetCALYJBLOWCut() ) && ( fYJB <= gCards->GetCALYJBUPCut() ) )
    fYJBCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::CheckETCut() {
  //
  // check if event fulfils E_T minus 10 deg cone (.le. cal_et-2ir) cut
  // or, in case there is a good DIS electron, use (E_T - E_T_10 - sinistra_E_T)
  if ( gDebug ) cout << endl << "GCal::CheckETCut() called" << endl << endl;

  //  if ( (gData->Getcal_et()-gData->Getet2ir()) >= gCards->GetCALETCut() )
  // if DIS electron present cut on cal_et-sicalpt_t[0]-cal_et10
  // ************************ WARNING *****************************************
  // ************************ WARNING *****************************************
  // THIS MIGHT WORK JUST FOR DIMUON SETTINGS!!!!!!!!!!
  // NEEDS TO BE CHECKED BY BEN/OLI!!!!!!
  // ************************ WARNING *****************************************
  // ************************ WARNING *****************************************
  //  if( (gCards->GetSinistraDIS()== kFALSE &&  gSinistra->GetDISRemovalCut()==kFALSE) || (gCards->GetSinistraDIS() && gSinistra->GetDISSelectionCut() ) ) {
// //   if( (gCards->GetSinistraDIS() && gSinistra->GetDISSelectionCut() ) && 42 == 42 ) {    
// //     //    if ( (gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10()) >= gCards->GetCALETCut() ) { // new 050331
// // //       cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
// // //       cout<<"DISDISDISDIS: gData->Getsipt(0): "<<gData->Getsipt(0)<<endl;
// // //       cout<<"DIS check: cand:"<< gData->Getsincand()<<" y: "<<gData->Getsiyjb(0)<<" / "<<gData->Getsiyel(0)<<" q2 "<<gData->Getsiq2el(0)<<" empz: "<<gData->Getv_h_e_zu()-gData->Getv_h_pz_zu()<<endl;
// //       fETCut = kTRUE;
// //     }
// // //       cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
// // //       cout<<"DISDISDISDIS: gData->Getsipt(0): "<<gData->Getsipt(0)<<endl;
// // //       cout<<"DIS check: cand:"<< gData->Getsincand()<<" y: "<<gData->Getsiyjb(0)<<" / "<<gData->Getsiyel(0)<<" q2 "<<gData->Getsiq2el(0)<<" empz: "<<gData->Getv_h_e_zu()-gData->Getv_h_pz_zu()<<endl;
// //   }
// //   // no reasonable DIS candidate
// //   else{
    
// //     if ( (gData->Getcal_et() - gData->Getcal_et10()) >= gCards->GetCALETCut() ) { // new 050331
// // //        cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
// // //        cout<<"NO DIS: gData->Getsipt(0): "<<gData->Getsipt(0)<<endl;
// //       fETCut = kTRUE;
// //     }
// //   }
       if ( fETtocuton >= gCards->GetCALETCut() ) { // new 050410
	 fETCut = kTRUE;
       }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::CheckPtOvEtCut() {
  //
  // check if event fulfils Pt/Et cut
  if ( gDebug ) cout << endl << "GCal::CheckPtOvEtCut() called" << endl << endl;

  if ( fPtOvEt < gCards->GetCALPtOvEtCut() )
    fPtOvEtCut = kTRUE;
    
  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::CheckTimeCut() {
  //
  // check if abs of cal_tg is smaller than cut
  if ( gDebug ) cout << endl << "GCal::CheckTimeCut() called" << endl << endl;

  if ( TMath::Abs(gData->Getcal_tg()) <= gCards->GetCALTimeCut() )
    fTimeCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GCal::GetAllCuts() {
  //
  // return flag if event passes all cal cuts
  if ( gDebug ) cout << endl << "GCal::GetAllCuts() called" << endl << endl;

  if ( GetYJBCut() && GetETCut() && GetPtOvEtCut() && GetTimeCut() )
    return  kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

TString GCal::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GCal::PrintMessage() called" << endl << endl;

  TString dummy = "Calorimeter:\n\n";

  dummy.Append("Cal: ");
  
  dummy.Append(gInclude->FormatedChar(" cal_px: ",9));
  dummy.Append(gInclude->FormatedDouble(gData->Getcal_px(),4,2));
  dummy.Append(gInclude->FormatedChar(" cal_py: ",9));
  dummy.Append(gInclude->FormatedDouble(gData->Getcal_py(),4,2));
  dummy.Append(gInclude->FormatedChar(" cal_pz: ",9));
  dummy.Append(gInclude->FormatedDouble(gData->Getcal_pz(),4,2));
  dummy.Append(gInclude->FormatedChar(" cal_e: ",8));
  dummy.Append(gInclude->FormatedDouble(gData->Getcal_e(),4,2));
  dummy.Append(gInclude->FormatedChar(" cal_empz: ",11));
  dummy.Append(gInclude->FormatedDouble(fEmpz,4,2));
  dummy.Append(gInclude->FormatedChar(" cal_pt: ",9));
  dummy.Append(gInclude->FormatedDouble(fPt,4,2));
  dummy.Append(gInclude->FormatedChar(" yjb: ",11));
  dummy.Append(gInclude->FormatedDouble(fYJB,4,2));
  dummy.Append(gInclude->FormatedChar(" yjb-cut: ",11));
  dummy.Append(gInclude->FormatedBool(fYJBCut));
  dummy.Append(gInclude->FormatedChar(" et-cut: ",11));
  dummy.Append(gInclude->FormatedBool(fETCut));
  dummy.Append(gInclude->FormatedChar(" ptovet-cut: ",14));
  dummy.Append(gInclude->FormatedBool(fPtOvEtCut));
  dummy.Append(gInclude->FormatedChar(" time-cut: ",12));
  dummy.Append(gInclude->FormatedBool(fTimeCut));

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GCal::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GCal::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("CAL") || option.Contains("ALL") ) {
    gLister->FillOutputList(PrintMessage(option));
    gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}
