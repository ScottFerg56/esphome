#pragma once

//#include "esphome/components/neotrellis_keypad/neotrellis_keypad.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace neotrellis_keypad {

// just a binary_sensor labeled with a key for use by the neotrellis_keypad
// simple here, but there's lots of cool magic in the BinarySensor class!

class NeoTrellisKeypadBinarySensor : public binary_sensor::BinarySensorInitiallyOff {
public:
  NeoTrellisKeypadBinarySensor(uint8_t key) : key_(key){};
  NeoTrellisKeypadBinarySensor(const char *key) : key_((uint8_t) key[0]){};

  uint8_t key_;
};

}  // namespace neotrellis_keypad
}  // namespace esphome
