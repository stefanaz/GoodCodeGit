//
// GJet.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 07:26:49 $
// $Revision: 1.26 $
//

#include <GJet.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GJet)
#endif

//_____________________________________________________________
// GJet
//
// jet class
//
GJet::GJet() : TLorentzVector() {
  //
  // GJet default constructor
  if ( gDebug ) cout << endl << "GJet::GJet default ctor called" << endl << endl;

  fID    = -99;
  fType  = kNormalJet;

  fMCJet = 0;

  fMatched = 0;
  fUnmatched = kFALSE;
  fMJCosThetaStar=-99;
  fSecondJetID=0;
  fMJCosThetaStar_xgamma=0;

}

//_____________________________________________________________

GJet::GJet(Int_t id, Double_t et, Double_t eta, Double_t phi, Double_t m) : TLorentzVector() {
  //
  // GJet normal constructor
  if ( gDebug ) cout << endl << "GJet::GJet normal ctor called" << endl << endl;

  Double_t theta = 2 * TMath::ATan(TMath::Exp(-eta));
  Double_t E = et / TMath::Sin(theta);
  Double_t p = TMath::Sqrt(TMath::Power(E,2)-TMath::Power(m,2));
  Double_t pt = p / E * et;

  SetPtEtaPhiM(pt,eta,phi,m);

  fID    = id;
  fType  = kNormalJet;

  fMCJet = 0;

  fEta = CheckEtaCut();
  fMatched = 0;
  fUnmatched = kFALSE;
  fEtbreit = 0.;
  fMJCosThetaStar=-99;
  fSecondJetID=0;
  fMJCosThetaStar_xgamma=0;
  fMJCosThetaStar_MJets = -999;
  fMJCosThetaStar_EtaJets = 999;
//   GJet(id, et, eta, phi, m, 0.);
}
//_____________________________________________________________

GJet::GJet(Int_t id, Double_t et, Double_t eta, Double_t phi, Double_t m, Double_t etbreit) : TLorentzVector() {
  //
  // GJet normal constructor
  if ( gDebug ) cout << endl << "GJet::GJet normal ctor called" << endl << endl;

  Double_t theta = 2 * TMath::ATan(TMath::Exp(-eta));
  Double_t E = et / TMath::Sin(theta);
  Double_t p = TMath::Sqrt(TMath::Power(E,2)-TMath::Power(m,2));
  Double_t pt = p / E * et;

  SetPtEtaPhiM(pt,eta,phi,m);

  fID    = id;
  fType  = kNormalJet;

  fMCJet = 0;

  fEta = CheckEtaCut();
  fMatched = 0;
  fUnmatched = kFALSE;
  fEtbreit = etbreit;
  fMJCosThetaStar=-99;
  fSecondJetID=0;
  fMJCosThetaStar_xgamma=0;
  fMJCosThetaStar_MJets = -999;
  fMJCosThetaStar_EtaJets = 999;

}

//_____________________________________________________________

GJet::GJet(Int_t id, Double_t px, Double_t py, Double_t pz, Double_t e, EZJetType type) : TLorentzVector(px,py,pz,e) {
  //
  // GJet normal constructor
  if ( gDebug ) cout << endl << "GJet::GJet normal ctor called" << endl << endl;

  fID    = id;
  fType  = type;

  fMCJet = 0;

  fEta = CheckEtaCut();
  fMatched = 0;
  fUnmatched = kFALSE;
  fEtbreit = 0.;
  fMJCosThetaStar=-99;
  fSecondJetID=0;
  fMJCosThetaStar_xgamma=0;
  fMJCosThetaStar_MJets = -999;
  fMJCosThetaStar_EtaJets = 999;

//   GJet(id, px, py, pz, e, type, 0.);
}
//_____________________________________________________________

GJet::GJet(Int_t id, Double_t px, Double_t py, Double_t pz, Double_t e, EZJetType type, Double_t etbreit) : TLorentzVector(px,py,pz,e) {
  //
  // GJet normal constructor
  if ( gDebug ) cout << endl << "GJet::GJet normal ctor called" << endl << endl;

  fID    = id;
  fType  = type;

  fMCJet = 0;

  fEta = CheckEtaCut();
  fMatched = 0;
  fUnmatched = kFALSE;
  fEtbreit = etbreit;
  fMJCosThetaStar=-99;
  fSecondJetID=0;
  fMJCosThetaStar_xgamma=0;
  fMJCosThetaStar_MJets = -999;
  fMJCosThetaStar_EtaJets = 999;

}

