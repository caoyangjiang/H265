#! /usr/bin/

exe=./TAppEncoderStatic
headfile=SFResult
testname=SkipGPU
cfgprefix=ScalingFast
prefix="$headfile"/"$testname"
#declare -a Videos=("Balloons" "PoznanStreet" "PoznanHall2" "Kendo" "Dancer" "GTFly" "Newspaper" "Shark")
declare -a Videos=("Newspaper" "Shark")
#declare -a QPs=("22" "27" "32" "37")
declare -a QPs=("37")

#Create directory for output result
if [ ! -d "$headfile" ]; then
	mkdir $headfile	
fi

if [ ! -d "$headfile/$testname" ]; then
	mkdir $headfile/$testname	
fi

for fname in "${Videos[@]}"
do
	if [ ! -d "$prefix/$fname" ]; then
		mkdir $prefix/$fname	
	fi
done

#Encoding
for fname in "${Videos[@]}"
do 
	for QP in "${QPs[@]}"
	do
		echo ../cfg/${cfgprefix}/${fname}/${fname}QP${QP}.cfg
		${exe} -c ../cfg/${cfgprefix}/${fname}/${fname}QP${QP}.cfg > $prefix/${fname}/${fname}QP${QP} 	
	done
done

