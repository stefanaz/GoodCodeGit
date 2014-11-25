#include <TH1D.h>
#include <TH2F.h>
using namespace std;

TH1D* h_DR_accept_all;
TH2F* h_DR_mmu_accept_all;
TH2F* h_ptmus_all;
TH2F* h_dphi_all;
TH1D* h_ptmu_all;
TH1D* h_dimuptmu_all;
TH1D* h_mmu_accept_all;
TH1D* h_muqual_accept_all;
TH1D* h_mueta_accept_all;
TH1D* h_caletm2ir_accept_all;
TH1D* h_triggers_all;
TH1D* h_ptasym_all;
TH1D* h_dphii_all;
TH1D* h_deta_all;
TH1D* h_thrust_all;
TH1D* h_empz_all;
TH1D* h_thrust_mu_ptrel_all;
TH1D* h_dimuphi_all;
TH1D* h_dimueta_all;
TH1D* h_cal_et_all;
TH1D* h_dimulog10q2si_all;
TH1D* h_etex2ir_all;
TH1D* h_dimuxsecpt_all;
TH1D* h_dimuxseceta_all;
TH1D* h_dimuxsecfinders_all;
TH1D* h_dimuxsecdr_all;
TH1D* h_dimuxsecdphi_all;
TH1D* h_dimuxsecptb_all;
TH1D* h_dimuxsecptb_sameb_all;
TH1D* h_dimuxsecptb_diffb_all;
TH1D* h_dimuxsecptb_samecone_all;
TH1D* h_dimuxsecptb_asym_all;
TH1D* h_cal_et_m_et2ir_all;
TH1D* h_cal_et_m_cal_et_10_all;
TH1D* h_PtRel_accept_all;
TH1D* h_muissqsum_accept_all;
TH1D* h_mcdimumass1bin_any_all;
TH1D* h_mcdimumass1bin_true_hfl_mu_all;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecPt_any_all;
TH1D* h_mcdimuxsecPt_true_hfl_mu_all;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecEta_any_all;
TH1D* h_mcdimuxsecEta_true_hfl_mu_all;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecFinders_any_all;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_all;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecDR_any_all;
TH1D* h_mcdimuxsecDR_true_hfl_mu_all;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecDphi_any_all;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_all;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_any_all;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_sameb_any_all;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_diffb_any_all;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_samecone_any_all;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_asym_any_all;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_all;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_all;

TH1D* h_DR_accept_lm_us;
TH2F* h_DR_mmu_accept_lm_us;
TH2F* h_ptmus_lm_us;
TH2F* h_dphi_lm_us;
TH1D* h_ptmu_lm_us;
TH1D* h_dimuptmu_lm_us;
TH1D* h_mmu_accept_lm_us;
TH1D* h_muqual_accept_lm_us;
TH1D* h_mueta_accept_lm_us;
TH1D* h_caletm2ir_accept_lm_us;
TH1D* h_triggers_lm_us;
TH1D* h_ptasym_lm_us;
TH1D* h_dphii_lm_us;
TH1D* h_deta_lm_us; 
TH1D* h_thrust_lm_us;
TH1D* h_empz_lm_us;
TH1D* h_thrust_mu_ptrel_lm_us;
TH1D* h_dimuphi_lm_us;
TH1D* h_dimueta_lm_us;
TH1D* h_cal_et_lm_us;
TH1D* h_dimulog10q2si_lm_us;
TH1D* h_etex2ir_lm_us;
TH1D* h_dimuxsecpt_lm_us;
TH1D* h_dimuxseceta_lm_us;
TH1D* h_dimuxsecfinders_lm_us;
TH1D* h_dimuxsecdr_lm_us;
TH1D* h_dimuxsecdphi_lm_us;
TH1D* h_dimuxsecptb_lm_us;
TH1D* h_dimuxsecptb_sameb_lm_us;
TH1D* h_dimuxsecptb_diffb_lm_us;
TH1D* h_dimuxsecptb_samecone_lm_us;
TH1D* h_dimuxsecptb_asym_lm_us;
TH1D* h_cal_et_m_et2ir_lm_us;
TH1D* h_cal_et_m_cal_et_10_lm_us;
TH1D* h_PtRel_accept_lm_us;
TH1D* h_muissqsum_accept_lm_us;
TH1D* h_mcdimumass1bin_any_lm_us;
TH1D* h_mcdimumass1bin_true_hfl_mu_lm_us;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPt_any_lm_us;
TH1D* h_mcdimuxsecPt_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecEta_any_lm_us;
TH1D* h_mcdimuxsecEta_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecFinders_any_lm_us;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecDR_any_lm_us;
TH1D* h_mcdimuxsecDR_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecDphi_any_lm_us;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_any_lm_us;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_sameb_any_lm_us;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_diffb_any_lm_us;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_samecone_any_lm_us;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_asym_any_lm_us;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_lm_us;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_lm_us;

