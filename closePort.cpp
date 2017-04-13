#include <math.h>
#include <matrix.h>
#include <mex.h>
#include <stdint.h>
#include "c_serial.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if(nrhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Please send serial port object.");
    }
    c_serial_port_t* m_port;
    m_port = reinterpret_cast<c_serial_port_t*>(*((uint64_t *)mxGetData(prhs[0])));
    c_serial_free(m_port);
}




//
// template<class base> inline class_handle<base> *convertMat2HandlePtr(const mxArray *in)
// {
//     if (mxGetNumberOfElements(in) != 1 || mxGetClassID(in) != mxUINT64_CLASS || mxIsComplex(in))
//         mexErrMsgTxt("Input must be a real uint64 scalar.");
//     class_handle<base> *ptr = reinterpret_cast<class_handle<base> *>(*((uint64_t *)mxGetData(in)));
//     if (!ptr->isValid())
//         mexErrMsgTxt("Handle not valid.");
//     return ptr;
// }
