An interface for faster serial within MATLAB by implementing c_serial code base: 
https://github.com/rm5248/CSerial 
This uses mex functions, so you will need to get the mex compiler within matlab working. I implemented this library to reduce latency and enable high bandwidth communication with an embedded micro-controller connected through a serial port. I have achieved 500 Hz round trip communication with a pic through an ft232r FTDI chip using this interface. 
The example.m file contains brief instructions on how to use this interface. Make sure to compile with mex before trying to run the example (I compiled with visual studio 2013, let me know if people run into compiler errors). I designed the interface to closely resemble using MATLAB's built in serial IO functions. readPort is analogous to fread and writePort is analogous to fwrite in this context.

Remember if you are using an FTDI FT232r (some Arduinos and many other MCUs use this chip) to turn down latency to achieve these speeds as in the following link: https://projectgus.com/2011/10/notes-on-ftdi-latency-with-arduino/

Linux users, let me know if this works for you! Haven't tested yet.
