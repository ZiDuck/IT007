#!/bin/sh
if [ $1 -ge 24 ]; then
	echo "Gio khong hop le" > $4
elif [ $2 -ge 60 ]; then
	echo "Phut khong hop le" > $4
elif [ $3 -gt 490 ];then
	echo "Thoi gian lam viec khong hop le" > $4
else
	gio=$(($3/60))
	phut=$(($3 - $gio*60))
	gio=$(($gio + $1))
	phut=$(($phut + $2))
	if [ $phut -ge 60 ];then
		phut=$(($phut/60))
		gio=$(($gio+1))
	fi
	if [ $gio -ge 24 ];then
		gio=$(($gio/24))
	fi
	echo "$gio $phut" > $4
fi
exit 0
