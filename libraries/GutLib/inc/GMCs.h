//
// GMCs.h
//
// $Author: meyer $
// $Date: 2008/06/10 07:14:51 $
// $Revision: 1.34 $
//

#ifndef GUT_GMCs
#define GUT_GMCs

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GMC;
class GMCVertex;
class GDIMuon;
class GMuon;
class GMuons;
class GJet;

class GMCs : public GPhysObj {

 private:

  // variables
  Int_t           fIndex1;                                      // index of highest jet, only used for massive b-hadron jets
  Int_t           fIndex2;                                      // index of second highest jet, only used for massive b-hadron jets
  Double_t        fXGammaJets;                                  // x_gamma^jets
  Double_t        fXGamma;                                      // x_gamma^jets in second definition
  Double_t        fXGammaJets_zufo;                             // x_gamma^jets with zufo properties
  Double_t        fMJets;                                       // dijet invariant mass
  Double_t        fDPhiJets;                                    // dphi from jets
  Double_t        fDRJets;                                      // dphi from jets
  Double_t        fPtJets;                                      // p_T of hijet system
  Double_t        fCosThetaStarJets;                            // cos ( theta* )
  Double_t        fEtaJets;                                     // average eta of jets

  Int_t           fPartIndex1;                                      // index of highest jet, only used for massive b-hadron jets parton level
  Int_t           fPartIndex2;                                      // index of second highest jet, only used for massive b-hadron jets parton level
  Double_t        fPartXGammaJets;                                  // x_gamma^jets parton level
  Double_t        fPartXGamma;                                      // x_gamma^jets in second definition parton level
  Double_t        fPartXGammaJets_zufo;                             // x_gamma^jets with zufo properties parton level
  Double_t        fPartMJets;                                       // dijet invariant mass parton level
  Double_t        fPartDPhiJets;                                    // dphi from jets parton level
  Double_t        fPartDRJets;                                      // dphi from jets parton level
  Double_t        fPartPtJets;                                      // p_T of hijet system parton level
  Double_t        fPartCosThetaStarJets;                            // cos ( theta* ) parton level
  Double_t        fPartEtaJets;                                  // average eta of parton level jets
  TClonesArray   *fMCs;                                         // mc particle array
  Int_t           fNMCs;                                        // counter for mc particle clonesarray
  TClonesArray   *fMCMuons;                                     // fmckin particle array
  Int_t           fNMCMuons;                                    // counter for fmckin particle clonesarray
  TClonesArray   *fMCDIMuons;                                   // fmckin particle array
  Int_t           fNMCDIMuons;                                  // counter for fmckin particle clonesarray
/*   TClonesArray   *fMCDIMuons2;                                   // fmckin particle array */
/*   Int_t           fNMCDIMuons2;                                  // counter for fmckin particle clonesarray */
  TClonesArray   *fMCVertices;                                  // mc vertex array
  Int_t           fNMCVertices;                                 // counter for mc vertex clonesarray

  TClonesArray   *fMCHJets;                                     // mc hadron jets array
  Int_t           fNMCHJets;                                    // counter for mc hadron jets clonesarray
  TClonesArray   *fMCHMJets;                                    // massive mc hadron jets array
  Int_t           fNMCHMJets;                                   // counter for massive mc hadron jets clonesarray
  TClonesArray   *fMCHBJets;                                    // mc hadron jets with stable B mesons array
  Int_t           fNMCHBJets;                                   // counter for mc hadron jets with stable B mesons clonesarray
  TClonesArray   *fMCHBMJets;                                   // massive mc hadron jets with stable B mesons array
  Int_t           fNMCHBMJets;                                  // counter for massive mc hadron jets with stable B mesons clonesarray
  TClonesArray   *fMCPJets;                                     // mc hadron jets array
  Int_t           fNMCPJets;                                    // counter for mc hadron jets clonesarray
  TClonesArray   *fMCPMJets;                                    // massive mc parton jets array
  Int_t           fNMCPMJets;                                   // counter for massive mc parton jets clonesarray

  // jet cut flags
  Bool_t          fMCHJetPtACut;                                // cut on highest pt MC hadron jet
  Bool_t          fMCHJetPtBCut;                                // cut on second highest pt MC hadron jet
  Bool_t          fMCHMJetPtACut;                               // cut on highest pt massive MC hadron jet
  Bool_t          fMCHMJetPtBCut;                               // cut on second highest pt massive MC hadron jet
  Bool_t          fMCHBJetPtACut;                               // cut on highest pt MC hadron jet with stable B mesons
  Bool_t          fMCHBJetPtBCut;                               // cut on second highest pt MC hadron jet with stable B mesons
  Bool_t          fMCHBMJetPtACut;                              // cut on highest pt massive MC hadron jet with stable B mesons
  Bool_t          fMCHBMJetPtBCut;                              // cut on second highest pt massive MC hadron jet with stable B mesons
  Bool_t          fMCPJetPtACut;                                // cut on highest pt MC parton jet
  Bool_t          fMCPJetPtBCut;                                // cut on second highest pt MC parton jet
  Bool_t          fMCPMJetPtACut;                               // cut on highest pt massive MC parton jet
  Bool_t          fMCPMJetPtBCut;                               // cut on second highest pt massive MC parton jet

