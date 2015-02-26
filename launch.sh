#!/bin/bash

# best, random, worst_best, tournament
select="tournament"
# cross_point, cross_uniform
cross="cross_point"
# bit_flip, k_flip
mutate="k_flip"
k=3
# compare_with_parents, age, replace_worst
insert="replace_worst"

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
    ./One-Future -select $select -cross $cross -mutate $mutate -k $k -insert $insert
    sleep 1
done