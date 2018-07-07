#!/bin/bash

echo "Usage: create a table of halo properties for trees with a range of numbers, from tree_a_b_c.dat (input as 'abc') to tree_d_e_f.dat (input as 'def')"

tree=$1
mass_cut=1000
halo_num=$2
trees_path='/fs2/shared/petulaa/sorted_trees/locations.dat'

# Get the subhalo tree
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

rm ${tree}.txt

line1=$(head -n 1 ${tree}_halo_${halo_num}.txt)
line1_arr=($line1)
host_ID=${line1_arr[6]}
host_tree=`python find_tree.py ${trees_path} ${host_ID}`

#echo $host_tree
#Get the host tree
cp /fs2/shared/petulaa/sorted_trees/${host_tree}.dat .
treenum1=$(echo "$host_tree" | awk -F '_' '{print $2}' )
treenum2=$(echo "$host_tree" | awk -F '_' '{print $3}' )
treenum3=$(echo "$host_tree" | awk -F '_' '{print $4}' )

tail -n +51 ${host_tree}.dat > ${host_tree}.txt
rm ${host_tree}.dat

sed '/^#/ d' < ${host_tree}.txt > temp_${host_tree}.txt
mv temp_${host_tree}.txt ${host_tree}.txt

lines=`cat ${host_tree}.txt | wc -l`

./tree_filesplitter_findhost ${host_tree}.txt $lines $treenum1 $treenum2 $treenum3 $host_ID

rm ${host_tree}.txt

echo "${tree}_halo_${halo_num}.txt" >> needed_files.txt
echo "${host_tree}_MainHalo.txt" >> needed_files.txt

#scp ${tree}_${halo}.txt abbie_local:/Documents/Research
#scp ${tree}_${halo}_MainHalo.txt abbie_local:/Documents/Research
