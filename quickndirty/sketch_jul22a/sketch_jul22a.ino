#include <Adafruit_NeoPixel.h>

#define N_LEDS 13
#define PIN     1
#define UNCONNECTED 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void setup() {
  strip.begin();
  strip.show();
  randomSeed(analogRead(UNCONNECTED));
}

int pos = 0, dir = 1; // Position, direction of "eye"

void loop() {

  //turnOn(10);
  twinkleLoop(10, 5);
  rainbowFade2White(10,10,1);
  goDark(1000);
}

/*
 * unit tests
 */
// test individual pixel
void testEach(int pixel){
  // random color
  uint32_t magenta = strip.Color(64, 64, 64);
  uint32_t nothing = strip.Color(0, 0, 0);
  strip.setPixelColor(pixel, magenta);
  strip.show();
  delay(1000);
  strip.setPixelColor(pixel, nothing);
  strip.show();
}

// test all the pixels one by one
void testAll(){
  for(int i=0; i<strip.numPixels(); i++){
    testEach(i);
  }
}

/*
 * Light show
 */

// reset
void goDark(int wait){
  for(int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
  delay(wait);
}
 
// turn on all lights gently
void turnOn(int wait){
  // white light but not very bright
  uint8_t red = 65;
  uint8_t blue = 65;
  uint8_t green = 65;
  // get a random number of lights
  int numLights = (int) random(5, 8);
  int count = 0;
  while(count <= numLights){
    // get a random light
    int pixel = (int) random(0, strip.numPixels());
    for(uint8_t b=0; b<255; b++){
      strip.setPixelColor(pixel, 65*b/255, 65*b/255, 65*b/255);
      strip.show();
      delay(wait);
    }
    count++;
  }
}

// twinkle a set of lights on and off
void twinkle(uint8_t wait) {
  // white light
  uint8_t red = 65;
  uint8_t green = 65;
  uint8_t blue = 65;
  // pick a random set of lights
  int numLights = (int) random(3, 6);
  int count = 0;
  int lights[numLights];
  while(count < numLights){
    lights[count] = (int) random(0, strip.numPixels());
    count++; 
  }
  
  for(uint8_t b = 0; b <255; b++) {
    for(int i=0; i<numLights; i++){
      strip.setPixelColor(lights[i], red * b/255, green * b/255, blue * b/255);
    }
    strip.show();
    delay(wait);
  };

  for(uint8_t b=255; b > 0; b--) {
    for(int i=0; i<numLights; i++){
      strip.setPixelColor(lights[i], red * b/255, green * b/255, blue * b/255);
    }
    strip.show();
    delay(wait);
  };
};

// twinkle loop
void twinkleLoop(int number, uint8_t wait){
  for(int i=0; i<=number; i++){
    twinkle(wait);
  }
}


// from neopixel lib because I couldn't figure it out on time
void rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< strip.numPixels(); i++) {

        wheelVal = Wheel(((i * 256 / strip.numPixels()) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);

        strip.setPixelColor( i, strip.Color( redVal, greenVal, blueVal ) );

      }

      //First loop, fade in!
      if(k == 0 && fadeVal < fadeMax-1) {
          fadeVal++;
      }

      //Last loop, fade out!
      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
          fadeVal--;
      }

        strip.show();
        delay(wait);
    }
  
  }



  delay(500);


  for(int k = 0 ; k < whiteLoops ; k ++){

    for(int j = 0; j < 256 ; j++){

        for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0, neopix_gamma[j] ) );
          }
          strip.show();
        }

        delay(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0, neopix_gamma[j] ) );
          }
          strip.show();
        }
  }

  delay(500);


}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
