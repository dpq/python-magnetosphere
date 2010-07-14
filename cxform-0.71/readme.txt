CXFORM:  An IDL/C library to convert between spacecraft coordinate systems

Originally written by Ed Santiago (LANL), esm@pobox.com
Modified & maintained by Ryan Boller (NASA/GSFC), Ryan.A.Boller@nasa.gov

	
============================
  OVERVIEW
============================

The CXFORM package contains a set of routines to convert spacecraft coordinates
from one system to another, i.e., GSE-->GSM.  It is written in C and can be
used as either a C library (.so or .dll) or an IDL function (via DLM -- 
Dynamically Loadable Module -- interface).

It has been tested under SunOS v5.7, Microsoft Windows 2000/XP, Mac OS X 10.3 &
10.4, and Linux 2.4.20-28.9.  It has previously been tested under Solaris 2.6 and
DEC OSF/1 V4.0.

It is largely based on Mike Hapgood's excellent introduction to coordinate 
transformations, along with Markus Fraenz' "Heliospheric Coordinate Systems" 
and Christopher Russell's "Geophysical Coordinate Transformations":

	http://sspg1.bnsc.rl.ac.uk/Share/Coordinates/ct_home.htm
	http://www.space-plasma.qmul.ac.uk/heliocoords/
	http://www-ssc.igpp.ucla.edu/personnel/russell/papers/gct1.html/

Note that since this follows much of Hapgood's formulae that are optimized for
simplicity and efficiency, he specifies a level of precision of 0.001 degrees
up to the year 2100 for each rotation angle, which has been deemed sufficient
for space physics applications. The disclaimer applies that these should not
be used for mission-critical flight applications due to their margin of error.

Formal testing has been completed as of 2004/12/01.  The results can be found
on the CXFORM web page.  In general, they are within 1% of the results of
SSCWeb's calculations (based on GEOPACK), and in many cases are within
0.01%.

Questions/comments/suggestions are welcome to Ryan.A.Boller@nasa.gov


============================
  INSTALLATION
============================

See install.txt for instructions.


============================
  USAGE FROM IDL
============================

The function prototype is

	new = CXFORM( pos, source_frame, dest_frame, time )

where:
	pos		is a vector of length 3, containing the position
			in source_frame coordinates. It can also be a 2-D
			array of size [3, M], where M is the number of points
			to convert

	source_frame	is an ASCII string naming the source
			coordinate system, e.g., 'GSE', 'J2000'.  See 
			"Coordinate Systems Implemented" below.

	dest_frame	is also an ASCII string, naming the destination
			coordinate system.

	time		is "ephemeris seconds past J2000 (1 Jan 2000 12:00)".
			The "date2es" function converts a standard Gregorian
			time (mm,dd,yyyy) to Ephemeris Seconds past/before
			J2000.  See the included "date2es.pro" file for more 
			details.

	new		is the position, in dest_frame coordinates.



Single-coordinate example:

	IDL> es = date2es(9,30,1999,7,5,0)  ; Sep. 30, 1999 07:05:00 UTC
	IDL> pos = cxform([1,0,0], 'GSE', 'GEO', et)
	IDL> help,pos
	POS             DOUBLE    = Array[3]
	IDL> print,pos
	       0.32034915      0.94616669    -0.046314350
	IDL> 


Multiple-coordinate example:

	IDL> imp8GEI = fltarr(3, 5)
	IDL> imp8Time = lonarr(5)
	IDL>
	IDL> help, imp8GEI
	IMP8GEI		FLOAT		= Array[3, 5]
	IDL> help, imp8Time
	IMP8TIME	LONG		= Array[5]
	IDL>
	IDL>
	IDL> imp8GEI[*,0] = [-32.562, 20.085, -10.471]
	IDL> imp8GEI[*,1] = [-34.415, 4.229, -6.173]
	...
	IDL> print, imp8GEI
		-32.5620	20.0850		-10.4710
		-34.4150	4.22900		-6.17300
		-27.2210	-12.441		-0.34300
		-9.01000	-23.380		 5.39300
		 14.1890	-19.583		 7.58900
	IDL>
	IDL> imp8Time = [-43200, 43200, 129600, 216000, 302400]
	IDL>
	IDL> imp8GEO = cxform(imp8GEI, 'GEI', 'GEO', imp8Time)
	IDL>
	IDL> print, imp8GEO
       25.418317       28.593709      -10.471000
       10.691414       32.984396      -6.1729999
      -6.5404276       29.205893     -0.34299999
      -20.772292       14.011294       5.3930001
      -22.419840      -9.0648980       7.5890002


