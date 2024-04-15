#define LED_PING 13
#define LED_PINR 12
#define BUTTON_PINR 2
#define BUTTON_PING 3

volatile unsigned long lastTimeButtonStateChangedR = millis();
volatile unsigned long lastTimeButtonStateChangedG = millis();
volatile unsigned long debounceDurationR = 50; // milli
volatile unsigned long debounceDurationG = 50; // milli

byte lastButtonStateR = LOW;
byte lastButtonStateG = LOW;
byte ledStateR = LOW;
byte ledStateG = LOW;

bool buttonEnabledR = true;
bool buttonEnabledG = true;
bool potentiometerEnabled = true;

void buttonInterrupt1() {
  if (buttonEnabledG && (millis() - lastTimeButtonStateChangedG >= debounceDurationG)) {
    byte buttonStateG = digitalRead(BUTTON_PING);
    if (buttonStateG != lastButtonStateG) {
      lastTimeButtonStateChangedG = millis();
      lastButtonStateG = buttonStateG;
      if (buttonStateG == LOW) {
        ledStateG = !ledStateG;
        digitalWrite(LED_PING, ledStateG);
      }
    }
  }
}

void buttonInterrupt2(){
  if (buttonEnabledR && (millis() - lastTimeButtonStateChangedR >= debounceDurationR)) {
    byte buttonStateR = digitalRead(BUTTON_PINR);
    if (buttonStateR != lastButtonStateR) {
      lastTimeButtonStateChangedR = millis();
      lastButtonStateR = buttonStateR;
      if (buttonStateR == LOW) {
        ledStateR = !ledStateR;
        digitalWrite(LED_PINR, ledStateR);
      }
    }
  }

}

void setup() {
  pinMode(LED_PINR, OUTPUT);
  pinMode(BUTTON_PINR, INPUT_PULLUP);
  pinMode(LED_PING, OUTPUT);
  pinMode(BUTTON_PING, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
  lastButtonStateR = digitalRead(BUTTON_PINR);
  lastButtonStateG = digitalRead(BUTTON_PING);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PING), buttonInterrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PINR), buttonInterrupt2, CHANGE);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println("Received command: " + command);
    
    if (command.startsWith("ledon")) {
      int ledNum = command.substring(5).toInt();
      Serial.print("Extracted LED number: ");
      Serial.println(ledNum);
      switch (ledNum) {
        case 12:
          digitalWrite(12, HIGH);
          Serial.println("LED 12 turned on");
          break;
        case 13:
          digitalWrite(13, HIGH);
          Serial.println("LED 13 turned on");
          break;
        default:
          Serial.println("Unknown LED number");
          break;
      }
    } else if (command.startsWith("ledoff")) {
      int ledNum = command.substring(6).toInt();
      Serial.print("Extracted LED number: ");
      Serial.println(ledNum);
      switch (ledNum) {
        case 12:
          digitalWrite(12, LOW);
          Serial.println("LED 12 turned off");
          break;
        case 13:
          digitalWrite(13, LOW);
          Serial.println("LED 13 turned off");
          break;
        default:
          Serial.println("Unknown LED number");
          break;
      }
    } else if (command.startsWith("ledpwm")) {
      int pwmLevel = command.substring(6).toInt();
      Serial.print("Extracted PWM level: ");
      Serial.println(pwmLevel);
      if (pwmLevel >= 0 && pwmLevel <= 255) {
        analogWrite(6, pwmLevel);
        Serial.println("PWM level adjusted via serial command");
      } else {
        Serial.println("Invalid PWM level");
      }
    } else if (command.startsWith("enablebutton")) {
      int buttonNum = command.substring(12).toInt();
      Serial.print("Extracted button number: ");
      Serial.println(buttonNum);
      switch (buttonNum) {
        case 1:
          buttonEnabledR = true;
          Serial.println("Button 1 enabled");
          break;
        case 2:
          buttonEnabledG = true;
          Serial.println("Button 2 enabled");
          break;
        default:
          Serial.println("Unknown button number");
          break;
      }
    } else if (command.startsWith("disablebutton")) {
      int buttonNum = command.substring(13).toInt();
      Serial.print("Extracted button number: ");
      Serial.println(buttonNum);
      switch (buttonNum) {
        case 1:
          buttonEnabledR = false;
          Serial.println("Button 1 disabled");
          break;
        case 2:
          buttonEnabledG = false;
          Serial.println("Button 2 disabled");
          break;
        default:
          Serial.println("Unknown button number");
          break;
      }
    } else if (command.startsWith("enablepotentiometer")) {
      potentiometerEnabled = true;
      Serial.println("Potentiometer enabled");
    } else if (command.startsWith("disablepotentiometer")) {
      potentiometerEnabled = false;
      Serial.println("Potentiometer disabled");
    } else {
      Serial.println("Unknown command");
    }
  }

  if (potentiometerEnabled) {
    int potValue = analogRead(A0);
    analogWrite(6, map(potValue, 0, 1023, 0, 255));
  }
}

//ledon n, ledoff n, ledpwm, enable/disablepotentiometer/button1/2
