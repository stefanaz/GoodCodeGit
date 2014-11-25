//
// GBeamSpot.cxx
//
// $Author: meyer $
// $Date: 2005/08/30 11:13:29 $
// $Revision: 1.4 $
//

#include <GBeamSpot.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GBeamSpot)
#endif

//_____________________________________________________________
// GBeamSpot
//
// class which holds information of the beamspot per run
//
GBeamSpot::GBeamSpot() : TVector3() {
  //
  // GBeamSpot normal constructor
  if ( gDebug ) cout << endl << "GBeamSpot::GBeamSpot normal ctor called" << endl << endl;

  fRun       = 0;
  fEvents    = 0;
  fX0        = 0.0;
  fY0        = 0.0;
  fX0_Sigma  = 0.0;
  fY0_Sigma  = 0.0;
  fX_Sigma   = 0.0;
  fY_Sigma   = 0.0;
  fZ_Sigma   = 0.0;
  fDX_DZ        = 0.0;
  fDX_DZ_Sigma  = 0.0;
  fDY_DZ        = 0.0;
  fDY_DZ_Sigma  = 0.0;

  

}

//_____________________________________________________________

GBeamSpot::GBeamSpot(Int_t run, Int_t events, Double_t x_mean, Double_t x_sigma, Double_t y_mean, Double_t y_sigma, Double_t z_mean, Double_t z_sigma) : TVector3(x_mean,y_mean,z_mean) {
  //
  // GBeamSpot constructor
  if ( gDebug ) cout << endl << "GBeamSpot::GBeamSpot  ctor called" << endl << endl;

  fRun       = run;
  fEvents    = events;
  fX_Sigma   = x_sigma;
  fY_Sigma   = y_sigma;
  fZ_Sigma   = z_sigma;
  fDX_DZ        = 0.0;
  fDX_DZ_Sigma  = 0.0;
  fDY_DZ        = 0.0;
  fDY_DZ_Sigma  = 0.0;
  fX0_Sigma  = 0.0;
  fY0_Sigma  = 0.0;
  fX0        = 0.0;
  fY0        = 0.0;

}
//_____________________________________________________________

GBeamSpot::GBeamSpot(Int_t run, Int_t events, Double_t x_mean, Double_t x_sigma, Double_t y_mean, Double_t y_sigma, Double_t z_mean, Double_t z_sigma,Double_t x0,Double_t x0_sigma,Double_t y0,Double_t y0_sigma,Double_t dx_dz,Double_t dx_dz_sigma,Double_t dy_dz,Double_t dy_dz_sigma) : TVector3(x_mean,y_mean,z_mean) {
  //
  // GBeamSpot normal constructor
  if ( gDebug ) cout << endl << "GBeamSpot::GBeamSpot normal ctor called" << endl << endl;

  fRun       = run;
  fEvents    = events;
  fX_Sigma   = x_sigma;
  fY_Sigma   = y_sigma;
  fZ_Sigma   = z_sigma;
  fDX_DZ        = dx_dz;
  fDX_DZ_Sigma  = dx_dz_sigma;
  fDY_DZ        = dy_dz;
  fDY_DZ_Sigma  = dy_dz_sigma;
  fX0_Sigma  = x0_sigma;
  fY0_Sigma  = y0_sigma;
  fX0        = x0;
  fY0        = y0;

}

//_____________________________________________________________

GBeamSpot::~GBeamSpot() {
  //
  // GBeamSpot default destructor
  if ( gDebug ) cout << endl << "GBeamSpot::~GBeamSpot dtor called" << endl << endl;

}

//_____________________________________________________________

TString GBeamSpot::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GBeamSpot::PrintMessage called" << endl << endl;

  TString dummy = "";
  if ( option.Contains("SILVIA") ) {
    dummy.Append(gInclude->FormatedInt(fRun,7,0," "));
    dummy.Append(gInclude->FormatedInt(fEvents,7,0," "));
    dummy.Append(gInclude->FormatedDouble(X(),5,5));
    dummy.Append(gInclude->FormatedDouble(fX_Sigma,5,5));
    dummy.Append(gInclude->FormatedDouble(Y(),5,5));
    dummy.Append(gInclude->FormatedDouble(fY_Sigma,5,5));
    dummy.Append(gInclude->FormatedDouble(Z(),5,5));
    dummy.Append(gInclude->FormatedDouble(fZ_Sigma,5,5));
    dummy.Append("\n");

  } else {
    dummy = "BeamSpot: ";
  
    dummy.Append(gInclude->FormatedChar(" run: ",7));
    dummy.Append(gInclude->FormatedInt(fRun,6,0," "));
    dummy.Append(gInclude->FormatedChar(" no. of events: ",17));
    dummy.Append(gInclude->FormatedInt(fEvents,7,0," "));
    dummy.Append(gInclude->FormatedChar(" x_mean: ",10));
    dummy.Append(gInclude->FormatedDouble(X(),3,5));
    dummy.Append(gInclude->FormatedChar(" x_sigma: ",11));
    dummy.Append(gInclude->FormatedDouble(fX_Sigma,3,5));
    dummy.Append(gInclude->FormatedChar(" y_mean: ",10));
    dummy.Append(gInclude->FormatedDouble(Y(),3,5));
    dummy.Append(gInclude->FormatedChar(" y_sigma: ",11));
    dummy.Append(gInclude->FormatedDouble(fY_Sigma,3,5));
    dummy.Append(gInclude->FormatedChar(" z_mean: ",10));
    dummy.Append(gInclude->FormatedDouble(Z(),3,5));
    dummy.Append(gInclude->FormatedChar(" z_sigma: ",11));
    dummy.Append(gInclude->FormatedDouble(fZ_Sigma,3,5));
    dummy.Append("\n");

  }

  return dummy;
}

//_____________________________________________________________

Bool_t GBeamSpot::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GBeamSpot::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}

//_____________________________________________________________

Int_t GBeamSpot::Compare(const TObject *obj) const {
  //
  // compare this to another beamspot
  if ( gDebug ) cout << endl << "GBeamSpot::Compare called" << endl << endl;

  if ( fRun > ((GBeamSpot*)obj)->GetRun() ) {
    return 1;
  } else if ( fRun < ((GBeamSpot*)obj)->GetRun() ) {
    return -1;
  }

  return 0;

}


















