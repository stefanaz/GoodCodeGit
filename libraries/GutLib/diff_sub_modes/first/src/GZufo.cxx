//
// GZufo.cxx
//
// $Author: meyer $
// $Date: 2005/06/14 13:41:14 $
// $Revision: 1.36 $
//

#include <GZufo.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GZufo)
#endif

GZufo *gZufo = 0;

//_____________________________________________________________
// GZufo
// Zufo class for everything which is related only to ZUFOs
//
//
GZufo::GZufo() : GPhysObj() {
  //
  // GZufo default constructor
  if ( gDebug ) cout << endl << "GZufo::GZufo ctor called" << endl << endl;

  // initialize variable
  gZufo = this;

  // general histograms
  fGeneraln_uncut         = 0;
  fGeneralpx_uncut        = 0;
  fGeneralpy_uncut        = 0;
  fGeneralpz_uncut        = 0;
  fGeneralp_uncut         = 0;
  fGeneralpt_uncut        = 0;
  fGeneralE_uncut         = 0;
  fGeneralpx_had_uncut    = 0;
  fGeneralpy_had_uncut    = 0;
  fGeneralpz_had_uncut    = 0;
  fGeneralE_had_uncut     = 0;
  fGeneralEmpz_had_uncut  = 0;
  fGeneralPt_had_uncut    = 0;
  fGeneralYJB_had_uncut   = 0;
  fGeneralYJBvsYTrue_uncut= 0;

  fGeneraln               = 0;
  fGeneralpx              = 0;
  fGeneralpy              = 0;
  fGeneralpz              = 0;
  fGeneralp               = 0;
  fGeneralpt              = 0;
  fGeneralE               = 0;
  fGeneralpx_had          = 0;
  fGeneralpy_had          = 0;
  fGeneralpz_had          = 0;
  fGeneralE_had           = 0;
  fGeneralEmpz_had        = 0;
  fGeneralPt_had          = 0;
  fGeneralYJB_had         = 0;
  fGeneralQ2JB_had_1      = 0;
  fGeneralQ2JB_had_2      = 0;
  fGeneralQ2JB_had_3      = 0;
  fGeneralQ2JB_had        = 0;
  fGeneralYJBMinYTrue     = 0;
  fGeneralYJBvsYTrue      = 0;

  // control plots
  fControlpx_had_uncut    = 0;
  fControlpy_had_uncut    = 0;
  fControlpz_had_uncut    = 0;
  fControlE_had_uncut     = 0;
  fControlEmpz_had_uncut  = 0;
  fControlPt_had_uncut    = 0;
  fControlYJB_had_uncut   = 0;

  fControlpx_had          = 0;
  fControlpy_had          = 0;
  fControlpz_had          = 0;
  fControlE_had           = 0;
  fControlEmpz_had        = 0;
  fControlPt_had          = 0;
  fControlYJB_had         = 0;

  fControlTUFO_First      = 0;
  fControlTUFO_Second     = 0;
  fControlTUFO_Third      = 0;
  fControlTUFO_Fourth     = 0;

  // initialize variables
  fPt_had   = -9999.99;
  fEmpz_had = -9999.99;
  fYJB_had  = -9999.99;
  fQ2JB_had = -9999.99;
  fRapid_Y  = -9999.99;
  fQ2Prime  = -9999.99;
  fZufoEta  = -9999.99;
  fZufoPt   = -9999.99;

  fYJBCut        = kFALSE;
  fEmpzCut       = kFALSE;
  fQ2PrimeLowCut = kFALSE;
  fPtHadMaxCut   = kFALSE;
  /*
  fQ2Prime_True   = -9999.99;
  fHadronEta_True = -9999.99;
  fHadronPt_True  = -9999.99;
  */
  fdelta_R_muzu    = 9999.;     
  fdelta_R_muzumin = 99.;    
  fzufo_ptmin      = 0.;          
  ftufocode        = 0;             

  for(Int_t reset=0; reset<fnbins_iso; ++reset) {
    fmuis[reset]  = 0.;
  }
  
  fzufo_perhaps_muon = false;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GZufo::~GZufo() {
  //
  // GZufo default destructor
  if ( gDebug ) cout << endl << "GZufo::~GZufo dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GZufo::CreateGeneral() {
  //
  // create general histograms for zufos
  if ( gDebug ) cout << endl << "GZufo::CreateGeneral() called" << endl << endl;

  // create general histograms

  if ( gCards->GetZUFOGeneral() ) {

    Int_t    nbins    =  100;
    Double_t nlow     =    0.;
    Double_t nhigh    =  100.;
    Int_t    pxbins   =   40;
    Double_t pxlow    =  -20.;
    Double_t pxhigh   =   20.;  
    Int_t    pybins   =   40;
    Double_t pylow    =  -20.;
    Double_t pyhigh   =   20.;  
    Int_t    pzbins   =  340;
    Double_t pzlow    =  -40.;
    Double_t pzhigh   =  300.;  
    Int_t    pbins    =  150;
    Double_t plow     =    0.;
    Double_t phigh    =  300.;  
    Int_t    ebins    =  300;
    Double_t elow     =    0.;
    Double_t ehigh    =  300.;  
    Int_t    empzbins =  100;
    Double_t empzlow  =    0.;
    Double_t empzhigh =  100.;  
    Int_t    ptbins   =   25;
    Double_t ptlow    =    0.;
    Double_t pthigh   =   25.;  
    Int_t    yjbbins  =   50;
    Double_t yjblow   =    0.;
    Double_t yjbhigh  =    1.;  
    Int_t    q2jbbins =   30;
    Double_t q2jblow  =   -10.;
    Double_t q2jbhigh =    5.;  

    Int_t    yjbminbins  =   50;
    Double_t yjbminlow   =    -1.;
    Double_t yjbminhigh  =     1.;  

    fGeneraln_uncut  = gHistogrammer->TH1DFactory("Zufo","n_uncut","uncut number of zufos",nbins,nlow,nhigh,"number of zufos","Events");
    fGeneralpx_uncut = gHistogrammer->TH1DFactory("Zufo","px_uncut","uncut p_{x}",pxbins,pxlow,pxhigh,"p_{x} [GeV]","Events");
    fGeneralpy_uncut = gHistogrammer->TH1DFactory("Zufo","py_uncut","uncut p_{y}",pybins,pylow,pyhigh,"p_{y} [GeV]","Events");
    fGeneralpz_uncut = gHistogrammer->TH1DFactory("Zufo","pz_uncut","uncut p_{z}",pzbins,pzlow,pzhigh,"p_{z} [GeV]","Events");
    fGeneralp_uncut  = gHistogrammer->TH1DFactory("Zufo","p_uncut","uncut p",pbins,plow,phigh,"p [GeV]","Events");
    fGeneralpt_uncut = gHistogrammer->TH1DFactory("Zufo","pt_uncut","uncut p_{t}",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fGeneralE_uncut  = gHistogrammer->TH1DFactory("Zufo","E_uncut","uncut E",ebins,elow,ehigh,"E [GeV]","Events");

    fGeneralpx_had_uncut = gHistogrammer->TH1DFactory("Zufo","px_had_uncut","uncut p_{x,had}",pxbins,pxlow,pxhigh,"p_{x,had} [GeV]","Events");
    fGeneralpy_had_uncut = gHistogrammer->TH1DFactory("Zufo","py_had_uncut","uncut p_{y,had}",pybins,pylow,pyhigh,"p_{y,had} [GeV]","Events");
    fGeneralpz_had_uncut = gHistogrammer->TH1DFactory("Zufo","pz_had_uncut","uncut p_{z,had}",pzbins,pzlow,pzhigh,"p_{z,had} [GeV]","Events");
    fGeneralE_had_uncut = gHistogrammer->TH1DFactory("Zufo","E_had_uncut","uncut E_{had}",ebins,elow,ehigh,"E_{had} [GeV]","Events");
    fGeneralEmpz_had_uncut = gHistogrammer->TH1DFactory("Zufo","Empz_had_uncut","uncut E-p_{z} (had)",empzbins,empzlow,empzhigh,"E-p_{z} (had) [GeV]","Events");
    fGeneralPt_had_uncut = gHistogrammer->TH1DFactory("Zufo","Pt_had_uncut","uncut p_{t,had} ",ptbins,ptlow,pthigh,"p_{t,had} [GeV]","Events");
    fGeneralYJB_had_uncut = gHistogrammer->TH1DFactory("Zufo","YJB_had_uncut","uncut y_{JB,had}",yjbbins,yjblow,yjbhigh,"y_{JB,had}","Events");
    fGeneralYJBvsYTrue_uncut = gHistogrammer->TH2DFactory("Zufo","YJBvsYTrue_uncut","uncut y_{JB,had} vs. y_{MC,true}",yjbbins,yjblow,yjbhigh,yjbbins,yjblow,yjbhigh,"y_{JB,had}","y_{MC,true}","Events");

    fGeneraln  = gHistogrammer->TH1DFactory("Zufo","n","number of zufos",nbins,nlow,nhigh,"number of zufos","Events");
    fGeneralpx = gHistogrammer->TH1DFactory("Zufo","px","p_{x}",pxbins,pxlow,phigh,"p_{x} [GeV]","Events");
    fGeneralpy = gHistogrammer->TH1DFactory("Zufo","py","p_{y}",pybins,pylow,pyhigh,"p_{y} [GeV]","Events");
    fGeneralpz = gHistogrammer->TH1DFactory("Zufo","pz","p_{z}",pybins,pzlow,pzhigh,"p_{z} [GeV]","Events");
    fGeneralp  = gHistogrammer->TH1DFactory("Zufo","p","p",pbins,plow,phigh,"p [GeV]","Events");
    fGeneralpt = gHistogrammer->TH1DFactory("Zufo","pt","p_{t}",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fGeneralE  = gHistogrammer->TH1DFactory("Zufo","E","E",ebins,elow,ehigh,"E [GeV]","Events");

    fGeneralpx_had   = gHistogrammer->TH1DFactory("Zufo","px_had","p_{x,had}",pxbins,pxlow,pxhigh,"p_{x,had} [GeV]","Events");
    fGeneralpy_had   = gHistogrammer->TH1DFactory("Zufo","py_had","p_{y,had}",pybins,pylow,pyhigh,"p_{y,had} [GeV]","Events");
    fGeneralpz_had   = gHistogrammer->TH1DFactory("Zufo","pz_had","p_{z,had}",pzbins,pzlow,pzhigh,"p_{z,had} [GeV]","Events");
    fGeneralE_had    = gHistogrammer->TH1DFactory("Zufo","E_had","E_{had}",ebins,elow,ehigh,"E_{had} [GeV]","Events");
    fGeneralEmpz_had = gHistogrammer->TH1DFactory("Zufo","Empz_had","E-p_{z} (had)",empzbins,empzlow,empzhigh,"E-p_{z} (had) [GeV]","Events");
    fGeneralPt_had   = gHistogrammer->TH1DFactory("Zufo","Pt_had","p_{t,had} ",ptbins,ptlow,pthigh,"p_{t,had} [GeV]","Events");
    fGeneralYJB_had  = gHistogrammer->TH1DFactory("Zufo","YJB_had","y_{JB,had}",yjbbins,yjblow,yjbhigh,"y_{JB,had}","Events");
    fGeneralQ2JB_had = gHistogrammer->TH1DFactory("Zufo","Q2JB_had","Q^{2}_{JB,had}",q2jbbins,q2jblow,q2jbhigh,"log_{10}(Q^{2}_{JB,had})","Events");
    fGeneralQ2JB_had_1 = gHistogrammer->TH1DFactory("Zufo","Q2JB_had_1","Q^{2}_{JB,had}",q2jbbins,q2jblow,q2jbhigh,"log_{10}(Q^{2}_{JB,had})","Events");
    fGeneralQ2JB_had_2 = gHistogrammer->TH1DFactory("Zufo","Q2JB_had_2","Q^{2}_{JB,had}",q2jbbins,q2jblow,q2jbhigh,"log_{10}(Q^{2}_{JB,had})","Events");
    fGeneralQ2JB_had_3 = gHistogrammer->TH1DFactory("Zufo","Q2JB_had_3","Q^{2}_{JB,had}",q2jbbins,q2jblow,q2jbhigh,"log_{10}(Q^{2}_{JB,had})","Events");
    fGeneralYJBMinYTrue = gHistogrammer->TH1DFactory("Zufo","YJBMinYTrue","(y_{JB}-y_{true})/y_{true}",yjbminbins,yjbminlow,yjbminhigh,"(y_{JB}-y_{true})/y_{true}","Events");
    fGeneralYJBvsYTrue = gHistogrammer->TH2DFactory("Zufo","YJBvsYTrue","y_{JB,had} vs. y_{MC,true}",yjbbins,yjblow,yjbhigh,yjbbins,yjblow,yjbhigh,"y_{JB,had}","y_{MC,true}","Events");

  }
    return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::FillGeneral() {
  //
  // fill general histograms for zufos
  if ( gDebug ) cout << endl << "GZufo::FillGeneral() called" << endl << endl;

  if ( gCards->GetZUFOGeneral() ) {
    fGeneraln_uncut->Fill(gData->Getnzufos(),gHeader->GetWeight());
    
    if ( gHeader->GetAllCuts() ) {
      fGeneraln->Fill(gData->Getnzufos(),gHeader->GetWeight());
    }
    
    fGeneralpx_had_uncut->Fill(gData->Getv_h_px_zu(),gHeader->GetWeight());
    fGeneralpy_had_uncut->Fill(gData->Getv_h_py_zu(),gHeader->GetWeight());
    fGeneralpz_had_uncut->Fill(gData->Getv_h_pz_zu(),gHeader->GetWeight());
    fGeneralE_had_uncut->Fill(gData->Getv_h_e_zu(),gHeader->GetWeight());
    fGeneralEmpz_had_uncut->Fill(fEmpz_had,gHeader->GetWeight());
    fGeneralPt_had_uncut->Fill(fPt_had,gHeader->GetWeight());
    fGeneralYJB_had_uncut->Fill(fYJB_had,gHeader->GetWeight());
    fGeneralYJBvsYTrue_uncut->Fill(fYJB_had,gData->Getmc_y(),gHeader->GetWeight());
  
    // loop over all zufos (?)
    for (Int_t i = 0; i < gData->Getnzufos(); i++ ) {

      Double_t p  = TMath::Sqrt(gData->Getzufo(i,0)*gData->Getzufo(i,0)+gData->Getzufo(i,1)*gData->Getzufo(i,1)+gData->Getzufo(i,2)*gData->Getzufo(i,2));
      Double_t pt = TMath::Sqrt(gData->Getzufo(i,0)*gData->Getzufo(i,0)+gData->Getzufo(i,1)*gData->Getzufo(i,1));

      fGeneralpx_uncut -> Fill(gData->Getzufo(i,0),gHeader->GetWeight());
      fGeneralpy_uncut -> Fill(gData->Getzufo(i,1),gHeader->GetWeight());
      fGeneralpz_uncut -> Fill(gData->Getzufo(i,2),gHeader->GetWeight());
      fGeneralp_uncut  -> Fill(p,gHeader->GetWeight());
      fGeneralpt_uncut -> Fill(pt,gHeader->GetWeight());
      fGeneralE_uncut  -> Fill(gData->Getzufo(i,3),gHeader->GetWeight());
    
      if ( gHeader->GetAllCuts() ) {
	fGeneralpx -> Fill(gData->Getzufo(i,0),gHeader->GetWeight());
	fGeneralpy -> Fill(gData->Getzufo(i,1),gHeader->GetWeight());
	fGeneralpz -> Fill(gData->Getzufo(i,2),gHeader->GetWeight());
	fGeneralp  -> Fill(p,gHeader->GetWeight());
	fGeneralpt -> Fill(pt,gHeader->GetWeight());
	fGeneralE  -> Fill(gData->Getzufo(i,3),gHeader->GetWeight());
      }
    }

    if ( gTrigger->GetAllCuts() ) {
      fGeneralQ2JB_had_1->Fill(TMath::Log10(fQ2JB_had),gHeader->GetWeight());
    }
    if ( gTrigger->GetAllCuts() && gSinistra->GetAllCuts() ) {
      fGeneralQ2JB_had_2->Fill(TMath::Log10(fQ2JB_had),gHeader->GetWeight());
    }
    if ( gTrigger->GetAllCuts() && gSinistra->GetAllCuts() && GetYJBCut() ) {
      fGeneralQ2JB_had_3->Fill(TMath::Log10(fQ2JB_had),gHeader->GetWeight());
    }

    if ( gHeader->GetAllCuts() ) {
      fGeneralpx_had   -> Fill(gData->Getv_h_px_zu(),gHeader->GetWeight());
      fGeneralpy_had   -> Fill(gData->Getv_h_py_zu(),gHeader->GetWeight());
      fGeneralpz_had   -> Fill(gData->Getv_h_pz_zu(),gHeader->GetWeight());
      fGeneralE_had    -> Fill(gData->Getv_h_e_zu(),gHeader->GetWeight());
      fGeneralEmpz_had -> Fill(fEmpz_had,gHeader->GetWeight());
      fGeneralPt_had   -> Fill(fPt_had,gHeader->GetWeight());
      fGeneralYJB_had  -> Fill(fYJB_had,gHeader->GetWeight());
      fGeneralQ2JB_had -> Fill(TMath::Log10(fQ2JB_had),gHeader->GetWeight());

      if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
	if ( gData->Getmc_y() != 0 ) {
	  fGeneralYJBMinYTrue->Fill((fYJB_had-gData->Getmc_y())/gData->Getmc_y(),gHeader->GetWeight());
	}
	fGeneralYJBvsYTrue->Fill(fYJB_had,gData->Getmc_y(),gHeader->GetWeight());
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::CreateControl() {
  //
  // create control histograms for zufos
  if ( gDebug ) cout << endl << "GZufo::CreateControl() called" << endl << endl;

  // create control histograms

  if ( gCards->GetZUFOControl() ) {

    Int_t    pxbins   =   60;
    Double_t pxlow    =  -30.;
    Double_t pxhigh   =   30.;  
    Int_t    pybins   =   60;
    Double_t pylow    =  -30.;
    Double_t pyhigh   =   30.;  
    Int_t    pzbins   =  200;
    Double_t pzlow    =  -40.;
    Double_t pzhigh   =  600.;  
    Int_t    ebins    =  200;
    Double_t elow     =    0.;
    Double_t ehigh    =  600.;  
    Int_t    empzbins =  100;
    Double_t empzlow  =    0.;
    Double_t empzhigh =  100.;  
    Int_t    ptbins   =   50;
    Double_t ptlow    =    0.;
    Double_t pthigh   =   50.;  
    Int_t    yjbbins  =   50;
    Double_t yjblow   =    0.;
    Double_t yjbhigh  =    1.;  
    
    fControlpx_had_uncut = gHistogrammer->TH1DFactory("Zufo_Control","px_had_uncut","uncut p_{x,had}",pxbins,pxlow,pxhigh,"p_{x,had} [GeV]","Events");
    fControlpy_had_uncut = gHistogrammer->TH1DFactory("Zufo_Control","py_had_uncut","uncut p_{y,had}",pybins,pylow,pyhigh,"p_{y,had} [GeV]","Events");
    fControlpz_had_uncut = gHistogrammer->TH1DFactory("Zufo_Control","pz_had_uncut","uncut p_{z,had}",pzbins,pzlow,pzhigh,"p_{z,had} [GeV]","Events");
    fControlE_had_uncut  = gHistogrammer->TH1DFactory("Zufo_Control","E_had_uncut","uncut E_{had}",ebins,elow,ehigh,"E_{had} [GeV]","Events");
    fControlEmpz_had_uncut = gHistogrammer->TH1DFactory("Zufo_Control","Empz_had_uncut","uncut E-p_{z} (had)",empzbins,empzlow,empzhigh,"E-p_{z} (had) [GeV]","Events");
    fControlPt_had_uncut   = gHistogrammer->TH1DFactory("Zufo_Control","Pt_had_uncut","uncut p_{t,had} ",ptbins,ptlow,pthigh,"p_{t,had} [GeV]","Events");
    fControlYJB_had_uncut  = gHistogrammer->TH1DFactory("Zufo_Control","YJB_had_uncut","uncut y_{JB,had}",yjbbins,yjblow,yjbhigh,"y_{JB,had}","Events");

    fControlpx_had   = gHistogrammer->TH1DFactory("Zufo_Control","px_had","p_{x,had}",pxbins,pxlow,pxhigh,"p_{x,had} [GeV]","Events");
    fControlpy_had   = gHistogrammer->TH1DFactory("Zufo_Control","py_had","p_{y,had}",pybins,pylow,pyhigh,"p_{y,had} [GeV]","Events");
    fControlpz_had   = gHistogrammer->TH1DFactory("Zufo_Control","pz_had","p_{z,had}",pzbins,pzlow,pzhigh,"p_{z,had} [GeV]","Events");
    fControlE_had    = gHistogrammer->TH1DFactory("Zufo_Control","E_had","E_{had}",ebins,elow,ehigh,"E_{had} [GeV]","Events");
    fControlEmpz_had = gHistogrammer->TH1DFactory("Zufo_Control","Empz_had","E-p_{z} (had)",empzbins,empzlow,empzhigh,"E-p_{z} (had) [GeV]","Events");
    fControlPt_had  = gHistogrammer->TH1DFactory("Zufo_Control","Pt_had","p_{t,had} ",ptbins,ptlow,pthigh,"p_{t,had} [GeV]","Events");
    fControlYJB_had = gHistogrammer->TH1DFactory("Zufo_Control","YJB_had","y_{JB,had}",yjbbins,yjblow,yjbhigh,"y_{JB,had}","Events");

    fControlTUFO_First  = gHistogrammer->TH1DFactory("Zufo_Control","TUFO_First","TUFO[0,i]",50,0.,50.,"TUFO[0,i]","Events");
    fControlTUFO_Second = gHistogrammer->TH1DFactory("Zufo_Control","TUFO_Second","TUFO[1,i]",100,0.,100.,"TUFO[1,i]","Events");
    fControlTUFO_Third  = gHistogrammer->TH1DFactory("Zufo_Control","TUFO_Third","TUFO[2,i]",100,0.,100.,"TUFO[2,i]","Events");
    fControlTUFO_Fourth = gHistogrammer->TH1DFactory("Zufo_Control","TUFO_Fourth","TUFO[3,i]",100,0.,100.,"TUFO[3,i]","Events");

  }
    return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::FillControl() {
  //
  // fill control histograms for zufos
  if ( gDebug ) cout << endl << "GZufo::FillControl() called" << endl << endl;

  if ( gCards->GetZUFOControl() ) {
    // loop over all zufos (?)
    for (Int_t i = 0; i < gData->Getnzufos(); i++ ) {

      fControlTUFO_First  -> Fill(gData->Gettufo(i,0));
      fControlTUFO_Second -> Fill(gData->Gettufo(i,1));
      fControlTUFO_Third  -> Fill(gData->Gettufo(i,2));
      fControlTUFO_Fourth -> Fill(gData->Gettufo(i,3));
    }

    fControlpx_had_uncut   -> Fill(gData->Getv_h_px_zu());
    fControlpy_had_uncut   -> Fill(gData->Getv_h_py_zu());
    fControlpz_had_uncut   -> Fill(gData->Getv_h_pz_zu());
    fControlE_had_uncut    -> Fill(gData->Getv_h_e_zu());
    fControlEmpz_had_uncut -> Fill(fEmpz_had);
    fControlPt_had_uncut   -> Fill(fPt_had);
    fControlYJB_had_uncut  -> Fill(fYJB_had);
    
    if ( gHeader->GetAllCuts() ) {
      fControlpx_had   -> Fill(gData->Getv_h_px_zu());
      fControlpy_had   -> Fill(gData->Getv_h_py_zu());
      fControlpz_had   -> Fill(gData->Getv_h_pz_zu());
      fControlE_had    -> Fill(gData->Getv_h_e_zu());
      fControlEmpz_had -> Fill(fEmpz_had);
      fControlPt_had   -> Fill(fPt_had);
      fControlYJB_had  -> Fill(fYJB_had);
    }

  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::Do() {
  //
  // execute per event
  if ( gDebug ) cout << endl << "GZufo::Do() called" << endl << endl;

  Calc();

  CheckYJBCut();
  CheckEmpzCut();
  CheckPtHadMaxCut();

  return kTRUE;

}

//_____________________________________________________________

Bool_t GZufo::Calc() {
  //
  // calculate jb properties
  if ( gDebug ) cout << endl << "GZufo::Calc() called" << endl << endl;

  fPt_had   = TMath::Sqrt(TMath::Power(gData->Getv_h_px_zu(),2)+TMath::Power(gData->Getv_h_py_zu(),2));
  fEmpz_had = gData->Getv_h_e_zu()-gData->Getv_h_pz_zu();
  fYJB_had  = fEmpz_had / ( 2 * gCards->GetMachineEnergyLepton() );
  fQ2JB_had = fPt_had/(1-fYJB_had);
  fRapid_Y  = 0.5*log(920/(27.5*fYJB_had));

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::CalcIsolation(GTriMuon *trimuon) {
//
// calculate trimuon isolation
    if ( gDebug ) cout << endl << "GZufo::CalcIsolation(trimuon) called" << endl << endl;

    //   fPt_had   = TMath::Sqrt(TMath::Power(gData->Getv_h_px_zu(),2)+TMath::Power(gData->Getv_h_py_zu(),2));
  //   fEmpz_had = gData->Getv_h_e_zu()-gData->Getv_h_pz_zu();
  //   fYJB_had  = fEmpz_had / ( 2 * gCards->GetMachineEnergyLepton() );
    // add up seperate muon isolations - linear and squared:
    GMuon *muon1 = trimuon->GetMuon1();
    GMuon *muon2 = trimuon->GetMuon2();

    Double_t muon1_zufopt = TMath::Sqrt( TMath::Power(gData->Getzufo(  ((muon1->GetZufoID())-1) , 0 ),2) + TMath::Power(gData->Getzufo(  ((muon1->GetZufoID())-1) , 1 ),2) ) ;
    Double_t muon2_zufopt = TMath::Sqrt( TMath::Power(gData->Getzufo(  ((muon2->GetZufoID())-1) , 0 ),2) + TMath::Power(gData->Getzufo(  ((muon2->GetZufoID())-1) , 1 ),2) ) ;
    

    // Calculate Isolation for both muons seperatelty:
    CalcIsolation( muon1 );
    CalcIsolation( muon2 );


    Double_t Isol1_01 = muon1->GetIsolation01();
    Double_t Isol1_02 = muon1->GetIsolation02();
    Double_t Isol1_03 = muon1->GetIsolation03();
    Double_t Isol1_04 = muon1->GetIsolation04();
    Double_t Isol1_05 = muon1->GetIsolation05();
    Double_t Isol1_06 = muon1->GetIsolation06();
    Double_t Isol1_07 = muon1->GetIsolation07();
    Double_t Isol1_08 = muon1->GetIsolation08();
    Double_t Isol1_09 = muon1->GetIsolation09();
    Double_t Isol1_10 = muon1->GetIsolation10();
    
    Double_t Isol2_01 = muon2->GetIsolation01();
    Double_t Isol2_02 = muon2->GetIsolation02();
    Double_t Isol2_03 = muon2->GetIsolation03();
    Double_t Isol2_04 = muon2->GetIsolation04();
    Double_t Isol2_05 = muon2->GetIsolation05();
    Double_t Isol2_06 = muon2->GetIsolation06();
    Double_t Isol2_07 = muon2->GetIsolation07();
    Double_t Isol2_08 = muon2->GetIsolation08();
    Double_t Isol2_09 = muon2->GetIsolation09();
    Double_t Isol2_10 = muon2->GetIsolation10();

    // subtract still undetected muon zufo_pt. All recognised muons (by Massimos "zufo is muon" flag) are subtracted already from single muon isolation.
    if( muon1->DeltaR(*muon2) < 1.0 ) { 
      // less than 999 does not seem to happen, but occasional its > 1e9 - what does this imply - a bug? 041011
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) { // subtract muzufopt1 from muis2 if muon1 is not flagged (i.e tufo[zufoid][0] <= 999 ) and inside DR cone of 1. 041011
	//	cout<<"GZufo::CalcIsolation(dimuon) - subtracting muzufopt1 from Isol2_10: before iso value: "<<Isol2_10;
	Isol2_10 -= muon1_zufopt; 
	//	cout<<" after iso value: "<<Isol2_10<<endl;
      }
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) { // subtract muzufopt2 from muis1 if muon2 is not flagged (i.e tufo[zufoid][0] <= 999 ) and inside DR cone of 1. 041011
	//	cout<<"GZufo::CalcIsolation(dimuon) - subtracting muzufopt2 from Isol1_10: before iso value: "<<Isol1_10;
	Isol1_10 -= muon2_zufopt;
	//	cout<<" after iso value: "<<Isol1_10<<endl;
      }
    }
    if( muon1->DeltaR(*muon2) < 0.9 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_09 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_09 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.8 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_08 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_08 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.7 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_07 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_07 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.6 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_06 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_06 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.5 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_05 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_05 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.4 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_04 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_04 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.3 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_03 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_03 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.2 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_02 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_02 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.1 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_01 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_01 -= muon2_zufopt; 
    }

      fmuissum[0]   = Isol1_01 + Isol2_01;
      fmuissum[1]   = Isol1_02 + Isol2_02;
      fmuissum[2]   = Isol1_03 + Isol2_03;
      fmuissum[3]   = Isol1_04 + Isol2_04;
      fmuissum[4]   = Isol1_05 + Isol2_05;
      fmuissum[5]   = Isol1_06 + Isol2_06;
      fmuissum[6]   = Isol1_07 + Isol2_07;
      fmuissum[7]   = Isol1_08 + Isol2_08;
      fmuissum[8]   = Isol1_09 + Isol2_09;
      fmuissum[9]   = Isol1_10 + Isol2_10;
   
      fmuissqsum[0] = TMath::Sqrt( (Isol1_01 * Isol1_01)  +  (Isol2_01 * Isol2_01));
      fmuissqsum[1] = TMath::Sqrt( (Isol1_02 * Isol1_02)  +  (Isol2_02 * Isol2_02));
      fmuissqsum[2] = TMath::Sqrt( (Isol1_03 * Isol1_03)  +  (Isol2_03 * Isol2_03));
      fmuissqsum[3] = TMath::Sqrt( (Isol1_04 * Isol1_04)  +  (Isol2_04 * Isol2_04));
      fmuissqsum[4] = TMath::Sqrt( (Isol1_05 * Isol1_05)  +  (Isol2_05 * Isol2_05));
      fmuissqsum[5] = TMath::Sqrt( (Isol1_06 * Isol1_06)  +  (Isol2_06 * Isol2_06));
      fmuissqsum[6] = TMath::Sqrt( (Isol1_07 * Isol1_07)  +  (Isol2_07 * Isol2_07));
      fmuissqsum[7] = TMath::Sqrt( (Isol1_08 * Isol1_08)  +  (Isol2_08 * Isol2_08));
      fmuissqsum[8] = TMath::Sqrt( (Isol1_09 * Isol1_09)  +  (Isol2_09 * Isol2_09));
      fmuissqsum[9] = TMath::Sqrt( (Isol1_10 * Isol1_10)  +  (Isol2_10 * Isol2_10));
 
    trimuon->SetIsolationSum01( fmuissum[0] );
    trimuon->SetIsolationSum02( fmuissum[1] );
    trimuon->SetIsolationSum03( fmuissum[2] );
    trimuon->SetIsolationSum04( fmuissum[3] );
    trimuon->SetIsolationSum05( fmuissum[4] );
    trimuon->SetIsolationSum06( fmuissum[5] );
    trimuon->SetIsolationSum07( fmuissum[6] );
    trimuon->SetIsolationSum08( fmuissum[7] );
    trimuon->SetIsolationSum09( fmuissum[8] );
    trimuon->SetIsolationSum10( fmuissum[9] );
    
    trimuon->SetIsolationSqSum01( fmuissqsum[0] );
    trimuon->SetIsolationSqSum02( fmuissqsum[1] );
    trimuon->SetIsolationSqSum03( fmuissqsum[2] );
    trimuon->SetIsolationSqSum04( fmuissqsum[3] );
    trimuon->SetIsolationSqSum05( fmuissqsum[4] );
    trimuon->SetIsolationSqSum06( fmuissqsum[5] );
    trimuon->SetIsolationSqSum07( fmuissqsum[6] );
    trimuon->SetIsolationSqSum08( fmuissqsum[7] );
    trimuon->SetIsolationSqSum09( fmuissqsum[8] );
    trimuon->SetIsolationSqSum10( fmuissqsum[9] );
   
    return kTRUE;
  }

//_____________________________________________________________

  Bool_t GZufo::CalcIsolation(GDIMuon *dimuon) {
//
// calculate dimuon isolation
    if ( gDebug ) cout << endl << "GZufo::CalcIsolation(dimuon) called" << endl << endl;

    //   fPt_had   = TMath::Sqrt(TMath::Power(gData->Getv_h_px_zu(),2)+TMath::Power(gData->Getv_h_py_zu(),2));
  //   fEmpz_had = gData->Getv_h_e_zu()-gData->Getv_h_pz_zu();
  //   fYJB_had  = fEmpz_had / ( 2 * gCards->GetMachineEnergyLepton() );
    // add up seperate muon isolations - linear and squared:
    GMuon *muon1 = dimuon->GetMuon1();
    GMuon *muon2 = dimuon->GetMuon2();

    Double_t muon1_zufopt = TMath::Sqrt( TMath::Power(gData->Getzufo(  ((muon1->GetZufoID())-1) , 0 ),2) + TMath::Power(gData->Getzufo(  ((muon1->GetZufoID())-1) , 1 ),2) ) ;
    Double_t muon2_zufopt = TMath::Sqrt( TMath::Power(gData->Getzufo(  ((muon2->GetZufoID())-1) , 0 ),2) + TMath::Power(gData->Getzufo(  ((muon2->GetZufoID())-1) , 1 ),2) ) ;
    

    // Calculate Isolation for both muons seperatelty:
    CalcIsolation( muon1 );
    CalcIsolation( muon2 );


    Double_t Isol1_01 = muon1->GetIsolation01();
    Double_t Isol1_02 = muon1->GetIsolation02();
    Double_t Isol1_03 = muon1->GetIsolation03();
    Double_t Isol1_04 = muon1->GetIsolation04();
    Double_t Isol1_05 = muon1->GetIsolation05();
    Double_t Isol1_06 = muon1->GetIsolation06();
    Double_t Isol1_07 = muon1->GetIsolation07();
    Double_t Isol1_08 = muon1->GetIsolation08();
    Double_t Isol1_09 = muon1->GetIsolation09();
    Double_t Isol1_10 = muon1->GetIsolation10();
    
    Double_t Isol2_01 = muon2->GetIsolation01();
    Double_t Isol2_02 = muon2->GetIsolation02();
    Double_t Isol2_03 = muon2->GetIsolation03();
    Double_t Isol2_04 = muon2->GetIsolation04();
    Double_t Isol2_05 = muon2->GetIsolation05();
    Double_t Isol2_06 = muon2->GetIsolation06();
    Double_t Isol2_07 = muon2->GetIsolation07();
    Double_t Isol2_08 = muon2->GetIsolation08();
    Double_t Isol2_09 = muon2->GetIsolation09();
    Double_t Isol2_10 = muon2->GetIsolation10();

    // subtract still undetected muon zufo_pt. All recognised muons (by Massimos "zufo is muon" flag) are subtracted already from single muon isolation.
    if( muon1->DeltaR(*muon2) < 1.0 ) { 
      // less than 999 does not seem to happen, but occasional its > 1e9 - what does this imply - a bug? 041011
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) { // subtract muzufopt1 from muis2 if muon1 is not flagged (i.e tufo[zufoid][0] <= 999 ) and inside DR cone of 1. 041011
	//	cout<<"GZufo::CalcIsolation(dimuon) - subtracting muzufopt1 from Isol2_10: before iso value: "<<Isol2_10;
	Isol2_10 -= muon1_zufopt; 
	//	cout<<" after iso value: "<<Isol2_10<<endl;
      }
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) { // subtract muzufopt2 from muis1 if muon2 is not flagged (i.e tufo[zufoid][0] <= 999 ) and inside DR cone of 1. 041011
	//	cout<<"GZufo::CalcIsolation(dimuon) - subtracting muzufopt2 from Isol1_10: before iso value: "<<Isol1_10;
	Isol1_10 -= muon2_zufopt;
	//	cout<<" after iso value: "<<Isol1_10<<endl;
      }
    }
    if( muon1->DeltaR(*muon2) < 0.9 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_09 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_09 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.8 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_08 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_08 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.7 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_07 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_07 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.6 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_06 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_06 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.5 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_05 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_05 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.4 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_04 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_04 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.3 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_03 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_03 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.2 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_02 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_02 -= muon2_zufopt; 
    }
    if( muon1->DeltaR(*muon2) < 0.1 ) { 
      if(gData->Gettufo( ((muon1->GetZufoID())-1) ,0 ) <= 999) Isol2_01 -= muon1_zufopt; 
      if(gData->Gettufo( ((muon2->GetZufoID())-1) ,0 ) <= 999) Isol1_01 -= muon2_zufopt; 
    }

      fmuissum[0]   = Isol1_01 + Isol2_01;
      fmuissum[1]   = Isol1_02 + Isol2_02;
      fmuissum[2]   = Isol1_03 + Isol2_03;
      fmuissum[3]   = Isol1_04 + Isol2_04;
      fmuissum[4]   = Isol1_05 + Isol2_05;
      fmuissum[5]   = Isol1_06 + Isol2_06;
      fmuissum[6]   = Isol1_07 + Isol2_07;
      fmuissum[7]   = Isol1_08 + Isol2_08;
      fmuissum[8]   = Isol1_09 + Isol2_09;
      fmuissum[9]   = Isol1_10 + Isol2_10;
      //    if ( muon1->DeltaR(*muon2) >= 1.0 )  { 
      //     }
      //     else {
      //    cout<<"GZufo::CalcIsolation(dimuon) would subtract second muon: muon1_zufopt: "<<muon1_zufopt<<"muon2_zufopt: "<<muon2_zufopt<<endl;
      //       fmuissum[0]   = muon1->GetIsolation01() - muon2_zufopt + muon2->GetIsolation01() - muon1_zufopt;
      //       fmuissum[1]   = muon1->GetIsolation02() - muon2_zufopt + muon2->GetIsolation02() - muon1_zufopt;
      //       fmuissum[2]   = muon1->GetIsolation03() - muon2_zufopt + muon2->GetIsolation03() - muon1_zufopt;
      //       fmuissum[3]   = muon1->GetIsolation04() - muon2_zufopt + muon2->GetIsolation04() - muon1_zufopt;
      //       fmuissum[4]   = muon1->GetIsolation05() - muon2_zufopt + muon2->GetIsolation05() - muon1_zufopt;
      //       fmuissum[5]   = muon1->GetIsolation06() - muon2_zufopt + muon2->GetIsolation06() - muon1_zufopt;
      //       fmuissum[6]   = muon1->GetIsolation07() - muon2_zufopt + muon2->GetIsolation07() - muon1_zufopt;
      //       fmuissum[7]   = muon1->GetIsolation08() - muon2_zufopt + muon2->GetIsolation08() - muon1_zufopt;
      //       fmuissum[8]   = muon1->GetIsolation09() - muon2_zufopt + muon2->GetIsolation09() - muon1_zufopt;
      //       fmuissum[9]   = muon1->GetIsolation10() - muon2_zufopt + muon2->GetIsolation10() - muon1_zufopt;
      //     }

      fmuissqsum[0] = TMath::Sqrt( (Isol1_01 * Isol1_01)  +  (Isol2_01 * Isol2_01));
      fmuissqsum[1] = TMath::Sqrt( (Isol1_02 * Isol1_02)  +  (Isol2_02 * Isol2_02));
      fmuissqsum[2] = TMath::Sqrt( (Isol1_03 * Isol1_03)  +  (Isol2_03 * Isol2_03));
      fmuissqsum[3] = TMath::Sqrt( (Isol1_04 * Isol1_04)  +  (Isol2_04 * Isol2_04));
      fmuissqsum[4] = TMath::Sqrt( (Isol1_05 * Isol1_05)  +  (Isol2_05 * Isol2_05));
      fmuissqsum[5] = TMath::Sqrt( (Isol1_06 * Isol1_06)  +  (Isol2_06 * Isol2_06));
      fmuissqsum[6] = TMath::Sqrt( (Isol1_07 * Isol1_07)  +  (Isol2_07 * Isol2_07));
      fmuissqsum[7] = TMath::Sqrt( (Isol1_08 * Isol1_08)  +  (Isol2_08 * Isol2_08));
      fmuissqsum[8] = TMath::Sqrt( (Isol1_09 * Isol1_09)  +  (Isol2_09 * Isol2_09));
      fmuissqsum[9] = TMath::Sqrt( (Isol1_10 * Isol1_10)  +  (Isol2_10 * Isol2_10));
      //     if( muon1->DeltaR(*muon2) >= 1.0 ) {
      //     }
      //     else {
      //      cout<<"GZufo::CalcIsolation(dimuon) subtracting second muon: "<<muon2->GetIsolation01()<<" muon2_zufopt: "<<muon2_zufopt<<" Eta: "<<muon2->Eta()<<" Phi: "<<muon2->Phi()<<endl;
      //       fmuissqsum[0] = TMath::Sqrt( ((muon1->GetIsolation01()-muon2_zufopt) * (muon1->GetIsolation01()-muon2_zufopt))  +  ((muon2->GetIsolation01()-muon1_zufopt) * (muon2->GetIsolation01()-muon1_zufopt)));
      //       fmuissqsum[1] = TMath::Sqrt( ((muon1->GetIsolation02()-muon2_zufopt) * (muon1->GetIsolation02()-muon2_zufopt))  +  ((muon2->GetIsolation02()-muon1_zufopt) * (muon2->GetIsolation02()-muon1_zufopt)));
      //       fmuissqsum[2] = TMath::Sqrt( ((muon1->GetIsolation03()-muon2_zufopt) * (muon1->GetIsolation03()-muon2_zufopt))  +  ((muon2->GetIsolation03()-muon1_zufopt) * (muon2->GetIsolation03()-muon1_zufopt)));
      //       fmuissqsum[3] = TMath::Sqrt( ((muon1->GetIsolation04()-muon2_zufopt) * (muon1->GetIsolation04()-muon2_zufopt))  +  ((muon2->GetIsolation04()-muon1_zufopt) * (muon2->GetIsolation04()-muon1_zufopt)));
      //       fmuissqsum[4] = TMath::Sqrt( ((muon1->GetIsolation05()-muon2_zufopt) * (muon1->GetIsolation05()-muon2_zufopt))  +  ((muon2->GetIsolation05()-muon1_zufopt) * (muon2->GetIsolation05()-muon1_zufopt)));
      //       fmuissqsum[5] = TMath::Sqrt( ((muon1->GetIsolation06()-muon2_zufopt) * (muon1->GetIsolation06()-muon2_zufopt))  +  ((muon2->GetIsolation06()-muon1_zufopt) * (muon2->GetIsolation06()-muon1_zufopt)));
      //       fmuissqsum[6] = TMath::Sqrt( ((muon1->GetIsolation07()-muon2_zufopt) * (muon1->GetIsolation07()-muon2_zufopt))  +  ((muon2->GetIsolation07()-muon1_zufopt) * (muon2->GetIsolation07()-muon1_zufopt)));
      //       fmuissqsum[7] = TMath::Sqrt( ((muon1->GetIsolation08()-muon2_zufopt) * (muon1->GetIsolation08()-muon2_zufopt))  +  ((muon2->GetIsolation08()-muon1_zufopt) * (muon2->GetIsolation08()-muon1_zufopt)));
      //       fmuissqsum[8] = TMath::Sqrt( ((muon1->GetIsolation09()-muon2_zufopt) * (muon1->GetIsolation09()-muon2_zufopt))  +  ((muon2->GetIsolation09()-muon1_zufopt) * (muon2->GetIsolation09()-muon1_zufopt)));
      //       fmuissqsum[9] = TMath::Sqrt( ((muon1->GetIsolation10()-muon2_zufopt) * (muon1->GetIsolation10()-muon2_zufopt))  +  ((muon2->GetIsolation10()-muon1_zufopt) * (muon2->GetIsolation10()-muon1_zufopt)));
      //     }

    dimuon->SetIsolationSum01( fmuissum[0] );
    dimuon->SetIsolationSum02( fmuissum[1] );
    dimuon->SetIsolationSum03( fmuissum[2] );
    dimuon->SetIsolationSum04( fmuissum[3] );
    dimuon->SetIsolationSum05( fmuissum[4] );
    dimuon->SetIsolationSum06( fmuissum[5] );
    dimuon->SetIsolationSum07( fmuissum[6] );
    dimuon->SetIsolationSum08( fmuissum[7] );
    dimuon->SetIsolationSum09( fmuissum[8] );
    dimuon->SetIsolationSum10( fmuissum[9] );
    
    dimuon->SetIsolationSqSum01( fmuissqsum[0] );
    dimuon->SetIsolationSqSum02( fmuissqsum[1] );
    dimuon->SetIsolationSqSum03( fmuissqsum[2] );
    dimuon->SetIsolationSqSum04( fmuissqsum[3] );
    dimuon->SetIsolationSqSum05( fmuissqsum[4] );
    dimuon->SetIsolationSqSum06( fmuissqsum[5] );
    dimuon->SetIsolationSqSum07( fmuissqsum[6] );
    dimuon->SetIsolationSqSum08( fmuissqsum[7] );
    dimuon->SetIsolationSqSum09( fmuissqsum[8] );
    dimuon->SetIsolationSqSum10( fmuissqsum[9] );
   
    return kTRUE;
  }

//_____________________________________________________________

Bool_t GZufo::CalcIsolation(GMuon *muon) {
  //
  // calculate single muon isolation
  if ( gDebug ) cout << endl << "GZufo::CalcIsolation(muon) called" << endl << endl;
  // ******************** Mu Isolation ***********************************************************
  // Calc the isolation by summing up the zufo pt in cones of delta r around the muon. 
  // Reminder: don't forget to exclude the muon.
  // translated from Achim Geiser's dimassis.f

  // Would like to have this guy in the header - but I don't manage to
  // get him initialised there (I get on compile "init. not allowed"; 
  // when I leave the init away: "incomplete type"
  TLorentzVector       fzufo_p(1.,1.,1.,1.);                    // zufo TLorentz Vec - now only filled in calcisolation - should be general feature!

  for(Int_t reset=0; reset<fnbins_iso; ++reset) {
    fmuis[reset]  = 0.;
  }

  // loop over all zufos
  for (Int_t i = 0; i < gData->Getnzufos(); i++ ) {
    fzufo_p.SetPxPyPzE(gData->Getzufo(i,0),gData->Getzufo(i,1), gData->Getzufo(i,2),  gData->Getzufo(i,3));
    fdelta_R_muzu = muon->DeltaR( fzufo_p ); // compiles but crashes then... grr
    if ( ( ( fdelta_R_muzu < .02 ) && gData->Gettufo(i,0) == 1 ) || gData->Gettufo(i,0) > 999 ) { // gData->Gettufo(i,0) == 1: means zufo contains 1 track, 1 island. usees CTD, >999 flagged as muon by Massimo's zufo flagging
      // C         probably muon zufo, do not count, but set flag
      if (fdelta_R_muzu < .02) fzufo_perhaps_muon = true;
    }
    else {
      // C  now add up the zufo pt's in cones of 0.3
      if (fdelta_R_muzu < .1) fmuis[0] = fmuis[0] + fzufo_p.Perp();
      if (fdelta_R_muzu < .2) fmuis[1] = fmuis[1] + fzufo_p.Perp();
      if (fdelta_R_muzu < .3) { // 0.3 seems not reasonable - check it!! 041011
	if (fdelta_R_muzu < fdelta_R_muzumin) { //check if muzumin is reset for every muon! 041011
	  fdelta_R_muzumin = fdelta_R_muzu;
	  fzufo_ptmin = fzufo_p.Perp();
	  ftufocode = gData->Gettufo(i,0);
	}
	fmuis[2] = fmuis[2] + fzufo_p.Perp();
      }
      if (fdelta_R_muzu < 0.4) fmuis[3] = fmuis[3] + fzufo_p.Perp();
      if (fdelta_R_muzu < 0.5) fmuis[4] = fmuis[4] + fzufo_p.Perp();
      if (fdelta_R_muzu < 0.6) fmuis[5] = fmuis[5] + fzufo_p.Perp();
      if (fdelta_R_muzu < 0.7) fmuis[6] = fmuis[6] + fzufo_p.Perp();
      if (fdelta_R_muzu < 0.8) fmuis[7] = fmuis[7] + fzufo_p.Perp();
      if (fdelta_R_muzu < 0.9) fmuis[8] = fmuis[8] + fzufo_p.Perp();
      if (fdelta_R_muzu < 1.0) fmuis[9] = fmuis[9] + fzufo_p.Perp();
    }
  }
  //     correct for undetected muon mip, cut of 0.4 needs to be tuned for bbbar events 041011
  if (!fzufo_perhaps_muon && fdelta_R_muzumin < 0.4 && fzufo_ptmin<3.) {
      if (fdelta_R_muzu < 0.4) fmuis[3] = fmuis[3] - fzufo_ptmin;
      if (fdelta_R_muzu < 0.5) fmuis[4] = fmuis[4] - fzufo_ptmin;
      if (fdelta_R_muzu < 0.6) fmuis[5] = fmuis[5] - fzufo_ptmin;
      if (fdelta_R_muzu < 0.7) fmuis[6] = fmuis[6] - fzufo_ptmin;
      if (fdelta_R_muzu < 0.8) fmuis[7] = fmuis[7] - fzufo_ptmin;
      if (fdelta_R_muzu < 0.9) fmuis[8] = fmuis[8] - fzufo_ptmin;
      if (fdelta_R_muzu < 1.0) fmuis[9] = fmuis[9] - fzufo_ptmin;
  }
  
//    cout<<endl;
//    cout<<"*****************************************************************************************************************"<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.1: "<<fmuis[0]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.2: "<<fmuis[1]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.3: "<<fmuis[2]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.4: "<<fmuis[3]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.5: "<<fmuis[4]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.6: "<<fmuis[5]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.7: "<<fmuis[6]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.8: "<<fmuis[7]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 0.9: "<<fmuis[8]<<endl;
//    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Muon isolation 1.0: "<<fmuis[9]<<endl;
//    cout<<"*****************************************************************************************************************"<<endl;
// still open here?: undetected tracks, not removed muons from zufos
// ******************** Mu Isolation *********************************************************** - end <<<

   muon->SetIsolation01( fmuis[0] );
   muon->SetIsolation02( fmuis[1] );
   muon->SetIsolation03( fmuis[2] );
   muon->SetIsolation04( fmuis[3] );
   muon->SetIsolation05( fmuis[4] );
   muon->SetIsolation06( fmuis[5] );
   muon->SetIsolation07( fmuis[6] );
   muon->SetIsolation08( fmuis[7] );
   muon->SetIsolation09( fmuis[8] );
   muon->SetIsolation10( fmuis[9] );
  
  return kTRUE;
}
//____________________________________________________________

Bool_t GZufo::CalcInstantonVariables(GDIMuon* dimuon) {
  //
  // Calculate Instanton variables like sphericity, isotropy, quark-virtuality using zufos
  if ( gDebug ) cout << endl << "GZufo::CalcInstantonVariables() called" << endl << endl;
    // *** initialize Instanton Variables value:

  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();

  fsphericity   = -999;
  fisotropy     = -999;
  fmultiplicity = 0;

// First get the jet with the highest transverse Energy

  Double_t Etmax    = 0.;
  Double_t EinB     = 0.;
  Double_t EoutB    = 0.;
  Double_t Ejet     = 0.;
  Double_t Pjet     = 0.;
  Double_t Ptjet    = 0.;
  Double_t Pxjet    = 0.;
  Double_t Pyjet    = 0.;
  Double_t Pzjet    = 0.;
  Double_t Mass2Jet = 0.;
  Double_t Etajet   = 0.;
  Double_t Phijet   = 0.;
  Double_t Thetajet = 0.;

  if( gData->Getsincand() == 0 ) {

    for ( Int_t b = 0; b < gData->Getkt_njet_a(); b++ ){

      Double_t Etjet    = gData->Getkt_etjet_a(b);
      Etajet   = gData->Getkt_etajet_a(b);
      Thetajet = 2*TMath::ATan(TMath::Exp(-Etajet));
      Phijet   = gData->Getkt_phijet_a(b);
      Mass2Jet = TMath::Power(gData->Getkt_masjet_a(b),2);

      if ( Etjet > Etmax ){
	Etmax = Etjet;
      }        

      Ejet  = Etmax/TMath::Sin(Thetajet);
      Pjet  = TMath::Sqrt(TMath::Power(Ejet,2)-Mass2Jet);
      Ptjet = Pjet*Etmax/Ejet;

      Pxjet=Pjet*TMath::Sin(Thetajet)*TMath::Cos(Phijet);
      Pyjet=Pjet*TMath::Sin(Thetajet)*TMath::Sin(Phijet);
      Pzjet=Pjet*TMath::Cos(Thetajet);
      
    }
  }

  else if ( gData->Getsincand() > 0) {

    for ( Int_t b = 0; b < gData->Getkt_njet_b(); b++ ){
	
      Double_t Etjet    = gData->Getkt_etjet_b(b);
      Etajet   = gData->Getkt_etajet_b(b);
      Thetajet = 2*TMath::ATan(TMath::Exp(-Etajet));
      Phijet   = gData->Getkt_phijet_b(b);
      Mass2Jet = TMath::Power(gData->Getkt_masjet_b(b),2);

      if ( Etjet > Etmax ){
	Etmax = Etjet;
      }        

      Ejet  = Etmax/TMath::Sin(Thetajet);
      Pjet  = TMath::Sqrt(TMath::Power(Ejet,2)-Mass2Jet);
      Ptjet = Pjet*Etmax/Ejet;

      Pxjet=Pjet*TMath::Sin(Thetajet)*TMath::Cos(Phijet);
      Pyjet=Pjet*TMath::Sin(Thetajet)*TMath::Sin(Phijet);
      Pzjet=Pjet*TMath::Cos(Thetajet);
    }   

  }

// Calculate the Quark - Virtuality

  fQ2Prime = fEmpz_had*(Ejet+Pzjet)-Mass2Jet;     

// 4 Momentum of the Photon in Photoproduction q=(E_Photon, 0, 0, -E_Photon), E_Photon= YJB * E_Elektron and DIS

  Double_t E_Electron  =  27.5;
  Double_t Pz_Electron = -27.5;

  Double_t PhotonE  = 0.;
  Double_t PhotonPx = 0.;
  Double_t PhotonPy = 0.;
  Double_t PhotonPz = 0.;

  Double_t DIS_Electron_Px = 0.;
  Double_t DIS_Electron_Py = 0.;
  Double_t DIS_Electron_Pz = 0.;
  Double_t DIS_Electron_E  = 0.;

  if( gData->Getsincand() == 0 ){

    PhotonE  =  fYJB_had*27.5;
    PhotonPz = -fYJB_had*27.5;
    PhotonPx =  0.;
    PhotonPy =  0.;
  }  

   if ( gData->Getsincand() > 0 ) {
  
     if( gData->Getsiecorr(0,2) > 0 ) {

       DIS_Electron_Px = gData->Getsiecorr(0,2)*TMath::Sin(gData->Getsith(0))*TMath::Cos(gData->Getsiph(0));
       DIS_Electron_Py = gData->Getsiecorr(0,2)*TMath::Sin(gData->Getsith(0))*TMath::Sin(gData->Getsiph(0));
       DIS_Electron_Pz = gData->Getsiecorr(0,2)*TMath::Cos(gData->Getsith(0));
       DIS_Electron_E  = gData->Getsiecorr(0,2);
     }
     else if ( gData->Getsiecorr(0,2) == 0 ) {

       DIS_Electron_Px = gData->Getsiecorr(0,0)*TMath::Sin(gData->Getsith(0))*TMath::Cos(gData->Getsiph(0));
       DIS_Electron_Py = gData->Getsiecorr(0,0)*TMath::Sin(gData->Getsith(0))*TMath::Sin(gData->Getsiph(0));
       DIS_Electron_Pz = gData->Getsiecorr(0,0)*TMath::Cos(gData->Getsith(0));
       DIS_Electron_E  = gData->Getsiecorr(0,0);
     }

     PhotonE  =  E_Electron  - DIS_Electron_E;
     PhotonPx = -DIS_Electron_Px;
     PhotonPy = -DIS_Electron_Py;
     PhotonPz =  Pz_Electron - DIS_Electron_Pz;
   }
 
  // Boost with mean value of xi=0.03719 of the gluon momentum fraction => g=(34.2148,0,0,34.2148)

   Double_t InstantonVelocityPx    = (           PhotonPx - Pxjet ) / ( 34.2148 + PhotonE - Ejet );
   Double_t InstantonVelocityPy    = (           PhotonPy - Pyjet ) / ( 34.2148 + PhotonE - Ejet );
   Double_t InstantonVelocityPz    = ( 34.2148 + PhotonPz - Pzjet ) / ( 34.2148 + PhotonE - Ejet );
   Double_t InstantonVelocity      = TMath::Sqrt(TMath::Power(InstantonVelocityPx,2) + TMath::Power(InstantonVelocityPy,2) + TMath::Power(InstantonVelocityPz,2));
   Double_t InstantonGamma   = 0.;


   if( InstantonVelocity < 1 ){
     InstantonGamma = 1/TMath::Sqrt(1-TMath::Power(InstantonVelocity,2));
   }

  // Loop over all Zufos...

   Double_t Sum_Zufo_Et     = 0.;
   Double_t Sum_Zufo_Eta_Et = 0.;
   Double_t Eta_Mean_Band   = 0.;
   Double_t fZufoEta_Sum    = 0.;
   Double_t fZufoPt_Sum     = 0.;

   Double_t Sphericity_Denominator = 0.;
   Double_t Sphericity_Numerator12 = 0.;
   Double_t Sphericity_Numerator13 = 0.;
   Double_t Sphericity_Numerator23 = 0.;

   Double_t ZufoPx_Star = 0.;
   Double_t ZufoPy_Star = 0.;
   Double_t ZufoPz_Star = 0.;

   Double_t EinBpx  = 0.;
   Double_t EinBpy  = 0.;
   Double_t EinBpz  = 0.;
   Double_t EoutBpx = 0.;
   Double_t EoutBpy = 0.;
   Double_t EoutBpz = 0.;

   Double_t Particle = 0;
     
   for ( Int_t i = 0; i < gData->Getnzufos(); i++ ) {
      
     Double_t Zufo_Px     =  gData->Getzufo(i,0);
     Double_t Zufo_Py     =  gData->Getzufo(i,1);
     Double_t Zufo_Pz     =  gData->Getzufo(i,2);
     Double_t Zufo_E      =  gData->Getzufo(i,3);
     Double_t Zufo_Pt     =  TMath::Sqrt(TMath::Power(gData->Getzufo(i,0),2)+TMath::Power(gData->Getzufo(i,1),2));
     Double_t Zufo_P      =  TMath::Sqrt(TMath::Power(gData->Getzufo(i,0),2)+TMath::Power(gData->Getzufo(i,1),2)+TMath::Power(gData->Getzufo(i,2),2));
     Double_t Zufo_Et     =  Zufo_E*Zufo_Pt/Zufo_P;
     Double_t Zufo_Phi    =  TMath::ATan2(Zufo_Py,Zufo_Px);
     Double_t Zufo_Theta  =  TMath::ATan2(Zufo_Pt,Zufo_Pz);
     Double_t Zufo_Eta    = -TMath::Log(TMath::Tan(Zufo_Theta/2));
     Double_t Zufo_DeltaR =  TMath::Sqrt(TMath::Power((Etajet-Zufo_Eta),2)+TMath::Power(Phijet-Zufo_Phi,2));
       
// ...calculate the Sphericity

     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
        if( i!=  ((muon1->GetZufoID())-1) && i!= ((muon2->GetZufoID())-1)){
	 if(fabs(Zufo_Eta) < 2.5 && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
	   Sphericity_Denominator += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
	   Sphericity_Numerator12 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2);
	   Sphericity_Numerator13 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Pz,2);
	   Sphericity_Numerator23 += TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
	 }
       }
     }
     //     else if( Zufo_Eta < fRapid_Y && Zufo_DeltaR > 1.0 && (gData->Gettufo(i,0)/1000 < 3 || gData->Gettufo(i,0)/1000 > 4)){
     else if( Zufo_Eta < fRapid_Y && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
       Sphericity_Denominator += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
       Sphericity_Numerator12 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2);
       Sphericity_Numerator13 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Pz,2);
       Sphericity_Numerator23 += TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
     }
    
// Construct the Instanton - Band
     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
       if( i!=  ((muon1->GetZufoID())-1) && i!= ((muon2->GetZufoID())-1)){
	 if(fabs(Zufo_Eta) < 2.5 && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
	   Sum_Zufo_Et     += Zufo_Et; 
	   Sum_Zufo_Eta_Et += Zufo_Eta*Zufo_Et;    
	 }
       }
     }
     //     else if(Zufo_Eta < fRapid_Y && Zufo_DeltaR > 1.0 && (gData->Gettufo(i,0)/1000 < 3 || gData->Gettufo(i,0)/1000 > 4)){
     else if(fabs(Zufo_Eta) < 2.5 && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
       Sum_Zufo_Et     += Zufo_Et; 
       Sum_Zufo_Eta_Et += Zufo_Eta*Zufo_Et;                     
     }
   }

   if( Sphericity_Numerator12 < Sphericity_Numerator13 && Sphericity_Numerator12 < Sphericity_Numerator23 ){
     fsphericity = 1.5 * Sphericity_Numerator12 / Sphericity_Denominator;
   }              
   else if( Sphericity_Numerator13 < Sphericity_Numerator12 && Sphericity_Numerator13 < Sphericity_Numerator23){
     fsphericity = 1.5 * Sphericity_Numerator13 / Sphericity_Denominator;
   }
   else if( Sphericity_Numerator23 < Sphericity_Numerator12 && Sphericity_Numerator23 < Sphericity_Numerator13 ){
     fsphericity = 1.5 * Sphericity_Numerator23 / Sphericity_Denominator;
   }
   if(Sum_Zufo_Et!=0){
     Eta_Mean_Band = Sum_Zufo_Eta_Et/Sum_Zufo_Et;
   }

   for( Int_t z = 0; z < gData->Getnzufos(); z++){
      
     Double_t Zufo_Px     =  gData->Getzufo(z,0);
     Double_t Zufo_Py     =  gData->Getzufo(z,1);
     Double_t Zufo_Pz     =  gData->Getzufo(z,2);
     Double_t Zufo_E      =  gData->Getzufo(z,3);
     Double_t Zufo_Pt     =  TMath::Sqrt(TMath::Power(gData->Getzufo(z,0),2)+TMath::Power(gData->Getzufo(z,1),2));
     Double_t Zufo_P      =  TMath::Sqrt(TMath::Power(gData->Getzufo(z,0),2)+TMath::Power(gData->Getzufo(z,1),2)+TMath::Power(gData->Getzufo(z,2),2));
     Double_t Zufo_Et     =  Zufo_E*Zufo_Pt/Zufo_P;
     Double_t Zufo_Theta  =  TMath::ATan2(Zufo_Pt,Zufo_Pz);
     Double_t Zufo_Phi    =  TMath::ATan2(Zufo_Py,Zufo_Px);
     Double_t Zufo_Eta    = -TMath::Log(TMath::Tan(Zufo_Theta/2));
     Double_t Zufo_DeltaR =  TMath::Sqrt(TMath::Power((Etajet-Zufo_Eta),2)+TMath::Power(Phijet-Zufo_Phi,2)); 


     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
       if( z!=  ((muon1->GetZufoID())-1) && z!= ((muon2->GetZufoID())-1)){
	 if( fabs(Zufo_Eta) < 2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P < 3.5){
	   if( Zufo_Et > 0 ){
	     if( gData->Getzufo_bsp(z)==0 || gData->Getzufo_bsp(z)==1 ){
	       Particle       = 1;
	       fmultiplicity += Particle;
	       fZufoEta_Sum  += Zufo_Eta;
	       fZufoPt_Sum   += Zufo_Pt;
	     }
	   }
	 }
       }
     }

     //     else if( Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 &&(gData->Gettufo(z,0)/1000 < 3 || gData->Gettufo(z,0)/1000 > 4)){
     else if( fabs(Zufo_Eta) < 2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P < 3.5){
       if( Zufo_Et > 0 ){
	 if( gData->Getzufo_bsp(z)==0 || gData->Getzufo_bsp(z)==1 ){
	   Particle       = 1;
	   fmultiplicity += Particle;
	   fZufoEta_Sum  += Zufo_Eta;
	   fZufoPt_Sum   += Zufo_Pt;
	 }
       }
     }

// Calculate the Isotropy of the Instanton - Band

     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
       if( z!=  ((muon1->GetZufoID())-1) && z!= ((muon2->GetZufoID())-1)){
	 if( fabs(Zufo_Eta)<2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P <3.5){
	   ZufoPx_Star = Zufo_Px + InstantonVelocityPx * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
	   ZufoPy_Star = Zufo_Py + InstantonVelocityPy * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
	   ZufoPz_Star = Zufo_Pz + InstantonVelocityPz * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);

	   EinBpx  += fabs(ZufoPx_Star);
	   EinBpy  += fabs(ZufoPy_Star);
	   EinBpz  += fabs(ZufoPz_Star);
	   EoutBpx += fabs(ZufoPx_Star);
	   EoutBpy += fabs(ZufoPy_Star);
	   EoutBpz += fabs(ZufoPz_Star);
	   
	 }
       }
     }

     //     else if(Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && (gData->Gettufo(z,0)/1000 < 3 || gData->Gettufo(z,0)/1000 > 4) ){  
     else if( fabs(Zufo_Eta)<2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P <3.5){
       ZufoPx_Star = Zufo_Px + InstantonVelocityPx * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
       ZufoPy_Star = Zufo_Py + InstantonVelocityPy * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
       ZufoPz_Star = Zufo_Pz + InstantonVelocityPz * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);

       EinBpx  += fabs(ZufoPx_Star);
       EinBpy  += fabs(ZufoPy_Star);
       EinBpz  += fabs(ZufoPz_Star);
       EoutBpx += fabs(ZufoPx_Star);
       EoutBpy += fabs(ZufoPy_Star);
       EoutBpz += fabs(ZufoPz_Star);
     }
   }

   if( EinBpx > EinBpy && EinBpx > EinBpz ){
     EinB = EinBpx;
   }
   else if( EinBpy > EinBpx && EinBpy > EinBpz ){
     EinB = EinBpy;
   }
   else if( EinBpz > EinBpy && EinBpz > EinBpx ){
     EinB = EinBpz;
   }

   if( EoutBpx < EoutBpy && EoutBpx<EoutBpz ){
     EoutB = EoutBpx;
   }
   else if( EoutBpy < EoutBpx && EoutBpy < EoutBpz ){
     EoutB = EoutBpy;
   }
   else if( EoutBpz < EoutBpx && EoutBpz < EoutBpy ){
     EoutB = EoutBpz;
   }   

   Double_t Isotropy_Numerator   = EinB - EoutB;
   Double_t Isotropy_Denominator = EinB;

   if( Isotropy_Denominator != 0 ){
     fisotropy = Isotropy_Numerator / Isotropy_Denominator;
   }

// Calculate the mean Eta and Pt value of Zufos in Instanton

   if( fmultiplicity > 0 ){
     fZufoEta = fZufoEta_Sum / fmultiplicity;
     fZufoPt  = fZufoPt_Sum  / fmultiplicity;
   }

   if( fQ2Prime >= gCards->GetZUFOQ2PrimeLowCut() ){
     fQ2PrimeLowCut = kTRUE;
   }

   return kTRUE;
}  

//_____________________________________________________________

Bool_t GZufo::CalcThrust() {
  //
  // calculate thrust for event iteratively (stupid mode - just loop in phi and theta)
  if ( gDebug ) cout << endl << "GZufo::CalcThrust() called" << endl << endl;
    // ********** Calculate the thrust for the given event ****************************************** - begin >>>
    // *** initialize thrust value:
    fthrust = -999;

    fthrust_axis1.SetXYZ( 1., 1., 1.);
    fthrust_axis2.SetXYZ( 1., 1., 1.);
    fthrust_axis_phi   = fthrust_axis1.Phi();
    fthrust_axis_theta1 = fthrust_axis1.Theta();
    fthrust_axis_theta2 = fthrust_axis2.Theta();
    
    // *** find axis and calculate thrust:
    ffind_thrust_axis( &fthrust_axis_phi, &fthrust_axis_theta1, &fthrust_axis_theta2,  &fthrust);
    
    // *** give found thrust theta and phi to thrust axis:
    fthrust_axis1.SetXYZ(TMath::Sin(fthrust_axis_theta1)*TMath::Cos(fthrust_axis_phi) , TMath::Sin(fthrust_axis_phi)*TMath::Sin(fthrust_axis_theta1) ,  TMath::Cos(fthrust_axis_theta1) );
    fthrust_axis2.SetXYZ(TMath::Sin(fthrust_axis_theta2)*TMath::Cos(fthrust_axis_phi) , TMath::Sin(fthrust_axis_phi)*TMath::Sin(fthrust_axis_theta2) ,  TMath::Cos(fthrust_axis_theta2) );
    //	      thrust_axis.SetMag(1.);
    //	      thrust_axis.SetPhi(   thrust_axis_phi   );
    //	      thrust_axis.SetTheta( thrust_axis_theta );
    // ********** Calculate the thrust for the given event ****************************************** - <<< end

    // Calc pt_rel in gutcode: fPtRel = fMuon->Pt(fJet->Vect())
    // *** Calc pt_rel to thrust axis:
//     thrust_mu1_ptrel = muon1.Perp(thrust_axis);
//     thrust_mu2_ptrel = muon2.Perp(thrust_axis);
//      cout<<"In GZufo: ffind_thrust_axis found - phi: "<<fthrust_axis_phi*180./TMath::Pi()<<" theta1: "<<fthrust_axis_theta1*180./TMath::Pi()<<" fthrust: " <<fthrust<<endl;
//      cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GZufo: GetThrust() returns: "<<GetThrust()<<" phi: "<<Getthrust_axis_phi()<<" theta1: "<<Getthrust_axis_theta1()<<" Vector Phi: "<<(180/TMath::Pi())*Getthrust_axis1().Phi()<<endl;
//      cout<<"In GZufo: ffind_thrust_axis found - phi: "<<fthrust_axis_phi*180./TMath::Pi()<<" theta2: "<<fthrust_axis_theta2*180./TMath::Pi()<<" fthrust: " <<fthrust<<endl;
//      cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GZufo: GetThrust() returns: "<<GetThrust()<<" phi: "<<Getthrust_axis_phi()<<" theta2: "<<Getthrust_axis_theta2()<<" Vector Phi: "<<(180/TMath::Pi())*Getthrust_axis2().Phi()<<endl;
//      getchar();
  return kTRUE;
}

