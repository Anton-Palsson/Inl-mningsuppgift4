

//STRÖM BERKÄKNINGAR, I = (5V - 1.8V) / 220Ω = 14.5mA För en grön lysdiod: I = (5V - 2.1V) / 220Ω = 13.2mA För en blå lysdiod: I = (5V - 3.3V) / 220Ω = 7.7mA För Röd lysdiod



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
