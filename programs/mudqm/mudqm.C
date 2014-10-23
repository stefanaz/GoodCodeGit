#define mudqm_cxx
#include "mudqm.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TObject.h>
#include <TLegend.h>
#include <TLegendEntry.h>

#include <iostream>
#include <fstream>
#include <strstream>
//#define BINS 3201
//#define BINS 4251
#define BINS 1682
#define LUMICUT 2

//TString running_p= "99e";
TString running_p;
TString current_file = "";
TString line = "";
Int_t run_nr =-999;
Float_t lumi[BINS];
Int_t run_bins = BINS-1;
Int_t startrun_nr_96 = 20718; // ln -sf b103.h mudqm.h
Int_t startrun_nr_97 = 25190; // ln -sf b104.h mudqm.h
Int_t startrun_nr_98 = 30758; // ln -sf b105.h mudqm.h
Int_t startrun_nr_99e= 31784; // (e-) ln -sf b106.h mudqm.h
Int_t startrun_nr_99 = 33125; // (e+) ln -sf b101.h mudqm.h
Int_t startrun_nr_00 = 35031; // ln -sf b102.h mudqm.h
Int_t startrun_nr_03 = 45783; // ln -sf b9b03.h mudqm.h
Int_t startrun_nr_04 = 47010; // ln -sf b9b04.h mudqm.h
Int_t startrun_nr_05 = 52258; // ln -sf b208.h mudqm.h
Int_t startrun_nr = -999;
Int_t endrun_nr = 100000;
Int_t lumi_cut = LUMICUT;

Int_t dump;

Float_t callumi;
Float_t spclumi;

Int_t nmu_lt_3 = 0;
Int_t nmu_lt_4 = 0;
Int_t nmu_lt_5 = 0;
Int_t nmu_lt_6 = 0;
Int_t nmu_lt_7 = 0;
Float_t bin_cont3 = 0;
Float_t bin_cont4 = 0;
Float_t bin_cont5 = 0;
Float_t bin_cont6 = 0;
Float_t bin_cont7 = 0;
Float_t bin_err3 = 0;
Float_t bin_err4 = 0;
Float_t bin_err5 = 0;
Float_t bin_err6 = 0;
Float_t bin_err7 = 0;
Int_t runnr_buffer = -999;

Int_t bin = -999;


// TH1F* muqual_ratio3 = new TH1F("muqual_ratio3","muqual_ratio3",300,45700,46000);
// TH1F* muqual_ratio4 = new TH1F("muqual_ratio4","muqual_ratio4",300,45700,46000);
// TH1F* muqual_ratio5 = new TH1F("muqual_ratio5","muqual_ratio5",300,45700,46000);
// TH1F* muqual_ratio6 = new TH1F("muqual_ratio6","muqual_ratio6",300,45700,46000);
// TH1F* muqual_ratio7 = new TH1F("muqual_ratio7","muqual_ratio7",300,45700,46000);

void mudqm::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L h1.C
  //      Root > h1 t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  
  Int_t nentries = Int_t(fChain->GetEntriesFast());
  
  Int_t nbytes = 0, nb = 0;
  
  for (Int_t i=0; i<=run_bins;++i) lumi[i]=-999;

