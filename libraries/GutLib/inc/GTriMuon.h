//
// GTriMuon.h
//
// $Author: dbot $
// $Date: 2010/06/10 08:01:31 $
// $Revision: 1.00 $
//

#ifndef GUT_GTriMuon
#define GUT_GTriMuon

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class GMuon;
class TString;

#ifndef GUT_EZTriMuonType
#define GUT_EZTriMuonType
enum EZTriMuonType {
  kGoodTriMuon,
  kChosenTriMuon,
  kNormalTriMuon,
  kMCTriMuon
};
#endif

#ifndef GUT_EZTriMuonTriggerType
#define GUT_EZTriMuonTriggerType
enum EZTriMuonTriggerType {
  kTakeAll,
  kTakeTriMuon1,
  kTakeTriMuon2,
  kTakeTriMuon3,
  kTakeTriNone
};
#endif

class GMC;

class GTriMuon : public TObject {

private:

  EZTriMuonType        fType;                  // type of trimuon match
  EZTriMuonTriggerType fTriggerType;           // type of trimuon match

  GMuon              *fMuon1;                  // pointer to 1st muon
  GMuon              *fMuon2;                  // pointer to 2nd muon
  GMuon              *fMuon3;                  // pointer to 3rd muon

  GMC                *fMCMuon1;                // pointer to 1st mcmuon
  GMC                *fMCMuon2;                // pointer to 2nd mcmuon
  GMC                *fMCMuon3;                // pointer to 3rd mcmuon
  
  Bool_t              fDifCharge;              // true if muons from trimuon have different charge

  Bool_t              fMuonsAllCuts;           // muons of trimuon fulfill all muon cuts
  Bool_t              fMuonsMVCuts;            // muons of trimuon fulfill MV muon cuts
  Bool_t              fInvMassCut;             // cut on invarant mass
  Bool_t              fSqSumIsolationCut;      // cut on sqsumisolation
  Bool_t              fDeltaRCut;              // cut on delta r
  Bool_t              fDeltaPhiCut;            // cut on delta phi
  Bool_t              fDeltaThetaCut;          // cut on delta theta
  Bool_t              fDeltaEtaCut;            // cut on delta eta
  Bool_t              fPtAsymetryCut;          // cut on pt asymetry of muons in trimuon pair
  Bool_t              fEtFractionHighCut;      // trimumass dependent cut on et fraction of muons in trimuon pair
  Bool_t              fEtFractionLowCut;       // cut on et fraction of muons in trimuon pair
  Bool_t              fDifChargeCut;           // cut on different charge of the two muons
  Bool_t              fCharmMCJpsiCut;         // cut rejecting muons from jpsis in ccbar MC
  Bool_t              fCharmMCPsiprimeCut;     // cut rejecting muons from psiprimes in ccbar MC
  Bool_t              fMCTriMuonHFLCut;        // cut true if trimuon is HFL, i.e. both mu's come from HFL
  Bool_t              fAllCuts;                // trimuon fulfills all cuts

  Double_t            fInvMass1;               // invariant mass of 1st muon pair
  Double_t            fInvMass2;               // invariant mass of 2nd muon pair
  Double_t            fInvMass3;               // invariant mass of 3rd muon pair
  Double_t            ftrimuPt;                // p_T of the trimuon
  Double_t            fDeltaR1;                // delta R of trimuon
  Double_t            fDeltaR2;                // delta R of trimuon
  Double_t            fDeltaR3;                // delta R of trimuon
  Double_t            fDeltaEta1;              // delta Eta of trimuon
  Double_t            fDeltaEta2;              // delta Eta of trimuon
  Double_t            fDeltaEta3;              // delta Eta of trimuon
  Double_t            fDeltaPhi1;              // delta phi of trimuon
  Double_t            fDeltaPhi2;              // delta phi of trimuon
  Double_t            fDeltaPhi3;              // delta phi of trimuon
  Double_t            fDeltaTheta1;            // delta theta of trimuon
  Double_t            fDeltaTheta2;            // delta theta of trimuon
  Double_t            fDeltaTheta3;            // delta theta of trimuon
  Double_t            fTriMuonPhi;             // phi of trimuon 
  Double_t            fTriMuonEta;             // eta of trimuon 
  Double_t            fPtAsymetry1;            // pt1-pt2/pt1+pt2 of trimuon
  Double_t            fPtAsymetry2;            // pt1-pt2/pt1+pt2 of trimuon
  Double_t            fPtAsymetry3;            // pt1-pt2/pt1+pt2 of trimuon
  Double_t            fEtFraction1;            // pt1+pt2/cal_et  of trimuon
  Double_t            fEtFraction2;            // pt1+pt2/cal_et  of trimuon
  Double_t            fEtFraction3;            // pt1+pt2/cal_et  of trimuon
  Double_t            fmuissum01;              // sum of isolation in DeltaR cone of 0.1 of the 2 muons in trimuon
  Double_t            fmuissum02;              // sum of isolation in DeltaR cone of 0.2 of the 2 muons in trimuon
  Double_t            fmuissum03;              // sum of isolation in DeltaR cone of 0.3 of the 2 muons in trimuon
  Double_t            fmuissum04;              // sum of isolation in DeltaR cone of 0.4 of the 2 muons in trimuon
  Double_t            fmuissum05;              // sum of isolation in DeltaR cone of 0.5 of the 2 muons in trimuon
  Double_t            fmuissum06;              // sum of isolation in DeltaR cone of 0.6 of the 2 muons in trimuon
  Double_t            fmuissum07;              // sum of isolation in DeltaR cone of 0.7 of the 2 muons in trimuon
  Double_t            fmuissum08;              // sum of isolation in DeltaR cone of 0.8 of the 2 muons in trimuon
  Double_t            fmuissum09;              // sum of isolation in DeltaR cone of 0.9 of the 2 muons in trimuon
  Double_t            fmuissum10;              // sum of isolation in DeltaR cone of 1.0 of the 2 muons in trimuon
  
