//
// GMC.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 07:30:12 $
// $Revision: 1.13 $
//

#include <GMC.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMC)
#endif

//_____________________________________________________________
// GMC
//
// mc particle class
//
GMC::GMC() : TLorentzVector() {
  //
  // GMC default constructor
  if ( gDebug ) cout << endl << "GMC::GMC default ctor called" << endl << endl;

  fHeavyFlavourQuark     = kFALSE;

  fMCKINID          = 0;
  CheckParticleType(0);

  fMCMuonType         = kUnidentifiedMCMuon;

  fMuon             = 0;
  fMCMuon           = 0;
  fMuonBQuark       = 0;
  fMuonDirectParent = 0;
  fMother           = 0;
  fVertex           = 0;

  fMotherID         = 0;
  fProducedAt       = 0;
  fImpact           = -9999.99;
  fSignificance     = -9999.99;
  fImpact2D         = -9999.99;
  fSignificance2D   = -9999.99;

  fAssociatedWithNegativeFMCKINID = kFALSE;

  fMCJet = 0;
  fMCJet2 = 0;
  fMCPMJet = 0;
  fMCMuonJet = 0;
  fMCPMMuonJet = 0;
}

//_____________________________________________________________

GMC::GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E) : TLorentzVector(px,py,pz,E) {
  //
  // GMC normal constructor
  if ( gDebug ) cout << endl << "GMC::GMC normal ctor called" << endl << endl;

  fHeavyFlavourQuark     = kFALSE;

  fMCKINID          = fmckinid;
  CheckParticleType(partid);

  fMCMuonType         = kUnidentifiedMCMuon;

  fAssociatedWithNegativeFMCKINID = kFALSE;

  fMuon             = 0;
  fMCMuon           = 0;
  fMuonBQuark       = 0;
  fMuonDirectParent = 0;
  fMother           = 0;
  fVertex           = 0;

  fMotherID         = 0;
  fProducedAt       = 0;
  fImpact           = -9999.99;
  fSignificance     = -9999.99;
  fImpact2D         = -9999.99;
  fSignificance2D   = -9999.99;

  fMCJet = 0;
  fMCJet2 = 0;
  fMCPMJet = 0;
  fMCMuonJet = 0;
  fMCPMMuonJet = 0;
}

//_____________________________________________________________

GMC::GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E, Int_t motherid, Int_t producedat, Double_t impact, Double_t impact2D) : TLorentzVector(px,py,pz,E) {
  //
  // GMC normal constructor
  if ( gDebug ) cout << endl << "GMC::GMC normal ctor called" << endl << endl;

  fHeavyFlavourQuark = kFALSE;

  fMCKINID          = fmckinid;
  CheckParticleType(partid);

  fMCMuonType         = kUnidentifiedMCMuon;

  fAssociatedWithNegativeFMCKINID = kFALSE;

  fMuon             = 0;
  fMCMuon           = 0;
  fMuonBQuark       = 0;
  fMuonDirectParent = 0;
  fMother           = 0;
  fVertex           = 0;

  fMotherID         = motherid;
  fProducedAt       = producedat;
  fImpact           = impact;
  //  fSignificance     = significance;
  fSignificance     = 0;
  fImpact2D         = impact2D;
  //  fSignificance2D   = significance2D;
  fSignificance2D   = 0;

  fMCJet = 0;
  fMCJet2 = 0;
  fMCPMJet = 0;
  fMCPMMuonJet = 0;
}

//_____________________________________________________________

GMC::GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E, GMuon *muon, GMC *bquark, GMC *directparent) : TLorentzVector(px,py,pz,E) {
  //
  // GMC muon constructor
  if ( gDebug ) cout << endl << "GMC::GMC muon ctor called" << endl << endl;

  fHeavyFlavourQuark = kFALSE;

  fMCKINID          = fmckinid;
  CheckParticleType(partid);

  fMCMuonType         = kUnidentifiedMCMuon;

  fAssociatedWithNegativeFMCKINID = kFALSE;

  fMuon             = muon;
  fMCMuon           = 0;
  fMuonBQuark       = bquark;
  fMuonDirectParent = directparent;
  fMother           = 0;
  fVertex           = 0;

  fMotherID         = 0;
  fProducedAt       = 0;
  fImpact           = -9999.99;
  fSignificance     = -9999.99;
  fImpact2D         = -9999.99;
  fSignificance2D   = -9999.99;

  fMCJet = 0;
  fMCJet2 = 0;
  fMCPMJet = 0;
  fMCMuonJet = 0;
  fMCPMMuonJet = 0;
}

