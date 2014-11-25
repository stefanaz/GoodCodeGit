//
// GTrack.h
//
// $Author: meyer $
// $Date: 2005/08/30 11:17:05 $
// $Revision: 1.12 $
//

#ifndef GUT_GTrack
#define GUT_GTrack

#ifndef ROOT_TVector3
#include <TVector3.h>
#endif

#ifndef GUT_EZTrackType
#define GUT_EZTrackType
enum EZTrackType {
  kCTD,
  kREG,
  kZTT,
  kNothing
};
#endif

#ifndef GUT_EZMuonKinTrackType
#define GUT_EZMuonKinTrackType
enum EZMuonKinTrackType {
  kForwardMuonKin,
  kBarrelMuonKin,
  kRearMuonKin,
  kNoMuonKin
};
#endif

class TLorentzVector;

class GTrack : public TVector3 {

private:

  Int_t              fID;                                 // track id: if track is ctd or reg, id gives vctrhl id, if track is ztt, id gives zttrhl id
  Int_t              fID2;                                // track id 2: gives the respective id in other tracking block, 0 if no relation available
  EZTrackType        fType;                               // track type
  EZMuonKinTrackType fMuonKinType;                        // track type
  Double_t           fCharge;                             // charge of track
  Int_t              fVertexID;                           // ID of primary or secondary vertex, else -1
  Bool_t             fPrimaryVertex;                      // flag for primary vertex track
  Bool_t             fSecondaryVertex;                    // flag for secondary vertex track
  Int_t              fVertexFittedTrackID;                // ID of vertex fitted track
  Double_t           fEndPosX;                            // end position of swim in X
  Double_t           fEndPosY;                            // end position of swim in Y
  Double_t           fEndPosZ;                            // end position of swim in Z
  Int_t              fZbzyTimingHits;                     // number of z-by-timing hits
  Int_t              fAxialHits;                          // number of axial hits
  Int_t              fStereoHits;                         // number of stereo hits
  Int_t              fInnerLayer;                         // inner layer used by track
  Int_t              fOuterLayer;                         // outer layer used by track
  Double_t           fDedx;                               // dEdx from CTD
  Double_t           fDedxCorr;                           // corrected dEdx from CTD
  Int_t              fNDoF;                               // number of degree of freedom
  Double_t           fChi2;                               // chi2
  Double_t           fVChi2;                              // chi2 of vertex associated vertex fitted track
  Int_t              fNMVDRBarrelHits;                    // number of barrel MVD R hits
  Int_t              fNMVDZBarrelHits;                    // number of barrel MVD Z hits
  Int_t              fNMVDUWheelHits;                     // number of wheel MVD U hits
  Int_t              fNMVDVWheelHits;                     // number of wheel MVD V hits
  Double_t           fDedxMVD;                            // dEdx from MVD

                 // helix parameter
  Double_t           fW;                                  // helix parameter
  Double_t           fPhiZero;                            // helix parameter
  Double_t           fT;                                  // helix parameter
  Double_t           fDZero;                              // helix parameter
  Double_t           fZZero;                              // helix parameter
  Double_t           fCov_0;                              // helix parameter
  Double_t           fCov_1;                              // helix parameter
  Double_t           fCov_2;                              // helix parameter
  Double_t           fCov_3;                              // helix parameter
  Double_t           fCov_4;                              // helix parameter
  Double_t           fCov_5;                              // helix parameter
  Double_t           fCov_6;                              // helix parameter
  Double_t           fCov_7;                              // helix parameter
  Double_t           fCov_8;                              // helix parameter
  Double_t           fCov_9;                              // helix parameter
  Double_t           fCov_10;                             // helix parameter
  Double_t           fCov_11;                             // helix parameter
  Double_t           fCov_12;                             // helix parameter
  Double_t           fCov_13;                             // helix parameter
  Double_t           fCov_14;                             // helix parameter

