#export ROOTSYS=/afs/desy.de/group/zeus/ZEUSSysSoft/Released/Support/root/i586-sl3-linux/5.26.00
export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH:/products/dcache/lib
export PATH=/zeus/bin:$ROOTSYS/bin:$PATH
export PATH=/afs/desy.de/group/zeus/jobs/released/jobs/cmd:$PATH

#  Define the path to the ZEUS Base directory
#  ------------------------------------------
export ZEUS_BASE_ROOT=/afs/desy.de/group/zeus.zsmsm

#  Setup the ZEUS environment
#  --------------------------
source $ZEUS_BASE_ROOT/ZEUSSysSoft/Setup/setup_ZEUS.sh

CDPATH=.:$HOME:
PRINTER=zeusps0
LPDEST=$PRINTER
export LPDEST PRINTER
export PATH=/afs/desy.de/group/zeus/jobs/released/jobs/cmd:$PATH

alias real='cd /data/zenith234d/stefan/2/MZ/'
alias real6='cd /data/zenith234d/stefan/6/'
alias hhs='ssh -XY stefan@zenith234'
alias ls='ls --color --color'
alias root='root -l'
alias gcc='g++ -o main.exe `root-config --cflags --libs`'
alias gcci='g++ -o main.exe -I `root-config --incdir` `root-config --libs` -I.'
alias mcc='zarah-jobsub -q M -s eaze_run.sh ../cards/control.cards ../exe/$ZARCH_TYPE/eaze_example.exe'
alias work='cd /data/zenith234d/stefan/GutCode/'
alias work2='cd /data/zenith234d/stefan/GoodCodeGit/'
alias datadir='cd /nfs/dust/zeus/group/stefan/'
