//
// GMC.h
//
// $Author: meyer $
// $Date: 2008/06/10 07:12:50 $
// $Revision: 1.14 $
//

#ifndef GUT_GMC
#define GUT_GMC

#include <iostream>

#ifndef ROOT_TLorentzVector
#include <TLorentzVector.h>
#endif

#ifndef GUT_EZMCType
#define GUT_EZMCType
enum EZMCType {
  kUnresolved,
  kDown,
  kAntiDown,
  kUp,
  kAntiUp,
  kStrange,
  kAntiStrange,
  kCharm,
  kAntiCharm,
  kBeauty,
  kAntiBeauty,
  kTop,
  kAntiTop,
  kElectron,
  kPositron,
  kMuon,
  kPi,
  kPiZero,
  kEta,
  kK,
  kKZero,
  kAntiKZero,
  kKShort,
  kKLong,
  kD,
  kDZero,
  kAntiDZero,
  kDS,
  kB,
  kBZero,
  kAntiBZero,
  kRho,
  kRhoZero,
  kOmega,
  kKStar,
  kKStarZero,
  kAntiKStarZero,
  kProton,
  kAntiProton,
  kLambda,
  kAntiLambda,
  kLambdaBZero,
  kAntiLambdaBZero,
  kDeltaTwoPlus,
  kDeltaTwoMinus,
  kAntiBSZero,
  kBSZero,
  kJpsi,
  kPsiprime,
  kCASCBP,
  kYPSI1S,
  kYPSI2S,
  kYPSI3S,
  kString,
  kCCUTwoMinus
};
#endif

#ifndef GUT_EZMCMuonType
#define GUT_EZMCMuonType
enum EZMCMuonType {
  kMCChosenForwardMuon,
  kMCChosenBarrelMuon,
  kMCChosenRearMuon,
  kMCMuon,
  kMCForwardMuon,
  kMCBarrelMuon,
  kMCRearMuon,
  kUnidentifiedMCMuon
};
#endif

class GMuon;
class GMCVertex;
class GJet;

class GMC : public TLorentzVector {

private:

  Int_t        fMCKINID;               // fmckin id
  Int_t        fPartID;                // particle type id
  EZMCType     fType;                  // particle type
  EZMCMuonType fMCMuonType;            // mc muon type
  Double_t     fCharge;                // charge
  Int_t        fMotherID;              // fmckin id of mother
  Int_t        fProducedAt;            // id of mc vertex particle is produced at
  Double_t     fImpact;                // impact parameter to primary mc vertex
  Double_t     fSignificance;          // significance of impact parameter to primary mc vertex
  Double_t     fImpact2D;              // 2D impact parameter to primary mc vertex
  Double_t     fSignificance2D;        // significance of 2D impact parameter to primary mc vertex

  Bool_t       fHeavyFlavourQuark;     // flag if particle is a heavy flavour quark

  GMuon       *fMuon;                  // associated muon from gmuon mc block
  GMC         *fMCMuon;                // associated mc muon from gmuon mc block in mc block
  GMC         *fMuonBQuark;            // associated b quark from gmuon mc block
  GMC         *fMuonBMeson;            // first b meson down the fmckin list
  GMC         *fMuonDirectParent;      // associated direct parent from gmuon mc block
  GMC         *fMother;                // pointer to mother if mother is filled in array

  GMCVertex   *fVertex;                // pointer to vertex

  Bool_t       fAssociatedWithNegativeFMCKINID; // flag if mc particle was associated to muon from gmuon with negative fmckin id

