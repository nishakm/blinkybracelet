/*
 * BlinkyBracelet powered by Arduino Uno 3
 * Using 3 LEDs in 2 rows
 * This is for debugging a short row of LEDs
 * 
 * author: Nisha K
 * nishakumarx@gmail.com
 */

/*
 * struct to store led pin high and pin low
 * In a 3x2 matrix there are 3 pins
 * One will go High, one will go Low and the
 * third is a high impedence
 */
typedef struct{
  int pinHigh;
  int pinLow;
  int pinHiImp; // we do this because we are charlieplexing
} LED;

/* 
 * Array of leds 
 * This is assuming we are using these lines:
 * 3, 5, 6
 */
LED leds[6] = {{6, 5, 3},
               {5, 6, 3},
               {6, 3, 5}, //row 1
               {5, 3, 6},
               {3, 5, 6},
               {3, 6, 5}}; //row 2

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
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW); 
}

void reset2()
{
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
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
    reset2();
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
      loopNum = 1300;
      break;
    case 2:
      loopNum = 800;
      break;
    case 3:
      loopNum = 500;
      break;
    case 4:
      loopNum = 400;
      break;
    case 5:
      loopNum = 300;
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
  // Generate a random number of leds that will light up
  int noLeds = (int) random(1,4);
  int onLeds[noLeds];
  Serial.println("No of leds");
  Serial.println(noLeds);
  // get the first random number within the total number of leds
  onLeds[0] = (int) random(1,7);
  Serial.println("--------");
  Serial.println(onLeds[0]);
  int dupes, randNo;
  for (int i=1; i<noLeds; i++)
  {
    // generate a random number
    // that is unique
    do
    {
      randNo = (int) random(1,7);
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
