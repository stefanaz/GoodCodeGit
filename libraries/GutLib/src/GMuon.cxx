//
// GMuon.cxx
//
// $Author: ibloch $
// $Date: 2005/10/12 16:49:18 $
// $Revision: 1.55 $
//

#include <GMuon.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMuon)
#endif

//_____________________________________________________________
// GMuon
//
// muon class
//
GMuon::GMuon() : TLorentzVector() {
  //
  // GMuon default constructor
  if ( gDebug ) cout << endl << "GMuon::GMuon default ctor called" << endl << endl;

  fOK             = kTRUE;

  // initialize cut flags
  fQualCut             = kFALSE;
  fFinderCut           = kFALSE;
  fEtaCut              = kFALSE;
  fTakeCut             = kFALSE;
  fPtCut               = kFALSE;
  fPCut                = kFALSE;
  fBrematCut           = kFALSE;
  fMPMatchCut          = kFALSE;
  fMUBACCut            = kFALSE;
  fForwardTrackMuonCut = kFALSE;
  fBACFQualityCut      = kFALSE;
  fVcidLowCut          = kFALSE;
  fVcidUpCut           = kFALSE;
  fAllCuts             = kFALSE;
  fForwardTrackMuon    = kFALSE;
  fBACFMuon            = kFALSE;
  fBest                = kFALSE;
  fMVCuts              = kFALSE;
  fOnlyVertexFittedCut = kFALSE;

  fMC             = 0;
  fMCQuark        = 0;
  fMCDirectParent = 0;

  fFmufiCID       = 0;

  fMatched        = kFALSE;
  fQualModified   = kFALSE;

  fMuJetMass    = 0.;
  fMuJetEt      = 0.;
  fImpactMuon2D = 0.;
  fImpactSig    = 0.;

  fImpactParameter               = -9999.99;
  f2DImpactParameter             = -9999.99;
  fImpactParameterSignificance   = -9999.99;
  f2DImpactParameterSignificance = -9999.99;

  f2DBeamSpotImpactParameter             = -9999.99;
  f2DBeamSpotImpactParameterSignificance = -9999.99;

  f2DMCBeamSpotImpactParameter             = -9999.99;
  f2DMCBeamSpotImpactParameterSignificance = -9999.99;

  fWeight = 1.0;

  fTrack = 0;
  fZTTTrack = 0;

  fWeight = 1.0;

  fEfficiencyReset = kFALSE;
  fMuTrueFl = 0;
  fMuTrueDecayDist = 0;
 
}

//_____________________________________________________________

