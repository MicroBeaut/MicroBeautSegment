/*
  AuCP_SevenSegmentOneDigit.ino
  By MicroBeaut
*/

#define commonAnode   true  // Default Value
#define commonCathode false

#define aPin 7
#define bPin 8
#define cPin 9
#define dPin 11
#define ePin 12
#define fPin 6
#define gPin 5
#define dpPin 13

#define commonPin 10

const bool commonMode = commonAnode;
const uint8_t numberOfSegments = 8;
const uint8_t segmentPins[numberOfSegments] = {aPin, bPin, cPin, dPin, ePin, fPin, gPin, dpPin};
const uint8_t fontCode[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                              0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
                             };

uint8_t count;                             

void DigitWrite(uint8_t const value);
void setup() {
  // put your setup code here, to run once:
  for (uint8_t index = 0; index < numberOfSegments; index++) {
    pinMode(segmentPins[index], OUTPUT);
  }
  pinMode(commonPin, OUTPUT);

  count = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  DigitWrite(count);
  count = (count + 1) % 16;
  delay(500);

  // Thank you

}

void DigitWrite(uint8_t const value) {
  uint8_t val = fontCode[value];
  for (uint8_t index = 0; index < numberOfSegments; index++) {
    bool bitValue = bitRead(val, index);
    if (bitValue) {
      digitalWrite(segmentPins[index], !commonMode);
    } else {
      digitalWrite(segmentPins[index], commonMode);
    }
  }
  digitalWrite(commonPin, commonMode);
}