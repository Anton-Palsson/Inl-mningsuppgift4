int analogPin = A0;
int val = 0;




void setup() {
Serial.begin(9600);
pinMode(analogPin, INPUT);
}




void loop() {
val = analogRead(analogPin);
float voltage = val * (5.0 / 1023.0);
Serial.print("ADC Value: ");
Serial.println(val);
Serial.print("Voltage: ");
Serial.print(voltage);
Serial.println(" V");
 delay(1000);
}
