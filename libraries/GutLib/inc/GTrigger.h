//
// GTrigger.h
//
// $Author: meyer $
// $Date: 2007/04/24 08:29:07 $
// $Revision: 1.18 $
//

#ifndef GUT_GTrigger
#define GUT_GTrigger

#ifndef GUT_GPhysObj
#include <GPhysObj.h>
#endif

class GTrigger : public GPhysObj {

 private:

  // control plots

  TH1D  *fControlFLT_uncut;                              // uncut control plot of flt bits
  TH1D  *fControlFLT_AfterPrescale_uncut;                // uncut control plot of flt bits after prescale

  TH1D  *fControlSLT_1_uncut;                            // uncut control plot of 1. word of slt bits
  TH1D  *fControlSLT_2_uncut;                            // uncut control plot of 2. word of slt bits
  TH1D  *fControlSLT_3_uncut;                            // uncut control plot of 3. word of slt bits
  TH1D  *fControlSLT_4_uncut;                            // uncut control plot of 4. word of slt bits
  TH1D  *fControlSLT_5_uncut;                            // uncut control plot of 5. word of slt bits
  TH1D  *fControlSLT_6_uncut;                            // uncut control plot of 6. word of slt bits

  TH1D  *fControlTLT_SPP_uncut;                          // uncut control plot for SPP TLT bits of 3. word of tlt bits
  TH1D  *fControlTLT_DIS_uncut;                          // uncut control plot for DIS TLT bits of 4. and 11. word of tlt bits
  TH1D  *fControlTLT_HPP_uncut;                          // uncut control plot for HPP TLT bits of 5. and 12. word of tlt bits
  TH1D  *fControlTLT_EXO_uncut;                          // uncut control plot for EXO TLT bits of 6. and 13. word of tlt bits
  TH1D  *fControlTLT_MUO_uncut;                          // uncut control plot for MUO TLT bits of 7. word of tlt bits
  TH1D  *fControlTLT_VTX_uncut;                          // uncut control plot for VTX TLT bits of 8. word of tlt bits
  TH1D  *fControlTLT_HFM_uncut;                          // uncut control plot for HFM TLT bits of 9. and 15. word of tlt bits
  TH1D  *fControlTLT_HFL_uncut;                          // uncut control plot for HFL TLT bits of 10. and 14. word of tlt bits

  TH1D  *fControlTLT_SPP_after_prescale_uncut;           // uncut control plot for SPP TLT bits of 3. word of tlt bits after prescale
  TH1D  *fControlTLT_DIS_after_prescale_uncut;           // uncut control plot for DIS TLT bits of 4. and 11. word of tlt bits after prescale
  TH1D  *fControlTLT_HPP_after_prescale_uncut;           // uncut control plot for HPP TLT bits of 5. and 12. word of tlt bits after prescale
  TH1D  *fControlTLT_EXO_after_prescale_uncut;           // uncut control plot for EXO TLT bits of 6. and 13. word of tlt bits after prescale
  TH1D  *fControlTLT_MUO_after_prescale_uncut;           // uncut control plot for MUO TLT bits of 7. word of tlt bits after prescale
  TH1D  *fControlTLT_VTX_after_prescale_uncut;           // uncut control plot for VTX TLT bits of 8. word of tlt bits after prescale
  TH1D  *fControlTLT_HFM_after_prescale_uncut;           // uncut control plot for HFM TLT bits of 9. and 15. word of tlt bits after prescale
  TH1D  *fControlTLT_HFL_after_prescale_uncut;           // uncut control plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale

  TH1D  *fControlFirstDST_uncut;                         // uncut control plot of first word of dst bits
  TH1D  *fControlSecondDST_uncut;                        // uncut control plot of second word of dst bits
  TH1D  *fControlThirdDST_uncut;                         // uncut control plot of third word of dst bits
  TH1D  *fControlFourthDST_uncut;                        // uncut control plot of fourth word of dst bits

  TH1D  *fControlZesSelect_uncut;                        // uncut control plot of zes_select variable

  TH1D  *fControlFLT;                                    // control plot of flt bits
  TH1D  *fControlFLT_AfterPrescale;                      // control plot of flt bits after prescale

