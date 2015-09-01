#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR
#endif

#define PIN_MATRIX 2
#define PIN_LASER 4
#define PIN_SOUND A0
#define SOUND_DIV 64

#define XPOS 0
#define YPOS 1
#define DELTAY 2

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN_MATRIX,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  pinMode(PIN_LASER, OUTPUT);
  //analogReference(INTERNAL2V56);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  delay(500);
}

int x    = matrix.width();
int colPos = 0;
int soundValue = 0;
int color = 0;

void loop() {
  digitalWrite(PIN_LASER, HIGH);
  soundValue = analogRead(PIN_SOUND);
  matrix.setBrightness((soundValue / 10)+10);
  soundValue = soundValue / SOUND_DIV;
  if (soundValue > 7) soundValue = 7;
  matrix.drawLine(colPos,0,colPos,7,matrix.Color(0,0,0));
  matrix.drawLine(colPos,soundValue,colPos,soundValue,Wheel(color));
  matrix.show();
  colPos++;
  if (colPos >= x) colPos = 0;
  if (soundValue > 1) digitalWrite(PIN_LASER, LOW);
  delay(5);
  color = color + soundValue;
  if (color > 255) color = color - 256;
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
