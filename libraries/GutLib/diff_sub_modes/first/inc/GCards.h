//
// GCards.h
//
// $Author: kahle $
// $Date: 2008/06/10 08:46:47 $
// $Revision: 1.101 $
//

#ifndef GUT_GCards
#define GUT_GCards

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

class GCards : public TObject {

 private:

  // status variable for valid card reading
  Bool_t                  fOK;                             // flag if everything is ok

  // general
  TString                *fInputFilePath;                  // path of input root files
  TString                *fAddToNames;                     // addendum to output file names if inputdir different from data
  TString                *fOutputPath;                     // path for output files
  TString                 fDCacheFileName;                 // read files from dcache
  TString                *fOutputFileName;                 // name of output root file
  Int_t                   fStartEntry;                     // start entry for loop over chain
  Int_t                   fEndEntry;                       // end entry for loop over chain
  Int_t                   fEventOut;                       // after each number of processed events output
  Double_t                fLuminosity;                     // luminosity corresponding to data sample
  Double_t                fLumiWeight;                     // MC Lumi Weighting Factor;
  Bool_t                  fHERA2;
  Bool_t                  fHERA1;
  Bool_t                  fMC;                             // flag for MC
  Bool_t                  fFMCK;                           // flag for FMCKIN Block
  Bool_t                  fDoFake;                         // apply fakemuon probabilities
  Bool_t                  fProduceFakeProbability;         // produce fakemuon probabilities
  Bool_t                  fMCOwn;                          // flag for own MC block
  Bool_t                  fMCOwnJets;                      // flag for own MC jets block
  Bool_t                  fDIMuonMCplots;                  // flag for producing MC Dimuon plots
  Bool_t                  fMCLF;                           // flag for lf MC
  Bool_t                  fMCBBBAR;                        // flag for bbbar MC
  Bool_t                  fMCCCBAR;                        // flag for ccbar MC
  Bool_t                  fMCJPSIHRWG;                     // flag for Herwig JPsi MC
  Bool_t                  fMCPSIPRIMEHRWG;                 // flag for Herwig Psiprime MC
  Bool_t                  fMCRejectHFL;                    // flag for rejecting HFL in LF MC samples
  TString                 fMCRunPeriod;                    // MC run period
  Double_t                fMCQ2Cut;                        // MC cut on true Q2
  Double_t                fMCLowQ2Cut;                     // lower MC cut on true Q2
  Double_t                fMCQ2SelectionCut;               // MC selection cut on true Q2
  Bool_t                  fMCQ2LowCut;                     // MC selection cut used as low cut on true Q2
  Double_t                fMCYLowCut;                      // low cut on true y
  Double_t                fMCYHighCut;                     // high cut on true y
  Bool_t                  fGMuon;                          // flag for gmuon selection
  Bool_t                  fDoJpsiReweight;                 // flag for DoJpsiReweight
  Bool_t                  fDoPsiprimeReweight;             // flag for DoPsiprimeReweight
  Bool_t                  fDoEfficiency;                   // flag for DoEfficiency 
  Bool_t                  fDoEventlist;                    // flag for DoEventlist selection
  Bool_t                  fWriteEventlistNtuple;           // flag for WriteEventlistNtuple selection
  Bool_t                  fEvtake;                         // flag for check of evtake list
  Bool_t                  fMvdtake;                        // flag for check of mvdtake list
  Int_t                   fMaximalRunnr;                   // maximal runnr after which processing is stopped
  Int_t                   fMinimalRunnr;                   // minimal runnr at which processing is started
  Bool_t                  fWeightFirstMuon;                // take only first valid muon for weight determination
  Bool_t                  fMiniNtuples;                    // mini ntuple mode, switch off lumi calculation from evtake and mvdtake list
  Bool_t                  fdCache;                         // read files from dCache
  Int_t                   fMBTake;                         // if > 0, take only runs with good barrel/rear muon chamber operation, =1 take only runs with completely working chambers, =2 take also runs with partially working chambers
  Int_t                   fFMUTake;                        // if > 0, take only runs with good forward muon chamber operation, =1 take only runs with completely working chambers, =2 take also runs with bad trigger
  Bool_t                  fExcludeShiftedVertexRuns;       // exclude runs with shifted vertex


  // machine
  Bool_t                  fPositron;                       // flag if machine is run with positrons
  Double_t                fEnergyLepton;                   // lepton energy in GeV
  Double_t                fEnergyProton;                   // proton energy in GeV
  Double_t                fLowerEnergyProton;              // lower proton energy in GeV
  Double_t                fHigherEnergyProton;             // higher proton energy in GeV

  // particles
  Double_t                fMassMuon;                       // muon mass

  // Lists
  Bool_t                  fProcEvents;                     // list with processed events
  Bool_t                  fErrorList;                      // list with errors
  Bool_t                  fSelectionList;                  // list with final selection
  Bool_t                  fOutputList;                     // list with final selection
  Bool_t                  fOutputListGGENERAL;             // output of ggeneral infos
  Bool_t                  fOutputListRUNS;                 // output of run infos
  Bool_t                  fOutputListMUONS;                // output of muon infos
  Bool_t                  fOutputListCAL;                  // output of cal infos
  Bool_t                  fOutputListBAC;                  // output of bac infos
  Bool_t                  fOutputListJETS;                 // output of jets infos
  Bool_t                  fOutputListMJMATCHS;             // output of mjmatchs infos
  Bool_t                  fOutputListTJMATCHS;             // output of tjmatchs infos
  Bool_t                  fOutputListSINISTRA;             // output of sinistra infos
  Bool_t                  fOutputListTRACKS;               // output of tracks infos
  Bool_t                  fOutputListVERTEX;               // output of vertex infos
  Bool_t                  fOutputListZUFO;                 // output of zufo infos
  Bool_t                  fOutputListMC;                   // output of mc infos
  Bool_t                  fOutputListDIMUONS;              // output of dimuon infos
  Bool_t                  fOutputListMVD;                  // output of MVD infos
  Bool_t                  fOutputSelected;                 // write out info of selected events
  Bool_t                  fOutputAll;                      // write out info of all events

  // ggeneral
  Bool_t                  fGGeneralGeneral;                // flag for generating general ggeneral histograms
  Bool_t                  fGGeneralControl;                // flag for generating control ggeneral histograms

  // mc
  Bool_t                  fMcGeneral;                      // flag for generating general mc histograms
  Bool_t                  fMcControl;                      // flag for generating control mc histograms

  // trigger
  Bool_t                  fTriggerGeneral;                 // flag for generating general trigger histograms
  Bool_t                  fTriggerControl;                 // flag for generating control trigger histograms
  UInt_t                  fTriggerTLTEXO96p00p;            // bit pattern for EXO TLT triggers (tlt words  6 and 13) for 96p - 00p
  UInt_t                  fTriggerTLTEXO03p04p;            // bit pattern for EXO TLT triggers (tlt words  6 and 13) for 03p - 04p
  UInt_t                  fTriggerTLTEXO05e06e;            // bit pattern for EXO TLT triggers (tlt words  6 and 13) for 05e - 06e
  UInt_t                  fTriggerTLTEXO06p07p;            // bit pattern for EXO TLT triggers (tlt words  6 and 13) for 06p - 07p
  UInt_t                  fTriggerTLTHPP96p00p;            // bit pattern for HPP TLT triggers (tlt words  5 and 12) for 96p - 00p
  UInt_t                  fTriggerTLTHPP03p04p;            // bit pattern for HPP TLT triggers (tlt words  5 and 12) for 03p - 04p
  UInt_t                  fTriggerTLTHPP05e06e;            // bit pattern for HPP TLT triggers (tlt words  5 and 12) for 05e - 06e
  UInt_t                  fTriggerTLTHPP06p07p;            // bit pattern for HPP TLT triggers (tlt words  5 and 12) for 06p - 07p
  UInt_t                  fTriggerTLTHFL96p00p;            // bit pattern for HFL TLT triggers (tlt words 10 and 14) for 96p - 00p
  UInt_t                  fTriggerTLTHFL99p00p;            // bit pattern for HFL TLT triggers (tlt words 10 and 14) for 99p - 00p
  UInt_t                  fTriggerTLTHFL03p04p;            // bit pattern for HFL TLT triggers (tlt words 10 and 14) for 03p - 04p
  UInt_t                  fTriggerTLTHFL05e06e;            // bit pattern for HFL TLT triggers (tlt words 10 and 14) for 05e - 06e
  UInt_t                  fTriggerTLTHFL06p07p;            // bit pattern for HFL TLT triggers (tlt words 10 and 14) for 06p - 07p
  UInt_t                  fTriggerTLTDIS96p00p;            // bit pattern for DIS TLT triggers (tlt words  4 and 11) for 96p - 00p
  UInt_t                  fTriggerTLTDIS03p04p;            // bit pattern for DIS TLT triggers (tlt words  4 and 11) for 03p - 04p
  UInt_t                  fTriggerTLTDIS05e06e;            // bit pattern for DIS TLT triggers (tlt words  4 and 11) for 05e - 06e
  UInt_t                  fTriggerTLTDIS06p07p;            // bit pattern for DIS TLT triggers (tlt words  4 and 11) for 06p - 07p
  UInt_t                  fTriggerTLTMUO96p00p;            // bit pattern for MUO TLT triggers (tlt word 7) for 96p - 00p
  UInt_t                  fTriggerTLTMUO03p04p;            // bit pattern for MUO TLT triggers (tlt word 7) for 03p - 04p
  UInt_t                  fTriggerTLTMUO05e06e;            // bit pattern for MUO TLT triggers (tlt word 7) for 05e - 06e
  UInt_t                  fTriggerTLTMUO06p07p;            // bit pattern for MUO TLT triggers (tlt word 7) for 06p - 07p
  UInt_t                  fTriggerTLTSPP03p04p;            // bit pattern for SPP TLT triggers (tlt word 2) for 03p - 04p
  UInt_t                  fTriggerTLTSPP05e06e;            // bit pattern for SPP TLT triggers (tlt word 2) for 05e - 06e
  UInt_t                  fTriggerTLTSPP06p07p;            // bit pattern for SPP TLT triggers (tlt word 2) for 06p - 07p
  Bool_t                  fTriggerEfficiencyCorrection;    // activate trigger efficiency correction
  Bool_t                  fTriggerDimuonEfficiencyCorrection;    // activate dimuon trigger efficiency correction
  Double_t                fTriggerEffCorr1011;             // correction factor for FLT 10,11
  Double_t                fTriggerEffCorr4254Forward;      // correction factor for FLT 42,44,51,52,53,54 (forward)
  Double_t                fTriggerEffCorr4254Barrel;       // correction factor for FLT 42,44,51,52,53,54 (barrel)
  Double_t                fTriggerEffCorr4254Rear;         // correction factor for FLT 42,44,51,52,53,54 (rear)

