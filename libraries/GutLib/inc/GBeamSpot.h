//
// GBeamSpot.h
//
// $Author: meyer $
// $Date: 2005/08/30 11:13:30 $
// $Revision: 1.4 $
//

#ifndef GUT_GBeamSpot
#define GUT_GBeamSpot

#ifndef ROOT_TVector3
#include <TVector3.h>
#endif

class TString;

#include <iostream>

using namespace std;

class GBeamSpot : public TVector3 {

private:

  Int_t    fRun;           // run number
  Int_t    fEvents;        // number of events in run
  Double_t fX_Sigma;       // sigma of x of beamspot
  Double_t fY_Sigma;       // sigma of y of beamspot
  Double_t fZ_Sigma;       // sigma of z of beamspot
  Double_t fX0;            //  x0 of beamspot
  Double_t fY0;            //  y0 of beamspot
  Double_t fX0_Sigma;      // sigma of x0 of beamspot
  Double_t fY0_Sigma;      // sigma of y0 of beamspot
  Double_t fDX_DZ;         // x slope  for straight linefit z dependence
  Double_t fDX_DZ_Sigma;   // delta x slope  for straight linefit z dependence
  Double_t fDY_DZ;         // y slope for straight linefit z dependence
  Double_t fDY_DZ_Sigma;   // delta y slope  for straight linefit z dependence

public:
  GBeamSpot();
  GBeamSpot(Int_t run, Int_t events, Double_t x_mean, Double_t x_sigma, Double_t y_mean, Double_t y_sigma, Double_t z_mean, Double_t z_sigma);
  GBeamSpot(Int_t run, Int_t events, Double_t x_mean, Double_t x_sigma, Double_t y_mean, Double_t y_sigma, Double_t z_mean, Double_t z_sigma,Double_t x_zero,Double_t x_zero_sigma,Double_t y_zero,Double_t y_zero_sigma,Double_t dx_dz,Double_t dx_dz_sigma,Double_t dy_dz,Double_t dy_dz_sigma);
  virtual ~GBeamSpot();

  Int_t Compare(const TObject *obj) const;

  inline virtual Int_t    GetRun()       { return fRun;       }
  inline virtual Int_t    GetEvents()    { return fEvents;    }
  inline virtual Double_t GetX_Mean()    { return X();    }
  inline virtual Double_t GetX_Sigma()   { return fX_Sigma;   }
  inline virtual Double_t GetY_Mean()    { return Y();    }
  inline virtual Double_t GetY_Sigma()   { return fY_Sigma;   }
  inline virtual Double_t GetZ_Mean()    { return Z();    }
  inline virtual Double_t GetZ_Sigma()   { return fZ_Sigma;   }
  inline virtual Double_t GetX0()        { return fX0;    }
  inline virtual Double_t GetX0_Sigma()  { return fX0_Sigma;   }
  inline virtual Double_t GetY0()        { return fY0;    }
  inline virtual Double_t GetY0_Sigma()  { return fY0_Sigma;   }
  inline virtual Double_t GetDX_DZ()        { return fDX_DZ;   }
  inline virtual Double_t GetDX_DZ_Sigma()  { return fDX_DZ_Sigma;   }
  inline virtual Double_t GetDY_DZ()        { return fDY_DZ;   }
  inline virtual Double_t GetDY_DZ_Sigma()  { return fDY_DZ_Sigma;   }

  virtual Bool_t IsSortable() const { return kTRUE;      }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GBeamSpot,0) // beamspot class
};

#endif
