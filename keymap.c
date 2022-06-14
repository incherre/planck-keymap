#include QMK_KEYBOARD_H

#include <stdlib.h>

#include "keymap_steno.h"

enum layers {
    _BASE,
    _RAISE,
    _RAND
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    RAND,
    EXIT_RAND,
    QUOTE,
    NINE,
    ZERO,
    SIGN
};
#define RAISE MO(_RAISE)

uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,            KC_R,    KC_T,   KC_Y,  KC_U,   KC_I,           KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,            KC_F,    KC_G,   KC_H,  KC_J,   KC_K,           KC_L,    KC_SCLN, QUOTE,
    KC_LEFT, KC_Z,    KC_X,    KC_C,            KC_V,    KC_B,   KC_N,  KC_M,   KC_COMM,        KC_DOT,  KC_SLSH, KC_RGHT,
    DM_REC1, DM_PLY1, KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, RAND, RAISE, KC_SPC, RCTL_T(KC_DEL), DM_REC2, DM_PLY2, DM_RSTP
),

[_RAISE] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_GRAVE, KC_LCBR, KC_LPRN,         KC_LBRC, KC_LABK, KC_RABK, KC_RBRC, KC_RPRN,        KC_RCBR, KC_BSLS, KC_BSPC,
    KC_ESC,  KC_1,     KC_2,    KC_3,            KC_4,    KC_5,    KC_6,    KC_7,    KC_8,           NINE,    ZERO,    SIGN,
    KC_LEFT, KC_HOME,  KC_PGDN, KC_PGUP,         KC_END,  AU_OFF,  AU_ON,   KC_LEFT, KC_DOWN,        KC_UP,   KC_RGHT, KC_RGHT,
    KC_VOLD, KC_VOLU,  KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, KC_ENT,  XXXXXXX, KC_SPC,  RCTL_T(KC_DEL), KC_BRID, KC_BRIU, KC_SLEP
),


[_RAND] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,            KC_R,    KC_T,   KC_Y,  KC_U,   KC_I,           KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,            KC_F,    KC_G,   KC_H,  KC_J,   KC_K,           KC_L,    KC_SCLN, QUOTE,
    KC_LEFT, KC_Z,    KC_X,    KC_C,            KC_V,    KC_B,   KC_N,  KC_M,   KC_COMM,        KC_DOT,  KC_SLSH, KC_RGHT,
    DM_REC1, DM_PLY1, KC_LGUI, LALT_T(KC_BSPC), KC_LSFT, EXIT_RAND, RAISE, KC_SPC, RCTL_T(KC_DEL), DM_REC2, DM_PLY2, DM_RSTP
)

};

bool random_initialized = false;

void shuffle_rand_layout() {
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            int swap_i = rand() % MATRIX_ROWS;
            int swap_j = rand() % MATRIX_COLS;

            uint16_t swap_val = keymaps[_RAND][i][j];
            keymaps[_RAND][i][j] = keymaps[_RAND][swap_i][swap_j];
            keymaps[_RAND][swap_i][swap_j] = swap_val;
        }
    }
}

#ifdef AUDIO_ENABLE
    float plover_song[][2]      = SONG(PLOVER_SOUND);
    float plover_gb_song[][2]   = SONG(PLOVER_GOODBYE_SOUND);

    float macro_start_song[][2] = SONG(STARTUP_SOUND);
    float macro_end_song[][2]   = SONG(GOODBYE_SOUND);
    float macro_play_song[][2]  = SONG(VIOLIN_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    uint16_t custom_keycode;
    switch (keycode) {
    case RAND: ;
        #ifdef RAND_ENABLE
        if (!random_initialized) {
            srand(timer_read());
            random_initialized = true;
        }

        if (!record->event.pressed) {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(plover_song);
            #endif
            shuffle_rand_layout();
            layer_on(_RAND);
        }
        #endif
        return false;
    case EXIT_RAND: ;
        #ifdef RAND_ENABLE
        if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
            #endif
            layer_off(_RAND);
        }
        #endif
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

void eeconfig_init_user() {
#ifdef STENO_ENABLE
    steno_set_mode(STENO_MODE_BOLT);
#endif
}

#ifdef DYNAMIC_MACRO_ENABLE

void dynamic_macro_record_start_user(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(macro_start_song);
#endif
}

void dynamic_macro_record_end_user(int8_t direction) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(macro_end_song);
#endif
}

void dynamic_macro_play_user(int8_t direction) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(macro_play_song);
#endif
}

#endif
