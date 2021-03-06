//
// GMuon.h
//
// $Author: ibloch $
// $Date: 2005/10/12 16:49:19 $
// $Revision: 1.47 $
//

#ifndef GUT_GMuon
#define GUT_GMuon

#ifndef ROOT_TLorentzVector
#include <TLorentzVector.h>
#endif

#ifndef GUT_EZMuonType
#define GUT_EZMuonType
enum EZMuonType {
  kNowhere,
  kForward,
  kBarrel,
  kRear
};
#endif

class GTrack;
class GMC;

class GMuon : public TLorentzVector {

private:

  Int_t         fID;                                       // id
  EZMuonType    fType;                                     // location of muon hit
  Int_t         fQual;                                     // muon quality
  Double_t      fSpecialQual;                              // muon specialquality
  Double_t      fmuis01;                                   // isolation of muon in DeltaR cone of 0.1
  Double_t      fmuis02;                                   // isolation of muon in DeltaR cone of 0.2
  Double_t      fmuis03;                                   // isolation of muon in DeltaR cone of 0.3
  Double_t      fmuis04;                                   // isolation of muon in DeltaR cone of 0.4
  Double_t      fmuis05;                                   // isolation of muon in DeltaR cone of 0.5
  Double_t      fmuis06;                                   // isolation of muon in DeltaR cone of 0.6
  Double_t      fmuis07;                                   // isolation of muon in DeltaR cone of 0.7
  Double_t      fmuis08;                                   // isolation of muon in DeltaR cone of 0.8
  Double_t      fmuis09;                                   // isolation of muon in DeltaR cone of 0.9
  Double_t      fmuis10;                                   // isolation of muon in DeltaR cone of 1.0
  Double_t      fCharge;                                   // charge of muon
  Int_t         fTrackFlag;                                // tracking flag
  Int_t         fTrackID;                                  // track id 
  Int_t         fVctrhlID;                                 // id of vctrhl track
  Int_t         fVertexFlag;                               // vertex flag
  Int_t         fVertexID;                                 // vertex id
  Int_t         fGlomuID;                                  // internal index of muon found by glomu
  Int_t         fBrematID;                                 // internal index of muon found by bremat
  Int_t         fBacMatID;                                 // internal index of muon found by bacmat
  Int_t         fMuBacID;                                  // internal index of muon found by mubac
  Int_t         fMundof;                                   // ndf from MFRTZ or BREMAT
  Int_t         fMunphi;                                   // number of phi hits from MFRTZ
  Double_t      fMuz;                                      // z from MFRTZ
  Int_t         fMammaID;                                  // internal index of muon found by mamma
  Int_t         fMPMatchID;                                // internal index of muon found by mpmatch
  Int_t         fMufoID;                                   // internal index of muon found by mufo
  Int_t         fMipID;                                    // internal index of muon found by mip
  Int_t         fMvID;                                     // internal index of muon found by mv
  Int_t         fMuztid;                                   // Track ZTTRHL id 
  Double_t      fMuhac2;                                   // cal energy deposit in HAC2
  Bool_t        fGlomu;                                    // muon found by glomu
  Bool_t        fBremat;                                   // muon found by bremat
  Bool_t        fBrematInnerOuter;                         // muon found by bremat using inner and outer chambers
  Bool_t        fBacMat;                                   // muon found by bacmat
  Bool_t        fMuBac;                                    // muon found by mubac
  Bool_t        fMamma;                                    // muon found by mamma
  Bool_t        fMPMatch;                                  // muon found by mpmatch
  Bool_t        fMufo;                                     // muon found by mufo
  Bool_t        fMip;                                      // muon found by mip
  Bool_t        fMv;                                       // muon found by mv
  Bool_t        fAllExcpMV;                                // muon found by an or of all finders except MV
  Int_t         fZufoType;                                 // type of associated zufo
  Int_t         fZufoID;                                   // id of associated zufo
  Double_t      fCalProbMV;                                // MV CAL mip probability
  Int_t         fChamberFlag;                              // which chamber combination was used
  Int_t         fChamberID;                                // chamber id
  Double_t      fProb;                                     // matching probability (bremat: 4-dof matching)
  Double_t      fBacFlag;                                  // BAC flag
  Int_t         fBacID;                                    // BAC id
  Int_t         fJetFlag;                                  // flag of associated jet
  Int_t         fJetID;                                    // id of associated jet
  Double_t      fJetPt;                                    // ptrel from orange block
  Double_t      fJetDr;                                    // dr from orange block
  Int_t         fMCID;                                     // id of fmckin particle
  Int_t         fMuTrueFl;                                 // flag to decide if true muon / decay etc.
  Float_t       fMuTrueDecayDist;                          // true scalar distance from muon vertex to primary 
  Int_t         fFmufiCID;                                 // fmufi id from forward track muon associated track in c convention [0,x]
  Bool_t        fOK;                                       // ok flag
  Bool_t        fMatched;                                  // flag if muon is associated to a jet and the match is the chosen match
  Bool_t        fQualModified;                             // flag if muon quality has been corrected
  Double_t      fMuJetMass;                                // Mass of Jet with muon
  Double_t      fMuJetDR;                                  // Delta R of Jet respective to Muon
  Double_t      fMuJetEt;                                  // Et of Muon Jet
  Double_t      fImpactMuon2D;                             // 2D Impact parameter
  Double_t      fImpactSig;                                // Significance of Impact parameter
  Double_t      fImpactParameter;                          // impact parameter calculated by CalcImpactParameter in reference to defined vertex
  Double_t      fImpactParameterSignificance;              // significance of 3D impact parameter calculated by CalcImpactParameter in reference to defined vertex
  Double_t      f2DImpactParameter;                        // 2D impact parameter calculated by CalcImpactParameter in reference to defined vertex
  Double_t      f2DImpactParameterSignificance;            // significance of 2D impact parameter calculated by CalcImpactParameter in reference to defined vertex
  Double_t      f2DBeamSpotImpactParameter;                // 2D impact parameter calculated by CalcBeamSpotImpactParameter in reference to beamspot
  Double_t      f2DBeamSpotImpactParameterSignificance;    // significance of 2D impact parameter calculated by CalcBeamSpotImpactParameter in reference to beamspot
  Double_t      f2DTrueImpactParameter;                    // 2D impact parameter calculated by CalcTrueImpactParameter in reference to MC true vertex
  Double_t      f2DTrueImpactParameterSignificance;        // significance of 2D impact parameter calculated by CalcTrueImpactParameter in reference to MC true vertex
  Double_t      f2DMCBeamSpotImpactParameter;              // true 2D impact parameter calculated to nominal MC beamspot 
  Double_t      f2DMCBeamSpotImpactParameterSignificance;  // significance of true 2D impact parameter calculated to nominal MC beamspot 
  Double_t      fWeight;                                   // efficiency correction factor

