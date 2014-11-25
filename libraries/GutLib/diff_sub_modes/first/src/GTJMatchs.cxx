//
// GTJMatchs.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 08:22:58 $
// $Revision: 1.18 $
//

#include <GTJMatchs.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTJMatchs)
#endif

  GTJMatchs *gTJMatchs = 0;

//_____________________________________________________________
// GTJMatchs
// Jets Class for everything which is related to JETs and Tracks
//
//
GTJMatchs::GTJMatchs() : GPhysObj() {
  //
  // GTJMatchs default constructor
  if ( gDebug ) cout << endl << "GTJMatchs::GTJMatchs ctor called" << endl << endl;

  // initialize global pointer
  gTJMatchs = this;

  // initialize clonesarray
  fMatchs  = new TClonesArray("GTJMatch",100);
  fNMatchs = 0;

  // init variables
  fTJMatchCut    = kFALSE;

  // init general plots
  fNperEv_uncut                            = 0;
  fDeltaR_uncut                            = 0;
  fDeltaPhi_uncut                          = 0;
  fDeltaEta_uncut                          = 0;
  fDeltaTheta_uncut                        = 0;
  fPtRel_uncut                             = 0;
  fPtRel_JetMinMu_uncut                    = 0;
  fPtRel_Forward_uncut                     = 0;
  fPtRel_JetMinMu_Forward_uncut            = 0;
  fPtRel_Barrel_uncut                      = 0;
  fPtRel_JetMinMu_Barrel_uncut             = 0;
  fPtRel_Rear_uncut                        = 0;
  fPtRel_JetMinMu_Rear_uncut               = 0;
  fPtRel_0_4_8_uncut                       = 0;
  fPtRel_0_4_8_JetMinMu_uncut              = 0;
  fPtRel_0_5_10_uncut                      = 0;
  fPtRel_0_5_10_JetMinMu_uncut             = 0;
  fPtRel_0_5_20_uncut                      = 0;
  fPtRel_0_5_20_JetMinMu_uncut             = 0;
  fPtRel_0_3_6_uncut                       = 0;
  fPtRel_0_3_6_JetMinMu_uncut              = 0;
  fPtRel_0_5_7_uncut                       = 0;
  fPtRel_0_5_7_JetMinMu_uncut              = 0;
  fPtRel_0_5_7_Forward_uncut               = 0;
  fPtRel_0_5_7_JetMinMu_Forward_uncut      = 0;
  fPtRel_0_5_7_Barrel_uncut                = 0;
  fPtRel_0_5_7_JetMinMu_Barrel_uncut       = 0;
  fPtRel_0_5_7_Rear_uncut                  = 0;
  fPtRel_0_5_7_JetMinMu_Rear_uncut         = 0;

  fPtTrackOverEtJet_uncut                  = 0;

  fNperEv                                  = 0;
  fDeltaR                                  = 0;
  fDeltaPhi                                = 0;
  fDeltaEta                                = 0;
  fDeltaTheta                              = 0;
  fPtRel                                   = 0;
  fPtRel_JetMinMu                          = 0;
  fPtRel_Forward                           = 0;
  fPtRel_JetMinMu_Forward                  = 0;
  fPtRel_Barrel                            = 0;
  fPtRel_JetMinMu_Barrel                   = 0;
  fPtRel_Rear                              = 0;
  fPtRel_JetMinMu_Rear                     = 0;
  fPtRel_0_4_8                             = 0;
  fPtRel_0_4_8_JetMinMu                    = 0;
  fPtRel_0_5_10                            = 0;
  fPtRel_0_5_10_JetMinMu                   = 0;
  fPtRel_0_5_20                            = 0;
  fPtRel_0_5_20_JetMinMu                   = 0;
  fPtRel_0_3_6                             = 0;
  fPtRel_0_3_6_JetMinMu                    = 0;
  fPtRel_0_5_7                             = 0;
  fPtRel_0_5_7_JetMinMu                    = 0;
  fPtRel_0_5_7_Forward                     = 0;
  fPtRel_0_5_7_JetMinMu_Forward            = 0;
  fPtRel_0_5_7_Barrel                      = 0;
  fPtRel_0_5_7_JetMinMu_Barrel             = 0;
  fPtRel_0_5_7_Rear                        = 0;
  fPtRel_0_5_7_JetMinMu_Rear               = 0;

  fPtRel_CrossMuonPt_Bin1                       = 0;
  fPtRel_CrossMuonPt_Bin2                       = 0;
  fPtRel_CrossMuonPt_Bin3                       = 0;
  fPtRel_CrossMuonPt_Bin4                       = 0;
  fPtRel_CrossMuonPt_Bin1_JetMinMu              = 0;
  fPtRel_CrossMuonPt_Bin2_JetMinMu              = 0;
  fPtRel_CrossMuonPt_Bin3_JetMinMu              = 0;
  fPtRel_CrossMuonPt_Bin4_JetMinMu              = 0;

  fPtRel_0_5_7_CrossMuonPt_Bin1                 = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin2                 = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin3                 = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin4                 = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu        = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu        = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu        = 0;
  fPtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu        = 0;

  fPtRel_CrossMuonEta_Bin1                      = 0;
  fPtRel_CrossMuonEta_Bin2                      = 0;
  fPtRel_CrossMuonEta_Bin3                      = 0;
  fPtRel_CrossMuonEta_Bin4                      = 0;
  fPtRel_CrossMuonEta_Bin1_JetMinMu             = 0;
  fPtRel_CrossMuonEta_Bin2_JetMinMu             = 0;
  fPtRel_CrossMuonEta_Bin3_JetMinMu             = 0;
  fPtRel_CrossMuonEta_Bin4_JetMinMu             = 0;

  fPtRel_0_5_7_CrossMuonEta_Bin1                = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin2                = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin3                = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin4                = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu       = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu       = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu       = 0;
  fPtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu       = 0;

  fPtRel_CrossMuonPtFine_Bin1                        = 0;
  fPtRel_CrossMuonPtFine_Bin2                        = 0;
  fPtRel_CrossMuonPtFine_Bin3                        = 0;
  fPtRel_CrossMuonPtFine_Bin4                        = 0;
  fPtRel_CrossMuonPtFine_Bin5                        = 0;
  fPtRel_CrossMuonPtFine_Bin6                        = 0;
  fPtRel_CrossMuonPtFine_Bin7                        = 0;
  fPtRel_CrossMuonPtFine_Bin8                        = 0;
  fPtRel_CrossMuonPtFine_Bin9                        = 0;
  fPtRel_CrossMuonPtFine_Bin1_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin2_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin3_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin4_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin5_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin6_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin7_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin8_JetMinMu               = 0;
  fPtRel_CrossMuonPtFine_Bin9_JetMinMu               = 0;

  fPtRel_0_5_7_CrossMuonPtFine_Bin1                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin2                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin3                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin4                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin5                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin6                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin7                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin8                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin9                        = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu               = 0;

  fPtRel_CrossMuonEtaFine_Bin1                       = 0;
  fPtRel_CrossMuonEtaFine_Bin2                       = 0;
  fPtRel_CrossMuonEtaFine_Bin3                       = 0;
  fPtRel_CrossMuonEtaFine_Bin4                       = 0;
  fPtRel_CrossMuonEtaFine_Bin5                       = 0;
  fPtRel_CrossMuonEtaFine_Bin6                       = 0;
  fPtRel_CrossMuonEtaFine_Bin7                       = 0;
  fPtRel_CrossMuonEtaFine_Bin8                       = 0;
  fPtRel_CrossMuonEtaFine_Bin9                       = 0;
  fPtRel_CrossMuonEtaFine_Bin10                      = 0;
  fPtRel_CrossMuonEtaFine_Bin11                      = 0;
  fPtRel_CrossMuonEtaFine_Bin12                      = 0;
  fPtRel_CrossMuonEtaFine_Bin13                      = 0;
  fPtRel_CrossMuonEtaFine_Bin14                      = 0;
  fPtRel_CrossMuonEtaFine_Bin15                      = 0;
  fPtRel_CrossMuonEtaFine_Bin1_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin2_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin3_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin4_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin5_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin6_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin7_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin8_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin9_JetMinMu              = 0;
  fPtRel_CrossMuonEtaFine_Bin10_JetMinMu             = 0;
  fPtRel_CrossMuonEtaFine_Bin11_JetMinMu             = 0;
  fPtRel_CrossMuonEtaFine_Bin12_JetMinMu             = 0;
  fPtRel_CrossMuonEtaFine_Bin13_JetMinMu             = 0;
  fPtRel_CrossMuonEtaFine_Bin14_JetMinMu             = 0;
  fPtRel_CrossMuonEtaFine_Bin15_JetMinMu             = 0;

  fPtRel_0_5_7_CrossMuonEtaFine_Bin1                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin2                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin3                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin4                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin5                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin6                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin7                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin8                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin9                       = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin10                      = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin11                      = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin12                      = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin13                      = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin14                      = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin15                      = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu             = 0;

  fPtRel_CrossMuonFinder_Bin0                       = 0;
  fPtRel_CrossMuonFinder_Bin1                       = 0;
  fPtRel_CrossMuonFinder_Bin2                       = 0;
  fPtRel_CrossMuonFinder_Bin3                       = 0;
  fPtRel_CrossMuonFinder_Bin4                       = 0;
  fPtRel_CrossMuonFinder_Bin5                       = 0;
  fPtRel_CrossMuonFinder_Bin6                       = 0;
  fPtRel_CrossMuonFinder_Bin7                       = 0;
  fPtRel_CrossMuonFinder_Bin8                       = 0;
  fPtRel_CrossMuonFinder_Bin9                       = 0;
  fPtRel_CrossMuonFinder_Bin10                      = 0;
  fPtRel_CrossMuonFinder_Bin11                      = 0;
  fPtRel_CrossMuonFinder_Bin12                      = 0;
  fPtRel_CrossMuonFinder_Bin13                      = 0;
  fPtRel_CrossMuonFinder_Bin14                      = 0;
  fPtRel_CrossMuonFinder_Bin0_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin1_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin2_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin3_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin4_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin5_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin6_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin7_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin8_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin9_JetMinMu              = 0;
  fPtRel_CrossMuonFinder_Bin10_JetMinMu             = 0;
  fPtRel_CrossMuonFinder_Bin11_JetMinMu             = 0;
  fPtRel_CrossMuonFinder_Bin12_JetMinMu             = 0;
  fPtRel_CrossMuonFinder_Bin13_JetMinMu             = 0;
  fPtRel_CrossMuonFinder_Bin14_JetMinMu             = 0;

  fPtRel_0_5_7_CrossMuonFinder_Bin0                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin1                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin2                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin3                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin4                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin5                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin6                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin7                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin8                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin9                       = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin10                      = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin11                      = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin12                      = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin13                      = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin14                      = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu             = 0;

  fPtRel_CrossMuonPtMassimo_Bin1                        = 0;
  fPtRel_CrossMuonPtMassimo_Bin2                        = 0;
  fPtRel_CrossMuonPtMassimo_Bin3                        = 0;
  fPtRel_CrossMuonPtMassimo_Bin1_JetMinMu               = 0;
  fPtRel_CrossMuonPtMassimo_Bin2_JetMinMu               = 0;
  fPtRel_CrossMuonPtMassimo_Bin3_JetMinMu               = 0;

  fPtRel_0_5_7_CrossMuonPtMassimo_Bin1                        = 0;
  fPtRel_0_5_7_CrossMuonPtMassimo_Bin2                        = 0;
  fPtRel_0_5_7_CrossMuonPtMassimo_Bin3                        = 0;
  fPtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu               = 0;

  fPtRel_CrossMuonEtaMassimo_Bin1                       = 0;
  fPtRel_CrossMuonEtaMassimo_Bin2                       = 0;
  fPtRel_CrossMuonEtaMassimo_Bin3                       = 0;
  fPtRel_CrossMuonEtaMassimo_Bin4                       = 0;
  fPtRel_CrossMuonEtaMassimo_Bin1_JetMinMu              = 0;
  fPtRel_CrossMuonEtaMassimo_Bin2_JetMinMu              = 0;
  fPtRel_CrossMuonEtaMassimo_Bin3_JetMinMu              = 0;
  fPtRel_CrossMuonEtaMassimo_Bin4_JetMinMu              = 0;

  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1                       = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2                       = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3                       = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4                       = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu              = 0;

  fPtRel_CrossMuonJetPt_Bin1                       = 0;
  fPtRel_CrossMuonJetPt_Bin2                       = 0;
  fPtRel_CrossMuonJetPt_Bin3                       = 0;
  fPtRel_CrossMuonJetPt_Bin1_JetMinMu              = 0;
  fPtRel_CrossMuonJetPt_Bin2_JetMinMu              = 0;
  fPtRel_CrossMuonJetPt_Bin3_JetMinMu              = 0;

  fPtRel_0_5_7_CrossMuonJetPt_Bin1                 = 0;
  fPtRel_0_5_7_CrossMuonJetPt_Bin2                 = 0;
  fPtRel_0_5_7_CrossMuonJetPt_Bin3                 = 0;
  fPtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu        = 0;
  fPtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu        = 0;
  fPtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu        = 0;

  fPtRel_CrossMuonJetEta_Bin1                      = 0;
  fPtRel_CrossMuonJetEta_Bin2                      = 0;
  fPtRel_CrossMuonJetEta_Bin3                      = 0;
  fPtRel_CrossMuonJetEta_Bin4                      = 0;
  fPtRel_CrossMuonJetEta_Bin1_JetMinMu             = 0;
  fPtRel_CrossMuonJetEta_Bin2_JetMinMu             = 0;
  fPtRel_CrossMuonJetEta_Bin3_JetMinMu             = 0;
  fPtRel_CrossMuonJetEta_Bin4_JetMinMu             = 0;

  fPtRel_0_5_7_CrossMuonJetEta_Bin1                = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin2                = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin3                = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin4                = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu       = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu       = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu       = 0;
  fPtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu       = 0;

  fPtRel_CrossMuonJetPtFine_Bin1                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin2                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin3                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin4                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin5                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin6                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin7                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin8                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin9                        = 0;
  fPtRel_CrossMuonJetPtFine_Bin10                       = 0;
  fPtRel_CrossMuonJetPtFine_Bin11                       = 0;
  fPtRel_CrossMuonJetPtFine_Bin12                       = 0;
  fPtRel_CrossMuonJetPtFine_Bin1_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin2_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin3_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin4_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin5_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin6_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin7_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin8_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin9_JetMinMu               = 0;
  fPtRel_CrossMuonJetPtFine_Bin10_JetMinMu              = 0;
  fPtRel_CrossMuonJetPtFine_Bin11_JetMinMu              = 0;
  fPtRel_CrossMuonJetPtFine_Bin12_JetMinMu              = 0;

  fPtRel_0_5_7_CrossMuonJetPtFine_Bin1                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin2                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin3                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin4                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin5                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin6                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin7                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin8                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin9                        = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin10                       = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin11                       = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin12                       = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu               = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu              = 0;

  fPtRel_CrossMuonJetEtaFine_Bin1                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin2                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin3                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin4                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin5                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin6                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin7                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin8                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin9                       = 0;
  fPtRel_CrossMuonJetEtaFine_Bin10                      = 0;
  fPtRel_CrossMuonJetEtaFine_Bin11                      = 0;
  fPtRel_CrossMuonJetEtaFine_Bin12                      = 0;
  fPtRel_CrossMuonJetEtaFine_Bin13                      = 0;
  fPtRel_CrossMuonJetEtaFine_Bin14                      = 0;
  fPtRel_CrossMuonJetEtaFine_Bin15                      = 0;
  fPtRel_CrossMuonJetEtaFine_Bin1_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin2_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin3_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin4_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin5_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin6_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin7_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin8_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin9_JetMinMu              = 0;
  fPtRel_CrossMuonJetEtaFine_Bin10_JetMinMu             = 0;
  fPtRel_CrossMuonJetEtaFine_Bin11_JetMinMu             = 0;
  fPtRel_CrossMuonJetEtaFine_Bin12_JetMinMu             = 0;
  fPtRel_CrossMuonJetEtaFine_Bin13_JetMinMu             = 0;
  fPtRel_CrossMuonJetEtaFine_Bin14_JetMinMu             = 0;
  fPtRel_CrossMuonJetEtaFine_Bin15_JetMinMu             = 0;

  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9                       = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10                      = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11                      = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12                      = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13                      = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14                      = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15                      = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu              = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu             = 0;
  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu             = 0;

  fPtRel_CrossJetXGamma_Bin1                                  = 0;
  fPtRel_CrossJetXGamma_Bin2                                  = 0;
  fPtRel_CrossJetXGamma_Bin3                                  = 0;
  fPtRel_CrossJetXGamma_Bin4                                  = 0;
  fPtRel_CrossJetXGamma_Bin5                                  = 0;
  fPtRel_CrossJetXGamma_Bin1_JetMinMu                         = 0;
  fPtRel_CrossJetXGamma_Bin2_JetMinMu                         = 0;
  fPtRel_CrossJetXGamma_Bin3_JetMinMu                         = 0;
  fPtRel_CrossJetXGamma_Bin4_JetMinMu                         = 0;
  fPtRel_CrossJetXGamma_Bin5_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin1                            = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin2                            = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin3                            = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin4                            = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin5                            = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu                   = 0;

  fPtRel_CrossJetXGammaFine_Bin1                              = 0;
  fPtRel_CrossJetXGammaFine_Bin2                              = 0;
  fPtRel_CrossJetXGammaFine_Bin3                              = 0;
  fPtRel_CrossJetXGammaFine_Bin4                              = 0;
  fPtRel_CrossJetXGammaFine_Bin5                              = 0;
  fPtRel_CrossJetXGammaFine_Bin6                              = 0;
  fPtRel_CrossJetXGammaFine_Bin1_JetMinMu                     = 0;
  fPtRel_CrossJetXGammaFine_Bin2_JetMinMu                     = 0;
  fPtRel_CrossJetXGammaFine_Bin3_JetMinMu                     = 0;
  fPtRel_CrossJetXGammaFine_Bin4_JetMinMu                     = 0;
  fPtRel_CrossJetXGammaFine_Bin5_JetMinMu                     = 0;
  fPtRel_CrossJetXGammaFine_Bin6_JetMinMu                     = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin1                        = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin2                        = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin3                        = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin4                        = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin5                        = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin6                        = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu               = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu               = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu               = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu               = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu               = 0;
  fPtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu               = 0;

  fPtRel_CrossJetMJets_Bin1                                   = 0;
  fPtRel_CrossJetMJets_Bin2                                   = 0;
  fPtRel_CrossJetMJets_Bin3                                   = 0;
  fPtRel_CrossJetMJets_Bin4                                   = 0;
  fPtRel_CrossJetMJets_Bin5                                   = 0;
  fPtRel_CrossJetMJets_Bin6                                   = 0;
  fPtRel_CrossJetMJets_Bin7                                   = 0;
  fPtRel_CrossJetMJets_Bin8                                   = 0;
  fPtRel_CrossJetMJets_Bin9                                   = 0;
  fPtRel_CrossJetMJets_Bin10                                  = 0;
  fPtRel_CrossJetMJets_Bin1_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin2_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin3_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin4_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin5_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin6_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin7_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin8_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin9_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin10_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin1                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin2                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin3                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin4                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin5                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin6                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin7                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin8                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin9                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin10                            = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu                   = 0;

  fPtRel_CrossJetDPhiJets_Bin1                                = 0;
  fPtRel_CrossJetDPhiJets_Bin2                                = 0;
  fPtRel_CrossJetDPhiJets_Bin3                                = 0;
  fPtRel_CrossJetDPhiJets_Bin4                                = 0;
  fPtRel_CrossJetDPhiJets_Bin5                                = 0;
  fPtRel_CrossJetDPhiJets_Bin6                                = 0;
  //   fPtRel_CrossJetDPhiJets_Bin7                                = 0;
  //   fPtRel_CrossJetDPhiJets_Bin8                                = 0;
  //   fPtRel_CrossJetDPhiJets_Bin9                                = 0;
  //   fPtRel_CrossJetDPhiJets_Bin10                               = 0;
  fPtRel_CrossJetDPhiJets_Bin1_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJets_Bin2_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJets_Bin3_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJets_Bin4_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJets_Bin5_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJets_Bin6_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJets_Bin7_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJets_Bin8_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJets_Bin9_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJets_Bin10_JetMinMu                      = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin1                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin2                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin3                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin4                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin5                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin6                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin7                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin8                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin9                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin10                         = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu                = 0;

  fPtRel_CrossJetDRJets_Bin1                                = 0;
  fPtRel_CrossJetDRJets_Bin2                                = 0;
  fPtRel_CrossJetDRJets_Bin3                                = 0;
  fPtRel_CrossJetDRJets_Bin4                                = 0;
  fPtRel_CrossJetDRJets_Bin5                                = 0;
  //   fPtRel_CrossJetDRJets_Bin6                                = 0;
  //   fPtRel_CrossJetDRJets_Bin7                                = 0;
  //   fPtRel_CrossJetDRJets_Bin8                                = 0;
  fPtRel_CrossJetDRJets_Bin1_JetMinMu                       = 0;
  fPtRel_CrossJetDRJets_Bin2_JetMinMu                       = 0;
  fPtRel_CrossJetDRJets_Bin3_JetMinMu                       = 0;
  fPtRel_CrossJetDRJets_Bin4_JetMinMu                       = 0;
  fPtRel_CrossJetDRJets_Bin5_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJets_Bin6_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJets_Bin7_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJets_Bin8_JetMinMu                       = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin1                          = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin2                          = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin3                          = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin4                          = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin5                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJets_Bin6                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJets_Bin7                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJets_Bin8                          = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu                 = 0;

  fPtRel_CrossJetPtJets_Bin1                                  = 0;
  fPtRel_CrossJetPtJets_Bin2                                  = 0;
  fPtRel_CrossJetPtJets_Bin3                                  = 0;
  fPtRel_CrossJetPtJets_Bin4                                  = 0;
  fPtRel_CrossJetPtJets_Bin5                                  = 0;
  //   fPtRel_CrossJetPtJets_Bin6                                  = 0;
  fPtRel_CrossJetPtJets_Bin1_JetMinMu                         = 0;
  fPtRel_CrossJetPtJets_Bin2_JetMinMu                         = 0;
  fPtRel_CrossJetPtJets_Bin3_JetMinMu                         = 0;
  fPtRel_CrossJetPtJets_Bin4_JetMinMu                         = 0;
  fPtRel_CrossJetPtJets_Bin5_JetMinMu                         = 0;
  //   fPtRel_CrossJetPtJets_Bin6_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin1                            = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin2                            = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin3                            = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin4                            = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin5                            = 0;
  //   fPtRel_0_5_7_CrossJetPtJets_Bin6                            = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu                   = 0;
  //   fPtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu                   = 0;

  fPtRel_CrossJetCosThetaStarJets_Bin1 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin2 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin3 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin4 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin5 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin6 = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin7 = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin8 = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin9 = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin10 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu = 0;

  fPtRel_CrossMJMatchCosThetaStarJets_Bin1 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin2 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin3 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin4 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin5 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin6 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin7 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin8 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin9 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin10 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = 0;

  fPtRel_CrossJetMJetsHigh_Bin1                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin2                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin3                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin4                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin5                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin6                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin7                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin8                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin9                                   = 0;
  fPtRel_CrossJetMJetsHigh_Bin10                                  = 0;
  fPtRel_CrossJetMJetsHigh_Bin1_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin2_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin3_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin4_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin5_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin6_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin7_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin8_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin9_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsHigh_Bin10_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin1                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin2                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin3                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin4                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin5                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin6                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin7                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin8                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin9                             = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin10                            = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu                   = 0;

  fPtRel_CrossJetDPhiJetsHigh_Bin1                                = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin2                                = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin3                                = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin4                                = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin5                                = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin6                                = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin7                                = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin8                                = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin9                                = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin10                               = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu                      = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10                         = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu                = 0;

  fPtRel_CrossJetDRJetsHigh_Bin1                                = 0;
  fPtRel_CrossJetDRJetsHigh_Bin2                                = 0;
  fPtRel_CrossJetDRJetsHigh_Bin3                                = 0;
  fPtRel_CrossJetDRJetsHigh_Bin4                                = 0;
  fPtRel_CrossJetDRJetsHigh_Bin5                                = 0;
  //   fPtRel_CrossJetDRJetsHigh_Bin6                                = 0;
  //   fPtRel_CrossJetDRJetsHigh_Bin7                                = 0;
  //   fPtRel_CrossJetDRJetsHigh_Bin8                                = 0;
  fPtRel_CrossJetDRJetsHigh_Bin1_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsHigh_Bin2_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsHigh_Bin3_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsHigh_Bin4_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsHigh_Bin5_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJetsHigh_Bin6_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJetsHigh_Bin7_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJetsHigh_Bin8_JetMinMu                       = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu                 = 0;

  fPtRel_CrossJetPtJetsHigh_Bin1                                  = 0;
  fPtRel_CrossJetPtJetsHigh_Bin2                                  = 0;
  fPtRel_CrossJetPtJetsHigh_Bin3                                  = 0;
  fPtRel_CrossJetPtJetsHigh_Bin4                                  = 0;
  fPtRel_CrossJetPtJetsHigh_Bin5                                  = 0;
  //   fPtRel_CrossJetPtJetsHigh_Bin6                                  = 0;
  fPtRel_CrossJetPtJetsHigh_Bin1_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsHigh_Bin2_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsHigh_Bin3_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsHigh_Bin4_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsHigh_Bin5_JetMinMu                         = 0;
  //   fPtRel_CrossJetPtJetsHigh_Bin6_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5                            = 0;
  //   fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu                   = 0;
  //   fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu                   = 0;

  fPtRel_CrossJetCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin6 = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin7 = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin8 = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin9 = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = 0;


  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = 0;

  fPtRel_CrossJetMJetsLow_Bin1                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin2                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin3                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin4                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin5                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin6                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin7                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin8                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin9                                   = 0;
  fPtRel_CrossJetMJetsLow_Bin10                                  = 0;
  fPtRel_CrossJetMJetsLow_Bin1_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin2_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin3_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin4_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin5_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin6_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin7_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin8_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin9_JetMinMu                          = 0;
  fPtRel_CrossJetMJetsLow_Bin10_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin1                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin2                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin3                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin4                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin5                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin6                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin7                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin8                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin9                             = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin10                            = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu                   = 0;

  fPtRel_CrossJetDPhiJetsLow_Bin1                                = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin2                                = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin3                                = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin4                                = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin5                                = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin6                                = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin7                                = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin8                                = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin9                                = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin10                               = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu                       = 0;
  fPtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu                       = 0;
  //   fPtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu                      = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5                          = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9                          = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10                         = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu                = 0;

  fPtRel_CrossJetDRJetsLow_Bin1                                = 0;
  fPtRel_CrossJetDRJetsLow_Bin2                                = 0;
  fPtRel_CrossJetDRJetsLow_Bin3                                = 0;
  fPtRel_CrossJetDRJetsLow_Bin4                                = 0;
  fPtRel_CrossJetDRJetsLow_Bin5                                = 0;
  //   fPtRel_CrossJetDRJetsLow_Bin6                                = 0;
  //   fPtRel_CrossJetDRJetsLow_Bin7                                = 0;
  //   fPtRel_CrossJetDRJetsLow_Bin8                                = 0;
  fPtRel_CrossJetDRJetsLow_Bin1_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsLow_Bin2_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsLow_Bin3_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsLow_Bin4_JetMinMu                       = 0;
  fPtRel_CrossJetDRJetsLow_Bin5_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJetsLow_Bin6_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJetsLow_Bin7_JetMinMu                       = 0;
  //   fPtRel_CrossJetDRJetsLow_Bin8_JetMinMu                       = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin1                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin2                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin3                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin4                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin5                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsLow_Bin6                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsLow_Bin7                          = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsLow_Bin8                          = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu                 = 0;
  fPtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu                 = 0;
  //   fPtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu                 = 0;

  fPtRel_CrossJetPtJetsLow_Bin1                                  = 0;
  fPtRel_CrossJetPtJetsLow_Bin2                                  = 0;
  fPtRel_CrossJetPtJetsLow_Bin3                                  = 0;
  fPtRel_CrossJetPtJetsLow_Bin4                                  = 0;
  fPtRel_CrossJetPtJetsLow_Bin5                                  = 0;
  //   fPtRel_CrossJetPtJetsLow_Bin6                                  = 0;
  fPtRel_CrossJetPtJetsLow_Bin1_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsLow_Bin2_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsLow_Bin3_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsLow_Bin4_JetMinMu                         = 0;
  fPtRel_CrossJetPtJetsLow_Bin5_JetMinMu                         = 0;
  //   fPtRel_CrossJetPtJetsLow_Bin6_JetMinMu                         = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin1                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin2                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin3                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin4                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin5                            = 0;
  //   fPtRel_0_5_7_CrossJetPtJetsLow_Bin6                            = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu                   = 0;
  fPtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu                   = 0;
  //   fPtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu                   = 0;

  fPtRel_CrossJetCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin6 = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin7 = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin8 = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin9 = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = 0;
//   fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9 = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = 0;
//   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = 0;

  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9 = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = 0;
//   fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9 = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = 0;
//   fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = 0;

  fPtTrackOverEtJet                        = 0;

  // init control plots
  fControlDeltaR_uncut                     = 0;
  fControlDeltaPhi_uncut                   = 0;
  fControlDeltaEta_uncut                   = 0;
  fControlDeltaTheta_uncut                 = 0;
  fControlPtRel_uncut                      = 0;
  fControlJetPt_uncut                      = 0;
  fControlTrackMinusJetPt_uncut            = 0;
  fControlDeltaR_good                      = 0;
  fControlDeltaPhi_good                    = 0;
  fControlDeltaEta_good                    = 0;
  fControlDeltaTheta_good                  = 0;
  fControlPtRel_good                       = 0;
  fControlJetPt_good                       = 0;
  fControlTrackMinusJetPt_good             = 0;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GTJMatchs::~GTJMatchs() {
  //
  // GTJMatchs default destructor
  if ( gDebug ) cout << endl << "GTJMatchs::~GTJMatchs dtor called" << endl << endl;

  fMatchs->Delete();
  delete fMatchs;

}

//_____________________________________________________________

Bool_t GTJMatchs::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GTJMatchs::Do() called" << endl << endl;

  Fill();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GTJMatchs::Reset() called" << endl << endl;

  // reset cut flags
  fTJMatchCut    = kFALSE;

  // reset clonesarray
  fMatchs->Clear();
  fNMatchs = 0;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::Fill() {
  //
  // fill clonesarray
  if ( gDebug ) cout << endl << "GTJMatchs::Do() called" << endl << endl;

  TClonesArray &matchs = *fMatchs;

  for ( Int_t i = 0; i < gTracks->GetNTracks(); i++ ) {
    GTrack *track = gTracks->GetTrack(i);
    if ( track != 0 ) {
      for ( Int_t j = 0; j < gJets->GetNJets(); j++ ) {
	GJet *jet = gJets->GetJet(j);
	if ( jet != 0 ) {
	  if ( jet->Vect().DeltaR(*track) <= gCards->GetTJMATCHAssociationCone() ) {
	    GTJMatch *match = new(matchs[fNMatchs++]) GTJMatch(track,jet);
	    CheckTrackAllCuts(match);
	    CheckJetCritCuts(match);
	    CheckJetPtCut(match);
	    CheckTrackMuonKinCuts(match);
	    CheckTrackMinusJetPtCut(match);
	    CheckAllCuts(match);
            CalcTJCosThetaStar(match);
	  }
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CheckTrackAllCuts(GTJMatch *match) {
  //
  // check match if track fulfills all track cuts
  if ( gDebug ) cout << endl << "GTJMatchs::CheckTrackAllCuts called" << endl << endl;

  if ( match->GetTrack()->GetAllCuts() ) {
    match->SetTrackAllCuts(kTRUE);
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CheckJetCritCuts(GTJMatch *match) {
  //
  // check match if event fulfills jet criteria
  if ( gDebug ) cout << endl << "GTJMatchs::CheckJetCritCuts called" << endl << endl;
  
  if ( (gJets->GetPtACut() && gJets->GetPtBCut()) || (gJets->GetPtACut() && gCards->GetJETNCut() == 1)) {
    match->SetJetCritCuts(kTRUE);
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CheckJetPtCut(GTJMatch *match) {
  //
  // check match if jet fulfills p_t cut
  if ( gDebug ) cout << endl << "GTJMatchs::CheckJetPtCut called" << endl << endl;

  if ( match->GetJet()->Pt() >= gCards->GetTJMATCHJetPtCut() ) {
    match->SetJetPtCut(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CheckTrackMinusJetPtCut(GTJMatch *match) {
  //
  // check match if match fulfills jet - track p_t cut
  if ( gDebug ) cout << endl << "GTJMatchs::CheckTrackMinusJetPtCut called" << endl << endl;

  if ( match->GetTrackMinusJetPt() >= gCards->GetTJMATCHTrackMinusJetPtCut() ) {
    match->SetTrackMinusJetPtCut(kTRUE);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CheckTrackMuonKinCuts(GTJMatch *match) {
  //
  // check match if match fulfills jet - track p_t cut
  if ( gDebug ) cout << endl << "GTJMatchs::CheckTrackMuonKinCuts called" << endl << endl;

  if ( match->GetTrack()->GetMuonKinType() == kForwardMuonKin ) {
    if ( (match->GetTrack()->Mag() >= gCards->GetFMUONP()) &&  
	 (match->GetTrack()->Pt() >= gCards->GetFMUONPt()) && 
	 (match->GetTrack()->Pt() >= gCards->GetFMUONPTCut1()) &&
	 (match->GetTrack()->Pt() >= gCards->GetFMUONPTCut2()) ) {
      match->SetTrackMuonKinCuts(kTRUE);
    }
  } else if ( match->GetTrack()->GetMuonKinType() == kBarrelMuonKin ) {
    if ( (match->GetTrack()->Mag() >= gCards->GetBMUONP()) &&  
	 (match->GetTrack()->Pt() >= gCards->GetBMUONPt()) && 
	 (match->GetTrack()->Pt() >= gCards->GetBMUONPTCut1()) &&
	 (match->GetTrack()->Pt() >= gCards->GetBMUONPTCut2()) ) {
      match->SetTrackMuonKinCuts(kTRUE);
    }
  } else if ( match->GetTrack()->GetMuonKinType() == kRearMuonKin ) {
    if ( (match->GetTrack()->Mag() >= gCards->GetRMUONP()) &&  
	 (match->GetTrack()->Pt() >= gCards->GetRMUONPt()) && 
	 (match->GetTrack()->Pt() >= gCards->GetRMUONPTCut1()) &&
	 (match->GetTrack()->Pt() >= gCards->GetRMUONPTCut2()) ) {
      match->SetTrackMuonKinCuts(kTRUE);
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CheckAllCuts(GTJMatch *match) {
  //
  // check match if match fulfills all cuts
  if ( gDebug ) cout << endl << "GTJMatchs::CheckAllCuts called" << endl << endl;

  if ( match->GetTrackAllCuts() && 
       match->GetJetCritCuts() && 
       match->GetJetPtCut() && 
       match->GetTrackMinusJetPtCut() && 
       match->GetTrackMuonKinCuts() ) {
    match->SetAllCuts(kTRUE);
    match->SetType(kGoodTrackMatch);
    fTJMatchCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::GetAllCuts() {
  //
  // returns true if event fulfills all track-jet-match cuts
  if ( gDebug ) cout << endl << "GTJMatchs::GetAllCuts() called" << endl << endl;
  if ( gCards->GetTJMATCHNMatchs() <= 0 )
    return kTRUE;
  else if ( fTJMatchCut )
    return kTRUE;
  else
    return kFALSE;
}
//_____________________________________________________________

Bool_t GTJMatchs::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GTJMatchs::CreateControl() called" << endl << endl;
  
  if ( gCards->GetTJMATCHControl() ) {
  
    //     Int_t    ptmubins   = 40;
    //     Double_t ptmulow    = 0.;
    //     Double_t ptmuhigh   = 40.;
    Int_t    drbins     = 25;
    Double_t drlow      = 0.;
    Double_t drhigh     = 2.5;
    Int_t    dphibins   = 150;
    Double_t dphilow    = -1.5;
    Double_t dphihigh   = 1.5;
    Int_t    detabins   = 150;
    Double_t detalow    = -1.5;
    Double_t detahigh   = 1.5;
    Int_t    dthetabins = 150;
    Double_t dthetalow  = -1.5;
    Double_t dthetahigh = 1.5;
    Int_t    ptrelbins  = 50;
    Double_t ptrellow   = 0.;
    Double_t ptrelhigh  = 5.;
    Int_t    ptbins     = 40;
    Double_t ptlow      = 0.0;
    Double_t pthigh     = 20.0;

    fControlDeltaR_uncut = gHistogrammer->TH1DFactory("TJMatch_control","DeltaR_uncut","uncut #Delta R",drbins,drlow,drhigh,"#Delta R","Events");
    fControlDeltaPhi_uncut = gHistogrammer->TH1DFactory("TJMatch_control","DeltaPhi_uncut","uncut #Delta #phi",dphibins,dphilow,dphihigh,"#Delta #phi","Events");
    fControlDeltaEta_uncut = gHistogrammer->TH1DFactory("TJMatch_control","DeltaEta_uncut","uncut #Delta #eta",detabins,detalow,detahigh,"#Delta #eta","Events");
    fControlDeltaTheta_uncut = gHistogrammer->TH1DFactory("TJMatch_control","DeltaTheta_uncut","uncut #Delta #theta",dthetabins,dthetalow,dthetahigh,"#Delta #theta","Events");
    fControlPtRel_uncut = gHistogrammer->TH1DFactory("TJMatch_control","PtRel_uncut","uncut p_{T}^{rel}",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]","Events");
    fControlJetPt_uncut = gHistogrammer->TH1DFactory("TJMatch_control","JetPt_uncut","uncut p_{T}^{jet}",ptbins,ptlow,pthigh,"p_{T}^{jet} [GeV]","Events");
    fControlTrackMinusJetPt_uncut = gHistogrammer->TH1DFactory("TJMatch_control","TrackMinusJetPt_uncut","uncut p_{T}^{#track-jet}",ptbins,ptlow,pthigh,"p_{T}^{#track-jet} [GeV]","Events");
    fControlDeltaR_good = gHistogrammer->TH1DFactory("TJMatch_control","DeltaR_good","#Delta R for good matchs",drbins,drlow,drhigh,"#Delta R","Events");
    fControlDeltaPhi_good = gHistogrammer->TH1DFactory("TJMatch_control","DeltaPhi_good","#Delta #phi for good matchs",dphibins,dphilow,dphihigh,"#Delta #phi","Events");
    fControlDeltaEta_good = gHistogrammer->TH1DFactory("TJMatch_control","DeltaEta_good","#Delta #eta for good matchs",detabins,detalow,detahigh,"#Delta #eta","Events");
    fControlDeltaTheta_good = gHistogrammer->TH1DFactory("TJMatch_control","DeltaTheta_good","#Delta #theta for good matchs",dthetabins,dthetalow,dthetahigh,"#Delta #theta","Events");
    fControlPtRel_good = gHistogrammer->TH1DFactory("TJMatch_control","PtRel_good","p_{T}^{rel} for good matchs",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]","Events");
    fControlJetPt_good = gHistogrammer->TH1DFactory("TJMatch_control","JetPt_good","p_{T}^{jet} for good matchs",ptbins,ptlow,pthigh,"p_{T}^{jet} [GeV]","Events");
    fControlTrackMinusJetPt_good = gHistogrammer->TH1DFactory("TJMatch_control","TrackMinusJetPt_good","p_{T}^{#track-jet} for good matchs",ptbins,ptlow,pthigh,"p_{T}^{#track-jet} [GeV]","Events");

  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GTJMatchs::FillHistos() called" << endl << endl;

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GTJMatchs::ObjectsFillHistos() called" << endl << endl;

  // loop over array
  for ( Int_t i = 0; i < fNMatchs; i++ ) {
    GTJMatch *match = ((GTJMatch*)(fMatchs->At(i)));

    // fill control plots
    ObjectsFillControl(match);

    // fill general plots
    ObjectsFillGeneral(match);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::ObjectsFillControl(GTJMatch *match) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GTJMatchs::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetTJMATCHControl() ) {

    fControlDeltaR_uncut->Fill(match->GetDeltaR());
    fControlDeltaPhi_uncut->Fill(match->GetDeltaPhi());
    fControlDeltaEta_uncut->Fill(match->GetDeltaEta());
    fControlDeltaTheta_uncut->Fill(match->GetDeltaTheta());
    fControlPtRel_uncut->Fill(match->GetPtRel());
    fControlJetPt_uncut->Fill(match->GetJet()->Pt());
    fControlTrackMinusJetPt_uncut->Fill(match->GetTrackMinusJetPt());

    if ( (match->GetType() == kGoodTrackMatch) ) {
      fControlDeltaR_good->Fill(match->GetDeltaR());
      fControlDeltaPhi_good->Fill(match->GetDeltaPhi());
      fControlDeltaEta_good->Fill(match->GetDeltaEta());
      fControlDeltaTheta_good->Fill(match->GetDeltaTheta());
      fControlPtRel_good->Fill(match->GetPtRel());
      if ( match->GetJetPtCut() )
	fControlJetPt_good->Fill(match->GetJet()->Pt());
      if ( match->GetTrackMinusJetPtCut() )
	fControlTrackMinusJetPt_good->Fill(match->GetTrackMinusJetPt());
    }

  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::ObjectsFillGeneral(GTJMatch *match) {
  //
  // fill general histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GTJMatchs::ObjectsFillGeneral() called" << endl << endl;
  
  if ( gCards->GetTJMATCHGeneral() ) {
    
    if ( (match->GetType() == kGoodTrackMatch) ) {
      
      fDeltaR_uncut->Fill(match->GetDeltaR(),gHeader->GetWeight());
      fDeltaEta_uncut->Fill(match->GetDeltaEta(),gHeader->GetWeight());
      fDeltaPhi_uncut->Fill(match->GetDeltaPhi(),gHeader->GetWeight());
      fDeltaTheta_uncut->Fill(match->GetDeltaTheta(),gHeader->GetWeight());
      fPtRel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
      fPtRel_JetMinMu_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      fPtRel_0_4_8_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
      fPtRel_0_4_8_JetMinMu_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      fPtRel_0_5_10_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
      fPtRel_0_5_10_JetMinMu_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      fPtRel_0_5_20_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
      fPtRel_0_5_20_JetMinMu_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      fPtRel_0_3_6_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
      fPtRel_0_3_6_JetMinMu_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      fPtRel_0_5_7_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
      fPtRel_0_5_7_JetMinMu_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());

      if ( match->GetTrack()->GetMuonKinType() == kForwardMuonKin ) {
	fPtRel_0_5_7_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_5_7_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      }
      if ( match->GetTrack()->GetMuonKinType() == kBarrelMuonKin ) {
	fPtRel_0_5_7_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_5_7_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      }
      if ( match->GetTrack()->GetMuonKinType() == kRearMuonKin ) {
	fPtRel_0_5_7_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_5_7_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
      }
      fPtTrackOverEtJet_uncut->Fill(match->GetTrack()->Pt()/match->GetJet()->Et(),gHeader->GetWeight());

      if ( gHeader->GetAllCuts() ) {
	fDeltaR->Fill(match->GetDeltaR(),gHeader->GetWeight());
	fDeltaEta->Fill(match->GetDeltaEta(),gHeader->GetWeight());
	fDeltaPhi->Fill(match->GetDeltaPhi(),gHeader->GetWeight());
	fDeltaTheta->Fill(match->GetDeltaTheta(),gHeader->GetWeight());
	fPtRel->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_0_4_8->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_4_8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_0_5_10->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_5_10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_0_5_20->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_5_20_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_0_3_6->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_3_6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	fPtRel_0_5_7->Fill(match->GetPtRel(),gHeader->GetWeight());
	fPtRel_0_5_7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());

	if ( match->GetTrack()->GetMuonKinType() == kForwardMuonKin ) {
	  fPtRel_0_5_7_Forward->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_JetMinMu_Forward->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_Forward->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_JetMinMu_Forward->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	if ( match->GetTrack()->GetMuonKinType() == kBarrelMuonKin ) {
	  fPtRel_0_5_7_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_JetMinMu_Barrel->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_JetMinMu_Barrel->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	if ( match->GetTrack()->GetMuonKinType() == kRearMuonKin ) {
	  fPtRel_0_5_7_Rear->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_JetMinMu_Rear->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_Rear->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_JetMinMu_Rear->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	fPtTrackOverEtJet->Fill(match->GetTrack()->Pt()/match->GetJet()->Et(),gHeader->GetWeight());

	Int_t    crosspt_nbins = 4;
	Double_t *crosspt_bins = new Double_t[crosspt_nbins+1];
	crosspt_bins[0] = 1.5;
	crosspt_bins[1] = 3.0;
	crosspt_bins[2] = 5.0;
	crosspt_bins[3] = 7.5;
	crosspt_bins[4] = 11.0;
	
	Int_t index = 1;
	if ( (match->GetTrack()->Pt() >= crosspt_bins[index-1]) && (match->GetTrack()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTrack()->Pt() >= crosspt_bins[index-1]) && (match->GetTrack()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTrack()->Pt() >= crosspt_bins[index-1]) && (match->GetTrack()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetTrack()->Pt() >= crosspt_bins[index-1]) && (match->GetTrack()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPt_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	Int_t    crosseta_nbins = 4;
	Double_t *crosseta_bins = new Double_t[crosseta_nbins+1];
	crosseta_bins[0]  = -2.0;
	crosseta_bins[1]  = -0.9;
	crosseta_bins[2]  =  0.0;
	crosseta_bins[3]  =  1.2;
	crosseta_bins[4]  =  2.5;

	index = 1;
	if ( (match->GetTrack()->Eta() >= crosseta_bins[index-1]) && (match->GetTrack()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTrack()->Eta() >= crosseta_bins[index-1]) && (match->GetTrack()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTrack()->Eta() >= crosseta_bins[index-1]) && (match->GetTrack()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetTrack()->Eta() >= crosseta_bins[index-1]) && (match->GetTrack()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

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

	index = 1;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 7;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 8;
	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
// 	index = 9;
// 	if ( (match->GetTrack()->Pt() >= crossptfine_bins[index-1]) && (match->GetTrack()->Pt() <= crossptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}

	Int_t    crossetafine_nbins = 8;
	Double_t *crossetafine_bins = new Double_t[crossetafine_nbins+1];
	crossetafine_bins[0]  = -1.5;
	crossetafine_bins[1]  = -1.0;
	crossetafine_bins[2]  = -0.50;
	crossetafine_bins[3]  = -0.00;
	crossetafine_bins[4]  =  0.50;
	crossetafine_bins[5]  =  1.00;
	crossetafine_bins[6] =   1.50;
	crossetafine_bins[7] =  2.00;
	crossetafine_bins[8] =  2.50;

	index = 1;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 7;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 8;
	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
// 	index = 9;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 10;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 11;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 12;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 13;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 14;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 15;
// 	if ( (match->GetTrack()->Eta() >= crossetafine_bins[index-1]) && (match->GetTrack()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
//--------------------------------
	if ( match->GetTrack()->GetMuonKinType() == kBarrelMuonKin ) {
	  fPtRel_CrossMuonFinder_Bin0->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin0_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin0->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  
	}
	if ( match->GetTrack()->GetMuonKinType() == kRearMuonKin ) {
	  fPtRel_CrossMuonFinder_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonFinder_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	}
	if ( match->GetTrack()->GetMuonKinType() == kForwardMuonKin ) {
 	  fPtRel_CrossMuonFinder_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin13_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonFinder_Bin14_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	}
	     //---------------------------------
	Int_t    crossptmassimo_nbins = 3;
	Double_t *crossptmassimo_bins = new Double_t[crossptmassimo_nbins+1];
	crossptmassimo_bins[0]  =  2.5;
	crossptmassimo_bins[1]  =  4.0;
	crossptmassimo_bins[2]  =  6.0;
	crossptmassimo_bins[3]  = 10.0;

	index = 1;
	if ( (match->GetTrack()->Pt() >= crossptmassimo_bins[index-1]) && (match->GetTrack()->Pt() <= crossptmassimo_bins[index]) ) {
	  fPtRel_CrossMuonPtMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTrack()->Pt() >= crossptmassimo_bins[index-1]) && (match->GetTrack()->Pt() <= crossptmassimo_bins[index]) ) {
	  fPtRel_CrossMuonPtMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTrack()->Pt() >= crossptmassimo_bins[index-1]) && (match->GetTrack()->Pt() <= crossptmassimo_bins[index]) ) {
	  fPtRel_CrossMuonPtMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonPtMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	Int_t    crossetamassimo_nbins = 4;
	Double_t *crossetamassimo_bins = new Double_t[crossetamassimo_nbins+1];
	crossetamassimo_bins[0] = -1.6;
	crossetamassimo_bins[1] = -0.75;
	crossetamassimo_bins[2] = 0.25;
	crossetamassimo_bins[3] = 1.3;
	crossetamassimo_bins[4] = 2.3;

	index = 1;
	if ( (match->GetTrack()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetTrack()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTrack()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetTrack()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTrack()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetTrack()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetTrack()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetTrack()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonEtaMassimo_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	Int_t    crossmuonjetpt_nbins = 3;
	Double_t *crossmuonjetpt_bins = new Double_t[crossmuonjetpt_nbins+1];
	crossmuonjetpt_bins[0] =  6.0;
	crossmuonjetpt_bins[1] = 11.0;;
	crossmuonjetpt_bins[2] = 16.0;
	crossmuonjetpt_bins[3] = 30.0;

	index = 1;
	if ( (match->GetJet()->Pt() >= crossmuonjetpt_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetpt_bins[index]) ) {
	  fPtRel_CrossMuonJetPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetJet()->Pt() >= crossmuonjetpt_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetpt_bins[index]) ) {
	  fPtRel_CrossMuonJetPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetJet()->Pt() >= crossmuonjetpt_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetpt_bins[index]) ) {
	  fPtRel_CrossMuonJetPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	Int_t    crossmuonjeteta_nbins = 4;
	Double_t *crossmuonjeteta_bins = new Double_t[crossmuonjeteta_nbins+1];
	crossmuonjeteta_bins[0] = -1.6;
	crossmuonjeteta_bins[1] = -0.6;
	crossmuonjeteta_bins[2] =  0.4;
	crossmuonjeteta_bins[3] =  1.4;
	crossmuonjeteta_bins[4] =  2.5;

	index = 1;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

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

	index = 1;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 7;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 8;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 9;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 10;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetPtFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
// 	index = 11;
// 	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetPtFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetPtFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 12;
// 	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetPtFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetPtFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}

	Int_t    crossmuonjetetafine_nbins = 8;
	Double_t *crossmuonjetetafine_bins = new Double_t[crossmuonjetetafine_nbins+1];
	crossmuonjetetafine_bins[0]  = -1.5;
	crossmuonjetetafine_bins[1]  = -1.0;
	crossmuonjetetafine_bins[2]  = -0.50;
	crossmuonjetetafine_bins[3]  =  0.0;
	crossmuonjetetafine_bins[4]  =  0.50;
	crossmuonjetetafine_bins[5]  =  1.0;
	crossmuonjetetafine_bins[6] =  1.50;
	crossmuonjetetafine_bins[7] =  2.0;
	crossmuonjetetafine_bins[8] =  2.50;

	index = 1;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 7;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMuonJetEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
 	index = 8;
 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
 	  fPtRel_CrossMuonJetEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_CrossMuonJetEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
 	}
// 	index = 9;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 10;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 11;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 12;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 13;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 14;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 15;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMuonJetEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}

	Int_t    crossjetxgamma_nbins = 5;
	Double_t *crossjetxgamma_bins = new Double_t[crossjetxgamma_nbins+1];
	crossjetxgamma_bins[0] =  0.000;
	crossjetxgamma_bins[1] =  0.375;
	crossjetxgamma_bins[2] =  0.500;
	crossjetxgamma_bins[3] =  0.625;
	crossjetxgamma_bins[4] =  0.750;
	crossjetxgamma_bins[5] =  1.000;

	index = 1;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGamma_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGamma_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGamma_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGamma_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGamma_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	Int_t    crossjetxgammafine_nbins = 6;
	Double_t *crossjetxgammafine_bins = new Double_t[crossjetxgammafine_nbins+1];
	crossjetxgammafine_bins[0] =  0.000;
	crossjetxgammafine_bins[1] =  0.250;
	crossjetxgammafine_bins[2] =  0.375;
	crossjetxgammafine_bins[3] =  0.500;
	crossjetxgammafine_bins[4] =  0.625;
	crossjetxgammafine_bins[5] =  0.750;
	crossjetxgammafine_bins[6] =  1.000;

	index = 1;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGammaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGammaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGammaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGammaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGammaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetXGammaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

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
	crossjetmjets_bins[9]  = 60.0;


	index = 1;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 7;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 8;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 9;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 10;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	Int_t    crossjetdphijets_nbins = 6;
	Double_t *crossjetdphijets_bins = new Double_t[crossjetdphijets_nbins+1];
	crossjetdphijets_bins[0]  = 0*TMath::Pi();
	crossjetdphijets_bins[1]  = 12./24.*TMath::Pi();
	crossjetdphijets_bins[2]  = 16./24.*TMath::Pi();
	crossjetdphijets_bins[3]  = 19./24.*TMath::Pi();
	crossjetdphijets_bins[4]  = 21./24.*TMath::Pi();
	crossjetdphijets_bins[5]  = 23./24.*TMath::Pi();
	crossjetdphijets_bins[6]  = 24./24.*TMath::Pi();
	
	index = 1;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	// 	index = 7;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 8;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 9;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 10;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}

	Int_t    crossjetdrjets_nbins = 5;
	Double_t *crossjetdrjets_bins = new Double_t[crossjetdrjets_nbins+1];
	crossjetdrjets_bins[0]  = 1.0;
	crossjetdrjets_bins[1]  = 2.0;
	crossjetdrjets_bins[2]  = 2.5;
	crossjetdrjets_bins[3]  = 3.0;
	crossjetdrjets_bins[4]  = 3.5;
	crossjetdrjets_bins[5]  = 5.0;

	index = 1;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	// 	index = 6;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDRJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 7;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDRJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 8;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDRJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}

	Int_t    crossjetptjets_nbins = 5;
	Double_t *crossjetptjets_bins = new Double_t[crossjetptjets_nbins+1];
	crossjetptjets_bins[0]  =   0.0;
	crossjetptjets_bins[1]  =   9.0;
	crossjetptjets_bins[2]  =  36.0;
	crossjetptjets_bins[3]  =  81.0;
	crossjetptjets_bins[4]  = 144.0;
	crossjetptjets_bins[5]  = 324.0;

	index = 1;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	// 	index = 6;
	// 	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	// 	  fPtRel_CrossJetPtJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetPtJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetPtJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}

	Int_t    crossjetcosthetastarjets_nbins = 6;
	Double_t *crossjetcosthetastarjets_bins = new Double_t[crossjetcosthetastarjets_nbins+1];
	crossjetcosthetastarjets_bins[0]  = -0.83;
	crossjetcosthetastarjets_bins[1]  = -0.664;
	crossjetcosthetastarjets_bins[2]  = -0.332;
	crossjetcosthetastarjets_bins[3]  =  0.0;
	crossjetcosthetastarjets_bins[4]  =  0.332;
	crossjetcosthetastarjets_bins[5]  =  0.664;
	crossjetcosthetastarjets_bins[6]  =  0.83;

	if(gJets->GetEtaJets()<99 && gJets->GetMJets()>0){
	index = 1;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
// 	index = 7;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 8;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 9;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 10;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
	}

	//--------------------------------------------------------
	if(match->GetTJCosThetaStar_MJets()>0 && match->GetTJCosThetaStar_EtaJets()<99){
	index = 1;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
// 	index = 7;
// 	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 8;
// 	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 9;
// 	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 10;
// 	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
	}

	if ( gJets->GetXGamma_zufo() >= 0.75 ) {

	index = 1;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 7;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 8;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 9;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 10;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetMJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}

	index = 1;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	// 	index = 7;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 8;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 9;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 10;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}

	index = 1;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetDRJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	// 	index = 6;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDRJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 7;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDRJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 8;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDRJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}

	index = 1;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetPtJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	// 	index = 6;
	// 	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	// 	  fPtRel_CrossJetPtJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetPtJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	if(gJets->GetEtaJets()<99 && gJets->GetMJets()>0){
	index = 1;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 3;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 4;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 5;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 6;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
// 	index = 7;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 8;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 9;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
// 	index = 10;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	}
	}
	if(match->GetTJCosThetaStar_MJets()>0 && match->GetTJCosThetaStar_EtaJets()<99){
	index = 1;
	if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	index = 2;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 3;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 6;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
// 	  index = 7;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 8;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 9;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 10;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
	}
	}

	
	if ( gJets->GetXGamma_zufo() < 0.75 ) {
	  
	  index = 1;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 2;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 3;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 6;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 7;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 8;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 9;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 10;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetMJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  
	  index = 1;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 2;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 3;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 6;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  // 	index = 7;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	}
	  // 	index = 8;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	}
	  // 	index = 9;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	// 	index = 10;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}

	  index = 1;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDRJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 2;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDRJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 3;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDRJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDRJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetDRJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  // 	index = 6;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_CrossJetDRJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	}
	  // 	index = 7;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_CrossJetDRJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	}
	  // 	index = 8;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_CrossJetDRJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  // 	}
	  
	  index = 1;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetPtJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 2;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetPtJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	}
	  index = 3;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetPtJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetPtJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetPtJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	// 	index = 6;
	// 	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	// 	  fPtRel_CrossJetPtJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_CrossJetPtJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetPtJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	// 	  fPtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	// 	}
	  if(gJets->GetEtaJets()<99 && gJets->GetMJets()>0){
	  index = 1;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 2;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 3;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 6;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
// 	  index = 7;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 8;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 9;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 10;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
	  }
	if(match->GetTJCosThetaStar_MJets()>0 && match->GetTJCosThetaStar_EtaJets()<99){
	  index = 1;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 2;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight());
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 3;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
	  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 4;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 5;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
	  index = 6;
	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight());
fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
	  }
// 	  index = 7;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 8;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 9;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
// 	  index = 10;
// 	  if ( (match->GetTJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetTJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight());
// fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinTrack(),gHeader->GetWeight());
// 	  }
	}	  
	  
	  
	}
	
      }
    }
    
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::CreateGeneral() {
  //
  // create general plots
  if ( gDebug ) cout << endl << "GTJMatchs::CreateGeneral() called" << endl << endl;
  
  if ( gCards->GetTJMATCHGeneral() ) {

    Int_t ptrel_nbins = 5;
    Double_t ptrel_bins[ptrel_nbins+1];
    ptrel_bins[0]=0.0;
    ptrel_bins[1]=0.75;
    ptrel_bins[2]=1.5;
    ptrel_bins[3]=2.15;
    ptrel_bins[4]=3.0;
    ptrel_bins[5]=5.0;
    Int_t ptrel_nbins_0_4_8 = 8;
    Double_t ptrel_bins_0_4_8[ptrel_nbins_0_4_8+1];
    ptrel_bins_0_4_8[0]=0.;
    ptrel_bins_0_4_8[1]=0.5;
    ptrel_bins_0_4_8[2]=1.0;
    ptrel_bins_0_4_8[3]=1.5;
    ptrel_bins_0_4_8[4]=2.0;
    ptrel_bins_0_4_8[5]=2.5;
    ptrel_bins_0_4_8[6]=3.0;
    ptrel_bins_0_4_8[7]=3.5;
    ptrel_bins_0_4_8[8]=4.0;
    Int_t ptrel_nbins_0_5_10 = 10;
    Double_t ptrel_bins_0_5_10[ptrel_nbins_0_5_10+1];
    ptrel_bins_0_5_10[0]=0.;
    ptrel_bins_0_5_10[1]=0.5;
    ptrel_bins_0_5_10[2]=1.0;
    ptrel_bins_0_5_10[3]=1.5;
    ptrel_bins_0_5_10[4]=2.0;
    ptrel_bins_0_5_10[5]=2.5;
    ptrel_bins_0_5_10[6]=3.0;
    ptrel_bins_0_5_10[7]=3.5;
    ptrel_bins_0_5_10[8]=4.0;
    ptrel_bins_0_5_10[9]=4.5;
    ptrel_bins_0_5_10[10]=5.0;
    Int_t ptrel_nbins_0_5_20 = 20;
    Double_t ptrel_bins_0_5_20[ptrel_nbins_0_5_20+1];
    ptrel_bins_0_5_20[0] =0.00;
    ptrel_bins_0_5_20[1] =0.25;
    ptrel_bins_0_5_20[2] =0.50;
    ptrel_bins_0_5_20[3] =0.75;
    ptrel_bins_0_5_20[4] =1.00;
    ptrel_bins_0_5_20[5] =1.25;
    ptrel_bins_0_5_20[6] =1.50;
    ptrel_bins_0_5_20[7] =1.75;
    ptrel_bins_0_5_20[8] =2.00;
    ptrel_bins_0_5_20[9] =2.25;
    ptrel_bins_0_5_20[10]=2.50;
    ptrel_bins_0_5_20[11]=2.75;
    ptrel_bins_0_5_20[12]=3.00;
    ptrel_bins_0_5_20[13]=3.25;
    ptrel_bins_0_5_20[14]=3.50;
    ptrel_bins_0_5_20[15]=3.75;
    ptrel_bins_0_5_20[16]=4.00;
    ptrel_bins_0_5_20[17]=4.25;
    ptrel_bins_0_5_20[18]=4.50;
    ptrel_bins_0_5_20[19]=4.75;
    ptrel_bins_0_5_20[20]=5.00;
    Int_t ptrel_nbins_0_3_6 = 6;
    Double_t ptrel_bins_0_3_6[ptrel_nbins_0_3_6+1];
    ptrel_bins_0_3_6[0]=0.;
    ptrel_bins_0_3_6[1]=0.5;
    ptrel_bins_0_3_6[2]=1.0;
    ptrel_bins_0_3_6[3]=1.5;
    ptrel_bins_0_3_6[4]=2.0;
    ptrel_bins_0_3_6[5]=2.5;
    ptrel_bins_0_3_6[6]=3.0;
    Int_t ptrel_nbins_0_5_7 = 7;
    Double_t ptrel_bins_0_5_7[ptrel_nbins_0_5_7+1];
    ptrel_bins_0_5_7[0]=0.;
    ptrel_bins_0_5_7[1]=0.7142857;
    ptrel_bins_0_5_7[2]=1.4285714;
    ptrel_bins_0_5_7[3]=2.1428571;
    ptrel_bins_0_5_7[4]=2.8571429;
    ptrel_bins_0_5_7[5]=3.5714286;
    ptrel_bins_0_5_7[6]=4.2857143;
    ptrel_bins_0_5_7[7]=5.0;
    Int_t    pttrackoveretjetbins = 30;
    Double_t pttrackoveretjetlow  = 0.;
    Double_t pttrackoveretjethigh = 1.5;
  
    Int_t    drbins        = 25;
    Double_t drlow         = 0.;
    Double_t drhigh        = 2.5;
    Int_t    dphibins      = 150;
    Double_t dphilow       = -1.5;
    Double_t dphihigh      = 1.5;
    Int_t    detabins      = 150;
    Double_t detalow       = -1.5;
    Double_t detahigh      = 1.5;
    Int_t    dthetabins    = 150;
    Double_t dthetalow     = -1.5;
    Double_t dthetahigh    = 1.5;
    //     Int_t    impact2Dbins  = 20;
    //     Double_t impact2Dlow   = -0.1;
    //     Double_t impact2Dhigh  = 0.1;
    //     Int_t    ptrelcompbins = 300;
    //     Double_t ptrelcomplow  = 0.;
    //     Double_t ptrelcomphigh = 3.;
    //     Int_t    drcompbins    = 300;
    //     Double_t drcomplow     = 0.;
    //     Double_t drcomphigh    = 3.;

    fNperEv_uncut = gHistogrammer->TH1DFactory("TJMatch","NperEv_uncut","uncut n_{match}",10,0.,10.,"n_{match}","Events");
    fDeltaR_uncut = gHistogrammer->TH1DFactory("TJMatch","DeltaR_uncut","uncut #DeltaR = #sqrt{#eta^{2}+#phi^{2}}",drbins,drlow,drhigh,"#DeltaR = #sqrt{#eta^{2}+#phi^{2}}","Events");
    fDeltaEta_uncut = gHistogrammer->TH1DFactory("TJMatch","DeltaEta_uncut","uncut #Delta#eta",detabins,detalow,detahigh,"#Delta#eta","Events");
    fDeltaPhi_uncut = gHistogrammer->TH1DFactory("TJMatch","DeltaPhi_uncut","uncut #Delta#phi",dphibins,dphilow,dphihigh,"#Delta#phi","Events");
    fDeltaTheta_uncut = gHistogrammer->TH1DFactory("TJMatch","DeltaTheta_uncut","uncut #Delta#theta",dthetabins,dthetalow,dthetahigh,"#Delta#theta","Events");
    fPtRel_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_uncut","uncut p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_Forward_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_Forward_uncut","uncut forward p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_Forward_uncut","uncut forward p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_Barrel_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_Barrel_uncut","uncut barrel p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_Barrel_uncut","uncut barrel p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_Rear_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_Rear_uncut","uncut rear p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_Rear_uncut","uncut rear p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_4_8_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_4_8_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_4_8_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_4_8_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_10_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_10_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_10_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_10_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_20_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_20_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_20_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_20_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_3_6_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_3_6_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_3_6_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_3_6_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_0_5_7_Forward_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_Forward_uncut","uncut forward #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_Forward_uncut","uncut forward #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_Barrel_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_Barrel_uncut","uncut barrel #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_Barrel_uncut","uncut barrel #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_Rear_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_Rear_uncut","uncut rear #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_Rear_uncut","uncut rear #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtTrackOverEtJet_uncut = gHistogrammer->TH1DFactory("TJMatch","PtTrackOverEtJet_uncut","uncut p_{T}^{#track}/E_{T}^{jet}",pttrackoveretjetbins,pttrackoveretjetlow,pttrackoveretjethigh,"p_{T}^{#track}/E_{T}^{jet}","Events");

    fNperEv = gHistogrammer->TH1DFactory("TJMatch","NperEv","n_{match}",10,0.,10.,"n_{match}","Events");
    fDeltaR = gHistogrammer->TH1DFactory("TJMatch","DeltaR","#DeltaR = #sqrt{#eta^{2}+#phi^{2}}",drbins,drlow,drhigh,"#DeltaR = #sqrt{#eta^{2}+#phi^{2}}","Events");
    fDeltaEta = gHistogrammer->TH1DFactory("TJMatch","DeltaEta","#Delta#eta",detabins,detalow,detahigh,"#Delta#eta","Events");
    fDeltaPhi = gHistogrammer->TH1DFactory("TJMatch","DeltaPhi","#Delta#phi",dphibins,dphilow,dphihigh,"#Delta#phi","Events");
    fDeltaTheta = gHistogrammer->TH1DFactory("TJMatch","DeltaTheta","#Delta#theta",dthetabins,dthetalow,dthetahigh,"#Delta#theta","Events");
    fPtRel = gHistogrammer->TH1DVarFactory("TJMatch","PtRel","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_Forward = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_Forward","forward p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_Forward","forward p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_Barrel = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_Barrel","barrel p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_Barrel","barrel p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_Rear = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_Rear","rear p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_JetMinMu_Rear","rear p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_4_8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_4_8","p_{T}^{rel}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_4_8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_4_8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_10","p_{T}^{rel}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_20 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_20","p_{T}^{rel}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_20_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_20_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_3_6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_3_6","p_{T}^{rel}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_3_6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_3_6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_0_5_7_Forward = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_Forward","forward #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_Forward","forward #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_Barrel = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_Barrel","barrel #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_Barrel","barrel #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_Rear = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_Rear","rear #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_JetMinMu_Rear","rear #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtTrackOverEtJet = gHistogrammer->TH1DFactory("TJMatch","PtTrackOverEtJet","p_{T}^{#track}/E_{T}^{jet}",pttrackoveretjetbins,pttrackoveretjetlow,pttrackoveretjethigh,"p_{T}^{#track}/E_{T}^{jet}","Events");

    // ptrel fits for muon pt cross section

    fPtRel_CrossMuonPt_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonPt_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonPt_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonPt_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPt_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPt_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for muon eta cross section

    fPtRel_CrossMuonEta_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonEta_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonEta_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonEta_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for fine muon pt cross section

    fPtRel_CrossMuonPtFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for fine muon eta cross section

    fPtRel_CrossMuonEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //-------------
    fPtRel_CrossMuonFinder_Bin0 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin0","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin13 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin13","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin14 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin14","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin0_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin0_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonFinder_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonFinder_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin0 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin0","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin13 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin13","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin14 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin14","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");


    // ptrel fits for massimo muon pt cross section

    fPtRel_CrossMuonPtMassimo_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtMassimo_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtMassimo_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtMassimo_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtMassimo_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtMassimo_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonPtMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonPtMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for massimo muon eta cross section

    fPtRel_CrossMuonEtaMassimo_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonEtaMassimo_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonEtaMassimo_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for muon jet pt cross section

    fPtRel_CrossMuonJetPt_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPt_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPt_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonJetPt_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPt_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPt_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonJetPt_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPt_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPt_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for muon jet eta cross section

    fPtRel_CrossMuonJetEta_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonJetEta_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonJetEta_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossMuonJetEta_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for fine muon jet pt cross section

    fPtRel_CrossMuonJetPtFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetPtFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetPtFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // ptrel fits for fine muon jet eta cross section

    fPtRel_CrossMuonJetEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMuonJetEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMuonJetEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    // dijet cross sections

    fPtRel_CrossJetXGamma_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGamma_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetXGamma_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGamma_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetXGamma_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGamma_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetXGamma_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGamma_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetXGamma_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGamma_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGamma_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetXGammaFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetXGammaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetXGammaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetMJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetDPhiJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetDRJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetPtJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetPtJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetPtJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetPtJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    //______________________________
    fPtRel_CrossMJMatchCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //_____________________________________________________________
    fPtRel_CrossJetMJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetDPhiJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetDRJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetPtJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetPtJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetPtJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    //_______________________________________________
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //____________________________________________________________________
    fPtRel_CrossJetMJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetMJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetMJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetDPhiJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetDRJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetDRJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetDRJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetDRJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetPtJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetPtJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetPtJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_CrossJetPtJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetPtJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetPtJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    //     fPtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

    fPtRel_CrossJetCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
  
  //_________________________________________
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("TJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTJMatchs::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GTJMatchs::FillGeneral() called" << endl << endl;

  if ( gCards->GetTJMATCHGeneral() ) {

    fNperEv_uncut->Fill(fNMatchs,gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {
      fNperEv->Fill(fNMatchs,gHeader->GetWeight());
    }
  }

  return kTRUE;
}

//_____________________________________________________________

TString GTJMatchs::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GTJMatchs::PrintMessage() called" << endl << endl;

  TString dummy = "";

  GTJMatch *match = 0;

  for ( Int_t i = 0; i < fNMatchs; i++ ) {
    match = ((GTJMatch*)(fMatchs->At(i)));
    dummy.Append(match->PrintMessage(option));
  }

  return dummy;
}

//_____________________________________________________________

Bool_t GTJMatchs::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GTJMatchs::Print() called" << endl << endl;

  option.ToUpper();

  GTJMatch *match = 0;

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("TJMATCHS") || option.Contains("ALL") ) {
      gLister->FillOutputList("TJMatchs:\n\n");
      for ( Int_t i = 0; i < fNMatchs; i++ ) {
	match = ((GTJMatch*)(fMatchs->At(i)));
	match->Print(option);
      }
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "TJMatchs:" << endl << endl;;
    for ( Int_t i = 0; i < fNMatchs; i++ ) {
      match = ((GTJMatch*)(fMatchs->At(i)));
      match->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

GTJMatch* GTJMatchs::GetMatch(Int_t index) {
  //
  // return match parameters of the match with index
  if ( gDebug ) cout << endl << "GTJMatchs::GetMatch called" << endl << endl;

  if ( (index < fNMatchs) && (index >= 0) ) {
    return ((GTJMatch*)(fMatchs->At(index)));
  } else {
    TString msg = "GTJMatchs::GetMatch: requested match index: ";
    msg += index;
    msg.Append(" is larger that total number of matchs: ");
    msg += fNMatchs;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}
//__________________________________________________________________
Bool_t	GTJMatchs::CalcTJCosThetaStar(GTJMatch *match){
  if ( gDebug ) cout << endl << "GMJMatchs::CalcTJCosThetaStar called" << endl << endl;

  Double_t jetPt2= 6;
  Double_t jetEta2 = -999;
  Int_t    jetID2 = -999;
  Double_t xgamma = -999;
  Double_t  MJCosThetaStar = -999;
  Double_t mjets = -999;
  Double_t etajets = 999;

  for ( Int_t i = 0; i < gJets->GetNJets(); i++ ) {
    GJet *jet = gJets->GetJet(i);
    if ((jet->GetID()!=match->GetJet()->GetID()) && (jet->Pt()> jetPt2)){
      jetEta2 = jet->Eta();
      jetPt2 = jet->Pt();
      jetID2  = jet->GetID();
      xgamma = (jet->E()-jet->Pz()+match->GetJet()->E() - match->GetJet()->Pz()) / gZufo->GetEmpz_had();
      MJCosThetaStar = TMath::TanH((match->GetJet()->Eta()-jetEta2)/2);
      Double_t mquadrat = (match->GetJet()->E()+jet->E())*(match->GetJet()->E()+jet->E())-(match->GetJet()->Px()+jet->Px())*(match->GetJet()->Px()+jet->Px())-(match->GetJet()->Py()+jet->Py())*(match->GetJet()->Py()+jet->Py())-(match->GetJet()->Pz()+jet->Pz())*(match->GetJet()->Pz()+jet->Pz());
      mjets = TMath::Sqrt(mquadrat);

    }
  }
  etajets =TMath::Abs((match->GetJet()->Eta()+jetEta2)/2);
  match->SetTJCosThetaStar(MJCosThetaStar);
  match->SetSecondJetID(jetID2);
  match->SetTJCosThetaStar_xgamma(xgamma);
  match->SetTJCosThetaStar_EtaJets(etajets);
  match->SetTJCosThetaStar_MJets(mjets);

return kTRUE;

}
