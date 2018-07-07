#!/bin/bash

echo "cd /fs1/Abbie/Get_OneSub; ./cleanup_sub.sh" | ssh bender

rm $3/tree_*_*_*.txt
