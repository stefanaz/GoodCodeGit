//
// GTJMatchs.h
//
// $Author: meyer $
// $Date: 2008/06/10 07:22:35 $
// $Revision: 1.15 $
//

#ifndef GUT_GTJMatchs
#define GUT_GTJMatchs

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GTJMatch;

class GTJMatchs : public GPhysObj {

 private:

  TClonesArray   *fMatchs;                                       // holds matchs objects per event 
  Int_t           fNMatchs;                                      // number of matchs
  
  Bool_t          fTJMatchCut;                                   // true if one match exists fulfilling cuts 

  // general plots (Mu is not replaced by track for easy copy to ptrel correction root file)
  TH1D                *fNperEv_uncut;                            // uncut matches per event
  TH1D                *fPtRel_uncut;                             // uncut pt rel distribution
  TH1D                *fPtRel_JetMinMu_uncut;                    // uncut pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_Forward_uncut;                     // uncut pt rel distribution
  TH1D                *fPtRel_JetMinMu_Forward_uncut;            // uncut pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_Barrel_uncut;                      // uncut pt rel distribution
  TH1D                *fPtRel_JetMinMu_Barrel_uncut;             // uncut pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_Rear_uncut;                        // uncut pt rel distribution
  TH1D                *fPtRel_JetMinMu_Rear_uncut;               // uncut pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_4_8_uncut;                       // uncut pt rel distribution with 8 equidistant bins from 0 to 4
  TH1D                *fPtRel_0_4_8_JetMinMu_uncut;              // uncut pt rel distribution with 8 equidistant bins from 0 to 4 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_10_uncut;                      // uncut pt rel distribution with 10 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_10_JetMinMu_uncut;             // uncut pt rel distribution with 10 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_20_uncut;                      // uncut pt rel distribution with 20 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_20_JetMinMu_uncut;             // uncut pt rel distribution with 20 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_3_6_uncut;                       // uncut pt rel distribution with 6 equidistant bins from 0 to 3
  TH1D                *fPtRel_0_3_6_JetMinMu_uncut;              // uncut pt rel distribution with 6 equidistant bins from 0 to 3 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_uncut;                       // uncut pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_uncut;              // uncut pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_Forward_uncut;               // uncut forward muon pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_Forward_uncut;      // uncut forward muon pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_Barrel_uncut;                // uncut barrel muon pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_Barrel_uncut;       // uncut barrel muon pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_Rear_uncut;                  // uncut rear muon pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_Rear_uncut;         // uncut rear muon pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)

  TH1D                *fPtRel_CrossMuonPt_Bin1;                         // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_CrossMuonPt_Bin2;                         // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_CrossMuonPt_Bin3;                         // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_CrossMuonPt_Bin4;                         // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_CrossMuonPt_Bin1_JetMinMu;                // ptrel distribution for bin 1 for muon pt cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonPt_Bin2_JetMinMu;                // ptrel distribution for bin 1 for muon pt cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonPt_Bin3_JetMinMu;                // ptrel distribution for bin 1 for muon pt cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonPt_Bin4_JetMinMu;                // ptrel distribution for bin 1 for muon pt cross section - JetMinMu

  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin1;                   // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin2;                   // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin3;                   // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin4;                   // ptrel distribution for bin 1 for muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu;          // ptrel distribution for bin 1 for muon pt cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu;          // ptrel distribution for bin 1 for muon pt cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu;          // ptrel distribution for bin 1 for muon pt cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu;          // ptrel distribution for bin 1 for muon pt cross section - JetMinMu

  TH1D                *fPtRel_CrossMuonEta_Bin1;                        // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_CrossMuonEta_Bin2;                        // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_CrossMuonEta_Bin3;                        // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_CrossMuonEta_Bin4;                        // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_CrossMuonEta_Bin1_JetMinMu;               // ptrel distribution for bin 1 for muon eta cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonEta_Bin2_JetMinMu;               // ptrel distribution for bin 1 for muon eta cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonEta_Bin3_JetMinMu;               // ptrel distribution for bin 1 for muon eta cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonEta_Bin4_JetMinMu;               // ptrel distribution for bin 1 for muon eta cross section - JetMinMu

  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin1;                  // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin2;                  // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin3;                  // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin4;                  // ptrel distribution for bin 1 for muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu;         // ptrel distribution for bin 1 for muon eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu;         // ptrel distribution for bin 1 for muon eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu;         // ptrel distribution for bin 1 for muon eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu;         // ptrel distribution for bin 1 for muon eta cross section - JetMinMu

  TH1D                *fPtRel_CrossMuonPtFine_Bin1;                     // ptrel distribution for bin 1 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin2;                     // ptrel distribution for bin 2 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin3;                     // ptrel distribution for bin 3 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin4;                     // ptrel distribution for bin 4 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin5;                     // ptrel distribution for bin 5 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin6;                     // ptrel distribution for bin 6 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin7;                     // ptrel distribution for bin 7 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin8;                     // ptrel distribution for bin 8 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin9;                     // ptrel distribution for bin 9 for fine muon pt cross section 
  TH1D                *fPtRel_CrossMuonPtFine_Bin1_JetMinMu;            // ptrel distribution for bin 1 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin2_JetMinMu;            // ptrel distribution for bin 2 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin3_JetMinMu;            // ptrel distribution for bin 3 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin4_JetMinMu;            // ptrel distribution for bin 4 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin5_JetMinMu;            // ptrel distribution for bin 5 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin6_JetMinMu;            // ptrel distribution for bin 6 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin7_JetMinMu;            // ptrel distribution for bin 7 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin8_JetMinMu;            // ptrel distribution for bin 8 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtFine_Bin9_JetMinMu;            // ptrel distribution for bin 9 for fine muon pt cross section - JetMinMu 

  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin1;               // ptrel distribution for bin 1 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin2;               // ptrel distribution for bin 2 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin3;               // ptrel distribution for bin 3 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin4;               // ptrel distribution for bin 4 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin5;               // ptrel distribution for bin 5 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin6;               // ptrel distribution for bin 6 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin7;               // ptrel distribution for bin 7 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin8;               // ptrel distribution for bin 8 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin9;               // ptrel distribution for bin 9 for fine muon pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu;      // ptrel distribution for bin 1 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu;      // ptrel distribution for bin 2 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu;      // ptrel distribution for bin 3 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu;      // ptrel distribution for bin 4 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu;      // ptrel distribution for bin 5 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu;      // ptrel distribution for bin 6 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu;      // ptrel distribution for bin 7 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu;      // ptrel distribution for bin 8 for fine muon pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu;      // ptrel distribution for bin 9 for fine muon pt cross section - JetMinMu 

