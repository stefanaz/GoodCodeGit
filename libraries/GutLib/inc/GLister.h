//
// GLister.h
//
// $Author: gutsche $
// $Date: 2004/06/24 17:41:40 $
// $Revision: 1.15 $
//

#ifndef GUT_GLister
#define GUT_GLister

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

class GLister : public TObject {

 private:

  TString          fPath;                  // output path

  TString          fSelList96p;            // selection list content for 96p runperiod
  TString          fSelList97p;            // selection list content for 97p runperiod
  TString          fSelList98e;            // selection list content for 98e runperiod
  TString          fSelList99e;            // selection list content for 99e runperiod
  TString          fSelList99p;            // selection list content for 99p runperiod
  TString          fSelList00p;            // selection list content for 00p runperiod
  TString          fSelList02p;            // selection list content for 02p runperiod
  TString          fSelList03p;            // selection list content for 03p runperiod
  TString          fSelList04p;            // selection list content for 04p runperiod
  TString          fSelListMC;             // selection list content for monte carlo
  TString          fSelListGen;            // selection list content for no specific run period

  Bool_t           fError;                 // flag if event has error 
  Bool_t           fOutput;                // flag if output of event should be written out
  Bool_t           fSelection;             // flag if entry to selection list should be made

  ofstream        *fErrorList;             // ascii list of error flags or processed events
  ofstream        *fProcEvents;            // ascii lists of processed events
  ofstream        *fSelectionList;         // ascii list of selected events
  ofstream        *fOutputList;            // ascii list of output

  TString          fFileName;              // current filename
  Bool_t           fNewFile;               // flag indicating filename was never used in gLister

 public:
  GLister(TString path);
  virtual ~GLister();

  virtual Bool_t GenerateLists();
  virtual Bool_t InitProcEvents(TString listname);
  virtual Bool_t InitErrorList(TString listname);
  virtual Bool_t InitSelectionList(TString listname);
  virtual Bool_t InitOutputList(TString listname);

  virtual Bool_t FillLists();
  virtual Bool_t FillErrorList(TString message);
  virtual Bool_t FillSelectionList(Int_t run, Int_t event);
  virtual Bool_t FillOutputList(Int_t run, Int_t event);
  virtual Bool_t FillOutputList(TString string);

  virtual Bool_t ResetLists();
  
  virtual Bool_t FinalizeLists();
  virtual Bool_t FinalizeProcEvents();
  virtual Bool_t FinalizeErrorList();
  virtual Bool_t FinalizeSelectionList();
  virtual Bool_t FinalizeOutputList();

  virtual Bool_t SelListHeader(ofstream *stream, TString title);

  virtual Bool_t Header(ofstream *stream, TString title);
  virtual Bool_t Footer(ofstream *stream, TString title);

  inline virtual void SetOutput(Bool_t input) { fOutput = input; }
  inline virtual void SetSelection(Bool_t input) { fSelection = input; }

  inline virtual void SetFileName(TString name) { fFileName = name; fNewFile = kTRUE; }

  ClassDef(GLister,0) // ascii list class
};

R__EXTERN GLister *gLister;

#endif
