//     _   __
//    | | / /
//    | |/ /  ___ _   _ _ __ ___   __ _ _ __
//    |    \ / _ \ | | | '_ ` _ \ / _` | '_ \
//    | |\  \  __/ |_| | | | | | | (_| | |_) |
//    \_| \_/\___|\__, |_| |_| |_|\__,_| .__/
//                 __/ |               | |
//                |___/                |_|

#include QMK_KEYBOARD_H
#include "host.h"
#include <stdio.h>

// ---------- OLED ----------
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_set_brightness(0);
    return OLED_ROTATION_270;
}
// ---------- OLED ----------

#endif

// ---------- Layer ----------
enum layers {
    _BASE,
    _FUNC,
    _GAME
};
// ---------- Layer ----------

// ---------- Encoder Acceleration ----------
// -- Variables --
static uint16_t last_encoder_time[2] = {0, 0};
static uint8_t  last_speed[2]         = {0, 0};

// -- Settings --
#define ENCODER_ACCEL_THRESHOLD 120  // ms between ticks (smaller = faster rotation)
#define MAX_MOUSE_MOVE 8             // maximum pixels per tick
// ---------- Encoder Acceleration ----------


// ---------- Keymaps ----------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ---------- Base Layer ----------
    /*
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
    * |------+------+------+------+------+------| Scroll|    | Volume|------+------+------+------+------+------|
    * | LCTL |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |   +  |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | _GAME| LALT | <|>  | LGUI | /Space  /       \Enter \  | RALT | _FUNC|      |  #'’ |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_BASE] = LAYOUT(
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                          KC_6,   KC_7,    KC_8,      KC_9,    KC_0,    KC_BSPC,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                          KC_Y,   KC_U,    KC_I,      KC_O,    KC_P,    KC_LBRC,
        KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                          KC_H,   KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,   KC_B, KC_VOLD,        XXXXXXX, KC_N,   KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_RBRC,
        TG(_GAME), KC_LALT, KC_NUBS, KC_LGUI, KC_SPC,                                KC_ENT, KC_RALT, TG(_FUNC), XXXXXXX, KC_BSLS
    ),
    // ---------- Base Layer ----------

    // ---------- Game Layer ----------
    /*
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  F3  | TAB  |   Q  |   W  |   E  |   R  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  F2  |LShift|   A  |   S  |   D  |   F  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
    * |------+------+------+------+------+------| Scroll|    | Volume|------+------+------+------+------+------|
    * |  F1  | LCTL |   Y  |   X  |   C  |   V  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | _GAME| LGUI |      | LAlt | /Space  /       \Enter \  | RALT | RCTL | RGUI |      |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_GAME] = LAYOUT(
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                        KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_F3,     KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,                        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_F2,     KC_LSFT, KC_A,    KC_S,    KC_D,   KC_F,                        KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_F1,     KC_LCTL, KC_Z,    KC_X,    KC_C,   KC_V, MS_LEFT,        MS_UP, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        TG(_GAME), KC_LGUI, XXXXXXX, KC_LALT, KC_SPC,                              KC_ENT, KC_RALT, KC_RCTL, KC_RGUI, XXXXXXX
    ),
    // ---------- Game Layer ----------

    // ---------- Function Layer ----------
    /*
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |      |      |   ↑  |      |   (  |  )   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------| #'’  |   ←  |   ↑  |   →  |   {  |  }   |
    * |------+------+------+------+------+------| MS x-A|    |MS y-A |------+------+------+------+------+------|
    * | LCTL |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|      |      |   ,  |   .  |   [  |  ]   |
    * `-----------------------------------------/       /    \       \-----------------------------------------'
    *            |      | LGUI |      | LALT | /L-Click/      \R-CLick\  | RALT | _FUNC| RGUI | RGUI |
    *            |      |      |      |      |/       /        \       \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_FUNC] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,     KC_F10,   KC_F11,     KC_F12,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         XXXXXXX, XXXXXXX, KC_UP,     XXXXXXX,  S(KC_8),    S(KC_9),
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_BSLS, KC_LEFT, KC_DOWN,   KC_RIGHT, ALGR(KC_8), ALGR(KC_9),
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  MS_LEFT,        MS_UP, XXXXXXX, XXXXXXX, KC_COMM,   KC_DOT,   ALGR(KC_7), ALGR(KC_0),
        XXXXXXX, KC_LGUI, XXXXXXX, KC_LALT, MS_BTN1,                               MS_BTN2, KC_RALT, TG(_FUNC), KC_RGUI,  KC_RCTL
    )
    // ---------- Function Layer ----------
};


// ---------- Encoder ----------
// -- Acceleration Settings --
#define ACCEL_THRESHOLD_FAST   80
#define ACCEL_THRESHOLD_MEDIUM 150

// -- Encoder Handler --
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t current_layer = get_highest_layer(layer_state);

    // -- Function Layer: Mouse Movement --
    if (current_layer == _FUNC) {
        int8_t direction = clockwise ? 1 : -1;
        uint16_t now = timer_read();
        uint16_t delta_time = TIMER_DIFF_16(now, last_encoder_time[index]);

        // -- Reset After Pause --
        if (delta_time > 400) {
            last_speed[index] = 1;
        }

        last_encoder_time[index] = now;

        // -- Speed Calculation --
        uint8_t speed = last_speed[index];
        if (delta_time < 10) {
            speed += 3;
        } else if (delta_time < 80) {
            speed += 2;
        } else if (delta_time < 140) {
            speed += 1;
        } else {
            if (speed > 1) {
                speed -= 1;
            }
        }

        // -- Speed Limits --
        if (speed > 100) {
            speed = 100;
        }

        if (speed < 1) {
            speed = 1;
        }

        last_speed[index] = speed;

        // -- Mouse Movement --
        int8_t move = direction * speed;
        report_mouse_t report = {0};

        if (index == 0) {
            // -- X-Axis --
            report.x = move;
        } else {
            // -- Y-Axis --
            report.y = move;
        }
        host_mouse_send(&report);
        return false;
    }

    // -- Default Encoder Behavior --
    else {

        // -- Encoder 0: Horizontal Scroll --
        if (index == 0) {
            if (clockwise) {
                tap_code(MS_WHLD);
            } else {
                tap_code(MS_WHLU);
            }
        }

        // -- Encoder 1: Volume Control --
        else if (index == 1) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }

    return false;
}
