//
// GTrimuon.cxx
//
// $Author: dbot $
// $Date: 2010/04/15 07:07:40 $
// $Revision: 1.00 $
//

#include <GTriMuon.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTriMuon)
#endif

//_____________________________________________________________
// GTriMuon
//
// trimuon class
//
GTriMuon::GTriMuon(GMuon *muon1, GMuon *muon2, GMuon *muon3) : TObject() {
  //
  // GTriMuon normal constructor
  if ( gDebug ) cout << endl << "GTriMuon::GTriMuon normal ctor called" << endl << endl;

  fType        = kNormalTriMuon;
  fTriggerType = kTakeTriNone;

  fMuon1 = muon1;
  fMuon2 = muon2;
  fMuon3 = muon3;

  if ( (muon1->GetCharge() != muon2->GetCharge()) || (muon1->GetCharge() != muon3->GetCharge()) || (muon2->GetCharge() != muon3->GetCharge()) )
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
  fMCTriMuonHFLCut    = kFALSE;
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
GTriMuon::GTriMuon(GMC *mcmuon1, GMC *mcmuon2,  GMC *mcmuon3) : TObject() {
  //
  // GTriMuon MCTriMuon constructor
  if ( gDebug ) cout << endl << "GTriMuon::GTriMuon MCTriMuon ctor called" << endl << endl;

   fType    = kMCTriMuon;
   fMCMuon1 = mcmuon1;
   fMCMuon2 = mcmuon2;
   fMCMuon3 = mcmuon3;

   if ( (mcmuon1->GetCharge() != mcmuon2->GetCharge()) || (mcmuon1->GetCharge() != mcmuon3->GetCharge()) || (mcmuon2->GetCharge() != mcmuon3->GetCharge()) )
     fDifCharge = kTRUE;
   else
     fDifCharge = kFALSE;
    
   fMCTriMuonHFLCut  = kFALSE;

   this->Calculate(mcmuon1, mcmuon2, mcmuon3);

}

//_____________________________________________________________

GTriMuon::~GTriMuon() {
  //
  // GTriMuon default destructor
  if ( gDebug ) cout << endl << "GTriMuon::~GTriMuon dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GTriMuon::Calculate() {
  //
  // calculate quantities for jet muon match
  if ( gDebug ) cout << endl << "GTriMuon::Calculate called" << endl << endl;

  TLorentzVector dimuon1 = *fMuon1 + *fMuon2;
  TLorentzVector dimuon2 = *fMuon1 + *fMuon3;
  TLorentzVector dimuon3 = *fMuon2 + *fMuon3;
  TLorentzVector trimuon = *fMuon1 + *fMuon2 + *fMuon3;

  fInvMass1 = dimuon1.M();
  fInvMass2 = dimuon2.M();
  fInvMass3 = dimuon3.M();

  fDeltaR1      =  fMuon1->DeltaR(*fMuon2);
  fDeltaR2      =  fMuon1->DeltaR(*fMuon3);
  fDeltaR3      =  fMuon2->DeltaR(*fMuon3);
  fDeltaPhi1    =  fMuon1->DeltaPhi(*fMuon2);
  fDeltaPhi2    =  fMuon1->DeltaPhi(*fMuon3);
  fDeltaPhi3    =  fMuon2->DeltaPhi(*fMuon3);
  fDeltaEta1    =  fMuon1->Eta()-fMuon2->Eta();
  fDeltaEta2    =  fMuon1->Eta()-fMuon3->Eta();
  fDeltaEta3    =  fMuon2->Eta()-fMuon3->Eta();
  fDeltaTheta1  =  fMuon1->Theta()-fMuon2->Theta();
  fDeltaTheta2  =  fMuon1->Theta()-fMuon3->Theta();
  fDeltaTheta3  =  fMuon2->Theta()-fMuon3->Theta();
  fTriMuonPhi   =  trimuon.Phi();
  fTriMuonEta   =  trimuon.Eta();
  fPtAsymetry1  =  TMath::Abs( (fMuon1->Pt()-fMuon2->Pt()) / (fMuon1->Pt()+fMuon2->Pt()) );
  fPtAsymetry2  =  TMath::Abs( (fMuon1->Pt()-fMuon3->Pt()) / (fMuon1->Pt()+fMuon3->Pt()) );
  fPtAsymetry3  =  TMath::Abs( (fMuon2->Pt()-fMuon3->Pt()) / (fMuon2->Pt()+fMuon3->Pt()) );
  fEtFraction1  =  (fMuon1->Pt()+fMuon2->Pt()) / gCal->GetETtocuton() ; // improved 050410
  fEtFraction2  =  (fMuon1->Pt()+fMuon3->Pt()) / gCal->GetETtocuton() ; // improved 050410
  fEtFraction3  =  (fMuon2->Pt()+fMuon3->Pt()) / gCal->GetETtocuton() ; // improved 050410

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuon::Calculate(GMC *mcmuon1, GMC *mcmuon2, GMC *mcmuon3) {
  //
  // calculate quantities for jet muon match
  if ( gDebug ) cout << endl << "GTriMuon::Calculate called" << endl << endl;

  TLorentzVector mcdimuon1 = *mcmuon1 + *mcmuon2;
  TLorentzVector mcdimuon2 = *mcmuon1 + *mcmuon3;
  TLorentzVector mcdimuon3 = *mcmuon3 + *mcmuon3;
  TLorentzVector mctrimuon = *mcmuon1 + *mcmuon2 + *mcmuon3;

  fInvMass1 = mcdimuon1.M();
  fInvMass2 = mcdimuon2.M();
  fInvMass3 = mcdimuon3.M();

  fDeltaR1      =  mcmuon1->DeltaR(*mcmuon2);
  fDeltaR2      =  mcmuon1->DeltaR(*mcmuon3);
  fDeltaR3      =  mcmuon2->DeltaR(*mcmuon3);
  fDeltaPhi1    =  mcmuon1->DeltaPhi(*mcmuon2);
  fDeltaPhi2    =  mcmuon1->DeltaPhi(*mcmuon3);
  fDeltaPhi3    =  mcmuon2->DeltaPhi(*mcmuon3);
  fDeltaEta1    =  mcmuon1->Eta()-mcmuon2->Eta();
  fDeltaEta2    =  mcmuon1->Eta()-mcmuon3->Eta();
  fDeltaEta3    =  mcmuon2->Eta()-mcmuon3->Eta();
  fDeltaTheta1  =  mcmuon1->Theta()-mcmuon2->Theta();
  fDeltaTheta2  =  mcmuon1->Theta()-mcmuon3->Theta();
  fDeltaTheta3  =  mcmuon2->Theta()-mcmuon3->Theta();
  fTriMuonPhi   =  mctrimuon.Phi();
  fTriMuonEta   =  mctrimuon.Eta();
  fPtAsymetry1  =  TMath::Abs( (mcmuon1->Pt()-mcmuon2->Pt()) / (mcmuon1->Pt()+mcmuon2->Pt()) );
  fPtAsymetry2  =  TMath::Abs( (mcmuon1->Pt()-mcmuon3->Pt()) / (mcmuon1->Pt()+mcmuon3->Pt()) );
  fPtAsymetry3  =  TMath::Abs( (mcmuon2->Pt()-mcmuon3->Pt()) / (mcmuon2->Pt()+mcmuon3->Pt()) );
  fEtFraction1  =  (mcmuon1->Pt()+mcmuon2->Pt()) / gCal->GetETtocuton() ; // improved 050410
  fEtFraction2  =  (mcmuon1->Pt()+mcmuon3->Pt()) / gCal->GetETtocuton() ; // improved 050410
  fEtFraction3  =  (mcmuon2->Pt()+mcmuon3->Pt()) / gCal->GetETtocuton() ; // improved 050410
  return kTRUE;
}

//_____________________________________________________________

TString GTriMuon::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GTriMuon::PrintMessage called" << endl << endl;

  TString dummy = "TriMuon: ";
  
  dummy.Append(gInclude->FormatedChar(" muon 1 id: ",13));
  dummy.Append(gInclude->FormatedInt(fMuon1->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" muon 2 id: ",13));
  dummy.Append(gInclude->FormatedInt(fMuon2->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" muon 3 id: ",13));
  dummy.Append(gInclude->FormatedInt(fMuon3->GetID(),3,0," "));
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

  if ( fType == kChosenTriMuon )
    dummy.Append(gInclude->FormatedChar(" , trimuon is chosen muon ",13));
  else if ( fType == kGoodTriMuon )
    dummy.Append(gInclude->FormatedChar(" , trimuon is good muon ",13));
  else
    dummy.Append(gInclude->FormatedChar(" , trimuon is normal muon ",13));
  if ( fTriggerType == kTakeAll )
    dummy.Append(gInclude->FormatedChar(" , both muons are taken for filling ",37));
  else if ( fTriggerType == kTakeTriMuon1 )
    dummy.Append(gInclude->FormatedChar(" , muon 1 is taken for filling ",32));
  else if ( fTriggerType == kTakeTriMuon2 )
    dummy.Append(gInclude->FormatedChar(" , muon 2 is taken for filling ",32));
  else if ( fTriggerType == kTakeTriMuon3 )
    dummy.Append(gInclude->FormatedChar(" , muon 3 is taken for filling ",32));
  else
    dummy.Append(gInclude->FormatedChar(" , no muon is taken for filling ",33));

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GTriMuon::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GTriMuon::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}

