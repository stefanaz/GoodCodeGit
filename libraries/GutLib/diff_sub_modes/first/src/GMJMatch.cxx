//
// GMJMatch.cxx
//
// $Author: gutsche $
// $Date: 2004/11/03 14:30:49 $
// $Revision: 1.13 $
//

#include <GMJMatch.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMJMatch)
#endif

//_____________________________________________________________
// GMJMatch
//
// jet-muon match class
//
  GMJMatch::GMJMatch(GMuon *muon, GJet *jet) : TObject() {
  //
  // GMJMatch normal constructor
  if ( gDebug ) cout << endl << "GMJMatch::GMJMatch normal ctor called" << endl << endl;

  fType = kNormalMatch;

  fJet = jet;
  fMuon = muon;

  // init variables
  fDeltaR        = -99.99;
  fDeltaPhi      = -99.99;
  fDeltaEta      = -99.99;
  fDeltaTheta    = -99.99;
  fPtRel         = -99.99;
  fPtRelJetMinMu = -99.99;
  fDeltaRJetMinMu= -99.99;
  fMuMinusJetPt  = -99.99;

  fMuonAllCuts     = kFALSE;
  fJetCritCuts     = kFALSE;
  fJetPtCut        = kFALSE;
  fMuMinusJetPtCut = kFALSE;
  fPtRelCut        = kFALSE;
  fAllCuts         = kFALSE;

  this->Calculate();

}

//_____________________________________________________________

GMJMatch::~GMJMatch() {
  //
  // GMJMatch default destructor
  if ( gDebug ) cout << endl << "GMJMatch::~GMJMatch dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GMJMatch::Calculate() {
  //
  // calculate quantities for jet muon match
  if ( gDebug ) cout << endl << "GMJMatch::Calculate called" << endl << endl;

  fDeltaR         =  fJet->DeltaR(*fMuon);
  fDeltaPhi       =  fJet->DeltaPhi(*fMuon);
  fDeltaEta       =  fJet->Eta()-fMuon->Eta();
  fDeltaTheta     =  fJet->Theta()-fMuon->Theta();
  fPtRel          =  fMuon->Pt(fJet->Vect());
  fEtJetMinusPtMu =  fJet->Et()-fMuon->Pt();

  // change ptrel definition relative to jet to relative to jet-mu
  TLorentzVector jetminusmu(*fJet);
  jetminusmu    -= *fMuon;
  fPtRelJetMinMu =  fMuon->Pt(jetminusmu.Vect());
  fDeltaRJetMinMu =  jetminusmu.DeltaR(*fMuon);

  fMuMinusJetPt =  TMath::Abs(fMuon->Pt()-fJet->Pt());

  

  return kTRUE;
}

//_____________________________________________________________

TString GMJMatch::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GMJMatch::PrintMessage called" << endl << endl;

  TString dummy = "MJMatch: ";
  
  dummy.Append(gInclude->FormatedChar(" muon id: ",10));
  dummy.Append(gInclude->FormatedInt(fMuon->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" jet id: ",9));
  dummy.Append(gInclude->FormatedInt(fJet->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" deltaR: ",9));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaR(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaRjetminmu: ",9));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaRJetMinMu(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaPhi: ",12));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaPhi(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaEta: ",12));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaEta(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaTheta: ",14));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaTheta(),3,2));
  dummy.Append(gInclude->FormatedChar(" ptrel: ",8));
  dummy.Append(gInclude->FormatedDouble(this->GetPtRel(),3,2));
  dummy.Append(gInclude->FormatedChar(" ptreljetminmu: ",16));
  dummy.Append(gInclude->FormatedDouble(this->GetPtRelJetMinMu(),3,2));
  
  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GMJMatch::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMJMatch::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}
