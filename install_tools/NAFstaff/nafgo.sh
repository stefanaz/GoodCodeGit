#!/bin/sh
qsub -l os=sld6 -q short.q -cwd /afs/desy.de/user/s/stefan/NAFstaff/nafsetups.sh $1
