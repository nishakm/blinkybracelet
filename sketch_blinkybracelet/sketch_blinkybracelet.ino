/*
 * BlinkyBracelet powered by Arduino Uno 3
 * Initial prototype
 * 
 * This is distributed under the "Do What You Want" license
 * author: Nisha K
 * nishakumarx@gmail.com
 */

/*
 * struct to store led pin high and pin low
 */
typedef struct{
  int pinHigh;
  int pinLow;
  int pinHiImp; // we do this because we are charlieplexing
} LED;

/* 
 * Array of leds 
 * This is assuming the LEDs look like this
 * 1 2
 * 3 4
 */
LED leds[4] = {{9, 10, 11}, {10, 9, 11},
               {10, 11, 9}, {11, 10, 9}};

/*
 * Reset all LEDs 
 * This means turn all pins into
 * OUTPUT and bring them down to LOW
 */
void reset()
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW); 
}

/*
 * Turn on a list of LEDs 
 * We need to do a list because the LEDs
 * are all tied together
 */
void turnOn(int indexArray[], int no)
{ 
  for (int i=0; i<no; i++)
  {
    int ledNo = indexArray[i]-1;
    // set pinmode
    pinMode(leds[ledNo].pinHigh, OUTPUT);
    pinMode(leds[ledNo].pinLow, OUTPUT);
    pinMode(leds[ledNo].pinHiImp, INPUT);
    // turn it on
    digitalWrite(leds[ledNo].pinLow, LOW);
    digitalWrite(leds[ledNo].pinHigh, HIGH);
    delay(1);
  }
}

void setup() {
  reset();
}

void loop() {
  // Turn on 1 and 4
  int onLeds[] = {1, 4};
  turnOn(onLeds, sizeof(onLeds));
}