//__________________________________________________________________________________

Double_t GZufo::ffind_thrust_axis(Double_t * thrust_axis_phi, Double_t * thrust_axis_theta1, Double_t * thrust_axis_theta2, Double_t * fthrust) { // start ffind_thrust_axis
  if ( gDebug ) cout << endl << "GZufo::CalcThrust() called" << endl << endl;

  //  Int_t phisteps       = 20;
  Int_t phisteps           = 60; // changed from 20 to 60 040225
  //  Int_t phisteps       = 3240; // changed from 60 to 3240 to test theta/phi scan option. -> takes too long!!
  Int_t thetasteps         = 60;
  Double_t phi             = -999.;
  Double_t phi_max         = -999.;
  Double_t theta1          = TMath::Pi()/2.;
  Double_t theta_max1      = -999.;
  Double_t theta2          = TMath::Pi()/2.;
  Double_t theta_max2      = -999.;
  Double_t pi              = TMath::Pi();
  Double_t thrust_iter1    = -999.;
  Double_t thrust_iter2    = -999.;
  Double_t thrust_max1     = -999.;
  Double_t thrust_max2     = -999.;
  Double_t thrust_max_phi  = -999.;
  Double_t fliptheta       = 0;
  Double_t fliptheta_max   = 0;

  Double_t p_sum           = 0;
  TVector3 zufo_pio(1.,1.,1.);

  // 1st and only phi iteration
  // calc the thrust for phi, not changing theta:  
  for(Int_t phistep = 0; phistep < phisteps; phistep++) {

    phi = (Double_t)phistep*(1.*pi/((Double_t)phisteps-1.));

    *thrust_axis_phi   = phi;
    *thrust_axis_theta1 = theta1;

    // *** calc the thrust for given phi
    thrust_iter1 = fcalc_thrust_NN( thrust_axis_phi, thrust_axis_theta1, &fliptheta );

    //    cout<<"thrust1 new is "<<thrust_iter1<<" thrust_max1: "<<thrust_max1<<" at phi / theta1 "<<phi<<" / "<<theta1<<" in phi loop"<<endl;
    //    getchar();

    // *** compare calculated thrust with previous values, store maximal thrust - phi based here:
    if(thrust_iter1 > thrust_max1 ) {
      thrust_max1    = thrust_iter1;
      thrust_max_phi = thrust_max1;
      phi_max        = phi;           // or elegantly use: thrust_axis_local.Phi();
      theta_max1     = theta1;        // or elegantly use: thrust_axis_local.Theta();
    }
  }
//   cout<<"ffind_thrust_axis found - phi: "<<phi_max*180./TMath::Pi()<<" theta1: "<<theta_max1*180./TMath::Pi()<<" thrust phi only:" <<thrust_max1<<endl;
//   getchar();
  // re-reset variables:
  thrust_iter1    = -999.;
  thrust_max1     = -999.;

  // 1st theta iteration:
  // refine the thrust for theta1 in 1st hemiphere defined by optimal phi, keeping the found optimal phi:  
  for(Int_t thetastep = 0; thetastep < thetasteps; thetastep++) {

    theta1 = (Double_t)thetastep*(1.*pi/((Double_t)thetasteps-1.));

    if(theta1 == 0 )  theta1 += 1e-5;
    if(theta1 == pi ) theta1 -= 1e-5;

    *thrust_axis_phi    = phi_max;
    *thrust_axis_theta1 = theta1;

    // *** calc the thrust for given theta
    thrust_iter1 = fcalc_thrust_NN( thrust_axis_phi, thrust_axis_theta1, &fliptheta, 1 );
    
    //    cout<<"thrust1 new is "<<thrust_iter1<<" thrust_max1: "<<thrust_max1<<" at theta1 / phi "<<theta1<<" / "<<*thrust_axis_phi<<" in theta1 loop"<<endl;
    //    getchar();


    // *** compare calculated thrust with previous values, store maximal thrust - theta based here:
    if(thrust_iter1 > thrust_max1 ) {
      thrust_max1 = thrust_iter1;
      theta_max1  = theta1;          // or elegantly use: thrust_axis_local.Theta();
      //      cout<<"theta_max is "<<theta_max<<" in theta_max step loop"<<endl;
    }
  }

//   cout<<"ffind_thrust_axis found - theta1: "<<phi_max*180./TMath::Pi()<<" theta1: "<<theta_max1*180./TMath::Pi()<<" thrust1:" <<thrust_max1<<endl;
//   getchar();

  fliptheta = 0;

  // 2nd theta iteration:
  // refine the thrust for theta2 in 2nd hemiphere defined by optimal phi, keeping the found optimal phi:  

  for(Int_t thetastep = 0; thetastep < thetasteps; thetastep++) {

    theta2 = (Double_t)thetastep*(1.*pi/((Double_t)thetasteps-1.));

    if(theta2 == 0 )  theta2 += 1e-5;
    if(theta2 == pi ) theta2 -= 1e-5;

    *thrust_axis_phi    = phi_max;
    *thrust_axis_theta2 = theta2;

    // *** calc the thrust for given theta
    thrust_iter2 = fcalc_thrust_NN( thrust_axis_phi, thrust_axis_theta2, &fliptheta, 2 );
    
//     cout<<"thrust2 new is "<<thrust_iter2<<" thrust_max2: "<<thrust_max2<<" at theta2 / phi "<<theta2<<" / "<<*thrust_axis_phi<<" in theta2 loop"<<endl;
    //    getchar();


    // *** compare calculated thrust with previous values, store maximal thrust - theta based here:
    if(thrust_iter2 > thrust_max2 ) {
      thrust_max2   = thrust_iter2;
      theta_max2    = theta2;          // or elegantly use: thrust_axis_local.Theta();
      fliptheta_max = fliptheta;
      //      cout<<"theta_max is "<<theta_max<<" in theta_max step loop"<<endl;
    }
  }

//   cout<<"ffind_thrust_axis found - theta2: "<<phi_max*180./TMath::Pi()<<" theta2 / phi: "<<theta_max2*180./TMath::Pi()<<" / "<<*thrust_axis_phi*180./TMath::Pi()<<" thrust2:" <<thrust_max2<<" and flip? "<<fliptheta_max<<endl;
//   getchar();

  // *** calculate the normalisation (was done in fcalc_thrust previously)
  for(Int_t zufonr = 0; zufonr<gData->Getnzufos(); zufonr++) {
    //    fzufo_p.SetPxPyPzE(gData->Getzufo(zufonr,0),gData->Getzufo(zufonr,1), gData->Getzufo(zufonr,2),  gData->Getzufo(zufonr,3));
    zufo_pio.SetXYZ(gData->Getzufo(zufonr,0),gData->Getzufo(zufonr,1), gData->Getzufo(zufonr,2));
    if( zufo_pio.Theta() > 10.*(TMath::Pi()/180.) ){ // throw out all zufoses with theta<10. deg
      p_sum += TMath::Sqrt( zufo_pio.Dot( zufo_pio ) );
    }
  }
  
  // *** set output values:
  if( fliptheta_max < 0.) theta_max2 = pi - theta_max2;

  *fthrust            = (thrust_max1 + thrust_max2) / p_sum;
  *thrust_axis_phi    = phi_max;
  *thrust_axis_theta1 = theta_max1;
  *thrust_axis_theta2 = theta_max2;

  //  cout<<">*>*>**>*> OUTPUT IS: fthrust: "<<*fthrust<<" = thrust_max1: "<<thrust_max1<<" + thrust_max2: "<<thrust_max2<<" / p_sum: "<<p_sum<<endl;

//   cout<<"ffind_thrust_axis found - phi: "<<phi_max*180./TMath::Pi()<<" theta: "<<theta_max*180./TMath::Pi()<<" thrust both / phi only:" <<thrust_max<<" / "<<thrust_max_phi<<endl;
//   getchar();

  if(42)  return *fthrust; // dummy - prep for error messages
  else  return -1.;

}

