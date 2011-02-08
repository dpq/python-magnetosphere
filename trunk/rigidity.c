/* rigidity.F -- translated by f2c (version 20050501).
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

struct {
    real rez, pi, st;
} const_;

#define const_1 const_

struct {
    real h1, h2, ain, fip, alon, bday;
} start_;

#define start_1 start_

/* Table of constant values */

static doublereal c_b3 = 10.;
static real c_b7 = 360.f;

/*       This program calculates the function of */
/*       cosmic ray penetration into the Earth's magnetosphere */
/*         Epoch 2010.0 */

/* 24.10.2010 edition */
/* Main program */ int MAIN__(void)
{
    /* Initialized data */

    static real rez1 = 6371.f;
    static real pi1 = 3.141593f;
    static real st1 = 57.296f;

    /* System generated locals */
    integer i__1;
    real r__1;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static real h__;
    static integer i__, j, l;
    static real x, y, re[75], rf0, r450, trl[300]	/* was [4][75] */;
    static integer ntr;

    extern /* Subroutine */ int rigrf_(real *, real *, real *);

/*        REZ - Earth radius */
    const_1.rez = rez1;
    const_1.pi = pi1;
    const_1.st = st1;

    for (j = 1; j <= 75; ++j) {
	for (l = 1; l <= 4; ++l) {
	    trl[l + (j << 2) - 5] = 0.f;
/* L1400: */
	}
    }
/*     Rigidity scales */
/* ========================= */
    ntr = 51;
    i__1 = ntr;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__1 = (doublereal) (((real) i__ - 21.f) / 20.f);
	re[i__ - 1] = pow_dd(&c_b3, &d__1);
/* L10: */
    }
/* ============================================= */
    rigrf_(&x, &y, &r450);

/* Computing 2nd power */
    r__1 = (const_1.rez + 450.f) / (const_1.rez + h__);
    rf0 = r450 * (r__1 * r__1);
    if (rf0 <= .001f) {
	rf0 = .001f;
    }
/* ============================================= */
/* Commented out to run the initialization procedure
   when importing Python module */
    // s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

/* Subroutine */ int rigrf_(real *clon, real *clat, real *r450)
{
    /* Builtin functions */
    double r_mod(real *, real *), exp(doublereal);

    /* Local variables */
    static integer j, k;
    static real d0, s0, bd[4], ck, bs[4];
    static integer ng, kl, nl;
    static real cx, rk[4];
    static integer ns;
    static real wb1[4], wb2[4], wb3[4], wb4[4], ass;
    static logical kex;
    static real sln, azz, stab[560]	/* was [14][40] */;
    extern /* Subroutine */ int gentab_(real *);


/* 	Lagrange interpolation - 4 points  */

/*        Input parameters */

/*     CLON - longitude (degrees) */
/*     CLAT - latitude (degrees) */


/*       Output parameter */

/*     R450 - Cutoff rigidity (in GeV) */


/*          24.08.2010 edition */


/*      LOGICAL KEX/.FALSE./ */
    kex = FALSE_;
    if (kex) {
	goto L10;
    }
    kex = TRUE_;
    gentab_(stab);
L10:
    sln = r_mod(clon, &c_b7);
    if (sln >= 30.f) {
	goto L20;
    }
    sln += 360.f;
    ng = 13;
    goto L30;
L20:
    ng = (integer) sln / 30 + 1;
/*   Longitude index */
L30:
    ns = (integer) (*clat + 90.f) / 5 + 1;
/*   Latitude index */
    if (ns <= 2) {
	ns = 2;
    }
    if (ns >= 36) {
	ns = 36;
    }
/* ============================== */
    nl = ng - 2;
    s0 = ns * 5.f - 100.f;
/*   Latitude */
    if (s0 >= 75.f) {
	s0 = 75.f;
    }
    d0 = nl * 30.f;
/*   Longitude */
    for (j = 1; j <= 4; ++j) {
	kl = j + nl;
/*   Longitude index */
	wb1[j - 1] = stab[kl + (ns - 1) * 14 - 15];
	wb2[j - 1] = stab[kl + ns * 14 - 15];
	wb3[j - 1] = stab[kl + (ns + 1) * 14 - 15];
	wb4[j - 1] = stab[kl + (ns + 2) * 14 - 15];
	rk[j - 1] = 0.f;
	bd[j - 1] = d0;
/*   Longitude */
	bs[j - 1] = s0;
/*   Latitude */
	d0 += 30.f;
	s0 += 5.f;
/* L50: */
    }
/* 	Interpolation by longitude */
    for (j = 1; j <= 4; ++j) {
	cx = bd[j - 1];
	ass = 1.f;
	for (k = 1; k <= 4; ++k) {
	    ck = bd[k - 1];
	    if (j == k) {
		goto L60;
	    }
	    ass = ass * (sln - ck) / (cx - ck);
L60:
	    ;
	}
	rk[0] += ass * wb1[j - 1];
	rk[1] += ass * wb2[j - 1];
	rk[2] += ass * wb3[j - 1];
	rk[3] += ass * wb4[j - 1];
/* L70: */
    }
/* 	Interpolation by latitude */

    azz = 0.f;
    for (j = 1; j <= 4; ++j) {
	cx = bs[j - 1];
	ass = 1.f;
	for (k = 1; k <= 4; ++k) {
	    ck = bs[k - 1];
	    if (j == k) {
		goto L80;
	    }
	    ass = ass * (*clat - ck) / (cx - ck);
L80:
	    ;
	}
	azz += ass * rk[j - 1];
/* L90: */
    }
    *r450 = exp(azz);
    return 0;
} /* rigrf_ */

