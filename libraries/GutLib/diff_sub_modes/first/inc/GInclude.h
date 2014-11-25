//
// GInclude.h
//
// $Author: meyer $
// $Date: 2005/02/14 17:30:02 $
// $Revision: 1.52 $
//

#ifndef GUT_GInclude
#define GUT_GInclude

#include <iostream>
#include <fstream>
#include <iomanip>
#include <strstream>
#include <vector>

#ifndef GUT_GAnalysis
#include <GAnalysis.h>
#endif

#ifndef GUT_GAnalysisHeader
#include <GAnalysisHeader.h>
#endif

#ifndef GUT_GConnectTree
#include <GConnectTree.h>
#endif

#ifndef GUT_GHistogrammer
#include <GHistogrammer.h>
#endif

#ifndef GUT_GCards
#include <GCards.h>
#endif

#ifndef GUT_GLister
#include <GLister.h>
#endif

#ifndef GUT_GCal
#include <GCal.h>
#endif

#ifndef GUT_GBac
#include <GBac.h>
#endif

#ifndef GUT_GJets
#include <GJets.h>
#endif

#ifndef GUT_GJet
#include <GJet.h>
#endif

#ifndef GUT_GSinistra
#include <GSinistra.h>
#endif

#ifndef GUT_GVertex
#include <GVertex.h>
#endif

#ifndef GUT_GTrigger
#include <GTrigger.h>
#endif

#ifndef GUT_GZufo
#include <GZufo.h>
#endif

#ifndef GUT_GGeneral
#include <GGeneral.h>
#endif

#ifndef GUT_GMCs
#include <GMCs.h>
#endif

#ifndef GUT_GMC
#include <GMC.h>
#endif

#ifndef GUT_GMCVertex
#include <GMCVertex.h>
#endif

#ifndef GUT_GRuns
#include <GRuns.h>
#endif

#ifndef GUT_GRun
#include <GRun.h>
#endif

#ifndef GUT_GMuons
#include <GMuons.h>
#endif

#ifndef GUT_GMuonEfficiency
#include <GMuonEfficiency.h>
#endif

#ifndef GUT_GMuon
#include <GMuon.h>
#endif

#ifndef GUT_GTracks
#include <GTracks.h>
#endif

#ifndef GUT_GTrack
#include <GTrack.h>
#endif

#ifndef GUT_GMJMatch
#include <GMJMatch.h>
#endif

#ifndef GUT_GMJMatchs
#include <GMJMatchs.h>
#endif

#ifndef GUT_GTJMatch
#include <GTJMatch.h>
#endif

#ifndef GUT_GTJMatchs
#include <GTJMatchs.h>
#endif

#ifndef GUT_GDIMuon
#include <GDIMuon.h>
#endif

#ifndef GUT_GDIMuons
#include <GDIMuons.h>
#endif

#ifndef GUT_GTriMuon
#include <GTriMuon.h>
#endif

#ifndef GUT_GTriMuons
#include <GTriMuons.h>
#endif

#ifndef GUT_GPtRelFit
#include <GPtRelFit.h>
#endif

#ifndef GUT_GImpactFit
#include <GImpactFit.h>
#endif

#ifndef GUT_GFitter
#include <GFitter.h>
#endif

#ifndef GUT_GMVD
#include <GMVD.h>
#endif

#ifndef GUT_GBeamSpot
#include <GBeamSpot.h>
#endif

#ifndef ROOT_THStack
#include <THStack.h>
#endif

#ifndef ROOT_TH1
#include <TH1.h>
#endif

#ifndef ROOT_TH1F
#include <TH1F.h>
#endif

#ifndef ROOT_TH1D
#include <TH1D.h>
#endif

#ifndef ROOT_TPROFILE
#include <TProfile.h>
#endif

#ifndef ROOT_TH2D
#include <TH2D.h>
#endif

#ifndef ROOT_TMath
#include <TMath.h>
#endif

#ifndef ROOT_TLorentzVector
#include <TLorentzVector.h>
#endif

#ifndef ROOT_TVector3
#include <TVector3.h>
#endif

#ifndef ROOT_TVector2
#include <TVector2.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

#ifndef ROOT_TObjString
#include <TObjString.h>
#endif

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TClonesArray
#include <TClonesArray.h>
#endif

#ifndef ROOT_TObjArray
#include <TObjArray.h>
#endif

#ifndef ROOT_TStyle
#include <TStyle.h>
#endif

#ifndef ROOT_TSystem
#include <TSystem.h>
#endif

#ifndef ROOT_TFile
#include <TFile.h>
#endif

#ifndef ROOT_TTree
#include <TTree.h>
#endif

