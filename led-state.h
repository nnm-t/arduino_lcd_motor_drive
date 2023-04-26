#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#include "state.h"

enum class LEDLightingState : uint8_t
{
	Off = 0,
	On = 1,
	Fade = 2,
	Flush = 3
};

class LEDState : public State
{
	static constexpr const uint8_t neopixel_off = 0x00;
	static constexpr const uint8_t neopixel_on = 0x08;
	static constexpr const size_t neopixel_color_num = 9;
	static constexpr const size_t neopixel_state_num = 4;
	static constexpr const uint8_t neopixel_fade_count_max = 0x0F;
	static constexpr const uint8_t neopixel_fade_count_min = 0x00;

	const uint32_t neopixel_colors[neopixel_color_num] = { 0x000000, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0xFFFFFF, 0xe9d366 };
	const char* neopixel_color_name[neopixel_color_num + 1] = {
		"Black ",
		"Red   ",
		"Green ",
		"Blue  ",
		"Yellow",
		"Sky   ",
		"Pink  ",
		"White ",
		"Warm  ",
		"Rainbow"
	};
	const char* neopixel_state_name[neopixel_state_num] = {
		" OFF ",
		"  ON ",
		"Fade ",
		"Flush"
	};

	LiquidCrystal& _lcd;
	Adafruit_NeoPixel& _neopixel;

	LEDLightingState _state = LEDLightingState::Off;
	
	size_t _color_index = 0;
	uint16_t _hue_step = 0;

	bool _is_fade_reverse = false;
	uint8_t _fade_count = 0;

	uint16_t _flush_count = 0;

public:

	LEDState(LiquidCrystal& lcd, Adafruit_NeoPixel& neopixel) : _lcd(lcd), _neopixel(neopixel)
	{

	}

	void update() override;

	void update_always();

	void on_right_pressed() override;

	void on_left_pressed() override;

	void on_select_pressed() override;
};