  Int_t           fOwnFMCKINID;                                 // own fmckin id for particles without id

  Bool_t          fHeavyFlavours;                               // event contains heavy flavour particles

  Bool_t          fQ2Cut;                                       // cut on true Q2 for histograms
  Bool_t          fQ2LowCut;                                    // low cut on true Q2 for histograms
  Bool_t          fQ2SelectionCut;                              // cut for selection on true Q2
  Bool_t          fYCut;                                        // cut in true y
  Bool_t          fMuonCuts;                                    // at least one true muon which fulfills muon kin cuts and coming from b quark
  Bool_t          fMCDIMuonCuts;                                // at least one true mcdimuon

  // general histograms
  TH1D           *fGeneralQ2_uncut;                             // uncut MC Q2
  TH1D           *fGeneralY_uncut;                              // uncut MC Y
  TH1D           *fGeneralX_uncut;                              // uncut MC X

  TH1D           *fGeneralQ2;                                   // MC Q2
  TH1D           *fGeneralQ2_1;                                 // MC Q2 fulfilling trigger requirement
  TH1D           *fGeneralQ2_2;                                 // MC Q2 fulfilling trigger and sinistra requirement
  TH1D           *fGeneralQ2_3;                                 // MC Q2 fulfilling trigger, sinistra and zufo requirement
  TH1D           *fGeneralY;                                    // MC Y
  TH1D           *fGeneralX;                                    // MC X

  TH1D           *fGeneralCrossTotalTrue;                       // true plot of total cross
  TH1D           *fGeneralCrossTotalTrueNRec;                   // true and rec plot of total cross
  TH1D           *fGeneralCrossTotalAssociatedTrue;             // true plot of total cross for muons ass. to a jet
  TH1D           *fGeneralCrossTotalAssociatedTrueNRec;
  TH1D           *fGeneralCrossTotalEventTrue;                  // true plot of total cross eventwise filled
  TH1D           *fGeneralCrossTotalEventTrueNRec;

  TH1D           *fGeneralCrossMuonRegionsTrue;                 // true plot of chosen muons region
  TH1D           *fGeneralCrossMuonRegionsTrueNRec;             // true and rec plot of chosen muons region
  TH1D           *fGeneralCrossMuonFinderTrue;
  TH1D           *fGeneralCrossMuonFinderTrueNRec;             // filled like muon region plot 0-4 barrel,5-9 rear 10-14 forward


  TH1D           *fGeneralCrossMuonPtTrue;                      // true plot of chosen muons pt
  TH1D           *fGeneralCrossMuonPtTrueNRec;                  // true and rec plot of chosen muons pt

  TH1D           *fGeneralCrossMuonEtaTrue;                     // true plot of chosen muons eta
  TH1D           *fGeneralCrossMuonEtaTrueNRec;                 // true and rec plot of chosen muons eta

  TH1D           *fGeneralCrossMuonPtFineTrue;                  // true plot of fine chosen muons pt
  TH1D           *fGeneralCrossMuonPtFineTrueNRec;              // true and rec plot of fine chosen muons pt

  TH1D           *fGeneralCrossMuonEtaFineTrue;                 // true plot of fine chosen muons eta
  TH1D           *fGeneralCrossMuonEtaFineTrueNRec;             // true and rec plot of fine chosen muons eta

  TH1D           *fGeneralCrossMuonPtMassimoTrue;               // true plot of chosen muons pt in massimo's binning
  TH1D           *fGeneralCrossMuonPtMassimoTrueNRec;           // true and rec plot of chosen muons pt in massimo's binning

  TH1D           *fGeneralCrossMuonEtaMassimoTrue;              // true plot of chosen muons eta in massimo's binning
  TH1D           *fGeneralCrossMuonEtaMassimoTrueNRec;          // true and rec plot of chosen muons eta in massimo's binning

  TH1D           *fGeneralCrossMuonRegionsNoJetTrue;                 // true plot of chosen muons region
  TH1D           *fGeneralCrossMuonRegionsNoJetTrueNRec;             // true and rec plot of chosen muons region

  TH1D           *fGeneralCrossMuonPtNoJetTrue;                      // true plot of chosen muons pt
  TH1D           *fGeneralCrossMuonPtNoJetTrueNRec;                  // true and rec plot of chosen muons pt

  TH1D           *fGeneralCrossMuonEtaNoJetTrue;                     // true plot of chosen muons eta
  TH1D           *fGeneralCrossMuonEtaNoJetTrueNRec;                 // true and rec plot of chosen muons eta

  TH1D           *fGeneralCrossMuonPtFineNoJetTrue;                  // true plot of fine chosen muons pt
  TH1D           *fGeneralCrossMuonPtFineNoJetTrueNRec;              // true and rec plot of fine chosen muons pt

  TH1D           *fGeneralCrossMuonEtaFineNoJetTrue;                 // true plot of fine chosen muons eta
  TH1D           *fGeneralCrossMuonEtaFineNoJetTrueNRec;             // true and rec plot of fine chosen muons eta

  TH1D           *fGeneralCrossMuonPtMassimoNoJetTrue;               // true plot of chosen muons pt in massimo's binning
  TH1D           *fGeneralCrossMuonPtMassimoNoJetTrueNRec;           // true and rec plot of chosen muons pt in massimo's binning

