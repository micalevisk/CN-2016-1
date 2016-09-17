#!/bin/bash

function fatorial {
	local fat=1 valor=$1 
	for ((i=1; i <= $valor; i++)); do
		fat=$(($fat * $i));
	done
	echo $fat
}


function serieSeno {
	local PRECISAO=21

	local M_PI=$(echo "scale=$PRECISAO; 4*a(1)" | bc -l)
	local X nSomas curr fatorialCurr sinal numerador denominador 
	local soma=" "

	[[ $# -ne 2 ]] && { echo "error" ; return 1; }
	X=$(echo "scale=$PRECISAO; ($1 * $M_PI)/180" | bc)

	nSomas=$2
	for ((N=0; N < nSomas; N++));do

		curr="$((2*$N +1))"
		fatorialCurr="$(fatorial $curr)"

		sinal="$([[ $(($N%2)) -eq 0 ]] && echo + || echo -)"	
		numerador="$(echo "scale=$PRECISAO; $X^$curr" | bc)" 
		denominador="$fatorialCurr"
		
		soma=${soma/% / $sinal ($numerador/$denominador) }	
	done

	soma="${soma/# +/}"


	#echo -ne "\033[40;31m" ## cor
	echo -ne "seno de $1 [$nSomas iterações] = " 
	#echo -ne "\033[40;31;1m" ## cor
	echo "scale=$PRECISAO; $soma" | bc | awk '{printf "%f\n", $0}' #| sed 's@^-\.@-0.@ ; s@^\.@0.@'
	#echo -ne "\033[0m"			## desativar cor

}
