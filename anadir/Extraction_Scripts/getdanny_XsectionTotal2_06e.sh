if [ -z $1 ]; then
    echo ""
    echo "Please give run version"
    echo ""
    echo "Usage: getdanny [version], e.g. ./getdanny_XsectionTotal2_06e.sh 041011_1_withtrigger_isocorr2"
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
target=$ver'_XsectionTotal2_06e_dbothistos/'
echo 'Chosen target directory is: '$target
cd $GUTANADIR/
cd data/
pwd
./oli2danny_XsectionTotal2_06e_data $ver da
cd ../mc
./oli2danny_XsectionTotal2_06e_mc $ver da
cd $GUTANADIR
mkdir $target
mv 06e.root $target
mv b_06e_*.root $target
mv c_06e_*.root $target
mv jpsi_06e_* $target
mv psiprime_06e_* $target
mv bh_06e_* $target
mv upsilon_06e_* $target
mv instanton_06e_* $target
mv bbbb_06e_* $target
mv cccc_06e_* $target
mv bbcc_06e_* $target
cd $target
exit
