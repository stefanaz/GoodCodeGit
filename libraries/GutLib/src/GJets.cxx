//
// GJets.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 07:28:56 $
// $Revision: 1.53 $
//

#include <GJets.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GJets)
#endif

GJets *gJets = 0;

//_____________________________________________________________
// GJets
// Jets Class for everything which is related only to JETs
//
//
GJets::GJets() : GPhysObj() {
  //
  // GJets default constructor
  if ( gDebug ) cout << endl << "GJets::GJets ctor called" << endl << endl;

  // initialize global pointer
  gJets = this;

  // initialize clonesarray
  fJets  = new TClonesArray("GJet",100);
  fNJets = 0;

  // initialize variables
  fIndex1                 = -99;
  fIndex2                 = -99;
  fXGammaJets             = -9999.99;
  fXGamma                 = -9999.99;
  fXGammaJets_zufo        = -9999.99;
  fMJets                  = -9999.99;
  fDPhiJets               = -9999.99;
  fDRJets                 = -9999.99;
  fPtJets                 = -9999.99;
  fCosThetaStarJets       = -9999.99;
  fEtaJets                = -9999.99;
  // initialize cut variables
  fPtACut                 = kFALSE;
  fPtBCut                 = kFALSE;

  // general histograms
  fGeneraln                   = 0;
  fGeneralE_A                 = 0;
  fGeneralE_B                 = 0;
  fGeneralPt_A                = 0;
  fGeneralPt_B                = 0;
  fGeneralEt_A                = 0;
  fGeneralEt_B                = 0;
  fGeneralEt_A_breit          = 0;
  fGeneralEt_B_breit          = 0;
  fGeneralEta_A               = 0;
  fGeneralEta_B               = 0;
  fGeneralEta_A_Large         = 0;
  fGeneralEta_B_Large         = 0;
  fGeneralPhi_A               = 0;
  fGeneralPhi_B               = 0;
  fGeneralXGamma              = 0;
  fGeneralXGamma_zufo         = 0;
  fGeneralXGamma2             = 0;
  fGeneralMJets               = 0;
  fGeneralDPhiJets            = 0;
  fGeneralPtJets              = 0;
  fGeneralMass_A              = 0;
  fGeneralMass_B              = 0;
  fGeneralMass_Matched        = 0;
  fGeneralMass_Unmatched      = 0;
  fGeneralPt_Matched          = 0;
  fGeneralPt_Unmatched        = 0;
  fGeneralEt_Matched          = 0;
  fGeneralEt_Unmatched        = 0;
  fGeneralEt_0_10_Matched     = 0;
  fGeneralEt_0_10_Unmatched   = 0;
  fGeneralEt_10_200_Matched   = 0;
  fGeneralEt_10_200_Unmatched = 0;
  fGeneralEt_200_Matched      = 0;
  fGeneralEt_200_Unmatched    = 0;
  fGeneralEt_0_10_Matched_breit     = 0;
  fGeneralEt_0_10_Unmatched_breit   = 0;
  fGeneralEt_10_200_Matched_breit   = 0;
  fGeneralEt_10_200_Unmatched_breit = 0;
  fGeneralEt_200_Matched_breit      = 0;
  fGeneralEt_200_Unmatched_breit    = 0;
  fGeneralEt_Matched_breit    = 0;
  fGeneralEt_Unmatched_breit  = 0;
  fGeneralEta_Matched         = 0;
  fGeneralEta_Unmatched       = 0;
  fGeneralEta_Matched_Large   = 0;
  fGeneralEta_Unmatched_Large = 0;
  fGeneralCostherastarXgamma  = 0;
  fGeneraln_uncut             = 0;
  fGeneralE_uncut             = 0;
  fGeneralPt_uncut            = 0;
  fGeneralEt_uncut            = 0;
  fGeneralEta_uncut           = 0;
  fGeneralPhi_uncut           = 0;
  fGeneralXGamma_uncut        = 0;
  fGeneralXGamma_zufo_uncut   = 0;
  fGeneralMass_uncut          = 0;

  fGeneralPtMinPtTrue         = 0;
  fGeneralPtVsPtTrue          = 0;
  fGeneralEtaMinEtaTrue       = 0;
  fGeneralEtaVsEtaTrue        = 0;
 
  fGeneralCrossMuonJetPt = 0;
  fGeneralCrossMuonJetPtRecNTrue = 0;

  fGeneralCrossMuonJetEta = 0;
  fGeneralCrossMuonJetEtaRecNTrue = 0;

  fGeneralCrossMuonJetPtFine = 0;
  fGeneralCrossMuonJetPtFineRecNTrue = 0;

  fGeneralCrossMuonJetEtaFine = 0;
  fGeneralCrossMuonJetEtaFineRecNTrue = 0;

  fGeneralCrossJetXGamma = 0;
  fGeneralCrossJetXGammaRecNTrue = 0;

  fGeneralCrossJetXGammaFine = 0;
  fGeneralCrossJetXGammaFineRecNTrue = 0;

  fGeneralCrossJetMJets = 0;
  fGeneralCrossJetMJetsRecNTrue = 0;
  fGeneralCrossJetMJetsLow = 0;
  fGeneralCrossJetMJetsLowRecNTrue = 0;
  fGeneralCrossJetMJetsHigh = 0;
  fGeneralCrossJetMJetsHighRecNTrue = 0;

  fGeneralCrossJetDPhiJets = 0;
  fGeneralCrossJetDPhiJetsRecNTrue = 0;
  fGeneralCrossJetDPhiJetsLow = 0;
  fGeneralCrossJetDPhiJetsLowRecNTrue = 0;
  fGeneralCrossJetDPhiJetsHigh = 0;
  fGeneralCrossJetDPhiJetsHighRecNTrue = 0;

  fGeneralCrossJetDRJets = 0;
  fGeneralCrossJetDRJetsRecNTrue = 0;
  fGeneralCrossJetDRJetsLow = 0;
  fGeneralCrossJetDRJetsLowRecNTrue = 0;
  fGeneralCrossJetDRJetsHigh = 0;
  fGeneralCrossJetDRJetsHighRecNTrue = 0;

  fGeneralCrossJetPtJets = 0;
  fGeneralCrossJetPtJetsRecNTrue = 0;
  fGeneralCrossJetPtJetsLow = 0;
  fGeneralCrossJetPtJetsLowRecNTrue = 0;
  fGeneralCrossJetPtJetsHigh = 0;
  fGeneralCrossJetPtJetsHighRecNTrue = 0;

  fGeneralCrossJetCosThetaStarJets = 0;
  fGeneralCrossJetCosThetaStarJetsRecNTrue = 0;
  fGeneralCrossJetCosThetaStarJetsLow = 0;
  fGeneralCrossJetCosThetaStarJetsLowRecNTrue = 0;
  fGeneralCrossJetCosThetaStarJetsHigh = 0;
  fGeneralCrossJetCosThetaStarJetsHighRecNTrue = 0;

  // control plots

  fControlPt_uncut            = 0;
  fControlEta_uncut           = 0;
  fControlPtA                 = 0;
  fControlPtB                 = 0;
  fControlEtaA                = 0;
  fControlEtaB                = 0;

  // generate histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GJets::~GJets() {
  //
  // GJets default destructor
  if ( gDebug ) cout << endl << "GJets::~GJets dtor called" << endl << endl;

  fJets->Delete();
  fNJets = 0;
  delete fJets;


}

//_____________________________________________________________

