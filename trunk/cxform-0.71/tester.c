/* tester.c: Testing routine for CXFORM
**
** 2004/11/25  Ryan Boller:  Initial version - ugly, but functional
*/

/*
** Required data format from SSCWeb is as follows:
**

       Time                   GEI (RE)                      GEI/J2000 (RE)                      GEO (RE)                          GM (RE)                         GSE (RE)                         GSM (RE)                          SM (RE)            
yy/mm/dd hh:mm:ss      X          Y          Z          X          Y          Z          X          Y          Z          X          Y          Z          X          Y          Z          X          Y          Z          X          Y          Z    

00/07/18 00:00:00    7.68129    1.67608    5.01664    7.68176    1.67515    5.01623    1.87559    7.63503    5.01664   -7.45039    4.18915    3.73107   -0.14490   -8.45372    3.93597   -0.14490   -8.44147    3.96216   -1.34120   -8.44147    3.73107
00/07/18 00:03:00    7.66237    1.67695    5.05177    7.66284    1.67601    5.05137    1.96631    7.59326    5.05177   -7.38960    4.26207    3.77797   -0.12368   -8.44306    3.96787   -0.12368   -8.42716    4.00152   -1.32455   -8.42716    3.77797
00/07/18 00:06:00    7.64297    1.67771    5.08660    7.64345    1.67678    5.08619    2.05615    7.54997    5.08660   -7.32761    4.33364    3.82477   -0.10246   -8.43188    3.99951   -0.10246   -8.41214    4.04086   -1.30773   -8.41214    3.82477
...

**
**   http://sscweb.gsfc.nasa.gov/cgi-bin/sscweb/Locator.cgi
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cxform.h"

#define NLINES  50    /* Number of lines to read from data file */
#define NSYSTEMS  7     /* Number of coordinate systems included in data file */



