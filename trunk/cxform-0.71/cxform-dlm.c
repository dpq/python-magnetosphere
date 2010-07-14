static char const Ident[] =
      "@(#) $Id: cxform-dlm.c,v 1.1.1.1 2005/02/25 20:41:41 rboller Exp $";
/*
** cxform-dlm.c  --  IDL DLM interface for Ed's coordinate transform package
*/

#include <stdio.h>
#include <string.h>
#include "export.h"

#include "cxform.h"

#define PROCEDURE void
#define FUNCTION  IDL_VPTR


/*
** Here be the entry point.  IDL calls this function when the user does
**
**         xx = CXFORM( ... )
**
** with Argc/Argv set as usual.  Basically, all we do is check the input
** arguments for validity, then call the real code.
*/
//FUNCTION CXFORM(int Argc, IDL_VPTR Argv[], char *Argk)
IDL_VPTR CXFORM(int Argc, IDL_VPTR Argv[])
{
  char      *from;
  char      *to;
  double     et;
  double    *v_in;
  double    *v_out;
  IDL_VPTR   tmp_v_out;
  IDL_VPTR   retval_idl;
  int        retval_cxform;

  int         tmp_ndims;
  IDL_MEMINT  tmp_dims[IDL_MAX_ARRAY_DIM];

  char      usage_msg[10240];

  static IDL_EZ_ARG args[] = {
    /* Double v_in[3] or v_in[3,M] */
    { IDL_EZ_DIM_MASK(1)|IDL_EZ_DIM_MASK(2),
      IDL_TYP_B_SIMPLE,
      IDL_EZ_ACCESS_R,
      IDL_TYP_DOUBLE,
      0,
      0 },
    /* const char   * from */
    { IDL_EZ_DIM_MASK(0),
      IDL_TYP_MASK(IDL_TYP_STRING),
      IDL_EZ_ACCESS_R,
      IDL_TYP_STRING,
      0,
      0 },
    /* const char   * to */
    { IDL_EZ_DIM_MASK(0),
      IDL_TYP_MASK(IDL_TYP_STRING),
      IDL_EZ_ACCESS_R,
      IDL_TYP_STRING,
      0,
      0 },
    /* double et */
    { IDL_EZ_DIM_MASK(0)|IDL_EZ_DIM_MASK(1),
      IDL_TYP_B_SIMPLE,
      IDL_EZ_ACCESS_R,
      IDL_TYP_DOUBLE,
      0,
      0 },
  };


  /* Make sure we got the right number of arguments */
  if (Argc != 4)
  {
    sprintf(usage_msg,"%s",
	    "\nIncorrect number of arguments.  Usage:\n"

	    "   new = CXFORM( pos, source_frame, dest_frame, time )\n\n"
      
	    "where:\n"
	    "   pos            is a vector of length 3 or a [3,M] array\n"
	    "   source_frame   source coordinate system, e.g. 'GSE', 'J2000'\n"
	    "   dest_frame     destination coordinate system\n"
	    "   time           seconds past J2000 (Ephemeris Time)\n"
	    "   new            is the position, in dest_frame coordinates\n\n"
	  
	    "Example:\n"
	    "  IDL> time = date2es(10,15,1987,14,05,00)  ;10/15/1987 14:05:00 UTC\n"
	    "  IDL> pos = cxform([1,0,0], 'GSE', 'GEO', time)\n"
	    "  IDL> print, pos\n"
	    "         0.81014581      -0.56750297    -0.14698347\n\n");


    IDL_Message(IDL_M_GENERIC, IDL_MSG_LONGJMP, usage_msg);
		
       	/*"Usage: v_out = CXFORM( v_in[3], `from', `to', et )\n");*/
  }

  /* Check the types of each argument */
  IDL_EzCall(Argc, Argv, args);

  /*
  ** Args are fine, to first order, but we need to perform further checks.
  **
  ** V_IN can be a vector[3] or a matrix[3,M].  The "3" is non-optional.
  **
  ** If V_IN is a vector, ET must be a scalar.  
  ** If V_IN is a matrix, ET must be a vector[M], where M is the order of V_IN.
  */
  switch (args[0].uargv->value.arr->n_dim) {
    /* V_IN is a vector: make sure ET is scalar, and V_IN is [3] */
    case 1:
      if (args[3].uargv->flags & IDL_V_ARR)
	IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		    "ET argument must be a scalar");
      if (args[0].uargv->value.arr->dim[0] != 3)
	IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		    "Vector length of V_IN must be exactly 3");
      break;

    /* V_IN is an NxM matrix.  Make sure ET is a vector[M], and N==3 */
    case 2:
      if (!(args[3].uargv->flags & IDL_V_ARR))
	IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		    "ET argument must be a vector");
      if (args[3].uargv->value.arr->n_dim != 1)
	IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		    "ET argument must be a vector");
      if (args[0].uargv->value.arr->dim[0] != 3)
	IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		    "Dimensions of V_IN must be [3] or [3,M]");
      if (args[3].uargv->value.arr->dim[0] != args[0].uargv->value.arr->dim[1])
	IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		    "Dimension mismatch between V_IN and ET");
      break;

    /* We should never get here, since IDL_EzCall() filters for us */
    default:
      IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		  "Unknown dimensions for V_IN");
  }

  /*
  ** All the arguments are okay.  
  **
  ** Extract string values of from/to frames, and alloc space for return value.
  */
  from        = IDL_STRING_STR(&args[1].uargv->value.str);
  to          = IDL_STRING_STR(&args[2].uargv->value.str);

  tmp_ndims   = args[0].uargv->value.arr->n_dim;	/* 1 or 2 */
  tmp_dims[0] = 3;					/* always 3, for XYZ */
  tmp_dims[1] = args[0].uargv->value.arr->dim[1];	/* (ignored if vec) */
  v_out       = (double*) IDL_MakeTempArray(IDL_TYP_DOUBLE, 
					    tmp_ndims, tmp_dims, 
					    IDL_BARR_INI_ZERO,
					    &tmp_v_out);

  /*
  ** Do the work.
  **
  ** 
  */
  if (tmp_ndims == 1) {				/* V_IN[3] - just one call */
    v_in = (double*)args[0].uargv->value.arr->data;
    et   =          args[3].uargv->value.d;

    retval_cxform = cxform(from, to, et, v_in, v_out);
  } else {					/* V_IN[3,M] - M calls */
    int i;

    for (i=0; i < tmp_dims[1]; i++) {
      v_in = &(((double*)args[0].uargv->value.arr->data)[i*3]);
      et   =  ((double*) args[3].uargv->value.arr->data)[i];

      if ((retval_cxform=cxform(from, to, et, v_in, &v_out[i*3])) != 0)
	break;
    }
  }


  /*
  ** Check the return value of the cxform() function.  If bad, barf out.
  */
  if (retval_cxform != 0) {
    char *msg = cxform_err();

    if (msg[0] == '\0')
      msg = "Unknown error in cxform.c";

    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP, msg);
  }


  /*
  ** All is groovy.  Create a temporary variable, and return that.
  **
  ** We can't just return tmp_v_out, since IDL then complains:
  **
  **    % Temporary variables are still checked out - cleaning up...
  **
  ** I don't know why IDL_MakeTempArray variables aren't the same as Gettmp().
  */
  retval_idl = IDL_Gettmp();
  IDL_VarCopy(tmp_v_out, retval_idl);

  IDL_EzCallCleanup(Argc, Argv, args);

  return retval_idl;
}


/*
** This is how IDL knows what to do when user calls CXFORM().  
*/

static IDL_SYSFUN_DEF main_FUNC_def[] = {
    {(IDL_FUN_RET) CXFORM, "CXFORM", 0, 15, 0},
};


int IDL_Load(void)
{	
/*  return IDL_SysRtnAdd(main_FUNC_def, TRUE, IDL_CARRAY_ELTS(main_FUNC_def)); */

  if (IDL_AddSystemRoutine(main_FUNC_def, IDL_TRUE, 1) == 0)
    return 0;
  return 1;

	
}
