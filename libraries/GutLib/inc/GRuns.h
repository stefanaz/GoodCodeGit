//
// GRuns.h
//
// $Author: gutsche $
// $Date: 2005/04/11 10:25:19 $
// $Revision: 1.5 $
//

#ifndef GUT_GRuns
#define GUT_GRuns

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

#ifndef GUT_GGeneral
#include <GGeneral.h>
#endif

class GRun;
class TClonesArray;

class GRuns : public GPhysObj {

 private:

  TClonesArray   *fRuns;                                   // array of runs from evtake list
  Int_t           fNRuns;                                  // counter for runs from evtake list
  TClonesArray   *fMVDRuns;                                // array of runs from mvdtake list
  Int_t           fNMVDRuns;                               // counter for runs from mvdtake list

  EZRunPeriod     fPeriod;                                 // period for runs which are currently filled in arrays
  EZRunPeriod     fMVDPeriod;                              // period for mvd runs which are currently filled in arrays

  Int_t           fCurrentRunNumber;                       // current checked run for evtake
  Bool_t          fCurrentRunEvtake;                       // result of evtake for current run
  Int_t           fCurrentMVDRunNumber;                    // current checked run for mvdtake
  Bool_t          fCurrentRunMvdtake;                      // result of mvdtake for current run

  Double_t        fLastAddedLuminosity;                    // has to be substracted again if mvdtake or evtake is activated and activated beamspotcut is kFALSE

  Bool_t          fLumiAddedToHeader;                      // flag if lumi for current run was added to header counter

 public:
  GRuns();
  virtual ~GRuns();

  virtual Bool_t GetAllCuts();

  virtual Bool_t CheckUpgradeRun();
  virtual Bool_t CheckRun();

  virtual Bool_t CheckMvdtake();
  virtual Bool_t CheckEvtake();

  virtual Bool_t InitEvtakeList(EZRunPeriod period);
  virtual Bool_t InitMvdtakeList(EZRunPeriod period);

  virtual Bool_t CheckEvtakeList(Int_t runnr);
  virtual Bool_t CheckMvdtakeList(Int_t runnr);

  virtual GRun* GetRun(Int_t runnummer);
  virtual Int_t GetNRuns() { return fNRuns; }
  virtual TClonesArray* GetRuns() { return fRuns; }


  virtual Bool_t CheckMBTake();
  virtual Bool_t CheckFMUTake();
  virtual Bool_t CheckShiftedVertexRuns();

  virtual Int_t MBTAKE(Int_t run);
  virtual Int_t FMUTAKE(Int_t run);
  virtual Int_t FMUTAKE96(Int_t run);
  virtual Int_t FMUTAKE97(Int_t run);
  virtual Int_t FMUTAKE99(Int_t run);
  virtual Int_t FMUTAKE00(Int_t run);
  virtual Int_t FMUTAKE04(Int_t run);

  inline virtual Double_t GetLastAddedLuminosity() { return fLastAddedLuminosity; }

  TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GRuns,0) // Runs Class for everything which is related only to run information
};

R__EXTERN GRuns *gRuns;

#endif