  Double_t            fmuissqsum01;            // sqared sum of isolation in DeltaR cone of 0.1 of the 2 muons in trimuon
  Double_t            fmuissqsum02;            // sqared sum of isolation in DeltaR cone of 0.2 of the 2 muons in trimuon
  Double_t            fmuissqsum03;            // sqared sum of isolation in DeltaR cone of 0.3 of the 2 muons in trimuon
  Double_t            fmuissqsum04;            // sqared sum of isolation in DeltaR cone of 0.4 of the 2 muons in trimuon
  Double_t            fmuissqsum05;            // sqared sum of isolation in DeltaR cone of 0.5 of the 2 muons in trimuon
  Double_t            fmuissqsum06;            // sqared sum of isolation in DeltaR cone of 0.6 of the 2 muons in trimuon
  Double_t            fmuissqsum07;            // sqared sum of isolation in DeltaR cone of 0.7 of the 2 muons in trimuon
  Double_t            fmuissqsum08;            // sqared sum of isolation in DeltaR cone of 0.8 of the 2 muons in trimuon
  Double_t            fmuissqsum09;            // sqared sum of isolation in DeltaR cone of 0.9 of the 2 muons in trimuon
  Double_t            fmuissqsum10;            // sqared sum of isolation in DeltaR cone of 1.0 of the 2 muons in trimuon
  
public:
  GTriMuon(GMuon *muon1, GMuon *muon2, GMuon *muon3);
  GTriMuon(GMC *fMCMuon1, GMC *fMCMuon2, GMC *fMCMuon3);
  virtual ~GTriMuon();

  virtual Bool_t Calculate();
  virtual Bool_t Calculate(GMC *fMCMuon1, GMC *fMCMuon2, GMC *fMCMuon3);

  inline virtual GMuon*       GetMuon1()                                  { return fMuon1;              }
  inline virtual GMuon*       GetMuon2()                                  { return fMuon2;              }
  inline virtual GMuon*       GetMuon3()                                  { return fMuon3;              }

  inline virtual GMC*         GetMCMuon1()                                { return fMCMuon1;            }
  inline virtual GMC*         GetMCMuon2()                                { return fMCMuon2;            }
  inline virtual GMC*         GetMCMuon3()                                { return fMCMuon3;            }

  inline virtual void         SetMuonsAllCuts(Bool_t input)               { fMuonsAllCuts       = input; }
  inline virtual void         SetMuonsMVCuts(Bool_t input)                { fMuonsMVCuts        = input; }
  inline virtual void         SetInvMassCut(Bool_t input)                 { fInvMassCut         = input; }
  inline virtual void         SetSqSumIsolationCut(Bool_t input)          { fSqSumIsolationCut  = input; }
  inline virtual void         SetDeltaRCut(Bool_t input)                  { fDeltaRCut          = input; }
  inline virtual void         SetDeltaPhiCut(Bool_t input)                { fDeltaPhiCut        = input; }
  inline virtual void         SetDeltaThetaCut(Bool_t input)              { fDeltaThetaCut      = input; }
  inline virtual void         SetDeltaEtaCut(Bool_t input)                { fDeltaEtaCut        = input; }
  inline virtual void         SetPtAsymetryCut(Bool_t input)              { fPtAsymetryCut      = input; }
  inline virtual void         SetEtFractionHighCut(Bool_t input)          { fEtFractionHighCut  = input; }
  inline virtual void         SetEtFractionLowCut(Bool_t input)           { fEtFractionLowCut   = input; }
  inline virtual void         SetDifChargeCut(Bool_t input)               { fDifChargeCut       = input; }
  inline virtual void         SetCharmMCJpsiCut(Bool_t input)             { fCharmMCJpsiCut     = input; }
  inline virtual void         SetCharmMCPsiprimeCut(Bool_t input)         { fCharmMCPsiprimeCut = input; }
  inline virtual void         SetMCTriMuonHFLCut(Bool_t input)            { fMCTriMuonHFLCut    = input; }
  inline virtual void         SetAllCuts(Bool_t input)                    { fAllCuts            = input; }
  inline virtual void         SetType(EZTriMuonType type)                 { fType               = type;  }
  inline virtual void         SetTriggerType(EZTriMuonTriggerType type)   { fTriggerType        = type;  }

