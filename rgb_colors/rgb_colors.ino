/*
Adafruit Arduino - Lesson 3. RGB LED
*/

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

int delay_time = 500;
void loop()
{
  /*
  Serial.print("red\n");
  setColor(255, 0, 0);  // red
  delay(delay_time);

  Serial.print("green\n");
  setColor(0, 255, 0);  // green
  delay(delay_time);

  Serial.print("blue\n");
  setColor(0, 0, 255);  // blue
  delay(delay_time);

  Serial.print("yellow\n");
  setColor(255, 255, 0);  // yellow
  delay(delay_time);

  Serial.print("purple\n");
  setColor(80, 0, 80);  // purple
  delay(delay_time);

  Serial.print("aqua\n");
  setColor(0, 255, 255);  // aqua
  delay(delay_time);

  Serial.print("acutal yellow\n");
  analogWrite(redPin, 80);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 80); 
  delay(delay_time);
  */

  for (int r = 0; r < 255; r += 50) {
    for (int g = 0; g < 255; g += 50) {
      for (int b = 0; b < 255; b += 50) {
        if (digitalRead(13) == HIGH) {
          String toprint = String("R: ") + r + ", G: " + g + ", B: "+ b;
          Serial.println(toprint);
          analogWrite(redPin, r);
          analogWrite(greenPin, g);
          analogWrite(bluePin, b); 
          delay(delay_time);
        } else {
          delay(delay_time);
        }
      }
    }
  }
}

/*
 * YELLOW R: 50, G: 0, B: 150
 * yellow too R: 100, G: 0, B: 100
 * 
 * yellow-green R: 150, G: 50, B: 150
 * 
 * PURPLE R: 150, G: 200, B: 100
 * also purple? R: 50, G: 0, B: 0
 * also purple? R: 100, G: 50, B: 0
 * purp??? R: 50, G: 50, B: 0
 * light purple R: 200, G: 100, B: 100
 * purple R: 50, G: 100, B: 0

 * 
 * WHITE  R: 100, G: 0, B: 50
 * also white R: 200, G: 50, B: 100
 * 
 * Close to green R: 150, G: 0, B: 150
 * some other green R: 250, G: 100, B: 200
 * 
 * blueish R: 250, G: 0, B: 100
 * light blue R: 250, G: 0, B: 150
 * 3 blues: R: 250, G: 0, B: 0
 *          R: 250, G: 0, B: 50
 *          R: 250, G: 0, B: 100





 */

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
