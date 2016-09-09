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
    output result;
    result = lagrange_interpolation();
    return Py_BuildValue("(ddd)",result.p[0],result.p[1],result.p[2]);
}

//Estructura que asocia nombre de funciones en Python
//con su respectivo wrapper.
//Ejemplo, en Python ejecuto "fact" y se ejecutara 'wrap_fact'
static PyMethodDef lagrangeMethods[] = {
    {"lagrange_interpolation", wrap_lagrange_interpolation, METH_VARARGS, "Execute a shell command."},
    { NULL, NULL}
};

static struct PyModuleDef lagrangeModule = {
   PyModuleDef_HEAD_INIT,
   "lagrange",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   lagrangeMethods //Connects to methods
};

PyMODINIT_FUNC
PyInit_lagrange(void) {
    return PyModule_Create(&lagrangeModule);
}