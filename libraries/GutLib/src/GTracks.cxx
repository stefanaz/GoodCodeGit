//
// GTracks.cxx
//
// $Author: meyer $
// $Date: 2007/10/24 13:01:00 $
// $Revision: 1.30 $
//

#include <GTracks.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTracks)
#endif

GTracks *gTracks = 0;

//_____________________________________________________________
// GTracks
// Tracks Class for everything which is related only to tracks
//
//
GTracks::GTracks() : GPhysObj() {
  //
  // GTracks default constructor
  if ( gDebug ) cout << endl << "GTracks::GTracks ctor called" << endl << endl;

  // initialize global pointer
  gTracks = this;

  // initialize clonesarray
  fTracks  = new TClonesArray("GTrack",512);
  fNTracks = 0;
  fNCTDTracks = 0;
  fNREGTracks = 0;
  fNZTTTracks = 0;
  fNVertexTracks = 0;
  fFakeEventWeight = 0;
  // initialize general histograms
  fGeneralN                    = 0;
  fGeneralN_uncut              = 0;
  fGeneralNVertex              = 0;
  fGeneralNVertex_uncut        = 0;
  fGeneralNTotalOvVertex       = 0;
  fGeneralNTotalOvVertex_uncut = 0;

  // initialize control histograms
  fControlN                    = 0;
  fControlN_uncut              = 0;
  fControlNVertex              = 0;
  fControlNVertex_uncut        = 0;
  fControlNTotalOvVertex       = 0;
  fControlNTotalOvVertex_uncut = 0;

  //initialalize plots for fake distributions
  fTrackAllPt              = 0;
  fTrackAllEta_lowPt       = 0;
  fTrackAllPhi_lowPt       = 0;
  fTrackAllEta_highPt      = 0;
  fTrackAllPhi_highPt      = 0;
  fTrack2DAll_PtEta        = 0;
  fTrackAllPt_fake         = 0;
  fTrackAllEta_lowPt_fake  = 0;
  fTrackAllPhi_lowPt_fake  = 0;
  fTrackAllEta_highPt_fake = 0;
  fTrackAllPhi_highPt_fake = 0;
  fTrack2DAll_PtEta_fake   = 0;

  // initialize variables
  fMultiplicityCut  = kFALSE;
  fVertexCut        = kFALSE;
  fMinVertexCut     = kFALSE;
  fTotalOvVertexCut = kFALSE;

  // create histograms
  fOK = CreateHistograms();
  // initialize fake muon correction plots
  if(gCards->GetDoFake()&& gCards->GetMCLF()){
   
    ReadInHistogram("Probabilities/MC/FakeProbability2DMuonAll_PtEta");
  }


}

//_____________________________________________________________

GTracks::~GTracks() {
  //
  // GTracks default destructor
  if ( gDebug ) cout << endl << "GTracks::~GTracks dtor called" << endl << endl;

  fTracks->Delete();
  fNTracks = 0;
  fNCTDTracks = 0;
  fNREGTracks = 0;
  fNZTTTracks = 0;
  fNVertexTracks = 0;
  delete fTracks;
  if ( fFile != 0 )
    fFile->Close();


}

//_____________________________________________________________

