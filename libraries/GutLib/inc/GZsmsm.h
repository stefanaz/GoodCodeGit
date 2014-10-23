//
// GZsmsm.h
//
// $Author: gutsche $
// $Date: 2003/10/05 16:19:32 $
// $Revision: 1.3 $
//

#ifndef GUT_GZsmsm
#define GUT_GZsmsm

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

class GZsmsm : public TObject {

 private:

  TString previous;       // previous zsmsm release
  TString current;        // current zsmsm release

 public:
  GZsmsm(Int_t argc, char **argv);
  virtual ~GZsmsm();

  virtual TString      ReturnHelpMessage();
  virtual Bool_t       PrintHelpMessage();

  virtual Bool_t       Init(Int_t argc, char **argv);

  virtual Bool_t       RemoveOldFiles();
  virtual Bool_t       RemoveTempFiles();
  virtual Bool_t       CvsDiff();
  virtual Bool_t       CheckErr();
  virtual Bool_t       CheckDiff();

  ClassDef(GZsmsm,0) // Checks cvs diff for zsmsm release of ZeVis
};

#endif
