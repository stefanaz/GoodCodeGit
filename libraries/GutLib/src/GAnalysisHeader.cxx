//
// GAnalysisHeader.cxx
//
// $Author: meyer $
// $Date: 2005/06/14 13:41:14 $
// $Revision: 1.55 $
//

#include <GAnalysisHeader.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef ROOT_TDatime
#include <TDatime.h>
#endif

#ifndef __CINT__
ClassImp(GAnalysisHeader)
#endif

GAnalysisHeader *gHeader = 0;

//_____________________________________________________________
// GAnalysisHeader
// Analysis Header, mainly for time of analysis processing
//
//
GAnalysisHeader::GAnalysisHeader() : TObject() {
  //
  // GAnalysisHeader default constructor
  if ( gDebug ) cout << "GAnalysisHeader::GAnalysisHeader ctor called" << endl;
  
  gHeader = this;

  // initialize data members
  fEventWeight             = 1.0;

  fProcessedEvents         = 0;

  fPassedEvtakeCutsOnly    = 0;
  fPassedTriggerCutsOnly   = 0;
  fPassedVertexCutsOnly    = 0;
  fPassedSinistraCutsOnly  = 0;
  fPassedCalCutsOnly       = 0;
  fPassedBacCutsOnly       = 0;
  fPassedZufoCutsOnly      = 0;
  fPassedJetCutsOnly       = 0;
  fPassedTrackCutsOnly     = 0;
  fPassedMuonCutsOnly      = 0;
  fPassedMVDCutsOnly       = 0;
  fPassedMJMatchCutsOnly   = 0;
  fPassedTJMatchCutsOnly   = 0;
  fPassedDIMuonCutsOnly    = 0;
  fPassedMCCutsOnly        = 0;
  fPassedAllCutsOnly       = 0;
  fForwardMuonsOnly        = 0;
  fBarrelMuonsOnly         = 0;
  fRearMuonsOnly           = 0;

  fPassedEvtakeCutsCons    = 0;
  fPassedTriggerCutsCons   = 0;
  fPassedVertexCutsCons    = 0;
  fPassedSinistraCutsCons  = 0;
  fPassedCalCutsCons       = 0;
  fPassedBacCutsCons       = 0;
  fPassedZufoCutsCons      = 0;
  fPassedJetCutsCons       = 0;
  fPassedTrackCutsCons     = 0;
  fPassedMuonCutsCons      = 0;
  fPassedMJMatchCutsCons   = 0;
  fPassedTJMatchCutsCons   = 0;
  fPassedMVDCutsCons       = 0;
  fPassedDIMuonCutsCons    = 0;
  fPassedMCCutsCons        = 0;
  fPassedAllCutsCons       = 0;
  fForwardMuonsCons        = 0;
  fBarrelMuonsCons         = 0;
  fRearMuonsCons           = 0;

  fPassedEvtakeCutsExcl    = 0;
  fPassedTriggerCutsExcl   = 0;
  fPassedVertexCutsExcl    = 0;
  fPassedSinistraCutsExcl  = 0;
  fPassedCalCutsExcl       = 0;
  fPassedBacCutsExcl       = 0;
  fPassedZufoCutsExcl      = 0;
  fPassedJetCutsExcl       = 0;
  fPassedTrackCutsExcl     = 0;
  fPassedMuonCutsExcl      = 0;
  fPassedMJMatchCutsExcl   = 0;
  fPassedTJMatchCutsExcl   = 0;
  fPassedMVDCutsExcl       = 0;
  fPassedDIMuonCutsExcl    = 0;
  fPassedMCCutsExcl        = 0;
  fPassedAllCutsExcl       = 0;
  fForwardMuonsExcl        = 0;
  fBarrelMuonsExcl         = 0;
  fRearMuonsExcl           = 0;
  
  fSecondStart = 0;             // start second
  fMinuteStart = 0;             // start minute
  fHourStart = 0;               // start hour
  fDayStart = 0;                // start day
  fMonthStart = 0;              // start month
  fYearStart = 0;               // start year

  fSecondEnd = 0;               // end second
  fMinuteEnd = 0;               // end minute
  fHourEnd = 0;                 // end hour
  fDayEnd = 0;                  // end day
  fMonthEnd = 0;                // end month
  fYearEnd = 0;                 // end year

  fDirectory = "";
  
  fLuminosity = 0;
  fLumiWeight = 1;
  fChosenMuons          = 0;
  fEfficiencyResetMuons = 0;

}

//_____________________________________________________________

GAnalysisHeader::~GAnalysisHeader() {
  //
  // GAnalysisHeader default destructor
  if ( gDebug ) cout << "GAnalysisHeader::~GAnalysisHeader dtor called" << endl;

}