  // sinistra
  Bool_t                  fSinistraGeneral;                // flag for generating general sinistra histograms
  Bool_t                  fSinistraControl;                // flag for generating control sinistra histograms

  Double_t                fSinistraProbCut;                // probability cut for sinistra
  Bool_t                  fSinistraDIS;                    // flag for DIS or PhP
  Bool_t                  fSinistraNoCut;                  // flag for DIS and PhP
  Double_t                fSinistraEnergyCut;              // energy cut for sinistra
  Double_t                fSinistraYELCut;                 // cut on y_el for DIS removal
  Double_t                fSinistraYELHighCut;             // cut on y_el for DIS
  Double_t                fSinistraYELLowCut;              // low cut on y_el for DIS
  Double_t                fSinistraQ2LowCut;               // low cut on Q2_jb for DIS
  Bool_t                  fSinistraBoxCut;                 // cut on Sinistra position
  Double_t                fSinistraBoxXCut;                // cut on Sinistra X position
  Double_t                fSinistraBoxYCut;                // cut on Sinistra Y position

  // CAL
  Bool_t                  fCALGeneral;                     // flag for generating general CAL histograms
  Bool_t                  fCALControl;                     // flag for generating control CAL histograms
  Double_t                fCALEmpzCut;                     // e-p_z cut
  Double_t                fCALYJBLOWCut;                   // lower cut on y_jb
  Double_t                fCALYJBUPCut;                    // upper cut on y_jb
  Double_t                fCALModeETCut;                   // Mode for cal_et cut: 1 = cal_et, 2 = cal_et-et10, 3 = cal_et - et10 - si_pt, nothing set: cal_et-et10
  Double_t                fCALETCut;                       // cut in E_T depending on ModeETCut
  Double_t                fCALTimeCut;                     // cut on absolute value auf cal_tg
  Double_t                fCALPtOvEtCut;                   // cut on Pt/Et

  // BAC
  Bool_t                  fBACGeneral;                     // flag for generating general BAC histograms
  Bool_t                  fBACControl;                     // flag for generating control BAC histograms
  Double_t                fBACbac_etotLOWCut;              // bac_etot lower cut
  Double_t                fBACbac_etotUPCut;               // bac_etot upper cut
  Double_t                fBACnbacmuCut;                   // nbacmu cut

  // ZUFO
  Bool_t                  fZUFOGeneral;                    // flag for generating general ZUFO histograms
  Bool_t                  fZUFOControl;                    // flag for generating control ZUFO histograms
  Double_t                fZUFOYJBLOWCut;                  // lower cut on y_jb
  Double_t                fZUFOYJBUPCut;                   // upper cut on y_jb
  Double_t                fZUFOEmpzUpCut;                  // upper cut on E minus pz
  Double_t                fZUFOEmpzLowCut;                 // lower cut on E minus pz
  Double_t                fZUFOPtHadMaxCut;                // cut on maximum of Pt_Had
  Double_t                fZUFOQ2PrimeLowCut;              // cut on Q'2 for eventshape variables

  // JET
  Bool_t                  fJETGeneral;                     // flag for generating general JET histograms
  Bool_t                  fJETControl;                     // flag for generating control JET histograms
  Bool_t                  fNewNtuple;                      // flag for using old ntuple format even for dis
  Bool_t                  fJETBreit;                       // flag for breitframe jets
  Int_t                   fJETNCut;                        // minimal number of jets cut
  Double_t                fJETPtACut;                      // p_t cut for hightest jet
  Double_t                fJETPtBCut;                      // p_t cut for second hightest jet
  Double_t                fJETEtaLowCut;                   // lower cut on eta 
  Double_t                fJETEtaUpCut;                    // upper cut on eta 
  Bool_t                  fJETCutOnEt;                     // if true, cuts denoted as Pt cuts are changed to be Et cuts

  // Vertex
  Bool_t                  fVertexGeneral;                  // flag for generating general vertex plots
  Bool_t                  fVertexControl;                  // flag for generating control vertex plots
  Double_t                fVertexNomX;                     // x position of nominal vertex
  Double_t                fVertexNomXOld;                  // x position of nominal vertex for 96-00
  Double_t                fVertexNomXNew;                  // x position of nominal vertex for 03-04
  Double_t                fVertexNomY;                     // y position of nominal vertex
  Double_t                fVertexNomZ;                     // z position of nominal vertex
  Double_t                fVertexZCut;                     // surrounding cut around nominal vertex in cm
  Bool_t                  fVertexXCut;                     // require that x vertex is not zero
  Bool_t                  fVertexYCut;                     // require that y vertex is not zero
  Double_t                fVertexXYCut;                    // minimal distance of vertex in xy from nominal vertex
  Bool_t                  fVertexBeamSpotCut;              // require valid beamspot
  Double_t                fVertexBeamSpotX;                // nominal x beam spot 
  Double_t                fVertexBeamSpotXSigma;           // nominal sigma of x beam spot 
  Double_t                fVertexBeamSpotY;                // nominal y beam spot 
  Double_t                fVertexBeamSpotYSigma;           // nominal sigma of y beam spot 
  Double_t                fVertexBeamSpotZ;                // nominal z beam spot 
  Double_t                fVertexBeamSpotZSigma;           // nominal sigma of z beam spot 
  Double_t                fVertexOldBeamSpotX;             // nominal x beam spot pre-upgrade 
  Double_t                fVertexOldBeamSpotXSigma;        // nominal sigma of x beam spot pre-upgrade
  Double_t                fVertexOldBeamSpotY;             // nominal y beam spot pre-upgrade
  Double_t                fVertexOldBeamSpotYSigma;        // nominal sigma of y beam spot pre-upgrade
  Double_t                fVertexOldBeamSpotZ;             // nominal z beam spot pre-upgrade
  Double_t                fVertexOldBeamSpotZSigma;        // nominal sigma of z beam spot pre-upgrade
  Double_t                fVertexNewBeamSpotX;             // nominal x beam spot post-upgrade 
  Double_t                fVertexNewBeamSpotXSigma;        // nominal sigma of x beam spot post-upgrade
  Double_t                fVertexNewBeamSpotY;             // nominal y beam spot post-upgrade
  Double_t                fVertexNewBeamSpotYSigma;        // nominal sigma of y beam spot post-upgrade
  Double_t                fVertexNewBeamSpotZ;             // nominal z beam spot post-upgrade
  Double_t                fVertexNewBeamSpotZSigma;        // nominal sigma of z beam spot post-upgrade
  Bool_t                  fVertexUseAllRuns;               // use all runs for beamspot

  // MUON
  Bool_t                  fMUONGeneral;                         // flag for generating general MUON histograms
  Bool_t                  fMUONControl;                         // flag for generating control MUON histograms
  Int_t                   fMUONNCut;                            // cut on number of reconstructed muons, if 0, muon id is switched off
  Bool_t                  fMUONFillAll;                         // flag for filling all muonin general plots, not only chosen muons
  Double_t                fMUONBremProb;                        // minimal bremat matching probability
  Int_t                   fMUONBremChamberFlag;                 // chamber flag requirement for bremat
  Double_t                fMUONMPMProb;                         // minimal MPMATCH2 matching probability
  Double_t                fMUONMUBACBacFlag;                    // maximal Bac Flag for MUBAC
  Int_t                   fMUONChamberFlagCut ;                 // identify muon as forward track muon if muchfl gt cut
  Double_t                fMUONMfpro;                           // minimal kalman filter probability for the associated mfrtz track
  Int_t                   fMUONMfndf;                           // minimal kalman filter degrees of freedom
  Int_t                   fMUONMfz;                             // maximal internal plane requirement for the track
  Int_t                   fMUONBACFQuality;                     // quality requirement for forward muons found only by mubac (chamber_flag = 0)  (greater_equal)
  Int_t                   fMUONVcidLowCut;                      // minimal vctrhl id of muon
  Int_t                   fMUONVcidUpCut;                       // maximal vctrhl id of muon
  Bool_t                  fMUONModifyQuality;                   // activate modify muon quality routine
  Bool_t                  fMuqualServicePack1;                  // activate muqual recalculation (Servive pack 1, by A. Geiser)
  Bool_t                  fMUONEfficiencyCorrection;            // activate muon efficiency correction routine, else take efficiency correction factors given for muon regions
  Bool_t                  fMuqualBasedEffCorr;                  // activate muqual based muon efficiency correction
  Bool_t                  fMUONReadEfficiencyFiles;             // activate efficiency base file reading
  TString                 fMUONEfficiencyFile;                  // file with efficiency histograms in $GUTCODEDIR/analysis/efficiencies for loose configuration (former standard)
  Int_t                   fMUONEfficiencyMPMATCHPtNBins;        // number of pt bins for the MPMATCH efficiencies for data and mc for loose configuration (former standard)
  Double_t*               fMUONEfficiencyMPMATCHPtBins;         // pt bins for MPMATCH efficiencies [PtNBins+1] for loose configuration (former standard)
  Int_t                   fMUONEfficiencyBREMATPtNBins;         // number of pt bins for the BREMAT efficiencies for data and mc for loose configuration (former standard)
  Double_t*               fMUONEfficiencyBREMATPtBins;          // pt bins for BREMAT efficiencies [PtNBins+1] for loose configuration (former standard)
  Int_t                   fMUONEfficiencyMUBACPtNBins;          // number of pt bins for the MUBAC efficiencies for data and mc for loose configuration (former standard)
  Double_t*               fMUONEfficiencyMUBACPtBins;           // pt bins for MUBAC efficiencies [PtNBins+1] for loose configuration (former standard)
  TString                 fMUONTIGHTEfficiencyFile;             // file with efficiency histograms in $GUTCODEDIR/analysis/efficiencies for tight configuration (former standard)
  Int_t                   fMUONTIGHTEfficiencyMPMATCHPtNBins;   // number of pt bins for the MPMATCH efficiencies for data and mc for tight configuration (former standard)
  Double_t*               fMUONTIGHTEfficiencyMPMATCHPtBins;    // pt bins for MPMATCH efficiencies [PtNBins+1] for tight configuration (former standard)
  Int_t                   fMUONTIGHTEfficiencyBREMATPtNBins;    // number of pt bins for the BREMAT efficiencies for data and mc for tight configuration (former standard)
  Double_t*               fMUONTIGHTEfficiencyBREMATPtBins;     // pt bins for BREMAT efficiencies [PtNBins+1] for tight configuration (former standard)
  Int_t                   fMUONTIGHTEfficiencyMUBACPtNBins;     // number of pt bins for the MUBAC efficiencies for data and mc for tight configuration (former standard)
  Double_t*               fMUONTIGHTEfficiencyMUBACPtBins;      // pt bins for MUBAC efficiencies [PtNBins+1] for tight configuration (former standard)
  Double_t                fMUONEfficiencyCutOff;                // cut off for muon efficiency correction factor, if larger, factor is reset to this value
  Bool_t                  fMUONCalculateMuonIsolation;          // switch for calculation of muon isolation for muons which have passed all previous cuts
  Double_t                fMUONMinIsolation10Veto;              // minimum isolation for cone 1.0, if one good muon of event has a smaller isolation, veto event
  Bool_t                  fMUONExcludeMamma;                    // exclude mamma in muon modification routine
  TString                 fFakeProbabilityFile;                 // file with  fake muon probabilities

