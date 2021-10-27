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
#include "jonboye.h"

// clang-format off
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
        KC_GRV,  KC_1,    CU_2,    CU_3,    KC_4,    KC_5,    CU_6,    CU_7,    CU_8,    CU_9,    CU_0,    KC_MINS, CU_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,    ES_Y,    ES_U,    ES_I,    ES_O,    ES_P,    CU_LBRC, CU_RBRC, CU_BSLS,          KC_PGUP,
        KC_CAPS, ES_A,    ES_S,    ES_D,    ES_F,    ES_G,    ES_H,    ES_J,    ES_K,    ES_L,    CU_SCLN, CU_QUOT,          KC_ENT,           KC_PGDN,
        CU_LSFT,          ES_Z,    ES_X,    ES_C,    ES_V,    ES_B,    ES_N,    ES_M,    CU_COMM, CU_DOT,  CU_SLSH,          CU_RSFT, KC_UP,   KC_END,
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
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         KC_MPLY,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,           KC_MNXT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,         KC_MPRV,
        _______,          _______, _______, _______, _______, _______, CU_N, _______, _______, _______, _______, _______, _______, KC_MSTP,
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


// Spanish spaghetti code down here

#ifdef SPANISH_ENABLE
// These indicate if left and right shift are physically pressed
bool lshift = false;
bool rshift = false;

// Number of items that are saved in prev_kcs
uint8_t prev_indx = 0;
// Used to save the last 6 actual keycodes activated by frankenkeycodes
uint16_t prev_kcs[6] = {0, 0, 0, 0, 0, 0};

// If true the deadkey characters grave and circonflexe are not automatically escaped
bool esct = false;

/*
Used to add a keycode to a prev_kcs to remember it.
When full the last code gets discarded and replaced by
the new one.
*/
void add_to_prev(uint16_t kc){
  for (int i=0; i<prev_indx; i++){
    if (kc == prev_kcs[i])
      return;
  }
  if (prev_indx == 6){
    for (int i=5; i>0; i--){
      prev_kcs[i] = prev_kcs[i-1];
    }
    prev_kcs[0] = kc;
  } else {
    prev_kcs[prev_indx] = kc;
    prev_indx++;
  }
}

/*
Unregisters all codes saved in prev_kcs and resets prev_indx.
gets called on multiple occasions mainly when shift is released
and when frankenkeycodes are pressed. Prevents output of
wrong characters when really specific key combinations
that would never occur during normal usage are pressed.
*/
void unreg_prev(void){
  if (prev_indx == 0)
    return;
  for (int i=0; i<prev_indx; i++){
    unregister_code(prev_kcs[i]);
  }
  prev_indx = 0;
}
#endif

// Interrupts all timers
void timer_timeout(void){
  #ifdef SPANISH_ENABLE
  lshiftp = false;
  rshiftp = false;
  #endif
  navesc = false;
  timer_timeout_keymap();
}

__attribute__((weak))
void timer_timeout_keymap(void){
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  #ifdef SPANISH_ENABLE
  case CU_LSFT:
    if(record->event.pressed) {
      lshiftp = true;
      lshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      lshift = true;
    } else {
      if (timer_elapsed(lshift_timer) {
        register_code(KC_LSFT);
        register_code(KC_8);
        unregister_code(KC_8);
        unregister_code(KC_LSFT);
      }
      unreg_prev();
      if (!rshift)
        unregister_code(KC_LSFT);
      lshift = false;
    }
    return false;
  case CU_RSFT:
    if(record->event.pressed) {
      rshiftp = true;
      rshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      rshift = true;
    } else {
      if (timer_elapsed(rshift_timer) {
        register_code(KC_LSFT);
        register_code(KC_9);
        unregister_code(KC_9);
        unregister_code(KC_LSFT);
      }
      unreg_prev();
      if (!lshift)
        unregister_code(KC_LSFT);
      rshift = false;
    }
    return false;

case CU_6:
  if(record->event.pressed){
    timer_timeout();
    unregister_code(KC_LSFT);
    if (lshift || rshift){
      unregister_code(ES_CIRC);
      register_code(ES_CIRC);
      unregister_code(ES_CIRC);
      if (!esct) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      register_code(KC_LSFT);
    } else {
      register_code(ES_6);
    }
  } else {
    unregister_code(ES_6);
  }
  return false;
case CU_COMM:
  SHIFT_NO(ES_COMM, ES_LABK)
case CU_DOT:
  SHIFT_NORM(DE_DOT, ES_LABK)
case CU_SLSH:
  SHIFT_ALL(ES_7, ES_SS)
case CU_SCLN:
  SHIFT_ALL(ES_COMM, ES_DOT)
case CU_2:
  SHIFT_ALGR(ES_2, ES_2)
  case CU_3:
    SHIFT_NO(ES_3, ES_HASH)
case CU_7:
  SHIFT_NORM(ES_7, ES_6)
case CU_8:
  SHIFT_NORM(ES_8, ES_PLUS)
case CU_9:
  SHIFT_NORM(ES_9, ES_8)
case CU_0:
  SHIFT_NORM(ES_0, ES_9)
case CU_EQL:
  SHIFT_SWITCH(ES_0, ES_PLUS)
case CU_LBRC:
  SHIFT_ALGR(ES_8, ES_7)
case CU_RBRC:
  SHIFT_ALGR(ES_9, ES_0)
case CU_BSLS:
  SHIFT_ALGR(ES_MORD, ES_1)
case CU_GRV:
  SHIFT_NO(ES_QUOT, ES_MORD)
  #endif

default:
  if(record->event.pressed) {
    timer_timeout();

    #ifdef SPANISH_ENABLE
    if (lshift || rshift)
      register_code(KC_LSFT);
    else
      unregister_code(KC_LSFT);
    #endif

  }
  return process_record_keymap(keycode, record);
}
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
return true;
}
