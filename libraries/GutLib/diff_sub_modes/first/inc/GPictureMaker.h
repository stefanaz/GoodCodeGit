//
// GPictureMaker.h
//
// $Author: kahle $
// $Date: 2004/10/14 18:15:38 $
// $Revision: 1.25 $
//

#ifndef GUT_GPictureMaker
#define GUT_GPictureMaker

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

using namespace std;

class GPictureMaker : public TObject {

private:

  TString     fDate;                      // date of html gallery
  TString     fTitle;                     // title for html gallery
  TString     fInputDir;                  // input directory
  TString     fDirectory;                 // output directory
  TString     fMode;                      // running mode
  TFile      *fFile;                      // input file
  TString     fOutputFile;                // output file for PS and LOGPS modes
  TString     fGalleryDirectory;          // gallery directory
  TString     fPsFileName;                // ps output filename
  Int_t       fPsRows;                    // rows in ps output file
  Int_t       fPsColumns;                 // columns in ps output file
  Int_t       fPsCurrentRow;              // current row in ps output file
  Int_t       fPsCurrentColumn;           // current column in ps output file
  TCanvas    *fCanvas;                    // canvas for ps output
  Bool_t      fPsFirstDirectory;          // boolean for label on first pad
  Bool_t      fPsFirstInFile;             // boolean for first in pad
  TPaveLabel *fPsLabel;                   // label for ps output 
  TPaveLabel *fPsTimeLabel;               // label for ps output 
  TPaveLabel *fPsLogyLabel;               // label for ps output 

  TString     fTime;                      // time string from start of object
  ofstream   *fHTMLTop;                   // top html file
  ofstream   *fHTML;                      // top file
  TString     fHTMLTopName;               // name of top html file
  TString     fHTMLTopSavedDir;           // saved dir of top html filling
  TString     fGutCodeDir;                // GUTCODEDIR
  TString     fConvert;                   // location of convert
  Float_t     fScaleFactor;               // scale factor for small and thumb pictures

  TFile      *fComparisonFile1;           // file one for comparison mode
  TFile      *fComparisonFile2;           // file two for comparison mode

  TList      *fPlotsPtRel;                // list for ptrel plots to generate
  TList      *fPlotsImpact;               // list for impact parameter plots to generate
  TList      *fPlotsComparison;           // list for comparison plots to generate
  TList      *fPlots1D;                   // list of 1D plots to generate
  TList      *fPlots1DMC;                 // list of 1D MC plots to generate
  TList      *fPlots1DZoomed;             // list of zoomed 1D plots to generate
  TList      *fPlots1DMCZoomed;           // list of zoomed 1D MC plots to generate
  TList      *fPlots2D;                   // list of 2D plots to generate
  TList      *fPlots2DMC;                 // list of 2D MC plots to generate
  TList      *fPlots2DZoomed;             // list of zoomed 2D plots to generate
  TList      *fPlots2DMCZoomed;           // list of zoomed 2D MC plots to generate

  TList      *fPlotsEfficiencyBasename;   // list of basenames for efficiency plots
  TList      *fPlotsEfficiencyFinder;     // list of finder combination ids for efficiency plots
  TList      *fPlotsEfficiencyRegion;     // list of regions for efficiency plots

  // global steering
  Bool_t     fCLFDraw;                    // draw c and lf seperatly in all histograms
  Bool_t     fPicturesPS;                 // produce PS-pictures of all histos 
  Bool_t     fPicturesGIF;                // produce GIF-pictures of all histos 
  Bool_t     fPicturesJPG;                // produce JPG-pictures of all histos 
  Bool_t     fPicturesEPS;                // produce EPS-pictures of all histos 
  Bool_t     fPicturesPeriods;            // produced pictures for all periods
  Bool_t     fPicturesPtRel;              // produced ptrel fit pictures
  Bool_t     fPicturesImpact;             // produced impact fit pictures
  TString    fPicturesPtRel_1;            // ptrel-base-histogram for ptrel comparison plots 1, if empty, deactivated
  TString    fPicturesPtRel_2;            // ptrel-base-histogram for ptrel comparison plots 2, if empty, deactivated
  Bool_t     fPicturesPtRelMCOnly;        // activate also MCONLY ptrel plots
  TString    fPicturesImpact_1;           // impact-base-histogram for impact fit comparison plots 2, if empty, deactivated
  Bool_t     fPicturesLumi;               // produce lumi-comparison-pictures
  Bool_t     fPictures1D;                 // produce 1D plots
  Bool_t     fPictures2D;                 // produce 2D plots
  Bool_t     fPicturesEff;                // produce efficiency plots

public:
  GPictureMaker();
  GPictureMaker(int argc, char **argv);
  virtual ~GPictureMaker();

