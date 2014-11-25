//
// GHistogrammer.h
//
// $Author: meyer $
// $Date: 2005/03/31 07:54:23 $
// $Revision: 1.31 $
//

#ifndef GUT_GHistogrammer
#define GUT_GHistogrammer

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class TDirectory;
class TH1;
class TH1F;
class TH1D;
class TH2D;
class TProfile;
class TFile;
class TString;
class TCanvas;
class TList;

class GHistogrammer : public TObject {

private:

  TDirectory          *fDirGeneral;             // directory
  TList               *fTypes;                  // which types of MC subdirectories are available (b,c,lf)
  TList               *fPeriods;                // which periods are available (96-p97p,98e-99e,99p-00p,03p-04p)
  TList               *fSubdirs;                // which subdirs are available (dir,res,exgamma,exproton,dir1,dir2,res1,res2,inc)

public:
  GHistogrammer();
  GHistogrammer(TDirectory *top);
  virtual ~GHistogrammer();

  virtual Bool_t InitLists();

  virtual TH1D* TH1DFactory(TString dir, TString name, TString title,
                            Int_t nbin, Double_t low, Double_t high,
                            TString xtitle, TString ytitle, Bool_t store = kTRUE);

  virtual TH1D* TH1DVarFactory(TString dir, TString name, TString title,
                               Int_t nbin, Double_t* array,
                               TString xtitle, TString ytitle, Bool_t store = kTRUE);

  virtual TH1D* TH1DLabelFactory(TString dir, TString name, TString title,
                                 TString binlabes,
                                 TString xtitle, TString ytitle, Bool_t store = kTRUE);

  virtual TProfile* TH1DProfile(TString dir, TString name, TString title,
                                Int_t nbin, Double_t lowx, Double_t highx,
                                Double_t lowy, Double_t highy,
				TString xtitle, TString ytitle, Bool_t store = kTRUE);

  virtual TH1D* ProjectionFactory(TFile* file, TString dir, TH2D* hist, TString newhist,
                                  TString title,Int_t axis, TString xtitle,TString ytitle,Bool_t store = kTRUE);

  virtual TH2D* TH2DFactory(TString dir, TString name, TString title,
                            Int_t nbinx, Double_t lowx, Double_t highx,
                            Int_t nbiny, Double_t lowy, Double_t highy,
                            TString xtitle, TString ytitle, TString ztitle, Bool_t store = kTRUE);

  virtual TH2D* TH2DVarFactory(TString dir, TString name, TString title,
			       Int_t nbinx, Double_t* xarray,
			       Int_t nbiny, Double_t lowy, Double_t highy,
			       TString xtitle, TString ytitle, TString ztitle, Bool_t store = kTRUE);

  virtual TH2D* TH2DVarFactory(TString dir, TString name, TString title,
			       Int_t nbinx, Double_t lowx, Double_t highx,
			       Int_t nbiny, Double_t* yarray,
			       TString xtitle, TString ytitle, TString ztitle, Bool_t store = kTRUE);

  virtual TH2D* TH2DVarFactory(TString dir, TString name, TString title,
			       Int_t nbinx, Double_t* xarray,
			       Int_t nbiny, Double_t* yarray,
			       TString xtitle, TString ytitle, TString ztitle, Bool_t store = kTRUE);

  virtual Bool_t  AddHistosDataStage1(TFile *file, TString type, TString histogramname, TString option);
  virtual Bool_t  AddHistos2DDataStage1(TFile *file, TString type, TString histogramname, TString option);
  virtual Bool_t  AddHistosMCStage1(TFile *file, TString type, TString period, TString histogramname, TString option);
  virtual Bool_t  CopyHistosMCStage1(TFile *file, TString type, TString period, TString histogramname, TString option);
  virtual Bool_t  AddHistos2DMCStage1(TFile *file, TString type, TString period, TString histogramname, TString option);

  virtual Bool_t  AddHistosMCStage2(TFile *file, TString type, TString period, TString histogramname, TString option);
  virtual Bool_t  AddHistos2DMCStage2(TFile *file, TString type, TString period, TString histogramname, TString option);

  virtual Bool_t  AddHistosDataStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  AddHistos2DDataStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  AddHistosMCStage3(TFile *file, TString type, TString histogramname, TString option);
  virtual Bool_t  CopyHistosMCStage3(TFile *file, TString type, TString histogramname, TString option);
  virtual Bool_t  AddHistos2DMCStage3(TFile *file, TString type, TString histogramname, TString option);

  virtual Bool_t  AddHistosMCStage4(TFile *file, TString type, TString histogramname, TString option);
  virtual Bool_t  AddHistos2DMCStage4(TFile *file, TString type, TString histogramname, TString option);

  virtual Double_t  GetGlobalScale(TFile *file, TString period, TString option);

  virtual TH1D* AddTwoHistograms(TH1D* histo1, Double_t weight1,TH1D* histo2, Double_t weight2);

