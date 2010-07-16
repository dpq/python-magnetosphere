/* igrf_sub.F -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

union {
    struct {
	real umr, era, aquad, bquad;
    } _1;
    struct {
	real umr, erad, aquad, bquad;
    } _2;
} gener_;

#define gener_1 (gener_._1)
#define gener_2 (gener_._2)

struct {
    real sp[3];
} fidb0_;

#define fidb0_1 fidb0_

union {
    struct {
	real x[3], h__[196];
    } _1;
    struct {
	real xi[3], h__[196];
    } _2;
} igrf2_;

#define igrf2_1 (igrf2_._1)
#define igrf2_2 (igrf2_._2)

union {
    struct {
	char name__[13];
	integer nmax;
	real time, g[196];
    } _1;
    struct {
	char fil1[13];
	integer nmax;
	real time, gh1[196];
    } _2;
} model_;

#define model_1 (model_._1)
#define model_2 (model_._2)

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__4 = 4;

/* IGRF_SUB.FOR */
/* ********************************************************************* */
/*  SUBROUTINES igrf_sub plus SHELLIG.FOR (see below)                 * */
/* ********************************************************************* */
/* ********************************************************************* */

/* 11/01/91 SHELLG: lowest starting point for B0 search is 2 */
/*  1/27/92 Adopted to IGRF-91 coeffcients model */
/*  2/05/92 Reduce variable names: INTER(P)SHC,EXTRA(P)SHC,INITI(ALI)ZE */
/*  8/08/95 Updated to IGRF-45-95; new coeff. DGRF90, IGRF95, IGRF95S */
/*  5/31/00 Updated to IGRF-45-00; new coeff.: IGRF00, IGRF00s */
/* -Version-mm/dd/yy-Description (Person reporting the correction) */
/* 2000.01 05/07/01 initial version */
/* 2000.02 07/11/01 replace feldi(xi,h) by feldi (P. Wilkinson) */
/* 2000.02 07/11/01 variables EGNR, AGNR,OGNR not used (P. Wilkinson) */
/* 2000.01 10/28/02 replace TAB/6 blanks, enforce 72/line (D. Simpson) */
/* 2000.02 11/08/02 change unit for coefficients to 14 */
/* 2000.03 06/05/03 correct DIPL computation (V. Truhlik) */
/* 2005.00 04/25/05 CALL FELDI and DO 1111 I=1,7 (Alexey Petrov) */
/* 2005.01 11/10/05 added igrf_dip and geodip (MLAT) */
/* 2005.02 11/10/05 updated to IGRF-10 version */
/* 2006.00 12/21/06 GH2(120) -> GH2(144) */
/* 2010.00 03/12/09 SHELLG: NMAX=13 for DGRF00 & IGRF05; H/G-arrays(195) */
/* 2010.01 02/26/10 FELDCOF: IGRF-11; new coeff: DGRF05, IGRF10, IGRF10S */

/* ********************************************************************* */
/* Subroutine */ int igrf_sub__(real *xlat, real *xlong, real *year, real *
	height, real *xl, integer *icode, real *dip, real *dec)
{
    /* Builtin functions */
    double log(doublereal), asin(doublereal), sqrt(doublereal);

    /* Local variables */
    static real bab1;
    static integer ibbb;
    static real babs, dimo, lati, alog2;
    extern /* Subroutine */ int feldg_(real *, real *, real *, real *, real *,
	     real *, real *);
    static real beast, longi, bdown;
    extern /* Subroutine */ int shellg_(real *, real *, real *, real *, real *
	    , integer *, real *);
    static real bnorth;
    static integer istart;
    extern /* Subroutine */ int feldcof_(real *, real *), initize_(void);

/* ---------------------------------------------------------------- */
/*   INPUT: */
/* 	xlat	geodatic latitude in degrees */
/* 	xlong	geodatic longitude in degrees */
/* 	year	decimal year (year+month/12.0-0.5 or year+day-of-year/365 */
/* 		or 366 if leap year) */
/* 	height	height in km */
/*   OUTPUT: */
/* 	xl	L value */
/* 	icode	=1  L is correct; =2  L is not correct; */
/* 		=3  an approximation is used */
/* 	dip	geomagnetic inclination in degrees */
/* 	dec	geomagnetic declination in degress */
/* ---------------------------------------------------------------- */

    initize_();
    ibbb = 0;
    alog2 = log(2.f);
    istart = 1;
    lati = *xlat;
    longi = *xlong;

/* ----------------CALCULATE PROFILES----------------------------------- */

    feldcof_(year, &dimo);
    feldg_(&lati, &longi, height, &bnorth, &beast, &bdown, &babs);
    shellg_(&lati, &longi, height, &dimo, xl, icode, &bab1);
    *dip = asin(bdown / babs) / gener_1.umr;
    *dec = asin(beast / sqrt(beast * beast + bnorth * bnorth)) / gener_1.umr;
    return 0;
} /* igrf_sub__ */



/* SHELLIG.FOR */

/* 11/01/91 SHELLG: lowest starting point for B0 search is 2 */
/*  1/27/92 Adopted to IGRF-91 coeffcients model */
/*  2/05/92 Reduce variable-names: INTER(P)SHC,EXTRA(P)SHC,INITI(ALI)ZE */
/*  8/08/95 Updated to IGRF-45-95; new coeff. DGRF90, IGRF95, IGRF95S */
/*  5/31/00 Updated to IGRF-45-00; new coeff.: IGRF00, IGRF00s */
/*  3/24/05 Updated to IGRF-45-10; new coeff.: IGRF05, IGRF05s */
/*  4/25/05 ENTRY FELDI(XI,H) and  DO 1111 I=1,7 [Alexey Petrov] */
/*  7/22/09 SHELLG: NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/*  2/26/10 FELDCOF: Updated IGRF45-15; new coeff: DGRF05, IGRF10, IGRF10S */
/*  4/29/10 H/H-arrays(196); FELDCOF: corrected IGRF00 and ..00S */
/*  4/29/10 Change to new files dgrf%%%%.asc; new GETSHC; char*12 to 13 */
/* ********************************************************************* */
/*  SUBROUTINES FINDB0, SHELLG, STOER, FELDG, FELDCOF, GETSHC,        * */
/*       INTERSHC, EXTRASHC, INITIZE                                  * */
/* ********************************************************************* */
/* ********************************************************************* */


