#include "pwm.h"

PWM::PWM()
{

}

void PWM::begin()
{
  pinMode(pin_pwm_forward, OUTPUT);
  pinMode(pin_pwm_reverse, OUTPUT);
}

void PWM::update()
{
  if (_pwm_output == pwm_stop)
  {
    analogWrite(pin_pwm_forward, pwm_stop);
    analogWrite(pin_pwm_reverse, pwm_stop);
  }
  else if (_pwm_output > pwm_stop)
  {
    analogWrite(pin_pwm_forward, _pwm_output);
    analogWrite(pin_pwm_reverse, pwm_stop);
  }
  else
  {
    analogWrite(pin_pwm_forward, pwm_stop);
    analogWrite(pin_pwm_reverse, abs(_pwm_output));
  }
}

void PWM::up_duty()
{
	// PWM Duty上げる
	if (_pwm_output < pwm_max)
	{
		_pwm_output += pwm_step;
	}
}

void PWM::down_duty()
{
	// PWM Duty下げる
	if (_pwm_output > pwm_min)
	{
		_pwm_output -= pwm_step;
	}
}

void PWM::stop_duty()
{

	_pwm_output = pwm_stop;
}

int16_t PWM::get_output()
{
	return _pwm_output;
}