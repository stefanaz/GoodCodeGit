{

#ifdef __MA__  
#include "TMath.h"
#endif

#include <cstdio>
#include <string>
//#include <stdio.h>
  
// gSystem->Load("libRooFit") ;
// using namespace RooFit ;  

 gROOT->Reset();
 gROOT->SetStyle("Plain");
 gStyle->SetOptStat("em"); 

TChain * nt_old = new TChain("orange");
nt_old->Add("/data/zenith234d/stefan/GutCode/datadir/mini_HeraII_05e_Data_MC_Dimuon_Finalversion/data/05e/data/smallntuple.root");

TChain * nt_mynew = new TChain("orange");
nt_mynew->Add("/data/zenith234d/stefan/GutCode/datadir/mini_test3_HeraII_Data/data/05e/data/smallntuple.root");

cout<<" N events in Danny_miniNT = "<<nt_old->GetEntries()<<endl;
cout<<" N events in Mynew_miniNT = "<<nt_mynew->GetEntries()<<endl;

/// DATA root files comparison
int Runnr_tmp = 0;
int Evtnr_tmp = 0;
int GoodCompare_tmp =0;

int Runnr_old = 0;
int Eventnr_old = 0;
int Runnr_new = 0;
int Eventnr_new = 0;
int Eventnr = 0;


nt_old->SetBranchAddress("Eventnr", &Eventnr_old);
nt_old->SetBranchStatus("Eventnr", 1);
nt_mynew->SetBranchAddress("Eventnr", &Eventnr_new);
nt_mynew->SetBranchStatus("Eventnr", 1);

nt_old->SetBranchAddress("Runnr", &Runnr_old);
nt_old->SetBranchStatus("Runnr", 1);
nt_mynew->SetBranchAddress("Runnr", &Runnr_new);
nt_mynew->SetBranchStatus("Runnr", 1);


int  Enent_old_array[15387];
int  Enent_new_array[12981];

int  Runnr_old_array[15387];
int  Runnr_new_array[12981];

for (int i=0;i<nt_old->GetEntries();i++)
{
	nt_old->GetEntry(i);
	Enent_old_array[i] = Eventnr_old;
	Runnr_old_array[i] = Runnr_old;
}

for (int j=0;j<nt_mynew->GetEntries();j++)
{
	nt_mynew->GetEntry(j);
	Enent_new_array[j] = Eventnr_new;
	Runnr_new_array[j] = Runnr_new;
}

// cout<<Enent_old_array[0]<<"	"<<Enent_old_array[1]<<endl;


for (int i=0;i<nt_old->GetEntries();i++)
{

	GoodCompare_tmp = 0;
	
	for (int j=0;j<nt_mynew->GetEntries();j++)
	{
			if (Enent_old_array[i] == Enent_new_array[j] && Runnr_old_array[i] ==  Runnr_new_array[j]) 
				{
					cout<<"SAME! Runnr = "<<Runnr_old_array[i]<<" Eventnr = "<<Enent_old_array[i]<<endl;
					GoodCompare_tmp = 1;
					continue;
				}

	}

	if (GoodCompare_tmp == 0 ) cout<<"Compare FAILED! Runnr = "<<Runnr_old_array[i]<<" Eventnr = "<<Enent_old_array[i]<<endl;

}

gROOT->ProcessLine(".q");

}