  TH1D  *fControlSLT_1;                                  // control plot of 1. word of slt bits
  TH1D  *fControlSLT_2;                                  // control plot of 2. word of slt bits
  TH1D  *fControlSLT_3;                                  // control plot of 3. word of slt bits
  TH1D  *fControlSLT_4;                                  // control plot of 4. word of slt bits
  TH1D  *fControlSLT_5;                                  // control plot of 5. word of slt bits
  TH1D  *fControlSLT_6;                                  // control plot of 6. word of slt bits

  TH1D  *fControlTLT_SPP;                                // control plot for SPP TLT bits of 3. word of tlt bits
  TH1D  *fControlTLT_DIS;                                // control plot for DIS TLT bits of 4. and 11. word of tlt bits
  TH1D  *fControlTLT_HPP;                                // control plot for HPP TLT bits of 5. and 12. word of tlt bits
  TH1D  *fControlTLT_EXO;                                // control plot for EXO TLT bits of 6. and 13. word of tlt bits
  TH1D  *fControlTLT_MUO;                                // control plot for MUO TLT bits of 7. word of tlt bits
  TH1D  *fControlTLT_VTX;                                // control plot for VTX TLT bits of 8. word of tlt bits
  TH1D  *fControlTLT_HFM;                                // control plot for HFM TLT bits of 9. and 15. word of tlt bits
  TH1D  *fControlTLT_HFL;                                // control plot for HFL TLT bits of 10. and 14. word of tlt bits

  TH1D  *fControlTLT_SPP_after_prescale;                 // control plot for SPP TLT bits of 3. word of tlt bits after prescale
  TH1D  *fControlTLT_DIS_after_prescale;                 // control plot for DIS TLT bits of 4. and 11. word of tlt bits after prescale
  TH1D  *fControlTLT_HPP_after_prescale;                 // control plot for HPP TLT bits of 5. and 12. word of tlt bits after prescale
  TH1D  *fControlTLT_EXO_after_prescale;                 // control plot for EXO TLT bits of 6. and 13. word of tlt bits after prescale
  TH1D  *fControlTLT_MUO_after_prescale;                 // control plot for MUO TLT bits of 7. word of tlt bits after prescale
  TH1D  *fControlTLT_VTX_after_prescale;                 // control plot for VTX TLT bits of 8. word of tlt bits after prescale
  TH1D  *fControlTLT_HFM_after_prescale;                 // control plot for HFM TLT bits of 9. and 15. word of tlt bits after prescale
  TH1D  *fControlTLT_HFL_after_prescale;                 // control plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale

  TH1D  *fControlFirstDST;                               // control plot of first word of dst bits
  TH1D  *fControlSecondDST;                              // control plot of second word of dst bits
  TH1D  *fControlThirdDST;                               // control plot of third word of dst bits
  TH1D  *fControlFourthDST;                              // control plot of fourth word of dst bits

  TH1D  *fControlZesSelect;                              // control plot of zes_select variable


  // general plots
  TH1D  *fGeneralFLT_uncut;                              // uncut general plot of flt bits
  TH1D  *fGeneralFLT_AfterPrescale_uncut;                // uncut general plot of flt bits after prescale

  TH1D  *fGeneralSLT_1_uncut;                            // uncut general plot of 1. word of slt bits
  TH1D  *fGeneralSLT_2_uncut;                            // uncut general plot of 2. word of slt bits
  TH1D  *fGeneralSLT_3_uncut;                            // uncut general plot of 3. word of slt bits
  TH1D  *fGeneralSLT_4_uncut;                            // uncut general plot of 4. word of slt bits
  TH1D  *fGeneralSLT_5_uncut;                            // uncut general plot of 5. word of slt bits
  TH1D  *fGeneralSLT_6_uncut;                            // uncut general plot of 6. word of slt bits

  TH1D  *fGeneralTLT_SPP_uncut;                          // uncut general plot for SPP TLT bits of 3. word of tlt bits
  TH1D  *fGeneralTLT_DIS_uncut;                          // uncut general plot for DIS TLT bits of 4. and 11. word of tlt bits
  TH1D  *fGeneralTLT_HPP_uncut;                          // uncut general plot for HPP TLT bits of 5. and 12. word of tlt bits
  TH1D  *fGeneralTLT_EXO_uncut;                          // uncut general plot for EXO TLT bits of 6. and 13. word of tlt bits
  TH1D  *fGeneralTLT_MUO_uncut;                          // uncut general plot for MUO TLT bits of 7. word of tlt bits
  TH1D  *fGeneralTLT_VTX_uncut;                          // uncut general plot for VTX TLT bits of 8. word of tlt bits
  TH1D  *fGeneralTLT_HFM_uncut;                          // uncut general plot for HFM TLT bits of 9. and 15. word of tlt bits
  TH1D  *fGeneralTLT_HFL_uncut;                          // uncut general plot for HFL TLT bits of 10. and 14. word of tlt bits

