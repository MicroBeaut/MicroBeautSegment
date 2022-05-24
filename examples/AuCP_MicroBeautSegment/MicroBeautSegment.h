


#ifndef __MICROBEAUTSEGMENT_H__
#define __MICROBEAUTSEGMENT_H__

#include "Arduino.h"


enum CommonTypes {
  CommonCathode = false,
  CommonAnode = true
};

const uint8_t fontCode[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                              0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
                             };

class MicroBeautSegment
{
    // constant
  private:
    const uint8_t _maxNumberOfDigits = 8;
    const uint8_t _maxNumberOfSegments = 8;

    // variable
  private:
    uint8_t _numberOfSegments;
    uint8_t _numberOfDigits;
    CommonTypes _commonType;


    uint8_t* _buffers;
    uint8_t* _digitPins;
    uint8_t* _segmentPins;

    uint8_t _digitIndex;
    bool _turnOnState;

    // function
  private:
    void InternalInit();
    void InternalDigitWrite(bool const value);
    void InternalDigitWrite(uint8_t const index, bool const value);
    void InternalSegmentWrite(bool const value);
    void InternalSegmentWrite(uint8_t const index, bool const value);


    void InternalSegmentTurnOn();
    void InternalSegmentTurnOff();


    template <typename T>
    T Limit(T const value, T const minLimit, T const maxLimit);

  public:
    MicroBeautSegment(uint8_t const numberOfDigits, uint8_t const numberOfSegments, CommonTypes const commonType = CommonCathode);
    void DigitPins(uint8_t const digitPins[]);
    void SegmentPins(uint8_t const segmentPins[]);
    void BeginInit();
    void SegmentWrite(uint16_t const value, uint8_t base = DEC);
    void BufferWrite(uint8_t const value);
    void BufferWrite(uint8_t const index, uint8_t const value);

    void Refresh();

};

#endif //__MICROBEAUTSEGMENT_H__