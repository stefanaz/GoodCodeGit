//
// GMCVertex.cxx
//
// $Author: gutsche $
// $Date: 2004/06/08 09:42:19 $
// $Revision: 1.2 $
//

#include <GMCVertex.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMCVertex)
#endif

//_____________________________________________________________
// GMCVertex
//
// mc vertex class
//
GMCVertex::GMCVertex() : TVector3() {
  //
  // GMCVertex default constructor
  if ( gDebug ) cout << endl << "GMCVertex::GMCVertex default ctor called" << endl << endl;

  fVertexID = 0;
  fTime     = 0.0;

}

//_____________________________________________________________

GMCVertex::GMCVertex(Int_t vertexid, Double_t x, Double_t y, Double_t z, Double_t time) : TVector3(x,y,z) {
  //
  // GMCVertex normal constructor
  if ( gDebug ) cout << endl << "GMCVertex::GMCVertex normal ctor called" << endl << endl;

  fVertexID = vertexid;
  fTime     = time;

}

//_____________________________________________________________

GMCVertex::~GMCVertex() {
  //
  // GMCVertex default destructor
  if ( gDebug ) cout << endl << "GMCVertex::~GMCVertex dtor called" << endl << endl;

}

//_____________________________________________________________

TString GMCVertex::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GMCVertex::PrintMessage called" << endl << endl;

  TString dummy = "GMCVertex: ";
  
  dummy.Append(gInclude->FormatedChar(" vertex id: ",13));
  dummy.Append(gInclude->FormatedInt(fVertexID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" x: ",5));
  dummy.Append(gInclude->FormatedDouble(X(),3,5));
  dummy.Append(gInclude->FormatedChar(" y: ",5));
  dummy.Append(gInclude->FormatedDouble(Y(),3,5));
  dummy.Append(gInclude->FormatedChar(" z: ",5));
  dummy.Append(gInclude->FormatedDouble(Z(),3,5));
  dummy.Append(gInclude->FormatedChar(" time: ",7));
  dummy.Append(gInclude->FormatedDouble(fTime,3,2));
  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GMCVertex::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMCVertex::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}
