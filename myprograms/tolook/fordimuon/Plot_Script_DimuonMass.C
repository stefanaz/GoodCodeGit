{
  TStyle *zeus_style = gInclude->ZEUSSetStyle();

  gROOT->SetStyle("zeus_pub");

#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Nevents_Histosum/Draw_Errorbar.C"

  bool check_Nevents = true;	

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

//***********************************************************************
//****  non isolated high and low mass plots  ***************************
//***********************************************************************

TH1D* h_mmu_accept_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_nis_data");
TH1D* h_mmu_accept_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_nis_allMC_sum");
TH1D* h_mmu_accept_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_nis_allMC_m_charm_sum");
TH1D* h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_nis_MC_lflbg_sum");
TH1D* h_mmu_accept_lm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_nis_data");
TH1D* h_mmu_accept_lm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_nis_allMC_sum");
TH1D* h_mmu_accept_lm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_nis_allMC_m_charm_sum");
TH1D* h_mmu_accept_lm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_lm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_nis_MC_lflbg_sum");

TH1D* h_mmu_accept_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_nis_data");
TH1D* h_mmu_accept_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_nis_allMC_sum");
TH1D* h_mmu_accept_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_nis_allMC_m_charm_sum");
TH1D* h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_nis_MC_lflbg_sum");
TH1D* h_mmu_accept_hm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_nis_data");
TH1D* h_mmu_accept_hm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_nis_allMC_sum");
TH1D* h_mmu_accept_hm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_nis_allMC_m_charm_sum");
TH1D* h_mmu_accept_hm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_hm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_nis_MC_lflbg_sum");

//***********************************************************************
//****  isolated high and low mass plots  *******************************
//***********************************************************************

TH1D* h_mmu_accept_lm_us_is_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_is_data");
TH1D* h_mmu_accept_lm_us_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_is_allMC_sum");
TH1D* h_mmu_accept_lm_us_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_is_allMC_m_charm_sum");
TH1D* h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum");;
TH1D* h_mmu_accept_lm_us_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_is_MC_lflbg_sum");
TH1D* h_mmu_accept_lm_ls_is_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_is_data");
TH1D* h_mmu_accept_lm_ls_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_is_allMC_sum");
TH1D* h_mmu_accept_lm_ls_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_is_allMC_m_charm_sum");
TH1D* h_mmu_accept_lm_ls_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_is_MC_c_p_lflbg_sum");;
TH1D* h_mmu_accept_lm_ls_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_is_MC_lflbg_sum");

TH1D* h_mmu_accept_hm_us_is_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_is_data");
TH1D* h_mmu_accept_hm_us_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_is_allMC_sum");
TH1D* h_mmu_accept_hm_us_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_is_allMC_m_charm_sum");
TH1D* h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_hm_us_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_is_MC_lflbg_sum");
TH1D* h_mmu_accept_hm_ls_is_data              = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_is_data");
TH1D* h_mmu_accept_hm_ls_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_is_allMC_sum");
TH1D* h_mmu_accept_hm_ls_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_is_allMC_m_charm_sum");
TH1D* h_mmu_accept_hm_ls_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_hm_ls_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_is_MC_lflbg_sum");

//***********************************************************************
//****  isolated and non-isolated high and low mass plots  **************
//***********************************************************************

TH1D* h_mmu_accept_hm_us_data                 = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_data");
TH1D* h_mmu_accept_hm_us_allMC_sum            = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_allMC_sum");
TH1D* h_mmu_accept_hm_us_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_allMC_m_charm_sum");
TH1D* h_mmu_accept_hm_us_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_hm_us_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_us_MC_lflbg_sum");
TH1D* h_mmu_accept_hm_ls_data                 = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_data");
TH1D* h_mmu_accept_hm_ls_allMC_sum            = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_allMC_sum");
TH1D* h_mmu_accept_hm_ls_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_allMC_m_charm_sum");
TH1D* h_mmu_accept_hm_ls_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_hm_ls_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_hm_ls_MC_lflbg_sum");

TH1D* h_mmu_accept_lm_us_data                 = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_data");
TH1D* h_mmu_accept_lm_us_allMC_sum            = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_allMC_sum");
TH1D* h_mmu_accept_lm_us_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_allMC_m_charm_sum");
TH1D* h_mmu_accept_lm_us_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_lm_us_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_us_MC_lflbg_sum");
TH1D* h_mmu_accept_lm_ls_data                 = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_data");
TH1D* h_mmu_accept_lm_ls_allMC_sum            = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_allMC_sum");
TH1D* h_mmu_accept_lm_ls_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_allMC_m_charm_sum");
TH1D* h_mmu_accept_lm_ls_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_mmu_accept_lm_ls_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto("h_mmu_accept_lm_ls_MC_lflbg_sum");



//************************************************************************
//**************** Plotting the ZEUS Style *******************************
//************************************************************************
// evnts calculating: 
if (check_Nevents) { 
Double_t entries = 0.;
cout<<endl<<" Lm and Us : "<<endl;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_allMC_m_charm_sum->GetBinContent(i);}
cout<<" Charm check! Ent =  "<<entries<<endl;


entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_MC_c_p_lflbg_sum->GetBinContent(i);}
cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}
// new Canvas for nisandis mass ranges

  TCanvas * canv = new TCanvas("canv","canv",1005,955);

  TPad *canv_1 = new TPad("canv_1", "canv_1",0.0,0.50,0.50,0.99);
  canv_1->Draw();
  canv_1->cd();
  canv_1->Range(-3.09474,-280.175,10.5829,1586.15);

  h_mmu_accept_lm_us_data->SetMarkerStyle(8);