  TH1D                *fPtRel_CrossMuonEtaFine_Bin1;                    // ptrel distribution for bin 1 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin2;                    // ptrel distribution for bin 2 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin3;                    // ptrel distribution for bin 3 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin4;                    // ptrel distribution for bin 4 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin5;                    // ptrel distribution for bin 5 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin6;                    // ptrel distribution for bin 6 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin7;                    // ptrel distribution for bin 7 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin8;                    // ptrel distribution for bin 8 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin9;                    // ptrel distribution for bin 9 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin10;                   // ptrel distribution for bin 10 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin11;                   // ptrel distribution for bin 11 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin12;                   // ptrel distribution for bin 12 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin13;                   // ptrel distribution for bin 13 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin14;                   // ptrel distribution for bin 14 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin15;                   // ptrel distribution for bin 15 for fine muon eta cross section 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin1_JetMinMu;           // ptrel distribution for bin 1 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin2_JetMinMu;           // ptrel distribution for bin 2 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin3_JetMinMu;           // ptrel distribution for bin 3 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin4_JetMinMu;           // ptrel distribution for bin 4 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin5_JetMinMu;           // ptrel distribution for bin 5 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin6_JetMinMu;           // ptrel distribution for bin 6 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin7_JetMinMu;           // ptrel distribution for bin 7 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin8_JetMinMu;           // ptrel distribution for bin 8 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin9_JetMinMu;           // ptrel distribution for bin 9 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin10_JetMinMu;          // ptrel distribution for bin 10 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin11_JetMinMu;          // ptrel distribution for bin 11 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin12_JetMinMu;          // ptrel distribution for bin 12 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin13_JetMinMu;          // ptrel distribution for bin 13 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin14_JetMinMu;          // ptrel distribution for bin 14 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaFine_Bin15_JetMinMu;          // ptrel distribution for bin 15 for fine muon eta cross section - JetMinMu 

  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin1;              // ptrel distribution for bin 1 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin2;              // ptrel distribution for bin 2 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin3;              // ptrel distribution for bin 3 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin4;              // ptrel distribution for bin 4 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin5;              // ptrel distribution for bin 5 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin6;              // ptrel distribution for bin 6 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin7;              // ptrel distribution for bin 7 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin8;              // ptrel distribution for bin 8 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin9;              // ptrel distribution for bin 9 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin10;             // ptrel distribution for bin 10 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin11;             // ptrel distribution for bin 11 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin12;             // ptrel distribution for bin 12 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin13;             // ptrel distribution for bin 13 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin14;             // ptrel distribution for bin 14 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin15;             // ptrel distribution for bin 15 for fine muon eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu;     // ptrel distribution for bin 1 for fine muon eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu;     // ptrel distribution for bin 2 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu;     // ptrel distribution for bin 3 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu;     // ptrel distribution for bin 4 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu;     // ptrel distribution for bin 5 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu;     // ptrel distribution for bin 6 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu;     // ptrel distribution for bin 7 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu;     // ptrel distribution for bin 8 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu;     // ptrel distribution for bin 9 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu;    // ptrel distribution for bin 10 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu;    // ptrel distribution for bin 11 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu;    // ptrel distribution for bin 12 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu;    // ptrel distribution for bin 13 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu;    // ptrel distribution for bin 14 for fine muon eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu;    // ptrel distribution for bin 15 for fine muon eta cross section - JetMinMu 

  TH1D                *fPtRel_CrossMuonFinder_Bin0;
  TH1D                *fPtRel_CrossMuonFinder_Bin1;
  TH1D                *fPtRel_CrossMuonFinder_Bin2;
  TH1D                *fPtRel_CrossMuonFinder_Bin3;
  TH1D                *fPtRel_CrossMuonFinder_Bin4;
  TH1D                *fPtRel_CrossMuonFinder_Bin5;
  TH1D                *fPtRel_CrossMuonFinder_Bin6;
  TH1D                *fPtRel_CrossMuonFinder_Bin7;
  TH1D                *fPtRel_CrossMuonFinder_Bin8;
  TH1D                *fPtRel_CrossMuonFinder_Bin9;
  TH1D                *fPtRel_CrossMuonFinder_Bin10;
  TH1D                *fPtRel_CrossMuonFinder_Bin11;
  TH1D                *fPtRel_CrossMuonFinder_Bin12;
  TH1D                *fPtRel_CrossMuonFinder_Bin13;
  TH1D                *fPtRel_CrossMuonFinder_Bin14;
  TH1D                *fPtRel_CrossMuonFinder_Bin0_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin1_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin2_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin3_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin4_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin5_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin6_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin7_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin8_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin9_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin10_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin11_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin12_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin13_JetMinMu;
  TH1D                *fPtRel_CrossMuonFinder_Bin14_JetMinMu;

  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin0;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin1;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin2;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin3;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin4;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin5;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin6;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin7;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin8;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin9;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin10;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin11;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin12;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin13;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin14;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu;
  TH1D                *fPtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu;

  TH1D                *fPtRel_CrossMuonPtMassimo_Bin1;                     // ptrel distribution for bin 1 for muon pt cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonPtMassimo_Bin2;                     // ptrel distribution for bin 2 for muon pt cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonPtMassimo_Bin3;                     // ptrel distribution for bin 3 for muon pt cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonPtMassimo_Bin1_JetMinMu;            // ptrel distribution for bin 1 for muon pt cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtMassimo_Bin2_JetMinMu;            // ptrel distribution for bin 2 for muon pt cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_CrossMuonPtMassimo_Bin3_JetMinMu;            // ptrel distribution for bin 3 for muon pt cross section in massimo's binning - JetMinMu 

  TH1D                *fPtRel_0_5_7_CrossMuonPtMassimo_Bin1;               // ptrel distribution for bin 1 for muon pt cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonPtMassimo_Bin2;               // ptrel distribution for bin 2 for muon pt cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonPtMassimo_Bin3;               // ptrel distribution for bin 3 for muon pt cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu;      // ptrel distribution for bin 1 for muon pt cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu;      // ptrel distribution for bin 2 for muon pt cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu;      // ptrel distribution for bin 3 for muon pt cross section in massimo's binning - JetMinMu 

  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin1;                    // ptrel distribution for bin 1 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin2;                    // ptrel distribution for bin 2 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin3;                    // ptrel distribution for bin 3 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin4;                    // ptrel distribution for bin 4 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin1_JetMinMu;           // ptrel distribution for bin 1 for muon eta cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin2_JetMinMu;           // ptrel distribution for bin 2 for muon eta cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin3_JetMinMu;           // ptrel distribution for bin 3 for muon eta cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_CrossMuonEtaMassimo_Bin4_JetMinMu;           // ptrel distribution for bin 4 for muon eta cross section in massimo's binning - JetMinMu 

  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1;              // ptrel distribution for bin 1 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2;              // ptrel distribution for bin 2 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3;              // ptrel distribution for bin 3 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4;              // ptrel distribution for bin 4 for muon eta cross section in massimo's binning 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu;     // ptrel distribution for bin 1 for muon eta cross section in massimo's binning - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu;     // ptrel distribution for bin 2 for muon eta cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu;     // ptrel distribution for bin 3 for muon eta cross section in massimo's binning - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu;     // ptrel distribution for bin 4 for muon eta cross section in massimo's binning - JetMinMu 

