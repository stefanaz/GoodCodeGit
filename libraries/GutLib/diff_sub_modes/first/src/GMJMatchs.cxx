//
// GMJMatchs.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 08:08:08 $
// $Revision: 1.73 $
//

#include <GMJMatchs.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMJMatchs)
#endif

  GMJMatchs *gMJMatchs = 0;

//_____________________________________________________________
// GMJMatchs
// Jets Class for everything which is related to JETs and Muons
//
//
GMJMatchs::GMJMatchs() : GPhysObj() {
  //
  // GMJMatchs default constructor
  if ( gDebug ) cout << endl << "GMJMatchs::GMJMatchs ctor called" << endl << endl;

  // initialize global pointer
  gMJMatchs = this;

  // initialize clonesarray
  fMatchs  = new TClonesArray("GMJMatch",100);
  fNMatchs = 0;

  // init variables
  fMJMatchCut    = kFALSE;
  fSelectedIndex = -99;

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

  fPtRel_0_5_7_MPMATCHMUBAC_uncut                     = 0;
  fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_uncut            = 0;
  fPtRel_0_5_7_MPMATCHMUBAC_Forward_uncut             = 0;
  fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward_uncut    = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_uncut                  = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_uncut         = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_Forward_uncut          = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward_uncut = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_uncut                  = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_uncut         = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_Forward_uncut          = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward_uncut = 0;

  fPtRel_0_5_7_BREMATMUBAC_uncut                      = 0;
  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_uncut             = 0;
  fPtRel_0_5_7_BREMATMUBAC_Barrel_uncut               = 0;
  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel_uncut      = 0;
  fPtRel_0_5_7_BREMATMUBAC_Rear_uncut                 = 0;
  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear_uncut        = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_uncut                   = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_uncut          = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_Barrel_uncut            = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel_uncut   = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_Rear_uncut              = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear_uncut     = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_uncut                   = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_uncut          = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_Barrel_uncut            = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel_uncut   = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_Rear_uncut              = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear_uncut     = 0;

  fPtMuOverEtJet_uncut                     = 0;
  fPtRel_0_4_8_Orange_uncut                = 0;
  fDeltaR_Orange_uncut                     = 0;
  f2DBSImpactVsPtRel_0_5_7_JetMinMu_uncut  = 0;
  f2DBSImpactVsPtRel_0_5_7_uncut           = 0;
  fPtRelSelfVsOrange_uncut                 = 0;
  fDeltaRSelfVsOrange_uncut                = 0;

  fNperEv                                  = 0;
  fDeltaR                                  = 0;
  fDeltaPhi                                = 0;
  fDeltaEta                                = 0;
  fDeltaTheta                              = 0;
  fPtRel                                   = 0;
  fPtRel_lu_is                                   = 0;
  fPtRel_ll_is                                   = 0;
  fPtRel_hu_is                                   = 0;
  fPtRel_hl_is                                   = 0;
  fPtRel_lu_nis                                   = 0;
  fPtRel_ll_nis                                   = 0;
  fPtRel_hu_nis                                   = 0;
  fPtRel_hl_nis                                   = 0;
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
  fPtRel_0_5_7_MuChamber_JetMinMu          = 0;
  fPtRel_0_5_7_MuBac_JetMinMu              = 0;
  fPtRel_0_5_7_Forward                     = 0;
  fPtRel_0_5_7_JetMinMu_Forward            = 0;
  fPtRel_0_5_7_Barrel                      = 0;
  fPtRel_0_5_7_JetMinMu_Barrel             = 0;
  fPtRel_0_5_7_Rear                        = 0;
  fPtRel_0_5_7_JetMinMu_Rear               = 0;

  fPtRel_0_5_7_MPMATCHMUBAC                     = 0;
  fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu            = 0;
  fPtRel_0_5_7_MPMATCHMUBAC_Forward             = 0;
  fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward    = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC                  = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu         = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_Forward          = 0;
  fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC                  = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu         = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_Forward          = 0;
  fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward = 0;

  fPtRel_0_5_7_BREMATMUBAC                      = 0;
  fPtRel_0_5_7_BREMATMUBAC_JetMinMu             = 0;
  fPtRel_0_5_7_BREMATMUBAC_Barrel               = 0;
  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel      = 0;
  fPtRel_0_5_7_BREMATMUBAC_Rear                 = 0;
  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear        = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC                   = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu          = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_Barrel            = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel   = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_Rear              = 0;
  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear     = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC                   = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu          = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_Barrel            = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel   = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_Rear              = 0;
  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear     = 0;

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
  fPtRel_CrossJetMJets_Bin10                                   = 0;
  fPtRel_CrossJetMJets_Bin1_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin2_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin3_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin4_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin5_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin6_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin7_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin8_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin9_JetMinMu                          = 0;
  fPtRel_CrossJetMJets_Bin10_JetMinMu                          = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin1                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin2                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin3                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin4                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin5                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin6                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin7                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin8                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin9                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin10                             = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu                    = 0;
  fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu                    = 0;

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
  fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu                   = 0;

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

  fPtRel_CrossJetCosThetaStarJets_Bin1 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin2 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin3 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin4 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin5 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin6 = 0;
  //  fPtRel_CrossJetCosThetaStarJets_Bin7 = 0;
  // fPtRel_CrossJetCosThetaStarJets_Bin8 = 0;
  // fPtRel_CrossJetCosThetaStarJets_Bin9 = 0;
  // fPtRel_CrossJetCosThetaStarJets_Bin10 = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu = 0;
  //fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu = 0;
  //fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu = 0;
  //fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu = 0;
  //fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6 = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7 = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8 = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9 = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu = 0;
  //fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu = 0;

  fPtRel_CrossJetCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin6 = 0;
  //  fPtRel_CrossJetCosThetaStarJetsHigh_Bin7 = 0;
  // fPtRel_CrossJetCosThetaStarJetsHigh_Bin8 = 0;
  //  fPtRel_CrossJetCosThetaStarJetsHigh_Bin9 = 0;
  // fPtRel_CrossJetCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = 0;

  fPtRel_CrossJetCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin6 = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin7 = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin8 = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin9 = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = 0;
   //fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9 = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = 0;
   //fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = 0;


  fGeneralCrossMJMatchCosThetaStarJets = 0;
  fGeneralCrossMJMatchCosThetaStarJetsRecNTrue = 0;
  fGeneralCrossMJMatchCosThetaStarJetsLow = 0;
  fGeneralCrossMJMatchCosThetaStarJetsLowRecNTrue = 0;
  fGeneralCrossMJMatchCosThetaStarJetsHigh = 0;
  fGeneralCrossMJMatchCosThetaStarJetsHighRecNTrue = 0;

  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = 0;   
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = 0;    
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = 0;   
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = 0;    
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin1 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin2 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin3 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin4 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin5 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin6 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin7 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin8 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin9 = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin10 = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = 0;   
  fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = 0;
   //fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5 = 0; 
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9 = 0; 
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10 = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = 0;    
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = 0;
  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = 0;
   //fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = 0;
  
  fPtMuOverEtJet                           = 0;
  fPtRel_0_4_8_Orange                      = 0;
  fDeltaR_Orange                           = 0;
  f2DBSImpactVsPtRel_0_5_7_JetMinMu        = 0;
  f2DBSImpactVsPtRel_0_5_7                 = 0;
  fPtRelSelfVsOrange                       = 0;
  fDeltaRSelfVsOrange                      = 0;

  // init control plots
  fControlDeltaR_uncut                     = 0;
  fControlDeltaPhi_uncut                   = 0;
  fControlDeltaEta_uncut                   = 0;
  fControlDeltaTheta_uncut                 = 0;
  fControlPtRel_uncut                      = 0;
  fControlJetPt_uncut                      = 0;
  fControlMuMinusJetPt_uncut               = 0;
  fControlDeltaR_good                      = 0;
  fControlDeltaPhi_good                    = 0;
  fControlDeltaEta_good                    = 0;
  fControlDeltaTheta_good                  = 0;
  fControlPtRel_good                       = 0;
  fControlJetPt_good                       = 0;
  fControlMuMinusJetPt_good                = 0;
  fControlDeltaR_chosen                    = 0;
  fControlDeltaPhi_chosen                  = 0;
  fControlDeltaEta_chosen                  = 0;
  fControlDeltaTheta_chosen                = 0;
  fControlPtRel_chosen                     = 0;
  fControlJetPt_chosen                     = 0;
  fControlMuMinusJetPt_chosen              = 0;

  fControlDeltaR6                          = 0;
  fControlDeltaR5                          = 0;
  fControlDeltaR4                          = 0;
  fControlPtRel6                           = 0;
  fControlPtRel5                           = 0;
  fControlPtRel4                           = 0;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GMJMatchs::~GMJMatchs() {
  //
  // GMJMatchs default destructor
  if ( gDebug ) cout << endl << "GMJMatchs::~GMJMatchs dtor called" << endl << endl;

  fMatchs->Delete();
  delete fMatchs;

}

//_____________________________________________________________

Bool_t GMJMatchs::Do() {
  //
  // execute for each event
  if ( gDebug ) cout << endl << "GMJMatchs::Do() called" << endl << endl;

  Fill();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GMJMatchs::Reset() called" << endl << endl;

  // reset cut flags
  fMJMatchCut    = kFALSE;
  fSelectedIndex = -99;

  // reset clonesarray
  fMatchs->Clear();
  fNMatchs = 0;

  fSelectedMatchs = 0;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::Fill() {
  //
  // fill clonesarray
   if ( gDebug ) cout << endl << "GMJMatchs::Do() called" << endl << endl;

  TClonesArray &matchs = *fMatchs;
  for ( Int_t i = 0; i < gMuons->GetNMuons(); i++ ) {
    GMuon *muon = gMuons->GetMuon(i);
    if ( muon->GetJetID() > 0) {
      GJet *jet = gJets->GetJetWithID(muon->GetJetID());
      if ( jet ) {
	GMJMatch *match = new(matchs[fNMatchs++]) GMJMatch(muon,jet);
	//	cout << "match->GetDeltaR() "<<match->GetDeltaR() << endl;
	CheckMuonAllCuts(match);
	//	cout << "match->GetMuonAllCuts() " << match->GetMuonAllCuts() << endl;
	CheckJetCritCuts(match);
	//	cout <<" match->GetJetCritCuts() " <<  match->GetJetCritCuts()  << endl;
	CheckJetPtCut(match);
	//	cout << "match->GetJetPtCut() " << match->GetJetPtCut() << endl;
	CheckMuMinusJetPtCut(match);
	//	cout << "match->GetMuMinusJetPtCut() " << match->GetMuMinusJetPtCut() << endl;
	CheckPtRelCut(match);
	//	cout << "match->GetPtRelCut() " << match->GetPtRelCut() << endl;
	CheckAllCuts(match); 
	CheckHighestPtRel(match,fNMatchs-1);
	CalcMJCosThetaStar(match);
      }
    }
  }
  // decide whether all good matches are taken into account or just the match with highest ptrel
  if ( gCards->GetMJMATCHTakeAllGood() ) {
    SelectAll();
  } else {
    // flag match fulfilling all cuts with highest ptrel
    if ( fSelectedIndex != -99 )
      DetSelectedCand(fSelectedIndex);
  }
  CalcJetCosThetaStar();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CheckMuonAllCuts(GMJMatch *match) {
  //
  // check match if muon fulfills all muon cuts
  if ( gDebug ) cout << endl << "GMJMatchs::CheckMuonAllCuts called" << endl << endl;

  if ( match->GetMuon()->GetAllCuts() )
    match->SetMuonAllCuts(kTRUE);

  return kTRUE;
}
//__________________________________________________________________
Bool_t	GMJMatchs::CalcMJCosThetaStar(GMJMatch *match){
      if ( gDebug ) cout << endl << "GMJMatchs::CalcMJCosThetaStar called" << endl << endl;

  Double_t jetPt2= 6;
  Double_t jetEta2 = -999;
  Int_t    jetID2 = -999;
  Double_t xgamma = -999;
  Double_t EtaJets = 999;
  Double_t MJets   = -999;

  Double_t  MJCosThetaStar = -999;
  if(match->GetJet()->Pt()>=gCards->GetJETPtBCut()){
    for ( Int_t i = 0; i < gJets->GetNJets(); i++ ) {
      GJet *jet = gJets->GetJet(i);
      if ((jet->GetID()!=match->GetJet()->GetID()) && (jet->Pt()> jetPt2)){
	jetEta2 = jet->Eta();
	jetPt2 = jet->Pt();
	jetID2  = jet->GetID();
	xgamma = (jet->E()-jet->Pz()+match->GetJet()->E() - match->GetJet()->Pz()) / gZufo->GetEmpz_had();
	MJCosThetaStar = TMath::TanH((match->GetJet()->Eta()-jetEta2)/2);
	Double_t mquadrat = (match->GetJet()->E()+jet->E())*(match->GetJet()->E()+jet->E())-(match->GetJet()->Px()+jet->Px())*(match->GetJet()->Px()+jet->Px())-(match->GetJet()->Py()+jet->Py())*(match->GetJet()->Py()+jet->Py())-(match->GetJet()->Pz()+jet->Pz())*(match->GetJet()->Pz()+jet->Pz());
	MJets = TMath::Sqrt(mquadrat);
      }
    }
  }
  EtaJets = TMath::Abs((match->GetJet()->Eta()+jetEta2)/2);
  match->GetJet()->SetMJCosThetaStar(MJCosThetaStar);
  match->GetJet()->SetSecondJetID(jetID2);
  match->GetJet()->SetMJCosThetaStar_xgamma(xgamma);
  match->GetJet()->SetMJCosThetaStar_MJets(MJets);
  match->GetJet()->SetMJCosThetaStar_EtaJets(EtaJets);
  
return kTRUE;

}
//_________________________________________________________
Bool_t GMJMatchs::CalcJetCosThetaStar(){
    if ( gDebug ) cout << endl << "GMJMatchs::CalcJetCosThetaStar called" << endl << endl;
  Int_t index1 = gJets->GetHighestJetID();
  Int_t index2 = gJets->GetSecondHighestJetID();

  GJet *jethigh = gJets->GetJetWithID(index1);
  GJet *jetnext = gJets->GetJetWithID(index2);
  Double_t CosThetaStarJets = -999;
  if(jethigh&&jetnext){
    if(jethigh->GetMatched())    CosThetaStarJets = TMath::TanH((jethigh->Eta()-jetnext->Eta())/2);
    else if(jetnext->GetMatched())    CosThetaStarJets = TMath::TanH((jetnext->Eta()-jethigh->Eta())/2);
    gJets->SetCosThetaStarJets(CosThetaStarJets);
  }
  Double_t jet2pt=0;
  for ( Int_t i = 0; i < gJets->GetNJets(); i++ ) {
    GJet *jet = gJets->GetJet(i);
    if(jet->GetMJCosThetaStar()!=-999){
      GJet *jet2 = gJets->GetJetWithID(jet->GetSecondJetID());
      if(jet2) jet2pt = jet2->Pt();
    }
  }
  return kTRUE;
}
//_____________________________________________________________

Bool_t GMJMatchs::CheckJetCritCuts(GMJMatch *match) {
  //
  // check match if event fulfills jet criteria
  if ( gDebug ) cout << endl << "GMJMatchs::CheckJetCritCuts called" << endl << endl;
  
  if ( (gJets->GetPtACut() && gJets->GetPtBCut()) || (gJets->GetPtACut() && gCards->GetJETNCut() == 1))
    match->SetJetCritCuts(kTRUE);
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CheckJetPtCut(GMJMatch *match) {
  //
  // check match if jet fulfills p_t cut
  if ( gDebug ) cout << endl << "GMJMatchs::CheckJetPtCut called" << endl << endl;
  
  if ( gCards->GetJETBreit()) {
    if ( gCards->GetJETCutOnEt() ) {
      if (match->GetJet()->GetEtbreit() >= gCards->GetMJMATCHJetPtCut())
	match->SetJetPtCut(kTRUE);
    }
    else {
      cout << "ERROR in CARDS! JETBREIT without JETCutOnEt!!!" << endl;
      match->SetJetPtCut(kFALSE);
    }
  }
  else {  
    if ( gCards->GetJETCutOnEt() ) {
      if ( match->GetJet()->Et() >= gCards->GetMJMATCHJetPtCut() ){
	match->SetJetPtCut(kTRUE);
      }
    }
    else {
      if ( match->GetJet()->Pt() >= gCards->GetMJMATCHJetPtCut() ){
	match->SetJetPtCut(kTRUE);
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CheckMuMinusJetPtCut(GMJMatch *match) {
  //
  // check match if match fulfills jet - mu p_t cut
  if ( gDebug ) cout << endl << "GMJMatchs::CheckMuMinusJetPtCut called" << endl << endl;

  if ( match->GetMuMinusJetPt() >= gCards->GetMJMATCHMuMinusJetPtCut() )
    match->SetMuMinusJetPtCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CheckPtRelCut(GMJMatch *match) {
  //
  // check match if match fulfills PtRel cut
  if ( gDebug ) cout << endl << "GMJMatchs::CheckPtRelCut called" << endl << endl;

  if ( (match->GetPtRel() >= gCards->GetMJMATCHPtRelLow()) && (match->GetPtRel() <= gCards->GetMJMATCHPtRelHigh()) )
    match->SetPtRelCut(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CheckAllCuts(GMJMatch *match) {
  //
  // check match if match fulfills all cuts
  if ( gDebug ) cout << endl << "GMJMatchs::CheckAllCuts called" << endl << endl;

  if ( match->GetMuonAllCuts() && 
       match->GetJetCritCuts() && 
       match->GetJetPtCut() && 
       match->GetMuMinusJetPtCut() && 
       match->GetPtRelCut() ) {
    match->SetAllCuts(kTRUE);
    match->SetType(kGood);
    fMJMatchCut = kTRUE;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CheckHighestPtRel(GMJMatch *match, Int_t index) {
  //
  // determine index of match with highest p_t_rel
  if ( gDebug ) cout << endl << "GMJMatchs::CheckHighestPtRel called" << endl << endl;

  if ( fSelectedIndex == -99 ) {
    if ( match->GetType() == kGood ) {
      fSelectedIndex = index;
    }
  } else {
    if ( match->GetType() == kGood ) {
      if ( match->GetPtRel() > GetMatch(fSelectedIndex)->GetPtRel() ) {
	fSelectedIndex = index;
      }
    }
  }
      
  return kTRUE;
}

//_____________________________________________________________
 
Bool_t GMJMatchs::DetSelectedCand(Int_t index) {
  //
  // flag match fullfilling all cuts with highest ptrel
  if ( gDebug ) cout << endl << "GMJMatchs::DetSelectedCand called" << endl << endl;

  if ( index != -99 ) {
    GMJMatch *match = GetMatch(index);
    match->SetType(kChosen);
    match->GetJet()->SetMatched(kTRUE);
    //    cout << "match->GetJet()->GetID()"<< match->GetJet()->GetID() << endl;
    match->GetMuon()->SetMatched(kTRUE);
    fSelectedMatchs = 1;
  }

  // select jet in event which is not matched and has highest pt
  // jet has to be first or second
  Bool_t found = kFALSE;
  for ( Int_t i = 0; i < gJets->GetNJets(); ++i ) {
    if ( !found ) {
      GJet *jet = gJets->GetJet(i);
      if ( !jet->GetMatched() && jet->GetSelected() ) {
	jet->SetUnmatched(kTRUE);
	found = kTRUE;
      }
    }
  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::SelectAll() {
  //
  // flag all matchs fullfilling all cuts 
  if ( gDebug ) cout << endl << "GMJMatchs::SelectAll called" << endl << endl;

  GMJMatch *match = 0;
  GMJMatch *match2 = 0;

  for ( Int_t i = 0; i < fNMatchs; i++ ) {
    match = ((GMJMatch*)(fMatchs->At(i)));
    if ( match->GetType() == kGood ) {
      
      // first look for a second chosen match with the same jet, if not, increase counter
      // of selected matches
      Bool_t foundMatchWithSameJet = kFALSE;
      for ( Int_t j = 0; j < fNMatchs; ++j ) {
	match2 = ((GMJMatch*)(fMatchs->At(i)));
	if ( match2->GetType() == kChosen ) {
	  if ( match2->GetJet()->GetID() == match->GetJet()->GetID() ) {
	    foundMatchWithSameJet = kTRUE;
	  }
	}
      }
      if ( !foundMatchWithSameJet ) {
	fSelectedMatchs += 1;
      }

      match->SetType(kChosen);
      match->GetJet()->SetMatched(kTRUE);
      match->GetMuon()->SetMatched(kTRUE);
    }
  }

  // select jet in event which is not matched and has highest pt
  // jet has to be first or second
  Bool_t found = kFALSE;
  for ( Int_t i = 0; i < gJets->GetNJets(); ++i ) {
    if ( !found ) {
      GJet *jet = gJets->GetJet(i);
      if ( !jet->GetMatched() && jet->GetSelected() ) {
	jet->SetUnmatched(kTRUE);
	found = kTRUE;
      }
    }
  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::GetAllCuts() {
  //
  // returns true if event fulfills all muon-jet-match cuts
  if ( gDebug ) cout << endl << "GMJMatchs::GetAllCuts() called" << endl << endl;
  if ( gCards->GetMJMATCHNMatchs() <= 0 )
    return kTRUE;
  else if ( fMJMatchCut )
    return kTRUE;
  else
    return kFALSE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GMJMatchs::CreateControl() called" << endl << endl;
  
  if ( gCards->GetMJMATCHControl() ) {
  
    Int_t    ptmubins   = 40;
    Double_t ptmulow    = 0.;
    Double_t ptmuhigh   = 40.;
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
    Int_t    ptrelbins  = 100;
    Double_t ptrellow   = 0.;
    Double_t ptrelhigh  = 10.;
    Int_t    ptbins     = 40;
    Double_t ptlow      = 0.0;
    Double_t pthigh     = 20.0;

    fControlDeltaR_uncut = gHistogrammer->TH1DFactory("MJMatch_control","DeltaR_uncut","uncut #Delta R",drbins,drlow,drhigh,"#Delta R","Events");
    fControlDeltaPhi_uncut = gHistogrammer->TH1DFactory("MJMatch_control","DeltaPhi_uncut","uncut #Delta #phi",dphibins,dphilow,dphihigh,"#Delta #phi","Events");
    fControlDeltaEta_uncut = gHistogrammer->TH1DFactory("MJMatch_control","DeltaEta_uncut","uncut #Delta #eta",detabins,detalow,detahigh,"#Delta #eta","Events");
    fControlDeltaTheta_uncut = gHistogrammer->TH1DFactory("MJMatch_control","DeltaTheta_uncut","uncut #Delta #theta",dthetabins,dthetalow,dthetahigh,"#Delta #theta","Events");
    fControlPtRel_uncut = gHistogrammer->TH1DFactory("MJMatch_control","PtRel_uncut","uncut p_{T}^{rel}",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]","Events");
    fControlJetPt_uncut = gHistogrammer->TH1DFactory("MJMatch_control","JetPt_uncut","uncut p_{T}^{jet}",ptbins,ptlow,pthigh,"p_{T}^{jet} [GeV]","Events");
    fControlMuMinusJetPt_uncut = gHistogrammer->TH1DFactory("MJMatch_control","MuMinusJetPt_uncut","uncut p_{T}^{#mu-jet}",ptbins,ptlow,pthigh,"p_{T}^{#mu-jet} [GeV]","Events");
    fControlDeltaR_good = gHistogrammer->TH1DFactory("MJMatch_control","DeltaR_good","#Delta R for good matchs",drbins,drlow,drhigh,"#Delta R","Events");
    fControlDeltaPhi_good = gHistogrammer->TH1DFactory("MJMatch_control","DeltaPhi_good","#Delta #phi for good matchs",dphibins,dphilow,dphihigh,"#Delta #phi","Events");
    fControlDeltaEta_good = gHistogrammer->TH1DFactory("MJMatch_control","DeltaEta_good","#Delta #eta for good matchs",detabins,detalow,detahigh,"#Delta #eta","Events");
    fControlDeltaTheta_good = gHistogrammer->TH1DFactory("MJMatch_control","DeltaTheta_good","#Delta #theta for good matchs",dthetabins,dthetalow,dthetahigh,"#Delta #theta","Events");
    fControlPtRel_good = gHistogrammer->TH1DFactory("MJMatch_control","PtRel_good","p_{T}^{rel} for good matchs",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]","Events");
    fControlJetPt_good = gHistogrammer->TH1DFactory("MJMatch_control","JetPt_good","p_{T}^{jet} for good matchs",ptbins,ptlow,pthigh,"p_{T}^{jet} [GeV]","Events");
    fControlMuMinusJetPt_good = gHistogrammer->TH1DFactory("MJMatch_control","MuMinusJetPt_good","p_{T}^{#mu-jet} for good matchs",ptbins,ptlow,pthigh,"p_{T}^{#mu-jet} [GeV]","Events");
    fControlDeltaR_chosen = gHistogrammer->TH1DFactory("MJMatch_control","DeltaR_chosen","#Delta R for chosen match",drbins,drlow,drhigh,"#Delta R","Events");
    fControlDeltaPhi_chosen = gHistogrammer->TH1DFactory("MJMatch_control","DeltaPhi_chosen","#Delta #phi for chosen match",dphibins,dphilow,dphihigh,"#Delta #phi","Events");
    fControlDeltaEta_chosen = gHistogrammer->TH1DFactory("MJMatch_control","DeltaEta_chosen","#Delta #eta for chosen match",detabins,detalow,detahigh,"#Delta #eta","Events");
    fControlDeltaTheta_chosen = gHistogrammer->TH1DFactory("MJMatch_control","DeltaTheta_chosen","#Delta #theta for chosen match",dthetabins,dthetalow,dthetahigh,"#Delta #theta","Events");
    fControlPtRel_chosen = gHistogrammer->TH1DFactory("MJMatch_control","PtRel_chosen","p_{T}^{rel} for chosen match",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]","Events");
    fControlJetPt_chosen = gHistogrammer->TH1DFactory("MJMatch_control","JetPt_chosen","p_{T}^{jet} for chosen match",ptbins,ptlow,pthigh,"p_{T}^{jet} [GeV]","Events");
    fControlMuMinusJetPt_chosen = gHistogrammer->TH1DFactory("MJMatch_control","MuMinusJetPt_chosen","p_{T}^{#mu-jet} for chosen match",ptbins,ptlow,pthigh,"p_{T}^{#mu-jet} [GeV]","Events");

    fControlDeltaR6 = gHistogrammer->TH2DFactory("MJMatch_control","DeltaR6","#Delta R for p_{T}^{#mu} > P_{T}^{min} for #mu_{qual}#geq 6",drbins,drlow,drhigh,ptmubins,ptmulow,ptmuhigh,"#Delta R","p_{T}^{min} [GeV]","events for p_{T}^{#mu} > p_{T}^{min}");
    fControlDeltaR5 = gHistogrammer->TH2DFactory("MJMatch_control","DeltaR5","#Delta R for p_{T}^{#mu} > P_{T}^{min} for #mu_{qual}#geq 5",drbins,drlow,drhigh,ptmubins,ptmulow,ptmuhigh,"#Delta R","p_{T}^{min} [GeV]","events for p_{T}^{#mu} > p_{T}^{min}");
    fControlDeltaR4 = gHistogrammer->TH2DFactory("MJMatch_control","DeltaR4","#Delta R for p_{T}^{#mu} > P_{T}^{min} for #mu_{qual}#geq 4",drbins,drlow,drhigh,ptmubins,ptmulow,ptmuhigh,"#Delta R","p_{T}^{min} [GeV]","events for p_{T}^{#mu} > p_{T}^{min}");
    fControlPtRel6 = gHistogrammer->TH2DFactory("MJMatch_control","PtRel6","p_{T}^{rel} for p_{T}^{#mu} > P_{T}^{min} for #mu_{qual}#geq 6",ptrelbins,ptrellow,ptrelhigh,ptmubins,ptmulow,ptmuhigh,"p_{T}^{rel} [GeV]","p_{T}^{min} [GeV]","events for p_{T}^{#mu} > p_{T}^{min}");
    fControlPtRel5 = gHistogrammer->TH2DFactory("MJMatch_control","PtRel5","p_{T}^{rel} for p_{T}^{#mu} > P_{T}^{min} for #mu_{qual}#geq 5",ptrelbins,ptrellow,ptrelhigh,ptmubins,ptmulow,ptmuhigh,"p_{T}^{rel} [GeV]","p_{T}^{min} [GeV]","events for p_{T}^{#mu} > p_{T}^{min}");
    fControlPtRel4 = gHistogrammer->TH2DFactory("MJMatch_control","PtRel4","p_{T}^{rel} for p_{T}^{#mu} > P_{T}^{min} for #mu_{qual}#geq 4",ptrelbins,ptrellow,ptrelhigh,ptmubins,ptmulow,ptmuhigh,"p_{T}^{rel} [GeV]","p_{T}^{min} [GeV]","events for p_{T}^{#mu} > p_{T}^{min}");
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GMJMatchs::FillHistos() called" << endl << endl;

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMJMatchs::ObjectsFillHistos() called" << endl << endl;

  // loop over array
  for ( Int_t i = 0; i < fNMatchs; i++ ) {
    GMJMatch *match = ((GMJMatch*)(fMatchs->At(i)));

    // fill control plots
    ObjectsFillControl(match);

    // fill general plots
    ObjectsFillGeneral(match);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::ObjectsFillControl(GMJMatch *match) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GMJMatchs::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetMJMATCHControl() ) {

    fControlDeltaR_uncut->Fill(match->GetDeltaR());
    fControlDeltaPhi_uncut->Fill(match->GetDeltaPhi());
    fControlDeltaEta_uncut->Fill(match->GetDeltaEta());
    fControlDeltaTheta_uncut->Fill(match->GetDeltaTheta());
    fControlPtRel_uncut->Fill(match->GetPtRel());
    fControlJetPt_uncut->Fill(match->GetJet()->Pt());
    fControlMuMinusJetPt_uncut->Fill(match->GetMuMinusJetPt());

    if ( (match->GetType() == kGood) || (match->GetType() == kChosen) ) {
      fControlDeltaR_good->Fill(match->GetDeltaR());
      fControlDeltaPhi_good->Fill(match->GetDeltaPhi());
      fControlDeltaEta_good->Fill(match->GetDeltaEta());
      fControlDeltaTheta_good->Fill(match->GetDeltaTheta());
      fControlPtRel_good->Fill(match->GetPtRel());
      if ( match->GetJetPtCut() )
	fControlJetPt_good->Fill(match->GetJet()->Pt());
      if ( match->GetMuMinusJetPtCut() )
	fControlMuMinusJetPt_good->Fill(match->GetMuMinusJetPt());
    }
    if ( match->GetType() == kChosen ) {
      fControlDeltaR_chosen->Fill(match->GetDeltaR());
      fControlDeltaPhi_chosen->Fill(match->GetDeltaPhi());
      fControlDeltaEta_chosen->Fill(match->GetDeltaEta());
      fControlDeltaTheta_chosen->Fill(match->GetDeltaTheta());
      fControlPtRel_chosen->Fill(match->GetPtRel());
      if ( match->GetJetPtCut() )
	fControlJetPt_chosen->Fill(match->GetJet()->Pt());
      if ( match->GetMuMinusJetPtCut() )
	fControlMuMinusJetPt_chosen->Fill(match->GetMuMinusJetPt());
    }


    for ( Int_t i = 1; i <= fControlDeltaR6->GetYaxis()->GetNbins(); ++i ) {
      if ( match->GetMuon()->Pt() >= fControlDeltaR6->GetYaxis()->GetBinLowEdge(i) ) {
	if ( match->GetMuon()->GetQuality() >= 6 ) {
	  fControlDeltaR6->Fill(match->GetDeltaR(),i);
	  fControlPtRel6->Fill(match->GetPtRel(),i);
	}
	if ( match->GetMuon()->GetQuality() >= 5 ) {
	  fControlDeltaR5->Fill(match->GetDeltaR(),i);
	  fControlPtRel5->Fill(match->GetPtRel(),i);
	}
	if ( match->GetMuon()->GetQuality() >= 4 ) {
	  fControlDeltaR4->Fill(match->GetDeltaR(),i);
	  fControlPtRel4->Fill(match->GetPtRel(),i);
	}
      }
    }
    
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::ObjectsFillGeneral(GMJMatch *match) {
  //
  // fill general histograms with data by looping over internal array
    if ( gDebug ) cout << endl << "GMJMatchs::ObjectsFillGeneral() called" << endl << endl;
  
  if ( gCards->GetMJMATCHGeneral() ) {

    if ( (match->GetType() == kChosen) ) {
      GDIMuon * dimuon = 0;
      if( gDIMuons->GetNDIMuons() > 0 ) dimuon = gDIMuons->GetDIMuon(0);

      //      cout<<"run event: "<<gData->Getrunnr()<<" "<<gData->Geteventnr()<<" "<<"Dimuon in GMJMatchs, Pt: "<<dimuon->GetdimuPt()<<endl;

      fDeltaR_uncut->Fill(match->GetDeltaR(),gHeader->GetWeight(match->GetMuon()));
      fDeltaEta_uncut->Fill(match->GetDeltaEta(),gHeader->GetWeight(match->GetMuon()));
      fDeltaPhi_uncut->Fill(match->GetDeltaPhi(),gHeader->GetWeight(match->GetMuon()));
      fDeltaTheta_uncut->Fill(match->GetDeltaTheta(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_4_8_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_4_8_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_5_10_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_5_10_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_5_20_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_5_20_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_3_6_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_3_6_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_5_7_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_5_7_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

      if ( match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	fPtRel_0_5_7_MPMATCHMUBAC_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      }
      if ( match->GetMuon()->GetMPMatch() && !match->GetMuon()->GetMuBac() ) {
	fPtRel_0_5_7_MPMATCHNOTMUBAC_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      }
      if ( !match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	fPtRel_0_5_7_NOTMPMATCHMUBAC_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      }
      if ( match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	fPtRel_0_5_7_BREMATMUBAC_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_BREMATMUBAC_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      }
      if ( match->GetMuon()->GetBremat() && !match->GetMuon()->GetMuBac() ) {
	fPtRel_0_5_7_BREMATNOTMUBAC_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      }
      if ( !match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	fPtRel_0_5_7_NOTBREMATMUBAC_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      }

      if ( match->GetMuon()->GetType() == kForward ) {
	fPtRel_0_5_7_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	if ( match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_MPMATCHMUBAC_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( match->GetMuon()->GetMPMatch() && !match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_MPMATCHNOTMUBAC_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( !match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_NOTMPMATCHMUBAC_Forward_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

      }
      if ( match->GetMuon()->GetType() == kBarrel ) {
	fPtRel_0_5_7_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	if ( match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_BREMATMUBAC_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( match->GetMuon()->GetBremat() && !match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_BREMATNOTMUBAC_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( !match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_NOTBREMATMUBAC_Barrel_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

      }
      if ( match->GetMuon()->GetType() == kRear ) {
	fPtRel_0_5_7_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	if ( match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_BREMATMUBAC_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( match->GetMuon()->GetBremat() && !match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_BREMATNOTMUBAC_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( !match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_NOTBREMATMUBAC_Rear_uncut->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear_uncut->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

      }

      fPtMuOverEtJet_uncut->Fill(match->GetMuon()->Pt()/match->GetJet()->Et(),gHeader->GetWeight(match->GetMuon()));
      fPtRel_0_4_8_Orange_uncut->Fill(match->GetMuon()->GetJetPt(),gHeader->GetWeight(match->GetMuon()));
      fDeltaR_Orange_uncut->Fill(match->GetMuon()->GetJetDr(),gHeader->GetWeight(match->GetMuon()));
      f2DBSImpactVsPtRel_0_5_7_JetMinMu_uncut->Fill(match->GetMuon()->Get2DBeamSpotImpactParameter(),match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
      f2DBSImpactVsPtRel_0_5_7_uncut->Fill(match->GetMuon()->Get2DBeamSpotImpactParameter(),match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
      fPtRelSelfVsOrange_uncut->Fill(match->GetPtRel(),match->GetMuon()->GetJetPt(),gHeader->GetWeight(match->GetMuon()));
      fDeltaRSelfVsOrange_uncut->Fill(match->GetDeltaR(),match->GetMuon()->GetJetDr(),gHeader->GetWeight(match->GetMuon()));

      if ( gHeader->GetAllCuts() ) {
	 if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99) fGeneralCrossMJMatchCosThetaStarJets->Fill(match->GetJet()->GetMJCosThetaStar(),gHeader->GetWeight(match->GetMuon()));
	if ( gCards->GetMC()  && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	  if ( gMCs->GetAllMCCuts() ) {
	    GJet *jet1 = match->GetJet();
	    GJet *jet2 = gJets->GetJetWithID(match->GetJet()->GetSecondJetID());
	    if ( (jet1!=0)&&(jet2!=0) ) {
	      if ( (jet1->GetAssociatedMCJet()!=0)&&(jet2->GetAssociatedMCJet()!=0) ) {
		 if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99) fGeneralCrossMJMatchCosThetaStarJetsRecNTrue->Fill(match->GetJet()->GetMJCosThetaStar(),gHeader->GetWeight(match->GetMuon()));
	      }
	    }
	  }
	}
	fDeltaR->Fill(match->GetDeltaR(),gHeader->GetWeight(match->GetMuon()));
	fDeltaEta->Fill(match->GetDeltaEta(),gHeader->GetWeight(match->GetMuon()));
	fDeltaPhi->Fill(match->GetDeltaPhi(),gHeader->GetWeight(match->GetMuon()));
	fDeltaTheta->Fill(match->GetDeltaTheta(),gHeader->GetWeight(match->GetMuon()));
	fPtRel->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	if( dimuon != 0 ){
	  if( !dimuon->GetSqSumIsolationCut() ) {      
	    //	  if( dimuon->GetIsolationSqSum10() <= gCards->GetDIMUONSqSumIsolationCut() ) {      
	    if ( dimuon->GetInvMass() <= 4 &&  dimuon->GetDifCharge() ) 	fPtRel_lu_is->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    if ( dimuon->GetInvMass() <= 4 && !dimuon->GetDifCharge() ) 	fPtRel_ll_is->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    if ( dimuon->GetInvMass() > 4  &&  dimuon->GetDifCharge() ) 	fPtRel_hu_is->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    if ( dimuon->GetInvMass() > 4  && !dimuon->GetDifCharge() ) 	fPtRel_hl_is->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  }						      
	  else{					      
	    if ( dimuon->GetInvMass() <= 4 &&  dimuon->GetDifCharge() ) 	fPtRel_lu_nis->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    if ( dimuon->GetInvMass() <= 4 && !dimuon->GetDifCharge() ) 	fPtRel_ll_nis->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    if ( dimuon->GetInvMass() > 4  &&  dimuon->GetDifCharge() ) 	fPtRel_hu_nis->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    if ( dimuon->GetInvMass() > 4  && !dimuon->GetDifCharge() ) 	fPtRel_hl_nis->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  }     
	}                                            
	fPtRel_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_4_8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_4_8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_20->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_20_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_3_6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_3_6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_5_7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	if((match->GetMuon()->GetBremat())||(match->GetMuon()->GetMPMatch())||(match->GetMuon()->GetMufo()))
	  fPtRel_0_5_7_MuChamber_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon())); 
	if(match->GetMuon()->GetMuBac()) fPtRel_0_5_7_MuBac_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	if ( match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_MPMATCHMUBAC->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( match->GetMuon()->GetMPMatch() && !match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_MPMATCHNOTMUBAC->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( !match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_NOTMPMATCHMUBAC->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_BREMATMUBAC->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_BREMATMUBAC_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( match->GetMuon()->GetBremat() && !match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_BREMATNOTMUBAC->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( !match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	  fPtRel_0_5_7_NOTBREMATMUBAC->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

	if ( match->GetMuon()->GetType() == kForward ) {
	  fPtRel_0_5_7_Forward->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_JetMinMu_Forward->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_Forward->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_JetMinMu_Forward->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	  if ( match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_MPMATCHMUBAC_Forward->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  if ( match->GetMuon()->GetMPMatch() && !match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_MPMATCHNOTMUBAC_Forward->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  if ( !match->GetMuon()->GetMPMatch() && match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_NOTMPMATCHMUBAC_Forward->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }

	}
	if ( match->GetMuon()->GetType() == kBarrel ) {
	  fPtRel_0_5_7_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_JetMinMu_Barrel->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_JetMinMu_Barrel->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	  if ( match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_BREMATMUBAC_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  if ( match->GetMuon()->GetBremat() && !match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_BREMATNOTMUBAC_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  if ( !match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_NOTBREMATMUBAC_Barrel->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }

	}
	if ( match->GetMuon()->GetType() == kRear ) {
	  fPtRel_0_5_7_Rear->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_JetMinMu_Rear->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_Rear->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_JetMinMu_Rear->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));

	  if ( match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_BREMATMUBAC_Rear->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  if ( match->GetMuon()->GetBremat() && !match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_BREMATNOTMUBAC_Rear->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  if ( !match->GetMuon()->GetBremat() && match->GetMuon()->GetMuBac() ) {
	    fPtRel_0_5_7_NOTBREMATMUBAC_Rear->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }

	}
	
	Int_t    crosspt_nbins = 4;
	Double_t *crosspt_bins = new Double_t[crosspt_nbins+1];
	crosspt_bins[0] = 1.5;
	crosspt_bins[1] = 3.0;
	crosspt_bins[2] = 5.0;
	crosspt_bins[3] = 7.5;
	crosspt_bins[4] = 11.0;
	
	Int_t index = 1;
	if ( (match->GetMuon()->Pt() >= crosspt_bins[index-1]) && (match->GetMuon()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetMuon()->Pt() >= crosspt_bins[index-1]) && (match->GetMuon()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetMuon()->Pt() >= crosspt_bins[index-1]) && (match->GetMuon()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetMuon()->Pt() >= crosspt_bins[index-1]) && (match->GetMuon()->Pt() <= crosspt_bins[index]) ) {
	  fPtRel_CrossMuonPt_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPt_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

	Int_t    crosseta_nbins = 4;
	Double_t *crosseta_bins = new Double_t[crosseta_nbins+1];
	crosseta_bins[0]  = -2.0;
	crosseta_bins[1]  = -0.9;
	crosseta_bins[2]  =  0.0;
	crosseta_bins[3]  =  1.2;
	crosseta_bins[4]  =  2.5;

	index = 1;
	if ( (match->GetMuon()->Eta() >= crosseta_bins[index-1]) && (match->GetMuon()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetMuon()->Eta() >= crosseta_bins[index-1]) && (match->GetMuon()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetMuon()->Eta() >= crosseta_bins[index-1]) && (match->GetMuon()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetMuon()->Eta() >= crosseta_bins[index-1]) && (match->GetMuon()->Eta() <= crosseta_bins[index]) ) {
	  fPtRel_CrossMuonEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 7;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 8;
	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
	  fPtRel_CrossMuonPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
// 	index = 9;
// 	if ( (match->GetMuon()->Pt() >= crossptfine_bins[index-1]) && (match->GetMuon()->Pt() <= crossptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}

	Int_t    crossetafine_nbins = 8;
	Double_t *crossetafine_bins = new Double_t[crossetafine_nbins+1];
	crossetafine_bins[0]  = -1.5;
	crossetafine_bins[1]  = -1.0;
	crossetafine_bins[2]  = -0.50;
	crossetafine_bins[3]  =  0.00;
	crossetafine_bins[4]  =  0.50;
	crossetafine_bins[5]  =  1.00;
	crossetafine_bins[6]  =  1.50;
	crossetafine_bins[7]  =  2.0;
	crossetafine_bins[8]  =  2.50;

	index = 1;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 7;
	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
	  fPtRel_CrossMuonEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
 	index = 8;
 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
 	  fPtRel_CrossMuonEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
// 	index = 9;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 10;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 11;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 12;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 13;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 14;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 15;
// 	if ( (match->GetMuon()->Eta() >= crossetafine_bins[index-1]) && (match->GetMuon()->Eta() <= crossetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}

//__________________

	
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==0){
	  fPtRel_CrossMuonFinder_Bin0->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin0_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin0->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==1){
	  fPtRel_CrossMuonFinder_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==2){
	  fPtRel_CrossMuonFinder_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==3){
	  fPtRel_CrossMuonFinder_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==4){
	  fPtRel_CrossMuonFinder_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==5){
	  fPtRel_CrossMuonFinder_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==6){
	  fPtRel_CrossMuonFinder_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==7){
	  fPtRel_CrossMuonFinder_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonFinder_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==8){
 	  fPtRel_CrossMuonFinder_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==9){
 	  fPtRel_CrossMuonFinder_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==10){
 	  fPtRel_CrossMuonFinder_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==11){
 	  fPtRel_CrossMuonFinder_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==12){
 	  fPtRel_CrossMuonFinder_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==13){
 	  fPtRel_CrossMuonFinder_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin13_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
	if ( gMuons->GetSpecialFinderBin(match->GetMuon())==14){
 	  fPtRel_CrossMuonFinder_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonFinder_Bin14_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}

//_______________________
	Int_t    crossptmassimo_nbins = 3;
	Double_t *crossptmassimo_bins = new Double_t[crossptmassimo_nbins+1];
	crossptmassimo_bins[0]  =  2.5;
	crossptmassimo_bins[1]  =  4.0;
	crossptmassimo_bins[2]  =  6.0;
	crossptmassimo_bins[3]  = 10.0;
	index = 1;
	if ( (match->GetMuon()->Pt() >= crossptmassimo_bins[index-1]) && (match->GetMuon()->Pt() <= crossptmassimo_bins[index]) ) {
	  fPtRel_CrossMuonPtMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetMuon()->Pt() >= crossptmassimo_bins[index-1]) && (match->GetMuon()->Pt() <= crossptmassimo_bins[index]) ) {
	  fPtRel_CrossMuonPtMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetMuon()->Pt() >= crossptmassimo_bins[index-1]) && (match->GetMuon()->Pt() <= crossptmassimo_bins[index]) ) {
	  fPtRel_CrossMuonPtMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonPtMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

	Int_t    crossetamassimo_nbins = 4;
	Double_t *crossetamassimo_bins = new Double_t[crossetamassimo_nbins+1];
	crossetamassimo_bins[0] = -1.6;
	crossetamassimo_bins[1] = -0.75;
	crossetamassimo_bins[2] = 0.25;
	crossetamassimo_bins[3] = 1.3;
	crossetamassimo_bins[4] = 2.3;

	index = 1;
	if ( (match->GetMuon()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetMuon()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetMuon()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetMuon()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetMuon()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetMuon()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetMuon()->Eta() >= crossetamassimo_bins[index-1]) && (match->GetMuon()->Eta() <= crossetamassimo_bins[index]) ) {
	  fPtRel_CrossMuonEtaMassimo_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonEtaMassimo_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

	Int_t    crossmuonjetpt_nbins = 3;
	Double_t *crossmuonjetpt_bins = new Double_t[crossmuonjetpt_nbins+1];
	crossmuonjetpt_bins[0] =  6.0;
	crossmuonjetpt_bins[1] = 11.0;;
	crossmuonjetpt_bins[2] = 16.0;
	crossmuonjetpt_bins[3] = 30.0;

	index = 1;
	if ( (match->GetJet()->Pt() >= crossmuonjetpt_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetpt_bins[index]) ) {
	  fPtRel_CrossMuonJetPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPt_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetJet()->Pt() >= crossmuonjetpt_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetpt_bins[index]) ) {
	  fPtRel_CrossMuonJetPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPt_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetJet()->Pt() >= crossmuonjetpt_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetpt_bins[index]) ) {
	  fPtRel_CrossMuonJetPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPt_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossMuonJetEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetJet()->Eta() >= crossmuonjeteta_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjeteta_bins[index]) ) {
	  fPtRel_CrossMuonJetEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossMuonJetPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 7;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 8;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 9;
	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
	  fPtRel_CrossMuonJetPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
// 	index = 10;
// 	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetPtFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetPtFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 11;
// 	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetPtFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetPtFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 12;
// 	if ( (match->GetJet()->Pt() >= crossmuonjetptfine_bins[index-1]) && (match->GetJet()->Pt() <= crossmuonjetptfine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetPtFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetPtFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}

	Int_t    crossmuonjetetafine_nbins = 8;
	Double_t *crossmuonjetetafine_bins = new Double_t[crossmuonjetetafine_nbins+1];
	crossmuonjetetafine_bins[0]  = -1.5;
	crossmuonjetetafine_bins[1]  = -1.0;
	crossmuonjetetafine_bins[2]  = -0.50;
	crossmuonjetetafine_bins[3]  =  0.0;
	crossmuonjetetafine_bins[4]  =  0.50;
	crossmuonjetetafine_bins[5]  =  1.0;
	crossmuonjetetafine_bins[6] =   1.5;
	crossmuonjetetafine_bins[7] =  2.0;
	crossmuonjetetafine_bins[8] =  2.50;

	index = 1;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 7;
	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
	  fPtRel_CrossMuonJetEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMuonJetEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
 	index = 8;
 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
 	  fPtRel_CrossMuonJetEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_CrossMuonJetEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
 	}
// 	index = 9;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 10;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 11;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 12;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 13;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 14;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 15;
// 	if ( (match->GetJet()->Eta() >= crossmuonjetetafine_bins[index-1]) && (match->GetJet()->Eta() <= crossmuonjetetafine_bins[index]) ) {
// 	  fPtRel_CrossMuonJetEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMuonJetEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
	fPtMuOverEtJet->Fill(match->GetMuon()->Pt()/match->GetJet()->Et(),gHeader->GetWeight(match->GetMuon()));
	fPtRel_0_4_8_Orange->Fill(match->GetMuon()->GetJetPt(),gHeader->GetWeight(match->GetMuon()));
	fDeltaR_Orange->Fill(match->GetMuon()->GetJetDr(),gHeader->GetWeight(match->GetMuon()));
	f2DBSImpactVsPtRel_0_5_7_JetMinMu->Fill(match->GetMuon()->Get2DBeamSpotImpactParameter(),match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	f2DBSImpactVsPtRel_0_5_7->Fill(match->GetMuon()->Get2DBeamSpotImpactParameter(),match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	fPtRelSelfVsOrange->Fill(match->GetPtRel(),match->GetMuon()->GetJetPt(),gHeader->GetWeight(match->GetMuon()));
	fDeltaRSelfVsOrange->Fill(match->GetDeltaR(),match->GetMuon()->GetJetDr(),gHeader->GetWeight(match->GetMuon()));
	
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
	  fPtRel_CrossJetXGamma_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGamma_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGamma_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGamma_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGamma_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgamma_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgamma_bins[index]) ) {
	  fPtRel_CrossJetXGamma_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGamma_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossJetXGammaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGammaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGammaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGammaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGammaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGammaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (gJets->GetXGamma_zufo() >= crossjetxgammafine_bins[index-1]) && (gJets->GetXGamma_zufo() <= crossjetxgammafine_bins[index]) ) {
	  fPtRel_CrossJetXGammaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetXGammaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	crossjetmjets_bins[10]  = 60.0;

	index = 1;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 7;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 8;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 9;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}

	index = 10;
	if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	  fPtRel_CrossJetMJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetMJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossJetDPhiJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDPhiJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDPhiJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDPhiJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDPhiJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDPhiJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  fPtRel_CrossJetDPhiJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDPhiJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	// 	index = 7;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDPhiJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	// 	index = 8;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDPhiJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	// 	index = 9;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDPhiJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	// 	index = 10;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDPhiJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossJetDRJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDRJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDRJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDRJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDRJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  fPtRel_CrossJetDRJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetDRJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	// 	index = 6;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDRJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	// 	index = 7;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDRJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	// 	index = 8;
	// 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	// 	  fPtRel_CrossJetDRJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDRJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossJetPtJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetPtJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetPtJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetPtJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetPtJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  fPtRel_CrossJetPtJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetPtJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	// 	index = 6;
	// 	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	// 	  fPtRel_CrossJetPtJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetPtJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetPtJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
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
	  fPtRel_CrossJetCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossJetCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	// index = 7;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 8;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 9;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 10;
// 	if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossJetCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
//	}
      }
	//--------------------------------------------------------
      if((match->GetJet()->GetMJCosThetaStar_MJets() > 20) && (match->GetJet()->GetMJCosThetaStar_EtaJets()<0.7)){
	index = 1;
	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 2;
	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 3;
	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 4;
	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 5;
	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	index = 6;
	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	// index = 7;
// 	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 8;
// 	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 9;
// 	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
// 	index = 10;
// 	if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	  fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	}
      }
	//---------------------------------------------------------------
	//	if ( match->GetJet()->GetMJCosThetaStar_xgamma() > 0.75 ) {
	if ( gJets->GetXGamma_zufo() >= 0.75 ) {
	  if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99) fGeneralCrossMJMatchCosThetaStarJetsHigh->Fill(match->GetJet()->GetMJCosThetaStar(),gHeader->GetWeight(match->GetMuon()));
	  if ( gCards->GetMC()  && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	    if ( gMCs->GetAllMCCuts() ) {
	      GJet *jet1 = match->GetJet();
	      GJet *jet2 = gJets->GetJetWithID(match->GetJet()->GetSecondJetID());
	      if ( (jet1!=0)&&(jet2!=0) ) {
		if ( (jet1->GetAssociatedMCJet()!=0)&&(jet2->GetAssociatedMCJet()!=0) ) {
		  if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99) fGeneralCrossMJMatchCosThetaStarJetsHighRecNTrue->Fill(match->GetJet()->GetMJCosThetaStar(),gHeader->GetWeight(match->GetMuon()));
		}
	      }
	    }
	  }
	  if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99){
	  index = 1;
	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
// 	  index = 7;
// 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 8;
// 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 9;
// 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 10;
// 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
 	}
    }
	if ( gJets->GetXGamma_zufo() >= 0.75 ) {
	  index = 1;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 7;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 8;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 9;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 10;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  
	  index = 1;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  // 	index = 7;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 8;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 9;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 10;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  
	  index = 1;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  // 	index = 6;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDRJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 7;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDRJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 8;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDRJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  
	  index = 1;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  // 	index = 6;
	  // 	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetPtJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetPtJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  
	  if(gJets->GetEtaJets()<99 && gJets->GetMJets()>0){
	  index = 1;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
// 	  index = 7;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 8;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 9;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 10;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    
// 	  }
	  }
	}
	
	
	//	if ( match->GetJet()->GetMJCosThetaStar_xgamma() < 0.75 ) {
	if ( gJets->GetXGamma_zufo() < 0.75 ) {
	  if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99) fGeneralCrossMJMatchCosThetaStarJetsLow->Fill(match->GetJet()->GetMJCosThetaStar(),gHeader->GetWeight(match->GetMuon()));
	  if ( gCards->GetMC()  && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	    if ( gMCs->GetAllMCCuts() ) {
	      GJet *jet1 = match->GetJet();
	      GJet *jet2 = gJets->GetJetWithID(match->GetJet()->GetSecondJetID());
	      if ( (jet1!=0)&&(jet2!=0) ) {
		if ( (jet1->GetAssociatedMCJet()!=0)&&(jet2->GetAssociatedMCJet()!=0) ) {
		   if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99) fGeneralCrossMJMatchCosThetaStarJetsLowRecNTrue->Fill(match->GetJet()->GetMJCosThetaStar(),gHeader->GetWeight(match->GetMuon()));
		}
	      }
	    }
	  }
	  if(match->GetJet()->GetMJCosThetaStar_MJets()>0 && match->GetJet()->GetMJCosThetaStar_EtaJets()<99){
	    index = 1;
	    if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    }
	    index = 2;
	    if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    }
	    index = 3;
	    if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    }
	    index = 4;
	    if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    }
	    index = 5;
	    if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    }
	    index = 6;
	    if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	      fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    }
	    // 	  index = 7;
	    // 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	  }
	    // 	  index = 8;
	    // 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	  }
	    // 	  index = 9;
	    // 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	    //    cout << " Run / Event "<<gData->Getrunnr() << " / " << gData->Geteventnr() << " costhetastarmjmatch " << match->GetJet()->GetMJCosThetaStar() << " xgamma_zufo " <<  match->GetJet()->GetMJCosThetaStar_xgamma() << endl;
	    // 	  }
	    // 	  index = 10;
	    // 	  if ( (match->GetJet()->GetMJCosThetaStar() >= crossjetcosthetastarjets_bins[index-1]) && (match->GetJet()->GetMJCosThetaStar() <= crossjetcosthetastarjets_bins[index]) ) {
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    // 	    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    // 	    //	    cout << " Run / Event "<<gData->Getrunnr() << " / " << gData->Geteventnr() << " costhetastarmjmatch " << match->GetJet()->GetMJCosThetaStar() << " xgamma_zufo " <<  match->GetJet()->GetMJCosThetaStar_xgamma() << endl;
	    
	  }
	  // 	  }
	}
	//-----
	if ( gJets->GetXGamma_zufo() < 0.75 ) {
	  index = 1;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 7;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 8;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 9;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 10;
	  if ( (gJets->GetMJets() >= crossjetmjets_bins[index-1]) && (gJets->GetMJets() <= crossjetmjets_bins[index]) ) {
	    fPtRel_CrossJetMJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetMJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  
	  index = 1;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	}
	  index = 2;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	    fPtRel_CrossJetDPhiJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  // 	index = 7;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 8;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 9;
	  // 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	// 	index = 10;
	// 	if ( (gJets->GetDPhiJets() >= crossjetdphijets_bins[index-1]) && (gJets->GetDPhiJets() <= crossjetdphijets_bins[index]) ) {
	// 	  fPtRel_CrossJetDPhiJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	// 	  fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	// 	}
	  
	  index = 1;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	    fPtRel_CrossJetDRJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetDRJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  // 	index = 6;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDRJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 7;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDRJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  // 	index = 8;
	  // 	if ( (gJets->GetDRJets() >= crossjetdrjets_bins[index-1]) && (gJets->GetDRJets() <= crossjetdrjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetDRJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetDRJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  
	  index = 1;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	    fPtRel_CrossJetPtJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetPtJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  // 	index = 6;
	  // 	if ( (gJets->GetPtJets() >= crossjetptjets_bins[index-1]) && (gJets->GetPtJets() <= crossjetptjets_bins[index]) ) {
	  // 	  fPtRel_CrossJetPtJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_CrossJetPtJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetPtJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	  // 	  fPtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  // 	}
	  if(gJets->GetEtaJets()<99 && gJets->GetMJets()>0){
	  index = 1;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 2;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 3;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 4;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 5;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
	  index = 6;
	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
	  }
// 	  index = 7;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 8;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 9;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
// 	  index = 10;
// 	  if ( (gJets->GetCosThetaStarJets() >= crossjetcosthetastarjets_bins[index-1]) && (gJets->GetCosThetaStarJets() <= crossjetcosthetastarjets_bins[index]) ) {
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10->Fill(match->GetPtRel(),gHeader->GetWeight(match->GetMuon()));
// 	    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu->Fill(match->GetPtRelJetMinMu(),gHeader->GetWeight(match->GetMuon()));
// 	  }
	  }
	  
	  
	}
	
      }
    }
    
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::CreateGeneral() {
  //
  // create general plots
  if ( gDebug ) cout << endl << "GMJMatchs::CreateGeneral() called" << endl << endl;
  
  if ( gCards->GetMJMATCHGeneral() ) {

    Bool_t uncut = kFALSE;
    Bool_t fits = kFALSE;
    Bool_t fits_JetMinMu = kFALSE;
    Bool_t fits_cross = kTRUE;
    Bool_t fits_JetMinMu_cross = kFALSE;
    Bool_t fits_0_4_8 = kFALSE;
    Bool_t fits_0_4_8_JetMinMu = kFALSE;
    Bool_t fits_0_5_10 = kFALSE;
    Bool_t fits_0_5_10_JetMinMu = kFALSE;
    Bool_t fits_0_5_20 = kFALSE;
    Bool_t fits_0_5_20_JetMinMu = kFALSE;
    Bool_t fits_0_3_6 = kFALSE;
    Bool_t fits_0_3_6_JetMinMu = kFALSE;
    Bool_t fits_0_5_7 = kTRUE;
    Bool_t fits_0_5_7_JetMinMu = kTRUE;
    Bool_t fits_0_5_7_trigger = kFALSE;
    Bool_t fits_0_5_7_JetMinMu_trigger = kFALSE;
    Bool_t fits_0_5_7_cross = kTRUE;
    Bool_t fits_0_5_7_JetMinMu_cross = kTRUE;

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
    Int_t    ptmuoveretjetbins = 30;
    Double_t ptmuoveretjetlow  = 0.;
    Double_t ptmuoveretjethigh = 1.5;
  
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
    Int_t    impact2Dbins  = 20;
    Double_t impact2Dlow   = -0.1;
    Double_t impact2Dhigh  = 0.1;
    Int_t    ptrelcompbins = 300;
    Double_t ptrelcomplow  = 0.;
    Double_t ptrelcomphigh = 3.;
    Int_t    drcompbins    = 300;
    Double_t drcomplow     = 0.;
    Double_t drcomphigh    = 3.;
    Int_t    ptrelbins     = 100;
    Double_t ptrellow      = 0.;
    Double_t ptrelhigh     = 10.;


    Int_t    crossjetcosthetastarjets_nbins = 6;
    Double_t *crossjetcosthetastarjets_bins = new Double_t[crossjetcosthetastarjets_nbins+1];
    crossjetcosthetastarjets_bins[0]  = -0.83;
    crossjetcosthetastarjets_bins[1]  = -0.664;
    crossjetcosthetastarjets_bins[2]  = -0.332;
    crossjetcosthetastarjets_bins[3]  =  0.0;
    crossjetcosthetastarjets_bins[4]  =  0.332;
    crossjetcosthetastarjets_bins[5]  =  0.664;
    crossjetcosthetastarjets_bins[6]  =  0.83;

    fNperEv_uncut = gHistogrammer->TH1DFactory("MJMatch","NperEv_uncut","uncut n_{match}",10,0.,10.,"n_{match}","Events");
    fDeltaR_uncut = gHistogrammer->TH1DFactory("MJMatch","DeltaR_uncut","uncut #DeltaR = #sqrt{#eta^{2}+#phi^{2}}",drbins,drlow,drhigh,"#DeltaR = #sqrt{#eta^{2}+#phi^{2}}","Events");
    fDeltaEta_uncut = gHistogrammer->TH1DFactory("MJMatch","DeltaEta_uncut","uncut #Delta#eta",detabins,detalow,detahigh,"#Delta#eta","Events");
    fDeltaPhi_uncut = gHistogrammer->TH1DFactory("MJMatch","DeltaPhi_uncut","uncut #Delta#phi",dphibins,dphilow,dphihigh,"#Delta#phi","Events");
    fDeltaTheta_uncut = gHistogrammer->TH1DFactory("MJMatch","DeltaTheta_uncut","uncut #Delta#theta",dthetabins,dthetalow,dthetahigh,"#Delta#theta","Events");
    fPtRel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_uncut","uncut p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_Forward_uncut","uncut forward p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_Forward_uncut","uncut forward p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_Barrel_uncut","uncut barrel p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_Barrel_uncut","uncut barrel p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_Rear_uncut","uncut rear p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_Rear_uncut","uncut rear p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_4_8_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_4_8_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_4_8_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_4_8_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_10_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_10_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_10_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_10_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_20_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_20_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_20_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_20_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_3_6_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_3_6_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_3_6_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_3_6_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_uncut","uncut p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);

    fPtRel_0_5_7_MPMATCHMUBAC_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_uncut","uncut p_{T}^{rel} for #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHMUBAC_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_Forward_uncut","uncut p_{T}^{rel} for forward #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for forward #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_uncut","uncut p_{T}^{rel} for #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_Forward_uncut","uncut p_{T}^{rel} for forward #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for forward #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_uncut","uncut p_{T}^{rel} for #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_Forward_uncut","uncut p_{T}^{rel} for forward #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for forward #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);

    fPtRel_0_5_7_BREMATMUBAC_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_uncut","uncut p_{T}^{rel} for #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATMUBAC_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_Barrel_uncut","uncut p_{T}^{rel} for barrel #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for barrel #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATMUBAC_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_Rear_uncut","uncut p_{T}^{rel} for rear #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for rear #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATNOTMUBAC_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_uncut","uncut p_{T}^{rel} for #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATNOTMUBAC_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_Barrel_uncut","uncut p_{T}^{rel} for barrel #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for barrel #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATNOTMUBAC_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_Rear_uncut","uncut p_{T}^{rel} for rear #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for rear #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTBREMATMUBAC_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_uncut","uncut p_{T}^{rel} for #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTBREMATMUBAC_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_Barrel_uncut","uncut p_{T}^{rel} for barrel #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for barrel #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTBREMATMUBAC_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_Rear_uncut","uncut p_{T}^{rel} for rear #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear_uncut","uncut p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for rear #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);

    fPtRel_0_5_7_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_Forward_uncut","uncut forward #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_JetMinMu_Forward_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_Forward_uncut","uncut forward #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_Barrel_uncut","uncut barrel #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_JetMinMu_Barrel_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_Barrel_uncut","uncut barrel #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_Rear_uncut","uncut rear #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);
    fPtRel_0_5_7_JetMinMu_Rear_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_Rear_uncut","uncut rear #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",uncut);

    fPtMuOverEtJet_uncut = gHistogrammer->TH1DFactory("MJMatch","PtMuOverEtJet_uncut","uncut p_{T}^{#mu}/E_{T}^{jet}",ptmuoveretjetbins,ptmuoveretjetlow,ptmuoveretjethigh,"p_{T}^{#mu}/E_{T}^{jet}","Events",uncut);
    fPtRel_0_4_8_Orange_uncut = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_4_8_Orange_uncut","uncut p_{T}^{rel} from orange",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events",uncut);
    fDeltaR_Orange_uncut = gHistogrammer->TH1DFactory("MJMatch","DeltaR_Orange_uncut","uncut #DeltaR from orange",drbins,drlow,drhigh,"#DeltaR","Events",uncut);
    
    f2DBSImpactVsPtRel_0_5_7_JetMinMu_uncut = gHistogrammer->TH2DVarFactory("MJMatch","2DBSImpactVsPtRel_0_5_7_JetMinMu_uncut","uncut 2D beamspot impact parameter vs. p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",impact2Dbins,impact2Dlow, impact2Dhigh,ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"#delta [cm]","p_{T}^{rel} [GeV]","Events",uncut);
    f2DBSImpactVsPtRel_0_5_7_uncut = gHistogrammer->TH2DVarFactory("MJMatch","2DBSImpactVsPtRel_0_5_7_uncut","uncut 2D beamspot impact parameter vs. p_{T}^{rel}",impact2Dbins,impact2Dlow, impact2Dhigh,ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"#delta [cm]","p_{T}^{rel} [GeV]","Events",uncut);
    fPtRelSelfVsOrange_uncut = gHistogrammer->TH2DFactory("MJMatch","PtRelSelfVsOrange_uncut","uncut p_{T}^{rel} self vs. orange",ptrelcompbins,ptrelcomplow,ptrelcomphigh,ptrelcompbins,ptrelcomplow,ptrelcomphigh,"p_{T}^{rel} [GeV]","p_{T}^{rel} [GeV]","Events",uncut);
    fDeltaRSelfVsOrange_uncut = gHistogrammer->TH2DFactory("MJMatch","DeltaRSelfVsOrange_uncut","uncut #DeltaR self vs. orange",drcompbins,drcomplow,drcomphigh,drcompbins,drcomplow,drcomphigh,"#DeltaR","#DeltaR","Events",uncut);

    fNperEv = gHistogrammer->TH1DFactory("MJMatch","NperEv","n_{match}",10,0.,10.,"n_{match}","Events");
    fDeltaR = gHistogrammer->TH1DFactory("MJMatch","DeltaR","#DeltaR = #sqrt{#eta^{2}+#phi^{2}}",drbins,drlow,drhigh,"#DeltaR = #sqrt{#eta^{2}+#phi^{2}}","Events");
    fDeltaEta = gHistogrammer->TH1DFactory("MJMatch","DeltaEta","#Delta#eta",detabins,detalow,detahigh,"#Delta#eta","Events");
    fDeltaPhi = gHistogrammer->TH1DFactory("MJMatch","DeltaPhi","#Delta#phi",dphibins,dphilow,dphihigh,"#Delta#phi","Events");
    fDeltaTheta = gHistogrammer->TH1DFactory("MJMatch","DeltaTheta","#Delta#theta",dthetabins,dthetalow,dthetahigh,"#Delta#theta","Events");
    /*
    fPtRel_lu_is = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_lu_is","p_{T}^{rel}_lu_is",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_lu_is","Events");
    fPtRel_ll_is = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_ll_is","p_{T}^{rel}_ll_is",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_ll_is","Events");
    fPtRel_hu_is = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_hu_is","p_{T}^{rel}_hu_is",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_hu_is","Events");
    fPtRel_hl_is = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_hl_is","p_{T}^{rel}_hl_is",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_hl_is","Events");
    fPtRel_lu_nis = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_lu_nis","p_{T}^{rel}_lu_nis",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_lu_nis","Events");
    fPtRel_ll_nis = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_ll_nis","p_{T}^{rel}_ll_nis",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_ll_nis","Events");
    fPtRel_hu_nis = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_hu_nis","p_{T}^{rel}_hu_nis",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_hu_nis","Events");
    fPtRel_hl_nis = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_hl_nis","p_{T}^{rel}_hl_nis",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]_hl_nis","Events");
    fPtRel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits);
    */
    fPtRel_lu_is = gHistogrammer->TH1DFactory("DIMuon","PtRel_lu_is","p_{T}^{rel}_lu_is",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_lu_is","Events");
    fPtRel_ll_is = gHistogrammer->TH1DFactory("DIMuon","PtRel_ll_is","p_{T}^{rel}_ll_is",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_ll_is","Events");
    fPtRel_hu_is = gHistogrammer->TH1DFactory("DIMuon","PtRel_hu_is","p_{T}^{rel}_hu_is",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_hu_is","Events");
    fPtRel_hl_is = gHistogrammer->TH1DFactory("DIMuon","PtRel_hl_is","p_{T}^{rel}_hl_is",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_hl_is","Events");
    fPtRel_lu_nis = gHistogrammer->TH1DFactory("DIMuon","PtRel_lu_nis","p_{T}^{rel}_lu_nis",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_lu_nis","Events");
    fPtRel_ll_nis = gHistogrammer->TH1DFactory("DIMuon","PtRel_ll_nis","p_{T}^{rel}_ll_nis",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_ll_nis","Events");
    fPtRel_hu_nis = gHistogrammer->TH1DFactory("DIMuon","PtRel_hu_nis","p_{T}^{rel}_hu_nis",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_hu_nis","Events");
    fPtRel_hl_nis = gHistogrammer->TH1DFactory("DIMuon","PtRel_hl_nis","p_{T}^{rel}_hl_nis",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]_hl_nis","Events");
    fPtRel = gHistogrammer->TH1DFactory("DIMuon","PtRel","p_{T}^{rel}",ptrelbins,ptrellow,ptrelhigh,"p_{T}^{rel} [GeV]","Events");

    fPtRel_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu);
    fPtRel_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_Forward","forward p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits);
    fPtRel_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_Forward","forward p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu);
    fPtRel_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_Barrel","barrel p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits);
    fPtRel_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_Barrel","barrel p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu);
    fPtRel_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_Rear","rear p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits);
    fPtRel_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_JetMinMu_Rear","rear p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu);
    fPtRel_0_4_8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_4_8","p_{T}^{rel}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events",fits_0_4_8);
    fPtRel_0_4_8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_4_8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events",fits_0_4_8_JetMinMu);
    fPtRel_0_5_10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_10","p_{T}^{rel}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events",fits_0_5_10);
    fPtRel_0_5_10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_10,ptrel_bins_0_5_10,"p_{T}^{rel} [GeV]","Events",fits_0_5_10_JetMinMu);
    fPtRel_0_5_20 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_20","p_{T}^{rel}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events",fits_0_5_20);
    fPtRel_0_5_20_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_20_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_20,ptrel_bins_0_5_20,"p_{T}^{rel} [GeV]","Events",fits_0_5_20_JetMinMu);
    fPtRel_0_3_6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_3_6","p_{T}^{rel}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events",fits_0_3_6);
    fPtRel_0_3_6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_3_6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_3_6,ptrel_bins_0_3_6,"p_{T}^{rel} [GeV]","Events",fits_0_3_6_JetMinMu);
    fPtRel_0_5_7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7);
    fPtRel_0_5_7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu);
    fPtRel_0_5_7_MuChamber_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MuChamber_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu);
  fPtRel_0_5_7_MuBac_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MuBac_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu); 

    fPtRel_0_5_7_MPMATCHMUBAC = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC","p_{T}^{rel} for #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_MPMATCHMUBAC_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_Forward","p_{T}^{rel} for forward #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for forward #mu found by MPMATCH and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_MPMATCHNOTMUBAC = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC","p_{T}^{rel} for #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_Forward","p_{T}^{rel} for forward #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for forward #mu found by MPMATCH and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_NOTMPMATCHMUBAC = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC","p_{T}^{rel} for #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_Forward","p_{T}^{rel} for forward #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for forward #mu found by MUBAC and not MPMATCH",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);

    fPtRel_0_5_7_BREMATMUBAC = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC","p_{T}^{rel} for #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_BREMATMUBAC_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_BREMATMUBAC_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_Barrel","p_{T}^{rel} for barrel #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for barrel #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_BREMATMUBAC_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_Rear","p_{T}^{rel} for rear #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for rear #mu found by BREMAT and MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_BREMATNOTMUBAC = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC","p_{T}^{rel} for #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_BREMATNOTMUBAC_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_Barrel","p_{T}^{rel} for barrel #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for barrel #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_BREMATNOTMUBAC_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_Rear","p_{T}^{rel} for rear #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for rear #mu found by BREMAT and not MUBAC",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_NOTBREMATMUBAC = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC","p_{T}^{rel} for #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_NOTBREMATMUBAC_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_Barrel","p_{T}^{rel} for barrel #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for barrel #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);
    fPtRel_0_5_7_NOTBREMATMUBAC_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_Rear","p_{T}^{rel} for rear #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_trigger);
    fPtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet} for rear #mu found by MUBAC and not BREMAT",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_trigger);

    fPtRel_0_5_7_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_Forward","forward #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7);
    fPtRel_0_5_7_JetMinMu_Forward = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_Forward","forward #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu);
    fPtRel_0_5_7_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_Barrel","barrel #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7);
    fPtRel_0_5_7_JetMinMu_Barrel = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_Barrel","barrel #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu);
    fPtRel_0_5_7_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_Rear","rear #mu p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7);
    fPtRel_0_5_7_JetMinMu_Rear = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_JetMinMu_Rear","rear #mu p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu);

    f2DBSImpactVsPtRel_0_5_7_JetMinMu = gHistogrammer->TH2DVarFactory("MJMatch","2DBSImpactVsPtRel_0_5_7_JetMinMu","2D beamspot impact parameter vs. p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",impact2Dbins,impact2Dlow, impact2Dhigh,ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"#delta [cm]","p_{T}^{rel} [GeV]","Events");
    f2DBSImpactVsPtRel_0_5_7 = gHistogrammer->TH2DVarFactory("MJMatch","2DBSImpactVsPtRel_0_5_7","2D beamspot impact parameter vs. p_{T}^{rel}",impact2Dbins,impact2Dlow, impact2Dhigh,ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"#delta [cm]","p_{T}^{rel} [GeV]","Events");
    fPtRelSelfVsOrange = gHistogrammer->TH2DFactory("MJMatch","PtRelSelfVsOrange","p_{T}^{rel} self vs. orange",ptrelcompbins,ptrelcomplow,ptrelcomphigh,ptrelcompbins,ptrelcomplow,ptrelcomphigh,"p_{T}^{rel} [GeV]","p_{T}^{rel} [GeV]","Events");
    fDeltaRSelfVsOrange = gHistogrammer->TH2DFactory("MJMatch","DeltaRSelfVsOrange","#DeltaR self vs. orange",drcompbins,drcomplow,drcomphigh,drcompbins,drcomplow,drcomphigh,"#DeltaR","#DeltaR","Events");

    // ptrel fits for muon pt cross section

    fPtRel_CrossMuonPt_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonPt_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonPt_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonPt_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPt_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPt_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for muon eta cross section

    fPtRel_CrossMuonEta_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonEta_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonEta_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonEta_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for fine muon pt cross section

    fPtRel_CrossMuonPtFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for fine muon eta cross section

    fPtRel_CrossMuonEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //----------------------
    fPtRel_CrossMuonFinder_Bin0 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin0","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin13 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin13","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin14 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin14","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonFinder_Bin0_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin0_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonFinder_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonFinder_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin0 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin0","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin13 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin13","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin14 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin14","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin0_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
   fPtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonFinder_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for massimo muon pt cross section

    fPtRel_CrossMuonPtMassimo_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtMassimo_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtMassimo_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtMassimo_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtMassimo_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtMassimo_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonPtMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonPtMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonPtMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonPtMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for massimo muon eta cross section

    fPtRel_CrossMuonEtaMassimo_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaMassimo_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaMassimo_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaMassimo_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonEtaMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonEtaMassimo_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonEtaMassimo_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonEtaMassimo_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for muon jet pt cross section

    fPtRel_CrossMuonJetPt_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPt_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPt_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonJetPt_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPt_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPt_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonJetPt_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPt_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPt_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPt_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for muon jet eta cross section

    fPtRel_CrossMuonJetEta_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonJetEta_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonJetEta_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossMuonJetEta_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEta_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for fine muon jet pt cross section

    fPtRel_CrossMuonJetPtFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetPtFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetPtFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetPtFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    // ptrel fits for fine muon jet eta cross section

    fPtRel_CrossMuonJetEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMuonJetEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMuonJetEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMuonJetEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin11","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin12","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin13","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin14","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin15","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin11_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin12_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin13_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin14_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMuonJetEtaFine_Bin15_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtMuOverEtJet = gHistogrammer->TH1DFactory("MJMatch","PtMuOverEtJet","p_{T}^{#mu}/E_{T}^{jet}",ptmuoveretjetbins,ptmuoveretjetlow,ptmuoveretjethigh,"p_{T}^{#mu}/E_{T}^{jet}","Events");
    fPtRel_0_4_8_Orange = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_4_8_Orange","p_{T}^{rel} from orange",ptrel_nbins_0_4_8,ptrel_bins_0_4_8,"p_{T}^{rel} [GeV]","Events");
    fDeltaR_Orange = gHistogrammer->TH1DFactory("MJMatch","DeltaR_Orange","#DeltaR from orange",drbins,drlow,drhigh,"#DeltaR","Events");


    // dijet cross sections

    fPtRel_CrossJetXGamma_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGamma_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetXGamma_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGamma_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetXGamma_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGamma_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetXGamma_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGamma_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetXGamma_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGamma_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGamma_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGamma_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetXGammaFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGammaFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGammaFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGammaFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGammaFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGammaFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetXGammaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetXGammaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetXGammaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetXGammaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetXGammaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetXGammaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetXGammaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetXGammaFine_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetMJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetDPhiJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetDRJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetPtJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetPtJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetPtJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetPtJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //------------
    fPtRel_CrossMJMatchCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //_________________________________________________________________
    fPtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //_______________________________________________________________________________________________
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //__________________________________________________________________________________________
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJets_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //____________________________________________________________________________
    fPtRel_CrossJetMJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetDPhiJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetDRJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetPtJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetPtJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetPtJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //________________________________________________________
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //________________________________________________________________

    fPtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //________________________________________________________________
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //_____________________________________________________________________

    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //------------
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //_________________________________________________________________
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //_______________________________________________________________________________________________
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //__________________________________________________________________________________________
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsHigh_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    //_________________________________________________________________
    fPtRel_CrossJetMJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetMJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetMJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetMJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetMJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetDPhiJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDPhiJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDPhiJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetDRJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetDRJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetDRJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetDRJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetDRJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetDRJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetDRJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    fPtRel_CrossJetPtJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //     fPtRel_CrossJetPtJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetPtJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetPtJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //     fPtRel_CrossJetPtJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetPtJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //     fPtRel_0_5_7_CrossJetPtJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //     fPtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetPtJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //_________________________________________________________
    fPtRel_CrossJetCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //_________________________________________________________________
    fPtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //____________________________________________________________ 
   fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //__________________________________________________________
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossJetCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    //------------
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_cross);
    //_________________________________________________________________
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
//     fPtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins,ptrel_bins,"p_{T}^{rel} [GeV]","Events",fits_JetMinMu_cross);
    //_______________________________________________________________________________________________
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10 = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10","p_{T}^{rel}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_cross);
    //__________________________________________________________________________________________
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin1_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin2_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin3_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin4_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin5_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
    fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin6_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin7_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin8_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin9_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);
//     fPtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu = gHistogrammer->TH1DVarFactory("MJMatch","PtRel_0_5_7_CrossMJMatchCosThetaStarJetsLow_Bin10_JetMinMu","p_{T}^{rel} for p_{T}^{#mu} relative to p_{T}^{#mu -jet}",ptrel_nbins_0_5_7,ptrel_bins_0_5_7,"p_{T}^{rel} [GeV]","Events",fits_0_5_7_JetMinMu_cross);

    //_______________________________________________________
    fGeneralCrossMJMatchCosThetaStarJetsHigh = gHistogrammer->TH1DVarFactory("Jet","CrossMJMatchCosThetaStarJetsHigh","cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJetsLow = gHistogrammer->TH1DVarFactory("Jet","CrossMJMatchCosThetaStarJetsLow","cos(#theta^{*})_{jj} for x_{#gamma} #leq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    fGeneralCrossMJMatchCosThetaStarJets = gHistogrammer->TH1DVarFactory("Jet","CrossMJMatchCosThetaStarJets","cos(#theta^{*})_{jj} for x_{#gamma} ",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      fGeneralCrossMJMatchCosThetaStarJetsRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMJMatchCosThetaStarJetsRecNTrue","rec. and true cos(#theta^{*})_{jj}} ",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
      fGeneralCrossMJMatchCosThetaStarJetsLowRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMJMatchCosThetaStarJetsLowRecNTrue","rec. and true cos(#theta^{*})_{jj}} for x_{#gamma} <0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
      fGeneralCrossMJMatchCosThetaStarJetsHighRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMJMatchCosThetaStarJetsHighRecNTrue","rec. and true cos(#theta^{*})_{jj}} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    }
    
  }
  
  // copy ptrel correction plots
  if ( gCards->GetMJMATCHPtRelCorrection() && gCards->GetMC() ) {
    
    TString filename = gSystem->Getenv("GUTCODEDIR");
    filename.Append("/analysis/ptrel-correction/");
    filename.Append(gCards->GetMJMATCHPtRelCorrFilename());
    TFile *input = new TFile(filename);
    if ( input->IsZombie() ) {
      TString msg = "GMJMatchs CreateGeneral ptrel-correction file: ";
      msg.Append(filename );
      msg.Append(" can not be found!");
      cout << msg << endl;
      gLister->FillErrorList(msg);
    } else {
      TList *histos = new TList();
      TDirectory *input_dir = (TDirectory*)input->Get("PtRel_Corrections");
      if ( input_dir == 0 ) {
        TString msg = "Could not find PtRel_Corrections directory in input file: ";
	msg.Append(input->GetName());
	cout << msg << endl;
	gLister->FillErrorList(msg);
      } else {
	input_dir->cd();
	TKey *key = 0;
	TObject *obj = 0;
	TIter nextkey(input_dir->GetListOfKeys());
	while ( (key = (TKey*)nextkey()) ) {
	  obj = key->ReadObj();
	  if (obj->IsA()->InheritsFrom("TH1D")) {
	    histos->Add((TH1D*)obj);
	  }
	}
	// copy histograms for charm MC samples
	if ( !gCards->GetMCBBBAR() && !gCards->GetMCLF() ) {
	  TH1D *copy = 0;
	  TIter nexthisto(histos);
	  while ( (copy = (TH1D*)nexthisto()) ) {
	    gHistogrammer->CopyPtRelCorrection("MJMatch",copy,gCards->GetMJMATCHPtRelCorrCMCWeight());
	  }
	}
	// copy histograms for lf MC samples
	if ( gCards->GetMCLF() ) {
	  TH1D *copy = 0;
	  TIter nexthisto(histos);
	  while ( (copy = (TH1D*)nexthisto()) ) {
	    gHistogrammer->CopyPtRelCorrection("MJMatch",copy,gCards->GetMJMATCHPtRelCorrLFMCWeight());
	  }
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GMJMatchs::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GMJMatchs::FillGeneral() called" << endl << endl;

  if ( gCards->GetMJMATCHGeneral() ) {

    fNperEv_uncut->Fill(fNMatchs,gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {
      if ( fSelectedMatchs != 0 ) {
	fNperEv->Fill(fSelectedMatchs,gHeader->GetWeight());
      }
    }

  }

  return kTRUE;
}

//_____________________________________________________________

TString GMJMatchs::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GMJMatchs::PrintMessage() called" << endl << endl;

  TString dummy = "";

  GMJMatch *match = 0;

  for ( Int_t i = 0; i < fNMatchs; i++ ) {
    match = ((GMJMatch*)(fMatchs->At(i)));
    dummy.Append(match->PrintMessage(option));
  }

  return dummy;
}

//_____________________________________________________________

Bool_t GMJMatchs::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GMJMatchs::Print() called" << endl << endl;

  option.ToUpper();

  GMJMatch *match = 0;

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("MJMATCHS") || option.Contains("ALL") ) {
      gLister->FillOutputList("MJMatchs:\n\n");
      for ( Int_t i = 0; i < fNMatchs; i++ ) {
	match = ((GMJMatch*)(fMatchs->At(i)));
	match->Print(option);
      }
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "MJMatchs:" << endl << endl;;
    for ( Int_t i = 0; i < fNMatchs; i++ ) {
      match = ((GMJMatch*)(fMatchs->At(i)));
      match->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

GMJMatch* GMJMatchs::GetMatch(Int_t index) {
  //
  // return match parameters of the match with index
  if ( gDebug ) cout << endl << "GMJMatchs::GetMatch called" << endl << endl;

  if ( (index < fNMatchs) && (index >= 0) ) {
    return ((GMJMatch*)(fMatchs->At(index)));
  } else {
    TString msg = "GMJMatchs::GetMatch: requested match index: ";
    msg += index;
    msg.Append(" is larger that total number of matchs: ");
    msg += fNMatchs;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GMJMatch* GMJMatchs::GetChosen() {
  //
  // return first chosen match
  if ( gDebug ) cout << endl << "GMJMatchs::GetChosen called" << endl << endl;

  GMJMatch *match = 0;

  for ( Int_t i = 0; i < fNMatchs; i++ ) {
    match = ((GMJMatch*)(fMatchs->At(i)));
    if ( match->GetType() == kChosen )
      return match;
  }

  return 0;

}