  GTrack       *fTrack;                                    // reference to track
  GTrack       *fZTTTrack;                                 // reference to ztt track

  // cut flags
  Bool_t           fQualCut;                               // cut on quality
  Bool_t           fFinderCut;                             // cut on finder requirement
  Bool_t           fEtaCut;                                // cut on eta range
  Bool_t           fPtCut;                                 // cut on transverse momentum
  Bool_t           fPCut;                                  // cut on momentum
  Bool_t           fBrematCut;                             // specific cut for bremat
  Bool_t           fMPMatchCut;                            // specific cut for mpmatch
  Bool_t           fMUBACCut;                              // specific cut for mubac
  Bool_t           fForwardTrackMuonCut;                   // cut on forward muon specific track quality properties
  Bool_t           fBACFQualityCut;                        // cut on quality for forward muons only found by mubac
  Bool_t           fVcidLowCut;                            // cut on minimal vcid  
  Bool_t           fVcidUpCut;                             // cut on maximal vcid  
  Bool_t           fAllCuts;                               // flag for fullfillment of all cuts
  Bool_t           fForwardTrackMuon;                      // muon is forward track muon 
  Bool_t           fBACFMuon;                              // forward muon is only found by mubac
  Bool_t           fBest;                                  // flag if muon ist best ( highest probability )
  Bool_t           fMVCuts;                                // flag for being special MV muon for efficiency denominator
  Bool_t           fOnlyVertexFittedCut;                   // flag if muon is only reconstructed from vertex fitted track
  Bool_t           fTakeCut;                               // flag if muon passes muon chamber take list cut
  
