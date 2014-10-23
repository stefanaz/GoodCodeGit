//
// GMCs.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 07:44:58 $
// $Revision: 1.50 $
//

#include <GMCs.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMCs)
#endif

GMCs *gMCs = 0;

//_____________________________________________________________
// GMCs
// MCs Class for everything which is related only to mc particles
//
//
GMCs::GMCs() : GPhysObj() {
  //
  // GMCs default constructor
  if ( gDebug ) cout << endl << "GMCs::GMCs ctor called" << endl << endl;

  // initialize global pointer
  gMCs = this;

  // initialize variables
  fIndex1                 = -99;
  fIndex2                 = -99;
  fXGammaJets             = -9999.99;
  fXGamma                 = -9999.99;
  fXGammaJets_zufo        = -9999.99;
  fMJets                  = -9999.99;
  fDPhiJets               = -9999.99;
  fDRJets                 = -9999.99;
  fPtJets                 = -9999.99;
  fCosThetaStarJets       = -9999.99;
  fEtaJets                =  9999.99;

  fPartIndex1                 = -99;
  fPartIndex2                 = -99;
  fPartXGammaJets             = -9999.99;
  fPartXGamma                 = -9999.99;
  fPartXGammaJets_zufo        = -9999.99;
  fPartMJets                  = -9999.99;
  fPartDPhiJets               = -9999.99;
  fPartDRJets                 = -9999.99;
  fPartPtJets                 = -9999.99;
  fPartCosThetaStarJets       = -9999.99;
  fPartEtaJets                =  9999.99;

  // initialize clonesarray
  fMCs         = new TClonesArray("GMC",511);
  fNMCs        = 0;
  fMCMuons     = new TClonesArray("GMC",20);
  fNMCMuons    = 0;
  fMCDIMuons   = new TClonesArray("GDIMuon",20);
  fNMCDIMuons  = 0;
//   fMCDIMuons2   = new TClonesArray("GDIMuon",20);
//   fNMCDIMuons2  = 0;
  fMCVertices  = new TClonesArray("GMCVertex",12);
  fNMCVertices = 0;
  fMCHJets     = new TClonesArray("GJet",10);
  fNMCHJets    = 0;
  fMCHMJets    = new TClonesArray("GJet",10);
  fNMCHMJets   = 0;
  fMCHBJets    = new TClonesArray("GJet",10);
  fNMCHBJets   = 0;
  fMCHBMJets   = new TClonesArray("GJet",10);
  fNMCHBMJets  = 0;
  fMCPJets     = new TClonesArray("GJet",10);
  fNMCPJets    = 0;
  fMCPMJets    = new TClonesArray("GJet",10);
  fNMCPMJets   = 0;

  // initialize jet cut flags
  fMCHJetPtACut   = kFALSE;
  fMCHJetPtBCut   = kFALSE;
  fMCHMJetPtACut  = kFALSE;
  fMCHMJetPtBCut  = kFALSE;
  fMCHBJetPtACut  = kFALSE;
  fMCHBJetPtBCut  = kFALSE;
  fMCHBMJetPtACut = kFALSE;
  fMCHBMJetPtBCut = kFALSE;
  fMCPJetPtACut   = kFALSE;
  fMCPJetPtBCut   = kFALSE;
  fMCPMJetPtACut  = kFALSE;
  fMCPMJetPtBCut  = kFALSE;

  // initialize cut flags
  fQ2Cut             = kFALSE;
  fQ2SelectionCut    = kFALSE;
  fYCut              = kFALSE;
  fMuonCuts          = kFALSE;
  fMCDIMuonCuts      = kFALSE;
  
  // initalize variables
  fOwnFMCKINID    = 10000;
  fHeavyFlavours  = kFALSE;

  // initialize general histograms
  fGeneralQ2_uncut                      = 0;
  fGeneralY_uncut                       = 0;
  fGeneralX_uncut                       = 0;

  fGeneralQ2                            = 0;
  fGeneralQ2_1                          = 0;
  fGeneralQ2_2                          = 0;
  fGeneralQ2_3                          = 0;
  fGeneralY                             = 0;
  fGeneralX                             = 0;
  fGeneralCrossTotalTrue                = 0;
  fGeneralCrossTotalTrueNRec            = 0;
  fGeneralCrossTotalAssociatedTrue      = 0;
  fGeneralCrossTotalAssociatedTrueNRec  = 0;
  fGeneralCrossTotalEventTrue           = 0;
  fGeneralCrossTotalEventTrueNRec       = 0;
  fGeneralCrossTotalTrue                = 0;
  fGeneralCrossTotalTrueNRec            = 0;
  fGeneralCrossMuonRegionsTrue          = 0;
  fGeneralCrossMuonRegionsTrueNRec      = 0;
  fGeneralCrossMuonFinderTrue           = 0;
  fGeneralCrossMuonFinderTrueNRec       = 0;

  fGeneralCrossMuonRegionsNoJetTrue          = 0;
  fGeneralCrossMuonRegionsNoJetTrueNRec      = 0;

  fGeneralMuParentPhiTrueNRec = 0; // ingo
  fGeneralMuParentPhiResTrueNRec = 0;
  fGeneralMuParentDRResTrueNRec = 0;
  fGeneralMuQuarkPhiTrueNRec = 0; // ingo
  fGeneralMuQuarkPhiResTrueNRec = 0;
  fGeneralMuQuarkDRResTrueNRec = 0;

  fGeneralDimuMass_any = 0;
  fGeneralDimuMass_true_hflmu = 0;
  fGeneralDimuMass_truenrec_hflmu = 0;

  fGeneralMuQuarkPtTrueNRec = 0; // ingo
  fGeneralMuQuarkPtTrueNRec_singlb = 0; // ingo
  fGeneralMuBMesonPtTrueNRec = 0; // ingo
  fGeneralMuBMesonPtTrueNRec_singlb = 0; // ingo

/* DB Dijet Selection  */

  fGeneralDijetbothDimuMass1bin_true_hflmu = 0;
  fGeneralDijetbothDimuxsecPt_true_hflmu   = 0;
  fGeneralDijetbothDimuxsecEta_true_hflmu  = 0;  
  fGeneralDijetbothDimuxsecDphi_true_hflmu = 0; 

  fGeneralDijetoneDimuMass1bin_true_hflmu  = 0;  
  fGeneralDijetoneDimuxsecPt_true_hflmu    = 0;    
  fGeneralDijetoneDimuxsecEta_true_hflmu   = 0;   
  fGeneralDijetoneDimuxsecDphi_true_hflmu  = 0;  

  fGeneralDijetnoneDimuMass1bin_true_hflmu = 0; 
  fGeneralDijetnoneDimuxsecPt_true_hflmu   = 0;   
  fGeneralDijetnoneDimuxsecEta_true_hflmu  = 0;  
  fGeneralDijetnoneDimuxsecDphi_true_hflmu = 0; 

/* End Dijet Selection */

  fGeneralDimuMass1bin_any = 0;
  fGeneralDimuMass1bin_true_hflmu = 0;
  fGeneralDimuMass1bin_truenrec_hflmu = 0;

  fGeneralDimuxsecPt_any = 0;
  fGeneralDimuxsecPt_true_hflmu = 0;
  fGeneralDimuxsecPt_truenrec_hflmu = 0;
  
  fGeneralDimuxsecEta_any = 0;
  fGeneralDimuxsecEta_true_hflmu = 0;
  fGeneralDimuxsecEta_truenrec_hflmu = 0;
  
  fGeneralDimuxsecFinders_any = 0;
  fGeneralDimuxsecFinders_true_hflmu = 0;
  fGeneralDimuxsecFinders_truenrec_hflmu = 0;

  fGeneralDimuxsecDR_any = 0;
  fGeneralDimuxsecDR_true_hflmu = 0;
  fGeneralDimuxsecDR_truenrec_hflmu = 0;
  
  fGeneralDimuxsecDphi_any = 0;
  fGeneralDimuxsecDphi_true_hflmu = 0;
  fGeneralDimuxsecDphi_truenrec_hflmu = 0;

  fGeneralDimuxsecPtb_any = 0;
  fGeneralDimuxsecPtb_true_hflmu = 0;
  fGeneralDimuxsecPtb_truenrec_hflmu = 0;

  fGeneralDimuxsecPtb_sameb_any = 0;
  fGeneralDimuxsecPtb_sameb_true_hflmu = 0;
  fGeneralDimuxsecPtb_sameb_truenrec_hflmu = 0;

  fGeneralDimuxsecPtb_diffb_any = 0;
  fGeneralDimuxsecPtb_diffb_true_hflmu = 0;
  fGeneralDimuxsecPtb_diffb_truenrec_hflmu = 0;

  fGeneralDimuxsecPtb_samecone_any = 0;
  fGeneralDimuxsecPtb_samecone_true_hflmu = 0;
  fGeneralDimuxsecPtb_samecone_truenrec_hflmu = 0;

  fGeneralDimuxsecPtb_asym_any = 0;
  fGeneralDimuxsecPtb_asym_true_hflmu = 0;
  fGeneralDimuxsecPtb_asym_truenrec_hflmu = 0;

  fGeneralDimu_b_pt_true_hflmu = 0;
  fGeneralDimu_b_pt_truenrec_hflmu = 0;

  fGeneralCrossMuonPtTrue               = 0;
  fGeneralCrossMuonPtTrueNRec           = 0;
  fGeneralCrossMuonEtaTrue              = 0;
  fGeneralCrossMuonEtaTrueNRec          = 0;
  fGeneralCrossMuonPtFineTrue           = 0;
  fGeneralCrossMuonPtFineTrueNRec       = 0;
  fGeneralCrossMuonEtaFineTrue          = 0;
  fGeneralCrossMuonEtaFineTrueNRec      = 0;
  fGeneralCrossMuonPtMassimoTrue           = 0;
  fGeneralCrossMuonPtMassimoTrueNRec       = 0;
  fGeneralCrossMuonEtaMassimoTrue          = 0;
  fGeneralCrossMuonEtaMassimoTrueNRec      = 0;

  fGeneralCrossMuonPtNoJetTrue               = 0;
  fGeneralCrossMuonPtNoJetTrueNRec           = 0;
  fGeneralCrossMuonEtaNoJetTrue              = 0;
  fGeneralCrossMuonEtaNoJetTrueNRec          = 0;
  fGeneralCrossMuonPtFineNoJetTrue           = 0;
  fGeneralCrossMuonPtFineNoJetTrueNRec       = 0;
  fGeneralCrossMuonEtaFineNoJetTrue          = 0;
  fGeneralCrossMuonEtaFineNoJetTrueNRec      = 0;
  fGeneralCrossMuonPtMassimoNoJetTrue           = 0;
  fGeneralCrossMuonPtMassimoNoJetTrueNRec       = 0;
  fGeneralCrossMuonEtaMassimoNoJetTrue          = 0;
  fGeneralCrossMuonEtaMassimoNoJetTrueNRec      = 0;

  fGeneralCrossMuonJetPtTrue            = 0;
  fGeneralCrossMuonJetPtTrueNRec        = 0;
  fGeneralCrossMuonJetEtaTrue           = 0;
  fGeneralCrossMuonJetEtaTrueNRec       = 0;
  fGeneralCrossMuonJetPtFineTrue        = 0;
  fGeneralCrossMuonJetPtFineTrueNRec    = 0;
  fGeneralCrossMuonJetEtaFineTrue       = 0;
  fGeneralCrossMuonJetEtaFineTrueNRec   = 0;
  fGeneralCrossJetXGammaTrue = 0;
  fGeneralCrossJetXGammaTrueNRec = 0;
  fGeneralCrossJetXGammaFineTrue = 0;
  fGeneralCrossJetXGammaFineTrueNRec = 0;
  fGeneralCrossJetMJetsTrue = 0;
  fGeneralCrossJetMJetsTrueNRec = 0;
  fGeneralCrossJetDPhiJetsTrue = 0;
  fGeneralCrossJetDPhiJetsTrueNRec = 0;
  fGeneralCrossJetDRJetsTrue = 0;
  fGeneralCrossJetDRJetsTrueNRec = 0;
  fGeneralCrossJetPtJetsTrue = 0;
  fGeneralCrossJetPtJetsTrueNRec = 0;
  fGeneralCrossJetCosThetaStarJetsTrue = 0;
  fGeneralCrossJetCosThetaStarJetsTrueNRec = 0;
  fGeneralCrossJetCosThetaStarJetsLowTrue = 0; 
  fGeneralCrossJetCosThetaStarJetsLowTrueNRec = 0;
  fGeneralCrossJetCosThetaStarJetsHighTrue = 0; 
  fGeneralCrossJetCosThetaStarJetsHighTrueNRec = 0;

  fGeneralCrossMJMatchCosThetaStarJetsTrue = 0;
  fGeneralCrossMJMatchCosThetaStarJetsTrueNRec = 0;
  fGeneralCrossMJMatchCosThetaStarJetsLowTrue = 0; 
  fGeneralCrossMJMatchCosThetaStarJetsLowTrueNRec = 0;
  fGeneralCrossMJMatchCosThetaStarJetsHighTrue = 0; 
  fGeneralCrossMJMatchCosThetaStarJetsHighTrueNRec = 0;

  fGeneralCrossMuonRegionsPartTrue = 0;                
  fGeneralCrossMuonPtPartTrue = 0;                     
  fGeneralCrossMuonEtaPartTrue = 0;                    
  fGeneralCrossMuonPtFinePartTrue = 0;                 
  fGeneralCrossMuonEtaFinePartTrue = 0;                
  fGeneralCrossMuonPtMassimoPartTrue = 0;              
  fGeneralCrossMuonEtaMassimoPartTrue = 0;             
  fGeneralCrossMuonJetPtPartTrue            = 0;
  fGeneralCrossMuonJetEtaPartTrue           = 0;
  fGeneralCrossMuonJetPtFinePartTrue        = 0;
  fGeneralCrossMuonJetEtaFinePartTrue       = 0;
  fGeneralCrossMJMatchCosThetaStarJetsPartTrue = 0;
  fGeneralCrossMJMatchCosThetaStarJetsLowPartTrue = 0; 
  fGeneralCrossMJMatchCosThetaStarJetsHighPartTrue = 0; 
  
  fGeneralCrossJetXGammaPartTrue = 0;                  
  fGeneralCrossJetXGammaFinePartTrue = 0;              
  fGeneralCrossJetMJetsPartTrue = 0;                   
  fGeneralCrossJetMJetsLowPartTrue = 0;                
  fGeneralCrossJetMJetsHighPartTrue = 0;               
  fGeneralCrossJetDPhiJetsPartTrue = 0;                
  fGeneralCrossJetDPhiJetsLowPartTrue = 0;             
  fGeneralCrossJetDPhiJetsHighPartTrue = 0;            
  fGeneralCrossJetDRJetsPartTrue = 0;                  
  fGeneralCrossJetDRJetsLowPartTrue = 0;               
  fGeneralCrossJetDRJetsHighPartTrue = 0;              
  fGeneralCrossJetPtJetsPartTrue = 0;                  
  fGeneralCrossJetPtJetsLowPartTrue = 0;               
  fGeneralCrossJetPtJetsHighPartTrue = 0;              
  fGeneralCrossJetCosThetaStarJetsPartTrue = 0;        
  fGeneralCrossJetCosThetaStarJetsLowPartTrue = 0;     
  fGeneralCrossJetCosThetaStarJetsHighPartTrue = 0;    
  fGeneralDeltaRMuonJet = 0;
  fGeneralDeltaRMuonSecondJet=0;
  fGeneralDeltaRMuonJet2D=0;
  fGeneralMCDeltaRTrue = 0;
  fGeneralMCDeltaRTrue_lu = 0;
  fGeneralMCDeltaRTrue_ll = 0;
  fGeneralMCDeltaRTrue_hu = 0;
  fGeneralMCDeltaRTrue_hl = 0;
  fGeneralMCDeltaRTrueNRec = 0;
  fGeneralMCDeltaRTrueNRec_lu = 0;
  fGeneralMCDeltaRTrueNRec_ll = 0;
  fGeneralMCDeltaRTrueNRec_hu = 0;
  fGeneralMCDeltaRTrueNRec_hl = 0;

  fGeneralMCDeltaPhiTrue = 0;
  fGeneralMCDeltaPhiTrue_lu = 0;
  fGeneralMCDeltaPhiTrue_ll = 0;
  fGeneralMCDeltaPhiTrue_hu = 0;
  fGeneralMCDeltaPhiTrue_hl = 0;
  fGeneralMCDeltaPhiTrueNRec  = 0;
  fGeneralMCDeltaPhiTrueNRec_lu = 0;
  fGeneralMCDeltaPhiTrueNRec_ll = 0;
  fGeneralMCDeltaPhiTrueNRec_hu = 0;
  fGeneralMCDeltaPhiTrueNRec_hl = 0;

  // initialize control histograms
  fControlJetPtDeltaR            = 0;      
  fControlJetEtDeltaR            = 0;      
  fControlJetMassDeltaR          = 0;      
  fControlJetPtDeltaRB           = 0;      
  fControlJetEtDeltaRB           = 0;      
  fControlJetMassDeltaRB         = 0;      
  fControlJetPtDeltaRC           = 0;      
  fControlJetEtDeltaRC           = 0;      
  fControlJetMassDeltaRC         = 0;      
  fControlJetPtDeltaRLF          = 0;      
  fControlJetEtDeltaRLF          = 0;      
  fControlJetMassDeltaRLF        = 0;      

  fControlJetPtPtRelRec          = 0;      
  fControlJetEtPtRelRec          = 0;      
  fControlJetMassPtRelRec        = 0;      
  fControlJetPtPtRelRecB         = 0;      
  fControlJetEtPtRelRecB         = 0;      
  fControlJetMassPtRelRecB       = 0;      
  fControlJetPtPtRelRecC         = 0;      
  fControlJetEtPtRelRecC         = 0;      
  fControlJetMassPtRelRecC       = 0;      
  fControlJetPtPtRelRecLF        = 0;      
  fControlJetEtPtRelRecLF        = 0;      
  fControlJetMassPtRelRecLF      = 0;      

  fControlPtRelJetQuark          = 0;
  fControlPtRelJetQuark45        = 0;
  fControlPtRelJetQuark56        = 0;
  fControlPtRelJetQuark6         = 0;
  fControlPtRelJetBQuark         = 0;
  fControlPtRelJetBQuark45       = 0;
  fControlPtRelJetBQuark56       = 0;
  fControlPtRelJetBQuark6        = 0;
  fControlPtRelJetCQuark         = 0;
  fControlPtRelJetCQuark45       = 0;
  fControlPtRelJetCQuark56       = 0;
  fControlPtRelJetCQuark6        = 0;
  fControlPtRelJetLFQuark        = 0;
  fControlPtRelJetLFQuark45      = 0;
  fControlPtRelJetLFQuark56      = 0;
  fControlPtRelJetLFQuark6       = 0;

  // fake muon histograms

  fFakeHadronAllPt              = 0;
  fFakeHadronAllEta_lowPt       = 0;
  fFakeHadronAllPhi_lowPt       = 0;
  fFakeHadronAllEta_highPt      = 0;
  fFakeHadronAllPhi_highPt      = 0;

  fFakeHadronPionPt              = 0;
  fFakeHadronPionEta_lowPt       = 0;
  fFakeHadronPionPhi_lowPt       = 0;
  fFakeHadronPionEta_highPt      = 0;
  fFakeHadronPionPhi_highPt      = 0;
  fFakeHadronKaonPt              = 0;
  fFakeHadronKaonEta_highPt      = 0;
  fFakeHadronKaonPhi_highPt      = 0;
  fFakeHadronKaonEta_lowPt       = 0;
  fFakeHadronKaonPhi_lowPt       = 0;

  fFakeProbabilityAllPt         = 0;
  fFakeProbabilityAllEta_lowPt  = 0;
  fFakeProbabilityAllPhi_lowPt  = 0;
  fFakeProbabilityAllEta_highPt = 0;
  fFakeProbabilityAllPhi_highPt = 0;

  fFakeProbabilityPionPt         = 0;
  fFakeProbabilityPionEta_lowPt  = 0;
  fFakeProbabilityPionPhi_lowPt  = 0;
  fFakeProbabilityPionEta_highPt = 0;
  fFakeProbabilityPionPhi_highPt = 0;
  fFakeProbabilityKaonPt         = 0;
  fFakeProbabilityKaonEta_lowPt  = 0;
  fFakeProbabilityKaonPhi_lowPt  = 0;
  fFakeProbabilityKaonEta_highPt = 0;
  fFakeProbabilityKaonPhi_highPt = 0;

  fFakeDecayProbabilityPionPt         = 0;
  fFakeDecayProbabilityPionEta_lowPt  = 0;
  fFakeDecayProbabilityPionPhi_lowPt  = 0;
  fFakeDecayProbabilityPionEta_highPt = 0;
  fFakeDecayProbabilityPionPhi_highPt = 0;
  fFakeDecayProbabilityKaonPt         = 0;
  fFakeDecayProbabilityKaonEta_lowPt  = 0;
  fFakeDecayProbabilityKaonPhi_lowPt  = 0;
  fFakeDecayProbabilityKaonEta_highPt = 0;
  fFakeDecayProbabilityKaonPhi_highPt = 0;

  fFakePunchProbabilityPionPt         = 0;
  fFakePunchProbabilityPionEta_lowPt  = 0;
  fFakePunchProbabilityPionPhi_lowPt  = 0;
  fFakePunchProbabilityPionEta_highPt = 0;
  fFakePunchProbabilityPionPhi_highPt = 0;
  fFakePunchProbabilityKaonPt         = 0;
  fFakePunchProbabilityKaonEta_lowPt  = 0;
  fFakePunchProbabilityKaonPhi_lowPt  = 0;
  fFakePunchProbabilityKaonEta_highPt = 0;
  fFakePunchProbabilityKaonPhi_highPt = 0;


  // create histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GMCs::~GMCs() {
  //
  // GMCs default destructor
  if ( gDebug ) cout << endl << "GMCs::~GMCs dtor called" << endl << endl;

  fMCs->Delete();
  fNMCs = 0;
  delete fMCs;
  fMCMuons->Delete();
  fNMCMuons = 0;
  delete fMCMuons;
//   fMCMuons->Delete();
//   fNMCMuons = 0;
//   delete fMCMuons;
  fMCDIMuons->Delete();
  fNMCDIMuons = 0;
  delete fMCDIMuons;
//   fMCDIMuons2->Delete();
//   fNMCDIMuons2 = 0;
//  delete fMCDIMuons2;
  fMCHJets->Delete();
  fNMCHJets = 0;
  delete fMCHJets;
  fMCHMJets->Delete();
  fNMCHMJets = 0;
  delete fMCHMJets;
  fMCHBJets->Delete();
  fNMCHBJets = 0;
  delete fMCHBJets;
  fMCHBMJets->Delete();
  fNMCHBMJets = 0;
  delete fMCHBMJets;
  fMCPJets->Delete();
  fNMCPJets = 0;
  delete fMCPJets;
  fMCPMJets->Delete();
  fNMCPMJets = 0;
  delete fMCPMJets;

  fMCVertices->Delete();
  fNMCVertices = 0;
  delete fMCVertices;

}

//_____________________________________________________________

