#!/bin/bash

if test -z "$1"
then
	TARGET=/usr/local/lib/igrf/
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

cp nssdcftp.gsfc.nasa.gov/models/geomagnetic/igrf/fortran_code/* .
for x in `ls *.for`; do mv $x `echo $x | sed s/.for/.F/`; done
f2c igrf_sub.F

cat igrf_sub.c | sed "s^o__1.ofnm = fout^extern char *trimwhitespace(char *str); \
char prefix_dp[28] = \"$TARGET\"; strcat(prefix_dp, fspec); \
o__1.ofnm = trimwhitespace(prefix_dp)^" > igrf_sub2.c
mv igrf_sub2.c igrf_sub.c

sudo mv *.dat $TARGET

cp cxform-0.71/cxform-manual.c cxform-0.71/cxform-auto.c cxform-0.71/cxform.h .

sudo python setup.py install
sudo rm -rf build *.F bilcal_log.txt 00_readme.txt igrf_sub.c bilcal.log
sudo rm -rf build cxform-auto.c cxform-manual.c cxform.h
