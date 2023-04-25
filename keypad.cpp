#include "keypad.h"

int8_t Keypad::get_key(const int16_t input)
{
  for (int8_t i = 0; i < key_nums; i++)
  {
    if (input < key_adc_thresholds[i])
    {
      return i;
    }
  }

  return -1;
}

void Keypad::update()
{
  const int8_t key_pressing = get_key(analogRead(pin_keypad));

  // キー押しっぱなし
  switch (key_pressing)
  {
    case key_up:
	  if (on_up_pressing != nullptr)
	  {
	    (*_p_state)->on_up_pressing();
	  }
      break;
    case key_down:
	  if (on_down_pressing != nullptr)
	  {
	    (*_p_state)->on_down_pressing();
	  }
      break;
	case key_left:
	  if (on_left_pressing != nullptr)
	  {
	    (*_p_state)->on_left_pressing();
	  }
	  break;
	case key_right:
	  if (on_right_pressing != nullptr)
	  {
	    (*_p_state)->on_right_pressing();
	  }
	  break;
    case key_select:
	  if (on_select_pressing != nullptr)
	  {
	    (*_p_state)->on_select_pressing();
	  }
      break;
    default:
      break;
  }

  if (_key_pressed != key_pressing)
  {
    _key_pressed = key_pressing;

    if (_key_pressed != -1)
    {
      // キー押した (押下時)
	  switch (_key_pressed)
	  {
		case key_up:
		  if (on_up_pressed != nullptr)
		  {
			// (*_p_state)->on_up_pressed();
			on_up_pressed();
		  }
		  break;
		case key_down:
		  if (on_down_pressed != nullptr)
		  {
			// (*_p_state)->on_down_pressed();
			on_down_pressed();
		  }
		  break;
		case key_left:
		  if (on_left_pressed != nullptr)
		  {
			(*_p_state)->on_left_pressed();
		  }
		  break;
		case key_right:
		  if (on_right_pressed != nullptr)
		  {
			(*_p_state)->on_right_pressed();
		  }
		  break;
		case key_select:
		  if (on_select_pressed != nullptr)
		  {
			(*_p_state)->on_select_pressed();
		  }
		  break;
		default:
		  break;
	  }
    }
    else
    {
      // キー離した
	  if (on_key_released != nullptr)
	  {
		(*_p_state)->on_key_released();
	  }
    }
  }
}