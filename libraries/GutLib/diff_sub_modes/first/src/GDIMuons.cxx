//
// GDIMuons.cxx
//
// $Author: ibloch $
// $Date: 2007/01/04 22:36:00 $
// $Revision: 1.48 $
//

#include <GDIMuons.h>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GDIMuons)
#endif

  GDIMuons *gDIMuons = 0;

//_____________________________________________________________
// GDIMuons
// DiMuon Class for everything which is related only to DiMuons
//
//
GDIMuons::GDIMuons() : GPhysObj() {
  //
  // GDIMuons default constructor
  if ( gDebug ) cout << endl << "GDIMuons::GDIMuons ctor called" << endl << endl;

  // initialize global pointer
  gDIMuons = this;

  // init variables
  InitVariables();

  // init arrays for histograms
  InitArrays();

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GDIMuons::GDIMuons(Int_t dummy) : GPhysObj() {
  //
  // GDIMuons standalone constructor
  if ( gDebug ) cout << endl << "GDIMuons::GDIMuons standalone constructor called" << endl << endl;

  // initialize global pointer
  gDIMuons = this;

  // init variables
  InitVariables();

  // init arrays for histograms
  InitArrays();

}

//_____________________________________________________________

GDIMuons::~GDIMuons() {
  //
  // GDIMuons default destructor
  if ( gDebug ) cout << endl << "GDIMuons::~GDIMuons dtor called" << endl << endl;

  fDIMuons->Delete();
  delete fDIMuons;

}

//_____________________________________________________________

Bool_t GDIMuons::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GDIMuons::Do() called" << endl << endl;

  Fill();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GDIMuons::Reset() called" << endl << endl;

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

  fDoCalcIsolation     = kFALSE;

  fSelectedIndex = -99;

  // reset clonesarray
  fDIMuons->Clear();
  fNDIMuons = 0;

  // reset variables
  fNGoodDIMuons   = 0;
  fNChosenDIMuons = 0;

  fSecvtx_DL2        = 0.;
  fSecvtx_DL2_err    = 0.;
  fSecvtx_DL2_sign   = 0.;
  fSecvtx_DL2_signm  = 0.;
  fSecvtx_DL2_signp  = 0.;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::Fill() {
  //
  // fill clonesarray
  if ( gDebug ) cout << endl << "GDIMuons::Fill() called" << endl << endl;

  if ( gCards->GetDIMUONNDimuons() > 0 ) {

    TClonesArray &dimuons = *fDIMuons;

    for ( Int_t i = 0; i < gMuons->GetNMuons(); ++i ) {
      for ( Int_t j = i+1; j < gMuons->GetNMuons(); ++j ) {
	GMuon *muon1 = gMuons->GetMuon(i);
	GMuon *muon2 = gMuons->GetMuon(j);
	GDIMuon *dimuon = new(dimuons[fNDIMuons++]) GDIMuon(muon1,muon2);
	// Need to reset the isolation cut, as the global reset is called eventwise only.
	dimuon->SetSqSumIsolationCut(kFALSE);
	CheckMuonsAllCut(dimuon);
	if( gCards->GetDoEfficiency() ) {
	  // reset match flag for correctly filling of muon histograms, temp. solution
	  muon1->SetMatched(kFALSE);
	  muon2->SetMatched(kFALSE);
	  CheckMuonsMVCut(dimuon);
	  CheckTrigger(dimuon);
	}
	CheckInvMassCut(dimuon);
	CheckDeltaRCut(dimuon);
	CheckDeltaPhiCut(dimuon);
	CheckDeltaThetaCut(dimuon);
	CheckDeltaEtaCut(dimuon);
	CheckPtAsymetryCut(dimuon);
	CheckEtFractionHighCut(dimuon);
	CheckEtFractionLowCut(dimuon);
	CheckDifChargeCut(dimuon);
	CheckCharmMCJpsiCut(dimuon);
        CheckCharmMCPsiprimeCut(dimuon);// wenn hier gut dann:
	// gZufo->CalcIso(dimuon);
	// in CalcIso() bitte 2 Methoden - eine fuer dimuonen und eine fuer single muonen - die dimuo ruft die singlmuo
	// dabei beachten: Diese Methde muss quasi "check all cuts - cut on isolation" rufen
	// gleiches gilt fuer CalcAllThrusts() - da drin auch das thrustptrel ausrechnen.
	//	if( CheckAllCuts(dimuon, 1)  && fDoCalcIsolation ) {
	if( CheckAllCuts(dimuon, 1) && fDoCalcIsolation ) {
	  gZufo->CalcIsolation( dimuon );
	  CheckSqSumIsolationCut(dimuon);
// 	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
// 	  cout<<"outside ********************************************************* 42*dimuon->GetSqSumIsolationCut() returns: "<<42*dimuon->GetSqSumIsolationCut()<<endl;
	  gZufo->CalcThrust();
          gZufo->CalcInstantonVariables(dimuon);
	  gVertex->CalcSecVTX();
	  //	  gZufo->CalcIsolation( dimuon->GetMuon1() );

	  // 	  if(dimuon->GetMuon1()->GetMCDirectParent()) {
	  // 	    if(dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Jpsi") cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: muon parent is: "<< dimuon->GetMuon1()->GetMCDirectParent()->GetPartID()<<" Is a: "<<dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() <<endl;
	  // 	  }
	  // 	  if(dimuon->GetMuon1()->GetMCQuark()) cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: quark pt is: "<< (dimuon->GetMuon1()->GetMCQuark()->Pt())*(dimuon->GetMuon1()->GetMCQuark()->GetType()==kCharm) <<" q_pt - mc_pt is: "<< (dimuon->GetMuon1()->GetMCQuark()->Pt()*(dimuon->GetMuon1()->GetMCQuark()->GetType()==kCharm)) - gData->Getmc_pt() <<endl;
	  // 	  if( gData->Getmc_pt() )	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: dimu pt is: "<< dimuon->GetdimuPt()<<" dimu_pt/mc_pt is: "<< dimuon->GetdimuPt()/gData->Getmc_pt() <<endl;
	  // nimm: mumc_p(4,nmu)
	  // 	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: dimuon->GetdimuPt() returns: "<<dimuon->GetdimuPt()<<endl;
	  // 	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gZufo->GetThrust() returns: "<<gZufo->GetThrust()<<" phi: "<<gZufo->Getthrust_axis_phi()<<" theta: "<<gZufo->Getthrust_axis_theta()<<" Vector Phi: "<<(180/TMath::Pi())*gZufo->Getthrust_axis().Phi()<<endl;
	  //	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9) returns: "<<gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9)<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9) returns: "<<gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9)<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon1()->GetIsolation10() returns: "<<dimuon->GetMuon1()->GetIsolation10()<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon2()->GetIsolation10() returns: "<<dimuon->GetMuon2()->GetIsolation10()<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 8) returns: "<<gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 8)<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 8) returns: "<<gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 8)<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon1()->GetIsolation09() returns: "<<dimuon->GetMuon1()->GetIsolation09()<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon2()->GetIsolation09() returns: "<<dimuon->GetMuon2()->GetIsolation09()<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 7) returns: "<<gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 7)<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 7) returns: "<<gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 7)<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon1()->GetIsolation08() returns: "<<dimuon->GetMuon1()->GetIsolation08()<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon2()->GetIsolation08() returns: "<<dimuon->GetMuon2()->GetIsolation08()<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 6) returns: "<<gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 6)<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 6) returns: "<<gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 6)<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon1()->GetIsolation07() returns: "<<dimuon->GetMuon1()->GetIsolation07()<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon2()->GetIsolation07() returns: "<<dimuon->GetMuon2()->GetIsolation07()<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 5) returns: "<<gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 5)<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 5) returns: "<<gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 5)<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon1()->GetIsolation06() returns: "<<dimuon->GetMuon1()->GetIsolation06()<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon2()->GetIsolation06() returns: "<<dimuon->GetMuon2()->GetIsolation06()<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 4) returns: "<<gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 4)<<endl;
	  //  	  cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 4) returns: "<<gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 4)<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon1()->GetIsolation05() returns: "<<dimuon->GetMuon1()->GetIsolation05()<<endl;
	  //   	  cout<<"In GDIMuons: GetMuon2()->GetIsolation05() returns: "<<dimuon->GetMuon2()->GetIsolation05()<<endl<<endl<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum01() returns: "<<dimuon->GetIsolationSum01()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum02() returns: "<<dimuon->GetIsolationSum02()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum03() returns: "<<dimuon->GetIsolationSum03()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum04() returns: "<<dimuon->GetIsolationSum04()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum05() returns: "<<dimuon->GetIsolationSum05()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum06() returns: "<<dimuon->GetIsolationSum06()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum07() returns: "<<dimuon->GetIsolationSum07()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum08() returns: "<<dimuon->GetIsolationSum08()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum09() returns: "<<dimuon->GetIsolationSum09()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSum10() returns: "<<dimuon->GetIsolationSum10()<<endl<<endl;

	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum01() returns: "<<dimuon->GetIsolationSqSum01()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum02() returns: "<<dimuon->GetIsolationSqSum02()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum03() returns: "<<dimuon->GetIsolationSqSum03()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum04() returns: "<<dimuon->GetIsolationSqSum04()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum05() returns: "<<dimuon->GetIsolationSqSum05()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum06() returns: "<<dimuon->GetIsolationSqSum06()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum07() returns: "<<dimuon->GetIsolationSqSum07()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum08() returns: "<<dimuon->GetIsolationSqSum08()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum09() returns: "<<dimuon->GetIsolationSqSum09()<<endl;
	  // 	  cout<<"In GDIMuons: dimuon->GetIsolationSqSum10() returns: "<<dimuon->GetIsolationSqSum10()<<endl<<endl;

	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation01() returns: "<<dimuon->GetMuon1()->GetIsolation01()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation02() returns: "<<dimuon->GetMuon1()->GetIsolation02()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation03() returns: "<<dimuon->GetMuon1()->GetIsolation03()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation04() returns: "<<dimuon->GetMuon1()->GetIsolation04()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation05() returns: "<<dimuon->GetMuon1()->GetIsolation05()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation06() returns: "<<dimuon->GetMuon1()->GetIsolation06()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation07() returns: "<<dimuon->GetMuon1()->GetIsolation07()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation08() returns: "<<dimuon->GetMuon1()->GetIsolation08()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation09() returns: "<<dimuon->GetMuon1()->GetIsolation09()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon1()->GetIsolation10() returns: "<<dimuon->GetMuon1()->GetIsolation10()<<endl<<endl;
	  // 	  //	  gZufo->CalcIsolation( dimuon->GetMuon2() );
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation01() returns: "<<dimuon->GetMuon2()->GetIsolation01()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation02() returns: "<<dimuon->GetMuon2()->GetIsolation02()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation03() returns: "<<dimuon->GetMuon2()->GetIsolation03()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation04() returns: "<<dimuon->GetMuon2()->GetIsolation04()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation05() returns: "<<dimuon->GetMuon2()->GetIsolation05()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation06() returns: "<<dimuon->GetMuon2()->GetIsolation06()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation07() returns: "<<dimuon->GetMuon2()->GetIsolation07()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation08() returns: "<<dimuon->GetMuon2()->GetIsolation08()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation09() returns: "<<dimuon->GetMuon2()->GetIsolation09()<<endl;
	  // 	  cout<<"In GDIMuons: GetMuon2()->GetIsolation10() returns: "<<dimuon->GetMuon2()->GetIsolation10()<<endl<<endl;
	}
	CheckAllCuts(dimuon);
	CheckBestDIMuon(dimuon,fNDIMuons-1);
      }
    }

    // flag dimuon fulfilling all cuts with highest ptrel
    if ( fSelectedIndex != -99 )
      DetSelectedCand(fSelectedIndex);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckMuonsAllCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills all muon cuts
  if ( gDebug ) cout << endl << "GDIMuons::CheckMuonsAllCut called" << endl << endl;

  if ( dimuon->GetMuon1()->GetAllCuts() && dimuon->GetMuon2()->GetAllCuts() ) {
    dimuon->SetMuonsAllCuts(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckMuonsMVCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills MV muon cuts
  if ( gDebug ) cout << endl << "GDIMuons::CheckMuonsMVCut called" << endl << endl;

  if ( dimuon->GetMuon1()->GetMVCuts() && dimuon->GetMuon2()->GetMVCuts() ) {
    dimuon->SetMuonsMVCuts(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckInvMassCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills invarant mass cuts
  if ( gDebug ) cout << endl << "GDIMuons::CheckInvMassCut called" << endl << endl;

  if ( ( dimuon->GetInvMass() >= gCards->GetDIMUONInvMassLowCut() ) && ( dimuon->GetInvMass() <= gCards->GetDIMUONInvMassHighCut() ) ) {
    dimuon->SetInvMassCut(kTRUE);
    fInvMassCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckSqSumIsolationCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills requirement to be called *NON*-isolated (sorry!!)
  if ( gDebug ) cout << endl << "GDIMuons::CheckSqSumIsolationCut called" << endl << endl;
//   cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<endl;
//   cout<<"gCards->GetDIMUONSqSumIsolationPeakCut(): "<<gCards->GetDIMUONSqSumIsolationPeakCut()<<endl;
//   cout<<"gCards->GetDIMUONSqSumIsolationContCut(): "<<gCards->GetDIMUONSqSumIsolationContCut()<<endl;
//   cout<<"dimuon->GetInvMass(), dimuon->GetIsolationSqSum10() "<<dimuon->GetInvMass()<<" "<<dimuon->GetIsolationSqSum10()<<endl;
  if( (dimuon->GetInvMass() >= 2.9 && dimuon->GetInvMass() <=3.25 ) || (dimuon->GetInvMass() >= 3.6 && dimuon->GetInvMass() <= 3.75 ) ){
    if ( dimuon->GetIsolationSqSum10() >= gCards->GetDIMUONSqSumIsolationPeakCut() ) {
      dimuon->SetSqSumIsolationCut(kTRUE);
      //      fSqSumIsolationCut = kTRUE;
//       cout<<"In peak:             42*dimuon->GetSqSumIsolationCut() returns: "<<42*dimuon->GetSqSumIsolationCut()<<endl;
    }
  }
  else{
    if ( dimuon->GetIsolationSqSum10() >= gCards->GetDIMUONSqSumIsolationContCut() ) {
      dimuon->SetSqSumIsolationCut(kTRUE);
      //      fSqSumIsolationCut = kTRUE;
//       cout<<"In cont:             42*dimuon->GetSqSumIsolationCut() returns: "<<42*dimuon->GetSqSumIsolationCut()<<endl;
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckDeltaRCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills delta r cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckDeltaRCut called" << endl << endl;

  if ( dimuon->GetDeltaR() >= gCards->GetDIMUONDeltaRCut() ) {
    dimuon->SetDeltaRCut(kTRUE);
    fDeltaRCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckDeltaPhiCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills delta phi
  if ( gDebug ) cout << endl << "GDIMuons::CheckDeltaPhiCut called" << endl << endl;

  if ( TMath::Abs( TMath::Abs(dimuon->GetDeltaPhi())-TMath::Pi() ) > gCards->GetDIMUONDeltaPhiCut() ) {
    dimuon->SetDeltaPhiCut(kTRUE);
    fDeltaPhiCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckDeltaThetaCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills delta theta cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckDeltaThetaCut called" << endl << endl;

  // orig. IB:  delta_theta_mus[0] = TMath::Abs( theta_mu[0] - (TMath::Pi() - theta_mu[1]) );
  //           if ( delta_theta_mus > 5.*TMath::Pi()/1000. && ... ) ...

  if ( TMath::Abs( dimuon->GetMuon1()->Theta() - ( TMath::Pi() - dimuon->GetMuon2()->Theta() ) ) > gCards->GetDIMUONDeltaThetaCut() ) {
    dimuon->SetDeltaThetaCut(kTRUE);
    fDeltaThetaCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckDeltaEtaCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills delta eta cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckDeltaEtaCut called" << endl << endl;

  if ( TMath::Abs( dimuon->GetMuon1()->Eta() - dimuon->GetMuon2()->Eta() ) < gCards->GetDIMUONDeltaEtaCut() ) {
    dimuon->SetDeltaEtaCut(kTRUE);
    fDeltaEtaCut = kTRUE;
  }

  return kTRUE;
}
//_____________________________________________________________

Bool_t GDIMuons::CheckPtAsymetryCut(GDIMuon *dimuon) {
  //
  // check if dimuon fulfills pt asymetry cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckPtAsymetryCut called" << endl << endl;

  // orig. IB:  sqrt(TMath::Power(((mupt[iii]-mupt[jjj])/(mupt[iii]+mupt[jjj])),2)) <= 0.7 // new 031113, estimated crudely from data/MC comparison

  if (  dimuon->GetPtAsymetry() <= gCards->GetDIMUONPtAsymetryCut() ) {
    dimuon->SetPtAsymetryCut(kTRUE);
    fPtAsymetryCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckEtFractionHighCut(GDIMuon *dimuon) {
  //
  // check if dimuon fulfills upper dimumass dependent et fraction cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckEtFractionHighCut called" << endl << endl;

  if(dimuon->GetInvMass() > 4 ){
    if (  dimuon->GetEtFraction() <= gCards->GetDIMUONEtFractionHigh1Cut() ) {
      dimuon->SetEtFractionHighCut(kTRUE);
      fEtFractionHighCut = kTRUE;
    }
  }
  else{
    if (  dimuon->GetEtFraction() <= gCards->GetDIMUONEtFractionHigh2Cut() ) {
      dimuon->SetEtFractionHighCut(kTRUE);
      fEtFractionHighCut = kTRUE;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckEtFractionLowCut(GDIMuon *dimuon) {
  //
  // check if dimuon fulfills lower et fraction cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckEtFractionLowCut called" << endl << endl;

  if (  dimuon->GetEtFraction() >= gCards->GetDIMUONEtFractionLowCut() ) {
    dimuon->SetEtFractionLowCut(kTRUE);
    fEtFractionLowCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckDifChargeCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills different charge cut
  if ( gDebug ) cout << endl << "GDIMuons::CheckDifChargeCut called" << endl << endl;

  if ( gCards->GetDIMUONDifCharge() ) {
    if ( dimuon->GetDifCharge() ) {
      dimuon->SetDifChargeCut(kTRUE);
      fDifChargeCut = kTRUE;
    }
  } else {
    dimuon->SetDifChargeCut(kTRUE);
    fDifChargeCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckCharmMCJpsiCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills CheckCharmMCJpsiCut (i.e. reject Jpsis in Charm MC)
  if ( gDebug ) cout << endl << "GDIMuons::CheckVetoCharmMCJpsiCut called" << endl << endl;

  if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCJpsi() ) { 
    if(dimuon->GetMuon1()->GetMCDirectParent()) {
      if((dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Jpsi")||
         (dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Upsilon1s")||
         (dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Upsilon2s")||
         (dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Upsilon3s")) {
  	fCharmMCJpsiCut = kTRUE;
  	dimuon->SetCharmMCJpsiCut(kTRUE);
      }
    }
    if(dimuon->GetMuon2()->GetMCDirectParent()) {
      if((dimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Jpsi")|| 
         (dimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Upsilon1s")|| 
	 (dimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Upsilon2s")|| 
	 (dimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Upsilon3s")){
  	fCharmMCJpsiCut = kTRUE;
  	dimuon->SetCharmMCJpsiCut(kTRUE);
      }
    }
  }


  //  dimuon->SetCharmMCJpsiCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckCharmMCPsiprimeCut(GDIMuon *dimuon) {
  //
  // check dimuon if muon fulfills CheckCharmMCPsiprimeCut (i.e. reject psiprimes in Charm MC)
  if ( gDebug ) cout << endl << "GDIMuons::CheckVetoCharmMCPsiprimeCut called" << endl << endl;

  if ( gCards->GetMCCCBAR() && gCards->GetDIMUONCharmMCPsiprime() ) { 
    if(dimuon->GetMuon1()->GetMCDirectParent()) {
      if(dimuon->GetMuon1()->GetMCDirectParent()->ReturnParticleType() == "Psiprime") {
  	fCharmMCPsiprimeCut = kTRUE;
  	dimuon->SetCharmMCPsiprimeCut(kTRUE);
      }
    }
    if(dimuon->GetMuon2()->GetMCDirectParent()) {
      if(dimuon->GetMuon2()->GetMCDirectParent()->ReturnParticleType() == "Psiprime") {
  	fCharmMCPsiprimeCut = kTRUE;
  	dimuon->SetCharmMCPsiprimeCut(kTRUE);
      }
    }
  }


  //  dimuon->SetCharmMCPsiprimeCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckTrigger(GDIMuon *dimuon) {
  //
  // check dimuon whether to take both muons, only one muon or none muon for histogram filling (trigger bias)
  if ( gDebug ) cout << endl << "GDIMuons::CheckTrigger called" << endl << endl;

  // distinguish between upgrade and pre-upgrade
  if ( (gGeneral->GetRunPeriod() == k02p)    ||
       (gGeneral->GetRunPeriod() == k03p)    ||
       (gGeneral->GetRunPeriod() == k04p)    ||
       (gGeneral->GetRunPeriod() == k05e)    ||
       (gGeneral->GetRunPeriod() == k06e)    ||
       (gGeneral->GetRunPeriod() == k06p)    ||
       (gGeneral->GetRunPeriod() == k07p)    ||
       (gGeneral->GetRunPeriod() == k03p04p) ||
       (gGeneral->GetRunPeriod() == k05e06e) ||
       (gGeneral->GetRunPeriod() == k06p07p)  ) {
    // check if event triggers any of the HPP, DIS and SPP TLT triggers, then take both
    // mark muon as matched (flag from GMJMatchs, to fill general muon histograms in GMuons (depends on match-flag)
    if ( gTrigger->EventTriggeredByTLTSPP() || gTrigger->EventTriggeredByTLTHPP() || gTrigger->EventTriggeredByTLTDIS() ) {
      dimuon->SetTriggerType(kTakeBoth);
      dimuon->GetMuon1()->SetMatched(kTRUE);
      dimuon->GetMuon2()->SetMatched(kTRUE);
    } else {
      // check if event triggers tlt hfl  1-12,18-22,24 then take both
      // all dis except 27, then take both
      // all exo except 8,9,10,11,12, then take both
      if ( gTrigger->EventTriggeredByTLTHFL(1) ||
	   gTrigger->EventTriggeredByTLTHFL(2) ||
	   gTrigger->EventTriggeredByTLTHFL(3) ||
	   gTrigger->EventTriggeredByTLTHFL(4) ||
	   gTrigger->EventTriggeredByTLTHFL(5) ||
	   gTrigger->EventTriggeredByTLTHFL(6) ||
	   gTrigger->EventTriggeredByTLTHFL(7) ||
	   gTrigger->EventTriggeredByTLTHFL(8) ||
	   gTrigger->EventTriggeredByTLTHFL(9) ||
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
	   gTrigger->EventTriggeredByTLTEXO(1) ||
	   gTrigger->EventTriggeredByTLTEXO(2) ||
	   gTrigger->EventTriggeredByTLTEXO(3) ||
	   gTrigger->EventTriggeredByTLTEXO(4) ||
	   gTrigger->EventTriggeredByTLTEXO(5) ||
	   gTrigger->EventTriggeredByTLTEXO(6) ||
	   gTrigger->EventTriggeredByTLTEXO(7) ||
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
	dimuon->SetTriggerType(kTakeBoth);
	dimuon->GetMuon1()->SetMatched(kTRUE);
	dimuon->GetMuon2()->SetMatched(kTRUE);
      } else {
	// glomu behandlung fuer exo 11,12, muo 3, hfl 13-16.23.25-30,32
	// glomu behandlung: take muon from dimuon which is not found by glomu, if none is found by glomu, take none, if both are found by glomu, take both
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
	  GMuon *muon1 = dimuon->GetMuon1();
	  GMuon *muon2 = dimuon->GetMuon2();

	  if ( muon1->GetGlomu() && !muon2->GetGlomu()) {
	    dimuon->SetTriggerType(kTakeMuon2);
	    dimuon->GetMuon2()->SetMatched(kTRUE);
	  } else if ( !muon1->GetGlomu() && muon2->GetGlomu()) {
	    dimuon->SetTriggerType(kTakeMuon1);
	    dimuon->GetMuon1()->SetMatched(kTRUE);
	  } else if ( muon1->GetGlomu() && muon2->GetGlomu()) {
	    dimuon->SetTriggerType(kTakeBoth);
	    dimuon->GetMuon1()->SetMatched(kTRUE);
	    dimuon->GetMuon2()->SetMatched(kTRUE);
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
	  GMuon *muon1 = dimuon->GetMuon1();
	  GMuon *muon2 = dimuon->GetMuon2();

	  if ( (muon1->GetType() == kForward) && (muon2->GetType() == kForward) ) {
	    dimuon->SetTriggerType(kTakeBoth);
	    dimuon->GetMuon1()->SetMatched(kTRUE);
	    dimuon->GetMuon2()->SetMatched(kTRUE);
	  } else if ( muon1->GetType() == kForward ) {
	    if ( muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon1);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	    } else {
	      dimuon->SetTriggerType(kTakeBoth);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    }
	  } else if ( muon2->GetType() == kForward ) {
	    if ( muon1->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon2);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    } else {
	      dimuon->SetTriggerType(kTakeBoth);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    }
	  } else {
	    if ( muon1->GetGlomu() && !muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon2);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    } else if ( !muon1->GetGlomu() && muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon1);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	    } else if ( muon1->GetGlomu() && muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeBoth);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    } 
	  }
	} else if ( gTrigger->EventTriggeredByTLTVTX()) {
	  // for MC, if event is only triggered by vtxm take both
	  dimuon->SetTriggerType(kTakeBoth);
	  dimuon->GetMuon1()->SetMatched(kTRUE);
	  dimuon->GetMuon2()->SetMatched(kTRUE);
	}
      }
    }
  } else {
    // check if event triggers any of the HPP and SPP TLT triggers, then take both
    // mark muon as matched (flag from GMJMatchs, to fill general muon histograms in GMuons (depends on match-flag)
    if ( gTrigger->EventTriggeredByTLTSPP() || gTrigger->EventTriggeredByTLTHPP()) {
      dimuon->SetTriggerType(kTakeBoth);
      dimuon->GetMuon1()->SetMatched(kTRUE);
      dimuon->GetMuon2()->SetMatched(kTRUE);
    } else {
      // check if event triggers tlt hfl 3,4,5,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24, then take both
      // all dis except 27, then take both
      // all exo except 8,9,10,11,12, then take both
      if ( gTrigger->EventTriggeredByTLTHFL(3) ||
	   gTrigger->EventTriggeredByTLTHFL(4) ||
	   gTrigger->EventTriggeredByTLTHFL(5) ||
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
	   gTrigger->EventTriggeredByTLTDIS(1) ||
	   gTrigger->EventTriggeredByTLTDIS(2) ||
	   gTrigger->EventTriggeredByTLTDIS(3) ||
	   gTrigger->EventTriggeredByTLTDIS(4) ||
	   gTrigger->EventTriggeredByTLTDIS(5) ||
	   gTrigger->EventTriggeredByTLTDIS(6) ||
	   gTrigger->EventTriggeredByTLTDIS(7) ||
	   gTrigger->EventTriggeredByTLTDIS(8) ||
	   gTrigger->EventTriggeredByTLTDIS(9) ||
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
	   gTrigger->EventTriggeredByTLTEXO(1) ||
	   gTrigger->EventTriggeredByTLTEXO(2) ||
	   gTrigger->EventTriggeredByTLTEXO(3) ||
	   gTrigger->EventTriggeredByTLTEXO(4) ||
	   gTrigger->EventTriggeredByTLTEXO(5) ||
	   gTrigger->EventTriggeredByTLTEXO(6) ||
	   gTrigger->EventTriggeredByTLTEXO(7) ||
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
	dimuon->SetTriggerType(kTakeBoth);
	dimuon->GetMuon1()->SetMatched(kTRUE);
	dimuon->GetMuon2()->SetMatched(kTRUE);
      } else {
	// glomu behandlung fuer exo 11,12, muo 3, hfl 1, dis 27
	// glomu behandlung: take muon from dimuon which is not found by glomu, if none is found by glomu, take none, if both are found by glomu, take both
	if ( gTrigger->EventTriggeredByTLTEXO(11) ||
	     gTrigger->EventTriggeredByTLTEXO(12) ||
	     gTrigger->EventTriggeredByTLTHFL(1) ||
	     gTrigger->EventTriggeredByTLTDIS(27) ) {
	  GMuon *muon1 = dimuon->GetMuon1();
	  GMuon *muon2 = dimuon->GetMuon2();

	  if ( muon1->GetGlomu() && !muon2->GetGlomu()) {
	    dimuon->SetTriggerType(kTakeMuon2);
	    dimuon->GetMuon2()->SetMatched(kTRUE);
	  } else if ( !muon1->GetGlomu() && muon2->GetGlomu()) {
	    dimuon->SetTriggerType(kTakeMuon1);
	    dimuon->GetMuon1()->SetMatched(kTRUE);
	  } else if ( muon1->GetGlomu() && muon2->GetGlomu()) {
	    dimuon->SetTriggerType(kTakeBoth);
	    dimuon->GetMuon1()->SetMatched(kTRUE);
	    dimuon->GetMuon2()->SetMatched(kTRUE);
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
	  GMuon *muon1 = dimuon->GetMuon1();
	  GMuon *muon2 = dimuon->GetMuon2();

	  if ( (muon1->GetType() == kForward) && (muon2->GetType() == kForward) ) {
	    dimuon->SetTriggerType(kTakeBoth);
	    dimuon->GetMuon1()->SetMatched(kTRUE);
	    dimuon->GetMuon2()->SetMatched(kTRUE);
	  } else if ( muon1->GetType() == kForward ) {
	    if ( muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon1);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	    } else {
	      dimuon->SetTriggerType(kTakeBoth);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    }
	  } else if ( muon2->GetType() == kForward ) {
	    if ( muon1->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon2);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    } else {
	      dimuon->SetTriggerType(kTakeBoth);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    }
	  } else {
	    if ( muon1->GetGlomu() && !muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon2);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    } else if ( !muon1->GetGlomu() && muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeMuon1);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	    } else if ( muon1->GetGlomu() && muon2->GetGlomu()) {
	      dimuon->SetTriggerType(kTakeBoth);
	      dimuon->GetMuon1()->SetMatched(kTRUE);
	      dimuon->GetMuon2()->SetMatched(kTRUE);
	    } 
	  }
	} else if ( gTrigger->EventTriggeredByTLTVTX()) {
	  // for MC, if event is only triggered by vtxm take both
	  dimuon->SetTriggerType(kTakeBoth);
	  dimuon->GetMuon1()->SetMatched(kTRUE);
	  dimuon->GetMuon2()->SetMatched(kTRUE);
	}
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckAllCuts(GDIMuon *dimuon, Int_t flag ) {
  //
  // check dimuon if dimuon fulfills all cuts
  if ( gDebug ) cout << endl << "GDIMuons::CheckAllCuts called" << endl << endl;

  // take dimuon which muon fulfill all muon cuts or all MV muon cuts, and then 
  // check for all dimuon specific cuts
  
  // reset bool in case several dimuons are found:
  fDoCalcIsolation = kFALSE;
 
  if ( ( (dimuon->GetMuonsAllCuts() && !gCards->GetDoEfficiency()) || ( dimuon->GetMuonsMVCuts() && gCards->GetDoEfficiency()) ) &&
       dimuon->GetInvMassCut() &&
       dimuon->GetDeltaRCut() &&
       ( dimuon->GetDeltaPhiCut() || dimuon->GetDeltaThetaCut()) &&
       dimuon->GetDeltaEtaCut()       &&
       dimuon->GetPtAsymetryCut()     &&
       dimuon->GetEtFractionHighCut() &&
       dimuon->GetEtFractionLowCut()  &&
       dimuon->GetDifChargeCut()      &&
       !dimuon->GetCharmMCJpsiCut()   &&
       !dimuon->GetCharmMCPsiprimeCut()) {
    if(flag == 0)      dimuon->SetAllCuts(kTRUE);
    if(flag == 0)      dimuon->SetType(kGoodDIMuon);
    if(flag == 0)      fNGoodDIMuons += 1;
    if(flag == 0)      fAllCuts = kTRUE;
    if(flag == 1)      fDoCalcIsolation = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CheckBestDIMuon(GDIMuon *dimuon, Int_t index) {
  //
  // determine index of best dimuon
  if ( gDebug ) cout << endl << "GDIMuons::CheckBestDIMuon called" << endl << endl;

  // take all dimuons
  if ( 42 == 42 ) {
    if ( dimuon->GetAllCuts()) {
      dimuon->SetType(kChosenDIMuon);
      fNChosenDIMuons += 1;
    }
  } 
  // take the first
  else if ( fSelectedIndex == -99 ) {
    if ( dimuon->GetAllCuts()) {
      fSelectedIndex = index;
      fNChosenDIMuons += 1;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::DetSelectedCand(Int_t index) {
  //
  // flag best dimuon fullfilling all cuts
  if ( gDebug ) cout << endl << "GDIMuons::DetSelectedCand called" << endl << endl;

  if ( index != -99 ) {
    GetDIMuon(index)->SetType(kChosenDIMuon);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::GetAllCuts() {
  //
  // returns true if event fulfills all muon-jet-dimuon cuts
  if ( gDebug ) cout << endl << "GDIMuons::GetAllCuts() called" << endl << endl;

  if ( gCards->GetDIMUONNDimuons() <= 0 )
    return kTRUE;
  else if ( fAllCuts )
    return kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

Bool_t GDIMuons::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GDIMuons::CreateControl() called" << endl << endl;
  
  if ( gCards->GetDIMUONControl()) {
  
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
    Int_t    dimuptbins     = 140;
    Double_t dimuptlow      = 0.;
    Double_t dimupthigh     = 35.0;
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
    Double_t q2primehigh       = 2000.0;

    fControlNperEv_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","NperEv_uncut","uncut n_{#mu#mu}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu}","Events");
    fControlDIMuonMass_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DIMuonMass_uncut","uncut #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fControlDIMuonMassLow_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DIMuonMassLow_uncut","uncut low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fControlDIMuonMassHigh_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DIMuonMassHigh_uncut","uncut high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fControlMass_lu_is_uncut  = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_lu_is_uncut","uncut #mass_lu_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_ll_is_uncut  = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_ll_is_uncut","uncut #mass_ll_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hu_is_uncut  = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_hu_is_uncut","uncut #mass_hu_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hl_is_uncut  = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_hl_is_uncut","uncut #mass_hl_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_lu_nis_uncut","uncut #mass_lu_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_ll_nis_uncut","uncut #mass_ll_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_hu_nis_uncut","uncut #mass_hu_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{uncut} [GeV]","Events");
    fControlMass_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Mass_hl_nis_uncut","uncut #mass_hl_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{uncut} [GeV]","Events");

    fControlDeltaR_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_uncut","uncut #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR","Events");
    fControlDeltaR_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_lu_is_uncut","uncut #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_is","Events");
    fControlDeltaR_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_ll_is_uncut","uncut #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_is","Events");
    fControlDeltaR_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_hu_is_uncut","uncut #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_is","Events");
    fControlDeltaR_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_hl_is_uncut","uncut #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_is","Events");
    fControlDeltaR_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_lu_nis_uncut","uncut #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_nis","Events");
    fControlDeltaR_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_ll_nis_uncut","uncut #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_nis","Events");
    fControlDeltaR_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_hu_nis_uncut","uncut #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_nis","Events");
    fControlDeltaR_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaR_hl_nis_uncut","uncut #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_nis","Events");

    fControlDeltaPhi_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_uncut","uncut #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","Events");
    fControlDeltaPhi_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_lu_is_uncut","uncut #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_is","Events");
    fControlDeltaPhi_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_ll_is_uncut","uncut #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_is","Events");
    fControlDeltaPhi_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_hu_is_uncut","uncut #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_is","Events");
    fControlDeltaPhi_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_hl_is_uncut","uncut #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_is","Events");
    fControlDeltaPhi_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_lu_nis_uncut","uncut #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_nis","Events");
    fControlDeltaPhi_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_ll_nis_uncut","uncut #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_nis","Events");
    fControlDeltaPhi_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_hu_nis_uncut","uncut #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_nis","Events");
    fControlDeltaPhi_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaPhi_hl_nis_uncut","uncut #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_nis","Events");

    fControlDeltaEta_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaEta_uncut","uncut #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta","Events");
    fControlDeltaTheta_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","DeltaTheta_uncut","uncut #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta","Events");

    fControlPtAsymetry_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_uncut","uncut p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.","Events");
    fControlPtAsymetry_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_lu_is_uncut","uncut_lu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.","Events");
    fControlPtAsymetry_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_ll_is_uncut","uncut_ll_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.","Events");
    fControlPtAsymetry_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_hu_is_uncut","uncut_hu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.","Events");
    fControlPtAsymetry_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_hl_is_uncut","uncut_hl_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.","Events");
    fControlPtAsymetry_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_lu_nis_uncut","uncut_lu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.","Events");
    fControlPtAsymetry_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_ll_nis_uncut","uncut_ll_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.","Events");
    fControlPtAsymetry_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_hu_nis_uncut","uncut_hu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.","Events");
    fControlPtAsymetry_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","PtAsymetry_hl_nis_uncut","uncut_hl_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.","Events");

    fControlpt_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_uncut","uncut p_{T}",ptbins,ptlow,pthigh,"p_{T}","Events");
    fControlpt_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_lu_is_uncut","uncut_lu_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_is","Events");
    fControlpt_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_ll_is_uncut","uncut_ll_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_is","Events");
    fControlpt_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_hu_is_uncut","uncut_hu_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_is","Events");
    fControlpt_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_hl_is_uncut","uncut_hl_is p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_is","Events");
    fControlpt_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_lu_nis_uncut","uncut_lu_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_nis","Events");
    fControlpt_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_ll_nis_uncut","uncut_ll_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_nis","Events");
    fControlpt_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_hu_nis_uncut","uncut_hu_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_nis","Events");
    fControlpt_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","pt_hl_nis_uncut","uncut_hl_nis p_{T}",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_nis","Events");

    fControldimupt_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_uncut","uncut p_{T}",dimuptbins,dimuptlow,dimupthigh,"p_{T}","Events");
    fControldimupt_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_lu_is_uncut","uncut_lu_is p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_lu_is","Events");
    fControldimupt_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_ll_is_uncut","uncut_ll_is p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_ll_is","Events");
    fControldimupt_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_hu_is_uncut","uncut_hu_is p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hu_is","Events");
    fControldimupt_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_hl_is_uncut","uncut_hl_is p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hl_is","Events");
    fControldimupt_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_lu_nis_uncut","uncut_lu_nis p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_lu_nis","Events");
    fControldimupt_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_ll_nis_uncut","uncut_ll_nis p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_ll_nis","Events");
    fControldimupt_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_hu_nis_uncut","uncut_hu_nis p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hu_nis","Events");
    fControldimupt_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","dimupt_hl_nis_uncut","uncut_hl_nis p_{T}",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hl_nis","Events");

    fControleta_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_uncut","uncut #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fControleta_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_lu_is_uncut","uncut_lu_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_lu_is","Events");
    fControleta_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_ll_is_uncut","uncut_ll_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_ll_is","Events");
    fControleta_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_hu_is_uncut","uncut_hu_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hu_is","Events");
    fControleta_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_hl_is_uncut","uncut_hl_is #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hl_is","Events");
    fControleta_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_lu_nis_uncut","uncut_lu_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_lu_nis","Events");
    fControleta_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_ll_nis_uncut","uncut_ll_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_ll_nis","Events");
    fControleta_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_hu_nis_uncut","uncut_hu_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hu_nis","Events");
    fControleta_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","eta_hl_nis_uncut","uncut_hl_nis #eta_{#mu}",etabins,etalow,etahigh,"#eta_{#mu}_hl_nis","Events");

    //     fControlsqisol_10_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_uncut","uncut sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    //     fControlsqisol_10_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_lu_uncut","uncut_lu sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}_lu","Events");
    //     fControlsqisol_10_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_ll_uncut","uncut_ll sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}_ll","Events");
    //     fControlsqisol_10_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_hu_uncut","uncut_hu sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}_hu","Events");
    //     fControlsqisol_10_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_hl_uncut","uncut_hl sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}_hl","Events");

    fControlsqisol_10_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_uncut","uncut sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    fControlsqisol_10_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_is_lu_uncut","uncut_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_lu","Events");
    fControlsqisol_10_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_is_ll_uncut","uncut_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_ll","Events");
    fControlsqisol_10_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_is_hu_uncut","uncut_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hu","Events");
    fControlsqisol_10_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_is_hl_uncut","uncut_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hl","Events");
    fControlsqisol_10_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_nis_lu_uncut","uncut_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_lu","Events");
    fControlsqisol_10_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_nis_ll_uncut","uncut_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_ll","Events");
    fControlsqisol_10_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_nis_hu_uncut","uncut_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hu","Events");
    fControlsqisol_10_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sqisol_10_nis_hl_uncut","uncut_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hl","Events");

    fControlthrust_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_uncut","uncut thrust",thrustbins,thrustlow,thrusthigh,"#thrust","Events");
    fControlthrust_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_lu_uncut","uncut_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_lu","Events");
    fControlthrust_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_ll_uncut","uncut_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_ll","Events");
    fControlthrust_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_hu_uncut","uncut_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hu","Events");
    fControlthrust_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_hl_uncut","uncut_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hl","Events");
    fControlthrust_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_lu_uncut","uncut_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_lu","Events");
    fControlthrust_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_ll_uncut","uncut_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_ll","Events");
    fControlthrust_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_hu_uncut","uncut_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hu","Events");
    fControlthrust_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_hl_uncut","uncut_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hl","Events");

//********************************************************
// Here Histograms for Instanton Variables
//********************************************************

    fControlQ2Prime_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_uncut","uncut Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2}","Events");
    fControlQ2Prime_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_lu_uncut","uncut_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_lu","Events");
    fControlQ2Prime_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_ll_uncut","uncut_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_ll","Events");
    fControlQ2Prime_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_hu_uncut","uncut_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hu","Events");
    fControlQ2Prime_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_hl_uncut","uncut_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hl","Events");
    fControlQ2Prime_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_lu_uncut","uncut_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_lu","Events");
    fControlQ2Prime_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_ll_uncut","uncut_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_ll","Events");
    fControlQ2Prime_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_hu_uncut","uncut_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hu","Events");
    fControlQ2Prime_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_hl_uncut","uncut_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hl","Events");

    fControlsphericity_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_uncut","uncut sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity","Events");
    fControlsphericity_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_lu_uncut","uncut_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_lu","Events");
    fControlsphericity_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_ll_uncut","uncut_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_ll","Events");
    fControlsphericity_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_hu_uncut","uncut_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hu","Events");
    fControlsphericity_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_hl_uncut","uncut_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hl","Events");
    fControlsphericity_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_lu_uncut","uncut_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_lu","Events");
    fControlsphericity_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_ll_uncut","uncut_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_ll","Events");
    fControlsphericity_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_hu_uncut","uncut_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hu","Events");
    fControlsphericity_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_hl_uncut","uncut_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hl","Events");

    fControlisotropy_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_uncut","uncut isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy","Events");
    fControlisotropy_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_lu_uncut","uncut_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_lu","Events");
    fControlisotropy_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_ll_uncut","uncut_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_ll","Events");
    fControlisotropy_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_hu_uncut","uncut_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hu","Events");
    fControlisotropy_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_hl_uncut","uncut_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hl","Events");
    fControlisotropy_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_lu_uncut","uncut_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_lu","Events");
    fControlisotropy_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_ll_uncut","uncut_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_ll","Events");
    fControlisotropy_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_hu_uncut","uncut_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hu","Events");
    fControlisotropy_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_hl_uncut","uncut_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hl","Events");

    fControlmultiplicity_uncut    = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_uncut","uncut multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity","Events");
    fControlmultiplicity_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_lu_uncut","uncut_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_lu","Events");
    fControlmultiplicity_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_ll_uncut","uncut_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_ll","Events");
    fControlmultiplicity_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_hu_uncut","uncut_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hu","Events");
    fControlmultiplicity_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_hl_uncut","uncut_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hl","Events");
    fControlmultiplicity_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_lu_uncut","uncut_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_lu","Events");
    fControlmultiplicity_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_ll_uncut","uncut_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_ll","Events");
    fControlmultiplicity_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_hu_uncut","uncut_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hu","Events");
    fControlmultiplicity_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_hl_uncut","uncut_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hl","Events");

//*******************************************************

    fControlNperEvGood = gHistogrammer->TH1DFactory("DIMuon_Control","NperEvGood","n_{#mu#mu,good}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu}^{good}","Events");
    fControlGoodDIMuonMass = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDIMuonMass","good #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodDIMuonMassLow = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDIMuonMassLow","good low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodDIMuonMassHigh = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDIMuonMassHigh","good high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");

    fControlGoodMass_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_lu_is_uncut","good #mass_lu_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_ll_is_uncut","good #mass_ll_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_hu_is_uncut","good #mass_hu_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_hl_is_uncut","good #mass_hl_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_lu_nis_uncut","good #mass_lu_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_ll_nis_uncut","good #mass_ll_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_hu_nis_uncut","good #mass_hu_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");
    fControlGoodMass_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodMass_hl_nis_uncut","good #mass_hl_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{good} [GeV]","Events");

    fControlGoodDeltaR = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR","good #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}","Events");
    fControlGoodDeltaR_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_lu_is","good #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_lu_is","Events");
    fControlGoodDeltaR_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_ll_is","good #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_ll_is","Events");
    fControlGoodDeltaR_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_hu_is","good #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hu_is","Events");
    fControlGoodDeltaR_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_hl_is","good #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hl_is","Events");
    fControlGoodDeltaR_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_lu_nis","good #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_lu_nis","Events");
    fControlGoodDeltaR_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_ll_nis","good #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_ll_nis","Events");
    fControlGoodDeltaR_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_hu_nis","good #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hu_nis","Events");
    fControlGoodDeltaR_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaR_hl_nis","good #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{good}_hl_nis","Events");

    fControlGoodDeltaPhi = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi","good #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}","Events");
    fControlGoodDeltaPhi_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_lu_is","good #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_lu_is","Events");
    fControlGoodDeltaPhi_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_ll_is","good #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_ll_is","Events");
    fControlGoodDeltaPhi_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_hu_is","good #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hu_is","Events");
    fControlGoodDeltaPhi_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_hl_is","good #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hl_is","Events");
    fControlGoodDeltaPhi_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_lu_nis","good #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_lu_nis","Events");
    fControlGoodDeltaPhi_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_ll_nis","good #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_ll_nis","Events");
    fControlGoodDeltaPhi_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_hu_nis","good #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hu_nis","Events");
    fControlGoodDeltaPhi_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaPhi_hl_nis","good #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{good}_hl_nis","Events");

    fControlGoodDeltaEta = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaEta","good #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta^{good}","Events");
    fControlGoodDeltaTheta = gHistogrammer->TH1DFactory("DIMuon_Control","GoodDeltaTheta","good #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta^{good}","Events");

    fControlGoodPtAsymetry = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry","good p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.^{good}","Events");
    fControlGoodPtAsymetry_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_lu_is","good_lu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.^{good}","Events");
    fControlGoodPtAsymetry_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_ll_is","good_ll_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.^{good}","Events");
    fControlGoodPtAsymetry_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_hu_is","good_hu_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.^{good}","Events");
    fControlGoodPtAsymetry_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_hl_is","good_hl_is p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.^{good}","Events");
    fControlGoodPtAsymetry_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_lu_nis","good_lu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.^{good}","Events");
    fControlGoodPtAsymetry_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_ll_nis","good_ll_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.^{good}","Events");
    fControlGoodPtAsymetry_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_hu_nis","good_hu_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.^{good}","Events");
    fControlGoodPtAsymetry_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","GoodPtAsymetry_hl_nis","good_hl_nis p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.^{good}","Events");
    fControlGoodpt = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt","good p_{T} ",ptbins,ptlow,pthigh,"p_{T}^{good}","Events");
    fControlGoodpt_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_lu_is","good #pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_lu_is","Events");
    fControlGoodpt_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_ll_is","good #pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_ll_is","Events");
    fControlGoodpt_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_hu_is","good #pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hu_is","Events");
    fControlGoodpt_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_hl_is","good #pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hl_is","Events");
    fControlGoodpt_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_lu_nis","good #pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_lu_nis","Events");
    fControlGoodpt_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_ll_nis","good #pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_ll_nis","Events");
    fControlGoodpt_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_hu_nis","good #pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hu_nis","Events");
    fControlGoodpt_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodpt_hl_nis","good #pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{good}_hl_nis","Events");
    fControlGooddimupt = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt","good p_{T} ",dimuptbins,dimuptlow,dimupthigh,"dimup_{T}^{good}","Events");
    fControlGooddimupt_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_lu_is","good #dimupt_{#mu}_lu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_lu_is","Events");
    fControlGooddimupt_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_ll_is","good #dimupt_{#mu}_ll_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_ll_is","Events");
    fControlGooddimupt_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_hu_is","good #dimupt_{#mu}_hu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_hu_is","Events");
    fControlGooddimupt_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_hl_is","good #dimupt_{#mu}_hl_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_hl_is","Events");
    fControlGooddimupt_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_lu_nis","good #dimupt_{#mu}_lu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_lu_nis","Events");
    fControlGooddimupt_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_ll_nis","good #dimupt_{#mu}_ll_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_ll_nis","Events");
    fControlGooddimupt_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_hu_nis","good #dimupt_{#mu}_hu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_hu_nis","Events");
    fControlGooddimupt_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Gooddimupt_hl_nis","good #dimupt_{#mu}_hl_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{good}_hl_nis","Events");
    fControlGoodeta = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta","good #eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu}^{good}","Events");
    fControlGoodeta_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_lu_is","good #eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_lu_is","Events");
    fControlGoodeta_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_ll_is","good #eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_ll_is","Events");
    fControlGoodeta_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_hu_is","good #eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hu_is","Events");
    fControlGoodeta_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_hl_is","good #eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hl_is","Events");
    fControlGoodeta_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_lu_nis","good #eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_lu_nis","Events");
    fControlGoodeta_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_ll_nis","good #eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_ll_nis","Events");
    fControlGoodeta_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_hu_nis","good #eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hu_nis","Events");
    fControlGoodeta_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Goodeta_hl_nis","good #eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{good}_hl_nis","Events");

    fControlGoodsqisol_10    = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10","good sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}^{good}","Events");
    fControlGoodsqisol_10_is_lu = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_is_lu","good_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_lu","Events");
    fControlGoodsqisol_10_is_ll = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_is_ll","good_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_ll","Events");
    fControlGoodsqisol_10_is_hu = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_is_hu","good_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_hu","Events");
    fControlGoodsqisol_10_is_hl = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_is_hl","good_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{good}_hl","Events");
    fControlGoodsqisol_10_nis_lu = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_nis_lu","good_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_lu","Events");
    fControlGoodsqisol_10_nis_ll = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_nis_ll","good_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_ll","Events");
    fControlGoodsqisol_10_nis_hu = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_nis_hu","good_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_hu","Events");
    fControlGoodsqisol_10_nis_hl = gHistogrammer->TH1DFactory("DIMuon_Control","Goodsqisol_10_nis_hl","good_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{good}_hl","Events");

    fControlGoodthrust    = gHistogrammer->TH1DFactory("DIMuon_Control","thrust","good thrust",thrustbins,thrustlow,thrusthigh,"#thrust^{good}","Events");
    fControlGoodthrust_is_lu = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_lu","good_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_lu","Events");
    fControlGoodthrust_is_ll = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_ll","good_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_ll","Events");
    fControlGoodthrust_is_hu = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_hu","good_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_hu","Events");
    fControlGoodthrust_is_hl = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_is_hl","good_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_is_hl","Events");
    fControlGoodthrust_nis_lu = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_lu","good_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_lu","Events");
    fControlGoodthrust_nis_ll = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_ll","good_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_ll","Events");
    fControlGoodthrust_nis_hu = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_hu","good_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_hu","Events");
    fControlGoodthrust_nis_hl = gHistogrammer->TH1DFactory("DIMuon_Control","thrust_nis_hl","good_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{good}_nis_hl","Events");

//********************************************************
// Here Histograms for Instanton Variables
//********************************************************

    fControlGoodQ2Prime    = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime","good Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}","Events");
    fControlGoodQ2Prime_is_lu = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_lu","good_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_lu","Events");
    fControlGoodQ2Prime_is_ll = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_ll","good_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_ll","Events");
    fControlGoodQ2Prime_is_hu = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_hu","good_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_hu","Events");
    fControlGoodQ2Prime_is_hl = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_is_hl","good_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_is_hl","Events");
    fControlGoodQ2Prime_nis_lu = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_lu","good_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_lu","Events");
    fControlGoodQ2Prime_nis_ll = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_ll","good_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_ll","Events");
    fControlGoodQ2Prime_nis_hu = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_hu","good_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_hu","Events");
    fControlGoodQ2Prime_nis_hl = gHistogrammer->TH1DFactory("DIMuon_Control","Q2Prime_nis_hl","good_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, good}_nis_hl","Events");

    fControlGoodsphericity     = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity","good sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}","Events");
    fControlGoodsphericity_is_lu = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_lu","good_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_lu","Events");
    fControlGoodsphericity_is_ll = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_ll","good_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_ll","Events");
    fControlGoodsphericity_is_hu = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_hu","good_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_hu","Events");
    fControlGoodsphericity_is_hl = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_is_hl","good_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_is_hl","Events");
    fControlGoodsphericity_nis_lu = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_lu","good_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_lu","Events");
    fControlGoodsphericity_nis_ll = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_ll","good_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_ll","Events");
    fControlGoodsphericity_nis_hu = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_hu","good_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_hu","Events");
    fControlGoodsphericity_nis_hl = gHistogrammer->TH1DFactory("DIMuon_Control","sphericity_nis_hl","good_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{good}_nis_hl","Events");

    fControlGoodisotropy     = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy","good isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}","Events");
    fControlGoodisotropy_is_lu = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_lu","good_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_lu","Events");
    fControlGoodisotropy_is_ll = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_ll","good_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_ll","Events");
    fControlGoodisotropy_is_hu = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_hu","good_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_hu","Events");
    fControlGoodisotropy_is_hl = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_is_hl","good_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_is_hl","Events");
    fControlGoodisotropy_nis_lu = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_lu","good_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_lu","Events");
    fControlGoodisotropy_nis_ll = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_ll","good_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_ll","Events");
    fControlGoodisotropy_nis_hu = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_hu","good_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_hu","Events");
    fControlGoodisotropy_nis_hl = gHistogrammer->TH1DFactory("DIMuon_Control","isotropy_nis_hl","good_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{good}_nis_hl","Events");

    fControlGoodmultiplicity    = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity","good multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}","Events");
    fControlGoodmultiplicity_is_lu = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_lu","good_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_lu","Events");
    fControlGoodmultiplicity_is_ll = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_ll","good_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_ll","Events");
    fControlGoodmultiplicity_is_hu = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_hu","good_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_hu","Events");
    fControlGoodmultiplicity_is_hl = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_is_hl","good_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_is_hl","Events");
    fControlGoodmultiplicity_nis_lu = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_lu","good_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_lu","Events");
    fControlGoodmultiplicity_nis_ll = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_ll","good_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_ll","Events");
    fControlGoodmultiplicity_nis_hu = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_hu","good_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_hu","Events");
    fControlGoodmultiplicity_nis_hl = gHistogrammer->TH1DFactory("DIMuon_Control","multiplicity_nis_hl","good_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{good}_nis_hl","Events");

//*******************************************************
   
    fControlNperEvChosen = gHistogrammer->TH1DFactory("DIMuon_Control","NperEvChosen","n_{#mu#mu,chosen}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu}^{chosen}","Events");
    fControlChosenDIMuonMass = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDIMuonMass","chosen #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenDIMuonMassLow = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDIMuonMassLow","chosen low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenDIMuonMassHigh = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDIMuonMassHigh","chosen high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");

    fControlChosenMass_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_lu_is_uncut","chosen #mass_lu_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_ll_is_uncut","chosen #mass_ll_is",massbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_hu_is_uncut","chosen #mass_hu_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_hl_is_uncut","chosen #mass_hl_is",massbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_lu_nis_uncut","chosen #mass_lu_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_ll_nis_uncut","chosen #mass_ll_nis",massbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_hu_nis_uncut","chosen #mass_hu_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");
    fControlChosenMass_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenMass_hl_nis_uncut","chosen #mass_hl_nis",massbins,masshighlow,masshighhigh,"m_{#mu#mu,inv}^{chosen} [GeV]","Events");

    fControlChosenDeltaR = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR","chosen #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}","Events");
    fControlChosenDeltaR_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_lu_is","chosen #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_lu_is","Events");
    fControlChosenDeltaR_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_ll_is","chosen #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_ll_is","Events");
    fControlChosenDeltaR_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_hu_is","chosen #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hu_is","Events");
    fControlChosenDeltaR_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_hl_is","chosen #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hl_is","Events");
    fControlChosenDeltaR_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_lu_nis","chosen #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_lu_nis","Events");
    fControlChosenDeltaR_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_ll_nis","chosen #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_ll_nis","Events");
    fControlChosenDeltaR_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_hu_nis","chosen #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hu_nis","Events");
    fControlChosenDeltaR_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaR_hl_nis","chosen #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR^{chosen}_hl_nis","Events");

    fControlChosenDeltaPhi = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi","chosen #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}","Events");
    fControlChosenDeltaPhi_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_lu_is","chosen #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_lu_is","Events");
    fControlChosenDeltaPhi_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_ll_is","chosen #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_ll_is","Events");
    fControlChosenDeltaPhi_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_hu_is","chosen #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hu_is","Events");
    fControlChosenDeltaPhi_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_hl_is","chosen #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hl_is","Events");
    fControlChosenDeltaPhi_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_lu_nis","chosen #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_lu_nis","Events");
    fControlChosenDeltaPhi_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_ll_nis","chosen #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_ll_nis","Events");
    fControlChosenDeltaPhi_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_hu_nis","chosen #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hu_nis","Events");
    fControlChosenDeltaPhi_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaPhi_hl_nis","chosen #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi^{chosen}_hl_nis","Events");

    fControlChosenDeltaEta = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaEta","chosen #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta^{chosen}","Events");
    fControlChosenDeltaTheta = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenDeltaTheta","chosen #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta^{chosen}","Events");

    fControlChosenPtAsymetry = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry","chosen p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"uncut p_{T} asym.^{chosen}","Events");
    fControlChosenPtAsymetry_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_lu_is","chosen p_{T}_lu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_ll_is","chosen p_{T}_ll_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_hu_is","chosen p_{T}_hu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_hl_is","chosen p_{T}_hl_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.^{chosen}","Events");
    fControlChosenPtAsymetry_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_lu_nis","chosen p_{T}_lu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.^{chosen}","Events");
    fControlChosenPtAsymetry_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_ll_nis","chosen p_{T}_ll_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_hu_nis","chosen p_{T}_hu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.^{chosen}","Events");
    fControlChosenPtAsymetry_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","ChosenPtAsymetry_hl_nis","chosen p_{T}_hl_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.^{chosen}","Events");

    fControlChosenpt = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt","chosen p_{T} ",ptbins,ptlow,pthigh,"p_{T}^{chosen}","Events");
    fControlChosenpt_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_lu_is","chosen #pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_lu_is","Events");
    fControlChosenpt_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_ll_is","chosen #pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_ll_is","Events");
    fControlChosenpt_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_hu_is","chosen #pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hu_is","Events");
    fControlChosenpt_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_hl_is","chosen #pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hl_is","Events");
    fControlChosenpt_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_lu_nis","chosen #pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_lu_nis","Events");
    fControlChosenpt_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_ll_nis","chosen #pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_ll_nis","Events");
    fControlChosenpt_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_hu_nis","chosen #pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hu_nis","Events");
    fControlChosenpt_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosenpt_hl_nis","chosen #pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}^{chosen}_hl_nis","Events");

    fControlChosendimupt = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt","chosen p_{T} ",dimuptbins,dimuptlow,dimupthigh,"p_{T}dimu^{chosen}","Events");
    fControlChosendimupt_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_lu_is","chosen #dimupt_{#mu}_lu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_lu_is","Events");
    fControlChosendimupt_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_ll_is","chosen #dimupt_{#mu}_ll_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_ll_is","Events");
    fControlChosendimupt_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_hu_is","chosen #dimupt_{#mu}_hu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_hu_is","Events");
    fControlChosendimupt_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_hl_is","chosen #dimupt_{#mu}_hl_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_hl_is","Events");
    fControlChosendimupt_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_lu_nis","chosen #dimupt_{#mu}_lu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_lu_nis","Events");
    fControlChosendimupt_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_ll_nis","chosen #dimupt_{#mu}_ll_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_ll_nis","Events");
    fControlChosendimupt_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_hu_nis","chosen #dimupt_{#mu}_hu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_hu_nis","Events");
    fControlChosendimupt_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Chosendimupt_hl_nis","chosen #dimupt_{#mu}_hl_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}^{chosen}_hl_nis","Events");

    fControlChoseneta = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta","chosen #eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}","Events");
    fControlChoseneta_lu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_lu_is","chosen #eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_lu_is","Events");
    fControlChoseneta_ll_is = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_ll_is","chosen #eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_ll_is","Events");
    fControlChoseneta_hu_is = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_hu_is","chosen #eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hu_is","Events");
    fControlChoseneta_hl_is = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_hl_is","chosen #eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hl_is","Events");
    fControlChoseneta_lu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_lu_nis","chosen #eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_lu_nis","Events");
    fControlChoseneta_ll_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_ll_nis","chosen #eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_ll_nis","Events");
    fControlChoseneta_hu_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_hu_nis","chosen #eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hu_nis","Events");
    fControlChoseneta_hl_nis = gHistogrammer->TH1DFactory("DIMuon_Control","Choseneta_hl_nis","chosen #eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}^{chosen}_hl_nis","Events");

    fControlChosensqisol_10    = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10   ","chosen sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}^{chosen}","Events");
    fControlChosensqisol_10_is_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_is_lu","chosen_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_lu","Events");
    fControlChosensqisol_10_is_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_is_ll","chosen_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_ll","Events");
    fControlChosensqisol_10_is_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_is_hu","chosen_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_hu","Events");
    fControlChosensqisol_10_is_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_is_hl","chosen_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}^{chosen}_hl","Events");
    fControlChosensqisol_10_nis_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_nis_lu","chosen_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_lu","Events");
    fControlChosensqisol_10_nis_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_nis_ll","chosen_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_ll","Events");
    fControlChosensqisol_10_nis_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_nis_hu","chosen_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_hu","Events");
    fControlChosensqisol_10_nis_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Chosensqisol_10_nis_hl","chosen_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}^{chosen}_hl","Events");

    fControlChosenthrust    = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust","chosen thrust",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}","Events");
    fControlChosenthrust_is_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_is_lu","chosen_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_lu","Events");
    fControlChosenthrust_is_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_is_ll","chosen_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_ll","Events");
    fControlChosenthrust_is_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_is_hu","chosen_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_hu","Events");
    fControlChosenthrust_is_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_is_hl","chosen_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_is_hl","Events");
    fControlChosenthrust_nis_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_nis_lu","chosen_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_lu","Events");
    fControlChosenthrust_nis_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_nis_ll","chosen_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_ll","Events");
    fControlChosenthrust_nis_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_nis_hu","chosen_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_hu","Events");
    fControlChosenthrust_nis_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","thrust_nis_hl","chosen_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust^{chosen}_nis_hl","Events");

//********************************************************
// Here Histograms for Instanton Variables
//********************************************************

    fControlChosenQ2Prime    = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime","chosen Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}","Events");
    fControlChosenQ2Prime_is_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_is_lu","chosen_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_lu","Events");
    fControlChosenQ2Prime_is_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_is_ll","chosen_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_ll","Events");
    fControlChosenQ2Prime_is_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_is_hu","chosen_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_hu","Events");
    fControlChosenQ2Prime_is_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_is_hl","chosen_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_is_hl","Events");
    fControlChosenQ2Prime_nis_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_nis_lu","chosen_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_lu","Events");
    fControlChosenQ2Prime_nis_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_nis_ll","chosen_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_ll","Events");
    fControlChosenQ2Prime_nis_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_nis_hu","chosen_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_hu","Events");
    fControlChosenQ2Prime_nis_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","Q2Prime_nis_hl","chosen_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2, chosen}_nis_hl","Events");

    fControlChosensphericity     = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity","chosen sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}","Events");
    fControlChosensphericity_is_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_is_lu","chosen_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_lu","Events");
    fControlChosensphericity_is_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_is_ll","chosen_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_ll","Events");
    fControlChosensphericity_is_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_is_hu","chosen_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_hu","Events");
    fControlChosensphericity_is_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_is_hl","chosen_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_is_hl","Events");
    fControlChosensphericity_nis_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_nis_lu","chosen_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_lu","Events");
    fControlChosensphericity_nis_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_nis_ll","chosen_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_ll","Events");
    fControlChosensphericity_nis_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_nis_hu","chosen_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_hu","Events");
    fControlChosensphericity_nis_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","sphericity_nis_hl","chosen_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity^{chosen}_nis_hl","Events");

    fControlChosenisotropy     = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy","chosen isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}","Events");
    fControlChosenisotropy_is_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_is_lu","chosen_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_lu","Events");
    fControlChosenisotropy_is_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_is_ll","chosen_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_ll","Events");
    fControlChosenisotropy_is_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_is_hu","chosen_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_hu","Events");
    fControlChosenisotropy_is_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_is_hl","chosen_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_is_hl","Events");
    fControlChosenisotropy_nis_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_nis_lu","chosen_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_lu","Events");
    fControlChosenisotropy_nis_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_nis_ll","chosen_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_ll","Events");
    fControlChosenisotropy_nis_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_nis_hu","chosen_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_hu","Events");
    fControlChosenisotropy_nis_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","isotropy_nis_hl","chosen_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy^{chosen}_nis_hl","Events");

    fControlChosenmultiplicity    = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity","chosen multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}","Events");
    fControlChosenmultiplicity_is_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_is_lu","chosen_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_lu","Events");
    fControlChosenmultiplicity_is_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_is_ll","chosen_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_ll","Events");
    fControlChosenmultiplicity_is_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_is_hu","chosen_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_hu","Events");
    fControlChosenmultiplicity_is_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_is_hl","chosen_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_is_hl","Events");
    fControlChosenmultiplicity_nis_lu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_nis_lu","chosen_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_lu","Events");
    fControlChosenmultiplicity_nis_ll = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_nis_ll","chosen_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_ll","Events");
    fControlChosenmultiplicity_nis_hu = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_nis_hu","chosen_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_hu","Events");
    fControlChosenmultiplicity_nis_hl = gHistogrammer->TH1DFactory("DIMuon_ControlChosen","multiplicity_nis_hl","chosen_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity^{chosen}_nis_hl","Events");


//*******************************************************

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::FillControl() {
  //
  // fill control histograms
  if ( gDebug ) cout << endl << "GDIMuons::FillControl() called" << endl << endl;

  if ( gCards->GetDIMUONControl()) {

    fControlNperEv_uncut->Fill(fNDIMuons);
    fControlNperEvGood->Fill(fNGoodDIMuons);
    fControlNperEvChosen->Fill(fNChosenDIMuons);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GDIMuons::FillHistos() called" << endl << endl;

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GDIMuons::ObjectsFillHistos() called" << endl << endl;

  // loop over array
  for ( Int_t i = 0; i < fNDIMuons; i++ ) {
    GDIMuon *dimuon = ((GDIMuon*)(fDIMuons->At(i)));

    // fill control plots
    ObjectsFillControl(dimuon);

    // fill general plots
    ObjectsFillGeneral(dimuon);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::ObjectsFillControl(GDIMuon *dimuon) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GDIMuons::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetDIMUONControl()) {

    Double_t invMass    = dimuon->GetInvMass();
    Double_t deltaR     = dimuon->GetDeltaR();
    Double_t deltaPhi   = dimuon->GetDeltaPhi();
    Double_t deltaEta   = dimuon->GetDeltaEta();
    Double_t deltaTheta = dimuon->GetDeltaTheta();
    Double_t ptAsymetry = dimuon->GetPtAsymetry();
    //    Double_t etFraction = dimuon->GetEtFraction();
    Double_t IsolationSqSum10 = dimuon->GetIsolationSqSum10();

    Double_t thrust       = gZufo->GetThrust();
    Double_t sphericity   = gZufo->GetSphericity();
    Double_t multiplicity = gZufo->GetMultiplicity();
    Double_t Q2Prime      = gZufo->GetQ2Prime();
    Double_t isotropy     = gZufo->GetIsotropy();

    fControlDIMuonMass_uncut->Fill(invMass);
    if(invMass <= 4 )
      fControlDIMuonMassLow_uncut->Fill(invMass,gHeader->GetWeight());
    if(invMass > 4 )
      fControlDIMuonMassHigh_uncut->Fill(invMass,gHeader->GetWeight());

    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {      
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlMass_lu_is_uncut->Fill(invMass,gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlMass_ll_is_uncut->Fill(invMass,gHeader->GetWeight());  
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlMass_hu_is_uncut->Fill(invMass,gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlMass_hl_is_uncut->Fill(invMass,gHeader->GetWeight());
    }						      
    else{					      
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlMass_lu_nis_uncut->Fill(invMass,gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlMass_ll_nis_uncut->Fill(invMass,gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlMass_hu_nis_uncut->Fill(invMass,gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlMass_hl_nis_uncut->Fill(invMass,gHeader->GetWeight());
    }                                                 

    fControlDeltaR_uncut->Fill(deltaR,gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlDeltaR_lu_is_uncut->Fill(deltaR,gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlDeltaR_ll_is_uncut->Fill(deltaR,gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlDeltaR_hu_is_uncut->Fill(deltaR,gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlDeltaR_hl_is_uncut->Fill(deltaR,gHeader->GetWeight());
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlDeltaR_lu_nis_uncut->Fill(deltaR,gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlDeltaR_ll_nis_uncut->Fill(deltaR,gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlDeltaR_hu_nis_uncut->Fill(deltaR,gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlDeltaR_hl_nis_uncut->Fill(deltaR,gHeader->GetWeight());
    }                     
                            
    fControlDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlDeltaPhi_lu_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlDeltaPhi_ll_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlDeltaPhi_hu_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlDeltaPhi_hl_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlDeltaPhi_lu_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlDeltaPhi_ll_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlDeltaPhi_hu_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlDeltaPhi_hl_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
    }
    
    fControlDeltaEta_uncut   -> Fill(deltaEta,gHeader->GetWeight());
    fControlDeltaTheta_uncut -> Fill(deltaTheta,gHeader->GetWeight());

    fControlPtAsymetry_uncut->Fill(ptAsymetry,gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlPtAsymetry_lu_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlPtAsymetry_ll_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlPtAsymetry_hu_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlPtAsymetry_hl_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlPtAsymetry_lu_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControlPtAsymetry_ll_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControlPtAsymetry_hu_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControlPtAsymetry_hl_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
    }

    fControlpt_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
    fControlpt_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	fControlpt_lu_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlpt_lu_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
      }
      if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	fControlpt_ll_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	fControlpt_ll_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
      }
      if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	fControlpt_hu_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlpt_hu_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
      }
      if(invMass > 4  && !dimuon->GetDifCharge())  { 
	fControlpt_hl_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	fControlpt_hl_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
      }
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	fControlpt_lu_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlpt_lu_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
      }
      if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	fControlpt_ll_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	fControlpt_ll_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
      }
      if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	fControlpt_hu_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	fControlpt_hu_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
      }
      if(invMass > 4  && !dimuon->GetDifCharge())  {  
	fControlpt_hl_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	fControlpt_hl_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
      }
    }

    fControldimupt_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControldimupt_lu_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControldimupt_ll_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControldimupt_hu_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControldimupt_hl_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())    fControldimupt_lu_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if(invMass <= 4 && !dimuon->GetDifCharge())    fControldimupt_ll_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if(invMass > 4  &&  dimuon->GetDifCharge())    fControldimupt_hu_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if(invMass > 4  && !dimuon->GetDifCharge())    fControldimupt_hl_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
    }

    fControleta_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
    fControleta_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	fControleta_lu_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_lu_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
      if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	fControleta_ll_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_ll_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
      if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	fControleta_hu_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_hu_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
      if(invMass > 4  && !dimuon->GetDifCharge())  { 
	fControleta_hl_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_hl_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	fControleta_lu_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	fControleta_lu_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
      }
      if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	fControleta_ll_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_ll_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
      if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	fControleta_hu_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_hu_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
      if(invMass > 4  && !dimuon->GetDifCharge())  {  
	fControleta_hl_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControleta_hl_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      }
    }

    fControlsqisol_10_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fControlsqisol_10_is_lu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
      if(invMass <= 4 && !dimuon->GetDifCharge())  {  fControlsqisol_10_is_ll_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
      if(invMass > 4  &&  dimuon->GetDifCharge())  {  fControlsqisol_10_is_hu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
      if(invMass > 4  && !dimuon->GetDifCharge())  {  fControlsqisol_10_is_hl_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); } 
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fControlsqisol_10_nis_lu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
      if(invMass <= 4 && !dimuon->GetDifCharge())  {  fControlsqisol_10_nis_ll_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
      if(invMass > 4  &&  dimuon->GetDifCharge())  {  fControlsqisol_10_nis_hu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
      if(invMass > 4  && !dimuon->GetDifCharge())  {  fControlsqisol_10_nis_hl_uncut->Fill( IsolationSqSum10,gHeader->GetWeight()); }
    }

    /*
    cout<<" "<< endl;;
    cout<<"******* Uncut Muons Control Histrograms ********"<< endl;
    cout<<" "<< endl;
    cout<<"Eventnr: "<< gData->Geteventnr() << endl;
    cout<<" " << endl;
    cout<<"1st Muon Pt:  "<< setw(8) << dimuon->GetMuon1()->Pt()  <<", 2nd Muon Pt:  "<< setw(8) << dimuon->GetMuon2()->Pt() << endl;
    cout<<"1st Muon Eta: "<< setw(8) << dimuon->GetMuon1()->Eta() <<", 2nd Muon Eta: "<< setw(8) << dimuon->GetMuon2()->Eta() << endl;
    
    cout<<"Dimuon Pt:    "<< setw(8) << dimuon->GetdimuPt()       <<", Dimuon Eta:   "<< setw(8) << dimuon->GetEta() << endl;
    cout<<"Isolation:    "<< setw(8) << IsolationSqSum10          <<", Pt asym:      "<< setw(8) << ptAsymetry << setw(8) <<", Delta Eta: "<< deltaEta <<endl;
    cout<<"Isolation Muon 1: " << setw(8) << gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9) <<", Isolation Muon 2: " << setw(8) << gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9) << endl;
    cout<<"Nachgerechnete Dimuon Isolation: " << TMath::Sqrt(TMath::Power(gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9),2)+TMath::Power(gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9),2)) << endl;
    cout<<"1st Muon Quality: " << setw(8) << dimuon->GetMuon1()->GetQuality() <<", 2nd Muon Quality: " << setw(8) << dimuon->GetMuon2()->GetQuality() << endl;
    */
// Event shape distributions

    if(gData->Getkt_njet_a()==0){
      fControlthrust_uncut  -> Fill(thrust      ,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlthrust_is_lu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	if(invMass <= 4 && !dimuon->GetDifCharge()) fControlthrust_is_ll_uncut -> Fill( thrust, gHeader->GetWeight()); 
	if(invMass > 4  &&  dimuon->GetDifCharge()) fControlthrust_is_hu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	if(invMass > 4  && !dimuon->GetDifCharge()) fControlthrust_is_hl_uncut -> Fill( thrust, gHeader->GetWeight()); 
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlthrust_nis_lu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	if(invMass <= 4 && !dimuon->GetDifCharge()) fControlthrust_nis_ll_uncut -> Fill( thrust, gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fControlthrust_nis_hu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	if(invMass > 4  && !dimuon->GetDifCharge()) fControlthrust_nis_hl_uncut -> Fill( thrust, gHeader->GetWeight()); 
      }
    }

    fControlsphericity_uncut   -> Fill( sphericity,      gHeader->GetWeight());
    fControlisotropy_uncut     -> Fill( isotropy,        gHeader->GetWeight());
    fControlQ2Prime_uncut      -> Fill( Q2Prime,         gHeader->GetWeight());
    fControlmultiplicity_uncut -> Fill( multiplicity,    gHeader->GetWeight());
 
    if( !dimuon->GetSqSumIsolationCut()) {      
      //    if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
      if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	fControlsphericity_is_lu_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	fControlisotropy_is_lu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_is_lu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_is_lu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
      if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	fControlsphericity_is_ll_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	fControlisotropy_is_ll_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_is_ll_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_is_ll_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
      if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	fControlsphericity_is_hu_uncut   -> Fill( sphericity,      gHeader->GetWeight());
	fControlisotropy_is_hu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_is_hu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_is_hu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
      if(invMass > 4  && !dimuon->GetDifCharge())  {
	fControlsphericity_is_hl_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	fControlisotropy_is_hl_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_is_hl_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_is_hl_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      } 
    }
    else{
      if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	fControlsphericity_nis_lu_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	fControlisotropy_nis_lu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_nis_lu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_nis_lu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
      if(invMass <= 4 && !dimuon->GetDifCharge())  {
	fControlsphericity_nis_ll_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	fControlisotropy_nis_ll_uncut     -> Fill( isotropy,        gHeader->GetWeight());
	fControlmultiplicity_nis_ll_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_nis_ll_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
      if(invMass > 4  &&  dimuon->GetDifCharge())  {
	fControlsphericity_nis_hu_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	fControlisotropy_nis_hu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_nis_hu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	fControlQ2Prime_nis_hu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
      if(invMass > 4  && !dimuon->GetDifCharge())  { 
	fControlsphericity_nis_hl_uncut   -> Fill( sphericity,      gHeader->GetWeight());
	fControlisotropy_nis_hl_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	fControlmultiplicity_nis_hl_uncut -> Fill( multiplicity ,   gHeader->GetWeight()); 
	fControlQ2Prime_nis_hl_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
      }
    }
      
    if( ( dimuon->GetType() == kGoodDIMuon ) || ( dimuon->GetType() == kChosenDIMuon )) {
      
      if( dimuon->GetInvMassCut()) {
	fControlGoodDIMuonMass->Fill(invMass,gHeader->GetWeight());
	if(invMass <= 4 )
	  fControlGoodDIMuonMassLow->Fill(invMass,gHeader->GetWeight());
	if(invMass > 4 )
	  fControlGoodDIMuonMassHigh->Fill(invMass,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())   fControlGoodMass_lu_is->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass <= 4 && !dimuon->GetDifCharge())   fControlGoodMass_ll_is->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass > 4  &&  dimuon->GetDifCharge())   fControlGoodMass_hu_is->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass > 4  && !dimuon->GetDifCharge())   fControlGoodMass_hl_is->Fill(invMass,gHeader->GetWeight()); 
	}						     			                      
	else{					     			                      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())   fControlGoodMass_lu_nis->Fill(invMass,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())   fControlGoodMass_ll_nis->Fill(invMass,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())   fControlGoodMass_hu_nis->Fill(invMass,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())   fControlGoodMass_hl_nis->Fill(invMass,gHeader->GetWeight());
	}                                                 
      }
      if( dimuon->GetDeltaRCut()) {
	fControlGoodDeltaR->Fill(deltaR,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlGoodDeltaR_lu_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlGoodDeltaR_ll_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlGoodDeltaR_hu_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlGoodDeltaR_hl_is->Fill(deltaR,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlGoodDeltaR_lu_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlGoodDeltaR_ll_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlGoodDeltaR_hu_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlGoodDeltaR_hl_nis->Fill(deltaR,gHeader->GetWeight());
	}
      }
      if( dimuon->GetDeltaPhiCut()) {
	fControlGoodDeltaPhi->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlGoodDeltaPhi_lu_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlGoodDeltaPhi_ll_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlGoodDeltaPhi_hu_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlGoodDeltaPhi_hl_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlGoodDeltaPhi_lu_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlGoodDeltaPhi_ll_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlGoodDeltaPhi_hu_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlGoodDeltaPhi_hl_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	}
      }
      fControlGoodDeltaEta->Fill(deltaEta,gHeader->GetWeight());
      if( dimuon->GetDeltaThetaCut())
	fControlGoodDeltaTheta->Fill(deltaTheta,gHeader->GetWeight());
      if( dimuon->GetPtAsymetryCut()) {
	fControlGoodPtAsymetry->Fill(ptAsymetry,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlGoodPtAsymetry_lu_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlGoodPtAsymetry_ll_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlGoodPtAsymetry_hu_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlGoodPtAsymetry_hl_is->Fill(ptAsymetry,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlGoodPtAsymetry_lu_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlGoodPtAsymetry_ll_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlGoodPtAsymetry_hu_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlGoodPtAsymetry_hl_nis->Fill(ptAsymetry,gHeader->GetWeight());
	}
      
	fControlGoodpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlGoodpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fControlGoodpt_lu_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlGoodpt_lu_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fControlGoodpt_ll_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlGoodpt_ll_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fControlGoodpt_hu_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fControlGoodpt_hu_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlGoodpt_hl_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fControlGoodpt_hl_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fControlGoodpt_lu_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fControlGoodpt_lu_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge()) {
	    fControlGoodpt_ll_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fControlGoodpt_ll_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fControlGoodpt_hu_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fControlGoodpt_hu_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlGoodpt_hl_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fControlGoodpt_hl_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	}

 	fControlGooddimupt->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) {  fControlGooddimupt_lu_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass <= 4 && !dimuon->GetDifCharge()) {  fControlGooddimupt_ll_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  &&  dimuon->GetDifCharge()) {  fControlGooddimupt_hu_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  && !dimuon->GetDifCharge()) {  fControlGooddimupt_hl_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) { fControlGooddimupt_lu_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge()) { fControlGooddimupt_ll_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge()) { fControlGooddimupt_hu_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge()) { fControlGooddimupt_hl_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	}

	fControlGoodeta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControlGoodeta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	    fControlGoodeta_lu_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fControlGoodeta_lu_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge()) { 
	    fControlGoodeta_ll_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlGoodeta_ll_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge()) { 
	    fControlGoodeta_hu_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fControlGoodeta_hu_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge()) { 
	    fControlGoodeta_hl_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlGoodeta_hl_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fControlGoodeta_lu_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlGoodeta_lu_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fControlGoodeta_ll_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlGoodeta_ll_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fControlGoodeta_hu_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlGoodeta_hu_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlGoodeta_hl_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlGoodeta_hl_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}

	fControlGoodsqisol_10->Fill( IsolationSqSum10,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fControlGoodsqisol_10_is_lu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fControlGoodsqisol_10_is_ll->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fControlGoodsqisol_10_is_hu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fControlGoodsqisol_10_is_hl->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	}	
	else {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fControlGoodsqisol_10_nis_lu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fControlGoodsqisol_10_nis_ll->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fControlGoodsqisol_10_nis_hu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fControlGoodsqisol_10_nis_hl->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	}
	/*
        cout<<" "<< endl;
	cout<<"******* Good Muons Control Histrograms ********"<< endl;
	cout<<" "<< endl;
        cout<<"Eventnr: "<< gData->Geteventnr() << endl;
        cout<<" " << endl;
	cout<<"1st Muon Pt:  "<< setw(8) << dimuon->GetMuon1()->Pt()  <<", 2nd Muon Pt:  "<< setw(8) << dimuon->GetMuon2()->Pt() << endl;
        cout<<"1st Muon Eta: "<< setw(8) << dimuon->GetMuon1()->Eta() <<", 2nd Muon Eta: "<< setw(8) << dimuon->GetMuon2()->Eta() << endl;
        cout<<"Dimuon Pt:    "<< setw(8) << dimuon->GetdimuPt()       <<", Dimuon Eta:   "<< setw(8) << dimuon->GetEta() << endl;
        cout<<"Isolation:    "<< setw(8) << IsolationSqSum10          <<", Pt asym:      "<< setw(8) << ptAsymetry << setw(8) <<", Delta Eta: "<< deltaEta <<endl;
	cout<<"Isolation Muon 1: " << setw(8) << gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9) <<" Isolation Muon 2: " << setw(8) << gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9) << endl;
	cout<<"Nachgerechnete Dimuon Isolation: " << TMath::Sqrt(TMath::Power(gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9),2)+TMath::Power(gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9),2)) << endl;
	cout<<"1st Muon Quality: " << setw(8) << dimuon->GetMuon1()->GetQuality() <<", 2nd Muon Quality: " << setw(8) << dimuon->GetMuon2()->GetQuality() << endl;
	*/
// Event shape distributions

	if(gData->Getkt_njet_a()==0){
	  fControlGoodthrust       -> Fill(thrust      ,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlGoodthrust_is_lu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fControlGoodthrust_is_ll -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fControlGoodthrust_is_hu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  && !dimuon->GetDifCharge()) fControlGoodthrust_is_hl -> Fill( thrust, gHeader->GetWeight()); 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlGoodthrust_nis_lu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fControlGoodthrust_nis_ll -> Fill( thrust, gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fControlGoodthrust_nis_hu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  && !dimuon->GetDifCharge()) fControlGoodthrust_nis_hl -> Fill( thrust, gHeader->GetWeight()); 
	  }
	}

        fControlGoodsphericity   -> Fill(sphericity  ,gHeader->GetWeight());
        fControlGoodisotropy     -> Fill(isotropy    ,gHeader->GetWeight());
        fControlGoodmultiplicity -> Fill(multiplicity,gHeader->GetWeight());
        fControlGoodQ2Prime      -> Fill(Q2Prime     ,gHeader->GetWeight());
      
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fControlGoodsphericity_is_lu   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_is_lu     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_lu -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_lu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {
	    fControlGoodsphericity_is_ll   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_is_ll     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_ll -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_ll      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fControlGoodsphericity_is_hu   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_is_hu     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_hu -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_hu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlGoodsphericity_is_hl   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_is_hl     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_is_hl -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_is_hl      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fControlGoodsphericity_nis_lu   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_lu     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_lu -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_lu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fControlGoodsphericity_nis_ll   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_ll     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_ll -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_ll      -> Fill( Q2Prime,         gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fControlGoodsphericity_nis_hu   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_hu     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_hu -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlGoodQ2Prime_nis_hu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fControlGoodsphericity_nis_hl   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlGoodisotropy_nis_hl     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlGoodmultiplicity_nis_hl -> Fill( multiplicity,    gHeader->GetWeight());
	    fControlGoodQ2Prime_nis_hl      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	}
      }
    }
        
    if( dimuon->GetType() == kChosenDIMuon ) {

      if( dimuon->GetInvMassCut()) {
	fControlChosenDIMuonMass->Fill(invMass,gHeader->GetWeight());
	if(invMass <= 4 )
	  fControlChosenDIMuonMassLow->Fill(invMass,gHeader->GetWeight());
	if(invMass > 4 )
	  fControlChosenDIMuonMassHigh->Fill(invMass,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
    	  if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlChosenMass_lu_is->Fill(invMass,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())    fControlChosenMass_ll_is->Fill(invMass,gHeader->GetWeight());  
	  if(invMass > 4  &&  dimuon->GetDifCharge())    fControlChosenMass_hu_is->Fill(invMass,gHeader->GetWeight());  
	  if(invMass > 4  && !dimuon->GetDifCharge())    fControlChosenMass_hl_is->Fill(invMass,gHeader->GetWeight());  
	}						      
	else{					      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())    fControlChosenMass_lu_nis->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass <= 4 && !dimuon->GetDifCharge())    fControlChosenMass_ll_nis->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass > 4  &&  dimuon->GetDifCharge())    fControlChosenMass_hu_nis->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass > 4  && !dimuon->GetDifCharge())    fControlChosenMass_hl_nis->Fill(invMass,gHeader->GetWeight()); 
	}                                                 
      }
      if( dimuon->GetDeltaRCut()) {
	fControlChosenDeltaR->Fill(deltaR,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
     	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fControlChosenDeltaR_lu_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fControlChosenDeltaR_ll_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fControlChosenDeltaR_hu_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fControlChosenDeltaR_hl_is->Fill(deltaR,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fControlChosenDeltaR_lu_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fControlChosenDeltaR_ll_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fControlChosenDeltaR_hu_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fControlChosenDeltaR_hl_nis->Fill(deltaR,gHeader->GetWeight());
	}
      }
      if( dimuon->GetDeltaPhiCut()) {
	fControlChosenDeltaPhi->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
    	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlChosenDeltaPhi_lu_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fControlChosenDeltaPhi_ll_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fControlChosenDeltaPhi_hu_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fControlChosenDeltaPhi_hl_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	}
      }

      fControlChosenDeltaEta->Fill(deltaEta,gHeader->GetWeight());
      if( dimuon->GetDeltaThetaCut())
	fControlChosenDeltaTheta->Fill(deltaTheta,gHeader->GetWeight());
      if( dimuon->GetPtAsymetryCut()) {
	fControlChosenPtAsymetry->Fill(ptAsymetry,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
    	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fControlChosenPtAsymetry_lu_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fControlChosenPtAsymetry_ll_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fControlChosenPtAsymetry_hu_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fControlChosenPtAsymetry_hl_is->Fill(ptAsymetry,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fControlChosenPtAsymetry_lu_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fControlChosenPtAsymetry_ll_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fControlChosenPtAsymetry_hu_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fControlChosenPtAsymetry_hl_nis->Fill(ptAsymetry,gHeader->GetWeight());
	}

	fControlChosenpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fControlChosenpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
  	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fControlChosenpt_lu_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_lu_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fControlChosenpt_ll_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_ll_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fControlChosenpt_hu_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_hu_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fControlChosenpt_hl_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_hl_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fControlChosenpt_lu_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_lu_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fControlChosenpt_ll_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_ll_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fControlChosenpt_hu_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_hu_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlChosenpt_hl_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fControlChosenpt_hl_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	}

 	fControlChosendimupt->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
     	  if(invMass <= 4 &&  dimuon->GetDifCharge()) { fControlChosendimupt_lu_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass <= 4 && !dimuon->GetDifCharge()) { fControlChosendimupt_ll_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  &&  dimuon->GetDifCharge()) { fControlChosendimupt_hu_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  && !dimuon->GetDifCharge()) { fControlChosendimupt_hl_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) { fControlChosendimupt_lu_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass <= 4 && !dimuon->GetDifCharge()) { fControlChosendimupt_ll_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  &&  dimuon->GetDifCharge()) { fControlChosendimupt_hu_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  && !dimuon->GetDifCharge()) { fControlChosendimupt_hl_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	}

	fControlChoseneta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fControlChoseneta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
     	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fControlChoseneta_lu_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_lu_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fControlChoseneta_ll_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_ll_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fControlChoseneta_hu_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_hu_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlChoseneta_hl_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_hl_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fControlChoseneta_lu_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_lu_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fControlChoseneta_ll_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_ll_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fControlChoseneta_hu_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fControlChoseneta_hu_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlChoseneta_hl_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fControlChoseneta_hl_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}
     
	fControlChosensqisol_10->Fill( IsolationSqSum10,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
   	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlChosensqisol_10_is_lu->Fill( IsolationSqSum10,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlChosensqisol_10_is_ll->Fill( IsolationSqSum10,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlChosensqisol_10_is_hu->Fill( IsolationSqSum10,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlChosensqisol_10_is_hl->Fill( IsolationSqSum10,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  fControlChosensqisol_10_nis_lu->Fill( IsolationSqSum10,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())  fControlChosensqisol_10_nis_ll->Fill( IsolationSqSum10,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())  fControlChosensqisol_10_nis_hu->Fill( IsolationSqSum10,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())  fControlChosensqisol_10_nis_hl->Fill( IsolationSqSum10,gHeader->GetWeight());
	}
	/*
	cout<<" "<< endl;
	cout<<"******* Chosen Muons Control Histrograms ********"<< endl;
	cout<<" "<< endl;
        cout<<"Eventnr: "<< gData->Geteventnr() << endl;
        cout<<" " << endl;
	cout<<"1st Muon Pt:  "<< setw(8) << dimuon->GetMuon1()->Pt()  <<", 2nd Muon Pt:  "<< setw(8) << dimuon->GetMuon2()->Pt() << endl;
        cout<<"1st Muon Eta: "<< setw(8) << dimuon->GetMuon1()->Eta() <<", 2nd Muon Eta: "<< setw(8) << dimuon->GetMuon2()->Eta() << endl;
        cout<<"Dimuon Pt:    "<< setw(8) << dimuon->GetdimuPt()       <<", Dimuon Eta:   "<< setw(8) << dimuon->GetEta() << endl;
        cout<<"Isolation:    "<< setw(8) << IsolationSqSum10          <<", Pt asym:      "<< setw(8) << ptAsymetry << setw(8) <<", Delta Eta: "<< deltaEta <<endl;
	cout<<"Isolation Muon 1: " << setw(8) << gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9) <<" Isolation Muon 2: " << setw(8) << gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9) << endl;
	cout<<"Nachgerechnete Dimuon Isolation: " << TMath::Sqrt(TMath::Power(gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9),2)+TMath::Power(gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9),2)) << endl;
	cout<<"1st Muon Quality: " << setw(8) << dimuon->GetMuon1()->GetQuality() <<", 2nd Muon Quality: " << setw(8) << dimuon->GetMuon2()->GetQuality() << endl;
	*/
// Event shape Distributions

	if(gData->Getkt_njet_a()==0){
	  fControlChosenthrust       -> Fill(thrust      ,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlChosenthrust_is_lu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fControlChosenthrust_is_ll -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fControlChosenthrust_is_hu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  && !dimuon->GetDifCharge()) fControlChosenthrust_is_hl -> Fill( thrust, gHeader->GetWeight()); 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fControlChosenthrust_nis_lu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fControlChosenthrust_nis_ll -> Fill( thrust, gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fControlChosenthrust_nis_hu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  && !dimuon->GetDifCharge()) fControlChosenthrust_nis_hl -> Fill( thrust, gHeader->GetWeight()); 
	  }
	}

	fControlChosensphericity   -> Fill(sphericity,      gHeader->GetWeight());
	fControlChosenisotropy     -> Fill(isotropy,        gHeader->GetWeight());
	fControlChosenmultiplicity -> Fill(multiplicity,    gHeader->GetWeight());
	fControlChosenQ2Prime      -> Fill(Q2Prime,         gHeader->GetWeight());

	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fControlChosensphericity_is_lu   -> Fill(sphericity,      gHeader->GetWeight());
	    fControlChosenisotropy_is_lu     -> Fill(isotropy,        gHeader->GetWeight());
	    fControlChosenmultiplicity_is_lu -> Fill(multiplicity,    gHeader->GetWeight());
	    fControlChosenQ2Prime_is_lu      -> Fill(Q2Prime,         gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fControlChosensphericity_is_ll   -> Fill(sphericity,      gHeader->GetWeight());
	    fControlChosenisotropy_is_ll     -> Fill(isotropy,        gHeader->GetWeight());
	    fControlChosenmultiplicity_is_ll -> Fill(multiplicity,    gHeader->GetWeight());
	    fControlChosenQ2Prime_is_ll      -> Fill(Q2Prime,         gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fControlChosensphericity_is_hu   -> Fill(sphericity,      gHeader->GetWeight()); 
	    fControlChosenisotropy_is_hu     -> Fill(isotropy,        gHeader->GetWeight()); 
	    fControlChosenmultiplicity_is_hu -> Fill(multiplicity,    gHeader->GetWeight()); 
	    fControlChosenQ2Prime_is_hu      -> Fill(Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fControlChosensphericity_is_hl   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlChosenisotropy_is_hl     -> Fill( isotropy,        gHeader->GetWeight());
	    fControlChosenmultiplicity_is_hl -> Fill( multiplicity,    gHeader->GetWeight());
	    fControlChosenQ2Prime_is_hl      -> Fill( Q2Prime,         gHeader->GetWeight());
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fControlChosensphericity_nis_lu   -> Fill( sphericity,      gHeader->GetWeight());
	    fControlChosenisotropy_nis_lu     -> Fill( isotropy,        gHeader->GetWeight());
	    fControlChosenmultiplicity_nis_lu -> Fill( multiplicity,    gHeader->GetWeight());
	    fControlChosenQ2Prime_nis_lu      -> Fill( Q2Prime,         gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fControlChosensphericity_nis_ll   -> Fill( sphericity,      gHeader->GetWeight());
	    fControlChosenisotropy_nis_ll     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlChosenmultiplicity_nis_ll -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlChosenQ2Prime_nis_ll      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fControlChosensphericity_nis_hu   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlChosenisotropy_nis_hu     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlChosenmultiplicity_nis_hu -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlChosenQ2Prime_nis_hu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fControlChosensphericity_nis_hl   -> Fill( sphericity,      gHeader->GetWeight()); 
	    fControlChosenisotropy_nis_hl     -> Fill( isotropy,        gHeader->GetWeight()); 
	    fControlChosenmultiplicity_nis_hl -> Fill( multiplicity,    gHeader->GetWeight()); 
	    fControlChosenQ2Prime_nis_hl      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	  }
	}
      }
    }
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GDIMuons::ObjectsFillGeneral(GDIMuon *dimuon) {
  //
  // fill general histograms with data by looping over internal array
  if( gDebug ) cout << endl << "GDIMuons::ObjectsFillGeneral() called" << endl << endl;
  
  if( gCards->GetDIMUONGeneral()) {
    
    Double_t invMass = dimuon->GetInvMass();

    // construct for likesign contribution
    // all cuts except diff charge cut
    // all in this if is the old 'ugly but stay' block - redo below for 'ib-dimuon'
    // remember to ask for unlike sign in unlike sign distris.
    if( ( ( dimuon->GetMuonsAllCuts() && !gCards->GetDoEfficiency()) || ( dimuon->GetMuonsMVCuts() && gCards->GetDoEfficiency()) ) &&
	 dimuon->GetInvMassCut() &&
	 dimuon->GetDeltaRCut() &&
	 ( dimuon->GetDeltaPhiCut() || dimuon->GetDeltaThetaCut()) &&
	 dimuon->GetDeltaEtaCut() &&
	 dimuon->GetPtAsymetryCut() &&
	 dimuon->GetEtFractionHighCut() &&
	 dimuon->GetEtFractionLowCut() &&
	 !dimuon->GetDifChargeCut() &&
	 gCards->GetDIMUONDifCharge()) {
      
      fGeneralDIMuonMass_LikeSign_uncut->Fill(invMass);
      if(invMass <= 4 )
	fGeneralDIMuonMassLow_LikeSign_uncut->Fill(invMass);
      if(invMass > 4 )
	fGeneralDIMuonMassHigh_LikeSign_uncut->Fill(invMass);

      if( gTrigger->GetAllCuts() &&
	   gVertex->GetAllCuts() && 
	   gSinistra->GetAllCuts() && 
	   gCal->GetAllCuts() && 
	   gZufo->GetAllCuts() && 
	   gMuons->GetAllCuts() && 
	   gJets->GetAllCuts()  &&
	   gTracks->GetAllCuts() &&
	   gMJMatchs->GetAllCuts()) {
	fGeneralDIMuonMass_LikeSign->Fill(invMass);
	if(invMass <= 4 )
	  fGeneralDIMuonMassLow_LikeSign->Fill(invMass);
	if(invMass > 4 )
	  fGeneralDIMuonMassHigh_LikeSign->Fill(invMass);
      }
    }
    if( ( dimuon->GetMuonsAllCuts() && (dimuon->GetType() == kChosenDIMuon) 
	  || ( dimuon->GetMuonsMVCuts() && gCards->GetDoEfficiency()) ) &&
	dimuon->GetInvMassCut() &&
	dimuon->GetDeltaRCut() &&
	( dimuon->GetDeltaPhiCut() || dimuon->GetDeltaThetaCut()) &&
	dimuon->GetDeltaEtaCut() &&
	dimuon->GetPtAsymetryCut() &&
	dimuon->GetEtFractionHighCut() &&
	dimuon->GetEtFractionLowCut() &&
	!dimuon->GetDifCharge() &&
	!gCards->GetDIMUONDifCharge()
	) {
      fGeneralDIMuonMass_LikeSign_uncut->Fill(invMass);
      if(invMass <= 4 )
	fGeneralDIMuonMassLow_LikeSign_uncut->Fill(invMass);
      if(invMass > 4 )
	fGeneralDIMuonMassHigh_LikeSign_uncut->Fill(invMass);
      if( gTrigger->GetAllCuts() &&
	   gVertex->GetAllCuts() && 
	   gSinistra->GetAllCuts() && 
	   gCal->GetAllCuts() && 
	   gZufo->GetAllCuts() && 
	   gMuons->GetAllCuts() && 
	   gJets->GetAllCuts()  &&
	   gTracks->GetAllCuts() &&
	   gMJMatchs->GetAllCuts()) {
	fGeneralDIMuonMass_LikeSign->Fill(invMass);
	if(invMass <= 4 )
	  fGeneralDIMuonMassLow_LikeSign->Fill(invMass);
	if(invMass > 4 )
	  fGeneralDIMuonMassHigh_LikeSign->Fill(invMass);
      }      
    }

    // ib-dimuon block starts here (? 040820)
    if( dimuon->GetAllCuts() && (dimuon->GetType() == kChosenDIMuon)) {
      
      Double_t deltaR     = dimuon->GetDeltaR();
      Double_t deltaPhi   = dimuon->GetDeltaPhi();
      Double_t deltaEta   = dimuon->GetDeltaEta();
      Double_t deltaTheta = dimuon->GetDeltaTheta();
      Double_t dimuphi    = dimuon->GetPhi();
      Double_t dimueta    = dimuon->GetEta();
      Double_t ptAsymetry = dimuon->GetPtAsymetry();
      //      Double_t etFraction = dimuon->GetEtFraction();
      Double_t IsolationSqSum10 = dimuon->GetIsolationSqSum10();
      Double_t Isolation_1_10 = 0;
      Double_t Isolation_2_10 = 0;
      Double_t Isolation_highpt_mu = 0;
      if(dimuon->GetMuon1()->GetIsolation10() > 0.) Isolation_1_10 = dimuon->GetMuon1()->GetIsolation10();
      if(dimuon->GetMuon2()->GetIsolation10() > 0.) Isolation_2_10 = dimuon->GetMuon2()->GetIsolation10();
      if(dimuon->GetMuon1()->GetIsolation10() > 0. && dimuon->GetMuon1()->Pt() > dimuon->GetMuon2()->Pt()) Isolation_highpt_mu = dimuon->GetMuon1()->GetIsolation10();
      if(dimuon->GetMuon2()->GetIsolation10() > 0. && dimuon->GetMuon2()->Pt() > dimuon->GetMuon1()->Pt()) Isolation_highpt_mu = dimuon->GetMuon2()->GetIsolation10();
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
      Double_t NJets              = gData->Getkt_njet_a();
      Int_t    secvtx             = 0;
      Int_t    nrsecvtx           = 0;
      Double_t Vertextracks       = gData->Getntrkvtx();
      Double_t TotalTracks        = gData->Gettrk_ntracks();
      Double_t VertexOvNTracks    = Vertextracks/TotalTracks;

      TVector3 r2d_v, upt_v;

      Double_t phi_d;
        
      fGeneralDIMuonMass_uncut->Fill(invMass);
      if(invMass <= 4 )
	fGeneralDIMuonMassLow_uncut->Fill(invMass);
      if(invMass > 4 )
	fGeneralDIMuonMassHigh_uncut->Fill(invMass);
      if( dimuon->GetDifCharge()) // enter this before allll unlike signs!
	fGeneralDIMuonMass_UnlikeSign_uncut->Fill(invMass);
      if(invMass <= 4 ){
	if( dimuon->GetDifCharge()) // enter this before allll unlike signs!
	  fGeneralDIMuonMassLow_UnlikeSign_uncut->Fill(invMass);
      }
      if(invMass > 4 ){
	if( dimuon->GetDifCharge()) // enter this before allll unlike signs!
	  fGeneralDIMuonMassHigh_UnlikeSign_uncut->Fill(invMass);
      }

      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {      
	if(invMass <= 4 &&  dimuon->GetDifCharge())    fGeneralMass_lu_is_uncut->Fill(invMass,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())    fGeneralMass_ll_is_uncut->Fill(invMass,gHeader->GetWeight()); 
	if(invMass > 4  &&  dimuon->GetDifCharge())    fGeneralMass_hu_is_uncut->Fill(invMass,gHeader->GetWeight()); 
	if(invMass > 4  && !dimuon->GetDifCharge())    fGeneralMass_hl_is_uncut->Fill(invMass,gHeader->GetWeight()); 
      }						      
      else{					      
	if(invMass <= 4 &&  dimuon->GetDifCharge())    fGeneralMass_lu_nis_uncut->Fill(invMass,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())    fGeneralMass_ll_nis_uncut->Fill(invMass,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())    fGeneralMass_hu_nis_uncut->Fill(invMass,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())    fGeneralMass_hl_nis_uncut->Fill(invMass,gHeader->GetWeight());
      }                                                 

      fGeneralDeltaR_uncut->Fill(deltaR,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneralDeltaR_lu_is_uncut->Fill(deltaR,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneralDeltaR_ll_is_uncut->Fill(deltaR,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneralDeltaR_hu_is_uncut->Fill(deltaR,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())      fGeneralDeltaR_hl_is_uncut->Fill(deltaR,gHeader->GetWeight());
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneralDeltaR_lu_nis_uncut->Fill(deltaR,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneralDeltaR_ll_nis_uncut->Fill(deltaR,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneralDeltaR_hu_nis_uncut->Fill(deltaR,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())      fGeneralDeltaR_hl_nis_uncut->Fill(deltaR,gHeader->GetWeight());
      }
      
      fGeneralDeltaPhi_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())    fGeneralDeltaPhi_lu_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())    fGeneralDeltaPhi_ll_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())    fGeneralDeltaPhi_hu_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())    fGeneralDeltaPhi_hl_is_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())    fGeneralDeltaPhi_lu_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())    fGeneralDeltaPhi_ll_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())    fGeneralDeltaPhi_hu_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())    fGeneralDeltaPhi_hl_nis_uncut->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
      }

      fGeneralDeltaEta_uncut->Fill(deltaEta,gHeader->GetWeight());
      fGeneralDeltaTheta_uncut->Fill(deltaTheta,gHeader->GetWeight());

      fGeneraldimuphi_uncut->Fill(dimuphi,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
        if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimuphi_lu_is_uncut->Fill(dimuphi,gHeader->GetWeight());
        if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimuphi_ll_is_uncut->Fill(dimuphi,gHeader->GetWeight());
        if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimuphi_hu_is_uncut->Fill(dimuphi,gHeader->GetWeight());
        if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimuphi_hl_is_uncut->Fill(dimuphi,gHeader->GetWeight());
      }
      else{
        if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimuphi_lu_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
        if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimuphi_ll_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
        if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimuphi_hu_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
        if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimuphi_hl_nis_uncut->Fill(dimuphi,gHeader->GetWeight());
      }
      
      fGeneraldimueta_uncut->Fill(dimueta,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimueta_lu_is_uncut->Fill(dimueta,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimueta_ll_is_uncut->Fill(dimueta,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimueta_hu_is_uncut->Fill(dimueta,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimueta_hl_is_uncut->Fill(dimueta,gHeader->GetWeight());
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimueta_lu_nis_uncut->Fill(dimueta,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimueta_ll_nis_uncut->Fill(dimueta,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimueta_hu_nis_uncut->Fill(dimueta,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimueta_hl_nis_uncut->Fill(dimueta,gHeader->GetWeight());
      }

      fGeneralPtAsymetry_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneralPtAsymetry_lu_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneralPtAsymetry_ll_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneralPtAsymetry_hu_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())      fGeneralPtAsymetry_hl_is_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneralPtAsymetry_lu_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneralPtAsymetry_ll_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneralPtAsymetry_hu_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge())      fGeneralPtAsymetry_hl_nis_uncut->Fill(ptAsymetry,gHeader->GetWeight());
      }

      fGeneralpt_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
      fGeneralpt_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	  fGeneralpt_lu_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_lu_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	  fGeneralpt_ll_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_ll_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	  fGeneralpt_hu_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_hu_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneralpt_hl_is_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_hl_is_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	  fGeneralpt_lu_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_lu_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	  fGeneralpt_ll_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_ll_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	  fGeneralpt_hu_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_hu_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneralpt_hl_nis_uncut->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	  fGeneralpt_hl_nis_uncut->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	}
      }

      fGeneraldimupt_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge()) { fGeneraldimupt_lu_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge()) { fGeneraldimupt_ll_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge()) { fGeneraldimupt_hu_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge()) { fGeneraldimupt_hl_is_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) { fGeneraldimupt_lu_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge()) { fGeneraldimupt_ll_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge()) { fGeneraldimupt_hu_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge()) { fGeneraldimupt_hl_nis_uncut->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
      }

      fGeneraleta_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
      fGeneraleta_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	  fGeneraleta_lu_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_lu_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	  fGeneraleta_ll_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_ll_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	  fGeneraleta_hu_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_hu_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  { 
	  fGeneraleta_hl_is_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_hl_is_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	  fGeneraleta_lu_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_lu_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	  fGeneraleta_ll_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_ll_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	  fGeneraleta_hu_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_hu_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneraleta_hl_nis_uncut->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	  fGeneraleta_hl_nis_uncut->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	}
      }

// Secondary Vertex Distributions

      for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

	if(gData->Getnr_secvtx()>0){

	  if(gData->Getvtxsec_x(i)!=666 && gData->Getvtxsec_y(i)!=666 && gData->Getvtxsec_z(i)!=666 && 
             gData->Getvtxredprm_x()!=666 && gData->Getvtxredprm_y()!= 666 && gData->Getvtxredprm_z()!= 666 ){

	    secvtx    = 1;
	    nrsecvtx += secvtx;

	    fGeneralVtxMass_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {     
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralVtxMass_is_lu_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralVtxMass_is_ll_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralVtxMass_is_hu_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralVtxMass_is_hl_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	    }
	    else{
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralVtxMass_nis_lu_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralVtxMass_nis_ll_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralVtxMass_nis_hu_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralVtxMass_nis_hl_uncut->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	    }

	    fGeneralChi2_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralChi2_is_lu_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralChi2_is_ll_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralChi2_is_hu_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralChi2_is_hl_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	    }
	    else{
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralChi2_nis_lu_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralChi2_nis_ll_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralChi2_nis_hu_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralChi2_nis_hl_uncut->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	    }

	    fGeneralNdof_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralNdof_is_lu_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralNdof_is_ll_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralNdof_is_hu_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralNdof_is_hl_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	    }
	    else{
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralNdof_nis_lu_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralNdof_nis_ll_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralNdof_nis_hu_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralNdof_nis_hl_uncut->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	    }

	    fGeneralMulti_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralMulti_is_lu_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralMulti_is_ll_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralMulti_is_hu_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralMulti_is_hl_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	    }
	    else{
	      if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralMulti_nis_lu_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralMulti_nis_ll_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralMulti_nis_hu_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralMulti_nis_hl_uncut->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	    }

	    r2d_v.SetXYZ(gData->Getvtxsec_x(i)-gData->Getvtxredprm_x(), gData->Getvtxsec_y(i)-gData->Getvtxredprm_y(), 0);
	  
	    phi_d = gData->Getkt_phijet_a(i);

	    upt_v.SetXYZ(TMath::Cos(phi_d),TMath::Sin(phi_d), 0);
	  
	    fSecvtx_DL2       = r2d_v.Dot(upt_v);
	    fSecvtx_DL2_err   = (gData->Getvtxredprm_cov(0)+gData->Getvtxsec_cov(i,0))*(TMath::Power(TMath::Cos(phi_d),2));
	    fSecvtx_DL2_err  += (gData->Getvtxredprm_cov(2)+gData->Getvtxsec_cov(i,2))*(TMath::Power(TMath::Sin(phi_d),2));
	    fSecvtx_DL2_err  += 2*(gData->Getvtxredprm_cov(1)+gData->Getvtxsec_cov(i,1))*(TMath::Sin(phi_d)*TMath::Cos(phi_d));
	    fSecvtx_DL2_err   = TMath::Sqrt(fSecvtx_DL2_err);
	    
	    if( gData->Getrunnr() == 1 ){ // MC Decay Length Smearing
	      static TRandom3 *rnd      = new TRandom3();
	      Double_t         nr_rand  = rnd->Rndm();
	      Float_t          exponent = 5.;

	      if(nr_rand < 0.05){
		Double_t nr_rand_gauss = rnd->Gaus();
		Float_t  smearvalue    = 1.8*fSecvtx_DL2_err*nr_rand_gauss;
		fSecvtx_DL2           += smearvalue;
		fSecvtx_DL2_sign       = fSecvtx_DL2 / fSecvtx_DL2_err;

		fGeneralDL2_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_is_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_is_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_is_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_is_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_nis_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_nis_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_nis_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_nis_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}

		fGeneralDL2_Sign_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}

		if( fSecvtx_DL2_sign > 0 ){
		  fSecvtx_DL2_signp = fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrp_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		  }
		}
	      
		if( fSecvtx_DL2_sign < 0 ){
		  fSecvtx_DL2_signm = -fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrm_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_is_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_nis_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_nis_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		  }
		}
	      }

	      if(nr_rand < 0.01){
		Double_t nr_rand_gauss = rnd->Gaus();
		Float_t  smearvalue    = 2.3*fSecvtx_DL2_err*nr_rand_gauss;
		fSecvtx_DL2           += smearvalue;
		fSecvtx_DL2_sign       = fSecvtx_DL2 / fSecvtx_DL2_err;

		fGeneralDL2_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_is_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_is_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_is_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_is_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_nis_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_nis_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_nis_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_nis_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}

		fGeneralDL2_Sign_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}

		if( fSecvtx_DL2_sign > 0 ){
		  fSecvtx_DL2_signp = fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrp_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		  }
		}

		if( fSecvtx_DL2_sign < 0 ){
		  fSecvtx_DL2_signm = -fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrm_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_is_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_nis_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		  }
		}
	      }

	      if( nr_rand < 0.1*fSecvtx_DL2_err ){
		static TRandom3 *rnd2      = new TRandom3();
		Double_t         nr_rand2  = rnd2->Rndm();
		Float_t          randtemp  = 2*nr_rand2-1;
		Float_t          sign      = randtemp/TMath::Abs(randtemp);
		fSecvtx_DL2               += sign*TMath::Log(1-TMath::Abs(randtemp))/(-exponent);
		fSecvtx_DL2_sign           = fSecvtx_DL2 / fSecvtx_DL2_err;

		fGeneralDL2_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_is_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_is_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_is_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_is_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_nis_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_nis_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_nis_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_nis_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}

		fGeneralDL2_Sign_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}

		if( fSecvtx_DL2_sign > 0 ){
		  fSecvtx_DL2_signp = fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrp_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_is_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrp_nis_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    }
		  }
		}

		if( fSecvtx_DL2_sign < 0 ){
		  fSecvtx_DL2_signm = -fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrm_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_is_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_is_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		      fGeneralDL2_Sign_Mirrm_nis_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		    if(invMass> 4  && !dimuon->GetDifCharge()){
		      fGeneralDL2_Sign_Mirrm_nis_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    }
		  }
		}
	      }
	    }
	
	    if( gData->Getrunnr() > 100 ){
    
	      fSecvtx_DL2_sign  = fSecvtx_DL2 / fSecvtx_DL2_err;
	      
	      if( fSecvtx_DL2_sign > 0 ){
		fSecvtx_DL2_signp = fSecvtx_DL2_sign;

		fGeneralDL2_Sign_Mirrp_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_is_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  if(invMass <= 4 && !dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_is_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		}
		  if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_is_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  if(invMass> 4  && !dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_is_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		}
		else{
		  if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_nis_lu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_nis_ll_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_nis_hu_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  if(invMass> 4  && !dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrp_nis_hl_uncut->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		}
	      }

	      if( fSecvtx_DL2_sign < 0 ){
		fSecvtx_DL2_signm = -fSecvtx_DL2_sign;

		fGeneralDL2_Sign_Mirrm_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass<= 4 &&  dimuon->GetDifCharge()){
		    fGeneralDL2_Sign_Mirrm_is_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  if(invMass<= 4 && !dimuon->GetDifCharge()){
		    fGeneralDL2_Sign_Mirrm_is_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  if(invMass> 4  &&  dimuon->GetDifCharge()){
		    fGeneralDL2_Sign_Mirrm_is_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  if(invMass> 4  && !dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrm_is_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		}
		else{
		  if(invMass<= 4 &&  dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrm_nis_lu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  if(invMass<= 4 && !dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrm_nis_ll_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  if(invMass> 4  &&  dimuon->GetDifCharge()){ 
		    fGeneralDL2_Sign_Mirrm_nis_hu_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  if(invMass> 4  && !dimuon->GetDifCharge()){
		    fGeneralDL2_Sign_Mirrm_nis_hl_uncut->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		}
	      }

	      fGeneralDL2_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_is_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_is_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_is_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_is_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_nis_lu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_nis_ll_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_nis_hu_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_nis_hl_uncut->Fill(fSecvtx_DL2,gHeader->GetWeight());
	      }

	      fGeneralDL2_Sign_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_lu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_ll_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hu_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hl_uncut->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
	      }
	    }
	  }
	}
      }

      fGeneralNrsecvtx_uncut->Fill(nrsecvtx,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {     
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_is_lu_uncut->Fill(nrsecvtx,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNrsecvtx_is_ll_uncut->Fill(nrsecvtx,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_is_hu_uncut->Fill(nrsecvtx,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNrsecvtx_is_hl_uncut->Fill(nrsecvtx,gHeader->GetWeight()); 
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_lu_uncut->Fill(nrsecvtx,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_ll_uncut->Fill(nrsecvtx,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_hu_uncut->Fill(nrsecvtx,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_hl_uncut->Fill(nrsecvtx,gHeader->GetWeight());
      }

// Forward Muon information 

      if( dimuon->GetMuon1()->GetForwardTrackMuon()){

	if(dimuon->GetMuon1()->GetMPMatch()) {

	  fGeneralMunphi_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_lu_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_ll_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_hu_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_hl_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    }
	  }
	  
	  fGeneralMundof_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_is_lu_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMundof_is_ll_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_is_hu_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMundof_is_hl_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    }
	  }

	  fGeneralMupmat_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) { 
	    if(invMass<=4&& dimuon->GetDifCharge())  {
	      fGeneralMupmat_is_lu_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass<=4&& !dimuon->GetDifCharge()) {
	      fGeneralMupmat_is_ll_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass> 4 && dimuon->GetDifCharge()) {
	      fGeneralMupmat_is_hu_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass> 4 && !dimuon->GetDifCharge()){
	      fGeneralMupmat_is_hl_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass<=4&& dimuon->GetDifCharge())  {
	      fGeneralMupmat_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass<=4&& !dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass> 4&&  dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass> 4&& !dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    }
	  }
 
	  fGeneralMPMatchID_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_lu_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_ll_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_hu_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_hl_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    }
	  }

	  fGeneralMuMvID_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_lu_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_ll_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_hu_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_hl_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    }
	  }
  
	  fGeneralMuMufoID_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_lu_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_ll_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_hu_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_hl_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass<= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass> 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass> 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    }
	  }
  
	  fGeneralMuz_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_is_lu_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuz_is_ll_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuz_is_hu_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuz_is_hl_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralMuz_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralMuz_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralMuz_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	  }
	}
      }

      else if(dimuon->GetMuon2()->GetForwardTrackMuon()){
	if(dimuon->GetMuon2()->GetMPMatch()) {
	  fGeneralMunphi_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_lu_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_ll_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_hu_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_is_hl_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMunphi_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    }
	  }
  
	  fGeneralMundof_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_is_lu_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMundof_is_ll_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_is_hu_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMundof_is_hl_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMundof_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    }
	  }

	  fGeneralMupmat_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) { 
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMupmat_is_lu_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMupmat_is_ll_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMupmat_is_hu_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMupmat_is_hl_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMupmat_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    }
	  }
 
	  fGeneralMPMatchID_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_lu_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_ll_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_hu_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_is_hl_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMPMatchID_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    }
	  }

	  fGeneralMuMvID_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_lu_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_ll_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_hu_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_is_hl_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMvID_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    }
	  }
  
	  fGeneralMuMufoID_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_lu_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_ll_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_hu_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_is_hl_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass<= 4 && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass> 4  &&  dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	    if(invMass> 4  && !dimuon->GetDifCharge()) {
	      fGeneralMuMufoID_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    }
	  }
  
	  fGeneralMuz_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
  	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_is_lu_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuz_is_ll_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuz_is_hu_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuz_is_hl_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralMuz_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralMuz_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralMuz_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	  }
	}
      }
    
  
      fGeneralMuBacMatID_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());;
      fGeneralMuBacMatID_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
	if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_is_lu_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_is_lu_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_is_ll_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_is_ll_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_is_hu_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_is_hu_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_is_hl_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_is_hl_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge()) {
	  fGeneralMuBacMatID_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	  fGeneralMuBacMatID_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	}
      }

      fGeneralNBacMat_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNBacMat_is_lu_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNBacMat_is_ll_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNBacMat_is_hu_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNBacMat_is_hl_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNBacMat_nis_lu_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNBacMat_nis_ll_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNBacMat_nis_hu_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNBacMat_nis_hl_uncut->Fill(gData->GetBm_n(),gHeader->GetWeight());
      }

      for( Int_t p = 0; p < gData->GetBm_n(); p++) {

	fGeneralBacMat_VCID_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_lu_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_ll_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_hu_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_hl_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	}
	else{
	  if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_lu_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
          if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_ll_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_hu_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_hl_uncut->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	}
	
	fGeneralBacMat_MuBacID_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass<= 4 &&  dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_is_lu_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  if(invMass<= 4 && !dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_is_ll_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  if(invMass> 4  &&  dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_is_hu_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  if(invMass> 4  && !dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_is_hl_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	}
	else{
	  if(invMass<= 4 &&  dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_nis_lu_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  if(invMass<= 4 && !dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_nis_ll_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  if(invMass> 4  &&  dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_nis_hu_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  if(invMass> 4  && !dimuon->GetDifCharge()) {
	    fGeneralBacMat_MuBacID_nis_hl_uncut->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	}

	fGeneralBacMat_Istop_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_lu_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_ll_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_hu_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_hl_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	}
	else{
	  if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_lu_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_ll_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
     	  if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_hu_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_hl_uncut->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	}

	fGeneralBacMat_Error_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Error_is_lu_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
  
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_is_ll_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_is_hu_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_is_hl_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_nis_lu_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_nis_ll_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_nis_hu_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Error_nis_hl_uncut->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    }
	  }

	  fGeneralBacMat_Readout_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_is_lu_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_is_ll_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_is_hu_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_is_hl_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_nis_lu_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	    if(invMass<= 4 && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_nis_ll_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	    if(invMass> 4  &&  dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_nis_hu_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	    if(invMass> 4  && !dimuon->GetDifCharge()) {
	      fGeneralBacMat_Readout_nis_hl_uncut->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    }
	  }
	}

// Signed Impact Parameter and Significance

      if(dimuon->GetMuon1()->GetJetID()>0){

	fGeneralImpact2D_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
          if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	    fGeneralImpact2D_is_lu_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_ll_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_hu_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_hl_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralImpact2D_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	}

	fGeneralImpact2D_Sign_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
          if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_is_lu_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_ll_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_hu_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_hl_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	}
      }

      if(dimuon->GetMuon2()->GetJetID()>0){
	fGeneralImpact2D_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
          if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_is_lu_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_ll_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_hu_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_hl_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralImpact2D_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	}

	fGeneralImpact2D_Sign_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
          if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_is_lu_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_ll_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_hu_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_hl_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	}
      }
    
// Muon-Jet Distributions

      if(dimuon->GetMuon1()->GetJetID()>0){
	fGeneralMuJetDeltaR_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_is_lu_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_is_ll_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_is_hu_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralMuJetDeltaR_is_hl_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_lu_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_ll_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_hu_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_hl_uncut->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  }
	}

	for ( Int_t j = 0; j < gData->Getkt_njet_a(); j++  ) {
    
	  if( j+1 == dimuon->GetMuon1()->GetJetID()) {
	      
	    fMuonJetMass  = gData->Getkt_masjet_a(j);
	    fMuonJetEt    = gData->Getkt_etjet_a(j);
	    fMuonJetEta   = gData->Getkt_etajet_a(j);
	    fMuonJetTheta = 2 * TMath::ATan(TMath::Exp(-fMuonJetEta));
	    fMuonJetE     = fMuonJetEt/TMath::Sin(fMuonJetTheta);
	    fMuonJetP     = TMath::Sqrt(TMath::Power(fMuonJetEt,2)-TMath::Power(fMuonJetMass,2));
	    fMuonJetPt    = fMuonJetP*fMuonJetEt/fMuonJetE;
	      
            fGeneralMuJetPt_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_lu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_ll_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_hu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_hl_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_lu_uncut->Fill(fMuonJetPt,gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_ll_uncut->Fill(fMuonJetPt,gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hl_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	    }

	    fGeneralMuJetEt_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_lu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_ll_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_hu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_hl_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_lu_uncut->Fill(fMuonJetEt,gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_ll_uncut->Fill(fMuonJetEt,gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hl_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	    }

	    fGeneralMuJetEta_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_lu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_ll_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_hu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_hl_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_lu_uncut->Fill(fMuonJetEta,gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_ll_uncut->Fill(fMuonJetEta,gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hl_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	    }

	    fGeneralMassJet_uncut->Fill( fMuonJetMass ,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_is_lu_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_is_ll_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_is_hu_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_is_hl_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_lu_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_nis_ll_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_hu_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_nis_hl_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	    }
	  }
	}
      }
      if(dimuon->GetMuon2()->GetJetID()>0){

	fGeneralMuJetDeltaR_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_is_lu_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_is_ll_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_is_hu_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralMuJetDeltaR_is_hl_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_lu_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralMuJetDeltaR_nis_ll_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_hu_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralMuJetDeltaR_nis_hl_uncut->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  }
	}

	for ( Int_t j = 0; j < gData->Getkt_njet_a(); j++  ) {
    
	  if( j+1 == dimuon->GetMuon2()->GetJetID()) {
	      
	    fMuonJetMass  = gData->Getkt_masjet_a(j);
	    fMuonJetEt    = gData->Getkt_etjet_a(j);
	    fMuonJetEta   = gData->Getkt_etajet_a(j);
	    fMuonJetTheta = 2 * TMath::ATan(TMath::Exp(-fMuonJetEta));
	    fMuonJetE     = fMuonJetEt/TMath::Sin(fMuonJetTheta);
	    fMuonJetP     = TMath::Sqrt(TMath::Power(fMuonJetEt,2)-TMath::Power(fMuonJetMass,2));
	    fMuonJetPt    = fMuonJetP*fMuonJetEt/fMuonJetE;

	    fGeneralMuJetPt_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_lu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_ll_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_hu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_hl_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_lu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_ll_uncut->Fill(fMuonJetPt,gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hu_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hl_uncut->Fill(fMuonJetPt,gHeader->GetWeight());
	    }

	    fGeneralMuJetEt_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_lu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_ll_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_hu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_hl_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_lu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_ll_uncut->Fill(fMuonJetEt,gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hu_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hl_uncut->Fill(fMuonJetEt,gHeader->GetWeight());
	    }

	    fGeneralMuJetEta_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_lu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_ll_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_hu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_hl_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_lu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_ll_uncut->Fill(fMuonJetEta,gHeader->GetWeight()); 
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hu_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hl_uncut->Fill(fMuonJetEta,gHeader->GetWeight());
	    }

	    fGeneralMassJet_uncut->Fill( fMuonJetMass ,gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_is_lu_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_is_ll_uncut->Fill( fMuonJetMass, gHeader->GetWeight());  
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_is_hu_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_is_hl_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_lu_uncut->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_nis_ll_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_hu_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_nis_hl_uncut->Fill( fMuonJetMass, gHeader->GetWeight());
	    }
	  }
	}
      }

     fGeneralNJets_uncut->Fill( NJets,gHeader->GetWeight());
     if( !dimuon->GetSqSumIsolationCut()) {      
   	if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNJets_is_lu_uncut->Fill( NJets,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNJets_is_ll_uncut->Fill( NJets,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNJets_is_hu_uncut->Fill( NJets,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNJets_is_hl_uncut->Fill( NJets,gHeader->GetWeight());
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNJets_nis_lu_uncut->Fill( NJets,gHeader->GetWeight());
	if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNJets_nis_ll_uncut->Fill( NJets,gHeader->GetWeight());
	if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNJets_nis_hu_uncut->Fill( NJets,gHeader->GetWeight());
	if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNJets_nis_hl_uncut->Fill( NJets,gHeader->GetWeight());
      }

      fGeneralphi_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
      fGeneralphi_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	  fGeneralphi_lu_is_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	  fGeneralphi_lu_is_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	  fGeneralphi_ll_is_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight()); 
	  fGeneralphi_ll_is_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight()); 
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	  fGeneralphi_hu_is_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	  fGeneralphi_hu_is_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneralphi_hl_is_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	  fGeneralphi_hl_is_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	  fGeneralphi_lu_nis_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	  fGeneralphi_lu_nis_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	  fGeneralphi_ll_nis_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	  fGeneralphi_ll_nis_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	  fGeneralphi_hu_nis_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	  fGeneralphi_hu_nis_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  { 
	  fGeneralphi_hl_nis_uncut->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight()); 
	  fGeneralphi_hl_nis_uncut->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight()); 
	}
      }

      fGeneralmuqual_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
      fGeneralmuqual_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	  fGeneralmuqual_lu_is_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_lu_is_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	  fGeneralmuqual_ll_is_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_ll_is_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	  fGeneralmuqual_hu_is_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight()); 
	  fGeneralmuqual_hu_is_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight()); 
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneralmuqual_hl_is_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_hl_is_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	  fGeneralmuqual_lu_nis_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_lu_nis_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	  fGeneralmuqual_ll_nis_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_ll_nis_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	  fGeneralmuqual_hu_nis_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_hu_nis_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  { 
	  fGeneralmuqual_hl_nis_uncut->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	  fGeneralmuqual_hl_nis_uncut->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	}
      }

      fGeneralsqisol_10_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());
      //    if( dimuon->GetMuon1()->DeltaR(*dimuon->GetMuon2()) < 1.0 )    cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"In GDIMuons: IsolationSqSum10 is: "<<IsolationSqSum10<<" with zufopt1= "<<TMath::Sqrt( TMath::Power(gData->Getzufo(  ((dimuon->GetMuon1()->GetZufoID())-1) , 0 ),2) + TMath::Power(gData->Getzufo(  ((dimuon->GetMuon1()->GetZufoID())-1) , 1 ),2))<<" zufopt2= "<< TMath::Sqrt( TMath::Power(gData->Getzufo(  ((dimuon->GetMuon2()->GetZufoID())-1) , 0 ),2) + TMath::Power(gData->Getzufo(  ((dimuon->GetMuon2()->GetZufoID())-1) , 1 ),2))<<" DR: "<<dimuon->GetMuon1()->DeltaR(*dimuon->GetMuon2()) <<" tufocode is: "<<gData->Gettufo( ((dimuon->GetMuon1()->GetZufoID())-1) ,0 ) <<endl;
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_lu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_ll_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_hu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_hl_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_lu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_ll_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_hu_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_hl_uncut->Fill( IsolationSqSum10,gHeader->GetWeight());}
      }
      /*
      cout<<" "<< endl;
      cout<<"******* General uncut Muons Control Histrograms ********"<< endl;
      cout<<" "<< endl;
      cout<<"Eventnr: "<< gData->Geteventnr() << endl;
      cout<<" " << endl;
      cout<<"1st Muon Pt:  "<< setw(8) << dimuon->GetMuon1()->Pt()  <<", 2nd Muon Pt:  "<< setw(8) << dimuon->GetMuon2()->Pt() << endl;
      cout<<"1st Muon Eta: "<< setw(8) << dimuon->GetMuon1()->Eta() <<", 2nd Muon Eta: "<< setw(8) << dimuon->GetMuon2()->Eta() << endl;
      cout<<"Dimuon Pt:    "<< setw(8) << dimuon->GetdimuPt()       <<", Dimuon Eta:   "<< setw(8) << dimueta << endl;
      cout<<"Isolation:    "<< setw(8) << IsolationSqSum10          <<", Pt asym:      "<< setw(8) << ptAsymetry << setw(8) <<", Delta Eta: "<< deltaEta <<endl;
      cout<<"Isolation Muon 1: " << setw(8) << gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9) <<" Isolation Muon 2: " << setw(8) << gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9) << endl;
      cout<<"Nachgerechnete Dimuon Isolation: " << TMath::Sqrt(TMath::Power(gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9),2)+TMath::Power(gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9),2)) << endl;
      cout<<"1st Muon Quality: " << setw(8) << dimuon->GetMuon1()->GetQuality() <<", 2nd Muon Quality: " << setw(8) << dimuon->GetMuon2()->GetQuality() << endl;
      */
// Event shape Distributions

      if(gData->Getkt_njet_a()==0){
	fGeneralthrust_uncut  -> Fill(thrust      ,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralthrust_is_lu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralthrust_is_ll_uncut -> Fill( thrust, gHeader->GetWeight()); 
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralthrust_is_hu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralthrust_is_hl_uncut -> Fill( thrust, gHeader->GetWeight()); 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralthrust_nis_lu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralthrust_nis_ll_uncut -> Fill( thrust, gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralthrust_nis_hu_uncut -> Fill( thrust, gHeader->GetWeight()); 
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralthrust_nis_hl_uncut -> Fill( thrust, gHeader->GetWeight()); 
	}
      }

      fGeneralsphericity_uncut   -> Fill( sphericity,      gHeader->GetWeight());
      fGeneralisotropy_uncut     -> Fill( isotropy,        gHeader->GetWeight());
      fGeneralmultiplicity_uncut -> Fill( multiplicity,    gHeader->GetWeight());
      fGeneralQ2Prime_uncut      -> Fill( Q2Prime,         gHeader->GetWeight());
     
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	  fGeneralsphericity_is_lu_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	  fGeneralisotropy_is_lu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	  fGeneralmultiplicity_is_lu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	  fGeneralQ2Prime_is_lu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	  fGeneralsphericity_is_ll_uncut   -> Fill( sphericity,      gHeader->GetWeight());
	  fGeneralisotropy_is_ll_uncut     -> Fill( isotropy,        gHeader->GetWeight());
	  fGeneralmultiplicity_is_ll_uncut -> Fill( multiplicity,    gHeader->GetWeight());
	  fGeneralQ2Prime_is_ll_uncut      -> Fill( Q2Prime,         gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {
	  fGeneralsphericity_is_hu_uncut   -> Fill( sphericity,      gHeader->GetWeight());
	  fGeneralisotropy_is_hu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	  fGeneralmultiplicity_is_hu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	  fGeneralQ2Prime_is_hu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneralsphericity_is_hl_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	  fGeneralisotropy_is_hl_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	  fGeneralmultiplicity_is_hl_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	  fGeneralQ2Prime_is_hl_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	} 
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	  fGeneralsphericity_nis_lu_uncut   -> Fill( sphericity,      gHeader->GetWeight());
	  fGeneralisotropy_nis_lu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	  fGeneralmultiplicity_nis_lu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	  fGeneralQ2Prime_nis_lu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	  fGeneralsphericity_nis_ll_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	  fGeneralisotropy_nis_ll_uncut     -> Fill( isotropy,        gHeader->GetWeight());
	  fGeneralmultiplicity_nis_ll_uncut -> Fill( multiplicity,    gHeader->GetWeight());
	  fGeneralQ2Prime_nis_ll_uncut      -> Fill( Q2Prime,         gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	  fGeneralsphericity_nis_hu_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	  fGeneralisotropy_nis_hu_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	  fGeneralmultiplicity_nis_hu_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	  fGeneralQ2Prime_nis_hu_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {  
	  fGeneralsphericity_nis_hl_uncut   -> Fill( sphericity,      gHeader->GetWeight()); 
	  fGeneralisotropy_nis_hl_uncut     -> Fill( isotropy,        gHeader->GetWeight()); 
	  fGeneralmultiplicity_nis_hl_uncut -> Fill( multiplicity,    gHeader->GetWeight()); 
	  fGeneralQ2Prime_nis_hl_uncut      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	}
      }

      fGeneralcal_et_uncut->Fill( cal_et,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralcal_et_is_lu_uncut->Fill( cal_et,gHeader->GetWeight()); }
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralcal_et_is_ll_uncut->Fill( cal_et,gHeader->GetWeight()); }
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralcal_et_is_hu_uncut->Fill( cal_et,gHeader->GetWeight()); }
	if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralcal_et_is_hl_uncut->Fill( cal_et,gHeader->GetWeight()); } 
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralcal_et_nis_lu_uncut->Fill( cal_et,gHeader->GetWeight()); }
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralcal_et_nis_ll_uncut->Fill( cal_et,gHeader->GetWeight()); }
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralcal_et_nis_hu_uncut->Fill( cal_et,gHeader->GetWeight()); }
	if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralcal_et_nis_hl_uncut->Fill( cal_et,gHeader->GetWeight()); }
      }

      fGeneraletex2ir_uncut->Fill( etex2ir,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_is_lu_uncut->Fill( etex2ir,gHeader->GetWeight()); }
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraletex2ir_is_ll_uncut->Fill( etex2ir,gHeader->GetWeight()); }
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_is_hu_uncut->Fill( etex2ir,gHeader->GetWeight()); }
	if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraletex2ir_is_hl_uncut->Fill( etex2ir,gHeader->GetWeight()); } 
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_lu_uncut->Fill( etex2ir,gHeader->GetWeight()); }
	if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_ll_uncut->Fill( etex2ir,gHeader->GetWeight()); }
	if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_hu_uncut->Fill( etex2ir,gHeader->GetWeight()); }
	if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_hl_uncut->Fill( etex2ir,gHeader->GetWeight()); }
      }
    
      fGeneralcal_et_m_et2ir_uncut->Fill( cal_et_m_et2ir,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_is_lu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_is_ll_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_is_hu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_is_hl_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());} 
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_nis_lu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_nis_ll_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_nis_hu_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge()) { fGeneralcal_et_m_et2ir_nis_hl_uncut->Fill(cal_et_m_et2ir,gHeader->GetWeight());}
      }

      fGeneralcal_et_m_cal_et_10_uncut->Fill( cal_et_m_cal_et_10,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      
      //      if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	  fGeneralcal_et_m_cal_et_10_is_lu_uncut->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	}
	if(invMass <= 4 && !dimuon->GetDifCharge()) {
	  fGeneralcal_et_m_cal_et_10_is_ll_uncut->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge()) {
	  fGeneralcal_et_m_cal_et_10_is_hu_uncut->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge()) {
	  fGeneralcal_et_m_cal_et_10_is_hl_uncut->Fill(cal_et_m_cal_et_10,gHeader->GetWeight()); 
	}
      }
      else{
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	  fGeneralcal_et_m_cal_et_10_nis_lu_uncut->Fill( cal_et_m_cal_et_10,gHeader->GetWeight()); 
	}
	if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	  fGeneralcal_et_m_cal_et_10_nis_ll_uncut->Fill( cal_et_m_cal_et_10,gHeader->GetWeight());
	}
	if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	  fGeneralcal_et_m_cal_et_10_nis_hu_uncut->Fill( cal_et_m_cal_et_10,gHeader->GetWeight());
	}
	if(invMass > 4  && !dimuon->GetDifCharge())  {
	  fGeneralcal_et_m_cal_et_10_nis_hl_uncut->Fill( cal_et_m_cal_et_10,gHeader->GetWeight());
	}
      }
            
      if( gCards->GetDoEfficiency()) {
	if( dimuon->GetTriggerType() == kTakeNone )
	  fGeneralTriggerType_uncut->Fill("None",1);
	else if( dimuon->GetTriggerType() == kTakeMuon1 )
	  fGeneralTriggerType_uncut->Fill("Muon1",1);
	else if( dimuon->GetTriggerType() == kTakeMuon2 )
	  fGeneralTriggerType_uncut->Fill("Muon2",1);
	else if( dimuon->GetTriggerType() == kTakeBoth )
	  fGeneralTriggerType_uncut->Fill("Both",1);
      }
//       if( 
// 	 (gData->Getrunnr()==20750 && gData->Geteventnr()==14345) ||
// 	 (gData->Getrunnr()==20791 && gData->Geteventnr()==139670) ||
// 	 (gData->Getrunnr()==21189 && gData->Geteventnr()==39557 ) ||
// 	 (gData->Getrunnr()==21219 && gData->Geteventnr()==66189 ) ||
// 	 (gData->Getrunnr()==21447 && gData->Geteventnr()==40770 ) ||
// 	 (gData->Getrunnr()==21448 && gData->Geteventnr()==8917  ) ||
// 	 (gData->Getrunnr()==21641 && gData->Geteventnr()==12017 ) ||
// 	 (gData->Getrunnr()==21647 && gData->Geteventnr()==59679 ) ||
// 	 (gData->Getrunnr()==21653 && gData->Geteventnr()==9592  ) ||
// 	 (gData->Getrunnr()==21663 && gData->Geteventnr()==49093 ) ||
// 	 (gData->Getrunnr()==21665 && gData->Geteventnr()==65707 ) ||
// 	 (gData->Getrunnr()==21796 && gData->Geteventnr()==8693  ) ||
// 	 (gData->Getrunnr()==21953 && gData->Geteventnr()==34442 ) ||
// 	 (gData->Getrunnr()==21953 && gData->Geteventnr()==35722 ) ||
// 	 (gData->Getrunnr()==22018 && gData->Geteventnr()==41439 ) ||
// 	 (gData->Getrunnr()==22061 && gData->Geteventnr()==60653 ) ||
// 	 (gData->Getrunnr()==22111 && gData->Geteventnr()==38536 ) ||
// 	 (gData->Getrunnr()==22113 && gData->Geteventnr()==23542 ) ||
// 	 (gData->Getrunnr()==22128 && gData->Geteventnr()==13114 ) ||
// 	 (gData->Getrunnr()==22151 && gData->Geteventnr()==20888 ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==7248  ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==20845 ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==20845 ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==83101 ) ||
// 	 (gData->Getrunnr()==22244 && gData->Geteventnr()==17995 ) ||
// 	 (gData->Getrunnr()==22264 && gData->Geteventnr()==6607  ) 
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) 
// 	 ){
// 	//      if(gData->Getrunnr()==31896 && gData->Geteventnr()==23281){
// 	cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" ndimu "<<fNGoodDIMuons<<" mass "<<invMass<<" dimupt "<<dimuon->GetdimuPt()<<" mupt 1 "<<dimuon->GetMuon1()->Pt()<<" mu phi 1 "<< dimuon->GetMuon1()->Phi()<<" mu th 1"<< dimuon->GetMuon1()->Theta()<<" mu vcrhlid 1 "<< dimuon->GetMuon1()->GetVctrhlID()<<" char 1 "<< dimuon->GetMuon1()->GetCharge()<<" qual 1 "<< dimuon->GetMuon1()->GetQuality()<<"dimuon->GetEtFraction() "<<dimuon->GetEtFraction()<<" abs Cal time: "<<TMath::Abs(gData->Getcal_tg())<<endl; 
// 	cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" ndimu "<<fNGoodDIMuons<<" mass "<<invMass<<" dimupt "<<dimuon->GetdimuPt()<<" mupt 2 "<<dimuon->GetMuon2()->Pt()<<" mu phi 2 "<< dimuon->GetMuon2()->Phi()<<" mu th 2"<< dimuon->GetMuon2()->Theta()<<" mu vcrhlid 2 "<< dimuon->GetMuon2()->GetVctrhlID()<<" char 2 "<< dimuon->GetMuon2()->GetCharge()<<" qual 2 "<< dimuon->GetMuon2()->GetQuality()<<endl;
// 	cout<<"(gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10()) "<<(gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10())<<endl; 
// 	cout<<"(gData->Getcal_et() - gData->Getcal_et10()): "<<(gData->Getcal_et() - gData->Getcal_et10())<<endl;
// 	cout<<"DIMuon cuts:            "<<1*dimuon->GetAllCuts()<<endl;
// 	cout<<"Cal cuts:               "<<1*gCal->GetAllCuts()<<" Et cut: "<<1*gCal->GetETCut()<<" gCal->GetTimeCut(): "<<1*gCal->GetTimeCut()<<" gCal->GetPtOvEtCut(): "<<gCal->GetPtOvEtCut()<<" GetYJBCut(): "<<gCal->GetYJBCut()<<endl;
//  	cout<<"gTrigger->GetAllCuts(): "<<1*gTrigger->GetAllCuts()<<endl;
// 	cout<<"gBac->GetAllCuts():     "<<1*gBac->GetAllCuts()<<endl;
//  	cout<<"gVertex->GetAllCuts():  "<<1*gVertex->GetAllCuts()<<endl;
//  	cout<<"gRuns->GetAllCuts():    "<<1*gRuns->GetAllCuts()<<endl;
//       }

      if( gHeader->GetAllCuts() ) {
//       if( 
// 	 (gData->Getrunnr()==20750 && gData->Geteventnr()==14345) ||
// 	 (gData->Getrunnr()==20791 && gData->Geteventnr()==139670) ||
// 	 (gData->Getrunnr()==21189 && gData->Geteventnr()==39557 ) ||
// 	 (gData->Getrunnr()==21219 && gData->Geteventnr()==66189 ) ||
// 	 (gData->Getrunnr()==21447 && gData->Geteventnr()==40770 ) ||
// 	 (gData->Getrunnr()==21448 && gData->Geteventnr()==8917  ) ||
// 	 (gData->Getrunnr()==21641 && gData->Geteventnr()==12017 ) ||
// 	 (gData->Getrunnr()==21647 && gData->Geteventnr()==59679 ) ||
// 	 (gData->Getrunnr()==21653 && gData->Geteventnr()==9592  ) ||
// 	 (gData->Getrunnr()==21663 && gData->Geteventnr()==49093 ) ||
// 	 (gData->Getrunnr()==21665 && gData->Geteventnr()==65707 ) ||
// 	 (gData->Getrunnr()==21796 && gData->Geteventnr()==8693  ) ||
// 	 (gData->Getrunnr()==21953 && gData->Geteventnr()==34442 ) ||
// 	 (gData->Getrunnr()==21953 && gData->Geteventnr()==35722 ) ||
// 	 (gData->Getrunnr()==22018 && gData->Geteventnr()==41439 ) ||
// 	 (gData->Getrunnr()==22061 && gData->Geteventnr()==60653 ) ||
// 	 (gData->Getrunnr()==22111 && gData->Geteventnr()==38536 ) ||
// 	 (gData->Getrunnr()==22113 && gData->Geteventnr()==23542 ) ||
// 	 (gData->Getrunnr()==22128 && gData->Geteventnr()==13114 ) ||
// 	 (gData->Getrunnr()==22151 && gData->Geteventnr()==20888 ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==7248  ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==20845 ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==20845 ) ||
// 	 (gData->Getrunnr()==22187 && gData->Geteventnr()==83101 ) ||
// 	 (gData->Getrunnr()==22244 && gData->Geteventnr()==17995 ) ||
// 	 (gData->Getrunnr()==22264 && gData->Geteventnr()==6607  ) 
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) ||
// // 	 (gData->Getrunnr()== && gData->Geteventnr()==		) 
// 	 ){
// 	//      if(gData->Getrunnr()==31896 && gData->Geteventnr()==23281){
// 	cout<<(char)27<<"[01;33m"<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" ALARM!!! This should not be seen!!!"<<(char)27<<"[0m"<<endl;
// 	getchar();
// // 	cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" ndimu "<<fNGoodDIMuons<<" mass "<<invMass<<" dimupt "<<dimuon->GetdimuPt()<<" mupt 2 "<<dimuon->GetMuon2()->Pt()<<" mu phi 2 "<< dimuon->GetMuon2()->Phi()<<" mu th 2"<< dimuon->GetMuon2()->Theta()<<" mu vcrhlid 2 "<< dimuon->GetMuon2()->GetVctrhlID()<<" char 2 "<< dimuon->GetMuon2()->GetCharge()<<" qual 2 "<< dimuon->GetMuon2()->GetQuality()<<endl;
// // 	cout<<"(gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10()) "<<(gData->Getcal_et() - gData->Getsipt(0) - gData->Getcal_et10())<<endl; 
// // 	cout<<"(gData->Getcal_et() - gData->Getcal_et10()): "<<(gData->Getcal_et() - gData->Getcal_et10())<<endl;
// // 	cout<<"DIMuon cuts:            "<<1*dimuon->GetAllCuts()<<endl;
// // 	cout<<"Cal cuts:               "<<1*gCal->GetAllCuts()<<" Et cut: "<<1*gCal->GetETCut()<<" gCal->GetTimeCut(): "<<1*gCal->GetTimeCut()<<" gCal->GetPtOvEtCut(): "<<gCal->GetPtOvEtCut()<<" GetYJBCut(): "<<gCal->GetYJBCut()<<endl;
// //  	cout<<"gTrigger->GetAllCuts(): "<<1*gTrigger->GetAllCuts()<<endl;
// // 	cout<<"gBac->GetAllCuts():     "<<1*gBac->GetAllCuts()<<endl;
// //  	cout<<"gVertex->GetAllCuts():  "<<1*gVertex->GetAllCuts()<<endl;
// //  	cout<<"gRuns->GetAllCuts():    "<<1*gRuns->GetAllCuts()<<endl;
// // 	gCal->PrintMessage("das");
//       }	
	
	//       if( fNGoodDIMuons >=3 ) {
	//  	cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" ndimu "<<fNGoodDIMuons<<" mass "<<invMass<<" dimupt "<<dimuon->GetdimuPt()<<" mupt 1 "<<dimuon->GetMuon1()->Pt()<<" mu phi 1 "<< dimuon->GetMuon1()->Phi()<<" mu th 1"<< dimuon->GetMuon1()->Theta()<<" mu vcrhlid 1 "<< dimuon->GetMuon1()->GetVctrhlID()<<" char 1 "<< dimuon->GetMuon1()->GetCharge()<<" qual 1 "<< dimuon->GetMuon1()->GetQuality()<<endl; 
	//  	cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" ndimu "<<fNGoodDIMuons<<" mass "<<invMass<<" dimupt "<<dimuon->GetdimuPt()<<" mupt 2 "<<dimuon->GetMuon2()->Pt()<<" mu phi 2 "<< dimuon->GetMuon2()->Phi()<<" mu th 2"<< dimuon->GetMuon2()->Theta()<<" mu vcrhlid 2 "<< dimuon->GetMuon2()->GetVctrhlID()<<" char 2 "<< dimuon->GetMuon2()->GetCharge()<<" qual 2 "<< dimuon->GetMuon2()->GetQuality()<<endl<<endl; 
	//       }

	fGeneralDIMuonMass->Fill(invMass);
	if(invMass <= 4 )
	  fGeneralDIMuonMassLow->Fill(invMass);
	if(invMass > 4 )
	  fGeneralDIMuonMassHigh->Fill(invMass);
	if( dimuon->GetDifCharge()) // enter this before allll unlike signs!
	  fGeneralDIMuonMass_UnlikeSign->Fill(invMass);
	if(invMass <= 4 ){
	  if( dimuon->GetDifCharge()) // enter this before allll unlike signs!
	    fGeneralDIMuonMassLow_UnlikeSign->Fill(invMass);
	}
	if(invMass > 4 ){
	  if( dimuon->GetDifCharge()) // enter this before allll unlike signs!
	    fGeneralDIMuonMassHigh_UnlikeSign->Fill(invMass);
	}

	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())    fGeneralMass_lu_is->Fill(invMass,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())    fGeneralMass_ll_is->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass > 4  &&  dimuon->GetDifCharge())    fGeneralMass_hu_is->Fill(invMass,gHeader->GetWeight()); 
	  if(invMass > 4  && !dimuon->GetDifCharge())    fGeneralMass_hl_is->Fill(invMass,gHeader->GetWeight()); 
	}						      
	else{					      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())    fGeneralMass_lu_nis->Fill(invMass,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())    fGeneralMass_ll_nis->Fill(invMass,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())    fGeneralMass_hu_nis->Fill(invMass,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())    fGeneralMass_hl_nis->Fill(invMass,gHeader->GetWeight());
	}                                                 

	fGeneralDeltaR->Fill(deltaR,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fGeneralDeltaR_lu_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fGeneralDeltaR_ll_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fGeneralDeltaR_hu_is->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fGeneralDeltaR_hl_is->Fill(deltaR,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fGeneralDeltaR_lu_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fGeneralDeltaR_ll_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fGeneralDeltaR_hu_nis->Fill(deltaR,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fGeneralDeltaR_hl_nis->Fill(deltaR,gHeader->GetWeight());
	}

	//	cout<<"r/e"<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<"REC:  Event contains rec dimuon!"<<endl;
	//	getchar();
	if(invMass > 3.25 ) {
	  fGeneralDeltaPhi->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	    if(invMass <= 4 &&  dimuon->GetDifCharge())	fGeneralDeltaPhi_lu_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge())	fGeneralDeltaPhi_ll_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge())	fGeneralDeltaPhi_hu_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge())	fGeneralDeltaPhi_hl_is->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())	fGeneralDeltaPhi_lu_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge())	fGeneralDeltaPhi_ll_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge())	fGeneralDeltaPhi_hu_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge())	fGeneralDeltaPhi_hl_nis->Fill( TMath::Abs(deltaPhi),gHeader->GetWeight());
	  }
	}

	fGeneralDeltaEta->Fill(deltaEta,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneralDeltaEta_lu_is->Fill(deltaEta,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneralDeltaEta_ll_is->Fill(deltaEta,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneralDeltaEta_hu_is->Fill(deltaEta,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())      fGeneralDeltaEta_hl_is->Fill(deltaEta,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneralDeltaEta_lu_nis->Fill(deltaEta,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneralDeltaEta_ll_nis->Fill(deltaEta,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneralDeltaEta_hu_nis->Fill(deltaEta,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())      fGeneralDeltaEta_hl_nis->Fill(deltaEta,gHeader->GetWeight());
	}

	fGeneralDeltaTheta->Fill(deltaTheta,gHeader->GetWeight());

	fGeneraldimuphi->Fill(dimuphi,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimuphi_lu_is->Fill(dimuphi,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimuphi_ll_is->Fill(dimuphi,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimuphi_hu_is->Fill(dimuphi,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimuphi_hl_is->Fill(dimuphi,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimuphi_lu_nis->Fill(dimuphi,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimuphi_ll_nis->Fill(dimuphi,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimuphi_hu_nis->Fill(dimuphi,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimuphi_hl_nis->Fill(dimuphi,gHeader->GetWeight());
	}

	fGeneraldimueta->Fill(dimueta,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimueta_lu_is->Fill(dimueta,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimueta_ll_is->Fill(dimueta,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimueta_hu_is->Fill(dimueta,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimueta_hl_is->Fill(dimueta,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())      fGeneraldimueta_lu_nis->Fill(dimueta,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())      fGeneraldimueta_ll_nis->Fill(dimueta,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())      fGeneraldimueta_hu_nis->Fill(dimueta,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())      fGeneraldimueta_hl_nis->Fill(dimueta,gHeader->GetWeight());
	}

	fGeneralPtAsymetry->Fill(ptAsymetry,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fGeneralPtAsymetry_lu_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fGeneralPtAsymetry_ll_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fGeneralPtAsymetry_hu_is->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fGeneralPtAsymetry_hl_is->Fill(ptAsymetry,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())	fGeneralPtAsymetry_lu_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge())	fGeneralPtAsymetry_ll_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge())	fGeneralPtAsymetry_hu_nis->Fill(ptAsymetry,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge())	fGeneralPtAsymetry_hl_nis->Fill(ptAsymetry,gHeader->GetWeight());
	}
	
	fGeneralpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fGeneralpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneralpt_lu_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fGeneralpt_lu_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralpt_ll_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneralpt_ll_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralpt_hu_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneralpt_hu_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fGeneralpt_hl_is->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneralpt_hl_is->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralpt_lu_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneralpt_lu_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralpt_ll_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneralpt_ll_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralpt_hu_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fGeneralpt_hu_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fGeneralpt_hl_nis->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneralpt_hl_nis->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  }
	}

	fGeneraldimupt->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldimupt_lu_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldimupt_ll_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldimupt_hu_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldimupt_hl_is->Fill(dimuon->GetdimuPt(),gHeader->GetWeight());}
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldimupt_lu_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldimupt_ll_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldimupt_hu_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldimupt_hl_nis->Fill(dimuon->GetdimuPt(),gHeader->GetWeight()); }
	}

	fGeneraleta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fGeneraleta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneraleta_lu_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraleta_lu_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneraleta_ll_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraleta_ll_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fGeneraleta_hu_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraleta_hu_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneraleta_hl_is->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraleta_hl_is->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneraleta_lu_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraleta_lu_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneraleta_ll_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fGeneraleta_ll_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fGeneraleta_hu_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fGeneraleta_hu_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneraleta_hl_nis->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraleta_hl_nis->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}

	if(!dimuon->GetDifCharge()){

	  if(dimuon->GetMuon1()->GetCharge()>0){
	    fGeneralCharge_Like->Fill(dimuon->GetMuon1()->GetCharge(),gHeader->GetWeight());
	    fGeneralCharge_Like->Fill(dimuon->GetMuon2()->GetCharge(),gHeader->GetWeight());
	  }
	  if(dimuon->GetMuon1()->GetCharge()<0){
	    fGeneralCharge_Like->Fill(dimuon->GetMuon1()->GetCharge(),gHeader->GetWeight());
	    fGeneralCharge_Like->Fill(dimuon->GetMuon2()->GetCharge(),gHeader->GetWeight());
	  }
	}

	fGeneralVertexOvNTracks->Fill(VertexOvNTracks,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralVertexOvNTracks_is_lu->Fill(VertexOvNTracks,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralVertexOvNTracks_is_ll->Fill(VertexOvNTracks,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralVertexOvNTracks_is_hu->Fill(VertexOvNTracks,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralVertexOvNTracks_is_hl->Fill(VertexOvNTracks,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralVertexOvNTracks_nis_lu->Fill(VertexOvNTracks,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralVertexOvNTracks_nis_ll->Fill(VertexOvNTracks,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralVertexOvNTracks_nis_hu->Fill(VertexOvNTracks,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralVertexOvNTracks_nis_hl->Fill(VertexOvNTracks,gHeader->GetWeight());
	}

// Secondary Vertex Distributions

	secvtx   = 0; // Needs to be reset !!!
	nrsecvtx = 0; //

	if(gData->Getnr_secvtx()==0){
	  nrsecvtx = gData->Getnr_secvtx();
	}

	if(gData->Getnr_secvtx()>0){

	  for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

	    if( gData->Getvtxsec_x(i)==666 ){

	      nrsecvtx = 0;
	    }

	    if(gData->Getvtxsec_x(i)!=666 && gData->Getvtxsec_y(i)!=666 && gData->Getvtxsec_z(i)!=666 && 
               gData->Getvtxredprm_x()!=666 && gData->Getvtxredprm_y()!= 666 && gData->Getvtxredprm_z()!= 666 ){

	      secvtx    = 1;
	      nrsecvtx += secvtx;

	      fGeneralVtxMass->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralVtxMass_is_lu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralVtxMass_is_ll->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralVtxMass_is_hu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralVtxMass_is_hl->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralVtxMass_nis_lu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralVtxMass_nis_ll->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralVtxMass_nis_hu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralVtxMass_nis_hl->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
	      }

	      fGeneralChi2->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralChi2_is_lu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralChi2_is_ll->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralChi2_is_hu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralChi2_is_hl->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralChi2_nis_lu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralChi2_nis_ll->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralChi2_nis_hu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralChi2_nis_hl->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
	      }

	      fGeneralNdof->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNdof_is_lu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNdof_is_ll->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNdof_is_hu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNdof_is_hl->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNdof_nis_lu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNdof_nis_ll->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNdof_nis_hu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNdof_nis_hl->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      }

              fGeneralChi2Ndof->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_is_lu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		}
		if(invMass <= 4 && !dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_is_ll->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		}
		if(invMass > 4  &&  dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_is_hu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		}
		if(invMass > 4  && !dimuon->GetDifCharge()) { 
		  fGeneralChi2Ndof_is_hl->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		}
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_nis_lu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		}
		if(invMass <= 4 && !dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_nis_ll->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		}
		if(invMass > 4  &&  dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_nis_hu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		}
		if(invMass > 4  && !dimuon->GetDifCharge()) {
		  fGeneralChi2Ndof_nis_hl->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		}
	      }

	      fGeneralMulti->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMulti_is_lu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMulti_is_ll->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMulti_is_hu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMulti_is_hl->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMulti_nis_lu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMulti_nis_ll->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMulti_nis_hu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMulti_nis_hl->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
	      }

	      r2d_v.SetXYZ(gData->Getvtxsec_x(i)-gData->Getvtxredprm_x(), gData->Getvtxsec_y(i)-gData->Getvtxredprm_y(), 0);

	      phi_d = gData->Getkt_phijet_a(i);

	      upt_v.SetXYZ(TMath::Cos(phi_d),TMath::Sin(phi_d), 0);

	      fSecvtx_DL2       = r2d_v.Dot(upt_v);
	      fSecvtx_DL2_err   = (gData->Getvtxredprm_cov(0)+gData->Getvtxsec_cov(i,0))*(TMath::Power(TMath::Cos(phi_d),2));
	      fSecvtx_DL2_err  += (gData->Getvtxredprm_cov(2)+gData->Getvtxsec_cov(i,2))*(TMath::Power(TMath::Sin(phi_d),2));
	      fSecvtx_DL2_err  += 2*(gData->Getvtxredprm_cov(1)+gData->Getvtxsec_cov(i,1))*(TMath::Sin(phi_d)*TMath::Cos(phi_d));
	      fSecvtx_DL2_err   = TMath::Sqrt(fSecvtx_DL2_err);
	      /*
	      if(gData->Getrunnr()==1){
		static TRandom3 *rnd      = new TRandom3();
		Double_t         nr_rand  = rnd->Rndm();
		Float_t          exponent = 5.;

		if(nr_rand < 0.05){
		  Double_t nr_rand_gauss = rnd->Gaus();
		  Float_t  smearvalue    = 2.3*fSecvtx_DL2_err*nr_rand_gauss;
		  fSecvtx_DL2           += smearvalue;
		  fSecvtx_DL2_sign  = fSecvtx_DL2 / fSecvtx_DL2_err;
		}

		if(nr_rand < 0.01){
		  Double_t nr_rand_gauss = rnd->Gaus();
		  Float_t  smearvalue    = 3.0*fSecvtx_DL2_err*nr_rand_gauss;
		  fSecvtx_DL2           += smearvalue;
		  fSecvtx_DL2_sign  = fSecvtx_DL2 / fSecvtx_DL2_err;
		}
		
		if(nr_rand > 0.2*fSecvtx_DL2_err && nr_rand < 0.7*fSecvtx_DL2_err){
		  static TRandom3 *rnd2      = new TRandom3();
		  Double_t         nr_rand2  = rnd2->Rndm();
		  Float_t          randtemp  = 2*nr_rand2-1;
		  Float_t          sign      = randtemp/TMath::Abs(randtemp);
	  	  fSecvtx_DL2               += sign*TMath::Log(1-TMath::Abs(randtemp))/(-exponent);
		  fSecvtx_DL2_sign  = fSecvtx_DL2 / fSecvtx_DL2_err;
		}
		
		fGeneralDL2->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_is_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_is_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_is_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_is_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_nis_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_nis_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_nis_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_nis_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}

		fGeneralDL2_err->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_err_is_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_err_is_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_err_is_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_err_is_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_err_nis_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_err_nis_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_err_nis_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_err_nis_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		}

		fGeneralDL2_Sign->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}

		if( fSecvtx_DL2_sign > 0 ){
		  fSecvtx_DL2_signp = fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrp->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  else{
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }

		  if(gData->Getvtxsec_mass(i) >= 2) {

		    fGeneral_mvtx2_DL2_Sign_Mirrp->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if( !dimuon->GetSqSumIsolationCut()) {      
		      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass <= 4 && !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 && !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		    }
		    else{
		      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass <= 4 && !dimuon->GetDifCharge()){
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 && !dimuon->GetDifCharge()){
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		    }
		  }
		}

		if( fSecvtx_DL2_sign < 0 ){
		  fSecvtx_DL2_signm = -fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrm->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  else{
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }

		  if(gData->Getvtxsec_mass(i) >= 2){
		    fGeneral_mvtx2_DL2_Sign_Mirrm->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if( !dimuon->GetSqSumIsolationCut()) {      
		      if(invMass<=4&&  dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass<=4&& !dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&&  dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&& !dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		    }
		    else{
		      if(invMass<=4&&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass<=4&& !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&& !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		    }
		  }
		}
	      
		if(gData->Getvtxsec_mass(i) >= 2){

		  fGeneral_mvtx2_VtxMass->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()){
		      fGeneral_mvtx2_VtxMass_is_lu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_is_ll->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_is_hu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_is_hl->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_lu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_ll->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_hu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_hl->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Chi2->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_lu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_ll->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_hu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_hl->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_lu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_ll->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_hu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_hl->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Ndof->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_lu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_ll->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_hu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_hl->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_nis_lu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_nis_ll->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_nis_hu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) { 
		      fGeneral_mvtx2_Ndof_nis_hl->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Chi2Ndof->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_is_lu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_is_ll->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_is_hu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) { 
		      fGeneral_mvtx2_Chi2Ndof_is_hl->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_lu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_ll->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_hu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_hl->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Multi->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_lu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_ll->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_hu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_hl->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_lu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_ll->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_hu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_hl->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());;
		    }
		  }
		
		  fGeneral_mvtx2_DL2->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());;
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());;
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_DL2_err->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_DL2_Sign->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		  }
		}
	      }

	      if( gData->Getrunnr() > 100 ){
	      */       
		fSecvtx_DL2_sign  = fSecvtx_DL2 / fSecvtx_DL2_err;
	    		
		if( fSecvtx_DL2_sign > 0 ){
		  fSecvtx_DL2_signp = fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrp->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_is_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }
		  else{
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrp_nis_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		  }

		  if(gData->Getvtxsec_mass(i) >= 2) {

		    fGeneral_mvtx2_DL2_Sign_Mirrp->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		    if( !dimuon->GetSqSumIsolationCut()) {      
		      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass <= 4 && !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 && !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_is_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		    }
		    else{
		      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_lu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass <= 4 && !dimuon->GetDifCharge()){
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_ll->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 &&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hu->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		      if(invMass > 4 && !dimuon->GetDifCharge()){
			fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hl->Fill(fSecvtx_DL2_signp,gHeader->GetWeight());
		      }
		    }
		  }
		}
	    	    
		if( fSecvtx_DL2_sign < 0 ){
		  fSecvtx_DL2_signm = -fSecvtx_DL2_sign;

		  fGeneralDL2_Sign_Mirrm->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_is_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }
		  else{
		    if(invMass<=4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass<=4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&&  dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if(invMass> 4&& !dimuon->GetDifCharge()) fGeneralDL2_Sign_Mirrm_nis_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		  }

		  if(gData->Getvtxsec_mass(i) >= 2){
		    fGeneral_mvtx2_DL2_Sign_Mirrm->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		    if( !dimuon->GetSqSumIsolationCut()) {      
		      if(invMass<=4&&  dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass<=4&& !dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&&  dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&& !dimuon->GetDifCharge()) { 
			fGeneral_mvtx2_DL2_Sign_Mirrm_is_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		    }
		    else{
		      if(invMass<=4&&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_lu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass<=4&& !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_ll->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&&  dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hu->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		      if(invMass> 4&& !dimuon->GetDifCharge()) {
			fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hl->Fill(fSecvtx_DL2_signm,gHeader->GetWeight());
		      }
		    }
		  }
		}

		fGeneralDL2->Fill(fSecvtx_DL2,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_is_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_is_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_is_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_is_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_nis_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_nis_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_nis_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_nis_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		}

		fGeneralDL2_err->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_err_is_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_err_is_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_err_is_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_err_is_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_err_nis_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_err_nis_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_err_nis_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_err_nis_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		}


		fGeneralDL2_Sign->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		if( !dimuon->GetSqSumIsolationCut()) {      
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_is_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}
		else{
		  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralDL2_Sign_nis_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		}

		if(gData->Getvtxsec_mass(i) >= 2){

		  fGeneral_mvtx2_VtxMass->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()){
		      fGeneral_mvtx2_VtxMass_is_lu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_is_ll->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_is_hu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_is_hl->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_lu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_ll->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_hu->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		    if(invMass > 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_VtxMass_nis_hl->Fill(gData->Getvtxsec_mass(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Chi2->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_lu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_ll->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_hu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_is_hl->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_lu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_ll->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_hu->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2_nis_hl->Fill(gData->Getvtxsec_chi2(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Ndof->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_lu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_ll->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_hu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_is_hl->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_nis_lu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_nis_ll->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Ndof_nis_hu->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) { 
		      fGeneral_mvtx2_Ndof_nis_hl->Fill(gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Chi2Ndof->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_is_lu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_is_ll->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_is_hu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) { 
		      fGeneral_mvtx2_Chi2Ndof_is_hl->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight()); 
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_lu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_ll->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_hu->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Chi2Ndof_nis_hl->Fill(gData->Getvtxsec_chi2(i)/gData->Getvtxsec_ndf(i),gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_Multi->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_lu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_ll->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_hu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_is_hl->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_lu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_ll->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_hu->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_Multi_nis_hl->Fill(gData->Getvtxsec_multi(i),gHeader->GetWeight());;
		    }
		  }
		
		  fGeneral_mvtx2_DL2->Fill(fSecvtx_DL2,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());;
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_is_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_lu->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_ll->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_hu->Fill(fSecvtx_DL2,gHeader->GetWeight());;
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_nis_hl->Fill(fSecvtx_DL2,gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_DL2_err->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_is_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_lu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_ll->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_hu->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_err_nis_hl->Fill(fSecvtx_DL2_err,gHeader->GetWeight());
		    }
		  }

		  fGeneral_mvtx2_DL2_Sign->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		  if( !dimuon->GetSqSumIsolationCut()) {      
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_is_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		  }
		  else{
		    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_lu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass <= 4 && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_ll->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  &&  dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_hu->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		    if(invMass > 4  && !dimuon->GetDifCharge()) {
		      fGeneral_mvtx2_DL2_Sign_nis_hl->Fill(fSecvtx_DL2_sign,gHeader->GetWeight());
		    }
		  }
		}
	      }
	    }
	  }
	//      }

	fGeneralNrsecvtx->Fill(nrsecvtx,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
    	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_is_lu->Fill(nrsecvtx,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNrsecvtx_is_ll->Fill(nrsecvtx,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_is_hu->Fill(nrsecvtx,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNrsecvtx_is_hl->Fill(nrsecvtx,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_lu->Fill(nrsecvtx,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_ll->Fill(nrsecvtx,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_hu->Fill(nrsecvtx,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNrsecvtx_nis_hl->Fill(nrsecvtx,gHeader->GetWeight());
	}

// Forward Muon information

	if( dimuon->GetMuon1()->GetForwardTrackMuon()){
	  if(dimuon->GetMuon1()->GetMPMatch()) {

	    fGeneralMunphi->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
    	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_is_lu->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMunphi_is_ll->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_is_hu->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMunphi_is_hl->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_lu->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_ll->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_hu->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_hl->Fill(dimuon->GetMuon1()->GetMunphi(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMundof->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMundof_is_lu->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMundof_is_ll->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMundof_is_hu->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMundof_is_hl->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMundof_nis_lu->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMundof_nis_ll->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMundof_nis_hu->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMundof_nis_hl->Fill(dimuon->GetMuon1()->GetMundof(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMupmat->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) { 
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_is_lu->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMupmat_is_ll->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_is_hu->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMupmat_is_hl->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_lu->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_ll->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_hu->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_hl->Fill(dimuon->GetMuon1()->GetProbability(),gHeader->GetWeight());
	      }
	    }

	    fGeneralMPMatchID->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {        
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_lu->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_ll->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_hu->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_hl->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      } 
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_lu->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_ll->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_hu->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_hl->Fill(dimuon->GetMuon1()->GetMPMatchID(),gHeader->GetWeight());
	      }
	    }

	    fGeneralMuMvID->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_lu->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_ll->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_hu->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_hl->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      } 
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_lu->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_ll->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_hu->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_hl->Fill(dimuon->GetMuon1()->GetMvID(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMuMufoID->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_lu->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_ll->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_hu->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_hl->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_lu->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_ll->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_hu->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_hl->Fill(dimuon->GetMuon1()->GetMufoID(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMuz->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
       	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_is_lu->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuz_is_ll->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuz_is_hu->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuz_is_hl->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_nis_lu->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuz_nis_ll->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuz_nis_hu->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuz_nis_hl->Fill(dimuon->GetMuon1()->GetMuz(),gHeader->GetWeight());
	    }
	  }
	}
	else if(dimuon->GetMuon2()->GetForwardTrackMuon()){
	  if(dimuon->GetMuon2()->GetMPMatch()) {
	    fGeneralMunphi->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_is_lu->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMunphi_is_ll->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_is_hu->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMunphi_is_hl->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_lu->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_ll->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_hu->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMunphi_nis_hl->Fill(dimuon->GetMuon2()->GetMunphi(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMundof->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMundof_is_lu->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMundof_is_ll->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMundof_is_hu->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMundof_is_hl->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMundof_nis_lu->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMundof_nis_ll->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMundof_nis_hu->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMundof_nis_hl->Fill(dimuon->GetMuon2()->GetMundof(),gHeader->GetWeight());
	      }
	    }

	    fGeneralMupmat->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) { 
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_is_lu->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMupmat_is_ll->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_is_hu->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMupmat_is_hl->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_lu->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_ll->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_hu->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMupmat_nis_hl->Fill(dimuon->GetMuon2()->GetProbability(),gHeader->GetWeight());
	      }
	    }

	    fGeneralMPMatchID->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
      	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_lu->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_ll->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_hu->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_is_hl->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_lu->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_ll->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_hu->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMPMatchID_nis_hl->Fill(dimuon->GetMuon2()->GetMPMatchID(),gHeader->GetWeight());
	      }
	    }

	    fGeneralMuMvID->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_lu->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_ll->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_hu->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_is_hl->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());} 
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_lu->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_ll->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_hu->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMvID_nis_hl->Fill(dimuon->GetMuon2()->GetMvID(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMuMufoID->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_lu->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass <= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_ll->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_hu->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass > 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_is_hl->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	    }
	    else{
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_lu->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_ll->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_hu->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneralMuMufoID_nis_hl->Fill(dimuon->GetMuon2()->GetMufoID(),gHeader->GetWeight());
	      }
	    }
  
	    fGeneralMuz->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    if( !dimuon->GetSqSumIsolationCut()) {      
    	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_is_lu->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuz_is_ll->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuz_is_hu->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuz_is_hl->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight()); 
	    }
	    else{
	      if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuz_nis_lu->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	      if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuz_nis_ll->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuz_nis_hu->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	      if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuz_nis_hl->Fill(dimuon->GetMuon2()->GetMuz(),gHeader->GetWeight());
	    }
	  }
	}

	fGeneralMuBacMatID->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	fGeneralMuBacMatID->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_is_lu->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_is_lu->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_is_ll->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_is_ll->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_is_hu->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_is_hu->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_is_hl->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_is_hl->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_nis_lu->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_nis_lu->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_nis_ll->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_nis_ll->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_nis_hu->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_nis_hu->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge()) {
	    fGeneralMuBacMatID_nis_hl->Fill(dimuon->GetMuon1()->GetBacMatID(),gHeader->GetWeight());
	    fGeneralMuBacMatID_nis_hl->Fill(dimuon->GetMuon2()->GetBacMatID(),gHeader->GetWeight());
	  }
	}
      
	fGeneralNBacMat->Fill(gData->GetBm_n(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNBacMat_is_lu->Fill(gData->GetBm_n(),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNBacMat_is_ll->Fill(gData->GetBm_n(),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNBacMat_is_hu->Fill(gData->GetBm_n(),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNBacMat_is_hl->Fill(gData->GetBm_n(),gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNBacMat_nis_lu->Fill(gData->GetBm_n(),gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNBacMat_nis_ll->Fill(gData->GetBm_n(),gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNBacMat_nis_hu->Fill(gData->GetBm_n(),gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNBacMat_nis_hl->Fill(gData->GetBm_n(),gHeader->GetWeight());
	}

	for( Int_t p = 0; p < gData->GetBm_n(); p++) {

	  fGeneralBacMat_VCID->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_lu->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_ll->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_hu->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_is_hl->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_lu->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_ll->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_hu->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_VCID_nis_hl->Fill(gData->GetBm_idvc(p),gHeader->GetWeight());
	  }

	  fGeneralBacMat_MuBacID->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_is_lu->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	    if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_is_ll->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	    if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_is_hu->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	    if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_is_hl->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_nis_lu->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	    if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_nis_ll->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	    if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_nis_hu->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	    if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralBacMat_MuBacID_nis_hl->Fill(gData->GetBm_idmubac(p),gHeader->GetWeight());
	  }

	  fGeneralBacMat_Istop->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_lu->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_ll->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_hu->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_is_hl->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_lu->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_ll->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_hu->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Istop_nis_hl->Fill(gData->GetBm_istop(p),gHeader->GetWeight());
	  }

	  fGeneralBacMat_Error->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Error_is_lu->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Error_is_ll->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Error_is_hu->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Error_is_hl->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Error_nis_lu->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Error_nis_ll->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Error_nis_hu->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Error_nis_hl->Fill(gData->GetBm_error(p),gHeader->GetWeight());
	  }

	  fGeneralBacMat_Readout->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Readout_is_lu->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Readout_is_ll->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Readout_is_hu->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Readout_is_hl->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	  }
	  else{
	    if(invMass<= 4 &&  dimuon->GetDifCharge()) fGeneralBacMat_Readout_nis_lu->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    if(invMass<= 4 && !dimuon->GetDifCharge()) fGeneralBacMat_Readout_nis_ll->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    if(invMass> 4  &&  dimuon->GetDifCharge()) fGeneralBacMat_Readout_nis_hu->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	    if(invMass> 4  && !dimuon->GetDifCharge()) fGeneralBacMat_Readout_nis_hl->Fill(gData->GetBm_readout(p),gHeader->GetWeight());
	  }
	}

// Signed Impact Parameter and Significance

	if(dimuon->GetMuon1()->GetJetID()>0){

	  fGeneralImpact2D->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) {
	      fGeneralImpact2D_is_lu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_is_ll->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_is_hu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_is_hl->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_nis_lu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_nis_ll->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_nis_hu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneralImpact2D_nis_hl->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	  }

	  fGeneralImpact2D_Sign->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_Sign_is_lu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_Sign_is_ll->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_Sign_is_hu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_Sign_is_hl->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_Sign_nis_lu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_Sign_nis_ll->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_Sign_nis_hu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneralImpact2D_Sign_nis_hl->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	  }
	}

	if(dimuon->GetMuon2()->GetJetID()>0){
	  fGeneralImpact2D->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_is_lu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_is_ll->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_is_hu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_is_hl->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_nis_lu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_nis_ll->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_nis_hu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneralImpact2D_nis_hl->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    }
	  }

	  fGeneralImpact2D_Sign->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_Sign_is_lu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_Sign_is_ll->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_Sign_is_hu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneralImpact2D_Sign_is_hl->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_Sign_nis_lu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	      fGeneralImpact2D_Sign_nis_ll->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {
	      fGeneralImpact2D_Sign_nis_hu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneralImpact2D_Sign_nis_hl->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	    }
	  }
	}

	/*
	fGeneralImpact2D->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	fGeneralImpact2D->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_lu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	    fGeneralImpact2D_is_lu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_ll->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    fGeneralImpact2D_is_ll->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_is_hu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	    fGeneralImpact2D_is_hu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_is_hl->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight()); 
	    fGeneralImpact2D_is_hl->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_nis_lu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	    fGeneralImpact2D_nis_lu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_nis_ll->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	    fGeneralImpact2D_nis_ll->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_nis_hu->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	    fGeneralImpact2D_nis_hu->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralImpact2D_nis_hl->Fill(dimuon->GetMuon1()->GetImpactMuon2D(),gHeader->GetWeight());
	    fGeneralImpact2D_nis_hl->Fill(dimuon->GetMuon2()->GetImpactMuon2D(),gHeader->GetWeight());
	  }
	}

	fGeneralImpact2D_Sign->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	fGeneralImpact2D_Sign->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_lu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	    fGeneralImpact2D_Sign_is_lu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_ll->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    fGeneralImpact2D_Sign_is_ll->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralImpact2D_Sign_is_hu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	    fGeneralImpact2D_Sign_is_hu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_is_hl->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight()); 
	    fGeneralImpact2D_Sign_is_hl->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight()); 
	  } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_nis_lu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	    fGeneralImpact2D_Sign_nis_lu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralImpact2D_Sign_nis_ll->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	    fGeneralImpact2D_Sign_nis_ll->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_nis_hu->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	    fGeneralImpact2D_Sign_nis_hu->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {
	    fGeneralImpact2D_Sign_nis_hl->Fill(dimuon->GetMuon1()->GetImpactSig(),gHeader->GetWeight());
	    fGeneralImpact2D_Sign_nis_hl->Fill(dimuon->GetMuon2()->GetImpactSig(),gHeader->GetWeight());
	  }
	}
	*/

// Muon-Jet Distributions

// Both muons matched to a jet

	if(dimuon->GetMuon1()->GetJetID()>0 && dimuon->GetMuon2()->GetJetID()>0){
	  fGeneralMuJetDeltaR->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	  fGeneralMuJetDeltaR->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneralMuJetDeltaR_is_lu->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	      fGeneralMuJetDeltaR_is_lu->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	      fGeneralMuJetDeltaR_is_ll->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	      fGeneralMuJetDeltaR_is_ll->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	      fGeneralMuJetDeltaR_is_hu->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	      fGeneralMuJetDeltaR_is_hu->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneralMuJetDeltaR_is_hl->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	      fGeneralMuJetDeltaR_is_hl->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneralMuJetDeltaR_nis_lu->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight()); 
	      fGeneralMuJetDeltaR_nis_lu->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneralMuJetDeltaR_nis_ll->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight()); 
	      fGeneralMuJetDeltaR_nis_ll->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneralMuJetDeltaR_nis_hu->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	      fGeneralMuJetDeltaR_nis_hu->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneralMuJetDeltaR_nis_hl->Fill(dimuon->GetMuon1()->GetJetDr(),gHeader->GetWeight());
	      fGeneralMuJetDeltaR_nis_hl->Fill(dimuon->GetMuon2()->GetJetDr(),gHeader->GetWeight());
	    }
	  }
	}

        if(dimuon->GetMuon1()->GetJetID()>0 || dimuon->GetMuon2()->GetJetID()>0){


	for ( Int_t j = 0; j < gData->Getkt_njet_a(); j++  ) {
	  //	  if(gData->Getmujetid_a(j)==0){
    
	     if( j+1 == dimuon->GetMuon1()->GetJetID() ) {
	      
	      fMuonJetMass  = gData->Getkt_masjet_a(j);
	      fMuonJetEt    = gData->Getkt_etjet_a(j);
	      fMuonJetEta   = gData->Getkt_etajet_a(j);
	      fMuonJetTheta = 2 * TMath::ATan(TMath::Exp(-fMuonJetEta));
	      fMuonJetE     = fMuonJetEt/TMath::Sin(fMuonJetTheta);
	      fMuonJetP     = TMath::Sqrt(TMath::Power(fMuonJetEt,2)-TMath::Power(fMuonJetMass,2));

	      fMuonJetPt    = fMuonJetP*fMuonJetEt/fMuonJetE;

	      fGeneralMuJetPt->Fill(fMuonJetPt,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_lu->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_ll->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_hu->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_hl->Fill(fMuonJetPt,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_lu->Fill(fMuonJetPt,gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_ll->Fill(fMuonJetPt,gHeader->GetWeight()); 
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hu->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hl->Fill(fMuonJetPt,gHeader->GetWeight());
	      }

	      fGeneralMuJetEt->Fill(fMuonJetEt,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_lu->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_ll->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_hu->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_hl->Fill(fMuonJetEt,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_lu->Fill(fMuonJetEt,gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_ll->Fill(fMuonJetEt,gHeader->GetWeight()); 
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hu->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hl->Fill(fMuonJetEt,gHeader->GetWeight());
	      }

	      fGeneralMuJetEta->Fill(fMuonJetEta,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_lu->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_ll->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_hu->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_hl->Fill(fMuonJetEta,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_lu->Fill(fMuonJetEta,gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_ll->Fill(fMuonJetEta,gHeader->GetWeight()); 
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hu->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hl->Fill(fMuonJetEta,gHeader->GetWeight());
	      }

	      fGeneralMassJet->Fill( fMuonJetMass ,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_is_lu->Fill( fMuonJetMass, gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_is_ll->Fill( fMuonJetMass, gHeader->GetWeight()); 
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_is_hu->Fill( fMuonJetMass, gHeader->GetWeight()); 
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_is_hl->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_lu->Fill( fMuonJetMass, gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_nis_ll->Fill( fMuonJetMass, gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_hu->Fill( fMuonJetMass, gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_nis_hl->Fill( fMuonJetMass, gHeader->GetWeight());
	      }
	    }
	}
      
       
	
	  for ( Int_t j = 0; j < gData->Getkt_njet_a(); j++  ) {
	  
	    if( j+1 == dimuon->GetMuon2()->GetJetID()) {
	      	      
	      fMuonJetMass  = gData->Getkt_masjet_a(j);
	      fMuonJetEt    = gData->Getkt_etjet_a(j);
	      fMuonJetEta   = gData->Getkt_etajet_a(j);
	      fMuonJetTheta = 2 * TMath::ATan(TMath::Exp(-fMuonJetEta));
	      fMuonJetE     = fMuonJetEt/TMath::Sin(fMuonJetTheta);
	      fMuonJetP     = TMath::Sqrt(TMath::Power(fMuonJetEt,2)-TMath::Power(fMuonJetMass,2));
	      fMuonJetPt    = fMuonJetP*fMuonJetEt/fMuonJetE;

	      fGeneralMuJetPt->Fill(fMuonJetPt,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_lu->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_ll->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_is_hu->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_is_hl->Fill(fMuonJetPt,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_lu->Fill(fMuonJetPt,gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_ll->Fill(fMuonJetPt,gHeader->GetWeight()); 		
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hu->Fill(fMuonJetPt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetPt_nis_hl->Fill(fMuonJetPt,gHeader->GetWeight());
	      }

	      fGeneralMuJetEt->Fill(fMuonJetEt,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_lu->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_ll->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_is_hu->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_is_hl->Fill(fMuonJetEt,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_lu->Fill(fMuonJetEt,gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_ll->Fill(fMuonJetEt,gHeader->GetWeight()); 		
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hu->Fill(fMuonJetEt,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEt_nis_hl->Fill(fMuonJetEt,gHeader->GetWeight());
	      }

	      fGeneralMuJetEta->Fill(fMuonJetEta,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_lu->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_ll->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_is_hu->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_is_hl->Fill(fMuonJetEta,gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_lu->Fill(fMuonJetEta,gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_ll->Fill(fMuonJetEta,gHeader->GetWeight()); 
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hu->Fill(fMuonJetEta,gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMuJetEta_nis_hl->Fill(fMuonJetEta,gHeader->GetWeight());
	      }

	      fGeneralMassJet->Fill( fMuonJetMass ,gHeader->GetWeight());
	      if( !dimuon->GetSqSumIsolationCut()) {      
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_is_lu->Fill( fMuonJetMass, gHeader->GetWeight());
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_is_ll->Fill( fMuonJetMass, gHeader->GetWeight());
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_is_hu->Fill( fMuonJetMass, gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_is_hl->Fill( fMuonJetMass, gHeader->GetWeight());
	      }
	      else{
		if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_lu->Fill( fMuonJetMass, gHeader->GetWeight()); 
		if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralMassJet_nis_ll->Fill( fMuonJetMass, gHeader->GetWeight());	
		if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralMassJet_nis_hu->Fill( fMuonJetMass, gHeader->GetWeight());
		if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralMassJet_nis_hl->Fill( fMuonJetMass, gHeader->GetWeight()); 
	      }
	    }
	  }
	}
	
	fGeneralNJets->Fill( NJets,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNJets_is_lu->Fill( NJets,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNJets_is_ll->Fill( NJets,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNJets_is_hu->Fill( NJets,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNJets_is_hl->Fill( NJets,gHeader->GetWeight());
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralNJets_nis_lu->Fill( NJets,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralNJets_nis_ll->Fill( NJets,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralNJets_nis_hu->Fill( NJets,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralNJets_nis_hl->Fill( NJets,gHeader->GetWeight());
	}



	fGeneralphi->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	fGeneralphi->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralphi_lu_is->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_lu_is->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralphi_ll_is->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight()); 
	    fGeneralphi_ll_is->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralphi_hu_is->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_hu_is->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralphi_hl_is->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_hl_is->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralphi_lu_nis->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_lu_nis->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralphi_ll_nis->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_ll_nis->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralphi_hu_nis->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_hu_nis->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralphi_hl_nis->Fill(dimuon->GetMuon1()->Phi(),gHeader->GetWeight());
	    fGeneralphi_hl_nis->Fill(dimuon->GetMuon2()->Phi(),gHeader->GetWeight());
	  }
	}

	fGeneralmuqual->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	fGeneralmuqual->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneralmuqual_lu_is->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_lu_is->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneralmuqual_ll_is->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_ll_is->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneralmuqual_hu_is->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_hu_is->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneralmuqual_hl_is->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_hl_is->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneralmuqual_lu_nis->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_lu_nis->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	    fGeneralmuqual_ll_nis->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_ll_nis->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fGeneralmuqual_hu_nis->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_hu_nis->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fGeneralmuqual_hl_nis->Fill(dimuon->GetMuon1()->GetQuality(),gHeader->GetWeight());
	    fGeneralmuqual_hl_nis->Fill(dimuon->GetMuon2()->GetQuality(),gHeader->GetWeight());
	  }
	}

	//	fGeneralsqisol_10->Fill( TMath::Log10(IsolationSqSum10),gHeader->GetWeight());
	fGeneralsqisol_10->Fill(IsolationSqSum10,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_lu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_ll->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_hu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_is_hl->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_lu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_ll->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_hu->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralsqisol_10_nis_hl->Fill( IsolationSqSum10,gHeader->GetWeight()); }
	}	
	/*
	cout<<" "<< endl;
	cout<<"******* General Muons Control Histrograms ********"<< endl;
	cout<<" "<< endl;
        cout<<"Eventnr: "<< gData->Geteventnr() << endl;
        cout<<" " << endl;
	cout<<"1st Muon Pt:  "<< setw(8) << dimuon->GetMuon1()->Pt()  <<", 2nd Muon Pt:  "<< setw(8) << dimuon->GetMuon2()->Pt() << endl;
        cout<<"1st Muon Eta: "<< setw(8) << dimuon->GetMuon1()->Eta() <<", 2nd Muon Eta: "<< setw(8) << dimuon->GetMuon2()->Eta() << endl;
        cout<<"Dimuon Pt:    "<< setw(8) << dimuon->GetdimuPt()       <<", Dimuon Eta:   "<< setw(8) << dimueta<< endl;
        cout<<"Isolation:    "<< setw(8) << IsolationSqSum10          <<", Pt asym:      "<< setw(8) << ptAsymetry << setw(8) <<", Delta Eta: "<< deltaEta <<endl;
	cout<<"Isolation Muon 1: " << setw(8) << gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9) <<" Isolation Muon 2: " << setw(8) << gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9) << endl;
	cout<<"Nachgerechnete Dimuon Isolation: " << TMath::Sqrt(TMath::Power(gData->Getmuisol(dimuon->GetMuon1()->GetID()-1, 9),2)+TMath::Power(gData->Getmuisol(dimuon->GetMuon2()->GetID()-1, 9),2)) << endl;
	cout<<"1st Muon Quality: " << setw(8) << dimuon->GetMuon1()->GetQuality() <<", 2nd Muon Quality: " << setw(8) << dimuon->GetMuon2()->GetQuality() << endl;
	*/
// Event shape Distributions

	if(gData->Getkt_njet_a()==0){
	  fGeneralthrust  -> Fill(thrust      ,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralthrust_is_lu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralthrust_is_ll -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralthrust_is_hu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralthrust_is_hl -> Fill( thrust, gHeader->GetWeight()); 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralthrust_nis_lu -> Fill( thrust, gHeader->GetWeight()); 
	    if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralthrust_nis_ll -> Fill( thrust, gHeader->GetWeight());
	    if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralthrust_nis_hu -> Fill( thrust, gHeader->GetWeight());
	    if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralthrust_nis_hl -> Fill( thrust, gHeader->GetWeight()); 
	  }
	}
	//************  22.09.2010 Does that make any sense for eventshapes? Don't thinks so :-/
	// if( !(dimuon->GetMuon1()->GetMatched() || dimuon->GetMuon2()->GetMatched()) || 42 == 42 ){
	//**********************************************************************************************
	if(gData->Getkt_njet_a()>0) {

//    if( !(dimuon->GetMuon1()->GetMatched() || dimuon->GetMuon2()->GetMatched())){

          fGeneralsphericity   -> Fill( sphericity,      gHeader->GetWeight());
          fGeneralisotropy     -> Fill( isotropy,        gHeader->GetWeight());
          fGeneralmultiplicity -> Fill( multiplicity,    gHeader->GetWeight());
          fGeneralQ2Prime      -> Fill( Q2Prime,         gHeader->GetWeight());

	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneralsphericity_is_lu   -> Fill( sphericity,      gHeader->GetWeight());
	      fGeneralisotropy_is_lu     -> Fill( isotropy,        gHeader->GetWeight());
	      fGeneralmultiplicity_is_lu -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_is_lu      -> Fill( Q2Prime,         gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneralsphericity_is_ll   -> Fill( sphericity,      gHeader->GetWeight()); 
	      fGeneralisotropy_is_ll     -> Fill( isotropy,        gHeader->GetWeight()); 
	      fGeneralmultiplicity_is_ll -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_is_ll      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	      fGeneralsphericity_is_hu   -> Fill( sphericity,      gHeader->GetWeight()); 
	      fGeneralisotropy_is_hu     -> Fill( isotropy,        gHeader->GetWeight()); 
	      fGeneralmultiplicity_is_hu -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_is_hu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneralsphericity_is_hl   -> Fill( sphericity,      gHeader->GetWeight()); 
	      fGeneralisotropy_is_hl     -> Fill( isotropy,        gHeader->GetWeight()); 
	      fGeneralmultiplicity_is_hl -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_is_hl      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	    } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneralsphericity_nis_lu   -> Fill( sphericity,      gHeader->GetWeight()); 
	      fGeneralisotropy_nis_lu     -> Fill( isotropy,        gHeader->GetWeight()); 
	      fGeneralmultiplicity_nis_lu -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_nis_lu      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  { 
	      fGeneralsphericity_nis_ll   -> Fill( sphericity,      gHeader->GetWeight()); 
	      fGeneralisotropy_nis_ll     -> Fill( isotropy,        gHeader->GetWeight()); 
	      fGeneralmultiplicity_nis_ll -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_nis_ll      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneralsphericity_nis_hu   -> Fill( sphericity,      gHeader->GetWeight());
	      fGeneralisotropy_nis_hu     -> Fill( isotropy,        gHeader->GetWeight());
	      fGeneralmultiplicity_nis_hu -> Fill( multiplicity,    gHeader->GetWeight());
	      fGeneralQ2Prime_nis_hu      -> Fill( Q2Prime,         gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneralsphericity_nis_hl   -> Fill( sphericity,      gHeader->GetWeight()); 
	      fGeneralisotropy_nis_hl     -> Fill( isotropy,        gHeader->GetWeight()); 
	      fGeneralmultiplicity_nis_hl -> Fill( multiplicity,    gHeader->GetWeight()); 
	      fGeneralQ2Prime_nis_hl      -> Fill( Q2Prime,         gHeader->GetWeight()); 
	    }
	  }
	}
      
	fGeneralempz->Fill( empz,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	  if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralempz_is_lu->Fill( empz,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralempz_is_ll->Fill( empz,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralempz_is_hu->Fill( empz,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralempz_is_hl->Fill( empz,gHeader->GetWeight()); } 
	}
	else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralempz_nis_lu->Fill( empz,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralempz_nis_ll->Fill( empz,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralempz_nis_hu->Fill( empz,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralempz_nis_hl->Fill( empz,gHeader->GetWeight()); }
	  }

	fGeneralcal_et->Fill( cal_et,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralcal_et_is_lu->Fill( cal_et,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralcal_et_is_ll->Fill( cal_et,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralcal_et_is_hu->Fill( cal_et,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralcal_et_is_hl->Fill( cal_et,gHeader->GetWeight()); } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralcal_et_nis_lu->Fill( cal_et,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralcal_et_nis_ll->Fill( cal_et,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralcal_et_nis_hu->Fill( cal_et,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralcal_et_nis_hl->Fill( cal_et,gHeader->GetWeight()); }
	}
	
	fGeneraletex2ir->Fill( etex2ir,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
       //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
 	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_is_lu->Fill( etex2ir,gHeader->GetWeight()); }
 	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraletex2ir_is_ll->Fill( etex2ir,gHeader->GetWeight()); }
 	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_is_hu->Fill( etex2ir,gHeader->GetWeight()); }
 	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraletex2ir_is_hl->Fill( etex2ir,gHeader->GetWeight()); } 
 	}
 	else{
 	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_lu->Fill( etex2ir,gHeader->GetWeight()); }
 	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_ll->Fill( etex2ir,gHeader->GetWeight()); }
 	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_hu->Fill( etex2ir,gHeader->GetWeight()); }
 	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_hl->Fill( etex2ir,gHeader->GetWeight()); }
 	}
// // // 	fGeneraletex2ir->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
// // // 	fGeneraletex2ir->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
// // //     if( !dimuon->GetSqSumIsolationCut()) {      
// // //       //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
// // // 	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_is_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_is_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraletex2ir_is_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_is_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_is_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_is_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraletex2ir_is_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_is_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); } 
// // // 	}
// // // 	else{
// // // 	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_nis_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_nis_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_nis_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraletex2ir_nis_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());  fGeneraletex2ir_nis_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); }
// // // 	}

	fGeneralcal_et_m_et2ir->Fill( cal_et_m_et2ir,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_is_lu->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_is_ll->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_is_hu->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_is_hl->Fill( cal_et_m_et2ir,gHeader->GetWeight()); } 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_nis_lu->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_nis_ll->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_nis_hu->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneralcal_et_m_et2ir_nis_hl->Fill( cal_et_m_et2ir,gHeader->GetWeight()); }
	}

	fGeneralcal_et_m_cal_et_10->Fill( cal_et_m_cal_et_10,gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_is_lu->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_is_ll->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_is_hu->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_is_hl->Fill(cal_et_m_cal_et_10,gHeader->GetWeight()); 
	}
	else{
	  if(invMass <= 4 &&  dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_nis_lu->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	  if(invMass <= 4 && !dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_nis_ll->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	  if(invMass > 4  &&  dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_nis_hu->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	  if(invMass > 4  && !dimuon->GetDifCharge()) fGeneralcal_et_m_cal_et_10_nis_hl->Fill(cal_et_m_cal_et_10,gHeader->GetWeight());
	}                                                    

// Histograms for Cross-Sections 

// DB Histos for Dijet Selection

// Both muons matched to jet

	if( (dimuon->GetMuon1()->GetJetID() == gJets->GetHighestJetID() &&
             dimuon->GetMuon2()->GetJetID() == gJets->GetSecondHighestJetID()) || 
            (dimuon->GetMuon2()->GetJetID() == gJets->GetHighestJetID() &&
             dimuon->GetMuon1()->GetJetID() == gJets->GetSecondHighestJetID()) || 
	    (dimuon->GetMuon1()->GetJetID() == gJets->GetHighestJetID() &&
             dimuon->GetMuon2()->GetJetID() == gJets->GetHighestJetID()) || 
	    (dimuon->GetMuon1()->GetJetID() == gJets->GetSecondHighestJetID() &&
             dimuon->GetMuon2()->GetJetID() == gJets->GetSecondHighestJetID()) ) {

	  fGeneraldijetbothetex2ir->Fill( etex2ir,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_is_lu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_is_ll->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_is_hu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_is_hl->Fill( etex2ir,gHeader->GetWeight()); } 
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_nis_lu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_nis_ll->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_nis_hu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldijetbothetex2ir_nis_hl->Fill( etex2ir,gHeader->GetWeight()); }
	  }

	  fGeneraldijetbothdimuxsecpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	  fGeneraldijetbothdimuxsecpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	      fGeneraldijetbothdimuxsecpt_is_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxsecpt_is_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {
	      fGeneraldijetbothdimuxsecpt_is_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxsecpt_is_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	      fGeneraldijetbothdimuxsecpt_is_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxsecpt_is_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  { 
	      fGeneraldijetbothdimuxsecpt_is_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxsecpt_is_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	  }						                              
	  else{	 						                 
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneraldijetbothdimuxsecpt_nis_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxsecpt_nis_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneraldijetbothdimuxsecpt_nis_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxsecpt_nis_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneraldijetbothdimuxsecpt_nis_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxsecpt_nis_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneraldijetbothdimuxsecpt_nis_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxsecpt_nis_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	  }
	
	  fGeneraldijetbothdimuxseceta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	  fGeneraldijetbothdimuxseceta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {    
	      fGeneraldijetbothdimuxseceta_is_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxseceta_is_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {    
	      fGeneraldijetbothdimuxseceta_is_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxseceta_is_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {    
	      fGeneraldijetbothdimuxseceta_is_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxseceta_is_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {    
	      fGeneraldijetbothdimuxseceta_is_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	      fGeneraldijetbothdimuxseceta_is_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	  }		                                                                                
	  else{		                                                                                  
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneraldijetbothdimuxseceta_nis_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxseceta_nis_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {   
	      fGeneraldijetbothdimuxseceta_nis_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxseceta_nis_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {   
              fGeneraldijetbothdimuxseceta_nis_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());;
              fGeneraldijetbothdimuxseceta_nis_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {   
	      fGeneraldijetbothdimuxseceta_nis_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetbothdimuxseceta_nis_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	  }           

	  fGeneraldijetbothdimuxsecdphi->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 3.25 ){
	    if( !dimuon->GetSqSumIsolationCut()) {      	     
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_is_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_is_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_is_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_is_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	    }				       
	    else{					     										 
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_nis_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_nis_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_nis_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneraldijetbothdimuxsecdphi_nis_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	    }                                                
	  }
	}

//One of both muons matched to jet

	if( ((dimuon->GetMuon1()->GetJetID() == gJets->GetHighestJetID()         || 
              dimuon->GetMuon1()->GetJetID() == gJets->GetSecondHighestJetID())  && 
             (dimuon->GetMuon2()->GetJetID() != gJets->GetHighestJetID()         && 
              dimuon->GetMuon2()->GetJetID() != gJets->GetSecondHighestJetID())) ||
	    ((dimuon->GetMuon2()->GetJetID() == gJets->GetHighestJetID()         || 
              dimuon->GetMuon2()->GetJetID() == gJets->GetSecondHighestJetID())  && 
             (dimuon->GetMuon1()->GetJetID() != gJets->GetHighestJetID()         && 
              dimuon->GetMuon1()->GetJetID() != gJets->GetSecondHighestJetID()))){

	  fGeneraldijetoneetex2ir->Fill( etex2ir,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_is_lu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_is_ll->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_is_hu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_is_hl->Fill( etex2ir,gHeader->GetWeight()); }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_nis_lu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_nis_ll->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_nis_hu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldijetoneetex2ir_nis_hl->Fill( etex2ir,gHeader->GetWeight()); }
	  }

	  fGeneraldijetonedimuxsecpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	  fGeneraldijetonedimuxsecpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	      fGeneraldijetonedimuxsecpt_is_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetonedimuxsecpt_is_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {
	      fGeneraldijetonedimuxsecpt_is_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetonedimuxsecpt_is_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	      fGeneraldijetonedimuxsecpt_is_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetonedimuxsecpt_is_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  { 
	      fGeneraldijetonedimuxsecpt_is_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetonedimuxsecpt_is_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	  }						                              
	  else{	 						                 
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneraldijetonedimuxsecpt_nis_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetonedimuxsecpt_nis_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneraldijetonedimuxsecpt_nis_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetonedimuxsecpt_nis_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneraldijetonedimuxsecpt_nis_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetonedimuxsecpt_nis_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneraldijetonedimuxsecpt_nis_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetonedimuxsecpt_nis_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	  }                                                    
	
	  fGeneraldijetonedimuxseceta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	  fGeneraldijetonedimuxseceta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {    
	      fGeneraldijetonedimuxseceta_is_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_is_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {    
	      fGeneraldijetonedimuxseceta_is_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_is_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {    
	      fGeneraldijetonedimuxseceta_is_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_is_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {    
	      fGeneraldijetonedimuxseceta_is_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_is_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	  }		                                                                                
	  else{		                                                                                  
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneraldijetonedimuxseceta_nis_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_nis_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {   
	      fGeneraldijetonedimuxseceta_nis_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_nis_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {   
	      fGeneraldijetonedimuxseceta_nis_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_nis_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {   
	      fGeneraldijetonedimuxseceta_nis_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetonedimuxseceta_nis_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	  }           

	  fGeneraldijetonedimuxsecdphi->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 3.25 ){
	    if( !dimuon->GetSqSumIsolationCut()) {      	     
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_is_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_is_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_is_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_is_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	    }				       
	    else{			     										 
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_nis_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_nis_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_nis_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneraldijetonedimuxsecdphi_nis_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	    }                                                
	  }
	}

//Both muons unmatched

	if( (dimuon->GetMuon1()->GetJetID() != gJets->GetHighestJetID() &&
             dimuon->GetMuon2()->GetJetID() != gJets->GetSecondHighestJetID()) && 
            (dimuon->GetMuon2()->GetJetID() != gJets->GetHighestJetID() &&
             dimuon->GetMuon1()->GetJetID() != gJets->GetSecondHighestJetID())) {

	  fGeneraldijetnoneetex2ir->Fill( etex2ir,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_is_lu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_is_ll->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_is_hu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_is_hl->Fill( etex2ir,gHeader->GetWeight()); }
	  }
	  else{
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_nis_lu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_nis_ll->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_nis_hu->Fill( etex2ir,gHeader->GetWeight()); }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  fGeneraldijetnoneetex2ir_nis_hl->Fill( etex2ir,gHeader->GetWeight()); }
	  }

	  fGeneraldijetnonedimuxsecpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	  fGeneraldijetnonedimuxsecpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	      fGeneraldijetnonedimuxsecpt_is_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetnonedimuxsecpt_is_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {
	      fGeneraldijetnonedimuxsecpt_is_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	      fGeneraldijetnonedimuxsecpt_is_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	      fGeneraldijetnonedimuxsecpt_is_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxsecpt_is_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  { 
	      fGeneraldijetnonedimuxsecpt_is_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxsecpt_is_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	  }						                              
	  else{	 						                 
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	      fGeneraldijetnonedimuxsecpt_nis_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxsecpt_nis_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	      fGeneraldijetnonedimuxsecpt_nis_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxsecpt_nis_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	      fGeneraldijetnonedimuxsecpt_nis_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxsecpt_nis_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {  
	      fGeneraldijetnonedimuxsecpt_nis_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxsecpt_nis_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	    }
	  }                                                    
	 
	  fGeneraldijetnonedimuxseceta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	  fGeneraldijetnonedimuxseceta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {    
	      fGeneraldijetnonedimuxseceta_is_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_is_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {    
	      fGeneraldijetnonedimuxseceta_is_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_is_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {    
	      fGeneraldijetnonedimuxseceta_is_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_is_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {    
	      fGeneraldijetnonedimuxseceta_is_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	      fGeneraldijetnonedimuxseceta_is_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	    }
	  }		                                                                                
	  else{		                                                                                  
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneraldijetnonedimuxseceta_nis_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_nis_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {   
	      fGeneraldijetnonedimuxseceta_nis_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_nis_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {   
	      fGeneraldijetnonedimuxseceta_nis_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_nis_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {   
	      fGeneraldijetnonedimuxseceta_nis_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	      fGeneraldijetnonedimuxseceta_nis_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	    }
	  }           
	  
	  fGeneraldijetnonedimuxsecdphi->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	  if(invMass > 3.25 ){
	    if( !dimuon->GetSqSumIsolationCut()) {      	     
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_is_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_is_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_is_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_is_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	    }			       
	    else{						     						 
	      if(invMass<= 4 &&  dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_nis_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass<= 4 && !dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_nis_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  &&  dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_nis_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	      if(invMass> 4  && !dimuon->GetDifCharge()) {
		fGeneraldijetnonedimuxsecdphi_nis_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
	      }
	    }                                                
	  }
	}

// IB Histos
	
	fGeneraldimuxsecpt->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	fGeneraldimuxsecpt->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      	     
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {
	    fGeneraldimuxsecpt_is_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneraldimuxsecpt_is_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {
	    fGeneraldimuxsecpt_is_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneraldimuxsecpt_is_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	    fGeneraldimuxsecpt_is_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneraldimuxsecpt_is_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  { 
	    fGeneraldimuxsecpt_is_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight()); 
	    fGeneraldimuxsecpt_is_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	}						                              
	else{	 						                 
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  { 
	    fGeneraldimuxsecpt_nis_lu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fGeneraldimuxsecpt_nis_lu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {  
	    fGeneraldimuxsecpt_nis_ll->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fGeneraldimuxsecpt_nis_ll->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {  
	    fGeneraldimuxsecpt_nis_hu->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fGeneraldimuxsecpt_nis_hu->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {  
	    fGeneraldimuxsecpt_nis_hl->Fill(dimuon->GetMuon1()->Pt(),gHeader->GetWeight());
	    fGeneraldimuxsecpt_nis_hl->Fill(dimuon->GetMuon2()->Pt(),gHeader->GetWeight()); 
	  }
	}                                                    
    
	fGeneraldimuxseceta->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	fGeneraldimuxseceta->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	if( !dimuon->GetSqSumIsolationCut()) {      	     
      //	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {    
	    fGeneraldimuxseceta_is_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraldimuxseceta_is_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {    
	    fGeneraldimuxseceta_is_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraldimuxseceta_is_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {    
	    fGeneraldimuxseceta_is_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraldimuxseceta_is_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {    
	    fGeneraldimuxseceta_is_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight()); 
	    fGeneraldimuxseceta_is_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	}		                                                                                
	else{		                                                                                  
	  if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	    fGeneraldimuxseceta_nis_lu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fGeneraldimuxseceta_nis_lu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	  if(invMass <= 4 && !dimuon->GetDifCharge())  {   
	    fGeneraldimuxseceta_nis_ll->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fGeneraldimuxseceta_nis_ll->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  &&  dimuon->GetDifCharge())  {   
	    fGeneraldimuxseceta_nis_hu->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());;
	    fGeneraldimuxseceta_nis_hu->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight()); 
	  }
	  if(invMass > 4  && !dimuon->GetDifCharge())  {   
	    fGeneraldimuxseceta_nis_hl->Fill(dimuon->GetMuon1()->Eta(),gHeader->GetWeight());
	    fGeneraldimuxseceta_nis_hl->Fill(dimuon->GetMuon2()->Eta(),gHeader->GetWeight());
	  }
	}                                                    

    // *******************************************;
    // filling finder by finder xsecs histos begin:
    // *******************************************;
    // Achims code to fill the finder wise histo: 
    // c   fill muqual histogram for both muons
    // c      all
    //                 call hf1(offs+59,7.05,wgtdimu)
    // c      sum of quality
    //                 call hf1(offs+59,6.45+(float(int(muquac(jj)))
    //      +                        +float(int(muquac(j))))/10.,wgtdimu)
    // c      quality of each muon, sum over finders
    //                 call hf1(offs+59,float(int(muquac(jj)))+.05,wgtdimu)
    //                 call hf1(offs+59,float(int(muquac(j)))+.05,wgtdimu)
    // c      quality of each muon, separately for each finder
    //                 call hf1(offs+59,muquac(jj)+.05,wgtdimu)
    //                 call hf1(offs+59,muquac(j)+.05,wgtdimu)
    // c   fill "true" bin for purity/efficiency into overflow
    //                 if(bbmumuflag) call hf1(offs+59,8.05,wgtdimu)
    // c   muon chamber info only
    //                 if(muchfl(jj).gt.0.and.muchfl(j).gt.0) 
    //      +            call hf1(offs+59,7.85,wgtdimu)
    // c   BAC only
    //                 if(MUMUBAC(jj).gt.0.and.MUMUBAC(j).gt.0)
    //      +            call hf1(offs+59,7.95,wgtdimu)
    // c             print *, 'hallo muquac',jj,j,muquac(jj),muquac(j),wgtdimu

	if( 42 == 42 ){ // all finders
	  fGeneraldimuxsecfinders->Fill(7.05,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_is_lu->Fill(7.05,gHeader->GetWeight());}
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_is_ll->Fill(7.05,gHeader->GetWeight());}
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_is_hu->Fill(7.05,gHeader->GetWeight());}
	    if(invMass > 4  && !dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_is_hl->Fill(7.05,gHeader->GetWeight());}
	  }				     					                      
	  else{    										              
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_nis_lu->Fill(7.05,gHeader->GetWeight());}
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_nis_ll->Fill(7.05,gHeader->GetWeight());}
	    if(invMass > 4  &&  dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_nis_hu->Fill(7.05,gHeader->GetWeight());}
	    if(invMass > 4  && !dimuon->GetDifCharge())  {   fGeneraldimuxsecfinders_nis_hl->Fill(7.05,gHeader->GetWeight());}
	  }                                                    
	}
	if( 42 == 42 ){//      sum of quality
      //      6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.
	  fGeneraldimuxsecfinders->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());
	  if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	    if(invMass <= 4 &&  dimuon->GetDifCharge())  {  
	      fGeneraldimuxsecfinders_is_lu->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());
	    }
	    if(invMass <= 4 && !dimuon->GetDifCharge())  {
	      fGeneraldimuxsecfinders_is_ll->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());
	    }
	    if(invMass > 4  &&  dimuon->GetDifCharge())  { 
	      fGeneraldimuxsecfinders_is_hu->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());
	    }
	    if(invMass > 4  && !dimuon->GetDifCharge())  {
	      fGeneraldimuxsecfinders_is_hl->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());
	    }
	  }		     										                      
	  else{		;		     										              
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_lu->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_ll->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hu->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hl->Fill(6.45+((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+(Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality())))/10.,gHeader->GetWeight());}
      }                                                    
    }
    if( 42 == 42 ){ // quality of each muon, sum over finders
    //                 call hf1(offs+59,float(int(muquac(jj)))+.05,wgtdimu)
    //                 call hf1(offs+59,float(int(muquac(j)))+.05,wgtdimu)

      fGeneraldimuxsecfinders->Fill((Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight());
      fGeneraldimuxsecfinders->Fill((Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_lu->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_lu->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight()); }
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_ll->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_ll->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight()); }
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hu->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_hu->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight()); }
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hl->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_hl->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight()); }
      }						     										                      	          								                      	      
      else{						     										              	       										              	      
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_lu->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_lu->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_ll->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_ll->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hu->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_hu->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hl->Fill( (Double_t)((Int_t)(dimuon->GetMuon1()->GetQuality()))+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_hl->Fill( (Double_t)((Int_t)(dimuon->GetMuon2()->GetQuality()))+0.05,gHeader->GetWeight());}
      }                                                    
    }
    if( 42 == 42 ){    // c      quality of each muon, separately for each finder
      //                 call hf1(offs+59,muquac(jj)+.05,wgtdimu)
      //                 call hf1(offs+59,muquac(j)+.05,wgtdimu)

      if(dimuon->GetMuon1()->GetSpecialQuality() > 4 && dimuon->GetMuon1()->GetSpecialQuality() < 4.2) {
	cout <<"Special Quality 4.1??? "<< dimuon->GetMuon1()->GetSpecialQuality() <<" Event: "<< gData->Geteventnr() << endl;
      }
      if(dimuon->GetMuon2()->GetSpecialQuality() > 4 && dimuon->GetMuon2()->GetSpecialQuality() < 4.2) {
	cout <<"Special Quality 4.1??? "<< dimuon->GetMuon2()->GetSpecialQuality() <<" Event: "<< gData->Geteventnr() << endl;
      }

      fGeneraldimuxsecfinders->Fill(dimuon->GetMuon1()->GetSpecialQuality()+0.05,gHeader->GetWeight());
      fGeneraldimuxsecfinders->Fill(dimuon->GetMuon2()->GetSpecialQuality()+0.05,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_lu->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_lu->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight()); }
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_ll->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_ll->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight()); }
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hu->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_hu->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight()); }
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hl->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight());  fGeneraldimuxsecfinders_is_hl->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight()); }
      }						     										                      	          								                      	      
      else{						     										              	       										              	      
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_lu->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_lu->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_ll->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_ll->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hu->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_hu->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hl->Fill( (dimuon->GetMuon1()->GetSpecialQuality())+0.05,gHeader->GetWeight()); fGeneraldimuxsecfinders_nis_hl->Fill( (dimuon->GetMuon2()->GetSpecialQuality())+0.05,gHeader->GetWeight());}
      }
    }
    /*
    if(dimuon->GetMuon1()->GetBacMatID()>0. && dimuon->GetMuon2()->GetBacMatID()>0.){// BACMAT info only
    //                 if(mubacmat(jj).gt.0.and.mubacmat(j).gt.0) 
    //      +            call hf1(offs+59,7.75,wgtdimu)
      fGeneraldimuxsecfinders->Fill(7.75,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_lu->Fill(7.75,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_ll->Fill(7.75,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hu->Fill(7.75,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hl->Fill(7.75,gHeader->GetWeight());}
      }	   			     										                      
      else{	    		     										              
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_lu->Fill(7.75,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_ll->Fill(7.75,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hu->Fill(7.75,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hl->Fill(7.75,gHeader->GetWeight());}
      }
    }  
    */

    if(dimuon->GetMuon1()->GetChamberFlag()>0. && dimuon->GetMuon2()->GetChamberFlag()>0.){// muon chamber info only
    //                 if(muchfl(jj).gt.0.and.muchfl(j).gt.0) 
    //      +            call hf1(offs+59,7.85,wgtdimu)
      fGeneraldimuxsecfinders->Fill(7.85,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_lu->Fill(7.85,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_ll->Fill(7.85,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hu->Fill(7.85,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hl->Fill(7.85,gHeader->GetWeight());}
      }	   			     										                      
      else{	    		     										              
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_lu->Fill(7.85,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_ll->Fill(7.85,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hu->Fill(7.85,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hl->Fill(7.85,gHeader->GetWeight());}
      }
    }
    if(dimuon->GetMuon1()->GetMuBacID()>0. && dimuon->GetMuon2()->GetMuBacID()>0.){    // c   BAC only
    //                 if(MUMUBAC(jj).gt.0.and.MUMUBAC(j).gt.0)
    //      +            call hf1(offs+59,7.95,wgtdimu)
      fGeneraldimuxsecfinders->Fill(7.95,gHeader->GetWeight());
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_lu->Fill(7.95,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_ll->Fill(7.95,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hu->Fill(7.95,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_is_hl->Fill(7.95,gHeader->GetWeight());}
      }						     			                      
      else{			    							              
	if(invMass <= 4 &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_lu->Fill(7.95,gHeader->GetWeight());}
	if(invMass <= 4 && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_ll->Fill(7.95,gHeader->GetWeight());}
	if(invMass > 4  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hu->Fill(7.95,gHeader->GetWeight());}
	if(invMass > 4  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecfinders_nis_hl->Fill(7.95,gHeader->GetWeight());}
      }
    }
    // *******************************************;
    // filling finder by finder xsecs histos end.
    // *******************************************;

    fGeneraldimuxsecdr->Fill(deltaR,gHeader->GetWeight());
    if(invMass > 3.25 ){
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_is_lu->Fill(deltaR,gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_is_ll->Fill(deltaR,gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_is_hu->Fill(deltaR,gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_is_hl->Fill(deltaR,gHeader->GetWeight()); }
      }					     										             
      else{					     										     
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_nis_lu->Fill(deltaR,gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_nis_ll->Fill(deltaR,gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_nis_hu->Fill(deltaR,gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecdr_nis_hl->Fill(deltaR,gHeader->GetWeight()); }
      }                                                    
    }

    fGeneraldimuxsecdphi->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());
    if(invMass > 3.25 ){
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4. &&  dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_is_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_is_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_is_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_is_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight()); }
      }				       
      else{						     										 
	if(invMass <= 4. &&  dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_nis_lu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_nis_ll->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_nis_hu->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge()) { fGeneraldimuxsecdphi_nis_hl->Fill(TMath::Abs(deltaPhi),gHeader->GetWeight());}
      }                                                    
    }

    fGeneraldimuxsecptb->Fill(dimuon->GetMuon1()->Pt()+dimuon->GetMuon1()->GetIsolation10(),gHeader->GetWeight());
    fGeneraldimuxsecptb->Fill(dimuon->GetMuon2()->Pt()+dimuon->GetMuon2()->GetIsolation10(),gHeader->GetWeight());
    if(invMass > 3.25 ){
      fGeneraldimuxsecptb_diffb->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight());
      fGeneraldimuxsecptb_diffb->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());
    }    
    else fGeneraldimuxsecptb_sameb->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight());
    if(TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10)) < 0.1 ){
      fGeneraldimuxsecptb_samecone->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight());
    }
    else  fGeneraldimuxsecptb_asym->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/(dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight()); // cone pt asymetry for events from different b (cone1 != cone2)
    if(invMass > 3.25 ){
      // muons from different b quarks: 2 entries per event:
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_lu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_is_lu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_ll->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_is_ll->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_hu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_is_hu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_hl->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_is_hl->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}

	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_is_lu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_is_lu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_is_ll->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_is_ll->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_is_hu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_is_hu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_is_hl->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_is_hl->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
      }						     										             
      else{						     										     
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_lu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_nis_lu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_ll->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_nis_ll->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_hu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_nis_hu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_hl->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_nis_hl->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}

	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_nis_lu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_nis_lu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_nis_ll->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_nis_ll->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_nis_hu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_nis_hu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_diffb_nis_hl->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_diffb_nis_hl->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
      }                                                    
    }
    else{
      // muons from the same b quark: 1 entry per event (same and different b xsecs might have to be separated):
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {   
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_lu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_ll->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_hu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_is_hl->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }

	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_is_lu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_is_ll->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_is_hu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_is_hl->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
      }						     										             
      else{						     										     
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_lu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_ll->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_hu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_nis_hl->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }

	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_nis_lu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_nis_ll->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_nis_hu->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_sameb_nis_hl->Fill(dimuon->GetdimuPt()+Isolation_highpt_mu,gHeader->GetWeight()); }
      }                                                    
    }
    if( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10)) < 0.1  ){
      // events with the same cone pt
      if( !dimuon->GetSqSumIsolationCut()) {
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {   
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_is_lu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_is_lu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_is_ll->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_is_ll->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_is_hu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_is_hu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_is_hl->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_is_hl->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
      }						     										             
      else {
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_nis_lu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_nis_lu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_nis_ll->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_nis_ll->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_nis_hu->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_nis_hu->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_samecone_nis_hl->Fill(dimuon->GetMuon1()->Pt()+Isolation_1_10,gHeader->GetWeight()); fGeneraldimuxsecptb_samecone_nis_hl->Fill(dimuon->GetMuon2()->Pt()+Isolation_2_10,gHeader->GetWeight());}
      }  
    }
    else{
      // events with different cone pts
      if( !dimuon->GetSqSumIsolationCut()) {      	     
	//	if( IsolationSqSum10 <= gCards->GetDIMUONSqSumIsolationCut()) {
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_is_lu->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight()); }
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_is_ll->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight()); }
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_is_hu->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight()); }
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_is_hl->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight()); }
      }						     										             
      else{						     										     
	if(invMass <= 4. &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_nis_lu->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight());}
	if(invMass <= 4. && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_nis_ll->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight());}
	if(invMass > 4.  &&  dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_nis_hu->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight());}
	if(invMass > 4.  && !dimuon->GetDifCharge())  {    fGeneraldimuxsecptb_asym_nis_hl->Fill( TMath::Abs((dimuon->GetMuon1()->Pt()+Isolation_1_10)-(dimuon->GetMuon2()->Pt()+Isolation_2_10))/ (dimuon->GetMuon1()->Pt()+Isolation_1_10+dimuon->GetMuon2()->Pt()+Isolation_2_10),gHeader->GetWeight());}
      }                                                    
    }
          
    if( gCards->GetDoEfficiency()) {

	  // 	  if( (gData->Getrunnr() == 47140) && (gData->Geteventnr() == 34602) ||
	  // 	       (gData->Getrunnr() == 47140) && (gData->Geteventnr() == 61812) ||
	  // 	       (gData->Getrunnr() == 47152) && (gData->Geteventnr() == 65705)) {
	  // 	    GMuon *muon1 = dimuon->GetMuon1();
	  // 	    GMuon *muon2 = dimuon->GetMuon2();
	  // 	    cout << "muon1 glomu: " << muon1->GetGlomu() << " muon2 glomu: " << muon2->GetGlomu() << " run: " << gData->Getrunnr() << " event: " << gData->Geteventnr() << endl;
	  // 	    cout << "SPP: " << gData->Gettltw(2) << endl;
	  // 	    cout << "DIS: " << gData->Gettltw(3) << " " << gData->Gettltw(10) << endl;
	  // 	    cout << "HPP: " << gData->Gettltw(4) << " " << gData->Gettltw(11) << endl;
	  // 	    cout << "EXO: " << gData->Gettltw(5) << " " << gData->Gettltw(12) << endl;
	  // 	    cout << "MUO: " << gData->Gettltw(6) << endl;
	  // 	    cout << "VTX: " << gData->Gettltw(7) << endl;
	  // 	    cout << "HFM: " << gData->Gettltw(8) << " " << gData->Gettltw(14) << endl;
	  // 	    cout << "HFL: " << gData->Gettltw(9) << " " << gData->Gettltw(13) << endl;
	  // 	  }

	  // attention
	  if( dimuon->GetTriggerType() == kTakeNone )
	    fGeneralTriggerType->Fill("None",1);
	  else if( dimuon->GetTriggerType() == kTakeMuon1 )
	    fGeneralTriggerType->Fill("Muon1",1);
	  else if( dimuon->GetTriggerType() == kTakeMuon2 )
	    fGeneralTriggerType->Fill("Muon2",1);
	  else if( dimuon->GetTriggerType() == kTakeBoth )
	    fGeneralTriggerType->Fill("Both",1);
	  
	  // fill muons of dimuon to comparison histograms
	  FillPlotMuonPt(dimuon,fGeneralMV_MuonPt,"MV");
	  FillPlotMuonPt(dimuon,fGeneralMV_BREMAT_MuonPt,"BREMAT");
	  FillPlotMuonPt(dimuon,fGeneralMV_MUBAC_MuonPt,"MUBAC");
	  FillPlotMuonP(dimuon,fGeneralMV_MuonP,"MV");
	  FillPlotMuonP(dimuon,fGeneralMV_MPMATCH_MuonP,"MPMATCH");
	  FillPlotMuonP(dimuon,fGeneralMV_MUBAC_MuonP,"MUBAC");
	  FillPlotMuonPz(dimuon,fGeneralMV_MuonPz,"MV");
	  FillPlotMuonPz(dimuon,fGeneralMV_BREMAT_MuonPz,"BREMAT");
	  FillPlotMuonPz(dimuon,fGeneralMV_MUBAC_MuonPz,"MUBAC");
	  FillPlotMuonEta(dimuon,fGeneralMV_MuonEta,"MV");
	  FillPlotMuonEta(dimuon,fGeneralMV_BREMAT_MuonEta,"BREMAT");
	  FillPlotMuonEta(dimuon,fGeneralMV_MPMATCH_MuonEta,"MPMATCH");
	  FillPlotMuonEta(dimuon,fGeneralMV_MUBAC_MuonEta,"MUBAC");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MuonPhi,"MV");
	  FillPlotMuonPhi(dimuon,fGeneralMV_BREMAT_MuonPhi,"BREMAT");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MPMATCH_MuonPhi,"MPMATCH");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MUBAC_MuonPhi,"MUBAC");
	  
	  for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MV; ++i ) {
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_MuonEtaPtBins[i],"MV",fGeneralMuonPt_Bins_MV[i],fGeneralMuonPt_Bins_MV[i+1],i+1,fGeneralMuonPt_NBins_MV);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_MuonPhiPtBins[i],"MV",fGeneralMuonPt_Bins_MV[i],fGeneralMuonPt_Bins_MV[i+1],i+1,fGeneralMuonPt_NBins_MV);
	  }
	  	
	  for ( Int_t i = 0; i < fGeneralMuonPt_NBins_BREMAT; ++i ) {
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_BREMAT_MuonEtaPtBins[i],"BREMAT",fGeneralMuonPt_Bins_BREMAT[i],fGeneralMuonPt_Bins_BREMAT[i+1],i+1,fGeneralMuonPt_NBins_BREMAT);
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_MPMATCH_MuonEtaPtBins[i],"MPMATCH",fGeneralMuonPt_Bins_BREMAT[i],fGeneralMuonPt_Bins_BREMAT[i+1],i+1,fGeneralMuonPt_NBins_BREMAT);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_BREMAT_MuonPhiPtBins[i],"BREMAT",fGeneralMuonPt_Bins_BREMAT[i],fGeneralMuonPt_Bins_BREMAT[i+1],i+1,fGeneralMuonPt_NBins_BREMAT);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_MPMATCH_MuonPhiPtBins[i],"MPMATCH",fGeneralMuonPt_Bins_BREMAT[i],fGeneralMuonPt_Bins_BREMAT[i+1],i+1,fGeneralMuonPt_NBins_BREMAT);
	  }
	  
	  for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MUBAC; ++i ) {
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_MUBAC_MuonEtaPtBins[i],"MUBAC",fGeneralMuonPt_Bins_MUBAC[i],fGeneralMuonPt_Bins_MUBAC[i+1],i+1,fGeneralMuonPt_NBins_MUBAC);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_MUBAC_MuonPhiPtBins[i],"MUBAC",fGeneralMuonPt_Bins_MUBAC[i],fGeneralMuonPt_Bins_MUBAC[i+1],i+1,fGeneralMuonPt_NBins_MUBAC);
	  }
	  
	  FillPlotMuonP(dimuon,fGeneralMV_MuonP_Forward,"MV,FORWARD");
	  FillPlotMuonP(dimuon,fGeneralMV_MPMATCH_MuonP_Forward,"MPMATCH,FORWARD");
	  FillPlotMuonP(dimuon,fGeneralMV_MUBAC_MuonP_Forward,"MUBAC,FORWARD");
	  FillPlotMuonPt(dimuon,fGeneralMV_MuonPt_Forward,"MV,FORWARD");
	  FillPlotMuonPt(dimuon,fGeneralMV_MPMATCH_MuonPt_Forward,"MPMATCH,FORWARD");
	  FillPlotMuonPt(dimuon,fGeneralMV_MUBAC_MuonPt_Forward,"MUBAC,FORWARD");
	  FillPlotMuonEta(dimuon,fGeneralMV_MuonEta_Forward,"MV,FORWARD");
	  FillPlotMuonEta(dimuon,fGeneralMV_MPMATCH_MuonEta_Forward,"MPMATCH,FORWARD");
	  FillPlotMuonEta(dimuon,fGeneralMV_MUBAC_MuonEta_Forward,"MUBAC,FORWARD");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MuonPhi_Forward,"MV,FORWARD");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MPMATCH_MuonPhi_Forward,"MPMATCH,FORWARD");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MUBAC_MuonPhi_Forward,"MUBAC,FORWARD");
	  
	  for ( Int_t i = 0; i < fGeneralMuonP_NBins_MV; ++i ) {
	    FillPlotMuonEtaPBins(dimuon,fGeneralMV_MuonEtaPBins_Forward[i],"MV,FORWARD",fGeneralMuonP_Bins_MV[i],fGeneralMuonP_Bins_MV[i+1],i+1,fGeneralMuonP_NBins_MV);
	    FillPlotMuonPhiPBins(dimuon,fGeneralMV_MuonPhiPBins_Forward[i],"MV,FORWARD",fGeneralMuonP_Bins_MV[i],fGeneralMuonP_Bins_MV[i+1],i+1,fGeneralMuonP_NBins_MV);
	  }
	  	
	  for ( Int_t i = 0; i < fGeneralMuonP_NBins_MPMATCH; ++i ) {
	    FillPlotMuonEtaPBins(dimuon,fGeneralMV_MPMATCH_MuonEtaPBins_Forward[i],"MPMATCH,FORWARD",fGeneralMuonP_Bins_MPMATCH[i],fGeneralMuonP_Bins_MPMATCH[i+1],i+1,fGeneralMuonP_NBins_MPMATCH);
	    FillPlotMuonPhiPBins(dimuon,fGeneralMV_MPMATCH_MuonPhiPBins_Forward[i],"MPMATCH,FORWARD",fGeneralMuonP_Bins_MPMATCH[i],fGeneralMuonP_Bins_MPMATCH[i+1],i+1,fGeneralMuonP_NBins_MPMATCH);
	  }
	  
	  for ( Int_t i = 0; i < fGeneralMuonP_NBins_MUBAC; ++i ) {
	    FillPlotMuonEtaPBins(dimuon,fGeneralMV_MUBAC_MuonEtaPBins_Forward[i],"MUBAC,FORWARD",fGeneralMuonP_Bins_MUBAC[i],fGeneralMuonP_Bins_MUBAC[i+1],i+1,fGeneralMuonP_NBins_MUBAC);
	    FillPlotMuonPhiPBins(dimuon,fGeneralMV_MUBAC_MuonPhiPBins_Forward[i],"MUBAC,FORWARD",fGeneralMuonP_Bins_MUBAC[i],fGeneralMuonP_Bins_MUBAC[i+1],i+1,fGeneralMuonP_NBins_MUBAC);
	  }
    	  
	  FillPlotMuonPt(dimuon,fGeneralMV_MuonPt_Barrel,"MV,BARREL");
	  FillPlotMuonPt(dimuon,fGeneralMV_BREMAT_MuonPt_Barrel,"BREMAT,BARREL");
	  FillPlotMuonPt(dimuon,fGeneralMV_MUBAC_MuonPt_Barrel,"MUBAC,BARREL");
	  FillPlotMuonEta(dimuon,fGeneralMV_MuonEta_Barrel,"MV,BARREL");
	  FillPlotMuonEta(dimuon,fGeneralMV_BREMAT_MuonEta_Barrel,"BREMAT,BARREL");
	  FillPlotMuonEta(dimuon,fGeneralMV_MUBAC_MuonEta_Barrel,"MUBAC,BARREL");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MuonPhi_Barrel,"MV,BARREL");
	  FillPlotMuonPhi(dimuon,fGeneralMV_BREMAT_MuonPhi_Barrel,"BREMAT,BARREL");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MUBAC_MuonPhi_Barrel,"MUBAC,BARREL");
	  
	  for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MV; ++i ) {
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_MuonEtaPtBins_Barrel[i],"MV,BARREL",fGeneralMuonPt_Bins_MV[i],fGeneralMuonPt_Bins_MV[i+1],i+1,fGeneralMuonPt_NBins_MV);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_MuonPhiPtBins_Barrel[i],"MV,BARREL",fGeneralMuonPt_Bins_MV[i],fGeneralMuonPt_Bins_MV[i+1],i+1,fGeneralMuonPt_NBins_MV);
	  }
	  	
	  for ( Int_t i = 0; i < fGeneralMuonPt_NBins_BREMAT; ++i ) {
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_BREMAT_MuonEtaPtBins_Barrel[i],"BREMAT,BARREL",fGeneralMuonPt_Bins_BREMAT[i],fGeneralMuonPt_Bins_BREMAT[i+1],i+1,fGeneralMuonPt_NBins_BREMAT);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_BREMAT_MuonPhiPtBins_Barrel[i],"BREMAT,BARREL",fGeneralMuonPt_Bins_BREMAT[i],fGeneralMuonPt_Bins_BREMAT[i+1],i+1,fGeneralMuonPt_NBins_BREMAT);
	  }
	  
	  for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MUBAC; ++i ) {
	    FillPlotMuonEtaPtBins(dimuon,fGeneralMV_MUBAC_MuonEtaPtBins_Barrel[i],"MUBAC,BARREL",fGeneralMuonPt_Bins_MUBAC[i],fGeneralMuonPt_Bins_MUBAC[i+1],i+1,fGeneralMuonPt_NBins_MUBAC);
	    FillPlotMuonPhiPtBins(dimuon,fGeneralMV_MUBAC_MuonPhiPtBins_Barrel[i],"MUBAC,BARREL",fGeneralMuonPt_Bins_MUBAC[i],fGeneralMuonPt_Bins_MUBAC[i+1],i+1,fGeneralMuonPt_NBins_MUBAC);
	  }
	  
	  FillPlotMuonPz(dimuon,fGeneralMV_MuonPz_Rear,"MV,REAR");
	  FillPlotMuonPz(dimuon,fGeneralMV_BREMAT_MuonPz_Rear,"BREMAT,REAR");
	  FillPlotMuonPz(dimuon,fGeneralMV_MUBAC_MuonPz_Rear,"MUBAC,REAR");
	  FillPlotMuonPt(dimuon,fGeneralMV_MuonPt_Rear,"MV,REAR");
	  FillPlotMuonPt(dimuon,fGeneralMV_BREMAT_MuonPt_Rear,"BREMAT,REAR");
	  FillPlotMuonPt(dimuon,fGeneralMV_MUBAC_MuonPt_Rear,"MUBAC,REAR");
	  FillPlotMuonEta(dimuon,fGeneralMV_MuonEta_Rear,"MV,REAR");
	  FillPlotMuonEta(dimuon,fGeneralMV_BREMAT_MuonEta_Rear,"BREMAT,REAR");
	  FillPlotMuonEta(dimuon,fGeneralMV_MUBAC_MuonEta_Rear,"MUBAC,REAR");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MuonPhi_Rear,"MV,REAR");
	  FillPlotMuonPhi(dimuon,fGeneralMV_BREMAT_MuonPhi_Rear,"BREMAT,REAR");
	  FillPlotMuonPhi(dimuon,fGeneralMV_MUBAC_MuonPhi_Rear,"MUBAC,REAR");
	  
	  for ( Int_t i = 0; i < fGeneralMuonPz_NBins_MV; ++i ) {
	    FillPlotMuonEtaPzBins(dimuon,fGeneralMV_MuonEtaPzBins_Rear[i],"MV,REAR",fGeneralMuonPz_Bins_MV[i],fGeneralMuonPz_Bins_MV[i+1],i+1,fGeneralMuonPz_NBins_MV);
	    FillPlotMuonPhiPzBins(dimuon,fGeneralMV_MuonPhiPzBins_Rear[i],"MV,REAR",fGeneralMuonPz_Bins_MV[i],fGeneralMuonPz_Bins_MV[i+1],i+1,fGeneralMuonPz_NBins_MV);
	  }
	  	
	  for ( Int_t i = 0; i < fGeneralMuonPz_NBins_BREMAT; ++i ) {
	    FillPlotMuonEtaPzBins(dimuon,fGeneralMV_BREMAT_MuonEtaPzBins_Rear[i],"BREMAT,REAR",fGeneralMuonPz_Bins_BREMAT[i],fGeneralMuonPz_Bins_BREMAT[i+1],i+1,fGeneralMuonPz_NBins_BREMAT);
	    FillPlotMuonPhiPzBins(dimuon,fGeneralMV_BREMAT_MuonPhiPzBins_Rear[i],"BREMAT,REAR",fGeneralMuonPz_Bins_BREMAT[i],fGeneralMuonPz_Bins_BREMAT[i+1],i+1,fGeneralMuonPz_NBins_BREMAT);
	  }
	  
	  
	  for ( Int_t i = 0; i < fGeneralMuonPz_NBins_MUBAC; ++i ) {
	    FillPlotMuonEtaPzBins(dimuon,fGeneralMV_MUBAC_MuonEtaPzBins_Rear[i],"MUBAC,REAR",fGeneralMuonPz_Bins_MUBAC[i],fGeneralMuonPz_Bins_MUBAC[i+1],i+1,fGeneralMuonPz_NBins_MUBAC);
	    FillPlotMuonPhiPzBins(dimuon,fGeneralMV_MUBAC_MuonPhiPzBins_Rear[i],"MUBAC,REAR",fGeneralMuonPz_Bins_MUBAC[i],fGeneralMuonPz_Bins_MUBAC[i+1],i+1,fGeneralMuonPz_NBins_MUBAC);
	  }
	}  
      }
    }
    
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::CreateGeneral() {
  //
  // create general plots
  if( gDebug ) cout << endl << "GDIMuons::CreateGeneral() called" << endl << endl;
  
  if( gCards->GetDIMUONGeneral()) {

    Int_t    nperevbins = 10;
    Double_t nperevlow  = 0.;
    Double_t nperevhigh = 10.;
    Int_t    massbins   = 1050;
    Double_t masslow    = 0.;
    Double_t masshigh   = 35.;

//Int_t    masslowbins = 80;
//Double_t masslowlow  = 2.;
//Double_t masslowhigh = 4.;
//Int_t    masslowbins = 150;

    Int_t    masslowbins    = 50; // same binning as Achim - careful not to reweight this guy! 050524
    Double_t masslowlow     = 1.5;
    Double_t masslowhigh    = 4.;

//Int_t    masshighbins = 840;
//Double_t masshighlow  = 4.;
//Double_t masshighhigh = 46.;
//Int_t    masshighbins = 252;

    Int_t    masshighbins   = 84; // same binning as Achim - careful not to reweight this guy! 050524
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
    Int_t    dimuphibins    = 314;
    Double_t dimuphilow     = -TMath::Pi();
    Double_t dimuphihigh    = TMath::Pi();
    Int_t    dimuetabins    = 160;
    Double_t dimuetalow     = -4.;
    Double_t dimuetahigh    = 4.;
    Int_t    ptasymetrybins = 80;
    Double_t ptasymetrylow  = -.2;
    Double_t ptasymetryhigh = 1.4;
    Int_t    ptbins         = 100;
    Double_t ptlow          = .0;
    Double_t pthigh         = 25.0;

    Int_t    dimuptbins = 100;
    Double_t dimuptlow  = .0;
    Double_t dimupthigh = 25.0;

    Int_t    etabins    = 160;
    Double_t etalow     = -4.0;
    Double_t etahigh    = 4.0;

    Int_t    phibins    = 360;
    Double_t philow     = -TMath::Pi();
    Double_t phihigh    = TMath::Pi();
    Int_t    muqualbins = 11;
    Double_t muquallow  = -4.0;
    Double_t muqualhigh = 7.0;

    Int_t    sqisol_10bins = 400;
    Double_t sqisol_10low  = 0.;
    Double_t sqisol_10high = 40.0;

    Int_t    chargebins =  4;
    Double_t chargelow  = -2.;
    Double_t chargehigh =  2.;

    Int_t    vtxovntrkbins = 150;
    Double_t vtxovntrklow  = 0.;
    Double_t vtxovntrkhigh = 1.5;

    Int_t    thrustbins       = 50;
    Double_t thrustlow        = 0.;
    Double_t thrusthigh       = 1.0;
    Int_t    sphericitybins   = 50;
    Double_t sphericitylow    = 0.;
    Double_t sphericityhigh   = 1.0;
    Int_t    multiplicitybins = 50;
    Double_t multiplicitylow  = 0.;
    Double_t multiplicityhigh = 100.0;
    Int_t    isotropybins     = 50;
    Double_t isotropylow      = 0.;
    Double_t isotropyhigh     = 1.0;
    Int_t    q2primebins      = 100;
    Double_t q2primelow       = 0.;
    Double_t q2primehigh      = 1050.0;
    //    Double_t q2primehigh      = 2000.0;

    Int_t    impactbins       = 100;
    Double_t impactlow        = -0.5;
    Double_t impacthigh       =  0.5; 
    Int_t    impactsignbins   = 30;
    Double_t impactsignlow    = -15.;
    Double_t impactsignhigh   = 15.;

    Int_t    dl2bins          = 100;
    Double_t dl2low           = -1.0;
    Double_t dl2high          = 1.0; 
    Int_t    dl2errbins       = 100;
    Double_t dl2errlow        = 0.;
    Double_t dl2errhigh       = 1.; 
    Int_t    dl2signbins      = 30;
    Double_t dl2signlow       = -15.;
    Double_t dl2signhigh      = 15.;
    Int_t    dl2mirrbins      = 15;
    Double_t dl2mirrlow       = 0.;
    Double_t dl2mirrhigh      = 15.;

    Int_t    mujetetbins      = 15;
    Double_t mujetetlow       = 0.;
    Double_t mujetethigh      = 15.;
    Int_t    mujetptbins      = 15;
    Double_t mujetptlow       = 0.;
    Double_t mujetpthigh      = 15.;
    Int_t    mujetetabins     = 160;
    Double_t mujetetalow      = -4.;
    Double_t mujetetahigh     =  4.;
    Int_t    mujetdeltarbins  = 60;
    Double_t mujetdeltarlow   = 0.;
    Double_t mujetdeltarhigh  = 1.5;
    Int_t    massjetbins      = 100;
    Double_t massjetlow       = 0.;
    Double_t massjethigh      = 20.;
    Int_t    njetbins         = 10;
    Double_t njetlow          = 0.;
    Double_t njethigh         = 10.;

    Int_t    munphibins       = 10;
    Double_t munphilow        = 0.;
    Double_t munphihigh       = 10.;
    Int_t    mumvidbins       = 10;
    Double_t mumvidlow        = 0.;
    Double_t mumvidhigh       = 10.;
    Int_t    mumufoidbins     = 10;
    Double_t mumufoidlow      = 0.;
    Double_t mumufoidhigh     = 10.;
    Int_t    mundofbins       = 15;
    Double_t mundoflow        = 0.;
    Double_t mundofhigh       = 15.;
    Int_t    muzbins          = 100;
    Double_t muzlow           = 0.;
    Double_t muzhigh          = 1000.;
    Int_t    mupmatbins       = 100;
    Double_t mupmatlow        = 0.;
    Double_t mupmathigh       = 1.;
    Int_t    mpmatchidbins    = 10;
    Double_t mpmatchidlow     = 0.;
    Double_t mpmatchidhigh    = 10.;

    Int_t    mubacmatidbins    = 10; 
    Double_t mubacmatidlow     = 0.;
    Double_t mubacmatidhigh    = 10.;
    Int_t    nbacmatbins       = 50;
    Double_t nbacmatlow        = 0.;
    Double_t nbacmathigh       = 50.;
    Int_t    bacmatidvcbins    = 90;
    Double_t bacmatidvclow     = 0.;
    Double_t bacmatidvchigh    = 90.;
    Int_t    bacmatidmubacbins = 15;
    Double_t bacmatidmubaclow  = 0.;
    Double_t bacmatidmubachigh = 15.;
    Int_t    bacmatistopbins   = 105;
    Double_t bacmatistoplow    = 0.;
    Double_t bacmatistophigh   = 105.;
    Int_t    bacmaterrorbins   = 7;
    Double_t bacmaterrorlow    = 0.;
    Double_t bacmaterrorhigh   = 7.;
    Int_t    bacmatreadoutbins = 6;
    Double_t bacmatreadoutlow  = 0.;
    Double_t bacmatreadouthigh = 6.;

    Int_t    vtxmassbins      = 100;
    Double_t vtxmasslow       = 0.;
    Double_t vtxmasshigh      = 10.;
    Int_t    chi2bins         = 20;
    Double_t chi2low          = 0.;
    Double_t chi2high         = 10.;
    Int_t    ndofbins         = 20;
    Double_t ndoflow          = 0.;
    Double_t ndofhigh         = 10.;
    Int_t    chi2ndofbins     = 20;
    Double_t chi2ndoflow      = 0.;
    Double_t chi2ndofhigh     = 10.;
    Int_t    nrsecbins        = 10; 
    Double_t nrseclow         = 0.;
    Double_t nrsechigh        = 10.;
    Int_t    multibins        = 12;
    Double_t multilow         = 0.;
    Double_t multihigh        = 12.;

    Int_t    empzbins    = 70;
    Double_t empzlow     = 0.;
    Double_t empzhigh    = 70.0;
    Int_t    cal_etbins  = 200;
    Double_t cal_etlow   = 0.;
    Double_t cal_ethigh  = 100.;
    Int_t    etex2irbins = 1;
    Double_t etex2irlow  = 0.;
    Double_t etex2irhigh = 100.;

//     Int_t    etex2irbins = 4;
//     Double_t etex2irlow  = 1.5;
//     Double_t etex2irhigh = 9.5;

    Int_t    dimucrosspt_nbins = 6;
    Double_t *dimucrosspt_bins = new Double_t[dimucrosspt_nbins+1];
    dimucrosspt_bins[0] =  1.5;
    dimucrosspt_bins[1] =  2.0;
    dimucrosspt_bins[2] =  2.5;
    dimucrosspt_bins[3] =  3.0;
    dimucrosspt_bins[4] =  3.5;
    dimucrosspt_bins[5] =  5.0;
    dimucrosspt_bins[6] = 10.0;

    Int_t    dimucrosseta_nbins = 6;
    Double_t *dimucrosseta_bins = new Double_t[dimucrosseta_nbins+1];
    dimucrosseta_bins[0] =  -2.2;
    dimucrosseta_bins[1] =  -1.2;
    dimucrosseta_bins[2] =  -0.6;
    dimucrosseta_bins[3] =   0.0;
    dimucrosseta_bins[4] =   0.6;
    dimucrosseta_bins[5] =   1.2;
    dimucrosseta_bins[6] =   2.5;

    Int_t    dimucrossfinders_nbins = 40;
    Double_t *dimucrossfinders_bins = new Double_t[dimucrossfinders_nbins+1];
    dimucrossfinders_bins[0]  =  4.0;
    dimucrossfinders_bins[1]  =  4.1;
    dimucrossfinders_bins[2]  =  4.2;
    dimucrossfinders_bins[3]  =  4.3;
    dimucrossfinders_bins[4]  =  4.4;
    dimucrossfinders_bins[5]  =  4.5;
    dimucrossfinders_bins[6]  =  4.6;
    dimucrossfinders_bins[7]  =  4.7;
    dimucrossfinders_bins[8]  =  4.8;
    dimucrossfinders_bins[9]  =  4.9;
    dimucrossfinders_bins[10] =  5.0;
    dimucrossfinders_bins[11] =  5.1;
    dimucrossfinders_bins[12] =  5.2;
    dimucrossfinders_bins[13] =  5.3;
    dimucrossfinders_bins[14] =  5.4;
    dimucrossfinders_bins[15] =  5.5;
    dimucrossfinders_bins[16] =  5.6;
    dimucrossfinders_bins[17] =  5.7;
    dimucrossfinders_bins[18] =  5.8;
    dimucrossfinders_bins[19] =  5.9;
    dimucrossfinders_bins[20] =  6.0;
    dimucrossfinders_bins[21] =  6.1;
    dimucrossfinders_bins[22] =  6.2;
    dimucrossfinders_bins[23] =  6.3;
    dimucrossfinders_bins[24] =  6.4;
    dimucrossfinders_bins[25] =  6.5;
    dimucrossfinders_bins[26] =  6.6;
    dimucrossfinders_bins[27] =  6.7;
    dimucrossfinders_bins[28] =  6.8;
    dimucrossfinders_bins[29] =  6.9;
    dimucrossfinders_bins[30] =  7.0;
    dimucrossfinders_bins[31] =  7.1;
    dimucrossfinders_bins[32] =  7.2;
    dimucrossfinders_bins[33] =  7.3;
    dimucrossfinders_bins[34] =  7.4;
    dimucrossfinders_bins[35] =  7.5;
    dimucrossfinders_bins[36] =  7.6;
    dimucrossfinders_bins[37] =  7.7;
    dimucrossfinders_bins[38] =  7.8;
    dimucrossfinders_bins[39] =  7.9;
    dimucrossfinders_bins[40] =  8.0;

    Int_t    dimucrossdr_nbins = 7;
    Double_t *dimucrossdr_bins = new Double_t[dimucrossdr_nbins+1];
    dimucrossdr_bins[0] = 0.0;
    dimucrossdr_bins[1] = 1.0;
    dimucrossdr_bins[2] = 1.5;
    dimucrossdr_bins[3] = 2.0;
    dimucrossdr_bins[4] = 2.4;
    dimucrossdr_bins[5] = 2.8;
    dimucrossdr_bins[6] = 3.2;
    dimucrossdr_bins[7] = 4.0;

    Int_t    dimucrossdphi_nbins = 5;
    Double_t *dimucrossdphi_bins = new Double_t[dimucrossdphi_nbins+1];
    dimucrossdphi_bins[0] = 0.0*TMath::Pi()/6.0;
    dimucrossdphi_bins[1] = 2.0*TMath::Pi()/6.0;
    dimucrossdphi_bins[2] = 3.0*TMath::Pi()/6.0;
    dimucrossdphi_bins[3] = 4.0*TMath::Pi()/6.0;
    dimucrossdphi_bins[4] = 5.0*TMath::Pi()/6.0;
    dimucrossdphi_bins[5] = 6.0*TMath::Pi()/6.0;

    
    Int_t    dimucrossptb_nbins = 3;
    Double_t *dimucrossptb_bins = new Double_t[dimucrossptb_nbins+1];
    dimucrossptb_bins[0] = 0.0;
    dimucrossptb_bins[1] = 5.0;
    dimucrossptb_bins[2] = 10.0;
    dimucrossptb_bins[3] = 40.0;

    Int_t    dimucrossptb_sameb_nbins = 3;
    Double_t *dimucrossptb_sameb_bins = new Double_t[dimucrossptb_sameb_nbins+1];
    dimucrossptb_sameb_bins[0] = 0.0;
    dimucrossptb_sameb_bins[1] = 5.0;
    dimucrossptb_sameb_bins[2] = 10.0;
    dimucrossptb_sameb_bins[3] = 40.0;

    Int_t    dimucrossptb_diffb_nbins = 3;
    Double_t *dimucrossptb_diffb_bins = new Double_t[dimucrossptb_diffb_nbins+1];
    dimucrossptb_diffb_bins[0] = 0.0;
    dimucrossptb_diffb_bins[1] = 5.0;
    dimucrossptb_diffb_bins[2] = 10.0;
    dimucrossptb_diffb_bins[3] = 40.0;

    Int_t    dimucrossptb_samecone_nbins = 3;
    Double_t *dimucrossptb_samecone_bins = new Double_t[dimucrossptb_samecone_nbins+1];
    dimucrossptb_samecone_bins[0] = 0.0;
    dimucrossptb_samecone_bins[1] = 5.0;
    dimucrossptb_samecone_bins[2] = 10.0;
    dimucrossptb_samecone_bins[3] = 40.0;
    

// Start new PtB binning
/*
    Int_t    dimucrossptb_nbins = 5;
    Double_t *dimucrossptb_bins = new Double_t[dimucrossptb_nbins+1];
    dimucrossptb_bins[0] = 0.0;
    dimucrossptb_bins[1] = 4.0;
    dimucrossptb_bins[2] = 8.0;
    dimucrossptb_bins[3] = 15.0;
    dimucrossptb_bins[4] = 25.0;
    dimucrossptb_bins[5] = 40.0;

    Int_t    dimucrossptb_sameb_nbins = 5;
    Double_t *dimucrossptb_sameb_bins = new Double_t[dimucrossptb_sameb_nbins+1];
    dimucrossptb_sameb_bins[0] = 0.0;
    dimucrossptb_sameb_bins[1] = 4.0;
    dimucrossptb_sameb_bins[2] = 8.0;
    dimucrossptb_sameb_bins[3] = 15.0;
    dimucrossptb_sameb_bins[4] = 25.0;
    dimucrossptb_sameb_bins[5] = 40.0;

    Int_t    dimucrossptb_diffb_nbins = 5;
    Double_t *dimucrossptb_diffb_bins = new Double_t[dimucrossptb_diffb_nbins+1];
    dimucrossptb_diffb_bins[0] = 0.0;
    dimucrossptb_diffb_bins[1] = 4.0;
    dimucrossptb_diffb_bins[2] = 8.0;
    dimucrossptb_diffb_bins[3] = 15.0;
    dimucrossptb_diffb_bins[4] = 25.0;
    dimucrossptb_diffb_bins[5] = 40.0;

    Int_t    dimucrossptb_samecone_nbins = 5;
    Double_t *dimucrossptb_samecone_bins = new Double_t[dimucrossptb_samecone_nbins+1];
    dimucrossptb_samecone_bins[0] = 0.0;
    dimucrossptb_samecone_bins[1] = 4.0;
    dimucrossptb_samecone_bins[2] = 8.0;
    dimucrossptb_samecone_bins[3] = 15.0;
    dimucrossptb_samecone_bins[4] = 25.0;
    dimucrossptb_samecone_bins[5] = 40.0;
*/
// End of new binning 

    Int_t    dimucrossptb_asym_nbins = 10;
    Double_t *dimucrossptb_asym_bins = new Double_t[dimucrossptb_asym_nbins+1];
    dimucrossptb_asym_bins[0] = 0.0;
    dimucrossptb_asym_bins[1] = 0.1;
    dimucrossptb_asym_bins[2] = 0.2;
    dimucrossptb_asym_bins[3] = 0.3;
    dimucrossptb_asym_bins[4] = 0.4;
    dimucrossptb_asym_bins[5] = 0.5;
    dimucrossptb_asym_bins[6] = 0.6;
    dimucrossptb_asym_bins[7] = 0.7;
    dimucrossptb_asym_bins[8] = 0.8;
    dimucrossptb_asym_bins[9] = 0.9;
    dimucrossptb_asym_bins[10] = 1.0;

    Int_t    cal_et_m_et2irbins = 200;
    Double_t cal_et_m_et2irlow  = 0.;
    Double_t cal_et_m_et2irhigh = 100.;
    Int_t    cal_et_m_cal_et_10bins = 200;
    Double_t cal_et_m_cal_et_10low  = 0.;
    Double_t cal_et_m_cal_et_10high = 100.;


    TString triggertype = "None,Muon1,Muon2,Both";
      
    Int_t MuonPt_NBins    = 26;
    Double_t MuonPt_Bins[MuonPt_NBins+1];
    MuonPt_Bins[0]  = 0.0;
    MuonPt_Bins[1]  = 0.1;
    MuonPt_Bins[2]  = 0.2;
    MuonPt_Bins[3]  = 0.3;
    MuonPt_Bins[4]  = 0.4;
    MuonPt_Bins[5]  = 0.5;
    MuonPt_Bins[6]  = 0.6;
    MuonPt_Bins[7]  = 0.7;
    MuonPt_Bins[8]  = 0.8;
    MuonPt_Bins[9]  = 0.9;
    MuonPt_Bins[10] = 1.0;
    MuonPt_Bins[11] = 1.1;
    MuonPt_Bins[12] = 1.2;
    MuonPt_Bins[13] = 1.3;
    MuonPt_Bins[14] = 1.4;
    MuonPt_Bins[15] = 1.5;
    MuonPt_Bins[16] = 1.6;
    MuonPt_Bins[17] = 1.7;
    MuonPt_Bins[18] = 1.8;
    MuonPt_Bins[19] = 1.9;
    MuonPt_Bins[20] = 2.0;
    MuonPt_Bins[21] = 2.2;
    MuonPt_Bins[22] = 2.4;
    MuonPt_Bins[23] = 2.6;
    MuonPt_Bins[24] = 3.0;
    MuonPt_Bins[25] = 3.4;
    MuonPt_Bins[26] = 5.0;
      
    Int_t MuonP_NBins    = 10;
    Double_t MuonP_Bins[MuonP_NBins+1];
    MuonP_Bins[0]  = 0.;
    MuonP_Bins[1]  = 0.5;
    MuonP_Bins[2]  = 1.0;
    MuonP_Bins[3]  = 1.5;
    MuonP_Bins[4]  = 2.0;
    MuonP_Bins[5]  = 2.5;
    MuonP_Bins[6]  = 3.0;
    MuonP_Bins[7]  = 3.5;
    MuonP_Bins[8]  = 4.0;
    MuonP_Bins[9]  = 8.0;
    MuonP_Bins[10] = 13.0;
      
    Int_t MuonPz_NBins    = 26;
    Double_t MuonPz_Bins[MuonPz_NBins+1];
    MuonPz_Bins[0]  =-13.0;
    MuonPz_Bins[1]  =-12.0;
    MuonPz_Bins[2]  =-11.0;
    MuonPz_Bins[3]  =-10.0;
    MuonPz_Bins[4]  = -9.0;
    MuonPz_Bins[5]  = -8.0;
    MuonPz_Bins[6]  = -7.0;
    MuonPz_Bins[7]  = -6.0;
    MuonPz_Bins[8]  = -5.0;
    MuonPz_Bins[9]  = -4.0;
    MuonPz_Bins[10] = -3.0;
    MuonPz_Bins[11] = -2.0;
    MuonPz_Bins[12] = -1.0;
    MuonPz_Bins[13] =  0.0;
    MuonPz_Bins[14] =  1.0;
    MuonPz_Bins[15] =  2.0;
    MuonPz_Bins[16] =  3.0;
    MuonPz_Bins[17] =  4.0;
    MuonPz_Bins[18] =  5.0;
    MuonPz_Bins[19] =  6.0;
    MuonPz_Bins[20] =  7.0;
    MuonPz_Bins[21] =  8.0;
    MuonPz_Bins[22] =  9.0;
    MuonPz_Bins[23] = 10.0;
    MuonPz_Bins[24] = 11.0;
    MuonPz_Bins[25] = 12.0;
    MuonPz_Bins[26] = 13.0;
      
    //     Int_t MuonEta_NBins    = 5;
    //     Double_t MuonEta_Bins[MuonEta_NBins+1];
    //     MuonEta_Bins[0]  = -4.0;
    //     MuonEta_Bins[1]  = -0.9;
    //     MuonEta_Bins[2]  = -0.2;
    //     MuonEta_Bins[3]  =  0.5;
    //     MuonEta_Bins[4]  =  1.2;
    //     MuonEta_Bins[5]  =  4.0;

    // pre upgrade eta bins
    Int_t MuonEta_NBins    = 12;
    Double_t MuonEta_Bins[MuonEta_NBins+1];
    MuonEta_Bins[0]  = -4.0;
    MuonEta_Bins[1]  = -1.7;
    MuonEta_Bins[2]  = -1.2;
    MuonEta_Bins[3]  = -0.9;
    MuonEta_Bins[4]  = -0.4;
    MuonEta_Bins[5]  =  0.0;
    MuonEta_Bins[6]  =  0.4;
    MuonEta_Bins[7]  =  0.8;
    MuonEta_Bins[8]  =  1.2;
    MuonEta_Bins[9]  =  1.5;
    MuonEta_Bins[10] =  1.9;
    MuonEta_Bins[11] =  2.5;
    MuonEta_Bins[12] =  4.0;
      
    Int_t MuonPhi_NBins    = 63;
    Double_t MuonPhi_Bins[MuonPhi_NBins+1];
    for ( Int_t i = 0; i <= MuonPhi_NBins; ++i )
      MuonPhi_Bins[i]  = -TMath::Pi()+TMath::Pi()/MuonPhi_NBins*2*i;
      
    Int_t MuonPt_NBins_Forward    = 26;
    Double_t MuonPt_Bins_Forward[MuonPt_NBins_Forward+1];
    MuonPt_Bins_Forward[0]  = 0.0;
    MuonPt_Bins_Forward[1]  = 0.1;
    MuonPt_Bins_Forward[2]  = 0.2;
    MuonPt_Bins_Forward[3]  = 0.3;
    MuonPt_Bins_Forward[4]  = 0.4;
    MuonPt_Bins_Forward[5]  = 0.5;
    MuonPt_Bins_Forward[6]  = 0.6;
    MuonPt_Bins_Forward[7]  = 0.7;
    MuonPt_Bins_Forward[8]  = 0.8;
    MuonPt_Bins_Forward[9]  = 0.9;
    MuonPt_Bins_Forward[10] = 1.0;
    MuonPt_Bins_Forward[11] = 1.1;
    MuonPt_Bins_Forward[12] = 1.2;
    MuonPt_Bins_Forward[13] = 1.3;
    MuonPt_Bins_Forward[14] = 1.4;
    MuonPt_Bins_Forward[15] = 1.5;
    MuonPt_Bins_Forward[16] = 1.6;
    MuonPt_Bins_Forward[17] = 1.7;
    MuonPt_Bins_Forward[18] = 1.8;
    MuonPt_Bins_Forward[19] = 1.9;
    MuonPt_Bins_Forward[20] = 2.0;
    MuonPt_Bins_Forward[21] = 2.2;
    MuonPt_Bins_Forward[22] = 2.4;
    MuonPt_Bins_Forward[23] = 2.6;
    MuonPt_Bins_Forward[24] = 3.0;
    MuonPt_Bins_Forward[25] = 3.4;
    MuonPt_Bins_Forward[26] = 5.0;
      
    Int_t MuonP_NBins_Forward    = 17;
    Double_t MuonP_Bins_Forward[MuonP_NBins_Forward+1];
    MuonP_Bins_Forward[0]  = 0.;
    MuonP_Bins_Forward[1]  = 0.5;
    MuonP_Bins_Forward[2]  = 1.0;
    MuonP_Bins_Forward[3]  = 1.5;
    MuonP_Bins_Forward[4]  = 2.0;
    MuonP_Bins_Forward[5]  = 2.5;
    MuonP_Bins_Forward[6]  = 3.0;
    MuonP_Bins_Forward[7]  = 3.5;
    MuonP_Bins_Forward[8]  = 4.0;
    MuonP_Bins_Forward[9]  = 4.5;
    MuonP_Bins_Forward[10] = 5.0;
    MuonP_Bins_Forward[11] = 5.5;
    MuonP_Bins_Forward[12] = 6.0;
    MuonP_Bins_Forward[13] = 7.0;
    MuonP_Bins_Forward[14] = 8.0;
    MuonP_Bins_Forward[15] = 9.0;
    MuonP_Bins_Forward[16] =10.0;
    MuonP_Bins_Forward[17] =13.0;
      
    Int_t MuonPz_NBins_Forward    = 16;
    Double_t MuonPz_Bins_Forward[MuonPz_NBins_Forward+1];
    MuonPz_Bins_Forward[0]  =  0.0;
    MuonPz_Bins_Forward[1]  =  0.5;
    MuonPz_Bins_Forward[2]  =  1.0;
    MuonPz_Bins_Forward[3]  =  1.5;
    MuonPz_Bins_Forward[4]  =  2.0;
    MuonPz_Bins_Forward[5]  =  2.5;
    MuonPz_Bins_Forward[6]  =  3.0;
    MuonPz_Bins_Forward[7]  =  3.5;
    MuonPz_Bins_Forward[8]  =  4.0;
    MuonPz_Bins_Forward[9]  =  4.5;
    MuonPz_Bins_Forward[10] =  5.0;
    MuonPz_Bins_Forward[11] =  6.0;
    MuonPz_Bins_Forward[12] =  7.0;
    MuonPz_Bins_Forward[13] =  8.0;
    MuonPz_Bins_Forward[14] =  9.5;
    MuonPz_Bins_Forward[15] = 11.0;
    MuonPz_Bins_Forward[16] = 13.0;
      
    Int_t MuonEta_NBins_Forward    = 9;
    Double_t MuonEta_Bins_Forward[MuonEta_NBins_Forward+1];
    MuonEta_Bins_Forward[0] =  1.2;
    MuonEta_Bins_Forward[1] =  1.4;
    MuonEta_Bins_Forward[2] =  1.6;
    MuonEta_Bins_Forward[3] =  1.8;
    MuonEta_Bins_Forward[4] =  2.0;
    MuonEta_Bins_Forward[5] =  2.2;
    MuonEta_Bins_Forward[6] =  2.4;
    MuonEta_Bins_Forward[7] =  2.6;
    MuonEta_Bins_Forward[8] =  3.0;
    MuonEta_Bins_Forward[9] =  4.0;
      
    Int_t MuonPhi_NBins_Forward    = 63;
    Double_t MuonPhi_Bins_Forward[MuonPhi_NBins_Forward+1];
    for ( Int_t i = 0; i <= MuonPhi_NBins_Forward; ++i )
      MuonPhi_Bins_Forward[i]  = -TMath::Pi()+TMath::Pi()/MuonPhi_NBins_Forward*2*i;
      
    Int_t MuonPt_NBins_Barrel    = 26;
    Double_t MuonPt_Bins_Barrel[MuonPt_NBins_Barrel+1];
    MuonPt_Bins_Barrel[0]  = 0.0;
    MuonPt_Bins_Barrel[1]  = 0.1;
    MuonPt_Bins_Barrel[2]  = 0.2;
    MuonPt_Bins_Barrel[3]  = 0.3;
    MuonPt_Bins_Barrel[4]  = 0.4;
    MuonPt_Bins_Barrel[5]  = 0.5;
    MuonPt_Bins_Barrel[6]  = 0.6;
    MuonPt_Bins_Barrel[7]  = 0.7;
    MuonPt_Bins_Barrel[8]  = 0.8;
    MuonPt_Bins_Barrel[9]  = 0.9;
    MuonPt_Bins_Barrel[10] = 1.0;
    MuonPt_Bins_Barrel[11] = 1.1;
    MuonPt_Bins_Barrel[12] = 1.2;
    MuonPt_Bins_Barrel[13] = 1.3;
    MuonPt_Bins_Barrel[14] = 1.4;
    MuonPt_Bins_Barrel[15] = 1.5;
    MuonPt_Bins_Barrel[16] = 1.6;
    MuonPt_Bins_Barrel[17] = 1.7;
    MuonPt_Bins_Barrel[18] = 1.8;
    MuonPt_Bins_Barrel[19] = 1.9;
    MuonPt_Bins_Barrel[20] = 2.0;
    MuonPt_Bins_Barrel[21] = 2.2;
    MuonPt_Bins_Barrel[22] = 2.4;
    MuonPt_Bins_Barrel[23] = 2.6;
    MuonPt_Bins_Barrel[24] = 3.0;
    MuonPt_Bins_Barrel[25] = 3.4;
    MuonPt_Bins_Barrel[26] = 5.0;
      
    Int_t MuonP_NBins_Barrel    = 11;
    Double_t MuonP_Bins_Barrel[MuonP_NBins_Barrel+1];
    MuonP_Bins_Barrel[0]  = 0.;
    MuonP_Bins_Barrel[1]  = 0.5;
    MuonP_Bins_Barrel[2]  = 1.0;
    MuonP_Bins_Barrel[3]  = 1.5;
    MuonP_Bins_Barrel[4]  = 2.0;
    MuonP_Bins_Barrel[5]  = 2.5;
    MuonP_Bins_Barrel[7]  = 3.0;
    MuonP_Bins_Barrel[8]  = 4.0;
    MuonP_Bins_Barrel[9]  = 5.0;
    MuonP_Bins_Barrel[10] = 8.0;
    MuonP_Bins_Barrel[11] =13.0;
      
    Int_t MuonPz_NBins_Barrel    = 10;
    Double_t MuonPz_Bins_Barrel[MuonPz_NBins_Barrel+1];
    MuonPz_Bins_Barrel[0]  = -5.0;
    MuonPz_Bins_Barrel[1]  = -4.0;
    MuonPz_Bins_Barrel[2]  = -3.0;
    MuonPz_Bins_Barrel[3]  = -2.0;
    MuonPz_Bins_Barrel[4]  = -1.0;
    MuonPz_Bins_Barrel[5]  =  0.0;
    MuonPz_Bins_Barrel[6]  =  1.0;
    MuonPz_Bins_Barrel[7]  =  2.0;
    MuonPz_Bins_Barrel[8]  =  3.0;
    MuonPz_Bins_Barrel[9]  =  4.0;
    MuonPz_Bins_Barrel[10] =  5.0;
      
    Int_t MuonEta_NBins_Barrel    = 11;
    Double_t MuonEta_Bins_Barrel[MuonEta_NBins_Barrel+1];
    MuonEta_Bins_Barrel[0]  = -1.0;
    MuonEta_Bins_Barrel[1]  = -0.8;
    MuonEta_Bins_Barrel[2]  = -0.6;
    MuonEta_Bins_Barrel[3]  = -0.4;
    MuonEta_Bins_Barrel[4]  = -0.2;
    MuonEta_Bins_Barrel[5]  =  0.0;
    MuonEta_Bins_Barrel[6]  =  0.2;
    MuonEta_Bins_Barrel[7]  =  0.4;
    MuonEta_Bins_Barrel[8]  =  0.6;
    MuonEta_Bins_Barrel[9]  =  0.8;
    MuonEta_Bins_Barrel[10] =  1.0;
    MuonEta_Bins_Barrel[11] =  1.2;
      
    Int_t MuonPhi_NBins_Barrel    = 63;
    Double_t MuonPhi_Bins_Barrel[MuonPhi_NBins_Barrel+1];
    for ( Int_t i = 0; i <= MuonPhi_NBins_Barrel; ++i )
      MuonPhi_Bins_Barrel[i]  = -TMath::Pi()+TMath::Pi()/MuonPhi_NBins_Barrel*2*i;
      
    Int_t MuonPt_NBins_Rear    = 26;
    Double_t MuonPt_Bins_Rear[MuonPt_NBins_Rear+1];
    MuonPt_Bins_Rear[0]  = 0.0;
    MuonPt_Bins_Rear[1]  = 0.1;
    MuonPt_Bins_Rear[2]  = 0.2;
    MuonPt_Bins_Rear[3]  = 0.3;
    MuonPt_Bins_Rear[4]  = 0.4;
    MuonPt_Bins_Rear[5]  = 0.5;
    MuonPt_Bins_Rear[6]  = 0.6;
    MuonPt_Bins_Rear[7]  = 0.7;
    MuonPt_Bins_Rear[8]  = 0.8;
    MuonPt_Bins_Rear[9]  = 0.9;
    MuonPt_Bins_Rear[10] = 1.0;
    MuonPt_Bins_Rear[11] = 1.1;
    MuonPt_Bins_Rear[12] = 1.2;
    MuonPt_Bins_Rear[13] = 1.3;
    MuonPt_Bins_Rear[14] = 1.4;
    MuonPt_Bins_Rear[15] = 1.5;
    MuonPt_Bins_Rear[16] = 1.6;
    MuonPt_Bins_Rear[17] = 1.7;
    MuonPt_Bins_Rear[18] = 1.8;
    MuonPt_Bins_Rear[19] = 1.9;
    MuonPt_Bins_Rear[20] = 2.0;
    MuonPt_Bins_Rear[21] = 2.2;
    MuonPt_Bins_Rear[22] = 2.4;
    MuonPt_Bins_Rear[23] = 2.6;
    MuonPt_Bins_Rear[24] = 3.0;
    MuonPt_Bins_Rear[25] = 3.4;
    MuonPt_Bins_Rear[26] = 5.0;
      
    Int_t MuonP_NBins_Rear    = 15;
    Double_t MuonP_Bins_Rear[MuonP_NBins_Rear+1];
    MuonP_Bins_Rear[0]  = 0.;
    MuonP_Bins_Rear[1]  = 0.5;
    MuonP_Bins_Rear[2]  = 1.0;
    MuonP_Bins_Rear[3]  = 1.5;
    MuonP_Bins_Rear[4]  = 2.0;
    MuonP_Bins_Rear[5]  = 2.5;
    MuonP_Bins_Rear[6]  = 3.0;
    MuonP_Bins_Rear[7]  = 3.5;
    MuonP_Bins_Rear[8]  = 4.0;
    MuonP_Bins_Rear[9]  = 4.5;
    MuonP_Bins_Rear[10] = 5.0;
    MuonP_Bins_Rear[11] = 6.0;
    MuonP_Bins_Rear[12] = 7.0;
    MuonP_Bins_Rear[13] = 8.0;
    MuonP_Bins_Rear[14] =10.0;
    MuonP_Bins_Rear[15] =13.0;
      
    Int_t MuonPz_NBins_Rear    = 22;
    Double_t MuonPz_Bins_Rear[MuonPz_NBins_Rear+1];
    MuonPz_Bins_Rear[22] =  0.0;
    MuonPz_Bins_Rear[21] = -0.25;
    MuonPz_Bins_Rear[20] = -0.5;
    MuonPz_Bins_Rear[19] = -0.75;
    MuonPz_Bins_Rear[18] = -1.0;
    MuonPz_Bins_Rear[17] = -1.25;
    MuonPz_Bins_Rear[16] = -1.5;
    MuonPz_Bins_Rear[15] = -1.75;
    MuonPz_Bins_Rear[14] = -2.0;
    MuonPz_Bins_Rear[13] = -2.25;
    MuonPz_Bins_Rear[12] = -2.75;
    MuonPz_Bins_Rear[11] = -3.25;
    MuonPz_Bins_Rear[10] = -3.75;
    MuonPz_Bins_Rear[9]  = -4.25;
    MuonPz_Bins_Rear[8]  = -4.75;
    MuonPz_Bins_Rear[7]  = -5.25;
    MuonPz_Bins_Rear[6]  = -5.75;
    MuonPz_Bins_Rear[5]  = -6.25;
    MuonPz_Bins_Rear[4]  = -7.25;
    MuonPz_Bins_Rear[3]  = -8.25;
    MuonPz_Bins_Rear[2]  = -9.25;
    MuonPz_Bins_Rear[1]  =-11.0;
    MuonPz_Bins_Rear[0]  =-13.0;
      
    Int_t MuonEta_NBins_Rear    = 11;
    Double_t MuonEta_Bins_Rear[MuonEta_NBins_Rear+1];
    MuonEta_Bins_Rear[0]  = -4.0;
    MuonEta_Bins_Rear[1]  = -3.0;
    MuonEta_Bins_Rear[2]  = -2.6;
    MuonEta_Bins_Rear[3]  = -2.4;
    MuonEta_Bins_Rear[4]  = -2.2;
    MuonEta_Bins_Rear[5]  = -2.0;
    MuonEta_Bins_Rear[6]  = -1.8;
    MuonEta_Bins_Rear[7]  = -1.6;
    MuonEta_Bins_Rear[8]  = -1.4;
    MuonEta_Bins_Rear[9]  = -1.2;
    MuonEta_Bins_Rear[10] = -1.0;
    MuonEta_Bins_Rear[11] = -0.8;
      
    Int_t MuonPhi_NBins_Rear    = 63;
    Double_t MuonPhi_Bins_Rear[MuonPhi_NBins_Rear+1];
    for ( Int_t i = 0; i <= MuonPhi_NBins_Rear; ++i )
      MuonPhi_Bins_Rear[i]  = -TMath::Pi()+TMath::Pi()/MuonPhi_NBins_Rear*2*i;
    fGeneralNperEv_uncut = gHistogrammer->TH1DFactory("DIMuon","NperEv_uncut","uncut n_{#mu#mu}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu}","Events");
    fGeneralDIMuonMass_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMass_uncut","uncut #mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassLow_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassLow_uncut","uncut low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassHigh_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassHigh_uncut","uncut high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMass_LikeSign_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMass_LikeSign_uncut","uncut #mu#mu invariant mass for like-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassLow_LikeSign_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassLow_LikeSign_uncut","uncut low #mu#mu invariant mass for like-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassHigh_LikeSign_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassHigh_LikeSign_uncut","uncut high #mu#mu invariant mass for like-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMass_UnlikeSign_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMass_UnlikeSign_uncut","uncut #mu#mu invariant mass for unlike-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassLow_UnlikeSign_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassLow_UnlikeSign_uncut","uncut low #mu#mu invariant mass for unlike-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassHigh_UnlikeSign_uncut = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassHigh_UnlikeSign_uncut","uncut high #mu#mu invariant mass for unlike-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralMass_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_lu_is_uncut","good #mass_lu_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_ll_is_uncut","good #mass_ll_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_hu_is_uncut","good #mass_hu_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_hl_is_uncut","good #mass_hl_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_lu_nis_uncut","good #mass_lu_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_ll_nis_uncut","good #mass_ll_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_hu_nis_uncut","good #mass_hu_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","Mass_hl_nis_uncut","good #mass_hl_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralDeltaR_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_uncut","uncut #DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR","Events");
    fGeneralDeltaR_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_lu_is_uncut","uncut #DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_is","Events");
    fGeneralDeltaR_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_ll_is_uncut","uncut #DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_is","Events");
    fGeneralDeltaR_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hu_is_uncut","uncut #DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_is","Events");
    fGeneralDeltaR_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hl_is_uncut","uncut #DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_is","Events");
    fGeneralDeltaR_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_lu_nis_uncut","uncut #DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_nis","Events");
    fGeneralDeltaR_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_ll_nis_uncut","uncut #DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_nis","Events");
    fGeneralDeltaR_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hu_nis_uncut","uncut #DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_nis","Events");
    fGeneralDeltaR_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hl_nis_uncut","uncut #DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_nis","Events");
    fGeneralDeltaPhi_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_uncut","uncut #Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","Events");
    fGeneralDeltaPhi_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_lu_is_uncut","uncut #Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_is","Events");
    fGeneralDeltaPhi_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_ll_is_uncut","uncut #Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_is","Events");
    fGeneralDeltaPhi_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hu_is_uncut","uncut #Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_is","Events");
    fGeneralDeltaPhi_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hl_is_uncut","uncut #Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_is","Events");
    fGeneralDeltaPhi_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_lu_nis_uncut","uncut #Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_nis","Events");
    fGeneralDeltaPhi_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_ll_nis_uncut","uncut #Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_nis","Events");
    fGeneralDeltaPhi_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hu_nis_uncut","uncut #Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_nis","Events");
    fGeneralDeltaPhi_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hl_nis_uncut","uncut #Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_nis","Events");
    fGeneralDeltaEta_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_uncut","uncut #Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta","Events");
    fGeneralDeltaTheta_uncut = gHistogrammer->TH1DFactory("DIMuon","DeltaTheta_uncut","uncut #Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta","Events");
    fGeneraldimuphi_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_uncut","uncut phi ",dimuphibins,dimuphilow,dimuphihigh,"phi dimu","Events");
    fGeneraldimuphi_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_lu_is_uncut","uncut #dimuphi_{#mu}_lu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_is","Events");
    fGeneraldimuphi_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_ll_is_uncut","uncut #dimuphi_{#mu}_ll_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_is","Events");
    fGeneraldimuphi_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hu_is_uncut","uncut #dimuphi_{#mu}_hu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_is","Events");
    fGeneraldimuphi_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hl_is_uncut","uncut #dimuphi_{#mu}_hl_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_is","Events");
    fGeneraldimuphi_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_lu_nis_uncut","uncut #dimuphi_{#mu}_lu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_nis","Events");
    fGeneraldimuphi_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_ll_nis_uncut","uncut #dimuphi_{#mu}_ll_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_nis","Events");
    fGeneraldimuphi_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hu_nis_uncut","uncut #dimuphi_{#mu}_hu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_nis","Events");
    fGeneraldimuphi_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hl_nis_uncut","uncut #dimuphi_{#mu}_hl_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_nis","Events");
    fGeneraldimueta_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_uncut","uncut eta ",dimuetabins,dimuetalow,dimuetahigh,"eta dimu","Events");
    fGeneraldimueta_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_lu_is_uncut","uncut #dimueta_{#mu}_lu_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_lu_is","Events");
    fGeneraldimueta_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_ll_is_uncut","uncut #dimueta_{#mu}_ll_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_ll_is","Events");
    fGeneraldimueta_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_hu_is_uncut","uncut #dimueta_{#mu}_hu_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hu_is","Events");
    fGeneraldimueta_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_hl_is_uncut","uncut #dimueta_{#mu}_hl_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hl_is","Events");
    fGeneraldimueta_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_lu_nis_uncut","uncut #dimueta_{#mu}_lu_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_lu_nis","Events");
    fGeneraldimueta_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_ll_nis_uncut","uncut #dimueta_{#mu}_ll_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_ll_nis","Events");
    fGeneraldimueta_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_hu_nis_uncut","uncut #dimueta_{#mu}_hu_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hu_nis","Events");
    fGeneraldimueta_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimueta_hl_nis_uncut","uncut #dimueta_{#mu}_hl_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hl_nis","Events");
    fGeneralPtAsymetry_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_uncut","uncut p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.","Events");
    fGeneralPtAsymetry_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_lu_is_uncut","uncut p_{T}_lu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.","Events");
    fGeneralPtAsymetry_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_ll_is_uncut","uncut p_{T}_ll_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.","Events");
    fGeneralPtAsymetry_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hu_is_uncut","uncut p_{T}_hu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.","Events");
    fGeneralPtAsymetry_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hl_is_uncut","uncut p_{T}_hl_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.","Events");
    fGeneralPtAsymetry_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_lu_nis_uncut","uncut p_{T}_lu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.","Events");
    fGeneralPtAsymetry_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_ll_nis_uncut","uncut p_{T}_ll_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.","Events");
    fGeneralPtAsymetry_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hu_nis_uncut","uncut p_{T}_hu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.","Events");
    fGeneralPtAsymetry_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hl_nis_uncut","uncut p_{T}_hl_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.","Events");
    fGeneralpt_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_uncut","uncut p_{T} ",ptbins,ptlow,pthigh,"p_{T}","Events");
    fGeneralpt_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_lu_is_uncut","uncut #pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_is","Events");
    fGeneralpt_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_ll_is_uncut","uncut #pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_is","Events");
    fGeneralpt_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_hu_is_uncut","uncut #pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_is","Events");
    fGeneralpt_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_hl_is_uncut","uncut #pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_is","Events");
    fGeneralpt_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_lu_nis_uncut","uncut #pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_nis","Events");
    fGeneralpt_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_ll_nis_uncut","uncut #pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_nis","Events");
    fGeneralpt_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_hu_nis_uncut","uncut #pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_nis","Events");
    fGeneralpt_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","pt_hl_nis_uncut","uncut #pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_nis","Events");
    fGeneraldimupt_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_uncut","uncut p_{T} ",dimuptbins,dimuptlow,dimupthigh,"p_{T}dimu","Events");
    fGeneraldimupt_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_lu_is_uncut","uncut #dimupt_{#mu}_lu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_lu_is","Events");
    fGeneraldimupt_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_ll_is_uncut","uncut #dimupt_{#mu}_ll_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_ll_is","Events");
    fGeneraldimupt_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_hu_is_uncut","uncut #dimupt_{#mu}_hu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hu_is","Events");
    fGeneraldimupt_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_hl_is_uncut","uncut #dimupt_{#mu}_hl_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hl_is","Events");
    fGeneraldimupt_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_lu_nis_uncut","uncut #dimupt_{#mu}_lu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_lu_nis","Events");
    fGeneraldimupt_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_ll_nis_uncut","uncut #dimupt_{#mu}_ll_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_ll_nis","Events");
    fGeneraldimupt_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_hu_nis_uncut","uncut #dimupt_{#mu}_hu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hu_nis","Events");
    fGeneraldimupt_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","dimupt_hl_nis_uncut","uncut #dimupt_{#mu}_hl_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hl_nis","Events");
    fGeneraleta_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_uncut","uncut #eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu}","Events");
    fGeneraleta_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_lu_is_uncut","uncut #eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}_lu_is","Events");
    fGeneraleta_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_ll_is_uncut","uncut #eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}_ll_is","Events");
    fGeneraleta_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_hu_is_uncut","uncut #eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}_hu_is","Events");
    fGeneraleta_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_hl_is_uncut","uncut #eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}_hl_is","Events");
    fGeneraleta_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_lu_nis_uncut","uncut #eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_lu_nis","Events");
    fGeneraleta_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_ll_nis_uncut","uncut #eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}_ll_nis","Events");
    fGeneraleta_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_hu_nis_uncut","uncut #eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hu_nis","Events");
    fGeneraleta_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","eta_hl_nis_uncut","uncut #eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hl_nis","Events");

    fGeneralVtxMass_uncut    = gHistogrammer->TH1DFactory("DIMuon","VtxMass_uncut","uncut VtxMass",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx} [GeV]","Events");
    fGeneralVtxMass_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_lu_uncut","uncut_lu VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_lu [GeV]","Events");
    fGeneralVtxMass_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_ll_uncut","uncut_ll VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_ll [GeV]","Events");
    fGeneralVtxMass_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_hu_uncut","uncut_hu VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_hu [GeV]","Events");
    fGeneralVtxMass_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_hl_uncut","uncut_hl VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_hl [GeV]","Events");
    fGeneralVtxMass_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_lu_uncut","uncut_lu VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_lu [GeV]","Events");
    fGeneralVtxMass_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_ll_uncut","uncut_ll VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_ll [GeV]","Events");
    fGeneralVtxMass_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_hu_uncut","uncut_hu VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_hu [GeV]","Events");
    fGeneralVtxMass_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_hl_uncut","uncut_hl VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_hl [GeV]","Events");

    fGeneralChi2_uncut    = gHistogrammer->TH1DFactory("DIMuon","Chi2_uncut","uncut Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralChi2_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_lu_uncut","uncut_lu Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_lu","Events");
    fGeneralChi2_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_ll_uncut","uncut_ll Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_ll","Events");
    fGeneralChi2_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_hu_uncut","uncut_hu Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_hu","Events");
    fGeneralChi2_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_hl_uncut","uncut_hl Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_hl","Events");
    fGeneralChi2_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_lu_uncut","uncut_lu Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_lu","Events");
    fGeneralChi2_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_ll_uncut","uncut_ll Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_ll","Events");
    fGeneralChi2_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_hu_uncut","uncut_hu Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_hu","Events");
    fGeneralChi2_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_hl_uncut","uncut_hl Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_hl","Events");

    fGeneralNdof_uncut    = gHistogrammer->TH1DFactory("DIMuon","Ndof_uncut","uncut Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneralNdof_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_lu_uncut","uncut_lu Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_lu","Events");
    fGeneralNdof_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_ll_uncut","uncut_ll Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_ll","Events");
    fGeneralNdof_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_hu_uncut","uncut_hu Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_hu","Events");
    fGeneralNdof_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_hl_uncut","uncut_hl Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_hl","Events");
    fGeneralNdof_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_lu_uncut","uncut_lu Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_lu","Events");
    fGeneralNdof_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_ll_uncut","uncut_ll Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_ll","Events");
    fGeneralNdof_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_hu_uncut","uncut_hu Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_hu","Events");
    fGeneralNdof_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_hl_uncut","uncut_hl Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_hl","Events");

    fGeneralMulti_uncut    = gHistogrammer->TH1DFactory("DIMuon","Multi_uncut","uncut Multi",multibins,multilow,multihigh,"multi","Events");
    fGeneralMulti_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_is_lu_uncut","uncut_lu Multi_is",multibins,multilow,multihigh,"multi_is_lu","Events");
    fGeneralMulti_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_is_ll_uncut","uncut_ll Multi_is",multibins,multilow,multihigh,"multi_is_ll","Events");
    fGeneralMulti_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_is_hu_uncut","uncut_hu Multi_is",multibins,multilow,multihigh,"multi_is_hu","Events");
    fGeneralMulti_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_is_hl_uncut","uncut_hl Multi_is",multibins,multilow,multihigh,"multi_is_hl","Events");
    fGeneralMulti_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_lu_uncut","uncut_lu Multi_nis",multibins,multilow,multihigh,"multi_nis_lu","Events");
    fGeneralMulti_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_ll_uncut","uncut_ll Multi_nis",multibins,multilow,multihigh,"multi_nis_ll","Events");
    fGeneralMulti_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_hu_uncut","uncut_hu Multi_nis",multibins,multilow,multihigh,"multi_nis_hu","Events");
    fGeneralMulti_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_hl_uncut","uncut_hl Multi_nis",multibins,multilow,multihigh,"multi_nis_hl","Events");

    fGeneralNrsecvtx_uncut    = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_uncut","uncut Nrsecvtx",nrsecbins,nrseclow,nrsechigh,"nrsecvtx","Events");
    fGeneralNrsecvtx_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_lu_uncut","uncut_lu Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_lu","Events");
    fGeneralNrsecvtx_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_ll_uncut","uncut_ll Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_ll","Events");
    fGeneralNrsecvtx_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_hu_uncut","uncut_hu Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_hu","Events");
    fGeneralNrsecvtx_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_hl_uncut","uncut_hl Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_hl","Events");
    fGeneralNrsecvtx_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_lu_uncut","uncut_lu Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_lu","Events");
    fGeneralNrsecvtx_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_ll_uncut","uncut_ll Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_ll","Events");
    fGeneralNrsecvtx_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_hu_uncut","uncut_hu Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_hu","Events");
    fGeneralNrsecvtx_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_hl_uncut","uncut_hl Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_hl","Events");

    fGeneralMunphi_uncut    = gHistogrammer->TH1DFactory("DIMuon","Munphi_uncut","uncut Munphi",munphibins,munphilow,munphihigh,"# Munphi","Events");
    fGeneralMunphi_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_lu_uncut","uncut_lu Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_lu","Events");
    fGeneralMunphi_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_ll_uncut","uncut_ll Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_ll","Events");
    fGeneralMunphi_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_hu_uncut","uncut_hu Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_hu","Events");
    fGeneralMunphi_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_hl_uncut","uncut_hl Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_hl","Events");
    fGeneralMunphi_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_lu_uncut","uncut_lu Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_lu","Events");
    fGeneralMunphi_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_ll_uncut","uncut_ll Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_ll","Events");
    fGeneralMunphi_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_hu_uncut","uncut_hu Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_hu","Events");
    fGeneralMunphi_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_hl_uncut","uncut_hl Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_hl","Events");

    fGeneralMundof_uncut    = gHistogrammer->TH1DFactory("DIMuon","Mundof_uncut","uncut Mundof",mundofbins,mundoflow,mundofhigh,"Mundof","Events");
    fGeneralMundof_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_lu_uncut","uncut_lu Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_lu","Events");
    fGeneralMundof_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_ll_uncut","uncut_ll Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_ll","Events");
    fGeneralMundof_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_hu_uncut","uncut_hu Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_hu","Events");
    fGeneralMundof_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_hl_uncut","uncut_hl Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_hl","Events");
    fGeneralMundof_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_lu_uncut","uncut_lu Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_lu","Events");
    fGeneralMundof_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_ll_uncut","uncut_ll Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_ll","Events");
    fGeneralMundof_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_hu_uncut","uncut_hu Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_hu","Events");
    fGeneralMundof_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_hl_uncut","uncut_hl Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_hl","Events");

    fGeneralMupmat_uncut    = gHistogrammer->TH1DFactory("DIMuon","Mupmat_uncut","uncut Mupmat",mupmatbins,mupmatlow,mupmathigh,"MuPMat","Events");
    fGeneralMupmat_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_lu_uncut","uncut_lu Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_lu","Events");
    fGeneralMupmat_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_ll_uncut","uncut_ll Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_ll","Events");
    fGeneralMupmat_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_hu_uncut","uncut_hu Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_hu","Events");
    fGeneralMupmat_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_hl_uncut","uncut_hl Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_hl","Events");
    fGeneralMupmat_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_lu_uncut","uncut_lu Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_lu","Events");
    fGeneralMupmat_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_ll_uncut","uncut_ll Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_ll","Events");
    fGeneralMupmat_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_hu_uncut","uncut_hu Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_hu","Events");
    fGeneralMupmat_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_hl_uncut","uncut_hl Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_hl","Events");

    fGeneralMPMatchID_uncut    = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_uncut","uncut MPMatchID",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID","Events");
    fGeneralMPMatchID_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_lu_uncut","uncut_lu MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_lu","Events");
    fGeneralMPMatchID_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_ll_uncut","uncut_ll MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_ll","Events");
    fGeneralMPMatchID_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_hu_uncut","uncut_hu MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_hu","Events");
    fGeneralMPMatchID_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_hl_uncut","uncut_hl MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_hl","Events");
    fGeneralMPMatchID_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_lu_uncut","uncut_lu MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_lu","Events");
    fGeneralMPMatchID_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_ll_uncut","uncut_ll MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_ll","Events");
    fGeneralMPMatchID_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_hu_uncut","uncut_hu MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_hu","Events");
    fGeneralMPMatchID_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_hl_uncut","uncut_hl MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_hl","Events");

    fGeneralMuMvID_uncut    = gHistogrammer->TH1DFactory("DIMuon","MuMvID_uncut","uncut MuMvID",mumvidbins,mumvidlow,mumvidhigh,"MuMvID","Events");
    fGeneralMuMvID_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_lu_uncut","uncut_lu MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_lu","Events");
    fGeneralMuMvID_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_ll_uncut","uncut_ll MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_ll","Events");
    fGeneralMuMvID_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_hu_uncut","uncut_hu MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_hu","Events");
    fGeneralMuMvID_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_hl_uncut","uncut_hl MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_hl","Events");
    fGeneralMuMvID_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_lu_uncut","uncut_lu MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_lu","Events");
    fGeneralMuMvID_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_ll_uncut","uncut_ll MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_ll","Events");
    fGeneralMuMvID_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_hu_uncut","uncut_hu MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_hu","Events");
    fGeneralMuMvID_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_hl_uncut","uncut_hl MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_hl","Events");

    fGeneralMuMufoID_uncut    = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_uncut","uncut MuMufoID",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID","Events");
    fGeneralMuMufoID_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_lu_uncut","uncut_lu MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_lu","Events");
    fGeneralMuMufoID_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_ll_uncut","uncut_ll MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_ll","Events");
    fGeneralMuMufoID_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_hu_uncut","uncut_hu MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_hu","Events");
    fGeneralMuMufoID_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_hl_uncut","uncut_hl MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_hl","Events");
    fGeneralMuMufoID_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_lu_uncut","uncut_lu MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_lu","Events");
    fGeneralMuMufoID_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_ll_uncut","uncut_ll MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_ll","Events");
    fGeneralMuMufoID_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_hu_uncut","uncut_hu MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_hu","Events");
    fGeneralMuMufoID_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_hl_uncut","uncut_hl MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_hl","Events");

    fGeneralMuz_uncut    = gHistogrammer->TH1DFactory("DIMuon","Muz_uncut","uncut Muz",muzbins,muzlow,muzhigh,"Muz","Events");
    fGeneralMuz_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_is_lu_uncut","uncut_lu Muz_is",muzbins,muzlow,muzhigh,"Muz_is_lu","Events");
    fGeneralMuz_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_is_ll_uncut","uncut_ll Muz_is",muzbins,muzlow,muzhigh,"Muz_is_ll","Events");
    fGeneralMuz_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_is_hu_uncut","uncut_hu Muz_is",muzbins,muzlow,muzhigh,"Muz_is_hu","Events");
    fGeneralMuz_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_is_hl_uncut","uncut_hl Muz_is",muzbins,muzlow,muzhigh,"Muz_is_hl","Events");
    fGeneralMuz_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_lu_uncut","uncut_lu Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_lu","Events");
    fGeneralMuz_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_ll_uncut","uncut_ll Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_ll","Events");
    fGeneralMuz_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_hu_uncut","uncut_hu Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_hu","Events");
    fGeneralMuz_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_hl_uncut","uncut_hl Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_hl","Events");

//**** BacMat Information

    fGeneralMuBacMatID_uncut    = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_uncut","uncut MuBacMatID",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID","Events");
    fGeneralMuBacMatID_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_lu_uncut","uncut_lu MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_lu","Events");
    fGeneralMuBacMatID_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_ll_uncut","uncut_ll MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_ll","Events");
    fGeneralMuBacMatID_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_hu_uncut","uncut_hu MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_hu","Events");
    fGeneralMuBacMatID_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_hl_uncut","uncut_hl MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_hl","Events");
    fGeneralMuBacMatID_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_lu_uncut","uncut_lu MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_lu","Events");
    fGeneralMuBacMatID_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_ll_uncut","uncut_ll MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_ll","Events");
    fGeneralMuBacMatID_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_hu_uncut","uncut_hu MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_hu","Events");
    fGeneralMuBacMatID_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_hl_uncut","uncut_hl MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_hl","Events");

    fGeneralNBacMat_uncut    = gHistogrammer->TH1DFactory("DIMuon","NBacMat_uncut","uncut NBacMat",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat","Events");
    fGeneralNBacMat_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_lu_uncut","uncut_lu NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_lu","Events");
    fGeneralNBacMat_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_ll_uncut","uncut_ll NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_ll","Events");
    fGeneralNBacMat_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_hu_uncut","uncut_hu NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_hu","Events");
    fGeneralNBacMat_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_hl_uncut","uncut_hl NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_hl","Events");
    fGeneralNBacMat_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_lu_uncut","uncut_lu NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_lu","Events");
    fGeneralNBacMat_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_ll_uncut","uncut_ll NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_ll","Events");
    fGeneralNBacMat_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_hu_uncut","uncut_hu NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_hu","Events");
    fGeneralNBacMat_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_hl_uncut","uncut_hl NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_hl","Events");

    fGeneralBacMat_VCID_uncut    = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_uncut","uncut BacMat_VCID",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID","Events");
    fGeneralBacMat_VCID_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_lu_uncut","uncut_lu BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_lu","Events");
    fGeneralBacMat_VCID_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_ll_uncut","uncut_ll BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_ll","Events");
    fGeneralBacMat_VCID_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_hu_uncut","uncut_hu BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_hu","Events");
    fGeneralBacMat_VCID_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_hl_uncut","uncut_hl BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_hl","Events");
    fGeneralBacMat_VCID_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_lu_uncut","uncut_lu BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_lu","Events");
    fGeneralBacMat_VCID_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_ll_uncut","uncut_ll BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_ll","Events");
    fGeneralBacMat_VCID_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_hu_uncut","uncut_hu BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_hu","Events");
    fGeneralBacMat_VCID_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_hl_uncut","uncut_hl BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_hl","Events");

    fGeneralBacMat_MuBacID_uncut    = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_uncut","uncut BacMat_MuBacID",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID","Events");
    fGeneralBacMat_MuBacID_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_lu_uncut","uncut_lu BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_lu","Events");
    fGeneralBacMat_MuBacID_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_ll_uncut","uncut_ll BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_ll","Events");
    fGeneralBacMat_MuBacID_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_hu_uncut","uncut_hu BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_hu","Events");
    fGeneralBacMat_MuBacID_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_hl_uncut","uncut_hl BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_hl","Events");
    fGeneralBacMat_MuBacID_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_lu_uncut","uncut_lu BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_lu","Events");
    fGeneralBacMat_MuBacID_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_ll_uncut","uncut_ll BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_ll","Events");
    fGeneralBacMat_MuBacID_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_hu_uncut","uncut_hu BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_hu","Events");
    fGeneralBacMat_MuBacID_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_hl_uncut","uncut_hl BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_hl","Events");

    fGeneralBacMat_Istop_uncut    = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_uncut","uncut BacMat_Istop",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop","Events");
    fGeneralBacMat_Istop_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_lu_uncut","uncut_lu BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_lu","Events");
    fGeneralBacMat_Istop_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_ll_uncut","uncut_ll BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_ll","Events");
    fGeneralBacMat_Istop_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_hu_uncut","uncut_hu BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_hu","Events");
    fGeneralBacMat_Istop_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_hl_uncut","uncut_hl BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_hl","Events");
    fGeneralBacMat_Istop_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_lu_uncut","uncut_lu BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_lu","Events");
    fGeneralBacMat_Istop_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_ll_uncut","uncut_ll BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_ll","Events");
    fGeneralBacMat_Istop_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_hu_uncut","uncut_hu BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_hu","Events");
    fGeneralBacMat_Istop_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_hl_uncut","uncut_hl BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_hl","Events");

    fGeneralBacMat_Error_uncut    = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_uncut","uncut BacMat_Error",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error","Events");
    fGeneralBacMat_Error_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_lu_uncut","uncut_lu BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_lu","Events");
    fGeneralBacMat_Error_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_ll_uncut","uncut_ll BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_ll","Events");
    fGeneralBacMat_Error_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_hu_uncut","uncut_hu BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_hu","Events");
    fGeneralBacMat_Error_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_hl_uncut","uncut_hl BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_hl","Events");
    fGeneralBacMat_Error_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_lu_uncut","uncut_lu BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_lu","Events");
    fGeneralBacMat_Error_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_ll_uncut","uncut_ll BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_ll","Events");
    fGeneralBacMat_Error_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_hu_uncut","uncut_hu BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_hu","Events");
    fGeneralBacMat_Error_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_hl_uncut","uncut_hl BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_hl","Events");

    fGeneralBacMat_Readout_uncut    = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_uncut","uncut BacMat_Readout",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout","Events");
    fGeneralBacMat_Readout_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_lu_uncut","uncut_lu BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_lu","Events");
    fGeneralBacMat_Readout_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_ll_uncut","uncut_ll BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_ll","Events");
    fGeneralBacMat_Readout_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_hu_uncut","uncut_hu BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_hu","Events");
    fGeneralBacMat_Readout_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_hl_uncut","uncut_hl BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_hl","Events");
    fGeneralBacMat_Readout_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_lu_uncut","uncut_lu BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_lu","Events");
    fGeneralBacMat_Readout_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_ll_uncut","uncut_ll BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_ll","Events");
    fGeneralBacMat_Readout_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_hu_uncut","uncut_hu BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_hu","Events");
    fGeneralBacMat_Readout_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_hl_uncut","uncut_hl BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_hl","Events");

    fGeneralImpact2D_uncut    = gHistogrammer->TH1DFactory("DIMuon","Impact2D_uncut","uncut Impact2D",impactbins,impactlow,impacthigh,"#2D_IP [cm]","Events");
    fGeneralImpact2D_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_lu_uncut","uncut_lu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_lu [cm]","Events");
    fGeneralImpact2D_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_ll_uncut","uncut_ll Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_ll [cm]","Events");
    fGeneralImpact2D_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_hu_uncut","uncut_hu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_hu [cm]","Events");
    fGeneralImpact2D_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_hl_uncut","uncut_hl Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_hl [cm]","Events");
    fGeneralImpact2D_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_lu_uncut","uncut_lu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_lu [cm]","Events");
    fGeneralImpact2D_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_ll_uncut","uncut_ll Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_ll [cm]","Events");
    fGeneralImpact2D_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_hu_uncut","uncut_hu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_hu [cm]","Events");
    fGeneralImpact2D_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_hl_uncut","uncut_hl Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_hl [cm]","Events");

    fGeneralImpact2D_Sign_uncut    = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_uncut","uncut Impact2D_Sign",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign","Events");
    fGeneralImpact2D_Sign_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_lu_uncut","uncut_lu Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_lu","Events");
    fGeneralImpact2D_Sign_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_ll_uncut","uncut_ll Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_ll","Events");
    fGeneralImpact2D_Sign_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_hu_uncut","uncut_hu Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_hu","Events");
    fGeneralImpact2D_Sign_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_hl_uncut","uncut_hl Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_hl","Events");
    fGeneralImpact2D_Sign_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_lu_uncut","uncut_lu Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_lu","Events");
    fGeneralImpact2D_Sign_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_ll_uncut","uncut_ll Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_ll","Events");
    fGeneralImpact2D_Sign_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_hu_uncut","uncut_hu Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_hu","Events");
    fGeneralImpact2D_Sign_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_hl_uncut","uncut_hl Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_hl","Events");

    fGeneralDL2_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_uncut","uncut DL2",dl2bins,dl2low,dl2high,"Decay length","Events");
    fGeneralDL2_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_is_lu_uncut","uncut_lu DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_lu","Events");
    fGeneralDL2_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_is_ll_uncut","uncut_ll DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_ll","Events");
    fGeneralDL2_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_is_hu_uncut","uncut_hu DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_hu","Events");
    fGeneralDL2_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_is_hl_uncut","uncut_hl DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_hl","Events");
    fGeneralDL2_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_lu_uncut","uncut_lu DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_lu","Events");
    fGeneralDL2_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_ll_uncut","uncut_ll DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_ll","Events");
    fGeneralDL2_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_hu_uncut","uncut_hu DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_hu","Events");
    fGeneralDL2_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_hl_uncut","uncut_hl DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_hl","Events");

    fGeneralDL2_Sign_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_uncut","uncut DL2_Sign",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance","Events");
    fGeneralDL2_Sign_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_lu_uncut","uncut_lu DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_lu","Events");
    fGeneralDL2_Sign_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_ll_uncut","uncut_ll DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_ll","Events");
    fGeneralDL2_Sign_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_hu_uncut","uncut_hu DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_hu","Events");
    fGeneralDL2_Sign_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_hl_uncut","uncut_hl DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_hl","Events");
    fGeneralDL2_Sign_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_lu_uncut","uncut_lu DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_lu","Events");
    fGeneralDL2_Sign_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_ll_uncut","uncut_ll DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_ll","Events");
    fGeneralDL2_Sign_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_hu_uncut","uncut_hu DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_hu","Events");
    fGeneralDL2_Sign_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_hl_uncut","uncut_hl DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_hl","Events");

    fGeneralDL2_Sign_Mirrp_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_uncut","uncut DL2_Sign_Mirrp",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance","Events");
    fGeneralDL2_Sign_Mirrp_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_lu_uncut","uncut_lu DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_lu","Events");
    fGeneralDL2_Sign_Mirrp_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_ll_uncut","uncut_ll DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_ll","Events");
    fGeneralDL2_Sign_Mirrp_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_hu_uncut","uncut_hu DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_hu","Events");
    fGeneralDL2_Sign_Mirrp_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_hl_uncut","uncut_hl DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_hl","Events");
    fGeneralDL2_Sign_Mirrp_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_lu_uncut","uncut_lu DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_lu","Events");
    fGeneralDL2_Sign_Mirrp_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_ll_uncut","uncut_ll DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_ll","Events");
    fGeneralDL2_Sign_Mirrp_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_hu_uncut","uncut_hu DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_hu","Events");
    fGeneralDL2_Sign_Mirrp_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_hl_uncut","uncut_hl DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_hl","Events");

    fGeneralDL2_Sign_Mirrm_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_uncut","uncut DL2_Sign_Mirrm",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance","Events");
    fGeneralDL2_Sign_Mirrm_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_lu_uncut","uncut_lu DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_lu","Events");
    fGeneralDL2_Sign_Mirrm_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_ll_uncut","uncut_ll DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_ll","Events");
    fGeneralDL2_Sign_Mirrm_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_hu_uncut","uncut_hu DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_hu","Events");
    fGeneralDL2_Sign_Mirrm_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_hl_uncut","uncut_hl DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_hl","Events");
    fGeneralDL2_Sign_Mirrm_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_lu_uncut","uncut_lu DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_lu","Events");
    fGeneralDL2_Sign_Mirrm_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_ll_uncut","uncut_ll DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_ll","Events");
    fGeneralDL2_Sign_Mirrm_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_hu_uncut","uncut_hu DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_hu","Events");
    fGeneralDL2_Sign_Mirrm_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_hl_uncut","uncut_hl DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_hl","Events");

    fGeneralMuJetDeltaR_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_uncut","uncut MuJetDeltaR",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}","Events");
    fGeneralMuJetDeltaR_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_lu_uncut","uncut_lu MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_lu","Events");
    fGeneralMuJetDeltaR_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_ll_uncut","uncut_ll MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_ll","Events");
    fGeneralMuJetDeltaR_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_hu_uncut","uncut_hu MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_hu","Events");
    fGeneralMuJetDeltaR_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_hl_uncut","uncut_hl MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_hl","Events");
    fGeneralMuJetDeltaR_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_lu_uncut","uncut_lu MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_lu","Events");
    fGeneralMuJetDeltaR_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_ll_uncut","uncut_ll MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_ll","Events");
    fGeneralMuJetDeltaR_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_hu_uncut","uncut_hu MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_hu","Events");
    fGeneralMuJetDeltaR_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_hl_uncut","uncut_hl MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_hl","Events");

    fGeneralMuJetPt_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_uncut","uncut MuJetPt",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet} [GeV]","Events");
    fGeneralMuJetPt_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_lu_uncut","uncut_lu MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_lu [GeV]","Events");
    fGeneralMuJetPt_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_ll_uncut","uncut_ll MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_ll [GeV]","Events");
    fGeneralMuJetPt_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_hu_uncut","uncut_hu MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_hu [GeV]","Events");
    fGeneralMuJetPt_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_hl_uncut","uncut_hl MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_hl [GeV]","Events");
    fGeneralMuJetPt_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_lu_uncut","uncut_lu MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_lu [GeV]","Events");
    fGeneralMuJetPt_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_ll_uncut","uncut_ll MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_ll [GeV]","Events");
    fGeneralMuJetPt_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_hu_uncut","uncut_hu MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_hu [GeV]","Events");
    fGeneralMuJetPt_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_hl_uncut","uncut_hl MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_hl [GeV]","Events");

    fGeneralMuJetEt_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_uncut","uncut MuJetEt",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet} [GeV]","Events");
    fGeneralMuJetEt_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_lu_uncut","uncut_lu MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_lu [GeV]","Events");
    fGeneralMuJetEt_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_ll_uncut","uncut_ll MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_ll [GeV]","Events");
    fGeneralMuJetEt_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_hu_uncut","uncut_hu MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_hu [GeV]","Events");
    fGeneralMuJetEt_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_hl_uncut","uncut_hl MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_hl [GeV]","Events");
    fGeneralMuJetEt_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_lu_uncut","uncut_lu MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_lu [GeV]","Events");
    fGeneralMuJetEt_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_ll_uncut","uncut_ll MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_ll [GeV]","Events");
    fGeneralMuJetEt_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_hu_uncut","uncut_hu MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_hu [GeV]","Events");
    fGeneralMuJetEt_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_hl_uncut","uncut_hl MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_hl [GeV]","Events");

    fGeneralMuJetEta_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_uncut","uncut MuJetEta",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}","Events");
    fGeneralMuJetEta_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_lu_uncut","uncut_lu MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_lu","Events");
    fGeneralMuJetEta_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_ll_uncut","uncut_ll MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_ll","Events");
    fGeneralMuJetEta_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_hu_uncut","uncut_hu MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_hu","Events");
    fGeneralMuJetEta_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_hl_uncut","uncut_hl MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_hl","Events");
    fGeneralMuJetEta_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_lu_uncut","uncut_lu MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_lu","Events");
    fGeneralMuJetEta_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_ll_uncut","uncut_ll MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_ll","Events");
    fGeneralMuJetEta_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_hu_uncut","uncut_hu MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_hu","Events");
    fGeneralMuJetEta_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_hl_uncut","uncut_hl MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_hl","Events");

    fGeneralMassJet_uncut    = gHistogrammer->TH1DFactory("DIMuon","MassJet_uncut","uncut MassJet",massjetbins,massjetlow,massjethigh,"#MassJet [GeV]","Events");
    fGeneralMassJet_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_lu_uncut","uncut_lu MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_lu [GeV]","Events");
    fGeneralMassJet_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_ll_uncut","uncut_ll MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_ll [GeV]","Events");
    fGeneralMassJet_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_hu_uncut","uncut_hu MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_hu [GeV]","Events");
    fGeneralMassJet_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_hl_uncut","uncut_hl MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_hl [GeV]","Events");
    fGeneralMassJet_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_lu_uncut","uncut_lu MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_lu [GeV]","Events");
    fGeneralMassJet_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_ll_uncut","uncut_ll MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_ll [GeV]","Events");
    fGeneralMassJet_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_hu_uncut","uncut_hu MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_hu [GeV]","Events");
    fGeneralMassJet_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_hl_uncut","uncut_hl MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_hl [GeV]","Events");

    fGeneralNJets_uncut    = gHistogrammer->TH1DFactory("DIMuon","NJets_uncut","uncut NJets",njetbins,njetlow,njethigh,"#NJets","Events");
    fGeneralNJets_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_is_lu_uncut","uncut_lu NJets_is",njetbins,njetlow,njethigh,"#NJets_is_lu","Events");
    fGeneralNJets_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_is_ll_uncut","uncut_ll NJets_is",njetbins,njetlow,njethigh,"#NJets_is_ll","Events");
    fGeneralNJets_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_is_hu_uncut","uncut_hu NJets_is",njetbins,njetlow,njethigh,"#NJets_is_hu","Events");
    fGeneralNJets_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_is_hl_uncut","uncut_hl NJets_is",njetbins,njetlow,njethigh,"#NJets_is_hl","Events");
    fGeneralNJets_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_lu_uncut","uncut_lu NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_lu","Events");
    fGeneralNJets_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_ll_uncut","uncut_ll NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_ll","Events");
    fGeneralNJets_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_hu_uncut","uncut_hu NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_hu","Events");
    fGeneralNJets_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_hl_uncut","uncut_hl NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_hl","Events");

    fGeneralphi_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_uncut","uncut #phi_{#mu}",phibins,philow,phihigh,"#phi_{#mu}","Events");
    fGeneralphi_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_lu_is_uncut","uncut #phi_{#mu}_lu_is ",phibins,philow,phihigh,"#phi_{#mu}_lu_is","Events");
    fGeneralphi_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_ll_is_uncut","uncut #phi_{#mu}_ll_is ",phibins,philow,phihigh,"#phi_{#mu}_ll_is","Events");
    fGeneralphi_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_hu_is_uncut","uncut #phi_{#mu}_hu_is ",phibins,philow,phihigh,"#phi_{#mu}_hu_is","Events");
    fGeneralphi_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_hl_is_uncut","uncut #phi_{#mu}_hl_is ",phibins,philow,phihigh,"#phi_{#mu}_hl_is","Events");
    fGeneralphi_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_lu_nis_uncut","uncut #phi_{#mu}_lu_nis ",phibins,philow,phihigh,"#phi_{#mu}_lu_nis","Events");
    fGeneralphi_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_ll_nis_uncut","uncut #phi_{#mu}_ll_nis ",phibins,philow,phihigh,"#phi_{#mu}_ll_nis","Events");
    fGeneralphi_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_hu_nis_uncut","uncut #phi_{#mu}_hu_nis ",phibins,philow,phihigh,"#phi_{#mu}_hu_nis","Events");
    fGeneralphi_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","phi_hl_nis_uncut","uncut #phi_{#mu}_hl_nis ",phibins,philow,phihigh,"#phi_{#mu}_hl_nis","Events");
    fGeneralmuqual_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_uncut","uncut #muqual_{#mu} ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}","Events");
    fGeneralmuqual_lu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_lu_is_uncut","uncut #muqual_{#mu}_lu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_is","Events");
    fGeneralmuqual_ll_is_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_ll_is_uncut","uncut #muqual_{#mu}_ll_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_is","Events");
    fGeneralmuqual_hu_is_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_hu_is_uncut","uncut #muqual_{#mu}_hu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_is","Events");
    fGeneralmuqual_hl_is_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_hl_is_uncut","uncut #muqual_{#mu}_hl_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_is","Events");
    fGeneralmuqual_lu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_lu_nis_uncut","uncut #muqual_{#mu}_lu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_nis","Events");
    fGeneralmuqual_ll_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_ll_nis_uncut","uncut #muqual_{#mu}_ll_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_nis","Events");
    fGeneralmuqual_hu_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_hu_nis_uncut","uncut #muqual_{#mu}_hu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_nis","Events");
    fGeneralmuqual_hl_nis_uncut = gHistogrammer->TH1DFactory("DIMuon","muqual_hl_nis_uncut","uncut #muqual_{#mu}_hl_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_nis","Events");

    fGeneralsqisol_10_uncut    = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_uncut","uncut sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    fGeneralsqisol_10_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_lu_uncut","uncut_lu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_lu","Events");
    fGeneralsqisol_10_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_ll_uncut","uncut_ll sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_ll","Events");
    fGeneralsqisol_10_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_hu_uncut","uncut_hu sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hu","Events");
    fGeneralsqisol_10_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_hl_uncut","uncut_hl sqisol_10_is_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hl","Events");
    fGeneralsqisol_10_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_lu_uncut","uncut_lu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_lu","Events");
    fGeneralsqisol_10_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_ll_uncut","uncut_ll sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_ll","Events");
    fGeneralsqisol_10_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_hu_uncut","uncut_hu sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hu","Events");
    fGeneralsqisol_10_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_hl_uncut","uncut_hl sqisol_10_nis_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hl","Events");

    fGeneralthrust_uncut    = gHistogrammer->TH1DFactory("DIMuon","thrust_uncut","uncut thrust",thrustbins,thrustlow,thrusthigh,"#thrust","Events");
    fGeneralthrust_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_is_lu_uncut","uncut_lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_lu","Events");
    fGeneralthrust_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_is_ll_uncut","uncut_ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_ll","Events");
    fGeneralthrust_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_is_hu_uncut","uncut_hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hu","Events");
    fGeneralthrust_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_is_hl_uncut","uncut_hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hl","Events");
    fGeneralthrust_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_lu_uncut","uncut_lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_lu","Events");
    fGeneralthrust_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_ll_uncut","uncut_ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_ll","Events");
    fGeneralthrust_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_hu_uncut","uncut_hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hu","Events");
    fGeneralthrust_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_hl_uncut","uncut_hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hl","Events");

//**************************************************
//Here the Histograms for the Instanton - Variables
//**************************************************

    fGeneralQ2Prime_uncut    = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_uncut","uncut Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2}","Events");
    fGeneralQ2Prime_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_lu_uncut","uncut_lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_lu","Events");
    fGeneralQ2Prime_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_ll_uncut","uncut_ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_ll","Events");
    fGeneralQ2Prime_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_hu_uncut","uncut_hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hu","Events");
    fGeneralQ2Prime_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_hl_uncut","uncut_hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hl","Events");
    fGeneralQ2Prime_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_lu_uncut","uncut_lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_lu","Events");
    fGeneralQ2Prime_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_ll_uncut","uncut_ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_ll","Events");
    fGeneralQ2Prime_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_hu_uncut","uncut_hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hu","Events");
    fGeneralQ2Prime_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_hl_uncut","uncut_hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hl","Events");

    fGeneralsphericity_uncut    = gHistogrammer->TH1DFactory("DIMuon","sphericity_uncut","uncut sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity","Events");
    fGeneralsphericity_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_lu_uncut","uncut_lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_lu","Events");
    fGeneralsphericity_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_ll_uncut","uncut_ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_ll","Events");
    fGeneralsphericity_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_hu_uncut","uncut_hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hu","Events");
    fGeneralsphericity_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_hl_uncut","uncut_hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hl","Events");
    fGeneralsphericity_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_lu_uncut","uncut_lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_lu","Events");
    fGeneralsphericity_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_ll_uncut","uncut_ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_ll","Events");
    fGeneralsphericity_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_hu_uncut","uncut_hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hu","Events");
    fGeneralsphericity_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_hl_uncut","uncut_hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hl","Events");

    fGeneralisotropy_uncut    = gHistogrammer->TH1DFactory("DIMuon","isotropy_uncut","uncut isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy","Events");
    fGeneralisotropy_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_lu_uncut","uncut_lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_lu","Events");
    fGeneralisotropy_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_ll_uncut","uncut_ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_ll","Events");
    fGeneralisotropy_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_hu_uncut","uncut_hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hu","Events");
    fGeneralisotropy_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_hl_uncut","uncut_hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hl","Events");
    fGeneralisotropy_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_lu_uncut","uncut_lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_lu","Events");
    fGeneralisotropy_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_ll_uncut","uncut_ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_ll","Events");
    fGeneralisotropy_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_hu_uncut","uncut_hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hu","Events");
    fGeneralisotropy_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_hl_uncut","uncut_hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hl","Events");

    fGeneralmultiplicity_uncut    = gHistogrammer->TH1DFactory("DIMuon","multiplicity_uncut","uncut multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity","Events");
    fGeneralmultiplicity_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_lu_uncut","uncut_lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_lu","Events");
    fGeneralmultiplicity_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_ll_uncut","uncut_ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_ll","Events");
    fGeneralmultiplicity_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_hu_uncut","uncut_hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hu","Events");
    fGeneralmultiplicity_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_hl_uncut","uncut_hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hl","Events");
    fGeneralmultiplicity_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_lu_uncut","uncut_lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_lu","Events");
    fGeneralmultiplicity_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_ll_uncut","uncut_ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_ll","Events");
    fGeneralmultiplicity_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_hu_uncut","uncut_hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hu","Events");
    fGeneralmultiplicity_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_hl_uncut","uncut_hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hl","Events");

//*************************************************************

    fGeneralcal_et_uncut    = gHistogrammer->TH1DFactory("DIMuon","cal_et_uncut","uncut cal_et",cal_etbins,cal_etlow,cal_ethigh,"#cal_et","Events");
    fGeneralcal_et_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_lu_uncut","uncut_lu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_lu","Events");
    fGeneralcal_et_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_ll_uncut","uncut_ll cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_ll","Events");
    fGeneralcal_et_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_hu_uncut","uncut_hu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hu","Events");
    fGeneralcal_et_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_hl_uncut","uncut_hl cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hl","Events");
    fGeneralcal_et_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_lu_uncut","uncut_lu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_lu","Events");
    fGeneralcal_et_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_ll_uncut","uncut_ll cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_ll","Events");
    fGeneralcal_et_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_hu_uncut","uncut_hu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hu","Events");
    fGeneralcal_et_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_hl_uncut","uncut_hl cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hl","Events");

    fGeneraletex2ir_uncut    = gHistogrammer->TH1DFactory("DIMuon","etex2ir_uncut","uncut etex2ir",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir","Events");
    fGeneraletex2ir_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_lu_uncut","uncut_lu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_lu","Events");
    fGeneraletex2ir_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_ll_uncut","uncut_ll etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_ll","Events");
    fGeneraletex2ir_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_hu_uncut","uncut_hu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hu","Events");
    fGeneraletex2ir_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_hl_uncut","uncut_hl etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hl","Events");
    fGeneraletex2ir_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_lu_uncut","uncut_lu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_lu","Events");
    fGeneraletex2ir_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_ll_uncut","uncut_ll etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_ll","Events");
    fGeneraletex2ir_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_hu_uncut","uncut_hu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hu","Events");
    fGeneraletex2ir_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_hl_uncut","uncut_hl etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hl","Events");

    fGeneralcal_et_m_et2ir_uncut    = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_uncut","uncut cal_et_m_et2ir",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir","Events");
    fGeneralcal_et_m_et2ir_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_lu_uncut","uncut_lu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_lu","Events");
    fGeneralcal_et_m_et2ir_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_ll_uncut","uncut_ll cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_ll","Events");
    fGeneralcal_et_m_et2ir_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_hu_uncut","uncut_hu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hu","Events");
    fGeneralcal_et_m_et2ir_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_hl_uncut","uncut_hl cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hl","Events");
    fGeneralcal_et_m_et2ir_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_lu_uncut","uncut_lu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_lu","Events");
    fGeneralcal_et_m_et2ir_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_ll_uncut","uncut_ll cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_ll","Events");
    fGeneralcal_et_m_et2ir_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_hu_uncut","uncut_hu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hu","Events");
    fGeneralcal_et_m_et2ir_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_hl_uncut","uncut_hl cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hl","Events");

    fGeneralcal_et_m_cal_et_10_uncut    = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_uncut","uncut cal_et_m_cal_et_10",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10","Events");
    fGeneralcal_et_m_cal_et_10_is_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_lu_uncut","uncut_lu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_lu","Events");
    fGeneralcal_et_m_cal_et_10_is_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_ll_uncut","uncut_ll cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_ll","Events");
    fGeneralcal_et_m_cal_et_10_is_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_hu_uncut","uncut_hu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hu","Events");
    fGeneralcal_et_m_cal_et_10_is_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_hl_uncut","uncut_hl cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hl","Events");
    fGeneralcal_et_m_cal_et_10_nis_lu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_lu_uncut","uncut_lu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_lu","Events");
    fGeneralcal_et_m_cal_et_10_nis_ll_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_ll_uncut","uncut_ll cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_ll","Events");
    fGeneralcal_et_m_cal_et_10_nis_hu_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_hu_uncut","uncut_hu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hu","Events");
    fGeneralcal_et_m_cal_et_10_nis_hl_uncut = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_hl_uncut","uncut_hl cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hl","Events");

    if( gCards->GetDoEfficiency()) {
      fGeneralTriggerType_uncut = gHistogrammer->TH1DLabelFactory("DIMuon","TriggerType_uncut","uncut Trigger Type",triggertype,"","Events");
    }

    fGeneralNperEv = gHistogrammer->TH1DFactory("DIMuon","NperEv","n_{#mu#mu}",nperevbins,nperevlow,nperevhigh,"n_{#mu#mu}","Events");
    fGeneralDIMuonMass = gHistogrammer->TH1DFactory("DIMuon","DIMuonMass","#mu#mu invariant mass",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassLow = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassLow","low #mu#mu invariant mass",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassHigh = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassHigh","high #mu#mu invariant mass",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMass_LikeSign = gHistogrammer->TH1DFactory("DIMuon","DIMuonMass_LikeSign","#mu#mu invariant mass for like-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassLow_LikeSign = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassLow_LikeSign","low #mu#mu invariant mass for like-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassHigh_LikeSign = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassHigh_LikeSign","high #mu#mu invariant mass for like-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMass_UnlikeSign = gHistogrammer->TH1DFactory("DIMuon","DIMuonMass_UnlikeSign","#mu#mu invariant mass for unlike-sign #mu#mu",massbins,masslow,masshigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassLow_UnlikeSign = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassLow_UnlikeSign","low #mu#mu invariant mass for unlike-sign #mu#mu",masslowbins,masslowlow,masslowhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralDIMuonMassHigh_UnlikeSign = gHistogrammer->TH1DFactory("DIMuon","DIMuonMassHigh_UnlikeSign","high #mu#mu invariant mass for unlike-sign #mu#mu",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralMass_lu_is = gHistogrammer->TH1DFactory("DIMuon","Mass_lu_is","#mass_lu_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_is = gHistogrammer->TH1DFactory("DIMuon","Mass_ll_is","#mass_ll_is",masslowbins,masslowlow,masslowhigh,     "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_is = gHistogrammer->TH1DFactory("DIMuon","Mass_hu_is","#mass_hu_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_is = gHistogrammer->TH1DFactory("DIMuon","Mass_hl_is","#mass_hl_is",masshighbins,masshighlow,masshighhigh,   "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_lu_nis = gHistogrammer->TH1DFactory("DIMuon","Mass_lu_nis","#mass_lu_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_ll_nis = gHistogrammer->TH1DFactory("DIMuon","Mass_ll_nis","#mass_ll_nis",masslowbins,masslowlow,masslowhigh,  "m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hu_nis = gHistogrammer->TH1DFactory("DIMuon","Mass_hu_nis","#mass_hu_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");
    fGeneralMass_hl_nis = gHistogrammer->TH1DFactory("DIMuon","Mass_hl_nis","#mass_hl_nis",masshighbins,masshighlow,masshighhigh,"m_{#mu#mu,inv} [GeV]","Events");

    fGeneralDeltaR = gHistogrammer->TH1DFactory("DIMuon","DeltaR","#DeltaR",deltarbins,deltarlow,deltarhigh,"#DeltaR","Events");
    fGeneralDeltaR_lu_is = gHistogrammer->TH1DFactory("DIMuon","DeltaR_lu_is","#DeltaR_lu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_is","Events");
    fGeneralDeltaR_ll_is = gHistogrammer->TH1DFactory("DIMuon","DeltaR_ll_is","#DeltaR_ll_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_is","Events");
    fGeneralDeltaR_hu_is = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hu_is","#DeltaR_hu_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_is","Events");
    fGeneralDeltaR_hl_is = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hl_is","#DeltaR_hl_is",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_is","Events");
    fGeneralDeltaR_lu_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaR_lu_nis","#DeltaR_lu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_lu_nis","Events");
    fGeneralDeltaR_ll_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaR_ll_nis","#DeltaR_ll_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_ll_nis","Events");
    fGeneralDeltaR_hu_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hu_nis","#DeltaR_hu_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hu_nis","Events");
    fGeneralDeltaR_hl_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaR_hl_nis","#DeltaR_hl_nis",deltarbins,deltarlow,deltarhigh,"#DeltaR_hl_nis","Events");
    fGeneralDeltaPhi = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi","#Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","Events");
    fGeneralDeltaPhi_lu_is = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_lu_is","#Delta#phi_lu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_is","Events");
    fGeneralDeltaPhi_ll_is = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_ll_is","#Delta#phi_ll_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_is","Events");
    fGeneralDeltaPhi_hu_is = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hu_is","#Delta#phi_hu_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_is","Events");
    fGeneralDeltaPhi_hl_is = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hl_is","#Delta#phi_hl_is",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_is","Events");
    fGeneralDeltaPhi_lu_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_lu_nis","#Delta#phi_lu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_nis","Events");
    fGeneralDeltaPhi_ll_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_ll_nis","#Delta#phi_ll_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_nis","Events");
    fGeneralDeltaPhi_hu_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hu_nis","#Delta#phi_hu_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_nis","Events");
    fGeneralDeltaPhi_hl_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hl_nis","#Delta#phi_hl_nis",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_nis","Events");
    fGeneralDeltaEta = gHistogrammer->TH1DFactory("DIMuon","DeltaEta","#Delta#eta",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta","Events");
    fGeneralDeltaEta_lu_is = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_lu_is","#Delta#eta_lu_is",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_lu_is","Events");
    fGeneralDeltaEta_ll_is = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_ll_is","#Delta#eta_ll_is",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_ll_is","Events");
    fGeneralDeltaEta_hu_is = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_hu_is","#Delta#eta_hu_is",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_hu_is","Events");
    fGeneralDeltaEta_hl_is = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_hl_is","#Delta#eta_hl_is",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_hl_is","Events");
    fGeneralDeltaEta_lu_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_lu_nis","#Delta#eta_lu_nis",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_lu_nis","Events");
    fGeneralDeltaEta_ll_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_ll_nis","#Delta#eta_ll_nis",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_ll_nis","Events");
    fGeneralDeltaEta_hu_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_hu_nis","#Delta#eta_hu_nis",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_hu_nis","Events");
    fGeneralDeltaEta_hl_nis = gHistogrammer->TH1DFactory("DIMuon","DeltaEta_hl_nis","#Delta#eta_hl_nis",deltaetabins,deltaetalow,deltaetahigh,"#Delta#eta_hl_nis","Events");
    fGeneralDeltaTheta = gHistogrammer->TH1DFactory("DIMuon","DeltaTheta","#Delta#theta",deltathetabins,deltathetalow,deltathetahigh,"#Delta#theta","Events");
    fGeneraldimuphi = gHistogrammer->TH1DFactory("DIMuon","dimuphi","#varphi ",dimuphibins,dimuphilow,dimuphihigh,"#varphi dimu ","Events");
    fGeneraldimuphi_lu_is = gHistogrammer->TH1DFactory("DIMuon","dimuphi_lu_is","#dimuphi_{#mu}_lu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_is ","Events");
    fGeneraldimuphi_ll_is = gHistogrammer->TH1DFactory("DIMuon","dimuphi_ll_is","#dimuphi_{#mu}_ll_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_is ","Events");
    fGeneraldimuphi_hu_is = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hu_is","#dimuphi_{#mu}_hu_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_is ","Events");
    fGeneraldimuphi_hl_is = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hl_is","#dimuphi_{#mu}_hl_is ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_is ","Events");
    fGeneraldimuphi_lu_nis = gHistogrammer->TH1DFactory("DIMuon","dimuphi_lu_nis","#dimuphi_{#mu}_lu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_lu_nis ","Events");
    fGeneraldimuphi_ll_nis = gHistogrammer->TH1DFactory("DIMuon","dimuphi_ll_nis","#dimuphi_{#mu}_ll_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_ll_nis ","Events");
    fGeneraldimuphi_hu_nis = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hu_nis","#dimuphi_{#mu}_hu_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hu_nis ","Events");
    fGeneraldimuphi_hl_nis = gHistogrammer->TH1DFactory("DIMuon","dimuphi_hl_nis","#dimuphi_{#mu}_hl_nis ",dimuphibins,dimuphilow,dimuphihigh,"#dimuphi_{#mu}_hl_nis ","Events");
    fGeneraldimueta = gHistogrammer->TH1DFactory("DIMuon","dimueta","#eta ",dimuetabins,dimuetalow,dimuetahigh,"#eta dimu ","Events");
    fGeneraldimueta_lu_is = gHistogrammer->TH1DFactory("DIMuon","dimueta_lu_is","#dimueta_{#mu}_lu_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_lu_is ","Events");
    fGeneraldimueta_ll_is = gHistogrammer->TH1DFactory("DIMuon","dimueta_ll_is","#dimueta_{#mu}_ll_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_ll_is ","Events");
    fGeneraldimueta_hu_is = gHistogrammer->TH1DFactory("DIMuon","dimueta_hu_is","#dimueta_{#mu}_hu_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hu_is ","Events");
    fGeneraldimueta_hl_is = gHistogrammer->TH1DFactory("DIMuon","dimueta_hl_is","#dimueta_{#mu}_hl_is ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hl_is ","Events");
    fGeneraldimueta_lu_nis = gHistogrammer->TH1DFactory("DIMuon","dimueta_lu_nis","#dimueta_{#mu}_lu_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_lu_nis ","Events");
    fGeneraldimueta_ll_nis = gHistogrammer->TH1DFactory("DIMuon","dimueta_ll_nis","#dimueta_{#mu}_ll_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_ll_nis ","Events");
    fGeneraldimueta_hu_nis = gHistogrammer->TH1DFactory("DIMuon","dimueta_hu_nis","#dimueta_{#mu}_hu_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hu_nis ","Events");
    fGeneraldimueta_hl_nis = gHistogrammer->TH1DFactory("DIMuon","dimueta_hl_nis","#dimueta_{#mu}_hl_nis ",dimuetabins,dimuetalow,dimuetahigh,"#dimueta_{#mu}_hl_nis ","Events");
    fGeneralPtAsymetry = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry","p_{T} asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T} asym.","Events");
    fGeneralPtAsymetry_lu_is = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_lu_is","p_{T}_lu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_is asym.","Events");
    fGeneralPtAsymetry_ll_is = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_ll_is","p_{T}_ll_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_is asym.","Events");
    fGeneralPtAsymetry_hu_is = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hu_is","p_{T}_hu_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_is asym.","Events");
    fGeneralPtAsymetry_hl_is = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hl_is","p_{T}_hl_is asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_is asym.","Events");
    fGeneralPtAsymetry_lu_nis = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_lu_nis","p_{T}_lu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_lu_nis asym.","Events");
    fGeneralPtAsymetry_ll_nis = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_ll_nis","p_{T}_ll_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_ll_nis asym.","Events");
    fGeneralPtAsymetry_hu_nis = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hu_nis","p_{T}_hu_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hu_nis asym.","Events");
    fGeneralPtAsymetry_hl_nis = gHistogrammer->TH1DFactory("DIMuon","PtAsymetry_hl_nis","p_{T}_hl_nis asym.",ptasymetrybins,ptasymetrylow,ptasymetryhigh,"p_{T}_hl_nis asym.","Events");
    fGeneralpt = gHistogrammer->TH1DFactory("DIMuon","pt","p_{T} ",ptbins,ptlow,pthigh,"p_{T} ","Events");
    fGeneralpt_lu_is = gHistogrammer->TH1DFactory("DIMuon","pt_lu_is","#pt_{#mu}_lu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_is ","Events");
    fGeneralpt_ll_is = gHistogrammer->TH1DFactory("DIMuon","pt_ll_is","#pt_{#mu}_ll_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_is ","Events");
    fGeneralpt_hu_is = gHistogrammer->TH1DFactory("DIMuon","pt_hu_is","#pt_{#mu}_hu_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_is ","Events");
    fGeneralpt_hl_is = gHistogrammer->TH1DFactory("DIMuon","pt_hl_is","#pt_{#mu}_hl_is ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_is ","Events");
    fGeneralpt_lu_nis = gHistogrammer->TH1DFactory("DIMuon","pt_lu_nis","#pt_{#mu}_lu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_lu_nis ","Events");
    fGeneralpt_ll_nis = gHistogrammer->TH1DFactory("DIMuon","pt_ll_nis","#pt_{#mu}_ll_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_ll_nis ","Events");
    fGeneralpt_hu_nis = gHistogrammer->TH1DFactory("DIMuon","pt_hu_nis","#pt_{#mu}_hu_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hu_nis ","Events");
    fGeneralpt_hl_nis = gHistogrammer->TH1DFactory("DIMuon","pt_hl_nis","#pt_{#mu}_hl_nis ",ptbins,ptlow,pthigh,"#pt_{#mu}_hl_nis ","Events");
    fGeneraldimupt = gHistogrammer->TH1DFactory("DIMuon","dimupt","p_{T} ",dimuptbins,dimuptlow,dimupthigh,"p_{T}dimu ","Events");
    fGeneraldimupt_lu_is = gHistogrammer->TH1DFactory("DIMuon","dimupt_lu_is","#dimupt_{#mu}_lu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_lu_is ","Events");
    fGeneraldimupt_ll_is = gHistogrammer->TH1DFactory("DIMuon","dimupt_ll_is","#dimupt_{#mu}_ll_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_ll_is ","Events");
    fGeneraldimupt_hu_is = gHistogrammer->TH1DFactory("DIMuon","dimupt_hu_is","#dimupt_{#mu}_hu_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hu_is ","Events");
    fGeneraldimupt_hl_is = gHistogrammer->TH1DFactory("DIMuon","dimupt_hl_is","#dimupt_{#mu}_hl_is ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hl_is ","Events");
    fGeneraldimupt_lu_nis = gHistogrammer->TH1DFactory("DIMuon","dimupt_lu_nis","#dimupt_{#mu}_lu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_lu_nis ","Events");
    fGeneraldimupt_ll_nis = gHistogrammer->TH1DFactory("DIMuon","dimupt_ll_nis","#dimupt_{#mu}_ll_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_ll_nis ","Events");
    fGeneraldimupt_hu_nis = gHistogrammer->TH1DFactory("DIMuon","dimupt_hu_nis","#dimupt_{#mu}_hu_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hu_nis ","Events");
    fGeneraldimupt_hl_nis = gHistogrammer->TH1DFactory("DIMuon","dimupt_hl_nis","#dimupt_{#mu}_hl_nis ",dimuptbins,dimuptlow,dimupthigh,"#dimupt_{#mu}_hl_nis ","Events");
    fGeneraleta = gHistogrammer->TH1DFactory("DIMuon","eta","#eta_{#mu} ",etabins,etalow,etahigh,"#eta_{#mu} ","Events");
    fGeneraleta_lu_is = gHistogrammer->TH1DFactory("DIMuon","eta_lu_is","#eta_{#mu}_lu_is ",etabins,etalow,etahigh,"#eta_{#mu}_lu_is ","Events");
    fGeneraleta_ll_is = gHistogrammer->TH1DFactory("DIMuon","eta_ll_is","#eta_{#mu}_ll_is ",etabins,etalow,etahigh,"#eta_{#mu}_ll_is ","Events");
    fGeneraleta_hu_is = gHistogrammer->TH1DFactory("DIMuon","eta_hu_is","#eta_{#mu}_hu_is ",etabins,etalow,etahigh,"#eta_{#mu}_hu_is ","Events");
    fGeneraleta_hl_is = gHistogrammer->TH1DFactory("DIMuon","eta_hl_is","#eta_{#mu}_hl_is ",etabins,etalow,etahigh,"#eta_{#mu}_hl_is ","Events");
    fGeneraleta_lu_nis = gHistogrammer->TH1DFactory("DIMuon","eta_lu_nis","#eta_{#mu}_lu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_lu_nis ","Events");
    fGeneraleta_ll_nis = gHistogrammer->TH1DFactory("DIMuon","eta_ll_nis","#eta_{#mu}_ll_nis ",etabins,etalow,etahigh,"#eta_{#mu}_ll_nis ","Events");
    fGeneraleta_hu_nis = gHistogrammer->TH1DFactory("DIMuon","eta_hu_nis","#eta_{#mu}_hu_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hu_nis ","Events");
    fGeneraleta_hl_nis = gHistogrammer->TH1DFactory("DIMuon","eta_hl_nis","#eta_{#mu}_hl_nis ",etabins,etalow,etahigh,"#eta_{#mu}_hl_nis ","Events");

    fGeneralCharge_Like   = gHistogrammer->TH1DFactory("DIMuon","mucharge_like","charge_{#mu}_ll ",chargebins,chargelow,chargehigh,"#mu charge","Events");

    fGeneralVertexOvNTracks    = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks","VertexOvNTracks",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}","Events");
    fGeneralVertexOvNTracks_is_lu = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_is_lu","lu VertexOvNTracks_is",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_is_lu","Events");
    fGeneralVertexOvNTracks_is_ll = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_is_ll","ll VertexOvNTracks_is",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_is_ll","Events");
    fGeneralVertexOvNTracks_is_hu = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_is_hu","hu VertexOvNTracks_is",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_is_hu","Events");
    fGeneralVertexOvNTracks_is_hl = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_is_hl","hl VertexOvNTracks_is",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_is_hl","Events");
    fGeneralVertexOvNTracks_nis_lu = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_nis_lu","lu VertexOvNTracks_nis",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_nis_lu","Events");
    fGeneralVertexOvNTracks_nis_ll = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_nis_ll","ll VertexOvNTracks_nis",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_nis_ll","Events");
    fGeneralVertexOvNTracks_nis_hu = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_nis_hu","hu VertexOvNTracks_nis",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_nis_hu","Events");
    fGeneralVertexOvNTracks_nis_hl = gHistogrammer->TH1DFactory("DIMuon","VertexOvNTracks_nis_hl","hl VertexOvNTracks_nis",vtxovntrkbins,vtxovntrklow,vtxovntrkhigh,"tracks^{vtx}/tracks^{total}_nis_hl","Events");

    fGeneralVtxMass    = gHistogrammer->TH1DFactory("DIMuon","VtxMass","VtxMass",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx} [GeV]","Events");
    fGeneralVtxMass_is_lu = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_lu","lu VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_lu [GeV]","Events");
    fGeneralVtxMass_is_ll = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_ll","ll VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_ll [GeV]","Events");
    fGeneralVtxMass_is_hu = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_hu","hu VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_hu [GeV]","Events");
    fGeneralVtxMass_is_hl = gHistogrammer->TH1DFactory("DIMuon","VtxMass_is_hl","hl VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_hl [GeV]","Events");
    fGeneralVtxMass_nis_lu = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_lu","lu VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_lu [GeV]","Events");
    fGeneralVtxMass_nis_ll = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_ll","ll VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_ll [GeV]","Events");
    fGeneralVtxMass_nis_hu = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_hu","hu VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_hu [GeV]","Events");
    fGeneralVtxMass_nis_hl = gHistogrammer->TH1DFactory("DIMuon","VtxMass_nis_hl","hl VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_hl [GeV]","Events");

    fGeneralChi2    = gHistogrammer->TH1DFactory("DIMuon","Chi2","Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneralChi2_is_lu = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_lu","lu Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_lu","Events");
    fGeneralChi2_is_ll = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_ll","ll Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_ll","Events");
    fGeneralChi2_is_hu = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_hu","hu Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_hu","Events");
    fGeneralChi2_is_hl = gHistogrammer->TH1DFactory("DIMuon","Chi2_is_hl","hl Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_hl","Events");
    fGeneralChi2_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_lu","lu Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_lu","Events");
    fGeneralChi2_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_ll","ll Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_ll","Events");
    fGeneralChi2_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_hu","hu Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_hu","Events");
    fGeneralChi2_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Chi2_nis_hl","hl Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_hl","Events");

    fGeneralNdof    = gHistogrammer->TH1DFactory("DIMuon","Ndof","Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneralNdof_is_lu = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_lu","lu Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_lu","Events");
    fGeneralNdof_is_ll = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_ll","ll Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_ll","Events");
    fGeneralNdof_is_hu = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_hu","hu Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_hu","Events");
    fGeneralNdof_is_hl = gHistogrammer->TH1DFactory("DIMuon","Ndof_is_hl","hl Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_hl","Events");
    fGeneralNdof_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_lu","lu Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_lu","Events");
    fGeneralNdof_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_ll","ll Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_ll","Events");
    fGeneralNdof_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_hu","hu Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_hu","Events");
    fGeneralNdof_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Ndof_nis_hl","hl Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_hl","Events");

    fGeneralChi2Ndof    = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof","Chi2Ndof",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof","Events");
    fGeneralChi2Ndof_is_lu = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_is_lu","lu Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_lu","Events");
    fGeneralChi2Ndof_is_ll = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_is_ll","ll Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_ll","Events");
    fGeneralChi2Ndof_is_hu = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_is_hu","hu Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_hu","Events");
    fGeneralChi2Ndof_is_hl = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_is_hl","hl Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_hl","Events");
    fGeneralChi2Ndof_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_nis_lu","lu Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_lu","Events");
    fGeneralChi2Ndof_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_nis_ll","ll Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_ll","Events");
    fGeneralChi2Ndof_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_nis_hu","hu Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_hu","Events");
    fGeneralChi2Ndof_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Chi2Ndof_nis_hl","hl Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_hl","Events");

    fGeneralMulti    = gHistogrammer->TH1DFactory("DIMuon","Multi","Multi",multibins,multilow,multihigh,"multi","Events");
    fGeneralMulti_is_lu = gHistogrammer->TH1DFactory("DIMuon","Multi_is_lu","lu Multi_is",multibins,multilow,multihigh,"multi_is_lu","Events");
    fGeneralMulti_is_ll = gHistogrammer->TH1DFactory("DIMuon","Multi_is_ll","ll Multi_is",multibins,multilow,multihigh,"multi_is_ll","Events");
    fGeneralMulti_is_hu = gHistogrammer->TH1DFactory("DIMuon","Multi_is_hu","hu Multi_is",multibins,multilow,multihigh,"multi_is_hu","Events");
    fGeneralMulti_is_hl = gHistogrammer->TH1DFactory("DIMuon","Multi_is_hl","hl Multi_is",multibins,multilow,multihigh,"multi_is_hl","Events");
    fGeneralMulti_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_lu","lu Multi_nis",multibins,multilow,multihigh,"multi_nis_lu","Events");
    fGeneralMulti_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_ll","ll Multi_nis",multibins,multilow,multihigh,"multi_nis_ll","Events");
    fGeneralMulti_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_hu","hu Multi_nis",multibins,multilow,multihigh,"multi_nis_hu","Events");
    fGeneralMulti_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Multi_nis_hl","hl Multi_nis",multibins,multilow,multihigh,"multi_nis_hl","Events");

    fGeneral_mvtx2_VtxMass    = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass","VtxMass",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx} [GeV]","Events");
    fGeneral_mvtx2_VtxMass_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_is_lu","lu VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_lu [GeV]","Events");
    fGeneral_mvtx2_VtxMass_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_is_ll","ll VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_ll [GeV]","Events");
    fGeneral_mvtx2_VtxMass_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_is_hu","hu VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_hu [GeV]","Events");
    fGeneral_mvtx2_VtxMass_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_is_hl","hl VtxMass_is",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_is_hl [GeV]","Events");
    fGeneral_mvtx2_VtxMass_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_nis_lu","lu VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_lu [GeV]","Events");
    fGeneral_mvtx2_VtxMass_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_nis_ll","ll VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_ll [GeV]","Events");
    fGeneral_mvtx2_VtxMass_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_nis_hu","hu VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_hu [GeV]","Events");
    fGeneral_mvtx2_VtxMass_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_VtxMass_nis_hl","hl VtxMass_nis",vtxmassbins,vtxmasslow,vtxmasshigh,"m_{vtx}_nis_hl [GeV]","Events");

    fGeneral_mvtx2_Chi2    = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2","Chi2",chi2bins,chi2low,chi2high,"chi2","Events");
    fGeneral_mvtx2_Chi2_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_is_lu","lu Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_lu","Events");
    fGeneral_mvtx2_Chi2_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_is_ll","ll Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_ll","Events");
    fGeneral_mvtx2_Chi2_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_is_hu","hu Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_hu","Events");
    fGeneral_mvtx2_Chi2_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_is_hl","hl Chi2_is",chi2bins,chi2low,chi2high,"chi2_is_hl","Events");
    fGeneral_mvtx2_Chi2_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_nis_lu","lu Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_lu","Events");
    fGeneral_mvtx2_Chi2_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_nis_ll","ll Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_ll","Events");
    fGeneral_mvtx2_Chi2_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_nis_hu","hu Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_hu","Events");
    fGeneral_mvtx2_Chi2_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2_nis_hl","hl Chi2_nis",chi2bins,chi2low,chi2high,"chi2_nis_hl","Events");

    fGeneral_mvtx2_Ndof    = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof","Ndof",ndofbins,ndoflow,ndofhigh,"ndof","Events");
    fGeneral_mvtx2_Ndof_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_is_lu","lu Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_lu","Events");
    fGeneral_mvtx2_Ndof_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_is_ll","ll Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_ll","Events");
    fGeneral_mvtx2_Ndof_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_is_hu","hu Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_hu","Events");
    fGeneral_mvtx2_Ndof_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_is_hl","hl Ndof_is",ndofbins,ndoflow,ndofhigh,"ndof_is_hl","Events");
    fGeneral_mvtx2_Ndof_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_nis_lu","lu Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_lu","Events");
    fGeneral_mvtx2_Ndof_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_nis_ll","ll Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_ll","Events");
    fGeneral_mvtx2_Ndof_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_nis_hu","hu Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_hu","Events");
    fGeneral_mvtx2_Ndof_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Ndof_nis_hl","hl Ndof_nis",ndofbins,ndoflow,ndofhigh,"ndof_nis_hl","Events");

    fGeneral_mvtx2_Chi2Ndof    = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof","Chi2Ndof",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof","Events");
    fGeneral_mvtx2_Chi2Ndof_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_is_lu","lu Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_lu","Events");
    fGeneral_mvtx2_Chi2Ndof_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_is_ll","ll Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_ll","Events");
    fGeneral_mvtx2_Chi2Ndof_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_is_hu","hu Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_hu","Events");
    fGeneral_mvtx2_Chi2Ndof_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_is_hl","hl Chi2Ndof_is",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_is_hl","Events");
    fGeneral_mvtx2_Chi2Ndof_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_nis_lu","lu Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_lu","Events");
    fGeneral_mvtx2_Chi2Ndof_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_nis_ll","ll Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_ll","Events");
    fGeneral_mvtx2_Chi2Ndof_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_nis_hu","hu Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_hu","Events");
    fGeneral_mvtx2_Chi2Ndof_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Chi2Ndof_nis_hl","hl Chi2Ndof_nis",chi2ndofbins,chi2ndoflow,chi2ndofhigh,"chi2ndof_nis_hl","Events");

    fGeneral_mvtx2_Multi    = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi","Multi",multibins,multilow,multihigh,"multi","Events");
    fGeneral_mvtx2_Multi_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_is_lu","lu Multi_is",multibins,multilow,multihigh,"multi_is_lu","Events");
    fGeneral_mvtx2_Multi_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_is_ll","ll Multi_is",multibins,multilow,multihigh,"multi_is_ll","Events");
    fGeneral_mvtx2_Multi_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_is_hu","hu Multi_is",multibins,multilow,multihigh,"multi_is_hu","Events");
    fGeneral_mvtx2_Multi_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_is_hl","hl Multi_is",multibins,multilow,multihigh,"multi_is_hl","Events");
    fGeneral_mvtx2_Multi_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_nis_lu","lu Multi_nis",multibins,multilow,multihigh,"multi_nis_lu","Events");
    fGeneral_mvtx2_Multi_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_nis_ll","ll Multi_nis",multibins,multilow,multihigh,"multi_nis_ll","Events");
    fGeneral_mvtx2_Multi_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_nis_hu","hu Multi_nis",multibins,multilow,multihigh,"multi_nis_hu","Events");
    fGeneral_mvtx2_Multi_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_Multi_nis_hl","hl Multi_nis",multibins,multilow,multihigh,"multi_nis_hl","Events");

    fGeneralNrsecvtx    = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx","Nrsecvtx",nrsecbins,nrseclow,nrsechigh,"nrsecvtx","Events");
    fGeneralNrsecvtx_is_lu = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_lu","lu Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_lu","Events");
    fGeneralNrsecvtx_is_ll = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_ll","ll Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_ll","Events");
    fGeneralNrsecvtx_is_hu = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_hu","hu Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_hu","Events");
    fGeneralNrsecvtx_is_hl = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_is_hl","hl Nrsecvtx_is",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_is_hl","Events");
    fGeneralNrsecvtx_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_lu","lu Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_lu","Events");
    fGeneralNrsecvtx_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_ll","ll Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_ll","Events");
    fGeneralNrsecvtx_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_hu","hu Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_hu","Events");
    fGeneralNrsecvtx_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Nrsecvtx_nis_hl","hl Nrsecvtx_nis",nrsecbins,nrseclow,nrsechigh,"nrsecvtx_nis_hl","Events");

    fGeneralMunphi    = gHistogrammer->TH1DFactory("DIMuon","Munphi","Munphi",munphibins,munphilow,munphihigh,"# Munphi","Events");
    fGeneralMunphi_is_lu = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_lu","lu Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_lu","Events");
    fGeneralMunphi_is_ll = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_ll","ll Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_ll","Events");
    fGeneralMunphi_is_hu = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_hu","hu Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_hu","Events");
    fGeneralMunphi_is_hl = gHistogrammer->TH1DFactory("DIMuon","Munphi_is_hl","hl Munphi_is",munphibins,munphilow,munphihigh,"# Munphi_is_hl","Events");
    fGeneralMunphi_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_lu","lu Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_lu","Events");
    fGeneralMunphi_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_ll","ll Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_ll","Events");
    fGeneralMunphi_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_hu","hu Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_hu","Events");
    fGeneralMunphi_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Munphi_nis_hl","hl Munphi_nis",munphibins,munphilow,munphihigh,"# Munphi_nis_hl","Events");

    fGeneralMundof    = gHistogrammer->TH1DFactory("DIMuon","Mundof","Mundof",mundofbins,mundoflow,mundofhigh,"Mundof","Events");
    fGeneralMundof_is_lu = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_lu","lu Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_lu","Events");
    fGeneralMundof_is_ll = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_ll","ll Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_ll","Events");
    fGeneralMundof_is_hu = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_hu","hu Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_hu","Events");
    fGeneralMundof_is_hl = gHistogrammer->TH1DFactory("DIMuon","Mundof_is_hl","hl Mundof_is",mundofbins,mundoflow,mundofhigh,"Mundof_is_hl","Events");
    fGeneralMundof_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_lu","lu Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_lu","Events");
    fGeneralMundof_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_ll","ll Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_ll","Events");
    fGeneralMundof_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_hu","hu Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_hu","Events");
    fGeneralMundof_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Mundof_nis_hl","hl Mundof_nis",mundofbins,mundoflow,mundofhigh,"Mundof_nis_hl","Events");

    fGeneralMupmat    = gHistogrammer->TH1DFactory("DIMuon","Mupmat","Mupmat",mupmatbins,mupmatlow,mupmathigh,"MuPMat","Events");
    fGeneralMupmat_is_lu = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_lu","lu Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_lu","Events");
    fGeneralMupmat_is_ll = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_ll","ll Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_ll","Events");
    fGeneralMupmat_is_hu = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_hu","hu Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_hu","Events");
    fGeneralMupmat_is_hl = gHistogrammer->TH1DFactory("DIMuon","Mupmat_is_hl","hl Mupmat_is",mupmatbins,mupmatlow,mupmathigh,"MuPMat_is_hl","Events");
    fGeneralMupmat_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_lu","lu Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_lu","Events");
    fGeneralMupmat_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_ll","ll Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_ll","Events");
    fGeneralMupmat_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_hu","hu Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_hu","Events");
    fGeneralMupmat_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Mupmat_nis_hl","hl Mupmat_nis",mupmatbins,mupmatlow,mupmathigh,"MuPMat_nis_hl","Events");

    fGeneralMPMatchID    = gHistogrammer->TH1DFactory("DIMuon","MPMatchID","MPMatchID",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID","Events");
    fGeneralMPMatchID_is_lu = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_lu","lu MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_lu","Events");
    fGeneralMPMatchID_is_ll = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_ll","ll MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_ll","Events");
    fGeneralMPMatchID_is_hu = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_hu","hu MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_hu","Events");
    fGeneralMPMatchID_is_hl = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_is_hl","hl MPMatchID_is",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_is_hl","Events");
    fGeneralMPMatchID_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_lu","lu MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_lu","Events");
    fGeneralMPMatchID_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_ll","ll MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_ll","Events");
    fGeneralMPMatchID_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_hu","hu MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_hu","Events");
    fGeneralMPMatchID_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MPMatchID_nis_hl","hl MPMatchID_nis",mpmatchidbins,mpmatchidlow,mpmatchidhigh,"MPMatchID_nis_hl","Events");

    fGeneralMuMvID    = gHistogrammer->TH1DFactory("DIMuon","MuMvID","MuMvID",mumvidbins,mumvidlow,mumvidhigh,"MuMvID","Events");
    fGeneralMuMvID_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_lu","lu MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_lu","Events");
    fGeneralMuMvID_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_ll","ll MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_ll","Events");
    fGeneralMuMvID_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_hu","hu MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_hu","Events");
    fGeneralMuMvID_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuMvID_is_hl","hl MuMvID_is",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_is_hl","Events");
    fGeneralMuMvID_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_lu","lu MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_lu","Events");
    fGeneralMuMvID_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_ll","ll MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_ll","Events");
    fGeneralMuMvID_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_hu","hu MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_hu","Events");
    fGeneralMuMvID_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuMvID_nis_hl","hl MuMvID_nis",mumvidbins,mumvidlow,mumvidhigh,"MuMvID_nis_hl","Events");

    fGeneralMuMufoID    = gHistogrammer->TH1DFactory("DIMuon","MuMufoID","MuMufoID",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID","Events");
    fGeneralMuMufoID_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_lu","lu MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_lu","Events");
    fGeneralMuMufoID_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_ll","ll MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_ll","Events");
    fGeneralMuMufoID_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_hu","hu MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_hu","Events");
    fGeneralMuMufoID_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_is_hl","hl MuMufoID_is",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_is_hl","Events");
    fGeneralMuMufoID_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_lu","lu MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_lu","Events");
    fGeneralMuMufoID_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_ll","ll MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_ll","Events");
    fGeneralMuMufoID_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_hu","hu MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_hu","Events");
    fGeneralMuMufoID_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuMufoID_nis_hl","hl MuMufoID_nis",mumufoidbins,mumufoidlow,mumufoidhigh,"MuMufoID_nis_hl","Events");

    fGeneralMuz    = gHistogrammer->TH1DFactory("DIMuon","Muz","Muz",muzbins,muzlow,muzhigh,"Muz","Events");
    fGeneralMuz_is_lu = gHistogrammer->TH1DFactory("DIMuon","Muz_is_lu","lu Muz_is",muzbins,muzlow,muzhigh,"Muz_is_lu","Events");
    fGeneralMuz_is_ll = gHistogrammer->TH1DFactory("DIMuon","Muz_is_ll","ll Muz_is",muzbins,muzlow,muzhigh,"Muz_is_ll","Events");
    fGeneralMuz_is_hu = gHistogrammer->TH1DFactory("DIMuon","Muz_is_hu","hu Muz_is",muzbins,muzlow,muzhigh,"Muz_is_hu","Events");
    fGeneralMuz_is_hl = gHistogrammer->TH1DFactory("DIMuon","Muz_is_hl","hl Muz_is",muzbins,muzlow,muzhigh,"Muz_is_hl","Events");
    fGeneralMuz_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_lu","lu Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_lu","Events");
    fGeneralMuz_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_ll","ll Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_ll","Events");
    fGeneralMuz_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_hu","hu Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_hu","Events");
    fGeneralMuz_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Muz_nis_hl","hl Muz_nis",muzbins,muzlow,muzhigh,"Muz_nis_hl","Events");

    fGeneralMuBacMatID    = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID","MuBacMatID",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID","Events");
    fGeneralMuBacMatID_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_lu","lu MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_lu","Events");
    fGeneralMuBacMatID_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_ll","ll MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_ll","Events");
    fGeneralMuBacMatID_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_hu","hu MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_hu","Events");
    fGeneralMuBacMatID_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_is_hl","hl MuBacMatID_is",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_is_hl","Events");
    fGeneralMuBacMatID_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_lu","lu MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_lu","Events");
    fGeneralMuBacMatID_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_ll","ll MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_ll","Events");
    fGeneralMuBacMatID_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_hu","hu MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_hu","Events");
    fGeneralMuBacMatID_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuBacMatID_nis_hl","hl MuBacMatID_nis",mubacmatidbins,mubacmatidlow,mubacmatidhigh,"MuBacMatID_nis_hl","Events");

    fGeneralNBacMat    = gHistogrammer->TH1DFactory("DIMuon","NBacMat","NBacMat",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat","Events");
    fGeneralNBacMat_is_lu = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_lu","lu NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_lu","Events");
    fGeneralNBacMat_is_ll = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_ll","ll NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_ll","Events");
    fGeneralNBacMat_is_hu = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_hu","hu NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_hu","Events");
    fGeneralNBacMat_is_hl = gHistogrammer->TH1DFactory("DIMuon","NBacMat_is_hl","hl NBacMat_is",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_is_hl","Events");
    fGeneralNBacMat_nis_lu = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_lu","lu NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_lu","Events");
    fGeneralNBacMat_nis_ll = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_ll","ll NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_ll","Events");
    fGeneralNBacMat_nis_hu = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_hu","hu NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_hu","Events");
    fGeneralNBacMat_nis_hl = gHistogrammer->TH1DFactory("DIMuon","NBacMat_nis_hl","hl NBacMat_nis",nbacmatbins,nbacmatlow,nbacmathigh,"NBacMat_nis_hl","Events");

    fGeneralBacMat_VCID    = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID","BacMat_VCID",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID","Events");
    fGeneralBacMat_VCID_is_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_lu","lu BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_lu","Events");
    fGeneralBacMat_VCID_is_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_ll","ll BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_ll","Events");
    fGeneralBacMat_VCID_is_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_hu","hu BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_hu","Events");
    fGeneralBacMat_VCID_is_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_is_hl","hl BacMat_VCID_is",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_is_hl","Events");
    fGeneralBacMat_VCID_nis_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_lu","lu BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_lu","Events");
    fGeneralBacMat_VCID_nis_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_ll","ll BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_ll","Events");
    fGeneralBacMat_VCID_nis_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_hu","hu BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_hu","Events");
    fGeneralBacMat_VCID_nis_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_VCID_nis_hl","hl BacMat_VCID_nis",bacmatidvcbins,bacmatidvclow,bacmatidvchigh,"BacMat_VCID_nis_hl","Events");

    fGeneralBacMat_MuBacID    = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID","BacMat_MuBacID",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID","Events");
    fGeneralBacMat_MuBacID_is_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_lu","lu BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_lu","Events");
    fGeneralBacMat_MuBacID_is_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_ll","ll BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_ll","Events");
    fGeneralBacMat_MuBacID_is_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_hu","hu BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_hu","Events");
    fGeneralBacMat_MuBacID_is_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_is_hl","hl BacMat_MuBacID_is",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_is_hl","Events");
    fGeneralBacMat_MuBacID_nis_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_lu","lu BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_lu","Events");
    fGeneralBacMat_MuBacID_nis_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_ll","ll BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_ll","Events");
    fGeneralBacMat_MuBacID_nis_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_hu","hu BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_hu","Events");
    fGeneralBacMat_MuBacID_nis_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_MuBacID_nis_hl","hl BacMat_MuBacID_nis",bacmatidmubacbins,bacmatidmubaclow,bacmatidmubachigh,"BacMat_MuBacID_nis_hl","Events");

    fGeneralBacMat_Istop    = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop","BacMat_Istop",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop","Events");
    fGeneralBacMat_Istop_is_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_lu","lu BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_lu","Events");
    fGeneralBacMat_Istop_is_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_ll","ll BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_ll","Events");
    fGeneralBacMat_Istop_is_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_hu","hu BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_hu","Events");
    fGeneralBacMat_Istop_is_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_is_hl","hl BacMat_Istop_is",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_is_hl","Events");
    fGeneralBacMat_Istop_nis_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_lu","lu BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_lu","Events");
    fGeneralBacMat_Istop_nis_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_ll","ll BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_ll","Events");
    fGeneralBacMat_Istop_nis_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_hu","hu BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_hu","Events");
    fGeneralBacMat_Istop_nis_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_Istop_nis_hl","hl BacMat_Istop_nis",bacmatistopbins,bacmatistoplow,bacmatistophigh,"BacMat_Istop_nis_hl","Events");

    fGeneralBacMat_Error    = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error","BacMat_Error",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error","Events");
    fGeneralBacMat_Error_is_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_lu","lu BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_lu","Events");
    fGeneralBacMat_Error_is_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_ll","ll BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_ll","Events");
    fGeneralBacMat_Error_is_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_hu","hu BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_hu","Events");
    fGeneralBacMat_Error_is_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_is_hl","hl BacMat_Error_is",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_is_hl","Events");
    fGeneralBacMat_Error_nis_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_lu","lu BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_lu","Events");
    fGeneralBacMat_Error_nis_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_ll","ll BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_ll","Events");
    fGeneralBacMat_Error_nis_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_hu","hu BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_hu","Events");
    fGeneralBacMat_Error_nis_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_Error_nis_hl","hl BacMat_Error_nis",bacmaterrorbins,bacmaterrorlow,bacmaterrorhigh,"BacMat_Error_nis_hl","Events");

    fGeneralBacMat_Readout    = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout","BacMat_Readout",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout","Events");
    fGeneralBacMat_Readout_is_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_lu","lu BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_lu","Events");
    fGeneralBacMat_Readout_is_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_ll","ll BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_ll","Events");
    fGeneralBacMat_Readout_is_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_hu","hu BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_hu","Events");
    fGeneralBacMat_Readout_is_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_is_hl","hl BacMat_Readout_is",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_is_hl","Events");
    fGeneralBacMat_Readout_nis_lu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_lu","lu BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_lu","Events");
    fGeneralBacMat_Readout_nis_ll = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_ll","ll BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_ll","Events");
    fGeneralBacMat_Readout_nis_hu = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_hu","hu BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_hu","Events");
    fGeneralBacMat_Readout_nis_hl = gHistogrammer->TH1DFactory("DIMuon","BacMat_Readout_nis_hl","hl BacMat_Readout_nis",bacmatreadoutbins,bacmatreadoutlow,bacmatreadouthigh,"BacMat_Readout_nis_hl","Events");

    fGeneralImpact2D    = gHistogrammer->TH1DFactory("DIMuon","Impact2D","Impact2D",impactbins,impactlow,impacthigh,"#2D_IP [cm]","Events");
    fGeneralImpact2D_is_lu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_lu","lu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_lu [cm]","Events");
    fGeneralImpact2D_is_ll = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_ll","ll Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_ll [cm]","Events");
    fGeneralImpact2D_is_hu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_hu","hu Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_hu [cm]","Events");
    fGeneralImpact2D_is_hl = gHistogrammer->TH1DFactory("DIMuon","Impact2D_is_hl","hl Impact2D_is",impactbins,impactlow,impacthigh,"#2D_IP_is_hl [cm]","Events");
    fGeneralImpact2D_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_lu","lu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_lu [cm]","Events");
    fGeneralImpact2D_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_ll","ll Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_ll [cm]","Events");
    fGeneralImpact2D_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_hu","hu Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_hu [cm]","Events");
    fGeneralImpact2D_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Impact2D_nis_hl","hl Impact2D_nis",impactbins,impactlow,impacthigh,"#2D_IP_nis_hl [cm]","Events");

    fGeneralImpact2D_Sign    = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign","Impact2D_Sign",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign","Events");
    fGeneralImpact2D_Sign_is_lu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_lu","lu Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_lu","Events");
    fGeneralImpact2D_Sign_is_ll = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_ll","ll Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_ll","Events");
    fGeneralImpact2D_Sign_is_hu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_hu","hu Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_hu","Events");
    fGeneralImpact2D_Sign_is_hl = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_is_hl","hl Impact2D_Sign_is",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_is_hl","Events");
    fGeneralImpact2D_Sign_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_lu","lu Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_lu","Events");
    fGeneralImpact2D_Sign_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_ll","ll Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_ll","Events");
    fGeneralImpact2D_Sign_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_hu","hu Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_hu","Events");
    fGeneralImpact2D_Sign_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Impact2D_Sign_nis_hl","hl Impact2D_Sign_nis",impactsignbins,impactsignlow,impactsignhigh,"#2D_IP_Sign_nis_hl","Events");

    fGeneralDL2 = gHistogrammer->TH1DFactory("DIMuon","DL2","DL2",dl2bins,dl2low,dl2high,"Decay length","Events");
    fGeneralDL2_is_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_is_lu","lu DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_lu","Events");
    fGeneralDL2_is_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_is_ll","ll DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_ll","Events");
    fGeneralDL2_is_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_is_hu","hu DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_hu","Events");
    fGeneralDL2_is_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_is_hl","hl DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_hl","Events");
    fGeneralDL2_nis_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_lu","lu DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_lu","Events");
    fGeneralDL2_nis_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_ll","ll DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_ll","Events");
    fGeneralDL2_nis_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_hu","hu DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_hu","Events");
    fGeneralDL2_nis_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_nis_hl","hl DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_hl","Events");

    fGeneralDL2_err = gHistogrammer->TH1DFactory("DIMuon","DL2_err","DL2_err",dl2errbins,dl2errlow,dl2errhigh,"Decay length error","Events");
    fGeneralDL2_err_is_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_err_is_lu","lu DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_lu","Events");
    fGeneralDL2_err_is_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_err_is_ll","ll DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_ll","Events");
    fGeneralDL2_err_is_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_err_is_hu","hu DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_hu","Events");
    fGeneralDL2_err_is_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_err_is_hl","hl DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_hl","Events");
    fGeneralDL2_err_nis_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_err_nis_lu","lu DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_lu","Events");
    fGeneralDL2_err_nis_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_err_nis_ll","ll DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_ll","Events");
    fGeneralDL2_err_nis_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_err_nis_hu","hu DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_hu","Events");
    fGeneralDL2_err_nis_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_err_nis_hl","hl DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_hl","Events");

    fGeneralDL2_Sign = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign","DL2_Sign",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance","Events");
    fGeneralDL2_Sign_is_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_lu","lu DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_lu","Events");
    fGeneralDL2_Sign_is_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_ll","ll DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_ll","Events");
    fGeneralDL2_Sign_is_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_hu","hu DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_hu","Events");
    fGeneralDL2_Sign_is_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_is_hl","hl DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_hl","Events");
    fGeneralDL2_Sign_nis_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_lu","lu DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_lu","Events");
    fGeneralDL2_Sign_nis_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_ll","ll DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_ll","Events");
    fGeneralDL2_Sign_nis_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_hu","hu DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_hu","Events");
    fGeneralDL2_Sign_nis_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_nis_hl","hl DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_hl","Events");

    fGeneralDL2_Sign_Mirrp = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp","DL2_Sign_Mirrp",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance","Events");
    fGeneralDL2_Sign_Mirrp_is_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_lu","lu DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_lu","Events");
    fGeneralDL2_Sign_Mirrp_is_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_ll","ll DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_ll","Events");
    fGeneralDL2_Sign_Mirrp_is_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_hu","hu DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_hu","Events");
    fGeneralDL2_Sign_Mirrp_is_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_is_hl","hl DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_hl","Events");
    fGeneralDL2_Sign_Mirrp_nis_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_lu","lu DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_lu","Events");
    fGeneralDL2_Sign_Mirrp_nis_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_ll","ll DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_ll","Events");
    fGeneralDL2_Sign_Mirrp_nis_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_hu","hu DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_hu","Events");
    fGeneralDL2_Sign_Mirrp_nis_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrp_nis_hl","hl DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_hl","Events");

    fGeneralDL2_Sign_Mirrm = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm","DL2_Sign_Mirrm",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance","Events");
    fGeneralDL2_Sign_Mirrm_is_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_lu","lu DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_lu","Events");
    fGeneralDL2_Sign_Mirrm_is_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_ll","ll DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_ll","Events");
    fGeneralDL2_Sign_Mirrm_is_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_hu","hu DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_hu","Events");
    fGeneralDL2_Sign_Mirrm_is_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_is_hl","hl DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_hl","Events");
    fGeneralDL2_Sign_Mirrm_nis_lu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_lu","lu DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_lu","Events");
    fGeneralDL2_Sign_Mirrm_nis_ll = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_ll","ll DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_ll","Events");
    fGeneralDL2_Sign_Mirrm_nis_hu = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_hu","hu DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_hu","Events");
    fGeneralDL2_Sign_Mirrm_nis_hl = gHistogrammer->TH1DFactory("DIMuon","DL2_Sign_Mirrm_nis_hl","hl DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_hl","Events");

    fGeneral_mvtx2_DL2 = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2","DL2",dl2bins,dl2low,dl2high,"Decay length","Events");
    fGeneral_mvtx2_DL2_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_is_lu","lu DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_lu","Events");
    fGeneral_mvtx2_DL2_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_is_ll","ll DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_ll","Events");
    fGeneral_mvtx2_DL2_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_is_hu","hu DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_hu","Events");
    fGeneral_mvtx2_DL2_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_is_hl","hl DL2_is",dl2bins,dl2low,dl2high,"Decay length_is_hl","Events");
    fGeneral_mvtx2_DL2_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_nis_lu","lu DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_lu","Events");
    fGeneral_mvtx2_DL2_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_nis_ll","ll DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_ll","Events");
    fGeneral_mvtx2_DL2_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_nis_hu","hu DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_hu","Events");
    fGeneral_mvtx2_DL2_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_nis_hl","hl DL2_nis",dl2bins,dl2low,dl2high,"Decay length_nis_hl","Events");

    fGeneral_mvtx2_DL2_err = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err","DL2_err",dl2errbins,dl2errlow,dl2errhigh,"Decay length error","Events");
    fGeneral_mvtx2_DL2_err_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_is_lu","lu DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_lu","Events");
    fGeneral_mvtx2_DL2_err_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_is_ll","ll DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_ll","Events");
    fGeneral_mvtx2_DL2_err_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_is_hu","hu DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_hu","Events");
    fGeneral_mvtx2_DL2_err_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_is_hl","hl DL2_err_is",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_is_hl","Events");
    fGeneral_mvtx2_DL2_err_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_nis_lu","lu DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_lu","Events");
    fGeneral_mvtx2_DL2_err_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_nis_ll","ll DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_ll","Events");
    fGeneral_mvtx2_DL2_err_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_nis_hu","hu DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_hu","Events");
    fGeneral_mvtx2_DL2_err_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_err_nis_hl","hl DL2_err_nis",dl2errbins,dl2errlow,dl2errhigh,"Decay length_error_nis_hl","Events");

    fGeneral_mvtx2_DL2_Sign = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign","DL2_Sign",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance","Events");
    fGeneral_mvtx2_DL2_Sign_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_is_lu","lu DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_lu","Events");
    fGeneral_mvtx2_DL2_Sign_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_is_ll","ll DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_ll","Events");
    fGeneral_mvtx2_DL2_Sign_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_is_hu","hu DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_hu","Events");
    fGeneral_mvtx2_DL2_Sign_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_is_hl","hl DL2_Sign_is",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_is_hl","Events");
    fGeneral_mvtx2_DL2_Sign_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_nis_lu","lu DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_lu","Events");
    fGeneral_mvtx2_DL2_Sign_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_nis_ll","ll DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_ll","Events");
    fGeneral_mvtx2_DL2_Sign_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_nis_hu","hu DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_hu","Events");
    fGeneral_mvtx2_DL2_Sign_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_nis_hl","hl DL2_Sign_nis",dl2signbins,dl2signlow,dl2signhigh,"Decay length significance_nis_hl","Events");

    fGeneral_mvtx2_DL2_Sign_Mirrp = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp","DL2_Sign_Mirrp",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_is_lu","lu DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_lu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_is_ll","ll DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_ll","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_is_hu","hu DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_hu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_is_hl","hl DL2_Sign_Mirrp_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_is_hl","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_nis_lu","lu DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_lu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_nis_ll","ll DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_ll","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_nis_hu","hu DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_hu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrp_nis_hl","hl DL2_Sign_Mirrp_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"P Mirrored significance_nis_hl","Events");

    fGeneral_mvtx2_DL2_Sign_Mirrm = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm","DL2_Sign_Mirrm",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_is_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_is_lu","lu DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_lu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_is_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_is_ll","ll DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_ll","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_is_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_is_hu","hu DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_hu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_is_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_is_hl","hl DL2_Sign_Mirrm_is",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_is_hl","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_nis_lu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_nis_lu","lu DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_lu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_nis_ll = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_nis_ll","ll DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_ll","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hu = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_nis_hu","hu DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_hu","Events");
    fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hl = gHistogrammer->TH1DFactory("DIMuon","mvtx2_DL2_Sign_Mirrm_nis_hl","hl DL2_Sign_Mirrm_nis",dl2mirrbins,dl2mirrlow,dl2mirrhigh,"M Mirrored significance_nis_hl","Events");

    fGeneralMuJetDeltaR = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR","MuJetDeltaR",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}","Events");
    fGeneralMuJetDeltaR_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_lu","lu MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_lu","Events");
    fGeneralMuJetDeltaR_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_ll","ll MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_ll","Events");
    fGeneralMuJetDeltaR_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_hu","hu MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_hu","Events");
    fGeneralMuJetDeltaR_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_is_hl","hl MuJetDeltaR_is",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_is_hl","Events");
    fGeneralMuJetDeltaR_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_lu","lu MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_lu","Events");
    fGeneralMuJetDeltaR_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_ll","ll MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_ll","Events");
    fGeneralMuJetDeltaR_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_hu","hu MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_hu","Events");
    fGeneralMuJetDeltaR_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetDeltaR_nis_hl","hl MuJetDeltaR_nis",mujetdeltarbins,mujetdeltarlow,mujetdeltarhigh,"#Delta R^{Jet}_{#mu}_nis_hl","Events");

    fGeneralMuJetPt = gHistogrammer->TH1DFactory("DIMuon","MuJetPt","MuJetPt",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet} [GeV]","Events");
    fGeneralMuJetPt_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_lu","lu MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_lu [GeV]","Events");
    fGeneralMuJetPt_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_ll","ll MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_ll [GeV]","Events");
    fGeneralMuJetPt_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_hu","hu MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_hu [GeV]","Events");
    fGeneralMuJetPt_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_is_hl","hl MuJetPt_is",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_is_hl [GeV]","Events");
    fGeneralMuJetPt_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_lu","lu MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_lu [GeV]","Events");
    fGeneralMuJetPt_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_ll","ll MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_ll [GeV]","Events");
    fGeneralMuJetPt_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_hu","hu MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_hu [GeV]","Events");
    fGeneralMuJetPt_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetPt_nis_hl","hl MuJetPt_nis",mujetptbins,mujetptlow,mujetpthigh,"p^{#mu}_{T,Jet}_nis_hl [GeV]","Events");

    fGeneralMuJetEt = gHistogrammer->TH1DFactory("DIMuon","MuJetEt","MuJetEt",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet} [GeV]","Events");
    fGeneralMuJetEt_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_lu","lu MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_lu [GeV]","Events");
    fGeneralMuJetEt_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_ll","ll MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_ll [GeV]","Events");
    fGeneralMuJetEt_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_hu","hu MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_hu [GeV]","Events");
    fGeneralMuJetEt_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_is_hl","hl MuJetEt_is",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_is_hl [GeV]","Events");
    fGeneralMuJetEt_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_lu","lu MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_lu [GeV]","Events");
    fGeneralMuJetEt_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_ll","ll MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_ll [GeV]","Events");
    fGeneralMuJetEt_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_hu","hu MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_hu [GeV]","Events");
    fGeneralMuJetEt_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetEt_nis_hl","hl MuJetEt_nis",mujetetbins,mujetetlow,mujetethigh,"E^{#mu}_{T,Jet}_nis_hl [GeV]","Events");

    fGeneralMuJetEta = gHistogrammer->TH1DFactory("DIMuon","MuJetEta","MuJetEta",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}","Events");
    fGeneralMuJetEta_is_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_lu","lu MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_lu","Events");
    fGeneralMuJetEta_is_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_ll","ll MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_ll","Events");
    fGeneralMuJetEta_is_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_hu","hu MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_hu","Events");
    fGeneralMuJetEta_is_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_is_hl","hl MuJetEta_is",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_is_hl","Events");
    fGeneralMuJetEta_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_lu","lu MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_lu","Events");
    fGeneralMuJetEta_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_ll","ll MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_ll","Events");
    fGeneralMuJetEta_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_hu","hu MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_hu","Events");
    fGeneralMuJetEta_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MuJetEta_nis_hl","hl MuJetEta_nis",mujetetabins,mujetetalow,mujetetahigh,"#eta_{#mu}^{Jet}_nis_hl","Events");

    fGeneralMassJet   = gHistogrammer->TH1DFactory("DIMuon","MassJet","MassJet",massjetbins,massjetlow,massjethigh,"#MassJet [GeV]","Events");
    fGeneralMassJet_is_lu = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_lu","lu MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_lu [GeV]","Events");
    fGeneralMassJet_is_ll = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_ll","ll MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_ll [GeV]","Events");
    fGeneralMassJet_is_hu = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_hu","hu MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_hu [GeV]","Events");
    fGeneralMassJet_is_hl = gHistogrammer->TH1DFactory("DIMuon","MassJet_is_hl","hl MassJet_is",massjetbins,massjetlow,massjethigh,"#MassJet_is_hl [GeV]","Events");
    fGeneralMassJet_nis_lu = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_lu","lu MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_lu [GeV]","Events");
    fGeneralMassJet_nis_ll = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_ll","ll MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_ll [GeV]","Events");
    fGeneralMassJet_nis_hu = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_hu","hu MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_hu [GeV]","Events");
    fGeneralMassJet_nis_hl = gHistogrammer->TH1DFactory("DIMuon","MassJet_nis_hl","hl MassJet_nis",massjetbins,massjetlow,massjethigh,"#MassJet_nis_hl [GeV]","Events");

    fGeneralNJets   = gHistogrammer->TH1DFactory("DIMuon","NJets","NJets",njetbins,njetlow,njethigh,"#NJets","Events");
    fGeneralNJets_is_lu = gHistogrammer->TH1DFactory("DIMuon","NJets_is_lu","lu NJets_is",njetbins,njetlow,njethigh,"#NJets_is_lu","Events");
    fGeneralNJets_is_ll = gHistogrammer->TH1DFactory("DIMuon","NJets_is_ll","ll NJets_is",njetbins,njetlow,njethigh,"#NJets_is_ll","Events");
    fGeneralNJets_is_hu = gHistogrammer->TH1DFactory("DIMuon","NJets_is_hu","hu NJets_is",njetbins,njetlow,njethigh,"#NJets_is_hu","Events");
    fGeneralNJets_is_hl = gHistogrammer->TH1DFactory("DIMuon","NJets_is_hl","hl NJets_is",njetbins,njetlow,njethigh,"#NJets_is_hl","Events");
    fGeneralNJets_nis_lu = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_lu","lu NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_lu","Events");
    fGeneralNJets_nis_ll = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_ll","ll NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_ll","Events");
    fGeneralNJets_nis_hu = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_hu","hu NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_hu","Events");
    fGeneralNJets_nis_hl = gHistogrammer->TH1DFactory("DIMuon","NJets_nis_hl","hl NJets_nis",njetbins,njetlow,njethigh,"#NJets_nis_hl","Events");

    fGeneralphi = gHistogrammer->TH1DFactory("DIMuon","phi","#phi_{#mu} ",phibins,philow,phihigh,"#phi_{#mu} ","Events");
    fGeneralphi_lu_is = gHistogrammer->TH1DFactory("DIMuon","phi_lu_is","#phi_{#mu}_lu_is ",phibins,philow,phihigh,"#phi_{#mu}_lu_is ","Events");
    fGeneralphi_ll_is = gHistogrammer->TH1DFactory("DIMuon","phi_ll_is","#phi_{#mu}_ll_is ",phibins,philow,phihigh,"#phi_{#mu}_ll_is ","Events");
    fGeneralphi_hu_is = gHistogrammer->TH1DFactory("DIMuon","phi_hu_is","#phi_{#mu}_hu_is ",phibins,philow,phihigh,"#phi_{#mu}_hu_is ","Events");
    fGeneralphi_hl_is = gHistogrammer->TH1DFactory("DIMuon","phi_hl_is","#phi_{#mu}_hl_is ",phibins,philow,phihigh,"#phi_{#mu}_hl_is ","Events");
    fGeneralphi_lu_nis = gHistogrammer->TH1DFactory("DIMuon","phi_lu_nis","#phi_{#mu}_lu_nis ",phibins,philow,phihigh,"#phi_{#mu}_lu_nis ","Events");
    fGeneralphi_ll_nis = gHistogrammer->TH1DFactory("DIMuon","phi_ll_nis","#phi_{#mu}_ll_nis ",phibins,philow,phihigh,"#phi_{#mu}_ll_nis ","Events");
    fGeneralphi_hu_nis = gHistogrammer->TH1DFactory("DIMuon","phi_hu_nis","#phi_{#mu}_hu_nis ",phibins,philow,phihigh,"#phi_{#mu}_hu_nis ","Events");
    fGeneralphi_hl_nis = gHistogrammer->TH1DFactory("DIMuon","phi_hl_nis","#phi_{#mu}_hl_nis ",phibins,philow,phihigh,"#phi_{#mu}_hl_nis ","Events");
    fGeneralmuqual = gHistogrammer->TH1DFactory("DIMuon","muqual","#muqual_{#mu} ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu} ","Events");
    fGeneralmuqual_lu_is = gHistogrammer->TH1DFactory("DIMuon","muqual_lu_is","#muqual_{#mu}_lu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_is ","Events");
    fGeneralmuqual_ll_is = gHistogrammer->TH1DFactory("DIMuon","muqual_ll_is","#muqual_{#mu}_ll_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_is ","Events");
    fGeneralmuqual_hu_is = gHistogrammer->TH1DFactory("DIMuon","muqual_hu_is","#muqual_{#mu}_hu_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_is ","Events");
    fGeneralmuqual_hl_is = gHistogrammer->TH1DFactory("DIMuon","muqual_hl_is","#muqual_{#mu}_hl_is ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_is ","Events");
    fGeneralmuqual_lu_nis = gHistogrammer->TH1DFactory("DIMuon","muqual_lu_nis","#muqual_{#mu}_lu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_lu_nis ","Events");
    fGeneralmuqual_ll_nis = gHistogrammer->TH1DFactory("DIMuon","muqual_ll_nis","#muqual_{#mu}_ll_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_ll_nis ","Events");
    fGeneralmuqual_hu_nis = gHistogrammer->TH1DFactory("DIMuon","muqual_hu_nis","#muqual_{#mu}_hu_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hu_nis ","Events");
    fGeneralmuqual_hl_nis = gHistogrammer->TH1DFactory("DIMuon","muqual_hl_nis","#muqual_{#mu}_hl_nis ",muqualbins,muquallow,muqualhigh,"#muqual_{#mu}_hl_nis ","Events");

    fGeneralsqisol_10    = gHistogrammer->TH1DFactory("DIMuon","sqisol_10","sqisol_10_{#mu}",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_{#mu}","Events");
    fGeneralsqisol_10_is_lu = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_lu","sqisol_10_is_{#mu}_lu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_lu","Events");
    fGeneralsqisol_10_is_ll = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_ll","sqisol_10_is_{#mu}_ll",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_ll","Events");
    fGeneralsqisol_10_is_hu = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_hu","sqisol_10_is_{#mu}_hu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hu","Events");
    fGeneralsqisol_10_is_hl = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_is_hl","sqisol_10_is_{#mu}_hl",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_is_{#mu}_hl","Events");
    fGeneralsqisol_10_nis_lu = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_lu","sqisol_10_nis_{#mu}_lu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_lu","Events");
    fGeneralsqisol_10_nis_ll = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_ll","sqisol_10_nis_{#mu}_ll",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_ll","Events");
    fGeneralsqisol_10_nis_hu = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_hu","sqisol_10_nis_{#mu}_hu",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hu","Events");
    fGeneralsqisol_10_nis_hl = gHistogrammer->TH1DFactory("DIMuon","sqisol_10_nis_hl","sqisol_10_nis_{#mu}_hl",sqisol_10bins,sqisol_10low,sqisol_10high,"#sqisol_10_nis_{#mu}_hl","Events");

    fGeneralthrust    = gHistogrammer->TH1DFactory("DIMuon","thrust","thrust",thrustbins,thrustlow,thrusthigh,"#thrust","Events");
    fGeneralthrust_is_lu = gHistogrammer->TH1DFactory("DIMuon","thrust_is_lu","lu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_lu","Events");
    fGeneralthrust_is_ll = gHistogrammer->TH1DFactory("DIMuon","thrust_is_ll","ll thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_ll","Events");
    fGeneralthrust_is_hu = gHistogrammer->TH1DFactory("DIMuon","thrust_is_hu","hu thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hu","Events");
    fGeneralthrust_is_hl = gHistogrammer->TH1DFactory("DIMuon","thrust_is_hl","hl thrust_is",thrustbins,thrustlow,thrusthigh,"#thrust_is_hl","Events");
    fGeneralthrust_nis_lu = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_lu","lu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_lu","Events");
    fGeneralthrust_nis_ll = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_ll","ll thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_ll","Events");
    fGeneralthrust_nis_hu = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_hu","hu thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hu","Events");
    fGeneralthrust_nis_hl = gHistogrammer->TH1DFactory("DIMuon","thrust_nis_hl","hl thrust_nis",thrustbins,thrustlow,thrusthigh,"#thrust_nis_hl","Events");

//**********************************************************
//Here the Histograms for the Instanton - Variables
//**********************************************************

    fGeneralQ2Prime    = gHistogrammer->TH1DFactory("DIMuon","Q2Prime","Q2Prime",q2primebins,q2primelow,q2primehigh,"Q'^{2}","Events");
    fGeneralQ2Prime_is_lu = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_lu","lu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_lu","Events");
    fGeneralQ2Prime_is_ll = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_ll","ll Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_ll","Events");
    fGeneralQ2Prime_is_hu = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_hu","hu Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hu","Events");
    fGeneralQ2Prime_is_hl = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_is_hl","hl Q2Prime_is",q2primebins,q2primelow,q2primehigh,"Q'^{2}_is_hl","Events");
    fGeneralQ2Prime_nis_lu = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_lu","lu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_lu","Events");
    fGeneralQ2Prime_nis_ll = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_ll","ll Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_ll","Events");
    fGeneralQ2Prime_nis_hu = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_hu","hu Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hu","Events");
    fGeneralQ2Prime_nis_hl = gHistogrammer->TH1DFactory("DIMuon","Q2Prime_nis_hl","hl Q2Prime_nis",q2primebins,q2primelow,q2primehigh,"Q'^{2}_nis_hl","Events");

    fGeneralsphericity    = gHistogrammer->TH1DFactory("DIMuon","sphericity","sphericity",sphericitybins,sphericitylow,sphericityhigh,"#sphericity","Events");
    fGeneralsphericity_is_lu = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_lu","lu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_lu","Events");
    fGeneralsphericity_is_ll = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_ll","ll sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_ll","Events");
    fGeneralsphericity_is_hu = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_hu","hu sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hu","Events");
    fGeneralsphericity_is_hl = gHistogrammer->TH1DFactory("DIMuon","sphericity_is_hl","hl sphericity_is",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_is_hl","Events");
    fGeneralsphericity_nis_lu = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_lu","lu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_lu","Events");
    fGeneralsphericity_nis_ll = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_ll","ll sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_ll","Events");
    fGeneralsphericity_nis_hu = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_hu","hu sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hu","Events");
    fGeneralsphericity_nis_hl = gHistogrammer->TH1DFactory("DIMuon","sphericity_nis_hl","hl sphericity_nis",sphericitybins,sphericitylow,sphericityhigh,"#sphericity_nis_hl","Events");

    fGeneralisotropy    = gHistogrammer->TH1DFactory("DIMuon","isotropy","isotropy",isotropybins,isotropylow,isotropyhigh,"#isotropy","Events");
    fGeneralisotropy_is_lu = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_lu","lu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_lu","Events");
    fGeneralisotropy_is_ll = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_ll","ll isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_ll","Events");
    fGeneralisotropy_is_hu = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_hu","hu isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hu","Events");
    fGeneralisotropy_is_hl = gHistogrammer->TH1DFactory("DIMuon","isotropy_is_hl","hl isotropy_is",isotropybins,isotropylow,isotropyhigh,"#isotropy_is_hl","Events");
    fGeneralisotropy_nis_lu = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_lu","lu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_lu","Events");
    fGeneralisotropy_nis_ll = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_ll","ll isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_ll","Events");
    fGeneralisotropy_nis_hu = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_hu","hu isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hu","Events");
    fGeneralisotropy_nis_hl = gHistogrammer->TH1DFactory("DIMuon","isotropy_nis_hl","hl isotropy_nis",isotropybins,isotropylow,isotropyhigh,"#isotropy_nis_hl","Events");

    fGeneralmultiplicity    = gHistogrammer->TH1DFactory("DIMuon","multiplicity","multiplicity",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity","Events");
    fGeneralmultiplicity_is_lu = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_lu","lu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_lu","Events");
    fGeneralmultiplicity_is_ll = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_ll","ll multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_ll","Events");
    fGeneralmultiplicity_is_hu = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_hu","hu multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hu","Events");
    fGeneralmultiplicity_is_hl = gHistogrammer->TH1DFactory("DIMuon","multiplicity_is_hl","hl multiplicity_is",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_is_hl","Events");
    fGeneralmultiplicity_nis_lu = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_lu","lu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_lu","Events");
    fGeneralmultiplicity_nis_ll = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_ll","ll multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_ll","Events");
    fGeneralmultiplicity_nis_hu = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_hu","hu multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hu","Events");
    fGeneralmultiplicity_nis_hl = gHistogrammer->TH1DFactory("DIMuon","multiplicity_nis_hl","hl multiplicity_nis",multiplicitybins,multiplicitylow,multiplicityhigh,"# multiplicity_nis_hl","Events");

//**********************************************************

    fGeneralempz    = gHistogrammer->TH1DFactory("DIMuon","empz","empz",empzbins,empzlow,empzhigh,"#empz","Events");
    fGeneralempz_is_lu = gHistogrammer->TH1DFactory("DIMuon","empz_is_lu","lu empz_is",empzbins,empzlow,empzhigh,"#empz_is_lu","Events");
    fGeneralempz_is_ll = gHistogrammer->TH1DFactory("DIMuon","empz_is_ll","ll empz_is",empzbins,empzlow,empzhigh,"#empz_is_ll","Events");
    fGeneralempz_is_hu = gHistogrammer->TH1DFactory("DIMuon","empz_is_hu","hu empz_is",empzbins,empzlow,empzhigh,"#empz_is_hu","Events");
    fGeneralempz_is_hl = gHistogrammer->TH1DFactory("DIMuon","empz_is_hl","hl empz_is",empzbins,empzlow,empzhigh,"#empz_is_hl","Events");
    fGeneralempz_nis_lu = gHistogrammer->TH1DFactory("DIMuon","empz_nis_lu","lu empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_lu","Events");
    fGeneralempz_nis_ll = gHistogrammer->TH1DFactory("DIMuon","empz_nis_ll","ll empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_ll","Events");
    fGeneralempz_nis_hu = gHistogrammer->TH1DFactory("DIMuon","empz_nis_hu","hu empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_hu","Events");
    fGeneralempz_nis_hl = gHistogrammer->TH1DFactory("DIMuon","empz_nis_hl","hl empz_nis",empzbins,empzlow,empzhigh,"#empz_nis_hl","Events");

    fGeneralcal_et    = gHistogrammer->TH1DFactory("DIMuon","cal_et","cal_et",cal_etbins,cal_etlow,cal_ethigh,"#cal_et","Events");
    fGeneralcal_et_is_lu = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_lu","lu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_lu","Events");
    fGeneralcal_et_is_ll = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_ll","ll cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_ll","Events");
    fGeneralcal_et_is_hu = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_hu","hu cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hu","Events");
    fGeneralcal_et_is_hl = gHistogrammer->TH1DFactory("DIMuon","cal_et_is_hl","hl cal_et_is",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_is_hl","Events");
    fGeneralcal_et_nis_lu = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_lu","lu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_lu","Events");
    fGeneralcal_et_nis_ll = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_ll","ll cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_ll","Events");
    fGeneralcal_et_nis_hu = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_hu","hu cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hu","Events");
    fGeneralcal_et_nis_hl = gHistogrammer->TH1DFactory("DIMuon","cal_et_nis_hl","hl cal_et_nis",cal_etbins,cal_etlow,cal_ethigh,"#cal_et_nis_hl","Events");

     fGeneraletex2ir    = gHistogrammer->TH1DFactory("DIMuon","etex2ir","etex2ir",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir","Events");
     fGeneraletex2ir_is_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_lu","lu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_lu","Events");
     fGeneraletex2ir_is_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_ll","ll etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_ll","Events");
     fGeneraletex2ir_is_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_hu","hu etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hu","Events");
     fGeneraletex2ir_is_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_is_hl","hl etex2ir_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_is_hl","Events");
     fGeneraletex2ir_nis_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_lu","lu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_lu","Events");
     fGeneraletex2ir_nis_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_ll","ll etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_ll","Events");
     fGeneraletex2ir_nis_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_hu","hu etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hu","Events");
     fGeneraletex2ir_nis_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_nis_hl","hl etex2ir_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_nis_hl","Events");
//     fGeneraletex2ir    = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir","etex2ir",            dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir","Events");
//     fGeneraletex2ir_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_is_lu","lu etex2ir_is",   dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_is_lu","Events");
//     fGeneraletex2ir_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_is_ll","ll etex2ir_is",   dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_is_ll","Events");
//     fGeneraletex2ir_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_is_hu","hu etex2ir_is",   dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_is_hu","Events");
//     fGeneraletex2ir_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_is_hl","hl etex2ir_is",   dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_is_hl","Events");
//     fGeneraletex2ir_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_nis_lu","lu etex2ir_nis",dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_nis_lu","Events");
//     fGeneraletex2ir_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_nis_ll","ll etex2ir_nis",dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_nis_ll","Events");
//     fGeneraletex2ir_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_nis_hu","hu etex2ir_nis",dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_nis_hu","Events");
//     fGeneraletex2ir_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","etex2ir_nis_hl","hl etex2ir_nis",dimucrosspt_nbins,dimucrosspt_bins,"#etex2ir_nis_hl","Events");

    fGeneralcal_et_m_et2ir    = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir","cal_et_m_et2ir",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir","Events");
    fGeneralcal_et_m_et2ir_is_lu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_lu","lu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_lu","Events");
    fGeneralcal_et_m_et2ir_is_ll = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_ll","ll cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_ll","Events");
    fGeneralcal_et_m_et2ir_is_hu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_hu","hu cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hu","Events");
    fGeneralcal_et_m_et2ir_is_hl = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_is_hl","hl cal_et_m_et2ir_is",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_is_hl","Events");
    fGeneralcal_et_m_et2ir_nis_lu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_lu","lu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_lu","Events");
    fGeneralcal_et_m_et2ir_nis_ll = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_ll","ll cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_ll","Events");
    fGeneralcal_et_m_et2ir_nis_hu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_hu","hu cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hu","Events");
    fGeneralcal_et_m_et2ir_nis_hl = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_et2ir_nis_hl","hl cal_et_m_et2ir_nis",cal_et_m_et2irbins,cal_et_m_et2irlow,cal_et_m_et2irhigh,"#cal_et_m_et2ir_nis_hl","Events");

    fGeneralcal_et_m_cal_et_10    = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10","cal_et_m_cal_et_10",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10","Events");
    fGeneralcal_et_m_cal_et_10_is_lu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_lu","lu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_lu","Events");
    fGeneralcal_et_m_cal_et_10_is_ll = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_ll","ll cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_ll","Events");
    fGeneralcal_et_m_cal_et_10_is_hu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_hu","hu cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hu","Events");
    fGeneralcal_et_m_cal_et_10_is_hl = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_is_hl","hl cal_et_m_cal_et_10_is",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_is_hl","Events");
    fGeneralcal_et_m_cal_et_10_nis_lu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_lu","lu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_lu","Events");
    fGeneralcal_et_m_cal_et_10_nis_ll = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_ll","ll cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_ll","Events");
    fGeneralcal_et_m_cal_et_10_nis_hu = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_hu","hu cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hu","Events");
    fGeneralcal_et_m_cal_et_10_nis_hl = gHistogrammer->TH1DFactory("DIMuon","cal_et_m_cal_et_10_nis_hl","hl cal_et_m_cal_et_10_nis",cal_et_m_cal_et_10bins,cal_et_m_cal_et_10low,cal_et_m_cal_et_10high,"#cal_et_m_cal_et_10_nis_hl","Events");

/* DB Dijet Histos  */

    fGeneraldijetbothetex2ir    = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both","etex2ir_both",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both","Events");
    fGeneraldijetbothetex2ir_is_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_is_lu","lu etex2ir_both_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_is_lu","Events");
    fGeneraldijetbothetex2ir_is_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_is_ll","ll etex2ir_both_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_is_ll","Events");
    fGeneraldijetbothetex2ir_is_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_is_hu","hu etex2ir_both_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_is_hu","Events");
    fGeneraldijetbothetex2ir_is_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_is_hl","hl etex2ir_both_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_is_hl","Events");
    fGeneraldijetbothetex2ir_nis_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_nis_lu","lu etex2ir_both_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_nis_lu","Events");
    fGeneraldijetbothetex2ir_nis_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_nis_ll","ll etex2ir_both_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_nis_ll","Events");
    fGeneraldijetbothetex2ir_nis_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_nis_hu","hu etex2ir_both_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_nis_hu","Events");
    fGeneraldijetbothetex2ir_nis_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_both_nis_hl","hl etex2ir_both_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_both_nis_hl","Events");

    fGeneraldijetbothdimuxsecpt        = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both"," dimuxsecpt_both",            dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both","Events");
    fGeneraldijetbothdimuxsecpt_is_lu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_is_lu","lu dimuxsecpt_both_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_is_lu","Events");
    fGeneraldijetbothdimuxsecpt_is_ll  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_is_ll","ll dimuxsecpt_both_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_is_ll","Events");
    fGeneraldijetbothdimuxsecpt_is_hu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_is_hu","hu dimuxsecpt_both_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_is_hu","Events");
    fGeneraldijetbothdimuxsecpt_is_hl  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_is_hl","hl dimuxsecpt_both_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_is_hl","Events");
    fGeneraldijetbothdimuxsecpt_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_nis_lu","lu dimuxsecpt_both_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_nis_lu","Events");
    fGeneraldijetbothdimuxsecpt_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_nis_ll","ll dimuxsecpt_both_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_nis_ll","Events");
    fGeneraldijetbothdimuxsecpt_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_nis_hu","hu dimuxsecpt_both_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_nis_hu","Events");
    fGeneraldijetbothdimuxsecpt_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_both_nis_hl","hl dimuxsecpt_both_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_both_nis_hl","Events");

    fGeneraldijetbothdimuxseceta    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both"," dimuxseceta_both",            dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both","Events");
    fGeneraldijetbothdimuxseceta_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_is_lu","lu dimuxseceta_both_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_is_lu","Events");
    fGeneraldijetbothdimuxseceta_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_is_ll","ll dimuxseceta_both_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_is_ll","Events");
    fGeneraldijetbothdimuxseceta_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_is_hu","hu dimuxseceta_both_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_is_hu","Events");
    fGeneraldijetbothdimuxseceta_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_is_hl","hl dimuxseceta_both_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_is_hl","Events");
    fGeneraldijetbothdimuxseceta_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_nis_lu","lu dimuxseceta_both_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_nis_lu","Events");
    fGeneraldijetbothdimuxseceta_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_nis_ll","ll dimuxseceta_both_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_nis_ll","Events");
    fGeneraldijetbothdimuxseceta_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_nis_hu","hu dimuxseceta_both_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_nis_hu","Events");
    fGeneraldijetbothdimuxseceta_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_both_nis_hl","hl dimuxseceta_both_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_both_nis_hl","Events");

    fGeneraldijetbothdimuxsecdphi    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both"," dimuxsecdphi_both",            dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both","Events");
    fGeneraldijetbothdimuxsecdphi_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_is_lu","lu dimuxsecdphi_both_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_is_lu","Events");
    fGeneraldijetbothdimuxsecdphi_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_is_ll","ll dimuxsecdphi_both_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_is_ll","Events");
    fGeneraldijetbothdimuxsecdphi_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_is_hu","hu dimuxsecdphi_both_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_is_hu","Events");
    fGeneraldijetbothdimuxsecdphi_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_is_hl","hl dimuxsecdphi_both_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_is_hl","Events");
    fGeneraldijetbothdimuxsecdphi_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_nis_lu","lu dimuxsecdphi_both_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_nis_lu","Events");
    fGeneraldijetbothdimuxsecdphi_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_nis_ll","ll dimuxsecdphi_both_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_nis_ll","Events");
    fGeneraldijetbothdimuxsecdphi_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_nis_hu","hu dimuxsecdphi_both_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_nis_hu","Events");
    fGeneraldijetbothdimuxsecdphi_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_both_nis_hl","hl dimuxsecdphi_both_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_both_nis_hl","Events");

    fGeneraldijetoneetex2ir    = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one","etex2ir_one",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one","Events");
    fGeneraldijetoneetex2ir_is_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_is_lu","lu etex2ir_one_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_is_lu","Events");
    fGeneraldijetoneetex2ir_is_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_is_ll","ll etex2ir_one_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_is_ll","Events");
    fGeneraldijetoneetex2ir_is_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_is_hu","hu etex2ir_one_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_is_hu","Events");
    fGeneraldijetoneetex2ir_is_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_is_hl","hl etex2ir_one_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_is_hl","Events");
    fGeneraldijetoneetex2ir_nis_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_nis_lu","lu etex2ir_one_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_nis_lu","Events");
    fGeneraldijetoneetex2ir_nis_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_nis_ll","ll etex2ir_one_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_nis_ll","Events");
    fGeneraldijetoneetex2ir_nis_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_nis_hu","hu etex2ir_one_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_nis_hu","Events");
    fGeneraldijetoneetex2ir_nis_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_one_nis_hl","hl etex2ir_one_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_one_nis_hl","Events");

    fGeneraldijetonedimuxsecpt        = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one"," dimuxsecpt_one",            dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one","Events");
    fGeneraldijetonedimuxsecpt_is_lu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_is_lu","lu dimuxsecpt_one_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_is_lu","Events");
    fGeneraldijetonedimuxsecpt_is_ll  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_is_ll","ll dimuxsecpt_one_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_is_ll","Events");
    fGeneraldijetonedimuxsecpt_is_hu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_is_hu","hu dimuxsecpt_one_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_is_hu","Events");
    fGeneraldijetonedimuxsecpt_is_hl  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_is_hl","hl dimuxsecpt_one_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_is_hl","Events");
    fGeneraldijetonedimuxsecpt_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_nis_lu","lu dimuxsecpt_one_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_nis_lu","Events");
    fGeneraldijetonedimuxsecpt_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_nis_ll","ll dimuxsecpt_one_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_nis_ll","Events");
    fGeneraldijetonedimuxsecpt_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_nis_hu","hu dimuxsecpt_one_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_nis_hu","Events");
    fGeneraldijetonedimuxsecpt_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_one_nis_hl","hl dimuxsecpt_one_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_one_nis_hl","Events");

    fGeneraldijetonedimuxseceta    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one"," dimuxseceta_one",            dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one","Events");
    fGeneraldijetonedimuxseceta_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_is_lu","lu dimuxseceta_one_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_is_lu","Events");
    fGeneraldijetonedimuxseceta_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_is_ll","ll dimuxseceta_one_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_is_ll","Events");
    fGeneraldijetonedimuxseceta_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_is_hu","hu dimuxseceta_one_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_is_hu","Events");
    fGeneraldijetonedimuxseceta_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_is_hl","hl dimuxseceta_one_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_is_hl","Events");
    fGeneraldijetonedimuxseceta_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_nis_lu","lu dimuxseceta_one_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_nis_lu","Events");
    fGeneraldijetonedimuxseceta_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_nis_ll","ll dimuxseceta_one_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_nis_ll","Events");
    fGeneraldijetonedimuxseceta_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_nis_hu","hu dimuxseceta_one_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_nis_hu","Events");
    fGeneraldijetonedimuxseceta_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_one_nis_hl","hl dimuxseceta_one_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_one_nis_hl","Events");

    fGeneraldijetonedimuxsecdphi    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one"," dimuxsecdphi_one",            dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one","Events");
    fGeneraldijetonedimuxsecdphi_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_is_lu","lu dimuxsecdphi_one_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_is_lu","Events");
    fGeneraldijetonedimuxsecdphi_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_is_ll","ll dimuxsecdphi_one_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_is_ll","Events");
    fGeneraldijetonedimuxsecdphi_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_is_hu","hu dimuxsecdphi_one_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_is_hu","Events");
    fGeneraldijetonedimuxsecdphi_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_is_hl","hl dimuxsecdphi_one_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_is_hl","Events");
    fGeneraldijetonedimuxsecdphi_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_nis_lu","lu dimuxsecdphi_one_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_nis_lu","Events");
    fGeneraldijetonedimuxsecdphi_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_nis_ll","ll dimuxsecdphi_one_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_nis_ll","Events");
    fGeneraldijetonedimuxsecdphi_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_nis_hu","hu dimuxsecdphi_one_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_nis_hu","Events");
    fGeneraldijetonedimuxsecdphi_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_one_nis_hl","hl dimuxsecdphi_one_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_one_nis_hl","Events");

    fGeneraldijetnoneetex2ir    = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none","etex2ir_none",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none","Events");
    fGeneraldijetnoneetex2ir_is_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_is_lu","lu etex2ir_none_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_is_lu","Events");
    fGeneraldijetnoneetex2ir_is_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_is_ll","ll etex2ir_none_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_is_ll","Events");
    fGeneraldijetnoneetex2ir_is_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_is_hu","hu etex2ir_none_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_is_hu","Events");
    fGeneraldijetnoneetex2ir_is_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_is_hl","hl etex2ir_none_is",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_is_hl","Events");
    fGeneraldijetnoneetex2ir_nis_lu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_nis_lu","lu etex2ir_none_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_nis_lu","Events");
    fGeneraldijetnoneetex2ir_nis_ll = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_nis_ll","ll etex2ir_none_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_nis_ll","Events");
    fGeneraldijetnoneetex2ir_nis_hu = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_nis_hu","hu etex2ir_none_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_nis_hu","Events");
    fGeneraldijetnoneetex2ir_nis_hl = gHistogrammer->TH1DFactory("DIMuon","etex2ir_none_nis_hl","hl etex2ir_none_nis",etex2irbins,etex2irlow,etex2irhigh,"#etex2ir_none_nis_hl","Events");

    fGeneraldijetnonedimuxsecpt        = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none"," dimuxsecpt_none",            dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none","Events");
    fGeneraldijetnonedimuxsecpt_is_lu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_is_lu","lu dimuxsecpt_none_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_is_lu","Events");
    fGeneraldijetnonedimuxsecpt_is_ll  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_is_ll","ll dimuxsecpt_none_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_is_ll","Events");
    fGeneraldijetnonedimuxsecpt_is_hu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_is_hu","hu dimuxsecpt_none_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_is_hu","Events");
    fGeneraldijetnonedimuxsecpt_is_hl  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_is_hl","hl dimuxsecpt_none_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_is_hl","Events");
    fGeneraldijetnonedimuxsecpt_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_nis_lu","lu dimuxsecpt_none_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_nis_lu","Events");
    fGeneraldijetnonedimuxsecpt_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_nis_ll","ll dimuxsecpt_none_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_nis_ll","Events");
    fGeneraldijetnonedimuxsecpt_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_nis_hu","hu dimuxsecpt_none_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_nis_hu","Events");
    fGeneraldijetnonedimuxsecpt_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_none_nis_hl","hl dimuxsecpt_none_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_none_nis_hl","Events");

    fGeneraldijetnonedimuxseceta    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none"," dimuxseceta_none",            dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none","Events");
    fGeneraldijetnonedimuxseceta_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_is_lu","lu dimuxseceta_none_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_is_lu","Events");
    fGeneraldijetnonedimuxseceta_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_is_ll","ll dimuxseceta_none_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_is_ll","Events");
    fGeneraldijetnonedimuxseceta_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_is_hu","hu dimuxseceta_none_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_is_hu","Events");
    fGeneraldijetnonedimuxseceta_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_is_hl","hl dimuxseceta_none_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_is_hl","Events");
    fGeneraldijetnonedimuxseceta_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_nis_lu","lu dimuxseceta_none_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_nis_lu","Events");
    fGeneraldijetnonedimuxseceta_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_nis_ll","ll dimuxseceta_none_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_nis_ll","Events");
    fGeneraldijetnonedimuxseceta_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_nis_hu","hu dimuxseceta_none_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_nis_hu","Events");
    fGeneraldijetnonedimuxseceta_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_none_nis_hl","hl dimuxseceta_none_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_none_nis_hl","Events");

    fGeneraldijetnonedimuxsecdphi    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none"," dimuxsecdphi_none",            dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none","Events");
    fGeneraldijetnonedimuxsecdphi_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_is_lu","lu dimuxsecdphi_none_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_is_lu","Events");
    fGeneraldijetnonedimuxsecdphi_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_is_ll","ll dimuxsecdphi_none_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_is_ll","Events");
    fGeneraldijetnonedimuxsecdphi_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_is_hu","hu dimuxsecdphi_none_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_is_hu","Events");
    fGeneraldijetnonedimuxsecdphi_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_is_hl","hl dimuxsecdphi_none_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_is_hl","Events");
    fGeneraldijetnonedimuxsecdphi_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_nis_lu","lu dimuxsecdphi_none_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_nis_lu","Events");
    fGeneraldijetnonedimuxsecdphi_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_nis_ll","ll dimuxsecdphi_none_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_nis_ll","Events");
    fGeneraldijetnonedimuxsecdphi_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_nis_hu","hu dimuxsecdphi_none_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_nis_hu","Events");
    fGeneraldijetnonedimuxsecdphi_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_none_nis_hl","hl dimuxsecdphi_none_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_none_nis_hl","Events");

/* End DB Histos */

    fGeneraldimuxsecpt        = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt"," dimuxsecpt",            dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt","Events");
    fGeneraldimuxsecpt_is_lu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_is_lu","lu dimuxsecpt_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_is_lu","Events");
    fGeneraldimuxsecpt_is_ll  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_is_ll","ll dimuxsecpt_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_is_ll","Events");
    fGeneraldimuxsecpt_is_hu  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_is_hu","hu dimuxsecpt_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_is_hu","Events");
    fGeneraldimuxsecpt_is_hl  = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_is_hl","hl dimuxsecpt_is",   dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_is_hl","Events");
    fGeneraldimuxsecpt_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_nis_lu","lu dimuxsecpt_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_nis_lu","Events");
    fGeneraldimuxsecpt_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_nis_ll","ll dimuxsecpt_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_nis_ll","Events");
    fGeneraldimuxsecpt_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_nis_hu","hu dimuxsecpt_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_nis_hu","Events");
    fGeneraldimuxsecpt_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecpt_nis_hl","hl dimuxsecpt_nis",dimucrosspt_nbins,dimucrosspt_bins,"#dimuxsecpt_nis_hl","Events");

    fGeneraldimuxseceta    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta"," dimuxseceta",            dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta","Events");
    fGeneraldimuxseceta_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_is_lu","lu dimuxseceta_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_is_lu","Events");
    fGeneraldimuxseceta_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_is_ll","ll dimuxseceta_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_is_ll","Events");
    fGeneraldimuxseceta_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_is_hu","hu dimuxseceta_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_is_hu","Events");
    fGeneraldimuxseceta_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_is_hl","hl dimuxseceta_is",   dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_is_hl","Events");
    fGeneraldimuxseceta_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_nis_lu","lu dimuxseceta_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_nis_lu","Events");
    fGeneraldimuxseceta_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_nis_ll","ll dimuxseceta_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_nis_ll","Events");
    fGeneraldimuxseceta_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_nis_hu","hu dimuxseceta_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_nis_hu","Events");
    fGeneraldimuxseceta_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxseceta_nis_hl","hl dimuxseceta_nis",dimucrosseta_nbins,dimucrosseta_bins,"#dimuxseceta_nis_hl","Events");

    fGeneraldimuxsecfinders    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders"," dimuxsecfinders",            dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders","Events");
    fGeneraldimuxsecfinders_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_is_lu","lu dimuxsecfinders_is",   dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_is_lu","Events");
    fGeneraldimuxsecfinders_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_is_ll","ll dimuxsecfinders_is",   dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_is_ll","Events");
    fGeneraldimuxsecfinders_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_is_hu","hu dimuxsecfinders_is",   dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_is_hu","Events");
    fGeneraldimuxsecfinders_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_is_hl","hl dimuxsecfinders_is",   dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_is_hl","Events");
    fGeneraldimuxsecfinders_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_nis_lu","lu dimuxsecfinders_nis",dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_nis_lu","Events");
    fGeneraldimuxsecfinders_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_nis_ll","ll dimuxsecfinders_nis",dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_nis_ll","Events");
    fGeneraldimuxsecfinders_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_nis_hu","hu dimuxsecfinders_nis",dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_nis_hu","Events");
    fGeneraldimuxsecfinders_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecfinders_nis_hl","hl dimuxsecfinders_nis",dimucrossfinders_nbins,dimucrossfinders_bins,"#dimuxsecfinders_nis_hl","Events");

    fGeneraldimuxsecdr    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr"," dimuxsecdr",            dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr","Events");
    fGeneraldimuxsecdr_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_is_lu","lu dimuxsecdr_is",   dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_is_lu","Events");
    fGeneraldimuxsecdr_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_is_ll","ll dimuxsecdr_is",   dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_is_ll","Events");
    fGeneraldimuxsecdr_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_is_hu","hu dimuxsecdr_is",   dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_is_hu","Events");
    fGeneraldimuxsecdr_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_is_hl","hl dimuxsecdr_is",   dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_is_hl","Events");
    fGeneraldimuxsecdr_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_nis_lu","lu dimuxsecdr_nis",dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_nis_lu","Events");
    fGeneraldimuxsecdr_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_nis_ll","ll dimuxsecdr_nis",dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_nis_ll","Events");
    fGeneraldimuxsecdr_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_nis_hu","hu dimuxsecdr_nis",dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_nis_hu","Events");
    fGeneraldimuxsecdr_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdr_nis_hl","hl dimuxsecdr_nis",dimucrossdr_nbins,dimucrossdr_bins,"#dimuxsecdr_nis_hl","Events");

    fGeneraldimuxsecdphi    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi"," dimuxsecdphi",            dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi","Events");
    fGeneraldimuxsecdphi_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_is_lu","lu dimuxsecdphi_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_is_lu","Events");
    fGeneraldimuxsecdphi_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_is_ll","ll dimuxsecdphi_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_is_ll","Events");
    fGeneraldimuxsecdphi_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_is_hu","hu dimuxsecdphi_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_is_hu","Events");
    fGeneraldimuxsecdphi_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_is_hl","hl dimuxsecdphi_is",   dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_is_hl","Events");
    fGeneraldimuxsecdphi_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_nis_lu","lu dimuxsecdphi_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_nis_lu","Events");
    fGeneraldimuxsecdphi_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_nis_ll","ll dimuxsecdphi_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_nis_ll","Events");
    fGeneraldimuxsecdphi_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_nis_hu","hu dimuxsecdphi_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_nis_hu","Events");
    fGeneraldimuxsecdphi_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecdphi_nis_hl","hl dimuxsecdphi_nis",dimucrossdphi_nbins,dimucrossdphi_bins,"#dimuxsecdphi_nis_hl","Events");

    fGeneraldimuxsecptb    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb"," dimuxsecptb",            dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb","Events");
    fGeneraldimuxsecptb_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_is_lu","lu dimuxsecptb_is",   dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_is_lu","Events");
    fGeneraldimuxsecptb_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_is_ll","ll dimuxsecptb_is",   dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_is_ll","Events");
    fGeneraldimuxsecptb_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_is_hu","hu dimuxsecptb_is",   dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_is_hu","Events");
    fGeneraldimuxsecptb_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_is_hl","hl dimuxsecptb_is",   dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_is_hl","Events");
    fGeneraldimuxsecptb_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_nis_lu","lu dimuxsecptb_nis",dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_nis_lu","Events");
    fGeneraldimuxsecptb_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_nis_ll","ll dimuxsecptb_nis",dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_nis_ll","Events");
    fGeneraldimuxsecptb_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_nis_hu","hu dimuxsecptb_nis",dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_nis_hu","Events");
    fGeneraldimuxsecptb_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_nis_hl","hl dimuxsecptb_nis",dimucrossptb_nbins,dimucrossptb_bins,"#dimuxsecptb_nis_hl","Events");

    fGeneraldimuxsecptb_sameb    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb"," dimuxsecptb_sameb",            dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb","Events");
    fGeneraldimuxsecptb_sameb_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_is_lu","lu dimuxsecptb_sameb_is",   dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_is_lu","Events");
    fGeneraldimuxsecptb_sameb_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_is_ll","ll dimuxsecptb_sameb_is",   dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_is_ll","Events");
    fGeneraldimuxsecptb_sameb_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_is_hu","hu dimuxsecptb_sameb_is",   dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_is_hu","Events");
    fGeneraldimuxsecptb_sameb_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_is_hl","hl dimuxsecptb_sameb_is",   dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_is_hl","Events");
    fGeneraldimuxsecptb_sameb_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_nis_lu","lu dimuxsecptb_sameb_nis",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_nis_lu","Events");
    fGeneraldimuxsecptb_sameb_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_nis_ll","ll dimuxsecptb_sameb_nis",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_nis_ll","Events");
    fGeneraldimuxsecptb_sameb_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_nis_hu","hu dimuxsecptb_sameb_nis",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_nis_hu","Events");
    fGeneraldimuxsecptb_sameb_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_sameb_nis_hl","hl dimuxsecptb_sameb_nis",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"#dimuxsecptb_sameb_nis_hl","Events");

    fGeneraldimuxsecptb_diffb    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb"," dimuxsecptb_diffb",            dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb","Events");
    fGeneraldimuxsecptb_diffb_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_is_lu","lu dimuxsecptb_diffb_is",   dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_is_lu","Events");
    fGeneraldimuxsecptb_diffb_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_is_ll","ll dimuxsecptb_diffb_is",   dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_is_ll","Events");
    fGeneraldimuxsecptb_diffb_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_is_hu","hu dimuxsecptb_diffb_is",   dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_is_hu","Events");
    fGeneraldimuxsecptb_diffb_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_is_hl","hl dimuxsecptb_diffb_is",   dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_is_hl","Events");
    fGeneraldimuxsecptb_diffb_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_nis_lu","lu dimuxsecptb_diffb_nis",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_nis_lu","Events");
    fGeneraldimuxsecptb_diffb_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_nis_ll","ll dimuxsecptb_diffb_nis",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_nis_ll","Events");
    fGeneraldimuxsecptb_diffb_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_nis_hu","hu dimuxsecptb_diffb_nis",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_nis_hu","Events");
    fGeneraldimuxsecptb_diffb_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_diffb_nis_hl","hl dimuxsecptb_diffb_nis",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"#dimuxsecptb_diffb_nis_hl","Events");

    fGeneraldimuxsecptb_samecone    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone"," dimuxsecptb_samecone",            dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone","Events");
    fGeneraldimuxsecptb_samecone_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_is_lu","lu dimuxsecptb_samecone_is",   dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_is_lu","Events");
    fGeneraldimuxsecptb_samecone_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_is_ll","ll dimuxsecptb_samecone_is",   dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_is_ll","Events");
    fGeneraldimuxsecptb_samecone_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_is_hu","hu dimuxsecptb_samecone_is",   dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_is_hu","Events");
    fGeneraldimuxsecptb_samecone_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_is_hl","hl dimuxsecptb_samecone_is",   dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_is_hl","Events");
    fGeneraldimuxsecptb_samecone_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_nis_lu","lu dimuxsecptb_samecone_nis",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_nis_lu","Events");
    fGeneraldimuxsecptb_samecone_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_nis_ll","ll dimuxsecptb_samecone_nis",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_nis_ll","Events");
    fGeneraldimuxsecptb_samecone_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_nis_hu","hu dimuxsecptb_samecone_nis",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_nis_hu","Events");
    fGeneraldimuxsecptb_samecone_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_samecone_nis_hl","hl dimuxsecptb_samecone_nis",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"#dimuxsecptb_samecone_nis_hl","Events");

    fGeneraldimuxsecptb_asym    = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym"," dimuxsecptb_asym",            dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym","Events");
    fGeneraldimuxsecptb_asym_is_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_is_lu","lu dimuxsecptb_asym_is",   dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_is_lu","Events");
    fGeneraldimuxsecptb_asym_is_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_is_ll","ll dimuxsecptb_asym_is",   dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_is_ll","Events");
    fGeneraldimuxsecptb_asym_is_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_is_hu","hu dimuxsecptb_asym_is",   dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_is_hu","Events");
    fGeneraldimuxsecptb_asym_is_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_is_hl","hl dimuxsecptb_asym_is",   dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_is_hl","Events");
    fGeneraldimuxsecptb_asym_nis_lu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_nis_lu","lu dimuxsecptb_asym_nis",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_nis_lu","Events");
    fGeneraldimuxsecptb_asym_nis_ll = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_nis_ll","ll dimuxsecptb_asym_nis",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_nis_ll","Events");
    fGeneraldimuxsecptb_asym_nis_hu = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_nis_hu","hu dimuxsecptb_asym_nis",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_nis_hu","Events");
    fGeneraldimuxsecptb_asym_nis_hl = gHistogrammer->TH1DVarFactory("DIMuon","dimuxsecptb_asym_nis_hl","hl dimuxsecptb_asym_nis",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"#dimuxsecptb_asym_nis_hl","Events");

    if( gCards->GetDoEfficiency()) {
      fGeneralTriggerType = gHistogrammer->TH1DLabelFactory("DIMuon","TriggerType","Trigger Type",triggertype,"","Events");

      fGeneralMV_MuonPt = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPt","p_{T}^{#mu} found by MV",MuonPt_NBins,MuonPt_Bins,"p_{T}^{#mu} [GeV]","Events");
      fGeneralMV_BREMAT_MuonPt = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPt","p_{T}^{#mu} found by MV and BREMAT",MuonPt_NBins,MuonPt_Bins,"p_{T}^{#mu} [GeV]","Events");
      fGeneralMV_MUBAC_MuonPt = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPt","p_{T}^{#mu} found by MV and MUBAC",MuonPt_NBins,MuonPt_Bins,"p_{T}^{#mu} [GeV]","Events");
	
      fGeneralMV_MuonP = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonP","p^{#mu} found by MV",MuonP_NBins,MuonP_Bins,"p^{#mu} [GeV]","Events");
      fGeneralMV_MPMATCH_MuonP = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonP","p^{#mu} found by MV and MPMATCH",MuonP_NBins,MuonP_Bins,"p^{#mu} [GeV]","Events");
      fGeneralMV_MUBAC_MuonP = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonP","p^{#mu} found by MV and MUBAC",MuonP_NBins,MuonP_Bins,"p^{#mu} [GeV]","Events");
	
      fGeneralMV_MuonPz = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPz","p_{z}^{#mu} found by MV",MuonPz_NBins,MuonPz_Bins,"p_{z}^{#mu} [GeV]","Events");
      fGeneralMV_BREMAT_MuonPz = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPz","p_{z}^{#mu} found by MV and BREMAT",MuonPz_NBins,MuonPz_Bins,"p_{z}^{#mu} [GeV]","Events");
      fGeneralMV_MUBAC_MuonPz = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPz","p_{z}^{#mu} found by MV and MUBAC",MuonPz_NBins,MuonPz_Bins,"p_{z}^{#mu} [GeV]","Events");
	
      fGeneralMV_MuonEta = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonEta","#eta^{#mu} found by MV",MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
      fGeneralMV_BREMAT_MuonEta = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonEta","#eta^{#mu} found by MV and BREMAT",MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
      fGeneralMV_MPMATCH_MuonEta = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonEta","#eta^{#mu} found by MV and MPMATCH",MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
      fGeneralMV_MUBAC_MuonEta = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonEta","#eta^{#mu} found by MV and MUBAC",MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
      fGeneralMV_MuonPhi = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPhi","#phi^{#mu} found by MV",MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      fGeneralMV_BREMAT_MuonPhi = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPhi","#phi^{#mu} found by MV and BREMAT",MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      fGeneralMV_MPMATCH_MuonPhi = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonPhi","#phi^{#mu} found by MV and MPMATCH",MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      fGeneralMV_MUBAC_MuonPhi = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPhi","#phi^{#mu} found by MV and MUBAC",MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
	
	
      fGeneralMV_MuonEtaPtBins = new TH1D *[fGeneralMuonPt_NBins_MV];
      fGeneralMV_MuonPhiPtBins = new TH1D *[fGeneralMuonPt_NBins_MV];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MV; ++i ) {
	
	TString name = "MV_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	TString title = "#eta^{#mu} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	fGeneralMV_MuonEtaPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
	
	name = "MV_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	title = "#phi^{#mu} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	fGeneralMV_MuonPhiPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      }
	
      fGeneralMV_BREMAT_MuonEtaPtBins = new TH1D *[fGeneralMuonPt_NBins_BREMAT];
      fGeneralMV_BREMAT_MuonPhiPtBins = new TH1D *[fGeneralMuonPt_NBins_BREMAT];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_BREMAT; ++i ) {
	TString name = "MV_BREMAT_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	TString title = "#eta^{#mu} found by MV and BREMAT for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	fGeneralMV_BREMAT_MuonEtaPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
	
	name = "MV_BREMAT_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	title = "#phi^{#mu} found by MV and BREMAT for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	fGeneralMV_BREMAT_MuonPhiPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      }
	
      fGeneralMV_MPMATCH_MuonEtaPtBins = new TH1D *[fGeneralMuonPt_NBins_BREMAT];
      fGeneralMV_MPMATCH_MuonPhiPtBins = new TH1D *[fGeneralMuonPt_NBins_BREMAT];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_BREMAT; ++i ) {
	TString name = "MV_MPMATCH_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	TString title = "#eta^{#mu} found by MV and MPMATCH for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	fGeneralMV_MPMATCH_MuonEtaPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
	
	name = "MV_MPMATCH_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	title = "#phi^{#mu} found by MV and MPMATCH for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	fGeneralMV_MPMATCH_MuonPhiPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      }
	
      fGeneralMV_MUBAC_MuonEtaPtBins = new TH1D *[fGeneralMuonPt_NBins_MUBAC];
      fGeneralMV_MUBAC_MuonPhiPtBins = new TH1D *[fGeneralMuonPt_NBins_MUBAC];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MUBAC; ++i ) {
	TString name = "MV_MUBAC_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	TString title = "#eta^{#mu} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonEtaPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins,MuonEta_Bins,"#eta^{#mu}","Events");
	
	name = "MV_MUBAC_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	title = "#phi^{#mu} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	title.Append(" #leq p_{T}^{#mu} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonPhiPtBins[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins,MuonPhi_Bins,"#phi^{#mu}","Events");
      }
	
      fGeneralMV_MuonP_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonP_Forward","p^{#mu,forward} found by MV",MuonP_NBins_Forward,MuonP_Bins_Forward,"p^{#mu,forward} [GeV]","Events");
      fGeneralMV_MPMATCH_MuonP_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonP_Forward","p^{#mu,forward} found by MV and MPMATCH",MuonP_NBins_Forward,MuonP_Bins_Forward,"p^{#mu,forward} [GeV]","Events");
      fGeneralMV_MUBAC_MuonP_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonP_Forward","p^{#mu,forward} found by MV and MUBAC",MuonP_NBins_Forward,MuonP_Bins_Forward,"p^{#mu,forward} [GeV]","Events");
      fGeneralMV_MuonPt_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPt_Forward","p_{T}^{#mu,forward} found by MV",MuonPt_NBins_Forward,MuonPt_Bins_Forward,"p_}T}^{#mu,forward} [GeV]","Events");
      fGeneralMV_MPMATCH_MuonPt_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonPt_Forward","p_{T}^{#mu,forward} found by MV and MPMATCH",MuonPt_NBins_Forward,MuonPt_Bins_Forward,"p_{T}^{#mu,forward} [GeV]","Events");
      fGeneralMV_MUBAC_MuonPt_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPt_Forward","p_{T}^{#mu,forward} found by MV and MUBAC",MuonPt_NBins_Forward,MuonPt_Bins_Forward,"p_{T}^{#mu,forward} [GeV]","Events");
      fGeneralMV_MuonEta_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonEta_Forward","#eta^{#mu,forward} found by MV",MuonEta_NBins_Forward,MuonEta_Bins_Forward,"#eta^{#mu,forward}","Events");
      fGeneralMV_MPMATCH_MuonEta_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonEta_Forward","#eta^{#mu,forward} found by MV and MPMATCH",MuonEta_NBins_Forward,MuonEta_Bins_Forward,"#eta^{#mu,forward}","Events");
      fGeneralMV_MUBAC_MuonEta_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonEta_Forward","#eta^{#mu,forward} found by MV and MUBAC",MuonEta_NBins_Forward,MuonEta_Bins_Forward,"#eta^{#mu,forward}","Events");
      fGeneralMV_MuonPhi_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPhi_Forward","#phi^{#mu,forward} found by MV",MuonPhi_NBins_Forward,MuonPhi_Bins_Forward,"#phi^{#mu,forward}","Events");
      fGeneralMV_MPMATCH_MuonPhi_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MPMATCH_MuonPhi_Forward","#phi^{#mu,forward} found by MV and MPMATCH",MuonPhi_NBins_Forward,MuonPhi_Bins_Forward,"#phi^{#mu,forward}","Events");
      fGeneralMV_MUBAC_MuonPhi_Forward = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPhi_Forward","#phi^{#mu,forward} found by MV and MUBAC",MuonPhi_NBins_Forward,MuonPhi_Bins_Forward,"#phi^{#mu,forward}","Events");
	
	
      fGeneralMV_MuonEtaPBins_Forward = new TH1D *[fGeneralMuonP_NBins_MV];
      fGeneralMV_MuonPhiPBins_Forward = new TH1D *[fGeneralMuonP_NBins_MV];
      for ( Int_t i = 0; i < fGeneralMuonP_NBins_MV; ++i ) {
	TString name = "MV_MuonEtaPBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i+1],0,2));
	name.Append("_Forward");
	TString title = "#eta^{#mu,forward} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i],0,2));
	title.Append(" #leq p^{#mu,forward} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i+1],0,2));
	fGeneralMV_MuonEtaPBins_Forward[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Forward,MuonEta_Bins_Forward,"#eta^{#mu,forward}","Events");
	
	name = "MV_MuonPhiPBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i+1],0,2));
	name.Append("_Forward");
	title = "#phi^{#mu,forward} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i],0,2));
	title.Append(" #leq p^{#mu,forward} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MV[i+1],0,2));
	fGeneralMV_MuonPhiPBins_Forward[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Forward,MuonPhi_Bins_Forward,"#phi^{#mu,forward}","Events");
      }
	
      fGeneralMV_MPMATCH_MuonEtaPBins_Forward = new TH1D *[fGeneralMuonP_NBins_MPMATCH];
      fGeneralMV_MPMATCH_MuonPhiPBins_Forward = new TH1D *[fGeneralMuonP_NBins_MPMATCH];
      for ( Int_t i = 0; i < fGeneralMuonP_NBins_MPMATCH; ++i ) {
	TString name = "MV_MPMATCH_MuonEtaPBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i+1],0,2));
	name.Append("_Forward");
	TString title = "#eta^{#mu,forward} found by MV and MPMATCH for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i],0,2));
	title.Append(" #leq p^{#mu,forward} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i+1],0,2));
	fGeneralMV_MPMATCH_MuonEtaPBins_Forward[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Forward,MuonEta_Bins_Forward,"#eta^{#mu,forward}","Events");
	
	name = "MV_MPMATCH_MuonPhiPBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i+1],0,2));
	name.Append("_Forward");
	title = "#phi^{#mu,forward} found by MV and MPMATCH for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i],0,2));
	title.Append(" #leq p^{#mu,forward} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MPMATCH[i+1],0,2));
	fGeneralMV_MPMATCH_MuonPhiPBins_Forward[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Forward,MuonPhi_Bins_Forward,"#phi^{#mu,forward}","Events");
      }
	
      fGeneralMV_MUBAC_MuonEtaPBins_Forward = new TH1D *[fGeneralMuonP_NBins_MUBAC];
      fGeneralMV_MUBAC_MuonPhiPBins_Forward = new TH1D *[fGeneralMuonP_NBins_MUBAC];
      for ( Int_t i = 0; i < fGeneralMuonP_NBins_MUBAC; ++i ) {
	TString name = "MV_MUBAC_MuonEtaPBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i+1],0,2));
	name.Append("_Forward");
	TString title = "#eta^{#mu,forward} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i],0,2));
	title.Append(" #leq p^{#mu,forward} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonEtaPBins_Forward[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Forward,MuonEta_Bins_Forward,"#eta^{#mu,forward}","Events");
	
	name = "MV_MUBAC_MuonPhiPBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i+1],0,2));
	name.Append("_Forward");
	title = "#phi^{#mu,forward} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i],0,2));
	title.Append(" #leq p^{#mu,forward} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonP_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonPhiPBins_Forward[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Forward,MuonPhi_Bins_Forward,"#phi^{#mu,forward}","Events");
      }
	
      fGeneralMV_MuonPt_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPt_Barrel","p_{T}^{#mu,barrel} found by MV",MuonPt_NBins_Barrel,MuonPt_Bins_Barrel,"p_{T}^{#mu,barrel} [GeV]","Events");
      fGeneralMV_BREMAT_MuonPt_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPt_Barrel","p_{T}^{#mu,barrel} found by MV and BREMAT",MuonPt_NBins_Barrel,MuonPt_Bins_Barrel,"p_{T}^{#mu,barrel} [GeV]","Events");
      fGeneralMV_MUBAC_MuonPt_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPt_Barrel","p_{T}^{#mu,barrel} found by MV and MUBAC",MuonPt_NBins_Barrel,MuonPt_Bins_Barrel,"p_{T}^{#mu,barrel} [GeV]","Events");
	
      fGeneralMV_MuonEta_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonEta_Barrel","#eta^{#mu,barrel} found by MV",MuonEta_NBins_Barrel,MuonEta_Bins_Barrel,"#eta^{#mu,barrel}","Events");
      fGeneralMV_BREMAT_MuonEta_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonEta_Barrel","#eta^{#mu,barrel} found by MV and BREMAT",MuonEta_NBins_Barrel,MuonEta_Bins_Barrel,"#eta^{#mu,barrel}","Events");
      fGeneralMV_MUBAC_MuonEta_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonEta_Barrel","#eta^{#mu,barrel} found by MV and MUBAC",MuonEta_NBins_Barrel,MuonEta_Bins_Barrel,"#eta^{#mu,barrel}","Events");
      fGeneralMV_MuonPhi_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPhi_Barrel","#phi^{#mu,barrel} found by MV",MuonPhi_NBins_Barrel,MuonPhi_Bins_Barrel,"#phi^{#mu,barrel}","Events");
      fGeneralMV_BREMAT_MuonPhi_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPhi_Barrel","#phi^{#mu,barrel} found by MV and BREMAT",MuonPhi_NBins_Barrel,MuonPhi_Bins_Barrel,"#phi^{#mu,barrel}","Events");
      fGeneralMV_MUBAC_MuonPhi_Barrel = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPhi_Barrel","#phi^{#mu,barrel} found by MV and MUBAC",MuonPhi_NBins_Barrel,MuonPhi_Bins_Barrel,"#phi^{#mu,barrel}","Events");
	
	
      fGeneralMV_MuonEtaPtBins_Barrel = new TH1D *[fGeneralMuonPt_NBins_MV];
      fGeneralMV_MuonPhiPtBins_Barrel = new TH1D *[fGeneralMuonPt_NBins_MV];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MV; ++i ) {

	TString name = "MV_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	name.Append("_Barrel");
	TString title = "#eta^{#mu,barrel} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	title.Append(" #leq p_{T}^{#mu,barrel} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	fGeneralMV_MuonEtaPtBins_Barrel[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Barrel,MuonEta_Bins_Barrel,"#eta^{#mu,barrel}","Events");
	
	name = "MV_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	name.Append("_Barrel");
	title = "#phi^{#mu,barrel} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i],0,2));
	title.Append(" #leq p_{T}^{#mu,barrel} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MV[i+1],0,2));
	fGeneralMV_MuonPhiPtBins_Barrel[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Barrel,MuonPhi_Bins_Barrel,"#phi^{#mu,barrel}","Events");
      }
	
      fGeneralMV_BREMAT_MuonEtaPtBins_Barrel = new TH1D *[fGeneralMuonPt_NBins_BREMAT];
      fGeneralMV_BREMAT_MuonPhiPtBins_Barrel = new TH1D *[fGeneralMuonPt_NBins_BREMAT];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_BREMAT; ++i ) {
	TString name = "MV_BREMAT_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	name.Append("_Barrel");
	TString title = "#eta^{#mu,barrel} found by MV and BREMAT for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{T}^{#mu,barrel} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	fGeneralMV_BREMAT_MuonEtaPtBins_Barrel[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Barrel,MuonEta_Bins_Barrel,"#eta^{#mu,barrel}","Events");
	
	name = "MV_BREMAT_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	name.Append("_Barrel");
	title = "#phi^{#mu,barrel} found by MV and BREMAT for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{T}^{#mu,barrel} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_BREMAT[i+1],0,2));
	fGeneralMV_BREMAT_MuonPhiPtBins_Barrel[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Barrel,MuonPhi_Bins_Barrel,"#phi^{#mu,barrel}","Events");
      }
	
      fGeneralMV_MUBAC_MuonEtaPtBins_Barrel = new TH1D *[fGeneralMuonPt_NBins_MUBAC];
      fGeneralMV_MUBAC_MuonPhiPtBins_Barrel = new TH1D *[fGeneralMuonPt_NBins_MUBAC];
      for ( Int_t i = 0; i < fGeneralMuonPt_NBins_MUBAC; ++i ) {
	TString name = "MV_MUBAC_MuonEtaPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	name.Append("_Barrel");
	TString title = "#eta^{#mu,barrel} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	title.Append(" #leq p_{T}^{#mu,barrel} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonEtaPtBins_Barrel[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Barrel,MuonEta_Bins_Barrel,"#eta^{#mu,barrel}","Events");
	
	name = "MV_MUBAC_MuonPhiPtBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	name.Append("_Barrel");
	title = "#phi^{#mu,barrel} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i],0,2));
	title.Append(" #leq p_{T}^{#mu,barrel} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPt_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonPhiPtBins_Barrel[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Barrel,MuonPhi_Bins_Barrel,"#phi^{#mu,barrel}","Events");
      }
	
      fGeneralMV_MuonPz_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPz_Rear","p_{z}^{#mu,rear} found by MV",MuonPz_NBins_Rear,MuonPz_Bins_Rear,"p_{z}^{#mu,rear} [GeV]","Events");
      fGeneralMV_BREMAT_MuonPz_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPz_Rear","p_{z}^{#mu,rear} found by MV and BREMAT",MuonPz_NBins_Rear,MuonPz_Bins_Rear,"p_{z}^{#mu,rear} [GeV]","Events");
      fGeneralMV_MUBAC_MuonPz_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPz_Rear","p_{z}^{#mu,rear} found by MV and MUBAC",MuonPz_NBins_Rear,MuonPz_Bins_Rear,"p_{z}^{#mu,rear} [GeV]","Events");
      fGeneralMV_MuonPt_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPt_Rear","p_{T}^{#mu,rear} found by MV",MuonPt_NBins_Rear,MuonPt_Bins_Rear,"p_{T}^{#mu,rear} [GeV]","Events");
      fGeneralMV_BREMAT_MuonPt_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPt_Rear","p_{T}^{#mu,rear} found by MV and BREMAT",MuonPt_NBins_Rear,MuonPt_Bins_Rear,"p_{T}^{#mu,rear} [GeV]","Events");
      fGeneralMV_MUBAC_MuonPt_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPt_Rear","p_{T}^{#mu,rear} found by MV and MUBAC",MuonPt_NBins_Rear,MuonPt_Bins_Rear,"p_{T}^{#mu,rear} [GeV]","Events");
	
      fGeneralMV_MuonEta_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonEta_Rear","#eta^{#mu,rear} found by MV",MuonEta_NBins_Rear,MuonEta_Bins_Rear,"#eta^{#mu,rear}","Events");
      fGeneralMV_BREMAT_MuonEta_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonEta_Rear","#eta^{#mu,rear} found by MV and BREMAT",MuonEta_NBins_Rear,MuonEta_Bins_Rear,"#eta^{#mu,rear}","Events");
      fGeneralMV_MUBAC_MuonEta_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonEta_Rear","#eta^{#mu,rear} found by MV and MUBAC",MuonEta_NBins_Rear,MuonEta_Bins_Rear,"#eta^{#mu,rear}","Events");
      fGeneralMV_MuonPhi_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MuonPhi_Rear","#phi^{#mu,rear} found by MV",MuonPhi_NBins_Rear,MuonPhi_Bins_Rear,"#phi^{#mu,rear}","Events");
      fGeneralMV_BREMAT_MuonPhi_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_BREMAT_MuonPhi_Rear","#phi^{#mu,rear} found by MV and BREMAT",MuonPhi_NBins_Rear,MuonPhi_Bins_Rear,"#phi^{#mu,rear}","Events");
      fGeneralMV_MUBAC_MuonPhi_Rear = gHistogrammer->TH1DVarFactory("DIMuon","MV_MUBAC_MuonPhi_Rear","#phi^{#mu,rear} found by MV and MUBAC",MuonPhi_NBins_Rear,MuonPhi_Bins_Rear,"#phi^{#mu,rear}","Events");
	
      fGeneralMV_MuonEtaPzBins_Rear = new TH1D *[fGeneralMuonPz_NBins_MV];
      fGeneralMV_MuonPhiPzBins_Rear = new TH1D *[fGeneralMuonPz_NBins_MV];
      for ( Int_t i = 0; i < fGeneralMuonPz_NBins_MV; ++i ) {
	TString name = "MV_MuonEtaPzBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i+1],0,2));
	name.Append("_Rear");
	TString title = "#eta^{#mu,rear} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i],0,2));
	title.Append(" #leq p_{z}^{#mu,rear} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i+1],0,2));
	fGeneralMV_MuonEtaPzBins_Rear[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Rear,MuonEta_Bins_Rear,"#eta^{#mu,rear}","Events");
	
	name = "MV_MuonPhiPzBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i+1],0,2));
	name.Append("_Rear");
	title = "#phi^{#mu,rear} found by MV for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i],0,2));
	title.Append(" #leq p_{z}^{#mu,rear} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MV[i+1],0,2));
	fGeneralMV_MuonPhiPzBins_Rear[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Rear,MuonPhi_Bins_Rear,"#phi^{#mu,rear}","Events");
      }
	
      fGeneralMV_BREMAT_MuonEtaPzBins_Rear = new TH1D *[fGeneralMuonPz_NBins_BREMAT];
      fGeneralMV_BREMAT_MuonPhiPzBins_Rear = new TH1D *[fGeneralMuonPz_NBins_BREMAT];
      for ( Int_t i = 0; i < fGeneralMuonPz_NBins_BREMAT; ++i ) {
	TString name = "MV_BREMAT_MuonEtaPzBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i+1],0,2));
	name.Append("_Rear");
	TString title = "#eta^{#mu,rear} found by MV and BREMAT for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{z}^{#mu,rear} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i+1],0,2));
	fGeneralMV_BREMAT_MuonEtaPzBins_Rear[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Rear,MuonEta_Bins_Rear,"#eta^{#mu,rear}","Events");
	
	name = "MV_BREMAT_MuonPhiPzBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i+1],0,2));
	name.Append("_Rear");
	title = "#phi^{#mu,rear} found by MV and BREMAT for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i],0,2));
	title.Append(" #leq p_{z}^{#mu,rear} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_BREMAT[i+1],0,2));
	fGeneralMV_BREMAT_MuonPhiPzBins_Rear[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Rear,MuonPhi_Bins_Rear,"#phi^{#mu,rear}","Events");
      }
	
      fGeneralMV_MUBAC_MuonEtaPzBins_Rear = new TH1D *[fGeneralMuonPz_NBins_MUBAC];
      fGeneralMV_MUBAC_MuonPhiPzBins_Rear = new TH1D *[fGeneralMuonPz_NBins_MUBAC];
      for ( Int_t i = 0; i < fGeneralMuonPz_NBins_MUBAC; ++i ) {
	TString name = "MV_MUBAC_MuonEtaPzBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i+1],0,2));
	name.Append("_Rear");
	TString title = "#eta^{#mu,rear} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i],0,2));
	title.Append(" #leq p_{z}^{#mu,rear} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonEtaPzBins_Rear[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonEta_NBins_Rear,MuonEta_Bins_Rear,"#eta^{#mu,rear}","Events");
	
	name = "MV_MUBAC_MuonPhiPzBins_";
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i],0,2));
	name.Append("_");
	name.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i+1],0,2));
	name.Append("_Rear");
	title = "#phi^{#mu,rear} found by MV and MUBAC for ";
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i],0,2));
	title.Append(" #leq p_{z}^{#mu,rear} #leq ");
	title.Append(gInclude->FormatedDouble(fGeneralMuonPz_Bins_MUBAC[i+1],0,2));
	fGeneralMV_MUBAC_MuonPhiPzBins_Rear[i] = gHistogrammer->TH1DVarFactory("DIMuon",name,title,MuonPhi_NBins_Rear,MuonPhi_Bins_Rear,"#phi^{#mu,rear}","Events");
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::FillGeneral() {
  //
  // fill general histograms
  if( gDebug ) cout << endl << "GDIMuons::FillGeneral() called" << endl << endl;

  if( gCards->GetDIMUONGeneral()) {

    fGeneralNperEv_uncut->Fill(fNDIMuons,gHeader->GetWeight());

    if( gHeader->GetAllCuts()) {
      fGeneralNperEv->Fill(fNChosenDIMuons,gHeader->GetWeight());
    }
  }

  return kTRUE;
}

//_____________________________________________________________

TString GDIMuons::PrintMessage(TString option) {
  //
  // return print message
  if( gDebug ) cout << endl << "GDIMuons::PrintMessage() called" << endl << endl;

  TString dummy = "";

  GDIMuon *dimuon = 0;

  for ( Int_t i = 0; i < fNDIMuons; i++ ) {
    dimuon = ((GDIMuon*)(fDIMuons->At(i)));
    dummy.Append(dimuon->PrintMessage(option));
  }

  return dummy;
}

//_____________________________________________________________

Bool_t GDIMuons::Print(TString option) {
  //
  // print message
  if( gDebug ) cout << endl << "GDIMuons::Print() called" << endl << endl;

  option.ToUpper();

  GDIMuon *dimuon = 0;

  if( option.Contains("OUTPUTLIST")) {
    if( option.Contains("DIMUONS") || option.Contains("ALL")) {
      gLister->FillOutputList("DIMuons:\n\n");
      for ( Int_t i = 0; i < fNDIMuons; i++ ) {
	dimuon = ((GDIMuon*)(fDIMuons->At(i)));
	dimuon->Print(option);
      }
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "DIMuons:" << endl << endl;;
    for ( Int_t i = 0; i < fNDIMuons; i++ ) {
      dimuon = ((GDIMuon*)(fDIMuons->At(i)));
      dimuon->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

GDIMuon* GDIMuons::GetDIMuon(Int_t index) {
  //
  // return dimuon parameters of the dimuon with index
  if( gDebug ) cout << endl << "GDIMuons::GetDIMuon called" << endl << endl;

  if( (index < fNDIMuons) && (index >= 0)) {
    return ((GDIMuon*)(fDIMuons->At(index)));
  } else {
    if( gCards->GetDIMUONNDimuons() > 0 ) {
      TString msg = "GDIMuons::GetDIMuon: requested dimuon index: ";
      msg += index;
      msg.Append(" is larger that total number of dimuons: ");
      msg += fNDIMuons;
      gLister->FillErrorList(msg.Data());
    } 
    return 0;
  }
}

//_____________________________________________________________

GDIMuon* GDIMuons::GetChosen() {
  //
  // return chosen dimuon
  if( gDebug ) cout << endl << "GDIMuons::GetChosen called" << endl << endl;

  GDIMuon *dimuon = 0;

  for ( Int_t i = 0; i < fNDIMuons; i++ ) {
    dimuon = ((GDIMuon*)(fDIMuons->At(i)));
    if( dimuon->GetType() == kChosenDIMuon )
      return dimuon;
  }

  return 0;

}

//_____________________________________________________________

Bool_t GDIMuons::FillPlotMuonPt(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with pt from appropriate muons from dimuon
  //
  // options:
  //
  // ALL: fill if muon is found by mv and or of all finders except mv
  // BREMAT: fill if muon is found by mv and bremat
  // BREMINOUT: fill if muon is found by mv and bremat using inner and outer chambers
  // MPMATCH: fill if muon is found by mv and (mpmatch || mufo)
  // MUBAC: fill if muon is found by mv and mubac
  // MUFO: fill if muon is found by mv and mufo
  // MV: fill if muon is found by mv and mv
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonPt called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	tofill = muon->Pt();
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Pt();
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	tofill = muon->Pt();
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	tofill = muon->Pt();
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	tofill = muon->Pt();
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	tofill = muon->Pt();
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	tofill = muon->Pt();
      }
    }
    if( histo != 0 ) {
      if( (tofill >= min) && (tofill <= max)) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonP(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with p from appropriate muons from dimuon
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonP called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	tofill = muon->P();
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->P();
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	tofill = muon->P();
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	tofill = muon->P();
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	tofill = muon->P();
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	tofill = muon->P();
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	tofill = muon->P();
      }
    }
    if( histo != 0 ) {
      if( (tofill >= min) && (tofill <= max)) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonPz(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with pz from appropriate muons from dimuon
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonPz called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	tofill = muon->Pz();
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Pz();
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	tofill = muon->Pz();
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	tofill = muon->Pz();
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	tofill = muon->Pz();
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	tofill = muon->Pz();
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	tofill = muon->Pz();
      }
    }
    if( histo != 0 ) {
      if( (tofill >= min) && (tofill <= max)) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonEta(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with eta from appropriate muons from dimuon
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonEta called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	tofill = muon->Eta();
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Eta();
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	tofill = muon->Eta();
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	tofill = muon->Eta();
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	tofill = muon->Eta();
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	tofill = muon->Eta();
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	tofill = muon->Eta();
      }
    }
    if( histo != 0 ) {
      if( (tofill >= min) && (tofill <= max)) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonPhi(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max) {
  //
  // fill plot with phi from appropriate muons from dimuon
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonPhi called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	tofill = muon->Phi();
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	tofill = muon->Phi();
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	tofill = muon->Phi();
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	tofill = muon->Phi();
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	tofill = muon->Phi();
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	tofill = muon->Phi();
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	tofill = muon->Phi();
      }
    }
    if( histo != 0 ) {
      if( (tofill >= min) && (tofill <= max)) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonEtaPtBins(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with eta from appropriate muons from dimuon in bins of muon pt
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonEtaPtBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    }
    if( histo != 0 ) {
      if( tofill !=  -999999999.99) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonPhiPtBins(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with phi from appropriate muons from dimuon in bins of muon pt
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonPhiPtBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	if( (muon->Pt() > min) && (muon->Pt() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    }
    if( histo != 0 ) {
      if( tofill != -999999999.99 ) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonEtaPBins(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with eta from appropriate muons from dimuon in bins of muon pt
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonEtaPBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    }
    if( histo != 0 ) {
      if( tofill !=  -999999999.99) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonPhiPBins(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with phi from appropriate muons from dimuon in bins pf muon pt
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonPhiPBins called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	if( (muon->P() > min) && (muon->P() <= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    }
    if( histo != 0 ) {
      if( tofill != -999999999.99 ) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonEtaPzBins(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with eta from appropriate muons from dimuon in bins of muon pt
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonEtaPz called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Eta();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Eta();
	}
      }
    }
    if( histo != 0 ) {
      if( tofill !=  -999999999.99) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::FillPlotMuonPhiPzBins(GDIMuon *dimuon, TH1D* histo, TString option, Double_t min, Double_t max, Int_t currentBin, Int_t maxBin) {
  //
  // fill plot with phi from appropriate muons from dimuon in bins of muon pt
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
  if( gDebug ) cout << endl << "GDIMuons::FillPlotMuonPhiPz called" << endl << endl;

  option.ToUpper();

  // fill list with muons to fill in histo
  TList *muons = new TList();
  GMuon *muon1 = dimuon->GetMuon1();
  GMuon *muon2 = dimuon->GetMuon2();
  if( dimuon->GetTriggerType() == kTakeBoth ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon1);
      muons->Add(muon2);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon1 ) {
    if( option.Contains("FORWARD")) {
      if( muon1->GetType() == kForward )
	muons->Add(muon1);
    } else if( option.Contains("BARREL")) {
      if( muon1->GetType() == kBarrel )
	muons->Add(muon1);
    } else if( option.Contains("REAR")) {
      if( muon1->GetType() == kRear )
	muons->Add(muon1);
    } else {
      muons->Add(muon1);
    }
  } else if( dimuon->GetTriggerType() == kTakeMuon2 ) {
    if( option.Contains("FORWARD")) {
      if( muon2->GetType() == kForward )
	muons->Add(muon2);
    } else if( option.Contains("BARREL")) {
      if( muon2->GetType() == kBarrel )
	muons->Add(muon2);
    } else if( option.Contains("REAR")) {
      if( muon2->GetType() == kRear )
	muons->Add(muon2);
    } else {
      muons->Add(muon2);
    }
  }

  // loop over list and fill histo according to option
  TIter nextmuon(muons);
  while ( GMuon *muon = (GMuon*)nextmuon()) {
    Double_t tofill = -999999999.99;
    if( option.Contains("ALL")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetAllExcpMv()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("BREMAT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBremat() && muon->GetBrematCut()  ) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("BREMINOUT")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetBrematInnerOuter()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MPMATCH")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMPMatchCut()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MUBAC")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMuBac() && muon->GetMUBACCut()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MUFO")) {
      if( dimuon->GetMuonsAllCuts() && muon->GetMv() && muon->GetMufo()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    } else if( option.Contains("MV")) {
      if( dimuon->GetMuonsMVCuts() && muon->GetMv()) {
	if( (muon->Pz() < min) && (muon->Pz() >= max )) { 
	  tofill = muon->Phi();
	} else if( (currentBin == maxBin) && (muon->Pt() > max)) {
	  tofill = muon->Phi();
	}
      }
    }
    if( histo != 0 ) {
      if( tofill != -999999999.99 ) {
	if( tofill > (histo->GetBinLowEdge(histo->GetNbinsX())+histo->GetBinWidth(histo->GetNbinsX()))) {
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

Bool_t GDIMuons::InitVariables() {
  //
  // init variables
  if( gDebug ) cout << endl << "GDIMuons::InitVariables() called" << endl << endl;

  // initialize clonesarray
  fDIMuons  = new TClonesArray("GDIMuon",100);
  fNDIMuons = 0;

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

  fDoCalcIsolation = kFALSE;

  fSelectedIndex = -99;

  fNGoodDIMuons = 0;
  fNChosenDIMuons = 0;

  fSecvtx_DL2       = 0.;
  fSecvtx_DL2_err   = 0.;
  fSecvtx_DL2_sign  = 0.;
  fSecvtx_DL2_signp = 0.;
  fSecvtx_DL2_signm = 0.;

  // init arrays
  fGeneralMuonP_NBins_MPMATCH   = 0;
  fGeneralMuonP_Bins_MPMATCH    = 0;
  fGeneralMuonP_NBins_MUBAC     = 0;
  fGeneralMuonP_Bins_MUBAC      = 0;
  fGeneralMuonP_NBins_MV        = 0;
  fGeneralMuonP_Bins_MV         = 0;
  
  fGeneralMuonPt_NBins_BREMAT  = 0;
  fGeneralMuonPt_Bins_BREMAT   = 0;
  fGeneralMuonPt_NBins_MUBAC   = 0;
  fGeneralMuonPt_Bins_MUBAC    = 0;
  fGeneralMuonPt_NBins_MV      = 0;
  fGeneralMuonPt_Bins_MV       = 0;
  
  fGeneralMuonPz_NBins_BREMAT  = 0;
  fGeneralMuonPz_Bins_BREMAT   = 0;
  fGeneralMuonPz_NBins_MUBAC   = 0;
  fGeneralMuonPz_Bins_MUBAC    = 0;
  fGeneralMuonPz_NBins_MV      = 0;
  fGeneralMuonPz_Bins_MV       = 0;
  
  // init general histograms
  fGeneralNperEv_uncut                        = 0;
  fGeneralDIMuonMass_uncut                    = 0;
  fGeneralDIMuonMassLow_uncut                 = 0;
  fGeneralDIMuonMassHigh_uncut                = 0;
  fGeneralDIMuonMass_LikeSign_uncut           = 0;
  fGeneralDIMuonMassLow_LikeSign_uncut        = 0;
  fGeneralDIMuonMassHigh_LikeSign_uncut       = 0;
  fGeneralDIMuonMass_UnlikeSign_uncut         = 0;
  fGeneralDIMuonMassLow_UnlikeSign_uncut      = 0;
  fGeneralDIMuonMassHigh_UnlikeSign_uncut     = 0;

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
  fGeneraldimuphi_uncut                       = 0;
  fGeneraldimuphi_lu_is_uncut                 = 0;
  fGeneraldimuphi_ll_is_uncut                 = 0;
  fGeneraldimuphi_hu_is_uncut                 = 0;
  fGeneraldimuphi_hl_is_uncut                 = 0;
  fGeneraldimuphi_lu_nis_uncut                = 0;
  fGeneraldimuphi_ll_nis_uncut                = 0;
  fGeneraldimuphi_hu_nis_uncut                = 0;
  fGeneraldimuphi_hl_nis_uncut                = 0;
  fGeneraldimueta_uncut                       = 0;
  fGeneraldimueta_lu_is_uncut                 = 0;
  fGeneraldimueta_ll_is_uncut                 = 0;
  fGeneraldimueta_hu_is_uncut                 = 0;
  fGeneraldimueta_hl_is_uncut                 = 0;
  fGeneraldimueta_lu_nis_uncut                = 0;
  fGeneraldimueta_ll_nis_uncut                = 0;
  fGeneraldimueta_hu_nis_uncut                = 0;
  fGeneraldimueta_hl_nis_uncut                = 0;
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
  fGeneraldimupt_uncut                        = 0;
  fGeneraldimupt_lu_is_uncut                  = 0;
  fGeneraldimupt_ll_is_uncut                  = 0;
  fGeneraldimupt_hu_is_uncut                  = 0;
  fGeneraldimupt_hl_is_uncut                  = 0;
  fGeneraldimupt_lu_nis_uncut                 = 0;
  fGeneraldimupt_ll_nis_uncut                 = 0;
  fGeneraldimupt_hu_nis_uncut                 = 0;
  fGeneraldimupt_hl_nis_uncut                 = 0;
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

  fGeneralVtxMass_uncut                       = 0;
  fGeneralVtxMass_is_lu_uncut                 = 0;
  fGeneralVtxMass_is_ll_uncut                 = 0;  
  fGeneralVtxMass_is_hu_uncut                 = 0;
  fGeneralVtxMass_is_hl_uncut                 = 0;
  fGeneralVtxMass_nis_lu_uncut                = 0;
  fGeneralVtxMass_nis_ll_uncut                = 0; 
  fGeneralVtxMass_nis_hu_uncut                = 0;
  fGeneralVtxMass_nis_hl_uncut                = 0;

  fGeneralChi2_uncut                          = 0;
  fGeneralChi2_is_lu_uncut                    = 0;
  fGeneralChi2_is_ll_uncut                    = 0;  
  fGeneralChi2_is_hu_uncut                    = 0;
  fGeneralChi2_is_hl_uncut                    = 0;
  fGeneralChi2_nis_lu_uncut                   = 0;
  fGeneralChi2_nis_ll_uncut                   = 0; 
  fGeneralChi2_nis_hu_uncut                   = 0;
  fGeneralChi2_nis_hl_uncut                   = 0;

  fGeneralNdof_uncut                          = 0;
  fGeneralNdof_is_lu_uncut                    = 0;
  fGeneralNdof_is_ll_uncut                    = 0;  
  fGeneralNdof_is_hu_uncut                    = 0;
  fGeneralNdof_is_hl_uncut                    = 0;
  fGeneralNdof_nis_lu_uncut                   = 0;
  fGeneralNdof_nis_ll_uncut                   = 0; 
  fGeneralNdof_nis_hu_uncut                   = 0;
  fGeneralNdof_nis_hl_uncut                   = 0;

  fGeneralMulti_uncut                         = 0;
  fGeneralMulti_is_lu_uncut                   = 0;
  fGeneralMulti_is_ll_uncut                   = 0;  
  fGeneralMulti_is_hu_uncut                   = 0;
  fGeneralMulti_is_hl_uncut                   = 0;
  fGeneralMulti_nis_lu_uncut                  = 0;
  fGeneralMulti_nis_ll_uncut                  = 0; 
  fGeneralMulti_nis_hu_uncut                  = 0;
  fGeneralMulti_nis_hl_uncut                  = 0;

  fGeneralNrsecvtx_uncut                      = 0;
  fGeneralNrsecvtx_is_lu_uncut                = 0;
  fGeneralNrsecvtx_is_ll_uncut                = 0;  
  fGeneralNrsecvtx_is_hu_uncut                = 0;
  fGeneralNrsecvtx_is_hl_uncut                = 0;
  fGeneralNrsecvtx_nis_lu_uncut               = 0;
  fGeneralNrsecvtx_nis_ll_uncut               = 0; 
  fGeneralNrsecvtx_nis_hu_uncut               = 0;
  fGeneralNrsecvtx_nis_hl_uncut               = 0;

  fGeneralMunphi_uncut                        = 0;
  fGeneralMunphi_is_lu_uncut                  = 0;
  fGeneralMunphi_is_ll_uncut                  = 0;  
  fGeneralMunphi_is_hu_uncut                  = 0;
  fGeneralMunphi_is_hl_uncut                  = 0;
  fGeneralMunphi_nis_lu_uncut                 = 0;
  fGeneralMunphi_nis_ll_uncut                 = 0; 
  fGeneralMunphi_nis_hu_uncut                 = 0;
  fGeneralMunphi_nis_hl_uncut                 = 0;

  fGeneralMundof_uncut                        = 0;
  fGeneralMundof_is_lu_uncut                  = 0;
  fGeneralMundof_is_ll_uncut                  = 0;  
  fGeneralMundof_is_hu_uncut                  = 0;
  fGeneralMundof_is_hl_uncut                  = 0;
  fGeneralMundof_nis_lu_uncut                 = 0;
  fGeneralMundof_nis_ll_uncut                 = 0; 
  fGeneralMundof_nis_hu_uncut                 = 0;
  fGeneralMundof_nis_hl_uncut                 = 0;

  fGeneralMupmat_uncut                        = 0;
  fGeneralMupmat_is_lu_uncut                  = 0;
  fGeneralMupmat_is_ll_uncut                  = 0;  
  fGeneralMupmat_is_hu_uncut                  = 0;
  fGeneralMupmat_is_hl_uncut                  = 0;
  fGeneralMupmat_nis_lu_uncut                 = 0;
  fGeneralMupmat_nis_ll_uncut                 = 0; 
  fGeneralMupmat_nis_hu_uncut                 = 0;
  fGeneralMupmat_nis_hl_uncut                 = 0;

  fGeneralMPMatchID_uncut                     = 0;
  fGeneralMPMatchID_is_lu_uncut               = 0;
  fGeneralMPMatchID_is_ll_uncut               = 0;  
  fGeneralMPMatchID_is_hu_uncut               = 0;
  fGeneralMPMatchID_is_hl_uncut               = 0;
  fGeneralMPMatchID_nis_lu_uncut              = 0;
  fGeneralMPMatchID_nis_ll_uncut              = 0; 
  fGeneralMPMatchID_nis_hu_uncut              = 0;
  fGeneralMPMatchID_nis_hl_uncut              = 0;

  fGeneralMuMvID_uncut                        = 0;
  fGeneralMuMvID_is_lu_uncut                  = 0;
  fGeneralMuMvID_is_ll_uncut                  = 0;  
  fGeneralMuMvID_is_hu_uncut                  = 0;
  fGeneralMuMvID_is_hl_uncut                  = 0;
  fGeneralMuMvID_nis_lu_uncut                 = 0;
  fGeneralMuMvID_nis_ll_uncut                 = 0; 
  fGeneralMuMvID_nis_hu_uncut                 = 0;
  fGeneralMuMvID_nis_hl_uncut                 = 0;

  fGeneralMuMufoID_uncut                      = 0;
  fGeneralMuMufoID_is_lu_uncut                = 0;
  fGeneralMuMufoID_is_ll_uncut                = 0;  
  fGeneralMuMufoID_is_hu_uncut                = 0;
  fGeneralMuMufoID_is_hl_uncut                = 0;
  fGeneralMuMufoID_nis_lu_uncut               = 0;
  fGeneralMuMufoID_nis_ll_uncut               = 0; 
  fGeneralMuMufoID_nis_hu_uncut               = 0;
  fGeneralMuMufoID_nis_hl_uncut               = 0;

  fGeneralMuz_uncut                           = 0;
  fGeneralMuz_is_lu_uncut                     = 0;
  fGeneralMuz_is_ll_uncut                     = 0;  
  fGeneralMuz_is_hu_uncut                     = 0;
  fGeneralMuz_is_hl_uncut                     = 0;
  fGeneralMuz_nis_lu_uncut                    = 0;
  fGeneralMuz_nis_ll_uncut                    = 0; 
  fGeneralMuz_nis_hu_uncut                    = 0;
  fGeneralMuz_nis_hl_uncut                    = 0;

  fGeneralMuBacMatID_uncut                    = 0;
  fGeneralMuBacMatID_is_lu_uncut              = 0;
  fGeneralMuBacMatID_is_ll_uncut              = 0;  
  fGeneralMuBacMatID_is_hu_uncut              = 0;
  fGeneralMuBacMatID_is_hl_uncut              = 0;
  fGeneralMuBacMatID_nis_lu_uncut             = 0;
  fGeneralMuBacMatID_nis_ll_uncut             = 0; 
  fGeneralMuBacMatID_nis_hu_uncut             = 0;
  fGeneralMuBacMatID_nis_hl_uncut             = 0;

  fGeneralNBacMat_uncut                       = 0;
  fGeneralNBacMat_is_lu_uncut                 = 0;
  fGeneralNBacMat_is_ll_uncut                 = 0;  
  fGeneralNBacMat_is_hu_uncut                 = 0;
  fGeneralNBacMat_is_hl_uncut                 = 0;
  fGeneralNBacMat_nis_lu_uncut                = 0;
  fGeneralNBacMat_nis_ll_uncut                = 0; 
  fGeneralNBacMat_nis_hu_uncut                = 0;
  fGeneralNBacMat_nis_hl_uncut                = 0;

  fGeneralBacMat_VCID_uncut                   = 0;
  fGeneralBacMat_VCID_is_lu_uncut             = 0;
  fGeneralBacMat_VCID_is_ll_uncut             = 0;  
  fGeneralBacMat_VCID_is_hu_uncut             = 0;
  fGeneralBacMat_VCID_is_hl_uncut             = 0;
  fGeneralBacMat_VCID_nis_lu_uncut            = 0;
  fGeneralBacMat_VCID_nis_ll_uncut            = 0; 
  fGeneralBacMat_VCID_nis_hu_uncut            = 0;
  fGeneralBacMat_VCID_nis_hl_uncut            = 0;

  fGeneralBacMat_MuBacID_uncut                = 0;
  fGeneralBacMat_MuBacID_is_lu_uncut          = 0;
  fGeneralBacMat_MuBacID_is_ll_uncut          = 0;  
  fGeneralBacMat_MuBacID_is_hu_uncut          = 0;
  fGeneralBacMat_MuBacID_is_hl_uncut          = 0;
  fGeneralBacMat_MuBacID_nis_lu_uncut         = 0;
  fGeneralBacMat_MuBacID_nis_ll_uncut         = 0; 
  fGeneralBacMat_MuBacID_nis_hu_uncut         = 0;
  fGeneralBacMat_MuBacID_nis_hl_uncut         = 0;

  fGeneralBacMat_Istop_uncut                  = 0;
  fGeneralBacMat_Istop_is_lu_uncut            = 0;
  fGeneralBacMat_Istop_is_ll_uncut            = 0;  
  fGeneralBacMat_Istop_is_hu_uncut            = 0;
  fGeneralBacMat_Istop_is_hl_uncut            = 0;
  fGeneralBacMat_Istop_nis_lu_uncut           = 0;
  fGeneralBacMat_Istop_nis_ll_uncut           = 0; 
  fGeneralBacMat_Istop_nis_hu_uncut           = 0;
  fGeneralBacMat_Istop_nis_hl_uncut           = 0;

  fGeneralBacMat_Error_uncut                  = 0;
  fGeneralBacMat_Error_is_lu_uncut            = 0;
  fGeneralBacMat_Error_is_ll_uncut            = 0;  
  fGeneralBacMat_Error_is_hu_uncut            = 0;
  fGeneralBacMat_Error_is_hl_uncut            = 0;
  fGeneralBacMat_Error_nis_lu_uncut           = 0;
  fGeneralBacMat_Error_nis_ll_uncut           = 0; 
  fGeneralBacMat_Error_nis_hu_uncut           = 0;
  fGeneralBacMat_Error_nis_hl_uncut           = 0;

  fGeneralBacMat_Readout_uncut                = 0;
  fGeneralBacMat_Readout_is_lu_uncut          = 0;
  fGeneralBacMat_Readout_is_ll_uncut          = 0;  
  fGeneralBacMat_Readout_is_hu_uncut          = 0;
  fGeneralBacMat_Readout_is_hl_uncut          = 0;
  fGeneralBacMat_Readout_nis_lu_uncut         = 0;
  fGeneralBacMat_Readout_nis_ll_uncut         = 0; 
  fGeneralBacMat_Readout_nis_hu_uncut         = 0;
  fGeneralBacMat_Readout_nis_hl_uncut         = 0;

  fGeneralImpact2D_uncut                      = 0;
  fGeneralImpact2D_is_lu_uncut                = 0;
  fGeneralImpact2D_is_ll_uncut                = 0;  
  fGeneralImpact2D_is_hu_uncut                = 0;
  fGeneralImpact2D_is_hl_uncut                = 0;
  fGeneralImpact2D_nis_lu_uncut               = 0;
  fGeneralImpact2D_nis_ll_uncut               = 0; 
  fGeneralImpact2D_nis_hu_uncut               = 0;
  fGeneralImpact2D_nis_hl_uncut               = 0;

  fGeneralImpact2D_Sign_uncut                 = 0;
  fGeneralImpact2D_Sign_is_lu_uncut           = 0;
  fGeneralImpact2D_Sign_is_ll_uncut           = 0;  
  fGeneralImpact2D_Sign_is_hu_uncut           = 0;
  fGeneralImpact2D_Sign_is_hl_uncut           = 0;
  fGeneralImpact2D_Sign_nis_lu_uncut          = 0;
  fGeneralImpact2D_Sign_nis_ll_uncut          = 0; 
  fGeneralImpact2D_Sign_nis_hu_uncut          = 0;
  fGeneralImpact2D_Sign_nis_hl_uncut          = 0;

  fGeneralDL2_uncut                           = 0;
  fGeneralDL2_is_lu_uncut                     = 0;
  fGeneralDL2_is_ll_uncut                     = 0;  
  fGeneralDL2_is_hu_uncut                     = 0;
  fGeneralDL2_is_hl_uncut                     = 0;
  fGeneralDL2_nis_lu_uncut                    = 0;
  fGeneralDL2_nis_ll_uncut                    = 0; 
  fGeneralDL2_nis_hu_uncut                    = 0;
  fGeneralDL2_nis_hl_uncut                    = 0;

  fGeneralDL2_Sign_uncut                      = 0;
  fGeneralDL2_Sign_is_lu_uncut                = 0;
  fGeneralDL2_Sign_is_ll_uncut                = 0;  
  fGeneralDL2_Sign_is_hu_uncut                = 0;
  fGeneralDL2_Sign_is_hl_uncut                = 0;
  fGeneralDL2_Sign_nis_lu_uncut               = 0;
  fGeneralDL2_Sign_nis_ll_uncut               = 0; 
  fGeneralDL2_Sign_nis_hu_uncut               = 0;
  fGeneralDL2_Sign_nis_hl_uncut               = 0;

  fGeneralDL2_Sign_Mirrp_uncut                = 0;
  fGeneralDL2_Sign_Mirrp_is_lu_uncut          = 0;
  fGeneralDL2_Sign_Mirrp_is_ll_uncut          = 0;  
  fGeneralDL2_Sign_Mirrp_is_hu_uncut          = 0;
  fGeneralDL2_Sign_Mirrp_is_hl_uncut          = 0;
  fGeneralDL2_Sign_Mirrp_nis_lu_uncut         = 0;
  fGeneralDL2_Sign_Mirrp_nis_ll_uncut         = 0; 
  fGeneralDL2_Sign_Mirrp_nis_hu_uncut         = 0;
  fGeneralDL2_Sign_Mirrp_nis_hl_uncut         = 0;

  fGeneralDL2_Sign_Mirrm_uncut                = 0;
  fGeneralDL2_Sign_Mirrm_is_lu_uncut          = 0;
  fGeneralDL2_Sign_Mirrm_is_ll_uncut          = 0;  
  fGeneralDL2_Sign_Mirrm_is_hu_uncut          = 0;
  fGeneralDL2_Sign_Mirrm_is_hl_uncut          = 0;
  fGeneralDL2_Sign_Mirrm_nis_lu_uncut         = 0;
  fGeneralDL2_Sign_Mirrm_nis_ll_uncut         = 0; 
  fGeneralDL2_Sign_Mirrm_nis_hu_uncut         = 0;
  fGeneralDL2_Sign_Mirrm_nis_hl_uncut         = 0;

  fGeneralMuJetDeltaR_uncut                   = 0;
  fGeneralMuJetDeltaR_is_lu_uncut             = 0;
  fGeneralMuJetDeltaR_is_ll_uncut             = 0;  
  fGeneralMuJetDeltaR_is_hu_uncut             = 0;
  fGeneralMuJetDeltaR_is_hl_uncut             = 0;
  fGeneralMuJetDeltaR_nis_lu_uncut            = 0;
  fGeneralMuJetDeltaR_nis_ll_uncut            = 0; 
  fGeneralMuJetDeltaR_nis_hu_uncut            = 0;
  fGeneralMuJetDeltaR_nis_hl_uncut            = 0;

  fGeneralMuJetPt_uncut                       = 0;
  fGeneralMuJetPt_is_lu_uncut                 = 0;
  fGeneralMuJetPt_is_ll_uncut                 = 0;  
  fGeneralMuJetPt_is_hu_uncut                 = 0;
  fGeneralMuJetPt_is_hl_uncut                 = 0;
  fGeneralMuJetPt_nis_lu_uncut                = 0;
  fGeneralMuJetPt_nis_ll_uncut                = 0; 
  fGeneralMuJetPt_nis_hu_uncut                = 0;
  fGeneralMuJetPt_nis_hl_uncut                = 0;

  fGeneralMuJetEt_uncut                       = 0;
  fGeneralMuJetEt_is_lu_uncut                 = 0;
  fGeneralMuJetEt_is_ll_uncut                 = 0;  
  fGeneralMuJetEt_is_hu_uncut                 = 0;
  fGeneralMuJetEt_is_hl_uncut                 = 0;
  fGeneralMuJetEt_nis_lu_uncut                = 0;
  fGeneralMuJetEt_nis_ll_uncut                = 0; 
  fGeneralMuJetEt_nis_hu_uncut                = 0;
  fGeneralMuJetEt_nis_hl_uncut                = 0;

  fGeneralMuJetEta_uncut                      = 0;
  fGeneralMuJetEta_is_lu_uncut                = 0;
  fGeneralMuJetEta_is_ll_uncut                = 0;  
  fGeneralMuJetEta_is_hu_uncut                = 0;
  fGeneralMuJetEta_is_hl_uncut                = 0;
  fGeneralMuJetEta_nis_lu_uncut               = 0;
  fGeneralMuJetEta_nis_ll_uncut               = 0; 
  fGeneralMuJetEta_nis_hu_uncut               = 0;
  fGeneralMuJetEta_nis_hl_uncut               = 0;

  fGeneralMassJet_uncut                       = 0;
  fGeneralMassJet_is_lu_uncut                 = 0;
  fGeneralMassJet_is_ll_uncut                 = 0;  
  fGeneralMassJet_is_hu_uncut                 = 0;
  fGeneralMassJet_is_hl_uncut                 = 0;
  fGeneralMassJet_nis_lu_uncut                = 0;
  fGeneralMassJet_nis_ll_uncut                = 0; 
  fGeneralMassJet_nis_hu_uncut                = 0;
  fGeneralMassJet_nis_hl_uncut                = 0;

  fGeneralNJets_uncut                         = 0;
  fGeneralNJets_is_lu_uncut                   = 0;
  fGeneralNJets_is_ll_uncut                   = 0;  
  fGeneralNJets_is_hu_uncut                   = 0;
  fGeneralNJets_is_hl_uncut                   = 0;
  fGeneralNJets_nis_lu_uncut                  = 0;
  fGeneralNJets_nis_ll_uncut                  = 0; 
  fGeneralNJets_nis_hu_uncut                  = 0;
  fGeneralNJets_nis_hl_uncut                  = 0;

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
  fGeneralDIMuonMass                          = 0;
  fGeneralDIMuonMassLow                       = 0;
  fGeneralDIMuonMassHigh                      = 0;
  fGeneralDIMuonMass_LikeSign                 = 0;
  fGeneralDIMuonMassLow_LikeSign              = 0;
  fGeneralDIMuonMassHigh_LikeSign             = 0;
  fGeneralDIMuonMass_UnlikeSign               = 0;
  fGeneralDIMuonMassLow_UnlikeSign            = 0;
  fGeneralDIMuonMassHigh_UnlikeSign           = 0;

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
  fGeneralDeltaEta_lu_is                      = 0;
  fGeneralDeltaEta_ll_is                      = 0;
  fGeneralDeltaEta_hu_is                      = 0;
  fGeneralDeltaEta_hl_is                      = 0;
  fGeneralDeltaEta_lu_nis                     = 0;
  fGeneralDeltaEta_ll_nis                     = 0;
  fGeneralDeltaEta_hu_nis                     = 0;
  fGeneralDeltaEta_hl_nis                     = 0;
  fGeneralDeltaTheta                          = 0;
  fGeneraldimuphi                             = 0;
  fGeneraldimuphi_lu_is                       = 0;
  fGeneraldimuphi_ll_is                       = 0;
  fGeneraldimuphi_hu_is                       = 0;
  fGeneraldimuphi_hl_is                       = 0;
  fGeneraldimuphi_lu_nis                      = 0;
  fGeneraldimuphi_ll_nis                      = 0;
  fGeneraldimuphi_hu_nis                      = 0;
  fGeneraldimuphi_hl_nis                      = 0;
  fGeneraldimueta                             = 0;
  fGeneraldimueta_lu_is                       = 0;
  fGeneraldimueta_ll_is                       = 0;
  fGeneraldimueta_hu_is                       = 0;
  fGeneraldimueta_hl_is                       = 0;
  fGeneraldimueta_lu_nis                      = 0;
  fGeneraldimueta_ll_nis                      = 0;
  fGeneraldimueta_hu_nis                      = 0;
  fGeneraldimueta_hl_nis                      = 0;
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
  fGeneraldimupt                              = 0;
  fGeneraldimupt_lu_is                        = 0;
  fGeneraldimupt_ll_is                        = 0;
  fGeneraldimupt_hu_is                        = 0;
  fGeneraldimupt_hl_is                        = 0;
  fGeneraldimupt_lu_nis                       = 0;
  fGeneraldimupt_ll_nis                       = 0;
  fGeneraldimupt_hu_nis                       = 0;
  fGeneraldimupt_hl_nis                       = 0;
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

  fGeneralCharge_Like                         = 0;

  fGeneralVertexOvNTracks                     = 0;
  fGeneralVertexOvNTracks_is_lu               = 0;
  fGeneralVertexOvNTracks_is_ll               = 0;  
  fGeneralVertexOvNTracks_is_hu               = 0;
  fGeneralVertexOvNTracks_is_hl               = 0;
  fGeneralVertexOvNTracks_nis_lu              = 0;
  fGeneralVertexOvNTracks_nis_ll              = 0; 
  fGeneralVertexOvNTracks_nis_hu              = 0;
  fGeneralVertexOvNTracks_nis_hl              = 0;

  fGeneralVtxMass                             = 0;
  fGeneralVtxMass_is_lu                       = 0;
  fGeneralVtxMass_is_ll                       = 0;  
  fGeneralVtxMass_is_hu                       = 0;
  fGeneralVtxMass_is_hl                       = 0;
  fGeneralVtxMass_nis_lu                      = 0;
  fGeneralVtxMass_nis_ll                      = 0; 
  fGeneralVtxMass_nis_hu                      = 0;
  fGeneralVtxMass_nis_hl                      = 0;

  fGeneralChi2                                = 0;
  fGeneralChi2_is_lu                          = 0;
  fGeneralChi2_is_ll                          = 0;  
  fGeneralChi2_is_hu                          = 0;
  fGeneralChi2_is_hl                          = 0;
  fGeneralChi2_nis_lu                         = 0;
  fGeneralChi2_nis_ll                         = 0; 
  fGeneralChi2_nis_hu                         = 0;
  fGeneralChi2_nis_hl                         = 0;

  fGeneralNdof                                = 0;
  fGeneralNdof_is_lu                          = 0;
  fGeneralNdof_is_ll                          = 0;  
  fGeneralNdof_is_hu                          = 0;
  fGeneralNdof_is_hl                          = 0;
  fGeneralNdof_nis_lu                         = 0;
  fGeneralNdof_nis_ll                         = 0; 
  fGeneralNdof_nis_hu                         = 0;
  fGeneralNdof_nis_hl                         = 0;

  fGeneralChi2Ndof                            = 0;
  fGeneralChi2Ndof_is_lu                      = 0;
  fGeneralChi2Ndof_is_ll                      = 0;  
  fGeneralChi2Ndof_is_hu                      = 0;
  fGeneralChi2Ndof_is_hl                      = 0;
  fGeneralChi2Ndof_nis_lu                     = 0;
  fGeneralChi2Ndof_nis_ll                     = 0; 
  fGeneralChi2Ndof_nis_hu                     = 0;
  fGeneralChi2Ndof_nis_hl                     = 0;

  fGeneralMulti                               = 0;
  fGeneralMulti_is_lu                         = 0;
  fGeneralMulti_is_ll                         = 0;  
  fGeneralMulti_is_hu                         = 0;
  fGeneralMulti_is_hl                         = 0;
  fGeneralMulti_nis_lu                        = 0;
  fGeneralMulti_nis_ll                        = 0; 
  fGeneralMulti_nis_hu                        = 0;
  fGeneralMulti_nis_hl                        = 0;

  fGeneral_mvtx2_VtxMass                      = 0;
  fGeneral_mvtx2_VtxMass_is_lu                = 0;
  fGeneral_mvtx2_VtxMass_is_ll                = 0;  
  fGeneral_mvtx2_VtxMass_is_hu                = 0;
  fGeneral_mvtx2_VtxMass_is_hl                = 0;
  fGeneral_mvtx2_VtxMass_nis_lu               = 0;
  fGeneral_mvtx2_VtxMass_nis_ll               = 0; 
  fGeneral_mvtx2_VtxMass_nis_hu               = 0;
  fGeneral_mvtx2_VtxMass_nis_hl               = 0;

  fGeneral_mvtx2_Chi2                         = 0;
  fGeneral_mvtx2_Chi2_is_lu                   = 0;
  fGeneral_mvtx2_Chi2_is_ll                   = 0;  
  fGeneral_mvtx2_Chi2_is_hu                   = 0;
  fGeneral_mvtx2_Chi2_is_hl                   = 0;
  fGeneral_mvtx2_Chi2_nis_lu                  = 0;
  fGeneral_mvtx2_Chi2_nis_ll                  = 0; 
  fGeneral_mvtx2_Chi2_nis_hu                  = 0;
  fGeneral_mvtx2_Chi2_nis_hl                  = 0;

  fGeneral_mvtx2_Ndof                         = 0;
  fGeneral_mvtx2_Ndof_is_lu                   = 0;
  fGeneral_mvtx2_Ndof_is_ll                   = 0;  
  fGeneral_mvtx2_Ndof_is_hu                   = 0;
  fGeneral_mvtx2_Ndof_is_hl                   = 0;
  fGeneral_mvtx2_Ndof_nis_lu                  = 0;
  fGeneral_mvtx2_Ndof_nis_ll                  = 0; 
  fGeneral_mvtx2_Ndof_nis_hu                  = 0;
  fGeneral_mvtx2_Ndof_nis_hl                  = 0;

  fGeneral_mvtx2_Chi2Ndof                     = 0;
  fGeneral_mvtx2_Chi2Ndof_is_lu               = 0;
  fGeneral_mvtx2_Chi2Ndof_is_ll               = 0;  
  fGeneral_mvtx2_Chi2Ndof_is_hu               = 0;
  fGeneral_mvtx2_Chi2Ndof_is_hl               = 0;
  fGeneral_mvtx2_Chi2Ndof_nis_lu              = 0;
  fGeneral_mvtx2_Chi2Ndof_nis_ll              = 0; 
  fGeneral_mvtx2_Chi2Ndof_nis_hu              = 0;
  fGeneral_mvtx2_Chi2Ndof_nis_hl              = 0;

  fGeneral_mvtx2_Multi                        = 0;
  fGeneral_mvtx2_Multi_is_lu                  = 0;
  fGeneral_mvtx2_Multi_is_ll                  = 0;  
  fGeneral_mvtx2_Multi_is_hu                  = 0;
  fGeneral_mvtx2_Multi_is_hl                  = 0;
  fGeneral_mvtx2_Multi_nis_lu                 = 0;
  fGeneral_mvtx2_Multi_nis_ll                 = 0; 
  fGeneral_mvtx2_Multi_nis_hu                 = 0;
  fGeneral_mvtx2_Multi_nis_hl                 = 0;

  fGeneralNrsecvtx                            = 0;
  fGeneralNrsecvtx_is_lu                      = 0;
  fGeneralNrsecvtx_is_ll                      = 0;  
  fGeneralNrsecvtx_is_hu                      = 0;
  fGeneralNrsecvtx_is_hl                      = 0;
  fGeneralNrsecvtx_nis_lu                     = 0;
  fGeneralNrsecvtx_nis_ll                     = 0; 
  fGeneralNrsecvtx_nis_hu                     = 0;
  fGeneralNrsecvtx_nis_hl                     = 0;

  fGeneralMunphi                              = 0;
  fGeneralMunphi_is_lu                        = 0;
  fGeneralMunphi_is_ll                        = 0;  
  fGeneralMunphi_is_hu                        = 0;
  fGeneralMunphi_is_hl                        = 0;
  fGeneralMunphi_nis_lu                       = 0;
  fGeneralMunphi_nis_ll                       = 0; 
  fGeneralMunphi_nis_hu                       = 0;
  fGeneralMunphi_nis_hl                       = 0;

  fGeneralMundof                              = 0;
  fGeneralMundof_is_lu                        = 0;
  fGeneralMundof_is_ll                        = 0;  
  fGeneralMundof_is_hu                        = 0;
  fGeneralMundof_is_hl                        = 0;
  fGeneralMundof_nis_lu                       = 0;
  fGeneralMundof_nis_ll                       = 0; 
  fGeneralMundof_nis_hu                       = 0;
  fGeneralMundof_nis_hl                       = 0;

  fGeneralMupmat                              = 0;
  fGeneralMupmat_is_lu                        = 0;
  fGeneralMupmat_is_ll                        = 0;  
  fGeneralMupmat_is_hu                        = 0;
  fGeneralMupmat_is_hl                        = 0;
  fGeneralMupmat_nis_lu                       = 0;
  fGeneralMupmat_nis_ll                       = 0; 
  fGeneralMupmat_nis_hu                       = 0;
  fGeneralMupmat_nis_hl                       = 0;

  fGeneralMPMatchID                           = 0;
  fGeneralMPMatchID_is_lu                     = 0;
  fGeneralMPMatchID_is_ll                     = 0;  
  fGeneralMPMatchID_is_hu                     = 0;
  fGeneralMPMatchID_is_hl                     = 0;
  fGeneralMPMatchID_nis_lu                    = 0;
  fGeneralMPMatchID_nis_ll                    = 0; 
  fGeneralMPMatchID_nis_hu                    = 0;
  fGeneralMPMatchID_nis_hl                    = 0;

  fGeneralMuMvID                              = 0;
  fGeneralMuMvID_is_lu                        = 0;
  fGeneralMuMvID_is_ll                        = 0;  
  fGeneralMuMvID_is_hu                        = 0;
  fGeneralMuMvID_is_hl                        = 0;
  fGeneralMuMvID_nis_lu                       = 0;
  fGeneralMuMvID_nis_ll                       = 0; 
  fGeneralMuMvID_nis_hu                       = 0;
  fGeneralMuMvID_nis_hl                       = 0;

  fGeneralMuMufoID                            = 0;
  fGeneralMuMufoID_is_lu                      = 0;
  fGeneralMuMufoID_is_ll                      = 0;  
  fGeneralMuMufoID_is_hu                      = 0;
  fGeneralMuMufoID_is_hl                      = 0;
  fGeneralMuMufoID_nis_lu                     = 0;
  fGeneralMuMufoID_nis_ll                     = 0; 
  fGeneralMuMufoID_nis_hu                     = 0;
  fGeneralMuMufoID_nis_hl                     = 0;

  fGeneralMuz                                 = 0;
  fGeneralMuz_is_lu                           = 0;
  fGeneralMuz_is_ll                           = 0;  
  fGeneralMuz_is_hu                           = 0;
  fGeneralMuz_is_hl                           = 0;
  fGeneralMuz_nis_lu                          = 0;
  fGeneralMuz_nis_ll                          = 0; 
  fGeneralMuz_nis_hu                          = 0;
  fGeneralMuz_nis_hl                          = 0;

  fGeneralMuBacMatID                          = 0;
  fGeneralMuBacMatID_is_lu                    = 0;
  fGeneralMuBacMatID_is_ll                    = 0;  
  fGeneralMuBacMatID_is_hu                    = 0;
  fGeneralMuBacMatID_is_hl                    = 0;
  fGeneralMuBacMatID_nis_lu                   = 0;
  fGeneralMuBacMatID_nis_ll                   = 0; 
  fGeneralMuBacMatID_nis_hu                   = 0;
  fGeneralMuBacMatID_nis_hl                   = 0;

  fGeneralNBacMat                             = 0;
  fGeneralNBacMat_is_lu                       = 0;
  fGeneralNBacMat_is_ll                       = 0;  
  fGeneralNBacMat_is_hu                       = 0;
  fGeneralNBacMat_is_hl                       = 0;
  fGeneralNBacMat_nis_lu                      = 0;
  fGeneralNBacMat_nis_ll                      = 0; 
  fGeneralNBacMat_nis_hu                      = 0;
  fGeneralNBacMat_nis_hl                      = 0;

  fGeneralBacMat_VCID                         = 0;
  fGeneralBacMat_VCID_is_lu                   = 0;
  fGeneralBacMat_VCID_is_ll                   = 0;  
  fGeneralBacMat_VCID_is_hu                   = 0;
  fGeneralBacMat_VCID_is_hl                   = 0;
  fGeneralBacMat_VCID_nis_lu                  = 0;
  fGeneralBacMat_VCID_nis_ll                  = 0; 
  fGeneralBacMat_VCID_nis_hu                  = 0;
  fGeneralBacMat_VCID_nis_hl                  = 0;

  fGeneralBacMat_MuBacID                      = 0;
  fGeneralBacMat_MuBacID_is_lu                = 0;
  fGeneralBacMat_MuBacID_is_ll                = 0;  
  fGeneralBacMat_MuBacID_is_hu                = 0;
  fGeneralBacMat_MuBacID_is_hl                = 0;
  fGeneralBacMat_MuBacID_nis_lu               = 0;
  fGeneralBacMat_MuBacID_nis_ll               = 0; 
  fGeneralBacMat_MuBacID_nis_hu               = 0;
  fGeneralBacMat_MuBacID_nis_hl               = 0;

  fGeneralBacMat_Istop                        = 0;
  fGeneralBacMat_Istop_is_lu                  = 0;
  fGeneralBacMat_Istop_is_ll                  = 0;  
  fGeneralBacMat_Istop_is_hu                  = 0;
  fGeneralBacMat_Istop_is_hl                  = 0;
  fGeneralBacMat_Istop_nis_lu                 = 0;
  fGeneralBacMat_Istop_nis_ll                 = 0; 
  fGeneralBacMat_Istop_nis_hu                 = 0;
  fGeneralBacMat_Istop_nis_hl                 = 0;

  fGeneralBacMat_Error                        = 0;
  fGeneralBacMat_Error_is_lu                  = 0;
  fGeneralBacMat_Error_is_ll                  = 0;  
  fGeneralBacMat_Error_is_hu                  = 0;
  fGeneralBacMat_Error_is_hl                  = 0;
  fGeneralBacMat_Error_nis_lu                 = 0;
  fGeneralBacMat_Error_nis_ll                 = 0; 
  fGeneralBacMat_Error_nis_hu                 = 0;
  fGeneralBacMat_Error_nis_hl                 = 0;

  fGeneralBacMat_Readout                      = 0;
  fGeneralBacMat_Readout_is_lu                = 0;
  fGeneralBacMat_Readout_is_ll                = 0;  
  fGeneralBacMat_Readout_is_hu                = 0;
  fGeneralBacMat_Readout_is_hl                = 0;
  fGeneralBacMat_Readout_nis_lu               = 0;
  fGeneralBacMat_Readout_nis_ll               = 0; 
  fGeneralBacMat_Readout_nis_hu               = 0;
  fGeneralBacMat_Readout_nis_hl               = 0;

  fGeneralImpact2D                            = 0;
  fGeneralImpact2D_is_lu                      = 0;
  fGeneralImpact2D_is_ll                      = 0;  
  fGeneralImpact2D_is_hu                      = 0;
  fGeneralImpact2D_is_hl                      = 0;
  fGeneralImpact2D_nis_lu                     = 0;
  fGeneralImpact2D_nis_ll                     = 0; 
  fGeneralImpact2D_nis_hu                     = 0;
  fGeneralImpact2D_nis_hl                     = 0;

  fGeneralImpact2D_Sign                       = 0;
  fGeneralImpact2D_Sign_is_lu                 = 0;
  fGeneralImpact2D_Sign_is_ll                 = 0;  
  fGeneralImpact2D_Sign_is_hu                 = 0;
  fGeneralImpact2D_Sign_is_hl                 = 0;
  fGeneralImpact2D_Sign_nis_lu                = 0;
  fGeneralImpact2D_Sign_nis_ll                = 0; 
  fGeneralImpact2D_Sign_nis_hu                = 0;
  fGeneralImpact2D_Sign_nis_hl                = 0;

  fGeneralDL2                                 = 0;
  fGeneralDL2_is_lu                           = 0;
  fGeneralDL2_is_ll                           = 0;  
  fGeneralDL2_is_hu                           = 0;
  fGeneralDL2_is_hl                           = 0;
  fGeneralDL2_nis_lu                          = 0;
  fGeneralDL2_nis_ll                          = 0; 
  fGeneralDL2_nis_hu                          = 0;
  fGeneralDL2_nis_hl                          = 0;

  fGeneralDL2_err                             = 0;
  fGeneralDL2_err_is_lu                       = 0;
  fGeneralDL2_err_is_ll                       = 0;  
  fGeneralDL2_err_is_hu                       = 0;
  fGeneralDL2_err_is_hl                       = 0;
  fGeneralDL2_err_nis_lu                      = 0;
  fGeneralDL2_err_nis_ll                      = 0; 
  fGeneralDL2_err_nis_hu                      = 0;
  fGeneralDL2_err_nis_hl                      = 0;

  fGeneralDL2_Sign                            = 0;
  fGeneralDL2_Sign_is_lu                      = 0;
  fGeneralDL2_Sign_is_ll                      = 0;  
  fGeneralDL2_Sign_is_hu                      = 0;
  fGeneralDL2_Sign_is_hl                      = 0;
  fGeneralDL2_Sign_nis_lu                     = 0;
  fGeneralDL2_Sign_nis_ll                     = 0; 
  fGeneralDL2_Sign_nis_hu                     = 0;
  fGeneralDL2_Sign_nis_hl                     = 0;

  fGeneralDL2_Sign_Mirrp                      = 0;
  fGeneralDL2_Sign_Mirrp_is_lu                = 0;
  fGeneralDL2_Sign_Mirrp_is_ll                = 0;  
  fGeneralDL2_Sign_Mirrp_is_hu                = 0;
  fGeneralDL2_Sign_Mirrp_is_hl                = 0;
  fGeneralDL2_Sign_Mirrp_nis_lu               = 0;
  fGeneralDL2_Sign_Mirrp_nis_ll               = 0; 
  fGeneralDL2_Sign_Mirrp_nis_hu               = 0;
  fGeneralDL2_Sign_Mirrp_nis_hl               = 0;

  fGeneralDL2_Sign_Mirrm                      = 0;
  fGeneralDL2_Sign_Mirrm_is_lu                = 0;
  fGeneralDL2_Sign_Mirrm_is_ll                = 0;  
  fGeneralDL2_Sign_Mirrm_is_hu                = 0;
  fGeneralDL2_Sign_Mirrm_is_hl                = 0;
  fGeneralDL2_Sign_Mirrm_nis_lu               = 0;
  fGeneralDL2_Sign_Mirrm_nis_ll               = 0; 
  fGeneralDL2_Sign_Mirrm_nis_hu               = 0;
  fGeneralDL2_Sign_Mirrm_nis_hl               = 0;

  fGeneral_mvtx2_DL2                          = 0;
  fGeneral_mvtx2_DL2_is_lu                    = 0;
  fGeneral_mvtx2_DL2_is_ll                    = 0;  
  fGeneral_mvtx2_DL2_is_hu                    = 0;
  fGeneral_mvtx2_DL2_is_hl                    = 0;
  fGeneral_mvtx2_DL2_nis_lu                   = 0;
  fGeneral_mvtx2_DL2_nis_ll                   = 0; 
  fGeneral_mvtx2_DL2_nis_hu                   = 0;
  fGeneral_mvtx2_DL2_nis_hl                   = 0;

  fGeneral_mvtx2_DL2_err                      = 0;
  fGeneral_mvtx2_DL2_err_is_lu                = 0;
  fGeneral_mvtx2_DL2_err_is_ll                = 0;  
  fGeneral_mvtx2_DL2_err_is_hu                = 0;
  fGeneral_mvtx2_DL2_err_is_hl                = 0;
  fGeneral_mvtx2_DL2_err_nis_lu               = 0;
  fGeneral_mvtx2_DL2_err_nis_ll               = 0; 
  fGeneral_mvtx2_DL2_err_nis_hu               = 0;
  fGeneral_mvtx2_DL2_err_nis_hl               = 0;

  fGeneral_mvtx2_DL2_Sign                     = 0;
  fGeneral_mvtx2_DL2_Sign_is_lu               = 0;
  fGeneral_mvtx2_DL2_Sign_is_ll               = 0;  
  fGeneral_mvtx2_DL2_Sign_is_hu               = 0;
  fGeneral_mvtx2_DL2_Sign_is_hl               = 0;
  fGeneral_mvtx2_DL2_Sign_nis_lu              = 0;
  fGeneral_mvtx2_DL2_Sign_nis_ll              = 0; 
  fGeneral_mvtx2_DL2_Sign_nis_hu              = 0;
  fGeneral_mvtx2_DL2_Sign_nis_hl              = 0;

  fGeneral_mvtx2_DL2_Sign_Mirrp               = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrp_is_lu         = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrp_is_ll         = 0;  
  fGeneral_mvtx2_DL2_Sign_Mirrp_is_hu         = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrp_is_hl         = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrp_nis_lu        = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrp_nis_ll        = 0; 
  fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hu        = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrp_nis_hl        = 0;

  fGeneral_mvtx2_DL2_Sign_Mirrm               = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrm_is_lu         = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrm_is_ll         = 0;  
  fGeneral_mvtx2_DL2_Sign_Mirrm_is_hu         = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrm_is_hl         = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrm_nis_lu        = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrm_nis_ll        = 0; 
  fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hu        = 0;
  fGeneral_mvtx2_DL2_Sign_Mirrm_nis_hl        = 0;

  fGeneralMuJetDeltaR                         = 0;
  fGeneralMuJetDeltaR_is_lu                   = 0;
  fGeneralMuJetDeltaR_is_ll                   = 0;  
  fGeneralMuJetDeltaR_is_hu                   = 0;
  fGeneralMuJetDeltaR_is_hl                   = 0;
  fGeneralMuJetDeltaR_nis_lu                  = 0;
  fGeneralMuJetDeltaR_nis_ll                  = 0; 
  fGeneralMuJetDeltaR_nis_hu                  = 0;
  fGeneralMuJetDeltaR_nis_hl                  = 0;

  fGeneralMuJetPt                             = 0;
  fGeneralMuJetPt_is_lu                       = 0;
  fGeneralMuJetPt_is_ll                       = 0;  
  fGeneralMuJetPt_is_hu                       = 0;
  fGeneralMuJetPt_is_hl                       = 0;
  fGeneralMuJetPt_nis_lu                      = 0;
  fGeneralMuJetPt_nis_ll                      = 0; 
  fGeneralMuJetPt_nis_hu                      = 0;
  fGeneralMuJetPt_nis_hl                      = 0;

  fGeneralMuJetEt                             = 0;
  fGeneralMuJetEt_is_lu                       = 0;
  fGeneralMuJetEt_is_ll                       = 0;  
  fGeneralMuJetEt_is_hu                       = 0;
  fGeneralMuJetEt_is_hl                       = 0;
  fGeneralMuJetEt_nis_lu                      = 0;
  fGeneralMuJetEt_nis_ll                      = 0; 
  fGeneralMuJetEt_nis_hu                      = 0;
  fGeneralMuJetEt_nis_hl                      = 0;

  fGeneralMuJetEta                            = 0;
  fGeneralMuJetEta_is_lu                      = 0;
  fGeneralMuJetEta_is_ll                      = 0;  
  fGeneralMuJetEta_is_hu                      = 0;
  fGeneralMuJetEta_is_hl                      = 0;
  fGeneralMuJetEta_nis_lu                     = 0;
  fGeneralMuJetEta_nis_ll                     = 0; 
  fGeneralMuJetEta_nis_hu                     = 0;
  fGeneralMuJetEta_nis_hl                     = 0;

  fGeneralMassJet                             = 0;
  fGeneralMassJet_is_lu                       = 0;
  fGeneralMassJet_is_ll                       = 0;  
  fGeneralMassJet_is_hu                       = 0;
  fGeneralMassJet_is_hl                       = 0;
  fGeneralMassJet_nis_lu                      = 0;
  fGeneralMassJet_nis_ll                      = 0; 
  fGeneralMassJet_nis_hu                      = 0;
  fGeneralMassJet_nis_hl                      = 0;

  fGeneralNJets                               = 0;
  fGeneralNJets_is_lu                         = 0;
  fGeneralNJets_is_ll                         = 0;  
  fGeneralNJets_is_hu                         = 0;
  fGeneralNJets_is_hl                         = 0;
  fGeneralNJets_nis_lu                        = 0;
  fGeneralNJets_nis_ll                        = 0; 
  fGeneralNJets_nis_hu                        = 0;
  fGeneralNJets_nis_hl                        = 0;

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

/* DB Histos */

  fGeneraldijetbothetex2ir                    = 0;
  fGeneraldijetbothetex2ir_is_lu	      = 0;
  fGeneraldijetbothetex2ir_is_ll	      = 0;
  fGeneraldijetbothetex2ir_is_hu	      = 0;
  fGeneraldijetbothetex2ir_is_hl	      = 0;
  fGeneraldijetbothetex2ir_nis_lu             = 0;
  fGeneraldijetbothetex2ir_nis_ll	      = 0;
  fGeneraldijetbothetex2ir_nis_hu	      = 0;
  fGeneraldijetbothetex2ir_nis_hl	      = 0;

  fGeneraldijetbothdimuxsecpt                 = 0;
  fGeneraldijetbothdimuxsecpt_is_lu           = 0;
  fGeneraldijetbothdimuxsecpt_is_ll           = 0;
  fGeneraldijetbothdimuxsecpt_is_hu           = 0;
  fGeneraldijetbothdimuxsecpt_is_hl           = 0;
  fGeneraldijetbothdimuxsecpt_nis_lu          = 0;
  fGeneraldijetbothdimuxsecpt_nis_ll          = 0;
  fGeneraldijetbothdimuxsecpt_nis_hu          = 0;
  fGeneraldijetbothdimuxsecpt_nis_hl          = 0;

  fGeneraldijetbothdimuxseceta                = 0;
  fGeneraldijetbothdimuxseceta_is_lu          = 0;
  fGeneraldijetbothdimuxseceta_is_ll          = 0;
  fGeneraldijetbothdimuxseceta_is_hu          = 0;
  fGeneraldijetbothdimuxseceta_is_hl          = 0;
  fGeneraldijetbothdimuxseceta_nis_lu         = 0;
  fGeneraldijetbothdimuxseceta_nis_ll         = 0;
  fGeneraldijetbothdimuxseceta_nis_hu         = 0;
  fGeneraldijetbothdimuxseceta_nis_hl         = 0;

  fGeneraldijetbothdimuxsecdphi               = 0;
  fGeneraldijetbothdimuxsecdphi_is_lu         = 0;
  fGeneraldijetbothdimuxsecdphi_is_ll         = 0;
  fGeneraldijetbothdimuxsecdphi_is_hu         = 0;
  fGeneraldijetbothdimuxsecdphi_is_hl         = 0;
  fGeneraldijetbothdimuxsecdphi_nis_lu        = 0;
  fGeneraldijetbothdimuxsecdphi_nis_ll        = 0;
  fGeneraldijetbothdimuxsecdphi_nis_hu        = 0;
  fGeneraldijetbothdimuxsecdphi_nis_hl        = 0;

  fGeneraldijetoneetex2ir                     = 0;
  fGeneraldijetoneetex2ir_is_lu	              = 0;
  fGeneraldijetoneetex2ir_is_ll	              = 0;
  fGeneraldijetoneetex2ir_is_hu	              = 0;
  fGeneraldijetoneetex2ir_is_hl	              = 0;
  fGeneraldijetoneetex2ir_nis_lu              = 0;
  fGeneraldijetoneetex2ir_nis_ll	      = 0;
  fGeneraldijetoneetex2ir_nis_hu	      = 0;
  fGeneraldijetoneetex2ir_nis_hl	      = 0;

  fGeneraldijetonedimuxsecpt                  = 0;
  fGeneraldijetonedimuxsecpt_is_lu            = 0;
  fGeneraldijetonedimuxsecpt_is_ll            = 0;
  fGeneraldijetonedimuxsecpt_is_hu            = 0;
  fGeneraldijetonedimuxsecpt_is_hl            = 0;
  fGeneraldijetonedimuxsecpt_nis_lu           = 0;
  fGeneraldijetonedimuxsecpt_nis_ll           = 0;
  fGeneraldijetonedimuxsecpt_nis_hu           = 0;
  fGeneraldijetonedimuxsecpt_nis_hl           = 0;

  fGeneraldijetonedimuxseceta                 = 0;
  fGeneraldijetonedimuxseceta_is_lu           = 0;
  fGeneraldijetonedimuxseceta_is_ll           = 0;
  fGeneraldijetonedimuxseceta_is_hu           = 0;
  fGeneraldijetonedimuxseceta_is_hl           = 0;
  fGeneraldijetonedimuxseceta_nis_lu          = 0;
  fGeneraldijetonedimuxseceta_nis_ll          = 0;
  fGeneraldijetonedimuxseceta_nis_hu          = 0;
  fGeneraldijetonedimuxseceta_nis_hl          = 0;

  fGeneraldijetonedimuxsecdphi                = 0;
  fGeneraldijetonedimuxsecdphi_is_lu          = 0;
  fGeneraldijetonedimuxsecdphi_is_ll          = 0;
  fGeneraldijetonedimuxsecdphi_is_hu          = 0;
  fGeneraldijetonedimuxsecdphi_is_hl          = 0;
  fGeneraldijetonedimuxsecdphi_nis_lu         = 0;
  fGeneraldijetonedimuxsecdphi_nis_ll         = 0;
  fGeneraldijetonedimuxsecdphi_nis_hu         = 0;
  fGeneraldijetonedimuxsecdphi_nis_hl         = 0;

  fGeneraldijetnoneetex2ir                    = 0;
  fGeneraldijetnoneetex2ir_is_lu	      = 0;
  fGeneraldijetnoneetex2ir_is_ll	      = 0;
  fGeneraldijetnoneetex2ir_is_hu	      = 0;
  fGeneraldijetnoneetex2ir_is_hl	      = 0;
  fGeneraldijetnoneetex2ir_nis_lu             = 0;
  fGeneraldijetnoneetex2ir_nis_ll	      = 0;
  fGeneraldijetnoneetex2ir_nis_hu	      = 0;
  fGeneraldijetnoneetex2ir_nis_hl	      = 0;

  fGeneraldijetnonedimuxsecpt                 = 0;
  fGeneraldijetnonedimuxsecpt_is_lu           = 0;
  fGeneraldijetnonedimuxsecpt_is_ll           = 0;
  fGeneraldijetnonedimuxsecpt_is_hu           = 0;
  fGeneraldijetnonedimuxsecpt_is_hl           = 0;
  fGeneraldijetnonedimuxsecpt_nis_lu          = 0;
  fGeneraldijetnonedimuxsecpt_nis_ll          = 0;
  fGeneraldijetnonedimuxsecpt_nis_hu          = 0;
  fGeneraldijetnonedimuxsecpt_nis_hl          = 0;

  fGeneraldijetnonedimuxseceta                = 0;
  fGeneraldijetnonedimuxseceta_is_lu          = 0;
  fGeneraldijetnonedimuxseceta_is_ll          = 0;
  fGeneraldijetnonedimuxseceta_is_hu          = 0;
  fGeneraldijetnonedimuxseceta_is_hl          = 0;
  fGeneraldijetnonedimuxseceta_nis_lu         = 0;
  fGeneraldijetnonedimuxseceta_nis_ll         = 0;
  fGeneraldijetnonedimuxseceta_nis_hu         = 0;
  fGeneraldijetnonedimuxseceta_nis_hl         = 0;

  fGeneraldijetnonedimuxsecdphi               = 0;
  fGeneraldijetnonedimuxsecdphi_is_lu         = 0;
  fGeneraldijetnonedimuxsecdphi_is_ll         = 0;
  fGeneraldijetnonedimuxsecdphi_is_hu         = 0;
  fGeneraldijetnonedimuxsecdphi_is_hl         = 0;
  fGeneraldijetnonedimuxsecdphi_nis_lu        = 0;
  fGeneraldijetnonedimuxsecdphi_nis_ll        = 0;
  fGeneraldijetnonedimuxsecdphi_nis_hu        = 0;
  fGeneraldijetnonedimuxsecdphi_nis_hl        = 0;


/* End DB Histos */

  fGeneraldimuxsecpt                          = 0;
  fGeneraldimuxsecpt_is_lu                    = 0;
  fGeneraldimuxsecpt_is_ll                    = 0;
  fGeneraldimuxsecpt_is_hu                    = 0;
  fGeneraldimuxsecpt_is_hl                    = 0;
  fGeneraldimuxsecpt_nis_lu                   = 0;
  fGeneraldimuxsecpt_nis_ll                   = 0;
  fGeneraldimuxsecpt_nis_hu                   = 0;
  fGeneraldimuxsecpt_nis_hl                   = 0;

  fGeneraldimuxseceta                         = 0;
  fGeneraldimuxseceta_is_lu                   = 0;
  fGeneraldimuxseceta_is_ll                   = 0;
  fGeneraldimuxseceta_is_hu                   = 0;
  fGeneraldimuxseceta_is_hl                   = 0;
  fGeneraldimuxseceta_nis_lu                  = 0;
  fGeneraldimuxseceta_nis_ll                  = 0;
  fGeneraldimuxseceta_nis_hu                  = 0;
  fGeneraldimuxseceta_nis_hl                  = 0;

  fGeneraldimuxsecfinders                     = 0;
  fGeneraldimuxsecfinders_is_lu               = 0;
  fGeneraldimuxsecfinders_is_ll               = 0;
  fGeneraldimuxsecfinders_is_hu               = 0;
  fGeneraldimuxsecfinders_is_hl               = 0;
  fGeneraldimuxsecfinders_nis_lu              = 0;
  fGeneraldimuxsecfinders_nis_ll              = 0;
  fGeneraldimuxsecfinders_nis_hu              = 0;
  fGeneraldimuxsecfinders_nis_hl              = 0;

  fGeneraldimuxsecdr                          = 0;
  fGeneraldimuxsecdr_is_lu                    = 0;
  fGeneraldimuxsecdr_is_ll                    = 0;
  fGeneraldimuxsecdr_is_hu                    = 0;
  fGeneraldimuxsecdr_is_hl                    = 0;
  fGeneraldimuxsecdr_nis_lu                   = 0;
  fGeneraldimuxsecdr_nis_ll                   = 0;
  fGeneraldimuxsecdr_nis_hu                   = 0;
  fGeneraldimuxsecdr_nis_hl                   = 0;

  fGeneraldimuxsecdphi                        = 0;
  fGeneraldimuxsecdphi_is_lu                  = 0;
  fGeneraldimuxsecdphi_is_ll                  = 0;
  fGeneraldimuxsecdphi_is_hu                  = 0;
  fGeneraldimuxsecdphi_is_hl                  = 0;
  fGeneraldimuxsecdphi_nis_lu                 = 0;
  fGeneraldimuxsecdphi_nis_ll                 = 0;
  fGeneraldimuxsecdphi_nis_hu                 = 0;
  fGeneraldimuxsecdphi_nis_hl                 = 0;

  fGeneraldimuxsecptb                         = 0;
  fGeneraldimuxsecptb_is_lu                   = 0;
  fGeneraldimuxsecptb_is_ll                   = 0;
  fGeneraldimuxsecptb_is_hu                   = 0;
  fGeneraldimuxsecptb_is_hl                   = 0;
  fGeneraldimuxsecptb_nis_lu                  = 0;
  fGeneraldimuxsecptb_nis_ll                  = 0;
  fGeneraldimuxsecptb_nis_hu                  = 0;
  fGeneraldimuxsecptb_nis_hl                  = 0;

  fGeneraldimuxsecptb_sameb                   = 0;
  fGeneraldimuxsecptb_sameb_is_lu             = 0;
  fGeneraldimuxsecptb_sameb_is_ll             = 0;
  fGeneraldimuxsecptb_sameb_is_hu             = 0;
  fGeneraldimuxsecptb_sameb_is_hl             = 0;
  fGeneraldimuxsecptb_sameb_nis_lu            = 0;
  fGeneraldimuxsecptb_sameb_nis_ll            = 0;
  fGeneraldimuxsecptb_sameb_nis_hu            = 0;
  fGeneraldimuxsecptb_sameb_nis_hl            = 0;

  fGeneraldimuxsecptb_diffb                   = 0;
  fGeneraldimuxsecptb_diffb_is_lu             = 0;
  fGeneraldimuxsecptb_diffb_is_ll             = 0;
  fGeneraldimuxsecptb_diffb_is_hu             = 0;
  fGeneraldimuxsecptb_diffb_is_hl             = 0;
  fGeneraldimuxsecptb_diffb_nis_lu            = 0;
  fGeneraldimuxsecptb_diffb_nis_ll            = 0;
  fGeneraldimuxsecptb_diffb_nis_hu            = 0;
  fGeneraldimuxsecptb_diffb_nis_hl            = 0;

  fGeneraldimuxsecptb_samecone                = 0;
  fGeneraldimuxsecptb_samecone_is_lu          = 0;
  fGeneraldimuxsecptb_samecone_is_ll          = 0;
  fGeneraldimuxsecptb_samecone_is_hu          = 0;
  fGeneraldimuxsecptb_samecone_is_hl          = 0;
  fGeneraldimuxsecptb_samecone_nis_lu         = 0;
  fGeneraldimuxsecptb_samecone_nis_ll         = 0;
  fGeneraldimuxsecptb_samecone_nis_hu         = 0;
  fGeneraldimuxsecptb_samecone_nis_hl         = 0;

  fGeneraldimuxsecptb_asym                    = 0;
  fGeneraldimuxsecptb_asym_is_lu              = 0;
  fGeneraldimuxsecptb_asym_is_ll              = 0;
  fGeneraldimuxsecptb_asym_is_hu              = 0;
  fGeneraldimuxsecptb_asym_is_hl              = 0;
  fGeneraldimuxsecptb_asym_nis_lu             = 0;
  fGeneraldimuxsecptb_asym_nis_ll             = 0;
  fGeneraldimuxsecptb_asym_nis_hu             = 0;
  fGeneraldimuxsecptb_asym_nis_hl             = 0;

  fGeneralTriggerType                         = 0;

  fGeneralMV_MuonPt                           = 0;
  fGeneralMV_BREMAT_MuonPt                    = 0;
  fGeneralMV_MUBAC_MuonPt                     = 0;
  fGeneralMV_MuonP                            = 0;
  fGeneralMV_MPMATCH_MuonP                    = 0;
  fGeneralMV_MUBAC_MuonP                      = 0;
  fGeneralMV_MuonPz                           = 0;
  fGeneralMV_BREMAT_MuonPz                    = 0;
  fGeneralMV_MUBAC_MuonPz                     = 0;
  fGeneralMV_MuonEta                          = 0;
  fGeneralMV_BREMAT_MuonEta                   = 0;
  fGeneralMV_MPMATCH_MuonEta                  = 0;
  fGeneralMV_MUBAC_MuonEta                    = 0;
  fGeneralMV_MuonEtaPtBins                    = 0;
  fGeneralMV_BREMAT_MuonEtaPtBins             = 0;
  fGeneralMV_MPMATCH_MuonEtaPtBins            = 0;
  fGeneralMV_MUBAC_MuonEtaPtBins              = 0;
  fGeneralMV_MuonPhi                          = 0;
  fGeneralMV_BREMAT_MuonPhi                   = 0;
  fGeneralMV_MPMATCH_MuonPhi                  = 0;
  fGeneralMV_MUBAC_MuonPhi                    = 0;
  fGeneralMV_MuonPhiPtBins                    = 0;
  fGeneralMV_BREMAT_MuonPhiPtBins             = 0;
  fGeneralMV_MPMATCH_MuonPhiPtBins            = 0;
  fGeneralMV_MUBAC_MuonPhiPtBins              = 0;
	
  fGeneralMV_MuonP_Forward                    = 0;
  fGeneralMV_MPMATCH_MuonP_Forward            = 0;
  fGeneralMV_MUBAC_MuonP_Forward              = 0;
  fGeneralMV_MuonPt_Forward                   = 0;
  fGeneralMV_MPMATCH_MuonPt_Forward           = 0;
  fGeneralMV_MUBAC_MuonPt_Forward             = 0;
  fGeneralMV_MuonEta_Forward                  = 0;
  fGeneralMV_MPMATCH_MuonEta_Forward          = 0;
  fGeneralMV_MUBAC_MuonEta_Forward            = 0;
  fGeneralMV_MuonEtaPBins_Forward             = 0;
  fGeneralMV_MPMATCH_MuonEtaPBins_Forward     = 0;
  fGeneralMV_MUBAC_MuonEtaPBins_Forward       = 0;
  fGeneralMV_MuonPhi_Forward                  = 0;
  fGeneralMV_MPMATCH_MuonPhi_Forward          = 0;
  fGeneralMV_MUBAC_MuonPhi_Forward            = 0;
  fGeneralMV_MuonPhiPBins_Forward             = 0;
  fGeneralMV_MPMATCH_MuonPhiPBins_Forward     = 0;
  fGeneralMV_MUBAC_MuonPhiPBins_Forward       = 0;
	
  fGeneralMV_MuonPt_Barrel                    = 0;
  fGeneralMV_BREMAT_MuonPt_Barrel             = 0;
  fGeneralMV_MUBAC_MuonPt_Barrel              = 0;
  fGeneralMV_MuonEta_Barrel                   = 0;
  fGeneralMV_BREMAT_MuonEta_Barrel            = 0;
  fGeneralMV_MUBAC_MuonEta_Barrel             = 0;
  fGeneralMV_MuonEtaPtBins_Barrel             = 0;
  fGeneralMV_BREMAT_MuonEtaPtBins_Barrel      = 0;
  fGeneralMV_MUBAC_MuonEtaPtBins_Barrel       = 0;
  fGeneralMV_MuonPhi_Barrel                   = 0;
  fGeneralMV_BREMAT_MuonPhi_Barrel            = 0;
  fGeneralMV_MUBAC_MuonPhi_Barrel             = 0;
  fGeneralMV_MuonPhiPtBins_Barrel             = 0;
  fGeneralMV_BREMAT_MuonPhiPtBins_Barrel      = 0;
  fGeneralMV_MUBAC_MuonPhiPtBins_Barrel       = 0;
	
  fGeneralMV_MuonPz_Rear                      = 0;
  fGeneralMV_BREMAT_MuonPz_Rear               = 0;
  fGeneralMV_MUBAC_MuonPz_Rear                = 0;
  fGeneralMV_MuonPt_Rear                      = 0;
  fGeneralMV_BREMAT_MuonPt_Rear               = 0;
  fGeneralMV_MUBAC_MuonPt_Rear                = 0;
  fGeneralMV_MuonEta_Rear                     = 0;
  fGeneralMV_BREMAT_MuonEta_Rear              = 0;
  fGeneralMV_MUBAC_MuonEta_Rear               = 0;
  fGeneralMV_MuonEtaPzBins_Rear               = 0;
  fGeneralMV_BREMAT_MuonEtaPzBins_Rear        = 0;
  fGeneralMV_MUBAC_MuonEtaPzBins_Rear         = 0;
  fGeneralMV_MuonPhi_Rear                     = 0;
  fGeneralMV_BREMAT_MuonPhi_Rear              = 0;
  fGeneralMV_MUBAC_MuonPhi_Rear               = 0;
  fGeneralMV_MuonPhiPzBins_Rear               = 0;
  fGeneralMV_BREMAT_MuonPhiPzBins_Rear        = 0;
  fGeneralMV_MUBAC_MuonPhiPzBins_Rear         = 0;
  
  // init control plots
  fControlNperEv_uncut                        = 0;
  fControlDIMuonMass_uncut                    = 0;
  fControlDIMuonMassLow_uncut                 = 0;
  fControlDIMuonMassHigh_uncut                = 0;

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
  fControldimupt_uncut                        = 0;
  fControldimupt_lu_is_uncut                  = 0;
  fControldimupt_ll_is_uncut                  = 0;
  fControldimupt_hu_is_uncut                  = 0;
  fControldimupt_hl_is_uncut                  = 0;
  fControldimupt_lu_nis_uncut                 = 0;
  fControldimupt_ll_nis_uncut                 = 0;
  fControldimupt_hu_nis_uncut                 = 0;
  fControldimupt_hl_nis_uncut                 = 0;
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

  fControlNperEvGood                          = 0;
  fControlGoodDIMuonMass                      = 0;
  fControlGoodDIMuonMassLow                   = 0;
  fControlGoodDIMuonMassHigh                  = 0;

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
  fControlGooddimupt                          = 0;
  fControlGooddimupt_lu_is                    = 0;
  fControlGooddimupt_ll_is                    = 0;
  fControlGooddimupt_hu_is                    = 0;
  fControlGooddimupt_hl_is                    = 0;
  fControlGooddimupt_lu_nis                   = 0;
  fControlGooddimupt_ll_nis                   = 0;
  fControlGooddimupt_hu_nis                   = 0;
  fControlGooddimupt_hl_nis                   = 0;
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

  fControlNperEvChosen                        = 0;
  fControlChosenDIMuonMass                    = 0;
  fControlChosenDIMuonMassLow                 = 0;
  fControlChosenDIMuonMassHigh                = 0;

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
  fControlChosendimupt                        = 0;
  fControlChosendimupt_lu_is                  = 0;
  fControlChosendimupt_ll_is                  = 0;
  fControlChosendimupt_hu_is                  = 0;
  fControlChosendimupt_hl_is                  = 0;
  fControlChosendimupt_lu_nis                 = 0;
  fControlChosendimupt_ll_nis                 = 0;
  fControlChosendimupt_hu_nis                 = 0;
  fControlChosendimupt_hl_nis                 = 0;
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

  return kTRUE;
}

//_____________________________________________________________

Bool_t GDIMuons::InitArrays() {
  //
  // init arrays for histogram generation
  if( gDebug ) cout << endl << "GDIMuons::InitArrays() called" << endl << endl;

  Bool_t fine_binning = kTRUE;

  if( fine_binning ) {
    fGeneralMuonP_NBins_MPMATCH    = 1;
    fGeneralMuonP_Bins_MPMATCH     = new Double_t[fGeneralMuonP_NBins_MPMATCH+1];
    fGeneralMuonP_Bins_MPMATCH[0]  = 0.0;
    fGeneralMuonP_Bins_MPMATCH[1]  = 5.0;

    fGeneralMuonP_NBins_MUBAC    = 1;
    fGeneralMuonP_Bins_MUBAC     = new Double_t[fGeneralMuonP_NBins_MUBAC+1];
    fGeneralMuonP_Bins_MUBAC[0]  = 0.0;
    fGeneralMuonP_Bins_MUBAC[1]  = 5.0;

    // determine from MPMATCH and MUBAC P arrays the corresponding MV array, 
    fGeneralMuonP_NBins_MV = 1;
    fGeneralMuonP_Bins_MV  = new Double_t[fGeneralMuonP_NBins_MV+1];
    fGeneralMuonP_Bins_MV[0]  = 0.0;
    fGeneralMuonP_Bins_MV[1]  = 5.0;
  
    // fine pt binning configuration
    fGeneralMuonPt_NBins_BREMAT    = 15;
    fGeneralMuonPt_Bins_BREMAT     = new Double_t[fGeneralMuonPt_NBins_BREMAT+1];
    fGeneralMuonPt_Bins_BREMAT[0]  = 0.75;
    fGeneralMuonPt_Bins_BREMAT[1]  = 1.0;
    fGeneralMuonPt_Bins_BREMAT[2]  = 1.1;
    fGeneralMuonPt_Bins_BREMAT[3]  = 1.2;
    fGeneralMuonPt_Bins_BREMAT[4]  = 1.3;
    fGeneralMuonPt_Bins_BREMAT[5]  = 1.4;
    fGeneralMuonPt_Bins_BREMAT[6]  = 1.5;
    fGeneralMuonPt_Bins_BREMAT[7]  = 1.6;
    fGeneralMuonPt_Bins_BREMAT[8]  = 1.7;
    fGeneralMuonPt_Bins_BREMAT[9]  = 1.8;
    fGeneralMuonPt_Bins_BREMAT[10]  = 1.9;
    fGeneralMuonPt_Bins_BREMAT[11]  = 2.0;
    fGeneralMuonPt_Bins_BREMAT[12]  = 2.2;
    fGeneralMuonPt_Bins_BREMAT[13]  = 2.4;
    fGeneralMuonPt_Bins_BREMAT[14]  = 2.8;
    fGeneralMuonPt_Bins_BREMAT[15]  = 5.0;

    fGeneralMuonPt_NBins_MUBAC    = 15;
    fGeneralMuonPt_Bins_MUBAC     = new Double_t[fGeneralMuonPt_NBins_MUBAC+1];
    fGeneralMuonPt_Bins_MUBAC[0]  = 0.75;
    fGeneralMuonPt_Bins_MUBAC[1]  = 1.0;
    fGeneralMuonPt_Bins_MUBAC[2]  = 1.1;
    fGeneralMuonPt_Bins_MUBAC[3]  = 1.2;
    fGeneralMuonPt_Bins_MUBAC[4]  = 1.3;
    fGeneralMuonPt_Bins_MUBAC[5]  = 1.4;
    fGeneralMuonPt_Bins_MUBAC[6]  = 1.5;
    fGeneralMuonPt_Bins_MUBAC[7]  = 1.6;
    fGeneralMuonPt_Bins_MUBAC[8]  = 1.7;
    fGeneralMuonPt_Bins_MUBAC[9]  = 1.8;
    fGeneralMuonPt_Bins_MUBAC[10]  = 1.9;
    fGeneralMuonPt_Bins_MUBAC[11]  = 2.0;
    fGeneralMuonPt_Bins_MUBAC[12]  = 2.2;
    fGeneralMuonPt_Bins_MUBAC[13]  = 2.4;
    fGeneralMuonPt_Bins_MUBAC[14]  = 2.8;
    fGeneralMuonPt_Bins_MUBAC[15]  = 5.0;

    // determine from BREMAT and MUBAC P arrays the corresponding MV array, 
    fGeneralMuonPt_NBins_MV = 15;
    fGeneralMuonPt_Bins_MV  = new Double_t[fGeneralMuonPt_NBins_MV+1];
    fGeneralMuonPt_Bins_MV[0]  = 0.75;
    fGeneralMuonPt_Bins_MV[1]  = 1.0;
    fGeneralMuonPt_Bins_MV[2]  = 1.1;
    fGeneralMuonPt_Bins_MV[3]  = 1.2;
    fGeneralMuonPt_Bins_MV[4]  = 1.3;
    fGeneralMuonPt_Bins_MV[5]  = 1.4;
    fGeneralMuonPt_Bins_MV[6]  = 1.5;
    fGeneralMuonPt_Bins_MV[7]  = 1.6;
    fGeneralMuonPt_Bins_MV[8]  = 1.7;
    fGeneralMuonPt_Bins_MV[9]  = 1.8;
    fGeneralMuonPt_Bins_MV[10]  = 1.9;
    fGeneralMuonPt_Bins_MV[11]  = 2.0;
    fGeneralMuonPt_Bins_MV[12]  = 2.2;
    fGeneralMuonPt_Bins_MV[13]  = 2.4;
    fGeneralMuonPt_Bins_MV[14]  = 2.8;
    fGeneralMuonPt_Bins_MV[15]  = 5.0;

    fGeneralMuonPz_NBins_BREMAT    = 1;
    fGeneralMuonPz_Bins_BREMAT     = new Double_t[fGeneralMuonPz_NBins_BREMAT+1];
    fGeneralMuonPz_Bins_BREMAT[0]  =  0.0;
    fGeneralMuonPz_Bins_BREMAT[1]  = -5.0;

    fGeneralMuonPz_NBins_MUBAC    = 1;
    fGeneralMuonPz_Bins_MUBAC     = new Double_t[fGeneralMuonPz_NBins_MUBAC+1];
    fGeneralMuonPz_Bins_MUBAC[0]  =  0.0;
    fGeneralMuonPz_Bins_MUBAC[1]  = -5.0;

    // determine from BREMAT and MUBAC P arrays the corresponding MV array, 
    fGeneralMuonPz_NBins_MV = 1;
    fGeneralMuonPz_Bins_MV  = new Double_t[fGeneralMuonPz_NBins_MV+1];
    fGeneralMuonPz_Bins_MV[0]  =  0.0;
    fGeneralMuonPz_Bins_MV[1]  = -5.0;

  } else {
    fGeneralMuonP_NBins_MPMATCH    = 1;
    fGeneralMuonP_Bins_MPMATCH     = new Double_t[fGeneralMuonP_NBins_MPMATCH+1];
    fGeneralMuonP_Bins_MPMATCH[0]  = 0.0;
    fGeneralMuonP_Bins_MPMATCH[1]  = 5.0;

    fGeneralMuonP_NBins_MUBAC    = 1;
    fGeneralMuonP_Bins_MUBAC     = new Double_t[fGeneralMuonP_NBins_MUBAC+1];
    fGeneralMuonP_Bins_MUBAC[0]  = 0.0;
    fGeneralMuonP_Bins_MUBAC[1]  = 5.0;

    // determine from MPMATCH and MUBAC P arrays the corresponding MV array, 
    fGeneralMuonP_NBins_MV = 1;
    fGeneralMuonP_Bins_MV  = new Double_t[fGeneralMuonP_NBins_MV+1];
    fGeneralMuonP_Bins_MV[0]  = 0.0;
    fGeneralMuonP_Bins_MV[1]  = 5.0;
  
    // coarse pt binning configuration
    fGeneralMuonPt_NBins_BREMAT    = 4;
    fGeneralMuonPt_Bins_BREMAT     = new Double_t[fGeneralMuonPt_NBins_BREMAT+1];
    fGeneralMuonPt_Bins_BREMAT[0]  = 1.50;
    fGeneralMuonPt_Bins_BREMAT[1]  = 1.75;
    fGeneralMuonPt_Bins_BREMAT[2]  = 2.00;
    fGeneralMuonPt_Bins_BREMAT[3]  = 2.50;
    fGeneralMuonPt_Bins_BREMAT[4]  = 5.00;

    fGeneralMuonPt_NBins_MUBAC    = 4;
    fGeneralMuonPt_Bins_MUBAC     = new Double_t[fGeneralMuonPt_NBins_MUBAC+1];
    fGeneralMuonPt_Bins_MUBAC[0]  = 1.50;
    fGeneralMuonPt_Bins_MUBAC[1]  = 1.75;
    fGeneralMuonPt_Bins_MUBAC[2]  = 2.00;
    fGeneralMuonPt_Bins_MUBAC[3]  = 2.50;
    fGeneralMuonPt_Bins_MUBAC[4]  = 5.00;

    // determine from BREMAT and MUBAC P arrays the corresponding MV array, 
    fGeneralMuonPt_NBins_MV = 4;
    fGeneralMuonPt_Bins_MV  = new Double_t[fGeneralMuonPt_NBins_MV+1];
    fGeneralMuonPt_Bins_MV[0]  = 1.50;
    fGeneralMuonPt_Bins_MV[1]  = 1.75;
    fGeneralMuonPt_Bins_MV[2]  = 2.00;
    fGeneralMuonPt_Bins_MV[3]  = 2.50;
    fGeneralMuonPt_Bins_MV[4]  = 5.00;

    fGeneralMuonPz_NBins_BREMAT    = 1;
    fGeneralMuonPz_Bins_BREMAT     = new Double_t[fGeneralMuonPz_NBins_BREMAT+1];
    fGeneralMuonPz_Bins_BREMAT[0]  =  0.0;
    fGeneralMuonPz_Bins_BREMAT[1]  = -5.0;

    fGeneralMuonPz_NBins_MUBAC    = 1;
    fGeneralMuonPz_Bins_MUBAC     = new Double_t[fGeneralMuonPz_NBins_MUBAC+1];
    fGeneralMuonPz_Bins_MUBAC[0]  =  0.0;
    fGeneralMuonPz_Bins_MUBAC[1]  = -5.0;

    // determine from BREMAT and MUBAC P arrays the corresponding MV array, 
    fGeneralMuonPz_NBins_MV = 1;
    fGeneralMuonPz_Bins_MV  = new Double_t[fGeneralMuonPz_NBins_MV+1];
    fGeneralMuonPz_Bins_MV[0]  =  0.0;
    fGeneralMuonPz_Bins_MV[1]  = -5.0;

  }
  return kTRUE;
}


// in GDIMuons.h
  TH1D                *fGeneraldimuxsecfinders       ;                     // plot for dimuon muon dimuxsec in finders
