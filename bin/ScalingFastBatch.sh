#! /usr/bin/

exe=./TAppEncoderStatic
headfile=SFResult
testname=Batch
cfgprefix=ScalingFast
prefix="$headfile"/"$testname"
#declare -a Videos=("Balloons" "PoznanStreet" "PoznanHall2" "Kendo" "Dancer" "GTFly" "Newspaper" "Shark")
declare -a Videos=("Balloons")
#declare -a QPs=("22" "27" "32" "37")
declare -a QPs=("22")
declare -a Exes=("TAppEncoderStaticSF1" "TAppEncoderStaticSF2" "TAppEncoderStaticSF4" "TAppEncoderStaticSF8")

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
		sf=1
		for exe in "${Exes[@]}"
		do
			echo ${exe} ${fname}QP${QP}.cfg
			#${exe} -c ../cfg/${cfgprefix}/${fname}/${fname}QP${QP}.cfg > $prefix/${fname}/${fname}QP${QP}${SF} 	
			touch $prefix/${fname}/${fname}QP${QP}SF${sf} 	
			sf=$((sf*2))
		done
	done
done

