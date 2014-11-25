//
// GBac.h
//
// $Author: ibloch $
// $Date: 2004/05/27 13:40:54 $
// $Revision: 1.1 $
//

#ifndef GUT_GBac
#define GUT_GBac

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GBac : public GPhysObj {

private:
  
  //  Double_t             fbac_etot;                       // bac_etot total bac energy
  //  Double_t             fnbacmu;                         // nbacmu number of muons rec. in BAC

  Bool_t               fbac_etotCut;                    // 
  Bool_t               fnbacmuCut;                      // 

  // general bac histos
  TH1D                *fGeneralbac_etot;                  // bac_etot
  TH1D                *fGeneralnbacmu;                    // nbacmu

  TH1D                *fGeneralbac_etot_uncut;           // uncut bac_etot distribution
  TH1D                *fGeneralnbacmu_uncut;             // uncut nbacmu distribution

  // control plots
  TH1D                *fControlbac_etot;                  // bac_etot
  TH1D                *fControlnbacmu;                    // nbacmu

  TH1D                *fControlbac_etot_uncut;            // uncut bac_etot
  TH1D                *fControlnbacmu_uncut;              // uncut nbacmu

public:
  GBac();
  virtual ~GBac();

  virtual Bool_t CreateGeneral();
  virtual Bool_t CreateControl();
  virtual Bool_t FillGeneral();
  virtual Bool_t FillControl();

  virtual Bool_t Do();

  //  virtual Bool_t Calc();

  virtual Bool_t Checkbac_etotCut();
  virtual Bool_t ChecknbacmuCut();

  inline virtual Bool_t Getbac_etotCut()      { return fbac_etotCut;    }
  inline virtual Bool_t GetnbacmuCut()        { return fnbacmuCut;      }

  virtual Bool_t Reset();

  virtual Bool_t GetAllCuts();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GBac,0) // Bac class for everything which is related only to BAC
};

R__EXTERN GBac *gBac;

#endif