/* Subroutine */ int findb0_(real *stps, real *bdel, logical *value, real *
	bequ, real *rr0)
{
    /* Builtin functions */
    double r_sign(real *, real *), sqrt(doublereal);

    /* Local variables */
    static real b;
    static integer i__, j, n;
    static real p[32]	/* was [8][4] */, r1, r2, r3, zz, bq1, bq2, bq3, bold,
	     bmin, rold, step;
    static integer irun;
    static real step12;
    extern /* Subroutine */ int stoer_(real *, real *, real *);
    static real bdelta;

/* -------------------------------------------------------------------- */
/* FINDS SMALLEST MAGNETIC FIELD STRENGTH ON FIELD LINE */

/* INPUT:   STPS   STEP SIZE FOR FIELD LINE TRACING */
/*       COMMON/FIDB0/ */
/*          SP     DIPOLE ORIENTED COORDINATES FORM SHELLG; P(1,*), */
/*                 P(2,*), P(3,*) CLOSEST TO MAGNETIC EQUATOR */
/*          BDEL   REQUIRED ACCURACY  = [ B(LAST) - BEQU ] / BEQU */
/*                 B(LAST)  IS FIELD STRENGTH BEFORE BEQU */

/* OUTPUT:  VALUE  =.FALSE., IF BEQU IS NOT MINIMAL VALUE ON FIELD LINE */
/*          BEQU   MAGNETIC FIELD STRENGTH AT MAGNETIC EQUATOR */
/*          RR0    EQUATORIAL RADIUS NORMALIZED TO EARTH RADIUS */
/*          BDEL   FINAL ACHIEVED ACCURACY */
/* -------------------------------------------------------------------- */

    step = *stps;
    irun = 0;
L7777:
    ++irun;
    if (irun > 5) {
	*value = FALSE_;
	goto L8888;
    }
/* *********************FIRST THREE POINTS */
    p[8] = fidb0_1.sp[0];
    p[9] = fidb0_1.sp[1];
    p[10] = fidb0_1.sp[2];
    step = -r_sign(&step, &p[10]);
    stoer_(&p[8], &bq2, &r2);
    p[16] = p[8] + step * .5f * p[11];
    p[17] = p[9] + step * .5f * p[12];
    p[18] = p[10] + step * .5f;
    stoer_(&p[16], &bq3, &r3);
    p[0] = p[8] - step * (p[11] * 2.f - p[19]);
    p[1] = p[9] - step * (p[12] * 2.f - p[20]);
    p[2] = p[10] - step;
    stoer_(p, &bq1, &r1);
    p[16] = p[8] + step * (p[19] * 20.f - p[11] * 3.f + p[3]) / 18.f;
    p[17] = p[9] + step * (p[20] * 20.f - p[12] * 3.f + p[4]) / 18.f;
    p[18] = p[10] + step;
    stoer_(&p[16], &bq3, &r3);
/* ******************INVERT SENSE IF REQUIRED */
    if (bq3 <= bq1) {
	goto L2;
    }
    step = -step;
    r3 = r1;
    bq3 = bq1;
    for (i__ = 1; i__ <= 5; ++i__) {
	zz = p[i__ - 1];
	p[i__ - 1] = p[i__ + 15];
/* L1: */
	p[i__ + 15] = zz;
    }
/* ******************INITIALIZATION */
L2:
    step12 = step / 12.f;
    *value = TRUE_;
    bmin = 1e4f;
    bold = 1e4f;
/* ******************CORRECTOR (FIELD LINE TRACING) */
    n = 0;
L5555:
    p[16] = p[8] + step12 * (p[19] * 5.f + p[11] * 8.f - p[3]);
    ++n;
    p[17] = p[9] + step12 * (p[20] * 5.f + p[12] * 8.f - p[4]);
/* ******************PREDICTOR (FIELD LINE TRACING) */
    p[24] = p[16] + step12 * (p[19] * 23.f - p[11] * 16.f + p[3] * 5.f);
    p[25] = p[17] + step12 * (p[20] * 23.f - p[12] * 16.f + p[4] * 5.f);
    p[26] = p[18] + step;
    stoer_(&p[24], &bq3, &r3);
    for (j = 1; j <= 3; ++j) {
/*        DO 1111 I=1,8 */
	for (i__ = 1; i__ <= 7; ++i__) {
/* L1111: */
	    p[i__ + (j << 3) - 9] = p[i__ + (j + 1 << 3) - 9];
	}
    }
    b = sqrt(bq3);
    if (b < bmin) {
	bmin = b;
    }
    if (b <= bold) {
	bold = b;
	rold = 1.f / r3;
	fidb0_1.sp[0] = p[24];
	fidb0_1.sp[1] = p[25];
	fidb0_1.sp[2] = p[26];
	goto L5555;
    }
    if (bold != bmin) {
	*value = FALSE_;
    }
    bdelta = (b - bold) / bold;
    if (bdelta > *bdel) {
	step /= 10.f;
	goto L7777;
    }
L8888:
    *rr0 = rold;
    *bequ = bold;
    *bdel = bdelta;
    return 0;
} /* findb0_ */



/* Subroutine */ int shellg_0_(int n__, real *glat, real *glon, real *alt, 
	real *dimo, real *fl, integer *icode, real *b0, real *v)
{
    /* Initialized data */

    static real rmin = .05f;
    static real rmax = 1.01f;
    static real step = .2f;
    static real steq = .03f;
    static real u[9]	/* was [3][3] */ = { .3511737f,-.9148385f,-.1993679f,
	    .9335804f,.358368f,0.f,.0714471f,-.186126f,.9799247f };

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), sqrt(doublereal), r_sign(real *, 
	    real *), log(doublereal), exp(doublereal);

    /* Local variables */
    static real d__;
    static integer i__, n;
    static real p[800]	/* was [8][100] */, r__, t, z__, c0, c1, c2, c3, d0, 
	    d1, d2, e0, e1, e2, r1, r2, r3, ff, gg, fi, ct, rq, st, zq, xx, 
	    zz, bq1, bq2, bq3, r3h, hli, stp, arg1, arg2, bequ, rlat;
    static integer iequ;
    static real term, rlon, step2, radik, step12, oterm;
    extern /* Subroutine */ int stoer_(real *, real *, real *);
    static real dimob0, oradik;

/* -------------------------------------------------------------------- */
/* CALCULATES L-VALUE FOR SPECIFIED GEODAETIC COORDINATES, ALTITUDE */
/* AND GEMAGNETIC FIELD MODEL. */
/* REF: G. KLUGE, EUROPEAN SPACE OPERATIONS CENTER, INTERNAL NOTE */
/*      NO. 67, 1970. */
/*      G. KLUGE, COMPUTER PHYSICS COMMUNICATIONS 3, 31-35, 1972 */
/* -------------------------------------------------------------------- */
/* CHANGES (D. BILITZA, NOV 87): */
/*   - USING CORRECT DIPOL MOMENT I.E.,DIFFERENT COMMON/MODEL/ */
/* 09/07/22 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* -------------------------------------------------------------------- */
/*  INPUT:  ENTRY POINT SHELLG */
/*               GLAT  GEODETIC LATITUDE IN DEGREES (NORTH) */
/*               GLON  GEODETIC LONGITUDE IN DEGREES (EAST) */
/*               ALT   ALTITUDE IN KM ABOVE SEA LEVEL */

/*          ENTRY POINT SHELLC */
/*               V(3)  CARTESIAN COORDINATES IN EARTH RADII (6371.2 KM) */
/*                       X-AXIS POINTING TO EQUATOR AT 0 LONGITUDE */
/*                       Y-AXIS POINTING TO EQUATOR AT 90 LONG. */
/*                       Z-AXIS POINTING TO NORTH POLE */

/*          DIMO       DIPOL MOMENT IN GAUSS (NORMALIZED TO EARTH RADIUS) */

