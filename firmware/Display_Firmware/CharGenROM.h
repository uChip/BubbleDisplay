/* 
  This character generator table has evolved from the table in SevSeg.h (https://github.com/sparkfun/SevSeg) which SparkFun attributes as follows.
    
    Original Library by Dean Reading (deanreading@hotmail.com:
    http://arduino.cc/playground/Main/SevenSegmentLibrary), 2012
    Improvements by Nathan Seidle, 2012

  My changes include removing the PROGMEM attribute (to make the table editable dynamically) adding the DP segment, reversing the segment order to match my hardware and tweaking the character appearances to suit my taste.  Since there don't seem to be any license terms in the earlier files, I won't add any either.

 */

// Character generator for 7-segment displays
uint8_t	chargen[] = {
//  dpGFEDCBA  Segments
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01110111, // 10  "A"
  0b01111100, // 11  "B"
  0b00111001, // 12  "C"
  0b01011110, // 13  "D"
  0b01111001, // 14  "E"
  0b01110001, // 15  "F"
  0b00000000, // 16  NO DISPLAY
  0b00000000, // 17  NO DISPLAY
  0b00000000, // 18  NO DISPLAY
  0b00000000, // 19  NO DISPLAY
  0b00000000, // 20  NO DISPLAY
  0b00000000, // 21  NO DISPLAY
  0b00000000, // 22  NO DISPLAY
  0b00000000, // 23  NO DISPLAY
  0b00000000, // 24  NO DISPLAY
  0b00000000, // 25  NO DISPLAY
  0b00000000, // 26  NO DISPLAY
  0b00000000, // 27  NO DISPLAY
  0b00000000, // 28  NO DISPLAY
  0b00000000, // 29  NO DISPLAY
  0b00000000, // 30  NO DISPLAY
  0b00000000, // 31  NO DISPLAY
  0b00000000, // 32 ' '
  0b10000110, // 33 '!'
  0b00100010, // 34 '"'
  0b00000000, // 35 '#'  NO DISPLAY
  0b00000000, // 36 '$'  NO DISPLAY
  0b00000000, // 37 '%'  NO DISPLAY
  0b00000000, // 38 '&'  NO DISPLAY
  0b00000010, // 39 '''
  0b00111001, // 40 '('
  0b00001111, // 41 ')'
  0b00000000, // 42 '*'  NO DISPLAY
  0b00000000, // 43 '+'  NO DISPLAY
  0b00010000, // 44 ','
  0b01000000, // 45 '-'
  0b10000000, // 46 '.'
  0b00000000, // 47 '/'  NO DISPLAY
  0b00111111, // 48 '0'
  0b00000110, // 49 '1'
  0b01011011, // 50 '2'
  0b01001111, // 51 '3'
  0b01100110, // 52 '4'
  0b01101101, // 53 '5'
  0b01111101, // 54 '6'
  0b00000111, // 55 '7'
  0b01111111, // 56 '8'
  0b01101111, // 57 '9'
  0b00000000, // 58 ':'  NO DISPLAY
  0b00000000, // 59 ';'  NO DISPLAY
  0b00000000, // 60 '<'  NO DISPLAY
  0b00000000, // 61 '='  NO DISPLAY
  0b00000000, // 62 '>'  NO DISPLAY
  0b00000000, // 63 '?'  NO DISPLAY
  0b00000000, // 64 '@'  NO DISPLAY
  0b01110111, // 65 'A'
  0b01111100, // 66 'B'
  0b00111001, // 67 'C'
  0b01011110, // 68 'D'
  0b01111001, // 69 'E'
  0b01110001, // 70 'F'
  0b00111101, // 71 'G'
  0b01110110, // 72 'H'
  0b00000110, // 73 'I'
  0b00001110, // 74 'J'
  0b01110110, // 75 'K'  SAME AS 'H'
  0b00111000, // 76 'L'
  0b00000000, // 77 'M'  NO DISPLAY
  0b01010100, // 78 'N'
  0b00111111, // 79 'O'
  0b01110011, // 80 'P'
  0b01100111, // 81 'Q'
  0b01010000, // 82 'R'
  0b01101101, // 83 'S'
  0b01111000, // 84 'T'
  0b00111110, // 85 'U'
  0b00000000, // 86 'V'  NO DISPLAY
  0b00000000, // 87 'W'  NO DISPLAY
  0b00000000, // 88 'X'  NO DISPLAY
  0b01101110, // 89 'Y'
  0b00000000, // 90 'Z'  NO DISPLAY
  0b00111001, // 91 '['
  0b00000000, // 92 '\'  NO DISPLAY
  0b00001111, // 93 ']'
  0b00000000, // 94 '^'  NO DISPLAY
  0b00001000, // 95 '_'
  0b00100000, // 96 '`'
  0b01110111, // 97 'a' SAME AS CAP
  0b01111100, // 98 'b' SAME AS CAP
  0b01011000, // 99 'c'
  0b01011110, // 100 'd' SAME AS CAP
  0b01111011, // 101 'e'
  0b01110001, // 102 'f' SAME AS CAP
  0b00111101, // 103 'g' SAME AS CAP
  0b01110100, // 104 'h'
  0b00000100, // 105 'i'
  0b00001110, // 106 'j' SAME AS CAP
  0b11110000, // 107 'k' funky attempt
  0b00000110, // 108 'l'
  0b00000000, // 109 'm'  NO DISPLAY
  0b01010100, // 110 'n' SAME AS CAP
  0b01011100, // 111 'o'
  0b01110011, // 112 'p' SAME AS CAP
  0b01100111, // 113 'q' SAME AS CAP
  0b01010000, // 114 'r' SAME AS CAP
  0b01101101, // 115 's' SAME AS CAP
  0b01111000, // 116 't' SAME AS CAP
  0b00011100, // 117 'u'
  0b00000000, // 118 'v'  NO DISPLAY
  0b00000000, // 119 'w'  NO DISPLAY
  0b00000000, // 120 'x'  NO DISPLAY
  0b00000000, // 121 'y'  NO DISPLAY
  0b00000000, // 122 'z'  NO DISPLAY
  0b00000000, // 123 '0b'  NO DISPLAY
  0b00000000, // 124 '|'  NO DISPLAY
  0b00000000, // 125 ','  NO DISPLAY
  0b00000000, // 126 '~'  NO DISPLAY
  0b00000000, // 127 'DEL'  NO DISPLAY
};

