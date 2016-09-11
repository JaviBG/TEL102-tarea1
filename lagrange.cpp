#include <iostream>
#include <fstream>
#include <Python.h>
 
using namespace std;
 
#include <iomanip>
 
struct output{
	double* p;
	double* l;
	int n;
} salida;

void monomio2(int n, double *x, double *D);
 
output lagrange_interpolation () {
 
    ifstream label1 ("datos//datos.in");
     
    int n, i, j, k;
 
    label1 >> n;
 
    double *x, *xp, *f, *L, *D, producto, sum, *P;
 
    x = new double [n], xp = new double [n], f = new double [n];
    L = new double [n], D = new double [n+1], P = new double [n];
 
    for (i= 0; i < n; i++){
 
        label1 >> x[i] >> f[i];
    }
 
    cout << endl;
 
    for (k = 0; k < n; k++){
 
    producto = 1;
 
        for (i = 0; i < n; i++){
 
            if (i != k) producto = producto * (x[k] - x[i]);
 
        }
     
    L[k] = f[k]/producto;
 
    }
 
    for (k = 0; k < n; k++){
     
        j = 0;  
         
        for (i = 0; i < n; i++){
 
            if (i != k) {xp[j] = x[i]; j += 1;}
 
        }
     
        monomio2 (n-1, xp, D);
 
        for (i= 0; i < n; i++){
 
            P[i] = P[i] + L[k]*D[i];
 
        }
      
    }

    salida.p = P;
    salida.l = L;
    salida.n = n;

    return salida;
 
}
 
void monomio2(int n, double *x, double *D){
 
    double *E;
 
    E = new double [n];
 
    D[0] = 1;
 
    D[1] = -x[0];
 
    for (int i = 1; i < n; i++) {
 
        for (int k =1; k < i+1; k++) {
 
            E[k] = D[k] + D[k-1]*(-x[i]);
 
        }
 
        D[i+1] = D[i]*(-x[i]);
 
        for (int j = 1; j < i+1; j++) {
 
            D[j] = E[j];
 
        }
 
    }
 
    delete E;
}

PyObject *wrap_lagrange_interpolation(PyObject *self, PyObject *args){
    output data;
    data = lagrange_interpolation();
    if (data.n == 1) {
    	return Py_BuildValue("(d)",data.p[0]);	
    }
    else if (data.n == 2){
    	return Py_BuildValue("(dd)",data.p[0],data.p[1]);
    }
    else if (data.n == 3){
    	return Py_BuildValue("(ddd)",data.p[0],data.p[1],data.p[2]);
    }
    else if (data.n == 4){
    	return Py_BuildValue("(dddd)",data.p[0],data.p[1],data.p[2],data.p[3]);
    }
    else {
    	return NULL;
    }
}

PyObject *wrap_lagrange_interpolation_L(PyObject *self, PyObject *args){
    output data;
    data = lagrange_interpolation();
    if (data.n == 1) {
    	return Py_BuildValue("(d)",data.l[0]);	
    }
    else if (data.n == 2){
    	return Py_BuildValue("(dd)",data.l[0],data.l[1]);
    }
    else if (data.n == 3){
    	return Py_BuildValue("(ddd)",data.l[0],data.l[1],data.l[2]);
    }
    else if (data.n == 4){
    	return Py_BuildValue("(dddd)",data.p[0],data.l[1],data.l[2],data.l[3]);
    }
    else {
    	return NULL;
    }
}

PyObject *wrap_point_interpolate(PyObject *self, PyObject *args){
    int x;
    output data = lagrange_interpolation();
	if (!PyArg_ParseTuple(args, "i", &x))
		return NULL;

	if (data.n == 1) {
    	return Py_BuildValue("d",data.p[0]);	
    }
    else if (data.n == 2){
    	return Py_BuildValue("d",x*data.p[0]+data.p[1]);
    }
    else if (data.n == 3){
    	return Py_BuildValue("d",x*x*data.p[0]+x*data.p[1]+data.p[2]);
    }
    else if (data.n == 4){
    	return Py_BuildValue("d",x*x*x*data.p[0]+x*x*data.p[1]+x*data.p[2]+data.p[3]);
    }
    else {
    	return NULL;
    }
}

static PyMethodDef lagrangeMethods[] = {
    {"lagrange_interpolation", wrap_lagrange_interpolation, METH_VARARGS, "Execute a shell command."},
    {"lagrange_interpolation_L", wrap_lagrange_interpolation_L, METH_VARARGS, "Execute a shell command."},
    {"point_interpolate", wrap_point_interpolate, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL}
};

static struct PyModuleDef lagrangeModule = {
   PyModuleDef_HEAD_INIT,
   "lagrange",
   NULL,
   -1,
   lagrangeMethods
};

PyMODINIT_FUNC
PyInit_lagrange(void) {
    return PyModule_Create(&lagrangeModule);
}