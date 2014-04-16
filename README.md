# hp Bubble Display Controller  

<img src="https://raw2.github.com/uChip/BubbleDisplay/master/board_front.png" alt="Bubble Display Controller front side" height="250" width="231">___<img src="https://raw2.github.com/uChip/BubbleDisplay/master/board_back.png" alt="Bubble Display Controller back side" height="250" width="231">  

This is the beginning of a board and firmware project supporting hp's 4 digit 7 segment LED bubble display, QDSP-6064, available from [SparkFun](https://www.sparkfun.com/products/12710).  The project is intended to enable a pair of displays to be easily connected over a two-wire I2C bus to a microcontroller (e.g. Arduino).  The board is also an example circuit of how to get reasonable brightness from these small displays.  By having a separate microcontroller driving the display, the burden (I/O pins, code space & CPU cycles) on the main application microcontroller is reduced.


Here is a photo of the functional display.  

<img src="https://raw2.github.com/uChip/BubbleDisplay/master/board_front.jpg" alt="Coming Soon" height="213" width="320">  

This repo includes Eagle CAD PCB design files for the board and ultimately will include the controller firmware.  The board acts as an I2C slave driven from another microcontroller as I2C master.

## Order PCBs  

You can order this PCB directly from OSH Park.  Click on the following link.  
  * Bubble Display Controller - http://oshpark.com/shared_projects/VC1AZwbj  

See Bill of Materials file in repo for parts list.  

## Status  
  * PCB layout has been completed and submitted to fab at Osh Park.  I expect boards back in 10 to 14 days.
  * PCB has not been proven.  Circuit has been prototyped and simulated, so confidence is reasonable, but order PCBs at this time at your own risk.
  * Firmware has not yet been written but there are no new inventions required.  I expect no significant issues and the dedicated microcontroller seems adequate to the task.

## File Formats  

Design files are in "CadSoft EAGLE PCB Design Software" .brd and .sch formats.  
A free version of the software can be downloaded from www.cadsoftusa.com.  

<img src="https://raw.github.com/uChip/BubbleDisplay/master/BubbleDisplay_sch.PNG" alt="schematic" height="401" width="597">  
schematic  

<img src="https://raw.github.com/uChip/BubbleDisplay/master/BubbleDisplay_brd.PNG" alt="PCB" height="405" width="375">  
PCB   

Firmware is developed using the [Arduino](http://arduino.cc/) 1.0.5-r2 IDE and the source files are in Arduino .ino format (and .h or .cpp formats as applicable).

## Distribution License  

You may use this PCB design and firmware however you like but no liability is accepted.  

## Attributions

The hardware design has roots in the SparkFun [RedBoard](https://www.sparkfun.com/products/11575) design.  

The firmware is based on the slave_receiver.ino example and relies upon the wire library from Arduino, both included as part of the Arduino distribution.  The SparkFun tutorial [Using the Serial 7-Segment Display](https://learn.sparkfun.com/tutorials/using-the-serial-7-segment-display) was reviewed with an eye toward creating a compatible interface, but in the end it was decided to implement a driver library instead.  Still the tutorial may have influenced this design.  The BubbleDisplay library interface and code were modeled after the Arduino Liquid Crystal library.


## Notes:

This controller board has no serial port for connecting to the Arduino IDE.  The controller firmware is programed using an ISP programer such as the [Pocket AVR Programer](https://www.sparkfun.com/products/9825) from SparkFun.
