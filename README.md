# hp Bubble Display Controller  

<img src="https://raw2.github.com/uChip/BubbleDisplay/master/MPHS_top.png" alt="Bubble Display Controller front side" height="270" width="200">___<img src="https://raw2.github.com/uChip/BubbleDisplay/master/MPHS_bottom.png" alt="Bubble Display Controller back side" height="270" width="200">  

This is the beginning of a board and firmware project supporting hp's 4 digit 7 segment LED bubble display, QDSP-6064, available (soon) from [SparkFun](https://www.sparkfun.com/products/12710).  The project is intended to enable a pair of displays to be easily connected over an I2C bus to a microcontroller (e.g. Arduino).  The board is also an example circuit of how to get reasonable brightness from these small displays.  By having a separate microcontroller driving the display, the burden (I/O pins, code space & CPU cycles) on the main application microcontroller is reduced.


Here is a photo of the functional display.  

<img src="https://raw2.github.com/uChip/BubbleDisplay/master/board_front.jpg" alt="hp Display Controller" height="300" width="200">  

This repo includes Eagle CAD PCB design files for the board and ultimately will include the controller firmware.  The board acts as an I2C slave driven from another microcontroller.

## Order PCBs  

You can order this PCB directly from OSH Park.  Click on the following link.  
  * Radio Breakout - http://oshpark.com/shared_projects/AadEx5fd  

See Bill of Materials file in repo for parts list.  

## Status  
  * PCB layout has been completed and submitted to fab at Osh Park.  I expect boards back in 10 to 14 days.
  * PCB has not been proven.  Circuit has been prototyped and simulated, so confidence is reasonable, but order PCBs at this time at your own risk.
  * Firmware has not yet been written but there are no new inventions required.  I expect no significant issues and the dedicated microcontroller seems adequate to the task.

## File Formats  

Design files are in "CadSoft EAGLE PCB Design Software" .brd and .sch formats.  
A free version of the software can be downloaded from www.cadsoftusa.com.  

<img src="https://raw.github.com/uChip/BubbleDisplay/master/BubbleDisplay_sch.PNG" alt="schematic" height="396" width="531">  
schematic  

<img src="https://raw.github.com/uChip/BubbleDisplay/master/BubbleDisplay_brd.PNG" alt="PCB" height="326" width="244">  
PCB   

Firmware is developed using the Arduino 1..0.5-r2 IDE and the source files are in Arduino .ino format (and .h or .cpp formats as applicable).

## Distribution License  

You may use this PCB design and firmware however you like but no liability is accepted.  

## Notes:

