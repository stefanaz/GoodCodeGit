//
// GTrigger.cxx
//
// $Author: meyer $
// $Date: 2007/04/24 08:29:05 $
// $Revision: 1.31 $
//

#include <GTrigger.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTrigger)
#endif

GTrigger *gTrigger = 0;

//_____________________________________________________________
// GTrigger
// Trigger Class for everything which is related only to Trigger
//
//
GTrigger::GTrigger() : GPhysObj() {
  //
  // GTrigger default constructor
  if ( gDebug ) cout << endl << "GTrigger::GTrigger ctor called" << endl << endl;

  // initialize global pointer
  gTrigger = this;

  // initialize control histograms
  fControlFLT_uncut = 0;
  fControlFLT_AfterPrescale_uncut = 0;

  fControlSLT_1_uncut = 0;
  fControlSLT_2_uncut = 0;
  fControlSLT_3_uncut = 0;
  fControlSLT_4_uncut = 0;
  fControlSLT_5_uncut = 0;
  fControlSLT_6_uncut = 0;

  fControlTLT_SPP_uncut = 0;
  fControlTLT_DIS_uncut = 0;
  fControlTLT_HPP_uncut = 0;
  fControlTLT_EXO_uncut = 0;
  fControlTLT_MUO_uncut = 0;
  fControlTLT_VTX_uncut = 0;
  fControlTLT_HFM_uncut = 0;
  fControlTLT_HFL_uncut = 0;

  fControlTLT_SPP_after_prescale_uncut = 0;
  fControlTLT_DIS_after_prescale_uncut = 0;
  fControlTLT_HPP_after_prescale_uncut = 0;
  fControlTLT_EXO_after_prescale_uncut = 0;
  fControlTLT_MUO_after_prescale_uncut = 0;
  fControlTLT_VTX_after_prescale_uncut = 0;
  fControlTLT_HFM_after_prescale_uncut = 0;
  fControlTLT_HFL_after_prescale_uncut = 0;

  fControlFirstDST_uncut = 0;
  fControlSecondDST_uncut = 0;
  fControlThirdDST_uncut = 0;
  fControlFourthDST_uncut = 0;

  fControlZesSelect_uncut = 0;

  fControlFLT = 0;
  fControlFLT_AfterPrescale = 0;

  fControlSLT_1 = 0;
  fControlSLT_2 = 0;
  fControlSLT_3 = 0;
  fControlSLT_4 = 0;
  fControlSLT_5 = 0;
  fControlSLT_6 = 0;

  fControlTLT_SPP = 0;
  fControlTLT_DIS = 0;
  fControlTLT_HPP = 0;
  fControlTLT_EXO = 0;
  fControlTLT_MUO = 0;
  fControlTLT_VTX = 0;
  fControlTLT_HFM = 0;
  fControlTLT_HFL = 0;

  fControlTLT_SPP_after_prescale = 0;
  fControlTLT_DIS_after_prescale = 0;
  fControlTLT_HPP_after_prescale = 0;
  fControlTLT_EXO_after_prescale = 0;
  fControlTLT_MUO_after_prescale = 0;
  fControlTLT_VTX_after_prescale = 0;
  fControlTLT_HFM_after_prescale = 0;
  fControlTLT_HFL_after_prescale = 0;

  fControlFirstDST = 0;
  fControlSecondDST = 0;
  fControlThirdDST = 0;
  fControlFourthDST = 0;

  fControlZesSelect = 0;

  // initialize general histograms
  fGeneralFLT_uncut = 0;
  fGeneralFLT_AfterPrescale_uncut = 0;

  fGeneralSLT_1_uncut = 0;
  fGeneralSLT_2_uncut = 0;
  fGeneralSLT_3_uncut = 0;
  fGeneralSLT_4_uncut = 0;
  fGeneralSLT_5_uncut = 0;
  fGeneralSLT_6_uncut = 0;

  fGeneralTLT_SPP_uncut = 0;
  fGeneralTLT_DIS_uncut = 0;
  fGeneralTLT_HPP_uncut = 0;
  fGeneralTLT_EXO_uncut = 0;
  fGeneralTLT_MUO_uncut = 0;
  fGeneralTLT_VTX_uncut = 0;
  fGeneralTLT_HFM_uncut = 0;
  fGeneralTLT_HFL_uncut = 0;

  fGeneralTLT_SPP_after_prescale_uncut = 0;
  fGeneralTLT_DIS_after_prescale_uncut = 0;
  fGeneralTLT_HPP_after_prescale_uncut = 0;
  fGeneralTLT_EXO_after_prescale_uncut = 0;
  fGeneralTLT_MUO_after_prescale_uncut = 0;
  fGeneralTLT_VTX_after_prescale_uncut = 0;
  fGeneralTLT_HFM_after_prescale_uncut = 0;
  fGeneralTLT_HFL_after_prescale_uncut = 0;

  fGeneralFirstDST_uncut = 0;
  fGeneralSecondDST_uncut = 0;
  fGeneralThirdDST_uncut = 0;
  fGeneralFourthDST_uncut = 0;

  fGeneralZesSelect_uncut = 0;

  fGeneralFLT = 0;
  fGeneralFLT_AfterPrescale = 0;

  fGeneralSLT_1 = 0;
  fGeneralSLT_2 = 0;
  fGeneralSLT_3 = 0;
  fGeneralSLT_4 = 0;
  fGeneralSLT_5 = 0;
  fGeneralSLT_6 = 0;

  fGeneralTLT_SPP = 0;
  fGeneralTLT_DIS = 0;
  fGeneralTLT_HPP = 0;
  fGeneralTLT_EXO = 0;
  fGeneralTLT_MUO = 0;
  fGeneralTLT_VTX = 0;
  fGeneralTLT_HFM = 0;
  fGeneralTLT_HFL = 0;

  fGeneralTLT_SPP_after_prescale = 0;
  fGeneralTLT_DIS_after_prescale = 0;
  fGeneralTLT_HPP_after_prescale = 0;
  fGeneralTLT_EXO_after_prescale = 0;
  fGeneralTLT_MUO_after_prescale = 0;
  fGeneralTLT_VTX_after_prescale = 0;
  fGeneralTLT_HFM_after_prescale = 0;
  fGeneralTLT_HFL_after_prescale = 0;

  fGeneralTLT_HFL_after_prescale_lu_is = 0;
  fGeneralTLT_HFL_after_prescale_ll_is = 0;
  fGeneralTLT_HFL_after_prescale_hu_is = 0;
  fGeneralTLT_HFL_after_prescale_hl_is = 0;
  fGeneralTLT_HFL_after_prescale_lu_nis = 0;
  fGeneralTLT_HFL_after_prescale_ll_nis = 0;
  fGeneralTLT_HFL_after_prescale_hu_nis = 0;
  fGeneralTLT_HFL_after_prescale_hl_nis = 0;

  fGeneralFirstDST = 0;
  fGeneralSecondDST = 0;
  fGeneralThirdDST = 0;
  fGeneralFourthDST = 0;

  fGeneralFLT_ExclTrigCuts = 0;
  fGeneralFLT_AfterPrescale_ExclTrigCuts = 0;

  fGeneralSLT_1_ExclTrigCuts = 0;
  fGeneralSLT_2_ExclTrigCuts = 0;
  fGeneralSLT_3_ExclTrigCuts = 0;
  fGeneralSLT_4_ExclTrigCuts = 0;
  fGeneralSLT_5_ExclTrigCuts = 0;
  fGeneralSLT_6_ExclTrigCuts = 0;

  fGeneralTLT_SPP_ExclTrigCuts = 0;
  fGeneralTLT_DIS_ExclTrigCuts = 0;
  fGeneralTLT_HPP_ExclTrigCuts = 0;
  fGeneralTLT_EXO_ExclTrigCuts = 0;
  fGeneralTLT_MUO_ExclTrigCuts = 0;
  fGeneralTLT_VTX_ExclTrigCuts = 0;
  fGeneralTLT_HFM_ExclTrigCuts = 0;
  fGeneralTLT_HFL_ExclTrigCuts = 0;

  fGeneralTLT_SPP_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_DIS_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_HPP_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_EXO_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_MUO_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_VTX_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_HFM_after_prescale_ExclTrigCuts = 0;
  fGeneralTLT_HFL_after_prescale_ExclTrigCuts = 0;

  fGeneralFirstDST_ExclTrigCuts = 0;
  fGeneralSecondDST_ExclTrigCuts = 0;
  fGeneralThirdDST_ExclTrigCuts = 0;
  fGeneralFourthDST_ExclTrigCuts = 0;

  fGeneralFLT30Low = 0;
  fGeneralFLT30LowForward = 0;
  fGeneralFLT30LowBarrel = 0;
  fGeneralFLT30LowRear = 0;
  fGeneralFLT30 = 0;
  fGeneralFLT30Forward = 0;
  fGeneralFLT30Barrel = 0;
  fGeneralFLT30Rear = 0;
  fGeneralFLT51Low = 0;
  fGeneralFLT51LowForward = 0;
  fGeneralFLT51LowBarrel = 0;
  fGeneralFLT51LowRear = 0;

  fGeneralFLT9_15 = 0;
  fGeneralFLT9_15Forward = 0;
  fGeneralFLT9_15Barrel = 0;
  fGeneralFLT9_15Rear = 0;

  fGeneralFLTCombination = 0;
  fGeneralFLTCombinationForward = 0;
  fGeneralFLTCombinationBarrel = 0;
  fGeneralFLTCombinationRear = 0;

  fGeneralFLTCombination2 = 0;
  fGeneralFLTCombination2Forward = 0;
  fGeneralFLTCombination2Barrel = 0;
  fGeneralFLTCombination2Rear = 0;

  fGeneralFLTCheck = 0;


  fGeneralZesSelect = 0;

  fGeneralDijetPHPTriggerCombinations = 0;
  fGeneralDijetPHPTriggerCombinations_special = 0;
  fGeneralDijetPHPTrigger = 0;

  // init trigger logic flags
  fHadronTriggered = kFALSE;                               // a hadron trigger from Ingos trigger selection has fired.
  fMuonTriggered   = kFALSE;                               // a muon   trigger from Ingos trigger selection has fired.
  fFMuonTriggered  = kFALSE;                               // a Fmuon  trigger from Ingos trigger selection has fired.
  fDISTLTTriggered = kFALSE;                               // a DIS TLT trigger from Ingos trigger selection has fired.
  fDiJetOnlyMuonTriggered = kFALSE;                        // muon only triggered by muo3,exo11,exo12,
  fHpp_trig = kFALSE;                               // dijet analysis flags
  fHfl_trig = kFALSE;                               // dijet analysis flags
  fMuo_trig = kFALSE;                               // dijet analysis flags
  fMuo3     = kFALSE;                               // dijet analysis flags
  fExo11    = kFALSE;                               // dijet analysis flags
  fExo12    = kFALSE;                               // dijet analysis flags

  // init cut flags
  fCutTLTEXO96p00p = kFALSE;
  fCutTLTEXO03p04p = kFALSE;
  fCutTLTEXO05e06e = kFALSE;
  fCutTLTEXO06p07p = kFALSE;

  fCutTLTHPP96p00p = kFALSE;
  fCutTLTHPP03p04p = kFALSE;
  fCutTLTHPP05e06e = kFALSE;
  fCutTLTHPP06p07p = kFALSE;

  fCutTLTHFL96p00p = kFALSE;
  fCutTLTHFL99p00p = kFALSE;
  fCutTLTHFL03p04p = kFALSE;
  fCutTLTHFL05e06e = kFALSE;
  fCutTLTHFL06p07p = kFALSE;

  fCutTLTDIS96p00p = kFALSE;
  fCutTLTDIS03p04p = kFALSE;
  fCutTLTDIS05e06e = kFALSE;
  fCutTLTDIS06p07p = kFALSE;

  fCutTLTMUO96p00p = kFALSE;
  fCutTLTMUO03p04p = kFALSE;
  fCutTLTMUO05e06e = kFALSE;
  fCutTLTMUO06p07p = kFALSE;

  fCutTLTSPP03p04p = kFALSE;
  fCutTLTSPP05e06e = kFALSE;
  fCutTLTSPP06p07p = kFALSE;

  fCutAllCuts      = kFALSE;

  // create Histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GTrigger::~GTrigger() {
  //
  // GTrigger default destructor
  if ( gDebug ) cout << endl << "GTrigger::~GTrigger dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GTrigger::CreateControl() {
  //
  // create general histograms for trigger
  if ( gDebug ) cout << endl << "GTrigger::CreateControl() called" << endl << endl;

  if ( gCards->GetTriggerControl() ) {

    // dst histograms
    TString dst_first_labels = "";
    for ( Int_t i = 0; i < 32; ++i ) {
      dst_first_labels.Append("DST");
      if ( i < 10 ) {
	dst_first_labels.Append("00");
	dst_first_labels += i;
      } else if ( i < 100 ) {
	dst_first_labels.Append("0");
	dst_first_labels += i;
      } else {
	dst_first_labels += i;
      }
      if ( i != 31 ) 
	dst_first_labels.Append(",");
    }
    TString dst_second_labels = "";
    for ( Int_t i = 32; i < 64; ++i ) {
      dst_second_labels.Append("DST");
      if ( i < 10 ) {
	dst_second_labels.Append("00");
	dst_second_labels += i;
      } else if ( i < 100 ) {
	dst_second_labels.Append("0");
	dst_second_labels += i;
      } else {
	dst_second_labels += i;
      }
      if ( i != 63 ) 
	dst_second_labels.Append(",");
    }
    TString dst_third_labels = "";
    for ( Int_t i = 64; i < 96; ++i ) {
      dst_third_labels.Append("DST");
      if ( i < 10 ) {
	dst_third_labels.Append("00");
	dst_third_labels += i;
      } else if ( i < 100 ) {
	dst_third_labels.Append("0");
	dst_third_labels += i;
      } else {
	dst_third_labels += i;
      }
      if ( i != 95 ) 
	dst_third_labels.Append(",");
    }
    TString dst_fourth_labels = "";
    for ( Int_t i = 96; i < 128; ++i ) {
      dst_fourth_labels.Append("DST");
      if ( i < 10 ) {
	dst_fourth_labels.Append("00");
	dst_fourth_labels += i;
      } else if ( i < 100 ) {
	dst_fourth_labels.Append("0");
	dst_fourth_labels += i;
      } else {
	dst_fourth_labels += i;
      }
      if ( i != 127 ) 
	dst_fourth_labels.Append(",");
    }
    fControlFirstDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger_Control","FirstDST_uncut","uncut DST Bits 0 - 31",dst_first_labels.Data(),"","Events");
    fControlSecondDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger_Control","SecondDST_uncut","uncut DST Bits 32 - 63",dst_second_labels.Data(),"","Events");
    fControlThirdDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger_Control","ThirdDST_uncut","uncut DST Bits 64 - 95",dst_third_labels.Data(),"","Events");
    fControlFourthDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger_Control","ForthDST_uncut","uncut DST Bits 96 - 127",dst_fourth_labels.Data(),"","Events");
    fControlFirstDST = gHistogrammer->TH1DLabelFactory("Trigger_Control","FirstDST","DST Bits 0 - 31",dst_first_labels.Data(),"","Events");
    fControlSecondDST = gHistogrammer->TH1DLabelFactory("Trigger_Control","SecondDST","DST Bits 32 - 63",dst_second_labels.Data(),"","Events");
    fControlThirdDST = gHistogrammer->TH1DLabelFactory("Trigger_Control","ThirdDST","DST Bits 64 - 95",dst_third_labels.Data(),"","Events");
    fControlFourthDST = gHistogrammer->TH1DLabelFactory("Trigger_Control","ForthDST","DST Bits 96 - 127",dst_fourth_labels.Data(),"","Events");

    // zes select
    Int_t    zesselect_bins = 2;
    Double_t zesselect_low  = 0.;
    Double_t zesselect_high = 2.;
    fControlZesSelect_uncut = gHistogrammer->TH1DFactory("Trigger_Control","ZesSelect_uncut","uncut Number of events selected by ZES",zesselect_bins,zesselect_low,zesselect_high,"","Events");
    fControlZesSelect = gHistogrammer->TH1DFactory("Trigger_Control","ZesSelect","Number of events selected by ZES",zesselect_bins,zesselect_low,zesselect_high,"","Events");

    // flt histograms
    Int_t    flt_bins = 65;
    Double_t flt_low  = 0.;
    Double_t flt_high = 65.;
    fControlFLT_uncut = gHistogrammer->TH1DFactory("Trigger_Control","FLT_uncut","uncut FLT Bits",flt_bins,flt_low,flt_high,"FLT Slot","Events");
    fControlFLT_AfterPrescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","FLT_AfterPrescale_uncut","uncut FLT Bits after prescale",flt_bins,flt_low,flt_high,"FLT Slot","Events");
    fControlFLT = gHistogrammer->TH1DFactory("Trigger_Control","FLT","FLT Bits",flt_bins,flt_low,flt_high,"FLT Bits","Events");
    fControlFLT_AfterPrescale = gHistogrammer->TH1DFactory("Trigger_Control","FLT_AfterPrescale","FLT Bits after prescale",flt_bins,flt_low,flt_high,"FLT Slot","Events");
    
    // slt histograms
    Int_t    slt_bins = 33;
    Double_t slt_low  = 0.;
    Double_t slt_high = 33.;
    fControlSLT_1_uncut = gHistogrammer->TH1DFactory("Trigger_Control","SLT_1_uncut","uncut SLT Bits 1. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_2_uncut = gHistogrammer->TH1DFactory("Trigger_Control","SLT_2_uncut","uncut SLT Bits 2. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_3_uncut = gHistogrammer->TH1DFactory("Trigger_Control","SLT_3_uncut","uncut SLT Bits 3. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_4_uncut = gHistogrammer->TH1DFactory("Trigger_Control","SLT_4_uncut","uncut SLT Bits 4. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_5_uncut = gHistogrammer->TH1DFactory("Trigger_Control","SLT_5_uncut","uncut SLT Bits 5. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_6_uncut = gHistogrammer->TH1DFactory("Trigger_Control","SLT_6_uncut","uncut SLT Bits 6. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_1 = gHistogrammer->TH1DFactory("Trigger_Control","SLT_1","SLT Bits 1. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_2 = gHistogrammer->TH1DFactory("Trigger_Control","SLT_2","SLT Bits 2. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_3 = gHistogrammer->TH1DFactory("Trigger_Control","SLT_3","SLT Bits 3. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_4 = gHistogrammer->TH1DFactory("Trigger_Control","SLT_4","SLT Bits 4. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_5 = gHistogrammer->TH1DFactory("Trigger_Control","SLT_5","SLT Bits 5. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fControlSLT_6 = gHistogrammer->TH1DFactory("Trigger_Control","SLT_6","SLT Bits 6. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    
    
    // tlt histograms
    Int_t    single_tlt_bins = 17;
    Double_t single_tlt_low  = 1.;
    Double_t single_tlt_high = 18.;
    Int_t    double_tlt_bins = 33;
    Double_t double_tlt_low  = 1.;
    Double_t double_tlt_high = 34.;
   
 fControlTLT_SPP_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_SPP_uncut","uncut TLT SPP Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_DIS_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_DIS_uncut","uncut TLT DIS Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HPP_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HPP_uncut","uncut TLT HPP Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_EXO_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_EXO_uncut","uncut TLT EXO Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_MUO_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_MUO_uncut","uncut TLT MUO Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_VTX_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_VTX_uncut","uncut TLT VTX Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_HFM_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFM_uncut","uncut TLT SAP/HFM Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HFL_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFL_uncut","uncut TLT HFL Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_SPP_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_SPP_after_prescale_uncut","uncut TLT SPP Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_DIS_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_DIS_after_prescale_uncut","uncut TLT DIS Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HPP_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HPP_after_prescale_uncut","uncut TLT HPP Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_EXO_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_EXO_after_prescale_uncut","uncut TLT EXO Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_MUO_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_MUO_after_prescale_uncut","uncut TLT MUO Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_VTX_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_VTX_after_prescale_uncut","uncut TLT VTX Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_HFM_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFM_after_prescale_uncut","uncut TLT SAP/HFM Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HFL_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFL_after_prescale_uncut","uncut TLT HFL Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");

    fControlTLT_SPP = gHistogrammer->TH1DFactory("Trigger_Control","TLT_SPP","TLT SPP Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_DIS = gHistogrammer->TH1DFactory("Trigger_Control","TLT_DIS","TLT DIS Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HPP = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HPP","TLT HPP Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_EXO = gHistogrammer->TH1DFactory("Trigger_Control","TLT_EXO","TLT EXO Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_MUO = gHistogrammer->TH1DFactory("Trigger_Control","TLT_MUO","TLT MUO Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_VTX = gHistogrammer->TH1DFactory("Trigger_Control","TLT_VTX","TLT VTX Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_HFM = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFM","TLT SAP/HFM Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HFL = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFL","TLT HFL Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_SPP_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_SPP_after_prescale","TLT SPP Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_DIS_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_DIS_after_prescale","TLT DIS Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HPP_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HPP_after_prescale","TLT HPP Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_EXO_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_EXO_after_prescale","TLT EXO Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_MUO_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_MUO_after_prescale","TLT MUO Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_VTX_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_VTX_after_prescale","TLT VTX Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fControlTLT_HFM_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFM_after_prescale","TLT SAP/HFM Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fControlTLT_HFL_after_prescale = gHistogrammer->TH1DFactory("Trigger_Control","TLT_HFL_after_prescale","TLT HFL Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CreateGeneral() {
  //
  // create general histograms for trigger
  if ( gDebug ) cout << endl << "GTrigger::CreateGeneral() called" << endl << endl;

  if ( gCards->GetTriggerGeneral() ) {

    // dst histograms
    TString dst_first_labels = "";
    for ( Int_t i = 0; i < 32; ++i ) {
      dst_first_labels.Append("DST");
      if ( i < 10 ) {
	dst_first_labels.Append("00");
	dst_first_labels += i;
      } else if ( i < 100 ) {
	dst_first_labels.Append("0");
	dst_first_labels += i;
      } else {
	dst_first_labels += i;
      }
      if ( i != 31 ) 
	dst_first_labels.Append(",");
    }
    TString dst_second_labels = "";
    for ( Int_t i = 32; i < 64; ++i ) {
      dst_second_labels.Append("DST");
      if ( i < 10 ) {
	dst_second_labels.Append("00");
	dst_second_labels += i;
      } else if ( i < 100 ) {
	dst_second_labels.Append("0");
	dst_second_labels += i;
      } else {
	dst_second_labels += i;
      }
      if ( i != 63 ) 
	dst_second_labels.Append(",");
    }
    TString dst_third_labels = "";
    for ( Int_t i = 64; i < 96; ++i ) {
      dst_third_labels.Append("DST");
      if ( i < 10 ) {
	dst_third_labels.Append("00");
	dst_third_labels += i;
      } else if ( i < 100 ) {
	dst_third_labels.Append("0");
	dst_third_labels += i;
      } else {
	dst_third_labels += i;
      }
      if ( i != 95 ) 
	dst_third_labels.Append(",");
    }
    TString dst_fourth_labels = "";
    for ( Int_t i = 96; i < 128; ++i ) {
      dst_fourth_labels.Append("DST");
      if ( i < 10 ) {
	dst_fourth_labels.Append("00");
	dst_fourth_labels += i;
      } else if ( i < 100 ) {
	dst_fourth_labels.Append("0");
	dst_fourth_labels += i;
      } else {
	dst_fourth_labels += i;
      }
      if ( i != 127 ) 
	dst_fourth_labels.Append(",");
    }
    Int_t    zesselect_bins = 2;
    Double_t zesselect_low  = 0.;
    Double_t zesselect_high = 2.;
    Int_t    flt_bins = 65;
    Double_t flt_low  = 0.;
    Double_t flt_high = 65.;
    Int_t    slt_bins = 33;
    Double_t slt_low  = 0.;
    Double_t slt_high = 33.;
    Int_t    single_tlt_bins = 17;
    Double_t single_tlt_low  = 1.;
    Double_t single_tlt_high = 18.;
    Int_t    double_tlt_bins = 33;
    Double_t double_tlt_low  = 1.;
    Double_t double_tlt_high = 34.;
    Int_t    fltspecialbins  = 1;
    Double_t fltspeciallow   = 0.;
    Double_t fltspecialhigh  = 1.;

    // uncut
    fGeneralZesSelect_uncut = gHistogrammer->TH1DFactory("Trigger","ZesSelect_uncut","uncut Number of events selected by ZES",zesselect_bins,zesselect_low,zesselect_high,"","Events");

    fGeneralFirstDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger","FirstDST_uncut","uncut DST Bits 0 - 31",dst_first_labels.Data(),"","Events");
    fGeneralSecondDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger","SecondDST_uncut","uncut DST Bits 32 - 63",dst_second_labels.Data(),"","Events");
    fGeneralThirdDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger","ThirdDST_uncut","uncut DST Bits 64 - 95",dst_third_labels.Data(),"","Events");
    fGeneralFourthDST_uncut = gHistogrammer->TH1DLabelFactory("Trigger","ForthDST_uncut","uncut DST Bits 96 - 127",dst_fourth_labels.Data(),"","Events");

    fGeneralFLT_uncut = gHistogrammer->TH1DFactory("Trigger","FLT_uncut","uncut FLT Bits",flt_bins,flt_low,flt_high,"FLT Slot","Events");
    fGeneralFLT_AfterPrescale_uncut = gHistogrammer->TH1DFactory("Trigger","FLT_AfterPrescale_uncut","uncut FLT Bits after prescale",flt_bins,flt_low,flt_high,"FLT Slot","Events");

    fGeneralSLT_1_uncut = gHistogrammer->TH1DFactory("Trigger","SLT_1_uncut","uncut SLT Bits 1. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_2_uncut = gHistogrammer->TH1DFactory("Trigger","SLT_2_uncut","uncut SLT Bits 2. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_3_uncut = gHistogrammer->TH1DFactory("Trigger","SLT_3_uncut","uncut SLT Bits 3. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_4_uncut = gHistogrammer->TH1DFactory("Trigger","SLT_4_uncut","uncut SLT Bits 4. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_5_uncut = gHistogrammer->TH1DFactory("Trigger","SLT_5_uncut","uncut SLT Bits 5. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_6_uncut = gHistogrammer->TH1DFactory("Trigger","SLT_6_uncut","uncut SLT Bits 6. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");

    fGeneralTLT_SPP_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_SPP_uncut","uncut TLT SPP Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_DIS_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_DIS_uncut","uncut TLT DIS Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HPP_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_HPP_uncut","uncut TLT HPP Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_EXO_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_EXO_uncut","uncut TLT EXO Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_MUO_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_MUO_uncut","uncut TLT MUO Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_VTX_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_VTX_uncut","uncut TLT VTX Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFM_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_HFM_uncut","uncut TLT SAP/HFM Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFL_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_uncut","uncut TLT HFL Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_SPP_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_SPP_after_prescale_uncut","uncut TLT SPP Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_DIS_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_DIS_after_prescale_uncut","uncut TLT DIS Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HPP_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_HPP_after_prescale_uncut","uncut TLT HPP Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_EXO_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_EXO_after_prescale_uncut","uncut TLT EXO Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_MUO_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_MUO_after_prescale_uncut","uncut TLT MUO Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_VTX_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_VTX_after_prescale_uncut","uncut TLT VTX Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFM_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_HFM_after_prescale_uncut","uncut TLT SAP/HFM Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFL_after_prescale_uncut = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_uncut","uncut TLT HFL Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");

    // after cuts
    fGeneralFirstDST = gHistogrammer->TH1DLabelFactory("Trigger","FirstDST","DST Bits 0 - 31",dst_first_labels.Data(),"","Events");
    fGeneralSecondDST = gHistogrammer->TH1DLabelFactory("Trigger","SecondDST","DST Bits 32 - 63",dst_second_labels.Data(),"","Events");
    fGeneralThirdDST = gHistogrammer->TH1DLabelFactory("Trigger","ThirdDST","DST Bits 64 - 95",dst_third_labels.Data(),"","Events");
    fGeneralFourthDST = gHistogrammer->TH1DLabelFactory("Trigger","ForthDST","DST Bits 96 - 127",dst_fourth_labels.Data(),"","Events");

    fGeneralFLT = gHistogrammer->TH1DFactory("Trigger","FLT","FLT Bits",flt_bins,flt_low,flt_high,"FLT Bits","Events");
    fGeneralFLT_AfterPrescale = gHistogrammer->TH1DFactory("Trigger","FLT_AfterPrescale","FLT Bits after prescale",flt_bins,flt_low,flt_high,"FLT Slot","Events");
    
    fGeneralSLT_1 = gHistogrammer->TH1DFactory("Trigger","SLT_1","SLT Bits 1. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_2 = gHistogrammer->TH1DFactory("Trigger","SLT_2","SLT Bits 2. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_3 = gHistogrammer->TH1DFactory("Trigger","SLT_3","SLT Bits 3. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_4 = gHistogrammer->TH1DFactory("Trigger","SLT_4","SLT Bits 4. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_5 = gHistogrammer->TH1DFactory("Trigger","SLT_5","SLT Bits 5. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_6 = gHistogrammer->TH1DFactory("Trigger","SLT_6","SLT Bits 6. word",slt_bins,slt_low,slt_high,"SLT Slot","Events");

    fGeneralTLT_SPP = gHistogrammer->TH1DFactory("Trigger","TLT_SPP","TLT SPP Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_DIS = gHistogrammer->TH1DFactory("Trigger","TLT_DIS","TLT DIS Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HPP = gHistogrammer->TH1DFactory("Trigger","TLT_HPP","TLT HPP Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_EXO = gHistogrammer->TH1DFactory("Trigger","TLT_EXO","TLT EXO Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_MUO = gHistogrammer->TH1DFactory("Trigger","TLT_MUO","TLT MUO Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_VTX = gHistogrammer->TH1DFactory("Trigger","TLT_VTX","TLT VTX Bits",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFM = gHistogrammer->TH1DFactory("Trigger","TLT_HFM","TLT SAP/HFM Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFL = gHistogrammer->TH1DFactory("Trigger","TLT_HFL","TLT HFL Bits",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_SPP_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_SPP_after_prescale","TLT SPP Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_DIS_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_DIS_after_prescale","TLT DIS Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HPP_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_HPP_after_prescale","TLT HPP Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_EXO_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_EXO_after_prescale","TLT EXO Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_MUO_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_MUO_after_prescale","TLT MUO Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_VTX_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_VTX_after_prescale","TLT VTX Bits after prescale",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFM_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_HFM_after_prescale","TLT SAP/HFM Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFL_after_prescale = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale","TLT HFL Bits after prescale",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");

    fGeneralTLT_HFL_after_prescale_lu_is  = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_lu_is ","TLT HFL Bits after prescale_lu_is ",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_lu_is ","Events");
    fGeneralTLT_HFL_after_prescale_ll_is  = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_ll_is ","TLT HFL Bits after prescale_ll_is ",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_ll_is ","Events");
    fGeneralTLT_HFL_after_prescale_hu_is  = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_hu_is ","TLT HFL Bits after prescale_hu_is ",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_hu_is ","Events");
    fGeneralTLT_HFL_after_prescale_hl_is  = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_hl_is ","TLT HFL Bits after prescale_hl_is ",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_hl_is ","Events");
    fGeneralTLT_HFL_after_prescale_lu_nis = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_lu_nis","TLT HFL Bits after prescale_lu_nis",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_lu_nis","Events");
    fGeneralTLT_HFL_after_prescale_ll_nis = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_ll_nis","TLT HFL Bits after prescale_ll_nis",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_ll_nis","Events");
    fGeneralTLT_HFL_after_prescale_hu_nis = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_hu_nis","TLT HFL Bits after prescale_hu_nis",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_hu_nis","Events");
    fGeneralTLT_HFL_after_prescale_hl_nis = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_hl_nis","TLT HFL Bits after prescale_hl_nis",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot_hl_nis","Events");

    // after all cuts but before trigger cuts
    fGeneralFirstDST_ExclTrigCuts = gHistogrammer->TH1DLabelFactory("Trigger","FirstDST_ExclTrigCuts","DST Bits 0 - 31 excluding trigger cuts",dst_first_labels.Data(),"","Events");
    fGeneralSecondDST_ExclTrigCuts = gHistogrammer->TH1DLabelFactory("Trigger","SecondDST_ExclTrigCuts","DST Bits 32 - 63 excluding trigger cuts",dst_second_labels.Data(),"","Events");
    fGeneralThirdDST_ExclTrigCuts = gHistogrammer->TH1DLabelFactory("Trigger","ThirdDST_ExclTrigCuts","DST Bits 64 - 95 excluding trigger cuts",dst_third_labels.Data(),"","Events");
    fGeneralFourthDST_ExclTrigCuts = gHistogrammer->TH1DLabelFactory("Trigger","ForthDST_ExclTrigCuts","DST Bits 96 - 127 excluding trigger cuts",dst_fourth_labels.Data(),"","Events");

    fGeneralFLT_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","FLT_ExclTrigCuts","FLT Bits",flt_bins,flt_low,flt_high,"FLT Bits","Events");
    fGeneralFLT_AfterPrescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","FLT_AfterPrescale_ExclTrigCuts","FLT Bits after prescale",flt_bins,flt_low,flt_high,"FLT Slot","Events");
    
    fGeneralSLT_1_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","SLT_1_ExclTrigCuts","SLT Bits 1. word excluding trigger cuts",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_2_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","SLT_2_ExclTrigCuts","SLT Bits 2. word excluding trigger cuts",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_3_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","SLT_3_ExclTrigCuts","SLT Bits 3. word excluding trigger cuts",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_4_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","SLT_4_ExclTrigCuts","SLT Bits 4. word excluding trigger cuts",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_5_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","SLT_5_ExclTrigCuts","SLT Bits 5. word excluding trigger cuts",slt_bins,slt_low,slt_high,"SLT Slot","Events");
    fGeneralSLT_6_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","SLT_6_ExclTrigCuts","SLT Bits 6. word excluding trigger cuts",slt_bins,slt_low,slt_high,"SLT Slot","Events");

    fGeneralTLT_SPP_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_SPP_ExclTrigCuts","TLT SPP Bits excluding trigger cuts",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_DIS_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_DIS_ExclTrigCuts","TLT DIS Bits excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HPP_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_HPP_ExclTrigCuts","TLT HPP Bits excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_EXO_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_EXO_ExclTrigCuts","TLT EXO Bits excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_MUO_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_MUO_ExclTrigCuts","TLT MUO Bits excluding trigger cuts",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_VTX_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_VTX_ExclTrigCuts","TLT VTX Bits excluding trigger cuts",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFM_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_HFM_ExclTrigCuts","TLT SAP/HFM Bits excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFL_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_ExclTrigCuts","TLT HFL Bits excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_SPP_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_SPP_after_prescale_ExclTrigCuts","TLT SPP Bits after prescale excluding trigger cuts",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_DIS_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_DIS_after_prescale_ExclTrigCuts","TLT DIS Bits after prescale excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HPP_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_HPP_after_prescale_ExclTrigCuts","TLT HPP Bits after prescale excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_EXO_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_EXO_after_prescale_ExclTrigCuts","TLT EXO Bits after prescale excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_MUO_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_MUO_after_prescale_ExclTrigCuts","TLT MUO Bits after prescale excluding trigger cuts",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_VTX_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_VTX_after_prescale_ExclTrigCuts","TLT VTX Bits after prescale excluding trigger cuts",single_tlt_bins,single_tlt_low,single_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFM_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_HFM_after_prescale_ExclTrigCuts","TLT SAP/HFM Bits after prescale excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");
    fGeneralTLT_HFL_after_prescale_ExclTrigCuts = gHistogrammer->TH1DFactory("Trigger","TLT_HFL_after_prescale_ExclTrigCuts","TLT HFL Bits after prescale excluding trigger cuts",double_tlt_bins,double_tlt_low,double_tlt_high,"TLT Slot","Events");

    fGeneralZesSelect = gHistogrammer->TH1DFactory("Trigger","ZesSelect","Number of events selected by ZES",zesselect_bins,zesselect_low,zesselect_high,"","Events");

    fGeneralFLT30Low = gHistogrammer->TH1DFactory("Trigger","FLT30Low","Number of low lumi configuration events triggered by FLT 30",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");
    fGeneralFLT30LowForward = gHistogrammer->TH1DFactory("Trigger","FLT30LowForward","Number of low lumi configuration events triggered by FLT 30 with chosen forward muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");
    fGeneralFLT30LowBarrel = gHistogrammer->TH1DFactory("Trigger","FLT30LowBarrel","Number of low lumi configuration events triggered by FLT 30 with chosen barrel muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");
    fGeneralFLT30LowRear = gHistogrammer->TH1DFactory("Trigger","FLT30LowRear","Number of low lumi configuration events triggered by FLT 30 with chosen rear muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");

    fGeneralFLT30 = gHistogrammer->TH1DFactory("Trigger","FLT30","Number of events triggered by FLT 30",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");
    fGeneralFLT30Forward = gHistogrammer->TH1DFactory("Trigger","FLT30Forward","Number of events triggered by FLT 30 with chosen forward muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");
    fGeneralFLT30Barrel = gHistogrammer->TH1DFactory("Trigger","FLT30Barrel","Number of events triggered by FLT 30 with chosen barrel muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");
    fGeneralFLT30Rear = gHistogrammer->TH1DFactory("Trigger","FLT30Rear","Number of events triggered by FLT 30 with chosen rear muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30","Events");

    fGeneralFLT9_15 = gHistogrammer->TH1DFactory("Trigger","FLT9_15","Number of events triggered by OR of FLT 9,10,11,14,15",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 9,10,11,14,15","Events");
    fGeneralFLT9_15Forward = gHistogrammer->TH1DFactory("Trigger","FLT9_15Forward","Number of events triggered by OR of FLT 9,10,11,14,15 with chosen forward muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 9,10,11,14,15","Events");
    fGeneralFLT9_15Barrel = gHistogrammer->TH1DFactory("Trigger","FLT9_15Barrel","Number of events triggered by OR of FLT 9,10,11,14,15 with chosen barrel muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 9,10,11,14,15","Events");
    fGeneralFLT9_15Rear = gHistogrammer->TH1DFactory("Trigger","FLT9_15Rear","Number of events triggered by OR of FLT 9,10,11,14,15 with chosen rear muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 9,10,11,14,15","Events");

    fGeneralFLT51Low = gHistogrammer->TH1DFactory("Trigger","FLT51Low","Number of low lumi configuration events triggered by FLT 30 && 51",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30 && 51","Events");
    fGeneralFLT51LowForward = gHistogrammer->TH1DFactory("Trigger","FLT51LowForward","Number of low lumi configuration events triggered by FLT 30 && 51 with chosen forward muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30 && 51","Events");
    fGeneralFLT51LowBarrel = gHistogrammer->TH1DFactory("Trigger","FLT51LowBarrel","Number of low lumi configuration events triggered by FLT 30 && 51 with chosen barrel muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30 && 51","Events");
    fGeneralFLT51LowRear = gHistogrammer->TH1DFactory("Trigger","FLT51LowRear","Number of low lumi configuration events triggered by FLT 30 && 51 with chosen rear muon",fltspecialbins,fltspeciallow,fltspecialhigh,"FLT 30 && 51","Events");

    fGeneralFLTCombination = gHistogrammer->TH1DFactory("Trigger","FLTCombination","Number of events triggered by OR of FLT 42,44,51,52,53,54 && 30",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && 30","Events");
    fGeneralFLTCombinationForward = gHistogrammer->TH1DFactory("Trigger","FLTCombinationForward","Number of events triggered by OR of FLT 42,44,51,52,53,54 && 30 with chosen forward muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && 30","Events");
    fGeneralFLTCombinationBarrel = gHistogrammer->TH1DFactory("Trigger","FLTCombinationBarrel","Number of events triggered by OR of FLT 42,44,51,52,53,54 && 30 with chosen barrel muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && 30","Events");
    fGeneralFLTCombinationRear = gHistogrammer->TH1DFactory("Trigger","FLTCombinationRear","Number of events triggered by OR of FLT 42,44,51,52,53,54 && 30 with chosen rear muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && 30","Events");

    fGeneralFLTCombination2 = gHistogrammer->TH1DFactory("Trigger","FLTCombination2","Number of events triggered by OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15","Events");
    fGeneralFLTCombination2Forward = gHistogrammer->TH1DFactory("Trigger","FLTCombination2Forward","Number of events triggered by OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15 with chosen forward muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15","Events");
    fGeneralFLTCombination2Barrel = gHistogrammer->TH1DFactory("Trigger","FLTCombination2Barrel","Number of events triggered by OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15 with chosen barrel muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15","Events");
    fGeneralFLTCombination2Rear = gHistogrammer->TH1DFactory("Trigger","FLTCombination2Rear","Number of events triggered by OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15 with chosen rear muon",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 42,44,51,52,53,54 && OR of FLT 9,10,11,14,15","Events");

    fGeneralFLTCheck = gHistogrammer->TH1DFactory("Trigger","FLTCheck","Number of events triggered by OR of FLT 10,11,42,44,51,52,53,54",fltspecialbins,fltspeciallow,fltspecialhigh,"OR of FLT 10,11,42,44,51,52,53,54","Events");
  TString  dijettriggercomb  = "MUO,HFL1,HPP14,MUO+HFL1,MUO+HPP14,HFL1+HPP14,MUO+HFL1+HPP14,HPP14+ANY";
  TString  dijettriggercomb_special  = "MUO,HFL1,MUO+HFL1,HPP14+ANY";
  fGeneralDijetPHPTriggerCombinations = gHistogrammer->TH1DLabelFactory("Trigger","DijetPHPTriggerCombinations ","event found by which trigger",dijettriggercomb.Data(),"","Events");
  fGeneralDijetPHPTriggerCombinations_special = gHistogrammer->TH1DLabelFactory("Trigger","DijetPHPTriggerCombinations_special ","event found by which trigger",dijettriggercomb_special.Data(),"","Events");
  fGeneralDijetPHPTriggerCombinations_after_prescale = gHistogrammer->TH1DLabelFactory("Trigger","DijetPHPTriggerCombinations_after_prescale ","event found by which trigger",dijettriggercomb.Data(),"","Events");

    TString  dijettrigger  = "Muo3,Exo11,Exo12,HFL1,HPP14,MUO";
    fGeneralDijetPHPTrigger = gHistogrammer->TH1DLabelFactory("Trigger","DijetPHPTrigger","event found by which trigger",dijettrigger.Data(),"","Events");
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::FillControl() {
  //
  // fill general histograms for trigger
  //  if ( gDebug ) cout << endl << "GTrigger::FillControl() called" << endl << endl;

  if ( gCards->GetTriggerControl() ) {

    // fill uncut histograms
    // fill first word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(0) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 0;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlFirstDST_uncut->Fill(label.Data(),1);
      }
    }

    // fill second word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(1) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 32;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlSecondDST_uncut->Fill(label.Data(),1);
      }
    }

    // fill third word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(2) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 64;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlThirdDST_uncut->Fill(label.Data(),1);
      }
    }

    // fill fourth word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(3) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 96;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlFourthDST_uncut->Fill(label.Data(),1);
      }
    }

    
    fControlZesSelect_uncut->Fill(gData->Getzes_select());

    FillBitIntoHistogram(fControlFLT_uncut,32,gData->Getfltw(0),0,0);
    FillBitIntoHistogram(fControlFLT_uncut,32,gData->Getfltw(1),0,32);
    fControlFLT_uncut->Fill(fControlFLT_uncut->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlFLT_AfterPrescale_uncut,32,gData->Getfltpsw(0),0,0);
    FillBitIntoHistogram(fControlFLT_AfterPrescale_uncut,32,gData->Getfltpsw(1),0,32);
    fControlFLT_AfterPrescale_uncut->Fill(fControlFLT_AfterPrescale_uncut->GetNbinsX()-1,1);

    FillBitIntoHistogram(fControlSLT_1_uncut,32,gData->Getsltw(0));
    fControlSLT_1_uncut->Fill(fControlSLT_1_uncut->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_2_uncut,32,gData->Getsltw(1));
    fControlSLT_2_uncut->Fill(fControlSLT_2_uncut->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_3_uncut,32,gData->Getsltw(2));
    fControlSLT_3_uncut->Fill(fControlSLT_3_uncut->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_4_uncut,32,gData->Getsltw(3));
    fControlSLT_4_uncut->Fill(fControlSLT_4_uncut->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_5_uncut,32,gData->Getsltw(4));
    fControlSLT_5_uncut->Fill(fControlSLT_5_uncut->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_6_uncut,32,gData->Getsltw(5));
    fControlSLT_6_uncut->Fill(fControlSLT_6_uncut->GetNbinsX()-1,1);

    FillBitIntoHistogram(fControlTLT_SPP_uncut,16,gData->Gettltw(2),0,1);
    fControlTLT_SPP_uncut->Fill(fControlTLT_SPP_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_DIS_uncut,16,gData->Gettltw(3),0,1);
    FillBitIntoHistogram(fControlTLT_DIS_uncut,16,gData->Gettltw(10),0,17);
    fControlTLT_DIS_uncut->Fill(fControlTLT_DIS_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HPP_uncut,16,gData->Gettltw(4),0,1);
    FillBitIntoHistogram(fControlTLT_HPP_uncut,16,gData->Gettltw(11),0,17);
    fControlTLT_HPP_uncut->Fill(fControlTLT_HPP_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_EXO_uncut,16,gData->Gettltw(5),0,1);
    FillBitIntoHistogram(fControlTLT_EXO_uncut,16,gData->Gettltw(12),0,17);
    fControlTLT_EXO_uncut->Fill(fControlTLT_EXO_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_MUO_uncut,16,gData->Gettltw(6),0,1);
    fControlTLT_MUO_uncut->Fill(fControlTLT_MUO_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_VTX_uncut,16,gData->Gettltw(7),0,1);
    fControlTLT_VTX_uncut->Fill(fControlTLT_VTX_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HFM_uncut,16,gData->Gettltw(8),0,1);
    FillBitIntoHistogram(fControlTLT_HFM_uncut,16,gData->Gettltw(14),0,17);
    fControlTLT_HFM_uncut->Fill(fControlTLT_HFM_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HFL_uncut,16,gData->Gettltw(9),0,1);
    FillBitIntoHistogram(fControlTLT_HFL_uncut,16,gData->Gettltw(13),0,17);
    fControlTLT_HFL_uncut->Fill(fControlTLT_HFL_uncut->GetNbinsX(),1);

    FillBitIntoHistogram(fControlTLT_SPP_after_prescale_uncut,16,gData->Gettltw(2),16,1);
    fControlTLT_SPP_after_prescale_uncut->Fill(fControlTLT_SPP_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_DIS_after_prescale_uncut,16,gData->Gettltw(3),16,1);
    FillBitIntoHistogram(fControlTLT_DIS_after_prescale_uncut,16,gData->Gettltw(10),16,17);
    fControlTLT_DIS_after_prescale_uncut->Fill(fControlTLT_DIS_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HPP_after_prescale_uncut,16,gData->Gettltw(4),16,1);
    FillBitIntoHistogram(fControlTLT_HPP_after_prescale_uncut,16,gData->Gettltw(11),16,17);
    fControlTLT_HPP_after_prescale_uncut->Fill(fControlTLT_HPP_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_EXO_after_prescale_uncut,16,gData->Gettltw(5),16,1);
    FillBitIntoHistogram(fControlTLT_EXO_after_prescale_uncut,16,gData->Gettltw(12),16,17);
    fControlTLT_EXO_after_prescale_uncut->Fill(fControlTLT_EXO_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_MUO_after_prescale_uncut,16,gData->Gettltw(6),16,1);
    fControlTLT_MUO_after_prescale_uncut->Fill(fControlTLT_MUO_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_VTX_after_prescale_uncut,16,gData->Gettltw(7),16,1);
    fControlTLT_VTX_after_prescale_uncut->Fill(fControlTLT_VTX_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HFM_after_prescale_uncut,16,gData->Gettltw(8),16,1);
    FillBitIntoHistogram(fControlTLT_HFM_after_prescale_uncut,16,gData->Gettltw(14),16,17);
    fControlTLT_HFM_after_prescale_uncut->Fill(fControlTLT_HFM_after_prescale_uncut->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HFL_after_prescale_uncut,16,gData->Gettltw(9),16,1);
    FillBitIntoHistogram(fControlTLT_HFL_after_prescale_uncut,16,gData->Gettltw(13),16,17);
    fControlTLT_HFL_after_prescale_uncut->Fill(fControlTLT_HFL_after_prescale_uncut->GetNbinsX(),1);

    // fill first word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(0) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 0;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlFirstDST->Fill(label.Data(),1);
      }
    }

    // fill second word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(1) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 32;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlSecondDST->Fill(label.Data(),1);
      }
    }

    // fill third word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(2) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 64;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlThirdDST->Fill(label.Data(),1);
      }
    }

    // fill fourth word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(3) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 96;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fControlFourthDST->Fill(label.Data(),1);
      }
    }

    
    fControlZesSelect->Fill(gData->Getzes_select());

    // fill flt bins
    FillBitIntoHistogram(fControlFLT,32,gData->Getfltw(0),0,0);
    FillBitIntoHistogram(fControlFLT,32,gData->Getfltw(1),0,32);
    fControlFLT->Fill(fControlFLT->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlFLT_AfterPrescale,32,gData->Getfltpsw(0),0,0);
    FillBitIntoHistogram(fControlFLT_AfterPrescale,32,gData->Getfltpsw(1),0,32);
    fControlFLT_AfterPrescale->Fill(fControlFLT_AfterPrescale->GetNbinsX()-1,1);

    // fill slt bits
    FillBitIntoHistogram(fControlSLT_1,32,gData->Getsltw(0));
    fControlSLT_1->Fill(fControlSLT_1->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_2,32,gData->Getsltw(1));
    fControlSLT_2->Fill(fControlSLT_2->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_3,32,gData->Getsltw(2));
    fControlSLT_3->Fill(fControlSLT_3->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_4,32,gData->Getsltw(3));
    fControlSLT_4->Fill(fControlSLT_4->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_5,32,gData->Getsltw(4));
    fControlSLT_5->Fill(fControlSLT_5->GetNbinsX()-1,1);
    FillBitIntoHistogram(fControlSLT_6,32,gData->Getsltw(5));
    fControlSLT_6->Fill(fControlSLT_6->GetNbinsX()-1,1);

    // fill tlt bits
    if( fCutTLTSPP03p04p || fCutTLTSPP05e06e || fCutTLTSPP06p07p ) {
      FillBitIntoHistogram(fControlTLT_SPP,16,gData->Gettltw(2),0,1);
      fControlTLT_SPP->Fill(fControlTLT_SPP->GetNbinsX(),1);
    }
    if ( fCutTLTDIS96p00p || fCutTLTDIS03p04p || fCutTLTDIS05e06e || fCutTLTDIS06p07p ) {
    FillBitIntoHistogram(fControlTLT_DIS,16,gData->Gettltw(3),0,1);
    FillBitIntoHistogram(fControlTLT_DIS,16,gData->Gettltw(10),0,17);
    fControlTLT_DIS->Fill(fControlTLT_DIS->GetNbinsX(),1);
    }
    if ( fCutTLTHPP96p00p || fCutTLTHPP03p04p || fCutTLTHPP05e06e || fCutTLTHPP06p07p ) {
      FillBitIntoHistogram(fControlTLT_HPP,16,gData->Gettltw(4),0,1);
      FillBitIntoHistogram(fControlTLT_HPP,16,gData->Gettltw(11),0,17);
      fControlTLT_HPP->Fill(fControlTLT_HPP->GetNbinsX(),1);
    }
    if ( fCutTLTEXO96p00p || fCutTLTEXO03p04p || fCutTLTEXO05e06e || fCutTLTEXO06p07p ) {
      FillBitIntoHistogram(fControlTLT_EXO,16,gData->Gettltw(5),0,1);
      FillBitIntoHistogram(fControlTLT_EXO,16,gData->Gettltw(12),0,17);
      fControlTLT_EXO->Fill(fControlTLT_EXO->GetNbinsX(),1);
    }
    if ( fCutTLTMUO96p00p || fCutTLTMUO03p04p || fCutTLTMUO05e06e ||  fCutTLTMUO06p07p ) {
      FillBitIntoHistogram(fControlTLT_MUO,16,gData->Gettltw(6),0,1);
      fControlTLT_MUO->Fill(fControlTLT_MUO->GetNbinsX(),1);
    }
    FillBitIntoHistogram(fControlTLT_VTX,16,gData->Gettltw(7),0,1);
    fControlTLT_VTX->Fill(fControlTLT_VTX->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HFM,16,gData->Gettltw(8),0,1);
    FillBitIntoHistogram(fControlTLT_HFM,16,gData->Gettltw(14),0,17);
    fControlTLT_HFM->Fill(fControlTLT_HFM->GetNbinsX(),1);
    if ( fCutTLTHFL96p00p || fCutTLTHFL99p00p || fCutTLTHFL03p04p || fCutTLTHFL05e06e || fCutTLTHFL06p07p ) {
      FillBitIntoHistogram(fControlTLT_HFL,16,gData->Gettltw(9),0,1);
      FillBitIntoHistogram(fControlTLT_HFL,16,gData->Gettltw(13),0,17);
      fControlTLT_HFL->Fill(fControlTLT_HFL->GetNbinsX(),1);
    }
    if( fCutTLTSPP03p04p || fCutTLTSPP05e06e || fCutTLTSPP06p07p ) {
      FillBitIntoHistogram(fControlTLT_SPP_after_prescale,16,gData->Gettltw(2),16,1);
      fControlTLT_SPP_after_prescale->Fill(fControlTLT_SPP_after_prescale->GetNbinsX(),1);
    }
    if ( fCutTLTDIS96p00p || fCutTLTDIS03p04p || fCutTLTDIS05e06e || fCutTLTDIS06p07p ) {
    FillBitIntoHistogram(fControlTLT_DIS_after_prescale,16,gData->Gettltw(3),16,1);
    FillBitIntoHistogram(fControlTLT_DIS_after_prescale,16,gData->Gettltw(10),16,17);
    fControlTLT_DIS_after_prescale->Fill(fControlTLT_DIS_after_prescale->GetNbinsX(),1);
    }
    if ( fCutTLTHPP96p00p || fCutTLTHPP03p04p || fCutTLTHPP05e06e || fCutTLTHPP06p07p ) {
      FillBitIntoHistogram(fControlTLT_HPP_after_prescale,16,gData->Gettltw(4),16,1);
      FillBitIntoHistogram(fControlTLT_HPP_after_prescale,16,gData->Gettltw(11),16,17);
      fControlTLT_HPP_after_prescale->Fill(fControlTLT_HPP_after_prescale->GetNbinsX(),1);
    }
    if ( fCutTLTEXO96p00p || fCutTLTEXO03p04p || fCutTLTEXO05e06e || fCutTLTEXO06p07p ) {
      FillBitIntoHistogram(fControlTLT_EXO_after_prescale,16,gData->Gettltw(5),16,1);
      FillBitIntoHistogram(fControlTLT_EXO_after_prescale,16,gData->Gettltw(12),16,17);
      fControlTLT_EXO_after_prescale->Fill(fControlTLT_EXO_after_prescale->GetNbinsX(),1);
    }
    if ( fCutTLTMUO96p00p || fCutTLTMUO03p04p || fCutTLTMUO05e06e || fCutTLTMUO06p07p ) {
      FillBitIntoHistogram(fControlTLT_MUO_after_prescale,16,gData->Gettltw(6),16,1);
      fControlTLT_MUO_after_prescale->Fill(fControlTLT_MUO_after_prescale->GetNbinsX(),1);
    }
    FillBitIntoHistogram(fControlTLT_VTX_after_prescale,16,gData->Gettltw(7),16,1);
    fControlTLT_VTX_after_prescale->Fill(fControlTLT_VTX_after_prescale->GetNbinsX(),1);
    FillBitIntoHistogram(fControlTLT_HFM_after_prescale,16,gData->Gettltw(8),16,1);
    FillBitIntoHistogram(fControlTLT_HFM_after_prescale,16,gData->Gettltw(14),16,17);
    fControlTLT_HFM_after_prescale->Fill(fControlTLT_HFM_after_prescale->GetNbinsX(),1);
    if ( fCutTLTHFL96p00p || fCutTLTHFL99p00p || fCutTLTHFL03p04p || fCutTLTHFL05e06e || fCutTLTHFL06p07p ) {
      FillBitIntoHistogram(fControlTLT_HFL_after_prescale,16,gData->Gettltw(9),16,1);
      FillBitIntoHistogram(fControlTLT_HFL_after_prescale,16,gData->Gettltw(13),16,17);
      fControlTLT_HFL_after_prescale->Fill(fControlTLT_HFL_after_prescale->GetNbinsX(),1);
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::FillGeneral() {
  //
  // fill general histograms for trigger
  if ( gDebug ) cout << endl << "GTrigger::FillGeneral() called" << endl << endl;

  if ( gCards->GetTriggerGeneral() ) {

    // fill uncut histograms
    // fill first word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(0) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 0;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fGeneralFirstDST_uncut->Fill(label.Data(),gHeader->GetWeight());

      }
    }

    // fill second word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(1) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 32;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fGeneralSecondDST_uncut->Fill(label.Data(),gHeader->GetWeight());
      }
    }

    // fill third word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(2) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 64;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fGeneralThirdDST_uncut->Fill(label.Data(),gHeader->GetWeight());
      }
    }
    // fill fourth word
    for ( Int_t i = 0; i < 32; ++i ) {
      if ( gData->Getdstw(3) & (Int_t)TMath::Power(2,i) ) {
	Int_t offset = 96;
	i += offset;
	TString label = "DST";
	if ( i < 10 ) {
	  label.Append("00");
	  label += i;
	} else if ( i < 100 ) {
	  label.Append("0");
	  label += i;
	} else {
	  label += i;
	}
	fGeneralFourthDST_uncut->Fill(label.Data(),gHeader->GetWeight());
      }
    }
    
    fGeneralZesSelect_uncut->Fill(gData->Getzes_select(),gHeader->GetWeight());

    FillBitIntoHistogram(fGeneralFLT_uncut,32,gData->Getfltw(0),0,0,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralFLT_uncut,32,gData->Getfltw(1),0,32,gHeader->GetWeight());
    fGeneralFLT_uncut->Fill(fGeneralFLT_uncut->GetNbinsX()-1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralFLT_AfterPrescale_uncut,32,gData->Getfltpsw(0),0,0,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralFLT_AfterPrescale_uncut,32,gData->Getfltpsw(1),0,32,gHeader->GetWeight());
    fGeneralFLT_AfterPrescale_uncut->Fill(fGeneralFLT_AfterPrescale_uncut->GetNbinsX()-1,gHeader->GetWeight());

    FillBitIntoHistogram(fGeneralSLT_1_uncut,32,gData->Getsltw(0),0,0,gHeader->GetWeight());
    fGeneralSLT_1_uncut->Fill(fGeneralSLT_1_uncut->GetNbinsX()-1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralSLT_2_uncut,32,gData->Getsltw(1),0,0,gHeader->GetWeight());
    fGeneralSLT_2_uncut->Fill(fGeneralSLT_2_uncut->GetNbinsX()-1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralSLT_3_uncut,32,gData->Getsltw(2),0,0,gHeader->GetWeight());
    fGeneralSLT_3_uncut->Fill(fGeneralSLT_3_uncut->GetNbinsX()-1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralSLT_4_uncut,32,gData->Getsltw(3),0,0,gHeader->GetWeight());
    fGeneralSLT_4_uncut->Fill(fGeneralSLT_4_uncut->GetNbinsX()-1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralSLT_5_uncut,32,gData->Getsltw(4),0,0,gHeader->GetWeight());
    fGeneralSLT_5_uncut->Fill(fGeneralSLT_5_uncut->GetNbinsX()-1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralSLT_6_uncut,32,gData->Getsltw(5),0,0,gHeader->GetWeight());
    fGeneralSLT_6_uncut->Fill(fGeneralSLT_6_uncut->GetNbinsX()-1,gHeader->GetWeight());

    FillBitIntoHistogram(fGeneralTLT_SPP_uncut,16,gData->Gettltw(2),0,1,gHeader->GetWeight());
    fGeneralTLT_SPP_uncut->Fill(fGeneralTLT_SPP_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_DIS_uncut,16,gData->Gettltw(3),0,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_DIS_uncut,16,gData->Gettltw(10),0,17,gHeader->GetWeight());
    fGeneralTLT_DIS_uncut->Fill(fGeneralTLT_DIS_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HPP_uncut,16,gData->Gettltw(4),0,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HPP_uncut,16,gData->Gettltw(11),0,17,gHeader->GetWeight());
    fGeneralTLT_HPP_uncut->Fill(fGeneralTLT_HPP_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_EXO_uncut,16,gData->Gettltw(5),0,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_EXO_uncut,16,gData->Gettltw(12),0,17,gHeader->GetWeight());
    fGeneralTLT_EXO_uncut->Fill(fGeneralTLT_EXO_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_MUO_uncut,16,gData->Gettltw(6),0,1,gHeader->GetWeight());
    fGeneralTLT_MUO_uncut->Fill(fGeneralTLT_MUO_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_VTX_uncut,16,gData->Gettltw(7),0,1,gHeader->GetWeight());
    fGeneralTLT_VTX_uncut->Fill(fGeneralTLT_VTX_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFM_uncut,16,gData->Gettltw(8),0,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFM_uncut,16,gData->Gettltw(14),0,17,gHeader->GetWeight());
    fGeneralTLT_HFM_uncut->Fill(fGeneralTLT_HFM_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFL_uncut,16,gData->Gettltw(9),0,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFL_uncut,16,gData->Gettltw(13),0,17,gHeader->GetWeight());
    fGeneralTLT_HFL_uncut->Fill(fGeneralTLT_HFL_uncut->GetNbinsX(),gHeader->GetWeight());

    FillBitIntoHistogram(fGeneralTLT_SPP_after_prescale_uncut,16,gData->Gettltw(2),16,1,gHeader->GetWeight());
    fGeneralTLT_SPP_after_prescale_uncut->Fill(fGeneralTLT_SPP_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_DIS_after_prescale_uncut,16,gData->Gettltw(3),16,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_DIS_after_prescale_uncut,16,gData->Gettltw(10),16,17,gHeader->GetWeight());
    fGeneralTLT_DIS_after_prescale_uncut->Fill(fGeneralTLT_DIS_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HPP_after_prescale_uncut,16,gData->Gettltw(4),16,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HPP_after_prescale_uncut,16,gData->Gettltw(11),16,17,gHeader->GetWeight());
    fGeneralTLT_HPP_after_prescale_uncut->Fill(fGeneralTLT_HPP_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_EXO_after_prescale_uncut,16,gData->Gettltw(5),16,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_EXO_after_prescale_uncut,16,gData->Gettltw(12),16,17,gHeader->GetWeight());
    fGeneralTLT_EXO_after_prescale_uncut->Fill(fGeneralTLT_EXO_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_MUO_after_prescale_uncut,16,gData->Gettltw(6),16,1,gHeader->GetWeight());
    fGeneralTLT_MUO_after_prescale_uncut->Fill(fGeneralTLT_MUO_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_VTX_after_prescale_uncut,16,gData->Gettltw(7),16,1,gHeader->GetWeight());
    fGeneralTLT_VTX_after_prescale_uncut->Fill(fGeneralTLT_VTX_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFM_after_prescale_uncut,16,gData->Gettltw(8),16,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFM_after_prescale_uncut,16,gData->Gettltw(14),16,17,gHeader->GetWeight());
    fGeneralTLT_HFM_after_prescale_uncut->Fill(fGeneralTLT_HFM_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_uncut,16,gData->Gettltw(9),16,1,gHeader->GetWeight());
    FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_uncut,16,gData->Gettltw(13),16,17,gHeader->GetWeight());
    fGeneralTLT_HFL_after_prescale_uncut->Fill(fGeneralTLT_HFL_after_prescale_uncut->GetNbinsX(),gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {

	  if (fMuo3)  fGeneralDijetPHPTrigger->Fill("Muo3",gHeader->GetWeight());
	  if (fExo11) fGeneralDijetPHPTrigger->Fill("Exo11",gHeader->GetWeight());
	  if (fExo12)fGeneralDijetPHPTrigger->Fill("Exo12",gHeader->GetWeight());
	  if (fMuo_trig)  fGeneralDijetPHPTrigger->Fill("MUO",gHeader->GetWeight());
	  if (fHpp_trig){
	    fGeneralDijetPHPTrigger->Fill("HPP14",gHeader->GetWeight());
	  }

	  if ((fMuo_trig) && (!fHpp_trig ) &&  (!fHfl_trig)) {  
	    fGeneralDijetPHPTriggerCombinations->Fill("MUO",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations_special->Fill("MUO",gHeader->GetWeight());
	  }
	  if ((!fMuo_trig) && (fHpp_trig) &&  (!fHfl_trig)) { 
	    fGeneralDijetPHPTriggerCombinations->Fill("HPP14",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations->Fill("HPP14+ANY",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations_special->Fill("HPP14+ANY",gHeader->GetWeight());
                                                 
	  }
	  if ((!fMuo_trig) && (!fHpp_trig) &&  (fHfl_trig))  {
	    fGeneralDijetPHPTriggerCombinations->Fill("HFL1",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations_special->Fill("HFL1",gHeader->GetWeight());
	    fGeneralDijetPHPTrigger->Fill("HFL1",gHeader->GetWeight());
	  }
	  if ((fMuo_trig) && (fHpp_trig) &&  (!fHfl_trig)) { 
	    fGeneralDijetPHPTriggerCombinations->Fill("MUO+HPP14",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations->Fill("HPP14+ANY",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations_special->Fill("HPP14+ANY",gHeader->GetWeight());
	  }
	  if ((fMuo_trig) && (!fHpp_trig) &&  (fHfl_trig)) { 
	    fGeneralDijetPHPTriggerCombinations->Fill("MUO+HFL1",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations_special->Fill("MUO+HFL1",gHeader->GetWeight());
	  }
	  if ((!fMuo_trig) && (fHpp_trig) &&  (fHfl_trig))  
	    { fGeneralDijetPHPTriggerCombinations->Fill("HFL1+HPP14",gHeader->GetWeight());
	      fGeneralDijetPHPTriggerCombinations->Fill("HPP14+ANY",gHeader->GetWeight());
	      fGeneralDijetPHPTriggerCombinations_special->Fill("HPP14+ANY",gHeader->GetWeight());
	    }
	  if ((fMuo_trig) && (fHpp_trig) &&  (fHfl_trig)) {
	    fGeneralDijetPHPTriggerCombinations->Fill("MUO+HFL1+HPP14",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations->Fill("HPP14+ANY",gHeader->GetWeight());
	    fGeneralDijetPHPTriggerCombinations_special->Fill("HPP14+ANY",gHeader->GetWeight());
	  }


	  Bool_t hpp_trig_after_prescale = 0;
	  Bool_t hfl_trig_after_prescale = 0;
	  Bool_t muo_trig_after_prescale = 0;
	  if (gData->Gettltw(4) & (Int_t)TMath::Power(2,29)){
	    hpp_trig_after_prescale = kTRUE;
	  }
	  if (gData->Gettltw(9) & (Int_t)TMath::Power(2,16)){
	    hfl_trig_after_prescale = kTRUE;
	  }
	  if ( (gData->Gettltw(6) & (Int_t)TMath::Power(2,18))||
	       (gData->Gettltw(5) & (Int_t)TMath::Power(2,26))||
	       (gData->Gettltw(5) & (Int_t)TMath::Power(2,27)) ){
	    muo_trig_after_prescale = kTRUE;
	  }

	  if ((muo_trig_after_prescale) && (!hpp_trig_after_prescale) && ( !hfl_trig_after_prescale)) {
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("MUO",gHeader->GetWeight());
}
	  if ((!muo_trig_after_prescale ) && (hpp_trig_after_prescale) &&  (!hfl_trig_after_prescale)) {  
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("HPP14",gHeader->GetWeight());
	  }
	  if ((!muo_trig_after_prescale) && (!hpp_trig_after_prescale) && ( hfl_trig_after_prescale)) { 
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("HFL1",gHeader->GetWeight());
	  }
	  if ((muo_trig_after_prescale) && (hpp_trig_after_prescale) && ( !hfl_trig_after_prescale)) {  
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("MUO+HPP14",gHeader->GetWeight());
	  }
	  if ((muo_trig_after_prescale) && (!hpp_trig_after_prescale) &&  (hfl_trig_after_prescale )) { 
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("MUO+HFL1",gHeader->GetWeight());
	  }
	  if ((!muo_trig_after_prescale) && (hpp_trig_after_prescale) && ( hfl_trig_after_prescale)) { 
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("HFL1+HPP14",gHeader->GetWeight());
	  }
	  if ((muo_trig_after_prescale) && (hpp_trig_after_prescale) && ( hfl_trig_after_prescale)) { 
	    fGeneralDijetPHPTriggerCombinations_after_prescale->Fill("MUO+HFL1+HPP14",gHeader->GetWeight());
	  }
	  
      // get the first dimuon for dimuon plots (check for valid pointer when using it):
      GDIMuon * dimuon = 0; 
      if( gDIMuons->GetNDIMuons() > 0 ) dimuon = gDIMuons->GetDIMuon(0);

      // fill first word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(0) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 0;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralFirstDST->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill second word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(1) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 32;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralSecondDST->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill third word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(2) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 64;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralThirdDST->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill fourth word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(3) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 96;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralFourthDST->Fill(label.Data(),gHeader->GetWeight());
	}
      }

    
      fGeneralZesSelect->Fill(gData->Getzes_select(),gHeader->GetWeight());

      // fill flt bins
      FillBitIntoHistogram(fGeneralFLT,32,gData->Getfltw(0),0,0,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralFLT,32,gData->Getfltw(1),0,32,gHeader->GetWeight());
      fGeneralFLT->Fill(fGeneralFLT->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralFLT_AfterPrescale,32,gData->Getfltpsw(0),0,0,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralFLT_AfterPrescale,32,gData->Getfltpsw(1),0,32,gHeader->GetWeight());
      fGeneralFLT_AfterPrescale->Fill(fGeneralFLT_AfterPrescale->GetNbinsX()-1,gHeader->GetWeight());

      // fill slt bits
      FillBitIntoHistogram(fGeneralSLT_1,32,gData->Getsltw(0),0,0,gHeader->GetWeight());
      fGeneralSLT_1->Fill(fGeneralSLT_1->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_2,32,gData->Getsltw(1),0,0,gHeader->GetWeight());
      fGeneralSLT_2->Fill(fGeneralSLT_2->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_3,32,gData->Getsltw(2),0,0,gHeader->GetWeight());
      fGeneralSLT_3->Fill(fGeneralSLT_3->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_4,32,gData->Getsltw(3),0,0,gHeader->GetWeight());
      fGeneralSLT_4->Fill(fGeneralSLT_4->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_5,32,gData->Getsltw(4),0,0,gHeader->GetWeight());
      fGeneralSLT_5->Fill(fGeneralSLT_5->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_6,32,gData->Getsltw(5),0,0,gHeader->GetWeight());
      fGeneralSLT_6->Fill(fGeneralSLT_6->GetNbinsX()-1,gHeader->GetWeight());

      // fill tlt bits
      FillBitIntoHistogram(fGeneralTLT_SPP,16,gData->Gettltw(2),0,1,gHeader->GetWeight());
      fGeneralTLT_SPP->Fill(fGeneralTLT_SPP->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS,16,gData->Gettltw(3),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS,16,gData->Gettltw(10),0,17,gHeader->GetWeight());
      fGeneralTLT_DIS->Fill(fGeneralTLT_DIS->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP,16,gData->Gettltw(4),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP,16,gData->Gettltw(11),0,17,gHeader->GetWeight());
      fGeneralTLT_HPP->Fill(fGeneralTLT_HPP->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO,16,gData->Gettltw(5),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO,16,gData->Gettltw(12),0,17,gHeader->GetWeight());
      fGeneralTLT_EXO->Fill(fGeneralTLT_EXO->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_MUO,16,gData->Gettltw(6),0,1,gHeader->GetWeight());
      fGeneralTLT_MUO->Fill(fGeneralTLT_MUO->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_VTX,16,gData->Gettltw(7),0,1,gHeader->GetWeight());
      fGeneralTLT_VTX->Fill(fGeneralTLT_VTX->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM,16,gData->Gettltw(8),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM,16,gData->Gettltw(14),0,17,gHeader->GetWeight());
      fGeneralTLT_HFM->Fill(fGeneralTLT_HFM->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL,16,gData->Gettltw(9),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL,16,gData->Gettltw(13),0,17,gHeader->GetWeight());
      fGeneralTLT_HFL->Fill(fGeneralTLT_HFL->GetNbinsX(),gHeader->GetWeight());

      FillBitIntoHistogram(fGeneralTLT_SPP_after_prescale,16,gData->Gettltw(2),16,1,gHeader->GetWeight());
      fGeneralTLT_SPP_after_prescale->Fill(fGeneralTLT_SPP_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS_after_prescale,16,gData->Gettltw(3),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS_after_prescale,16,gData->Gettltw(10),16,17,gHeader->GetWeight());
      fGeneralTLT_DIS_after_prescale->Fill(fGeneralTLT_DIS_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP_after_prescale,16,gData->Gettltw(4),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP_after_prescale,16,gData->Gettltw(11),16,17,gHeader->GetWeight());
      fGeneralTLT_HPP_after_prescale->Fill(fGeneralTLT_HPP_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO_after_prescale,16,gData->Gettltw(5),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO_after_prescale,16,gData->Gettltw(12),16,17,gHeader->GetWeight());
      fGeneralTLT_EXO_after_prescale->Fill(fGeneralTLT_EXO_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_MUO_after_prescale,16,gData->Gettltw(6),16,1,gHeader->GetWeight());
      fGeneralTLT_MUO_after_prescale->Fill(fGeneralTLT_MUO_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_VTX_after_prescale,16,gData->Gettltw(7),16,1,gHeader->GetWeight());
      fGeneralTLT_VTX_after_prescale->Fill(fGeneralTLT_VTX_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM_after_prescale,16,gData->Gettltw(8),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM_after_prescale,16,gData->Gettltw(14),16,17,gHeader->GetWeight());
      fGeneralTLT_HFM_after_prescale->Fill(fGeneralTLT_HFM_after_prescale->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale,16,gData->Gettltw(9),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale,16,gData->Gettltw(13),16,17,gHeader->GetWeight());
      fGeneralTLT_HFL_after_prescale->Fill(fGeneralTLT_HFL_after_prescale->GetNbinsX(),gHeader->GetWeight());

 	if( dimuon != 0 ){
	  if( !dimuon->GetSqSumIsolationCut() ) {      
	    // 	  if( dimuon->GetIsolationSqSum10() <= gCards->GetDIMUONSqSumIsolationCut() ) {      
 	    if ( dimuon->GetInvMass() <= 4. &&  dimuon->GetDifCharge() ) {	FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_lu_is,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_lu_is,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_lu_is->Fill(fGeneralTLT_HFL_after_prescale_lu_is->GetNbinsX(),gHeader->GetWeight()); }
	    if ( dimuon->GetInvMass() <= 4. && !dimuon->GetDifCharge() ) {	FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_ll_is,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_ll_is,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_ll_is->Fill(fGeneralTLT_HFL_after_prescale_ll_is->GetNbinsX(),gHeader->GetWeight()); }
 	    if ( dimuon->GetInvMass() > 4.  &&  dimuon->GetDifCharge() ) {	FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hu_is,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hu_is,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_hu_is->Fill(fGeneralTLT_HFL_after_prescale_hu_is->GetNbinsX(),gHeader->GetWeight()); }
 	    if ( dimuon->GetInvMass() > 4.  && !dimuon->GetDifCharge() ) {	FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hl_is,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hl_is,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_hl_is->Fill(fGeneralTLT_HFL_after_prescale_hl_is->GetNbinsX(),gHeader->GetWeight()); }
 	  }						      
 	  else{					      
 	    if ( dimuon->GetInvMass() <= 4. &&  dimuon->GetDifCharge() ) {       FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_lu_nis,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_lu_nis,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_lu_nis->Fill(fGeneralTLT_HFL_after_prescale_lu_nis->GetNbinsX(),gHeader->GetWeight()); }
 	    if ( dimuon->GetInvMass() <= 4. && !dimuon->GetDifCharge() ) {       FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_ll_nis,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_ll_nis,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_ll_nis->Fill(fGeneralTLT_HFL_after_prescale_ll_nis->GetNbinsX(),gHeader->GetWeight()); }
 	    if ( dimuon->GetInvMass() > 4.  &&  dimuon->GetDifCharge() ) {       FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hu_nis,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hu_nis,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); fGeneralTLT_HFL_after_prescale_hu_nis->Fill(fGeneralTLT_HFL_after_prescale_hu_nis->GetNbinsX(),gHeader->GetWeight()); }
 	    if ( dimuon->GetInvMass() > 4.  && !dimuon->GetDifCharge() ) {   
	      FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hl_nis,16,gData->Gettltw(9),16,1,gHeader->GetWeight()); 
	      FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_hl_nis,16,gData->Gettltw(13),16,17,gHeader->GetWeight()); 
	      fGeneralTLT_HFL_after_prescale_hl_nis->Fill(fGeneralTLT_HFL_after_prescale_hl_nis->GetNbinsX(),gHeader->GetWeight()); 
	    }
 	  }     
 	}                                            

      // fill events in LOW lumi configuration
      Bool_t checkfltlow = kFALSE;
      if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	checkfltlow = kTRUE;
      } else {
	GRun *run = gRuns->GetRun(gData->Getrunnr());
	if ( run ) {
	  if ( run->GetType() == kLow ) {
	    checkfltlow = kTRUE;
	  }
	}
      }
	
      GMJMatch *match = gMJMatchs->GetChosen();
      GMuon *muon = 0;
      if (match != 0 ) {
	muon = match->GetMuon();
      }

      
      if ( checkfltlow ) {
	// check flt 30
	if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	  fGeneralFLT30Low->Fill(0.5);
	}
	// check flt 51
	if ( (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) && (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	  fGeneralFLT51Low->Fill(0.5);
	}
	
	if ( muon != 0 ) {
	  if ( muon->GetType() == kForward ) {
 	    // check flt 30
	    if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	      fGeneralFLT30LowForward->Fill(0.5);
	    }
	    // check flt 51 && FLT 30
	    if ( (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) && (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	      fGeneralFLT51LowForward->Fill(0.5);
	    }
	  } else if ( muon->GetType() == kBarrel ) {
	    // check flt 30
	    if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	      fGeneralFLT30LowBarrel->Fill(0.5);
	    }
	    // check flt 51 && FLT 30
	    if ( (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) && (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	      fGeneralFLT51LowBarrel->Fill(0.5);
	    }
	  } else if ( muon->GetType() == kRear ) {
	    // check flt 30
	    if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	      fGeneralFLT30LowRear->Fill(0.5);
	    }
	    // check flt 51 && FLT 30
	    if ( (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) && (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	      fGeneralFLT51LowRear->Fill(0.5);
	    }
	  }
	}
      }

      // check flt 30
      if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	fGeneralFLT30->Fill(0.5);
      }

      // check OR of FLT 9,10,11,14,15
      if ( (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15)) ) {
	fGeneralFLT9_15->Fill(0.5);
      }

      // fill OR of 42,44,51,52,53,54 && FLT 30
      if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	fGeneralFLTCombination->Fill(0.5);
      }

      // fill OR of 42,44,51,52,53,54 && OR of 9,10,11,14,15
      if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
	    (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	   ((gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
	    (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	    (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
	    (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
	    (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15))) ) {
	fGeneralFLTCombination2->Fill(0.5);
      }

      if ( muon != 0 ) {
	if ( muon->GetType() == kForward ) {
	  // fill OR of 42,44,51,52,53,54 && FLT 30
	  if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	    fGeneralFLTCombinationForward->Fill(0.5);
	  }
	  // check flt 30
	  if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	    fGeneralFLT30Forward->Fill(0.5);
	  }
	  // check OR of FLT 9,10,11,14,15
	  if ( (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15)) ) {
	    fGeneralFLT9_15Forward->Fill(0.5);
	  }
	  // fill OR of 42,44,51,52,53,54 && OR of 9,10,11,14,15
	  if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	       ((gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15))) ) {
	    fGeneralFLTCombination2Forward->Fill(0.5);
	  }
	} else if ( muon->GetType() == kBarrel ) {
	  // fill OR of 42,44,51,52,53,54 && FLT 30
	  if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	    fGeneralFLTCombinationBarrel->Fill(0.5);
	  }
	  // check flt 30
	  if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	    fGeneralFLT30Barrel->Fill(0.5);
	  }
	  // check OR of FLT 9,10,11,14,15
	  if ( (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15)) ) {
	    fGeneralFLT9_15Barrel->Fill(0.5);
	  }
	  // fill OR of 42,44,51,52,53,54 && OR of 9,10,11,14,15
	  if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	       ((gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15))) ) {
	    fGeneralFLTCombination2Barrel->Fill(0.5);
	  }
	} else if ( muon->GetType() == kRear ) {
	  // fill OR of 42,44,51,52,53,54 && FLT 30
	  if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30)) ) {
	    fGeneralFLTCombinationRear->Fill(0.5);
	  }
	  // check flt 30
	  if ( gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,30) ) {
	    fGeneralFLT30Rear->Fill(0.5);
	  }

	  // check OR of FLT 9,10,11,14,15
	  if ( (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
	       (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15)) ) {
	    fGeneralFLT9_15Rear->Fill(0.5);
	  }
	  // fill OR of 42,44,51,52,53,54 && OR of 9,10,11,14,15
	  if ( ((gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		(gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) &&
	       ((gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,9)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,14)) ||
		(gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,15))) ) {
	    fGeneralFLTCombination2Rear->Fill(0.5);
	  }
	}
      }
      // fill OR of 10,11,42,44,51,52,53,54
      if ( (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ||
	   (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
	   (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,12)) ||
	   (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
	   (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
	   (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
	   (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22)) ) {
	fGeneralFLTCheck->Fill(0.5);
      }
    }

    Bool_t excl = kFALSE;

    // check for fulfilllment of allc uts except trigger cuts
    if ( gCards->GetMC() &&  !(gCards->GetMCLF() && gCards->GetDoFake())) {
      if ( gRuns->GetAllCuts() &&
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
	excl = kTRUE;
    } else {
      if ( gRuns->GetAllCuts() &&
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
	excl = kTRUE;
    }

    if ( excl ) {

      // fill first word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(0) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 0;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralFirstDST_ExclTrigCuts->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill second word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(1) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 32;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralSecondDST_ExclTrigCuts->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill third word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(2) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 64;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralThirdDST_ExclTrigCuts->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill fourth word
      for ( Int_t i = 0; i < 32; ++i ) {
	if ( gData->Getdstw(3) & (Int_t)TMath::Power(2,i) ) {
	  Int_t offset = 96;
	  i += offset;
	  TString label = "DST";
	  if ( i < 10 ) {
	    label.Append("00");
	    label += i;
	  } else if ( i < 100 ) {
	    label.Append("0");
	    label += i;
	  } else {
	    label += i;
	  }
	  fGeneralFourthDST_ExclTrigCuts->Fill(label.Data(),gHeader->GetWeight());
	}
      }

      // fill flt bins
      FillBitIntoHistogram(fGeneralFLT_ExclTrigCuts,32,gData->Getfltw(0),0,0,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralFLT_ExclTrigCuts,32,gData->Getfltw(1),0,32,gHeader->GetWeight());
      fGeneralFLT_ExclTrigCuts->Fill(fGeneralFLT_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralFLT_AfterPrescale_ExclTrigCuts,32,gData->Getfltpsw(0),0,0,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralFLT_AfterPrescale_ExclTrigCuts,32,gData->Getfltpsw(1),0,32,gHeader->GetWeight());
      fGeneralFLT_AfterPrescale_ExclTrigCuts->Fill(fGeneralFLT_AfterPrescale_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());

      // fill slt bits
      FillBitIntoHistogram(fGeneralSLT_1_ExclTrigCuts,32,gData->Getsltw(0),0,0,gHeader->GetWeight());
      fGeneralSLT_1_ExclTrigCuts->Fill(fGeneralSLT_1_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_2_ExclTrigCuts,32,gData->Getsltw(1),0,0,gHeader->GetWeight());
      fGeneralSLT_2_ExclTrigCuts->Fill(fGeneralSLT_2_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_3_ExclTrigCuts,32,gData->Getsltw(2),0,0,gHeader->GetWeight());
      fGeneralSLT_3_ExclTrigCuts->Fill(fGeneralSLT_3_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_4_ExclTrigCuts,32,gData->Getsltw(3),0,0,gHeader->GetWeight());
      fGeneralSLT_4_ExclTrigCuts->Fill(fGeneralSLT_4_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_5_ExclTrigCuts,32,gData->Getsltw(4),0,0,gHeader->GetWeight());
      fGeneralSLT_5_ExclTrigCuts->Fill(fGeneralSLT_5_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralSLT_6_ExclTrigCuts,32,gData->Getsltw(5),0,0,gHeader->GetWeight());
      fGeneralSLT_6_ExclTrigCuts->Fill(fGeneralSLT_6_ExclTrigCuts->GetNbinsX()-1,gHeader->GetWeight());

      // fill tlt bits
      FillBitIntoHistogram(fGeneralTLT_SPP_ExclTrigCuts,16,gData->Gettltw(2),0,1,gHeader->GetWeight());
      fGeneralTLT_SPP_ExclTrigCuts->Fill(fGeneralTLT_SPP_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS_ExclTrigCuts,16,gData->Gettltw(3),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS_ExclTrigCuts,16,gData->Gettltw(10),0,17,gHeader->GetWeight());
      fGeneralTLT_DIS_ExclTrigCuts->Fill(fGeneralTLT_DIS_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP_ExclTrigCuts,16,gData->Gettltw(4),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP_ExclTrigCuts,16,gData->Gettltw(11),0,17,gHeader->GetWeight());
      fGeneralTLT_HPP_ExclTrigCuts->Fill(fGeneralTLT_HPP_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO_ExclTrigCuts,16,gData->Gettltw(5),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO_ExclTrigCuts,16,gData->Gettltw(12),0,17,gHeader->GetWeight());
      fGeneralTLT_EXO_ExclTrigCuts->Fill(fGeneralTLT_EXO_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_MUO_ExclTrigCuts,16,gData->Gettltw(6),0,1,gHeader->GetWeight());
      fGeneralTLT_MUO_ExclTrigCuts->Fill(fGeneralTLT_MUO_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_VTX_ExclTrigCuts,16,gData->Gettltw(7),0,1,gHeader->GetWeight());
      fGeneralTLT_VTX_ExclTrigCuts->Fill(fGeneralTLT_VTX_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM_ExclTrigCuts,16,gData->Gettltw(8),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM_ExclTrigCuts,16,gData->Gettltw(14),0,17,gHeader->GetWeight());
      fGeneralTLT_HFM_ExclTrigCuts->Fill(fGeneralTLT_HFM_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL_ExclTrigCuts,16,gData->Gettltw(9),0,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL_ExclTrigCuts,16,gData->Gettltw(13),0,17,gHeader->GetWeight());
      fGeneralTLT_HFL_ExclTrigCuts->Fill(fGeneralTLT_HFL_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());

      FillBitIntoHistogram(fGeneralTLT_SPP_after_prescale_ExclTrigCuts,16,gData->Gettltw(2),16,1,gHeader->GetWeight());
      fGeneralTLT_SPP_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_SPP_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS_after_prescale_ExclTrigCuts,16,gData->Gettltw(3),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_DIS_after_prescale_ExclTrigCuts,16,gData->Gettltw(10),16,17,gHeader->GetWeight());
      fGeneralTLT_DIS_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_DIS_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP_after_prescale_ExclTrigCuts,16,gData->Gettltw(4),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HPP_after_prescale_ExclTrigCuts,16,gData->Gettltw(11),16,17,gHeader->GetWeight());
      fGeneralTLT_HPP_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_HPP_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO_after_prescale_ExclTrigCuts,16,gData->Gettltw(5),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_EXO_after_prescale_ExclTrigCuts,16,gData->Gettltw(12),16,17,gHeader->GetWeight());
      fGeneralTLT_EXO_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_EXO_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_MUO_after_prescale_ExclTrigCuts,16,gData->Gettltw(6),16,1,gHeader->GetWeight());
      fGeneralTLT_MUO_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_MUO_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_VTX_after_prescale_ExclTrigCuts,16,gData->Gettltw(7),16,1,gHeader->GetWeight());
      fGeneralTLT_VTX_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_VTX_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM_after_prescale_ExclTrigCuts,16,gData->Gettltw(8),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFM_after_prescale_ExclTrigCuts,16,gData->Gettltw(14),16,17,gHeader->GetWeight());
      fGeneralTLT_HFM_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_HFM_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_ExclTrigCuts,16,gData->Gettltw(9),16,1,gHeader->GetWeight());
      FillBitIntoHistogram(fGeneralTLT_HFL_after_prescale_ExclTrigCuts,16,gData->Gettltw(13),16,17,gHeader->GetWeight());
      fGeneralTLT_HFL_after_prescale_ExclTrigCuts->Fill(fGeneralTLT_HFL_after_prescale_ExclTrigCuts->GetNbinsX(),gHeader->GetWeight());

    }


  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::Do() {
  //
  // execute per event
  if ( gDebug ) cout << endl << "GTrigger::Do() called" << endl << endl;

  CheckCutTLTEXO96p00p();
  CheckCutTLTEXO03p04p();
  CheckCutTLTEXO05e06e();
  CheckCutTLTEXO06p07p();
  CheckCutTLTHPP96p00p();
  CheckCutTLTHPP03p04p();
  CheckCutTLTHPP05e06e();
  CheckCutTLTHPP06p07p();
  CheckCutTLTHFL96p00p();
  CheckCutTLTHFL99p00p();
  CheckCutTLTHFL03p04p();
  CheckCutTLTHFL05e06e();
  CheckCutTLTHFL06p07p();
  CheckCutTLTDIS96p00p();
  CheckCutTLTDIS03p04p();
  CheckCutTLTDIS05e06e();
  CheckCutTLTDIS06p07p();
  CheckCutTLTMUO96p00p();
  CheckCutTLTMUO03p04p();
  CheckCutTLTMUO05e06e();
  CheckCutTLTMUO06p07p();
  CheckCutTLTSPP03p04p();
  CheckCutTLTSPP05e06e();
  CheckCutTLTSPP06p07p();
  CheckHadronOrMuonTrigger();
  CheckAllCuts();
  CheckDiJetTrigger();  

  return kTRUE;
}