int main()
{
	/* Misc variables */
	int retVal, i, j, srcSystemIndex;
	char srcSystem[3];
	double jd;
	Vec v_in, v_out;
	FILE *filePtr, *filePtrOut;
	float avgPctDiff[3], avgAbsDiff[3];
	
	/* data variables */
	char fname[] = "test_ssc_data.dat";
	char fname_out[] = "test_results.txt";
	int years[NLINES], months[NLINES], days[NLINES], hours[NLINES], minutes[NLINES], 
		seconds[NLINES], ESs[NLINES];
	float sscData[NLINES][NSYSTEMS*3], cxformOut[NLINES][NSYSTEMS*3];
	char trash[20], temp[20], sscSysNames[NSYSTEMS][20];
	
	/* Open SSCWeb ASCII file */
	filePtr = fopen(fname, "r");
	
	if (filePtr == 0)
	{
			printf("Error opening file.  Exiting.\n");
			exit(0);
	}

	printf("\nAttempting to read %d lines from %s\n\n", NLINES, fname);
	
	/* Read header */
	fscanf(filePtr, "%s%s%s%s%s%s%s%s", trash, sscSysNames[0], trash, sscSysNames[1],
		trash, sscSysNames[2], trash, sscSysNames[3]);	
	fscanf(filePtr, "%s%s%s%s%s%s%s",  trash, sscSysNames[4], trash, sscSysNames[5], 
		trash, sscSysNames[6], trash);
	for (i=0; i<23; i++)
	{
		fscanf(filePtr, "%s", trash);
		/*printf("%s\n", trash);*/
	}
	
	 			
	/* Read data */
	for (i=0; i<NLINES; i++)
	{
		 /* Read time */
	 	if ((fscanf(filePtr, "%2d%1s%2d%1s%2d", &years[i], trash, &months[i], trash, &days[i]) < 1) ||	 	
	 		(fscanf(filePtr, "%2d%1s%2d%1s%2d", &hours[i], trash, &minutes[i], trash, &seconds[i]) < 1))
	 	{
			printf("EOF reached.  Set NLINES smaller.  Exiting.\n");
			exit(0); 		
	 	}
	 	
	 	/* Convert date to YYYY format if nec */
	 	if (years[i] < 50)
	 		years[i] = years[i] + 2000;
	 	else if (years[i] < 1900)
	 		years[i] = years[i] + 1900;
	 		
	 	/* Convert time to ephemeris seconds */
	 	ESs[i] = date2es(years[i], months[i], days[i], hours[i], minutes[i], seconds[i]);

		/*
	 	printf("Read time: %4d/%0.2d/%0.2d %0.2d:%0.2d:%0.2d  ", years[i], months[i], days[i], hours[i], minutes[i], seconds[i]);	 		 	
	 	printf("ES: %d\n", ESs[i]);
	 	*/
		
	 	/* Read position data */
	 	for (j=0; j<3*NSYSTEMS; j++)
	 	{		 	
		 	fscanf(filePtr, "%f", &sscData[i][j]);
	 	}
	}
	
	
	
	/* Close the file */
	fclose(filePtr);
	
	/* Echo systems, convert J2000 & GM strings */
	printf("\nRead the following systems:\n");
	for (i=0; i<NSYSTEMS; i++)
	{
		if (strcmp(sscSysNames[i], "GEI/J2000") == 0)
			strcpy(sscSysNames[i], "J2000");
		else if (strcmp(sscSysNames[i], "GM") == 0)
			strcpy(sscSysNames[i], "MAG");
			
		printf("%s\n", sscSysNames[i]);
	}
	printf("\n");

	
	/* Begin testing */
	strcpy(srcSystem, "GSE");   /* Use 2nd parameter as source system */
	srcSystemIndex = 4;
	
	
	for (i=0; i<NSYSTEMS; i++)
	{
		for (j=0; j<NLINES; j++)
		{
			/* Parse input vector */
			v_in[0] = sscData[j][srcSystemIndex*3+0];
			v_in[1] = sscData[j][srcSystemIndex*3+1];
			v_in[2] = sscData[j][srcSystemIndex*3+2];
				
			/* Perform transformation (finally) */
			retVal = cxform(srcSystem, sscSysNames[i], ESs[j], v_in, v_out);
			
			if (retVal != 0)
			{
				printf("Error during call to cxform. Exiting.\n");
				exit(0);
			}
		
			
			/* Place output vector */
			cxformOut[j][i*3+0] = v_out[0];
			cxformOut[j][i*3+1] = v_out[1];
			cxformOut[j][i*3+2] = v_out[2];
		
			
			/*
			printf("Input Vector (%s): \t%f\t%f\t%f\n",
				srcSystem, v_in[0], v_in[1], v_in[2]);
			
			printf("Output Vector (%s):\t%f\t%f\t%f\n",
				sscSysNames[i], v_out[0], v_out[1], v_out[2]);
			*/
		}
	}
	
	
	/* Perform comparison between SSC and CXFORM's results */
	
	/* Open output file */
	filePtrOut = fopen(fname_out, "w");
	
	if (filePtrOut == 0)
	{
			printf("Error opening file for writing.  Exiting.\n");
			exit(0);
	}
	
	printf("\nWriting results to %s\n", fname_out);
	fprintf(filePtrOut, "N=%d", NLINES);
	
	
	for (i=0; i<NSYSTEMS; i++)
	{
		avgAbsDiff[0] = 0.0;
		avgAbsDiff[1] = 0.0;
		avgAbsDiff[2] = 0.0;
		avgPctDiff[0] = 0.0;
		avgPctDiff[1] = 0.0;
		avgPctDiff[2] = 0.0;
		
		fprintf(filePtrOut, "\nComparing transformation from %s to %s:\n", srcSystem, sscSysNames[i]);
		
		for (j=0; j<NLINES; j++)
		{	
			/*
			printf("Absolute differences: %f\t%f\t%f\n", fabs(sscData[j][i*3+0]-cxformOut[j][i*3+0]),
				fabs(sscData[j][i*3+1]-cxformOut[j][i*3+1]),
				fabs(sscData[j][i*3+2]-cxformOut[j][i*3+2]));
			*/
			
			/*
			printf("Percent differences: %f\t%f\t%f\n", 
				fabs(100.0 - (sscData[j][i*3+0]/cxformOut[j][i*3+0])*100.0),
				fabs(100.0 - (sscData[j][i*3+1]/cxformOut[j][i*3+1])*100.0),
				fabs(100.0 - (sscData[j][i*3+2]/cxformOut[j][i*3+2])*100.0));
			*/

			avgAbsDiff[0] = avgAbsDiff[0] + fabs(sscData[j][i*3+0]-cxformOut[j][i*3+0]);
			avgAbsDiff[1] = avgAbsDiff[1] + fabs(sscData[j][i*3+1]-cxformOut[j][i*3+1]);
			avgAbsDiff[2] = avgAbsDiff[2] + fabs(sscData[j][i*3+2]-cxformOut[j][i*3+2]);
				
			avgPctDiff[0] = avgPctDiff[0] + fabs(100.0 - (sscData[j][i*3+0]/cxformOut[j][i*3+0])*100.0);
			avgPctDiff[1] = avgPctDiff[1] + fabs(100.0 - (sscData[j][i*3+1]/cxformOut[j][i*3+1])*100.0);
			avgPctDiff[2] = avgPctDiff[2] + fabs(100.0 - (sscData[j][i*3+2]/cxformOut[j][i*3+2])*100.0);
		}

		
		avgAbsDiff[0] = avgAbsDiff[0]/(float)NLINES;
		avgAbsDiff[1] = avgAbsDiff[1]/(float)NLINES;
		avgAbsDiff[2] = avgAbsDiff[2]/(float)NLINES;
				
		avgPctDiff[0] = avgPctDiff[0]/(float)NLINES;
		avgPctDiff[1] = avgPctDiff[1]/(float)NLINES;
		avgPctDiff[2] = avgPctDiff[2]/(float)NLINES;
		
		
		fprintf(filePtrOut, "Average absolute differences: \t%f\t%f\t%f\n", 	avgAbsDiff[0], 	avgAbsDiff[1], 	avgAbsDiff[2]);
		fprintf(filePtrOut, "Average percent differences:  \t%f\t%f\t%f\n", 	avgPctDiff[0], 	avgPctDiff[1], 	avgPctDiff[2]);
	}
		
	fclose(filePtrOut);
	
	return 0; 
}
