//
// GAnalysis.h
//
// $Author: kahle $
// $Date: 2004/10/14 13:04:58 $
// $Revision: 1.11 $
//

#ifndef GUT_GAnalysis
#define GUT_GAnalysis

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#include <TEventList.h>

class TFile;
class TChain;
class TDirectory;
class TTree;
class TList;
class GAnalysisHeader;
class TString;

class GAnalysis : public TObject {

 private:

  Bool_t                  fEnableAnalysis;                 // flag for enabling analysis loop

  TChain                 *fChain;                          // chain of root files from input path
  TFile                  *fOutputFile;                     // output file

  TDirectory             *fHistogramDir;                   // directorty in fOutputFile for histograms
  TDirectory             *fGeneralDir;                     // directorty in fOutputFile for generalities

  TTree                  *fHeaderTree;                     // tree for header

  TList                  *fPhysicsObjs;                    // list of physics objects, attention, order matters

  GAnalysisHeader        *fHeader;                         // header of analysis

  TEventList * fevlist;                                    // generating an eventlist
  TEventList * fevlist_use;                                // using an existing eventlist
  TFile* ffile_ev;                                         // file to store the generated eventlist in
  TString fevlistfilename;                                 // name of above file

 public:
  GAnalysis(TString cardname);
  virtual ~GAnalysis();

  virtual Bool_t DoAnalysis();
  virtual Bool_t InitAnalysis(TString cardname);

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  virtual Bool_t InitInclude();
  virtual Bool_t ReadControlCards(TString cardname);
  virtual Bool_t ChainRootFiles();
  virtual Bool_t CreateOutputFile();
  virtual Bool_t GenerateHistogrammer();
  virtual Bool_t FinalizeOutputFile();

  inline virtual TFile*           GetOutputFile()        { return fOutputFile;     }
  inline virtual TDirectory*      GetHistrogramDir()     { return fHistogramDir;   }
  inline virtual TDirectory*      GetGeneralDir()        { return fGeneralDir;     }
  virtual TString GetFileName();

  Int_t temp_count;

  ClassDef(GAnalysis,0) // main analysis class
};

R__EXTERN GAnalysis *gAnalysis;

#endif
