//
// GImpactFit.cxx
//
// $Author: gutsche $
// $Date: 2005/02/07 12:31:20 $
// $Revision: 1.2 $
//

#include <GImpactFit.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GImpactFit)
#endif

//_____________________________________________________________
// GImpactFit
//
// impact parameter fit class, takes all parameters from fit and stores them
// including identifier 
//
GImpactFit::GImpactFit() : TObject() {
  //
  // GImpactFit default constructor
  if ( gDebug ) cout << endl << "GImpactFit::GImpactFit normal ctor called" << endl << endl;

}

//_____________________________________________________________

GImpactFit::GImpactFit(TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter) : TObject() {
  //
  // GImpactFit normal constructor
  if ( gDebug ) cout << endl << "GImpactFit::GImpactFit normal ctor called" << endl << endl;

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

GImpactFit::~GImpactFit() {
  //
  // GImpactFit default destructor
  if ( gDebug ) cout << endl << "GImpactFit::~GImpactFit dtor called" << endl << endl;

}

//_____________________________________________________________

TString GImpactFit::Print(TString option) {
  //
  // GImpactFit print function
  if ( gDebug ) cout << endl << "GImpactFit::Print called" << endl << endl;

  GInclude include;

  TString output = "";

  output.Append("Impact Parameter Fit: ");
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
  output.Append(include.FormatedDouble(fChi2,2,3));
  output.Append(" / ");
  output.Append(include.FormatedInt(GetNdof(),2,3," "));
  output.Append("\n");

  return output;
}