TH1D* h_DR_accept_lm_ls;
TH2F* h_DR_mmu_accept_lm_ls;
TH2F* h_ptmus_lm_ls;
TH2F* h_dphi_lm_ls;
TH1D* h_ptmu_lm_ls;
TH1D* h_dimuptmu_lm_ls;
TH1D* h_mmu_accept_lm_ls;
TH1D* h_muqual_accept_lm_ls;
TH1D* h_mueta_accept_lm_ls;
TH1D* h_caletm2ir_accept_lm_ls;
TH1D* h_triggers_lm_ls;
TH1D* h_ptasym_lm_ls;
TH1D* h_dphii_lm_ls;
TH1D* h_deta_lm_ls; 
TH1D* h_thrust_lm_ls;
TH1D* h_empz_lm_ls;
TH1D* h_thrust_mu_ptrel_lm_ls;
TH1D* h_dimuphi_lm_ls;
TH1D* h_dimueta_lm_ls;
TH1D* h_cal_et_lm_ls;
TH1D* h_dimulog10q2si_lm_ls;
TH1D* h_etex2ir_lm_ls;
TH1D* h_dimuxsecpt_lm_ls;
TH1D* h_dimuxseceta_lm_ls;
TH1D* h_dimuxsecfinders_lm_ls;
TH1D* h_dimuxsecdr_lm_ls;
TH1D* h_dimuxsecdphi_lm_ls;
TH1D* h_dimuxsecptb_lm_ls;
TH1D* h_dimuxsecptb_sameb_lm_ls;
TH1D* h_dimuxsecptb_diffb_lm_ls;
TH1D* h_dimuxsecptb_samecone_lm_ls;
TH1D* h_dimuxsecptb_asym_lm_ls;
TH1D* h_cal_et_m_et2ir_lm_ls;
TH1D* h_cal_et_m_cal_et_10_lm_ls;
TH1D* h_PtRel_accept_lm_ls;
TH1D* h_muissqsum_accept_lm_ls;
TH1D* h_mcdimumass1bin_any_lm_ls;
TH1D* h_mcdimumass1bin_true_hfl_mu_lm_ls;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPt_any_lm_ls;
TH1D* h_mcdimuxsecPt_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecEta_any_lm_ls;
TH1D* h_mcdimuxsecEta_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecFinders_any_lm_ls;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecDR_any_lm_ls;
TH1D* h_mcdimuxsecDR_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecDphi_any_lm_ls;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_any_lm_ls;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_sameb_any_lm_ls;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_diffb_any_lm_ls;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_samecone_any_lm_ls;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_asym_any_lm_ls;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_lm_ls;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_lm_ls;

TH1D* h_DR_accept_hm_us;
TH2F* h_DR_mmu_accept_hm_us;
TH2F* h_ptmus_hm_us;
TH2F* h_dphi_hm_us;
TH1D* h_ptmu_hm_us;
TH1D* h_dimuptmu_hm_us;
TH1D* h_mmu_accept_hm_us;
TH1D* h_muqual_accept_hm_us;
TH1D* h_mueta_accept_hm_us;
TH1D* h_caletm2ir_accept_hm_us;
TH1D* h_triggers_hm_us;
TH1D* h_ptasym_hm_us;
TH1D* h_dphii_hm_us;
TH1D* h_deta_hm_us; 
TH1D* h_thrust_hm_us;
TH1D* h_empz_hm_us;
TH1D* h_thrust_mu_ptrel_hm_us;
TH1D* h_dimuphi_hm_us;
TH1D* h_dimueta_hm_us;
TH1D* h_cal_et_hm_us;
TH1D* h_dimulog10q2si_hm_us;
TH1D* h_etex2ir_hm_us;
TH1D* h_dimuxsecpt_hm_us;
TH1D* h_dimuxseceta_hm_us;
TH1D* h_dimuxsecfinders_hm_us;
TH1D* h_dimuxsecdr_hm_us;
TH1D* h_dimuxsecdphi_hm_us;
TH1D* h_dimuxsecptb_hm_us;
TH1D* h_dimuxsecptb_sameb_hm_us;
TH1D* h_dimuxsecptb_diffb_hm_us;
TH1D* h_dimuxsecptb_samecone_hm_us;
TH1D* h_dimuxsecptb_asym_hm_us;
TH1D* h_cal_et_m_et2ir_hm_us;
TH1D* h_cal_et_m_cal_et_10_hm_us;
TH1D* h_PtRel_accept_hm_us;
TH1D* h_muissqsum_accept_hm_us;
TH1D* h_mcdimumass1bin_any_hm_us;
TH1D* h_mcdimumass1bin_true_hfl_mu_hm_us;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPt_any_hm_us;
TH1D* h_mcdimuxsecPt_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecEta_any_hm_us;
TH1D* h_mcdimuxsecEta_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecFinders_any_hm_us;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecDR_any_hm_us;
TH1D* h_mcdimuxsecDR_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecDphi_any_hm_us;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_any_hm_us;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_sameb_any_hm_us;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_diffb_any_hm_us;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_samecone_any_hm_us;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_asym_any_hm_us;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_hm_us;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_hm_us;

