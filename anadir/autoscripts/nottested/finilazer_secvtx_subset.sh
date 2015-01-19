#!bin/sh
cd Extraction_Scripts
sh run_all_secvtx.sh
# # cd ../mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx
cd ../mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_subsets_secvtx
rm *.root
cd ..
# # sh move_all_secvtx.sh
sh move_all_secvtx_subset.sh
# cd mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx
cd mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_subsets_secvtx
sh mergefiles.sh
# sh Histogramm_Plotscript.sh
# root -l Plot_Script_Danny_Dimuon_Secvtx_2.C
