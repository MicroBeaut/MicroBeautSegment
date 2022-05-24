


#include "MicroBeautSegment.h"

MicroBeautSegment::MicroBeautSegment(uint8_t const numberOfDigits, uint8_t const numberOfSegments, CommonTypes const commonType) {
  _numberOfDigits = this->Limit<uint8_t>(numberOfDigits, 0, _maxNumberOfDigits);
  _numberOfSegments = this->Limit<uint8_t>(numberOfSegments, 0, _maxNumberOfSegments);
  _commonType = this->Limit<CommonTypes>(commonType, CommonCathode, CommonAnode);

  _buffers = new uint8_t[_numberOfDigits];
  _digitPins = new uint8_t[_numberOfDigits];
  _segmentPins = new uint8_t[_numberOfSegments];

}

void MicroBeautSegment:: DigitPins(uint8_t const digitPins[]) {
  for (uint8_t index = 0; index < _numberOfDigits; index++) {
    _digitPins[index] = digitPins[index];
    pinMode(_digitPins[index], OUTPUT);
    this->InternalDigitWrite(index, !_commonType);
  }
}


void MicroBeautSegment::SegmentPins(uint8_t const segmentPins[]) {
  for (uint8_t index = 0; index < _numberOfSegments; index++) {
    _segmentPins[index] = segmentPins[index];
    pinMode(_segmentPins[index], OUTPUT);
    this->InternalSegmentWrite(index, _commonType);
  }
}

void MicroBeautSegment::BeginInit() {
  this->InternalInit();
}

void MicroBeautSegment::InternalInit() {
  _digitIndex = 0;
  _turnOnState = true;
  this->BufferWrite(0);
}



void MicroBeautSegment::InternalDigitWrite(bool const value) {
  for (uint8_t index = 0; index < _numberOfDigits; index++) {
    this->InternalDigitWrite(index, value);
  }
}

void MicroBeautSegment::InternalDigitWrite(uint8_t const index, bool const value) {
  digitalWrite(_digitPins[index], value);
}

void MicroBeautSegment::InternalSegmentWrite(bool const value) {
  for (uint8_t index = 0; index < _numberOfDigits; index++) {
    this->InternalDigitWrite(index, value);
  }
}

void MicroBeautSegment::InternalSegmentWrite(uint8_t const index, bool const value) {
  digitalWrite(_segmentPins[index], value);
}


void MicroBeautSegment::BufferWrite(uint8_t const value) {
  for (uint8_t index = 0; index < _numberOfDigits; index++) {
    _buffers[index] = value;
  }
}

void MicroBeautSegment::BufferWrite(uint8_t const index, uint8_t const value) {
  _buffers[index] = value;
}

void MicroBeautSegment::SegmentWrite(uint16_t const value, uint8_t base) {
  uint16_t val = value;
  uint8_t index = 0;
  do {
    _buffers[index++] = fontCode[val % base];
    val /= base;
  } while ( val > 0);
  while (index < _numberOfDigits) {
    _buffers[index++] = 0;
  }
}

void MicroBeautSegment::Refresh() {
  if (_turnOnState) {
    this->InternalSegmentTurnOn();
  } else {
    this->InternalSegmentTurnOff();
    _digitIndex = (_digitIndex + 1) % _numberOfDigits;
  }
  _turnOnState = !_turnOnState;
}

void MicroBeautSegment::InternalSegmentTurnOn() {
  uint8_t value = _buffers[_digitIndex];
  for (uint8_t index = 0; index < _numberOfSegments; index++) {
    bool bitValue = bitRead(value, index);
    if (bitValue) {
      this->InternalSegmentWrite(index, !_commonType);
    } else {
      this->InternalSegmentWrite(index, _commonType);
    }
  }
  this->InternalDigitWrite(_digitIndex, _commonType);
}

void MicroBeautSegment::InternalSegmentTurnOff() {
  this->InternalDigitWrite(_digitIndex, !_commonType);
}


template <typename T>
T MicroBeautSegment::Limit(T const value, T const minLimit, T const maxLimit) {
  if (value < minLimit) return minLimit;
  if (value > maxLimit) return maxLimit;
  return value;
}