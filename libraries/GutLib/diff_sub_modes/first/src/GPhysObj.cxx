//
// GPhysObj.cxx
//
// $Author: gutsche $
// $Date: 2004/01/13 18:41:14 $
// $Revision: 1.10 $
//

#include <GPhysObj.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GPhysObj)
#endif

//_____________________________________________________________
// GPhysObj
// abstract base class for physics objects, includes:
//
// CreateHistograms()    : called from constructor, calls per default
//       CreateGeneral() : for general histograms
//       CreateControl() : for control plots
//
// Reset()               : resets variables on event by event basis
// Do()                  : main function to call per event
// FillHistos()          : fills histograms
//
// FillHistos()          : fills histograms, calls per default
//       FillGeneral()   : fills general histograms
//       FillControl()   : fills control plots
//
//
GPhysObj::GPhysObj() : TObject() {
  //
  // GPhysObj default constructor
  if ( gDebug ) cout << endl << "GPhysObj::GPhysObj ctor called" << endl << endl;

  // initialize ok flag
  fOK = kFALSE;

}

//_____________________________________________________________

GPhysObj::~GPhysObj() {
  //
  // GPhysObj default destructor
  if ( gDebug ) cout << endl << "GPhysObj::~GPhysObj dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GPhysObj::CreateHistograms() {
  //
  // create histograms
  if ( gDebug ) cout << endl << "GPhysObj::CreateHistograms() called" << endl << endl;

  Bool_t returny = kFALSE;

  // create general histograms
  returny = this->CreateGeneral();

  // create control plots
  returny = this->CreateControl();

  return returny;
}

//_____________________________________________________________

Bool_t GPhysObj::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GPhysObj::FillHistos() called" << endl << endl;

  // fill general histograms
  this->FillGeneral();
  
  // fill control plots
  this->FillControl();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::CreateGeneral() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GPhysObj::CreateGeneral() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GPhysObj::FillGeneral() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::CreateControl() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GPhysObj::CreateControl() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::FillControl() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GPhysObj::FillControl() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GPhysObj::Do() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GPhysObj::Reset() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::Finalize() {
  //
  // finalize operations of physics object, mainly for histograms
  if ( gDebug ) cout << endl << "GPhysObj::Finalize() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPhysObj::GetAllCuts() {
  //
  // returns flag for physics object if event passes all object cuts
  if ( gDebug ) cout << endl << "GPhysObj::GetAllCuts() called" << endl << endl;

  return kFALSE;
}

//_____________________________________________________________

TString GPhysObj::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GPhysObj::PrintMessage() called" << endl << endl;

  TString dummy = "";

  return dummy;
}

//_____________________________________________________________

Bool_t GPhysObj::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GPhysObj::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("GPHYSOBJ") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}
