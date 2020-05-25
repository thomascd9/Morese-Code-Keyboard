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

enum state_t { waiting, reading, dot, dash };
state_t state = waiting;
state_t prev_state = reading;
unsigned long press_start = 0;
unsigned long read_end = 0;
String seq = "";

void loop() {
  unsigned long curr_time = millis();

  // STATE MACHINE FOR READING
  if (digitalRead(BUTTON_PIN) == DEPRESSED) {
    if (state == waiting || state == reading) {
      press_start = millis();
      state = dot;
    } else if (state == dot) {
      if (curr_time > press_start + dot_time) {
        state = dash;
      }
    }
  } else {
    if (state == dot) {
      // Serial.print(".");
      seq = seq + ".";
      state = reading;
      read_end = curr_time;
    } else if (state == dash) {
      // Serial.print("_");
      seq = seq + "_";
      state = reading;
      read_end = curr_time;
    } else if (state == reading) {
      if (curr_time > read_end + word_interval) {
        Serial.print(morseToChar(seq));
        // Arduino Uno does not by default do keyboard emulation
        //  to use with Arduino Leonardo/ other, change it to Keyboard.print
        //  and add Keyboard.begin() in setup().
        seq = "";
        state = waiting;
        // Serial.print('\n');
      }
    }
  }

  // Update LED if necessary
  if (prev_state != state) {
    turnOffAllLEDs();
    if (state == waiting) {
      digitalWrite(BLUE_LED, ON);
    } else if (state == reading) {
      digitalWrite(GREEN_LED, ON);
    } else if (state == dot) {
      digitalWrite(RED_LED, ON);
    } else if (state == dash) {
      analogWrite(RED_LED, 50);
      analogWrite(GREEN_LED, 0);
      analogWrite(BLUE_LED, 150); 
    }
    prev_state = state;
  }
}

void turnOffAllLEDs() {
    digitalWrite(RED_LED, OFF);
    digitalWrite(GREEN_LED, OFF);
    digitalWrite(BLUE_LED, OFF);
}
char morseToChar(String seq) {
  if (seq == "._") {
    return 'a';
  } else if (seq == "_...") {
    return 'b';
  } else if (seq == "_._.") {
    return 'c';
  } else if (seq == "_..") {
    return 'd';
  } else if (seq == ".") {
    return 'e';
  } else if (seq == ".._.") {
    return 'f';
  } else if (seq == "__.") {
    return 'g';
  } else if (seq == "....") {
    return 'h';
  } else if (seq == "..") {
    return 'i';
  } else if (seq == ".___") {
    return 'j';
  } else if (seq == "_._") {
    return 'k';
  } else if (seq == "._..") {
    return 'l';
  } else if (seq == "__") {
    return 'm';
  } else if (seq == "_.") {
    return 'n';
  } else if (seq == "___") {
    return 'o';
  } else if (seq == ".__.") {
    return 'p';
  } else if (seq == "__._") {
    return 'q';
  } else if (seq == "._.") {
    return 'r';
  } else if (seq == "...") {
    return 's';
  } else if (seq == "_") {
    return 't';
  } else if (seq == ".._") {
    return 'u';
  } else if (seq == "..._") {
    return 'v';
  } else if (seq == ".__") {
    return 'w';
  } else if (seq == "_.._") {
    return 'x';
  } else if (seq == "_.__") {
    return 'y';
  } else if (seq == "__..") {
    return 'z';
  } else if (seq == ".____") {
    return '1';
  } else if (seq == "..___") {
    return '2';
  } else if (seq == "...__") {
    return '3';
  } else if (seq == "...._") {
    return '4';
  } else if (seq == ".....") {
    return '5';
  } else if (seq == "_....") {
    return '6';
  } else if (seq == "__...") {
    return '7';
  } else if (seq == "___..") {
    return '8';
  } else if (seq == "____.") {
    return '9';
  } else if (seq == "_____") {
    return '0';
  } else {
    return '#'; // Error character
  }
}
