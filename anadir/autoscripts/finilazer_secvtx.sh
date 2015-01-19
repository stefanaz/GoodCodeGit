#!bin/sh

# sh ../analysis_macros/set_src_first.sh
mkdir ../mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx

cd ../Extraction_Scripts
sh run_all_secvtx.sh
cd ../mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx
rm *.root
cd ../autoscripts
sh move_all_secvtx.sh
cd ../mini_HeraII_0307p_Data_MC_Dimuon_Finalversion_dbothistos_secvtx
sh mergefiles.sh
sh Histogramm_Plotscript.sh

# root -l run_8_plotmaker.C