GMuon::GMuon(Int_t id, EZMuonType type,
	     Int_t muqual, Int_t charge, 
	     Double_t mupx, Double_t mupy, Double_t mupz, Double_t muperr,
	     Int_t mutrfl, Int_t mutrid, Int_t muvcid, 
	     Int_t muvtxfl, Int_t muvtxid,
	     Int_t muglomu, Int_t mubremat, Int_t mubacmat, Int_t mumubac, Int_t mumamma, Int_t mumpmat, Int_t mumufo, 
	     Int_t mumip, Int_t mumv, Int_t muztid,
	     Int_t mucalfl, Float_t muhac2, Int_t muzufid, Double_t mupmip,  
	     Int_t muchfl, Int_t muchid, Double_t mupmat, 
	     Double_t mubacfl, Int_t mubacid, Int_t munphi,
	     Int_t mujetfl, Int_t mujetid_a, Double_t mujetdr_a, Double_t mujetpt,Int_t mutruefl, Float_t mudecdist) : TLorentzVector() {
  //
  // GMuon normal constructor
  if ( gDebug ) cout << endl << "GMuon::GMuon normal ctor called" << endl << endl;

  // set variables
  fID          = id;
  fType        = type;
  fQual        = muqual;
  fmuis01      = -9999.;
  fmuis02      = -9999.;
  fmuis03      = -9999.;
  fmuis04      = -9999.;
  fmuis05      = -9999.;
  fmuis06      = -9999.;
  fmuis07      = -9999.;
  fmuis08      = -9999.;
  fmuis09      = -9999.;
  fmuis10      = -9999.;
  fCharge      = charge;
  this->SetPx(mupx);
  this->SetPy(mupy);
  this->SetPz(mupz);
  this->SetE(TMath::Sqrt(mupx*mupx+mupy*mupy+mupz*mupz+gCards->GetMassMuon()*gCards->GetMassMuon()));
  fTrackFlag   = mutrfl;
  fTrackID     = mutrid;
  fVctrhlID    = muvcid;
  fVertexFlag  = muvtxfl;
  fVertexID    = muvtxid;
  fGlomuID     = muglomu;
  fBrematID    = mubremat;
  fBacMatID    = mubacmat;
  fMuBacID     = mumubac;
  fMammaID     = mumamma;
  fMPMatchID   = mumpmat;
  fMufoID      = mumufo;
  fMipID       = mumip;
  fMvID        = mumv;
  fZufoType    = mucalfl;
  fZufoID      = muzufid;
  fCalProbMV   = mupmip;
  fChamberFlag = muchfl;
  fChamberID   = muchid;
  fMuhac2      = muhac2;
  fMundof      = gMuons->GetMuonMundof();
  fMunphi      = munphi;
  fMuz         = gMuons->GetMuonMuz();
  fMuztid      = muztid;
  fProb        = mupmat;
  fBacFlag     = mubacfl;
  fBacID       = mubacid;
  fJetFlag     = mujetfl;
  fJetID       = mujetid_a;
  fJetPt       = mujetpt;
  fJetDr       = mujetdr_a;
  fOK          = kTRUE;
  fMuTrueFl        = mutruefl;
  fMuTrueDecayDist = mudecdist;


  // check flag for finder
  EvaluateFinders();

  // initialize cut flags
  fQualCut             = kFALSE;
  fFinderCut           = kFALSE;
  fEtaCut              = kFALSE;
  fTakeCut             = kFALSE;
  fPtCut               = kFALSE;
  fPCut                = kFALSE;
  fBrematCut           = kFALSE;
  fMPMatchCut          = kFALSE;
  fMUBACCut            = kFALSE;
  fForwardTrackMuonCut = kFALSE;
  fBACFQualityCut      = kFALSE;
  fVcidLowCut          = kFALSE;
  fVcidUpCut           = kFALSE;
  fAllCuts             = kFALSE;
  fForwardTrackMuon    = kFALSE;
  fBACFMuon            = kFALSE;
  fBest                = kFALSE;
  fMVCuts              = kFALSE;
  fOnlyVertexFittedCut = kFALSE;

  fMC             = 0;
  fMCQuark        = 0;
  fMCDirectParent = 0;

  fFmufiCID       = 0;

  fMatched        = kFALSE;
  fQualModified   = kFALSE;

  fMuJetMass    = gMuons->GetMuonJetMass();
  fMuJetEt      = gMuons->GetMuonJetEt();
  fImpactMuon2D = gMuons->GetMuonImp();
  fImpactSig    = gMuons->GetMuonImpSig();

  fImpactParameter               = -9999.99;
  f2DImpactParameter             = -9999.99;
  fImpactParameterSignificance   = -9999.99;
  f2DImpactParameterSignificance = -9999.99;

  f2DBeamSpotImpactParameter             = -9999.99;
  f2DBeamSpotImpactParameterSignificance = -9999.99;

  f2DMCBeamSpotImpactParameter             = -9999.99;
  f2DMCBeamSpotImpactParameterSignificance = -9999.99;

  fTrack = gTracks->GetNormalTrackByVCTRHLID(fVctrhlID);
  fZTTTrack = gTracks->GetZTTTrackByVCTRHLID(fVctrhlID);

  fWeight = 1.0;

  fEfficiencyReset = kFALSE;

}

//_____________________________________________________________

GMuon::~GMuon() {
  //
  // GMuon default destructor
  if ( gDebug ) cout << endl << "GMuon::~GMuon dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GMuon::EvaluateFinders(){
  // check flag for finder
  Int_t requirement = 0;
  if ( fGlomuID > requirement ) 
    fGlomu = kTRUE;
  else
    fGlomu = kFALSE;
  if ( fBrematID > requirement ) 
    fBremat = kTRUE;
  else
    fBremat = kFALSE;
  if ( fBacMatID > requirement ) 
    fBacMat = kTRUE;
  else
    fBacMat = kFALSE;
  if ( fMuBacID > requirement ) 
    fMuBac = kTRUE;
  else
    fMuBac = kFALSE;
  if ( fMammaID > requirement ) 
    fMamma = kTRUE;
  else
    fMamma = kFALSE;
  if ( fMPMatchID > requirement ) 
    fMPMatch = kTRUE;
  else
    fMPMatch = kFALSE;
  if ( fMufoID > requirement ) 
    fMufo = kTRUE;
  else
    fMufo = kFALSE;
  if ( fMipID > requirement ) 
    fMip = kTRUE;
  else
    fMip = kFALSE;
  if ( fMvID > requirement ) 
    fMv = kTRUE;
  else
    fMv = kFALSE;

  if ( fBremat && (fChamberFlag == 3 ) )
    fBrematInnerOuter = kTRUE;
  else
    fBrematInnerOuter = kFALSE;
  
  //  if ( fGlomu || fBremat || fMuBac || fMamma || fMPMatch || fMufo || fMip )
  if ( fGlomu || fBremat || fBacMat || fMuBac || fMamma || fMPMatch || fMufo || fMip )
    fAllExcpMV = kTRUE;
  else
    fAllExcpMV = kFALSE;
  
  return kTRUE;
}