/*          COMMON */
/*               X(3)    NOT USED */
/*               H(144)  FIELD MODEL COEFFICIENTS ADJUSTED FOR SHELLG */
/* ----------------------------------------------------------------------- */
/*  OUTPUT: FL           L-VALUE */
/*          ICODE        =1 NORMAL COMPLETION */
/*                       =2 UNPHYSICAL CONJUGATE POINT (FL MEANINGLESS) */
/*                       =3 SHELL PARAMETER GREATER THAN LIMIT UP TO */
/*                          WHICH ACCURATE CALCULATION IS REQUIRED; */
/*                          APPROXIMATION IS USED. */
/*          B0           MAGNETIC FIELD STRENGTH IN GAUSS */
/* ----------------------------------------------------------------------- */

/* -- RMIN, RMAX ARE BOUNDARIES FOR IDENTIFICATION OF ICODE=2 AND 3 */
/* -- STEP IS STEP SIZE FOR FIELD LINE TRACING */
/* -- STEQ IS STEP SIZE FOR INTEGRATION */

    /* Parameter adjustments */
    if (v) {
	--v;
	}

    /* Function Body */
    switch(n__) {
	case 1: goto L_shellc;
	}

    bequ = 1e10f;
/* *****ENTRY POINT  SHELLG  TO BE USED WITH GEODETIC CO-ORDINATES */
    rlat = *glat * gener_1.umr;
    ct = sin(rlat);
    st = cos(rlat);
    d__ = sqrt(gener_1.aquad - (gener_1.aquad - gener_1.bquad) * ct * ct);
    igrf2_1.x[0] = (*alt + gener_1.aquad / d__) * st / gener_1.era;
    igrf2_1.x[2] = (*alt + gener_1.bquad / d__) * ct / gener_1.era;
    rlon = *glon * gener_1.umr;
    igrf2_1.x[1] = igrf2_1.x[0] * sin(rlon);
    igrf2_1.x[0] *= cos(rlon);
    goto L9;

L_shellc:
/* *****ENTRY POINT  SHELLC  TO BE USED WITH CARTESIAN CO-ORDINATES */
    igrf2_1.x[0] = v[1];
    igrf2_1.x[1] = v[2];
    igrf2_1.x[2] = v[3];
/* *****CONVERT TO DIPOL-ORIENTED CO-ORDINATES */
L9:
    rq = 1.f / (igrf2_1.x[0] * igrf2_1.x[0] + igrf2_1.x[1] * igrf2_1.x[1] + 
	    igrf2_1.x[2] * igrf2_1.x[2]);
    r3h = sqrt(rq * sqrt(rq));
    p[8] = (igrf2_1.x[0] * u[0] + igrf2_1.x[1] * u[1] + igrf2_1.x[2] * u[2]) *
	     r3h;
    p[9] = (igrf2_1.x[0] * u[3] + igrf2_1.x[1] * u[4]) * r3h;
    p[10] = (igrf2_1.x[0] * u[6] + igrf2_1.x[1] * u[7] + igrf2_1.x[2] * u[8]) 
	    * rq;
/* *****FIRST THREE POINTS OF FIELD LINE */
    step = -r_sign(&step, &p[10]);
    stoer_(&p[8], &bq2, &r2);
    *b0 = sqrt(bq2);
    p[16] = p[8] + step * .5f * p[11];
    p[17] = p[9] + step * .5f * p[12];
    p[18] = p[10] + step * .5f;
    stoer_(&p[16], &bq3, &r3);
    p[0] = p[8] - step * (p[11] * 2.f - p[19]);
    p[1] = p[9] - step * (p[12] * 2.f - p[20]);
    p[2] = p[10] - step;
    stoer_(p, &bq1, &r1);
    p[16] = p[8] + step * (p[19] * 20.f - p[11] * 3.f + p[3]) / 18.f;
    p[17] = p[9] + step * (p[20] * 20.f - p[12] * 3.f + p[4]) / 18.f;
    p[18] = p[10] + step;
    stoer_(&p[16], &bq3, &r3);
/* *****INVERT SENSE IF REQUIRED */
    if (bq3 <= bq1) {
	goto L2;
    }
    step = -step;
    r3 = r1;
    bq3 = bq1;
    for (i__ = 1; i__ <= 7; ++i__) {
	zz = p[i__ - 1];
	p[i__ - 1] = p[i__ + 15];
/* L1: */
	p[i__ + 15] = zz;
    }
/* *****SEARCH FOR LOWEST MAGNETIC FIELD STRENGTH */
L2:
    if (bq1 < bequ) {
	bequ = bq1;
	iequ = 1;
    }
    if (bq2 < bequ) {
	bequ = bq2;
	iequ = 2;
    }
    if (bq3 < bequ) {
	bequ = bq3;
	iequ = 3;
    }
/* *****INITIALIZATION OF INTEGRATION LOOPS */
    step12 = step / 12.f;
    step2 = step + step;
    steq = r_sign(&steq, &step);
    fi = 0.f;
    *icode = 1;
    oradik = 0.f;
    oterm = 0.f;
    stp = r2 * steq;
    z__ = p[10] + stp;
    stp /= .75f;
    p[7] = step2 * (p[0] * p[3] + p[1] * p[4]);
    p[15] = step2 * (p[8] * p[11] + p[9] * p[12]);
/* *****MAIN LOOP (FIELD LINE TRACING) */
    for (n = 3; n <= 3333; ++n) {
/* *****CORRECTOR (FIELD LINE TRACING) */
	p[(n << 3) - 8] = p[(n - 1 << 3) - 8] + step12 * (p[(n << 3) - 5] * 
		5.f + p[(n - 1 << 3) - 5] * 8.f - p[(n - 2 << 3) - 5]);
	p[(n << 3) - 7] = p[(n - 1 << 3) - 7] + step12 * (p[(n << 3) - 4] * 
		5.f + p[(n - 1 << 3) - 4] * 8.f - p[(n - 2 << 3) - 4]);
/* *****PREPARE EXPANSION COEFFICIENTS FOR INTERPOLATION */
/* *****OF SLOWLY VARYING QUANTITIES */
	p[(n << 3) - 1] = step2 * (p[(n << 3) - 8] * p[(n << 3) - 5] + p[(n <<
		 3) - 7] * p[(n << 3) - 4]);
/* Computing 2nd power */
	r__1 = p[(n - 1 << 3) - 8];
/* Computing 2nd power */
	r__2 = p[(n - 1 << 3) - 7];
	c0 = r__1 * r__1 + r__2 * r__2;
	c1 = p[(n - 1 << 3) - 1];
	c2 = (p[(n << 3) - 1] - p[(n - 2 << 3) - 1]) * .25f;
	c3 = (p[(n << 3) - 1] + p[(n - 2 << 3) - 1] - c1 - c1) / 6.f;
	d0 = p[(n - 1 << 3) - 3];
	d1 = (p[(n << 3) - 3] - p[(n - 2 << 3) - 3]) * .5f;
	d2 = (p[(n << 3) - 3] + p[(n - 2 << 3) - 3] - d0 - d0) * .5f;
	e0 = p[(n - 1 << 3) - 2];
	e1 = (p[(n << 3) - 2] - p[(n - 2 << 3) - 2]) * .5f;
	e2 = (p[(n << 3) - 2] + p[(n - 2 << 3) - 2] - e0 - e0) * .5f;
/* *****INNER LOOP (FOR QUADRATURE) */
L4:
	t = (z__ - p[(n - 1 << 3) - 6]) / step;
	if (t > 1.f) {
	    goto L5;
	}
	hli = (((c3 * t + c2) * t + c1) * t + c0) * .5f;
	zq = z__ * z__;
	r__ = hli + sqrt(hli * hli + zq);
	if (r__ <= rmin) {
	    goto L30;
	}
	rq = r__ * r__;
	ff = sqrt(zq * 3.f / rq + 1.f);
	radik = *b0 - ((d2 * t + d1) * t + d0) * r__ * rq * ff;
	if (r__ - rmax <= 0.f) {
	    goto L44;
	} else {
	    goto L45;
	}
L45:
	*icode = 2;
/* Computing 2nd power */
	r__1 = r__ - rmax;
	radik -= r__1 * r__1 * 12.f;
L44:
	if (radik + radik <= oradik) {
	    goto L10;
	}
	term = sqrt(radik) * ff * ((e2 * t + e1) * t + e0) / (rq + zq);
	fi += stp * (oterm + term);
	oradik = radik;
	oterm = term;
	stp = r__ * steq;
	z__ += stp;
	goto L4;
/* *****PREDICTOR (FIELD LINE TRACING) */
L5:
	p[(n + 1 << 3) - 8] = p[(n << 3) - 8] + step12 * (p[(n << 3) - 5] * 
		23.f - p[(n - 1 << 3) - 5] * 16.f + p[(n - 2 << 3) - 5] * 5.f)
		;
	p[(n + 1 << 3) - 7] = p[(n << 3) - 7] + step12 * (p[(n << 3) - 4] * 
		23.f - p[(n - 1 << 3) - 4] * 16.f + p[(n - 2 << 3) - 4] * 5.f)
		;
	p[(n + 1 << 3) - 6] = p[(n << 3) - 6] + step;
	stoer_(&p[(n + 1 << 3) - 8], &bq3, &r3);
/* *****SEARCH FOR LOWEST MAGNETIC FIELD STRENGTH */
	if (bq3 < bequ) {
	    iequ = n + 1;
	    bequ = bq3;
	}
/* L3: */
    }