  TH1D                *fPtRel_CrossMuonJetPt_Bin1;                      // ptrel distribution for bin 1 for muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPt_Bin2;                      // ptrel distribution for bin 1 for muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPt_Bin3;                      // ptrel distribution for bin 1 for muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPt_Bin1_JetMinMu;             // ptrel distribution for bin 1 for muon jet pt cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonJetPt_Bin2_JetMinMu;             // ptrel distribution for bin 1 for muon jet pt cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonJetPt_Bin3_JetMinMu;             // ptrel distribution for bin 1 for muon jet pt cross section - JetMinMu

  TH1D                *fPtRel_0_5_7_CrossMuonJetPt_Bin1;                // ptrel distribution for bin 1 for muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPt_Bin2;                // ptrel distribution for bin 1 for muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPt_Bin3;                // ptrel distribution for bin 1 for muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu;       // ptrel distribution for bin 1 for muon jet pt cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu;       // ptrel distribution for bin 1 for muon jet pt cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu;       // ptrel distribution for bin 1 for muon jet pt cross section - JetMinMu

  TH1D                *fPtRel_CrossMuonJetEta_Bin1;                     // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEta_Bin2;                     // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEta_Bin3;                     // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEta_Bin4;                     // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEta_Bin1_JetMinMu;            // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonJetEta_Bin2_JetMinMu;            // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonJetEta_Bin3_JetMinMu;            // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_CrossMuonJetEta_Bin4_JetMinMu;            // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu

  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin1;               // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin2;               // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin3;               // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin4;               // ptrel distribution for bin 1 for muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu;      // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu;      // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu;      // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu;      // ptrel distribution for bin 1 for muon jet eta cross section - JetMinMu

  TH1D                *fPtRel_CrossMuonJetPtFine_Bin1;                  // ptrel distribution for bin 1 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin2;                  // ptrel distribution for bin 2 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin3;                  // ptrel distribution for bin 3 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin4;                  // ptrel distribution for bin 4 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin5;                  // ptrel distribution for bin 5 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin6;                  // ptrel distribution for bin 6 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin7;                  // ptrel distribution for bin 7 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin8;                  // ptrel distribution for bin 8 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin9;                  // ptrel distribution for bin 9 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin10;                 // ptrel distribution for bin 0 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin11;                 // ptrel distribution for bin 1 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin12;                 // ptrel distribution for bin 2 for fine muon jet pt cross section 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin1_JetMinMu;         // ptrel distribution for bin 1 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin2_JetMinMu;         // ptrel distribution for bin 2 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin3_JetMinMu;         // ptrel distribution for bin 3 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin4_JetMinMu;         // ptrel distribution for bin 4 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin5_JetMinMu;         // ptrel distribution for bin 5 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin6_JetMinMu;         // ptrel distribution for bin 6 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin7_JetMinMu;         // ptrel distribution for bin 7 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin8_JetMinMu;         // ptrel distribution for bin 8 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin9_JetMinMu;         // ptrel distribution for bin 9 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin10_JetMinMu;        // ptrel distribution for bin 0 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin11_JetMinMu;        // ptrel distribution for bin 1 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetPtFine_Bin12_JetMinMu;        // ptrel distribution for bin 2 for fine muon jet pt cross section - JetMinMu 

  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin1;            // ptrel distribution for bin 1 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin2;            // ptrel distribution for bin 2 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin3;            // ptrel distribution for bin 3 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin4;            // ptrel distribution for bin 4 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin5;            // ptrel distribution for bin 5 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin6;            // ptrel distribution for bin 6 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin7;            // ptrel distribution for bin 7 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin8;            // ptrel distribution for bin 8 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin9;            // ptrel distribution for bin 9 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin10;           // ptrel distribution for bin 0 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin11;           // ptrel distribution for bin 1 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin12;           // ptrel distribution for bin 2 for fine muon jet pt cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu;   // ptrel distribution for bin 1 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu;   // ptrel distribution for bin 2 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu;   // ptrel distribution for bin 3 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu;   // ptrel distribution for bin 4 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu;   // ptrel distribution for bin 5 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu;   // ptrel distribution for bin 6 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu;   // ptrel distribution for bin 7 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu;   // ptrel distribution for bin 8 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu;   // ptrel distribution for bin 9 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu;  // ptrel distribution for bin 0 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu;  // ptrel distribution for bin 1 for fine muon jet pt cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu;  // ptrel distribution for bin 2 for fine muon jet pt cross section - JetMinMu 

  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin1;                 // ptrel distribution for bin 1 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin2;                 // ptrel distribution for bin 2 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin3;                 // ptrel distribution for bin 3 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin4;                 // ptrel distribution for bin 4 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin5;                 // ptrel distribution for bin 5 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin6;                 // ptrel distribution for bin 6 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin7;                 // ptrel distribution for bin 7 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin8;                 // ptrel distribution for bin 8 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin9;                 // ptrel distribution for bin 9 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin10;                // ptrel distribution for bin 10 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin11;                // ptrel distribution for bin 11 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin12;                // ptrel distribution for bin 12 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin13;                // ptrel distribution for bin 13 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin14;                // ptrel distribution for bin 14 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin15;                // ptrel distribution for bin 15 for fine muon jet eta cross section 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin1_JetMinMu;        // ptrel distribution for bin 1 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin2_JetMinMu;        // ptrel distribution for bin 2 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin3_JetMinMu;        // ptrel distribution for bin 3 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin4_JetMinMu;        // ptrel distribution for bin 4 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin5_JetMinMu;        // ptrel distribution for bin 5 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin6_JetMinMu;        // ptrel distribution for bin 6 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin7_JetMinMu;        // ptrel distribution for bin 7 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin8_JetMinMu;        // ptrel distribution for bin 8 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin9_JetMinMu;        // ptrel distribution for bin 9 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin10_JetMinMu;       // ptrel distribution for bin 10 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin11_JetMinMu;       // ptrel distribution for bin 11 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin12_JetMinMu;       // ptrel distribution for bin 12 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin13_JetMinMu;       // ptrel distribution for bin 13 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin14_JetMinMu;       // ptrel distribution for bin 14 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_CrossMuonJetEtaFine_Bin15_JetMinMu;       // ptrel distribution for bin 15 for fine muon jet eta cross section - JetMinMu 

  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1;           // ptrel distribution for bin 1 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2;           // ptrel distribution for bin 2 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3;           // ptrel distribution for bin 3 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4;           // ptrel distribution for bin 4 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5;           // ptrel distribution for bin 5 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6;           // ptrel distribution for bin 6 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7;           // ptrel distribution for bin 7 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8;           // ptrel distribution for bin 8 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9;           // ptrel distribution for bin 9 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10;          // ptrel distribution for bin 10 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11;          // ptrel distribution for bin 11 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12;          // ptrel distribution for bin 12 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13;          // ptrel distribution for bin 13 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14;          // ptrel distribution for bin 14 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15;          // ptrel distribution for bin 15 for fine muon jet eta cross section 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu;  // ptrel distribution for bin 1 for fine muon jet eta cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu;  // ptrel distribution for bin 2 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu;  // ptrel distribution for bin 3 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu;  // ptrel distribution for bin 4 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu;  // ptrel distribution for bin 5 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu;  // ptrel distribution for bin 6 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu;  // ptrel distribution for bin 7 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu;  // ptrel distribution for bin 8 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu;  // ptrel distribution for bin 9 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu; // ptrel distribution for bin 10 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu; // ptrel distribution for bin 11 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu; // ptrel distribution for bin 12 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu; // ptrel distribution for bin 13 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu; // ptrel distribution for bin 14 for fine muon jet eta cross section - JetMinMu 
  TH1D                *fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu; // ptrel distribution for bin 15 for fine muon jet eta cross section - JetMinMu 

