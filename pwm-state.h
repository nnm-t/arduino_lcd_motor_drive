#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "state.h"
#include "pwm.h"

class PWMState : public State
{
	LiquidCrystal& _lcd;
	PWM& _pwm;
	bool _is_pwm_zero_raised = false;

public:
	PWMState(LiquidCrystal& lcd, PWM& pwm) : _lcd(lcd), _pwm(pwm)
	{

	}

	void update() override;

	void update_always();

	void on_right_pressing() override;

	void on_left_pressing() override;

	void on_select_pressing() override;

	void on_key_released() override;
};