Note that if your data is imported as [M, 3] instead of [3, M], you can
transpose it using IDL's TRANSPOSE function:

	IDL> correctArr = fltarr(3, M)
	IDL> correctArr = TRANSPOSE(originalArr)

		
============================
  USAGE FROM C
============================

See main.c included in this package for an example of using CXFORM in C.
See install.txt for instructions on building it on your platform.


============================
  TEST RESULTS
============================

The bulk of the testing used SSCWeb's Locator Tabulator as the data source.
As stated in the introduction, this service uses GEOPACK for its calculations.
An included file, tester.c, was used to read in data from SSCWeb and
compare it to the results of CXFORM.  In addition, one data point was used from
the HelioCoords transformation package documentation as a sanity check and also
as a test for the heliospheric systems that are not present in SSCWeb.

See the following URL for links to the actual results:
http://nssdcftp.gsfc.nasa.gov/selected_software/coordinate_transform/#Test_Results

	
==================================
  COORDINATE SYSTEMS IMPLEMENTED
==================================

GEI			Geocentric Equatorial Inertial, also known as True
			Equator and True Equinox of Date, True of Date (TOD),
			ECI, or GCI
J2000			Geocentric Equatorial Inertial for epoch J2000.0 
			(GEI2000), also known as Mean Equator and Mean Equinox
			of J2000.0
GEO			Geographic, also known as Greenwich Rotating
			Coordinates (GRC), or Earth-fixed Greenwich (EFG)
MAG			Geomagnetic
GSE			Geocentric Solar Ecliptic
GSM			Geocentric Solar Magnetospheric
SM			Solar Magnetic
RTN*		Radial Tangential Normal (Earth-centered)
GSEQ		Geocentric Solar Equatorial
HEE			Heliocentric Earth Ecliptic
HAE			Heliocentric Aries Ecliptic
HEEQ		Heliocentric Earth Equatorial


* = this system has not been tested and should be treated as such


=================================
  ADDING NEW COORDINATE SYSTEMS
=================================

This package has been designed to allow for easy additions of new coordinate
systems.

All you need to do is define one transformation between the new system and any
of the existing ones.  Once you do that, the Perl script will generate code to
convert to all others.  This, of course, means that a working copy of Perl must
be installed.  You will need the IxHash module if it is not already installed.
It can be found at http://search.cpan.org/dist/Tie-IxHash/

Here's what you do:

  1. Edit the file cxform-manual.c and add a new function, xxxx_twixt_yyyy, 
     where `xxxx' is any existing coordinate frame, and `yyyy' is the new one.

  2. Run "perl gen_cxform_auto.pl cxform-manual.c" from the prompt. This will
     create a new cxform-auto.c with support for your new coordinate system.
     
  3. Build and install a new CXFORM library as described in install.txt.

  4. Run and test it in IDL/C.  That's it! 

If it works, please send me your code.  I will include it in the next 
distribution (with appropriate credit to you, of course).


============================
  VERSION HISTORY
============================

2000/06/21  v0.2  Ed Santiago:  Last released version from Ed.
2003/09/12  v0.3  Ryan Boller:  First modified version from Ryan.  Added RTN
		  and GSEQ systems, IGRF2000 model, slightly different time
		  manipulation, Windows support, additional documentation, and
		  standalone C functionality.
2004/03/19  v0.4  Ryan Boller:  Updated Makefile to auto-detect platform and
          to build under Mac OS X.  HEEQ system now implemented by Kristi
          Keller.
2004/05/21  v0.5  Ryan Boller:  Fixed small discrepancy in calculation of
          T0 and lambda0.  Results now match those of SSCWeb's (GEOPACK-
          based) when the mag pole lat/lon is fixed to their values,
          as they haven't updated their IGRF coefficients.
2004/12/01  v0.6  Ryan Boller: Finished comprehensive testing, posted results.
          Updated IGRF to Revision 9.  Moved cxRound, date2es, and
          gregorian_calendar_to_jd to cxform-manual.c so it is included
          in the shared library.
2006/10/19  v0.7  Ryan Boller: Updated IGRF coefficients to 10th generation.
          Fixed IDL DLM interface under Windows XP & IDL 6.0+. Updated
          installation documentation.
2009/11/25  v0.71  Ryan Boller: Updated Mac compiler flags to compile 32- and 
          64-bit versions on Intel- and PPC-based CPUs.  Fixed memory pointer
          problem on 64-bit machines (now using IDL_MEMINT instead of IDL_LONG
          in cxform-dlm.c).

============================
  KNOWN ISSUES / TODOs
============================

- Mac shared object does not link with C objects.  May need to convert to a
  dylib.  The shared object does work with the IDL DLM interface, though.
- RTN system needs to be tested for accuracy