  TH1D                *fPtRel_CrossJetXGamma_Bin1;                      // ptrel distribution for bin 1 for jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGamma_Bin2;                      // ptrel distribution for bin 2 for jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGamma_Bin3;                      // ptrel distribution for bin 3 for jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGamma_Bin4;                      // ptrel distribution for bin 4 for jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGamma_Bin5;                      // ptrel distribution for bin 3 for jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGamma_Bin1_JetMinMu;             // ptrel distribution for bin 1 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGamma_Bin2_JetMinMu;             // ptrel distribution for bin 2 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGamma_Bin3_JetMinMu;             // ptrel distribution for bin 3 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGamma_Bin4_JetMinMu;             // ptrel distribution for bin 4 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGamma_Bin5_JetMinMu;             // ptrel distribution for bin 3 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin1;                // ptrel distribution for bin 1 for jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin2;                // ptrel distribution for bin 2 for jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin3;                // ptrel distribution for bin 3 for jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin4;                // ptrel distribution for bin 4 for jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin5;                // ptrel distribution for bin 3 for jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu;       // ptrel distribution for bin 1 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu;       // ptrel distribution for bin 2 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu;       // ptrel distribution for bin 3 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu;       // ptrel distribution for bin 4 for jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu;       // ptrel distribution for bin 3 for jet xgamma cross section - JetMinMu

  TH1D                *fPtRel_CrossJetXGammaFine_Bin1;                  // ptrel distribution for bin 1 for fine jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGammaFine_Bin2;                  // ptrel distribution for bin 2 for fine jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGammaFine_Bin3;                  // ptrel distribution for bin 3 for fine jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGammaFine_Bin4;                  // ptrel distribution for bin 4 for fine jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGammaFine_Bin5;                  // ptrel distribution for bin 5 for fine jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGammaFine_Bin6;                  // ptrel distribution for bin 6 for fine jet xgamma cross section
  TH1D                *fPtRel_CrossJetXGammaFine_Bin1_JetMinMu;         // ptrel distribution for bin 1 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGammaFine_Bin2_JetMinMu;         // ptrel distribution for bin 2 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGammaFine_Bin3_JetMinMu;         // ptrel distribution for bin 3 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGammaFine_Bin4_JetMinMu;         // ptrel distribution for bin 4 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGammaFine_Bin5_JetMinMu;         // ptrel distribution for bin 5 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_CrossJetXGammaFine_Bin6_JetMinMu;         // ptrel distribution for bin 6 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin1;            // ptrel distribution for bin 1 for fine jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin2;            // ptrel distribution for bin 2 for fine jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin3;            // ptrel distribution for bin 3 for fine jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin4;            // ptrel distribution for bin 4 for fine jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin5;            // ptrel distribution for bin 5 for fine jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin6;            // ptrel distribution for bin 6 for fine jet xgamma cross section
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu;   // ptrel distribution for bin 1 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu;   // ptrel distribution for bin 2 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu;   // ptrel distribution for bin 3 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu;   // ptrel distribution for bin 4 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu;   // ptrel distribution for bin 5 for fine jet xgamma cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu;   // ptrel distribution for bin 6 for fine jet xgamma cross section - JetMinMu

  TH1D                *fPtRel_CrossJetMJets_Bin1;                       // ptrel distribution for bin 1 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin2;                       // ptrel distribution for bin 2 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin3;                       // ptrel distribution for bin 3 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin4;                       // ptrel distribution for bin 4 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin5;                       // ptrel distribution for bin 5 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin6;                       // ptrel distribution for bin 6 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin7;                       // ptrel distribution for bin 7 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin8;                       // ptrel distribution for bin 8 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin9;                       // ptrel distribution for bin 9 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin10;                      // ptrel distribution for bin 10 for dijet mass cross section
  TH1D                *fPtRel_CrossJetMJets_Bin1_JetMinMu;              // ptrel distribution for bin 1 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin2_JetMinMu;              // ptrel distribution for bin 2 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin3_JetMinMu;              // ptrel distribution for bin 3 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin4_JetMinMu;              // ptrel distribution for bin 4 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin5_JetMinMu;              // ptrel distribution for bin 5 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin6_JetMinMu;              // ptrel distribution for bin 6 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin7_JetMinMu;              // ptrel distribution for bin 7 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin8_JetMinMu;              // ptrel distribution for bin 8 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin9_JetMinMu;              // ptrel distribution for bin 9 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_CrossJetMJets_Bin10_JetMinMu;             // ptrel distribution for bin 10 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin1;                 // ptrel distribution for bin 1 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin2;                 // ptrel distribution for bin 2 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin3;                 // ptrel distribution for bin 3 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin4;                 // ptrel distribution for bin 4 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin5;                 // ptrel distribution for bin 5 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin6;                 // ptrel distribution for bin 6 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin7;                 // ptrel distribution for bin 7 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin8;                 // ptrel distribution for bin 8 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin9;                 // ptrel distribution for bin 9 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin10;                // ptrel distribution for bin 10 for dijet mass cross section
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu;        // ptrel distribution for bin 1 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu;        // ptrel distribution for bin 2 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu;        // ptrel distribution for bin 3 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu;        // ptrel distribution for bin 4 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu;        // ptrel distribution for bin 5 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu;        // ptrel distribution for bin 6 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu;        // ptrel distribution for bin 7 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu;        // ptrel distribution for bin 8 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu;        // ptrel distribution for bin 9 for dijet mass cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu;       // ptrel distribution for bin 10 for dijet mass cross section - JetMinMu

