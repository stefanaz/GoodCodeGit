//
// GDIMuon.h
//
// $Author: ibloch $
// $Date: 2005/04/26 10:33:31 $
// $Revision: 1.14 $
//

#ifndef GUT_GDIMuon
#define GUT_GDIMuon

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class GMuon;
class TString;

#ifndef GUT_EZDIMuonType
#define GUT_EZDIMuonType
enum EZDIMuonType {
  kGoodDIMuon,
  kChosenDIMuon,
  kNormalDIMuon,
  kMCDIMuon
};
#endif

#ifndef GUT_EZDIMuonTriggerType
#define GUT_EZDIMuonTriggerType
enum EZDIMuonTriggerType {
  kTakeBoth,
  kTakeMuon1,
  kTakeMuon2,
  kTakeNone
};
#endif

class GMC;

class GDIMuon : public TObject {

private:

  EZDIMuonType        fType;                   // type of dimuon match
  EZDIMuonTriggerType fTriggerType;            // type of dimuon match

  GMuon              *fMuon1;                  // pointer to first muon
  GMuon              *fMuon2;                  // pointer to second muon

  GMC                *fMCMuon1;                // pointer to first mcmuon
  GMC                *fMCMuon2;                // pointer to second mcmuon
  
  Bool_t              fDifCharge;              // true if muons from dimuon have different charge

  Bool_t              fMuonsAllCuts;           // muons of dimuon fulfill all muon cuts
  Bool_t              fMuonsMVCuts;            // muons of dimuon fulfill MV muon cuts
  Bool_t              fInvMassCut;             // cut on invarant mass
  Bool_t              fSqSumIsolationCut;      // cut on sqsumisolation
  Bool_t              fDeltaRCut;              // cut on delta r
  Bool_t              fDeltaPhiCut;            // cut on delta phi
  Bool_t              fDeltaThetaCut;          // cut on delta theta
  Bool_t              fDeltaEtaCut;            // cut on delta eta
  Bool_t              fPtAsymetryCut;          // cut on pt asymetry of muons in dimuon pair
  Bool_t              fEtFractionHighCut;      // dimumass dependent cut on et fraction of muons in dimuon pair
  Bool_t              fEtFractionLowCut;       // cut on et fraction of muons in dimuon pair
  Bool_t              fDifChargeCut;           // cut on different charge of the two muons
  Bool_t              fCharmMCJpsiCut;         // cut rejecting muons from jpsis in ccbar MC
  Bool_t              fCharmMCPsiprimeCut;     // cut rejecting muons from psiprimes in ccbar MC
  Bool_t              fMCDIMuonHFLCut;         // cut true if dimuon is HFL, i.e. both mu's come from HFL
  Bool_t              fAllCuts;                // dimuon fulfills all cuts

  Double_t            fInvMass;                // invariant mass of dimuon
  Double_t            fdimuPt;                 // p_T of the dimuon
  Double_t            fDeltaR;                 // delta R of diumuon
  Double_t            fDeltaEta;               // delta Eta of dimuon
  Double_t            fDeltaPhi;               // delta phi of dimuon
  Double_t            fDeltaTheta;             // delta theta of dimuon
  Double_t            fDimuonPhi;              //  phi of dimuon 
  Double_t            fDimuonEta;              //  eta of dimuon 
  Double_t            fPtAsymetry;             // pt1-pt2/pt1+pt2 of dimuon
  Double_t            fEtFraction;             // pt1+pt2/cal_et of dimuon