//_____________________________________________________________

void GAnalysisHeader::SetStart() {
  //
  // set start time and date
  if ( gDebug ) cout << "GAnalysisHeader::SetStart() called" << endl;

  TDatime *time = new TDatime();
  fYearStart    = time->GetYear();
  fMonthStart   = time->GetMonth();
  fDayStart     = time->GetDay();
  fHourStart    = time->GetHour();
  fMinuteStart  = time->GetMinute();
  fSecondStart  = time->GetSecond();

  delete time;
}

//_____________________________________________________________

void GAnalysisHeader::SetEnd() {
  //
  // set start time and date
  if ( gDebug ) cout << "GAnalysisHeader::SetEnd() called" << endl;

  TDatime *time = new TDatime();
  fYearEnd      = time->GetYear();
  fMonthEnd     = time->GetMonth();
  fDayEnd       = time->GetDay();
  fHourEnd      = time->GetHour();
  fMinuteEnd    = time->GetMinute();
  fSecondEnd    = time->GetSecond();

  delete time;

  // calculate duration, calculate times and dates in seconds substract and extract
  // calculate only for day difference, reference, startday at 00:00:00


  if ( this->GetStartDay() == this->GetEndDay() ) {

    Int_t diff = 0;

    Int_t start = this->GetStartHour() * 3600 
      + this->GetStartMinute() * 60
      + this->GetStartSecond();

    Int_t end = this->GetEndHour() * 3600 
      + this->GetEndMinute() * 60
      + this->GetEndSecond();

    diff = end - start;

    fDayDiff = (Int_t)diff/(24*3600);
    fHourDiff = (Int_t)((diff%(24*3600))/3600); 
    fMinuteDiff = (Int_t)((diff%(3600))/60);
    fSecondDiff = (Int_t)((diff%(60)));

  } else {
    fDayDiff    = 0;
    fHourDiff   = 0;
    fMinuteDiff = 0;
    fSecondDiff = 0;
  }

  // if in data mode and none of evtake and mvdtake are used, take lumi from cards-file
  // else, the lumi is calculated from the evtake and mvdtake informations from gRuns
  // also if in mini-ntuple mode, take lumi from cards-file
  if ( gCards ) {
    if ( !gCards->GetMC() ) {
      if ( gCards->GetMiniNtuples() ) {
	fLuminosity = gCards->GetLuminosity();
      } else {
	if ( !gCards->GetEvtake() && !gCards->GetMvdtake() ) {
	  fLuminosity = gCards->GetLuminosity();
	} 
      }
    } else {
      fLuminosity = gCards->GetLuminosity();
      fLumiWeight = gCards->GetLumiWeight();
    }
  }
}

//_____________________________________________________________