  TH1D                *fPtRel_CrossJetDPhiJets_Bin1;                    // ptrel distribution for bin 1 for dijet dphi cross section
  TH1D                *fPtRel_CrossJetDPhiJets_Bin2;                    // ptrel distribution for bin 2 for dijet dphi cross section
  TH1D                *fPtRel_CrossJetDPhiJets_Bin3;                    // ptrel distribution for bin 3 for dijet dphi cross section
  TH1D                *fPtRel_CrossJetDPhiJets_Bin4;                    // ptrel distribution for bin 4 for dijet dphi cross section
  TH1D                *fPtRel_CrossJetDPhiJets_Bin5;                    // ptrel distribution for bin 5 for dijet dphi cross section
  TH1D                *fPtRel_CrossJetDPhiJets_Bin6;                    // ptrel distribution for bin 6 for dijet dphi cross section
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin7;                    // ptrel distribution for bin 7 for dijet dphi cross section
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin8;                    // ptrel distribution for bin 8 for dijet dphi cross section
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin9;                    // ptrel distribution for bin 9 for dijet dphi cross section
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin10;                   // ptrel distribution for bin 10 for dijet dphi cross section
  TH1D                *fPtRel_CrossJetDPhiJets_Bin1_JetMinMu;           // ptrel distribution for bin 1 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJets_Bin2_JetMinMu;           // ptrel distribution for bin 2 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJets_Bin3_JetMinMu;           // ptrel distribution for bin 3 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJets_Bin4_JetMinMu;           // ptrel distribution for bin 4 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJets_Bin5_JetMinMu;           // ptrel distribution for bin 5 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJets_Bin6_JetMinMu;           // ptrel distribution for bin 6 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin7_JetMinMu;           // ptrel distribution for bin 7 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin8_JetMinMu;           // ptrel distribution for bin 8 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin9_JetMinMu;           // ptrel distribution for bin 9 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJets_Bin10_JetMinMu;          // ptrel distribution for bin 10 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin1;              // ptrel distribution for bin 1 for dijet dphi cross section
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin2;              // ptrel distribution for bin 2 for dijet dphi cross section
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin3;              // ptrel distribution for bin 3 for dijet dphi cross section
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin4;              // ptrel distribution for bin 4 for dijet dphi cross section
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin5;              // ptrel distribution for bin 5 for dijet dphi cross section
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin6;              // ptrel distribution for bin 6 for dijet dphi cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin7;              // ptrel distribution for bin 7 for dijet dphi cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin8;              // ptrel distribution for bin 8 for dijet dphi cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin9;              // ptrel distribution for bin 9 for dijet dphi cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin10;             // ptrel distribution for bin 10 for dijet dphi cross section
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu;     // ptrel distribution for bin 1 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu;     // ptrel distribution for bin 2 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu;     // ptrel distribution for bin 3 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu;     // ptrel distribution for bin 4 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu;     // ptrel distribution for bin 5 for dijet dphi cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu;     // ptrel distribution for bin 6 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu;     // ptrel distribution for bin 7 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu;     // ptrel distribution for bin 8 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu;     // ptrel distribution for bin 9 for dijet dphi cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu;    // ptrel distribution for bin 10 for dijet dphi cross section - JetMinMu

  TH1D                *fPtRel_CrossJetDRJets_Bin1;                    // ptrel distribution for bin 1 for dijet dr cross section
  TH1D                *fPtRel_CrossJetDRJets_Bin2;                    // ptrel distribution for bin 2 for dijet dr cross section
  TH1D                *fPtRel_CrossJetDRJets_Bin3;                    // ptrel distribution for bin 3 for dijet dr cross section
  TH1D                *fPtRel_CrossJetDRJets_Bin4;                    // ptrel distribution for bin 4 for dijet dr cross section
  TH1D                *fPtRel_CrossJetDRJets_Bin5;                    // ptrel distribution for bin 5 for dijet dr cross section
//   TH1D                *fPtRel_CrossJetDRJets_Bin6;                    // ptrel distribution for bin 6 for dijet dr cross section
//   TH1D                *fPtRel_CrossJetDRJets_Bin7;                    // ptrel distribution for bin 7 for dijet dr cross section
//   TH1D                *fPtRel_CrossJetDRJets_Bin8;                    // ptrel distribution for bin 8 for dijet dr cross section
  TH1D                *fPtRel_CrossJetDRJets_Bin1_JetMinMu;           // ptrel distribution for bin 1 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDRJets_Bin2_JetMinMu;           // ptrel distribution for bin 2 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDRJets_Bin3_JetMinMu;           // ptrel distribution for bin 3 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDRJets_Bin4_JetMinMu;           // ptrel distribution for bin 4 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_CrossJetDRJets_Bin5_JetMinMu;           // ptrel distribution for bin 5 for dijet dr cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJets_Bin6_JetMinMu;           // ptrel distribution for bin 6 for dijet dr cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJets_Bin7_JetMinMu;           // ptrel distribution for bin 7 for dijet dr cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJets_Bin8_JetMinMu;           // ptrel distribution for bin 8 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin1;              // ptrel distribution for bin 1 for dijet dr cross section
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin2;              // ptrel distribution for bin 2 for dijet dr cross section
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin3;              // ptrel distribution for bin 3 for dijet dr cross section
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin4;              // ptrel distribution for bin 4 for dijet dr cross section
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin5;              // ptrel distribution for bin 5 for dijet dr cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin6;              // ptrel distribution for bin 6 for dijet dr cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin7;              // ptrel distribution for bin 7 for dijet dr cross section
//   TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin8;              // ptrel distribution for bin 8 for dijet dr cross section
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu;     // ptrel distribution for bin 1 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu;     // ptrel distribution for bin 2 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu;     // ptrel distribution for bin 3 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu;     // ptrel distribution for bin 4 for dijet dr cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu;     // ptrel distribution for bin 5 for dijet dr cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu;     // ptrel distribution for bin 6 for dijet dr cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu;     // ptrel distribution for bin 7 for dijet dr cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu;     // ptrel distribution for bin 8 for dijet dr cross section - JetMinMu

