//
// GBac.cxx
//
// $Author: ibloch $
// $Date: 2005/04/26 10:27:22 $
// $Revision: 1.2 $
//

#include <GBac.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GBac)
#endif

GBac *gBac = 0;

//_____________________________________________________________
// GBac
// Call class for everything which is related only to BAC
//     desired cut:   &&  (bac_etot < 100 || nbacmu < 15)
//
GBac::GBac() : GPhysObj() {
  //
  // GBac default constructor
  if ( gDebug ) cout << endl << "GBac::GBac ctor called" << endl << endl;

  gBac = this;

  // initialize variables
  //  fbac_etot      = -9999.99;
  //  fnbacmu        = -9999.99;

  fbac_etotCut    = kFALSE;
  fnbacmuCut      = kFALSE;

  // general bac histos
  fGeneralbac_etot                  = 0;
  fGeneralnbacmu                    = 0;

  fGeneralbac_etot_uncut            = 0;
  fGeneralnbacmu_uncut              = 0;

  // control plots
  fControlbac_etot                  = 0;
  fControlnbacmu                    = 0;

  fControlbac_etot_uncut            = 0;
  fControlnbacmu_uncut              = 0;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GBac::~GBac() {
  //
  // GBac default destructor
  if ( gDebug ) cout << endl << "GBac::~GBac dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GBac::CreateGeneral() {
  //
  // create general histograms for BAC
  if ( gDebug ) cout << endl << "GBac::CreateGeneral() called" << endl << endl;

  // create general histograms
  if ( gCards->GetBACGeneral() ) {

    Int_t    bac_etotbins   =    200;
    Double_t bac_etotlow    =    -10.;
    Double_t bac_etothigh   =   1990.;  
    Int_t    nbacmubins     =    200;
    Double_t nbacmulow      =      0.;
    Double_t nbacmuhigh     =    200.;  

    fGeneralbac_etot = gHistogrammer->TH1DFactory("Bac","bac_etot","BAC: E_{tot}",bac_etotbins,bac_etotlow,bac_etothigh,"E_{tot} [GeV]","Events");
    fGeneralnbacmu = gHistogrammer->TH1DFactory("Bac","nbacmu","BAC: N_{#mu}",nbacmubins,nbacmulow,nbacmuhigh,"N_{#mu}","Events");

    fGeneralbac_etot_uncut = gHistogrammer->TH1DFactory("Bac","bac_etot_uncut","uncut BAC: E_{tot}",bac_etotbins,bac_etotlow,bac_etothigh,"E_{tot} [GeV]","Events");
    fGeneralnbacmu_uncut = gHistogrammer->TH1DFactory("Bac","nbacmu_uncut","uncut BAC: N_{#mu}",nbacmubins,nbacmulow,nbacmuhigh,"N_{#mu}","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::FillGeneral() {
  //
  // fill general histograms for BAC
  if ( gDebug ) cout << endl << "GBac::FillGeneral() called" << endl << endl;

  if ( gCards->GetBACGeneral() ) {

    fGeneralbac_etot_uncut->Fill(gData->Getbac_etot(),gHeader->GetWeight());
    fGeneralnbacmu_uncut->Fill(gData->Getnbacmu(),gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {
      fGeneralbac_etot->Fill(gData->Getbac_etot(),gHeader->GetWeight());
      fGeneralnbacmu->Fill(gData->Getnbacmu(),gHeader->GetWeight());

    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GBac::Do() called" << endl << endl;

  //  Calc();

  Checkbac_etotCut();
  ChecknbacmuCut();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GBac::CreateControl() called" << endl << endl;

  if ( gCards->GetBACControl() ) {

    Int_t    bac_etotbins   =    200;
    Double_t bac_etotlow    =    -10.;
    Double_t bac_etothigh   =   1990.;  
    Int_t    nbacmubins     =    200;
    Double_t nbacmulow      =      0.;
    Double_t nbacmuhigh     =    200.;  
                                      
    fControlbac_etot = gHistogrammer->TH1DFactory("Bac_Control","bac_etot","BAC: E_{tot}",bac_etotbins,bac_etotlow,bac_etothigh,"E_{tot} [GeV]","Events");
    fControlnbacmu = gHistogrammer->TH1DFactory("Bac_Control","nbacmu","BAC: N_{#mu}",nbacmubins,nbacmulow,nbacmuhigh,"N_{#mu}","Events");
                                           
    fControlbac_etot_uncut = gHistogrammer->TH1DFactory("Bac_Control","bac_etot_uncut","uncut BAC: E_{tot}",bac_etotbins,bac_etotlow,bac_etothigh,"E_{tot} [GeV]","Events");
    fControlnbacmu_uncut = gHistogrammer->TH1DFactory("Bac_Control","nbacmu_uncut","uncut BAC: N_{#mu}",nbacmubins,nbacmulow,nbacmuhigh,"N_{#mu}","Events");

  }  

  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::FillControl() {
  //
  // fill control plots
  if ( gDebug ) cout << endl << "GBac::FillControl() called" << endl << endl;

  if ( gCards->GetBACControl() ) {

    fControlbac_etot_uncut->Fill(gData->Getbac_etot());
    fControlnbacmu_uncut->Fill(gData->Getnbacmu());

    if ( Getbac_etotCut() ) {
      fControlbac_etot->Fill(gData->Getbac_etot());
    }

    if ( GetnbacmuCut() ) {
      fControlnbacmu->Fill(gData->Getnbacmu());
    }

  }

  return kTRUE;
}

// //_____________________________________________________________

// Bool_t GBac::Calc() {
//   //
//   // calculate jb properties
//   if ( gDebug ) cout << endl << "GBac::Calc() called" << endl << endl;

//   fPt   = TMath::Sqrt(TMath::Power(gData->Getbac_etot(),2)+TMath::Power(gData->Getnbacmu(),2));
//   fEmpz = gData->Getbac_e()-gData->Getbac_pz();

//   return kTRUE;
// }

//_____________________________________________________________

Bool_t GBac::Reset() {
  //
  // reset on event by event basis
  if ( gDebug ) cout << endl << "GBac::Reset() called" << endl << endl;

  //  fbac_etot    = -9999.99;
  //  fnbacmu      = -9999.99;

  fbac_etotCut  = kFALSE;
  fnbacmuCut    = kFALSE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::Checkbac_etotCut() {
  //
  // check if event fulfils bac_etot cut (ge && le)
  if ( gDebug ) cout << endl << "GBac::Checkbac_etotCut() called" << endl << endl;

  if ( ( gData->Getbac_etot() >= gCards->GetBACbac_etotLOWCut() ) && ( gData->Getbac_etot() <= gCards->GetBACbac_etotUPCut() ) )
    fbac_etotCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::ChecknbacmuCut() {
  //
  // check if event fulfils nbacmu cut (le)
  if ( gDebug ) cout << endl << "GBac::ChecknbacmuCut() called" << endl << endl;

  if ( ( gData->Getnbacmu() ) <= gCards->GetBACnbacmuCut() )
    fnbacmuCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GBac::GetAllCuts() {
  //
  // return flag if event passes all bac cuts
  if ( gDebug ) cout << endl << "GBac::GetAllCuts() called" << endl << endl;

  if ( Getbac_etotCut() || GetnbacmuCut() )
    return  kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

TString GBac::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GBac::PrintMessage() called" << endl << endl;

  TString dummy = "Backing Calorimeter:\n\n";

  dummy.Append("Bac: ");
  
  dummy.Append(gInclude->FormatedChar(" bac_etot: ",9));
  dummy.Append(gInclude->FormatedDouble(gData->Getbac_etot(),4,2));
  dummy.Append(gInclude->FormatedChar(" nbacmu: ",9));
  dummy.Append(gInclude->FormatedDouble(gData->Getnbacmu(),4,2));

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GBac::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GBac::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("BAC") || option.Contains("ALL") ) {
    gLister->FillOutputList(PrintMessage(option));
    gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}
