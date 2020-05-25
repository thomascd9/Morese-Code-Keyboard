const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11;

const int BUTTON_PIN = 13;

#define ON HIGH
#define OFF LOW
#define DEPRESSED HIGH

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  turnOffAllLEDs();
  
  pinMode(BUTTON_PIN, INPUT);

  randomSeed(analogRead(0));
}

int state = 0;

void loop() {
  state = digitalRead(BUTTON_PIN);

  if (state == HIGH) {
    digitalWrite(randLED(), ON);
    delay(100);
    turnOffAllLEDs();
  } else {
    turnOffAllLEDs();
  }
}

int randLED() {
  int x = random(0, 3);
  if (x == 0) {
    Serial.print('r');
    return RED_LED;
  } else if (x == 1) {
    Serial.print('g');
    return GREEN_LED;
  } else {
    Serial.print('b');
    return BLUE_LED;
  }
}

void turnOffAllLEDs() {
    digitalWrite(RED_LED, OFF);
    digitalWrite(GREEN_LED, OFF);
    digitalWrite(BLUE_LED, OFF);
}