L10:
    if (iequ < 2) {
	iequ = 2;
    }
    fidb0_1.sp[0] = p[(iequ - 1 << 3) - 8];
    fidb0_1.sp[1] = p[(iequ - 1 << 3) - 7];
    fidb0_1.sp[2] = p[(iequ - 1 << 3) - 6];
    if (oradik < 1e-15f) {
	goto L11;
    }
    fi += stp / .75f * oterm * oradik / (oradik - radik);

/* -- The minimal allowable value of FI was changed from 1E-15 to 1E-12, */
/* -- because 1E-38 is the minimal allowable arg. for ALOG in our envir. */
/* -- D. Bilitza, Nov 87. */

L11:
    fi = dabs(fi) * .5f / sqrt(*b0) + 1e-12f;

/* *****COMPUTE L FROM B AND I.  SAME AS CARMEL IN INVAR. */

/* -- Correct dipole moment is used here. D. Bilitza, Nov 87. */

    dimob0 = *dimo / *b0;
    arg1 = log(fi);
    arg2 = log(dimob0);
/* 	arg = FI*FI*FI/DIMOB0 */
/* 	if(abs(arg).gt.88.0) arg=88.0 */
    xx = arg1 * 3 - arg2;
    if (xx > 23.f) {
	goto L776;
    }
    if (xx > 11.7f) {
	goto L775;
    }
    if (xx > 3.f) {
	goto L774;
    }
    if (xx > -3.f) {
	goto L773;
    }
    if (xx > -22.f) {
	goto L772;
    }
/* L771: */
    gg = xx * .333338f + .30062102f;
    goto L777;
L772:
    gg = ((((((((xx * -8.1537735e-14f + 8.3232531e-13f) * xx + 1.0066362e-9f) 
	    * xx + 8.1048663e-8f) * xx + 3.2916354e-6f) * xx + 8.2711096e-5f) 
	    * xx + .0013714667f) * xx + .015017245f) * xx + .43432642f) * xx 
	    + .62337691f;
    goto L777;
L773:
    gg = ((((((((xx * 2.6047023e-10f + 2.3028767e-9f) * xx - 2.1997983e-8f) * 
	    xx - 5.3977642e-7f) * xx - 3.3408822e-6f) * xx + 3.8379917e-5f) * 
	    xx + .0011784234f) * xx + .014492441f) * xx + .43352788f) * xx + 
	    .6228644f;
    goto L777;
L774:
    gg = ((((((((xx * 6.3271665e-10f - 3.958306e-8f) * xx + 9.9766148e-7f) * 
	    xx - 1.2531932e-5f) * xx + 7.9451313e-5f) * xx - 3.2077032e-4f) * 
	    xx + .0021680398f) * xx + .012817956f) * xx + .43510529f) * xx + 
	    .6222355f;
    goto L777;
L775:
    gg = (((((xx * 2.8212095e-8f - 3.8049276e-6f) * xx + 2.170224e-4f) * xx - 
	    .0067310339f) * xx + .12038224f) * xx - .18461796f) * xx + 
	    2.0007187f;
    goto L777;
L776:
    gg = xx - 3.0460681f;
L777:
    *fl = exp(log((exp(gg) + 1.f) * dimob0) / 3.f);
    return 0;
/* *****APPROXIMATION FOR HIGH VALUES OF L. */
L30:
    *icode = 3;
    t = -p[(n - 1 << 3) - 6] / step;
    *fl = 1.f / ((r__1 = ((c3 * t + c2) * t + c1) * t + c0, dabs(r__1)) + 
	    1e-15f);
    return 0;
} /* shellg_ */

/* Subroutine */ int shellg_(real *glat, real *glon, real *alt, real *dimo, 
	real *fl, integer *icode, real *b0)
{
    return shellg_0_(0, glat, glon, alt, dimo, fl, icode, b0, (real *)0);
    }

/* Subroutine */ int shellc_(real *v, real *fl, real *b0)
{
    return shellg_0_(1, (real *)0, (real *)0, (real *)0, (real *)0, fl, (
	    integer *)0, b0, v);
    }