TH1D* h_DR_accept_hm_ls;
TH2F* h_DR_mmu_accept_hm_ls;
TH2F* h_ptmus_hm_ls;
TH2F* h_dphi_hm_ls;
TH1D* h_ptmu_hm_ls;
TH1D* h_dimuptmu_hm_ls;
TH1D* h_mmu_accept_hm_ls;
TH1D* h_muqual_accept_hm_ls;
TH1D* h_mueta_accept_hm_ls;
TH1D* h_caletm2ir_accept_hm_ls;
TH1D* h_triggers_hm_ls;
TH1D* h_ptasym_hm_ls;
TH1D* h_dphii_hm_ls;
TH1D* h_deta_hm_ls; 
TH1D* h_thrust_hm_ls;
TH1D* h_empz_hm_ls;
TH1D* h_thrust_mu_ptrel_hm_ls;
TH1D* h_dimuphi_hm_ls;
TH1D* h_dimueta_hm_ls;
TH1D* h_cal_et_hm_ls;
TH1D* h_dimulog10q2si_hm_ls;
TH1D* h_etex2ir_hm_ls;
TH1D* h_dimuxsecpt_hm_ls;
TH1D* h_dimuxseceta_hm_ls;
TH1D* h_dimuxsecfinders_hm_ls;
TH1D* h_dimuxsecdr_hm_ls;
TH1D* h_dimuxsecdphi_hm_ls;
TH1D* h_dimuxsecptb_hm_ls;
TH1D* h_dimuxsecptb_sameb_hm_ls;
TH1D* h_dimuxsecptb_diffb_hm_ls;
TH1D* h_dimuxsecptb_samecone_hm_ls;
TH1D* h_dimuxsecptb_asym_hm_ls;
TH1D* h_cal_et_m_et2ir_hm_ls;
TH1D* h_cal_et_m_cal_et_10_hm_ls;
TH1D* h_PtRel_accept_hm_ls;
TH1D* h_muissqsum_accept_hm_ls;
TH1D* h_mcdimumass1bin_any_hm_ls;
TH1D* h_mcdimumass1bin_true_hfl_mu_hm_ls;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPt_any_hm_ls;
TH1D* h_mcdimuxsecPt_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecEta_any_hm_ls;
TH1D* h_mcdimuxsecEta_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecFinders_any_hm_ls;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecDR_any_hm_ls;
TH1D* h_mcdimuxsecDR_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecDphi_any_hm_ls;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_any_hm_ls;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_sameb_any_hm_ls;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_diffb_any_hm_ls;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_samecone_any_hm_ls;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_asym_any_hm_ls;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_hm_ls;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_hm_ls;

TH1D* h_DR_accept_lm_us_is;
TH2F* h_DR_mmu_accept_lm_us_is;
TH2F* h_ptmus_lm_us_is;
TH2F* h_dphi_lm_us_is;
TH1D* h_ptmu_lm_us_is;
TH1D* h_dimuptmu_lm_us_is;
TH1D* h_mmu_accept_lm_us_is;
TH1D* h_muqual_accept_lm_us_is;
TH1D* h_mueta_accept_lm_us_is;
TH1D* h_caletm2ir_accept_lm_us_is;
TH1D* h_triggers_lm_us_is;
TH1D* h_ptasym_lm_us_is;
TH1D* h_dphii_lm_us_is;
TH1D* h_deta_lm_us_is; 
TH1D* h_thrust_lm_us_is;
TH1D* h_empz_lm_us_is;
TH1D* h_thrust_mu_ptrel_lm_us_is;
TH1D* h_dimuphi_lm_us_is;
TH1D* h_dimueta_lm_us_is;
TH1D* h_cal_et_lm_us_is;
TH1D* h_dimulog10q2si_lm_us_is;
TH1D* h_etex2ir_lm_us_is;
TH1D* h_dimuxsecpt_lm_us_is;
TH1D* h_dimuxseceta_lm_us_is;
TH1D* h_dimuxsecfinders_lm_us_is;
TH1D* h_dimuxsecdr_lm_us_is;
TH1D* h_dimuxsecdphi_lm_us_is;
TH1D* h_dimuxsecptb_lm_us_is;
TH1D* h_dimuxsecptb_sameb_lm_us_is;
TH1D* h_dimuxsecptb_diffb_lm_us_is;
TH1D* h_dimuxsecptb_samecone_lm_us_is;
TH1D* h_dimuxsecptb_asym_lm_us_is;
TH1D* h_cal_et_m_et2ir_lm_us_is;
TH1D* h_cal_et_m_cal_et_10_lm_us_is;
TH1D* h_PtRel_accept_lm_us_is;
TH1D* h_muissqsum_accept_lm_us_is;
TH1D* h_mcdimumass1bin_any_lm_us_is;
TH1D* h_mcdimumass1bin_true_hfl_mu_lm_us_is;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPt_any_lm_us_is;
TH1D* h_mcdimuxsecPt_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecEta_any_lm_us_is;
TH1D* h_mcdimuxsecEta_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecFinders_any_lm_us_is;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecDR_any_lm_us_is;
TH1D* h_mcdimuxsecDR_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecDphi_any_lm_us_is;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_any_lm_us_is;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_sameb_any_lm_us_is;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_diffb_any_lm_us_is;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_samecone_any_lm_us_is;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_asym_any_lm_us_is;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_lm_us_is;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_lm_us_is;

