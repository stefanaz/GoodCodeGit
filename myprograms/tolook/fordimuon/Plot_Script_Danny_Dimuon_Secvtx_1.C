{
  TStyle *zeus_style = gInclude->ZEUSSetStyle();

// #include "Draw_Errorbar.C"

  bool check_Nevents = true;	

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

// # of sec vtx

TH1D* h_nrsecvtx_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_nis_data");
TH1D* h_nrsecvtx_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_nis_allMC_sum");
TH1D* h_nrsecvtx_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_nis_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_nis_MC_c_p_lflbg_sum");

TH1D* h_nrsecvtx_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_nis_data");
TH1D* h_nrsecvtx_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_nis_allMC_sum");
TH1D* h_nrsecvtx_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_nis_MC_lflbg_sum");

TH1D* h_nrsecvtx_lm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_is_data");
TH1D* h_nrsecvtx_lm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_is_allMC_sum");
TH1D* h_nrsecvtx_lm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_is_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_is_MC_c_p_lflbg_sum");

TH1D* h_nrsecvtx_hm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_is_data");
TH1D* h_nrsecvtx_hm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_is_allMC_sum");
TH1D* h_nrsecvtx_hm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_is_MC_lflbg_sum");

TH1D* h_nrsecvtx_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_data");
TH1D* h_nrsecvtx_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_allMC_sum");
TH1D* h_nrsecvtx_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_us_MC_lflbg_sum");

TH1D* h_nrsecvtx_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_data");
TH1D* h_nrsecvtx_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_allMC_sum");
TH1D* h_nrsecvtx_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_us_MC_lflbg_sum");

TH1D* h_nrsecvtx_lm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_nis_data");
TH1D* h_nrsecvtx_lm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_nis_allMC_sum");
TH1D* h_nrsecvtx_lm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_nis_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_nis_MC_c_p_lflbg_sum");

TH1D* h_nrsecvtx_hm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_nis_data");
TH1D* h_nrsecvtx_hm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_nis_allMC_sum");
TH1D* h_nrsecvtx_hm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_nis_MC_lflbg_sum");

TH1D* h_nrsecvtx_lm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_is_data");
TH1D* h_nrsecvtx_lm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_is_allMC_sum");
TH1D* h_nrsecvtx_lm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_is_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_is_MC_c_p_lflbg_sum");

TH1D* h_nrsecvtx_hm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_is_data");
TH1D* h_nrsecvtx_hm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_is_allMC_sum");
TH1D* h_nrsecvtx_hm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_is_MC_lflbg_sum");

TH1D* h_nrsecvtx_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_data");
TH1D* h_nrsecvtx_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_allMC_sum");
TH1D* h_nrsecvtx_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_hm_ls_MC_lflbg_sum");

TH1D* h_nrsecvtx_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_data");
TH1D* h_nrsecvtx_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_allMC_sum");
TH1D* h_nrsecvtx_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_nrsecvtx_lm_ls_MC_lflbg_sum");

// Multiplicity of Tracks in sec vtx

TH1D* h_multiplicity_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_nis_data");
TH1D* h_multiplicity_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_nis_allMC_sum");
TH1D* h_multiplicity_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_nis_allMC_m_charm_sum");
TH1D* h_multiplicity_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_nis_MC_lflbg_sum");
TH1D* h_multiplicity_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_nis_MC_c_p_lflbg_sum");

TH1D* h_multiplicity_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_nis_data");
TH1D* h_multiplicity_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_nis_allMC_sum");
TH1D* h_multiplicity_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_nis_allMC_m_charm_sum");
TH1D* h_multiplicity_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_nis_MC_lflbg_sum");

TH1D* h_multiplicity_lm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_is_data");
TH1D* h_multiplicity_lm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_is_allMC_sum");
TH1D* h_multiplicity_lm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_is_allMC_m_charm_sum");
TH1D* h_multiplicity_lm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_is_MC_lflbg_sum");
TH1D* h_multiplicity_lm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_is_MC_c_p_lflbg_sum");

TH1D* h_multiplicity_hm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_is_data");
TH1D* h_multiplicity_hm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_is_allMC_sum");
TH1D* h_multiplicity_hm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_is_allMC_m_charm_sum");
TH1D* h_multiplicity_hm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_hm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_is_MC_lflbg_sum");

TH1D* h_multiplicity_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_data");
TH1D* h_multiplicity_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_allMC_sum");
TH1D* h_multiplicity_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_allMC_m_charm_sum");
TH1D* h_multiplicity_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_us_MC_lflbg_sum");

TH1D* h_multiplicity_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_data");
TH1D* h_multiplicity_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_allMC_sum");
TH1D* h_multiplicity_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_allMC_m_charm_sum");
TH1D* h_multiplicity_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_us_MC_lflbg_sum");

TH1D* h_multiplicity_lm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_nis_data");
TH1D* h_multiplicity_lm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_nis_allMC_sum");
TH1D* h_multiplicity_lm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_nis_allMC_m_charm_sum");
TH1D* h_multiplicity_lm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_nis_MC_lflbg_sum");
TH1D* h_multiplicity_lm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_nis_MC_c_p_lflbg_sum");

TH1D* h_multiplicity_hm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_nis_data");
TH1D* h_multiplicity_hm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_nis_allMC_sum");
TH1D* h_multiplicity_hm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_nis_allMC_m_charm_sum");
TH1D* h_multiplicity_hm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_hm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_nis_MC_lflbg_sum");

TH1D* h_multiplicity_lm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_is_data");
TH1D* h_multiplicity_lm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_is_allMC_sum");
TH1D* h_multiplicity_lm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_is_allMC_m_charm_sum");
TH1D* h_multiplicity_lm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_is_MC_lflbg_sum");
TH1D* h_multiplicity_lm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_is_MC_c_p_lflbg_sum");

TH1D* h_multiplicity_hm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_is_data");
TH1D* h_multiplicity_hm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_is_allMC_sum");
TH1D* h_multiplicity_hm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm
_ls_is_allMC_m_charm_sum");
TH1D* h_multiplicity_hm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_hm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_is_MC_lflbg_sum");

TH1D* h_multiplicity_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_data");
TH1D* h_multiplicity_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_allMC_sum");
TH1D* h_multiplicity_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_allMC_m_charm_sum");
TH1D* h_multiplicity_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_hm_ls_MC_lflbg_sum");

TH1D* h_multiplicity_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_data");
TH1D* h_multiplicity_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_allMC_sum");
TH1D* h_multiplicity_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_allMC_m_charm_sum");
TH1D* h_multiplicity_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_multiplicity_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_multiplicity_lm_ls_MC_lflbg_sum");

// Vertex Mass

TH1D* h_vtxmass_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_nis_data");
TH1D* h_vtxmass_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_nis_allMC_sum");
TH1D* h_vtxmass_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_nis_allMC_m_charm_sum");
TH1D* h_vtxmass_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_nis_MC_lflbg_sum");
TH1D* h_vtxmass_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_nis_MC_c_p_lflbg_sum");

TH1D* h_vtxmass_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_nis_data");
TH1D* h_vtxmass_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_nis_allMC_sum");
TH1D* h_vtxmass_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_nis_allMC_m_charm_sum");
TH1D* h_vtxmass_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_nis_MC_lflbg_sum");

TH1D* h_vtxmass_lm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_is_data");
TH1D* h_vtxmass_lm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_is_allMC_sum");
TH1D* h_vtxmass_lm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_is_allMC_m_charm_sum");
TH1D* h_vtxmass_lm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_is_MC_lflbg_sum");
TH1D* h_vtxmass_lm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_is_MC_c_p_lflbg_sum");

TH1D* h_vtxmass_hm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_is_data");
TH1D* h_vtxmass_hm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_is_allMC_sum");
TH1D* h_vtxmass_hm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_is_allMC_m_charm_sum");
TH1D* h_vtxmass_hm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_hm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_is_MC_lflbg_sum");

TH1D* h_vtxmass_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_data");
TH1D* h_vtxmass_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_allMC_sum");
TH1D* h_vtxmass_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_allMC_m_charm_sum");
TH1D* h_vtxmass_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_us_MC_lflbg_sum");

TH1D* h_vtxmass_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_data");
TH1D* h_vtxmass_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_allMC_sum");
TH1D* h_vtxmass_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_allMC_m_charm_sum");
TH1D* h_vtxmass_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_us_MC_lflbg_sum");

TH1D* h_vtxmass_lm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_nis_data");
TH1D* h_vtxmass_lm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_nis_allMC_sum");
TH1D* h_vtxmass_lm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_nis_allMC_m_charm_sum");
TH1D* h_vtxmass_lm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_nis_MC_lflbg_sum");
TH1D* h_vtxmass_lm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_nis_MC_c_p_lflbg_sum");

TH1D* h_vtxmass_hm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_nis_data");
TH1D* h_vtxmass_hm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_nis_allMC_sum");
TH1D* h_vtxmass_hm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_nis_allMC_m_charm_sum");
TH1D* h_vtxmass_hm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_hm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_nis_MC_lflbg_sum");

TH1D* h_vtxmass_lm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_is_data");
TH1D* h_vtxmass_lm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_is_allMC_sum");
TH1D* h_vtxmass_lm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_is_allMC_m_charm_sum");
TH1D* h_vtxmass_lm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_is_MC_lflbg_sum");
TH1D* h_vtxmass_lm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_is_MC_c_p_lflbg_sum");

TH1D* h_vtxmass_hm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_is_data");
TH1D* h_vtxmass_hm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_is_allMC_sum");
TH1D* h_vtxmass_hm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_is_allMC_m_charm_sum");
TH1D* h_vtxmass_hm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_hm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_is_MC_lflbg_sum");

TH1D* h_vtxmass_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_data");
TH1D* h_vtxmass_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_allMC_sum");
TH1D* h_vtxmass_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_allMC_m_charm_sum");
TH1D* h_vtxmass_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_hm_ls_MC_lflbg_sum");

TH1D* h_vtxmass_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_data");
TH1D* h_vtxmass_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_allMC_sum");
TH1D* h_vtxmass_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_allMC_m_charm_sum");
TH1D* h_vtxmass_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_vtxmass_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_vtxmass_lm_ls_MC_lflbg_sum");

// Chi2/Ndof

TH1D* h_chi2ndof_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_nis_data");
TH1D* h_chi2ndof_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_nis_allMC_sum");
TH1D* h_chi2ndof_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_nis_allMC_m_charm_sum");
TH1D* h_chi2ndof_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_nis_MC_lflbg_sum");
TH1D* h_chi2ndof_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_nis_MC_c_p_lflbg_sum");

TH1D* h_chi2ndof_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_nis_data");
TH1D* h_chi2ndof_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_nis_allMC_sum");
TH1D* h_chi2ndof_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_nis_allMC_m_charm_sum");
TH1D* h_chi2ndof_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_nis_MC_lflbg_sum");

TH1D* h_chi2ndof_lm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_is_data");
TH1D* h_chi2ndof_lm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_is_allMC_sum");
TH1D* h_chi2ndof_lm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_is_allMC_m_charm_sum");
TH1D* h_chi2ndof_lm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_is_MC_lflbg_sum");
TH1D* h_chi2ndof_lm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_is_MC_c_p_lflbg_sum");

TH1D* h_chi2ndof_hm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_is_data");
TH1D* h_chi2ndof_hm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_is_allMC_sum");
TH1D* h_chi2ndof_hm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_is_allMC_m_charm_sum");
TH1D* h_chi2ndof_hm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_hm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_is_MC_lflbg_sum");

TH1D* h_chi2ndof_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_data");
TH1D* h_chi2ndof_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_allMC_sum");
TH1D* h_chi2ndof_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_allMC_m_charm_sum");
TH1D* h_chi2ndof_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_us_MC_lflbg_sum");

TH1D* h_chi2ndof_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_data");
TH1D* h_chi2ndof_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_allMC_sum");
TH1D* h_chi2ndof_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_allMC_m_charm_sum");
TH1D* h_chi2ndof_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_us_MC_lflbg_sum");


TH1D* h_chi2ndof_lm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_nis_data");
TH1D* h_chi2ndof_lm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_nis_allMC_sum");
TH1D* h_chi2ndof_lm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_nis_allMC_m_charm_sum");
TH1D* h_chi2ndof_lm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_nis_MC_lflbg_sum");
TH1D* h_chi2ndof_lm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_nis_MC_c_p_lflbg_sum");

TH1D* h_chi2ndof_hm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_nis_data");
TH1D* h_chi2ndof_hm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_nis_allMC_sum");
TH1D* h_chi2ndof_hm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_nis_allMC_m_charm_sum");
TH1D* h_chi2ndof_hm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_hm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_nis_MC_lflbg_sum");

TH1D* h_chi2ndof_lm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_is_data");
TH1D* h_chi2ndof_lm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_is_allMC_sum");
TH1D* h_chi2ndof_lm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_is_allMC_m_charm_sum");
TH1D* h_chi2ndof_lm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_is_MC_lflbg_sum");
TH1D* h_chi2ndof_lm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_is_MC_c_p_lflbg_sum");

TH1D* h_chi2ndof_hm_ls_is_data               = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_is_data");
TH1D* h_chi2ndof_hm_ls_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_is_allMC_sum");
TH1D* h_chi2ndof_hm_ls_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_is_allMC_m_charm_sum");
TH1D* h_chi2ndof_hm_ls_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_hm_ls_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_is_MC_lflbg_sum");

TH1D* h_chi2ndof_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_data");
TH1D* h_chi2ndof_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_allMC_sum");
TH1D* h_chi2ndof_hm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_allMC_m_charm_sum");
TH1D* h_chi2ndof_hm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_hm_ls_MC_lflbg_sum");

TH1D* h_chi2ndof_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_data");
TH1D* h_chi2ndof_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_allMC_sum");
TH1D* h_chi2ndof_lm_ls_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_allMC_m_charm_sum");
TH1D* h_chi2ndof_lm_ls_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_chi2ndof_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_chi2ndof_lm_ls_MC_lflbg_sum");


//***********************************************************************
//****  plotting the ZEUS style guys!  **********************************
//***********************************************************************



  TCanvas * canv = new TCanvas("canv","canv",1005,500);

  canv->cd();


// # Sec Vtx

  canv_1 = new TPad("canv_1", "canv_1", 0.0, 0.00, 0.50, 0.99);
  canv_1->Draw();
  canv_1->cd();
  canv_1->Range(-3.86269,-150.588,3.62985,830.588);

  h_nrsecvtx_lm_us_data->Add(h_nrsecvtx_hm_us_data,1.);
  h_nrsecvtx_lm_us_data->Add(h_nrsecvtx_lm_ls_data,1.);
  h_nrsecvtx_lm_us_data->Add(h_nrsecvtx_hm_ls_data,1.);
  h_nrsecvtx_lm_us_data->SetMarkerStyle(8);


// format X axis

  h_nrsecvtx_lm_us_data->GetXaxis()->SetRangeUser(0.0,10.);
  h_nrsecvtx_lm_us_data->GetXaxis()->SetTitle("Nr. Sec Vtx");
  h_nrsecvtx_lm_us_data->GetXaxis()->SetTitleSize(0.06);
  h_nrsecvtx_lm_us_data->GetXaxis()->SetTitleOffset(0.9);
  h_nrsecvtx_lm_us_data->GetXaxis()->SetLabelSize(0.05);
  h_nrsecvtx_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_nrsecvtx_lm_us_data->GetYaxis()->SetRangeUser(0.0,3550.);
  h_nrsecvtx_lm_us_data->GetYaxis()->SetTitle("Events");
  h_nrsecvtx_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_nrsecvtx_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_nrsecvtx_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_nrsecvtx_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_nrsecvtx_lm_us_data->SetMarkerSize(1.);
  else            h_nrsecvtx_lm_us_data->SetMarkerSize(.6);
  h_nrsecvtx_lm_us_data->Draw("P");

/// lfl 
  h_nrsecvtx_hm_ls_MC_lflbg_sum->Add(h_nrsecvtx_hm_ls_MC_lflbg_sum,1.);
  h_nrsecvtx_hm_ls_MC_lflbg_sum->Add(h_nrsecvtx_lm_ls_MC_lflbg_sum,1.);
  h_nrsecvtx_hm_ls_MC_lflbg_sum->Add(h_nrsecvtx_lm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_nrsecvtx_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_nrsecvtx_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_nrsecvtx_hm_ls_MC_lflbg_sum->SetFillStyle(1001);


/// c cbar
  h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->Add(h_nrsecvtx_hm_us_MC_c_p_lflbg_sum,1.);
  h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->Add(h_nrsecvtx_hm_ls_MC_c_p_lflbg_sum,-1.);
  h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->Add(h_nrsecvtx_lm_ls_MC_c_p_lflbg_sum,-1.);

  h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->Add(h_nrsecvtx_hm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);


/// Jpsi ...
  h_nrsecvtx_hm_us_allMC_m_charm_sum->Add(h_nrsecvtx_lm_us_allMC_m_charm_sum,1.);
  h_nrsecvtx_hm_us_allMC_m_charm_sum->Add(h_nrsecvtx_lm_ls_allMC_m_charm_sum,-1.);
  h_nrsecvtx_hm_us_allMC_m_charm_sum->Add(h_nrsecvtx_hm_ls_allMC_m_charm_sum,-1.);

  h_nrsecvtx_hm_us_allMC_m_charm_sum->Add(h_nrsecvtx_lm_us_MC_c_p_lflbg_sum,1.);


  if(bg_black)    h_nrsecvtx_hm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_nrsecvtx_hm_us_allMC_m_charm_sum->SetFillColor(555);
  h_nrsecvtx_hm_us_allMC_m_charm_sum->SetFillStyle(1001);

/// b bbar
  h_nrsecvtx_lm_us_allMC_sum->Add(h_nrsecvtx_hm_us_allMC_sum,1.);
  h_nrsecvtx_lm_us_allMC_sum->Add(h_nrsecvtx_lm_ls_allMC_sum,1.);
  h_nrsecvtx_lm_us_allMC_sum->Add(h_nrsecvtx_hm_ls_allMC_sum,1.);
  h_nrsecvtx_lm_us_allMC_sum->Add(h_nrsecvtx_hm_us_allMC_m_charm_sum,1.);


/// *********************************************  ///
// cout<<" Bin_few content MC = "<<(h_nrsecvtx_lm_us_allMC_sum->GetBinContent(2) + (h_nrsecvtx_lm_us_allMC_sum->GetBinContent(3))*2 + (h_nrsecvtx_lm_us_allMC_sum->GetBinContent(4))*3 + (h_nrsecvtx_lm_us_allMC_sum->GetBinContent(5))*4 + (h_nrsecvtx_lm_us_allMC_sum->GetBinContent(6))*5 ) <<endl;


/// *********************************************  ///


  if(bg_black)    h_nrsecvtx_lm_us_allMC_sum->SetFillColor(111); 
  else            h_nrsecvtx_lm_us_allMC_sum->SetFillColor(22222); 
  h_nrsecvtx_lm_us_allMC_sum->SetFillStyle(1001);

// 	TH1D *h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down = (TH1D*) h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->Clone("h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down");
// 	Get_hist_minus_error(h_nrsecvtx_lm_us_MC_c_p_lflbg_sum, h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down);
// 	h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->SetFillStyle(3354);
// 	h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down->SetLineWidth(1.);

// cout<<" bin1 = "<<h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down->GetBinContent(1)<<endl;
// cout<<" bin2 = "<<h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down->GetBinContent(2)<<endl;

  h_nrsecvtx_lm_us_allMC_sum->Draw("hist same");
  h_nrsecvtx_hm_us_allMC_m_charm_sum->Draw("hist same");
//   h_nrsecvtx_lm_us_MC_c_p_lflbg_sum_down->Draw("hist same ");
  h_nrsecvtx_lm_us_MC_c_p_lflbg_sum->Draw("hist same ");
  h_nrsecvtx_hm_ls_MC_lflbg_sum->Draw("hist same");


  h_nrsecvtx_lm_us_data->Draw("P same");

  leg6 = new TLegend(0.474751,0.594708,0.900132,0.853784,NULL,"brNDC");
  if(bg_black)  leg6->SetLineColor(1);
  else leg6->SetLineColor(4);
  leg6->SetLineStyle(1);
  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetLineWidth(1);
  leg6->SetBorderSize(0);
  leg6->AddEntry(h_nrsecvtx_lm_us_data,"ZEUS data 03p-07p","pe");
  leg6->AddEntry(h_nrsecvtx_lm_us_allMC_sum,"b#bar{b} MC","f");
  leg6->AddEntry(h_nrsecvtx_hm_us_allMC_m_charm_sum,"J/#psi, #psi', #varUpsilon, BH MC","f");
  leg6->AddEntry(h_nrsecvtx_lm_us_MC_c_p_lflbg_sum,"c#bar{c} MC","f");
  leg6->AddEntry(h_nrsecvtx_hm_ls_MC_lflbg_sum,"lfl bg","f");
  leg6->Draw();
  
  canv_1->RedrawAxis();


  canv->cd();

// Multiplicity in Sec. Vertices

  canv_2 = new TPad("canv_2", "canv_2", 0.50, 0.00, 1.0, 0.99);
  canv_2->Draw();
  canv_2->cd();
  canv_2->Range(-3.86269,-150.588,3.62985,830.588);

  h_multiplicity_lm_us_data->Add(h_multiplicity_hm_us_data,1.);
  h_multiplicity_lm_us_data->Add(h_multiplicity_lm_ls_data,1.);
  h_multiplicity_lm_us_data->Add(h_multiplicity_hm_ls_data,1.);  
  h_multiplicity_lm_us_data->SetMarkerStyle(8);

// format X axis

  h_multiplicity_lm_us_data->GetXaxis()->SetRangeUser(0.0,12.);
  h_multiplicity_lm_us_data->GetXaxis()->SetTitle("Track multiplicity");
  h_multiplicity_lm_us_data->GetXaxis()->SetTitleSize(0.06);
  h_multiplicity_lm_us_data->GetXaxis()->SetTitleOffset(0.9);
  h_multiplicity_lm_us_data->GetXaxis()->SetLabelSize(0.05);
  h_multiplicity_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_multiplicity_lm_us_data->GetYaxis()->SetRangeUser(0.0,3050.);
  h_multiplicity_lm_us_data->GetYaxis()->SetTitle("Events");
  h_multiplicity_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_multiplicity_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_multiplicity_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_multiplicity_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_multiplicity_lm_us_data->SetMarkerSize(1.);
  else            h_multiplicity_lm_us_data->SetMarkerSize(.6);
  h_multiplicity_lm_us_data->Draw("P");

/// lfl
  h_multiplicity_hm_ls_MC_lflbg_sum->Add(h_multiplicity_hm_ls_MC_lflbg_sum,1.);
  h_multiplicity_hm_ls_MC_lflbg_sum->Add(h_multiplicity_lm_ls_MC_lflbg_sum,1.);
  h_multiplicity_hm_ls_MC_lflbg_sum->Add(h_multiplicity_lm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_multiplicity_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_multiplicity_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_multiplicity_hm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_multiplicity_lm_us_MC_c_p_lflbg_sum->Add(h_multiplicity_hm_us_MC_c_p_lflbg_sum,1.);
  h_multiplicity_lm_us_MC_c_p_lflbg_sum->Add(h_multiplicity_lm_ls_MC_c_p_lflbg_sum,-1.);
  h_multiplicity_lm_us_MC_c_p_lflbg_sum->Add(h_multiplicity_hm_ls_MC_c_p_lflbg_sum,-1.);

  h_multiplicity_lm_us_MC_c_p_lflbg_sum->Add(h_multiplicity_hm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_multiplicity_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_multiplicity_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_multiplicity_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...

  h_multiplicity_lm_us_allMC_m_charm_sum->Add(h_multiplicity_hm_us_allMC_m_charm_sum,1.);
  h_multiplicity_lm_us_allMC_m_charm_sum->Add(h_multiplicity_lm_ls_allMC_m_charm_sum,-1.);
  h_multiplicity_lm_us_allMC_m_charm_sum->Add(h_multiplicity_hm_ls_allMC_m_charm_sum,-1.);

  h_multiplicity_lm_us_allMC_m_charm_sum->Scale(2.9);

  h_multiplicity_lm_us_allMC_m_charm_sum->Add(h_multiplicity_lm_us_MC_c_p_lflbg_sum,1.);

  if(bg_black)    h_multiplicity_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_multiplicity_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_multiplicity_lm_us_allMC_m_charm_sum->SetFillStyle(1001);



/// bbbar
  h_multiplicity_lm_us_allMC_sum->Add(h_multiplicity_hm_us_allMC_sum,1.);
  h_multiplicity_lm_us_allMC_sum->Add(h_multiplicity_lm_ls_allMC_sum,1.);
  h_multiplicity_lm_us_allMC_sum->Add(h_multiplicity_hm_ls_allMC_sum,1.);

  h_multiplicity_lm_us_allMC_sum->Add(h_multiplicity_lm_us_allMC_m_charm_sum,1.);

  if(bg_black)    h_multiplicity_lm_us_allMC_sum->SetFillColor(111); 
  else            h_multiplicity_lm_us_allMC_sum->SetFillColor(22222); 
  h_multiplicity_lm_us_allMC_sum->SetFillStyle(1001);

//   Draw_Errorbar("h_multiplicity_lm_us_data", "data Multiplicity");


  h_multiplicity_lm_us_allMC_sum->Draw("hist same");
  h_multiplicity_lm_us_allMC_m_charm_sum->Draw("hist same");
  h_multiplicity_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_multiplicity_hm_ls_MC_lflbg_sum->Draw("hist same");
//Draw data again as top layer

  h_multiplicity_lm_us_data->Draw("P same");
 
  canv_2->RedrawAxis();

Double_t Data_count = 0.;
Double_t MC_count = 0.;
for (Int_t i=1;i<=10;i++) {Data_count = Data_count + h_multiplicity_lm_us_data->GetBinContent(i);}
for (Int_t i=1;i<=10;i++) {MC_count = MC_count + h_multiplicity_lm_us_allMC_sum->GetBinContent(i);}
// cout<<" Sum bins data = "<<Data_count<<"   MC = "<<MC_count<<endl;


cout<<endl<<" ***************** Nr. Sec Vtx  cheking BEGIN 2  ****************** " <<endl;
Double_t bins = 0.0;
for (Int_t i=1;i<=12;i++) {bins = bins + (h_multiplicity_lm_us_allMC_sum->GetBinContent(i));}
cout<<"bin"<<i<<" : "<<"; Multiplicity in bin  ="<<bins<<endl;/*bins = 0.;*/

cout<<endl<<" ***************** Nr. Sec Vtx  cheking END 2 ****************** " <<endl;


  canv->cd();

// Vtxmass

  TCanvas * canv2 = new TCanvas("canv2","canv2",1005,500);

  canv2->cd();

  canv2_1 = new TPad("canv2_1", "canv2_1", 0.00, 0.00, 0.50, 0.99);
  canv2_1->Draw();
  canv2_1->cd();
  canv2_1->Range(-3.86269,-150.588,3.62985,830.588);

  h_vtxmass_lm_us_data->Add(h_vtxmass_hm_us_data,1.);
  h_vtxmass_lm_us_data->Add(h_vtxmass_lm_ls_data,1.);
  h_vtxmass_lm_us_data->Add(h_vtxmass_hm_ls_data,1.);
  h_vtxmass_lm_us_data->SetMarkerStyle(8);

// format X axis

  h_vtxmass_lm_us_data->GetXaxis()->SetRangeUser(0.0,100);
  h_vtxmass_lm_us_data->GetXaxis()->SetTitle("m_{Sec. vtx} [GeV]");
  h_vtxmass_lm_us_data->GetXaxis()->SetTitleSize(0.06);
  h_vtxmass_lm_us_data->GetXaxis()->SetTitleOffset(0.9);
  h_vtxmass_lm_us_data->GetXaxis()->SetLabelSize(0.05);
  h_vtxmass_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_vtxmass_lm_us_data->GetYaxis()->SetRangeUser(0.0,2050.);
  h_vtxmass_lm_us_data->GetYaxis()->SetTitle("Events");
  h_vtxmass_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_vtxmass_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_vtxmass_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_vtxmass_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_vtxmass_lm_us_data->SetMarkerSize(1.);
  else            h_vtxmass_lm_us_data->SetMarkerSize(.6);
  h_vtxmass_lm_us_data->Rebin(5);
  h_vtxmass_lm_us_data->Draw("P");

/// lfl
  h_vtxmass_lm_ls_MC_lflbg_sum->Add(h_vtxmass_lm_ls_MC_lflbg_sum,1.);
  h_vtxmass_lm_ls_MC_lflbg_sum->Add(h_vtxmass_hm_ls_MC_lflbg_sum,1.);
  h_vtxmass_lm_ls_MC_lflbg_sum->Add(h_vtxmass_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_vtxmass_lm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_vtxmass_lm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_vtxmass_lm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_vtxmass_lm_us_MC_c_p_lflbg_sum->Add(h_vtxmass_hm_us_MC_c_p_lflbg_sum,1.);
  h_vtxmass_lm_us_MC_c_p_lflbg_sum->Add(h_vtxmass_lm_ls_MC_c_p_lflbg_sum,-1.);
  h_vtxmass_lm_us_MC_c_p_lflbg_sum->Add(h_vtxmass_hm_ls_MC_c_p_lflbg_sum,-1.);

  h_vtxmass_lm_us_MC_c_p_lflbg_sum->Add(h_vtxmass_lm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_vtxmass_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_vtxmass_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_vtxmass_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...

  h_vtxmass_lm_us_allMC_m_charm_sum->Add(h_vtxmass_hm_us_allMC_m_charm_sum,1.);
  h_vtxmass_lm_us_allMC_m_charm_sum->Add(h_vtxmass_lm_ls_allMC_m_charm_sum,-1.);
  h_vtxmass_lm_us_allMC_m_charm_sum->Add(h_vtxmass_hm_ls_allMC_m_charm_sum,-1.);

  h_vtxmass_lm_us_allMC_m_charm_sum->Scale(2.9);

  h_vtxmass_lm_us_allMC_m_charm_sum->Add(h_vtxmass_lm_us_MC_c_p_lflbg_sum,1.);

  if(bg_black)    h_vtxmass_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_vtxmass_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_vtxmass_lm_us_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar
  h_vtxmass_lm_us_allMC_sum->Add(h_vtxmass_hm_us_allMC_sum,1.);
  h_vtxmass_lm_us_allMC_sum->Add(h_vtxmass_lm_ls_allMC_sum,1.);
  h_vtxmass_lm_us_allMC_sum->Add(h_vtxmass_hm_ls_allMC_sum,1.);

  h_vtxmass_lm_us_allMC_sum->Add(h_vtxmass_lm_us_allMC_m_charm_sum,1.);

  if(bg_black)    h_vtxmass_lm_us_allMC_sum->SetFillColor(111); 
  else            h_vtxmass_lm_us_allMC_sum->SetFillColor(22222); 
  h_vtxmass_lm_us_allMC_sum->SetFillStyle(1001);


// Rebinning
  h_vtxmass_lm_ls_MC_lflbg_sum->Rebin(5);
  h_vtxmass_lm_us_MC_c_p_lflbg_sum->Rebin(5);
  h_vtxmass_lm_us_allMC_m_charm_sum->Rebin(5);
  h_vtxmass_lm_us_allMC_sum->Rebin(5);

//Draw data again as top layer

  h_vtxmass_lm_us_allMC_sum->Draw("hist same");
  h_vtxmass_lm_us_allMC_m_charm_sum->Draw("hist same");
  h_vtxmass_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_vtxmass_lm_ls_MC_lflbg_sum->Draw("hist same");
  h_vtxmass_lm_us_data->Draw("P same");

cout<<" *******************  Ratio 3  BEGIN *****************" <<endl;
Double_t Ratio_bins_lfl = 0.;
Double_t Ratio_bins_cc = 0.;
for (Int_t i=1;i<=12;i++) {
Ratio_bins_cc = Ratio_bins_cc + (h_vtxmass_lm_us_MC_c_p_lflbg_sum->GetBinContent(i));
Ratio_bins_lfl = Ratio_bins_lfl + (h_vtxmass_lm_ls_MC_lflbg_sum->GetBinContent(i));
}
cout<<Ratio_bins_cc/Ratio_bins_lfl<<endl;
Ratio_bins_cc = 0;
Ratio_bins_lfl = 0;
cout<<" *******************  Ratio 3  END *****************" <<endl;

  
  canv2_1->RedrawAxis();

  canv2->cd();

// Chi2/ndof

  canv2_2 = new TPad("canv2_2", "canv2_2", 0.50, 0.0, 1.0, 0.99);
  canv2_2->Draw();
  canv2_2->cd();
  canv2_2->Range(-3.86269,-150.588,3.62985,830.588);

  h_chi2ndof_lm_us_data->Add(h_chi2ndof_hm_us_data,1.);
  h_chi2ndof_lm_us_data->Add(h_chi2ndof_lm_ls_data,1.);
  h_chi2ndof_lm_us_data->Add(h_chi2ndof_hm_ls_data,1.);
  h_chi2ndof_lm_us_data->SetMarkerStyle(8);

// format X axis

  h_chi2ndof_lm_us_data->GetXaxis()->SetRangeUser(0.0,10.);
  h_chi2ndof_lm_us_data->GetXaxis()->SetTitle("#chi^{2}/ndf");
  h_chi2ndof_lm_us_data->GetXaxis()->SetTitleSize(0.06);
  h_chi2ndof_lm_us_data->GetXaxis()->SetTitleOffset(0.9);
  h_chi2ndof_lm_us_data->GetXaxis()->SetLabelSize(0.05);
  h_chi2ndof_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

//  h_chi2ndof_lm_us_data->GetYaxis()->SetRangeUser(0.0,1450.);
  h_chi2ndof_lm_us_data->GetYaxis()->SetTitle("Events");
  h_chi2ndof_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_chi2ndof_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_chi2ndof_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_chi2ndof_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_chi2ndof_lm_us_data->SetMarkerSize(1.);
  else            h_chi2ndof_lm_us_data->SetMarkerSize(.6);
  h_chi2ndof_lm_us_data->Draw("P");

/// lfl
  h_chi2ndof_lm_ls_MC_lflbg_sum->Add(h_chi2ndof_lm_ls_MC_lflbg_sum,1.);
  h_chi2ndof_lm_ls_MC_lflbg_sum->Add(h_chi2ndof_hm_ls_MC_lflbg_sum,1.);
  h_chi2ndof_lm_ls_MC_lflbg_sum->Add(h_chi2ndof_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_chi2ndof_lm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_chi2ndof_lm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_chi2ndof_lm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_chi2ndof_lm_us_MC_c_p_lflbg_sum->Add(h_chi2ndof_hm_us_MC_c_p_lflbg_sum,1.);
  h_chi2ndof_lm_us_MC_c_p_lflbg_sum->Add(h_chi2ndof_lm_ls_MC_c_p_lflbg_sum,-1.);
  h_chi2ndof_lm_us_MC_c_p_lflbg_sum->Add(h_chi2ndof_hm_ls_MC_c_p_lflbg_sum,-1.);

cout<<" Usefull info:  N1bin = "<<h_chi2ndof_lm_us_MC_c_p_lflbg_sum->GetBinContent(1)<<endl;

  h_chi2ndof_lm_us_MC_c_p_lflbg_sum->Add(h_chi2ndof_lm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_chi2ndof_lm_us_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_chi2ndof_lm_us_MC_c_p_lflbg_sum->SetFillColor(333);
  h_chi2ndof_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...

  h_chi2ndof_lm_us_allMC_m_charm_sum->Add(h_chi2ndof_hm_us_allMC_m_charm_sum,1.);
  h_chi2ndof_lm_us_allMC_m_charm_sum->Add(h_chi2ndof_lm_ls_allMC_m_charm_sum,-1.);
  h_chi2ndof_lm_us_allMC_m_charm_sum->Add(h_chi2ndof_hm_ls_allMC_m_charm_sum,-1.);

  h_chi2ndof_lm_us_allMC_m_charm_sum->Scale(2.97);

  h_chi2ndof_lm_us_allMC_m_charm_sum->Add(h_chi2ndof_lm_us_MC_c_p_lflbg_sum,1.);

  if(bg_black)    h_chi2ndof_lm_us_allMC_m_charm_sum->SetFillColor(16);
  else            h_chi2ndof_lm_us_allMC_m_charm_sum->SetFillColor(555);
  h_chi2ndof_lm_us_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar
  h_chi2ndof_lm_us_allMC_sum->Add(h_chi2ndof_hm_us_allMC_sum,1.);
  h_chi2ndof_lm_us_allMC_sum->Add(h_chi2ndof_lm_ls_allMC_sum,1.);
  h_chi2ndof_lm_us_allMC_sum->Add(h_chi2ndof_hm_ls_allMC_sum,1.);

  h_chi2ndof_lm_us_allMC_sum->Add(h_chi2ndof_lm_us_allMC_m_charm_sum,1.);

  if(bg_black)    h_chi2ndof_lm_us_allMC_sum->SetFillColor(111); 
  else            h_chi2ndof_lm_us_allMC_sum->SetFillColor(22222); 
  h_chi2ndof_lm_us_allMC_sum->SetFillStyle(1001);

//Draw data again as top layer

  h_chi2ndof_lm_us_allMC_sum->Draw("hist same");
  h_chi2ndof_lm_us_allMC_m_charm_sum->Draw("hist same");
  h_chi2ndof_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_chi2ndof_lm_ls_MC_lflbg_sum->Draw("hist same");
  h_chi2ndof_lm_us_data->Draw("P same");
  
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
