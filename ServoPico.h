#ifndef SERVO_PICO_H
#define SERVO_PICO_H

#include <Arduino.h>
#include <stdint.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

class ServoPico {
  public:
    ServoPico();

    bool attach(uint8_t pin, uint16_t minUs = 1000, uint16_t maxUs = 2000, uint16_t freqHz = 50);
    void detach();

    void write(int16_t angle);               // Angle dalam derajat: 0 - 180
    void writeMicroseconds(uint16_t us);     // Durasi pulsa dalam mikrodetik

    int16_t read() const;                    // Membaca sudut terakhir (0 - 180)
    uint16_t readMicroseconds() const;       // Membaca durasi pulsa terakhir

    bool attached() const;

  private:
    uint8_t _pin;
    uint _slice;
    uint _channel;
    uint16_t _minUs;
    uint16_t _maxUs;
    uint16_t _top;
    uint16_t _lastUs;
    int16_t _lastAngle;
    bool _isAttached;

    void setPWM(uint16_t us);
};

#endif
