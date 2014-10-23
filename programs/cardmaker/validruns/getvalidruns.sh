#! /bin/zsh -f
#if [ $# -gt 0 -a $# -ne 3 -a $# -ne 4]
#then
    echo 'usage: getvalidruns <date> [leptons]'
    echo '       date: 04 02 27 '
    echo '       date: 99 02 27 e'
#    exit
#fi

if [ $# -eq 3 ]
then
    date_formated=$1$2$3
    year=$1
    leptons=""
    if [ $year -eq 98 ]
    then
	leptons="e"
    fi
fi
if [ $# -eq 4 ]
then
    date_formated=$1$2$3
    year=$1
    leptons=$4
fi
if [ $# -eq 0 ]
    then
    date_formated=`date +%y%m%d`
    year=`date +%y`
    leptons=""
fi

echo "Downloading validruns for $year$leptons"
if [ $leptons = "e" -a $year -eq 99 ]
then
    wget http://www-zeus.desy.de/physics/lumi/lumi$year$leptons/validruns.html
else
    wget http://www-zeus.desy.de/physics/lumi/lumi$year/validruns.html
fi

if [ -e validruns$year$leptons-latest.html ] 
then
    dummy=`diff validruns.html validruns$year$leptons-latest.html | wc -l | tr -d ' '`
else
    echo "creating new validruns file"
    dummy="1"
fi
if [ $dummy -eq 0 ]
then 
    echo 'No new validruns-list avalible!'
    rm validruns.html
fi
if [ $dummy -gt 0 ]
then
    mv validruns.html validruns$year$leptons-$date_formated.html
    ln -sf validruns$year$leptons-$date_formated.html validruns$year$leptons-latest.html
    echo 'New valdiruns list!'
fi
# hera 1 format
echo $year$leptons
if [ $year -ge "96" -a  $year -le "99" ]
    then
    echo "HERA I format"
    grep "  +   [[:digit:]][[:digit:]][[:digit:]][[:digit:]][[:digit:]] " validruns$year$leptons-latest.html | gawk  -F" " '{runnr=$2;events=$4;lumi=$3;print runnr "\t" lumi "\t" events}' > validruns_$year$leptons.txt
else
# hera 2 format
    echo "HERA II format"
    grep "+  [[:digit:]][[:digit:]][[:digit:]][[:digit:]][[:digit:]] " validruns$year-latest.html | gawk  -F" " '{runnr=$2;events=$3;lumi=$4;print runnr "\t" lumi "\t" events}' > validruns_$year.txt
fi