  inline virtual Bool_t       GetDifCharge()                              { return fDifCharge;          } 
  inline virtual Bool_t       GetMuonsAllCuts()                           { return fMuonsAllCuts;       }
  inline virtual Bool_t       GetMuonsMVCuts()                            { return fMuonsMVCuts;        }
  inline virtual Bool_t       GetInvMassCut()                             { return fInvMassCut;         }
  inline virtual Bool_t       GetSqSumIsolationCut()                      { return fSqSumIsolationCut;  }
  inline virtual Bool_t       GetDeltaRCut()                              { return fDeltaRCut;          }
  inline virtual Bool_t       GetDeltaPhiCut()                            { return fDeltaPhiCut;        }
  inline virtual Bool_t       GetDeltaThetaCut()                          { return fDeltaThetaCut;      }
  inline virtual Bool_t       GetDeltaEtaCut()                            { return fDeltaEtaCut;        }
  inline virtual Bool_t       GetPtAsymetryCut()                          { return fPtAsymetryCut;      }
  inline virtual Bool_t       GetEtFractionHighCut()                      { return fEtFractionHighCut;  }
  inline virtual Bool_t       GetEtFractionLowCut()                       { return fEtFractionLowCut;   }
  inline virtual Bool_t       GetDifChargeCut()                           { return fDifChargeCut;       }
  inline virtual Bool_t       GetCharmMCJpsiCut()                         { return fCharmMCJpsiCut;     }
  inline virtual Bool_t       GetCharmMCPsiprimeCut()                     { return fCharmMCPsiprimeCut; }
  inline virtual Bool_t       GetMCTriMuonHFLCut()                        { return fMCTriMuonHFLCut;    }
  inline virtual Bool_t       GetAllCuts()                                { return fAllCuts;            }

  inline virtual EZTriMuonType        GetType()                           { return fType;               }
  inline virtual EZTriMuonTriggerType GetTriggerType()                    { return fTriggerType;        }

  inline virtual Double_t     GetInvMass1()                               { return fInvMass1;           }
  inline virtual Double_t     GetInvMass2()                               { return fInvMass2;           }
  inline virtual Double_t     GetInvMass3()                               { return fInvMass3;           }
  inline virtual Double_t     GettrimuPt()                                { return ftrimuPt;            }
  inline virtual Double_t     GetDeltaR1()                                { return fDeltaR1;            }
  inline virtual Double_t     GetDeltaR2()                                { return fDeltaR2;            }
  inline virtual Double_t     GetDeltaR3()                                { return fDeltaR3;            }
  inline virtual Double_t     GetDeltaEta1()                              { return fDeltaEta1;          }
  inline virtual Double_t     GetDeltaEta2()                              { return fDeltaEta2;          }
  inline virtual Double_t     GetDeltaEta3()                              { return fDeltaEta3;          }
  inline virtual Double_t     GetDeltaPhi1()                              { return fDeltaPhi1;          }
  inline virtual Double_t     GetDeltaPhi2()                              { return fDeltaPhi2;          }
  inline virtual Double_t     GetDeltaPhi3()                              { return fDeltaPhi3;          }
  inline virtual Double_t     GetDeltaTheta1()                            { return fDeltaTheta1;        }
  inline virtual Double_t     GetDeltaTheta2()                            { return fDeltaTheta2;        }
  inline virtual Double_t     GetDeltaTheta3()                            { return fDeltaTheta3;        }
  inline virtual Double_t     GetPhi()                                    { return fTriMuonPhi;         }
  inline virtual Double_t     GetEta()                                    { return fTriMuonEta;         }
  inline virtual Double_t     GetPtAsymetry1()                            { return fPtAsymetry1;        }
  inline virtual Double_t     GetPtAsymetry2()                            { return fPtAsymetry2;        }
  inline virtual Double_t     GetPtAsymetry3()                            { return fPtAsymetry3;        }
  inline virtual Double_t     GetEtFraction1()                            { return fEtFraction1;        }
  inline virtual Double_t     GetEtFraction2()                            { return fEtFraction2;        }
  inline virtual Double_t     GetEtFraction3()                            { return fEtFraction3;        }

