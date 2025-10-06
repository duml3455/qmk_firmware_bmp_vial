/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define BMP_BOOTPIN_AS_RESET
/* key matrix size */
#define MATRIX_ROWS_DEFAULT 5
#define MATRIX_COLS_DEFAULT 8
#define THIS_DEVICE_ROWS 5
#define THIS_DEVICE_COLS 8
#define IS_LEFT_HAND  true
#define BMP_DEFAULT_MODE SINGLE
#define ACTION_DEBUG
/* key matrix size */

#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

//#define RGBLIGHT_SPLIT
//#define RGBLED_NUM_DEFAULT 128

#define OLED_DISPLAY_128X32
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_IC OLED_IC_SSD1306
