//
// GRun.h
//
// $Author: gutsche $
// $Date: 2004/07/19 17:32:02 $
// $Revision: 1.2 $
//

#ifndef GUT_GRun
#define GUT_GRun

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef GUT_EZRunType
#define GUT_EZRunType
enum EZRunType {
  kNormal,
  kLTRKV,
  kNOTTV,
  kLow,
  kHigh
};
#endif




class TString;

class GRun : public TObject {

private:

  Int_t     fRun;           // run number
  Int_t     fEvents;        // number of events in run
  Double_t  fLumi_Cal;      // calorimeter lumi
  Double_t  fLumi_Spec;     // spectrometer lumi
  EZRunType fType;          // run type, especially for 03p-04p, where there are low and high configuration runs


public:
  GRun();
  GRun(Int_t run, Int_t events, Double_t lumi_cal, Double_t lumi_spec, EZRunType type = kNormal);
  virtual ~GRun();

  inline virtual Int_t     GetRun()       { return fRun;       }
  inline virtual Int_t     GetEvents()    { return fEvents;    }
  inline virtual Double_t  GetLumi_Cal()  { return fLumi_Cal;  }
  inline virtual Double_t  GetLumi_Spec() { return fLumi_Spec; }
  inline virtual EZRunType GetType()      { return fType;      }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GRun,0) // run class
};

#endif
