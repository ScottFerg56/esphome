import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID, CONF_KEY
from .. import NeoTrellisKeypad, neotrellis_keypad_ns, CONF_KEYPAD_ID

DEPENDENCIES = ["neotrellis_keypad"]

NeoTrellisKeypadBinarySensor = neotrellis_keypad_ns.class_(
    "NeoTrellisKeypadBinarySensor", binary_sensor.BinarySensor
)

def check_button(obj):
    if len(obj[CONF_KEY]) != 1:
        raise cv.Invalid("Key must be one character")
    return obj

# The binary_sensor schema processes all the on_press and on_release triggers.
# Somehow behind the scenes it appears its 'to_code' also runs to 
# create trigger automations and connect them to our state.
# So all we have to do is publish the state in our code and the triggers happen!
# CONSIDER: What other binary_sensor features also lurk behind the scenes!

CONFIG_SCHEMA = cv.All(
    binary_sensor.binary_sensor_schema(NeoTrellisKeypadBinarySensor).extend(
        {
            cv.GenerateID(CONF_KEYPAD_ID): cv.use_id(NeoTrellisKeypad),
            cv.Required(CONF_KEY): cv.string,
        }
    ),
    check_button,
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_KEY][0])
    await binary_sensor.register_binary_sensor(var, config)
    neotrellis_keypad = await cg.get_variable(config[CONF_KEYPAD_ID])
    cg.add(neotrellis_keypad.register_button(var))
