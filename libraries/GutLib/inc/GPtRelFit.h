//
// GPtRelFit.h
//
// $Author: gutsche $
// $Date: 2005/02/07 12:31:20 $
// $Revision: 1.2 $
//

#ifndef GUT_GPtRelFit
#define GUT_GPtRelFit

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

class GPtRelFit : public TObject {

private:

  TString   fName;                // describer of fit
  Double_t  fBScale;              // scale factor for b mc
  Double_t  fBScaleErr;           // error on scale factor for b mc
  Double_t  fCLFScale;            // scale factor for c and lf mc
  Double_t  fCLFScaleErr;         // error on scale factor for c and lf mc
  Double_t  fBFraction;           // b fraction
  Double_t  fBFractionErr;        // error on b fraction
  Double_t  fChi2;                // chi2
  Int_t     fBins;                // number of bins
  Int_t     fParameter;           // number of parameter

public:
  GPtRelFit();
  GPtRelFit(TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter);
  virtual ~GPtRelFit();
  
  virtual TString Print(TString option);


  inline virtual TString GetName()                   { return fName;        }
  inline virtual Double_t GetBScale()                { return fBScale;      }
  inline virtual Double_t GetBScaleErr()             { return fBScaleErr;   }
  inline virtual Double_t GetCLFScale()              { return fCLFScale;    }
  inline virtual Double_t GetCLFScaleErr()           { return fCLFScaleErr; }
  inline virtual Double_t GetBFraction()             { return fBFraction;   }
  inline virtual Double_t GetBFractionErr()          { return fBFractionErr;}
  inline virtual Double_t GetChi2()                  { return fChi2;}
  inline virtual Int_t    GetNdof()                  { return fBins-fParameter;}
  inline virtual Int_t    GetBins()                  { return fBins;        }
  inline virtual Int_t    GetParameter()             { return fParameter;   }

  inline virtual void SetName(TString input)         { fName = input;       }
  inline virtual void SetBScale(Double_t input)      { fBScale = input;     }
  inline virtual void SetBScaleErr(Double_t input)   { fBScaleErr = input;  }
  inline virtual void SetCLFScale(Double_t input)    { fCLFScale = input;   }
  inline virtual void SetCLFScaleErr(Double_t input) { fCLFScaleErr = input;}
  inline virtual void SetBFraction(Double_t input)   { fBFraction = input;  }
  inline virtual void SetBFractionErr(Double_t input){ fBFractionErr=input; }
  inline virtual void SetChi2(Double_t input)        { fChi2=input;         }
  inline virtual void SetBins(Int_t input)           { fBins=input;         }
  inline virtual void SetParameter(Int_t input)      { fParameter=input;    }

  ClassDef(GPtRelFit,1) // PtRel Fit parameter
};

#endif
