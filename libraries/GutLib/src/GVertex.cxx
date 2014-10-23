//
// GVertex.cxx
//
// $Author: dbot $
// $Date: 2010/03/29 13:12:20 $
// $Revision: 1.27 $
//

#include <GVertex.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GVertex)
#endif

GVertex *gVertex = 0;

//_____________________________________________________________
// GVertex
// Vertex Class for everything which is related only to Vertices
//
//
GVertex::GVertex() : GPhysObj() {
  //
  // GVertex default constructor
  if ( gDebug ) cout << endl << "GVertex::GVertex ctor called" << endl << endl;

  // initialize global pointer
  gVertex = this;

  // initialize variables
  fZCut              = kFALSE;
  fXCut              = kFALSE;
  fYCut              = kFALSE;
  fXYCut             = kFALSE;
  fBeamSpotCut       = kFALSE;

  // variables for secondary vertex block

  fRedprm_X         = 0.;
  fRedprm_Y         = 0.;
  fRedprm_Z         = 0.;
  fRedprm_Chi2      = 0.;
  fRedprm_Ndof      = 0.;
  fNr_secvtx        = 0;
  fSecvtx_X         = 0.;
  fSecvtx_Y         = 0.;
  fSecvtx_Z         = 0.;
  fSecvtx_Mass      = 0.;
  fSecvtx_Chi2      = 0.;
  fSecvtx_Ndof      = 0.;
  fSecvtx_Multi     = 0;
  fSecvtx_Cov1      = 0.;
  fSecvtx_Cov2      = 0.;
  fSecvtx_Cov3      = 0.;
  fSecvtx_Cov4      = 0.;
  fSecvtx_Cov5      = 0.;
  fSecvtx_Cov6      = 0.;
  fSecvtx_DL2       = 0.;
  fSecvtx_DL2_err   = 0.;
  fSecvtx_DL2_sign  = 0.;

  fSecvtx2D_X       = 0.;
  fSecvtx2D_Y       = 0.;
  fSecvtx2D_Z       = 0.;
  fSecvtx2D_Mass    = 0.;
  fSecvtx2D_Chi2    = 0.;
  fSecvtx2D_Ndof    = 0.;

  // initialize uncut control histograms
  fControlX_uncut = 0;
  fControlY_uncut = 0;
  fControlZ_uncut = 0;
  fControlXY_uncut = 0;

  fControlXMCTRUE_uncut = 0;
  fControlYMCTRUE_uncut = 0;
  fControlZMCTRUE_uncut = 0;

  fControlRedprm_X_uncut      = 0;
  fControlRedprm_Y_uncut      = 0;
  fControlRedprm_Z_uncut      = 0;
  fControlRedprm_Chi2_uncut   = 0;
  fControlRedprm_Ndof_uncut   = 0;
  fControlNr_secvtx_uncut     = 0;
  fControlSecvtx_X_uncut      = 0;
  fControlSecvtx_Y_uncut      = 0;
  fControlSecvtx_Z_uncut      = 0;
  fControlSecvtx_Mass_uncut   = 0;
  fControlSecvtx_Chi2_uncut   = 0;
  fControlSecvtx_Ndof_uncut   = 0;
  fControlSecvtx_Multi_uncut  = 0;
  fControlSecvtx_Cov1_uncut   = 0;
  fControlSecvtx_Cov2_uncut   = 0;
  fControlSecvtx_Cov3_uncut   = 0;
  fControlSecvtx_Cov4_uncut   = 0;
  fControlSecvtx_Cov5_uncut   = 0;
  fControlSecvtx_Cov6_uncut   = 0;
  fControlSecvtx2D_X_uncut    = 0;
  fControlSecvtx2D_Y_uncut    = 0;
  fControlSecvtx2D_Z_uncut    = 0;
  fControlSecvtx2D_Mass_uncut = 0;
  fControlSecvtx2D_Chi2_uncut = 0;
  fControlSecvtx2D_Ndof_uncut = 0;

  // initialize control histograms
  fControlX = 0;
  fControlY = 0;
  fControlZ = 0;
  fControlXY = 0;

  fControlXMCTRUE = 0;
  fControlYMCTRUE = 0;
  fControlZMCTRUE = 0;

  fControlRedprm_X      = 0;
  fControlRedprm_Y      = 0;
  fControlRedprm_Z      = 0;
  fControlRedprm_Chi2   = 0;
  fControlRedprm_Ndof   = 0;
  fControlNr_secvtx     = 0;
  fControlSecvtx_X      = 0;
  fControlSecvtx_Y      = 0;
  fControlSecvtx_Z      = 0;
  fControlSecvtx_Mass   = 0;
  fControlSecvtx_Chi2   = 0;
  fControlSecvtx_Ndof   = 0;
  fControlSecvtx_Multi  = 0;
  fControlSecvtx_Cov1   = 0;
  fControlSecvtx_Cov2   = 0;
  fControlSecvtx_Cov3   = 0;
  fControlSecvtx_Cov4   = 0;
  fControlSecvtx_Cov5   = 0;
  fControlSecvtx_Cov6   = 0;
  fControlSecvtx2D_X    = 0;
  fControlSecvtx2D_Y    = 0;
  fControlSecvtx2D_Z    = 0;
  fControlSecvtx2D_Mass = 0;
  fControlSecvtx2D_Chi2 = 0;
  fControlSecvtx2D_Ndof = 0;

  // initialize uncut general histograms
  fGeneralX_uncut = 0;
  fGeneralY_uncut = 0;
  fGeneralZ_uncut = 0;

  fGeneralXMCTRUE_uncut = 0;
  fGeneralYMCTRUE_uncut = 0;
  fGeneralZMCTRUE_uncut = 0;

  fGeneralRedprm_X_uncut      = 0;
  fGeneralRedprm_Y_uncut      = 0;
  fGeneralRedprm_Z_uncut      = 0;
  fGeneralRedprm_Chi2_uncut   = 0;
  fGeneralRedprm_Ndof_uncut   = 0;
  fGeneralNr_secvtx_uncut     = 0;
  fGeneralSecvtx_X_uncut      = 0;
  fGeneralSecvtx_Y_uncut      = 0;
  fGeneralSecvtx_Z_uncut      = 0;
  fGeneralSecvtx_Mass_uncut   = 0;
  fGeneralSecvtx_Chi2_uncut   = 0;
  fGeneralSecvtx_Ndof_uncut   = 0;
  fGeneralSecvtx_Multi_uncut  = 0;
  fGeneralSecvtx_Cov1_uncut   = 0;
  fGeneralSecvtx_Cov2_uncut   = 0;
  fGeneralSecvtx_Cov3_uncut   = 0;
  fGeneralSecvtx_Cov4_uncut   = 0;
  fGeneralSecvtx_Cov5_uncut   = 0;
  fGeneralSecvtx_Cov6_uncut   = 0;
  fGeneralSecvtx2D_X_uncut    = 0;
  fGeneralSecvtx2D_Y_uncut    = 0;
  fGeneralSecvtx2D_Z_uncut    = 0;
  fGeneralSecvtx2D_Mass_uncut = 0;
  fGeneralSecvtx2D_Chi2_uncut = 0;
  fGeneralSecvtx2D_Ndof_uncut = 0;

  // initialize general histograms
  fGeneralX = 0;
  fGeneralY = 0;
  fGeneralZ = 0;

  fGeneralXMCTRUE = 0;
  fGeneralYMCTRUE = 0;
  fGeneralZMCTRUE = 0;

  fGeneralRedprm_X      = 0;
  fGeneralRedprm_Y      = 0;
  fGeneralRedprm_Z      = 0;
  fGeneralRedprm_Chi2   = 0;
  fGeneralRedprm_Ndof   = 0;
  fGeneralNr_secvtx     = 0;
  fGeneralSecvtx_X      = 0;
  fGeneralSecvtx_Y      = 0;
  fGeneralSecvtx_Z      = 0;
  fGeneralSecvtx_Mass   = 0;
  fGeneralSecvtx_Chi2   = 0;
  fGeneralSecvtx_Ndof   = 0;
  fGeneralSecvtx_Multi  = 0;
  fGeneralSecvtx_Cov1   = 0;
  fGeneralSecvtx_Cov2   = 0;
  fGeneralSecvtx_Cov3   = 0;
  fGeneralSecvtx_Cov4   = 0;
  fGeneralSecvtx_Cov5   = 0;
  fGeneralSecvtx_Cov6   = 0;
  fGeneralSecvtx2D_X    = 0;
  fGeneralSecvtx2D_Y    = 0;
  fGeneralSecvtx2D_Z    = 0;
  fGeneralSecvtx2D_Mass = 0;
  fGeneralSecvtx2D_Chi2 = 0;
  fGeneralSecvtx2D_Ndof = 0;

  // create Histograms
  fOK = CreateHistograms();

  // initialize current beamspot
  fCurrentBeamSpot = 0;
  fEventBeamSpot = 0;
  fMCBeamSpot = 0;

  // init beamspot array
  fBeamSpots       = 0;
  fNBeamSpots      = 0;

  fNoBeamSpotRunnr = 0;
  fLastValidBeamSpot = 0;

}

