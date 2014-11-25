//
// GMerger.h
//
// $Author: meyer $
// $Date: 2007/03/14 09:28:06 $
// $Revision: 1.13 $
//

#ifndef GUT_GMerger
#define GUT_GMerger

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class TFile;
class TString;
class TList;

class GMerger : public TObject {

private:

  TList *fOneD;             // list of 1-D histogram names
  TList *fOneD_unweighted;  // list of unweighted 1-D histogram names
  TList *fOneDLabel;        // list of 1d labeled histograms

  TList *fTwoD;             // list of 2-D histogram names
  TList *fTwoD_unweighted;  // list of 2-D histogram names
  TList *fPtRel;            // list of histograms for which the ptrel fit is done
  TList *fOneDCopy;         // list of MC histograms which are only copied to the next higher level
  TList *fImpact;           // list of histograms for which the impact fit is done
  TList *fTwoDProjection;   // list of 2D Histograms to make 1D Projections

public:
  GMerger();
  GMerger(int argc, char **argv);
  virtual ~GMerger();

  virtual Bool_t DecodeCommandline(int argc, char **argv);

  virtual TString HelpMessage();

  virtual Bool_t InitLists();

  virtual Bool_t MergeHistoFiles(TFile *inputfile, TFile *outputfile, TString directory);
  virtual Bool_t MergeHistoTree(TFile *inputfile, TFile *outputfile, TString directory);
  virtual Bool_t CopyFile(TString inputfile, TString outpufile, TString directory);
  virtual Bool_t CopyFiles(TString inputfiles, TString outpufile, TString directory);
  virtual Bool_t MergeHistograms(TString filename);
  virtual Bool_t MergeHistogramsStage1(TFile *file);
  virtual Bool_t MergeHistogramsStage2(TFile *file);
  virtual Bool_t MergeHistogramsStage3(TFile *file);
  virtual Bool_t MergeHistogramsStage4(TFile *file);
  virtual Bool_t MergeHistogramsPtRel(TFile *file);
  virtual Bool_t MergeHistogramsImpact(TFile *file);
  virtual Bool_t MergeHistogramsStage1(TString filename);
  virtual Bool_t MergeHistogramsStage2(TString filename);
  virtual Bool_t MergeHistogramsStage3(TString filename);
  virtual Bool_t MergeHistogramsStage4(TString filename);
  virtual Bool_t MergeHistogramsPtRel(TString filename);
  virtual Bool_t MergeHistogramsImpact(TString filename);
  virtual Bool_t FinalizeHistograms(TString filename);
  virtual Bool_t MakeProjections(TFile *file);

  ClassDef(GMerger,0) // merges histogram and tree files to one file
};

R__EXTERN GMerger *gMerger;

#endif