TH1D* h_DR_accept_lm_ls_is;
TH2F* h_DR_mmu_accept_lm_ls_is;
TH2F* h_ptmus_lm_ls_is;
TH2F* h_dphi_lm_ls_is;
TH1D* h_ptmu_lm_ls_is;
TH1D* h_dimuptmu_lm_ls_is;
TH1D* h_mmu_accept_lm_ls_is;
TH1D* h_muqual_accept_lm_ls_is;
TH1D* h_mueta_accept_lm_ls_is;
TH1D* h_caletm2ir_accept_lm_ls_is;
TH1D* h_triggers_lm_ls_is;
TH1D* h_ptasym_lm_ls_is;
TH1D* h_dphii_lm_ls_is;
TH1D* h_deta_lm_ls_is; 
TH1D* h_thrust_lm_ls_is;
TH1D* h_empz_lm_ls_is;
TH1D* h_thrust_mu_ptrel_lm_ls_is;
TH1D* h_dimuphi_lm_ls_is;
TH1D* h_dimueta_lm_ls_is;
TH1D* h_cal_et_lm_ls_is;
TH1D* h_dimulog10q2si_lm_ls_is;
TH1D* h_etex2ir_lm_ls_is;
TH1D* h_dimuxsecpt_lm_ls_is;
TH1D* h_dimuxseceta_lm_ls_is;
TH1D* h_dimuxsecfinders_lm_ls_is;
TH1D* h_dimuxsecdr_lm_ls_is;
TH1D* h_dimuxsecdphi_lm_ls_is;
TH1D* h_dimuxsecptb_lm_ls_is;
TH1D* h_dimuxsecptb_sameb_lm_ls_is;
TH1D* h_dimuxsecptb_diffb_lm_ls_is;
TH1D* h_dimuxsecptb_samecone_lm_ls_is;
TH1D* h_dimuxsecptb_asym_lm_ls_is;
TH1D* h_cal_et_m_et2ir_lm_ls_is;
TH1D* h_cal_et_m_cal_et_10_lm_ls_is;
TH1D* h_PtRel_accept_lm_ls_is;
TH1D* h_muissqsum_accept_lm_ls_is;
TH1D* h_mcdimumass1bin_any_lm_ls_is;
TH1D* h_mcdimumass1bin_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPt_any_lm_ls_is;
TH1D* h_mcdimuxsecPt_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecEta_any_lm_ls_is;
TH1D* h_mcdimuxsecEta_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecFinders_any_lm_ls_is;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecDR_any_lm_ls_is;
TH1D* h_mcdimuxsecDR_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecDphi_any_lm_ls_is;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_any_lm_ls_is;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_sameb_any_lm_ls_is;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_diffb_any_lm_ls_is;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_samecone_any_lm_ls_is;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_asym_any_lm_ls_is;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_lm_ls_is;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_lm_ls_is;

TH1D* h_DR_accept_hm_us_is;
TH2F* h_DR_mmu_accept_hm_us_is;
TH2F* h_ptmus_hm_us_is;
TH2F* h_dphi_hm_us_is;
TH1D* h_ptmu_hm_us_is;
TH1D* h_dimuptmu_hm_us_is;
TH1D* h_mmu_accept_hm_us_is;
TH1D* h_muqual_accept_hm_us_is;
TH1D* h_mueta_accept_hm_us_is;
TH1D* h_caletm2ir_accept_hm_us_is;
TH1D* h_triggers_hm_us_is;
TH1D* h_ptasym_hm_us_is;
TH1D* h_dphii_hm_us_is;
TH1D* h_deta_hm_us_is; 
TH1D* h_thrust_hm_us_is;
TH1D* h_empz_hm_us_is;
TH1D* h_thrust_mu_ptrel_hm_us_is;
TH1D* h_dimuphi_hm_us_is;
TH1D* h_dimueta_hm_us_is;
TH1D* h_cal_et_hm_us_is;
TH1D* h_dimulog10q2si_hm_us_is;
TH1D* h_etex2ir_hm_us_is;
TH1D* h_dimuxsecpt_hm_us_is;
TH1D* h_dimuxseceta_hm_us_is;
TH1D* h_dimuxsecfinders_hm_us_is;
TH1D* h_dimuxsecdr_hm_us_is;
TH1D* h_dimuxsecdphi_hm_us_is;
TH1D* h_dimuxsecptb_hm_us_is;
TH1D* h_dimuxsecptb_sameb_hm_us_is;
TH1D* h_dimuxsecptb_diffb_hm_us_is;
TH1D* h_dimuxsecptb_samecone_hm_us_is;
TH1D* h_dimuxsecptb_asym_hm_us_is;
TH1D* h_cal_et_m_et2ir_hm_us_is;
TH1D* h_cal_et_m_cal_et_10_hm_us_is;
TH1D* h_PtRel_accept_hm_us_is;
TH1D* h_muissqsum_accept_hm_us_is;
TH1D* h_mcdimumass1bin_any_hm_us_is;
TH1D* h_mcdimumass1bin_true_hfl_mu_hm_us_is;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPt_any_hm_us_is;
TH1D* h_mcdimuxsecPt_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecEta_any_hm_us_is;
TH1D* h_mcdimuxsecEta_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecFinders_any_hm_us_is;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecDR_any_hm_us_is;
TH1D* h_mcdimuxsecDR_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecDphi_any_hm_us_is;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_any_hm_us_is;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_sameb_any_hm_us_is;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_diffb_any_hm_us_is;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_samecone_any_hm_us_is;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_asym_any_hm_us_is;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_hm_us_is;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_hm_us_is;

