#! /usr/bin/

alg=BaseTime


for fname in {"GTFly","Newspaper","Shark"} 
do

	for QP in {"10","20","30","40","50"}
	do
		echo Encoding ${fname}QP${QP}NOSkip.cfg
		./TAppEncoderStaticNoSkip -c ../cfg/QPTest/${fname}/${fname}QP${QP}.cfg > ./Result/${fname}/${fname}QP${QP}NOSkip
		echo Encoding ${fname}QP${QP}Skip012.cfg
		./TAppEncoderStaticSkip0 -c  ../cfg/QPTest/${fname}/${fname}QP${QP}.cfg > ./Result/${fname}/${fname}QP${QP}Skip012
		echo Encoding ${fname}QP${QP}Skip12.cfg
		./TAppEncoderStaticSkip1 -c  ../cfg/QPTest/${fname}/${fname}QP${QP}.cfg > ./Result/${fname}/${fname}QP${QP}Skip12
		echo Encoding ${fname}QP${QP}Skip2.cfg
		./TAppEncoderStaticSkip2 -c  ../cfg/QPTest/${fname}/${fname}QP${QP}.cfg > ./Result/${fname}/${fname}QP${QP}Skip2
	done
done

