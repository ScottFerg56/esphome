#include "neotrellis_keypad.h"
#include "esphome/core/log.h"

namespace esphome {
namespace neotrellis_keypad {

static const char *const TAG = "neotrellis_keypad";

// single is set in loop() before we read the Trellis so we connect
// to the active instance from the static key callback
// which would become important if we ever support more than one
static NeoTrellisKeypad* single;

TrellisCallback keycb(keyEvent evt)
{
    // we're only activated to see SEESAW_KEYPAD_EDGE_RISING & FALLING here
    // find the button for this key and publish its state
    // publishing also seems to fire all the attached ON_* triggers!
    bool rising = evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING;
    uint8_t keycode = single->keys_[evt.bit.NUM];
    ESP_LOGD(TAG, "key '%c' %s", keycode, rising ? "pressed" : "released");
    // we could possibly see more than one button for a given key!
    for (auto& button : single->buttons_)
    {
        if (button->key_ == keycode)
            button->publish_state(rising);
    }
    if (rising)
        single->send_key(keycode);  // for key_provider/key_collector magic
    return 0;
}

void NeoTrellisKeypad::setup()
{
    trellis_.begin();
    //activate all keys and set callbacks
    for (int i = 0; i < trellis_.pixels.numPixels(); i++)
    {
        trellis_.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
        trellis_.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
        trellis_.registerCallback(i, keycb);
    }
}

void NeoTrellisKeypad::loop()
{
    // this pointer used by the static callback to connect to this instance
    // since we can't have class member functions as callbacks
    single = this;
    trellis_.read();
}

void NeoTrellisKeypad::dump_config()
{
    ESP_LOGCONFIG(TAG, "NeoTrellis Keypad:");
    ESP_LOGCONFIG(TAG, " Keys:");
    ESP_LOGCONFIG(TAG, this->keys_.c_str());
}

}  // namespace neotrellis_keypad
}  // namespace esphome