//_____________________________________________________________

GMC::~GMC() {
  //
  // GMC default destructor
  if ( gDebug ) cout << endl << "GMC::~GMC dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GMC::CheckParticleType(Int_t partid) {
  //
  // check mc particle type
  if ( gDebug ) cout << endl << "GMC::CheckParticleType called" << endl << endl;

  // reset particle
  fPartID       = partid;
  fType         = kUnresolved;
  fCharge       = 0.0;

  if ( partid == 1 ) {
    fType = kDown;
    fCharge = -1/3;
  } else if ( partid == 2 ) {
    fType = kAntiDown;
    fCharge = 1/3;
  } else if ( partid == 3 ) {
    fType = kUp;
    fCharge = 2/3;
  } else if ( partid == 4 ) {
    fType = kAntiUp;
    fCharge = -2/3;
  } else if ( partid == 5 ) {
    fType = kStrange;
    fCharge = -1/3;
  } else if ( partid == 6 ) {
    fType = kAntiStrange;
    fCharge = 1/3;
  } else if ( partid == 7 ) {
    fType = kCharm;
    fCharge = 2/3;
    fHeavyFlavourQuark = kTRUE;
  } else if ( partid == 8 ) {
    fType = kAntiCharm;
    fCharge = -2/3;
    fHeavyFlavourQuark = kTRUE;
  } else if ( partid == 9 ) {
    fType = kBeauty;
    fCharge = -1/3;
    fHeavyFlavourQuark = kTRUE;
  } else if ( partid == 10 ) {
    fType = kAntiBeauty;
    fCharge = 1/3;
    fHeavyFlavourQuark = kTRUE;
  } else if ( partid == 11 ) {
    fType = kTop;
    fCharge = 2/3;
    fHeavyFlavourQuark = kTRUE;
  } else if ( partid == 12 ) {
    fType = kAntiTop;
    fCharge = -2/3;
    fHeavyFlavourQuark = kTRUE;
  } else if ( partid == 23 ) {
    fType = kElectron;
    fCharge = -1.0;
  } else if ( partid == 24 ) {
    fType = kPositron;
    fCharge = 1.0;
  } else if ( partid == 25 ) {
    fType = kMuon;
    fCharge = -1.0;
  } else if ( partid == 26 ) {
    fType = kMuon;
    fCharge = 1.0;
  } else if ( partid == 54 ) {
    fType = kPi;
    fCharge = 1.0;
  } else if ( partid == 55 ) {
    fType = kPi;
    fCharge = -1.0;
  } else if ( partid == 56 ) {
    fType = kPiZero;
    fCharge = 0.0;
  } else if ( partid == 57 ) {
    fType = kEta;
    fCharge = 0.0;
  } else if ( partid == 58 ) {
    fType = kK;
    fCharge = 1.0;
  } else if ( partid == 59 ) {
    fType = kK;
    fCharge = -1.0;
  } else if ( partid == 60 ) {
    fType = kKZero;
    fCharge = 0.0;
  } else if ( partid == 61 ) {
    fType = kAntiKZero;
    fCharge = 0.0;
  } else if ( partid == 62 ) {
    fType = kKShort;
    fCharge = 0.0;
  } else if ( partid == 63 ) {
    fType = kKLong;
    fCharge = 0.0;
  } else if ( partid == 64 ) {
    fType = kD;
    fCharge = 1.0;
  } else if ( partid == 65 ) {
    fType = kD;
    fCharge = -1.0;
  } else if ( partid == 66 ) {
    fType = kDZero;
    fCharge = 0.0;
  } else if ( partid == 67 ) {
    fType = kAntiDZero;
    fCharge = 0.0;
  } else if ( partid == 68 ) {
    fType = kDS;
    fCharge = 1.0;
  } else if ( partid == 69 ) {
    fType = kDS;
    fCharge = -1.0;
  } else if ( partid == 72 ) {
    fType = kB;
    fCharge = 1.0;
  } else if ( partid == 73 ) {
    fType = kB;
    fCharge = -1.0;
  } else if ( partid == 74 ) {
    fType = kBZero;
    fCharge = 0.0;
  } else if ( partid == 75 ) {
    fType = kAntiBZero;
    fCharge = 0.0;
  } else if ( partid == 76 ) {
    fType = kRho;
    fCharge = 1.0;
  } else if ( partid == 77 ) {
    fType = kRho;
    fCharge = -1.0;
  } else if ( partid == 78 ) {
    fType = kRhoZero;
    fCharge = 0.0;
  } else if ( partid == 79 ) {
    fType = kOmega;
    fCharge = 0.0;
  } else if ( partid == 146 ) {
    fType = kKStar;
    fCharge = 1.0;
  } else if ( partid == 147 ) {
    fType = kKStar;
    fCharge = -1.0;
  } else if ( partid == 148 ) {
    fType = kKStarZero;
    fCharge = 0.0;
  } else if ( partid == 149 ) {
    fType = kAntiKStarZero;
    fCharge = 0.0;
  } else if ( partid == 190 ) {
    fType = kProton;
    fCharge = 1.0;
  } else if ( partid == 191 ) {
    fType = kAntiProton;
    fCharge = -1.0;
  } else if ( partid == 194 ) {
    fType = kLambda;
    fCharge = 0.0;
  } else if ( partid == 195 ) {
    fType = kAntiLambda;
    fCharge = 0.0;
  } else if ( partid == 214 ) {
    fType = kLambdaBZero;
    fCharge = 0.0;
  } else if ( partid == 215 ) {
    fType = kAntiLambdaBZero;
    fCharge = 0.0;
  } else if ( partid == 256 ) {
    fType = kDeltaTwoPlus;
    fCharge = 2.0;
  } else if ( partid == 257 ) {
    fType = kDeltaTwoMinus;
    fCharge = -2.0;
  } else if ( partid == 468 ) {
    fType = kAntiBSZero;
    fCharge = 0.0;
  } else if ( partid == 469 ) {
    fType = kBSZero;
    fCharge = 0.0;
  } else if ( partid == 125 ) {
    fType = kJpsi;
    fCharge = 0.0;
  } else if ( partid == 129 ) {
    fType = kPsiprime;
    fCharge = 0.0;
  } else if ( partid == 492 ) {
    fType = kCASCBP;
    fCharge = -1.0;
  } else if ( partid == 493 ) {
    fType = kCASCBP;
    fCharge = 1.0;
  } else if ( partid == 134 ) {
    fType = kYPSI1S;
    fCharge = 0.0;
  } else if ( partid == 138 ) {
    fType = kYPSI2S;
    fCharge = 0.0;
  } else if ( partid == 142 ) {
    fType = kYPSI3S;
    fCharge = 0.0;
  } else if ( partid == 2092 ) {
    fType = kString;
    fCharge = 0.0;
  } else if ( partid == 2336 ) {
    fType = kCCUTwoMinus;
    fCharge = -2.0;
  } 

  return kTRUE;
}

