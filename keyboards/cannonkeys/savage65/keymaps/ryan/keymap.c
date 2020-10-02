#include QMK_KEYBOARD_H

#define DEFAULT_LAYER      0
#define FUNCTION_LAYER     1
#define TOGGLE_LAYER       2
#define FUCK_WINDOWS_LAYER 3

#define XXXXXXX KC_NO
#define _______ KC_TRNS

// Tap Space for space, hold for MOUSE_LAYER
#define SPCE_LT LT(MOUSE_LAYER, KC_SPC)

// FN Key
#define FN MO(FUNCTION_LAYER)

// Toggle layer
#define TG_L MO(TOGGLE_LAYER)

// Toggle windows layer
#define TG_WIN TG(FUCK_WINDOWS_LAYER)

// @depracted
// Tap LALT for Caps, hold for LALT
/* #define ALT_LT MT(MOD_LALT, KC_CAPS) */

// @depracted
// Tap FN for CPAS, hold for FN
/* #define FN_LT LT(FUNCTION_LAYER, KC_CAPS) */

// Mission control and launchpad on macOS
// This requires setting keyboard shortcut in system preferences
// since they basically map to hyper + up/down
#define MISNCTL HYPR(KC_UP)
#define LNCHPAD HYPR(KC_DOWN)

// Custom keycode
enum custom_keycodes {
    LRCTRL = SAFE_RANGE   // lctrl and rctrl together
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |FN  | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |ESC    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |Cmd |        Space          |Ctrl|Alt|FN |Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[DEFAULT_LAYER] = LAYOUT_ansi(

    FN     ,KC_1   ,KC_2   ,KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_GRV ,\
    KC_TAB ,KC_Q   ,KC_W   ,KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,KC_DEL ,\
    KC_ESC ,KC_A   ,KC_S   ,KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,\
    KC_LSFT,        KC_Z   ,KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,  KC_UP,KC_PGDN,\
    LRCTRL ,KC_LALT,KC_LGUI,                KC_SPC ,                        KC_RCTL,KC_RALT,   FN  ,KC_LEFT,KC_DOWN,KC_RGHT

    ),

[FUCK_WINDOWS_LAYER] = LAYOUT_ansi(

    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MPRV,\
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,KC_MNXT,\
    _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
    KC_LCTL,KC_LGUI,KC_LALT,                _______,                        _______,_______,_______,_______,_______,_______

    ),

  /* Keymap : Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Play|
   * |----------------------------------------------------------------|
   * |    |   |  |   |   |   |   |   |BRID|BRIU|   |   |   |     |PREV|
   * |----------------------------------------------------------------|
   * |CPAS  |   |   |   |   |   |   |LEFT|DOWN|UP|RGHT|   |      |NEXT|
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   |MUT| VU-|VU+|  |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |           MUT         |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */

[FUNCTION_LAYER] = LAYOUT_ansi(

    _______,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_DEL ,KC_MPLY,\
    _______,_______,_______,_______,_______,_______,_______,KC_BRID,KC_BRIU,_______,_______,_______,_______,_______,KC_MRWD,\
    _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT,_______,_______,        KC_CAPS,KC_MFFD,\
    _______,_______,_______,_______,_______,_______,_______,KC_MUTE,KC_VOLD,KC_VOLU,_______,        _______,_______,MISNCTL,\
    _______,_______,_______,                KC_MUTE,                        TG_L   ,_______,_______,_______,_______,LNCHPAD

    ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case LRCTRL:
            {
                // Custom keycode for both left and right ctrl
                if(record->event.pressed) {
                    register_mods(MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL));
                } else {
                    unregister_mods(MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL));
                }

                return false;
            }

    }

    return true;
}
