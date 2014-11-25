if [ -z $1 ]; then
    echo ""
    echo "Please give run version"
    echo ""
    echo "Usage: getdanny [version], e.g. ./getdanny_secvtx_0304p.sh 041011_1_withtrigger_isocorr2"
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
target=$ver'_secvtx_0304p_dbothistos/'
echo 'Chosen target directory is: '$target
cd $GUTANADIR/
cd data/
pwd
./oli2danny_secvtx_0304p_data $ver da
cd ../mc
./oli2danny_secvtx_0304p_mc $ver da
cd $GUTANADIR
mkdir $target
mv 03p.root 04p.root $target
mv b_03p-04p*.root $target
mv c_03p-04p*.root $target
mv jpsi_03p-04p* $target
mv psiprime_03p-04p* $target
mv bh_03p-04p* $target
mv upsilon_03p-04p* $target
mv instanton_03p-04p* $target
mv bbbb_03p-04p* $target
mv cccc_03p-04p* $target
mv bbcc_03p-04p* $target
cd $target
exit
