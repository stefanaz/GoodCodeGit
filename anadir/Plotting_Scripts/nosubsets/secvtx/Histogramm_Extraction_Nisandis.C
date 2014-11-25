#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Nevents_Histosum/Draw_Errorbar.C"
#include "/data/zenith234d/stefan/GutCode/anadir/minuit/parameters_set.h"

Int_t Histogramm_Extraction_Nisandis(Bool_t highmass=true, Bool_t autoquit=false){



  if(highmass)
    {
      cout<<"***************************************"<<endl;
      cout<<"**** executing beauty est. hm *********"<<endl;
      cout<<"***************************************"<<endl;
    }

  else if(!highmass)
    {
      cout<<"***************************************"<<endl;
      cout<<"**** executing beauty est. lm *********"<<endl;
      cout<<"***************************************"<<endl;
    }

//   gROOT->Reset();
  gROOT->SetStyle("Plain");
  gROOT->UseCurrentStyle();

/// lfl corrections for 2% and 6%
  
  Double_t entries = 0.;
  Int_t nbins = 0;
  TString histoname;
  Double_t Delta_lfl =0.;
  Double_t Delta_bb =0.;

  gErrorIgnoreLevel = 1;

  Int_t  count1            = 0;
  //  Int_t nfiles        = 28+12+2; // WARNING! Do not move below 'dataposition'!
  Int_t  nfiles            = 50;
  Int_t  dataposition      = nfiles -1;
  Int_t  charmbegin        = 12; 

  Int_t  charmend           = 39;
  Int_t  BH_position1       = 30;
  Int_t  BH_position2       = 31;
  Int_t  BH_position3       = 32;
  Int_t  jpsi_position1     = 33;
  Int_t  jpsi_position2     = 34;
  Int_t  psiprime_position1 = 35;
  Int_t  psiprime_position2 = 36;
  Int_t  ups1_position      = 37;
  Int_t  ups2_position      = 38;
  Int_t  ups3_position      = 39;
  Int_t  bbbb_position      = 40;
  Int_t  cccc_position      = 41;
  Int_t  bbcc_position      = 42;

  Int_t  nhistos           = -9999;
  Int_t  nrows             = 9+4;
  Int_t  startfile         = 0;
  Int_t  typechooser       = 0;
  Int_t  rangechooser      = 0;
  Int_t  histonr           = 0;

  Int_t  MCentries        = 0;
  Int_t  dataentries      = 0;
  Stat_t MCintegral       = 0.;
  Stat_t MCallintegral    = 0.;
  Stat_t dataintegral     = 0.;
  Stat_t MCintegral_ls    = 0.;
  Stat_t dataintegral_ls  = 0.;

  Double_t binerror       = 0.;
  Double_t entries 	  = 0.;
// s_MC^b = (d^u-d^l-(c^u+bh^u+jpsi^u+psiprime^u))/(b^u-b^l)

  Double_t data_unlike                = 0.;
  Double_t data_like                  = 0.;
  Double_t beauty_unlike              = 0.;
  Double_t beauty_like                = 0.;
  Double_t all_bg_p_beauty_m_lfl_bg_u = 0.;


  Bool_t oldfilestyle   = false;
  Bool_t realtime       = false;
  Bool_t print_single   = false;
  Bool_t bigmarker      = false;
  Bool_t charm_extra    = false;
  Double_t useccbarincl = 1.0; // 1.8 if like sign charm is subtracted. In the old sample there was
                               // nearly NO like sign background, due to the preselection - here there is lots. Checks NEEDE!! 050203
  Double_t usedimuccbar = 0.0;
  Double_t rapgapscale  = 1.0; // to change DIS contrib.
  Double_t us_bg_corr   = 0;
  Bool_t smoothMC       = false;
  Bool_t list_histos    = true;
  Bool_t MBtakeON       = true;
  Bool_t fromoli        = true;
  Bool_t plot_dists_std = false;
  Bool_t plot_dists_kum = true;
  Bool_t plot_ls        = true;     // true - plots with ls part (N.Stefaniuk)
  Bool_t plot_diffxsec  = false;    // if true, norm. for differential xsec, if false, norm. for tot. xsec is used.
  Bool_t plot_hm        = highmass; // if false, lm is plotted

  TString iso_chooser   = "nisandis"; // possible values: is, nis & nisandis

  Bool_t calc_b_frac = autoquit;

  Bool_t MC_first       = false;

  Bool_t during_construction = false; //040521 distribs look good.

  TString previous_obj, printname, filename, strbuffer;

  TPad * padbuffer;

// Set plotting parametes:

  Double_t data_lumi       = 376.16; // Sum Lumi 05e,06e,06/07p
  Double_t data_lumi_03_04 =  40.59; // 03-04 data e+
  Double_t data_lumi_05_06 = 190.12; // 05-06 data e-
  Double_t data_lumi_06_07 = 145.90; // 06-07 data e+

  if(MBtakeON)
    {
      cout<<(char)27<<"[06;33m"<<"WARNING!! assuming MBtake to be ON and reducing the lumi values accordingly."<<(char)27<<"[0m"<<endl;
      data_lumi_03_04 =  40.59;          // 03-04 data e+
      data_lumi_05_06 = 190.12;          // 05-06 data e-
      data_lumi_06_07 = 145.90;          // 06-07 data e+
      data_lumi       = data_lumi_03_04 + data_lumi_05_06 + data_lumi_06_07; // sum of used preupgrade years
    }

  cout<<"data_lumi 03p-07p is: "<<data_lumi<<endl;

  Double_t dim_fl_exc = 1.0;

  if (scales_from_fit)Double_t MC_scale_b = MC_scale_b_fit; else
  if(!plot_diffxsec)  Double_t MC_scale_b = /*1.85*//*1.68002*//*1.42874*//*1.982164*/1.70149/*0.615674*/;         // tuning 080116 - for tot. xsec with BHadron ptb PAPERED2
  else                Double_t MC_scale_b = 1.777;        // tuning 080116 - for differential xsecs PAPERED2, new charm 1.37
 
  if (scales_from_fit)Double_t MC_scale_c = MC_scale_c_fit; else
  Double_t MC_scale_c = 1.37/*1.547214*/;                             // knowing 080116 - Achim's charm (D* analyse)
                                                          // scaling factor PAPERED2 (nach neuen effizienz korrekturen)

  if (scales_from_fit)Double_t MC_scale_BH_DIS = (MC_scale_jpsi1_fit*0.55/2.5); else
  if(!plot_diffxsec) Double_t MC_scale_BH_DIS = 0.55;    // tuning 080116 - for tot. xsec PAPERED2, new charm 1.37
  else               Double_t MC_scale_BH_DIS = 1.2;      // tuning 080116 - for differential xsecs PAPERED2, new charm 1.37

  if (scales_from_fit)Double_t MC_scale_BH_ela = (MC_scale_jpsi1_fit*6./2.5); else
  if(!plot_diffxsec) Double_t MC_scale_BH_ela = 6.;       // tuning 080116 - for tot. xsec PAPERED2, new charm 1.37
  else               Double_t MC_scale_BH_ela = 1.2;      // tuning 080116 - for differential xsecs PAPERED2, new charm 1.37

  if (scales_from_fit)Double_t MC_scale_BH_inela = (MC_scale_jpsi1_fit*2.2/2.5); else
  if(!plot_diffxsec) Double_t MC_scale_BH_inela = 2.2;     // tuning 080116 - for tot. xsec PAPERED2, new charm 1.37
  else               Double_t MC_scale_BH_inela = 1.2;    // tuning 080116 - for differential xsecs PAPERED2, new charm 1.37

  Double_t b_mixing = 0.00;                               // 041015: after cheching: BBbar osci is ON in our Pythia sample - take
                                                          // additional mixing out again *sigh*

  if (scales_from_fit)Double_t MC_scale_jpsi1 = MC_scale_jpsi1_fit; else
  if(!plot_diffxsec)  Double_t MC_scale_jpsi1 = 2.5/*2.441173*/;       // tuning 080116 - for tot. xsec with BHadron ptb PAPERED2, new charm 1.37
  else                Double_t MC_scale_jpsi1 = 2.097;    // tuning 080116 - for differential xsecs PAPERED2, new charm 1.37

  if (scales_from_fit)Double_t MC_scale_jpsi2 = (MC_scale_jpsi1_fit*0.90*0.036/2.5); else
  if(!plot_diffxsec)  Double_t MC_scale_jpsi2 = 0.9*0.036;    // tuning 080116 - for tot. xsec with BHadron ptb PAPERED2, new charm 1.37
  else                Double_t MC_scale_jpsi2 = 2.097;    // tuning 080116 - for differential xsecs PAPERED2, new charm 1.37
 

  if (scales_from_fit)Double_t MC_scale_psiprime1 = (MC_scale_jpsi1_fit*5./2.5); else
  if(!plot_diffxsec)  Double_t MC_scale_psiprime1 = 5.;   // tuning 080116, for tot. xsec PAPERED2, new charm 1.37
  else                Double_t MC_scale_psiprime1 = 0.3;  // tuning 080116, for diff. xsecs PAPERED2, new charm 1.37

  if (scales_from_fit)Double_t MC_scale_psiprime2 = (MC_scale_jpsi1_fit*0.0027/2.5); else
  if(!plot_diffxsec)  Double_t MC_scale_psiprime2 = 0.0027; // tuning 080116, for tot. xsec PAPERED2, new charm 1.37
  else                Double_t MC_scale_psiprime2 = 0.3;   // tuning 080116, for diff. xsecs PAPERED2, new charm 1.37

  Double_t MC_scale_ups1   = 0.0040447;
  Double_t MC_scale_ups2   = MC_scale_ups1*0.19/0.73;
  Double_t MC_scale_ups3   = MC_scale_ups1*0.08/0.73;

  Double_t MC_scale_bbbb   = 1.0;
  Double_t MC_scale_cccc   = 1.0;
  Double_t MC_scale_bbcc   = 1.0;

  Double_t gluspli_up       = 0.0;                       // enhance only gluon splitting MC a bit (dirty!!)
  //  Double_t MC_scale_inst    = 1.0;

  if(iso_chooser == "nis" && !plot_hm) 
    {
      Double_t scaledown_psiprime = 1.0;// neutral 050412
      Double_t scaledown_jpsi     = 1.0;
      Double_t scaledown_c        = 1.0;
      Double_t scaledown_b        = 1.0;

      cout<<endl<<(char)27<<"[06;33m"<<"WARNING!!!!!!! scaling down psiprime from default by factor: "<<scaledown_psiprime<<(char)27<<"[0m"<<endl;
      MC_scale_psiprime1 = MC_scale_psiprime1*scaledown_psiprime;
      MC_scale_psiprime2 = MC_scale_psiprime2*scaledown_psiprime;

      cout<<(char)27<<"[06;33m"<<      "WARNING!!!!!!! scaling down jpsi     from default by factor: "<<scaledown_jpsi<<(char)27<<"[0m"<<endl;
      MC_scale_jpsi1 = MC_scale_jpsi1*scaledown_jpsi;
      MC_scale_jpsi2 = MC_scale_jpsi2*scaledown_jpsi;

      cout<<(char)27<<"[06;33m"<<      "WARNING!!!!!!! scaling down b        from default by factor: "<<scaledown_b<<(char)27<<"[0m"<<endl;

      MC_scale_b = MC_scale_b*scaledown_b;

      cout<<"acknowledge by pressing return"<<endl;

      if(!autoquit)getchar();
    }

  if( plot_ls && calc_b_frac )
    {
      cout<<(char)27<<"[06;33m"<<"WARNING!!!!!!! both plot_ls AND calc_b_frac are true - this is momentarily impossible - breaking...!"<<(char)27<<"[0m"<<endl;
    }

  if( plot_dists_std && plot_dists_kum )
    {
      cout<<(char)27<<"[06;33m"<<"WARNING!!!!!!! both plot_dists_std AND plot_dists_kum are true - this is not possible - breaking...!"<<(char)27<<"[0m"<<endl;
      break;
    }

  if(gluspli_up != 1.0)
    {
      cout<<(char)27<<"[06;33m"<<"WARNING!!!!!!! scaling bbbar gluon splitting to: "<<MC_scale_b*gluspli_up<<endl;
      cout<<"acknowledge by pressing return"<<(char)27<<"[0m"<<endl;
      if(!autoquit)    getchar();
    }

  if(useccbarincl != .0)
    {
      cout<<(char)27<<"[06;33m"<<"WARNING!!!!!!! Using BAD inclusive ccbar MC scaled by factor: "<<useccbarincl<<" dimufactor: "<<usedimuccbar<<(char)27<<"[0m"<<endl;
    }
  
  Int_t    rebinvalue = 0; // for no rebinning

  // 0 = b-MC,  4 = c-MC,  dataposition = data

  // to be updated when plots are added: 031201
  // second array index: 0 = b-MC,  4 = c-MC,  dataposition = data
  //obj[0 +N*13][] :  h_mmu
  //obj[1 +N*13][] :  h_DR
  //obj[2 +N*13][] :  h_DR_mmu
  //obj[3 +N*13][] :  h_ptmus
  //obj[4 +N*13][] :  h_ptmu
  //obj[5 +N*13][] :  h_dphi
  //obj[6 +N*13][] :  h_muqual
  //obj[7 +N*13][] :  h_mueta
  //obj[8 +N*13][] :  h_calet
  //obj[9 +N*13][] :  h_triggers
  //obj[10+N*13][] :  h_ptasym
  //obj[11+N*13][] :  h_dphii
  //obj[12+N*13][] :  h_deta
  //
  // choose N => lm/hm us/ls
  // N     range
  // ---0-----------
  // 0    all
  // 1    lm_us
  // 2    lm_ls
  // 3    hm_us
  // 4    hm_ls
  // 5... nope!


  // now also below! begin >>>
  // prepared checked types:
  // typechooser = 10; // pt_asym -> Doesn/t work yet - rebinning...
  // typechooser = 7;  // mueta
  // typechooser = 4;  // mupt
  // typechooser = 8;  // calet
  // typechooser = 0;  // mmu
  // typechooser = 1;  // DR
  // typechooser = 6;  // muqual
  // typechooser = 11;  // dphii
  // typechooser = 12;  // deta
  // typechooser = 13;
  // 
  // rangechooser = 3; // hm_us
  // rangechooser = 1; // lm_us // tested only for mmu!!
  // now also below! end <<<
  // will be set below - as nhistos is unknown here.
  // histonr = typechooser + rangechooser*nhistos; // nhistos = 11 for histos v2 (before 031201)
  // histonr = typechooser + rangechooser*nhistos; // nhistos = 13 for histos after 031130

  // old: now renewed above... 031201
  // Int_t histonr = 43; // 43 = pt_asym_hm_us -> Doesn/t work yet - rebinning...
  // Int_t histonr = 40; // 40 = mueta_hm_us
  // Int_t histonr = 37; // 37 = mupt
  // Int_t histonr = 41; // 41 = calet_hm_us
  // Int_t histonr = 33; // 33 = mmu_hm_us
  // Int_t histonr = 18; // 18 = mueta_lm
  // Int_t histonr = 11; // 11 = mmu_lm_us
  // Int_t histonr = 34; // 34 = DR_hm_us
  // Int_t histonr = 39; // 39 = muqual_hm_us
  // Int_t histonr = 39-22; // 39-22 = muqual_lm_us

  //if(histo == mueta_hm_us ) rebinvalue = 4;
  //static const Int_t obj_size_v = 1000;
  //static const Int_t obj_size_h = nfiles+20;
  //TH1D *obj[obj_size_v][obj_size_h];

  TH1D *obj[1000][60];
  
  TKey *key;

// initialise histogram array:

  for(Int_t vorne = 0; vorne<1000; vorne++)
    {
      for(Int_t hinten = 0; hinten<60; hinten++) obj[vorne][hinten] = 0;
    }

  if( during_construction )
    {
//******* CONSTRUCTION WARNING!!!
      cout<<"*******************************************************************************************************"<<endl;
      cout<<"*** CONSTRUCTION WARNING!!! CONSTRUCTION WARNING!!! CONSTRUCTION WARNING!!! CONSTRUCTION WARNING!!! ***"<<endl;
      cout<<"*** CONSTRUCTION WARNING!!! CONSTRUCTION WARNING!!! CONSTRUCTION WARNING!!! CONSTRUCTION WARNING!!! ***"<<endl;
      cout<<"*******************************************************************************************************"<<endl;
    }

  if(dim_fl_exc != 1.0)
    {
//******* FL EXC FUDGED -  WARNING!!!
      cout<<"*******************************************************************************************"<<endl;
      cout<<"*** FL EXC FUDGED -  WARNING!!! FL EXC FUDGED -  WARNING!!! FL EXC FUDGED -  WARNING!!! ***"<<endl;
      cout<<"*** FL EXC FUDGED -  WARNING!!! FL EXC FUDGED -  WARNING!!! FL EXC FUDGED -  WARNING!!! ***"<<endl;
      cout<<"*******************************************************************************************"<<endl;
    }

  for(Int_t i=startfile; i<nfiles; i++) 
    { // here fileloop

      cout<<"i is equal: "<<i<<endl;
      			  	    
      if(i==0)
	{// bpeterson_dir_9900_all_histosv04.root    
	  if(oldfilestyle)    file = new TFile("bpeterson_dir_9900_all_histosv04.root","READ");
	  else                file = new TFile("b_06p-07p_dir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==1)
	{// bpeterson_res_9900_all_histosv04.root    
	  if(oldfilestyle)    file = new TFile("bpeterson_res_9900_all_histosv04.root","READ");
	  else                file = new TFile("b_06p-07p_res.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==2)
	{// bpeterson_exc_g_9900_all_histosv04.root  
	  if(oldfilestyle)    file = new TFile("bpeterson_exc_g_9900_all_histosv04.root","READ");
	  else                file = new TFile("b_06p-07p_exgamma.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==3)
	{// bpeterson_exc_p_9900_all_histosv04.root  
	  if(oldfilestyle)    file = new TFile("bpeterson_exc_p_9900_all_histosv04.root","READ");
	  else                file = new TFile("b_06p-07p_exproton.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout << file->GetName() <<" : file opened" << endl;
	}
      else if(i==4) 
	{// bpeterson_dir_9899_all_histosv04.root    
	  if(oldfilestyle)    file = new TFile("bpeterson_dir_9899_all_histosv04.root","READ");
	  else                file = new TFile("b_05e-06e_dir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout << file->GetName() <<" : file opened" << endl;
	}
      else if(i==5)
	{// bpeterson_res_9899_all_histosv04.root    
	  if(oldfilestyle)    file = new TFile("bpeterson_res_9899_all_histosv04.root","READ");
	  else                file = new TFile("b_05e-06e_res.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==6)
	{// bpeterson_exc_g_9899_all_histosv04.root  
	  if(oldfilestyle)    file = new TFile("bpeterson_exc_g_9899_all_histosv04.root","READ");
	  else                file = new TFile("b_05e-06e_exgamma.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==7)
	{// bpeterson_exc_p_9899_all_histosv04.root  
	  if(oldfilestyle)    file = new TFile("bpeterson_exc_p_9899_all_histosv04.root","READ");
	  else                file = new TFile("b_05e-06e_exproton.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==8)
	{// bpeterson_dir_9697_all_histosv04.root    
	  if(oldfilestyle)    file = new TFile("bpeterson_dir_9697_all_histosv04.root","READ");
	  else                file = new TFile("b_03p-04p_dir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==9)
	{// bpeterson_res_9697_all_histosv04.root    
	  if(oldfilestyle)    file = new TFile("bpeterson_res_9697_all_histosv04.root","READ");
	  else                file = new TFile("b_03p-04p_res.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==10)
	{// bpeterson_exc_g_9697_all_histosv04.root  
	  if(oldfilestyle)    file = new TFile("bpeterson_exc_g_9697_all_histosv04.root","READ");
	  else                file = new TFile("b_03p-04p_exgamma.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==11)
	{// bpeterson_exc_p_9697_all_histosv04.root  
	  if(oldfilestyle)    file = new TFile("bpeterson_exc_p_9697_all_histosv04.root","READ");
	  else                file = new TFile("b_03p-04p_exproton.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==12)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_06p-07p_dir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==13)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_06p-07p_exgamma.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==14)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_06p-07p_exproton.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==15)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_06p-07p_res.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==16)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_05e-06e_dir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==17)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_05e-06e_exgamma.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==18)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_05e-06e_exproton.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==19)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_05e-06e_res.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==20)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_03p-04p_dir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==21)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_03p-04p_exgamma.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==22)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_03p-04p_exproton.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==23)
	{// ccbar
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_03p-04p_res.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==24)
	{// ccbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_03p-04p_dirrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==25)
	{// ccbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_05e-06e_dirrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==26)
	{// ccbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_06p-07p_dirrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==27)
	{// ccbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_03p-04p_resrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==28)
	{// ccbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_05e-06e_resrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==29)
	{// ccbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("c_06p-07p_resrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==30)
	{// all_BH_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_BH_fudge_040615_extr.root","READ");
	  else                file = new TFile("BH_DIS.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==31)
	{// all_BH_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_BH_fudge_040615_extr.root","READ");
	  else                file = new TFile("BH_elastic.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==32)
	{// all_BH_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_BH_fudge_040615_extr.root","READ");
	  else                file = new TFile("BH_inelastic.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==33)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("jpsi1.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==34)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("jpsi2.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==35)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("psiprime1.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==36)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("psiprime2.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==37)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("upsilon_1sdir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==38)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("upsilon_2sdir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==39)
	{// all_jpsi_hrw_fudge_040615_extr.root
	  if(oldfilestyle)    file = new TFile("all_jpsi_hrw_fudge_040615_extr.root","READ");
	  else                file = new TFile("upsilon_3sdir.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==40)
	{// bbbb Madgraph
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("bbbb.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==41)
	{// cccc Madgraph
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("cccc.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==42)
	{// bbcc Madgraph
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("bbcc.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==43)
	{// bbbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("b_03p-04p_dirrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==44)
	{// bbbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("b_05e-06e_dirrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==45)
	{// bbbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("b_06p-07p_dirrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==46)
	{// bbbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("b_03p-04p_resrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==47)
	{// bbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("b_05e-06e_resrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else if(i==48)
	{// bbbar Rapgap
	  if(oldfilestyle)    file = new TFile("doesnotexist.root","READ");
	  else                file = new TFile("b_06p-07p_resrap.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	} 
      else if(i==49)
	{// batch101to106_all_histosv04.root
	  if(oldfilestyle)    file = new TFile("0307p.root","READ");
	  else                file = new TFile("0307p.root","READ");
	  TIter next( file->GetListOfKeys() );
	  count1=0;
	  cout <<  file->GetName() <<" : file opened" << endl;
	}
      else
	{ 
	  cout << "bad filenames given, i has value: "<< i << endl;
	}

      while ((key = (TKey *) next()))
	{
	  obj[count1][i] = (TH1D*) file->Get(key->GetName()); // copy object to memory
	  obj[count1][i] -> SetDirectory(0);
// do something with obj
	  if( previous_obj==key->GetName() )
	    {
	      continue;
	    } 
	  previous_obj = key->GetName();
	  count1++;
	}
      file->Close();
    }



// reweight MC histos and add the reweighted ones:

  cout<<"Start reweighting and adding MC histos..."<<endl;

  for(Int_t j=startfile; j<nfiles; j++)
    {
      for(Int_t k=0; k<count1; k++)
	{
	  cout<<".";
         
//*****************Luminosities for MC Samples*******************
// 			03/04       05/06          06/07
//---------------------------------------------------------------
// incl bbbar 	 	
// DIR		       371.61       1797.44        1558.53
// RES		       352.91       1785.22        1555.75
// EXCG		       465.53       1829.81        1416.72
// EXCP		       389.95       1836.76        1736.66
//
//incl ccbar
// DIR                  40.59        190.12         145.90
// EXCG                 40.59        190.12         145.90
// EXCP                 40.59        190.12         145.90
// RES                  40.59        190.12         145.90


//       if(j==00)  obj[k][j]->Scale( MC_scale_b *(data_lumi_06_07/            1558.53 ) ); // b_06p-07p_dir.root  
//       if(j==01)  obj[k][j]->Scale( MC_scale_b *(data_lumi_06_07/            1555.75 ) ); // b_06p-07p_res.root
//       if(j==02)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_06_07/ 1416.72 ) ); // b_06p-07p_exgamma.root  
//       if(j==03)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_06_07/ 1736.66 ) ); // b_06p-07p_exproton.root
// 
//       if(j==04)  obj[k][j]->Scale( MC_scale_b *(data_lumi_05_06/            1797.44 ) ); // b_05e-06e_dir.root  
//       if(j==05)  obj[k][j]->Scale( MC_scale_b *(data_lumi_05_06/            1785.22 ) ); // b_05e-06e_res.root  
//       if(j==06)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_05_06/ 1829.81 ) ); // b_05e-06e_exgamma.root
//       if(j==07)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_05_06/ 1836.76 ) ); // b_05e-06e_exproton.root
// 
//       if(j==08)  obj[k][j]->Scale( MC_scale_b *(data_lumi_03_04/            371.61 ) ); // b_03p-04p_dir.root  
//       if(j==09)  obj[k][j]->Scale( MC_scale_b *(data_lumi_03_04/            352.91 ) ); // b_03p-04p_res.root 
//       if(j==10)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_03_04/ 465.53 ) ); // b_03p-04p_exgamma.root 
//       if(j==11)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_03_04/ 389.95 ) ); // b_03p-04p_exproton.root
//  					     
//       if(j==12)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_dir.root      
//       if(j==13)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_res.root       
//       if(j==14)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_exgamma.root 
//       if(j==15)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_exproton.root 
// 
//       if(j==16)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_dir.root      
//       if(j==17)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_res.root
//       if(j==18)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_exgamma.root   
//       if(j==19)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_exproton.root      
// 
//       if(j==20)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_dir.root      
//       if(j==21)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_res.root  
//       if(j==22)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_exgamma.root 
//       if(j==23)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_exproton.root      
// 
//       if(j==24)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_03_04/ 124.491  ) ); // c_03p-04p_dirrap.root
//       if(j==25)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_05_06/ 449.839  ) ); // c_05e-06e_dirrap.root
//       if(j==26)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_06_07/ 498.047  ) ); // c_06p-07p_dirrap.root
//       if(j==27)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_03_04/  41.444  ) ); // c_03p-04p_resrap.root
//       if(j==28)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_05_06/ 202.371  ) ); // c_05e-06e_resrap.root
//       if(j==29)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_06_07/ 498.113  ) ); // c_06p-07p_resrap.root
// 
//       if(j==30)  obj[k][j]->Scale( MC_scale_BH_DIS        *(data_lumi/       21808.51 ) ); // BH_DIS.root
//       if(j==31)  obj[k][j]->Scale( MC_scale_BH_ela        *(data_lumi/        1546.21 ) ); // BH_elastic.root
//       if(j==32)  obj[k][j]->Scale( MC_scale_BH_inela      *(data_lumi/        2740.01 ) ); // BH_inelastic.root
//       if(j==33)  obj[k][j]->Scale( MC_scale_jpsi1         *(data_lumi/        7144.6  ) ); // jpsi1.root
//       if(j==34)  obj[k][j]->Scale( MC_scale_jpsi2         *(data_lumi/         414.07 ) ); // jpsi2.root
//       if(j==35)  obj[k][j]->Scale( MC_scale_psiprime1     *(data_lumi/        5916.6  ) ); // psiprime1.root
//       if(j==36)  obj[k][j]->Scale( MC_scale_psiprime2     *(data_lumi/      581.39536 ) ); // psiprime2.root
//       if(j==37)  obj[k][j]->Scale( MC_scale_ups1          *(data_lumi/        357.608 ) ); // upsilon_1sdir.root
//       if(j==38)  obj[k][j]->Scale( MC_scale_ups2          *(data_lumi/        357.608 ) ); // upsilon_2sdir.root
//       if(j==39)  obj[k][j]->Scale( MC_scale_ups3          *(data_lumi/        357.608 ) ); // upsilon_3sdir.root
// 
//       if(j==40)  obj[k][j]->Scale( MC_scale_bbbb          *(data_lumi/        3815.8  ) ); // bbbb.root
//       if(j==41)  obj[k][j]->Scale( MC_scale_cccc          *(data_lumi/         743.02 ) ); // cccc.root
//       if(j==42)  obj[k][j]->Scale( MC_scale_bbcc          *(data_lumi/        3718.99 ) ); // bbcc.root
//     
//       if(j==43)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_03_04/ 1167.787 ) ); // b_03p-04p_dirrap.root
//       if(j==44)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_05_06/ 3040.652 ) ); // b_05e-06e_dirrap.root
//       if(j==45)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_06_07/ 2577.944 ) ); // b_06p-07p_dirrap.root
//       if(j==46)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_03_04/ 1167.247 ) ); // b_03p-04p_resrap.root
//       if(j==47)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_05_06/ 3039.42  ) ); // b_05e-06e_resrap.root
//       if(j==48)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_06_07/ 2500.    ) ); // b_06p-07p_resrap.root


/// N.Stefaniuk , modified charm lumi , due to thesis: 

      if(j==00)  obj[k][j]->Scale( MC_scale_b *(data_lumi_06_07/            1558.53 ) ); // b_06p-07p_dir.root  
      if(j==01)  obj[k][j]->Scale( MC_scale_b *(data_lumi_06_07/            1555.75 ) ); // b_06p-07p_res.root
      if(j==02)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_06_07/ 1416.72 ) ); // b_06p-07p_exgamma.root  
      if(j==03)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_06_07/ 1763.66 ) ); // b_06p-07p_exproton.root

      if(j==04)  obj[k][j]->Scale( MC_scale_b *(data_lumi_05_06/            1797.44 ) ); // b_05e-06e_dir.root  
      if(j==05)  obj[k][j]->Scale( MC_scale_b *(data_lumi_05_06/            1785.22 ) ); // b_05e-06e_res.root
      if(j==06)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_05_06/ 1829.81 ) ); // b_05e-06e_exgamma.root  
      if(j==07)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_05_06/ 1836.76 ) ); // b_05e-06e_exproton.root

      if(j==08)  obj[k][j]->Scale( MC_scale_b *(data_lumi_03_04/            371.62 ) ); // b_03p-04p_dir.root  
      if(j==09)  obj[k][j]->Scale( MC_scale_b *(data_lumi_03_04/            352.91 ) ); // b_03p-04p_res.root
      if(j==10)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_03_04/ 465.53 ) ); // b_03p-04p_exgamma.root  
      if(j==11)  obj[k][j]->Scale( dim_fl_exc*MC_scale_b *(data_lumi_03_04/ 389.95 ) ); // b_03p-04p_exproton.root
 					     
      if(j==12)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_dir.root      
      if(j==13)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_res.root      
      if(j==14)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_exgamma.root   
      if(j==15)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_06_07/ 145.90  ) ); // c_06p-07p_exproton.root 

      if(j==16)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_dir.root      
      if(j==17)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_res.root      
      if(j==18)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_exgamma.root 
      if(j==19)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_05_06/ 190.12  ) ); // c_05e-06e_exproton.root *

      if(j==20)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_dir.root       +
      if(j==21)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_res.root       +
      if(j==22)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_exgamma.root   +
      if(j==23)  obj[k][j]->Scale( useccbarincl*MC_scale_c *(data_lumi_03_04/  40.59  ) ); // c_03p-04p_exproton.root  +

      if(j==24)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_03_04/ 124.491  ) ); // c_03p-04p_dirrap.root    
      if(j==25)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_05_06/ 449.839  ) ); // c_05e-06e_dirrap.root
      if(j==26)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_06_07/ 498.042  ) ); // c_06p-07p_dirrap.root
      if(j==27)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_03_04/ 41.444   ) ); // c_03p-04p_resrap.root
      if(j==28)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_05_06/ 202.275  ) ); // c_05e-06e_resrap.root
      if(j==29)  obj[k][j]->Scale( rapgapscale*MC_scale_c *(data_lumi_06_07/ 498.085  ) ); // c_06p-07p_resrap.root

      if(j==30)  obj[k][j]->Scale( MC_scale_BH_DIS        *(data_lumi/        22379.51) ); // BH_DIS.root	+
      if(j==31)  obj[k][j]->Scale( MC_scale_BH_ela        *(data_lumi/        1546.21 ) ); // BH_elastic.root	+
      if(j==32)  obj[k][j]->Scale( MC_scale_BH_inela      *(data_lumi/        2740.01 ) ); // BH_inelastic.root	+
      if(j==33)  obj[k][j]->Scale( MC_scale_jpsi1         *(data_lumi/        6986.   ) ); // jpsi1.root	+
      if(j==34)  obj[k][j]->Scale( MC_scale_jpsi2         *(data_lumi/         414.07 ) ); // jpsi2.root	+
      if(j==35)  obj[k][j]->Scale( MC_scale_psiprime1     *(data_lumi/        5916.6  ) ); // psiprime1.root	+
      if(j==36)  obj[k][j]->Scale( MC_scale_psiprime2     *(data_lumi/      581.39536 ) ); // psiprime2.root	+
      if(j==37)  obj[k][j]->Scale( MC_scale_ups1          *(data_lumi/        357.608 ) ); // upsilon_1sdir.root +
      if(j==38)  obj[k][j]->Scale( MC_scale_ups2          *(data_lumi/        357.608 ) ); // upsilon_2sdir.root +
      if(j==39)  obj[k][j]->Scale( MC_scale_ups3          *(data_lumi/        357.608 ) ); // upsilon_3sdir.root +

      if(j==40)  obj[k][j]->Scale( MC_scale_bbbb          *(data_lumi/        3815.8  ) ); // bbbb.root
      if(j==41)  obj[k][j]->Scale( MC_scale_cccc          *(data_lumi/         743.02 ) ); // cccc.root
      if(j==42)  obj[k][j]->Scale( MC_scale_bbcc          *(data_lumi/        3718.99 ) ); // bbcc.root
    
      if(j==43)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_03_04/ 1167.787 ) ); // b_03p-04p_dirrap.root
      if(j==44)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_05_06/ 3040.73  ) ); // b_05e-06e_dirrap.root
      if(j==45)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_06_07/ 2577.939 ) ); // b_06p-07p_dirrap.root
      if(j==46)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_03_04/ 1167.247 ) ); // b_03p-04p_resrap.root
      if(j==47)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_05_06/ 3040.524 ) ); // b_05e-06e_resrap.root
      if(j==48)  obj[k][j]->Scale( rapgapscale*MC_scale_b *(data_lumi_06_07/ 2574.08  ) ); // b_06p-07p_resrap.root



// add lumi-reweighted beauty histos to first beauty histo sample:

      if(j!=0 && j!=dataposition && (j<charmbegin || j>charmend) && j!=bbbb_position && j!=cccc_position && j!=bbcc_position )
	{ 
	  obj[k][0]->Add(obj[k][j],1); // ccbar MC is added later on below!
	}

//add lumi-reweighted charm histos to first charm histo sample:
      if(j!=0 && j!=dataposition &&  j!=charmbegin && !(j<charmbegin || j>charmend) && j!=BH_position1 && j!=BH_position2 && j!=BH_position3 && j!= jpsi_position1 && j!= jpsi_position2 && j!= psiprime_position1 && j!= psiprime_position2 && j!= ups1_position && j!= ups2_position && j!= ups3_position && j!=bbbb_position && j!=cccc_position && j!=bbcc_position )
	{
	  obj[k][charmbegin]->Add(obj[k][j],1); // ccbar MC is added to ccbar MC here - added to total MC estimate later!
	}
    }
  }

  cout<<endl<<"Done reweighting and adding MC histos."<<endl;

  Int_t  pl_range = 1;         // set equal nhistos below
  Bool_t plot_good, lastplot;

  // prepared checked types:
  // typechooser = 0;  // mmu
  // typechooser = 1;  // DR
  // typechooser = 4;  // mupt
  // typechooser = 6;  // muqual
  // typechooser = 7;  // mueta
  // typechooser = 8;  // calet
  // typechooser = 10; // pt_asym -> Doesn/t work yet - rebinning...
  // typechooser = 11;  // dphii
  // typechooser = 12;  // deta
  // typechooser = 13;
  // //
  // ***************************************
  // choose low mass (1) / high mass (3) range here:
  // also is, nis or nisandis
  // ***************************************

  if(plot_hm)rangechooser = 3; // hm_us
  else       rangechooser = 1; // lm_us

  if(iso_chooser == "nis")
    { 
      cout<<"Thinking you want iso range: nis"<<endl;    
      rangechooser+=8; 
    }
  else if(iso_chooser == "is")
    {
      cout<<"Thinking you want iso range: is"<<endl;    
      rangechooser+=4;
    }
  else if(iso_chooser == "nisandis")
    {
      cout<<"Thinking you want iso range: nisandis"<<endl;    
      rangechooser+=0; // good - +4 works 
    }
  else
    {//    rangechooser+=4;
      cout<<endl<<"*** ERROR! no proper iso range chosen - exiting"<<endl<<endl;
      cout<<"Possible isolation choices are: nis, is & nisandis"<<endl;
      break;
    }
  if(!(rangechooser == 3 || rangechooser == 1 || rangechooser == 7 || rangechooser == 5|| rangechooser == 11 || rangechooser == 9 ))
    {
      cout<<"*** Error: ! No range (hm or lm) chosen - exiting."<<endl;
      break;
    }

  nhistos  = count1/nrows;
  pl_range = nhistos;

  TH1D* hm_us_bMC[1000];
  TH1D* hm_ls_data[1000];
  TH1D* hm_ls_bMC_lfl[1000];
  TH1D* hm_us_bMC_buffer[1000];
  TH1D* hm_ls_bMC_buffer[1000];
  TH1D* bMC_u_plus_l[1000];
  TH1D* bMC_u_minus_l[1000];
  TH1D* cMC_orig[1000];
  TH1D* b_frac[1000];
  TH1D* b_acc[1000];
  TH1D* b_MCrec[1000];
  TH1D* b_xsec[1000];
  TH1D* xsec_buffer[1000];
  TH1D* Charm_MC_p_lfl_bg[1000];
  TH1D* jpsi_p_Charm_MC_p_lfl_bg[1000];
  TH1D* lfl_bg_us[1000];
  TH1D* lfl_bg_ls[1000];
  TH1D* hm_ls_bMC[1000];
  TH1D* orig_true[1000];
  TH1D* BH_p_jpsi_p_Charm_MC_p_lfl_bg[1000];
  TH1D* hm_us_bbbbMC[1000];
  TH1D* hm_ls_bbbbMC[1000];
  TH1D* hm_us_ccccMC[1000];
  TH1D* hm_ls_ccccMC[1000];
  TH1D* hm_us_bbccMC[1000];
  TH1D* hm_ls_bbccMC[1000];

  TH1D* bbbar_us[1000];
  TH1D* bbbar_ls[1000];
  TH1D* hm_ls_jpsi_and[1000];
  TH1D* hm_us_jpsi_and[1000];
  TH1D* ccbar_us[1000];
  TH1D* ccbar_ls[1000];

  TString title, histoname;
  /// changed!!! 
  for(Int_t plotss = 0; plotss < /*1 */pl_range; plotss++)
    { // plotting loop start >>>
      title =obj[plotss+rangechooser*nhistos][dataposition]->GetTitle(); 

      cout<<"plotss: "<<plotss<<" Name: "<<obj[plotss+rangechooser*nhistos][dataposition]->GetName()<<" Title: "<<obj[plotss+rangechooser*nhistos][dataposition]->GetTitle()<<endl;

// set histonr form type and rangechooser:

	  typechooser = plotss;
	  histonr     = typechooser + rangechooser*nhistos;

 
///	  hm_us_bMC_buffer[plotss]  = (TH1D*) obj[histonr][0]         ->Clone("hm_us_bMC_buffer");
///	  hm_ls_bMC_buffer[plotss]  = (TH1D*) obj[histonr+nhistos][0] ->Clone("hm_ls_bMC_buffer");

// set rebinvalues individually for each histo type:
	  strbuffer = obj[histonr][dataposition]->GetName();

	  if( strbuffer.Contains("mmu") )
	    {
	      if( strbuffer.Contains("lm") )          rebinvalue = 16;
	      else if(strbuffer.Contains("hm_us_is")) rebinvalue = 20;
	      else                                    rebinvalue = 12;  // choose 10 for comparison with achim 05012
 
	      rebinvalue = 0;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("DR") )
	    {
	      rebinvalue = 2;
	      MC_first = false;
	    }

	  else if( strbuffer.Contains("ptmu") )
	    {
	      rebinvalue = 2;

	      if(fromoli && (!(iso_chooser == "is") || !plot_hm) ) rebinvalue = 2;
	      if(fromoli && (  iso_chooser == "is") &&  plot_hm)   rebinvalue = 3;

	      MC_first = false;
	    }
	  else if( strbuffer.Contains("mueta") && !(strbuffer.Contains("dimueta")))
	    {
	      rebinvalue = 2*2*2;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("dimueta"))
	    {
	    rebinvalue = 2*2*2;
	    MC_first = false;
	    }
	  else if( strbuffer.Contains("calet") )
	    {
	      rebinvalue = 5;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("ptasym") )
	    {
	      rebinvalue = 0;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("dphii") )
	    {
	      rebinvalue = 0; 
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("deta") )
	    {
	      rebinvalue = 2;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("thrust") && !strbuffer.Contains("ptrel") )
	    {
	      rebinvalue = 2;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("dimuphi")  )
	    {
	      rebinvalue = 10;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("ptrel") )
	    {
	      rebinvalue = 0;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("sqsum") )
	    {
	      rebinvalue = 6;
	      MC_first = false;
	    }
	  else if( strbuffer.Contains("cal_et") )
	    {
	      rebinvalue = 4;
	      MC_first = false;
	    }
	  else
	    {
	      rebinvalue = 0;
	      MC_first = false;
	    }
  
// do some proper adding (only MC and bg estimates are modified, data is left alone)
	
// entries = 0.;
// cout<<endl<<" b bbar MC : "<<obj[histonr][0]->GetName()<<endl;
// for (Int_t i=1;i<=obj[histonr][0]->GetNbinsX();i++) {entries = entries + obj[histonr][0]->GetBinContent(i);}
// cout<<" b bbar MC Ent (us) =  "<<entries<<" Nbins = "<<obj[histonr][0]->GetNbinsX()<<endl;

bbbar_us[plotss] = (TH1D*) obj[histonr][0]->Clone("bbbar_us");
bbbar_ls[plotss] = (TH1D*) obj[histonr+nhistos][0]->Clone("bbbar_ls");


ccbar_us[plotss] = (TH1D*) obj[histonr][charmbegin]->Clone("ccbar_us");
ccbar_ls[plotss] = (TH1D*) obj[histonr+nhistos][charmbegin]->Clone("ccbar_ls");


// charmsubmarker
// prepare charm MC. Subtract charm like sign part ("fake") from charm unlike sign ("real"):
// WARNING: Now (050410) charm contains open charm only! NO jpsi, psiprime, thus ls bg is subtracted for them here too.

histoname=obj[histonr+nhistos][jpsi_position1]->GetName();

	      hm_ls_jpsi_and[plotss]   = (TH1D*) obj[histonr+nhistos][jpsi_position1]->Clone(histoname);
	      hm_ls_jpsi_and[plotss]     ->Add(obj[histonr+nhistos][jpsi_position2],1);
	      hm_ls_jpsi_and[plotss] 	 ->Add(obj[histonr+nhistos][psiprime_position1],1);
	      hm_ls_jpsi_and[plotss] 	 ->Add(obj[histonr+nhistos][psiprime_position2],1);
	      hm_ls_jpsi_and[plotss]       ->Add(obj[histonr+nhistos][BH_position1],1);
	      hm_ls_jpsi_and[plotss]       ->Add(obj[histonr+nhistos][BH_position2],1);
	      hm_ls_jpsi_and[plotss]       ->Add(obj[histonr+nhistos][BH_position3],1);
	      hm_ls_jpsi_and[plotss]      ->Add(obj[histonr+nhistos][ups1_position],1);
	      hm_ls_jpsi_and[plotss]      ->Add(obj[histonr+nhistos][ups2_position],1);
	      hm_ls_jpsi_and[plotss]      ->Add(obj[histonr+nhistos][ups3_position],1);
// 
histoname=obj[histonr][jpsi_position1]->GetName();
	      hm_us_jpsi_and[plotss]   = (TH1D*) obj[histonr][jpsi_position1]->Clone(histoname);
	      hm_us_jpsi_and[plotss]     ->Add(obj[histonr][jpsi_position2],1);
	      hm_us_jpsi_and[plotss] 	 ->Add(obj[histonr][psiprime_position1],1);
	      hm_us_jpsi_and[plotss] 	 ->Add(obj[histonr][psiprime_position2],1);
	      hm_us_jpsi_and[plotss]       ->Add(obj[histonr][BH_position1],1);
	      hm_us_jpsi_and[plotss]       ->Add(obj[histonr][BH_position2],1);
	      hm_us_jpsi_and[plotss]       ->Add(obj[histonr][BH_position3],1);
	      hm_us_jpsi_and[plotss]      ->Add(obj[histonr][ups1_position],1);
	      hm_us_jpsi_and[plotss]      ->Add(obj[histonr][ups2_position],1);
	      hm_us_jpsi_and[plotss]      ->Add(obj[histonr][ups3_position],1);


// hm_us_jpsi_and[plotss]->Add(hm_ls_jpsi_and[plotss],-1);

	  lfl_bg_us[plotss] = (TH1D*) obj[histonr+nhistos][dataposition]->Clone("lfl_bg_us");
	  lfl_bg_ls[plotss] = (TH1D*) obj[histonr+nhistos][dataposition]->Clone("lfl_bg_ls");

	  lfl_bg_us[plotss]->Add(obj[histonr+nhistos][0],-1);
	  lfl_bg_ls[plotss]->Add(obj[histonr+nhistos][0],-1); 	

	  if(plot_hm) us_bg_corr = 1.01;
	  else us_bg_corr = 1.04;

/*
/// lfl corrections for 2% and 6%

// lfl nevents                                                                   // from hm_ls data = lfl_ls_bg = lfl_us_bg
entries = 0.;
nbins = 0;

nbins = lfl_bg_us[plotss]->GetXaxis()->GetNbins();
for (Int_t i=1;i<=nbins;i++) {entries = entries + lfl_bg_us[plotss]->GetBinContent(i);}
histoname = lfl_bg_us[plotss]->GetName();
cout<< "Entries = "<<entries<<" for hist : "<<histoname<<endl;

// correct for small ls us asymetry:
	  if(plot_hm) us_bg_corr = 1.02;
	  else us_bg_corr = 1.06;

// 	  if(plot_hm) us_bg_corr = 1.00;
// 	  else us_bg_corr = 1.00;

Delta_lfl = (us_bg_corr - 1.)*entries;
cout<< " Delta_lfl = "<<Delta_lfl<<endl; 

// bb Nevents ls
entries = 0.;
nbins = 0;
Delta_bb =0.;

nbins = bbbar_ls[plotss]->GetXaxis()->GetNbins();
for (Int_t i=1;i<=nbins;i++) {entries = entries + bbbar_ls[plotss]->GetBinContent(i);}
histoname = bbbar_ls[plotss]->GetName();
Delta_bb = (entries-Delta_lfl)/entries;
bbbar_ls[plotss]->Scale(Delta_bb);
cout<<" Delta_bb ls = "<<Delta_bb<<endl;
cout<< "Entries ls bb = "<<entries<<" for hist : "<<histoname<<endl;

// entries = 0.;
// nbins = 0;
// nbins = bbbar_ls[plotss]->GetXaxis()->GetNbins();
// for (Int_t i=1;i<=nbins;i++) {entries = entries + bbbar_ls[plotss]->GetBinContent(i);}
// cout<< "Entries ls bb new = "<<entries<<" for hist : "<<histoname<<endl;

// bb Nevents us
entries = 0.;
nbins = 0;
Delta_bb =0.;

nbins = bbbar_us[plotss]->GetXaxis()->GetNbins();
for (Int_t i=1;i<=nbins;i++) {entries = entries + bbbar_us[plotss]->GetBinContent(i);}
histoname = bbbar_us[plotss]->GetName();
Delta_bb = (entries-Delta_lfl)/entries;
bbbar_us[plotss]->Scale(Delta_bb);
cout<<" Delta_bb us = "<<Delta_bb<<endl;
cout<< "Entries us bb = "<<entries<<" for hist : "<<histoname<<endl;

// entries = 0.;
// nbins = 0;
// nbins = bbbar_us[plotss]->GetXaxis()->GetNbins();
// for (Int_t i=1;i<=nbins;i++) {entries = entries + bbbar_us[plotss]->GetBinContent(i);}
// cout<< "Entries us bb new = "<<entries<<" for hist : "<<histoname<<endl;

*/
	  lfl_bg_us[plotss]->Scale(us_bg_corr);
// 	  lfl_bg_ls[plotss]->Scale(us_bg_corr);

	  if(plot_dists_kum)
	    {// some plotting...

	      if(rebinvalue > 0) 
		{
		  obj[histonr][dataposition]->Rebin(rebinvalue);
		  obj[histonr+nhistos][dataposition]->Rebin(rebinvalue);
		}

	      histoname=obj[histonr][dataposition]->GetName();
	      histoname.Append("_data");
	      gInclude->DumpHisto((TH1D*)obj[histonr][dataposition]->Clone(histoname),histoname);

	      histoname=obj[histonr+nhistos][dataposition]->GetName();
	      histoname.Append("_data");
	      gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][dataposition]->Clone(histoname),histoname);	 
	

entries = 0.;
cout<<endl<<" DATA : "<<obj[histonr][dataposition]->GetName()<<endl;
for (Int_t i=1;i<=obj[histonr][dataposition]->GetNbinsX();i++) {entries = entries + obj[histonr][dataposition]->GetBinContent(i);}
cout<<" DATA Ent (us) =  "<<entries<<" Nbins = "<<obj[histonr][dataposition]->GetNbinsX()<<endl;

entries = 0.;
cout<<endl<<" DATA : "<<obj[histonr+nhistos][dataposition]->GetName()<<endl;
for (Int_t i=1;i<=obj[histonr+nhistos][dataposition]->GetNbinsX();i++) {entries = entries + obj[histonr+nhistos][dataposition]->GetBinContent(i);}
cout<<" DATA Ent (ls) =  "<<entries<<" Nbins = "<<obj[histonr+nhistos][dataposition]->GetNbinsX()<<endl;


	      if(rebinvalue > 0)
		{
		  bbbar_us[plotss]->Rebin(rebinvalue);
		  bbbar_ls[plotss]->Rebin(rebinvalue);
		}
// total sum is shown rear red - is the kum beauty. old: us MC (b + c + jpsi + Y + BH + bg_estim.)
	      histoname=obj[histonr][dataposition]->GetName();
	      histoname.Append("_allMC_sum");
	      gInclude->DumpHisto((TH1D*)bbbar_us[plotss]->Clone(histoname),histoname);

	      histoname=obj[histonr+nhistos][dataposition]->GetName();
	      histoname.Append("_allMC_sum");
	      gInclude->DumpHisto((TH1D*)bbbar_ls[plotss]->Clone(histoname),histoname);

entries = 0.;
cout<<endl<<" bbar MC : "<<bbbar_us[plotss]->GetName()<<endl;
for (Int_t i=1;i<=bbbar_us[plotss]->GetNbinsX();i++) {entries = entries + bbbar_us[plotss]->GetBinContent(i);}
cout<<" bbar MC (us) =  "<<entries<<" Nbins = "<<bbbar_us[plotss]->GetNbinsX()<<endl;

entries = 0.;
cout<<endl<<" bbar MC : "<<bbbar_ls[plotss]->GetName()<<endl;
for (Int_t i=1;i<=bbbar_ls[plotss]->GetNbinsX();i++) {entries = entries + bbbar_ls[plotss]->GetBinContent(i);}
cout<<" bbar MC (ls) =  "<<entries<<" Nbins = "<<bbbar_ls[plotss]->GetNbinsX()<<endl;


//Quarkonia

	      if(rebinvalue > 0)
		{
		  hm_us_jpsi_and[plotss]->Rebin(rebinvalue);
		  hm_ls_jpsi_and[plotss]->Rebin(rebinvalue);
 	  	}

	      histoname=obj[histonr][dataposition]->GetName();
	      histoname.Append("_allMC_m_charm_sum");
	      gInclude->DumpHisto((TH1D*)hm_us_jpsi_and[plotss]->Clone(histoname),histoname);

	      histoname=obj[histonr+nhistos][dataposition]->GetName();
	      histoname.Append("_allMC_m_charm_sum");
	      gInclude->DumpHisto((TH1D*)hm_ls_jpsi_and[plotss]->Clone(histoname),histoname);

entries = 0.;
cout<<endl<<" Jpsi_and MC : "<<hm_us_jpsi_and[plotss]->GetName()<<endl;
for (Int_t i=1;i<=hm_us_jpsi_and[plotss]->GetNbinsX();i++) {entries = entries + hm_us_jpsi_and[plotss]->GetBinContent(i);}
cout<<" Jpsi_and MC (us) =  "<<entries<<" Nbins = "<<hm_us_jpsi_and[plotss]->GetNbinsX()<<endl;

entries = 0.;
cout<<endl<<" Jpsi_and MC : "<<hm_ls_jpsi_and[plotss]->GetName()<<endl;
for (Int_t i=1;i<=hm_ls_jpsi_and[plotss]->GetNbinsX();i++) {entries = entries + hm_ls_jpsi_and[plotss]->GetBinContent(i);}
cout<<" Jpsi_and MC (ls) =  "<<entries<<" Nbins = "<<hm_ls_jpsi_and[plotss]->GetNbinsX()<<endl;


	      if(rebinvalue > 0)
		{
		  ccbar_us[plotss]->Rebin(rebinvalue);
		  ccbar_ls[plotss]->Rebin(rebinvalue);
		}
// total sum is shown rear red - is the kum beauty. old: us MC (b + c + jpsi + Y + BH + bg_estim.)
	      histoname=obj[histonr][dataposition]->GetName();
	      histoname.Append("_MC_c_p_lflbg_sum");
	      gInclude->DumpHisto((TH1D*)ccbar_us[plotss]->Clone(histoname),histoname);

	      histoname=obj[histonr+nhistos][dataposition]->GetName();
	      histoname.Append("_MC_c_p_lflbg_sum");
	      gInclude->DumpHisto((TH1D*)ccbar_ls[plotss]->Clone(histoname),histoname);

entries = 0.;
cout<<endl<<" ccbar MC : "<<ccbar_us[plotss]->GetName()<<endl;
for (Int_t i=1;i<=ccbar_us[plotss]->GetNbinsX();i++) {entries = entries + ccbar_us[plotss]->GetBinContent(i);}
cout<<" ccbar MC (us) =  "<<entries<<" Nbins = "<<ccbar_us[plotss]->GetNbinsX()<<endl;

entries = 0.;
cout<<endl<<" ccar MC : "<<ccbar_ls[plotss]->GetName()<<endl;
for (Int_t i=1;i<=ccbar_ls[plotss]->GetNbinsX();i++) {entries = entries + ccbar_ls[plotss]->GetBinContent(i);}
cout<<" ccbar MC (ls) =  "<<entries<<" Nbins = "<<ccbar_ls[plotss]->GetNbinsX()<<endl;

// lfl_bg_us[plotss]

	      if(rebinvalue > 0) 
		{
		lfl_bg_us[plotss]->Rebin(rebinvalue); 
		lfl_bg_ls[plotss]->Rebin(rebinvalue); 
		}

	      histoname=obj[histonr][dataposition]->GetName();
	      histoname.Append("_MC_lflbg_sum");
	      gInclude->DumpHisto((TH1D*)lfl_bg_us[plotss]->Clone(histoname),histoname);

	      histoname=obj[histonr+nhistos][dataposition]->GetName();
	      histoname.Append("_MC_lflbg_sum");
	      gInclude->DumpHisto((TH1D*)lfl_bg_ls[plotss]->Clone(histoname),histoname);


entries = 0.;
cout<<endl<<" lfl MC : "<<lfl_bg_us[plotss]->GetName()<<endl;
for (Int_t i=1;i<=lfl_bg_us[plotss]->GetNbinsX();i++) {entries = entries + lfl_bg_us[plotss]->GetBinContent(i);}
cout<<" lfl MC (us) =  "<<entries<<" Nbins = "<<lfl_bg_us[plotss]->GetNbinsX()<<endl;

entries = 0.;
cout<<endl<<" lfl MC : "<<lfl_bg_ls[plotss]->GetName()<<endl;
for (Int_t i=1;i<=lfl_bg_ls[plotss]->GetNbinsX();i++) {entries = entries + lfl_bg_ls[plotss]->GetBinContent(i);}
cout<<" lfl MC (ls) =  "<<entries<<" Nbins = "<<lfl_bg_ls[plotss]->GetNbinsX()<<endl;

// us data draw again, to be there as top layer
/*
	      if((plot_dists_std || plot_dists_kum) && plot_ls)
		{
		  cc->cd(1);
		  hm_ls_data[plotss]->SetMarkerStyle(8);
		  if(bigmarker)    hm_ls_data[plotss]->SetMarkerSize(2.);
		  if(rebinvalue>0) hm_ls_data[plotss]->Rebin(rebinvalue);
		  hm_ls_data[plotss]->Draw("hist E P");

		  histoname=obj[histonr+nhistos][dataposition]->GetName();
		  histoname.Append("_data");

		  if(!plot_hm) gInclude->DumpHisto((TH1D*)hm_ls_data[plotss]->Clone(histoname),histoname);
		  else         gInclude->DumpHisto((TH1D*)hm_ls_data[plotss]->Clone(histoname),histoname);

		  if(rebinvalue>0)
		    {
		      obj[histonr+nhistos][0]           ->Rebin(rebinvalue);
		      obj[histonr+nhistos][dataposition]->Rebin(rebinvalue);
		    }

		  hm_ls_bMC_lfl[plotss] = (TH1D*) obj[histonr+nhistos][0]->Clone("hm_ls_bMC_lfl");
		  hm_ls_bMC_lfl[plotss] -> Add(obj[histonr+nhistos][dataposition], 1);
		  hm_ls_bMC_lfl[plotss] -> SetFillColor(2);   	  
		  hm_ls_bMC_lfl[plotss] -> SetFillStyle(3001);	  
		  hm_ls_bMC_lfl[plotss] -> Draw("hist same"); // ls b MC + lfl bg es.

		  histoname=obj[histonr+nhistos][dataposition]->GetName();
		  histoname.Append("_allMC_sum");

		  if(!plot_hm) gInclude->DumpHisto((TH1D*)hm_ls_bMC_lfl[plotss]->Clone(histoname),histoname);
		  else         gInclude->DumpHisto((TH1D*)hm_ls_bMC_lfl[plotss]->Clone(histoname),histoname);

		  obj[histonr+nhistos][dataposition]->SetFillStyle(3001);
		  obj[histonr+nhistos][dataposition]->SetFillColor(4);
		  obj[histonr+nhistos][dataposition]->Draw("hist same"); // lfl bg estimate only

		  histoname=obj[histonr+nhistos][dataposition]->GetName();
		  histoname.Append("_MC_lflbg_sum");

		  if(!plot_hm) gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][dataposition]->Clone(histoname),histoname);
		  else         gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][dataposition]->Clone(histoname),histoname);

// bbbb MC
		  obj[histonr+nhistos][bbbb_position]->SetFillColor(44); 
		  obj[histonr+nhistos][bbbb_position]->SetFillStyle(3001);
	
		  if(rebinvalue > 0)
		    {
		      obj[histonr+nhistos][bbbb_position]->Rebin(rebinvalue);
		    }
		  obj[histonr+nhistos][bbbb_position]->Draw("hist same"); 
		  histoname=obj[histonr+nhistos][dataposition]->GetName();
		  histoname.Append("_MC_bbbb");

		  if(!plot_hm) gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][bbbb_position]->Clone(histoname),histoname);
		  else         gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][bbbb_position]->Clone(histoname),histoname);

// cccc MC
		  obj[histonr+nhistos][cccc_position]->SetFillColor(44); 
		  obj[histonr+nhistos][cccc_position]->SetFillStyle(3001);
	
		  if(rebinvalue > 0)
		    {
		      obj[histonr+nhistos][cccc_position]->Rebin(rebinvalue);
		    }
		  obj[histonr+nhistos][cccc_position]->Draw("hist same"); 
		  histoname=obj[histonr+nhistos][dataposition]->GetName();
		  histoname.Append("_MC_cccc");

		  if(!plot_hm) gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][cccc_position]->Clone(histoname),histoname);
		  else         gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][cccc_position]->Clone(histoname),histoname);

// bbcc MC
		  obj[histonr+nhistos][bbcc_position]->SetFillColor(44); 
		  obj[histonr+nhistos][bbcc_position]->SetFillStyle(3001);
	
		  if(rebinvalue > 0)
		    {
		      obj[histonr+nhistos][bbcc_position]->Rebin(rebinvalue);
		    }
		  obj[histonr+nhistos][bbcc_position]->Draw("hist same"); 
		  histoname=obj[histonr+nhistos][dataposition]->GetName();
		  histoname.Append("_MC_bbcc");

		  if(!plot_hm) gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][bbcc_position]->Clone(histoname),histoname);
		  else         gInclude->DumpHisto((TH1D*)obj[histonr+nhistos][bbcc_position]->Clone(histoname),histoname);

		  hm_ls_data[plotss]->Draw("hist E P same"); //Data again on top

		}*/
	    }

	}
  

	  
 
    
//smile!!
  cout<<"Nice?  "<<nhistos<<endl;
 
  if(autoquit)    gROOT->ProcessLine(".q");

  return 1;
}
//**********NEW********040210*********************************<<<   // add lumi-reweighted beauty histos to first beauty histo sample:
