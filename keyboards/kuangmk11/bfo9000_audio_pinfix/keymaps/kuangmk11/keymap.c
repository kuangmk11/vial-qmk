#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  #ifdef AUTOCORRECT_ENABLE
    autocorrect_enable();
  #endif
  #ifdef AUTO_SHIFT_ENABLE
    autoshift_enable();
  #endif
};


#ifdef AUDIO_ENABLE
float song0[][2] = SONG(COIN_SOUND);
float song1[][2] = SONG(ZELDA_PUZZLE);
float song2[][2] = SONG(ONE_UP_SOUND);

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

float autocorrect_song[][2] = SONG(TERMINAL_SOUND);
#endif

// We want to enable audio clicky (i.e. compile it into firmware),
// but not have it "turned on" by default.
#ifdef AUDIO_CLICKY
#include "process_clicky.h"
extern audio_config_t audio_config;

void eeconfig_init_kb(void) {
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);

    // Need to read here because this isn't done before calling eeconfig_init_kb()
    audio_config.raw = eeconfig_read_audio();
    // ...and this call needs audio_config initialized.
    clicky_off();

    eeconfig_init_user();
}
#endif // AUDIO_CLICKY



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case TO(0):
          if (record->event.pressed) {
            #ifdef AUTOCORRECT_ENABLE
                autocorrect_enable();
            #endif
            #ifdef AUTO_SHIFT_ENABLE
                autoshift_enable();
            #endif
            #ifdef AUDIO_ENABLE
            PLAY_SONG(song0);
            #endif
            break;
          }
      case TO(1):
        if (record->event.pressed) {
            autocorrect_disable();
            autoshift_disable();
            #ifdef AUDIO_ENABLE
            PLAY_SONG(song1);
            #endif
            break;
        }
      case TO(2):
        if (record->event.pressed) {
            autocorrect_disable();
            autoshift_disable();
            #ifdef AUDIO_ENABLE
            PLAY_SONG(song2);
            #endif
            break;
        }
    }
  // If console is enabled, it will print the matrix position and status of each key pressed
  #ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
  #endif
  return true;
};

//Lock Key Feedback
bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        //writePin(F1, led_state.caps_lock);
    }

#ifdef AUDIO_ENABLE
    static led_t old_led_state = { .raw = 0 };

    wait_ms(10); // gets rid of tick

    if (led_state.caps_lock && !old_led_state.caps_lock)
    {
        PLAY_SONG(tone_caps_on);
    }
    else if (!led_state.caps_lock && old_led_state.caps_lock)
    {
        PLAY_SONG(tone_caps_off);
    }
    else if (led_state.num_lock && !old_led_state.num_lock)
    {
        PLAY_SONG(tone_numlk_on);
    }
    else if (!led_state.num_lock && old_led_state.num_lock)
    {
        PLAY_SONG(tone_numlk_off);
    }
    else if (led_state.scroll_lock && !old_led_state.scroll_lock)
    {
        PLAY_SONG(tone_scroll_on);
    }
    else if (!led_state.scroll_lock && old_led_state.scroll_lock)
    {
        PLAY_SONG(tone_scroll_off);
    }

    old_led_state = led_state;
#endif // AUDIO_ENABLE
  return true;
}

