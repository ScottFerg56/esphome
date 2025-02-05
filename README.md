# neotrellis_keypad ESPHome External Component
An External Component for use in ESPHome device YAML files to support the [Adafruit 4x4 NeoTrellis Feather M4 Kit Pack](https://www.adafruit.com/product/4352)
as a button keypad.

## Image of NeoTrellis keypad with custom keycaps:
![Image of NeoTrellis keypad with custom keycaps](NeoTrellis%20Keypad.jpg)

## Features:
* The neotrellis_keypad component provides a platform to allow the 16 lighted buttons of the 4x4 NeoTrellis to interact with the device
and with Home Assistant automations.
* Add a neotrellis_keypad [binary_sensor](https://esphome.io/components/binary_sensor/) for each button to use all the features that class has to offer.
* Add a neotrellis_keypad [light](https://esphome.io/components/light/) for each button to use all the features that class has to offer.
* The neotrellis_keypad also supports the [Key collector component](https://esphome.io/components/key_collector.html).

## Limitations:
* At present, only ONE 4x4 NeoTrellis is supported on the default I2C address. Different configurations are not supported.

## Usage:
Include as an External Component, referencing this GitHub repository.
```
external_components:
  - source: github://ScottFerg56/esphome
    components: [ neotrellis_keypad ]
```
Declare the main keyboard component.
The **keys** value is the only vital option. It must be 16 characters long, one for each button of the 4x4 matrix,
and specifies the **key** to be referenced in the accompanying binary_sensor and light components.
Note that the Adafruit Acrylic Enclosure and Hardware kit has the USB connector sticking out the 'bottom'
when you have the keyboard oriented so that button/light #1 (as referenced on the trellis circuit board)
is at the upper-left corner. I have mine turned 180° so that the USB cable exits out the 'top' and under my
monitor, so I've inverted the **keys** list so I can reference 'A' as the upper-left button.
The **id** value could be referenced to connect buttons and lights with a specific keypad. But at present only
one trellis keypad is supported for a device.
```
neotrellis_keypad:
  id: mykeypad
  keys: "PONMLKJIHGFEDCBA"
```
Add binary_sensor buttons, specifying the neotrellis_keypad platform.
Reference the **key** you want to associate with this button.
You'll want to give it a **name** if you want to reference it from Home Assistant automations.
Note that there are many other features of the **binary_sensor** component class that can be leveraged here!
```
binary_sensor:
  - platform: neotrellis_keypad
    name: "KeyA"
    key: A
  - platform: neotrellis_keypad
    name: "KeyB"
    key: B
```
Add binary_sensor lights, specifying the neotrellis_keypad platform.
Reference the **key** you want to associate with this light.
You'll want to give it a **name** if you want to reference it from Home Assistant automations.
Note that there are many other features of the **light** component class that can be leveraged here!
```
light:
  - platform: neotrellis_keypad
    name: "LightA"
    key: A
  - platform: neotrellis_keypad
    name: "LightB"
    key: B
```
You can rely on Home Assistant automations to control the button lights, or you can code the **on_press**
and **on_release** actions for simpler feedback. This example turns the button light on when it's
pressed and back off when released. The transition time is set shorter than the default 1000ms for
better response. You could also simply toggle the light in the on_press action.
```
binary_sensor:
  - platform: neotrellis_keypad
    name: "KeyP"
    id: keyP
    key: P
    on_press:
      - lambda: id(lightP).turn_on().set_rgb(0.0,0.8,0.0).set_transition_length(100).perform();
    on_release:
      - lambda: id(lightP).turn_off().set_transition_length(100).perform();

light:
  - platform: neotrellis_keypad
    name: "LightP"
    id: lightP
    key: P
```
## Custom Keycaps:
The 'Silicone Elastomer' button cover material provided in the 4x4 NeoTrellis Kit Pack resists
being written on or having anything stuck to it for labeling. So I've designed 3D-printed and customizable keycaps
to fit snugly over the silicone buttons. I've made some in black with transparent icons from
the [Material Design Icons](https://pictogrammers.com/library/mdi/) set (used by HA) that work
well as functional lighted keycaps!

Find them at my [NeoTrellis Keycaps repo](https://github.com/ScottFerg56/NeoTrellis-Keycaps).