void GAnalysisHeader::Increase() {
  //
  // increase counters
  if ( gDebug ) cout << "GAnalysisHeader::Increase() called" << endl;

  fProcessedEvents+=1;
  // only
  if ( gRuns->GetAllCuts() )
    fPassedEvtakeCutsOnly+=1;

  if ( gCards->GetMC() &&  !(gCards->GetMCLF() && gCards->GetDoFake()) )
    if ( gMCs->GetQ2SelectionCut() )
      fPassedMCSelectionCutsOnly+=1;

  if ( gTrigger->GetAllCuts() )
    fPassedTriggerCutsOnly+=1;

  if ( gVertex->GetAllCuts() )
    fPassedVertexCutsOnly+=1;

  if ( gSinistra->GetAllCuts() )
    fPassedSinistraCutsOnly+=1;

  if ( gCal->GetAllCuts() ) {
    fPassedCalCutsOnly+=1;
  }

  if ( gBac->GetAllCuts() ) {
    fPassedBacCutsOnly+=1;
  }
  if ( gZufo->GetAllCuts() )
    fPassedZufoCutsOnly+=1;

  if ( gJets->GetAllCuts() )
    fPassedJetCutsOnly+=1;

  if ( gTracks->GetAllCuts() )
    fPassedTrackCutsOnly+=1;

  if ( gMuons->GetAllCuts() ) {
    fPassedMuonCutsOnly+=1;
    fForwardMuonsOnly  += gMuons->GetForwardMuons();
    fBarrelMuonsOnly   += gMuons->GetBarrelMuons();
    fRearMuonsOnly     += gMuons->GetRearMuons();
  }
  if ( gMJMatchs->GetAllCuts() )
    fPassedMJMatchCutsOnly+=1;
  if ( gTJMatchs->GetAllCuts() ){
    fPassedTJMatchCutsOnly+=1;
  }
  if ( gMVD->GetAllCuts() )
    fPassedMVDCutsOnly+=1;

  if ( gDIMuons->GetAllCuts() )
    fPassedDIMuonCutsOnly+=1;

  if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) )
    if ( gMCs->GetAllCuts() )
      fPassedMCCutsOnly+=1;
  if ( this->GetAllCuts() )
    fPassedAllCutsOnly+=1;
  // consecutive
  if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
    if ( gRuns->GetAllCuts() )
      fPassedEvtakeCutsCons+=1;
 
    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() )
      fPassedMCSelectionCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() )
      fPassedTriggerCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() )
      fPassedVertexCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() )
      fPassedSinistraCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() )
      fPassedCalCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() )
      fPassedBacCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() )
      fPassedZufoCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() )
      fPassedJetCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() )
      fPassedTrackCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() ) {
      fPassedMuonCutsCons+=1;
      fForwardMuonsCons  += gMuons->GetForwardMuons();
      fBarrelMuonsCons   += gMuons->GetBarrelMuons();
      fRearMuonsCons     += gMuons->GetRearMuons();
    }

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() )
      fPassedMJMatchCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts())
      fPassedTJMatchCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts() && gDIMuons->GetAllCuts() )
      fPassedDIMuonCutsCons+=1;

    if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts() && gDIMuons->GetAllCuts() && gMVD->GetAllCuts() )
      fPassedMVDCutsCons+=1;

    if ( gCards->GetMC()&&  !(gCards->GetMCLF() && gCards->GetDoFake()) )
      if ( gRuns->GetAllCuts() && gMCs->GetQ2SelectionCut() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts() && gDIMuons->GetAllCuts() && gMVD->GetAllCuts() && gMCs->GetAllCuts() )
	fPassedMCCutsCons+=1;
  }
  else {
    if ( gRuns->GetAllCuts() )
      fPassedEvtakeCutsCons+=1;
    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() )
      fPassedTriggerCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() )
      fPassedVertexCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() )
      fPassedSinistraCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() )
      fPassedCalCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() )
      fPassedBacCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() )
      fPassedZufoCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() )
      fPassedJetCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() )
      fPassedTrackCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() ) {
      fPassedMuonCutsCons+=1;
      fForwardMuonsCons  += gMuons->GetForwardMuons();
      fBarrelMuonsCons   += gMuons->GetBarrelMuons();
      fRearMuonsCons     += gMuons->GetRearMuons();
    }

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() )
      fPassedMJMatchCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts())
      fPassedTJMatchCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts() && gDIMuons->GetAllCuts() )
      fPassedDIMuonCutsCons+=1;

    if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts() && gDIMuons->GetAllCuts() && gMVD->GetAllCuts() )
      fPassedMVDCutsCons+=1;

    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) )
      if ( gRuns->GetAllCuts() && gTrigger->GetAllCuts() && gVertex->GetAllCuts() && gSinistra->GetAllCuts() && gCal->GetAllCuts() && gBac->GetAllCuts() && gZufo->GetAllCuts() && gJets->GetAllCuts() && gTracks->GetAllCuts() && gMuons->GetAllCuts() && gMJMatchs->GetAllCuts() && gTJMatchs->GetAllCuts() && gDIMuons->GetAllCuts() && gMVD->GetAllCuts() && gMCs->GetAllCuts() )
	fPassedMCCutsCons+=1;
  }
  
  if ( this->GetAllCuts() )
    fPassedAllCutsCons+=1;
   if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
    if ( gTrigger->GetAllCuts() &&
	 gMCs->GetQ2SelectionCut() &&
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedEvtakeCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedTriggerCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedMCSelectionCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedVertexCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedSinistraCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedCalCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedBacCutsExcl+=1;


    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedZufoCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedJetCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedTrackCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() ) {
      fPassedMuonCutsExcl+=1;
      fForwardMuonsExcl  += gMuons->GetForwardMuons();
      fBarrelMuonsExcl   += gMuons->GetBarrelMuons();
      fRearMuonsExcl     += gMuons->GetRearMuons();
    }

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedMJMatchCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedTJMatchCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedDIMuonCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedMVDCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedMCCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gMCs->GetQ2SelectionCut() &&
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() &&
	 gMCs->GetAllCuts() )
      fPassedAllCutsExcl+=1;
  } else {
    // exclusive
    if ( gTrigger->GetAllCuts() &&  
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedEvtakeCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedTriggerCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedVertexCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedSinistraCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedCalCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedBacCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedZufoCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedJetCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedTrackCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() ) {
      fPassedMuonCutsExcl+=1;
      fForwardMuonsExcl  += gMuons->GetForwardMuons();
      fBarrelMuonsExcl   += gMuons->GetBarrelMuons();
      fRearMuonsExcl     += gMuons->GetRearMuons();
    }

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedMJMatchCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedTJMatchCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedDIMuonCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() )
      fPassedMVDCutsExcl+=1;

    if ( gRuns->GetAllCuts() &&  
	 gTrigger->GetAllCuts() && 
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gTracks->GetAllCuts()  &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      fPassedAllCutsExcl+=1;
  }

  // increase counter for chosen muons and reset efficiency muons
  if ( GetAllCuts() ) {
    for ( Int_t i = 0; i < gMJMatchs->GetNMatchs(); ++i ) {
      GMJMatch *match = gMJMatchs->GetMatch(i);
      if ( match->GetType() == kChosen ) {
	IncreaseChosenMuons();	  
	if ( match->GetMuon()->GetEfficiencyReset() ) {
	  IncreaseEfficiencyResetMuons();
	}
      }
    }
  }

}

