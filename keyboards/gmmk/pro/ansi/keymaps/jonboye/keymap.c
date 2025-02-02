/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"

// clang-format of
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.


    //      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
    //      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
    //      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
    //      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
    //      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
    //      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,    ES_Y,    ES_U,    ES_I,    ES_O,    ES_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, ES_A,    ES_S,    ES_D,    ES_F,    ES_G,    ES_H,    ES_J,    ES_K,    ES_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          ES_Z,    ES_X,    ES_C,    ES_V,    ES_B,    ES_N,    ES_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    //  RGB onoff    •        •        •        •        •        •        •       •        •        •         •       •        •	                 •
    //      •        •        •        •        •        •        •        •       •        •        •         •       •	      Reset              Play
    //      •        •        •        •        •        •        •        •       •        •        •         •       •        •                  Next
    //      •        •        •        •        •        •        •        •       •        •        •         •                Enter              Prev
    //      •                 •        •        •        •        •        ñ       •        •        •         •                •        •         Stop
    //      •        •        •                                   •                                  N Tog     FN      •        •        •         •


    [1] = LAYOUT(
        RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______,
        _______, ES_IEXL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         KC_MPLY,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,           KC_MNXT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,         KC_MPRV,
        _______,          _______, _______, _______, _______, _______, ES_NTIL, _______, _______, _______, S(ES_IEXL), _______, _______, KC_MSTP,
        _______, _______, _______,                            _______,                            NK_TOGG, _______, _______, _______, _______, _______
    ),

};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch(biton32(layer_state)){
        case 1:
            if (clockwise){
                tap_code16(C(KC_MNXT));
            } else{
                tap_code16(S(C(KC_MPRV)));
            }
            break;
        default:
            if (clockwise) {
                tap_code16(KC_VOLU);
            } else {
                tap_code16(KC_VOLD);
            }
            break;
        }
    }
    return true;
}
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state)) {
    // special handling per layer
        case 0:  //layer one
            if (host_keyboard_led_state().caps_lock)
                rgb_matrix_set_color_all(255,0,0);
            else
                rgb_matrix_set_color_all(0,255,56);
            break;
        case 1:
            for (uint8_t i = led_min; i < led_max; i++) {
                 RGB_MATRIX_INDICATOR_SET_COLOR(i,0,0,0);
            }
            RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 255) //esc
            RGB_MATRIX_INDICATOR_SET_COLOR(6, 0, 0, 255) //f1
            RGB_MATRIX_INDICATOR_SET_COLOR(8, 0, 0, 255) //q
            RGB_MATRIX_INDICATOR_SET_COLOR(14, 0, 0, 255) //w
            RGB_MATRIX_INDICATOR_SET_COLOR(20, 0, 0, 255) //e
            RGB_MATRIX_INDICATOR_SET_COLOR(15, 0, 0, 255) //s
            RGB_MATRIX_INDICATOR_SET_COLOR(26, 0, 0, 255) //f
            RGB_MATRIX_INDICATOR_SET_COLOR(49, 0, 0, 255) //R_Alt
            break;
        default:
            break;
    }
}

#endif // RGB_MATRIX_ENABLE
