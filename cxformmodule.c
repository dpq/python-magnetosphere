#include <python2.5/Python.h>
#include "cxform.h"

static PyObject *cxform_transform(PyObject *self, PyObject *args) {
	const char *from, *to;
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	Vec v_in = {0.0, 0.0, 0.0};
	Vec v_out = {0.0, 0.0, 0.0};
	PyObject dt;

//	if (!PyArg_ParseTuple(args, "ssdddO!", &from, &to, &v_in[0], &v_in[1], &v_in[2], "DateTime", &dt))
//		return NULL;
	if (!PyArg_ParseTuple(args, "ssdddiiiiii", &from, &to, &v_in[0], &v_in[1], &v_in[2], &year, &month, &day, &hour, &minute, &second))
		return NULL;

	double es = date2es(year, month, day, hour, minute, second);
	cxform(from, to, es, v_in, v_out);
	return Py_BuildValue("ddd", v_out[0], v_out[1], v_out[2]);
}

static PyMethodDef CxformMethods[] = {
	{"transform",  cxform_transform, METH_VARARGS, "transform(from, to, x, y, z, year, month, day, hour, minute, second)\n\nTransform coordinates from one system to another."},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initcxform(void) {
	(void) Py_InitModule("cxform", CxformMethods);
}
