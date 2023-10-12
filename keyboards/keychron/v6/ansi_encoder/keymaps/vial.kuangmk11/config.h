/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xA5, 0xAC, 0x70, 0x4B, 0xBF, 0x30, 0xA9, 0x47}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

// Change USB Polling Rate to 1000hz
#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12