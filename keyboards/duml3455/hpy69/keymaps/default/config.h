/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x9A, 0x4D, 0x73, 0xB1, 0x2E, 0xC8, 0x6F, 0x15}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

#undef OLED_TIMEOUT
#define OLED_TIMEOUT 300000

#undef OLED_BRIGHTNESS
#define OLED_BRIGHTNESS 96

/* Enable/disable "Left Shift + Space sends KC_LNG2". */
/* Enable   define HPY69_ENABLE_SHIFT_SPACE_LNG2 1 */
/* disable  define HPY69_ENABLE_SHIFT_SPACE_LNG2 0 */
#ifndef HPY69_ENABLE_SHIFT_SPACE_LNG2
#    define HPY69_ENABLE_SHIFT_SPACE_LNG2 1
#endif
