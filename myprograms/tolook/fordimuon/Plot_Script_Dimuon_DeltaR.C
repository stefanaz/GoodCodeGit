{
  TStyle *zeus_style = gInclude->ZEUSSetStyle();

  gROOT->SetStyle("zeus_pub");

  zeus_pub->SetPadRightMargin(0.048);
  zeus_pub->SetPadLeftMargin(0.196);
  zeus_pub->SetPadTopMargin(0.05);
  zeus_pub->SetPadBottomMargin(0.16);

  Bool_t bigmarker = false;
  Bool_t bg_black  = false;

  TColor * redish    = new TColor(22222, 255./255., 175./255., 155./255.);
  TColor * blueish   = new TColor(  444, 163./255., 167./255., 255./255.);
  TColor * yellowish = new TColor(  555, 255./255., 255./255., 160./255.);
  TColor * greenish  = new TColor(  333, 165./255., 255./255., 150./255.);
  TColor * blackish  = new TColor(  111, 168./255., 168./255., 168./255.);
  TColor * greyish   = new TColor(  666,  98./255.,  89./255., 102./255.);
  TColor * brownish  = new TColor(  777, 128./255.,  51./255.,  43./255.);

  TLegend* leg, leg2;
  TCanvas* canv = new TCanvas("canv","canv",1005,500);

  TPad *canv_1 = new TPad("canv_1", "canv_1",0.0,0.0,0.50,0.99);
  canv_1->Draw();
  canv_1->cd();
  canv_1->Range(-3.09474,-280.175,10.5829,1586.15);

//***********************************************************************
//****  non isolated high and low mass plots  ***************************
//***********************************************************************

TH1D* h_DR_accept_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_nis_data");
TH1D* h_DR_accept_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_nis_allMC_sum");
TH1D* h_DR_accept_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_nis_allMC_m_charm_sum");
TH1D* h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_DR_accept_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_nis_MC_lflbg_sum");
TH1D* h_DR_accept_lm_us_nis_MC_Instanton      = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_nis_MC_Instanton");

TH1D* h_DR_accept_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_nis_data");
TH1D* h_DR_accept_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_nis_allMC_sum");
TH1D* h_DR_accept_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_nis_allMC_m_charm_sum");
TH1D* h_DR_accept_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_DR_accept_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_nis_MC_lflbg_sum");
TH1D* h_DR_accept_hm_us_nis_MC_Instanton      = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_nis_MC_Instanton");

//***********************************************************************
//****  isolated high and low mass plots  *******************************
//***********************************************************************

TH1D* h_DR_accept_lm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_is_data");
TH1D* h_DR_accept_lm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_is_allMC_sum");
TH1D* h_DR_accept_lm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_is_allMC_m_charm_sum");
TH1D* h_DR_accept_lm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_is_MC_c_p_lflbg_sum");
TH1D* h_DR_accept_lm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_is_MC_lflbg_sum");
TH1D* h_DR_accept_lm_us_is_MC_Instanton       = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_is_MC_Instanton");

TH1D* h_DR_accept_hm_us_is_data               = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_is_data");
TH1D* h_DR_accept_hm_us_is_allMC_sum          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_is_allMC_sum");
TH1D* h_DR_accept_hm_us_is_allMC_m_charm_sum  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_is_allMC_m_charm_sum");
TH1D* h_DR_accept_hm_us_is_MC_c_p_lflbg_sum   = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_DR_accept_hm_us_is_MC_lflbg_sum       = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_is_MC_lflbg_sum");
TH1D* h_DR_accept_hm_us_is_MC_Instanton       = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_is_MC_Instanton");

//***********************************************************************
//****  isolated and non-isolated high and low mass plots  **************
//***********************************************************************;

TH1D* h_DR_accept_hm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_data");
TH1D* h_DR_accept_hm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_allMC_sum");
TH1D* h_DR_accept_hm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_allMC_m_charm_sum");
TH1D* h_DR_accept_hm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_MC_c_p_lflbg_sum");
TH1D* h_DR_accept_hm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_MC_lflbg_sum");
TH1D* h_DR_accept_hm_us_MC_Instanton          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_us_MC_Instanton");
TH1D* h_DR_accept_hm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_ls_data");
TH1D* h_DR_accept_hm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_ls_allMC_sum");
TH1D* h_DR_accept_hm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_ls_MC_lflbg_sum");
TH1D* h_DR_accept_hm_ls_MC_Instanton          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_hm_ls_MC_Instanton");

TH1D* h_DR_accept_lm_us_data                  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_data");
TH1D* h_DR_accept_lm_us_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_allMC_sum");
TH1D* h_DR_accept_lm_us_allMC_m_charm_sum     = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_allMC_m_charm_sum");
TH1D* h_DR_accept_lm_us_MC_c_p_lflbg_sum      = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_MC_c_p_lflbg_sum");
TH1D* h_DR_accept_lm_us_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_MC_lflbg_sum");
TH1D* h_DR_accept_lm_us_MC_Instanton          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_us_MC_Instanton");
TH1D* h_DR_accept_lm_ls_data                  = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_ls_data");
TH1D* h_DR_accept_lm_ls_allMC_sum             = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_ls_allMC_sum");
TH1D* h_DR_accept_lm_ls_MC_lflbg_sum          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_ls_MC_lflbg_sum");
TH1D* h_DR_accept_lm_ls_MC_Instanton          = (TH1D*) gInclude->ReadinHisto("h_DR_accept_lm_ls_MC_Instanton");

//***********************************************************************
//****  plotting the ZEUS style guys!  **********************************
//***********************************************************************


  h_DR_accept_lm_us_nis_data->SetMarkerStyle(8);

// format X axis

  h_DR_accept_lm_us_nis_data->GetXaxis()->SetRangeUser(0.0,4.25.);
  h_DR_accept_lm_us_nis_data->GetXaxis()->SetTitle("#Delta R^{#mu#mu}");
  h_DR_accept_lm_us_nis_data->GetXaxis()->SetTitleSize(0.07);
  h_DR_accept_lm_us_nis_data->GetXaxis()->SetTitleOffset(0.8);
  h_DR_accept_lm_us_nis_data->GetXaxis()->SetLabelSize(0.06);
  h_DR_accept_lm_us_nis_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_DR_accept_lm_us_nis_data->GetYaxis()->SetRangeUser(0.0,450.);
  h_DR_accept_lm_us_nis_data->GetYaxis()->SetTitle("Events");
  h_DR_accept_lm_us_nis_data->GetYaxis()->SetTitleSize(0.07);
  h_DR_accept_lm_us_nis_data->GetYaxis()->SetTitleOffset(1.4);
  h_DR_accept_lm_us_nis_data->GetYaxis()->SetLabelSize(0.06);
  h_DR_accept_lm_us_nis_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_DR_accept_lm_us_nis_data->SetMarkerSize(1.);
  else            h_DR_accept_lm_us_nis_data->SetMarkerSize(.7);
  h_DR_accept_lm_us_nis_data->Draw("P");

  if(bg_black)    h_DR_accept_lm_us_nis_allMC_sum->SetFillColor(111); 
  else            h_DR_accept_lm_us_nis_allMC_sum->SetFillColor(22222); 
  h_DR_accept_lm_us_nis_allMC_sum->SetFillStyle(1001);
  h_DR_accept_lm_us_nis_allMC_sum->Draw("hist same");

  if(bg_black)    h_DR_accept_lm_us_nis_allMC_m_charm_sum->SetFillColor(16);
  else            h_DR_accept_lm_us_nis_allMC_m_charm_sum->SetFillColor(555);
  h_DR_accept_lm_us_nis_allMC_m_charm_sum->SetFillStyle(1001);
  h_DR_accept_lm_us_nis_allMC_m_charm_sum->Draw("hist same");

  if(bg_black)    h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum->SetFillColor(333);
  h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum->SetFillStyle(1001);
  h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum->Draw("hist same");

  if(bg_black)    h_DR_accept_lm_us_nis_MC_lflbg_sum->SetFillColor(19); 
  else            h_DR_accept_lm_us_nis_MC_lflbg_sum->SetFillColor(444); 
  h_DR_accept_lm_us_nis_MC_lflbg_sum->SetFillStyle(1001);
  h_DR_accept_lm_us_nis_MC_lflbg_sum->Draw("hist same");

  h_DR_accept_lm_us_nis_MC_Instanton->SetFillColor(13); 
  h_DR_accept_lm_us_nis_MC_Instanton->SetFillStyle(1001);
  h_DR_accept_lm_us_nis_MC_Instanton->Draw("hist same");


//Draw data again as top layer

  h_DR_accept_lm_us_nis_data->Draw("P same");
/*
  TLatex *   tex5_3;
  TLatex* tex5_4;
  tex5_3 = new TLatex(0.25,0.87,"non-isolated +-");
  tex5_4 = new TLatex(0.25,0.8,"low-mass");
  tex5_3->SetNDC();
  tex5_4->SetNDC();

  tex5_3->SetTextColor(1);
  tex5_3->SetTextSize(0.05);
  tex5_3->SetLineWidth(2);
  tex5_3->Draw();

  tex5_4->SetTextColor(1);
  tex5_4->SetTextSize(0.05);
  tex5_4->SetLineWidth(2);
  tex5_4->Draw();
*/
  leg = new TLegend(0.472996,0.676062,0.992885,0.909351,NULL,"brNDC");
  if(bg_black)  leg->SetLineColor(1);
  else leg->SetLineColor(4);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  leg->AddEntry(h_DR_accept_lm_us_nis_data,"ZEUS data 03p-07p","pe");
  leg->AddEntry(h_DR_accept_lm_us_nis_allMC_sum,"b#bar{b} MC","f");
  leg->AddEntry(h_DR_accept_lm_us_nis_allMC_m_charm_sum,"J/#psi, #psi', #varUpsilon, BH MC","f");
  leg->AddEntry(h_DR_accept_lm_us_nis_MC_c_p_lflbg_sum,"c#bar{c} MC","f");
  leg->AddEntry(h_DR_accept_lm_us_nis_MC_lflbg_sum,"lfl bg","f");
  leg->AddEntry(h_DR_accept_lm_us_nis_MC_Instanton,"QCDINS MC","f");
  leg->Draw();

//Draw data again as top layer

  canv_1->RedrawAxis();

  canv->cd();

  canv_2 = new TPad("canv_2", "canv_2",0.50,0.0,1.0,0.99);
  canv_2->Draw();
  canv_2->cd();
  canv_2->Range(-3.86269,-150.588,3.62985,830.588);

  h_DR_accept_hm_us_nis_data->SetMarkerStyle(8);

// format X axis

  h_DR_accept_hm_us_nis_data->GetXaxis()->SetRangeUser(0.,4.25.);
  h_DR_accept_hm_us_nis_data->GetXaxis()->SetTitle("#Delta R^{#mu#mu}");
  h_DR_accept_hm_us_nis_data->GetXaxis()->SetTitleSize(0.07);
  h_DR_accept_hm_us_nis_data->GetXaxis()->SetTitleOffset(0.8);
  h_DR_accept_hm_us_nis_data->GetXaxis()->SetLabelSize(0.06);
  h_DR_accept_hm_us_nis_data->GetXaxis()->SetLabelOffset(0.005);

// format Y axis

  h_DR_accept_hm_us_nis_data->GetYaxis()->SetRangeUser(0.0,450.);
  h_DR_accept_hm_us_nis_data->GetYaxis()->SetTitle("Events");
  h_DR_accept_hm_us_nis_data->GetYaxis()->SetTitleSize(0.07);
  h_DR_accept_hm_us_nis_data->GetYaxis()->SetTitleOffset(1.4);
  h_DR_accept_hm_us_nis_data->GetYaxis()->SetLabelSize(0.06);
  h_DR_accept_hm_us_nis_data->GetYaxis()->SetLabelOffset(0.005);

  if(bigmarker)   h_DR_accept_hm_us_nis_data->SetMarkerSize(1.);
  else            h_DR_accept_hm_us_nis_data->SetMarkerSize(.7);
  h_DR_accept_hm_us_nis_data->Draw("P");

  if(bg_black)    h_DR_accept_hm_us_nis_allMC_sum->SetFillColor(111); 
  else            h_DR_accept_hm_us_nis_allMC_sum->SetFillColor(22222); 
  h_DR_accept_hm_us_nis_allMC_sum->SetFillStyle(1001);
  h_DR_accept_hm_us_nis_allMC_sum->Draw("hist same");

  if(bg_black)    h_DR_accept_hm_us_nis_allMC_m_charm_sum->SetFillColor(16);
  else            h_DR_accept_hm_us_nis_allMC_m_charm_sum->SetFillColor(555);
  h_DR_accept_hm_us_nis_allMC_m_charm_sum->SetFillStyle(1001);
  h_DR_accept_hm_us_nis_allMC_m_charm_sum->Draw("hist same");

  if(bg_black)    h_DR_accept_hm_us_nis_MC_c_p_lflbg_sum->SetFillColor(12);
  else            h_DR_accept_hm_us_nis_MC_c_p_lflbg_sum->SetFillColor(333);
  h_DR_accept_hm_us_nis_MC_c_p_lflbg_sum->SetFillStyle(1001);
  h_DR_accept_hm_us_nis_MC_c_p_lflbg_sum->Draw("hist same");

  if(bg_black)    h_DR_accept_hm_us_nis_MC_lflbg_sum->SetFillColor(19); 
  else            h_DR_accept_hm_us_nis_MC_lflbg_sum->SetFillColor(444); 
  h_DR_accept_hm_us_nis_MC_lflbg_sum->SetFillStyle(1001);
  h_DR_accept_hm_us_nis_MC_lflbg_sum->Draw("hist same");

  h_DR_accept_hm_us_nis_MC_Instanton->SetFillColor(13); 
  h_DR_accept_hm_us_nis_MC_Instanton->SetFillStyle(1001);
  h_DR_accept_hm_us_nis_MC_Instanton->Draw("hist same");

//Draw data again as top layer

  h_DR_accept_hm_us_nis_data->Draw("P same");
/*
  TLatex *   tex5_3;
  tex5_3 = new TLatex(0.25,0.8,"high mass");
  tex5_3->SetNDC();

  tex5_3->SetTextColor(1);
  tex5_3->SetTextSize(0.05);
  tex5_3->SetLineWidth(2);
  tex5_3->Draw();
*/
  canv_2->RedrawAxis();

  canv->cd();

// Draw Histo Title 
/*
  TLatex *   tex2;
  tex2 = new TLatex(0.485,0.9,"ZEUS");
  tex2->SetNDC();

  tex2->SetTextSize(0.0847458);
  tex2->SetLineWidth(2);
  tex2->Draw();
*/
// Saving Histograms as Postscript

//  canv -> SaveAs("Plots/Dimuon_Pt_Eta.ps");

//***************************************************************************
//*********************** Plotting Script ends here *************************
//***************************************************************************
//***************************************************************************
//*********************** Plotting Script ends here *************************
//***************************************************************************
//***************************************************************************
//*********************** Plotting Script ends here *************************
//***************************************************************************

}