  Double_t            fmuissum01;              // sum of isolation in DeltaR cone of 0.1 of the 2 muons in dimuon
  Double_t            fmuissum02;              // sum of isolation in DeltaR cone of 0.2 of the 2 muons in dimuon
  Double_t            fmuissum03;              // sum of isolation in DeltaR cone of 0.3 of the 2 muons in dimuon
  Double_t            fmuissum04;              // sum of isolation in DeltaR cone of 0.4 of the 2 muons in dimuon
  Double_t            fmuissum05;              // sum of isolation in DeltaR cone of 0.5 of the 2 muons in dimuon
  Double_t            fmuissum06;              // sum of isolation in DeltaR cone of 0.6 of the 2 muons in dimuon
  Double_t            fmuissum07;              // sum of isolation in DeltaR cone of 0.7 of the 2 muons in dimuon
  Double_t            fmuissum08;              // sum of isolation in DeltaR cone of 0.8 of the 2 muons in dimuon
  Double_t            fmuissum09;              // sum of isolation in DeltaR cone of 0.9 of the 2 muons in dimuon
  Double_t            fmuissum10;              // sum of isolation in DeltaR cone of 1.0 of the 2 muons in dimuon
  
  Double_t            fmuissqsum01;            // sqared sum of isolation in DeltaR cone of 0.1 of the 2 muons in dimuon
  Double_t            fmuissqsum02;            // sqared sum of isolation in DeltaR cone of 0.2 of the 2 muons in dimuon
  Double_t            fmuissqsum03;            // sqared sum of isolation in DeltaR cone of 0.3 of the 2 muons in dimuon
  Double_t            fmuissqsum04;            // sqared sum of isolation in DeltaR cone of 0.4 of the 2 muons in dimuon
  Double_t            fmuissqsum05;            // sqared sum of isolation in DeltaR cone of 0.5 of the 2 muons in dimuon
  Double_t            fmuissqsum06;            // sqared sum of isolation in DeltaR cone of 0.6 of the 2 muons in dimuon
  Double_t            fmuissqsum07;            // sqared sum of isolation in DeltaR cone of 0.7 of the 2 muons in dimuon
  Double_t            fmuissqsum08;            // sqared sum of isolation in DeltaR cone of 0.8 of the 2 muons in dimuon
  Double_t            fmuissqsum09;            // sqared sum of isolation in DeltaR cone of 0.9 of the 2 muons in dimuon
  Double_t            fmuissqsum10;            // sqared sum of isolation in DeltaR cone of 1.0 of the 2 muons in dimuon
  
public:
  GDIMuon(GMuon *muon1, GMuon *muon2);
  GDIMuon(GMC *fMCMuon1, GMC *fMCMuon2);
  virtual ~GDIMuon();

  virtual Bool_t Calculate();
  virtual Bool_t Calculate(GMC *fMCMuon1, GMC *fMCMuon2);

  inline virtual GMuon*       GetMuon1()                      { return fMuon1;         }
  inline virtual GMuon*       GetMuon2()                      { return fMuon2;         }

  inline virtual GMC*       GetMCMuon1()                      { return fMCMuon1;         }
  inline virtual GMC*       GetMCMuon2()                      { return fMCMuon2;         }


  inline virtual void         SetMuonsAllCuts(Bool_t input)                 { fMuonsAllCuts       = input; }
  inline virtual void         SetMuonsMVCuts(Bool_t input)                  { fMuonsMVCuts        = input; }
  inline virtual void         SetInvMassCut(Bool_t input)                   { fInvMassCut         = input; }
  inline virtual void         SetSqSumIsolationCut(Bool_t input)            { fSqSumIsolationCut  = input; }
  inline virtual void         SetDeltaRCut(Bool_t input)                    { fDeltaRCut          = input; }
  inline virtual void         SetDeltaPhiCut(Bool_t input)                  { fDeltaPhiCut        = input; }
  inline virtual void         SetDeltaThetaCut(Bool_t input)                { fDeltaThetaCut      = input; }
  inline virtual void         SetDeltaEtaCut(Bool_t input)                  { fDeltaEtaCut        = input; }
  inline virtual void         SetPtAsymetryCut(Bool_t input)                { fPtAsymetryCut      = input; }
  inline virtual void         SetEtFractionHighCut(Bool_t input)            { fEtFractionHighCut  = input; }
  inline virtual void         SetEtFractionLowCut(Bool_t input)             { fEtFractionLowCut   = input; }
  inline virtual void         SetDifChargeCut(Bool_t input)                 { fDifChargeCut       = input; }
  inline virtual void         SetCharmMCJpsiCut(Bool_t input)               { fCharmMCJpsiCut     = input; }
  inline virtual void         SetCharmMCPsiprimeCut(Bool_t input)           { fCharmMCPsiprimeCut = input; }
  inline virtual void         SetMCDIMuonHFLCut(Bool_t input)               { fMCDIMuonHFLCut     = input; }
  inline virtual void         SetAllCuts(Bool_t input)                      { fAllCuts            = input; }
  inline virtual void         SetType(EZDIMuonType type)                    { fType               = type;  }
  inline virtual void         SetTriggerType(EZDIMuonTriggerType type)      { fTriggerType        = type;  }

