//
// GJets.h
//
// $Author: meyer $
// $Date: 2008/06/10 07:10:38 $
// $Revision: 1.26 $
//

#ifndef GUT_GJets
#define GUT_GJets

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GJets : public GPhysObj {

 private:

  TClonesArray        *fJets;                                  // array of jets
  Int_t                fNJets;                                 // jet counter  

  // cut flags
  Bool_t               fPtACut;                                // event with one jet fulfilling cuts on p_t for highest p_t jet and eta
  Bool_t               fPtBCut;                                // event with one jet fulfilling cuts on p_t for second highest p_t jet and eta

  // variables
  Int_t                fIndex1;                                // index of highest jet
  Int_t                fIndex2;                                // index of second highest jet
  Double_t             fXGammaJets;                            // x_gamma^jets
  Double_t             fXGamma;                                // x_gamma^jets in second definition
  Double_t             fXGammaJets_zufo;                       // x_gamma^jets with zufo properties
  Double_t             fMJets;                                 // dijet invariant mass
  Double_t             fDPhiJets;                              // dphi from jets
  Double_t             fDRJets;                                // dr from jets
  Double_t             fPtJets;                                // p_T of dijet system
  Double_t             fCosThetaStarJets;                      // cos ( theta* )
  Double_t             fEtaJets;                               // average eta of jets
  // general histograms
  TH1D                *fGeneraln;                              // number of jets
  TH1D                *fGeneralE_A;                            // energy for highest transverse momentum jet
  TH1D                *fGeneralE_B;                            // energy for second highest transverse momentum jet
  TH1D                *fGeneralPt_A;                           // transverse momentum for highest transverse momentum jet
  TH1D                *fGeneralPt_B;                           // transverse momentum for second highest transverse momentum jet
  TH1D                *fGeneralEt_A;                           // transverse energy for highest transverse momentum jet
  TH1D                *fGeneralEt_B;                           // transverse energy for second highest transverse momentum jet
  TH1D                *fGeneralEt_A_breit;                     // transverse energy for highest transverse momentum jet in breitframe variables
  TH1D                *fGeneralEt_B_breit;                     // transverse energy for second highest transverse momentum jet in breitframe variables
  TH1D                *fGeneralEta_A;                          // pseudorapidity for highest transverse momentum jet
  TH1D                *fGeneralEta_B;                          // pseudorapidity for second highest transverse momentum jet
  TH1D                *fGeneralEta_A_Large;                    // pseudorapidity for highest transverse momentum jet in large eta range
  TH1D                *fGeneralEta_B_Large;                    // pseudorapidity for second highest transverse momentum jet in large eta range
  TH1D                *fGeneralPhi_A;                          // phi for highest transverse momentum jet
  TH1D                *fGeneralPhi_B;                          // phi for second highest transverse momentum jet
  TH1D                *fGeneralXGamma;                         // x_gamma^jet plot
  TH1D                *fGeneralXGamma2;                        // x_gamma^jet plot 2nd definition
  TH1D                *fGeneralXGamma_zufo;                    // x_gamma^jet plot with zufo properties
  TH1D                *fGeneralMJets;                          // jet dijet invariant mass
  TH1D                *fGeneralDPhiJets;                       // jet dijet dphi
  TH1D                *fGeneralPtJets;                         // jet dijet p_T
  TH1D                *fGeneralMass_A;                         // jet mass for highest transverse momentum jet
  TH1D                *fGeneralMass_B;                         // jet mass for second highest transverse momentum jet
  TH1D                *fGeneralMass_Matched;                   // jet mass for highest or second highest transverse momentum jet which is matched to an muon
  TH1D                *fGeneralMass_Unmatched;                 // jet mass for highest or second highest transverse momentum jet which is not matched to an muon
  TH1D                *fGeneralPt_Matched;                     // transverse momentum for highest or second highest transverse momentum jet which is matched to an muon
  TH1D                *fGeneralPt_Unmatched;                   // transverse momentum for highest or second highest transverse momentum jet which is not matched to an muon
  TH1D                *fGeneralEt_Matched;                     // transverse energy for highest or second highest transverse momentum jet which is matched to an muon
  TH1D                *fGeneralEt_Unmatched;                   // transverse energy for highest or second highest transverse momentum jet which is not matched to an muon
  TH1D                *fGeneralEt_Matched_breit;               // transverse energy for highest or second highest transverse momentum jet which is matched to an muon in breitframe variables
  TH1D                *fGeneralEt_Unmatched_breit;             // transverse energy for highest or second highest transverse momentum jet which is not matched to an muon in breitframe variables

  TH1D                *fGeneralCostherastarXgamma;             // xgamma used for mjmatchcosthetastar plots
  TH1D                *fGeneralEt_0_10_Matched    ;            // transverse energy for highest or second highest transverse momentum jet which is matched to an muon for 0 < Q2 < 10 
  TH1D                *fGeneralEt_0_10_Unmatched  ;
  TH1D                *fGeneralEt_10_200_Matched  ;
  TH1D                *fGeneralEt_10_200_Unmatched;
  TH1D                *fGeneralEt_200_Matched     ;
  TH1D                *fGeneralEt_200_Unmatched   ;
  TH1D                *fGeneralEt_0_10_Matched_breit    ;            // transverse energy for highest or second highest transverse momentum jet which is matched to an muon for 0 < Q2 < 10 in breitframe vars.
  TH1D                *fGeneralEt_0_10_Unmatched_breit  ;
  TH1D                *fGeneralEt_10_200_Matched_breit  ;
  TH1D                *fGeneralEt_10_200_Unmatched_breit;
  TH1D                *fGeneralEt_200_Matched_breit     ;
  TH1D                *fGeneralEt_200_Unmatched_breit   ;
  
  TH1D                *fGeneralEta_Matched;                          // pseudorapidity for highest or second highest transverse momentum jet which is matched to an muon
  TH1D                *fGeneralEta_Unmatched;                        // pseudorapidity for highest or second highest transverse momentum jet which is not matched to an muon
  TH1D                *fGeneralEta_Matched_Large;                    // pseudorapidity for highest or second highest transverse momentum jet which is matched to an muon in large eta range
  TH1D                *fGeneralEta_Unmatched_Large;                  // pseudorapidity for highest or second highest transverse momentum jet which is not matched to an muon in large eta range
  TH1D                *fGeneralPhi_Matched;                          // phi for highest or second highest transverse momentum jet which is matched to an muon
  TH1D                *fGeneralPhi_Unmatched;                        // phi for highest or second highest transverse momentum jet which is not matched to an muon

  TH1D                *fGeneralPtMinPtTrue;                          // for all good jets: (p_T - p_T^TRUE)/p_T^TRUE
  TH2D                *fGeneralPtVsPtTrue;                           // for all good jets: p_T vs. p_T^TRUE
  TH1D                *fGeneralEtaMinEtaTrue;                        // for all good jets: (eta - eta^TRUE)/eta^TRUE
  TH2D                *fGeneralEtaVsEtaTrue;                         // for all good jets: eta vs. eta^TRUE
  

  TH1D                *fGeneraln_uncut;                              // uncut number of jets
  TH1D                *fGeneralE_uncut;                              // uncut energy
  TH1D                *fGeneralPt_uncut;                             // uncut transverse momentum
  TH1D                *fGeneralEt_uncut;                             // uncut transverse energy
  TH1D                *fGeneralEta_uncut;                            // uncut pseudorapidity in large eta range
  TH1D                *fGeneralPhi_uncut;                            // uncut phi
  TH1D                *fGeneralMass_uncut;                           // jet mass
  TH1D                *fGeneralXGamma_uncut;                         // x_gamma^jet plot
  TH1D                *fGeneralXGamma_zufo_uncut;                    // x_gamma^jet plot with zufo properties

  TH1D                *fGeneralCrossMuonJetPt;                       // muon jet pt for cross section
  TH1D                *fGeneralCrossMuonJetPtRecNTrue;               // muon jet pt  rec and true for cross section

  TH1D                *fGeneralCrossMuonJetEta;                      // muon jet eta for cross section
  TH1D                *fGeneralCrossMuonJetEtaRecNTrue;              // muon jet eta  rec and true for cross section

  TH1D                *fGeneralCrossMuonJetPtFine;                         // fine muon jet pt for cross section
  TH1D                *fGeneralCrossMuonJetPtFineRecNTrue;           // fine muon jet pt  rec and true for cross section

  TH1D                *fGeneralCrossMuonJetEtaFine;                  // fine muon jet eta for cross section
  TH1D                *fGeneralCrossMuonJetEtaFineRecNTrue;          // fine muon jet eta  rec and true for cross section

  TH1D                *fGeneralCrossJetXGamma;                       // x_gamma_zufo for cross section
  TH1D                *fGeneralCrossJetXGammaRecNTrue;               // x_gamma_zufo rec and true for cross section

  TH1D                *fGeneralCrossJetXGammaFine;                   // fine x_gamma_zufo for cross section
  TH1D                *fGeneralCrossJetXGammaFineRecNTrue;           // fine x_gamma_zufo rec and true for cross section

  TH1D                *fGeneralCrossJetMJets;                        // jet dijet invariant mass for cross section
  TH1D                *fGeneralCrossJetMJetsRecNTrue;                // jet dijet invariant mass rec and true for cross section
  TH1D                *fGeneralCrossJetMJetsLow;                     // jet dijet invariant mass for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetMJetsLowRecNTrue;             // jet dijet invariant mass rec and true for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetMJetsHigh;                    // jet dijet invariant mass for cross section for x_gamma > 0.75
  TH1D                *fGeneralCrossJetMJetsHighRecNTrue;            // jet dijet invariant mass rec and true for cross section for x_gamma > 0.75

  TH1D                *fGeneralCrossJetDPhiJets;                     // jet dijet dphi for cross section
  TH1D                *fGeneralCrossJetDPhiJetsRecNTrue;             // jet dijet dphi rec and true for cross section
  TH1D                *fGeneralCrossJetDPhiJetsLow;                  // jet dijet dphi for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetDPhiJetsLowRecNTrue;          // jet dijet dphi rec and true for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetDPhiJetsHigh;                 // jet dijet dphi for cross section for x_gamma > 0.75
  TH1D                *fGeneralCrossJetDPhiJetsHighRecNTrue;         // jet dijet dphi rec and true for cross section for x_gamma > 0.75

  TH1D                *fGeneralCrossJetDRJets;                       // jet dijet dr for cross section
  TH1D                *fGeneralCrossJetDRJetsRecNTrue;               // jet dijet dr rec and true for cross section
  TH1D                *fGeneralCrossJetDRJetsLow;                    // jet dijet dr for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetDRJetsLowRecNTrue;            // jet dijet dr rec and true for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetDRJetsHigh;                   // jet dijet dr for cross section for x_gamma > 0.75
  TH1D                *fGeneralCrossJetDRJetsHighRecNTrue;           // jet dijet dr rec and true for cross section for x_gamma > 0.75

  TH1D                *fGeneralCrossJetPtJets;                       // jet dijet p_T for cross section
  TH1D                *fGeneralCrossJetPtJetsRecNTrue;               // jet dijet p_T rec and true for cross section
  TH1D                *fGeneralCrossJetPtJetsLow;                    // jet dijet p_T for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetPtJetsLowRecNTrue;            // jet dijet p_T rec and true for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetPtJetsHigh;                   // jet dijet p_T for cross section for x_gamma > 0.75
  TH1D                *fGeneralCrossJetPtJetsHighRecNTrue;           // jet dijet p_T rec and true for cross section for x_gamma > 0.75

  TH1D                *fGeneralCrossJetCosThetaStarJets;             // jet cos(theta*) for cross section
  TH1D                *fGeneralCrossJetCosThetaStarJetsRecNTrue;     // jet cos(theta*) rec and true for cross section
  TH1D                *fGeneralCrossJetCosThetaStarJetsLow;          // jet cos(theta*) for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetCosThetaStarJetsLowRecNTrue;  // jet cos(theta*) rec and true for cross section for x_gamma < 0.75
  TH1D                *fGeneralCrossJetCosThetaStarJetsHigh;         // jet cos(theta*) for cross section for x_gamma > 0.75
  TH1D                *fGeneralCrossJetCosThetaStarJetsHighRecNTrue; // jet cos(theta*) rec and true for cross section for x_gamma > 0.75

  // control plots

  TH1D                *fControlPt_uncut;            // uncut control plot for p_t
  TH1D                *fControlEta_uncut;           // uncut control plot for eta

  TH1D                *fControlPtA;                 // control plot for p_t of highest jet
  TH1D                *fControlPtB;                 // control plot for p_t of second highest jet
  TH1D                *fControlEtaA;                // control plot for eta of highest jet
  TH1D                *fControlEtaB;                // control plot for eta of second highest jet

 public:
  GJets();
  virtual ~GJets();

  virtual Bool_t FillHistos();

  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();

  virtual Bool_t ObjectsFillHistos();
  virtual Bool_t ObjectsFillGeneral(GJet *jet);
  virtual Bool_t ObjectsFillControl(GJet *jet);

  virtual Bool_t Reset();

  virtual Bool_t Do();

  virtual Bool_t Fill();

  virtual Bool_t Calc(Int_t index1, Int_t index2);

  virtual Double_t GetE(Int_t index);
  virtual Double_t GetEtbreit(Int_t index);
  virtual Double_t GetPt(Int_t index);
  virtual GJet* GetJet(Int_t index);
  virtual GJet* GetJetWithID(Int_t id);

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  inline virtual Int_t GetNJets() { return fNJets; }

  inline virtual Bool_t GetPtACut()  { return fPtACut;    }
  inline virtual Bool_t GetPtBCut()  { return fPtBCut;    }

  virtual Bool_t GetAllCuts();

  inline virtual Double_t GetXGamma()                { return fXGammaJets;      }
  inline virtual Double_t GetXGamma_zufo()           { return fXGammaJets_zufo; }
  inline virtual Double_t GetXGamma2()               { return fXGamma;          }
  inline virtual Double_t GetMJets()                 { return fMJets;           }
  inline virtual Double_t GetDPhiJets()              { return fDPhiJets;        }
  inline virtual Double_t GetDRJets()                { return fDRJets;          }
  inline virtual Double_t GetPtJets()                { return fPtJets;          }
  inline virtual Double_t GetCosThetaStarJets()      { return fCosThetaStarJets;}
  inline virtual Double_t GetEtaJets()               {return  fEtaJets;         }
  inline virtual Int_t GetHighestJetID()          { return fIndex1;}
  inline virtual Int_t GetSecondHighestJetID()    { return fIndex2;}
  inline virtual void SetCosThetaStarJets(Double_t input) { fCosThetaStarJets = input;}
  ClassDef(GJets,0) // Jets Class for everything which is related only to JETs
};

R__EXTERN GJets *gJets;

#endif