#ifndef ROOT_TChain
#include <TChain.h>
#endif

#ifndef ROOT_TCanvas
#include <TCanvas.h>
#endif

#ifndef ROOT_TDatime
#include <TDatime.h>
#endif

#ifndef ROOT_TDirectory
#include <TDirectoy.h>
#endif

#ifndef ROOT_TRegexp
#include <TRegexp.h>
#endif

#ifndef ROOT_TROOT
#include <TROOT.h>
#endif

#ifndef ROOT_TPaveLabel
#include <TPaveLabel.h>
#endif

#ifndef ROOT_TPaveText
#include <TPaveText.h>
#endif

#ifndef ROOT_TPaveStats
#include <TPaveStats.h>
#endif

#ifndef ROOT_TText
#include <TText.h>
#endif

#ifndef ROOT_TKey
#include <TKey.h>
#endif

#ifndef ROOT_TMinuit
#include <TMinuit.h>
#endif

#ifndef ROOT_TLegend
#include <TLegend.h>
#endif

#ifndef ROOT_TCanvas
#include <TCanvas.h>
#endif

#ifndef ROOT_TClonesArray
#include <TClonesArray.h>
#endif

using namespace std;

class GInclude : public TObject {

private:

public:
  GInclude();
  virtual ~GInclude();

  virtual TString FormatedInt(Int_t number, Int_t length, Int_t decimals, TString fill, Bool_t neg = kFALSE);
  virtual TString FormatedDouble(Double_t number, Int_t length, Int_t decimals);
  virtual TString FormatedChar(TString string, Int_t length);
  virtual TString FormatedBool(Bool_t input);
  virtual TStyle* MySetStyle();
  virtual TStyle* ZEUSSetStyle();
  virtual TH1D* ReadAscii(TString filename, TString histoname, 
			  TString histotitle, TString xaxistitle, 
			  TString yaxistitle, Int_t bins, Double_t lower_border, 
			  Double_t upper_border);
  virtual void StartChainViewer(TChain *chain);
  virtual TChain* ChainFiles(TString directory);
  virtual void StartViewer(TTree *tree);
  virtual TTree* InitTree(TFile *file);
  virtual void InitData(TString name);
  virtual void ReadoutHeader(TFile *file);
  virtual void ReadoutHeaderToFile(TFile *file, TString outputfilename);
  virtual void ReadoutFits(TFile *file);
  virtual void ReadoutFitsToFile(TFile *file, TString outputfilename);
  virtual Double_t GetLumi(TFile *file, TString histoname);
  virtual void SetLumi(TFile *file, TString histoname,Double_t reweightfactor);
  virtual TFile* OpenFile(TString name);
  virtual void GenClass(TString name);
  virtual TDirectory* MkdirRecursive(TDirectory *initial, TString directory);
  virtual TDirectory* MkdirRecursiveOld(TDirectory *initial, TString directory);
  virtual TKey* FindKeyAnyRecursive(TDirectory *initial, TString object);
  virtual TString StripLastDir(TString dir);
  virtual TString StripFirstDir(TString dir);
  virtual TString StripFromFirstSpace(TString dir);
  virtual TString GetExtension(TString file);

  virtual Bool_t AddFit(TFile *file, TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter);
  virtual Bool_t AddImpactFit(TFile *file, TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter);
  virtual Bool_t CopyFits(TFile *source, TFile *destination); 

  virtual Int_t GetNHeaders(TFile *file);
  virtual GAnalysisHeader* GetHeader(TFile *file, Int_t index);
  virtual GPtRelFit* GetFit(TFile *file, TString name);
  virtual GImpactFit* GetImpactFit(TFile *file, TString name);

  virtual void NicePlot(TPad *pad);
  virtual void NicePlotDraw(TPad *pad);
  virtual void FastNice();
  virtual void FastPics();
  virtual TString GetFirstHistoFromCanvas(TCanvas *canvas);
  virtual TString GetFirstHistoFromPad(TPad *pad);
  virtual TObject* GetFromFile(TFile *file, TString name);

  virtual Bool_t DumpHisto(TH1D *histo, TString filename);
  virtual Bool_t DumpHisto(TH2D *histo, TString filename);  
  virtual TH1D* ReadinHisto(TString filename);

  virtual void CopyEfficiencyPlots(TFile *input, TString outputname);
  
  virtual Bool_t CopyPtRelCorrections(TFile *input, TFile *output, Double_t charm_weight, Double_t lf_weight);
  virtual TH1D *CloneHistoWithWeight(TH1D *histo, Double_t weight);

  ClassDef(GInclude,0) // class for general include and helper functions
};

R__EXTERN GInclude *gInclude;

#endif