Bool_t GJets::CreateGeneral() {
  //
  // create general histograms for jets
  if ( gDebug ) cout << endl << "GJets::CreateGeneral() called" << endl << endl;

  // create general histograms

  if ( gCards->GetJETGeneral() ) {

    Int_t    ebins = 40;
    Double_t elow  = 0.;
    Double_t ehigh = 40.;
    Int_t    ptbins = 35;
    Double_t ptlow  = 5.;
    Double_t pthigh = 40.;
    Int_t    ptminbins = 50;
    Double_t ptminlow  = -1.;
    Double_t ptminhigh = 1.;
    Int_t    etbins = 60;
    Double_t etlow  = 0.;
    Double_t ethigh = 60.;
    Int_t    etbreitbins = 60;
    Double_t etbreitlow  = 0.;
    Double_t etbreithigh = 30.;
    Int_t    etabins = 23;
    Double_t etalow  = -2.0;
    Double_t etahigh = 2.6;
    Int_t    etalargebins = 40;
    Double_t etalargelow  = -4.0;
    Double_t etalargehigh = 4.0;
    Int_t    phibins = 20;
    Double_t philow  = -TMath::Pi();
    Double_t phihigh = TMath::Pi();
    Int_t    xgammabins = 20;
    Double_t xgammalow  = 0.0;
    Double_t xgammahigh = 1.0;
    Int_t    massbins   = 20;
    Double_t masslow    = 0;
    Double_t masshigh   = 20.;

    Int_t    xgammafine_nbins = 7;
    Double_t *xgammafine_bins = new Double_t[xgammafine_nbins+1];
    xgammafine_bins[0] =  0.000;
    xgammafine_bins[1] =  0.125;
    xgammafine_bins[2] =  0.250;
    xgammafine_bins[3] =  0.375;;
    xgammafine_bins[4] =  0.500;;
    xgammafine_bins[5] =  0.625;;
    xgammafine_bins[6] =  0.750;;
    xgammafine_bins[7] =  1.000;;

    Int_t    mjets_nbins = 10;
    Double_t *mjets_bins = new Double_t[mjets_nbins+1];
    mjets_bins[0]  =  0.0;
    mjets_bins[1]  =  5.0;
    mjets_bins[2]  = 10.0;
    mjets_bins[3]  = 15.0;
    mjets_bins[4]  = 20.0;
    mjets_bins[5]  = 25.0;
    mjets_bins[6]  = 30.0;
    mjets_bins[7]  = 35.0;
    mjets_bins[8]  = 40.0;
    mjets_bins[9]  = 45.0;
    mjets_bins[10] = 50.0;

    Int_t    dphijets_nbins = 5;
    Double_t *dphijets_bins = new Double_t[dphijets_nbins+1];
    dphijets_bins[0]  = 0*TMath::Pi()/dphijets_nbins;
    dphijets_bins[1]  = 1*TMath::Pi()/dphijets_nbins;
    dphijets_bins[2]  = 2*TMath::Pi()/dphijets_nbins;
    dphijets_bins[3]  = 3*TMath::Pi()/dphijets_nbins;
    dphijets_bins[4]  = 4*TMath::Pi()/dphijets_nbins;
    dphijets_bins[5]  = 5*TMath::Pi()/dphijets_nbins;

    Int_t    ptjets_nbins = 6;
    Double_t *ptjets_bins = new Double_t[ptjets_nbins+1];
    ptjets_bins[0]  =  0.0;
    ptjets_bins[1]  =  3.0;
    ptjets_bins[2]  =  6.0;
    ptjets_bins[3]  =  9.0;
    ptjets_bins[4]  = 12.0;
    ptjets_bins[5]  = 15.0;
    ptjets_bins[6]  = 18.0;

    Int_t    crossmuonjetpt_nbins = 3;
    Double_t *crossmuonjetpt_bins = new Double_t[crossmuonjetpt_nbins+1];
    crossmuonjetpt_bins[0] =  6.0;
    crossmuonjetpt_bins[1] = 11.0;;
    crossmuonjetpt_bins[2] = 16.0;
    crossmuonjetpt_bins[3] = 30.0;

    Int_t    crossmuonjeteta_nbins = 4;
    Double_t *crossmuonjeteta_bins = new Double_t[crossmuonjeteta_nbins+1];
    crossmuonjeteta_bins[0] = -1.6;
    crossmuonjeteta_bins[1] = -0.6;
    crossmuonjeteta_bins[2] =  0.4;
    crossmuonjeteta_bins[3] =  1.4;
    crossmuonjeteta_bins[4] =  2.5;

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

    Int_t    crossmuonjetetafine_nbins = 8;
    Double_t *crossmuonjetetafine_bins = new Double_t[crossmuonjetetafine_nbins+1];

     crossmuonjetetafine_bins[0]  = -1.50;
     crossmuonjetetafine_bins[1]  = -1.00;
     crossmuonjetetafine_bins[2]  = -0.5;
     crossmuonjetetafine_bins[3]  = -0.0;
     crossmuonjetetafine_bins[4]  =  0.50;
     crossmuonjetetafine_bins[5]  =  1.0;
     crossmuonjetetafine_bins[6] =  1.5;
     crossmuonjetetafine_bins[7] =  2.0;
     crossmuonjetetafine_bins[8] =  2.50;

//     crossmuonjetetafine_bins[0]  = -2.00;
//     crossmuonjetetafine_bins[1]  = -1.25;
//     crossmuonjetetafine_bins[2]  = -1.00;
//     crossmuonjetetafine_bins[3]  = -0.75;
//     crossmuonjetetafine_bins[4]  = -0.50;
//     crossmuonjetetafine_bins[5]  = -0.25;
//     crossmuonjetetafine_bins[6] =  0.00;
//     crossmuonjetetafine_bins[7] =  0.25;
//     crossmuonjetetafine_bins[8] =  0.50;
//     crossmuonjetetafine_bins[9] =  0.75;
//     crossmuonjetetafine_bins[10] =  1.00;
//     crossmuonjetetafine_bins[11] =  1.25;
//     crossmuonjetetafine_bins[12] =  1.50;
//     crossmuonjetetafine_bins[13] =  1.75;
//     crossmuonjetetafine_bins[14] =  2.00;
//     crossmuonjetetafine_bins[15] =  2.50;

    Int_t    crossjetxgamma_nbins = 5;
    Double_t *crossjetxgamma_bins = new Double_t[crossjetxgamma_nbins+1];
    crossjetxgamma_bins[0] =  0.000;
    crossjetxgamma_bins[1] =  0.375;
    crossjetxgamma_bins[2] =  0.500;
    crossjetxgamma_bins[3] =  0.625;
    crossjetxgamma_bins[4] =  0.750;
    crossjetxgamma_bins[5] =  1.00;

    Int_t    crossjetxgammafine_nbins = 6;
    Double_t *crossjetxgammafine_bins = new Double_t[crossjetxgammafine_nbins+1];
    crossjetxgammafine_bins[0] =  0.000;
    crossjetxgammafine_bins[1] =  0.250;
    crossjetxgammafine_bins[2] =  0.375;;
    crossjetxgammafine_bins[3] =  0.500;;
    crossjetxgammafine_bins[4] =  0.625;;
    crossjetxgammafine_bins[5] =  0.750;;
    crossjetxgammafine_bins[6] =  1.000;;

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

    Int_t    crossjetdphijets_nbins = 6;
    Double_t *crossjetdphijets_bins = new Double_t[crossjetdphijets_nbins+1];
    crossjetdphijets_bins[0]  = 0*TMath::Pi();
    crossjetdphijets_bins[1]  = 12./24.*TMath::Pi();
    crossjetdphijets_bins[2]  = 16./24.*TMath::Pi();
    crossjetdphijets_bins[3]  = 19./24.*TMath::Pi();
    crossjetdphijets_bins[4]  = 21./24.*TMath::Pi();
    crossjetdphijets_bins[5]  = 23./24.*TMath::Pi();
    crossjetdphijets_bins[6]  = 24./24.*TMath::Pi();

    Int_t    crossjetdrjets_nbins = 5;
    Double_t *crossjetdrjets_bins = new Double_t[crossjetdrjets_nbins+1];
    crossjetdrjets_bins[0]  = 1.0;
    crossjetdrjets_bins[1]  = 2.0;
    crossjetdrjets_bins[2]  = 2.5;
    crossjetdrjets_bins[3]  = 3.0;
    crossjetdrjets_bins[4]  = 3.5;
    crossjetdrjets_bins[5]  = 5;

    Int_t    crossjetptjets_nbins = 5;
    Double_t *crossjetptjets_bins = new Double_t[crossjetptjets_nbins+1];
    crossjetptjets_bins[0]  =   0.0;
    crossjetptjets_bins[1]  =   9.0;
    crossjetptjets_bins[2]  =  36.0;
    crossjetptjets_bins[3]  =  81.0;
    crossjetptjets_bins[4]  = 144.0;
    crossjetptjets_bins[5]  = 324.0;

    Int_t    crossjetcosthetastarjets_nbins = 6;
    Double_t *crossjetcosthetastarjets_bins = new Double_t[crossjetcosthetastarjets_nbins+1];
    crossjetcosthetastarjets_bins[0]  = -0.83;
    crossjetcosthetastarjets_bins[1]  = -0.664;
    crossjetcosthetastarjets_bins[2]  = -0.332;
    crossjetcosthetastarjets_bins[3]  =  0.0;
    crossjetcosthetastarjets_bins[4]  =  0.332;
    crossjetcosthetastarjets_bins[5]  =  0.664;
    crossjetcosthetastarjets_bins[6]  =  0.83;

    fGeneralPtMinPtTrue = gHistogrammer->TH1DFactory("Jet","PtMinPtTrue","JET: (p_{T}-p_{T}^{true})/p_{T}^{true}",ptminbins,ptminlow,ptminhigh,"(p_{T}-p_{T}^{true})/p_{T}^{true}","Events");
    fGeneralPtVsPtTrue = gHistogrammer->TH2DFactory("Jet","PtVsPtTrue","JET: p_{T} vs. p_{T}^{true}",ptbins,ptlow,pthigh,ptbins,ptlow,pthigh,"p_{T}","p_{T}^{true}","Events");
    fGeneralEtaMinEtaTrue = gHistogrammer->TH1DFactory("Jet","EtaMinEtaTrue","JET: (#eta-#eta^{true})/#eta^{true}",ptminbins,ptminlow,ptminhigh,"(#eta-#eta^{true})/#eta^{true}","Events");
    fGeneralEtaVsEtaTrue = gHistogrammer->TH2DFactory("Jet","EtaVsEtaTrue","JET: #eta vs. #eta^{true}",etabins,etalow,etahigh,etabins,etalow,etahigh,"#eta","#eta^{true}","Events");

    fGeneraln = gHistogrammer->TH1DFactory("Jet","n","JET: n",10,0.,10.,"Jets","Events");
    fGeneralE_A = gHistogrammer->TH1DFactory("Jet","E_A","JET: E_{a}",ebins,elow,ehigh,"E_{a} [GeV]","Events");
    fGeneralE_B = gHistogrammer->TH1DFactory("Jet","E_B","JET: E_{b}",ebins,elow,ehigh,"E_{b} [GeV]","Events");
    fGeneralPt_A = gHistogrammer->TH1DFactory("Jet","Pt_A","JET: p_{a,t}",ptbins,ptlow,pthigh,"p_{a,t} [GeV]","Events");
    fGeneralPt_B = gHistogrammer->TH1DFactory("Jet","Pt_B","JET: p_{b,t}",ptbins,ptlow,pthigh,"p_{b,t} [GeV]","Events");
    fGeneralEt_A = gHistogrammer->TH1DFactory("Jet","Et_A","JET: E_{a,t}",etbins,etlow,ethigh,"E_{a,t} [GeV]","Events");
    fGeneralEt_B = gHistogrammer->TH1DFactory("Jet","Et_B","JET: E_{b,t}",etbins,etlow,ethigh,"E_{b,t} [GeV]","Events");
    fGeneralEt_A_breit = gHistogrammer->TH1DFactory("Jet","Et_A_breit","JET: E_{a,t}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{a,t} [GeV]","Events");
    fGeneralEt_B_breit = gHistogrammer->TH1DFactory("Jet","Et_B_breit","JET: E_{b,t}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{b,t} [GeV]","Events");
    fGeneralEta_A = gHistogrammer->TH1DFactory("Jet","Eta_A","JET: #eta_{a}",etabins,etalow,etahigh,"#eta_{a}","Events");
    fGeneralEta_B = gHistogrammer->TH1DFactory("Jet","Eta_B","JET: #eta_{b}",etabins,etalow,etahigh,"#eta_{b}","Events");
    fGeneralEta_A_Large = gHistogrammer->TH1DFactory("Jet","Eta_A_Large","JET: #eta_{a}",etalargebins,etalargelow,etalargehigh,"#eta_{a}","Events");
    fGeneralEta_B_Large = gHistogrammer->TH1DFactory("Jet","Eta_B_Large","JET: #eta_{b}",etalargebins,etalargelow,etalargehigh,"#eta_{b}","Events");
    fGeneralPhi_A = gHistogrammer->TH1DFactory("Jet","Phi_A","JET: #phi_{a}",phibins,philow,phihigh,"#phi_{a}","Events");
    fGeneralPhi_B = gHistogrammer->TH1DFactory("Jet","Phi_B","JET: #phi_{b}",phibins,philow,phihigh,"#phi_{b}","Events");
    fGeneralXGamma = gHistogrammer->TH1DFactory("Jet","XGamma","JET: x_{#gamma}^{jets}",xgammabins,xgammalow,xgammahigh,"x_{#gamma}^{jets}","Events");
    fGeneralXGamma_zufo = gHistogrammer->TH1DFactory("Jet","XGamma_zufo","JET: x_{#gamma}^{jets} with zufo prop.",xgammabins,xgammalow,xgammahigh,"x_{#gamma}^{jets}","Events");
  fGeneralCostherastarXgamma  = gHistogrammer->TH1DVarFactory("Jet","CosThetaStarXGamma_zufo","xgamma for mjmatchcosthetastar calc",xgammafine_nbins,xgammafine_bins,"x_{#gamma}^{jets}","Events");
    fGeneralXGamma2 = gHistogrammer->TH1DVarFactory("Jet","XGamma2","JET: x_{#gamma}",xgammafine_nbins,xgammafine_bins,"x_{#gamma}","Events");
    fGeneralMJets = gHistogrammer->TH1DVarFactory("Jet","MJets","JET: M_{jj}",mjets_nbins,mjets_bins,"M_{jj} [GeV]","Events");
    fGeneralDPhiJets = gHistogrammer->TH1DVarFactory("Jet","DPhiJets","JET: #Delta #phi _{jj}",dphijets_nbins,dphijets_bins,"#Delta #phi _{tt}","Events");
    fGeneralPtJets = gHistogrammer->TH1DVarFactory("Jet","PtJets","JET: p_{T,jj}^{2}",ptjets_nbins,ptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralMass_A = gHistogrammer->TH1DFactory("Jet","Mass_A","JET: mass_{jet,a}",massbins,masslow,masshigh,"mass_{jet,a}","Events");
    fGeneralMass_B = gHistogrammer->TH1DFactory("Jet","Mass_B","JET: mass_{jet,b}",massbins,masslow,masshigh,"mass_{jet,b}","Events");
    fGeneralMass_Matched = gHistogrammer->TH1DFactory("Jet","Mass_Matched","JET: mass_{#mu-jet}",massbins,masslow,masshigh,"mass_{#mu-jet}","Events");
    fGeneralMass_Unmatched = gHistogrammer->TH1DFactory("Jet","Mass_Unmatched","JET: mass_{other-jet}",massbins,masslow,masshigh,"mass_{other-jet}","Events");
    fGeneralPt_Matched = gHistogrammer->TH1DFactory("Jet","Pt_Matched","JET: p_{t,#mu-jet}",ptbins,ptlow,pthigh,"p_{t,#mu-jet} [GeV]","Events");
    fGeneralEt_Matched = gHistogrammer->TH1DFactory("Jet","Et_Matched","JET: E_{t,#mu-jet}",etbins,etlow,ethigh,"E_{t,#mu-jet} [GeV]","Events");
    fGeneralEt_Matched_breit = gHistogrammer->TH1DFactory("Jet","Et_Matched_breit","JET: E_{t,#mu-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,#mu-jet} [GeV]","Events");
    fGeneralEta_Matched = gHistogrammer->TH1DFactory("Jet","Eta_Matched","JET: #eta_{#mu-jet}",etabins,etalow,etahigh,"#eta_{#mu-jet}","Events");
    fGeneralPt_Unmatched = gHistogrammer->TH1DFactory("Jet","Pt_Unmatched","JET: p_{t,other-jet}",ptbins,ptlow,pthigh,"p_{t,other-jet} [GeV]","Events");
    fGeneralEt_Unmatched = gHistogrammer->TH1DFactory("Jet","Et_Unmatched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events");
    fGeneralEt_Unmatched_breit = gHistogrammer->TH1DFactory("Jet","Et_Unmatched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet} [GeV]","Events");

    
    fGeneralEt_0_10_Unmatched = gHistogrammer->TH1DFactory("Jet","Et_0_10_Unmatched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events"); 
    fGeneralEt_0_10_Matched  = gHistogrammer->TH1DFactory("Jet","Et_0_10_Matched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events");    
    fGeneralEt_10_200_Matched   = gHistogrammer->TH1DFactory("Jet","Et_10_200_Matched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events"); 
    fGeneralEt_10_200_Unmatched = gHistogrammer->TH1DFactory("Jet","Et_10_200_Unmatched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events"); 
    fGeneralEt_200_Matched      = gHistogrammer->TH1DFactory("Jet","Et_200_Matched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events"); 
    fGeneralEt_200_Unmatched    = gHistogrammer->TH1DFactory("Jet","Et_200_Unmatched","JET: E_{t,other-jet}",etbins,etlow,ethigh,"E_{t,other-jet} [GeV]","Events"); 
    fGeneralEt_0_10_Matched_breit     = gHistogrammer->TH1DFactory("Jet","Et_0_10_Matched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet}^{breit} [GeV]","Events"); 
    fGeneralEt_0_10_Unmatched_breit   = gHistogrammer->TH1DFactory("Jet","Et_0_10_Unmatched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet}^{breit} [GeV]","Events"); 
    fGeneralEt_10_200_Matched_breit   = gHistogrammer->TH1DFactory("Jet","Et_10_200_Matched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet}^{breit} [GeV]","Events"); 
    fGeneralEt_10_200_Unmatched_breit = gHistogrammer->TH1DFactory("Jet","Et_10_200_Unmatched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet}^{breit} [GeV]","Events"); 
    fGeneralEt_200_Matched_breit      = gHistogrammer->TH1DFactory("Jet","Et_200_Matched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet}^{breit} [GeV]","Events"); 
    fGeneralEt_200_Unmatched_breit    = gHistogrammer->TH1DFactory("Jet","Et_200_Unmatched_breit","JET: E_{t,other-jet}^{breit}",etbreitbins,etbreitlow,etbreithigh,"E_{t,other-jet}^{breit} [GeV]","Events"); 
  
    fGeneralEta_Unmatched = gHistogrammer->TH1DFactory("Jet","Eta_Unmatched","JET: #eta_{other-jet}",etabins,etalow,etahigh,"#eta_{other-jet}","Events");
    fGeneralEta_Matched_Large = gHistogrammer->TH1DFactory("Jet","Eta_Matched_Large","JET: #eta_{#mu-jet}",etalargebins,etalargelow,etalargehigh,"#eta_{#mu-jet}","Events");
    fGeneralEta_Unmatched_Large = gHistogrammer->TH1DFactory("Jet","Eta_Unmatched_Large","JET: #eta_{other-jet}",etalargebins,etalargelow,etalargehigh,"#eta_{other-jet}","Events");
    fGeneralPhi_Matched = gHistogrammer->TH1DFactory("Jet","Phi_Matched","JET: #phi_{#mu-jet}",phibins,philow,phihigh,"#phi_{#mu-jet}","Events");
    fGeneralPhi_Unmatched = gHistogrammer->TH1DFactory("Jet","Phi_Unmatched","JET: #phi_{other-jet}",phibins,philow,phihigh,"#phi_{other-jet}","Events");

    fGeneraln_uncut = gHistogrammer->TH1DFactory("Jet","n_uncut","uncut JET: n",10,0.,10.,"Jets","Events");
    fGeneralE_uncut = gHistogrammer->TH1DFactory("Jet","E_uncut","uncut JET: E",ebins,elow,ehigh,"E [GeV]","Events");
    fGeneralPt_uncut = gHistogrammer->TH1DFactory("Jet","Pt_uncut","uncut JET: p_{t}",ptbins,ptlow,pthigh,"p_{t} [GeV]","Events");
    fGeneralEt_uncut = gHistogrammer->TH1DFactory("Jet","Et_uncut","uncut JET: E_{t}",etbins,etlow,ethigh,"E_{t} [GeV]","Events");
    fGeneralEta_uncut = gHistogrammer->TH1DFactory("Jet","Eta_uncut","uncut JET: #eta",etalargebins,etalargelow,etalargehigh,"#eta","Events");
    fGeneralPhi_uncut = gHistogrammer->TH1DFactory("Jet","Phi_uncut","uncut JET: #phi",phibins,philow,phihigh,"#phi","Events");
    fGeneralXGamma_uncut = gHistogrammer->TH1DFactory("Jet","XGamma_uncut","uncut JET: x_{#gamma}^{jets}",xgammabins,xgammalow,xgammahigh,"x_{#gamma}^{jets}","Events");
    fGeneralXGamma_zufo_uncut = gHistogrammer->TH1DFactory("Jet","XGamma_zufo_uncut","uncut JET: x_{#gamma}^{jets} with zufo prop.",xgammabins,xgammalow,xgammahigh,"x_{#gamma}^{jets}","Events");
    fGeneralMass_uncut = gHistogrammer->TH1DFactory("Jet","Mass_uncut","uncut JET: mass_{jet}",massbins,masslow,masshigh,"mass_{jet}","Events");

    fGeneralCrossMuonJetPt = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetPt","p_{T}^{#mu-jet}",crossmuonjetpt_nbins,crossmuonjetpt_bins,"p_{T}^{#mu-jet} [GeV]","Events");
    fGeneralCrossMuonJetEta = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetEta","#eta^{#mu-jet}",crossmuonjeteta_nbins,crossmuonjeteta_bins,"#eta^{#mu-jet}","Events");
    fGeneralCrossMuonJetPtFine = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetPtFine","p_{T}^{#mu-jet}",crossmuonjetptfine_nbins,crossmuonjetptfine_bins,"p_{T}^{#mu-jet} [GeV]","Events");
    fGeneralCrossMuonJetEtaFine = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetEtaFine","#eta^{#mu-jet}",crossmuonjetetafine_nbins,crossmuonjetetafine_bins,"#eta^{#mu-jet}","Events");

    fGeneralCrossJetXGamma = gHistogrammer->TH1DVarFactory("Jet","CrossJetXGamma","x_{#gamma}",crossjetxgamma_nbins,crossjetxgamma_bins,"x_{#gamma}","Events");
    fGeneralCrossJetXGammaFine = gHistogrammer->TH1DVarFactory("Jet","CrossJetXGammaFine","x_{#gamma}",crossjetxgammafine_nbins,crossjetxgammafine_bins,"x_{#gamma}","Events");
    fGeneralCrossJetMJets = gHistogrammer->TH1DVarFactory("Jet","CrossJetMJets","M_{jj}",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJets = gHistogrammer->TH1DVarFactory("Jet","CrossJetDPhiJets","#Delta #phi _{jj}",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJets = gHistogrammer->TH1DVarFactory("Jet","CrossJetDRJets","#Delta R_{jj}",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJets = gHistogrammer->TH1DVarFactory("Jet","CrossJetPtJets","p_{T,jj}^{2}",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJets = gHistogrammer->TH1DVarFactory("Jet","CrossJetCosThetaStarJets","cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    // Low: x_gamma < 0.75
    fGeneralCrossJetMJetsLow = gHistogrammer->TH1DVarFactory("Jet","CrossJetMJetsLow","M_{jj} for x_{#gamma} < 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsLow = gHistogrammer->TH1DVarFactory("Jet","CrossJetDPhiJetsLow","#Delta #phi _{jj} for x_{#gamma} < 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsLow = gHistogrammer->TH1DVarFactory("Jet","CrossJetDRJetsLow","#Delta R_{jj} for x_{#gamma} < 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsLow = gHistogrammer->TH1DVarFactory("Jet","CrossJetPtJetsLow","p_{T,jj}^{2} for x_{#gamma} < 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsLow = gHistogrammer->TH1DVarFactory("Jet","CrossJetCosThetaStarJetsLow","cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");
    // High: x_gamma >= 0.75
    fGeneralCrossJetMJetsHigh = gHistogrammer->TH1DVarFactory("Jet","CrossJetMJetsHigh","M_{jj} for x_{#gamma} #geq 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
    fGeneralCrossJetDPhiJetsHigh = gHistogrammer->TH1DVarFactory("Jet","CrossJetDPhiJetsHigh","#Delta #phi _{jj} for x_{#gamma} #geq 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
    fGeneralCrossJetDRJetsHigh = gHistogrammer->TH1DVarFactory("Jet","CrossJetDRJetsHigh","#Delta R_{jj} for x_{#gamma} #geq 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
    fGeneralCrossJetPtJetsHigh = gHistogrammer->TH1DVarFactory("Jet","CrossJetPtJetsHigh","p_{T,jj}^{2} for x_{#gamma} #geq 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
    fGeneralCrossJetCosThetaStarJetsHigh = gHistogrammer->TH1DVarFactory("Jet","CrossJetCosThetaStarJetsHigh","cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");


    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      fGeneralCrossMuonJetPtRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetPtRecNTrue","rec. and true p_{T}^{#mu-jet}",crossmuonjetpt_nbins,crossmuonjetpt_bins,"p_{T}^{#mu-jet} [GeV]","Events");
      fGeneralCrossMuonJetEtaRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetEtaRecNTrue","rec. and true #eta^{#mu-jet}",crossmuonjeteta_nbins,crossmuonjeteta_bins,"#eta^{#mu-jet}","Events");
      fGeneralCrossMuonJetPtFineRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetPtFineRecNTrue","rec. and true p_{T}^{#mu-jet}",crossmuonjetptfine_nbins,crossmuonjetptfine_bins,"p_{T}^{#mu-jet} [GeV]","Events");
      fGeneralCrossMuonJetEtaFineRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossMuonJetEtaFineRecNTrue","rec. and true #eta^{#mu-jet}",crossmuonjetetafine_nbins,crossmuonjetetafine_bins,"#eta^{#mu-jet}","Events");
      
      fGeneralCrossJetXGammaRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetXGammaRecNTrue","rec. and true x_{#gamma}",crossjetxgamma_nbins,crossjetxgamma_bins,"x_{#gamma}","Events");
      fGeneralCrossJetXGammaFineRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetXGammaFineRecNTrue","rec. and true x_{#gamma}",crossjetxgammafine_nbins,crossjetxgammafine_bins,"x_{#gamma}","Events");
      fGeneralCrossJetMJetsRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetMJetsRecNTrue","rec. and true M_{jj}",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
      fGeneralCrossJetDPhiJetsRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetDPhiJetsRecNTrue","rec. and true #Delta #phi _{jj}",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
      fGeneralCrossJetDRJetsRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetDRJetsRecNTrue","rec. and true #Delta R_{jj}",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
      fGeneralCrossJetPtJetsRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetPtJetsRecNTrue","rec. and true p_{T,jj}^{2}",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
      fGeneralCrossJetCosThetaStarJetsRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetCosThetaStarJetsRecNTrue","rec. and true cos(#theta^{*})_{jj}",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

      // Low: x_gamma < 0.75
      fGeneralCrossJetMJetsLowRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetMJetsLowRecNTrue","rec. and true M_{jj} for x_{#gamma} < 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
      fGeneralCrossJetDPhiJetsLowRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetDPhiJetsLowRecNTrue","rec. and true #Delta #phi _{jj} for x_{#gamma} < 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
      fGeneralCrossJetDRJetsLowRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetDRJetsLowRecNTrue","rec. and true #Delta R_{jj} for x_{#gamma} < 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
      fGeneralCrossJetPtJetsLowRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetPtJetsLowRecNTrue","rec. and true p_{T,jj}^{2} for x_{#gamma} < 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
      fGeneralCrossJetCosThetaStarJetsLowRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetCosThetaStarJetsLowRecNTrue","rec. and true cos(#theta^{*})_{jj} for x_{#gamma} < 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

      // High: x_gamma < 0.75
      fGeneralCrossJetMJetsHighRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetMJetsHighRecNTrue","rec. and true M_{jj} for x_{#gamma} #geq 0.75",crossjetmjets_nbins,crossjetmjets_bins,"M_{jj} [GeV]","Events");
      fGeneralCrossJetDPhiJetsHighRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetDPhiJetsHighRecNTrue","rec. and true #Delta #phi _{jj} for x_{#gamma} #geq 0.75",crossjetdphijets_nbins,crossjetdphijets_bins,"#Delta #phi _{jj}","Events");
      fGeneralCrossJetDRJetsHighRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetDRJetsHighRecNTrue","rec. and true #Delta R_{jj} for x_{#gamma} #geq 0.75",crossjetdrjets_nbins,crossjetdrjets_bins,"#Delta R_{jj}","Events");
      fGeneralCrossJetPtJetsHighRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetPtJetsHighRecNTrue","rec. and true p_{T,jj}^{2} for x_{#gamma} #geq 0.75",crossjetptjets_nbins,crossjetptjets_bins,"p_{T,jj}^{2} [GeV]","Events");
      fGeneralCrossJetCosThetaStarJetsHighRecNTrue = gHistogrammer->TH1DVarFactory("Jet","CrossJetCosThetaStarJetsHighRecNTrue","rec. and true cos(#theta^{*})_{jj} for x_{#gamma} #geq 0.75",crossjetcosthetastarjets_nbins,crossjetcosthetastarjets_bins,"cos(#theta^{*})_{jj}","Events");

    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::FillGeneral() {
  //
  // fill general histograms for jets
  if ( gDebug ) cout << endl << "GJets::FillGeneral() called" << endl << endl;

  if ( gCards->GetJETGeneral() ) {

    fGeneraln_uncut->Fill(fNJets,gHeader->GetWeight());

    if ( ((gCards->GetJETNCut() >= 2) && fPtACut && fPtBCut)||((gCards->GetJETNCut() == 1) && fPtACut) )
      fGeneralXGamma_uncut->Fill(fXGammaJets,gHeader->GetWeight());
      fGeneralXGamma_zufo_uncut->Fill(fXGammaJets_zufo,gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {
      fGeneraln->Fill(fNJets,gHeader->GetWeight());
      fGeneralXGamma->Fill(fXGammaJets,gHeader->GetWeight());
      fGeneralXGamma_zufo->Fill(fXGammaJets_zufo,gHeader->GetWeight());
      fGeneralXGamma2->Fill(fXGamma,gHeader->GetWeight());
      fGeneralMJets->Fill(fMJets,gHeader->GetWeight());
      fGeneralDPhiJets->Fill(fDPhiJets,gHeader->GetWeight());
      fGeneralPtJets->Fill(fPtJets,gHeader->GetWeight());
      fGeneralCrossJetXGamma->Fill(fXGammaJets_zufo,gHeader->GetWeight());
      fGeneralCrossJetXGammaFine->Fill(fXGammaJets_zufo,gHeader->GetWeight());
      fGeneralCrossJetMJets->Fill(fMJets,gHeader->GetWeight());
      fGeneralCrossJetDPhiJets->Fill(fDPhiJets,gHeader->GetWeight());
      fGeneralCrossJetDRJets->Fill(fDRJets,gHeader->GetWeight());
      fGeneralCrossJetPtJets->Fill(fPtJets,gHeader->GetWeight());
      if((fMJets>0)&&(fEtaJets<99)) fGeneralCrossJetCosThetaStarJets->Fill(fCosThetaStarJets,gHeader->GetWeight());

      if ( fXGammaJets_zufo < 0.75 ) {
	fGeneralCrossJetMJetsLow->Fill(fMJets,gHeader->GetWeight());
	fGeneralCrossJetDPhiJetsLow->Fill(fDPhiJets,gHeader->GetWeight());
	fGeneralCrossJetDRJetsLow->Fill(fDRJets,gHeader->GetWeight());
	fGeneralCrossJetPtJetsLow->Fill(fPtJets,gHeader->GetWeight());
	if((fMJets>0)&&(fEtaJets<99))	fGeneralCrossJetCosThetaStarJetsLow->Fill(fCosThetaStarJets,gHeader->GetWeight());
	
      }

      if ( fXGammaJets_zufo >= 0.75 ) {
	fGeneralCrossJetMJetsHigh->Fill(fMJets,gHeader->GetWeight());
	fGeneralCrossJetDPhiJetsHigh->Fill(fDPhiJets,gHeader->GetWeight());
	fGeneralCrossJetDRJetsHigh->Fill(fDRJets,gHeader->GetWeight());
	fGeneralCrossJetPtJetsHigh->Fill(fPtJets,gHeader->GetWeight());
	 if((fMJets>0)&&(fEtaJets<99)) fGeneralCrossJetCosThetaStarJetsHigh->Fill(fCosThetaStarJets,gHeader->GetWeight());
      }

      if ( gCards->GetMC()  && !(gCards->GetMCLF() && gCards->GetDoFake())) {
	if ( gMCs->GetAllMCCuts() ) {
	  GJet *jet1 = GetJetWithID(fIndex1);
	  GJet *jet2 = GetJetWithID(fIndex2);
	  if ( (jet1!=0)&&(jet2!=0) ) {
	    if ( (jet1->GetAssociatedMCJet()!=0)&&(jet2->GetAssociatedMCJet()!=0) ) {
	      fGeneralCrossJetXGammaRecNTrue->Fill(fXGammaJets_zufo,gHeader->GetWeight());
	      fGeneralCrossJetXGammaFineRecNTrue->Fill(fXGammaJets_zufo,gHeader->GetWeight());
	      fGeneralCrossJetMJetsRecNTrue->Fill(fMJets,gHeader->GetWeight());
	      fGeneralCrossJetDPhiJetsRecNTrue->Fill(fDPhiJets,gHeader->GetWeight());
	      fGeneralCrossJetDRJetsRecNTrue->Fill(fDRJets,gHeader->GetWeight());
	      fGeneralCrossJetPtJetsRecNTrue->Fill(fPtJets,gHeader->GetWeight());
	     if((fMJets>0)&&(fEtaJets<99))  fGeneralCrossJetCosThetaStarJetsRecNTrue->Fill(fCosThetaStarJets,gHeader->GetWeight());

	      if ( fXGammaJets_zufo < 0.75 ) {
		fGeneralCrossJetMJetsLowRecNTrue->Fill(fMJets,gHeader->GetWeight());
		fGeneralCrossJetDPhiJetsLowRecNTrue->Fill(fDPhiJets,gHeader->GetWeight());
		fGeneralCrossJetDRJetsLowRecNTrue->Fill(fDRJets,gHeader->GetWeight());
		fGeneralCrossJetPtJetsLowRecNTrue->Fill(fPtJets,gHeader->GetWeight());
	 if((fMJets>0)&&(fEtaJets<99))	fGeneralCrossJetCosThetaStarJetsLowRecNTrue->Fill(fCosThetaStarJets,gHeader->GetWeight());
	      }

	      if ( fXGammaJets_zufo >= 0.75 ) {
		fGeneralCrossJetMJetsHighRecNTrue->Fill(fMJets,gHeader->GetWeight());
		fGeneralCrossJetDPhiJetsHighRecNTrue->Fill(fDPhiJets,gHeader->GetWeight());
		fGeneralCrossJetDRJetsHighRecNTrue->Fill(fDRJets,gHeader->GetWeight());
		fGeneralCrossJetPtJetsHighRecNTrue->Fill(fPtJets,gHeader->GetWeight());
	 if((fMJets>0)&&(fEtaJets<99)) fGeneralCrossJetCosThetaStarJetsHighRecNTrue->Fill(fCosThetaStarJets,gHeader->GetWeight());
	      }

	    }
	  }
	}
      }
    }
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::Do() {
  //
  // execute per event
  if ( gDebug ) cout << endl << "GJet::Do() called" << endl << endl;

  Fill();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::Reset() {
  //
  // reset variables on event by event basis
  if ( gDebug ) cout << endl << "GJets::Reset() called" << endl << endl;

  // reset clonesarray
  fJets->Clear();
  fNJets = 0;

  // reset variables
  fIndex1                 = -99;
  fIndex2                 = -99;
  fXGammaJets             = -9999.99;
  fXGamma                 = -9999.99;
  fXGammaJets_zufo        = -9999.99;
  fMJets                  = -9999.99;
  fDPhiJets               = -9999.99;
  fDRJets                 = -9999.99;
  fPtJets                 = -9999.99;
  fCosThetaStarJets       = -9999.99;

  // reset cut flags
  fPtACut = kFALSE;
  fPtBCut = kFALSE;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::GetAllCuts() {
  //
  // return kTRUE if event passes all jets cuts
  if ( gDebug ) cout << endl << "GJet::GetAllCuts() called" << endl << endl;

  if ( gCards->GetJETNCut() <= 0 )
    return kTRUE;
  else if ((gCards->GetJETNCut() == 1) && GetPtACut() ) {
    gLister->SetOutput(1);
    return kTRUE;
  }
  else if ( GetPtACut() && GetPtBCut() )
    return kTRUE;
  else
    return kFALSE;

}

//_____________________________________________________________

Bool_t GJets::CreateControl() {
  //
  // create control plots
  if ( gDebug ) cout << endl << "GJets::CreateControl() called" << endl << endl;

  if ( gCards->GetJETControl() ) {

    fControlPt_uncut             = gHistogrammer->TH1DFactory("Jet_Control","Pt_uncut","uncut Jet Control Plot: #p_{t}",80,0.,80.,"#p_{t}","Events");
    fControlEta_uncut            = gHistogrammer->TH1DFactory("Jet_Control","Eta_uncut","uncut Jet Control Plot: #eta",72,-3.6,3.6,"#eta","Events");

    fControlPtA                  = gHistogrammer->TH1DFactory("Jet_Control","PtA","Jet Control Plot: #p_{t,A}",80,0.,80.,"#p_{t,A}","Events");
    fControlPtB                  = gHistogrammer->TH1DFactory("Jet_Control","PtB","Jet Control Plot: #p_{t,B}",50,0.,50.,"#p_{t,B}","Events");
    fControlEtaA                 = gHistogrammer->TH1DFactory("Jet_Control","EtaA","Jet Control Plot: #eta_{A}",72,-3.6,3.6,"#eta_{A}","Events");
    fControlEtaB                 = gHistogrammer->TH1DFactory("Jet_Control","EtaB","Jet Control Plot: #eta_{B}",72,-3.6,3.6,"#eta_{B}","Events");

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::FillControl() {
  //
  // fill control plots
  if ( gDebug ) cout << endl << "GJets::FillControl() called" << endl << endl;

  if ( gCards->GetJETControl() ) {

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::Fill() {
  //
  // Fill jets
  if ( gDebug ) cout << endl << "GJets::Fill() called" << endl << endl;

  // attention, if gCards->GetJETCutOnEt() is true, pt is replaced by et

  TClonesArray &jets = *fJets;
    Double_t pt1 = -9999.99;
    Double_t pt2 = -9999.99;

  //decide which kt_jet finder (with or without electron/lab or breit frame)

  if (gSinistra->GetDISPHPCut() == 1){ //PhP
    gData->SetDISPHPJets(1);
  }
  if (gSinistra->GetDISPHPCut() == 2){ //DIS
    if (gCards->GetJETBreit()) gData->SetDISPHPJets(3); // Breitframe
    else gData->SetDISPHPJets(2); //Labframe
  }
  if ( gData->Getkt_njet_a() > 0 ) {
    
    for ( Int_t i = 0; i < gData->Getkt_njet_a(); i++ ) {
      // if mass is not valid ( < 0), set mass to zero
      GJet *jet = 0;
      if ( gData->Getkt_masjet_a(i) > 0 ){
	jet = new(jets[fNJets++]) GJet(i+1,gData->Getkt_etjet_a(i),gData->Getkt_etajet_a(i),gData->Getkt_phijet_a(i),gData->Getkt_masjet_a(i),gData->Getkt_etjetbreit(i));

}
      
      else{
	jet = new(jets[fNJets++]) GJet(i+1,gData->Getkt_etjet_a(i),gData->Getkt_etajet_a(i),gData->Getkt_phijet_a(i),0,gData->Getkt_etjetbreit(i));
    }
      if ( jet != 0 ) {
	// decide by card whether to cut on Et or Pt
	Double_t cutonvalue = 0;
	if ( gCards->GetJETCutOnEt() ) {
	  if ( gCards->GetJETBreit() ) {
	    cutonvalue = jet->GetEtbreit(); 
	  }
	  else {
	    cutonvalue = jet->Et();
	  }
	} else {
	  if ( gCards->GetJETBreit() ) {
	    cout << "ERROR GetJETBreit() and not GetJETCutOnEt!" << endl; 
	    cout << "use jet->Pt to cut on!" << endl; 
	  }
	  cutonvalue = jet->Pt();
	}
	if ( jet->GetEtaCut() && (cutonvalue > pt1) ) {
	  fIndex2 = fIndex1;
	  pt2 = pt1;
	  fIndex1 = jet->GetID();
	  pt1 = cutonvalue;
	} else if ( jet->GetEtaCut() && (cutonvalue > pt2) ) {
	  fIndex2 = jet->GetID();
	  pt2 = cutonvalue;
	}
      }
    }
  }

  // set types of first and second jet if jets fulfill cuts
  if ( pt1 >= gCards->GetJETPtACut() ) {
    GJet *jet = GetJetWithID(fIndex1);
    jet->SetType(kFirst);
    fPtACut = kTRUE;
  }
  if ( pt2 >= gCards->GetJETPtBCut() ) {
    GJet *jet = GetJetWithID(fIndex2);
    jet->SetType(kSecond);
    fPtBCut = kTRUE;
  }

  Calc(fIndex1,fIndex2);

  return kTRUE;
}

//_____________________________________________________________

Double_t GJets::GetE(Int_t index) {
  //
  // return energy of jet[index]
  if ( gDebug ) cout << endl << "GJets::GetE(Int_t index) called" << endl << endl;

  if ( index < fNJets ) {
    return ((GJet*)(fJets->At(index)))->E();
  } else {
    TString msg = "GJets::GetE index: ";
    msg += index;
    msg.Append(" larger than total number of jets: ");
    msg += fNJets;
    gLister->FillErrorList(msg.Data());
    return -99.;
  }

}

//_____________________________________________________________

Double_t GJets::GetPt(Int_t index) {
  //
  // return transverse momentum of jet[index]
  if ( gDebug ) cout << endl << "GJets::GetPt(Int_t index) called" << endl << endl;

  if ( index < fNJets ) {
    return ((GJet*)(fJets->At(index)))->Pt();
  } else {
    TString msg = "GJets::GetPt index: ";
    msg += index;
    msg.Append(" larger than total number of jets: ");
    msg += fNJets;
    gLister->FillErrorList(msg.Data());
    return -99.;
  }

}
//_____________________________________________________________

Double_t GJets::GetEtbreit(Int_t index) {
  //
  // return transverse momentum of jet[index] in breit frame
  if ( gDebug ) cout << endl << "GJets::GetPtbreit(Int_t index) called" << endl << endl;

  if ( index < fNJets ) {
    return ((GJet*)(fJets->At(index)))->GetEtbreit();
  } else {
    TString msg = "GJets::GetPtbreit index: ";
    msg += index;
    msg.Append(" larger than total number of jets: ");
    msg += fNJets;
    gLister->FillErrorList(msg.Data());
    return -99.;
  }

}

//_____________________________________________________________

GJet* GJets::GetJet(Int_t index) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetJet called" << endl << endl;

  if ( (index < fNJets) && (index >= 0) ) {
    return ((GJet*)(fJets->At(index)));
  } else {
    TString msg = "GJets::GetJet: requested jet index: ";
    msg += index;
    msg.Append(" is larger that total number of jets: ");
    msg += fNJets;
    gLister->FillErrorList(msg.Data());
    return 0;
  }
}

//_____________________________________________________________

GJet* GJets::GetJetWithID(Int_t id) {
  //
  // return jet parameters of the jet with index
  if ( gDebug ) cout << endl << "GJets::GetJetWithID called" << endl << endl;

  GJet *jet1 = 0;

  for ( Int_t i = 0; i < fNJets; i++ ) {
    jet1 = ((GJet*)(fJets->At(i)));
    if ( jet1->GetID() == id )
      return jet1;
  }
  TString msg = "GJets::GetJetWithID: requested jet index: ";
  msg += id;
  msg.Append(" not found!");
  gLister->FillErrorList(msg.Data());
  return 0;
}

//_____________________________________________________________

TString GJets::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GJets::PrintMessage() called" << endl << endl;

  TString dummy = "Jets:\n\n";

  GJet *jet = 0;

  for ( Int_t i = 0; i < fNJets; i++ ) {
    jet = ((GJet*)(fJets->At(i)));
    dummy.Append(jet->PrintMessage(option));
  }

  return dummy;
}

//_____________________________________________________________

Bool_t GJets::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GJets::Print() called" << endl << endl;

  option.ToUpper();

  GJet *jet = 0;

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("JETS") || option.Contains("ALL") ) {
      gLister->FillOutputList("Jets:\n\n");
      for ( Int_t i = 0; i < fNJets; i++ ) {
	jet = ((GJet*)(fJets->At(i)));
	jet->Print(option);
      }
      gLister->FillOutputList("\n");
    }
  } else {
    cout << "Jets:" << endl << endl;;
    for ( Int_t i = 0; i < fNJets; i++ ) {
      jet = ((GJet*)(fJets->At(i)));
      jet->Print(option);
    }
    cout << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::FillHistos() {
  //
  // fill histograms with data
  if ( gDebug ) cout << endl << "GJets::FillHistos() called" << endl << endl;

  // fill histograms by looping over internal array
  ObjectsFillHistos();

  // fill general histograms
  FillGeneral();
  
  // fill control plots
  FillControl();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::ObjectsFillHistos() {
  //
  // fill histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GJets::ObjectsFillHistos() called" << endl << endl;

  // loop over array
  for ( Int_t i = 0; i < fNJets; i++ ) {
    GJet *jet = ((GJet*)(fJets->At(i)));

    // fill general plots
    ObjectsFillGeneral(jet);
    
    // fill control plots
    ObjectsFillControl(jet);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::ObjectsFillGeneral(GJet *jet) {
  //
  // fill general histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GJets::ObjectsFillGeneral() called" << endl << endl;

  if ( gCards->GetJETGeneral() ) {

    fGeneralE_uncut->Fill(jet->E(),gHeader->GetWeight());
    fGeneralPt_uncut->Fill(jet->Pt(),gHeader->GetWeight());
    fGeneralEt_uncut->Fill(jet->Et(),gHeader->GetWeight());
    fGeneralEta_uncut->Fill(jet->Eta(),gHeader->GetWeight());
    fGeneralPhi_uncut->Fill(jet->Phi(),gHeader->GetWeight());
    fGeneralMass_uncut->Fill(jet->M(),gHeader->GetWeight());

    if ( gHeader->GetAllCuts() ) {

      if ( jet->GetSelected() ) {
	GJet *mcjet = jet->GetAssociatedMCJet();
	if ( mcjet != 0 ) {
	  fGeneralPtMinPtTrue->Fill((jet->Pt()-mcjet->Pt())/mcjet->Pt(),gHeader->GetWeight());
	  fGeneralPtVsPtTrue->Fill(jet->Pt(),mcjet->Pt(),gHeader->GetWeight());
	  fGeneralEtaMinEtaTrue->Fill((jet->Eta()-mcjet->Eta())/mcjet->Eta(),gHeader->GetWeight());
	  fGeneralEtaVsEtaTrue->Fill(jet->Eta(),mcjet->Eta(),gHeader->GetWeight());
	}
      }


      if ( jet->GetType() == kFirst ) {
	fGeneralE_A->Fill(jet->E(),gHeader->GetWeight());
	fGeneralPt_A->Fill(jet->Pt(),gHeader->GetWeight());
	fGeneralEt_A->Fill(jet->Et(),gHeader->GetWeight());
	if (gCards->GetJETBreit())
	  fGeneralEt_A_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	fGeneralEta_A->Fill(jet->Eta(),gHeader->GetWeight());
	fGeneralEta_A_Large->Fill(jet->Eta(),gHeader->GetWeight());
	fGeneralPhi_A->Fill(jet->Phi(),gHeader->GetWeight());
	fGeneralMass_A->Fill(jet->M(),gHeader->GetWeight());
      }

      if ( jet->GetType() == kSecond ) {
	fGeneralE_B->Fill(jet->E(),gHeader->GetWeight());
	fGeneralPt_B->Fill(jet->Pt(),gHeader->GetWeight());
	fGeneralEt_B->Fill(jet->Et(),gHeader->GetWeight());
	if (gCards->GetJETBreit())
	  fGeneralEt_B_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	fGeneralEta_B->Fill(jet->Eta(),gHeader->GetWeight());
	fGeneralEta_B_Large->Fill(jet->Eta(),gHeader->GetWeight());
	fGeneralPhi_B->Fill(jet->Phi(),gHeader->GetWeight());
	fGeneralMass_B->Fill(jet->M(),gHeader->GetWeight());
      }

      if ( jet->GetMatched() ) {
	for ( Int_t i = 0; i < jet->GetMatched(); ++i ) {
	  fGeneralCrossMuonJetPt->Fill(jet->Pt(),gHeader->GetWeight());
	  fGeneralCrossMuonJetEta->Fill(jet->Eta(),gHeader->GetWeight());
	  fGeneralCrossMuonJetPtFine->Fill(jet->Pt(),gHeader->GetWeight());
	  fGeneralCrossMuonJetEtaFine->Fill(jet->Eta(),gHeader->GetWeight());

	  if ( gCards->GetMC()  && !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
	    if ( gMCs->GetAllMCCuts() ) {
	      GJet *mc_jet = jet->GetAssociatedMCJet();
	      if ( mc_jet != 0 ) {
		if ( gMCs->IsMuonAssociatedToMCJet(mc_jet) ) {
		  fGeneralCrossMuonJetPtRecNTrue->Fill(jet->Pt(),gHeader->GetWeight());
		  fGeneralCrossMuonJetEtaRecNTrue->Fill(jet->Eta(),gHeader->GetWeight());
		  fGeneralCrossMuonJetPtFineRecNTrue->Fill(jet->Pt(),gHeader->GetWeight());
		  fGeneralCrossMuonJetEtaFineRecNTrue->Fill(jet->Eta(),gHeader->GetWeight());
		}
	      }
	    }
	  }
	  fGeneralPt_Matched->Fill(jet->Pt(),gHeader->GetWeight());
	  fGeneralEt_Matched->Fill(jet->Et(),gHeader->GetWeight());
	  fGeneralCostherastarXgamma->Fill(jet->GetMJCosThetaStar_xgamma(),gHeader->GetWeight());

	  if (gSinistra->GetQ2() < 10.)
	    fGeneralEt_0_10_Matched->Fill(jet->Et(),gHeader->GetWeight());
	  else if (gSinistra->GetQ2() < 200.) 
	    fGeneralEt_10_200_Matched->Fill(jet->Et(),gHeader->GetWeight());
	  else 
	    fGeneralEt_200_Matched->Fill(jet->Et(),gHeader->GetWeight());
	  if (gCards->GetJETBreit()) {
	    fGeneralEt_Matched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	    if (gSinistra->GetQ2() < 10.)
	      fGeneralEt_0_10_Matched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	    else if (gSinistra->GetQ2() < 200.) 
	      fGeneralEt_10_200_Matched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	    else
	      fGeneralEt_200_Matched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	  }
	  fGeneralEta_Matched->Fill(jet->Eta(),gHeader->GetWeight());
	  fGeneralEta_Matched_Large->Fill(jet->Eta(),gHeader->GetWeight());
	  fGeneralMass_Matched->Fill(jet->M(),gHeader->GetWeight());
	  fGeneralPhi_Matched->Fill(jet->Phi(),gHeader->GetWeight());
	}
      }
      
      // fill the jet which is not matched but has the highest pt
      if ( jet->GetSelected() && jet->GetUnmatched() ) {
	fGeneralPt_Unmatched->Fill(jet->Pt(),gHeader->GetWeight());
	fGeneralEt_Unmatched->Fill(jet->Et(),gHeader->GetWeight());
	if (gSinistra->GetQ2() < 10.)
	  fGeneralEt_0_10_Unmatched->Fill(jet->Et(),gHeader->GetWeight());
	else if (gSinistra->GetQ2() < 200.) 
	  fGeneralEt_10_200_Unmatched->Fill(jet->Et(),gHeader->GetWeight());
	else 
	  fGeneralEt_200_Unmatched->Fill(jet->Et(),gHeader->GetWeight());
	if (gCards->GetJETBreit()) {
	  fGeneralEt_Unmatched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	  if (gSinistra->GetQ2() < 10.)
	    fGeneralEt_0_10_Unmatched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	  else if (gSinistra->GetQ2() < 200.) 
	    fGeneralEt_10_200_Unmatched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	  else
	    fGeneralEt_200_Unmatched_breit->Fill(jet->GetEtbreit(),gHeader->GetWeight());
	}
	fGeneralEta_Unmatched->Fill(jet->Eta(),gHeader->GetWeight());
	fGeneralEta_Unmatched_Large->Fill(jet->Eta(),gHeader->GetWeight());
	fGeneralMass_Unmatched->Fill(jet->M(),gHeader->GetWeight());
	fGeneralPhi_Unmatched->Fill(jet->Phi(),gHeader->GetWeight());
      }

    }
      
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::ObjectsFillControl(GJet *jet) {
  //
  // fill control histograms with data by looping over internal array
  if ( gDebug ) cout << endl << "GJets::ObjectsFillControl() called" << endl << endl;

  if ( gCards->GetJETControl() ) {

    fControlPt_uncut->Fill(jet->Pt());
    fControlEta_uncut->Fill(jet->Eta());

    if ( jet->GetType() == kFirst ) {
      fControlPtA->Fill(jet->Pt());
      fControlEtaA->Fill(jet->Eta());
    }

    if ( jet->GetType() == kSecond ) {
      fControlPtB->Fill(jet->Pt());
      fControlEtaB->Fill(jet->Eta());
    }

  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GJets::Calc(Int_t index1, Int_t index2) {
  //
  // calculate variables
  if ( gDebug ) cout << endl << "GJets::Calc called" << endl << endl;
  
  GJet *jet1 = 0;
  GJet *jet2 = 0;

  if ( fPtACut ) {
    jet1 = GetJetWithID(index1);
    fXGammaJets = jet1->E()-jet1->Pz();
    fXGammaJets_zufo = jet1->E()-jet1->Pz();
    // associated rec jet with true jet
    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake()) ) {
      gMCs->AssociateMCJet(jet1);
    }
  }
  if ( fPtBCut ) {
    jet2 = GetJetWithID(index2);
    if ( fXGamma == -9999.99 )
      fXGammaJets = jet2->E()-jet2->Pz();
    else
      fXGammaJets += jet2->E()-jet2->Pz();
    if ( fXGammaJets_zufo == -9999.99 )
      fXGammaJets_zufo = jet2->E()-jet2->Pz();
    else
      fXGammaJets_zufo += jet2->E()-jet2->Pz();
    // associated rec jet with true jet
    if ( gCards->GetMC() && !(gCards->GetMCLF() && gCards->GetDoFake())) {
      gMCs->AssociateMCJet(jet2);
    }
  }
  if(jet1 && jet2) fEtaJets = TMath::Abs((jet1->Eta()+jet2->Eta())/2);

  fXGammaJets /= gCal->GetEmpz();
  fXGammaJets_zufo /= gZufo->GetEmpz_had();

  if(fXGammaJets>=1) fXGammaJets=0.99999;
  if(fXGammaJets_zufo>=1) fXGammaJets_zufo=0.99999;

  if ( (jet1!=0)&&(jet2!=0) ) {
    fXGamma = ((jet1->Et()*TMath::Exp(-jet1->Eta()))+(jet2->Et()*TMath::Exp(-jet2->Eta())))/2/gCards->GetMachineEnergyLepton()/gZufo->GetYJB_had();

    Double_t mquadrat = (jet1->E()+jet2->E())*(jet1->E()+jet2->E())-(jet1->Px()+jet2->Px())*(jet1->Px()+jet2->Px())-(jet1->Py()+jet2->Py())*(jet1->Py()+jet2->Py())-(jet1->Pz()+jet2->Pz())*(jet1->Pz()+jet2->Pz());
    fMJets = TMath::Sqrt(mquadrat);

    //    TLorentzVector dijet = *jet1 + *jet2;
    // fMJets = dijet.M();
    fDPhiJets = TMath::Abs(jet1->DeltaPhi(*jet2));
    fDRJets   = jet1->DeltaR(*jet2);
    fPtJets = TMath::Power((jet1->Px()+jet2->Px()),2)+TMath::Power((jet1->Py()+jet2->Py()),2);
    //    fCosThetaStarJets = TMath::TanH((jet1->Eta()-jet2->Eta())/2);

  }
   
  return kTRUE;
}