  GJet        *fMCJet;                 // associated MC jet
  GJet        *fMCJet2;                 // second associated MC jet
  GJet        *fMCPMJet;                 // associated parton level MC jet
  GJet        *fMCMuonJet;            // associated jet to muon (use bquark for evaluation)
  GJet        *fMCPMMuonJet;            // associated jet to muon (use bquark for evaluation)
public:
  GMC();
  GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E);
  GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E, GMuon *muon, GMC *bquark, GMC *directparent);
  //  GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E, Int_t motherid, Int_t producedat, Double_t impact, Double_t significance, Double_t impact2D, Double_t significance2D);
  GMC(Int_t fmckinid, Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t E, Int_t motherid, Int_t producedat, Double_t impact, Double_t impact2D);
  virtual ~GMC();

  inline virtual Int_t        GetFMCKINID()         { return fMCKINID;          }
  inline virtual Int_t        GetPartID()           { return fPartID;           }
  inline virtual EZMCType     GetType()             { return fType;             }
  inline virtual EZMCMuonType GetMCMuonType()       { return fMCMuonType;       }
  inline virtual Bool_t       GetChosenMCMuon() { if ( (fMCMuonType==kMCChosenForwardMuon)||(fMCMuonType==kMCChosenBarrelMuon)||(fMCMuonType==kMCChosenRearMuon) ) return kTRUE;
  else
    return kFALSE;
  }
  inline virtual Double_t     GetCharge()           { return fCharge;           }
  inline virtual Int_t        GetMotherID()         { return fMotherID;         }
  inline virtual Int_t        GetProducedAt()       { return fProducedAt;       }
  inline virtual Double_t     GetImpact()           { return fImpact;           }
  inline virtual Double_t     GetSignificance()     { return fSignificance;     }
  inline virtual Double_t     GetImpact2D()         { return fImpact2D;         }
  inline virtual Double_t     GetSignificance2D()   { return fSignificance2D;   }
  

  inline virtual GMuon*       GetMuon()             { return fMuon;             }
  inline virtual GMC*         GetMCMuon()           { return fMCMuon;             }
  inline virtual GMC*         GetMuonBQuark()       { return fMuonBQuark;       } // WARNING! The name is misleading: this routine returns a b quark OR a lighter quark, if no b quark was found (in events where the wrong end of the fragmentation string (2092) was saved.)
  inline virtual GMC*         GetMuonBMeson()       { return fMuonBMeson;       }
  inline virtual GMC*         GetMuonDirectParent() { return fMuonDirectParent; }
  inline virtual GMC*         GetMother()           { return fMother;           }
  inline virtual GMCVertex*   GetVertex()           { return fVertex;           }

  inline virtual void     SetFMCKINID(Int_t input)            { fMCKINID = input;          }
  inline virtual void     SetMotherID(Int_t input)            { fMotherID = input;         }
  inline virtual void     SetProducedAt(Int_t input)          { fProducedAt = input;       }
  inline virtual void     SetImpact(Double_t input)           { fImpact = input;           }
  inline virtual void     SetSignificance(Double_t input)     { fSignificance = input;     }
  inline virtual void     SetImpact2D(Double_t input)         { fImpact2D = input;         }
  inline virtual void     SetSignificance2D(Double_t input)   { fSignificance2D = input;   }
  inline virtual void     SetMCMuonType(EZMCMuonType input)   { fMCMuonType = input;       }

  inline virtual void     SetMuon(GMuon* input )                 { fMuon = input;                  }
  inline virtual void     SetMCMuon(GMC* input )                 { fMCMuon = input;                  }
  inline virtual void     SetMuonBQuark(GMC* input )             { fMuonBQuark = input; }
  inline virtual void     SetMuonBMeson(GMC* input )             { fMuonBMeson = input; }
  inline virtual void     SetMuonDirectParent(GMC* input )       { fMuonDirectParent = input;      }
  inline virtual void     SetMother(GMC* mother)                 { fMother = mother;               }
  inline virtual void     SetVertex(GMCVertex* vertex)           { fVertex   = vertex;             }

  inline virtual void     SetAssociatedMCJetToMCMuon(GJet *input){ fMCMuonJet = input; }
  inline virtual GJet*     GetAssociatedMCJetToMCMuon()           { return fMCMuonJet;  }

  inline virtual void     SetAssociatedMCPMJetToMCMuon(GJet *input){ fMCPMMuonJet = input; }
  inline virtual GJet*     GetAssociatedMCPMJetToMCMuon()           { return fMCPMMuonJet;  }
  
  virtual Bool_t CheckParticleType(Int_t partid);
  virtual TString ReturnParticleType();

  inline virtual Bool_t IsHeavyFlavourQuark()     { return fHeavyFlavourQuark;     }

  inline virtual void AssociatedWithNegativeFMCKINID(Bool_t input) { fAssociatedWithNegativeFMCKINID = input; }
  inline virtual Bool_t IsAssociatedWithNegativeFMCKINID() { return fAssociatedWithNegativeFMCKINID; }

  inline virtual void SetAssociatedMCJet(GJet *input) { fMCJet = input; }
  inline virtual GJet* GetAssociatedMCJet() { return fMCJet; }
  inline virtual void SetAssociatedMCPMJet(GJet *input) { fMCPMJet = input; }
  inline virtual GJet* GetAssociatedMCPMJet() { return fMCPMJet; }
  inline virtual void SetSecondAssociatedMCJetToMCMuon(GJet *input) {fMCJet2 = input;}
  inline virtual GJet* GetSecondAssociatedMCJetToMCMuon() { return fMCJet2;}
  virtual Bool_t SetChosenMCMuon();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GMC,0) // mc particle class
};

#endif
