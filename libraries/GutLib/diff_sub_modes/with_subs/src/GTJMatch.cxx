//
// GTJMatch.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 08:22:58 $
// $Revision: 1.3 $
//

#include <GTJMatch.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTJMatch)
#endif

//_____________________________________________________________
// GTJMatch
//
// jet-track match class
//
  GTJMatch::GTJMatch(GTrack *track, GJet *jet) : TObject() {
  //
  // GTJMatch normal constructor
  if ( gDebug ) cout << endl << "GTJMatch::GTJMatch normal ctor called" << endl << endl;

  fType = kNormalTrackMatch;

  fJet = jet;
  fTrack = track;

  // init variables
  fDeltaR           = -99.99;
  fDeltaPhi         = -99.99;
  fDeltaEta         = -99.99;
  fDeltaTheta       = -99.99;
  fPtRel            = -99.99;
  fPtRelJetMinTrack = -99.99;
  fTrackMinusJetPt  = -99.99;
  fTJCosThetaStar   = -99.99; 
  fTJCosThetaStarSecJetID =0;
  fTJCosThetaStarXgamma= -99.99;
  fTJCosThetaStar_EtaJets = 999; 
  fTJCosThetaStar_MJets  = -999;  


  fTrackAllCuts       = kFALSE;
  fJetCritCuts        = kFALSE;
  fJetPtCut           = kFALSE;
  fTrackMuonKinCuts   = kFALSE;
  fTrackMinusJetPtCut = kFALSE;
  fAllCuts            = kFALSE;

  this->Calculate();

}

//_____________________________________________________________

GTJMatch::~GTJMatch() {
  //
  // GTJMatch default destructor
  if ( gDebug ) cout << endl << "GTJMatch::~GTJMatch dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GTJMatch::Calculate() {
  //
  // calculate quantities for jet track match
  if ( gDebug ) cout << endl << "GTJMatch::Calculate called" << endl << endl;

  fDeltaR       =  fJet->Vect().DeltaR(*fTrack);
  fDeltaPhi     =  fJet->Vect().DeltaPhi(*fTrack);
  fDeltaEta     =  fJet->Vect().Eta()-fTrack->Eta();
  fDeltaTheta   =  fJet->Vect().Theta()-fTrack->Theta();
  fPtRel        =  fTrack->Pt(fJet->Vect());

  // change ptrel definition relative to jet to relative to jet-track
  TVector3 jetminustrack(fJet->Vect());
  jetminustrack    -= *fTrack;
  fPtRelJetMinTrack =  fTrack->Pt(jetminustrack);

  fTrackMinusJetPt =  TMath::Abs(fTrack->Pt()-fJet->Vect().Pt());

  return kTRUE;
}

//_____________________________________________________________

TString GTJMatch::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GTJMatch::PrintMessage called" << endl << endl;

  TString dummy = "TJMatch: ";
  
  dummy.Append(gInclude->FormatedChar(" track id: ",10));
  dummy.Append(gInclude->FormatedInt(fTrack->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" jet id: ",9));
  dummy.Append(gInclude->FormatedInt(fJet->GetID(),3,0," "));
  dummy.Append(gInclude->FormatedChar(" deltaR: ",9));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaR(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaPhi: ",12));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaPhi(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaEta: ",12));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaEta(),3,2));
  dummy.Append(gInclude->FormatedChar(" deltaTheta: ",14));
  dummy.Append(gInclude->FormatedDouble(this->GetDeltaTheta(),3,2));
  dummy.Append(gInclude->FormatedChar(" ptrel: ",8));
  dummy.Append(gInclude->FormatedDouble(this->GetPtRel(),3,2));
  dummy.Append(gInclude->FormatedChar(" ptreljetmintrack: ",16));
  dummy.Append(gInclude->FormatedDouble(this->GetPtRelJetMinTrack(),3,2));
  
  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GTJMatch::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GTJMatch::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}
