//
//
// GCards.cxx
//
// $Author: meyer $
// $Date: 2005/08/30 11:14:28 $
// $Revision: 1.108 $
//

#include <GCards.h>
#include <iostream>
#include <fstream>
#include <strstream>

#ifndef ROOT_TString
#include <TString.h>
#endif

#ifndef ROOT_TSystem
#include <TSystem.h>
#endif

using namespace std;

#ifndef __CINT__
ClassImp(GCards)
#endif

  GCards *gCards = 0;

//_____________________________________________________________
// GCards
// Card file variable class
//
//
GCards::GCards(TString name) : TObject() {
  //
  // GCards default constructor
  if ( gDebug ) cout << "GCards::GCards ctor called" << endl;

  // initialize ok flag
  fOK = kTRUE;

  // initialize pointers
  fInputFilePath        = 0;
  // compatibility to logchecker
  fAddToNames           = new TString("");
  fOutputPath           = 0;
  fOutputFileName       = 0;
  fDCacheFileName       = "";
  // initialze loop variables
  fStartEntry =  0;                 // start from beginning
  fEndEntry   = -1;                 // end after all entries

  // initialize output options
  fEventOut   = 10000;

  // initialize luminosity and MC flags
  fLuminosity     = 0;
  fLumiWeight     = 1;

  fHERA1          = kFALSE;
  fHERA2          = kFALSE;
  fMC             = kFALSE;
  fFMCK           = kFALSE;
  fMCOwn          = kFALSE;
  fMCOwnJets      = kFALSE;
  fMCLF           = kFALSE;
  fDIMuonMCplots  = kFALSE;
  fMCBBBAR        = kFALSE;
  fMCCCBAR        = kFALSE;
  fMCJPSIHRWG     = kFALSE;
  fMCPSIPRIMEHRWG = kFALSE;
  fMCRejectHFL    = kTRUE;
  fMCRunPeriod    = "notset";
  fMCQ2Cut        = 999999.99;
  fMCLowQ2Cut     = -999999.99;
  fMCQ2SelectionCut  = -999999.99;
  fMCQ2LowCut     = kTRUE;
  fMCYLowCut      = -999999.99;
  fMCYHighCut     = 999999.99;

  // initialize DoJpsiReweight & DoPsiPrimeReweight flag
  fDoJpsiReweight     = kFALSE;
  fDoPsiprimeReweight = kFALSE;

  // initialize DoFake
  fDoFake = kFALSE;

  fProduceFakeProbability = kFALSE;

  // initialize GMuon flag
  fGMuon       = kFALSE;

  // initialize DoEfficiency flag
  fDoEfficiency  = kFALSE;

  // initialize DoEventlist flag
  fDoEventlist  = kFALSE;

  // initialize WriteEventlistNtuple flag
  fWriteEventlistNtuple  = kFALSE;

  // initalize evtake and mvdtake flags
  fEvtake      = kFALSE;
  fMvdtake     = kFALSE;

  // initialize minimal and maximal runnr
  fMinimalRunnr = -999999;
  fMaximalRunnr = 999999;

  // initialize general variables
  fWeightFirstMuon = kFALSE;
  fMiniNtuples     = kFALSE;

  // initialize reading from dcache;
  fdCache          = kFALSE;

  // initialize muon operation quality run exclusion
  fMBTake          = -99;
  fFMUTake         = -99;

  // initialize exclusion of shifted vertex runs
  fExcludeShiftedVertexRuns = kFALSE;

  // initialize machine variables
  fPositron           = kFALSE;
  fEnergyLepton       = 27.5;
  fEnergyProton       = 820.0;
  fLowerEnergyProton  = 820.0;
  fHigherEnergyProton = 920.0;

  // initialize lists variables
  fProcEvents         = kFALSE;
  fErrorList          = kFALSE;
  fSelectionList      = kFALSE;
  fOutputList         = kFALSE;
  fOutputListGGENERAL = kFALSE;
  fOutputListRUNS     = kFALSE;
  fOutputListMUONS    = kFALSE;
  fOutputListCAL      = kFALSE;
  fOutputListBAC      = kFALSE;
  fOutputListJETS     = kFALSE;
  fOutputListMJMATCHS = kFALSE;
  fOutputListTJMATCHS = kFALSE;
  fOutputListSINISTRA = kFALSE;
  fOutputListTRACKS   = kFALSE;
  fOutputListVERTEX   = kFALSE;
  fOutputListZUFO     = kFALSE;
  fOutputListMC       = kFALSE;
  fOutputListDIMUONS  = kFALSE;
  fOutputListMVD      = kFALSE;
  fOutputSelected     = kFALSE;
  fOutputAll          = kFALSE;

  // initialize mass variables
  fMassMuon = 0.105658357;

  // initialize ggeneral variables
  fGGeneralGeneral   = kFALSE;
  fGGeneralControl   = kFALSE;

  // initialize mc variables
  fMcGeneral   = kFALSE;
  fMcControl   = kFALSE;

  // initialize trigger variables
  fTriggerGeneral              = kFALSE;
  fTriggerControl              = kFALSE;
  fTriggerTLTEXO96p00p         = 0;
  fTriggerTLTEXO03p04p         = 0;
  fTriggerTLTEXO05e06e         = 0;
  fTriggerTLTEXO06p07p         = 0;
  fTriggerTLTHPP96p00p         = 0;
  fTriggerTLTHPP03p04p         = 0;
  fTriggerTLTHPP05e06e         = 0;
  fTriggerTLTHPP06p07p         = 0;
  fTriggerTLTHFL96p00p         = 0;
  fTriggerTLTHFL99p00p         = 0;
  fTriggerTLTHFL03p04p         = 0;
  fTriggerTLTHFL05e06e         = 0;
  fTriggerTLTHFL06p07p         = 0;
  fTriggerTLTDIS96p00p         = 0;
  fTriggerTLTDIS03p04p         = 0;
  fTriggerTLTDIS05e06e         = 0;
  fTriggerTLTDIS06p07p         = 0;
  fTriggerTLTMUO96p00p         = 0;
  fTriggerTLTMUO03p04p         = 0;
  fTriggerTLTMUO05e06e         = 0;
  fTriggerTLTMUO06p07p         = 0;
  fTriggerTLTSPP03p04p         = 0;
  fTriggerTLTSPP05e06e         = 0;
  fTriggerTLTSPP06p07p         = 0;
  fTriggerEfficiencyCorrection = kFALSE;
  fTriggerEffCorr1011          = 1.0;
  fTriggerEffCorr4254Forward   = 1.0;
  fTriggerEffCorr4254Barrel    = 1.0;
  fTriggerEffCorr4254Rear      = 1.0;

  // initialize sinistra variables
  fSinistraGeneral   = kFALSE;
  fSinistraControl   = kFALSE;
  fSinistraDIS       = kFALSE;
  fSinistraNoCut     = kFALSE;
  fSinistraProbCut   = 1.0;
  fSinistraEnergyCut = 0.0;
  fSinistraYELCut    = 1.0;
  fSinistraYELHighCut= 1.0;
  fSinistraYELLowCut = 0.0;
  fSinistraQ2LowCut  = -9999.99;

  // initialize cal variables
  fCALGeneral   = kFALSE;
  fCALControl   = kFALSE;
  fCALEmpzCut   = 0;
  fCALYJBLOWCut = -9999.99;
  fCALYJBUPCut  = 999.99;
  fCALModeETCut = -99;
  fCALETCut     = 0.0;
  fCALTimeCut   = 9999.99;
  fCALPtOvEtCut = 9999.99;

  // initialize bac variables
  fBACGeneral   = kFALSE;
  fBACControl   = kFALSE;
  fBACbac_etotLOWCut = -9999.99;
  fBACbac_etotUPCut  =  9999.99;
  fBACnbacmuCut   = 9999;

  // initialize ZUFO variables
  fZUFOGeneral     = kFALSE;
  fZUFOControl     = kFALSE;
  fZUFOYJBLOWCut   = -9999.99;
  fZUFOYJBUPCut    = 9999.99;
  fZUFOEmpzUpCut   = 9999.99;
  fZUFOEmpzLowCut  = -99999.99;
  fZUFOPtHadMaxCut = 999999.99;
  fZUFOQ2PrimeLowCut = 0.;

  // initialize JET variables
  fNewNtuple     = kTRUE;
  fJETGeneral    = kFALSE;
  fJETControl    = kFALSE;
  fJETBreit      = kFALSE;
  fJETNCut       = 0;
  fJETPtACut     = 0.;
  fJETPtBCut     = 0.;
  fJETEtaLowCut  = -999999.99;
  fJETEtaUpCut   =  999999.99;
  //  fJETQ2PrimeLowCut = 0.;
  fJETCutOnEt    = kFALSE;

  // init vertex variables
  fVertexGeneral           = kFALSE;
  fVertexControl           = kFALSE;
  fVertexNomX              = 0.;
  fVertexNomXOld           = 0.;
  fVertexNomXNew           = 0.;
  fVertexNomY              = 0.;
  fVertexNomZ              = 0.;
  fVertexZCut              = 2000.;
  fVertexXCut              = kFALSE;
  fVertexYCut              = kFALSE;
  fVertexXYCut             = 9999.99;
  fVertexBeamSpotCut       = kFALSE;
  fVertexBeamSpotX         = 0.0;
  fVertexBeamSpotXSigma    = 0.0;
  fVertexBeamSpotY         = 0.0;
  fVertexBeamSpotYSigma    = 0.0;
  fVertexBeamSpotZ         = 0.0;
  fVertexBeamSpotZSigma    = 0.0;
  fVertexOldBeamSpotX      = 0.0;
  fVertexOldBeamSpotXSigma = 0.0;
  fVertexOldBeamSpotY      = 0.0;
  fVertexOldBeamSpotYSigma = 0.0;
  fVertexOldBeamSpotZ      = 0.0;
  fVertexOldBeamSpotZSigma = 0.0;
  fVertexNewBeamSpotX      = 1.91999996;
  fVertexNewBeamSpotXSigma = 0.0;
  fVertexNewBeamSpotY      = 0.170000002;
  fVertexNewBeamSpotYSigma = 0.0;
  fVertexNewBeamSpotZ      = 0.0;
  fVertexNewBeamSpotZSigma = 0.0;
  fVertexUseAllRuns        = kFALSE;  
  // initialize logchecker variables
  fLogActivate      = kFALSE;
  fLogTermNumber    = 0;
  fLogCountNumber   = 0;

  // initialize MUON variables
  fMUONGeneral                        =  kFALSE;
  fMUONControl                        =  kFALSE;
  fMUONNCut                           =  1;
  fMUONFillAll                        =  kFALSE;
  fMUONBremProb                       =  0.0;
  fMUONBremChamberFlag                =  -99;
  fMUONMPMProb                        =  0.0;
  fMUONMUBACBacFlag                   =  9999999.99;
  fMUONChamberFlagCut                 =  3;
  fMUONMfpro                          =  0.00;
  fMUONMfndf                          =  0;
  fMUONMfz                            =  999999999;
  fMUONBACFQuality                    =  -99;
  fMUONVcidLowCut                     =  0;
  fMUONVcidUpCut                      =  999;
  fMUONModifyQuality                  =  kFALSE;
  fMuqualServicePack1                 =  kFALSE;
  fMUONEfficiencyCorrection           =  kFALSE;
  fMuqualBasedEffCorr                 =  kFALSE;
  fMUONReadEfficiencyFiles            =  kFALSE;
  fMUONEfficiencyFile                 =  "";
  fMUONEfficiencyMPMATCHPtNBins       =  -99;
  fMUONEfficiencyMPMATCHPtBins        =  0;
  fMUONEfficiencyBREMATPtNBins        =  -99;
  fMUONEfficiencyBREMATPtBins         =  0;
  fMUONEfficiencyMUBACPtNBins         =  -99;
  fMUONEfficiencyMUBACPtBins          =  0;
  fMUONTIGHTEfficiencyFile            =  "";
  fMUONTIGHTEfficiencyMPMATCHPtNBins  =  -99;
  fMUONTIGHTEfficiencyMPMATCHPtBins   =  0;
  fMUONTIGHTEfficiencyBREMATPtNBins   =  -99;
  fMUONTIGHTEfficiencyBREMATPtBins    =  0;
  fMUONTIGHTEfficiencyMUBACPtNBins    =  -99;
  fMUONTIGHTEfficiencyMUBACPtBins     =  0;
  fMUONEfficiencyCutOff               =  9999.99;
  fMUONCalculateMuonIsolation         =  kFALSE;
  fMUONMinIsolation10Veto             =  -99999.99;
  fMUONExcludeMamma                   =  kFALSE;

  fFMUONEtaLow           = 1.3;
  fFMUONEtaUp            = 99.0;
  fFMUONP                = 0.0;
  fFMUONPt               = 0.0;
  fFMUONQualCut1         = -99;
  fFMUONPTCut1           = 0.0;
  fFMUONQualCut2         = -99;
  fFMUONPTCut2           = 0.0;
  fFMUONFinder           = 255; 
  fFMUONEfficiency99p00p = 1.;
  fFMUONEfficiency98e99e = 1.;
  fFMUONEfficiency96p97p = 1.;
  fFMUONEfficiency03p04p = 1.;
  fFMUONEfficiency05e06e = 1.;
  fFMUONEfficiency06p07p = 1.;
  fFMUONOnlyVertexFitted = kFALSE;

  fBMUONEtaLow           = -0.9;
  fBMUONEtaUp            = 1.3;
  fBMUONP                = 0.0;
  fBMUONPt               = 0.0;
  fBMUONQualCut1         = -99;
  fBMUONPTCut1           = 0.0;
  fBMUONQualCut2         = -99;
  fBMUONPTCut2           = 0.0;
  fBMUONFinder           = 255; 
  fBMUONEfficiency99p00p = 1.;
  fBMUONEfficiency98e99e = 1.;
  fBMUONEfficiency96p97p = 1.;
  fBMUONEfficiency03p04p = 1.;
  fBMUONEfficiency05e06e = 1.;
  fBMUONEfficiency06p07p = 1.;
  fBMUONOnlyVertexFitted = kFALSE;

  fRMUONEtaLow           = -99.0;
  fRMUONEtaUp            = -0.9;
  fRMUONP                = 0.0;
  fRMUONPt               = 0.0;
  fRMUONQualCut1         = -99;
  fRMUONPTCut1           = 0.0;
  fRMUONQualCut2         = -99;
  fRMUONPTCut2           = 0.0;
  fRMUONFinder           = 255; 
  fRMUONEfficiency99p00p = 1.;
  fRMUONEfficiency98e99e = 1.;
  fRMUONEfficiency96p97p = 1.;
  fRMUONEfficiency03p04p = 1.;
  fRMUONEfficiency05e06e = 1.;
  fRMUONEfficiency06p07p = 1.;
  fRMUONOnlyVertexFitted = kFALSE;

  // initialize TRACKS variables
  fTRACKSGeneral            = kFALSE;
  fTRACKSControl            = kFALSE;
  fTRACKSMultiplicity       = 0;
  fTRACKSUsedSuperLayersCut = 0;
  fTRACKSUsedHitsCut        = 0;
  fTRACKSUsedStereoHitsCut  = 0;
  fTRACKSVertexCut          = 9999;
  fTRACKSMinVertexCut       = -9999;
  fTRACKSTotalOvVertexCut   = 9999.99;
  fTRACKSZHCut              = 9999.99;
  fTRACKSMVDHitsCut         = 0;
  fTRACKSType               = 0;

  // initialize MJMATCH variables
  fMJMATCHGeneral             = kFALSE;
  fMJMATCHControl             = kFALSE;
  fMJMATCHJetPtCut            = 0.0;
  fMJMATCHMuMinusJetPtCut     = 0.0;
  fMJMATCHNMatchs             = 0;
  fMJMATCHPtRelLow            = 0.0;
  fMJMATCHPtRelHigh           = 9999.99;
  fMJMATCHTakeAllGood         = kFALSE;
  fMJMATCHPtRelCorrection     = kFALSE;
  fMJMATCHPtRelCorrFilename   = "";
  fMJMATCHPtRelCorrCMCWeight  = 1.0;
  fMJMATCHPtRelCorrLFMCWeight = 1.0;

  // initialize TJMATCH variables
  fTJMATCHGeneral             = kFALSE;
  fTJMATCHControl             = kFALSE;
  fTJMATCHNMatchs             = 0;
  fTJMATCHJetPtCut            = 0.0;
  fTJMATCHTrackMinusJetPtCut  = 0.0;
  fTJMATCHAssociationCone     = 0.0;

  // initialize MVD variables
  fMVDActivate          = kFALSE;
  fMVDGeneral           = kFALSE;
  fMVDControl           = kFALSE;

  // initialize DIMUON variables
  fDIMUONGeneral          = kFALSE;
  fDIMUONControl          = kFALSE;
  fDIMUONInvMassLowCut    = 0.;
  fDIMUONInvMassHighCut   = 9999.99;
  fDIMUONSqSumIsolationCut= 0.0;
  fDIMUONSqSumIsolationPeakCut= 0.0;
  fDIMUONSqSumIsolationContCut= 0.0;
  fDIMUONDeltaRCut        = 0.0;
  fDIMUONDeltaPhiCut      = 0.0;
  fDIMUONDeltaThetaCut    = 0.0;
  fDIMUONDeltaEtaCut    = 9999.0;

  fDIMUONPtAsymetryCut    = 0.0;
  fDIMUONEtFractionHigh1Cut    = 9999.0;
  fDIMUONEtFractionHigh2Cut    = 9999.0;
  fDIMUONEtFractionLowCut    = 0.0;

  fDIMUONNDimuons         = 0;
  fDIMUONDifCharge        = kFALSE;
  fDIMUONCharmMCJpsi      = kFALSE;
  fDIMUONCharmMCPsiprime  = kFALSE;

  // initialize TRIMUON variables
  fTRIMUONGeneral          = kFALSE;
  fTRIMUONControl          = kFALSE;
  fTRIMUONInvMassLowCut    = 0.;
  fTRIMUONInvMassHighCut   = 9999.99;
  fTRIMUONSqSumIsolationCut= 0.0;
  fTRIMUONSqSumIsolationPeakCut= 0.0;
  fTRIMUONSqSumIsolationContCut= 0.0;
  fTRIMUONDeltaRCut        = 0.0;
  fTRIMUONDeltaPhiCut      = 0.0;
  fTRIMUONDeltaThetaCut    = 0.0;
  fTRIMUONDeltaEtaCut    = 9999.0;

  fTRIMUONPtAsymetryCut    = 0.0;
  fTRIMUONEtFractionHigh1Cut    = 9999.0;
  fTRIMUONEtFractionHigh2Cut    = 9999.0;
  fTRIMUONEtFractionLowCut    = 0.0;

  fTRIMUONNTrimuons         = 0;
  fTRIMUONDifCharge        = kFALSE;
  fTRIMUONCharmMCJpsi      = kFALSE;
  fTRIMUONCharmMCPsiprime  = kFALSE;

  // initialize PictureMaker Options

  fPICTURES_PS              = kTRUE; 
  fPICTURES_GIF             = kTRUE; 
  fPICTURES_EPS             = kTRUE; 
  fPICTURES_JPG             = kTRUE; 
  fPICTUREScomp_ptrel       = kFALSE;
  fPICTUREScomp_muon        = kFALSE;
  fPICTUREScomp_jet         = kFALSE;
  fPICTUREScomp_mjmatch     = kFALSE;
  fPICTUREScomp_cal         = kFALSE;
  fPICTUREScomp_tracks      = kFALSE;
  fPICTUREScomp_trigger     = kFALSE;
  fPICTUREScomp_zufo        = kFALSE;
  fPICTUREScomp_sinistra    = kFALSE;
  fPICTUREScomp_disonly     = kFALSE;
  fPICTUREScomp_phponly     = kTRUE; 
  
  fPICTURESONED_dimuon      = kFALSE;
  fPICTURESONED_track       = kFALSE;
  fPICTURESONED_muon        = kFALSE;
  
  fPICTURESONEDMC_dimuon    = kFALSE;
  fPICTURESONEDMC_mc        = kFALSE;
  fPICTURESONEDMC_track     = kFALSE;
  fPICTURESONEDMC_muon      = kFALSE;
  
  fPICTURESTWOD_mjmatch     = kFALSE;
  fPICTURESTWODMC_cal       = kFALSE;
  fPICTURESTWODMC_zufo      = kFALSE;
  fPICTURESTWODMC_mc        = kFALSE;
  fPICTURESTWODMC_muon      = kFALSE;
  fPICTURESTWODMC_mjmatch   = kFALSE;
  
  fPICTURESTWODMCzoomed_mc  = kFALSE;
  
  fPICTURESEfficiencyFull   = kFALSE;

  // number of check terms limited to 20 by hand
  fLogTerms      = new TString[20];
  fLogCountTerms = new TString[20];
  fPositiveFMCK  = kFALSE;
  gCards = this;

  this->ReadControlCards(name);

}

//_____________________________________________________________

GCards::~GCards() {
  //
  // GCards default destructor
  if ( gDebug ) cout << "GCards::~GCards dtor called" << endl;

  // destroy pointers if necessary
  if ( fLogTerms          != 0 ) delete [] fLogTerms;
  if ( fLogCountTerms     != 0 ) delete [] fLogCountTerms;
  if ( fOutputFileName    != 0 ) delete fOutputFileName;
  if ( fOutputPath        != 0 ) delete fOutputPath;
  if ( fAddToNames        != 0 ) delete fAddToNames;
  if ( fInputFilePath     != 0 ) delete fInputFilePath;

}

//_____________________________________________________________

Bool_t GCards::ReadControlCards(TString name) {
  //
  // read in control cards
  if ( gDebug > 1 ) cout << endl << "GCards::ReadControlCards() called" << endl << endl;

  TString *line = new TString("");
  ifstream input_stream(name,ios::in);

  if ( input_stream == 0 ) {
    cout << endl << "GCards::ReadControlCards(): cardname is wrong or cardfile does not exist" << endl << endl;
    fOK = kFALSE;
    return kFALSE;
  }

  while ( line->ReadLine(input_stream) ) {
    if ( !line->BeginsWith("C") || line->BeginsWith("CAL") ) {
      this->ReadGeneral(line);
      this->ReadMachine(line);
      this->ReadLists(line);
      this->ReadMass(line);
      this->ReadGGeneral(line);
      this->ReadMc(line);
      this->ReadTrigger(line);
      this->ReadSinistra(line);
      this->ReadCal(line);
      this->ReadBac(line);
      this->ReadZufo(line);
      this->ReadJet(line);
      this->ReadVertex(line);
      this->ReadMuon(line);
      this->ReadFMuon(line);
      this->ReadBMuon(line);
      this->ReadRMuon(line);
      this->ReadTracks(line);
      this->ReadMJMatch(line);
      this->ReadTJMatch(line);
      this->ReadMVD(line);
      this->ReadDIMuon(line);
      this->ReadTRIMuon(line);
      this->ReadLogChecker(line);
      this->ReadPictures(line);
    }
  }
  return kTRUE;
}

//_____________________________________________________________

TString* GCards::GetOutputFileName() {
  //
  // return Output file name incl. path
  if ( gDebug > 1 ) cout << endl << "GCards::GetOutputFileName() called" << endl << endl;

  TString *dummy = new TString(fOutputPath->Data());

  if ( dummy->EndsWith(".") )
    return fOutputFileName;
  else {
    dummy->Append(*fOutputFileName);
    return dummy;
  }
}
  
//_____________________________________________________________

