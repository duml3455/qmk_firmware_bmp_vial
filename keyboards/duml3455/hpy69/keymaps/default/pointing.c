// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing.h"

#include "hpy69_debug.h"

static pointing_mode_t g_pointing_mode = POINTING_MODE_CURSOR;
static uint8_t         g_button_mask   = 0;

static pointing_mode_t pointing_sanitize_mode(pointing_mode_t mode) {
    switch (mode) {
        case POINTING_MODE_CURSOR:
        case POINTING_MODE_SCROLL:
            return mode;
        default:
            return POINTING_MODE_CURSOR;
    }
}

void pointing_init_user_state(void) {
    pointing_set_mode(POINTING_MODE_CURSOR);
    pointing_set_button_mask(0);
}

void pointing_task_user_state(void) {
}

bool pointing_process_record_user(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    (void)record;
    return true;
}

void pointing_set_mode(pointing_mode_t mode) {
    g_pointing_mode = pointing_sanitize_mode(mode);
}

void pointing_set_button_mask(uint8_t mask) {
    g_button_mask = mask;
}

pointing_mode_t pointing_current_mode(void) {
    return g_pointing_mode;
}

uint8_t pointing_button_mask(void) {
    return g_button_mask;
}