  TH1D                *fPtRel_CrossJetPtJets_Bin1;                      // ptrel distribution for bin 1 for dijet p_T cross section
  TH1D                *fPtRel_CrossJetPtJets_Bin2;                      // ptrel distribution for bin 2 for dijet p_T cross section
  TH1D                *fPtRel_CrossJetPtJets_Bin3;                      // ptrel distribution for bin 3 for dijet p_T cross section
  TH1D                *fPtRel_CrossJetPtJets_Bin4;                      // ptrel distribution for bin 4 for dijet p_T cross section
  TH1D                *fPtRel_CrossJetPtJets_Bin5;                      // ptrel distribution for bin 5 for dijet p_T cross section
//   TH1D                *fPtRel_CrossJetPtJets_Bin6;                      // ptrel distribution for bin 6 for dijet p_T cross section
  TH1D                *fPtRel_CrossJetPtJets_Bin1_JetMinMu;             // ptrel distribution for bin 1 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_CrossJetPtJets_Bin2_JetMinMu;             // ptrel distribution for bin 2 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_CrossJetPtJets_Bin3_JetMinMu;             // ptrel distribution for bin 3 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_CrossJetPtJets_Bin4_JetMinMu;             // ptrel distribution for bin 4 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_CrossJetPtJets_Bin5_JetMinMu;             // ptrel distribution for bin 5 for dijet p_T cross section - JetMinMu
//   TH1D                *fPtRel_CrossJetPtJets_Bin6_JetMinMu;             // ptrel distribution for bin 6 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin1;                // ptrel distribution for bin 1 for dijet p_T cross section
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin2;                // ptrel distribution for bin 2 for dijet p_T cross section
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin3;                // ptrel distribution for bin 3 for dijet p_T cross section
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin4;                // ptrel distribution for bin 4 for dijet p_T cross section
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin5;                // ptrel distribution for bin 5 for dijet p_T cross section
//   TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin6;                // ptrel distribution for bin 6 for dijet p_T cross section
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu;       // ptrel distribution for bin 1 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu;       // ptrel distribution for bin 2 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu;       // ptrel distribution for bin 3 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu;       // ptrel distribution for bin 4 for dijet p_T cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu;       // ptrel distribution for bin 5 for dijet p_T cross section - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu;       // ptrel distribution for bin 6 for dijet p_T cross section - JetMinMu

  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin1;                    // ptrel distribution for bin 1 for cos(theta*) cross section
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin2;                    // ptrel distribution for bin 2 for cos(theta*) cross section
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin3;                    // ptrel distribution for bin 3 for cos(theta*) cross section
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin4;                    // ptrel distribution for bin 4 for cos(theta*) cross section
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin5;                    // ptrel distribution for bin 5 for cos(theta*) cross section
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin6;                    // ptrel distribution for bin 6 for cos(theta*) cross section
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin7;                    // ptrel distribution for bin 7 for cos(theta*) cross section */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin8;                    // ptrel distribution for bin 8 for cos(theta*) cross section */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin9;                    // ptrel distribution for bin 9 for cos(theta*) cross section */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin10;                   // ptrel distribution for bin 10 for cos(theta*) cross section */
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu;           // ptrel distribution for bin 1 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu;           // ptrel distribution for bin 2 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu;           // ptrel distribution for bin 3 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu;           // ptrel distribution for bin 4 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu;           // ptrel distribution for bin 5 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu;           // ptrel distribution for bin 6 for cos(theta*) cross section - JetMinMu
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu;           // ptrel distribution for bin 7 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu;           // ptrel distribution for bin 8 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu;           // ptrel distribution for bin 9 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu;          // ptrel distribution for bin 10 for cos(theta*) cross section - JetMinMu */
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1;              // ptrel distribution for bin 1 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2;              // ptrel distribution for bin 2 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3;              // ptrel distribution for bin 3 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4;              // ptrel distribution for bin 4 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5;              // ptrel distribution for bin 5 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6;              // ptrel distribution for bin 6 for cos(theta*) cross section
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7;              // ptrel distribution for bin 7 for cos(theta*) cross section */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8;              // ptrel distribution for bin 8 for cos(theta*) cross section */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9;              // ptrel distribution for bin 9 for cos(theta*) cross section */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10;             // ptrel distribution for bin 10 for cos(theta*) cross section */
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu;     // ptrel distribution for bin 1 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu;     // ptrel distribution for bin 2 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu;     // ptrel distribution for bin 3 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu;     // ptrel distribution for bin 4 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu;     // ptrel distribution for bin 5 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu;     // ptrel distribution for bin 6 for cos(theta*) cross section - JetMinMu
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu;     // ptrel distribution for bin 7 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu;     // ptrel distribution for bin 8 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu;     // ptrel distribution for bin 9 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu;    // ptrel distribution for bin 10 for cos(theta*) cross section - JetMinMu */

  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin1;                    // ptrel distribution for bin 1 for cos(theta*) cross section
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin2;                    // ptrel distribution for bin 2 for cos(theta*) cross section
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin3;                    // ptrel distribution for bin 3 for cos(theta*) cross section
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin4;                    // ptrel distribution for bin 4 for cos(theta*) cross section
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin5;                    // ptrel distribution for bin 5 for cos(theta*) cross section
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin6;                    // ptrel distribution for bin 6 for cos(theta*) cross section
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin7;                    // ptrel distribution for bin 7 for cos(theta*) cross section */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin8;                    // ptrel distribution for bin 8 for cos(theta*) cross section */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin9;                    // ptrel distribution for bin 9 for cos(theta*) cross section */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin10;                   // ptrel distribution for bin 10 for cos(theta*) cross section */
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu;           // ptrel distribution for bin 1 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu;           // ptrel distribution for bin 2 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu;           // ptrel distribution for bin 3 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu;           // ptrel distribution for bin 4 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu;           // ptrel distribution for bin 5 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu;           // ptrel distribution for bin 6 for cos(theta*) cross section - JetMinMu
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu;           // ptrel distribution for bin 7 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu;           // ptrel distribution for bin 8 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu;           // ptrel distribution for bin 9 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu;          // ptrel distribution for bin 10 for cos(theta*) cross section - JetMinMu */
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1;              // ptrel distribution for bin 1 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2;              // ptrel distribution for bin 2 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3;              // ptrel distribution for bin 3 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4;              // ptrel distribution for bin 4 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5;              // ptrel distribution for bin 5 for cos(theta*) cross section
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6;              // ptrel distribution for bin 6 for cos(theta*) cross section
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7;              // ptrel distribution for bin 7 for cos(theta*) cross section */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8;              // ptrel distribution for bin 8 for cos(theta*) cross section */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9;              // ptrel distribution for bin 9 for cos(theta*) cross section */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10;             // ptrel distribution for bin 10 for cos(theta*) cross section */
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu;     // ptrel distribution for bin 1 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu;     // ptrel distribution for bin 2 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu;     // ptrel distribution for bin 3 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu;     // ptrel distribution for bin 4 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu;     // ptrel distribution for bin 5 for cos(theta*) cross section - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu;     // ptrel distribution for bin 6 for cos(theta*) cross section - JetMinMu
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu;     // ptrel distribution for bin 7 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu;     // ptrel distribution for bin 8 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu;     // ptrel distribution for bin 9 for cos(theta*) cross section - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu;    // ptrel distribution for bin 10 for cos(theta*) cross section - JetMinMu */

