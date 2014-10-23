#! /bin/zsh -f
if [ $# -gt 1 ]
then
echo 'usage: getvalidruns <date> '
echo '       date: 040227 '
exit
fi

if [ $# -eq 1 ]
then
date_formated=`%1`
year='04'
fi
if [ $# -lt 1 ]
then
date_formated=`date +%y%m%d`
year=`date +%y`
fi

wget http://www-zeus.desy.de/physics/lumi/lumi$year/validruns.html

dummy=`diff validruns.html validruns$year-latest.html | wc -l | tr -d ' '`
if [ $dummy -eq 0 ]
then 
echo 'No new validruns-list avalible!'
rm validruns.html
exit
fi
if [ $dummy -gt 0 ]
then
mv validruns.html validruns$year-$date_formated.html
ln -sf validruns$year-$date_formated.html validruns$year-latest.html
echo 'New valdiruns list!'
fi
