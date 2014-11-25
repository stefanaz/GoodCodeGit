//
// GTriMuons.cxx
//
// $Author: dbot $
// $Date: 2010/06/10 08:08:00 $
// $Revision: 1.00 $
//

#include <GTriMuons.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTriMuons)
#endif

  GTriMuons *gTriMuons = 0;

//_____________________________________________________________
// GTriMuons
// Trimuon Class for everything which is related only to Trimuons
//
//
GTriMuons::GTriMuons() : GPhysObj() {
  //
  // GTriMuons default constructor
  if ( gDebug ) cout << endl << "GTriMuons::GTriMuons ctor called" << endl << endl;

  // initialize global pointer
  gTriMuons = this;

  // init variables
  InitVariables();

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GTriMuons::GTriMuons(Int_t dummy) : GPhysObj() {
  //
  // GTriMuons standalone constructor
  if ( gDebug ) cout << endl << "GTriMuons::GTriMuons standalone constructor called" << endl << endl;

  // initialize global pointer
  gTriMuons = this;

  // init variables
  InitVariables();

}

//_____________________________________________________________

GTriMuons::~GTriMuons() {
  //
  // GTriMuons default destructor
  if ( gDebug ) cout << endl << "GTriMuons::~GTriMuons dtor called" << endl << endl;

  fTriMuons->Delete();
  delete fTriMuons;

}

//_____________________________________________________________

Bool_t GTriMuons::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GTriMuons::Do() called" << endl << endl;

  Fill();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GTriMuons::Reset() called" << endl << endl;

  // reset cut flags
  fInvMassCut         = kFALSE;
  fSqSumIsolationCut  = kFALSE;
  fDeltaRCut          = kFALSE;
  fDeltaPhiCut        = kFALSE;
  fDeltaThetaCut      = kFALSE;
  fDeltaEtaCut        = kFALSE;
  fPtAsymetryCut      = kFALSE;
  fEtFractionHighCut  = kFALSE;
  fEtFractionLowCut   = kFALSE;
  fDifChargeCut       = kFALSE;
  fCharmMCJpsiCut     = kFALSE;
  fCharmMCPsiprimeCut = kFALSE;
  fAllCuts            = kFALSE;

  fDoCalcIsolation   = kFALSE;

  fSelectedIndex = -99;

  // reset clonesarray
  fTriMuons  -> Clear();
  fNTriMuons =  0;

  // reset variables
  fNGoodTriMuons   = 0;
  fNChosenTriMuons = 0;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::Fill() {
  //
  // fill clonesarray
  if ( gDebug ) cout << endl << "GTriMuons::Fill() called" << endl << endl;

  if ( gCards->GetTRIMUONNTrimuons() > 0 ) {

    TClonesArray &trimuons = *fTriMuons;

    for ( Int_t i = 0; i < gMuons->GetNMuons(); ++i ) {
      for ( Int_t j = i+1; j < gMuons->GetNMuons(); ++j ) {
	for ( Int_t k = j+1; k < gMuons->GetNMuons(); ++k ) {
	  GMuon *muon1 = gMuons->GetMuon(i);
	  GMuon *muon2 = gMuons->GetMuon(j);
	  GMuon *muon3 = gMuons->GetMuon(k);
	  GTriMuon *trimuon = new(trimuons[fNTriMuons++]) GTriMuon(muon1,muon2,muon3);
	// Need to reset the isolation cut, as the global reset is called eventwise only.
	  trimuon->SetSqSumIsolationCut(kFALSE);
	  CheckMuonsAllCut(trimuon);
	  if( gCards->GetDoEfficiency() ) {
	  // reset match flag for correctly filling of muon histograms, temp. solution
	    muon1->SetMatched(kFALSE);
	    muon2->SetMatched(kFALSE);
	    muon3->SetMatched(kFALSE);
	    CheckMuonsMVCut(trimuon);
	    CheckTrigger(trimuon);
	  }
	  CheckInvMassCut(trimuon);
	  CheckDeltaRCut(trimuon);
	  CheckDeltaPhiCut(trimuon);
	  CheckDeltaThetaCut(trimuon);
	  CheckDeltaEtaCut(trimuon);
	  CheckPtAsymetryCut(trimuon);
	  CheckEtFractionHighCut(trimuon);
	  CheckEtFractionLowCut(trimuon);
	  CheckDifChargeCut(trimuon);
	  CheckCharmMCJpsiCut(trimuon); // wenn hier gut dann:
	  CheckCharmMCPsiprimeCut(trimuon);

	  if( CheckAllCuts(trimuon, 1) && fDoCalcIsolation ) {

	    gZufo->CalcIsolation(trimuon);
	    CheckSqSumIsolationCut(trimuon);
	    gZufo->CalcThrust();
	    //	    gZufo->CalcInstantonVariables();

	  }

	  CheckAllCuts(trimuon);
	  CheckBestTriMuon(trimuon,fNTriMuons-1);

	}
      }
    }
    // flag trimuon fulfilling all cuts with highest ptrel
    if ( fSelectedIndex != -99 )
      DetSelectedCand(fSelectedIndex);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckMuonsAllCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills all muon cuts
  if ( gDebug ) cout << endl << "GTriMuons::CheckMuonsAllCut called" << endl << endl;

  if ( trimuon->GetMuon1()->GetAllCuts() && trimuon->GetMuon2()->GetAllCuts() && trimuon->GetMuon3()->GetAllCuts()) {
    trimuon->SetMuonsAllCuts(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckMuonsMVCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills MV muon cuts
  if ( gDebug ) cout << endl << "GTriMuons::CheckMuonsMVCut called" << endl << endl;

  if ( trimuon->GetMuon1()->GetMVCuts() && trimuon->GetMuon2()->GetMVCuts() && trimuon->GetMuon3()->GetMVCuts()) {
    trimuon->SetMuonsMVCuts(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckInvMassCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills invarant mass cuts
  if ( gDebug ) cout << endl << "GTriMuons::CheckInvMassCut called" << endl << endl;

  if ( ((trimuon->GetInvMass1() >= gCards->GetTRIMUONInvMassLowCut()) && (trimuon->GetInvMass1() <= gCards->GetTRIMUONInvMassHighCut())) && ((trimuon->GetInvMass2() >= gCards->GetTRIMUONInvMassLowCut()) && (trimuon->GetInvMass2() <= gCards->GetTRIMUONInvMassHighCut())) && ((trimuon->GetInvMass3() >= gCards->GetTRIMUONInvMassLowCut()) && (trimuon->GetInvMass3() <= gCards->GetTRIMUONInvMassHighCut())) ) {
    trimuon->SetInvMassCut(kTRUE);
    fInvMassCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckSqSumIsolationCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills requirement to be called *NON*-isolated (sorry!!)
  if ( gDebug ) cout << endl << "GTriMuons::CheckSqSumIsolationCut called" << endl << endl;

  if( (trimuon->GetInvMass1() >= 2.9 && trimuon->GetInvMass1() <=3.25 ) || (trimuon->GetInvMass1() >= 3.6 && trimuon->GetInvMass1() <= 3.75 ) || (trimuon->GetInvMass2() >= 2.9 && trimuon->GetInvMass2() <=3.25 ) || (trimuon->GetInvMass2() >= 3.6 && trimuon->GetInvMass2() <= 3.75 ) || (trimuon->GetInvMass3() >= 2.9 && trimuon->GetInvMass3() <=3.25 ) || (trimuon->GetInvMass3() >= 3.6 && trimuon->GetInvMass3() <= 3.75 ) ){
    if ( trimuon->GetIsolationSqSum10() >= gCards->GetTRIMUONSqSumIsolationPeakCut() ) {

      trimuon->SetSqSumIsolationCut(kTRUE);
     
    }
  }
  else{
    if ( trimuon->GetIsolationSqSum10() >= gCards->GetTRIMUONSqSumIsolationContCut() ) {
   
      trimuon->SetSqSumIsolationCut(kTRUE);
   
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckDeltaRCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills delta r cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckDeltaRCut called" << endl << endl;

  if ( (trimuon->GetDeltaR1() >= gCards->GetTRIMUONDeltaRCut()) ||(trimuon->GetDeltaR2() >= gCards->GetTRIMUONDeltaRCut())||(trimuon->GetDeltaR3() >= gCards->GetTRIMUONDeltaRCut()) ) {
    trimuon->SetDeltaRCut(kTRUE);
    fDeltaRCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckDeltaPhiCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills delta phi
  if ( gDebug ) cout << endl << "GTriMuons::CheckDeltaPhiCut called" << endl << endl;

  if ( (TMath::Abs( TMath::Abs(trimuon->GetDeltaPhi1())-TMath::Pi() ) > gCards->GetTRIMUONDeltaPhiCut())&&(TMath::Abs( TMath::Abs(trimuon->GetDeltaPhi2())-TMath::Pi() ) > gCards->GetTRIMUONDeltaPhiCut())&&(TMath::Abs( TMath::Abs(trimuon->GetDeltaPhi3())-TMath::Pi() ) > gCards->GetTRIMUONDeltaPhiCut())) {
    trimuon->SetDeltaPhiCut(kTRUE);
    fDeltaPhiCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckDeltaThetaCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills delta theta cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckDeltaThetaCut called" << endl << endl;

  // orig. IB:  delta_theta_mus[0] = TMath::Abs( theta_mu[0] - (TMath::Pi() - theta_mu[1]) );
  //           if ( delta_theta_mus > 5.*TMath::Pi()/1000. && ... ) ...

  if (( TMath::Abs(trimuon->GetMuon1()->Theta()-(TMath::Pi()-trimuon->GetMuon2()->Theta())) > gCards->GetTRIMUONDeltaThetaCut())&&( TMath::Abs(trimuon->GetMuon1()->Theta()-(TMath::Pi()-trimuon->GetMuon3()->Theta())) > gCards->GetTRIMUONDeltaThetaCut()) &&( TMath::Abs(trimuon->GetMuon2()->Theta()-(TMath::Pi()-trimuon->GetMuon3()->Theta())) > gCards->GetTRIMUONDeltaThetaCut()) ){
    trimuon->SetDeltaThetaCut(kTRUE);
    fDeltaThetaCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckDeltaEtaCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills delta eta cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckDeltaEtaCut called" << endl << endl;

  if ( (TMath::Abs( trimuon->GetMuon1()->Eta() - trimuon->GetMuon2()->Eta() ) < gCards->GetTRIMUONDeltaEtaCut())&&(TMath::Abs( trimuon->GetMuon1()->Eta() - trimuon->GetMuon3()->Eta() ) < gCards->GetTRIMUONDeltaEtaCut())&&(TMath::Abs( trimuon->GetMuon2()->Eta() - trimuon->GetMuon3()->Eta() ) < gCards->GetTRIMUONDeltaEtaCut()) ) {
    trimuon->SetDeltaEtaCut(kTRUE);
    fDeltaEtaCut = kTRUE;
  }

  return kTRUE;
}
//_____________________________________________________________

Bool_t GTriMuons::CheckPtAsymetryCut(GTriMuon *trimuon) {
  //
  // check if trimuon fulfills pt asymetry cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckPtAsymetryCut called" << endl << endl;

  // orig. IB:  sqrt(TMath::Power(((mupt[iii]-mupt[jjj])/(mupt[iii]+mupt[jjj])),2)) <= 0.7 // new 031113, estimated crudely from data/MC comparison

  if ( (trimuon->GetPtAsymetry1() <= gCards->GetTRIMUONPtAsymetryCut())&&(trimuon->GetPtAsymetry2() <= gCards->GetTRIMUONPtAsymetryCut()) &&(trimuon->GetPtAsymetry3() <= gCards->GetTRIMUONPtAsymetryCut()) ) {
    trimuon->SetPtAsymetryCut(kTRUE);
    fPtAsymetryCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckEtFractionHighCut(GTriMuon *trimuon) {
  //
  // check if trimuon fulfills upper trimumass dependent et fraction cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckEtFractionHighCut called" << endl << endl;

  if( trimuon->GetInvMass1() > 4 && trimuon->GetInvMass2() > 4 && trimuon->GetInvMass3() > 4 ){
    if ((trimuon->GetEtFraction1() <= gCards->GetTRIMUONEtFractionHigh1Cut())&&(trimuon->GetEtFraction2() <= gCards->GetTRIMUONEtFractionHigh1Cut())&&(trimuon->GetEtFraction3() <= gCards->GetTRIMUONEtFractionHigh1Cut())) {
      trimuon->SetEtFractionHighCut(kTRUE);
      fEtFractionHighCut = kTRUE;
    }
  }
  else{
    if ((trimuon->GetEtFraction1() <= gCards->GetTRIMUONEtFractionHigh2Cut())&&(trimuon->GetEtFraction2() <= gCards->GetTRIMUONEtFractionHigh2Cut()) &&(trimuon->GetEtFraction3() <= gCards->GetTRIMUONEtFractionHigh2Cut()) ) {
      trimuon->SetEtFractionHighCut(kTRUE);
      fEtFractionHighCut = kTRUE;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckEtFractionLowCut(GTriMuon *trimuon) {
  //
  // check if trimuon fulfills lower et fraction cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckEtFractionLowCut called" << endl << endl;

  if ((trimuon->GetEtFraction1() >= gCards->GetTRIMUONEtFractionLowCut())&&(trimuon->GetEtFraction2() >= gCards->GetTRIMUONEtFractionLowCut()) &&(trimuon->GetEtFraction3() >= gCards->GetTRIMUONEtFractionLowCut()) ) {
    trimuon->SetEtFractionLowCut(kTRUE);
    fEtFractionLowCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckDifChargeCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills different charge cut
  if ( gDebug ) cout << endl << "GTriMuons::CheckDifChargeCut called" << endl << endl;

  if ( gCards->GetTRIMUONDifCharge() ) {
    if ( trimuon->GetDifCharge() ) {
      trimuon->SetDifChargeCut(kTRUE);
      fDifChargeCut = kTRUE;
    }
  } else {
    trimuon->SetDifChargeCut(kTRUE);
    fDifChargeCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckCharmMCJpsiCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills CheckCharmMCJpsiCut (i.e. reject Jpsis in Charm MC)
  if ( gDebug ) cout << endl << "GTriMuons::CheckVetoCharmMCJpsiCut called" << endl << endl;

  if ( gCards->GetMCCCBAR() && gCards->GetTRIMUONCharmMCJpsi() ) { 
    if(trimuon->GetMuon1()->GetMCDirectParent()) {
      if(trimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Jpsi") {
  	fCharmMCJpsiCut = kTRUE;
  	trimuon->SetCharmMCJpsiCut(kTRUE);
      }
    }
    if(trimuon->GetMuon2()->GetMCDirectParent()) {
      if(trimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Jpsi") {
  	fCharmMCJpsiCut = kTRUE;
  	trimuon->SetCharmMCJpsiCut(kTRUE);
      }
    }
    if(trimuon->GetMuon3()->GetMCDirectParent()) {
      if(trimuon->GetMuon3()->GetMCDirectParent()->ReturnParticleType() == "Jpsi") {
  	fCharmMCJpsiCut = kTRUE;
  	trimuon->SetCharmMCJpsiCut(kTRUE);
      }
    }
  }


  //  trimuon->SetCharmMCJpsiCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckCharmMCPsiprimeCut(GTriMuon *trimuon) {
  //
  // check trimuon if muon fulfills CheckCharmMCPsiprimeCut (i.e. reject Psiprimes in Charm MC)
  if ( gDebug ) cout << endl << "GTriMuons::CheckVetoCharmMCPsiprimeCut called" << endl << endl;

  if ( gCards->GetMCCCBAR() && gCards->GetTRIMUONCharmMCPsiprime() ) { 
    if(trimuon->GetMuon1()->GetMCDirectParent()) {
      if(trimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Psiprime") {
  	fCharmMCPsiprimeCut = kTRUE;
  	trimuon->SetCharmMCPsiprimeCut(kTRUE);
      }
    }
    if(trimuon->GetMuon2()->GetMCDirectParent()) {
      if(trimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Psiprime") {
  	fCharmMCPsiprimeCut = kTRUE;
  	trimuon->SetCharmMCPsiprimeCut(kTRUE);
      }
    }
    if(trimuon->GetMuon3()->GetMCDirectParent()) {
      if(trimuon->GetMuon3()->GetMCDirectParent()->ReturnParticleType() == "Psiprime") {
  	fCharmMCPsiprimeCut = kTRUE;
  	trimuon->SetCharmMCPsiprimeCut(kTRUE);
      }
    }
  }


  //  trimuon->SetCharmMCPsiprimeCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckTrigger(GTriMuon *trimuon) {
  //
  // check trimuon whether to take both muons, only one muon or none muon for histogram filling (trigger bias)
  if ( gDebug ) cout << endl << "GTriMuons::CheckTrigger called" << endl << endl;

  // distinguish between upgrade and pre-upgrade
  if ( (gGeneral->GetRunPeriod() == k02p) ||
       (gGeneral->GetRunPeriod() == k03p) ||
       (gGeneral->GetRunPeriod() == k04p) ||
       (gGeneral->GetRunPeriod() == k03p04p) ) {
    // check if event triggers any of the HPP, DIS and SPP TLT triggers, then take both
    // mark muon as matched (flag from GMJMatchs, to fill general muon histograms in GMuons (depends on match-flag)
    if ( gTrigger->EventTriggeredByTLTSPP() || gTrigger->EventTriggeredByTLTHPP() || gTrigger->EventTriggeredByTLTDIS() ) {
      trimuon->SetTriggerType(kTakeAll);
      trimuon->GetMuon1()->SetMatched(kTRUE);
      trimuon->GetMuon2()->SetMatched(kTRUE);
      trimuon->GetMuon3()->SetMatched(kTRUE);
    } else {
      // check if event triggers tlt hfl  1-12,18-22,24 then take both
      // all dis except 27, then take both
      // all exo except 8,9,10,11,12, then take both
      if ( gTrigger->EventTriggeredByTLTHFL(1)  ||
	   gTrigger->EventTriggeredByTLTHFL(2)  ||
	   gTrigger->EventTriggeredByTLTHFL(3)  ||
	   gTrigger->EventTriggeredByTLTHFL(4)  ||
	   gTrigger->EventTriggeredByTLTHFL(5)  ||
	   gTrigger->EventTriggeredByTLTHFL(6)  ||
	   gTrigger->EventTriggeredByTLTHFL(7)  ||
	   gTrigger->EventTriggeredByTLTHFL(8)  ||
	   gTrigger->EventTriggeredByTLTHFL(9)  ||
	   gTrigger->EventTriggeredByTLTHFL(10) ||
	   gTrigger->EventTriggeredByTLTHFL(11) ||
	   gTrigger->EventTriggeredByTLTHFL(12) ||
	   gTrigger->EventTriggeredByTLTHFL(16) ||
	   gTrigger->EventTriggeredByTLTHFL(18) ||
	   gTrigger->EventTriggeredByTLTHFL(19) ||
	   gTrigger->EventTriggeredByTLTHFL(20) ||
	   gTrigger->EventTriggeredByTLTHFL(21) ||
	   gTrigger->EventTriggeredByTLTHFL(22) ||
	   gTrigger->EventTriggeredByTLTHFL(24) ||
	   gTrigger->EventTriggeredByTLTEXO(1)  ||
	   gTrigger->EventTriggeredByTLTEXO(2)  ||
	   gTrigger->EventTriggeredByTLTEXO(3)  ||
	   gTrigger->EventTriggeredByTLTEXO(4)  ||
	   gTrigger->EventTriggeredByTLTEXO(5)  ||
	   gTrigger->EventTriggeredByTLTEXO(6)  ||
	   gTrigger->EventTriggeredByTLTEXO(7)  ||
	   gTrigger->EventTriggeredByTLTEXO(13) ||
	   gTrigger->EventTriggeredByTLTEXO(14) ||
	   gTrigger->EventTriggeredByTLTEXO(15) ||
	   gTrigger->EventTriggeredByTLTEXO(16) ||
	   gTrigger->EventTriggeredByTLTEXO(17) ||
	   gTrigger->EventTriggeredByTLTEXO(18) ||
	   gTrigger->EventTriggeredByTLTEXO(19) ||
	   gTrigger->EventTriggeredByTLTEXO(20) ||
	   gTrigger->EventTriggeredByTLTEXO(21) ||
	   gTrigger->EventTriggeredByTLTEXO(22) ||
	   gTrigger->EventTriggeredByTLTEXO(23) ||
	   gTrigger->EventTriggeredByTLTEXO(24) ||
	   gTrigger->EventTriggeredByTLTEXO(25) ||
	   gTrigger->EventTriggeredByTLTEXO(26) ||
	   gTrigger->EventTriggeredByTLTEXO(27) ||
	   gTrigger->EventTriggeredByTLTEXO(28) ||
	   gTrigger->EventTriggeredByTLTEXO(29) ||
	   gTrigger->EventTriggeredByTLTEXO(30) ||
	   gTrigger->EventTriggeredByTLTEXO(31) ||
	   gTrigger->EventTriggeredByTLTEXO(32) ) {
	trimuon->SetTriggerType(kTakeAll);
	trimuon->GetMuon1()->SetMatched(kTRUE);
	trimuon->GetMuon2()->SetMatched(kTRUE);
	trimuon->GetMuon3()->SetMatched(kTRUE);

      } else {
	// glomu behandlung fuer exo 11,12, muo 3, hfl 13-16.23.25-30,32
	// glomu behandlung: take muon from trimuon which is not found by glomu, if none is found by glomu, take none, if both are found by glomu, take both
	if ( gTrigger->EventTriggeredByTLTEXO(11) ||
	     gTrigger->EventTriggeredByTLTEXO(12) ||
	     gTrigger->EventTriggeredByTLTHFL(13) ||
	     gTrigger->EventTriggeredByTLTHFL(14) ||
	     gTrigger->EventTriggeredByTLTHFL(15) ||
	     gTrigger->EventTriggeredByTLTHFL(23) ||
	     gTrigger->EventTriggeredByTLTHFL(25) ||
	     gTrigger->EventTriggeredByTLTHFL(26) ||
	     gTrigger->EventTriggeredByTLTHFL(27) ||
	     gTrigger->EventTriggeredByTLTHFL(28) ||
	     gTrigger->EventTriggeredByTLTHFL(29) ||
	     gTrigger->EventTriggeredByTLTHFL(32) ) {
	  GMuon *muon1 = trimuon->GetMuon1();
	  GMuon *muon2 = trimuon->GetMuon2();
	  GMuon *muon3 = trimuon->GetMuon3();
	  if ( muon1->GetGlomu() && !muon2->GetGlomu() && muon3->GetGlomu() ) {
	    trimuon->SetTriggerType(kTakeTriMuon2);
	    trimuon->GetMuon2()->SetMatched(kTRUE);
	  } else if ( !muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu()) {
	    trimuon->SetTriggerType(kTakeTriMuon1);
	    trimuon->GetMuon1()->SetMatched(kTRUE);
	  } else if (  muon1->GetGlomu() && muon2->GetGlomu() && !muon3->GetGlomu()){
	    trimuon->SetTriggerType(kTakeTriMuon3);
	    trimuon->GetMuon3()->SetMatched(kTRUE);
	  } else if ( muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu()) {
	    trimuon->SetTriggerType(kTakeAll);
	    trimuon->GetMuon1()->SetMatched(kTRUE);
	    trimuon->GetMuon2()->SetMatched(kTRUE);
	    trimuon->GetMuon3()->SetMatched(kTRUE);
	  } 


	} else if (
		   gTrigger->EventTriggeredByTLTMUO(3)  ||
		   gTrigger->EventTriggeredByTLTMUO(4)  || 
		   gTrigger->EventTriggeredByTLTHFL(30) ||
		   gTrigger->EventTriggeredByTLTHFL(31) ) {
	  // special treatment for muo triggers
	  // muo3: glomu (post--upgrade: also HFL30)
	  // muo4: mamma (post--upgrade: also HFL31)
	  //
	  // muo4 and HFL31 triggers on forward muons using mamma
	  // mamma taken out for OLI's muon selection, so set to take both
	  // Attention for others!!!
	  // distinguish forward and barrel/rear muons
	  // if both forward, take both
	  // if one forward, take the forward, check the barrel/rear for glomu, if not glomu, take also barrel/rear
	  // if both barrel, check for glomu
	  GMuon *muon1 = trimuon->GetMuon1();
	  GMuon *muon2 = trimuon->GetMuon2();
	  GMuon *muon3 = trimuon->GetMuon3();
	  if ( (muon1->GetType() == kForward) && (muon2->GetType() == kForward) && (muon3->GetType() == kForward) ) {
	    trimuon->SetTriggerType(kTakeAll);
	    trimuon->GetMuon1()->SetMatched(kTRUE);
	    trimuon->GetMuon2()->SetMatched(kTRUE);
	    trimuon->GetMuon3()->SetMatched(kTRUE);
	  } else if ( muon1->GetType() == kForward ) {
	    if ( muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon1);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	    } else {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    }
	  } else if ( muon2->GetType() == kForward ) {
	    if ( muon1->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon2);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	    } else {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    }
	  } else if ( muon3->GetType() == kForward ) {
	    if ( muon1->GetGlomu() && muon2->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon3);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    } else {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    }
	  } else {
	    if ( muon1->GetGlomu() && !muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon2);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	    } else if ( !muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon1);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	    } else if ( muon1->GetGlomu() && muon2->GetGlomu() && !muon3->GetGlomu() ){
	      trimuon->SetTriggerType(kTakeTriMuon3);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    } else if ( muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    } 
	  }
	} else if ( gTrigger->EventTriggeredByTLTVTX() ) {
	  // for MC, if event is only triggered by vtxm take both
	  trimuon->SetTriggerType(kTakeAll);
	  trimuon->GetMuon1()->SetMatched(kTRUE);
	  trimuon->GetMuon2()->SetMatched(kTRUE);
	  trimuon->GetMuon3()->SetMatched(kTRUE);
	}
      }
    }
  } else {
    // check if event triggers any of the HPP and SPP TLT triggers, then take both
    // mark muon as matched (flag from GMJMatchs, to fill general muon histograms in GMuons (depends on match-flag)
    if ( gTrigger->EventTriggeredByTLTSPP() || gTrigger->EventTriggeredByTLTHPP() ) {
      trimuon->SetTriggerType(kTakeAll);
      trimuon->GetMuon1()->SetMatched(kTRUE);
      trimuon->GetMuon2()->SetMatched(kTRUE);
      trimuon->GetMuon3()->SetMatched(kTRUE);
    } else {
      // check if event triggers tlt hfl 3,4,5,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24, then take both
      // all dis except 27, then take both
      // all exo except 8,9,10,11,12, then take both
      if ( gTrigger->EventTriggeredByTLTHFL(3)  ||
	   gTrigger->EventTriggeredByTLTHFL(4)  ||
	   gTrigger->EventTriggeredByTLTHFL(5)  ||
	   gTrigger->EventTriggeredByTLTHFL(10) ||
	   gTrigger->EventTriggeredByTLTHFL(11) ||
	   gTrigger->EventTriggeredByTLTHFL(12) ||
	   gTrigger->EventTriggeredByTLTHFL(13) ||
	   gTrigger->EventTriggeredByTLTHFL(14) ||
	   gTrigger->EventTriggeredByTLTHFL(15) ||
	   gTrigger->EventTriggeredByTLTHFL(16) ||
	   gTrigger->EventTriggeredByTLTHFL(17) ||
	   gTrigger->EventTriggeredByTLTHFL(18) ||
	   gTrigger->EventTriggeredByTLTHFL(19) ||
	   gTrigger->EventTriggeredByTLTHFL(20) ||
	   gTrigger->EventTriggeredByTLTHFL(21) ||
	   gTrigger->EventTriggeredByTLTHFL(22) ||
	   gTrigger->EventTriggeredByTLTHFL(23) ||
	   gTrigger->EventTriggeredByTLTHFL(24) ||
	   gTrigger->EventTriggeredByTLTDIS(1)  ||
	   gTrigger->EventTriggeredByTLTDIS(2)  ||
	   gTrigger->EventTriggeredByTLTDIS(3)  ||
	   gTrigger->EventTriggeredByTLTDIS(4)  ||
	   gTrigger->EventTriggeredByTLTDIS(5)  ||
	   gTrigger->EventTriggeredByTLTDIS(6)  ||
	   gTrigger->EventTriggeredByTLTDIS(7)  ||
	   gTrigger->EventTriggeredByTLTDIS(8)  ||
	   gTrigger->EventTriggeredByTLTDIS(9)  ||
	   gTrigger->EventTriggeredByTLTDIS(10) ||
	   gTrigger->EventTriggeredByTLTDIS(11) ||
	   gTrigger->EventTriggeredByTLTDIS(12) ||
	   gTrigger->EventTriggeredByTLTDIS(13) ||
	   gTrigger->EventTriggeredByTLTDIS(14) ||
	   gTrigger->EventTriggeredByTLTDIS(15) ||
	   gTrigger->EventTriggeredByTLTDIS(16) ||
	   gTrigger->EventTriggeredByTLTDIS(17) ||
	   gTrigger->EventTriggeredByTLTDIS(18) ||
	   gTrigger->EventTriggeredByTLTDIS(19) ||
	   gTrigger->EventTriggeredByTLTDIS(20) ||
	   gTrigger->EventTriggeredByTLTDIS(21) ||
	   gTrigger->EventTriggeredByTLTDIS(22) ||
	   gTrigger->EventTriggeredByTLTDIS(23) ||
	   gTrigger->EventTriggeredByTLTDIS(24) ||
	   gTrigger->EventTriggeredByTLTDIS(25) ||
	   gTrigger->EventTriggeredByTLTDIS(26) ||
	   gTrigger->EventTriggeredByTLTDIS(28) ||
	   gTrigger->EventTriggeredByTLTDIS(29) ||
	   gTrigger->EventTriggeredByTLTDIS(30) ||
	   gTrigger->EventTriggeredByTLTDIS(31) ||
	   gTrigger->EventTriggeredByTLTDIS(32) ||
	   gTrigger->EventTriggeredByTLTEXO(1)  ||
	   gTrigger->EventTriggeredByTLTEXO(2)  ||
	   gTrigger->EventTriggeredByTLTEXO(3)  ||
	   gTrigger->EventTriggeredByTLTEXO(4)  ||
	   gTrigger->EventTriggeredByTLTEXO(5)  ||
	   gTrigger->EventTriggeredByTLTEXO(6)  ||
	   gTrigger->EventTriggeredByTLTEXO(7)  ||
	   gTrigger->EventTriggeredByTLTEXO(13) ||
	   gTrigger->EventTriggeredByTLTEXO(14) ||
	   gTrigger->EventTriggeredByTLTEXO(15) ||
	   gTrigger->EventTriggeredByTLTEXO(16) ||
	   gTrigger->EventTriggeredByTLTEXO(17) ||
	   gTrigger->EventTriggeredByTLTEXO(18) ||
	   gTrigger->EventTriggeredByTLTEXO(19) ||
	   gTrigger->EventTriggeredByTLTEXO(20) ||
	   gTrigger->EventTriggeredByTLTEXO(21) ||
	   gTrigger->EventTriggeredByTLTEXO(22) ||
	   gTrigger->EventTriggeredByTLTEXO(23) ||
	   gTrigger->EventTriggeredByTLTEXO(24) ||
	   gTrigger->EventTriggeredByTLTEXO(25) ||
	   gTrigger->EventTriggeredByTLTEXO(26) ||
	   gTrigger->EventTriggeredByTLTEXO(27) ||
	   gTrigger->EventTriggeredByTLTEXO(28) ||
	   gTrigger->EventTriggeredByTLTEXO(29) ||
	   gTrigger->EventTriggeredByTLTEXO(30) ||
	   gTrigger->EventTriggeredByTLTEXO(31) ||
	   gTrigger->EventTriggeredByTLTEXO(32) ) {
	trimuon->SetTriggerType(kTakeAll);
	trimuon->GetMuon1()->SetMatched(kTRUE);
	trimuon->GetMuon2()->SetMatched(kTRUE);
	trimuon->GetMuon3()->SetMatched(kTRUE);
      } else {
	// glomu behandlung fuer exo 11,12, muo 3, hfl 1, dis 27
	// glomu behandlung: take muon from trimuon which is not found by glomu, if none is found by glomu, take none, if both are found by glomu, take both
	if ( gTrigger->EventTriggeredByTLTEXO(11) ||
	     gTrigger->EventTriggeredByTLTEXO(12) ||
	     gTrigger->EventTriggeredByTLTHFL(1) ||
	     gTrigger->EventTriggeredByTLTDIS(27) ) {
	  GMuon *muon1 = trimuon->GetMuon1();
	  GMuon *muon2 = trimuon->GetMuon2();
	  GMuon *muon3 = trimuon->GetMuon3();
	  if ( muon1->GetGlomu() && !muon2->GetGlomu() && muon3->GetGlomu() ) {
	    trimuon->SetTriggerType(kTakeTriMuon2);
	    trimuon->GetMuon2()->SetMatched(kTRUE);
	  } else if ( !muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu() ) {
	    trimuon->SetTriggerType(kTakeTriMuon1);
	    trimuon->GetMuon1()->SetMatched(kTRUE);
	  } else if ( muon1->GetGlomu() && muon2->GetGlomu() && !muon3->GetGlomu() ) {
	    trimuon->SetTriggerType(kTakeTriMuon3);
	    trimuon->GetMuon3()->SetMatched(kTRUE);
	  } else if ( muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu()) {
	    trimuon->SetTriggerType(kTakeAll);
	    trimuon->GetMuon1()->SetMatched(kTRUE);
	    trimuon->GetMuon2()->SetMatched(kTRUE);
	    trimuon->GetMuon3()->SetMatched(kTRUE);
	  }
	} else if ( gTrigger->EventTriggeredByTLTMUO(3)  ||
		    gTrigger->EventTriggeredByTLTMUO(4) ) {
	  // special treatment for muo triggers
	  // muo3: glomu (post--upgrade: also HFL30)
	  // muo4: mamma (post--upgrade: also HFL31)
	  //
	  // muo4 and HFL31 triggers on forward muons using mamma
	  // mamma taken out for OLI's muon selection, so set to take both
	  // Attention for others!!!
	  // distinguish forward and barrel/rear muons
	  // if both forward, take both
	  // if one forward, take the forward, check the barrel/rear for glomu, if not glomu, take also barrel/rear
	  // if both barrel, check for glomu
	  GMuon *muon1 = trimuon->GetMuon1();
	  GMuon *muon2 = trimuon->GetMuon2();
	  GMuon *muon3 = trimuon->GetMuon3();
	  if ( (muon1->GetType() == kForward) && (muon2->GetType() == kForward) && (muon3->GetType() == kForward) ) {
	    trimuon->SetTriggerType(kTakeAll);
	    trimuon->GetMuon1()->SetMatched(kTRUE);
	    trimuon->GetMuon2()->SetMatched(kTRUE);
	    trimuon->GetMuon3()->SetMatched(kTRUE);
	  } else if ( muon1->GetType() == kForward ) {
	    if ( muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon1);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	    } else {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    }
	  } else if ( muon2->GetType() == kForward ) {
	    if ( muon1->GetGlomu() && muon3->GetGlomu()) {
	      trimuon->SetTriggerType(kTakeTriMuon2);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	    } else {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    }
	  } else if ( muon3->GetType() == kForward ) {
	    if ( muon1->GetGlomu() && muon2->GetGlomu()) {
	      trimuon->SetTriggerType(kTakeTriMuon3);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    } else {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    }
	  } else {
	    if ( muon1->GetGlomu() && !muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon2);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	    } else if ( !muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon1);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	    } else if ( muon1->GetGlomu() && muon2->GetGlomu() && !muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeTriMuon3);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    } else if ( muon1->GetGlomu() && muon2->GetGlomu() && muon3->GetGlomu() ) {
	      trimuon->SetTriggerType(kTakeAll);
	      trimuon->GetMuon1()->SetMatched(kTRUE);
	      trimuon->GetMuon2()->SetMatched(kTRUE);
	      trimuon->GetMuon3()->SetMatched(kTRUE);
	    } 
	  }
	} else if ( gTrigger->EventTriggeredByTLTVTX() ) {
	  // for MC, if event is only triggered by vtxm take both
	  trimuon->SetTriggerType(kTakeAll);
	  trimuon->GetMuon1()->SetMatched(kTRUE);
	  trimuon->GetMuon2()->SetMatched(kTRUE);
	  trimuon->GetMuon3()->SetMatched(kTRUE);
	}
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckAllCuts(GTriMuon *trimuon, Int_t flag ) {
  //
  // check trimuon if trimuon fulfills all cuts
  if ( gDebug ) cout << endl << "GTriMuons::CheckAllCuts called" << endl << endl;

  // take trimuon which muon fulfill all muon cuts or all MV muon cuts, and then 
  // check for all trimuon specific cuts
  
  // reset bool in case several trimuons are found:
  fDoCalcIsolation = kFALSE;
 
  if ( ( (trimuon->GetMuonsAllCuts() && !gCards->GetDoEfficiency()) || ( trimuon->GetMuonsMVCuts() && gCards->GetDoEfficiency() ) ) &&
       trimuon  -> GetInvMassCut()        &&
       trimuon  -> GetDeltaRCut()         &&
       ( trimuon-> GetDeltaPhiCut() || trimuon->GetDeltaThetaCut() ) &&
       trimuon  -> GetDeltaEtaCut()       &&
       trimuon  -> GetPtAsymetryCut()     &&
       trimuon  -> GetEtFractionHighCut() &&
       trimuon  -> GetEtFractionLowCut()  &&
       trimuon  -> GetDifChargeCut()      &&
       !trimuon -> GetCharmMCJpsiCut()    &&
       !trimuon -> GetCharmMCPsiprimeCut()) {

    if(flag == 0)      trimuon -> SetAllCuts(kTRUE);
    if(flag == 0)      trimuon -> SetType(kGoodTriMuon);
    if(flag == 0)      fNGoodTriMuons  += 1;
    if(flag == 0)      fAllCuts         = kTRUE;
    if(flag == 1)      fDoCalcIsolation = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CheckBestTriMuon(GTriMuon *trimuon, Int_t index) {
  //
  // determine index of best trimuon
  if ( gDebug ) cout << endl << "GTriMuons::CheckBestTriMuon called" << endl << endl;

  // take all trimuons
  if ( 42 == 42 ) {
    if ( trimuon->GetAllCuts() ) {
      trimuon->SetType(kChosenTriMuon);
      fNChosenTriMuons += 1;
    }
  } 
  // take the first
  else if ( fSelectedIndex == -99 ) {
    if ( trimuon->GetAllCuts() ) {
      fSelectedIndex = index;
      fNChosenTriMuons += 1;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::DetSelectedCand(Int_t index) {
  //
  // flag best trimuon fullfilling all cuts
  if ( gDebug ) cout << endl << "GTriMuons::DetSelectedCand called" << endl << endl;

  if ( index != -99 ) {
    GetTriMuon(index)->SetType(kChosenTriMuon);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::GetAllCuts() {
  //
  // returns true if event fulfills all muon-jet-trimuon cuts
  if ( gDebug ) cout << endl << "GTriMuons::GetAllCuts() called" << endl << endl;

  if ( gCards->GetTRIMUONNTrimuons() <= 0 )
    return kTRUE;
  else if ( fAllCuts )
    return kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

Bool_t GTriMuons::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GTriMuons::CreateControl() called" << endl << endl;
  
  if ( gCards->GetTRIMUONControl() ) {
  
    Int_t    nperevbins     = 10;
    Double_t nperevlow      = 0.;
    Double_t nperevhigh     = 10.;
    Int_t    massbins       = 1050;
    Double_t masslow        = 0.;
    Double_t masshigh       = 35.;
    Int_t    masslowbins    = 160;
    Double_t masslowlow     = 0.;
    Double_t masslowhigh    = 4.;
    Int_t    masshighbins   = 840;
    Double_t masshighlow    = 4.;
    Double_t masshighhigh   = 46.;
    Int_t    deltarbins     = 200;
    Double_t deltarlow      = 0.;
    Double_t deltarhigh     = 10.;
    Int_t    deltaphibins   = 20;
    Double_t deltaphilow    = 0.0;
    Double_t deltaphihigh   = TMath::Pi();
    Int_t    deltaetabins   = 400;
    Double_t deltaetalow    = -10.;
    Double_t deltaetahigh   = 10.;
    Int_t    deltathetabins = 60;
    Double_t deltathetalow  = -3.0;
    Double_t deltathetahigh = 3.0;
    Int_t    ptasymetrybins = 80;
    Double_t ptasymetrylow  = -.2;
    Double_t ptasymetryhigh = 1.4;
    Int_t    ptbins         = 140;
    Double_t ptlow          = 0.;
    Double_t pthigh         = 35.0;
    Int_t    etabins        = 160;
    Double_t etalow         = -4.;
    Double_t etahigh        = 4.0;
    Int_t    sqisol_10bins  = 400;
    Double_t sqisol_10low   = 0.;
    Double_t sqisol_10high  = 40.0;

    Int_t    thrustbins        = 50;
    Double_t thrustlow         = 0.;
    Double_t thrusthigh        = 1.0;
    Int_t    sphericitybins    = 50;
    Double_t sphericitylow     = 0.;
    Double_t sphericityhigh    = 1.0;
    Int_t    multiplicitybins  = 50;
    Double_t multiplicitylow   = 0.;
    Double_t multiplicityhigh  = 100.0;
    Int_t    isotropybins      = 50;
    Double_t isotropylow       = 0.;
    Double_t isotropyhigh      = 1.0;
    Int_t    q2primebins       = 100; 
    Double_t q2primelow        = 0.;
    Double_t q2primehigh       = 500.0;

    Int_t    impactbins        = 100;
    Double_t impactlow         = 0.;
    Double_t impacthigh        = 1.0; 

    fControlNperEv_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","NperEv_uncut","uncut n_{#mu#mu#mu}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu#mu}","Events");
    fControlTriMuonMass_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","TriMuonMass_uncut","uncut #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fControlTriMuonMassLow_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","TriMuonMassLow_uncut","uncut low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fControlTriMuonMassHigh_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","TriMuonMassHigh_uncut","uncut high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fControlMass_lu_is_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_lu_is_uncut","uncut #mass_lu_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_ll_is_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_ll_is_uncut","uncut #mass_ll_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hu_is_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_hu_is_uncut","uncut #mass_hu_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hl_is_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_hl_is_uncut","uncut #mass_hl_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_lu_nis_uncut","uncut #mass_lu_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_ll_nis_uncut","uncut #mass_ll_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_hu_nis_uncut","uncut #mass_hu_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Mass_hl_nis_uncut","uncut #mass_hl_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{uncut} [GeV]","Events");

    fControlDeltaR_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_uncut","uncut #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR","Events");
    fControlDeltaR_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_lu_is_uncut","uncut #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_is","Events");
    fControlDeltaR_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_ll_is_uncut","uncut #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_is","Events");
    fControlDeltaR_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_hu_is_uncut","uncut #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_is","Events");
    fControlDeltaR_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_hl_is_uncut","uncut #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_is","Events");
    fControlDeltaR_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_lu_nis_uncut","uncut #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_nis","Events");
    fControlDeltaR_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_ll_nis_uncut","uncut #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_nis","Events");
    fControlDeltaR_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_hu_nis_uncut","uncut #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_nis","Events");
    fControlDeltaR_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaR_hl_nis_uncut","uncut #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_nis","Events");
    fControlDeltaPhi_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_uncut","uncut #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","Events");
    fControlDeltaPhi_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_lu_is_uncut","uncut #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_is","Events");
    fControlDeltaPhi_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_ll_is_uncut","uncut #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_is","Events");
    fControlDeltaPhi_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_hu_is_uncut","uncut #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_is","Events");
    fControlDeltaPhi_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_hl_is_uncut","uncut #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_is","Events");
    fControlDeltaPhi_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_lu_nis_uncut","uncut #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_nis","Events");
    fControlDeltaPhi_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_ll_nis_uncut","uncut #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_nis","Events");
    fControlDeltaPhi_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_hu_nis_uncut","uncut #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_nis","Events");
    fControlDeltaPhi_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaPhi_hl_nis_uncut","uncut #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_nis","Events");
    fControlDeltaEta_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaEta_uncut","uncut #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta","Events");
    fControlDeltaTheta_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","DeltaTheta_uncut","uncut #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta","Events");
    fControlPtAsymetry_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_uncut","uncut p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.","Events");
    fControlPtAsymetry_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_lu_is_uncut","uncut_lu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.","Events");
    fControlPtAsymetry_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_ll_is_uncut","uncut_ll_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.","Events");
    fControlPtAsymetry_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_hu_is_uncut","uncut_hu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.","Events");
    fControlPtAsymetry_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_hl_is_uncut","uncut_hl_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.","Events");
    fControlPtAsymetry_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_lu_nis_uncut","uncut_lu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.","Events");
    fControlPtAsymetry_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_ll_nis_uncut","uncut_ll_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.","Events");
    fControlPtAsymetry_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_hu_nis_uncut","uncut_hu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.","Events");
    fControlPtAsymetry_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","PtAsymetry_hl_nis_uncut","uncut_hl_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.","Events");
    fControlpt_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_uncut","uncut p_{T}",ptbins,ptlow,pthigh,"p_{T}","Events");
    fControlpt_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_lu_is_uncut","uncut_lu_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_is","Events");
    fControlpt_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_ll_is_uncut","uncut_ll_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_is","Events");
    fControlpt_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_hu_is_uncut","uncut_hu_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_is","Events");
    fControlpt_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_hl_is_uncut","uncut_hl_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_is","Events");
    fControlpt_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_lu_nis_uncut","uncut_lu_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_nis","Events");
    fControlpt_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_ll_nis_uncut","uncut_ll_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_nis","Events");
    fControlpt_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_hu_nis_uncut","uncut_hu_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_nis","Events");
    fControlpt_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","pt_hl_nis_uncut","uncut_hl_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_nis","Events");
 
    fControleta_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_uncut","uncut #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fControleta_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_lu_is_uncut","uncut_lu_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_lu_is","Events");
    fControleta_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_ll_is_uncut","uncut_ll_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_ll_is","Events");
    fControleta_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_hu_is_uncut","uncut_hu_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hu_is","Events");
    fControleta_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_hl_is_uncut","uncut_hl_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hl_is","Events");
    fControleta_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_lu_nis_uncut","uncut_lu_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_lu_nis","Events");
    fControleta_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_ll_nis_uncut","uncut_ll_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_ll_nis","Events");
    fControleta_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_hu_nis_uncut","uncut_hu_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hu_nis","Events");
    fControleta_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","eta_hl_nis_uncut","uncut_hl_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hl_nis","Events");

    fControlImpact2D_uncut    = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_uncut","uncut Impact2D",impactbins,impactlow,impacthigh,"#2D_IP","Events");
    fControlImpact2D_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_lu_uncut","uncut_lu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_lu","Events");
    fControlImpact2D_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_ll_uncut","uncut_ll Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_ll","Events");
    fControlImpact2D_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_hu_uncut","uncut_hu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_hu","Events");
    fControlImpact2D_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_hl_uncut","uncut_hl Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_hl","Events");
    fControlImpact2D_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_lu_uncut","uncut_lu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_lu","Events");
    fControlImpact2D_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_ll_uncut","uncut_ll Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_ll","Events");
    fControlImpact2D_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_hu_uncut","uncut_hu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_hu","Events");
    fControlImpact2D_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_hl_uncut","uncut_hl Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_hl","Events");

    fControlsqisol_10_uncut    = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_uncut","uncut sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    fControlsqisol_10_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_is_lu_uncut","uncut_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_lu","Events");
    fControlsqisol_10_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_is_ll_uncut","uncut_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_ll","Events");
    fControlsqisol_10_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_is_hu_uncut","uncut_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hu","Events");
    fControlsqisol_10_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_is_hl_uncut","uncut_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hl","Events");
    fControlsqisol_10_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_nis_lu_uncut","uncut_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_lu","Events");
    fControlsqisol_10_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_nis_ll_uncut","uncut_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_ll","Events");
    fControlsqisol_10_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_nis_hu_uncut","uncut_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hu","Events");
    fControlsqisol_10_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sqisol_10_nis_hl_uncut","uncut_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hl","Events");

    fControlthrust_uncut    = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_uncut","uncut thrust",thrustbins,thrustlow,thrusthigh,"#thrust","Events");
    fControlthrust_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_lu_uncut","uncut_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_lu","Events");
    fControlthrust_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_ll_uncut","uncut_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_ll","Events");
    fControlthrust_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_hu_uncut","uncut_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hu","Events");
    fControlthrust_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_hl_uncut","uncut_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hl","Events");
    fControlthrust_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_lu_uncut","uncut_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_lu","Events");
    fControlthrust_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_ll_uncut","uncut_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_ll","Events");
    fControlthrust_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_hu_uncut","uncut_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hu","Events");
    fControlthrust_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_hl_uncut","uncut_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hl","Events");

//********************************************************
// Here Histograms for Instanton Variables
//********************************************************

    fControlQ2Prime_uncut    = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_uncut","uncut Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2}","Events");
    fControlQ2Prime_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_lu_uncut","uncut_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_lu","Events");
    fControlQ2Prime_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_ll_uncut","uncut_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_ll","Events");
    fControlQ2Prime_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_hu_uncut","uncut_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hu","Events");
    fControlQ2Prime_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_hl_uncut","uncut_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hl","Events");
    fControlQ2Prime_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_lu_uncut","uncut_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_lu","Events");
    fControlQ2Prime_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_ll_uncut","uncut_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_ll","Events");
    fControlQ2Prime_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_hu_uncut","uncut_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hu","Events");
    fControlQ2Prime_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_hl_uncut","uncut_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hl","Events");

    fControlsphericity_uncut    = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_uncut","uncut sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity","Events");
    fControlsphericity_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_lu_uncut","uncut_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_lu","Events");
    fControlsphericity_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_ll_uncut","uncut_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_ll","Events");
    fControlsphericity_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_hu_uncut","uncut_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hu","Events");
    fControlsphericity_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_hl_uncut","uncut_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hl","Events");
    fControlsphericity_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_lu_uncut","uncut_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_lu","Events");
    fControlsphericity_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_ll_uncut","uncut_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_ll","Events");
    fControlsphericity_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_hu_uncut","uncut_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hu","Events");
    fControlsphericity_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_hl_uncut","uncut_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hl","Events");

    fControlisotropy_uncut    = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_uncut","uncut isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy","Events");
    fControlisotropy_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_lu_uncut","uncut_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_lu","Events");
    fControlisotropy_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_ll_uncut","uncut_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_ll","Events");
    fControlisotropy_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_hu_uncut","uncut_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hu","Events");
    fControlisotropy_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_hl_uncut","uncut_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hl","Events");
    fControlisotropy_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_lu_uncut","uncut_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_lu","Events");
    fControlisotropy_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_ll_uncut","uncut_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_ll","Events");
    fControlisotropy_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_hu_uncut","uncut_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hu","Events");
    fControlisotropy_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_hl_uncut","uncut_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hl","Events");

    fControlmultiplicity_uncut        = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_uncut","uncut multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity","Events");
    fControlmultiplicity_is_lu_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_lu_uncut","uncut_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_lu","Events");
    fControlmultiplicity_is_ll_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_ll_uncut","uncut_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_ll","Events");
    fControlmultiplicity_is_hu_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_hu_uncut","uncut_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hu","Events");
    fControlmultiplicity_is_hl_uncut  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_hl_uncut","uncut_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hl","Events");
    fControlmultiplicity_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_lu_uncut","uncut_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_lu","Events");
    fControlmultiplicity_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_ll_uncut","uncut_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_ll","Events");
    fControlmultiplicity_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_hu_uncut","uncut_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hu","Events");
    fControlmultiplicity_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_hl_uncut","uncut_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hl","Events");


//*******************************************************

    fControlNperEvGood          = gHistogrammer->TH1DFactory("TriMuon_Control","NperEvGood","n_{#mu#mu#mu,good}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu#mu}^{good}","Events");
    fControlGoodTriMuonMass     = gHistogrammer->TH1DFactory("TriMuon_Control","GoodTriMuonMass","good #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodTriMuonMassLow  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodTriMuonMassLow","good low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodTriMuonMassHigh = gHistogrammer->TH1DFactory("TriMuon_Control","GoodTriMuonMassHigh","good high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");

    fControlGoodMass_lu_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_lu_is_uncut","good #mass_lu_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_ll_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_ll_is_uncut","good #mass_ll_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hu_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_hu_is_uncut","good #mass_hu_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hl_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_hl_is_uncut","good #mass_hl_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_lu_nis_uncut","good #mass_lu_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_ll_nis_uncut","good #mass_ll_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_hu_nis_uncut","good #mass_hu_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodMass_hl_nis_uncut","good #mass_hl_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");

    fControlGoodDeltaR       = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR","good #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}","Events");
    fControlGoodDeltaR_lu_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_lu_is","good #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_lu_is","Events");
    fControlGoodDeltaR_ll_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_ll_is","good #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_ll_is","Events");
    fControlGoodDeltaR_hu_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_hu_is","good #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hu_is","Events");
    fControlGoodDeltaR_hl_is = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_hl_is","good #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hl_is","Events");
    fControlGoodDeltaR_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_lu_nis","good #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_lu_nis","Events");
    fControlGoodDeltaR_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_ll_nis","good #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_ll_nis","Events");
    fControlGoodDeltaR_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_hu_nis","good #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hu_nis","Events");
    fControlGoodDeltaR_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaR_hl_nis","good #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hl_nis","Events");

    fControlGoodDeltaPhi        = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi","good #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}","Events");
    fControlGoodDeltaPhi_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_lu_is","good #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_lu_is","Events");
    fControlGoodDeltaPhi_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_ll_is","good #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_ll_is","Events");
    fControlGoodDeltaPhi_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_hu_is","good #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hu_is","Events");
    fControlGoodDeltaPhi_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_hl_is","good #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hl_is","Events");
    fControlGoodDeltaPhi_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_lu_nis","good #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_lu_nis","Events");
    fControlGoodDeltaPhi_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_ll_nis","good #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_ll_nis","Events");
    fControlGoodDeltaPhi_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_hu_nis","good #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hu_nis","Events");
    fControlGoodDeltaPhi_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaPhi_hl_nis","good #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hl_nis","Events");

    fControlGoodDeltaEta   = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaEta","good #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta^{good}","Events");
    fControlGoodDeltaTheta = gHistogrammer->TH1DFactory("TriMuon_Control","GoodDeltaTheta","good #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta^{good}","Events");

    fControlGoodPtAsymetry        = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry","good p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.^{good}","Events");
    fControlGoodPtAsymetry_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_lu_is","good_lu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.^{good}","Events");
    fControlGoodPtAsymetry_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_ll_is","good_ll_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.^{good}","Events");
    fControlGoodPtAsymetry_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_hu_is","good_hu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.^{good}","Events");
    fControlGoodPtAsymetry_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_hl_is","good_hl_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.^{good}","Events");
    fControlGoodPtAsymetry_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_lu_nis","good_lu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.^{good}","Events");
    fControlGoodPtAsymetry_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_ll_nis","good_ll_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.^{good}","Events");
    fControlGoodPtAsymetry_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_hu_nis","good_hu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.^{good}","Events");
    fControlGoodPtAsymetry_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","GoodPtAsymetry_hl_nis","good_hl_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.^{good}","Events");

    fControlGoodpt        = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt","good p_{T} ",ptbins,ptlow,pthigh,"p_{T}^{good}","Events");
    fControlGoodpt_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_lu_is","good #pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_lu_is","Events");
    fControlGoodpt_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_ll_is","good #pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_ll_is","Events");
    fControlGoodpt_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_hu_is","good #pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hu_is","Events");
    fControlGoodpt_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_hl_is","good #pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hl_is","Events");
    fControlGoodpt_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_lu_nis","good #pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_lu_nis","Events");
    fControlGoodpt_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_ll_nis","good #pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_ll_nis","Events");
    fControlGoodpt_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_hu_nis","good #pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hu_nis","Events");
    fControlGoodpt_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodpt_hl_nis","good #pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hl_nis","Events");

    fControlGoodeta        = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta","good #eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu}^{good}","Events");
    fControlGoodeta_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_lu_is","good #eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_lu_is","Events");
    fControlGoodeta_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_ll_is","good #eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_ll_is","Events");
    fControlGoodeta_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_hu_is","good #eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hu_is","Events");
    fControlGoodeta_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_hl_is","good #eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hl_is","Events");
    fControlGoodeta_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_lu_nis","good #eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_lu_nis","Events");
    fControlGoodeta_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_ll_nis","good #eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_ll_nis","Events");
    fControlGoodeta_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_hu_nis","good #eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hu_nis","Events");
    fControlGoodeta_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Goodeta_hl_nis","good #eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hl_nis","Events");

    fControlGoodImpact2D        = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D","good Impact2D",impactbins,impactlow,impacthigh,"#2D_IP^{good}","Events");
    fControlGoodImpact2D_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_lu","good_lu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{good}_is_lu","Events");
    fControlGoodImpact2D_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_ll","good_ll Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{good}_is_ll","Events");
    fControlGoodImpact2D_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_hu","good_hu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{good}_is_hu","Events");
    fControlGoodImpact2D_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_is_hl","good_hl Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{good}_is_hl","Events");
    fControlGoodImpact2D_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_lu","good_lu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{good}_nis_lu","Events");
    fControlGoodImpact2D_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_ll","good_ll Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{good}_nis_ll","Events");
    fControlGoodImpact2D_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_hu","good_hu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{good}_nis_hu","Events");
    fControlGoodImpact2D_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","Impact2D_nis_hl","good_hl Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{good}_nis_hl","Events");

    fControlGoodsqisol_10        = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10","good sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}^{good}","Events");
    fControlGoodsqisol_10_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_is_lu","good_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_lu","Events");
    fControlGoodsqisol_10_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_is_ll","good_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_ll","Events");
    fControlGoodsqisol_10_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_is_hu","good_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_hu","Events");
    fControlGoodsqisol_10_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_is_hl","good_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_hl","Events");
    fControlGoodsqisol_10_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_nis_lu","good_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_lu","Events");
    fControlGoodsqisol_10_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_nis_ll","good_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_ll","Events");
    fControlGoodsqisol_10_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_nis_hu","good_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_hu","Events");
    fControlGoodsqisol_10_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","Goodsqisol_10_nis_hl","good_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_hl","Events");

    fControlGoodthrust        = gHistogrammer->TH1DFactory("TriMuon_Control","thrust","good thrust",thrustbins,thrustlow,thrusthigh,"#thrust^{good}","Events");
    fControlGoodthrust_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_lu","good_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_lu","Events");
    fControlGoodthrust_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_ll","good_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_ll","Events");
    fControlGoodthrust_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_hu","good_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_hu","Events");
    fControlGoodthrust_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_is_hl","good_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_hl","Events");
    fControlGoodthrust_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_lu","good_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_lu","Events");
    fControlGoodthrust_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_ll","good_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_ll","Events");
    fControlGoodthrust_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_hu","good_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_hu","Events");
    fControlGoodthrust_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","thrust_nis_hl","good_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_hl","Events");

//********************************************************
// Here Histograms for Instanton Variables
//********************************************************

    fControlGoodQ2Prime        = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime","good Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}","Events");
    fControlGoodQ2Prime_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_lu","good_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_lu","Events");
    fControlGoodQ2Prime_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_ll","good_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_ll","Events");
    fControlGoodQ2Prime_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_hu","good_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_hu","Events");
    fControlGoodQ2Prime_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_is_hl","good_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_hl","Events");
    fControlGoodQ2Prime_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_lu","good_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_lu","Events");
    fControlGoodQ2Prime_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_ll","good_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_ll","Events");
    fControlGoodQ2Prime_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_hu","good_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_hu","Events");
    fControlGoodQ2Prime_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","Q2Prime_nis_hl","good_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_hl","Events");

    fControlGoodsphericity         = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity","good sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}","Events");
    fControlGoodsphericity_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_lu","good_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_lu","Events");
    fControlGoodsphericity_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_ll","good_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_ll","Events");
    fControlGoodsphericity_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_hu","good_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_hu","Events");
    fControlGoodsphericity_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_is_hl","good_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_hl","Events");
    fControlGoodsphericity_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_lu","good_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_lu","Events");
    fControlGoodsphericity_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_ll","good_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_ll","Events");
    fControlGoodsphericity_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_hu","good_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_hu","Events");
    fControlGoodsphericity_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","sphericity_nis_hl","good_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_hl","Events");

    fControlGoodisotropy        = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy","good isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}","Events");
    fControlGoodisotropy_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_lu","good_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_lu","Events");
    fControlGoodisotropy_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_ll","good_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_ll","Events");
    fControlGoodisotropy_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_hu","good_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_hu","Events");
    fControlGoodisotropy_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_is_hl","good_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_hl","Events");
    fControlGoodisotropy_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_lu","good_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_lu","Events");
    fControlGoodisotropy_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_ll","good_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_ll","Events");
    fControlGoodisotropy_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_hu","good_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_hu","Events");
    fControlGoodisotropy_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","isotropy_nis_hl","good_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_hl","Events");

    fControlGoodmultiplicity        = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity","good multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}","Events");
    fControlGoodmultiplicity_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_lu","good_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_lu","Events");
    fControlGoodmultiplicity_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_ll","good_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_ll","Events");
    fControlGoodmultiplicity_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_hu","good_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_hu","Events");
    fControlGoodmultiplicity_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_is_hl","good_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_hl","Events");
    fControlGoodmultiplicity_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_lu","good_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_lu","Events");
    fControlGoodmultiplicity_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_ll","good_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_ll","Events");
    fControlGoodmultiplicity_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_hu","good_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_hu","Events");
    fControlGoodmultiplicity_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","multiplicity_nis_hl","good_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_hl","Events");


//*******************************************************

    fControlNperEvChosen          = gHistogrammer->TH1DFactory("TriMuon_Control","NperEvChosen","n_{#mu#mu#mu,chosen}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu#mu}^{chosen}","Events");
    fControlChosenTriMuonMass     = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenTriMuonMass","chosen #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenTriMuonMassLow  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenTriMuonMassLow","chosen low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenTriMuonMassHigh = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenTriMuonMassHigh","chosen high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");

    fControlChosenMass_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_lu_is_uncut","chosen #mass_lu_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_ll_is_uncut","chosen #mass_ll_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_hu_is_uncut","chosen #mass_hu_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_hl_is_uncut","chosen #mass_hl_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_lu_nis_uncut","chosen #mass_lu_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_ll_nis_uncut","chosen #mass_ll_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_hu_nis_uncut","chosen #mass_hu_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenMass_hl_nis_uncut","chosen #mass_hl_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");

    fControlChosenDeltaR        = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR","chosen #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}","Events");
    fControlChosenDeltaR_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_lu_is","chosen #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_lu_is","Events");
    fControlChosenDeltaR_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_ll_is","chosen #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_ll_is","Events");
    fControlChosenDeltaR_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_hu_is","chosen #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hu_is","Events");
    fControlChosenDeltaR_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_hl_is","chosen #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hl_is","Events");
    fControlChosenDeltaR_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_lu_nis","chosen #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_lu_nis","Events");
    fControlChosenDeltaR_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_ll_nis","chosen #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_ll_nis","Events");
    fControlChosenDeltaR_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_hu_nis","chosen #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hu_nis","Events");
    fControlChosenDeltaR_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaR_hl_nis","chosen #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hl_nis","Events");

    fControlChosenDeltaPhi        = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi","chosen #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}","Events");
    fControlChosenDeltaPhi_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_lu_is","chosen #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_lu_is","Events");
    fControlChosenDeltaPhi_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_ll_is","chosen #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_ll_is","Events");
    fControlChosenDeltaPhi_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_hu_is","chosen #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hu_is","Events");
    fControlChosenDeltaPhi_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_hl_is","chosen #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hl_is","Events");
    fControlChosenDeltaPhi_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_lu_nis","chosen #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_lu_nis","Events");
    fControlChosenDeltaPhi_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_ll_nis","chosen #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_ll_nis","Events");
    fControlChosenDeltaPhi_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_hu_nis","chosen #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hu_nis","Events");
    fControlChosenDeltaPhi_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaPhi_hl_nis","chosen #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hl_nis","Events");

    fControlChosenDeltaEta   = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaEta","chosen #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta^{chosen}","Events");
    fControlChosenDeltaTheta = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenDeltaTheta","chosen #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta^{chosen}","Events");

    fControlChosenPtAsymetry        = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry","chosen p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"uncut p_{T} asym.^{chosen}","Events");
    fControlChosenPtAsymetry_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_lu_is","chosen p_{T}_lu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_ll_is","chosen p_{T}_ll_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_hu_is","chosen p_{T}_hu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_hl_is","chosen p_{T}_hl_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_lu_nis","chosen p_{T}_lu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.^{chosen}","Events");
    fControlChosenPtAsymetry_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_ll_nis","chosen p_{T}_ll_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_hu_nis","chosen p_{T}_hu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","ChosenPtAsymetry_hl_nis","chosen p_{T}_hl_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.^{chosen}","Events");

    fControlChosenpt        = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt","chosen p_{T} ",ptbins,ptlow,pthigh,"p_{T}^{chosen}","Events");
    fControlChosenpt_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_lu_is","chosen #pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_lu_is","Events");
    fControlChosenpt_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_ll_is","chosen #pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_ll_is","Events");
    fControlChosenpt_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_hu_is","chosen #pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hu_is","Events");
    fControlChosenpt_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_hl_is","chosen #pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hl_is","Events");
    fControlChosenpt_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_lu_nis","chosen #pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_lu_nis","Events");
    fControlChosenpt_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_ll_nis","chosen #pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_ll_nis","Events");
    fControlChosenpt_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_hu_nis","chosen #pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hu_nis","Events");
    fControlChosenpt_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Chosenpt_hl_nis","chosen #pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hl_nis","Events");

    fControlChoseneta        = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta","chosen #eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}","Events");
    fControlChoseneta_lu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_lu_is","chosen #eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_lu_is","Events");
    fControlChoseneta_ll_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_ll_is","chosen #eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_ll_is","Events");
    fControlChoseneta_hu_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_hu_is","chosen #eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hu_is","Events");
    fControlChoseneta_hl_is  = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_hl_is","chosen #eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hl_is","Events");
    fControlChoseneta_lu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_lu_nis","chosen #eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_lu_nis","Events");
    fControlChoseneta_ll_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_ll_nis","chosen #eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_ll_nis","Events");
    fControlChoseneta_hu_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_hu_nis","chosen #eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hu_nis","Events");
    fControlChoseneta_hl_nis = gHistogrammer->TH1DFactory("TriMuon_Control","Choseneta_hl_nis","chosen #eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hl_nis","Events");

    fControlChosenImpact2D        = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D","chosen Impact2D",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}","Events");
    fControlChosenImpact2D_is_lu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_is_lu","chosen_lu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_is_lu","Events");
    fControlChosenImpact2D_is_ll  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_is_ll","chosen_ll Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_is_ll","Events");
    fControlChosenImpact2D_is_hu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_is_hu","chosen_hu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_is_hu","Events");
    fControlChosenImpact2D_is_hl  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_is_hl","chosen_hl Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_is_hl","Events");
    fControlChosenImpact2D_nis_lu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_nis_lu","chosen_lu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_nis_lu","Events");
    fControlChosenImpact2D_nis_ll = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_nis_ll","chosen_ll Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_nis_ll","Events");
    fControlChosenImpact2D_nis_hu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_nis_hu","chosen_hu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_nis_hu","Events");
    fControlChosenImpact2D_nis_hl = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Impact2D_nis_hl","chosen_hl Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP^{chosen}_nis_hl","Events");

    fControlChosensqisol_10        = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10   ","chosen sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}^{chosen}","Events");
    fControlChosensqisol_10_is_lu  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_is_lu","chosen_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_lu","Events");
    fControlChosensqisol_10_is_ll  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_is_ll","chosen_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_ll","Events");
    fControlChosensqisol_10_is_hu  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_is_hu","chosen_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_hu","Events");
    fControlChosensqisol_10_is_hl  = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_is_hl","chosen_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_hl","Events");
    fControlChosensqisol_10_nis_lu = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_nis_lu","chosen_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_lu","Events");
    fControlChosensqisol_10_nis_ll = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_nis_ll","chosen_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_ll","Events");
    fControlChosensqisol_10_nis_hu = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_nis_hu","chosen_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_hu","Events");
    fControlChosensqisol_10_nis_hl = gHistogrammer->TH1DFactory("TriMuon_Control","Chosensqisol_10_nis_hl","chosen_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_hl","Events");

    fControlChosenthrust        = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust","chosen thrust",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}","Events");
    fControlChosenthrust_is_lu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_is_lu","chosen_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_lu","Events");
    fControlChosenthrust_is_ll  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_is_ll","chosen_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_ll","Events");
    fControlChosenthrust_is_hu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_is_hu","chosen_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_hu","Events");
    fControlChosenthrust_is_hl  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_is_hl","chosen_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_hl","Events");
    fControlChosenthrust_nis_lu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_nis_lu","chosen_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_lu","Events");
    fControlChosenthrust_nis_ll = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_nis_ll","chosen_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_ll","Events");
    fControlChosenthrust_nis_hu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_nis_hu","chosen_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_hu","Events");
    fControlChosenthrust_nis_hl = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","thrust_nis_hl","chosen_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_hl","Events");

//********************************************************
// Here Histograms for Instanton Variables
//********************************************************

    fControlChosenQ2Prime        = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime","chosen Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}","Events");
    fControlChosenQ2Prime_is_lu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_is_lu","chosen_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_lu","Events");
    fControlChosenQ2Prime_is_ll  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_is_ll","chosen_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_ll","Events");
    fControlChosenQ2Prime_is_hu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_is_hu","chosen_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_hu","Events");
    fControlChosenQ2Prime_is_hl  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_is_hl","chosen_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_hl","Events");
    fControlChosenQ2Prime_nis_lu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_nis_lu","chosen_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_lu","Events");
    fControlChosenQ2Prime_nis_ll = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_nis_ll","chosen_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_ll","Events");
    fControlChosenQ2Prime_nis_hu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_nis_hu","chosen_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_hu","Events");
    fControlChosenQ2Prime_nis_hl = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","Q2Prime_nis_hl","chosen_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_hl","Events");

    fControlChosensphericity        = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity","chosen sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}","Events");
    fControlChosensphericity_is_lu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_is_lu","chosen_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_lu","Events");
    fControlChosensphericity_is_ll  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_is_ll","chosen_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_ll","Events");
    fControlChosensphericity_is_hu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_is_hu","chosen_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_hu","Events");
    fControlChosensphericity_is_hl  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_is_hl","chosen_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_hl","Events");
    fControlChosensphericity_nis_lu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_nis_lu","chosen_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_lu","Events");
    fControlChosensphericity_nis_ll = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_nis_ll","chosen_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_ll","Events");
    fControlChosensphericity_nis_hu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_nis_hu","chosen_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_hu","Events");
    fControlChosensphericity_nis_hl = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","sphericity_nis_hl","chosen_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_hl","Events");

    fControlChosenisotropy        = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy","chosen isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}","Events");
    fControlChosenisotropy_is_lu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_is_lu","chosen_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_lu","Events");
    fControlChosenisotropy_is_ll  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_is_ll","chosen_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_ll","Events");
    fControlChosenisotropy_is_hu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_is_hu","chosen_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_hu","Events");
    fControlChosenisotropy_is_hl  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_is_hl","chosen_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_hl","Events");
    fControlChosenisotropy_nis_lu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_nis_lu","chosen_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_lu","Events");
    fControlChosenisotropy_nis_ll = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_nis_ll","chosen_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_ll","Events");
    fControlChosenisotropy_nis_hu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_nis_hu","chosen_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_hu","Events");
    fControlChosenisotropy_nis_hl = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","isotropy_nis_hl","chosen_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_hl","Events");

    fControlChosenmultiplicity        = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity","chosen multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}","Events");
    fControlChosenmultiplicity_is_lu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_is_lu","chosen_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_lu","Events");
    fControlChosenmultiplicity_is_ll  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_is_ll","chosen_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_ll","Events");
    fControlChosenmultiplicity_is_hu  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_is_hu","chosen_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_hu","Events");
    fControlChosenmultiplicity_is_hl  = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_is_hl","chosen_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_hl","Events");
    fControlChosenmultiplicity_nis_lu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_nis_lu","chosen_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_lu","Events");
    fControlChosenmultiplicity_nis_ll = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_nis_ll","chosen_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_ll","Events");
    fControlChosenmultiplicity_nis_hu = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_nis_hu","chosen_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_hu","Events");
    fControlChosenmultiplicity_nis_hl = gHistogrammer->TH1DFactory("TriMuon_ControlChosen","multiplicity_nis_hl","chosen_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_hl","Events");

//*******************************************************

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillControl() {
  //
  // fill control histograms
  if ( gDebug ) cout << endl << "GTriMuons::FillControl() called" << endl << endl;

  if ( gCards->GetTRIMUONControl() ) {

    fControlNperEv_uncut -> Fill(fNTriMuons);
    fControlNperEvGood   -> Fill(fNGoodTriMuons);
    fControlNperEvChosen -> Fill(fNChosenTriMuons);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GTriMuons::FillHistos() called" << endl << endl;

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GTriMuons::ObjectsFillHistos() called" << endl << endl;

  // loop over array
  for ( Int_t i = 0; i < fNTriMuons; i++ ) {
    GTriMuon *trimuon = ((GTriMuon*)(fTriMuons->At(i)));

    // fill control plots
    ObjectsFillControl(trimuon);

    // fill general plots
    ObjectsFillGeneral(trimuon);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::ObjectsFillControl(GTriMuon *trimuon) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GTriMuons::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetTRIMUONControl() ) {

    Double_t invMass1         = trimuon->GetInvMass1();
    Double_t invMass2         = trimuon->GetInvMass2();
    Double_t invMass3         = trimuon->GetInvMass3();
    Double_t deltaR1          = trimuon->GetDeltaR1();
    Double_t deltaR2          = trimuon->GetDeltaR2();
    Double_t deltaR3          = trimuon->GetDeltaR3();
    Double_t deltaPhi1        = trimuon->GetDeltaPhi2();
    Double_t deltaPhi2        = trimuon->GetDeltaPhi2();
    Double_t deltaPhi3        = trimuon->GetDeltaPhi3();
    Double_t deltaEta1        = trimuon->GetDeltaEta1();
    Double_t deltaEta2        = trimuon->GetDeltaEta2();
    Double_t deltaEta3        = trimuon->GetDeltaEta3();
    Double_t deltaTheta1      = trimuon->GetDeltaTheta1();
    Double_t deltaTheta2      = trimuon->GetDeltaTheta2();
    Double_t deltaTheta3      = trimuon->GetDeltaTheta3();
    Double_t ptAsymetry1      = trimuon->GetPtAsymetry1();
    Double_t ptAsymetry2      = trimuon->GetPtAsymetry2();
    Double_t ptAsymetry3      = trimuon->GetPtAsymetry3();
    Double_t IsolationSqSum10 = trimuon->GetIsolationSqSum10();
    Double_t thrust           = gZufo->GetThrust();
    Double_t sphericity       = gZufo->GetSphericity();
    Double_t multiplicity     = gZufo->GetMultiplicity();
    Double_t Q2Prime          = gZufo->GetQ2Prime();
    Double_t isotropy         = gZufo->GetIsotropy();

    fControlTriMuonMass_uncut->Fill(invMass1);
    fControlTriMuonMass_uncut->Fill(invMass2);
    fControlTriMuonMass_uncut->Fill(invMass3);
    if( invMass1 <= 4 )  fControlTriMuonMassLow_uncut->Fill(invMass1,gHeader->GetWeight());
    if( invMass2 <= 4 )  fControlTriMuonMassLow_uncut->Fill(invMass2,gHeader->GetWeight());
    if( invMass3 <= 4 )  fControlTriMuonMassLow_uncut->Fill(invMass3,gHeader->GetWeight());
    
    if( invMass1 > 4 )   fControlTriMuonMassHigh_uncut->Fill(invMass1,gHeader->GetWeight());
    if( invMass2 > 4 )   fControlTriMuonMassHigh_uncut->Fill(invMass2,gHeader->GetWeight());
    if( invMass3 > 4 )   fControlTriMuonMassHigh_uncut->Fill(invMass3,gHeader->GetWeight());
    
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlMass_lu_is_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlMass_lu_is_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlMass_lu_is_uncut->Fill(invMass3,gHeader->GetWeight()); 
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlMass_ll_is_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlMass_ll_is_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlMass_ll_is_uncut->Fill(invMass3,gHeader->GetWeight()); 
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlMass_hu_is_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlMass_hu_is_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlMass_hu_is_uncut->Fill(invMass3,gHeader->GetWeight()); 
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlMass_hl_is_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlMass_hl_is_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlMass_hl_is_uncut->Fill(invMass3,gHeader->GetWeight()); 
    }						     
    else{					      
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlMass_lu_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlMass_lu_nis_uncut->Fill(invMass2,gHeader->GetWeight());
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlMass_lu_nis_uncut->Fill(invMass3,gHeader->GetWeight());
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlMass_ll_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlMass_ll_nis_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlMass_ll_nis_uncut->Fill(invMass3,gHeader->GetWeight()); 
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlMass_hu_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlMass_hu_nis_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlMass_hu_nis_uncut->Fill(invMass3,gHeader->GetWeight()); 
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlMass_hl_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlMass_hl_nis_uncut->Fill(invMass2,gHeader->GetWeight()); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlMass_hl_nis_uncut->Fill(invMass3,gHeader->GetWeight()); 
    }                                 
                  
    fControlDeltaR_uncut->Fill(deltaR1,gHeader->GetWeight());
    fControlDeltaR_uncut->Fill(deltaR2,gHeader->GetWeight());
    fControlDeltaR_uncut->Fill(deltaR3,gHeader->GetWeight());
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaR_lu_is_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaR_lu_is_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaR_lu_is_uncut->Fill(deltaR3,gHeader->GetWeight()); 
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaR_ll_is_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaR_ll_is_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaR_ll_is_uncut->Fill(deltaR3,gHeader->GetWeight()); 
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaR_hu_is_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaR_hu_is_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaR_hu_is_uncut->Fill(deltaR3,gHeader->GetWeight()); 
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlDeltaR_lu_is_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlDeltaR_lu_is_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlDeltaR_lu_is_uncut->Fill(deltaR3,gHeader->GetWeight()); 
    }
    else{
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaR_lu_nis_uncut->Fill(deltaR1,gHeader->GetWeight());
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaR_lu_nis_uncut->Fill(deltaR2,gHeader->GetWeight());
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaR_lu_nis_uncut->Fill(deltaR3,gHeader->GetWeight());
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaR_ll_nis_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaR_ll_nis_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaR_ll_nis_uncut->Fill(deltaR3,gHeader->GetWeight()); 
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaR_hu_nis_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaR_hu_nis_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaR_hu_nis_uncut->Fill(deltaR3,gHeader->GetWeight()); 
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlDeltaR_hl_nis_uncut->Fill(deltaR1,gHeader->GetWeight()); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlDeltaR_hl_nis_uncut->Fill(deltaR2,gHeader->GetWeight()); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlDeltaR_hl_nis_uncut->Fill(deltaR3,gHeader->GetWeight()); 
    }                                        

    fControlDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi1),gHeader->GetWeight());
    fControlDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi2),gHeader->GetWeight());
    fControlDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi3),gHeader->GetWeight());
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaPhi_lu_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() );
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaPhi_lu_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() );
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaPhi_lu_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() );
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaPhi_ll_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() );
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaPhi_ll_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() );
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaPhi_ll_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() );
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaPhi_hu_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() ); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaPhi_hu_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() ); 
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaPhi_hu_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() ); 
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlDeltaPhi_hl_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() );
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlDeltaPhi_hl_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() );
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlDeltaPhi_hl_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() );
    }
    else{
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaPhi_lu_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() ); 
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaPhi_lu_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() ); 
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlDeltaPhi_lu_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() ); 
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaPhi_ll_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() ); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaPhi_ll_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() );
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlDeltaPhi_ll_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() );
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaPhi_hu_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() );
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaPhi_hu_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() );
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlDeltaPhi_hu_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() );
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlDeltaPhi_hl_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight() ); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlDeltaPhi_hl_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight() ); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlDeltaPhi_hl_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight() ); 
    }
  
    fControlDeltaEta_uncut->Fill(deltaEta1,gHeader->GetWeight());
    fControlDeltaEta_uncut->Fill(deltaEta2,gHeader->GetWeight());
    fControlDeltaEta_uncut->Fill(deltaEta3,gHeader->GetWeight());

    fControlDeltaTheta_uncut->Fill(deltaTheta1,gHeader->GetWeight());
    fControlDeltaTheta_uncut->Fill(deltaTheta2,gHeader->GetWeight());
    fControlDeltaTheta_uncut->Fill(deltaTheta3,gHeader->GetWeight());

    fControlPtAsymetry_uncut->Fill(ptAsymetry1,gHeader->GetWeight());
    fControlPtAsymetry_uncut->Fill(ptAsymetry2,gHeader->GetWeight());
    fControlPtAsymetry_uncut->Fill(ptAsymetry3,gHeader->GetWeight());

    if( !trimuon->GetSqSumIsolationCut() ) {     
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlPtAsymetry_lu_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlPtAsymetry_lu_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlPtAsymetry_lu_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlPtAsymetry_ll_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlPtAsymetry_ll_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlPtAsymetry_ll_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlPtAsymetry_hu_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlPtAsymetry_hu_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlPtAsymetry_hu_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlPtAsymetry_hl_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlPtAsymetry_hl_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlPtAsymetry_hl_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
    }
    else{
      if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlPtAsymetry_lu_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlPtAsymetry_lu_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlPtAsymetry_lu_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlPtAsymetry_ll_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlPtAsymetry_ll_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlPtAsymetry_ll_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlPtAsymetry_hu_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlPtAsymetry_hu_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight());
      if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlPtAsymetry_hu_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight());
      if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlPtAsymetry_hl_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
      if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlPtAsymetry_hl_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
      if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlPtAsymetry_hl_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
    }
  
    fControlpt_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() );
    fControlpt_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );
    fControlpt_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlpt_lu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_lu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlpt_lu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_lu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlpt_lu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_lu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlpt_ll_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_ll_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlpt_ll_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_ll_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlpt_ll_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_ll_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlpt_hu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlpt_hu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlpt_hu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_hu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlpt_hl_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hl_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlpt_hl_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hl_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlpt_hl_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_hl_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
    }
    else{
      if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlpt_lu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_lu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlpt_lu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_lu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlpt_lu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_lu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlpt_ll_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_ll_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlpt_ll_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_ll_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlpt_ll_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_ll_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlpt_hu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlpt_hu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlpt_hu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_hu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlpt_hl_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hl_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
      if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlpt_hl_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlpt_hl_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlpt_hl_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlpt_hl_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
    }
  
    fControleta_uncut->Fill( trimuon->GetMuon1()->Eta() ,gHeader->GetWeight());
    fControleta_uncut->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight());
    fControleta_uncut->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight());
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControleta_lu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_lu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControleta_lu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_lu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControleta_lu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_lu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControleta_ll_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_ll_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControleta_ll_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_ll_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControleta_ll_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_ll_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControleta_hu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); }
      if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControleta_hu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControleta_hu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_hu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControleta_hl_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hl_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControleta_hl_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hl_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControleta_hl_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_hl_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
    }
    else{
      if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControleta_lu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_lu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControleta_lu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_lu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControleta_lu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_lu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControleta_ll_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_ll_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControleta_ll_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_ll_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControleta_ll_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_ll_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControleta_hu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControleta_hu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControleta_hu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_hu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControleta_hl_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hl_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
      if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControleta_hl_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControleta_hl_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControleta_hl_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControleta_hl_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
    }
  
    fControlImpact2D_uncut->Fill(trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
    fControlImpact2D_uncut->Fill(trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
    fControlImpact2D_uncut->Fill(trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight());
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlImpact2D_is_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlImpact2D_is_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlImpact2D_is_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlImpact2D_is_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlImpact2D_is_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlImpact2D_is_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlImpact2D_is_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlImpact2D_is_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlImpact2D_is_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlImpact2D_is_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlImpact2D_is_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlImpact2D_is_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_is_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
    }
    else{
      if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
    }
  
    fControlsqisol_10_uncut->Fill( IsolationSqSum10 ,gHeader->GetWeight());
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() ) { fControlsqisol_10_is_lu_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() ) { fControlsqisol_10_is_ll_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) &&  trimuon->GetDifCharge() ) { fControlsqisol_10_is_hu_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) && !trimuon->GetDifCharge() ) { fControlsqisol_10_is_hl_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());} 
    }
    else{
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() ) { fControlsqisol_10_nis_lu_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() ) { fControlsqisol_10_nis_ll_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) { fControlsqisol_10_nis_hu_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4 )  && !trimuon->GetDifCharge() ) { fControlsqisol_10_nis_hl_uncut->Fill(IsolationSqSum10,gHeader->GetWeight());}
    }
    
    fControlthrust_uncut      -> Fill( thrust,       gHeader->GetWeight());
    fControlsphericity_uncut  -> Fill( sphericity,   gHeader->GetWeight());
    fControlisotropy_uncut    -> Fill( isotropy,     gHeader->GetWeight());
    fControlQ2Prime_uncut     -> Fill( Q2Prime,      gHeader->GetWeight());
    fControlmultiplicity_uncut-> Fill( multiplicity, gHeader->GetWeight());   
    if( !trimuon->GetSqSumIsolationCut() ) {      
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {
	fControlthrust_is_lu_uncut       -> Fill(thrust       , gHeader->GetWeight()); 
	fControlsphericity_is_lu_uncut   -> Fill(sphericity   , gHeader->GetWeight()); 
	fControlisotropy_is_lu_uncut     -> Fill(isotropy     , gHeader->GetWeight()); 
	fControlmultiplicity_is_lu_uncut -> Fill(multiplicity , gHeader->GetWeight()); 
	fControlQ2Prime_is_hl_uncut      -> Fill(Q2Prime      , gHeader->GetWeight()); 
      }
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {
	fControlthrust_is_ll_uncut       -> Fill(thrust       , gHeader->GetWeight());
	fControlsphericity_is_ll_uncut   -> Fill(sphericity   , gHeader->GetWeight());
	fControlisotropy_is_ll_uncut     -> Fill(isotropy     , gHeader->GetWeight());
	fControlmultiplicity_is_ll_uncut -> Fill(multiplicity , gHeader->GetWeight());
	fControlQ2Prime_is_hl_uncut      -> Fill(Q2Prime      , gHeader->GetWeight());
      }
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  )  &&  trimuon->GetDifCharge() ) {
	fControlthrust_is_hu_uncut       -> Fill(thrust       , gHeader->GetWeight());
	fControlsphericity_is_hu_uncut   -> Fill(sphericity   , gHeader->GetWeight());
	fControlisotropy_is_hu_uncut     -> Fill(isotropy     , gHeader->GetWeight());
	fControlmultiplicity_is_hu_uncut -> Fill(multiplicity , gHeader->GetWeight());
	fControlQ2Prime_is_hl_uncut      -> Fill(Q2Prime      , gHeader->GetWeight()); 
      }
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  )  && !trimuon->GetDifCharge() ) {
	fControlthrust_is_hl_uncut       -> Fill(thrust       , gHeader->GetWeight());
	fControlsphericity_is_hl_uncut   -> Fill(sphericity   , gHeader->GetWeight()); 
	fControlisotropy_is_hl_uncut     -> Fill(isotropy     , gHeader->GetWeight()); 
	fControlmultiplicity_is_hl_uncut -> Fill(multiplicity , gHeader->GetWeight());
	fControlQ2Prime_is_hl_uncut      -> Fill(Q2Prime      , gHeader->GetWeight());
      } 
    }
    else{
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) { 
	fControlthrust_nis_lu_uncut       -> Fill(thrust       , gHeader->GetWeight()); 
	fControlsphericity_nis_lu_uncut   -> Fill(sphericity   , gHeader->GetWeight()); 
	fControlisotropy_nis_lu_uncut     -> Fill(isotropy     , gHeader->GetWeight()); 
	fControlmultiplicity_nis_lu_uncut -> Fill(multiplicity , gHeader->GetWeight()); 
	fControlQ2Prime_nis_lu_uncut      -> Fill(Q2Prime      , gHeader->GetWeight()); 
      }
      if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {
	fControlthrust_nis_ll_uncut       -> Fill(thrust       , gHeader->GetWeight());
	fControlsphericity_nis_ll_uncut   -> Fill(sphericity   , gHeader->GetWeight()); 
	fControlisotropy_nis_ll_uncut     -> Fill(isotropy     , gHeader->GetWeight()); 
	fControlmultiplicity_nis_ll_uncut -> Fill(multiplicity , gHeader->GetWeight()); 
	fControlQ2Prime_nis_ll_uncut      -> Fill(Q2Prime      , gHeader->GetWeight());
      }
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  )  &&  trimuon->GetDifCharge() ) { 
	fControlthrust_nis_hu_uncut       -> Fill(thrust       , gHeader->GetWeight()); 
	fControlsphericity_nis_hu_uncut   -> Fill(sphericity   , gHeader->GetWeight()); 
	fControlisotropy_nis_hu_uncut     -> Fill(isotropy     , gHeader->GetWeight()); 
	fControlmultiplicity_nis_hu_uncut -> Fill(multiplicity , gHeader->GetWeight()); 
	fControlQ2Prime_nis_hu_uncut      -> Fill(Q2Prime      , gHeader->GetWeight()); 
      }
      if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  )  && !trimuon->GetDifCharge() ) { 
	fControlthrust_nis_hl_uncut       -> Fill(thrust       , gHeader->GetWeight()); 
	fControlsphericity_nis_hl_uncut   -> Fill(sphericity   , gHeader->GetWeight()); 
	fControlisotropy_nis_hl_uncut     -> Fill(isotropy     , gHeader->GetWeight()); 
	fControlmultiplicity_nis_hl_uncut -> Fill(multiplicity , gHeader->GetWeight()); 
	fControlQ2Prime_nis_hl_uncut      -> Fill(Q2Prime      , gHeader->GetWeight()); 
      }
    }
    
    if ( ( trimuon->GetType() == kGoodTriMuon ) || ( trimuon->GetType() == kChosenTriMuon ) ) {
    
      if ( trimuon->GetInvMassCut() ) {
	fControlGoodTriMuonMass->Fill(invMass1,gHeader->GetWeight());
	fControlGoodTriMuonMass->Fill(invMass2,gHeader->GetWeight());
	fControlGoodTriMuonMass->Fill(invMass3,gHeader->GetWeight());
      
	if( invMass1 <= 4 )  fControlGoodTriMuonMassLow->Fill(invMass1,gHeader->GetWeight());
        if( invMass2 <= 4 )  fControlGoodTriMuonMassLow->Fill(invMass2,gHeader->GetWeight());
        if( invMass3 <= 4 )  fControlGoodTriMuonMassLow->Fill(invMass3,gHeader->GetWeight());
	
	if( invMass1 > 4  )  fControlGoodTriMuonMassHigh->Fill(invMass1,gHeader->GetWeight());
        if( invMass2 > 4  )  fControlGoodTriMuonMassHigh->Fill(invMass2,gHeader->GetWeight());
        if( invMass3 > 4  )  fControlGoodTriMuonMassHigh->Fill(invMass3,gHeader->GetWeight());
      
	if( !trimuon->GetSqSumIsolationCut() ) {      
          if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodMass_lu_is->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodMass_lu_is->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodMass_lu_is->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodMass_ll_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodMass_ll_is->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodMass_ll_is->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodMass_hu_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodMass_hu_is->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodMass_hu_is->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodMass_hl_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodMass_hl_is->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodMass_hl_is->Fill(invMass3,gHeader->GetWeight());
	}						     			                      
	else{					     			                      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodMass_lu_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodMass_lu_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodMass_lu_nis->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodMass_ll_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodMass_ll_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodMass_ll_nis->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodMass_hu_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodMass_hu_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodMass_hu_nis->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodMass_hl_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodMass_hl_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodMass_hl_nis->Fill(invMass3,gHeader->GetWeight()); 
	}                                                 
      }

      if ( trimuon->GetDeltaRCut() ) {
	fControlGoodDeltaR->Fill(deltaR1,gHeader->GetWeight());
	fControlGoodDeltaR->Fill(deltaR2,gHeader->GetWeight());
	fControlGoodDeltaR->Fill(deltaR3,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
          if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_lu_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_lu_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_lu_is->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaR_ll_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaR_ll_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaR_ll_is->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_hu_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_hu_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_hu_is->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaR_hl_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaR_hl_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaR_hl_is->Fill(deltaR3,gHeader->GetWeight()); 
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_lu_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_lu_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_lu_nis->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaR_ll_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaR_ll_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaR_ll_nis->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_hu_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_hu_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaR_hu_nis->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaR_hl_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaR_hl_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaR_hl_nis->Fill(deltaR3,gHeader->GetWeight());
	}
      }

      if ( trimuon->GetDeltaPhiCut() ) {
	fControlGoodDeltaPhi->Fill( TMath::Abs(deltaPhi1) ,gHeader->GetWeight());
	fControlGoodDeltaPhi->Fill( TMath::Abs(deltaPhi2) ,gHeader->GetWeight());
	fControlGoodDeltaPhi->Fill( TMath::Abs(deltaPhi3) ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
     	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	}
      }

      fControlGoodDeltaEta->Fill(deltaEta1,gHeader->GetWeight());
      fControlGoodDeltaEta->Fill(deltaEta2,gHeader->GetWeight());
      fControlGoodDeltaEta->Fill(deltaEta2,gHeader->GetWeight());
      if ( trimuon->GetDeltaThetaCut() ){
	fControlGoodDeltaTheta->Fill(deltaTheta1,gHeader->GetWeight());
	fControlGoodDeltaTheta->Fill(deltaTheta2,gHeader->GetWeight());
	fControlGoodDeltaTheta->Fill(deltaTheta3,gHeader->GetWeight());
      }
      if ( trimuon->GetPtAsymetryCut() ) {
	fControlGoodPtAsymetry->Fill(ptAsymetry1,gHeader->GetWeight());
	fControlGoodPtAsymetry->Fill(ptAsymetry2,gHeader->GetWeight());
	fControlGoodPtAsymetry->Fill(ptAsymetry3,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_lu_is->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_lu_is->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_lu_is->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_ll_is->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_ll_is->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_ll_is->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hu_is->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hu_is->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hu_is->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hl_is->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hl_is->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hl_is->Fill(ptAsymetry3,gHeader->GetWeight()); 
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_lu_nis->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_lu_nis->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_lu_nis->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_ll_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_ll_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_ll_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hu_nis->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hu_nis->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hu_nis->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hl_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hl_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlGoodPtAsymetry_hl_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	}

	fControlGoodpt->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlGoodpt->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	fControlGoodpt->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodpt_lu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_lu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodpt_lu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_lu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodpt_lu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_lu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodpt_ll_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_ll_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );} 
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodpt_ll_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_ll_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodpt_ll_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_ll_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodpt_hu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodpt_hu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodpt_hu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodpt_hl_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hl_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodpt_hl_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hl_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodpt_hl_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hl_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	}
	else{
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodpt_lu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_lu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodpt_lu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_lu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodpt_lu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_lu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodpt_ll_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_ll_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodpt_ll_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_ll_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodpt_ll_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_ll_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodpt_hu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodpt_hu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodpt_hu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodpt_hl_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hl_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlGoodpt_hl_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hl_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlGoodpt_hl_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlGoodpt_hl_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	} 
      
	fControlGoodeta->Fill( trimuon->GetMuon1()->Eta() ,gHeader->GetWeight());
	fControlGoodeta->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight());
	fControlGoodeta->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodeta_lu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_lu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodeta_lu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_lu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodeta_lu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_lu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodeta_ll_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_ll_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodeta_ll_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_ll_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodeta_ll_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_ll_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodeta_hu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodeta_hu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodeta_hu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodeta_hl_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hl_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodeta_hl_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hl_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodeta_hl_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hl_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	}
	else{
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodeta_lu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_lu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodeta_lu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_lu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodeta_lu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_lu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodeta_ll_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_ll_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodeta_ll_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_ll_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodeta_ll_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_ll_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodeta_hu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodeta_hu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodeta_hu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodeta_hl_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hl_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlGoodeta_hl_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hl_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlGoodeta_hl_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlGoodeta_hl_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	}

	fControlGoodImpact2D->Fill( trimuon->GetMuon1()->GetImpactMuon2D() ,gHeader->GetWeight());
	fControlGoodImpact2D->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight());
	fControlGoodImpact2D->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );} 
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_is_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_is_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	}
	else{
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlGoodImpact2D_nis_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlGoodImpact2D_nis_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	}
	
	fControlGoodsqisol_10->Fill( IsolationSqSum10 ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
      	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge()) {fControlGoodsqisol_10_is_lu->Fill( IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge()) {fControlGoodsqisol_10_is_ll->Fill( IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) &&  trimuon->GetDifCharge()) {fControlGoodsqisol_10_is_hu->Fill( IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) && !trimuon->GetDifCharge()) {fControlGoodsqisol_10_is_hl->Fill( IsolationSqSum10,gHeader->GetWeight());}
	}	
	else{
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge()) {fControlGoodsqisol_10_nis_lu->Fill(IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge()) {fControlGoodsqisol_10_nis_ll->Fill(IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) &&  trimuon->GetDifCharge()) {fControlGoodsqisol_10_nis_hu->Fill(IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) && !trimuon->GetDifCharge()) {fControlGoodsqisol_10_nis_hl->Fill(IsolationSqSum10,gHeader->GetWeight());}
	}
      
	fControlGoodthrust       -> Fill(thrust,       gHeader->GetWeight());
        fControlGoodsphericity   -> Fill(sphericity,   gHeader->GetWeight());
        fControlGoodisotropy     -> Fill(isotropy,     gHeader->GetWeight());
        fControlGoodmultiplicity -> Fill(multiplicity, gHeader->GetWeight());
        fControlGoodQ2Prime      -> Fill(Q2Prime,      gHeader->GetWeight());
      
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge()) { 
	    fControlGoodthrust_is_lu       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_is_lu   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_is_lu     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_lu -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_lu      -> Fill(Q2Prime      , gHeader->GetWeight()); 
	  }
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge()) { 
	    fControlGoodthrust_is_ll       -> Fill(thrust       , gHeader->GetWeight());
	    fControlGoodsphericity_is_ll   -> Fill(sphericity   , gHeader->GetWeight());
	    fControlGoodisotropy_is_ll     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_ll -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_ll      -> Fill(Q2Prime      , gHeader->GetWeight()); 
	  }
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) &&  trimuon->GetDifCharge()) {
	    fControlGoodthrust_is_hu       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_is_hu   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_is_hu     -> Fill(isotropy     , gHeader->GetWeight());
	    fControlGoodmultiplicity_is_hu -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_hu      -> Fill(Q2Prime      , gHeader->GetWeight()); 
	  }
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) && !trimuon->GetDifCharge()) {
	    fControlGoodthrust_is_hl       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_is_hl   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_is_hl     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_hl -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_hl      -> Fill(Q2Prime      , gHeader->GetWeight()); 
	  } 
	}
	else{
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge()) { 
	    fControlGoodthrust_nis_lu       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_nis_lu   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_lu     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_lu -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_lu      -> Fill(Q2Prime      , gHeader->GetWeight());
	  }
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge()) { 
	    fControlGoodthrust_nis_ll       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_nis_ll   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_ll     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_ll -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_ll      -> Fill(Q2Prime      , gHeader->GetWeight());
	  }
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) &&  trimuon->GetDifCharge()) {  
	    fControlGoodthrust_nis_hu       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_nis_hu   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_hu     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_hu -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_hu      -> Fill(Q2Prime      , gHeader->GetWeight()); 
	  }
	  if( ( invMass1 > 4  && invMass2 > 4  && invMass3 > 4  ) && !trimuon->GetDifCharge()) {
	    fControlGoodthrust_nis_hl       -> Fill(thrust       , gHeader->GetWeight()); 
	    fControlGoodsphericity_nis_hl   -> Fill(sphericity   , gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_hl     -> Fill(isotropy     , gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_hl -> Fill(multiplicity , gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_hl      -> Fill(Q2Prime      , gHeader->GetWeight()); 
	  }
	}
      }
    }
    
    if ( trimuon->GetType() == kChosenTriMuon ) {

      if ( trimuon->GetInvMassCut() ) {
	fControlChosenTriMuonMass->Fill(invMass1,gHeader->GetWeight());
	fControlChosenTriMuonMass->Fill(invMass2,gHeader->GetWeight());
	fControlChosenTriMuonMass->Fill(invMass3,gHeader->GetWeight());

	if( invMass1 <= 4 ) fControlChosenTriMuonMassLow->Fill(invMass1,gHeader->GetWeight());
	if( invMass2 <= 4 ) fControlChosenTriMuonMassLow->Fill(invMass2,gHeader->GetWeight());
	if( invMass3 <= 4 ) fControlChosenTriMuonMassLow->Fill(invMass3,gHeader->GetWeight());
	
	if( invMass1 > 4 )  fControlChosenTriMuonMassHigh->Fill(invMass1,gHeader->GetWeight());
	if( invMass2 > 4 )  fControlChosenTriMuonMassHigh->Fill(invMass2,gHeader->GetWeight());
	if( invMass3 > 4 )  fControlChosenTriMuonMassHigh->Fill(invMass3,gHeader->GetWeight());
	
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenMass_lu_is->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenMass_lu_is->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenMass_lu_is->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlChosenMass_ll_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlChosenMass_ll_is->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlChosenMass_ll_is->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlChosenMass_hu_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlChosenMass_hu_is->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlChosenMass_hu_is->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlChosenMass_hl_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlChosenMass_hl_is->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlChosenMass_hl_is->Fill(invMass3,gHeader->GetWeight()); 
	}						      
	else{					      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenMass_lu_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenMass_lu_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenMass_lu_nis->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlChosenMass_ll_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlChosenMass_ll_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlChosenMass_ll_nis->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlChosenMass_hu_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlChosenMass_hu_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlChosenMass_hu_nis->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlChosenMass_hl_nis->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlChosenMass_hl_nis->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlChosenMass_hl_nis->Fill(invMass3,gHeader->GetWeight()); 
	}                                                 
      }

      if ( trimuon->GetDeltaRCut() ) {
	fControlChosenDeltaR->Fill(deltaR1,gHeader->GetWeight());
	fControlChosenDeltaR->Fill(deltaR2,gHeader->GetWeight());
	fControlChosenDeltaR->Fill(deltaR3,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_lu_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_lu_is->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_lu_is->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlChosenDeltaR_ll_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlChosenDeltaR_ll_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlChosenDeltaR_ll_is->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_hu_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_hu_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_hu_is->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlChosenDeltaR_hl_is->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlChosenDeltaR_hl_is->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlChosenDeltaR_hl_is->Fill(deltaR3,gHeader->GetWeight()); 
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_lu_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_lu_nis->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_lu_nis->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fControlChosenDeltaR_ll_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fControlChosenDeltaR_ll_nis->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fControlChosenDeltaR_ll_nis->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_hu_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_hu_nis->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fControlChosenDeltaR_hu_nis->Fill(deltaR3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) fControlChosenDeltaR_hl_nis->Fill(deltaR1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) fControlChosenDeltaR_hl_nis->Fill(deltaR2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) fControlChosenDeltaR_hl_nis->Fill(deltaR3,gHeader->GetWeight()); 
	}
      }

      if ( trimuon->GetDeltaPhiCut() ) {
	fControlChosenDeltaPhi->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	fControlChosenDeltaPhi->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	fControlChosenDeltaPhi->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if(invMass1 <= 4 &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 <= 4 &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight()); 
	  if(invMass3 <= 4 &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	  if(invMass1 <= 4 && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 <= 4 && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if(invMass3 <= 4 && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  if(invMass1 > 4  &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 > 4  &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight()); 
	  if(invMass3 > 4  &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	  if(invMass1 > 4  && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	  if(invMass2 > 4  && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if(invMass3 > 4  && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	}
	else{
	  if(invMass1 <= 4 &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 <= 4 &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight()); 
	  if(invMass3 <= 4 &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	  if(invMass1 <= 4 && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 <= 4 && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight()); 
	  if(invMass3 <= 4 && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
          if(invMass1 > 4  &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 > 4  &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  if(invMass3 > 4  &&  trimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  if(invMass1 > 4  && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight()); 
	  if(invMass2 > 4  && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight()); 
	  if(invMass3 > 4  && !trimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight()); 
	}
      }

      fControlChosenDeltaEta->Fill(deltaEta1,gHeader->GetWeight());
      fControlChosenDeltaEta->Fill(deltaEta2,gHeader->GetWeight());
      fControlChosenDeltaEta->Fill(deltaEta3,gHeader->GetWeight());

      if ( trimuon->GetDeltaThetaCut() ){
	fControlChosenDeltaTheta->Fill(deltaTheta1,gHeader->GetWeight());
	fControlChosenDeltaTheta->Fill(deltaTheta2,gHeader->GetWeight());
	fControlChosenDeltaTheta->Fill(deltaTheta3,gHeader->GetWeight());
      }
    
      if ( trimuon->GetPtAsymetryCut() ) {
	fControlChosenPtAsymetry->Fill(ptAsymetry1,gHeader->GetWeight());
	fControlChosenPtAsymetry->Fill(ptAsymetry2,gHeader->GetWeight());
	fControlChosenPtAsymetry->Fill(ptAsymetry3,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_lu_is->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_lu_is->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_lu_is->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_ll_is->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_ll_is->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_ll_is->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_hu_is->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_hu_is->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_hu_is->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_hl_is->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_hl_is->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_hl_is->Fill(ptAsymetry3,gHeader->GetWeight()); 
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_lu_nis->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_lu_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_lu_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_ll_nis->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_ll_nis->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_ll_nis->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_hu_nis->Fill(ptAsymetry1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_hu_nis->Fill(ptAsymetry2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge()) fControlChosenPtAsymetry_hu_nis->Fill(ptAsymetry3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_hl_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_hl_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge()) fControlChosenPtAsymetry_hl_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	}
      
	fControlChosenpt->Fill(trimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlChosenpt->Fill(trimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	fControlChosenpt->Fill(trimuon->GetMuon3()->Pt(),gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenpt_lu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_lu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenpt_lu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_lu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenpt_lu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_lu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenpt_ll_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_ll_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );} 
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenpt_ll_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_ll_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenpt_ll_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_ll_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenpt_hu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenpt_hu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenpt_hu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hu_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChosenpt_hl_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hl_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChosenpt_hl_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hl_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChosenpt_hl_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hl_is->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	}
	else{
	  if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenpt_lu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_lu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenpt_lu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_lu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenpt_lu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_lu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenpt_ll_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_ll_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenpt_ll_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_ll_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenpt_ll_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_ll_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenpt_hu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenpt_hu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenpt_hu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hu_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChosenpt_hl_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hl_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	  if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlChosenpt_hl_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hl_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	  if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlChosenpt_hl_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fControlChosenpt_hl_nis->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	} 
        
	fControlChoseneta->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControlChoseneta->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	fControlChoseneta->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlChoseneta_lu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_lu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlChoseneta_lu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_lu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlChoseneta_lu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_lu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlChoseneta_ll_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_ll_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlChoseneta_ll_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_ll_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlChoseneta_ll_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_ll_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlChoseneta_hu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlChoseneta_hu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlChoseneta_hu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hu_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChoseneta_hl_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hl_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChoseneta_hl_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hl_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChoseneta_hl_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hl_is->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlChoseneta_lu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_lu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlChoseneta_lu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_lu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlChoseneta_lu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_lu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlChoseneta_ll_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_ll_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlChoseneta_ll_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_ll_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlChoseneta_ll_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_ll_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlChoseneta_hu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlChoseneta_hu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlChoseneta_hu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hu_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChoseneta_hl_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hl_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlChoseneta_hl_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hl_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlChoseneta_hl_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fControlChoseneta_hl_nis->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	}
	  
	fControlChosenImpact2D->Fill( trimuon->GetMuon1()->GetImpactMuon2D() ,gHeader->GetWeight());
	fControlChosenImpact2D->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight());
	fControlChosenImpact2D->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );} 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_is_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_is_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  { fControlChosenImpact2D_nis_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fControlChosenImpact2D_nis_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	}
	  
	fControlChosensqisol_10->Fill( IsolationSqSum10 ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {fControlChosensqisol_10_is_lu->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {fControlChosensqisol_10_is_ll->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) {fControlChosensqisol_10_is_hu->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() ) {fControlChosensqisol_10_is_hl->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	}
	else{
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {fControlChosensqisol_10_nis_lu->Fill( IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {fControlChosensqisol_10_nis_ll->Fill( IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) {fControlChosensqisol_10_nis_hu->Fill( IsolationSqSum10,gHeader->GetWeight());}
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() ) {fControlChosensqisol_10_nis_hl->Fill( IsolationSqSum10,gHeader->GetWeight());}
	}
	  
	fControlChosenthrust       -> Fill( thrust,       gHeader->GetWeight());
        fControlChosensphericity   -> Fill( sphericity,   gHeader->GetWeight());
        fControlChosenisotropy     -> Fill( isotropy,     gHeader->GetWeight());
        fControlChosenmultiplicity -> Fill( multiplicity, gHeader->GetWeight());
        fControlChosenQ2Prime      -> Fill( Q2Prime,      gHeader->GetWeight());

	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fControlChosenthrust_is_lu->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_is_lu->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_is_lu->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_is_lu->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_is_lu->Fill( Q2Prime ,gHeader->GetWeight()); }
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fControlChosenthrust_is_ll->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_is_ll->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_is_ll->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_is_ll->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_is_ll->Fill( Q2Prime ,gHeader->GetWeight()); }
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fControlChosenthrust_is_hu->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_is_hu->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_is_hu->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_is_hu->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_is_hu->Fill( Q2Prime ,gHeader->GetWeight()); }
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fControlChosenthrust_is_hl->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_is_hl->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_is_hl->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_is_hl->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_is_hl->Fill( Q2Prime ,gHeader->GetWeight()); } 
	}
	else{
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fControlChosenthrust_nis_lu->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_nis_lu->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_nis_lu->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_nis_lu->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_nis_lu->Fill( Q2Prime ,gHeader->GetWeight()); }
	  if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fControlChosenthrust_nis_ll->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_nis_ll->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_nis_ll->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_nis_ll->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_nis_ll->Fill( Q2Prime ,gHeader->GetWeight()); }
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fControlChosenthrust_nis_hu->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_nis_hu->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_nis_hu->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_nis_hu->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_nis_hu->Fill( Q2Prime ,gHeader->GetWeight()); }
	  if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fControlChosenthrust_nis_hl->Fill( thrust ,gHeader->GetWeight()); fControlChosensphericity_nis_hl->Fill( sphericity ,gHeader->GetWeight()); fControlChosenisotropy_nis_hl->Fill( isotropy, gHeader->GetWeight()); fControlChosenmultiplicity_nis_hl->Fill( multiplicity ,gHeader->GetWeight()); fControlChosenQ2Prime_nis_hl->Fill( Q2Prime ,gHeader->GetWeight()); }
	}

      }
    }
  
  }
	  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::ObjectsFillGeneral(GTriMuon *trimuon) {
  //
  // fill general histograms with data by looping over internal array
  if( gDebug ) cout << endl << "GTriMuons::ObjectsFillGeneral() called" << endl << endl;
  
  if ( gCards->GetTRIMUONGeneral() ) {
    
    Double_t invMass1 = trimuon->GetInvMass1();
    Double_t invMass2 = trimuon->GetInvMass2();
    Double_t invMass3 = trimuon->GetInvMass3();
    // construct for likesign contribution
    // all cuts except diff charge cut
    // all in this if is the old 'ugly but stay' block - redo below for 'dbot-trimuon'
    // remember to ask for unlike sign in unlike sign distris.
    if ( (( trimuon->GetMuonsAllCuts() && !gCards->GetDoEfficiency() ) || ( trimuon->GetMuonsMVCuts() && gCards->GetDoEfficiency() ) ) &&
	 trimuon  -> GetInvMassCut()        &&
	 trimuon  -> GetDeltaRCut()         &&
	 (trimuon -> GetDeltaPhiCut() || trimuon->GetDeltaThetaCut() ) &&
	 trimuon  -> GetDeltaEtaCut()       &&
	 trimuon  -> GetPtAsymetryCut()     &&
	 trimuon  -> GetEtFractionHighCut() &&
	 trimuon  -> GetEtFractionLowCut()  &&
	 !trimuon -> GetDifChargeCut()      &&
	 gCards   -> GetTRIMUONDifCharge() ) {
      
      fGeneralTriMuonMass_LikeSign_uncut->Fill(invMass1);
      fGeneralTriMuonMass_LikeSign_uncut->Fill(invMass2);
      fGeneralTriMuonMass_LikeSign_uncut->Fill(invMass3);

      if( invMass1 <= 4 )  fGeneralTriMuonMassLow_LikeSign_uncut->Fill(invMass1);
      if( invMass2 <= 4 )  fGeneralTriMuonMassLow_LikeSign_uncut->Fill(invMass2);
      if( invMass3 <= 4 )  fGeneralTriMuonMassLow_LikeSign_uncut->Fill(invMass3);
      
      if( invMass1 > 4  )  fGeneralTriMuonMassHigh_LikeSign_uncut->Fill(invMass1);
      if( invMass2 > 4  )  fGeneralTriMuonMassHigh_LikeSign_uncut->Fill(invMass2);
      if( invMass3 > 4  )  fGeneralTriMuonMassHigh_LikeSign_uncut->Fill(invMass3);
      
      if ( gTrigger  -> GetAllCuts() &&
	   gVertex   -> GetAllCuts() && 
	   gSinistra -> GetAllCuts() && 
	   gCal      -> GetAllCuts() && 
	   gZufo     -> GetAllCuts() && 
	   gMuons    -> GetAllCuts() && 
	   gJets     -> GetAllCuts() &&
	   gTracks   -> GetAllCuts() &&
	   gMJMatchs -> GetAllCuts() ) {

	fGeneralTriMuonMass_LikeSign->Fill(invMass1);
	fGeneralTriMuonMass_LikeSign->Fill(invMass2);
	fGeneralTriMuonMass_LikeSign->Fill(invMass3);

	if( invMass1 <= 4 )  fGeneralTriMuonMassLow_LikeSign->Fill(invMass1);
	if( invMass2 <= 4 )  fGeneralTriMuonMassLow_LikeSign->Fill(invMass2);
	if( invMass3 <= 4 )  fGeneralTriMuonMassLow_LikeSign->Fill(invMass3);
	
	if( invMass1 > 4  )  fGeneralTriMuonMassHigh_LikeSign->Fill(invMass1);
	if( invMass2 > 4  )  fGeneralTriMuonMassHigh_LikeSign->Fill(invMass2);
 	if( invMass3 > 4  )  fGeneralTriMuonMassHigh_LikeSign->Fill(invMass3);
	
      }
    }
    if( ( trimuon->GetMuonsAllCuts() && (trimuon->GetType() == kChosenTriMuon) 
	  || ( trimuon->GetMuonsMVCuts() && gCards->GetDoEfficiency() ) ) &&
	trimuon  -> GetInvMassCut()        &&
	trimuon  -> GetDeltaRCut()         &&
	(trimuon -> GetDeltaPhiCut() || trimuon->GetDeltaThetaCut() ) &&
	trimuon  -> GetDeltaEtaCut()       &&
	trimuon  -> GetPtAsymetryCut()     &&
	trimuon  -> GetEtFractionHighCut() &&
	trimuon  -> GetEtFractionLowCut()  &&
	!trimuon -> GetDifCharge()         &&
	!gCards  -> GetTRIMUONDifCharge() ) {

      fGeneralTriMuonMass_LikeSign_uncut->Fill(invMass1);
      fGeneralTriMuonMass_LikeSign_uncut->Fill(invMass2);
      fGeneralTriMuonMass_LikeSign_uncut->Fill(invMass3);

      if( invMass1 <= 4 ) fGeneralTriMuonMassLow_LikeSign_uncut->Fill(invMass1);
      if( invMass2 <= 4 ) fGeneralTriMuonMassLow_LikeSign_uncut->Fill(invMass2);
      if( invMass3 <= 4 ) fGeneralTriMuonMassLow_LikeSign_uncut->Fill(invMass3);
      
      if( invMass1 > 4 )  fGeneralTriMuonMassHigh_LikeSign_uncut->Fill(invMass1);
      if( invMass2 > 4 )  fGeneralTriMuonMassHigh_LikeSign_uncut->Fill(invMass2);
      if( invMass3 > 4 )  fGeneralTriMuonMassHigh_LikeSign_uncut->Fill(invMass3);
      
      if ( gTrigger  -> GetAllCuts() &&
	   gVertex   -> GetAllCuts() && 
	   gSinistra -> GetAllCuts() && 
	   gCal      -> GetAllCuts() && 
	   gZufo     -> GetAllCuts() && 
	   gMuons    -> GetAllCuts() && 
	   gJets     -> GetAllCuts() &&
	   gTracks   -> GetAllCuts() &&
	   gMJMatchs -> GetAllCuts() ) {

	fGeneralTriMuonMass_LikeSign->Fill(invMass1);
	fGeneralTriMuonMass_LikeSign->Fill(invMass2);
	fGeneralTriMuonMass_LikeSign->Fill(invMass3);

	if( invMass1 <= 4 )  fGeneralTriMuonMassLow_LikeSign->Fill(invMass1);
	if( invMass2 <= 4 )  fGeneralTriMuonMassLow_LikeSign->Fill(invMass2);
	if( invMass3 <= 4 )  fGeneralTriMuonMassLow_LikeSign->Fill(invMass3);
	
	if( invMass1 > 4  )  fGeneralTriMuonMassHigh_LikeSign->Fill(invMass1);
	if( invMass2 > 4  )  fGeneralTriMuonMassHigh_LikeSign->Fill(invMass2);
	if( invMass3 > 4  )  fGeneralTriMuonMassHigh_LikeSign->Fill(invMass3);
	
      }      
    }

    // dbot-trimuon block starts here 
    if ( trimuon->GetAllCuts() && (trimuon->GetType() == kChosenTriMuon) ) {
      
      Double_t deltaR1             = trimuon->GetDeltaR1();
      Double_t deltaR2             = trimuon->GetDeltaR2();
      Double_t deltaR3             = trimuon->GetDeltaR3();
      Double_t deltaPhi1           = trimuon->GetDeltaPhi1();
      Double_t deltaPhi2           = trimuon->GetDeltaPhi2();
      Double_t deltaPhi3           = trimuon->GetDeltaPhi3();
      Double_t deltaEta1           = trimuon->GetDeltaEta1();
      Double_t deltaEta2           = trimuon->GetDeltaEta2();
      Double_t deltaEta3           = trimuon->GetDeltaEta3();
      Double_t deltaTheta1         = trimuon->GetDeltaTheta1();
      Double_t deltaTheta2         = trimuon->GetDeltaTheta2();
      Double_t deltaTheta3         = trimuon->GetDeltaTheta3();
      Double_t ptAsymetry1         = trimuon->GetPtAsymetry1();
      Double_t ptAsymetry2         = trimuon->GetPtAsymetry2();
      Double_t ptAsymetry3         = trimuon->GetPtAsymetry3();
      Double_t IsolationSqSum10    = trimuon->GetIsolationSqSum10();
      Double_t Isolation_1_10      = 0;
      Double_t Isolation_2_10      = 0;
      Double_t Isolation_highpt_mu = 0;

      if(trimuon->GetMuon1()->GetIsolation10() > 0.) Isolation_1_10 = trimuon->GetMuon1()->GetIsolation10();
      if(trimuon->GetMuon2()->GetIsolation10() > 0.) Isolation_2_10 = trimuon->GetMuon2()->GetIsolation10();
      if(trimuon->GetMuon1()->GetIsolation10() > 0. && trimuon->GetMuon1()->Pt() > trimuon->GetMuon2()->Pt() ) Isolation_highpt_mu = trimuon->GetMuon1()->GetIsolation10();
      if(trimuon->GetMuon2()->GetIsolation10() > 0. && trimuon->GetMuon2()->Pt() > trimuon->GetMuon1()->Pt() ) Isolation_highpt_mu = trimuon->GetMuon2()->GetIsolation10();

      Double_t thrust             = gZufo->GetThrust();
      Double_t sphericity         = gZufo->GetSphericity();
      Double_t isotropy           = gZufo->GetIsotropy();
      Double_t multiplicity       = gZufo->GetMultiplicity();
      Double_t Q2Prime            = gZufo->GetQ2Prime();
      Double_t empz               = gZufo->GetEmpz_had();
      Double_t cal_et             = gData->Getcal_et();
      Double_t etex2ir            = gData->Getetex2ir();
      Double_t cal_et_m_et2ir     = (gData->Getcal_et() - gData->Getet2ir());
      Double_t cal_et_m_cal_et_10 = (gData->Getcal_et() - gData->Getcal_et10());

      fGeneralTriMuonMass_uncut->Fill(invMass1);
      fGeneralTriMuonMass_uncut->Fill(invMass2);
      fGeneralTriMuonMass_uncut->Fill(invMass3);

      if( invMass1 <= 4 ) fGeneralTriMuonMassLow_uncut->Fill(invMass1);
      if( invMass2 <= 4 ) fGeneralTriMuonMassLow_uncut->Fill(invMass2);
      if( invMass3 <= 4 ) fGeneralTriMuonMassLow_uncut->Fill(invMass3);
      
      if( invMass1 > 4 )  fGeneralTriMuonMassHigh_uncut->Fill(invMass1);
      if( invMass2 > 4 )  fGeneralTriMuonMassHigh_uncut->Fill(invMass2);
      if( invMass3 > 4 )  fGeneralTriMuonMassHigh_uncut->Fill(invMass3);
      
      if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	fGeneralTriMuonMass_UnlikeSign_uncut->Fill(invMass1);
	fGeneralTriMuonMass_UnlikeSign_uncut->Fill(invMass2);
	fGeneralTriMuonMass_UnlikeSign_uncut->Fill(invMass3);
      }


      if ( invMass1 <= 4 ){
	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMassLow_UnlikeSign_uncut->Fill(invMass1);
	}
      }
      if ( invMass2 <= 4 ){
	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMassLow_UnlikeSign_uncut->Fill(invMass2);;
	}
      }
      if ( invMass3 <= 4 ){
	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMassLow_UnlikeSign_uncut->Fill(invMass3);
	}
      }

      if ( invMass1 > 4 ){
	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMassHigh_UnlikeSign_uncut->Fill(invMass1);
	}
      }

      if ( invMass2 > 4 ){
	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMassHigh_UnlikeSign_uncut->Fill(invMass2);
	}
      }
      if ( invMass3 > 4 ){
	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMassHigh_UnlikeSign_uncut->Fill(invMass3);
	}
      }

      if( !trimuon->GetSqSumIsolationCut() ) {      
     	if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralMass_lu_is_uncut->Fill(invMass1,gHeader->GetWeight());
  	if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralMass_lu_is_uncut->Fill(invMass2,gHeader->GetWeight());
  	if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralMass_lu_is_uncut->Fill(invMass3,gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralMass_ll_is_uncut->Fill(invMass1,gHeader->GetWeight());
	if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralMass_ll_is_uncut->Fill(invMass2,gHeader->GetWeight());
	if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralMass_ll_is_uncut->Fill(invMass3,gHeader->GetWeight());
	if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralMass_hu_is_uncut->Fill(invMass1,gHeader->GetWeight()); 
	if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralMass_hu_is_uncut->Fill(invMass2,gHeader->GetWeight()); 
	if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralMass_hu_is_uncut->Fill(invMass3,gHeader->GetWeight()); 
	if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralMass_hl_is_uncut->Fill(invMass1,gHeader->GetWeight());
	if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralMass_hl_is_uncut->Fill(invMass2,gHeader->GetWeight());
	if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralMass_hl_is_uncut->Fill(invMass3,gHeader->GetWeight());
      }						      
      else{					      
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralMass_lu_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralMass_lu_nis_uncut->Fill(invMass2,gHeader->GetWeight()); 
	if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralMass_lu_nis_uncut->Fill(invMass3,gHeader->GetWeight()); 
	if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralMass_ll_nis_uncut->Fill(invMass1,gHeader->GetWeight());
	if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralMass_ll_nis_uncut->Fill(invMass2,gHeader->GetWeight());
	if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralMass_ll_nis_uncut->Fill(invMass3,gHeader->GetWeight());
	if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralMass_hu_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
	if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralMass_hu_nis_uncut->Fill(invMass2,gHeader->GetWeight()); 
	if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralMass_hu_nis_uncut->Fill(invMass3,gHeader->GetWeight()); 
	if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralMass_hl_nis_uncut->Fill(invMass1,gHeader->GetWeight()); 
	if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralMass_hl_nis_uncut->Fill(invMass2,gHeader->GetWeight()); 
	if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralMass_hl_nis_uncut->Fill(invMass3,gHeader->GetWeight()); 
      }                                                 

      fGeneralDeltaR_uncut->Fill(deltaR1,gHeader->GetWeight());
      fGeneralDeltaR_uncut->Fill(deltaR2,gHeader->GetWeight());
      fGeneralDeltaR_uncut->Fill(deltaR3,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_is_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_is_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_is_uncut->Fill(deltaR3,gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_is_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_is_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_is_uncut->Fill(deltaR3,gHeader->GetWeight());
	if( invMass1 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_is_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_is_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_is_uncut->Fill(deltaR3,gHeader->GetWeight());
	if( invMass1 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_is_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_is_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_is_uncut->Fill(deltaR3,gHeader->GetWeight());
      }
      else{
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_nis_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_nis_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_nis_uncut->Fill(deltaR3,gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_nis_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_nis_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_nis_uncut->Fill(deltaR3,gHeader->GetWeight());
	if( invMass1 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_nis_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_nis_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_nis_uncut->Fill(deltaR3,gHeader->GetWeight());
	if( invMass1 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_nis_uncut->Fill(deltaR1,gHeader->GetWeight());
	if( invMass2 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_nis_uncut->Fill(deltaR2,gHeader->GetWeight());
	if( invMass3 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_nis_uncut->Fill(deltaR3,gHeader->GetWeight());
      }
      
      fGeneralDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi1) ,gHeader->GetWeight());
      fGeneralDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi2) ,gHeader->GetWeight());
      fGeneralDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi3) ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
 	if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_is_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_is_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_is_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
      }
      else{
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_nis_uncut->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_nis_uncut->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_nis_uncut->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
      }

      fGeneralDeltaEta_uncut   -> Fill(deltaEta1,gHeader->GetWeight());
      fGeneralDeltaEta_uncut   -> Fill(deltaEta2,gHeader->GetWeight());
      fGeneralDeltaEta_uncut   -> Fill(deltaEta3,gHeader->GetWeight());
      fGeneralDeltaTheta_uncut -> Fill(deltaTheta1,gHeader->GetWeight());
      fGeneralDeltaTheta_uncut -> Fill(deltaTheta2,gHeader->GetWeight());
      fGeneralDeltaTheta_uncut -> Fill(deltaTheta3,gHeader->GetWeight());

      fGeneralPtAsymetry_uncut->Fill(ptAsymetry1,gHeader->GetWeight());
      fGeneralPtAsymetry_uncut->Fill(ptAsymetry2,gHeader->GetWeight());
      fGeneralPtAsymetry_uncut->Fill(ptAsymetry3,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_lu_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight());
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_lu_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight());
	if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_lu_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_ll_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
	if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_ll_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
	if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_ll_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
	if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_hu_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
	if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_hu_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
	if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_hu_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
	if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_hl_is_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
	if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_hl_is_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
	if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_hl_is_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      }
      else{
	if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_lu_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
	if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_lu_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight());
	if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_lu_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight());
	if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_ll_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
	if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_ll_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
	if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_ll_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
	if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_hu_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight());
	if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_hu_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight());
	if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralPtAsymetry_hu_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight());
	if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_hl_nis_uncut->Fill(ptAsymetry1,gHeader->GetWeight()); 
	if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_hl_nis_uncut->Fill(ptAsymetry2,gHeader->GetWeight()); 
	if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralPtAsymetry_hl_nis_uncut->Fill(ptAsymetry3,gHeader->GetWeight()); 
      }

      fGeneralpt_uncut->Fill( trimuon->GetMuon1()->Pt() ,gHeader->GetWeight());
      fGeneralpt_uncut->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight());
      fGeneralpt_uncut->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralpt_lu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_lu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralpt_lu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_lu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralpt_lu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_lu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralpt_ll_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_ll_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralpt_ll_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_ll_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralpt_ll_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_ll_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralpt_hu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralpt_hu_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralpt_hu_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_hu_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralpt_hl_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hl_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralpt_hl_is_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hl_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralpt_hl_is_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_hl_is_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      }
      else{
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralpt_lu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_lu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralpt_lu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_lu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralpt_lu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_lu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralpt_ll_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_ll_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralpt_ll_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_ll_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralpt_ll_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_ll_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralpt_hu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralpt_hu_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralpt_hu_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_hu_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralpt_hl_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hl_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() );}
	if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fGeneralpt_hl_nis_uncut->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight() ); fGeneralpt_hl_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
	if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fGeneralpt_hl_nis_uncut->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight() ); fGeneralpt_hl_nis_uncut->Fill( trimuon->GetMuon3()->Pt(),gHeader->GetWeight() );}
      }

      fGeneraleta_uncut->Fill( trimuon->GetMuon1()->Eta() ,gHeader->GetWeight());
      fGeneraleta_uncut->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight());
      fGeneraleta_uncut->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneraleta_lu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_lu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneraleta_lu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_lu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneraleta_lu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_lu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneraleta_ll_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_ll_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneraleta_ll_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_ll_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneraleta_ll_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_ll_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneraleta_hu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneraleta_hu_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneraleta_hu_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_hu_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneraleta_hl_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hl_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneraleta_hl_is_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hl_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneraleta_hl_is_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_hl_is_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      }
      else{
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneraleta_lu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_lu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneraleta_lu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_lu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneraleta_lu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_lu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneraleta_ll_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_ll_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneraleta_ll_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_ll_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneraleta_ll_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_ll_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneraleta_hu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneraleta_hu_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneraleta_hu_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_hu_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneraleta_hl_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hl_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() );}
	if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fGeneraleta_hl_nis_uncut->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight() ); fGeneraleta_hl_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
	if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fGeneraleta_hl_nis_uncut->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight() ); fGeneraleta_hl_nis_uncut->Fill( trimuon->GetMuon3()->Eta(),gHeader->GetWeight() );}
      }
 
      fGeneralImpact2D_uncut->Fill(trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
      fGeneralImpact2D_uncut->Fill(trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
      fGeneralImpact2D_uncut->Fill(trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_is_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_is_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_is_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralImpact2D_is_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralImpact2D_is_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralImpact2D_is_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralImpact2D_is_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralImpact2D_is_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralImpact2D_is_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_is_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      }
      else{
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_lu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_ll_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_hu_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
	if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fGeneralImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight() ); fGeneralImpact2D_nis_hl_uncut->Fill( trimuon->GetMuon3()->GetImpactMuon2D(),gHeader->GetWeight() );}
      }

      fGeneralphi_uncut->Fill( trimuon->GetMuon1()->Phi() ,gHeader->GetWeight());
      fGeneralphi_uncut->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight());
      fGeneralphi_uncut->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralphi_lu_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_lu_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralphi_lu_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_lu_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralphi_lu_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_lu_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralphi_ll_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_ll_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralphi_ll_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_ll_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralphi_ll_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_ll_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralphi_hu_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hu_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralphi_hu_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hu_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralphi_hu_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_hu_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralphi_hl_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hl_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralphi_hl_is_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hl_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralphi_hl_is_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_hl_is_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
      }
      else{
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralphi_lu_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_lu_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralphi_lu_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_lu_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralphi_lu_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_lu_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralphi_ll_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_ll_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralphi_ll_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_ll_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralphi_ll_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_ll_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralphi_hu_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hu_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralphi_hu_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hu_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralphi_hu_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_hu_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralphi_hl_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hl_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() );}
	if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fGeneralphi_hl_nis_uncut->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight() ); fGeneralphi_hl_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
	if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fGeneralphi_hl_nis_uncut->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight() ); fGeneralphi_hl_nis_uncut->Fill( trimuon->GetMuon3()->Phi(),gHeader->GetWeight() );}
      }

      fGeneralmuqual_uncut->Fill( trimuon->GetMuon1()->GetQuality() ,gHeader->GetWeight());
      fGeneralmuqual_uncut->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight());
      fGeneralmuqual_uncut->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralmuqual_lu_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_lu_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralmuqual_lu_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_lu_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralmuqual_lu_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_lu_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralmuqual_ll_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_ll_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralmuqual_ll_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_ll_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralmuqual_ll_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_ll_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralmuqual_hu_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hu_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralmuqual_hu_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hu_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralmuqual_hu_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hu_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralmuqual_hl_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hl_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralmuqual_hl_is_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hl_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralmuqual_hl_is_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hl_is_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
      }
      else{
	if ( invMass1 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralmuqual_lu_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_lu_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralmuqual_lu_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_lu_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 &&  trimuon->GetDifCharge() )  { fGeneralmuqual_lu_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_lu_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 <= 4 && !trimuon->GetDifCharge() )  { fGeneralmuqual_ll_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_ll_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 <= 4 && !trimuon->GetDifCharge() )  { fGeneralmuqual_ll_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_ll_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 <= 4 && !trimuon->GetDifCharge() )  { fGeneralmuqual_ll_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_ll_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 > 4  &&  trimuon->GetDifCharge() )  { fGeneralmuqual_hu_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hu_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 > 4  &&  trimuon->GetDifCharge() )  { fGeneralmuqual_hu_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hu_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 > 4  &&  trimuon->GetDifCharge() )  { fGeneralmuqual_hu_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hu_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass1 > 4  && !trimuon->GetDifCharge() )  { fGeneralmuqual_hl_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hl_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass2 > 4  && !trimuon->GetDifCharge() )  { fGeneralmuqual_hl_nis_uncut->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hl_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
	if ( invMass3 > 4  && !trimuon->GetDifCharge() )  { fGeneralmuqual_hl_nis_uncut->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight() ); fGeneralmuqual_hl_nis_uncut->Fill( trimuon->GetMuon3()->GetQuality(),gHeader->GetWeight() );}
      }

      fGeneralsqisol_10_uncut->Fill( IsolationSqSum10 ,gHeader->GetWeight());
          if( !trimuon->GetSqSumIsolationCut() ) {      
	    if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {fGeneralsqisol_10_is_lu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	    if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {fGeneralsqisol_10_is_ll_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	    if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) {fGeneralsqisol_10_is_hu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	    if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() ) {fGeneralsqisol_10_is_hl_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
      }
      else{
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {fGeneralsqisol_10_nis_lu_uncut->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {fGeneralsqisol_10_nis_ll_uncut->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) {fGeneralsqisol_10_nis_hu_uncut->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() ) {fGeneralsqisol_10_nis_hl_uncut->Fill( IsolationSqSum10 ,gHeader->GetWeight());}
      }

      fGeneralthrust_uncut       -> Fill( thrust,       gHeader->GetWeight());
      fGeneralsphericity_uncut   -> Fill( sphericity,   gHeader->GetWeight());
      fGeneralisotropy_uncut     -> Fill( isotropy,     gHeader->GetWeight());
      fGeneralmultiplicity_uncut -> Fill( multiplicity, gHeader->GetWeight());
      fGeneralQ2Prime_uncut      -> Fill( Q2Prime,      gHeader->GetWeight());

      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralthrust_is_lu_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_lu_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_lu_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_is_lu_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_lu_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneralthrust_is_ll_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_ll_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_ll_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_is_ll_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_ll_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralthrust_is_hu_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_hu_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_hu_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_is_hu_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_hu_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralthrust_is_hl_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_hl_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_hl_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_is_hl_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_hl_uncut->Fill( Q2Prime ,gHeader->GetWeight()); } 
      }
      else{
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralthrust_nis_lu_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_lu_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_lu_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_nis_lu_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_lu_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneralthrust_nis_ll_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_ll_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_ll_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_nis_ll_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_ll_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralthrust_nis_hu_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_hu_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_hu_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_nis_hu_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_hu_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralthrust_nis_hl_uncut->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_hl_uncut->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_hl_uncut->Fill( isotropy ,gHeader->GetWeight()); fGeneralmultiplicity_nis_hl_uncut->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_hl_uncut->Fill( Q2Prime ,gHeader->GetWeight()); }
      }

      fGeneralcal_et_uncut->Fill( cal_et ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_is_lu_uncut->Fill( cal_et ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_is_ll_uncut->Fill( cal_et ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_is_hu_uncut->Fill( cal_et ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_is_hl_uncut->Fill( cal_et ,gHeader->GetWeight()); } 
      }
      else{
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_lu_uncut->Fill( cal_et ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_ll_uncut->Fill( cal_et ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_hu_uncut->Fill( cal_et ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_hl_uncut->Fill( cal_et ,gHeader->GetWeight()); }
      }

      fGeneraletex2ir_uncut->Fill( etex2ir ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_lu_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_ll_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_hu_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_hl_uncut->Fill( etex2ir ,gHeader->GetWeight()); } 
      }
      else{
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_lu_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_ll_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_hu_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_hl_uncut->Fill( etex2ir ,gHeader->GetWeight()); }
      }

      fGeneralcal_et_m_et2ir_uncut->Fill( cal_et_m_et2ir ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_is_lu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_is_ll_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_is_hu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_is_hl_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());} 
      }
      else{
	if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_nis_lu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_nis_ll_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_nis_hu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() ) {fGeneralcal_et_m_et2ir_nis_hl_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
      }

      fGeneralcal_et_m_cal_et_10_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight());
      if( !trimuon->GetSqSumIsolationCut() ) {      
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_lu_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_ll_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_hu_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_hl_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); } 
      }
      else{
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_lu_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_ll_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_hu_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_hl_uncut->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
      }

      if( gCards->GetDoEfficiency() ) {
	if ( trimuon->GetTriggerType() == kTakeTriNone )
	  fGeneralTriggerType_uncut->Fill("None",1);
	else if ( trimuon->GetTriggerType() == kTakeTriMuon1 )
	  fGeneralTriggerType_uncut->Fill("Muon1",1);
	else if ( trimuon->GetTriggerType() == kTakeTriMuon2 )
	  fGeneralTriggerType_uncut->Fill("Muon2",1);
	else if ( trimuon->GetTriggerType() == kTakeAll )
	  fGeneralTriggerType_uncut->Fill("Both",1);
	else if ( trimuon->GetTriggerType() == kTakeTriMuon3 )
	  fGeneralTriggerType_uncut->Fill("Muon3",1);
      }

      if ( gHeader->GetAllCuts() ) {

	fGeneralTriMuonMass->Fill(invMass1);
	fGeneralTriMuonMass->Fill(invMass2);
	fGeneralTriMuonMass->Fill(invMass3);

	if( invMass1 <= 4 )  fGeneralTriMuonMassLow->Fill(invMass1);
	if( invMass2 <= 4 )  fGeneralTriMuonMassLow->Fill(invMass2);
	if( invMass3 <= 4 )  fGeneralTriMuonMassLow->Fill(invMass3);


	if( invMass1 > 4  )  fGeneralTriMuonMassHigh->Fill(invMass1);
	if( invMass2 > 4  )  fGeneralTriMuonMassHigh->Fill(invMass2);
	if( invMass3 > 4  )  fGeneralTriMuonMassHigh->Fill(invMass3);


	if ( trimuon->GetDifCharge() ){ // enter this before allll unlike signs!
	  fGeneralTriMuonMass_UnlikeSign->Fill(invMass1);
	  fGeneralTriMuonMass_UnlikeSign->Fill(invMass2);
	  fGeneralTriMuonMass_UnlikeSign->Fill(invMass3);
	}
	if( invMass1 <= 4 ){
	  if ( trimuon->GetDifCharge() ) // enter this before allll unlike signs!
	    fGeneralTriMuonMassLow_UnlikeSign->Fill(invMass1);
	}
	if( invMass2 <= 4 ){
	  if ( trimuon->GetDifCharge() ) // enter this before allll unlike signs!
	    fGeneralTriMuonMassLow_UnlikeSign->Fill(invMass2);
	}
	if( invMass3 <= 4 ){
	  if ( trimuon->GetDifCharge() ) // enter this before allll unlike signs!
	    fGeneralTriMuonMassLow_UnlikeSign->Fill(invMass3);
	}

	if ( invMass1 > 4 ){
	  if ( trimuon->GetDifCharge() ) // enter this before allll unlike signs!
	    fGeneralTriMuonMassHigh_UnlikeSign->Fill(invMass1);
	}
	if ( invMass2 > 4 ){
	  if ( trimuon->GetDifCharge() ) // enter this before allll unlike signs!
	    fGeneralTriMuonMassHigh_UnlikeSign->Fill(invMass2);
	}
	if ( invMass3 > 4 ){
	  if ( trimuon->GetDifCharge() ) // enter this before allll unlike signs!
	    fGeneralTriMuonMassHigh_UnlikeSign->Fill(invMass3);
	}

	if( !trimuon->GetSqSumIsolationCut() ) {       
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  fGeneralMass_lu_is->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  fGeneralMass_lu_is->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  fGeneralMass_lu_is->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  fGeneralMass_ll_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  fGeneralMass_ll_is->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  fGeneralMass_ll_is->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  fGeneralMass_hu_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  fGeneralMass_hu_is->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  fGeneralMass_hu_is->Fill(invMass3,gHeader->GetWeight()); 
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  fGeneralMass_hl_is->Fill(invMass1,gHeader->GetWeight()); 
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  fGeneralMass_hl_is->Fill(invMass2,gHeader->GetWeight()); 
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  fGeneralMass_hl_is->Fill(invMass3,gHeader->GetWeight()); 
	}						      
	else{					      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  fGeneralMass_lu_nis->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  fGeneralMass_lu_nis->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  fGeneralMass_lu_nis->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  fGeneralMass_ll_nis->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  fGeneralMass_ll_nis->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  fGeneralMass_ll_nis->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  fGeneralMass_hu_nis->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  fGeneralMass_hu_nis->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  fGeneralMass_hu_nis->Fill(invMass3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  fGeneralMass_hl_nis->Fill(invMass1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  fGeneralMass_hl_nis->Fill(invMass2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  fGeneralMass_hl_nis->Fill(invMass3,gHeader->GetWeight());
	}          

	fGeneralDeltaR->Fill(deltaR1,gHeader->GetWeight());
	fGeneralDeltaR->Fill(deltaR2,gHeader->GetWeight());
	fGeneralDeltaR->Fill(deltaR3,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_is->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_is->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_is->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_is->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_is->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_is->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_is->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_is->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_is->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_is->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_is->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_is->Fill(deltaR3,gHeader->GetWeight());
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_nis->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )  fGeneralDeltaR_lu_nis->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_nis->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )  fGeneralDeltaR_ll_nis->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_nis->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )  fGeneralDeltaR_hu_nis->Fill(deltaR3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_nis->Fill(deltaR1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_nis->Fill(deltaR2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )  fGeneralDeltaR_hl_nis->Fill(deltaR3,gHeader->GetWeight());
	}
	
	if( invMass1 > 3.25 && invMass2 > 3.25 && invMass3 > 3.25 ) {
	  fGeneralDeltaPhi->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	  fGeneralDeltaPhi->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	  fGeneralDeltaPhi->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  if( !trimuon->GetSqSumIsolationCut() ) {     
	    if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	    if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	    if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	    if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_is->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  }
	  else{
	    if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_lu_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	    if( invMass1 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 <= 4 && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_ll_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	    if( invMass1 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 > 4  &&  trimuon->GetDifCharge() ) fGeneralDeltaPhi_hu_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	    if( invMass1 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi1),gHeader->GetWeight());
	    if( invMass2 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi2),gHeader->GetWeight());
	    if( invMass3 > 4  && !trimuon->GetDifCharge() ) fGeneralDeltaPhi_hl_nis->Fill(TMath::Abs(deltaPhi3),gHeader->GetWeight());
	  }
	}

	fGeneralDeltaEta->Fill(deltaEta1,gHeader->GetWeight());
	fGeneralDeltaEta->Fill(deltaEta2,gHeader->GetWeight());
	fGeneralDeltaEta->Fill(deltaEta3,gHeader->GetWeight());

	fGeneralDeltaTheta->Fill(deltaTheta1,gHeader->GetWeight());
	fGeneralDeltaTheta->Fill(deltaTheta2,gHeader->GetWeight());
	fGeneralDeltaTheta->Fill(deltaTheta3,gHeader->GetWeight());

	fGeneralPtAsymetry->Fill(ptAsymetry1,gHeader->GetWeight());
	fGeneralPtAsymetry->Fill(ptAsymetry2,gHeader->GetWeight());
	fGeneralPtAsymetry->Fill(ptAsymetry3,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_lu_is->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_lu_is->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_lu_is->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_ll_is->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_ll_is->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_ll_is->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_hu_is->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_hu_is->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_hu_is->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_hl_is->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_hl_is->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_hl_is->Fill(ptAsymetry3,gHeader->GetWeight());
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_lu_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_lu_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_lu_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_ll_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_ll_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_ll_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_hu_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_hu_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() )   fGeneralPtAsymetry_hu_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	  if( invMass1 > 4  && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_hl_nis->Fill(ptAsymetry1,gHeader->GetWeight());
	  if( invMass2 > 4  && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_hl_nis->Fill(ptAsymetry2,gHeader->GetWeight());
	  if( invMass3 > 4  && !trimuon->GetDifCharge() )   fGeneralPtAsymetry_hl_nis->Fill(ptAsymetry3,gHeader->GetWeight());
	}
	
	fGeneralpt->Fill( trimuon->GetMuon1()->Pt() ,gHeader->GetWeight());
	fGeneralpt->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight());
	fGeneralpt->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralpt_lu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_lu_is->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralpt_lu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_lu_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralpt_lu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_lu_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralpt_ll_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_ll_is->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralpt_ll_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_ll_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralpt_ll_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_ll_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralpt_hu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hu_is->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralpt_hu_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hu_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralpt_hu_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_hu_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralpt_hl_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hl_is->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralpt_hl_is->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hl_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralpt_hl_is->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_hl_is->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralpt_lu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_lu_nis->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralpt_lu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_lu_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralpt_lu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_lu_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralpt_ll_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_ll_nis->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralpt_ll_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_ll_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralpt_ll_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_ll_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralpt_hu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hu_nis->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralpt_hu_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hu_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralpt_hu_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_hu_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralpt_hl_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hl_nis->Fill( trimuon->GetMuon2()->Pt() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralpt_hl_nis->Fill( trimuon->GetMuon1()->Pt(),gHeader->GetWeight()); fGeneralpt_hl_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralpt_hl_nis->Fill( trimuon->GetMuon2()->Pt(),gHeader->GetWeight()); fGeneralpt_hl_nis->Fill( trimuon->GetMuon3()->Pt() ,gHeader->GetWeight() );}
	}

	fGeneraleta->Fill( trimuon->GetMuon1()->Eta() ,gHeader->GetWeight());
	fGeneraleta->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight());
	fGeneraleta->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneraleta_lu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_lu_is->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneraleta_lu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_lu_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneraleta_lu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_lu_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneraleta_ll_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_ll_is->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneraleta_ll_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_ll_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneraleta_ll_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_ll_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneraleta_hu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hu_is->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneraleta_hu_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hu_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneraleta_hu_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_hu_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneraleta_hl_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hl_is->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneraleta_hl_is->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hl_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneraleta_hl_is->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_hl_is->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneraleta_lu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_lu_nis->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneraleta_lu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_lu_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneraleta_lu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_lu_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneraleta_ll_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_ll_nis->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneraleta_ll_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_ll_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneraleta_ll_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_ll_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneraleta_hu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hu_nis->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneraleta_hu_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hu_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneraleta_hu_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_hu_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneraleta_hl_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hl_nis->Fill( trimuon->GetMuon2()->Eta() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneraleta_hl_nis->Fill( trimuon->GetMuon1()->Eta(),gHeader->GetWeight()); fGeneraleta_hl_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneraleta_hl_nis->Fill( trimuon->GetMuon2()->Eta(),gHeader->GetWeight()); fGeneraleta_hl_nis->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	}

	fGeneralImpact2D->Fill( trimuon->GetMuon1()->GetImpactMuon2D() ,gHeader->GetWeight());
	fGeneralImpact2D->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight());
	fGeneralImpact2D->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_is_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_is_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_is_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralImpact2D_is_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralImpact2D_is_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralImpact2D_is_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_is_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_is_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_is_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralImpact2D_is_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralImpact2D_is_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralImpact2D_is_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_is_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_lu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_lu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_lu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_ll->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_ll->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_ll->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_hu->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_hu->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_hu->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_hl->Fill( trimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_hl->Fill( trimuon->GetMuon3()->GetImpactMuon2D() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralImpact2D_nis_hl->Fill( trimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); fGeneralImpact2D_nis_hl->Fill( trimuon->GetMuon3()->Eta() ,gHeader->GetWeight() );}
	}

	fGeneralphi->Fill( trimuon->GetMuon1()->Phi() ,gHeader->GetWeight());
	fGeneralphi->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight());
	fGeneralphi->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralphi_lu_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_lu_is->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralphi_lu_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_lu_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralphi_lu_is->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_lu_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralphi_ll_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_ll_is->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralphi_ll_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_ll_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralphi_ll_is->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_ll_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralphi_hu_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hu_is->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralphi_hu_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hu_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralphi_hu_is->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_hu_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralphi_hl_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hl_is->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralphi_hl_is->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hl_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralphi_hl_is->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_hl_is->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralphi_lu_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_lu_nis->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralphi_lu_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_lu_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralphi_lu_nis->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_lu_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralphi_ll_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_ll_nis->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralphi_ll_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_ll_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralphi_ll_nis->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_ll_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralphi_hu_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hu_nis->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralphi_hu_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hu_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralphi_hu_nis->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_hu_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralphi_hl_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hl_nis->Fill( trimuon->GetMuon2()->Phi() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralphi_hl_nis->Fill( trimuon->GetMuon1()->Phi(),gHeader->GetWeight()); fGeneralphi_hl_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralphi_hl_nis->Fill( trimuon->GetMuon2()->Phi(),gHeader->GetWeight()); fGeneralphi_hl_nis->Fill( trimuon->GetMuon3()->Phi() ,gHeader->GetWeight() );}
	}

	fGeneralmuqual->Fill( trimuon->GetMuon1()->GetQuality() ,gHeader->GetWeight());
	fGeneralmuqual->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight());
	fGeneralmuqual->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralmuqual_lu_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_lu_is->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralmuqual_lu_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_lu_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralmuqual_lu_is->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_lu_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralmuqual_ll_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_ll_is->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralmuqual_ll_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_ll_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralmuqual_ll_is->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_ll_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralmuqual_hu_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hu_is->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralmuqual_hu_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hu_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralmuqual_hu_is->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hu_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralmuqual_hl_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hl_is->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralmuqual_hl_is->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hl_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralmuqual_hl_is->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hl_is->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	}
	else{
	  if( invMass1 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralmuqual_lu_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_lu_nis->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralmuqual_lu_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_lu_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 &&  trimuon->GetDifCharge() ) {fGeneralmuqual_lu_nis->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_lu_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass1 <= 4 && !trimuon->GetDifCharge() ) {fGeneralmuqual_ll_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_ll_nis->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 <= 4 && !trimuon->GetDifCharge() ) {fGeneralmuqual_ll_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_ll_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 <= 4 && !trimuon->GetDifCharge() ) {fGeneralmuqual_ll_nis->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_ll_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  &&  trimuon->GetDifCharge() ) {fGeneralmuqual_hu_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hu_nis->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  &&  trimuon->GetDifCharge() ) {fGeneralmuqual_hu_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hu_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  &&  trimuon->GetDifCharge() ) {fGeneralmuqual_hu_nis->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hu_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass1 > 4  && !trimuon->GetDifCharge() ) {fGeneralmuqual_hl_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hl_nis->Fill( trimuon->GetMuon2()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass2 > 4  && !trimuon->GetDifCharge() ) {fGeneralmuqual_hl_nis->Fill( trimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hl_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	  if( invMass3 > 4  && !trimuon->GetDifCharge() ) {fGeneralmuqual_hl_nis->Fill( trimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); fGeneralmuqual_hl_nis->Fill( trimuon->GetMuon3()->GetQuality() ,gHeader->GetWeight() );}
	}

	fGeneralsqisol_10->Fill( TMath::Log10(IsolationSqSum10) ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralsqisol_10_is_lu->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralsqisol_10_is_ll->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralsqisol_10_is_hu->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralsqisol_10_is_hl->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	}
	else{
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralsqisol_10_nis_lu->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralsqisol_10_nis_ll->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralsqisol_10_nis_hu->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralsqisol_10_nis_hl->Fill( IsolationSqSum10 ,gHeader->GetWeight()); }
	}	
	if( !(trimuon->GetMuon1()->GetMatched() || trimuon->GetMuon2()->GetMatched()) || 42 == 42 ){
	  fGeneralthrust->Fill( thrust ,gHeader->GetWeight());
          fGeneralsphericity->Fill( sphericity ,gHeader->GetWeight());
          fGeneralisotropy->Fill( isotropy, gHeader->GetWeight());
          fGeneralmultiplicity->Fill( multiplicity ,gHeader->GetWeight());
          fGeneralQ2Prime->Fill( Q2Prime ,gHeader->GetWeight());

	  if( !trimuon->GetSqSumIsolationCut() ) {      
	    if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralthrust_is_lu->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_lu->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_lu->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_is_lu->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_lu->Fill( Q2Prime ,gHeader->GetWeight()); }
	    if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralthrust_is_ll->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_ll->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_ll->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_is_ll->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_ll->Fill( Q2Prime ,gHeader->GetWeight()); }
	    if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralthrust_is_hu->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_hu->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_hu->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_is_hu->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_hu->Fill( Q2Prime ,gHeader->GetWeight()); }
	    if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralthrust_is_hl->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_is_hl->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_is_hl->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_is_hl->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_is_hl->Fill( Q2Prime ,gHeader->GetWeight()); } 
	  }
	  else{
	    if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralthrust_nis_lu->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_lu->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_lu->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_nis_lu->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_lu->Fill( Q2Prime ,gHeader->GetWeight()); }
	    if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralthrust_nis_ll->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_ll->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_ll->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_nis_ll->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_ll->Fill( Q2Prime ,gHeader->GetWeight()); }
	    if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralthrust_nis_hu->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_hu->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_hu->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_nis_hu->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_hu->Fill( Q2Prime ,gHeader->GetWeight()); }
	    if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralthrust_nis_hl->Fill( thrust ,gHeader->GetWeight()); fGeneralsphericity_nis_hl->Fill( sphericity ,gHeader->GetWeight()); fGeneralisotropy_nis_hl->Fill( isotropy, gHeader->GetWeight()); fGeneralmultiplicity_nis_hl->Fill( multiplicity ,gHeader->GetWeight()); fGeneralQ2Prime_nis_hl->Fill( Q2Prime ,gHeader->GetWeight()); }
	  }
	}

	fGeneralempz->Fill( empz ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralempz_is_lu->Fill( empz ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralempz_is_ll->Fill( empz ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralempz_is_hu->Fill( empz ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralempz_is_hl->Fill( empz ,gHeader->GetWeight()); } 
	}
	else{
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralempz_nis_lu->Fill( empz ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralempz_nis_ll->Fill( empz ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralempz_nis_hu->Fill( empz ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralempz_nis_hl->Fill( empz ,gHeader->GetWeight()); }
	}

	fGeneralcal_et->Fill( cal_et ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_is_lu->Fill( cal_et ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralcal_et_is_ll->Fill( cal_et ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_is_hu->Fill( cal_et ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_is_hl->Fill( cal_et ,gHeader->GetWeight()); } 
	}
	else{
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_lu->Fill( cal_et ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_ll->Fill( cal_et ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_hu->Fill( cal_et ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_nis_hl->Fill( cal_et ,gHeader->GetWeight()); }
	}
	
	fGeneraletex2ir->Fill( etex2ir ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
 	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_lu->Fill( etex2ir ,gHeader->GetWeight()); }
 	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_ll->Fill( etex2ir ,gHeader->GetWeight()); }
 	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_hu->Fill( etex2ir ,gHeader->GetWeight()); }
 	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_is_hl->Fill( etex2ir ,gHeader->GetWeight()); } 
 	}
 	else{
 	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_lu->Fill( etex2ir ,gHeader->GetWeight()); }
 	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_ll->Fill( etex2ir ,gHeader->GetWeight()); }
 	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_hu->Fill( etex2ir ,gHeader->GetWeight()); }
 	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneraletex2ir_nis_hl->Fill( etex2ir ,gHeader->GetWeight()); }
 	}


	fGeneralcal_et_m_et2ir->Fill( cal_et_m_et2ir ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_is_lu->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_is_ll->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_is_hu->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_is_hl->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); } 
	}
	else{
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_nis_lu->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_nis_ll->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_nis_hu->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {fGeneralcal_et_m_et2ir_nis_hl->Fill( cal_et_m_et2ir ,gHeader->GetWeight()); }
	}

	fGeneralcal_et_m_cal_et_10->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight());
	if( !trimuon->GetSqSumIsolationCut() ) {      
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_lu->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_ll->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_hu->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_is_hl->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); } 
	}
	else{
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_lu->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 <= 4 && invMass2 <= 4 && invMass3 <= 4 ) && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_ll->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  &&  trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_hu->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	  if ( ( invMass1 > 4 && invMass2 > 4 && invMass3 > 4 )  && !trimuon->GetDifCharge() )  {  fGeneralcal_et_m_cal_et_10_nis_hl->Fill( cal_et_m_cal_et_10 ,gHeader->GetWeight()); }
	}                                                    
      
      }
    }
   
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::CreateGeneral() {
  //
  // create general plots
  if ( gDebug ) cout << endl << "GTriMuons::CreateGeneral() called" << endl << endl;
  
  if ( gCards->GetTRIMUONGeneral() ) {

    Int_t    nperevbins       = 10;
    Double_t nperevlow        = 0.;
    Double_t nperevhigh       = 10.;

    Int_t    massbins         = 1050;
    Double_t masslow          = 0.;
    Double_t masshigh         = 35.;

    Int_t    masslowbins      = 50;
    Double_t masslowlow       = 1.5;
    Double_t masslowhigh      = 4.;

    Int_t    masshighbins     = 84;
    Double_t masshighlow      = 4.;
    Double_t masshighhigh     = 46.;

    Int_t    deltarbins       = 200;
    Double_t deltarlow        = 0.;
    Double_t deltarhigh       = 10.;
    Int_t    deltaphibins     = 20;
    Double_t deltaphilow      = 0.0;
    Double_t deltaphihigh     = TMath::Pi();
    Int_t    deltaetabins     =   400;
    Double_t deltaetalow      = -10.0;
    Double_t deltaetahigh     =  10.0;
    Int_t    deltathetabins   =    60;
    Double_t deltathetalow    =  -3.0;
    Double_t deltathetahigh   =   3.0;

    Int_t    ptasymetrybins   =   80;
    Double_t ptasymetrylow    = -0.2;
    Double_t ptasymetryhigh   =  1.4;
    Int_t    ptbins           = 100;
    Double_t ptlow            =  0.0;
    Double_t pthigh           = 25.0;

    Int_t    etabins          =  160;
    Double_t etalow           = -4.0;
    Double_t etahigh          =  4.0;

    Int_t    phibins          = 360;
    Double_t philow           = -TMath::Pi();
    Double_t phihigh          =  TMath::Pi();
    Int_t    muqualbins       =    11;
    Double_t muquallow        =  -4.0;
    Double_t muqualhigh       =   7.0;

    Int_t    sqisol_10bins    =   400;
    Double_t sqisol_10low     =   0.0;
    Double_t sqisol_10high    =   1.0;

    Int_t    thrustbins       =    50;
    Double_t thrustlow        =   0.0;
    Double_t thrusthigh       =   1.0;
    Int_t    sphericitybins   =    50;
    Double_t sphericitylow    =   0.0;
    Double_t sphericityhigh   =   1.0;
    Int_t    multiplicitybins =    50;
    Double_t multiplicitylow  =   0.0;
    Double_t multiplicityhigh = 100.0;
    Int_t    isotropybins     =    50;
    Double_t isotropylow      =   0.0;
    Double_t isotropyhigh     =   1.0;
    Int_t    q2primebins      =   100; 
    Double_t q2primelow       =   0.0;
    Double_t q2primehigh      = 500.0;
    Int_t    impactbins       =   100;
    Double_t impactlow        =   0.0;
    Double_t impacthigh       =   1.0; 

    Int_t    empzbins         =    60;
    Double_t empzlow          =   0.0;
    Double_t empzhigh         =  60.0;
    Int_t    cal_etbins       =   200;
    Double_t cal_etlow        =   0.0;
    Double_t cal_ethigh       = 100.0;
    Int_t    etex2irbins      =     1;
    Double_t etex2irlow       =   0.0;
    Double_t etex2irhigh      = 100.0;
 
    Int_t    cal_et_m_et2irbins = 200;
    Double_t cal_et_m_et2irlow  = 0.;
    Double_t cal_et_m_et2irhigh = 100.;
    Int_t    cal_et_m_cal_et_10bins = 200;
    Double_t cal_et_m_cal_et_10low  = 0.;
    Double_t cal_et_m_cal_et_10high = 100.;


    TString triggertype = "None,Muon1,Muon2,Muon3,Both";
      
    fGeneralNperEv_uncut = gHistogrammer->TH1DFactory("TriMuon","NperEv_uncut","uncut n_{#mu#mu#mu}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu#mu}","Events");
    fGeneralTriMuonMass_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMass_uncut","uncut #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassLow_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassLow_uncut","uncut low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassHigh_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassHigh_uncut","uncut high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMass_LikeSign_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMass_LikeSign_uncut","uncut #mu#mu invariant mass for like-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassLow_LikeSign_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassLow_LikeSign_uncut","uncut low #mu#mu invariant mass for like-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassHigh_LikeSign_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassHigh_LikeSign_uncut","uncut high #mu#mu invariant mass for like-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMass_UnlikeSign_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMass_UnlikeSign_uncut","uncut #mu#mu invariant mass for unlike-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassLow_UnlikeSign_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassLow_UnlikeSign_uncut","uncut low #mu#mu invariant mass for unlike-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassHigh_UnlikeSign_uncut = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassHigh_UnlikeSign_uncut","uncut high #mu#mu invariant mass for unlike-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralMass_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_lu_is_uncut","good #mass_lu_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_ll_is_uncut","good #mass_ll_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_hu_is_uncut","good #mass_hu_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_hl_is_uncut","good #mass_hl_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_lu_nis_uncut","good #mass_lu_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_ll_nis_uncut","good #mass_ll_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_hu_nis_uncut","good #mass_hu_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","Mass_hl_nis_uncut","good #mass_hl_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralDeltaR_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_uncut","uncut #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR","Events");
    fGeneralDeltaR_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_lu_is_uncut","uncut #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_is","Events");
    fGeneralDeltaR_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_ll_is_uncut","uncut #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_is","Events");
    fGeneralDeltaR_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hu_is_uncut","uncut #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_is","Events");
    fGeneralDeltaR_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hl_is_uncut","uncut #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_is","Events");
    fGeneralDeltaR_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_lu_nis_uncut","uncut #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_nis","Events");
    fGeneralDeltaR_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_ll_nis_uncut","uncut #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_nis","Events");
    fGeneralDeltaR_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hu_nis_uncut","uncut #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_nis","Events");
    fGeneralDeltaR_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hl_nis_uncut","uncut #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_nis","Events");
    fGeneralDeltaPhi_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_uncut","uncut #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","Events");
    fGeneralDeltaPhi_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_lu_is_uncut","uncut #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_is","Events");
    fGeneralDeltaPhi_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_ll_is_uncut","uncut #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_is","Events");
    fGeneralDeltaPhi_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hu_is_uncut","uncut #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_is","Events");
    fGeneralDeltaPhi_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hl_is_uncut","uncut #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_is","Events");
    fGeneralDeltaPhi_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_lu_nis_uncut","uncut #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_nis","Events");
    fGeneralDeltaPhi_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_ll_nis_uncut","uncut #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_nis","Events");
    fGeneralDeltaPhi_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hu_nis_uncut","uncut #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_nis","Events");
    fGeneralDeltaPhi_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hl_nis_uncut","uncut #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_nis","Events");
    fGeneralDeltaEta_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaEta_uncut","uncut #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta","Events");
    fGeneralDeltaTheta_uncut = gHistogrammer->TH1DFactory("TriMuon","DeltaTheta_uncut","uncut #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta","Events");
  
    fGeneralPtAsymetry_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_uncut","uncut p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.","Events");
    fGeneralPtAsymetry_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_lu_is_uncut","uncut p_{T}_lu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.","Events");
    fGeneralPtAsymetry_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_ll_is_uncut","uncut p_{T}_ll_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.","Events");
    fGeneralPtAsymetry_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hu_is_uncut","uncut p_{T}_hu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.","Events");
    fGeneralPtAsymetry_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hl_is_uncut","uncut p_{T}_hl_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.","Events");
    fGeneralPtAsymetry_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_lu_nis_uncut","uncut p_{T}_lu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.","Events");
    fGeneralPtAsymetry_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_ll_nis_uncut","uncut p_{T}_ll_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.","Events");
    fGeneralPtAsymetry_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hu_nis_uncut","uncut p_{T}_hu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.","Events");
    fGeneralPtAsymetry_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hl_nis_uncut","uncut p_{T}_hl_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.","Events");
    fGeneralpt_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_uncut","uncut p_{T} ",ptbins,ptlow,pthigh,"p_{T}","Events");
    fGeneralpt_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_lu_is_uncut","uncut #pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_is","Events");
    fGeneralpt_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_ll_is_uncut","uncut #pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_is","Events");
    fGeneralpt_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_hu_is_uncut","uncut #pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_is","Events");
    fGeneralpt_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_hl_is_uncut","uncut #pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_is","Events");
    fGeneralpt_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_lu_nis_uncut","uncut #pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_nis","Events");
    fGeneralpt_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_ll_nis_uncut","uncut #pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_nis","Events");
    fGeneralpt_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_hu_nis_uncut","uncut #pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_nis","Events");
    fGeneralpt_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","pt_hl_nis_uncut","uncut #pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_nis","Events");

    fGeneraleta_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_uncut","uncut #eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fGeneraleta_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_lu_is_uncut","uncut #eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}_lu_is","Events");
    fGeneraleta_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_ll_is_uncut","uncut #eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}_ll_is","Events");
    fGeneraleta_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_hu_is_uncut","uncut #eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}_hu_is","Events");
    fGeneraleta_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_hl_is_uncut","uncut #eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}_hl_is","Events");
    fGeneraleta_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_lu_nis_uncut","uncut #eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_lu_nis","Events");
    fGeneraleta_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_ll_nis_uncut","uncut #eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}_ll_nis","Events");
    fGeneraleta_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_hu_nis_uncut","uncut #eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hu_nis","Events");
    fGeneraleta_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","eta_hl_nis_uncut","uncut #eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hl_nis","Events");

    fGeneralImpact2D_uncut    = gHistogrammer->TH1DFactory("TriMuon","Impact2D_uncut","uncut Impact2D",impactbins,impactlow,impacthigh,"# Impact2D","Events");
    fGeneralImpact2D_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_lu_uncut","uncut_lu Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_lu","Events");
    fGeneralImpact2D_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_ll_uncut","uncut_ll Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_ll","Events");
    fGeneralImpact2D_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_hu_uncut","uncut_hu Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_hu","Events");
    fGeneralImpact2D_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_hl_uncut","uncut_hl Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_hl","Events");
    fGeneralImpact2D_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_lu_uncut","uncut_lu Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_lu","Events");
    fGeneralImpact2D_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_ll_uncut","uncut_ll Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_ll","Events");
    fGeneralImpact2D_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_hu_uncut","uncut_hu Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_hu","Events");
    fGeneralImpact2D_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_hl_uncut","uncut_hl Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_hl","Events");

    fGeneralphi_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_uncut","uncut #phi_{#mu} ",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralphi_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_lu_is_uncut","uncut #phi_{#mu}_lu_is ",phibins,philow,phihigh,"#phi_{#mu}_lu_is","Events");
    fGeneralphi_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_ll_is_uncut","uncut #phi_{#mu}_ll_is ",phibins,philow,phihigh,"#phi_{#mu}_ll_is","Events");
    fGeneralphi_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_hu_is_uncut","uncut #phi_{#mu}_hu_is ",phibins,philow,phihigh,"#phi_{#mu}_hu_is","Events");
    fGeneralphi_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_hl_is_uncut","uncut #phi_{#mu}_hl_is ",phibins,philow,phihigh,"#phi_{#mu}_hl_is","Events");
    fGeneralphi_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_lu_nis_uncut","uncut #phi_{#mu}_lu_nis ",phibins,philow,phihigh,"#phi_{#mu}_lu_nis","Events");
    fGeneralphi_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_ll_nis_uncut","uncut #phi_{#mu}_ll_nis ",phibins,philow,phihigh,"#phi_{#mu}_ll_nis","Events");
    fGeneralphi_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_hu_nis_uncut","uncut #phi_{#mu}_hu_nis ",phibins,philow,phihigh,"#phi_{#mu}_hu_nis","Events");
    fGeneralphi_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","phi_hl_nis_uncut","uncut #phi_{#mu}_hl_nis ",phibins,philow,phihigh,"#phi_{#mu}_hl_nis","Events");
    fGeneralmuqual_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_uncut","uncut #muqual_{#mu} ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}","Events");
    fGeneralmuqual_lu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_lu_is_uncut","uncut #muqual_{#mu}_lu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_is","Events");
    fGeneralmuqual_ll_is_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_ll_is_uncut","uncut #muqual_{#mu}_ll_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_is","Events");
    fGeneralmuqual_hu_is_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_hu_is_uncut","uncut #muqual_{#mu}_hu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_is","Events");
    fGeneralmuqual_hl_is_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_hl_is_uncut","uncut #muqual_{#mu}_hl_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_is","Events");
    fGeneralmuqual_lu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_lu_nis_uncut","uncut #muqual_{#mu}_lu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_nis","Events");
    fGeneralmuqual_ll_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_ll_nis_uncut","uncut #muqual_{#mu}_ll_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_nis","Events");
    fGeneralmuqual_hu_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_hu_nis_uncut","uncut #muqual_{#mu}_hu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_nis","Events");
    fGeneralmuqual_hl_nis_uncut = gHistogrammer->TH1DFactory("TriMuon","muqual_hl_nis_uncut","uncut #muqual_{#mu}_hl_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_nis","Events");

    fGeneralsqisol_10_uncut    = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_uncut","uncut sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    fGeneralsqisol_10_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_lu_uncut","uncut_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_lu","Events");
    fGeneralsqisol_10_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_ll_uncut","uncut_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_ll","Events");
    fGeneralsqisol_10_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_hu_uncut","uncut_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hu","Events");
    fGeneralsqisol_10_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_hl_uncut","uncut_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hl","Events");
    fGeneralsqisol_10_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_lu_uncut","uncut_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_lu","Events");
    fGeneralsqisol_10_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_ll_uncut","uncut_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_ll","Events");
    fGeneralsqisol_10_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_hu_uncut","uncut_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hu","Events");
    fGeneralsqisol_10_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_hl_uncut","uncut_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hl","Events");

    fGeneralthrust_uncut    = gHistogrammer->TH1DFactory("TriMuon","thrust_uncut","uncut thrust",thrustbins,thrustlow,thrusthigh,"#thrust","Events");
    fGeneralthrust_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_is_lu_uncut","uncut_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_lu","Events");
    fGeneralthrust_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_is_ll_uncut","uncut_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_ll","Events");
    fGeneralthrust_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_is_hu_uncut","uncut_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hu","Events");
    fGeneralthrust_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_is_hl_uncut","uncut_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hl","Events");
    fGeneralthrust_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_lu_uncut","uncut_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_lu","Events");
    fGeneralthrust_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_ll_uncut","uncut_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_ll","Events");
    fGeneralthrust_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_hu_uncut","uncut_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hu","Events");
    fGeneralthrust_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_hl_uncut","uncut_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hl","Events");

//**************************************************
//Here the Histograms for the Instanton - Variables
//**************************************************

    fGeneralQ2Prime_uncut    = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_uncut","uncut Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2}","Events");
    fGeneralQ2Prime_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_lu_uncut","uncut_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_lu","Events");
    fGeneralQ2Prime_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_ll_uncut","uncut_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_ll","Events");
    fGeneralQ2Prime_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_hu_uncut","uncut_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hu","Events");
    fGeneralQ2Prime_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_hl_uncut","uncut_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hl","Events");
    fGeneralQ2Prime_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_lu_uncut","uncut_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_lu","Events");
    fGeneralQ2Prime_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_ll_uncut","uncut_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_ll","Events");
    fGeneralQ2Prime_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_hu_uncut","uncut_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hu","Events");
    fGeneralQ2Prime_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_hl_uncut","uncut_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hl","Events");

    fGeneralsphericity_uncut    = gHistogrammer->TH1DFactory("TriMuon","sphericity_uncut","uncut sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity","Events");
    fGeneralsphericity_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_lu_uncut","uncut_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_lu","Events");
    fGeneralsphericity_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_ll_uncut","uncut_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_ll","Events");
    fGeneralsphericity_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_hu_uncut","uncut_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hu","Events");
    fGeneralsphericity_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_hl_uncut","uncut_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hl","Events");
    fGeneralsphericity_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_lu_uncut","uncut_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_lu","Events");
    fGeneralsphericity_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_ll_uncut","uncut_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_ll","Events");
    fGeneralsphericity_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_hu_uncut","uncut_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hu","Events");
    fGeneralsphericity_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_hl_uncut","uncut_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hl","Events");

    fGeneralisotropy_uncut    = gHistogrammer->TH1DFactory("TriMuon","isotropy_uncut","uncut isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy","Events");
    fGeneralisotropy_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_lu_uncut","uncut_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_lu","Events");
    fGeneralisotropy_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_ll_uncut","uncut_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_ll","Events");
    fGeneralisotropy_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_hu_uncut","uncut_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hu","Events");
    fGeneralisotropy_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_hl_uncut","uncut_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hl","Events");
    fGeneralisotropy_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_lu_uncut","uncut_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_lu","Events");
    fGeneralisotropy_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_ll_uncut","uncut_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_ll","Events");
    fGeneralisotropy_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_hu_uncut","uncut_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hu","Events");
    fGeneralisotropy_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_hl_uncut","uncut_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hl","Events");

    fGeneralmultiplicity_uncut    = gHistogrammer->TH1DFactory("TriMuon","multiplicity_uncut","uncut multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity","Events");
    fGeneralmultiplicity_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_lu_uncut","uncut_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_lu","Events");
    fGeneralmultiplicity_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_ll_uncut","uncut_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_ll","Events");
    fGeneralmultiplicity_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_hu_uncut","uncut_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hu","Events");
    fGeneralmultiplicity_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_hl_uncut","uncut_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hl","Events");
    fGeneralmultiplicity_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_lu_uncut","uncut_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_lu","Events");
    fGeneralmultiplicity_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_ll_uncut","uncut_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_ll","Events");
    fGeneralmultiplicity_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_hu_uncut","uncut_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hu","Events");
    fGeneralmultiplicity_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_hl_uncut","uncut_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hl","Events");

//*************************************************************

    fGeneralcal_et_uncut    = gHistogrammer->TH1DFactory("TriMuon","cal_et_uncut","uncut cal_et",cal_etbins,cal_etlow,cal_ethigh,"#cal_et","Events");
    fGeneralcal_et_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_lu_uncut","uncut_lu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_lu","Events");
    fGeneralcal_et_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_ll_uncut","uncut_ll cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_ll","Events");
    fGeneralcal_et_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_hu_uncut","uncut_hu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hu","Events");
    fGeneralcal_et_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_hl_uncut","uncut_hl cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hl","Events");
    fGeneralcal_et_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_lu_uncut","uncut_lu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_lu","Events");
    fGeneralcal_et_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_ll_uncut","uncut_ll cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_ll","Events");
    fGeneralcal_et_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_hu_uncut","uncut_hu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hu","Events");
    fGeneralcal_et_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_hl_uncut","uncut_hl cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hl","Events");

    fGeneraletex2ir_uncut    = gHistogrammer->TH1DFactory("TriMuon","etex2ir_uncut","uncut etex2ir",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir","Events");
    fGeneraletex2ir_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_lu_uncut","uncut_lu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_lu","Events");
    fGeneraletex2ir_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_ll_uncut","uncut_ll etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_ll","Events");
    fGeneraletex2ir_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_hu_uncut","uncut_hu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hu","Events");
    fGeneraletex2ir_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_hl_uncut","uncut_hl etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hl","Events");
    fGeneraletex2ir_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_lu_uncut","uncut_lu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_lu","Events");
    fGeneraletex2ir_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_ll_uncut","uncut_ll etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_ll","Events");
    fGeneraletex2ir_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_hu_uncut","uncut_hu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hu","Events");
    fGeneraletex2ir_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_hl_uncut","uncut_hl etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hl","Events");

    fGeneralcal_et_m_et2ir_uncut    = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_uncut","uncut cal_et_m_et2ir",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir","Events");
    fGeneralcal_et_m_et2ir_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_lu_uncut","uncut_lu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_lu","Events");
    fGeneralcal_et_m_et2ir_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_ll_uncut","uncut_ll cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_ll","Events");
    fGeneralcal_et_m_et2ir_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_hu_uncut","uncut_hu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hu","Events");
    fGeneralcal_et_m_et2ir_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_hl_uncut","uncut_hl cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hl","Events");
    fGeneralcal_et_m_et2ir_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_lu_uncut","uncut_lu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_lu","Events");
    fGeneralcal_et_m_et2ir_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_ll_uncut","uncut_ll cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_ll","Events");
    fGeneralcal_et_m_et2ir_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_hu_uncut","uncut_hu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hu","Events");
    fGeneralcal_et_m_et2ir_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_hl_uncut","uncut_hl cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hl","Events");

    fGeneralcal_et_m_cal_et_10_uncut    = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_uncut","uncut cal_et_m_cal_et_10",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10","Events");
    fGeneralcal_et_m_cal_et_10_is_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_lu_uncut","uncut_lu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_lu","Events");
    fGeneralcal_et_m_cal_et_10_is_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_ll_uncut","uncut_ll cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_ll","Events");
    fGeneralcal_et_m_cal_et_10_is_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_hu_uncut","uncut_hu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hu","Events");
    fGeneralcal_et_m_cal_et_10_is_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_hl_uncut","uncut_hl cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hl","Events");
    fGeneralcal_et_m_cal_et_10_nis_lu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_lu_uncut","uncut_lu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_lu","Events");
    fGeneralcal_et_m_cal_et_10_nis_ll_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_ll_uncut","uncut_ll cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_ll","Events");
    fGeneralcal_et_m_cal_et_10_nis_hu_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_hu_uncut","uncut_hu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hu","Events");
    fGeneralcal_et_m_cal_et_10_nis_hl_uncut = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_hl_uncut","uncut_hl cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hl","Events");

    if( gCards->GetDoEfficiency() ) {
      fGeneralTriggerType_uncut = gHistogrammer->TH1DLabelFactory("TriMuon","TriggerType_uncut","uncut Trigger Type",triggertype,"","Events");
    }

    fGeneralNperEv = gHistogrammer->TH1DFactory("TriMuon","NperEv","n_{#mu#mu#mu}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu#mu}","Events");
    fGeneralTriMuonMass = gHistogrammer->TH1DFactory("TriMuon","TriMuonMass","#mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassLow = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassLow","low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassHigh = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassHigh","high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMass_LikeSign = gHistogrammer->TH1DFactory("TriMuon","TriMuonMass_LikeSign","#mu#mu invariant mass for like-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassLow_LikeSign = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassLow_LikeSign","low #mu#mu invariant mass for like-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassHigh_LikeSign = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassHigh_LikeSign","high #mu#mu invariant mass for like-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMass_UnlikeSign = gHistogrammer->TH1DFactory("TriMuon","TriMuonMass_UnlikeSign","#mu#mu invariant mass for unlike-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassLow_UnlikeSign = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassLow_UnlikeSign","low #mu#mu invariant mass for unlike-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralTriMuonMassHigh_UnlikeSign = gHistogrammer->TH1DFactory("TriMuon","TriMuonMassHigh_UnlikeSign","high #mu#mu invariant mass for unlike-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralMass_lu_is = gHistogrammer->TH1DFactory("TriMuon","Mass_lu_is","#mass_lu_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_is = gHistogrammer->TH1DFactory("TriMuon","Mass_ll_is","#mass_ll_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_is = gHistogrammer->TH1DFactory("TriMuon","Mass_hu_is","#mass_hu_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_is = gHistogrammer->TH1DFactory("TriMuon","Mass_hl_is","#mass_hl_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_lu_nis = gHistogrammer->TH1DFactory("TriMuon","Mass_lu_nis","#mass_lu_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_nis = gHistogrammer->TH1DFactory("TriMuon","Mass_ll_nis","#mass_ll_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_nis = gHistogrammer->TH1DFactory("TriMuon","Mass_hu_nis","#mass_hu_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_nis = gHistogrammer->TH1DFactory("TriMuon","Mass_hl_nis","#mass_hl_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralDeltaR = gHistogrammer->TH1DFactory("TriMuon","DeltaR","#DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR","Events");
    fGeneralDeltaR_lu_is = gHistogrammer->TH1DFactory("TriMuon","DeltaR_lu_is","#DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_is","Events");
    fGeneralDeltaR_ll_is = gHistogrammer->TH1DFactory("TriMuon","DeltaR_ll_is","#DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_is","Events");
    fGeneralDeltaR_hu_is = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hu_is","#DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_is","Events");
    fGeneralDeltaR_hl_is = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hl_is","#DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_is","Events");
    fGeneralDeltaR_lu_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaR_lu_nis","#DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_nis","Events");
    fGeneralDeltaR_ll_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaR_ll_nis","#DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_nis","Events");
    fGeneralDeltaR_hu_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hu_nis","#DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_nis","Events");
    fGeneralDeltaR_hl_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaR_hl_nis","#DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_nis","Events");
    fGeneralDeltaPhi = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi","#Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","Events");
    fGeneralDeltaPhi_lu_is = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_lu_is","#Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_is","Events");
    fGeneralDeltaPhi_ll_is = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_ll_is","#Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_is","Events");
    fGeneralDeltaPhi_hu_is = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hu_is","#Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_is","Events");
    fGeneralDeltaPhi_hl_is = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hl_is","#Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_is","Events");
    fGeneralDeltaPhi_lu_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_lu_nis","#Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_nis","Events");
    fGeneralDeltaPhi_ll_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_ll_nis","#Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_nis","Events");
    fGeneralDeltaPhi_hu_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hu_nis","#Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_nis","Events");
    fGeneralDeltaPhi_hl_nis = gHistogrammer->TH1DFactory("TriMuon","DeltaPhi_hl_nis","#Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_nis","Events");
    fGeneralDeltaEta = gHistogrammer->TH1DFactory("TriMuon","DeltaEta","#Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta","Events");
    fGeneralDeltaTheta = gHistogrammer->TH1DFactory("TriMuon","DeltaTheta","#Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta","Events");
  
    fGeneralPtAsymetry = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry","p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.","Events");
    fGeneralPtAsymetry_lu_is = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_lu_is","p_{T}_lu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.","Events");
    fGeneralPtAsymetry_ll_is = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_ll_is","p_{T}_ll_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.","Events");
    fGeneralPtAsymetry_hu_is = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hu_is","p_{T}_hu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.","Events");
    fGeneralPtAsymetry_hl_is = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hl_is","p_{T}_hl_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.","Events");
    fGeneralPtAsymetry_lu_nis = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_lu_nis","p_{T}_lu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.","Events");
    fGeneralPtAsymetry_ll_nis = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_ll_nis","p_{T}_ll_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.","Events");
    fGeneralPtAsymetry_hu_nis = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hu_nis","p_{T}_hu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.","Events");
    fGeneralPtAsymetry_hl_nis = gHistogrammer->TH1DFactory("TriMuon","PtAsymetry_hl_nis","p_{T}_hl_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.","Events");
    fGeneralpt = gHistogrammer->TH1DFactory("TriMuon","pt","p_{T} ",ptbins,ptlow,pthigh,"p_{T} ","Events");
    fGeneralpt_lu_is = gHistogrammer->TH1DFactory("TriMuon","pt_lu_is","#pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_is ","Events");
    fGeneralpt_ll_is = gHistogrammer->TH1DFactory("TriMuon","pt_ll_is","#pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_is ","Events");
    fGeneralpt_hu_is = gHistogrammer->TH1DFactory("TriMuon","pt_hu_is","#pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_is ","Events");
    fGeneralpt_hl_is = gHistogrammer->TH1DFactory("TriMuon","pt_hl_is","#pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_is ","Events");
    fGeneralpt_lu_nis = gHistogrammer->TH1DFactory("TriMuon","pt_lu_nis","#pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_nis ","Events");
    fGeneralpt_ll_nis = gHistogrammer->TH1DFactory("TriMuon","pt_ll_nis","#pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_nis ","Events");
    fGeneralpt_hu_nis = gHistogrammer->TH1DFactory("TriMuon","pt_hu_nis","#pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_nis ","Events");
    fGeneralpt_hl_nis = gHistogrammer->TH1DFactory("TriMuon","pt_hl_nis","#pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_nis ","Events");

    fGeneraleta = gHistogrammer->TH1DFactory("TriMuon","eta","#eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu} ","Events");
    fGeneraleta_lu_is = gHistogrammer->TH1DFactory("TriMuon","eta_lu_is","#eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}_lu_is ","Events");
    fGeneraleta_ll_is = gHistogrammer->TH1DFactory("TriMuon","eta_ll_is","#eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}_ll_is ","Events");
    fGeneraleta_hu_is = gHistogrammer->TH1DFactory("TriMuon","eta_hu_is","#eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}_hu_is ","Events");
    fGeneraleta_hl_is = gHistogrammer->TH1DFactory("TriMuon","eta_hl_is","#eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}_hl_is ","Events");
    fGeneraleta_lu_nis = gHistogrammer->TH1DFactory("TriMuon","eta_lu_nis","#eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_lu_nis ","Events");
    fGeneraleta_ll_nis = gHistogrammer->TH1DFactory("TriMuon","eta_ll_nis","#eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}_ll_nis ","Events");
    fGeneraleta_hu_nis = gHistogrammer->TH1DFactory("TriMuon","eta_hu_nis","#eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hu_nis ","Events");
    fGeneraleta_hl_nis = gHistogrammer->TH1DFactory("TriMuon","eta_hl_nis","#eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hl_nis ","Events");

    fGeneralImpact2D    = gHistogrammer->TH1DFactory("TriMuon","Impact2D","Impact2D",impactbins,impactlow,impacthigh,"# Impact2D","Events");
    fGeneralImpact2D_is_lu = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_lu","lu Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_lu","Events");
    fGeneralImpact2D_is_ll = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_ll","ll Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_ll","Events");
    fGeneralImpact2D_is_hu = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_hu","hu Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_hu","Events");
    fGeneralImpact2D_is_hl = gHistogrammer->TH1DFactory("TriMuon","Impact2D_is_hl","hl Impact2D_is",impactbins,impactlow,impacthigh,"# Impact2D_is_hl","Events");
    fGeneralImpact2D_nis_lu = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_lu","lu Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_lu","Events");
    fGeneralImpact2D_nis_ll = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_ll","ll Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_ll","Events");
    fGeneralImpact2D_nis_hu = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_hu","hu Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_hu","Events");
    fGeneralImpact2D_nis_hl = gHistogrammer->TH1DFactory("TriMuon","Impact2D_nis_hl","hl Impact2D_nis",impactbins,impactlow,impacthigh,"# Impact2D_nis_hl","Events");

    fGeneralphi = gHistogrammer->TH1DFactory("TriMuon","phi","#phi_{#mu} ",phibins,philow,phihigh,"#phi_{#mu} ","Events");
    fGeneralphi_lu_is = gHistogrammer->TH1DFactory("TriMuon","phi_lu_is","#phi_{#mu}_lu_is ",phibins,philow,phihigh,"#phi_{#mu}_lu_is ","Events");
    fGeneralphi_ll_is = gHistogrammer->TH1DFactory("TriMuon","phi_ll_is","#phi_{#mu}_ll_is ",phibins,philow,phihigh,"#phi_{#mu}_ll_is ","Events");
    fGeneralphi_hu_is = gHistogrammer->TH1DFactory("TriMuon","phi_hu_is","#phi_{#mu}_hu_is ",phibins,philow,phihigh,"#phi_{#mu}_hu_is ","Events");
    fGeneralphi_hl_is = gHistogrammer->TH1DFactory("TriMuon","phi_hl_is","#phi_{#mu}_hl_is ",phibins,philow,phihigh,"#phi_{#mu}_hl_is ","Events");
    fGeneralphi_lu_nis = gHistogrammer->TH1DFactory("TriMuon","phi_lu_nis","#phi_{#mu}_lu_nis ",phibins,philow,phihigh,"#phi_{#mu}_lu_nis ","Events");
    fGeneralphi_ll_nis = gHistogrammer->TH1DFactory("TriMuon","phi_ll_nis","#phi_{#mu}_ll_nis ",phibins,philow,phihigh,"#phi_{#mu}_ll_nis ","Events");
    fGeneralphi_hu_nis = gHistogrammer->TH1DFactory("TriMuon","phi_hu_nis","#phi_{#mu}_hu_nis ",phibins,philow,phihigh,"#phi_{#mu}_hu_nis ","Events");
    fGeneralphi_hl_nis = gHistogrammer->TH1DFactory("TriMuon","phi_hl_nis","#phi_{#mu}_hl_nis ",phibins,philow,phihigh,"#phi_{#mu}_hl_nis ","Events");
    fGeneralmuqual = gHistogrammer->TH1DFactory("TriMuon","muqual","#muqual_{#mu} ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu} ","Events");
    fGeneralmuqual_lu_is = gHistogrammer->TH1DFactory("TriMuon","muqual_lu_is","#muqual_{#mu}_lu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_is ","Events");
    fGeneralmuqual_ll_is = gHistogrammer->TH1DFactory("TriMuon","muqual_ll_is","#muqual_{#mu}_ll_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_is ","Events");
    fGeneralmuqual_hu_is = gHistogrammer->TH1DFactory("TriMuon","muqual_hu_is","#muqual_{#mu}_hu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_is ","Events");
    fGeneralmuqual_hl_is = gHistogrammer->TH1DFactory("TriMuon","muqual_hl_is","#muqual_{#mu}_hl_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_is ","Events");
    fGeneralmuqual_lu_nis = gHistogrammer->TH1DFactory("TriMuon","muqual_lu_nis","#muqual_{#mu}_lu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_nis ","Events");
    fGeneralmuqual_ll_nis = gHistogrammer->TH1DFactory("TriMuon","muqual_ll_nis","#muqual_{#mu}_ll_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_nis ","Events");
    fGeneralmuqual_hu_nis = gHistogrammer->TH1DFactory("TriMuon","muqual_hu_nis","#muqual_{#mu}_hu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_nis ","Events");
    fGeneralmuqual_hl_nis = gHistogrammer->TH1DFactory("TriMuon","muqual_hl_nis","#muqual_{#mu}_hl_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_nis ","Events");

    fGeneralsqisol_10    = gHistogrammer->TH1DFactory("TriMuon","sqisol_10","sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    fGeneralsqisol_10_is_lu = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_lu","sqisol_10_is_{#mu}_lu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_lu","Events");
    fGeneralsqisol_10_is_ll = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_ll","sqisol_10_is_{#mu}_ll",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_ll","Events");
    fGeneralsqisol_10_is_hu = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_hu","sqisol_10_is_{#mu}_hu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hu","Events");
    fGeneralsqisol_10_is_hl = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_is_hl","sqisol_10_is_{#mu}_hl",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hl","Events");
    fGeneralsqisol_10_nis_lu = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_lu","sqisol_10_nis_{#mu}_lu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_lu","Events");
    fGeneralsqisol_10_nis_ll = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_ll","sqisol_10_nis_{#mu}_ll",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_ll","Events");
    fGeneralsqisol_10_nis_hu = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_hu","sqisol_10_nis_{#mu}_hu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hu","Events");
    fGeneralsqisol_10_nis_hl = gHistogrammer->TH1DFactory("TriMuon","sqisol_10_nis_hl","sqisol_10_nis_{#mu}_hl",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hl","Events");

    fGeneralthrust    = gHistogrammer->TH1DFactory("TriMuon","thrust","thrust",thrustbins,thrustlow,thrusthigh,"#thrust","Events");
    fGeneralthrust_is_lu = gHistogrammer->TH1DFactory("TriMuon","thrust_is_lu","lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_lu","Events");
    fGeneralthrust_is_ll = gHistogrammer->TH1DFactory("TriMuon","thrust_is_ll","ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_ll","Events");
    fGeneralthrust_is_hu = gHistogrammer->TH1DFactory("TriMuon","thrust_is_hu","hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hu","Events");
    fGeneralthrust_is_hl = gHistogrammer->TH1DFactory("TriMuon","thrust_is_hl","hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hl","Events");
    fGeneralthrust_nis_lu = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_lu","lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_lu","Events");
    fGeneralthrust_nis_ll = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_ll","ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_ll","Events");
    fGeneralthrust_nis_hu = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_hu","hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hu","Events");
    fGeneralthrust_nis_hl = gHistogrammer->TH1DFactory("TriMuon","thrust_nis_hl","hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hl","Events");

//**********************************************************
//Here the Histograms for the Instanton - Variables
//**********************************************************

    fGeneralQ2Prime    = gHistogrammer->TH1DFactory("TriMuon","Q2Prime","Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2}","Events");
    fGeneralQ2Prime_is_lu = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_lu","lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_lu","Events");
    fGeneralQ2Prime_is_ll = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_ll","ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_ll","Events");
    fGeneralQ2Prime_is_hu = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_hu","hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hu","Events");
    fGeneralQ2Prime_is_hl = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_is_hl","hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hl","Events");
    fGeneralQ2Prime_nis_lu = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_lu","lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_lu","Events");
    fGeneralQ2Prime_nis_ll = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_ll","ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_ll","Events");
    fGeneralQ2Prime_nis_hu = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_hu","hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hu","Events");
    fGeneralQ2Prime_nis_hl = gHistogrammer->TH1DFactory("TriMuon","Q2Prime_nis_hl","hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hl","Events");

    fGeneralsphericity    = gHistogrammer->TH1DFactory("TriMuon","sphericity","sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity","Events");
    fGeneralsphericity_is_lu = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_lu","lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_lu","Events");
    fGeneralsphericity_is_ll = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_ll","ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_ll","Events");
    fGeneralsphericity_is_hu = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_hu","hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hu","Events");
    fGeneralsphericity_is_hl = gHistogrammer->TH1DFactory("TriMuon","sphericity_is_hl","hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hl","Events");
    fGeneralsphericity_nis_lu = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_lu","lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_lu","Events");
    fGeneralsphericity_nis_ll = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_ll","ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_ll","Events");
    fGeneralsphericity_nis_hu = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_hu","hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hu","Events");
    fGeneralsphericity_nis_hl = gHistogrammer->TH1DFactory("TriMuon","sphericity_nis_hl","hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hl","Events");

    fGeneralisotropy    = gHistogrammer->TH1DFactory("TriMuon","isotropy","isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy","Events");
    fGeneralisotropy_is_lu = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_lu","lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_lu","Events");
    fGeneralisotropy_is_ll = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_ll","ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_ll","Events");
    fGeneralisotropy_is_hu = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_hu","hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hu","Events");
    fGeneralisotropy_is_hl = gHistogrammer->TH1DFactory("TriMuon","isotropy_is_hl","hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hl","Events");
    fGeneralisotropy_nis_lu = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_lu","lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_lu","Events");
    fGeneralisotropy_nis_ll = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_ll","ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_ll","Events");
    fGeneralisotropy_nis_hu = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_hu","hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hu","Events");
    fGeneralisotropy_nis_hl = gHistogrammer->TH1DFactory("TriMuon","isotropy_nis_hl","hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hl","Events");

    fGeneralmultiplicity    = gHistogrammer->TH1DFactory("TriMuon","multiplicity","multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity","Events");
    fGeneralmultiplicity_is_lu = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_lu","lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_lu","Events");
    fGeneralmultiplicity_is_ll = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_ll","ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_ll","Events");
    fGeneralmultiplicity_is_hu = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_hu","hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hu","Events");
    fGeneralmultiplicity_is_hl = gHistogrammer->TH1DFactory("TriMuon","multiplicity_is_hl","hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hl","Events");
    fGeneralmultiplicity_nis_lu = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_lu","lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_lu","Events");
    fGeneralmultiplicity_nis_ll = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_ll","ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_ll","Events");
    fGeneralmultiplicity_nis_hu = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_hu","hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hu","Events");
    fGeneralmultiplicity_nis_hl = gHistogrammer->TH1DFactory("TriMuon","multiplicity_nis_hl","hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hl","Events");


//**********************************************************

    fGeneralempz    = gHistogrammer->TH1DFactory("TriMuon","empz","empz",empzbins,empzlow,empzhigh,"#empz","Events");
    fGeneralempz_is_lu = gHistogrammer->TH1DFactory("TriMuon","empz_is_lu","lu empz_is",empzbins,empzlow,empzhigh,"#empz_is_lu","Events");
    fGeneralempz_is_ll = gHistogrammer->TH1DFactory("TriMuon","empz_is_ll","ll empz_is",empzbins,empzlow,empzhigh,"#empz_is_ll","Events");
    fGeneralempz_is_hu = gHistogrammer->TH1DFactory("TriMuon","empz_is_hu","hu empz_is",empzbins,empzlow,empzhigh,"#empz_is_hu","Events");
    fGeneralempz_is_hl = gHistogrammer->TH1DFactory("TriMuon","empz_is_hl","hl empz_is",empzbins,empzlow,empzhigh,"#empz_is_hl","Events");
    fGeneralempz_nis_lu = gHistogrammer->TH1DFactory("TriMuon","empz_nis_lu","lu empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_lu","Events");
    fGeneralempz_nis_ll = gHistogrammer->TH1DFactory("TriMuon","empz_nis_ll","ll empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_ll","Events");
    fGeneralempz_nis_hu = gHistogrammer->TH1DFactory("TriMuon","empz_nis_hu","hu empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_hu","Events");
    fGeneralempz_nis_hl = gHistogrammer->TH1DFactory("TriMuon","empz_nis_hl","hl empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_hl","Events");

    fGeneralcal_et    = gHistogrammer->TH1DFactory("TriMuon","cal_et","uncut cal_et",cal_etbins,cal_etlow,cal_ethigh,"#cal_et","Events");
    fGeneralcal_et_is_lu = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_lu","lu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_lu","Events");
    fGeneralcal_et_is_ll = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_ll","ll cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_ll","Events");
    fGeneralcal_et_is_hu = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_hu","hu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hu","Events");
    fGeneralcal_et_is_hl = gHistogrammer->TH1DFactory("TriMuon","cal_et_is_hl","hl cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hl","Events");
    fGeneralcal_et_nis_lu = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_lu","lu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_lu","Events");
    fGeneralcal_et_nis_ll = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_ll","ll cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_ll","Events");
    fGeneralcal_et_nis_hu = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_hu","hu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hu","Events");
    fGeneralcal_et_nis_hl = gHistogrammer->TH1DFactory("TriMuon","cal_et_nis_hl","hl cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hl","Events");

     fGeneraletex2ir    = gHistogrammer->TH1DFactory("TriMuon","etex2ir","uncut etex2ir",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir","Events");
     fGeneraletex2ir_is_lu = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_lu","lu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_lu","Events");
     fGeneraletex2ir_is_ll = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_ll","ll etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_ll","Events");
     fGeneraletex2ir_is_hu = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_hu","hu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hu","Events");
     fGeneraletex2ir_is_hl = gHistogrammer->TH1DFactory("TriMuon","etex2ir_is_hl","hl etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hl","Events");
     fGeneraletex2ir_nis_lu = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_lu","lu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_lu","Events");
     fGeneraletex2ir_nis_ll = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_ll","ll etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_ll","Events");
     fGeneraletex2ir_nis_hu = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_hu","hu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hu","Events");
     fGeneraletex2ir_nis_hl = gHistogrammer->TH1DFactory("TriMuon","etex2ir_nis_hl","hl etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hl","Events");


    fGeneralcal_et_m_et2ir    = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir","uncut cal_et_m_et2ir",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir","Events");
    fGeneralcal_et_m_et2ir_is_lu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_lu","lu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_lu","Events");
    fGeneralcal_et_m_et2ir_is_ll = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_ll","ll cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_ll","Events");
    fGeneralcal_et_m_et2ir_is_hu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_hu","hu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hu","Events");
    fGeneralcal_et_m_et2ir_is_hl = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_is_hl","hl cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hl","Events");
    fGeneralcal_et_m_et2ir_nis_lu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_lu","lu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_lu","Events");
    fGeneralcal_et_m_et2ir_nis_ll = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_ll","ll cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_ll","Events");
    fGeneralcal_et_m_et2ir_nis_hu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_hu","hu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hu","Events");
    fGeneralcal_et_m_et2ir_nis_hl = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_et2ir_nis_hl","hl cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hl","Events");

    fGeneralcal_et_m_cal_et_10    = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10","uncut cal_et_m_cal_et_10",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10","Events");
    fGeneralcal_et_m_cal_et_10_is_lu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_lu","lu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_lu","Events");
    fGeneralcal_et_m_cal_et_10_is_ll = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_ll","ll cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_ll","Events");
    fGeneralcal_et_m_cal_et_10_is_hu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_hu","hu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hu","Events");
    fGeneralcal_et_m_cal_et_10_is_hl = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_is_hl","hl cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hl","Events");
    fGeneralcal_et_m_cal_et_10_nis_lu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_lu","lu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_lu","Events");
    fGeneralcal_et_m_cal_et_10_nis_ll = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_ll","ll cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_ll","Events");
    fGeneralcal_et_m_cal_et_10_nis_hu = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_hu","hu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hu","Events");
    fGeneralcal_et_m_cal_et_10_nis_hl = gHistogrammer->TH1DFactory("TriMuon","cal_et_m_cal_et_10_nis_hl","hl cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hl","Events");
 
    if( gCards->GetDoEfficiency() ) {
      fGeneralTriggerType = gHistogrammer->TH1DLabelFactory("TriMuon","TriggerType","Trigger Type",triggertype,"","Events");
    } 
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GTriMuons::FillGeneral() called" << endl << endl;

  if ( gCards->GetTRIMUONGeneral() ) {

    fGeneralNperEv_uncut->Fill(fNTriMuons,gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {
      fGeneralNperEv->Fill(fNChosenTriMuons,gHeader->GetWeight());
    }
  }

  return kTRUE;
}

//_____________________________________________________________

TString GTriMuons::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GTriMuons::PrintMessage() called" << endl << endl;

  TString dummy = "";

  GTriMuon *trimuon = 0;

  for ( Int_t i = 0; i < fNTriMuons; i++ ) {
    trimuon = ((GTriMuon*)(fTriMuons->At(i)));
    dummy.Append(trimuon->PrintMessage(option));
  }

  return dummy;
}

//_____________________________________________________________

Bool_t GTriMuons::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GTriMuons::Print() called" << endl << endl;

  option.ToUpper();

  GTriMuon *trimuon = 0;

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("TRIMUONS") || option.Contains("ALL") ) {
      gLister->FillOutputList("TriMuons:\n\n");
      for ( Int_t i = 0; i < fNTriMuons; i++ ) {
	trimuon = ((GTriMuon*)(fTriMuons->At(i)));
	trimuon->Print(option);
      }
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "TriMuons:" << endl << endl;;
    for ( Int_t i = 0; i < fNTriMuons; i++ ) {
      trimuon = ((GTriMuon*)(fTriMuons->At(i)));
      trimuon->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

GTriMuon* GTriMuons::GetTriMuon(Int_t index) {
  //
  // return trimuon parameters of the trimuon with index
  if ( gDebug ) cout << endl << "GTriMuons::GetTriMuon called" << endl << endl;

  if ( (index < fNTriMuons) && (index >= 0) ) {
    return ((GTriMuon*)(fTriMuons->At(index)));
  } else {
    if ( gCards->GetTRIMUONNTrimuons() > 0 ) {
      TString msg = "GTriMuons::GetTriMuon: requested trimuon index: ";
      msg += index;
      msg.Append(" is larger that total number of trimuons: ");
      msg += fNTriMuons;
      gLister->FillErrorList(msg.Data());
    } 
    return 0;
  }
}

//_____________________________________________________________

GTriMuon* GTriMuons::GetChosen() {
  //
  // return chosen trimuon
  if ( gDebug ) cout << endl << "GTriMuons::GetChosen called" << endl << endl;

  GTriMuon *trimuon = 0;

  for ( Int_t i = 0; i < fNTriMuons; i++ ) {
    trimuon = ((GTriMuon*)(fTriMuons->At(i)));
    if ( trimuon->GetType() == kChosenTriMuon )
      return trimuon;
  }

  return 0;

}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonPt(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with pt from appropriate muons from trimuon
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and (mpmatch || mufo)
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonPt called" << endl << endl;

  option.ToUpper();

// fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

// loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	tofill = muon->Pt();
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Pt();
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	tofill = muon->Pt();
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	tofill = muon->Pt();
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	tofill = muon->Pt();
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	tofill = muon->Pt();
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	tofill = muon->Pt();
      }
    }
    if ( histo != 0 ) {
      if ( (tofill >= min) && (tofill <= max) ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonP(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with p from appropriate muons from trimuon
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonP called" << endl << endl;

  option.ToUpper();

// fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	tofill = muon->P();
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->P();
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	tofill = muon->P();
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	tofill = muon->P();
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	tofill = muon->P();
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	tofill = muon->P();
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	tofill = muon->P();
      }
    }
    if ( histo != 0 ) {
      if ( (tofill >= min) && (tofill <= max) ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonPz(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with pz from appropriate muons from trimuon
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonPz called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    } 
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }
  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	tofill = muon->Pz();
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Pz();
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	tofill = muon->Pz();
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	tofill = muon->Pz();
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	tofill = muon->Pz();
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	tofill = muon->Pz();
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	tofill = muon->Pz();
      }
    }
    if ( histo != 0 ) {
      if ( (tofill >= min) && (tofill <= max) ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;
    
  return kTRUE;
}
  

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonEta(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with eta from appropriate muons from trimuon
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonEta called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }
  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	tofill = muon->Eta();
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Eta();
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	tofill = muon->Eta();
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	tofill = muon->Eta();
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	tofill = muon->Eta();
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	tofill = muon->Eta();
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	tofill = muon->Eta();
      }
    }
    if ( histo != 0 ) {
      if ( (tofill >= min) && (tofill <= max) ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonPhi(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with phi from appropriate muons from trimuon
  //
  // options:
  //
  // ALL: fill if muon is found by mv and or of all finders except mv
  // BREMAT: fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH: fill if muon is found by mv and mpmatch
  // MUBAC: fill if muon is found by mv and mubac
  // MUFO: fill if muon is found by mv and mufo
  // MV: fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonPhi called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }
  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	tofill = muon->Phi();
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Phi();
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	tofill = muon->Phi();
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	tofill = muon->Phi();
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	tofill = muon->Phi();
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	tofill = muon->Phi();
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	tofill = muon->Phi();
      }
    }
    if ( histo != 0 ) {
      if ( (tofill >= min) && (tofill <= max) ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonEtaPtBins(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with eta from appropriate muons from trimuon in bins of muon pt
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonEtaPtBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    }
    if ( histo != 0 ) {
      if ( tofill !=  -999999999.99) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonPhiPtBins(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with phi from appropriate muons from trimuon in bins of muon pt
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonPhiPtBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	if ( (muon->Pt() > min) && (muon->Pt() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    }
    if ( histo != 0 ) {
      if ( tofill != -999999999.99 ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonEtaPBins(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with eta from appropriate muons from trimuon in bins of muon pt
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonEtaPBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    }
    if ( histo != 0 ) {
      if ( tofill !=  -999999999.99) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonPhiPBins(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with phi from appropriate muons from trimuon in bins pf muon pt
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonPhiPBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
     if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	if ( (muon->P() > min) && (muon->P() <= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    }
    if ( histo != 0 ) {
      if ( tofill != -999999999.99 ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonEtaPzBins(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with eta from appropriate muons from trimuon in bins of muon pt
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonEtaPz called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
     if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Eta();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Eta();
	}
      }
    }
    if ( histo != 0 ) {
      if ( tofill !=  -999999999.99) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::FillPlotMuonPhiPzBins(GTriMuon *trimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with phi from appropriate muons from trimuon in bins of muon pt
  //
  // options:
  //
  // ALL:       fill if muon is found by mv and or of all finders except mv
  // BREMAT:    fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH:   fill if muon is found by mv and mpmatch
  // MUBAC:     fill if muon is found by mv and mubac
  // MUFO:      fill if muon is found by mv and mufo
  // MV:        fill if muon is found by mv and mv
  if ( gDebug ) cout << endl << "GTriMuons::FillPlotMuonPhiPz called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = trimuon->GetMuon1();
  GMuon *muon2 = trimuon->GetMuon2();
  GMuon *muon3 = trimuon->GetMuon3();
  if ( trimuon->GetTriggerType() == kTakeAll ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
      muons->Add(muon3);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon1 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if ( option.Contains("BARREL") ) {
      if ( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if ( option.Contains("REAR") ) {
      if ( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon2 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if ( option.Contains("BARREL") ) {
      if ( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if ( option.Contains("REAR") ) {
      if ( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  } else if ( trimuon->GetTriggerType() == kTakeTriMuon3 ) {
    if ( option.Contains("FORWARD") ) {
      if ( muon3->GetType() == kForward )
	muons->Add(muon3);
    } else if ( option.Contains("BARREL") ) {
      if ( muon3->GetType() == kBarrel )
	muons->Add(muon3);
    } else if ( option.Contains("REAR") ) {
      if ( muon3->GetType() == kRear )
	muons->Add(muon3);
    } else {
      muons->Add(muon3);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon() ) {
    Double_t tofill = -999999999.99;
    if ( option.Contains("ALL") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("BREMAT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("BREMINOUT") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MPMATCH") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MUBAC") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MUFO") ) {
      if ( trimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    } else if ( option.Contains("MV") ) {
      if ( trimuon->GetMuonsMVCuts() && muon->GetMv() ) {
	if ( (muon->Pz() < min) && (muon->Pz() >= max ) ) { 
	  tofill = muon->Phi();
	} else if ( (currentBin == maxBin) && (muon->Pt() > max) ) {
	  tofill = muon->Phi();
	}
      }
    }
    if ( histo != 0 ) {
      if ( tofill != -999999999.99 ) {
	if ( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX())) ) {
	  histo->Fill(histo->GetBinLowEdge(histo->GetNbinsX())+(histo->GetBinWidth(histo->GetNbinsX())/2));
	} else {
	  histo->Fill(tofill);
	}
      }
    }
  }

  muons->Clear("nodelete");
  delete muons;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTriMuons::InitVariables() {
  //
  // init variables
  if ( gDebug ) cout << endl << "GTriMuons::InitVariables() called" << endl << endl;

  // initialize clonesarray
  fTriMuons  = new TClonesArray("GTriMuon",100);
  fNTriMuons = 0;

  // init variables
  fInvMassCut         = kFALSE;
  fDeltaRCut          = kFALSE;
  fDeltaPhiCut        = kFALSE;
  fDeltaThetaCut      = kFALSE;
  fDeltaEtaCut        = kFALSE;
  fPtAsymetryCut      = kFALSE;
  fEtFractionHighCut  = kFALSE;
  fEtFractionLowCut   = kFALSE;
  fDifChargeCut       = kFALSE;
  fCharmMCJpsiCut     = kFALSE;
  fCharmMCPsiprimeCut = kFALSE;
  fAllCuts            = kFALSE;

  fDoCalcIsolation   = kFALSE;

  fSelectedIndex     = -99;

  fNGoodTriMuons     = 0;
  fNChosenTriMuons   = 0;
   
  // init general histograms
  fGeneralNperEv_uncut                        = 0;
  fGeneralTriMuonMass_uncut                   = 0;
  fGeneralTriMuonMassLow_uncut                = 0;
  fGeneralTriMuonMassHigh_uncut               = 0;
  fGeneralTriMuonMass_LikeSign_uncut          = 0;
  fGeneralTriMuonMassLow_LikeSign_uncut       = 0;
  fGeneralTriMuonMassHigh_LikeSign_uncut      = 0;
  fGeneralTriMuonMass_UnlikeSign_uncut        = 0;
  fGeneralTriMuonMassLow_UnlikeSign_uncut     = 0;
  fGeneralTriMuonMassHigh_UnlikeSign_uncut    = 0;

  fGeneralMass_lu_is_uncut                    = 0; 
  fGeneralMass_ll_is_uncut                    = 0; 
  fGeneralMass_hu_is_uncut                    = 0; 
  fGeneralMass_hl_is_uncut                    = 0; 
  fGeneralMass_lu_nis_uncut                   = 0;
  fGeneralMass_ll_nis_uncut                   = 0;
  fGeneralMass_hu_nis_uncut                   = 0;
  fGeneralMass_hl_nis_uncut                   = 0;

  fGeneralDeltaR_uncut                        = 0;
  fGeneralDeltaR_lu_is_uncut                  = 0;
  fGeneralDeltaR_ll_is_uncut                  = 0;
  fGeneralDeltaR_hu_is_uncut                  = 0;
  fGeneralDeltaR_hl_is_uncut                  = 0;
  fGeneralDeltaR_lu_nis_uncut                 = 0;
  fGeneralDeltaR_ll_nis_uncut                 = 0;
  fGeneralDeltaR_hu_nis_uncut                 = 0;
  fGeneralDeltaR_hl_nis_uncut                 = 0;
  fGeneralDeltaPhi_uncut                      = 0;
  fGeneralDeltaPhi_lu_is_uncut                = 0;
  fGeneralDeltaPhi_ll_is_uncut                = 0;
  fGeneralDeltaPhi_hu_is_uncut                = 0;
  fGeneralDeltaPhi_hl_is_uncut                = 0;
  fGeneralDeltaPhi_lu_nis_uncut               = 0;
  fGeneralDeltaPhi_ll_nis_uncut               = 0;
  fGeneralDeltaPhi_hu_nis_uncut               = 0;
  fGeneralDeltaPhi_hl_nis_uncut               = 0;
  fGeneralDeltaEta_uncut                      = 0;
  fGeneralDeltaTheta_uncut                    = 0;

  fGeneralPtAsymetry_uncut                    = 0;
  fGeneralPtAsymetry_lu_is_uncut              = 0;
  fGeneralPtAsymetry_ll_is_uncut              = 0;
  fGeneralPtAsymetry_hu_is_uncut              = 0;
  fGeneralPtAsymetry_hl_is_uncut              = 0;
  fGeneralPtAsymetry_lu_nis_uncut             = 0;
  fGeneralPtAsymetry_ll_nis_uncut             = 0;
  fGeneralPtAsymetry_hu_nis_uncut             = 0;
  fGeneralPtAsymetry_hl_nis_uncut             = 0;
  fGeneralpt_uncut                            = 0;
  fGeneralpt_lu_is_uncut                      = 0;
  fGeneralpt_ll_is_uncut                      = 0;
  fGeneralpt_hu_is_uncut                      = 0;
  fGeneralpt_hl_is_uncut                      = 0;
  fGeneralpt_lu_nis_uncut                     = 0;
  fGeneralpt_ll_nis_uncut                     = 0;
  fGeneralpt_hu_nis_uncut                     = 0;
  fGeneralpt_hl_nis_uncut                     = 0;

  fGeneraleta_uncut                           = 0;
  fGeneraleta_lu_is_uncut                     = 0;
  fGeneraleta_ll_is_uncut                     = 0;
  fGeneraleta_hu_is_uncut                     = 0;
  fGeneraleta_hl_is_uncut                     = 0;
  fGeneraleta_lu_nis_uncut                    = 0;
  fGeneraleta_ll_nis_uncut                    = 0;
  fGeneraleta_hu_nis_uncut                    = 0;
  fGeneraleta_hl_nis_uncut                    = 0;

  fGeneralphi_uncut                           = 0;
  fGeneralphi_lu_is_uncut                     = 0;
  fGeneralphi_ll_is_uncut                     = 0;
  fGeneralphi_hu_is_uncut                     = 0;
  fGeneralphi_hl_is_uncut                     = 0;
  fGeneralphi_lu_nis_uncut                    = 0;
  fGeneralphi_ll_nis_uncut                    = 0;
  fGeneralphi_hu_nis_uncut                    = 0;
  fGeneralphi_hl_nis_uncut                    = 0;
  fGeneralmuqual_uncut                        = 0;
  fGeneralmuqual_lu_is_uncut                  = 0;
  fGeneralmuqual_ll_is_uncut                  = 0;
  fGeneralmuqual_hu_is_uncut                  = 0;
  fGeneralmuqual_hl_is_uncut                  = 0;
  fGeneralmuqual_lu_nis_uncut                 = 0;
  fGeneralmuqual_ll_nis_uncut                 = 0;
  fGeneralmuqual_hu_nis_uncut                 = 0;
  fGeneralmuqual_hl_nis_uncut                 = 0;

  fGeneralsqisol_10_uncut                     = 0;   
  fGeneralsqisol_10_is_lu_uncut               = 0;
  fGeneralsqisol_10_is_ll_uncut               = 0;
  fGeneralsqisol_10_is_hu_uncut               = 0;
  fGeneralsqisol_10_is_hl_uncut               = 0;
  fGeneralsqisol_10_nis_lu_uncut              = 0;
  fGeneralsqisol_10_nis_ll_uncut              = 0;
  fGeneralsqisol_10_nis_hu_uncut              = 0;
  fGeneralsqisol_10_nis_hl_uncut              = 0;
  fGeneralthrust_uncut                        = 0;
  fGeneralthrust_is_lu_uncut	              = 0;
  fGeneralthrust_is_ll_uncut	              = 0;
  fGeneralthrust_is_hu_uncut	              = 0;
  fGeneralthrust_is_hl_uncut	              = 0;
  fGeneralthrust_nis_lu_uncut	              = 0;
  fGeneralthrust_nis_ll_uncut	              = 0;
  fGeneralthrust_nis_hu_uncut	              = 0;
  fGeneralthrust_nis_hl_uncut	              = 0;

  fGeneralQ2Prime_uncut                       = 0;
  fGeneralQ2Prime_is_lu_uncut                 = 0;
  fGeneralQ2Prime_is_ll_uncut                 = 0;
  fGeneralQ2Prime_is_hu_uncut                 = 0;
  fGeneralQ2Prime_is_hl_uncut                 = 0;
  fGeneralQ2Prime_nis_lu_uncut                = 0; 
  fGeneralQ2Prime_nis_ll_uncut                = 0;
  fGeneralQ2Prime_nis_hu_uncut                = 0;
  fGeneralQ2Prime_nis_hl_uncut                = 0;

  fGeneralsphericity_uncut                    = 0;
  fGeneralsphericity_is_lu_uncut              = 0;
  fGeneralsphericity_is_ll_uncut              = 0;
  fGeneralsphericity_is_hu_uncut              = 0;
  fGeneralsphericity_is_hl_uncut              = 0;
  fGeneralsphericity_nis_lu_uncut             = 0; 
  fGeneralsphericity_nis_ll_uncut             = 0;
  fGeneralsphericity_nis_hu_uncut             = 0;
  fGeneralsphericity_nis_hl_uncut             = 0;

  fGeneralisotropy_uncut                      = 0;
  fGeneralisotropy_is_lu_uncut                = 0;
  fGeneralisotropy_is_ll_uncut                = 0;
  fGeneralisotropy_is_hu_uncut                = 0;
  fGeneralisotropy_is_hl_uncut                = 0;
  fGeneralisotropy_nis_lu_uncut               = 0;
  fGeneralisotropy_nis_ll_uncut               = 0;
  fGeneralisotropy_nis_hu_uncut               = 0;
  fGeneralisotropy_nis_hl_uncut               = 0;

  fGeneralmultiplicity_uncut                  = 0;
  fGeneralmultiplicity_is_lu_uncut            = 0;
  fGeneralmultiplicity_is_ll_uncut            = 0;
  fGeneralmultiplicity_is_hu_uncut            = 0;
  fGeneralmultiplicity_is_hl_uncut            = 0;
  fGeneralmultiplicity_nis_lu_uncut           = 0;
  fGeneralmultiplicity_nis_ll_uncut           = 0;
  fGeneralmultiplicity_nis_hu_uncut           = 0;
  fGeneralmultiplicity_nis_hl_uncut           = 0;

  fGeneralImpact2D_uncut                      = 0;
  fGeneralImpact2D_is_lu_uncut                = 0;
  fGeneralImpact2D_is_ll_uncut                = 0;  
  fGeneralImpact2D_is_hu_uncut                = 0;
  fGeneralImpact2D_is_hl_uncut                = 0;
  fGeneralImpact2D_nis_lu_uncut               = 0;
  fGeneralImpact2D_nis_ll_uncut               = 0; 
  fGeneralImpact2D_nis_hu_uncut               = 0;
  fGeneralImpact2D_nis_hl_uncut               = 0;

  fGeneralcal_et_uncut                        = 0;
  fGeneralcal_et_is_lu_uncut	              = 0;
  fGeneralcal_et_is_ll_uncut	              = 0;
  fGeneralcal_et_is_hu_uncut	              = 0;
  fGeneralcal_et_is_hl_uncut	              = 0;
  fGeneralcal_et_nis_lu_uncut	              = 0;
  fGeneralcal_et_nis_ll_uncut	              = 0;
  fGeneralcal_et_nis_hu_uncut	              = 0;
  fGeneralcal_et_nis_hl_uncut	              = 0;

  fGeneraletex2ir_uncut                       = 0;
  fGeneraletex2ir_is_lu_uncut	              = 0;
  fGeneraletex2ir_is_ll_uncut	              = 0;
  fGeneraletex2ir_is_hu_uncut	              = 0;
  fGeneraletex2ir_is_hl_uncut	              = 0;
  fGeneraletex2ir_nis_lu_uncut	              = 0;
  fGeneraletex2ir_nis_ll_uncut	              = 0;
  fGeneraletex2ir_nis_hu_uncut	              = 0;
  fGeneraletex2ir_nis_hl_uncut	              = 0;

  fGeneralcal_et_m_et2ir_uncut                = 0;
  fGeneralcal_et_m_et2ir_is_lu_uncut	      = 0;
  fGeneralcal_et_m_et2ir_is_ll_uncut	      = 0;
  fGeneralcal_et_m_et2ir_is_hu_uncut	      = 0;
  fGeneralcal_et_m_et2ir_is_hl_uncut	      = 0;
  fGeneralcal_et_m_et2ir_nis_lu_uncut	      = 0;
  fGeneralcal_et_m_et2ir_nis_ll_uncut	      = 0;
  fGeneralcal_et_m_et2ir_nis_hu_uncut	      = 0;
  fGeneralcal_et_m_et2ir_nis_hl_uncut	      = 0;

  fGeneralcal_et_m_cal_et_10_uncut            = 0;
  fGeneralcal_et_m_cal_et_10_is_lu_uncut      = 0;
  fGeneralcal_et_m_cal_et_10_is_ll_uncut      = 0;
  fGeneralcal_et_m_cal_et_10_is_hu_uncut      = 0;
  fGeneralcal_et_m_cal_et_10_is_hl_uncut      = 0;
  fGeneralcal_et_m_cal_et_10_nis_lu_uncut     = 0;
  fGeneralcal_et_m_cal_et_10_nis_ll_uncut     = 0;
  fGeneralcal_et_m_cal_et_10_nis_hu_uncut     = 0;
  fGeneralcal_et_m_cal_et_10_nis_hl_uncut     = 0;

  fGeneralTriggerType_uncut                   = 0;
  fGeneralNperEv                              = 0;
  fGeneralTriMuonMass                         = 0;
  fGeneralTriMuonMassLow                      = 0;
  fGeneralTriMuonMassHigh                     = 0;
  fGeneralTriMuonMass_LikeSign                = 0;
  fGeneralTriMuonMassLow_LikeSign             = 0;
  fGeneralTriMuonMassHigh_LikeSign            = 0;
  fGeneralTriMuonMass_UnlikeSign              = 0;
  fGeneralTriMuonMassLow_UnlikeSign           = 0;
  fGeneralTriMuonMassHigh_UnlikeSign          = 0;

  fGeneralMass_lu_is                          = 0;	
  fGeneralMass_ll_is                          = 0;	
  fGeneralMass_hu_is                          = 0;	
  fGeneralMass_hl_is                          = 0;	
  fGeneralMass_lu_nis                         = 0;
  fGeneralMass_ll_nis                         = 0;
  fGeneralMass_hu_nis                         = 0;
  fGeneralMass_hl_nis                         = 0;

  fGeneralDeltaR                              = 0;
  fGeneralDeltaR_lu_is                        = 0;
  fGeneralDeltaR_ll_is                        = 0;
  fGeneralDeltaR_hu_is                        = 0;
  fGeneralDeltaR_hl_is                        = 0;
  fGeneralDeltaR_lu_nis                       = 0;
  fGeneralDeltaR_ll_nis                       = 0;
  fGeneralDeltaR_hu_nis                       = 0;
  fGeneralDeltaR_hl_nis                       = 0;
  fGeneralDeltaPhi                            = 0;
  fGeneralDeltaPhi_lu_is                      = 0;
  fGeneralDeltaPhi_ll_is                      = 0;
  fGeneralDeltaPhi_hu_is                      = 0;
  fGeneralDeltaPhi_hl_is                      = 0;
  fGeneralDeltaPhi_lu_nis                     = 0;
  fGeneralDeltaPhi_ll_nis                     = 0;
  fGeneralDeltaPhi_hu_nis                     = 0;
  fGeneralDeltaPhi_hl_nis                     = 0;
  fGeneralDeltaEta                            = 0;
  fGeneralDeltaTheta                          = 0;

  fGeneralPtAsymetry                          = 0;
  fGeneralPtAsymetry_lu_is                    = 0;
  fGeneralPtAsymetry_ll_is                    = 0;
  fGeneralPtAsymetry_hu_is                    = 0;
  fGeneralPtAsymetry_hl_is                    = 0;
  fGeneralPtAsymetry_lu_nis                   = 0;
  fGeneralPtAsymetry_ll_nis                   = 0;
  fGeneralPtAsymetry_hu_nis                   = 0;
  fGeneralPtAsymetry_hl_nis                   = 0;
  fGeneralpt                                  = 0;
  fGeneralpt_lu_is                            = 0;
  fGeneralpt_ll_is                            = 0;
  fGeneralpt_hu_is                            = 0;
  fGeneralpt_hl_is                            = 0;
  fGeneralpt_lu_nis                           = 0;
  fGeneralpt_ll_nis                           = 0;
  fGeneralpt_hu_nis                           = 0;
  fGeneralpt_hl_nis                           = 0;

  fGeneraleta                                 = 0;
  fGeneraleta_lu_is                           = 0;
  fGeneraleta_ll_is                           = 0;
  fGeneraleta_hu_is                           = 0;
  fGeneraleta_hl_is                           = 0;
  fGeneraleta_lu_nis                          = 0;
  fGeneraleta_ll_nis                          = 0;
  fGeneraleta_hu_nis                          = 0;
  fGeneraleta_hl_nis                          = 0;

  fGeneralphi                                 = 0;
  fGeneralphi_lu_is                           = 0;
  fGeneralphi_ll_is                           = 0;
  fGeneralphi_hu_is                           = 0;
  fGeneralphi_hl_is                           = 0;
  fGeneralphi_lu_nis                          = 0;
  fGeneralphi_ll_nis                          = 0;
  fGeneralphi_hu_nis                          = 0;
  fGeneralphi_hl_nis                          = 0;
  fGeneralmuqual                              = 0;
  fGeneralmuqual_lu_is                        = 0;
  fGeneralmuqual_ll_is                        = 0;
  fGeneralmuqual_hu_is                        = 0;
  fGeneralmuqual_hl_is                        = 0;
  fGeneralmuqual_lu_nis                       = 0;
  fGeneralmuqual_ll_nis                       = 0;
  fGeneralmuqual_hu_nis                       = 0;
  fGeneralmuqual_hl_nis                       = 0;
  fGeneralsqisol_10                           = 0;
  fGeneralsqisol_10_is_lu                     = 0;
  fGeneralsqisol_10_is_ll                     = 0;
  fGeneralsqisol_10_is_hu                     = 0;
  fGeneralsqisol_10_is_hl                     = 0;
  fGeneralsqisol_10_nis_lu                    = 0;
  fGeneralsqisol_10_nis_ll                    = 0;
  fGeneralsqisol_10_nis_hu                    = 0;
  fGeneralsqisol_10_nis_hl                    = 0;

  fGeneralthrust                              = 0;
  fGeneralthrust_is_lu	                      = 0;
  fGeneralthrust_is_ll	                      = 0;
  fGeneralthrust_is_hu	                      = 0;
  fGeneralthrust_is_hl	                      = 0;
  fGeneralthrust_nis_lu	                      = 0;
  fGeneralthrust_nis_ll	                      = 0;
  fGeneralthrust_nis_hu	                      = 0;
  fGeneralthrust_nis_hl	                      = 0;

  fGeneralQ2Prime                             = 0;
  fGeneralQ2Prime_is_lu                       = 0;
  fGeneralQ2Prime_is_ll                       = 0;
  fGeneralQ2Prime_is_hu                       = 0;
  fGeneralQ2Prime_is_hl                       = 0;
  fGeneralQ2Prime_nis_lu                      = 0; 
  fGeneralQ2Prime_nis_ll                      = 0;
  fGeneralQ2Prime_nis_hu                      = 0;
  fGeneralQ2Prime_nis_hl                      = 0;

  fGeneralsphericity                          = 0;
  fGeneralsphericity_is_lu                    = 0;
  fGeneralsphericity_is_ll                    = 0;
  fGeneralsphericity_is_hu                    = 0;
  fGeneralsphericity_is_hl                    = 0;
  fGeneralsphericity_nis_lu                   = 0; 
  fGeneralsphericity_nis_ll                   = 0;
  fGeneralsphericity_nis_hu                   = 0;
  fGeneralsphericity_nis_hl                   = 0;

  fGeneralisotropy                            = 0;
  fGeneralisotropy_is_lu                      = 0;
  fGeneralisotropy_is_ll                      = 0;
  fGeneralisotropy_is_hu                      = 0;
  fGeneralisotropy_is_hl                      = 0;
  fGeneralisotropy_nis_lu                     = 0;
  fGeneralisotropy_nis_ll                     = 0;
  fGeneralisotropy_nis_hu                     = 0;
  fGeneralisotropy_nis_hl                     = 0;

  fGeneralmultiplicity                        = 0;
  fGeneralmultiplicity_is_lu                  = 0;
  fGeneralmultiplicity_is_ll                  = 0;
  fGeneralmultiplicity_is_hu                  = 0;
  fGeneralmultiplicity_is_hl                  = 0;
  fGeneralmultiplicity_nis_lu                 = 0;
  fGeneralmultiplicity_nis_ll                 = 0;
  fGeneralmultiplicity_nis_hu                 = 0;
  fGeneralmultiplicity_nis_hl                 = 0;

  fGeneralImpact2D                            = 0;
  fGeneralImpact2D_is_lu                      = 0;
  fGeneralImpact2D_is_ll                      = 0;  
  fGeneralImpact2D_is_hu                      = 0;
  fGeneralImpact2D_is_hl                      = 0;
  fGeneralImpact2D_nis_lu                     = 0;
  fGeneralImpact2D_nis_ll                     = 0; 
  fGeneralImpact2D_nis_hu                     = 0;
  fGeneralImpact2D_nis_hl                     = 0;

  fGeneralcal_et                              = 0;
  fGeneralcal_et_is_lu	                      = 0;
  fGeneralcal_et_is_ll	                      = 0;
  fGeneralcal_et_is_hu	                      = 0;
  fGeneralcal_et_is_hl	                      = 0;
  fGeneralcal_et_nis_lu	                      = 0;
  fGeneralcal_et_nis_ll	                      = 0;
  fGeneralcal_et_nis_hu	                      = 0;
  fGeneralcal_et_nis_hl	                      = 0;

  fGeneraletex2ir                             = 0;
  fGeneraletex2ir_is_lu	                      = 0;
  fGeneraletex2ir_is_ll	                      = 0;
  fGeneraletex2ir_is_hu	                      = 0;
  fGeneraletex2ir_is_hl	                      = 0;
  fGeneraletex2ir_nis_lu	              = 0;
  fGeneraletex2ir_nis_ll	              = 0;
  fGeneraletex2ir_nis_hu	              = 0;
  fGeneraletex2ir_nis_hl	              = 0;

  fGeneralcal_et_m_et2ir                      = 0;
  fGeneralcal_et_m_et2ir_is_lu	              = 0;
  fGeneralcal_et_m_et2ir_is_ll	              = 0;
  fGeneralcal_et_m_et2ir_is_hu	              = 0;
  fGeneralcal_et_m_et2ir_is_hl	              = 0;
  fGeneralcal_et_m_et2ir_nis_lu	              = 0;
  fGeneralcal_et_m_et2ir_nis_ll	              = 0;
  fGeneralcal_et_m_et2ir_nis_hu	              = 0;
  fGeneralcal_et_m_et2ir_nis_hl	              = 0;

  fGeneralcal_et_m_cal_et_10                  = 0;
  fGeneralcal_et_m_cal_et_10_is_lu	      = 0;
  fGeneralcal_et_m_cal_et_10_is_ll	      = 0;
  fGeneralcal_et_m_cal_et_10_is_hu	      = 0;
  fGeneralcal_et_m_cal_et_10_is_hl	      = 0;
  fGeneralcal_et_m_cal_et_10_nis_lu	      = 0;
  fGeneralcal_et_m_cal_et_10_nis_ll	      = 0;
  fGeneralcal_et_m_cal_et_10_nis_hu	      = 0;
  fGeneralcal_et_m_cal_et_10_nis_hl	      = 0;

  fGeneralTriggerType                         = 0;

  // init control plots
  fControlNperEv_uncut                        = 0;
  fControlTriMuonMass_uncut                   = 0;
  fControlTriMuonMassLow_uncut                = 0;
  fControlTriMuonMassHigh_uncut               = 0;

  fControlMass_lu_is_uncut                    = 0;	
  fControlMass_ll_is_uncut                    = 0;	
  fControlMass_hu_is_uncut                    = 0;	
  fControlMass_hl_is_uncut                    = 0;	
  fControlMass_lu_nis_uncut                   = 0;
  fControlMass_ll_nis_uncut                   = 0;
  fControlMass_hu_nis_uncut                   = 0;
  fControlMass_hl_nis_uncut                   = 0;
 
  fControlDeltaR_uncut                        = 0;
  fControlDeltaR_lu_is_uncut                  = 0;
  fControlDeltaR_ll_is_uncut                  = 0;
  fControlDeltaR_hu_is_uncut                  = 0;
  fControlDeltaR_hl_is_uncut                  = 0;
  fControlDeltaR_lu_nis_uncut                 = 0;
  fControlDeltaR_ll_nis_uncut                 = 0;
  fControlDeltaR_hu_nis_uncut                 = 0;
  fControlDeltaR_hl_nis_uncut                 = 0;
  fControlDeltaPhi_uncut                      = 0;
  fControlDeltaPhi_lu_is_uncut                = 0;
  fControlDeltaPhi_ll_is_uncut                = 0;
  fControlDeltaPhi_hu_is_uncut                = 0;
  fControlDeltaPhi_hl_is_uncut                = 0;
  fControlDeltaPhi_lu_nis_uncut               = 0;
  fControlDeltaPhi_ll_nis_uncut               = 0;
  fControlDeltaPhi_hu_nis_uncut               = 0;
  fControlDeltaPhi_hl_nis_uncut               = 0;
  fControlDeltaEta_uncut                      = 0;
  fControlDeltaTheta_uncut                    = 0;
  fControlPtAsymetry_uncut                    = 0;
  fControlPtAsymetry_lu_is_uncut              = 0;
  fControlPtAsymetry_ll_is_uncut              = 0;
  fControlPtAsymetry_hu_is_uncut              = 0;
  fControlPtAsymetry_hl_is_uncut              = 0;
  fControlPtAsymetry_lu_nis_uncut             = 0;
  fControlPtAsymetry_ll_nis_uncut             = 0;
  fControlPtAsymetry_hu_nis_uncut             = 0;
  fControlPtAsymetry_hl_nis_uncut             = 0;
  fControlpt_uncut                            = 0;
  fControlpt_lu_is_uncut                      = 0;
  fControlpt_ll_is_uncut                      = 0;
  fControlpt_hu_is_uncut                      = 0;
  fControlpt_hl_is_uncut                      = 0;
  fControlpt_lu_nis_uncut                     = 0;
  fControlpt_ll_nis_uncut                     = 0;
  fControlpt_hu_nis_uncut                     = 0;
  fControlpt_hl_nis_uncut                     = 0;
 
  fControleta_uncut                           = 0;
  fControleta_lu_is_uncut                     = 0;
  fControleta_ll_is_uncut                     = 0;
  fControleta_hu_is_uncut                     = 0;
  fControleta_hl_is_uncut                     = 0;
  fControleta_lu_nis_uncut                    = 0;
  fControleta_ll_nis_uncut                    = 0;
  fControleta_hu_nis_uncut                    = 0;
  fControleta_hl_nis_uncut                    = 0;
  fControlsqisol_10_uncut                     = 0;
  fControlsqisol_10_is_lu_uncut               = 0;
  fControlsqisol_10_is_ll_uncut               = 0;
  fControlsqisol_10_is_hu_uncut               = 0;
  fControlsqisol_10_is_hl_uncut               = 0;
  fControlsqisol_10_nis_lu_uncut              = 0;
  fControlsqisol_10_nis_ll_uncut              = 0;
  fControlsqisol_10_nis_hu_uncut              = 0;
  fControlsqisol_10_nis_hl_uncut              = 0;

  fControlthrust_uncut                        = 0;
  fControlthrust_is_lu_uncut	              = 0;
  fControlthrust_is_ll_uncut	              = 0;
  fControlthrust_is_hu_uncut	              = 0;
  fControlthrust_is_hl_uncut	              = 0;
  fControlthrust_nis_lu_uncut	              = 0;
  fControlthrust_nis_ll_uncut	              = 0;
  fControlthrust_nis_hu_uncut	              = 0;
  fControlthrust_nis_hl_uncut	              = 0;

  fControlQ2Prime_uncut                       = 0; 
  fControlQ2Prime_is_lu_uncut                 = 0;  
  fControlQ2Prime_is_ll_uncut                 = 0;  
  fControlQ2Prime_is_hu_uncut                 = 0;
  fControlQ2Prime_is_hl_uncut                 = 0;
  fControlQ2Prime_nis_lu_uncut                = 0;
  fControlQ2Prime_nis_ll_uncut                = 0;
  fControlQ2Prime_nis_hu_uncut                = 0;
  fControlQ2Prime_nis_hl_uncut                = 0;

  fControlsphericity_uncut                    = 0; 
  fControlsphericity_is_lu_uncut              = 0;  
  fControlsphericity_is_ll_uncut              = 0;  
  fControlsphericity_is_hu_uncut              = 0;
  fControlsphericity_is_hl_uncut              = 0;
  fControlsphericity_nis_lu_uncut             = 0;
  fControlsphericity_nis_ll_uncut             = 0;
  fControlsphericity_nis_hu_uncut             = 0;
  fControlsphericity_nis_hl_uncut             = 0;

  fControlisotropy_uncut                      = 0;
  fControlisotropy_is_lu_uncut                = 0;
  fControlisotropy_is_ll_uncut                = 0;
  fControlisotropy_is_hu_uncut                = 0;
  fControlisotropy_is_hl_uncut                = 0;
  fControlisotropy_nis_lu_uncut               = 0;
  fControlisotropy_nis_ll_uncut               = 0;
  fControlisotropy_nis_hu_uncut               = 0;
  fControlisotropy_nis_ll_uncut               = 0;
   
  fControlmultiplicity_uncut                  = 0;
  fControlmultiplicity_is_lu_uncut            = 0;
  fControlmultiplicity_is_ll_uncut            = 0;  
  fControlmultiplicity_is_hu_uncut            = 0;
  fControlmultiplicity_is_hl_uncut            = 0;
  fControlmultiplicity_nis_lu_uncut           = 0;
  fControlmultiplicity_nis_ll_uncut           = 0; 
  fControlmultiplicity_nis_hu_uncut           = 0;
  fControlmultiplicity_nis_hl_uncut           = 0;

  fControlImpact2D_uncut                      = 0;
  fControlImpact2D_is_lu_uncut                = 0;
  fControlImpact2D_is_ll_uncut                = 0;  
  fControlImpact2D_is_hu_uncut                = 0;
  fControlImpact2D_is_hl_uncut                = 0;
  fControlImpact2D_nis_lu_uncut               = 0;
  fControlImpact2D_nis_ll_uncut               = 0; 
  fControlImpact2D_nis_hu_uncut               = 0;
  fControlImpact2D_nis_hl_uncut               = 0;

  fControlNperEvGood                          = 0;
  fControlGoodTriMuonMass                     = 0;
  fControlGoodTriMuonMassLow                  = 0;
  fControlGoodTriMuonMassHigh                 = 0;

  fControlGoodMass_lu_is                      = 0;	
  fControlGoodMass_ll_is                      = 0;	
  fControlGoodMass_hu_is                      = 0;	
  fControlGoodMass_hl_is                      = 0;	
  fControlGoodMass_lu_nis                     = 0;
  fControlGoodMass_ll_nis                     = 0;
  fControlGoodMass_hu_nis                     = 0;
  fControlGoodMass_hl_nis                     = 0;

  fControlGoodDeltaR                          = 0;
  fControlGoodDeltaR_lu_is                    = 0;
  fControlGoodDeltaR_ll_is                    = 0;
  fControlGoodDeltaR_hu_is                    = 0;
  fControlGoodDeltaR_hl_is                    = 0;
  fControlGoodDeltaR_lu_nis                   = 0;
  fControlGoodDeltaR_ll_nis                   = 0;
  fControlGoodDeltaR_hu_nis                   = 0;
  fControlGoodDeltaR_hl_nis                   = 0;
  fControlGoodDeltaPhi                        = 0;
  fControlGoodDeltaPhi_lu_is                  = 0;
  fControlGoodDeltaPhi_ll_is                  = 0;
  fControlGoodDeltaPhi_hu_is                  = 0;
  fControlGoodDeltaPhi_hl_is                  = 0;
  fControlGoodDeltaPhi_lu_nis                 = 0;
  fControlGoodDeltaPhi_ll_nis                 = 0;
  fControlGoodDeltaPhi_hu_nis                 = 0;
  fControlGoodDeltaPhi_hl_nis                 = 0;
  fControlGoodDeltaEta                        = 0;
  fControlGoodDeltaTheta                      = 0;
  fControlGoodPtAsymetry                      = 0;
  fControlGoodPtAsymetry_lu_is                = 0;
  fControlGoodPtAsymetry_ll_is                = 0;
  fControlGoodPtAsymetry_hu_is                = 0;
  fControlGoodPtAsymetry_hl_is                = 0;
  fControlGoodPtAsymetry_lu_nis               = 0;
  fControlGoodPtAsymetry_ll_nis               = 0;
  fControlGoodPtAsymetry_hu_nis               = 0;
  fControlGoodPtAsymetry_hl_nis               = 0;
  fControlGoodpt                              = 0;
  fControlGoodpt_lu_is                        = 0;
  fControlGoodpt_ll_is                        = 0;
  fControlGoodpt_hu_is                        = 0;
  fControlGoodpt_hl_is                        = 0;
  fControlGoodpt_lu_nis                       = 0;
  fControlGoodpt_ll_nis                       = 0;
  fControlGoodpt_hu_nis                       = 0;
  fControlGoodpt_hl_nis                       = 0;
 
  fControlGoodeta                             = 0;
  fControlGoodeta_lu_is                       = 0;
  fControlGoodeta_ll_is                       = 0;
  fControlGoodeta_hu_is                       = 0;
  fControlGoodeta_hl_is                       = 0;
  fControlGoodeta_lu_nis                      = 0;
  fControlGoodeta_ll_nis                      = 0;
  fControlGoodeta_hu_nis                      = 0;
  fControlGoodeta_hl_nis                      = 0;
  fControlGoodsqisol_10                       = 0;
  fControlGoodsqisol_10_is_lu                 = 0;
  fControlGoodsqisol_10_is_ll                 = 0;
  fControlGoodsqisol_10_is_hu                 = 0;
  fControlGoodsqisol_10_is_hl                 = 0;
  fControlGoodsqisol_10_nis_lu                = 0;
  fControlGoodsqisol_10_nis_ll                = 0;
  fControlGoodsqisol_10_nis_hu                = 0;
  fControlGoodsqisol_10_nis_hl                = 0;

  fControlGoodthrust                          = 0;
  fControlGoodthrust_is_lu	              = 0;
  fControlGoodthrust_is_ll	              = 0;
  fControlGoodthrust_is_hu	              = 0;
  fControlGoodthrust_is_hl	              = 0;
  fControlGoodthrust_nis_lu	              = 0;
  fControlGoodthrust_nis_ll	              = 0;
  fControlGoodthrust_nis_hu	              = 0;
  fControlGoodthrust_nis_hl	              = 0;

  fControlGoodQ2Prime                         = 0; 
  fControlGoodQ2Prime_is_lu                   = 0;  
  fControlGoodQ2Prime_is_ll                   = 0;  
  fControlGoodQ2Prime_is_hu                   = 0;
  fControlGoodQ2Prime_is_hl                   = 0;
  fControlGoodQ2Prime_nis_lu                  = 0;
  fControlGoodQ2Prime_nis_ll                  = 0;
  fControlGoodQ2Prime_nis_hu                  = 0;
  fControlGoodQ2Prime_nis_hl                  = 0;

  fControlGoodsphericity                      = 0; 
  fControlGoodsphericity_is_lu                = 0;  
  fControlGoodsphericity_is_ll                = 0;  
  fControlGoodsphericity_is_hu                = 0;
  fControlGoodsphericity_is_hl                = 0;
  fControlGoodsphericity_nis_lu               = 0;
  fControlGoodsphericity_nis_ll               = 0;
  fControlGoodsphericity_nis_hu               = 0;
  fControlGoodsphericity_nis_hl               = 0;

  fControlGoodisotropy                        = 0;
  fControlGoodisotropy_is_lu                  = 0;
  fControlGoodisotropy_is_ll                  = 0;
  fControlGoodisotropy_is_hu                  = 0;
  fControlGoodisotropy_is_hl                  = 0;
  fControlGoodisotropy_nis_lu                 = 0;
  fControlGoodisotropy_nis_ll                 = 0;
  fControlGoodisotropy_nis_hu                 = 0;
  fControlGoodisotropy_nis_ll                 = 0;
   
  fControlGoodmultiplicity                    = 0;
  fControlGoodmultiplicity_is_lu              = 0;
  fControlGoodmultiplicity_is_ll              = 0;  
  fControlGoodmultiplicity_is_hu              = 0;
  fControlGoodmultiplicity_is_hl              = 0;
  fControlGoodmultiplicity_nis_lu             = 0;
  fControlGoodmultiplicity_nis_ll             = 0; 
  fControlGoodmultiplicity_nis_hu             = 0;
  fControlGoodmultiplicity_nis_hl             = 0;

  fControlGoodImpact2D                        = 0;
  fControlGoodImpact2D_is_lu                  = 0;
  fControlGoodImpact2D_is_ll                  = 0;  
  fControlGoodImpact2D_is_hu                  = 0;
  fControlGoodImpact2D_is_hl                  = 0;
  fControlGoodImpact2D_nis_lu                 = 0;
  fControlGoodImpact2D_nis_ll                 = 0; 
  fControlGoodImpact2D_nis_hu                 = 0;
  fControlGoodImpact2D_nis_hl                 = 0;

  fControlNperEvChosen                        = 0;
  fControlChosenTriMuonMass                   = 0;
  fControlChosenTriMuonMassLow                = 0;
  fControlChosenTriMuonMassHigh               = 0;

  fControlChosenMass_lu_is                    = 0;	
  fControlChosenMass_ll_is                    = 0;	
  fControlChosenMass_hu_is                    = 0;	
  fControlChosenMass_hl_is                    = 0;	
  fControlChosenMass_lu_nis                   = 0;
  fControlChosenMass_ll_nis                   = 0;
  fControlChosenMass_hu_nis                   = 0;
  fControlChosenMass_hl_nis                   = 0;

  fControlChosenDeltaR                        = 0;
  fControlChosenDeltaR_lu_is                  = 0;
  fControlChosenDeltaR_ll_is                  = 0;
  fControlChosenDeltaR_hu_is                  = 0;
  fControlChosenDeltaR_hl_is                  = 0;
  fControlChosenDeltaR_lu_nis                 = 0;
  fControlChosenDeltaR_ll_nis                 = 0;
  fControlChosenDeltaR_hu_nis                 = 0;
  fControlChosenDeltaR_hl_nis                 = 0;
  fControlChosenDeltaPhi                      = 0;
  fControlChosenDeltaPhi_lu_is                = 0;
  fControlChosenDeltaPhi_ll_is                = 0;
  fControlChosenDeltaPhi_hu_is                = 0;
  fControlChosenDeltaPhi_hl_is                = 0;
  fControlChosenDeltaPhi_lu_nis               = 0;
  fControlChosenDeltaPhi_ll_nis               = 0;
  fControlChosenDeltaPhi_hu_nis               = 0;
  fControlChosenDeltaPhi_hl_nis               = 0;
  fControlChosenDeltaEta                      = 0;
  fControlChosenDeltaTheta                    = 0;
  fControlChosenPtAsymetry                    = 0;
  fControlChosenPtAsymetry_lu_is              = 0;
  fControlChosenPtAsymetry_ll_is              = 0;
  fControlChosenPtAsymetry_hu_is              = 0;
  fControlChosenPtAsymetry_hl_is              = 0;
  fControlChosenPtAsymetry_lu_nis             = 0;
  fControlChosenPtAsymetry_ll_nis             = 0;
  fControlChosenPtAsymetry_hu_nis             = 0;
  fControlChosenPtAsymetry_hl_nis             = 0;
  fControlChosenpt                            = 0;
  fControlChosenpt_lu_is                      = 0;
  fControlChosenpt_ll_is                      = 0;
  fControlChosenpt_hu_is                      = 0;
  fControlChosenpt_hl_is                      = 0;
  fControlChosenpt_lu_nis                     = 0;
  fControlChosenpt_ll_nis                     = 0;
  fControlChosenpt_hu_nis                     = 0;
  fControlChosenpt_hl_nis                     = 0;
 
  fControlChoseneta                           = 0;
  fControlChoseneta_lu_is                     = 0;
  fControlChoseneta_ll_is                     = 0;
  fControlChoseneta_hu_is                     = 0;
  fControlChoseneta_hl_is                     = 0;
  fControlChoseneta_lu_nis                    = 0;
  fControlChoseneta_ll_nis                    = 0;
  fControlChoseneta_hu_nis                    = 0;
  fControlChoseneta_hl_nis                    = 0;
  fControlChosensqisol_10                     = 0;
  fControlChosensqisol_10_is_lu               = 0;
  fControlChosensqisol_10_is_ll               = 0;
  fControlChosensqisol_10_is_hu               = 0;
  fControlChosensqisol_10_is_hl               = 0;
  fControlChosensqisol_10_nis_lu              = 0;
  fControlChosensqisol_10_nis_ll              = 0;
  fControlChosensqisol_10_nis_hu              = 0;
  fControlChosensqisol_10_nis_hl              = 0;

  fControlChosenthrust                        = 0;
  fControlChosenthrust_is_lu	              = 0;
  fControlChosenthrust_is_ll	              = 0;
  fControlChosenthrust_is_hu	              = 0;
  fControlChosenthrust_is_hl	              = 0;
  fControlChosenthrust_nis_lu	              = 0;
  fControlChosenthrust_nis_ll	              = 0;
  fControlChosenthrust_nis_hu	              = 0;
  fControlChosenthrust_nis_hl	              = 0;

  fControlChosenQ2Prime                       = 0; 
  fControlChosenQ2Prime_is_lu                 = 0;  
  fControlChosenQ2Prime_is_ll                 = 0;  
  fControlChosenQ2Prime_is_hu                 = 0;
  fControlChosenQ2Prime_is_hl                 = 0;
  fControlChosenQ2Prime_nis_lu                = 0;
  fControlChosenQ2Prime_nis_ll                = 0;
  fControlChosenQ2Prime_nis_hu                = 0;
  fControlChosenQ2Prime_nis_hl                = 0;

  fControlChosensphericity                    = 0; 
  fControlChosensphericity_is_lu              = 0;  
  fControlChosensphericity_is_ll              = 0;  
  fControlChosensphericity_is_hu              = 0;
  fControlChosensphericity_is_hl              = 0;
  fControlChosensphericity_nis_lu             = 0;
  fControlChosensphericity_nis_ll             = 0;
  fControlChosensphericity_nis_hu             = 0;
  fControlChosensphericity_nis_hl             = 0;

  fControlChosenisotropy                      = 0;
  fControlChosenisotropy_is_lu                = 0;
  fControlChosenisotropy_is_ll                = 0;
  fControlChosenisotropy_is_hu                = 0;
  fControlChosenisotropy_is_hl                = 0;
  fControlChosenisotropy_nis_lu               = 0;
  fControlChosenisotropy_nis_ll               = 0;
  fControlChosenisotropy_nis_hu               = 0;
  fControlChosenisotropy_nis_ll               = 0;
   
  fControlChosenmultiplicity                  = 0;
  fControlChosenmultiplicity_is_lu            = 0;
  fControlChosenmultiplicity_is_ll            = 0;  
  fControlChosenmultiplicity_is_hu            = 0;
  fControlChosenmultiplicity_is_hl            = 0;
  fControlChosenmultiplicity_nis_lu           = 0;
  fControlChosenmultiplicity_nis_ll           = 0; 
  fControlChosenmultiplicity_nis_hu           = 0;
  fControlChosenmultiplicity_nis_hl           = 0;

  fControlChosenImpact2D                      = 0;
  fControlChosenImpact2D_is_lu                = 0;
  fControlChosenImpact2D_is_ll                = 0;  
  fControlChosenImpact2D_is_hu                = 0;
  fControlChosenImpact2D_is_hl                = 0;
  fControlChosenImpact2D_nis_lu               = 0;
  fControlChosenImpact2D_nis_ll               = 0; 
  fControlChosenImpact2D_nis_hu               = 0;
  fControlChosenImpact2D_nis_hl               = 0;

  return kTRUE;
}
