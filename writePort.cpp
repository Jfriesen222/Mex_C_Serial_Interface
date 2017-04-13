#include <math.h>
#include <matrix.h>
#include <mex.h>
#include <stdint.h>
#include "c_serial.h"
static c_serial_port_t* m_port;
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
        if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Please send serial port object and msg.");
    }
    if(nlhs!=0) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","No outputs here.");
    }
    if(mxGetClassID(prhs[1]) != mxUINT8_CLASS){
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","Write data is not a vector of uint8 numbers, please convert.");
    }
    int status;
    int bytes_read;
    int data_length;
    uint8_t *data;
    mwSize total_num_of_elements, index;
    data = (uint8_t *)mxGetData(prhs[1]);
    data_length = mxGetNumberOfElements(prhs[1]);
    m_port = reinterpret_cast<c_serial_port_t*>(*((uint64_t *)mxGetData(prhs[0])));
    int iii;
    status = c_serial_write_data( m_port, data, &data_length );
    if( status < 0 ){
        mexPrintf("can't write data");
    }
}