//__________________________________________________________________________________

Double_t GZufo::fcalc_thrust_NN(Double_t * thrust_axis_phi, Double_t * thrust_axis_theta, Double_t * fliptheta, Int_t mode ) { // start fcalc_thrust_NN
  if ( gDebug ) cout << endl << "GZufo::fcalc_thrust_NN() called" << endl << endl;

  // This routine calculates a non normalised thrust, i.e. Sum(p_i*T_j) rather than the normalised thrust: Sum(p_i*T_j)/Sum(|p_i|). Normalisation is performed in ffind_thrust_axis().
  // mode chooses which iteration is performed: 0 = phi, 1 = theta1, 2 = theta2

  //  TLorentzVector       fzufo_pi(1.,1.,1.);                    // zufo TLorentz Vec - now only filled in calcisolation and calcthrust - should be general feature!
  TVector3 zufo_pi(1.,1.,1.);
  TVector3 ThAxLoc(1.,1.,1.);

  Double_t thrust_NN;
  Double_t p_dot_thr_sum;
  Double_t bufferphi   = 0;
  Double_t buffertheta = 0;

  Double_t p_sum_loc = 0;

  bufferphi   = *thrust_axis_phi;
  buffertheta = *thrust_axis_theta;

  //  cout<<"bufferphi / buffertheta are: "<<bufferphi<<" / "<<buffertheta<<endl;

  ThAxLoc.SetXYZ( TMath::Sin(buffertheta)*TMath::Cos(bufferphi) , TMath::Sin(bufferphi)*TMath::Sin(buffertheta) ,  TMath::Cos(buffertheta) );
  //  cout<<" Phi of axis ThAxLoc: "<<ThAxLoc.Phi()<<" Theta of axis ThAxLoc: "<<ThAxLoc.Theta()<<endl;
  //  ThAxLoc.SetTheta(buffertheta);
  //  ThAxLoc.SetMag(1.);
  thrust_NN        = -999;
  p_dot_thr_sum    = 0.;
  *fliptheta        = 0.;
  // *** calc thrust_NN from zufos here (at the moment with all zufos. Intend to prepare a list of 'chosen' zufos for 3d version):
  for(Int_t zufonr = 0; zufonr<gData->Getnzufos(); zufonr++) {
    //    fzufo_p.SetPxPyPzE(gData->Getzufo(zufonr,0),gData->Getzufo(zufonr,1), gData->Getzufo(zufonr,2),  gData->Getzufo(zufonr,3));
    zufo_pi.SetXYZ(gData->Getzufo(zufonr,0),gData->Getzufo(zufonr,1), gData->Getzufo(zufonr,2));
    //    zufo_pi.SetXYZ(zufo[zufonr][0], zufo[zufonr][1], zufo[zufonr][2]); // activcated this line 040311 to allow theta iteration.
    //    zufo_pi.SetXYZ(zufo[zufonr][0], zufo[zufonr][1], 0.0); // removed this line 040311 to allow theta iteration.
    //    cout<<"fcalc_thrust_NN - mode: "<<mode<<" dphi: "<<zufo_pi.DeltaPhi(ThAxLoc)<<" Phi of axis: "<<ThAxLoc.Phi()<<" Theta of axis: "<<ThAxLoc.Theta()<<" p_dot_thr_sum: "<<p_dot_thr_sum<<endl;

    // *** sum up all p_i * n (with theta>10. deg):
    if( mode==0 || (mode==1 && TMath::Abs(zufo_pi.DeltaPhi(ThAxLoc)) <= TMath::Pi()/2.) || (mode==2 && TMath::Abs(zufo_pi.DeltaPhi(ThAxLoc)) > TMath::Pi()/2.) ){ // throw out one hemisphere if iterating theta1 and 2
      //      cout<<"fcalc_thrust_NN - mode: "<<mode<<" dphi: "<<zufo_pi.DeltaPhi(ThAxLoc)<<" Phi of axis: "<<ThAxLoc.Phi()<<endl;
      if( zufo_pi.Theta() > 10.*(TMath::Pi()/180.) ){// throw out all zufoses with theta<10. deg

//  	if(mode == 0) p_dot_thr_sum += TMath::Abs(zufo_pi.Dot( ThAxLoc ));
//  	else p_dot_thr_sum += zufo_pi.Dot( ThAxLoc );
	p_dot_thr_sum += TMath::Abs(zufo_pi.Dot( ThAxLoc ));
	*fliptheta += zufo_pi.Dot( ThAxLoc );
	p_sum_loc += TMath::Sqrt( zufo_pi.Dot( zufo_pi ) );
// 	if( mode == 2 ) {
// 	  cout<<"Zufos used for thrust2: phi / theta / metric:         "<<(180./TMath::Pi())*zufo_pi.Phi()<<" / "<<(180./TMath::Pi())*zufo_pi.Theta()<<" / "<<zufo_pi.Mag()<<endl;
// 	  cout<<"Zufos used for thrust2: ThAxLoc phi / theta / metric: "<<(180./TMath::Pi())*ThAxLoc.Phi()<<" / "<<(180./TMath::Pi())*ThAxLoc.Theta()<<" / "<<ThAxLoc.Mag()<<"and the dot prod is: "<<zufo_pi.Dot( ThAxLoc )<<endl;
// 	  cout<<"%%%%%%%%%%%%% reliable basis to flip theta?: if neg flip: "<<*fliptheta<<endl;
// 	}
      }
    }
  }
//   cout<<endl<<"******************* after zufo loop: "<<" p_dot_thr_sum: "<<p_dot_thr_sum<<" local thrust: "<<p_dot_thr_sum/p_sum_loc<<endl;
  thrust_NN = p_dot_thr_sum;
  return thrust_NN;
}

