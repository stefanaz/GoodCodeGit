//
// GVertex.h
//
// $Author: meyer $
// $Date: 2005/08/30 11:13:30 $
// $Revision: 1.11 $
//

#ifndef GUT_GVertex
#define GUT_GVertex

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GBeamSpot;

class GVertex : public GPhysObj {

 private:

  Bool_t        fZCut;                    // vertex passes z cut
  Bool_t        fXCut;                    // x vertex passes cut to be different than the nominal vertex
  Bool_t        fYCut;                    // y vertex passes cut to be different than the nominal vertex
  Bool_t        fXYCut;                   // vertex passes cut to have a maximal distance from the nominal vertex in the xy plane
  Bool_t        fBeamSpotCut;             // event has beam spot

  Double_t      fRedprm_X;                // x-coordinate of reduced prim. vtx
  Double_t      fRedprm_Y;                // y-coordinate of reduced prim. vtx
  Double_t      fRedprm_Z;                // z-coordinate of reduced prim. vtx
  Double_t      fRedprm_Chi2;             // chi2 of reduced prim. vtx
  Double_t      fRedprm_Cov1;             // 1st element of covariant matrix of reduced prim. vtx
  Double_t      fRedprm_Cov2;             // 2nd element of covariant matrix of reduced prim. vtx
  Double_t      fRedprm_Cov3;             // 3rd element of covariant matrix of reduced prim. vtx
  Double_t      fRedprm_Cov4;             // 4th element of covariant matrix of reduced prim. vtx
  Double_t      fRedprm_Cov5;             // 5th element of covariant matrix of reduced prim. vtx
  Double_t      fRedprm_Cov6;             // 6th element of covariant matrix of reduced prim. vtx
  Double_t      fRedprm_Ndof;             // ndof of reduced prim. vtx
  Int_t         fNr_secvtx;               // number of sec. vtx (for each jet/axis --> 1 sec. vtx)
  Double_t      fSecvtx_X;                // x-coordinate of sec. vtx
  Double_t      fSecvtx_Y;                // y-coordinate of sec. vtx
  Double_t      fSecvtx_Z;                // z-coordinate of sec. vtx
  Double_t      fSecvtx_Mass;             // inv mass of sec. vtx
  Double_t      fSecvtx_Chi2;             // chi2 of sec. vtx
  Double_t      fSecvtx_Ndof;             // ndof of sec. vtx
  Int_t         fSecvtx_Multi;            // multiplicity in sec. vtx (nr. of fitted trks)
  Double_t      fSecvtx_Cov1;             // 1st element of covariant matrix of sec. vtx
  Double_t      fSecvtx_Cov2;             // 2nd element of covariant matrix of sec. vtx
  Double_t      fSecvtx_Cov3;             // 3rd element of covariant matrix of sec. vtx
  Double_t      fSecvtx_Cov4;             // 4th element of covariant matrix of sec. vtx
  Double_t      fSecvtx_Cov5;             // 5th element of covariant matrix of sec. vtx
  Double_t      fSecvtx_Cov6;             // 6th element of covariant matrix of sec. vtx
  Double_t      fSecvtx_DL2;              // Decay length
  Double_t      fSecvtx_DL2_err;          // Decay length error
  Double_t      fSecvtx_DL2_sign;         // Decay length significance
  Double_t      fSecvtx2D_X;              // x-coordinate of sec. vtx 
  Double_t      fSecvtx2D_Y;              // y-coordinate of sec. vtx
  Double_t      fSecvtx2D_Z;              // z-coordinate of sec. vtx
  Double_t      fSecvtx2D_Mass;           // inv mass of sec. vtx
  Double_t      fSecvtx2D_Chi2;           // chi2 of sec. vtx
  Double_t      fSecvtx2D_Ndof;           // ndof of sec. vtx
  Double_t      fSecvtx2D_Cov1;           // 1st element of covariant matrix of sec. vtx
  Double_t      fSecvtx2D_Cov2;           // 2nd element of covariant matrix of sec. vtx
  Double_t      fSecvtx2D_Cov3;           // 3rd element of covariant matrix of sec. vtx
  Double_t      fSecvtx2D_Cov4;           // 4th element of covariant matrix of sec. vtx
  Double_t      fSecvtx2D_Cov5;           // 5th element of covariant matrix of sec. vtx
  Double_t      fSecvtx2D_Cov6;           // 6th element of covariant matrix of sec. vtx