  // links to mc
  GMC             *fMC;                                    // link to assoctiated mc particle
  GMC             *fMCQuark;                               // link to associated mc quark
  GMC             *fMCDirectParent;                        // link to associated mc direct parent

  // efficiency flag
  Bool_t           fEfficiencyReset;                       // reset efficiency to 1 if one MC efficiency in GMuonEfficiency is zero (MC does not contain data event of that type)

public:
  GMuon();
  GMuon(Int_t id, EZMuonType type,
	Int_t muqual, Int_t charge, 
	Double_t mupx, Double_t mupy, Double_t mupz, Double_t muperr,
	Int_t mutrfl, Int_t mutrid, Int_t muvcid, Int_t muztid,
	Int_t muvtxfl, Int_t muvtxid,
	Int_t muglomu, Int_t mubremat, Int_t mubacmat, Int_t mumubac, Int_t mumamma, Int_t mumpmat, Int_t mumufo, 
	Int_t mumip, Int_t mumv,  
	Int_t mucalfl, Float_t muhac2, Int_t muzufid, Double_t mupmip,
	Int_t muchfl, Int_t muchid, Double_t mupmat, 
	Double_t mubacfl, Int_t mubacid, Int_t munphi, 
	Int_t mujetfl, Int_t mujetid_a, Double_t mujetdr_a, Double_t mujetpt, Int_t mutruefl, Float_t mudecdist);
  virtual ~GMuon();

  virtual Bool_t CalcImpactParameter(Double_t new_x_ref, Double_t new_x_ref_sigma, 
				     Double_t new_y_ref, Double_t new_y_ref_sigma, 
				     Double_t new_z_ref, Double_t new_z_ref_sigma);
  virtual Bool_t CalcBeamSpotImpactParameter();
  virtual Bool_t CalcTrueImpactParameter();
  virtual Bool_t CalcMCBeamSpotImpactParameter();
  virtual Bool_t  AssociateJetByDeltaR();
 
  virtual TString PrintMessage(TString option);
  virtual Bool_t EvaluateFinders();
  virtual Bool_t Print(TString option);

  inline virtual Int_t      GetID()                                        { return fID;                                       }
  inline virtual EZMuonType GetType()                                      { return fType;                                     }
  inline virtual Int_t      GetQuality()                                   { return fQual;                                     }
  inline virtual Double_t   GetSpecialQuality()                            { return fSpecialQual;                              }
  inline virtual Bool_t     GetHasBeenQualModified()                       { return fQualModified;                             }
  inline virtual Double_t   GetCharge()                                    { return fCharge;                                   }
  inline virtual void       SetQuality(Int_t input)                        { fQual = input;                                    }
  inline virtual void       SetSpecialQuality(Double_t input)              { fSpecialQual = input;                             }
  inline virtual void       SetHasBeenQualModified(Bool_t input)           { fQualModified = input;                            }

  inline virtual void       SetBrematID(Int_t input)                       { fBrematID    = input;                             }
  inline virtual void       SetGlomuID(Int_t input)                        { fGlomuID     = input;                             }
  inline virtual void       SetChamberFlag(Int_t input)                    { fChamberFlag = input;                             }
  inline virtual void       SetBacMatID(Int_t input)                       { fBacMatID    = input;                             }   
  inline virtual void       SetMuBacID(Int_t input)                        { fMuBacID     = input;                             }
  inline virtual void       SetMPMatchID(Int_t input)                      { fMPMatchID   = input;                             }
  inline virtual void       SetMufoID(Int_t input)                         { fMufoID      = input;                             }
  inline virtual void       SetMammaID(Int_t input)                        { fMammaID     = input;                             }