/* Subroutine */ int stoer_(real *p, real *bq, real *r__)
{
    /* Initialized data */

    static real u[9]	/* was [3][3] */ = { .3511737f,-.9148385f,-.1993679f,
	    .9335804f,.358368f,0.f,.0714471f,-.186126f,.9799247f };

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static real q, dr, dx, dy, dz, rq, xm, ym, zm, wr, fli, dsq, dxm, dym, 
	    dzm;
    extern /* Subroutine */ int feldi_(void);

/* ******************************************************************* */
/* * SUBROUTINE USED FOR FIELD LINE TRACING IN SHELLG                * */
/* * CALLS ENTRY POINT FELDI IN GEOMAGNETIC FIELD SUBROUTINE FELDG   * */

/* 09/07/22 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* ******************************************************************* */
/* *****XM,YM,ZM  ARE GEOMAGNETIC CARTESIAN INVERSE CO-ORDINATES */
    /* Parameter adjustments */
    --p;

    /* Function Body */
    zm = p[3];
    fli = p[1] * p[1] + p[2] * p[2] + 1e-15f;
/* Computing 2nd power */
    r__1 = zm + zm;
    *r__ = (fli + sqrt(fli * fli + r__1 * r__1)) * .5f;
    rq = *r__ * *r__;
    wr = sqrt(*r__);
    xm = p[1] * wr;
    ym = p[2] * wr;
/* *****TRANSFORM TO GEOGRAPHIC CO-ORDINATE SYSTEM */
    igrf2_2.xi[0] = xm * u[0] + ym * u[3] + zm * u[6];
    igrf2_2.xi[1] = xm * u[1] + ym * u[4] + zm * u[7];
    igrf2_2.xi[2] = xm * u[2] + zm * u[8];
/* *****COMPUTE DERIVATIVES */
/*      CALL FELDI(XI,H) */
    feldi_();
    q = igrf2_2.h__[0] / rq;
    dx = igrf2_2.h__[2] + igrf2_2.h__[2] + q * igrf2_2.xi[0];
    dy = igrf2_2.h__[3] + igrf2_2.h__[3] + q * igrf2_2.xi[1];
    dz = igrf2_2.h__[1] + igrf2_2.h__[1] + q * igrf2_2.xi[2];
/* *****TRANSFORM BACK TO GEOMAGNETIC CO-ORDINATE SYSTEM */
    dxm = u[0] * dx + u[1] * dy + u[2] * dz;
    dym = u[3] * dx + u[4] * dy;
    dzm = u[6] * dx + u[7] * dy + u[8] * dz;
    dr = (xm * dxm + ym * dym + zm * dzm) / *r__;
/* *****FORM SLOWLY VARYING EXPRESSIONS */
    p[4] = (wr * dxm - p[1] * .5f * dr) / (*r__ * dzm);
    p[5] = (wr * dym - p[2] * .5f * dr) / (*r__ * dzm);
    dsq = rq * (dxm * dxm + dym * dym + dzm * dzm);
    *bq = dsq * rq * rq;
    p[6] = sqrt(dsq / (rq + zm * 3.f * zm));
    p[7] = p[6] * (rq + zm * zm) / (rq * dzm);
    return 0;
} /* stoer_ */



/* Subroutine */ int feldg_0_(int n__, real *glat, real *glon, real *alt, 
	real *bnorth, real *beast, real *bdown, real *babs, real *v, real *b)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), sqrt(doublereal);

    /* Local variables */
    static real d__, f;
    static integer i__, k, m;
    static real s, t, x, y, z__;
    static integer ih;
    static real cp;
    static integer il;
    static real ct;
    static integer is;
    static real sp, rq, st, rho, xxx, yyy, zzz, brho;
    static integer imax;
    static real rlat;
    static integer last;
    static real rlon, bxxx, byyy, bzzz;
    static integer ihmax;

/* ------------------------------------------------------------------- */
/* CALCULATES EARTH MAGNETIC FIELD FROM SPHERICAL HARMONICS MODEL */
/* REF: G. KLUGE, EUROPEAN SPACE OPERATIONS CENTRE, INTERNAL NOTE 61, */
/*      1970. */
/* -------------------------------------------------------------------- */
/* CHANGES (D. BILITZA, NOV 87): */
/*   - FIELD COEFFICIENTS IN BINARY DATA FILES INSTEAD OF BLOCK DATA */
/*   - CALCULATES DIPOL MOMENT */
/* 09/07/22 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* -------------------------------------------------------------------- */
/*  INPUT:  ENTRY POINT FELDG */
/*               GLAT  GEODETIC LATITUDE IN DEGREES (NORTH) */
/*               GLON  GEODETIC LONGITUDE IN DEGREES (EAST) */
/*               ALT   ALTITUDE IN KM ABOVE SEA LEVEL */

/*          ENTRY POINT FELDC */
/*               V(3)  CARTESIAN COORDINATES IN EARTH RADII (6371.2 KM) */
/*                       X-AXIS POINTING TO EQUATOR AT 0 LONGITUDE */
/*                       Y-AXIS POINTING TO EQUATOR AT 90 LONG. */
/*                       Z-AXIS POINTING TO NORTH POLE */

/*          COMMON BLANK AND ENTRY POINT FELDI ARE NEEDED WHEN USED */
/*            IN CONNECTION WITH L-CALCULATION PROGRAM SHELLG. */

/*          COMMON /MODEL/ AND /GENER/ */
/*               UMR     = ATAN(1.0)*4./180.   <DEGREE>*UMR=<RADIANT> */
/*               ERA     EARTH RADIUS FOR NORMALIZATION OF CARTESIAN */
/*                       COORDINATES (6371.2 KM) */
/*               AQUAD, BQUAD   SQUARE OF MAJOR AND MINOR HALF AXIS FOR */
/*                       EARTH ELLIPSOID AS RECOMMENDED BY INTERNATIONAL */
/*                       ASTRONOMICAL UNION (6378.160, 6356.775 KM). */
/*               NMAX    MAXIMUM ORDER OF SPHERICAL HARMONICS */
/*               TIME    YEAR (DECIMAL: 1973.5) FOR WHICH MAGNETIC */
/*                       FIELD IS TO BE CALCULATED */
/*               G(M)    NORMALIZED FIELD COEFFICIENTS (SEE FELDCOF) */
/*                       M=NMAX*(NMAX+2) */
/* ------------------------------------------------------------------------ */
/*  OUTPUT: BABS   MAGNETIC FIELD STRENGTH IN GAUSS */
/*          BNORTH, BEAST, BDOWN   COMPONENTS OF THE FIELD WITH RESPECT */
/*                 TO THE LOCAL GEODETIC COORDINATE SYSTEM, WITH AXIS */
/*                 POINTING IN THE TANGENTIAL PLANE TO THE NORTH, EAST */
/*                 AND DOWNWARD. */
/* ----------------------------------------------------------------------- */

/* -- IS RECORDS ENTRY POINT */

/* *****ENTRY POINT  FELDG  TO BE USED WITH GEODETIC CO-ORDINATES */
    /* Parameter adjustments */
    if (v) {
	--v;
	}
    if (b) {
	--b;
	}

    /* Function Body */
    switch(n__) {
	case 1: goto L_feldc;
	case 2: goto L_feldi;
	}

    is = 1;
    rlat = *glat * gener_1.umr;
    ct = sin(rlat);
    st = cos(rlat);
    d__ = sqrt(gener_1.aquad - (gener_1.aquad - gener_1.bquad) * ct * ct);
    rlon = *glon * gener_1.umr;
    cp = cos(rlon);
    sp = sin(rlon);
    zzz = (*alt + gener_1.bquad / d__) * ct / gener_1.era;
    rho = (*alt + gener_1.aquad / d__) * st / gener_1.era;
    xxx = rho * cp;
    yyy = rho * sp;
    goto L10;

L_feldc:
/* *****ENTRY POINT  FELDC  TO BE USED WITH CARTESIAN CO-ORDINATES */
    is = 2;
    xxx = v[1];
    yyy = v[2];
    zzz = v[3];
L10:
    rq = 1.f / (xxx * xxx + yyy * yyy + zzz * zzz);
    igrf2_2.xi[0] = xxx * rq;
    igrf2_2.xi[1] = yyy * rq;
    igrf2_2.xi[2] = zzz * rq;
    goto L20;

