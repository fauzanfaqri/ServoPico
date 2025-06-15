#include "ServoPico.h"

ServoPico::ServoPico() : _isAttached(false), _lastUs(0), _lastAngle(0) {}

bool ServoPico::attach(uint8_t pin, uint16_t minUs, uint16_t maxUs, uint16_t freqHz) {
  if (freqHz == 0) return false;

  _pin = pin;
  _minUs = minUs;
  _maxUs = maxUs;

  gpio_set_function(_pin, GPIO_FUNC_PWM);
  _slice = pwm_gpio_to_slice_num(_pin);
  _channel = pwm_gpio_to_channel(_pin);

  uint32_t clkHz = clock_get_hz(clk_sys); // default: 125 MHz
  _top = clkHz / freqHz / 1000;           // hitung nilai wrap
  pwm_set_wrap(_slice, _top - 1);
  pwm_set_clkdiv(_slice, 1.0f);
  pwm_set_enabled(_slice, true);

  pwm_set_chan_level(_slice, _channel, 0); // awalnya nol

  _isAttached = true;
  write(90); // default center
  return true;
}

void ServoPico::detach() {
  if (!_isAttached) return;
  pwm_set_chan_level(_slice, _channel, 0);
  pwm_set_enabled(_slice, false);
  _isAttached = false;
}

void ServoPico::write(int16_t angle) {
  angle = constrain(angle, 0, 180);
  _lastAngle = angle;
  _lastUs = map((int32_t)angle, 0, 180, _minUs, _maxUs);
  setPWM(_lastUs);
}

void ServoPico::writeMicroseconds(int32_t us) {
  us = constrain(us, _minUs, _maxUs);
  _lastUs = us;
  _lastAngle = map((int32_t)us, _minUs, _maxUs, 0, 180);
  setPWM(us);
}

int16_t ServoPico::read() const {
  return _lastAngle;
}

uint16_t ServoPico::readMicroseconds() const {
  return _lastUs;
}

bool ServoPico::attached() const {
  return _isAttached;
}

void ServoPico::setPWM(int32_t us) {
  if (!_isAttached) return;
  us = constrain(us, _minUs, _maxUs);
  uint32_t clkHz = clock_get_hz(clk_sys);
  uint32_t cycles = (clkHz / 1000000) * us; // convert us to cycle
  uint16_t level = (cycles * _top) / (clkHz / 50); // pwm frequency = 50Hz
  pwm_set_chan_level(_slice, _channel, level);
}
