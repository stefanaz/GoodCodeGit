//
// GDIMuon.cxx
//
// $Author: ibloch $
// $Date: 2005/10/12 16:47:40 $
// $Revision: 1.15 $
//

#include <GDIMuon.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GDIMuon)
#endif

//_____________________________________________________________
// GDIMuon
//
// dimuon class
//
GDIMuon::GDIMuon(GMuon *muon1, GMuon *muon2) : TObject() {
  //
  // GDIMuon normal constructor
  if ( gDebug ) cout << endl << "GDIMuon::GDIMuon normal ctor called" << endl << endl;

  fType        = kNormalDIMuon;
  fTriggerType = kTakeNone;

  fMuon1 = muon1;
  fMuon2 = muon2;

  if ( muon1->GetCharge() != muon2->GetCharge() )
    fDifCharge = kTRUE;
  else
    fDifCharge = kFALSE;
    
  fMuonsAllCuts       = kFALSE;
  fMuonsMVCuts        = kFALSE;
  fInvMassCut         = kFALSE;
  fDeltaRCut          = kFALSE;
  fDeltaPhiCut        = kFALSE;
  fDeltaThetaCut      = kFALSE;
  fDeltaEtaCut        = kFALSE;
  fPtAsymetryCut      = kFALSE;
  fEtFractionHighCut  = kFALSE;
  fEtFractionLowCut   = kFALSE;
  fDifChargeCut       = kFALSE;
  fCharmMCJpsiCut     = kFALSE;
  fCharmMCPsiprimeCut = kFALSE;
  fMCDIMuonHFLCut     = kFALSE;
  fAllCuts            = kFALSE;

  fmuissum01 = -999.;	
  fmuissum02 = -999.;	
  fmuissum03 = -999.;	
  fmuissum04 = -999.;	
  fmuissum05 = -999.;	
  fmuissum06 = -999.;	
  fmuissum07 = -999.;	
  fmuissum08 = -999.;	
  fmuissum09 = -999.;	
  fmuissum10 = -999.;	
  
  fmuissqsum01 = -999.;
  fmuissqsum02 = -999.;
  fmuissqsum03 = -999.;
  fmuissqsum04 = -999.;
  fmuissqsum05 = -999.;
  fmuissqsum06 = -999.;
  fmuissqsum07 = -999.;
  fmuissqsum08 = -999.;
  fmuissqsum09 = -999.;
  fmuissqsum10 = -999.;

  this->Calculate();

}

//_____________________________________________________________
GDIMuon::GDIMuon(GMC *mcmuon1, GMC *mcmuon2) : TObject() {
  //
  // GDIMuon MCDIMuon constructor
  if ( gDebug ) cout << endl << "GDIMuon::GDIMuon MCDIMuon ctor called" << endl << endl;

   fType        = kMCDIMuon;
   fMCMuon1 = mcmuon1;
   fMCMuon2 = mcmuon2;
//   fTriggerType = kTakeNone;

//   fMuon1 = muon1;
//   fMuon2 = muon2;

   if ( mcmuon1->GetCharge() != mcmuon2->GetCharge() )
     fDifCharge = kTRUE;
   else
     fDifCharge = kFALSE;
    
   fMCDIMuonHFLCut  = kFALSE;
//   fMuonsAllCuts    = kFALSE;
//   fMuonsMVCuts     = kFALSE;
//   fInvMassCut      = kFALSE;
//   fDeltaRCut       = kFALSE;
//   fDeltaPhiCut     = kFALSE;
//   fDeltaThetaCut   = kFALSE;
//   fDeltaEtaCut   = kFALSE;
//   fPtAsymetryCut   = kFALSE;
//   fEtFractionHighCut   = kFALSE;
//   fEtFractionLowCut   = kFALSE;
//   fDifChargeCut    = kFALSE;
//   fCharmMCJpsiCut  = kFALSE;
//   fAllCuts         = kFALSE;

//   fmuissum01 = -999.;	
//   fmuissum02 = -999.;	
//   fmuissum03 = -999.;	
//   fmuissum04 = -999.;	
//   fmuissum05 = -999.;	
//   fmuissum06 = -999.;	
//   fmuissum07 = -999.;	
//   fmuissum08 = -999.;	
//   fmuissum09 = -999.;	
//   fmuissum10 = -999.;	
  
//   fmuissqsum01 = -999.;
//   fmuissqsum02 = -999.;
//   fmuissqsum03 = -999.;
//   fmuissqsum04 = -999.;
//   fmuissqsum05 = -999.;
//   fmuissqsum06 = -999.;
//   fmuissqsum07 = -999.;
//   fmuissqsum08 = -999.;
//   fmuissqsum09 = -999.;
//   fmuissqsum10 = -999.;

   this->Calculate(mcmuon1, mcmuon2);

}