Bool_t GTracks::CreateControl() {
  //
  // create control histograms
  if ( gDebug ) cout << endl << "GTracks::CreateControl() called" << endl << endl;

  if ( gCards->GetTRACKSControl() ) {

    Int_t    nbins = 100;
    Double_t nlow  =   0.;
    Double_t nhigh = 100.;
    Double_t ran_low = 0;
    Double_t ran_high = 1;


    fControlN                     = gHistogrammer->TH1DFactory("Tracks_Control","N","Tracks: number of tracks",nbins,nlow,nhigh,"number of tracks","Events");
    fControlN_uncut               = gHistogrammer->TH1DFactory("Tracks_Control","N_uncut","uncut Tracks: number of tracks",nbins,nlow,nhigh,"number of tracks","Events");
    fControlNVertex               = gHistogrammer->TH1DFactory("Tracks_Control","NVertex","Tracks: number of vertex tracks",nbins,nlow,nhigh,"number of vertex tracks","Events");
    fControlNVertex_uncut         = gHistogrammer->TH1DFactory("Tracks_Control","NVertex_uncut","uncut Tracks: number of vertex tracks",nbins,nlow,nhigh,"number of vertex tracks","Events");
    fControlNTotalOvVertex        = gHistogrammer->TH1DFactory("Tracks_Control","NTotalOvVertex","Tracks: number of total over vertex tracks",nbins,nlow,nhigh,"number of total over vertex tracks","Events");
    fControlNTotalOvVertex_uncut  = gHistogrammer->TH1DFactory("Tracks_Control","NTotalOvVertex_uncut","uncut Tracks: number of total over vertex tracks",nbins,nlow,nhigh,"number of total over vertex tracks","Events");
    fControlRandomNumber  = gHistogrammer->TH1DFactory("Tracks_Control","random number","Entries",nbins,ran_low,ran_high,"random number unique distribution","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::FillControl() {
  //
  // fill control histograms
  if ( gDebug ) cout << endl << "GTracks::FillControl() called" << endl << endl;

  if ( gCards->GetTRACKSControl() ) {

    fControlN_uncut->Fill(fNTracks);
    fControlNVertex_uncut->Fill(fNVertexTracks);
    if ( fNVertexTracks != 0 )
      fControlNTotalOvVertex_uncut->Fill(fNTracks/fNVertexTracks);
    
    if ( GetMultiplicityCut() ) {
      fControlN->Fill(fNTracks);
    }

    if ( GetVertexCut() && GetMinVertexCut() ) {
      fControlNVertex->Fill(fNVertexTracks);
    }

    if ( GetTotalOvVertexCut() ) {
      if ( fNVertexTracks != 0 )
	fControlNTotalOvVertex->Fill(fNTracks/fNVertexTracks);
    }

  }

  return kTRUE;
}

//_____________________________________________________________

GTrack* GTracks::GetTrackByID(Int_t index) {
  //
  // return track parameters of the track with index
  if ( gDebug ) cout << endl << "GTracks::GetTrack called" << endl << endl;

  GTrack* track = 0;

  if ( (index <= fNTracks) && (index >= 0) ) {
    for ( Int_t i = 0; i < fNTracks; i++ ) {
      track = ((GTrack*)(fTracks->At(i)));
      if ( track->GetID() == index )
	return track;
    }
  } else {
    TString msg = "GTracks::GetTrack: requested track index: ";
    msg += index;
    msg.Append(" is larger that total number of tracks: ");
    msg += fNTracks;
    gLister->FillErrorList(msg.Data());
  }
  return 0;
}

//_____________________________________________________________

GTrack* GTracks::GetNormalTrackByVCTRHLID(Int_t vctrhl_id) {
  //
  // return track parameters of normal track with vctrhl_id
  if ( gDebug ) cout << endl << "GTracks::GetTrack called" << endl << endl;

  GTrack* track = 0;

  if ( (vctrhl_id <= fNTracks) && (vctrhl_id >= 0) ) {
    for ( Int_t i = 0; i < fNTracks; i++ ) {
      track = ((GTrack*)(fTracks->At(i)));
      if ( track->GetType() != kZTT ) {
	if ( track->GetID() == vctrhl_id )
	  return track;
      }
    }
  } else {
    TString msg = "GTracks::GetNormalTrackByID: requested track index: ";
    msg += vctrhl_id;
    msg.Append(" is larger that total number of tracks: ");
    msg += fNTracks;
    gLister->FillErrorList(msg.Data());
  }
  return 0;
}

//_____________________________________________________________

GTrack* GTracks::GetZTTTrackByVCTRHLID(Int_t vctrhl_id) {
  //
  // return track parameters of ztt track with vctrhl_id
  if ( gDebug ) cout << endl << "GTracks::GetTrack called" << endl << endl;

  GTrack* track = 0;

  if ( (vctrhl_id <= fNTracks) && (vctrhl_id >= 0) ) {
    for ( Int_t i = 0; i < fNTracks; i++ ) {
      track = ((GTrack*)(fTracks->At(i)));
      if ( track->GetType() == kZTT ) {
	if ( track->GetID2() == vctrhl_id )
	  return track;
      }
    }
  } else {
    TString msg = "GTracks::GetNormalTrackByID: requested track index: ";
    msg += vctrhl_id;
    msg.Append(" is larger that total number of tracks: ");
    msg += fNTracks;
    gLister->FillErrorList(msg.Data());
  }
  return 0;
}

//_____________________________________________________________

GTrack* GTracks::GetTrack(Int_t index) {
  //
  // return track parameters of the track with index
  if ( gDebug ) cout << endl << "GTracks::GetTrack called" << endl << endl;

  GTrack* track = 0;

  if ( (index <= fNTracks) && (index >= 0) ) {
    track = ((GTrack*)(fTracks->At(index)));
    return track;
  } else {
    TString msg = "GTracks::GetTrack: requested track index: ";
    msg += index;
    msg.Append(" is larger that total number of tracks: ");
    msg += fNTracks;
    gLister->FillErrorList(msg.Data());
  }
  return track;
}

//_____________________________________________________________

Bool_t GTracks::Reset() {
  //
  // reset tracks object on event by event basis
  if ( gDebug ) cout << endl << "GTracks::Reset called" << endl << endl;

  // reset variables
  fMultiplicityCut  = kFALSE;
  fVertexCut        = kFALSE;
  fMinVertexCut     = kFALSE;
  fTotalOvVertexCut = kFALSE;
  fFakeEventWeight  = 0;
  // reset clonesarray
  fTracks->Clear();
  fNTracks = 0;
  fNCTDTracks = 0;
  fNREGTracks = 0;
  fNZTTTracks = 0;
  fNVertexTracks = 0;
  fFakeID  = 0;
  return kTRUE;
} 

//_____________________________________________________________

Bool_t GTracks::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GTracks::Do() called" << endl << endl;

  // fill clonesarray with tracks
  Fill();

  // check for multiplicity cut
  CheckMultiplicityCut();

  // check for cut on maximal vertex tracks
  CheckVertexCut();

  // check for cut on minimal vertex tracks
  CheckMinVertexCut();

  // check for cut on total over vertex tracks
  CheckTotalOvVertexCut();
  // choose fake muon candidate 
  if(gCards->GetDoFake() && gCards->GetMCLF()) ChooseFakeMuCand();
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::Fill() {
  //
  // fill clonesarray with tracks
  if ( gDebug ) cout << endl << "GTracks::Fill() called" << endl << endl;



  TClonesArray &tracks = *fTracks;

  for ( Int_t i = 0; i < gData->Gettrk_ntracks(); i++ ) {
    GTrack *track = 0;
    track = new(tracks[fNTracks++]) GTrack(gData->Gettrk_id(i),
					   gData->Gettrk_id2(i),
					   gData->Gettrk_type(i),
					   gData->Gettrk_px(i),
					   gData->Gettrk_py(i),
					   gData->Gettrk_pz(i),
					   gData->Gettrk_charge(i),
					   gData->Gettrk_vtx(i),
					   gData->Gettrk_prim_vtx(i),
					   gData->Gettrk_sec_vtx(i),
					   gData->Gettrk_vxid(i),
					   gData->Gettrk_endpos(i,0),
					   gData->Gettrk_endpos(i,1),
					   gData->Gettrk_endpos(i,2),
					   gData->Gettrk_nzbyt(i),
					   gData->Gettrk_naxial(i),
					   gData->Gettrk_nstereo(i),
					   gData->Gettrk_layinner(i),
					   gData->Gettrk_layouter(i),
					   gData->Gettrk_dedxctd(i),
					   gData->Gettrk_dedxctdcr(i),
					   gData->Gettrk_ndof(i),
					   gData->Gettrk_chi2(i),
					   gData->Gettrk_vchi2(i),
					   gData->Gettrk_nbr(i),
					   gData->Gettrk_nbz(i),
					   gData->Gettrk_nwu(i),
					   gData->Gettrk_nwv(i),
					   gData->Gettrk_dedxmvd(i),
					   gData->Gettrk_w(i),
					   gData->Gettrk_phizero(i),
					   gData->Gettrk_t(i),
					   gData->Gettrk_dzero(i),
					   gData->Gettrk_zzero(i));
    if ( track != 0 ) {
      for ( Int_t j = 0; j < 15; ++j ) {
	track->SetCov(j,gData->Gettrk_cov(i,j));
      }
      if ( track->GetType() == kCTD ) {
	fNCTDTracks += 1;
      }
      if ( track->GetType() == kREG ) {
	fNREGTracks += 1;
      }
      if ( track->GetType() == kZTT ) {
	fNZTTTracks += 1;
      }
      CheckUsedSuperLayersCut(track);
      CheckUsedHitsCut(track);
      CheckUsedStereoHitsCut(track);
      CheckZHCut(track);
      CheckMVDHitsCut(track);
      CheckAllCuts(track);
      if(gCards->GetDoFake() && gCards->GetMCLF()&& track->GetType()==kREG) CheckFakeBackground(track);
    }
  }

  fNVertexTracks = gData->Getntrkvtx();

  return kTRUE;
}

//_____________________________________________________________

TString GTracks::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GTracks::PrintMessage() called" << endl << endl;

  TString dummy = "";

  GTrack *track = 0;

  for ( Int_t i = 0; i < fNTracks; i++ ) {
    track = ((GTrack*)(fTracks->At(i)));
    dummy.Append(track->PrintMessage(option));
  }
  dummy.Append(gInclude->FormatedChar(" mult-cut: ",12));
  dummy.Append(gInclude->FormatedBool(fMultiplicityCut));
  dummy.Append(gInclude->FormatedChar(" vertex-cut: ",14));
  dummy.Append(gInclude->FormatedBool(fVertexCut));
  dummy.Append(gInclude->FormatedChar(" min vertex-cut: ",18));
  dummy.Append(gInclude->FormatedBool(fMinVertexCut));
  dummy.Append(gInclude->FormatedChar(" totovvert-cut: ",17));
  dummy.Append(gInclude->FormatedBool(fTotalOvVertexCut));

  return dummy;
}

//_____________________________________________________________

Bool_t GTracks::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GTracks::Print() called" << endl << endl;

  option.ToUpper();

  GTrack *track = 0;

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("TRACKS") || option.Contains("ALL") ) {
      gLister->FillOutputList("Tracks:\n\n");
      for ( Int_t i = 0; i < fNTracks; i++ ) {
	track = ((GTrack*)(fTracks->At(i)));
	track->Print(option);
      }
      gLister->FillOutputList("Cuts:");
      gLister->FillOutputList(gInclude->FormatedChar(" mult-cut: ",12));
      gLister->FillOutputList(gInclude->FormatedBool(fMultiplicityCut));
      gLister->FillOutputList(gInclude->FormatedChar(" vertex-cut: ",14));
      gLister->FillOutputList(gInclude->FormatedBool(fVertexCut));
      gLister->FillOutputList(gInclude->FormatedChar(" min vertex-cut: ",18));
      gLister->FillOutputList(gInclude->FormatedBool(fMinVertexCut));
      gLister->FillOutputList(gInclude->FormatedChar(" totovvert-cut: ",17));
      gLister->FillOutputList(gInclude->FormatedBool(fTotalOvVertexCut));
    gLister->FillOutputList("\n\n");
    }
  } else {
    cout << "Tracks:" << endl << endl;;
    for ( Int_t i = 0; i < fNTracks; i++ ) {
      track = ((GTrack*)(fTracks->At(i)));
      track->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CreateGeneral() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GTracks::CreateGeneral() called" << endl << endl;

  if ( gCards->GetTRACKSGeneral() ) {

    Int_t    nbins = 100;
    Double_t nlow  =   0.;
    Double_t nhigh = 100.;
    Int_t    ptbins     = 30;
    Double_t ptlow      = 0.;
    Double_t pthigh     = 15.;
    Int_t    etabins    = 40;
    Double_t etalow     = -4.0;
    Double_t etahigh    = 4;
    Int_t    phibins    = 36;   
    Double_t philow     = -TMath::Pi();    
    Double_t phihigh    =  TMath::Pi();    

    Int_t      fakePtNBins    = 6; 
    Double_t   fakePtBins[fakePtNBins+1];
    fakePtBins[0]  = 1.5;
    fakePtBins[1]  = 2.0;
    fakePtBins[2]  = 3.0;
    fakePtBins[3]  = 4.0;
    fakePtBins[4]  = 6.0;
    fakePtBins[5]  = 10.0;
    fakePtBins[6]  = 15.0;

    Int_t      fakeEtaNBins   = 8;
    Double_t   fakeEtaBins[fakeEtaNBins+1];
    fakeEtaBins[0]  = -2.4;
    fakeEtaBins[1]  = -1.6;
    fakeEtaBins[2]  = -1.1;
    fakeEtaBins[3]  = -0.75;
    fakeEtaBins[4]  =  0.25;
    fakeEtaBins[5]  =  0.75;
    fakeEtaBins[6]  =  1.3;
    fakeEtaBins[7]  =  2.3;
    fakeEtaBins[8]  =  3.0;


    fGeneralN                     = gHistogrammer->TH1DFactory("Tracks","N","Tracks: number of tracks",nbins,nlow,nhigh,"number of tracks","Events");
    fGeneralN_uncut               = gHistogrammer->TH1DFactory("Tracks","N_uncut","uncut Tracks: number of tracks",nbins,nlow,nhigh,"number of tracks","Events");
    fGeneralNVertex               = gHistogrammer->TH1DFactory("Tracks","NVertex","Tracks: number of vertex tracks",nbins,nlow,nhigh,"number of vertex tracks","Events");
    fGeneralNVertex_uncut         = gHistogrammer->TH1DFactory("Tracks","NVertex_uncut","uncut Tracks: number of vertex tracks",nbins,nlow,nhigh,"number of vertex tracks","Events");
    fGeneralNTotalOvVertex        = gHistogrammer->TH1DFactory("Tracks","NTotalOvVertex","Tracks: number of total over vertex tracks",nbins,nlow,nhigh,"number of total over vertex tracks","Events");
    fGeneralNTotalOvVertex_uncut  = gHistogrammer->TH1DFactory("Tracks","NTotalOvVertex_uncut","uncut Tracks: number of total over vertex tracks",nbins,nlow,nhigh,"number of total over vertex tracks","Events");

  fTrackAllPt              = gHistogrammer->TH1DFactory("Fake","TracksAllPt","Pt of all ",ptbins,ptlow,pthigh,"Pt_{rec}","Events");
  fTrackAllEta_lowPt       = gHistogrammer->TH1DFactory("Fake","TracksAllEtalow","Eta of all  lowPt",etabins,etalow,etahigh,"Eta_{rec}","Events");
  fTrackAllPhi_lowPt       = gHistogrammer->TH1DFactory("Fake","TracksAllPhilow","Phi of all lowPt",phibins,philow,phihigh,"Phi_{rec}","Events");
  fTrackAllEta_highPt      = gHistogrammer->TH1DFactory("Fake","TracksAllEtahigh","Eta of all  highPt",etabins,etalow,etahigh,"Eta_{rec}","Events");
  fTrackAllPhi_highPt      = gHistogrammer->TH1DFactory("Fake","TracksAllPhihigh","Phi of all  highPt",phibins,philow,phihigh,"Phi_{rec}","Events");
  fTrack2DAll_PtEta        = gHistogrammer->TH2DVarFactory("Fake","Tracks2DAll_PtEta","Pt vs Eta for all Tracks",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
  // fTrack2DAll_PtEta        = gHistogrammer->TH2DFactory("Fake","Tracks2DAll_PtEta","Pt vs Eta for all Tracks",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  if(gCards->GetDoFake()){
  fTrackAllPt_fake         = gHistogrammer->TH1DFactory("Fake","TracksAllPt_fake","Pt of all ",ptbins,ptlow,pthigh,"Pt_{rec}","Events");
  fTrackAllEta_lowPt_fake  = gHistogrammer->TH1DFactory("Fake","TracksAllEtalow_fake","Eta of all  lowPt",etabins,etalow,etahigh,"Eta_{rec}","Events");
  fTrackAllPhi_lowPt_fake  = gHistogrammer->TH1DFactory("Fake","TracksAllPhilow_fake","Phi of all lowPt",phibins,philow,phihigh,"Phi_{rec}","Events");
  fTrackAllEta_highPt_fake = gHistogrammer->TH1DFactory("Fake","TracksAllEtahigh_fake","Eta of all  highPt",etabins,etalow,etahigh,"Eta_{rec}","Events");
  fTrackAllPhi_highPt_fake = gHistogrammer->TH1DFactory("Fake","TracksAllPhihigh_fake","Phi of all  highPt",phibins,philow,phihigh,"Phi_{rec}","Events");
  fTrack2DAll_PtEta_fake   = gHistogrammer->TH2DFactory("Fake","Tracks2DAll_PtEta_fake","Pt vs Eta for all Tracks",etabins,etalow,etahigh,ptbins,ptlow,pthigh,"Eta","Pt","Events");
  //  fTrack2DAll_PtEta_fake   = gHistogrammer->TH2DVarFactory("Fake","Tracks2DAll_PtEta_fake","Pt vs Eta for all Tracks",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
  fTrack2DAll_PtEta_fake_diff   = gHistogrammer->TH2DVarFactory("Fake","differenc_2DAll_PtEta_fake","Pt vs Eta for all Tracks",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
  fTrack2DAll_PtEta_fake_diff   = gHistogrammer->TH2DVarFactory("Fake","differenc_2DAll_PtEta_fake","Pt vs Eta for all Tracks",fakeEtaNBins,fakeEtaBins,fakePtNBins,fakePtBins,"Eta","Pt","Events");
     }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GTracks::FillHistos() called" << endl << endl;

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  return kTRUE;
}

//_____________________________________________________________


Bool_t GTracks::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GTracks::FillGeneral() called" << endl << endl;

  if ( gCards->GetTRACKSGeneral() ) {

    fGeneralN_uncut->Fill(fNTracks,gHeader->GetWeight());
    fGeneralNVertex_uncut->Fill(fNVertexTracks,gHeader->GetWeight());
    if ( fNVertexTracks != 0 )
      fGeneralNTotalOvVertex_uncut->Fill(fNTracks/fNVertexTracks,gHeader->GetWeight());
    
    if ( gHeader->GetAllCuts() ) {
      fGeneralN->Fill(fNTracks,gHeader->GetWeight());
      fGeneralNVertex->Fill(fNVertexTracks,gHeader->GetWeight());
      if ( fNVertexTracks != 0 )
	fGeneralNTotalOvVertex->Fill(fNTracks/fNVertexTracks,gHeader->GetWeight());
    }

  }

  return kTRUE;
}
//_____________________________________________________________

Bool_t GTracks::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  //  if ( gDebug ) cout << endl << "GTracks::ObjectsFillHistos() called" << endl << endl;
  
  // loop over array
  for ( Int_t i = 0; i < fNTracks; i++ ) {
    GTrack *track = ((GTrack*)(fTracks->At(i)));

    // fill general plots
    ObjectsFillGeneral(track);
    
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::ObjectsFillGeneral(GTrack *track) {

  //  if ( gDebug ) cout << endl << "GTracks::ObjectsFillGeneral() called" << endl << endl;
  if(gCards->GetTRACKSGeneral()) {
    //  if(gCards->GetTRACKSGeneral()&& track->GetType()==kREG) {
    if(gHeader->GetAllCuts()){
      if(track->Pt()>1.5){
	if (gCards->GetDoFake())      fTrack2DAll_PtEta_fake->Fill(track->Eta(),track->Pt(),track->GetFakeWeight());  

	fTrackAllPt->Fill(track->Pt());
       	fTrack2DAll_PtEta->Fill(track->Eta(),track->Pt());
	
	
	if(track->Pt()>0.7&&track->Pt()<1.5){
	  fTrackAllEta_lowPt->Fill(track->Eta());   
	  fTrackAllPhi_lowPt->Fill(track->Phi());
	}   
	if(track->Pt()>1.5){
	  fTrackAllEta_highPt->Fill(track->Eta());   
	  fTrackAllPhi_highPt->Fill(track->Phi());   
	}
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckMultiplicityCut() {
  //
  // check multiplicity cut, cut on default track type
  if ( gDebug ) cout << endl << "GTracks::CheckMultiplicityCut called" << endl << endl;

  if ( gData->Getdef_trk_type() == 1 ) {
    if ( (fNCTDTracks)>gCards->GetTRACKSMultiplicity() )
      fMultiplicityCut = kTRUE;
  } else if ( gData->Getdef_trk_type() == 2 ) {
    if ( (fNREGTracks)>gCards->GetTRACKSMultiplicity() )
      fMultiplicityCut = kTRUE;
  } else if ( gData->Getdef_trk_type() == 3 ) {
    if ( (fNZTTTracks)>gCards->GetTRACKSMultiplicity() )
      fMultiplicityCut = kTRUE;
  } else {
    TString msg = "GTracks::CheckMultiplicityCut no valid default track type";
    gLister->FillErrorList(msg);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckUsedSuperLayersCut(GTrack *track) {
  //
  // check cut for used superlayers
  if ( gDebug ) cout << endl << "GTracks::CheckUsedSuperLayersCut called" << endl << endl;

  Int_t usedlayers = track->GetOuterLayer() - track->GetInnerLayer() +1;

  if ( usedlayers >= gCards->GetTRACKSUsedSuperLayersCut() )
    track->SetUsedSuperLayersCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckUsedHitsCut(GTrack *track) {
  //
  // check cut for used axial and stereo hits
  if ( gDebug ) cout << endl << "GTracks::CheckUsedHitsCut called" << endl << endl;

  Int_t usedhits = track->GetAxialHits() + track->GetStereoHits();

  if ( usedhits >= gCards->GetTRACKSUsedHitsCut() )
    track->SetUsedHitsCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckUsedStereoHitsCut(GTrack *track) {
  //
  // check cut for used stereo hits
  if ( gDebug ) cout << endl << "GTracks::CheckUsedStereoHitsCut called" << endl << endl;

  Int_t usedhits = track->GetStereoHits();

  if ( usedhits >= gCards->GetTRACKSUsedStereoHitsCut() )
    track->SetUsedStereoHitsCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckZHCut(GTrack *track) {
  //
  // check cut for z_h of associated helix parameters
  if ( gDebug ) cout << endl << "GTracks::CheckZHCut called" << endl << endl;

  Double_t z_h = track->GetZZero()/10;

  if ( TMath::Abs(z_h) <= gCards->GetTRACKSZHCut() )
    track->SetZHCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckMVDHitsCut(GTrack *track) {
  //
  // check cut for minimal number of mvd hits
  if ( gDebug ) cout << endl << "GTracks::CheckMVDHitsCut called" << endl << endl;

  Int_t mvdhits = track->GetMVDHits();

  if ( mvdhits >= gCards->GetTRACKSMVDHitsCut() )
    track->SetMVDHitsCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckVertexCut() {
  //
  // check cut on maximal vertex tracks
  if ( gDebug ) cout << endl << "GTracks::CheckVertexCut called" << endl << endl;

  if ( fNVertexTracks <= gCards->GetTRACKSVertexCut() )
    fVertexCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckTotalOvVertexCut() {
  //
  // check cut on total over vertex tracks
  if ( gDebug ) cout << endl << "GTracks::CheckTotalOvVertexCut called" << endl << endl;

  if ( fNVertexTracks != 0 ) {
    if ( (gGeneral->GetRunPeriod() == k03p)||(gGeneral->GetRunPeriod() == k04p)||(gGeneral->GetRunPeriod() == k03p04p) ) {
      if ( (fNREGTracks/fNVertexTracks) <= gCards->GetTRACKSTotalOvVertexCut() )
	fTotalOvVertexCut = kTRUE;
    } else {
      if ( (fNCTDTracks/fNVertexTracks) <= gCards->GetTRACKSTotalOvVertexCut() )
	fTotalOvVertexCut = kTRUE;
    }
  } else {
      fTotalOvVertexCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckMinVertexCut() {
  //
  // check cut on minimal vertex tracks
  if ( gDebug ) cout << endl << "GTracks::CheckMinVertexCut called" << endl << endl;

  if ( fNVertexTracks > gCards->GetTRACKSMinVertexCut() )
    fMinVertexCut = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckAllCuts(GTrack *track) {
  //
  // check all cuts
  if ( gDebug ) cout << endl << "GTracks::CheckAllCuts called" << endl << endl;
  
   if ( track->GetUsedSuperLayersCut() && 
       track->GetUsedHitsCut() && 
       track->GetUsedStereoHitsCut() && 
       track->GetZHCut() && 
       track->GetMVDHitsCut() )
     track->SetAllCuts(kTRUE);
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::CheckFakeBackground(GTrack *track){

 //set probability for fake muon
  if (gDebug) cout << endl << "GTracks::FakeWeight called" << endl << endl;

Double_t weight = 1;

 Int_t pteta_bin  = fFakeWeight_hist->FindBin(track->Eta(),track->Pt());
 weight = fFakeWeight_hist->GetBinContent(pteta_bin);
 track->SetFakeWeight(weight);
 if (weight!= 0.){
   fFakeEventWeight += weight;
   track->SetFakeWeight_cum(fFakeEventWeight);
 }
 else{
   track->SetFakeWeight_cum(10);
 }
 





return kTRUE;
}

//_____________________________________________________________

Bool_t GTracks::GetAllCuts() {
  //
  // get all cuts
  if ( gDebug ) cout << endl << "GTracks::GetAllCuts called" << endl << endl;
  
  Bool_t returny = kFALSE;
  
  if ( GetMultiplicityCut() && GetVertexCut() && GetMinVertexCut() && GetTotalOvVertexCut() )
    returny = kTRUE;

  return returny;
}
//_____________________________________________________________

 Bool_t GTracks::ChooseFakeMuCand()
 {
  //
  // choose fake muon candidate 
   if ( gDebug )  cout << endl << "GTracks::ChooseFakeMuCand() called" << endl << endl;

   Double_t random_prob = gRandom->Uniform(fFakeEventWeight);
   Double_t temp_random = random_prob/fFakeEventWeight;
   //   cout << "fFakeEventWeight " << fFakeEventWeight << endl;
   //   cout << "random_prob" << random_prob << endl;
   //   cout << "fFakeID " << fFakeID << endl;
   if ( gCards->GetTRACKSControl() ) fControlRandomNumber->Fill(temp_random);


   for ( Int_t i = 0; i < fNTracks; i++ ) {
     GTrack *track = ((GTrack*)(fTracks->At(i)));
     if (track->GetType()== 2){
       if(track->GetFakeWeight_cum()>=random_prob && track->GetFakeWeight_cum() != 10.){
	 fFakeID = track->GetID();
	 break;
       }
     }
   }
      
  return kTRUE;
}

//________________________________________________________________
 GTrack* GTracks::GetFakeMuCand()
 {
  //
  // get fake muon candidate 
  //  if ( gDebug ) cout << endl << "GTracks::GetFakeMuCand() called" << endl << endl;
   
   GTrack *track = 0;
   //   cout << "fFakeID"  << fFakeID  << endl;
   // cout << "fNTracks" << fNTracks << endl;
   if (fFakeID!=0) {
     track = (GTrack*)GetTrackByID(fFakeID);

	      //(fTracks->At(fFakeID)));
     //     cout << "type " << track->GetType() << endl;
     //cout << "PX " << track->Px() << endl;
     //     cout << " track->GetID() "<< track->GetID() << endl;
   }


   return track;
 }
//________________________________________________________________



Bool_t GTracks::ReadInHistogram(char *histoname) {
  //
  // read in histograms from root-file

  TString filename = gSystem->Getenv("GUTCODEDIR");
  filename.Append("/analysis/fake/");
  filename.Append(gCards->GetFakeProbabilityFile());

  fFile = new TFile(filename);

  if ( fFile->IsZombie() ) {
    cout << "GTracks::ReadinHistogram histogram-file: " << filename << " can not be found!" << endl;
    return kFALSE;
  }

  // get histograms 
    fFakeWeight_hist = (TH2D*)fFile->Get(histoname);

  
  
  return kTRUE;
}

//____________________________________________________________________

Bool_t GTracks::Finalize() {
  //
  // finalize operations of physics object, mainly for histograms
  if (gDebug) cout << endl << "GTracks::Finalize() called" << endl << endl;

  return kTRUE;
}