  // FORWARD MUON
  Double_t                fFMUONEtaLow;                    // lower eta cut for forward muons
  Double_t                fFMUONEtaUp;                     // upper eta cut for forward muons
  Double_t                fFMUONP;                         // minimal momentum cut for forward muons
  Double_t                fFMUONPt;                        // minimal transverse momentum cut for forward muons
  Int_t                   fFMUONQualCut1;                  // quality cut for first quality-p_T cut pair for forward muons
  Double_t                fFMUONPTCut1;                    // p_T cut for first quality-p_T cut pair for forward muons
  Int_t                   fFMUONQualCut2;                  // quality cut for second quality-p_T cut pair for forward muons
  Double_t                fFMUONPTCut2;                    // p_T cut for second quality-p_T cut pair for forward muons
  Int_t                   fFMUONFinder;                    // finder bits for "and" requirements for forward muons
  Double_t                fFMUONEfficiency99p00p;          // forward muon efficiency 99p-00p
  Double_t                fFMUONEfficiency98e99e;          // forward muon efficiency 98e-99e
  Double_t                fFMUONEfficiency96p97p;          // forward muon efficiency 96p-97p
  Double_t                fFMUONEfficiency03p04p;          // forward muon efficiency 03p-04p
  Double_t                fFMUONEfficiency05e06e;          // forward muon efficiency 05e-06e
  Double_t                fFMUONEfficiency06p07p;          // forward muon efficiency 06p-07p
  Bool_t                  fFMUONOnlyVertexFitted;          // forward muon has to be reconstructed from vertex fitted track (MuTrFl = 2 || 3)

  // BARREL MUON
  Double_t                fBMUONEtaLow;                    // lower eta cut for barrel muons
  Double_t                fBMUONEtaUp;                     // upper eta cut for barrel muons
  Double_t                fBMUONP;                         // minimal momentum cut for barrel muons
  Double_t                fBMUONPt;                        // minimal transverse momentum cut for barrel muons
  Int_t                   fBMUONQualCut1;                  // quality cut for first quality-p_T cut pair for barrel muons
  Double_t                fBMUONPTCut1;                    // p_T cut for first quality-p_T cut pair for barrel muons
  Int_t                   fBMUONQualCut2;                  // quality cut for second quality-p_T cut pair for barrel muons
  Double_t                fBMUONPTCut2;                    // p_T cut for second quality-p_T cut pair for barrel muons
  Int_t                   fBMUONFinder;                    // finder bits for "and" requirements for barrel muons
  Double_t                fBMUONEfficiency99p00p;          // barrel muon efficiency 99p-00p
  Double_t                fBMUONEfficiency98e99e;          // barrel muon efficiency 98e-99e
  Double_t                fBMUONEfficiency96p97p;          // barrel muon efficiency 96p-97p
  Double_t                fBMUONEfficiency03p04p;          // barrel muon efficiency 03p-04p
  Double_t                fBMUONEfficiency05e06e;          // barrel muon efficiency 05e-06e
  Double_t                fBMUONEfficiency06p07p;          // barrel muon efficiency 06p-07p
  Bool_t                  fBMUONOnlyVertexFitted;          // barrel muon has to be reconstructed from vertex fitted track (MuTrFl = 2 || 3)

  // REAR MUON
  Double_t                fRMUONEtaLow;                    // lower eta cut for rear muons
  Double_t                fRMUONEtaUp;                     // upper eta cut for rear muons
  Double_t                fRMUONP;                         // minimal momentum cut for rear muons
  Double_t                fRMUONPt;                        // minimal transverse momentum cut for rear muons
  Int_t                   fRMUONQualCut1;                  // quality cut for first quality-p_T cut pair for rear muons
  Double_t                fRMUONPTCut1;                    // p_T cut for first quality-p_T cut pair for rear muons
  Int_t                   fRMUONQualCut2;                  // quality cut for second quality-p_T cut pair for rear muons
  Double_t                fRMUONPTCut2;                    // p_T cut for second quality-p_T cut pair for rear muons
  Int_t                   fRMUONFinder;                    // finder bits for "and" requirements for rear muons
  Double_t                fRMUONEfficiency99p00p;          // rear muon efficiency 99p-00p
  Double_t                fRMUONEfficiency98e99e;          // rear muon efficiency 98e-99e
  Double_t                fRMUONEfficiency96p97p;          // rear muon efficiency 96p-97p
  Double_t                fRMUONEfficiency03p04p;          // rear muon efficiency 03p-04p
  Double_t                fRMUONEfficiency05e06e;          // rear muon efficiency 05e-06e
  Double_t                fRMUONEfficiency06p07p;          // rear muon efficiency 06p-07p
  Bool_t                  fRMUONOnlyVertexFitted;          // rear muon has to be reconstructed from vertex fitted track (MuTrFl = 2 || 3)

  // TRACKS
  Bool_t                  fTRACKSGeneral;                  // flag for generating general TRACKS histograms
  Bool_t                  fTRACKSControl;                  // flag for generating control TRACKS histograms
  Int_t                   fTRACKSMultiplicity;             // track multiplicity cut
  Int_t                   fTRACKSUsedSuperLayersCut;       // cut on used superlayers
  Int_t                   fTRACKSUsedHitsCut;              // cut on used axial and stereo hits
  Int_t                   fTRACKSUsedStereoHitsCut;        // cut on used stereo hits
  Int_t                   fTRACKSVertexCut;                // cut on maximum of vertex tracks
  Int_t                   fTRACKSMinVertexCut;             // cut on minimum of vertex tracks
  Double_t                fTRACKSTotalOvVertexCut;         // cut on total tracks/vertex tracks
  Double_t                fTRACKSZHCut;                    // cut on z_h of track
  Int_t                   fTRACKSMVDHitsCut;               // cut on used mvd hits
  UInt_t                  fTRACKSType;                     // tracktye 1=ctd 2=reg 3=ztt
  // MJMatch
  Bool_t                  fMJMATCHGeneral;                 // flag for generating general MJMATCH histograms
  Bool_t                  fMJMATCHControl;                 // flag for generating control MJMATCH histograms
  Double_t                fMJMATCHJetPtCut;                // match only jets with pt larger than cut
  Double_t                fMJMATCHMuMinusJetPtCut;         // match only jet-muon pairs with pt of jet-muon larger than cut
  Int_t                   fMJMATCHNMatchs;                 // how many matchs are required at least
  Double_t                fMJMATCHPtRelLow;                // lower cut on PtRel
  Double_t                fMJMATCHPtRelHigh;               // higher cut on PtRel
  Bool_t                  fMJMATCHTakeAllGood;             // take into account all good matches and not only the highest ptrel
  Bool_t                  fMJMATCHPtRelCorrection;         // activate ptrel correction
  TString                 fMJMATCHPtRelCorrFilename;       // filename with ptrel correction histograms in $GUTCODEDIR/analysis/ptrel_correction
  Double_t                fMJMATCHPtRelCorrCMCWeight;      // weight for correction in C MC samples
  Double_t                fMJMATCHPtRelCorrLFMCWeight;     // weight for correction in LF MC samples

  // TJMatch
  Bool_t                  fTJMATCHGeneral;                 // flag for generating general TJMATCH histograms
  Bool_t                  fTJMATCHControl;                 // flag for generating control TJMATCH histograms
  Int_t                   fTJMATCHNMatchs;                 // how many matchs are required at least
  Double_t                fTJMATCHJetPtCut;                // match only jets with pt larger than cut
  Double_t                fTJMATCHTrackMinusJetPtCut;      // match only jet-track pairs with pt of jet-track larger than cut
  Double_t                fTJMATCHAssociationCone;         // match track and jet if they are in deltaR cone of gives size

  // MVD
  Bool_t                  fMVDActivate;                    // flag for activation of MVD object
  Bool_t                  fMVDGeneral;                     // flag for generating general MVD histograms
  Bool_t                  fMVDControl;                     // flag for generating control MVD histograms