//AutoCorrect
#ifdef AUTOCORRECT_ENABLE
bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods) {
    // See quantum_keycodes.h for reference on these matched ranges.
    switch (*keycode) {
        // Exclude these keycodes from processing.
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case QK_TO ... QK_ONE_SHOT_LAYER_MAX:
        //case QK_LAYER_TAP_TOGGLE ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return false;

        // Mask for base keycode from shifted keys.
        case QK_LSFT ... QK_LSFT + 255:
        case QK_RSFT ... QK_RSFT + 255:
            if (*keycode >= QK_LSFT && *keycode <= (QK_LSFT + 255)) {
                *mods |= MOD_LSFT;
            } else {
                *mods |= MOD_RSFT;
            }
            *keycode &= 0xFF; // Get the basic keycode.
            return true;
#ifndef NO_ACTION_TAPPING
        // Exclude tap-hold keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    ifdef NO_ACTION_LAYER
            // Exclude Layer Tap, if layers are disabled
            // but action tapping is still enabled.
            return false;
#    endif
        //case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            // Exclude hold if mods other than Shift is not active
        //    if (!record->tap.count) {
        //        return false;
        //    }
        //    *keycode &= 0xFF;
        //    break;
#else
        //case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        //case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // Exclude if disabled
        //    return false;
#endif
        // Exclude swap hands keys when they are held down
        // and mask for base keycode when they are tapped.
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
#ifdef SWAP_HANDS_ENABLE
            if (*keycode >= 0x56F0 || !record->tap.count) {
                return false;
            }
            *keycode &= 0xFF;
            break;
#else
            // Exclude if disabled
            return false;
#endif
        // Handle custom keycodes
        //case QMKBEST:
        //    return false;
        //case QMKLAYER:
        //    *typo_buffer_size = 0;
        //    return false;
    }

    // Disable autocorrect while a mod other than shift is active.
    if ((*mods & ~MOD_MASK_SHIFT) != 0) {
        *typo_buffer_size = 0;
        return false;
    }

    return true;
}


bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(autocorrect_song);
#endif
    for (uint8_t i = 0; i < backspaces; ++i) {
        tap_code(KC_BSPC);
    }
    send_string_P(str);
    return false;
}
#endif
//END Autocorrect

//Custom Keycodes
enum custom_keycode {
    QMK_AC_ON = QK_USER_0,
    QMK_AC_OFF,
    QMK_AC_TOGG
};

//Layer Definitions
enum layers {
	_BASE,
	_GAME,
  _MIDI
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_ESC,      KC_VOLD,        KC_VOLU,      KC_F1,         KC_F2,   KC_F3,    KC_F4,   KC_F5,    KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCROLL_LOCK, KC_MPLY,
    KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,  KC_GRAVE,      KC_1,    KC_2,     KC_3,    KC_4,     KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_BSPC,  KC_DELETE,
    KC_KP_7,     KC_KP_8,        KC_KP_9,      KC_TAB,        KC_Q,    KC_W,     KC_E,    KC_R,     KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_HOME,   KC_BSLS,
    KC_KP_4,     KC_KP_5,        KC_KP_6,      KC_CAPS_LOCK,   KC_A,   KC_S,     KC_D,    KC_F,     KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, TD(0),      KC_END,   KC_PGUP,
    KC_KP_1,     KC_KP_2,        KC_KP_3,      KC_LSFT,       KC_Z,    KC_X,     KC_C,    KC_V,     KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_DELETE,  KC_UP,    KC_PGDN,
    KC_KP_0,     KC_KP_DOT,      KC_KP_ENTER,  KC_LCTL,       TO(2),   KC_LALT,  KC_NO,   KC_BSPC,  KC_NO,         KC_BSPC, KC_SPC,  KC_SPC,  TD(2),   KC_RALT, KC_RCTL, KC_LEFT,    KC_DOWN,  KC_RGHT
),

[_GAME] = LAYOUT(
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LSFT,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LCTL,	_______,	_______,	_______,	_______,	KC_SPC,  	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______
),

[_MIDI] = LAYOUT(
	MI_TOGG,	QK_MIDI_NOTE_C_SHARP_0,	QK_MIDI_NOTE_D_0,	QK_MIDI_NOTE_D_SHARP_0,	QK_MIDI_NOTE_E_0,	QK_MIDI_NOTE_F_0,	QK_MIDI_NOTE_F_SHARP_0,	QK_MIDI_NOTE_G_0,	QK_MIDI_NOTE_G_SHARP_0,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LSFT,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LCTL,	_______,	_______,	_______,	_______,	KC_SPC,  	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______
)
};