TH1D* h_DR_accept_hm_ls_is;
TH2F* h_DR_mmu_accept_hm_ls_is;
TH2F* h_ptmus_hm_ls_is;
TH2F* h_dphi_hm_ls_is;
TH1D* h_ptmu_hm_ls_is;
TH1D* h_dimuptmu_hm_ls_is;
TH1D* h_mmu_accept_hm_ls_is;
TH1D* h_muqual_accept_hm_ls_is;
TH1D* h_mueta_accept_hm_ls_is;
TH1D* h_caletm2ir_accept_hm_ls_is;
TH1D* h_triggers_hm_ls_is;
TH1D* h_ptasym_hm_ls_is;
TH1D* h_dphii_hm_ls_is;
TH1D* h_deta_hm_ls_is; 
TH1D* h_thrust_hm_ls_is;
TH1D* h_empz_hm_ls_is;
TH1D* h_thrust_mu_ptrel_hm_ls_is;
TH1D* h_dimuphi_hm_ls_is;
TH1D* h_dimueta_hm_ls_is;
TH1D* h_cal_et_hm_ls_is;
TH1D* h_dimulog10q2si_hm_ls_is;
TH1D* h_etex2ir_hm_ls_is;
TH1D* h_dimuxsecpt_hm_ls_is;
TH1D* h_dimuxseceta_hm_ls_is;
TH1D* h_dimuxsecfinders_hm_ls_is;
TH1D* h_dimuxsecdr_hm_ls_is;
TH1D* h_dimuxsecdphi_hm_ls_is;
TH1D* h_dimuxsecptb_hm_ls_is;
TH1D* h_dimuxsecptb_sameb_hm_ls_is;
TH1D* h_dimuxsecptb_diffb_hm_ls_is;
TH1D* h_dimuxsecptb_samecone_hm_ls_is;
TH1D* h_dimuxsecptb_asym_hm_ls_is;
TH1D* h_cal_et_m_et2ir_hm_ls_is;
TH1D* h_cal_et_m_cal_et_10_hm_ls_is;
TH1D* h_PtRel_accept_hm_ls_is;
TH1D* h_muissqsum_accept_hm_ls_is;
TH1D* h_mcdimumass1bin_any_hm_ls_is;
TH1D* h_mcdimumass1bin_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPt_any_hm_ls_is;
TH1D* h_mcdimuxsecPt_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecEta_any_hm_ls_is;
TH1D* h_mcdimuxsecEta_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecFinders_any_hm_ls_is;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecDR_any_hm_ls_is;
TH1D* h_mcdimuxsecDR_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecDphi_any_hm_ls_is;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_any_hm_ls_is;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_sameb_any_hm_ls_is;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_diffb_any_hm_ls_is;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_samecone_any_hm_ls_is;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_asym_any_hm_ls_is;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_hm_ls_is;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_hm_ls_is;

TH1D* h_DR_accept_lm_us_nis;
TH2F* h_DR_mmu_accept_lm_us_nis;
TH2F* h_ptmus_lm_us_nis;
TH2F* h_dphi_lm_us_nis;
TH1D* h_ptmu_lm_us_nis;
TH1D* h_dimuptmu_lm_us_nis;
TH1D* h_mmu_accept_lm_us_nis;
TH1D* h_muqual_accept_lm_us_nis;
TH1D* h_mueta_accept_lm_us_nis;
TH1D* h_caletm2ir_accept_lm_us_nis;
TH1D* h_triggers_lm_us_nis;
TH1D* h_ptasym_lm_us_nis;
TH1D* h_dphii_lm_us_nis;
TH1D* h_deta_lm_us_nis; 
TH1D* h_thrust_lm_us_nis;
TH1D* h_empz_lm_us_nis;
TH1D* h_thrust_mu_ptrel_lm_us_nis;
TH1D* h_dimuphi_lm_us_nis;
TH1D* h_dimueta_lm_us_nis;
TH1D* h_cal_et_lm_us_nis;
TH1D* h_dimulog10q2si_lm_us_nis;
TH1D* h_etex2ir_lm_us_nis;
TH1D* h_dimuxsecpt_lm_us_nis;
TH1D* h_dimuxseceta_lm_us_nis;
TH1D* h_dimuxsecfinders_lm_us_nis;
TH1D* h_dimuxsecdr_lm_us_nis;
TH1D* h_dimuxsecdphi_lm_us_nis;
TH1D* h_dimuxsecptb_lm_us_nis;
TH1D* h_dimuxsecptb_sameb_lm_us_nis;
TH1D* h_dimuxsecptb_diffb_lm_us_nis;
TH1D* h_dimuxsecptb_samecone_lm_us_nis;
TH1D* h_dimuxsecptb_asym_lm_us_nis;
TH1D* h_cal_et_m_et2ir_lm_us_nis;
TH1D* h_cal_et_m_cal_et_10_lm_us_nis;
TH1D* h_PtRel_accept_lm_us_nis;
TH1D* h_muissqsum_accept_lm_us_nis;
TH1D* h_mcdimumass1bin_any_lm_us_nis;
TH1D* h_mcdimumass1bin_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPt_any_lm_us_nis;
TH1D* h_mcdimuxsecPt_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecEta_any_lm_us_nis;
TH1D* h_mcdimuxsecEta_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecFinders_any_lm_us_nis;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecDR_any_lm_us_nis;
TH1D* h_mcdimuxsecDR_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecDphi_any_lm_us_nis;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_any_lm_us_nis;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_sameb_any_lm_us_nis;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_diffb_any_lm_us_nis;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_samecone_any_lm_us_nis;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_asym_any_lm_us_nis;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_lm_us_nis;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_lm_us_nis;

