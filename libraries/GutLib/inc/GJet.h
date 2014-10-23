//
// GJet.h
//
// $Author: meyer $
// $Date: 2008/06/10 07:09:48 $
// $Revision: 1.23 $
//

#ifndef GUT_GJet
#define GUT_GJet

#ifndef ROOT_TLorentzVector
#include <TLorentzVector.h>
#endif

#ifndef GUT_EZJetType
#define GUT_EZJetType
enum EZJetType {
  kFirst,
  kSecond,
  kMCFirst,
  kMCSecond,
  kMCJet,
  kNormalJet
};
#endif

class GJet : public TLorentzVector {

private:

  EZJetType     fType;          // jet type, normal, first or second according to jet cut criteria

  Int_t         fID;            // jet id from orange block
  Bool_t        fEta;           // flag if jet fulfills cut on Eta
  Int_t         fMatched;       // counter if jet is associated to a muon and the match is the chosen one
  Double_t      fEtbreit;       // Et in breitframe not boosted back
  Bool_t        fUnmatched;     // flag if jet is not associated to a muon but the highest pt jet in event

  GJet         *fMCJet;         // associated jet in relation mc-rec in both directions mc->rec && rec->mc
  Double_t     fMJCosThetaStar;     // costhetastar of matched jet and other highest Pt jet  
  Int_t        fSecondJetID;     // id of second jet for costhetastar calculation
  Double_t     fMJCosThetaStar_xgamma; // xgamma calculated with jets used in fMJCosThetaStar calculation 
  Double_t     fMJCosThetaStar_MJets;  // mass of jets in costhstar calculation
  Double_t     fMJCosThetaStar_EtaJets; // average eta of jets in costhstar calculation

  public:
  GJet();
  GJet(Int_t id, Double_t et, Double_t eta, Double_t phi, Double_t m);
  GJet(Int_t id, Double_t et, Double_t eta, Double_t phi, Double_t m, Double_t etbreit);
  GJet(Int_t id, Double_t px, Double_t py, Double_t pz, Double_t e, EZJetType type);
  GJet(Int_t id, Double_t px, Double_t py, Double_t pz, Double_t e, EZJetType type, Double_t etbreit);
  virtual ~GJet();

  virtual Bool_t CheckEtaCut();

  virtual Double_t Et();
/*    virtual Double_t Etbreit(); */

  inline virtual void SetType(EZJetType type) { fType = type; }

  virtual void SetMatched(Bool_t input);
  inline virtual void SetUnmatched(Bool_t input)       { fUnmatched = input; }

  inline virtual Int_t GetID()               { return fID;   }
  inline virtual EZJetType GetType()         { return fType; }
  inline virtual Bool_t GetEtaCut()          { return fEta;  }
  inline virtual Double_t GetEtbreit()       { return fEtbreit;  }
  inline virtual Int_t GetMatched()          { return fMatched;  }
  inline virtual Bool_t GetUnmatched()       { return fUnmatched;  }
  inline virtual Bool_t GetSelected() { if ( (fType==kFirst) || (fType==kSecond) || (fType==kMCFirst) || (fType==kMCSecond) )
                                           return kTRUE;
                                        else
					  return kFALSE;
                                      }
  inline virtual Double_t GetMJCosThetaStar()    { return fMJCosThetaStar;}
  inline virtual Int_t    GetSecondJetID()       {return  fSecondJetID;   }
  inline virtual Double_t GetMJCosThetaStar_MJets() {return fMJCosThetaStar_MJets; }
  inline virtual Double_t GetMJCosThetaStar_EtaJets() {return fMJCosThetaStar_EtaJets;}
  inline virtual void SetMJCosThetaStar(Double_t input){ fMJCosThetaStar  = input; }
  inline virtual void SetSecondJetID(Int_t input)      { fSecondJetID     = input; }
  inline virtual void SetMJCosThetaStar_MJets(Double_t input) {fMJCosThetaStar_MJets = input; }
  inline virtual void SetMJCosThetaStar_EtaJets(Double_t input) {fMJCosThetaStar_EtaJets = input;}

  inline virtual void SetMJCosThetaStar_xgamma(Double_t input){ fMJCosThetaStar_xgamma = input;}
  inline virtual Double_t GetMJCosThetaStar_xgamma()  {return  fMJCosThetaStar_xgamma;}
  inline virtual void SetAssociatedMCJet(GJet *input) { fMCJet = input; }
  inline virtual GJet* GetAssociatedMCJet() { return fMCJet; }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GJet,0) // jet class
};

#endif
