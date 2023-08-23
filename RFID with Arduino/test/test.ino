String id;
void setup() {
  Serial.begin(9600);
  pinMode(6,OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    id = Serial.readString();
    Serial.println(id);
          digitalWrite(6,HIGH);
    delay(1000);
    
  }

}
