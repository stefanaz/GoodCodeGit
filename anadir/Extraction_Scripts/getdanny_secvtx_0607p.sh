if [ -z $1 ]; then
    echo ""
    echo "Please give run version"
    echo ""
    echo "Usage: getdanny [version], e.g. ./getdanny_secvtx_0607p.sh 041011_1_withtrigger_isocorr2"
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
target=$ver'_secvtx_0607p_dbothistos/'
echo 'Chosen target directory is: '$target
cd $GUTANADIR/
cd data/
pwd
./oli2danny_secvtx_0607p_data $ver da
cd ../mc
./oli2danny_secvtx_0607p_mc $ver da
cd $GUTANADIR
mkdir $target
mv 06p.root 07p.root $target
mv b_06p-07p*.root $target
mv c_06p-07p*.root $target
mv jpsi_06p-07p* $target
mv psiprime_06p-07p* $target
mv bh_06p-07p* $target
mv upsilon_06p-07p* $target
mv instanton_06p-07p* $target
mv bbbb_06p-07p* $target
mv cccc_06p-07p* $target
mv bbcc_06p-07p* $target
cd $target
exit
