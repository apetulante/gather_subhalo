#!/bin/bash

echo "Usage: create a table of halo properties for trees with a range of numbers, from tree_a_b_c.dat (input as 'abc') to tree_d_e_f.dat (input as 'def')"

tree=$1
mass_cut=1000
halo_num=$2

cp /fs2/shared/petulaa/sorted_trees/${tree}.dat .
treenum1=$(echo "$tree" | awk -F '_' '{print $2}' )
treenum2=$(echo "$tree" | awk -F '_' '{print $3}' )
treenum3=$(echo "$tree" | awk -F '_' '{print $4}' )    

tail -n +51 ${tree}.dat > ${tree}.txt
rm ${tree}.dat

sed '/^#/ d' < ${tree}.txt > temp_${tree}.txt
mv temp_${tree}.txt ${tree}.txt

lines=`cat ${tree}.txt | wc -l`
   
./tree_filesplitter_findsub ${tree}.txt $lines $treenum1 $treenum2 $treenum3 $halo_num

lines_halo=`cat ${tree}_halo_${halo_num}.txt | wc -l`

./sub_finder ${tree}_halo_${halo_num}.txt $lines_halo $treenum1 $treenum2 $treenum3 $halo_num

rm ${tree}.txt

#scp ${tree}_${halo}.txt abbie_local:/Documents/Research
#scp ${tree}_${halo}_MainHalo.txt abbie_local:/Documents/Research
