//
// GZufo.h
//
// $Author: gutsche $
// $Date: 2005/02/07 12:52:00 $
// $Revision: 1.16 $
//

#ifndef GUT_GZufo
#define GUT_GZufo

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

#ifndef ROOT_TVector3
#include <TVector3.h>
#endif


class GZufo : public GPhysObj {

 private:

  Double_t             fPt_had;                    // p_T from had zufo properties
  Double_t             fEmpz_had;                  // empz from had zufo properties
  Double_t             fYJB_had;                   // yjb from had zufo properties
  Double_t             fQ2JB_had;                  // Q2jb from had zufo properties
  Double_t             fRapid_Y;                   // Rapidity Y of whole System from had zufo properties
  Double_t             fQ2Prime;                   // Q2' from had zufo properties
  Double_t             fZufoPt;                    // Zufo Pt in Instanton Band
  Double_t             fZufoEta;                   // Zufo Eta in Instanton Band

  Bool_t               fYJBCut;                    // flag for yjb cut
  Bool_t               fEmpzCut;                   // flag for Empz cut
  Bool_t               fPtHadMaxCut;               // cut on max of PtHad
  Bool_t               fQ2PrimeLowCut;             // Cut on Q'2 for eventshape variables

  Double_t             fdelta_R_muzu;              // delta R between muon and zufo
  Double_t             fdelta_R_muzumin;           // minimal vallue of above var. rel to all zufoses
  Double_t             fzufo_ptmin;                // minimal zufo pt
  Int_t                ftufocode;                  // tufo info: 1: means zufo contains 1 track, 1 island. usees CTD
  static const Int_t   fnbins_iso = 10;            // bins used for the muon isolation
  Double_t             fmuis[fnbins_iso];          // array of muon isolations
  Double_t             fmuissum[fnbins_iso];       // array of dimuon summed isolations
  Double_t             fmuissqsum[fnbins_iso];     // array of dimuon sqared summed isolations
  Bool_t               fzufo_perhaps_muon;         // flag to set, if zufo seems to be the muon zufo

  Double_t             fthrust;                     // thrust calculated for chosen event
  TVector3             fthrust_axis1;               // thrust axis
  TVector3             fthrust_axis2;               // thrust axis
  Double_t             fthrust_axis_phi;            // thrust axis phi
  Double_t             fthrust_axis_theta1;         // thrust axis theta
  Double_t             fthrust_axis_theta2;         // thrust axis theta

  Double_t             fsphericity;                 // Sphericity calculated for chosen event  
  Double_t             fisotropy;                   // Isotropy of Instanton - Band calculated for chosen event
  Double_t             fmultiplicity;               // Multiplicity in Instanton - Band calculated for chosen event
  /*
  Double_t             fQ2Prime_True;
  Double_t             fHadronPt_True;
  Double_t             fHadronEta_True;
  Double_t             fsphericity_True;
  Double_t             fisotropy_True;
  Double_t             fmultiplicity_True;
  */
  // general histograms
  TH1D                *fGeneraln_uncut;            // uncut number of zufos
  TH1D                *fGeneralpx_uncut;           // uncut zufo x momentum
  TH1D                *fGeneralpy_uncut;           // uncut zufo y momentum
  TH1D                *fGeneralpz_uncut;           // uncut zufo z momentum
  TH1D                *fGeneralp_uncut;            // uncut zufo momentum
  TH1D                *fGeneralpt_uncut;           // uncut zufo t momentum
  TH1D                *fGeneralE_uncut;            // uncut zufo energy
  TH1D                *fGeneralYJB_had_uncut;      // uncut y_jb distribution
  TH1D                *fGeneralpx_had_uncut;       // uncut had x momentum
  TH1D                *fGeneralpy_had_uncut;       // uncut had y momentum
  TH1D                *fGeneralpz_had_uncut;       // uncut had z momentum
  TH1D                *fGeneralE_had_uncut;        // uncut had Energy
  TH1D                *fGeneralEmpz_had_uncut;     // uncut had E - p_z
  TH1D                *fGeneralPt_had_uncut;       // uncut had transvers momentum
  TH2D                *fGeneralYJBvsYTrue_uncut;   // uncut YJB zufo vs. YTrue MC

  TH1D                *fGeneraln;                  // zufo number of zufos
  TH1D                *fGeneralpx;                 // zufo x momentum
  TH1D                *fGeneralpy;                 // zufo y momentum
  TH1D                *fGeneralpz;                 // zufo z momentum
  TH1D                *fGeneralp;                  // zufo momentum
  TH1D                *fGeneralpt;                 // zufo t momentum
  TH1D                *fGeneralE;                  // zufo energy
  TH1D                *fGeneralpx_had;             // had x momentum
  TH1D                *fGeneralpy_had;             // had y momentum
  TH1D                *fGeneralpz_had;             // had z momentum
  TH1D                *fGeneralE_had;              // had Energy
  TH1D                *fGeneralEmpz_had;           // had E - p_z
  TH1D                *fGeneralPt_had;             // had transvers momentum
  TH1D                *fGeneralYJB_had;            // y_jb distribution
  TH1D                *fGeneralQ2JB_had_1;         // Q2_jb distribution for only the trigger selection
  TH1D                *fGeneralQ2JB_had_2;         // Q2_jb distribution for only the trigger selection and sinistra selection
  TH1D                *fGeneralQ2JB_had_3;         // Q2_jb distribution for only the trigger selection and sinistra and yjb cut
  TH1D                *fGeneralQ2JB_had;           // Q2_jb distribution
  TH1D                *fGeneralYJBMinYTrue;        // (y_jb-y_true)/y_true distribution
  TH2D                *fGeneralYJBvsYTrue;         // YJB zufo vs. YTrue MC