  inline virtual void         SetIsolationSum01(Double_t input01)         { fmuissum01 = input01;       }
  inline virtual void         SetIsolationSum02(Double_t input02)         { fmuissum02 = input02;       }
  inline virtual void         SetIsolationSum03(Double_t input03)         { fmuissum03 = input03;       }
  inline virtual void         SetIsolationSum04(Double_t input04)         { fmuissum04 = input04;       }
  inline virtual void         SetIsolationSum05(Double_t input05)         { fmuissum05 = input05;       }
  inline virtual void         SetIsolationSum06(Double_t input06)         { fmuissum06 = input06;       }
  inline virtual void         SetIsolationSum07(Double_t input07)         { fmuissum07 = input07;       }
  inline virtual void         SetIsolationSum08(Double_t input08)         { fmuissum08 = input08;       }
  inline virtual void         SetIsolationSum09(Double_t input09)         { fmuissum09 = input09;       }
  inline virtual void         SetIsolationSum10(Double_t input10)         { fmuissum10 = input10;       }

  inline virtual void         SetIsolationSqSum01(Double_t inputsq01)     { fmuissqsum01 = inputsq01;   }
  inline virtual void         SetIsolationSqSum02(Double_t inputsq02)     { fmuissqsum02 = inputsq02;   }
  inline virtual void         SetIsolationSqSum03(Double_t inputsq03)     { fmuissqsum03 = inputsq03;   }
  inline virtual void         SetIsolationSqSum04(Double_t inputsq04)     { fmuissqsum04 = inputsq04;   }
  inline virtual void         SetIsolationSqSum05(Double_t inputsq05)     { fmuissqsum05 = inputsq05;   }
  inline virtual void         SetIsolationSqSum06(Double_t inputsq06)     { fmuissqsum06 = inputsq06;   }
  inline virtual void         SetIsolationSqSum07(Double_t inputsq07)     { fmuissqsum07 = inputsq07;   }
  inline virtual void         SetIsolationSqSum08(Double_t inputsq08)     { fmuissqsum08 = inputsq08;   }
  inline virtual void         SetIsolationSqSum09(Double_t inputsq09)     { fmuissqsum09 = inputsq09;   }
  inline virtual void         SetIsolationSqSum10(Double_t inputsq10)     { fmuissqsum10 = inputsq10;   }

  inline virtual Double_t     GetIsolationSum01()                         { return fmuissum01;          }
  inline virtual Double_t     GetIsolationSum02()                         { return fmuissum02;          }
  inline virtual Double_t     GetIsolationSum03()                         { return fmuissum03;          }
  inline virtual Double_t     GetIsolationSum04()                         { return fmuissum04;          }
  inline virtual Double_t     GetIsolationSum05()                         { return fmuissum05;          }
  inline virtual Double_t     GetIsolationSum06()                         { return fmuissum06;          }
  inline virtual Double_t     GetIsolationSum07()                         { return fmuissum07;          }
  inline virtual Double_t     GetIsolationSum08()                         { return fmuissum08;          }
  inline virtual Double_t     GetIsolationSum09()                         { return fmuissum09;          }
  inline virtual Double_t     GetIsolationSum10()                         { return fmuissum10;          }

  inline virtual Double_t     GetIsolationSqSum01()                       { return fmuissqsum01;        }
  inline virtual Double_t     GetIsolationSqSum02()                       { return fmuissqsum02;        }
  inline virtual Double_t     GetIsolationSqSum03()                       { return fmuissqsum03;        }
  inline virtual Double_t     GetIsolationSqSum04()                       { return fmuissqsum04;        }
  inline virtual Double_t     GetIsolationSqSum05()                       { return fmuissqsum05;        }
  inline virtual Double_t     GetIsolationSqSum06()                       { return fmuissqsum06;        }
  inline virtual Double_t     GetIsolationSqSum07()                       { return fmuissqsum07;        }
  inline virtual Double_t     GetIsolationSqSum08()                       { return fmuissqsum08;        }
  inline virtual Double_t     GetIsolationSqSum09()                       { return fmuissqsum09;        }
  inline virtual Double_t     GetIsolationSqSum10()                       { return fmuissqsum10;        }

  virtual TString PrintMessage(TString option);
  virtual Bool_t  Print(TString option);

  ClassDef(GTriMuon,0) // trimuon class
};

#endif
