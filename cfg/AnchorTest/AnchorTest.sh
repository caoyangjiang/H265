#! /usr/bin/

alg=BaseTime


for fname in {"Balloons","PoznanStreet","PoznanHall2","Kendo","Dancer","GTFly","Newspaper","Shark"} 
do

	for QP in {"22","27","32","37"}
	do
		echo Encoding ${fname}QP${QP}.cfg
		./TAppEncoderStatic -c ../cfg/AnchorTest/${fname}/${fname}QP${QP}.cfg > ./Result/AnchorTest/${fname}/${fname}QP${QP} 
	done
done
