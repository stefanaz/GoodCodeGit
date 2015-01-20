#!/bin/zsh
# Modificated by Nazar Stefaniuk to run GUTCODE analysis;
# This is a simple example of a SGE batch script
# request Bourne shell as shell for job
#$ -S /bin/zsh
#
# print date and time
echo "$QUEUE $JOB $HOST"
# Sleep for 20 seconds
# sleep 20
# print date and time again
date
echo $TMP
# workaround for occasional NAF problem with SL6
source /etc/profile.d/modules.sh
# ROOT for SL6
module load root/5.34
# My exports ################################################
source /afs/desy.de/user/s/stefan/NAFstaff/GUTCODE_setup.sh
#############################################################
echo $SHELL
$1
#/nfs/dust/zeus/group/stefan/test2/GoodCodeGit/anadir/autoscripts/run_05data_test.sh
#############################################################
