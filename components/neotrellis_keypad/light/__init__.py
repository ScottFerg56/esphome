import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID, CONF_KEY, CONF_OUTPUT_ID
from .. import NeoTrellisKeypad, neotrellis_keypad_ns, CONF_KEYPAD_ID

DEPENDENCIES = ["neotrellis_keypad"]

NeoTrellisKeypadLight = neotrellis_keypad_ns.class_(
    "NeoTrellisKeypadLight", light.LightOutput
)

def check_button(obj):
    if len(obj[CONF_KEY]) != 1:
        raise cv.Invalid("Key must be one character")
    return obj

CONFIG_SCHEMA = cv.All(
    light.RGB_LIGHT_SCHEMA.extend(
        {
            cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(NeoTrellisKeypadLight),
            cv.GenerateID(CONF_KEYPAD_ID): cv.use_id(NeoTrellisKeypad),
            cv.Required(CONF_KEY): cv.string,
        }
    ),
    check_button,
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await light.register_light(var, config)
    neotrellis_keypad = await cg.get_variable(config[CONF_KEYPAD_ID])
    cg.add(var.set_pad(neotrellis_keypad, config[CONF_KEY][0]))