  // Dimuon
  Bool_t                  fDIMUONGeneral;                  // flag for generating general DIMUON histograms
  Bool_t                  fDIMUONControl;                  // flag for generating control DIMUON histograms
  Double_t                fDIMUONInvMassLowCut;            // cut on invariant mass of dimuon to be larger than cut-value
  Double_t                fDIMUONInvMassHighCut;           // cut on invariant mass of dimuon to be less than cut-value
  Double_t                fDIMUONSqSumIsolationCut;        // cut on sqsumisolation10 of dimuon to be .ge. cut-value
  Double_t                fDIMUONSqSumIsolationPeakCut;    // cut on sqsumisolation10 of dimuon to be .ge. cut-value, special for resonances
  Double_t                fDIMUONSqSumIsolationContCut;    // cut on sqsumisolation10 of dimuon to be .ge. cut-value, special outside resonances
  Double_t                fDIMUONDeltaRCut;                // cut on delta R of dimuon to be larger than cut-value
  Double_t                fDIMUONDeltaPhiCut;              // cut on delta phi of dimuon to be larger than cut-value
  Double_t                fDIMUONDeltaThetaCut;            // cut on delta theta of dimuon to be larger than cut-value
  Double_t                fDIMUONDeltaEtaCut;              // cut on delta eta of dimuon to be less than cut-value
  Double_t                fDIMUONPtAsymetryCut;            // cut on pt asymetry of dimuon to be .le. than cut-value
  Double_t                fDIMUONEtFractionHigh1Cut;       // cut on et fraction of highmass dimuon to be .le. than cut-value
  Double_t                fDIMUONEtFractionHigh2Cut;       // cut on et fraction of lowmass dimuon to be .le. than cut-value
  Double_t                fDIMUONEtFractionLowCut;         // cut on et fraction of all dimuons to be .ge. than cut-value
  Int_t                   fDIMUONNDimuons;                 // how many dimuons are required at least
  Bool_t                  fDIMUONDifCharge;                // requirement on different charge of the two muons
  Bool_t                  fDIMUONCharmMCJpsi;              // requirement rejecting jpsis in Charm MC (as they are added sepereately in a more controlled fashion)
  Bool_t                  fDIMUONCharmMCPsiprime;          // requirement rejecting psiprimes in Charm MC (as they are added sepereately in a more controlled fashion)

 // Dimuon
  Bool_t                  fTRIMUONGeneral;                  // flag for generating general TRIMUON histograms
  Bool_t                  fTRIMUONControl;                  // flag for generating control TRIMUON histograms
  Double_t                fTRIMUONInvMassLowCut;            // cut on invariant mass of dimuon to be larger than cut-value
  Double_t                fTRIMUONInvMassHighCut;           // cut on invariant mass of dimuon to be less than cut-value
  Double_t                fTRIMUONSqSumIsolationCut;        // cut on sqsumisolation10 of dimuon to be .ge. cut-value
  Double_t                fTRIMUONSqSumIsolationPeakCut;    // cut on sqsumisolation10 of dimuon to be .ge. cut-value, special for resonances
  Double_t                fTRIMUONSqSumIsolationContCut;    // cut on sqsumisolation10 of dimuon to be .ge. cut-value, special outside resonances
  Double_t                fTRIMUONDeltaRCut;                // cut on delta R of dimuon to be larger than cut-value
  Double_t                fTRIMUONDeltaPhiCut;              // cut on delta phi of dimuon to be larger than cut-value
  Double_t                fTRIMUONDeltaThetaCut;            // cut on delta theta of dimuon to be larger than cut-value
  Double_t                fTRIMUONDeltaEtaCut;              // cut on delta eta of dimuon to be less than cut-value
  Double_t                fTRIMUONPtAsymetryCut;            // cut on pt asymetry of dimuon to be .le. than cut-value
  Double_t                fTRIMUONEtFractionHigh1Cut;       // cut on et fraction of highmass dimuon to be .le. than cut-value
  Double_t                fTRIMUONEtFractionHigh2Cut;       // cut on et fraction of lowmass dimuon to be .le. than cut-value
  Double_t                fTRIMUONEtFractionLowCut;         // cut on et fraction of all dimuons to be .ge. than cut-value
  Int_t                   fTRIMUONNTrimuons;                // how many dimuons are required at least
  Bool_t                  fTRIMUONDifCharge;                // requirement on different charge of the two muons
  Bool_t                  fTRIMUONCharmMCJpsi;              // requirement rejecting jpsis in Charm MC (as they are added sepereately in a more controlled fashion)
  Bool_t                  fTRIMUONCharmMCPsiprime;          // requirement rejecting psiprimes in Charm MC (as they are added sepereately in a more controlled fashion)

  Bool_t                  fPICTURES_GIF;
  Bool_t                  fPICTURES_EPS;
  Bool_t                  fPICTURES_PS;
  Bool_t                  fPICTURES_JPG;
  Bool_t                  fPICTUREScomp_ptrel     ;  // produce different
  Bool_t                  fPICTUREScomp_muon      ;  // categories of 
  Bool_t                  fPICTUREScomp_jet       ;  // pictures in the 
  Bool_t                  fPICTUREScomp_mjmatch   ;  // picturemaker
  Bool_t                  fPICTUREScomp_tjmatch   ;  // picturemaker
  Bool_t                  fPICTUREScomp_cal       ;  // ...
  Bool_t                  fPICTUREScomp_tracks    ;
  Bool_t                  fPICTUREScomp_trigger   ;
  Bool_t                  fPICTUREScomp_zufo      ;
  Bool_t                  fPICTUREScomp_sinistra  ;
  Bool_t                  fPICTUREScomp_disonly   ;
  Bool_t                  fPICTUREScomp_phponly   ; 
						  
  Bool_t                  fPICTURESONED_dimuon    ;
  Bool_t                  fPICTURESONED_track     ;
  Bool_t                  fPICTURESONED_muon      ;
  						  
  Bool_t                  fPICTURESONEDMC_dimuon  ;
  Bool_t                  fPICTURESONEDMC_mc      ;
  Bool_t                  fPICTURESONEDMC_track   ;
  Bool_t                  fPICTURESONEDMC_muon    ;
						  
  Bool_t                  fPICTURESTWOD_mjmatch   ;
  Bool_t                  fPICTURESTWOD_tjmatch   ;
  Bool_t                  fPICTURESTWODMC_cal     ;
  Bool_t                  fPICTURESTWODMC_zufo    ;
  Bool_t                  fPICTURESTWODMC_mc      ;
  Bool_t                  fPICTURESTWODMC_muon    ;
  Bool_t                  fPICTURESTWODMC_mjmatch ;
  Bool_t                  fPICTURESTWODMC_tjmatch ;
  						  
  Bool_t                  fPICTURESTWODMCzoomed_mc;
  						  
  Bool_t                  fPICTURESEfficiencyFull ;

  // logchecker
  Bool_t                  fLogActivate;                    // flag if logchecker is activated
  Int_t                   fLogTermNumber;                  // number of terms to check
  TString                *fLogTerms;                       //[fLogTermNumber] terms to check
  Int_t                   fLogCountNumber;                 // number of terms to count
  TString                *fLogCountTerms;                  //[fLogCountNumber] terms to count
  Bool_t                  fPositiveFMCK;                   // flag to only use positive fmck id's

 public:
  GCards(TString name);
  virtual ~GCards();

  virtual Bool_t ReadControlCards(TString name);

  virtual TString* GetOutputFileName();
  virtual Bool_t ReadGeneral(TString* line);
  virtual Bool_t ReadMachine(TString* line);
  virtual Bool_t ReadLists(TString* line);
  virtual Bool_t ReadMass(TString* line);
  virtual Bool_t ReadGGeneral(TString* line);
  virtual Bool_t ReadMc(TString* line);
  virtual Bool_t ReadTrigger(TString* line);
  virtual Bool_t ReadSinistra(TString* line);
  virtual Bool_t ReadCal(TString* line);
  virtual Bool_t ReadBac(TString* line);
  virtual Bool_t ReadZufo(TString* line);
  virtual Bool_t ReadJet(TString* line);
  virtual Bool_t ReadVertex(TString* line);
  virtual Bool_t ReadMuon(TString* line);
  virtual Bool_t ReadFMuon(TString* line);
  virtual Bool_t ReadBMuon(TString* line);
  virtual Bool_t ReadRMuon(TString* line);
  virtual Bool_t ReadTracks(TString* line);
  virtual Bool_t ReadMJMatch(TString* line);
  virtual Bool_t ReadTJMatch(TString* line);
  virtual Bool_t ReadMVD(TString* line);
  virtual Bool_t ReadDIMuon(TString* line);
  virtual Bool_t ReadTRIMuon(TString* line);
  virtual Bool_t ReadLogChecker(TString* line);
  virtual Bool_t ReadPictures(TString* line);

