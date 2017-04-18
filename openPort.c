#include <math.h>
#include <matrix.h>
#include <mex.h>
#include <stdint.h>
#include "c_serial.h"
static c_serial_port_t* m_port;
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int status;
    char portName[255];
    mxGetString(prhs[0], portName, sizeof(portName));
    double *baudRate;
    baudRate = mxGetPr(prhs[1]);
    if( c_serial_new( &m_port, NULL ) < 0 ){
        mexPrintf("ERROR: Unable to create new serial port\n" );
        return;
    }
//     /*
//      * The port name is the device to open(/dev/ttyS0 on Linux,
//      * COM1 on Windows)
//      */
    mexPrintf((const char*) portName);
    if( c_serial_set_port_name( m_port, (const char*) portName ) < 0 ){
        mexPrintf("ERROR: can't set port name\n" );
    }
//     /*
//      * Set various serial port settings.  These are the default.
//      */
    c_serial_set_baud_rate( m_port,((int)  baudRate[0]));
    c_serial_set_data_bits( m_port, CSERIAL_BITS_8 );
    c_serial_set_stop_bits( m_port, CSERIAL_STOP_BITS_1 );
    c_serial_set_parity( m_port, CSERIAL_PARITY_NONE );
    c_serial_set_flow_control( m_port, CSERIAL_FLOW_NONE );
    mexPrintf( ": Baud rate is %d\n", c_serial_get_baud_rate( m_port ) );
//
//     /*
//      * We want to get all line flags when they change
//      */
//    c_serial_set_serial_line_change_flags( m_port, CSERIAL_LINE_FLAG_ALL );
    status = c_serial_open( m_port );
    if( status < 0 ){
        mexPrintf("ERROR: Can't open serial port\n" );
        return;
    }
    mxArray *out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *((uint64_t *)mxGetData(out)) = (uint64_t)(m_port);
    plhs[0] = out;
}

