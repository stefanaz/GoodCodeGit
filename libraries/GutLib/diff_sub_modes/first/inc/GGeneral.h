//
// GGeneral.h
//
// $Author: gutsche $
// $Date: 2005/02/18 12:07:41 $
// $Revision: 1.12 $
//

#ifndef GUT_GGeneral
#define GUT_GGeneral

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

#ifndef GUT_EZRunPeriod
#define GUT_EZRunPeriod
enum EZRunPeriod {
  kUnidentified,
  k96p,
  k97p,
  k98e,
  k99e,
  k99p,
  k00p,
  k02p,
  k03p,
  k04p,
  k05e,
  k06e,
  k06p,
  k07p,
  k96p97p,
  k98e99e,
  k99p00p,
  k03p04p,
  k05e06e,
  k06p07p,
};
#endif

class GGeneral : public GPhysObj {

 private:

  EZRunPeriod fPeriod;       // run period

  Int_t      f96p_low;       // lower border of 96p' runrange
  Int_t      f96p_up;        // upper border of 96p' runrange
  Int_t      f97p_low;       // lower border of 97p' runrange
  Int_t      f97p_up;        // upper border of 97p' runrange
  Int_t      f98e_low;       // lower border of 98e' runrange
  Int_t      f98e_up;        // upper border of 98e' runrange
  Int_t      f99e_low;       // lower border of 99e' runrange
  Int_t      f99e_up;        // upper border of 99e' runrange
  Int_t      f99p_low;       // lower border of 99p' runrange
  Int_t      f99p_up;        // upper border of 99p' runrange
  Int_t      f00p_low;       // lower border of 00p' runrange
  Int_t      f00p_up;        // upper border of 00p' runrange
  Int_t      f02p_low;       // lower border of 02p' runrange
  Int_t      f02p_up;        // upper border of 02p' runrange
  Int_t      f03p_low;       // lower border of 03p' runrange
  Int_t      f03p_up;        // upper border of 03p' runrange
  Int_t      f04p_low;       // lower border of 04p' runrange
  Int_t      f04p_up;        // upper border of 04p' runrange
  Int_t      f05e_low;       // lower border of 05e' runrange
  Int_t      f05e_up;        // upper border of 05e' runrange
  Int_t      f06e_low;       // lower border of 06e' runrange
  Int_t      f06e_up;        // upper border of 06e' runrange
  Int_t      f06p_low;       // lower border of 06p' runrange
  Int_t      f06p_up;        // upper border of 06p' runrange
  Int_t      f07p_low;       // lower border of 07p' runrange
  Int_t      f07p_up;        // upper border of 07p' runrange

  TH1D      *f96p_uncut;     // uncut run summary plot for 96p
  TH1D      *f97p_uncut;     // uncut run summary plot for 97p
  TH1D      *f98e_uncut;     // uncut run summary plot for 98e
  TH1D      *f99e_uncut;     // uncut run summary plot for 99e
  TH1D      *f99p_uncut;     // uncut run summary plot for 99p
  TH1D      *f00p_uncut;     // uncut run summary plot for 00p
  TH1D      *f02p_uncut;     // uncut run summary plot for 02p
  TH1D      *f03p_uncut;     // uncut run summary plot for 03p
  TH1D      *f04p_uncut;     // uncut run summary plot for 04p
  TH1D      *f05e_uncut;     // uncut run summary plot for 05e
  TH1D      *f06e_uncut;     // uncut run summary plot for 06e
  TH1D      *f06p_uncut;     // uncut run summary plot for 06p
  TH1D      *f07p_uncut;     // uncut run summary plot for 07p

  TH1D      *f96p;           // run summary plot for 96p
  TH1D      *f97p;           // run summary plot for 97p
  TH1D      *f98e;           // run summary plot for 98e
  TH1D      *f99e;           // run summary plot for 99e
  TH1D      *f99p;           // run summary plot for 99p
  TH1D      *f00p;           // run summary plot for 00p
  TH1D      *f02p;           // run summary plot for 02p
  TH1D      *f03p;           // run summary plot for 03p
  TH1D      *f04p;           // run summary plot for 04p
  TH1D      *f05e;           // run summary plot for 05e
  TH1D      *f06e;           // run summary plot for 06e
  TH1D      *f06p;           // run summary plot for 06p
  TH1D      *f07p;           // run summary plot for 07p

  TH1D      *f96p_Taked;     // run summary plot for 96p
  TH1D      *f97p_Taked;     // run summary plot for 97p
  TH1D      *f98e_Taked;     // run summary plot for 98e
  TH1D      *f99e_Taked;     // run summary plot for 99e
  TH1D      *f99p_Taked;     // run summary plot for 99p
  TH1D      *f00p_Taked;     // run summary plot for 00p
  TH1D      *f02p_Taked;     // run summary plot for 02p
  TH1D      *f03p_Taked;     // run summary plot for 03p
  TH1D      *f04p_Taked;     // run summary plot for 04p
  TH1D      *f05e_Taked;     // run summary plot for 05e
  TH1D      *f06e_Taked;     // run summary plot for 06e
  TH1D      *f06p_Taked;     // run summary plot for 06p
  TH1D      *f07p_Taked;     // run summary plot for 07p

  TH1D      *fWeight_uncut;  // uncut event weight
  TH1D      *fWeight;        // event weight

 public:
  GGeneral();
  virtual ~GGeneral();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();
  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();

  virtual Bool_t Do();

  virtual Bool_t CheckRunPeriod();
  virtual Bool_t CheckProperties();
  
  virtual Bool_t Reset();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  inline virtual Int_t       Get96p_low()   { return f96p_low;}
  inline virtual Int_t       Get96p_up()    { return f96p_up; }
  inline virtual Int_t       Get97p_low()   { return f97p_low;}
  inline virtual Int_t       Get97p_up()    { return f97p_up; }
  inline virtual Int_t       Get98e_low()   { return f98e_low;}
  inline virtual Int_t       Get98e_up()    { return f98e_up; }
  inline virtual Int_t       Get99e_low()   { return f99e_low;}
  inline virtual Int_t       Get99e_up()    { return f99e_up; }
  inline virtual Int_t       Get99p_low()   { return f99p_low;}
  inline virtual Int_t       Get99p_up()    { return f99p_up; }
  inline virtual Int_t       Get00p_low()   { return f00p_low;}
  inline virtual Int_t       Get00p_up()    { return f00p_up; }
  inline virtual Int_t       Get02p_low()   { return f02p_low;}
  inline virtual Int_t       Get02p_up()    { return f02p_up; }
  inline virtual Int_t       Get03p_low()   { return f03p_low;}
  inline virtual Int_t       Get03p_up()    { return f03p_up; }
  inline virtual Int_t       Get04p_low()   { return f04p_low;}
  inline virtual Int_t       Get04p_up()    { return f04p_up; }
  inline virtual Int_t       Get05e_low()   { return f05e_low;}
  inline virtual Int_t       Get05e_up()    { return f05e_up; }
  inline virtual Int_t       Get06e_low()   { return f06e_low;}
  inline virtual Int_t       Get06e_up()    { return f06e_up; }
  inline virtual Int_t       Get06p_low()   { return f06p_low;}
  inline virtual Int_t       Get06p_up()    { return f06p_up; }
  inline virtual Int_t       Get07p_low()   { return f07p_low;}
  inline virtual Int_t       Get07p_up()    { return f07p_up; }

  inline virtual EZRunPeriod GetRunPeriod() { return fPeriod; } 

  ClassDef(GGeneral,0) // General class for general properties
};

R__EXTERN GGeneral *gGeneral;

#endif