  virtual Bool_t CheckHistoCompat(Int_t number, TH1D **histos);
  virtual Bool_t CheckHistoCompat(TList *histolist);
  virtual Bool_t CheckHistoCompat2D(Int_t number, TH2D **histos);
  virtual Bool_t CheckHistoCompat2D(TList *histolist);
  virtual Bool_t CheckTwoHistoCompat(TH1D* histo1, TH1D* histo2);
  virtual Bool_t CheckTwoHistoCompat2D(TH2D* histo1, TH2D* histo2);

  virtual TH1D* LabelHist(TString name, TString title,
                          TString xaxistitle, TString yaxistitle,
                          TString labels, TString contents);
  virtual TH1D* IntHist(TH1D* histo);
  virtual TH1D* InvIntHist(TH1D* histo);

  virtual TString SameDirectory(Int_t num, TString *array);
  virtual TString SameDirectory(Int_t histonum, TList *histodirlist);

  virtual Bool_t  MergeHistogramsStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  CopyHistogramsStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistograms2DStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistogramsStage2(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistograms2DStage2(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistogramsStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  CopyHistogramsStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistograms2DStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistogramsStage4(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeHistograms2DStage4(TFile *file, TString histogramname, TString option);

  virtual Bool_t  MergeMCHistogramsStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  CopyMCHistogramsStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistograms2DStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistogramsStage2(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistograms2DStage2(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistogramsStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistograms2DStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistogramsStage4(TFile *file, TString histogramname, TString option);
  virtual Bool_t  CopyMCHistogramsStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeMCHistograms2DStage4(TFile *file, TString histogramname, TString option);

  virtual Bool_t  MergeDataHistogramsStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeDataHistograms2DStage1(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeDataHistogramsStage3(TFile *file, TString histogramname, TString option);
  virtual Bool_t  MergeDataHistograms2DStage3(TFile *file, TString histogramname, TString option);

  virtual Bool_t  FitPtRel(TFile *file, TString histogramname, TString option);
  virtual Bool_t  FitPtRelMCOnly(TFile *file, TString histogramname, TString option);

  virtual Bool_t  FitImpact(TFile *file, TString histogramname, TString option);
  virtual Bool_t  FitImpactMCOnly(TFile *file, TString histogramname, TString option);

  virtual Bool_t  MergeMCHistogramsUnweighted(TFile *file, TString histogramname, TString histoname, TString histotitle, TString option);
  virtual Bool_t  MergeMCHistogramsUnweighted2D(TFile *file, TString histogramname, TString histoname, TString histotitle, TString option);
  virtual Bool_t  MakeHistogramProjection(TFile *file, TString histogramname, TString option);


  virtual TCanvas* DataMcPlot(Int_t histonumber, TH1D** histos,
                              TString name, TString title,
                              TString xaxis, TString yaxis,
                              Double_t x1ndc, Double_t y1ndc,
                              Double_t x2ndc, Double_t y2ndc,
                              Double_t leftMargin,
                              TString option);
  virtual TCanvas* DataMcPlot(Int_t histonumber, TH1F** histos,
                              TString name, TString title,
                              TString xaxis, TString yaxis,
                              Double_t x1ndc, Double_t y1ndc,
                              Double_t x2ndc, Double_t y2ndc,
                              Double_t leftMargin,
                              TString option);
  virtual TCanvas* DataMcPlot2(Int_t histonumber, TH1D** histos,
                              TString name, TString title,
                              TString datalegend, TString mclegend,
                              TString xaxis, TString yaxis,
                              Double_t x1ndc, Double_t y1ndc,
                              Double_t x2ndc, Double_t y2ndc,
                              Double_t leftMargin,
                              TString option);
  virtual TCanvas* McPlot(Int_t histonumber, TH1D** histos,
                          TString name, TString title,
                          TString xaxis, TString yaxis,
                          Double_t x1ndc, Double_t y1ndc,
                          Double_t x2ndc, Double_t y2ndc,
                          Double_t leftMargin,
                          TString option);
  virtual TCanvas* McPlot(Int_t histonumber, TH1F** histos,
                          TString name, TString title,
                          TString xaxis, TString yaxis,
                          Double_t x1ndc, Double_t y1ndc,
                          Double_t x2ndc, Double_t y2ndc,
                          Double_t leftMargin,
                          TString option);
  virtual Bool_t ZeroErrors(TH1 *hist);
  virtual Bool_t ComparePlots(TFile *reference, TFile *compare, TString dir, TString plot, TString option);
  virtual Double_t IntegrateHistLowEdge(TH1* hist);

  inline TList* GetPeriods() { return fPeriods; }
  inline TList* GetTypes()   { return fTypes;   }
  inline TList* GetSubdirs() { return fSubdirs; }

  virtual TH1D* CopyPtRelCorrection(TString dir, TH1D *histo, Double_t weight);

  virtual TH1D* PlusMinusErrorPerBin(TH1D *input, Bool_t plus = kTRUE);

  ClassDef(GHistogrammer,0) // Histogram creation and store class
};

R__EXTERN GHistogrammer *gHistogrammer;

#endif
