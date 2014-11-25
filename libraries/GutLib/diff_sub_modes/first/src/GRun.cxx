//
// GRun.cxx
//
// $Author: gutsche $
// $Date: 2004/07/19 17:32:03 $
// $Revision: 1.2 $
//

#include <GRun.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GRun)
#endif

//_____________________________________________________________
// GRun
//
// class which holds information per run from lumi-web-lists
//
GRun::GRun() : TObject() {
  //
  // GRun normal constructor
  if ( gDebug ) cout << endl << "GRun::GRun normal ctor called" << endl << endl;

  fRun       = 0;
  fEvents    = 0;
  fLumi_Cal  = 0.0;
  fLumi_Spec = 0.0;
  fType      = kNormal;

}

//_____________________________________________________________

GRun::GRun(Int_t run, Int_t events, Double_t lumi_cal, Double_t lumi_spec, EZRunType type) : TObject() {
  //
  // GRun normal constructor
  if ( gDebug ) cout << endl << "GRun::GRun normal ctor called" << endl << endl;

  fRun       = run;
  fEvents    = events;
  fLumi_Cal  = lumi_cal;
  fLumi_Spec = lumi_spec;
  fType      = type;

}

//_____________________________________________________________

GRun::~GRun() {
  //
  // GRun default destructor
  if ( gDebug ) cout << endl << "GRun::~GRun dtor called" << endl << endl;

}

//_____________________________________________________________

TString GRun::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GRun::PrintMessage called" << endl << endl;

  TString dummy = "GRun: ";
  
  dummy.Append(gInclude->FormatedChar(" run: ",7));
  dummy.Append(gInclude->FormatedInt(fRun,6,0," "));
  dummy.Append(gInclude->FormatedChar(" no. of events: ",17));
  dummy.Append(gInclude->FormatedInt(fEvents,7,0," "));
  dummy.Append(gInclude->FormatedChar(" Lumi_Cal: ",12));
  dummy.Append(gInclude->FormatedDouble(fLumi_Cal,3,2));
  dummy.Append(gInclude->FormatedChar(" Lumi_Spec: ",13));
  dummy.Append(gInclude->FormatedDouble(fLumi_Spec,3,2));
  if ( fType == kHigh )
    dummy.Append(" high lumi trigger configuration");
  else if ( fType == kLow )
    dummy.Append(" low lumi trigger configuration");
  else if ( fType == kLTRKV )
    dummy.Append(" LTRKV lumi trigger configuration");
  else if ( fType == kNOTTV )
    dummy.Append(" NOTTV lumi trigger configuration");
  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GRun::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GRun::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}