  TH1D  *fGeneralTLT_SPP_after_prescale_uncut;           // uncut general plot for SPP TLT bits of 3. word of tlt bits after prescale
  TH1D  *fGeneralTLT_DIS_after_prescale_uncut;           // uncut general plot for DIS TLT bits of 4. and 11. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HPP_after_prescale_uncut;           // uncut general plot for HPP TLT bits of 5. and 12. word of tlt bits after prescale
  TH1D  *fGeneralTLT_EXO_after_prescale_uncut;           // uncut general plot for EXO TLT bits of 6. and 13. word of tlt bits after prescale
  TH1D  *fGeneralTLT_MUO_after_prescale_uncut;           // uncut general plot for MUO TLT bits of 7. word of tlt bits after prescale
  TH1D  *fGeneralTLT_VTX_after_prescale_uncut;           // uncut general plot for VTX TLT bits of 8. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HFM_after_prescale_uncut;           // uncut general plot for HFM TLT bits of 9. and 15. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HFL_after_prescale_uncut;           // uncut general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale

  TH1D  *fGeneralFirstDST_uncut;                         // uncut general plot of first word of dst bits
  TH1D  *fGeneralSecondDST_uncut;                        // uncut general plot of second word of dst bits
  TH1D  *fGeneralThirdDST_uncut;                         // uncut general plot of third word of dst bits
  TH1D  *fGeneralFourthDST_uncut;                        // uncut general plot of fourth word of dst bits

  TH1D  *fGeneralZesSelect_uncut;                        // uncut general plot of zes_select variable

  TH1D  *fGeneralFLT;                                    // general plot of flt bits
  TH1D  *fGeneralFLT_AfterPrescale;                      // general plot of flt bits after prescale

  TH1D  *fGeneralSLT_1;                                  // general plot of 1. word of slt bits
  TH1D  *fGeneralSLT_2;                                  // general plot of 2. word of slt bits
  TH1D  *fGeneralSLT_3;                                  // general plot of 3. word of slt bits
  TH1D  *fGeneralSLT_4;                                  // general plot of 4. word of slt bits
  TH1D  *fGeneralSLT_5;                                  // general plot of 5. word of slt bits
  TH1D  *fGeneralSLT_6;                                  // general plot of 6. word of slt bits

  TH1D  *fGeneralTLT_SPP;                                // general plot for SPP TLT bits of 3. word of tlt bits
  TH1D  *fGeneralTLT_DIS;                                // general plot for DIS TLT bits of 4. and 11. word of tlt bits
  TH1D  *fGeneralTLT_HPP;                                // general plot for HPP TLT bits of 5. and 12. word of tlt bits
  TH1D  *fGeneralTLT_EXO;                                // general plot for EXO TLT bits of 6. and 13. word of tlt bits
  TH1D  *fGeneralTLT_MUO;                                // general plot for MUO TLT bits of 7. word of tlt bits
  TH1D  *fGeneralTLT_VTX;                                // general plot for VTX TLT bits of 8. word of tlt bits
  TH1D  *fGeneralTLT_HFM;                                // general plot for HFM TLT bits of 9. and 15. word of tlt bits
  TH1D  *fGeneralTLT_HFL;                                // general plot for HFL TLT bits of 10. and 14. word of tlt bits

  TH1D  *fGeneralTLT_SPP_after_prescale;                 // general plot for SPP TLT bits of 3. word of tlt bits after prescale
  TH1D  *fGeneralTLT_DIS_after_prescale;                 // general plot for DIS TLT bits of 4. and 11. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HPP_after_prescale;                 // general plot for HPP TLT bits of 5. and 12. word of tlt bits after prescale
  TH1D  *fGeneralTLT_EXO_after_prescale;                 // general plot for EXO TLT bits of 6. and 13. word of tlt bits after prescale
  TH1D  *fGeneralTLT_MUO_after_prescale;                 // general plot for MUO TLT bits of 7. word of tlt bits after prescale
  TH1D  *fGeneralTLT_VTX_after_prescale;                 // general plot for VTX TLT bits of 8. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HFM_after_prescale;                 // general plot for HFM TLT bits of 9. and 15. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HFL_after_prescale;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale

