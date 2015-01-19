#!/bin/sh

echo " cp src/ and inc/ to include/GutLib/  from setup wit subsets"
rm -r $GUTCODEDIR/libraries/GutLib/src
rm -r $GUTCODEDIR/libraries/GutLib/inc
cp -r $GUTCODEDIR/libraries/GutLib/diff_sub_modes/with_subs/src $GUTCODEDIR/libraries/GutLib/src
cp -r $GUTCODEDIR/libraries/GutLib/diff_sub_modes/with_subs/inc $GUTCODEDIR/libraries/GutLib/inc

echo " recompile...."
cd $GUTCODEDIR/scripts-analysis/
./recompile