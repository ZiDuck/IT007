#!/bin/sh
if [ -f $2 ]; then
	echo "Thu muc $2 khong ton tai." > $3
else
	count=0 #dem so luong chuoi xuat hien trong thu muc
	for file in $(ls $2)
	do
		if grep -l $1 $2/$file ; then
		count=$(($count+1))
		fi
	done

	if [ "$count" -eq 0 ]; then
		echo "Trong thu muc $2 khong co tap tin nao chua chuoi $1" > $3
	else
		echo "Trong thu muc $2 co $count tap tin chua chuoi $1" > $3
	fi
fi
exit 0

