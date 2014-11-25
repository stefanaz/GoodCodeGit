//
// GLogChecker.h
//
// $Author: gutsche $
// $Date: 2003/10/05 16:19:31 $
// $Revision: 1.2 $
//

#ifndef GUT_GLogChecker
#define GUT_GLogChecker

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class TString;

class GLogChecker : public TObject {

 private:

 public:
  GLogChecker(Int_t argc, char **argv);
  virtual ~GLogChecker();

  virtual TString      ReturnHelpMessage();
  virtual Bool_t       PrintHelpMessage();

  virtual Bool_t       Init(Int_t argc, char **argv);

  virtual Bool_t       CheckLogFiles(Int_t argc, char **argv);
  virtual Bool_t       CheckLogFile(TString file);

  ClassDef(GLogChecker,0) // Card file variable class
};

#endif
