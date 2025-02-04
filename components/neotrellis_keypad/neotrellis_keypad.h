#pragma once

#include "esphome/components/key_provider/key_provider.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include <cstdlib>
#include <utility>
#include "Adafruit_NeoTrellis.h"
#include "esphome/components/neotrellis_keypad/binary_sensor/neotrellis_keypad_binary_sensor.h"

namespace esphome {
namespace neotrellis_keypad {

class NeoTrellisKeypad : public key_provider::KeyProvider, public Component
{
public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  void set_keys(std::string keys) { keys_ = std::move(keys); };
  void send_key(uint8_t keycode) { this->send_key_(keycode); }
  void register_button(NeoTrellisKeypadBinarySensor *button) { this->buttons_.push_back(button); }

  std::string keys_;            // the KEYS provided in the YAML
  Adafruit_NeoTrellis trellis_; // the underlying hardware

  // list of binary_sensor buttons connected to this keypad
  std::vector<NeoTrellisKeypadBinarySensor *> buttons_{};
};

}  // namespace neotrellis_keypad
}  // namespace esphome