//_____________________________________________________________

//Bool_t GZufo::CalcInstantonVariables_True(){

  //
  // Calculate Instanton variables like sphericity, isotropy, quark-virtuality using Fmckin Particles

  //  if ( gDebug ) cout << endl << "GZufo::CalcInstantonVariables_True() called" << endl << endl;

  //  initialize Instanton Variables value:
/*
  fsphericity_True = -999.99;
  fisotropy_True   = -999.99;

  Double_t Etmax_True    = 0.;
  Double_t Ptmax_True    = 0.;
  Double_t EinB_True     = 0.;
  Double_t EoutB_True    = 0.;
  Double_t Ejet_True     = 0.;
  Double_t Pjet_True     = 0.;
  Double_t Ptjet_True    = 0.;
  Double_t Pxjet_True    = 0.;
  Double_t Pyjet_True    = 0.;
  Double_t Pzjet_True    = 0.;
  Double_t Mass2Jet_True = 0.;
  Double_t Etajet_True   = 0.;
  Double_t Phijet_True   = 0.;
  Double_t Thetajet_True = 0.;

  for ( Int_t b = 0; b < gData->Getnhbmjets(); b++ ){

    Pxjet_True    = gData->Getpxhbmjet(b);
    Pyjet_True    = gData->Getpyhbmjet(b);
    Pzjet_True    = gData->Getpzhbmjet(b);
    Ejet_True     = gData->Getehbmjet(b);

    Ptjet_True    = TMath::Sqrt(TMath::Power(Pxjet_True,2) + TMath::Power(Pyjet_True,2));
    Pjet_True     = TMath::Sqrt(TMath::Power(Pxjet_True,2) + TMath::Power(Pyjet_True,2) + TMath::Power(Pzjet_True,2));
    Etjet_True    = Ejet_True*Ptjet_True/Pjet_True;

    if(Ptjet_True > Ptmax_True){
      Ptmax_True = Ptjet_True;
    }

    if(Etjet_True > Etmax_True){
      Etmax_True = Etjet_True;
    }

    Phijet_True   = TMath::ATan2(Pyjet_True,Pxjet_True);
    Thetajet_True = TMath::ATan2(Ptjet_True,Pzjet_True);
    Etajet_True   = -TMath::Log(TMath::Tan(Thetajet_True/2));
    Mass2Jet_True = TMath::Power(Ejet_True,2)- TMath::Power(Pjet_True,2);
  }


  fQ2Prime_True = fEmpz_had_True*(Ejet_True+Pzjet_True)-Mass2Jet_True;     


  Double_t E_Electron  =  27.5;
  Double_t Pz_Electron = -27.5;

  Double_t PhotonE  = 0.;
  Double_t PhotonPx = 0.;
  Double_t PhotonPy = 0.;
  Double_t PhotonPz = 0.;

  Double_t DIS_Electron_Px = 0.;
  Double_t DIS_Electron_Py = 0.;
  Double_t DIS_Electron_Pz = 0.;
  Double_t DIS_Electron_E  = 0.;

  PhotonE  =  fYJB_had*27.5;
  PhotonPz = -fYJB_had*27.5;
  PhotonPx =  0.;
  PhotonPy =  0.;
  
  DIS_Electron_Px = ;
  DIS_Electron_Py = ;
  DIS_Electron_Pz = ;
  DIS_Electron_E  = ;
  
  PhotonE  =  E_Electron  - DIS_Electron_E;
  PhotonPx = -DIS_Electron_Px;
  PhotonPy = -DIS_Electron_Py;
  PhotonPz =  Pz_Electron - DIS_Electron_Pz;
  
  Double_t InstantonVelocityPx    = (           PhotonPx - Pxjet ) / ( 34.2148 + PhotonE - Ejet );
  Double_t InstantonVelocityPy    = (           PhotonPy - Pyjet ) / ( 34.2148 + PhotonE - Ejet );
  Double_t InstantonVelocityPz    = ( 34.2148 + PhotonPz - Pzjet ) / ( 34.2148 + PhotonE - Ejet );
  Double_t InstantonVelocity      = TMath::Sqrt(TMath::Power(InstantonVelocityPx,2) + TMath::Power(InstantonVelocityPy,2) + TMath::Power(InstantonVelocityPz,2));
  Double_t InstantonGamma   = 0.;


  if( InstantonVelocity < 1 ){
    InstantonGamma = 1/TMath::Sqrt(1-TMath::Power(InstantonVelocity,2));
  }


   Double_t Sum_Zufo_Et     = 0.;
   Double_t Sum_Zufo_Eta_Et = 0.;
   Double_t Eta_Mean_Band   = 0.;
   Double_t fZufoEta_Sum    = 0.;
   Double_t fZufoPt_Sum     = 0.;

   Double_t Sphericity_Denominator = 0.;
   Double_t Sphericity_Numerator12 = 0.;
   Double_t Sphericity_Numerator13 = 0.;
   Double_t Sphericity_Numerator23 = 0.;

   Double_t ZufoPx_Star = 0.;
   Double_t ZufoPy_Star = 0.;
   Double_t ZufoPz_Star = 0.;

   Double_t EinBpx  = 0.;
   Double_t EinBpy  = 0.;
   Double_t EinBpz  = 0.;
   Double_t EoutBpx = 0.;
   Double_t EoutBpy = 0.;
   Double_t EoutBpz = 0.;

   Double_t Particle = 0;
     
   for ( Int_t i = 0; i < gData->Getnzufos(); i++ ) {
      
     Double_t Zufo_Px     =  gData->Getzufo(i,0);
     Double_t Zufo_Py     =  gData->Getzufo(i,1);
     Double_t Zufo_Pz     =  gData->Getzufo(i,2);
     Double_t Zufo_E      =  gData->Getzufo(i,3);
     Double_t Zufo_Pt     =  TMath::Sqrt(TMath::Power(gData->Getzufo(i,0),2)+TMath::Power(gData->Getzufo(i,1),2));
     Double_t Zufo_P      =  TMath::Sqrt(TMath::Power(gData->Getzufo(i,0),2)+TMath::Power(gData->Getzufo(i,1),2)+TMath::Power(gData->Getzufo(i,2),2));
     Double_t Zufo_Et     =  Zufo_E*Zufo_Pt/Zufo_P;
     Double_t Zufo_Phi    =  TMath::ATan2(Zufo_Py,Zufo_Px);
     Double_t Zufo_Theta  =  TMath::ATan2(Zufo_Pt,Zufo_Pz);
     Double_t Zufo_Eta    = -TMath::Log(TMath::Tan(Zufo_Theta/2));
     Double_t Zufo_DeltaR =  TMath::Sqrt(TMath::Power((Etajet-Zufo_Eta),2)+TMath::Power(Phijet-Zufo_Phi,2));
       
     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
        if( i!=  ((muon1->GetZufoID())-1) && i!= ((muon2->GetZufoID())-1)){
	 if(fabs(Zufo_Eta) < 2.5 && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
	   Sphericity_Denominator += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
	   Sphericity_Numerator12 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2);
	   Sphericity_Numerator13 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Pz,2);
	   Sphericity_Numerator23 += TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
	 }
       }
     }
     else if( Zufo_Eta < fRapid_Y && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
       Sphericity_Denominator += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
       Sphericity_Numerator12 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Py,2);
       Sphericity_Numerator13 += TMath::Power(Zufo_Px,2) + TMath::Power(Zufo_Pz,2);
       Sphericity_Numerator23 += TMath::Power(Zufo_Py,2) + TMath::Power(Zufo_Pz,2);
     }
    
     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
       if( i!=  ((muon1->GetZufoID())-1) && i!= ((muon2->GetZufoID())-1)){
	 if(fabs(Zufo_Eta) < 2.5 && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
	   Sum_Zufo_Et     += Zufo_Et; 
	   Sum_Zufo_Eta_Et += Zufo_Eta*Zufo_Et;    
	 }
       }
     }
     else if(fabs(Zufo_Eta) < 2.5 && Zufo_DeltaR > 1.0 && gData->Gettufo(i,0)/1000 < 1 && Zufo_P < 3.5){
       Sum_Zufo_Et     += Zufo_Et; 
       Sum_Zufo_Eta_Et += Zufo_Eta*Zufo_Et;                     
     }
   }

   if( Sphericity_Numerator12 < Sphericity_Numerator13 && Sphericity_Numerator12 < Sphericity_Numerator23 ){
     fsphericity = 1.5 * Sphericity_Numerator12 / Sphericity_Denominator;
   }              
   else if( Sphericity_Numerator13 < Sphericity_Numerator12 && Sphericity_Numerator13 < Sphericity_Numerator23){
     fsphericity = 1.5 * Sphericity_Numerator13 / Sphericity_Denominator;
   }
   else if( Sphericity_Numerator23 < Sphericity_Numerator12 && Sphericity_Numerator23 < Sphericity_Numerator13 ){
     fsphericity = 1.5 * Sphericity_Numerator23 / Sphericity_Denominator;
   }
   if(Sum_Zufo_Et!=0){
     Eta_Mean_Band = Sum_Zufo_Eta_Et/Sum_Zufo_Et;
   }

   for( Int_t z = 0; z < gData->Getnzufos(); z++){
      
     Double_t Zufo_Px     =  gData->Getzufo(z,0);
     Double_t Zufo_Py     =  gData->Getzufo(z,1);
     Double_t Zufo_Pz     =  gData->Getzufo(z,2);
     Double_t Zufo_E      =  gData->Getzufo(z,3);
     Double_t Zufo_Pt     =  TMath::Sqrt(TMath::Power(gData->Getzufo(z,0),2)+TMath::Power(gData->Getzufo(z,1),2));
     Double_t Zufo_P      =  TMath::Sqrt(TMath::Power(gData->Getzufo(z,0),2)+TMath::Power(gData->Getzufo(z,1),2)+TMath::Power(gData->Getzufo(z,2),2));
     Double_t Zufo_Et     =  Zufo_E*Zufo_Pt/Zufo_P;
     Double_t Zufo_Theta  =  TMath::ATan2(Zufo_Pt,Zufo_Pz);
     Double_t Zufo_Phi    =  TMath::ATan2(Zufo_Py,Zufo_Px);
     Double_t Zufo_Eta    = -TMath::Log(TMath::Tan(Zufo_Theta/2));
     Double_t Zufo_DeltaR =  TMath::Sqrt(TMath::Power((Etajet-Zufo_Eta),2)+TMath::Power(Phijet-Zufo_Phi,2)); 


     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
       if( z!=  ((muon1->GetZufoID())-1) && z!= ((muon2->GetZufoID())-1)){
	 if( fabs(Zufo_Eta) < 2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P < 3.5){
	   if( Zufo_Et > 0 ){
	     if( gData->Getzufo_bsp(z)==0 || gData->Getzufo_bsp(z)==1 ){
	       Particle       = 1;
	       fmultiplicity += Particle;
	       fZufoEta_Sum  += Zufo_Eta;
	       fZufoPt_Sum   += Zufo_Pt;
	     }
	   }
	 }
       }
     }

     else if( fabs(Zufo_Eta) < 2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P < 3.5){
       if( Zufo_Et > 0 ){
	 if( gData->Getzufo_bsp(z)==0 || gData->Getzufo_bsp(z)==1 ){
	   Particle       = 1;
	   fmultiplicity += Particle;
	   fZufoEta_Sum  += Zufo_Eta;
	   fZufoPt_Sum   += Zufo_Pt;
	 }
       }
     }


     if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
       if( z!=  ((muon1->GetZufoID())-1) && z!= ((muon2->GetZufoID())-1)){
	 if( fabs(Zufo_Eta)<2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P <3.5){
	   ZufoPx_Star = Zufo_Px + InstantonVelocityPx * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
	   ZufoPy_Star = Zufo_Py + InstantonVelocityPy * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
	   ZufoPz_Star = Zufo_Pz + InstantonVelocityPz * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);

	   EinBpx  += fabs(ZufoPx_Star);
	   EinBpy  += fabs(ZufoPy_Star);
	   EinBpz  += fabs(ZufoPz_Star);
	   EoutBpx += fabs(ZufoPx_Star);
	   EoutBpy += fabs(ZufoPy_Star);
	   EoutBpz += fabs(ZufoPz_Star);
	   
	 }
       }
     }

     else if( fabs(Zufo_Eta)<2.5 && Zufo_Eta < Eta_Mean_Band+1.1 && Zufo_Eta > Eta_Mean_Band-1.1 && Zufo_DeltaR > 1.0 && gData->Gettufo(z,0)/1000 < 1 && Zufo_P <3.5){
       ZufoPx_Star = Zufo_Px + InstantonVelocityPx * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
       ZufoPy_Star = Zufo_Py + InstantonVelocityPy * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);
       ZufoPz_Star = Zufo_Pz + InstantonVelocityPz * InstantonGamma * (InstantonGamma/(InstantonGamma+1)* (InstantonVelocityPx*Zufo_Px + InstantonVelocityPy*Zufo_Py + InstantonVelocityPz*Zufo_Pz)-Zufo_E);

       EinBpx  += fabs(ZufoPx_Star);
       EinBpy  += fabs(ZufoPy_Star);
       EinBpz  += fabs(ZufoPz_Star);
       EoutBpx += fabs(ZufoPx_Star);
       EoutBpy += fabs(ZufoPy_Star);
       EoutBpz += fabs(ZufoPz_Star);
     }
   }

   if( EinBpx > EinBpy && EinBpx > EinBpz ){
     EinB = EinBpx;
   }
   else if( EinBpy > EinBpx && EinBpy > EinBpz ){
     EinB = EinBpy;
   }
   else if( EinBpz > EinBpy && EinBpz > EinBpx ){
     EinB = EinBpz;
   }

   if( EoutBpx < EoutBpy && EoutBpx<EoutBpz ){
     EoutB = EoutBpx;
   }
   else if( EoutBpy < EoutBpx && EoutBpy < EoutBpz ){
     EoutB = EoutBpy;
   }
   else if( EoutBpz < EoutBpx && EoutBpz < EoutBpy ){
     EoutB = EoutBpz;
   }   

   Double_t Isotropy_Numerator   = EinB - EoutB;
   Double_t Isotropy_Denominator = EinB;

   if( Isotropy_Denominator != 0 ){
     fisotropy = Isotropy_Numerator / Isotropy_Denominator;
   }

  return kTRUE;

}
*/
//_____________________________________________________________

