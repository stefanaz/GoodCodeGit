//
// GFitter.h
//
// $Author: gutsche $
// $Date: 2005/02/07 12:31:20 $
// $Revision: 1.7 $
//

#ifndef GUT_GFitter
#define GUT_GFitter

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class TMinuit;
class TFile;
class TH1D;

class GFitter : public TObject {

 private:

  TMinuit        *gMinuit;              // TMinuit instance

  Int_t           fBins;                // number of bins for fit
  Int_t           fHistos;              // number of histograms to fit
  Double_t       *fData;                // data array from Histograms
  Double_t       *fDataErr;             // data error array from Histograms
  Double_t      **fMC;                  // mc array from Histograms
  Double_t      **fMCErr;               // mc error array from Histograms
  Double_t       *fStartArray;          // array with variable starts
  Double_t       *fStepArray;           // array with variable steps
  Int_t           fParameter;           // number of parameters to fit
  Double_t       *fParameterArray;      // array of resulting parameters
  Double_t       *fParaErrArray;        // array of resulting parameters
  Double_t        fChi2;                // chi2

 public:
  GFitter();
  GFitter(TFile *file, Int_t parameter, Double_t *startArray, Double_t *stepArray);
  GFitter(int argc, char **argv);
  virtual ~GFitter();

  Bool_t ReadInContents(TH1D** histos);
  Bool_t ReadInContentsImpact(TH1D** histos);
  Bool_t DoFit();

  Double_t FitFunction(Double_t *input, Double_t *par);

  static void Chi2Function(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
  
  inline TMinuit*   GetMinuit()         { return gMinuit;         }
  inline Int_t      GetBins()           { return fBins;           }
  inline Int_t      GetHistos()         { return fHistos;         }
  inline Int_t      GetParameter()      { return fParameter;      }
  inline Double_t*  GetData()           { return fData;           }
  inline Double_t*  GetDataErr()        { return fDataErr;        } 
  inline Double_t** GetMC()             { return fMC;             }
  inline Double_t** GetMCErr()          { return fMCErr;          }
  inline Double_t*  GetParameterArray() { return fParameterArray; }
  inline Double_t*  GetParaErrArray()   { return fParaErrArray;   }
  inline Double_t   GetChi2()           { return fChi2;           }

  inline void SetParameter(Int_t input )     { fParameter = input;  }
  inline void SetStartArray(Double_t *input) { fStartArray = input; }
  inline void SetStepArray(Double_t *input)  { fStepArray = input;  }
  inline void SetHistos(Int_t input)         { fHistos = input;     }

  ClassDef(GFitter,0) // fits ptrel distributions with TMinuit
};

R__EXTERN GFitter *gFitter;

#endif
