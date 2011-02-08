#include <python2.5/Python.h>
#include "f2c.h"

extern int rigrf_(real *clon, real *clat, real *r450);
extern int reper_(real *rigrf, real *vkp, real *tmlt, real *reff);
extern int MAIN__(void);
extern struct {
    real rez, pi, st;
} const_;

static PyObject *cutoff_rigidity450(PyObject *self, PyObject *args) {
	float lat = 0.0, lon = 0.0, r450 = 0.0;
	if (!PyArg_ParseTuple(args, "ff", &lat, &lon))
		return NULL;

	rigrf_(&lon, &lat, &r450);
  return Py_BuildValue("f", r450);
}

static PyObject *cutoff_rigidity(PyObject *self, PyObject *args) {
	float lat = 0.0, lon = 0.0, alt = 0.0, r450 = 0.0;
	if (!PyArg_ParseTuple(args, "fff", &lat, &lon, &alt))
		return NULL;

	rigrf_(&lon, &lat, &r450);
	float rf0 = r450*((const_.rez + 450.0) / (const_.rez + alt));
	// rf0 *= rf0;
  if (rf0 < 0.001)
		rf0 = 0.001;
	return Py_BuildValue("f", rf0);
}

static PyObject *cutoff_rigidity_corrected(PyObject *self, PyObject *args) {
	float rig = 0.0, kp = 0.0, lt = 0.0, reff = 0.0;
	if (!PyArg_ParseTuple(args, "ddd", &rig, &kp, &lt))
		return NULL;
	reper_(&rig, &kp, &lt, &reff);
	return Py_BuildValue("d", reff);
}


static PyMethodDef RigidityMethods[] = {
	{"cutoff450",  cutoff_rigidity450, METH_VARARGS, "cutoff(lat, lon)\n\nCalculate cutoff rigidity at 450km altitude."},
	{"cutoff",  cutoff_rigidity, METH_VARARGS, "cutoff(lat, lon, alt)\n\nCalculate cutoff rigidity at the specified altitude (extrapolation from\
 values calculated at the 450km grid)."},
	{"correctedcutoff",  cutoff_rigidity_corrected, METH_VARARGS, "correctedcutoff(rig, kp, lt)\n\nCalculate corrected cutoff rigidity\
 taking into account the current Kp index value and the local time."},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initrigidity(void) {
	MAIN__();
	(void) Py_InitModule("rigidity", RigidityMethods);
}