//_____________________________________________________________

TString GAnalysisHeader::ReturnHeader(TString title) {
  //
  // return header information as char string
  if ( gDebug ) cout << "GAnalysisHeader::ReturnHeader() called" << endl;
  
  TString dummy;

  dummy.Append("==========================================================================\n");
  dummy.Append(title);
  dummy.Append("\n");
  dummy.Append("==========================================================================\n");
  dummy.Append("Analysis Job started : \n");
  if ( this->GetStartDay() < 10 ) {
    dummy.Append("0");
    dummy += this->GetStartDay();
  } else {
    dummy += this->GetStartDay();
  }
  dummy.Append(".");
  if ( this->GetStartMonth() < 10 ) {
    dummy.Append("0");
    dummy += this->GetStartMonth();
  } else {
    dummy += this->GetStartMonth();
  }
  dummy.Append(".");
  dummy += this->GetStartYear();
  dummy.Append(" ");
  if ( this->GetStartHour() < 10 ) {
    dummy.Append("0");
    dummy += this->GetStartHour();
  } else {
    dummy += this->GetStartHour();
  }
  dummy.Append(":");
  if ( this->GetStartMinute() < 10 ) {
    dummy.Append("0");
    dummy += this->GetStartMinute();
  } else {
    dummy += this->GetStartMinute();
  }
  dummy.Append(":");
  if ( this->GetStartSecond() < 10 ) {
    dummy.Append("0");
    dummy += this->GetStartSecond();
  } else {
    dummy += this->GetStartSecond();
  }
  dummy.Append("\n==========================================================================\n");

  return dummy;
}

//_____________________________________________________________