//   if (running_p.BeginsWith("96")) { // b103.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns96-latest.html");
//     startrun_nr = startrun_nr_96;
//   }
//   else if (running_p.BeginsWith("97")) {// b104.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns97-latest.html");
//     startrun_nr  = startrun_nr_97;
//   }
//   else if (running_p.BeginsWith("98")) {// (e-)b105.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns98-latest.html");
//     startrun_nr  = startrun_nr_98;
//   }
//   else if (running_p.BeginsWith("99e")) {// (e-)b106.h 
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns99e-latest.html");
//     startrun_nr  = startrun_nr_99e;
//   }
//   else if (running_p.BeginsWith("99p")) {// (e+)b101.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns99-latest.html");
//     startrun_nr  = startrun_nr_99;
//   }
//   else if (running_p.BeginsWith("00")) {// b102.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns00-latest.html");
//     startrun_nr  = startrun_nr_00;
//   }
//   else if (running_p.BeginsWith("03")) {// b9b03.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns03-latest.html");
//     startrun_nr  = startrun_nr_03;
//   }
//   else if (running_p.BeginsWith("04")) {// b9b04.h
//     current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns04-latest.html");
//     startrun_nr  = startrun_nr_04;
//   }
//   else cout << "Invalid running periode!"<< endl;
  
  //   cout << "run_bins: " << run_bins << "\t startbin:" << startrun_nr << "endbin:" <<startrun_nr+run_bins << endl;  
  //  current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns04-latest.html");  
  current_file.Append("/afs/desy.de/user/k/kahle/zeus/dqm/validruns05-latest.html");  
  runnr_buffer = startrun_nr;
  ifstream stream(current_file);
  
  while ( line.ReadLine(stream) ) {
    istrstream stream5(line.Data());
    if ( line.BeginsWith("+") ) line.ReplaceAll("+   ","");
    if ( line.BeginsWith("+") ) line.ReplaceAll("+  ","");
    if ( line.BeginsWith("  +"))line.ReplaceAll("  +   ","");
    stream5 >> run_nr;
//     cout<<" run_nr "<< run_nr<<endl;
//     cout<<" startrun_nr "<< startrun_nr<<endl;
    if (startrun_nr < 1) {
      if (run_nr >= startrun_nr_96 && run_nr < startrun_nr_97) {
	running_p="96";
	startrun_nr  = startrun_nr_96;
      }
      else if (run_nr >= startrun_nr_97 && run_nr < startrun_nr_98){
	running_p="97";
	startrun_nr  = startrun_nr_97;
      }
      else if (run_nr >= startrun_nr_98 && run_nr < startrun_nr_99e){
	running_p="98";
	startrun_nr  = startrun_nr_98;
      }
      else if (run_nr >= startrun_nr_99e && run_nr < startrun_nr_99){
	running_p="99e";
	startrun_nr  = startrun_nr_99e;
      }
      else if (run_nr >= startrun_nr_99 && run_nr < startrun_nr_00){
	running_p="99";
	startrun_nr  = startrun_nr_99;
      }
      else if (run_nr >= startrun_nr_00 && run_nr < startrun_nr_03) {
	running_p="00";
	startrun_nr  = startrun_nr_00;
      }
      else if (run_nr >= startrun_nr_03 && run_nr < startrun_nr_04) {
	running_p="03";
	startrun_nr  = startrun_nr_03;
      }
      else if (run_nr >= startrun_nr_04 && run_nr < startrun_nr_05) {
	running_p="04";
	startrun_nr  = startrun_nr_04;
      }
      else if (run_nr >= startrun_nr_05 && run_nr < 100000) {
	running_p="05";
	startrun_nr  = startrun_nr_05;
      }
    }
    if (run_nr >= startrun_nr && run_nr < startrun_nr_03 && startrun_nr!=-999) { // 1996-2000 data
//       cout<<"pre startrun_nr "<<startrun_nr<<endl;
      stream5 >> callumi;
      lumi[run_nr+1-startrun_nr]=callumi;
    }  
    else if (run_nr >= startrun_nr_03 && run_nr < 100000 && startrun_nr!=-999) { // >2003 data
//       cout<<"post startrun_nr "<<startrun_nr<<endl;
      stream5 >> dump;
      stream5 >> callumi;
      stream5 >> spclumi;
      lumi[run_nr+1-startrun_nr]=((callumi > spclumi) ? callumi : spclumi);
    }  
    endrun_nr = run_nr;
  }     
  for (Int_t i=0; i<=run_bins;++i) {
    if(lumi[i]>0) cout << "run: " << i+startrun_nr-1<<"\t lumi: " <<lumi[i]<<endl;
  } 
  cout << "Endrun: " <<endrun_nr << " startrun_nr: "<< startrun_nr << endl;

  TH1F* muqual_ratio3 = new TH1F("muqual_ratio3","muqual_ratio3",run_bins,startrun_nr,startrun_nr+run_bins);
  TH1F* muqual_ratio4 = new TH1F("muqual_ratio4","muqual_ratio4",run_bins,startrun_nr,startrun_nr+run_bins);
  TH1F* muqual_ratio5 = new TH1F("muqual_ratio5","muqual_ratio5",run_bins,startrun_nr,startrun_nr+run_bins);
  TH1F* muqual_ratio6 = new TH1F("muqual_ratio6","muqual_ratio6",run_bins,startrun_nr,startrun_nr+run_bins);
  TH1F* muqual_ratio7 = new TH1F("muqual_ratio7","muqual_ratio7",run_bins,startrun_nr,startrun_nr+run_bins);
  

  cout<<"\t runnr t runnr \t lumi \t 7-6 \t 7-6/lumi"<<endl;
  
  cout<<"*****************************************************************************"<<endl;
  for (Int_t jentry=0; jentry<nentries;jentry++) {
    Int_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //     if (jentry > 50000) break;
    
    if (runnr_buffer==startrun_nr) runnr_buffer = runnr; 
    if(trk_ntracks > 10 && trk_ntracks < 40){
      for(Int_t i = 0; i< nmu; ++i) {
	if(muqual[i]<3) nmu_lt_3 += 1;
	if(muqual[i]<4) nmu_lt_4 += 1;
	if(muqual[i]<5) nmu_lt_5 += 1;
	if(muqual[i]<6) nmu_lt_6 += 1;
	if(muqual[i]<7) nmu_lt_7 += 1;
      }
    }
    if(runnr_buffer != runnr) {
      
      bin = muqual_ratio3->FindBin((Float_t) runnr_buffer);
      
      // Fill histos and output ratios
      
      //	cout << "run " << runnr_buffer << " \t \t" << nmu_lt_3 << " \t" << nmu_lt_4 << " \t" << nmu_lt_5 << " \t" << nmu_lt_6 << " \t" << nmu_lt_7 <<endl;
      //	cout<<bin<<" "<<bin+45700-1<<" "<<lumi[bin]<<" 3: "<<nmu_lt_7-nmu_lt_3<<" "<<(Float_t)(nmu_lt_7-nmu_lt_3)/(Float_t)lumi[bin]<<" \t \t"<<(Float_t)(nmu_lt_7-nmu_lt_3)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_4)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_5)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_6)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_7)/(Float_t)nmu_lt_7<<endl;
      //	cout<<bin<<" "<<bin+45700-1<<" "<<lumi[bin]<<" 4: "<<nmu_lt_7-nmu_lt_4<<" "<<(Float_t)(nmu_lt_7-nmu_lt_4)/(Float_t)lumi[bin]<<" \t \t"<<(Float_t)(nmu_lt_7-nmu_lt_3)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_4)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_5)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_6)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_7)/(Float_t)nmu_lt_7<<endl;
      //	cout<<bin<<" "<<bin+45700-1<<" "<<lumi[bin]<<" 5: "<<nmu_lt_7-nmu_lt_5<<" "<<(Float_t)(nmu_lt_7-nmu_lt_5)/(Float_t)lumi[bin]<<" \t \t"<<(Float_t)(nmu_lt_7-nmu_lt_3)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_4)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_5)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_6)/(Float_t)nmu_lt_7<<" \t"<<(Float_t)(nmu_lt_7-nmu_lt_7)/(Float_t)nmu_lt_7<<endl;
      if(lumi[bin]>lumi_cut) cout<<bin<<"\t "<<runnr_buffer<<"\t "<<bin+startrun_nr-1<<"\t "<<lumi[bin]<<"\t 6: "<<nmu_lt_7-nmu_lt_6<<"\t "<<(Float_t)(nmu_lt_7-nmu_lt_6)/(Float_t)lumi[bin]<<endl;
	
      //	cout<<"runnr "<<runnr_buffer<<" bin nr "<<runnr_buffer - (45700-1)<< " erorr "<< TMath::Sqrt(nmu_lt_7)<<endl;

      if (lumi[bin]>lumi_cut) { // what if lumi 0?
	//	bin = runnr_buffer - 45700;
  	//	cout<<"runnr "<<runnr_buffer<<" bin nr "<<bin<< " erorr "<< TMath::Sqrt(nmu_lt_7)<<endl;
 	bin_cont3 = (Float_t)(nmu_lt_7-nmu_lt_3)/(Float_t)lumi[bin];
 	bin_cont4 = (Float_t)(nmu_lt_7-nmu_lt_4)/(Float_t)lumi[bin];
 	bin_cont5 = (Float_t)(nmu_lt_7-nmu_lt_5)/(Float_t)lumi[bin];
 	bin_cont6 = (Float_t)(nmu_lt_7-nmu_lt_6)/(Float_t)lumi[bin];
 	bin_cont7 = (Float_t)(nmu_lt_7-nmu_lt_7)/(Float_t)lumi[bin];

	muqual_ratio3->SetBinContent(bin,  bin_cont3 );
	muqual_ratio4->SetBinContent(bin,  bin_cont4 );
	muqual_ratio5->SetBinContent(bin,  bin_cont5 );
	muqual_ratio6->SetBinContent(bin,  bin_cont6 );
	muqual_ratio7->SetBinContent(bin,  bin_cont7 );
	
	//  	bin_err3 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7))/lumi[bin],2)+TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_3))/lumi[bin],2)+TMath::Power(bin_cont3*0.1,2));
	//  	bin_err4 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7))/lumi[bin],2)+TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_4))/lumi[bin],2)+TMath::Power(bin_cont4*0.1,2));
	//  	bin_err5 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7))/lumi[bin],2)+TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_5))/lumi[bin],2)+TMath::Power(bin_cont5*0.1,2));
	//  	bin_err6 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7))/lumi[bin],2)+TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_6))/lumi[bin],2)+TMath::Power(bin_cont6*0.1,2));
	//  	bin_err7 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7))/lumi[bin],2)+TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7))/lumi[bin],2)+TMath::Power(bin_cont7*0.1,2));

	//  	bin_err3 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_3))/lumi[bin],2)+TMath::Power(bin_cont3*0.1,2));
	//  	bin_err4 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_4))/lumi[bin],2)+TMath::Power(bin_cont4*0.1,2));
	//  	bin_err5 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_5))/lumi[bin],2)+TMath::Power(bin_cont5*0.1,2));
	//  	bin_err6 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_6))/lumi[bin],2)+TMath::Power(bin_cont6*0.1,2));
	//  	bin_err7 = TMath::Sqrt(TMath::Power(TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_7))/lumi[bin],2)+TMath::Power(bin_cont7*0.1,2));

 	bin_err3 = TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_3))/lumi[bin];  // small errors for lumi (Uta)
 	bin_err4 = TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_4))/lumi[bin];
 	bin_err5 = TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_5))/lumi[bin];
 	bin_err6 = TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_6))/lumi[bin];
 	bin_err7 = TMath::Sqrt((Float_t)(nmu_lt_7-nmu_lt_7))/lumi[bin];
	if (bin_cont3 == 0) bin_err3 = 0.00001; // make all entries visible!
	if (bin_cont4 == 0) bin_err4 = 0.00001; // make all entries visible!
	if (bin_cont5 == 0) bin_err5 = 0.00001; // make all entries visible!
	if (bin_cont6 == 0) bin_err6 = 0.00001; // make all entries visible!
	if (bin_cont7 == 0) bin_err7 = 0.00001; // make all entries visible!
	// 	bin_err3 = TMath::Sqrt(TMath::Power(bin_cont3*0.1,2));
	// 	bin_err4 = TMath::Sqrt(TMath::Power(bin_cont4*0.1,2));
	// 	bin_err5 = TMath::Sqrt(TMath::Power(bin_cont5*0.1,2));
	// 	bin_err6 = TMath::Sqrt(TMath::Power(bin_cont6*0.1,2));
	// 	bin_err7 = TMath::Sqrt(TMath::Power(bin_cont7*0.1,2));

	muqual_ratio3->SetBinError(bin, bin_err3);
	muqual_ratio4->SetBinError(bin, bin_err4);
	muqual_ratio5->SetBinError(bin, bin_err5);
	muqual_ratio6->SetBinError(bin, bin_err6);
	muqual_ratio7->SetBinError(bin, bin_err7);
      }
      // reinitialise counters	
      nmu_lt_3 = 0;
      nmu_lt_4 = 0;
      nmu_lt_5 = 0;
      nmu_lt_6 = 0;
      nmu_lt_7 = 0;
      runnr_buffer = runnr;
    }
    //     endrun_nr = 20755;
    // if (runnr>endrun_nr) break;
    // if (Cut(ientry) < 0) continue;
  }
  
  TCanvas * da = new TCanvas("da","ratios");
  da->Divide(1,5);
  
  da->cd(1);
  muqual_ratio3->SetMarkerColor(3);
  muqual_ratio3->SetMarkerStyle(28);
  muqual_ratio3->SetMarkerSize(0.7);
  muqual_ratio3->GetXaxis()->SetTitle("ZEUS Run number");
  muqual_ratio3->GetYaxis()->SetTitle("#mu's with given muqual / nb^{-1}");
  muqual_ratio3->Draw("P0");

  da->cd(2);
  muqual_ratio4->SetMarkerColor(4);
  muqual_ratio4->SetMarkerStyle(8);
  muqual_ratio4->SetMarkerSize(0.7);
  muqual_ratio4->GetXaxis()->SetTitle("ZEUS Run number");
  muqual_ratio4->GetYaxis()->SetTitle("#mu's with given muqual / nb^{-1}");
  muqual_ratio4->Draw("P0");

  da->cd(3);
  muqual_ratio5->SetMarkerColor(6);
  muqual_ratio5->SetMarkerStyle(23);
  muqual_ratio5->SetMarkerSize(0.7);
  muqual_ratio5->GetXaxis()->SetTitle("ZEUS Run number");
  muqual_ratio5->GetYaxis()->SetTitle("#mu's with given muqual / nb^{-1}");
  muqual_ratio5->Draw("P0");

  da->cd(4);
  muqual_ratio6->SetMarkerColor(2);
  muqual_ratio6->SetMarkerStyle(29);
  muqual_ratio6->SetMarkerSize(1.1);
  muqual_ratio6->GetXaxis()->SetTitle("ZEUS Run number");
  muqual_ratio6->GetYaxis()->SetTitle("#mu's with given muqual / nb^{-1}");
  muqual_ratio6->Draw("P0"); // probier das mal!

  da->cd(5);
  muqual_ratio3->Draw("P0");
  muqual_ratio4->Draw("same P0");
  muqual_ratio5->Draw("same P0");
  muqual_ratio6->Draw("same P0");
  //   muqual_ratio7->Draw();

  TCanvas * da2 = new TCanvas("da2","ratios2");
  muqual_ratio3->Draw("P0");
  muqual_ratio4->Draw("same P0");
  muqual_ratio5->Draw("same P0");
  muqual_ratio6->Draw("same P0");


  TLegend *leg = new TLegend(0.487069,0.690678,0.771552,0.879237,NULL,"brNDC");
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(1001);
  leg->SetBorderSize(1);
  TLegendEntry *entry=leg->AddEntry("muqual_ratio3","#mu's with muqual #geq 3","p");
  entry=leg->AddEntry("muqual_ratio4","#mu's with muqual #geq 4","p");
  entry=leg->AddEntry("muqual_ratio5","#mu's with muqual #geq 5","p");
  entry=leg->AddEntry("muqual_ratio6","#mu's with muqual #geq 6","p");
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(1);
  entry->SetMarkerStyle(21);
  entry->SetMarkerSize(1);
  entry->SetTextAlign(12);
  entry->SetTextColor(1);
  leg->Draw("P0");
 
 

  //Save histos to file:
  TString filename;
  Int_t good_len;
  TDatime * time = new TDatime();
  filename = "muon_dqm";
  filename.Append(running_p);
  filename.Append("_");
  filename += time->GetDate();
  good_len = filename.Length();

  filename.Append(".root");
  TFile * output = new TFile(filename,"RECREATE");
  filename.Remove(good_len);

  filename.Append(".ps(");
  da->SaveAs(filename);
  filename.Remove(good_len);
  filename.Append(".ps)");
  da2->SaveAs(filename);
  filename.Remove(good_len);


  output->Append(muqual_ratio3->Clone());
  output->Append(muqual_ratio4->Clone());
  output->Append(muqual_ratio5->Clone());
  output->Append(muqual_ratio6->Clone());
  output->Append(muqual_ratio7->Clone());
  output->Append(da);
  output->Append(da2);
  output->Write();
  //    output->Close();

}