  TH1D           *fGeneralCrossMuonEtaMassimoNoJetTrue;              // true plot of chosen muons eta in massimo's binning
  TH1D           *fGeneralCrossMuonEtaMassimoNoJetTrueNRec;          // true and rec plot of chosen muons eta in massimo's binning

  TH1D           *fGeneralCrossMuonJetPtTrue;                   // true plot of chosen muon jets pt
  TH1D           *fGeneralCrossMuonJetPtTrueNRec;               // true and rec plot of chosen muon jets pt

  TH1D           *fGeneralCrossMuonJetEtaTrue;                  // true plot of chosen muon jets eta
  TH1D           *fGeneralCrossMuonJetEtaTrueNRec;              // true and rec plot of chosen muon jets eta

  TH1D           *fGeneralCrossMuonJetPtFineTrue;               // true plot of fine chosen muon jets pt
  TH1D           *fGeneralCrossMuonJetPtFineTrueNRec;           // true and rec plot of fine chosen muon jets pt

  TH1D           *fGeneralCrossMuonJetEtaFineTrue;              // true plot of fine chosen muon jets eta
  TH1D           *fGeneralCrossMuonJetEtaFineTrueNRec;          // true and rec plot of fine chosen muon jets eta

  TH1D           *fGeneralCrossJetXGammaTrue;                   // true x_gamma_zufo for cross section
  TH1D           *fGeneralCrossJetXGammaTrueNRec;               // x_gamma_zufo true and rec for cross section

  TH1D           *fGeneralCrossJetXGammaFineTrue;               // true fine x_gamma_zufo for cross section
  TH1D           *fGeneralCrossJetXGammaFineTrueNRec;           // fine x_gamma_zufo true and rec for cross section

  TH1D           *fGeneralCrossJetMJetsTrue;                    // true jet dijet invariant mass for cross section
  TH1D           *fGeneralCrossJetMJetsTrueNRec;                // jet dijet invariant mass true and rec for cross section
  TH1D           *fGeneralCrossJetMJetsLowTrue;                 // true jet dijet invariant mass for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetMJetsLowTrueNRec;             // jet dijet invariant mass true and rec for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetMJetsHighTrue;                // true jet dijet invariant mass for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetMJetsHighTrueNRec;            // jet dijet invariant mass true and rec for cross section for x_gamma >= 0.75

  TH1D           *fGeneralCrossJetDPhiJetsTrue;                 // true jet dijet dphi for cross section
  TH1D           *fGeneralCrossJetDPhiJetsTrueNRec;             // jet dijet dphi true and rec for cross section
  TH1D           *fGeneralCrossJetDPhiJetsLowTrue;              // true jet dijet dphi for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetDPhiJetsLowTrueNRec;          // jet dijet dphi true and rec for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetDPhiJetsHighTrue;             // true jet dijet dphi for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetDPhiJetsHighTrueNRec;         // jet dijet dphi true and rec for cross section for x_gamma >= 0.75

  TH1D           *fGeneralCrossJetDRJetsTrue;                   // true jet dijet dr for cross section
  TH1D           *fGeneralCrossJetDRJetsTrueNRec;               // jet dijet dr true and rec for cross section
  TH1D           *fGeneralCrossJetDRJetsLowTrue;                // true jet dijet dr for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetDRJetsLowTrueNRec;            // jet dijet dr true and rec for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetDRJetsHighTrue;               // true jet dijet dr for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetDRJetsHighTrueNRec;           // jet dijet dr true and rec for cross section for x_gamma >= 0.75

  TH1D           *fGeneralCrossJetPtJetsTrue;                   // true jet dijet p_T for cross section
  TH1D           *fGeneralCrossJetPtJetsTrueNRec;               // jet dijet p_T true and rec for cross section
  TH1D           *fGeneralCrossJetPtJetsLowTrue;                // true jet dijet p_T for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetPtJetsLowTrueNRec;            // jet dijet p_T true and rec for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetPtJetsHighTrue;               // true jet dijet p_T for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetPtJetsHighTrueNRec;           // jet dijet p_T true and rec for cross section for x_gamma >= 0.75

  TH1D           *fGeneralCrossJetCosThetaStarJetsTrue;         // true cos(theta*) for cross section
  TH1D           *fGeneralCrossJetCosThetaStarJetsTrueNRec;     // jet cos(theta*) true and rec for cross section
  TH1D           *fGeneralCrossJetCosThetaStarJetsLowTrue;      // true cos(theta*) for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetCosThetaStarJetsLowTrueNRec;  // jet cos(theta*) true and rec for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetCosThetaStarJetsHighTrue;     // true cos(theta*) for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetCosThetaStarJetsHighTrueNRec; // jet cos(theta*) true and rec for cross section for x_gamma >= 0.75

  TH1D  *fGeneralCrossMJMatchCosThetaStarJetsTrue;       // cos theta star of matched and next highest pt(or et) jet 
  TH1D  *fGeneralCrossMJMatchCosThetaStarJetsTrueNRec;
  TH1D  *fGeneralCrossMJMatchCosThetaStarJetsLowTrue; 
  TH1D  *fGeneralCrossMJMatchCosThetaStarJetsLowTrueNRec;
  TH1D  *fGeneralCrossMJMatchCosThetaStarJetsHighTrue; 
  TH1D  *fGeneralCrossMJMatchCosThetaStarJetsHighTrueNRec;

