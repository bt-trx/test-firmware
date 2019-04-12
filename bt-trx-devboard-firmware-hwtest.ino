/*
  Hardware test for bt-trx devboard v2
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
  
  digitalWrite(PIN_WT32_ONOFF, HIGH);
}

void loop() { // run over and over
  if (Serial3.available()) {
    Serial.write(Serial3.read());
  }
  if (Serial.available()) {
    Serial3.write(Serial.read());
  }

  if (digitalRead(PIN_BTN0)) {
    digitalWrite(PIN_LED0, LOW);
    digitalWrite(PIN_LED1, HIGH);
  } else {
    digitalWrite(PIN_LED0, HIGH);
    digitalWrite(PIN_LED1, LOW);
  }
}