//_____________________________________________________________

TString GMuon::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GMuon::PrintMessage called" << endl << endl;

  TString dummy = "GMuon: ";
  
  if ( fType == kBarrel )
      dummy.Append("Type: Barrel ");
  else if ( fType == kRear )
    dummy.Append("Type: Rear     ");
  else if ( fType == kForward )
    dummy.Append("Type: Forward  ");
  else 
    dummy.Append("Type: Unknown  ");

  dummy.Append(gInclude->FormatedChar(" id: ",5));
  dummy.Append(gInclude->FormatedInt(fID,2,0," "));
  dummy.Append(gInclude->FormatedChar(" charge: ",9));
  dummy.Append(gInclude->FormatedInt((Int_t)fCharge,3,0," "));
  dummy.Append(gInclude->FormatedChar(" qual: ",9));
  dummy.Append(gInclude->FormatedInt(fQual,3,0," "));
  dummy.Append(gInclude->FormatedChar(" track flg: ",13));
  dummy.Append(gInclude->FormatedInt(fTrackFlag,3,0," "));
  dummy.Append(gInclude->FormatedChar(" track id: ",12));
  dummy.Append(gInclude->FormatedInt(fTrackID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" vctrhl: ",9));
  dummy.Append(gInclude->FormatedInt(fVctrhlID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" chfl: ",9));
  dummy.Append(gInclude->FormatedInt(fChamberFlag,3,0," "));
  dummy.Append(gInclude->FormatedChar(" chid: ",9));
  dummy.Append(gInclude->FormatedInt(fChamberID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" prob: ",10));
  dummy.Append(gInclude->FormatedDouble(fProb,1,2));
  dummy.Append(gInclude->FormatedChar(" px: ",5));
  dummy.Append(gInclude->FormatedDouble(this->Px(),4,2));
  dummy.Append(gInclude->FormatedChar(" py: ",5));
  dummy.Append(gInclude->FormatedDouble(this->Py(),4,2));
  dummy.Append(gInclude->FormatedChar(" pz: ",5));
  dummy.Append(gInclude->FormatedDouble(this->Pz(),4,2));
  dummy.Append(gInclude->FormatedChar(" p: ",4));
  dummy.Append(gInclude->FormatedDouble(this->P(),3,2));
  dummy.Append(gInclude->FormatedChar(" theta: ",8));
  dummy.Append(gInclude->FormatedDouble(this->Theta(),2,2));
  dummy.Append(gInclude->FormatedChar(" eta: ",8));
  dummy.Append(gInclude->FormatedDouble(this->Eta(),2,2));
  dummy.Append(gInclude->FormatedChar(" phi: ",8));
  dummy.Append(gInclude->FormatedDouble(this->Phi(),2,2));
  dummy.Append(gInclude->FormatedChar(" imp: ",8));
  dummy.Append(gInclude->FormatedDouble(this->GetImpactParameter(),2,7));
  dummy.Append(gInclude->FormatedChar(" imp 2D: ",11));
  dummy.Append(gInclude->FormatedDouble(this->Get2DImpactParameter(),2,7));
  dummy.Append(gInclude->FormatedChar(" beamspot imp 2D: ",20));
  dummy.Append(gInclude->FormatedDouble(this->Get2DBeamSpotImpactParameter(),2,7));
  dummy.Append(gInclude->FormatedChar(" beamspot imp sig 2D: ",24));
  dummy.Append(gInclude->FormatedDouble(this->Get2DBeamSpotImpactParameterSignificance(),2,7));
  if ( fMC != 0 ) {
    dummy.Append(gInclude->FormatedChar(" mc beamspot imp 2D: ",23));
    dummy.Append(gInclude->FormatedDouble(this->Get2DMCBeamSpotImpactParameter(),2,7));
    dummy.Append(gInclude->FormatedChar(" mc imp: ",11));
    dummy.Append(gInclude->FormatedDouble(fMC->GetImpact(),2,7));
    dummy.Append(gInclude->FormatedChar(" mc imp 2D: ",14));
    dummy.Append(gInclude->FormatedDouble(fMC->GetImpact2D(),2,7));
    dummy.Append(gInclude->FormatedChar(" true imp 2D: ",14));
    dummy.Append(gInclude->FormatedDouble(Get2DTrueImpactParameter(),2,7));
  }
  dummy.Append(gInclude->FormatedChar(" zufo: ",9));
  dummy.Append(gInclude->FormatedInt(fZufoID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" ztype: ",9));
  dummy.Append(gInclude->FormatedInt(fZufoType,5,0," "));
  dummy.Append(gInclude->FormatedChar(" jet: ",9));
  dummy.Append(gInclude->FormatedInt(fJetID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" jetpt: ",11));
  dummy.Append(gInclude->FormatedDouble(fJetPt,3,3));
  dummy.Append(gInclude->FormatedChar(" jetdr: ",11));
  dummy.Append(gInclude->FormatedDouble(fJetDr,3,3));
  dummy.Append(gInclude->FormatedChar(" etacut: ",11));
  dummy.Append(gInclude->FormatedBool(GetEtaCut()));
  dummy.Append(gInclude->FormatedChar(" qualcut: ",11));
  dummy.Append(gInclude->FormatedBool(GetQualityCut()));
  dummy.Append(gInclude->FormatedChar(" findcut: ",11));
  dummy.Append(gInclude->FormatedBool(GetFinderCut()));
  dummy.Append(gInclude->FormatedChar(" pcut: ",11));
  dummy.Append(gInclude->FormatedBool(GetPCut()));
  dummy.Append(gInclude->FormatedChar(" ptcut: ",11));
  dummy.Append(gInclude->FormatedBool(GetPtCut()));
  dummy.Append(gInclude->FormatedChar(" brematcut: ",11));
  dummy.Append(gInclude->FormatedBool(GetBrematCut()));
  dummy.Append(gInclude->FormatedChar(" mpmatchcut: ",11));
  dummy.Append(gInclude->FormatedBool(GetMPMatchCut()));
  dummy.Append(gInclude->FormatedChar(" forwardmuon: ",12));
  dummy.Append(gInclude->FormatedBool(GetForwardTrackMuonCut()));
  dummy.Append(gInclude->FormatedChar(" allcuts: ",11));
  dummy.Append(gInclude->FormatedBool(GetAllCuts()));

  if ( fMC != 0 ) {
    dummy.Append(gInclude->FormatedChar(" mc part: ",11));
    dummy.Append(gInclude->FormatedInt(fMC->GetFMCKINID(),3,0," "));
  }

  if ( fMCQuark != 0 ) {
    dummy.Append(gInclude->FormatedChar(" mc quark: ",12));
    dummy.Append(gInclude->FormatedInt(fMCQuark->GetFMCKINID(),3,0," "));
  }

  if ( fMCDirectParent != 0 ) {
    dummy.Append(gInclude->FormatedChar(" mc dir parent: ",17));
    dummy.Append(gInclude->FormatedInt(fMCDirectParent->GetFMCKINID(),3,0," "));
  }

  dummy.Append("\n");

