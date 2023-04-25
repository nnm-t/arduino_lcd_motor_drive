#pragma once

#include <Arduino.h>

class PWM
{
  static constexpr const uint8_t pin_pwm_forward = 3;
  static constexpr const uint8_t pin_pwm_reverse = 11;

  static constexpr const int16_t pwm_max = 255;
  static constexpr const int16_t pwm_stop = 0;
  static constexpr const int16_t pwm_min = -255;
  static constexpr const int16_t pwm_step = 5;

  int16_t _pwm_output = 0;

public:
	PWM();

	void begin();

	void update();

	void up_duty();

	void down_duty();

	void stop_duty();

	int16_t get_output();
};