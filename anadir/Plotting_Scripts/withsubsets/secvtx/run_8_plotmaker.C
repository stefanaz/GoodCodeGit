{

#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/plot_8_plots.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Nevents_Histosum/Draw_Errorbar.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/plot_8_plots_sum.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/bscale_calculation.C"
// #include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Q2_reweight/my_func.C"
#include "/data/zenith234d/stefan/GutCode/anadir/mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx/plot_DL_distributions.C"
#include "/data/zenith234d/stefan/GutCode/anadir/mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx/plot_DL_distributions_ls.C"
#include "/data/zenith234d/stefan/GutCode/anadir/mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx/plot_DL_distributions_us.C"

#include <string>
#include <stdio.h>
using namespace std;

/// (from SECVTX part! ):
// DL distributions
plot_DL_distributions("h_dl2_171","h_dl2_sign_171",40, 30, true);
// plot_DL_distributions_ls("h_dl2","h_dl2_sign", 30, 30);
// plot_DL_distributions_us("h_dl2","h_dl2_sign", 30, 30);
// plot_8_plots_sum("h_dl2_sign", -15,15,1,1, "S = L_{XY}/#sigma_{L_{XY}}", true);

///
// ( name of vars, rangemin, rangemax, Rebinning, LogY, LogX, NameXaxes, inst_bool)

// plot_8_plots("h_nrsecvtx", 0.0,10.,1,0,0, "Nr. Sec Vtx", true);
// plot_8_plots_sum("h_nrsecvtx_3", 0.0,10.,1,0, "Nr. Sec Vtx", false);
// // 
// plot_8_plots("h_vtxmass", 0.0,10.,5,0,0, "m_{Sec. vtx} [GeV]", false);
// plot_8_plots_sum("h_vtxmass", 0.0,10.,5,1, "m_{Sec. vtx} [GeV]", false);
// //
// plot_8_plots("h_chi2ndof", 0.0,10.,1,0,0, "#Chi^{2}/ndof",false);
// plot_8_plots_sum("h_chi2ndof", 0.0,10.,1,0,"#Chi^{2}/ndof", false);
// // // 
// plot_8_plots("h_multiplicity", 0.0,12.,1,0,0, "Track multiplicity",false);
// plot_8_plots_sum("h_multiplicity", 0.0,12.,1,0, "Track multiplicity", false);
/// DL
// plot_8_plots("h_dl2_sign", -25,25,1,1,0, "S = L_{XY}/#sigma_{L_{XY}}", true);
// plot_8_plots("h_dl2", -2,2,5,1,0, "L_{XY}", false);

/// DL_mvtx
// plot_8_plots("h_dl2_mvtx1_sign", -15,15,1,1,0, "S = L_{XY}/#sigma_{L_{XY}}", false);
// plot_8_plots("h_dl2_mvtx1", -1,1,5,1,0, "L_{XY}", false);
// plot_DL_distributions("h_dl2_mvtx8","h_dl2_sign_mvtx8", 30, 30);
// plot_DL_distributions_ls("h_dl2_mvtx2","h_dl2_sign_mvtx2", 30, 30);
// plot_DL_distributions_us("h_dl2_mvtx4","h_dl2_sign_mvtx4", 30, 30);


/// for Presentation (from DIMUON part! ): 
// plot_8_plots("h_ptmu", 0.,10.0,1,0,0, "P_{T}^{#mu}", false);
// plot_8_plots_sum("h_ptmu", 0.0,10.,1,0, "P_{T}^{#mu}", false);

// plot_8_plots("h_mmu_accept", 1.5,4.0,1,0,1, "M^{inv}_{#mu #mu}");

// plot_8_plots("h_dimuptmu", 0.,10.0,1,0, "P_{T}^{#mu #mu}");
// plot_8_plots_sum("h_dimuptmu", 0.0,10.,1,0, "P_{T}^{#mu #mu}");

// plot_8_plots("h_DR_accept", 0.,3.0,1,1, "P_{T}^{#mu #mu}");
// plot_8_plots_sum("h_DR_accept", 0.0,3.,1,1, "P_{T}^{#mu #mu}");


//Q2:
// plot_8_plots("h_dimulog10q2si", -2.,5.,1,0, "Q2_log");
// plot_8_plots_sum("h_dimulog10q2si", -2.,5.,1,1, "Q2_log");
//Q2:
// plot_8_plots("h_dimuq2si", -100.,2000.,1,1, "Q2");
// plot_8_plots_sum("h_dimuq2si", 0.,1000.,1,1, "Q2");


/// Checking: 
// plot_8_plots("h_dimuq2si", 0.01,10000.,80,1,1, "Q2");
// plot_8_plots("h_dimuq2si_cutjpsi", 0.,2000.,1,1,0, "Q2");
// plot_8_plots("h_dimulog10q2si_cutjpsi", -2.,5.,1,1,1, "Q2_log");
// plot_8_plots_sum("h_dimulog10q2si_cutjpsi", -2.,5.,1,1, "Q2_log");
// plot_8_plots("h_dimulog10q2si", -2.,5.,5,1,1, "Q2_log");

// gROOT->ProcessLine(".x run_8_plotmaker.C");

/// B scale study: 
// bscale_calculation("h_mmu_accept", "h_mmu_accept");
// bscale_calculation("h_dimuphi", "h_dimuphi");
// bscale_calculation("h_nrsecvtx", "h_nrsecvtx", false);
// bscale_calculation("h_vtxmass", "h_vtxmass");

// gROOT->ProcessLine(".q");

}