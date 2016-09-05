/*
 * BlinkyBracelet powered by Arduino Uno 3
 * Initial prototype
 * 
 * This is distributed under the "Do What You Want" license
 * author: Nisha K
 * nishakumarx@gmail.com
 */

// declare pins
int matrix[2][2] = {{10,11},{12,13}};

void setup() {
  // initialize digital PWM pins
  for (int i=0; i<2; i++){
    for(int j=0; j<2; j++){
      pinMode(matrix[i][j], OUTPUT);
    }
  }

}

void loop() {
  // This runs in a loop
  for (int i=0; i<2; i++){
    for (int j=0; j<2; j++){
      digitalWrite(matrix[i][j], HIGH);
      delay(500);
      digitalWrite(matrix[i][j], LOW);
    }
  }

}
