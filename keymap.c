#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _LOWER,
  _RAISE
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    QUOTE,
    NINE,
    ZERO,
    SIGN
};

enum unicode_names {
    QSTN,
    WINK,
    EYES,
    RLVD,
    TNGE,
    YEN,
    UPDN,
    IMP,
    OH,
    PRTY,

    AGRY,
    SPKL,
    DSPT,
    FIRE,
    GRIN,
    HRT,
    JANK,
    KISS,
    LGH,
    POOP,

    ZZZ,
    XMRK,
    COOL,
    VMIT,
    BANA,
    NOSE,
    MNKY,
    DOWN,
    UP,
    CHK
};

const uint32_t PROGMEM unicode_map[] = {
    [QSTN] = 0x1F914,
    [WINK] = 0x1F609,
    [EYES] = 0x1F440,
    [RLVD] = 0x1F60C,
    [TNGE] = 0x1F61B,
    [YEN] = 0x1F4B4,
    [UPDN] = 0x1F643,
    [IMP] = 0x1F608,
    [OH] = 0x1F62E,
    [PRTY] = 0x1F973,

    [AGRY] = 0x1F621,
    [SPKL] = 0x2728,
    [DSPT] = 0x1F625,
    [FIRE] = 0x1F525,
    [GRIN] = 0x1F600,
    [HRT] = 0x2764,
    [JANK] = 0x1F615,
    [KISS] = 0x1F618,
    [LGH] = 0x1F923,
    [POOP] = 0x1F4A9,

    [ZZZ] = 0x1F634,
    [XMRK] = 0x274C,
    [COOL] = 0x1F60E,
    [VMIT] = 0x1F92E,
    [BANA] = 0x1F34C,
    [NOSE] = 0x1F443,
    [MNKY] = 0x1F648,
    [DOWN] = 0x1F44E,
    [UP] = 0x1F44D,
    [CHK] = 0x2705
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,            KC_R,    KC_T,  KC_Y,  KC_U,   KC_I,           KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,            KC_F,    KC_G,  KC_H,  KC_J,   KC_K,           KC_L,    KC_SCLN, QUOTE,
    KC_LEFT, KC_Z,    KC_X,    KC_C,            KC_V,    KC_B,  KC_N,  KC_M,   KC_COMM,        KC_DOT,  KC_SLSH, KC_RGHT,
    DM_REC1, DM_PLY1, KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, LOWER, RAISE, KC_SPC, RCTL_T(KC_DEL), DM_REC2, DM_PLY2, DM_RSTP
),

[_LOWER] = LAYOUT_ortho_4x12(
    KC_F1, X(QSTN), X(WINK), X(EYES),         X(RLVD), X(TNGE), X(YEN),  X(UPDN), X(IMP),         X(OH),  X(PRTY), KC_F12,
    KC_F2, X(AGRY), X(SPKL), X(DSPT),         X(FIRE), X(GRIN), X(HRT),  X(JANK), X(KISS),        X(LGH), X(POOP), KC_F11,
    KC_F3, X(ZZZ),  X(XMRK), X(COOL),         X(VMIT), X(BANA), X(NOSE), X(MNKY), X(DOWN),        X(UP),  X(CHK),  KC_F10,
    KC_F4, KC_F5,   KC_F6,   LALT_T(KC_BSPC), KC_LSFT, XXXXXXX, KC_ENT,  KC_SPC,  RCTL_T(KC_DEL), KC_F7,  KC_F8,   KC_F9
),

[_RAISE] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_GRAVE, KC_LCBR, KC_LPRN,         KC_LBRC, KC_LABK, KC_RABK, KC_RBRC, KC_RPRN,        KC_RCBR, KC_BSLS, KC_BSPC,
    KC_ESC,  KC_1,     KC_2,    KC_3,            KC_4,    KC_5,    KC_6,    KC_7,    KC_8,           NINE,    ZERO,    SIGN,
    KC_LEFT, KC_HOME,  KC_PGDN, KC_PGUP,         KC_END,  AU_OFF,  AU_ON,   KC_LEFT, KC_DOWN,        KC_UP,   KC_RGHT, KC_RGHT,
    KC_VOLD, KC_VOLU,  KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, KC_ENT,  XXXXXXX, KC_SPC,  RCTL_T(KC_DEL), KC_BRID, KC_BRIU, KC_SLEP
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    uint16_t custom_keycode;
    switch (keycode) {
    case QUOTE: ;
        custom_keycode = KC_DOUBLE_QUOTE;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                set_mods(mod_state & ~MOD_MASK_SHIFT);
                tap_code(KC_QUOTE);
                set_mods(mod_state);
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case NINE: ;
        custom_keycode = KC_9;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                tap_code(KC_MINUS);  // KC_UNDERSCORE
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case ZERO: ;
        custom_keycode = KC_0;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                set_mods(mod_state & ~MOD_MASK_SHIFT);
                tap_code(KC_EQUAL);
                set_mods(mod_state);
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    case SIGN: ;
        custom_keycode = KC_MINUS;
        if (mod_state & MOD_MASK_SHIFT) {
            if (record->event.pressed) {
                tap_code(KC_EQUAL);  // KC_PLUS
            }
        } else {
            if (record->event.pressed) {
                register_code16(custom_keycode);
            } else {
                unregister_code16(custom_keycode);
            }
        }
        return false;
    }
    return true;
}

#ifdef DYNAMIC_MACRO_ENABLE

float start_song[][2] = SONG(STARTUP_SOUND);
float end_song[][2] = SONG(GOODBYE_SOUND);
float play_song[][2] = SONG(VIOLIN_SOUND);

void dynamic_macro_record_start_user(void) {
#ifdef AUDIO_ENABLE
  PLAY_SONG(start_song);
#endif
}

void dynamic_macro_record_end_user(int8_t direction) {
#ifdef AUDIO_ENABLE
  PLAY_SONG(end_song);
#endif
}

void dynamic_macro_play_user(int8_t direction) {
#ifdef AUDIO_ENABLE
  PLAY_SONG(play_song);
#endif
}

#endif