TH1D* h_DR_accept_lm_ls_nis;
TH2F* h_DR_mmu_accept_lm_ls_nis;
TH2F* h_ptmus_lm_ls_nis;
TH2F* h_dphi_lm_ls_nis;
TH1D* h_ptmu_lm_ls_nis;
TH1D* h_dimuptmu_lm_ls_nis;
TH1D* h_mmu_accept_lm_ls_nis;
TH1D* h_muqual_accept_lm_ls_nis;
TH1D* h_mueta_accept_lm_ls_nis;
TH1D* h_caletm2ir_accept_lm_ls_nis;
TH1D* h_triggers_lm_ls_nis;
TH1D* h_ptasym_lm_ls_nis;
TH1D* h_dphii_lm_ls_nis;
TH1D* h_deta_lm_ls_nis; 
TH1D* h_thrust_lm_ls_nis;
TH1D* h_empz_lm_ls_nis;
TH1D* h_thrust_mu_ptrel_lm_ls_nis;
TH1D* h_dimuphi_lm_ls_nis;
TH1D* h_dimueta_lm_ls_nis;
TH1D* h_cal_et_lm_ls_nis;
TH1D* h_dimulog10q2si_lm_ls_nis;
TH1D* h_etex2ir_lm_ls_nis;
TH1D* h_dimuxsecpt_lm_ls_nis;
TH1D* h_dimuxseceta_lm_ls_nis;
TH1D* h_dimuxsecfinders_lm_ls_nis;
TH1D* h_dimuxsecdr_lm_ls_nis;
TH1D* h_dimuxsecdphi_lm_ls_nis;
TH1D* h_dimuxsecptb_lm_ls_nis;
TH1D* h_dimuxsecptb_sameb_lm_ls_nis;
TH1D* h_dimuxsecptb_diffb_lm_ls_nis;
TH1D* h_dimuxsecptb_samecone_lm_ls_nis;
TH1D* h_dimuxsecptb_asym_lm_ls_nis;
TH1D* h_cal_et_m_et2ir_lm_ls_nis;
TH1D* h_cal_et_m_cal_et_10_lm_ls_nis;
TH1D* h_PtRel_accept_lm_ls_nis;
TH1D* h_muissqsum_accept_lm_ls_nis;
TH1D* h_mcdimumass1bin_any_lm_ls_nis;
TH1D* h_mcdimumass1bin_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPt_any_lm_ls_nis;
TH1D* h_mcdimuxsecPt_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecEta_any_lm_ls_nis;
TH1D* h_mcdimuxsecEta_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecFinders_any_lm_ls_nis;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecDR_any_lm_ls_nis;
TH1D* h_mcdimuxsecDR_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecDphi_any_lm_ls_nis;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_any_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_sameb_any_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_diffb_any_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_samecone_any_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_asym_any_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_lm_ls_nis;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_lm_ls_nis;

TH1D* h_DR_accept_hm_us_nis;
TH2F* h_DR_mmu_accept_hm_us_nis;
TH2F* h_ptmus_hm_us_nis;
TH2F* h_dphi_hm_us_nis;
TH1D* h_ptmu_hm_us_nis;
TH1D* h_dimuptmu_hm_us_nis;
TH1D* h_mmu_accept_hm_us_nis;
TH1D* h_muqual_accept_hm_us_nis;
TH1D* h_mueta_accept_hm_us_nis;
TH1D* h_caletm2ir_accept_hm_us_nis;
TH1D* h_triggers_hm_us_nis;
TH1D* h_ptasym_hm_us_nis;
TH1D* h_dphii_hm_us_nis;
TH1D* h_deta_hm_us_nis; 
TH1D* h_thrust_hm_us_nis;
TH1D* h_empz_hm_us_nis;
TH1D* h_thrust_mu_ptrel_hm_us_nis;
TH1D* h_dimuphi_hm_us_nis;
TH1D* h_dimueta_hm_us_nis;
TH1D* h_cal_et_hm_us_nis;
TH1D* h_dimulog10q2si_hm_us_nis;
TH1D* h_etex2ir_hm_us_nis;
TH1D* h_dimuxsecpt_hm_us_nis;
TH1D* h_dimuxseceta_hm_us_nis;
TH1D* h_dimuxsecfinders_hm_us_nis;
TH1D* h_dimuxsecdr_hm_us_nis;
TH1D* h_dimuxsecdphi_hm_us_nis;
TH1D* h_dimuxsecptb_hm_us_nis;
TH1D* h_dimuxsecptb_sameb_hm_us_nis;
TH1D* h_dimuxsecptb_diffb_hm_us_nis;
TH1D* h_dimuxsecptb_samecone_hm_us_nis;
TH1D* h_dimuxsecptb_asym_hm_us_nis;
TH1D* h_cal_et_m_et2ir_hm_us_nis;
TH1D* h_cal_et_m_cal_et_10_hm_us_nis;
TH1D* h_PtRel_accept_hm_us_nis;
TH1D* h_muissqsum_accept_hm_us_nis;
TH1D* h_mcdimumass1bin_any_hm_us_nis;
TH1D* h_mcdimumass1bin_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPt_any_hm_us_nis;
TH1D* h_mcdimuxsecPt_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecEta_any_hm_us_nis;
TH1D* h_mcdimuxsecEta_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecFinders_any_hm_us_nis;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecDR_any_hm_us_nis;
TH1D* h_mcdimuxsecDR_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecDphi_any_hm_us_nis;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_any_hm_us_nis;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_sameb_any_hm_us_nis;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_diffb_any_hm_us_nis;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_samecone_any_hm_us_nis;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_asym_any_hm_us_nis;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_hm_us_nis;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_hm_us_nis;