  // cut flags
  Bool_t             fUsedSuperLayersCut;                 // flag for cut on used superlayers
  Bool_t             fUsedHitsCut;                        // flag for cut on used stereo + axial hits
  Bool_t             fUsedStereoHitsCut;                  // flag for cut on used stereo hits
  Bool_t             fZHCut;                              // flag for cut on z_h from helix parameters
  Bool_t             fMVDHitsCut;                         // flag for cut on number of mvdhits used
  Bool_t             fAllCuts;                            // flag for all cuts

  Double_t           fImpactParameter;                    // 3D impact parameter
  Double_t           f2DImpactParameter;                  // 2D impact parameter in XY
  Double_t           fImpactParameterSignificance;        // significance of 3D impact parameter
  Double_t           f2DImpactParameterSignificance;      // significance of 2D impact parameter
  Double_t           fFakeWeight;                         // track probability  of fake muon;
  Double_t           fFakeWeight_etalowpt;                // track probability  of fake muon; 0.75 < pt <1.5
  Double_t           fFakeWeight_etahighpt;               // track probability  of fake muon; pt > 1.5
  Double_t           fFakeWeight_cum;                     // track probability  of fake muon cumulative ;

public:
  GTrack();
  GTrack(Int_t id, Int_t id2, Int_t trktype, Double_t x, Double_t y, Double_t z, Double_t charge,
	 Int_t vertexid, Bool_t primary, Bool_t secondary,
	 Int_t vertexfittedtrackid, Double_t endposx, Double_t endposy, Double_t endposz, 
	 Int_t zbytiminghits, Int_t axialhits, Int_t stereohits,
	 Int_t innerlayer, Int_t outerlayer, Double_t dedx, Double_t dedxcorr,
	 Int_t ndof, Double_t chi2, Double_t vchi2, Int_t nbr, Int_t nbz, Int_t nwu, 
	 Int_t nwv, Double_t dedxmvd, Double_t w, Double_t phizero, Double_t t,
	 Double_t dzero, Double_t zzero);
  virtual ~GTrack();

  inline virtual Int_t              GetID()                  { return fID;                  }
  inline virtual Int_t              GetID2()                 { return fID2;                 }
  inline virtual EZTrackType        GetType()                { return fType;                }     
  inline virtual EZMuonKinTrackType GetMuonKinType()         { return fMuonKinType;         }     
  inline virtual Double_t           Charge()                 { return fCharge;              }
  inline virtual Int_t              GetVertexID()            { return fVertexID;            }
  inline virtual Bool_t             GetPrimaryVertex()       { return fPrimaryVertex;       }
  inline virtual Bool_t             GetSecondaryVertex()     { return fSecondaryVertex;     }
  inline virtual Int_t              GetVertexFittedTrackID() { return fVertexFittedTrackID; }
  inline virtual Double_t           GetEndPosX()             { return fEndPosX;             }
  inline virtual Double_t           GetEndPosY()             { return fEndPosY;             }
  inline virtual Double_t           GetEndPosZ()             { return fEndPosZ;             }
  inline virtual Int_t              GetZbzyTimingHits()      { return fZbzyTimingHits;      }
  inline virtual Int_t              GetAxialHits()           { return fAxialHits;           }
  inline virtual Int_t              GetStereoHits()          { return fStereoHits;          }
  inline virtual Int_t              GetNDoF()                { return fNDoF;                }
  inline virtual Int_t              GetInnerLayer()          { return fInnerLayer;          }
  inline virtual Int_t              GetOuterLayer()          { return fOuterLayer;          }
  inline virtual Double_t           GetDedx()                { return fDedx;                }
  inline virtual Double_t           GetDedxCorr()            { return fDedxCorr;            }
  inline virtual Double_t           GetChi2()                { return fChi2;                }
  inline virtual Double_t           GetVChi2()               { return fVChi2;               }
  inline virtual Int_t              GetMVDRBarrelHits()      { return fNMVDRBarrelHits;     }
  inline virtual Int_t              GetMVDZBarrelHits()      { return fNMVDZBarrelHits;     }
  inline virtual Int_t              GetMVDUWheelHits()       { return fNMVDUWheelHits;      }
  inline virtual Int_t              GetMVDVWheelHits()       { return fNMVDVWheelHits;      }
  inline virtual Int_t              GetMVDHits()             { return fNMVDRBarrelHits+
								 fNMVDZBarrelHits+
								 fNMVDUWheelHits+
								 fNMVDVWheelHits;}
  inline virtual Double_t           GetDedxMVD()             { return fDedxMVD;             }
  inline virtual Double_t           GetW()                   { return fW;                   }
  inline virtual Double_t           GetPhiZero()             { return fPhiZero;             }
  inline virtual Double_t           GetT()                   { return fT;                   }
  inline virtual Double_t           GetDZero()               { return fDZero;               }
  inline virtual Double_t           GetZZero()               { return fZZero;               }
  
