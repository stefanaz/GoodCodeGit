{
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Nevents_Histosum/Draw_Errorbar.C"

#include <string>
#include <stdio.h>
using namespace std;


// char * name_histo = "h_dimulog10q2si";
char * name_histo = "h_mmu_accept";

if (1==1) {
string mystring = string(name_histo); mystring.append("_lm_us_nis_data");
TH1D* h_nrsecvtx_lm_us_nis_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_nis_allMC_sum");
TH1D* h_nrsecvtx_lm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_nis_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_nis_data");
TH1D* h_nrsecvtx_lm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_nis_allMC_sum");
TH1D* h_nrsecvtx_lm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_nis_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);



mystring = string(name_histo); mystring.append("_hm_us_nis_data");
TH1D* h_nrsecvtx_hm_us_nis_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_nis_allMC_sum");
TH1D* h_nrsecvtx_hm_us_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_us_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_nis_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_nis_MC_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_nis_data");
TH1D* h_nrsecvtx_hm_ls_nis_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_nis_allMC_sum");
TH1D* h_nrsecvtx_hm_ls_nis_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_nis_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_ls_nis_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_nis_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_nis_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_nis_MC_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_nis_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);



//***********************************************************************
//****  isolated high and low mass plots  *******************************
//***********************************************************************
mystring = string(name_histo); mystring.append("_lm_us_is_data");
TH1D* h_nrsecvtx_lm_us_is_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_is_allMC_sum");
TH1D* h_nrsecvtx_lm_us_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_us_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_is_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);;

mystring = string(name_histo); mystring.append("_lm_us_is_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_is_data");
TH1D* h_nrsecvtx_lm_ls_is_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_is_allMC_sum");
TH1D* h_nrsecvtx_lm_ls_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_ls_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);;

mystring = string(name_histo); mystring.append("_lm_ls_is_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);



mystring = string(name_histo); mystring.append("_hm_us_is_data");
TH1D* h_nrsecvtx_hm_us_is_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_is_allMC_sum");
TH1D* h_nrsecvtx_hm_us_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_us_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_is_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_is_MC_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_is_data");
TH1D* h_nrsecvtx_hm_ls_is_data              = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_is_allMC_sum");
TH1D* h_nrsecvtx_hm_ls_is_allMC_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_is_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_ls_is_allMC_m_charm_sum = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_is_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_is_MC_c_p_lflbg_sum  = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_is_MC_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_is_MC_lflbg_sum      = (TH1D*) gInclude->ReadinHisto(mystring);

//***********************************************************************
//****  isolated and non-isolated high and low mass plots  **************
//***********************************************************************
mystring = string(name_histo); mystring.append("_hm_us_data");
TH1D* h_nrsecvtx_hm_us_data                 = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_allMC_sum");
TH1D* h_nrsecvtx_hm_us_allMC_sum            = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_us_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_us_MC_lflbg_sum");
TH1D* h_nrsecvtx_hm_us_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_data");
TH1D* h_nrsecvtx_hm_ls_data                 = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_allMC_sum");
TH1D* h_nrsecvtx_hm_ls_allMC_sum            = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_allMC_m_charm_sum");
TH1D* h_nrsecvtx_hm_ls_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_hm_ls_MC_lflbg_sum");
TH1D* h_nrsecvtx_hm_ls_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto(mystring);


mystring = string(name_histo); mystring.append("_lm_us_data");
TH1D* h_nrsecvtx_lm_us_data                 = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_allMC_sum");
TH1D* h_nrsecvtx_lm_us_allMC_sum            = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_us_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_us_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_us_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_data");
TH1D* h_nrsecvtx_lm_ls_data                 = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_allMC_sum");
TH1D* h_nrsecvtx_lm_ls_allMC_sum            = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_allMC_m_charm_sum");
TH1D* h_nrsecvtx_lm_ls_allMC_m_charm_sum    = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_MC_c_p_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_MC_c_p_lflbg_sum     = (TH1D*) gInclude->ReadinHisto(mystring);

mystring = string(name_histo); mystring.append("_lm_ls_MC_lflbg_sum");
TH1D* h_nrsecvtx_lm_ls_MC_lflbg_sum         = (TH1D*) gInclude->ReadinHisto(mystring);
}

