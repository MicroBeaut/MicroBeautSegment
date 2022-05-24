/*
  AuCP_MicroBeautSegment.ino
  By MicroBeaut
*/



#include "MicroBeautSegment.h"

#define aPin 3
#define bPin 7
#define cPin 10
#define dPin 12
#define ePin 13
#define fPin 4
#define gPin 9
#define dpPin 11

#define digit0Pin 8
#define digit1Pin 6
#define digit2Pin 5
#define digit3Pin 2

#define colonPin A5


const uint8_t numberOfSegments = 8;
const uint8_t segmentPins[numberOfSegments] = {aPin, bPin, cPin, dPin, ePin, fPin, gPin, dpPin};

const uint8_t numberOfDigits = 4;
const uint8_t digitPins[numberOfDigits] = {digit0Pin, digit1Pin, digit2Pin, digit3Pin};


MicroBeautSegment sevenSegment(numberOfDigits, numberOfSegments, CommonAnode);
uint16_t count;

void setup() {
  //Serial.begin(115200);
  sevenSegment.DigitPins(digitPins);
  sevenSegment.SegmentPins(segmentPins);
  sevenSegment.BeginInit();

  for (uint8_t index = 0; index < numberOfDigits; index++) {
    sevenSegment.BufferWrite(index, fontCode[numberOfDigits - index - 1]);
  }
  count = 9990;
  sevenSegment.SegmentWrite(count);
}

void loop() {
  sevenSegment.Refresh();
  if (DelayMilliseconds(1000)) {
    count = (count + 1) % (uint16_t)pow(10, numberOfDigits);
    sevenSegment.SegmentWrite(count);
  }
}

bool DelayMilliseconds(uint16_t const durationMilliseconds) {
  static uint32_t startTime = micros();
  uint32_t currTime = micros();
  uint32_t duration = (uint32_t)durationMilliseconds * 1000;
  if (currTime - startTime < duration) return false;
  startTime = currTime;
  return true;
}