/* Subroutine */ int gentab_(real *stab)
{
    /* Initialized data */

    static real t0[48]	/* was [12][4] */ = { 1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,
	    1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,.103f,.036f,.001f,.004f,
	    .004f,.004f,.004f,.021f,.085f,.135f,.17f,.147f,.222f,.106f,.001f,
	    .004f,.004f,.004f,.004f,.062f,.217f,.337f,.378f,.331f,.403f,.199f,
	    .021f,.004f,.004f,.004f,.004f,.164f,.412f,.645f,.732f,.604f };
    static real t1[48]	/* was [12][4] */ = { .627f,.345f,.098f,.004f,.004f,
	    .007f,.045f,.322f,.742f,1.163f,1.268f,.985f,.929f,.535f,.218f,
	    .001f,.006f,.006f,.191f,.588f,1.232f,1.829f,1.941f,1.435f,1.272f,
	    .812f,.397f,.109f,.006f,.109f,.397f,1.018f,1.901f,2.795f,2.798f,
	    1.951f,1.684f,1.175f,.673f,.288f,.184f,.32f,.79f,1.649f,2.787f,
	    3.847f,3.615f,2.52f };
    static real t2[48]	/* was [12][4] */ = { 2.113f,1.623f,1.061f,.622f,
	    .521f,.724f,1.384f,2.447f,3.92f,5.312f,4.666f,3.114f,2.682f,2.22f,
	    1.663f,1.109f,.992f,1.338f,2.264f,3.589f,5.382f,7.089f,5.908f,
	    3.837f,3.414f,3.071f,2.543f,1.892f,1.756f,2.341f,3.464f,4.657f,
	    6.977f,8.087f,6.455f,4.78f,4.259f,3.952f,3.641f,3.07f,2.944f,
	    3.601f,4.778f,6.705f,8.48f,8.983f,7.464f,5.492f };
    static real t3[48]	/* was [12][4] */ = { 5.165f,5.378f,5.013f,4.617f,
	    4.485f,5.002f,6.562f,7.606f,9.988f,9.725f,8.35f,6.154f,6.343f,
	    6.867f,7.21f,6.623f,6.563f,7.219f,8.369f,9.648f,10.74f,10.278f,
	    9.174f,7.282f,7.543f,8.329f,9.053f,9.363f,9.122f,9.044f,10.269f,
	    11.3f,11.319f,10.778f,9.885f,8.328f,9.001f,9.905f,11.03f,11.461f,
	    11.132f,11.242f,11.846f,11.981f,11.721f,11.07f,10.408f,9.434f };
    static real t4[48]	/* was [12][4] */ = { 10.158f,11.139f,12.423f,13.045f,
	    12.944f,12.608f,12.586f,12.423f,11.972f,11.221f,10.829f,10.247f,
	    11.11f,12.082f,13.385f,14.087f,13.866f,13.347f,13.075f,12.663f,
	    12.052f,11.241f,11.109f,10.938f,11.881f,12.814f,14.067f,14.788f,
	    14.478f,13.786f,13.265f,12.693f,11.953f,11.039f,11.209f,11.49f,
	    12.413f,13.295f,14.448f,15.159f,14.799f,13.957f,13.245f,12.526f,
	    11.622f,10.429f,11.139f,11.821f };
    static real t5[48]	/* was [12][4] */ = { 12.684f,13.486f,14.508f,15.209f,
	    14.828f,13.896f,13.014f,12.202f,10.992f,9.467f,10.849f,11.941f,
	    12.633f,13.345f,14.247f,14.929f,14.588f,13.636f,12.613f,11.675f,
	    10.13f,7.72f,10.246f,11.761f,12.104f,12.854f,13.646f,14.318f,
	    14.077f,13.165f,12.052f,10.964f,8.995f,6.231f,8.892f,11.201f,
	    11.192f,11.743f,12.495f,13.355f,13.265f,12.483f,11.319f,9.925f,
	    7.782f,5.218f,7.211f,10.328f };
    static real t6[48]	/* was [12][4] */ = { 9.717f,10.068f,10.851f,11.503f,
	    11.953f,11.381f,9.887f,8.267f,5.713f,3.791f,5.268f,9.002f,8.228f,
	    8.349f,9.111f,9.414f,9.837f,9.585f,8.017f,6.461f,4.288f,2.933f,
	    3.899f,7.087f,5.916f,6.128f,6.492f,7.138f,7.742f,7.914f,6.522f,
	    4.698f,3.091f,2.048f,2.684f,4.687f,4.249f,4.453f,4.595f,4.994f,
	    5.429f,5.521f,4.639f,3.517f,2.025f,1.289f,1.758f,3.415f };
    static real t7[48]	/* was [12][4] */ = { 2.841f,3.08f,3.227f,3.539f,
	    3.828f,4.045f,3.458f,2.361f,1.266f,.739f,1.035f,2.071f,1.746f,
	    1.959f,2.059f,2.255f,2.48f,2.692f,2.33f,1.386f,.745f,.429f,.571f,
	    1.139f,.971f,1.179f,1.304f,1.398f,1.548f,1.672f,1.38f,.829f,.349f,
	    .171f,.259f,.603f,.476f,.653f,.726f,.794f,.871f,.932f,.741f,.4f,
	    .141f,.018f,.074f,.276f };
    static real t8[48]	/* was [12][4] */ = { .215f,.308f,.364f,.411f,.443f,
	    .458f,.343f,.165f,.004f,.004f,.004f,.077f,.039f,.106f,.15f,.174f,
	    .191f,.174f,.124f,.004f,.007f,.007f,.004f,.004f,.004f,.004f,.004f,
	    .024f,.03f,.016f,.004f,.007f,.01f,.01f,.007f,.004f,.004f,.004f,
	    .007f,.01f,.01f,.01f,.013f,.001f,.013f,.007f,.007f,.007f };
    static real t9[48]	/* was [12][4] */ = { 1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,
	    1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,
	    1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,
	    1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,
	    1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f,1e-4f };

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static integer i__, j;


/*      "IGRF" base table generation for 450km altitude */
/*                  Epoch 2010.0 */

/*     Output parameter */
/*      STAB - "IGRF" base table */

    /* Parameter adjustments */
    stab -= 15;

    /* Function Body */
/* -90. 			! -90. */
/* -80. */
/* -75. */
/* -70. */
/* -65. */
/* -60. */
/* -55. */
/* -50. */
/* -45. */
/* -40. */
/* -35. */
/* -30. */
/* -25. */
/* -20. */
/* -15. */
/* -10. */
/*  -5. */
/*   0. */
/*   5. */
/*  10. */
/*  15. */
/*  20. */
/*  30. */
/*  35. */
/*  40. */
/*  45. */
/*  50. */
/*  55. */
/*   60. */
/* 70. */
/* 90. */
    for (i__ = 1; i__ <= 12; ++i__) {
	for (j = 1; j <= 4; ++j) {
	    stab[i__ + j * 14] = t0[i__ + j * 12 - 13];
	    stab[i__ + (j + 4) * 14] = t1[i__ + j * 12 - 13];
	    stab[i__ + (j + 8) * 14] = t2[i__ + j * 12 - 13];
	    stab[i__ + (j + 12) * 14] = t3[i__ + j * 12 - 13];
	    stab[i__ + (j + 16) * 14] = t4[i__ + j * 12 - 13];
	    stab[i__ + (j + 20) * 14] = t5[i__ + j * 12 - 13];
	    stab[i__ + (j + 24) * 14] = t6[i__ + j * 12 - 13];
	    stab[i__ + (j + 28) * 14] = t7[i__ + j * 12 - 13];
	    stab[i__ + (j + 32) * 14] = t8[i__ + j * 12 - 13];
	    stab[i__ + (j + 36) * 14] = t9[i__ + j * 12 - 13];
/* L10: */
	}
    }
    for (j = 1; j <= 39; ++j) {
	for (i__ = 1; i__ <= 12; ++i__) {
/* L20: */
	    stab[i__ + j * 14] = log(stab[i__ + j * 14]);
	}
	stab[j * 14 + 13] = stab[j * 14 + 1];
	stab[j * 14 + 14] = stab[j * 14 + 2];
/* L30: */
    }
    return 0;
} /* gentab_ */

