const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11;

const int BUTTON_PIN = 13;

#define ON LOW
#define OFF HIGH
#define DEPRESSED HIGH

const int dot_time = 300;
const int word_interval = 750;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  turnOffAllLEDs();
  
  pinMode(BUTTON_PIN, INPUT);

  randomSeed(analogRead(0));
}

enum state_t { waiting, reading, dd };
state_t state = waiting;
unsigned long press_start = 0;
unsigned long read_end = 0;

void loop() {
  unsigned long curr_time = millis();

  // STATE MACHINE FOR READING
  if (digitalRead(BUTTON_PIN) == DEPRESSED) {
    if (state == waiting || state == reading) {
      press_start = millis();
      state = dd;
    }
  } else {
    if (state == dd) {
      if (curr_time > press_start + dot_time) {
        Serial.print('_');
      } else {
        Serial.print('.');
      }
      state = reading;
      read_end = curr_time;
    } else if (state == reading) {
      if (curr_time > read_end + word_interval) {
        state = waiting;
        Serial.print('\n');
      }
    }
  }

  // DISPLAY STATE
  turnOffAllLEDs();
  if (state == waiting) {
    digitalWrite(BLUE_LED, ON);
  } else if (state == reading) {
    digitalWrite(GREEN_LED, ON);
  } else if (state == dd) {
    digitalWrite(RED_LED, ON);
  }
}

void turnOffAllLEDs() {
    digitalWrite(RED_LED, OFF);
    digitalWrite(GREEN_LED, OFF);
    digitalWrite(BLUE_LED, OFF);
}
