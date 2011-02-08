/* igrf_sub.f -- translated by f2c (version 20050501).
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

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__4 = 4;
static doublereal c_b431 = 1.1;


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


/* Subroutine */ int dmddec_(integer *i__, integer *m, doublereal *x)
{
    static doublereal de, em;

    de = (doublereal) (*i__);
    em = (doublereal) (*m);
    if (*i__ < 0) {
	em = -em;
    }
    *x = de + em / 60.f;
    return 0;
} /* dmddec_ */


/* Subroutine */ int ddecdm_(doublereal *x, integer *i__, integer *m)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);
    integer i_dnnt(doublereal *);

    /* Local variables */
    static doublereal t, dr, sig;
    static integer isig;

    sig = d_sign(&c_b431, x);
    dr = abs(*x);
    *i__ = (integer) dr;
    t = (doublereal) (*i__);
    d__1 = (dr - t) * 60.f;
    *m = i_dnnt(&d__1);
    if (*m == 60) {
	*m = 0;
	++(*i__);
    }
    isig = (integer) sig;
    if (*i__ != 0) {
	*i__ *= isig;
    } else {
	if (*m != 0) {
	    *m *= isig;
	}
    }
    return 0;
} /* ddecdm_ */

/* Subroutine */ int igrf11syn_(integer *isv, doublereal *date, integer *
	itype, doublereal *alt, doublereal *colat, doublereal *elong, 
	doublereal *x, doublereal *y, doublereal *z__, doublereal *f)
{
    /* Initialized data */

    static struct {
	doublereal e_1[3255];
	doublereal fill_2[1];
	} equiv_23 = { -31543., -2298., 5922., -677., 2905., -1061., 924., 
		1121., 1022., -1469., -330., 1256., 3., 572., 523., 876., 
		628., 195., 660., -69., -361., -210., 134., -75., -184., 328.,
		 -210., 264., 53., 5., -33., -86., -124., -16., 3., 63., 61., 
		-9., -11., 83., -217., 2., -58., -35., 59., 36., -90., -69., 
		70., -55., -45., 0., -13., 34., -10., -41., -1., -21., 28., 
		18., -12., 6., -22., 11., 8., 8., -4., -14., -9., 7., 1., 
		-13., 2., 5., -9., 16., 5., -5., 8., -18., 8., 10., -20., 1., 
		14., -11., 5., 12., -3., 1., -2., -2., 8., 2., 10., -1., -2., 
		-1., 2., -3., -4., 2., 2., 1., -5., 2., -2., 6., 6., -4., 4., 
		0., 0., -2., 2., 4., 2., 0., 0., -6., -31464., -2298., 5909., 
		-728., 2928., -1086., 1041., 1065., 1037., -1494., -357., 
		1239., 34., 635., 480., 880., 643., 203., 653., -77., -380., 
		-201., 146., -65., -192., 328., -193., 259., 56., -1., -32., 
		-93., -125., -26., 11., 62., 60., -7., -11., 86., -221., 4., 
		-57., -32., 57., 32., -92., -67., 70., -54., -46., 0., -14., 
		33., -11., -41., 0., -20., 28., 18., -12., 6., -22., 11., 8., 
		8., -4., -15., -9., 7., 1., -13., 2., 5., -8., 16., 5., -5., 
		8., -18., 8., 10., -20., 1., 14., -11., 5., 12., -3., 1., -2.,
		 -2., 8., 2., 10., 0., -2., -1., 2., -3., -4., 2., 2., 1., 
		-5., 2., -2., 6., 6., -4., 4., 0., 0., -2., 2., 4., 2., 0., 
		0., -6., -31354., -2297., 5898., -769., 2948., -1128., 1176., 
		1e3, 1058., -1524., -389., 1223., 62., 705., 425., 884., 660.,
		 211., 644., -90., -400., -189., 160., -55., -201., 327., 
		-172., 253., 57., -9., -33., -102., -126., -38., 21., 62., 
		58., -5., -11., 89., -224., 5., -54., -29., 54., 28., -95., 
		-65., 71., -54., -47., 1., -14., 32., -12., -40., 1., -19., 
		28., 18., -13., 6., -22., 11., 8., 8., -4., -15., -9., 6., 1.,
		 -13., 2., 5., -8., 16., 5., -5., 8., -18., 8., 10., -20., 1.,
		 14., -11., 5., 12., -3., 1., -2., -2., 8., 2., 10., 0., -2., 
		-1., 2., -3., -4., 2., 2., 1., -5., 2., -2., 6., 6., -4., 4., 
		0., 0., -2., 2., 4., 2., 0., 0., -6., -31212., -2306., 5875., 
		-802., 2956., -1191., 1309., 917., 1084., -1559., -421., 
		1212., 84., 778., 360., 887., 678., 218., 631., -109., -416., 
		-173., 178., -51., -211., 327., -148., 245., 58., -16., -34., 
		-111., -126., -51., 32., 61., 57., -2., -10., 93., -228., 8., 
		-51., -26., 49., 23., -98., -62., 72., -54., -48., 2., -14., 
		31., -12., -38., 2., -18., 28., 19., -15., 6., -22., 11., 8., 
		8., -4., -15., -9., 6., 2., -13., 3., 5., -8., 16., 6., -5., 
		8., -18., 8., 10., -20., 1., 14., -11., 5., 12., -3., 1., -2.,
		 -2., 8., 2., 10., 0., -2., -1., 2., -3., -4., 2., 2., 1., 
		-5., 2., -2., 6., 6., -4., 4., 0., 0., -2., 1., 4., 2., 0., 
		0., -6., -31060., -2317., 5845., -839., 2959., -1259., 1407., 
		823., 1111., -1600., -445., 1205., 103., 839., 293., 889., 
		695., 220., 616., -134., -424., -153., 199., -57., -221., 
		326., -122., 236., 58., -23., -38., -119., -125., -62., 43., 
		61., 55., 0., -10., 96., -233., 11., -46., -22., 44., 18., 
		-101., -57., 73., -54., -49., 2., -14., 29., -13., -37., 4., 
		-16., 28., 19., -16., 6., -22., 11., 7., 8., -3., -15., -9., 
		6., 2., -14., 4., 5., -7., 17., 6., -5., 8., -19., 8., 10., 
		-20., 1., 14., -11., 5., 12., -3., 1., -2., -2., 9., 2., 10., 
		0., -2., -1., 2., -3., -4., 2., 2., 1., -5., 2., -2., 6., 6., 
		-4., 4., 0., 0., -2., 1., 4., 3., 0., 0., -6., -30926., 
		-2318., 5817., -893., 2969., -1334., 1471., 728., 1140., 
		-1645., -462., 1202., 119., 881., 229., 891., 711., 216., 
		601., -163., -426., -130., 217., -70., -230., 326., -96., 
		226., 58., -28., -44., -125., -122., -69., 51., 61., 54., 3., 
		-9., 99., -238., 14., -40., -18., 39., 13., -103., -52., 73., 
		-54., -50., 3., -14., 27., -14., -35., 5., -14., 29., 19., 
		-17., 6., -21., 11., 7., 8., -3., -15., -9., 6., 2., -14., 4.,
		 5., -7., 17., 7., -5., 8., -19., 8., 10., -20., 1., 14., 
		-11., 5., 12., -3., 1., -2., -2., 9., 2., 10., 0., -2., -1., 
		2., -3., -4., 2., 2., 1., -5., 2., -2., 6., 6., -4., 4., 0., 
		0., -2., 1., 4., 3., 0., 0., -6., -30805., -2316., 5808., 
		-951., 2980., -1424., 1517., 644., 1172., -1692., -480., 
		1205., 133., 907., 166., 896., 727., 205., 584., -195., -422.,
		 -109., 234., -90., -237., 327., -72., 218., 60., -32., -53., 
		-131., -118., -74., 58., 60., 53., 4., -9., 102., -242., 19., 
		-32., -16., 32., 8., -104., -46., 74., -54., -51., 4., -15., 
		25., -14., -34., 6., -12., 29., 18., -18., 6., -20., 11., 7., 
		8., -3., -15., -9., 5., 2., -14., 5., 5., -6., 18., 8., -5., 
		8., -19., 8., 10., -20., 1., 14., -12., 5., 12., -3., 1., -2.,
		 -2., 9., 3., 10., 0., -2., -2., 2., -3., -4., 2., 2., 1., 
		-5., 2., -2., 6., 6., -4., 4., 0., 0., -2., 1., 4., 3., 0., 
		0., -6., -30715., -2306., 5812., -1018., 2984., -1520., 1550.,
		 586., 1206., -1740., -494., 1215., 146., 918., 101., 903., 
		744., 188., 565., -226., -415., -90., 249., -114., -241., 
		329., -51., 211., 64., -33., -64., -136., -115., -76., 64., 
		59., 53., 4., -8., 104., -246., 25., -25., -15., 25., 4., 
		-106., -40., 74., -53., -52., 4., -17., 23., -14., -33., 7., 
		-11., 29., 18., -19., 6., -19., 11., 7., 8., -3., -15., -9., 
		5., 1., -15., 6., 5., -6., 18., 8., -5., 7., -19., 8., 10., 
		-20., 1., 15., -12., 5., 11., -3., 1., -3., -2., 9., 3., 11., 
		0., -2., -2., 2., -3., -4., 2., 2., 1., -5., 2., -2., 6., 6., 
		-4., 4., 0., 0., -1., 2., 4., 3., 0., 0., -6., -30654., 
		-2292., 5821., -1106., 2981., -1614., 1566., 528., 1240., 
		-1790., -499., 1232., 163., 916., 43., 914., 762., 169., 550.,
		 -252., -405., -72., 265., -141., -241., 334., -33., 208., 
		71., -33., -75., -141., -113., -76., 69., 57., 54., 4., -7., 
		105., -249., 33., -18., -15., 18., 0., -107., -33., 74., -53.,
		 -52., 4., -18., 20., -14., -31., 7., -9., 29., 17., -20., 5.,
		 -19., 11., 7., 8., -3., -14., -10., 5., 1., -15., 6., 5., 
		-5., 19., 9., -5., 7., -19., 8., 10., -21., 1., 15., -12., 5.,
		 11., -3., 1., -3., -2., 9., 3., 11., 1., -2., -2., 2., -3., 
		-4., 2., 2., 1., -5., 2., -2., 6., 6., -4., 4., 0., 0., -1., 
		2., 4., 3., 0., 0., -6., -30594., -2285., 5810., -1244., 
		2990., -1702., 1578., 477., 1282., -1834., -499., 1255., 186.,
		 913., -11., 944., 776., 144., 544., -276., -421., -55., 304.,
		 -178., -253., 346., -12., 194., 95., -20., -67., -142., 
		-119., -82., 82., 59., 57., 6., 6., 100., -246., 16., -25., 
		-9., 21., -16., -104., -39., 70., -40., -45., 0., -18., 0., 
		2., -29., 6., -10., 28., 15., -17., 29., -22., 13., 7., 12., 
		-8., -21., -5., -12., 9., -7., 7., 2., -10., 18., 7., 3., 2., 
		-11., 5., -21., -27., 1., 17., -11., 29., 3., -9., 16., 4., 
		-3., 9., -4., 6., -3., 1., -4., 8., -3., 11., 5., 1., 1., 2., 
		-20., -5., -1., -1., -6., 8., 6., -1., -4., -3., -2., 5., 0., 
		-2., -2., -30554., -2250., 5815., -1341., 2998., -1810., 
		1576., 381., 1297., -1889., -476., 1274., 206., 896., -46., 
		954., 792., 136., 528., -278., -408., -37., 303., -210., 
		-240., 349., 3., 211., 103., -20., -87., -147., -122., -76., 
		80., 54., 57., -1., 4., 99., -247., 33., -16., -12., 12., 
		-12., -105., -30., 65., -55., -35., 2., -17., 1., 0., -40., 
		10., -7., 36., 5., -18., 19., -16., 22., 15., 5., -4., -22., 
		-1., 0., 11., -21., 15., -8., -13., 17., 5., -4., -1., -17., 
		3., -7., -24., -1., 19., -25., 12., 10., 2., 5., 2., -5., 8., 
		-2., 8., 3., -11., 8., -7., -8., 4., 13., -1., -2., 13., -10.,
		 -4., 2., 4., -3., 12., 6., 3., -3., 2., 6., 10., 11., 3., 8.,
		 -30500., -2215., 5820., -1440., 3003., -1898., 1581., 291., 
		1302., -1944., -462., 1288., 216., 882., -83., 958., 796., 
		133., 510., -274., -397., -23., 290., -230., -229., 360., 15.,
		 230., 110., -23., -98., -152., -121., -69., 78., 47., 57., 
		-9., 3., 96., -247., 48., -8., -16., 7., -12., -107., -24., 
		65., -56., -50., 2., -24., 10., -4., -32., 8., -11., 28., 9., 
		-20., 18., -18., 11., 9., 10., -6., -15., -14., 5., 6., -23., 
		10., 3., -7., 23., 6., -4., 9., -13., 4., 9., -11., -4., 12., 
		-5., 7., 2., 6., 4., -2., 1., 10., 2., 7., 2., -6., 5., 5., 
		-3., -5., -4., -1., 0., 2., -8., -3., -2., 7., -4., 4., 1., 
		-2., -3., 6., 7., -2., -1., 0., -3., -30421., -2169., 5791., 
		-1555., 3002., -1967., 1590., 206., 1302., -1992., -414., 
		1289., 224., 878., -130., 957., 800., 135., 504., -278., 
		-394., 3., 269., -255., -222., 362., 16., 242., 125., -26., 
		-117., -156., -114., -63., 81., 46., 58., -10., 1., 99., 
		-237., 60., -1., -20., -2., -11., -113., -17., 67., -56., 
		-55., 5., -28., 15., -6., -32., 7., -7., 23., 17., -18., 8., 
		-17., 15., 6., 11., -4., -14., -11., 7., 2., -18., 10., 4., 
		-5., 23., 10., 1., 8., -20., 4., 6., -18., 0., 12., -9., 2., 
		1., 0., 4., -3., -1., 9., -2., 8., 3., 0., -1., 5., 1., -3., 
		4., 4., 1., 0., 0., -1., 2., 4., -5., 6., 1., 1., -1., -1., 
		6., 2., 0., 0., -7., -30334., -2119., 5776., -1662., 2997., 
		-2016., 1594., 114., 1297., -2038., -404., 1292., 240., 856., 
		-165., 957., 804., 148., 479., -269., -390., 13., 252., -269.,
		 -219., 358., 19., 254., 128., -31., -126., -157., -97., -62.,
		 81., 45., 61., -11., 8., 100., -228., 68., 4., -32., 1., -8.,
		 -111., -7., 75., -57., -61., 4., -27., 13., -2., -26., 6., 
		-6., 26., 13., -23., 1., -12., 13., 5., 7., -4., -12., -14., 
		9., 0., -16., 8., 4., -1., 24., 11., -3., 4., -17., 8., 10., 
		-22., 2., 15., -13., 7., 10., -4., -1., -5., -1., 10., 5., 
		10., 1., -4., -2., 1., -2., -3., 2., 2., 1., -5., 2., -2., 6.,
		 4., -4., 4., 0., 0., -2., 2., 3., 2., 0., 0., -6., -30220., 
		-2068., 5737., -1781., 3e3, -2047., 1611., 25., 1287., -2091.,
		 -366., 1278., 251., 838., -196., 952., 800., 167., 461., 
		-266., -395., 26., 234., -279., -216., 359., 26., 262., 139., 
		-42., -139., -160., -91., -56., 83., 43., 64., -12., 15., 
		100., -212., 72., 2., -37., 3., -6., -112., 1., 72., -57., 
		-70., 1., -27., 14., -4., -22., 8., -2., 23., 13., -23., -2., 
		-11., 14., 6., 7., -2., -15., -13., 6., -3., -17., 5., 6., 0.,
		 21., 11., -6., 3., -16., 8., 10., -21., 2., 16., -12., 6., 
		10., -4., -1., -5., 0., 10., 3., 11., 1., -2., -1., 1., -3., 
		-3., 1., 2., 1., -5., 3., -1., 4., 6., -4., 4., 0., 1., -1., 
		0., 3., 3., 1., -1., -4., -30100., -2013., 5675., -1902., 
		3010., -2067., 1632., -68., 1276., -2144., -333., 1260., 262.,
		 830., -223., 946., 791., 191., 438., -265., -405., 39., 216.,
		 -288., -218., 356., 31., 264., 148., -59., -152., -159., 
		-83., -49., 88., 45., 66., -13., 28., 99., -198., 75., 1., 
		-41., 6., -4., -111., 11., 71., -56., -77., 1., -26., 16., 
		-5., -14., 10., 0., 22., 12., -23., -5., -12., 14., 6., 6., 
		-1., -16., -12., 4., -8., -19., 4., 6., 0., 18., 10., -10., 
		1., -17., 7., 10., -21., 2., 16., -12., 7., 10., -4., -1., 
		-5., -1., 10., 4., 11., 1., -3., -2., 1., -3., -3., 1., 2., 
		1., -5., 3., -2., 4., 5., -4., 4., -1., 1., -1., 0., 3., 3., 
		1., -1., -5., -29992., -1956., 5604., -1997., 3027., -2129., 
		1663., -200., 1281., -2180., -336., 1251., 271., 833., -252., 
		938., 782., 212., 398., -257., -419., 53., 199., -297., -218.,
		 357., 46., 261., 150., -74., -151., -162., -78., -48., 92., 
		48., 66., -15., 42., 93., -192., 71., 4., -43., 14., -2., 
		-108., 17., 72., -59., -82., 2., -27., 21., -5., -12., 16., 
		1., 18., 11., -23., -2., -10., 18., 6., 7., 0., -18., -11., 
		4., -7., -22., 4., 9., 3., 16., 6., -13., -1., -15., 5., 10., 
		-21., 1., 16., -12., 9., 9., -5., -3., -6., -1., 9., 7., 10., 
		2., -6., -5., 2., -4., -4., 1., 2., 0., -5., 3., -2., 6., 5., 
		-4., 3., 0., 1., -1., 2., 4., 3., 0., 0., -6., -29873., 
		-1905., 5500., -2072., 3044., -2197., 1687., -306., 1296., 
		-2208., -310., 1247., 284., 829., -297., 936., 780., 232., 
		361., -249., -424., 69., 170., -297., -214., 355., 47., 253., 
		150., -93., -154., -164., -75., -46., 95., 53., 65., -16., 
		51., 88., -185., 69., 4., -48., 16., -1., -102., 21., 74., 
		-62., -83., 3., -27., 24., -2., -6., 20., 4., 17., 10., -23., 
		0., -7., 21., 6., 8., 0., -19., -11., 5., -9., -23., 4., 11., 
		4., 14., 4., -15., -4., -11., 5., 10., -21., 1., 15., -12., 
		9., 9., -6., -3., -6., -1., 9., 7., 9., 1., -7., -5., 2., -4.,
		 -4., 1., 3., 0., -5., 3., -2., 6., 5., -4., 3., 0., 1., -1., 
		2., 4., 3., 0., 0., -6., -29775., -1848., 5406., -2131., 
		3059., -2279., 1686., -373., 1314., -2239., -284., 1248., 
		293., 802., -352., 939., 780., 247., 325., -240., -423., 84., 
		141., -299., -214., 353., 46., 245., 154., -109., -153., 
		-165., -69., -36., 97., 61., 65., -16., 59., 82., -178., 69., 
		3., -52., 18., 1., -96., 24., 77., -64., -80., 2., -26., 26., 
		0., -1., 21., 5., 17., 9., -23., 0., -4., 23., 5., 10., -1., 
		-19., -10., 6., -12., -22., 3., 12., 4., 12., 2., -16., -6., 
		-10., 4., 9., -20., 1., 15., -12., 11., 9., -7., -4., -7., 
		-2., 9., 7., 8., 1., -7., -6., 2., -3., -4., 2., 2., 1., -5., 
		3., -2., 6., 4., -4., 3., 0., 1., -2., 3., 3., 3., -1., 0., 
		-6., -29692., -1784., 5306., -2200., 3070., -2366., 1681., 
		-413., 1335., -2267., -262., 1249., 302., 759., -427., 940., 
		780., 262., 290., -236., -418., 97., 122., -306., -214., 352.,
		 46., 235., 165., -118., -143., -166., -55., -17., 107., 68., 
		67., -17., 68., 72., -170., 67., -1., -58., 19., 1., -93., 
		36., 77., -72., -69., 1., -25., 28., 4., 5., 24., 4., 17., 8.,
		 -24., -2., -6., 25., 6., 11., -6., -21., -9., 8., -14., -23.,
		 9., 15., 6., 11., -5., -16., -7., -4., 4., 9., -20., 3., 15.,
		 -10., 12., 8., -6., -8., -8., -1., 8., 10., 5., -2., -8., 
		-8., 3., -3., -6., 1., 2., 0., -4., 4., -1., 5., 4., -5., 2., 
		-1., 2., -2., 5., 1., 1., -2., 0., -7., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., -29619.4, -1728.2, 
		5186.1, -2267.7, 3068.4, -2481.6, 1670.9, -458., 1339.6, 
		-2288., -227.6, 1252.1, 293.4, 714.5, -491.1, 932.3, 786.8, 
		272.6, 250., -231.9, -403., 119.8, 111.3, -303.8, -218.8, 
		351.4, 43.8, 222.3, 171.9, -130.4, -133.1, -168.6, -39.3, 
		-12.9, 106.3, 72.3, 68.2, -17.4, 74.2, 63.7, -160.9, 65.1, 
		-5.9, -61.2, 16.9, .7, -90.4, 43.8, 79., -74., -64.6, 0., 
		-24.2, 33.3, 6.2, 9.1, 24., 6.9, 14.8, 7.3, -25.4, -1.2, -5.8,
		 24.4, 6.6, 11.9, -9.2, -21.5, -7.9, 8.5, -16.6, -21.5, 9.1, 
		15.5, 7., 8.9, -7.9, -14.9, -7., -2.1, 5., 9.4, -19.7, 3., 
		13.4, -8.4, 12.5, 6.3, -6.2, -8.9, -8.4, -1.5, 8.4, 9.3, 3.8, 
		-4.3, -8.2, -8.2, 4.8, -2.6, -6., 1.7, 1.7, 0., -3.1, 4., -.5,
		 4.9, 3.7, -5.9, 1., -1.2, 2., -2.9, 4.2, .2, .3, -2.2, -1.1, 
		-7.4, 2.7, -1.7, .1, -1.9, 1.3, 1.5, -.9, -.1, -2.6, .1, .9, 
		-.7, -.7, .7, -2.8, 1.7, -.9, .1, -1.2, 1.2, -1.9, 4., -.9, 
		-2.2, -.3, -.4, .2, .3, .9, 2.5, -.2, -2.6, .9, .7, -.5, .3, 
		.3, 0., -.3, 0., -.4, .3, -.1, -.9, -.2, -.4, -.4, .8, -.2, 
		-.9, -.9, .3, .2, .1, 1.8, -.4, -.4, 1.3, -1., -.4, -.1, .7, 
		.7, -.4, .3, .3, .6, -.1, .3, .4, -.2, 0., -.5, .1, -.9, 
		-29554.63, -1669.05, 5077.99, -2337.24, 3047.69, -2594.5, 
		1657.76, -515.43, 1336.3, -2305.83, -198.86, 1246.39, 269.72, 
		672.51, -524.72, 920.55, 797.96, 282.07, 210.65, -225.23, 
		-379.86, 145.15, 100., -305.36, -227., 354.41, 42.72, 208.95, 
		180.25, -136.54, -123.45, -168.05, -19.57, -13.55, 103.85, 
		73.6, 69.56, -20.33, 76.74, 54.75, -151.34, 63.63, -14.58, 
		-63.53, 14.58, .24, -86.36, 50.94, 79.88, -74.46, -61.14, 
		-1.65, -22.57, 38.73, 6.82, 12.3, 25.35, 9.37, 10.93, 5.42, 
		-26.32, 1.94, -4.64, 24.8, 7.62, 11.2, -11.73, -20.88, -6.88, 
		9.83, -18.11, -19.71, 10.17, 16.22, 9.36, 7.61, -11.25, 
		-12.76, -4.87, -.06, 5.58, 9.76, -20.11, 3.58, 12.69, -6.94, 
		12.67, 5.01, -6.72, -10.76, -8.16, -1.25, 8.1, 8.76, 2.92, 
		-6.66, -7.73, -9.22, 6.01, -2.17, -6.12, 2.19, 1.42, .1, 
		-2.35, 4.46, -.15, 4.76, 3.06, -6.58, .29, -1.01, 2.06, -3.47,
		 3.77, -.86, -.21, -2.31, -2.09, -7.93, 2.95, -1.6, .26, 
		-1.88, 1.44, 1.44, -.77, -.31, -2.27, .29, .9, -.79, -.58, 
		.53, -2.69, 1.8, -1.08, .16, -1.58, .96, -1.9, 3.99, -1.39, 
		-2.15, -.29, -.55, .21, .23, .89, 2.38, -.38, -2.63, .96, .61,
		 -.3, .4, .46, .01, -.35, .02, -.36, .28, .08, -.87, -.49, 
		-.34, -.08, .88, -.16, -.88, -.76, .3, .33, .28, 1.72, -.43, 
		-.54, 1.18, -1.07, -.37, -.04, .75, .63, -.26, .21, .35, .53, 
		-.05, .38, .41, -.22, -.1, -.57, -.18, -.82, -29496.5, 
		-1585.9, 4945.1, -2396.6, 3026., -2707.7, 1668.6, -575.4, 
		1339.7, -2326.3, -160.5, 1231.7, 251.7, 634.2, -536.8, 912.6, 
		809., 286.4, 166.6, -211.2, -357.1, 164.4, 89.7, -309.2, 
		-231.1, 357.2, 44.7, 200.3, 188.9, -141.2, -118.1, -163.1, .1,
		 -7.7, 100.9, 72.8, 68.6, -20.8, 76., 44.2, -141.4, 61.5, 
		-22.9, -66.3, 13.1, 3.1, -77.9, 54.9, 80.4, -75., -57.8, -4.7,
		 -21.2, 45.3, 6.6, 14., 24.9, 10.4, 7., 1.6, -27.7, 4.9, -3.4,
		 24.3, 8.2, 10.9, -14.5, -20., -5.7, 11.9, -19.3, -17.4, 11.6,
		 16.7, 10.9, 7.1, -14.1, -10.8, -3.7, 1.7, 5.4, 9.4, -20.5, 
		3.4, 11.6, -5.3, 12.8, 3.1, -7.2, -12.4, -7.4, -.8, 8., 8.4, 
		2.2, -8.4, -6.1, -10.1, 7., -2., -6.3, 2.8, .9, -.1, -1.1, 
		4.7, -.2, 4.4, 2.5, -7.2, -.3, -1., 2.2, -4., 3.1, -2., -1., 
		-2., -2.8, -8.3, 3., -1.5, .1, -2.1, 1.7, 1.6, -.6, -.5, -1.8,
		 .5, .9, -.8, -.4, .4, -2.5, 1.8, -1.3, .2, -2.1, .8, -1.9, 
		3.8, -1.8, -2.1, -.2, -.8, .3, .3, 1., 2.2, -.7, -2.5, .9, .5,
		 -.1, .6, .5, 0., -.4, .1, -.4, .3, .2, -.9, -.8, -.2, 0., .8,
		 -.2, -.9, -.8, .3, .3, .4, 1.7, -.4, -.6, 1.1, -1.2, -.3, 
		-.1, .8, .5, -.2, .1, .4, .5, 0., .4, .4, -.2, -.3, -.5, -.3, 
		-.8, 11.4, 16.7, -28.8, -11.3, -3.9, -23., 2.7, -12.9, 1.3, 
		-3.9, 8.6, -2.9, -2.9, -8.1, -2.1, -1.4, 2., .4, -8.9, 3.2, 
		4.4, 3.6, -2.3, -.8, -.5, .5, .5, -1.5, 1.5, -.7, .9, 1.3, 
		3.7, 1.4, -.6, -.3, -.3, -.1, -.3, -2.1, 1.9, -.4, -1.6, -.5, 
		-.2, .8, 1.8, .5, .2, -.1, .6, -.6, .3, 1.4, -.2, .3, -.1, .1,
		 -.8, -.8, -.3, .4, .2, -.1, .1, 0., -.5, .2, .3, .5, -.3, .4,
		 .3, .1, .2, -.1, -.5, .4, .2, .4, 0., 0., 0., 0., 0., 0., 0.,
		 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 
		0., 0., 0. };


    /* Format strings */
    static char fmt_960[] = "(/\002 This version of the IGRF is intended for"
	    " use up\002,\002 to 2015.0.\002/\002 values for\002,f9.3,\002 wi"
	    "ll be computed\002,\002 but may be of reduced accuracy\002/)";
    static char fmt_961[] = "(/\002 This subroutine will not work with a dat"
	    "e of\002,f9.3,\002.  Date must be in the range 1900.0.ge.date"
	    "\002,\002.le.2020.0. On return f = 1.0d8., x = y = z = 0.\002)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double cos(doublereal), sin(doublereal), sqrt(doublereal);

    /* Local variables */
    static integer i__, j, k, l, m, n;
    static doublereal p[105], q[105], r__, t, a2, b2;
#define g0 ((doublereal *)&equiv_23)
#define g1 ((doublereal *)&equiv_23 + 120)
#define g2 ((doublereal *)&equiv_23 + 240)
#define g3 ((doublereal *)&equiv_23 + 360)
#define g4 ((doublereal *)&equiv_23 + 480)
#define g5 ((doublereal *)&equiv_23 + 600)
#define g6 ((doublereal *)&equiv_23 + 720)
#define g7 ((doublereal *)&equiv_23 + 840)
#define g8 ((doublereal *)&equiv_23 + 960)
#define g9 ((doublereal *)&equiv_23 + 1080)
    static doublereal cd;
#define ga ((doublereal *)&equiv_23 + 1200)
#define gb ((doublereal *)&equiv_23 + 1320)
#define gc ((doublereal *)&equiv_23 + 1440)
#define gd ((doublereal *)&equiv_23 + 1560)
#define ge ((doublereal *)&equiv_23 + 1680)
#define gf ((doublereal *)&equiv_23 + 1800)
#define gg ((doublereal *)&equiv_23 + 1920)
#define gh ((doublereal *)&equiv_23)
#define gi ((doublereal *)&equiv_23 + 2040)
#define gj ((doublereal *)&equiv_23 + 2160)
#define gk ((doublereal *)&equiv_23 + 2280)
#define gl ((doublereal *)&equiv_23 + 2475)
#define gm ((doublereal *)&equiv_23 + 2670)
    static doublereal cl[13];
    static integer nc;
#define gp ((doublereal *)&equiv_23 + 2865)
#define gq ((doublereal *)&equiv_23 + 3060)
    static integer ll;
    static doublereal tc, ct, sd, fn, gn, sl[13], fm;
    static integer lm;
    static doublereal rr, st, one, gmm, rho;
    static integer kmx, nmx;
    static doublereal two, three, ratio;

    /* Fortran I/O blocks */
    static cilist io___202 = { 0, 6, 0, fmt_960, 0 };
    static cilist io___237 = { 0, 6, 0, fmt_961, 0 };



/*     This is a synthesis routine for the 11th generation IGRF as agreed */
/*     in December 2009 by IAGA Working Group V-MOD. It is valid 1900.0 to */
/*     2015.0 inclusive. Values for dates from 1945.0 to 2005.0 inclusive are */
/*     definitive, otherwise they are non-definitive. */
/*   INPUT */
/*     isv   = 0 if main-field values are required */
/*     isv   = 1 if secular variation values are required */
/*     date  = year A.D. Must be greater than or equal to 1900.0 and */
/*             less than or equal to 2020.0. Warning message is given */
/*             for dates greater than 2015.0. Must be double precision. */
/*     itype = 1 if geodetic (spheroid) */
/*     itype = 2 if geocentric (sphere) */
/*     alt   = height in km above sea level if itype = 1 */
/*           = distance from centre of Earth in km if itype = 2 (>3485 km) */
/*     colat = colatitude (0-180) */
/*     elong = east-longitude (0-360) */
/*     alt, colat and elong must be double precision. */
/*   OUTPUT */
/*     x     = north component (nT) if isv = 0, nT/year if isv = 1 */
/*     y     = east component (nT) if isv = 0, nT/year if isv = 1 */
/*     z     = vertical component (nT) if isv = 0, nT/year if isv = 1 */
/*     f     = total intensity (nT) if isv = 0, rubbish if isv = 1 */

/*     To get the other geomagnetic elements (D, I, H and secular */
/*     variations dD, dH, dI and dF) use routines ptoc and ptocsv. */

/*     Adapted from 8th generation version to include new maximum degree for */
/*     main-field models for 2000.0 and onwards and use WGS84 spheroid instead */
/*     of International Astronomical Union 1966 spheroid as recommended by IAGA */
/*     in July 2003. Reference radius remains as 6371.2 km - it is NOT the mean */
/*     radius (= 6371.0 km) but 6371.2 km is what is used in determining the */
/*     coefficients. Adaptation by Susan Macmillan, August 2003 (for */
/*     9th generation), December 2004 & December 2009. */

/*     Coefficients at 1995.0 incorrectly rounded (rounded up instead of */
/*     to even) included as these are the coefficients published in Excel */
/*     spreadsheet July 2005. */



/*     set initial values */

    *x = 0.f;
    *y = 0.f;
    *z__ = 0.f;
    if (*date < 1900.f || *date > 2020.f) {
	goto L11;
    }
    if (*date > 2015.f) {
	s_wsfe(&io___202);
	do_fio(&c__1, (char *)&(*date), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (*date >= 2010.f) {
	goto L1;
    }
    t = (*date - 1900.f) * .2f;
    ll = (integer) t;
    one = (doublereal) ll;
    t -= one;

/*     SH models before 1995.0 are only to degree 10 */

    if (*date < 1995.f) {
	nmx = 10;
	nc = nmx * (nmx + 2);
	ll = nc * ll;
	kmx = (nmx + 1) * (nmx + 2) / 2;
    } else {
	nmx = 13;
	nc = nmx * (nmx + 2);
	ll = (integer) ((*date - 1995.f) * .2f);

/*     19 is the number of SH models that extend to degree 10 */

	ll = nc * ll + 2280;
	kmx = (nmx + 1) * (nmx + 2) / 2;
    }
    tc = 1.f - t;
    if (*isv == 1) {
	tc = -.2f;
	t = .2f;
    }
    goto L2;

L1:
    t = *date - 2010.f;
    tc = 1.f;
    if (*isv == 1) {
	t = 1.f;
	tc = 0.f;
    }

/*     pointer for last coefficient in pen-ultimate set of MF coefficients... */

    ll = 2865;
    nmx = 13;
    nc = nmx * (nmx + 2);
    kmx = (nmx + 1) * (nmx + 2) / 2;
L2:
    r__ = *alt;
    one = *colat * .017453292f;
    ct = cos(one);
    st = sin(one);
    one = *elong * .017453292f;
    cl[0] = cos(one);
    sl[0] = sin(one);
    cd = 1.f;
    sd = 0.f;
    l = 1;
    m = 1;
    n = 0;
    if (*itype == 2) {
	goto L3;
    }

/*     conversion from geodetic to geocentric coordinates */
/*     (using the WGS84 spheroid) */

    a2 = 40680631.6f;
    b2 = 40408296.f;
    one = a2 * st * st;
    two = b2 * ct * ct;
    three = one + two;
    rho = sqrt(three);
    r__ = sqrt(*alt * (*alt + rho * 2.f) + (a2 * one + b2 * two) / three);
    cd = (*alt + rho) / r__;
    sd = (a2 - b2) / rho * ct * st / r__;
    one = ct;
    ct = ct * cd - st * sd;
    st = st * cd + one * sd;

L3:
    ratio = 6371.2f / r__;
    rr = ratio * ratio;

/*     computation of Schmidt quasi-normal coefficients p and x(=q) */

    p[0] = 1.f;
    p[2] = st;
    q[0] = 0.f;
    q[2] = ct;
    i__1 = kmx;
    for (k = 2; k <= i__1; ++k) {
	if (n >= m) {
	    goto L4;
	}
	m = 0;
	++n;
	rr *= ratio;
	fn = (doublereal) n;
	gn = (doublereal) (n - 1);
L4:
	fm = (doublereal) m;
	if (m != n) {
	    goto L5;
	}
	if (k == 3) {
	    goto L6;
	}
	one = sqrt(1.f - .5f / fm);
	j = k - n - 1;
	p[k - 1] = one * st * p[j - 1];
	q[k - 1] = one * (st * q[j - 1] + ct * p[j - 1]);
	cl[m - 1] = cl[m - 2] * cl[0] - sl[m - 2] * sl[0];
	sl[m - 1] = sl[m - 2] * cl[0] + cl[m - 2] * sl[0];
	goto L6;
L5:
	gmm = (doublereal) (m * m);
	one = sqrt(fn * fn - gmm);
	two = sqrt(gn * gn - gmm) / one;
	three = (fn + gn) / one;
	i__ = k - n;
	j = i__ - n + 1;
	p[k - 1] = three * ct * p[i__ - 1] - two * p[j - 1];
	q[k - 1] = three * (ct * q[i__ - 1] - st * p[i__ - 1]) - two * q[j - 
		1];

/*     synthesis of x, y and z in geocentric coordinates */

L6:
	lm = ll + l;
	one = (tc * gh[lm - 1] + t * gh[lm + nc - 1]) * rr;
	if (m == 0) {
	    goto L9;
	}
	two = (tc * gh[lm] + t * gh[lm + nc]) * rr;
	three = one * cl[m - 1] + two * sl[m - 1];
	*x += three * q[k - 1];
	*z__ -= (fn + 1.f) * three * p[k - 1];
	if (st == 0.f) {
	    goto L7;
	}
	*y += (one * sl[m - 1] - two * cl[m - 1]) * fm * p[k - 1] / st;
	goto L8;
L7:
	*y += (one * sl[m - 1] - two * cl[m - 1]) * q[k - 1] * ct;
L8:
	l += 2;
	goto L10;
L9:
	*x += one * q[k - 1];
	*z__ -= (fn + 1.f) * one * p[k - 1];
	++l;
L10:
	++m;
    }

/*     conversion to coordinate system specified by itype */

    one = *x;
    *x = *x * cd + *z__ * sd;
    *z__ = *z__ * cd - one * sd;
    *f = sqrt(*x * *x + *y * *y + *z__ * *z__);

    return 0;

/*     error return if date out of bounds */

L11:
    *f = 1e8;
    s_wsfe(&io___237);
    do_fio(&c__1, (char *)&(*date), (ftnlen)sizeof(doublereal));
    e_wsfe();
    return 0;
} /* igrf11syn_ */

#undef gq
#undef gp
#undef gm
#undef gl
#undef gk
#undef gj
#undef gi
#undef gh
#undef gg
#undef gf
#undef ge
#undef gd
#undef gc
#undef gb
#undef ga
#undef g9
#undef g8
#undef g7
#undef g6
#undef g5
#undef g4
#undef g3
#undef g2
#undef g1
#undef g0


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



/* Main program alias */ int igrf11_ () { MAIN__ (); return 0; }
