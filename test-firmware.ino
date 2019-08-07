/*
This file is part of bt-trx

bt-trx is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

bt-trx is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2019 Christian Obersteiner (DL1COM), Andreas Müller (DC1MIL)
Contact: bt-trx.com, mail@bt-trx.com
*/

//#define TEENSY  // Board: "Teensy 3.2 / 3.1"
#define ESP32     // Board: "Node32s"

#ifdef ESP32  
  #define PIN_WT32_RESET 23 // Active Low
  #define PIN_LED_BLUE 26   // Active High
  #define PIN_LED_GREEN 27  // Active High
  #define PIN_BTN0 25       // Active Low
  #define PIN_PTT_IN 5      // Active Low
  #define PIN_PTT_OUT 6     // Active Low  

  #define SERIAL_DBG Serial
  #define SERIAL_BT Serial2
#endif
#ifdef TEENSY
  #define PIN_WT32_RESET 13 // Active Low
  #define PIN_LED_BLUE 3    // Active High
  #define PIN_LED_GREEN 4   // Active High
  #define PIN_BTN0 23       // Active Low
  #define PIN_PTT_IN 5      // Active Low
  #define PIN_PTT_OUT 6     // Active Low

  #define SERIAL_DBG Serial
  #define SERIAL_BT Serial3
#endif

void setup() {
  // Open serial communications and wait for port to open:
  SERIAL_DBG.begin(115200);

  #ifdef ESP32
    // https://quadmeup.com/arduino-esp32-and-3-hardware-serial-ports/
    SERIAL_BT.begin(115200, SERIAL_8N1, 32, 33);
  #endif
  #ifdef TEENSY
    SERIAL_BT.begin(115200);
    while (!SERIAL_DBG) {
      // wait for serial port to connect. Needed for native USB port only
    }
  #endif

  SERIAL_DBG.println("bt-trx Hardware Test");
  pinMode(PIN_WT32_RESET, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_BTN0, INPUT);
  pinMode(PIN_PTT_IN, INPUT);
  pinMode(PIN_PTT_OUT, OUTPUT);

  digitalWrite(PIN_PTT_OUT, HIGH);

  // Get WT32i out of reset
  digitalWrite(PIN_WT32_RESET, HIGH);
}

void loop() { // run over and over
  // Pipe serial data from/to WT32i to USB Serial
  if (SERIAL_BT.available()) {
    SERIAL_DBG.write(SERIAL_BT.read());
  }
  if (SERIAL_DBG.available()) {
    SERIAL_BT.write(SERIAL_DBG.read());
  }

  // If the button is not pressed, light up green LED
  // If the button is pressed, light up blue LED
  if (digitalRead(PIN_BTN0)) {
    digitalWrite(PIN_LED_BLUE, LOW);    // off
    digitalWrite(PIN_LED_GREEN, HIGH);  // on
  } else {
    digitalWrite(PIN_LED_BLUE, HIGH);   // on
    digitalWrite(PIN_LED_GREEN, LOW);   // off
  }

  // If PTT is pressed, light up blue LED and control PTT out accordingly
  if (digitalRead(PIN_PTT_IN)) {
    digitalWrite(PIN_LED_BLUE, LOW);
    digitalWrite(PIN_PTT_OUT, HIGH);
  } else {
    digitalWrite(PIN_LED_BLUE, HIGH);  
    digitalWrite(PIN_PTT_OUT, LOW);
  }
}