  // uncut control histograms
  TH1D         *fControlX_uncut;          // uncut vertex x position
  TH1D         *fControlY_uncut;          // uncut vertex y position
  TH1D         *fControlZ_uncut;          // uncut vertex z position
  TH1D         *fControlXY_uncut;         // uncut vertex xy position

  TH1D         *fControlRedprm_X_uncut;      // uncut x-coordinate of reduced prim. vtx     
  TH1D         *fControlRedprm_Y_uncut;      // uncut y-coordinate of reduced prim. vtx
  TH1D         *fControlRedprm_Z_uncut;      // uncut z-coordinate of reduced prim. vtx
  TH1D         *fControlRedprm_Chi2_uncut;   // uncut chi2 of reduced prim. vtx
  TH1D         *fControlRedprm_Ndof_uncut;   // uncut ndof of reduced prim. vtx
  TH1D         *fControlNr_secvtx_uncut;     // uncut number of sec. vtx (for each jet/axis --> 1 sec. vtx)
  TH1D         *fControlSecvtx_X_uncut;      // uncut x-coordinate of sec. vtx
  TH1D         *fControlSecvtx_Y_uncut;      // uncut y-coordinate of sec. vtx
  TH1D         *fControlSecvtx_Z_uncut;      // uncut z-coordinate of sec. vtx
  TH1D         *fControlSecvtx_Mass_uncut;   // uncut inv mass of sec. vtx
  TH1D         *fControlSecvtx_Chi2_uncut;   // uncut chi2 of sec. vtx
  TH1D         *fControlSecvtx_Ndof_uncut;   // uncut ndof of sec. vtx
  TH1D         *fControlSecvtx_Multi_uncut;  // uncut multiplicity in sec. vtx (nr. of fitted trks)
  TH1D         *fControlSecvtx_Cov1_uncut;   // uncut Cov1 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov2_uncut;   // uncut Cov2 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov3_uncut;   // uncut Cov3 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov4_uncut;   // uncut Cov4 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov5_uncut;   // uncut Cov5 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov6_uncut;   // uncut Cov6 matrix element in sec.vtx
  TH1D         *fControlSecvtx2D_X_uncut;    // uncut x-coordinate of sec. vtx
  TH1D         *fControlSecvtx2D_Y_uncut;    // uncut y-coordinate of sec. vtx
  TH1D         *fControlSecvtx2D_Z_uncut;    // uncut z-coordinate of sec. vtx
  TH1D         *fControlSecvtx2D_Mass_uncut; // uncut inv mass of sec. vtx
  TH1D         *fControlSecvtx2D_Chi2_uncut; // uncut chi2 of sec. vtx
  TH1D         *fControlSecvtx2D_Ndof_uncut; // uncut ndof of sec. vtx

  TH1D         *fControlXMCTRUE_uncut;    // uncut vertex x position MC true info
  TH1D         *fControlYMCTRUE_uncut;    // uncut vertex y position MC true info
  TH1D         *fControlZMCTRUE_uncut;    // uncut vertex z position MC true info

  // control histograms
  TH1D         *fControlX;                // vertex x position
  TH1D         *fControlY;                // vertex y position
  TH1D         *fControlZ;                // vertex z position
  TH1D         *fControlXY;               // vertex xy position

  TH1D         *fControlRedprm_X;      // x-coordinate of reduced prim. vtx     
  TH1D         *fControlRedprm_Y;      // y-coordinate of reduced prim. vtx
  TH1D         *fControlRedprm_Z;      // z-coordinate of reduced prim. vtx
  TH1D         *fControlRedprm_Chi2;   // chi2 of reduced prim. vtx
  TH1D         *fControlRedprm_Ndof;   // ndof of reduced prim. vtx
  TH1D         *fControlNr_secvtx;     // number of sec. vtx (for each jet/axis --> 1 sec. vtx)
  TH1D         *fControlSecvtx_X;      // x-coordinate of sec. vtx
  TH1D         *fControlSecvtx_Y;      // y-coordinate of sec. vtx
  TH1D         *fControlSecvtx_Z;      // z-coordinate of sec. vtx
  TH1D         *fControlSecvtx_Mass;   // inv mass of sec. vtx
  TH1D         *fControlSecvtx_Chi2;   // chi2 of sec. vtx
  TH1D         *fControlSecvtx_Ndof;   // ndof of sec. vtx
  TH1D         *fControlSecvtx_Multi;  // multiplicity in sec. vtx (nr. of fitted trks)
  TH1D         *fControlSecvtx_Cov1;   // uncut Cov1 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov2;   // uncut Cov2 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov3;   // uncut Cov3 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov4;   // uncut Cov4 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov5;   // uncut Cov5 matrix element in sec.vtx
  TH1D         *fControlSecvtx_Cov6;   // uncut Cov6 matrix element in sec.vtx
  TH1D         *fControlSecvtx2D_X;    // x-coordinate of sec. vtx
  TH1D         *fControlSecvtx2D_Y;    // y-coordinate of sec. vtx
  TH1D         *fControlSecvtx2D_Z;    // z-coordinate of sec. vtx
  TH1D         *fControlSecvtx2D_Mass; // inv mass of sec. vtx
  TH1D         *fControlSecvtx2D_Chi2; // chi2 of sec. vtx
  TH1D         *fControlSecvtx2D_Ndof; // ndof of sec. vtx