// //_____________________________________________________________

 Bool_t GTrigger::CheckHadronOrMuonTrigger() {
   //
   // check if hadron or muon trigger has fired. ONLY VALID FOR INGOS TRIGGER SELECTION!!!
   // Needs to be made aware of the triggers that are chosen in the cards. 050413
   if ( gDebug ) cout << endl << "GTrigger::CheckHadronOrMuonTrigger() called" << endl << endl;
   if(
      EventTriggeredByTLTHPP(14)
      || EventTriggeredByTLTHFL(10)
      || EventTriggeredByTLTHFL(11)
      ) {
     fHadronTriggered = kTRUE;
   }
   if( 
      //BRMuo Triggers
      EventTriggeredByTLTMUO(3)
      // HFL Muon Triggers
      || EventTriggeredByTLTHFL(1) 
      // EXO Muon Triggers (outer muon chambers)
      || EventTriggeredByTLTEXO(11) 
      || EventTriggeredByTLTEXO(12)
      // DIS Muon Triggers
      || EventTriggeredByTLTDIS(27) 
       ){
     fMuonTriggered = kTRUE;
   }
   if(      // FMUO Triggers
      EventTriggeredByTLTMUO(1) 
      || EventTriggeredByTLTMUO(2) 
      || EventTriggeredByTLTMUO(4)
      ){
     fFMuonTriggered = kTRUE;
   }
   if( EventTriggeredByTLTDIS(3) ){
     fDISTLTTriggered = kTRUE;
   }

   return kTRUE;
 }

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTEXO96p00p() {
  //
  // check exo trigger bits for 96p-00p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTEXO96p00p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTEXO96p00p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first exo word (tlt word 6, prescaled)
	if ( gData->Gettltw(5) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTEXO96p00p = kTRUE;
	}
      } else {
	// second exo word (tlt word 13, prescaled)
	if ( gData->Gettltw(12) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTEXO96p00p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTEXO03p04p() {
  //
  // check exo trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTEXO03p04p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTEXO03p04p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first exo word (tlt word 6, prescaled)
	if ( gData->Gettltw(5) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTEXO03p04p = kTRUE;
	}
      } else {
	// second exo word (tlt word 13, prescaled)
	if ( gData->Gettltw(12) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTEXO03p04p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}
//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTEXO05e06e() {
  //
  // check exo trigger bits for 05e-06e
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTEXO05e06e() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTEXO05e06e();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first exo word (tlt word 6, prescaled)
	if ( gData->Gettltw(5) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTEXO05e06e = kTRUE;
	}
      } else {
	// second exo word (tlt word 13, prescaled)
	if ( gData->Gettltw(12) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTEXO05e06e = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTEXO06p07p() {
  //
  // check exo trigger bits for 06p-07p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTEXO06p07p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTEXO06p07p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first exo word (tlt word 6, prescaled)
	if ( gData->Gettltw(5) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTEXO06p07p = kTRUE;
	}
      } else {
	// second exo word (tlt word 13, prescaled)
	if ( gData->Gettltw(12) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTEXO06p07p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHPP96p00p() {
  //
  // check hpp trigger bits for 96p-00p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHPP96p00p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHPP96p00p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hpp word (tlt word 5, prescaled)
	if ( gData->Gettltw(4) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHPP96p00p = kTRUE;
	}
      } else {
	// second hpp word (tlt word 12, prescaled)
	if ( gData->Gettltw(11) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHPP96p00p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHPP03p04p() {
  //
  // check hpp trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHPP03p04p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHPP03p04p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hpp word (tlt word 5, prescaled)
	if ( gData->Gettltw(4) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHPP03p04p = kTRUE;
	}
      } else {
	// second hpp word (tlt word 12, prescaled)
	if ( gData->Gettltw(11) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHPP03p04p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHPP05e06e() {
  //
  // check hpp trigger bits for 05e-06e
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHPP05e06e() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHPP05e06e();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hpp word (tlt word 5, prescaled)
	if ( gData->Gettltw(4) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHPP05e06e = kTRUE;
	}
      } else {
	// second hpp word (tlt word 12, prescaled)
	if ( gData->Gettltw(11) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHPP05e06e = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHPP06p07p() {
  //
  // check hpp trigger bits for 06p-07p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHPP06p07p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHPP06p07p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hpp word (tlt word 5, prescaled)
	if ( gData->Gettltw(4) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHPP06p07p = kTRUE;
	}
      } else {
	// second hpp word (tlt word 12, prescaled)
	if ( gData->Gettltw(11) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHPP06p07p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHFL96p00p() {
  //
  // check hfl trigger bits for 96p-00p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHFL96p00p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHFL96p00p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hlf word (tlt word 10, prescaled)
	if ( gData->Gettltw(9) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHFL96p00p = kTRUE;
	}
      } else {
	// second hfl word (tlt word 14, prescaled)
	if ( gData->Gettltw(13) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHFL96p00p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHFL99p00p() {
  //
  // check hfl trigger bits for 99p-00p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHFL99p00p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHFL99p00p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hlf word (tlt word 10, prescaled)
	if ( gData->Gettltw(9) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHFL99p00p = kTRUE;
	}
      } else {
	// second hfl word (tlt word 14, prescaled)
	if ( gData->Gettltw(13) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHFL99p00p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHFL03p04p() {
  //
  // check hfl trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHFL03p04p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHFL03p04p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hlf word (tlt word 10, prescaled)
	if ( gData->Gettltw(9) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHFL03p04p = kTRUE;
	}
      } else {
	// second hfl word (tlt word 14, prescaled)
	if ( gData->Gettltw(13) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHFL03p04p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}
 //_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHFL05e06e() {
  //
  // check hfl trigger bits for 05e-06e
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHFL05e06e() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHFL05e06e();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hlf word (tlt word 10, prescaled)
	if ( gData->Gettltw(9) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHFL05e06e = kTRUE;
	}
      } else {
	// second hfl word (tlt word 14, prescaled)
	if ( gData->Gettltw(13) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHFL05e06e = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTHFL06p07p() {
  //
  // check hfl trigger bits for 06p-07p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTHFL06p07p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTHFL06p07p();

  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
	// first hlf word (tlt word 10, prescaled)
	if ( gData->Gettltw(9) & (UInt_t)TMath::Power(2,i+15)) {
	  fCutTLTHFL06p07p = kTRUE;
	}
      } else {
	// second hfl word (tlt word 14, prescaled)
	if ( gData->Gettltw(13) & (UInt_t)TMath::Power(2,i-1)) {
	  fCutTLTHFL06p07p = kTRUE;
	}
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTDIS96p00p() {
  //
  // check dis trigger bits for 96p-00p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTDIS96p00p() called" << endl << endl;
  
  UInt_t checkpattern = gCards->GetTriggerTLTDIS96p00p();
  
  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
 	// first dis word (tlt word 4, prescaled)
 	if ( gData->Gettltw(3) & (UInt_t)TMath::Power(2,i+15)) {
 	  fCutTLTDIS96p00p = kTRUE;
 	}
      } else {
 	// second dis word (tlt word 11, prescaled)
 	if ( gData->Gettltw(10) & (UInt_t)TMath::Power(2,i-1)) {
 	  fCutTLTDIS96p00p = kTRUE;
 	}
      }
    }
    
  }
  
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTDIS03p04p() {
  //
  // check dis trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTDIS03p04p() called" << endl << endl;
  
  UInt_t checkpattern = gCards->GetTriggerTLTDIS03p04p();
  
  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
 	// first dis word (tlt word 4, prescaled)
 	if ( gData->Gettltw(3) & (UInt_t)TMath::Power(2,i+15)) {
 	  fCutTLTDIS03p04p = kTRUE;
 	}
      } else {
 	// second dis word (tlt word 11, prescaled)
 	if ( gData->Gettltw(10) & (UInt_t)TMath::Power(2,i-1)) {
 	  fCutTLTDIS03p04p = kTRUE;
 	}
      }
    }
    
  }
  
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTDIS05e06e() {
  //
  // check dis trigger bits for 05e-06e
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTDIS05e06e() called" << endl << endl;
  
  UInt_t checkpattern = gCards->GetTriggerTLTDIS05e06e();
  
  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
 	// first dis word (tlt word 4, prescaled)
 	if ( gData->Gettltw(3) & (UInt_t)TMath::Power(2,i+15)) {
 	  fCutTLTDIS05e06e = kTRUE;
 	}
      } else {
 	// second dis word (tlt word 11, prescaled)
 	if ( gData->Gettltw(10) & (UInt_t)TMath::Power(2,i-1)) {
 	  fCutTLTDIS05e06e = kTRUE;
 	}
      }
    }
    
  }
  
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTDIS06p07p() {
  //
  // check dis trigger bits for 06p-07p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTDIS06p07p() called" << endl << endl;
  
  UInt_t checkpattern = gCards->GetTriggerTLTDIS06p07p();
  
  for ( Int_t i =0; i < 32; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      if ( i < 16 ) {
 	// first dis word (tlt word 4, prescaled)
 	if ( gData->Gettltw(3) & (UInt_t)TMath::Power(2,i+15)) {
 	  fCutTLTDIS06p07p = kTRUE;
 	}
      } else {
 	// second dis word (tlt word 11, prescaled)
 	if ( gData->Gettltw(10) & (UInt_t)TMath::Power(2,i-1)) {
 	  fCutTLTDIS06p07p = kTRUE;
 	}
      }
    }
    
  }
  
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTMUO96p00p() {
  //
  // check muo trigger bits for 96p-00p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTMUO96p00p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTMUO96p00p();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(6) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTMUO96p00p = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTMUO03p04p() {
  //
  // check hlf trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTMUO03p04p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTMUO03p04p();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(6) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTMUO03p04p = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTMUO05e06e() {
  //
  // check hlf trigger bits for 05e-06e
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTMUO05e06e() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTMUO05e06e();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(6) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTMUO05e06e = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTMUO06p07p() {
  //
  // check hlf trigger bits for 06p-07p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTMUO06p07p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTMUO06p07p();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(6) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTMUO06p07p = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTSPP03p04p() {
  //
  // check SPP trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTSPP03p04p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTSPP03p04p();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(2) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTSPP03p04p = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTSPP05e06e() {
  //
  // check SPP trigger bits for 05e-06e
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTSPP05e06e() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTSPP05e06e();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(2) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTSPP05e06e = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckCutTLTSPP06p07p() {
  //
  // check SPP trigger bits for 06p-07p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTSPP06p07p() called" << endl << endl;

  UInt_t checkpattern = gCards->GetTriggerTLTSPP06p07p();

  for ( Int_t i =0; i < 16; ++i ) {
    // check if bit is required
    if ( checkpattern & (UInt_t)TMath::Power(2,i) ) {
      // first hlf word (tlt word 10, prescaled)
      if ( gData->Gettltw(2) & (UInt_t)TMath::Power(2,i+15)) {
	fCutTLTSPP06p07p = kTRUE;
      }
    }

  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::CheckDiJetTrigger() {
  //
  // check hlf trigger bits for 03p-04p
  if ( gDebug ) cout << endl << "GTrigger::CheckTLTMUO03p04p() called" << endl << endl;

  
	  if (gData->Gettltw(4) & (Int_t)TMath::Power(2,13)) {  
	    fHpp_trig = kTRUE;
	  }
	  if (gData->Gettltw(9) & (Int_t)TMath::Power(2,0)){
	    fHfl_trig = kTRUE;
	  }
	  
	  if (gData->Gettltw(6) & (Int_t)TMath::Power(2,2)){
	    fMuo3  = kTRUE;
	    fMuo_trig = kTRUE;
	  }
	  if (gData->Gettltw(5) & (Int_t)TMath::Power(2,10)){
	    fExo11 = kTRUE;
	    fMuo_trig = kTRUE;
	  }
	  if (gData->Gettltw(5) & (Int_t)TMath::Power(2,11)){
	    fExo12 = kTRUE;
	    fMuo_trig = kTRUE;
	  }

if ((fMuo_trig) && (!fHpp_trig ) &&  (!fHfl_trig)) {  
    fDiJetOnlyMuonTriggered = kTRUE;
  }


  return kTRUE;
}



//_____________________________________________________________

Bool_t GTrigger::CheckAllCuts() {
  //
  // check all trigger cuts depending on run period
  if ( gDebug ) cout << endl << "GTrigger::CheckAllCuts() called" << endl << endl;

  EZRunPeriod period = gGeneral->GetRunPeriod();

  UInt_t checkpattern = gCards->GetTriggerTLTEXO96p00p();
  checkpattern += gCards->GetTriggerTLTEXO03p04p();
  checkpattern += gCards->GetTriggerTLTEXO05e06e();
  checkpattern += gCards->GetTriggerTLTEXO06p07p();
  checkpattern += gCards->GetTriggerTLTHPP96p00p();
  checkpattern += gCards->GetTriggerTLTHPP03p04p();
  checkpattern += gCards->GetTriggerTLTHPP05e06e();
  checkpattern += gCards->GetTriggerTLTHPP06p07p();
  checkpattern += gCards->GetTriggerTLTHFL96p00p();
  checkpattern += gCards->GetTriggerTLTHFL99p00p();
  checkpattern += gCards->GetTriggerTLTHFL03p04p();
  checkpattern += gCards->GetTriggerTLTHFL05e06e();
  checkpattern += gCards->GetTriggerTLTHFL06p07p();
  checkpattern += gCards->GetTriggerTLTDIS96p00p();
  checkpattern += gCards->GetTriggerTLTDIS03p04p();
  checkpattern += gCards->GetTriggerTLTDIS05e06e();
  checkpattern += gCards->GetTriggerTLTDIS06p07p();
  checkpattern += gCards->GetTriggerTLTMUO96p00p();
  checkpattern += gCards->GetTriggerTLTMUO03p04p();
  checkpattern += gCards->GetTriggerTLTMUO05e06e();
  checkpattern += gCards->GetTriggerTLTMUO06p07p();
  checkpattern += gCards->GetTriggerTLTSPP03p04p();
  checkpattern += gCards->GetTriggerTLTSPP05e06e();
  checkpattern += gCards->GetTriggerTLTSPP06p07p();

  Bool_t neutral = kFALSE;
  if ( checkpattern == 0 ) {
    neutral = kTRUE;
  }

  if ( (period == k96p) ||
       (period == k97p) ||
       (period == k98e) ||
       (period == k99e) ||
       (period == k96p97p) ||
       (period == k98e99e) ) {
    if ( fCutTLTEXO96p00p || fCutTLTHPP96p00p || fCutTLTHFL96p00p || fCutTLTDIS96p00p || fCutTLTMUO96p00p ) {
      fCutAllCuts = kTRUE;
    }
  }
       
  if ( (period == k99p) ||
       (period == k00p) ||
       (period == k99p00p) ) {
    if ( fCutTLTEXO96p00p || fCutTLTHPP96p00p || fCutTLTHFL99p00p || fCutTLTHFL96p00p || fCutTLTDIS96p00p || fCutTLTMUO96p00p ) {
      fCutAllCuts = kTRUE;
    }
  }

  if ( (period == k02p) ||
       (period == k03p) ||
       (period == k04p) ||
       (period == k05e) ||
       (period == k06e) ||
       (period == k06p) ||
       (period == k07p) ||
       (period == k03p04p)||
       (period == k05e06e)||
       (period == k06p07p) ) {

    if( fCutTLTEXO03p04p || fCutTLTEXO05e06e || fCutTLTEXO06p07p || fCutTLTHPP03p04p || fCutTLTHPP05e06e || fCutTLTHPP06p07p || fCutTLTHFL03p04p || fCutTLTHFL05e06e || fCutTLTHFL06p07p || fCutTLTDIS03p04p || fCutTLTDIS05e06e || fCutTLTDIS06p07p || fCutTLTMUO03p04p || fCutTLTMUO05e06e || fCutTLTMUO06p07p || fCutTLTSPP03p04p || fCutTLTSPP05e06e || fCutTLTSPP06p07p ) {
      fCutAllCuts = kTRUE;
    }
  }

  if ( neutral )
    fCutAllCuts = kTRUE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::Reset() {
  //
  // reset for each new event
  if ( gDebug ) cout << endl << "GTrigger::Reset() called" << endl << endl;

//   // reset trigger logic flags
   fHadronTriggered = kFALSE;                               // a hadron trigger from Ingos trigger selection has fired.
   fMuonTriggered   = kFALSE;                               // a muon   trigger from Ingos trigger selection has fired.
   fFMuonTriggered   = kFALSE;                               // a muon   trigger from Ingos trigger selection has fired.
   fDISTLTTriggered = kFALSE;                               // a DIS TLT trigger from Ingos trigger selection has fired.
  
   fDiJetOnlyMuonTriggered = kFALSE;      
   
  fHpp_trig = kFALSE;
  fHfl_trig = kFALSE;
  fMuo_trig = kFALSE;
  fMuo3     = kFALSE;
  fExo11    = kFALSE;
  fExo12    = kFALSE;
 

 // reset cut flags
  fCutTLTEXO96p00p = kFALSE;
  fCutTLTEXO03p04p = kFALSE;
  fCutTLTEXO05e06e = kFALSE;
  fCutTLTEXO06p07p = kFALSE;

  fCutTLTHPP96p00p = kFALSE;
  fCutTLTHPP03p04p = kFALSE;
  fCutTLTHPP05e06e = kFALSE;
  fCutTLTHPP06p07p = kFALSE;

  fCutTLTHFL96p00p = kFALSE;
  fCutTLTHFL99p00p = kFALSE;
  fCutTLTHFL03p04p = kFALSE;
  fCutTLTHFL05e06e = kFALSE;
  fCutTLTHFL06p07p = kFALSE;

  fCutTLTDIS96p00p = kFALSE;
  fCutTLTDIS03p04p = kFALSE;
  fCutTLTDIS05e06e = kFALSE;
  fCutTLTDIS06p07p = kFALSE;

  fCutTLTMUO96p00p = kFALSE;
  fCutTLTMUO03p04p = kFALSE;
  fCutTLTMUO05e06e = kFALSE;
  fCutTLTMUO06p07p = kFALSE;

  fCutTLTSPP03p04p = kFALSE;
  fCutTLTSPP05e06e = kFALSE;
  fCutTLTSPP06p07p = kFALSE;

  fCutAllCuts      = kFALSE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::GetAllCuts() {
  //
  // return flag if event passes all trigger cuts
  if ( gDebug ) cout << endl << "GTrigger::GetAllCuts() called" << endl << endl;
  
  return fCutAllCuts;
}

//_____________________________________________________________

Bool_t GTrigger::FillBitIntoHistogram(TH1D *histo, Int_t number, UInt_t bit, Int_t bitoffset, Int_t filloffset, Double_t weight) {
  //
  // fill histogram with bit pattern
  if ( gDebug ) cout << endl << "GTrigger::FillBitIntoHistogram called" << endl << endl;

  for ( Int_t i = 0; i < number; ++i ) {
    if ( bit & (UInt_t)TMath::Power(2,i+bitoffset) )
      histo->Fill(i+filloffset,weight);
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTSPP() {
  //
  // return true if event is triggered by any spp tlt slot
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTSPP called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if one of the bits 16 or larger is set, return kTRUE
  if ( gData->Gettltw(2) >= 65536 )
    triggered = kTRUE;

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTVTX() {
  //
  // return true if event is triggered by any VTX tlt slot
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTSPP called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if one of the bits is set, return kTRUE
  if ( gData->Gettltw(7) >= 1 )
    triggered = kTRUE;

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTHPP() {
  //
  // return true if event is triggered by any hpp tlt slot
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTHPP called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if one of the bits 16 or larger is set, return kTRUE
  if ( gData->Gettltw(4) >= 65536 )
    triggered = kTRUE;

  // if one of the bits 16 or larger is set, return kTRUE
  if ( gData->Gettltw(11) >= 65536 )
    triggered = kTRUE;

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTDIS() {
  //
  // return true if event is triggered by any dis tlt slot
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTDIS called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if one of the bits 16 or larger is set, return kTRUE
  if ( gData->Gettltw(3) >= 65536 )
    triggered = kTRUE;

  // if one of the bits 16 or larger is set, return kTRUE
  if ( gData->Gettltw(10) >= 65536 )
    triggered = kTRUE;

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTHPP(Int_t slot) {
  //
  // return true if event is triggered by any hpp tlt slot
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTHPP(Int_t slot) called" << endl << endl;
  
  Bool_t triggered = kFALSE;

   // if slot > 16, then take different hpp word
   if ( slot <= 16 ) {
     if ( gData->Gettltw(4) & (UInt_t)TMath::Power(2,slot+15) )
       triggered = kTRUE;
   } else {
     if ( gData->Gettltw(11) & (UInt_t)TMath::Power(2,slot-1) )
       triggered = kTRUE;
   }

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTHFL(Int_t slot) {
  //
  // return true if event is triggered by specified hfl tlt slot
  // slot is labeled 1 to 32
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTHFL(Int_t slot) called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if slot > 16, then take different tlt word
  if ( slot <= 16 ) {
    if ( gData->Gettltw(9) & (UInt_t)TMath::Power(2,slot+15) )
      triggered = kTRUE;
  } else {
    if ( gData->Gettltw(13) & (UInt_t)TMath::Power(2,slot-1) )
      triggered = kTRUE;
  }

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTEXO(Int_t slot) {
  //
  // return true if event is triggered by specified exo tlt slot
  // slot is labeled 1 to 32
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTEXO(Int_t slot) called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if slot > 16, then take different tlt word
  if ( slot <= 16 ) {
    if ( gData->Gettltw(5) & (UInt_t)TMath::Power(2,slot+15) )
      triggered = kTRUE;
  } else {
    if ( gData->Gettltw(12) & (UInt_t)TMath::Power(2,slot-1) )
      triggered = kTRUE;
  }

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTDIS(Int_t slot) {
  //
  // return true if event is triggered by specified dis tlt slot
  // slot is labeled 1 to 32
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTDIS(Int_t slot) called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if slot > 16, then take different tlt word
  if ( slot <= 16 ) {
    if ( gData->Gettltw(3) & (UInt_t)TMath::Power(2,slot+15) )
      triggered = kTRUE;
  } else {
    if ( gData->Gettltw(10) & (UInt_t)TMath::Power(2,slot-1) )
      triggered = kTRUE;
  }

  return triggered;
}

//_____________________________________________________________

Bool_t GTrigger::EventTriggeredByTLTMUO(Int_t slot) {
  //
  // return true if event is triggered by specified muo tlt slot
  // slot is labeled 1 to 32
  if ( gDebug ) cout << endl << "GTrigger::EventTriggeredByTLTMUO(Int_t slot) called" << endl << endl;
  
  Bool_t triggered = kFALSE;

  // if slot > 16, then take different tlt word
  if ( gData->Gettltw(6) & (UInt_t)TMath::Power(2,slot+15) )
    triggered = kTRUE;

  return triggered;
}

//_____________________________________________________________

Double_t GTrigger::GetWeight() {
  //
  // return event weight from trigger efficiency correction
  if ( gDebug ) cout << endl << "GTrigger::GetWeight called" << endl << endl;
  
  Double_t weight = 1.0;

  if ( gCards->GetMC()){
       //&& !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
    if ( gCards->GetTriggerEfficiencyCorrection() ) {

      if (( fDiJetOnlyMuonTriggered) && (!gMuons->GetGlomus())){
	weight = 0.0;
      }
      // check for flt 10,11
      if ( (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,10)) ||
	   (gData->Getfltpsw(0) & (UInt_t)TMath::Power(2,11)) ) {
	weight = weight*gCards->GetTriggerEffCorr1011();
	// check for OR of FLT 42,44,51,52,53,54
      } else if ( (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,10)) ||
		  (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,12)) ||
		  (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,19)) ||
		  (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,20)) ||
		  (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,21)) ||
		  (gData->Getfltpsw(1) & (UInt_t)TMath::Power(2,22))) {
	GMJMatch *match = gMJMatchs->GetChosen();
	if ( match != 0 ) {
	  GMuon *muon = match->GetMuon();
	  if ( muon != 0 ) {
	    if ( muon->GetType() == kForward ) {
	      weight = weight*gCards->GetTriggerEffCorr4254Forward()*gCards->GetTriggerEffCorr1011();
	    } else if ( muon->GetType() == kBarrel ) {
	      weight = weight*gCards->GetTriggerEffCorr4254Barrel()*gCards->GetTriggerEffCorr1011();
	    } else if ( muon->GetType() == kRear ) {
	      weight = weight*gCards->GetTriggerEffCorr4254Rear()*gCards->GetTriggerEffCorr1011();
	    }
	  }
	}
      }	
    }
    else if( gCards->GetTriggerDimuonEfficiencyCorrection() ){
      // calculate trigger efficiency correction weight for 
      // method used in GMuons below "Achim's muquana START". 
      // Missing card for "Achim's muquana" activation - will come soon! 050415 ibl
      // ingo's dimuon uncut DIS plots start:
      GDIMuon * dimuon = 0; 
      if( gDIMuons->GetNDIMuons() > 0 ) dimuon = gDIMuons->GetDIMuon(0);
      if( dimuon != 0 ){
	GMuon *muon1 = dimuon->GetMuon1();
	GMuon *muon2 = dimuon->GetMuon2();
	// make sure, it is consistent with trigger selection in your card!!!
	if( GetMuonTriggered() && !GetHadronTriggered() && !GetDISTLTTriggered() ) {
	  // muon trigger efficiency (after BREMAT/MBTAKE) is higher in MC than data
	  // .88 per muon, 8% of 6% for mbtake =.995 (only Achim, not me!)
	  // test both GLOMU and BREMAT to allow also non-isolated muons
	  if( 
	     ( muon1->GetGlomuID()+ muon1->GetBrematID())!=0 
	     &&( muon2->GetGlomuID() + muon2->GetBrematID())!=0
	     ){
	    // both can trigger
	    // Achim	    weight = weight * 0.995 * (1.-(TMath::Power( (1. - 0.88) ,2) ));
	    weight = weight * (1.- (TMath::Power( (1. - 0.88) ,2) ) );
	  }
	  else if(
		  ( muon1->GetGlomuID()+ muon1->GetBrematID()) 
		  + ( muon2->GetGlomuID() + muon2->GetBrematID()) !=0
		  ){
	    // only one can trigger
	    // Achim  weight = weight * 0.995 * 0.88;
	    weight = weight * 0.88;
	  }
	  else{
	    // none can trigger (presumably efficiency correction)
	    weight = 0.0;
	  }
	}
	if( GetFMuonTriggered() && !GetHadronTriggered() && !GetDISTLTTriggered() &&!GetMuonTriggered() ){
	  // muon trigger efficiency (for FMUON) is higher in MC than in data
	  // scale to FMUTAKE/Total ratio
	  weight = weight * 0.89;
	}
      }
    }
  }
  return weight;
}