  virtual Bool_t InitLists();

  virtual void    DecodeCommandline(int argc, char **argv);
  virtual Bool_t  EndGallery(TString option);
  virtual Bool_t  EndPsFile(TString option);
  virtual void    FillGallery(TString dirname, TH1 *histo, TString option);
  virtual void    FillPs(TString dirname, TH1 *histo, TString option);
  virtual Bool_t  GenHTMLPics(TCanvas* canvas, TString name, TString directory, 
			      TString title, TString option);
  virtual Bool_t  GenHTMLPics(ofstream *stream, TCanvas* canvas, TString name, TString directory, 
			      TString title, TString option);
  virtual TString GetTime();
  virtual TString GoThroughDirectory(TString dirname, TDirectory* directory, TString option);
  virtual Bool_t  GoThroughFile(TFile* file, TString option);
  virtual void    HelpMessage();
  virtual Bool_t  HTMLEnd(ofstream *stream, TString top, TString date, TString option);
  virtual Bool_t  HTMLStart(ofstream *stream, TString title, TString filename, TString option);
  virtual Bool_t  HTMLStream(TString thumb, TString title, TString ps, TString eps, TString gif, TString jpg,
			    TString logps, TString logeps, TString loggif, TString logjpg, TString option);
  virtual Bool_t  HTMLStream(ofstream *stream, TString thumb, TString title, TString ps, TString eps, TString gif, TString jpg,
			    TString logps, TString logeps, TString loggif, TString logjpg, TString option);
  virtual Bool_t  HTMLStreamTop(TString link, TString entry, TString option);
  virtual Bool_t  HTMLStreamTop(ofstream *stream, TString link, TString entry, TString option);
  virtual Bool_t  MakeDir(TString directory);
  virtual void    MakeGallery(TFile *file, TString directory, TString option);
  virtual void    MakePics(TFile *file, TString filename, TString directory, 
			   Int_t rows, Int_t columns, TString option);
  virtual Bool_t  MakePtRelPlot(TFile *file, ofstream *stream, TString histogramname, TString directory, TString period, TString option);
  virtual Bool_t  MakeImpactPlot(TFile *file, ofstream *stream, TString histogramname, TString directory, TString period, TString option);
  virtual Bool_t  Make1DPlot(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString period, TString option, Double_t zoomx = 0.0);
  virtual Bool_t  Make2DPlot(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString period, TString option, Double_t zoomx = 0.0, Double_t zoomy = 0.0);
  virtual Bool_t  MakeEfficiencyPlotData(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString period, TString region, TString type, TString option);
  virtual Bool_t  MakeEfficiencyPlotMC(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString period, TString region, TString type, TString option);
  virtual Bool_t  MakeCorrectionPlot(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString period, TString region, TString type, TString option);
  virtual Bool_t MakeDataMCComparisonPlot(TFile *file, TString period, TString name, TString datadir, TString histoname, TString histotitle, TString directory, TString option, Double_t addToMaximum = 0.0);
  virtual Bool_t MakeComparisonPlot(TFile *file, ofstream *stream, TString histogramname, TString ptrelhistogramname, TString period, TString directory, TString option, Double_t scaleMaximum = 1.2);
  virtual Bool_t MakeComparisonPlotLumi(TFile *file, TString period, TString name, TString datadir, TString histoname, TString histotitle, TString directory, TString option);

  virtual Bool_t  MakePtRelPlotComplete(TFile *file, ofstream *stream, TString histogramname, TString directory, TString option);
  virtual Bool_t  MakeImpactPlotComplete(TFile *file, ofstream *stream, TString histogramname, TString directory, TString option);
  virtual Bool_t  Make1DPlotComplete(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString option, Double_t zoomx = 0.0);
  virtual Bool_t  Make2DPlotComplete(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString option, Double_t zoomx = 0.0, Double_t zoomy = 0.0);
  virtual Bool_t MakeComparisonPlotComplete(TFile *file, ofstream *stream, TString histogramname, TString ptrelhistogramname, TString directory, TString option, Double_t scaleMaximum = 1.2);
  virtual Bool_t  MakeEfficiencyPlotDataComplete(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString region, TString type, TString option);
  virtual Bool_t  MakeEfficiencyPlotMCComplete(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString region, TString type, TString option);
  virtual Bool_t  MakeCorrectionPlotComplete(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString region, TString type, TString option);


