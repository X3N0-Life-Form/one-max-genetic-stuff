#!/bin/bash

# best, random, worst_best, tournament
select="tournament"
# cross_point, cross_uniform
cross="cross_point"
# bit_flip, k_flip
mutate="bit_flip"
k=3
# compare_with_parents, age, replace_worst
insert="replace_worst"

options="-select $select -cross $cross -mutate $mutate -k $k -insert $insert"

loopCount=1

make

if [ "$#" -ge 1 ]
then
    echo "Setting loop count to $1"
    loopCount=$1
fi


for i in `seq 1 $loopCount`
do
    echo "Loop #$i/$loopCount"
    echo ./One-Future -automate $options 
    ./One-Future -automate $options
    sleep 1
done