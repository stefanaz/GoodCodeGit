//
// GCal.h
//
// $Author: ibloch $
// $Date: 2005/04/26 10:30:15 $
// $Revision: 1.21 $
//

#ifndef GUT_GCal
#define GUT_GCal

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GCal : public GPhysObj {

private:
  
  Double_t             fEmpz;                       // E-p_z
  Double_t             fPt;                         // p_t
  Double_t             fYJB;                        // y_jb
  Double_t             fPtOvEt;                     // Pt/Et
  Double_t             fETtocuton;                  // proton splash + electron corrected cal_et

  Bool_t               fYJBCut;                     // cut on y_jb
  Bool_t               fETCut;                      // cut on E_T minus 2 inner rings
  Bool_t               fPtOvEtCut;                  // cut on Pt/Et
  Bool_t               fTimeCut;                    // cut on cal_tg

  // general cal histos
  TH1D                *fGeneralpx;                  // cal x momentum
  TH1D                *fGeneralpy;                  // cal y momentum
  TH1D                *fGeneralpz;                  // cal z momentum
  TH1D                *fGeneralE;                   // cal Energy
  TH1D                *fGeneralEt;                  // cal transverse Energy
  TH1D                *fGeneralEtex2ir;             // cal transverse Energy minus et from 2 inner cal rings (self calculated)
  TH1D                *fGeneralEtex2irOrange;       // cal transverse Energy minus et from 2 inner cal rings (calculated by orange)
  TH1D                *fGeneralEmpz;                // cal E - p_z
  TH1D                *fGeneralPt;                  // cal transvers momentum
  TH1D                *fGeneralPtOvEt;              // cal Pt/Et
  TH1D                *fGeneralYJB;                 // y_jb distribution
  TH2D                *fGeneralYJBvsYTrue;          // YJB zufo vs. YTrue MC

  TH1D                *fGeneralcal_tg;                  // cal timing

  TH1D                *fGeneralYJB_uncut;           // uncut y_jb distribution
  TH1D                *fGeneralpx_uncut;            // uncut cal x momentum
  TH1D                *fGeneralpy_uncut;            // uncut cal y momentum
  TH1D                *fGeneralpz_uncut;            // uncut cal z momentum
  TH1D                *fGeneralE_uncut;             // uncut cal Energy
  TH1D                *fGeneralEt_uncut;            // uncut cal transverse Energy
  TH1D                *fGeneralEtex2ir_uncut;       // uncut cal transverse Energy minus et from 2 inner cal rings (self calculated)
  TH1D                *fGeneralEtex2irOrange_uncut; // uncut cal transverse Energy minus et from 2 inner cal rings (calculated by orange)
  TH1D                *fGeneralEmpz_uncut;          // uncut cal E - p_z
  TH1D                *fGeneralPt_uncut;            // uncut cal transvers momentum
  TH1D                *fGeneralPtOvEt_uncut;        // uncut cal Pt/Et
  TH2D                *fGeneralYJBvsYTrue_uncut;    // uncut YJB zufo vs. YTrue MC

  TH1D                *fGeneralcal_tg_uncut;            // uncut cal timing

  // control plots
  TH1D                *fControlpx;                  // cal x momentum
  TH1D                *fControlpy;                  // cal y momentum
  TH1D                *fControlpz;                  // cal z momentum
  TH1D                *fControlE;                   // cal Energy
  TH1D                *fControlEt;                  // cal transverse energy minus 2 inner rings
  TH1D                *fControlEmpz;                // cal E - p_z
  TH1D                *fControlPt;                  // cal transvers momentum
  TH1D                *fControlPtOvEt;              // cal Pt/Et
  TH1D                *fControlYJB;                 // control y_jb distribution
  TH1D                *fControlTime;                // control cal_tg distribution

  TH1D                *fControlpx_uncut;            // uncut cal x momentum
  TH1D                *fControlpy_uncut;            // uncut cal y momentum
  TH1D                *fControlpz_uncut;            // uncut cal z momentum
  TH1D                *fControlE_uncut;             // uncut cal Energy
  TH1D                *fControlEt_uncut;            // uncut cal transverse energy minus 2 inner rings
  TH1D                *fControlEmpz_uncut;          // uncut cal E - p_z
  TH1D                *fControlPt_uncut;            // uncut cal transvers momentum
  TH1D                *fControlPtOvEt_uncut;        // uncut cal Pt/Et
  TH1D                *fControlYJB_uncut;           // uncut control y_jb distribution
  TH1D                *fControlTime_uncut;          // uncut control cal_tg distribution

public:
  GCal();
  virtual ~GCal();

  virtual Bool_t CreateGeneral();
  virtual Bool_t CreateControl();
  virtual Bool_t FillGeneral();
  virtual Bool_t FillControl();

  virtual Bool_t Do();

  virtual Bool_t Calc();

  virtual Bool_t CheckYJBCut();
  virtual Bool_t CheckETCut();
  virtual Bool_t CheckPtOvEtCut();
  virtual Bool_t CheckTimeCut();

  inline virtual Bool_t GetYJBCut()      { return fYJBCut;    }
  inline virtual Bool_t GetETCut()       { return fETCut;     }
  inline virtual Bool_t GetPtOvEtCut()   { return fPtOvEtCut; }
  inline virtual Bool_t GetTimeCut()     { return fTimeCut;   }
  inline virtual Double_t GetEmpz()      { return fEmpz;      }
  inline virtual Double_t GetETtocuton() { return fETtocuton; }

  virtual Bool_t Reset();

  virtual Bool_t GetAllCuts();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GCal,0) // Cal class for everything which is related only to CAL
};

R__EXTERN GCal *gCal;

#endif