Bool_t GZufo::Reset() {
  //
  // reset on event by event basis
  if ( gDebug ) cout << endl << "GZufo::Reset() called" << endl << endl;

  fPt_had   = -9999.99;
  fEmpz_had = -9999.99;
  fYJB_had  = -9999.99;
  fQ2JB_had = -9999.99;
  fRapid_Y  = -9999.99;
  fQ2Prime  = -9999.99;
  fZufoEta  = -9999.99;
  fZufoPt   = -9999.99;

  fYJBCut        = kFALSE;
  fEmpzCut       = kFALSE;
  fPtHadMaxCut   = kFALSE;
  fQ2PrimeLowCut = kFALSE;
  /*
  fQ2Prime_True   = -9999.99;
  fHadronEta_True = -9999.99;
  fHadronPt_True  = -9999.99;
  */
  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::CheckYJBCut() {
  //
  // check if event fulfils y_jb cut
  if ( gDebug ) cout << endl << "GZufo::CheckYJBCut() called" << endl << endl;

  if ( ( fYJB_had >= gCards->GetZUFOYJBLOWCut() ) && ( fYJB_had <= gCards->GetZUFOYJBUPCut() ) )
    fYJBCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::CheckEmpzCut() {
  //
  // check if event fulfils Empz cut
  if ( gDebug ) cout << endl << "GZufo::CheckEmpzCut() called" << endl << endl;
  
  if ( ( fEmpz_had >= gCards->GetZUFOEMPZLOWCut() ) && ( fEmpz_had <= gCards->GetZUFOEMPZUPCut() ) )
    fEmpzCut = kTRUE;
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::CheckPtHadMaxCut() {
  //
  // check if event fulfills pt_had max cut
  if ( gDebug ) cout << endl << "GZufo::CheckPtHadMaxCut() called" << endl << endl;

  if ( fPt_had <= gCards->GetZUFOPtHadMaxCut() )
    fPtHadMaxCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZufo::GetAllCuts() {
  //
  // return flag if event passes all zufo cuts
  if ( gDebug ) cout << endl << "GZufo::GetAllCuts() called" << endl << endl;

  if (gCards->GetSinistraNoCut()==kTRUE)
    return kTRUE;
  else if ( GetYJBCut() && GetEmpzCut() && GetPtHadMaxCut() )
    return  kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

TString  GZufo::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GZufo::PrintMessage() called" << endl << endl;

  TString dummy = "Zufos:\n\n";

  for ( Int_t i = 0; i < gData->Getnzufos(); i++ ) {

    dummy.Append("Zufo: ");
  
    dummy.Append(gInclude->FormatedChar(" id: ",5));
    dummy.Append(gInclude->FormatedInt(i+1,3,0," "));
    dummy.Append(gInclude->FormatedChar(" px: ",5));
    dummy.Append(gInclude->FormatedDouble(gData->Getzufo(i,0),4,2));
    dummy.Append(gInclude->FormatedChar(" py: ",5));
    dummy.Append(gInclude->FormatedDouble(gData->Getzufo(i,1),4,2));
    dummy.Append(gInclude->FormatedChar(" pz: ",5));
    dummy.Append(gInclude->FormatedDouble(gData->Getzufo(i,2),4,2));
    dummy.Append(gInclude->FormatedChar(" E: ",4));
    dummy.Append(gInclude->FormatedDouble(gData->Getzufo(i,3),4,2));
    dummy.Append(gInclude->FormatedChar(" type: ",8));
    dummy.Append(gInclude->FormatedInt(gData->Gettufo(i,0),5,0," "));
    dummy.Append(gInclude->FormatedChar(" track: ",10));
    dummy.Append(gInclude->FormatedInt(gData->Gettufo(i,1),3,0," "));

    dummy.Append("\n");

  }
  dummy.Append("\n");
  dummy.Append("yJB_had: ");
  dummy.Append(gInclude->FormatedDouble(fYJB_had,4,2));
  dummy.Append(" yJB_cut: ");
  dummy.Append(gInclude->FormatedBool(fYJBCut));
  dummy.Append(" Empz_had: ");
  dummy.Append(gInclude->FormatedDouble(fEmpz_had,4,2));
  dummy.Append(" Empz_cut: ");
  dummy.Append(gInclude->FormatedBool(fEmpzCut));
  dummy.Append(" pt_had_max_cut: ");
  dummy.Append(gInclude->FormatedBool(fPtHadMaxCut));
  dummy.Append(" all cuts: ");
  dummy.Append(gInclude->FormatedBool(GetAllCuts()));
  dummy.Append("\n");
  

  
  return dummy;
}

//_____________________________________________________________

Bool_t GZufo::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GZufo::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("ZUFO") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}
