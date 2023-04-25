#include "led-state.h"

void LEDState::update()
{
	_lcd.setCursor(0, 1);
	_lcd.print(">");

	if (_color_index == neopixel_color_num)
	{
		// ゲーミング色
		for (uint16_t i = 0; i < neopixel_num; i++)
		{
			uint16_t hue = _hue_step + i * 65535 / neopixel_num;
			_neopixel.setPixelColor(i, _neopixel.gamma32(_neopixel.ColorHSV(hue)));
		}

		_hue_step += 1024;
	}
	else
	{
		for (uint16_t i = 0; i < neopixel_num; i++)
		{
			_neopixel.setPixelColor(i, neopixel_colors[_color_index]);
		}
	}

	_neopixel.setBrightness(_is_led_on ? neopixel_on : neopixel_off);
	_neopixel.show();
}

void LEDState::update_always()
{
	_lcd.setCursor(1, 1);
	_lcd.print("LED");

	_lcd.setCursor(5, 1);
	if (_is_led_on)
	{
		_lcd.print("ON");
	}
	else
	{
		_lcd.print("OFF");
	}

	_lcd.setCursor(9, 1);
	_lcd.print(neopixel_color_name[_color_index]);
}

void LEDState::on_right_pressed()
{
	if (++_color_index >= neopixel_color_num + 1)
	{
		_color_index = 0;
	}
}

void LEDState::on_left_pressed()
{
	if (_color_index <= 0)
	{
		_color_index = neopixel_color_num;
		return;
	}

	_color_index--;
}

void LEDState::on_select_pressed()
{
	if (_is_led_on)
	{
		_is_led_on = false;
	}
	else
	{
		_is_led_on = true;
	}
}