L_feldi:
/* *****ENTRY POINT  FELDI  USED FOR L COMPUTATION */
    is = 3;
L20:
    ihmax = model_1.nmax * model_1.nmax + 1;
    last = ihmax + model_1.nmax + model_1.nmax;
    imax = model_1.nmax + model_1.nmax - 1;
    i__1 = last;
    for (i__ = ihmax; i__ <= i__1; ++i__) {
/* L8: */
	igrf2_2.h__[i__ - 1] = model_1.g[i__ - 1];
    }
    for (k = 1; k <= 3; k += 2) {
	i__ = imax;
	ih = ihmax;
L1:
	il = ih - i__;
	f = 2.f / (real) (i__ - k + 2);
	x = igrf2_2.xi[0] * f;
	y = igrf2_2.xi[1] * f;
	z__ = igrf2_2.xi[2] * (f + f);
	i__ += -2;
	if ((i__1 = i__ - 1) < 0) {
	    goto L5;
	} else if (i__1 == 0) {
	    goto L4;
	} else {
	    goto L2;
	}
L2:
	i__1 = i__;
	for (m = 3; m <= i__1; m += 2) {
	    igrf2_2.h__[il + m] = model_1.g[il + m] + z__ * igrf2_2.h__[ih + 
		    m] + x * (igrf2_2.h__[ih + m + 2] - igrf2_2.h__[ih + m - 
		    2]) - y * (igrf2_2.h__[ih + m + 1] + igrf2_2.h__[ih + m - 
		    3]);
/* L3: */
	    igrf2_2.h__[il + m - 1] = model_1.g[il + m - 1] + z__ * 
		    igrf2_2.h__[ih + m - 1] + x * (igrf2_2.h__[ih + m + 1] - 
		    igrf2_2.h__[ih + m - 3]) + y * (igrf2_2.h__[ih + m + 2] + 
		    igrf2_2.h__[ih + m - 2]);
	}
L4:
	igrf2_2.h__[il + 1] = model_1.g[il + 1] + z__ * igrf2_2.h__[ih + 1] + 
		x * igrf2_2.h__[ih + 3] - y * (igrf2_2.h__[ih + 2] + 
		igrf2_2.h__[ih - 1]);
	igrf2_2.h__[il] = model_1.g[il] + z__ * igrf2_2.h__[ih] + y * 
		igrf2_2.h__[ih + 3] + x * (igrf2_2.h__[ih + 2] - igrf2_2.h__[
		ih - 1]);
L5:
	igrf2_2.h__[il - 1] = model_1.g[il - 1] + z__ * igrf2_2.h__[ih - 1] + 
		(x * igrf2_2.h__[ih] + y * igrf2_2.h__[ih + 1]) * 2.f;
	ih = il;
	if (i__ >= k) {
	    goto L1;
	}
/* L6: */
    }
    if (is == 3) {
	return 0;
    }
    s = igrf2_2.h__[0] * .5f + (igrf2_2.h__[1] * igrf2_2.xi[2] + igrf2_2.h__[
	    2] * igrf2_2.xi[0] + igrf2_2.h__[3] * igrf2_2.xi[1]) * 2.f;
    t = (rq + rq) * sqrt(rq);
    bxxx = t * (igrf2_2.h__[2] - s * xxx);
    byyy = t * (igrf2_2.h__[3] - s * yyy);
    bzzz = t * (igrf2_2.h__[1] - s * zzz);
    if (is == 2) {
	goto L7;
    }
    *babs = sqrt(bxxx * bxxx + byyy * byyy + bzzz * bzzz);
    *beast = byyy * cp - bxxx * sp;
    brho = byyy * sp + bxxx * cp;
    *bnorth = bzzz * st - brho * ct;
    *bdown = -bzzz * ct - brho * st;
    return 0;
L7:
    b[1] = bxxx;
    b[2] = byyy;
    b[3] = bzzz;
    return 0;
} /* feldg_ */

/* Subroutine */ int feldg_(real *glat, real *glon, real *alt, real *bnorth, 
	real *beast, real *bdown, real *babs)
{
    return feldg_0_(0, glat, glon, alt, bnorth, beast, bdown, babs, (real *)0,
	     (real *)0);
    }

/* Subroutine */ int feldc_(real *v, real *b)
{
    return feldg_0_(1, (real *)0, (real *)0, (real *)0, (real *)0, (real *)0, 
	    (real *)0, (real *)0, v, b);
    }

/* Subroutine */ int feldi_(void)
{
    return feldg_0_(2, (real *)0, (real *)0, (real *)0, (real *)0, (real *)0, 
	    (real *)0, (real *)0, (real *)0, (real *)0);
    }



/* Subroutine */ int feldcof_(real *year, real *dimo)
{
    /* Initialized data */

    static char filmod[13*24] = "igrf1900.dat " "igrf1905.dat " "igrf1910.da"
	    "t " "igrf1915.dat " "igrf1920.dat " "igrf1925.dat " "igrf1930.da"
	    "t " "igrf1935.dat " "igrf1940.dat " "dgrf1945.dat " "dgrf1950.da"
	    "t " "dgrf1955.dat " "dgrf1960.dat " "dgrf1965.dat " "dgrf1970.da"
	    "t " "dgrf1975.dat " "dgrf1980.dat " "dgrf1985.dat " "dgrf1990.da"
	    "t " "dgrf1995.dat " "dgrf2000.dat " "dgrf2005.dat " "igrf2010.da"
	    "t " "igrf2010s.dat";
    static real dtemod[24] = { 1900.f,1905.f,1910.f,1915.f,1920.f,1925.f,
	    1930.f,1935.f,1940.f,1945.f,1950.f,1955.f,1960.f,1965.f,1970.f,
	    1975.f,1980.f,1985.f,1990.f,1995.f,2e3f,2005.f,2010.f,2015.f };

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen), s_stop(char *
	    , ftnlen);
    double sqrt(doublereal);

    /* Local variables */
    extern /* Subroutine */ int intershc_(real *, real *, integer *, real *, 
	    real *, integer *, real *, integer *, real *), extrashc_(real *, 
	    real *, integer *, real *, integer *, real *, integer *, real *);
    static doublereal f;
    static integer i__, j, l, m, n;
    static doublereal x, f0;
    static integer is, iu;
    static real gh2[196], gha[196];
    static integer ier;
    static char fil2[13];
    static real dte1, dte2;
    static integer iyea, nmax1, nmax2;
    static real sqrt2;
    static integer numye, istye;
    extern /* Subroutine */ int getshc_(integer *, char *, integer *, real *, 
	    real *, integer *, ftnlen);

/* ------------------------------------------------------------------------ */
/*  DETERMINES COEFFICIENTS AND DIPOL MOMENT FROM IGRF MODELS */

