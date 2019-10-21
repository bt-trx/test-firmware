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

#ifdef ESP32 // Board: "NodeMCU ESP32-DevKitC-32D"
  #define PIN_WT32_RESET 4   // Active Low
  #define PIN_LED_BLUE 25    // Active High
  #define PIN_LED_GREEN 26   // Active High
  #define PIN_BTN0 18        // Active Low
  #define PIN_PTT_IN 32      // Active Low
  #define PIN_PTT_OUT 33     // Active Low  
  #define PIN_PTT_LED 13     // Active High
  #define PIN_WT32_RX 16     // Serial2 Rx
  #define PIN_WT32_TX 17     // Serial2 Tx
  #define PIN_HW_VER 34      // ADC1 CH6
  #define PIN_VOX_IN 35      // ADC1 CH7

  #define SERIAL_DBG Serial
  #define SERIAL_BT Serial2
#endif
#ifdef TEENSY // Board: "Teensy 3.2 / 3.1"
  #define PIN_WT32_RESET 13 // Active Low
  #define PIN_LED_BLUE 3    // Active High
  #define PIN_LED_GREEN 4   // Active High
  #define PIN_BTN0 23       // Active Low
  #define PIN_PTT_IN 5      // Active Low
  #define PIN_PTT_OUT 6     // Active Low

  #define SERIAL_DBG Serial
  #define SERIAL_BT Serial3
#endif