#include "led-state.h"

void LEDState::update()
{
	_lcd.setCursor(0, 1);
	_lcd.print(">");

	if (_color_index == neopixel_color_num)
	{
		// ゲーミング色
		for (uint16_t i = 0; i < _neopixel.numPixels(); i++)
		{
			if (_state == LEDLightingState::Flush && i != _flush_count)
			{
				_neopixel.setPixelColor(i, neopixel_colors[0]);
				continue;
			}
			uint16_t hue = _hue_step + i * 65535 / _neopixel.numPixels();
			_neopixel.setPixelColor(i, _neopixel.gamma32(_neopixel.ColorHSV(hue)));
		}

		_hue_step += 1024;
	}
	else
	{
		for (uint16_t i = 0; i < _neopixel.numPixels(); i++)
		{
			if (_state == LEDLightingState::Flush && i != _flush_count)
			{
				_neopixel.setPixelColor(i, neopixel_colors[0]);
				continue;
			}
			_neopixel.setPixelColor(i, neopixel_colors[_color_index]);
		}
	}

	uint8_t brightness = neopixel_off;
	switch (_state)
	{
		case LEDLightingState::On:
			brightness = neopixel_on;
			break;
		case LEDLightingState::Flush:
			brightness = neopixel_on;
			break;
		case LEDLightingState::Fade:
			brightness = _fade_count * neopixel_on / neopixel_fade_count_max;
			break;
		default:
			brightness = neopixel_off;
			break;
	}

	_neopixel.setBrightness(brightness);
	_neopixel.show();

	// Flush用カウント制御
	if (++_flush_count >= _neopixel.numPixels())
	{
		_flush_count = 0;
	}

	// Fade用カウント制御
	if (_is_fade_reverse)
	{
		if (--_fade_count <= neopixel_fade_count_min)
		{
			_is_fade_reverse = false;
		}
		return;
	}

	if (++_fade_count >= neopixel_fade_count_max)
	{
		_is_fade_reverse = true;
	}
}

void LEDState::update_always()
{
	_lcd.setCursor(1, 1);
	_lcd.print("LED");

	_lcd.setCursor(4, 1);
	_lcd.print(neopixel_state_name[static_cast<uint8_t>(_state)]);

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
	switch (_state)
	{
		case LEDLightingState::Off:
			_state = LEDLightingState::On;
			break;
		case LEDLightingState::On:
			_state = LEDLightingState::Fade;
			break;
		case LEDLightingState::Fade:
			_state = LEDLightingState::Flush;
			break;
		default:
			_state = LEDLightingState::Off;
			break;
	}
}