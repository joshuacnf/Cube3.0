#!/bin/bash

let min=100000000000000
bestconfig=""

while read line;
do
    ./genPatDB S $line
    let result=`./evalPatDB`
    if [ "$result" -lt "$min" ]
    then
	let min=$result
	mv databaseS.in databaseS0.in
	bestconfig=$line
	printf "Best configuration updated: "
	echo $min
    fi
    rm databaseS.in
    echo "$result"
    printf "\n"
done < "cubieSets.in"

mv databaseS0.in databaseS.in
printf "Best configuration: %s\n" "$bestconfig"
printf "Theoretical number of nodes generated at search depth of 18: "
echo $min