  virtual        Bool_t   SetDCacheFileName();    
  inline virtual Bool_t   IsOK()                        { return fOK;                           }
  inline virtual TString* GetInputFilePath()            { return fInputFilePath;                }
  inline virtual TString  GetDCacheFileName()           { return fDCacheFileName;               }
  inline virtual TString* GetAddToNames()               { return fAddToNames;                   }
  inline virtual TString* GetOutputPath()               { return fOutputPath;                   }
  inline virtual Int_t    GetStartEntry()               { return fStartEntry;                   }
  inline virtual Int_t    GetEndEntry()                 { return fEndEntry;                     }
  inline virtual Int_t    GetEventOut()                 { return fEventOut;                     }
  inline virtual Double_t GetLuminosity()               { return fLuminosity;                   }
  inline virtual Double_t GetLumiWeight()               { return fLumiWeight;                   }
  inline virtual Bool_t   GetHERA1() {return fHERA1;}
  inline virtual Bool_t   GetHERA2() {return fHERA2;}
  inline virtual Bool_t   GetMC()                       { return fMC;                           }
  inline virtual Bool_t   GetFMCK()                     { return fFMCK;                         }
  inline virtual Bool_t   GetPositiveFMCK()             { return fPositiveFMCK;                 }
  inline virtual Bool_t   GetMCOwn()                    { return fMCOwn;                        }
  inline virtual Bool_t   GetMCOwnJets()                { return fMCOwnJets;                    }
  inline virtual Bool_t   GetDIMuonMCplots()            { return fDIMuonMCplots;                }
  inline virtual Bool_t   GetMCLF()                     { return fMCLF;                         }
  inline virtual Bool_t   GetMCBBBAR()                  { return fMCBBBAR;                      }
  inline virtual Bool_t   GetMCCCBAR()                  { return fMCCCBAR;                      }
  inline virtual Bool_t   GetMCJPSIHRWG()               { return fMCJPSIHRWG;                   }
  inline virtual Bool_t   GetMCPSIPRIMEHRWG()           { return fMCPSIPRIMEHRWG;               }
  inline virtual Bool_t   GetMCRejectHFL()              { return fMCRejectHFL;                  }
  inline virtual TString  GetMCRunPeriod()              { return fMCRunPeriod;                  }
  inline virtual Double_t GetMCQ2Cut()                  { return fMCQ2Cut;                      }
  inline virtual Double_t GetMCLowQ2Cut()               { return fMCLowQ2Cut;                   }
  inline virtual Double_t GetMCQ2SelectionCut()       	{ return fMCQ2SelectionCut;       	}
  inline virtual Bool_t   GetMCQ2LowCut()             	{ return fMCQ2LowCut;             	}
  inline virtual Double_t GetMCYLowCut()                { return fMCYLowCut;                    }
  inline virtual Double_t GetMCYHighCut()               { return fMCYHighCut;                   }
  inline virtual Bool_t   GetGMuon()                    { return fGMuon;                        }
  inline virtual Bool_t   GetDoJpsiReweight()           { return fDoJpsiReweight;               }
  inline virtual Bool_t   GetDoPsiprimeReweight()       { return fDoPsiprimeReweight;           }
  inline virtual Bool_t   GetDoEfficiency()             { return fDoEfficiency;                 }
  inline virtual Bool_t   GetDoFake()                   { return fDoFake;                       }
  inline virtual Bool_t   GetProduceFakeMuon()          { return fProduceFakeProbability;       }
  inline virtual Bool_t   GetDoEventlist()              { return fDoEventlist;                  }
  inline virtual Bool_t   GetWriteEventlistNtuple()     { return fWriteEventlistNtuple;         }
  inline virtual Bool_t   GetEvtake()                   { return fEvtake;                       }
  inline virtual Bool_t   GetMvdtake()                  { return fMvdtake;                      }
  inline virtual Int_t    GetMaximalRunnr()             { return fMaximalRunnr;                 }
  inline virtual Int_t    GetMinimalRunnr()             { return fMinimalRunnr;                 }
  inline virtual Bool_t   GetWeightFirstMuon()          { return fWeightFirstMuon;              }
  inline virtual Bool_t   GetMiniNtuples()              { return fMiniNtuples;                  }
  inline virtual Bool_t   GetdCache()                   { return fdCache;                       }
  inline virtual Bool_t   GetNewNtuple()                { return fNewNtuple;                    }
  inline virtual Int_t    GetMBTake()                   { return fMBTake;                       }
  inline virtual Int_t    GetFMUTake()                  { return fFMUTake;                      }
  inline virtual Bool_t   GetExcludeShiftedVertexRuns() { return fExcludeShiftedVertexRuns;     }
  inline virtual TString  GetFakeProbabilityFile()      { return fFakeProbabilityFile;          }

  inline virtual Bool_t   GetMachinePositron()                   { return fPositron;           }
  inline virtual void     SetMachinePositron(Bool_t input)       { fPositron = input;          }
  inline virtual Double_t GetMachineEnergyLepton()               { return fEnergyLepton;       }
  inline virtual Double_t GetMachineEnergyProton()               { return fEnergyProton;       }
  inline virtual void     SetMachineEnergyProton(Double_t input) { fEnergyProton = input;      }
  inline virtual Double_t GetMachineLowerEnergyProton()          { return fLowerEnergyProton;  }
  inline virtual Double_t GetMachineHigherEnergyProton()         { return fHigherEnergyProton; }

  inline virtual Bool_t   GetListsProcEvents()          { return fProcEvents;            }
  inline virtual Bool_t   GetListsErrorList()           { return fErrorList;             }
  inline virtual Bool_t   GetListsSelectionList()       { return fSelectionList;         }
  inline virtual Bool_t   GetListsOutputList()          { return fOutputList;            }
  inline virtual Bool_t   GetListsOutputListGGENERAL()  { return fOutputListGGENERAL;    }
  inline virtual Bool_t   GetListsOutputListRUNS()      { return fOutputListRUNS;        }
  inline virtual Bool_t   GetListsOutputListMUONS()     { return fOutputListMUONS;       }
  inline virtual Bool_t   GetListsOutputListCAL()       { return fOutputListCAL;         }
  inline virtual Bool_t   GetListsOutputListBAC()       { return fOutputListBAC;         }
  inline virtual Bool_t   GetListsOutputListJETS()      { return fOutputListJETS;        }
  inline virtual Bool_t   GetListsOutputListMJMATCHS()  { return fOutputListMJMATCHS;    }
  inline virtual Bool_t   GetListsOutputListTJMATCHS()  { return fOutputListTJMATCHS;    }
  inline virtual Bool_t   GetListsOutputListSINISTRA()  { return fOutputListSINISTRA;    }
  inline virtual Bool_t   GetListsOutputListTRACKS()    { return fOutputListTRACKS;      }
  inline virtual Bool_t   GetListsOutputListVERTEX()    { return fOutputListVERTEX;      }
  inline virtual Bool_t   GetListsOutputListZUFO()      { return fOutputListZUFO;        }
  inline virtual Bool_t   GetListsOutputListMC()        { return fOutputListMC;          }
  inline virtual Bool_t   GetListsOutputListDIMUONS()   { return fOutputListDIMUONS;     }
  inline virtual Bool_t   GetListsOutputListMVD()       { return fOutputListMVD;         }
  inline virtual Bool_t   GetListsOutputSelected()      { return fOutputSelected;        }
  inline virtual Bool_t   GetListsOutputAll()           { return fOutputAll;             }

  inline virtual void     SetListsErrorList(Bool_t input) { fErrorList = input; }

  inline virtual Double_t GetMassMuon() { return fMassMuon; }

  inline virtual Bool_t   GetGGeneralGeneral()   { return fGGeneralGeneral;   }
  inline virtual Bool_t   GetGGeneralControl()   { return fGGeneralControl;   }

  inline virtual Bool_t   GetMcGeneral()   { return fMcGeneral;   }
  inline virtual Bool_t   GetMcControl()   { return fMcControl;   }

  inline virtual Bool_t   GetTriggerGeneral()              { return fTriggerGeneral;              }
  inline virtual Bool_t   GetTriggerControl()              { return fTriggerControl;              }
  inline virtual UInt_t   GetTriggerTLTEXO96p00p()         { return fTriggerTLTEXO96p00p;         }
  inline virtual UInt_t   GetTriggerTLTEXO03p04p()         { return fTriggerTLTEXO03p04p;         }
  inline virtual UInt_t   GetTriggerTLTEXO05e06e()         { return fTriggerTLTEXO05e06e;         }
  inline virtual UInt_t   GetTriggerTLTEXO06p07p()         { return fTriggerTLTEXO06p07p;         }
  inline virtual UInt_t   GetTriggerTLTHPP96p00p()         { return fTriggerTLTHPP96p00p;         }
  inline virtual UInt_t   GetTriggerTLTHPP03p04p()         { return fTriggerTLTHPP03p04p;         }
  inline virtual UInt_t   GetTriggerTLTHPP05e06e()         { return fTriggerTLTHPP05e06e;         }
  inline virtual UInt_t   GetTriggerTLTHPP06p07p()         { return fTriggerTLTHPP06p07p;         }
  inline virtual UInt_t   GetTriggerTLTHFL96p00p()         { return fTriggerTLTHFL96p00p;         }
  inline virtual UInt_t   GetTriggerTLTHFL99p00p()         { return fTriggerTLTHFL99p00p;         }
  inline virtual UInt_t   GetTriggerTLTHFL03p04p()         { return fTriggerTLTHFL03p04p;         }
  inline virtual UInt_t   GetTriggerTLTHFL05e06e()         { return fTriggerTLTHFL05e06e;         }
  inline virtual UInt_t   GetTriggerTLTHFL06p07p()         { return fTriggerTLTHFL06p07p;         }
  inline virtual UInt_t   GetTriggerTLTDIS96p00p()         { return fTriggerTLTDIS96p00p;         }
  inline virtual UInt_t   GetTriggerTLTDIS03p04p()         { return fTriggerTLTDIS03p04p;         }
  inline virtual UInt_t   GetTriggerTLTDIS05e06e()         { return fTriggerTLTDIS05e06e;         }
  inline virtual UInt_t   GetTriggerTLTDIS06p07p()         { return fTriggerTLTDIS06p07p;         }
  inline virtual UInt_t   GetTriggerTLTMUO96p00p()         { return fTriggerTLTMUO96p00p;         }
  inline virtual UInt_t   GetTriggerTLTMUO03p04p()         { return fTriggerTLTMUO03p04p;         }
  inline virtual UInt_t   GetTriggerTLTMUO05e06e()         { return fTriggerTLTMUO05e06e;         }
  inline virtual UInt_t   GetTriggerTLTMUO06p07p()         { return fTriggerTLTMUO06p07p;         }
  inline virtual UInt_t   GetTriggerTLTSPP03p04p()         { return fTriggerTLTSPP03p04p;         }
  inline virtual UInt_t   GetTriggerTLTSPP05e06e()         { return fTriggerTLTSPP05e06e;         }
  inline virtual UInt_t   GetTriggerTLTSPP06p07p()         { return fTriggerTLTSPP06p07p;         }
  inline virtual Bool_t   GetTriggerEfficiencyCorrection() { return fTriggerEfficiencyCorrection; }
  inline virtual Bool_t   GetTriggerDimuonEfficiencyCorrection() { return fTriggerDimuonEfficiencyCorrection; }
  inline virtual Double_t GetTriggerEffCorr1011()          { return fTriggerEffCorr1011;          }
  inline virtual Double_t GetTriggerEffCorr4254Forward()   { return fTriggerEffCorr4254Forward;   }
  inline virtual Double_t GetTriggerEffCorr4254Barrel()    { return fTriggerEffCorr4254Barrel;    }
  inline virtual Double_t GetTriggerEffCorr4254Rear()      { return fTriggerEffCorr4254Rear;      }