TH1D* h_DR_accept_hm_ls_nis;
TH2F* h_DR_mmu_accept_hm_ls_nis;
TH2F* h_ptmus_hm_ls_nis;
TH2F* h_dphi_hm_ls_nis;
TH1D* h_ptmu_hm_ls_nis;
TH1D* h_dimuptmu_hm_ls_nis;
TH1D* h_mmu_accept_hm_ls_nis;
TH1D* h_muqual_accept_hm_ls_nis;
TH1D* h_mueta_accept_hm_ls_nis;
TH1D* h_caletm2ir_accept_hm_ls_nis;
TH1D* h_triggers_hm_ls_nis;
TH1D* h_ptasym_hm_ls_nis;
TH1D* h_dphii_hm_ls_nis;
TH1D* h_deta_hm_ls_nis; 
TH1D* h_thrust_hm_ls_nis;
TH1D* h_empz_hm_ls_nis;
TH1D* h_thrust_mu_ptrel_hm_ls_nis;
TH1D* h_dimuphi_hm_ls_nis;
TH1D* h_dimueta_hm_ls_nis;
TH1D* h_cal_et_hm_ls_nis;
TH1D* h_dimulog10q2si_hm_ls_nis;
TH1D* h_etex2ir_hm_ls_nis;
TH1D* h_dimuxsecpt_hm_ls_nis;
TH1D* h_dimuxseceta_hm_ls_nis;
TH1D* h_dimuxsecfinders_hm_ls_nis;
TH1D* h_dimuxsecdr_hm_ls_nis;
TH1D* h_dimuxsecdphi_hm_ls_nis;
TH1D* h_dimuxsecptb_hm_ls_nis;
TH1D* h_dimuxsecptb_sameb_hm_ls_nis;
TH1D* h_dimuxsecptb_diffb_hm_ls_nis;
TH1D* h_dimuxsecptb_samecone_hm_ls_nis;
TH1D* h_dimuxsecptb_asym_hm_ls_nis;
TH1D* h_cal_et_m_et2ir_hm_ls_nis;
TH1D* h_cal_et_m_cal_et_10_hm_ls_nis;
TH1D* h_PtRel_accept_hm_ls_nis;
TH1D* h_muissqsum_accept_hm_ls_nis;
TH1D* h_mcdimumass1bin_any_hm_ls_nis;
TH1D* h_mcdimumass1bin_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPt_any_hm_ls_nis;
TH1D* h_mcdimuxsecPt_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPt_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecEta_any_hm_ls_nis;
TH1D* h_mcdimuxsecEta_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecEta_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecFinders_any_hm_ls_nis;
TH1D* h_mcdimuxsecFinders_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecFinders_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecDR_any_hm_ls_nis;
TH1D* h_mcdimuxsecDR_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecDR_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecDphi_any_hm_ls_nis;
TH1D* h_mcdimuxsecDphi_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecDphi_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_any_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_sameb_any_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_sameb_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_sameb_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_diffb_any_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_diffb_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_diffb_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_samecone_any_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_samecone_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_samecone_truenrec_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_asym_any_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_asym_true_hfl_mu_hm_ls_nis;
TH1D* h_mcdimuxsecPtb_asym_truenrec_hfl_mu_hm_ls_nis;

TH1D* MCDIMuonDRtrue_hu;
TH1D* MCDIMuonDRtrue_hl;
TH1D* mcdimumass_true_hfl_mu;
TH1D* mcdimumass_truenrec_hfl_mu;
TH1D* h_mcdphi_true;
TH1D* h_mcdphi_lu_true;
TH1D* h_mcdphi_ll_true;
TH1D* h_mcdphi_hu_true;
TH1D* h_mcdphi_hl_true;
TH1D* h_mcdphi_truenrec;
TH1D* h_mcdphi_lu_truenrec;
TH1D* h_mcdphi_ll_truenrec;
TH1D* h_mcdphi_hu_truenrec;
TH1D* h_mcdphi_hl_truenrec;
TH1D* h_mcdimumass1bin_any;
TH1D* h_mcdimumass1bin_true_hfl_mu;
TH1D* h_mcdimumass1bin_truenrec_hfl_mu;

TH1D* h_Impact2D_all;
TH1D* h_Impact2D_lm_us;
TH1D* h_Impact2D_lm_ls;
TH1D* h_Impact2D_hm_us;
TH1D* h_Impact2D_hm_ls;
TH1D* h_Impact2D_lm_us_is;
TH1D* h_Impact2D_lm_ls_is;
TH1D* h_Impact2D_hm_us_is;
TH1D* h_Impact2D_hm_ls_is;
TH1D* h_Impact2D_lm_us_nis;
TH1D* h_Impact2D_lm_ls_nis;
TH1D* h_Impact2D_hm_us_nis;
TH1D* h_Impact2D_hm_ls_nis;

TH1D* h_Impact2D_Sign_all;
TH1D* h_Impact2D_Sign_lm_us;
TH1D* h_Impact2D_Sign_lm_ls;
TH1D* h_Impact2D_Sign_hm_us;
TH1D* h_Impact2D_Sign_hm_ls;
TH1D* h_Impact2D_Sign_lm_us_is;
TH1D* h_Impact2D_Sign_lm_ls_is;
TH1D* h_Impact2D_Sign_hm_us_is;
TH1D* h_Impact2D_Sign_hm_ls_is;
TH1D* h_Impact2D_Sign_lm_us_nis;
TH1D* h_Impact2D_Sign_lm_ls_nis;
TH1D* h_Impact2D_Sign_hm_us_nis;
TH1D* h_Impact2D_Sign_hm_ls_nis;

TH1D* h_dimuq2si_all;
TH1D* h_dimuq2si_lm_us;
TH1D* h_dimuq2si_lm_ls;
TH1D* h_dimuq2si_hm_us;
TH1D* h_dimuq2si_hm_ls;
TH1D* h_dimuq2si_lm_us_is;
TH1D* h_dimuq2si_lm_ls_is;
TH1D* h_dimuq2si_hm_us_is;
TH1D* h_dimuq2si_hm_ls_is;
TH1D* h_dimuq2si_lm_us_nis;
TH1D* h_dimuq2si_lm_ls_nis;
TH1D* h_dimuq2si_hm_us_nis;
TH1D* h_dimuq2si_hm_ls_nis;

