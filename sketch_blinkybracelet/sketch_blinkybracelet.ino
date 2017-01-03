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
void turnOn(int indexArray[], int len)
{ 
  for (int i=0; i<len; i++)
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

/*
 * Return a delay based on the number of LEDs
 * We do this because the time taken to setup
 * the pins increases exponentially as the number
 * of LEDs increase so we cannot set a constant loop
 * number
 */
int delayLoop(int noLeds)
{
  int loopNum = 1000;
  switch(noLeds)
  {
    case 1:
      loopNum = 1500;
      break;
    case 2:
      loopNum = 900;
      break;
    case 3:
      loopNum = 600;
      break;
    case 4:
      loopNum = 500;
      break; 
  }
  return loopNum;
}

void setup()
{
  reset();
  randomSeed(analogRead(A0)); //seed random number generator
  Serial.begin(9600);
}

void loop() {
  // Generate a random number of leds
  int noLeds = (int) random(1,5);
  // Serial port slows things down
  // remove this when tuning for delays is done
  Serial.println(noLeds);
  Serial.println("-------------");
  int onLeds[noLeds];
  for (int i=0; i<noLeds; i++)
  {
    onLeds[i] = i+1;
  }
  for (int i=0; i<delayLoop(noLeds); i++)
  {
    turnOn(onLeds, noLeds);
  }
}
