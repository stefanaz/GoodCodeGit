if [ -z $1 ]; then
    echo ""
    echo "Please give run version"
    echo ""
    echo "Usage: getdanny [version], e.g. ./getdanny_muonjet_05e.sh 041011_1_withtrigger_isocorr2"
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
target=$ver'_muonjet_05e_dbothistos/'
echo 'Chosen target directory is: '$target
cd $GUTANADIR/
cd data/
pwd
./oli2danny_muonjet_05e_data $ver da
cd ../mc
./oli2danny_muonjet_05e_mc $ver da
cd $GUTANADIR
mkdir $target
mv 05e.root $target
mv b_05e*.root $target
mv c_05e*.root $target
mv jpsi_05e* $target
mv psiprime_05e* $target
mv bh_05e* $target
mv upsilon_05e* $target
mv instanton_05e* $target
mv bbbb_05e* $target
mv cccc_05e* $target
mv bbcc_05e* $target
cd $target
exit
