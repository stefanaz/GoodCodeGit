//
// GMVD.h
//
// $Author: gutsche $
// $Date: 2004/05/28 18:02:25 $
// $Revision: 1.2 $
//

#ifndef GUT_GMVD
#define GUT_GMVD

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class TClonesArray;

class GMVD : public GPhysObj {

private:

  // uncut control histograms
  TH1D         *fControlX_uncut;                     // uncut x from vertex generated from good ztt-tracks
  TH1D         *fControlY_uncut;                     // uncut y from vertex generated from good ztt-tracks
  TH1D         *fControlZ_uncut;                     // uncut z from vertex generated from good ztt-tracks
  TH1D         *fControlX_without_muon_uncut;        // uncut x from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fControlY_without_muon_uncut;        // uncut y from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fControlZ_without_muon_uncut;        // uncut z from vertex generated from good ztt-tracks without the chosen muon

  // control histograms
  TH1D         *fControlX;                           // x from vertex generated from good ztt-tracks
  TH1D         *fControlY;                           // y from vertex generated from good ztt-tracks
  TH1D         *fControlZ;                           // z from vertex generated from good ztt-tracks
  TH1D         *fControlX_without_muon;              // x from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fControlY_without_muon;              // y from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fControlZ_without_muon;              // z from vertex generated from good ztt-tracks without the chosen muon

  // uncut general histograms
  TH1D         *fGeneralX_uncut;                     // uncut x from vertex generated from good ztt-tracks
  TH1D         *fGeneralY_uncut;                     // uncut y from vertex generated from good ztt-tracks
  TH1D         *fGeneralZ_uncut;                     // uncut z from vertex generated from good ztt-tracks
  TH1D         *fGeneralX_without_muon_uncut;        // uncut x from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fGeneralY_without_muon_uncut;        // uncut y from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fGeneralZ_without_muon_uncut;        // uncut z from vertex generated from good ztt-tracks without the chosen muon

  // general histograms
  TH1D         *fGeneralX;                           // x from vertex generated from good ztt-tracks
  TH1D         *fGeneralY;                           // y from vertex generated from good ztt-tracks
  TH1D         *fGeneralZ;                           // z from vertex generated from good ztt-tracks
  TH1D         *fGeneralX_without_muon;              // x from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fGeneralY_without_muon;              // y from vertex generated from good ztt-tracks without the chosen muon
  TH1D         *fGeneralZ_without_muon;              // z from vertex generated from good ztt-tracks without the chosen muon

  Double_t      fX;                                  // x from vertex generated from good ztt-tracks
  Double_t      fY;                                  // y from vertex generated from good ztt-tracks
  Double_t      fZ;                                  // z from vertex generated from good ztt-tracks
  Double_t      fX_without_muon;                     // x from vertex generated from good ztt-tracks without chosen muon
  Double_t      fY_without_muon;                     // y from vertex generated from good ztt-tracks without chosen muon
  Double_t      fZ_without_muon;                     // z from vertex generated from good ztt-tracks without chosen muon

  Bool_t        fAllCuts;                            // flag for passing all MVD cuts

public:
  GMVD();
  virtual ~GMVD();
  
  virtual Bool_t CreateHistograms();
  virtual Bool_t CreateGeneral();
  virtual Bool_t CreateControl();

  virtual Bool_t Reset();

  virtual Bool_t FillHistos();
  virtual Bool_t FillGeneral();
  virtual Bool_t FillControl();

  virtual Bool_t Do();

  virtual Bool_t MakeZTTVertex();
  virtual Bool_t MakeZTTVertexWithoutMuon();

  virtual Bool_t Finalize();

  virtual Bool_t GetAllCuts();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  inline virtual Bool_t IsOK() { return fOK; }

  ClassDef(GMVD,0) // class which deals with special MVD functionality
};

R__EXTERN GMVD *gMVD;

#endif
