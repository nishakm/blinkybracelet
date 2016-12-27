/*
 * BlinkyBracelet powered by Arduino Uno 3
 * Initial prototype
 * 
 * This is distributed under the "Do What You Want" license
 * author: Nisha K
 * nishakumarx@gmail.com
 */

// struct to store led pin high and pin low
typedef struct{
  int pinHigh;
  int pinLow;
} LED;

// array of leds
// This is assuming the LEDs look like this
// 1 2
// 3 4
LED leds[4] = {{13, 11}, {13, 10}, {12, 11}, {12, 10}};

void setup() {
  // initialize digital PWM pins
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  // This runs in a loop
  for (int i=0; i<4; i++){
    //bring the pinHigh high and the pinLow low
    int pinHigh = leds[i].pinHigh;
    int pinLow = leds[i].pinLow;
    digitalWrite(pinHigh, HIGH);
    digitalWrite(pinLow, LOW);
    delay(1000);
    digitalWrite(pinHigh, LOW);
  }
}
