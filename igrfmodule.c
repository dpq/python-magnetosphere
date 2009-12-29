#include <python2.5/Python.h>
#include "f2c.h"

int MAIN__() { return 0; }

static PyObject *igrf_dimo(PyObject *self, PyObject *args) {
	real year, dimo;
	if (!PyArg_ParseTuple(args, "f", &year)) {
		return NULL;
	}
	feldcof_(&year, &dimo);
	return Py_BuildValue("f", dimo);
}

static PyObject *igrf_lb(PyObject *self, PyObject *args) {
	real glat, glon, alt, dimo, fl, b0, year;
	integer icode;
	if (!PyArg_ParseTuple(args, "ffff", &glat, &glon, &alt, &year)) {
		return NULL;
	}
	feldcof_(&year, &dimo);
	shellg_(&glat, &glon, &alt, &dimo, &fl, &icode, &b0);
	return Py_BuildValue("iff", icode, fl, b0);
}

static PyObject *igrf_b(PyObject *self, PyObject *args) {
	real glat, glon, alt, dimo, bnorth, beast, bdown, babs, year;
	if (!PyArg_ParseTuple(args, "ffff", &glat, &glon, &alt, &year)) {
		return NULL;
	}
	feldcof_(&year, &dimo);
	feldg_(&glat, &glon, &alt, &bnorth, &beast, &bdown, &babs);
	return Py_BuildValue("ffff", bnorth, beast, bdown, babs);
}

static PyObject *igrf_b0(PyObject *self, PyObject *args) {
	real glat, glon, alt, dimo, fl, b0, year, stps, bdel, bequ, rr0;
	integer icode;
	logical value;
	if (!PyArg_ParseTuple(args, "fffff", &glat, &glon, &alt, &year, &stps)) {
		return NULL;
	}
	feldcof_(&year, &dimo);
	shellg_(&glat, &glon, &alt, &dimo, &fl, &icode, &b0);
	findb0_(&stps, &bdel, &value, &bequ, &rr0);
	return Py_BuildValue("lfff", value, bequ, rr0, bdel);
}

char *trimwhitespace(char *str) {
	char *end;
	// Trim leading space
	while(isspace(*str)) str++;
	
	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;
	
	// Write new null terminator
	*(end+1) = 0;

	return str;
}

static PyMethodDef IgrfMethods[] = {
	{ "dimo",  igrf_dimo, METH_VARARGS, "dimo(year)\n\nFind the geomagnetic dipole moment in Gauss (normalized to the Earth's radius) at the specified time (decimal year)" },
	{ "lb",  igrf_lb, METH_VARARGS, "igrf.lb(lat, lon, alt, year)\n\nFind the L-shell and geomagnetic field intensity at the specified latitude, longitude, altitude and decimal year" },
	{ "b",  igrf_b, METH_VARARGS, "igrf.b(lat, lon, alt, year)\n\nFind the Earth's magnetic field value using the spherical harmonics model" },
	{ "b0",  igrf_b0, METH_VARARGS, "igrf.b0(lat, lon, alt, year, stps)\n\nFind the smallest magnetic field strength on a field line" },
	{ NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initigrf(void) {
	(void) Py_InitModule("igrf", IgrfMethods);
	initize_();
}
