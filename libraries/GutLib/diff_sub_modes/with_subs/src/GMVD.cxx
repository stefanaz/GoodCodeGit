//
// GMVD.cxx
//
// $Author: gutsche $
// $Date: 2004/06/07 09:59:31 $
// $Revision: 1.4 $
//

#include <GMVD.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifdef CF__MVD
#ifndef _vmptypes_h_
#include <vmptypes.h>
#endif

#ifndef _HelixTrack_h_
#include <HelixTrack.h>
#endif

#ifndef _ReconstructedHelixTrack_h_
#include <ReconstructedHelixTrack.h>
#endif

#ifndef _MVDReconstructedVertex_h_
#include <MVDReconstructedVertex.h>
#endif

#ifndef _MVDVertexPack_h_
#include <MVDVertexPack.h>
#endif
#endif

#ifndef __CINT__
ClassImp(GMVD)
#endif

GMVD *gMVD = 0;

//_____________________________________________________________
// GMVD
//
// deals with special MVD functionality
//
GMVD::GMVD() : GPhysObj() {
  //
  // GMVD default constructor
  if ( gDebug ) cout << endl << "GMVD::GMVD ctor called" << endl << endl;

  // initialize global pointer
  gMVD = this;

  // initialize ok flag
  fOK = kTRUE;

  // initialize variables
  fX = 0.0;
  fY = 0.0;
  fZ = 0.0;
  fX_without_muon = 0.0;
  fY_without_muon = 0.0;
  fZ_without_muon = 0.0;

  // initialize uncut control histograms
  fControlX_uncut = 0;
  fControlY_uncut = 0;
  fControlZ_uncut = 0;
  fControlX_without_muon_uncut = 0;
  fControlY_without_muon_uncut = 0;
  fControlZ_without_muon_uncut = 0;

  // initialize control histograms
  fControlX = 0;
  fControlY = 0;
  fControlZ = 0;
  fControlX_without_muon = 0;
  fControlY_without_muon = 0;
  fControlZ_without_muon = 0;

  // initialize uncut general histograms
  fGeneralX_uncut = 0;
  fGeneralY_uncut = 0;
  fGeneralZ_uncut = 0;
  fGeneralX_without_muon_uncut = 0;
  fGeneralY_without_muon_uncut = 0;
  fGeneralZ_without_muon_uncut = 0;

  // initialize general histograms
  fGeneralX = 0;
  fGeneralY = 0;
  fGeneralZ = 0;
  fGeneralX_without_muon = 0;
  fGeneralY_without_muon = 0;
  fGeneralZ_without_muon = 0;

  // init cut variables
  fAllCuts     = kFALSE;

  CreateHistograms();

}

//_____________________________________________________________

GMVD::~GMVD() {
  //
  // GMVD default destructor
  if ( gDebug ) cout << endl << "GMVD::~GMVD dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GMVD::CreateHistograms() {
  //
  // create histograms
  if ( gDebug ) cout << endl << "GMVD::CreateHistograms() called" << endl << endl;

  Bool_t returny = kFALSE;

  // create general histograms
  returny = this->CreateGeneral();

  // create control plots
  returny = this->CreateControl();

  return returny;
}

//_____________________________________________________________

