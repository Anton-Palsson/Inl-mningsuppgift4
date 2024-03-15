void setup() {
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(6, OUTPUT);
}


void loop() {
 digitalWrite(13, HIGH);
 delay(100);
 digitalWrite(13, LOW);
 delay(1000);


 digitalWrite(12, HIGH);
 delay(100);
 digitalWrite(12, LOW);
 delay(1000);


  digitalWrite(6, HIGH);
 delay(100);
 digitalWrite(6, LOW);
 delay(1000);


}
