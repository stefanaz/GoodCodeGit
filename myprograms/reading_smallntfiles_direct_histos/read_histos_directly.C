#include "TCanvas.h"
#include "TMath.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TKey.h"
#include "TROOT.h"
//#include "TIter.h"
#include "iostream"
#include "iomanip"


Int_t read_histos() {

Int_t rebin_value = 3;

Bool_t bbfiles = false;
Bool_t ccfiles = false;
Bool_t Jpsifiles = false;
Bool_t all = false;


Int_t start_file = 2;
Int_t nfiles = 4;  /// 88

if (bbfiles) 	{start_file = 0;nfiles = 24;}
if (ccfiles)	{start_file = 24;nfiles = 48;}
if (Jpsifiles) 	{start_file = 48;nfiles = 88;}
if (all) 	{start_file = 0;nfiles = 88;}


TString outfile, infile[100];
TString previous_obj, histonamebuffer;

infile[0] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/03p-04p/dir/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[1] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/03p-04p/res/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[2] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/03p-04p/resrap/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[3] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/03p-04p/dirrap/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[4] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/03p-04p/exgamma/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[5] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/03p-04p/exproton/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";

infile[6] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/05e/dir/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[7] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/05e/res/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[8] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/05e/resrap/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[9] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/05e/dirrap/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[10] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/05e/exgamma/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[11] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/05e/exproton/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";

infile[12] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06e/dir/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[13] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06e/res/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[14] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06e/resrap/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[15] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06e/dirrap/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[16] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06e/exgamma/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[17] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06e/exproton/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";

infile[18] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06p-07p/dir/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[19] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06p-07p/res/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[20] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06p-07p/resrap/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[21] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06p-07p/dirrap/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[22] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06p-07p/exgamma/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[23] = "/data/zenith234d/stefan/GutCode/anadir/mc/b/06p-07p/exproton/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";

/// cc
infile[24] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/03p-04p/dir/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[25] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/03p-04p/res/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[26] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/03p-04p/resrap/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[27] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/03p-04p/dirrap/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[28] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/03p-04p/exgamma/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[29] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/03p-04p/exproton/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";

infile[30] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/05e/dir/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[31] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/05e/res/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[32] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/05e/resrap/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[33] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/05e/dirrap/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[34] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/05e/exgamma/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[35] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/05e/exproton/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";

infile[36] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06e/dir/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[37] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06e/res/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[38] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06e/resrap/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[39] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06e/dirrap/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[40] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06e/exgamma/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[41] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06e/exproton/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";

infile[42] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06p-07p/dir/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[43] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06p-07p/res/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[44] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06p-07p/resrap/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[45] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06p-07p/dirrap/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[46] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06p-07p/exgamma/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[47] = "/data/zenith234d/stefan/GutCode/anadir/mc/c/06p-07p/exproton/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";

/// bh
infile[48] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/03p-04p/DIS/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[49] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/03p-04p/elastic/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[50] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/03p-04p/inelastic/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";

infile[51] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/05e/DIS/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[52] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/05e/elastic/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[53] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/05e/inelastic/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";

infile[54] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/06e/DIS/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[55] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/06e/elastic/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[56] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/06e/inelastic/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";

infile[57] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/06p-07p/DIS/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[58] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/06p-07p/elastic/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[59] = "/data/zenith234d/stefan/GutCode/anadir/mc/bh/06p-07p/inelastic/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";

/// jpsi
infile[60] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/03p-04p/jpsi1/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[61] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/03p-04p/jpsi2/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[62] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/05e/jpsi1/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[63] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/05e/jpsi2/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[64] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/06e/jpsi1/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[65] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/06e/jpsi2/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[66] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/06p-07p/jpsi1/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[67] = "/data/zenith234d/stefan/GutCode/anadir/mc/jpsi/06p-07p/jpsi2/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";

/// psiprime
infile[68] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/03p-04p/all/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[69] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/03p-04p/psi2/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[70] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/05e/all/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[71] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/05e/psi2/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[72] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/06e/all/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[73] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/06e/psi2/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[74] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/06p-07p/all/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[75] = "/data/zenith234d/stefan/GutCode/anadir/mc/psiprime/06p-07p/psi2/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";

/// Upsilon
infile[76] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/03p-04p/1s_dir/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[77] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/03p-04p/2s_dir/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";
infile[78] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/03p-04p/3s_dir/mini_HeraII_0304p_Data_MC_Dimuon_Finalversion/histos.root";

infile[79] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/05e/1s_dir/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[80] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/05e/2s_dir/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";
infile[81] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/05e/3s_dir/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/histos.root";

infile[82] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/06e/1s_dir/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[83] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/06e/2s_dir/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";
infile[84] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/06e/3s_dir/mini_HeraII_06e_Data_MC_Dimuon_Finalversion/histos.root";

infile[85] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/06p-07p/1s_dir/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[86] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/06p-07p/2s_dir/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";
infile[87] = "/data/zenith234d/stefan/GutCode/anadir/mc/upsilon/06p-07p/3s_dir/mini_HeraII_0607p_Data_MC_Dimuon_Finalversion/histos.root";


Double_t scale[88];
scale[0] = 0.109224 ;
scale[1] = 0.115015 ;
scale[2] = 0.0347741 ;
scale[3] = 0.0347581 ;
scale[4] = 0.0871909 ;
scale[5] = 0.10409 ;
scale[6] = 0.105773 ;
scale[7] = 0.106497 ;
scale[8] = 0.0625514 ;
scale[9] = 0.0625261 ;
scale[10] = 0.103901 ;
scale[11] = 0.103508 ;
scale[12] = 0.105773 ;
scale[13] = 0.106497 ;
scale[14] = 0.0625514 ;
scale[15] = 0.0625261 ;
scale[16] = 0.103901 ;
scale[17] = 0.103508 ;
scale[18] = 0.0936139 ;
scale[19] = 0.0937811 ;
scale[20] = 0.05836 ;
scale[21] = 0.0565955 ;
scale[22] = 0.102984 ;
scale[23] = 0.0827257 ;
scale[24] = 1 ;
scale[25] = 1 ;
scale[26] = 0.979394 ;
scale[27] = 0.326048 ;
scale[28] = 1 ;
scale[29] = 1 ;
scale[30] = 1 ;
scale[31] = 1 ;
scale[32] = 0.939463 ;
scale[33] = 0.42264 ;
scale[34] = 1 ;
scale[35] = 1 ;
scale[36] = 1 ;
scale[37] = 1 ;
scale[38] = 0.939463 ;
scale[39] = 0.42264 ;
scale[40] = 1 ;
scale[41] = 1 ;
scale[42] = 1 ;
scale[43] = 1 ;
scale[44] = 0.292905 ;
scale[45] = 0.292944 ;
scale[46] = 1 ;
scale[47] = 1 ;
scale[48] = 0.0168283 ;
scale[49] = 0.24357 ;
scale[50] = 0.137448 ;
scale[51] = 0.0168283 ;
scale[52] = 0.24357 ;
scale[53] = 0.137448 ;
scale[54] = 0.0168283 ;
scale[55] = 0.24357 ;
scale[56] = 0.137448 ;
scale[57] = 0.0168283 ;
scale[58] = 0.24357 ;
scale[59] = 0.137448 ;
scale[60] = 0.0539092 ;
scale[61] = 0.909532 ;
scale[62] = 0.0539092 ;
scale[63] = 0.909532 ;
scale[64] = 0.0539092 ;
scale[65] = 0.909532 ;
scale[66] = 0.0539092 ;
scale[67] = 0.909532 ;
scale[68] = 0.0636531 ;
scale[69] = 0.647769 ;
scale[70] = 0.0636531 ;
scale[71] = 0.647769 ;
scale[72] = 0.0636531 ;
scale[73] = 0.647769 ;
scale[74] = 0.0636531 ;
scale[75] = 0.647769 ;
scale[76] = 1.05314 ;
scale[77] = 1.05314 ;
scale[78] = 1.05314 ;
scale[79] = 1.05314 ;
scale[80] = 1.05314 ;
scale[81] = 1.05314 ;
scale[82] = 1.05314 ;
scale[83] = 1.05314 ;
scale[84] = 1.05314 ;
scale[85] = 1.05314 ;
scale[86] = 1.05314 ;
scale[87] = 1.05314 ;


Int_t count1 = 0;
TH1D *obj[10000][100];
TKey *key;
Int_t entries = 0;
const Int_t histNumb =5;
// 45 -full Q2silog10
// 543   - invmass


  for(Int_t vorne = 0; vorne<10000; vorne++)
    {
      for(Int_t hinten = 0; hinten<100; hinten++) obj[vorne][hinten] = 0;
    }


  for(Int_t i=start_file; i<nfiles; i++) 
    { // here fileloop
count1 =0;
cout<<infile[i]<<endl;
_file0 = new TFile(infile[i],"READ"); 
// _file0->ls();
_file0->cd("Histograms/MC");
// gDirectory->pwd();
  TIter next( gDirectory->GetListOfKeys() );
  while ((key = (TKey *) next())) 
{
    obj[count1][i] = (TH1D*) gDirectory->Get(key->GetName());  /// cout<<key->GetName()<<endl; // copy object to memory
    obj[count1][i]->SetDirectory(0);
    obj[count1][i]->AddDirectory(kFALSE);
   
 // do something with obj
    if( previous_obj==key->GetName() ) 
	{
	continue;
	} 
	  previous_obj = key->GetName();
	  count1++;

}
    _file0->Close();
// gDirectory->Get(key->GetName());
// cout<<" File "<<gDirectory->Get(key->GetName())<<"have added"<<endl;
  }

cout<<" Finish reading histoses ! "<<endl;

  for(Int_t j=start_file; j<nfiles; j++)
    {
      for(Int_t k=0; k<count1; k++)
	{
	obj[k][j]->Scale(scale[j]);
	  if (j!= start_file) {obj[k][start_file]->Add(obj[k][j],1);}
	}
    }	

obj[histNumb][start_file]->Rebin(rebin_value);
obj[histNumb][start_file]->SetMarkerSize(1.1);
obj[histNumb][start_file]->SetMarkerColor(4);
obj[histNumb][start_file]->SetMarkerStyle(20);
obj[histNumb][start_file]->Draw("E1");

entries = 0;
cout<<endl;
for (Int_t i=1;i<=obj[histNumb][start_file]->GetNbinsX();i++) {

entries = entries + obj[histNumb][start_file]->GetBinContent(i);/*cout<<entries<<endl;*/
}
cout<<obj[histNumb][start_file]->GetName()<<" Nevnts =  "<<entries<<"   Nbins = "<<obj[histNumb][start_file]->GetNbinsX()<<endl;

// cout<<"Nhistos = "<<count1<<endl;


return 0;
}