  // control histograms
  TH1D                *fControln_uncut;            // uncut number of zufos
  TH1D                *fControlpx_uncut;           // uncut zufo x momentum
  TH1D                *fControlpy_uncut;           // uncut zufo y momentum
  TH1D                *fControlpz_uncut;           // uncut zufo z momentum
  TH1D                *fControlp_uncut;            // uncut zufo momentum
  TH1D                *fControlpt_uncut;           // uncut zufo t momentum
  TH1D                *fControlE_uncut;            // uncut zufo energy
  TH1D                *fControlpx_had_uncut;       // uncut had x momentum
  TH1D                *fControlpy_had_uncut;       // uncut had y momentum
  TH1D                *fControlpz_had_uncut;       // uncut had z momentum
  TH1D                *fControlE_had_uncut;        // uncut had Energy
  TH1D                *fControlEmpz_had_uncut;     // uncut had E - p_z
  TH1D                *fControlPt_had_uncut;       // uncut had transvers momentum
  TH1D                *fControlYJB_had_uncut;      // uncut control y_jb distribution

  TH1D                *fControln;                  // zufo number of zufos
  TH1D                *fControlpx;                 // zufo x momentum
  TH1D                *fControlpy;                 // zufo y momentum
  TH1D                *fControlpz;                 // zufo z momentum
  TH1D                *fControlp;                  // zufo momentum
  TH1D                *fControlpt;                 // zufo t momentum
  TH1D                *fControlE;                  // zufo energy
  TH1D                *fControlpx_had;             // had x momentum
  TH1D                *fControlpy_had;             // had y momentum
  TH1D                *fControlpz_had;             // had z momentum
  TH1D                *fControlE_had;              // had Energy
  TH1D                *fControlEmpz_had;           // had E - p_z
  TH1D                *fControlPt_had;             // had transvers momentum
  TH1D                *fControlYJB_had;            // control y_jb distribution

  TH1D                *fControlTUFO_First;         // tufo[0,i]
  TH1D                *fControlTUFO_Second;        // tufo[1,i]
  TH1D                *fControlTUFO_Third;         // tufo[2,i]
  TH1D                *fControlTUFO_Fourth;        // tufo[3,i]

 public:
  GZufo();
  virtual ~GZufo();

  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();

  virtual Bool_t Do();

  virtual Bool_t Calc();
  Bool_t CalcIsolation(GMuon *muon);
  Bool_t CalcIsolation(GDIMuon *dimuon);
  Bool_t CalcIsolation(GTriMuon *trimuon);

  Bool_t   CalcThrust();
  Bool_t   CalcInstantonVariables(GDIMuon *dimuon);
  //  Bool_t   CalcInstantonVariables_True();
  Double_t ffind_thrust_axis(Double_t * thrust_axis_phi, Double_t * thrust_axis_theta1, Double_t * thrust_axis_theta2, Double_t * thrust);
  Double_t fcalc_thrust_NN(Double_t * thrust_axis_phi, Double_t * thrust_axis_theta, Double_t * fliptheta, Int_t mode = 0);

  virtual Bool_t CheckYJBCut();
  virtual Bool_t CheckEmpzCut();
  virtual Bool_t CheckPtHadMaxCut();

  inline virtual Bool_t     GetYJBCut()                { return fYJBCut;             }
  inline virtual Bool_t     GetEmpzCut()               { return fEmpzCut;            }
  inline virtual Bool_t     GetPtHadMaxCut()           { return fPtHadMaxCut;        }
  inline virtual Bool_t     GetQ2PrimeLowCut()         { return fQ2PrimeLowCut;      }

  inline virtual Double_t   GetEmpz_had()              { return fEmpz_had;           }
  inline virtual Double_t   GetYJB_had()               { return fYJB_had;            }
  inline virtual Double_t   GetQ2JB_had()              { return fQ2JB_had;           }
  inline virtual Double_t   GetQ2Prime()               { return fQ2Prime;            }
  inline virtual Double_t   GetZufoPt()                { return fZufoPt;             }
  inline virtual Double_t   GetZufoEta()               { return fZufoEta;            }

  inline virtual Double_t   GetThrust()                { return fthrust;             }
  inline virtual TVector3   Getthrust_axis1()          { return fthrust_axis1;	     }
  inline virtual TVector3   Getthrust_axis2()          { return fthrust_axis2;	     }
  inline virtual Double_t   Getthrust_axis_phi()       { return fthrust_axis_phi;    }
  inline virtual Double_t   Getthrust_axis_phi1()      { return fthrust_axis_phi;    }
  inline virtual Double_t   Getthrust_axis_phi2()      { return fthrust_axis_phi;    }
  inline virtual Double_t   Getthrust_axis_theta1()    { return fthrust_axis_theta1; }
  inline virtual Double_t   Getthrust_axis_theta2()    { return fthrust_axis_theta2; }

  inline virtual Double_t   GetSphericity()            { return fsphericity;         }
  inline virtual Double_t   GetIsotropy()              { return fisotropy;           }
  inline virtual Double_t   GetMultiplicity()          { return fmultiplicity;       }
  /*
  inline virtual Double_t   GetTrueQ2Prime()           { return fQ2Prime_True;       }
  inline virtual Double_t   GetTrueSphericity()        { return fsphericity_True;    }
  inline virtual Double_t   GetTrueIsotropy()          { return fisotropy_True;      }
  inline virtual Double_t   GetTrueMultiplicity()      { return fmultiplicity_True;  }
  */


  virtual Bool_t Reset();

  virtual Bool_t GetAllCuts();

  TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GZufo,0) // Zufo class for everything which is related only to ZUFOs
};

R__EXTERN GZufo *gZufo;

#endif
