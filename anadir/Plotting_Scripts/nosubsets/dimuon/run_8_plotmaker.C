{

#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/plot_8_plots.C"
// #include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/test.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Nevents_Histosum/Draw_Errorbar.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/plot_8_plots_sum.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/plot_8_plots_sum_with_thesis.C"
#include "/data/zenith234d/stefan/PhD_work/Useful_Codes/8_Histo/bscale_calculation.C"
// #include "/data/zenith234d/stefan/PhD_work/Useful_Codes/Q2_reweight/my_func.C"

#include <string>
#include <stdio.h>

//Q2:
// plot_8_plots("h_dimulog10q2si", -2.,5.,1,0, "Q2_log");
// plot_8_plots_sum("h_dimulog10q2si", -2.,5.,1,1, "Q2_log");

//Q2:
// plot_8_plots("h_dimuq2si", -100.,2000.,1,1, "Q2");
// plot_8_plots_sum("h_dimuq2si", 0.,1000.,1,1, "Q2");

///invmass, phi_dimu,  pt_mu;
plot_8_plots("h_mmu_accept", 4.,12.0,1,0,0, "M^{inv}_{#mu #mu}", false);
// plot_8_plots_sum("h_mmu_accept", 1.5,4.,1,0, "M^{inv}_{#mu #mu}");

// // plot_8_plots("h_dimuphi", -5.,5.0,1,0,0, "#Phi^{#mu #mu}",false);
// // plot_8_plots_sum("h_dimuphi", -5.,5.,0,0, "#Phi^{#mu #mu}");


/// for Presentation: 
plot_8_plots("h_ptmu", 0.,10.0,1,0,0, "P_{T}^{#mu}", false);
plot_8_plots_sum("h_ptmu", 0.0,8.,1,0, "P_{T}^{#mu}");

plot_8_plots("h_mueta_accept", -4.,4.5,1,0,0, "#eta^{#mu}", false);
plot_8_plots_sum("h_mueta_accept", -4.0,4.5,1,0, "#eta^{#mu}");

plot_8_plots("h_dimuptmu", 0.,10.0,1,0,0, "P_{T}^{#mu #mu}", false);
plot_8_plots_sum("h_dimuptmu", 0.0,10.,1,0, "P_{T}^{#mu #mu}");

plot_8_plots("h_DR_accept", 0.,4.5,1,0,0, "#Delta R^{#mu #mu}", false);
plot_8_plots_sum("h_DR_accept", 0.0,5.,1,0, "#Delta R^{#mu #mu}");


/// Checking: 
// plot_8_plots("h_dimuq2si", 0.01,10000.,80,1,1, "Q2");
// plot_8_plots("h_dimuq2si_cutjpsi", 0.,2000.,1,1, "Q2");
// plot_8_plots("h_dimulog10q2si_cutjpsi", -2.,5.,5,1,1, "Q2_log");
// plot_8_plots_sum("h_dimulog10q2si_cutjpsi", -2.,5.,1,1, "Q2_log");
// plot_8_plots("h_dimulog10q2si", -2.,5.,5,1,1, "Q2_log");

// gROOT->ProcessLine(".x run_8_plotmaker.C");

/// B scale study: 
bscale_calculation("h_mmu_accept", "M^{inv}_{#mu #mu}", true);
// bscale_calculation("h_dimuphi", "M^{inv}_{#mu #mu}", false);

/// Event shape vars: 
// plot_8_plots("h_thrust", 0.5,1.0,1,1,0, "T_{Psevdo}", true);
// plot_8_plots("h_sphericity", 0.,1.0,2,0,0, "Sph", true);
// plot_8_plots("h_isotropy", 0.,1.0,2,0,0, "#Delta_{B}", true);
// plot_8_plots("h_Q2Prime", 0.,1000.,2,0,0, "Q'^{2}", true);
// plot_8_plots("h_multiplicity", 0.,80.0,1,0,0, "N_{band}", true);

// plot_8_plots_sum_with_thesis("h_sphericity", 0.,1.0,2,0, "Sph", false);
// plot_8_plots_sum_with_thesis("h_isotropy", 0.,1.0,2,0, "#Delta_{B}", false);
// plot_8_plots_sum_with_thesis("h_Q2Prime", 0.,1000.,2,0, "Q'^{2}", false);
// plot_8_plots_sum_with_thesis("h_multiplicity", 0.,80.0,1,0, "N_{band}", false);

// plot_8_plots_sum_with_thesis("h_sphericity", 0.,1.0,2,0, "Sph", true);
// plot_8_plots_sum_with_thesis("h_isotropy", 0.,1.0,2,0, "#Delta_{B}", true);
// plot_8_plots_sum_with_thesis("h_Q2Prime", 0.,1000.,2,0, "Q'^{2}", true);
// plot_8_plots_sum_with_thesis("h_multiplicity", 0.,80.0,1,0, "N_{band}", true);

// test("h_mmu_accept");
gROOT->ProcessLine(".q");

}