  inline virtual void       SetIsolation01(Double_t input01)               { fmuis01 = input01;                                }
  inline virtual void       SetIsolation02(Double_t input02)               { fmuis02 = input02;                                }
  inline virtual void       SetIsolation03(Double_t input03)               { fmuis03 = input03;                                }
  inline virtual void       SetIsolation04(Double_t input04)               { fmuis04 = input04;                                }
  inline virtual void       SetIsolation05(Double_t input05)               { fmuis05 = input05;                                }
  inline virtual void       SetIsolation06(Double_t input06)               { fmuis06 = input06;                                }
  inline virtual void       SetIsolation07(Double_t input07)               { fmuis07 = input07;                                }
  inline virtual void       SetIsolation08(Double_t input08)               { fmuis08 = input08;                                }
  inline virtual void       SetIsolation09(Double_t input09)               { fmuis09 = input09;                                }
  inline virtual void       SetIsolation10(Double_t input10)               { fmuis10 = input10;                                }

  inline virtual Double_t   GetIsolation01()                               { return  fmuis01;                                  }
  inline virtual Double_t   GetIsolation02()                               { return  fmuis02;                                  }
  inline virtual Double_t   GetIsolation03()                               { return  fmuis03;                                  }
  inline virtual Double_t   GetIsolation04()                               { return  fmuis04;                                  }
  inline virtual Double_t   GetIsolation05()                               { return  fmuis05;                                  }
  inline virtual Double_t   GetIsolation06()                               { return  fmuis06;                                  }
  inline virtual Double_t   GetIsolation07()                               { return  fmuis07;                                  }
  inline virtual Double_t   GetIsolation08()                               { return  fmuis08;                                  }
  inline virtual Double_t   GetIsolation09()                               { return  fmuis09;                                  }
  inline virtual Double_t   GetIsolation10()                               { return  fmuis10;                                  }

  inline virtual Int_t      GetTrackFlag()                                 { return fTrackFlag;                                }
  inline virtual Int_t      GetTrackID()                                   { return fTrackID;                                  }
  inline virtual Int_t      GetVctrhlID()                                  { return fVctrhlID;                                 }
  inline virtual Int_t      GetVertexFlag()                                { return fVertexFlag;                               }
  inline virtual Int_t      GetVertexID()                                  { return fVertexID;                                 }
  inline virtual Int_t      GetGlomuID()                                   { return fGlomuID;                                  } 
  inline virtual Int_t      GetBrematID()                                  { return fBrematID;                                 } 
  inline virtual Int_t      GetBacMatID()                                  { return fBacMatID;                                 }
  inline virtual Int_t      GetMuBacID()                                   { return fMuBacID;                                  } 
  inline virtual Int_t      GetMundof()                                    { return fMundof;                                   } 
  inline virtual Int_t      GetMunphi()                                    { return fMunphi;                                   }
  inline virtual Double_t   GetMuz()                                       { return fMuz;                                      }
  inline virtual Int_t      GetMammaID()                                   { return fMammaID;                                  } 
  inline virtual Int_t      GetMPMatchID()                                 { return fMPMatchID;                                } 
  inline virtual Int_t      GetMufoID()                                    { return fMufoID;                                   } 
  inline virtual Int_t      GetMipID()                                     { return fMipID;                                    } 
  inline virtual Int_t      GetMvID()                                      { return fMvID;                                     } 
  inline virtual Int_t      Getmuztid()                                    { return fMuztid;                                   }      
  inline virtual Double_t   Getmuhac2()                                    { return fMuhac2;                                   }
  inline virtual Bool_t     GetGlomu()                                     { return fGlomu;                                    } 
  inline virtual Bool_t     GetBremat()                                    { return fBremat;                                   } 
  inline virtual Bool_t     GetBrematInnerOuter()                          { return fBrematInnerOuter;                         } 
  inline virtual Bool_t     GetBacMat()                                    { return fBacMat;                                   }
  inline virtual Bool_t     GetMuBac()                                     { return fMuBac;                                    } 
  inline virtual Bool_t     GetMamma()                                     { return fMamma;                                    } 
  inline virtual Bool_t     GetMPMatch()                                   { return fMPMatch;                                  } 
  inline virtual Bool_t     GetMufo()                                      { return fMufo;                                     } 
  inline virtual Bool_t     GetMip()                                       { return fMip;                                      } 
  inline virtual Bool_t     GetMv()                                        { return fMv;                                       } 
  inline virtual Bool_t     GetAllExcpMv()                                 { return fAllExcpMV;                                } 
  inline virtual Int_t      GetZufoType()                                  { return fZufoType;                                 }
  inline virtual Int_t      GetZufoID()                                    { return fZufoID;                                   }
  inline virtual Double_t   GetCalProbMV()                                 { return fCalProbMV;                                }
  inline virtual Int_t      GetChamberFlag()                               { return fChamberFlag;                              }
  inline virtual Int_t      GetChamberID()                                 { return fChamberID;                                }
  inline virtual Double_t   GetProbability()                               { return fProb;                                     }
  inline virtual Double_t   GetBacFlag()                                   { return fBacFlag;                                  }
  inline virtual Int_t      GetBacID()                                     { return fBacID;                                    }
  inline virtual Int_t      GetJetFlag()                                   { return fJetFlag;                                  }
  inline virtual Int_t      GetJetID()                                     { return fJetID;                                    }
  inline virtual Double_t   GetJetPt()                                     { return fJetPt;                                    }
  inline virtual Double_t   GetJetDr()                                     { return fJetDr;                                    }
  inline virtual Int_t      GetFmufiCID()                                  { return fFmufiCID;                                 }
  inline virtual Int_t      GetMCID()                                      { return fMCID;                                     }
  inline virtual Int_t      GetMuTrueFl()                                  { return fMuTrueFl;                                 }
  inline virtual Float_t    GetMuTrueDecayDist()                           { return fMuTrueDecayDist;                          }
 
