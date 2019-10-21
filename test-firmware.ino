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

#define ESP32 // TEENSY

#include "pins.h"

ulong result = 0;
ulong counter = 0;

void setup() {
  // Open serial communications and wait for port to open:
  SERIAL_DBG.begin(115200);

  #ifdef ESP32
    // https://quadmeup.com/arduino-esp32-and-3-hardware-serial-ports/
    SERIAL_BT.begin(115200, SERIAL_8N1, PIN_WT32_RX, PIN_WT32_TX);
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
  pinMode(PIN_PTT_LED, OUTPUT);
  pinMode(PIN_HW_VER, INPUT);
  pinMode(PIN_VOX_IN, INPUT);

  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_PTT_LED, LOW);
  digitalWrite(PIN_PTT_OUT, HIGH);

  // Get WT32i out of reset
  digitalWrite(PIN_WT32_RESET, HIGH);

  analogSetPinAttenuation(PIN_VOX_IN, ADC_0db);
}

void loop() { // run over and over
  // Pipe serial data from/to WT32i to USB Serial
  if (SERIAL_BT.available()) {
    SERIAL_DBG.write(SERIAL_BT.read());
  }
  if (SERIAL_DBG.available()) {
    SERIAL_BT.write(SERIAL_DBG.read());
  }

  result += analogRead(PIN_VOX_IN);
  counter += 1;
  if(counter == 30000) {    
    SERIAL_DBG.print("HW_VER: ");
    SERIAL_DBG.print(analogRead(PIN_HW_VER));
    SERIAL_DBG.print("\tVOX_IN: ");
    SERIAL_DBG.println(result/counter);
    
    counter = 0;
    result = 0;
    }

  if (digitalRead(PIN_BTN0)) {
    digitalWrite(PIN_LED_GREEN, LOW);
  } else {
    digitalWrite(PIN_LED_GREEN, HIGH);
  }

  // If PTT is pressed, light up blue LED and control PTT out accordingly
  if (digitalRead(PIN_PTT_IN)) {
    digitalWrite(PIN_LED_BLUE, LOW);
    digitalWrite(PIN_PTT_LED, LOW);
    digitalWrite(PIN_PTT_OUT, HIGH);    
  } else {
    digitalWrite(PIN_LED_BLUE, HIGH);
    digitalWrite(PIN_PTT_LED, HIGH); 
    digitalWrite(PIN_PTT_OUT, LOW);    
  }
}
