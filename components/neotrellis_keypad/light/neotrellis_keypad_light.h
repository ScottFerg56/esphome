#pragma once

#include "esphome/components/neotrellis_keypad/neotrellis_keypad.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace neotrellis_keypad {

class NeoTrellisKeypadLight : public light::LightOutput
{
public:
  light::LightTraits get_traits() override
  {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::RGB});
    return traits;
  }

  void write_state(light::LightState *state) override
  {
    if (index_ == -1) // make sure the KEY is valid
      return;
    // just get the RGB from the state and set/show the pixel
    float red, green, blue;
    state->current_values_as_rgb(&red, &green, &blue, false);
    this->pad_->trellis_.pixels.setPixelColor(index_, (uint8_t)(red * 255), (uint8_t)(green * 255), (uint8_t)(blue * 255));
    this->pad_->trellis_.pixels.show();
  }

  void set_pad(NeoTrellisKeypad* pad, uint8_t key)
  {
    pad_ = pad;
    index_ = this->pad_->keys_.find_first_of(key);
  }

  void set_pad(NeoTrellisKeypad* pad, const char *key)
  {
    set_pad(pad, (uint8_t)key[0]);
  }

 protected:
  NeoTrellisKeypad* pad_;
  int index_;
};

}  // namespace neotrellis_keypad
}  // namespace esphome