Bool_t GCards::ReadGeneral(TString *line) {
  //
  // read cards for General Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadGeneral() called" << endl << endl;

  if ( line->BeginsWith("GENERAL") ) {
    line->ReplaceAll("GENERAL-","");
	
    // InputFilePath
    if ( line->BeginsWith("INPUTDIR") ) {
      line->ReplaceAll("INPUTDIR ","");
      fInputFilePath = new TString(*line);
      // determine AddToNames
//       fAddToNames = new TString("");
      if ( ! (fInputFilePath->EndsWith("data/") || fInputFilePath->EndsWith("data")) ) {
	// get last dir and add to all outputnames
	TString temp = fInputFilePath->Data();
	for ( Int_t i = 0; i < temp.Length(); i++ ) {
	  TString dummy = temp(temp.Length()-i-1);
	  if ( !dummy.Contains("/") )
	    fAddToNames->Prepend(dummy);
	  else if ( i != 0 )
	    break;
	}
      }
      if ( fAddToNames->Length() > 0 )
	fAddToNames->Prepend("_");
      if ( gDebug ) cout << "     fInputFilePath: " << fInputFilePath->Data() << endl;
      if ( gDebug ) cout << "     fAddToNames: " << fAddToNames->Data() << endl;
    }

    // OutputPath
    if ( line->BeginsWith("OUTPUTPATH") ) {
      line->ReplaceAll("OUTPUTPATH ","");
      if ( !gSystem->AccessPathName(line->Data()) ) {
	fOutputPath = new TString(line->Data());
	if ( gDebug ) cout << "     fOutputPath: " << fOutputPath->Data() << endl;
      } else {
	cout << "GCards::ReadControlCards() problems with OutputPath!" << endl;
      }
    }

    // OutputFileName
    if ( line->BeginsWith("OUTPUTFILE") ) {
      line->ReplaceAll("OUTPUTFILE ","");
      fOutputFileName = new TString(*line);
      fOutputFileName->ReplaceAll(".root","");
      fOutputFileName->Append(fAddToNames->Data());
      fOutputFileName->Append(".root");
      if ( gDebug ) cout << "     fOutputFileName: " << fOutputFileName->Data() << endl;
    }

    if (line->BeginsWith("HERA1") ) {
      line->ReplaceAll("HERA1 ","");
      if ( line->Contains("OFF") || line->Contains("NO") )
	fHERA1 = kFALSE;
      else 
	fHERA1 = kTRUE;
    }

    if (line->BeginsWith("HERA2") ) {
      line->ReplaceAll("HERA2 ","");
      if ( line->Contains("OFF") || line->Contains("NO") )
	fHERA2 = kFALSE;
      else 
	fHERA2 = kTRUE;
    }

    // start entry
    if ( line->BeginsWith("STARTENTRY") ) {
      line->ReplaceAll("STARTENTRY ","");
      istrstream stream(line->Data());
      stream >> fStartEntry;
      if ( gDebug ) cout << "     fStartEntry    : " << fStartEntry             << endl;
    }

    // end entry
    if ( line->BeginsWith("ENDENTRY") ) {
      line->ReplaceAll("ENDENTRY ","");
      istrstream stream(line->Data());
      stream >> fEndEntry;
      if ( gDebug ) cout << "     fEndEntry      : " << fEndEntry               << endl;
    }

    // event output each number of processed events
    if ( line->BeginsWith("EVENTOUT") ) {
      line->ReplaceAll("EVENTOUT ","");
      istrstream stream(line->Data());
      stream >> fEventOut;
      if ( gDebug ) cout << "     fEventOut    : " << fEventOut               << endl;
    }

    // luminosity
    if ( line->BeginsWith("LUMINOSITY") ) {
      line->ReplaceAll("LUMINOSITY ","");
      istrstream stream(line->Data());
      stream >> fLuminosity;
      if ( gDebug ) cout << "     fLuminosity    : " << fLuminosity               << endl;
    }
    // luminosity
    if ( line->BeginsWith("MCWEIGHT") ) {
      line->ReplaceAll("MCWEIGHT ","");
      istrstream stream(line->Data());
      stream >> fLumiWeight;
      if ( gDebug ) cout << "     fLumiWeight    : " << fLumiWeight               << endl;
    }

    // true Q2 cut
    if ( line->BeginsWith("Q2MCCUT") ) {
      line->ReplaceAll("Q2MCCUT ","");
      istrstream stream(line->Data());
      stream >> fMCQ2Cut;
      if ( gDebug ) cout << "     fMCQ2Cut    : " << fMCQ2Cut                     << endl;
    }

    // true Q2LOW cut
    if ( line->BeginsWith("Q2LOWMCCUT") ) {
      line->ReplaceAll("Q2LOWMCCUT ","");
      istrstream stream(line->Data());
      stream >> fMCLowQ2Cut;
      if ( gDebug ) cout << "     fMCLowQ2Cut    : " << fMCLowQ2Cut                     << endl;
    }

    // true Q2 selection cut
    if ( line->BeginsWith("Q2MCSELECTIONCUT") ) {
      line->ReplaceAll("Q2MCSELECTIONCUT ","");
      istrstream stream(line->Data());
      stream >> fMCQ2SelectionCut;
      if ( gDebug ) cout << "     fMCQ2SelectionCut    : " << fMCQ2SelectionCut    << endl;
    }
    // true low Q2 cut
    if ( line->BeginsWith("Q2MCLOWCUT") ) {
      line->ReplaceAll("Q2MCLOWCUT ","");
      if ( line->Contains("OFF") || line->Contains("NO") )
	fMCQ2LowCut = kFALSE;
      else 
	fMCQ2LowCut = kTRUE;	
      if ( gDebug ) cout << "     fMCQ2LowCut    : " << fMCQ2LowCut                     << endl;
    }

    // true YLow cut
    if ( line->BeginsWith("YLOWMCCUT") ) {
      line->ReplaceAll("YLOWMCCUT ","");
      istrstream stream(line->Data());
      stream >> fMCYLowCut;
      if ( gDebug ) cout << "     fMCYLowCut    : " << fMCYLowCut                     << endl;
    }

    // true YHigh cut
    if ( line->BeginsWith("YHIGHMCCUT") ) {
      line->ReplaceAll("YHIGHMCCUT ","");
      istrstream stream(line->Data());
      stream >> fMCYHighCut;
      if ( gDebug ) cout << "     fMCYHighCut    : " << fMCYHighCut                     << endl;
    }

    // fmckin orange block info
    if ( line->BeginsWith("POSITIVEFMCK") ) {
      line->ReplaceAll("POSITIVEFMCK ","");
      if ( line->Contains("ON") )
	fPositiveFMCK = kTRUE;
      else
	fPositiveFMCK = kFALSE;
      if ( gDebug ) cout << "     fPositiveFMCK: " << fFMCK << endl;
    }

    // light flavour monte carlo flag
    if ( line->BeginsWith("LFMC") ) {
      line->ReplaceAll("LFMC ","");
      if ( line->Contains("ON") )
	fMCLF = kTRUE;
      else
	fMCLF = kFALSE;
      if ( gDebug ) cout << "     fMCLF: " << fMCLF << endl;
    }
    // fmckin orange block info
    if ( line->BeginsWith("FMCK") ) {
      line->ReplaceAll("FMCK ","");
      if ( line->Contains("ON") )
	fFMCK = kTRUE;
      else
	fFMCK = kFALSE;
      if ( gDebug ) cout << "     fFMCK: " << fFMCK << endl;
    }

    // light flavour monte carlo flag
    if ( line->BeginsWith("BBBARMC") ) {
      line->ReplaceAll("BBBARMC ","");
      if ( line->Contains("ON") )
	fMCBBBAR = kTRUE;
      else
	fMCBBBAR = kFALSE;
      if ( gDebug ) cout << "     fMCBBBAR: " << fMCBBBAR << endl;
    }

    // open charm monte carlo flag
    if ( line->BeginsWith("CCBARMC") ) {
      line->ReplaceAll("CCBARMC ","");
      if ( line->Contains("ON") )
	fMCCCBAR = kTRUE;
      else
	fMCCCBAR = kFALSE;
      if ( gDebug ) cout << "     fMCCCBAR: " << fMCCCBAR << endl;
    }

    // Herwig jspi monte carlo flag
    // Use with GetMCJPSIHRWG.
    if ( line->BeginsWith("JPSIHRWGMC") ) {
      line->ReplaceAll("JPSIHRWGMC ","");
      if ( line->Contains("ON") )
	fMCJPSIHRWG = kTRUE;
      else
	fMCJPSIHRWG = kFALSE;
      if ( gDebug ) cout << "     fMCJPSIHRWG: " << fMCJPSIHRWG << endl;
    }

    // Herwig psiprime monte carlo flag
    // Use with GetMCPSIPRIMEHRWG.
    if ( line->BeginsWith("PSIPRIMEHRWGMC") ) {
      line->ReplaceAll("PSIPRIMEHRWGMC ","");
      if ( line->Contains("ON") )
	fMCPSIPRIMEHRWG = kTRUE;
      else
	fMCPSIPRIMEHRWG = kFALSE;
      if ( gDebug ) cout << "     fMCPSIPRIMEHRWG: " << fMCPSIPRIMEHRWG << endl;
    }


    // reject hfl in lf mc samples
    if ( line->BeginsWith("REJECTHFL") ) {
      line->ReplaceAll("REJECTHFL ","");
      if ( line->Contains("ON") )
	fMCRejectHFL = kTRUE;
      else
	fMCRejectHFL = kFALSE;
      if ( gDebug ) cout << "     fMCRejectHFL: " << fMCRejectHFL << endl;
    }

    // flag for activation of own MC block
    if ( line->BeginsWith("OWNMC") ) {
      line->ReplaceAll("OWNMC ","");
      if ( line->Contains("ON") )
	fMCOwn = kTRUE;
      else
	fMCOwn = kFALSE;
      if ( gDebug ) cout << "     fMCOwn: " << fMCOwn << endl;
    }

    // flag for activation of own MC jets block
    if ( line->BeginsWith("OWNJETSMC") ) {
      line->ReplaceAll("OWNJETSMC ","");
      if ( line->Contains("ON") )
	fMCOwnJets = kTRUE;
      else
	fMCOwnJets = kFALSE;
      if ( gDebug ) cout << "     fMCOwnJets: " << fMCOwnJets << endl;
    }

    // flag for activation of MC Dimuon plots
    if ( line->BeginsWith("DIMUONMCPLOTS") ) {
      line->ReplaceAll("DIMUONMCPLOTS ","");
      if ( line->Contains("ON") )
	fDIMuonMCplots = kTRUE;
      else
	fDIMuonMCplots = kFALSE;
      if ( gDebug ) cout << "     fDIMuonMCplots: " << fDIMuonMCplots << endl;
    }

    // monte carlo flag
    if ( line->BeginsWith("MC") ) {
      line->ReplaceAll("MC ","");
      if ( line->Contains("ON") )
	fMC = kTRUE;
      else
	fMC = kFALSE;
      if ( gDebug ) cout << "     fMC: " << fMC << endl;
    }

    // monte carlo flag
    if ( line->BeginsWith("RUNPERIODMC") ) {
      line->ReplaceAll("RUNPERIODMC ","");
      fMCRunPeriod = *line;
      if ( gDebug ) cout << "     fMCRunPeriod: " << fMCRunPeriod << endl;
    }

    // gmuon flag
    if ( line->BeginsWith("GMUON") ) {
      line->ReplaceAll("GMUON ","");
      if ( line->Contains("ON") )
	fGMuon = kTRUE;
      else
	fGMuon = kFALSE;
      if ( gDebug ) cout << "     fGMuon: " << fGMuon << endl;
    }

    // doefficiency flag
    if ( line->BeginsWith("DOEFFICIENCY") ) {
      line->ReplaceAll("DOEFFICIENCY ","");
      if ( line->Contains("ON") )
	fDoEfficiency = kTRUE;
      else
	fDoEfficiency = kFALSE;
      if ( gDebug ) cout << "     fDoEfficiency: " << fDoEfficiency << endl;
    }

    //dofake 
    if ( line->BeginsWith("DOFAKEBACKGROUND") ) {
      line->ReplaceAll("DOFAKEBACKGROUND ","");
      if ( line->Contains("ON") )
	fDoFake = kTRUE;
      else
	fDoFake = kFALSE;
      if ( gDebug ) cout << "     fDoFake: " << fDoFake << endl;
    }

    // dojpsireweight flag - if enabled jpsi pt spectra are 
    // reweighted to higher pt.
    if ( line->BeginsWith("DOJPSIREWEIGHT") ) {
      line->ReplaceAll("DOJPSIREWEIGHT ","");
      if ( line->Contains("ON") )
	fDoJpsiReweight = kTRUE;
      else
	fDoJpsiReweight = kFALSE;
      if ( gDebug ) cout << "     fDoJpsiReweight: " << fDoJpsiReweight << endl;
    }

   if ( line->BeginsWith("DOPSIPRIMEREWEIGHT") ) {
      line->ReplaceAll("DOPSIPRIMEREWEIGHT ","");
      if ( line->Contains("ON") )
	fDoPsiprimeReweight = kTRUE;
      else
	fDoPsiprimeReweight = kFALSE;
      if ( gDebug ) cout << "     fDoPsiprimeReweight: " << fDoPsiprimeReweight << endl;
    }

    // doeventlist flag
    if ( line->BeginsWith("DOEVENTLIST") ) {
      line->ReplaceAll("DOEVENTLIST ","");
      if ( line->Contains("ON") )
	fDoEventlist = kTRUE;
      else
	fDoEventlist = kFALSE;
      if ( gDebug ) cout << "     fDoEventlist: " << fDoEventlist << endl;
    }

    // WriteEventlistNtuple flag
    if ( line->BeginsWith("WRITEEVENTLISTNTUPLE") ) {
      line->ReplaceAll("WRITEEVENTLISTNTUPLE ","");
      if ( line->Contains("ON") && !fDoEventlist )
	fWriteEventlistNtuple = kTRUE;
      else
	fWriteEventlistNtuple = kFALSE;
      if ( gDebug ) cout << "     fWriteEventlistNtuple: " << fWriteEventlistNtuple << endl;
    }

    // evtake flag
    if ( line->BeginsWith("EVTAKE") ) {
      line->ReplaceAll("EVTAKE ","");
      if ( line->Contains("ON") )
	fEvtake = kTRUE;
      else
	fEvtake = kFALSE;
      if ( gDebug ) cout << "     fEvtake: " << fEvtake << endl;
    }

    // mvdtake flag
    if ( line->BeginsWith("MVDTAKE") ) {
      line->ReplaceAll("MVDTAKE ","");
      if ( line->Contains("ON") )
	fMvdtake = kTRUE;
      else
	fMvdtake = kFALSE;
      if ( gDebug ) cout << "     fMvdtake: " << fMvdtake << endl;
    }

    // minimal runnr
    if ( line->BeginsWith("MINIMALRUNNR") ) {
      line->ReplaceAll("MINIMALRUNNR ","");
      istrstream stream(line->Data());
      stream >> fMinimalRunnr;
      if ( gDebug ) cout << "     fMinimalRunnr    : " << fMinimalRunnr               << endl;
    }

    // maximal runnr
    if ( line->BeginsWith("MAXIMALRUNNR") ) {
      line->ReplaceAll("MAXIMALRUNNR ","");
      istrstream stream(line->Data());
      stream >> fMaximalRunnr;
      if ( gDebug ) cout << "     fMaximalRunnr    : " << fMaximalRunnr               << endl;
    }

    // take only first valid muon for weight determination
    if ( line->BeginsWith("WEIGHTFIRSTMUON") ) {
      line->ReplaceAll("WEIGHTFIRSTMUON ","");
      if ( line->Contains("ON") )
	fWeightFirstMuon = kTRUE;
      else
	fWeightFirstMuon = kFALSE;
      if ( gDebug ) cout << "     fWeightFirstMuon: " << fWeightFirstMuon << endl;
    }

    // mini ntuple mode, switch off lumi calculation from evtake and mvdtake list
    if ( line->BeginsWith("MININTUPLE") ) {
      line->ReplaceAll("MININTUPLE ","");
      if ( line->Contains("ON") )
	fMiniNtuples = kTRUE;
      else
	fMiniNtuples = kFALSE;
      if ( gDebug ) cout << "     fMiniNtuples: " << fMiniNtuples << endl;
    }

    // dCache flag
    if ( line->BeginsWith("DCACHE") ) {
      line->ReplaceAll("DCACHE ","");
      if ( line->Contains("ON") ){
	fdCache = kTRUE;
	this->SetDCacheFileName();
      }
      else{
	fdCache = kFALSE;
      }
      if ( gDebug ) cout << "     fdCache: " << fdCache << endl;
    }

    // if > 0, take only runs with good barrel/rear muon chamber operation, =1 take only runs with completely working chambers, =2 take also runs with partially working chambers
    if ( line->BeginsWith("MBTAKE") ) {
      line->ReplaceAll("MBTAKE ","");
      istrstream stream(line->Data());
      stream >> fMBTake;
      if ( gDebug ) cout << "     fMBTake    : " << fMBTake               << endl;
    }

    // if > 0, take only runs with good forward muon chamber operation, =1 take only runs with completely working chambers, =2 take also runs with bad trigger
    if ( line->BeginsWith("FMUTAKE") ) {
      line->ReplaceAll("FMUTAKE ","");
      istrstream stream(line->Data());
      stream >> fFMUTake;
      if ( gDebug ) cout << "     fFMUTake    : " << fFMUTake               << endl;
    }

    // exclude runs with shifted vertex
    if ( line->BeginsWith("EXCLUDESHIFTEDVERTEXRUNS") ) {
      line->ReplaceAll("EXCLUDESHIFTEDVERTEXRUNS ","");
      if ( line->Contains("ON") ){
	fExcludeShiftedVertexRuns = kTRUE;
      }
      else{
	fExcludeShiftedVertexRuns = kFALSE;
      }
      if ( gDebug ) cout << "     fExcludeShiftedVertexRuns: " << fExcludeShiftedVertexRuns << endl;
    }

    // read new ntuple format (mujet_a,_b...)
    if ( line->BeginsWith("NEWNTUPLE") ) {
      line->ReplaceAll("NEWNTUPLE ","");
      if ( line->Contains("OFF") )
	fNewNtuple = kFALSE;
      else
	fNewNtuple = kTRUE;
      if ( gDebug ) cout << "     fNewNtuple: " << fNewNtuple << endl;
    }
    
  }
  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadMachine(TString *line) {
  //
  // read cards for Machine Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadMachine() called" << endl << endl;

  if ( line->BeginsWith("MACHINE") ) {
    line->ReplaceAll("MACHINE-","");
	
    // flag for positrons
    if ( line->BeginsWith("POSITRON") ) {
      line->ReplaceAll("POSITRON ","");
      if ( line->Contains("ON") )
	fPositron = kTRUE;
      else
	fPositron = kFALSE;
      if ( gDebug ) cout << "     fPositron: " << fPositron << endl;
    }

    // lepton energy
    if ( line->BeginsWith("LEPTONENERGY") ) {
      line->ReplaceAll("LEPTONENERGY ","");
      istrstream stream(line->Data());
      stream >> fEnergyLepton;
      if ( gDebug ) cout << "     fEnergyLepton: " << fEnergyLepton << endl;
    }

    // lower proton energy
    if ( line->BeginsWith("PROTONENERGYLOW") ) {
      line->ReplaceAll("PROTONENERGYLOW ","");
      istrstream stream(line->Data());
      stream >> fLowerEnergyProton;
      if ( gDebug ) cout << "     fLowerEnergyProton: " << fLowerEnergyProton << endl;
    }

    // higher proton energy
    if ( line->BeginsWith("PROTONENERGYHIGH") ) {
      line->ReplaceAll("PROTONENERGYHIGH ","");
      istrstream stream(line->Data());
      stream >> fHigherEnergyProton;
      if ( gDebug ) cout << "     fHigherEnergyProton: " << fHigherEnergyProton << endl;
    }

    // set proton energy to default to lower energy
    SetMachineEnergyProton(fLowerEnergyProton);

  }
  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadLists(TString *line) {
  //
  // read cards for Lists Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadLists() called" << endl << endl;

  if ( line->BeginsWith("LISTS") ) {
    line->ReplaceAll("LISTS-","");
	
    // flag for processed events list
    if ( line->BeginsWith("PROCEVENTS") ) {
      line->ReplaceAll("PROCEVENTS ","");
      if ( line->Contains("ON") )
	fProcEvents = kTRUE;
      else
	fProcEvents = kFALSE;
      if ( gDebug ) cout << "     fProcEvents: " << fProcEvents << endl;
    }

    // flag for error list
    if ( line->BeginsWith("ERRORLIST") ) {
      line->ReplaceAll("ERRORLIST ","");
      if ( line->Contains("ON") )
	fErrorList = kTRUE;
      else
	fErrorList = kFALSE;
      if ( gDebug ) cout << "     fErrorList: " << fErrorList << endl;
    }

    // flag for selection list
    if ( line->BeginsWith("SELECTIONLIST") ) {
      line->ReplaceAll("SELECTIONLIST ","");
      if ( line->Contains("ON") )
	fSelectionList = kTRUE;
      else
	fSelectionList = kFALSE;
      if ( gDebug ) cout << "     fSelectionList: " << fSelectionList << endl;
    }

    // flag for output list
    if ( line->BeginsWith("OUTPUTLISTGENERAL") ) {
      line->ReplaceAll("OUTPUTLISTGENERAL ","");
      if ( line->Contains("ON") )
	fOutputList = kTRUE;
      else
	fOutputList = kFALSE;
      if ( gDebug ) cout << "     fOutputList: " << fOutputList << endl;
    }

    // flag for ggeneral output list entries
    if ( line->BeginsWith("OUTPUTLISTGGENERAL") ) {
      line->ReplaceAll("OUTPUTLISTGGENERAL ","");
      if ( line->Contains("ON") )
	fOutputListGGENERAL = kTRUE;
      else
	fOutputListGGENERAL = kFALSE;
      if ( gDebug ) cout << "     fOutputListGGENERAL: " << fOutputListGGENERAL << endl;
    }

    // flag for runs output list entries
    if ( line->BeginsWith("OUTPUTLISTRUNS") ) {
      line->ReplaceAll("OUTPUTLISTRUNS ","");
      if ( line->Contains("ON") )
	fOutputListRUNS = kTRUE;
      else
	fOutputListRUNS = kFALSE;
      if ( gDebug ) cout << "     fOutputListRUNS: " << fOutputListRUNS << endl;
    }

    // flag for muons output list entries
    if ( line->BeginsWith("OUTPUTLISTMUONS") ) {
      line->ReplaceAll("OUTPUTLISTMUONS ","");
      if ( line->Contains("ON") )
	fOutputListMUONS = kTRUE;
      else
	fOutputListMUONS = kFALSE;
      if ( gDebug ) cout << "     fOutputListMUONS: " << fOutputListMUONS << endl;
    }

    // flag for cal output list entries
    if ( line->BeginsWith("OUTPUTLISTCAL") ) {
      line->ReplaceAll("OUTPUTLISTCAL ","");
      if ( line->Contains("ON") )
	fOutputListCAL = kTRUE;
      else
	fOutputListCAL = kFALSE;
      if ( gDebug ) cout << "     fOutputListCAL: " << fOutputListCAL << endl;
    }

    // flag for bac output list entries
    if ( line->BeginsWith("OUTPUTLISTBAC") ) {
      line->ReplaceAll("OUTPUTLISTBAC ","");
      if ( line->Contains("ON") )
	fOutputListBAC = kTRUE;
      else
	fOutputListBAC = kFALSE;
      if ( gDebug ) cout << "     fOutputListBAC: " << fOutputListBAC << endl;
    }

    // flag for jets output list entries
    if ( line->BeginsWith("OUTPUTLISTJETS") ) {
      line->ReplaceAll("OUTPUTLISTJETS ","");
      if ( line->Contains("ON") )
	fOutputListJETS = kTRUE;
      else
	fOutputListJETS = kFALSE;
      if ( gDebug ) cout << "     fOutputListJETS: " << fOutputListJETS << endl;
    }

    // flag for mjmatchs output list entries
    if ( line->BeginsWith("OUTPUTLISTMJMATCHS") ) {
      line->ReplaceAll("OUTPUTLISTMJMATCHS ","");
      if ( line->Contains("ON") )
	fOutputListMJMATCHS = kTRUE;
      else
	fOutputListMJMATCHS = kFALSE;
      if ( gDebug ) cout << "     fOutputListMJMATCHS: " << fOutputListMJMATCHS << endl;
    }

    // flag for tjmatchs output list entries
    if ( line->BeginsWith("OUTPUTLISTTJMATCHS") ) {
      line->ReplaceAll("OUTPUTLISTTJMATCHS ","");
      if ( line->Contains("ON") )
	fOutputListTJMATCHS = kTRUE;
      else
	fOutputListTJMATCHS = kFALSE;
      if ( gDebug ) cout << "     fOutputListTJMATCHS: " << fOutputListTJMATCHS << endl;
    }

    // flag for sinistra output list entries
    if ( line->BeginsWith("OUTPUTLISTSINISTRA") ) {
      line->ReplaceAll("OUTPUTLISTSINISTRA ","");
      if ( line->Contains("ON") )
	fOutputListSINISTRA = kTRUE;
      else
	fOutputListSINISTRA = kFALSE;
      if ( gDebug ) cout << "     fOutputListSINISTRA: " << fOutputListSINISTRA << endl;
    }

    // flag for tracks output list entries
    if ( line->BeginsWith("OUTPUTLISTTRACKS") ) {
      line->ReplaceAll("OUTPUTLISTTRACKS ","");
      if ( line->Contains("ON") )
	fOutputListTRACKS = kTRUE;
      else
	fOutputListTRACKS = kFALSE;
      if ( gDebug ) cout << "     fOutputListTRACKS: " << fOutputListTRACKS << endl;
    }

    // flag for vertex output list entries
    if ( line->BeginsWith("OUTPUTLISTVERTEX") ) {
      line->ReplaceAll("OUTPUTLISTVERTEX ","");
      if ( line->Contains("ON") )
	fOutputListVERTEX = kTRUE;
      else
	fOutputListVERTEX = kFALSE;
      if ( gDebug ) cout << "     fOutputListVERTEX: " << fOutputListVERTEX << endl;
    }

    // flag for zufo output list entries
    if ( line->BeginsWith("OUTPUTLISTZUFO") ) {
      line->ReplaceAll("OUTPUTLISTZUFO ","");
      if ( line->Contains("ON") )
	fOutputListZUFO = kTRUE;
      else
	fOutputListZUFO = kFALSE;
      if ( gDebug ) cout << "     fOutputListZUFO: " << fOutputListZUFO << endl;
    }

    // flag for mc output list entries
    if ( line->BeginsWith("OUTPUTLISTMC") ) {
      line->ReplaceAll("OUTPUTLISTMC ","");
      if ( line->Contains("ON") )
	fOutputListMC = kTRUE;
      else
	fOutputListMC = kFALSE;
      if ( gDebug ) 
	cout << "     fOutputListMC: " << fOutputListMC << endl;
    }

    // flag for dimuons output list entries
    if ( line->BeginsWith("OUTPUTLISTDIMUONS") ) {
      line->ReplaceAll("OUTPUTLISTDIMUONS ","");
      if ( line->Contains("ON") )
	fOutputListDIMUONS = kTRUE;
      else
	fOutputListDIMUONS = kFALSE;
      if ( gDebug ) cout << "     fOutputListDIMUONS: " << fOutputListDIMUONS << endl;
    }

    // flag for mvd output list entries
    if ( line->BeginsWith("OUTPUTLISTMVD") ) {
      line->ReplaceAll("OUTPUTLISTMVD ","");
      if ( line->Contains("ON") )
	fOutputListMVD = kTRUE;
      else
	fOutputListMVD = kFALSE;
      if ( gDebug ) cout << "     fOutputListMVD: " << fOutputListMVD << endl;
    }

    // flag for write out selected events
    if ( line->BeginsWith("OUTPUTSELECTED") ) {
      line->ReplaceAll("OUTPUTSELECTED ","");
      if ( line->Contains("ON") )
	fOutputSelected = kTRUE;
      else
	fOutputSelected = kFALSE;
      if ( gDebug ) cout << "     fOutputSelected: " << fOutputSelected << endl;
    }

    // flag for write out all events
    if ( line->BeginsWith("OUTPUTALL") ) {
      line->ReplaceAll("OUTPUTALL ","");
      if ( line->Contains("ON") )
	fOutputAll = kTRUE;
      else
	fOutputAll = kFALSE;
      if ( gDebug ) cout << "     fOutputAll: " << fOutputAll << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadMass(TString *line) {
  //
  // read cards for Mass Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadMass() called" << endl << endl;

  if ( line->BeginsWith("MASS") ) {
    line->ReplaceAll("MASS-","");
	
    // muon mass
    if ( line->BeginsWith("MUON") ) {
      line->ReplaceAll("MUON ","");
      istrstream stream(line->Data());
      stream >> fMassMuon;
      if ( gDebug ) cout << "     fMassMuon: " << fMassMuon << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadGGeneral(TString *line) {
  //
  // read cards for GGeneral Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadGGeneral() called" << endl << endl;

  if ( line->BeginsWith("GGENERAL") ) {
    line->ReplaceAll("GGENERAL-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fGGeneralGeneral = kTRUE;
      else
	fGGeneralGeneral = kFALSE;
      if ( gDebug ) cout << "     fGGeneralGeneral: " << fGGeneralGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fGGeneralControl = kTRUE;
      else
	fGGeneralControl = kFALSE;
      if ( gDebug ) cout << "     fGGeneralControl: " << fGGeneralControl << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadMc(TString *line) {
  //
  // read cards for Mc Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadMc() called" << endl << endl;

  if ( line->BeginsWith("MC") ) {
    line->ReplaceAll("MC-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fMcGeneral = kTRUE;
      else
	fMcGeneral = kFALSE;
      if ( gDebug ) cout << "     fMcGeneral: " << fMcGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fMcControl = kTRUE;
      else
	fMcControl = kFALSE;
      if ( gDebug ) cout << "     fMcControl: " << fMcControl << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadTrigger(TString *line) {
  //
  // read cards for Trigger Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadTrigger() called" << endl << endl;

  if ( line->BeginsWith("TRIGGER") ) {
    line->ReplaceAll("TRIGGER-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fTriggerGeneral = kTRUE;
      else
	fTriggerGeneral = kFALSE;
      if ( gDebug ) cout << "     fTriggerGeneral: " << fTriggerGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fTriggerControl = kTRUE;
      else
	fTriggerControl = kFALSE;
      if ( gDebug ) cout << "     fTriggerControl: " << fTriggerControl << endl;
    }

    // tlt exo bits for 96p-00p
    if ( line->BeginsWith("TLTEXO96p00p") ) {
      line->ReplaceAll("TLTEXO96p00p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTEXO96p00p;
      if ( gDebug ) cout << "     fTriggerTLTEXO96p00p: " << fTriggerTLTEXO96p00p << endl;
    }
 
    // tlt exo bits for 03p-04p
    if ( line->BeginsWith("TLTEXO03p04p") ) {
      line->ReplaceAll("TLTEXO03p04p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTEXO03p04p;
      if ( gDebug ) cout << "     fTriggerTLTEXO03p04p: " << fTriggerTLTEXO03p04p << endl;
    }

    // tlt exo bits for 05e-06e
    if ( line->BeginsWith("TLTEXO05e06e") ) {
      line->ReplaceAll("TLTEXO05e06e ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTEXO05e06e;
      if ( gDebug ) cout << "     fTriggerTLTEXO05e06e: " << fTriggerTLTEXO05e06e << endl;
    }

    // tlt exo bits for 06p-07p
    if ( line->BeginsWith("TLTEXO06p07p") ) {
      line->ReplaceAll("TLTEXO06p07p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTEXO06p07p;
      if ( gDebug ) cout << "     fTriggerTLTEXO06p07p: " << fTriggerTLTEXO06p07p << endl;
    }

    // tlt hpp bits for 96p-00p
    if ( line->BeginsWith("TLTHPP96p00p") ) {
      line->ReplaceAll("TLTHPP96p00p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHPP96p00p;
      if ( gDebug ) cout << "     fTriggerTLTHPP96p00p: " << fTriggerTLTHPP96p00p << endl;
    }

    // tlt hpp bits for 03p-04p
    if ( line->BeginsWith("TLTHPP03p04p") ) {
      line->ReplaceAll("TLTHPP03p04p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHPP03p04p;
      if ( gDebug ) cout << "     fTriggerTLTHPP03p04p: " << fTriggerTLTHPP03p04p << endl;
    }

   // tlt hpp bits for 05e-06e
    if ( line->BeginsWith("TLTHPP05e06e") ) {
      line->ReplaceAll("TLTHPP05e06e ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHPP05e06e;
      if ( gDebug ) cout << "     fTriggerTLTHPP05e06e: " << fTriggerTLTHPP05e06e << endl;
    }

    // tlt hpp bits for 06p-07p
    if ( line->BeginsWith("TLTHPP06p07p") ) {
      line->ReplaceAll("TLTHPP06p07p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHPP06p07p;
      if ( gDebug ) cout << "     fTriggerTLTHPP06p07p: " << fTriggerTLTHPP06p07p << endl;
    }

    // tlt hfl bits for 96p-00p
    if ( line->BeginsWith("TLTHFL96p00p") ) {
      line->ReplaceAll("TLTHFL96p00p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHFL96p00p;
      if ( gDebug ) cout << "     fTriggerTLTHFL_96p-00p: " << fTriggerTLTHFL96p00p << endl;
    }

    // tlt hfl bits for 99p-00p
    if ( line->BeginsWith("TLTHFL99p00p") ) {
      line->ReplaceAll("TLTHFL99p00p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHFL99p00p;
      if ( gDebug ) cout << "     fTriggerTLTHFL_99p-00p: " << fTriggerTLTHFL99p00p << endl;
    }

    // tlt hfl bits for 03p-04p
    if ( line->BeginsWith("TLTHFL03p04p") ) {
      line->ReplaceAll("TLTHFL03p04p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHFL03p04p;
      if ( gDebug ) cout << "     fTriggerTLTHFL03p04p: " << fTriggerTLTHFL03p04p << endl;
    }

    // tlt hfl bits for 05e-06e
    if ( line->BeginsWith("TLTHFL05e06e") ) {
      line->ReplaceAll("TLTHFL05e06e ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHFL05e06e;
      if ( gDebug ) cout << "     fTriggerTLTHFL05e06e: " << fTriggerTLTHFL05e06e << endl;
    }

    // tlt hfl bits for 06p-07p
    if ( line->BeginsWith("TLTHFL06p07p") ) {
      line->ReplaceAll("TLTHFL06p07p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTHFL06p07p;
      if ( gDebug ) cout << "     fTriggerTLTHFL06p07p: " << fTriggerTLTHFL06p07p << endl;
    }

    // tlt dis bits for 96p-00p
    if ( line->BeginsWith("TLTDIS96p00p") ) {
      line->ReplaceAll("TLTDIS96p00p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTDIS96p00p;
      if ( gDebug ) cout << "     fTriggerTLTDIS_96p-00p: " << fTriggerTLTDIS96p00p << endl;
    }

    // tlt dis bits for 03p-04p
    if ( line->BeginsWith("TLTDIS03p04p") ) {
      line->ReplaceAll("TLTDIS03p04p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTDIS03p04p;
      if ( gDebug ) cout << "     fTriggerTLTDIS_03p-04p: " << fTriggerTLTDIS03p04p << endl;
    }

    // tlt dis bits for 05e-06e
    if ( line->BeginsWith("TLTDIS05e06e") ) {
      line->ReplaceAll("TLTDIS05e06e ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTDIS05e06e;
      if ( gDebug ) cout << "     fTriggerTLTDIS_05e-06e: " << fTriggerTLTDIS05e06e << endl;
    }

    // tlt dis bits for 06p-07p
    if ( line->BeginsWith("TLTDIS06p07p") ) {
      line->ReplaceAll("TLTDIS06p07p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTDIS06p07p;
      if ( gDebug ) cout << "     fTriggerTLTDIS_06p-07p: " << fTriggerTLTDIS06p07p << endl;
    }

    // tlt muo bits for 96p-00p
    if ( line->BeginsWith("TLTMUO96p00p") ) {
      line->ReplaceAll("TLTMUO96p00p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTMUO96p00p;
      if ( gDebug ) cout << "     fTriggerTLTMUO_96p-00p: " << fTriggerTLTMUO96p00p << endl;
    }

    // tlt muo bits for 03p-04p
    if ( line->BeginsWith("TLTMUO03p04p") ) {
      line->ReplaceAll("TLTMUO03p04p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTMUO03p04p;
      if ( gDebug ) cout << "     fTriggerTLTMUO03p04p: " << fTriggerTLTMUO03p04p << endl;
    }

    // tlt muo bits for 05e-06e
    if ( line->BeginsWith("TLTMUO05e06e") ) {
      line->ReplaceAll("TLTMUO05e06e ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTMUO05e06e;
      if ( gDebug ) cout << "     fTriggerTLTMUO05e06e: " << fTriggerTLTMUO05e06e << endl;
    }

    // tlt muo bits for 06p-07p
    if ( line->BeginsWith("TLTMUO06p07p") ) {
      line->ReplaceAll("TLTMUO06p07p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTMUO06p07p;
      if ( gDebug ) cout << "     fTriggerTLTMUO06p07p: " << fTriggerTLTMUO06p07p << endl;
    }

    // tlt SPP bits for 03p-04p
    if ( line->BeginsWith("TLTSPP03p04p") ) {
      line->ReplaceAll("TLTSPP03p04p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTSPP03p04p;
      if ( gDebug ) cout << "     fTriggerTLTSPP03p04p: " << fTriggerTLTSPP03p04p << endl;
    }

    // tlt SPP bits for 05e-06e
    if ( line->BeginsWith("TLTSPP05e06e") ) {
      line->ReplaceAll("TLTSPP05e06e ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTSPP05e06e;
      if ( gDebug ) cout << "     fTriggerTLTSPP05e06e: " << fTriggerTLTSPP05e06e << endl;
    }

    // tlt SPP bits for 06p-07p
    if ( line->BeginsWith("TLTSPP06p07p") ) {
      line->ReplaceAll("TLTSPP06p07p ","");
      istrstream stream(line->Data());
      stream >> fTriggerTLTSPP06p07p;
      if ( gDebug ) cout << "     fTriggerTLTSPP06p07p: " << fTriggerTLTSPP06p07p << endl;
    }

    // activate efficiency correction
    if ( line->BeginsWith("EFFICIENCYCORRECTION") ) {
      line->ReplaceAll("EFFICIENCYCORRECTION ","");
      if ( line->Contains("ON") )
	fTriggerEfficiencyCorrection = kTRUE;
      else
	fTriggerEfficiencyCorrection = kFALSE;
      if ( gDebug ) cout << "     fTriggerEfficiencyCorrection: " << fTriggerEfficiencyCorrection << endl;
    }

    // activate dimuon efficiency correction
    if ( line->BeginsWith("DIMUONEFFICIENCYCORRECTION") ) {
      line->ReplaceAll("DIMUONEFFICIENCYCORRECTION ","");
      if ( line->Contains("ON") )
	fTriggerDimuonEfficiencyCorrection = kTRUE;
      else
	fTriggerDimuonEfficiencyCorrection = kFALSE;
      if ( gDebug ) cout << "     fTriggerDimuonEfficiencyCorrection: " << fTriggerDimuonEfficiencyCorrection << endl;
    }

    // correction factor for flt 10,11
    if ( line->BeginsWith("FLT1011") ) {
      line->ReplaceAll("FLT1011 ","");
      istrstream stream(line->Data());
      stream >> fTriggerEffCorr1011;
      if ( gDebug ) cout << "     fTriggerEffCorr1011: " << fTriggerEffCorr1011 << endl;
    }

    // correction factor for flt 42,44,51,52,53,54 (FORWARD)
    if ( line->BeginsWith("FLT4254FORWARD") ) {
      line->ReplaceAll("FLT4254FORWARD ","");
      istrstream stream(line->Data());
      stream >> fTriggerEffCorr4254Forward;
      if ( gDebug ) cout << "     fTriggerEffCorr4254Forward: " << fTriggerEffCorr4254Forward << endl;
    }

    // correction factor for flt 42,44,51,52,53,54 (BARREL)
    if ( line->BeginsWith("FLT4254BARREL") ) {
      line->ReplaceAll("FLT4254BARREL ","");
      istrstream stream(line->Data());
      stream >> fTriggerEffCorr4254Barrel;
      if ( gDebug ) cout << "     fTriggerEffCorr4254Barrel: " << fTriggerEffCorr4254Barrel << endl;
    }

    // correction factor for flt 42,44,51,52,53,54 (REAR)
    if ( line->BeginsWith("FLT4254REAR") ) {
      line->ReplaceAll("FLT4254REAR ","");
      istrstream stream(line->Data());
      stream >> fTriggerEffCorr4254Rear;
      if ( gDebug ) cout << "     fTriggerEffCorr4254Rear: " << fTriggerEffCorr4254Rear << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadSinistra(TString *line) {
  //
  // read cards for Sinistra Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadSinistra() called" << endl << endl;

  if ( line->BeginsWith("SINISTRA") ) {
    line->ReplaceAll("SINISTRA-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fSinistraGeneral = kTRUE;
      else
	fSinistraGeneral = kFALSE;
      if ( gDebug ) cout << "     fSinistraGeneral: " << fSinistraGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fSinistraControl = kTRUE;
      else
	fSinistraControl = kFALSE;
      if ( gDebug ) cout << "     fSinistraControl: " << fSinistraControl << endl;
    }

    // probability cut for sinistra
    if ( line->BeginsWith("PROBCUT") ) {
      line->ReplaceAll("PROBCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraProbCut;
      if ( gDebug ) cout << "     fSinistraProbCut: " << fSinistraProbCut << endl;
    }

    // energy cut for sinistra
    if ( line->BeginsWith("ENERGYCUT") ) {
      line->ReplaceAll("ENERGYCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraEnergyCut;
      if ( gDebug ) cout << "     fSinistraEnergyCut: " << fSinistraEnergyCut << endl;
    }

    // DIS or PhP
    if ( line->BeginsWith("DIS") ) {
      line->ReplaceAll("DIS ","");
      if ( line->Contains("ON") )
	fSinistraDIS = kTRUE;
      else
	fSinistraDIS = kFALSE;
      if ( gDebug ) cout << "     fSinistraDIS: " << fSinistraDIS << endl;
    }
    // cut on DIS/PhP (OFF) or no sinistra cut (ON) but sinistra histos
    if ( line->BeginsWith("NOCUT") ) {
      line->ReplaceAll("NOCUT ","");
      if ( line->Contains("ON") )
	fSinistraNoCut = kTRUE;
      else
	fSinistraNoCut = kFALSE;
      if ( gDebug ) cout << "     fSinistraNoCut: " << fSinistraNoCut << endl;
    }

    // yel cut for sinistra
    if ( line->BeginsWith("YELCUT") ) {
      line->ReplaceAll("YELCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraYELCut;
      if ( gDebug ) cout << "     fSinistraYELCut: " << fSinistraYELCut << endl;
    }

    // yel HIGH cut for sinistra
    if ( line->BeginsWith("YELHIGHCUT") ) {
      line->ReplaceAll("YELHIGHCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraYELHighCut;
      if ( gDebug ) cout << "     fSinistraYELHighCut: " << fSinistraYELHighCut << endl;
    }
    // yel LOW cut for sinistra
    if ( line->BeginsWith("YELLOWCUT") ) {
      line->ReplaceAll("YELLOWCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraYELLowCut;
      if ( gDebug ) cout << "     fSinistraYELLowCut: " << fSinistraYELLowCut << endl;
    }
    // Q_jb cut for sinistra
    if ( line->BeginsWith("Q2LOWCUT") ) {
      line->ReplaceAll("Q2LOWCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraQ2LowCut;
      if ( gDebug ) cout << "     fSinistraQ2LowCut: " << fSinistraQ2LowCut << endl;
    }
    // box cut for sinistra
    if ( line->BeginsWith("BOXCUT") ) {
      line->ReplaceAll("BOXCUT ","");
      if ( line->Contains("ON") )
	fSinistraBoxCut = kTRUE;
      else
	fSinistraBoxCut = kFALSE;
      if ( gDebug ) cout << "     fSinistraBoxCut: " << fSinistraBoxCut << endl;
    }
    // box cut for sinistra
    if ( line->BeginsWith("BOXXCUT") ) {
      line->ReplaceAll("BOXXCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraBoxXCut;
      if ( gDebug ) cout << "     fSinistraBoxXCut: " << fSinistraBoxXCut << endl;
    }
    // box cut for sinistra
    if ( line->BeginsWith("BOXYCUT") ) {
      line->ReplaceAll("BOXYCUT ","");
      istrstream stream(line->Data());
      stream >> fSinistraBoxYCut;
      if ( gDebug ) cout << "     fSinistraBoxYCut: " << fSinistraBoxYCut << endl;
    }
    
  }
  
  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadCal(TString *line) {
  //
  // read cards for Cal Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadCal() called" << endl << endl;

  if ( line->BeginsWith("CAL") ) {
    line->ReplaceAll("CAL-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fCALGeneral = kTRUE;
      else
	fCALGeneral = kFALSE;
      if ( gDebug ) cout << "     fCALGeneral: " << fCALGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fCALControl = kTRUE;
      else
	fCALControl = kFALSE;
      if ( gDebug ) cout << "     fCALControl: " << fCALControl << endl;
    }

    // empz cut
    if ( line->BeginsWith("EMPZCUT") ) {
      line->ReplaceAll("EMPZCUT ","");
      istrstream stream(line->Data());
      stream >> fCALEmpzCut;
      if ( gDebug ) cout << "     fCALEmpzCut: " << fCALEmpzCut << endl;
    }

    // yjblow cut for cal
    if ( line->BeginsWith("YJBLOWCUT") ) {
      line->ReplaceAll("YJBLOWCUT ","");
      istrstream stream(line->Data());
      stream >> fCALYJBLOWCut;
      if ( gDebug ) cout << "     fCALYJBLOWCut: " << fCALYJBLOWCut << endl;
    }
	
    // yjbup cut for cal
    if ( line->BeginsWith("YJBUPCUT") ) {
      line->ReplaceAll("YJBUPCUT ","");
      istrstream stream(line->Data());
      stream >> fCALYJBUPCut;
      if ( gDebug ) cout << "     fCALYJBUPCut: " << fCALYJBUPCut << endl;
    }

    // Mode for cal_et cut: 1 = cal_et, 2 = cal_et-et10, 3 = cal_et - et10 - si_pt, nothing set: cal_et-et10
    if ( line->BeginsWith("MODEETCUT") ) {
      line->ReplaceAll("MODEETCUT ","");
      istrstream stream(line->Data());
      stream >> fCALModeETCut;
      if ( gDebug ) cout << "     fCALModeETCut: " << fCALModeETCut << endl;
    }

    // 
    if ( line->BeginsWith("ETCUT") ) {
      line->ReplaceAll("ETCUT ","");
      istrstream stream(line->Data());
      stream >> fCALETCut;
      if ( gDebug ) cout << "     fCALETCut: " << fCALETCut << endl;
    }

    // cut on cal timing
    if ( line->BeginsWith("TIMECUT") ) {
      line->ReplaceAll("TIMECUT ","");
      istrstream stream(line->Data());
      stream >> fCALTimeCut;
      if ( gDebug ) cout << "     fCALTimeCut: " << fCALTimeCut << endl;
    }

    // PtOvEt cut for cal
    if ( line->BeginsWith("PTOVETCUT") ) {
      line->ReplaceAll("PTOVETCUT ","");
      istrstream stream(line->Data());
      stream >> fCALPtOvEtCut;
      if ( gDebug ) cout << "     fCALPtOvEtCut: " << fCALPtOvEtCut << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadBac(TString *line) {
  //
  // read cards for Bac Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadBac() called" << endl << endl;

  if ( line->BeginsWith("BAC") ) {
    line->ReplaceAll("BAC-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fBACGeneral = kTRUE;
      else
	fBACGeneral = kFALSE;
      if ( gDebug ) cout << "     fBACGeneral: " << fBACGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fBACControl = kTRUE;
      else
	fBACControl = kFALSE;
      if ( gDebug ) cout << "     fBACControl: " << fBACControl << endl;
    }

    //  bac_etotLOW cut for bac
    if ( line->BeginsWith("BAC_ETOTLOWCUT") ) {
      line->ReplaceAll("BAC_ETOTLOWCUT ","");
      istrstream stream(line->Data());
      stream >> fBACbac_etotLOWCut;
      if ( gDebug ) cout << "     fBACbac_etotLOWCut: " << fBACbac_etotLOWCut << endl;
    }
	
    // bac_etotUP cut for bac
    if ( line->BeginsWith("BAC_ETOTUPCUT") ) {
      line->ReplaceAll("BAC_ETOTUPCUT ","");
      istrstream stream(line->Data());
      stream >> fBACbac_etotUPCut;
      if ( gDebug ) cout << "     fBACbac_etotUPCut: " << fBACbac_etotUPCut << endl;
    }

    // nbacmu cut 
    if ( line->BeginsWith("NBACMUCUT") ) {
      line->ReplaceAll("NBACMUCUT ","");
      istrstream stream(line->Data());
      stream >> fBACnbacmuCut;
      if ( gDebug ) cout << "     fBACnbacmuCut: " << fBACnbacmuCut << endl;
    }


  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadZufo(TString *line) {
  //
  // read cards for Zufo Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadZufo() called" << endl << endl;

  if ( line->BeginsWith("ZUFO") ) {
    line->ReplaceAll("ZUFO-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fZUFOGeneral = kTRUE;
      else
	fZUFOGeneral = kFALSE;
      if ( gDebug ) cout << "     fZUFOGeneral: " << fZUFOGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fZUFOControl = kTRUE;
      else
	fZUFOControl = kFALSE;
      if ( gDebug ) cout << "     fZUFOControl: " << fZUFOControl << endl;
    }

    // yjblow cut for zufo
    if ( line->BeginsWith("YJBLOWCUT") ) {
      line->ReplaceAll("YJBLOWCUT ","");
      istrstream stream(line->Data());
      stream >> fZUFOYJBLOWCut;
      if ( gDebug ) cout << "     fZUFOYJBLOWCut: " << fZUFOYJBLOWCut << endl;
    }
	
    // yjbup cut for zufo
    if ( line->BeginsWith("YJBUPCUT") ) {
      line->ReplaceAll("YJBUPCUT ","");
      istrstream stream(line->Data());
      stream >> fZUFOYJBUPCut;
      if ( gDebug ) cout << "     fZUFOYJBUPCut: " << fZUFOYJBUPCut << endl;
    }
    // E minus pz (EmpzUp) cut for zufo
    if ( line->BeginsWith("EMPZUPCUT") ) {
      line->ReplaceAll("EMPZUPCUT ","");
      istrstream stream(line->Data());
      stream >> fZUFOEmpzUpCut;
      if ( gDebug ) cout << "     fZUFOEmpzUpCut: " << fZUFOEmpzUpCut << endl;
    }
	
    // E minus pz (EmpzLow) cut for zufo
    if ( line->BeginsWith("EMPZLOWCUT") ) {
      line->ReplaceAll("EMPZLOWCUT ","");
      istrstream stream(line->Data());
      stream >> fZUFOEmpzLowCut;
      if ( gDebug ) cout << "     fZUFOEmpzLowCut: " << fZUFOEmpzLowCut << endl;
    }

    // Q'2 Cut for eventshape variables
    if ( line->BeginsWith("Q2PRIMELOWCUT") ) {
      line->ReplaceAll("Q2PRIMELOWCUT ","");
      istrstream stream(line->Data());
      stream >> fZUFOQ2PrimeLowCut;
      if ( gDebug ) cout << "     fZUFOQ2PrimeLowCut: " << fZUFOQ2PrimeLowCut << endl;
    }

    // cut on max of pt_had
    if ( line->BeginsWith("PTHADMAXCUT") ) {
      line->ReplaceAll("PTHADMAXCUT ","");
      istrstream stream(line->Data());
      stream >> fZUFOPtHadMaxCut;
      if ( gDebug ) cout << "     fZUFOPtHadMaxCut: " << fZUFOPtHadMaxCut << endl;
    }
  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadJet(TString *line) {
  //
  // read cards for Jet Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadJet() called" << endl << endl;

  if ( line->BeginsWith("JET") ) {
    line->ReplaceAll("JET-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fJETGeneral = kTRUE;
      else
	fJETGeneral = kFALSE;
      if ( gDebug ) cout << "     fJETGeneral: " << fJETGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fJETControl = kTRUE;
      else
	fJETControl = kFALSE;
      if ( gDebug ) cout << "     fJETControl: " << fJETControl << endl;
    }

    // Jetfinder to connect (php->jet_a, dis in labframe->jet_b, dis in breitframe->jet_c +jet_d)
    if ( line->BeginsWith("BREIT") ) {
      line->ReplaceAll("BREIT ","");
      if ( line->Contains("ON") )
	fJETBreit = kTRUE;
      else
	fJETBreit = kFALSE;
      if ( gDebug ) cout << "     fJETBreit: " << fJETBreit << endl;
    }


    // cut on number of jets
    if ( line->BeginsWith("NCUT") ) {
      line->ReplaceAll("NCUT ","");
      istrstream stream(line->Data());
      stream >> fJETNCut;
      if ( gDebug ) cout << "     fJETNCut: " << fJETNCut << endl;
    }

    // cut on pt of highest jet
    if ( line->BeginsWith("PTACUT") ) {
      line->ReplaceAll("PTACUT ","");
      istrstream stream(line->Data());
      stream >> fJETPtACut;
      if ( gDebug ) cout << "     fJETPtACut: " << fJETPtACut << endl;
    }

    // cut on pt of second highest jet
    if ( line->BeginsWith("PTBCUT") ) {
      line->ReplaceAll("PTBCUT ","");
      istrstream stream(line->Data());
      stream >> fJETPtBCut;
      if ( gDebug ) cout << "     fJETPtBCut: " << fJETPtBCut << endl;
    }

    // lower cut on eta for highest jet
    if ( line->BeginsWith("ETALOWCUT") ) {
      line->ReplaceAll("ETALOWCUT ","");
      istrstream stream(line->Data());
      stream >> fJETEtaLowCut;
      if ( gDebug ) cout << "     fJETEtaLowCut: " << fJETEtaLowCut << endl;
    }

    // upper cut on eta for highest jet
    if ( line->BeginsWith("ETAUPCUT") ) {
      line->ReplaceAll("ETAUPCUT ","");
      istrstream stream(line->Data());
      stream >> fJETEtaUpCut;
      if ( gDebug ) cout << "     fJETEtaUpCut: " << fJETEtaUpCut << endl;
    }

    // it true, cuts denoted as Pt cuts are changed to be Et cuts
    if ( line->BeginsWith("CUTONET") ) {
      line->ReplaceAll("CUTONET ","");
      if ( line->Contains("ON") )
	fJETCutOnEt = kTRUE;
      else
	fJETCutOnEt = kFALSE;
      if ( gDebug ) cout << "     fJETCutOnEt: " << fJETCutOnEt << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadVertex(TString *line) {
  //
  // read cards for Vertex Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadVertex() called" << endl << endl;

  if ( line->BeginsWith("VERTEX") ) {
    line->ReplaceAll("VERTEX-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fVertexGeneral = kTRUE;
      else
	fVertexGeneral = kFALSE;
      if ( gDebug ) cout << "     fVertexGeneral: " << fVertexGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fVertexControl = kTRUE;
      else
	fVertexControl = kFALSE;
      if ( gDebug ) cout << "     fVertexControl: " << fVertexControl << endl;
    }

    // x position of nominal vertex for 96-00
    if ( line->BeginsWith("NOMXOLD") ) {
      line->ReplaceAll("NOMXOLD ","");
      istrstream stream(line->Data());
      stream >> fVertexNomXOld;
      if ( gDebug ) cout << "     fVertexNomXOld: " << fVertexNomXOld << endl;
    }

    // x position of nominal vertex for 03-04
    if ( line->BeginsWith("NOMXNEW") ) {
      line->ReplaceAll("NOMXNEW ","");
      istrstream stream(line->Data());
      stream >> fVertexNomXNew;
      if ( gDebug ) cout << "     fVertexNomXNew: " << fVertexNomXNew << endl;
    }

    // y position of nominal vertex
    if ( line->BeginsWith("NOMY") ) {
      line->ReplaceAll("NOMY ","");
      istrstream stream(line->Data());
      stream >> fVertexNomY;
      if ( gDebug ) cout << "     fVertexNomY: " << fVertexNomY << endl;
    }

    // z position of nominal vertex
    if ( line->BeginsWith("NOMZ") ) {
      line->ReplaceAll("NOMZ ","");
      istrstream stream(line->Data());
      stream >> fVertexNomZ;
      if ( gDebug ) cout << "     fVertexNomZ: " << fVertexNomZ << endl;
    }

    // surrounding-cut around nominal vertex
    if ( line->BeginsWith("ZCUT") ) {
      line->ReplaceAll("ZCUT ","");
      istrstream stream(line->Data());
      stream >> fVertexZCut;
      if ( gDebug ) cout << "     fVertexZCut: " << fVertexZCut << endl;
    }

    // cut on x vertex not to be nominal vertex
    if ( line->BeginsWith("XCUT") ) {
      line->ReplaceAll("XCUT ","");
      if ( line->Contains("ON") )
	fVertexXCut = kTRUE;
      else
	fVertexXCut = kFALSE;
      if ( gDebug ) cout << "     fVertexXCut: " << fVertexXCut << endl;
    }

    // cut on y vertex not to be nominal vertex
    if ( line->BeginsWith("YCUT") ) {
      line->ReplaceAll("YCUT ","");
      if ( line->Contains("ON") )
	fVertexYCut = kTRUE;
      else
	fVertexYCut = kFALSE;
      if ( gDebug ) cout << "     fVertexYCut: " << fVertexYCut << endl;
    }

    // cut on maximal distance from nominal vertex
    if ( line->BeginsWith("XYCUT") ) {
      line->ReplaceAll("XYCUT ","");
      istrstream stream(line->Data());
      stream >> fVertexXYCut;
      if ( gDebug ) cout << "     fVertexXYCut: " << fVertexXYCut << endl;
    }

    // require valid beamspot cut
    if ( line->BeginsWith("BEAMSPOTCUT") ) {
      line->ReplaceAll("BEAMSPOTCUT ","");
      if ( line->Contains("ON") )
	fVertexBeamSpotCut = kTRUE;
      else
	fVertexBeamSpotCut = kFALSE;
      if ( gDebug ) cout << "     fVertexBeamSpotCut: " << fVertexBeamSpotCut << endl;
    }

    // x beam spot
    if ( line->BeginsWith("OLDBEAMSPOTX") ) {
      line->ReplaceAll("OLDBEAMSPOTX ","");
      istrstream stream(line->Data());
      stream >> fVertexOldBeamSpotX;
      if ( gDebug ) cout << "     fVertexOldBeamSpotX: " << fVertexOldBeamSpotX << endl;
    }

    // x beam spot
    if ( line->BeginsWith("OLDBEAMSPOTSIGMAX") ) {
      line->ReplaceAll("OLDBEAMSPOTSIGMAX ","");
      istrstream stream(line->Data());
      stream >> fVertexOldBeamSpotXSigma;
      if ( gDebug ) cout << "     fVertexOldBeamSpotXSigma: " << fVertexOldBeamSpotXSigma << endl;
    }

    // y beam spot
    if ( line->BeginsWith("OLDBEAMSPOTY") ) {
      line->ReplaceAll("OLDBEAMSPOTY ","");
      istrstream stream(line->Data());
      stream >> fVertexOldBeamSpotY;
      if ( gDebug ) cout << "     fVertexOldBeamSpotY: " << fVertexOldBeamSpotY << endl;
    }

    // y beam spot
    if ( line->BeginsWith("OLDBEAMSPOTSIGMAY") ) {
      line->ReplaceAll("OLDBEAMSPOTSIGMAY ","");
      istrstream stream(line->Data());
      stream >> fVertexOldBeamSpotYSigma;
      if ( gDebug ) cout << "     fVertexOldBeamSpotYSigma: " << fVertexOldBeamSpotYSigma << endl;
    }

    // z beam spot
    if ( line->BeginsWith("OLDBEAMSPOTZ") ) {
      line->ReplaceAll("OLDBEAMSPOTZ ","");
      istrstream stream(line->Data());
      stream >> fVertexOldBeamSpotZ;
      if ( gDebug ) cout << "     fVertexOldBeamSpotZ: " << fVertexOldBeamSpotZ << endl;
    }

    // z beam spot
    if ( line->BeginsWith("OLDBEAMSPOTSIGMAZ") ) {
      line->ReplaceAll("OLDBEAMSPOTSIGMAZ ","");
      istrstream stream(line->Data());
      stream >> fVertexOldBeamSpotZSigma;
      if ( gDebug ) cout << "     fVertexOldBeamSpotZSigma: " << fVertexOldBeamSpotZSigma << endl;
    }

    // x beam spot
    if ( line->BeginsWith("NEWBEAMSPOTX") ) {
      line->ReplaceAll("NEWBEAMSPOTX ","");
      istrstream stream(line->Data());
      stream >> fVertexNewBeamSpotX;
      if ( gDebug ) cout << "     fVertexNewBeamSpotX: " << fVertexNewBeamSpotX << endl;
    }

    // x beam spot
    if ( line->BeginsWith("NEWBEAMSPOTSIGMAX") ) {
      line->ReplaceAll("NEWBEAMSPOTSIGMAX ","");
      istrstream stream(line->Data());
      stream >> fVertexNewBeamSpotXSigma;
      if ( gDebug ) cout << "     fVertexNewBeamSpotXSigma: " << fVertexNewBeamSpotXSigma << endl;
    }

    // y beam spot
    if ( line->BeginsWith("NEWBEAMSPOTY") ) {
      line->ReplaceAll("NEWBEAMSPOTY ","");
      istrstream stream(line->Data());
      stream >> fVertexNewBeamSpotY;
      if ( gDebug ) cout << "     fVertexNewBeamSpotY: " << fVertexNewBeamSpotY << endl;
    }

    // y beam spot
    if ( line->BeginsWith("NEWBEAMSPOTSIGMAY") ) {
      line->ReplaceAll("NEWBEAMSPOTSIGMAY ","");
      istrstream stream(line->Data());
      stream >> fVertexNewBeamSpotYSigma;
      if ( gDebug ) cout << "     fVertexNewBeamSpotYSigma: " << fVertexNewBeamSpotYSigma << endl;
    }

    // z beam spot
    if ( line->BeginsWith("NEWBEAMSPOTZ") ) {
      line->ReplaceAll("NEWBEAMSPOTZ ","");
      istrstream stream(line->Data());
      stream >> fVertexNewBeamSpotZ;
      if ( gDebug ) cout << "     fVertexNewBeamSpotZ: " << fVertexNewBeamSpotZ << endl;
    }

    // z beam spot
    if ( line->BeginsWith("NEWBEAMSPOTSIGMAZ") ) {
      line->ReplaceAll("NEWBEAMSPOTSIGMAZ ","");
      istrstream stream(line->Data());
      stream >> fVertexNewBeamSpotZSigma;
      if ( gDebug ) cout << "     fVertexNewBeamSpotZSigma: " << fVertexNewBeamSpotZSigma << endl;
    }
    if ( line->BeginsWith("ALLRUNS") ) {
      line->ReplaceAll("ALLRUNS ","");
      if ( line->Contains("ON") )
	fVertexUseAllRuns = kTRUE;
      else
	fVertexUseAllRuns = kFALSE;
      if ( gDebug ) cout << "     fVertexUseAllRuns: " << fVertexUseAllRuns << endl;
    }


  }


  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadMuon(TString *line) {
  //
  // read cards for Muon Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadMuon() called" << endl << endl;

  if ( line->BeginsWith("MUON") ) {
    line->ReplaceAll("MUON-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fMUONGeneral = kTRUE;
      else
	fMUONGeneral = kFALSE;
      if ( gDebug ) cout << "     fMUONGeneral: " << fMUONGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fMUONControl = kTRUE;
      else
	fMUONControl = kFALSE;
      if ( gDebug ) cout << "     fMUONControl: " << fMUONControl << endl;
    }

    // cut on number of reconstructed muons, if 0, muon id is switched off
    if ( line->BeginsWith("NCUT") ) {
      line->ReplaceAll("NCUT ","");
      istrstream stream(line->Data());
      stream >> fMUONNCut;
      if ( gDebug ) cout << "     fMUONNCut: " << fMUONNCut << endl;
    }

    // flag for filling all histograms in general plots, not only chosen
    if ( line->BeginsWith("FILLALL") ) {
      line->ReplaceAll("FILLALL ","");
      if ( line->Contains("ON") )
	fMUONFillAll = kTRUE;
      else
	fMUONFillAll = kFALSE;
      if ( gDebug ) cout << "     fMUONFillAll: " << fMUONFillAll << endl;
    }

    // minimal bremat matching probability
    if ( line->BeginsWith("BREMPROB") ) {
      line->ReplaceAll("BREMPROB ","");
      istrstream stream(line->Data());
      stream >> fMUONBremProb;
      if ( gDebug ) cout << "     fMUONBremProb: " << fMUONBremProb << endl;
    }

    // minimal bremat chamber flag requirement
    if ( line->BeginsWith("BREMCHAMBERFLAG") ) {
      line->ReplaceAll("BREMCHAMBERFLAG ","");
      istrstream stream(line->Data());
      stream >> fMUONBremChamberFlag;
      if ( gDebug ) cout << "     fMUONBremChamberFlag: " << fMUONBremChamberFlag << endl;
    }

    // minimal MPMATCH matching probability
    if ( line->BeginsWith("MPMPROB") ) {
      line->ReplaceAll("MPMPROB ","");
      istrstream stream(line->Data());
      stream >> fMUONMPMProb;
      if ( gDebug ) cout << "     fMUONMPMProb: " << fMUONMPMProb << endl;
    }

    // maximal MUBAC bac flag
    if ( line->BeginsWith("MUBACBACFLAG") ) {
      line->ReplaceAll("MUBACBACFLAG ","");
      istrstream stream(line->Data());
      stream >> fMUONMUBACBacFlag;
      if ( gDebug ) cout << "     fMUONMUBACBacFlag: " << fMUONMUBACBacFlag << endl;
    }

    // identify muon as forward track muon if muchfl gt cut
    if ( line->BeginsWith("CHAMBERFLAGCUT") ) {
      line->ReplaceAll("CHAMBERFLAGCUT ","");
      istrstream stream(line->Data());
      stream >> fMUONChamberFlagCut;
      if ( gDebug ) cout << "     fMUONChamberFlagCut: " << fMUONChamberFlagCut << endl;
    }

    // minimal kalman filter matching probability
    if ( line->BeginsWith("MFPRO") ) {
      line->ReplaceAll("MFPRO ","");
      istrstream stream(line->Data());
      stream >> fMUONMfpro;
      if ( gDebug ) cout << "     fMUONMfpro: " << fMUONMfpro << endl;
    }

    // minimal kalman filter degrees of freedom
    if ( line->BeginsWith("MFNDF") ) {
      line->ReplaceAll("MFNDF ","");
      istrstream stream(line->Data());
      stream >> fMUONMfndf;
      if ( gDebug ) cout << "     fMUONMfndf: " << fMUONMfndf << endl;
    }

    // minimal kalman filter degrees of freedom
    if ( line->BeginsWith("MFZ") ) {
      line->ReplaceAll("MFZ ","");
      istrstream stream(line->Data());
      stream >> fMUONMfz;
      if ( gDebug ) cout << "     fMUONMfz: " << fMUONMfz << endl;
    }
    // quality requirement for forward muons only found by mubac (chamber_flag = 0) (greater_equal)
    if ( line->BeginsWith("BACFQUALITY") ) {
      line->ReplaceAll("BACFQUALITY ","");
      istrstream stream(line->Data());
      stream >> fMUONBACFQuality;
      if ( gDebug ) cout << "     fMUONBACFQuality: " << fMUONBACFQuality << endl;
    }

    // minimal muon vcid
    if ( line->BeginsWith("VCIDLOW") ) {
      line->ReplaceAll("VCIDLOW ","");
      istrstream stream(line->Data());
      stream >>  fMUONVcidLowCut;
      if ( gDebug ) cout << "      fMUONVcidLowCut " <<  fMUONVcidLowCut << endl;
    }

  // minimal muon vcid
    if ( line->BeginsWith("VCIDUP") ) {
      line->ReplaceAll("VCIDUP ","");
      istrstream stream(line->Data());
      stream >>  fMUONVcidUpCut;
      if ( gDebug ) cout << "      fMUONVcidUpCut: " <<  fMUONVcidUpCut << endl;
    }

    // activate quality modification routine
    if ( line->BeginsWith("MODIFYQUALITY") ) {
      line->ReplaceAll("MODIFYQUALITY ","");
      if ( line->Contains("ON") )
	fMUONModifyQuality = kTRUE;
      else
	fMUONModifyQuality = kFALSE;
      if ( gDebug ) cout << "     fMUONModifyQuality: " << fMUONModifyQuality << endl;
    }

    // activate GMUON SP1 (muqual recalculation) within quality modification routine
    if ( line->BeginsWith("MUQUALSERVICEPACK1") ) {
      line->ReplaceAll("MUQUALSERVICEPACK1 ","");
      if ( line->Contains("ON") )
	fMuqualServicePack1 = kTRUE;
      else
	fMuqualServicePack1 = kFALSE;
      if ( gDebug ) cout << "     fMuqualServicePack1: " << fMuqualServicePack1 << endl;
    }

    // activate muon efficiency correction, if false, take correction factors given in muon regions
    if ( line->BeginsWith("EFFICIENCYCORRECTION") ) {
      line->ReplaceAll("EFFICIENCYCORRECTION ","");
      if ( line->Contains("ON") )
	fMUONEfficiencyCorrection = kTRUE;
      else
	fMUONEfficiencyCorrection = kFALSE;
      if ( gDebug ) cout << "     fMUONEfficiencyCorrection: " << fMUONEfficiencyCorrection << endl;
    }

    // activate muqual based efficiency correction (works only if Achim's GMUON SP1 is active)
    if ( line->BeginsWith("MUQUALBASEDEFFCORR") ) {
      line->ReplaceAll("MUQUALBASEDEFFCORR ","");
      if ( line->Contains("ON") )
	fMuqualBasedEffCorr = kTRUE;
      else
	fMuqualBasedEffCorr = kFALSE;
      if ( gDebug ) cout << "     fMuqualBasedEffCorr: " << fMuqualBasedEffCorr << endl;
    }

    // activate efficiency base file reading
    if ( line->BeginsWith("READEFFICIENCYFILES") ) {
      line->ReplaceAll("READEFFICIENCYFILES ","");
      if ( line->Contains("ON") )
	fMUONReadEfficiencyFiles = kTRUE;
      else
	fMUONReadEfficiencyFiles = kFALSE;
      if ( gDebug ) cout << "     fMUONReadEfficiencyFiles: " << fMUONReadEfficiencyFiles << endl;
    }

    // file with efficiency histograms in $GUTCODEDIR/analysis/fake
    if ( line->BeginsWith("FAKEPROBABILITYFILE") ) {
      line->ReplaceAll("FAKEPROBABILITYFILE ","");
      fFakeProbabilityFile = *line;
      if (gDebug )  cout << "     fFakeProbabilityFile: " <<  fFakeProbabilityFile << endl;
    }


    // file with efficiency histograms in $GUTCODEDIR/analysis/efficiencies
    if ( line->BeginsWith("EFFICIENCYFILE") ) {
      line->ReplaceAll("EFFICIENCYFILE ","");
      fMUONEfficiencyFile = *line;
      if ( gDebug ) cout << "     fMUONEfficiencyFile: " << fMUONEfficiencyFile << endl;
    }

    // produce plots with fake muon probabilities
    if ( line->BeginsWith("PRODUCEFAKEMUONBACKGROUND") ) {
      line->ReplaceAll("PRODUCEFAKEMUONBACKGROUND ","");
      if ( line->Contains("ON") )
	fProduceFakeProbability = kTRUE;
      else
	fProduceFakeProbability = kFALSE;
      if ( gDebug ) cout << "     fProduceFakeProbability " << fProduceFakeProbability << endl;
    }

    // number of pt bins for the MPMATCH efficiencies for data and mc
    if ( line->BeginsWith("EFFICIENCYMPMATCHPTNBINS") ) {
      line->ReplaceAll("EFFICIENCYMPMATCHPTNBINS ","");
      istrstream stream(line->Data());
      stream >> fMUONEfficiencyMPMATCHPtNBins;
      if ( gDebug ) cout << "     fMUONEfficiencyMPMATCHPtNBins: " << fMUONEfficiencyMPMATCHPtNBins << endl;
    }

    if ( fMUONEfficiencyMPMATCHPtNBins != -99 ) {

      // pt bins for MPMATCH efficiencies [PtNBins]
      if ( line->BeginsWith("EFFICIENCYMPMATCHPTBINS") ) {
	if (  fMUONEfficiencyMPMATCHPtNBins != 0 ) {
	  line->ReplaceAll("EFFICIENCYMPMATCHPTBINS ","");
	  istrstream stream(line->Data());
	  fMUONEfficiencyMPMATCHPtBins =  new Double_t[fMUONEfficiencyMPMATCHPtNBins+1];
	  for ( Int_t i = 0; i <= fMUONEfficiencyMPMATCHPtNBins; ++i ) {
	    stream >> fMUONEfficiencyMPMATCHPtBins[i];
	    if ( gDebug ) cout << "     fMUONEfficiencyMPMATCHPtBins[" << i << "]: " << fMUONEfficiencyMPMATCHPtBins[i] << endl;
	  }
	} else {
	  cout << "GCards::ReadMuon Please define EFFICIENCYMPMATCHPTNBINS before defining EFFICIENCYMPMATCHPTBINS!" << endl;
	  cout << "GCards::ReadMuon Muon efficiencies set neutral" << endl;
	  fMUONEfficiencyMPMATCHPtNBins = 0;
	}
      }

    }

    // number of pt bins for the BREMAT efficiencies for data and mc
    if ( line->BeginsWith("EFFICIENCYBREMATPTNBINS") ) {
      line->ReplaceAll("EFFICIENCYBREMATPTNBINS ","");
      istrstream stream(line->Data());
      stream >> fMUONEfficiencyBREMATPtNBins;
      if ( gDebug ) cout << "     fMUONEfficiencyBREMATPtNBins: " << fMUONEfficiencyBREMATPtNBins << endl;
    }

    if ( fMUONEfficiencyBREMATPtNBins != -99 ) {

      // pt bins for BREMAT efficiencies [PtNBins]
      if ( line->BeginsWith("EFFICIENCYBREMATPTBINS") ) {
	if (  fMUONEfficiencyBREMATPtNBins != 0 ) {
	  line->ReplaceAll("EFFICIENCYBREMATPTBINS ","");
	  istrstream stream(line->Data());
	  fMUONEfficiencyBREMATPtBins =  new Double_t[fMUONEfficiencyBREMATPtNBins+1];
	  for ( Int_t i = 0; i <= fMUONEfficiencyBREMATPtNBins; ++i ) {
	    stream >> fMUONEfficiencyBREMATPtBins[i];
	    if ( gDebug ) cout << "     fMUONEfficiencyBREMATPtBins[" << i << "]: " << fMUONEfficiencyBREMATPtBins[i] << endl;
	  }
	} else {
	  cout << "GCards::ReadMuon Please define EFFICIENCYBREMATPTNBINS before defining EFFICIENCYBREMATPTBINS!" << endl;
	  cout << "GCards::ReadMuon Muon efficiencies set neutral" << endl;
	  fMUONEfficiencyBREMATPtNBins = 0;
	}
      }

    }

    // number of pt bins for the MUBAC efficiencies for data and mc
    if ( line->BeginsWith("EFFICIENCYMUBACPTNBINS") ) {
      line->ReplaceAll("EFFICIENCYMUBACPTNBINS ","");
      istrstream stream(line->Data());
      stream >> fMUONEfficiencyMUBACPtNBins;
      if ( gDebug ) cout << "     fMUONEfficiencyMUBACPtNBins: " << fMUONEfficiencyMUBACPtNBins << endl;
    }

    if ( fMUONEfficiencyMUBACPtNBins != -99 ) {

      // pt bins for MUBAC efficiencies [PtNBins]
      if ( line->BeginsWith("EFFICIENCYMUBACPTBINS") ) {
	if (  fMUONEfficiencyMUBACPtNBins != 0 ) {
	  line->ReplaceAll("EFFICIENCYMUBACPTBINS ","");
	  istrstream stream(line->Data());
	  fMUONEfficiencyMUBACPtBins =  new Double_t[fMUONEfficiencyMUBACPtNBins+1];
	  for ( Int_t i = 0; i <= fMUONEfficiencyMUBACPtNBins; ++i ) {
	    stream >> fMUONEfficiencyMUBACPtBins[i];
	    if ( gDebug ) cout << "     fMUONEfficiencyMUBACPtBins[" << i << "]: " << fMUONEfficiencyMUBACPtBins[i] << endl;
	  }
	} else {
	  cout << "GCards::ReadMuon Please define EFFICIENCYMUBACPTNBINS before defining EFFICIENCYMUBACPTBINS!" << endl;
	  cout << "GCards::ReadMuon Muon efficiencies set neutral" << endl;
	  fMUONEfficiencyMUBACPtNBins = 0;
	}
      }

    }

    // file with efficiency histograms in $GUTCODEDIR/analysis/efficiencies
    if ( line->BeginsWith("TIGHTEFFICIENCYFILE") ) {
      line->ReplaceAll("TIGHTEFFICIENCYFILE ","");
      fMUONTIGHTEfficiencyFile = *line;
      if ( gDebug ) cout << "     fMUONTIGHTEfficiencyFile: " << fMUONTIGHTEfficiencyFile << endl;
    }

    // number of pt bins for the MPMATCH efficiencies for data and mc
    if ( line->BeginsWith("TIGHTEFFICIENCYMPMATCHPTNBINS") ) {
      line->ReplaceAll("TIGHTEFFICIENCYMPMATCHPTNBINS ","");
      istrstream stream(line->Data());
      stream >> fMUONTIGHTEfficiencyMPMATCHPtNBins;
      if ( gDebug ) cout << "     fMUONTIGHTEfficiencyMPMATCHPtNBins: " << fMUONTIGHTEfficiencyMPMATCHPtNBins << endl;
    }

    if ( fMUONTIGHTEfficiencyMPMATCHPtNBins != -99 ) {

      // pt bins for MPMATCH efficiencies [PtNBins]
      if ( line->BeginsWith("TIGHTEFFICIENCYMPMATCHPTBINS") ) {
	if (  fMUONTIGHTEfficiencyMPMATCHPtNBins != 0 ) {
	  line->ReplaceAll("TIGHTEFFICIENCYMPMATCHPTBINS ","");
	  istrstream stream(line->Data());
	  fMUONTIGHTEfficiencyMPMATCHPtBins =  new Double_t[fMUONTIGHTEfficiencyMPMATCHPtNBins+1];
	  for ( Int_t i = 0; i <= fMUONTIGHTEfficiencyMPMATCHPtNBins; ++i ) {
	    stream >> fMUONTIGHTEfficiencyMPMATCHPtBins[i];
	    if ( gDebug ) cout << "     fMUONTIGHTEfficiencyMPMATCHPtBins[" << i << "]: " << fMUONTIGHTEfficiencyMPMATCHPtBins[i] << endl;
	  }
	} else {
	  cout << "GCards::ReadMuon Please define TIGHTEFFICIENCYMPMATCHPTNBINS before defining TIGHTEFFICIENCYMPMATCHPTBINS!" << endl;
	  cout << "GCards::ReadMuon Muon efficiencies set neutral" << endl;
	  fMUONTIGHTEfficiencyMPMATCHPtNBins = 0;
	}
      }

    }

    // number of pt bins for the BREMAT efficiencies for data and mc
    if ( line->BeginsWith("TIGHTEFFICIENCYBREMATPTNBINS") ) {
      line->ReplaceAll("TIGHTEFFICIENCYBREMATPTNBINS ","");
      istrstream stream(line->Data());
      stream >> fMUONTIGHTEfficiencyBREMATPtNBins;
      if ( gDebug ) cout << "     fMUONTIGHTEfficiencyBREMATPtNBins: " << fMUONTIGHTEfficiencyBREMATPtNBins << endl;
    }

    if ( fMUONTIGHTEfficiencyBREMATPtNBins != -99 ) {

      // pt bins for BREMAT efficiencies [PtNBins]
      if ( line->BeginsWith("TIGHTEFFICIENCYBREMATPTBINS") ) {
	if (  fMUONTIGHTEfficiencyBREMATPtNBins != 0 ) {
	  line->ReplaceAll("TIGHTEFFICIENCYBREMATPTBINS ","");
	  istrstream stream(line->Data());
	  fMUONTIGHTEfficiencyBREMATPtBins =  new Double_t[fMUONTIGHTEfficiencyBREMATPtNBins+1];
	  for ( Int_t i = 0; i <= fMUONTIGHTEfficiencyBREMATPtNBins; ++i ) {
	    stream >> fMUONTIGHTEfficiencyBREMATPtBins[i];
	    if ( gDebug ) cout << "     fMUONTIGHTEfficiencyBREMATPtBins[" << i << "]: " << fMUONTIGHTEfficiencyBREMATPtBins[i] << endl;
	  }
	} else {
	  cout << "GCards::ReadMuon Please define TIGHTEFFICIENCYBREMATPTNBINS before defining TIGHTEFFICIENCYBREMATPTBINS!" << endl;
	  cout << "GCards::ReadMuon Muon efficiencies set neutral" << endl;
	  fMUONTIGHTEfficiencyBREMATPtNBins = 0;
	}
      }

    }

    // number of pt bins for the MUBAC efficiencies for data and mc
    if ( line->BeginsWith("TIGHTEFFICIENCYMUBACPTNBINS") ) {
      line->ReplaceAll("TIGHTEFFICIENCYMUBACPTNBINS ","");
      istrstream stream(line->Data());
      stream >> fMUONTIGHTEfficiencyMUBACPtNBins;
      if ( gDebug ) cout << "     fMUONTIGHTEfficiencyMUBACPtNBins: " << fMUONTIGHTEfficiencyMUBACPtNBins << endl;
    }

    if ( fMUONTIGHTEfficiencyMUBACPtNBins != -99 ) {

      // pt bins for MUBAC efficiencies [PtNBins]
      if ( line->BeginsWith("TIGHTEFFICIENCYMUBACPTBINS") ) {
	if (  fMUONTIGHTEfficiencyMUBACPtNBins != 0 ) {
	  line->ReplaceAll("TIGHTEFFICIENCYMUBACPTBINS ","");
	  istrstream stream(line->Data());
	  fMUONTIGHTEfficiencyMUBACPtBins =  new Double_t[fMUONTIGHTEfficiencyMUBACPtNBins+1];
	  for ( Int_t i = 0; i <= fMUONTIGHTEfficiencyMUBACPtNBins; ++i ) {
	    stream >> fMUONTIGHTEfficiencyMUBACPtBins[i];
	    if ( gDebug ) cout << "     fMUONTIGHTEfficiencyMUBACPtBins[" << i << "]: " << fMUONTIGHTEfficiencyMUBACPtBins[i] << endl;
	  }
	} else {
	  cout << "GCards::ReadMuon Please define TIGHTEFFICIENCYMUBACPTNBINS before defining TIGHTEFFICIENCYMUBACPTBINS!" << endl;
	  cout << "GCards::ReadMuon Muon efficiencies set neutral" << endl;
	  fMUONTIGHTEfficiencyMUBACPtNBins = 0;
	}
      }

    }

    // cut off for muon efficiency correction factor, if larger, factor is reset to this value
    if ( line->BeginsWith("EFFICIENCYCUTOFF") ) {
      line->ReplaceAll("EFFICIENCYCUTOFF ","");
      istrstream stream(line->Data());
      stream >> fMUONEfficiencyCutOff;
      if ( gDebug ) cout << "     fMUONEfficiencyCutOff: " << fMUONEfficiencyCutOff << endl;
    }
    

    // calculate muon isolation of muons passing all previous cuts
    if ( line->BeginsWith("CALCULATEISOLATION") ) {
      line->ReplaceAll("CALCULATEISOLATION ","");
      if ( line->Contains("ON") )
	fMUONCalculateMuonIsolation = kTRUE;
      else
	fMUONCalculateMuonIsolation = kFALSE;
      if ( gDebug ) cout << "     fMUONCalculateMuonIsolation: " << fMUONCalculateMuonIsolation << endl;
    }

    // minimum isolation for cone 1.0, if one good muon of event has a smaller isolation, veto event
    if ( line->BeginsWith("MINISOLATION10VETO") ) {
      line->ReplaceAll("MINISOLATION10VETO ","");
      istrstream stream(line->Data());
      stream >> fMUONMinIsolation10Veto;
      if ( gDebug ) cout << "     fMUONMinIsolation10Veto: " << fMUONMinIsolation10Veto << endl;
    }

    // exclude mamma in muon modification routine
    if ( line->BeginsWith("EXCLUDEMAMMA") ) {
      line->ReplaceAll("EXCLUDEMAMMA ","");
      if ( line->Contains("ON") )
	fMUONExcludeMamma = kTRUE;
      else
	fMUONExcludeMamma = kFALSE;
      if ( gDebug ) cout << "     fMUONExcludeMamma: " << fMUONExcludeMamma << endl;
    }
    // use only positive fmckin id´s from gmuonmcblock in fakeplots
    if ( line->BeginsWith("POSITIVEFMCK") ) {
      line->ReplaceAll("POSITIVEFMCK ","");
      if ( line->Contains("ON") )
	fPositiveFMCK = kTRUE;
      else
	fPositiveFMCK = kFALSE;
      if ( gDebug ) cout << "     fPositiveFMCK: " << fFMCK << endl;
    }


  }

  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GCards::ReadFMuon(TString *line) {
  //
  // read cards for Forward Muon Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadFMuon() called" << endl << endl;

  if ( line->BeginsWith("FMUON") ) {
    line->ReplaceAll("FMUON-","");
	
    // lower eta cut for forward muons
    if ( line->BeginsWith("ETALOW") ) {
      line->ReplaceAll("ETALOW ","");
      istrstream stream(line->Data());
      stream >> fFMUONEtaLow;
      if ( gDebug ) cout << "     fFMUONEtaLow: " << fFMUONEtaLow << endl;
    }

    // upper eta cut for forward muons
    if ( line->BeginsWith("ETAUP") ) {
      line->ReplaceAll("ETAUP ","");
      istrstream stream(line->Data());
      stream >> fFMUONEtaUp;
      if ( gDebug ) cout << "     fFMUONEtaUp: " << fFMUONEtaUp << endl;
    }

    // minimal transverse momentum cut for forward muons
    if ( line->BeginsWith("PT") ) {
      line->ReplaceAll("PT ","");
      istrstream stream(line->Data());
      stream >> fFMUONPt;
      if ( gDebug ) cout << "     fFMUONPt: " << fFMUONPt << endl;
    }

    // minimal momentum cut for forward muons
    if ( line->BeginsWith("P") ) {
      line->ReplaceAll("P ","");
      istrstream stream(line->Data());
      stream >> fFMUONP;
      if ( gDebug ) cout << "     fFMUONP: " << fFMUONP << endl;
    }

    // quality cut for first pair of quality-p_T cut
    if ( line->BeginsWith("QUALCUT1") ) {
      line->ReplaceAll("QUALCUT1 ","");
      istrstream stream(line->Data());
      stream >> fFMUONQualCut1;
      if ( gDebug ) cout << "     fFMUONQualCut1: " << fFMUONQualCut1 << endl;
    }

    // p_T cut for first pair of quality-p_T cut
    if ( line->BeginsWith("QUALPTCUT1") ) {
      line->ReplaceAll("QUALPTCUT1 ","");
      istrstream stream(line->Data());
      stream >> fFMUONPTCut1;
      if ( gDebug ) cout << "     fFMUONPTCut1: " << fFMUONPTCut1 << endl;
    }

    // quality cut for second pair of quality-p_T cut
    if ( line->BeginsWith("QUALCUT2") ) {
      line->ReplaceAll("QUALCUT2 ","");
      istrstream stream(line->Data());
      stream >> fFMUONQualCut2;
      if ( gDebug ) cout << "     fFMUONQualCut2: " << fFMUONQualCut2 << endl;
    }

    // p_T cut for second pair of quality-p_T cut
    if ( line->BeginsWith("QUALPTCUT2") ) {
      line->ReplaceAll("QUALPTCUT2 ","");
      istrstream stream(line->Data());
      stream >> fFMUONPTCut2;
      if ( gDebug ) cout << "     fFMUONPTCut2: " << fFMUONPTCut2 << endl;
    }

    // finder bits for "and" requirements for forward muons
    if ( line->BeginsWith("FINDER") ) {
      line->ReplaceAll("FINDER ","");
      istrstream stream(line->Data());
      stream >> fFMUONFinder;
      if ( gDebug ) cout << "     fFMUONFinder: " << fFMUONFinder << endl;
    }

    // forward muon efficieny for 03p-04p
    if ( line->BeginsWith("EFFICIENCY03p04p") ) {
      line->ReplaceAll("EFFICIENCY03p04p ","");
      istrstream stream(line->Data());
      stream >> fFMUONEfficiency03p04p;
      if ( gDebug ) cout << "     fFMUONEfficiency03p04p: " << fFMUONEfficiency03p04p << endl;
    }

    // forward muon efficieny for 05e-06e
    if ( line->BeginsWith("EFFICIENCY05e06e") ) {
      line->ReplaceAll("EFFICIENCY05e06e ","");
      istrstream stream(line->Data());
      stream >> fFMUONEfficiency05e06e;
      if ( gDebug ) cout << "     fFMUONEfficiency05e06e: " << fFMUONEfficiency05e06e << endl;
    }

    // forward muon efficieny for 06p-07p
    if ( line->BeginsWith("EFFICIENCY06p07p") ) {
      line->ReplaceAll("EFFICIENCY06p07p ","");
      istrstream stream(line->Data());
      stream >> fFMUONEfficiency06p07p;
      if ( gDebug ) cout << "     fFMUONEfficiency06p07p: " << fFMUONEfficiency06p07p << endl;
    }

    // forward muon efficieny for 99p-00p
    if ( line->BeginsWith("EFFICIENCY99p00p") ) {
      line->ReplaceAll("EFFICIENCY99p00p ","");
      istrstream stream(line->Data());
      stream >> fFMUONEfficiency99p00p;
      if ( gDebug ) cout << "     fFMUONEfficiency99p00p: " << fFMUONEfficiency99p00p << endl;
    }

    // forward muon efficieny for 98e-99e
    if ( line->BeginsWith("EFFICIENCY98e99e") ) {
      line->ReplaceAll("EFFICIENCY98e99e ","");
      istrstream stream(line->Data());
      stream >> fFMUONEfficiency98e99e;
      if ( gDebug ) cout << "     fFMUONEfficiency98e99e: " << fFMUONEfficiency98e99e << endl;
    }

    // forward muon efficieny for 96p-97p
    if ( line->BeginsWith("EFFICIENCY96p97p") ) {
      line->ReplaceAll("EFFICIENCY96p97p ","");
      istrstream stream(line->Data());
      stream >> fFMUONEfficiency96p97p;
      if ( gDebug ) cout << "     fFMUONEfficiency96p97p: " << fFMUONEfficiency96p97p << endl;
    }

    // forward muon has to be reconstructed from vertex fitted track (MuTrFl = 2 || 3)
    if ( line->BeginsWith("ONLYVERTEXFITTED") ) {
      line->ReplaceAll("ONLYVERTEXFITTED ","");
      if ( line->Contains("ON") )
	fFMUONOnlyVertexFitted = kTRUE;
      else
	fFMUONOnlyVertexFitted = kFALSE;
      if ( gDebug ) cout << "     fFMUONOnlyVertexFitted: " << fFMUONOnlyVertexFitted << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadBMuon(TString *line) {
  //
  // read cards for barrel Muon Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadBMuon() called" << endl << endl;

  if ( line->BeginsWith("BMUON") ) {
    line->ReplaceAll("BMUON-","");
	
    // lower eta cut for barrel muons
    if ( line->BeginsWith("ETALOW") ) {
      line->ReplaceAll("ETALOW ","");
      istrstream stream(line->Data());
      stream >> fBMUONEtaLow;
      if ( gDebug ) cout << "     fBMUONEtaLow: " << fBMUONEtaLow << endl;
    }

    // upper eta cut for barrel muons
    if ( line->BeginsWith("ETAUP") ) {
      line->ReplaceAll("ETAUP ","");
      istrstream stream(line->Data());
      stream >> fBMUONEtaUp;
      if ( gDebug ) cout << "     fBMUONEtaUp: " << fBMUONEtaUp << endl;
    }

    // minimal transverse momentum cut for barrel muons
    if ( line->BeginsWith("PT") ) {
      line->ReplaceAll("PT ","");
      istrstream stream(line->Data());
      stream >> fBMUONPt;
      if ( gDebug ) cout << "     fBMUONPt: " << fBMUONPt << endl;
    }

    // minimal momentum cut for barrel muons
    if ( line->BeginsWith("P") ) {
      line->ReplaceAll("P ","");
      istrstream stream(line->Data());
      stream >> fBMUONP;
      if ( gDebug ) cout << "     fBMUONP: " << fBMUONP << endl;
    }

    // quality cut for first pair of quality-p_T cut
    if ( line->BeginsWith("QUALCUT1") ) {
      line->ReplaceAll("QUALCUT1 ","");
      istrstream stream(line->Data());
      stream >> fBMUONQualCut1;
      if ( gDebug ) cout << "     fBMUONQualCut1: " << fBMUONQualCut1 << endl;
    }

    // p_T cut for first pair of quality-p_T cut
    if ( line->BeginsWith("QUALPTCUT1") ) {
      line->ReplaceAll("QUALPTCUT1 ","");
      istrstream stream(line->Data());
      stream >> fBMUONPTCut1;
      if ( gDebug ) cout << "     fBMUONPTCut1: " << fBMUONPTCut1 << endl;
    }

    // quality cut for second pair of quality-p_T cut
    if ( line->BeginsWith("QUALCUT2") ) {
      line->ReplaceAll("QUALCUT2 ","");
      istrstream stream(line->Data());
      stream >> fBMUONQualCut2;
      if ( gDebug ) cout << "     fBMUONQualCut2: " << fBMUONQualCut2 << endl;
    }

    // p_T cut for second pair of quality-p_T cut
    if ( line->BeginsWith("QUALPTCUT2") ) {
      line->ReplaceAll("QUALPTCUT2 ","");
      istrstream stream(line->Data());
      stream >> fBMUONPTCut2;
      if ( gDebug ) cout << "     fBMUONPTCut2: " << fBMUONPTCut2 << endl;
    }

    // finder bits for "and" requirements for barrel muons
    if ( line->BeginsWith("FINDER") ) {
      line->ReplaceAll("FINDER ","");
      istrstream stream(line->Data());
      stream >> fBMUONFinder;
      if ( gDebug ) cout << "     fBMUONFinder: " << fBMUONFinder << endl;
    }

    // barrel muon efficieny for 03p-04p
    if ( line->BeginsWith("EFFICIENCY03p04p") ) {
      line->ReplaceAll("EFFICIENCY03p04p ","");
      istrstream stream(line->Data());
      stream >> fBMUONEfficiency03p04p;
      if ( gDebug ) cout << "     fBMUONEfficiency03p04p: " << fBMUONEfficiency03p04p << endl;
    }

    // barrel muon efficieny for 05e-06e
    if ( line->BeginsWith("EFFICIENCY05e06e") ) {
      line->ReplaceAll("EFFICIENCY98e99e ","");
      istrstream stream(line->Data());
      stream >> fBMUONEfficiency05e06e;
      if ( gDebug ) cout << "     fBMUONEfficiency05e06e: " << fBMUONEfficiency05e06e << endl;
    }

    // barrel muon efficieny for 06p-07p
    if ( line->BeginsWith("EFFICIENCY06p07p") ) {
      line->ReplaceAll("EFFICIENCY06p07p ","");
      istrstream stream(line->Data());
      stream >> fBMUONEfficiency06p07p;
      if ( gDebug ) cout << "     fBMUONEfficiency06p07p: " << fBMUONEfficiency06p07p << endl;
    }

    // barrel muon efficieny for 99p-00p
    if ( line->BeginsWith("EFFICIENCY99p00p") ) {
      line->ReplaceAll("EFFICIENCY99p00p ","");
      istrstream stream(line->Data());
      stream >> fBMUONEfficiency99p00p;
      if ( gDebug ) cout << "     fBMUONEfficiency99p00p: " << fBMUONEfficiency99p00p << endl;
    }

    // barrel muon efficieny for 98e-99e
    if ( line->BeginsWith("EFFICIENCY98e99e") ) {
      line->ReplaceAll("EFFICIENCY98e99e ","");
      istrstream stream(line->Data());
      stream >> fBMUONEfficiency98e99e;
      if ( gDebug ) cout << "     fBMUONEfficiency98e99e: " << fBMUONEfficiency98e99e << endl;
    }

    // barrel muon efficieny for 96p-97p
    if ( line->BeginsWith("EFFICIENCY96p97p") ) {
      line->ReplaceAll("EFFICIENCY96p97p ","");
      istrstream stream(line->Data());
      stream >> fBMUONEfficiency96p97p;
      if ( gDebug ) cout << "     fBMUONEfficiency96p97p: " << fBMUONEfficiency96p97p << endl;
    }

    // barrel muon has to be reconstructed from vertex fitted track (MuTrFl = 2 || 3)
    if ( line->BeginsWith("ONLYVERTEXFITTED") ) {
      line->ReplaceAll("ONLYVERTEXFITTED ","");
      if ( line->Contains("ON") )
	fBMUONOnlyVertexFitted = kTRUE;
      else
	fBMUONOnlyVertexFitted = kFALSE;
      if ( gDebug ) cout << "     fBMUONOnlyVertexFitted: " << fBMUONOnlyVertexFitted << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadRMuon(TString *line) {
  //
  // read cards for rear Muon Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadRMuon() called" << endl << endl;

  if ( line->BeginsWith("RMUON") ) {
    line->ReplaceAll("RMUON-","");
	
    // lower eta cut for rear muons
    if ( line->BeginsWith("ETALOW") ) {
      line->ReplaceAll("ETALOW ","");
      istrstream stream(line->Data());
      stream >> fRMUONEtaLow;
      if ( gDebug ) cout << "     fRMUONEtaLow: " << fRMUONEtaLow << endl;
    }

    // upper eta cut for rear muons
    if ( line->BeginsWith("ETAUP") ) {
      line->ReplaceAll("ETAUP ","");
      istrstream stream(line->Data());
      stream >> fRMUONEtaUp;
      if ( gDebug ) cout << "     fRMUONEtaUp: " << fRMUONEtaUp << endl;
    }

    // minimal transverse momentum cut for rear muons
    if ( line->BeginsWith("PT") ) {
      line->ReplaceAll("PT ","");
      istrstream stream(line->Data());
      stream >> fRMUONPt;
      if ( gDebug ) cout << "     fRMUONPt: " << fRMUONPt << endl;
    }

    // minimal momentum cut for rear muons
    if ( line->BeginsWith("P") ) {
      line->ReplaceAll("P ","");
      istrstream stream(line->Data());
      stream >> fRMUONP;
      if ( gDebug ) cout << "     fRMUONP: " << fRMUONP << endl;
    }

    // quality cut for first pair of quality-p_T cut
    if ( line->BeginsWith("QUALCUT1") ) {
      line->ReplaceAll("QUALCUT1 ","");
      istrstream stream(line->Data());
      stream >> fRMUONQualCut1;
      if ( gDebug ) cout << "     fRMUONQualCut1: " << fRMUONQualCut1 << endl;
    }

    // p_T cut for first pair of quality-p_T cut
    if ( line->BeginsWith("QUALPTCUT1") ) {
      line->ReplaceAll("QUALPTCUT1 ","");
      istrstream stream(line->Data());
      stream >> fRMUONPTCut1;
      if ( gDebug ) cout << "     fRMUONPTCut1: " << fRMUONPTCut1 << endl;
    }

    // quality cut for second pair of quality-p_T cut
    if ( line->BeginsWith("QUALCUT2") ) {
      line->ReplaceAll("QUALCUT2 ","");
      istrstream stream(line->Data());
      stream >> fRMUONQualCut2;
      if ( gDebug ) cout << "     fRMUONQualCut2: " << fRMUONQualCut2 << endl;
    }

    // p_T cut for second pair of quality-p_T cut
    if ( line->BeginsWith("QUALPTCUT2") ) {
      line->ReplaceAll("QUALPTCUT2 ","");
      istrstream stream(line->Data());
      stream >> fRMUONPTCut2;
      if ( gDebug ) cout << "     fRMUONPTCut2: " << fRMUONPTCut2 << endl;
    }

    // finder bits for "and" requirements for rear muons
    if ( line->BeginsWith("FINDER") ) {
      line->ReplaceAll("FINDER ","");
      istrstream stream(line->Data());
      stream >> fRMUONFinder;
      if ( gDebug ) cout << "     fRMUONFinder: " << fRMUONFinder << endl;
    }

    // rear muon efficieny for 03p-04p
    if ( line->BeginsWith("EFFICIENCY03p04p") ) {
      line->ReplaceAll("EFFICIENCY03p04p ","");
      istrstream stream(line->Data());
      stream >> fRMUONEfficiency03p04p;
      if ( gDebug ) cout << "     fRMUONEfficiency03p04p: " << fRMUONEfficiency03p04p << endl;
    }

    // rear muon efficieny for 05e-06e
    if ( line->BeginsWith("EFFICIENCY05e06e") ) {
      line->ReplaceAll("EFFICIENCY05e06e ","");
      istrstream stream(line->Data());
      stream >> fRMUONEfficiency05e06e;
      if ( gDebug ) cout << "     fRMUONEfficiency05e06e: " << fRMUONEfficiency05e06e << endl;
    }

    // rear muon efficieny for 06p-07p
    if ( line->BeginsWith("EFFICIENCY06p07p") ) {
      line->ReplaceAll("EFFICIENCY06p07p ","");
      istrstream stream(line->Data());
      stream >> fRMUONEfficiency06p07p;
      if ( gDebug ) cout << "     fRMUONEfficiency06p07p: " << fRMUONEfficiency06p07p << endl;
    }

    // rear muon efficieny for 99p-00p
    if ( line->BeginsWith("EFFICIENCY99p00p") ) {
      line->ReplaceAll("EFFICIENCY99p00p ","");
      istrstream stream(line->Data());
      stream >> fRMUONEfficiency99p00p;
      if ( gDebug ) cout << "     fRMUONEfficiency99p00p: " << fRMUONEfficiency99p00p << endl;
    }

    // rear muon efficieny for 98e-99e
    if ( line->BeginsWith("EFFICIENCY98e99e") ) {
      line->ReplaceAll("EFFICIENCY98e99e ","");
      istrstream stream(line->Data());
      stream >> fRMUONEfficiency98e99e;
      if ( gDebug ) cout << "     fRMUONEfficiency98e99e: " << fRMUONEfficiency98e99e << endl;
    }

    // rear muon efficieny for 96p-97p
    if ( line->BeginsWith("EFFICIENCY96p97p") ) {
      line->ReplaceAll("EFFICIENCY96p97p ","");
      istrstream stream(line->Data());
      stream >> fRMUONEfficiency96p97p;
      if ( gDebug ) cout << "     fRMUONEfficiency96p97p: " << fRMUONEfficiency96p97p << endl;
    }

    // REAR muon has to be reconstructed from vertex fitted track (MuTrFl = 2 || 3)
    if ( line->BeginsWith("ONLYVERTEXFITTED") ) {
      line->ReplaceAll("ONLYVERTEXFITTED ","");
      if ( line->Contains("ON") )
	fRMUONOnlyVertexFitted = kTRUE;
      else
	fRMUONOnlyVertexFitted = kFALSE;
      if ( gDebug ) cout << "     fRMUONOnlyVertexFitted: " << fRMUONOnlyVertexFitted << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadTracks(TString *line) {
  //
  // read cards for Tracks Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadTracks() called" << endl << endl;

  if ( line->BeginsWith("TRACKS") ) {
    line->ReplaceAll("TRACKS-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fTRACKSGeneral = kTRUE;
      else
	fTRACKSGeneral = kFALSE;
      if ( gDebug ) cout << "     fTRACKSGeneral: " << fTRACKSGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fTRACKSControl = kTRUE;
      else
	fTRACKSControl = kFALSE;
      if ( gDebug ) cout << "     fTRACKSControl: " << fTRACKSControl << endl;
    }

    // tracks multiplicity cut
    if ( line->BeginsWith("MULTIPLICITY") ) {
      line->ReplaceAll("MULTIPLICITY ","");
      istrstream stream(line->Data());
      stream >> fTRACKSMultiplicity;
      if ( gDebug ) cout << "     fTRACKSMultiplicity: " << fTRACKSMultiplicity << " ." << endl;
    }

    // tracks cut on used superlayers
    if ( line->BeginsWith("USEDSUPERLAYERSCUT") ) {
      line->ReplaceAll("USEDSUPERLAYERSCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSUsedSuperLayersCut;
      if ( gDebug ) cout << "     fTRACKSUsedSuperLayersCut: " << fTRACKSUsedSuperLayersCut << " ." << endl;
    }

    // maximal number of vertex tracks cut
    if ( line->BeginsWith("VERTEXCUT") ) {
      line->ReplaceAll("VERTEXCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSVertexCut;
      if ( gDebug ) cout << "     fTRACKSVertexCut: " << fTRACKSVertexCut << endl;
    }

    // tracks cut on used stereo and axial hits
    if ( line->BeginsWith("USEDHITSCUT") ) {
      line->ReplaceAll("USEDHITSCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSUsedHitsCut;
      if ( gDebug ) cout << "     fTRACKSUsedHitsCut: " << fTRACKSUsedHitsCut << " ." << endl;
    }

    // tracks cut on used stereo and axial hits
    if ( line->BeginsWith("USEDSTEREOHITSCUT") ) {
      line->ReplaceAll("USEDSTEREOHITSCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSUsedStereoHitsCut;
      if ( gDebug ) cout << "     fTRACKSUsedStereoHitsCut: " << fTRACKSUsedStereoHitsCut << " ." << endl;
    }

    // minimal number of vertex tracks cut
    if ( line->BeginsWith("MINVERTEXCUT") ) {
      line->ReplaceAll("MINVERTEXCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSMinVertexCut;
      if ( gDebug ) cout << "     fTRACKSMinVertexCut: " << fTRACKSMinVertexCut << endl;
    }

    // total over vertex tracks cut
    if ( line->BeginsWith("TOTALOVVERTEXCUT") ) {
      line->ReplaceAll("TOTALOVVERTEXCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSTotalOvVertexCut;
      if ( gDebug ) cout << "     fTRACKSTotalOvVertexCut: " << fTRACKSTotalOvVertexCut << endl;
    }

    // cut of z_h
    if ( line->BeginsWith("ZHCUT") ) {
      line->ReplaceAll("ZHCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSZHCut;
      if ( gDebug ) cout << "     fTRACKSZHCut: " << fTRACKSZHCut << endl;
    }

    // tracks cut on mvd hits
    if ( line->BeginsWith("MVDHITSCUT") ) {
      line->ReplaceAll("MVDHITSCUT ","");
      istrstream stream(line->Data());
      stream >> fTRACKSMVDHitsCut;
      if ( gDebug ) cout << "     fTRACKSMVDHitsCut: " << fTRACKSMVDHitsCut << " ." << endl;
    }
    // choose tracktype to fill array
    if ( line->BeginsWith("CHOOSETYPE") ) {
      line->ReplaceAll("CHOOSETYPE ","");
      istrstream stream(line->Data());
      stream >> fTRACKSType;
           if ( gDebug ) cout << "     fTRACKSType: " << fTRACKSType << " ." << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadMJMatch(TString *line) {
  //
  // read cards for MJMatch Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadMJMatch() called" << endl << endl;

  if ( line->BeginsWith("MJMATCH") ) {
    line->ReplaceAll("MJMATCH-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fMJMATCHGeneral = kTRUE;
      else
	fMJMATCHGeneral = kFALSE;
      if ( gDebug ) cout << "     fMJMATCHGeneral: " << fMJMATCHGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fMJMATCHControl = kTRUE;
      else
	fMJMATCHControl = kFALSE;
      if ( gDebug ) cout << "     fMJMATCHControl: " << fMJMATCHControl << endl;
    }

    // match only jets with pt larger than cut
    if ( line->BeginsWith("JETPTCUT") ) {
      line->ReplaceAll("JETPTCUT ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHJetPtCut;
      if ( gDebug ) cout << "     fMJMATCHJetPtCut: " << fMJMATCHJetPtCut << endl;
    }

    // match only jet-muon pairs with pt of jet minus muon larger than cut
    if ( line->BeginsWith("MUMINUSJETPTCUT") ) {
      line->ReplaceAll("MUMINUSJETPTCUT ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHMuMinusJetPtCut;
      if ( gDebug ) cout << "     fMJMATCHMuMinusJetPtCut: " << fMJMATCHMuMinusJetPtCut << " ." << endl;
    }

    // number of matchs required at least
    if ( line->BeginsWith("NMATCHS") ) {
      line->ReplaceAll("NMATCHS ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHNMatchs;
      if ( gDebug ) cout << "     fMJMATCHNMatchs: " << fMJMATCHNMatchs << endl;
    }

    // lower cut on PtRel
    if ( line->BeginsWith("PTRELLOW") ) {
      line->ReplaceAll("PTRELLOW ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHPtRelLow;
      if ( gDebug ) cout << "     fMJMATCHPtRelLow: " << fMJMATCHPtRelLow << endl;
    }

    // higher cut on PtRel
    if ( line->BeginsWith("PTRELHIGH") ) {
      line->ReplaceAll("PTRELHIGH ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHPtRelHigh;
      if ( gDebug ) cout << "     fMJMATCHPtRelHigh: " << fMJMATCHPtRelHigh << endl;
    }

    // take all good matchs into accoun and not only the highest ptrel match
    if ( line->BeginsWith("TAKEALLGOOD") ) {
      line->ReplaceAll("TAKEALLGOOD ","");
      if ( line->Contains("ON") )
	fMJMATCHTakeAllGood = kTRUE;
      else
	fMJMATCHTakeAllGood = kFALSE;
      if ( gDebug ) cout << "     fMJMATCHTakeAllGood: " << fMJMATCHTakeAllGood << endl;
    }

    // activate ptrel correction
    if ( line->BeginsWith("PTRELCORRECTION") ) {
      line->ReplaceAll("PTRELCORRECTION ","");
      if ( line->Contains("ON") )
	fMJMATCHPtRelCorrection = kTRUE;
      else
	fMJMATCHPtRelCorrection = kFALSE;
      if ( gDebug ) cout << "     fMJMATCHPtRelCorrection: " << fMJMATCHPtRelCorrection << endl;
    }

    // filename of root file with ptrel correction histograms in $GUTCODEDIR/analysis/ptrel-correction
    if ( line->BeginsWith("PTRELCORRFILENAME") ) {
      line->ReplaceAll("PTRELCORRFILENAME ","");
      fMJMATCHPtRelCorrFilename = *line;
      if ( gDebug ) cout << "     fMJMATCHPtRelCorrFilename: " << fMJMATCHPtRelCorrFilename << endl;
    }

    // weight for ptrel corrections in C MC samples
    if ( line->BeginsWith("PTRELCORRCMCWEIGHT") ) {
      line->ReplaceAll("PTRELCORRCMCWEIGHT ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHPtRelCorrCMCWeight;
      if ( gDebug ) cout << "     fMJMATCHPtRelCorrCMCWeight: " << fMJMATCHPtRelCorrCMCWeight << endl;
    }

    // weight for ptrel corrections in LF MC samples
    if ( line->BeginsWith("PTRELCORRLFMCWEIGHT") ) {
      line->ReplaceAll("PTRELCORRLFMCWEIGHT ","");
      istrstream stream(line->Data());
      stream >> fMJMATCHPtRelCorrLFMCWeight;
      if ( gDebug ) cout << "     fMJMATCHPtRelCorrLFMCWeight: " << fMJMATCHPtRelCorrLFMCWeight << endl;
    }

  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GCards::ReadTJMatch(TString *line) {
  //
  // read cards for TJMatch Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadTJMatch() called" << endl << endl;

  if ( line->BeginsWith("TJMATCH") ) {
    line->ReplaceAll("TJMATCH-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fTJMATCHGeneral = kTRUE;
      else
	fTJMATCHGeneral = kFALSE;
      if ( gDebug ) cout << "     fTJMATCHGeneral: " << fTJMATCHGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fTJMATCHControl = kTRUE;
      else
	fTJMATCHControl = kFALSE;
      if ( gDebug ) cout << "     fTJMATCHControl: " << fTJMATCHControl << endl;
    }

    // number of matchs required at least
    if ( line->BeginsWith("NMATCHS") ) {
      line->ReplaceAll("NMATCHS ","");
      istrstream stream(line->Data());
      stream >> fTJMATCHNMatchs;
      if ( gDebug ) cout << "     fTJMATCHNMatchs: " << fTJMATCHNMatchs << endl;
    }

    // match only jets with pt larger than cut
    if ( line->BeginsWith("JETPTCUT") ) {
      line->ReplaceAll("JETPTCUT ","");
      istrstream stream(line->Data());
      stream >> fTJMATCHJetPtCut;
      if ( gDebug ) cout << "     fTJMATCHJetPtCut: " << fTJMATCHJetPtCut << endl;
    }

    // match only jet-track pairs with pt of jet minus track larger than cut
    if ( line->BeginsWith("TRACKMINUSJETPTCUT") ) {
      line->ReplaceAll("TRACKMINUSJETPTCUT ","");
      istrstream stream(line->Data());
      stream >> fTJMATCHTrackMinusJetPtCut;
      if ( gDebug ) cout << "     fTJMATCHTrackMinusJetPtCut: " << fTJMATCHTrackMinusJetPtCut << " ." << endl;
    }

    // match track and jet if they are in deltaR cone of gives size
    if ( line->BeginsWith("ASSOCIATIONCONE") ) {
      line->ReplaceAll("ASSOCIATIONCONE ","");
      istrstream stream(line->Data());
      stream >> fTJMATCHAssociationCone;
      if ( gDebug ) cout << "     fTJMATCHAssociationCone: " << fTJMATCHAssociationCone << " ." << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadMVD(TString *line) {
  //
  // read cards for MVD Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadMVD() called" << endl << endl;

  if ( line->BeginsWith("MVD") ) {
    line->ReplaceAll("MVD-","");
	
    // flag for activation of GMVD object
    if ( line->BeginsWith("ACTIVATE") ) {
      line->ReplaceAll("ACTIVATE ","");
      if ( line->Contains("ON") )
	fMVDActivate = kTRUE;
      else
	fMVDActivate = kFALSE;
      if ( gDebug ) cout << "     fMVDActivate: " << fMVDActivate << " ." << endl;
    }

    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fMVDGeneral = kTRUE;
      else
	fMVDGeneral = kFALSE;
      if ( gDebug ) cout << "     fMVDGeneral: " << fMVDGeneral << " ." << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fMVDControl = kTRUE;
      else
	fMVDControl = kFALSE;
      if ( gDebug ) cout << "     fMVDControl: " << fMVDControl << " ." << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadDIMuon(TString *line) {
  //
  // read cards for DIMuon Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadDIMuon() called" << endl << endl;

  if ( line->BeginsWith("DIMUON") ) {
    line->ReplaceAll("DIMUON-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fDIMUONGeneral = kTRUE;
      else
	fDIMUONGeneral = kFALSE;
      if ( gDebug ) cout << "     fDIMUONGeneral: " << fDIMUONGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fDIMUONControl = kTRUE;
      else
	fDIMUONControl = kFALSE;
      if ( gDebug ) cout << "     fDIMUONControl: " << fDIMUONControl << endl;
    }

    // cut on dimuon invarant mass to be larger that cut-value
    if ( line->BeginsWith("INVMASSLOW") ) {
      line->ReplaceAll("INVMASSLOW ","");
      istrstream stream(line->Data());
      stream >> fDIMUONInvMassLowCut;
      if ( gDebug ) cout << "     fDIMUONInvMassLowCut: " << fDIMUONInvMassLowCut << endl;
    }

    // cut on dimuon invarant mass to be less that cut-value
    if ( line->BeginsWith("INVMASSHIGH") ) {
      line->ReplaceAll("INVMASSHIGH ","");
      istrstream stream(line->Data());
      stream >> fDIMUONInvMassHighCut;
      if ( gDebug ) cout << "     fDIMUONInvMassHighCut: " << fDIMUONInvMassHighCut << endl;
    }


     // cut on dimuon SqSumisolation10 to be .ge. that cut-value
     if ( line->BeginsWith("SQSUMISOLATION") ) {
       line->ReplaceAll("SQSUMISOLATION ","");
       istrstream stream(line->Data());
       stream >> fDIMUONSqSumIsolationCut;
       if ( gDebug ) cout << "     fDIMUONSqSumIsolationCut: " << fDIMUONSqSumIsolationCut << endl;
     }

     // cut on dimuon SqSumisolation10 to be .ge. that cut-value, special for resonances
     if ( line->BeginsWith("SQSUMISOLATIONPEAK") ) {
       line->ReplaceAll("SQSUMISOLATIONPEAK ","");
       istrstream stream(line->Data());
       stream >> fDIMUONSqSumIsolationPeakCut;
       if ( gDebug ) cout << "     fDIMUONSqSumIsolationPeakCut: " << fDIMUONSqSumIsolationPeakCut << endl;
     }

     // cut on dimuon SqSumisolation10 to be .ge. that cut-value, special outside resonances
     if ( line->BeginsWith("SQSUMISOLATIONCONT") ) {
       line->ReplaceAll("SQSUMISOLATIONCONT ","");
       istrstream stream(line->Data());
       stream >> fDIMUONSqSumIsolationContCut;
       if ( gDebug ) cout << "     fDIMUONSqSumIsolationContCut: " << fDIMUONSqSumIsolationContCut << endl;
     }

    // cut on dimuon delta R to be larger that cut-value
    if ( line->BeginsWith("DELTAR") ) {
      line->ReplaceAll("DELTAR ","");
      istrstream stream(line->Data());
      stream >> fDIMUONDeltaRCut;
      if ( gDebug ) cout << "     fDIMUONDeltaRCut: " << fDIMUONDeltaRCut << endl;
    }

    // cut on dimuon delta phi to be larger that cut-value
    if ( line->BeginsWith("DELTAPHI") ) {
      line->ReplaceAll("DELTAPHI ","");
      istrstream stream(line->Data());
      stream >> fDIMUONDeltaPhiCut;
      if ( gDebug ) cout << "     fDIMUONDeltaPhiCut: " << fDIMUONDeltaPhiCut << endl;
    }

    // cut on dimuon delta theta to be larger that cut-value
    if ( line->BeginsWith("DELTATHETA") ) {
      line->ReplaceAll("DELTATHETA ","");
      istrstream stream(line->Data());
      stream >> fDIMUONDeltaThetaCut;
      if ( gDebug ) cout << "     fDIMUONDeltaThetaCut: " << fDIMUONDeltaThetaCut << endl;
    }

    // cut on dimuon delta eta to be larger that cut-value
    if ( line->BeginsWith("DELTAETA") ) {
      line->ReplaceAll("DELTAETA ","");
      istrstream stream(line->Data());
      stream >> fDIMUONDeltaEtaCut;
      if ( gDebug ) cout << "     fDIMUONDeltaEtaCut: " << fDIMUONDeltaEtaCut << endl;
    }

    // cut on dimuon pt asymetry to be smaller or equal that cut-value
    if ( line->BeginsWith("PTASYMETRY") ) {
      line->ReplaceAll("PTASYMETRY ","");
      istrstream stream(line->Data());
      stream >> fDIMUONPtAsymetryCut;
      if ( gDebug ) cout << "     fDIMUONPtAsymetryCut: " << fDIMUONPtAsymetryCut << endl;
    }

    // cut on dimuon et fraction to be less that cut-value (high1 = upper cut for highmass dimuons)
    if ( line->BeginsWith("ETFRACTIONHIGH1") ) {
      line->ReplaceAll("ETFRACTIONHIGH1 ","");
      istrstream stream(line->Data());
      stream >> fDIMUONEtFractionHigh1Cut;
      if ( gDebug ) cout << "     fDIMUONEtFractionHigh1Cut: " << fDIMUONEtFractionHigh1Cut << endl;
    }

    // cut on dimuon et fraction to be less that cut-value (high2 = upper cut for lowmass dimuons)
    if ( line->BeginsWith("ETFRACTIONHIGH2") ) {
      line->ReplaceAll("ETFRACTIONHIGH2 ","");
      istrstream stream(line->Data());
      stream >> fDIMUONEtFractionHigh2Cut;
      if ( gDebug ) cout << "     fDIMUONEtFractionHigh2Cut: " << fDIMUONEtFractionHigh2Cut << endl;
    }

    // cut on dimuon et fraction to be less that cut-value (low = lower cut for all dimuons)
    if ( line->BeginsWith("ETFRACTIONLOW") ) {
      line->ReplaceAll("ETFRACTIONLOW ","");
      istrstream stream(line->Data());
      stream >> fDIMUONEtFractionLowCut;
      if ( gDebug ) cout << "     fDIMUONEtFractionLowCut: " << fDIMUONEtFractionLowCut << endl;
    }

    // number of dimuons required at least
    if ( line->BeginsWith("NDIMUONS") ) {
      line->ReplaceAll("NDIMUONS ","");
      istrstream stream(line->Data());
      stream >> fDIMUONNDimuons;
      if ( gDebug ) cout << "     fDIMUONNDimuons: " << fDIMUONNDimuons << endl;
    }

    // requirement on different charge of the two muons
    if ( line->BeginsWith("DIFCHARGE") ) {
      line->ReplaceAll("DIFCHARGE ","");
      if ( line->Contains("ON") )
	fDIMUONDifCharge = kTRUE;
      else
	fDIMUONDifCharge = kFALSE;
      if ( gDebug ) cout << "     fDIMUONDifCharge: " << fDIMUONDifCharge << endl;
    }

    // requirement rejecting jpsis in Charm MC (as they are added sepereately in a more controlled fashion)
    if ( line->BeginsWith("") ) {
      line->ReplaceAll("CHARMMCJPSI ","");
      if ( line->Contains("ON") )
	fDIMUONCharmMCJpsi = kTRUE;
      else
	fDIMUONCharmMCJpsi = kFALSE;
      if ( gDebug ) cout << "     fDIMUONCharmMCJpsi: " << fDIMUONCharmMCJpsi << endl;
    }

    if ( line->BeginsWith("") ) {
      line->ReplaceAll("CHARMMCPSIPRIME ","");
      if ( line->Contains("ON") )
	fDIMUONCharmMCPsiprime = kTRUE;
      else
	fDIMUONCharmMCPsiprime = kFALSE;
      if ( gDebug ) cout << "     fDIMUONCharmMCPsiprime: " << fDIMUONCharmMCPsiprime << endl;
    }

  }

  return kTRUE;

}
  
//_____________________________________________________________

Bool_t GCards::ReadTRIMuon(TString *line) {
  //
  // read cards for TRIMuon Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadTRIMuon() called" << endl << endl;

  if ( line->BeginsWith("TRIMUON") ) {
    line->ReplaceAll("TRIMUON-","");
	
    // flag for generating general histograms
    if ( line->BeginsWith("GENERAL") ) {
      line->ReplaceAll("GENERAL ","");
      if ( line->Contains("ON") )
	fTRIMUONGeneral = kTRUE;
      else
	fTRIMUONGeneral = kFALSE;
      if ( gDebug ) cout << "     fTRIMUONGeneral: " << fTRIMUONGeneral << endl;
    }

    // flag for generating control histograms
    if ( line->BeginsWith("CONTROL") ) {
      line->ReplaceAll("CONTROL ","");
      if ( line->Contains("ON") )
	fTRIMUONControl = kTRUE;
      else
	fTRIMUONControl = kFALSE;
      if ( gDebug ) cout << "     fTRIMUONControl: " << fTRIMUONControl << endl;
    }

    // cut on dimuon invarant mass to be larger that cut-value
    if ( line->BeginsWith("INVMASSLOW") ) {
      line->ReplaceAll("INVMASSLOW ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONInvMassLowCut;
      if ( gDebug ) cout << "     fTRIMUONInvMassLowCut: " << fTRIMUONInvMassLowCut << endl;
    }

    // cut on dimuon invarant mass to be less that cut-value
    if ( line->BeginsWith("INVMASSHIGH") ) {
      line->ReplaceAll("INVMASSHIGH ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONInvMassHighCut;
      if ( gDebug ) cout << "     fTRIMUONInvMassHighCut: " << fTRIMUONInvMassHighCut << endl;
    }


     // cut on dimuon SqSumisolation10 to be .ge. that cut-value
     if ( line->BeginsWith("SQSUMISOLATION") ) {
       line->ReplaceAll("SQSUMISOLATION ","");
       istrstream stream(line->Data());
       stream >> fTRIMUONSqSumIsolationCut;
       if ( gDebug ) cout << "     fTRIMUONSqSumIsolationCut: " << fTRIMUONSqSumIsolationCut << endl;
     }

     // cut on dimuon SqSumisolation10 to be .ge. that cut-value, special for resonances
     if ( line->BeginsWith("SQSUMISOLATIONPEAK") ) {
       line->ReplaceAll("SQSUMISOLATIONPEAK ","");
       istrstream stream(line->Data());
       stream >> fTRIMUONSqSumIsolationPeakCut;
       if ( gDebug ) cout << "     fTRIMUONSqSumIsolationPeakCut: " << fTRIMUONSqSumIsolationPeakCut << endl;
     }

     // cut on dimuon SqSumisolation10 to be .ge. that cut-value, special outside resonances
     if ( line->BeginsWith("SQSUMISOLATIONCONT") ) {
       line->ReplaceAll("SQSUMISOLATIONCONT ","");
       istrstream stream(line->Data());
       stream >> fTRIMUONSqSumIsolationContCut;
       if ( gDebug ) cout << "     fTRIMUONSqSumIsolationContCut: " << fTRIMUONSqSumIsolationContCut << endl;
     }

    // cut on dimuon delta R to be larger that cut-value
    if ( line->BeginsWith("DELTAR") ) {
      line->ReplaceAll("DELTAR ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONDeltaRCut;
      if ( gDebug ) cout << "     fTRIMUONDeltaRCut: " << fTRIMUONDeltaRCut << endl;
    }

    // cut on dimuon delta phi to be larger that cut-value
    if ( line->BeginsWith("DELTAPHI") ) {
      line->ReplaceAll("DELTAPHI ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONDeltaPhiCut;
      if ( gDebug ) cout << "     fTRIMUONDeltaPhiCut: " << fTRIMUONDeltaPhiCut << endl;
    }

    // cut on dimuon delta theta to be larger that cut-value
    if ( line->BeginsWith("DELTATHETA") ) {
      line->ReplaceAll("DELTATHETA ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONDeltaThetaCut;
      if ( gDebug ) cout << "     fTRIMUONDeltaThetaCut: " << fTRIMUONDeltaThetaCut << endl;
    }

    // cut on dimuon delta eta to be larger that cut-value
    if ( line->BeginsWith("DELTAETA") ) {
      line->ReplaceAll("DELTAETA ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONDeltaEtaCut;
      if ( gDebug ) cout << "     fTRIMUONDeltaEtaCut: " << fTRIMUONDeltaEtaCut << endl;
    }

    // cut on dimuon pt asymetry to be smaller or equal that cut-value
    if ( line->BeginsWith("PTASYMETRY") ) {
      line->ReplaceAll("PTASYMETRY ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONPtAsymetryCut;
      if ( gDebug ) cout << "     fTRIMUONPtAsymetryCut: " << fTRIMUONPtAsymetryCut << endl;
    }

    // cut on dimuon et fraction to be less that cut-value (high1 = upper cut for highmass dimuons)
    if ( line->BeginsWith("ETFRACTIONHIGH1") ) {
      line->ReplaceAll("ETFRACTIONHIGH1 ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONEtFractionHigh1Cut;
      if ( gDebug ) cout << "     fTRIMUONEtFractionHigh1Cut: " << fTRIMUONEtFractionHigh1Cut << endl;
    }

    // cut on dimuon et fraction to be less that cut-value (high2 = upper cut for lowmass dimuons)
    if ( line->BeginsWith("ETFRACTIONHIGH2") ) {
      line->ReplaceAll("ETFRACTIONHIGH2 ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONEtFractionHigh2Cut;
      if ( gDebug ) cout << "     fTRIMUONEtFractionHigh2Cut: " << fTRIMUONEtFractionHigh2Cut << endl;
    }

    // cut on dimuon et fraction to be less that cut-value (low = lower cut for all dimuons)
    if ( line->BeginsWith("ETFRACTIONLOW") ) {
      line->ReplaceAll("ETFRACTIONLOW ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONEtFractionLowCut;
      if ( gDebug ) cout << "     fTRIMUONEtFractionLowCut: " << fTRIMUONEtFractionLowCut << endl;
    }

    // number of dimuons required at least
    if ( line->BeginsWith("NTRIMUONS") ) {
      line->ReplaceAll("NTRIMUONS ","");
      istrstream stream(line->Data());
      stream >> fTRIMUONNTrimuons;
      if ( gDebug ) cout << "     fTRIMUONNTrimuons: " << fTRIMUONNTrimuons << endl;
    }

    // requirement on different charge of the two muons
    if ( line->BeginsWith("DIFCHARGE") ) {
      line->ReplaceAll("DIFCHARGE ","");
      if ( line->Contains("ON") )
	fTRIMUONDifCharge = kTRUE;
      else
	fTRIMUONDifCharge = kFALSE;
      if ( gDebug ) cout << "     fTRIMUONDifCharge: " << fTRIMUONDifCharge << endl;
    }

    // requirement rejecting jpsis in Charm MC (as they are added sepereately in a more controlled fashion)
    if ( line->BeginsWith("") ) {
      line->ReplaceAll("CHARMMCJPSI ","");
      if ( line->Contains("ON") )
	fTRIMUONCharmMCJpsi = kTRUE;
      else
	fTRIMUONCharmMCJpsi = kFALSE;
      if ( gDebug ) cout << "     fTRIMUONCharmMCJpsi: " << fTRIMUONCharmMCJpsi << endl;
    }

    if ( line->BeginsWith("") ) {
      line->ReplaceAll("CHARMMCPSIPRIME ","");
      if ( line->Contains("ON") )
	fTRIMUONCharmMCPsiprime = kTRUE;
      else
	fTRIMUONCharmMCPsiprime = kFALSE;
      if ( gDebug ) cout << "     fTRIMUONCharmMCPsiprime: " << fTRIMUONCharmMCPsiprime << endl;
    }

  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GCards::ReadLogChecker(TString *line) {
  //
  // read cards for LogChecker Section
  if ( gDebug > 1 ) cout << endl << "GCards::ReadLogChecker() called" << endl << endl;

  if ( line->BeginsWith("LOGCHECKER") ) {
    line->ReplaceAll("LOGCHECKER-","");
	
    // flag for activating logchecker mode
    if ( line->BeginsWith("ACTIVATE") ) {
      line->ReplaceAll("ACTIVATE ","");
      if ( line->Contains("ON") )
	fLogActivate = kTRUE;
      else
	fLogActivate = kFALSE;
      if ( gDebug ) cout << "     fLogActivate: " << fLogActivate << endl;
    }

    // number of terms to check
    if ( line->BeginsWith("TERMNUMBER") ) {
      line->ReplaceAll("TERMNUMBER ","");
      istrstream stream(line->Data());
      stream >> fLogTermNumber;
      if ( gDebug ) cout << "     fLogTermNumber: " << fLogTermNumber << endl;
    }

    // terms to check
    if ( line->BeginsWith("TERM") ) {
      if ( fLogTermNumber > 0 ) {
	TString checkname;
	for ( Int_t i = 0; i < fLogTermNumber; i++ ) {
	  checkname = "TERM";
	  if ( i < 9 ) {
	    checkname.Append("0");
	    checkname += i+1;
	  } else {
	    checkname += i+1;
	  }
	  
	  if ( line->BeginsWith(checkname.Data()) ) {
	    checkname.Append(" ");
	    line->ReplaceAll(checkname.Data(),"");
	    fLogTerms[i] = line->Data();
	    if ( gDebug ) cout << "     fLogTerms[" << i << "]: " << fLogTerms[i].Data() << endl;
	  }
	}
      }

    }

    // number of terms to count
    if ( line->BeginsWith("COUNTNUMBER") ) {
      line->ReplaceAll("COUNTNUMBER ","");
      istrstream stream(line->Data());
      stream >> fLogCountNumber;
      if ( gDebug ) cout << "     fLogCountNumber: " << fLogCountNumber << endl;
    }

    // terms to check
    if ( line->BeginsWith("COUNT") ) {
      if ( fLogCountNumber > 0 ) {
	TString checkname;
	for ( Int_t i = 0; i < fLogCountNumber; i++ ) {
	  checkname = "COUNT";
	  if ( i < 9 ) {
	    checkname.Append("0");
	    checkname += i+1;
	  } else {
	    checkname += i+1;
	  }
	  
	  if ( line->BeginsWith(checkname.Data()) ) {
	    checkname.Append(" ");
	    line->ReplaceAll(checkname.Data(),"");
	    fLogCountTerms[i] = line->Data();
	    if ( gDebug ) cout << "     fLogCountTerms[" << i << "]: " << fLogCountTerms[i].Data() << endl;
	  }
	}
      }
    }
  }

  return kTRUE;

}
//_____________________________________________________________

Bool_t GCards::ReadPictures(TString *line) {
  //
  // read cards for PictureMaker Options
  if ( gDebug > 1 ) cout << endl << "GCards::ReadPictures() called" << endl << endl;
  
  if ( line->BeginsWith("PICTURES") ) {
    line->ReplaceAll("PICTURES-","");
    // 
    if ( line->BeginsWith("GIF") ) {
      line->ReplaceAll("GIF ","");
      if ( line->Contains("ON") )
	fPICTURES_GIF = kTRUE;
      else
	fPICTURES_GIF = kFALSE;
      if ( gDebug ) cout << "     fPICTURES_GIF: " << fPICTURES_GIF << endl;
    }
    if ( line->BeginsWith("EPS") ) {
      line->ReplaceAll("EPS ","");
      if ( line->Contains("ON") )
	fPICTURES_EPS = kTRUE;
      else
	fPICTURES_EPS = kFALSE;
      if ( gDebug ) cout << "     fPICTURES_EPS: " << fPICTURES_EPS << endl;
    }
    if ( line->BeginsWith("PS") ) {
      line->ReplaceAll("PS ","");
      if ( line->Contains("ON") )
	fPICTURES_PS = kTRUE;
      else
	fPICTURES_PS = kFALSE;
      if ( gDebug ) cout << "     fPICTURES_PS: " << fPICTURES_PS << endl;
    }
    if ( line->BeginsWith("JPG") ) {
      line->ReplaceAll("JPG ","");
      if ( line->Contains("ON") )
	fPICTURES_JPG = kTRUE;
      else
	fPICTURES_JPG = kFALSE;
      if ( gDebug ) cout << "     fPICTURES_JPG: " << fPICTURES_JPG << endl;
    }
    //
    if ( line->BeginsWith("COMP") ) {
      line->ReplaceAll("COMP-","");
      if ( line->BeginsWith("DISONLY") ) {
	line->ReplaceAll("DISONLY ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_disonly = kTRUE;
	else
	  fPICTUREScomp_disonly = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_disonly: " << fPICTUREScomp_disonly << endl;
      }
      if ( line->BeginsWith("PHPONLY") ) {
	line->ReplaceAll("PHPONLY ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_phponly = kTRUE;
	else
	  fPICTUREScomp_phponly = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_phponly: " << fPICTUREScomp_phponly << endl;
      }
      if ( line->BeginsWith("PTREL") ) {
	line->ReplaceAll("PTREL ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_ptrel = kTRUE;
	else
	  fPICTUREScomp_ptrel = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_ptrel: " << fPICTUREScomp_ptrel << endl;
      }
      if ( line->BeginsWith("MUON") ) {
	line->ReplaceAll("MUON ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_muon = kTRUE;
	else
	  fPICTUREScomp_muon = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_muon: " << fPICTUREScomp_muon << endl;
      }
      if ( line->BeginsWith("JET") ) {
	line->ReplaceAll("JET ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_jet = kTRUE;
	else
	  fPICTUREScomp_jet = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_jet: " << fPICTUREScomp_jet << endl;
      }
      if ( line->BeginsWith("MJMATCH") ) {
	line->ReplaceAll("MJMATCH ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_mjmatch = kTRUE;
	else
	  fPICTUREScomp_mjmatch = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_mjmatch: " << fPICTUREScomp_mjmatch << endl;
      }
      if ( line->BeginsWith("TJMATCH") ) {
	line->ReplaceAll("TJMATCH ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_tjmatch = kTRUE;
	else
	  fPICTUREScomp_tjmatch = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_tjmatch: " << fPICTUREScomp_tjmatch << endl;
      }
      if ( line->BeginsWith("CAL") ) {
	line->ReplaceAll("CAL ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_cal = kTRUE;
	else
	  fPICTUREScomp_cal = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_cal: " << fPICTUREScomp_cal << endl;
      }
      if ( line->BeginsWith("TRACKS") ) {
	line->ReplaceAll("TRACKS ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_tracks = kTRUE;
	else
	  fPICTUREScomp_tracks = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_tracks: " << fPICTUREScomp_tracks << endl;
      }
      if ( line->BeginsWith("TRIGGER") ) {
	line->ReplaceAll("TRIGGER ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_trigger = kTRUE;
	else
	  fPICTUREScomp_trigger = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_trigger: " << fPICTUREScomp_trigger << endl;
      }
      if ( line->BeginsWith("ZUFO") ) {
	line->ReplaceAll("ZUFO ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_zufo = kTRUE;
	else
	  fPICTUREScomp_zufo = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_zufo: " << fPICTUREScomp_zufo << endl;
      }
      if ( line->BeginsWith("SINISTRA") ) {
	line->ReplaceAll("SINISTRA ","");
	if ( line->Contains("ON") )
	  fPICTUREScomp_sinistra = kTRUE;
	else
	  fPICTUREScomp_sinistra = kFALSE;
	if ( gDebug ) cout << "     fPICTUREScomp_sinistra: " << fPICTUREScomp_sinistra << endl;
      }
    }
    if ( line->BeginsWith("ONED") ) {
      line->ReplaceAll("ONED-","");
      if ( line->BeginsWith("DIMUON") ) {
	line->ReplaceAll("DIMUON ","");
	if ( line->Contains("ON") )
	  fPICTURESONED_dimuon = kTRUE;
	else
	  fPICTURESONED_dimuon = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONED_dimuon: " << fPICTURESONED_dimuon << endl;
      }
      if ( line->BeginsWith("TRACKS") ) {
	line->ReplaceAll("TRACKS ","");
	if ( line->Contains("ON") )
	  fPICTURESONED_track = kTRUE;
	else
	  fPICTURESONED_track = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONED_track: " << fPICTURESONED_track << endl;
      }
      if ( line->BeginsWith("MUON") ) {
	line->ReplaceAll("MUON ","");
	if ( line->Contains("ON") )
	  fPICTURESONED_muon = kTRUE;
	else
	  fPICTURESONED_muon = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONED_muon: " << fPICTURESONED_muon << endl;
      }
    }
    if ( line->BeginsWith("ONEDMC") ) {
      line->ReplaceAll("ONEDMC-","");
      if ( line->BeginsWith("DIMUON") ) {
	line->ReplaceAll("DIMUON ","");
	if ( line->Contains("ON") )
	  fPICTURESONEDMC_dimuon = kTRUE;
	else
	  fPICTURESONEDMC_dimuon = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONEDMC_dimuon: " << fPICTURESONEDMC_dimuon << endl;
      }
      if ( line->BeginsWith("MC") ) {
	line->ReplaceAll("MC ","");
	if ( line->Contains("ON") )
	  fPICTURESONEDMC_mc = kTRUE;
	else
	  fPICTURESONEDMC_mc = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONEDMC_mc: " << fPICTURESONEDMC_mc << endl;
      }
      if ( line->BeginsWith("TRACK") ) {
	line->ReplaceAll("TRACK ","");
	if ( line->Contains("ON") )
	  fPICTURESONEDMC_track = kTRUE;
	else
	  fPICTURESONEDMC_track = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONEDMC_track: " << fPICTURESONEDMC_track << endl;
      }
      if ( line->BeginsWith("MUON") ) {
	line->ReplaceAll("MUON ","");
	if ( line->Contains("ON") )
	  fPICTURESONEDMC_muon = kTRUE;
	else
	  fPICTURESONEDMC_muon = kFALSE;
	if ( gDebug ) cout << "     fPICTURESONEDMC_muon: " << fPICTURESONEDMC_muon << endl;
      }
    }
    if ( line->BeginsWith("TWOD") ) {
      line->ReplaceAll("TWOD-","");
      if ( line->BeginsWith("MJMATCH") ) {
	line->ReplaceAll("MJMATCH ","");
	if ( line->Contains("ON") )
	  fPICTURESTWOD_mjmatch = kTRUE;
	else
	  fPICTURESTWOD_mjmatch = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWOD_mjmatch: " << fPICTURESTWOD_mjmatch << endl;
      }
    }
    if ( line->BeginsWith("TWOD") ) {
      line->ReplaceAll("TWOD-","");
      if ( line->BeginsWith("TJMATCH") ) {
	line->ReplaceAll("TJMATCH ","");
	if ( line->Contains("ON") )
	  fPICTURESTWOD_tjmatch = kTRUE;
	else
	  fPICTURESTWOD_tjmatch = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWOD_tjmatch: " << fPICTURESTWOD_tjmatch << endl;
      }
    }
    if ( line->BeginsWith("TWODMC") ) {
      line->ReplaceAll("TWODMC-","");
      if ( line->BeginsWith("CAL") ) {
	line->ReplaceAll("CAL ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMC_cal = kTRUE;
	else
	  fPICTURESTWODMC_cal = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMC_cal: " << fPICTURESTWODMC_cal << endl;
      }
      if ( line->BeginsWith("ZUFO") ) {
	line->ReplaceAll("ZUFO ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMC_zufo = kTRUE;
	else
	  fPICTURESTWODMC_zufo = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMC_zufo: " << fPICTURESTWODMC_zufo << endl;
      }
      if ( line->BeginsWith("MC") ) {
	line->ReplaceAll("MC ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMC_mc = kTRUE;
	else
	  fPICTURESTWODMC_mc = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMC_mc: " << fPICTURESTWODMC_mc << endl;
      }
      if ( line->BeginsWith("MUON") ) {
	line->ReplaceAll("MUON ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMC_muon = kTRUE;
	else
	  fPICTURESTWODMC_muon = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMC_muon: " << fPICTURESTWODMC_muon << endl;
      }
      if ( line->BeginsWith("MJMATCH") ) {
	line->ReplaceAll("MJMATCH ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMC_mjmatch = kTRUE;
	else
	  fPICTURESTWODMC_mjmatch = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMC_mjmatch: " << fPICTURESTWODMC_mjmatch << endl;
      }
      if ( line->BeginsWith("TJMATCH") ) {
	line->ReplaceAll("TJMATCH ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMC_tjmatch = kTRUE;
	else
	  fPICTURESTWODMC_tjmatch = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMC_tjmatch: " << fPICTURESTWODMC_tjmatch << endl;
      }
      if ( line->BeginsWith("ZOOMEDMC") ) {
	line->ReplaceAll("ZOOMEDMC ","");
	if ( line->Contains("ON") )
	  fPICTURESTWODMCzoomed_mc = kTRUE;
	else
	  fPICTURESTWODMCzoomed_mc = kFALSE;
	if ( gDebug ) cout << "     fPICTURESTWODMCzoomed_mc: " << fPICTURESTWODMCzoomed_mc << endl;
      }
    }
    if ( line->BeginsWith("EFFICIENCYFULL") ) {
      line->ReplaceAll("EFFICIENCYFULL ","");
      if ( line->Contains("ON") )
	fPICTURESEfficiencyFull = kTRUE;
      else
	fPICTURESEfficiencyFull = kFALSE;
      if ( gDebug ) cout << "     fPICTURESEfficiencyFull: " << fPICTURESEfficiencyFull << endl;
    }
    
  }
  
  return kTRUE;
  
}

//_____________________________________________________________

Bool_t GCards::SetDCacheFileName() {
  //
  // read cards for LogChecker Section
  if ( gDebug ) cout << endl << "GCards::SetDCacheFileName() called" << endl << endl;
  //  TSubString period =this->GetInputFilePath()->SubString("/data/

  if(!this->GetInputFilePath()->Contains("mc")){
    if(this->GetInputFilePath()->Contains("96p")){
      fDCacheFileName = "96pdata.txt";
    } 
    if(this->GetInputFilePath()->Contains("97p")){
      fDCacheFileName = "97pdata.txt";
    }  
    if(this->GetInputFilePath()->Contains("98e")){
      fDCacheFileName = "98edata.txt";
    } 
    if(this->GetInputFilePath()->Contains("99e")){
      fDCacheFileName = "99edata.txt";
    }
    if(this->GetInputFilePath()->Contains("99p")){
      fDCacheFileName = "99pdata.txt";
    }
    if(this->GetInputFilePath()->Contains("00p")){
      fDCacheFileName = "00pdata.txt";
    }   
    if(this->GetInputFilePath()->Contains("03p")){
      fDCacheFileName = "03pdata.txt";
    }   
    if(this->GetInputFilePath()->Contains("04p")){
      fDCacheFileName = "04pdata.txt";
    }   
    if(this->GetInputFilePath()->Contains("05e")){
      fDCacheFileName = "05edata.txt";
    } 
    if(this->GetInputFilePath()->Contains("06e")){
      fDCacheFileName = "06edata.txt";
    } 
    if(this->GetInputFilePath()->Contains("06p")){
      fDCacheFileName = "06pdata.txt";
    } 
    if(this->GetInputFilePath()->Contains("07p")){
      fDCacheFileName = "07pdata.txt";
    } 
  }

  if(this->GetInputFilePath()->Contains("mc")){
    if(this->GetInputFilePath()->Contains("b/03p-04p/dir")){
      fDCacheFileName = "0304pmcbeautydir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/03p-04p/res")){
      fDCacheFileName = "0304pmcbeautyres.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/03p-04p/exg")){
      fDCacheFileName = "0304pmcbeautyexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/03p-04p/exp")){
      fDCacheFileName = "0304pmcbeautyexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/03p-04p/dirrap")){
      fDCacheFileName = "0304pmcbeautyDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/03p-04p/resrap")){
      fDCacheFileName = "0304pmcbeautyDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir")){
      fDCacheFileName = "0304pmccharmdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir01")){
      fDCacheFileName = "0304pmccharmdir01.txt";
    }  
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir02")){
      fDCacheFileName = "0304pmccharmdir02.txt";
    }  
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir03")){
      fDCacheFileName = "0304pmccharmdir03.txt";
    }  
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir04")){
      fDCacheFileName = "0304pmccharmdir04.txt";
    }  
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir05")){
      fDCacheFileName = "0304pmccharmdir05.txt";
    }  
    if(this->GetInputFilePath()->Contains("c/03p-04p/res")){
      fDCacheFileName = "0304pmccharmres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/03p-04p/res01")){
      fDCacheFileName = "0304pmccharmres01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/03p-04p/exg")){
      fDCacheFileName = "0304pmccharmexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/exgamma01")){
      fDCacheFileName = "0304pmccharmexg01.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/exgamma02")){
      fDCacheFileName = "0304pmccharmexg02.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/exgamma03")){
      fDCacheFileName = "0304pmccharmexg03.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/exp")){
      fDCacheFileName = "0304pmccharmexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/03p-04p/exproton01")){
      fDCacheFileName = "0304pmccharmexp01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/03p-04p/dirrap")){
      fDCacheFileName = "0304pmccharmDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/resrap")){
      fDCacheFileName = "0304pmccharmDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/03p-04p/DIS")){
      fDCacheFileName = "0304pmcBHdis.txt";
    }   
    if(this->GetInputFilePath()->Contains("bh/03p-04p/elastic")){
      fDCacheFileName = "0304pmcBHela.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/03p-04p/inelastic")){
      fDCacheFileName = "0304pmcBHinela.txt";
    }   
    if(this->GetInputFilePath()->Contains("jpsi/03p-04p/jpsi1")){
      fDCacheFileName = "0304pmcjpsi.txt";
    }
    if(this->GetInputFilePath()->Contains("jpsi/03p-04p/jpsi2")){
      fDCacheFileName = "0304pmcjpsi2.txt";
    }   
    if(this->GetInputFilePath()->Contains("psiprime/03p-04p/all")){
      fDCacheFileName = "0304pmcpsiprime.txt";
    } 
    if(this->GetInputFilePath()->Contains("psiprime/03p-04p/psi2")){
      fDCacheFileName = "0304pmcpsiprime2.txt";
    }
    if(this->GetInputFilePath()->Contains("upsilon/03p-04p/1s_dir")){
      fDCacheFileName = "0304pmcupsi1s.txt";
    }   
    if(this->GetInputFilePath()->Contains("upsilon/03p-04p/2s_dir")){
      fDCacheFileName = "0304pmcupsi2s.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/03p-04p/3s_dir")){
      fDCacheFileName = "0304pmcupsi3s.txt";
    } 
    if(this->GetInputFilePath()->Contains("instanton/03p-04p/inst1")){
      fDCacheFileName = "0304pmcqcdins.txt";
    }
    if(this->GetInputFilePath()->Contains("bbbb/03p-04p/bbbb1")){
      fDCacheFileName = "0304pmcmultibeauty.txt";
    }
    if(this->GetInputFilePath()->Contains("cccc/03p-04p/cccc1")){
      fDCacheFileName = "0304pmcmulticharm.txt";
    }
    if(this->GetInputFilePath()->Contains("bbcc/03p-04p/bbcc1")){
      fDCacheFileName = "0304pmcmultibbcc.txt";
    }
    if(this->GetInputFilePath()->Contains("c/03p-04p/dir_dijet")){
      fDCacheFileName = "0304pmccharmdijetdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/res_dijet")){
      fDCacheFileName = "0304pmccharmdijetres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/03p-04p/exg_dijet")){
      fDCacheFileName = "0304pmccharmdijetexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/03p-04p/exp_dijet")){
      fDCacheFileName = "0304pmccharmdijetexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/05e-06e/dir")){
      fDCacheFileName = "0506emcbeautydir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/05e-06e/res")){
      fDCacheFileName = "0506emcbeautyres.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/05e-06e/exg")){
      fDCacheFileName = "0506emcbeautyexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/05e-06e/exp")){
      fDCacheFileName = "0506emcbeautyexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/05e-06e/dirrap")){
      fDCacheFileName = "0506emcbeautyDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/05e-06e/resrap")){
      fDCacheFileName = "0506emcbeautyDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir")){
      fDCacheFileName = "0506emccharmdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir01")){
      fDCacheFileName = "0506emccharmdir01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir02")){
      fDCacheFileName = "0506emccharmdir02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir03")){
      fDCacheFileName = "0506emccharmdir03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir04")){
      fDCacheFileName = "0506emccharmdir04.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir05")){
      fDCacheFileName = "0506emccharmdir05.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir06")){
      fDCacheFileName = "0506emccharmdir06.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir07")){
      fDCacheFileName = "0506emccharmdir07.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir08")){
      fDCacheFileName = "0506emccharmdir08.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir09")){
      fDCacheFileName = "0506emccharmdir09.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir10")){
      fDCacheFileName = "0506emccharmdir10.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir11")){
      fDCacheFileName = "0506emccharmdir11.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir12")){
      fDCacheFileName = "0506emccharmdir12.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir13")){
      fDCacheFileName = "0506emccharmdir13.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir14")){
      fDCacheFileName = "0506emccharmdir14.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir15")){
      fDCacheFileName = "0506emccharmdir15.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir16")){
      fDCacheFileName = "0506emccharmdir16.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir17")){
      fDCacheFileName = "0506emccharmdir17.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir18")){
      fDCacheFileName = "0506emccharmdir18.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir19")){
      fDCacheFileName = "0506emccharmdir19.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir20")){
      fDCacheFileName = "0506emccharmdir20.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir21")){
      fDCacheFileName = "0506emccharmdir21.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir22")){
      fDCacheFileName = "0506emccharmdir22.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir23")){
      fDCacheFileName = "0506emccharmdir23.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir24")){
      fDCacheFileName = "0506emccharmdir24.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir25")){
      fDCacheFileName = "0506emccharmdir25.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/res01")){
      fDCacheFileName = "0506emccharmres01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/res02")){
      fDCacheFileName = "0506emccharmres02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/res03")){
      fDCacheFileName = "0506emccharmres03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma01")){
      fDCacheFileName = "0506emccharmexg01.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma02")){
      fDCacheFileName = "0506emccharmexg02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma03")){
      fDCacheFileName = "0506emccharmexg03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma04")){
      fDCacheFileName = "0506emccharmexg04.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma05")){
      fDCacheFileName = "0506emccharmexg05.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma06")){
      fDCacheFileName = "0506emccharmexg06.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma07")){
      fDCacheFileName = "0506emccharmexg07.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma08")){
      fDCacheFileName = "0506emccharmexg08.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma09")){
      fDCacheFileName = "0506emccharmexg09.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma10")){
      fDCacheFileName = "0506emccharmexg10.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma11")){
      fDCacheFileName = "0506emccharmexg11.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exgamma12")){
      fDCacheFileName = "0506emccharmexg12.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exproton01")){
      fDCacheFileName = "0506emccharmexp01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exproton02")){
      fDCacheFileName = "0506emccharmexp02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exproton03")){
      fDCacheFileName = "0506emccharmexp03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/dirrap")){
      fDCacheFileName = "0506emccharmDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e-06e/resrap")){
      fDCacheFileName = "0506emccharmDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/05e-06e/DIS")){
      fDCacheFileName = "0506emcBHdis.txt";
    }   
    if(this->GetInputFilePath()->Contains("bh/05e-06e/elastic")){
      fDCacheFileName = "0506emcBHela.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/05e-06e/inelastic")){
      fDCacheFileName = "0506emcBHinela.txt";
    }   
    if(this->GetInputFilePath()->Contains("jpsi/05e-06e/jpsi1")){
      fDCacheFileName = "0506emcjpsi.txt";
    }
    if(this->GetInputFilePath()->Contains("jpsi/05e-06e/jpsi2")){
      fDCacheFileName = "0506emcjpsi2.txt";
    }
    if(this->GetInputFilePath()->Contains("psiprime/05e-06e/all")){
      fDCacheFileName = "0506emcpsiprime.txt";
    } 
    if(this->GetInputFilePath()->Contains("psiprime/05e-06e/psi2")){
      fDCacheFileName = "0506emcpsiprime2.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/05e-06e/1s_dir")){
      fDCacheFileName = "0506emcupsi1s.txt";
    }   
    if(this->GetInputFilePath()->Contains("upsilon/05e-06e/2s_dir")){
      fDCacheFileName = "0506emcupsi2s.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/05e-06e/3s_dir")){
      fDCacheFileName = "0506emcupsi3s.txt";
    } 
    if(this->GetInputFilePath()->Contains("instanton/05e-06e/inst1")){
      fDCacheFileName = "0506emcqcdins.txt";
    }
    if(this->GetInputFilePath()->Contains("bbbb/05e-06e/bbbb1")){
      fDCacheFileName = "0506emcmultibeauty.txt";
    }
    if(this->GetInputFilePath()->Contains("cccc/05e-06e/cccc1")){
      fDCacheFileName = "0506emcmulticharm.txt";
    }
    if(this->GetInputFilePath()->Contains("bbcc/05e-06e/bbcc1")){
      fDCacheFileName = "0506emcmultibbcc.txt";
    }
    if(this->GetInputFilePath()->Contains("c/05e-06e/dir_dijet")){
      fDCacheFileName = "0506emccharmdijetdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e-06e/res_dijet")){
      fDCacheFileName = "0506emccharmdijetres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e-06e/exg_dijet")){
      fDCacheFileName = "0506emccharmdijetexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e-06e/exp_dijet")){
      fDCacheFileName = "0506emccharmdijetexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/06p-07p/dir")){
      fDCacheFileName = "0607pmcbeautydir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/06p-07p/res")){
      fDCacheFileName = "0607pmcbeautyres.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/06p-07p/exg")){
      fDCacheFileName = "0607pmcbeautyexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/06p-07p/exp")){
      fDCacheFileName = "0607pmcbeautyexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/06p-07p/dirrap")){
      fDCacheFileName = "0607pmcbeautyDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/06p-07p/resrap")){
      fDCacheFileName = "0607pmcbeautyDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir")){
      fDCacheFileName = "0607pmccharmdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir01")){
      fDCacheFileName = "0607pmccharmdir01.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir02")){
      fDCacheFileName = "0607pmccharmdir02.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir03")){
      fDCacheFileName = "0607pmccharmdir03.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir04")){
      fDCacheFileName = "0607pmccharmdir04.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir05")){
      fDCacheFileName = "0607pmccharmdir05.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir06")){
      fDCacheFileName = "0607pmccharmdir06.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir07")){
      fDCacheFileName = "0607pmccharmdir07.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir08")){
      fDCacheFileName = "0607pmccharmdir08.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir09")){
      fDCacheFileName = "0607pmccharmdir09.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir10")){
      fDCacheFileName = "0607pmccharmdir10.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir11")){
      fDCacheFileName = "0607pmccharmdir11.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir12")){
      fDCacheFileName = "0607pmccharmdir12.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir13")){
      fDCacheFileName = "0607pmccharmdir13.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir14")){
      fDCacheFileName = "0607pmccharmdir14.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir15")){
      fDCacheFileName = "0607pmccharmdir15.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir16")){
      fDCacheFileName = "0607pmccharmdir16.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir17")){
      fDCacheFileName = "0607pmccharmdir17.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir18")){
      fDCacheFileName = "0607pmccharmdir18.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir19")){
      fDCacheFileName = "0607pmccharmdir19.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir20")){
      fDCacheFileName = "0607pmccharmdir20.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir21")){
      fDCacheFileName = "0607pmccharmdir21.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir22")){
      fDCacheFileName = "0607pmccharmdir22.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir23")){
      fDCacheFileName = "0607pmccharmdir23.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir24")){
      fDCacheFileName = "0607pmccharmdir24.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir25")){
      fDCacheFileName = "0607pmccharmdir25.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir26")){
      fDCacheFileName = "0607pmccharmdir26.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir27")){
      fDCacheFileName = "0607pmccharmdir27.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir28")){
      fDCacheFileName = "0607pmccharmdir28.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir29")){
      fDCacheFileName = "0607pmccharmdir29.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir30")){
      fDCacheFileName = "0607pmccharmdir30.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir31")){
      fDCacheFileName = "0607pmccharmdir31.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir32")){
      fDCacheFileName = "0607pmccharmdir32.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir33")){
      fDCacheFileName = "0607pmccharmdir33.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir34")){
      fDCacheFileName = "0607pmccharmdir34.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir35")){
      fDCacheFileName = "0607pmccharmdir35.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir36")){
      fDCacheFileName = "0607pmccharmdir36.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir37")){
      fDCacheFileName = "0607pmccharmdir37.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir38")){
      fDCacheFileName = "0607pmccharmdir38.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir39")){
      fDCacheFileName = "0607pmccharmdir39.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir40")){
      fDCacheFileName = "0607pmccharmdir40.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/res")){
      fDCacheFileName = "0607pmccharmres.txt";
    }
    if(this->GetInputFilePath()->Contains("c/06p-07p/res1")){
      fDCacheFileName = "0607pmccharmres1.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/res2")){
      fDCacheFileName = "0607pmccharmres2.txt";
    }
    if(this->GetInputFilePath()->Contains("c/06p-07p/res3")){
      fDCacheFileName = "0607pmccharmres3.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/res4")){
      fDCacheFileName = "0607pmccharmres4.txt";
    }
    if(this->GetInputFilePath()->Contains("c/06p-07p/res5")){
      fDCacheFileName = "0607pmccharmres5.txt";
    }
    if(this->GetInputFilePath()->Contains("c/06p-07p/exg")){
      fDCacheFileName = "0607pmccharmexg.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma1")){
      fDCacheFileName = "0607pmccharmexg1.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma2")){
      fDCacheFileName = "0607pmccharmexg2.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma3")){
      fDCacheFileName = "0607pmccharmexg3.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma4")){
      fDCacheFileName = "0607pmccharmexg4.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma5")){
      fDCacheFileName = "0607pmccharmexg5.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma6")){
      fDCacheFileName = "0607pmccharmexg6.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma7")){
      fDCacheFileName = "0607pmccharmexg7.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exgamma8")){
      fDCacheFileName = "0607pmccharmexg8.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/exp")){
      fDCacheFileName = "0607pmccharmexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/dirrap")){
      fDCacheFileName = "0607pmccharmDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/resrap")){
      fDCacheFileName = "0607pmccharmDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/06p-07p/DIS")){
      fDCacheFileName = "0607pmcBHdis.txt";
    }   
    if(this->GetInputFilePath()->Contains("bh/06p-07p/elastic")){
      fDCacheFileName = "0607pmcBHela.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/06p-07p/inelastic")){
      fDCacheFileName = "0607pmcBHinela.txt";
    }   
    if(this->GetInputFilePath()->Contains("jpsi/06p-07p/jpsi1")){
      fDCacheFileName = "0607pmcjpsi.txt";
    }   
    if(this->GetInputFilePath()->Contains("jpsi/06p-07p/jpsi2")){
      fDCacheFileName = "0607pmcjpsi2.txt";
    }  
    if(this->GetInputFilePath()->Contains("psiprime/06p-07p/all")){
      fDCacheFileName = "0607pmcpsiprime.txt";
    } 
    if(this->GetInputFilePath()->Contains("psiprime/06p-07p/psi2")){
      fDCacheFileName = "0607pmcpsiprime2.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/06p-07p/1s_dir")){
      fDCacheFileName = "0607pmcupsi1s.txt";
    }   
    if(this->GetInputFilePath()->Contains("upsilon/06p-07p/2s_dir")){
      fDCacheFileName = "0607pmcupsi2s.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/06p-07p/3s_dir")){
      fDCacheFileName = "0607pmcupsi3s.txt";
    } 
    if(this->GetInputFilePath()->Contains("instanton/06p-07p/inst1")){
      fDCacheFileName = "0607pmcqcdins.txt";
    } 
    if(this->GetInputFilePath()->Contains("bbbb/06p-07p/bbbb1")){
      fDCacheFileName = "0607pmcmultibeauty.txt";
    }
    if(this->GetInputFilePath()->Contains("cccc/06p-07p/cccc1")){
      fDCacheFileName = "0607pmcmulticharm.txt";
    }
    if(this->GetInputFilePath()->Contains("bbcc/06p-07p/bbcc1")){
      fDCacheFileName = "0607pmcmultibbcc.txt";
    }
    if(this->GetInputFilePath()->Contains("c/06p-07p/dir_dijet")){
      fDCacheFileName = "0607pmccharmdijetdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/res_dijet")){
      fDCacheFileName = "0607pmccharmdijetres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06p-07p/exg_dijet")){
      fDCacheFileName = "0607pmccharmdijetexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06p-07p/exp_dijet")){
      fDCacheFileName = "0607pmccharmdijetexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/05e/dir")){
      fDCacheFileName = "05emcbeautydir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/05e/res")){
      fDCacheFileName = "05emcbeautyres.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/05e/exg")){
      fDCacheFileName = "05emcbeautyexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/05e/exp")){
      fDCacheFileName = "05emcbeautyexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/05e/dirrap")){
      fDCacheFileName = "05emcbeautyDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/05e/resrap")){
      fDCacheFileName = "05emcbeautyDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/dir")){
      fDCacheFileName = "05emccharmdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e/dir01")){
      fDCacheFileName = "05emccharmdir01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/dir02")){
      fDCacheFileName = "05emccharmdir02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/dir03")){
      fDCacheFileName = "05emccharmdir03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/dir04")){
      fDCacheFileName = "05emccharmdir04.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/dir05")){
      fDCacheFileName = "05emccharmdir05.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/res")){
      fDCacheFileName = "05emccharmres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/exgamma01")){
      fDCacheFileName = "05emccharmexg01.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e/exgamma02")){
      fDCacheFileName = "05emccharmexg02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/exgamma03")){
      fDCacheFileName = "05emccharmexg03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/exgamma04")){
      fDCacheFileName = "05emccharmexg04.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/exproton")){
      fDCacheFileName = "05emccharmexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/05e/dirrap")){
      fDCacheFileName = "05emccharmDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/05e/resrap")){
      fDCacheFileName = "05emccharmDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/05e/DIS")){
      fDCacheFileName = "05emcBHdis.txt";
    }   
    if(this->GetInputFilePath()->Contains("bh/05e/elastic")){
      fDCacheFileName = "05emcBHela.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/05e/inelastic")){
      fDCacheFileName = "05emcBHinela.txt";
    }   
    if(this->GetInputFilePath()->Contains("jpsi/05e/jpsi1")){
      fDCacheFileName = "05emcjpsi.txt";
    }
    if(this->GetInputFilePath()->Contains("jpsi/05e/jpsi2")){
      fDCacheFileName = "05emcjpsi2.txt";
    }
    if(this->GetInputFilePath()->Contains("psiprime/05e/all")){
      fDCacheFileName = "05emcpsiprime.txt";
    } 
    if(this->GetInputFilePath()->Contains("psiprime/05e/psi2")){
      fDCacheFileName = "05emcpsiprime2.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/05e/1s_dir")){
      fDCacheFileName = "05emcupsi1s.txt";
    }   
    if(this->GetInputFilePath()->Contains("upsilon/05e/2s_dir")){
      fDCacheFileName = "05emcupsi2s.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/05e/3s_dir")){
      fDCacheFileName = "05emcupsi3s.txt";
    } 
    if(this->GetInputFilePath()->Contains("instanton/05e/inst1")){
      fDCacheFileName = "05emcqcdins.txt";
    }
    if(this->GetInputFilePath()->Contains("bbbb/05e/bbbb1")){
      fDCacheFileName = "05emcmultibeauty.txt";
    }
    if(this->GetInputFilePath()->Contains("cccc/05e/cccc1")){
      fDCacheFileName = "05emcmulticharm.txt";
    }
    if(this->GetInputFilePath()->Contains("bbcc/05e/bbcc1")){
      fDCacheFileName = "05emcmultibbcc.txt";
    }
    if(this->GetInputFilePath()->Contains("b/06e/dir")){
      fDCacheFileName = "06emcbeautydir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/06e/res")){
      fDCacheFileName = "06emcbeautyres.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/06e/exg")){
      fDCacheFileName = "06emcbeautyexg.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/06e/exp")){
      fDCacheFileName = "06emcbeautyexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("b/06e/dirrap")){
      fDCacheFileName = "06emcbeautyDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("b/06e/resrap")){
      fDCacheFileName = "06emcbeautyDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/dir")){
      fDCacheFileName = "06emccharmdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06e/dir01")){
      fDCacheFileName = "06emccharmdir01.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/dir02")){
      fDCacheFileName = "06emccharmdir02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/dir03")){
      fDCacheFileName = "06emccharmdir03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/dir04")){
      fDCacheFileName = "06emccharmdir04.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/dir05")){
      fDCacheFileName = "06emccharmdir05.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/res")){
      fDCacheFileName = "06emccharmres.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/exgamma01")){
      fDCacheFileName = "06emccharmexg01.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06e/exgamma02")){
      fDCacheFileName = "06emccharmexg02.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/exgamma03")){
      fDCacheFileName = "06emccharmexg03.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/exgamma04")){
      fDCacheFileName = "06emccharmexg04.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/exproton")){
      fDCacheFileName = "06emccharmexp.txt";
    } 
    if(this->GetInputFilePath()->Contains("c/06e/dirrap")){
      fDCacheFileName = "06emccharmDISdir.txt";
    }   
    if(this->GetInputFilePath()->Contains("c/06e/resrap")){
      fDCacheFileName = "06emccharmDISres.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/06e/DIS")){
      fDCacheFileName = "06emcBHdis.txt";
    }   
    if(this->GetInputFilePath()->Contains("bh/06e/elastic")){
      fDCacheFileName = "06emcBHela.txt";
    } 
    if(this->GetInputFilePath()->Contains("bh/06e/inelastic")){
      fDCacheFileName = "06emcBHinela.txt";
    }   
    if(this->GetInputFilePath()->Contains("jpsi/06e/jpsi1")){
      fDCacheFileName = "06emcjpsi.txt";
    }
    if(this->GetInputFilePath()->Contains("jpsi/06e/jpsi2")){
      fDCacheFileName = "06emcjpsi2.txt";
    }
    if(this->GetInputFilePath()->Contains("psiprime/06e/all")){
      fDCacheFileName = "06emcpsiprime.txt";
    } 
    if(this->GetInputFilePath()->Contains("psiprime/06e/psi2")){
      fDCacheFileName = "06emcpsiprime2.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/06e/1s_dir")){
      fDCacheFileName = "06emcupsi1s.txt";
    }   
    if(this->GetInputFilePath()->Contains("upsilon/06e/2s_dir")){
      fDCacheFileName = "06emcupsi2s.txt";
    } 
    if(this->GetInputFilePath()->Contains("upsilon/06e/3s_dir")){
      fDCacheFileName = "06emcupsi3s.txt";
    } 
    if(this->GetInputFilePath()->Contains("instanton/06e/inst1")){
      fDCacheFileName = "06emcqcdins.txt";
    }
    if(this->GetInputFilePath()->Contains("bbbb/06e/bbbb1")){
      fDCacheFileName = "06emcmultibeauty.txt";
    }
    if(this->GetInputFilePath()->Contains("cccc/06e/cccc1")){
      fDCacheFileName = "06emcmulticharm.txt";
    }
    if(this->GetInputFilePath()->Contains("bbcc/06e/bbcc1")){
      fDCacheFileName = "06emcmultibbcc.txt";
    }
   }
  return kTRUE;

}