  //****************************************************************
  TH1D           *fGeneralCrossMuonRegionsPartTrue;                 // true plot of chosen muons region
  TH1D           *fGeneralCrossMuonPtPartTrue;                      // true plot of chosen muons pt
  TH1D           *fGeneralCrossMuonEtaPartTrue;                     // true plot of chosen muons eta
  TH1D           *fGeneralCrossMuonPtFinePartTrue;                  // true plot of fine chosen muons pt
  TH1D           *fGeneralCrossMuonEtaFinePartTrue;                 // true plot of fine chosen muons eta
  TH1D           *fGeneralCrossMuonPtMassimoPartTrue;               // true plot of chosen muons pt in massimo's binning
  TH1D           *fGeneralCrossMuonEtaMassimoPartTrue;              // true plot of chosen muons eta in massimo's binning
  TH1D           *fGeneralCrossMuonJetPtPartTrue;                   // true plot of chosen muon jets pt
  TH1D           *fGeneralCrossMuonJetEtaPartTrue;                  // true plot of chosen muon jets eta
  TH1D           *fGeneralCrossMuonJetPtFinePartTrue;               // true plot of fine chosen muon jets pt
  TH1D           *fGeneralCrossMuonJetEtaFinePartTrue;              // true plot of fine chosen muon jets eta
  TH1D           *fGeneralCrossJetXGammaPartTrue;                   // true x_gamma_zufo for cross section
  TH1D           *fGeneralCrossJetXGammaFinePartTrue;               // true fine x_gamma_zufo for cross section
  TH1D           *fGeneralCrossJetMJetsPartTrue;                    // true jet dijet invariant mass for cross section
  TH1D           *fGeneralCrossJetMJetsLowPartTrue;                 // true jet dijet invariant mass for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetMJetsHighPartTrue;                // true jet dijet invariant mass for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetDPhiJetsPartTrue;                 // true jet dijet dphi for cross section
  TH1D           *fGeneralCrossJetDPhiJetsLowPartTrue;              // true jet dijet dphi for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetDPhiJetsHighPartTrue;             // true jet dijet dphi for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetDRJetsPartTrue;                   // true jet dijet dr for cross section
  TH1D           *fGeneralCrossJetDRJetsLowPartTrue;                // true jet dijet dr for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetDRJetsHighPartTrue;               // true jet dijet dr for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetPtJetsPartTrue;                   // true jet dijet p_T for cross section
  TH1D           *fGeneralCrossJetPtJetsLowPartTrue;                // true jet dijet p_T for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetPtJetsHighPartTrue;               // true jet dijet p_T for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossJetCosThetaStarJetsPartTrue;         // true cos(theta*) for cross section
  TH1D           *fGeneralCrossJetCosThetaStarJetsLowPartTrue;      // true cos(theta*) for cross section for x_gamma < 0.75
  TH1D           *fGeneralCrossJetCosThetaStarJetsHighPartTrue;     // true cos(theta*) for cross section for x_gamma >= 0.75
  TH1D           *fGeneralCrossMJMatchCosThetaStarJetsPartTrue;       // cos theta star of matched and next highest pt(or et) jet 
  TH1D           *fGeneralCrossMJMatchCosThetaStarJetsLowPartTrue; 
  TH1D           *fGeneralCrossMJMatchCosThetaStarJetsHighPartTrue; 

  //******************************************************************************
  TH1D           *fGeneralMCDeltaRTrue;                         // true mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrue_lu;                      // true mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrue_ll;                      // true mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrue_hu;                      // true mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrue_hl;                      // true mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrueNRec;                     // true and reconstructed mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrueNRec_lu;                  // true and reconstructed mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrueNRec_ll;                  // true and reconstructed mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrueNRec_hu;                  // true and reconstructed mcdimuon deltaR for cross section
  TH1D           *fGeneralMCDeltaRTrueNRec_hl;                  // true and reconstructed mcdimuon deltaR for cross section

  TH1D           *fGeneralMCDeltaPhiTrue;                       // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrue_lu;                    // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrue_ll;                    // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrue_hu;                    // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrue_hl;                    // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrueNRec ;                  // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrueNRec_lu;                // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrueNRec_ll;                // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrueNRec_hu;                // mcdimuon delta phi    
  TH1D           *fGeneralMCDeltaPhiTrueNRec_hl;                // mcdimuon delta phi    

  TH2D           *fGeneralMuParentPhiTrueNRec;                  // Ingo dirty paste
  TH1D           *fGeneralMuParentPhiResTrueNRec;               // Ingo dirty paste
  TH1D           *fGeneralMuParentDRResTrueNRec;                // Ingo dirty paste
  TH1D           *fGeneralMuParentPTResTrueNRec;                // Ingo dirty paste
  TH2D           *fGeneralMuQuarkPhiTrueNRec;                   // Ingo dirty paste
  TH1D           *fGeneralMuQuarkPhiResTrueNRec;                // Ingo dirty paste
  TH1D           *fGeneralMuQuarkDRResTrueNRec;                 // Ingo dirty paste
  TH1D           *fGeneralMuQuarkPTResTrueNRec;                 // Ingo dirty paste

/* DB Dijet Selection  */