  inline virtual Bool_t              GetDifCharge()                  { return fDifCharge;          }
  inline virtual Bool_t              GetMuonsAllCuts()               { return fMuonsAllCuts;       }
  inline virtual Bool_t              GetMuonsMVCuts()                { return fMuonsMVCuts;        }
  inline virtual Bool_t              GetInvMassCut()                 { return fInvMassCut;         }
  inline virtual Bool_t              GetSqSumIsolationCut()          { return fSqSumIsolationCut;  }
  inline virtual Bool_t              GetDeltaRCut()                  { return fDeltaRCut;          }
  inline virtual Bool_t              GetDeltaPhiCut()                { return fDeltaPhiCut;        }
  inline virtual Bool_t              GetDeltaThetaCut()              { return fDeltaThetaCut;      }
  inline virtual Bool_t              GetDeltaEtaCut()                { return fDeltaEtaCut;        }
  inline virtual Bool_t              GetPtAsymetryCut()              { return fPtAsymetryCut;      }
  inline virtual Bool_t              GetEtFractionHighCut()          { return fEtFractionHighCut;  }
  inline virtual Bool_t              GetEtFractionLowCut()           { return fEtFractionLowCut;   }
  inline virtual Bool_t              GetDifChargeCut()               { return fDifChargeCut;       }
  inline virtual Bool_t              GetCharmMCJpsiCut()             { return fCharmMCJpsiCut;     }
  inline virtual Bool_t              GetCharmMCPsiprimeCut()         { return fCharmMCPsiprimeCut; }
  inline virtual Bool_t              GetMCDIMuonHFLCut()             { return fMCDIMuonHFLCut;     }
  inline virtual Bool_t              GetAllCuts()                    { return fAllCuts;            }
  inline virtual EZDIMuonType        GetType()                       { return fType;               }
  inline virtual EZDIMuonTriggerType GetTriggerType()                { return fTriggerType;        } 

  inline virtual Double_t     GetInvMass()                    { return fInvMass;       }
  inline virtual Double_t     GetdimuPt()                     { return fdimuPt;        }
  inline virtual Double_t     GetDeltaR()                     { return fDeltaR;        }
  inline virtual Double_t     GetDeltaEta()                   { return fDeltaEta;      }
  inline virtual Double_t     GetDeltaPhi()                   { return fDeltaPhi;      }
  inline virtual Double_t     GetDeltaTheta()                 { return fDeltaTheta;    }
  inline virtual Double_t     GetPhi()                        { return fDimuonPhi;     }
  inline virtual Double_t     GetEta()                        { return fDimuonEta;     }
  inline virtual Double_t     GetPtAsymetry()                 { return fPtAsymetry;    }
  inline virtual Double_t     GetEtFraction()                 { return fEtFraction;    }

