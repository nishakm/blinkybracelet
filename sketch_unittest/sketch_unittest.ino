/*
 * Unit testing for Blinky Bracelet
 */

 /*
  * Blink LED connected to pin 9
  * and GND
  */
void blink9(){
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(1000);
}

/*
 * Blink LED connected to pin 9 and
 * pin 10
 * This means that pin 9 needs to be driven high and pin 10
 * needs to be driven low
 */
void blink9NotGnd(){
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(1000);
}

/*
 * Blink two LEDs connected in parallel
 * LED connected from 9 to 10 goes on
 * LED connected from 10 to 9 goes off
 * Toggle
 */
void blinkPullUpPullDown(){
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
}

/*
 * Blink an 2x2 LED Matrix in this order:
 * 1 2
 * 3 4
 * LED 9-10 is 1
 * LED 10-9 is 2
 * LED 10-11 is 3
 * LED 11-10 is 4
 */
void blink2x2(){
  // set 9 and 10 as outputs and
  // 11 as an input for high impedence state
  pinMode(9, OUTPUT);
  pinMode(11, INPUT);
  // Turn 1 on
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  // Turn 2 on
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  // Now set pin 9 as a high impedence state
  // and set pin 11 as an output
  pinMode(11, OUTPUT);
  pinMode(9, INPUT);
  // Turn 3 on
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  // Turn 4 on
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(1000);
}

/*
 * Turn on 2x2 LED Matrix in this order:
 * 1 2
 * 3 4
 * 1&2 and 3&4 are tied together so
 * this will have to be flickered
 * In addition, because modes are being changed
 * for each LED selection, the loop timings are adjusted
 */
void turnOn2x2(){
  // set 9 and 10 as outputs and 11 as
  // as input for high impedence state
  for (int i=1; i<=900; i++){
    pinMode(9, OUTPUT);
    pinMode(11, INPUT);
    // turn 10 low and flicker 9 on and off
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    delay(1);
    digitalWrite(9, LOW);
    delay(1);
  }
  // turn 1 and 2 on
  for (int i=1; i<=900; i++){
    pinMode(9, OUTPUT);
    pinMode(11, INPUT);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    delay(1);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    delay(1);
  }
  // turn 1, 2 and 3 on
  for (int i=1; i<=600; i++){
    pinMode(9, OUTPUT);
    pinMode(11, INPUT);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    delay(1);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    delay(1);
    pinMode(9, INPUT);
    pinMode(11, OUTPUT);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    delay(1);
  }
  // turn 1, 2, 3 and 4 on
    for (int i=1; i<=500; i++){
    pinMode(9, OUTPUT);
    pinMode(11, INPUT);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    delay(1);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    delay(1);
    pinMode(9, INPUT);
    pinMode(11, OUTPUT);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    delay(1);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(1);
  }
}

void setup() {
  // Change these according to what needs to be tested
  pinMode(9, OUTPUT); //set pin 9 as output
  pinMode(10, OUTPUT); //set pin 10 as output
  pinMode(11, OUTPUT); //set pin 11 as output
}

void loop() {
  turnOn2x2();
}
