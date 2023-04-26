#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#include "keypad.h"
#include "pwm.h"
#include "pwm-state.h"
#include "led-state.h"

namespace {
  // LCD
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

  // 未使用ピン (D): 0, 1, 2, 3, 11, 12, 13 (LED)
  // 未使用ピン (A): 1, 2, 3, 4, 5

  // NeoPixel
  // ピン: 12
	constexpr const uint8_t neopixel_num = 10;
  constexpr const uint8_t neopixel_pin = 12;
  Adafruit_NeoPixel neopixel(neopixel_num, neopixel_pin);
  
  // PWM
  // ピン: 3, 11
  PWM pwm;

  // D13 (LED)
  constexpr const uint8_t pin_d13 = 13;
  uint8_t d13_state = LOW;

  // 残りピン
  // DigitalPin: 2 (0, 1: UARTで使用)
  // AnalogPin: 2, 3
  // I2C: 4 (SDA), 5 (SCL)
  // L字XHコネクタで引き出す?

  // 状態管理
  PWMState pwm_state(lcd, pwm);
  LEDState led_state(lcd, neopixel);
  State* p_state = &pwm_state;

  // LCD Keypad Shield
  Keypad keypad(&p_state);
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(pin_d13, OUTPUT);

  keypad.on_up_pressing = &(p_state->on_up_pressing);
  keypad.on_down_pressing = &(p_state->on_down_pressing);
  keypad.on_right_pressing = &(p_state->on_right_pressing);
  keypad.on_left_pressing = &(p_state->on_left_pressing);
  keypad.on_select_pressing = &(p_state->on_select_pressing);

  // keypad.on_up_pressed = &(p_state->on_up_pressed);
  keypad.on_up_pressed = [] { p_state = &pwm_state; };
  // keypad.on_down_pressed = &(p_state->on_down_pressed);
  keypad.on_down_pressed = [] { p_state = &led_state; };
  keypad.on_right_pressed = &(p_state->on_right_pressed);
  keypad.on_left_pressed = &(p_state->on_left_pressed);
  keypad.on_select_pressed = &(p_state->on_select_pressed);

  keypad.on_key_released = &(p_state->on_key_released);

  pwm.begin();

  lcd.begin(16, 2);
  lcd.clear();

  neopixel.begin();
}

void loop()
{
  // LED点滅
  if (d13_state == HIGH)
  {
    digitalWrite(pin_d13, LOW);
    d13_state = LOW;
  }
  else
  {
    digitalWrite(pin_d13, HIGH);
    d13_state = HIGH;
  }

  lcd.clear();

  keypad.update();

  p_state->update();
  pwm_state.update_always();
  led_state.update_always();

  pwm.update();

  delay(50);
}