Bool_t GMCs::CreateControl() {
  //
  // create control histograms
  if ( gDebug ) cout << endl << "GMCs::CreateControl() called" << endl << endl;

  if ( gCards->GetMcControl() ) {

    Int_t    drbins        = 400;
    Double_t drlow         = 0.;
    Double_t drhigh        = 10.;
//     Int_t    detabins      = 100;
//     Double_t detalow       = 0.;
//     Double_t detahigh      = 6;
//     Int_t    dphibins      = 200;
//     Double_t dphilow       = 0.0;
//     Double_t dphihigh      = TMath::Pi();
//     Int_t    dthetabins    = 100;
//     Double_t dthetalow     = -TMath::Pi();
//     Double_t dthetahigh    = TMath::Pi();

    Int_t    ptbins        = 32;
    Double_t ptlow         = 4.0;
    Double_t pthigh        = 20.0;

    Int_t    ptrelbins     = 50;
    Double_t ptrellow      = 0.;
    Double_t ptrelhigh     = 5.;
    
    Int_t    etbins        = 120;
    Double_t etlow         = 0.;
    Double_t ethigh        = 60.;

    Int_t    jetmassbins   = 20;
    Double_t jetmasslow    = 0;
    Double_t jetmasshigh   = 20.;
    Int_t    weightbins    = 500;
    Int_t    q2bins        = 100;

    fControlJetPtDeltaR = gHistogrammer->TH2DFactory("MC_Control","JetPtDeltaR","p_{T}^{jet} vs. #Delta R between jet and any quark",ptbins,ptlow,pthigh,drbins,drlow,drhigh,"p_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetEtDeltaR = gHistogrammer->TH2DFactory("MC_Control","JetEtDeltaR","E_{T}^{jet} vs. #Delta R between jet and any quark",etbins,etlow,ethigh,drbins,drlow,drhigh,"E_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetMassDeltaR = gHistogrammer->TH2DFactory("MC_Control","JetMassDeltaR","m^{jet} vs. #Delta R between jet and any quark",jetmassbins,jetmasslow,jetmasshigh,drbins,drlow,drhigh,"m^{jet} [GeV]","#Delta R","Events");
    fControlJetPtDeltaRB = gHistogrammer->TH2DFactory("MC_Control","JetPtDeltaRB","p_{T}^{jet} vs. #Delta R between jet and b-quark",ptbins,ptlow,pthigh,drbins,drlow,drhigh,"p_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetEtDeltaRB = gHistogrammer->TH2DFactory("MC_Control","JetEtDeltaRB","E_{T}^{jet} vs. #Delta R between jet and b-quark",etbins,etlow,ethigh,drbins,drlow,drhigh,"E_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetMassDeltaRB = gHistogrammer->TH2DFactory("MC_Control","JetMassDeltaRB","m^{jet} vs. #Delta R between jet and b-quark",jetmassbins,jetmasslow,jetmasshigh,drbins,drlow,drhigh,"m^{jet} [GeV]","#Delta R","Events");
    fControlJetPtDeltaRC = gHistogrammer->TH2DFactory("MC_Control","JetPtDeltaRC","p_{T}^{jet} vs. #Delta R between jet and c-quark",ptbins,ptlow,pthigh,drbins,drlow,drhigh,"p_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetEtDeltaRC = gHistogrammer->TH2DFactory("MC_Control","JetEtDeltaRC","E_{T}^{jet} vs. #Delta R between jet and c-quark",etbins,etlow,ethigh,drbins,drlow,drhigh,"E_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetMassDeltaRC = gHistogrammer->TH2DFactory("MC_Control","JetMassDeltaRC","m^{jet} vs. #Delta R between jet and c-quark",jetmassbins,jetmasslow,jetmasshigh,drbins,drlow,drhigh,"m^{jet} [GeV]","#Delta R","Events");
    fControlJetPtDeltaRLF = gHistogrammer->TH2DFactory("MC_Control","JetPtDeltaRLF","p_{T}^{jet} vs. #Delta R between jet and light quark",ptbins,ptlow,pthigh,drbins,drlow,drhigh,"p_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetEtDeltaRLF = gHistogrammer->TH2DFactory("MC_Control","JetEtDeltaRLF","E_{T}^{jet} vs. #Delta R between jet and light quark",etbins,etlow,ethigh,drbins,drlow,drhigh,"E_{T}^{jet} [GeV]","#Delta R","Events");
    fControlJetMassDeltaRLF = gHistogrammer->TH2DFactory("MC_Control","JetMassDeltaRLF","m^{jet} vs. #Delta R between jet and light quark",jetmassbins,jetmasslow,jetmasshigh,drbins,drlow,drhigh,"m^{jet} [GeV]","#Delta R","Events");

    fControlJetPtPtRelRec = gHistogrammer->TH2DFactory("MC_Control","JetPtPtRelRec","p_{T}^{jet} vs. p_{T}^{rel,rec} (any quark)",ptbins,ptlow,pthigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetEtPtRelRec = gHistogrammer->TH2DFactory("MC_Control","JetEtPtRelRec","E_{T}^{jet} vs. p_{T}^{rel,rec} (any quark)",etbins,etlow,ethigh,ptrelbins,ptrellow,ptrelhigh,"E_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetMassPtRelRec = gHistogrammer->TH2DFactory("MC_Control","JetMassPtRelRec","m^{jet} vs. p_{T}^{rel,rec} (any quark)",jetmassbins,jetmasslow,jetmasshigh,ptrelbins,ptrellow,ptrelhigh,"m^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetPtPtRelRecB = gHistogrammer->TH2DFactory("MC_Control","JetPtPtRelRecB","p_{T}^{jet} vs. p_{T}^{rel,rec} (b-quark)",ptbins,ptlow,pthigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetEtPtRelRecB = gHistogrammer->TH2DFactory("MC_Control","JetEtPtRelRecB","E_{T}^{jet} vs. p_{T}^{rel,rec} (b-quark)",etbins,etlow,ethigh,ptrelbins,ptrellow,ptrelhigh,"E_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetMassPtRelRecB = gHistogrammer->TH2DFactory("MC_Control","JetMassPtRelRecB","m^{jet} vs. p_{T}^{rel,rec} (b-quark)",jetmassbins,jetmasslow,jetmasshigh,ptrelbins,ptrellow,ptrelhigh,"m^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetPtPtRelRecC = gHistogrammer->TH2DFactory("MC_Control","JetPtPtRelRecC","p_{T}^{jet} vs. p_{T}^{rel,rec} (c-quark)",ptbins,ptlow,pthigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetEtPtRelRecC = gHistogrammer->TH2DFactory("MC_Control","JetEtPtRelRecC","E_{T}^{jet} vs. p_{T}^{rel,rec} (c-quark)",etbins,etlow,ethigh,ptrelbins,ptrellow,ptrelhigh,"E_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetMassPtRelRecC = gHistogrammer->TH2DFactory("MC_Control","JetMassPtRelRecC","m^{jet} vs. p_{T}^{rel,rec} (c-quark)",jetmassbins,jetmasslow,jetmasshigh,ptrelbins,ptrellow,ptrelhigh,"m^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetPtPtRelRecLF = gHistogrammer->TH2DFactory("MC_Control","JetPtPtRelRecLF","p_{T}^{jet} vs. p_{T}^{rel,rec} (light quark)",ptbins,ptlow,pthigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetEtPtRelRecLF = gHistogrammer->TH2DFactory("MC_Control","JetEtPtRelRecLF","E_{T}^{jet} vs. p_{T}^{rel,rec} (light quark)",etbins,etlow,ethigh,ptrelbins,ptrellow,ptrelhigh,"E_{T}^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");
    fControlJetMassPtRelRecLF = gHistogrammer->TH2DFactory("MC_Control","JetMassPtRelRecLF","m^{jet} vs. p_{T}^{rel,rec} (light quark)",jetmassbins,jetmasslow,jetmasshigh,ptrelbins,ptrellow,ptrelhigh,"m^{jet} [GeV]","p_{T}^{rel,rec} [GeV]","Events");

    fControlPtRelJetQuark = gHistogrammer->TH2DFactory("MC_Control","PtRelJetQuark","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/any quark",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/any quark [GeV]","Events");
    fControlPtRelJetQuark45 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetQuark45","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/any quark for 4 GeV #leq p_{T}^{jet} < 5 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/any quark [GeV]","Events");
    fControlPtRelJetQuark56 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetQuark56","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/any quark for 5 GeV #leq p_{T}^{jet} < 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/any quark [GeV]","Events");
    fControlPtRelJetQuark6 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetQuark6","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/any quark for p_{T}^{jet} #geq 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/any quark [GeV]","Events");
    fControlPtRelJetBQuark = gHistogrammer->TH2DFactory("MC_Control","PtRelJetBQuark","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/b-quark",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/b-quark [GeV]","Events");
    fControlPtRelJetBQuark45 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetBQuark45","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/b-quark for 4 GeV #leq p_{T}^{jet} < 5 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/b-quark [GeV]","Events");
    fControlPtRelJetBQuark56 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetBQuark56","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/b-quark for 5 GeV #leq p_{T}^{jet} < 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/b-quark [GeV]","Events");
    fControlPtRelJetBQuark6 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetBQuark6","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/b-quark for p_{T}^{jet} #geq 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/b-quark [GeV]","Events");
    fControlPtRelJetCQuark = gHistogrammer->TH2DFactory("MC_Control","PtRelJetCQuark","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/c-quark",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/c-quark [GeV]","Events");
    fControlPtRelJetCQuark45 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetCQuark45","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/c-quark for 4 GeV #leq p_{T}^{jet} < 5 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/c-quark [GeV]","Events");
    fControlPtRelJetCQuark56 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetCQuark56","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/c-quark for 5 GeV #leq p_{T}^{jet} < 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/c-quark [GeV]","Events");
    fControlPtRelJetCQuark6 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetCQuark6","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/c-quark for p_{T}^{jet} #geq 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/c-quark [GeV]","Events");
    fControlPtRelJetLFQuark = gHistogrammer->TH2DFactory("MC_Control","PtRelJetLFQuark","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/light quark",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/light quark [GeV]","Events");
    fControlPtRelJetLFQuark45 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetLFQuark45","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/light quark for 4 GeV #leq p_{T}^{jet} < 5 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/light quark [GeV]","Events");
    fControlPtRelJetLFQuark56 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetLFQuark56","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/light quark for 5 GeV #leq p_{T}^{jet} < 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/light quark [GeV]","Events");
    fControlPtRelJetLFQuark6 = gHistogrammer->TH2DFactory("MC_Control","PtRelJetLFQuark6","p_{T}^{rel} #mu/jet vs. p_{T}^{rel} #mu/light quark for p_{T}^{jet} #geq 6 GeV",ptrelbins,ptrellow,ptrelhigh,ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} #mu/jet [GeV]","p_{T}^{rel} #mu/light quark [GeV]","Events");
    fControlMCWeightsQ2 = gHistogrammer->TH2DFactory("MC_Control","MCWeightQ2","Weight vs. Q^{2}, lf MC",weightbins,0.,500.,q2bins,0.,5000.,"Weight","Q^{2} [GeV^{2}]","Events");
    fControlMCWeights = gHistogrammer->TH1DFactory("MC_Control","MCWeight","Weight, lf MC",weightbins,0.,500.,"Weight","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::FillControl() {
  //
  // fill control histograms
  if ( gDebug ) cout << endl << "GMCs::FillControl() called" << endl << endl;

  if ( gCards->GetMcControl() ) {

    for ( Int_t i = 0; i < gMuons->GetNMuons(); ++i ) {
      GMuon *muon = gMuons->GetMuon(i);
      Int_t jetid = muon->GetJetID();
      fControlMCWeightsQ2->Fill(gMCs->GetWeight(),gData->Getmc_q2(),1.);
      fControlMCWeights->Fill(gMCs->GetWeight(),1.);
      if (  jetid > 0) {
	GJet *jet = gJets->GetJetWithID(jetid);
	if ( jet != 0 ) {
	  GMC *quark = muon->GetMCQuark();

	  if ( quark != 0 ) {

	    // any quark plots
	    if ( (quark->GetType() == kUp) || 
		 (quark->GetType() == kAntiUp) || 
		 (quark->GetType() == kDown) || 
		 (quark->GetType() == kAntiDown) || 
		 (quark->GetType() == kCharm) || 
		 (quark->GetType() == kAntiCharm) || 
		 (quark->GetType() == kStrange) || 
		 (quark->GetType() == kAntiStrange) || 
		 (quark->GetType() == kBeauty) || 
		 (quark->GetType() == kAntiBeauty) || 
		 (quark->GetType() == kTop) || 
		 (quark->GetType() == kAntiTop) ) {
	      fControlJetPtDeltaR->Fill(jet->Pt(),quark->DeltaR(*jet));
	      fControlJetEtDeltaR->Fill(jet->Et(),quark->DeltaR(*jet));

	      fControlJetPtPtRelRec->Fill(jet->Pt(),muon->Pt(jet->Vect()));
	      fControlJetEtPtRelRec->Fill(jet->Et(),muon->Pt(jet->Vect()));

	      fControlJetMassDeltaR->Fill(jet->M(),quark->DeltaR(*jet));
	      fControlJetMassPtRelRec->Fill(jet->M(),muon->Pt(jet->Vect()));

	      fControlPtRelJetQuark->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (4 <= jet->Pt()) && (jet->Pt() < 5)) 
		fControlPtRelJetQuark45->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (5 <= jet->Pt()) && (jet->Pt() < 6)) 
		fControlPtRelJetQuark56->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( jet->Pt() >= 6 ) 
		fControlPtRelJetQuark6->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	    }

	    // b-quark plots
	    if ( (quark->GetType() == kBeauty) || 
		 (quark->GetType() == kAntiBeauty) ) {
	      fControlJetPtDeltaRB->Fill(jet->Pt(),quark->DeltaR(*jet));
	      fControlJetEtDeltaRB->Fill(jet->Et(),quark->DeltaR(*jet));

	      fControlJetPtPtRelRecB->Fill(jet->Pt(),muon->Pt(jet->Vect()));
	      fControlJetEtPtRelRecB->Fill(jet->Et(),muon->Pt(jet->Vect()));

	      fControlJetMassDeltaRB->Fill(jet->M(),quark->DeltaR(*jet));
	      fControlJetMassPtRelRecB->Fill(jet->M(),muon->Pt(jet->Vect()));

	      fControlPtRelJetBQuark->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (4 <= jet->Pt()) && (jet->Pt() < 5)) 
		fControlPtRelJetBQuark45->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (5 <= jet->Pt()) && (jet->Pt() < 6)) 
		fControlPtRelJetBQuark56->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( jet->Pt() >= 6 ) 
		fControlPtRelJetBQuark6->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	    }

	    // c-quark plots
	    if ( (quark->GetType() == kCharm) || 
		 (quark->GetType() == kAntiCharm) ) {
	      fControlJetPtDeltaRC->Fill(jet->Pt(),quark->DeltaR(*jet));
	      fControlJetEtDeltaRC->Fill(jet->Et(),quark->DeltaR(*jet));

	      fControlJetPtPtRelRecC->Fill(jet->Pt(),muon->Pt(jet->Vect()));
	      fControlJetEtPtRelRecC->Fill(jet->Et(),muon->Pt(jet->Vect()));

	      fControlJetMassDeltaRC->Fill(jet->M(),quark->DeltaR(*jet));
	      fControlJetMassPtRelRecC->Fill(jet->M(),muon->Pt(jet->Vect()));

	      fControlPtRelJetCQuark->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (4 <= jet->Pt()) && (jet->Pt() < 5)) 
		fControlPtRelJetCQuark45->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (5 <= jet->Pt()) && (jet->Pt() < 6)) 
		fControlPtRelJetCQuark56->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( jet->Pt() >= 6 ) 
		fControlPtRelJetCQuark6->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	    }

	    // light quark plots
	    if ( (quark->GetType() == kUp) || 
		 (quark->GetType() == kAntiUp) || 
		 (quark->GetType() == kDown) || 
		 (quark->GetType() == kAntiDown) ) {
	      fControlJetPtDeltaRLF->Fill(jet->Pt(),quark->DeltaR(*jet));
	      fControlJetEtDeltaRLF->Fill(jet->Et(),quark->DeltaR(*jet));

	      fControlJetPtPtRelRecLF->Fill(jet->Pt(),muon->Pt(jet->Vect()));
	      fControlJetEtPtRelRecLF->Fill(jet->Et(),muon->Pt(jet->Vect()));

	      fControlJetMassDeltaRLF->Fill(jet->M(),quark->DeltaR(*jet));
	      fControlJetMassPtRelRecLF->Fill(jet->M(),muon->Pt(jet->Vect()));

	      fControlPtRelJetLFQuark->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (4 <= jet->Pt()) && (jet->Pt() < 5)) 
		fControlPtRelJetLFQuark45->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( (5 <= jet->Pt()) && (jet->Pt() < 6)) 
		fControlPtRelJetLFQuark56->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	      if ( jet->Pt() >= 6 ) 
		fControlPtRelJetLFQuark6->Fill(muon->Pt(jet->Vect()),muon->Pt(quark->Vect()));
	    }

	  }
	}
      }
    }

  }

  return kTRUE;
}

//_____________________________________________________________

GMCVertex* GMCs::GetMCVertex(Int_t index) {
  //
  // return MC object with vertex index if object exists
  if ( gDebug ) cout << endl << "GMCs::GetMCVertex called" << endl << endl;

  GMCVertex* mcvertex = 0;

  for ( Int_t i = 0; i < fNMCVertices; i++ ) {
    mcvertex = ((GMCVertex*)(fMCVertices->At(i)));
    if ( mcvertex->GetVertexID() == index )
      return mcvertex;
  }

  return 0;
}

//_____________________________________________________________

GMC* GMCs::GetMC(Int_t index) {
  //
  // return MC object with fmckinid index if object exists
  if ( gDebug ) cout << endl << "GMCs::GetMC called" << endl << endl;

  GMC* mc = 0;

  for ( Int_t i = 0; i < fNMCs; i++ ) {
    mc = ((GMC*)(fMCs->At(i)));
    if ( mc->GetFMCKINID() == index ) {
      return mc;
    }
  }

  return 0;
}

//_____________________________________________________________

GMC* GMCs::GetMC(Int_t partid, Double_t px, Double_t py, Double_t pz, Double_t e) {
  //
  // return mc object 
  if ( gDebug ) cout << endl << "GMCs::GetMC called" << endl << endl;

  GMC* mc = 0;

//   for ( Int_t i = 0; i < fNMCs; i++ ) {
//     mc = ((GMC*)(fMCs->At(i)));
//     if ( (mc->GetPartID() == partid) && (mc->Px() == px) && (mc->Py() == py) && (mc->Pz() == pz) && (mc->E() == e) )
//       return mc;
//   }
// 050604: reversed order of finding MC particle (to get the closest b 
// quark to the muon, not the one closest to the hard scatter):
  for ( Int_t i = fNMCs-1; i >= 0; i-- ) {
    mc = ((GMC*)(fMCs->At(i)));
    if ( (mc->GetPartID() == partid) && (mc->Px() == px) && (mc->Py() == py) && (mc->Pz() == pz) && (mc->E() == e) )
      return mc;
  }

  return 0;
}

//_____________________________________________________________

Bool_t GMCs::Reset() {
  //
  // reset tracks object on event by event basis
  if ( gDebug ) cout << endl << "GMCs::Reset called" << endl << endl;

  // reset clonesarray
  fMCs->Clear();
  fNMCs = 0;
  fMCMuons->Clear();
  fNMCMuons = 0;
  fMCDIMuons->Clear();
  fNMCDIMuons = 0;
//   fMCDIMuons2->Clear();
//   fNMCDIMuons2 = 0;
  fMCHJets->Clear();
  fNMCHJets = 0;
  fMCHMJets->Clear();
  fNMCHMJets = 0;
  fMCHBJets->Clear();
  fNMCHBJets = 0;
  fMCHBMJets->Clear();
  fNMCHBMJets = 0;
  fMCPJets->Clear();
  fNMCPJets = 0;
  fMCPMJets->Clear();
  fNMCPMJets = 0;

  fMCVertices->Clear();
  fNMCVertices = 0;
  // reset jet cut flags
  fMCHJetPtACut   = kFALSE;
  fMCHJetPtBCut   = kFALSE;
  fMCHMJetPtACut  = kFALSE;
  fMCHMJetPtBCut  = kFALSE;
  fMCHBJetPtACut  = kFALSE;
  fMCHBJetPtBCut  = kFALSE;
  fMCHBMJetPtACut = kFALSE;
  fMCHBMJetPtBCut = kFALSE;
  fMCPJetPtACut   = kFALSE;
  fMCPJetPtBCut   = kFALSE;
  fMCPMJetPtACut  = kFALSE;
  fMCPMJetPtBCut  = kFALSE;

  // reset variables
  fIndex1                 = -99;
  fIndex2                 = -99;
  fXGammaJets             = -9999.99;
  fXGamma                 = -9999.99;
  fXGammaJets_zufo        = -9999.99;
  fMJets                  = -9999.99;
  fDPhiJets               = -9999.99;
  fDRJets                 = -9999.99;
  fPtJets                 = -9999.99;
  fCosThetaStarJets       = -9999.99;

  fPartIndex1                 = -99;
  fPartIndex2                 = -99;
  fPartXGammaJets             = -9999.99;
  fPartXGamma                 = -9999.99;
  fPartXGammaJets_zufo        = -9999.99;
  fPartMJets                  = -9999.99;
  fPartDPhiJets               = -9999.99;
  fPartDRJets                 = -9999.99;
  fPartPtJets                 = -9999.99;
  fPartCosThetaStarJets       = -9999.99;

  // reset cut flags
  fQ2Cut             = kFALSE;
  fQ2SelectionCut    = kFALSE;
  fYCut              = kFALSE;
  fMuonCuts          = kFALSE;
  fMCDIMuonCuts          = kFALSE;

  // reset variables
  fOwnFMCKINID    = 10000;
  fHeavyFlavours  = kFALSE;

  return kTRUE;
} 

//_____________________________________________________________

Bool_t GMCs::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GMCs::Do() called" << endl << endl;

  // fill clonesarray with tracks
  Fill();

  CheckAllCuts();
  CalcMJCosThetaStarhbmjets();
  CalcMJCosThetaStarpmjets();
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::Fill() {
  //
  // fill clonesarray
  if ( gDebug ) cout << endl << "GMCs::Fill() called" << endl << endl;
  Double_t cutonvalue = 0;

  // fill mc objects from own mc block (i.e. fmckin block assebbled by Achim G.), if this is activated
  // look in already existing entries if entry exsist, than only replace fmckinid

  if ( gCards->GetMCOwn() ) {
    TClonesArray &mcs = *fMCs;
    //    TClonesArray &mcdimuons2 = *fMCDIMuons2; 
    for ( Int_t i = 0; i < gData->Getfmck_nstor(); ++i ) {
      new(mcs[fNMCs++]) GMC(gData->Getfmck_id(i),gData->Getfmck_prt(i),gData->Getfmck_px(i),gData->Getfmck_py(i),gData->Getfmck_pz(i),gData->Getfmck_e(i),
			    //			    gData->Getfmck_daug(i),gData->Getfmck_prat(i),gData->Getfmck_impar(i),gData->Getfmck_dsignif(i),
			    //			    gData->Getfmck_impar2(i),gData->Getfmck_dsignif2(i));
			    gData->Getfmck_daug(i),gData->Getfmck_prat(i),gData->Getfmck_impar(i),gData->Getfmck_impar2(i));
    }
    TClonesArray &mcvertices = *fMCVertices;
    for ( Int_t i = 0; i < gData->Getfmvtx_nstor(); ++i ) {
      new(mcvertices[fNMCVertices++]) GMCVertex(gData->Getfmvtx_id(i),gData->Getfmvtx_r(i,0),gData->Getfmvtx_r(i,1),gData->Getfmvtx_r(i,2),gData->Getfmvtx_time(i));
    }
    CheckMothersAndVertices();
  }

  // fill mc objects from Ursula's fmckin block. start:
  if ( gCards->GetFMCK() && !(gCards->GetMCOwn()) ) {
    TClonesArray &mcs = *fMCs;
    Int_t nmax = gData->Getnpart();
    if(nmax >= 511) {
      cout << "GMCs::Fill ERROR nmax = " << nmax << endl;
      nmax = 511;}
    for ( Int_t i = 0; i < nmax-1; ++i ) {
    new(mcs[fNMCs++]) GMC(gData->Getpart_id(i),gData->Getpart_prt(i),gData->Getpart_p(i,0),gData->Getpart_p(i,1),gData->Getpart_p(i,2),gData->Getpart_p(i,3));
    }
    
  }
  else if (gCards->GetFMCK() && gCards->GetMCOwn()){ 
    cout << "FMCK MC card and MCOwn card set, MCOwn information will be filled" << endl;
   }

  // fill mc objects from Ursula's fmckin block. end.

  if ( gCards->GetMCOwnJets() ) {
    TClonesArray &jets = *fMCHJets;
    Int_t index1 = -99;
    Int_t index2 = -99;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;
    for ( Int_t i = 0; i < gData->Getnhjets(); i++ ) {
      GJet *jet = new(jets[fNMCHJets++]) GJet(i+1,gData->Getpxhjet(i),gData->Getpyhjet(i),gData->Getpzhjet(i),gData->Getehjet(i),kMCJet,gData->Getkt_etjetbreit(i));
      if ( jet != 0 ) {
	// decide by card whether to cut on Et or Pt in lab or breitframe
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cutonvalue = jet->GetEtbreit();
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR in CARD! Cut on Pt in Breitframe not implemented!!!" << endl;
	  }
	  else {
	    cutonvalue = jet->Pt();
	  }
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  index2 = index1;
	  pt2 = pt1;
	  index1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  index2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
    
    // set types of first and second jet if jets fulfill cuts
    if ( pt1 >= gCards->GetJETPtACut() ) {
      GJet *jet = GetMCHJetWithID(index1);
      jet->SetType(kMCFirst);
      fMCHJetPtACut = kTRUE;
    }
    if ( pt2 >= gCards->GetJETPtBCut() ) {
      GJet *jet = GetMCHJetWithID(index2);
      jet->SetType(kMCSecond);
      fMCHJetPtBCut = kTRUE;
    }
  }

  if ( gCards->GetMCOwnJets() ) {
    TClonesArray &jets = *fMCHMJets;
    Int_t index1 = -99;
    Int_t index2 = -99;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;
    for ( Int_t i = 0; i < gData->Getnhmjets(); i++ ) {
      GJet *jet = new(jets[fNMCHMJets++]) GJet(i+1,gData->Getpxhmjet(i),gData->Getpyhmjet(i),gData->Getpzhmjet(i),gData->Getehmjet(i),kMCJet,gData->Getkt_etjetbreit(i));
      if ( jet != 0 ) {
	// decide by card whether to cut on Et or Pt in lab or breitframe
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cutonvalue = jet->GetEtbreit();
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR in CARD! Cut on Pt in Breitframe not implemented!!!" << endl;
	  }
	  else {
	    cutonvalue = jet->Pt();
	  }
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  index2 = index1;
	  pt2 = pt1;
	  index1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  index2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
    
    // set types of first and second jet if jets fulfill cuts
    if ( pt1 >= gCards->GetJETPtACut() ) {
      GJet *jet = GetMCHMJetWithID(index1);
      jet->SetType(kMCFirst);
      fMCHMJetPtACut = kTRUE;
    }
    if ( pt2 >= gCards->GetJETPtBCut() ) {
      GJet *jet = GetMCHMJetWithID(index2);
      jet->SetType(kMCSecond);
      fMCHMJetPtBCut = kTRUE;
    }
  }

  if ( gCards->GetMCOwnJets() ) {
    TClonesArray &jets = *fMCHBJets;
    Int_t index1 = -99;
    Int_t index2 = -99;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;
    for ( Int_t i = 0; i < gData->Getnhbjets(); i++ ) {
      GJet *jet = new(jets[fNMCHBJets++]) GJet(i+1,gData->Getpxhbjet(i),gData->Getpyhbjet(i),gData->Getpzhbjet(i),gData->Getehbjet(i),kMCJet,gData->Getkt_etjetbreit(i));
      if ( jet != 0 ) {
	// decide by card whether to cut on Et or Pt in lab or breitframe
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cutonvalue = jet->GetEtbreit();
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR in CARD! Cut on Pt in Breitframe not implemented!!!" << endl;
	  }
	  else {
	    cutonvalue = jet->Pt();
	  }
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  index2 = index1;
	  pt2 = pt1;
	  index1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  index2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
    
    // set types of first and second jet if jets fulfill cuts
    if ( pt1 >= gCards->GetJETPtACut() ) {
      GJet *jet = GetMCHBJetWithID(index1);
      jet->SetType(kMCFirst);
      fMCHBJetPtACut = kTRUE;
    }
    if ( pt2 >= gCards->GetJETPtBCut() ) {
      GJet *jet = GetMCHBJetWithID(index2);
      jet->SetType(kMCSecond);
      fMCHBJetPtBCut = kTRUE;
    }
  }

  if ( gCards->GetMCOwnJets() ) {
    TClonesArray &jets = *fMCHBMJets;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;
    for ( Int_t i = 0; i < gData->Getnhbmjets(); i++ ) {
      GJet *jet = new(jets[fNMCHBMJets++]) GJet(i+1,gData->Getpxhbmjet(i),gData->Getpyhbmjet(i),gData->Getpzhbmjet(i),gData->Getehbmjet(i),kMCJet,gData->Getkt_etjetbreit(i));

      if ( jet != 0 ) {

	// decide by card whether to cut on Et or Pt in lab or breitframe
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cutonvalue = jet->GetEtbreit();
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR in CARD! Cut on Pt in Breitframe not implemented!!!" << endl;
	  }
	  else {
	    cutonvalue = jet->Pt();
	  }
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  fIndex2 = fIndex1;
	  pt2 = pt1;
	  fIndex1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  fIndex2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
    
    // set types of first and second jet if jets fulfill cuts
    if ( pt1 >= gCards->GetJETPtACut() ) {
      GJet *jet = GetMCHBMJetWithID(fIndex1);
      jet->SetType(kMCFirst);
      fMCHBMJetPtACut = kTRUE;
    }
    if ( pt2 >= gCards->GetJETPtBCut() ) {
      GJet *jet = GetMCHBMJetWithID(fIndex2);
      jet->SetType(kMCSecond);
      fMCHBMJetPtBCut = kTRUE;
    }
  }

  // calculate true properties
  Calc(fIndex1,fIndex2);

  if ( gCards->GetMCOwnJets() ) {
    TClonesArray &jets = *fMCPJets;
    Int_t index1 = -99;
    Int_t index2 = -99;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;
    for ( Int_t i = 0; i < gData->Getnpjets(); i++ ) {
      GJet *jet = new(jets[fNMCPJets++]) GJet(i+1,gData->Getpxpjet(i),gData->Getpypjet(i),gData->Getpzpjet(i),gData->Getepjet(i),kMCJet,gData->Getkt_etjetbreit(i));
      if ( jet != 0 ) {
	// decide by card whether to cut on Et or Pt in lab or breitframe
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cutonvalue = jet->GetEtbreit();
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR in CARD! Cut on Pt in Breitframe not implemented!!!" << endl;
	  }
	  else {
	    cutonvalue = jet->Pt();
	  }
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  index2 = index1;
	  pt2 = pt1;
	  index1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  index2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
    
    // set types of first and second jet if jets fulfill cuts
    if ( pt1 >= gCards->GetJETPtACut() ) {
      GJet *jet = GetMCPJetWithID(index1);
      jet->SetType(kMCFirst);
      fMCPJetPtACut = kTRUE;
    }
    if ( pt2 >= gCards->GetJETPtBCut() ) {
      GJet *jet = GetMCPJetWithID(index2);
      jet->SetType(kMCSecond);
      fMCPJetPtBCut = kTRUE;
    }
  }

  if ( gCards->GetMCOwnJets() ) {
    TClonesArray &jets = *fMCPMJets;
    fPartIndex1 = -99;
    fPartIndex2 = -99;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;
    for ( Int_t i = 0; i < gData->Getnpmjets(); i++ ) {
      GJet *jet = new(jets[fNMCPMJets++]) GJet(i+1,gData->Getpxpmjet(i),gData->Getpypmjet(i),gData->Getpzpmjet(i),gData->Getepmjet(i),kMCJet,gData->Getkt_etjetbreit(i));
      if ( jet != 0 ) {
	//	cout << "index " << i << " jet->Px() " << jet->Px() <<   "jet->Py() " << jet->Py() <<   "jet->Pz() " << jet->Pz() <<   "jet->E() " << jet->E() <<  endl;
	// decide by card whether to cut on Et or Pt in lab or breitframe
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cout << "breitframe pmjets" << endl;
	    cutonvalue = jet->GetEtbreit();
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR in CARD! Cut on Pt in Breitframe not implemented!!!" << endl;
	  }
	  else {
	    cutonvalue = jet->Pt();
	  }
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  fPartIndex2 = fPartIndex1;
	  pt2 = pt1;
	  fPartIndex1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  fPartIndex2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
    
    // set types of first and second jet if jets fulfill cuts
    if ( pt1 >= gCards->GetJETPtACut() ) {
      GJet *jet = GetMCPMJetWithID(fPartIndex1);
      jet->SetType(kMCFirst);
      fMCPMJetPtACut = kTRUE;
    }
    if ( pt2 >= gCards->GetJETPtBCut() ) {
      GJet *jet = GetMCPMJetWithID(fPartIndex2);
      jet->SetType(kMCSecond);
      fMCPMJetPtBCut = kTRUE;
    }
        if (fPartIndex1!=0 && fPartIndex2!=0)
	  CalcPart(fPartIndex1,fPartIndex2);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CheckMothersAndVertices() {
  //
  // check mother pointers of echt mc-object in array
  if ( gDebug ) cout << endl << "GMCs::CheckMothersAndVertices() called" << endl << endl;

  GMC *mc = 0;

  for ( Int_t i = 0; i < fNMCs; i++ ) {
    mc = ((GMC*)(fMCs->At(i)));
    mc->SetMother(GetMC(mc->GetMotherID()));
    mc->SetVertex(GetMCVertex(mc->GetProducedAt()));
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CheckHeavyFlavours(GMC *mc) {
  //
  // look for heavy flavours in list
  if ( gDebug ) cout << endl << "GMCs::CheckHeavyFlavours() called" << endl << endl;

  if ( mc->IsHeavyFlavourQuark() ) {
    fHeavyFlavours = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CheckQ2Cut() {
  //
  // check cut on true Q2
  if ( gDebug ) cout << endl << "GMCs::CheckQ2Cut() called" << endl << endl;
  
  if (( gData->Getfmck_q2() <= gCards->GetMCQ2Cut() ) && ( gData->Getfmck_q2() >= gCards->GetMCLowQ2Cut() ))
    fQ2Cut = kTRUE;
  else
    fQ2Cut = kFALSE;
  
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMCs::CheckQ2SelectionCut() {
  //
  // check cut on true Q2
  if ( gDebug ) cout << endl << "GMCs::CheckQ2SelectionCut() called" << endl << endl;
  
  if (gCards->GetMCQ2SelectionCut() > 0.) {
    if (gCards->GetMCQ2LowCut() ){ 
      if ( gData->Getmc_q2() >= gCards->GetMCQ2SelectionCut())
	fQ2SelectionCut = kTRUE;
      else
	fQ2SelectionCut = kFALSE;
    }
    else
      if ( gData->Getmc_q2() <= gCards->GetMCQ2SelectionCut())
	fQ2SelectionCut = kTRUE;
      else
	fQ2SelectionCut = kFALSE;
  }
  else 
    fQ2SelectionCut = kTRUE;
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CheckYCut() {
  //
  // check cut on true y
  if ( gDebug ) cout << endl << "GMCs::CheckYCut() called" << endl << endl;

  if ( (gData->Getmc_y() >= gCards->GetMCYLowCut()) && (gData->Getmc_y() <= gCards->GetMCYHighCut()) )
    fYCut = kTRUE;
  else
    fYCut = kFALSE;
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CheckAllCuts() {
  //
  // check all cuts
  //
  // MCs object is first in list of GPhysObjects and will be executed first per event
  // if list of MC objects is changed afterwards by other objects (gMuons)
  // call this function again to check for cuts with updated list
  if ( gDebug ) cout << endl << "GMCs::CheckAllCuts() called" << endl << endl;
  
  // reset cut flags for case that check of cuts os called from physobj later in the physobj-array in GAnalysis
  
  //reset cut flags
  fQ2Cut             = kFALSE;
  fQ2SelectionCut    = kFALSE;
  fYCut              = kFALSE;
  fMuonCuts          = kFALSE;
  fMCDIMuonCuts      = kFALSE;
  fHeavyFlavours     = kFALSE;
  
  CheckQ2Cut();
  
  CheckQ2SelectionCut();
  
  CheckYCut();
  
  //Oli sacht: Mach dir das b quark hier richtig.
  GMC *mc_find_b_1  = 0;
  GMC *mc_find_b_2  = 0;
  GMC *mc_find_b_mubuffer  = 0;
  //  Bool_t outputtit = kFALSE;
  GMC *mc_iterator1  = 0;
  
  GMC *mc  = 0;
  GMC *mc2 = 0;
  GDIMuon *mcdimuon = 0;
  TClonesArray &mcdimuons = *fMCDIMuons; 
  
  // Reset Dimuon array here, as they are not filled in Fill but here (after gmuon mc info has been added to the GMCs array)
  fMCDIMuons->Clear();
  fNMCDIMuons = 0;
  
//   cout<<"starting to fill mcdimuons for event: "<<gData->Geteventnr()<<endl;
  for ( Int_t i = 0; i < fNMCs; i++ ) {
    mc = ((GMC*)(fMCs->At(i)));
    // all true particles  in fmcs

    // ingo: create mcdimuons HERE! and then check cuts
    if( mc->GetPartID() == 25 || mc->GetPartID() == 26 ) {// only start mcdimuon finding if 1st particle is a muon
      //       cout<<"For muon with FMCKID: "<<mc->GetFMCKINID()<<" and PartID: "<<mc->GetPartID()<<endl;
      
      // find the correct b quark (GMuon quark info is sometimes corrupted) for the muon here:
      mc_find_b_1 = mc;
      //        if(mc->GetFMCKINID() < 0 ){
      //  	cout<<endl<<"Negative FMCKINID outside correction! r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" FMCKID: "<<mc->GetFMCKINID()<<endl;
      //  	outputtit = kTRUE;
      //        }
      if( ! mc->GetMuonBQuark() ) {
	if( mc->GetMuonBQuark() != 0 ) mc_find_b_mubuffer = mc; // this line if if above is commented out to correct ALL b quarks.
	while ( ( mc_find_b_2 = mc_find_b_1->GetMother() ) ) {
	  if( ( mc_find_b_2->GetType() == kBeauty ) || ( mc_find_b_2->GetType() == kAntiBeauty ) ) {
	    
	    // have found one b quark - stop the while loop and set the b quark.
	    mc->SetMuonBQuark(mc_find_b_2);
	    break;
	  }
	  else mc_find_b_1 = mc_find_b_2;
	}
      }
      else {
	//  	cout<<"r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" FMCKID: *** mu has old bquark: "<<mc->GetFMCKINID()<<endl;
	//  	cout<<"r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" PartID: *** mu has old bquark: "<<mc->GetPartID()<<endl; 
	//  	cout<<"r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" FMCKID: *** b is: "<<mc->GetMuonBQuark()->GetFMCKINID()<<endl;
	//  	cout<<"r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" PartID: *** b is: "<<mc->GetMuonBQuark()->GetPartID()<<endl; 
      }
      

      // Loop to find the closest B Meson to the muon:
      mc_iterator1 = 0;
      mc->SetMuonBMeson(0);
      if(mc->GetMother())                mc_iterator1 = mc->GetMother();
      else if(mc->GetMuonDirectParent()) mc_iterator1 = mc->GetMuonDirectParent();
      if(mc_iterator1 != 0 ){
	if(CheckBParent( mc_iterator1->GetPartID() ) && mc_iterator1->GetPartID()!= 27 && mc_iterator1->GetPartID() != 28 ) {
	  mc->SetMuonBMeson(mc_iterator1);
	  //	  cout<<"directly Found Part ID: "<<mc_iterator1->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator1->GetPartID() )<<" Pt: "<<mc_iterator1->Pt()<<endl;
	}
	
	if( 
	   (!( CheckBParent( mc_iterator1->GetPartID() ) ) || mc_iterator1->GetPartID()== 27 || mc_iterator1->GetPartID()== 28) && 
	   !(mc_iterator1->GetPartID() >= 54 && mc_iterator1->GetPartID() <= 63) ) {
	  while (  mc_iterator1->GetMother()  ) {
	    if( mc_iterator1->GetMother()->GetPartID() >= 54 && mc_iterator1->GetMother()->GetPartID() <= 63 ) {
	      //	      cout<<"Aborting Part ID: "<<mc_iterator1->GetMother()->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator1->GetMother()->GetPartID() )<<" Is K or pi."<<endl;
	      mc_iterator1 = mc_iterator1->GetMother();
 	      break;
 	    }
	    if( CheckBParent( mc_iterator1->GetMother()->GetPartID() ) && mc_iterator1->GetMother()->GetPartID()!= 27 && mc_iterator1->GetMother()->GetPartID() != 28 ) {
	      // have found one B meson - stop the while loop and set the B meson.
	      mc_iterator1 = mc_iterator1->GetMother();
	      mc->SetMuonBMeson(mc_iterator1);
	      //	      cout<<"Found Part ID: "<<mc_iterator1->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator1->GetPartID() )<<" Pt: "<<mc_iterator1->Pt()<<endl;
	      break;
	    }
	    else {
	      mc_iterator1 = mc_iterator1->GetMother();
	      //	      cout<<"Iterating to Part ID: "<<mc_iterator1->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator1->GetPartID() )<<endl;
	    }
	  }

	  if( !CheckBParent( mc_iterator1->GetPartID() ) || mc_iterator1->GetPartID()== 27 || mc_iterator1->GetPartID()== 28 ){
// 	    cout<<"Part ID: "<<mc_iterator1->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator1->GetPartID() )<<endl;
// 	    cout<<"No B meson found, but no mothers any more!! Bad? - likely muon from Geant"<<endl;
	  }
	}
	if(!mc->GetMuonBMeson()) {
	  // cout<<"Unsuccessful search for base particle: "<<mc->GetPartID()<<" with next-to-kin: "<<mc_iterator1->GetPartID()<<endl;
	}
// 	if(!mc->GetMuonBMeson() && hat B parent) {
// 	  cout<<"Unsuccessful search for base muon from hfl: "<<mc->GetPartID()<<" with next-to-kin: "<<mc_iterator1->GetPartID()<<endl;
// 	}
      }
      
      // 2nd loop to get the dimuon pairs:

      for ( Int_t j = i+1; j < fNMCs; ++j) {
	mc2 = ((GMC*)(fMCs->At(j)));
	
	if(  mc2->GetPartID() == 25 || mc2->GetPartID() == 26 ){  // 2nd mc particle is not a muon - skip mcdimuon finding
	  mcdimuon = new(mcdimuons[fNMCDIMuons++]) GDIMuon(mc, mc2);
	  CheckMCDIMuonHFL(mcdimuon);
	  if ( gCards->GetMcGeneral() ) {
	    fGeneralDimuMass_any->Fill(mcdimuon->GetInvMass());
	    fGeneralDimuMass1bin_any->Fill(mcdimuon->GetInvMass());
	    // 	    fGeneralDimuMass1bin_any->Fill(mcdimuon->GetMCMuon1()->Pt());
	    // 	    fGeneralDimuMass1bin_any->Fill(mcdimuon->GetMCMuon2()->Pt());
	    fGeneralDimuxsecPt_any->Fill(mcdimuon->GetMCMuon1()->Pt());
	    fGeneralDimuxsecPt_any->Fill(mcdimuon->GetMCMuon2()->Pt());
	    fGeneralDimuxsecEta_any->Fill(mcdimuon->GetMCMuon1()->Eta());
	    fGeneralDimuxsecEta_any->Fill(mcdimuon->GetMCMuon2()->Eta());
	    Double_t binx = 4.05;
	    for(Int_t dd = 0; dd < 40 ; dd += 1){
	      //	cout<<dd<<" is: "<<binx<<endl;
	      if( binx < 7.0 ){
		fGeneralDimuxsecFinders_any->Fill(binx);
		//		fGeneralDimuxsecFinders_any->Fill(binx);
	      }
	      else{
		fGeneralDimuxsecFinders_any->Fill(binx);
	      }
	      binx += 0.1;
	    }
	    fGeneralDimuxsecDR_any->Fill(mcdimuon->GetDeltaR());
	    fGeneralDimuxsecDphi_any->Fill(TMath::Abs(mcdimuon->GetDeltaPhi()));
	  }
	}
      }
    }
    CheckHeavyFlavours(mc);  
    
    CheckMuonCutsStage1(mc);
    
    AssociateMCJet(mc);
    AssociateMCPMJet(mc);
    
  }
  
  return kTRUE;
}

//_____________________________________________________________

TString GMCs::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GMCs::PrintMessage() called" << endl << endl;

  TString dummy = "";

  GMC       *mc       = 0;
  GJet      *jet      = 0;
  GMCVertex *mcvertex = 0;

  for ( Int_t i = 0; i < fNMCs; i++ ) {
    mc = ((GMC*)(fMCs->At(i)));
    dummy.Append(mc->PrintMessage(option));
  }
  dummy.Append("\nMC vertices\n\n");
  for ( Int_t i = 0; i < fNMCVertices; i++ ) {
    mcvertex = ((GMCVertex*)(fMCVertices->At(i)));
    dummy.Append(mcvertex->PrintMessage(option));
  }
  dummy.Append("\nMC hadron jets\n\n");
  for ( Int_t i = 0; i < fNMCHJets; i++ ) {
    jet = ((GJet*)(fMCHJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }
  dummy.Append("\nmassive MC hadron jets\n\n");
  for ( Int_t i = 0; i < fNMCHMJets; i++ ) {
    jet = ((GJet*)(fMCHMJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }
  dummy.Append("\nhadron jets with stable B mesons\n\n");
  for ( Int_t i = 0; i < fNMCHBJets; i++ ) {
    jet = ((GJet*)(fMCHBJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }
  dummy.Append("\nmassive MC hadron jets with stable B mesons\n\n");
  for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
    jet = ((GJet*)(fMCHBMJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }
  dummy.Append("\nMC parton jets\n\n");
  for ( Int_t i = 0; i < fNMCPJets; i++ ) {
    jet = ((GJet*)(fMCPJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }
  dummy.Append("\nmassive MC parton jets\n\n");
  for ( Int_t i = 0; i < fNMCPMJets; i++ ) {
    jet = ((GJet*)(fMCPMJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }

  // general information
  dummy.Append("\nGeneral information\n\n");
  dummy.Append(gInclude->FormatedChar(" Q2: ",5));
  dummy.Append(gInclude->FormatedDouble(gData->Getfmck_q2(),4,2));
  dummy.Append(gInclude->FormatedChar(" Q2: ",5));
  dummy.Append(gInclude->FormatedDouble(gData->Getmc_q2(),4,2));
  dummy.Append(gInclude->FormatedChar(" Y: ",5));
  dummy.Append(gInclude->FormatedDouble(gData->Getmc_y(),4,2));
  dummy.Append(gInclude->FormatedChar(" Q2 cut: ",10));
  dummy.Append(gInclude->FormatedBool(fQ2Cut));
  dummy.Append(gInclude->FormatedChar(" Y cut: ",9));
  dummy.Append(gInclude->FormatedBool(fYCut));
  dummy.Append(gInclude->FormatedChar(" muon cuts: ",13));
  dummy.Append(gInclude->FormatedBool(fMuonCuts));
  dummy.Append(gInclude->FormatedChar(" mcdimuon cuts: ",13));
  dummy.Append(gInclude->FormatedBool(fMCDIMuonCuts));
  dummy.Append(gInclude->FormatedChar(" jet a cut: ",13));
  dummy.Append(gInclude->FormatedBool(fMCHBMJetPtACut));
  dummy.Append(gInclude->FormatedChar(" jet b cut: ",13));
  dummy.Append(gInclude->FormatedBool(fMCHBMJetPtBCut));
  dummy.Append(gInclude->FormatedChar(" all MC cuts: ",15));
  dummy.Append(gInclude->FormatedBool(GetAllMCCuts()));
  dummy.Append("\n");


  return dummy;
}

//_____________________________________________________________

Bool_t GMCs::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMCs::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("MC") || option.Contains("ALL") ) {
      gLister->FillOutputList("MCs:\n\n");
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "MCs:" << endl << endl;;
    cout << PrintMessage(option) << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CreateGeneral() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GMCs::CreateGeneral() called" << endl << endl;

  if ( gCards->GetMcGeneral() ) {

    Int_t    ybins  =   50;
    Double_t ylow   =    0.;
    Double_t yhigh  =    1.;  
    Int_t    xbins  =   50;
    Double_t xlow   =    0.;
    Double_t xhigh  =    1.;  
    Int_t    q2bins = 30;
    Double_t q2low  = -10.;
    Double_t q2high = 5.;
    Int_t    crossmuonregionbins = 3;
    Double_t crossmuonregionlow  = 0.;
    Double_t crossmuonregionhigh = 3.;
    Int_t    crossmuonfinderbins = 15;
    Double_t crossmuonfinderlow  = 0.;
    Double_t crossmuonfinderhigh = 15.;
    Int_t    crosstotalbins = 1;
    Double_t crosstotallow  = 0.;
    Double_t crosstotalhigh = 1.;

    Int_t    deltaphibins = 157;
    Double_t deltaphilow  = 0.0;
    Double_t deltaphihigh = TMath::Pi();
//     Int_t    phibins = 360;
//     Double_t philow  = -TMath::Pi();
//     Double_t phihigh = TMath::Pi();

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
// End new binning

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

    Int_t    crosspt_nbins = 4;
    Double_t *crosspt_bins = new Double_t[crosspt_nbins+1];
    crosspt_bins[0] = 1.5;
    crosspt_bins[1] = 3.0;
    crosspt_bins[2] = 5.0;
    crosspt_bins[3] = 7.5;
    crosspt_bins[4] = 11.0;

    Int_t    crosseta_nbins = 4;
    Double_t *crosseta_bins = new Double_t[crosseta_nbins+1];
    crosseta_bins[0]  = -2.0;
    crosseta_bins[1]  = -0.9;
    crosseta_bins[2]  =  0.0;
    crosseta_bins[3]  =  1.2;
    crosseta_bins[4]  =  2.5;

    Int_t    crossptfine_nbins = 8;
    Double_t *crossptfine_bins = new Double_t[crossptfine_nbins+1];
    crossptfine_bins[0]  =  1.5;
    crossptfine_bins[1]  =  2.5;
    crossptfine_bins[2]  =  3.5;
    crossptfine_bins[3]  =  4.5;
    crossptfine_bins[4]  =  5.5;
    crossptfine_bins[5]  =  6.5;
    crossptfine_bins[6]  =  7.5;
    crossptfine_bins[7]  =  8.5;
    crossptfine_bins[8]  = 11.5;

    Int_t    crossetafine_nbins = 8;
    Double_t *crossetafine_bins = new Double_t[crossetafine_nbins+1];
    crossetafine_bins[0]  = -1.5;
    crossetafine_bins[1]  = -1.0;
    crossetafine_bins[2]  = -0.50;
    crossetafine_bins[3]  =  0.0;
    crossetafine_bins[4]  =  0.50;
    crossetafine_bins[5]  =  1.00;
    crossetafine_bins[6]  =  1.50;
    crossetafine_bins[7]  =  2.0;
    crossetafine_bins[8]  =  2.50;

    Int_t    crossptmassimo_nbins = 3;
    Double_t *crossptmassimo_bins = new Double_t[crossptmassimo_nbins+1];
    crossptmassimo_bins[0]  =  2.5;
    crossptmassimo_bins[1]  =  4.0;
    crossptmassimo_bins[2]  =  6.0;
    crossptmassimo_bins[3]  = 10.0;

    Int_t    crossetamassimo_nbins = 4;
    Double_t *crossetamassimo_bins = new Double_t[crossetamassimo_nbins+1];
    crossetamassimo_bins[0] = -1.6;
    crossetamassimo_bins[1] = -0.75;
    crossetamassimo_bins[2] = 0.25;
    crossetamassimo_bins[3] = 1.3;
    crossetamassimo_bins[4] = 2.3;

    Int_t    crossmuonjetpt_nbins = 3;
    Double_t *crossmuonjetpt_bins = new Double_t[crossmuonjetpt_nbins+1];
    crossmuonjetpt_bins[0] =  6.0;
    crossmuonjetpt_bins[1] = 11.0;;
    crossmuonjetpt_bins[2] = 16.0;
    crossmuonjetpt_bins[3] = 30.0;

    Int_t    crossmuonjeteta_nbins = 4;
    Double_t *crossmuonjeteta_bins = new Double_t[crossmuonjeteta_nbins+1];
    crossmuonjeteta_bins[0] = -1.6;
    crossmuonjeteta_bins[1] = -0.6;
    crossmuonjeteta_bins[2] =  0.4;
    crossmuonjeteta_bins[3] =  1.4;
    crossmuonjeteta_bins[4] =  2.5;

    Int_t    crossmuonjetptfine_nbins = 9;
    Double_t *crossmuonjetptfine_bins = new Double_t[crossmuonjetptfine_nbins+1];
    crossmuonjetptfine_bins[0]  =  6.0;
    crossmuonjetptfine_bins[1]  =  8.0;
    crossmuonjetptfine_bins[2]  =  9.0;
    crossmuonjetptfine_bins[3]  = 10.0;
    crossmuonjetptfine_bins[4]  = 11.0;
    crossmuonjetptfine_bins[5]  = 12.0;
    crossmuonjetptfine_bins[6]  = 13.0;
    crossmuonjetptfine_bins[7]  = 15.0;
    crossmuonjetptfine_bins[8]  = 18.0;
    crossmuonjetptfine_bins[9]  = 30.0;

    Int_t    crossmuonjetetafine_nbins = 8;
    Double_t *crossmuonjetetafine_bins = new Double_t[crossmuonjetetafine_nbins+1];
    crossmuonjetetafine_bins[0]  = -1.50;
    crossmuonjetetafine_bins[1]  = -1.0;
    crossmuonjetetafine_bins[2]  = -0.50;
    crossmuonjetetafine_bins[3]  =  0.0;
    crossmuonjetetafine_bins[4]  =  0.50;
    crossmuonjetetafine_bins[5]  =  1.0;
    crossmuonjetetafine_bins[6] =  1.5;
    crossmuonjetetafine_bins[7] =  2.0;
    crossmuonjetetafine_bins[8] =  2.50;

    Int_t    crossjetxgamma_nbins = 5;
    Double_t *crossjetxgamma_bins = new Double_t[crossjetxgamma_nbins+1];
    crossjetxgamma_bins[0] =  0.000;
    crossjetxgamma_bins[1] =  0.375;
    crossjetxgamma_bins[2] =  0.500;
    crossjetxgamma_bins[3] =  0.625;
    crossjetxgamma_bins[4] =  0.750;
    crossjetxgamma_bins[5] =  1.00;

    Int_t    crossjetxgammafine_nbins = 6;
    Double_t *crossjetxgammafine_bins = new Double_t[crossjetxgammafine_nbins+1];
    crossjetxgammafine_bins[0] =  0.000;
    crossjetxgammafine_bins[1] =  0.250;
    crossjetxgammafine_bins[2] =  0.375;;
    crossjetxgammafine_bins[3] =  0.500;;
    crossjetxgammafine_bins[4] =  0.625;;
    crossjetxgammafine_bins[5] =  0.750;;
    crossjetxgammafine_bins[6] =  1.00;;

    Int_t    crossjetmjets_nbins = 10;
    Double_t *crossjetmjets_bins = new Double_t[crossjetmjets_nbins+1];
    crossjetmjets_bins[0]  =  0.0;
    crossjetmjets_bins[1]  =  5.0;
    crossjetmjets_bins[2]  = 10.0;
    crossjetmjets_bins[3]  = 15.0;
    crossjetmjets_bins[4]  = 20.0;
    crossjetmjets_bins[5]  = 25.0;
    crossjetmjets_bins[6]  = 30.0;
    crossjetmjets_bins[7]  = 35.0;
    crossjetmjets_bins[8]  = 40.0;
    crossjetmjets_bins[9]  = 45.0;
    crossjetmjets_bins[10]  = 60.0;

    Int_t    crossjetdphijets_nbins = 6;
    Double_t *crossjetdphijets_bins = new Double_t[crossjetdphijets_nbins+1];
    crossjetdphijets_bins[0]  = 0*TMath::Pi();
    crossjetdphijets_bins[1]  = 12./24.*TMath::Pi();
    crossjetdphijets_bins[2]  = 16./24.*TMath::Pi();
    crossjetdphijets_bins[3]  = 19./24.*TMath::Pi();
    crossjetdphijets_bins[4]  = 21./24.*TMath::Pi();
    crossjetdphijets_bins[5]  = 23./24.*TMath::Pi();
    crossjetdphijets_bins[6]  = 24./24.*TMath::Pi();

    Int_t    crossjetdrjets_nbins = 5;
    Double_t *crossjetdrjets_bins = new Double_t[crossjetdrjets_nbins+1];
    crossjetdrjets_bins[0]  = 1.0;
    crossjetdrjets_bins[1]  = 2.0;
    crossjetdrjets_bins[2]  = 2.5;
    crossjetdrjets_bins[3]  = 3.0;
    crossjetdrjets_bins[4]  = 3.5;
    crossjetdrjets_bins[5]  = 5;

    Int_t    crossjetptjets_nbins = 5;
    Double_t *crossjetptjets_bins = new Double_t[crossjetptjets_nbins+1];
    crossjetptjets_bins[0]  =   0.0;
    crossjetptjets_bins[1]  =   9.0;
    crossjetptjets_bins[2]  =  36.0;
    crossjetptjets_bins[3]  =  81.0;
    crossjetptjets_bins[4]  = 144.0;
    crossjetptjets_bins[5]  = 324.0;

    Int_t    crossjetcosthetastarjets_nbins = 6;
    Double_t *crossjetcosthetastarjets_bins = new Double_t[crossjetcosthetastarjets_nbins+1];
    crossjetcosthetastarjets_bins[0]  = -0.83;
    crossjetcosthetastarjets_bins[1]  = -0.664;
    crossjetcosthetastarjets_bins[2]  = -0.332;
    crossjetcosthetastarjets_bins[3]  =  0.0;
    crossjetcosthetastarjets_bins[4]  =  0.332;
    crossjetcosthetastarjets_bins[5]  =  0.664;
    crossjetcosthetastarjets_bins[6]  =  0.83;

    Int_t ndrbins = 100;
    Double_t drlow = 0;
    Double_t drhigh = 5;

    fGeneralDeltaRMuonJet =gHistogrammer->TH1DFactory("MC","DeltaRMuonJet","DeltaRMuonJet",ndrbins,drlow,drhigh,"#Delta R^{#mu}","Events");
    fGeneralDeltaRMuonJet2D =gHistogrammer->TH2DFactory("MC","DeltaRMuonJet2D","DeltaRMuonJet2D",ndrbins,drlow,drhigh,ndrbins,drlow,drhigh,"#Delta R^{#mu}","#Delta R2^{#mu}","Muons");

    fGeneralDeltaRMuonSecondJet =gHistogrammer->TH1DFactory("MC","DeltaRMuonSecondJet","DeltaRMuonSecondJet",ndrbins,drlow,drhigh,"#Delta R^{#mu}","Events");
    fGeneralY_uncut = gHistogrammer->TH1DFactory("MC","Y_uncut","uncut y_{true}",ybins,ylow,yhigh,"y_{true}","Events");
    fGeneralX_uncut = gHistogrammer->TH1DFactory("MC","X_uncut","uncut x_{true}",xbins,xlow,xhigh,"x_{true}","Events");
    fGeneralQ2_uncut = gHistogrammer->TH1DFactory("MC","Q2_uncut","uncut Q^{2}_{true}",q2bins,q2low,q2high,"log_{10}(Q^{2}_{true})","Events");

    fGeneralY = gHistogrammer->TH1DFactory("MC","Y","y_{true}",ybins,ylow,yhigh,"y_{true}","Events");
    fGeneralX = gHistogrammer->TH1DFactory("MC","X","x_{true}",xbins,xlow,xhigh,"x_{true}","Events");
    fGeneralQ2 = gHistogrammer->TH1DFactory("MC","Q2","Q^{2}_{true}",q2bins,q2low,q2high,"log_{10}(Q^{2}_{true})","Events");
    fGeneralQ2_1 = gHistogrammer->TH1DFactory("MC","Q2_1","Q^{2}_{true}",q2bins,q2low,q2high,"log_{10}(Q^{2}_{true})","Events");
    fGeneralQ2_2 = gHistogrammer->TH1DFactory("MC","Q2_2","Q^{2}_{true}",q2bins,q2low,q2high,"log_{10}(Q^{2}_{true})","Events");
    fGeneralQ2_3 = gHistogrammer->TH1DFactory("MC","Q2_3","Q^{2}_{true}",q2bins,q2low,q2high,"log_{10}(Q^{2}_{true})","Events");


    fGeneralCrossTotalTrue = gHistogrammer->TH1DFactory("MC","CrossTotalTrue","true total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
    fGeneralCrossTotalTrueNRec = gHistogrammer->TH1DFactory("MC","CrossTotalTrueNRec","true and rec total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");

  fGeneralCrossTotalAssociatedTrue = gHistogrammer->TH1DFactory("MC","CrossTotalAssociatedTrue","true total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
  fGeneralCrossTotalAssociatedTrueNRec = gHistogrammer->TH1DFactory("MC","CrossTotalAssociatedTrueNRec","true and rec total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
  fGeneralCrossTotalEventTrue      = gHistogrammer->TH1DFactory("MC","CrossTotalEventTrue","true total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");
  fGeneralCrossTotalEventTrueNRec  = gHistogrammer->TH1DFactory("MC","CrossTotalEventTrueNRec","true and rec total",crosstotalbins,crosstotallow,crosstotalhigh,"total","Events");


  fGeneralCrossMuonFinderTrue = gHistogrammer->TH1DFactory("MC","CrossMuonFinderTrue","true #mu regions 0-4 barrel 5-9 rear, 10-14 forward",crossmuonfinderbins,crossmuonfinderlow,crossmuonfinderhigh,"#mu region","Events");
  fGeneralCrossMuonFinderTrueNRec = gHistogrammer->TH1DFactory("MC","CrossMuonFinderTrueNRec","true #mu regions 0-4 barrel 5-9 rear, 10-14 forward",crossmuonfinderbins,crossmuonfinderlow,crossmuonfinderhigh,"#mu region","Events");

    fGeneralCrossMuonRegionsTrue = gHistogrammer->TH1DFactory("MC","CrossMuonRegionsTrue","true #mu regions",crossmuonregionbins,crossmuonregionlow,crossmuonregionhigh,"#mu region","Events");
    fGeneralCrossMuonRegionsTrueNRec = gHistogrammer->TH1DFactory("MC","CrossMuonRegionsTrueNRec","true and rec #mu regions",crossmuonregionbins,crossmuonregionlow,crossmuonregionhigh,"#mu region","Events");
    fGeneralCrossMuonRegionsNoJetTrue = gHistogrammer->TH1DFactory("MC","CrossMuonRegionsNoJetTrue","true #mu regions",crossmuonregionbins,crossmuonregionlow,crossmuonregionhigh,"#mu region","Events");
    fGeneralCrossMuonRegionsNoJetTrueNRec = gHistogrammer->TH1DFactory("MC","CrossMuonRegionsNoJetTrueNRec","true and rec #mu regions nojet",crossmuonregionbins,crossmuonregionlow,crossmuonregionhigh,"#mu region","Events");

    fGeneralMuParentPhiTrueNRec = gHistogrammer->TH2DFactory("DIMuon","phi_mc_Parent","phi rec mu",100,-3.15,3.15,100,-3.15,3.15,"phi mc Parent","phi rec #mu","Muons");
    fGeneralMuParentPhiResTrueNRec = gHistogrammer->TH1DFactory("DIMuon","dphi_parent_mu_res","true and rec...",360,-180.,180.,"phi parent - phi mu ","Muons");
    fGeneralMuParentDRResTrueNRec = gHistogrammer->TH1DFactory("DIMuon","DR_mc_mu_meson_res","true and rec...",300,0.,10.,"DR parent : mu ","Muons");
    fGeneralMuParentPTResTrueNRec = gHistogrammer->TH1DFactory("DIMuon","PT_mc_mu_meson_res","true and rec...",300,-50.,50.,"PT parent : mu ","Muons");
    fGeneralMuQuarkPhiTrueNRec = gHistogrammer->TH2DFactory("DIMuon","phi_mc_Quark","phi rec mu",100,-3.15,3.15,100,-3.15,3.15,"phi mc Quark","phi rec #mu","Muons");
    fGeneralMuQuarkPhiResTrueNRec = gHistogrammer->TH1DFactory("DIMuon","dphi_quark_mu_res","true and rec...",360,-180.,180.,"phi quark - phi mu ","Muons");
    fGeneralMuQuarkDRResTrueNRec = gHistogrammer->TH1DFactory("DIMuon","DR_mc_mu_quark_res","true and rec...",300,0.,10.,"DR quark : mu ","Muons");
    fGeneralMuQuarkPTResTrueNRec = gHistogrammer->TH1DFactory("DIMuon","PT_mc_mu_quark_res","true and rec...",300,-50.,50.,"PT quark : mu ","Muons");

    fGeneralDimuMass_any = gHistogrammer->TH1DFactory("DIMuon","mcdimumass_any","any mcdimu ",500,0.,50.,"mcdimumass","MCDIMuons");
    fGeneralDimuMass_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass_true_hfl_mu","true hfl dimu ",500,0.,50.,"mcdimumass","MCDIMuons");
    fGeneralDimuMass_truenrec_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass_truenrec_hfl_mu","truenrec hfl dimu ",500,0.,50.,"mcdimumass","MCDIMuons");

    fGeneralMuQuarkPtTrueNRec = gHistogrammer->TH2DFactory("DIMuon","pt_mc_Quark","pt rec mu",120,0.,40.,120,0.,40.,"pt mc Quark","pt rec #mu","Muons");
    fGeneralMuQuarkPtTrueNRec_singlb = gHistogrammer->TH2DFactory("DIMuon","pt_mc_Quark_singlb","pt rec mu_singlb",120,0.,40.,120,0.,40.,"pt mc Quark_singlb","pt rec #mu","Muons_singlb");
    fGeneralMuBMesonPtTrueNRec = gHistogrammer->TH2DFactory("DIMuon","pt_mc_bmeson","pt rec mu",120,0.,40.,120,0.,40.,"pt mc bmeson","pt rec #mu","Muons");
    fGeneralMuBMesonPtTrueNRec_singlb = gHistogrammer->TH2DFactory("DIMuon","pt_mc_bmeson_singlb","pt rec mu_singlb",120,0.,40.,120,0.,40.,"pt mc bmeson_singlb","pt rec #mu","Muons_singlb");

     fGeneralDimuMass1bin_any = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_any","any mcdimu ",1,0.,100.,"mcdimumass1bin","MCDIMuons");
     fGeneralDimuMass1bin_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_true_hfl_mu","true hfl dimu ",1,0.,100.,"mcdimumass1bin","MCDIMuons");
     fGeneralDimuMass1bin_truenrec_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_truenrec_hfl_mu","truenrec hfl dimu ",1,0.,100.,"mcdimumass1bin","MCDIMuons");
//     fGeneralDimuMass1bin_any = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_any","any mcdimu ",4,1.5,9.5,"mcdimumass1bin","MCDIMuons");
//     fGeneralDimuMass1bin_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_true_hfl_mu","true hfl dimu ",4,1.5,9.5,"mcdimumass1bin","MCDIMuons");
//     fGeneralDimuMass1bin_truenrec_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_truenrec_hfl_mu","truenrec hfl dimu ",4,1.5,9.5,"mcdimumass1bin","MCDIMuons");
//     fGeneralDimuMass1bin_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimumass1bin_any","any mcdimu ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimumass1bin","MCDIMuons");
//     fGeneralDimuMass1bin_true_hflmu     = gHistogrammer->TH1DVarFactory("DIMuon","mcdimumass1bin_true_hfl_mu","true hfl dimu ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimumass1bin","MCDIMuons");
//     fGeneralDimuMass1bin_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimumass1bin_truenrec_hfl_mu","truenrec hfl dimu ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimumass1bin","MCDIMuons");

   fGeneralDimuxsecPt_any             = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPt_any","any mcdimu ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimuxsecPt","MCDIMuons");			
   fGeneralDimuxsecPt_true_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPt_true_hfl_mu","true hfl dimu ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimuxsecPt","MCDIMuons");	
   fGeneralDimuxsecPt_truenrec_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPt_truenrec_hfl_mu","truenrec hfl dimu ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimuxsecPt","MCDIMuons");

   fGeneralDimuxsecEta_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecEta_any","any mcdimu ",dimucrosseta_nbins,dimucrosseta_bins,"mcdimuxsecEta","MCDIMuons");		    
   fGeneralDimuxsecEta_true_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecEta_true_hfl_mu","true hfl dimu ",dimucrosseta_nbins,dimucrosseta_bins,"mcdimuxsecEta","MCDIMuons");	    
   fGeneralDimuxsecEta_truenrec_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecEta_truenrec_hfl_mu","truenrec hfl dimu ",dimucrosseta_nbins,dimucrosseta_bins,"mcdimuxsecEta","MCDIMuons");

   fGeneralDimuxsecFinders_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecFinders_any","any mcdimu ",dimucrossfinders_nbins,dimucrossfinders_bins,"mcdimuxsecFinders","MCDIMuons");		    
   fGeneralDimuxsecFinders_true_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecFinders_true_hfl_mu","true hfl dimu ",dimucrossfinders_nbins,dimucrossfinders_bins,"mcdimuxsecFinders","MCDIMuons");	    
   fGeneralDimuxsecFinders_truenrec_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecFinders_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossfinders_nbins,dimucrossfinders_bins,"mcdimuxsecFinders","MCDIMuons");

   fGeneralDimuxsecDR_any             = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDR_any","any mcdimu ",dimucrossdr_nbins,dimucrossdr_bins,"mcdimuxsecDR","MCDIMuons");		    
   fGeneralDimuxsecDR_true_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDR_true_hfl_mu","true hfl dimu ",dimucrossdr_nbins,dimucrossdr_bins,"mcdimuxsecDR","MCDIMuons");	    
   fGeneralDimuxsecDR_truenrec_hflmu	= gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDR_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossdr_nbins,dimucrossdr_bins,"mcdimuxsecDR","MCDIMuons");

   fGeneralDimuxsecDphi_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDphi_any","any mcdimu ",dimucrossdphi_nbins,dimucrossdphi_bins,"mcdimuxsecDphi","MCDIMuons");		    
   fGeneralDimuxsecDphi_true_hflmu	 = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDphi_true_hfl_mu","true hfl dimu ",dimucrossdphi_nbins,dimucrossdphi_bins,"mcdimuxsecDphi","MCDIMuons");	    
   fGeneralDimuxsecDphi_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDphi_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossdphi_nbins,dimucrossdphi_bins,"mcdimuxsecDphi","MCDIMuons");

   fGeneralDimuxsecPtb_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_any","any mcdimu ",dimucrossptb_nbins,dimucrossptb_bins,"mcdimuxsecPtb","MCDIMuons");		    
   fGeneralDimuxsecPtb_true_hflmu	 = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_true_hfl_mu","true hfl dimu ",dimucrossptb_nbins,dimucrossptb_bins,"mcdimuxsecPtb","MCDIMuons");	    
   fGeneralDimuxsecPtb_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossptb_nbins,dimucrossptb_bins,"mcdimuxsecPtb","MCDIMuons");

   fGeneralDimuxsecPtb_sameb_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_sameb_any","any mcdimu ",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"mcdimuxsecPtb_sameb","MCDIMuons");		    
   fGeneralDimuxsecPtb_sameb_true_hflmu	 = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_sameb_true_hfl_mu","true hfl dimu ",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"mcdimuxsecPtb_sameb","MCDIMuons");	    
   fGeneralDimuxsecPtb_sameb_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_sameb_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossptb_sameb_nbins,dimucrossptb_sameb_bins,"mcdimuxsecPtb_sameb","MCDIMuons");

   fGeneralDimuxsecPtb_diffb_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_diffb_any","any mcdimu ",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"mcdimuxsecPtb_diffb","MCDIMuons");		    
   fGeneralDimuxsecPtb_diffb_true_hflmu	 = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_diffb_true_hfl_mu","true hfl dimu ",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"mcdimuxsecPtb_diffb","MCDIMuons");	    
   fGeneralDimuxsecPtb_diffb_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_diffb_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossptb_diffb_nbins,dimucrossptb_diffb_bins,"mcdimuxsecPtb_diffb","MCDIMuons");

   fGeneralDimuxsecPtb_samecone_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_samecone_any","any mcdimu ",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"mcdimuxsecPtb_samecone","MCDIMuons");		    
   fGeneralDimuxsecPtb_samecone_true_hflmu	 = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_samecone_true_hfl_mu","true hfl dimu ",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"mcdimuxsecPtb_samecone","MCDIMuons");	    
   fGeneralDimuxsecPtb_samecone_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_samecone_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossptb_samecone_nbins,dimucrossptb_samecone_bins,"mcdimuxsecPtb_samecone","MCDIMuons");

   fGeneralDimuxsecPtb_asym_any            = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_asym_any","any mcdimu ",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"mcdimuxsecPtb_asym","MCDIMuons");		    
   fGeneralDimuxsecPtb_asym_true_hflmu	 = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_asym_true_hfl_mu","true hfl dimu ",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"mcdimuxsecPtb_asym","MCDIMuons");	    
   fGeneralDimuxsecPtb_asym_truenrec_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPtb_asym_truenrec_hfl_mu","truenrec hfl dimu ",dimucrossptb_asym_nbins,dimucrossptb_asym_bins,"mcdimuxsecPtb_asym","MCDIMuons");

    fGeneralDimu_b_pt_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","Dimu_b_pt_true_hflmu","true hfl dimu quark",80,0.,20.,"p_{T}^{b-quark}","MCDIMuons");
    fGeneralDimu_b_pt_truenrec_hflmu = gHistogrammer->TH1DFactory("DIMuon","Dimu_b_pt_truenrec_hflmu","truenrec hfl dimu quark",80,0.,20.,"p_{T}^{b-quark}","MCDIMuons");

/* DB Histos for Dijet Selection */

    fGeneralDijetbothDimuMass1bin_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_both_true_hfl_mu","true hfl dimu_both ",1,0.,100.,"mcdimumass1bin_both","MCDIMuons");
    fGeneralDijetbothDimuxsecPt_true_hflmu   = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPt_both_true_hfl_mu","true hfl dimu_both ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimuxsecPt_both","MCDIMuons");	
    fGeneralDijetbothDimuxsecEta_true_hflmu  = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecEta_both_true_hfl_mu","true hfl dimu_both ",dimucrosseta_nbins,dimucrosseta_bins,"mcdimuxsecEta_both","MCDIMuons");	    
    fGeneralDijetbothDimuxsecDphi_true_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDphi_both_true_hfl_mu","true hfl dimu_both ",dimucrossdphi_nbins,dimucrossdphi_bins,"mcdimuxsecDphi_both","MCDIMuons");	    

    fGeneralDijetnoneDimuMass1bin_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_none_true_hfl_mu","true hfl dimu_none ",1,0.,100.,"mcdimumass1bin_none","MCDIMuons");
    fGeneralDijetnoneDimuxsecPt_true_hflmu   = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPt_none_true_hfl_mu","true hfl dimu_none ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimuxsecPt_none","MCDIMuons");	
    fGeneralDijetnoneDimuxsecEta_true_hflmu  = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecEta_none_true_hfl_mu","true hfl dimu_none ",dimucrosseta_nbins,dimucrosseta_bins,"mcdimuxsecEta_none","MCDIMuons");	    
    fGeneralDijetnoneDimuxsecDphi_true_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDphi_none_true_hfl_mu","true hfl dimu_none ",dimucrossdphi_nbins,dimucrossdphi_bins,"mcdimuxsecDphi_none","MCDIMuons");	    

    fGeneralDijetoneDimuMass1bin_true_hflmu = gHistogrammer->TH1DFactory("DIMuon","mcdimumass1bin_one_true_hfl_mu","true hfl dimu_one ",1,0.,100.,"mcdimumass1bin_one","MCDIMuons");
    fGeneralDijetoneDimuxsecPt_true_hflmu   = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecPt_one_true_hfl_mu","true hfl dimu_one ",dimucrosspt_nbins,dimucrosspt_bins,"mcdimuxsecPt_one","MCDIMuons");	
    fGeneralDijetoneDimuxsecEta_true_hflmu  = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecEta_one_true_hfl_mu","true hfl dimu_one ",dimucrosseta_nbins,dimucrosseta_bins,"mcdimuxsecEta_one","MCDIMuons");	    
    fGeneralDijetoneDimuxsecDphi_true_hflmu = gHistogrammer->TH1DVarFactory("DIMuon","mcdimuxsecDphi_one_true_hfl_mu","true hfl dimu_one ",dimucrossdphi_nbins,dimucrossdphi_bins,"mcdimuxsecDphi_one","MCDIMuons");	    

/* End Dijet Selection           */

    //_____________________________________________
    fGeneralCrossMuonPtTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtTrue","true p_{T}^{#mu}",crosspt_nbins,crosspt_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonPtTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtTrueNRec","true and rec p_{T}^{#mu}",crosspt_nbins,crosspt_bins,"p_{T}^{#mu}","Events");

    fGeneralCrossMuonEtaTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaTrue","true #eta^{#mu}",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonEtaTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaTrueNRec","true and rec #eta^{#mu}",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");

    fGeneralCrossMuonPtFineTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtFineTrue","true p_{T}^{#mu}",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonPtFineTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtFineTrueNRec","true and rec p_{T}^{#mu}",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu}","Events");

    fGeneralCrossMuonEtaFineTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaFineTrue","true #eta^{#mu}",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonEtaFineTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaFineTrueNRec","true and rec #eta^{#mu}",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");

    fGeneralCrossMuonPtMassimoTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtMassimoTrue","true p_{T}^{#mu}",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonPtMassimoTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtMassimoTrueNRec","true and rec p_{T}^{#mu}",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu}","Events");

    fGeneralCrossMuonEtaMassimoTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaMassimoTrue","true #eta^{#mu}",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonEtaMassimoTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaMassimoTrueNRec","true and rec #eta^{#mu}",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");
    //_______________
    fGeneralCrossMuonPtNoJetTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtNoJetTrue","true p_{T}^{#mu} nomatch nomatch",crosspt_nbins,crosspt_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonPtNoJetTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtNoJetTrueNRec","true and rec p_{T}^{#mu} nomatch nomatch",crosspt_nbins,crosspt_bins,"p_{T}^{#mu}","Events");

    fGeneralCrossMuonEtaNoJetTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaNoJetTrue","true #eta^{#mu} nomatch",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonEtaNoJetTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaNoJetTrueNRec","true and rec #eta^{#mu} nomatch",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");

    fGeneralCrossMuonPtFineNoJetTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtFineNoJetTrue","true p_{T}^{#mu} nomatch",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonPtFineNoJetTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtFineNoJetTrueNRec","true and rec p_{T}^{#mu} nomatch",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu}","Events");

    fGeneralCrossMuonEtaFineNoJetTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaFineNoJetTrue","true #eta^{#mu} nomatch",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonEtaFineNoJetTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaFineNoJetTrueNRec","true and rec #eta^{#mu} nomatch",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");

    fGeneralCrossMuonPtMassimoNoJetTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtMassimoNoJetTrue","true p_{T}^{#mu} nomatch",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonPtMassimoNoJetTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtMassimoNoJetTrueNRec","true and rec p_{T}^{#mu}",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu}","Events");

    fGeneralCrossMuonEtaMassimoNoJetTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaMassimoNoJetTrue","true #eta^{#mu} nomatch",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonEtaMassimoNoJetTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaMassimoNoJetTrueNRec","true and rec #eta^{#mu} nomatch",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");
    //____________________________
    fGeneralCrossMuonJetPtTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetPtTrue","true p_{T}^{#mu-jet}",crossmuonjetpt_nbins,crossmuonjetpt_bins,"p_{T}^{#mu-jet}","Events");
    fGeneralCrossMuonJetPtTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetPtTrueNRec","true and rec p_{T}^{#mu-jet}",crossmuonjetpt_nbins,crossmuonjetpt_bins,"p_{T}^{#mu-jet}","Events");

    fGeneralCrossMuonJetEtaTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetEtaTrue","true #eta^{#mu-jet}",crossmuonjeteta_nbins,crossmuonjeteta_bins,"#eta^{#mu-jet}","Events");
    fGeneralCrossMuonJetEtaTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetEtaTrueNRec","true and rec #eta^{#mu-jet}",crossmuonjeteta_nbins,crossmuonjeteta_bins,"#eta^{#mu-jet}","Events");

    fGeneralCrossMuonJetPtFineTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetPtFineTrue","true p_{T}^{#mu-jet}",crossmuonjetptfine_nbins,crossmuonjetptfine_bins,"p_{T}^{#mu-jet}","Events");
    fGeneralCrossMuonJetPtFineTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetPtFineTrueNRec","true and rec p_{T}^{#mu-jet}",crossmuonjetptfine_nbins,crossmuonjetptfine_bins,"p_{T}^{#mu-jet}","Events");

    fGeneralCrossMuonJetEtaFineTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetEtaFineTrue","true #eta^{#mu-jet}",crossmuonjetetafine_nbins,crossmuonjetetafine_bins,"#eta^{#mu-jet}","Events");
    fGeneralCrossMuonJetEtaFineTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetEtaFineTrueNRec","true and rec #eta^{#mu-jet}",crossmuonjetetafine_nbins,crossmuonjetetafine_bins,"#eta^{#mu-jet}","Events");

    fGeneralCrossJetXGammaTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetXGammaTrue","true x_{#gamma}",crossjetxgamma_nbins,crossjetxgamma_bins,"x_{#gamma}","Events");
    fGeneralCrossJetXGammaFineTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetXGammaFineTrue","true x_{#gamma}",crossjetxgammafine_nbins,crossjetxgammafine_bins,"x_{#gamma}","Events");
    fGeneralCrossJetMJetsTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsTrue","true M_{jj}",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsTrue","true #Delta #phi _{jj}",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsTrue","true #Delta R_{jj}",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsTrue","true p_{T,jj}^{2}",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsTrue","true cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsTrue = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsTrue","true cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

    // Low: x_gamma < 0.75
    fGeneralCrossJetMJetsLowTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsLowTrue","true M_{jj} for x_{#gamma} < 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsLowTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsLowTrue","true #Delta #phi _{jj} for x_{#gamma} < 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsLowTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsLowTrue","true #Delta R_{jj} for x_{#gamma} < 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsLowTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsLowTrue","true p_{T,jj}^{2} for x_{#gamma} < 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsLowTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsLowTrue","true cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsLowTrue = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsLowTrue","true cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

    // High: x_gamma >= 0.75
    fGeneralCrossJetMJetsHighTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsHighTrue","true M_{jj} for x_{#gamma} #geq 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsHighTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsHighTrue","true #Delta #phi _{jj} for x_{#gamma} #geq 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsHighTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsHighTrue","true #Delta R_{jj} for x_{#gamma} #geq 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsHighTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsHighTrue","true p_{T,jj}^{2} for x_{#gamma} #geq 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsHighTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsHighTrue","true cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsHighTrue = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsHighTrue","true cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

      fGeneralCrossJetXGammaTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetXGammaTrueNRec","true and rec.x_{#gamma}",crossjetxgamma_nbins,crossjetxgamma_bins,"x_{#gamma}","Events");
      fGeneralCrossJetXGammaFineTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetXGammaFineTrueNRec","true and rec.x_{#gamma}",crossjetxgammafine_nbins,crossjetxgammafine_bins,"x_{#gamma}","Events");
      fGeneralCrossJetMJetsTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsTrueNRec","true and rec.M_{jj}",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
      fGeneralCrossJetDPhiJetsTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsTrueNRec","true and rec.#Delta #phi _{jj}",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
      fGeneralCrossJetDRJetsTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsTrueNRec","true and rec.#Delta R_{jj}",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
      fGeneralCrossJetPtJetsTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsTrueNRec","true and rec.p_{T,jj}^{2}",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
      fGeneralCrossJetCosThetaStarJetsTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsTrueNRec","true and rec. cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
      fGeneralCrossMJMatchCosThetaStarJetsTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsTrueNRec","true and rec. cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

      // Low: x_gamma < 0.75
      fGeneralCrossJetMJetsLowTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsLowTrueNRec","true and rec.M_{jj} for x_{#gamma} < 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
      fGeneralCrossJetDPhiJetsLowTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsLowTrueNRec","true and rec.#Delta #phi _{jj} for x_{#gamma} < 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
      fGeneralCrossJetDRJetsLowTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsLowTrueNRec","true and rec.#Delta R_{jj} for x_{#gamma} < 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
      fGeneralCrossJetPtJetsLowTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsLowTrueNRec","true and rec.p_{T,jj}^{2} for x_{#gamma} < 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
      fGeneralCrossJetCosThetaStarJetsLowTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsLowTrueNRec","true and rec. cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
      fGeneralCrossMJMatchCosThetaStarJetsLowTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsLowTrueNRec","true and rec. cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

      // High: x_gamma < 0.75
      fGeneralCrossJetMJetsHighTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsHighTrueNRec","true and rec.M_{jj} for x_{#gamma} #geq 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
      fGeneralCrossJetDPhiJetsHighTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsHighTrueNRec","true and rec.#Delta #phi _{jj} for x_{#gamma} #geq 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
      fGeneralCrossJetDRJetsHighTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsHighTrueNRec","true and rec.#Delta R_{jj} for x_{#gamma} #geq 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
      fGeneralCrossJetPtJetsHighTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsHighTrueNRec","true and rec.p_{T,jj}^{2} for x_{#gamma} #geq 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
      fGeneralCrossJetCosThetaStarJetsHighTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsHighTrueNRec","true and rec. cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
      fGeneralCrossMJMatchCosThetaStarJetsHighTrueNRec = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsHighTrueNRec","true and rec. cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
      //--------------------------
    fGeneralCrossMuonRegionsPartTrue = gHistogrammer->TH1DFactory("MC","CrossMuonRegionsPartTrue","true #mu regions",crossmuonregionbins,crossmuonregionlow,crossmuonregionhigh,"#mu region","Events");
    fGeneralCrossMuonPtPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtPartTrue","true p_{T}^{#mu}",crosspt_nbins,crosspt_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonEtaPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaPartTrue","true #eta^{#mu}",crosseta_nbins,crosseta_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonPtFinePartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtFinePartTrue","true p_{T}^{#mu}",crossptfine_nbins,crossptfine_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonEtaFinePartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaFinePartTrue","true #eta^{#mu}",crossetafine_nbins,crossetafine_bins,"#eta^{#mu}","Events");
    fGeneralCrossMuonPtMassimoPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonPtMassimoPartTrue","true p_{T}^{#mu}",crossptmassimo_nbins,crossptmassimo_bins,"p_{T}^{#mu}","Events");
    fGeneralCrossMuonEtaMassimoPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonEtaMassimoPartTrue","true #eta^{#mu}",crossetamassimo_nbins,crossetamassimo_bins,"#eta^{#mu}","Events");
    //_______________
    fGeneralCrossMuonJetPtPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetPtPartTrue","true p_{T}^{#mu-jet}",crossmuonjetpt_nbins,crossmuonjetpt_bins,"p_{T}^{#mu-jet}","Events");
    fGeneralCrossMuonJetEtaPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetEtaPartTrue","true #eta^{#mu-jet}",crossmuonjeteta_nbins,crossmuonjeteta_bins,"#eta^{#mu-jet}","Events");
    fGeneralCrossMuonJetPtFinePartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetPtFinePartTrue","true p_{T}^{#mu-jet}",crossmuonjetptfine_nbins,crossmuonjetptfine_bins,"p_{T}^{#mu-jet}","Events");
    fGeneralCrossMuonJetEtaFinePartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMuonJetEtaFinePartTrue","true #eta^{#mu-jet}",crossmuonjetetafine_nbins,crossmuonjetetafine_bins,"#eta^{#mu-jet}","Events");
    fGeneralCrossJetXGammaPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetXGammaPartTrue","true x_{#gamma}",crossjetxgamma_nbins,crossjetxgamma_bins,"x_{#gamma}","Events");
    fGeneralCrossJetXGammaFinePartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetXGammaFinePartTrue","true x_{#gamma}",crossjetxgammafine_nbins,crossjetxgammafine_bins,"x_{#gamma}","Events");
    fGeneralCrossJetMJetsPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsPartTrue","true M_{jj}",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsPartTrue","true #Delta #phi _{jj}",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsPartTrue","true #Delta R_{jj}",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsPartTrue","true p_{T,jj}^{2}",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsPartTrue","true cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsPartTrue","true cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

    // Low: x_gamma < 0.75
    fGeneralCrossJetMJetsLowPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsLowPartTrue","true M_{jj} for x_{#gamma} < 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsLowPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsLowPartTrue","true #Delta #phi _{jj} for x_{#gamma} < 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsLowPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsLowPartTrue","true #Delta R_{jj} for x_{#gamma} < 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsLowPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsLowPartTrue","true p_{T,jj}^{2} for x_{#gamma} < 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsLowPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsLowPartTrue","true cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsLowPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsLowPartTrue","true cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

    // High: x_gamma >= 0.75
    fGeneralCrossJetMJetsHighPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetMJetsHighPartTrue","true M_{jj} for x_{#gamma} #geq 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsHighPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDPhiJetsHighPartTrue","true #Delta #phi _{jj} for x_{#gamma} #geq 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsHighPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetDRJetsHighPartTrue","true #Delta R_{jj} for x_{#gamma} #geq 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsHighPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetPtJetsHighPartTrue","true p_{T,jj}^{2} for x_{#gamma} #geq 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsHighPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossJetCosThetaStarJetsHighPartTrue","true cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsHighPartTrue = gHistogrammer->TH1DVarFactory("MC","CrossMJMatchCosThetaStarJetsHighPartTrue","true cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

      //___________________________________________________
    fGeneralMCDeltaRTrue = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtrue","true #Delta R",100,0.,5.,"#Delta R","MCDIMuons");
    fGeneralMCDeltaRTrue_lu = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtrue_lu","true_lu #Delta R",100,0.,5.,"#Delta R","MCDIMuons_lu");
    fGeneralMCDeltaRTrue_ll = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtrue_ll","true_ll #Delta R",100,0.,5.,"#Delta R","MCDIMuons_ll");
    fGeneralMCDeltaRTrue_hu = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtrue_hu","true_hu #Delta R",100,0.,5.,"#Delta R","MCDIMuons_hu");
    fGeneralMCDeltaRTrue_hl = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtrue_hl","true_hl #Delta R",100,0.,5.,"#Delta R","MCDIMuons_hl");
    fGeneralMCDeltaRTrueNRec = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtruenrec","truenrec #Delta R",100,0.,5.,"#Delta R","MCDIMuons");
    fGeneralMCDeltaRTrueNRec_lu = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtruenrec_lu","truenrec_lu #Delta R",100,0.,5.,"#Delta R","MCDIMuons_lu");
    fGeneralMCDeltaRTrueNRec_ll = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtruenrec_ll","truenrec_ll #Delta R",100,0.,5.,"#Delta R","MCDIMuons_ll");
    fGeneralMCDeltaRTrueNRec_hu = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtruenrec_hu","truenrec_hu #Delta R",100,0.,5.,"#Delta R","MCDIMuons_hu");
    fGeneralMCDeltaRTrueNRec_hl = gHistogrammer->TH1DFactory("DIMuon","MCDIMuonDRtruenrec_hl","truenrec_hl #Delta R",100,0.,5.,"#Delta R","MCDIMuons_hl");
    
    fGeneralMCDeltaPhiTrue = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_true","#Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","MCDIMuons");
    fGeneralMCDeltaPhiTrue_lu = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_lu_true","#Delta#phi_lu_true",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_true","MCDIMuons_lu");
    fGeneralMCDeltaPhiTrue_ll = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_ll_true","#Delta#phi_ll_true",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_true","MCDIMuons_ll");
    fGeneralMCDeltaPhiTrue_hu = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hu_true","#Delta#phi_hu_true",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_true","MCDIMuons_hu");
    fGeneralMCDeltaPhiTrue_hl = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hl_true","#Delta#phi_hl_true",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_true","MCDIMuons_hl");
    fGeneralMCDeltaPhiTrueNRec = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_truenrec","#Delta#phi",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi","MCDIMuons");
    fGeneralMCDeltaPhiTrueNRec_lu = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_lu_truenrec","#Delta#phi_lu_truenrec",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_lu_truenrec","MCDIMuons_lu");
    fGeneralMCDeltaPhiTrueNRec_ll = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_ll_truenrec","#Delta#phi_ll_truenrec",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_ll_truenrec","MCDIMuons_ll");
    fGeneralMCDeltaPhiTrueNRec_hu = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hu_truenrec","#Delta#phi_hu_truenrec",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hu_truenrec","MCDIMuons_hu");
    fGeneralMCDeltaPhiTrueNRec_hl = gHistogrammer->TH1DFactory("DIMuon","DeltaPhi_hl_truenrec","#Delta#phi_hl_truenrec",deltaphibins,deltaphilow,deltaphihigh,"#Delta#phi_hl_truenrec","MCDIMuons_hl");
    
    if ( gCards->GetFMCK() ) CreateFake();    

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GMCs::FillGeneral() called" << endl << endl;

  if ( gCards->GetMcGeneral() ) {
    fGeneralY_uncut->Fill(gData->Getmc_y());
    fGeneralX_uncut->Fill(gData->Getmc_x());
    fGeneralQ2_uncut->Fill(TMath::Log10(gData->Getmc_q2()));
    
    if ( GetAllPartMCCuts() ) {
      GJet *jet1 = GetMCPMJetWithID(fPartIndex1);
      GJet *jet2 = GetMCPMJetWithID(fPartIndex2);
      if ( (jet1!=0)&&(jet2!=0) ) {
	if ( IsMuonAssociatedToMCPMJet(jet1) || IsMuonAssociatedToMCPMJet(jet2) ) {
	  fGeneralCrossJetXGammaPartTrue->Fill(fPartXGammaJets_zufo);
	  fGeneralCrossJetXGammaFinePartTrue->Fill(fPartXGammaJets_zufo);
	  fGeneralCrossJetMJetsPartTrue->Fill(fPartMJets);
	  fGeneralCrossJetDPhiJetsPartTrue->Fill(fPartDPhiJets);
	  fGeneralCrossJetDRJetsPartTrue->Fill(fPartDRJets);
	  fGeneralCrossJetPtJetsPartTrue->Fill(fPartPtJets);
	  fGeneralCrossJetCosThetaStarJetsPartTrue->Fill(fPartCosThetaStarJets);
	  
	  
	  if ( fPartXGammaJets_zufo < 0.75 ) {
	    fGeneralCrossJetMJetsLowPartTrue->Fill(fPartMJets);
	    fGeneralCrossJetDPhiJetsLowPartTrue->Fill(fPartDPhiJets);
	    fGeneralCrossJetDRJetsLowPartTrue->Fill(fPartDRJets);
	    fGeneralCrossJetPtJetsLowPartTrue->Fill(fPartPtJets);
	    fGeneralCrossJetCosThetaStarJetsLowPartTrue->Fill(fPartCosThetaStarJets);
	  }
	  
	  if ( fPartXGammaJets_zufo >= 0.75 ) {
	    fGeneralCrossJetMJetsHighPartTrue->Fill(fPartMJets);
	    fGeneralCrossJetDPhiJetsHighPartTrue->Fill(fPartDPhiJets);
	    fGeneralCrossJetDRJetsHighPartTrue->Fill(fPartDRJets);
	    fGeneralCrossJetPtJetsHighPartTrue->Fill(fPartPtJets);
	    fGeneralCrossJetCosThetaStarJetsHighPartTrue->Fill(fPartCosThetaStarJets);
	  }
	}
      }
    }      
    if ( GetAllMCCuts() ) {
      GJet *jet1 = GetMCHBMJetWithID(fIndex1);
      GJet *jet2 = GetMCHBMJetWithID(fIndex2);
      if ( (jet1!=0)&&(jet2!=0) ) {
	if ( IsMuonAssociatedToMCJet(jet1) || IsMuonAssociatedToMCJet(jet2) ) {
	  fGeneralCrossJetXGammaTrue->Fill(fXGammaJets_zufo);
	  fGeneralCrossTotalEventTrue->Fill(0.5);
	  fGeneralCrossJetXGammaFineTrue->Fill(fXGammaJets_zufo);
	  fGeneralCrossJetMJetsTrue->Fill(fMJets);
	  fGeneralCrossJetDPhiJetsTrue->Fill(fDPhiJets);
	  fGeneralCrossJetDRJetsTrue->Fill(fDRJets);
	  fGeneralCrossJetPtJetsTrue->Fill(fPtJets);
	  fGeneralCrossJetCosThetaStarJetsTrue->Fill(fCosThetaStarJets);
	  
	  
	  if ( fXGammaJets_zufo < 0.75 ) {
	    fGeneralCrossJetMJetsLowTrue->Fill(fMJets);
	    fGeneralCrossJetDPhiJetsLowTrue->Fill(fDPhiJets);
	    fGeneralCrossJetDRJetsLowTrue->Fill(fDRJets);
	    fGeneralCrossJetPtJetsLowTrue->Fill(fPtJets);
	    fGeneralCrossJetCosThetaStarJetsLowTrue->Fill(fCosThetaStarJets);
	  }

	  if ( fXGammaJets_zufo >= 0.75 ) {
	    fGeneralCrossJetMJetsHighTrue->Fill(fMJets);
	    fGeneralCrossJetDPhiJetsHighTrue->Fill(fDPhiJets);
	    fGeneralCrossJetDRJetsHighTrue->Fill(fDRJets);
	    fGeneralCrossJetPtJetsHighTrue->Fill(fPtJets);
	    fGeneralCrossJetCosThetaStarJetsHighTrue->Fill(fCosThetaStarJets);
	  }

	  // mc rec and true plots
	  if ( GetAllMCCuts() && gHeader->GetAllCuts() ) {
	    if ( (jet1->GetAssociatedMCJet()!=0)&&(jet2->GetAssociatedMCJet()!=0) ) {
	      fGeneralCrossJetXGammaTrueNRec->Fill(fXGammaJets_zufo);
	      fGeneralCrossTotalEventTrueNRec->Fill(0.5);
	      fGeneralCrossJetXGammaFineTrueNRec->Fill(fXGammaJets_zufo);
	      fGeneralCrossJetMJetsTrueNRec->Fill(fMJets);
	      fGeneralCrossJetDPhiJetsTrueNRec->Fill(fDPhiJets);
	      fGeneralCrossJetDRJetsTrueNRec->Fill(fDRJets);
	      fGeneralCrossJetPtJetsTrueNRec->Fill(fPtJets);
	      fGeneralCrossJetCosThetaStarJetsTrueNRec->Fill(fCosThetaStarJets);

	      if ( fXGammaJets_zufo < 0.75 ) {
		fGeneralCrossJetMJetsLowTrueNRec->Fill(fMJets);
		fGeneralCrossJetDPhiJetsLowTrueNRec->Fill(fDPhiJets);
		fGeneralCrossJetDRJetsLowTrueNRec->Fill(fDRJets);
		fGeneralCrossJetPtJetsLowTrueNRec->Fill(fPtJets);
		fGeneralCrossJetCosThetaStarJetsLowTrueNRec->Fill(fCosThetaStarJets);
	      }

	      if ( fXGammaJets_zufo >= 0.75 ) {
		fGeneralCrossJetMJetsHighTrueNRec->Fill(fMJets);
		fGeneralCrossJetDPhiJetsHighTrueNRec->Fill(fDPhiJets);
		fGeneralCrossJetDRJetsHighTrueNRec->Fill(fDRJets);
		fGeneralCrossJetPtJetsHighTrueNRec->Fill(fPtJets);
		fGeneralCrossJetCosThetaStarJetsHighTrueNRec->Fill(fCosThetaStarJets);
	      }

	    }
	  }
	}
      }
    }

    // logarithmic scale, to avoid NAN entries du to occasionally negative true Q2, only if Q2 > e19
    if ( gData->Getmc_q2() > 1e-9 ) {
      if ( gTrigger->GetAllCuts() ) {
	if ( gData->Getmc_q2() <= 1e-9 ) {
	  fGeneralQ2_1->Fill(TMath::Log10(1e-9));
	} else {
	  fGeneralQ2_1->Fill(TMath::Log10(gData->Getmc_q2()));
	}
      }
      if ( gTrigger->GetAllCuts() && gSinistra->GetAllCuts() ) {
	if ( gData->Getmc_q2() <= 1e-9 ) {
	  fGeneralQ2_2->Fill(TMath::Log10(1e-9));
	} else {
	  fGeneralQ2_2->Fill(TMath::Log10(gData->Getmc_q2()));
	}
      }
      if ( gTrigger->GetAllCuts() && gSinistra->GetAllCuts() && gZufo->GetAllCuts() ) {
	if ( gData->Getmc_q2() <= 1e-9 ) {
	  fGeneralQ2_3->Fill(TMath::Log10(1e-9));
	} else {
	  fGeneralQ2_3->Fill(TMath::Log10(gData->Getmc_q2()));
	}
      }

      if ( gHeader->GetAllCuts() ) {
	if ( gData->Getmc_q2() <= 1e-9 ) {
	  fGeneralQ2->Fill(TMath::Log10(1e-9));
	} else {
	  fGeneralQ2->Fill(TMath::Log10(gData->Getmc_q2()));
	}
      }
    }
    if ( gHeader->GetAllCuts() ) {
      fGeneralY->Fill(gData->Getmc_y());
      fGeneralX->Fill(gData->Getmc_x());
    }

  }

  return kTRUE;
}
//_____________________________________________________________

Bool_t GMCs::CreateFake() {
  //
  // create fakemuon histograms
  if ( gDebug ) cout << endl << "GMCs::CreateFake() called" << endl << endl;

  if ( gCards->GetFMCK() ) {

    Int_t    ptbins     = 30;
    Double_t ptlow      = 0.;
    Double_t pthigh     = 15.;
    Int_t    etabins    = 23;
    Double_t etalow     = -2.0;
    Double_t etahigh    = 2.6;
    Int_t    phibins    = 72;   
    Double_t philow     = -TMath::Pi();    
    Double_t phihigh    =  TMath::Pi();    

  fFakeHadronAllPt              =  gHistogrammer->TH1DFactory("MC","TrueAllPt","Pt of all ",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeHadronAllEta_lowPt             =   gHistogrammer->TH1DFactory("MC","TrueAllEtalow","Eta of all  lowPt",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeHadronAllPhi_lowPt             =  gHistogrammer->TH1DFactory("MC","TrueAllPhilow","Phi of all lowPt",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeHadronAllEta_highPt             =   gHistogrammer->TH1DFactory("MC","TrueAllEtahigh","Eta of all  highPt",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeHadronAllPhi_highPt             =  gHistogrammer->TH1DFactory("MC","TrueAllPhihigh","Phi of all  highPt",phibins,philow,phihigh,"Phi_{true}","Events");

  fFakeHadronPionPt              =  gHistogrammer->TH1DFactory("MC","TruePionPt","Pt of all Pions",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeHadronPionEta_lowPt             =   gHistogrammer->TH1DFactory("MC","TruePionEtalow","Eta of all Pions lowPt",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeHadronPionPhi_lowPt             =  gHistogrammer->TH1DFactory("MC","TruePionPhilow","Phi of all Pions lowPt",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeHadronPionEta_highPt             =   gHistogrammer->TH1DFactory("MC","TruePionEtahigh","Eta of all Pions highPt",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeHadronPionPhi_highPt             =  gHistogrammer->TH1DFactory("MC","TruePionPhihigh","Phi of all Pions highPt",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeHadronKaonPt              =  gHistogrammer->TH1DFactory("MC","TrueKaonPt","Pt of all Kaons",ptbins,ptlow,pthigh,"Pt_{true}","Events");
  fFakeHadronKaonEta_lowPt             =   gHistogrammer->TH1DFactory("MC","TrueKaonEtalow","Eta of all Kaons lowPt",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeHadronKaonPhi_lowPt             =  gHistogrammer->TH1DFactory("MC","TrueKaonPhilow","Phi of all Kaons lowPt",phibins,philow,phihigh,"Phi_{true}","Events");
  fFakeHadronKaonEta_highPt             =   gHistogrammer->TH1DFactory("MC","TrueKaonEtahigh","Eta of all Kaons highPt",etabins,etalow,etahigh,"Eta_{true}","Events");
  fFakeHadronKaonPhi_highPt             =  gHistogrammer->TH1DFactory("MC","TrueKaonPhihigh","Phi of all Kaons highPt",phibins,philow,phihigh,"Phi_{true}","Events");

  fFakeProbabilityAllPt         =  gHistogrammer->TH1DFactory("MC","ProbabilityAllPt","Fake Probability Pt dependence ",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeProbabilityAllEta_lowPt        =   gHistogrammer->TH1DFactory("MC","ProbabilityAllEtalow","Fake Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityAllPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","ProbabilityAllPhilow","Fake Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeProbabilityAllEta_highPt        =   gHistogrammer->TH1DFactory("MC","ProbabilityAllEtahigh","Fake Probability Eta dependence ",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityAllPhi_highPt        =  gHistogrammer->TH1DFactory("MC","ProbabilityAllPhihigh","Fake Probability Phi dependence ",phibins,philow,phihigh,"Phi_{true}","Fake Probability");

  fFakeProbabilityPionPt         =  gHistogrammer->TH1DFactory("MC","ProbabilityPionPt","Fake Probability Pt dependence (Pion)",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeProbabilityPionEta_lowPt        =   gHistogrammer->TH1DFactory("MC","ProbabilityPionEtalow","Fake Probability Eta dependence (Pion)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityPionPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","ProbabilityPionPhilow","Fake Probability Phi dependence (Pion)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeProbabilityPionEta_highPt        =   gHistogrammer->TH1DFactory("MC","ProbabilityPionEtahigh","Fake Probability Eta dependence (Pion)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityPionPhi_highPt        =  gHistogrammer->TH1DFactory("MC","ProbabilityPionPhihigh","Fake Probability Phi dependence (Pion)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeProbabilityKaonPt         =  gHistogrammer->TH1DFactory("MC","ProbabilityKaonPt","Fake Probability Pt dependence (Kaons)",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeProbabilityKaonEta_lowPt        =   gHistogrammer->TH1DFactory("MC","ProbabilityKaonEtalow","Fake Probability Eta dependence (Kaons)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityKaonPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","ProbabilityKaonPhilow","Fake Probability Phi dependence (Kaons)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeProbabilityKaonEta_highPt        =   gHistogrammer->TH1DFactory("MC","ProbabilityKaonEtahigh","Fake Probability Eta dependence (Kaons)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeProbabilityKaonPhi_highPt        =  gHistogrammer->TH1DFactory("MC","ProbabilityKaonPhihigh","Fake Probability Phi dependence (Kaons)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  //-------decays
  fFakeDecayProbabilityPionPt         =  gHistogrammer->TH1DFactory("MC","DecayProbabilityPionPt","Fake Probability from Decays Pt dependence (Pion)",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeDecayProbabilityPionEta_lowPt        =   gHistogrammer->TH1DFactory("MC","DecayProbabilityPionEtalow","Fake Probability from Decays Eta dependence (Pion)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeDecayProbabilityPionPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","DecayProbabilityPionPhilow","Fake Probability from Decays Phi dependence (Pion)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeDecayProbabilityPionEta_highPt        =   gHistogrammer->TH1DFactory("MC","DecayProbabilityPionEtahigh","Fake Probability from Decays Eta dependence (Pion)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeDecayProbabilityPionPhi_highPt        =  gHistogrammer->TH1DFactory("MC","DecayProbabilityPionPhihigh","Fake Probability from Decays Phi dependence (Pion)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeDecayProbabilityKaonPt         =  gHistogrammer->TH1DFactory("MC","DecayProbabilityKaonPt","Fake Probability from Decays Pt dependence (Kaons)",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakeDecayProbabilityKaonEta_lowPt        =   gHistogrammer->TH1DFactory("MC","DecayProbabilityKaonEtalow","Fake Probability from Decays Eta dependence (Kaons)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeDecayProbabilityKaonPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","DecayProbabilityKaonPhilow","Fake Probability from Decays Phi dependence (Kaons)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakeDecayProbabilityKaonEta_highPt        =   gHistogrammer->TH1DFactory("MC","DecayProbabilityKaonEtahigh","Fake Probability from Decays Eta dependence (Kaons)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakeDecayProbabilityKaonPhi_highPt        =  gHistogrammer->TH1DFactory("MC","DecayProbabilityKaonPhihigh","Fake Probability from Decays Phi dependence (Kaons)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  //--- punch throughs
  fFakePunchProbabilityPionPt         =  gHistogrammer->TH1DFactory("MC","PunchProbabilityPionPt","Fake Probability from punch through Pt dependence (Pion)",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakePunchProbabilityPionEta_lowPt        =   gHistogrammer->TH1DFactory("MC","PunchProbabilityPionEtalow","Fake Probability  from punch through Eta dependence (Pion)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakePunchProbabilityPionPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","PunchProbabilityPionPhilow","Fake Probability  from punch through Phi dependence (Pion)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakePunchProbabilityPionEta_highPt        =   gHistogrammer->TH1DFactory("MC","PunchProbabilityPionEtahigh","Fake Probability  from punch through Eta dependence (Pion)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakePunchProbabilityPionPhi_highPt        =  gHistogrammer->TH1DFactory("MC","PunchProbabilityPionPhihigh","Fake Probability  from punch through Phi dependence (Pion)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakePunchProbabilityKaonPt         =  gHistogrammer->TH1DFactory("MC","PunchProbabilityKaonPt","Fake Probability  from punch through Pt dependence (Kaons)",ptbins,ptlow,pthigh,"Pt_{true}","Fake Probability");
  fFakePunchProbabilityKaonEta_lowPt        =   gHistogrammer->TH1DFactory("MC","PunchProbabilityKaonEtalow","Fake Probability  from punch through Eta dependence (Kaons)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakePunchProbabilityKaonPhi_lowPt        =  gHistogrammer->TH1DFactory("MC","PunchProbabilityKaonPhilow","Fake Probability  from punch through Phi dependence (Kaons)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");
  fFakePunchProbabilityKaonEta_highPt        =   gHistogrammer->TH1DFactory("MC","PunchProbabilityKaonEtahigh","Fake Probability  from punch through Eta dependence (Kaons)",etabins,etalow,etahigh,"Eta_{true}","Fake Probability");
  fFakePunchProbabilityKaonPhi_highPt        =  gHistogrammer->TH1DFactory("MC","PunchProbabilityKaonPhihigh","Fake Probability  from punch through Phi dependence (Kaons)",phibins,philow,phihigh,"Phi_{true}","Fake Probability");


  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::GetAllCuts() {
  //
  // get all cuts
  if ( gDebug ) cout << endl << "GMCs::GetAllCuts called" << endl << endl;

  Bool_t returny = kFALSE;


  if(fQ2SelectionCut){
    if ( gCards->GetMCLF() ) {
      if ( fHeavyFlavours && gCards->GetMCRejectHFL() ) {
	returny = kFALSE;
      }
      else returny = kTRUE;
    }
    else returny = kTRUE;
  }
  else returny = kFALSE;

  return returny;
}
  
//_____________________________________________________________

Bool_t GMCs::GetAllMCCuts() {
  //
  // get all cuts for selection this MC event
  if ( gDebug ) cout << endl << "GMCs::GetAllMCCuts called" << endl << endl;

  Bool_t returny = kFALSE;

  // check if massive MC jets with stable B mesons fulfill jet cuts
  // 2 jets with asymmetric pt cuts in eta-range
  if( !(gCards->GetDIMuonMCplots()) ) {
  if ( fMCHBMJetPtACut && fMCHBMJetPtBCut)
    // check for Q2 selection
    if ( fQ2SelectionCut ) 
      // check for Q2 range
      if ( fQ2Cut )
	// check for y cut
	if ( fYCut )
	  // check muon cuts
	  if ( fMuonCuts ) 
	    returny = kTRUE;
  
  }
  else if( gCards->GetDIMuonMCplots() ) {
    //    if( fMCDIMuonCuts ) returny = kTRUE;
    if( fMCDIMuonCuts && fQ2SelectionCut ) returny = kTRUE; // included q2 cut for true definition 050531 (had not been there for total xsec!)
  }
  return returny;
}
//_____________________________________________________________

Bool_t GMCs::GetAllPartMCCuts() {
  //
  // get all cuts for selection this MC event
  if ( gDebug ) cout << endl << "GMCs::GetAllPartMCCuts called" << endl << endl;
  
  Bool_t returny = kFALSE;

  // check if massive MC jets with stable B mesons fulfill jet cuts
  // 2 jets with asymmetric pt cuts in eta-range
  if ( fMCPMJetPtACut && fMCPMJetPtBCut){
    // check for Q2 selection
    if ( fQ2SelectionCut ) {
      // cout << " check for Q2 range " << endl;
	if ( fQ2Cut ){
	  //  cout << "	// check for y cut " << endl;
	  if ( fYCut ){
	    //  cout<< "	  // check muon cuts " << endl;
	  if ( fMuonCuts ) 
	    returny = kTRUE;
	  }
	}
    }
  }
  return returny;
}

//_____________________________________________________________

Bool_t GMCs::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GMCs::FillHistos() called" << endl << endl;

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMCs::ObjectsFillHistos() called" << endl << endl;
  

  // loop over mcdimuons array ingo
  GDIMuon *mcdimuon = 0;
  //  for ( Int_t i = 0; i < fNMCDIMuons; i++ ) {
  if(fNMCDIMuons>0){
    //    for ( Int_t i = 0; i < 1; i++ ) { // VERY DIRTY! like this: take first dimuon only. NEED: "chosen dimuon"-flag and ask when filling. Implement this! 050411
    for ( Int_t i = 0; i < fNMCDIMuons; i++ ) { 
      mcdimuon = ((GDIMuon*)(fMCDIMuons->At(i)));
      
      // fill general plots

      ObjectsFillGeneralMCDIMuons(mcdimuon);
      // stop loop as soon as one dimuon has fulfilled the true cuts:
      if( GetAllMCCuts() && mcdimuon->GetMCDIMuonHFLCut() ) break;
      // use this to plot first dimuon only:
      //      if(i != 0) break;
      // fill control plots
      //    ObjectsFillControlMCDIMuons(mcdimuon);
      
    }
  }


  // loop over jets array
  GJet *mc_jet = 0;
  for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
    mc_jet = ((GJet*)(fMCHBMJets->At(i)));

    // fill general plots
    ObjectsFillGeneralJets(mc_jet);
    
    // fill control plots
    ObjectsFillControlJets(mc_jet);

  }
  // loop over partonlevel jets
  GJet *partjet = 0;
  for ( Int_t j = 0; j < fNMCPMJets; j++ ) {
    partjet =((GJet*)( fMCPMJets->At(j)));
    ObjectsFillGeneralPMJets(partjet);
  }

  // loop over array
  for ( Int_t i = 0; i < fNMCs; i++ ) {
    GMC *mc = ((GMC*)(fMCs->At(i)));

    // fill general plots
    ObjectsFillGeneral(mc);
    
    // fill control plots
    ObjectsFillControl(mc);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::ObjectsFillGeneral(GMC *mc) {
  //
  // fill general histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMCs::ObjectsFillGeneral() called" << endl << endl;

  if ( gCards->GetMcGeneral() ) {

      if(mc->GetChosenMCMuon()){
	GJet *mc_jet = mc->GetAssociatedMCJetToMCMuon();
	GJet *mc_jet2 = mc->GetSecondAssociatedMCJetToMCMuon();
	if(mc_jet){
	  Double_t deltaR = mc_jet->DeltaR(*mc);
	  fGeneralDeltaRMuonJet->Fill(deltaR);
	}
	if(mc_jet2){
	  Double_t deltaR = mc_jet2->DeltaR(*mc);
	  fGeneralDeltaRMuonSecondJet->Fill(deltaR);
	}
	if(mc_jet && mc_jet2){
	  Double_t deltaR = mc_jet->DeltaR(*mc);
	  Double_t deltaR2 = mc_jet2->DeltaR(*mc);
	  fGeneralDeltaRMuonJet2D->Fill(deltaR,deltaR2);
	}
      }
    if ( GetAllPartMCCuts() ) {
      if (( mc->GetMCMuonType() == kMCChosenForwardMuon) &&(IsPMJetAssociatedToMCMuon(mc))) {
	fGeneralCrossMuonRegionsPartTrue->Fill(2.5);
      } else if (( mc->GetMCMuonType() == kMCChosenBarrelMuon) &&(IsPMJetAssociatedToMCMuon(mc))) {
	fGeneralCrossMuonRegionsPartTrue->Fill(1.5);
      } else if (( mc->GetMCMuonType() == kMCChosenRearMuon) &&(IsPMJetAssociatedToMCMuon(mc))) {
	fGeneralCrossMuonRegionsPartTrue->Fill(0.5);
      }
      if ( (mc->GetMCMuonType() == kMCChosenForwardMuon) || (mc->GetMCMuonType() == kMCChosenBarrelMuon) || (mc->GetMCMuonType() == kMCChosenRearMuon) ) {
	if(IsPMJetAssociatedToMCMuon(mc)){
	  fGeneralCrossMuonPtPartTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaPartTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtFinePartTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaFinePartTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtMassimoPartTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaMassimoPartTrue->Fill(mc->Eta());
	}
      }
    }
    // mc true plots
    if ( GetAllMCCuts() ) {
      if (( mc->GetMCMuonType() == kMCChosenForwardMuon) &&(IsJetAssociatedToMCMuon(mc))) {
	fGeneralCrossMuonRegionsTrue->Fill(2.5);
	fGeneralCrossMuonFinderTrue->Fill(10.5);
	fGeneralCrossMuonFinderTrue->Fill(11.5);
	fGeneralCrossMuonFinderTrue->Fill(12.5);
	fGeneralCrossMuonFinderTrue->Fill(13.5);
	fGeneralCrossMuonFinderTrue->Fill(14.5);

      } else if (( mc->GetMCMuonType() == kMCChosenBarrelMuon) &&(IsJetAssociatedToMCMuon(mc))) {
	fGeneralCrossMuonRegionsTrue->Fill(1.5);
	fGeneralCrossMuonFinderTrue->Fill(0.5);
	fGeneralCrossMuonFinderTrue->Fill(1.5);
	fGeneralCrossMuonFinderTrue->Fill(2.5);
	fGeneralCrossMuonFinderTrue->Fill(3.5);
	fGeneralCrossMuonFinderTrue->Fill(4.5);
      } else if (( mc->GetMCMuonType() == kMCChosenRearMuon) &&(IsJetAssociatedToMCMuon(mc))) {
	fGeneralCrossMuonRegionsTrue->Fill(0.5);
	fGeneralCrossMuonFinderTrue->Fill(5.5);
	fGeneralCrossMuonFinderTrue->Fill(6.5);
	fGeneralCrossMuonFinderTrue->Fill(7.5);
	fGeneralCrossMuonFinderTrue->Fill(8.5);
	fGeneralCrossMuonFinderTrue->Fill(9.5);
	
      }
      if ( (mc->GetMCMuonType() == kMCChosenForwardMuon) || (mc->GetMCMuonType() == kMCChosenBarrelMuon) || (mc->GetMCMuonType() == kMCChosenRearMuon) ) {
	if(IsJetAssociatedToMCMuon(mc)){
	      GJet *mc_jet = 0;
	      mc_jet=mc->GetAssociatedMCJetToMCMuon();
	      //	      cout << "is jet to muon? mc id " << mc->GetFMCKINID() << " jetid " << mc_jet->GetID()<< endl;
	  fGeneralCrossTotalTrue->Fill(0.5);
	  fGeneralCrossTotalAssociatedTrue->Fill(0.5);
  	  fGeneralCrossMuonPtTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtFineTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaFineTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtMassimoTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaMassimoTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtNoJetTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaNoJetTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtFineNoJetTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaFineNoJetTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtMassimoNoJetTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaMassimoNoJetTrue->Fill(mc->Eta());

	}else{
	  fGeneralCrossTotalTrue->Fill(0.5);
	  fGeneralCrossMuonPtNoJetTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaNoJetTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtFineNoJetTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaFineNoJetTrue->Fill(mc->Eta());
	  fGeneralCrossMuonPtMassimoNoJetTrue->Fill(mc->Pt());
	  fGeneralCrossMuonEtaMassimoNoJetTrue->Fill(mc->Eta());

	}
      }
    }
  
    // mc rec and true plots
    if ( GetAllMCCuts() && gHeader->GetAllCuts() ) {
      
      // muon plots where chosen reconstructed muon is this selected true muon
      if ( mc->GetMuon() != 0 ) {
      
      // Ingo dirty test paste:
	if( mc->GetMuonDirectParent() != 0 ) {
	  //	  if( CheckBParent(mc->GetMuonDirectParent()->GetPartID()) || CheckCParent(mc->GetMuonDirectParent()->GetPartID()) ){
	  //	  cout<<"Filling MC muon from parent with ID: "<<mc->GetMuonDirectParent()->GetPartID()<<endl;
	  if( mc->GetMuonBQuark() != 0){
	    if( !( CheckBParent(mc->GetMuonDirectParent()->GetPartID()) || CheckCParent(mc->GetMuonDirectParent()->GetPartID()) ) && 
		( mc->GetMuonBQuark()->GetPartID() == 9 || mc->GetMuonBQuark()->GetPartID() == 10 ) ){
	      //	      cout<<"NOTTTTT Filling MC muon from parent with ID: "<<mc->GetMuonDirectParent()->GetPartID()<<endl;
	      //	      cout<<"though muon comes from b quark!!"<<endl;
	      //	      cout<<mc->GetMuonDirectParent()->GetPartID()<<endl;
	    }
	  }
	  fGeneralMuParentPhiTrueNRec->Fill( mc->GetMuonDirectParent()->Phi(),mc->GetMuon()->Phi() );
	  fGeneralMuParentPhiResTrueNRec->Fill( (mc->GetMuonDirectParent()->DeltaPhi( *((GMC *)mc->GetMuon()) ))*180./TMath::Pi() );
	  fGeneralMuParentDRResTrueNRec->Fill(   mc->GetMuonDirectParent()->DeltaR( *(mc->GetMuon()) ) );
	  fGeneralMuParentPTResTrueNRec->Fill(   mc->GetMuonDirectParent()->Pt() - mc->GetMuon()->Pt() );
	  //	  }
	}
	//	if( mc->GetMother() != 0) {
	if( mc->GetMuonBQuark() != 0) {
	  //	  GMC *quark = mc->GetMuon()->GetMCQuark(); // to get MCQuark of reconstructed muon
	  //      mc->GetMuonBQuark() // to geht b quark of true muon
	  if( mc->GetMuonBQuark()->GetPartID() == 9 || mc->GetMuonBQuark()->GetPartID() == 10  ){
	    //	    cout<<"Filling MC muon from quark with ID: "<<mc->GetMuonBQuark()->GetPartID()<<endl<<endl;
	    fGeneralMuQuarkPhiTrueNRec->Fill( mc->GetMuonBQuark()->Phi(),mc->GetMuon()->Phi() );
	    fGeneralMuQuarkPhiResTrueNRec->Fill( (mc->GetMuonBQuark()->DeltaPhi( *((GMC *)mc->GetMuon()) ))*180./TMath::Pi() );
	    fGeneralMuQuarkDRResTrueNRec->Fill(   mc->GetMuonBQuark()->DeltaR( *((GMC *)mc->GetMuon()) ) );
	    fGeneralMuQuarkPTResTrueNRec->Fill(   mc->GetMuonBQuark()->Pt() -  mc->GetMuon()->Pt() );
	  }
	}
	
	if ( mc->GetMuon()->GetMatched() || (mc->GetMuon()->GetAllCuts() && gCards->GetMUONFillAll()) ) {
	  if ( mc->GetMCMuonType() == kMCChosenForwardMuon ) {
	    fGeneralCrossMuonRegionsTrueNRec->Fill(2.5);
	    fGeneralCrossMuonRegionsNoJetTrueNRec->Fill(2.5);
	  } else if ( mc->GetMCMuonType() == kMCChosenBarrelMuon ) {
	    fGeneralCrossMuonRegionsTrueNRec->Fill(1.5);
	    fGeneralCrossMuonRegionsNoJetTrueNRec->Fill(1.5);
	  } else if ( mc->GetMCMuonType() == kMCChosenRearMuon ) {
	    fGeneralCrossMuonRegionsTrueNRec->Fill(0.5);
	    fGeneralCrossMuonRegionsNoJetTrueNRec->Fill(0.5);
	  }
	  if ( (mc->GetMCMuonType() == kMCChosenForwardMuon) || (mc->GetMCMuonType() == kMCChosenBarrelMuon) || (mc->GetMCMuonType() == kMCChosenRearMuon) ) {
	    
	    if(IsJetAssociatedToMCMuon(mc)){
	      fGeneralCrossTotalTrueNRec->Fill(0.5);
	      fGeneralCrossMuonPtTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaTrueNRec->Fill(mc->Eta());
	      fGeneralCrossMuonPtFineTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaFineTrueNRec->Fill(mc->Eta());
	      fGeneralCrossMuonPtMassimoTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaMassimoTrueNRec->Fill(mc->Eta());
	      fGeneralCrossTotalAssociatedTrueNRec->Fill(0.5);
	      fGeneralCrossMuonPtNoJetTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaNoJetTrueNRec->Fill(mc->Eta());
	      fGeneralCrossMuonPtFineNoJetTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaFineNoJetTrueNRec->Fill(mc->Eta());
	      fGeneralCrossMuonPtMassimoNoJetTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaMassimoNoJetTrueNRec->Fill(mc->Eta());
	      
	    }else{
	      fGeneralCrossTotalTrueNRec->Fill(0.5);
	      fGeneralCrossMuonPtNoJetTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaNoJetTrueNRec->Fill(mc->Eta());
	      fGeneralCrossMuonPtFineNoJetTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaFineNoJetTrueNRec->Fill(mc->Eta());
	      fGeneralCrossMuonPtMassimoNoJetTrueNRec->Fill(mc->Pt());
	      fGeneralCrossMuonEtaMassimoNoJetTrueNRec->Fill(mc->Eta());
	      
	    }
	  }
	}
      }
    }
  }
  if ( gCards->GetFMCK() && !(gCards->GetMCOwn()) ) {
    //    mc->CheckParticleType();

    if(mc->GetCharge()){
	fFakeHadronAllPt->Fill(mc->Pt());
	if(mc->Pt()>0.7&&mc->Pt()<1.5){
	fFakeHadronAllEta_lowPt->Fill(mc->Eta());   
	fFakeHadronAllPhi_lowPt->Fill(mc->Phi());
	}   
	if(mc->Pt()>1.5){
	fFakeHadronAllEta_highPt->Fill(mc->Eta());   
	fFakeHadronAllPhi_highPt->Fill(mc->Phi());   
	}
    }
    
      if(mc->GetPartID()>=54 && mc->GetPartID()<=56){
	fFakeHadronPionPt->Fill(mc->Pt());
	if(mc->Pt()>0.7&&mc->Pt()<1.5){
	fFakeHadronPionEta_lowPt->Fill(mc->Eta());   
	fFakeHadronPionPhi_lowPt->Fill(mc->Phi());
	}   
	if(mc->Pt()>1.5){
	fFakeHadronPionEta_highPt->Fill(mc->Eta());   
	fFakeHadronPionPhi_highPt->Fill(mc->Phi());   
	}
      }

      if(mc->GetPartID()>=58 && mc->GetPartID()<=59){
	fFakeHadronKaonPt->Fill(mc->Pt());
	if(mc->Pt()>0.7&&mc->Pt()<1.5){
	fFakeHadronKaonEta_lowPt->Fill(mc->Eta());   
	fFakeHadronKaonPhi_lowPt->Fill(mc->Phi());
	}
	if(mc->Pt()>0.7&&mc->Pt()<1.5){   
	fFakeHadronKaonEta_highPt->Fill(mc->Eta());   
	fFakeHadronKaonPhi_highPt->Fill(mc->Phi());   
	}
      }


  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::ObjectsFillControl(GMC *mc) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMCs::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetMcControl() ) {

  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::ObjectsFillGeneralJets(GJet *mc_jet) {
  //
  // fill general jet histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMCs::ObjectsFillGeneralJets() called" << endl << endl;

  if ( gCards->GetMcGeneral() ) {

    // mc true plots
  
    if ( GetAllMCCuts() ) {
      if ( IsMuonAssociatedToMCJet(mc_jet) ) {
	//	cout << " nr jets " << fcountjet << endl;

	//	cout << "is muonto jet: mc_jetid " << mc_jet->GetID()<< endl;
	fGeneralCrossMuonJetPtTrue->Fill(mc_jet->Pt());
	fGeneralCrossMuonJetEtaTrue->Fill(mc_jet->Eta());
	fGeneralCrossMuonJetPtFineTrue->Fill(mc_jet->Pt());
	fGeneralCrossMuonJetEtaFineTrue->Fill(mc_jet->Eta());
	if(mc_jet->GetMJCosThetaStar_MJets()>0 && mc_jet->GetMJCosThetaStar_EtaJets()< 99){
	  fGeneralCrossMJMatchCosThetaStarJetsTrue->Fill(mc_jet->GetMJCosThetaStar());
	  if ( fXGammaJets_zufo <= 0.75 ) fGeneralCrossMJMatchCosThetaStarJetsLowTrue->Fill(mc_jet->GetMJCosThetaStar()); 
	  if ( fXGammaJets_zufo >= 0.75 ) fGeneralCrossMJMatchCosThetaStarJetsHighTrue->Fill(mc_jet->GetMJCosThetaStar()); 
	}
	
	
      } 
    }
    
    // mc rec and true plots
    if ( GetAllMCCuts() && gHeader->GetAllCuts() ) {
      if ( IsMuonAssociatedToMCJet(mc_jet) ) {
	GJet *jet = mc_jet->GetAssociatedMCJet();
	if ( jet != 0 ) {
	  for ( Int_t i = 0; i < jet->GetMatched(); ++i ) {
	    fGeneralCrossMuonJetPtTrueNRec->Fill(mc_jet->Pt());
	    fGeneralCrossMuonJetEtaTrueNRec->Fill(mc_jet->Eta());
	    fGeneralCrossMuonJetPtFineTrueNRec->Fill(mc_jet->Pt());
	    fGeneralCrossMuonJetEtaFineTrueNRec->Fill(mc_jet->Eta());
	    if(mc_jet->GetMJCosThetaStar_MJets()>0 && mc_jet->GetMJCosThetaStar_EtaJets()< 99){
	      fGeneralCrossMJMatchCosThetaStarJetsHighTrueNRec->Fill(mc_jet->GetMJCosThetaStar());
	      if ( mc_jet->GetMJCosThetaStar_xgamma() <= 0.75 ) fGeneralCrossMJMatchCosThetaStarJetsTrueNRec->Fill(mc_jet->GetMJCosThetaStar());
	      if ( mc_jet->GetMJCosThetaStar_xgamma() >= 0.75 ) fGeneralCrossMJMatchCosThetaStarJetsLowTrueNRec->Fill(mc_jet->GetMJCosThetaStar());
	    }
	  }
	}
      }
    }
  }
  return kTRUE;
 }
 
//_____________________________________________________________
 
 Bool_t GMCs::ObjectsFillGeneralPMJets(GJet *mc_jet) {
   //
   // fill general jet histograms with data by looping over internal array
   if ( gDebug ) cout << endl << "GMCs::ObjectsFillGeneralPMJets() called" << endl << endl;
   
   if ( gCards->GetMcGeneral() ) {
     
     // mc true plots
     if ( GetAllPartMCCuts() ) {
       if ( IsMuonAssociatedToMCPMJet(mc_jet) ) {
	 fGeneralCrossMuonJetPtPartTrue->Fill(mc_jet->Pt());
	 fGeneralCrossMuonJetEtaPartTrue->Fill(mc_jet->Eta());
	 fGeneralCrossMuonJetPtFinePartTrue->Fill(mc_jet->Pt());
	 fGeneralCrossMuonJetEtaFinePartTrue->Fill(mc_jet->Eta());
	 if(mc_jet->GetMJCosThetaStar_MJets()>0 && mc_jet->GetMJCosThetaStar_EtaJets()< 99){
	   fGeneralCrossMJMatchCosThetaStarJetsPartTrue->Fill(mc_jet->GetMJCosThetaStar());
	   if (fPartXGammaJets_zufo <= 0.75 ) fGeneralCrossMJMatchCosThetaStarJetsLowPartTrue->Fill(mc_jet->GetMJCosThetaStar()); 
	   if ( fPartXGammaJets_zufo >= 0.75 ) fGeneralCrossMJMatchCosThetaStarJetsHighPartTrue->Fill(mc_jet->GetMJCosThetaStar()); 
	 }
       } 
     }
   }
   return kTRUE;
 }
 
 //_____________________________________________________________

Bool_t GMCs::ObjectsFillControlJets(GJet *mc_jet) {
  //
  // fill control jet histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMCs::ObjectsFillControlJets() called" << endl << endl;

  if ( gCards->GetMcControl() ) {

  }
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMCs::ObjectsFillGeneralMCDIMuons(GDIMuon *mcdimuon) {
  //
  // fill general dimuon histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMCs::ObjectsFillGeneralMCDIMuons() called" << endl << endl;

  GJet *jetfirst  = GetMCHBMJetWithID(fIndex1);
  GJet *jetsecond = GetMCHBMJetWithID(fIndex2);

  if ( gCards->GetMcGeneral() ) {

    Double_t invMass = mcdimuon->GetInvMass();
    Double_t deltaR  = mcdimuon->GetDeltaR();
    Double_t deltaPhi  = mcdimuon->GetDeltaPhi();

    // mc true plots
    if ( GetAllMCCuts() && mcdimuon->GetMCDIMuonHFLCut() ) {      
      fGeneralDimuMass_true_hflmu->Fill(invMass);
      fGeneralDimuMass1bin_true_hflmu->Fill(invMass);


      //       fGeneralDimuMass1bin_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
      //       fGeneralDimuMass1bin_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
      fGeneralDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
      fGeneralDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
      fGeneralDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Eta());
      fGeneralDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Eta());

/* Dijet Selection */

// Both Muons 
      if(jetfirst&&jetsecond){

	if( (jetfirst->DeltaR(*mcdimuon->GetMCMuon1())  < 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon2()) < 1.0 ) ||
	    (jetfirst->DeltaR(*mcdimuon->GetMCMuon2())  < 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon1()) < 1.0 ) ||
            (jetfirst->DeltaR(*mcdimuon->GetMCMuon1())  < 1.0 && jetfirst->DeltaR(*mcdimuon->GetMCMuon2()) < 1.0  ) ||
	    (jetsecond->DeltaR(*mcdimuon->GetMCMuon2()) < 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon1()) < 1.0 ) ){    
    
	  fGeneralDijetbothDimuMass1bin_true_hflmu->Fill(invMass);
	  fGeneralDijetbothDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
	  fGeneralDijetbothDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
	  fGeneralDijetbothDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Eta());
	  fGeneralDijetbothDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Eta());

	  if( mcdimuon->GetMCMuon1()->GetMuonBQuark() != 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark() != 0 ) {
	    if( mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID() !=  mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID() ) {
	      fGeneralDijetbothDimuxsecDphi_true_hflmu->Fill( TMath::Abs(deltaPhi) );
	    }
	  }
	}
      
// One Muon

	if(((jetfirst->DeltaR(*mcdimuon->GetMCMuon1()) < 1.0 || jetsecond->DeltaR(*mcdimuon->GetMCMuon1()) < 1.0 )  &&
            (jetfirst->DeltaR(*mcdimuon->GetMCMuon2()) > 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon2()) > 1.0 )) ||
	   ((jetfirst->DeltaR(*mcdimuon->GetMCMuon2()) < 1.0 || jetsecond->DeltaR(*mcdimuon->GetMCMuon2()) < 1.0 )  &&
	    (jetfirst->DeltaR(*mcdimuon->GetMCMuon1()) > 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon1()) > 1.0 ))){

	  fGeneralDijetoneDimuMass1bin_true_hflmu->Fill(invMass);
	  fGeneralDijetoneDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
	  fGeneralDijetoneDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
	  fGeneralDijetoneDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Eta());
	  fGeneralDijetoneDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Eta());
	  
	  if( mcdimuon->GetMCMuon1()->GetMuonBQuark() != 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark() != 0 ) {
	    if( mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID() !=  mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID() ) {
	      fGeneralDijetoneDimuxsecDphi_true_hflmu->Fill( TMath::Abs(deltaPhi) );
	    }
	  }
	}

// None of them

	if( (jetfirst->DeltaR(*mcdimuon->GetMCMuon1()) > 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon2()) > 1.0 ) &&
	    (jetfirst->DeltaR(*mcdimuon->GetMCMuon2()) > 1.0 && jetsecond->DeltaR(*mcdimuon->GetMCMuon1()) > 1.0 )){    

	  fGeneralDijetnoneDimuMass1bin_true_hflmu->Fill(invMass);
	  fGeneralDijetnoneDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
	  fGeneralDijetnoneDimuxsecPt_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
	  fGeneralDijetnoneDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon1()->Eta());
	  fGeneralDijetnoneDimuxsecEta_true_hflmu->Fill(mcdimuon->GetMCMuon2()->Eta());

	  if( mcdimuon->GetMCMuon1()->GetMuonBQuark() != 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark() != 0 ) {

	    if( mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID() !=  mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID() ) {
	      fGeneralDijetnoneDimuxsecDphi_true_hflmu->Fill( TMath::Abs(deltaPhi) );
	    }
	  }
	}
      }

/* End Dijet Selection */

      Double_t binx = 4.05;
      for(Int_t dd = 0; dd < 40 ; dd += 1){
	//	cout<<dd<<" is: "<<binx<<endl;
	if( binx < 7.0 ){
	fGeneralDimuxsecFinders_true_hflmu->Fill(binx);
	//	fGeneralDimuxsecFinders_true_hflmu->Fill(binx);
	}
	else{
	fGeneralDimuxsecFinders_true_hflmu->Fill(binx);
	}
	binx += 0.1;
      }

      if( mcdimuon->GetMCMuon1()->GetMuonBQuark() != 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark() != 0 ) {

	if( mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID() !=  mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID() ) {
	  fGeneralDimuxsecDR_true_hflmu->Fill(deltaR);
	  fGeneralDimuxsecDphi_true_hflmu->Fill( TMath::Abs(deltaPhi) );
	  
	}
	else{
	  // 	  cout<<"Same or no b quark on dimu: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with p, pTs, eta: : hflcut: "<<1*mcdimuon->GetMCDIMuonHFLCut()<<" eventhflcut: "<<1*fMCDIMuonCuts<<endl;
	  // 	  cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon1()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" parent id "<< mcdimuon->GetMCMuon1()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon1()->GetPartID()<<endl;
	  // 	  cout<<"dimuon: 2 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" parent id "<< mcdimuon->GetMCMuon2()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon2()->GetPartID()<<endl;
	}
      }

      //*** dimu xsecs ptb BEGIN ***;
      if(mcdimuon->GetMCMuon1()->GetMuonBMeson() !=0 && mcdimuon->GetMCMuon2()->GetMuonBMeson() != 0 ){
	if(mcdimuon->GetMCMuon1()->GetMuonBMeson()->GetPartID() != mcdimuon->GetMCMuon2()->GetMuonBMeson()->GetPartID() ){
	  // some safety printout in case the muons have different Bhadron parents but seem to come from the same quark:;
	  if(mcdimuon->GetMCMuon1()->GetMuonBQuark() != 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark() != 0){
	    if(mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID() ==  mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID()) {
	      cout<<"ALARM! Found event where 2 visible muons have a different BHadron parent, but come from the same bquark. r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<endl;
 	    cout<<"info mu1: b "<<mcdimuon->GetMCMuon1()->GetMuonBQuark()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->GetMuonBQuark()->Eta()<<" quark id "<< mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID()<<" q fmckinid "<<mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetFMCKINID()<<endl;
 	    cout<<"info mu2: b "<<mcdimuon->GetMCMuon2()->GetMuonBQuark()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->GetMuonBQuark()->Eta()<<" quark id "<< mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID()<<" q fmckinid "<<mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetFMCKINID()<<endl;
 	    cout<<"info mu1: B "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()->Eta()<<" meson id "<< mcdimuon->GetMCMuon1()->GetMuonBMeson()->GetPartID()<<" q fmckinid "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()->GetFMCKINID()<<endl;
 	    cout<<"info mu2: B "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()->Eta()<<" meson id "<< mcdimuon->GetMCMuon2()->GetMuonBMeson()->GetPartID()<<" q fmckinid "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()->GetFMCKINID()<<endl;
	    }
	  }
	  // fill pTb xsec for muons from diff. b quarks, 2 entries per event:;
	  fGeneralDimuxsecPtb_true_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt());
	  fGeneralDimuxsecPtb_true_hflmu->Fill(mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt());
	  
	  fGeneralDimuxsecPtb_diffb_true_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt());
	  fGeneralDimuxsecPtb_diffb_true_hflmu->Fill(mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt());
	  
	  fGeneralDimuxsecPtb_asym_true_hflmu->Fill(TMath::Abs(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt()-mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt())/(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt()+mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt()));

//  	  cout<<"Filling **diffB** mcdimuon: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with pTs, eta:"<<endl;
//  	  cout<<"dimuon: 1  Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" mu fmck id "<< mcdimuon->GetMCMuon1()->GetFMCKINID()<<" B fmck ID "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()->GetFMCKINID()<<endl;
//  	  cout<<"dimuon: 2  Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" mu fmck id "<< mcdimuon->GetMCMuon2()->GetFMCKINID()<<" B fmck ID "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()->GetFMCKINID()<<endl;
	}
	else {
	  // fill pTb xsec for muons from the same b quarks, 1 entry per event:
	  fGeneralDimuxsecPtb_true_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt());
	  fGeneralDimuxsecPtb_sameb_true_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt());
	  fGeneralDimuxsecPtb_samecone_true_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt());

//  	  cout<<"Filling   sameB   mcdimuon: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with pTs, eta:"<<endl;
//  	  cout<<"dimuon: 1  Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" mu fmck id "<< mcdimuon->GetMCMuon1()->GetFMCKINID()<<" B fmck ID "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()->GetFMCKINID()<<endl;
//  	  cout<<"dimuon: 2  Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" mu fmck id "<< mcdimuon->GetMCMuon2()->GetFMCKINID()<<" B fmck ID "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()->GetFMCKINID()<<endl;
	}
      }
      //*** dimu xsecs ptb END ***;
      
      if(mcdimuon->GetMCMuon1()->GetMuonBQuark()!= 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark()!= 0){
	fGeneralDimu_b_pt_true_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt());
	//	fGeneralDimu_b_pt_true_hflmu->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),gHeader->GetWeight());
      }

      //      cout<<endl<<"r/e"<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<"TRUE:  Event contains true dimuon!"<<endl;


      fGeneralMCDeltaRTrue->Fill(deltaR);
      if ( invMass <= 4 &&  mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrue_lu->Fill(deltaR);
      if ( invMass <= 4 && !mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrue_ll->Fill(deltaR);
      if ( invMass > 4  &&  mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrue_hu->Fill(deltaR);
      if ( invMass > 4  && !mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrue_hl->Fill(deltaR);
      fGeneralMCDeltaPhiTrue->Fill( TMath::Abs(deltaPhi));
      if ( invMass <= 4 &&  mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrue_lu->Fill( TMath::Abs(deltaPhi));
      if ( invMass <= 4 && !mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrue_ll->Fill( TMath::Abs(deltaPhi));
      if ( invMass > 4  &&  mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrue_hu->Fill( TMath::Abs(deltaPhi));
      if ( invMass > 4  && !mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrue_hl->Fill( TMath::Abs(deltaPhi));
    }

    // mc rec and true plots
    // is incomplete - need to check still whether mcmuons are gmuons
    if ( GetAllMCCuts() && mcdimuon->GetMCDIMuonHFLCut() && gHeader->GetAllCuts() ) {

      //      cout<<"r/e"<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<"TRUEnREC:  Event contains trueNrec dimuon!"<<endl;

      fGeneralDimuMass_truenrec_hflmu->Fill(invMass,gHeader->GetWeight());

      // fill muon b quark histos:
      if(mcdimuon->GetMCMuon1()->GetMuonBQuark()!= 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark()!= 0 ) {
 	if( (mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID()==9 || mcdimuon->GetMCMuon2()->GetMuonBQuark()->GetPartID()==10) &&
	   (mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID()==9 || mcdimuon->GetMCMuon1()->GetMuonBQuark()->GetPartID()==10) ) {
	  if( mcdimuon->GetMCMuon1()->GetMuon()->GetMatched() && mcdimuon->GetMCMuon2()->GetMuon()->GetMatched()  && 42 != 42 ){
	    fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->GetJetPt());
	    fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->GetJetPt());
	  }
	  else if(42 == 42){
	    //	  if(mcdimuon->GetDeltaR()> 2.2){
	    if(mcdimuon->GetInvMass() > 3.25){ // use this to look at events separated by mass
	      if(mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10() < 2. && mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10()< 2. && 42 != 42){
		// 	      fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+2*mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10());
		// 	      fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt()+2*mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10());
		fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10());
		fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt()+mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10());
	      }
	      else{
		// 	      fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+2*mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation05());
		// 	      fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt()+2*mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation05());
		if(mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10()>0.) fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10());
		else                                                       fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt());
		if(mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10()>0.) fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt()+mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10());
		else                                                       fGeneralMuQuarkPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt());
		
	      }
	    }
	    else{
	      //	    fGeneralMuQuarkPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+mcdimuon->GetMCMuon1()->GetMuon()->Pt()+1.5*mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10() );
	      //	      fGeneralMuQuarkPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+mcdimuon->GetMCMuon2()->GetMuon()->Pt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10() );
	      // use dimuon pT (vectorial pT):
	      if( mcdimuon->GetMCMuon1()->GetMuon()->Pt() >= mcdimuon->GetMCMuon2()->GetMuon()->Pt() ) fGeneralMuQuarkPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetdimuPt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10() );
	      else fGeneralMuQuarkPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),mcdimuon->GetdimuPt()+mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10() );
	    }
	  }
	}
      }
      // fill muon B Meson histos:
      if(mcdimuon->GetInvMass() > 3.25){ // use this to look at events separated by mass
	if(mcdimuon->GetMCMuon1()->GetMuonBMeson() !=0 && mcdimuon->GetMCMuon2()->GetMuonBMeson() != 0 ){
	  //		cout<<"Try to fill with these pointers: "<<mcdimuon->GetMCMuon1()->GetMuonBMeson()<<" and "<<mcdimuon->GetMCMuon2()->GetMuonBMeson()<<endl;
	  if(mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10()>0.) fGeneralMuBMesonPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10());
	  else                                                       fGeneralMuBMesonPtTrueNRec->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt());
	  if(mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10()>0.) fGeneralMuBMesonPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt()+mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10());
	  else                                                       fGeneralMuBMesonPtTrueNRec->Fill(mcdimuon->GetMCMuon2()->GetMuonBMeson()->Pt(),mcdimuon->GetMCMuon2()->GetMuon()->Pt());
	}
      }
      else{
	if(mcdimuon->GetMCMuon1()->GetMuonBMeson() !=0 ){
	      if( mcdimuon->GetMCMuon1()->GetMuon()->Pt() >= mcdimuon->GetMCMuon2()->GetMuon()->Pt() )   fGeneralMuBMesonPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt(),mcdimuon->GetdimuPt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10() );
	      else   fGeneralMuBMesonPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt(),mcdimuon->GetdimuPt()+mcdimuon->GetMCMuon2()->GetMuon()->GetIsolation10() );
	      //	  fGeneralMuBMesonPtTrueNRec_singlb->Fill(mcdimuon->GetMCMuon1()->GetMuonBMeson()->Pt(),mcdimuon->GetMCMuon1()->GetMuon()->Pt()+mcdimuon->GetMCMuon2()->GetMuon()->Pt()+mcdimuon->GetMCMuon1()->GetMuon()->GetIsolation10() );
	}	
      }

      fGeneralDimuMass1bin_truenrec_hflmu->Fill(invMass,gHeader->GetWeight());
//       fGeneralDimuMass1bin_truenrec_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
//       fGeneralDimuMass1bin_truenrec_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
      fGeneralDimuxsecPt_truenrec_hflmu->Fill(mcdimuon->GetMCMuon1()->Pt());
      fGeneralDimuxsecPt_truenrec_hflmu->Fill(mcdimuon->GetMCMuon2()->Pt());
      fGeneralDimuxsecEta_truenrec_hflmu->Fill(mcdimuon->GetMCMuon1()->Eta());
      fGeneralDimuxsecEta_truenrec_hflmu->Fill(mcdimuon->GetMCMuon2()->Eta());
      Double_t binx = 4.05;
      for(Int_t dd = 0; dd < 40 ; dd += 1){
	//	cout<<dd<<" is: "<<binx<<endl;
	if( binx < 7.0 ){
		fGeneralDimuxsecFinders_truenrec_hflmu->Fill(binx);
		//		fGeneralDimuxsecFinders_truenrec_hflmu->Fill(binx);
	      }
	else{
	  fGeneralDimuxsecFinders_truenrec_hflmu->Fill(binx);
	}
	binx += 0.1;
      }

      fGeneralDimuxsecDR_truenrec_hflmu->Fill(deltaR);
      fGeneralDimuxsecDphi_truenrec_hflmu->Fill(TMath::Abs(deltaPhi));

      if(mcdimuon->GetMCMuon1()->GetMuonBQuark()!= 0 && mcdimuon->GetMCMuon2()->GetMuonBQuark()!= 0){
	fGeneralDimu_b_pt_truenrec_hflmu->Fill(mcdimuon->GetMCMuon1()->GetMuonBQuark()->Pt(),gHeader->GetWeight());
	//	fGeneralDimu_b_pt_truenrec_hflmu->Fill(mcdimuon->GetMCMuon2()->GetMuonBQuark()->Pt(),gHeader->GetWeight());
      }


      fGeneralMCDeltaRTrueNRec->Fill(deltaR,gHeader->GetWeight());
      if ( invMass <= 4 &&  mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrueNRec_lu->Fill(deltaR,gHeader->GetWeight());
      if ( invMass <= 4 && !mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrueNRec_ll->Fill(deltaR,gHeader->GetWeight());
      if ( invMass > 4  &&  mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrueNRec_hu->Fill(deltaR,gHeader->GetWeight());
      if ( invMass > 4  && !mcdimuon->GetDifCharge() )      fGeneralMCDeltaRTrueNRec_hl->Fill(deltaR,gHeader->GetWeight());
      fGeneralMCDeltaPhiTrueNRec->Fill( TMath::Abs(deltaPhi) ,gHeader->GetWeight());
      if ( invMass <= 4 &&  mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrueNRec_lu->Fill( TMath::Abs(deltaPhi) ,gHeader->GetWeight());
      if ( invMass <= 4 && !mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrueNRec_ll->Fill( TMath::Abs(deltaPhi) ,gHeader->GetWeight());
      if ( invMass > 4  &&  mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrueNRec_hu->Fill( TMath::Abs(deltaPhi) ,gHeader->GetWeight());
      if ( invMass > 4  && !mcdimuon->GetDifCharge() )	fGeneralMCDeltaPhiTrueNRec_hl->Fill( TMath::Abs(deltaPhi) ,gHeader->GetWeight());
    }
  }
  return kTRUE;
}

//  //_____________________________________________________________

// Bool_t GMCs::ObjectsFillControlMCDIMuons(GDIMuon *mcdimuon) {
//   //
//   // fill control dimuon histograms with data by looping over internal array
//   if ( gDebug ) cout << endl << "GMCs::ObjectsFillControlMCDIMuons() called" << endl << endl;
  
//   if ( gCards->GetMcControl() ) {
    
//   }
//   return kTRUE;
// }

//_____________________________________________________________

Bool_t GMCs::AddMuonMCInfo(GMuon *muon, Int_t fmckinid, Int_t partid, 
		     Double_t px, Double_t py, Double_t pz, Double_t e, 
		     Int_t qpartid, 
		     Double_t qpx, Double_t qpy, Double_t qpz, Double_t qe, 
		     Int_t dirpartid, 
		     Double_t dirpx, Double_t dirpy, Double_t dirpz, Double_t dire) {
  //
  // fill mc info from gmuon block
  if ( gDebug ) cout << endl << "GMCs::AddMuonMCInfo called" << endl << endl;

  TClonesArray &mcs = *fMCs;

  GMC *mcmuon = 0;

  // add muon, only if fmckid != 0
  if ( fmckinid != 0 ) {
    // try if fmckin id exists
    GMC *existing = GetMC(fmckinid);
    if ( existing != 0 ) {
      muon->SetMC(existing);
      existing->SetMuon(muon);
      mcmuon = existing;
    } else {
      // try if negative fmckin id exists
      existing = GetMC(-fmckinid);
      if ( existing != 0 ) {
	muon->SetMC(existing);
	existing->SetMuon(muon);
	existing->AssociatedWithNegativeFMCKINID(kTRUE);
	mcmuon = existing;
      } else {
	GMC *addition = new(mcs[fNMCs++]) GMC(fmckinid,partid,px,py,pz,e);
	muon->SetMC(addition);
	addition->SetMuon(muon);
	mcmuon = addition;
      }
    }
  
    // add quark only if qpartid != 0 
    if ( qpartid != 0 ) {
      existing = GetMC(qpartid,qpx,qpy,qpz,qe);
      if ( existing != 0 ) {
	muon->SetMCQuark(existing);
	if ( mcmuon != 0 )
	  mcmuon->SetMuonBQuark(existing);
	existing->SetMCMuon(mcmuon);
      } else {
	GMC *addition = new(mcs[fNMCs++]) GMC(fOwnFMCKINID++,qpartid,qpx,qpy,qpz,qe);
	muon->SetMCQuark(addition);
	if ( mcmuon != 0 )
	  mcmuon->SetMuonBQuark(addition);
	addition->SetMCMuon(mcmuon);
      }
    }

    // add direct parent of dirpartid != 0
    if ( dirpartid != 0 ) {
      existing = GetMC(dirpartid,dirpx,dirpy,dirpz,dire);
      if ( existing != 0 ) {
	muon->SetMCDirectParent(existing);
	if ( mcmuon != 0 )
	  mcmuon->SetMuonDirectParent(existing);
	existing->SetMCMuon(mcmuon);
      } else {
	GMC *addition = new(mcs[fNMCs++]) GMC(fOwnFMCKINID++,dirpartid,dirpx,dirpy,dirpz,dire);
	muon->SetMCDirectParent(addition);
	if ( mcmuon != 0 )
	  mcmuon->SetMuonDirectParent(addition);
	addition->SetMCMuon(mcmuon);
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

GJet* GMCs::GetMCHJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetMCHJet called" << endl << endl;

  if ( (index < fNMCHJets) && (index >= 0) ) {
    return ((GJet*)(fMCHJets->At(index)));
  } else {
    TString msg = "GMCs::GetMCHJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNMCHJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GMCs::GetMCHJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GMCs::GetMCHJet called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNMCHJets; i++ ) {
    jet1 = ((GJet*)(fMCHJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GMCs::GetMCHJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

GJet* GMCs::GetMCHMJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetMCHMJet called" << endl << endl;

  if ( (index < fNMCHMJets) && (index >= 0) ) {
    return ((GJet*)(fMCHMJets->At(index)));
  } else {
    TString msg = "GMCs::GetMCHMJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNMCHMJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GMCs::GetMCHMJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GMCs::GetMCHMJet called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNMCHMJets; i++ ) {
    jet1 = ((GJet*)(fMCHMJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GMCs::GetMCHMJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

GJet* GMCs::GetMCHBJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetMCHBJet called" << endl << endl;

  if ( (index < fNMCHBJets) && (index >= 0) ) {
    return ((GJet*)(fMCHBJets->At(index)));
  } else {
    TString msg = "GMCs::GetMCHBJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNMCHBJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GMCs::GetMCHBJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GMCs::GetMCHBJet called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNMCHBJets; i++ ) {
    jet1 = ((GJet*)(fMCHBJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GMCs::GetMCHBJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

GJet* GMCs::GetMCHBMJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetMCHBMJet called" << endl << endl;

  if ( (index < fNMCHBMJets) && (index >= 0) ) {
    return ((GJet*)(fMCHBMJets->At(index)));
  } else {
    TString msg = "GMCs::GetMCHBMJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNMCHBMJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GMCs::GetMCHBMJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GMCs::GetMCHBMJet called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
    jet1 = ((GJet*)(fMCHBMJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GMCs::GetMCHBMJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

GJet* GMCs::GetMCPJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetMCPJet called" << endl << endl;

  if ( (index < fNMCPJets) && (index >= 0) ) {
    return ((GJet*)(fMCPJets->At(index)));
  } else {
    TString msg = "GMCs::GetMCPJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNMCPJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GMCs::GetMCPJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GMCs::GetMCPJet called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNMCPJets; i++ ) {
    jet1 = ((GJet*)(fMCPJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GMCs::GetMCPJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

GJet* GMCs::GetMCPMJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetMCPMJet called" << endl << endl;

  if ( (index < fNMCPMJets) && (index >= 0) ) {
    return ((GJet*)(fMCPMJets->At(index)));
  } else {
    TString msg = "GMCs::GetMCPMJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNMCPMJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GMCs::GetMCPMJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GMCs::GetMCPMJet called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNMCPMJets; i++ ) {
    jet1 = ((GJet*)(fMCPMJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GMCs::GetMCPMJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

Bool_t GMCs::CheckMCDIMuonHFL(GDIMuon *mcdimuon) {
  //
  // check if both muons in dimuon originate from hlf parent
  if ( gDebug ) cout << endl << "GMCs::CheckMCDIMuonHFL() called" << endl << endl;

  Bool_t mushaveparents = kFALSE;

  if ( mcdimuon != 0  ) {

    // check whether a parent Meson is there. 4 combinations, as GetMother works for muons from the FMCKIN block and GetMuonDirectParents for 
    // muons found in the GMUON MC block only (mainly muons below 1 GeV, as they are nor stored in the FMCKIN list).
    if( mcdimuon->GetMCMuon1()->GetMother() && mcdimuon->GetMCMuon2()->GetMother() ) { //&& 42 != 42 
      if ( ( CheckBParent( mcdimuon->GetMCMuon1()->GetMother()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon1()->GetMother()->GetPartID() ) ) &&
	   ( CheckBParent( mcdimuon->GetMCMuon2()->GetMother()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon2()->GetMother()->GetPartID() ) )     ) {
	mushaveparents = kTRUE;
	  }
    }
    else if(mcdimuon->GetMCMuon1()->GetMuonDirectParent() && mcdimuon->GetMCMuon2()->GetMuonDirectParent()){
      if ( ( CheckBParent( mcdimuon->GetMCMuon1()->GetMuonDirectParent()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon1()->GetMuonDirectParent()->GetPartID() ) ) &&
	   ( CheckBParent( mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID() ) )     ) {
	mushaveparents = kTRUE;
	  }
    }
    else if(mcdimuon->GetMCMuon1()->GetMother() && mcdimuon->GetMCMuon2()->GetMuonDirectParent()){
      if ( ( CheckBParent( mcdimuon->GetMCMuon1()->GetMother()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon1()->GetMother()->GetPartID() ) ) &&
	   ( CheckBParent( mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID() ) )     ) {
	mushaveparents = kTRUE;
	  }
    }
    else if(mcdimuon->GetMCMuon1()->GetMuonDirectParent() && mcdimuon->GetMCMuon2()->GetMother()){
      if ( ( CheckBParent( mcdimuon->GetMCMuon1()->GetMuonDirectParent()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon1()->GetMuonDirectParent()->GetPartID() ) ) &&
	   ( CheckBParent( mcdimuon->GetMCMuon2()->GetMother()->GetPartID() ) || CheckCParent( mcdimuon->GetMCMuon2()->GetMother()->GetPartID() ) )     ) {
	mushaveparents = kTRUE;
	  }
    }
    if(42 != 42 && mushaveparents ) {
      // This is the true definition used for total and ptb cross sections!
      // mcdimuon->GetInvMass() >= gCards->GetDIMUONInvMassLowCut() &&
      //	if(  mcdimuon->GetMCMuon1()->Pt() >= gCards->GetBMUONPTCut1() && mcdimuon->GetMCMuon2()->Pt()>= gCards->GetBMUONPTCut1() ) {
      // 	if(  mcdimuon->GetMCMuon1()->Pt() >= gCards->GetBMUONPTCut2() && mcdimuon->GetMCMuon2()->Pt()>= gCards->GetBMUONPTCut2() ) { // use for both mu>1.5
      // first common true vsisble definition version, by A. Geiser:
      // 	if(  mcdimuon->GetMCMuon1()->Pt() >= 1.5
      // 	     && 
      // 	     (
      // 	      ( mcdimuon->GetMCMuon2()->P()>= 1.5 && mcdimuon->GetMCMuon2()->Eta()<=1.)
      // 	      || 
      // 	      ( mcdimuon->GetMCMuon2()->P()>= 2.5 && mcdimuon->GetMCMuon2()->Eta()>1. )
      // 	      )
      // 	     &&
      // 	     (mcdimuon->GetMCMuon1()->Eta()>-2. && mcdimuon->GetMCMuon1()->Eta()<2.5 && mcdimuon->GetMCMuon2()->Eta()>-2. && mcdimuon->GetMCMuon2()->Eta()<2.5 )
      // 	     &&
      // 	     (mcdimuon->GetMCMuon1()->Pt()>0.75 && mcdimuon->GetMCMuon2()->Pt()>0.75 )
      // 	     ) {
      // second common true visible definition, by A. Geiser
      if(
	 (    
	  (
	   mcdimuon->GetMCMuon1()->Pt() > 1.5 && mcdimuon->GetMCMuon2()->Pt() > 0.75  && ( ((mcdimuon->GetMCMuon2()->P() > 2.5 || mcdimuon->GetMCMuon2()->Pt() > 1.5) && mcdimuon->GetMCMuon2()->Eta() > 0.6 ) || (mcdimuon->GetMCMuon2()->P() > 1.8 && mcdimuon->GetMCMuon2()->Eta() < 0.6) ) 
	   )
	  ||   
	  (
	   mcdimuon->GetMCMuon2()->Pt() > 1.5 && mcdimuon->GetMCMuon1()->Pt() > 0.75  && ( ((mcdimuon->GetMCMuon1()->P() > 2.5 || mcdimuon->GetMCMuon1()->Pt() > 1.5) && mcdimuon->GetMCMuon1()->Eta() > 0.6 ) || (mcdimuon->GetMCMuon1()->P() > 1.8 && mcdimuon->GetMCMuon1()->Eta() < 0.6) )  
	   )
	  )   &&   mcdimuon->GetMCMuon1()->Eta() > -2.2 && mcdimuon->GetMCMuon1()->Eta() < 2.5   &&   mcdimuon->GetMCMuon2()->Eta() > -2.2 && mcdimuon->GetMCMuon2()->Eta() < 2.5
	 ) {
	mcdimuon->SetMCDIMuonHFLCut(kTRUE);
	fMCDIMuonCuts = kTRUE;
	// 	cout<<"Selecting dimuon: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with p, pTs, eta:"<<endl;
	// 	if(mcdimuon->GetMCMuon1()->GetMother()) cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon1()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" parent id "<< mcdimuon->GetMCMuon1()->GetMother()->GetPartID()<<endl;
	// 	else  cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon1()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" parent id "<< mcdimuon->GetMCMuon1()->GetMuonDirectParent()->GetPartID()<<endl;
	// 	if(mcdimuon->GetMCMuon2()->GetMother() ) cout<<"dimuon: 2 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" parent id "<< mcdimuon->GetMCMuon2()->GetMother()->GetPartID()<<endl;
	// 	else cout<<"dimuon: 2 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" parent id "<< mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID()<<endl;
	// 	  getchar();
      }
      // If this below is used, we select less events. But why? What is correct? - was BUG in mcdimuon contructor - flag was not initialised!! found 050530
      //  	  else{
      //  	    mcdimuon->SetMCDIMuonHFLCut(kFALSE);
      //  	  }
    }
    if(42 == 42 && mushaveparents ) {
      // This is the true definition used for muon differential cross sections

//       GMC* mc_iterator = 0;
//       cout<<"DIMuon with parents: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" FMCKIN id: "<<mcdimuon->GetMCMuon2()->GetFMCKINID()<<endl;
//       if(mcdimuon->GetMCMuon2()->GetMother()) cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" mother id "<< mcdimuon->GetMCMuon2()->GetMother()->GetPartID()<<" BParen? "<<1*CheckBParent( mcdimuon->GetMCMuon2()->GetMother()->GetPartID() )<<endl;
//       else  cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" mudirparent id "<< mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID()<<" BParen? "<<1*CheckBParent( mcdimuon->GetMCMuon2()->GetMuonDirectParent()->GetPartID() )<<endl;
//       //      if(gData->Geteventnr() == 156)	getchar();
//       if(mcdimuon->GetMCMuon2()->GetMother())                mc_iterator = mcdimuon->GetMCMuon2()->GetMother();
//       else if(mcdimuon->GetMCMuon2()->GetMuonDirectParent()) mc_iterator = mcdimuon->GetMCMuon2()->GetMuonDirectParent();
//       if(mc_iterator != 0 ){
// 	if( !( CheckBParent( mc_iterator->GetPartID() ) )){
// 	  while (  mc_iterator->GetMother()  ) {
// 	    if( CheckBParent( mc_iterator->GetMother()->GetPartID() ) && mc_iterator->GetMother()->GetPartID()!= 27 && mc_iterator->GetMother()->GetPartID() != 28 ) {
// 	      // have found one B meson - stop the while loop and set the B meson.
// 	      mc_iterator = mc_iterator->GetMother();
// 	      //	      mcdimuon->GetMCMuon2()->SetMuonBMeson(mc_iterator);
// 	      cout<<"DI Part ID: "<<mc_iterator->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator->GetPartID() )<<" Pt: "<<mc_iterator->Pt()<<endl;
// 	      //		getchar();
// 	      //	      mc_iterator = 0;
// 	      break;
// 	    }
// 	    else mc_iterator = mc_iterator->GetMother();
// 	    cout<<"DI Part ID: "<<mc_iterator->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator->GetPartID() )<<endl;
// 	  }
// 	  if( !CheckBParent( mc_iterator->GetPartID() ) ){
// 	    cout<<"DI Part ID: "<<mc_iterator->GetPartID()<<" BParen? "<<1*CheckBParent( mc_iterator->GetPartID() )<<endl;
// 	    cout<<"DI No B meson found, but no mothers any more!! Bad? - likely muon from Geant"<<endl;
// 	    getchar();
// 	  }
// 	}
//       }

      // true definition for pt, eta, DR and Dphi dimuon xsecs:
      if( mcdimuon->GetMCMuon1()->Pt() > 1.5 && mcdimuon->GetMCMuon2()->Pt() > 1.5 
	  && 
	  mcdimuon->GetMCMuon1()->Eta() > -2.2 && mcdimuon->GetMCMuon2()->Eta() > -2.2 
	  &&
	  mcdimuon->GetMCMuon1()->Eta() < 2.5 && mcdimuon->GetMCMuon2()->Eta() < 2.5 
	  ) {
	mcdimuon->SetMCDIMuonHFLCut(kTRUE);
	fMCDIMuonCuts = kTRUE;
	//  	    if(gData->Geteventnr()==9297) {
	// 	      cout<<"DOOO turee Selecting dimuon: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with p, pTs, eta: : hflcut: "<<1*mcdimuon->GetMCDIMuonHFLCut()<<" eventhflcut: "<<1*fMCDIMuonCuts<<endl;
	//        	      cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon1()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" parent id "<< mcdimuon->GetMCMuon1()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon1()->GetPartID()<<endl;
	//  	      cout<<"dimuon: 2 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" parent id "<< mcdimuon->GetMCMuon2()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon2()->GetPartID()<<endl;
	//  	      //  	    mcdimuon->SetMCDIMuonHFLCut(kFALSE);
	//  	    }
	// 	    cout<<"Selecting dimuon: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with p, pTs, eta:"<<endl;
	// 	    cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon1()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" parent id "<< mcdimuon->GetMCMuon1()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon1()->GetPartID()<<endl;
	// 	    cout<<"dimuon: 2 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" parent id "<< mcdimuon->GetMCMuon2()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon2()->GetPartID()<<endl;
	//	    getchar();
      }
      //    	  else if(gData->Geteventnr()==9297) {
      //   	    cout<<"NOT Selecting dimuon: r "<<gData->Getrunnr()<<" e "<<gData->Geteventnr()<<" with p, pTs, eta:"<<endl;
      //   	    cout<<"dimuon: 1 P "<<mcdimuon->GetMCMuon1()->P()<<" Pt "<<mcdimuon->GetMCMuon1()->Pt()<<" Eta "<<mcdimuon->GetMCMuon1()->Eta()<<" parent id "<< mcdimuon->GetMCMuon1()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon1()->GetPartID()<<endl;
      //  	    cout<<"dimuon: 2 P "<<mcdimuon->GetMCMuon2()->P()<<" Pt "<<mcdimuon->GetMCMuon2()->Pt()<<" Eta "<<mcdimuon->GetMCMuon2()->Eta()<<" parent id "<< mcdimuon->GetMCMuon2()->GetMother()->GetPartID()<<" "<<mcdimuon->GetMCMuon2()->GetPartID()<<endl;
      //  //  	    mcdimuon->SetMCDIMuonHFLCut(kFALSE);
      //    	  }
    }
    if( mcdimuon->GetMCMuon1()->Pt() > 0.75 && mcdimuon->GetMCMuon2()->Pt() > 0.75 && 42 != 42 ) {
      // This is a true definition for test purposes
      mcdimuon->SetMCDIMuonHFLCut(kTRUE);
      fMCDIMuonCuts = kTRUE;
    }
    //     else mcdimuon->SetMCDIMuonHFLCut(kFALSE);
  }
  else cout<<endl<<"ERROR!! in GMCs::CheckMCDIMuonHFL(): called with mcdimuon pointer = 0"<<endl;
  
  return kTRUE;
}



//_____________________________________________________________

Bool_t GMCs::CheckMuonCutsStage1(GMC *mc) {
  //
  // check mc true muon cuts
  if ( gDebug ) cout << endl << "GMCs::CheckMuonCutsStage1() called" << endl << endl;

  if ( mc->GetType() == kMuon ) {
    // identify muon
    mc->SetMCMuonType(kMCMuon);
    Double_t eta = mc->Eta();
    // check for muon regions
    if ( ( eta >= gCards->GetFMUONEtaLow() ) && ( eta <= gCards->GetFMUONEtaUp() ) ) {
      mc->SetMCMuonType(kMCForwardMuon);
      // check muon cuts
      CheckMuonCutsStage2(mc);
    } else if ( ( eta >= gCards->GetBMUONEtaLow() ) && ( eta <= gCards->GetBMUONEtaUp() ) ) {
      mc->SetMCMuonType(kMCBarrelMuon);
      // check muon cuts
      CheckMuonCutsStage2(mc);
    } else if ( ( eta >= gCards->GetRMUONEtaLow() ) && ( eta <= gCards->GetRMUONEtaUp() ) ) {
      mc->SetMCMuonType(kMCRearMuon);
      // check muon cuts
      CheckMuonCutsStage2(mc);
    }
  } else{
    mc->SetMCMuonType(kUnidentifiedMCMuon);
  }
 
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::CheckMuonCutsStage2(GMC *mc) {
  //
  // check mc true muon p and pt cuts and for cut on muon coming from b quark
  if ( gDebug ) cout << endl << "GMCs::CheckMuonCutsStage2() called" << endl << endl;

  Double_t ptcut = 9999.99;
  Double_t pcut  = 9999.99;

  if ( mc->GetMCMuonType() == kMCForwardMuon ) {
    ptcut = gCards->GetFMUONPt();
    if ( ptcut < gCards->GetFMUONPTCut1() )
      ptcut = gCards->GetFMUONPTCut1();
    if ( ptcut < gCards->GetFMUONPTCut2() )
      ptcut = gCards->GetFMUONPTCut2();
    pcut = gCards->GetFMUONP();
  } else if ( mc->GetMCMuonType() == kMCBarrelMuon ) {
    ptcut = gCards->GetBMUONPt();
    if ( ptcut < gCards->GetBMUONPTCut1() )
      ptcut = gCards->GetBMUONPTCut1();
    if ( ptcut < gCards->GetBMUONPTCut2() )
      ptcut = gCards->GetBMUONPTCut2();
    pcut = gCards->GetBMUONP();
  } else if (  mc->GetMCMuonType() == kMCRearMuon ) {
    ptcut = gCards->GetRMUONPt();
    if ( ptcut < gCards->GetRMUONPTCut1() )
      ptcut = gCards->GetRMUONPTCut1();
    if ( ptcut < gCards->GetRMUONPTCut2() )
      ptcut = gCards->GetRMUONPTCut2();
    pcut = gCards->GetRMUONP();
  }


  // check p and pt cut, flag only first muon if getallgood card not set
  if ( gCards->GetMJMATCHTakeAllGood() ) {
    if ( (mc->P() >= pcut) && (mc->Pt() >= ptcut) ) {
      // check for b or c parent
      // if mc has a mother
      if ( mc->GetMother() != 0 ) {
	if ( CheckBParent(mc->GetMother()->GetPartID()) || CheckCParent(mc->GetMother()->GetPartID()) ) {
	  mc->SetChosenMCMuon();
	  fMuonCuts = kTRUE;
	}
      } else {
	// check for pointer from gmuon
	if ( mc->GetMuonDirectParent() != 0 ) {
	  if ( CheckBParent(mc->GetMuonDirectParent()->GetPartID()) || CheckCParent(mc->GetMuonDirectParent()->GetPartID()) ) {
	    mc->SetChosenMCMuon();
	    fMuonCuts = kTRUE;
	  }
	}
      } 
    }
  } else {
    if ( (mc->P() >= pcut) && (mc->Pt() >= ptcut) && ! fMuonCuts ) {
      // check for b or c parent
      // if mc has a mother
      if ( mc->GetMother() != 0 ) {
	if ( CheckBParent(mc->GetMother()->GetPartID()) || CheckCParent(mc->GetMother()->GetPartID()) ) {
	  mc->SetChosenMCMuon();
	  fMuonCuts = kTRUE;
	}
      } else {
	// check for pointer from gmuon
	if ( mc->GetMuonDirectParent() != 0 ) {
	  if ( CheckBParent(mc->GetMuonDirectParent()->GetPartID()) || CheckCParent(mc->GetMuonDirectParent()->GetPartID()) ) {
	    mc->SetChosenMCMuon();
	    fMuonCuts = kTRUE;
	  }
	}
      }
    }
  }
  if(fMuonCuts){
    AssociateMCJetToMCMuon(mc);
    AssociateMCPMJetToMCMuon(mc);
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::Finalize() {
  //
  // finalize operations of physics object, mainly for histograms
  if (gDebug) cout << endl << "GMCs::Finalize() called" << endl << endl;

    if ( gCards->GetFMCK() ) {

    double scaleAllPt = 1./fFakeHadronPionPt->GetEntries();
    double scaleAllEta_lowPt = 1./fFakeHadronAllEta_lowPt->GetEntries();
    double scaleAllPhi_lowPt = 1./fFakeHadronAllPhi_lowPt->GetEntries();
    double scaleAllEta_highPt = 1./fFakeHadronAllEta_highPt->GetEntries();
    double scaleAllPhi_highPt = 1./fFakeHadronAllPhi_highPt->GetEntries();

    double scalePionPt = 1./fFakeHadronPionPt->GetEntries();
    double scalePionEta_lowPt = 1./fFakeHadronPionEta_lowPt->GetEntries();
    double scalePionPhi_lowPt = 1./fFakeHadronPionPhi_lowPt->GetEntries();
    double scalePionEta_highPt = 1./fFakeHadronPionEta_highPt->GetEntries();
    double scalePionPhi_highPt = 1./fFakeHadronPionPhi_highPt->GetEntries();
    double scaleKaonPt = 1./fFakeHadronKaonPt->GetEntries();
    double scaleKaonEta_lowPt = 1./fFakeHadronKaonEta_lowPt->GetEntries();
    double scaleKaonPhi_lowPt = 1./fFakeHadronKaonPhi_lowPt->GetEntries();
    double scaleKaonEta_highPt = 1./fFakeHadronKaonEta_highPt->GetEntries();
    double scaleKaonPhi_highPt = 1./fFakeHadronKaonPhi_highPt->GetEntries();
    fFakeProbabilityPionEta_lowPt->Divide(gMuons->GetFakeMuonPionEta_lowPt(),fFakeHadronPionEta_lowPt,scalePionEta_lowPt,scalePionEta_lowPt);
    fFakeProbabilityPionPhi_lowPt->Divide(gMuons->GetFakeMuonPionPhi_lowPt(),fFakeHadronPionPhi_lowPt,scalePionPhi_lowPt,scalePionPhi_lowPt);
    fFakeProbabilityPionEta_highPt->Divide(gMuons->GetFakeMuonPionEta_highPt(),fFakeHadronPionEta_highPt,scalePionEta_highPt,scalePionEta_highPt);
    fFakeProbabilityPionPhi_highPt->Divide(gMuons->GetFakeMuonPionPhi_highPt(),fFakeHadronPionPhi_highPt,scalePionPhi_highPt,scalePionPhi_highPt);
    fFakeProbabilityPionPt->Divide(gMuons->GetFakeMuonPionPt(),fFakeHadronPionPt,scalePionPt,scalePionPt);
    fFakeProbabilityKaonPt->Divide(gMuons->GetFakeMuonKaonPt(),fFakeHadronKaonPt,scaleKaonPt,scaleKaonPt);
    fFakeProbabilityKaonEta_lowPt->Divide(gMuons->GetFakeMuonKaonEta_lowPt(),fFakeHadronKaonEta_lowPt,scaleKaonEta_lowPt,scaleKaonEta_lowPt);
    fFakeProbabilityKaonPhi_lowPt->Divide(gMuons->GetFakeMuonKaonPhi_lowPt(),fFakeHadronKaonPhi_lowPt,scaleKaonPhi_lowPt,scaleKaonPhi_lowPt);
    fFakeProbabilityKaonEta_highPt->Divide(gMuons->GetFakeMuonKaonEta_highPt(),fFakeHadronKaonEta_highPt,scaleKaonEta_highPt,scaleKaonEta_highPt);
    fFakeProbabilityKaonPhi_highPt->Divide(gMuons->GetFakeMuonKaonPhi_highPt(),fFakeHadronKaonPhi_highPt,scaleKaonPhi_highPt,scaleKaonPhi_highPt);
        //---------------------------------------------------------------------------------------
    fFakeDecayProbabilityPionPhi_lowPt->Divide(gMuons->GetFakeDecayMuonPionPhi_lowPt(),fFakeHadronPionPhi_lowPt,scalePionPhi_lowPt,scalePionPhi_lowPt);
    fFakeDecayProbabilityPionEta_highPt->Divide(gMuons->GetFakeDecayMuonPionEta_highPt(),fFakeHadronPionEta_highPt,scalePionEta_highPt,scalePionEta_highPt);
    fFakeDecayProbabilityPionPhi_highPt->Divide(gMuons->GetFakeDecayMuonPionPhi_highPt(),fFakeHadronPionPhi_highPt,scalePionPhi_highPt,scalePionPhi_highPt);
    fFakeDecayProbabilityPionPt->Divide(gMuons->GetFakeDecayMuonPionPt(),fFakeHadronPionPt,scalePionPt,scalePionPt);
    fFakeDecayProbabilityKaonPt->Divide(gMuons->GetFakeDecayMuonKaonPt(),fFakeHadronKaonPt,scaleKaonPt,scaleKaonPt);
    fFakeDecayProbabilityKaonEta_lowPt->Divide(gMuons->GetFakeDecayMuonKaonEta_lowPt(),fFakeHadronKaonEta_lowPt,scaleKaonEta_lowPt,scaleKaonEta_lowPt);
    fFakeDecayProbabilityKaonPhi_lowPt->Divide(gMuons->GetFakeDecayMuonKaonPhi_lowPt(),fFakeHadronKaonPhi_lowPt,scaleKaonPhi_lowPt,scaleKaonPhi_lowPt);
    fFakeDecayProbabilityKaonEta_highPt->Divide(gMuons->GetFakeDecayMuonKaonEta_highPt(),fFakeHadronKaonEta_highPt,scaleKaonEta_highPt,scaleKaonEta_highPt);
    fFakeDecayProbabilityKaonPhi_highPt->Divide(gMuons->GetFakeDecayMuonKaonPhi_highPt(),fFakeHadronKaonPhi_highPt,scaleKaonPhi_highPt,scaleKaonPhi_highPt);
    //---------------------------------------------------------------------------------------------------------------------------------
    fFakePunchProbabilityPionEta_lowPt->Divide(gMuons->GetFakePunchMuonPionEta_lowPt(),fFakeHadronPionEta_lowPt,scalePionEta_lowPt,scalePionEta_lowPt);
    fFakePunchProbabilityPionPhi_lowPt->Divide(gMuons->GetFakePunchMuonPionPhi_lowPt(),fFakeHadronPionPhi_lowPt,scalePionPhi_lowPt,scalePionPhi_lowPt);
    fFakePunchProbabilityPionEta_highPt->Divide(gMuons->GetFakePunchMuonPionEta_highPt(),fFakeHadronPionEta_highPt,scalePionEta_highPt,scalePionEta_highPt);
    fFakePunchProbabilityPionPhi_highPt->Divide(gMuons->GetFakePunchMuonPionPhi_highPt(),fFakeHadronPionPhi_highPt,scalePionPhi_highPt,scalePionPhi_highPt);
    fFakePunchProbabilityPionPt->Divide(gMuons->GetFakePunchMuonPionPt(),fFakeHadronPionPt,scalePionPt,scalePionPt);
    fFakePunchProbabilityKaonPt->Divide(gMuons->GetFakePunchMuonKaonPt(),fFakeHadronKaonPt,scaleKaonPt,scaleKaonPt);
    fFakePunchProbabilityKaonEta_lowPt->Divide(gMuons->GetFakePunchMuonKaonEta_lowPt(),fFakeHadronKaonEta_lowPt,scaleKaonEta_lowPt,scaleKaonEta_lowPt);
    fFakePunchProbabilityKaonPhi_lowPt->Divide(gMuons->GetFakePunchMuonKaonPhi_lowPt(),fFakeHadronKaonPhi_lowPt,scaleKaonPhi_lowPt,scaleKaonPhi_lowPt);
    fFakePunchProbabilityKaonEta_highPt->Divide(gMuons->GetFakePunchMuonKaonEta_highPt(),fFakeHadronKaonEta_highPt,scaleKaonEta_highPt,scaleKaonEta_highPt);
    fFakePunchProbabilityKaonPhi_highPt->Divide(gMuons->GetFakePunchMuonKaonPhi_highPt(),fFakeHadronKaonPhi_highPt,scaleKaonPhi_highPt,scaleKaonPhi_highPt);
    //---------------------------------------------------------------------------------------------------------------------------------
    fFakeProbabilityPionEta_lowPt->Divide(gMuons->GetFakeMuonAllEta_lowPt(),fFakeHadronAllEta_lowPt,scaleAllEta_lowPt,scaleAllEta_lowPt);
    fFakeProbabilityPionPhi_lowPt->Divide(gMuons->GetFakeMuonAllPhi_lowPt(),fFakeHadronAllPhi_lowPt,scaleAllPhi_lowPt,scaleAllPhi_lowPt);
    fFakeProbabilityPionEta_highPt->Divide(gMuons->GetFakeMuonAllEta_highPt(),fFakeHadronAllEta_highPt,scaleAllEta_highPt,scaleAllEta_highPt);
    fFakeProbabilityPionPhi_highPt->Divide(gMuons->GetFakeMuonAllPhi_highPt(),fFakeHadronAllPhi_highPt,scaleAllPhi_highPt,scaleAllPhi_highPt);
    fFakeProbabilityPionPt->Divide(gMuons->GetFakeMuonAllPt(),fFakeHadronAllPt,scaleAllPt,scaleAllPt);

  }
  
  return kTRUE;
}

//_____________________________________________________________

Double_t GMCs::GetWeight() {
  
  if ( gDebug ) cout << endl << "GMCs::GetWeight() called" << endl << endl;
  
  //dummy
  return 1.;
}

//_____________________________________________________________

Bool_t GMCs::CheckBParent(Int_t id) {
  //
  // check if id comes from b parent;
  // id's 72-75,214-215,468-529,2085

  // tau
  if ( (id>=27)&&(id<=28) )
    return kTRUE;

  if ( (id>=72)&&(id<=75) )
    return kTRUE;

  if ( (id>=214)&&(id<=215) )
    return kTRUE;

  if ( (id>=468)&&(id<=529) )
    return kTRUE;

  // bottonium
  if ( id==455 )
    return kTRUE;

  if ( id==2085 )
    return kTRUE;

  return kFALSE;
}

//_____________________________________________________________

Bool_t GMCs::CheckCParent(Int_t id) {
  //
  // check if id comes from c parent (from a b);
  // standard c hadrons (id's 64-71,186-189,208-213,417-454,466-467)
  // excited c hadrons (id's 535-546, 2339-2348) 

  if ( (id>=64)&&(id<=71) )
    return kTRUE;

  // charmonium
  if ( (id>=124)&&(id<=145) )
    return kTRUE;

  if ( (id>=186)&&(id<=189) )
    return kTRUE;

  if ( (id>=208)&&(id<=213) )
    return kTRUE;

  if ( (id>=417)&&(id<=454) )
    return kTRUE;

  if ( (id>=466)&&(id<=467) )
    return kTRUE;

  if ( (id>=535)&&(id<=546) )
    return kTRUE;

  if ( (id>=2339)&&(id<=2348) )
    return kTRUE;

  return kFALSE;
}

//_____________________________________________________________

Bool_t GMCs::AssociateMCJet(GJet *jet) {
  //
  // associate rec jet to mc jet, take deltaR cone of 0.7

  GJet *mc_jet = 0;
  Double_t cut = 0.7;

  for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
    mc_jet = ((GJet*)(fMCHBMJets->At(i)));
    if ( mc_jet->DeltaR(*jet) <= cut ) {
      jet->SetAssociatedMCJet(mc_jet);
      cut = mc_jet->DeltaR(*jet);
    }
  }
  if(jet->GetAssociatedMCJet()){
    mc_jet =  jet->GetAssociatedMCJet();
    mc_jet->SetAssociatedMCJet(jet);
  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GMCs::AssociateMCJet(GMC *particle) {
  //  cout <<"associate mc particle to mc jet, take deltaR cone of 1.0"<< endl;
 
  GJet *mc_jet = 0;
  Double_t cut = 1.0;
  particle->SetAssociatedMCJet(0);
  
  for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
    mc_jet = ((GJet*)(fMCHBMJets->At(i)));
    if ( mc_jet->DeltaR(*particle) <= cut ) {
      particle->SetAssociatedMCJet(mc_jet);
      cut = mc_jet->DeltaR(*particle);
    }  
  }
  
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMCs::AssociateMCJetToMCMuon(GMC *mc_muon) {
  //cout <<"associate mc particle to mc jet, take deltaR cone of 1.0"<< endl;
  GJet *mc_jet = 0;
  GJet *mc_jet2 = 0;
  Double_t cut = 1.0;
  mc_muon->SetAssociatedMCJetToMCMuon(0);
  mc_muon->SetSecondAssociatedMCJetToMCMuon(0);
  for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
    mc_jet = ((GJet*)(fMCHBMJets->At(i)));
    if(mc_jet->Pt() >=  gCards->GetJETPtBCut() && mc_jet->GetEtaCut()){
      if ( mc_jet->DeltaR(*mc_muon) <= cut ) {
	mc_jet2 = mc_muon->GetAssociatedMCJetToMCMuon();
	mc_muon->SetAssociatedMCJetToMCMuon(mc_jet);
	if(mc_jet2) mc_muon->SetSecondAssociatedMCJetToMCMuon(mc_jet2);
	cut = mc_jet->DeltaR(*mc_muon);
      }
    }  
  }
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMCs::AssociateMCPMJetToMCMuon(GMC *mc_muon) {
  //  cout <<"associate mc particle to mc jet, take deltaR cone of 1.0"<< endl;
  GJet *mc_jet = 0;
  Double_t cut = 1.0;
  mc_muon->SetAssociatedMCPMJetToMCMuon(0);
  for ( Int_t i = 0; i < fNMCPMJets; i++ ) {
    mc_jet = ((GJet*)(fMCPMJets->At(i)));
    if(mc_jet->Pt() >=  gCards->GetJETPtBCut() && mc_jet->GetEtaCut()){
      if ( mc_jet->DeltaR(*mc_muon) <= cut ) {
	mc_muon->SetAssociatedMCPMJetToMCMuon(mc_jet);
	cut = mc_jet->DeltaR(*mc_muon);
      }
    }  
  }
  
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMCs::AssociateMCPMJet(GMC *particle) {
  //  cout <<"associate mc particle to mc jet, take deltaR cone of 1.0"<< endl;

  GJet *mc_jet = 0;
  Double_t cut = 1.0;

  particle->SetAssociatedMCPMJet(0);

  for ( Int_t i = 0; i < fNMCPMJets; i++ ) {
    mc_jet = ((GJet*)(fMCPMJets->At(i)));
    if ( mc_jet->DeltaR(*particle) <= cut ) {
      particle->SetAssociatedMCPMJet(mc_jet);
      cut = mc_jet->DeltaR(*particle);
    }  
  }
  
  return kTRUE;
}


//_____________________________________________________________

Int_t GMCs::IsMuonAssociatedToMCJet(GJet *mc_jet) {
  // cout << "IsMuonAssociatedToMCJet(GJet *mc_jet) {" << endl;
  // return if muon is associated to jet and coming from b

  GMC *mc = 0;
  
  Int_t counter = 0;

  for ( Int_t i = 0; i < fNMCs; i++ ) {
    mc = ((GMC*)(fMCs->At(i)));
    if ( mc->GetChosenMCMuon() ) {
      if ( mc->GetAssociatedMCJetToMCMuon() != 0 ) {
	if ( mc->GetAssociatedMCJetToMCMuon()->GetID() == mc_jet->GetID() ) {
	  if((mc_jet->Pt() >=  gCards->GetJETPtBCut())&& (mc_jet->DeltaR(*mc)<=1.0)){
	    ++counter;
 
	  }
	}
      }
    }
  }
  return counter;
}
//_____________________________________________________________

Int_t GMCs::IsMuonAssociatedToMCPMJet(GJet *mc_jet) {
  //
  // return if muon is associated to partonlevel massive jet and coming from b

  GMC *mc = 0;
  
  Int_t counter = 0;
  
  for ( Int_t i = 0; i < fNMCs; i++ ) {
    mc = ((GMC*)(fMCs->At(i)));
    if ( mc->GetChosenMCMuon() ) {
      if ( mc->GetAssociatedMCPMJetToMCMuon() != 0 ) {
	if ( mc->GetAssociatedMCPMJetToMCMuon()->GetID() == mc_jet->GetID() ) {
	  if((mc_jet->Pt() >=  gCards->GetJETPtBCut())&& (mc_jet->DeltaR(*mc)<=1.0)){
	    ++counter;
	  }
	}
      }
    }
  }
  return counter;
}
//_____________________________________________________________

Int_t GMCs::IsJetAssociatedToMCMuon(GMC *mcmuon) {
  // cout << " IsJetAssociatedToMCMuon(GMC *mcmuon) {" << endl;
  // return if muon is associated to jet and coming from b
  GJet *mc_jet = 0;
  Int_t counter = 0;
  if ( mcmuon->GetChosenMCMuon() ) {
    if ( mcmuon->GetAssociatedMCJetToMCMuon()!= 0 ) {
      if(( mcmuon->GetAssociatedMCJetToMCMuon()->Pt() >= gCards->GetJETPtBCut())&& (mcmuon->GetAssociatedMCJetToMCMuon()->DeltaR(*mcmuon)<=1.0)){
	mc_jet = mcmuon->GetAssociatedMCJet();
	++counter;
      } 
    }
  }
  
  return counter;
}
//_____________________________________________________________

Int_t GMCs::IsPMJetAssociatedToMCMuon(GMC *mcmuon) {
  //
  // return if muon is associated to jet and coming from b

  Int_t counter = 0;
  if ( mcmuon->GetChosenMCMuon() ) {
    if ( mcmuon->GetAssociatedMCPMJetToMCMuon() != 0 ) {
      if(( mcmuon->GetAssociatedMCPMJetToMCMuon()->Pt() >= gCards->GetJETPtBCut())&& (mcmuon->GetAssociatedMCPMJetToMCMuon()->DeltaR(*mcmuon)<=1.0)){
	++counter;
      }
    }
  }
  return counter;
}

//_____________________________________________________________

Bool_t GMCs::Calc(Int_t index1, Int_t index2) {
  //
  // calculate variables
  if ( gDebug ) cout << endl << "GMCs::Calc called" << endl << endl;
  
  GJet *jet1 = 0;
  GJet *jet2 = 0;

  if ( fMCHBMJetPtACut ) {
    jet1 = GetMCHBMJetWithID(index1);
    fXGammaJets = jet1->E()-jet1->Pz();
    fXGammaJets_zufo = jet1->E()-jet1->Pz();
  }
  if ( fMCHBMJetPtBCut ) {
    jet2 = GetMCHBMJetWithID(index2);
    if ( fXGammaJets == -9999.99 )
      fXGammaJets = jet2->E()-jet2->Pz();
    else
      fXGammaJets += jet2->E()-jet2->Pz();
    if ( fXGammaJets_zufo == -9999.99 )
      fXGammaJets_zufo = jet2->E()-jet2->Pz();
    else
      fXGammaJets_zufo += jet2->E()-jet2->Pz();
  }
  
  fXGammaJets /= (gData->Getmc_esum()-gData->Getmc_ez());
  fXGammaJets_zufo /= (gData->Getmc_esum()-gData->Getmc_ez());
  if(jet1 && jet2) fEtaJets = TMath::Abs((jet1->Eta()+jet2->Eta())/2);
  if(fXGammaJets>=1) fXGammaJets=0.99999;
  if(fXGammaJets_zufo>=1) fXGammaJets_zufo=0.99999;

  if ( (jet1!=0)&&(jet2!=0) ) {
    fXGamma = ((jet1->Et()*TMath::Exp(-jet1->Eta()))+(jet2->Et()*TMath::Exp(-jet2->Eta())))/(gData->Getmc_esum()-gData->Getmc_ez());
    //    fMJets = TMath::Sqrt(2*jet1->Et()*jet2->Et()*(TMath::Power(TMath::CosH(jet1->Eta()-jet2->Eta()),2)-TMath::Power(TMath::Cos(jet1->Phi()-jet2->Phi()),2)));

    //    TLorentzVector dijet = *jet1 + *jet2;

    Double_t mquadrat = (jet1->E()+jet2->E())*(jet1->E()+jet2->E())-(jet1->Px()+jet2->Px())*(jet1->Px()+jet2->Px())-(jet1->Py()+jet2->Py())*(jet1->Py()+jet2->Py())-(jet1->Pz()+jet2->Pz())*(jet1->Pz()+jet2->Pz());
    fMJets = TMath::Sqrt(mquadrat);
    //    cout << "fMJets "<< fMJets << endl;
    fDPhiJets = TMath::Abs(jet1->DeltaPhi(*jet2));
    fDRJets = jet1->DeltaR(*jet2);
    fPtJets = TMath::Power((jet1->Px()+jet2->Px()),2)+TMath::Power((jet1->Py()+jet2->Py()),2);
    //    fCosThetaStarJets = TMath::TanH((jet1->Eta()-jet2->Eta())/2);
  }

  return kTRUE;
}
//----------------------------------------------------------------------

Bool_t GMCs::CalcPart(Int_t index1, Int_t index2) {
  //
  // calculate variables
  if ( gDebug ) cout << endl << "GMCs::Calc called" << endl << endl;
  GJet *jet1 = 0;
  GJet *jet2 = 0;
  if (  fMCPMJetPtACut) {
    jet1 = GetMCPMJetWithID(index1);
    //	cout << "jet1->Px() " << jet1->Px() <<   "jet1->Py() " << jet1->Py() <<   "jet1->Pz() " << jet1->Pz() <<   "jet1->E() " << jet1->E() <<  endl;

    fPartXGammaJets = jet1->E()-jet1->Pz();
    fPartXGammaJets_zufo = jet1->E()-jet1->Pz();
  }
  if (  fMCPMJetPtBCut ) {
    jet2 = GetMCPMJetWithID(index2);
    //cout << "jet2->Px() " << jet2->Px() <<   "jet2->Py() " << jet2->Py() <<   "jet2->Pz() " << jet2->Pz() <<   "jet2->E() " << jet2->E() <<  endl;

    if ( fPartXGammaJets == -9999.99 ){
      fPartXGammaJets = jet2->E()-jet2->Pz();
    }else{
      fPartXGammaJets += jet2->E()-jet2->Pz();
    }
    if ( fXGammaJets_zufo == -9999.99 ){
      fPartXGammaJets_zufo = jet2->E()-jet2->Pz();
    }else{
      fPartXGammaJets_zufo += jet2->E()-jet2->Pz();
    }
  }
  if(jet1 && jet2) fPartEtaJets = TMath::Abs((jet1->Eta()+jet2->Eta())/2);
  fPartXGammaJets /= (gData->Getmc_esum()-gData->Getmc_ez());
  fPartXGammaJets_zufo /= (gData->Getmc_esum()-gData->Getmc_ez());
  if(fPartXGammaJets>=1) fXGammaJets=0.99999;
  if(fPartXGammaJets_zufo>=1) fXGammaJets_zufo=0.99999;

  if ( (jet1!=0)&&(jet2!=0) ) {
    fPartXGamma = ((jet1->Et()*TMath::Exp(-jet1->Eta()))+(jet2->Et()*TMath::Exp(-jet2->Eta())))/(gData->Getmc_esum()-gData->Getmc_ez());
    Double_t mquadrat = (jet1->E()+jet2->E())*(jet1->E()+jet2->E())-(jet1->Px()+jet2->Px())*(jet1->Px()+jet2->Px())-(jet1->Py()+jet2->Py())*(jet1->Py()+jet2->Py())-(jet1->Pz()+jet2->Pz())*(jet1->Pz()+jet2->Pz());
    fPartMJets = TMath::Sqrt(mquadrat);
    fPartDPhiJets = TMath::Abs(jet1->DeltaPhi(*jet2));
    fPartDRJets = jet1->DeltaR(*jet2);
    fPartPtJets = TMath::Power((jet1->Px()+jet2->Px()),2)+TMath::Power((jet1->Py()+jet2->Py()),2);
  }
  return kTRUE;
}

//__________________________________________________________________
Bool_t	GMCs::CalcMJCosThetaStarhbmjets(){
    if ( gDebug ) cout << endl << "GMCs::CalcMJCosThetaStarhbmjets called" << endl << endl;

  Double_t jetPt2= 6;
  Double_t jetEta2 = -999;
  Int_t    jetID2 = -999;
  Double_t jetE2=0;
  Double_t jetPz2=0;
  Double_t  MJCosThetaStar = -999;
  Double_t xgamma = 0;
  Double_t etajets = 999;
  Double_t MJets = -999;
   for ( Int_t j = 0; j < fNMCHBMJets; j++ ) {
     GJet *jet =((GJet*)( fMCHBMJets->At(j)));

     if(  IsMuonAssociatedToMCJet(jet)){
       for ( Int_t i = 0; i < fNMCHBMJets; i++ ) {
	 GJet *jet2 =((GJet*)( fMCHBMJets->At(i)));
	 jetID2  = jet2->GetID();
	 Int_t jetID = jet->GetID();
	 
	 if ((jetID2!=jetID) && (jet2->Pt()> jetPt2)){
	   jetEta2 = jet2->Eta();
	   jetPt2 = jet2->Pt();
	   jetE2 = jet2->E();
	   jetPz2 = jet2->Pz();
	   Double_t mquadrat = (jet->E()+jet2->E())*(jet->E()+jet2->E())-(jet->Px()+jet2->Px())*(jet->Px()+jet2->Px())-(jet->Py()+jet2->Py())*(jet->Py()+jet2->Py())-(jet->Pz()+jet2->Pz())*(jet->Pz()+jet2->Pz());
	   MJets = TMath::Sqrt(mquadrat);


	 }
       }
       MJCosThetaStar = TMath::TanH((jet->Eta()-jetEta2)/2);
       etajets = TMath::Abs((jet->Eta()+jetEta2)/2);
       jet->SetMJCosThetaStar(MJCosThetaStar);
       jet->SetSecondJetID(jetID2);
       jet->SetMJCosThetaStar_EtaJets(etajets);
       jet->SetMJCosThetaStar_MJets(MJets);

       if(jetID2>0) xgamma = (jet->E()-jet->Pz() + jetE2 - jetPz2) /(gData->Getmc_esum()-gData->Getmc_ez());
              jet->SetMJCosThetaStar_xgamma(xgamma);
     }

   }



   GJet *jetfirst  = GetMCHBMJetWithID(fIndex1);
   GJet *jetsecond = GetMCHBMJetWithID(fIndex2);
   if(jetfirst && jetsecond){
     if(IsMuonAssociatedToMCJet(jetfirst))        fCosThetaStarJets = TMath::TanH((jetfirst->Eta()-jetsecond->Eta())/2);
     else if (IsMuonAssociatedToMCJet(jetsecond))  fCosThetaStarJets = TMath::TanH((jetsecond->Eta()-jetfirst->Eta())/2);
   }
   return kTRUE;
   
}

//__________________________________________________________________
Bool_t	GMCs::CalcMJCosThetaStarpmjets(){
  if ( gDebug ) cout << endl << "GMCs::CalcMJCosThetaStarpmjets called" << endl << endl;
  
  Double_t jetPt2= 6;
  Double_t jetEta2 = -999;
  Int_t    jetID2 = -999;
  Double_t jetE2=0;
  Double_t jetPz2=0;
  Double_t  MJCosThetaStar = -999;
  Double_t xgamma = 0;
  Double_t etajets = 999;
  Double_t MJets = -999;

  for ( Int_t j = 0; j < fNMCPMJets; j++ ) {
    GJet *jet =((GJet*)( fMCPMJets->At(j)));
    
    if(  IsMuonAssociatedToMCPMJet(jet)){
      for ( Int_t i = 0; i < fNMCPMJets; i++ ) {
	GJet *jet2 =((GJet*)( fMCPMJets->At(i)));
	jetID2  = jet2->GetID();
	Int_t jetID = jet->GetID();
	
	if ((jetID2!=jetID) && (jet2->Pt()> jetPt2)){
	  jetEta2 = jet2->Eta();
	  jetPt2 = jet2->Pt();
	  jetE2 = jet2->E();
	  jetPz2 = jet2->Pz();
	  Double_t mquadrat = (jet->E()+jet2->E())*(jet->E()+jet2->E())-(jet->Px()+jet2->Px())*(jet->Px()+jet2->Px())-(jet->Py()+jet2->Py())*(jet->Py()+jet2->Py())-(jet->Pz()+jet2->Pz())*(jet->Pz()+jet2->Pz());
	  MJets = TMath::Sqrt(mquadrat);

	}
      }
      MJCosThetaStar = TMath::TanH((jet->Eta()-jetEta2)/2);
       etajets = TMath::Abs((jet->Eta()+jetEta2)/2);
      jet->SetMJCosThetaStar(MJCosThetaStar);
      jet->SetSecondJetID(jetID2);
      if(jetID2>0) xgamma = (jet->E()-jet->Pz() + jetE2 - jetPz2) /(gData->Getmc_esum()-gData->Getmc_ez());
      jet->SetMJCosThetaStar_xgamma(xgamma);
      jet->SetMJCosThetaStar_EtaJets(etajets);
      jet->SetMJCosThetaStar_MJets(MJets);

    }
    
  }
  
  GJet *jetfirst  = GetMCPMJetWithID(fIndex1);
  GJet *jetsecond = GetMCPMJetWithID(fIndex2);
  if(jetfirst && jetsecond){
    if(IsMuonAssociatedToMCPMJet(jetfirst))        fPartCosThetaStarJets = TMath::TanH((jetfirst->Eta()-jetsecond->Eta())/2);
    else if (IsMuonAssociatedToMCPMJet(jetsecond))  fPartCosThetaStarJets = TMath::TanH((jetsecond->Eta()-jetfirst->Eta())/2);
  }
  return kTRUE;
} 
