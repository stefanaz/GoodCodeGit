//
// GMCVertex.h
//
// $Author: gutsche $
// $Date: 2004/06/01 16:33:48 $
// $Revision: 1.1 $
//

#ifndef GUT_GMCVertex
#define GUT_GMCVertex

#ifndef ROOT_TVector3
#include <TVector3.h>
#endif

class GMCVertex : public TVector3 {

private:

  Int_t      fVertexID;              // vertex id
  Double_t   fTime;                  // production time

public:
  GMCVertex();
  GMCVertex(Int_t vertexid, Double_t x, Double_t y, Double_t z, Double_t time);
  virtual ~GMCVertex();

  inline virtual Int_t    GetVertexID()         { return fVertexID;       }
  inline virtual Double_t GetTime()             { return fTime;           }

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GMCVertex,0) // mc vertex class
};

#endif
