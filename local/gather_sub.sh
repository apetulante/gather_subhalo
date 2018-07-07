#!/bin/bash

if [ $1 = 1 ]
then
    echo "cd /fs1/Abbie/Get_OneSub; ./get_one_survivor.sh "$2" "$3"" | ssh bender
fi
if [ $1 = 0 ]
then
   echo "cd /fs1/Abbie/Get_OneSub; ./get_one_merger.sh "$2" "$3"" | ssh bender
fi

scp bender:/fs1/Abbie/Get_OneSub/tree_*_*_*.txt $4
scp bender:/fs1/Abbie/Get_OneSub/needed_files.txt $4
