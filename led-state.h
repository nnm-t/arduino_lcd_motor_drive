#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#include "state.h"

class LEDState : public State
{
	static constexpr const uint8_t neopixel_off = 0x00;
	static constexpr const uint8_t neopixel_on = 0x08;
	static constexpr const size_t neopixel_color_num = 8;

	const uint32_t neopixel_colors[neopixel_color_num] = { 0x000000, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0xFFFFFF };
	const char* neopixel_color_name[neopixel_color_num + 1] = {
		"Black ",
		"Red   ",
		"Green ",
		"Blue  ",
		"Yellow",
		"Sky   ",
		"Pink  ",
		"White ",
		"Rainbow"
	};

	LiquidCrystal& _lcd;
	Adafruit_NeoPixel& _neopixel;
	
	bool _is_led_on = false;
	size_t _color_index = 0;
	uint16_t _hue_step = 0;

public:
	static constexpr const uint8_t neopixel_num = 10;

	LEDState(LiquidCrystal& lcd, Adafruit_NeoPixel& neopixel) : _lcd(lcd), _neopixel(neopixel)
	{

	}

	void update() override;

	void update_always();

	void on_right_pressed() override;

	void on_left_pressed() override;

	void on_select_pressed() override;
};