  inline virtual Bool_t   GetSinistraGeneral()   { return fSinistraGeneral;   }
  inline virtual Bool_t   GetSinistraControl()   { return fSinistraControl;   }
  inline virtual Double_t GetSinistraProbCut()   { return fSinistraProbCut;   }
  inline virtual Double_t GetSinistraEnergyCut() { return fSinistraEnergyCut; }
  inline virtual Bool_t   GetSinistraDIS()       { return fSinistraDIS;       }
  inline virtual Bool_t   GetSinistraNoCut()     { return fSinistraNoCut;     }
  inline virtual Double_t GetSinistraYELCut()    { return fSinistraYELCut;    }
  inline virtual Double_t GetSinistraYELHighCut(){ return fSinistraYELHighCut;}
  inline virtual Double_t GetSinistraYELLowCut() { return fSinistraYELLowCut; }
  inline virtual Double_t GetSinistraQ2LowCut()  { return fSinistraQ2LowCut;  }
  inline virtual Bool_t   GetSinistraBoxCut()    { return fSinistraBoxCut;    }
  inline virtual Double_t GetSinistraBoxXCut()   { return fSinistraBoxXCut;   }
  inline virtual Double_t GetSinistraBoxYCut()   { return fSinistraBoxYCut;   }

  inline virtual Bool_t   GetCALGeneral()   { return fCALGeneral;   }
  inline virtual Bool_t   GetCALControl()   { return fCALControl;   }
  inline virtual Double_t GetCALEmpzCut()   { return fCALEmpzCut;   }
  inline virtual Double_t GetCALYJBLOWCut() { return fCALYJBLOWCut; }
  inline virtual Double_t GetCALYJBUPCut()  { return fCALYJBUPCut;  }
  inline virtual Double_t GetCALModeETCut() { return fCALModeETCut; }
  inline virtual Double_t GetCALETCut()     { return fCALETCut;     }
  inline virtual Double_t GetCALTimeCut()   { return fCALTimeCut;   }
  inline virtual Double_t GetCALPtOvEtCut() { return fCALPtOvEtCut; }

  inline virtual Bool_t   GetBACGeneral()        { return fBACGeneral;       }
  inline virtual Bool_t   GetBACControl()        { return fBACControl;       }
  inline virtual Double_t GetBACbac_etotLOWCut() { return fBACbac_etotLOWCut;}
  inline virtual Double_t GetBACbac_etotUPCut()  { return fBACbac_etotUPCut; }
  inline virtual Double_t GetBACnbacmuCut()      { return fBACnbacmuCut;     }

  inline virtual Bool_t   GetZUFOGeneral()    { return fZUFOGeneral;    }
  inline virtual Bool_t   GetZUFOControl()    { return fZUFOControl;    }
  inline virtual Double_t GetZUFOYJBLOWCut()  { return fZUFOYJBLOWCut;  }
  inline virtual Double_t GetZUFOYJBUPCut()   { return fZUFOYJBUPCut;   }
  inline virtual Double_t GetZUFOEMPZUPCut()  { return fZUFOEmpzUpCut;  }
  inline virtual Double_t GetZUFOEMPZLOWCut() { return fZUFOEmpzLowCut; }
  inline virtual Double_t GetZUFOPtHadMaxCut(){ return fZUFOPtHadMaxCut;}
  inline virtual Double_t GetZUFOQ2PrimeLowCut() { return fZUFOQ2PrimeLowCut; }

  inline virtual Bool_t   GetJETGeneral()    { return fJETGeneral;    }
  inline virtual Bool_t   GetJETControl()    { return fJETControl;    }
  inline virtual Bool_t   GetJETBreit()      { return fJETBreit;      }
  inline virtual Int_t    GetJETNCut()       { return fJETNCut;       }
  inline virtual Double_t GetJETPtACut()     { return fJETPtACut;     }
  inline virtual Double_t GetJETPtBCut()     { return fJETPtBCut;     }
  inline virtual Double_t GetJETEtaLowCut()  { return fJETEtaLowCut;  }
  inline virtual Double_t GetJETEtaUpCut()   { return fJETEtaUpCut;   }
  inline virtual Bool_t   GetJETCutOnEt()    { return fJETCutOnEt;    }

  inline virtual Bool_t   GetVertexGeneral()             { return fVertexGeneral;              }
  inline virtual Bool_t   GetVertexControl()             { return fVertexControl;              }
  inline virtual Double_t GetVertexNomXOld()             { return fVertexNomXOld;              }
  inline virtual Double_t GetVertexNomXNew()             { return fVertexNomXNew;              }
  inline virtual Double_t GetVertexNomX()                { return fVertexNomX;                 }
  inline virtual Double_t SetVertexNomX(Double_t input)  { return fVertexNomX = input;         }
  inline virtual Double_t GetVertexNomY()                { return fVertexNomY;                 }
  inline virtual Double_t GetVertexNomZ()                { return fVertexNomZ;                 }
  inline virtual Double_t GetVertexZCut()                { return fVertexZCut;                 }
  inline virtual Bool_t   GetVertexXCut()                { return fVertexXCut;                 }
  inline virtual Bool_t   GetVertexYCut()                { return fVertexYCut;                 }
  inline virtual Double_t GetVertexXYCut()               { return fVertexXYCut;                }
  inline virtual Double_t GetVertexBeamSpotCut()         { return fVertexBeamSpotCut;          }
  inline virtual Double_t GetVertexBeamSpotX()           { return fVertexBeamSpotX;            }
  inline virtual Double_t GetVertexBeamSpotXSigma()      { return fVertexBeamSpotXSigma;       }
  inline virtual Double_t GetVertexBeamSpotY()           { return fVertexBeamSpotY;            }
  inline virtual Double_t GetVertexBeamSpotYSigma()      { return fVertexBeamSpotYSigma;       }
  inline virtual Double_t GetVertexBeamSpotZ()           { return fVertexBeamSpotZ;            }
  inline virtual Double_t GetVertexBeamSpotZSigma()      { return fVertexBeamSpotZSigma;       }
  inline virtual Double_t GetVertexOldBeamSpotX()        { return fVertexOldBeamSpotX;         }
  inline virtual Double_t GetVertexOldBeamSpotXSigma()   { return fVertexOldBeamSpotXSigma;    }
  inline virtual Double_t GetVertexOldBeamSpotY()        { return fVertexOldBeamSpotY;         }
  inline virtual Double_t GetVertexOldBeamSpotYSigma()   { return fVertexOldBeamSpotYSigma;    }
  inline virtual Double_t GetVertexOldBeamSpotZ()        { return fVertexOldBeamSpotZ;         }
  inline virtual Double_t GetVertexOldBeamSpotZSigma()   { return fVertexOldBeamSpotZSigma;    }
  inline virtual Double_t GetVertexNewBeamSpotX()        { return fVertexNewBeamSpotX;         }
  inline virtual Double_t GetVertexNewBeamSpotXSigma()   { return fVertexNewBeamSpotXSigma;    }
  inline virtual Double_t GetVertexNewBeamSpotY()        { return fVertexNewBeamSpotY;         }
  inline virtual Double_t GetVertexNewBeamSpotYSigma()   { return fVertexNewBeamSpotYSigma;    }
  inline virtual Double_t GetVertexNewBeamSpotZ()        { return fVertexNewBeamSpotZ;         }
  inline virtual Double_t GetVertexNewBeamSpotZSigma()   { return fVertexNewBeamSpotZSigma;    }
  inline virtual Bool_t   GetVertexUseAllRuns()          { return fVertexUseAllRuns;    }

  inline virtual void     SetVertexBeamSpotX(Double_t input)           { fVertexBeamSpotX = input;            }
  inline virtual void     SetVertexBeamSpotXSigma(Double_t input)      { fVertexBeamSpotXSigma = input;       }
  inline virtual void     SetVertexBeamSpotY(Double_t input)           { fVertexBeamSpotY = input;            }
  inline virtual void     SetVertexBeamSpotYSigma(Double_t input)      { fVertexBeamSpotYSigma = input;       }
  inline virtual void     SetVertexBeamSpotZ(Double_t input)           { fVertexBeamSpotZ = input;            }
  inline virtual void     SetVertexBeamSpotZSigma(Double_t input)      { fVertexBeamSpotZSigma = input;       }

