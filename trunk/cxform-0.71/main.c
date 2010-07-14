/* main.c: Sample of using CXFORM in C
**
** 2003/09/12  Ryan Boller:  Initial version
** 2003/11/11  Ryan Boller:  Added date2es function
** 2004/11/25  Ryan Boller:  Moved date2es and other utility functions to cxform-manual shared lib
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cxform.h"



int main()
{
	int retVal, es, year, month, day, hour, minute, second;
	double jd;
	Vec v_in, v_out0, v_out1, v_out2, v_out3;
	static char inSys[] = "J2000";
	static char outSys0[] = "GEO";
	static char outSys1[] = "GSE";
	static char outSys2[] = "GSM";
	static char outSys3[] = "SM";

	year = 2005;
	month = 3;
	day = 2;
	hour = 9;
	minute = 28;
	second = 11;

	jd = gregorian_calendar_to_jd(year, month, day, hour, minute, second);
	es = date2es(year, month, day, hour, minute, second);
	
	printf("Time: %.4d/%.2d/%.2d %.2d:%.2d:%.2d  (JD %f, ES: %d)\n\n", 
		year, month, day, hour, minute, second, jd, es);
	
	

	v_in[0] = -896921337.28302002;
	v_in[1] = 220296912.43620300; 
	v_in[2] =  44419205.01961136;  

	retVal = cxform(inSys, outSys0, es, v_in, v_out0);
	retVal = cxform(inSys, outSys1, es, v_in, v_out1);
	retVal = cxform(inSys, outSys2, es, v_in, v_out2);
	retVal = cxform(inSys, outSys3, es, v_in, v_out3);


	if (retVal == 0)
	{
		printf("Input Vector (%s): \t%f\t%f\t%f\n",
			inSys, v_in[0], v_in[1], v_in[2]);
			
		printf("Output Vector (%s):\t%f\t%f\t%f\n",
			outSys0, v_out0[0], v_out0[1], v_out0[2]);
		printf("Output Vector (%s):\t%f\t%f\t%f\n",
			outSys1, v_out1[0], v_out1[1], v_out1[2]);
		printf("Output Vector (%s):\t%f\t%f\t%f\n",
			outSys2, v_out2[0], v_out2[1], v_out2[2]);
		printf("Output Vector (%s):\t%f\t%f\t%f\n",
			outSys3, v_out3[0], v_out3[1], v_out3[2]);						
	}
	else
		printf("Error during call to cxform\n");
		
	fflush(stdout);
	
	return 0; 
}