  TH1D           *fGeneralDijetbothDimuMass1bin_true_hflmu;     // Dimuon total xsection true def
  TH1D           *fGeneralDijetbothDimuxsecPt_true_hflmu;       // Dimuon xsection true plots
  TH1D           *fGeneralDijetbothDimuxsecEta_true_hflmu;      // Dimuon xsection true plots
  TH1D           *fGeneralDijetbothDimuxsecDphi_true_hflmu;     // Dimuon xsection true plots

  TH1D           *fGeneralDijetoneDimuMass1bin_true_hflmu;      // Dimuon total xsection true def
  TH1D           *fGeneralDijetoneDimuxsecPt_true_hflmu;        // Dimuon xsection true plots
  TH1D           *fGeneralDijetoneDimuxsecEta_true_hflmu;       // Dimuon xsection true plots
  TH1D           *fGeneralDijetoneDimuxsecDphi_true_hflmu;      // Dimuon xsection true plots

  TH1D           *fGeneralDijetnoneDimuMass1bin_true_hflmu;     // Dimuon total xsection true def
  TH1D           *fGeneralDijetnoneDimuxsecPt_true_hflmu;       // Dimuon xsection true plots
  TH1D           *fGeneralDijetnoneDimuxsecEta_true_hflmu;      // Dimuon xsection true plots
  TH1D           *fGeneralDijetnoneDimuxsecDphi_true_hflmu;     // Dimuon xsection true plots

/* End Dijet Selection  */


  TH1D           *fGeneralDimuMass_any;                         // Ingo dirty paste
  TH1D           *fGeneralDimuMass_true_hflmu;                  // Ingo dirty paste
  TH1D           *fGeneralDimuMass_truenrec_hflmu;              // Ingo dirty paste

  TH2D           *fGeneralMuQuarkPtTrueNRec;                    // Ingo dirty paste
  TH2D           *fGeneralMuQuarkPtTrueNRec_singlb;             // Ingo dirty paste
  TH2D           *fGeneralMuBMesonPtTrueNRec;                   // Ingo dirty paste
  TH2D           *fGeneralMuBMesonPtTrueNRec_singlb;            // Ingo dirty paste

  TH1D           *fGeneralDimuMass1bin_any;                     // Dimuon total xsection true def
  TH1D           *fGeneralDimuMass1bin_true_hflmu;              // Dimuon total xsection true def
  TH1D           *fGeneralDimuMass1bin_truenrec_hflmu;          // Dimuon total xsection true def

  TH1D           *fGeneralDimuxsecPt_any;                       // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPt_true_hflmu;                // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPt_truenrec_hflmu;            // Dimuon xsection true plots
    
  TH1D           *fGeneralDimuxsecEta_any;                      // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecEta_true_hflmu;               // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecEta_truenrec_hflmu;           // Dimuon xsection true plots
  
  TH1D           *fGeneralDimuxsecFinders_any;                  // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecFinders_true_hflmu;           // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecFinders_truenrec_hflmu;       // Dimuon xsection true plots

  TH1D           *fGeneralDimuxsecDR_any;                       // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecDR_true_hflmu;                // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecDR_truenrec_hflmu;            // Dimuon xsection true plots
  
  TH1D           *fGeneralDimuxsecDphi_any;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecDphi_true_hflmu;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecDphi_truenrec_hflmu;            // Dimuon xsection true plots

  TH1D           *fGeneralDimuxsecPtb_any;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_true_hflmu;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_truenrec_hflmu;            // Dimuon xsection true plots

  TH1D           *fGeneralDimuxsecPtb_sameb_any;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_sameb_true_hflmu;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_sameb_truenrec_hflmu;            // Dimuon xsection true plots

  TH1D           *fGeneralDimuxsecPtb_diffb_any;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_diffb_true_hflmu;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_diffb_truenrec_hflmu;            // Dimuon xsection true plots

  TH1D           *fGeneralDimuxsecPtb_samecone_any;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_samecone_true_hflmu;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_samecone_truenrec_hflmu;            // Dimuon xsection true plots

  TH1D           *fGeneralDimuxsecPtb_asym_any;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_asym_true_hflmu;            // Dimuon xsection true plots
  TH1D           *fGeneralDimuxsecPtb_asym_truenrec_hflmu;            // Dimuon xsection true plots

  TH1D           *fGeneralDimu_b_pt_true_hflmu;                 // pt of b quark from which the muon came
  TH1D           *fGeneralDimu_b_pt_truenrec_hflmu;             // pt of b quark from which the muon came
  TH1D           *fGeneralDeltaRMuonJet;   // dr between muon and nearest jet
  TH2D           *fGeneralDeltaRMuonJet2D;   // dr between muon and nearest jet vs dr between muon and second nearest jet
  TH1D           *fGeneralDeltaRMuonSecondJet;   // dr between muon and second nearest jet