/*       INPUT:  YEAR    DECIMAL YEAR FOR WHICH GEOMAGNETIC FIELD IS TO */
/*                       BE CALCULATED */
/*       OUTPUT: DIMO    GEOMAGNETIC DIPOL MOMENT IN GAUSS (NORMALIZED */
/*                       TO EARTH'S RADIUS) AT THE TIME (YEAR) */
/*  D. BILITZA, NSSDC, GSFC, CODE 633, GREENBELT, MD 20771, */
/*       (301)286-9536   NOV 1987. */
/* 05/31/2000 updated to IGRF-2000 version (###) */
/* 03/24/2000 updated to IGRF-2005 version (###) */
/* 07/22/2009 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* 02/26/2010 updated to IGRF-2010 version (###) */
/* ----------------------------------------------------------------------- */
/* ### FILMOD, DTEMOD array-size is number of IGRF maps */
/* ### updated coefficient file names and corresponding years */

/* ### numye is number of IGRF coefficient files minus 1 */
/* ### istye is start year of IGRF coefficient files */

    numye = 23;
    istye = 1900;

/*  IS=0 FOR SCHMIDT NORMALIZATION   IS=1 GAUSS NORMALIZATION */
/*  IU  IS INPUT UNIT NUMBER FOR IGRF COEFFICIENT SETS */

    iu = 10;
    is = 0;
/* -- DETERMINE IGRF-YEARS FOR INPUT-YEAR */
    model_2.time = *year;
    iyea = (integer) (*year / 5.f) * 5;
    l = (iyea - istye) / 5 + 1;
    if (l < 1) {
	l = 1;
    }
    if (l > numye) {
	l = numye;
    }
    dte1 = dtemod[l - 1];
    s_copy(model_2.fil1, filmod + (l - 1) * 13, (ftnlen)13, (ftnlen)13);
    dte2 = dtemod[l];
    s_copy(fil2, filmod + l * 13, (ftnlen)13, (ftnlen)13);
/* -- GET IGRF COEFFICIENTS FOR THE BOUNDARY YEARS */
    getshc_(&iu, model_2.fil1, &nmax1, &gener_2.erad, model_2.gh1, &ier, (
	    ftnlen)13);
    if (ier != 0) {
	s_stop("", (ftnlen)0);
    }
    getshc_(&iu, fil2, &nmax2, &gener_2.erad, gh2, &ier, (ftnlen)13);
    if (ier != 0) {
	s_stop("", (ftnlen)0);
    }
/* -- DETERMINE IGRF COEFFICIENTS FOR YEAR */
    if (l <= numye - 1) {
	intershc_(year, &dte1, &nmax1, model_2.gh1, &dte2, &nmax2, gh2, &
		model_2.nmax, gha);
    } else {
	extrashc_(year, &dte1, &nmax1, model_2.gh1, &nmax2, gh2, &
		model_2.nmax, gha);
    }
/* -- DETERMINE MAGNETIC DIPOL MOMENT AND COEFFIECIENTS G */
    f0 = 0.;
    for (j = 1; j <= 3; ++j) {
	f = gha[j - 1] * 1e-5;
	f0 += f * f;
/* L1234: */
    }
    *dimo = sqrt(f0);
    model_2.gh1[0] = 0.f;
    i__ = 2;
    f0 = 1e-5;
    if (is == 0) {
	f0 = -f0;
    }
    sqrt2 = sqrt(2.f);
    i__1 = model_2.nmax;
    for (n = 1; n <= i__1; ++n) {
	x = (doublereal) n;
	f0 = f0 * x * x / (x * 4. - 2.);
	if (is == 0) {
	    f0 = f0 * (x * 2. - 1.) / x;
	}
	f = f0 * .5;
	if (is == 0) {
	    f *= sqrt2;
	}
	model_2.gh1[i__ - 1] = gha[i__ - 2] * f0;
	++i__;
	i__2 = n;
	for (m = 1; m <= i__2; ++m) {
	    f = f * (x + m) / (x - m + 1.);
	    if (is == 0) {
		f *= sqrt((x - m + 1.) / (x + m));
	    }
	    model_2.gh1[i__ - 1] = gha[i__ - 2] * f;
	    model_2.gh1[i__] = gha[i__ - 1] * f;
	    i__ += 2;
/* L9: */
	}
    }
    return 0;
} /* feldcof_ */



/* Subroutine */ int getshc_(integer *iu, char *fspec, integer *nmax, real *
	erad, real *gh, integer *ier, ftnlen fspec_len)
{
    /* Format strings */
    static char fmt_667[] = "(a13)";
    static char fmt_100[] = "(\002Error while reading \002,a13)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    , f_open(olist *), s_rsle(cilist *), e_rsle(void), do_lio(integer 
	    *, integer *, char *, ftnlen), s_wsfe(cilist *), e_wsfe(void), 
	    f_clos(cllist *);

    /* Local variables */
    static integer i__, j, nm;
    static char fout[80];
    static real xmyear;
    static integer monito;

    /* Fortran I/O blocks */
    static icilist io___157 = { 0, fout, 0, fmt_667, 80, 1 };
    static cilist io___158 = { 1, 0, 1, 0, 0 };
    static cilist io___159 = { 1, 0, 1, 0, 0 };
    static cilist io___162 = { 1, 0, 1, 0, 0 };
    static cilist io___165 = { 0, 0, 0, fmt_100, 0 };


/* =============================================================== */
/*       Reads spherical harmonic coefficients from the specified */
/*       file into an array. */
/*       Input: */
/*           IU    - Logical unit number */
/*           FSPEC - File specification */
/*       Output: */
/*           NMAX  - Maximum degree and order of model */
/*           ERAD  - Earth's radius associated with the spherical */
/*                   harmonic coefficients, in the same units as */
/*                   elevation */
/*           GH    - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients */
/*           IER   - Error number: =  0, no error */
/*                                 = -2, records out of order */
/*                                 = FORTRAN run-time error number */
/* =============================================================== */
    /* Parameter adjustments */
    --gh;

    /* Function Body */
    for (j = 1; j <= 196; ++j) {
/* L1: */
	gh[j] = 0.f;
    }
/* --------------------------------------------------------------- */
/*       Open coefficient file. Read past first header record. */
/*       Read degree and order of model and Earth's radius. */
/* --------------------------------------------------------------- */
    s_wsfi(&io___157);
    do_fio(&c__1, fspec, fspec_len);
    e_wsfi();
/* 667    FORMAT('/var/www/omniweb/cgi/vitmo/IRI/',A13) */
    o__1.oerr = 1;
    o__1.ounit = *iu;
    o__1.ofnmlen = 80;
    extern char *trimwhitespace(char *str); char prefix_dp[28] = "/usr/local/lib/igrf/"; strcat(prefix_dp, fspec); o__1.ofnm = trimwhitespace(prefix_dp);
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    *ier = f_open(&o__1);
    if (*ier != 0) {
	goto L999;
    }
    io___158.ciunit = *iu;
    *ier = s_rsle(&io___158);
    if (*ier != 0) {
	goto L100001;
    }
    *ier = e_rsle();
L100001:
    if (*ier > 0) {
	goto L999;
    }
    io___159.ciunit = *iu;
    *ier = s_rsle(&io___159);
    if (*ier != 0) {
	goto L100002;
    }
    *ier = do_lio(&c__3, &c__1, (char *)&(*nmax), (ftnlen)sizeof(integer));
    if (*ier != 0) {
	goto L100002;
    }
    *ier = do_lio(&c__4, &c__1, (char *)&(*erad), (ftnlen)sizeof(real));
    if (*ier != 0) {
	goto L100002;
    }
    *ier = do_lio(&c__4, &c__1, (char *)&xmyear, (ftnlen)sizeof(real));
    if (*ier != 0) {
	goto L100002;
    }
    *ier = e_rsle();