//_____________________________________________________________

TString GMC::ReturnParticleType() {
  //
  // return mc particle type
  if ( gDebug ) cout << endl << "GMC::ReturnParticleType called" << endl << endl;

  TString type = "";

  if ( fType == kUp ) {
    type.Append("u quark");
  } else if ( fType == kAntiUp ) {
    type.Append("anti u quark");
  } else if ( fType == kDown ) {
    type.Append("d quark");
  } else if ( fType == kAntiDown ) {
    type.Append("anti d quark");
  } else if ( fType == kStrange ) {
    type.Append("s quark");
  } else if ( fType == kAntiStrange ) {
    type.Append("anti s quark");
  } else if ( fType == kCharm ) {
    type.Append("c quark");
  } else if ( fType == kAntiCharm ) {
    type.Append("anti c quark");
  } else if ( fType == kBeauty ) {
    type.Append("b quark");
  } else if ( fType == kAntiBeauty ) {
    type.Append("anti b quark");
  } else if ( fType == kTop ) {
    type.Append("t quark");
  } else if ( fType == kAntiTop ) {
    type.Append("anti t quark");
  } else if ( fType == kElectron ) {
    type.Append("electron");
  } else if ( fType == kPositron ) {
    type.Append("positron");
  } else if ( fType == kMuon ) {
    type.Append("muon");
  } else if ( fType == kPi ) {
    type.Append("pi");
  } else if ( fType == kPiZero ) {
    type.Append("pi 0");
  } else if ( fType == kEta ) {
    type.Append("eta");
  } else if ( fType == kK ) {
    type.Append("K");
  } else if ( fType == kKZero ) {
    type.Append("K0");
  } else if ( fType == kAntiKZero ) {
    type.Append("anti K0");
  } else if ( fType == kKShort ) {
    type.Append("K short");
  } else if ( fType == kKLong ) {
    type.Append("K long");
  } else if ( fType == kD ) {
    type.Append("D");
  } else if ( fType == kDZero ) {
    type.Append("D0");
  } else if ( fType == kAntiDZero ) {
    type.Append("anti D0");
  } else if ( fType == kDS ) {
    type.Append("DS");
  } else if ( fType == kB ) {
    type.Append("B");
  } else if ( fType == kBZero ) {
    type.Append("B0");
  } else if ( fType == kAntiBZero ) {
    type.Append("anti B0");
  } else if ( fType == kRho ) {
    type.Append("rho");
  } else if ( fType == kRhoZero ) {
    type.Append("rho 0");
  } else if ( fType == kOmega ) {
    type.Append("omega");
  } else if ( fType == kKStar ) {
    type.Append("K*");
  } else if ( fType == kKStarZero ) {
    type.Append("K* 0");
  } else if ( fType == kAntiKStarZero ) {
    type.Append("anti K* 0");
  } else if ( fType == kProton ) {
    type.Append("proton");
  } else if ( fType == kAntiProton ) {
    type.Append("anti proton");
  } else if ( fType == kLambda ) {
    type.Append("lambda");
  } else if ( fType == kAntiLambda ) {
    type.Append("anti lambda");
  } else if ( fType == kLambdaBZero ) {
    type.Append("lambda B0");
  } else if ( fType == kAntiLambdaBZero ) {
    type.Append("anti lambda B0");
  } else if ( fType == kDeltaTwoPlus ) {
    type.Append("delta 2+");
  } else if ( fType == kDeltaTwoMinus ) {
    type.Append("delta 2-");
  } else if ( fType == kAntiBSZero ) {
    type.Append("anti BS0");
  } else if ( fType == kBSZero ) {
    type.Append("BS0");
  } else if ( fType == kJpsi ) {
    type.Append("Jpsi");
  } else if ( fType == kPsiprime ) {
    type.Append("Psiprime");
  } else if ( fType == kCASCBP ) {
    type.Append("CASCBP");
  } else if ( fType == kYPSI1S ) {
    type.Append("Upsilon1s");
  } else if ( fType == kYPSI2S ) {
    type.Append("Upsilon2s");
  } else if ( fType == kYPSI3S ) {
    type.Append("Upsilon3s");
  } else if ( fType == kString ) {
    type.Append("string");
  } else if ( fType == kCCUTwoMinus ) {
    type.Append("CCU 2-");
  } else {
    type += fPartID;
  } 

  return type;
}