  // control histograms
  TH2D           *fControlJetPtDeltaR;                    // control histogram for delta r between jet and any quark associated by muon and p_T_jet
  TH2D           *fControlJetEtDeltaR;                    // control histogram for delta r between jet and any quark associated by muon and E_T_jet
  TH2D           *fControlJetMassDeltaR;                  // control histogram for delta r between jet and any quark associated by muon and jet_mass
  TH2D           *fControlJetPtDeltaRB;                   // control histogram for delta r between jet and b-quark associated by muon and p_T_jet
  TH2D           *fControlJetEtDeltaRB;                   // control histogram for delta r between jet and b-quark associated by muon and E_T_jet
  TH2D           *fControlJetMassDeltaRB;                 // control histogram for delta r between jet and b-quark associated by muon and jet_mass
  TH2D           *fControlJetPtDeltaRC;                   // control histogram for delta r between jet and c-quark associated by muon and p_T_jet
  TH2D           *fControlJetEtDeltaRC;                   // control histogram for delta r between jet and c-quark associated by muon and E_T_jet
  TH2D           *fControlJetMassDeltaRC;                 // control histogram for delta r between jet and c-quark associated by muon and jet_mass
  TH2D           *fControlJetPtDeltaRLF;                  // control histogram for delta r between jet and light quark associated by muon and p_T_jet
  TH2D           *fControlJetEtDeltaRLF;                  // control histogram for delta r between jet and light quark associated by muon and E_T_jet
  TH2D           *fControlJetMassDeltaRLF;                // control histogram for delta r between jet and light quark associated by muon and jet_mass

  TH2D           *fControlJetPtPtRelRec;                  // control histogram for between rec ptrel (any quark) and p_T_jet
  TH2D           *fControlJetEtPtRelRec;                  // control histogram for between rec ptrel (any quark) and E_T_jet
  TH2D           *fControlJetMassPtRelRec;                // control histogram for between rec ptrel (any quark) and jet_mass
  TH2D           *fControlJetPtPtRelRecB;                 // control histogram for between rec ptrel (b-quark) and p_T_jet
  TH2D           *fControlJetEtPtRelRecB;                 // control histogram for between rec ptrel (b-quark) and E_T_jet
  TH2D           *fControlJetMassPtRelRecB;               // control histogram for between rec ptrel (b-quark) and jet_mass
  TH2D           *fControlJetPtPtRelRecC;                 // control histogram for between rec ptrel (c-quark) and p_T_jet
  TH2D           *fControlJetEtPtRelRecC;                 // control histogram for between rec ptrel (c-quark) and E_T_jet
  TH2D           *fControlJetMassPtRelRecC;               // control histogram for between rec ptrel (c-quark) and jet_mass
  TH2D           *fControlJetPtPtRelRecLF;                // control histogram for between rec ptrel (light quark) and p_T_jet
  TH2D           *fControlJetEtPtRelRecLF;                // control histogram for between rec ptrel (light quark) and E_T_jet
  TH2D           *fControlJetMassPtRelRecLF;              // control histogram for between rec ptrel (light quark) and jet_mass

  TH2D           *fControlPtRelJetQuark;                  // control histogram for ptrel between jet or any quark and reconstructed muon
  TH2D           *fControlPtRelJetQuark45;                // control histogram for ptrel between jet or any quark and reconstructed muon for 4 < p_T_jet < 5
  TH2D           *fControlPtRelJetQuark56;                // control histogram for ptrel between jet or any quark and reconstructed muon for 5 < p_T_jet < 6
  TH2D           *fControlPtRelJetQuark6;                 // control histogram for ptrel between jet or any quark and reconstructed muon for p_T_jet > 6
  TH2D           *fControlPtRelJetBQuark;                 // control histogram for ptrel between jet or b-quark and reconstructed muon
  TH2D           *fControlPtRelJetBQuark45;               // control histogram for ptrel between jet or b-quark and reconstructed muon for 4 < p_T_jet < 5
  TH2D           *fControlPtRelJetBQuark56;               // control histogram for ptrel between jet or b-quark and reconstructed muon for 5 < p_T_jet < 6
  TH2D           *fControlPtRelJetBQuark6;                // control histogram for ptrel between jet or b-quark and reconstructed muon for p_T_jet > 6
  TH2D           *fControlPtRelJetCQuark;                 // control histogram for ptrel between jet or c-quark and reconstructed muon
  TH2D           *fControlPtRelJetCQuark45;               // control histogram for ptrel between jet or c-quark and reconstructed muon for 4 < p_T_jet < 5
  TH2D           *fControlPtRelJetCQuark56;               // control histogram for ptrel between jet or c-quark and reconstructed muon for 5 < p_T_jet < 6
  TH2D           *fControlPtRelJetCQuark6;                // control histogram for ptrel between jet or c-quark and reconstructed muon for p_T_jet > 6
  TH2D           *fControlPtRelJetLFQuark;                // control histogram for ptrel between jet or light quark and reconstructed muon
  TH2D           *fControlPtRelJetLFQuark45;              // control histogram for ptrel between jet or light quark and reconstructed muon for 4 < p_T_jet < 5
  TH2D           *fControlPtRelJetLFQuark56;              // control histogram for ptrel between jet or light quark and reconstructed muon for 5 < p_T_jet < 6
  TH2D           *fControlPtRelJetLFQuark6;               // control histogram for ptrel between jet or light quark and reconstructed muon for p_T_jet > 6
  TH2D           *fControlMCWeightsQ2;
  TH1D           *fControlMCWeights;

  // fake muon histograms