  inline virtual Bool_t    GetMUONGeneral()                       { return fMUONGeneral;                       }
  inline virtual Bool_t    GetMUONControl()                       { return fMUONControl;                       }
  inline virtual Int_t     GetMUONNCut()                          { return fMUONNCut;                          }
  inline virtual Bool_t    GetMUONFillAll()                       { return fMUONFillAll;                       }
  inline virtual Double_t  GetMUONBremProb()                      { return fMUONBremProb;                      }
  inline virtual Int_t     GetMUONBremChamberFlag()               { return fMUONBremChamberFlag;               }
  inline virtual Double_t  GetMUONMPMProb()                       { return fMUONMPMProb;                       }
  inline virtual Double_t  GetMUONMUBACBacFlag()                  { return fMUONMUBACBacFlag;                  }
  inline virtual Int_t     GetMUONChamberFlagCut()                { return fMUONChamberFlagCut;                }
  inline virtual Double_t  GetMUONMfpro()                         { return fMUONMfpro;                         }
  inline virtual Int_t     GetMUONMfndf()                         { return fMUONMfndf;                         }
  inline virtual Int_t     GetMUONMfz()                           { return fMUONMfz;                           }
  inline virtual Int_t     GetMUONBACFQuality()                   { return fMUONBACFQuality;                   }
  inline virtual Int_t     GetMUONVcidLowCut()                    { return fMUONVcidLowCut;                    }
  inline virtual Int_t     GetMUONVcidUpCut()                     { return fMUONVcidUpCut;                     }
  inline virtual Bool_t    GetMUONModifyQuality()                 { return fMUONModifyQuality;                 }
  inline virtual Bool_t    GetMuqualServicePack1()                { return fMuqualServicePack1;                }
  inline virtual Bool_t    GetMUONEfficiencyCorrection()          { return fMUONEfficiencyCorrection;          }
  inline virtual Bool_t    GetMuqualBasedEffCorr()                { return fMuqualBasedEffCorr;                }
  inline virtual Bool_t    GetMUONReadEfficiencyFiles()           { return fMUONReadEfficiencyFiles;           }
  inline virtual TString   GetMUONEfficiencyFile()                { return fMUONEfficiencyFile;                }
  inline virtual Int_t     GetMUONEfficiencyMPMATCHPtNBins()      { return fMUONEfficiencyMPMATCHPtNBins;      }
  inline virtual Double_t* GetMUONEfficiencyMPMATCHPtBins()       { return fMUONEfficiencyMPMATCHPtBins;       }
  inline virtual Int_t     GetMUONEfficiencyBREMATPtNBins()       { return fMUONEfficiencyBREMATPtNBins;       }
  inline virtual Double_t* GetMUONEfficiencyBREMATPtBins()        { return fMUONEfficiencyBREMATPtBins;        }
  inline virtual Int_t     GetMUONEfficiencyMUBACPtNBins()        { return fMUONEfficiencyMUBACPtNBins;        }
  inline virtual Double_t* GetMUONEfficiencyMUBACPtBins()         { return fMUONEfficiencyMUBACPtBins;         }
  inline virtual TString   GetMUONTIGHTEfficiencyFile()           { return fMUONTIGHTEfficiencyFile;           }
  inline virtual Int_t     GetMUONTIGHTEfficiencyMPMATCHPtNBins() { return fMUONTIGHTEfficiencyMPMATCHPtNBins; }
  inline virtual Double_t* GetMUONTIGHTEfficiencyMPMATCHPtBins()  { return fMUONTIGHTEfficiencyMPMATCHPtBins;  }
  inline virtual Int_t     GetMUONTIGHTEfficiencyBREMATPtNBins()  { return fMUONTIGHTEfficiencyBREMATPtNBins;  }
  inline virtual Double_t* GetMUONTIGHTEfficiencyBREMATPtBins()   { return fMUONTIGHTEfficiencyBREMATPtBins;   }
  inline virtual Int_t     GetMUONTIGHTEfficiencyMUBACPtNBins()   { return fMUONTIGHTEfficiencyMUBACPtNBins;   }
  inline virtual Double_t* GetMUONTIGHTEfficiencyMUBACPtBins()    { return fMUONTIGHTEfficiencyMUBACPtBins;    }
  inline virtual Double_t  GetMUONEfficiencyCutOff()              { return fMUONEfficiencyCutOff;              }
  inline virtual Bool_t    GetMUONCalculateMuonIsolation()        { return fMUONCalculateMuonIsolation;        }
  inline virtual Double_t  GetMUONMinIsolation10Veto()            { return fMUONMinIsolation10Veto;            }
  inline virtual Bool_t    GetMUONExcludeMamma()                  { return fMUONExcludeMamma;                  }

  inline virtual Double_t GetFMUONEtaLow()           { return fFMUONEtaLow;           }
  inline virtual Double_t GetFMUONEtaUp()            { return fFMUONEtaUp;            }
  inline virtual Double_t GetFMUONP()                { return fFMUONP;                }
  inline virtual Double_t GetFMUONPt()               { return fFMUONPt;               }
  inline virtual Int_t    GetFMUONQualCut1()         { return fFMUONQualCut1;         }
  inline virtual Double_t GetFMUONPTCut1()           { return fFMUONPTCut1;           }
  inline virtual Int_t    GetFMUONQualCut2()         { return fFMUONQualCut2;         }
  inline virtual Double_t GetFMUONPTCut2()           { return fFMUONPTCut2;           }
  inline virtual Int_t    GetFMUONFinder()           { return fFMUONFinder;           }
  inline virtual Double_t GetFMUONEfficiency99p00p() { return fFMUONEfficiency99p00p; }
  inline virtual Double_t GetFMUONEfficiency98e99e() { return fFMUONEfficiency98e99e; }
  inline virtual Double_t GetFMUONEfficiency96p97p() { return fFMUONEfficiency96p97p; }
  inline virtual Double_t GetFMUONEfficiency03p04p() { return fFMUONEfficiency03p04p; }
  inline virtual Double_t GetFMUONEfficiency05e06e() { return fFMUONEfficiency05e06e; }
  inline virtual Double_t GetFMUONEfficiency06p07p() { return fFMUONEfficiency06p07p; }
  inline virtual Bool_t   GetFMUONOnlyVertexFitted() { return fFMUONOnlyVertexFitted; }

  inline virtual Double_t GetBMUONEtaLow()           { return fBMUONEtaLow;           }
  inline virtual Double_t GetBMUONEtaUp()            { return fBMUONEtaUp;            }
  inline virtual Double_t GetBMUONP()                { return fBMUONP;                }
  inline virtual Double_t GetBMUONPt()               { return fBMUONPt;               }
  inline virtual Int_t    GetBMUONQualCut1()         { return fBMUONQualCut1;         }
  inline virtual Double_t GetBMUONPTCut1()           { return fBMUONPTCut1;           }
  inline virtual Int_t    GetBMUONQualCut2()         { return fBMUONQualCut2;         }
  inline virtual Double_t GetBMUONPTCut2()           { return fBMUONPTCut2;           }
  inline virtual Int_t    GetBMUONFinder()           { return fBMUONFinder;           }
  inline virtual Double_t GetBMUONEfficiency96p97p() { return fBMUONEfficiency96p97p; }
  inline virtual Double_t GetBMUONEfficiency98e99e() { return fBMUONEfficiency98e99e; }
  inline virtual Double_t GetBMUONEfficiency99p00p() { return fBMUONEfficiency99p00p; }
  inline virtual Double_t GetBMUONEfficiency03p04p() { return fBMUONEfficiency03p04p; }
  inline virtual Double_t GetBMUONEfficiency05e06e() { return fBMUONEfficiency05e06e; }
  inline virtual Double_t GetBMUONEfficiency06p07p() { return fBMUONEfficiency06p07p; }
  inline virtual Bool_t   GetBMUONOnlyVertexFitted() { return fBMUONOnlyVertexFitted; }

  inline virtual Double_t GetRMUONEtaLow()           { return fRMUONEtaLow;           }
  inline virtual Double_t GetRMUONEtaUp()            { return fRMUONEtaUp;            }
  inline virtual Double_t GetRMUONP()                { return fRMUONP;                }
  inline virtual Double_t GetRMUONPt()               { return fRMUONPt;               }
  inline virtual Int_t    GetRMUONQualCut1()         { return fRMUONQualCut1;         }
  inline virtual Double_t GetRMUONPTCut1()           { return fRMUONPTCut1;           }
  inline virtual Int_t    GetRMUONQualCut2()         { return fRMUONQualCut2;         }
  inline virtual Double_t GetRMUONPTCut2()           { return fRMUONPTCut2;           }
  inline virtual Int_t    GetRMUONFinder()           { return fRMUONFinder;           }
  inline virtual Double_t GetRMUONEfficiency96p97p() { return fRMUONEfficiency96p97p; }
  inline virtual Double_t GetRMUONEfficiency98e99e() { return fRMUONEfficiency98e99e; }
  inline virtual Double_t GetRMUONEfficiency99p00p() { return fRMUONEfficiency99p00p; }
  inline virtual Double_t GetRMUONEfficiency03p04p() { return fRMUONEfficiency03p04p; }
  inline virtual Double_t GetRMUONEfficiency05e06e() { return fRMUONEfficiency05e06e; }
  inline virtual Double_t GetRMUONEfficiency06p07p() { return fRMUONEfficiency06p07p; }
  inline virtual Bool_t   GetRMUONOnlyVertexFitted() { return fRMUONOnlyVertexFitted; }

  inline virtual Bool_t   GetTRACKSGeneral()            { return fTRACKSGeneral;            }
  inline virtual Bool_t   GetTRACKSControl()            { return fTRACKSControl;            }
  inline virtual Int_t    GetTRACKSMultiplicity()       { return fTRACKSMultiplicity;       }
  inline virtual Int_t    GetTRACKSVertexCut()          { return fTRACKSVertexCut;          }
  inline virtual Int_t    GetTRACKSMinVertexCut()       { return fTRACKSMinVertexCut;       }
  inline virtual Double_t GetTRACKSTotalOvVertexCut()   { return fTRACKSTotalOvVertexCut;   }
  inline virtual Int_t    GetTRACKSUsedSuperLayersCut() { return fTRACKSUsedSuperLayersCut; }
  inline virtual Int_t    GetTRACKSUsedHitsCut()        { return fTRACKSUsedHitsCut;        }
  inline virtual Int_t    GetTRACKSUsedStereoHitsCut()  { return fTRACKSUsedStereoHitsCut;  }
  inline virtual Double_t GetTRACKSZHCut()              { return fTRACKSZHCut;              }
  inline virtual Int_t    GetTRACKSMVDHitsCut()         { return fTRACKSMVDHitsCut;         }
  inline virtual UInt_t   GetTRACKSType()               { return fTRACKSType;               }


  inline virtual Bool_t   GetMJMATCHGeneral()              { return fMJMATCHGeneral;               }
  inline virtual Bool_t   GetMJMATCHControl()              { return fMJMATCHControl;               }
  inline virtual Double_t GetMJMATCHJetPtCut()             { return fMJMATCHJetPtCut;              }
  inline virtual Double_t GetMJMATCHMuMinusJetPtCut()      { return fMJMATCHMuMinusJetPtCut;       }
  inline virtual Int_t    GetMJMATCHNMatchs()              { return fMJMATCHNMatchs;               }
  inline virtual Double_t GetMJMATCHPtRelLow()             { return fMJMATCHPtRelLow;              }
  inline virtual Double_t GetMJMATCHPtRelHigh()            { return fMJMATCHPtRelHigh;             }
  inline virtual Bool_t   GetMJMATCHTakeAllGood()          { return fMJMATCHTakeAllGood;           }
  inline virtual Bool_t   GetMJMATCHPtRelCorrection()      { return fMJMATCHPtRelCorrection;       }
  inline virtual TString  GetMJMATCHPtRelCorrFilename()    { return fMJMATCHPtRelCorrFilename;     }
  inline virtual Double_t GetMJMATCHPtRelCorrCMCWeight()   { return fMJMATCHPtRelCorrCMCWeight;    }
  inline virtual Double_t GetMJMATCHPtRelCorrLFMCWeight()  { return fMJMATCHPtRelCorrLFMCWeight;   }