//_____________________________________________________________

GJet::~GJet() {
  //
  // GJet default destructor
  if ( gDebug ) cout << endl << "GJet::~GJet dtor called" << endl << endl;

}

//_____________________________________________________________

TString GJet::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GJet::PrintMessage called" << endl << endl;

  TString dummy = "Jet: ";
  
  dummy.Append(gInclude->FormatedChar(" id: ",5));
  dummy.Append(gInclude->FormatedInt(fID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" px: ",5));
  dummy.Append(gInclude->FormatedDouble(Px(),4,2));
  dummy.Append(gInclude->FormatedChar(" py: ",5));
  dummy.Append(gInclude->FormatedDouble(Py(),4,2));
  dummy.Append(gInclude->FormatedChar(" pz: ",5));
  dummy.Append(gInclude->FormatedDouble(Pz(),4,2));
  dummy.Append(gInclude->FormatedChar(" pt: ",5));
  dummy.Append(gInclude->FormatedDouble(Pt(),4,2));
  dummy.Append(gInclude->FormatedChar(" E: ",4));
  dummy.Append(gInclude->FormatedDouble(E(),4,2));
  dummy.Append(gInclude->FormatedChar(" eta: ",6));
  dummy.Append(gInclude->FormatedDouble(Eta(),2,2));
  dummy.Append(gInclude->FormatedChar(" phi: ",6));
  dummy.Append(gInclude->FormatedDouble(Phi(),3,2));
  dummy.Append(gInclude->FormatedChar(" Etbreit: ",10));
  dummy.Append(gInclude->FormatedDouble(GetEtbreit(),4,2));
  if ( fType == kFirst )
    dummy.Append(gInclude->FormatedChar(" type kFirst ",17));
  else if ( fType == kSecond )
    dummy.Append(gInclude->FormatedChar(" type kSecond ",17));
  else if ( fType == kMCFirst )
    dummy.Append(gInclude->FormatedChar(" type kMCFirst ",17));
  else if ( fType == kMCSecond )
    dummy.Append(gInclude->FormatedChar(" type kMCSecond ",17));
  else if ( fType == kMCJet )
    dummy.Append(gInclude->FormatedChar(" type kMCJet ",17));
  else if ( fType == kNormalJet )
    dummy.Append(gInclude->FormatedChar(" type kNormalJet ",14));
  dummy.Append(gInclude->FormatedChar(" eta cut: ",11));
  dummy.Append(gInclude->FormatedBool(fEta));

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GJet::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMuon::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(PrintMessage(option));
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GJet::CheckEtaCut() {
  //
  // check eta cut
  if ( gDebug ) cout << endl << "GMuon::CheckEtaCut called" << endl << endl;
  
  Bool_t returny = kFALSE;

  if ( (Eta() >= gCards->GetJETEtaLowCut()) && (Eta() <= gCards->GetJETEtaUpCut()))
    returny = kTRUE;

  return returny;
}

//_____________________________________________________________

Double_t GJet::Et() {
  //
  // return E_T of jet
  if ( gDebug ) cout << endl << "GMuon::Et called" << endl << endl;
  
  Double_t et = E()*Pt()/P();

  return et;
}

//_____________________________________________________________

//  Double_t GJet::Etbreit() {
//    //
//    // return E_T of jet
//    if ( gDebug ) cout << endl << "GMuon::Etbreit called" << endl << endl;
  
//    Double_t etbreit;
//    etbreit= E()*Pt()/P();

//    return etbreit;
//  }

//_____________________________________________________________

void GJet::SetMatched(Bool_t input) {
  //
  // increase matched counter by one if input is true
  // set counter to zero if input is false !!!
  if ( gDebug ) cout << endl << "GMuon::SetMatched called" << endl << endl;
  
  if ( input == kTRUE ) {
    fMatched += 1;
  } else {
    fMatched = 0;
  }

}