  inline virtual void       SetIsolationSum01(Double_t input01)               { fmuissum01 = input01;                                }
  inline virtual void       SetIsolationSum02(Double_t input02)               { fmuissum02 = input02;                                }
  inline virtual void       SetIsolationSum03(Double_t input03)               { fmuissum03 = input03;                                }
  inline virtual void       SetIsolationSum04(Double_t input04)               { fmuissum04 = input04;                                }
  inline virtual void       SetIsolationSum05(Double_t input05)               { fmuissum05 = input05;                                }
  inline virtual void       SetIsolationSum06(Double_t input06)               { fmuissum06 = input06;                                }
  inline virtual void       SetIsolationSum07(Double_t input07)               { fmuissum07 = input07;                                }
  inline virtual void       SetIsolationSum08(Double_t input08)               { fmuissum08 = input08;                                }
  inline virtual void       SetIsolationSum09(Double_t input09)               { fmuissum09 = input09;                                }
  inline virtual void       SetIsolationSum10(Double_t input10)               { fmuissum10 = input10;                                }

  inline virtual void       SetIsolationSqSum01(Double_t inputsq01)           { fmuissqsum01 = inputsq01;                            }
  inline virtual void       SetIsolationSqSum02(Double_t inputsq02)           { fmuissqsum02 = inputsq02;                            }
  inline virtual void       SetIsolationSqSum03(Double_t inputsq03)           { fmuissqsum03 = inputsq03;                            }
  inline virtual void       SetIsolationSqSum04(Double_t inputsq04)           { fmuissqsum04 = inputsq04;                            }
  inline virtual void       SetIsolationSqSum05(Double_t inputsq05)           { fmuissqsum05 = inputsq05;                            }
  inline virtual void       SetIsolationSqSum06(Double_t inputsq06)           { fmuissqsum06 = inputsq06;                            }
  inline virtual void       SetIsolationSqSum07(Double_t inputsq07)           { fmuissqsum07 = inputsq07;                            }
  inline virtual void       SetIsolationSqSum08(Double_t inputsq08)           { fmuissqsum08 = inputsq08;                            }
  inline virtual void       SetIsolationSqSum09(Double_t inputsq09)           { fmuissqsum09 = inputsq09;                            }
  inline virtual void       SetIsolationSqSum10(Double_t inputsq10)           { fmuissqsum10 = inputsq10;                            }

  inline virtual Double_t       GetIsolationSum01()                           {  return fmuissum01;                              }
  inline virtual Double_t       GetIsolationSum02()                           {  return fmuissum02;                              }
  inline virtual Double_t       GetIsolationSum03()                           {  return fmuissum03;                              }
  inline virtual Double_t       GetIsolationSum04()                           {  return fmuissum04;                              }
  inline virtual Double_t       GetIsolationSum05()                           {  return fmuissum05;                              }
  inline virtual Double_t       GetIsolationSum06()                           {  return fmuissum06;                              }
  inline virtual Double_t       GetIsolationSum07()                           {  return fmuissum07;                              }
  inline virtual Double_t       GetIsolationSum08()                           {  return fmuissum08;                              }
  inline virtual Double_t       GetIsolationSum09()                           {  return fmuissum09;                              }
  inline virtual Double_t       GetIsolationSum10()                           {  return fmuissum10;                              }

  inline virtual Double_t       GetIsolationSqSum01()                         {  return fmuissqsum01;                            }
  inline virtual Double_t       GetIsolationSqSum02()                         {  return fmuissqsum02;                            }
  inline virtual Double_t       GetIsolationSqSum03()                         {  return fmuissqsum03;                            }
  inline virtual Double_t       GetIsolationSqSum04()                         {  return fmuissqsum04;                            }
  inline virtual Double_t       GetIsolationSqSum05()                         {  return fmuissqsum05;                            }
  inline virtual Double_t       GetIsolationSqSum06()                         {  return fmuissqsum06;                            }
  inline virtual Double_t       GetIsolationSqSum07()                         {  return fmuissqsum07;                            }
  inline virtual Double_t       GetIsolationSqSum08()                         {  return fmuissqsum08;                            }
  inline virtual Double_t       GetIsolationSqSum09()                         {  return fmuissqsum09;                            }
  inline virtual Double_t       GetIsolationSqSum10()                         {  return fmuissqsum10;                            }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GDIMuon,0) // dimuon class
};

#endif
