//
// GTracks.h
//
// $Author: meyer $
// $Date: 2005/06/14 13:41:12 $
// $Revision: 1.18 $
//

#ifndef GUT_GTracks
#define GUT_GTracks

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif
#ifndef ROOT_TRandom
#include <TRandom.h>
#endif

class TFile;
//class TRandom;

class GTracks : public GPhysObj {

 private:

  Bool_t          fMultiplicityCut;             // flag for multiplicity cut
  Bool_t          fVertexCut;                   // flag for cut on maximal vertex tracks
  Bool_t          fMinVertexCut;                // flag for cut on minimal vertex tracks
  Bool_t          fTotalOvVertexCut;            // flag for cut on total over vertex tracks

  TClonesArray   *fTracks;                      // track array
  Int_t           fNTracks;                     // counter for tracks clonesarray
  Int_t           fNCTDTracks;                  // counter for ctd only tracks
  Int_t           fNREGTracks;                  // counter for regular tracks
  Int_t           fNZTTTracks;                  // counter for ZTT tracks
  Int_t           fNVertexTracks;               // counter for vertex tracks
  Double_t        fFakeEventWeight;              // sum of fake weights of all tracks
  Int_t           fFakeID;                       // trackID of chosen fake muon candidate

  TH1D           *fGeneralN;                    // number of tracks
  TH1D           *fGeneralN_uncut;              // uncut number of tracks
  TH1D           *fGeneralNVertex;              // number of vertex tracks
  TH1D           *fGeneralNVertex_uncut;        // uncut number of vertex tracks
  TH1D           *fGeneralNTotalOvVertex;       // total over vertex tracks
  TH1D           *fGeneralNTotalOvVertex_uncut; // uncut total over vertex tracks

  TH1D  *fTrackAllPt;                           // pt distribution of all tracks
  TH1D  *fTrackAllEta_lowPt;                    // eta track for pt 0.7<pt<1.5 GeV
  TH1D  *fTrackAllPhi_lowPt;                    // phi track for pt 0.7<pt<1.5 GeV
  TH1D  *fTrackAllEta_highPt;                   // eta track for pt > 1.5
  TH1D  *fTrackAllPhi_highPt;                   // phi track for pt > 1.5
  TH2D  *fTrack2DAll_PtEta;                     // pt vs eta all tracks 
  TH1D  *fTrackAllPt_fake;                      // pt distribution of all tracks
  TH1D  *fTrackAllEta_lowPt_fake;               // eta track weighted with fake for pt 0.7<pt<1.5 GeV
  TH1D  *fTrackAllPhi_lowPt_fake;               // phi track weighted with fake for pt 0.7<pt<1.5 GeV
  TH1D  *fTrackAllEta_highPt_fake;              // eta track for pt > 1.5
  TH1D  *fTrackAllPhi_highPt_fake;              // phi track for pt > 1.5
  TH2D  *fTrack2DAll_PtEta_fake;                // pt vs eta all tracks 
  TH2D  *fTrack2DAll_PtEta_fake_diff;           // pt vs eta all tracks deviation from original fake distribution (MuonAll_pteta - fTrack2DAll_PtEta_fake)
  TH2D  *fFakeWeight_hist;                      // plot with fake weight/probabilities
  TFile *fFile;                                 // fake muon probability file

  TH1D           *fControlN;                    // control plot of number of tracks
  TH1D           *fControlN_uncut;              // uncut control plot of number of tracks
  TH1D           *fControlNVertex;              // control plot of number of vertex tracks
  TH1D           *fControlNVertex_uncut;        // uncut control plot of number of vertex tracks
  TH1D           *fControlNTotalOvVertex;       // total over vertex tracks
  TH1D           *fControlNTotalOvVertex_uncut; // uncut total over vertex tracks
  TH1D           *fControlRandomNumber; // random number generator

 public:
  GTracks();
  virtual ~GTracks();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();

  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();


  virtual Bool_t Reset();
  virtual Bool_t Do();
  virtual Bool_t Fill();
  virtual Bool_t FillHistos();
  virtual Bool_t ObjectsFillHistos();
  virtual Bool_t ObjectsFillGeneral(GTrack *track);
  virtual Bool_t Finalize();


  virtual GTrack* GetTrack(Int_t index);
  virtual GTrack* GetTrackByID(Int_t index);
  virtual GTrack* GetNormalTrackByVCTRHLID(Int_t vctrhl_id);
  virtual GTrack* GetZTTTrackByVCTRHLID(Int_t vctrhl_id);

  inline virtual Int_t GetNTracks() { return fNTracks; }

  virtual Bool_t CheckUsedSuperLayersCut(GTrack *track);
  virtual Bool_t CheckUsedHitsCut(GTrack *track);
  virtual Bool_t CheckUsedStereoHitsCut(GTrack *track);
  virtual Bool_t CheckZHCut(GTrack *track);
  virtual Bool_t CheckMVDHitsCut(GTrack *track);
  virtual Bool_t CheckAllCuts(GTrack *track);
  virtual Bool_t CheckMultiplicityCut();
  virtual Bool_t CheckVertexCut();
  virtual Bool_t CheckMinVertexCut();
  virtual Bool_t CheckTotalOvVertexCut();
  virtual Bool_t CheckFakeBackground(GTrack *track);
  virtual Bool_t ReadInHistogram(char*);
  virtual Bool_t ChooseFakeMuCand();
  virtual GTrack* GetFakeMuCand();


  inline virtual Bool_t   GetMultiplicityCut()  { return fMultiplicityCut;  }
  inline virtual Bool_t   GetVertexCut()        { return fVertexCut;        }
  inline virtual Bool_t   GetMinVertexCut()     { return fMinVertexCut;     }
  inline virtual Bool_t   GetTotalOvVertexCut() { return fTotalOvVertexCut; }
  inline virtual Double_t GetFakeEventWeight()  { return fFakeEventWeight;  }
  inline virtual TH1D*  GetTrackPt()              { return fTrackAllPt;        }
  inline virtual TH1D*  GetTrackEta_lowPt()       { return fTrackAllEta_lowPt; }
  inline virtual TH1D*  GetTrackPhi_lowPt()       { return fTrackAllPhi_lowPt; }
  inline virtual TH1D*  GetTrackEta_highPt()      { return fTrackAllEta_highPt;}
  inline virtual TH1D*  GetTrackPhi_highPt()      { return fTrackAllPhi_highPt;}
  inline virtual TH2D*  GetTrack2DAll_PtEta()     { return fTrack2DAll_PtEta;  }
  inline virtual TH2D*  GetTrack2DAll_PtEta_fake(){ return fTrack2DAll_PtEta_fake;  }

  virtual Bool_t GetAllCuts();

  TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GTracks,0) // Tracks Class for everything which is related only to tracks
};

R__EXTERN GTracks *gTracks;

#endif