  inline virtual Double_t   GetMuJetMass()                                 { return fMuJetMass;                                }
  inline virtual Double_t   GetMuJetEt()                                   { return fMuJetEt;                                  }
  inline virtual Double_t   GetImpactMuon2D()                              { return fImpactMuon2D;                             }
  inline virtual Double_t   GetImpactSig()                                 { return fImpactSig;                                }
  inline virtual Double_t   GetImpactParameter()                           { return fImpactParameter;                          }
  inline virtual Double_t   GetImpactParameterSignificance()               { return fImpactParameterSignificance;              }
  inline virtual Double_t   Get2DImpactParameter()                         { return f2DImpactParameter;                        }
  inline virtual Double_t   Get2DImpactParameterSignificance()             { return f2DImpactParameterSignificance;            }
  inline virtual Double_t   Get2DBeamSpotImpactParameter()                 { return f2DBeamSpotImpactParameter;                }
  inline virtual Double_t   Get2DBeamSpotImpactParameterSignificance()     { return f2DBeamSpotImpactParameterSignificance;    }
  inline virtual Double_t   Get2DTrueImpactParameter()                     { return f2DTrueImpactParameter;                    }
  inline virtual Double_t   Get2DTrueImpactParameterSignificance()         { return f2DTrueImpactParameterSignificance;        }
  inline virtual Double_t   Get2DMCBeamSpotImpactParameter()               { return f2DMCBeamSpotImpactParameter;              }
  inline virtual Double_t   Get2DMCBeamSpotImpactParameterSignificance()   { return f2DMCBeamSpotImpactParameterSignificance;  }
  inline virtual Double_t   GetOriginalWeight()                            { return fWeight;                                   }
  virtual        Double_t   GetWeight(); 
  inline virtual GTrack*    GetTrack()                                     { return fTrack;                                    }
  inline virtual GTrack*    GetZTTTrack()                                  { return fZTTTrack;                                 }

