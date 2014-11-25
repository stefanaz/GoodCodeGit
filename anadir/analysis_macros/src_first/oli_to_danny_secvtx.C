#include <TCanvas.h>
#include <TMath.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TKey.h>
#include <TROOT.h>
#include "iostream"
#include "iomanip"
// #include </data/zenith223a/dbot/Gut_Code_PhD/anadir/analysis_macros/Test.h>
#include </data/zenith234d/stefan/GoodCodeGit/anadir/analysis_macros/inc/oli_to_danny_secvtx_mymodify.h>

using namespace std;

void oli_to_danny_secvtx(Bool_t slowme = false){
  cout<<"slowme is: "<<1*slowme<<endl;
  
  //  Int_t obj_size_v          = 10000;
  //  Int_t obj_size_h          = 1;

  Int_t DIMuon_folder_size  = 0;

  TH1D *obj[10000][1];
  
  // initialise histogram array:
  for(Int_t vorne = 0; vorne<10000; vorne++){
    for(Int_t hinten = 0; hinten<1; hinten++) obj[vorne][hinten] = 0;
  }
//test histos reset start:

// Histograms for eventshape Variables

  h_nrsecvtx_all                         = 0;
  h_nrsecvtx_lm_us_is                    = 0;   
  h_nrsecvtx_lm_ls_is                    = 0;   
  h_nrsecvtx_hm_us_is                    = 0;   
  h_nrsecvtx_hm_ls_is                    = 0;   
  h_nrsecvtx_lm_us_nis                   = 0;   
  h_nrsecvtx_lm_ls_nis                   = 0;   
  h_nrsecvtx_hm_us_nis                   = 0;   
  h_nrsecvtx_hm_ls_nis                   = 0;  

  h_multiplicity_all                     = 0;
  h_multiplicity_lm_us_is                = 0;   
  h_multiplicity_lm_ls_is                = 0;   
  h_multiplicity_hm_us_is                = 0;   
  h_multiplicity_hm_ls_is                = 0;   
  h_multiplicity_lm_us_nis               = 0;   
  h_multiplicity_lm_ls_nis               = 0;   
  h_multiplicity_hm_us_nis               = 0;   
  h_multiplicity_hm_ls_nis               = 0;  

  h_chi2_all                             = 0;
  h_chi2_lm_us_is                        = 0;   
  h_chi2_lm_ls_is                        = 0;   
  h_chi2_hm_us_is                        = 0;   
  h_chi2_hm_ls_is                        = 0;   
  h_chi2_lm_us_nis                       = 0;   
  h_chi2_lm_ls_nis                       = 0;   
  h_chi2_hm_us_nis                       = 0;   
  h_chi2_hm_ls_nis                       = 0;  

  h_ndof_all                             = 0;
  h_ndof_lm_us_is                        = 0;   
  h_ndof_lm_ls_is                        = 0;   
  h_ndof_hm_us_is                        = 0;   
  h_ndof_hm_ls_is                        = 0;   
  h_ndof_lm_us_nis                       = 0;   
  h_ndof_lm_ls_nis                       = 0;   
  h_ndof_hm_us_nis                       = 0;   
  h_ndof_hm_ls_nis                       = 0;  

  h_chi2ndof_all                         = 0;
  h_chi2ndof_lm_us_is                    = 0;   
  h_chi2ndof_lm_ls_is                    = 0;   
  h_chi2ndof_hm_us_is                    = 0;   
  h_chi2ndof_hm_ls_is                    = 0;   
  h_chi2ndof_lm_us_nis                   = 0;   
  h_chi2ndof_lm_ls_nis                   = 0;   
  h_chi2ndof_hm_us_nis                   = 0;   
  h_chi2ndof_hm_ls_nis                   = 0;  

  h_vtxmass_all                          = 0;
  h_vtxmass_lm_us_is                     = 0;   
  h_vtxmass_lm_ls_is                     = 0;   
  h_vtxmass_hm_us_is                     = 0;   
  h_vtxmass_hm_ls_is                     = 0;   
  h_vtxmass_lm_us_nis                    = 0;   
  h_vtxmass_lm_ls_nis                    = 0;   
  h_vtxmass_hm_us_nis                    = 0;   
  h_vtxmass_hm_ls_nis                    = 0;  

  h_dl2_all                              = 0;
  h_dl2_lm_us_is                         = 0;   
  h_dl2_lm_ls_is                         = 0;   
  h_dl2_hm_us_is                         = 0;   
  h_dl2_hm_ls_is                         = 0;   
  h_dl2_lm_us_nis                        = 0;   
  h_dl2_lm_ls_nis                        = 0;   
  h_dl2_hm_us_nis                        = 0;   
  h_dl2_hm_ls_nis                        = 0;  

  h_dl2_err_all                          = 0;
  h_dl2_err_lm_us_is                     = 0;   
  h_dl2_err_lm_ls_is                     = 0;   
  h_dl2_err_hm_us_is                     = 0;   
  h_dl2_err_hm_ls_is                     = 0;   
  h_dl2_err_lm_us_nis                    = 0;   
  h_dl2_err_lm_ls_nis                    = 0;   
  h_dl2_err_hm_us_nis                    = 0;   
  h_dl2_err_hm_ls_nis                    = 0;  

  h_dl2_sign_all                         = 0;
  h_dl2_sign_lm_us_is                    = 0;   
  h_dl2_sign_lm_ls_is                    = 0;   
  h_dl2_sign_hm_us_is                    = 0;   
  h_dl2_sign_hm_ls_is                    = 0;   
  h_dl2_sign_lm_us_nis                   = 0;   
  h_dl2_sign_lm_ls_nis                   = 0;   
  h_dl2_sign_hm_us_nis                   = 0;   
  h_dl2_sign_hm_ls_nis                   = 0;  

  h_dl2_sign_mirrp_all                   = 0;
  h_dl2_sign_mirrp_lm_us_is              = 0;   
  h_dl2_sign_mirrp_lm_ls_is              = 0;   
  h_dl2_sign_mirrp_hm_us_is              = 0;   
  h_dl2_sign_mirrp_hm_ls_is              = 0;   
  h_dl2_sign_mirrp_lm_us_nis             = 0;   
  h_dl2_sign_mirrp_lm_ls_nis             = 0;   
  h_dl2_sign_mirrp_hm_us_nis             = 0;   
  h_dl2_sign_mirrp_hm_ls_nis             = 0;  

  h_dl2_sign_mirrm_all                   = 0;
  h_dl2_sign_mirrm_lm_us_is              = 0;   
  h_dl2_sign_mirrm_lm_ls_is              = 0;   
  h_dl2_sign_mirrm_hm_us_is              = 0;   
  h_dl2_sign_mirrm_hm_ls_is              = 0;   
  h_dl2_sign_mirrm_lm_us_nis             = 0;   
  h_dl2_sign_mirrm_lm_ls_nis             = 0;   
  h_dl2_sign_mirrm_hm_us_nis             = 0;   
  h_dl2_sign_mirrm_hm_ls_nis             = 0;  

  h_mvtx2_multiplicity_all                     = 0;
  h_mvtx2_multiplicity_lm_us_is                = 0;   
  h_mvtx2_multiplicity_lm_ls_is                = 0;   
  h_mvtx2_multiplicity_hm_us_is                = 0;   
  h_mvtx2_multiplicity_hm_ls_is                = 0;   
  h_mvtx2_multiplicity_lm_us_nis               = 0;   
  h_mvtx2_multiplicity_lm_ls_nis               = 0;   
  h_mvtx2_multiplicity_hm_us_nis               = 0;   
  h_mvtx2_multiplicity_hm_ls_nis               = 0;  

  h_mvtx2_chi2_all                             = 0;
  h_mvtx2_chi2_lm_us_is                        = 0;   
  h_mvtx2_chi2_lm_ls_is                        = 0;   
  h_mvtx2_chi2_hm_us_is                        = 0;   
  h_mvtx2_chi2_hm_ls_is                        = 0;   
  h_mvtx2_chi2_lm_us_nis                       = 0;   
  h_mvtx2_chi2_lm_ls_nis                       = 0;   
  h_mvtx2_chi2_hm_us_nis                       = 0;   
  h_mvtx2_chi2_hm_ls_nis                       = 0;  

  h_mvtx2_ndof_all                             = 0;
  h_mvtx2_ndof_lm_us_is                        = 0;   
  h_mvtx2_ndof_lm_ls_is                        = 0;   
  h_mvtx2_ndof_hm_us_is                        = 0;   
  h_mvtx2_ndof_hm_ls_is                        = 0;   
  h_mvtx2_ndof_lm_us_nis                       = 0;   
  h_mvtx2_ndof_lm_ls_nis                       = 0;   
  h_mvtx2_ndof_hm_us_nis                       = 0;   
  h_mvtx2_ndof_hm_ls_nis                       = 0;  

  h_mvtx2_chi2ndof_all                         = 0;
  h_mvtx2_chi2ndof_lm_us_is                    = 0;   
  h_mvtx2_chi2ndof_lm_ls_is                    = 0;   
  h_mvtx2_chi2ndof_hm_us_is                    = 0;   
  h_mvtx2_chi2ndof_hm_ls_is                    = 0;   
  h_mvtx2_chi2ndof_lm_us_nis                   = 0;   
  h_mvtx2_chi2ndof_lm_ls_nis                   = 0;   
  h_mvtx2_chi2ndof_hm_us_nis                   = 0;   
  h_mvtx2_chi2ndof_hm_ls_nis                   = 0;  

  h_mvtx2_vtxmass_all                          = 0;
  h_mvtx2_vtxmass_lm_us_is                     = 0;   
  h_mvtx2_vtxmass_lm_ls_is                     = 0;   
  h_mvtx2_vtxmass_hm_us_is                     = 0;   
  h_mvtx2_vtxmass_hm_ls_is                     = 0;   
  h_mvtx2_vtxmass_lm_us_nis                    = 0;   
  h_mvtx2_vtxmass_lm_ls_nis                    = 0;   
  h_mvtx2_vtxmass_hm_us_nis                    = 0;   
  h_mvtx2_vtxmass_hm_ls_nis                    = 0;  

  h_mvtx2_dl2_all                              = 0;
  h_mvtx2_dl2_lm_us_is                         = 0;   
  h_mvtx2_dl2_lm_ls_is                         = 0;   
  h_mvtx2_dl2_hm_us_is                         = 0;   
  h_mvtx2_dl2_hm_ls_is                         = 0;   
  h_mvtx2_dl2_lm_us_nis                        = 0;   
  h_mvtx2_dl2_lm_ls_nis                        = 0;   
  h_mvtx2_dl2_hm_us_nis                        = 0;   
  h_mvtx2_dl2_hm_ls_nis                        = 0;  

  h_mvtx2_dl2_err_all                          = 0;
  h_mvtx2_dl2_err_lm_us_is                     = 0;   
  h_mvtx2_dl2_err_lm_ls_is                     = 0;   
  h_mvtx2_dl2_err_hm_us_is                     = 0;   
  h_mvtx2_dl2_err_hm_ls_is                     = 0;   
  h_mvtx2_dl2_err_lm_us_nis                    = 0;   
  h_mvtx2_dl2_err_lm_ls_nis                    = 0;   
  h_mvtx2_dl2_err_hm_us_nis                    = 0;   
  h_mvtx2_dl2_err_hm_ls_nis                    = 0;  

  h_mvtx2_dl2_sign_all                         = 0;
  h_mvtx2_dl2_sign_lm_us_is                    = 0;   
  h_mvtx2_dl2_sign_lm_ls_is                    = 0;   
  h_mvtx2_dl2_sign_hm_us_is                    = 0;   
  h_mvtx2_dl2_sign_hm_ls_is                    = 0;   
  h_mvtx2_dl2_sign_lm_us_nis                   = 0;   
  h_mvtx2_dl2_sign_lm_ls_nis                   = 0;   
  h_mvtx2_dl2_sign_hm_us_nis                   = 0;   
  h_mvtx2_dl2_sign_hm_ls_nis                   = 0;  

  h_mvtx2_dl2_sign_mirrp_all                   = 0;
  h_mvtx2_dl2_sign_mirrp_lm_us_is              = 0;   
  h_mvtx2_dl2_sign_mirrp_lm_ls_is              = 0;   
  h_mvtx2_dl2_sign_mirrp_hm_us_is              = 0;   
  h_mvtx2_dl2_sign_mirrp_hm_ls_is              = 0;   
  h_mvtx2_dl2_sign_mirrp_lm_us_nis             = 0;   
  h_mvtx2_dl2_sign_mirrp_lm_ls_nis             = 0;   
  h_mvtx2_dl2_sign_mirrp_hm_us_nis             = 0;   
  h_mvtx2_dl2_sign_mirrp_hm_ls_nis             = 0;  

  h_mvtx2_dl2_sign_mirrm_all                   = 0;
  h_mvtx2_dl2_sign_mirrm_lm_us_is              = 0;   
  h_mvtx2_dl2_sign_mirrm_lm_ls_is              = 0;   
  h_mvtx2_dl2_sign_mirrm_hm_us_is              = 0;   
  h_mvtx2_dl2_sign_mirrm_hm_ls_is              = 0;   
  h_mvtx2_dl2_sign_mirrm_lm_us_nis             = 0;   
  h_mvtx2_dl2_sign_mirrm_lm_ls_nis             = 0;   
  h_mvtx2_dl2_sign_mirrm_hm_us_nis             = 0;   
  h_mvtx2_dl2_sign_mirrm_hm_ls_nis             = 0;  


//test histos reset end.

  Int_t count1 = 0;
  
  TString previous_obj, histonamebuffer;
  TString outfile, infile;
  TKey *key;
  TFile *_file0;
 
  infile = "histos.root";
  
  if( _file0 = new TFile(infile,"READ") ) cout << "file opened "<< infile << endl;
  
  outfile = "oli2danny_out.root";
  
  _file0->ls();
  _file0->cd("Histograms/DIMuon");

  cout<<"getlist is: "<<endl;
 
  TIter next( gDirectory->GetListOfKeys() );
  while ((key = (TKey *) next())) {
    obj[count1][0] = (TH1D*) gDirectory->Get(key->GetName()); // copy object to memory
    obj[count1][0]->SetDirectory(0);
    obj[count1][0]->AddDirectory(kFALSE);

    // do something with obj
    if( previous_obj==key->GetName() ) {

      continue;

    } 

    previous_obj = key->GetName();

    count1++;
  }
  cout<<"Directory DIMuon left at count1= "<<count1<<endl;
  DIMuon_folder_size = count1;
  cout<<"DIMuon_folder_size = "<<DIMuon_folder_size<<endl;

  TFile * file = new TFile(outfile,"RECREATE");
  for( Int_t i=0; i< count1; ++i) {
    histonamebuffer = obj[i][0]->GetName();
    obj[i][0]->AddDirectory(kFALSE);
            
    if( i < DIMuon_folder_size ){

// Histograms for eventshape variables

      if(histonamebuffer=="Nrsecvtx")                    h_nrsecvtx_all        = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_is_lu")              h_nrsecvtx_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_is_ll")              h_nrsecvtx_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_is_hu")              h_nrsecvtx_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_is_hl")              h_nrsecvtx_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_nis_lu")             h_nrsecvtx_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_nis_ll")             h_nrsecvtx_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_nis_hu")             h_nrsecvtx_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Nrsecvtx_nis_hl")             h_nrsecvtx_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="Chi2")                        h_chi2_all        = obj[i][0];   
      if(histonamebuffer=="Chi2_is_lu")                  h_chi2_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="Chi2_is_ll")                  h_chi2_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Chi2_is_hu")                  h_chi2_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="Chi2_is_hl")                  h_chi2_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Chi2_nis_lu")                 h_chi2_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Chi2_nis_ll")                 h_chi2_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="Chi2_nis_hu")                 h_chi2_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Chi2_nis_hl")                 h_chi2_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="Ndof")                        h_ndof_all        = obj[i][0];   
      if(histonamebuffer=="Ndof_is_lu")                  h_ndof_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="Ndof_is_ll")                  h_ndof_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Ndof_is_hu")                  h_ndof_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="Ndof_is_hl")                  h_ndof_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Ndof_nis_lu")                 h_ndof_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Ndof_nis_ll")                 h_ndof_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="Ndof_nis_hu")                 h_ndof_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Ndof_nis_hl")                 h_ndof_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="Chi2Ndof")                    h_chi2ndof_all        = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_is_lu")              h_chi2ndof_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_is_ll")              h_chi2ndof_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_is_hu")              h_chi2ndof_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_is_hl")              h_chi2ndof_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_nis_lu")             h_chi2ndof_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_nis_ll")             h_chi2ndof_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_nis_hu")             h_chi2ndof_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Chi2Ndof_nis_hl")             h_chi2ndof_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="Multi")                       h_multiplicity_all        = obj[i][0];   
      if(histonamebuffer=="Multi_is_lu")                 h_multiplicity_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="Multi_is_ll")                 h_multiplicity_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Multi_is_hu")                 h_multiplicity_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="Multi_is_hl")                 h_multiplicity_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="Multi_nis_lu")                h_multiplicity_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Multi_nis_ll")                h_multiplicity_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="Multi_nis_hu")                h_multiplicity_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="Multi_nis_hl")                h_multiplicity_hm_ls_nis  = obj[i][0];   
   
      if(histonamebuffer=="VtxMass")                     h_vtxmass_all        = obj[i][0];   
      if(histonamebuffer=="VtxMass_is_lu")               h_vtxmass_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="VtxMass_is_ll")               h_vtxmass_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="VtxMass_is_hu")               h_vtxmass_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="VtxMass_is_hl")               h_vtxmass_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="VtxMass_nis_lu")              h_vtxmass_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="VtxMass_nis_ll")              h_vtxmass_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="VtxMass_nis_hu")              h_vtxmass_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="VtxMass_nis_hl")              h_vtxmass_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="DL2")                         h_dl2_all        = obj[i][0];   
      if(histonamebuffer=="DL2_is_lu")                   h_dl2_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_is_ll")                   h_dl2_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_is_hu")                   h_dl2_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_is_hl")                   h_dl2_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_nis_lu")                  h_dl2_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_nis_ll")                  h_dl2_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_nis_hu")                  h_dl2_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_nis_hl")                  h_dl2_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="DL2_err")                     h_dl2_err_all        = obj[i][0];   
      if(histonamebuffer=="DL2_err_is_lu")               h_dl2_err_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_err_is_ll")               h_dl2_err_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_err_is_hu")               h_dl2_err_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_err_is_hl")               h_dl2_err_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_err_nis_lu")              h_dl2_err_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_err_nis_ll")              h_dl2_err_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_err_nis_hu")              h_dl2_err_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_err_nis_hl")              h_dl2_err_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="DL2_Sign")                    h_dl2_sign_all        = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_is_lu")              h_dl2_sign_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_is_ll")              h_dl2_sign_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_is_hu")              h_dl2_sign_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_is_hl")              h_dl2_sign_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_nis_lu")             h_dl2_sign_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_nis_ll")             h_dl2_sign_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_nis_hu")             h_dl2_sign_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_nis_hl")             h_dl2_sign_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="DL2_Sign_Mirrp")              h_dl2_sign_mirrp_all        = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_is_lu")        h_dl2_sign_mirrp_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_is_ll")        h_dl2_sign_mirrp_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_is_hu")        h_dl2_sign_mirrp_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_is_hl")        h_dl2_sign_mirrp_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_nis_lu")       h_dl2_sign_mirrp_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_nis_ll")       h_dl2_sign_mirrp_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_nis_hu")       h_dl2_sign_mirrp_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrp_nis_hl")       h_dl2_sign_mirrp_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="DL2_Sign_Mirrm")              h_dl2_sign_mirrm_all        = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_is_lu")        h_dl2_sign_mirrm_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_is_ll")        h_dl2_sign_mirrm_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_is_hu")        h_dl2_sign_mirrm_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_is_hl")        h_dl2_sign_mirrm_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_nis_lu")       h_dl2_sign_mirrm_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_nis_ll")       h_dl2_sign_mirrm_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_nis_hu")       h_dl2_sign_mirrm_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="DL2_Sign_Mirrm_nis_hl")       h_dl2_sign_mirrm_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_Chi2")                  h_mvtx2_chi2_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_is_lu")            h_mvtx2_chi2_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_is_ll")            h_mvtx2_chi2_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_is_hu")            h_mvtx2_chi2_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_is_hl")            h_mvtx2_chi2_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_nis_lu")           h_mvtx2_chi2_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_nis_ll")           h_mvtx2_chi2_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_nis_hu")           h_mvtx2_chi2_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2_nis_hl")           h_mvtx2_chi2_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_Ndof")                  h_mvtx2_ndof_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_is_lu")            h_mvtx2_ndof_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_is_ll")            h_mvtx2_ndof_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_is_hu")            h_mvtx2_ndof_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_is_hl")            h_mvtx2_ndof_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_nis_lu")           h_mvtx2_ndof_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_nis_ll")           h_mvtx2_ndof_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_nis_hu")           h_mvtx2_ndof_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Ndof_nis_hl")           h_mvtx2_ndof_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_Chi2Ndof")              h_mvtx2_chi2ndof_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_is_lu")        h_mvtx2_chi2ndof_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_is_ll")        h_mvtx2_chi2ndof_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_is_hu")        h_mvtx2_chi2ndof_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_is_hl")        h_mvtx2_chi2ndof_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_nis_lu")       h_mvtx2_chi2ndof_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_nis_ll")       h_mvtx2_chi2ndof_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_nis_hu")       h_mvtx2_chi2ndof_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Chi2Ndof_nis_hl")       h_mvtx2_chi2ndof_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_Multi")                 h_mvtx2_multiplicity_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_is_lu")           h_mvtx2_multiplicity_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_is_ll")           h_mvtx2_multiplicity_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_is_hu")           h_mvtx2_multiplicity_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_is_hl")           h_mvtx2_multiplicity_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_nis_lu")          h_mvtx2_multiplicity_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_nis_ll")          h_mvtx2_multiplicity_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_nis_hu")          h_mvtx2_multiplicity_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_Multi_nis_hl")          h_mvtx2_multiplicity_hm_ls_nis  = obj[i][0];   
   
      if(histonamebuffer=="mvtx2_VtxMass")               h_mvtx2_vtxmass_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_is_lu")         h_mvtx2_vtxmass_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_is_ll")         h_mvtx2_vtxmass_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_is_hu")         h_mvtx2_vtxmass_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_is_hl")         h_mvtx2_vtxmass_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_nis_lu")        h_mvtx2_vtxmass_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_nis_ll")        h_mvtx2_vtxmass_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_nis_hu")        h_mvtx2_vtxmass_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_VtxMass_nis_hl")        h_mvtx2_vtxmass_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_DL2")                   h_mvtx2_dl2_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_is_lu")             h_mvtx2_dl2_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_is_ll")             h_mvtx2_dl2_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_is_hu")             h_mvtx2_dl2_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_is_hl")             h_mvtx2_dl2_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_nis_lu")            h_mvtx2_dl2_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_nis_ll")            h_mvtx2_dl2_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_nis_hu")            h_mvtx2_dl2_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_nis_hl")            h_mvtx2_dl2_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_DL2_err")               h_mvtx2_dl2_err_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_is_lu")         h_mvtx2_dl2_err_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_is_ll")         h_mvtx2_dl2_err_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_is_hu")         h_mvtx2_dl2_err_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_is_hl")         h_mvtx2_dl2_err_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_nis_lu")        h_mvtx2_dl2_err_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_nis_ll")        h_mvtx2_dl2_err_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_nis_hu")        h_mvtx2_dl2_err_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_err_nis_hl")        h_mvtx2_dl2_err_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_DL2_Sign")              h_mvtx2_dl2_sign_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_is_lu")        h_mvtx2_dl2_sign_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_is_ll")        h_mvtx2_dl2_sign_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_is_hu")        h_mvtx2_dl2_sign_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_is_hl")        h_mvtx2_dl2_sign_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_nis_lu")       h_mvtx2_dl2_sign_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_nis_ll")       h_mvtx2_dl2_sign_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_nis_hu")       h_mvtx2_dl2_sign_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_nis_hl")       h_mvtx2_dl2_sign_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp")        h_mvtx2_dl2_sign_mirrp_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_is_lu")  h_mvtx2_dl2_sign_mirrp_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_is_ll")  h_mvtx2_dl2_sign_mirrp_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_is_hu")  h_mvtx2_dl2_sign_mirrp_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_is_hl")  h_mvtx2_dl2_sign_mirrp_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_nis_lu") h_mvtx2_dl2_sign_mirrp_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_nis_ll") h_mvtx2_dl2_sign_mirrp_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_nis_hu") h_mvtx2_dl2_sign_mirrp_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrp_nis_hl") h_mvtx2_dl2_sign_mirrp_hm_ls_nis  = obj[i][0];   

      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm")        h_mvtx2_dl2_sign_mirrm_all        = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_is_lu")  h_mvtx2_dl2_sign_mirrm_lm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_is_ll")  h_mvtx2_dl2_sign_mirrm_lm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_is_hu")  h_mvtx2_dl2_sign_mirrm_hm_us_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_is_hl")  h_mvtx2_dl2_sign_mirrm_hm_ls_is   = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_nis_lu") h_mvtx2_dl2_sign_mirrm_lm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_nis_ll") h_mvtx2_dl2_sign_mirrm_lm_ls_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_nis_hu") h_mvtx2_dl2_sign_mirrm_hm_us_nis  = obj[i][0];   
      if(histonamebuffer=="mvtx2_DL2_Sign_Mirrm_nis_hl") h_mvtx2_dl2_sign_mirrm_hm_ls_nis  = obj[i][0];   

    }
  }
  
  if(42 == 42) {
  
    if(h_nrsecvtx_all       != 0) file->Append(h_nrsecvtx_all       -> Clone("h_nrsecvtx_all") );
    if(h_chi2_all           != 0) file->Append(h_chi2_all           -> Clone("h_chi2_all") );
    if(h_multiplicity_all   != 0) file->Append(h_multiplicity_all   -> Clone("h_multiplicity_all") );
    if(h_ndof_all           != 0) file->Append(h_ndof_all           -> Clone("h_ndof_all") ); 
    if(h_chi2ndof_all       != 0) file->Append(h_chi2ndof_all       -> Clone("h_chi2ndof_all") ); 
    if(h_vtxmass_all        != 0) file->Append(h_vtxmass_all        -> Clone("h_vtxmass_all") );
    if(h_dl2_all            != 0) file->Append(h_dl2_all            -> Clone("h_dl2_all") );
    if(h_dl2_err_all        != 0) file->Append(h_dl2_err_all        -> Clone("h_dl2_err_all") );
    if(h_dl2_sign_all       != 0) file->Append(h_dl2_sign_all       -> Clone("h_dl2_sign_all") );
    if(h_dl2_sign_mirrp_all != 0) file->Append(h_dl2_sign_mirrp_all -> Clone("h_dl2_sign_mirrp_all") );
    if(h_dl2_sign_mirrm_all != 0) file->Append(h_dl2_sign_mirrm_all -> Clone("h_dl2_sign_mirrm_all") );   
    if(h_mvtx2_chi2_all           != 0) file->Append(h_mvtx2_chi2_all           -> Clone("h_mvtx2_chi2_all") );
    if(h_mvtx2_multiplicity_all   != 0) file->Append(h_mvtx2_multiplicity_all   -> Clone("h_mvtx2_multiplicity_all") );
    if(h_mvtx2_ndof_all           != 0) file->Append(h_mvtx2_ndof_all           -> Clone("h_mvtx2_ndof_all") ); 
    if(h_mvtx2_chi2ndof_all       != 0) file->Append(h_mvtx2_chi2ndof_all       -> Clone("h_mvtx2_chi2ndof_all") ); 
    if(h_mvtx2_vtxmass_all        != 0) file->Append(h_mvtx2_vtxmass_all        -> Clone("h_mvtx2_vtxmass_all") );
    if(h_mvtx2_dl2_all            != 0) file->Append(h_mvtx2_dl2_all            -> Clone("h_mvtx2_dl2_all") );
    if(h_mvtx2_dl2_err_all        != 0) file->Append(h_mvtx2_dl2_err_all        -> Clone("h_mvtx2_dl2_err_all") );
    if(h_mvtx2_dl2_sign_all       != 0) file->Append(h_mvtx2_dl2_sign_all       -> Clone("h_mvtx2_dl2_sign_all") );
    if(h_mvtx2_dl2_sign_mirrp_all != 0) file->Append(h_mvtx2_dl2_sign_mirrp_all -> Clone("h_mvtx2_dl2_sign_mirrp_all") );
    if(h_mvtx2_dl2_sign_mirrm_all != 0) file->Append(h_mvtx2_dl2_sign_mirrm_all -> Clone("h_mvtx2_dl2_sign_mirrm_all") );


    // ***************************************************************************************
    // produce and append pre-isolation histos:
    // ***************************************************************************************

    if(h_nrsecvtx_lm_us_nis       != 0) h_nrsecvtx_lm_us       = (TH1D*) h_nrsecvtx_lm_us_nis       -> Clone("h_nrsecvtx_lm_us");
    if(h_chi2_lm_us_nis           != 0) h_chi2_lm_us           = (TH1D*) h_chi2_lm_us_nis           -> Clone("h_chi2_lm_us");
    if(h_multiplicity_lm_us_nis   != 0) h_multiplicity_lm_us   = (TH1D*) h_multiplicity_lm_us_nis   -> Clone("h_multiplicity_lm_us");
    if(h_ndof_lm_us_nis           != 0) h_ndof_lm_us           = (TH1D*) h_ndof_lm_us_nis           -> Clone("h_ndof_lm_us");
    if(h_chi2ndof_lm_us_nis       != 0) h_chi2ndof_lm_us       = (TH1D*) h_chi2ndof_lm_us_nis       -> Clone("h_chi2ndof_lm_us");
    if(h_vtxmass_lm_us_nis        != 0) h_vtxmass_lm_us        = (TH1D*) h_vtxmass_lm_us_nis        -> Clone("h_vtxmass_lm_us");
    if(h_dl2_lm_us_nis            != 0) h_dl2_lm_us            = (TH1D*) h_dl2_lm_us_nis            -> Clone("h_dl2_lm_us");
    if(h_dl2_err_lm_us_nis        != 0) h_dl2_err_lm_us        = (TH1D*) h_dl2_err_lm_us_nis        -> Clone("h_dl2_err_lm_us");
    if(h_dl2_sign_lm_us_nis       != 0) h_dl2_sign_lm_us       = (TH1D*) h_dl2_sign_lm_us_nis       -> Clone("h_dl2_sign_lm_us");
    if(h_dl2_sign_mirrp_lm_us_nis != 0) h_dl2_sign_mirrp_lm_us = (TH1D*) h_dl2_sign_mirrp_lm_us_nis -> Clone("h_dl2_sign_mirrp_lm_us");
    if(h_dl2_sign_mirrm_lm_us_nis != 0) h_dl2_sign_mirrm_lm_us = (TH1D*) h_dl2_sign_mirrm_lm_us_nis -> Clone("h_dl2_sign_mirrm_lm_us");
    if(h_mvtx2_chi2_lm_us_nis           != 0) h_mvtx2_chi2_lm_us           = (TH1D*) h_mvtx2_chi2_lm_us_nis           -> Clone("h_mvtx2_chi2_lm_us");
    if(h_mvtx2_multiplicity_lm_us_nis   != 0) h_mvtx2_multiplicity_lm_us   = (TH1D*) h_mvtx2_multiplicity_lm_us_nis   -> Clone("h_mvtx2_multiplicity_lm_us");
    if(h_mvtx2_ndof_lm_us_nis           != 0) h_mvtx2_ndof_lm_us           = (TH1D*) h_mvtx2_ndof_lm_us_nis           -> Clone("h_mvtx2_ndof_lm_us");
    if(h_mvtx2_chi2ndof_lm_us_nis       != 0) h_mvtx2_chi2ndof_lm_us       = (TH1D*) h_mvtx2_chi2ndof_lm_us_nis       -> Clone("h_mvtx2_chi2ndof_lm_us");
    if(h_mvtx2_vtxmass_lm_us_nis        != 0) h_mvtx2_vtxmass_lm_us        = (TH1D*) h_mvtx2_vtxmass_lm_us_nis        -> Clone("h_mvtx2_vtxmass_lm_us");
    if(h_mvtx2_dl2_lm_us_nis            != 0) h_mvtx2_dl2_lm_us            = (TH1D*) h_mvtx2_dl2_lm_us_nis            -> Clone("h_mvtx2_dl2_lm_us");
    if(h_mvtx2_dl2_err_lm_us_nis        != 0) h_mvtx2_dl2_err_lm_us        = (TH1D*) h_mvtx2_dl2_err_lm_us_nis        -> Clone("h_mvtx2_dl2_err_lm_us");
    if(h_mvtx2_dl2_sign_lm_us_nis       != 0) h_mvtx2_dl2_sign_lm_us       = (TH1D*) h_mvtx2_dl2_sign_lm_us_nis       -> Clone("h_mvtx2_dl2_sign_lm_us");
    if(h_mvtx2_dl2_sign_mirrp_lm_us_nis != 0) h_mvtx2_dl2_sign_mirrp_lm_us = (TH1D*) h_mvtx2_dl2_sign_mirrp_lm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrp_lm_us");
    if(h_mvtx2_dl2_sign_mirrm_lm_us_nis != 0) h_mvtx2_dl2_sign_mirrm_lm_us = (TH1D*) h_mvtx2_dl2_sign_mirrm_lm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrm_lm_us");

    if(h_nrsecvtx_lm_ls_nis       != 0) h_nrsecvtx_lm_ls       = (TH1D*) h_nrsecvtx_lm_ls_nis       -> Clone("h_nrsecvtx_lm_ls");
    if(h_chi2_lm_ls_nis           != 0) h_chi2_lm_ls           = (TH1D*) h_chi2_lm_ls_nis           -> Clone("h_chi2_lm_ls");
    if(h_multiplicity_lm_ls_nis   != 0) h_multiplicity_lm_ls   = (TH1D*) h_multiplicity_lm_ls_nis   -> Clone("h_multiplicity_lm_ls");
    if(h_ndof_lm_ls_nis           != 0) h_ndof_lm_ls           = (TH1D*) h_ndof_lm_ls_nis           -> Clone("h_ndof_lm_ls");
    if(h_chi2ndof_lm_ls_nis       != 0) h_chi2ndof_lm_ls       = (TH1D*) h_chi2ndof_lm_ls_nis       -> Clone("h_chi2ndof_lm_ls");
    if(h_vtxmass_lm_ls_nis        != 0) h_vtxmass_lm_ls        = (TH1D*) h_vtxmass_lm_ls_nis        -> Clone("h_vtxmass_lm_ls");
    if(h_dl2_lm_ls_nis            != 0) h_dl2_lm_ls            = (TH1D*) h_dl2_lm_ls_nis            -> Clone("h_dl2_lm_ls");
    if(h_dl2_err_lm_ls_nis        != 0) h_dl2_err_lm_ls        = (TH1D*) h_dl2_err_lm_ls_nis        -> Clone("h_dl2_err_lm_ls");
    if(h_dl2_sign_lm_ls_nis       != 0) h_dl2_sign_lm_ls       = (TH1D*) h_dl2_sign_lm_ls_nis       -> Clone("h_dl2_sign_lm_ls");
    if(h_dl2_sign_mirrp_lm_ls_nis != 0) h_dl2_sign_mirrp_lm_ls = (TH1D*) h_dl2_sign_mirrp_lm_ls_nis -> Clone("h_dl2_sign_mirrp_lm_ls");
    if(h_dl2_sign_mirrm_lm_ls_nis != 0) h_dl2_sign_mirrm_lm_ls = (TH1D*) h_dl2_sign_mirrm_lm_ls_nis -> Clone("h_dl2_sign_mirrm_lm_ls");
    if(h_mvtx2_chi2_lm_ls_nis           != 0) h_mvtx2_chi2_lm_ls           = (TH1D*) h_mvtx2_chi2_lm_ls_nis           -> Clone("h_mvtx2_chi2_lm_ls");
    if(h_mvtx2_multiplicity_lm_ls_nis   != 0) h_mvtx2_multiplicity_lm_ls   = (TH1D*) h_mvtx2_multiplicity_lm_ls_nis   -> Clone("h_mvtx2_multiplicity_lm_ls");
    if(h_mvtx2_ndof_lm_ls_nis           != 0) h_mvtx2_ndof_lm_ls           = (TH1D*) h_mvtx2_ndof_lm_ls_nis           -> Clone("h_mvtx2_ndof_lm_ls");
    if(h_mvtx2_chi2ndof_lm_ls_nis       != 0) h_mvtx2_chi2ndof_lm_ls       = (TH1D*) h_mvtx2_chi2ndof_lm_ls_nis       -> Clone("h_mvtx2_chi2ndof_lm_ls");
    if(h_mvtx2_vtxmass_lm_ls_nis        != 0) h_mvtx2_vtxmass_lm_ls        = (TH1D*) h_mvtx2_vtxmass_lm_ls_nis        -> Clone("h_mvtx2_vtxmass_lm_ls");
    if(h_mvtx2_dl2_lm_ls_nis            != 0) h_mvtx2_dl2_lm_ls            = (TH1D*) h_mvtx2_dl2_lm_ls_nis            -> Clone("h_mvtx2_dl2_lm_ls");
    if(h_mvtx2_dl2_err_lm_ls_nis        != 0) h_mvtx2_dl2_err_lm_ls        = (TH1D*) h_mvtx2_dl2_err_lm_ls_nis        -> Clone("h_mvtx2_dl2_err_lm_ls");
    if(h_mvtx2_dl2_sign_lm_ls_nis       != 0) h_mvtx2_dl2_sign_lm_ls       = (TH1D*) h_mvtx2_dl2_sign_lm_ls_nis       -> Clone("h_mvtx2_dl2_sign_lm_ls");
    if(h_mvtx2_dl2_sign_mirrp_lm_ls_nis != 0) h_mvtx2_dl2_sign_mirrp_lm_ls = (TH1D*) h_mvtx2_dl2_sign_mirrp_lm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrp_lm_ls");
    if(h_mvtx2_dl2_sign_mirrm_lm_ls_nis != 0) h_mvtx2_dl2_sign_mirrm_lm_ls = (TH1D*) h_mvtx2_dl2_sign_mirrm_lm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrm_lm_ls");

    if(h_nrsecvtx_hm_us_nis       != 0) h_nrsecvtx_hm_us       = (TH1D*) h_nrsecvtx_hm_us_nis       -> Clone("h_nrsecvtx_hm_us");
    if(h_chi2_hm_us_nis           != 0) h_chi2_hm_us           = (TH1D*) h_chi2_hm_us_nis           -> Clone("h_chi2_hm_us");
    if(h_multiplicity_hm_us_nis   != 0) h_multiplicity_hm_us   = (TH1D*) h_multiplicity_hm_us_nis   -> Clone("h_multiplicity_hm_us");
    if(h_ndof_hm_us_nis           != 0) h_ndof_hm_us           = (TH1D*) h_ndof_hm_us_nis           -> Clone("h_ndof_hm_us");
    if(h_chi2ndof_hm_us_nis       != 0) h_chi2ndof_hm_us       = (TH1D*) h_chi2ndof_hm_us_nis       -> Clone("h_chi2ndof_hm_us");
    if(h_vtxmass_hm_us_nis        != 0) h_vtxmass_hm_us        = (TH1D*) h_vtxmass_hm_us_nis        -> Clone("h_vtxmass_hm_us");
    if(h_dl2_hm_us_nis            != 0) h_dl2_hm_us            = (TH1D*) h_dl2_hm_us_nis            -> Clone("h_dl2_hm_us");
    if(h_dl2_err_hm_us_nis        != 0) h_dl2_err_hm_us        = (TH1D*) h_dl2_err_hm_us_nis        -> Clone("h_dl2_err_hm_us");
    if(h_dl2_sign_hm_us_nis       != 0) h_dl2_sign_hm_us       = (TH1D*) h_dl2_sign_hm_us_nis       -> Clone("h_dl2_sign_hm_us");
    if(h_dl2_sign_mirrp_hm_us_nis != 0) h_dl2_sign_mirrp_hm_us = (TH1D*) h_dl2_sign_mirrp_hm_us_nis -> Clone("h_dl2_sign_mirrp_hm_us");
    if(h_dl2_sign_mirrm_hm_us_nis != 0) h_dl2_sign_mirrm_hm_us = (TH1D*) h_dl2_sign_mirrm_hm_us_nis -> Clone("h_dl2_sign_mirrm_hm_us");
    if(h_mvtx2_chi2_hm_us_nis           != 0) h_mvtx2_chi2_hm_us           = (TH1D*) h_mvtx2_chi2_hm_us_nis           -> Clone("h_mvtx2_chi2_hm_us");
    if(h_mvtx2_multiplicity_hm_us_nis   != 0) h_mvtx2_multiplicity_hm_us   = (TH1D*) h_mvtx2_multiplicity_hm_us_nis   -> Clone("h_mvtx2_multiplicity_hm_us");
    if(h_mvtx2_ndof_hm_us_nis           != 0) h_mvtx2_ndof_hm_us           = (TH1D*) h_mvtx2_ndof_hm_us_nis           -> Clone("h_mvtx2_ndof_hm_us");
    if(h_mvtx2_chi2ndof_hm_us_nis       != 0) h_mvtx2_chi2ndof_hm_us       = (TH1D*) h_mvtx2_chi2ndof_hm_us_nis       -> Clone("h_mvtx2_chi2ndof_hm_us");
    if(h_mvtx2_vtxmass_hm_us_nis        != 0) h_mvtx2_vtxmass_hm_us        = (TH1D*) h_mvtx2_vtxmass_hm_us_nis        -> Clone("h_mvtx2_vtxmass_hm_us");
    if(h_mvtx2_dl2_hm_us_nis            != 0) h_mvtx2_dl2_hm_us            = (TH1D*) h_mvtx2_dl2_hm_us_nis            -> Clone("h_mvtx2_dl2_hm_us");
    if(h_mvtx2_dl2_err_hm_us_nis        != 0) h_mvtx2_dl2_err_hm_us        = (TH1D*) h_mvtx2_dl2_err_hm_us_nis        -> Clone("h_mvtx2_dl2_err_hm_us");
    if(h_mvtx2_dl2_sign_hm_us_nis       != 0) h_mvtx2_dl2_sign_hm_us       = (TH1D*) h_mvtx2_dl2_sign_hm_us_nis       -> Clone("h_mvtx2_dl2_sign_hm_us");
    if(h_mvtx2_dl2_sign_mirrp_hm_us_nis != 0) h_mvtx2_dl2_sign_mirrp_hm_us = (TH1D*) h_mvtx2_dl2_sign_mirrp_hm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrp_hm_us");
    if(h_mvtx2_dl2_sign_mirrm_hm_us_nis != 0) h_mvtx2_dl2_sign_mirrm_hm_us = (TH1D*) h_mvtx2_dl2_sign_mirrm_hm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrm_hm_us");

    if(h_nrsecvtx_hm_ls_nis       != 0) h_nrsecvtx_hm_ls       = (TH1D*) h_nrsecvtx_hm_ls_nis       -> Clone("h_nrsecvtx_hm_ls");
    if(h_chi2_hm_ls_nis           != 0) h_chi2_hm_ls           = (TH1D*) h_chi2_hm_ls_nis           -> Clone("h_chi2_hm_ls");
    if(h_multiplicity_hm_ls_nis   != 0) h_multiplicity_hm_ls   = (TH1D*) h_multiplicity_hm_ls_nis   -> Clone("h_multiplicity_hm_ls");
    if(h_ndof_hm_ls_nis           != 0) h_ndof_hm_ls           = (TH1D*) h_ndof_hm_ls_nis           -> Clone("h_ndof_hm_ls");
    if(h_chi2ndof_hm_ls_nis       != 0) h_chi2ndof_hm_ls       = (TH1D*) h_chi2ndof_hm_ls_nis       -> Clone("h_chi2ndof_hm_ls");
    if(h_vtxmass_hm_ls_nis        != 0) h_vtxmass_hm_ls        = (TH1D*) h_vtxmass_hm_ls_nis        -> Clone("h_vtxmass_hm_ls");
    if(h_dl2_hm_ls_nis            != 0) h_dl2_hm_ls            = (TH1D*) h_dl2_hm_ls_nis            -> Clone("h_dl2_hm_ls");
    if(h_dl2_err_hm_ls_nis        != 0) h_dl2_err_hm_ls        = (TH1D*) h_dl2_err_hm_ls_nis        -> Clone("h_dl2_err_hm_ls");
    if(h_dl2_sign_hm_ls_nis       != 0) h_dl2_sign_hm_ls       = (TH1D*) h_dl2_sign_hm_ls_nis       -> Clone("h_dl2_sign_hm_ls");
    if(h_dl2_sign_mirrp_hm_ls_nis != 0) h_dl2_sign_mirrp_hm_ls = (TH1D*) h_dl2_sign_mirrp_hm_ls_nis -> Clone("h_dl2_sign_mirrp_hm_ls");
    if(h_dl2_sign_mirrm_hm_ls_nis != 0) h_dl2_sign_mirrm_hm_ls = (TH1D*) h_dl2_sign_mirrm_hm_ls_nis -> Clone("h_dl2_sign_mirrm_hm_ls");
    if(h_mvtx2_chi2_hm_ls_nis           != 0) h_mvtx2_chi2_hm_ls           = (TH1D*) h_mvtx2_chi2_hm_ls_nis           -> Clone("h_mvtx2_chi2_hm_ls");
    if(h_mvtx2_multiplicity_hm_ls_nis   != 0) h_mvtx2_multiplicity_hm_ls   = (TH1D*) h_mvtx2_multiplicity_hm_ls_nis   -> Clone("h_mvtx2_multiplicity_hm_ls");
    if(h_mvtx2_ndof_hm_ls_nis           != 0) h_mvtx2_ndof_hm_ls           = (TH1D*) h_mvtx2_ndof_hm_ls_nis           -> Clone("h_mvtx2_ndof_hm_ls");
    if(h_mvtx2_chi2ndof_hm_ls_nis       != 0) h_mvtx2_chi2ndof_hm_ls       = (TH1D*) h_mvtx2_chi2ndof_hm_ls_nis       -> Clone("h_mvtx2_chi2ndof_hm_ls");
    if(h_mvtx2_vtxmass_hm_ls_nis        != 0) h_mvtx2_vtxmass_hm_ls        = (TH1D*) h_mvtx2_vtxmass_hm_ls_nis        -> Clone("h_mvtx2_vtxmass_hm_ls");
    if(h_mvtx2_dl2_hm_ls_nis            != 0) h_mvtx2_dl2_hm_ls            = (TH1D*) h_mvtx2_dl2_hm_ls_nis            -> Clone("h_mvtx2_dl2_hm_ls");
    if(h_mvtx2_dl2_err_hm_ls_nis        != 0) h_mvtx2_dl2_err_hm_ls        = (TH1D*) h_mvtx2_dl2_err_hm_ls_nis        -> Clone("h_mvtx2_dl2_err_hm_ls");
    if(h_mvtx2_dl2_sign_hm_ls_nis       != 0) h_mvtx2_dl2_sign_hm_ls       = (TH1D*) h_mvtx2_dl2_sign_hm_ls_nis       -> Clone("h_mvtx2_dl2_sign_hm_ls");
    if(h_mvtx2_dl2_sign_mirrp_hm_ls_nis != 0) h_mvtx2_dl2_sign_mirrp_hm_ls = (TH1D*) h_mvtx2_dl2_sign_mirrp_hm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrp_hm_ls");
    if(h_mvtx2_dl2_sign_mirrm_hm_ls_nis != 0) h_mvtx2_dl2_sign_mirrm_hm_ls = (TH1D*) h_mvtx2_dl2_sign_mirrm_hm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrm_hm_ls");

//Add is + nis to have nisandis:

    if(h_nrsecvtx_lm_us_nis       != 0) h_nrsecvtx_lm_us       -> Add(h_nrsecvtx_lm_us_is       , h_nrsecvtx_lm_us_nis);
    if(h_chi2_lm_us_nis           != 0) h_chi2_lm_us           -> Add(h_chi2_lm_us_is           , h_chi2_lm_us_nis);
    if(h_ndof_lm_us_nis           != 0) h_ndof_lm_us           -> Add(h_ndof_lm_us_is           , h_ndof_lm_us_nis);
    if(h_chi2ndof_lm_us_nis       != 0) h_chi2ndof_lm_us       -> Add(h_chi2ndof_lm_us_is       , h_chi2ndof_lm_us_nis);
    if(h_multiplicity_lm_us_nis   != 0) h_multiplicity_lm_us   -> Add(h_multiplicity_lm_us_is   , h_multiplicity_lm_us_nis);
    if(h_vtxmass_lm_us_nis        != 0) h_vtxmass_lm_us        -> Add(h_vtxmass_lm_us_is        , h_vtxmass_lm_us_nis);
    if(h_dl2_lm_us_nis            != 0) h_dl2_lm_us            -> Add(h_dl2_lm_us_is            , h_dl2_lm_us_nis);
    if(h_dl2_err_lm_us_nis        != 0) h_dl2_err_lm_us        -> Add(h_dl2_err_lm_us_is        , h_dl2_err_lm_us_nis);
    if(h_dl2_sign_lm_us_nis       != 0) h_dl2_sign_lm_us       -> Add(h_dl2_sign_lm_us_is       , h_dl2_sign_lm_us_nis);
    if(h_dl2_sign_mirrp_lm_us_nis != 0) h_dl2_sign_mirrp_lm_us -> Add(h_dl2_sign_mirrp_lm_us_is , h_dl2_sign_mirrp_lm_us_nis);
    if(h_dl2_sign_mirrm_lm_us_nis != 0) h_dl2_sign_mirrm_lm_us -> Add(h_dl2_sign_mirrm_lm_us_is , h_dl2_sign_mirrm_lm_us_nis);
    if(h_chi2_lm_us_nis           != 0) h_chi2_lm_us           -> Add(h_chi2_lm_us_is           , h_chi2_lm_us_nis);
    if(h_ndof_lm_us_nis           != 0) h_ndof_lm_us           -> Add(h_ndof_lm_us_is           , h_ndof_lm_us_nis);
    if(h_mvtx2_chi2ndof_lm_us_nis       != 0) h_mvtx2_chi2ndof_lm_us       -> Add(h_mvtx2_chi2ndof_lm_us_is       , h_mvtx2_chi2ndof_lm_us_nis);
    if(h_mvtx2_multiplicity_lm_us_nis   != 0) h_mvtx2_multiplicity_lm_us   -> Add(h_mvtx2_multiplicity_lm_us_is   , h_mvtx2_multiplicity_lm_us_nis);
    if(h_mvtx2_vtxmass_lm_us_nis        != 0) h_mvtx2_vtxmass_lm_us        -> Add(h_mvtx2_vtxmass_lm_us_is        , h_mvtx2_vtxmass_lm_us_nis);
    if(h_mvtx2_dl2_lm_us_nis            != 0) h_mvtx2_dl2_lm_us            -> Add(h_mvtx2_dl2_lm_us_is            , h_mvtx2_dl2_lm_us_nis);
    if(h_mvtx2_dl2_err_lm_us_nis        != 0) h_mvtx2_dl2_err_lm_us        -> Add(h_mvtx2_dl2_err_lm_us_is        , h_mvtx2_dl2_err_lm_us_nis);
    if(h_mvtx2_dl2_sign_lm_us_nis       != 0) h_mvtx2_dl2_sign_lm_us       -> Add(h_mvtx2_dl2_sign_lm_us_is       , h_mvtx2_dl2_sign_lm_us_nis);
    if(h_mvtx2_dl2_sign_mirrp_lm_us_nis != 0) h_mvtx2_dl2_sign_mirrp_lm_us -> Add(h_mvtx2_dl2_sign_mirrp_lm_us_is , h_mvtx2_dl2_sign_mirrp_lm_us_nis);
    if(h_mvtx2_dl2_sign_mirrm_lm_us_nis != 0) h_mvtx2_dl2_sign_mirrm_lm_us -> Add(h_mvtx2_dl2_sign_mirrm_lm_us_is , h_mvtx2_dl2_sign_mirrm_lm_us_nis);

    if(h_nrsecvtx_lm_ls_nis       != 0) h_nrsecvtx_lm_ls       -> Add(h_nrsecvtx_lm_ls_is       , h_nrsecvtx_lm_ls_nis);
    if(h_chi2_lm_ls_nis           != 0) h_chi2_lm_ls           -> Add(h_chi2_lm_ls_is           , h_chi2_lm_ls_nis);
    if(h_ndof_lm_ls_nis           != 0) h_ndof_lm_ls           -> Add(h_ndof_lm_ls_is           , h_ndof_lm_ls_nis);
    if(h_chi2ndof_lm_ls_nis       != 0) h_chi2ndof_lm_ls       -> Add(h_chi2ndof_lm_ls_is       , h_chi2ndof_lm_ls_nis);
    if(h_multiplicity_lm_ls_nis   != 0) h_multiplicity_lm_ls   -> Add(h_multiplicity_lm_ls_is   , h_multiplicity_lm_ls_nis);
    if(h_vtxmass_lm_ls_nis        != 0) h_vtxmass_lm_ls        -> Add(h_vtxmass_lm_ls_is        , h_vtxmass_lm_ls_nis);
    if(h_dl2_lm_ls_nis            != 0) h_dl2_lm_ls            -> Add(h_dl2_lm_ls_is            , h_dl2_lm_ls_nis);
    if(h_dl2_err_lm_ls_nis        != 0) h_dl2_err_lm_ls        -> Add(h_dl2_err_lm_ls_is        , h_dl2_err_lm_ls_nis);
    if(h_dl2_sign_lm_ls_nis       != 0) h_dl2_sign_lm_ls       -> Add(h_dl2_sign_lm_ls_is       , h_dl2_sign_lm_ls_nis);
    if(h_dl2_sign_mirrp_lm_ls_nis != 0) h_dl2_sign_mirrp_lm_ls -> Add(h_dl2_sign_mirrp_lm_ls_is , h_dl2_sign_mirrp_lm_ls_nis);
    if(h_dl2_sign_mirrm_lm_ls_nis != 0) h_dl2_sign_mirrm_lm_ls -> Add(h_dl2_sign_mirrm_lm_ls_is , h_dl2_sign_mirrm_lm_ls_nis);
    if(h_mvtx2_chi2_lm_ls_nis           != 0) h_mvtx2_chi2_lm_ls           -> Add(h_mvtx2_chi2_lm_ls_is           , h_mvtx2_chi2_lm_ls_nis);
    if(h_mvtx2_ndof_lm_ls_nis           != 0) h_mvtx2_ndof_lm_ls           -> Add(h_mvtx2_ndof_lm_ls_is           , h_mvtx2_ndof_lm_ls_nis);
    if(h_mvtx2_chi2ndof_lm_ls_nis       != 0) h_mvtx2_chi2ndof_lm_ls       -> Add(h_mvtx2_chi2ndof_lm_ls_is       , h_mvtx2_chi2ndof_lm_ls_nis);
    if(h_mvtx2_multiplicity_lm_ls_nis   != 0) h_mvtx2_multiplicity_lm_ls   -> Add(h_mvtx2_multiplicity_lm_ls_is   , h_mvtx2_multiplicity_lm_ls_nis);
    if(h_mvtx2_vtxmass_lm_ls_nis        != 0) h_mvtx2_vtxmass_lm_ls        -> Add(h_mvtx2_vtxmass_lm_ls_is        , h_mvtx2_vtxmass_lm_ls_nis);
    if(h_mvtx2_dl2_lm_ls_nis            != 0) h_mvtx2_dl2_lm_ls            -> Add(h_mvtx2_dl2_lm_ls_is            , h_mvtx2_dl2_lm_ls_nis);
    if(h_mvtx2_dl2_err_lm_ls_nis        != 0) h_mvtx2_dl2_err_lm_ls        -> Add(h_mvtx2_dl2_err_lm_ls_is        , h_mvtx2_dl2_err_lm_ls_nis);
    if(h_mvtx2_dl2_sign_lm_ls_nis       != 0) h_mvtx2_dl2_sign_lm_ls       -> Add(h_mvtx2_dl2_sign_lm_ls_is       , h_mvtx2_dl2_sign_lm_ls_nis);
    if(h_mvtx2_dl2_sign_mirrp_lm_ls_nis != 0) h_mvtx2_dl2_sign_mirrp_lm_ls -> Add(h_mvtx2_dl2_sign_mirrp_lm_ls_is , h_mvtx2_dl2_sign_mirrp_lm_ls_nis);
    if(h_mvtx2_dl2_sign_mirrm_lm_ls_nis != 0) h_mvtx2_dl2_sign_mirrm_lm_ls -> Add(h_mvtx2_dl2_sign_mirrm_lm_ls_is , h_mvtx2_dl2_sign_mirrm_lm_ls_nis);
  
    if(h_nrsecvtx_hm_us_nis       != 0) h_nrsecvtx_hm_us       -> Add(h_nrsecvtx_hm_us_is       , h_nrsecvtx_hm_us_nis);
    if(h_chi2_hm_us_nis           != 0) h_chi2_hm_us           -> Add(h_chi2_hm_us_is           , h_chi2_hm_us_nis);
    if(h_ndof_hm_us_nis           != 0) h_ndof_hm_us           -> Add(h_ndof_hm_us_is           , h_ndof_hm_us_nis);
    if(h_chi2ndof_hm_us_nis       != 0) h_chi2ndof_hm_us       -> Add(h_chi2ndof_hm_us_is       , h_chi2ndof_hm_us_nis);
    if(h_multiplicity_hm_us_nis   != 0) h_multiplicity_hm_us   -> Add(h_multiplicity_hm_us_is   , h_multiplicity_hm_us_nis);
    if(h_vtxmass_hm_us_nis        != 0) h_vtxmass_hm_us        -> Add(h_vtxmass_hm_us_is        , h_vtxmass_hm_us_nis);
    if(h_dl2_hm_us_nis            != 0) h_dl2_hm_us            -> Add(h_dl2_hm_us_is            , h_dl2_hm_us_nis);
    if(h_dl2_err_hm_us_nis        != 0) h_dl2_err_hm_us        -> Add(h_dl2_err_hm_us_is        , h_dl2_err_hm_us_nis);
    if(h_dl2_sign_hm_us_nis       != 0) h_dl2_sign_hm_us       -> Add(h_dl2_sign_hm_us_is       , h_dl2_sign_hm_us_nis);
    if(h_dl2_sign_mirrp_hm_us_nis != 0) h_dl2_sign_mirrp_hm_us -> Add(h_dl2_sign_mirrp_hm_us_is , h_dl2_sign_mirrp_hm_us_nis);
    if(h_dl2_sign_mirrm_hm_us_nis != 0) h_dl2_sign_mirrm_hm_us -> Add(h_dl2_sign_mirrm_hm_us_is , h_dl2_sign_mirrm_hm_us_nis);
    if(h_mvtx2_chi2_hm_us_nis           != 0) h_mvtx2_chi2_hm_us           -> Add(h_mvtx2_chi2_hm_us_is           , h_mvtx2_chi2_hm_us_nis);
    if(h_mvtx2_ndof_hm_us_nis           != 0) h_mvtx2_ndof_hm_us           -> Add(h_mvtx2_ndof_hm_us_is           , h_mvtx2_ndof_hm_us_nis);
    if(h_mvtx2_chi2ndof_hm_us_nis       != 0) h_mvtx2_chi2ndof_hm_us       -> Add(h_mvtx2_chi2ndof_hm_us_is       , h_mvtx2_chi2ndof_hm_us_nis);
    if(h_mvtx2_multiplicity_hm_us_nis   != 0) h_mvtx2_multiplicity_hm_us   -> Add(h_mvtx2_multiplicity_hm_us_is   , h_mvtx2_multiplicity_hm_us_nis);
    if(h_mvtx2_vtxmass_hm_us_nis        != 0) h_mvtx2_vtxmass_hm_us        -> Add(h_mvtx2_vtxmass_hm_us_is        , h_mvtx2_vtxmass_hm_us_nis);
    if(h_mvtx2_dl2_hm_us_nis            != 0) h_mvtx2_dl2_hm_us            -> Add(h_mvtx2_dl2_hm_us_is            , h_mvtx2_dl2_hm_us_nis);
    if(h_mvtx2_dl2_err_hm_us_nis        != 0) h_mvtx2_dl2_err_hm_us        -> Add(h_mvtx2_dl2_err_hm_us_is        , h_mvtx2_dl2_err_hm_us_nis);
    if(h_mvtx2_dl2_sign_hm_us_nis       != 0) h_mvtx2_dl2_sign_hm_us       -> Add(h_mvtx2_dl2_sign_hm_us_is       , h_mvtx2_dl2_sign_hm_us_nis);
    if(h_mvtx2_dl2_sign_mirrp_hm_us_nis != 0) h_mvtx2_dl2_sign_mirrp_hm_us -> Add(h_mvtx2_dl2_sign_mirrp_hm_us_is , h_mvtx2_dl2_sign_mirrp_hm_us_nis);
    if(h_mvtx2_dl2_sign_mirrm_hm_us_nis != 0) h_mvtx2_dl2_sign_mirrm_hm_us -> Add(h_mvtx2_dl2_sign_mirrm_hm_us_is , h_mvtx2_dl2_sign_mirrm_hm_us_nis);

    if(h_nrsecvtx_hm_ls_nis       != 0) h_nrsecvtx_hm_ls       -> Add(h_nrsecvtx_hm_ls_is       , h_nrsecvtx_hm_ls_nis);
    if(h_chi2_hm_ls_nis           != 0) h_chi2_hm_ls           -> Add(h_chi2_hm_ls_is           , h_chi2_hm_ls_nis);
    if(h_ndof_hm_ls_nis           != 0) h_ndof_hm_ls           -> Add(h_ndof_hm_ls_is           , h_ndof_hm_ls_nis);
    if(h_chi2ndof_hm_ls_nis       != 0) h_chi2ndof_hm_ls       -> Add(h_chi2ndof_hm_ls_is       , h_chi2ndof_hm_ls_nis);
    if(h_multiplicity_hm_ls_nis   != 0) h_multiplicity_hm_ls   -> Add(h_multiplicity_hm_ls_is   , h_multiplicity_hm_ls_nis);
    if(h_vtxmass_hm_ls_nis        != 0) h_vtxmass_hm_ls        -> Add(h_vtxmass_hm_ls_is        , h_vtxmass_hm_ls_nis);
    if(h_dl2_hm_ls_nis            != 0) h_dl2_hm_ls            -> Add(h_dl2_hm_ls_is            , h_dl2_hm_ls_nis);
    if(h_dl2_err_hm_ls_nis        != 0) h_dl2_err_hm_ls        -> Add(h_dl2_err_hm_ls_is        , h_dl2_err_hm_ls_nis);
    if(h_dl2_sign_hm_ls_nis       != 0) h_dl2_sign_hm_ls       -> Add(h_dl2_sign_hm_ls_is       , h_dl2_sign_hm_ls_nis);
    if(h_dl2_sign_mirrp_hm_ls_nis != 0) h_dl2_sign_mirrp_hm_ls -> Add(h_dl2_sign_mirrp_hm_ls_is , h_dl2_sign_mirrp_hm_ls_nis);
    if(h_dl2_sign_mirrm_hm_ls_nis != 0) h_dl2_sign_mirrm_hm_ls -> Add(h_dl2_sign_mirrm_hm_ls_is , h_dl2_sign_mirrm_hm_ls_nis);
    if(h_mvtx2_chi2_hm_ls_nis           != 0) h_mvtx2_chi2_hm_ls           -> Add(h_mvtx2_chi2_hm_ls_is           , h_mvtx2_chi2_hm_ls_nis);
    if(h_mvtx2_ndof_hm_ls_nis           != 0) h_mvtx2_ndof_hm_ls           -> Add(h_mvtx2_ndof_hm_ls_is           , h_mvtx2_ndof_hm_ls_nis);
    if(h_mvtx2_chi2ndof_hm_ls_nis       != 0) h_mvtx2_chi2ndof_hm_ls       -> Add(h_mvtx2_chi2ndof_hm_ls_is       , h_mvtx2_chi2ndof_hm_ls_nis);
    if(h_mvtx2_multiplicity_hm_ls_nis   != 0) h_mvtx2_multiplicity_hm_ls   -> Add(h_mvtx2_multiplicity_hm_ls_is   , h_mvtx2_multiplicity_hm_ls_nis);
    if(h_mvtx2_vtxmass_hm_ls_nis        != 0) h_mvtx2_vtxmass_hm_ls        -> Add(h_mvtx2_vtxmass_hm_ls_is        , h_mvtx2_vtxmass_hm_ls_nis);
    if(h_mvtx2_dl2_hm_ls_nis            != 0) h_mvtx2_dl2_hm_ls            -> Add(h_mvtx2_dl2_hm_ls_is            , h_mvtx2_dl2_hm_ls_nis);
    if(h_mvtx2_dl2_err_hm_ls_nis        != 0) h_mvtx2_dl2_err_hm_ls        -> Add(h_mvtx2_dl2_err_hm_ls_is        , h_mvtx2_dl2_err_hm_ls_nis);
    if(h_mvtx2_dl2_sign_hm_ls_nis       != 0) h_mvtx2_dl2_sign_hm_ls       -> Add(h_mvtx2_dl2_sign_hm_ls_is       , h_mvtx2_dl2_sign_hm_ls_nis);
    if(h_mvtx2_dl2_sign_mirrp_hm_ls_nis != 0) h_mvtx2_dl2_sign_mirrp_hm_ls -> Add(h_mvtx2_dl2_sign_mirrp_hm_ls_is , h_mvtx2_dl2_sign_mirrp_hm_ls_nis);
    if(h_mvtx2_dl2_sign_mirrm_hm_ls_nis != 0) h_mvtx2_dl2_sign_mirrm_hm_ls -> Add(h_mvtx2_dl2_sign_mirrm_hm_ls_is , h_mvtx2_dl2_sign_mirrm_hm_ls_nis);

//Append all histos:

    if(h_nrsecvtx_lm_us       != 0) file -> Append(h_nrsecvtx_lm_us       -> Clone("h_nrsecvtx_lm_us"));
    if(h_chi2_lm_us           != 0) file -> Append(h_chi2_lm_us           -> Clone("h_chi2_lm_us"));
    if(h_ndof_lm_us           != 0) file -> Append(h_ndof_lm_us           -> Clone("h_ndof_lm_us"));
    if(h_chi2ndof_lm_us       != 0) file -> Append(h_chi2ndof_lm_us       -> Clone("h_chi2ndof_lm_us"));
    if(h_multiplicity_lm_us   != 0) file -> Append(h_multiplicity_lm_us   -> Clone("h_multiplicity_lm_us"));
    if(h_vtxmass_lm_us        != 0) file -> Append(h_vtxmass_lm_us        -> Clone("h_vtxmass_lm_us"));
    if(h_dl2_lm_us            != 0) file -> Append(h_dl2_lm_us            -> Clone("h_dl2_lm_us"));
    if(h_dl2_err_lm_us        != 0) file -> Append(h_dl2_err_lm_us        -> Clone("h_dl2_err_lm_us"));
    if(h_dl2_sign_lm_us       != 0) file -> Append(h_dl2_sign_lm_us       -> Clone("h_dl2_sign_lm_us"));
    if(h_dl2_sign_mirrp_lm_us != 0) file -> Append(h_dl2_sign_mirrp_lm_us -> Clone("h_dl2_sign_mirrp_lm_us"));
    if(h_dl2_sign_mirrm_lm_us != 0) file -> Append(h_dl2_sign_mirrm_lm_us -> Clone("h_dl2_sign_mirrm_lm_us"));
    if(h_mvtx2_chi2_lm_us           != 0) file -> Append(h_mvtx2_chi2_lm_us           -> Clone("h_mvtx2_chi2_lm_us"));
    if(h_mvtx2_ndof_lm_us           != 0) file -> Append(h_mvtx2_ndof_lm_us           -> Clone("h_mvtx2_ndof_lm_us"));
    if(h_mvtx2_chi2ndof_lm_us       != 0) file -> Append(h_mvtx2_chi2ndof_lm_us       -> Clone("h_mvtx2_chi2ndof_lm_us"));
    if(h_mvtx2_multiplicity_lm_us   != 0) file -> Append(h_mvtx2_multiplicity_lm_us   -> Clone("h_mvtx2_multiplicity_lm_us"));
    if(h_mvtx2_vtxmass_lm_us        != 0) file -> Append(h_mvtx2_vtxmass_lm_us        -> Clone("h_mvtx2_vtxmass_lm_us"));
    if(h_mvtx2_dl2_lm_us            != 0) file -> Append(h_mvtx2_dl2_lm_us            -> Clone("h_mvtx2_dl2_lm_us"));
    if(h_mvtx2_dl2_err_lm_us        != 0) file -> Append(h_mvtx2_dl2_err_lm_us        -> Clone("h_mvtx2_dl2_err_lm_us"));
    if(h_mvtx2_dl2_sign_lm_us       != 0) file -> Append(h_mvtx2_dl2_sign_lm_us       -> Clone("h_mvtx2_dl2_sign_lm_us"));
    if(h_mvtx2_dl2_sign_mirrp_lm_us != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_lm_us -> Clone("h_mvtx2_dl2_sign_mirrp_lm_us"));
    if(h_mvtx2_dl2_sign_mirrm_lm_us != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_lm_us -> Clone("h_mvtx2_dl2_sign_mirrm_lm_us"));

    if(h_nrsecvtx_lm_ls       != 0) file -> Append(h_nrsecvtx_lm_ls       -> Clone("h_nrsecvtx_lm_ls"));
    if(h_chi2_lm_ls           != 0) file -> Append(h_chi2_lm_ls           -> Clone("h_chi2_lm_ls"));
    if(h_ndof_lm_ls           != 0) file -> Append(h_ndof_lm_ls           -> Clone("h_ndof_lm_ls"));
    if(h_chi2ndof_lm_ls       != 0) file -> Append(h_chi2ndof_lm_ls       -> Clone("h_chi2ndof_lm_ls"));
    if(h_multiplicity_lm_ls   != 0) file -> Append(h_multiplicity_lm_ls   -> Clone("h_multiplicity_lm_ls"));
    if(h_vtxmass_lm_ls        != 0) file -> Append(h_vtxmass_lm_ls        -> Clone("h_vtxmass_lm_ls"));
    if(h_dl2_lm_ls            != 0) file -> Append(h_dl2_lm_ls            -> Clone("h_dl2_lm_ls"));
    if(h_dl2_err_lm_ls        != 0) file -> Append(h_dl2_err_lm_ls        -> Clone("h_dl2_err_lm_ls"));
    if(h_dl2_sign_lm_ls       != 0) file -> Append(h_dl2_sign_lm_ls       -> Clone("h_dl2_sign_lm_ls"));
    if(h_dl2_sign_mirrp_lm_ls != 0) file -> Append(h_dl2_sign_mirrp_lm_ls -> Clone("h_dl2_sign_mirrp_lm_ls"));
    if(h_dl2_sign_mirrm_lm_ls != 0) file -> Append(h_dl2_sign_mirrm_lm_ls -> Clone("h_dl2_sign_mirrm_lm_ls"));
    if(h_mvtx2_chi2_lm_ls           != 0) file -> Append(h_mvtx2_chi2_lm_ls           -> Clone("h_mvtx2_chi2_lm_ls"));
    if(h_mvtx2_ndof_lm_ls           != 0) file -> Append(h_mvtx2_ndof_lm_ls           -> Clone("h_mvtx2_ndof_lm_ls"));
    if(h_mvtx2_chi2ndof_lm_ls       != 0) file -> Append(h_mvtx2_chi2ndof_lm_ls       -> Clone("h_mvtx2_chi2ndof_lm_ls"));
    if(h_mvtx2_multiplicity_lm_ls   != 0) file -> Append(h_mvtx2_multiplicity_lm_ls   -> Clone("h_mvtx2_multiplicity_lm_ls"));
    if(h_mvtx2_vtxmass_lm_ls        != 0) file -> Append(h_mvtx2_vtxmass_lm_ls        -> Clone("h_mvtx2_vtxmass_lm_ls"));
    if(h_mvtx2_dl2_lm_ls            != 0) file -> Append(h_mvtx2_dl2_lm_ls            -> Clone("h_mvtx2_dl2_lm_ls"));
    if(h_mvtx2_dl2_err_lm_ls        != 0) file -> Append(h_mvtx2_dl2_err_lm_ls        -> Clone("h_mvtx2_dl2_err_lm_ls"));
    if(h_mvtx2_dl2_sign_lm_ls       != 0) file -> Append(h_mvtx2_dl2_sign_lm_ls       -> Clone("h_mvtx2_dl2_sign_lm_ls"));
    if(h_mvtx2_dl2_sign_mirrp_lm_ls != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_lm_ls -> Clone("h_mvtx2_dl2_sign_mirrp_lm_ls"));
    if(h_mvtx2_dl2_sign_mirrm_lm_ls != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_lm_ls -> Clone("h_mvtx2_dl2_sign_mirrm_lm_ls"));

    if(h_nrsecvtx_hm_us       != 0) file -> Append(h_nrsecvtx_hm_us       -> Clone("h_nrsecvtx_hm_us"));
    if(h_chi2_hm_us           != 0) file -> Append(h_chi2_hm_us           -> Clone("h_chi2_hm_us"));
    if(h_ndof_hm_us           != 0) file -> Append(h_ndof_hm_us           -> Clone("h_ndof_hm_us"));
    if(h_chi2ndof_hm_us       != 0) file -> Append(h_chi2ndof_hm_us       -> Clone("h_chi2ndof_hm_us"));
    if(h_multiplicity_hm_us   != 0) file -> Append(h_multiplicity_hm_us   -> Clone("h_multiplicity_hm_us"));
    if(h_vtxmass_hm_us        != 0) file -> Append(h_vtxmass_hm_us        -> Clone("h_vtxmass_hm_us"));
    if(h_dl2_hm_us            != 0) file -> Append(h_dl2_hm_us            -> Clone("h_dl2_hm_us"));
    if(h_dl2_err_hm_us        != 0) file -> Append(h_dl2_err_hm_us        -> Clone("h_dl2_err_hm_us"));
    if(h_dl2_sign_hm_us       != 0) file -> Append(h_dl2_sign_hm_us       -> Clone("h_dl2_sign_hm_us"));
    if(h_dl2_sign_mirrp_hm_us != 0) file -> Append(h_dl2_sign_mirrp_hm_us -> Clone("h_dl2_sign_mirrp_hm_us"));
    if(h_dl2_sign_mirrm_hm_us != 0) file -> Append(h_dl2_sign_mirrm_hm_us -> Clone("h_dl2_sign_mirrm_hm_us"));
    if(h_mvtx2_chi2_hm_us           != 0) file -> Append(h_mvtx2_chi2_hm_us           -> Clone("h_mvtx2_chi2_hm_us"));
    if(h_mvtx2_ndof_hm_us           != 0) file -> Append(h_mvtx2_ndof_hm_us           -> Clone("h_mvtx2_ndof_hm_us"));
    if(h_mvtx2_chi2ndof_hm_us       != 0) file -> Append(h_mvtx2_chi2ndof_hm_us       -> Clone("h_mvtx2_chi2ndof_hm_us"));
    if(h_mvtx2_multiplicity_hm_us   != 0) file -> Append(h_mvtx2_multiplicity_hm_us   -> Clone("h_mvtx2_multiplicity_hm_us"));
    if(h_mvtx2_vtxmass_hm_us        != 0) file -> Append(h_mvtx2_vtxmass_hm_us        -> Clone("h_mvtx2_vtxmass_hm_us"));
    if(h_mvtx2_dl2_hm_us            != 0) file -> Append(h_mvtx2_dl2_hm_us            -> Clone("h_mvtx2_dl2_hm_us"));
    if(h_mvtx2_dl2_err_hm_us        != 0) file -> Append(h_mvtx2_dl2_err_hm_us        -> Clone("h_mvtx2_dl2_err_hm_us"));
    if(h_mvtx2_dl2_sign_hm_us       != 0) file -> Append(h_mvtx2_dl2_sign_hm_us       -> Clone("h_mvtx2_dl2_sign_hm_us"));
    if(h_mvtx2_dl2_sign_mirrp_hm_us != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_hm_us -> Clone("h_mvtx2_dl2_sign_mirrp_hm_us"));
    if(h_mvtx2_dl2_sign_mirrm_hm_us != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_hm_us -> Clone("h_mvtx2_dl2_sign_mirrm_hm_us"));

    if(h_nrsecvtx_hm_ls       != 0) file -> Append(h_nrsecvtx_hm_ls       -> Clone("h_nrsecvtx_hm_ls"));
    if(h_chi2_hm_ls           != 0) file -> Append(h_chi2_hm_ls           -> Clone("h_chi2_hm_ls"));
    if(h_ndof_hm_ls           != 0) file -> Append(h_ndof_hm_ls           -> Clone("h_ndof_hm_ls"));
    if(h_chi2ndof_hm_ls       != 0) file -> Append(h_chi2ndof_hm_ls       -> Clone("h_chi2ndof_hm_ls"));
    if(h_multiplicity_hm_ls   != 0) file -> Append(h_multiplicity_hm_ls   -> Clone("h_multiplicity_hm_ls"));
    if(h_vtxmass_hm_ls        != 0) file -> Append(h_vtxmass_hm_ls        -> Clone("h_vtxmass_hm_ls"));
    if(h_dl2_hm_ls            != 0) file -> Append(h_dl2_hm_ls            -> Clone("h_dl2_hm_ls"));
    if(h_dl2_err_hm_ls        != 0) file -> Append(h_dl2_err_hm_ls        -> Clone("h_dl2_err_hm_ls"));
    if(h_dl2_sign_hm_ls       != 0) file -> Append(h_dl2_sign_hm_ls       -> Clone("h_dl2_sign_hm_ls"));
    if(h_dl2_sign_mirrp_hm_ls != 0) file -> Append(h_dl2_sign_mirrp_hm_ls -> Clone("h_dl2_sign_mirrp_hm_ls"));
    if(h_dl2_sign_mirrm_hm_ls != 0) file -> Append(h_dl2_sign_mirrm_hm_ls -> Clone("h_dl2_sign_mirrm_hm_ls"));
    if(h_mvtx2_chi2_hm_ls           != 0) file -> Append(h_mvtx2_chi2_hm_ls           -> Clone("h_mvtx2_chi2_hm_ls"));
    if(h_mvtx2_ndof_hm_ls           != 0) file -> Append(h_mvtx2_ndof_hm_ls           -> Clone("h_mvtx2_ndof_hm_ls"));
    if(h_mvtx2_chi2ndof_hm_ls       != 0) file -> Append(h_mvtx2_chi2ndof_hm_ls       -> Clone("h_mvtx2_chi2ndof_hm_ls"));
    if(h_mvtx2_multiplicity_hm_ls   != 0) file -> Append(h_mvtx2_multiplicity_hm_ls   -> Clone("h_mvtx2_multiplicity_hm_ls"));
    if(h_mvtx2_vtxmass_hm_ls        != 0) file -> Append(h_mvtx2_vtxmass_hm_ls        -> Clone("h_mvtx2_vtxmass_hm_ls"));
    if(h_mvtx2_dl2_hm_ls            != 0) file -> Append(h_mvtx2_dl2_hm_ls            -> Clone("h_mvtx2_dl2_hm_ls"));
    if(h_mvtx2_dl2_err_hm_ls        != 0) file -> Append(h_mvtx2_dl2_err_hm_ls        -> Clone("h_mvtx2_dl2_err_hm_ls"));
    if(h_mvtx2_dl2_sign_hm_ls       != 0) file -> Append(h_mvtx2_dl2_sign_hm_ls       -> Clone("h_mvtx2_dl2_sign_hm_ls"));
    if(h_mvtx2_dl2_sign_mirrp_hm_ls != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_hm_ls -> Clone("h_mvtx2_dl2_sign_mirrp_hm_ls"));
    if(h_mvtx2_dl2_sign_mirrm_hm_ls != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_hm_ls -> Clone("h_mvtx2_dl2_sign_mirrm_hm_ls"));

// ***************************************************************************************
// append isolated histos:
// ***************************************************************************************

    if(h_nrsecvtx_lm_us_is       != 0) file -> Append(h_nrsecvtx_lm_us_is       -> Clone("h_nrsecvtx_lm_us_is"));
    if(h_chi2_lm_us_is           != 0) file -> Append(h_chi2_lm_us_is           -> Clone("h_chi2_lm_us_is"));
    if(h_ndof_lm_us_is           != 0) file -> Append(h_ndof_lm_us_is           -> Clone("h_ndof_lm_us_is"));
    if(h_chi2ndof_lm_us_is       != 0) file -> Append(h_chi2ndof_lm_us_is       -> Clone("h_chi2ndof_lm_us_is"));
    if(h_multiplicity_lm_us_is   != 0) file -> Append(h_multiplicity_lm_us_is   -> Clone("h_multiplicity_lm_us_is"));
    if(h_vtxmass_lm_us_is        != 0) file -> Append(h_vtxmass_lm_us_is        -> Clone("h_vtxmass_lm_us_is"));
    if(h_dl2_lm_us_is            != 0) file -> Append(h_dl2_lm_us_is            -> Clone("h_dl2_lm_us_is"));
    if(h_dl2_err_lm_us_is        != 0) file -> Append(h_dl2_err_lm_us_is        -> Clone("h_dl2_err_lm_us_is"));
    if(h_dl2_sign_lm_us_is       != 0) file -> Append(h_dl2_sign_lm_us_is       -> Clone("h_dl2_sign_lm_us_is"));
    if(h_dl2_sign_mirrp_lm_us_is != 0) file -> Append(h_dl2_sign_mirrp_lm_us_is -> Clone("h_dl2_sign_mirrp_lm_us_is"));
    if(h_dl2_sign_mirrm_lm_us_is != 0) file -> Append(h_dl2_sign_mirrm_lm_us_is -> Clone("h_dl2_sign_mirrm_lm_us_is"));
    if(h_mvtx2_chi2_lm_us_is           != 0) file -> Append(h_mvtx2_chi2_lm_us_is           -> Clone("h_mvtx2_chi2_lm_us_is"));
    if(h_mvtx2_ndof_lm_us_is           != 0) file -> Append(h_mvtx2_ndof_lm_us_is           -> Clone("h_mvtx2_ndof_lm_us_is"));
    if(h_mvtx2_chi2ndof_lm_us_is       != 0) file -> Append(h_mvtx2_chi2ndof_lm_us_is       -> Clone("h_mvtx2_chi2ndof_lm_us_is"));
    if(h_mvtx2_multiplicity_lm_us_is   != 0) file -> Append(h_mvtx2_multiplicity_lm_us_is   -> Clone("h_mvtx2_multiplicity_lm_us_is"));
    if(h_mvtx2_vtxmass_lm_us_is        != 0) file -> Append(h_mvtx2_vtxmass_lm_us_is        -> Clone("h_mvtx2_vtxmass_lm_us_is"));
    if(h_mvtx2_dl2_lm_us_is            != 0) file -> Append(h_mvtx2_dl2_lm_us_is            -> Clone("h_mvtx2_dl2_lm_us_is"));
    if(h_mvtx2_dl2_err_lm_us_is        != 0) file -> Append(h_mvtx2_dl2_err_lm_us_is        -> Clone("h_mvtx2_dl2_err_lm_us_is"));
    if(h_mvtx2_dl2_sign_lm_us_is       != 0) file -> Append(h_mvtx2_dl2_sign_lm_us_is       -> Clone("h_mvtx2_dl2_sign_lm_us_is"));
    if(h_mvtx2_dl2_sign_mirrp_lm_us_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_lm_us_is -> Clone("h_mvtx2_dl2_sign_mirrp_lm_us_is"));
    if(h_mvtx2_dl2_sign_mirrm_lm_us_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_lm_us_is -> Clone("h_mvtx2_dl2_sign_mirrm_lm_us_is"));

    if(h_nrsecvtx_lm_ls_is       != 0) file -> Append(h_nrsecvtx_lm_ls_is       -> Clone("h_nrsecvtx_lm_ls_is"));
    if(h_chi2_lm_ls_is           != 0) file -> Append(h_chi2_lm_ls_is           -> Clone("h_chi2_lm_ls_is"));
    if(h_ndof_lm_ls_is           != 0) file -> Append(h_ndof_lm_ls_is           -> Clone("h_ndof_lm_ls_is"));
    if(h_chi2ndof_lm_ls_is       != 0) file -> Append(h_chi2ndof_lm_ls_is       -> Clone("h_chi2ndof_lm_ls_is"));
    if(h_multiplicity_lm_ls_is   != 0) file -> Append(h_multiplicity_lm_ls_is   -> Clone("h_multiplicity_lm_ls_is"));
    if(h_vtxmass_lm_ls_is        != 0) file -> Append(h_vtxmass_lm_ls_is        -> Clone("h_vtxmass_lm_ls_is"));
    if(h_dl2_lm_ls_is            != 0) file -> Append(h_dl2_lm_ls_is            -> Clone("h_dl2_lm_ls_is"));
    if(h_dl2_err_lm_ls_is        != 0) file -> Append(h_dl2_err_lm_ls_is        -> Clone("h_dl2_err_lm_ls_is"));
    if(h_dl2_sign_lm_ls_is       != 0) file -> Append(h_dl2_sign_lm_ls_is       -> Clone("h_dl2_sign_lm_ls_is"));
    if(h_dl2_sign_mirrp_lm_ls_is != 0) file -> Append(h_dl2_sign_mirrp_lm_ls_is -> Clone("h_dl2_sign_mirrp_lm_ls_is"));
    if(h_dl2_sign_mirrm_lm_ls_is != 0) file -> Append(h_dl2_sign_mirrm_lm_ls_is -> Clone("h_dl2_sign_mirrm_lm_ls_is"));
    if(h_mvtx2_chi2_lm_ls_is           != 0) file -> Append(h_mvtx2_chi2_lm_ls_is           -> Clone("h_mvtx2_chi2_lm_ls_is"));
    if(h_mvtx2_ndof_lm_ls_is           != 0) file -> Append(h_mvtx2_ndof_lm_ls_is           -> Clone("h_mvtx2_ndof_lm_ls_is"));
    if(h_mvtx2_chi2ndof_lm_ls_is       != 0) file -> Append(h_mvtx2_chi2ndof_lm_ls_is       -> Clone("h_mvtx2_chi2ndof_lm_ls_is"));
    if(h_mvtx2_multiplicity_lm_ls_is   != 0) file -> Append(h_mvtx2_multiplicity_lm_ls_is   -> Clone("h_mvtx2_multiplicity_lm_ls_is"));
    if(h_mvtx2_vtxmass_lm_ls_is        != 0) file -> Append(h_mvtx2_vtxmass_lm_ls_is        -> Clone("h_mvtx2_vtxmass_lm_ls_is"));
    if(h_mvtx2_dl2_lm_ls_is            != 0) file -> Append(h_mvtx2_dl2_lm_ls_is            -> Clone("h_mvtx2_dl2_lm_ls_is"));
    if(h_mvtx2_dl2_err_lm_ls_is        != 0) file -> Append(h_mvtx2_dl2_err_lm_ls_is        -> Clone("h_mvtx2_dl2_err_lm_ls_is"));
    if(h_mvtx2_dl2_sign_lm_ls_is       != 0) file -> Append(h_mvtx2_dl2_sign_lm_ls_is       -> Clone("h_mvtx2_dl2_sign_lm_ls_is"));
    if(h_mvtx2_dl2_sign_mirrp_lm_ls_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_lm_ls_is -> Clone("h_mvtx2_dl2_sign_mirrp_lm_ls_is"));
    if(h_mvtx2_dl2_sign_mirrm_lm_ls_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_lm_ls_is -> Clone("h_mvtx2_dl2_sign_mirrm_lm_ls_is"));

    if(h_nrsecvtx_hm_us_is       != 0) file -> Append(h_nrsecvtx_hm_us_is       -> Clone("h_nrsecvtx_hm_us_is"));
    if(h_chi2_hm_us_is           != 0) file -> Append(h_chi2_hm_us_is           -> Clone("h_chi2_hm_us_is"));
    if(h_ndof_hm_us_is           != 0) file -> Append(h_ndof_hm_us_is           -> Clone("h_ndof_hm_us_is"));
    if(h_chi2ndof_hm_us_is       != 0) file -> Append(h_chi2ndof_hm_us_is       -> Clone("h_chi2ndof_hm_us_is"));
    if(h_multiplicity_hm_us_is   != 0) file -> Append(h_multiplicity_hm_us_is   -> Clone("h_multiplicity_hm_us_is"));
    if(h_vtxmass_hm_us_is        != 0) file -> Append(h_vtxmass_hm_us_is        -> Clone("h_vtxmass_hm_us_is"));
    if(h_dl2_hm_us_is            != 0) file -> Append(h_dl2_hm_us_is            -> Clone("h_dl2_hm_us_is"));
    if(h_dl2_err_hm_us_is        != 0) file -> Append(h_dl2_err_hm_us_is        -> Clone("h_dl2_err_hm_us_is"));
    if(h_dl2_sign_hm_us_is       != 0) file -> Append(h_dl2_sign_hm_us_is       -> Clone("h_dl2_sign_hm_us_is"));
    if(h_dl2_sign_mirrp_hm_us_is != 0) file -> Append(h_dl2_sign_mirrp_hm_us_is -> Clone("h_dl2_sign_mirrp_hm_us_is"));
    if(h_dl2_sign_mirrm_hm_us_is != 0) file -> Append(h_dl2_sign_mirrm_hm_us_is -> Clone("h_dl2_sign_mirrm_hm_us_is"));
    if(h_mvtx2_chi2_hm_us_is           != 0) file -> Append(h_mvtx2_chi2_hm_us_is           -> Clone("h_mvtx2_chi2_hm_us_is"));
    if(h_mvtx2_ndof_hm_us_is           != 0) file -> Append(h_mvtx2_ndof_hm_us_is           -> Clone("h_mvtx2_ndof_hm_us_is"));
    if(h_mvtx2_chi2ndof_hm_us_is       != 0) file -> Append(h_mvtx2_chi2ndof_hm_us_is       -> Clone("h_mvtx2_chi2ndof_hm_us_is"));
    if(h_mvtx2_multiplicity_hm_us_is   != 0) file -> Append(h_mvtx2_multiplicity_hm_us_is   -> Clone("h_mvtx2_multiplicity_hm_us_is"));
    if(h_mvtx2_vtxmass_hm_us_is        != 0) file -> Append(h_mvtx2_vtxmass_hm_us_is        -> Clone("h_mvtx2_vtxmass_hm_us_is"));
    if(h_mvtx2_dl2_hm_us_is            != 0) file -> Append(h_mvtx2_dl2_hm_us_is            -> Clone("h_mvtx2_dl2_hm_us_is"));
    if(h_mvtx2_dl2_err_hm_us_is        != 0) file -> Append(h_mvtx2_dl2_err_hm_us_is        -> Clone("h_mvtx2_dl2_err_hm_us_is"));
    if(h_mvtx2_dl2_sign_hm_us_is       != 0) file -> Append(h_mvtx2_dl2_sign_hm_us_is       -> Clone("h_mvtx2_dl2_sign_hm_us_is"));
    if(h_mvtx2_dl2_sign_mirrp_hm_us_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_hm_us_is -> Clone("h_mvtx2_dl2_sign_mirrp_hm_us_is"));
    if(h_mvtx2_dl2_sign_mirrm_hm_us_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_hm_us_is -> Clone("h_mvtx2_dl2_sign_mirrm_hm_us_is"));

    if(h_nrsecvtx_hm_ls_is       != 0) file -> Append(h_nrsecvtx_hm_ls_is       -> Clone("h_nrsecvtx_hm_ls_is"));
    if(h_chi2_hm_ls_is           != 0) file -> Append(h_chi2_hm_ls_is           -> Clone("h_chi2_hm_ls_is"));
    if(h_ndof_hm_ls_is           != 0) file -> Append(h_ndof_hm_ls_is           -> Clone("h_ndof_hm_ls_is"));
    if(h_chi2ndof_hm_ls_is       != 0) file -> Append(h_chi2ndof_hm_ls_is       -> Clone("h_chi2ndof_hm_ls_is"));
    if(h_multiplicity_hm_ls_is   != 0) file -> Append(h_multiplicity_hm_ls_is   -> Clone("h_multiplicity_hm_ls_is"));
    if(h_vtxmass_hm_ls_is        != 0) file -> Append(h_vtxmass_hm_ls_is        -> Clone("h_vtxmass_hm_ls_is"));
    if(h_dl2_hm_ls_is            != 0) file -> Append(h_dl2_hm_ls_is            -> Clone("h_dl2_hm_ls_is"));
    if(h_dl2_err_hm_ls_is        != 0) file -> Append(h_dl2_err_hm_ls_is        -> Clone("h_dl2_err_hm_ls_is"));
    if(h_dl2_sign_hm_ls_is       != 0) file -> Append(h_dl2_sign_hm_ls_is       -> Clone("h_dl2_sign_hm_ls_is"));
    if(h_dl2_sign_mirrp_hm_ls_is != 0) file -> Append(h_dl2_sign_mirrp_hm_ls_is -> Clone("h_dl2_sign_mirrp_hm_ls_is"));
    if(h_dl2_sign_mirrm_hm_ls_is != 0) file -> Append(h_dl2_sign_mirrm_hm_ls_is -> Clone("h_dl2_sign_mirrm_hm_ls_is"));
    if(h_mvtx2_chi2_hm_ls_is           != 0) file -> Append(h_mvtx2_chi2_hm_ls_is           -> Clone("h_mvtx2_chi2_hm_ls_is"));
    if(h_mvtx2_ndof_hm_ls_is           != 0) file -> Append(h_mvtx2_ndof_hm_ls_is           -> Clone("h_mvtx2_ndof_hm_ls_is"));
    if(h_mvtx2_chi2ndof_hm_ls_is       != 0) file -> Append(h_mvtx2_chi2ndof_hm_ls_is       -> Clone("h_mvtx2_chi2ndof_hm_ls_is"));
    if(h_mvtx2_multiplicity_hm_ls_is   != 0) file -> Append(h_mvtx2_multiplicity_hm_ls_is   -> Clone("h_mvtx2_multiplicity_hm_ls_is"));
    if(h_mvtx2_vtxmass_hm_ls_is        != 0) file -> Append(h_mvtx2_vtxmass_hm_ls_is        -> Clone("h_mvtx2_vtxmass_hm_ls_is"));
    if(h_mvtx2_dl2_hm_ls_is            != 0) file -> Append(h_mvtx2_dl2_hm_ls_is            -> Clone("h_mvtx2_dl2_hm_ls_is"));
    if(h_mvtx2_dl2_err_hm_ls_is        != 0) file -> Append(h_mvtx2_dl2_err_hm_ls_is        -> Clone("h_mvtx2_dl2_err_hm_ls_is"));
    if(h_mvtx2_dl2_sign_hm_ls_is       != 0) file -> Append(h_mvtx2_dl2_sign_hm_ls_is       -> Clone("h_mvtx2_dl2_sign_hm_ls_is"));
    if(h_mvtx2_dl2_sign_mirrp_hm_ls_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_hm_ls_is -> Clone("h_mvtx2_dl2_sign_mirrp_hm_ls_is"));
    if(h_mvtx2_dl2_sign_mirrm_hm_ls_is != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_hm_ls_is -> Clone("h_mvtx2_dl2_sign_mirrm_hm_ls_is"));

//***************************************************************************************
// append non-isolated histos:
//***************************************************************************************
 
    if(h_nrsecvtx_lm_us_nis       != 0) file -> Append(h_nrsecvtx_lm_us_nis       -> Clone("h_nrsecvtx_lm_us_nis"));
    if(h_chi2_lm_us_nis           != 0) file -> Append(h_chi2_lm_us_nis           -> Clone("h_chi2_lm_us_nis"));
    if(h_ndof_lm_us_nis           != 0) file -> Append(h_ndof_lm_us_nis           -> Clone("h_ndof_lm_us_nis"));
    if(h_chi2ndof_lm_us_nis       != 0) file -> Append(h_chi2ndof_lm_us_nis       -> Clone("h_chi2ndof_lm_us_nis"));
    if(h_multiplicity_lm_us_nis   != 0) file -> Append(h_multiplicity_lm_us_nis   -> Clone("h_multiplicity_lm_us_nis"));
    if(h_vtxmass_lm_us_nis        != 0) file -> Append(h_vtxmass_lm_us_nis        -> Clone("h_vtxmass_lm_us_nis"));
    if(h_dl2_lm_us_nis            != 0) file -> Append(h_dl2_lm_us_nis            -> Clone("h_dl2_lm_us_nis"));
    if(h_dl2_err_lm_us_nis        != 0) file -> Append(h_dl2_err_lm_us_nis        -> Clone("h_dl2_err_lm_us_nis"));
    if(h_dl2_sign_lm_us_nis       != 0) file -> Append(h_dl2_sign_lm_us_nis       -> Clone("h_dl2_sign_lm_us_nis"));
    if(h_dl2_sign_mirrp_lm_us_nis != 0) file -> Append(h_dl2_sign_mirrp_lm_us_nis -> Clone("h_dl2_sign_mirrp_lm_us_nis"));
    if(h_dl2_sign_mirrm_lm_us_nis != 0) file -> Append(h_dl2_sign_mirrm_lm_us_nis -> Clone("h_dl2_sign_mirrm_lm_us_nis"));
    if(h_mvtx2_chi2_lm_us_nis           != 0) file -> Append(h_mvtx2_chi2_lm_us_nis           -> Clone("h_mvtx2_chi2_lm_us_nis"));
    if(h_mvtx2_ndof_lm_us_nis           != 0) file -> Append(h_mvtx2_ndof_lm_us_nis           -> Clone("h_mvtx2_ndof_lm_us_nis"));
    if(h_mvtx2_chi2ndof_lm_us_nis       != 0) file -> Append(h_mvtx2_chi2ndof_lm_us_nis       -> Clone("h_mvtx2_chi2ndof_lm_us_nis"));
    if(h_mvtx2_multiplicity_lm_us_nis   != 0) file -> Append(h_mvtx2_multiplicity_lm_us_nis   -> Clone("h_mvtx2_multiplicity_lm_us_nis"));
    if(h_mvtx2_vtxmass_lm_us_nis        != 0) file -> Append(h_mvtx2_vtxmass_lm_us_nis        -> Clone("h_mvtx2_vtxmass_lm_us_nis"));
    if(h_mvtx2_dl2_lm_us_nis            != 0) file -> Append(h_mvtx2_dl2_lm_us_nis            -> Clone("h_mvtx2_dl2_lm_us_nis"));
    if(h_mvtx2_dl2_err_lm_us_nis        != 0) file -> Append(h_mvtx2_dl2_err_lm_us_nis        -> Clone("h_mvtx2_dl2_err_lm_us_nis"));
    if(h_mvtx2_dl2_sign_lm_us_nis       != 0) file -> Append(h_mvtx2_dl2_sign_lm_us_nis       -> Clone("h_mvtx2_dl2_sign_lm_us_nis"));
    if(h_mvtx2_dl2_sign_mirrp_lm_us_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_lm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrp_lm_us_nis"));
    if(h_mvtx2_dl2_sign_mirrm_lm_us_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_lm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrm_lm_us_nis"));

    if(h_nrsecvtx_lm_ls_nis       != 0) file -> Append(h_nrsecvtx_lm_ls_nis       -> Clone("h_nrsecvtx_lm_ls_nis"));
    if(h_chi2_lm_ls_nis           != 0) file -> Append(h_chi2_lm_ls_nis           -> Clone("h_chi2_lm_ls_nis"));
    if(h_ndof_lm_ls_nis           != 0) file -> Append(h_ndof_lm_ls_nis           -> Clone("h_ndof_lm_ls_nis"));
    if(h_chi2ndof_lm_ls_nis       != 0) file -> Append(h_chi2ndof_lm_ls_nis       -> Clone("h_chi2ndof_lm_ls_nis"));
    if(h_multiplicity_lm_ls_nis   != 0) file -> Append(h_multiplicity_lm_ls_nis   -> Clone("h_multiplicity_lm_ls_nis"));
    if(h_vtxmass_lm_ls_nis        != 0) file -> Append(h_vtxmass_lm_ls_nis        -> Clone("h_vtxmass_lm_ls_nis"));
    if(h_dl2_lm_ls_nis            != 0) file -> Append(h_dl2_lm_ls_nis            -> Clone("h_dl2_lm_ls_nis"));
    if(h_dl2_err_lm_ls_nis        != 0) file -> Append(h_dl2_err_lm_ls_nis        -> Clone("h_dl2_err_lm_ls_nis"));
    if(h_dl2_sign_lm_ls_nis       != 0) file -> Append(h_dl2_sign_lm_ls_nis       -> Clone("h_dl2_sign_lm_ls_nis"));
    if(h_dl2_sign_mirrp_lm_ls_nis != 0) file -> Append(h_dl2_sign_mirrp_lm_ls_nis -> Clone("h_dl2_sign_mirrp_lm_ls_nis"));
    if(h_dl2_sign_mirrm_lm_ls_nis != 0) file -> Append(h_dl2_sign_mirrm_lm_ls_nis -> Clone("h_dl2_sign_mirrm_lm_ls_nis"));
    if(h_mvtx2_chi2_lm_ls_nis           != 0) file -> Append(h_mvtx2_chi2_lm_ls_nis           -> Clone("h_mvtx2_chi2_lm_ls_nis"));
    if(h_mvtx2_ndof_lm_ls_nis           != 0) file -> Append(h_mvtx2_ndof_lm_ls_nis           -> Clone("h_mvtx2_ndof_lm_ls_nis"));
    if(h_mvtx2_chi2ndof_lm_ls_nis       != 0) file -> Append(h_mvtx2_chi2ndof_lm_ls_nis       -> Clone("h_mvtx2_chi2ndof_lm_ls_nis"));
    if(h_mvtx2_multiplicity_lm_ls_nis   != 0) file -> Append(h_mvtx2_multiplicity_lm_ls_nis   -> Clone("h_mvtx2_multiplicity_lm_ls_nis"));
    if(h_mvtx2_vtxmass_lm_ls_nis        != 0) file -> Append(h_mvtx2_vtxmass_lm_ls_nis        -> Clone("h_mvtx2_vtxmass_lm_ls_nis"));
    if(h_mvtx2_dl2_lm_ls_nis            != 0) file -> Append(h_mvtx2_dl2_lm_ls_nis            -> Clone("h_mvtx2_dl2_lm_ls_nis"));
    if(h_mvtx2_dl2_err_lm_ls_nis        != 0) file -> Append(h_mvtx2_dl2_err_lm_ls_nis        -> Clone("h_mvtx2_dl2_err_lm_ls_nis"));
    if(h_mvtx2_dl2_sign_lm_ls_nis       != 0) file -> Append(h_mvtx2_dl2_sign_lm_ls_nis       -> Clone("h_mvtx2_dl2_sign_lm_ls_nis"));
    if(h_mvtx2_dl2_sign_mirrp_lm_ls_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_lm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrp_lm_ls_nis"));
    if(h_mvtx2_dl2_sign_mirrm_lm_ls_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_lm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrm_lm_ls_nis"));

    if(h_nrsecvtx_hm_us_nis       != 0) file -> Append(h_nrsecvtx_hm_us_nis       -> Clone("h_nrsecvtx_hm_us_nis"));
    if(h_chi2_hm_us_nis           != 0) file -> Append(h_chi2_hm_us_nis           -> Clone("h_chi2_hm_us_nis"));
    if(h_ndof_hm_us_nis           != 0) file -> Append(h_ndof_hm_us_nis           -> Clone("h_ndof_hm_us_nis"));
    if(h_chi2ndof_hm_us_nis       != 0) file -> Append(h_chi2ndof_hm_us_nis       -> Clone("h_chi2ndof_hm_us_nis"));
    if(h_multiplicity_hm_us_nis   != 0) file -> Append(h_multiplicity_hm_us_nis   -> Clone("h_multiplicity_hm_us_nis"));
    if(h_vtxmass_hm_us_nis        != 0) file -> Append(h_vtxmass_hm_us_nis        -> Clone("h_vtxmass_hm_us_nis"));
    if(h_dl2_hm_us_nis            != 0) file -> Append(h_dl2_hm_us_nis            -> Clone("h_dl2_hm_us_nis"));
    if(h_dl2_err_hm_us_nis        != 0) file -> Append(h_dl2_err_hm_us_nis        -> Clone("h_dl2_err_hm_us_nis"));
    if(h_dl2_sign_hm_us_nis       != 0) file -> Append(h_dl2_sign_hm_us_nis       -> Clone("h_dl2_sign_hm_us_nis"));
    if(h_dl2_sign_mirrp_hm_us_nis != 0) file -> Append(h_dl2_sign_mirrp_hm_us_nis -> Clone("h_dl2_sign_mirrp_hm_us_nis"));
    if(h_dl2_sign_mirrm_hm_us_nis != 0) file -> Append(h_dl2_sign_mirrm_hm_us_nis -> Clone("h_dl2_sign_mirrm_hm_us_nis"));
    if(h_mvtx2_chi2_hm_us_nis           != 0) file -> Append(h_mvtx2_chi2_hm_us_nis           -> Clone("h_mvtx2_chi2_hm_us_nis"));
    if(h_mvtx2_ndof_hm_us_nis           != 0) file -> Append(h_mvtx2_ndof_hm_us_nis           -> Clone("h_mvtx2_ndof_hm_us_nis"));
    if(h_mvtx2_chi2ndof_hm_us_nis       != 0) file -> Append(h_mvtx2_chi2ndof_hm_us_nis       -> Clone("h_mvtx2_chi2ndof_hm_us_nis"));
    if(h_mvtx2_multiplicity_hm_us_nis   != 0) file -> Append(h_mvtx2_multiplicity_hm_us_nis   -> Clone("h_mvtx2_multiplicity_hm_us_nis"));
    if(h_mvtx2_vtxmass_hm_us_nis        != 0) file -> Append(h_mvtx2_vtxmass_hm_us_nis        -> Clone("h_mvtx2_vtxmass_hm_us_nis"));
    if(h_mvtx2_dl2_hm_us_nis            != 0) file -> Append(h_mvtx2_dl2_hm_us_nis            -> Clone("h_mvtx2_dl2_hm_us_nis"));
    if(h_mvtx2_dl2_err_hm_us_nis        != 0) file -> Append(h_mvtx2_dl2_err_hm_us_nis        -> Clone("h_mvtx2_dl2_err_hm_us_nis"));
    if(h_mvtx2_dl2_sign_hm_us_nis       != 0) file -> Append(h_mvtx2_dl2_sign_hm_us_nis       -> Clone("h_mvtx2_dl2_sign_hm_us_nis"));
    if(h_mvtx2_dl2_sign_mirrp_hm_us_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_hm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrp_hm_us_nis"));
    if(h_mvtx2_dl2_sign_mirrm_hm_us_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_hm_us_nis -> Clone("h_mvtx2_dl2_sign_mirrm_hm_us_nis"));

    if(h_nrsecvtx_hm_ls_nis       != 0) file -> Append(h_nrsecvtx_hm_ls_nis       -> Clone("h_nrsecvtx_hm_ls_nis"));
    if(h_chi2_hm_ls_nis           != 0) file -> Append(h_chi2_hm_ls_nis           -> Clone("h_chi2_hm_ls_nis"));
    if(h_ndof_hm_ls_nis           != 0) file -> Append(h_ndof_hm_ls_nis           -> Clone("h_ndof_hm_ls_nis"));
    if(h_chi2ndof_hm_ls_nis       != 0) file -> Append(h_chi2ndof_hm_ls_nis       -> Clone("h_chi2ndof_hm_ls_nis"));
    if(h_multiplicity_hm_ls_nis   != 0) file -> Append(h_multiplicity_hm_ls_nis   -> Clone("h_multiplicity_hm_ls_nis"));
    if(h_vtxmass_hm_ls_nis        != 0) file -> Append(h_vtxmass_hm_ls_nis        -> Clone("h_vtxmass_hm_ls_nis"));
    if(h_dl2_hm_ls_nis            != 0) file -> Append(h_dl2_hm_ls_nis            -> Clone("h_dl2_hm_ls_nis"));
    if(h_dl2_err_hm_ls_nis        != 0) file -> Append(h_dl2_err_hm_ls_nis        -> Clone("h_dl2_err_hm_ls_nis"));
    if(h_dl2_sign_hm_ls_nis       != 0) file -> Append(h_dl2_sign_hm_ls_nis       -> Clone("h_dl2_sign_hm_ls_nis"));
    if(h_dl2_sign_mirrp_hm_ls_nis != 0) file -> Append(h_dl2_sign_mirrp_hm_ls_nis -> Clone("h_dl2_sign_mirrp_hm_ls_nis"));
    if(h_dl2_sign_mirrm_hm_ls_nis != 0) file -> Append(h_dl2_sign_mirrm_hm_ls_nis -> Clone("h_dl2_sign_mirrm_hm_ls_nis"));
    if(h_mvtx2_chi2_hm_ls_nis           != 0) file -> Append(h_mvtx2_chi2_hm_ls_nis           -> Clone("h_mvtx2_chi2_hm_ls_nis"));
    if(h_mvtx2_ndof_hm_ls_nis           != 0) file -> Append(h_mvtx2_ndof_hm_ls_nis           -> Clone("h_mvtx2_ndof_hm_ls_nis"));
    if(h_mvtx2_chi2ndof_hm_ls_nis       != 0) file -> Append(h_mvtx2_chi2ndof_hm_ls_nis       -> Clone("h_mvtx2_chi2ndof_hm_ls_nis"));
    if(h_mvtx2_multiplicity_hm_ls_nis   != 0) file -> Append(h_mvtx2_multiplicity_hm_ls_nis   -> Clone("h_mvtx2_multiplicity_hm_ls_nis"));
    if(h_mvtx2_vtxmass_hm_ls_nis        != 0) file -> Append(h_mvtx2_vtxmass_hm_ls_nis        -> Clone("h_mvtx2_vtxmass_hm_ls_nis"));
    if(h_mvtx2_dl2_hm_ls_nis            != 0) file -> Append(h_mvtx2_dl2_hm_ls_nis            -> Clone("h_mvtx2_dl2_hm_ls_nis"));
    if(h_mvtx2_dl2_err_hm_ls_nis        != 0) file -> Append(h_mvtx2_dl2_err_hm_ls_nis        -> Clone("h_mvtx2_dl2_err_hm_ls_nis"));
    if(h_mvtx2_dl2_sign_hm_ls_nis       != 0) file -> Append(h_mvtx2_dl2_sign_hm_ls_nis       -> Clone("h_mvtx2_dl2_sign_hm_ls_nis"));
    if(h_mvtx2_dl2_sign_mirrp_hm_ls_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrp_hm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrp_hm_ls_nis"));
    if(h_mvtx2_dl2_sign_mirrm_hm_ls_nis != 0) file -> Append(h_mvtx2_dl2_sign_mirrm_hm_ls_nis -> Clone("h_mvtx2_dl2_sign_mirrm_hm_ls_nis"));

  }
  
  file->Write();
  file->Close();
  gROOT->ProcessLine(".q");

}