  TH1D         *fControlXMCTRUE;          // vertex x position MC true info
  TH1D         *fControlYMCTRUE;          // vertex y position MC true info
  TH1D         *fControlZMCTRUE;          // vertex z position MC true info

  // uncut general histograms
  TH1D         *fGeneralX_uncut;          // uncut vertex x position
  TH1D         *fGeneralY_uncut;          // uncut vertex y position
  TH1D         *fGeneralZ_uncut;          // uncut vertex z position

  TH1D         *fGeneralRedprm_X_uncut;      // uncut x-coordinate of reduced prim. vtx     
  TH1D         *fGeneralRedprm_Y_uncut;      // uncut y-coordinate of reduced prim. vtx
  TH1D         *fGeneralRedprm_Z_uncut;      // uncut z-coordinate of reduced prim. vtx
  TH1D         *fGeneralRedprm_Chi2_uncut;   // uncut chi2 of reduced prim. vtx
  TH1D         *fGeneralRedprm_Ndof_uncut;   // uncut ndof of reduced prim. vtx
  TH1D         *fGeneralNr_secvtx_uncut;     // uncut number of sec. vtx (for each jet/axis --> 1 sec. vtx)
  TH1D         *fGeneralSecvtx_X_uncut;      // uncut x-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx_Y_uncut;      // uncut y-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx_Z_uncut;      // uncut z-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx_Mass_uncut;   // uncut inv mass of sec. vtx
  TH1D         *fGeneralSecvtx_Chi2_uncut;   // uncut chi2 of sec. vtx
  TH1D         *fGeneralSecvtx_Ndof_uncut;   // uncut ndof of sec. vtx
  TH1D         *fGeneralSecvtx_Multi_uncut;  // uncut multiplicity in sec. vtx (nr. of fitted trks)
  TH1D         *fGeneralSecvtx_Cov1_uncut;   // uncut Cov1 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov2_uncut;   // uncut Cov2 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov3_uncut;   // uncut Cov3 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov4_uncut;   // uncut Cov4 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov5_uncut;   // uncut Cov5 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov6_uncut;   // uncut Cov6 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx2D_X_uncut;    // uncut x-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx2D_Y_uncut;    // uncut y-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx2D_Z_uncut;    // uncut z-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx2D_Mass_uncut; // uncut inv mass of sec. vtx
  TH1D         *fGeneralSecvtx2D_Chi2_uncut; // uncut chi2 of sec. vtx
  TH1D         *fGeneralSecvtx2D_Ndof_uncut; // uncut ndof of sec. vtx

  TH1D         *fGeneralXMCTRUE_uncut;    // uncut vertex x position MC true info
  TH1D         *fGeneralYMCTRUE_uncut;    // uncut vertex y position MC true info
  TH1D         *fGeneralZMCTRUE_uncut;    // uncut vertex z position MC true info

  // general histograms
  TH1D         *fGeneralX;                // vertex x position
  TH1D         *fGeneralY;                // vertex y position
  TH1D         *fGeneralZ;                // vertex z position