/// Mass inv;
if (40==40){

/// Nisandis part: 
// cout<<" Nisandis LM part: "<<endl;
cout<<"data = "<<Get_sumof_hist("h_mmu_accept_lm_us_data", h_mmu_accept_lm_us_data,1 )<<endl;
cout<<"lfl = "<<Get_sumof_hist("h_mmu_accept_lm_ls_MC_lflbg_sum", h_mmu_accept_lm_ls_MC_lflbg_sum, 1)<<endl;
cout<<"cc = "<<Get_sumof_hist("h_mmu_accept_lm_us_MC_c_p_lflbg_sum", h_mmu_accept_lm_us_MC_c_p_lflbg_sum, 1)<<endl;
cout<<"J/Psi.. = "<<Get_sumof_hist("h_mmu_accept_lm_us_allMC_m_charm_sum", h_mmu_accept_lm_us_allMC_m_charm_sum, 1)<<endl;
cout<<"bb = "<<Get_sumof_hist("h_mmu_accept_lm_us_allMC_sum", h_mmu_accept_lm_us_allMC_sum, 1)<<endl<<endl;


/// Isolated part: 
cout<<" Isolated LM part: "<<endl;
cout<<"data = "<<Get_sumof_hist("h_mmu_accept_lm_us_is_data", h_mmu_accept_lm_us_is_data, 1)<<endl;
cout<<"lfl = "<<Get_sumof_hist("h_mmu_accept_lm_ls_is_MC_lflbg_sum", h_mmu_accept_lm_ls_is_MC_lflbg_sum, 1)<<endl;
cout<<"cc = "<<Get_sumof_hist("h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum", h_mmu_accept_lm_us_is_MC_c_p_lflbg_sum, 1)<<endl;
cout<<"J/Psi.. = "<<Get_sumof_hist("h_mmu_accept_lm_us_is_allMC_m_charm_sum", h_mmu_accept_lm_us_is_allMC_m_charm_sum, 1)<<endl;
cout<<"bb = "<<Get_sumof_hist("h_mmu_accept_lm_us_is_allMC_sum", h_mmu_accept_lm_us_is_allMC_sum, 1)<<endl<<endl;


/// Nis LM part: 
cout<<" Nis LM part: "<<endl;
cout<<"data = "<<Get_sumof_hist("h_mmu_accept_lm_us_nis_data", h_mmu_accept_lm_us_nis_data, 1)<<endl;
cout<<"lfl = "<<Get_sumof_hist("h_mmu_accept_lm_ls_nis_MC_lflbg_sum", h_mmu_accept_lm_ls_nis_MC_lflbg_sum, 1)<<endl;
cout<<"cc = "<<Get_sumof_hist("h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum", h_mmu_accept_lm_us_nis_MC_c_p_lflbg_sum, 1)<<endl;
cout<<"J/Psi.. = "<<Get_sumof_hist("h_mmu_accept_lm_us_nis_allMC_m_charm_sum", h_mmu_accept_lm_us_nis_allMC_m_charm_sum, 1)<<endl;
cout<<"bb = "<<Get_sumof_hist("h_mmu_accept_lm_us_nis_allMC_sum", h_mmu_accept_lm_us_nis_allMC_sum, 1)<<endl<<endl;
}


/// Log10_Q2
if (40==41) {
/// Nisandis part: 
cout<<" Nisandis LM part: "<<endl;
cout<<"data = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_data", h_dimulog10q2si_lm_us_data,1 )<<endl;
cout<<"lfl = "<<Get_sumof_hist("h_dimulog10q2si_lm_ls_MC_lflbg_sum", h_dimulog10q2si_lm_ls_MC_lflbg_sum, 1)<<endl;
cout<<"cc = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_MC_c_p_lflbg_sum", h_dimulog10q2si_lm_us_MC_c_p_lflbg_sum, 1)<<endl;
cout<<"J/Psi.. = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_allMC_m_charm_sum", h_dimulog10q2si_lm_us_allMC_m_charm_sum, 1)<<endl;
cout<<"bb = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_allMC_sum", h_dimulog10q2si_lm_us_allMC_sum, 1)<<endl<<endl;


/// Isolated part: 
cout<<" Isolated LM part: "<<endl;
cout<<"data = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_is_data", h_dimulog10q2si_lm_us_is_data, 1)<<endl;
cout<<"lfl = "<<Get_sumof_hist("h_dimulog10q2si_lm_ls_is_MC_lflbg_sum", h_dimulog10q2si_lm_ls_is_MC_lflbg_sum, 1)<<endl;
cout<<"cc = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_is_MC_c_p_lflbg_sum", h_dimulog10q2si_lm_us_is_MC_c_p_lflbg_sum, 1)<<endl;
cout<<"J/Psi.. = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_is_allMC_m_charm_sum", h_dimulog10q2si_lm_us_is_allMC_m_charm_sum, 1)<<endl;
cout<<"bb = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_is_allMC_sum", h_dimulog10q2si_lm_us_is_allMC_sum, 1)<<endl<<endl;


/// Nis LM part: 
cout<<" Nis LM part: "<<endl;
cout<<"data = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_nis_data", h_dimulog10q2si_lm_us_nis_data, 1)<<endl;
cout<<"lfl = "<<Get_sumof_hist("h_dimulog10q2si_lm_ls_nis_MC_lflbg_sum", h_dimulog10q2si_lm_ls_nis_MC_lflbg_sum, 1)<<endl;
cout<<"cc = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_nis_MC_c_p_lflbg_sum", h_dimulog10q2si_lm_us_nis_MC_c_p_lflbg_sum, 1)<<endl;
cout<<"J/Psi.. = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_nis_allMC_m_charm_sum", h_dimulog10q2si_lm_us_nis_allMC_m_charm_sum, 1)<<endl;
cout<<"bb = "<<Get_sumof_hist("h_dimulog10q2si_lm_us_nis_allMC_sum", h_dimulog10q2si_lm_us_nis_allMC_sum, 1)<<endl<<endl;
}

}

