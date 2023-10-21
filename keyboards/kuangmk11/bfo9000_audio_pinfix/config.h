/*
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

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE



//By default, these are set to 0 and 0, which is usually the "ESC" key on a majority of keyboards.
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 250U

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* ChibiOS SPI definitions */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP13
#define SPI_MOSI_PIN GP27
#define SPI_MISO_PIN GP28

/*  Auto Shift  */
#define AUTO_SHIFT_TIMEOUT 180
//#define NO_AUTO_SHIFT_SPECIAL     //Do not Auto Shift special keys, which include -_, =+, [{, ]}, ;:, '", ,<, .>, /?, and the KC_TAB.
#define NO_AUTO_SHIFT_TAB           //Do not Auto Shift KC_TAB but leave Auto Shift enabled for the other special characters.
//#define NO_AUTO_SHIFT_SYMBOLS       //Do not Auto Shift symbol keys, which include -_, =+, [{, ]}, ;:, '", ,<, .>, and /?.
//#define NO_AUTO_SHIFT_NUMERIC     //Do not Auto Shift numeric keys, zero through nine.
//#define NO_AUTO_SHIFT_ALPHA       //Do not Auto Shift alpha characters, which include A through Z.

/* Audio */
#define AUDIO_PIN GP8
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#define AUDIO_INIT_DELAY
#define AUDIO_CLICKY
#define DAC_SAMPLE_MAX 65535U

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
#endif


/* RGB */
//#define RGBLED_SPLIT
#define WS2812_DI_PIN GP17  //GP17 is neopixel on KB2040
#define RGBLED_NUM 2
#define RGBLED_SPLIT  {1, 1}


//RGB Defaults
#define RGBLIGHT_HUE_STEP 	8 	                        //The number of steps to cycle through the hue by
#define RGBLIGHT_SAT_STEP 	17 	                                //The number of steps to increment the saturation by
#define RGBLIGHT_VAL_STEP 	17 	                                //The number of steps to increment the brightness by
#define RGBLIGHT_LIMIT_VAL 	255 	                            //The maximum brightness level
#define RGBLIGHT_SLEEP	                                        //If defined, the RGB lighting will be switched off when the host goes to sleep
//#define RGBLIGHT_DISABLE_KEYCODES 	     	                    //If defined, disables the ability to control RGB Light from the keycodes. You must use code functions to control the feature
#define RGBLIGHT_DEFAULT_MODE 	RGBLIGHT_MODE_ALTERNATING 	    //The default mode to use upon clearing the EEPROM
#define RGBLIGHT_DEFAULT_HUE 	0       	                    //The default hue to use upon clearing the EEPROM
#define RGBLIGHT_DEFAULT_SAT 	255	                            //The default saturation to use upon clearing the EEPROM
#define RGBLIGHT_DEFAULT_VAL 	255 	                        //The default value (brightness) to use upon clearing the EEPROM
#define RGBLIGHT_DEFAULT_SPD 	0 	                            //The default speed to use upon clearing the EEPROM

//enable all RGB effects
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

//#define RGBLIGHT_EFFECT_BREATHE_CENTER              //If defined, used to calculate the curve for the breathing animation. Valid values are 1.0 to 2.7
//#define RGBLIGHT_EFFECT_BREATHE_MAX 255             //The maximum brightness for the breathing mode. Valid values are 1 to 255
//#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 40       //How long (in milliseconds) to wait between animation steps for the "Christmas" animation
//#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2            //The number of LEDs to group the red/green colors by for the "Christmas" animation
//#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 2            //The number of LEDs to have the "Knight" animation travel
//#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3             //The number of LEDs to light up for the "Knight" animation
//#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0             //The number of LEDs to start the "Knight" animation from the start of the strip by
//#define RGBLIGHT_RAINBOW_SWIRL_RANGE 255            //Range adjustment for the rainbow swirl effect to get different swirls
//#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4              //The number of LEDs to light up for the "Snake" animation
//#define RGBLIGHT_EFFECT_TWINKLE_LIFE 200            //Adjusts how quickly each LED brightens and dims when twinkling (in animation steps)
//#define RGBLIGHT_EFFECT_TWINKLE_PROBABILITY 1/127   //Adjusts how likely each LED is to twinkle (on each animation step)