  TH1D         *fGeneralRedprm_X;      // x-coordinate of reduced prim. vtx     
  TH1D         *fGeneralRedprm_Y;      // y-coordinate of reduced prim. vtx
  TH1D         *fGeneralRedprm_Z;      // z-coordinate of reduced prim. vtx
  TH1D         *fGeneralRedprm_Chi2;   // chi2 of reduced prim. vtx
  TH1D         *fGeneralRedprm_Ndof;   // ndof of reduced prim. vtx
  TH1D         *fGeneralNr_secvtx;     // number of sec. vtx (for each jet/axis --> 1 sec. vtx)
  TH1D         *fGeneralSecvtx_X;      // x-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx_Y;      // y-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx_Z;      // z-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx_Mass;   // inv mass of sec. vtx
  TH1D         *fGeneralSecvtx_Chi2;   // chi2 of sec. vtx
  TH1D         *fGeneralSecvtx_Ndof;   // ndof of sec. vtx
  TH1D         *fGeneralSecvtx_Multi;  // multiplicity in sec. vtx (nr. of fitted trks)
  TH1D         *fGeneralSecvtx_Cov1;   // uncut Cov1 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov2;   // uncut Cov2 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov3;   // uncut Cov3 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov4;   // uncut Cov4 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov5;   // uncut Cov5 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx_Cov6;   // uncut Cov6 matrix element in sec.vtx
  TH1D         *fGeneralSecvtx2D_X;    // x-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx2D_Y;    // y-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx2D_Z;    // z-coordinate of sec. vtx
  TH1D         *fGeneralSecvtx2D_Mass; // inv mass of sec. vtx
  TH1D         *fGeneralSecvtx2D_Chi2; // chi2 of sec. vtx
  TH1D         *fGeneralSecvtx2D_Ndof; // ndof of sec. vtx

  TH1D         *fGeneralXMCTRUE;          // vertex x position MC true info
  TH1D         *fGeneralYMCTRUE;          // vertex y position MC true info
  TH1D         *fGeneralZMCTRUE;          // vertex z position MC true info

  // beamspot array
  TClonesArray *fBeamSpots;               // array of beamspots
  Int_t         fNBeamSpots;              // number of beam spots

  // beamspot variables
  GBeamSpot    *fCurrentBeamSpot;         // current data beamspot object
  GBeamSpot    *fEventBeamSpot;         // current event beamspot object
  GBeamSpot    *fMCBeamSpot;              // MC beamspot object
  GBeamSpot    *fLastValidBeamSpot;        // last valid beamspot, to use all mvd take runs

  Int_t         fNoBeamSpotRunnr;         // runnr in case that no beamspot for this run was found

 public:
  GVertex();
  virtual ~GVertex();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();

  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();

  virtual Bool_t Do();

  virtual Bool_t Reset();

  virtual Bool_t GetAllCuts();

  virtual Bool_t CheckZCut();
  virtual Bool_t CheckXCut();
  virtual Bool_t CheckYCut();
  virtual Bool_t CheckXYCut();
  virtual Bool_t CalcSecVTX();
  virtual Bool_t CheckBeamSpotCut();

  TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  inline virtual Bool_t     GetZCut()                { return fZCut;            }
  inline virtual Bool_t     GetXCut()                { return fXCut;            }
  inline virtual Bool_t     GetYCut()                { return fYCut;            }
  inline virtual Bool_t     GetXYCut()               { return fXYCut;           }
  inline virtual Bool_t     GetBeamSpotCut()         { return fBeamSpotCut;     }

  inline virtual Bool_t     GetVtxMass()             { return fSecvtx_Mass;  }
  inline virtual Bool_t     GetChi2()                { return fSecvtx_Chi2;  }
  inline virtual Bool_t     GetNdof()                { return fSecvtx_Ndof;  }
  inline virtual Bool_t     GetMulti()               { return fSecvtx_Multi; }
  inline virtual Bool_t     GetNrsecVtx()            { return fNr_secvtx;    }
  inline virtual Bool_t     GetCov1()                { return fSecvtx_Cov1;  }
  inline virtual Bool_t     GetCov2()                { return fSecvtx_Cov2;  }
  inline virtual Bool_t     GetCov3()                { return fSecvtx_Cov3;  }
  inline virtual Bool_t     GetCov4()                { return fSecvtx_Cov4;  }
  inline virtual Bool_t     GetCov5()                { return fSecvtx_Cov5;  }
  inline virtual Bool_t     GetCov6()                { return fSecvtx_Cov6;  }
  inline virtual Bool_t     GetDL2()                 { return fSecvtx_DL2;   }
  inline virtual Bool_t     GetDL2err()              { return fSecvtx_DL2_err;  }
  inline virtual Bool_t     GetDL2sign()             { return fSecvtx_DL2_sign; }



  virtual GBeamSpot* GetCurrentBeamSpot();

  virtual GBeamSpot* CheckCurrentBeamSpot();
  virtual GBeamSpot* CheckEventBeamSpot();  
  virtual GBeamSpot* GetEventBeamSpot();  
  virtual Bool_t InitBeamSpotList();

  ClassDef(GVertex,0) // Vertex Class for everything which is related only to Vertices
};

R__EXTERN GVertex *gVertex;

#endif
