#!/bin/sh
# clean notused staff before commit
rm *.root
sh mc/cleaner_MC.sh
sh data/cleaner_DATA.sh

