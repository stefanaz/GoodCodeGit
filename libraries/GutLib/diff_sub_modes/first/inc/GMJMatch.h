//
// GMJMatch.h
//
// $Author: gutsche $
// $Date: 2004/11/03 14:30:49 $
// $Revision: 1.13 $
//

#ifndef GUT_GMJMatch
#define GUT_GMJMatch

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class GJet;
class GMuon;
class TString;

#ifndef GUT_EZMJMatchType
#define GUT_EZMJMatchType
enum EZMJMatchType {
  kGood,
  kChosen,
  kNormalMatch
};
#endif

class GMJMatch : public TObject {

private:

  EZMJMatchType fType;            // type of jet-muon match

  GJet        *fJet;              // pointer to jet belonging to this match
  GMuon       *fMuon;             // pointer to muon belonging to this match
  
  Double_t     fDeltaR;           // discriminant delta r = sqrt(delta-eta^2+delta-phi^2)
  Double_t     fDeltaPhi;         // difference in phi between jet and muon (always positive)
  Double_t     fDeltaEta;         // difference in eta between jet and muon (always positive)
  Double_t     fDeltaTheta;       // difference in theta between jet and muon (always positive)
  Double_t     fPtRel;            // relative transverse momentum of muon to jet
  Double_t     fEtJetMinusPtMu;   // JetEt - MuonPt
  Double_t     fPtRelJetMinMu;    // relative transverse momentum of muon to (jet-muon)
  Double_t     fDeltaRJetMinMu  ; // mu - jet delta r
  Double_t     fMuMinusJetPt;     // mu - jet p_t

  Bool_t       fMuonAllCuts;      // muon of match fulfills all cuts
  Bool_t       fJetCritCuts;      // event fulfills jet criteria cuts
  Bool_t       fJetPtCut;         // jet of muon fulfills p_t cut
  Bool_t       fMuMinusJetPtCut;  // match fulfills cut on p_t of mu-jet
  Bool_t       fPtRelCut;         // match fulfills cut on PtRel (upper and lower bound)
  Bool_t       fAllCuts;          // match fulfills all cuts

  
public:
  GMJMatch(GMuon *muon, GJet *jet);
  virtual ~GMJMatch();

  virtual Bool_t Calculate();

  inline virtual GJet*    GetJet()               { return fJet;           }
  inline virtual GMuon*   GetMuon()              { return fMuon;          }
  inline virtual Double_t GetDeltaR()            { return fDeltaR;        }
  inline virtual Double_t GetDeltaPhi()          { return fDeltaPhi;      }
  inline virtual Double_t GetDeltaEta()          { return fDeltaEta;      }
  inline virtual Double_t GetDeltaTheta()        { return fDeltaTheta;    }
  inline virtual Double_t GetPtRel()             { return fPtRel;         }
  inline virtual Double_t GetPtRelJetMinMu()     { return fPtRelJetMinMu; }
  inline virtual Double_t GetDeltaRJetMinMu()    { return fDeltaRJetMinMu; }
  inline virtual Double_t GetMuMinusJetPt()      { return fMuMinusJetPt;  }

  inline virtual void SetMuonAllCuts(Bool_t input)     { fMuonAllCuts     = input; }
  inline virtual void SetJetCritCuts(Bool_t input)     { fJetCritCuts     = input; }
  inline virtual void SetJetPtCut(Bool_t input)        { fJetPtCut        = input; }
  inline virtual void SetMuMinusJetPtCut(Bool_t input) { fMuMinusJetPtCut = input; }
  inline virtual void SetPtRelCut(Bool_t input)        { fPtRelCut        = input; }
  inline virtual void SetAllCuts(Bool_t input)         { fAllCuts         = input; }
  inline virtual void SetType(EZMJMatchType type)      { fType            = type;  }

  inline virtual Bool_t        GetMuonAllCuts()     { return fMuonAllCuts;     }
  inline virtual Bool_t        GetJetCritCuts()     { return fJetCritCuts;     }
  inline virtual Bool_t        GetJetPtCut()        { return fJetPtCut;        }
  inline virtual Bool_t        GetMuMinusJetPtCut() { return fMuMinusJetPtCut; }
  inline virtual Bool_t        GetPtRelCut()        { return fPtRelCut;        }
  inline virtual Bool_t        GetAllCuts()         { return fAllCuts;         }
  inline virtual EZMJMatchType GetType()            { return fType;            }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GMJMatch,0) // muon-jet match class
};

#endif
