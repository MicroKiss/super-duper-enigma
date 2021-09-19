#!/bin/bash
read s
c=0
k=0
while [[ "$s" != "vege" ]] 
do 
(( c++ )) 
if [[ $s == z* ]] 
then 
(( k++ )) 
fi 
if [[ $s == *p ]] 
then 
(( k++ )) 
fi 
if [[ $s == z*p ]] 
then 
(( k-- )) 
fi 
read s 
done 
echo ennyi probalkozas: $c
echo ennyi keresett szo: $k
