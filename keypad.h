#pragma once

#include <Arduino.h>

#include "state.h"

using KeyPressCallback = void(State::*)();
using KeyPressCallback2 = void(*)();

class Keypad
{
public:
  static constexpr const uint8_t key_nums = 5;
  static constexpr const uint8_t key_right = 0;
  static constexpr const uint8_t key_up = 1;
  static constexpr const uint8_t key_down = 2;
  static constexpr const uint8_t key_left = 3;
  static constexpr const uint8_t key_select = 4;

private:
  static constexpr const uint8_t pin_keypad = 0;

  uint16_t key_adc_thresholds[key_nums] = { 70, 240, 420, 620, 880 };

  int8_t _key_pressed = -1;

  int8_t get_key(const int16_t input);

  State** _p_state;
public:
  Keypad(State** p_state) : _p_state(p_state)
  {

  }

  void update();

  KeyPressCallback on_up_pressing = nullptr;
  KeyPressCallback on_down_pressing = nullptr;
  KeyPressCallback on_left_pressing = nullptr;
  KeyPressCallback on_right_pressing = nullptr;
  KeyPressCallback on_select_pressing = nullptr;

  KeyPressCallback2 on_up_pressed = nullptr;
  KeyPressCallback2 on_down_pressed = nullptr;
  KeyPressCallback on_left_pressed = nullptr;
  KeyPressCallback on_right_pressed = nullptr;
  KeyPressCallback on_select_pressed = nullptr;

  KeyPressCallback on_key_released = nullptr;
};