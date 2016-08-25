#!/bin/bash

FILE=aesp8-ppc.S
LINES=$(grep -n "^\." $FILE | grep -v ".align\|.long\|.size\|.byte\|.machine\|.abiversion\|.text")

OLDIFS=$IFS
IFS=$'\n'
for LINE in $LINES; do
	LINE_NUMBER=$(echo $LINE | cut -d: -f1)
	FUNCTION=$(echo $LINE | cut -d: -f2)

	echo "b ${FILE}:${LINE_NUMBER}"
	#echo "b ${FILE}:${LINE_NUMBER} # $FUNCTION"
done
IFS=$OLDIFS
