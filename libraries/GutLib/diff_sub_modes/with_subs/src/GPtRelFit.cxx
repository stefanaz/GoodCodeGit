//
// GPtRelFit.cxx
//
// $Author: gutsche $
// $Date: 2005/02/07 12:31:20 $
// $Revision: 1.4 $
//

#include <GPtRelFit.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GPtRelFit)
#endif

//_____________________________________________________________
// GPtRelFit
//
// ptrel fit class, takes all parameters from fit and stores them
// including identifier 
//
GPtRelFit::GPtRelFit() : TObject() {
  //
  // GPtRelFit default constructor
  if ( gDebug ) cout << endl << "GPtRelFit::GPtRelFit normal ctor called" << endl << endl;

}

//_____________________________________________________________

GPtRelFit::GPtRelFit(TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter) : TObject() {
  //
  // GPtRelFit normal constructor
  if ( gDebug ) cout << endl << "GPtRelFit::GPtRelFit normal ctor called" << endl << endl;

  fName        = name;
  fBScale      = bscale;
  fBScaleErr   = bscaleerr;
  fCLFScale    = clfscale;
  fCLFScaleErr = clfscaleerr;
  fBFraction   = bfraction;
  fBFractionErr= bfractionerr;
  fChi2        = chi2;
  fBins        = bins;
  fParameter   = parameter;

}

//_____________________________________________________________

GPtRelFit::~GPtRelFit() {
  //
  // GPtRelFit default destructor
  if ( gDebug ) cout << endl << "GPtRelFit::~GPtRelFit dtor called" << endl << endl;

}

//_____________________________________________________________

TString GPtRelFit::Print(TString option) {
  //
  // GPtRelFit print function
  if ( gDebug ) cout << endl << "GPtRelFit::Print called" << endl << endl;

  GInclude include;

  TString output = "";

  output.Append("PtRel Fit: ");
  output.Append(fName);
  output.Append("\n");
  output.Append("beauty mc scale factor      :  ");
  output.Append(include.FormatedDouble(fBScale,1,3));
  output.Append(" +- ");
  output.Append(include.FormatedDouble(fBScaleErr,1,3));
  output.Append("\n");
  output.Append("charm and lf mc scale factor:  ");
  output.Append(include.FormatedDouble(fCLFScale,1,3));
  output.Append(" +- ");
  output.Append(include.FormatedDouble(fCLFScaleErr,1,3));
  output.Append("\n");
  output.Append("beauty fraction             :  ");
  output.Append(include.FormatedDouble(fBFraction,1,3));
  output.Append(" +- ");
  output.Append(include.FormatedDouble(fBFractionErr,1,3));
  output.Append("\n");
  output.Append("chi2/ndof                   : ");
  output.Append(include.FormatedDouble(fChi2,4,3));
  output.Append(" / ");
  output.Append(include.FormatedInt(GetNdof(),2,3," "));
  output.Append(" = ");
  output.Append(include.FormatedDouble(fChi2/GetNdof(),4,3));
  output.Append("\n");

  return output;
}