  TH1D  *fGeneralTLT_HFL_after_prescale_lu_is;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale _low mass unlike sign_isolated
  TH1D  *fGeneralTLT_HFL_after_prescale_ll_is;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale _l like sign_is
  TH1D  *fGeneralTLT_HFL_after_prescale_hu_is;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale _high u_is
  TH1D  *fGeneralTLT_HFL_after_prescale_hl_is;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale _hl_is
  TH1D  *fGeneralTLT_HFL_after_prescale_lu_nis;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale _lu_non-isolated
  TH1D  *fGeneralTLT_HFL_after_prescale_ll_nis;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale	_ll_nis
  TH1D  *fGeneralTLT_HFL_after_prescale_hu_nis;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale	_hu_nis
  TH1D  *fGeneralTLT_HFL_after_prescale_hl_nis;                 // general plot for HFL TLT bits of 10. and 14. word of tlt bits after prescale	_hl_nis

  TH1D  *fGeneralFirstDST;                               // general plot of first word of dst bits
  TH1D  *fGeneralSecondDST;                              // general plot of second word of dst bits
  TH1D  *fGeneralThirdDST;                               // general plot of third word of dst bits
  TH1D  *fGeneralFourthDST;                              // general plot of fourth word of dst bits

  TH1D  *fGeneralFLT_ExclTrigCuts;                       // general plot exluding trigger cuts of flt bits
  TH1D  *fGeneralFLT_AfterPrescale_ExclTrigCuts;         // general plot exluding trigger cuts of flt bits after prescale

  TH1D  *fGeneralSLT_1_ExclTrigCuts;                     // general plot exluding trigger cuts of 1. word of slt bits
  TH1D  *fGeneralSLT_2_ExclTrigCuts;                     // general plot exluding trigger cuts of 2. word of slt bits
  TH1D  *fGeneralSLT_3_ExclTrigCuts;                     // general plot exluding trigger cuts of 3. word of slt bits
  TH1D  *fGeneralSLT_4_ExclTrigCuts;                     // general plot exluding trigger cuts of 4. word of slt bits
  TH1D  *fGeneralSLT_5_ExclTrigCuts;                     // general plot exluding trigger cuts of 5. word of slt bits
  TH1D  *fGeneralSLT_6_ExclTrigCuts;                     // general plot exluding trigger cuts of 6. word of slt bits

  TH1D  *fGeneralTLT_SPP_ExclTrigCuts;                   // general plot exluding trigger cuts for SPP TLT bits of 3. word of tlt bits
  TH1D  *fGeneralTLT_DIS_ExclTrigCuts;                   // general plot exluding trigger cuts for DIS TLT bits of 4. and 11. word of tlt bits
  TH1D  *fGeneralTLT_HPP_ExclTrigCuts;                   // general plot exluding trigger cuts for HPP TLT bits of 5. and 12. word of tlt bits
  TH1D  *fGeneralTLT_EXO_ExclTrigCuts;                   // general plot exluding trigger cuts for EXO TLT bits of 6. and 13. word of tlt bits
  TH1D  *fGeneralTLT_MUO_ExclTrigCuts;                   // general plot exluding trigger cuts for MUO TLT bits of 7. word of tlt bits
  TH1D  *fGeneralTLT_VTX_ExclTrigCuts;                   // general plot exluding trigger cuts for VTX TLT bits of 8. word of tlt bits
  TH1D  *fGeneralTLT_HFM_ExclTrigCuts;                   // general plot exluding trigger cuts for HFM TLT bits of 9. and 15. word of tlt bits
  TH1D  *fGeneralTLT_HFL_ExclTrigCuts;                   // general plot exluding trigger cuts for HFL TLT bits of 10. and 14. word of tlt bits

  TH1D  *fGeneralTLT_SPP_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for SPP TLT bits of 3. word of tlt bits after prescale
  TH1D  *fGeneralTLT_DIS_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for DIS TLT bits of 4. and 11. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HPP_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for HPP TLT bits of 5. and 12. word of tlt bits after prescale
  TH1D  *fGeneralTLT_EXO_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for EXO TLT bits of 6. and 13. word of tlt bits after prescale
  TH1D  *fGeneralTLT_MUO_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for MUO TLT bits of 7. word of tlt bits after prescale
  TH1D  *fGeneralTLT_VTX_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for VTX TLT bits of 8. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HFM_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for HFM TLT bits of 9. and 15. word of tlt bits after prescale
  TH1D  *fGeneralTLT_HFL_after_prescale_ExclTrigCuts;    // general plot exluding trigger cuts for HFL TLT bits of 10. and 14. word of tlt bits after prescale

  TH1D  *fGeneralFirstDST_ExclTrigCuts;                  // general plot exluding trigger cuts of first word of dst bits
  TH1D  *fGeneralSecondDST_ExclTrigCuts;                 // general plot exluding trigger cuts of second word of dst bits
  TH1D  *fGeneralThirdDST_ExclTrigCuts;                  // general plot exluding trigger cuts of third word of dst bits
  TH1D  *fGeneralFourthDST_ExclTrigCuts;                 // general plot exluding trigger cuts of fourth word of dst bits

  TH1D  *fGeneralFLT30Low;                               // general plot of events triggering FLT slot 30 in LOW configuration
  TH1D  *fGeneralFLT30LowForward;                        // general plot of events triggering FLT slot 30 in LOW configuration where the chosen muon is a forward muon
  TH1D  *fGeneralFLT30LowBarrel;                         // general plot of events triggering FLT slot 30 in LOW configuration where the chosen muon is a barrel muon
  TH1D  *fGeneralFLT30LowRear;                           // general plot of events triggering FLT slot 30 in LOW configuration where the chosen muon is a rear muon
  TH1D  *fGeneralFLT30;                                  // general plot of events triggering FLT slot 30
  TH1D  *fGeneralFLT30Forward;                           // general plot of events triggering FLT slot 30 where the chosen muon is a forward muon
  TH1D  *fGeneralFLT30Barrel;                            // general plot of events triggering FLT slot 30 where the chosen muon is a barrel muon
  TH1D  *fGeneralFLT30Rear;                              // general plot of events triggering FLT slot 30 where the chosen muon is a rear muon
  TH1D  *fGeneralFLT51Low;                               // general plot of events triggering FLT slot 51 and FLT 30 in LOW configuration
  TH1D  *fGeneralFLT51LowForward;                        // general plot of events triggering FLT slot 51 and FLT 30 in LOW configuration where the chosen muon is a forward muon
  TH1D  *fGeneralFLT51LowBarrel;                         // general plot of events triggering FLT slot 51 and FLT 30 in LOW configuration where the chosen muon is a barrel muon
  TH1D  *fGeneralFLT51LowRear;                           // general plot of events triggering FLT slot 51 and FLT 30 in LOW configuration where the chosen muon is a rear muon

  TH1D  *fGeneralFLT9_15;                                // general plot of events triggering OR of FLT slots 9,10,11,14,15 
  TH1D  *fGeneralFLT9_15Forward;                         // general plot of events triggering OR of FLT slots 9,10,11,14,15 where the chosen muon is a forward muon
  TH1D  *fGeneralFLT9_15Barrel;                          // general plot of events triggering OR of FLT slots 9,10,11,14,15 where the chosen muon is a barrel muon
  TH1D  *fGeneralFLT9_15Rear;                            // general plot of events triggering OR of FLT slots 9,10,11,14,15 where the chosen muon is a rear muon

  TH1D  *fGeneralFLTCombination;                         // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and FLT 30
  TH1D  *fGeneralFLTCombinationForward;                  // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and FLT 30 where the chosen muon is a forward muon
  TH1D  *fGeneralFLTCombinationBarrel;                   // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and FLT 30 where the chosen muon is a barrel muon
  TH1D  *fGeneralFLTCombinationRear;                     // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and FLT 30 where the chosen muon is a rear muon

  TH1D  *fGeneralFLTCombination2;                        // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and OR of FLT slots 9,10,11,14,15
  TH1D  *fGeneralFLTCombination2Forward;                 // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and OR of FLT slots 9,10,11,14,15 where the chosen muon is a forward muon
  TH1D  *fGeneralFLTCombination2Barrel;                  // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and OR of FLT slots 9,10,11,14,15 where the chosen muon is a barrel muon
  TH1D  *fGeneralFLTCombination2Rear;                    // general plot of events fulfilling OR of FLT slots 42,44,51,52,53,54 and OR of FLT slots 9,10,11,14,15 where the chosen muon is a rear muon

