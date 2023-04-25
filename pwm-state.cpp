#include "pwm-state.h"

void PWMState::update()
{
	_lcd.setCursor(0, 0);
	_lcd.print(">");
}

void PWMState::update_always()
{
	_lcd.setCursor(1, 0);
	if (_pwm.get_output() > 0)
	{
		_lcd.print("FORWARD");
	}
	else if (_pwm.get_output() < 0)
	{
		_lcd.print("REVERSE");
	}
	else
	{
		_lcd.print("STOP");
	}

	_lcd.setCursor(9, 0);
	_lcd.print("PWM");
	_lcd.setCursor(12, 0);
	_lcd.print(String(_pwm.get_output(), DEC));
}

void PWMState::on_right_pressing()
{
    if (!_is_pwm_zero_raised)
    {
    	 _pwm.up_duty();
    }

    if (_pwm.get_output() == 0)
    {
    	 _is_pwm_zero_raised = true;
    }
}

void PWMState::on_left_pressing()
{
	if (!_is_pwm_zero_raised)
	{
		_pwm.down_duty();
	}

	if (_pwm.get_output() == 0)
	{
		_is_pwm_zero_raised = true;
	}
}

void PWMState::on_select_pressing()
{
	_pwm.stop_duty();
}

void PWMState::on_key_released()
{
	_is_pwm_zero_raised = false;
}