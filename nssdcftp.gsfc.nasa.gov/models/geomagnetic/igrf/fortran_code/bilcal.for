C BILCAL.FOR
C
C mm/dd/yy
C 01/25/92 Modified for use with the IGRF-91 coefficients, which
C	       were provided by R. Langel, GSFC.
C 02/05/92 Reduce variable-name: INITI(ALI)ZE
C 03/25/96 Modified for use with the IGRF-95 coefficients, which
C	       were provided by R. Langel, GSFC.
C 06/06/00 Modified for use with IGRF-2000 coefficients.
C 11/14/01 Add IMIN=0 above 4927 READ(...)  [Rui Pereira] 
C 04/25/05 IBBB instead of IBB in data statem.  [Alexey Petrov]
C 03/12/10 Updated to Version 11 (1945-2015) [###] 
C
C*****************************************************************
C**************** IGRF MAGNETIC FIELD MODEL  *********************
C**************** SHELLG L-VALUE CALCULATION *********************
C*****************************************************************
C*****************************************************************
C*** THIS PROGRAM PRODUCES PROFILES OF:                        ***
C***      GEOMAGNETIC FIELD STRENGTH (GAUSS) 		       ***
C***      L-VALUE 					       ***
C*****************************************************************
C*** FOR SPECIFIED:                                            ***
C***      YEAR (DECIMAL YEAR, E.G., 1995.5 FOR MID 1995)       ***
C***      GEODATIC LATITUDE AND LONGITUDE (DEGREE)             ***
C***      ALTITUDE (KM)                                        ***
C*****************************************************************
C*****************************************************************
C*     --------------------ADDRESS--------------------------     *
C*     I  DR. DIETER BILITZA  (301)513-1664      	   I     *
C*     I  GSFC, NSSDC, CODE 933, GREENBELT, MD 20771, USA  I     *
C*     I  SPAN:     NSSDCA::BILITZA, NSSDC::BILITZA        I     *
C*     I  BITNET:   BILITZA%NSSDCA.SPAN@DFTNIC.BITNET      I     *
C*     -----------------------------------------------------     *
C*****************************************************************
C*****************************************************************
C*****************************************************************
      INTEGER 		EGNR,AGNR,OGNR
      REAL 		LATI,LONGI,MLAT,MLONG
      CHARACTER*4 	ITEXT(4),LTEX
      CHARACTER*7 	ITB
      CHARACTER*11	NAME
      LOGICAL 		NOTBEG,VAL
      DIMENSION 	DEN(8),TEMP(2),XVAR(4),VARE(4),VARB(4)
      COMMON/GENER/	UMR,ERA,AQUAD,BQUAD
C
      DATA ITEXT	/'LATI','LONG','H/km','YEAR'/
      DATA LATI,LONGI,HEIGHT,YEAR,IVAR,BVAR,EVAR,SVAR,IBBB,JAGNR
     &    		/45.1,293.1,100,1985.5,3,100,1000,100,0,2/
c### year limit modified
      DATA VARB 	/-90.0,-360.0,0.00000,1940.0/
      DATA VARE 	/+90.0,+360.0,30000.0,2015.0/
C
      CALL INITIZE
      ALOG2=ALOG(2.)
      ISTART=1
C
C FIRST SPECIFY YOUR COMPUTERS CHANNEL NUMBERS ....................
C EGNR=INPUT, MONITO=MONITOR, KONSOL=MESSAGES......................
C AGNR=DISPLAY, OGNR=FILE OUTPUT...................................
C
      EGNR=5
      MONITO=6
      AGNR=6
      OGNR=16
      WRITE(MONITO,5100)
5100  FORMAT(1X/////4X,54('*')/4X,
     & '****** IGRF GEOMAGNETIC FIELD MODEL 1945 - 2005 ******'/4X,
     & '***********  SHELLG L-VALUE CALCULATION  *************'/1X,
     & 60('*')/'  This program allows you to produce B and L ',
     & 'profiles in '/'  latitude, longitude, year or altitude.'/
     & '  In each of the following windows you will be ',
     & 'asked to enter'/'  one or more values, defining the conditions',
     & ' for your tables.'/'  In each window the current value(s) is',
     & ' (are) shown in the right'/'  upper corner (#...#). You can ',
     & 'choose the current values by'/'  entering / at the prompt.'/
     & '  If you enter a wrong character or a value outside the ',
     & 'allowed'/'  parameter range, the program will ask you for a',
     & ' new entry.'/'  After your tables are displayed, you can ',
     & 'change any parameter'/'  you wish to change and create a ',
     & 'new profile.'/'  You can leave the program at any point ',
     & 'by entering Ctrl Z.'/1X,25('*'),' GOOD LUCK ',25('*'))
      NOTBEG=.FALSE.
      GOTO 5508
C---------------START ENTERING PARAMETERS----------------------------
3293  CONTINUE
      ISTART=ISTART+1
C---------------WINDOW 1: WHICH PARAMETER CHANGE ?-------------------
      WRITE(MONITO,5602) LATI,LONGI,ITEXT(IVAR),HEIGHT,YEAR,BVAR,
     & EVAR,SVAR
5602  FORMAT(1X//' **** WHICH PARAMETER DO YOU WANT TO CHANGE?'/
     & 1X,60('-')/' 0  NO FURTHER CHANGES, CALCULATE PROFILE'/
     & ' 1  LATITUDE  #',F6.1,'#',7X,'5  DISPLAY OR STORE'/
     & ' 2  LONGITUDE #',F6.1,'#',7X,'6  SELECTION OF VARIABLE  #',
     & A4,'#'/' 3  ALTITUDE  #',F8.1,'#',5X,'7  VARIABLE RANGE'/
     & ' 4  YEAR      #',F6.1,'#',11X,'#',F8.1,',',F8.1,',',
     & F8.1,'#'/29X,'8  B OR B/B0'/1X,60('-')/' ENTER NUMBER')   
	IMIN=0
	IMAX=8
4925  READ(EGNR,*,ERR=8600,END=6666) ISWIT
	IF((ISWIT.GE.IMIN).AND.(ISWIT.LE.IMAX)) GOTO 8601
8600		WRITE(MONITO,4924) IMIN,IMAX
4924		FORMAT(' Your input is outside the value range:',
     &		  I2,' to',I2/' try again')
		GOTO 4925
8601  GOTO (5505,3329,3339,5502,6780,5508,5503,5504,9138) ISWIT+1
C--------------WINDOW 2: DISPLAY OPTIONS--------------------------
5508  WRITE(MONITO,5123) JAGNR
5123  FORMAT(/' DO YOU WANT YOUR PROFILES',32X,'#',I1,'#'/5X,
     & 'DISPLAYED ON YOUR MONITOR: ENTER  0  AT PROMPT'/5X,
     & 'STORED IN FILE OUTPUT.IGR: ENTER  1  AT PROMPT'/5X,
     & 'DISPLAYED AND STORED:      ENTER  2  AT PROMPT')
      WRITE(MONITO,8630)
	IMAX=2
        IMIN=0
4927  READ(EGNR,*,ERR=8603,END=6666) JAGNR
	IF((JAGNR.GE.IMIN).AND.(JAGNR.LE.IMAX)) GOTO 8602
8603		WRITE(MONITO,4924) IMIN,IMAX 
		GOTO 4927
8602  IVARNR=0
      IF(JAGNR.GT.0) 
     &	OPEN(UNIT=OGNR,FILE='OUTPUT.IGR',STATUS='NEW',FORM='FORMATTED')
      IF(JAGNR.EQ.1)  AGNR=OGNR
      IF(NOTBEG) GOTO 3293
C---------------WINDOW 3: SELECT VARIABLE------------------------
5503  WRITE(MONITO,5040) IVAR
5040  FORMAT(1X//' SELECT YOUR VARIABLE:',31X,'#LAST:',I1,'#'//
     &	' 1  LATITUDE       3  ALTITUDE'/
     &  ' 2  LONGITUDE      4  YEAR')
      WRITE(MONITO,8630)
8630  FORMAT(1X,60('-')/' Enter / to use previous value(s) ',
     &	'(see # .. #); Ctrl Z to exit')
	IMIN=1
	IMAX=4
4929  READ(EGNR,*,ERR=8605,END=6666) IVAR
	IF((IVAR.GE.IMIN).AND.(IVAR.LE.IMAX)) GOTO 5504
8605		WRITE(MONITO,4924) IMIN,IMAX 
		GOTO 4929
C--------------WINDOW 4: SELECT VARIABLE RANGE---------------------
5504  WRITE(MONITO,5044) BVAR,EVAR,SVAR
5044  FORMAT(1X//' CHOOSE YOUR VARIABLE RANGE:',5X,' BEGIN, END, ',
     & 'STEPWIDTH ?'/32X,'#',F8.1,',',F8.1,',',F8.1,'#')
      WRITE(MONITO,8630)
	VAMIN=VARB(IVAR)
	VAMAX=VARE(IVAR)
4931  READ(EGNR,*,ERR=8606,END=6666) BVAR,EVAR,SVAR
	IF((BVAR.GE.VAMIN).AND.(EVAR.LE.VAMAX)) GOTO 8607
8606		WRITE(MONITO,4930) VAMIN,VAMAX
4930		FORMAT(' Your input is outside the value range:',
     &		  F8.1,' to',F8.1/' try again')
		GOTO 4931
8607  LANZ=INT((EVAR-BVAR)/SVAR)+1
      IF(NOTBEG) GOTO 3293
      IVARNR=IVARNR+1
      IF(IVARNR.EQ.IVAR) GOTO 7339
C--------------WINDOW 5: LATITUDE-----------------------------------
3329  WRITE(MONITO,5000) LATI
5000  FORMAT(1X//1X,'GEOD LATITUDE ?   !NORTH!    [DEGREE,DECIMAL]',
     & 8X,'#',F5.1,'#')
      WRITE(MONITO,8630)
	XMAX=VARE(1)
	XMIN=VARB(1)
4933  READ(EGNR,*,ERR=8608,END=6666) LATI
	IF((LATI.GE.XMIN).AND.(LATI.LE.XMAX)) GOTO 8609
8608		WRITE(MONITO,4930) XMIN,XMAX
		GOTO 4933
8609  IF(NOTBEG) GOTO 3293
7339  IVARNR=IVARNR+1
      IF(IVARNR.EQ.IVAR) GOTO 7500
C---------------WINDOW 6: LONGITUDE---------------------------------
3339  WRITE(MONITO,6001) LONGI
6001  FORMAT(1X//1X,'GEOD LONGITUDE ?   !EAST!    [DEGREE,DECIMAL]',
     & 7X,'#',F6.1,'#')
	WRITE(MONITO,8630)
	XMAX=VARE(2)
	XMIN=VARB(2)
4934  READ(EGNR,*,ERR=8610,END=6666) LONGI
	IF((LONGI.GE.XMIN).AND.(LONGI.LE.XMAX)) GOTO 8611
8610		WRITE(MONITO,4930) XMIN,XMAX
		GOTO 4934
8611  IF(NOTBEG) GOTO 3293
7500  IVARNR=IVARNR+1
      IF(IVARNR.EQ.IVAR) GOTO 5551
C---------------WINDOW 7: ALTITUDE---------------------------------
5502  WRITE(MONITO,6002) HEIGHT
6002  FORMAT(1X//1X,'ALTITUDE ?    [KM]',33X,'#',F7.1,'#')
	WRITE(MONITO,8630)
	XMAX=VARE(3)
	XMIN=VARB(3)
4936  READ(EGNR,*,ERR=8615,END=6666) HEIGHT
	IF((HEIGHT.GE.XMIN).AND.(HEIGHT.LE.XMAX)) GOTO 8616
8615		WRITE(MONITO,4930) XMIN,XMAX
		GOTO 4936
8616  IF(NOTBEG) GOTO 3293
5551  IVARNR=IVARNR+1
      IF(IVARNR.EQ.IVAR) GOTO 9138
C----------------WINDOW 8: YEAR------------------------------------
6780  WRITE(MONITO,6004) YEAR
6004  FORMAT(1X//' YEAR(EPOCH) ?',9X,'*decimal*',9X,'#',F6.1,'#')
	WRITE(MONITO,8630)
	XMAX=VARE(4)
	XMIN=VARB(4)
4938  READ(EGNR,*,ERR=8617,END=6666) YEAR
	IF((YEAR.GE.XMIN).AND.(YEAR.LE.XMAX)) GOTO 8618
8617		WRITE(MONITO,4930) XMIN,XMAX
		GOTO 4938
8618  IF(NOTBEG) GOTO 3293
C----------------WINDOW 9: ABSOLUTE OR NORMALIZED B--------------
9138  WRITE(MONITO,6204) IBBB
6204  FORMAT(1X//' OUTPUT OPTION: B OR B/B0 ?',19X,'#',I1,'#'//
     &	4X,'if you enter 0, the absolute magnetic field strength'/
     &	4X,'will be listed, otherwise the field strength normalized'/
     &	4X,'to the field strength at the magnetic equator is listed')
	WRITE(MONITO,8630)
4738  READ(EGNR,*,ERR=8717,END=6666) IBBB
	IF(IBBB.NE.0) THEN
		ITB='  B/B0 '
	ELSE
		ITB='B/Gauss'
	ENDIF
	GOTO 8718
8717	WRITE(MONITO,4630)
4630	FORMAT(' Your input should be a integer value'/' try again')
	GOTO 4738
8718  IF(NOTBEG) GOTO 3293
C----------------CALCULATE PROFILES-----------------------------------
5505	WRITE(AGNR,3910) ITEXT(IVAR),ITB
	IF(JAGNR.EQ.2) WRITE(OGNR,3910) ITEXT(IVAR),ITB
3910	FORMAT(1X////////////
     &   5X,A4,'   DIMO  ',A7,' B-NORTH  B-EAST  B-DOWN ',
     &   '   DIP    DEC  L-VALUE C')  
	XVAR(1)=LATI
	XVAR(2)=LONGI
        XVAR(3)=HEIGHT
        XVAR(4)=YEAR
        LFD=0
        XVAR(IVAR)=BVAR-SVAR
2123    XVAR(IVAR)=XVAR(IVAR)+SVAR
        LFD=LFD+1
        LATI=XVAR(1)
        LONGI=XVAR(2)
        HEIGHT=XVAR(3)
        YEAR=XVAR(4)
	IF((IVAR.LT.4).AND.(LFD.GT.1)) GOTO 2910
	CALL FELDCOF(YEAR,DIMO)
2910	CALL FELDG(LATI,LONGI,HEIGHT,BNORTH,BEAST,BDOWN,BABS)
	CALL SHELLG(LATI,LONGI,HEIGHT,DIMO,XL,ICODE,BAB1)
	IF(IABS(ICODE).GT.9) THEN
		WRITE(MONITO,7227) ICODE
7227	FORMAT(' ICODE=',I10,' is set to 2')
		ICODE=2
		ENDIF
	IF(IBBB.EQ.0) GOTO 2299
	BEQU=DIMO/(XL*XL*XL)
	IF(ICODE.EQ.1) THEN
		BDEL=1.E-3
		CALL FINDB0(0.05,BDEL,VAL,BEQ,RR0)
		IF(VAL) BEQU=BEQ
		ENDIF
2299	DIP=ASIN(BDOWN/BABS)/UMR
	DEC=ASIN(BEAST/SQRT(BEAST*BEAST+BNORTH*BNORTH))/UMR
	XCOR=XVAR(IVAR)
	IF(IBBB.EQ.0) THEN
	   WRITE(AGNR,7117) XCOR,DIMO,BABS,BNORTH,BEAST,BDOWN,
     &	      DIP,DEC,XL,ICODE
	   IF(JAGNR.EQ.2) WRITE(OGNR,7117) XCOR,DIMO,BABS,BNORTH,
     &        BEAST,BDOWN,DIP,DEC,XL,ICODE
7117	   FORMAT(1X,F8.2,F8.4,4(1X,F7.5),2F7.1,F8.3,I3)
	ELSE
	   BBX=BABS/BEQU
	   IF(BBX.GT.9999.999) BBX=9999.999
	   WRITE(AGNR,7177) XCOR,DIMO,BBX,BNORTH,BEAST,BDOWN,
     &	      DIP,DEC,XL,ICODE
	   IF(JAGNR.EQ.2) WRITE(OGNR,7177) XCOR,DIMO,BBX,BNORTH,
     &        BEAST,BDOWN,DIP,DEC,XL,ICODE
7177	   FORMAT(1X,F8.2,F8.4,F8.3,3(1X,F7.5),2F7.1,F8.3,I3)
	ENDIF
	IF(XCOR.LT.EVAR) GOTO 2123
	WRITE(AGNR,2193) LATI,LONGI,HEIGHT,YEAR
	IF(JAGNR.EQ.2) WRITE(OGNR,2193) LATI,LONGI,HEIGHT,YEAR
C ### edition date corrected
2193	FORMAT(1X,'------- International Geomagnetic Reference Field', 
     &	  ' --- Version 11 -------'/' LATI=',F7.1,'  LONGI=',F6.1,
     &    '  I   DIMO is Dipol   I   C=1  L and B0 correct'/
     &    '  ALT=',F7.1,'   YEAR=',F6.1,'  I  Moment in Gauss',
     &    '  I    =2  wrong,  =3  approx.'/1X,74('-'))
	IF(HEIGHT.GT.5000.0) THEN 
		WRITE(AGNR,5611)
		IF(JAGNR.EQ.2) WRITE(OGNR,5611)
		ENDIF
5611  	  FORMAT(' !! REMINDER: this field model does not',
     &		' include external sources !!')
C ### year limits corrected
	IF((YEAR.LT.1945.0).OR.(YEAR.GT.2015.0)) THEN
		WRITE(AGNR,5612)
		IF(JAGNR.EQ.2) WRITE(OGNR,5612)
		ENDIF
C ### timeperiod corrected
5612  	  FORMAT(' !! REMINDER: Recommended time period is 1945', 
     &		' to 2015 !!')
C-----------------LAST WINDOW: CONTINUE ?-----------------------
918   WRITE(MONITO,5600)
5600  FORMAT(1X/' **** DO YOU WANT TO CONTINUE?'/1X,60('-')/
     &  ' "0"  QUIT AND EXIT        "1"  NEW PARAMETERS'/
     &  1X,60('-'))
	IMIN=0
	IMAX=1
8651  READ(EGNR,*,ERR=8652,END=6666) IALL
	IF((IALL.GE.IMIN).AND.(IALL.LE.IMAX)) GOTO 8653
8652		WRITE(MONITO,4924) IMIN,IMAX 
		GOTO 8651
8653  NOTBEG=.TRUE.
      IF(IALL.EQ.1) GOTO 3293
6666  CONTINUE
      STOP
      END
