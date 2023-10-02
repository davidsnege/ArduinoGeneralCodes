void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char data_received = Serial.read();
    Serial.write(data_received);
  }
  delay(500);
}