TH1D* h_dimuq2si_cutjpsi_all;
TH1D* h_dimuq2si_cutjpsi_lm_us;
TH1D* h_dimuq2si_cutjpsi_lm_ls;
TH1D* h_dimuq2si_cutjpsi_hm_us;
TH1D* h_dimuq2si_cutjpsi_hm_ls;
TH1D* h_dimuq2si_cutjpsi_lm_us_is;
TH1D* h_dimuq2si_cutjpsi_lm_ls_is;
TH1D* h_dimuq2si_cutjpsi_hm_us_is;
TH1D* h_dimuq2si_cutjpsi_hm_ls_is;
TH1D* h_dimuq2si_cutjpsi_lm_us_nis;
TH1D* h_dimuq2si_cutjpsi_lm_ls_nis;
TH1D* h_dimuq2si_cutjpsi_hm_us_nis;
TH1D* h_dimuq2si_cutjpsi_hm_ls_nis;

TH1D* h_dimulog10q2si_cutjpsi_all;
TH1D* h_dimulog10q2si_cutjpsi_lm_us;
TH1D* h_dimulog10q2si_cutjpsi_lm_ls;
TH1D* h_dimulog10q2si_cutjpsi_hm_us;
TH1D* h_dimulog10q2si_cutjpsi_hm_ls;
TH1D* h_dimulog10q2si_cutjpsi_lm_us_is;
TH1D* h_dimulog10q2si_cutjpsi_lm_ls_is;
TH1D* h_dimulog10q2si_cutjpsi_hm_us_is;
TH1D* h_dimulog10q2si_cutjpsi_hm_ls_is;
TH1D* h_dimulog10q2si_cutjpsi_lm_us_nis;
TH1D* h_dimulog10q2si_cutjpsi_lm_ls_nis;
TH1D* h_dimulog10q2si_cutjpsi_hm_us_nis;
TH1D* h_dimulog10q2si_cutjpsi_hm_ls_nis;

TH1D* h_sphericity_all;
TH1D* h_sphericity_lm_us;
TH1D* h_sphericity_lm_ls;
TH1D* h_sphericity_hm_us;
TH1D* h_sphericity_hm_ls;
TH1D* h_sphericity_lm_us_is;
TH1D* h_sphericity_lm_ls_is;
TH1D* h_sphericity_hm_us_is;
TH1D* h_sphericity_hm_ls_is;
TH1D* h_sphericity_lm_us_nis;
TH1D* h_sphericity_lm_ls_nis;
TH1D* h_sphericity_hm_us_nis;
TH1D* h_sphericity_hm_ls_nis;

TH1D* h_isotropy_all;
TH1D* h_isotropy_lm_us;
TH1D* h_isotropy_lm_ls;
TH1D* h_isotropy_hm_us;
TH1D* h_isotropy_hm_ls;
TH1D* h_isotropy_lm_us_is;
TH1D* h_isotropy_lm_ls_is;
TH1D* h_isotropy_hm_us_is;
TH1D* h_isotropy_hm_ls_is;
TH1D* h_isotropy_lm_us_nis;
TH1D* h_isotropy_lm_ls_nis;
TH1D* h_isotropy_hm_us_nis;
TH1D* h_isotropy_hm_ls_nis;

TH1D* h_Q2Prime_all;
TH1D* h_Q2Prime_lm_us;
TH1D* h_Q2Prime_lm_ls;
TH1D* h_Q2Prime_hm_us;
TH1D* h_Q2Prime_hm_ls;
TH1D* h_Q2Prime_lm_us_is;
TH1D* h_Q2Prime_lm_ls_is;
TH1D* h_Q2Prime_hm_us_is;
TH1D* h_Q2Prime_hm_ls_is;
TH1D* h_Q2Prime_lm_us_nis;
TH1D* h_Q2Prime_lm_ls_nis;
TH1D* h_Q2Prime_hm_us_nis;
TH1D* h_Q2Prime_hm_ls_nis;

TH1D* h_multiplicity_all;
TH1D* h_multiplicity_lm_us;
TH1D* h_multiplicity_lm_ls;
TH1D* h_multiplicity_hm_us;
TH1D* h_multiplicity_hm_ls;
TH1D* h_multiplicity_lm_us_is;
TH1D* h_multiplicity_lm_ls_is;
TH1D* h_multiplicity_hm_us_is;
TH1D* h_multiplicity_hm_ls_is;
TH1D* h_multiplicity_lm_us_nis;
TH1D* h_multiplicity_lm_ls_nis;
TH1D* h_multiplicity_hm_us_nis;
TH1D* h_multiplicity_hm_ls_nis;

TH1D* h_Neventsubset;
TH1D* h_Neventsubset_all;
TH1D* h_Neventsubset_lm_us;
TH1D* h_Neventsubset_lm_ls;
TH1D* h_Neventsubset_hm_us;
TH1D* h_Neventsubset_hm_ls;
TH1D* h_Neventsubset_lm_us_is;
TH1D* h_Neventsubset_lm_ls_is;
TH1D* h_Neventsubset_hm_us_is;
TH1D* h_Neventsubset_hm_ls_is;
TH1D* h_Neventsubset_lm_us_nis;
TH1D* h_Neventsubset_lm_ls_nis;
TH1D* h_Neventsubset_hm_us_nis;
TH1D* h_Neventsubset_hm_ls_nis;


