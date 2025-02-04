import esphome.codegen as cg
from esphome.components import key_provider
import esphome.config_validation as cv
from esphome.const import CONF_ID

cg.add_library("Wire", None)
cg.add_library("SPI", None)

cg.add_library(
    name="Adafruit_BusIO",
    repository="https://github.com/adafruit/Adafruit_BusIO",
    version=None,
)

cg.add_library(
    name="Adafruit_Seesaw",
    repository="https://github.com/adafruit/Adafruit_Seesaw",
    version=None,
)

CODEOWNERS = ["@ScottFerg56"]

AUTO_LOAD = ["key_provider"]

MULTI_CONF = True

neotrellis_keypad_ns = cg.esphome_ns.namespace("neotrellis_keypad")
NeoTrellisKeypad = neotrellis_keypad_ns.class_(
    "NeoTrellisKeypad", key_provider.KeyProvider, cg.Component
)
CONF_KEYPAD_ID = "keypad_id"
CONF_KEYS = "keys"

def check_keys(obj):
    if len(obj[CONF_KEYS]) != 16:
        raise cv.Invalid("The number of key codes must be 16")
    return obj

CONFIG_SCHEMA = cv.All(
    cv.COMPONENT_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(NeoTrellisKeypad),
            cv.Required(CONF_KEYS): cv.string,
        }
    ),
    check_keys,
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_keys(config[CONF_KEYS]))
