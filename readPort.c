#include <math.h>
#include <matrix.h>
#include <mex.h>
#include <stdint.h>
#include "c_serial.h"
static c_serial_port_t* m_port;
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Please send serial port object and number of bytes to read.");
    }
    if(nlhs!=1 && nlhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","Serial data output required (optional bytes remaining).");
    }
    int status;
    uint8_t *msgData;               /* output  vector */
    double *bytesLeft;               /* output  vector */
    double *numBytesToRead;
    numBytesToRead = mxGetPr(prhs[1]);
    int data_length;
    int bytes_remaining =0;
    data_length = (int) numBytesToRead[0];
    uint8_t data[255];

    m_port = (c_serial_port_t*)(*((uint64_t *)mxGetData(prhs[0])));
    int iii;
    

    status = c_serial_read_data( m_port, data, &data_length, &bytes_remaining,  NULL);
    if( status < 0 ){
        mexPrintf( "Read Failed\n");
    }
    /* create the output matrix */
    plhs[0] = mxCreateNumericMatrix(1,(mwSize)data_length,mxUINT8_CLASS,mxREAL);
    msgData = (uint8_t *) mxGetData(plhs[0]);
    for (int j = 0; j < data_length; j++)
			msgData[j] = data[j]; 
    if( nlhs==2 ) {
        plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
        bytesLeft = mxGetPr(plhs[1]);
	    bytesLeft[0] = (double) bytes_remaining;
    }
}