TString GAnalysisHeader::ReturnFooter(TString title) {
  //
  // return header information as char string
  if ( gDebug ) cout << "GAnalysisHeader::ReturnFooter() called" << endl;
  
  TString dummy;


  if ( (fChosenMuons > 0) ){
    Double_t ResetFraction = (Double_t)fEfficiencyResetMuons/(Double_t)fChosenMuons;
    
    if ( ResetFraction>=0.01 ) {
      dummy.Append("==========================================================================\n");
      dummy.Append("NUMBER OF EFFICIENCY RESET MUONS OUT OF RANGE!\nreset muons: ");
      dummy += fEfficiencyResetMuons;
      dummy.Append(" chosen muons: ");
      dummy += fChosenMuons;
      dummy.Append(" fraction: ");
      dummy += ResetFraction;
      dummy.Append("\n");
      dummy.Append("==========================================================================\n");
    }
  }


  dummy.Append("==========================================================================\n");
  dummy.Append(this->ReturnTitle(title));
  dummy.Append("\n");
  dummy.Append("==========================================================================\n");
  dummy.Append(this->ReturnLine("processed events",this->GetProcessedEvents(),this->GetProcessedEvents(),this->GetProcessedEvents()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed evtake cuts",this->GetPassedEvtakeCutsOnly(),this->GetPassedEvtakeCutsCons(),this->GetPassedEvtakeCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  if ( fPassedMCSelectionCutsOnly != 0 ) {
    dummy.Append(this->ReturnLine("events passed MC selection cuts",this->GetPassedMCSelectionCutsOnly(),this->GetPassedMCSelectionCutsCons(),this->GetPassedMCSelectionCutsExcl()));
    dummy.Append("\n==========================================================================\n");
  }
  dummy.Append(this->ReturnLine("events passed trigger cuts",this->GetPassedTriggerCutsOnly(),this->GetPassedTriggerCutsCons(),this->GetPassedTriggerCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed vertex cuts",this->GetPassedVertexCutsOnly(),this->GetPassedVertexCutsCons(),this->GetPassedVertexCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed sinistra cuts",this->GetPassedSinistraCutsOnly(),this->GetPassedSinistraCutsCons(),this->GetPassedSinistraCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed cal cuts",this->GetPassedCalCutsOnly(),this->GetPassedCalCutsCons(),this->GetPassedCalCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed bac cuts",this->GetPassedBacCutsOnly(),this->GetPassedBacCutsCons(),this->GetPassedBacCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed zufo cuts",this->GetPassedZufoCutsOnly(),this->GetPassedZufoCutsCons(),this->GetPassedZufoCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed jet cuts",this->GetPassedJetCutsOnly(),this->GetPassedJetCutsCons(),this->GetPassedJetCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed track cuts",this->GetPassedTrackCutsOnly(),this->GetPassedTrackCutsCons(),this->GetPassedTrackCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed muon cuts",this->GetPassedMuonCutsOnly(),this->GetPassedMuonCutsCons(),this->GetPassedMuonCutsExcl()));
  dummy.Append("\n");
  dummy.Append(this->ReturnLine("          forward muons",this->GetForwardMuonsOnly(),this->GetForwardMuonsCons(),this->GetForwardMuonsExcl()));
  dummy.Append("\n");
  dummy.Append(this->ReturnLine("          barrel muons",this->GetBarrelMuonsOnly(),this->GetBarrelMuonsCons(),this->GetBarrelMuonsExcl()));
  dummy.Append("\n");
  dummy.Append(this->ReturnLine("          rear muons",this->GetRearMuonsOnly(),this->GetRearMuonsCons(),this->GetRearMuonsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed muon-jet match cuts",this->GetPassedMJMatchCutsOnly(),this->GetPassedMJMatchCutsCons(),this->GetPassedMJMatchCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed track-jet match cuts",this->GetPassedTJMatchCutsOnly(),this->GetPassedTJMatchCutsCons(),this->GetPassedTJMatchCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed dimuon cuts",this->GetPassedDIMuonCutsOnly(),this->GetPassedDIMuonCutsCons(),this->GetPassedDIMuonCutsExcl()));

  if ( fPassedMCCutsOnly != 0 ) {
    dummy.Append("\n==========================================================================\n");
    dummy.Append(this->ReturnLine("events passed MC cuts",this->GetPassedMCCutsOnly(),this->GetPassedMCCutsCons(),this->GetPassedMCCutsExcl()));
  }

  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed mvd vertexing cuts",this->GetPassedMVDCutsOnly(),this->GetPassedMVDCutsCons(),this->GetPassedMVDCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append(this->ReturnLine("events passed all cuts",this->GetPassedAllCutsOnly(),this->GetPassedAllCutsCons(),this->GetPassedAllCutsExcl()));
  dummy.Append("\n==========================================================================\n");
  dummy.Append("Analysis Job ends : \n");
  if ( this->GetEndDay() < 10 ) {
    dummy.Append("0");
    dummy += this->GetEndDay();
  } else {
    dummy += this->GetEndDay();
  }
  dummy.Append(".");
  if ( this->GetEndMonth() < 10 ) {
    dummy.Append("0");
    dummy += this->GetEndMonth();
  } else {
    dummy += this->GetEndMonth();
  }
  dummy.Append(".");
  dummy += this->GetEndYear();
  dummy.Append(" ");
  if ( this->GetEndHour() < 10 ) {
    dummy.Append("0");
    dummy += this->GetEndHour();
  } else {
    dummy += this->GetEndHour();
  }
  dummy.Append(":");
  if ( this->GetEndMinute() < 10 ) {
    dummy.Append("0");
    dummy += this->GetEndMinute();
  } else {
    dummy += this->GetEndMinute();
  }
  dummy.Append(":");
  if ( this->GetEndSecond() < 10 ) {
    dummy.Append("0");
    dummy += this->GetEndSecond();
  } else {
    dummy += this->GetEndSecond();
  }
  dummy.Append("\n==========================================================================\n");
  dummy.Append("Analysis Job took : \n");
  if ( this->GetDiffDay() < 10 ) {
    dummy.Append("0");
    dummy += this->GetDiffDay();
  } else {
    dummy += this->GetDiffDay();
  }
  dummy.Append(" Days, ");
  if ( this->GetDiffHour() < 10 ) {
    dummy.Append("0");
    dummy += this->GetDiffHour();
  } else {
    dummy += this->GetDiffHour();
  }
  dummy.Append(" Hours, ");
  if ( this->GetDiffMinute() < 10 ) {
    dummy.Append("0");
    dummy += this->GetDiffMinute();
  } else {
    dummy += this->GetDiffMinute();
  }
  dummy.Append(" Minutes, ");
  if ( this->GetDiffSecond() < 10 ) {
    dummy.Append("0");
    dummy += this->GetDiffSecond();
  } else {
    dummy += this->GetDiffSecond();
  }
  dummy.Append(" Seconds\n");
  dummy.Append("==========================================================================\n");
  dummy.Append("Time per Event: ");
  // calculate time per event
  Double_t perev = (this->GetDiffDay() * 86400 + 
		    this->GetDiffHour() * 3600 +
		    this->GetDiffMinute() * 60 +
		    this->GetDiffSecond() );
  perev /= this->GetProcessedEvents();  
  // give result in ms
  perev *= 1000;
  dummy += perev;
  dummy.Append(" ms\n");
  dummy.Append("==========================================================================\n");
  dummy.Append("Luminosity: ");
  dummy += this->GetLuminosity();
  dummy.Append("\n");
  dummy.Append("==========================================================================\n");

  return dummy;
}

//_____________________________________________________________

void GAnalysisHeader::Header(TString title) {
  //
  // print header
  if ( gDebug ) cout << "GAnalysisHeader::Header(TString title) called" << endl;

  cout << this->ReturnHeader(title).Data() << endl;

}

//_____________________________________________________________

void GAnalysisHeader::Footer(TString title) {
  //
  // print footer
  if ( gDebug ) cout << "GAnalysisHeader::Footer(TString title) called" << endl;

  cout << this->ReturnFooter(title).Data() << endl;

}

//_____________________________________________________________

void GAnalysisHeader::Header(ofstream *stream, TString title) {
  //
  // stream header
  if ( gDebug ) cout << "GAnalysisHeader::Header(ofstream *stream, TString title) called" << endl;

  *stream << this->ReturnHeader(title).Data();

}

//_____________________________________________________________

void GAnalysisHeader::Footer(ofstream *stream, TString title) {
  //
  // stream header
  if ( gDebug ) cout << "GAnalysisHeader::Footer(ofstream *stream, TString title) called" << endl;

  *stream << this->ReturnFooter(title).Data();

}

//_____________________________________________________________

Bool_t GAnalysisHeader::GetAllCuts() {
  //
  // indicate if all cuts are fullfilled
  // if objects with cuts are added, please check if somewhere objects require
  // a specific combination of cuts which is not the complete list given here
  // check: GTrigger
  if ( gDebug ) cout << "GAnalysisHeader::GetAllCuts called" << endl;

  if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
    // if event list is created, then also MC events which fulfill 
    // true cuts on jets, Q2 and Y and Muons are taken
    if ( gCards->GetDoEventlist() && gMCs->GetAllMCCuts() ) {
      return kTRUE;
    } else {
      if ( gRuns->GetAllCuts() &&
	   gTrigger->GetAllCuts() &&
	   gVertex->GetAllCuts() && 
	   gSinistra->GetAllCuts() && 
	   gCal->GetAllCuts() && 
	   gBac->GetAllCuts() && 
	   gZufo->GetAllCuts() && 
	   gMuons->GetAllCuts() && 
	   gJets->GetAllCuts()  &&
	   gTracks->GetAllCuts() &&
	   gMJMatchs->GetAllCuts() &&
	   gTJMatchs->GetAllCuts() &&
	   gDIMuons->GetAllCuts() &&
	   gMVD->GetAllCuts() &&
	   gMCs->GetAllCuts() )
	return kTRUE;
      else
	return kFALSE;
    }
  } else {
    if ( gRuns->GetAllCuts() &&
	 gTrigger->GetAllCuts() &&
	 gVertex->GetAllCuts() && 
	 gSinistra->GetAllCuts() && 
	 gCal->GetAllCuts() && 
	 gBac->GetAllCuts() && 
	 gZufo->GetAllCuts() && 
	 gMuons->GetAllCuts() && 
	 gJets->GetAllCuts()  &&
	 gTracks->GetAllCuts() &&
	 gMJMatchs->GetAllCuts() &&
	 gTJMatchs->GetAllCuts() &&
	 gDIMuons->GetAllCuts() &&
	 gMVD->GetAllCuts() )
      return kTRUE;
    else
      return kFALSE;
  }
}

//_____________________________________________________________

TString  GAnalysisHeader::ReturnSevenDigits(Int_t counter) {
  //
  // returns character string 7 digits long for integer counter, 
  // in error, return longer string
  if ( gDebug ) cout << "GAnalysisHeader::ReturnSevenDigits called" << endl;

  TString output = "";

  if ( counter < 10 ) {
    output.Append("      ");
    output += counter;
  } else if ( counter < 100 ) {
    output.Append("     ");
    output += counter;
  } else if ( counter < 1000 ) {
    output.Append("    ");
    output += counter;
  } else if ( counter < 10000 ) {
    output.Append("   ");
    output += counter;
  } else if ( counter < 100000 ) {
    output.Append("  ");
    output += counter;
  } else if ( counter < 1000000 ) {
    output.Append(" ");
    output += counter;
  } else {
    output += counter;
  }

  return output.Data();
}
    
//_____________________________________________________________

TString  GAnalysisHeader::ReturnTitle(TString title) {
  //
  // returns character string consisting of title and heading for right
  // numnber of characters
  if ( gDebug ) cout << "GAnalysisHeader::ReturnTitle called" << endl;

  // space for heading
  Int_t length = 37;
  TString heading = title;
  Int_t blanks = length - heading.Length();

  TString output = "";
  
  output.Append(title);
  for ( Int_t i = 0; i < blanks; i++)
    output.Append(" ");

  output.Append(":    only | consecutive | exclusive");

  return output;
}
        
//_____________________________________________________________

TString  GAnalysisHeader::ReturnLine(TString category, Int_t only, Int_t consecutive, Int_t exclusive) {
  //
  // returns character string consisting of category and three counting categories
  // including format
  if ( gDebug ) cout << "GAnalysisHeader::ReturnLine called" << endl;

  // space for category
  Int_t length = 37;
  TString cat = category;
  Int_t blanks = length - cat.Length();

  TString output = "";
  
  output.Append(category);
  for ( Int_t i = 0; i < blanks; i++)
    output.Append(" ");

  output.Append(": ");
  output.Append(this->ReturnSevenDigits(only));
  output.Append(" |     ");
  output.Append(this->ReturnSevenDigits(consecutive));
  output.Append(" |   ");
  output.Append(this->ReturnSevenDigits(exclusive));

  return output;
}
        
//_____________________________________________________________

Bool_t GAnalysisHeader::CheckWeight() {
  //
  // determines event weight for general plots
  if ( gDebug ) cout << "GAnalysisHeader::CheckWeight called" << endl;

  if ( GetAllCuts() ) {
    // get weight from muon from chosen match, if all are taken into account, take first
    GMJMatch *match = gMJMatchs->GetChosen();

    // if Jpsi MC is processed and jpsireweighting activated reweight depending on hard ME pt 
    // (formula taken from A. Bertolin ZN 03-004, sec. 4.1.2):
    if( gCards->GetMCJPSIHRWG() && gCards->GetDoJpsiReweight() ) {
      //       if( gData->Getmc_pt()>0.0 ) {                                                                                                            // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //  	fEventWeight = 1.33*TMath::Min( (0.44+0.114*gData->Getmc_pt()*gData->Getmc_pt()) , 20.);                                                  // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       }                                                                                                                                        // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //       TF1 * user = new TF1("user","[0]*TMath::Min(([1]+[2]*x+[3]*x^2),[4])",0,17);                                                    // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //       user->SetParameters(1.,0,-0.04,0.15,8);                                                                                         // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //  EXT PARAMETER                                   STEP         FIRST                                                                   // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //   NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE                                                                // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //    1  p0           1.32848e+00   4.50376e-02   1.98924e-04  -1.11997e-02                                                              // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //    2  p1           4.37458e-01   2.83241e-02   9.54201e-05  -2.84796e-02                                                              // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //    3  p2          -3.73307e-02   5.12785e-02  -1.57081e-04  -2.54793e-02                                                              // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //    4  p3           1.14193e-01   1.31262e-02   3.17718e-05  -2.45895e-02                                                              // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      //       //    5  p4           2.02127e+01   4.61336e+00   1.15112e-03   0.00000e+00                                                              // 8th test version  (by first fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt, then comparing reweighted and non reweighted mc_pt spectra and fitting)
      
      // The 7th version (i.e. reweighting according to dimuonPt results in the best description, thus will become default. 
      // The 8th version (i.e. deriving the mc_pt reweighting formula from the dimuPt reweighted mc) yields acceptable results, thus could be used for xsec measurements.
      GDIMuon * dimuon = gDIMuons->GetChosen();          // 7th version (by fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt)
      if(dimuon) {                                       // 7th version (by fitting lm_us_is_data/lm_us_is_jpsihrwgMC, but with dimupt)
 
	//	fEventWeight = 0.385*TMath::Min(TMath::Exp(0.425*dimuon->GetdimuPt()),24.1);   
	fEventWeight = 0.7064*TMath::Min(TMath::Exp(0.5604*dimuon->GetdimuPt()),8.64);   
	/*
	Int_t secvtx   = 0;
	Int_t nrsecvtx = 0;

	if( gData->Getnr_secvtx() == 0 ){

	  nrsecvtx = gData->Getnr_secvtx();

	}

	if( gData->Getnr_secvtx() > 0 ){

	  for(Int_t i = 0; i < gData->Getnr_secvtx(); i++){

	    if( gData->Getvtxsec_x(i) == 666 ){

	      nrsecvtx = 0;
	    }

	    if(gData->Getvtxsec_x(i)!=666 && gData->Getvtxsec_y(i)!=666 && gData->Getvtxsec_z(i)!=666 && 
               gData->Getvtxredprm_x()!=666 && gData->Getvtxredprm_y()!= 666 && gData->Getvtxredprm_z()!= 666 ){

	      secvtx    = 1;
	      nrsecvtx += secvtx;
	    }
	  }
	  
	  if( nrsecvtx == 0 )    fEventWeight = fEventWeight *  0.53732;
	  else if(nrsecvtx == 1) fEventWeight = fEventWeight *  2.82459;
	  else if(nrsecvtx == 2) fEventWeight = fEventWeight *  4.5;
	  else if(nrsecvtx == 3) fEventWeight = fEventWeight * 11.82458;
	}
	*/
      }
      else {
      	fEventWeight = 1.;
      }	
    }
    
 // if matched muon exits reweight it according to muon weight:
    else if ( match != 0 ) {
      fEventWeight = match->GetMuon()->GetWeight();
    } 
    else {
      fEventWeight = 1.0;
      if ( gCards->GetMJMATCHNMatchs() > 0 ) 
	gLister->FillErrorList("GAnalysisHeader: CheckWeight(): no chosen match");
    }
    // get weight from trigger
    fEventWeight = fEventWeight * gTrigger->GetWeight();

    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()))
      {
	fEventWeight = fEventWeight * gMCs->GetWeight();
      }
  }
  else {
    fEventWeight = 1.0;
  }
  if(gCards->GetMCLF() && gCards->GetDoFake()){
    fEventWeight = fEventWeight*gTracks->GetFakeEventWeight()*gTrigger->GetWeight();
  }
 
  return kTRUE;
}
        