  virtual Bool_t  MakeSpecial(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriod(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodPtRel(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodImpact(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodComparison(TFile *file, TString period, TString directory, TString ptrelhistogramname, TString option);
  virtual Bool_t  MakeSpecialPeriod1D(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriod2D(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodEfficiency(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodEfficiencyData(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodEfficiencyMC(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialPeriodEfficiencyMCType(TFile *file, TString period, TString directory, TString type, TString option);
  virtual Bool_t  MakeSpecialPeriodCorrection(TFile *file, TString period, TString directory, TString option);
  virtual Bool_t  MakeSpecialComplete(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompletePtRel(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompleteImpact(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompleteComparison(TFile *file, TString directory, TString ptrelhistogramname, TString option);
  virtual Bool_t  MakeSpecialComplete1D(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialComplete2D(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompleteEfficiency(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompleteEfficiencyData(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompleteEfficiencyMC(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeSpecialCompleteEfficiencyMCType(TFile *file, TString directory, TString type, TString option);
  virtual Bool_t  MakeSpecialCompleteCorrection(TFile *file, TString directory, TString option);
  virtual Bool_t  MakeTwoFileComparison(TFile *file1, TFile *file2, TString directory, TString option);
  virtual Bool_t  MakeTwoFilesComparisonPlot(TFile *file1, TFile *file2, ofstream *stream, TString histogramname, TString directory, TString option);
  virtual Int_t   PsIncreasePadNumber();
  virtual Bool_t  StartGallery(TString option);
  virtual Bool_t  StartPsFile(TFile *file, TString option);

  inline virtual Bool_t EndHTMLStream() { delete fHTML; fHTML = 0; return kTRUE; }
  inline virtual Bool_t EndHTMLTopStream() { delete fHTMLTop; fHTMLTop = 0; return kTRUE; }
  inline virtual ofstream* GetHTMLStream() { return fHTML; }
  inline virtual ofstream* GetHTMLTopStream() { return fHTMLTop; }
  inline virtual ofstream* InitHTMLStream(TString path) { return fHTML = new ofstream(path); }
  inline virtual ofstream* InitHTMLTopStream(TString path) { return fHTMLTop = new ofstream(path); }

  inline virtual TList* GetEfficiencyBasename() { return fPlotsEfficiencyBasename; }
  inline virtual TList* GetEfficiencyFinder()   { return fPlotsEfficiencyFinder;   }
  inline virtual TList* GetEfficiencyRegion()   { return fPlotsEfficiencyRegion;   }

  inline virtual Bool_t DoCLFDraw()          { return fCLFDraw;          }
  inline virtual Bool_t DoPicturesPS()       { return fPicturesPS;       }
  inline virtual Bool_t DoPicturesGIF()      { return fPicturesGIF;      }
  inline virtual Bool_t DoPicturesEPS()      { return fPicturesEPS;      }
  inline virtual Bool_t DoPicturesJPG()      { return fPicturesJPG;      }

  inline virtual Bool_t  DoPicturesPeriods()     { return fPicturesPeriods;     }
  inline virtual Bool_t  DoPicturesPtRel()       { return fPicturesPtRel;       }
  inline virtual Bool_t  DoPicturesImpact()      { return fPicturesImpact;      }
  inline virtual TString DoPicturesPtRel_1()     { return fPicturesPtRel_1;     }
  inline virtual TString DoPicturesPtRel_2()     { return fPicturesPtRel_2;     }
  inline virtual Bool_t  DoPicturesPtRelMCOnly() { return fPicturesPtRelMCOnly; }
  inline virtual TString DoPicturesImpact_1()    { return fPicturesImpact_1;    }
  inline virtual Bool_t  DoPicturesLumi()        { return fPicturesLumi;        }
  inline virtual Bool_t  DoPictures1D()          { return fPictures1D;          }
  inline virtual Bool_t  DoPictures2D()          { return fPictures2D;          }
  inline virtual Bool_t  DoPicturesEff()         { return fPicturesEff;         }

  ClassDef(GPictureMaker,0) // class for batch picture generation
};

R__EXTERN GPictureMaker *gPictureMaker;

#endif