return dummy;
}

//_____________________________________________________________

Bool_t GMuon::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMuon::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GMuon::CalcImpactParameter(Double_t new_x_ref, Double_t new_x_ref_sigma, 
				  Double_t new_y_ref, Double_t new_y_ref_sigma, 
				  Double_t new_z_ref, Double_t new_z_ref_sigma) {
  //
  // calc impact parameter from old helix parameters and new reference in x,y,z
  if ( gDebug ) cout << endl << "GMuon::CalcImpactParameter called" << endl << endl;

  if ( fZTTTrack != 0 ) {
    // take only valid tracks
    if ( fZTTTrack->GetAllCuts() ) {
      if ( fJetID != 0 ) {
	fZTTTrack->CalcImpactParameters(new_x_ref,new_x_ref_sigma,
					new_y_ref,new_y_ref_sigma,
					new_z_ref,new_z_ref_sigma,
					gJets->GetJetWithID(fJetID));
	fImpactParameter = fZTTTrack->GetImpactParameter();
	f2DImpactParameter = fZTTTrack->Get2DImpactParameter();
	fImpactParameterSignificance = fZTTTrack->GetImpactParameterSignificance();
	f2DImpactParameterSignificance = fZTTTrack->Get2DImpactParameterSignificance();
      }
    }
  }

  return kTRUE;
}