  inline virtual Bool_t   GetTJMATCHGeneral()              { return fTJMATCHGeneral;               }
  inline virtual Bool_t   GetTJMATCHControl()              { return fTJMATCHControl;               }
  inline virtual Int_t    GetTJMATCHNMatchs()              { return fTJMATCHNMatchs;               }
  inline virtual Double_t GetTJMATCHJetPtCut()             { return fTJMATCHJetPtCut;              }
  inline virtual Double_t GetTJMATCHTrackMinusJetPtCut()   { return fTJMATCHTrackMinusJetPtCut;    }
  inline virtual Double_t GetTJMATCHAssociationCone()      { return fTJMATCHAssociationCone;       }

  inline virtual Bool_t   GetDIMUONGeneral()               { return fDIMUONGeneral;                }
  inline virtual Bool_t   GetDIMUONControl()               { return fDIMUONControl;                }
  inline virtual Double_t GetDIMUONInvMassLowCut()         { return fDIMUONInvMassLowCut;          }
  inline virtual Double_t GetDIMUONInvMassHighCut()        { return fDIMUONInvMassHighCut;         } 
  inline virtual Double_t GetDIMUONSqSumIsolationCut()     { return fDIMUONSqSumIsolationCut;      }
  inline virtual Double_t GetDIMUONSqSumIsolationPeakCut() { return fDIMUONSqSumIsolationPeakCut;  }
  inline virtual Double_t GetDIMUONSqSumIsolationContCut() { return fDIMUONSqSumIsolationContCut;  }
  inline virtual Double_t GetDIMUONDeltaRCut()             { return fDIMUONDeltaRCut;              }
  inline virtual Double_t GetDIMUONDeltaPhiCut()           { return fDIMUONDeltaPhiCut;            }
  inline virtual Double_t GetDIMUONDeltaThetaCut()         { return fDIMUONDeltaThetaCut;          }
  inline virtual Double_t GetDIMUONDeltaEtaCut()           { return fDIMUONDeltaEtaCut;            }
  inline virtual Double_t GetDIMUONPtAsymetryCut()         { return fDIMUONPtAsymetryCut;          }
  inline virtual Double_t GetDIMUONEtFractionHigh1Cut()    { return fDIMUONEtFractionHigh1Cut;     }
  inline virtual Double_t GetDIMUONEtFractionHigh2Cut()    { return fDIMUONEtFractionHigh2Cut;     }
  inline virtual Double_t GetDIMUONEtFractionLowCut()      { return fDIMUONEtFractionLowCut;       }
  inline virtual Double_t GetDIMUONNDimuons()              { return fDIMUONNDimuons;               }
  inline virtual Bool_t   GetDIMUONDifCharge()             { return fDIMUONDifCharge;              }
  inline virtual Bool_t   GetDIMUONCharmMCJpsi()           { return fDIMUONCharmMCJpsi;            }
  inline virtual Bool_t   GetDIMUONCharmMCPsiprime()       { return fDIMUONCharmMCPsiprime;        }

  inline virtual Bool_t   GetTRIMUONGeneral()              { return fTRIMUONGeneral;               }
  inline virtual Bool_t   GetTRIMUONControl()              { return fTRIMUONControl;               }
  inline virtual Double_t GetTRIMUONInvMassLowCut()        { return fTRIMUONInvMassLowCut;         }
  inline virtual Double_t GetTRIMUONInvMassHighCut()       { return fTRIMUONInvMassHighCut;        }
  inline virtual Double_t GetTRIMUONSqSumIsolationCut()    { return fTRIMUONSqSumIsolationCut;     }
  inline virtual Double_t GetTRIMUONSqSumIsolationPeakCut(){ return fTRIMUONSqSumIsolationPeakCut; }
  inline virtual Double_t GetTRIMUONSqSumIsolationContCut(){ return fTRIMUONSqSumIsolationContCut; }
  inline virtual Double_t GetTRIMUONDeltaRCut()            { return fTRIMUONDeltaRCut;             }
  inline virtual Double_t GetTRIMUONDeltaPhiCut()          { return fTRIMUONDeltaPhiCut;           }
  inline virtual Double_t GetTRIMUONDeltaThetaCut()        { return fTRIMUONDeltaThetaCut;         }
  inline virtual Double_t GetTRIMUONDeltaEtaCut()          { return fTRIMUONDeltaEtaCut;           }
  inline virtual Double_t GetTRIMUONPtAsymetryCut()        { return fTRIMUONPtAsymetryCut;         }
  inline virtual Double_t GetTRIMUONEtFractionHigh1Cut()   { return fTRIMUONEtFractionHigh1Cut;    }
  inline virtual Double_t GetTRIMUONEtFractionHigh2Cut()   { return fTRIMUONEtFractionHigh2Cut;    }
  inline virtual Double_t GetTRIMUONEtFractionLowCut()     { return fTRIMUONEtFractionLowCut;      }
  inline virtual Double_t GetTRIMUONNTrimuons()            { return fTRIMUONNTrimuons;             }
  inline virtual Bool_t   GetTRIMUONDifCharge()            { return fTRIMUONDifCharge;             }
  inline virtual Bool_t   GetTRIMUONCharmMCJpsi()          { return fTRIMUONCharmMCJpsi;           }
  inline virtual Bool_t   GetTRIMUONCharmMCPsiprime()      { return fTRIMUONCharmMCPsiprime;       }

 
  inline virtual Bool_t   GetMVDActivate()                 { return fMVDActivate;                  }
  inline virtual Bool_t   GetMVDGeneral()                  { return fMVDGeneral;                   }
  inline virtual Bool_t   GetMVDControl()                  { return fMVDControl;                   }

  inline virtual Bool_t GetPicturesGIF()                   { return fPICTURES_GIF;                 }
  inline virtual Bool_t GetPicturesEPS()                   { return fPICTURES_EPS;                 }
  inline virtual Bool_t GetPicturesPS()                    { return fPICTURES_PS;                  }
  inline virtual Bool_t GetPicturesJPG()                   { return fPICTURES_JPG;                 }
  inline virtual Bool_t GetPicturesCompdisonly()           { return fPICTUREScomp_disonly;         }
  inline virtual Bool_t GetPicturesCompphponly()           { return fPICTUREScomp_phponly;         }
  inline virtual Bool_t GetPicturesCompptrel()             { return fPICTUREScomp_ptrel;           }      
  inline virtual Bool_t GetPicturesCompmuon()              { return fPICTUREScomp_muon;            }    
  inline virtual Bool_t GetPicturesCompjet()               { return fPICTUREScomp_jet;             }   
  inline virtual Bool_t GetPicturesCompmjmatch()           { return fPICTUREScomp_mjmatch;         }   
  inline virtual Bool_t GetPicturesComptjmatch()           { return fPICTUREScomp_tjmatch;         }   
  inline virtual Bool_t GetPicturesCompcal()               { return fPICTUREScomp_cal;             }
  inline virtual Bool_t GetPicturesComptracks()            { return fPICTUREScomp_tracks;          }    
  inline virtual Bool_t GetPicturesComptrigger()           { return fPICTUREScomp_trigger;         } 
  inline virtual Bool_t GetPicturesCompzufo()              { return fPICTUREScomp_zufo;            }
  inline virtual Bool_t GetPicturesCompsinistra()          { return fPICTUREScomp_sinistra;        }
  						     		                         
  inline virtual Bool_t GetPicturesONEDdimuon()            { return fPICTURESONED_dimuon;          }
  inline virtual Bool_t GetPicturesONEDtrack()             { return fPICTURESONED_track;           } 
  inline virtual Bool_t GetPicturesONEDmuon()              { return fPICTURESONED_muon;            }  
  		     			     		                         
  inline virtual Bool_t GetPicturesONEDMCdimuon()          { return fPICTURESONEDMC_dimuon;        }
  inline virtual Bool_t GetPicturesONEDMCmc()              { return fPICTURESONEDMC_mc;            }
  inline virtual Bool_t GetPicturesONEDMCtrack()           { return fPICTURESONEDMC_track;         } 
  inline virtual Bool_t GetPicturesONEDMCmuon()            { return fPICTURESONEDMC_muon;          }
  		     			     		                         
  inline virtual Bool_t GetPicturesTWODmjmatch()           { return fPICTURESTWOD_mjmatch;         } 
  inline virtual Bool_t GetPicturesTWODMCcal()             { return fPICTURESTWODMC_cal;           }
  inline virtual Bool_t GetPicturesTWODMCzufo()            { return fPICTURESTWODMC_zufo;          }  
  inline virtual Bool_t GetPicturesTWODMCmc()              { return fPICTURESTWODMC_mc;            } 
  inline virtual Bool_t GetPicturesTWODMCmuon()            { return fPICTURESTWODMC_muon;          }   
  inline virtual Bool_t GetPicturesTWODMCmjmatch()         { return fPICTURESTWODMC_mjmatch;       } 
  		     			     		                         
  inline virtual Bool_t GetPicturesTWODMCzoomedmc()        { return fPICTURESTWODMCzoomed_mc;      }
  		     			     		                         
  inline virtual Bool_t GetPicturesEfficiencyFull()        { return fPICTURESEfficiencyFull;       }


  inline virtual Bool_t   GetLogActivate()            { return fLogActivate;        }
  inline virtual Int_t    GetLogTermNumber()          { return fLogTermNumber;      }
  inline virtual TString* GetLogTerms()               { return fLogTerms;           }
  inline virtual Int_t    GetLogCountNumber()         { return fLogCountNumber;     }
  inline virtual TString* GetLogCountTerms()          { return fLogCountTerms;      }

  ClassDef(GCards,0) // Card file variable class
};

R__EXTERN GCards *gCards;

#endif
