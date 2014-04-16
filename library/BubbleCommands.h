/**************************************************************************/
/*
    file:     BubbleCommands.h
    author:   C. Schnarel
    license:  Beerware
	
    This is part of an Arduino library to interface with the hp "Bubble Display"
    (4-digit, 7-segment LED display) controller which is connected via
    the I2C bus.

    Display controller I2C device interprocessor commands definition

    (c) Copyright 2014 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uChip/BubbleDisplay

	@section  HISTORY

    2014-Apr  - First release, C. Schnarel
*/
/**************************************************************************/

// Command definitions
#define LED_CLEARDISPLAY   0x10
#define LED_HOMECURSOR     0x20
#define LED_HOMESCROLL     0x30
#define LED_DISPLAYON      0x40
#define LED_DISPLAYOFF     0x50
#define LED_SCROLLLEFT     0x60
#define LED_SCROLLRIGHT    0x70
#define LED_SETCURSOR      0x80
#define LED_SETSCROLL      0x90
#define LED_CREATECHAR     0xA0
#define LED_DATA           0xB0
#define LED_RESTART        0xF0

