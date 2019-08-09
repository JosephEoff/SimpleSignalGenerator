# SimpleSignalGenerator
A simple Arduino based square wave generator.

This simple signal generator will produce a 1kHz square wave when the Arduino is powered up.

If you connect to it using a serial monitor (PuTTy or the serial monitor in the Arduino IDE) at 115200 baud, then you can send it commands to generate different frequencies.

The generator works for frequencies between 32Hz and 1MHz.  Not all frequencies are allowed - the dividers used for the timer can't be set to generate all frequencies.

The generator accepts only digits and ignores all other typed characters.

The "Enter" key will tell the generator to switch frequencies.

The generator repeats the given command back, then tells you what frequency it is really generating.

Examples:
**Valid frequency**
2000
Command: 2000
Set: 2000

The user typed "2000" and pressed "Enter," then the signal generator verified the command and sent back the frequency as set.

**Invalid frequency**
750000
Command: 750000
Set: 1000000

The user entered 750000Hz (750kHz) and pressed "Enter."  The generator verified the command, then replied back that it had to set the frequency to 1000000Hz (1MHz.) 

The generator can also set its output to high or low.  Just send a 0 for low, or a 1 for high.

Examples:
0
Command: 0
Stopped.  Output 0

1
Command: 1
Stopped.  Output 1


You will need [the Arduino Timer1 library](https://www.arduinolibraries.info/libraries/timer-one) to compile this project.  The instructions for installing the library can be found at the linked site.