// format X axis

  h_mmu_accept_lm_us_data->GetXaxis()->SetRangeUser(1.5,4.0);
  h_mmu_accept_lm_us_data->GetXaxis()->SetNdivisions(505);
  h_mmu_accept_lm_us_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_lm_us_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_us_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_lm_us_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_lm_us_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_lm_us_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_lm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_lm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_us_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_lm_us_data->SetMarkerSize(1.);
  else            h_mmu_accept_lm_us_data->SetMarkerSize(.65);
  h_mmu_accept_lm_us_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_lm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_lm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_lm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c cbar
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_MC_lflbg_sum,1.);

  if(bg_black)    h_mmu_accept_lm_us_MC_c_p_lflbg_sum->SetFillColor(12); 
  else            h_mmu_accept_lm_us_MC_c_p_lflbg_sum->SetFillColor(333); 
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_mmu_accept_lm_us_allMC_m_charm_sum->Add(h_mmu_accept_lm_ls_allMC_m_charm_sum,-1.);
  h_mmu_accept_lm_us_allMC_m_charm_sum->Add(h_mmu_accept_lm_us_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_allMC_m_charm_sum->SetFillColor(16); 
  else            h_mmu_accept_lm_us_allMC_m_charm_sum->SetFillColor(555); 
  h_mmu_accept_lm_us_allMC_m_charm_sum->SetFillStyle(1001);

/// b bbar
  h_mmu_accept_lm_us_allMC_sum->Add(h_mmu_accept_lm_us_allMC_m_charm_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_lm_us_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_lm_us_allMC_sum->SetFillStyle(1001);




  h_mmu_accept_lm_us_allMC_sum->Draw("hist same");
  h_mmu_accept_lm_us_allMC_m_charm_sum->Draw("hist same");
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_ls_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_us_data->Draw("E P same");

  canv_1->RedrawAxis();

  TLatex *   tex2_1;
  tex2_1 = new TLatex(0.25,0.84,"+ -");
  tex2_1->SetNDC();

  tex2_1->SetTextColor(1);
  tex2_1->SetTextSize(0.1);
  tex2_1->SetLineWidth(2);
  tex2_1->Draw();

// cout<<"data Nvtx= "<<Get_sumof_hist("h_mmu_accept_lm_us_data", h_mmu_accept_lm_us_data, 0)<<endl;
// cout<<"MC Nvtx= "<<Get_sumof_hist("h_mmu_accept_lm_us_allMC_sum", h_mmu_accept_lm_us_allMC_sum, 0)<<endl;

  canv->cd();



if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Hm and Us : "<<endl;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_allMC_m_charm_sum->GetBinContent(i);}
cout<<" Charm  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_MC_c_p_lflbg_sum->GetBinContent(i);}
cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}

// cout<< " CHECK! = "<<h_mmu_accept_hm_us_data->GetBinContent(50)<<endl;

  TPad *canv_2 = new TPad("canv_2", "canv_2",0.50,0.50,1.0,0.99);
  canv_2->Draw();
  canv_2->cd();
  canv_2->Range(-3.09474,-280.175,10.5829,1586.15);

  h_mmu_accept_hm_us_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_hm_us_data->GetXaxis()->SetRangeUser(4,12.);
  h_mmu_accept_hm_us_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_hm_us_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_us_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_hm_us_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_us_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_hm_us_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_hm_us_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_hm_us_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_us_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_hm_us_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_us_data->GetYaxis()->SetLabelOffset(0.005);



  if(bigmarker)   h_mmu_accept_hm_us_data->SetMarkerSize(1.);
  else            h_mmu_accept_hm_us_data->SetMarkerSize(.65);
  h_mmu_accept_hm_us_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_hm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_mmu_accept_hm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_hm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_hm_us_MC_c_p_lflbg_sum->SetFillColor(12); 
  else            h_mmu_accept_hm_us_MC_c_p_lflbg_sum->SetFillColor(333); 
  h_mmu_accept_hm_us_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_mmu_accept_hm_us_allMC_m_charm_sum->Add(h_mmu_accept_hm_ls_allMC_m_charm_sum,-1.);
  h_mmu_accept_hm_us_allMC_m_charm_sum->Add(h_mmu_accept_hm_us_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_hm_us_allMC_m_charm_sum->SetFillColor(16); 
  else            h_mmu_accept_hm_us_allMC_m_charm_sum->SetFillColor(555); 
  h_mmu_accept_hm_us_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar
  h_mmu_accept_hm_us_allMC_sum->Add(h_mmu_accept_hm_us_allMC_m_charm_sum,1.);
  if(bg_black)    h_mmu_accept_hm_us_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_hm_us_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_hm_us_allMC_sum->SetFillStyle(1001);


  h_mmu_accept_hm_us_allMC_sum->Draw("hist same");
  h_mmu_accept_hm_us_allMC_m_charm_sum->Draw("hist same");
  h_mmu_accept_hm_us_MC_c_p_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_ls_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_us_data->Draw("E P same");
 
  leg2 = new TLegend(0.471383,0.626237,0.993777,0.90765,NULL,"brNDC");

  if(bg_black)  leg2->SetLineColor(1);
  else leg2->SetLineColor(4);
  leg2->SetLineStyle(1);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetLineWidth(1);
  leg2->SetBorderSize(0);
  leg2->AddEntry(h_mmu_accept_hm_us_data,"ZEUS data 03p-07p","pe");
  leg2->AddEntry(h_mmu_accept_hm_us_allMC_sum,"b#bar{b} MC","f");
  leg2->AddEntry(h_mmu_accept_hm_us_allMC_m_charm_sum,"J/#psi, #psi', #varUpsilon, BH MC","f");
  leg2->AddEntry(h_mmu_accept_hm_us_MC_c_p_lflbg_sum,"c#bar{c} MC","f");
  leg2->AddEntry(h_mmu_accept_hm_ls_MC_lflbg_sum,"lfl bg","f");
  leg2->Draw();

  canv_2->RedrawAxis();

  canv->cd();

if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Lm and Ls : "<<endl;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_ls_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_ls_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

// entries = 0.;
// for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_ls_allMC_m_charm_sum->GetBinContent(i);}
// cout<<" Charm  Ent =  "<<entries<<endl;

// entries = 0.;
// for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_ls_MC_c_p_lflbg_sum->GetBinContent(i);}
// cout<<" c cbar  Ent =  "<<entries<<endl;


entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_ls_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}




  TPad *canv_3 = new TPad("canv_3", "canv_3",0.0,0.0,0.50,0.49);
  canv_3->Draw();
  canv_3->cd();
  canv_3->Range(-3.09474,-280.175,10.5829,1586.15);
  h_mmu_accept_lm_ls_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_lm_ls_data->GetXaxis()->SetRangeUser(1.5,4.0);
  h_mmu_accept_lm_ls_data->GetXaxis()->SetNdivisions(505);
  h_mmu_accept_lm_ls_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_lm_ls_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_ls_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_lm_ls_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_ls_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_lm_ls_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_lm_ls_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_lm_ls_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_ls_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_lm_ls_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_ls_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_lm_ls_data->SetMarkerSize(1.);
  else            h_mmu_accept_lm_ls_data->SetMarkerSize(.65);
  h_mmu_accept_lm_ls_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_lm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_lm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_lm_ls_MC_lflbg_sum->SetFillStyle(1001);

/// bbbar
  h_mmu_accept_lm_ls_allMC_sum->Add(h_mmu_accept_lm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_lm_ls_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_lm_ls_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_lm_ls_allMC_sum->SetFillStyle(1001);


  h_mmu_accept_lm_ls_allMC_sum->Draw("hist same");
  h_mmu_accept_lm_ls_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_ls_data->Draw("E P same");

  canv_3->RedrawAxis();

  TLatex *   tex2_3;
  tex2_3 = new TLatex(0.25,0.84,"+ + / - -");
  tex2_3->SetNDC();

  tex2_3->SetTextColor(1);
  tex2_3->SetTextSize(0.1);
  tex2_3->SetLineWidth(2);
  tex2_3->Draw();

  canv->cd();


if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Hm and Ls : "<<endl;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_ls_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_ls_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

// entries = 0.;
// for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_ls_allMC_m_charm_sum->GetBinContent(i);}
// cout<<" Charm  Ent =  "<<entries<<endl;

// entries = 0.;
// for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_ls_MC_c_p_lflbg_sum->GetBinContent(i);}
// cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_ls_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;

cout<<" ******************************************************  " <<endl;
}

  TPad *canv_4 = new TPad("canv_4", "canv_4",0.50,0.0,1.0,0.49);
  canv_4->Draw();
  canv_4->cd();
  canv_4->Range(-3.09474,-280.175,10.5829,1586.15);
  h_mmu_accept_hm_ls_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_hm_ls_data->GetXaxis()->SetRangeUser(4,12.);
  h_mmu_accept_hm_ls_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_hm_ls_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_ls_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_hm_ls_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_ls_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_hm_ls_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_hm_ls_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_hm_ls_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_ls_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_hm_ls_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_ls_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_hm_ls_data->SetMarkerSize(1.);
  else            h_mmu_accept_hm_ls_data->SetMarkerSize(.65);
  h_mmu_accept_hm_ls_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_hm_ls_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_hm_ls_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_hm_ls_MC_lflbg_sum->SetFillStyle(1001);


/// bbbar
  h_mmu_accept_hm_ls_allMC_sum->Add(h_mmu_accept_hm_ls_MC_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_hm_ls_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_hm_ls_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_hm_ls_allMC_sum->SetFillStyle(1001);

  h_mmu_accept_hm_ls_allMC_sum->Draw("hist same");
  h_mmu_accept_hm_ls_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_ls_data->Draw("E P same");

  canv_4->RedrawAxis();

  canv->cd();

// Draw Histo Title 


if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Is Lm and Us : "<<endl;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_is_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_is_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_is_allMC_m_charm_sum->GetBinContent(i);}
cout<<" Charm  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->GetBinContent(i);}
cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_is_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}

// new Canvas for nis and is (seperate, us only) mass ranges
///  isolated and non isolated parts: 


  TCanvas * canv2 = new TCanvas("canv2","canv2",1005,955);

  TPad *canv2_1 = new TPad("canv2_1", "canv2_1",0.0,0.50,0.50,0.99);
  canv2_1->Draw();
  canv2_1->cd();
  canv2_1->Range(-3.09474,-280.175,10.5829,1586.15);

  h_mmu_accept_lm_us_is_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_lm_us_is_data->GetXaxis()->SetRangeUser(1.5,4.0);
  h_mmu_accept_lm_us_is_data->GetXaxis()->SetNdivisions(505);
  h_mmu_accept_lm_us_is_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_lm_us_is_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_us_is_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_lm_us_is_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_us_is_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_lm_us_is_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_lm_us_is_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_lm_us_is_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_us_is_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_lm_us_is_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_us_is_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_lm_us_is_data->SetMarkerSize(1.);
  else            h_mmu_accept_lm_us_is_data->SetMarkerSize(.65);
  h_mmu_accept_lm_us_is_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_lm_ls_is_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_lm_ls_is_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_lm_ls_is_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_is_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_is_MC_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->SetFillColor(12); 
  else            h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->SetFillColor(333); 
  h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_mmu_accept_lm_us_is_allMC_m_charm_sum->Add(h_mmu_accept_lm_ls_is_allMC_m_charm_sum,-1.);

Double_t Data_int =0.; 
Double_t Charm_int =0.; 
Double_t Beauty_int=0.; 


for (Int_t i=27;i<=39;i++) {Data_int = Data_int + h_mmu_accept_lm_us_is_data->GetBinContent(i);} //(2.8 - 3.4) bins [27;39]
for (Int_t i=27;i<=39;i++) {Charm_int = Charm_int + h_mmu_accept_lm_us_is_allMC_m_charm_sum->GetBinContent(i);} //(2.8 - 3.4) bins [27;39]
for (Int_t i=27;i<=39;i++) {Beauty_int = Beauty_int + h_mmu_accept_lm_us_is_allMC_sum->GetBinContent(i);} //(2.8 - 3.4) bins [27;39]


cout<<" Data int = "<<Data_int<<"	Beauty int "<<Beauty_int<<"	Charm int "<<Charm_int<<endl;


  h_mmu_accept_lm_us_is_allMC_m_charm_sum->Add(h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_is_allMC_m_charm_sum->SetFillColor(16); 
  else            h_mmu_accept_lm_us_is_allMC_m_charm_sum->SetFillColor(555); 
  h_mmu_accept_lm_us_is_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar


  h_mmu_accept_lm_us_is_allMC_sum->Add(h_mmu_accept_lm_us_is_allMC_m_charm_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_is_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_lm_us_is_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_lm_us_is_allMC_sum->SetFillStyle(1001);




  h_mmu_accept_lm_us_is_allMC_sum->Draw("hist same");
  h_mmu_accept_lm_us_is_allMC_m_charm_sum->Draw("hist same");
  h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_ls_is_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_us_is_data->Draw("E P same");

  canv2_1->RedrawAxis();

  TLatex *   tex5_1;

  tex5_1 = new TLatex(0.25,0.87,"isolated +-");
  tex5_1->SetNDC();

  tex5_1->SetTextColor(1);
  tex5_1->SetTextSize(0.05);
  tex5_1->SetLineWidth(2);
  tex5_1->Draw();

  canv2->cd();

if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Is Hm and Us : "<<endl;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_is_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_is_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_is_allMC_m_charm_sum->GetBinContent(i);}
cout<<" Charm  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->GetBinContent(i);}
cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_is_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}



  TPad *canv2_2 = new TPad("canv2_2", "canv2_2",0.50,0.50,1.0,0.99);
  canv2_2->Draw();
  canv2_2->cd();
  canv2_2->Range(-3.09474,-280.175,10.5829,1586.15);

  h_mmu_accept_hm_us_is_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_hm_us_is_data->GetXaxis()->SetRangeUser(4,12.);
  h_mmu_accept_hm_us_is_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_hm_us_is_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_us_is_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_hm_us_is_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_us_is_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_hm_us_is_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_hm_us_is_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_hm_us_is_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_us_is_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_hm_us_is_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_us_is_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_hm_us_is_data->SetMarkerSize(1.);
  else            h_mmu_accept_hm_us_is_data->SetMarkerSize(.65);
  h_mmu_accept_hm_us_is_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_hm_ls_is_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_hm_ls_is_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_hm_ls_is_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_is_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_is_MC_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->SetFillColor(12); 
  else            h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->SetFillColor(333); 
  h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_mmu_accept_hm_us_is_allMC_m_charm_sum->Add(h_mmu_accept_hm_ls_is_allMC_m_charm_sum,-1.);
  h_mmu_accept_hm_us_is_allMC_m_charm_sum->Add(h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_hm_us_is_allMC_m_charm_sum->SetFillColor(16); 
  else            h_mmu_accept_hm_us_is_allMC_m_charm_sum->SetFillColor(555); 
  h_mmu_accept_hm_us_is_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar
  h_mmu_accept_hm_us_is_allMC_sum->Add(h_mmu_accept_hm_us_is_allMC_m_charm_sum,1.);
  if(bg_black)    h_mmu_accept_hm_us_is_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_hm_us_is_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_hm_us_is_allMC_sum->SetFillStyle(1001);


  h_mmu_accept_hm_us_is_allMC_sum->Draw("hist same");
  h_mmu_accept_hm_us_is_allMC_m_charm_sum->Draw("hist same");
  h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_ls_is_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_us_is_data->Draw("E P same");

  leg5 = new TLegend(0.471383,0.626237,0.993777,0.90765,NULL,"brNDC");
  if(bg_black)  leg5->SetLineColor(1);
  else leg5->SetLineColor(4);
  leg5->SetLineStyle(1);
  leg5->SetFillStyle(0);
  leg5->SetFillColor(0);
  leg5->SetLineWidth(1);
  leg5->SetBorderSize(0);
  leg5->AddEntry(h_mmu_accept_hm_us_is_data,"ZEUS data 03p-07p","pe");
  leg5->AddEntry(h_mmu_accept_hm_us_is_allMC_sum,"b#bar{b} MC","f");
  leg5->AddEntry(h_mmu_accept_hm_us_is_allMC_m_charm_sum,"J/#psi, #psi', #varUpsilon, BH MC","f");
  leg5->AddEntry(h_mmu_accept_hm_us_is_MC_c_p_lflbg_sum,"c#bar{c} MC","f");
  leg5->AddEntry(h_mmu_accept_hm_ls_is_MC_lflbg_sum,"lfl bg","f");
  leg5->Draw();

  canv2_2->RedrawAxis();

  canv2->cd();

if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Nis Lm and Us : "<<endl;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_nis_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_nis_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_nis_allMC_m_charm_sum->GetBinContent(i);}
cout<<" Charm  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->GetBinContent(i);}
cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=50;i++) {entries = entries + h_mmu_accept_lm_us_nis_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}


  TPad *canv2_3 = new TPad("canv2_3", "canv2_3",0.0,0.0,0.50,0.49);
  canv2_3->Draw();
  canv2_3->cd();
  canv2_3->Range(-3.09474,-280.175,10.5829,1586.15);

  h_mmu_accept_lm_us_nis_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetRangeUser(1.5,4.0);
  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetNdivisions(505);
  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_us_nis_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_mmu_accept_lm_us_nis_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_lm_us_nis_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_lm_us_nis_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_lm_us_nis_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_lm_us_nis_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_lm_us_nis_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_lm_us_nis_data->SetMarkerSize(1.);
  else            h_mmu_accept_lm_us_nis_data->SetMarkerSize(.65);
  h_mmu_accept_lm_us_nis_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_lm_ls_nis_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_lm_ls_nis_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_lm_ls_nis_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_nis_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_nis_MC_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->SetFillColor(12); 
  else            h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->SetFillColor(333); 
  h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_mmu_accept_lm_us_nis_allMC_m_charm_sum->Add(h_mmu_accept_lm_ls_nis_allMC_m_charm_sum,-1.);
  h_mmu_accept_lm_us_nis_allMC_m_charm_sum->Add(h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_nis_allMC_m_charm_sum->SetFillColor(16); 
  else            h_mmu_accept_lm_us_nis_allMC_m_charm_sum->SetFillColor(555); 
  h_mmu_accept_lm_us_nis_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar
  h_mmu_accept_lm_us_nis_allMC_sum->Add(h_mmu_accept_lm_us_nis_allMC_m_charm_sum,1.);
  if(bg_black)    h_mmu_accept_lm_us_nis_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_lm_us_nis_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_lm_us_nis_allMC_sum->SetFillStyle(1001);

  h_mmu_accept_lm_us_nis_allMC_sum->Draw("hist same");
  h_mmu_accept_lm_us_nis_allMC_m_charm_sum->Draw("hist same");
  h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_ls_nis_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_lm_us_nis_data->Draw("E P same");

  canv2_3->RedrawAxis();

  TLatex *   tex5_3;
  tex5_3 = new TLatex(0.25,0.87,"non-isolated +-");
  tex5_3->SetNDC();

  tex5_3->SetTextColor(1);
  tex5_3->SetTextSize(0.05);
  tex5_3->SetLineWidth(2);
  tex5_3->Draw();

  canv2->cd();

if (check_Nevents) { 
Double_t entries = 0.;

cout<<endl<<" Nis Hm and Us : "<<endl;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_nis_data->GetBinContent(i);}
cout<<" DATA Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_nis_allMC_sum->GetBinContent(i);}
cout<<" b bbar Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_nis_allMC_m_charm_sum->GetBinContent(i);}
cout<<" Charm  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->GetBinContent(i);}
cout<<" c cbar  Ent =  "<<entries<<endl;

entries = 0.;
for (Int_t i=1;i<=84;i++) {entries = entries + h_mmu_accept_hm_us_nis_MC_lflbg_sum->GetBinContent(i);}
cout<<" lfl bg Ent =  "<<entries<<endl;
}


  TPad *canv2_4 = new TPad("canv2_4", "canv2_4",0.50,0.0,1.0,0.49);
  canv2_4->Draw();
  canv2_4->cd();
  canv2_4->Range(-3.09474,-280.175,10.5829,1586.15);

  h_mmu_accept_hm_us_nis_data->SetMarkerStyle(8);

// format X axis

  h_mmu_accept_hm_us_nis_data->GetXaxis()->SetRangeUser(4,12.);
  h_mmu_accept_hm_us_nis_data->GetXaxis()->SetTitle("m_{inv}^{#mu#mu} [GeV]");
  h_mmu_accept_hm_us_nis_data->GetXaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_us_nis_data->GetXaxis()->SetTitleOffset(0.8);
  h_mmu_accept_hm_us_nis_data->GetXaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_us_nis_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis
 
  h_mmu_accept_hm_us_nis_data->GetYaxis()->SetRangeUser(0.,1000.);
  h_mmu_accept_hm_us_nis_data->GetYaxis()->SetTitle("Events");
  h_mmu_accept_hm_us_nis_data->GetYaxis()->SetTitleSize(0.07);
  h_mmu_accept_hm_us_nis_data->GetYaxis()->SetTitleOffset(1.4);
  h_mmu_accept_hm_us_nis_data->GetYaxis()->SetLabelSize(0.06);
  h_mmu_accept_hm_us_nis_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_mmu_accept_hm_us_nis_data->SetMarkerSize(1.);
  else            h_mmu_accept_hm_us_nis_data->SetMarkerSize(.65);
  h_mmu_accept_hm_us_nis_data->Draw("E P");

/// lfl
  if(bg_black)    h_mmu_accept_hm_ls_nis_MC_lflbg_sum->SetFillColor(19); 
  else            h_mmu_accept_hm_ls_nis_MC_lflbg_sum->SetFillColor(444); 
  h_mmu_accept_hm_ls_nis_MC_lflbg_sum->SetFillStyle(1001);

/// c ccbar
  h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_nis_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_nis_MC_lflbg_sum,1.);

  if(bg_black)    h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->SetFillColor(12); 
  else            h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->SetFillColor(333); 
  h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->SetFillStyle(1001);

/// Jpsi ...
  h_mmu_accept_hm_us_nis_allMC_m_charm_sum->Add(h_mmu_accept_hm_ls_nis_allMC_m_charm_sum,-1.);
  h_mmu_accept_hm_us_nis_allMC_m_charm_sum->Add(h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum,1.);

  if(bg_black)    h_mmu_accept_hm_us_nis_allMC_m_charm_sum->SetFillColor(16); 
  else            h_mmu_accept_hm_us_nis_allMC_m_charm_sum->SetFillColor(555); 
  h_mmu_accept_hm_us_nis_allMC_m_charm_sum->SetFillStyle(1001);

/// bbbar

  h_mmu_accept_hm_us_nis_allMC_sum->Add(h_mmu_accept_hm_us_nis_allMC_m_charm_sum,1.);

  if(bg_black)    h_mmu_accept_hm_us_nis_allMC_sum->SetFillColor(111); 
  else            h_mmu_accept_hm_us_nis_allMC_sum->SetFillColor(22222); 
  h_mmu_accept_hm_us_nis_allMC_sum->SetFillStyle(1001);

  h_mmu_accept_hm_us_nis_allMC_sum->Draw("hist same");
  h_mmu_accept_hm_us_nis_allMC_m_charm_sum->Draw("hist same");
  h_mmu_accept_hm_us_nis_MC_c_p_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_ls_nis_MC_lflbg_sum->Draw("hist same");
  h_mmu_accept_hm_us_nis_data->Draw("E P same");

  canv2_4->RedrawAxis();

  canv2->cd();

// Draw Histo Title 
/*
  TLatex *   tex5a;
  tex5a = new TLatex(0.485,0.9471,"ZEUS");
  tex5a->SetNDC();

  tex5a->SetTextSize(0.0448);
  tex5a->SetLineWidth(2);
  tex5a->Draw();
*/

//***************************************************************************
//*********************** Plotting Script ends here *************************
//***************************************************************************
//***************************************************************************
//*********************** Plotting Script ends here *************************
//***************************************************************************
//***************************************************************************
//*********************** Plotting Script ends here *************************
//***************************************************************************
/*
/// Checking scaling: 
/// lfl 
  h_mmu_accept_lm_ls_MC_lflbg_sum->Add(h_mmu_accept_hm_ls_MC_lflbg_sum,1.);
  h_mmu_accept_lm_ls_MC_lflbg_sum->Add(h_mmu_accept_lm_ls_MC_lflbg_sum,1.);
  h_mmu_accept_lm_ls_MC_lflbg_sum->Add(h_mmu_accept_lm_ls_MC_lflbg_sum,1.);


/// c cbar
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_us_MC_c_p_lflbg_sum,1.);
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_hm_ls_MC_c_p_lflbg_sum,-1.);
  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_MC_c_p_lflbg_sum,-1.);

  h_mmu_accept_lm_us_MC_c_p_lflbg_sum->Add(h_mmu_accept_lm_ls_MC_lflbg_sum,1.);


/// Jpsi ...
  h_mmu_accept_hm_us_allMC_m_charm_sum->Add(h_mmu_accept_lm_us_allMC_m_charm_sum,1.);
  h_mmu_accept_hm_us_allMC_m_charm_sum->Add(h_mmu_accept_lm_ls_allMC_m_charm_sum,-1.);
  h_mmu_accept_hm_us_allMC_m_charm_sum->Add(h_mmu_accept_hm_ls_allMC_m_charm_sum,-1.);

  h_mmu_accept_hm_us_allMC_m_charm_sum->Add(h_mmu_accept_lm_us_MC_c_p_lflbg_sum,1.);

/// b bbar
  h_mmu_accept_lm_us_allMC_sum->Add(h_mmu_accept_hm_us_allMC_sum,1.);
  h_mmu_accept_lm_us_allMC_sum->Add(h_mmu_accept_lm_ls_allMC_sum,1.);
  h_mmu_accept_lm_us_allMC_sum->Add(h_mmu_accept_hm_ls_allMC_sum,1.);

  h_mmu_accept_lm_us_allMC_sum->Add(h_mmu_accept_hm_us_allMC_m_charm_sum,1.);

  h_mmu_accept_hm_us_data->Add(h_mmu_accept_lm_us_data,1.);

cout<<"data Nvtx= "<<Get_sumof_hist("h_mmu_accept_hm_us_data", h_mmu_accept_hm_us_data, 0)<<endl;
cout<<"MC Nvtx= "<<Get_sumof_hist("h_mmu_accept_lm_us_allMC_sum", h_mmu_accept_lm_us_allMC_sum, 0)<<endl;
*/
 
}