//_____________________________________________________________

Bool_t GMuon::CalcBeamSpotImpactParameter() {
  //
  // calc impact parameter from ztt helix parameter towards beamspot
  if (gDebug) cout << endl << "GMuon::CalcBeamSpotImpactParameter called" << endl << endl;

  if ( fZTTTrack != 0 ) {
    GBeamSpot *currentBeamSpot = gVertex->GetEventBeamSpot();
    //    GBeamSpot *currentBeamSpot = gVertex->GetCurrentBeamSpot();

    if ( currentBeamSpot != 0 ) {
      if ( fZTTTrack->GetAllCuts() ) {
	if ( fJetID != 0 ) {
	  fZTTTrack->CalcImpactParameters(currentBeamSpot->GetX_Mean(),currentBeamSpot->GetX_Sigma(),
					  currentBeamSpot->GetY_Mean(),currentBeamSpot->GetY_Sigma(),
					  currentBeamSpot->GetZ_Mean(),currentBeamSpot->GetZ_Sigma(),
					  gJets->GetJetWithID(fJetID));
	  f2DBeamSpotImpactParameter = fZTTTrack->Get2DImpactParameter();
	  f2DBeamSpotImpactParameterSignificance = fZTTTrack->Get2DImpactParameterSignificance();
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuon::CalcMCBeamSpotImpactParameter() {
  //
  // calc mc impact parameter towards MC nominal beamspot
  if ( gDebug ) cout << endl << "GMuon::CalcMCBeamSpotImpactParameter called" << endl << endl;

  GBeamSpot *currentBeamSpot = gVertex->GetCurrentBeamSpot();
  if ( currentBeamSpot != 0 ) {
    GMC *mc = GetMC();
    if ( mc != 0 ) {
      GMCVertex *mcvertex = mc->GetVertex();
      if ( mcvertex != 0 ) {
	TVector2 diff2D = currentBeamSpot->XYvector() - mcvertex->XYvector();
	Double_t cosalpha2D = ( diff2D * mc->Vect().XYvector() )/diff2D.Mod()/mc->Vect().XYvector().Mod();
	f2DMCBeamSpotImpactParameter = diff2D.Mod() * TMath::Sin(TMath::ACos(cosalpha2D));
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMuon::CalcTrueImpactParameter() {
  //
  // calc impact parameter from ztt helix parameter towards MC true vertex
  if ( gDebug ) cout << endl << "GMuon::CalcTrueImpactParameter called" << endl << endl;

  if ( fZTTTrack != 0 ) {
    // mc true vertex with id 1 is primary vertex
    GMCVertex *mcvertex = gMCs->GetMCVertex(1);
    if ( (mcvertex != 0) && fMCQuark ) {
      if ( fJetID != 0 ) {
	fZTTTrack->CalcImpactParameters(mcvertex->X(),0,
					mcvertex->Y(),0,
					mcvertex->Z(),0,
					gJets->GetJetWithID(fJetID));
	f2DTrueImpactParameter = fZTTTrack->Get2DImpactParameter();
	f2DTrueImpactParameterSignificance = fZTTTrack->Get2DImpactParameterSignificance();
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Double_t GMuon::GetWeight() {
  //
  // return weight, if weight is larger than cutoff value from cards, return cutoff value
  if ( gDebug ) cout << endl << "GMuon::GetWeight called" << endl << endl;
  
  if ( fWeight > gCards->GetMUONEfficiencyCutOff() ) {
    return gCards->GetMUONEfficiencyCutOff();
  }
  return fWeight;
}
//_____________________________________________________________

Bool_t GMuon::AssociateJetByDeltaR() {
  //
  // give back jetid with smallest deltaR
  if ( gDebug ) cout << endl << "GMuon::AssociateJet called" << endl << endl;

  fJetDr = 10;
  for ( Int_t j = 0; j < gJets->GetNJets(); j++ ) {
    GJet *jet = gJets->GetJet(j);
    if ( jet != 0 ) {
      if( this->Vect().DeltaR(jet->Vect())< fJetDr){
	fJetID = jet->GetID();  
	fJetDr = this->Vect().DeltaR(jet->Vect());
	fJetPt = this->Pt(jet->Vect());
      }
    }
  }
  return kTRUE;
}
