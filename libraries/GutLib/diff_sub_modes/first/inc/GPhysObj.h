//
// GPhysObj.h
//
// $Author: gutsche $
// $Date: 2004/04/08 09:37:07 $
// $Revision: 1.12 $
//

#ifndef GUT_GPhysObj
#define GUT_GPhysObj

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class TH1D;
class TH2D;
class TLorentzVector;
class TClonesArray;
class GTrack;
class GMuon;
class GJet;
class GMJMatch;
class TString;
class GDIMuon;
class GTriMuon;

class GPhysObj : public TObject {

private:
  
protected:
  Bool_t   fOK; // flag if initialization is successfull

  GPhysObj();
  virtual ~GPhysObj();
  
public:
  virtual Bool_t CreateHistograms();
  virtual Bool_t CreateGeneral();
  virtual Bool_t CreateControl();

  virtual Bool_t Reset();

  virtual Bool_t FillHistos();
  virtual Bool_t FillGeneral();
  virtual Bool_t FillControl();

  virtual Bool_t Do();

  virtual Bool_t Finalize();

  virtual Bool_t GetAllCuts();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  inline virtual Bool_t IsOK() { return fOK; }

  ClassDef(GPhysObj,0) // abstract base class for physics objects
};

#endif