 TH1D *fFakeHadronPionPt;            // pt distribution of all true pions
 TH1D *fFakeHadronPionEta_lowPt;           // eta distribution of all true pions  low Pt
 TH1D *fFakeHadronPionPhi_lowPt;           // phi distribution of all true pions  low Pt
 TH1D *fFakeHadronPionEta_highPt;           // eta distribution of all true pions high Pt
 TH1D *fFakeHadronPionPhi_highPt;           // phi distribution of all true pions high Pt


 TH1D *fFakeHadronAllPt;            // pt distribution of all true charged particles
 TH1D *fFakeHadronAllEta_lowPt;           // eta distribution of all charged particles low Pt
 TH1D *fFakeHadronAllPhi_lowPt;           // phi distribution of all charged particles low Pt
 TH1D *fFakeHadronAllEta_highPt;           // eta distribution of all true charged particles high Pt
 TH1D *fFakeHadronAllPhi_highPt;           // phi distribution of all true charged particles high Pt
 //-----
 TH1D *fFakeHadronKaonPt;            // pt distribution of all true kaons
 TH1D *fFakeHadronKaonEta_lowPt;           // eta distribution of all true kaons low Pt
 TH1D *fFakeHadronKaonPhi_lowPt;           // phi distribution of all true kaons low Pt
 TH1D *fFakeHadronKaonEta_highPt;           // eta distribution of all true kaons high Pt
 TH1D *fFakeHadronKaonPhi_highPt;           // phi distribution of all true kaons high Pt 

 TH1D *fFakeProbabilityAllPt;       // pt dependence of probability to identify pion as muon
 TH1D *fFakeProbabilityAllEta_lowPt;      // eta dependence of probability to identify charged particle as muon
 TH1D *fFakeProbabilityAllPhi_lowPt;      // phi dependence of probability to identify charged particle as muon low Pt
 TH1D *fFakeProbabilityAllEta_highPt;      // eta dependence of probability to identify charged particle as muon
 TH1D *fFakeProbabilityAllPhi_highPt;      // phi dependence of probability to identify charged particle as muon low Pt

 TH1D *fFakeProbabilityPionPt;       // pt dependence of probability to identify pion as muon
 TH1D *fFakeProbabilityPionEta_lowPt;      // eta dependence of probability to identify pion as muon
 TH1D *fFakeProbabilityPionPhi_lowPt;      // phi dependence of probability to identify pion as muon low Pt
 TH1D *fFakeProbabilityPionEta_highPt;      // eta dependence of probability to identify pion as muon
 TH1D *fFakeProbabilityPionPhi_highPt;      // phi dependence of probability to identify pion as muon low Pt
 TH1D *fFakeProbabilityKaonPt;       // pt dependence of probability to identify kaon as muon low Pt
 TH1D *fFakeProbabilityKaonEta_lowPt;      // eta dependence of probability to identify kaon as muon high Pt
 TH1D *fFakeProbabilityKaonPhi_lowPt;      // phi dependence of probability to identify kaon as muon high Pt
 TH1D *fFakeProbabilityKaonEta_highPt;      // eta dependence of probability to identify kaon as muon high Pt
 TH1D *fFakeProbabilityKaonPhi_highPt;      // phi dependence of probability to identify kaon as muon high Pt
 //-----------fakes from decays
 TH1D *fFakeDecayProbabilityPionPt;       // pt dependence of probability to identify pion as muon
 TH1D *fFakeDecayProbabilityPionEta_lowPt;      // eta dependence of probability to identify pion as muon
 TH1D *fFakeDecayProbabilityPionPhi_lowPt;      // phi dependence of probability to identify pion as muon low Pt
 TH1D *fFakeDecayProbabilityPionEta_highPt;      // eta dependence of probability to identify pion as muon
 TH1D *fFakeDecayProbabilityPionPhi_highPt;      // phi dependence of probability to identify pion as muon low Pt
 TH1D *fFakeDecayProbabilityKaonPt;       // pt dependence of probability to identify kaon as muon low Pt
 TH1D *fFakeDecayProbabilityKaonEta_lowPt;      // eta dependence of probability to identify kaon as muon high Pt
 TH1D *fFakeDecayProbabilityKaonPhi_lowPt;      // phi dependence of probability to identify kaon as muon high Pt
 TH1D *fFakeDecayProbabilityKaonEta_highPt;      // eta dependence of probability to identify kaon as muon high Pt
 TH1D *fFakeDecayProbabilityKaonPhi_highPt;      // phi dependence of probability to identify kaon as muon high Pt
 //------------- fakes from punch through
 TH1D *fFakePunchProbabilityPionPt;       // pt dependence of probability to identify pion as muon
 TH1D *fFakePunchProbabilityPionEta_lowPt;      // eta dependence of probability to identify pion as muon
 TH1D *fFakePunchProbabilityPionPhi_lowPt;      // phi dependence of probability to identify pion as muon low Pt
 TH1D *fFakePunchProbabilityPionEta_highPt;      // eta dependence of probability to identify pion as muon
 TH1D *fFakePunchProbabilityPionPhi_highPt;      // phi dependence of probability to identify pion as muon low Pt
 TH1D *fFakePunchProbabilityKaonPt;       // pt dependence of probability to identify kaon as muon low Pt
 TH1D *fFakePunchProbabilityKaonEta_lowPt;      // eta dependence of probability to identify kaon as muon high Pt
 TH1D *fFakePunchProbabilityKaonPhi_lowPt;      // phi dependence of probability to identify kaon as muon high Pt
 TH1D *fFakePunchProbabilityKaonEta_highPt;      // eta dependence of probability to identify kaon as muon high Pt
 TH1D *fFakePunchProbabilityKaonPhi_highPt;      // phi dependence of probability to identify kaon as muon high Pt