  inline virtual Bool_t IsOK()                                             { return fOK;                                       }
  inline virtual Bool_t GetQualityCut()                                    { return fQualCut;                                  }
  inline virtual Bool_t GetFinderCut()                                     { return fFinderCut;                                }
  inline virtual Bool_t GetEtaCut()                                        { return fEtaCut;                                   }
  inline virtual Bool_t GetPtCut()                                         { return fPtCut;                                    }
  inline virtual Bool_t GetPCut()                                          { return fPCut;                                     }
  inline virtual Bool_t GetBrematCut()                                     { return fBrematCut;                                }
  inline virtual Bool_t GetMPMatchCut()                                    { return fMPMatchCut;                               }
  inline virtual Bool_t GetMUBACCut()                                      { return fMUBACCut;                                 }
  inline virtual Bool_t GetForwardTrackMuonCut()                           { return fForwardTrackMuonCut;                      }
  inline virtual Bool_t GetBACFQualityCut()                                { return fBACFQualityCut;                           }
  inline virtual Bool_t GetVcidLowCut()                                    { return fVcidLowCut;                               }
  inline virtual Bool_t GetVcidUpCut()                                     { return fVcidUpCut;                                }
  inline virtual Bool_t GetAllCuts()                                       { return fAllCuts;                                  }
  inline virtual Bool_t GetForwardTrackMuon()                              { return fForwardTrackMuon;                         }
  inline virtual Bool_t GetBACFMuon()                                      { return fBACFMuon;                                 }
  inline virtual Bool_t GetBest()                                          { return fBest;                                     }
  inline virtual Bool_t GetMVCuts()                                        { return fMVCuts;                                   }
  inline virtual Bool_t GetOnlyVertexFittedCut()                           { return fOnlyVertexFittedCut;                      }
  inline virtual Bool_t GetTakeCut()                                       { return fTakeCut;                                  }

  inline virtual GMC*   GetMC()                                            { return fMC;                                       }
  inline virtual GMC*   GetMCQuark()                                       { return fMCQuark;                                  }
  inline virtual GMC*   GetMCDirectParent()                                { return fMCDirectParent;                           }
  inline virtual void SetQualityCut(Bool_t input)                          { fQualCut             = input;                     }
  inline virtual void SetFinderCut(Bool_t input)                           { fFinderCut           = input;                     }
  inline virtual void SetEtaCut(Bool_t input)                              { fEtaCut              = input;                     }
  inline virtual void SetTakeCut(Bool_t input)                             { fTakeCut             = input;                     }
  inline virtual void SetPtCut(Bool_t input)                               { fPtCut               = input;                     }
  inline virtual void SetPCut(Bool_t input)                                { fPCut                = input;                     }
  inline virtual void SetBrematCut(Bool_t input)                           { fBrematCut           = input;                     }
  inline virtual void SetForwardTrackMuonCut(Bool_t input)                 { fForwardTrackMuonCut = input;                     }
  inline virtual void SetBACFQualityCut(Bool_t input)                      { fBACFQualityCut      = input;                     }
  inline virtual void SetVcidLowCut(Bool_t input)                          { fVcidLowCut          = input;                     }
  inline virtual void SetVcidUpCut(Bool_t input)                           { fVcidUpCut           = input;                     }
  inline virtual void SetMPMatchCut(Bool_t input)                          { fMPMatchCut          = input;                     }
  inline virtual void SetMUBACCut(Bool_t input)                            { fMUBACCut            = input;                     }
  inline virtual void SetAllCuts(Bool_t input)                             { fAllCuts             = input;                     }
  inline virtual void SetBest(Bool_t input)                                { fBest                = input;                     }
  inline virtual void SetMVCuts(Bool_t input)                              { fMVCuts              = input;                     }
  inline virtual void SetOnlyVertexFittedCut(Bool_t input)                 { fOnlyVertexFittedCut = input;                     }
  inline virtual void SetForwardTrackMuon(Bool_t input)                    { fForwardTrackMuon    = input;                     }
  inline virtual void SetBACFMuon(Bool_t input)                            { fBACFMuon            = input;                     }
  inline virtual void SetType(EZMuonType type)                             { fType                = type;                      }
  inline virtual void SetFmufiCID(Int_t input)                             { fFmufiCID            = input;                     }

  inline virtual void SetMC(GMC *input)                                    { fMC = input;                                      }
  inline virtual void SetMCQuark(GMC *input)                               { fMCQuark = input;                                 }
  inline virtual void SetMCDirectParent(GMC *input)                        { fMCDirectParent = input;                          }

  inline virtual Bool_t GetMatched()                                       { return fMatched;                                  }
  inline virtual void   SetMatched(Bool_t input)                           { fMatched = input;                                 }

  inline virtual void   SetWeight(Double_t input)                          { fWeight =  input;                                 }

  inline virtual void   SetEfficiencyReset(Bool_t input)                   { fEfficiencyReset = input;                         }
  inline virtual Bool_t GetEfficiencyReset()                               { return fEfficiencyReset;                          }

  ClassDef(GMuon,0) // muon class
};

#endif