  TH1D                *fPtRel_CrossJetMJetsHigh_Bin1;                       // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin2;                       // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin3;                       // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin4;                       // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin5;                       // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin6;                       // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin7;                       // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin8;                       // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin9;                       // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin10;                      // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin1_JetMinMu;              // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin2_JetMinMu;              // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin3_JetMinMu;              // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin4_JetMinMu;              // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin5_JetMinMu;              // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin6_JetMinMu;              // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin7_JetMinMu;              // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin8_JetMinMu;              // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin9_JetMinMu;              // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsHigh_Bin10_JetMinMu;             // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin1;                 // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin2;                 // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin3;                 // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin4;                 // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin5;                 // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin6;                 // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin7;                 // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin8;                 // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin9;                 // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin10;                // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu;        // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu;        // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu;        // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu;        // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu;        // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu;        // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu;        // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu;        // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu;        // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu;       // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma >= 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin1;                    // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin2;                    // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin3;                    // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin4;                    // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin5;                    // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin6;                    // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin7;                    // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin8;                    // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin9;                    // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin10;                   // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu;           // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu;           // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu;           // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu;           // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu;           // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu;           // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu;           // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu;           // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu;           // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu;          // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1;              // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2;              // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3;              // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4;              // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5;              // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6;              // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7;              // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8;              // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9;              // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10;             // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu;     // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu;     // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu;     // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu;     // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu;     // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu;     // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu;     // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu;     // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu;     // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu;    // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma >= 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin1;                    // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin2;                    // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin3;                    // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin4;                    // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin5;                    // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDRJetsHigh_Bin6;                    // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDRJetsHigh_Bin7;                    // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetDRJetsHigh_Bin8;                    // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin1_JetMinMu;           // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin2_JetMinMu;           // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin3_JetMinMu;           // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin4_JetMinMu;           // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsHigh_Bin5_JetMinMu;           // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJetsHigh_Bin6_JetMinMu;           // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJetsHigh_Bin7_JetMinMu;           // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJetsHigh_Bin8_JetMinMu;           // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1;              // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2;              // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3;              // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4;              // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5;              // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6;              // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7;              // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8;              // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu;     // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu;     // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu;     // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu;     // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu;     // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu;     // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu;     // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu;     // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma >= 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin1;                      // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin2;                      // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin3;                      // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin4;                      // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin5;                      // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_CrossJetPtJetsHigh_Bin6;                      // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin1_JetMinMu;             // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin2_JetMinMu;             // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin3_JetMinMu;             // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin4_JetMinMu;             // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsHigh_Bin5_JetMinMu;             // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetPtJetsHigh_Bin6_JetMinMu;             // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1;                // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2;                // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3;                // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4;                // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5;                // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma >= 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6;                // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu;       // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu;       // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu;       // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu;       // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu;       // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu;       // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma >= 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin1;                    // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin2;                    // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin3;                    // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin4;                    // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin5;                    // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin6;                    // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin7;                    // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin8;                    // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin9;                    // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin10;                   // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 */
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu;           // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu;           // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu;           // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu;           // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu;           // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu;           // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu;           // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu;           // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu;           // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu;          // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1;              // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2;              // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3;              // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4;              // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5;              // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6;              // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7;              // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8;              // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9;              // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10;             // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 */
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu;     // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu;     // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu;     // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu;     // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu;     // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu;     // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu;     // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu;     // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu;     // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu;    // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */

  //______________________________________

  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1;                    // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2;                    // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3;                    // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4;                    // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5;                    // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6;                    // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7;                    // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8;                    // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9;                    // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10;                   // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 */
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu;           // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu;           // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu;           // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu;           // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu;           // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu;           // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu;           // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu;           // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu;           // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu;          // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1;              // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2;              // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3;              // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4;              // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5;              // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6;              // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7;              // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8;              // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9;              // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10;             // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 */
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu;     // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu;     // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu;     // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu;     // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu;     // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu;     // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu;     // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu;     // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu;     // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu;    // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma >= 0.75 - JetMinMu */

  TH1D                *fPtRel_CrossJetMJetsLow_Bin1;                       // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin2;                       // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin3;                       // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin4;                       // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin5;                       // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin6;                       // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin7;                       // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin8;                       // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin9;                       // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin10;                      // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetMJetsLow_Bin1_JetMinMu;              // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin2_JetMinMu;              // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin3_JetMinMu;              // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin4_JetMinMu;              // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin5_JetMinMu;              // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin6_JetMinMu;              // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin7_JetMinMu;              // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin8_JetMinMu;              // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin9_JetMinMu;              // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetMJetsLow_Bin10_JetMinMu;             // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin1;                 // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin2;                 // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin3;                 // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin4;                 // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin5;                 // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin6;                 // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin7;                 // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin8;                 // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin9;                 // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin10;                // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu;        // ptrel distribution for bin 1 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu;        // ptrel distribution for bin 2 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu;        // ptrel distribution for bin 3 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu;        // ptrel distribution for bin 4 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu;        // ptrel distribution for bin 5 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu;        // ptrel distribution for bin 6 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu;        // ptrel distribution for bin 7 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu;        // ptrel distribution for bin 8 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu;        // ptrel distribution for bin 9 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu;       // ptrel distribution for bin 10 for dijet mass section cross section for x_gamma < 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin1;                    // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin2;                    // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin3;                    // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin4;                    // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin5;                    // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin6;                    // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin7;                    // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin8;                    // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin9;                    // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin10;                   // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu;           // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu;           // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu;           // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu;           // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu;           // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu;           // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu;           // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu;           // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu;           // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu;          // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1;              // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2;              // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3;              // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4;              // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5;              // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6;              // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7;              // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8;              // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9;              // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10;             // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu;     // ptrel distribution for bin 1 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu;     // ptrel distribution for bin 2 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu;     // ptrel distribution for bin 3 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu;     // ptrel distribution for bin 4 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu;     // ptrel distribution for bin 5 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu;     // ptrel distribution for bin 6 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu;     // ptrel distribution for bin 7 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu;     // ptrel distribution for bin 8 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu;     // ptrel distribution for bin 9 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu;    // ptrel distribution for bin 10 for dijet dphi section cross section for x_gamma < 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetDRJetsLow_Bin1;                    // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin2;                    // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin3;                    // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin4;                    // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin5;                    // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDRJetsLow_Bin6;                    // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDRJetsLow_Bin7;                    // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetDRJetsLow_Bin8;                    // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin1_JetMinMu;           // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin2_JetMinMu;           // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin3_JetMinMu;           // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin4_JetMinMu;           // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetDRJetsLow_Bin5_JetMinMu;           // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJetsLow_Bin6_JetMinMu;           // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJetsLow_Bin7_JetMinMu;           // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetDRJetsLow_Bin8_JetMinMu;           // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin1;              // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin2;              // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin3;              // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin4;              // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin5;              // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin6;              // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin7;              // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin8;              // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu;     // ptrel distribution for bin 1 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu;     // ptrel distribution for bin 2 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu;     // ptrel distribution for bin 3 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu;     // ptrel distribution for bin 4 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu;     // ptrel distribution for bin 5 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu;     // ptrel distribution for bin 6 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu;     // ptrel distribution for bin 7 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu;     // ptrel distribution for bin 8 for dijet dr section cross section for x_gamma < 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetPtJetsLow_Bin1;                      // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin2;                      // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin3;                      // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin4;                      // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin5;                      // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_CrossJetPtJetsLow_Bin6;                      // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin1_JetMinMu;             // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin2_JetMinMu;             // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin3_JetMinMu;             // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin4_JetMinMu;             // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetPtJetsLow_Bin5_JetMinMu;             // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_CrossJetPtJetsLow_Bin6_JetMinMu;             // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin1;                // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin2;                // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin3;                // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin4;                // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin5;                // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma < 0.75
//   TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin6;                // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu;       // ptrel distribution for bin 1 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu;       // ptrel distribution for bin 2 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu;       // ptrel distribution for bin 3 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu;       // ptrel distribution for bin 4 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu;       // ptrel distribution for bin 5 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu
//   TH1D                *fPtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu;       // ptrel distribution for bin 6 for dijet p_T section cross section for x_gamma < 0.75 - JetMinMu

  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin1;                    // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin2;                    // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin3;                    // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin4;                    // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin5;                    // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin6;                    // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin7;                    // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin8;                    // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin9;                    // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin10;                   // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 */
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu;           // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu;           // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu;           // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu;           // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu;           // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu;           // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu;           // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu;           // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu;           // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu;          // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1;              // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2;              // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3;              // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4;              // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5;              // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6;              // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7;              // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8;              // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9;              // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10;             // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 */
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu;     // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu;     // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu;     // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu;     // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu;     // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu;     // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu;     // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu;     // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu;     // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu;    // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
  //__________________________________________________________________
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1;                    // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2;                    // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3;                    // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4;                    // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5;                    // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6;                    // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7;                    // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8;                    // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9;                    // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10;                   // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 */
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu;           // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu;           // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu;           // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu;           // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu;           // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu;           // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu;           // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu;           // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu;           // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu;          // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1;              // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2;              // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3;              // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4;              // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5;              // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6;              // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7;              // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8;              // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9;              // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10;             // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 */
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu;     // ptrel distribution for bin 1 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu;     // ptrel distribution for bin 2 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu;     // ptrel distribution for bin 3 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu;     // ptrel distribution for bin 4 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu;     // ptrel distribution for bin 5 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
  TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu;     // ptrel distribution for bin 6 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu;     // ptrel distribution for bin 7 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu;     // ptrel distribution for bin 8 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu;     // ptrel distribution for bin 9 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */
/*   TH1D                *fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu;    // ptrel distribution for bin 10 for cos(theta*) section cross section for x_gamma < 0.75 - JetMinMu */