//_____________________________________________________________

Double_t GAnalysisHeader::GetWeight(GMuon* muon) {
  //
  // determines event weight for general plots if muon can be selected directly (GMuons plots)
  // done here to have the chance of addition of other weights
  if ( gDebug ) cout << "GAnalysisHeader::GetWeight called" << endl;

  Double_t weight = 1.0;
  
  // return private member weight, which is checked before the histograms are filled, taking only
  // the first valid muon
  if ( gCards->GetWeightFirstMuon() ) {
    weight = fEventWeight;
  } else {
    weight = muon->GetWeight();
    // get weight from trigger
    weight = weight * gTrigger->GetWeight();
    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake())) {
      weight = weight * gMCs->GetWeight();
    }
  }
  if(gCards->GetMCLF() && gCards->GetDoFake()){
    weight = weight*gTracks->GetFakeEventWeight();
  }

  return weight;
}


//_____________________________________________________________

TString GAnalysisHeader::PrintAllCuts(Bool_t formated) {
  //
  // print all cut flags
  if ( gDebug ) cout << "GAnalysisHeader::PrintAllCuts called" << endl;

  TString output = "";

  output.Append("gRuns: " );
  output += gRuns->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  if ( gCards->GetMC() ) {
    output.Append("gMCSelction: " );
    output += gMCs->GetAllMCCuts();
    if ( formated )
      output.Append("\n");
    else
      output.Append(" ");
  }
  
  output.Append("gTrigger: " );
  output += gTrigger->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gVertex: " );
  output += gVertex->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gSinistra: " );
  output += gSinistra->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gCal: " );
  output += gCal->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gBac: " );
  output += gBac->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gZufo: " );
  output += gZufo->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gMuons: " );
  output += gMuons->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gJets: " );
  output += gJets->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gTracks: " );
  output += gTracks->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gMJMatchs: " );
  output += gMJMatchs->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gTJMatchs: " );
  output += gTJMatchs->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gDIMuons: " );
  output += gDIMuons->GetAllCuts();
  if ( formated )
    output.Append("\n");
  else
    output.Append(" ");

  output.Append("gMVD: " );
  output += gMVD->GetAllCuts();

  if ( gCards->GetMC() ) {

    if ( formated )
      output.Append("\n");
    else
      output.Append(" ");
    output.Append("gMCs: " );
    output += gMCs->GetAllCuts();
  }
  output.Append("\n");
  return output;
}