//_____________________________________________________________

GDIMuon::~GDIMuon() {
  //
  // GDIMuon default destructor
  if ( gDebug ) cout << endl << "GDIMuon::~GDIMuon dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GDIMuon::Calculate() {
  //
  // calculate quantities for jet muon match
  if ( gDebug ) cout << endl << "GDIMuon::Calculate called" << endl << endl;

  TLorentzVector dimuon = *fMuon1 + *fMuon2;

  fInvMass = dimuon.M();
  fdimuPt  = dimuon.Pt();

  fDeltaR       =  fMuon1->DeltaR(*fMuon2);
  fDeltaPhi     =  fMuon1->DeltaPhi(*fMuon2);
  fDeltaEta     =  fMuon1->Eta()-fMuon2->Eta();
  fDeltaTheta   =  fMuon1->Theta()-fMuon2->Theta();
  fDimuonPhi    =  dimuon.Phi();
  fDimuonEta    =  dimuon.Eta();
  fPtAsymetry   =  TMath::Abs( (fMuon1->Pt()-fMuon2->Pt()) / (fMuon1->Pt()+fMuon2->Pt()) );
  //  fEtFraction   =  (fMuon1->Pt()+fMuon2->Pt()) / gData->Getcal_et() ;
  fEtFraction   =  (fMuon1->Pt()+fMuon2->Pt()) / gCal->GetETtocuton() ; // improved 050410
//   cout<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" in gdimuon calculate - gCal->GetETtocuton(): "<<gCal->GetETtocuton()<<endl;
  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuon::Calculate(GMC *mcmuon1, GMC *mcmuon2) {
  //
  // calculate quantities for jet muon match
  if ( gDebug ) cout << endl << "GDIMuon::Calculate called" << endl << endl;

  TLorentzVector mcdimuon = *mcmuon1 + *mcmuon2;

  fInvMass = mcdimuon.M();
  fdimuPt  = mcdimuon.Pt();

  fDeltaR       =  mcmuon1->DeltaR(*mcmuon2);
  fDeltaPhi     =  mcmuon1->DeltaPhi(*mcmuon2);
  fDeltaEta     =  mcmuon1->Eta()-mcmuon2->Eta();
  fDeltaTheta   =  mcmuon1->Theta()-mcmuon2->Theta();
  fDimuonPhi    =  mcdimuon.Phi();
  fDimuonEta    =  mcdimuon.Eta();
  fPtAsymetry   =  TMath::Abs( (mcmuon1->Pt()-mcmuon2->Pt()) / (mcmuon1->Pt()+mcmuon2->Pt()) );
  //  fEtFraction   =  (mcmuon1->Pt()+mcmuon2->Pt()) / gData->Getcal_et() ;
  fEtFraction   =  (mcmuon1->Pt()+mcmuon2->Pt()) / gCal->GetETtocuton() ; // improved 050410
  
  return kTRUE;
}

//_____________________________________________________________

TString GDIMuon::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GDIMuon::PrintMessage called" << endl << endl;

  TString dummy = "DIMuon: ";
  
  dummy.Append(gInclude->FormatedChar(" muon 1 id: ",13));
  dummy.Append(gInclude->FormatedInt(fMuon1->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" muon 2 id: ",13));
  dummy.Append(gInclude->FormatedInt(fMuon2->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" muonsallcut: ",11));
  dummy.Append(gInclude->FormatedBool(fMuonsAllCuts));
  dummy.Append(gInclude->FormatedChar(" invmasscut: ",11));
  dummy.Append(gInclude->FormatedBool(fInvMassCut));
  dummy.Append(gInclude->FormatedChar(" deltarcut: ",11));
  dummy.Append(gInclude->FormatedBool(fDeltaRCut));
  dummy.Append(gInclude->FormatedChar(" deltaphicut: ",11));
  dummy.Append(gInclude->FormatedBool(fDeltaPhiCut));
  dummy.Append(gInclude->FormatedChar(" deltathetacut: ",11));
  dummy.Append(gInclude->FormatedBool(fDeltaThetaCut));
  dummy.Append(gInclude->FormatedChar(" deltaetacut: ",11));
  dummy.Append(gInclude->FormatedBool(fDeltaEtaCut));
  dummy.Append(gInclude->FormatedChar(" ptasymmcut: ",11));
  dummy.Append(gInclude->FormatedBool(fPtAsymetryCut));
  dummy.Append(gInclude->FormatedChar(" etfractionhighcut: ",11));
  dummy.Append(gInclude->FormatedBool(fEtFractionHighCut));
  dummy.Append(gInclude->FormatedChar(" etfractionlowcut: ",11));
  dummy.Append(gInclude->FormatedBool(fEtFractionLowCut));
  dummy.Append(gInclude->FormatedChar(" diffchargecut: ",11));
  dummy.Append(gInclude->FormatedBool(fDifChargeCut));
  dummy.Append(gInclude->FormatedChar(" muonsmvcut: ",11));
  dummy.Append(gInclude->FormatedBool(fMuonsMVCuts));
  dummy.Append(gInclude->FormatedChar(" allcuts: ",11));
  dummy.Append(gInclude->FormatedBool(fAllCuts));

  if ( fType == kChosenDIMuon )
    dummy.Append(gInclude->FormatedChar(" , dimuon is chosen muon ",13));
  else if ( fType == kGoodDIMuon )
    dummy.Append(gInclude->FormatedChar(" , dimuon is good muon ",13));
  else
    dummy.Append(gInclude->FormatedChar(" , dimuon is normal muon ",13));
  if ( fTriggerType == kTakeBoth )
    dummy.Append(gInclude->FormatedChar(" , both muons are taken for filling ",37));
  else if ( fTriggerType == kTakeMuon1 )
    dummy.Append(gInclude->FormatedChar(" , muon 1 is taken for filling ",32));
  else if ( fTriggerType == kTakeMuon2 )
    dummy.Append(gInclude->FormatedChar(" , muon 2 is taken for filling ",32));
  else
    dummy.Append(gInclude->FormatedChar(" , no muon is taken for filling ",33));

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GDIMuon::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GDIMuon::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}

// for reset method:
  
//   fmuissum01 = -999.;	
//   fmuissum02 = -999.;	
//   fmuissum03 = -999.;	
//   fmuissum04 = -999.;	
//   fmuissum05 = -999.;	
//   fmuissum06 = -999.;	
//   fmuissum07 = -999.;	
//   fmuissum08 = -999.;	
//   fmuissum09 = -999.;	
//   fmuissum10 = -999.;	
  
//   fmuissqsum01 = -999.;
//   fmuissqsum02 = -999.;
//   fmuissqsum03 = -999.;
//   fmuissqsum04 = -999.;
//   fmuissqsum05 = -999.;
//   fmuissqsum06 = -999.;
//   fmuissqsum07 = -999.;
//   fmuissqsum08 = -999.;
//   fmuissqsum09 = -999.;
//   fmuissqsum10 = -999.;
