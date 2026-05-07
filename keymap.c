#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /*
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
    * |------+------+------+------+------+------| Scroll|    | Volume|------+------+------+------+------+------|
    * | LCTL |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LGUI |      | LAlt |      | /Space  /       \Enter \  |      | RCTR | RAlt | RGUI |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_BASE] = LAYOUT( 
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                   KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                   KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
        KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                   KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_VOLD,        XXXXXXX,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
            XXXXXXX,    KC_LGUI,     XXXXXXX,    KC_LALT,     KC_SPC,                                              KC_ENT,     KC_RALT,    KC_RCTL,     KC_RGUI,    TG(_FUNC)
    ),


    /*
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
    * |------+------+------+------+------+------| MS x-A|    |MS y-A |------+------+------+------+------+------|
    * | LCTL |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
    * `-----------------------------------------/       /    \       \-----------------------------------------'
    *            | LGUI |      | LAlt |LOWER | /L-Click/      \R-CLick\  |      | RCTR | RAlt | RGUI |
    *            |      |      |      |      |/       /        \       \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_FUNC] = LAYOUT(
        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                                  KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                   KC_Y,       KC_U,       KC_UP,      KC_O,       KC_P,       KC_LBRC,
        KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                   KC_H,       KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_SCLN,    KC_QUOT,
        KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       MS_LEFT,        MS_UP,      KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
            XXXXXXX,    KC_LGUI,     XXXXXXX,    KC_LALT,     MS_BTN1,                                              MS_BTN2,     KC_RALT,    KC_RCTL,     KC_RGUI,    TG(_FUNC)
    )
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer == _FUNC) {
        if (index == 0) {
            if (clockwise) {
                tap_code(MS_RGHT);
            } else {
                tap_code(MS_LEFT);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code(MS_DOWN);
            } else {
                tap_code(MS_UP);
            }
        }
    }
    else {
        if (index == 0) {
            if (clockwise) {
                tap_code(MS_WHLD);
            } else {
                tap_code(MS_WHLU);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }

    return false;
}