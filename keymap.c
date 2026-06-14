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

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_set_brightness(0);
    return OLED_ROTATION_270;
}

#endif

enum layers {
    _BASE,
    _FUNC,
    _GAME
};


// ==================== Encoder Acceleration ====================
static uint16_t last_encoder_time[2] = {0, 0};
static uint8_t  last_speed[2]         = {0, 0};

#define ENCODER_ACCEL_THRESHOLD 120  // ms zwischen Ticks (kleiner = schneller drehen)
#define MAX_MOUSE_MOVE 8             // maximale Pixel pro Tick (kannst du höher stellen)



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
    *            |      | LGUI |      | LAlt | /Space  /       \Enter \  | RCTR | RAlt | RGUI | _FUNC|
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_BASE] = LAYOUT( 
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                   KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                   KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
        KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                   KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_VOLD,        XXXXXXX,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
            TG(_GAME),    KC_LALT,     KC_NUBS,    KC_LGUI,     KC_SPC,                                              KC_ENT,     KC_RALT,    KC_RCTL,     KC_RGUI,    TG(_FUNC)
    ),

    /*
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      | TAB  |   Q  |   W  |   E  |   R  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |LShift|   A  |   S  |   D  |   F  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
    * |------+------+------+------+------+------| Scroll|    | Volume|------+------+------+------+------+------|
    * |      | LCTL |   Y  |   X  |   C  |   V  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            |      | LGUI |      | LAlt | /Space  /       \Enter \  | RCTR | RAlt | RGUI |      |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_GAME] = LAYOUT( 
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                   KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
        XXXXXXX,    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,                                   KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
        XXXXXXX,    KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,                                   KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
        XXXXXXX,    KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       MS_LEFT,        MS_UP,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
            TG(_GAME),    KC_LGUI,     XXXXXXX,    KC_LALT,     KC_SPC,                                              KC_ENT,     KC_RALT,    KC_RCTL,     KC_RGUI,    XXXXXXX
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


// ==================== Encoder Acceleration ====================
#define ACCEL_THRESHOLD_FAST   80   // ms
#define ACCEL_THRESHOLD_MEDIUM 150  // ms


bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer == _FUNC) {
        int8_t direction = clockwise ? 1 : -1;
        uint16_t now = timer_read();
        uint16_t delta_time = TIMER_DIFF_16(now, last_encoder_time[index]);

        // Nach längerer Pause komplett resetten
        if (delta_time > 400) {
            last_speed[index] = 1;
        }
        last_encoder_time[index] = now;

        // === Geschwindigkeitsabhängige Acceleration ===
        uint8_t speed = last_speed[index];

        // Sehr schnell
        if (delta_time < 10) {
            speed += 3;
        }

        // Schnell
        else if (delta_time < 80) {
            speed += 2;
        }

        // Normal drehen
        else if (delta_time < 140) {
            speed += 1;
        }

        // Langsam abbauen
        else {
            if (speed > 1) {
                speed -= 1;
            }
        }

        // Maximum begrenzen
        if (speed > 100) {
            speed = 100;
        }

        // Minimum
        if (speed < 1) {
            speed = 1;
        }

        last_speed[index] = speed;

        int8_t move = direction * speed;

        report_mouse_t report = {0};

        if (index == 0) {           // Encoder 0 = X-Achse
            report.x = move;
        } else {                    // Encoder 1 = Y-Achse
            report.y = move;
        }

        host_mouse_send(&report);
        return false;
    }

    // =============================================
    // Normales Verhalten auf anderen Layern
    // =============================================
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