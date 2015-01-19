#!/bin/sh

echo " cp src/ and inc/ to include/GutLib/  from setup without subsets"
rm -r $GUTCODEDIR/libraries/GutLib/src
rm -r $GUTCODEDIR/libraries/GutLib/inc
cp -r $GUTCODEDIR/libraries/GutLib/diff_sub_modes/first/src $GUTCODEDIR/libraries/GutLib/src
cp -r $GUTCODEDIR/libraries/GutLib/diff_sub_modes/first/inc $GUTCODEDIR/libraries/GutLib/inc

echo " recompile...."
cd $GUTCODEDIR/scripts-analysis/
./recompile