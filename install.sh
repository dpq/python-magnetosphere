#!/bin/bash

if test -z "$1"
then
	TARGET=/usr/local/lib/pygrf/
else
	TARGET=$1
fi

if [ ! -d "$TARGET" ]
then
	sudo mkdir $TARGET
fi

if ( ! type -P f2c > /dev/null )
then
    echo "F2C not installed, aborting"
		exit
fi

wget -r ftp://nssdcftp.gsfc.nasa.gov/models/geomagnetic/igrf/fortran_code/
if [ ! -d nssdcftp.gsfc.nasa.gov]
then
	echo "Failed to download IGRF source code. Please check your Internet connection."
else
	mv nssdcftp.gsfc.nasa.gov/models/geomagnetic/igrf/fortran_code/* .
	rm -rf nssdcftp.gsfc.nasa.gov
	for x in `ls *.for`; do mv $x `echo $x | sed s/.for/.F/`; done
	f2c igrf_sub.F

	cat igrf_sub.c | sed "s^o__1.ofnm = fout^extern char *trimwhitespace(char *str); char prefix_dp[28] = \"$TARGET\"; 	strcat(prefix_dp, fspec); o__1.ofnm = trimwhitespace(prefix_dp)^" > igrf_sub2.c
	mv igrf_sub2.c igrf_sub.c


	sudo mv *.dat $TARGET
	sudo python setup.py install
	sudo rm -rf build *.F bilcal.log igrf_sub.c
fi