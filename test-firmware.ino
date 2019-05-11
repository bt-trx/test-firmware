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

#define PIN_WT32_ONOFF 13
#define PIN_LED0 3
#define PIN_LED1 4
#define PIN_BTN0 23

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial3.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("bt-trx Hardware Test");
  pinMode(PIN_WT32_ONOFF, OUTPUT);
  pinMode(PIN_LED0, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_BTN0, INPUT);

  // Get WT32i out of reset
  digitalWrite(PIN_WT32_ONOFF, HIGH);
}

void loop() { // run over and over
  // Pipe serial data from/to WT32i to USB Serial
  if (Serial3.available()) {
    Serial.write(Serial3.read());
  }
  if (Serial.available()) {
    Serial3.write(Serial.read());
  }

  // If the button is pressed, light up green LED
  // If the button is not pressen, light up blue LED
  if (digitalRead(PIN_BTN0)) {
    digitalWrite(PIN_LED0, LOW);
    digitalWrite(PIN_LED1, HIGH);
  } else {
    digitalWrite(PIN_LED0, HIGH);
    digitalWrite(PIN_LED1, LOW);
  }
}