L100002:
    if (*ier > 0) {
	goto L999;
    }
    nm = *nmax * (*nmax + 2);
    io___162.ciunit = *iu;
    *ier = s_rsle(&io___162);
    if (*ier != 0) {
	goto L100003;
    }
    i__1 = nm;
    for (i__ = 1; i__ <= i__1; ++i__) {
	*ier = do_lio(&c__4, &c__1, (char *)&gh[i__], (ftnlen)sizeof(real));
	if (*ier != 0) {
	    goto L100003;
	}
    }
    *ier = e_rsle();
L100003:
    if (*ier > 0) {
	goto L999;
    }
    goto L888;
L999:
    io___165.ciunit = monito;
    s_wsfe(&io___165);
    do_fio(&c__1, fout, (ftnlen)80);
    e_wsfe();
L888:
    cl__1.cerr = 0;
    cl__1.cunit = *iu;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* getshc_ */



/* Subroutine */ int intershc_(real *date, real *dte1, integer *nmax1, real *
	gh1, real *dte2, integer *nmax2, real *gh2, integer *nmax, real *gh)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static real factor;

/* =============================================================== */

/*       Version 1.01 */

/*       Interpolates linearly, in time, between two spherical */
/*       harmonic models. */

/*       Input: */
/*           DATE  - Date of resulting model (in decimal year) */
/*           DTE1  - Date of earlier model */
/*           NMAX1 - Maximum degree and order of earlier model */
/*           GH1   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of earlier model */
/*           DTE2  - Date of later model */
/*           NMAX2 - Maximum degree and order of later model */
/*           GH2   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of later model */

/*       Output: */
/*           GH    - Coefficients of resulting model */
/*           NMAX  - Maximum degree and order of resulting model */

/*       A. Zunde */
/*       USGS, MS 964, Box 25046 Federal Center, Denver, CO  80225 */

/* =============================================================== */
/* --------------------------------------------------------------- */
/*       The coefficients (GH) of the resulting model, at date */
/*       DATE, are computed by linearly interpolating between the */
/*       coefficients of the earlier model (GH1), at date DTE1, */
/*       and those of the later model (GH2), at date DTE2. If one */
/*       model is smaller than the other, the interpolation is */
/*       performed with the missing coefficients assumed to be 0. */
/* --------------------------------------------------------------- */
    /* Parameter adjustments */
    --gh;
    --gh2;
    --gh1;

    /* Function Body */
    factor = (*date - *dte1) / (*dte2 - *dte1);
    if (*nmax1 == *nmax2) {
	k = *nmax1 * (*nmax1 + 2);
	*nmax = *nmax1;
    } else if (*nmax1 > *nmax2) {
	k = *nmax2 * (*nmax2 + 2);
	l = *nmax1 * (*nmax1 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1122: */
	    gh[i__] = gh1[i__] + factor * (-gh1[i__]);
	}
	*nmax = *nmax1;
    } else {
	k = *nmax1 * (*nmax1 + 2);
	l = *nmax2 * (*nmax2 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1133: */
	    gh[i__] = factor * gh2[i__];
	}
	*nmax = *nmax2;
    }
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L1144: */
	gh[i__] = gh1[i__] + factor * (gh2[i__] - gh1[i__]);
    }
    return 0;
} /* intershc_ */



/* Subroutine */ int extrashc_(real *date, real *dte1, integer *nmax1, real *
	gh1, integer *nmax2, real *gh2, integer *nmax, real *gh)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static real factor;

/* =============================================================== */

/*       Version 1.01 */

/*       Extrapolates linearly a spherical harmonic model with a */
/*       rate-of-change model. */

/*       Input: */
/*           DATE  - Date of resulting model (in decimal year) */
/*           DTE1  - Date of base model */
/*           NMAX1 - Maximum degree and order of base model */
/*           GH1   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of base model */
/*           NMAX2 - Maximum degree and order of rate-of-change */
/*                   model */
/*           GH2   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of rate-of-change model */

/*       Output: */
/*           GH    - Coefficients of resulting model */
/*           NMAX  - Maximum degree and order of resulting model */

/*       A. Zunde */
/*       USGS, MS 964, Box 25046 Federal Center, Denver, CO  80225 */

/* =============================================================== */
/* --------------------------------------------------------------- */
/*       The coefficients (GH) of the resulting model, at date */
/*       DATE, are computed by linearly extrapolating the coef- */
/*       ficients of the base model (GH1), at date DTE1, using */
/*       those of the rate-of-change model (GH2), at date DTE2. If */
/*       one model is smaller than the other, the extrapolation is */
/*       performed with the missing coefficients assumed to be 0. */
/* --------------------------------------------------------------- */
    /* Parameter adjustments */
    --gh;
    --gh2;
    --gh1;

    /* Function Body */
    factor = *date - *dte1;
    if (*nmax1 == *nmax2) {
	k = *nmax1 * (*nmax1 + 2);
	*nmax = *nmax1;
    } else if (*nmax1 > *nmax2) {
	k = *nmax2 * (*nmax2 + 2);
	l = *nmax1 * (*nmax1 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1155: */
	    gh[i__] = gh1[i__];
	}
	*nmax = *nmax1;
    } else {
	k = *nmax1 * (*nmax1 + 2);
	l = *nmax2 * (*nmax2 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1166: */
	    gh[i__] = factor * gh2[i__];
	}
	*nmax = *nmax2;
    }
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L1177: */
	gh[i__] = gh1[i__] + factor * gh2[i__];
    }
    return 0;
} /* extrashc_ */



/* Subroutine */ int initize_(void)
{
    /* Builtin functions */
    double atan(doublereal);

    /* Local variables */
    static real erequ, erpol;

/* ---------------------------------------------------------------- */
/* Initializes the parameters in COMMON/GENER/ */

/*       UMR     = ATAN(1.0)*4./180.   <DEGREE>*UMR=<RADIANT> */
/*       ERA     EARTH RADIUS FOR NORMALIZATION OF CARTESIAN */
/*                       COORDINATES (6371.2 KM) */
/*       EREQU   MAJOR HALF AXIS FOR EARTH ELLIPSOID (6378.160 KM) */
/*       ERPOL   MINOR HALF AXIS FOR EARTH ELLIPSOID (6356.775 KM) */
/*       AQUAD   SQUARE OF MAJOR HALF AXIS FOR EARTH ELLIPSOID */
/*       BQUAD   SQUARE OF MINOR HALF AXIS FOR EARTH ELLIPSOID */

/* ERA, EREQU and ERPOL as recommended by the INTERNATIONAL */
/* ASTRONOMICAL UNION . */
/* ----------------------------------------------------------------- */
    gener_1.era = 6371.2f;
    erequ = 6378.16f;
    erpol = 6356.775f;
    gener_1.aquad = erequ * erequ;
    gener_1.bquad = erpol * erpol;
    gener_1.umr = atan(1.f) * 4.f / 180.f;
    return 0;
} /* initize_ */

