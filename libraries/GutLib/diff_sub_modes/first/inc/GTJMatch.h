//
// GTJMatch.h
//
// $Author: meyer $
// $Date: 2008/06/10 07:21:34 $
// $Revision: 1.3 $
//

#ifndef GUT_GTJMatch
#define GUT_GTJMatch

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class GJet;
class GTrack;
class TString;

#ifndef GUT_EZTJMatchType
#define GUT_EZTJMatchType
enum EZTJMatchType {
  kGoodTrackMatch,
  kNormalTrackMatch
};
#endif

class GTJMatch : public TObject {

private:

  EZTJMatchType fType;              // type of jet-track match

  GJet        *fJet;                // pointer to jet belonging to this match
  GTrack      *fTrack;              // pointer to track belonging to this match
  
  Double_t     fDeltaR;             // discriminant delta r = sqrt(delta-eta^2+delta-phi^2)
  Double_t     fDeltaPhi;           // difference in phi between jet and muon (always positive)
  Double_t     fDeltaEta;           // difference in eta between jet and muon (always positive)
  Double_t     fDeltaTheta;         // difference in theta between jet and muon (always positive)
  Double_t     fPtRel;              // relative transverse momentum of track to jet
  Double_t     fPtRelJetMinTrack;   // relative transverse momentum of track to (jet-track)
  Double_t     fTrackMinusJetPt;    // track - jet p_t
  Double_t     fTJCosThetaStar;     // costhetastar for TJMatched jets
  Int_t        fTJCosThetaStarSecJetID; // id of second jet for calculation 
  Double_t     fTJCosThetaStarXgamma; // xgamma calculated from these jets
  Bool_t       fTrackAllCuts;       // track of match fulfills all cuts
  Bool_t       fTrackMuonKinCuts;   // track fulfills muon kinematics cuts
  Bool_t       fJetCritCuts;        // event fulfills jet criteria cuts
  Bool_t       fJetPtCut;           // jet of muon fulfills p_t cut
  Bool_t       fTrackMinusJetPtCut; // match fulfills cut on p_t of track-jet
  Bool_t       fAllCuts;            // match fulfills all cuts
  Double_t     fTJCosThetaStar_EtaJets; // average eta from jets in costhetastar calculation
  Double_t     fTJCosThetaStar_MJets;   // mass of jets in costhetastar calculation
  

public:
  GTJMatch(GTrack *track, GJet *jet);
  virtual ~GTJMatch();

  virtual Bool_t Calculate();

  inline virtual GJet*    GetJet()               { return fJet;              }
  inline virtual GTrack*  GetTrack()             { return fTrack;            }
  inline virtual Double_t GetDeltaR()            { return fDeltaR;           }
  inline virtual Double_t GetDeltaPhi()          { return fDeltaPhi;         }
  inline virtual Double_t GetDeltaEta()          { return fDeltaEta;         }
  inline virtual Double_t GetDeltaTheta()        { return fDeltaTheta;       }
  inline virtual Double_t GetPtRel()             { return fPtRel;            }
  inline virtual Double_t GetPtRelJetMinTrack()  { return fPtRelJetMinTrack; }
  inline virtual Double_t GetTrackMinusJetPt()   { return fTrackMinusJetPt;  }

  inline virtual void SetTrackAllCuts(Bool_t input)       { fTrackAllCuts       = input; }
  inline virtual void SetJetCritCuts(Bool_t input)        { fJetCritCuts        = input; }
  inline virtual void SetJetPtCut(Bool_t input)           { fJetPtCut           = input; }
  inline virtual void SetTrackMuonKinCuts(Bool_t input)   { fTrackMuonKinCuts   = input; }
  inline virtual void SetTrackMinusJetPtCut(Bool_t input) { fTrackMinusJetPtCut = input; }
  inline virtual void SetAllCuts(Bool_t input)            { fAllCuts            = input; }
  inline virtual void SetType(EZTJMatchType type)         { fType               = type;  }
  inline virtual void SetTJCosThetaStar(Double_t input)   {fTJCosThetaStar = input;      } 
  inline virtual void SetSecondJetID(Int_t input)      {fTJCosThetaStarSecJetID = input;}
  inline virtual void SetTJCosThetaStar_xgamma(Double_t input) {fTJCosThetaStarXgamma = input;}
  inline virtual void SetTJCosThetaStar_EtaJets(Double_t input) {fTJCosThetaStar_EtaJets = input;}
  inline virtual void SetTJCosThetaStar_MJets(Double_t input) {fTJCosThetaStar_MJets = input;}
  inline virtual Double_t GetTJCosThetaStar()                   {return fTJCosThetaStar;      } 
  inline virtual Int_t GetSecondJetID()                      {return fTJCosThetaStarSecJetID;}
  inline virtual Double_t GetTJCosThetaStar_xgamma()            {return fTJCosThetaStarXgamma;}
  inline virtual Double_t GetTJCosThetaStar_MJets()            {return fTJCosThetaStar_MJets;}
  inline virtual Double_t GetTJCosThetaStar_EtaJets()            {return fTJCosThetaStar_EtaJets;}





  inline virtual Bool_t        GetTrackAllCuts()       { return fTrackAllCuts;       }
  inline virtual Bool_t        GetJetCritCuts()        { return fJetCritCuts;        }
  inline virtual Bool_t        GetJetPtCut()           { return fJetPtCut;           }
  inline virtual Bool_t        GetTrackMuonKinCuts()   { return fTrackMuonKinCuts;   }
  inline virtual Bool_t        GetTrackMinusJetPtCut() { return fTrackMinusJetPtCut; }
  inline virtual Bool_t        GetAllCuts()            { return fAllCuts;            }
  inline virtual EZTJMatchType GetType()               { return fType;               }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GTJMatch,0) // track-jet match class
};

#endif