  TH1D  *fGeneralFLTCheck;                               // check how many events do not fulfill OR of FLT 10,11,42,44,51,52,53,54
  
  TH1D  *fGeneralZesSelect;                              // general plot of zes_select variable
  TH1D  *fGeneralDijetPHPTriggerCombinations;            // plot with all possible trigger combinations for dijet in PHP analysis
  TH1D  *  fGeneralDijetPHPTriggerCombinations_special;    // trigger for dijet in PHP swiched off different hpp14 combinations just plot the sum
  TH1D  *fGeneralDijetPHPTriggerCombinations_after_prescale; // plot with all possible trigger combinations for dijet in PHP analysis after prescale
  TH1D *fGeneralDijetPHPTrigger;                        // trigger plot for dijet trigger analysis
 
  // trigger logic flags 
  Bool_t fHadronTriggered;                               // a hadron  trigger from Ingos trigger selection has fired.
  Bool_t fMuonTriggered;                                 // a muon    trigger from Ingos trigger selection has fired.
  Bool_t fFMuonTriggered;                                // a Fmuon   trigger from Ingos trigger selection has fired.
  Bool_t fDISTLTTriggered;                               // a DIS TLT trigger from Ingos trigger selection has fired.
  Bool_t fDiJetOnlyMuonTriggered;                        // muon only triggered by muo3,exo11,exo12, 
  Bool_t fHpp_trig;                               // dijet analysis flags
  Bool_t fHfl_trig;                               // dijet analysis flags
  Bool_t fMuo_trig;                               // dijet analysis flags
  Bool_t fMuo3    ;                               // dijet analysis flags
  Bool_t fExo11   ;                               // dijet analysis flags
  Bool_t fExo12   ;                               // dijet analysis flags
 
  // cut flags
  Bool_t fCutTLTEXO96p00p;                               // flag if event fulfills TLTEXO96p00p cuts (for description look in GCards)
  Bool_t fCutTLTEXO03p04p;                               // flag if event fulfills TLTEXO03p04p cuts (for description look in GCards)
  Bool_t fCutTLTEXO05e06e;                               // flag if event fulfills TLTEXO05e06e cuts (for description look in GCards)
  Bool_t fCutTLTEXO06p07p;                               // flag if event fulfills TLTEXO06p07p cuts (for description look in GCards)
  Bool_t fCutTLTHPP96p00p;                               // flag if event fulfills TLTHPP96p00p cuts (for description look in GCards)
  Bool_t fCutTLTHPP03p04p;                               // flag if event fulfills TLTHPP03p04p cuts (for description look in GCards)
  Bool_t fCutTLTHPP05e06e;                               // flag if event fulfills TLTHPP05e06e cuts (for description look in GCards)
  Bool_t fCutTLTHPP06p07p;                               // flag if event fulfills TLTHPP06p07p cuts (for description look in GCards)
  Bool_t fCutTLTHFL96p00p;                               // flag if event fulfills TLTHFL96p00p cuts (for description look in GCards)
  Bool_t fCutTLTHFL99p00p;                               // flag if event fulfills TLTHFL99p00p cuts (for description look in GCards)
  Bool_t fCutTLTHFL03p04p;                               // flag if event fulfills TLTHFL03p04p cuts (for description look in GCards)
  Bool_t fCutTLTHFL05e06e;                               // flag if event fulfills TLTHFL05e06e cuts (for description look in GCards)
  Bool_t fCutTLTHFL06p07p;                               // flag if event fulfills TLTHFL06p07p cuts (for description look in GCards)
  Bool_t fCutTLTDIS96p00p;                               // flag if event fulfills TLTDIS96p00p cuts (for description look in GCards)
  Bool_t fCutTLTDIS03p04p;                               // flag if event fulfills TLTDIS03p04p cuts (for description look in GCards)
  Bool_t fCutTLTDIS05e06e;                               // flag if event fulfills TLTDIS05e06e cuts (for description look in GCards)
  Bool_t fCutTLTDIS06p07p;                               // flag if event fulfills TLTDIS06p07p cuts (for description look in GCards)
  Bool_t fCutTLTMUO96p00p;                               // flag if event fulfills TLTMUO96p00p cuts (for description look in GCards)
  Bool_t fCutTLTMUO03p04p;                               // flag if event fulfills TLTMUO03p04p cuts (for description look in GCards)
  Bool_t fCutTLTMUO05e06e;                               // flag if event fulfills TLTMUO05e06e cuts (for description look in GCards)
  Bool_t fCutTLTMUO06p07p;                               // flag if event fulfills TLTMUO06p07p cuts (for description look in GCards)
  Bool_t fCutTLTSPP03p04p;                               // flag if event fulfills TLTSPP03p04p cuts (for description look in GCards)
  Bool_t fCutTLTSPP05e06e;                               // flag if event fulfills TLTSPP05e06e cuts (for description look in GCards)
  Bool_t fCutTLTSPP06p07p;                               // flag if event fulfills TLTSPP06p07p cuts (for description look in GCards)
  Bool_t fCutAllCuts;                                    // flag if event fulfills all cuts

