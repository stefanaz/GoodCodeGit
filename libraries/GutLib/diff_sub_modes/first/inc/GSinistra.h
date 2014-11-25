//
// GSinistra.h
//
// $Author: kahle $
// $Date: 2005/04/07 15:30:23 $
// $Revision: 1.23 $
//

#ifndef GUT_GSinistra
#define GUT_GSinistra

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GSinistra : public GPhysObj {

 private:

  Double_t             fY;                    // y_el if sinistra candidate, else -9999.99
  Double_t             fX;                    // x_el if sinistra candidate, else -9999.99
  Double_t             fXlog;                 // log10(x_el) if sinistra candidate found, else -9999.99
  Double_t             fThetaE;               // ThetaE if sinistra candidate, else -9999.99
  Double_t             fQ2;                   // q2_el if sinistra candidate, else -9999.99
  Double_t             fQ2log;                // log10(q2_el) if sinistra candidate, else -9999.99
  Double_t             fXpos;                 // X position of sinistra candidate, else -9999.99
  Double_t             fYpos;                 // X position of sinistra candidate, else -9999.99

  
  Bool_t               fEEnergyCut;             // cut on electron energy
  Bool_t               fYELCut;                 // cut on y_el
  Bool_t               fSiNCandCut;             // cut on sinistra electron
  Bool_t               fBoxCut;                 // cut on X and Y position
  Bool_t               fQ2LowCut;               // cut on Q2_el
  Double_t             fEmpz_had;               // empz from had ZUFO
  Bool_t               fEmpzCut;                // flag for Empz cut ZUFO


  // sinistra general plots
  TH1D                *fGeneralYEL_uncut;       // y_el general plot for sinistra electrons fulfilling cut on E_el 
  TH1D                *fGeneralYEL;             // y_el general plot for sinistra electrons
  TH1D                *fGeneralEE_uncut;        // E_el general plot for sinistra electrons fulfilling cut on y_el
  TH1D                *fGeneralEE;              // E_el general plot for sinistra electrons
  TH1D                *fGeneralXlog;            // log X general plot for sinistra electrons
  TH1D                *fGeneralThetaE_uncut;    // ThetaE general plot for sinistra electrons
  TH1D                *fGeneralThetaE;          // ThetaE general plot for sinistra electrons
  TH1D                *fGeneralThetaE_0_10_uncut;      // ThetaE general plot for sinistra electrons Q2<10
  TH1D                *fGeneralThetaE_0_10;            // ThetaE general plot for sinistra electrons Q2<10
  TH1D                *fGeneralThetaE_10_200_uncut;    // ThetaE general plot for sinistra electrons 10<Q2<200
  TH1D                *fGeneralThetaE_10_200;          // ThetaE general plot for sinistra electrons 10<Q2<200
  TH1D                *fGeneralThetaE_200_uncut;       // ThetaE general plot for sinistra electrons 200<Q2
  TH1D                *fGeneralThetaE_200;             // ThetaE general plot for sinistra electrons 200<Q2
  TH1D                *fGeneralQ2;              // Q_el general plot for sinistra electrons fulfilling all sinista cuts
  TH1D                *fGeneralQ2_uncut;        // Q_el general plot for sinistra electrons
  TH1D                *fGeneralQ2log;           // Q_el general plot for sinistra electrons fulfilling all sinista cuts
  TH1D                *fGeneralQ2log_uncut;     // Q_el general plot for sinistra electrons
  TH2D                *fGeneralQ2x;             // Q_el vs X general plot for sinistra electrons
  TH2D                *fGeneralQ2x_uncut;       // Q_el vs X general uncut plot for sinistra electrons
  TH2D                *fGeneralXY;              // X- vs Y-position  general plot for sinistra electrons
  TH2D                *fGeneralXY_uncut;        // X- vs Y-position  general uncut plot for sinistra electrons

/*   TH1D                *fGeneraldimuphi_uncut; */
/*   TH1D                *fGeneraldimuphi_lu_is_uncut; */
/*   TH1D                *fGeneraldimuphi_ll_is_uncut; */
/*   TH1D                *fGeneraldimuphi_hu_is_uncut; */
/*   TH1D                *fGeneraldimuphi_hl_is_uncut; */
/*   TH1D                *fGeneraldimuphi_lu_nis_uncut; */
/*   TH1D                *fGeneraldimuphi_ll_nis_uncut; */
/*   TH1D                *fGeneraldimuphi_hu_nis_uncut; */
/*   TH1D                *fGeneraldimuphi_hl_nis_uncut; */

  TH1D                *fGeneraldimuq2si_uncut;
  TH1D                *fGeneraldimuq2si_lu_is_uncut;
  TH1D                *fGeneraldimuq2si_ll_is_uncut;
  TH1D                *fGeneraldimuq2si_hu_is_uncut;
  TH1D                *fGeneraldimuq2si_hl_is_uncut;
  TH1D                *fGeneraldimuq2si_lu_nis_uncut;
  TH1D                *fGeneraldimuq2si_ll_nis_uncut;
  TH1D                *fGeneraldimuq2si_hu_nis_uncut;
  TH1D                *fGeneraldimuq2si_hl_nis_uncut;

  TH1D                *fGeneraldimulog10q2si_uncut;
  TH1D                *fGeneraldimulog10q2si_lu_is_uncut;
  TH1D                *fGeneraldimulog10q2si_ll_is_uncut;
  TH1D                *fGeneraldimulog10q2si_hu_is_uncut;
  TH1D                *fGeneraldimulog10q2si_hl_is_uncut;
  TH1D                *fGeneraldimulog10q2si_lu_nis_uncut;
  TH1D                *fGeneraldimulog10q2si_ll_nis_uncut;
  TH1D                *fGeneraldimulog10q2si_hu_nis_uncut;
  TH1D                *fGeneraldimulog10q2si_hl_nis_uncut;

/*   TH1D                *fGeneraldimuphi; */
/*   TH1D                *fGeneraldimuphi_lu_is; */
/*   TH1D                *fGeneraldimuphi_ll_is; */
/*   TH1D                *fGeneraldimuphi_hu_is; */
/*   TH1D                *fGeneraldimuphi_hl_is; */
/*   TH1D                *fGeneraldimuphi_lu_nis; */
/*   TH1D                *fGeneraldimuphi_ll_nis; */
/*   TH1D                *fGeneraldimuphi_hu_nis; */
/*   TH1D                *fGeneraldimuphi_hl_nis; */

  TH1D                *fGeneraldimuq2si;
  TH1D                *fGeneraldimuq2si_lu_is;
  TH1D                *fGeneraldimuq2si_ll_is;
  TH1D                *fGeneraldimuq2si_hu_is;
  TH1D                *fGeneraldimuq2si_hl_is;
  TH1D                *fGeneraldimuq2si_lu_nis;
  TH1D                *fGeneraldimuq2si_ll_nis;
  TH1D                *fGeneraldimuq2si_hu_nis;
  TH1D                *fGeneraldimuq2si_hl_nis;

  TH1D                *fGeneraldimulog10q2si;
  TH1D                *fGeneraldimulog10q2si_lu_is;
  TH1D                *fGeneraldimulog10q2si_ll_is;
  TH1D                *fGeneraldimulog10q2si_hu_is;
  TH1D                *fGeneraldimulog10q2si_hl_is;
  TH1D                *fGeneraldimulog10q2si_lu_nis;
  TH1D                *fGeneraldimulog10q2si_ll_nis;
  TH1D                *fGeneraldimulog10q2si_hu_nis;
  TH1D                *fGeneraldimulog10q2si_hl_nis;

  // sinistra control plots
  TH1D                *fControlYEL_uncut;       // y_el control plot for sinistra electrons fulfilling cut on E_el 
  TH1D                *fControlYEL;             // y_el control plot for sinistra electrons fulfilling cut on E_el and y_el
  TH1D                *fControlEE_uncut;        // E_el control plot for sinistra electrons fulfilling cut on y_el
  TH1D                *fControlEE;              // E_el control plot for sinistra electrons fulfilling cut on y_el and E_el
  TH1D                *fControlSiNCand_uncut;   // uncut electron candidate control plot
  TH1D                *fControlSiNCand;         // electron candidate control plot
  TH1D                *fControlQ2log;           // electron Q2 control plot
  TH1D                *fControlQ2log_uncut;     // electron Q2 control plot

 public:
  GSinistra();
  virtual ~GSinistra();

  virtual Bool_t CreateControl();
  virtual Bool_t CreateGeneral();
  virtual Bool_t FillControl();
  virtual Bool_t FillGeneral();


  virtual Bool_t Errors();
  virtual Bool_t YELCheck();
  virtual Bool_t Q2Check();
  virtual Bool_t BoxCheck();
  virtual Bool_t EEnergyCheck();
  virtual Bool_t SiNCandCheck();
  virtual Bool_t CheckEmpzCut();

  virtual Bool_t Do();

  virtual Bool_t Reset();
  
  virtual Bool_t GetAllCuts();

  virtual Bool_t GetDISRemovalCut();

  virtual Bool_t GetDISSelectionCut();

  virtual Int_t GetDISPHPCut();

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  inline virtual Bool_t   GetEEnergyCut() { return fEEnergyCut; }
  inline virtual Bool_t   GetYELCut()     { return fYELCut;     }
  inline virtual Bool_t   GetSiNCandCut() { return fSiNCandCut; }
  inline virtual Bool_t   GetQ2LowCut()   { return fQ2LowCut;   }
  inline virtual Bool_t   GetBoxCut()     { return fBoxCut;     }
  inline virtual Double_t GetX()          { return fX;          }
  inline virtual Double_t GetXlog()       { return fXlog;       }
  inline virtual Double_t GetY()          { return fY;          }
  inline virtual Double_t GetQ2()         { return fQ2;         }
  inline virtual Double_t GetXpos()       { return fXpos;       }
  inline virtual Double_t GetYpos()       { return fYpos;       }
  inline virtual Bool_t   GetEmpzCut()    { return fEmpzCut;    }
  inline virtual Double_t GetEmpz_had()   { return fEmpz_had;   }
  inline virtual Double_t GetThetaE()     { return fThetaE;     }
 
  ClassDef(GSinistra,0) //Sinistra class for everything which is related only to sinistra
};

R__EXTERN GSinistra *gSinistra;

#endif