  virtual Double_t                  GetCov(Int_t index);
  virtual void                      SetCov(Int_t index, Double_t value);

  inline virtual void               SetUsedSuperLayersCut(Bool_t input) { fUsedSuperLayersCut   = input; }
  inline virtual void               SetUsedHitsCut(Bool_t input)        { fUsedHitsCut          = input; }
  inline virtual void               SetUsedStereoHitsCut(Bool_t input)  { fUsedStereoHitsCut    = input; }
  inline virtual void               SetZHCut(Bool_t input)              { fZHCut                = input; }
  inline virtual void               SetMVDHitsCut(Bool_t input)         { fMVDHitsCut           = input; }
  inline virtual void               SetAllCuts(Bool_t input)            { fAllCuts              = input; }
  inline virtual void               SetFakeWeight(Double_t input)       { fFakeWeight           = input; }
  inline virtual void               SetFakeWeight_cum(Double_t input)   { fFakeWeight_cum       = input; }
  inline virtual void               SetFakeWeight_lowpt(Double_t input) { fFakeWeight_etalowpt  = input; }
  inline virtual void               SetFakeWeight_highpt(Double_t input){ fFakeWeight_etahighpt = input; }

  inline virtual Bool_t             GetUsedSuperLayersCut() { return fUsedSuperLayersCut;   }
  inline virtual Bool_t             GetUsedHitsCut()        { return fUsedHitsCut       ;   }
  inline virtual Bool_t             GetUsedStereoHitsCut()  { return fUsedStereoHitsCut ;   }
  inline virtual Bool_t             GetZHCut()              { return fZHCut             ;   }
  inline virtual Bool_t             GetMVDHitsCut()         { return fMVDHitsCut        ;   }
  inline virtual Bool_t             GetAllCuts()            { return fAllCuts           ;   }
  inline virtual Double_t           GetFakeWeight()         { return fFakeWeight        ;   }
  inline virtual Double_t           GetFakeWeight_cum()     { return fFakeWeight_cum    ;   }
  inline virtual Double_t           GetFakeWeight_lowpt()   { return fFakeWeight_etalowpt;  }
  inline virtual Double_t           GetFakeWeight_highpt()  { return fFakeWeight_etahighpt; }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  virtual Bool_t CalcImpactParameters(Double_t new_x_ref, Double_t new_x_ref_sigma, 
				      Double_t new_y_ref, Double_t new_y_ref_sigma, 
				      Double_t new_z_ref, Double_t new_z_ref_sigma,
				      TLorentzVector *reference);


  inline virtual Double_t        GetImpactParameter()               { return fImpactParameter;               }
  inline virtual Double_t        Get2DImpactParameter()             { return f2DImpactParameter;             }
  inline virtual Double_t        GetImpactParameterSignificance()   { return fImpactParameterSignificance;   }
  inline virtual Double_t        Get2DImpactParameterSignificance() { return f2DImpactParameterSignificance; }

  virtual Double_t Ranbw(Double_t r); 

  ClassDef(GTrack,0) // track class
};

#endif
