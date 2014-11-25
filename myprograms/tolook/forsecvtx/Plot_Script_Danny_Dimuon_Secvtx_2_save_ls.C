{
  TStyle *zeus_style = gInclude->ZEUSSetStyle();

#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Nevents_Histosum/Draw_Errorbar.C"

  gROOT->SetStyle("zeus_pub");

  zeus_pub->SetPadRightMargin(0.048);
  zeus_pub->SetPadLeftMargin(0.196);
  zeus_pub->SetPadTopMargin(0.05);
  zeus_pub->SetPadBottomMargin(0.16);

  Bool_t bigmarker = true;
  Bool_t bg_black  = false;

  TColor * redish    = new TColor(22222, 255./255., 175./255., 155./255.);
  TColor * blueish   = new TColor(  444, 163./255., 167./255., 255./255.);
  TColor * yellowish = new TColor(  555, 255./255., 255./255., 160./255.);
  TColor * greenish  = new TColor(  333, 165./255., 255./255., 150./255.);
  TColor * blackish  = new TColor(  111, 168./255., 168./255., 168./255.);
  TColor * greyish   = new TColor(  666,  98./255.,  89./255., 102./255.);
  TColor * brownish  = new TColor(  777, 128./255.,  51./255.,  43./255.);

  TLegend* leg, leg2;

//**************************************************************************
//**** Histograms for Secondary Vertices
//**************************************************************************

// Decay Length

TH1D* h_dl2_hm_us_data                   = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_us_data");
TH1D* h_dl2_hm_us_allMC_sum              = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_us_allMC_sum");
TH1D* h_dl2_hm_us_allMC_m_charm_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_us_allMC_m_charm_sum");
TH1D* h_dl2_hm_us_MC_c_p_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_hm_us_MC_lflbg_sum           = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_us_MC_lflbg_sum");

TH1D* h_dl2_lm_us_data                   = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_us_data");
TH1D* h_dl2_lm_us_allMC_sum              = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_us_allMC_sum");
TH1D* h_dl2_lm_us_allMC_m_charm_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_us_allMC_m_charm_sum");
TH1D* h_dl2_lm_us_MC_c_p_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_lm_us_MC_lflbg_sum           = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_us_MC_lflbg_sum");

TH1D* h_dl2_hm_ls_data                   = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_ls_data");
TH1D* h_dl2_hm_ls_allMC_sum              = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_ls_allMC_sum");
TH1D* h_dl2_hm_ls_allMC_m_charm_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_ls_allMC_m_charm_sum");
TH1D* h_dl2_hm_ls_MC_c_p_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_hm_ls_MC_lflbg_sum           = (TH1D*) gInclude->ReadinHisto("h_dl2_hm_ls_MC_lflbg_sum");

TH1D* h_dl2_lm_ls_data                   = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_ls_data");
TH1D* h_dl2_lm_ls_allMC_sum              = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_ls_allMC_sum");
TH1D* h_dl2_lm_ls_allMC_m_charm_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_ls_allMC_m_charm_sum");
TH1D* h_dl2_lm_ls_MC_c_p_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_lm_ls_MC_lflbg_sum           = (TH1D*) gInclude->ReadinHisto("h_dl2_lm_ls_MC_lflbg_sum");

// Decay Length Error

TH1D* h_dl2_err_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_us_data");
TH1D* h_dl2_err_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_us_allMC_sum");
TH1D* h_dl2_err_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_us_allMC_m_charm_sum");
TH1D* h_dl2_err_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_err_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_us_MC_lflbg_sum");

TH1D* h_dl2_err_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_us_data");
TH1D* h_dl2_err_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_us_allMC_sum");
TH1D* h_dl2_err_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_us_allMC_m_charm_sum");
TH1D* h_dl2_err_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_err_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_us_MC_lflbg_sum");

TH1D* h_dl2_err_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_ls_data");
TH1D* h_dl2_err_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_ls_allMC_sum");
TH1D* h_dl2_err_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_ls_allMC_m_charm_sum");
TH1D* h_dl2_err_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_err_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_err_hm_ls_MC_lflbg_sum");

TH1D* h_dl2_err_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_ls_data");
TH1D* h_dl2_err_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_ls_allMC_sum");
TH1D* h_dl2_err_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_ls_allMC_m_charm_sum");
TH1D* h_dl2_err_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_err_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_err_lm_ls_MC_lflbg_sum");

// Decay Length Significance

TH1D* h_dl2_sign_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_us_data");
TH1D* h_dl2_sign_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_us_allMC_sum");
TH1D* h_dl2_sign_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_us_allMC_m_charm_sum");
TH1D* h_dl2_sign_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_us_MC_lflbg_sum");

TH1D* h_dl2_sign_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_us_data");
TH1D* h_dl2_sign_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_us_allMC_sum");
TH1D* h_dl2_sign_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_us_allMC_m_charm_sum");
TH1D* h_dl2_sign_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_us_MC_lflbg_sum");

TH1D* h_dl2_sign_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_ls_data");
TH1D* h_dl2_sign_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_ls_allMC_sum");
TH1D* h_dl2_sign_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_ls_allMC_m_charm_sum");
TH1D* h_dl2_sign_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_hm_ls_MC_lflbg_sum");

TH1D* h_dl2_sign_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_ls_data");
TH1D* h_dl2_sign_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_ls_allMC_sum");
TH1D* h_dl2_sign_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_ls_allMC_m_charm_sum");
TH1D* h_dl2_sign_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_lm_ls_MC_lflbg_sum");

// + Mirrored Decay Length Significance

TH1D* h_dl2_sign_mirrp_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_us_data");
TH1D* h_dl2_sign_mirrp_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_us_allMC_sum");
TH1D* h_dl2_sign_mirrp_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_us_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrp_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrp_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_us_MC_lflbg_sum");

TH1D* h_dl2_sign_mirrp_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_us_data");
TH1D* h_dl2_sign_mirrp_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_us_allMC_sum");
TH1D* h_dl2_sign_mirrp_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_us_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrp_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrp_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_us_MC_lflbg_sum");

TH1D* h_dl2_sign_mirrp_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_ls_data");
TH1D* h_dl2_sign_mirrp_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_ls_allMC_sum");
TH1D* h_dl2_sign_mirrp_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_ls_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrp_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrp_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_hm_ls_MC_lflbg_sum");

TH1D* h_dl2_sign_mirrp_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_ls_data");
TH1D* h_dl2_sign_mirrp_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_ls_allMC_sum");
TH1D* h_dl2_sign_mirrp_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_ls_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrp_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrp_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrp_lm_ls_MC_lflbg_sum");

// - Mirrored Decay Length Significance

TH1D* h_dl2_sign_mirrm_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_us_data");
TH1D* h_dl2_sign_mirrm_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_us_allMC_sum");
TH1D* h_dl2_sign_mirrm_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_us_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrm_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrm_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_us_MC_lflbg_sum");

TH1D* h_dl2_sign_mirrm_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_us_data");
TH1D* h_dl2_sign_mirrm_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_us_allMC_sum");
TH1D* h_dl2_sign_mirrm_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_us_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrm_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_us_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrm_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_us_MC_lflbg_sum");

TH1D* h_dl2_sign_mirrm_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_ls_data");
TH1D* h_dl2_sign_mirrm_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_ls_allMC_sum");
TH1D* h_dl2_sign_mirrm_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_ls_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrm_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrm_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_hm_ls_MC_lflbg_sum");

TH1D* h_dl2_sign_mirrm_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_ls_data");
TH1D* h_dl2_sign_mirrm_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_ls_allMC_sum");
TH1D* h_dl2_sign_mirrm_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_ls_allMC_m_charm_sum");
TH1D* h_dl2_sign_mirrm_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_dl2_sign_mirrm_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_dl2_sign_mirrm_lm_ls_MC_lflbg_sum");

// Mirrored Decay Length Significance

TH1D* h_dl2_sign_mirr_hm_us_data                  = (TH1D*) h_dl2_sign_mirrp_hm_us_data->Clone("h_dl2_sign_mirr_hm_us_data");
      h_dl2_sign_mirr_hm_us_data                  -> Add(h_dl2_sign_mirrm_hm_us_data,-1.);

TH1D* h_dl2_sign_mirr_hm_us_allMC_sum             = (TH1D*) h_dl2_sign_mirrp_hm_us_allMC_sum->Clone("h_dl2_sign_mirr_hm_us_allMC_sum");
      h_dl2_sign_mirr_hm_us_allMC_sum             -> Add(h_dl2_sign_mirrm_hm_us_allMC_sum,-1.);

TH1D* h_dl2_sign_mirr_hm_us_allMC_m_charm_sum     = (TH1D*) h_dl2_sign_mirrp_hm_us_allMC_m_charm_sum->Clone("h_dl2_sign_mirr_hm_us_allMC_m_charm_sum");
      h_dl2_sign_mirr_hm_us_allMC_m_charm_sum     -> Add(h_dl2_sign_mirrm_hm_us_allMC_m_charm_sum,-1.);

TH1D* h_dl2_sign_mirr_hm_us_MC_c_p_lflbg_sum      = (TH1D*) h_dl2_sign_mirrp_hm_us_MC_c_p_lflbg_sum->Clone("h_dl2_sign_mirr_hm_us_MC_c_p_lflbg_sum");
      h_dl2_sign_mirr_hm_us_MC_c_p_lflbg_sum      -> Add(h_dl2_sign_mirrm_hm_us_MC_c_p_lflbg_sum,-1.);

TH1D* h_dl2_sign_mirr_hm_us_MC_lflbg_sum   = (TH1D*) h_dl2_sign_mirrp_hm_us_MC_lflbg_sum->Clone("h_dl2_sign_mirr_hm_us_MC_lflbg_sum");
      h_dl2_sign_mirr_hm_us_MC_lflbg_sum   -> Add(h_dl2_sign_mirrm_hm_us_MC_lflbg_sum,-1.);

TH1D* h_dl2_sign_mirr_lm_us_data                  = (TH1D*) h_dl2_sign_mirrp_lm_us_data->Clone("h_dl2_sign_mirr_lm_us_data");
      h_dl2_sign_mirr_lm_us_data                  -> Add(h_dl2_sign_mirrm_lm_us_data,-1.);

TH1D* h_dl2_sign_mirr_lm_us_allMC_sum             = (TH1D*) h_dl2_sign_mirrp_lm_us_allMC_sum->Clone("h_dl2_sign_mirr_lm_us_allMC_sum");
      h_dl2_sign_mirr_lm_us_allMC_sum             -> Add(h_dl2_sign_mirrm_lm_us_allMC_sum,-1.);

TH1D* h_dl2_sign_mirr_lm_us_allMC_m_charm_sum     = (TH1D*) h_dl2_sign_mirrp_lm_us_allMC_m_charm_sum->Clone("h_dl2_sign_mirr_lm_us_allMC_m_charm_sum");
      h_dl2_sign_mirr_lm_us_allMC_m_charm_sum     -> Add(h_dl2_sign_mirrm_lm_us_allMC_m_charm_sum,-1.);

TH1D* h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum      = (TH1D*) h_dl2_sign_mirrp_lm_us_MC_c_p_lflbg_sum->Clone("h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum");
      h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum       -> Add(h_dl2_sign_mirrm_lm_us_MC_c_p_lflbg_sum,-1.);

TH1D* h_dl2_sign_mirr_lm_us_MC_lflbg_sum   = (TH1D*) h_dl2_sign_mirrp_lm_us_MC_lflbg_sum->Clone("h_dl2_sign_mirr_lm_us_MC_lflbg_sum");
      h_dl2_sign_mirr_lm_us_MC_lflbg_sum   -> Add(h_dl2_sign_mirrm_lm_us_MC_lflbg_sum,-1.);

TH1D* h_dl2_sign_mirr_hm_ls_data                  = (TH1D*) h_dl2_sign_mirrp_hm_ls_data->Clone("h_dl2_sign_mirr_hm_ls_data");
      h_dl2_sign_mirr_hm_ls_data                  -> Add(h_dl2_sign_mirrm_hm_ls_data,-1.);

TH1D* h_dl2_sign_mirr_hm_ls_allMC_sum             = (TH1D*) h_dl2_sign_mirrp_hm_ls_allMC_sum->Clone("h_dl2_sign_mirr_hm_ls_allMC_sum");
      h_dl2_sign_mirr_hm_ls_allMC_sum             -> Add(h_dl2_sign_mirrm_hm_ls_allMC_sum,-1.);

TH1D* h_dl2_sign_mirr_hm_ls_MC_lflbg_sum   = (TH1D*) h_dl2_sign_mirrp_hm_ls_MC_lflbg_sum->Clone("h_dl2_sign_mirr_hm_ls_MC_lflbg_sum");
      h_dl2_sign_mirr_hm_ls_MC_lflbg_sum   -> Add(h_dl2_sign_mirrm_hm_ls_MC_lflbg_sum,-1.);

TH1D* h_dl2_sign_mirr_lm_ls_data                  = (TH1D*) h_dl2_sign_mirrp_lm_ls_data->Clone("h_dl2_sign_mirr_lm_ls_data");
      h_dl2_sign_mirr_lm_ls_data                  -> Add(h_dl2_sign_mirrm_lm_ls_data,-1.);

TH1D* h_dl2_sign_mirr_lm_ls_allMC_sum             = (TH1D*) h_dl2_sign_mirrp_lm_ls_allMC_sum->Clone("h_dl2_sign_mirr_lm_ls_allMC_sum");
      h_dl2_sign_mirr_lm_ls_allMC_sum             -> Add(h_dl2_sign_mirrm_lm_ls_allMC_sum,-1.);

TH1D* h_dl2_sign_mirr_lm_ls_MC_lflbg_sum   = (TH1D*) h_dl2_sign_mirrp_lm_ls_MC_lflbg_sum->Clone("h_dl2_sign_mirr_lm_ls_MC_lflbg_sum");
      h_dl2_sign_mirr_lm_ls_MC_lflbg_sum   -> Add(h_dl2_sign_mirrm_lm_ls_MC_lflbg_sum,-1.);
//***********************************************************************
//****  plotting the ZEUS style guys!  **********************************
//***********************************************************************
cout<<" DATA sum: "<<Get_sumof_hist("h_dl2_lm_us_data", h_dl2_lm_us_data, 0)+Get_sumof_hist("h_dl2_lm_ls_data", h_dl2_lm_ls_data, 0)+Get_sumof_hist("h_dl2_hm_us_data", h_dl2_hm_us_data, 0)+Get_sumof_hist("h_dl2_hm_ls_data", h_dl2_hm_ls_data, 0)<<endl;
cout<<"data lm_us: "<<Get_sumof_hist("h_dl2_lm_us_data", h_dl2_lm_us_data, 0)<<endl;
cout<<"data lm_ls: "<<Get_sumof_hist("h_dl2_lm_ls_data", h_dl2_lm_ls_data, 0)<<endl;
cout<<"data hm_us: "<<Get_sumof_hist("h_dl2_hm_us_data", h_dl2_hm_us_data, 0)<<endl;
cout<<"data hm_ls: "<<Get_sumof_hist("h_dl2_hm_ls_data", h_dl2_hm_ls_data, 0)<<endl<<endl;

cout<<" bb sum: "<<Get_sumof_hist("h_dl2_lm_us_allMC_sum", h_dl2_lm_us_allMC_sum, 0)+Get_sumof_hist("h_dl2_lm_ls_allMC_sum", h_dl2_lm_ls_allMC_sum, 0)+Get_sumof_hist("h_dl2_hm_us_allMC_sum", h_dl2_hm_us_allMC_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_allMC_sum", h_dl2_hm_ls_allMC_sum, 0)<<endl;
cout<<"bb lm_us: "<<Get_sumof_hist("h_dl2_lm_us_allMC_sum", h_dl2_lm_us_allMC_sum, 0)<<endl;
cout<<"bb lm_ls: "<<Get_sumof_hist("h_dl2_lm_ls_allMC_sum", h_dl2_lm_ls_allMC_sum, 0)<<endl;
cout<<"bb hm_us: "<<Get_sumof_hist("h_dl2_hm_us_allMC_sum", h_dl2_hm_us_allMC_sum, 0)<<endl;
cout<<"bb hm_ls: "<<Get_sumof_hist("h_dl2_hm_ls_allMC_sum", h_dl2_hm_ls_allMC_sum, 0)<<endl<<endl;

cout<<" cc sum: "<<Get_sumof_hist("h_dl2_lm_us_MC_c_p_lflbg_sum", h_dl2_lm_us_MC_c_p_lflbg_sum, 0)+Get_sumof_hist("h_dl2_lm_ls_MC_c_p_lflbg_sum", h_dl2_lm_ls_MC_c_p_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_us_MC_c_p_lflbg_sum", h_dl2_hm_us_MC_c_p_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_MC_c_p_lflbg_sum", h_dl2_hm_ls_MC_c_p_lflbg_sum, 0)<<endl;
cout<<"cc lm_us: "<<Get_sumof_hist("h_dl2_lm_us_MC_c_p_lflbg_sum", h_dl2_lm_us_MC_c_p_lflbg_sum, 0)<<endl;
cout<<"cc lm_ls: "<<Get_sumof_hist("h_dl2_lm_ls_MC_c_p_lflbg_sum", h_dl2_lm_ls_MC_c_p_lflbg_sum, 0)<<endl;
cout<<"cc hm_us: "<<Get_sumof_hist("h_dl2_hm_us_MC_c_p_lflbg_sum", h_dl2_hm_us_MC_c_p_lflbg_sum, 0)<<endl;
cout<<"cc hm_ls: "<<Get_sumof_hist("h_dl2_hm_ls_MC_c_p_lflbg_sum", h_dl2_hm_ls_MC_c_p_lflbg_sum, 0)<<endl<<endl;

cout<<" jpsi sum: "<<Get_sumof_hist("h_dl2_lm_us_allMC_m_charm_sum", h_dl2_lm_us_allMC_m_charm_sum, 0)+Get_sumof_hist("h_dl2_lm_ls_allMC_m_charm_sum", h_dl2_lm_ls_allMC_m_charm_sum, 0)+Get_sumof_hist("h_dl2_hm_us_allMC_m_charm_sum", h_dl2_hm_us_allMC_m_charm_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_allMC_m_charm_sum", h_dl2_hm_ls_allMC_m_charm_sum, 0)<<endl;
cout<<"jpsi lm_us: "<<Get_sumof_hist("h_dl2_lm_us_allMC_m_charm_sum", h_dl2_lm_us_allMC_m_charm_sum, 0)<<endl;
cout<<"jpsi lm_ls: "<<Get_sumof_hist("h_dl2_lm_ls_allMC_m_charm_sum", h_dl2_lm_ls_allMC_m_charm_sum, 0)<<endl;
cout<<"jpsi hm_us: "<<Get_sumof_hist("h_dl2_hm_us_allMC_m_charm_sum", h_dl2_hm_us_allMC_m_charm_sum, 0)<<endl;
cout<<"jpsi hm_ls: "<<Get_sumof_hist("h_dl2_hm_ls_allMC_m_charm_sum", h_dl2_hm_ls_allMC_m_charm_sum, 0)<<endl<<endl;

cout<<" lfl sum: "<<Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)+Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl lm_us: "<<Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl lm_ls: "<<Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl hm_us: "<<Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl hm_ls: "<<Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)<<endl<<endl;


cout<<endl<<" Modified:  (us -ls) " <<endl;
cout<<" bb sum: "<<Get_sumof_hist("h_dl2_lm_us_allMC_sum", h_dl2_lm_us_allMC_sum, 0)+Get_sumof_hist("h_dl2_lm_ls_allMC_sum", h_dl2_lm_ls_allMC_sum, 0)+Get_sumof_hist("h_dl2_hm_us_allMC_sum", h_dl2_hm_us_allMC_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_allMC_sum", h_dl2_hm_ls_allMC_sum, 0)<<endl;


Double_t cc_us = Get_sumof_hist("h_dl2_lm_us_MC_c_p_lflbg_sum", h_dl2_lm_us_MC_c_p_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_us_MC_c_p_lflbg_sum", h_dl2_hm_us_MC_c_p_lflbg_sum, 0);
Double_t cc_ls = Get_sumof_hist("h_dl2_lm_ls_MC_c_p_lflbg_sum", h_dl2_lm_ls_MC_c_p_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_MC_c_p_lflbg_sum", h_dl2_hm_ls_MC_c_p_lflbg_sum, 0);
cout<<" cc sum (us-ls) "<<(cc_us - cc_ls)<<endl;
cout<<"cc lm_us-ls: "<<Get_sumof_hist("h_dl2_lm_us_MC_c_p_lflbg_sum", h_dl2_lm_us_MC_c_p_lflbg_sum, 0)-Get_sumof_hist("h_dl2_lm_ls_MC_c_p_lflbg_sum", h_dl2_lm_ls_MC_c_p_lflbg_sum, 0)<<endl;
cout<<"cc hm_us-ls: "<<Get_sumof_hist("h_dl2_hm_us_MC_c_p_lflbg_sum", h_dl2_hm_us_MC_c_p_lflbg_sum, 0)-Get_sumof_hist("h_dl2_hm_ls_MC_c_p_lflbg_sum", h_dl2_hm_ls_MC_c_p_lflbg_sum, 0)<<endl;
cout<<endl;

Double_t jpsi_us = Get_sumof_hist("h_dl2_lm_us_allMC_m_charm_sum", h_dl2_lm_us_allMC_m_charm_sum, 0)+Get_sumof_hist("h_dl2_hm_us_allMC_m_charm_sum", h_dl2_hm_us_allMC_m_charm_sum, 0);
Double_t jpsi_ls = Get_sumof_hist("h_dl2_lm_ls_allMC_m_charm_sum", h_dl2_lm_ls_allMC_m_charm_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_allMC_m_charm_sum", h_dl2_hm_ls_allMC_m_charm_sum, 0);
cout<<" jpsi sum (us -ls) "<<(jpsi_us - jpsi_ls)<<endl;
cout<<"jpsi lm_us-ls: "<<Get_sumof_hist("h_dl2_lm_us_allMC_m_charm_sum", h_dl2_lm_us_allMC_m_charm_sum, 0)-Get_sumof_hist("h_dl2_lm_ls_allMC_m_charm_sum", h_dl2_lm_ls_allMC_m_charm_sum, 0)<<endl;
cout<<"jpsi hm_us-ls: "<<Get_sumof_hist("h_dl2_hm_us_allMC_m_charm_sum", h_dl2_hm_us_allMC_m_charm_sum, 0)-Get_sumof_hist("h_dl2_hm_ls_allMC_m_charm_sum", h_dl2_hm_ls_allMC_m_charm_sum, 0)<<endl;
cout<<endl;

cout<<" lfl sum "<<Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)+Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)+Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl lm_us: "<<Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl lm_ls: "<<Get_sumof_hist("h_dl2_lm_ls_MC_lflbg_sum", h_dl2_lm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl hm_us: "<<Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)<<endl;
cout<<"lfl hm_ls: "<<Get_sumof_hist("h_dl2_hm_ls_MC_lflbg_sum", h_dl2_hm_ls_MC_lflbg_sum, 0)<<endl<<endl;

//  Decay Length stuff

  TCanvas * canv = new TCanvas("canv","canv",1005,955);
  canv->cd();

// DL
  canv_1 = new TPad("canv_1", "canv_1", 0.0, 0.50, 0.50, 0.99);
  canv_1->Draw();
  canv_1->SetLogy();
  canv_1->cd();
  canv_1->Range(-3.86269,-150.588,3.62985,830.588);

//   h_dl2_lm_us_data->Add(h_dl2_hm_us_data,1.);
//   h_dl2_lm_us_data->Add(h_dl2_lm_ls_data,1.);
  h_dl2_lm_ls_data->Add(h_dl2_hm_ls_data,1.);
  h_dl2_lm_ls_data->SetMarkerStyle(8);

// format X axis

  h_dl2_lm_ls_data->GetXaxis()->SetRangeUser(-100.,100.);
  h_dl2_lm_ls_data->GetXaxis()->SetTitle("L_{XY} [cm]");
  h_dl2_lm_ls_data->GetXaxis()->SetTitleSize(0.06);
  h_dl2_lm_ls_data->GetXaxis()->SetTitleOffset(1.0);
  h_dl2_lm_ls_data->GetXaxis()->SetLabelSize(0.04);
  h_dl2_lm_ls_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_dl2_lm_us_data->GetYaxis()->SetRangeUser(0.0,1500.);
  h_dl2_lm_ls_data->GetYaxis()->SetTitle("Events");
  h_dl2_lm_ls_data->GetYaxis()->SetTitleSize(0.07);
  h_dl2_lm_ls_data->GetYaxis()->SetTitleOffset(1.4);
  h_dl2_lm_ls_data->GetYaxis()->SetLabelSize(0.06);
  h_dl2_lm_ls_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_dl2_lm_ls_data->SetMarkerSize(0.8);
  else            h_dl2_lm_ls_data->SetMarkerSize(.6);
  h_dl2_lm_ls_data->Draw("P");


/// lfl 
//   h_dl2_hm_ls_MC_lflbg_sum->Add(h_dl2_hm_ls_MC_lflbg_sum,1.);
  h_dl2_hm_ls_MC_lflbg_sum->Add(h_dl2_lm_ls_MC_lflbg_sum,1.);
//   h_dl2_hm_ls_MC_lflbg_sum->Add(h_dl2_lm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_dl2_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_dl2_hm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c cbar
  h_dl2_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_hm_us_MC_c_p_lflbg_sum,1.);
  h_dl2_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_hm_ls_MC_c_p_lflbg_sum,-1.);
  h_dl2_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_lm_ls_MC_c_p_lflbg_sum,-1.);

  h_dl2_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_hm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_dl2_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_dl2_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_dl2_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_dl2_lm_us_allMC_m_charm_sum->Add(h_dl2_hm_us_allMC_m_charm_sum,1.);
  h_dl2_lm_us_allMC_m_charm_sum->Add(h_dl2_hm_ls_allMC_m_charm_sum,-1.);
  h_dl2_lm_us_allMC_m_charm_sum->Add(h_dl2_lm_ls_allMC_m_charm_sum,-1.);

  h_dl2_lm_us_allMC_m_charm_sum->Add(h_dl2_hm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_dl2_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_dl2_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_dl2_lm_us_allMC_m_charm_sum->SetFillStyle(1001);


/// b bbar
//   h_dl2_lm_us_allMC_sum->Add(h_dl2_hm_us_allMC_sum,1.);
//   h_dl2_lm_us_allMC_sum->Add(h_dl2_lm_ls_allMC_sum,1.);
  h_dl2_lm_ls_allMC_sum->Add(h_dl2_hm_ls_allMC_sum,1.);

  h_dl2_lm_ls_allMC_sum->Add(h_dl2_hm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_dl2_lm_ls_allMC_sum->SetFillColor(111); 
  else            h_dl2_lm_ls_allMC_sum->SetFillColor(22222); 
  h_dl2_lm_ls_allMC_sum->SetFillStyle(1001);


  h_dl2_lm_ls_allMC_sum->Draw("hist same");
//   h_dl2_lm_us_allMC_m_charm_sum->Draw("hist same");
//   h_dl2_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_dl2_hm_ls_MC_lflbg_sum->Draw("hist same");

//Draw data again as top layer

  h_dl2_lm_ls_data->Draw("P same");
  
  canv_1->RedrawAxis();

  canv->cd();

  canv_2 = new TPad("canv_2", "canv_2", 0.50, 0.50, 1.0, 0.99);
  canv_2->Draw();
  canv_2->SetLogy();
  canv_2->cd();
  canv_2->Range(-3.86269,-150.588,3.62985,830.588);

//   h_dl2_sign_lm_us_data->Add(h_dl2_sign_hm_us_data,1.);
//   h_dl2_sign_lm_us_data->Add(h_dl2_sign_lm_ls_data,1.);
  h_dl2_sign_lm_ls_data->Add(h_dl2_sign_hm_ls_data,1.);
  h_dl2_sign_lm_ls_data->SetMarkerStyle(8);

// format X axis

  h_dl2_sign_lm_ls_data->GetXaxis()->SetRangeUser(-15.,15.);
  h_dl2_sign_lm_ls_data->GetXaxis()->SetTitle("S = L_{XY}/#sigma_{L_{XY}}");
  h_dl2_sign_lm_ls_data->GetXaxis()->SetTitleSize(0.06);
  h_dl2_sign_lm_ls_data->GetXaxis()->SetTitleOffset(0.9);
  h_dl2_sign_lm_ls_data->GetXaxis()->SetLabelSize(0.04);
  h_dl2_sign_lm_ls_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_dl2_sign_lm_us_data->GetYaxis()->SetRangeUser(0.0,1200.);
  h_dl2_sign_lm_ls_data->GetYaxis()->SetTitle("Events");
  h_dl2_sign_lm_ls_data->GetYaxis()->SetTitleSize(0.07);
  h_dl2_sign_lm_ls_data->GetYaxis()->SetTitleOffset(1.4);
  h_dl2_sign_lm_ls_data->GetYaxis()->SetLabelSize(0.06);
  h_dl2_sign_lm_ls_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_dl2_sign_lm_ls_data->SetMarkerSize(0.8);
  else            h_dl2_sign_lm_ls_data->SetMarkerSize(.6);
  h_dl2_sign_lm_ls_data->Draw("P");

/// lfl 
//   h_dl2_sign_hm_ls_MC_lflbg_sum->Add(h_dl2_sign_hm_ls_MC_lflbg_sum,1.);
  h_dl2_sign_hm_ls_MC_lflbg_sum->Add(h_dl2_sign_lm_ls_MC_lflbg_sum,1.);
//   h_dl2_sign_hm_ls_MC_lflbg_sum->Add(h_dl2_sign_lm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_sign_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_dl2_sign_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_dl2_sign_hm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c cbar
  h_dl2_sign_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_sign_hm_us_MC_c_p_lflbg_sum,1.);
  h_dl2_sign_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_sign_hm_ls_MC_c_p_lflbg_sum,-1.);
  h_dl2_sign_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_sign_lm_ls_MC_c_p_lflbg_sum,-1.);

  h_dl2_sign_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_sign_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_sign_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_dl2_sign_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_dl2_sign_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// J/Psi ...
  h_dl2_sign_lm_us_allMC_m_charm_sum->Add(h_dl2_sign_hm_us_allMC_m_charm_sum,1.);
  h_dl2_sign_lm_us_allMC_m_charm_sum->Add(h_dl2_sign_hm_ls_allMC_m_charm_sum,-1.);
  h_dl2_sign_lm_us_allMC_m_charm_sum->Add(h_dl2_sign_lm_ls_allMC_m_charm_sum,-1.);

  h_dl2_sign_lm_us_allMC_m_charm_sum->Add(h_dl2_sign_lm_us_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_dl2_sign_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_dl2_sign_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_dl2_sign_lm_us_allMC_m_charm_sum->SetFillStyle(1001);


/// b bbar
//   h_dl2_sign_lm_us_allMC_sum->Add(h_dl2_sign_hm_us_allMC_sum,1.);
//   h_dl2_sign_lm_us_allMC_sum->Add(h_dl2_sign_lm_ls_allMC_sum,1.);
  h_dl2_sign_lm_ls_allMC_sum->Add(h_dl2_sign_hm_ls_allMC_sum,1.);

  h_dl2_sign_lm_ls_allMC_sum->Add(h_dl2_sign_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_sign_lm_ls_allMC_sum->SetFillColor(111); 
  else            h_dl2_sign_lm_ls_allMC_sum->SetFillColor(22222); 
  h_dl2_sign_lm_ls_allMC_sum->SetFillStyle(1001);

//   h_dl2_sign_lm_us_allMC_sum->Scale(0.5);
//   h_dl2_sign_lm_us_allMC_m_charm_sum->Scale(0.5);
//   h_dl2_sign_lm_us_MC_c_p_lflbg_sum->Scale(0.5);
//   h_dl2_sign_hm_ls_MC_lflbg_sum->Scale(0.5);

  h_dl2_sign_lm_ls_allMC_sum->Draw("hist same");
//   h_dl2_sign_lm_us_allMC_m_charm_sum->Draw("hist same");
//   h_dl2_sign_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_dl2_sign_hm_ls_MC_lflbg_sum->Draw("hist same");

//Draw data again as top layer

  h_dl2_sign_lm_ls_data->Draw("P same");
  
  canv_2->RedrawAxis();

  canv->cd();

  TPad *canv_3 = new TPad("canv_3", "canv_3",0.0,0.0,0.50,0.49);
  canv_3->Draw();
  canv_3->cd();
  canv_3->Range(-3.09474,-280.175,10.5829,1586.15);

  h_dl2_lm_ls_allMC_sum->Sumw2();
  h_dl2_lm_ls_data->Sumw2();
  TH1D* h_dl2_data_copy = (TH1D*) h_dl2_lm_ls_data->Clone("h_dl2_data_copy");
  h_dl2_data_copy->Sumw2();

  h_dl2_data_copy->Divide(h_dl2_lm_ls_allMC_sum);
  h_dl2_data_copy->Draw("E1");
  canv_3->RedrawAxis();

  canv->cd();

  TPad *canv_4 = new TPad("canv_4", "canv_4",0.50,0.0,1.0,0.49);
  canv_4->Draw();
  canv_4->cd();

  h_dl2_sign_lm_ls_data->Sumw2();
  h_dl2_sign_lm_ls_allMC_sum->Sumw2();
  TH1D* h_dl2_sign_data_copy = (TH1D*) h_dl2_sign_lm_ls_data->Clone("h_dl2_sign_data_copy");
  h_dl2_sign_data_copy->Sumw2();

  h_dl2_sign_data_copy->Divide(h_dl2_sign_lm_ls_allMC_sum);
  h_dl2_sign_data_copy->Draw("E1");
  canv_4->RedrawAxis();


// Decay Length error

  TCanvas * canv2 = new TCanvas("canv2","canv2",1005,500);

  canv2_1 = new TPad("canv2_1", "canv2_1", 0.0, 0.0, 1.00, 0.99);
  canv2_1->Draw();
  canv2_1->SetLogy();
  canv2_1->cd();
  canv2_1->Range(-3.86269,-150.588,3.62985,830.588);

  h_dl2_err_lm_us_data->Add(h_dl2_err_hm_us_data,1.);
  h_dl2_err_lm_us_data->Add(h_dl2_err_lm_ls_data,1.);
  h_dl2_err_lm_us_data->Add(h_dl2_err_hm_ls_data,1.);
  h_dl2_err_lm_us_data->SetMarkerStyle(8);

// format X axis

  h_dl2_err_lm_us_data->GetXaxis()->SetRangeUser(-100.,100.);
  h_dl2_err_lm_us_data->GetXaxis()->SetTitle("#sigma_{L_{XY}} [cm]");
  h_dl2_err_lm_us_data->GetXaxis()->SetTitleSize(0.06);
  h_dl2_err_lm_us_data->GetXaxis()->SetTitleOffset(0.9);
  h_dl2_err_lm_us_data->GetXaxis()->SetLabelSize(0.04);
  h_dl2_err_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_dl2_err_lm_us_data->GetYaxis()->SetRangeUser(0.0,1500.);
  h_dl2_err_lm_us_data->GetYaxis()->SetTitle("Events");
  h_dl2_err_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_dl2_err_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_dl2_err_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_dl2_err_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_dl2_err_lm_us_data->SetMarkerSize(1.);
  else            h_dl2_err_lm_us_data->SetMarkerSize(.6);
  h_dl2_err_lm_us_data->Draw("P");

/// lfl 
  h_dl2_err_hm_ls_MC_lflbg_sum->Add(h_dl2_err_hm_ls_MC_lflbg_sum,1.);
  h_dl2_err_hm_ls_MC_lflbg_sum->Add(h_dl2_err_lm_ls_MC_lflbg_sum,1.);
  h_dl2_err_hm_ls_MC_lflbg_sum->Add(h_dl2_err_lm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_err_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_dl2_err_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_dl2_err_hm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c cbar
  h_dl2_err_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_err_hm_us_MC_c_p_lflbg_sum,1.);
  h_dl2_err_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_err_hm_ls_MC_c_p_lflbg_sum,-1.);
  h_dl2_err_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_err_lm_ls_MC_c_p_lflbg_sum,-1.);

  h_dl2_err_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_err_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_err_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_dl2_err_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_dl2_err_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// J/Psi ...
  h_dl2_err_lm_us_allMC_m_charm_sum->Add(h_dl2_err_hm_us_allMC_m_charm_sum,1.);
  h_dl2_err_lm_us_allMC_m_charm_sum->Add(h_dl2_err_hm_ls_allMC_m_charm_sum,-1.);
  h_dl2_err_lm_us_allMC_m_charm_sum->Add(h_dl2_err_lm_ls_allMC_m_charm_sum,-1.);

  h_dl2_err_lm_us_allMC_m_charm_sum->Add(h_dl2_err_lm_us_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_dl2_err_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_dl2_err_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_dl2_err_lm_us_allMC_m_charm_sum->SetFillStyle(1001);

/// b bbar
  h_dl2_err_lm_us_allMC_sum->Add(h_dl2_err_hm_us_allMC_sum,1.);
  h_dl2_err_lm_us_allMC_sum->Add(h_dl2_err_lm_ls_allMC_sum,1.);
  h_dl2_err_lm_us_allMC_sum->Add(h_dl2_err_hm_ls_allMC_sum,1.);

  h_dl2_err_lm_us_allMC_sum->Add(h_dl2_err_lm_us_allMC_m_charm_sum,1.);

  if(bg_black)    h_dl2_err_lm_us_allMC_sum->SetFillColor(111); 
  else            h_dl2_err_lm_us_allMC_sum->SetFillColor(22222); 
  h_dl2_err_lm_us_allMC_sum->SetFillStyle(1001);

  h_dl2_err_lm_us_allMC_sum->Draw("hist same");
  h_dl2_err_lm_us_allMC_m_charm_sum->Draw("hist same");
  h_dl2_err_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_dl2_err_hm_ls_MC_lflbg_sum->Draw("hist same");

//Draw data again as top layer

  h_dl2_err_lm_us_data->Draw("P same");

  TLatex *   tex5_1;

  leg6 = new TLegend(0.577527,0.634108,0.914689,0.839256,NULL,"brNDC");
  if(bg_black)  leg6->SetLineColor(1);
  else leg6->SetLineColor(4);
  leg6->SetLineStyle(1);
  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetLineWidth(1);
  leg6->SetBorderSize(0);
  leg6->AddEntry(h_dl2_err_lm_us_data,"ZEUS data 03p-07p","pe");
  leg6->AddEntry(h_dl2_err_lm_us_allMC_sum,"b#bar{b} MC","f");
  leg6->AddEntry(h_dl2_err_lm_us_allMC_m_charm_sum,"J/#psi, #psi', #varUpsilon, BH MC","f");
  leg6->AddEntry(h_dl2_err_lm_us_MC_c_p_lflbg_sum,"c#bar{c} MC","f");
  leg6->AddEntry(h_dl2_err_lm_us_MC_lflbg_sum,"lfl bg","f");
  leg6->Draw();


  canv2_1->RedrawAxis();

  canv2->cd();

// Mirrored Decay Length Significance

//  TCanvas * canv4 = new TCanvas("canv4","canv4",600,600);

  TCanvas * canv2 = new TCanvas("canv2","canv2",1005,500);

  canv2_1 = new TPad("canv2_1", "canv2_1", 0.00, 0.0, 0.50, 0.99);
  canv2_1->Draw();
  canv2_1->SetLogy();
  canv2_1->cd();
  canv2_1->Range(-3.86269,-150.588,3.62985,830.588);

  h_dl2_sign_mirr_lm_us_data->Add(h_dl2_sign_mirr_hm_us_data,1.);
  h_dl2_sign_mirr_lm_us_data->Add(h_dl2_sign_mirr_lm_ls_data,1.);
  h_dl2_sign_mirr_lm_us_data->Add(h_dl2_sign_mirr_hm_ls_data,1.);
  h_dl2_sign_mirr_lm_us_data->SetMarkerStyle(8);

// format X axis

  h_dl2_sign_mirr_lm_us_data->GetXaxis()->SetRangeUser(0.,30.);
  h_dl2_sign_mirr_lm_us_data->GetXaxis()->SetTitle("S^{+} - S^{-}");
  h_dl2_sign_mirr_lm_us_data->GetXaxis()->SetTitleSize(0.06);
  h_dl2_sign_mirr_lm_us_data->GetXaxis()->SetTitleOffset(0.9);
  h_dl2_sign_mirr_lm_us_data->GetXaxis()->SetLabelSize(0.04);
  h_dl2_sign_mirr_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_dl2_sign_mirr_lm_us_data->GetYaxis()->SetRangeUser(0.0,2500.);
  h_dl2_sign_mirr_lm_us_data->GetYaxis()->SetTitle("Events");
  h_dl2_sign_mirr_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_dl2_sign_mirr_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_dl2_sign_mirr_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_dl2_sign_mirr_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_dl2_sign_mirr_lm_us_data->SetMarkerSize(1.);
  else            h_dl2_sign_mirr_lm_us_data->SetMarkerSize(.6);
  h_dl2_sign_mirr_lm_us_data->Draw("P");

  h_dl2_sign_mirr_lm_us_allMC_sum->Add(h_dl2_sign_mirr_hm_us_allMC_sum,1.);
  h_dl2_sign_mirr_lm_us_allMC_sum->Add(h_dl2_sign_mirr_lm_ls_allMC_sum,1.);
  h_dl2_sign_mirr_lm_us_allMC_sum->Add(h_dl2_sign_mirr_hm_ls_allMC_sum,1.);
  if(bg_black)    h_dl2_sign_mirr_lm_us_allMC_sum->SetFillColor(111); 
  else            h_dl2_sign_mirr_lm_us_allMC_sum->SetFillColor(22222); 
  h_dl2_sign_mirr_lm_us_allMC_sum->SetFillStyle(1001);
  h_dl2_sign_mirr_lm_us_allMC_sum->Draw("hist same");

  h_dl2_sign_mirr_lm_us_allMC_m_charm_sum->Add(h_dl2_sign_mirr_hm_us_allMC_m_charm_sum,1.);
  if(bg_black)    h_dl2_sign_mirr_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_dl2_sign_mirr_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_dl2_sign_mirr_lm_us_allMC_m_charm_sum->SetFillStyle(1001);
  h_dl2_sign_mirr_lm_us_allMC_m_charm_sum->Draw("hist same");

  h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum->Add(h_dl2_sign_mirr_hm_us_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);
  h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum->Draw("hist same");

  h_dl2_sign_mirr_lm_us_MC_lflbg_sum->Add(h_dl2_sign_mirr_hm_us_MC_lflbg_sum,1.);
  h_dl2_sign_mirr_lm_us_MC_lflbg_sum->Add(h_dl2_sign_mirr_lm_ls_MC_lflbg_sum,1.);
  h_dl2_sign_mirr_lm_us_MC_lflbg_sum->Add(h_dl2_sign_mirr_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_dl2_sign_mirr_lm_us_MC_lflbg_sum->SetFillColor(19); 
  else            h_dl2_sign_mirr_lm_us_MC_lflbg_sum->SetFillColor(444); 
  h_dl2_sign_mirr_lm_us_MC_lflbg_sum->SetFillStyle(1001);
  h_dl2_sign_mirr_lm_us_MC_lflbg_sum->Draw("hist same");

 h_dl2_sign_mirr_lm_us_data->Draw("P same");

  canv2_1->RedrawAxis();

  canv2->cd();

  canv2_2 = new TPad("canv2_2", "canv2_2", 0.50, 0.00, 1.0, 0.99);
  canv2_2->Draw();
  canv2_2->cd();
  canv2_2->Range(-3.86269,-150.588,3.62985,830.588);


//Draw data again as top layer
  h_dl2_sign_mirr_lm_us_data->Draw("P");
  h_dl2_sign_mirr_lm_us_allMC_sum->Draw("hist same");
  h_dl2_sign_mirr_lm_us_allMC_m_charm_sum->Draw("hist same");
  h_dl2_sign_mirr_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_dl2_sign_mirr_lm_us_MC_lflbg_sum->Draw("hist same");
  h_dl2_sign_mirr_lm_us_data->Draw("P same");
  
  canv2_2->RedrawAxis();

  canv2->cd();

//*********************************************************************************
//*********************************************************************************
//*******Plotting Script ends here***Plotting Script ends here*********************
//*********************************************************************************
//*******Plotting Script ends here***Plotting Script ends here*********************
//*********************************************************************************
//*******Plotting Script ends here***Plotting Script ends here*********************
//*********************************************************************************
//*********************************************************************************


}
