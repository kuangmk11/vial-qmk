/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once
#define VIAL_KEYBOARD_UID {0xCA, 0x43, 0x6E, 0xF3, 0x4D, 0x91, 0x78, 0x1F}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }
#define MIDI_ADVANCED
#define SENDSTRING_BELL
//#define SEQUENCER_STEPS 16   //By default the sequencer has 16 steps

//#define USE_I2C

/* Select hand configuration */
// #define MASTER_RIGHT
// #define EE_HANDS
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