/* Subroutine */ int reper_(real *rigrf, real *vkp, real *tmlt, real *reff)
{
    /* Initialized data */

    static real pi12 = .2617994f;

    /* Builtin functions */
    double sin(doublereal), log(doublereal), exp(doublereal);

    /* Local variables */
    static real aa, ba, ab, bb, ac, bc, ax, bx, cx, hr, der, rst;


/*     13.08.2010 edition */

/*     Subprogram calculates corrected cutoff rigidity
 value */

/*     Input parameters */

/*     RIGRF - Cutoff rigidity per IGRF */
/*     VKP  - Kp index value */
/*     TMLT - local time */

/*     Output parameter */

/*     REFF - corrected cutoff rigidity */


    aa = -.037f * sin(pi12 * (*tmlt - 5.844f)) + .357f;
    ba = sin(pi12 * (*tmlt - 5.198f)) * -.237f + 6.073f;
    ax = aa * *vkp + ba;
    ab = sin(pi12 * (*tmlt - 6.448f)) * .0022f + .00177f;
    bb = sin(pi12 * (*tmlt - 6.39f)) * .0091f - .30538f;
    bx = ab * *vkp + bb;
    ac = sin(pi12 * (*tmlt + 6.082f)) * .0768f + .0769f;
    bc = sin(pi12 * (*tmlt + 5.785f)) * 2.3564f + 3.5876f;
    cx = ac * *vkp * *vkp + bc;
    hr = log(*rigrf);
    rst = exp(hr * bx);
    der = exp(ax * rst - 1.f) * .001f + 1.f;
    if (der > cx) {
	der = cx;
    }
    *reff = *rigrf / der;
    return 0;
} /* reper_ */

