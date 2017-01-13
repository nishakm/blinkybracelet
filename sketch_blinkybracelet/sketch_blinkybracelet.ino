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
  int pinHiImp1; // we do this because we are charlieplexing
  int pinHiImp2;
  int pinHiImp3;
  int pinHiImp4;
} LED;

/* 
 * Array of leds 
 * This is assuming we are using these lines:
 * 3, 5, 6, 9, 10, 11
 */
LED leds[30] = {{3, 5, 6, 9, 10, 11},
               {5, 3, 6, 9, 10, 11},
               {3, 6, 5, 9, 10, 11},
               {6, 3, 5, 9, 10, 11},
               {3, 9, 5, 6, 10, 11},
               {9, 3, 5, 6, 10, 11},
               {3, 10, 5, 6, 9, 11},
               {10, 3, 5, 6, 9, 11},
               {3, 11, 5, 6, 9, 10},
               {11, 3, 5, 6, 9, 10},
               {5, 6, 3, 9, 10, 11},
               {6, 5, 3, 9, 10, 11},
               {5, 9, 3, 6, 10, 11},
               {9, 5, 3, 6, 10, 11},
               {5, 10, 3, 6, 9, 11},
               {10, 5, 3, 6, 9, 11},
               {5, 11, 3, 6, 9, 10},
               {11, 5, 3, 6, 9, 10},
               {6, 9, 3, 5, 10, 11},
               {9, 6, 3, 5, 10, 11},
               {6, 10, 3, 5, 9, 11},
               {10, 6, 3, 5, 9, 11},
               {6, 11, 3, 5, 9, 11},
               {11, 6, 3, 5, 9, 11},
               {9, 10, 3, 5, 6, 11},
               {10, 9, 3, 5, 6, 11},
               {9, 11, 3, 5, 6, 10},
               {11, 9, 3, 5, 6, 10},
               {10, 11, 3, 5, 6, 9},
               {11, 10, 3, 5, 6, 9}};

/*
 * Reset all LEDs 
 * This means turn all pins into
 * OUTPUT and bring them down to LOW
 */
void reset()
{
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
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
    pinMode(leds[ledNo].pinHiImp1, INPUT);
    pinMode(leds[ledNo].pinHiImp2, INPUT);
    pinMode(leds[ledNo].pinHiImp3, INPUT);
    pinMode(leds[ledNo].pinHiImp4, INPUT);
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
      loopNum = 2500;
      break;
    case 2:
      loopNum = 1500;
      break;
    case 3:
      loopNum = 1300;
      break;
    case 4:
      loopNum = 1100;
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
  int onLeds[noLeds];
  Serial.println("No of leds");
  Serial.println(noLeds);
  // get the first random number
  onLeds[0] = (int) random(1,31);
  Serial.println("--------");
  Serial.println(onLeds[0]);
  int dupes, randNo;
  for (int i=1; i<noLeds; i++)
  {
    // generate a random number
    // that is unique
    do
    {
      randNo = (int) random(1,31);
      dupes = 0;
      for (int j=0; j<i; j++)
      {
        if (onLeds[j] == randNo)
        {
          dupes++;
        }
      }
    } while (dupes > 0);
    
    onLeds[i] = randNo;
    Serial.println(randNo);
  }
  Serial.println("------");
  for (int i=0; i<delayLoop(noLeds); i++)
  {
    turnOn(onLeds, noLeds);
  }
}
