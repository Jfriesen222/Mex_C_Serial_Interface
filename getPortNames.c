#include <math.h>
#include <matrix.h>
#include <mex.h>
#include <stdint.h>
#include "c_serial.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    const char** allPortList;
    allPortList = c_serial_get_serial_ports_list();
    int i = 0;
    int n;
    while(allPortList[i] != NULL){
//         mexPrintf(allPortList[i]);
//         mexPrintf("\r\n");
        i++;        
    }
    n = i;
    i=0;
    while(i<nlhs){
        if(i>=n){
            plhs[i] = mxCreateString("No more ports found");
        }
        else{
            plhs[i] = mxCreateString(allPortList[i]);
        }
        i++;
    }
    c_serial_free_serial_ports_list(allPortList);   
}
