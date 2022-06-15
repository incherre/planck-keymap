# Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes
# Random layer
RAND_ENABLE = yes

# Dynamic macros
DYNAMIC_MACRO_ENABLE = yes

# Audio output
AUDIO_ENABLE = yes

# Audio control and System control
EXTRAKEY_ENABLE = yes

# Console for debug
CONSOLE_ENABLE = yes
# Commands for debug and configuration
COMMAND_ENABLE = yes

# Unicode
UNICODEMAP_ENABLE = no
# Virtual DIP switch configuration
BOOTMAGIC_ENABLE = no
# Mouse keys
MOUSEKEY_ENABLE = no
# Backlight functionality
BACKLIGHT_ENABLE = no
# MIDI controls
MIDI_ENABLE = no
# Bluetooth with the Adafruit EZ-Key HID
BLUETOOTH_ENABLE = no
# WS2812 RGB underlight
RGBLIGHT_ENABLE = no
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no

ifeq ($(strip $(RAND_ENABLE)), yes)
    RAND_ENABLE += -DRAND_ENABLE
endif
