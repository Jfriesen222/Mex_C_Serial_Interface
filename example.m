%Run these mex commands to build the mex functions before executing this
%example:
%
% mex getPortNames.cpp c_serial.c;
% mex openPort.cpp c_serial.c;
% mex writePort.cpp c_serial.c;
% mex readPort.cpp c_serial.c;
% mex closePort.cpp c_serial.c;

%Need to put n arguments for n ports available you wish to find... probably a cleaner way to
%do this but oh well. 
[name1, name2, name3] = getPortNames; 

%Currently only works with standard baud rate i.e. 9600, 23400, 115200,
%921600 (note I added 921600 for windows only by editing c_serial.h and c_Serial.c so it is
%possible to add more with a bit of editing)
baudrate = 921600;

%Don't mess with this port pointer because once you lose it you can't
%access your serial port anymore. Essentially is just a 64 bit integer that
%stores the pointer value... not sure how this works cross-platform
portPointer = openPort(name1,baudrate);

%String we will print out to serial port
string = '$ Hello World, hope you are well $';

%Must convert to uint8 before sending out data
dataOut = uint8(string); 

%Always use this two argument form where portPointer is untouched from the
%open port and data is a 1d vector of uint8 values to send out data
writePort(portPointer, dataOut);

%Try and read 50 bytes
numBytesToRead = 50;

%This function will access the ports buffer and try to read the number of
%bytes specified by numBytesToRead. This function will timeout in a few
%milliseconds if the buffer has less data then numBytesToRead and will
%return all the contents that were in the buffer upon timeout. If the
%buffer contains more data than numBytesToRead then leftOverBytesInBuffer
%will tell you how many bytes remain in the buffer after the read operation
[dataIn , leftOverBytesInBuffer] = readPort(portPointer, numBytesToRead);

%Close the port when you are all finished... if you forget to close it
%unplugging and replugging the serial device will allow you to re-open the
%device
closePort(portPointer);