//_____________________________________________________________

GVertex::~GVertex() {
  //
  // GVertex default destructor
  if ( gDebug ) cout << endl << "GVertex::~GVertex dtor called" << endl << endl;

  if ( fBeamSpots != 0 ) {
    fBeamSpots->Delete();
    delete fBeamSpots;
    fNBeamSpots = 0;
  }

  if ( fMCBeamSpot != 0 ) {
    delete fMCBeamSpot;
  }

}

//_____________________________________________________________

Bool_t GVertex::CreateControl() {
  //
  // create control histograms for vertices
  if ( gDebug ) cout << endl << "GVertex::CreateControl() called" << endl << endl;

  if ( gCards->GetVertexControl() ) {

    Int_t    xbins  =  400;
    Double_t xlow   = -4.0;
    Double_t xhigh  =  4.0;
    Int_t    ybins  =  400;
    Double_t ylow   = -4.0;
    Double_t yhigh  =  4.0;
    Int_t    zbins  =  480;
    Double_t zlow   = -60.0;
    Double_t zhigh  =  60.0;

    Int_t    chi2bins  = 100;    
    Double_t chi2low   = 0.;
    Double_t chi2high  = 10.;
    Int_t    ndofbins  = 100;    
    Double_t ndoflow   = 0.;
    Double_t ndofhigh  = 50.;
    Int_t    nrsecbins = 10;
    Double_t nrseclow  = 0.;
    Double_t nrsechigh = 10.;
    Int_t    multibins = 12;
    Double_t multilow  = 0.;
    Double_t multihigh = 12.;
    Int_t    massbins  = 100;
    Double_t masslow   = 0.;
    Double_t masshigh  = 10.;
    Int_t    covbins   = 10;
    Double_t covlow    = -50.;
    Double_t covhigh   = 700.;

    fControlX_uncut = gHistogrammer->TH1DFactory("Vertex_Control","X_uncut","uncut Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlY_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Y_uncut","uncut Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlZ_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Z_uncut","uncut Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");

    fControlRedprm_X_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_X_uncut","uncut Red prim vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlRedprm_Y_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Y_uncut","uncut Red prim vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlRedprm_Z_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Z_uncut","uncut Red prim vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlRedprm_Chi2_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Chi2_uncut","uncut chi2 of Red prim vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fControlRedprm_Ndof_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Ndof_uncut","uncut Ndof of Red prim vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fControlNr_secvtx_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Nrsecvtx_uncut","uncut Nr of Sec vtx",nrsecbins,nrseclow,nrsechigh,"nrsecvtx","Events");
    fControlSecvtx_X_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_X_uncut","uncut X of Sec vtx",xbins,xlow,xhigh,"x [cm]","Events");
    fControlSecvtx_Y_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Y_uncut","uncut Y of Sec vtx",ybins,ylow,yhigh,"y [cm]","Events");
    fControlSecvtx_Z_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Z_uncut","uncut Z of Sec vtx",zbins,zlow,zhigh,"z [cm]","Events");
    fControlSecvtx_Mass_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Mass_uncut","uncut Mass of Sec vtx",massbins,masslow,masshigh,"mass","Events");
    fControlSecvtx_Chi2_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Chi2_uncut","uncut Chi2 of Sec vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fControlSecvtx_Ndof_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Ndof_uncut","uncut Ndof of Sec vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fControlSecvtx_Multi_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Multi_uncut","uncut Multiplicity in Sec vtx",multibins,multilow,multihigh,"sec_multi","Events");
    fControlSecvtx_Cov1_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov1_uncut","uncut Cov1 matrix element",covbins,covlow,covhigh,"Cov 1","Events");
    fControlSecvtx_Cov2_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov2_uncut","uncut Cov2 matrix element",covbins,covlow,covhigh,"Cov 2","Events");
    fControlSecvtx_Cov3_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov3_uncut","uncut Cov3 matrix element",covbins,covlow,covhigh,"Cov 3","Events");
    fControlSecvtx_Cov4_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov4_uncut","uncut Cov4 matrix element",covbins,covlow,covhigh,"Cov 4","Events");
    fControlSecvtx_Cov5_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov5_uncut","uncut Cov5 matrix element",covbins,covlow,covhigh,"Cov 5","Events");
    fControlSecvtx_Cov6_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov6_uncut","uncut Cov6 matrix element",covbins,covlow,covhigh,"Cov 6","Events");
    fControlSecvtx2D_X_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_X_uncut","uncut 2D Sec vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlSecvtx2D_Y_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Y_uncut","uncut 2D Sec vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlSecvtx2D_Z_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Z_uncut","uncut 2D Sec vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlSecvtx2D_Mass_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Mass_uncut","uncut 2D Sec vtx: Mass",massbins,masslow,masshigh,"mass","Events");
    fControlSecvtx2D_Chi2_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Chi2_uncut","uncut 2D Sec vtx: Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fControlSecvtx2D_Ndof_uncut = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Ndof_uncut","uncut 2D Sec vtx: Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");

    fControlX = gHistogrammer->TH1DFactory("Vertex_Control","X","Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlY = gHistogrammer->TH1DFactory("Vertex_Control","Y","Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlZ = gHistogrammer->TH1DFactory("Vertex_Control","Z","Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");

    fControlRedprm_X = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_X","Red prim vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlRedprm_Y = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Y","Red prim vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlRedprm_Z = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Z","Red prim vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlRedprm_Chi2 = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Chi2","chi2 of Red prim vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fControlRedprm_Ndof = gHistogrammer->TH1DFactory("Vertex_Control","Redprm_Ndof","Ndof of Red prim vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fControlNr_secvtx = gHistogrammer->TH1DFactory("Vertex_Control","Nrsecvtx","Nr of Sec vtx",nrsecbins,nrseclow,nrsechigh,"nrsecvtx","Events");
    fControlSecvtx_X = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_X","X of Sec vtx",xbins,xlow,xhigh,"x [cm]","Events");
    fControlSecvtx_Y = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Y","Y of Sec vtx",ybins,ylow,yhigh,"y [cm]","Events");
    fControlSecvtx_Z = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Z","Z of Sec vtx",zbins,zlow,zhigh,"z [cm]","Events");
    fControlSecvtx_Mass = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Mass","Mass of Sec vtx",massbins,masslow,masshigh,"mass","Events");
    fControlSecvtx_Chi2 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Chi2","Chi2 of Sec vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fControlSecvtx_Ndof = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Ndof","Ndof of Sec vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fControlSecvtx_Multi = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Multi","Multiplicity in Sec vtx",multibins,multilow,multihigh,"sec_multi","Events");
    fControlSecvtx_Cov1 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov1","Cov1 matrix element",covbins,covlow,covhigh,"Cov 1","Events");
    fControlSecvtx_Cov2 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov2","Cov2 matrix element",covbins,covlow,covhigh,"Cov 2","Events");
    fControlSecvtx_Cov3 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov3","Cov3 matrix element",covbins,covlow,covhigh,"Cov 3","Events");
    fControlSecvtx_Cov4 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov4","Cov4 matrix element",covbins,covlow,covhigh,"Cov 4","Events");
    fControlSecvtx_Cov5 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov5","Cov5 matrix element",covbins,covlow,covhigh,"Cov 5","Events");
    fControlSecvtx_Cov6 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx_Cov6","Cov6 matrix element",covbins,covlow,covhigh,"Cov 6","Events");
    fControlSecvtx2D_X = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_X","2D Sec vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlSecvtx2D_Y = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Y","2D Sec vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlSecvtx2D_Z = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Z","2D Sec vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlSecvtx2D_Mass = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Mass","2D Sec vtx: Mass",massbins,masslow,masshigh,"mass","Events");
    fControlSecvtx2D_Chi2 = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Chi2","2D Sec vtx: Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fControlSecvtx2D_Ndof = gHistogrammer->TH1DFactory("Vertex_Control","Secvtx2D_Ndof","2D Sec vtx: Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");

    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      fControlXMCTRUE_uncut = gHistogrammer->TH1DFactory("Vertex_Control","XMCTRUE_uncut","uncut Vertex from MC true info: x",xbins,xlow,xhigh,"x [cm]","Events");
      fControlYMCTRUE_uncut = gHistogrammer->TH1DFactory("Vertex_Control","YMCTRUE_uncut","uncut Vertex from MC true info: y",ybins,ylow,yhigh,"y [cm]","Events");
      fControlZMCTRUE_uncut = gHistogrammer->TH1DFactory("Vertex_Control","ZMCTRUE_uncut","uncut Vertex from MC true info: z",zbins,zlow,zhigh,"z [cm]","Events");
      fControlXMCTRUE = gHistogrammer->TH1DFactory("Vertex_Control","XMCTRUE","Vertex from MC true info: x",xbins,xlow,xhigh,"x [cm]","Events");
      fControlYMCTRUE = gHistogrammer->TH1DFactory("Vertex_Control","YMCTRUE","Vertex from MC true info: y",ybins,ylow,yhigh,"y [cm]","Events");
      fControlZMCTRUE = gHistogrammer->TH1DFactory("Vertex_Control","ZMCTRUE","Vertex from MC true info: z",zbins,zlow,zhigh,"z [cm]","Events");
    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::CreateGeneral() {
  //
  // create general histograms for vertices
  if ( gDebug ) cout << endl << "GVertex::CreateGeneral() called" << endl << endl;

  if ( gCards->GetVertexGeneral() ) {

    Int_t    xbins  =  400;
    Double_t xlow   = -4.0;
    Double_t xhigh  =  4.0;
    Int_t    ybins  =  400;
    Double_t ylow   = -4.0;
    Double_t yhigh  =  4.0;
    Int_t    zbins  =  480;
    Double_t zlow   = -60.0;
    Double_t zhigh  =  60.0;
    Int_t    xybins = 100;
    Double_t xylow  =   0.;
    Double_t xyhigh =   5.;
    
    Int_t    chi2bins  = 100;    
    Double_t chi2low   = 0.;
    Double_t chi2high  = 10.;
    Int_t    ndofbins  = 100;    
    Double_t ndoflow   = 0.;
    Double_t ndofhigh  = 50.;
    Int_t    nrsecbins = 10;
    Double_t nrseclow  = 0.;
    Double_t nrsechigh = 10.;
    Int_t    multibins = 12;
    Double_t multilow  = 0.;
    Double_t multihigh = 12.;
    Int_t    massbins  = 100;
    Double_t masslow   = 0.;
    Double_t masshigh  = 10.;
    Int_t    covbins   = 10;
    Double_t covlow    = -50.;
    Double_t covhigh   = 700.;


    Int_t    xmcbins  =  80;
    Double_t xmclow   =  1.88;
    Double_t xmchigh  =  1.96;
    Int_t    ymcbins  =  80;
    Double_t ymclow   =  0.16;
    Double_t ymchigh  =  0.18;
    Int_t    zmcbins  =  70;
    Double_t zmclow   = -35.0;
    Double_t zmchigh  =  35.0;
    
    fGeneralX_uncut = gHistogrammer->TH1DFactory("Vertex","X_uncut","uncut Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralY_uncut = gHistogrammer->TH1DFactory("Vertex","Y_uncut","uncut Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralZ_uncut = gHistogrammer->TH1DFactory("Vertex","Z_uncut","uncut Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlXY_uncut = gHistogrammer->TH1DFactory("Vertex_Control","XY_uncut","Vertex: #sqrt{x^{2}+y^{2}}",xybins,xylow,xyhigh,"#sqrt{x^{2}+y^{2}} [cm]","Events");

    fGeneralRedprm_X_uncut = gHistogrammer->TH1DFactory("Vertex","Redprm_X_uncut","uncut Red prim vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralRedprm_Y_uncut = gHistogrammer->TH1DFactory("Vertex","Redprm_Y_uncut","uncut Red prim vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralRedprm_Z_uncut = gHistogrammer->TH1DFactory("Vertex","Redprm_Z_uncut","uncut Red prim vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralRedprm_Chi2_uncut = gHistogrammer->TH1DFactory("Vertex","Redprm_Chi2_uncut","uncut chi2 of Red prim vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralRedprm_Ndof_uncut = gHistogrammer->TH1DFactory("Vertex","Redprm_Ndof_uncut","uncut Ndof of Red prim vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneralNr_secvtx_uncut = gHistogrammer->TH1DFactory("Vertex","Nrsecvtx_uncut","uncut Nr of Sec vtx",nrsecbins,nrseclow,nrsechigh,"nrsecvtx","Events");
    fGeneralSecvtx_X_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_X_uncut","uncut X of Sec vtx",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralSecvtx_Y_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Y_uncut","uncut Y of Sec vtx",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralSecvtx_Z_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Z_uncut","uncut Z of Sec vtx",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralSecvtx_Mass_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Mass_uncut","uncut Mass of Sec vtx",massbins,masslow,masshigh,"mass","Events");
    fGeneralSecvtx_Chi2_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Chi2_uncut","uncut Chi2 of Sec vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralSecvtx_Ndof_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Ndof_uncut","uncut Ndof of Sec vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneralSecvtx_Multi_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Multi_uncut","uncut Multiplicity in Sec vtx",multibins,multilow,multihigh,"sec_multi","Events");
    fGeneralSecvtx_Cov1_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov1_uncut","uncut Cov1 matrix element",covbins,covlow,covhigh,"Cov 1","Events");
    fGeneralSecvtx_Cov2_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov2_uncut","uncut Cov2 matrix element",covbins,covlow,covhigh,"Cov 2","Events");
    fGeneralSecvtx_Cov3_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov3_uncut","uncut Cov3 matrix element",covbins,covlow,covhigh,"Cov 3","Events");
    fGeneralSecvtx_Cov4_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov4_uncut","uncut Cov4 matrix element",covbins,covlow,covhigh,"Cov 4","Events");
    fGeneralSecvtx_Cov5_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov5_uncut","uncut Cov5 matrix element",covbins,covlow,covhigh,"Cov 5","Events");
    fGeneralSecvtx_Cov6_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov6_uncut","uncut Cov6 matrix element",covbins,covlow,covhigh,"Cov 6","Events");
    fGeneralSecvtx2D_X_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_X_uncut","uncut 2D Sec vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralSecvtx2D_Y_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Y_uncut","uncut 2D Sec vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralSecvtx2D_Z_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Z_uncut","uncut 2D Sec vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralSecvtx2D_Mass_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Mass_uncut","uncut 2D Sec vtx: Mass",massbins,masslow,masshigh,"mass","Events");
    fGeneralSecvtx2D_Chi2_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Chi2_uncut","uncut 2D Sec vtx: Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralSecvtx2D_Ndof_uncut = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Ndof_uncut","uncut 2D Sec vtx: Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");

    fGeneralX = gHistogrammer->TH1DFactory("Vertex","X","Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralY = gHistogrammer->TH1DFactory("Vertex","Y","Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralZ = gHistogrammer->TH1DFactory("Vertex","Z","Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlXY = gHistogrammer->TH1DFactory("Vertex_Control","XY","Vertex: #sqrt{x^{2}+y^{2}}",xybins,xylow,xyhigh,"#sqrt{x^{2}+y^{2}} [cm]","Events");

    fGeneralRedprm_X = gHistogrammer->TH1DFactory("Vertex","Redprm_X","Red prim vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralRedprm_Y = gHistogrammer->TH1DFactory("Vertex","Redprm_Y","Red prim vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralRedprm_Z = gHistogrammer->TH1DFactory("Vertex","Redprm_Z","Red prim vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralRedprm_Chi2 = gHistogrammer->TH1DFactory("Vertex","Redprm_Chi2","chi2 of Red prim vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralRedprm_Ndof = gHistogrammer->TH1DFactory("Vertex","Redprm_Ndof","Ndof of Red prim vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneralNr_secvtx = gHistogrammer->TH1DFactory("Vertex","Nrsecvtx","Nr of Sec vtx",nrsecbins,nrseclow,nrsechigh,"nrsecvtx","Events");
    fGeneralSecvtx_X = gHistogrammer->TH1DFactory("Vertex","Secvtx_X","X of Sec vtx",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralSecvtx_Y = gHistogrammer->TH1DFactory("Vertex","Secvtx_Y","Y of Sec vtx",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralSecvtx_Z = gHistogrammer->TH1DFactory("Vertex","Secvtx_Z","Z of Sec vtx",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralSecvtx_Mass = gHistogrammer->TH1DFactory("Vertex","Secvtx_Mass","Mass of Sec vtx",massbins,masslow,masshigh,"mass","Events");
    fGeneralSecvtx_Chi2 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Chi2","Chi2 of Sec vtx",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralSecvtx_Ndof = gHistogrammer->TH1DFactory("Vertex","Secvtx_Ndof","Ndof of Sec vtx",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneralSecvtx_Multi = gHistogrammer->TH1DFactory("Vertex","Secvtx_Multi","Multiplicity in Sec vtx",multibins,multilow,multihigh,"sec_multi","Events");
    fGeneralSecvtx_Cov1 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov1","Cov1 matrix element",covbins,covlow,covhigh,"Cov 1","Events");
    fGeneralSecvtx_Cov2 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov2","Cov2 matrix element",covbins,covlow,covhigh,"Cov 2","Events");
    fGeneralSecvtx_Cov3 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov3","Cov3 matrix element",covbins,covlow,covhigh,"Cov 3","Events");
    fGeneralSecvtx_Cov4 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov4","Cov4 matrix element",covbins,covlow,covhigh,"Cov 4","Events");
    fGeneralSecvtx_Cov5 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov5","Cov5 matrix element",covbins,covlow,covhigh,"Cov 5","Events");
    fGeneralSecvtx_Cov6 = gHistogrammer->TH1DFactory("Vertex","Secvtx_Cov6","Cov6 matrix element",covbins,covlow,covhigh,"Cov 6","Events");
    fGeneralSecvtx2D_X = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_X","2D Sec vtx: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralSecvtx2D_Y = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Y","2D Sec vtx: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralSecvtx2D_Z = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Z","2D Sec vtx: z",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralSecvtx2D_Mass = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Mass","2D Sec vtx: Mass",massbins,masslow,masshigh,"mass","Events");
    fGeneralSecvtx2D_Chi2 = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Chi2","2D Sec vtx: Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralSecvtx2D_Ndof = gHistogrammer->TH1DFactory("Vertex","Secvtx2D_Ndof","2D Sec vtx: Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");

    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake())) {
      fGeneralXMCTRUE_uncut = gHistogrammer->TH1DFactory("Vertex","XMCTRUE_uncut","uncut Vertex from MC true info: x",xmcbins,xmclow,xmchigh,"x [cm]","Events");
      fGeneralYMCTRUE_uncut = gHistogrammer->TH1DFactory("Vertex","YMCTRUE_uncut","uncut Vertex from MC true info: y",ymcbins,ymclow,ymchigh,"y [cm]","Events");
      fGeneralZMCTRUE_uncut = gHistogrammer->TH1DFactory("Vertex","ZMCTRUE_uncut","uncut Vertex from MC true info: z",zmcbins,zmclow,zmchigh,"z [cm]","Events");
      fGeneralXMCTRUE = gHistogrammer->TH1DFactory("Vertex","XMCTRUE","Vertex from MC true info: x",xmcbins,xmclow,xmchigh,"x [cm]","Events");
      fGeneralYMCTRUE = gHistogrammer->TH1DFactory("Vertex","YMCTRUE","Vertex from MC true info: y",ymcbins,ymclow,ymchigh,"y [cm]","Events");
      fGeneralZMCTRUE = gHistogrammer->TH1DFactory("Vertex","ZMCTRUE","Vertex from MC true info: z",zmcbins,zmclow,zmchigh,"z [cm]","Events");
    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::FillControl() {
  //
  // fill general histograms for vertices
  if ( gDebug ) cout << endl << "GVertex::FillControl() called" << endl << endl;

  if ( gCards->GetVertexControl() ) {

    Double_t xy = TMath::Sqrt(TMath::Power(gData->Getxvtx(),2)+TMath::Power(gData->Getyvtx(),2));

    fControlX_uncut->Fill(gData->Getxvtx());
    fControlY_uncut->Fill(gData->Getyvtx());
    fControlZ_uncut->Fill(gData->Getzvtx());
    fControlXY_uncut->Fill(xy);

    fControlRedprm_X_uncut->Fill(gData->Getvtxredprm_x());
    fControlRedprm_Y_uncut->Fill(gData->Getvtxredprm_y());
    fControlRedprm_Z_uncut->Fill(gData->Getvtxredprm_z());
    fControlRedprm_Chi2_uncut->Fill(gData->Getvtxredprm_chi2());
    fControlRedprm_Ndof_uncut->Fill(gData->Getvtxredprm_ndf());
    fControlNr_secvtx_uncut->Fill(gData->Getnr_secvtx());

    for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

      fControlSecvtx_X_uncut->Fill(gData->Getvtxsec_x(i));
      fControlSecvtx_Y_uncut->Fill(gData->Getvtxsec_y(i));
      fControlSecvtx_Z_uncut->Fill(gData->Getvtxsec_z(i));
      fControlSecvtx_Mass_uncut->Fill(gData->Getvtxsec_mass(i));
      fControlSecvtx_Chi2_uncut->Fill(gData->Getvtxsec_chi2(i));
      fControlSecvtx_Ndof_uncut->Fill(gData->Getvtxsec_ndf(i));
      fControlSecvtx_Multi_uncut->Fill(gData->Getvtxsec_multi(i));
      fControlSecvtx_Cov1_uncut->Fill(gData->Getvtxsec_cov(i,0));
      fControlSecvtx_Cov2_uncut->Fill(gData->Getvtxsec_cov(i,1));
      fControlSecvtx_Cov3_uncut->Fill(gData->Getvtxsec_cov(i,2));
      fControlSecvtx_Cov4_uncut->Fill(gData->Getvtxsec_cov(i,3));
      fControlSecvtx_Cov5_uncut->Fill(gData->Getvtxsec_cov(i,4));
      fControlSecvtx_Cov6_uncut->Fill(gData->Getvtxsec_cov(i,5));
      fControlSecvtx2D_X_uncut->Fill(gData->Getvtxsec2d_x(i));
      fControlSecvtx2D_Y_uncut->Fill(gData->Getvtxsec2d_y(i));
      fControlSecvtx2D_Z_uncut->Fill(gData->Getvtxsec2d_z(i));
      fControlSecvtx2D_Mass_uncut->Fill(gData->Getvtxsec2d_mass(i));
      fControlSecvtx2D_Chi2_uncut->Fill(gData->Getvtxsec2d_chi2(i));
      fControlSecvtx2D_Ndof_uncut->Fill(gData->Getvtxsec2d_ndf(i));

    }


    if ( gVertex->GetXCut() ) {
      fControlX->Fill(gData->Getxvtx());
    }

    if ( gVertex->GetYCut() ) {
      fControlY->Fill(gData->Getyvtx());
    }

    if ( gVertex->GetZCut() ) {
      fControlZ->Fill(gData->Getzvtx());
    }

    if ( gVertex->GetXYCut() ) {
      fControlXY->Fill(xy);
    }

    if( gVertex->GetZCut() ) {
      fControlRedprm_X->Fill(gData->Getvtxredprm_x());
      fControlRedprm_Y->Fill(gData->Getvtxredprm_y());
      fControlRedprm_Z->Fill(gData->Getvtxredprm_z());
      fControlRedprm_Chi2->Fill(gData->Getvtxredprm_chi2());
      fControlRedprm_Ndof->Fill(gData->Getvtxredprm_ndf());
      fControlNr_secvtx->Fill(gData->Getnr_secvtx());

      for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

	fControlSecvtx_X->Fill(gData->Getvtxsec_x(i));
	fControlSecvtx_Y->Fill(gData->Getvtxsec_y(i));
	fControlSecvtx_Z->Fill(gData->Getvtxsec_z(i));
	fControlSecvtx_Mass->Fill(gData->Getvtxsec_mass(i));
	fControlSecvtx_Chi2->Fill(gData->Getvtxsec_chi2(i));
	fControlSecvtx_Ndof->Fill(gData->Getvtxsec_ndf(i));
	fControlSecvtx_Multi->Fill(gData->Getvtxsec_multi(i));
	fControlSecvtx_Cov1->Fill(gData->Getvtxsec_cov(i,0));
	fControlSecvtx_Cov2->Fill(gData->Getvtxsec_cov(i,1));
	fControlSecvtx_Cov3->Fill(gData->Getvtxsec_cov(i,2));
	fControlSecvtx_Cov4->Fill(gData->Getvtxsec_cov(i,3));
	fControlSecvtx_Cov5->Fill(gData->Getvtxsec_cov(i,4));
	fControlSecvtx_Cov6->Fill(gData->Getvtxsec_cov(i,5));
	fControlSecvtx2D_X->Fill(gData->Getvtxsec2d_x(i));
	fControlSecvtx2D_Y->Fill(gData->Getvtxsec2d_y(i));
	fControlSecvtx2D_Z->Fill(gData->Getvtxsec2d_z(i));
	fControlSecvtx2D_Mass->Fill(gData->Getvtxsec2d_mass(i));
	fControlSecvtx2D_Chi2->Fill(gData->Getvtxsec2d_chi2(i));
	fControlSecvtx2D_Ndof->Fill(gData->Getvtxsec2d_ndf(i));
      }
    }

    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
      fControlXMCTRUE_uncut->Fill(gData->Getmcvtx(0));
      fControlYMCTRUE_uncut->Fill(gData->Getmcvtx(1));
      fControlZMCTRUE_uncut->Fill(gData->Getmcvtx(2));
      fControlXMCTRUE->Fill(gData->Getmcvtx(0));
      fControlYMCTRUE->Fill(gData->Getmcvtx(1));
      if ( gVertex->GetZCut() ) {
	fControlZMCTRUE->Fill(gData->Getmcvtx(2));      
      }
    }

  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::FillGeneral() {
  //
  // fill general histograms for vertices
  if ( gDebug ) cout << endl << "GVertex::FillGeneral() called" << endl << endl;

  if ( gCards->GetVertexGeneral() ) {

    fGeneralX_uncut->Fill(gData->Getxvtx());
    fGeneralY_uncut->Fill(gData->Getyvtx());
    fGeneralZ_uncut->Fill(gData->Getzvtx());

    fGeneralRedprm_X_uncut->Fill(gData->Getvtxredprm_x());
    fGeneralRedprm_Y_uncut->Fill(gData->Getvtxredprm_y());
    fGeneralRedprm_Z_uncut->Fill(gData->Getvtxredprm_z());
    fGeneralRedprm_Chi2_uncut->Fill(gData->Getvtxredprm_chi2());
    fGeneralRedprm_Ndof_uncut->Fill(gData->Getvtxredprm_ndf());
    fGeneralNr_secvtx_uncut->Fill(gData->Getnr_secvtx());

    for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

      fGeneralSecvtx_X_uncut->Fill(gData->Getvtxsec_x(i));
      fGeneralSecvtx_Y_uncut->Fill(gData->Getvtxsec_y(i));
      fGeneralSecvtx_Z_uncut->Fill(gData->Getvtxsec_z(i));
      fGeneralSecvtx_Mass_uncut->Fill(gData->Getvtxsec_mass(i));
      fGeneralSecvtx_Chi2_uncut->Fill(gData->Getvtxsec_chi2(i));
      fGeneralSecvtx_Ndof_uncut->Fill(gData->Getvtxsec_ndf(i));
      fGeneralSecvtx_Multi_uncut->Fill(gData->Getvtxsec_multi(i));
      fGeneralSecvtx_Cov1_uncut->Fill(gData->Getvtxsec_cov(i,0));
      fGeneralSecvtx_Cov2_uncut->Fill(gData->Getvtxsec_cov(i,1));
      fGeneralSecvtx_Cov3_uncut->Fill(gData->Getvtxsec_cov(i,2));
      fGeneralSecvtx_Cov4_uncut->Fill(gData->Getvtxsec_cov(i,3));
      fGeneralSecvtx_Cov5_uncut->Fill(gData->Getvtxsec_cov(i,4));
      fGeneralSecvtx_Cov6_uncut->Fill(gData->Getvtxsec_cov(i,5));
      fGeneralSecvtx2D_X_uncut->Fill(gData->Getvtxsec2d_x(i));
      fGeneralSecvtx2D_Y_uncut->Fill(gData->Getvtxsec2d_y(i));
      fGeneralSecvtx2D_Z_uncut->Fill(gData->Getvtxsec2d_z(i));
      fGeneralSecvtx2D_Mass_uncut->Fill(gData->Getvtxsec2d_mass(i));
      fGeneralSecvtx2D_Chi2_uncut->Fill(gData->Getvtxsec2d_chi2(i));
      fGeneralSecvtx2D_Ndof_uncut->Fill(gData->Getvtxsec2d_ndf(i));
    }

    if ( gHeader->GetAllCuts() ) {
      fGeneralX->Fill(gData->Getxvtx());
      fGeneralY->Fill(gData->Getyvtx());
      fGeneralZ->Fill(gData->Getzvtx());      
    }

    if( gVertex->GetZCut() ) {
      fGeneralRedprm_X->Fill(gData->Getvtxredprm_x());
      fGeneralRedprm_Y->Fill(gData->Getvtxredprm_y());
      fGeneralRedprm_Z->Fill(gData->Getvtxredprm_z());
      fGeneralRedprm_Chi2->Fill(gData->Getvtxredprm_chi2());
      fGeneralRedprm_Ndof->Fill(gData->Getvtxredprm_ndf());
      fGeneralNr_secvtx->Fill(gData->Getnr_secvtx());

      for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

	fGeneralSecvtx_X->Fill(gData->Getvtxsec_x(i));
	fGeneralSecvtx_Y->Fill(gData->Getvtxsec_y(i));
	fGeneralSecvtx_Z->Fill(gData->Getvtxsec_z(i));
	fGeneralSecvtx_Mass->Fill(gData->Getvtxsec_mass(i));
	fGeneralSecvtx_Chi2->Fill(gData->Getvtxsec_chi2(i));
	fGeneralSecvtx_Ndof->Fill(gData->Getvtxsec_ndf(i));
	fGeneralSecvtx_Multi->Fill(gData->Getvtxsec_multi(i));
	fGeneralSecvtx_Cov1->Fill(gData->Getvtxsec_cov(i,0));  
	fGeneralSecvtx_Cov2->Fill(gData->Getvtxsec_cov(i,1)); 
	fGeneralSecvtx_Cov3->Fill(gData->Getvtxsec_cov(i,2)); 
	fGeneralSecvtx_Cov4->Fill(gData->Getvtxsec_cov(i,3)); 
	fGeneralSecvtx_Cov5->Fill(gData->Getvtxsec_cov(i,4)); 
	fGeneralSecvtx_Cov6->Fill(gData->Getvtxsec_cov(i,5)); 
	fGeneralSecvtx2D_X->Fill(gData->Getvtxsec2d_x(i));
	fGeneralSecvtx2D_Y->Fill(gData->Getvtxsec2d_y(i));
	fGeneralSecvtx2D_Z->Fill(gData->Getvtxsec2d_z(i));
	fGeneralSecvtx2D_Mass->Fill(gData->Getvtxsec2d_mass(i));
	fGeneralSecvtx2D_Chi2->Fill(gData->Getvtxsec2d_chi2(i));
	fGeneralSecvtx2D_Ndof->Fill(gData->Getvtxsec2d_ndf(i));
      }
    }

    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      fGeneralXMCTRUE_uncut->Fill(gData->Getmcvtx(0));
      fGeneralYMCTRUE_uncut->Fill(gData->Getmcvtx(1));
      fGeneralZMCTRUE_uncut->Fill(gData->Getmcvtx(2));
      if ( gHeader->GetAllCuts() ) {
	fGeneralXMCTRUE->Fill(gData->Getmcvtx(0));
	fGeneralYMCTRUE->Fill(gData->Getmcvtx(1));
	fGeneralZMCTRUE->Fill(gData->Getmcvtx(2));      
      }
    }

  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::Do() {
  //
  // execute per event
  if ( gDebug ) cout << endl << "GVertex::Do() called" << endl << endl;

  CheckZCut();
  CheckXCut();
  CheckYCut();
  CheckXYCut();

  CalcSecVTX();

  CheckBeamSpotCut();
  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::CheckZCut() {
  //
  // checks if vertex lies in z window around nominal vertex
  if ( gDebug ) cout << endl << "GVertex::CheckZCut() called" << endl << endl;

  if ( (gData->Getzvtx() >= (gCards->GetVertexNomZ()-gCards->GetVertexZCut())) && (gData->Getzvtx() <= (gCards->GetVertexNomZ()+gCards->GetVertexZCut())) )
    fZCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::CheckXCut() {
  //
  // checks if x vertex is not equal to nominal vertex
  if ( gDebug ) cout << endl << "GVertex::CheckXCut() called" << endl << endl;

  if ( gCards->GetVertexXCut() ) {
    if ( gData->Getxvtx() != gCards->GetVertexNomX() ) {
      fXCut = kTRUE;
    }
  } else {
    fXCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::CheckYCut() {
  //
  // checks if Y vertex is not equal to nominal vertex
  if ( gDebug ) cout << endl << "GVertex::CheckYCut() called" << endl << endl;

  if ( gCards->GetVertexYCut() ) {
    if ( gData->Getyvtx() != gCards->GetVertexNomY() ) {
      fYCut = kTRUE;
    }
  } else {
    fYCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::CheckXYCut() {
  //
  // checks if distance in xy of vertex to nominal vertex is less than cut
  if ( gDebug ) cout << endl << "GVertex::CheckXYCut() called" << endl << endl;

  if ( TMath::Sqrt(TMath::Power(gData->Getxvtx(),2)+TMath::Power(gData->Getyvtx(),2)) <= gCards->GetVertexXYCut() ) 
    fXYCut = kTRUE;

  return kTRUE;
}

//____________________________________________________________

Bool_t GVertex::CalcSecVTX() {
  //
  // Fills the SecVtx Information

  if (gDebug) cout << endl << "GVertex::CalcSecVTX() called" << endl << endl;

  TVector3 r2d_v, upt_v;

  Double_t phi_d;

  if( gVertex -> GetZCut() ) {

    fNr_secvtx = gData->Getnr_secvtx();

    for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

      fSecvtx_Mass  = gData->Getvtxsec_mass(i);
      fSecvtx_Chi2  = gData->Getvtxsec_chi2(i);
      fSecvtx_Ndof  = gData->Getvtxsec_ndf(i);
      fSecvtx_Multi = gData->Getvtxsec_multi(i);
      fSecvtx_Cov1  = gData->Getvtxsec_cov(i,0);
      fSecvtx_Cov2  = gData->Getvtxsec_cov(i,1);
      fSecvtx_Cov3  = gData->Getvtxsec_cov(i,2);
      fSecvtx_Cov4  = gData->Getvtxsec_cov(i,3);
      fSecvtx_Cov5  = gData->Getvtxsec_cov(i,4);
      fSecvtx_Cov6  = gData->Getvtxsec_cov(i,5);

      r2d_v.SetXYZ(gData->Getvtxsec_x(i)-gData->Getvtxredprm_x(), gData->Getvtxsec_y(i)-gData->Getvtxredprm_y(), 0);

      phi_d = gData->Getkt_phijet_a(i);

      upt_v.SetXYZ(TMath::Cos(phi_d),TMath::Sin(phi_d), 0);

      fSecvtx_DL2       = r2d_v.Dot(upt_v);
      fSecvtx_DL2_err   = (gData->Getvtxredprm_cov(0)+gData->Getvtxsec_cov(i,0))*(TMath::Power(TMath::Cos(phi_d),2));
      fSecvtx_DL2_err  += (gData->Getvtxredprm_cov(2)+gData->Getvtxsec_cov(i,2))*(TMath::Power(TMath::Sin(phi_d),2));
      fSecvtx_DL2_err  += 2*(gData->Getvtxredprm_cov(1)+gData->Getvtxsec_cov(i,1))*(TMath::Sin(phi_d)*TMath::Cos(phi_d));
      fSecvtx_DL2_err   = TMath::Sqrt(fSecvtx_DL2_err);
      fSecvtx_DL2_sign  = fSecvtx_DL2 / fSecvtx_DL2_err;

      //      cout <<"Decay length: "<< fSecvtx_DL2 <<" Decay length SI: " << fSecvtx_DL2_sign << endl;

    }

  }
 
  return kTRUE;

}

//_____________________________________________________________

Bool_t GVertex::Reset() {
  //
  // reset for each new event
  if ( gDebug ) cout << endl << "GVertex::Reset() called" << endl << endl;
  
  fZCut              = kFALSE;
  fXCut              = kFALSE;
  fYCut              = kFALSE;
  fXYCut             = kFALSE;
  fBeamSpotCut       = kFALSE;
  
  // variables for secondary vertex block

  fRedprm_X         = 0.;
  fRedprm_Y         = 0.;
  fRedprm_Z         = 0.;
  fRedprm_Chi2      = 0.;
  fRedprm_Ndof      = 0.;
  fNr_secvtx        = 0;
  fSecvtx_X         = 0.;
  fSecvtx_Y         = 0.;
  fSecvtx_Z         = 0.;
  fSecvtx_Mass      = 0.;
  fSecvtx_Chi2      = 0.;
  fSecvtx_Ndof      = 0.;
  fSecvtx_Multi     = 0;
  fSecvtx_Cov1      = 0.;
  fSecvtx_Cov2      = 0.;
  fSecvtx_Cov3      = 0.;
  fSecvtx_Cov4      = 0.;
  fSecvtx_Cov5      = 0.;
  fSecvtx_Cov6      = 0.;
  fSecvtx_DL2       = 0.;
  fSecvtx_DL2_err   = 0.;
  fSecvtx_DL2_sign  = 0.;

  fSecvtx2D_X       = 0.;
  fSecvtx2D_Y       = 0.;
  fSecvtx2D_Z       = 0.;
  fSecvtx2D_Mass    = 0.;
  fSecvtx2D_Chi2    = 0.;
  fSecvtx2D_Ndof    = 0.;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::GetAllCuts() {
  //
  // return flag if event passes all vertex cuts
  if ( gDebug ) cout << endl << "GVertex::GetAllCuts() called" << endl << endl;
  
  if ( GetZCut() && GetXCut() && GetYCut() && GetXYCut() && GetBeamSpotCut() )
    return kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

TString GVertex::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GVertex::PrintMessage() called" << endl << endl;

  TString dummy = "Vertices:\n\n";

  dummy.Append("Vertex: ");
  
  dummy.Append(gInclude->FormatedChar(" x: ",4));
  dummy.Append(gInclude->FormatedDouble(gData->Getxvtx(),3,2));
  dummy.Append(gInclude->FormatedChar(" y: ",4));
  dummy.Append(gInclude->FormatedDouble(gData->Getyvtx(),3,2));
  dummy.Append(gInclude->FormatedChar(" z: ",4));
  dummy.Append(gInclude->FormatedDouble(gData->Getzvtx(),3,2));
  dummy.Append(gInclude->FormatedChar(" all cuts: ",11));
  dummy.Append(gInclude->FormatedBool(GetAllCuts()));
  if ( fCurrentBeamSpot != 0 ) {
    dummy.Append("\n");
    dummy.Append(fCurrentBeamSpot->PrintMessage(""));
  }
  if ( fMCBeamSpot != 0 ) {
    dummy.Append("\nMC ");
    dummy.Append(fMCBeamSpot->PrintMessage(""));
  }

  dummy.Append("\n");
  

  return dummy;
}

//_____________________________________________________________

Bool_t GVertex::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GVertex::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("VERTEX") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}

//_____________________________________________________________

GBeamSpot* GVertex::CheckCurrentBeamSpot() {
  //
  // check beamspot for current event, this is only done once per run
  if ( gDebug ) cout << endl << "GVertex::CheckBeamSpot() called" << endl << endl;
  
  Int_t runnr = gData->Getrunnr();
  // only fill beamspot list if upgrade data
  if ( runnr >= gGeneral->Get03p_low() ) {
    if ( fBeamSpots == 0 ) {
      InitBeamSpotList();
    }
    GBeamSpot *spot = 0;
    for ( Int_t i = 0; i < fNBeamSpots; i++ ) {
      spot = ((GBeamSpot*)(fBeamSpots->At(i)));
      if ( spot->GetRun() == runnr  ) {

	fNoBeamSpotRunnr = 0;
	fLastValidBeamSpot = spot;

	return spot;
      }
    }
  }

  // no beamspot was found, set nobeamspotrunnr to runnr
  fNoBeamSpotRunnr = runnr;

  // no beam spot was found, substract last added lumi value from lumi in header
  // works only if lumi is determined automatically if mvdtake or evtake are selected
  if ( (gCards->GetEvtake() || gCards->GetMvdtake() ) && gRuns->GetAllCuts() ) {
    gHeader->DecreaseLuminosity(gRuns->GetLastAddedLuminosity());
  }

  return 0;
}

//_____________________________________________________________

Bool_t GVertex::InitBeamSpotList() {
  //
  // init list ov available beam spots
  if ( gDebug ) cout << endl << "GVertex::InitBeamSpotList() called" << endl << endl;

  // init array
  fBeamSpots = new TClonesArray("GBeamSpot",1300);
  fNBeamSpots = 0;

  TString filename = gSystem->Getenv("GUTCODEDIR");
  if(filename.Length() == 0) {
    TString error_msg = "Environment variable GUTCODEDIR is not set!";
    cout << error_msg << endl;
    gLister->FillErrorList(error_msg);
    return kFALSE;
  }

  if((gData->Getrunnr()>= gGeneral->Get03p_low()) && (gData->Getrunnr() <= gGeneral->Get03p_up()) ){
    filename.Append("/analysis/beamspot/beamspot_03p.txt");
    cout<< " filename beamspot "<< filename << endl;
  }  else if((gData->Getrunnr()>= gGeneral->Get04p_low())&& (gData->Getrunnr() <=gGeneral->Get04p_up()) ){
    filename.Append("/analysis/beamspot/beamspot_04p.txt");
    cout<< " filename beamspot "<< filename << endl;
  }  else if((gData->Getrunnr()>= gGeneral->Get05e_low())&& (gData->Getrunnr() <=gGeneral->Get05e_up()) ){
    filename.Append("/analysis/beamspot/beamspot_05e.txt");
    cout<< " filename beamspot "<< filename << endl;
  }

  ifstream stream(filename.Data());
  TString line = "";
  while (line.ReadLine(stream)) {
    istrstream input(line.Data());
    Int_t run             = 0;
    Int_t events          = 0;
    Double_t x_mean       = 0.0;
    Double_t x_sigma      = 0.0;
    Double_t y_mean       = 0.0;
    Double_t y_sigma      = 0.0;
    Double_t z_mean       = 0.0;
    Double_t z_sigma      = 0.0;
    Double_t x_zero       = 0.0;
    Double_t x_zero_sigma = 0.0;
    Double_t dx_dz        = 0.0;
    Double_t dx_dz_sigma  = 0.0;
    Double_t y_zero       = 0.0;
    Double_t y_zero_sigma = 0.0;
    Double_t dy_dz        = 0.0;
    Double_t dy_dz_sigma  = 0.0;

    input >> run;
    input >> events;
    input >> x_mean;
    input >> x_sigma;
    input >> y_mean;
    input >> y_sigma;
    input >> z_mean;
    input >> z_sigma;
    input >> x_zero;     
    input >> x_zero_sigma;
    input >> dx_dz;      
    input >> dx_dz_sigma;
    input >> y_zero;     
    input >> y_zero_sigma;
    input >> dy_dz;      
    input >> dy_dz_sigma;

    TClonesArray &spots = *fBeamSpots;
    new(spots[fNBeamSpots++]) GBeamSpot(run,events,x_mean,x_sigma,y_mean,y_sigma,z_mean,z_sigma,x_zero,x_zero_sigma,y_zero,y_zero_sigma,dx_dz,dx_dz_sigma,dy_dz,dy_dz_sigma);

  }

//   fBeamSpots->Sort(fNBeamSpots);

//   ofstream ostream("sortet.txt");

//   GBeamSpot *old  = 0;
//   GBeamSpot *spot = 0;
//   for ( Int_t i = 1; i < fNBeamSpots; i++ ) {
//     if ( i == 1 ) {
//       old = ((GBeamSpot*)(fBeamSpots->At(0)));
//       spot = ((GBeamSpot*)(fBeamSpots->At(i)));
//     } else {
//       old  = spot;
//       spot = ((GBeamSpot*)(fBeamSpots->At(i)));
//     }

//     if ( old->GetRun() == spot->GetRun() ) {
//       if ( old->GetEvents() > spot->GetEvents() ) {
// 	spot = old;
//       }
//     } else {
//       ostream << old->PrintMessage("SILVIA");
//     }

//     if ( i == (fNBeamSpots-1) )
//       ostream << spot->PrintMessage("SILVIA");

//   }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GVertex::CheckBeamSpotCut() {
  //
  // checks if event has beamspot 
  if ( gDebug ) cout << endl << "GVertex::CheckBeamSpotCut() called" << endl << endl;
  
  if ( gCards->GetVertexBeamSpotCut() ) {
    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      if ( fMCBeamSpot == 0 ) {
	fMCBeamSpot = new GBeamSpot(1,0,gCards->GetVertexBeamSpotX(),gCards->GetVertexBeamSpotXSigma(),
				    gCards->GetVertexBeamSpotY(),gCards->GetVertexBeamSpotYSigma(),
				    gCards->GetVertexBeamSpotZ(),gCards->GetVertexBeamSpotZSigma());
      }
      fBeamSpotCut = kTRUE;
    } else {
      // if last currentbeamspotcheck was successfull or if this is the first check
      if ( fNoBeamSpotRunnr == 0 ) {
	// if no current beamspot is available, get it
	if ( fCurrentBeamSpot == 0 ) {
	  fCurrentBeamSpot = CheckCurrentBeamSpot();
	}
	// if still no current beamspot is available, then this run has none
	if ( fCurrentBeamSpot == 0 ) {
	  fBeamSpotCut = kFALSE;
	} else {
	  // if the runnr from the beamspot is the same of the event, cut is true
	  if ( fCurrentBeamSpot->GetRun() == gData->Getrunnr() ) {
	    fBeamSpotCut = kTRUE;
	  } else {
	    // else, if the runnr is different, get the new current beamspot
	    fCurrentBeamSpot = CheckCurrentBeamSpot();
	    // if valid beamspot is available, cut is true, else false
	    if ( fCurrentBeamSpot != 0 ) {
	      fBeamSpotCut = kTRUE;
	    } else {
	      fBeamSpotCut = kFALSE;
	    }
	  }
	}
      } else {
	if ( fNoBeamSpotRunnr == gData->Getrunnr() ) {
	  fBeamSpotCut = kFALSE;
	} else {
	  // else, if the runnr is different, get the new current beamspot
	  fCurrentBeamSpot = CheckCurrentBeamSpot();
	  // if valid beamspot is available, cut is true, else false
	  if ( fCurrentBeamSpot != 0 ) {
	    fBeamSpotCut = kTRUE;
	  } else {
	    fBeamSpotCut = kFALSE;
	  }
	}
      }
    } 
    if(gCards->GetVertexUseAllRuns()&&(!this->GetBeamSpotCut())){
      fCurrentBeamSpot = fLastValidBeamSpot;
      if ( fCurrentBeamSpot != 0 ) fBeamSpotCut = kTRUE;
    }
  } else {
    fBeamSpotCut = kTRUE;
  }
  
  return kTRUE;
}

//_____________________________________________________________

GBeamSpot* GVertex::GetCurrentBeamSpot() {
  //
  // return current beamspot, if mc, return MC beamspot
  if ( gDebug ) cout << endl << "GVertex::GetCurrentBeamSpot() called" << endl << endl;
  
  if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
    return fMCBeamSpot;
  } else {
    return fCurrentBeamSpot;
  }


  return 0;
}
//_____________________________________________________________

GBeamSpot* GVertex::CheckEventBeamSpot() {
  //
  // check event beamspot
  if ( gDebug ) cout << endl << "GVertex::CheckEventBeamSpot() called" << endl << endl;
  if(fCurrentBeamSpot){
    Int_t run =fCurrentBeamSpot->GetRun();
    Int_t events = fCurrentBeamSpot->GetEvents();
    Double_t x_0 =fCurrentBeamSpot->GetX0();
    Double_t x_0_sigma =fCurrentBeamSpot->GetX0_Sigma();
    Double_t dx_dz =fCurrentBeamSpot->GetDX_DZ();
    Double_t dx_dz_sigma =fCurrentBeamSpot->GetDX_DZ_Sigma();
    Double_t y_0 =fCurrentBeamSpot->GetY0();
    Double_t y_0_sigma =fCurrentBeamSpot->GetY0_Sigma();
    Double_t dy_dz =fCurrentBeamSpot->GetDY_DZ();
    Double_t dy_dz_sigma =fCurrentBeamSpot->GetDY_DZ_Sigma();
    Double_t z_vtx =gData->Getzvtx();
    Double_t beam_event_x = x_0 + dx_dz*(z_vtx);
    Double_t beam_event_y = y_0 + dy_dz*(z_vtx);


    Double_t delta_beam_event_x = sqrt(x_0_sigma*x_0_sigma + dx_dz_sigma*(z_vtx)*dx_dz_sigma*(z_vtx));
    Double_t delta_beam_event_y = sqrt(y_0_sigma*y_0_sigma + dy_dz_sigma*(z_vtx)*dy_dz_sigma*(z_vtx));
    
    // DELTA Z VERTEX SET TO 10 AT THE MOMENT!!!

    Double_t zvtx_sigma =1;
    
    GBeamSpot* spot = new GBeamSpot(run,events, beam_event_x,delta_beam_event_x,beam_event_y,delta_beam_event_y,z_vtx,zvtx_sigma);

    return spot;
  }
  return 0;
}
//_____________________________________________________________

GBeamSpot* GVertex::GetEventBeamSpot() {
  //
  // return event beamspot, if mc, return MC beamspot
  if ( gDebug ) cout << endl << "GVertex::GetEventBeamSpot() called" << endl << endl;
  
  if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
    return fMCBeamSpot;
  } else {
    fEventBeamSpot = CheckEventBeamSpot() ; 
    return fEventBeamSpot;
  }


  return 0;
}