  TH1D                *fDeltaR_uncut;                            // uncut eta phi distance
  TH1D                *fDeltaPhi_uncut;                          // uncut phi distance
  TH1D                *fDeltaEta_uncut;                          // uncut eta distance
  TH1D                *fDeltaTheta_uncut;                        // uncut theta distance
  TH1D                *fPtTrackOverEtJet_uncut;                     // uncut p_T_track / E_T_jet

  TH1D                *fNperEv;                                  // matches per event
  TH1D                *fPtRel;                                   // pt rel distribution
  TH1D                *fPtRel_JetMinMu;                          // pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_Forward;                           // pt rel distribution
  TH1D                *fPtRel_JetMinMu_Forward;                  // pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_Barrel;                            // pt rel distribution
  TH1D                *fPtRel_JetMinMu_Barrel;                   // pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_Rear;                              // pt rel distribution
  TH1D                *fPtRel_JetMinMu_Rear;                     // pt rel distribution for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_4_8;                             // pt rel distribution with 8 equidistant bins from 0 to 4
  TH1D                *fPtRel_0_4_8_JetMinMu;                    // pt rel distribution with 8 equidistant bins from 0 to 4 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_10;                            // pt rel distribution with 10 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_10_JetMinMu;                   // pt rel distribution with 10 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_20;                            // pt rel distribution with 20 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_20_JetMinMu;                   // pt rel distribution with 20 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_3_6;                             // pt rel distribution with 6 equidistant bins from 0 to 3
  TH1D                *fPtRel_0_3_6_JetMinMu;                    // pt rel distribution with 6 equidistant bins from 0 to 3 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7;                             // pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu;                    // pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_Forward;                     // forward muon pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_Forward;            // forward muon pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_Barrel;                      // barrel muon pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_Barrel;             // barrel muon pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)
  TH1D                *fPtRel_0_5_7_Rear;                        // rear muon pt rel distribution with 7 equidistant bins from 0 to 5
  TH1D                *fPtRel_0_5_7_JetMinMu_Rear;               // rear muon pt rel distribution with 7 equidistant bins from 0 to 5 for ptrel defined as transverse momentum of the muon relative to (jet-muon)

  TH1D                *fDeltaR;                                  // eta phi distance
  TH1D                *fDeltaPhi;                                // phi distance
  TH1D                *fDeltaEta;                                // eta distance
  TH1D                *fDeltaTheta;                              // theta distance
  TH1D                *fPtTrackOverEtJet;                        // p_T_track / E_T_jet

  // control plots
  TH1D                *fControlDeltaR_uncut;                     // uncut control plot for eta phi difference between jet and track
  TH1D                *fControlDeltaPhi_uncut;                   // uncut control plot for phi difference between jet and track
  TH1D                *fControlDeltaEta_uncut;                   // uncut control plot for eta difference between jet and track
  TH1D                *fControlDeltaTheta_uncut;                 // uncut control plot for theta differencebetween jet and track
  TH1D                *fControlPtRel_uncut;                      // uncut control plot for relative transvers momentum of jet and track
  TH1D                *fControlJetPt_uncut;                      // uncut control plot for p_t of jet
  TH1D                *fControlTrackMinusJetPt_uncut;            // uncut control plot for p_t of jet-track
  TH1D                *fControlDeltaR_good;                      // control plot for eta phi difference between jet and track for matchs where jet and track fulfill their cuts
  TH1D                *fControlDeltaPhi_good;                    // control plot for phi difference between jet and track for matchs where jet and track fulfill their cuts
  TH1D                *fControlDeltaEta_good;                    // control plot for eta difference between jet and track for matchs where jet and track fulfill their cuts
  TH1D                *fControlDeltaTheta_good;                  // control plot for theta differencebetween jet and track for matchs where jet and track fulfill their cuts
  TH1D                *fControlPtRel_good;                       // control plot for relative transvers momentum of jet and track for matchs where jet and track fulfill their cuts
  TH1D                *fControlJetPt_good;                       // control plot for p_t of jet for matchs which fulfill all cuts
  TH1D                *fControlTrackMinusJetPt_good;             // control plot for p_t of jet-track for matchs which fulfill all cuts

 public:
  GTJMatchs();
  virtual ~GTJMatchs();

  virtual Bool_t Reset();
  virtual Bool_t Do();
  virtual Bool_t Fill();

  virtual Bool_t CheckTrackAllCuts(GTJMatch *match);
  virtual Bool_t CheckJetCritCuts(GTJMatch *match);
  virtual Bool_t CheckJetPtCut(GTJMatch *match);
  virtual Bool_t CheckTrackMuonKinCuts(GTJMatch *match);
  virtual Bool_t CheckTrackMinusJetPtCut(GTJMatch *match);
  virtual Bool_t CheckAllCuts(GTJMatch *match);

  virtual Bool_t FillHistos();
  virtual Bool_t FillGeneral();

  virtual Bool_t CreateControl();
  virtual Bool_t CreateGeneral();

  virtual Bool_t ObjectsFillHistos();

  virtual Bool_t ObjectsFillGeneral(GTJMatch *match); 
  virtual Bool_t ObjectsFillControl(GTJMatch *match); 
  virtual Bool_t CalcTJCosThetaStar(GTJMatch *match);

  virtual Bool_t GetAllCuts();

  inline virtual Int_t GetNMatchs() { return fNMatchs; }
  virtual GTJMatch* GetMatch(Int_t id);

  virtual TString PrintMessage(TString option);
  virtual Bool_t Print(TString option);

  ClassDef(GTJMatchs,0) // match object for jet-track match
};

R__EXTERN GTJMatchs *gTJMatchs;

#endif