 public:
  GMCs();
  virtual ~GMCs();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();

  virtual Bool_t CreateFake();
  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();

  virtual Bool_t FillHistos();
  virtual Bool_t ObjectsFillHistos();
  virtual Bool_t ObjectsFillControl(GMC* mc);
  virtual Bool_t ObjectsFillGeneral(GMC* mc);
  virtual Bool_t ObjectsFillControlJets(GJet* mc_jet);
  virtual Bool_t ObjectsFillGeneralJets(GJet* mc_jet);
  virtual Bool_t ObjectsFillGeneralPMJets(GJet* mc_jet);
  //  virtual Bool_t ObjectsFillControlMCDIMuons(GDIMuon* mcdimuon);
  virtual Bool_t ObjectsFillGeneralMCDIMuons(GDIMuon* mcdimuon);

  virtual Bool_t Reset();
  virtual Bool_t Do();
  virtual Bool_t Fill();
  virtual Bool_t Finalize();

/*   virtual Bool_t AddMuonMCInfo(GMuon *muon, Int_t fmckinid, Int_t partid,  */
/* 			       Double_t px, Double_t py, Double_t pz, Double_t e,  */
/* 			       Int_t qpartid,  */
/* 			       Double_t qpx, Double_t qpy, Double_t qpz, Double_t qe,  */
/* 			       Int_t qpartid,  */
/* 			       Double_t dirpx, Double_t dirpy, Double_t dirpz, Double_t dire); */
  virtual Bool_t AddMuonMCInfo(GMuon *muon, Int_t fmckinid, Int_t partid, 
			       Double_t px, Double_t py, Double_t pz, Double_t e, 
			       Int_t qpartid, 
			       Double_t qpx, Double_t qpy, Double_t qpz, Double_t qe, 
			       Int_t dirpartid, 
			       Double_t dirpx, Double_t dirpy, Double_t dirpz, Double_t dire);

  virtual GMC*       GetMC(Int_t index);
  virtual GMC*       GetMC(Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t e);
  virtual GMCVertex* GetMCVertex(Int_t index);

  virtual GJet* GetMCHJet(Int_t index);
  virtual GJet* GetMCHJetWithID(Int_t id);
  virtual GJet* GetMCHMJet(Int_t index);
  virtual GJet* GetMCHMJetWithID(Int_t id);
  virtual GJet* GetMCHBJet(Int_t index);
  virtual GJet* GetMCHBJetWithID(Int_t id);
  virtual GJet* GetMCHBMJet(Int_t index);
  virtual GJet* GetMCHBMJetWithID(Int_t id);
  virtual GJet* GetMCPJet(Int_t index);
  virtual GJet* GetMCPJetWithID(Int_t id);
  virtual GJet* GetMCPMJet(Int_t index);
  virtual GJet* GetMCPMJetWithID(Int_t id);

  virtual Bool_t CheckMothersAndVertices();

  virtual Bool_t GetAllCuts();
  virtual Bool_t GetAllMCCuts();
  virtual Bool_t GetAllPartMCCuts();
  virtual Bool_t CheckQ2Cut();
  virtual Bool_t CheckQ2SelectionCut();
  inline virtual Bool_t GetQ2SelectionCut() { return fQ2SelectionCut; }
  virtual Bool_t CheckYCut();
  virtual Bool_t CheckHeavyFlavours(GMC *mc);
  virtual Bool_t CheckMCDIMuonHFL(GDIMuon *mcdimuon);
  virtual Bool_t CheckAllCuts();

  virtual Bool_t CheckMuonCutsStage1(GMC *mc);
  virtual Bool_t CheckMuonCutsStage2(GMC *mc);

  virtual Bool_t CheckBParent(Int_t id);
  virtual Bool_t CheckCParent(Int_t id);

  virtual Double_t GetWeight();

  virtual Bool_t AssociateMCJet(GJet *jet);

  virtual Bool_t AssociateMCJet(GMC *particle);
  virtual Bool_t AssociateMCPMJet(GMC *particle);
  virtual Bool_t AssociateMCJetToMCMuon(GMC *mc_muon); 
  virtual Bool_t AssociateMCPMJetToMCMuon(GMC *mc_muon); 
  virtual Int_t IsMuonAssociatedToMCJet(GJet *mc_jet);
  virtual Int_t IsMuonAssociatedToMCPMJet(GJet *mc_jet);
  virtual Int_t IsJetAssociatedToMCMuon(GMC *mcmuon);
  virtual Int_t IsPMJetAssociatedToMCMuon(GMC *mcmuon);

  virtual Bool_t Calc(Int_t index1, Int_t index2);
  virtual Bool_t CalcPart(Int_t index1, Int_t index2);
  virtual Bool_t CalcMJCosThetaStarpmjets();
  virtual Bool_t CalcMJCosThetaStarhbmjets();
  TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GMCs,0) // MCs Class for everything which is related only to mc particles
};

R__EXTERN GMCs *gMCs;

#endif