//_____________________________________________________________

TString GMC::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GMC::PrintMessage called" << endl << endl;

  TString dummy = "GMC: ";
  
  dummy.Append(gInclude->FormatedChar(" FMCKIN id: ",13));
  dummy.Append(gInclude->FormatedInt(fMCKINID,6,0," "));
  dummy.Append(gInclude->FormatedChar(" Particle: ",12));
  dummy.Append(gInclude->FormatedChar(ReturnParticleType(),15));
  dummy.Append(gInclude->FormatedChar(" charge: ",9));
  dummy.Append(gInclude->FormatedDouble(fCharge,3,2));
  dummy.Append(gInclude->FormatedChar(" px: ",5));
  dummy.Append(gInclude->FormatedDouble(Px(),3,2));
  dummy.Append(gInclude->FormatedChar(" py: ",5));
  dummy.Append(gInclude->FormatedDouble(Py(),3,2));
  dummy.Append(gInclude->FormatedChar(" pz: ",5));
  dummy.Append(gInclude->FormatedDouble(Pz(),3,2));
  dummy.Append(gInclude->FormatedChar(" E: ",4));
  dummy.Append(gInclude->FormatedDouble(E(),3,2));
  dummy.Append(gInclude->FormatedChar(" p: ",4));
  dummy.Append(gInclude->FormatedDouble(Mag(),3,2));
  dummy.Append(gInclude->FormatedChar(" eta: ",7));
  dummy.Append(gInclude->FormatedDouble(Eta(),2,2));
  dummy.Append(gInclude->FormatedChar(" phi: ",7));
  dummy.Append(gInclude->FormatedDouble(Phi(),2,2));
  dummy.Append(gInclude->FormatedChar(" pt: ",5));
  dummy.Append(gInclude->FormatedDouble(Pt(),3,2));
  dummy.Append(gInclude->FormatedChar(" produced at: ",14));
  dummy.Append(gInclude->FormatedInt(fProducedAt,3,0," "));

  if ( fMCJet != 0 ) {
    dummy.Append(gInclude->FormatedChar(" mcjet: ",8));
    dummy.Append(gInclude->FormatedInt(fMCJet->GetID(),3,0," "));
  }
  if ( fMuon != 0 ) {
    dummy.Append(gInclude->FormatedChar(" muon: ",8));
    dummy.Append(gInclude->FormatedInt(fMuon->GetID(),3,0," "));
  }
  if ( fMCMuon != 0 ) {
    dummy.Append(gInclude->FormatedChar(" gmuon mc muon: ",17));
    dummy.Append(gInclude->FormatedInt(fMCMuon->GetFMCKINID(),3,0," "));
  }
  if ( fMuonBQuark != 0 ) {
    dummy.Append(gInclude->FormatedChar(" b quark: ",11));
    dummy.Append(gInclude->FormatedInt(fMuonBQuark->GetFMCKINID(),3,0," "));
  }
  if ( fMuonDirectParent != 0 ) {
    dummy.Append(gInclude->FormatedChar(" direct parent: ",17));
    dummy.Append(gInclude->FormatedInt(fMuonDirectParent->GetFMCKINID(),3,0," "));
  }
  if ( fMother != 0 ) {
    dummy.Append(gInclude->FormatedChar(" mother: ",10));
    dummy.Append(gInclude->FormatedInt(fMother->GetFMCKINID(),3,0," "));
  }

  if ( fMCMuonType == kMCChosenForwardMuon ) {
    dummy.Append (" chosen true forward muon");
  }
  if ( fMCMuonType == kMCChosenBarrelMuon ) {
    dummy.Append (" chosen true barrel muon");
  }
  if ( fMCMuonType == kMCChosenRearMuon ) {
    dummy.Append (" chosen true rear muon");
  }

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GMC::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMC::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GMC::SetChosenMCMuon() {
  //
  // flag MC muon to be chosen MC muon
  if ( gDebug ) cout << endl << "GMC::SetChosenMCMuon called" << endl << endl;

  if ( fMCMuonType == kMCForwardMuon )
    fMCMuonType = kMCChosenForwardMuon;
  else if ( fMCMuonType == kMCBarrelMuon )
    fMCMuonType = kMCChosenBarrelMuon;
  else if ( fMCMuonType == kMCRearMuon )
    fMCMuonType = kMCChosenRearMuon;

  return kTRUE;

}
