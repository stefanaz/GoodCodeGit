#!/bin/sh

module load root/5.34


export CVSROOT=/afs/desy.de/user/g/gmuon/repository

# export GUTCODEDIR=/data/zenith234d/stefan/GutCode
# export GUTCODEDIR=/data/zenith234d/stefan/GoodCodeGit
export GUTCODEDIR=/nfs/dust/zeus/group/stefan/test2/GoodCodeGit

export GUTDATADIR=$GUTCODEDIR/datadir

export GUTANADIR=$GUTCODEDIR/anadir

export CONVERTLOCATION=`which convert`

export ZARCH_TYPE=i586-sl6-linux

export PATH=$PATH:$GUTCODEDIR/analysis/exe/$ZARCH_TYPE:$GUTCODEDIR/job-scripts:$GUTCODEDIR/programs/cardmaker/exe/$ZARCH_TYPE:$GUTCODEDIR/programs/logchecker/exe/$ZARCH_TYPE:$GUTCODEDIR/programs/merger/exe/$ZARCH_TYPE:$GUTCODEDIR/programs/picturemaker/exe/$ZARCH_TYPE

export PATH=$PATH:$GUTCODEDIR/scripts-analysis

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GUTCODEDIR/libraries/GutLib/lib/$ZARCH_TYPE

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GUTCODEDIR/libraries/GutLibX/lib/$ZARCH_TYPE
