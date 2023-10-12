#include QMK_KEYBOARD_H

float song0[][2] = SONG(ZELDA_PUZZLE);

layer_state_t layer_state_set_user(layer_state_t state) {
    static bool is_this_layer_on = false;
    if (layer_state_cmp(state, 0) != is_this_layer_on) {
        is_this_layer_on = layer_state_cmp(state, 0);
        if (is_this_layer_on) {
            PLAY_SONG(song0);
        } else {
            stop_all_notes();
        }
    }
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_MPLY,  KC_MSTP,  KC_UP,    TO(1),
		KC_VOLU,  KC_LEFT,  KC_DOWN,  KC_RIGHT,
		KC_VOLD,  KC_ENTER, KC_MPRV,  KC_MNXT   
	),
  
	[1] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS,  TO(2),
		KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
	),
	
	[2] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS, TO(3),
		KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
	),
	
	[3] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS, TO(4),
		KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
	),
	
	[4] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS, TO(5),
		KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
	),
	
	[5] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS, TO(6),
		KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
	),
	
	[6] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS, TO(7),
		KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
	),
	
	[7] = LAYOUT(
		KC_TRNS,  KC_TRNS,  KC_TRNS, TO(0),
		KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
	)
};