 public:
  GTrigger();
  virtual ~GTrigger();

  virtual Bool_t CreateControl();
  virtual Bool_t FillControl();

  virtual Bool_t CreateGeneral();
  virtual Bool_t FillGeneral();

  virtual Bool_t Do();

  virtual Bool_t Reset();

  virtual Bool_t CheckHadronOrMuonTrigger();

  virtual Bool_t CheckCutTLTEXO96p00p();
  virtual Bool_t CheckCutTLTEXO03p04p(); 
  virtual Bool_t CheckCutTLTEXO05e06e();
  virtual Bool_t CheckCutTLTEXO06p07p();
  virtual Bool_t CheckCutTLTHPP96p00p();
  virtual Bool_t CheckCutTLTHPP03p04p(); 
  virtual Bool_t CheckCutTLTHPP05e06e();
  virtual Bool_t CheckCutTLTHPP06p07p();
  virtual Bool_t CheckCutTLTHFL96p00p();
  virtual Bool_t CheckCutTLTHFL99p00p();
  virtual Bool_t CheckCutTLTHFL03p04p();
  virtual Bool_t CheckCutTLTHFL05e06e();
  virtual Bool_t CheckCutTLTHFL06p07p();
  virtual Bool_t CheckCutTLTDIS96p00p();
  virtual Bool_t CheckCutTLTDIS03p04p(); 
  virtual Bool_t CheckCutTLTDIS05e06e();
  virtual Bool_t CheckCutTLTDIS06p07p();
  virtual Bool_t CheckCutTLTMUO96p00p();
  virtual Bool_t CheckCutTLTMUO03p04p();
  virtual Bool_t CheckCutTLTMUO05e06e();
  virtual Bool_t CheckCutTLTMUO06p07p();
  virtual Bool_t CheckCutTLTSPP03p04p();
  virtual Bool_t CheckCutTLTSPP05e06e();
  virtual Bool_t CheckCutTLTSPP06p07p();
  virtual Bool_t CheckDiJetTrigger();
  virtual Bool_t CheckAllCuts();

  virtual Bool_t GetAllCuts();

  inline virtual Int_t  GetHadronTriggered()                { return fHadronTriggered;                } 
  inline virtual Int_t  GetMuonTriggered()                  { return fMuonTriggered;                  } 
  inline virtual Int_t  GetFMuonTriggered()                 { return fFMuonTriggered;                 } 
  inline virtual Int_t  GetDISTLTTriggered()                { return fDISTLTTriggered;                }

  virtual Bool_t EventTriggeredByTLTSPP();
  virtual Bool_t EventTriggeredByTLTVTX();
  virtual Bool_t EventTriggeredByTLTHPP();
  virtual Bool_t EventTriggeredByTLTDIS();
  virtual Bool_t EventTriggeredByTLTHPP(Int_t slot);
  virtual Bool_t EventTriggeredByTLTHFL(Int_t slot);
  virtual Bool_t EventTriggeredByTLTEXO(Int_t slot);
  virtual Bool_t EventTriggeredByTLTDIS(Int_t slot);
  virtual Bool_t EventTriggeredByTLTMUO(Int_t slot);

  virtual Double_t GetWeight();

  virtual Bool_t FillBitIntoHistogram(TH1D* histo, Int_t number, UInt_t bit, Int_t bitoffset = 0, Int_t filloffset = 0, Double_t weight = 1.0);

  ClassDef(GTrigger,0) // Trigger Class for everything which is related only to Trigger issues
};

R__EXTERN GTrigger *gTrigger;

#endif