Bool_t GMVD::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GMVD::FillHistos() called" << endl << endl;

  // fill general histograms
  this->FillGeneral();
  
  // fill control plots
  this->FillControl();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::CreateGeneral() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GMVD::CreateGeneral() called" << endl << endl;

  if ( gCards->GetMVDGeneral() ) {

    Int_t    xbins  =  8000;
    Double_t xlow   = -4.0;
    Double_t xhigh  =  4.0;
    Int_t    ybins  =  8000;
    Double_t ylow   = -4.0;
    Double_t yhigh  =  4.0;
    Int_t    zbins  =  1200;
    Double_t zlow   = -60.0;
    Double_t zhigh  =  60.0;

    fGeneralX_uncut = gHistogrammer->TH1DFactory("MVD","X_uncut","uncut ZTT Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralY_uncut = gHistogrammer->TH1DFactory("MVD","Y_uncut","uncut ZTT Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralZ_uncut = gHistogrammer->TH1DFactory("MVD","Z_uncut","uncut ZTT Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralX_without_muon_uncut = gHistogrammer->TH1DFactory("MVD","X_without_muon_uncut","uncut ZTT Vertex without chosen muon: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralY_without_muon_uncut = gHistogrammer->TH1DFactory("MVD","Y_without_muon_uncut","uncut ZTT Vertex without chosen muon: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralZ_without_muon_uncut = gHistogrammer->TH1DFactory("MVD","Z_without_muon_uncut","uncut ZTT Vertex without chosen muon: z",zbins,zlow,zhigh,"z [cm]","Events");

    fGeneralX = gHistogrammer->TH1DFactory("MVD","X","ZTT Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralY = gHistogrammer->TH1DFactory("MVD","Y","ZTT Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralZ = gHistogrammer->TH1DFactory("MVD","Z","ZTT Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");
    fGeneralX_without_muon = gHistogrammer->TH1DFactory("MVD","X_without_muon","ZTT Vertex without chosen muon: x",xbins,xlow,xhigh,"x [cm]","Events");
    fGeneralY_without_muon = gHistogrammer->TH1DFactory("MVD","Y_without_muon","ZTT Vertex without chosen muon: y",ybins,ylow,yhigh,"y [cm]","Events");
    fGeneralZ_without_muon = gHistogrammer->TH1DFactory("MVD","Z_without_muon","ZTT Vertex without chosen muon: z",zbins,zlow,zhigh,"z [cm]","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GMVD::FillGeneral() called" << endl << endl;

  if ( gCards->GetMVDGeneral() ) {

    fGeneralX_uncut->Fill(fX);
    fGeneralY_uncut->Fill(fY);
    fGeneralZ_uncut->Fill(fZ);
    fGeneralX_without_muon_uncut->Fill(fX_without_muon);
    fGeneralY_without_muon_uncut->Fill(fY_without_muon);
    fGeneralZ_without_muon_uncut->Fill(fZ_without_muon);

    if ( gHeader->GetAllCuts() ) {
      fGeneralX->Fill(fX);
      fGeneralY->Fill(fY);
      fGeneralZ->Fill(fZ);
      fGeneralX_without_muon->Fill(fX_without_muon);
      fGeneralY_without_muon->Fill(fY_without_muon);
      fGeneralZ_without_muon->Fill(fZ_without_muon);
    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::CreateControl() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GMVD::CreateControl() called" << endl << endl;

  if ( gCards->GetMVDControl() ) {

    Int_t    xbins  =  8000;
    Double_t xlow   = -4.0;
    Double_t xhigh  =  4.0;
    Int_t    ybins  =  8000;
    Double_t ylow   = -4.0;
    Double_t yhigh  =  4.0;
    Int_t    zbins  =  1200;
    Double_t zlow   = -60.0;
    Double_t zhigh  =  60.0;

    fControlX_uncut = gHistogrammer->TH1DFactory("MVD_Control","X_uncut","uncut ZTT Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlY_uncut = gHistogrammer->TH1DFactory("MVD_Control","Y_uncut","uncut ZTT Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlZ_uncut = gHistogrammer->TH1DFactory("MVD_Control","Z_uncut","uncut ZTT Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlX_without_muon_uncut = gHistogrammer->TH1DFactory("MVD_Control","X_without_muon_uncut","uncut ZTT Vertex without chosen muon: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlY_without_muon_uncut = gHistogrammer->TH1DFactory("MVD_Control","Y_without_muon_uncut","uncut ZTT Vertex without chosen muon: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlZ_without_muon_uncut = gHistogrammer->TH1DFactory("MVD_Control","Z_without_muon_uncut","uncut ZTT Vertex without chosen muon: z",zbins,zlow,zhigh,"z [cm]","Events");

    fControlX = gHistogrammer->TH1DFactory("MVD_Control","X","ZTT Vertex: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlY = gHistogrammer->TH1DFactory("MVD_Control","Y","ZTT Vertex: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlZ = gHistogrammer->TH1DFactory("MVD_Control","Z","ZTT Vertex: z",zbins,zlow,zhigh,"z [cm]","Events");
    fControlX_without_muon = gHistogrammer->TH1DFactory("MVD_Control","X_without_muon","ZTT Vertex without chosen muon: x",xbins,xlow,xhigh,"x [cm]","Events");
    fControlY_without_muon = gHistogrammer->TH1DFactory("MVD_Control","Y_without_muon","ZTT Vertex without chosen muon: y",ybins,ylow,yhigh,"y [cm]","Events");
    fControlZ_without_muon = gHistogrammer->TH1DFactory("MVD_Control","Z_without_muon","ZTT Vertex without chosen muon: z",zbins,zlow,zhigh,"z [cm]","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::FillControl() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GMVD::FillControl() called" << endl << endl;

  if ( gCards->GetMVDControl() ) {

    fControlX_uncut->Fill(fX);
    fControlY_uncut->Fill(fY);
    fControlZ_uncut->Fill(fZ);
    fControlX_without_muon_uncut->Fill(fX_without_muon);
    fControlY_without_muon_uncut->Fill(fY_without_muon);
    fControlZ_without_muon_uncut->Fill(fZ_without_muon);

    fControlX->Fill(fX);
    fControlY->Fill(fY);
    fControlZ->Fill(fZ);
    fControlX_without_muon->Fill(fX_without_muon);
    fControlY_without_muon->Fill(fY_without_muon);
    fControlZ_without_muon->Fill(fZ_without_muon);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GMVD::Do() called" << endl << endl;
  
  if ( gCards->GetMVDActivate() ) {

//     // check if event passes all previous cuts, then do mvd vertexing
//     fAllCuts = kTRUE;
//     if ( gHeader->GetAllCuts() ) {
//       fAllCuts = kFALSE;
//       MakeZTTVertex();
//       MakeZTTVertexWithoutMuon();
//     } else {
//       fAllCuts = kFALSE;
//     }

    fAllCuts = kTRUE;

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GMVD::Reset() called" << endl << endl;

  fX = 0.0;
  fY = 0.0;
  fZ = 0.0;
  fX_without_muon = 0.0;
  fY_without_muon = 0.0;
  fZ_without_muon = 0.0;

  fAllCuts     = kFALSE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::Finalize() {
  //
  // finalize operations of physics object, mainly for histograms
  if ( gDebug ) cout << endl << "GMVD::Finalize() called" << endl << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::GetAllCuts() {
  //
  // returns flag for physics object if event passes all object cuts
  if ( gDebug ) cout << endl << "GMVD::GetAllCuts() called" << endl << endl;

  if ( fAllCuts || !gCards->GetMVDActivate() ) 
    return kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

TString GMVD::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GMVD::PrintMessage() called" << endl << endl;

  TString dummy = "MVD:\n\n";

  return dummy;
}

//_____________________________________________________________

Bool_t GMVD::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMVD::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("MVD") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::MakeZTTVertex() {
  //
  // make vertex from ztt tracks using kfrecon
  if ( gDebug ) cout << endl << "GMVD::MakeZTTVertex called" << endl << endl;

#ifdef CF__MVD

  vector<ReconstructedHelixTrack> tracks;
  for ( Int_t i = 0; i < gTracks->GetNTracks(); ++i ) {
    GTrack *track = gTracks->GetTrack(i);
    if ( track->GetAllCuts() && ( track->GetType() == kZTT ) ) {

      HelixTrack temp(track->GetW(),track->GetT(),track->GetPhiZero(),track->GetDZero(),track->GetZZero());

      FIVEMATRIX cov2;
      VECTOR5 nr;
      
      nr[0]=track->GetCov(0);nr[1]=track->GetCov(1);nr[2]=track->GetCov(2); nr[3]=track->GetCov(3); nr[4]=track->GetCov(4);
      cov2.setRow(0,nr);
      nr[0]=track->GetCov(1);nr[1]=track->GetCov(5);nr[2]=track->GetCov(6); nr[3]=track->GetCov(7); nr[4]=track->GetCov(8);
      cov2.setRow(1,nr);
      nr[0]=track->GetCov(2);nr[1]=track->GetCov(6);nr[2]=track->GetCov(9); nr[3]=track->GetCov(10);nr[4]=track->GetCov(11);
      cov2.setRow(2,nr);
      nr[0]=track->GetCov(3);nr[1]=track->GetCov(7);nr[2]=track->GetCov(10);nr[3]=track->GetCov(12);nr[4]=track->GetCov(13);
      cov2.setRow(3,nr);
      nr[0]=track->GetCov(4);nr[1]=track->GetCov(8);nr[2]=track->GetCov(11);nr[3]=track->GetCov(13);nr[4]=track->GetCov(14);
      cov2.setRow(4,nr);
      
      FIVEMATRIX B(0.0);
      B[0][1]=.1; B[1][4]=1.; B[2][0]=1.; B[3][2]= 10.; B[4][3]=10.;
      FIVEMATRIX cov1 =  B*cov2*B.transpose();
      
      ReconstructedHelixTrack temp2(temp,cov1,track->GetNDoF(),track->GetChi2());
      
      tracks.push_back(temp2);
    }
  }

  MVDVertexPack vertex_pack(tracks,25);

  if ( vertex_pack.numberOfVertices() > 0 ) {
    Int_t max_tracks = 0;
    Int_t chosen_vertex = 0;
//     cout << "______________" << endl;
//     cout << "orange vertex x: " << gData->Getxvtx() << " y: " << gData->Getyvtx() << " z: " << gData->Getzvtx() << endl;
    for ( Int_t vertex = 1; vertex <= vertex_pack.numberOfVertices(); ++vertex ) {
      MVDReconstructedVertex prim_vertex = vertex_pack.vertex(vertex);
//       cout << "vertex " << vertex;
//       cout << " number of vertex tracks: " << prim_vertex.numberOfTracks();
//       THREEVECTOR prim_vertex_position = prim_vertex.position();
      if ( prim_vertex.numberOfTracks() > max_tracks ) {
	max_tracks = vertex_pack.numberOfVertices();
	chosen_vertex = vertex;
      }
    }
//     cout << "chosen vertex: " << chosen_vertex << endl;
    MVDReconstructedVertex selected_prim_vertex = vertex_pack.vertex(chosen_vertex);
    THREEVECTOR selected_prim_vertex_position = selected_prim_vertex.position();
    fX = selected_prim_vertex_position[0]/10;
    fY = selected_prim_vertex_position[1]/10;
    fZ = selected_prim_vertex_position[2]/10;
//     cout<<" vertex x: " << selected_prim_vertex_position[0]/10;
//     cout<<" vertex y: " << selected_prim_vertex_position[1]/10;
//     cout<<" vertex z: " << selected_prim_vertex_position[2]/10 << endl;
    fAllCuts = kTRUE;
  }

#endif

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMVD::MakeZTTVertexWithoutMuon() {
  //
  // make vertex from ztt tracks using kfrecon rejecting chosen muon
  if ( gDebug ) cout << endl << "GMVD::MakeZTTVertexWithoutMuon called" << endl << endl;

#ifdef CF__MVD

  vector<ReconstructedHelixTrack> tracks;
  GMJMatch *chosenMatch = gMJMatchs->GetChosen();
  if ( chosenMatch != 0 ) {
    GMuon *chosenMuon = chosenMatch->GetMuon();
    for ( Int_t i = 0; i < gTracks->GetNTracks(); ++i ) {
      GTrack *track = gTracks->GetTrack(i);
      if ( track->GetAllCuts() && ( track->GetType() == kZTT ) ) {
	if ( ( track->GetID() != chosenMuon->GetZTTTrack()->GetID() ) ) {

	  HelixTrack temp(track->GetW(),track->GetT(),track->GetPhiZero(),track->GetDZero(),track->GetZZero());

	  FIVEMATRIX cov2;
	  VECTOR5 nr;
      
	  nr[0]=track->GetCov(0);nr[1]=track->GetCov(1);nr[2]=track->GetCov(2); nr[3]=track->GetCov(3); nr[4]=track->GetCov(4);
	  cov2.setRow(0,nr);
	  nr[0]=track->GetCov(1);nr[1]=track->GetCov(5);nr[2]=track->GetCov(6); nr[3]=track->GetCov(7); nr[4]=track->GetCov(8);
	  cov2.setRow(1,nr);
	  nr[0]=track->GetCov(2);nr[1]=track->GetCov(6);nr[2]=track->GetCov(9); nr[3]=track->GetCov(10);nr[4]=track->GetCov(11);
	  cov2.setRow(2,nr);
	  nr[0]=track->GetCov(3);nr[1]=track->GetCov(7);nr[2]=track->GetCov(10);nr[3]=track->GetCov(12);nr[4]=track->GetCov(13);
	  cov2.setRow(3,nr);
	  nr[0]=track->GetCov(4);nr[1]=track->GetCov(8);nr[2]=track->GetCov(11);nr[3]=track->GetCov(13);nr[4]=track->GetCov(14);
	  cov2.setRow(4,nr);
      
	  FIVEMATRIX B(0.0);
	  B[0][1]=.1; B[1][4]=1.; B[2][0]=1.; B[3][2]= 10.; B[4][3]=10.;
	  FIVEMATRIX cov1 =  B*cov2*B.transpose();
      
	  ReconstructedHelixTrack temp2(temp,cov1,track->GetNDoF(),track->GetChi2());
      
	  tracks.push_back(temp2);
	}
      }

    }

    MVDVertexPack vertex_pack(tracks,25);

    if ( vertex_pack.numberOfVertices() > 0 ) {
      Int_t max_tracks = 0;
      Int_t chosen_vertex = 0;
      for ( Int_t vertex = 1; vertex <= vertex_pack.numberOfVertices(); ++vertex ) {
	MVDReconstructedVertex prim_vertex = vertex_pack.vertex(vertex);
	if ( prim_vertex.numberOfTracks() > max_tracks ) {
	  max_tracks = vertex_pack.numberOfVertices();
	  chosen_vertex = vertex;
	}
      }
      MVDReconstructedVertex selected_prim_vertex = vertex_pack.vertex(chosen_vertex);
      THREEVECTOR selected_prim_vertex_position = selected_prim_vertex.position();
      fX_without_muon = selected_prim_vertex_position[0]/10;
      fY_without_muon = selected_prim_vertex_position[1]/10;
      fZ_without_muon = selected_prim_vertex_position[2]/10;
    }

    chosenMuon->CalcImpactParameter(fX_without_muon,0,fY_without_muon,0,fZ_without_muon,0);

  } else {
    fX_without_muon = -99;
    fY_without_muon = -99;
    fZ_without_muon = -99;
  }

#endif

  return kTRUE;
}
