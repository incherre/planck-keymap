#include QMK_KEYBOARD_H

#include "keymap_steno.h"

enum layers {
    _BASE,
    _RAISE,
    _PLOVER
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    PLOVER,
    EXT_PLV,
    QUOTE,
    NINE,
    ZERO,
    SIGN
};
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,            KC_R,    KC_T,   KC_Y,  KC_U,   KC_I,           KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,            KC_F,    KC_G,   KC_H,  KC_J,   KC_K,           KC_L,    KC_SCLN, QUOTE,
    KC_LEFT, KC_Z,    KC_X,    KC_C,            KC_V,    KC_B,   KC_N,  KC_M,   KC_COMM,        KC_DOT,  KC_SLSH, KC_RGHT,
    DM_REC1, DM_PLY1, KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, PLOVER, RAISE, KC_SPC, RCTL_T(KC_DEL), DM_REC2, DM_PLY2, DM_RSTP
),

[_RAISE] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_GRAVE, KC_LCBR, KC_LPRN,         KC_LBRC, KC_LABK, KC_RABK, KC_RBRC, KC_RPRN,        KC_RCBR, KC_BSLS, KC_BSPC,
    KC_ESC,  KC_1,     KC_2,    KC_3,            KC_4,    KC_5,    KC_6,    KC_7,    KC_8,           NINE,    ZERO,    SIGN,
    KC_LEFT, KC_HOME,  KC_PGDN, KC_PGUP,         KC_END,  AU_OFF,  AU_ON,   KC_LEFT, KC_DOWN,        KC_UP,   KC_RGHT, KC_RGHT,
    KC_VOLD, KC_VOLU,  KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, KC_ENT,  XXXXXXX, KC_SPC,  RCTL_T(KC_DEL), KC_BRID, KC_BRIU, KC_SLEP
),


[_PLOVER] = LAYOUT_planck_grid(
    STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
    STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
    XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
    EXT_PLV, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2
)

};

#ifdef AUDIO_ENABLE
    float plover_song[][2]     = SONG(PLOVER_SOUND);
    float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    uint16_t custom_keycode;
    switch (keycode) {
    case PLOVER: ;
        if (!record->event.pressed) {
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
            #endif
            layer_on(_PLOVER);
        }
        return false;
    case EXT_PLV: ;
        if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
            #endif
            layer_off(_PLOVER);
        }
        return false;
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
