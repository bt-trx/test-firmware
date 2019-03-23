/*
  Software serial multple serial test
WT32i:
TX: Pin7
RX: Pin8

VREGENA: Pin 12
 */
#define PIN_WT32_ONOFF 20

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial3.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Hello!");
  pinMode(PIN_WT32_ONOFF, OUTPUT);
  digitalWrite(PIN_WT32_ONOFF, HIGH);
}

void loop() { // run over and over
  if (Serial3.available()) {
    Serial.write(Serial3.read());
  }
  if (Serial.available()) {
    Serial3.write(Serial.read());
  }
}
