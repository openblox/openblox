#!/bin/bash

echo -e "<!DOCTYPE RCC><RCC version=\"1.0\">\n<qresource>" > internalrc.qrc

function checkFiles {
	for f in $1/*
	do
		echo -e "\t<file>$f</file>" >> internalrc.qrc
		if [ -d $f ]
		then
			checkFiles $f
		fi
	done
}

checkFiles rc

echo -e "</qresource>\n</RCC>" >> internalrc.qrc