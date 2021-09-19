#!/bin/bash


if test $# -le 1; then echo Nincs eleg parameter ; exit 1; fi # megnezi a parameterek szamat
if test $# -gt 3; then echo Tul sok parameter; exit 1; fi
if test $# -eq 2
    then
    case "$1" in # az elso parameter erteke
        h)
        for (( i=$2; i>0; i-- ))
            do  
        for (( j=i; j>0; j-- ))
        do  
             echo -n '*'
        done
    echo  
    done
    ;;
    *) echo hibas parameter!!; exit 1
    esac

fi
if test $# -eq 3
then

case "$1" in
t) 
for (( i=$2; i>0; i-- ))
do  
   for (( j=$3; j>0; j-- ))
do  
if [ $i == $2 ] || [ $i == 1 ] || [ $j == $3 ] || [ $j == 1 ]
then
   echo -n '*'
else
echo -n " "
fi
done
echo  
done
;;
*) echo hibas parameter!!; exit 1 #minden egyeb elso parameter erteknel
esac
fi
