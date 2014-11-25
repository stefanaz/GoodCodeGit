if [ -z $1 ]; then
    echo ""
    echo "Please give run version"
    echo ""
    echo "Usage: getdanny [version], e.g. ./getdanny_dimuon_05e.sh 041011_1_withtrigger_isocorr2"
    echo ""
    exit
fi
#
#if [ -z $2 ]; then
#    echo ""
#    echo "Please give merged histogram-file"
#    echo ""
#    echo "Usage: merge [version] [outputname]"
#    echo ""
#    exit
#fi

ver=$1
echo 'Version to process is: '$ver
target=$ver'_dimuon_05e_dbothistos/'
echo 'Chosen target directory is: '$target
cd $GUTANADIR/
cd data/
pwd
./oli2danny_dimuon_05e_data $ver da
cd ../mc
./oli2danny_dimuon_05e_mc $ver da
cd $GUTANADIR
mkdir $target
mv 05e.root $target
mv b_05e_*.root $target
mv c_05e_*.root $target
mv jpsi_05e_* $target
mv psiprime_05e_* $target
mv bh_05e_* $target
mv upsilon_05e_* $target
mv instanton_05e_* $target
mv bbbb_05e_* $target
mv cccc_05e_* $target
mv bbcc_05e_* $target
cd $target
exit
