// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    POINTING_MODE_CURSOR = 0,
    POINTING_MODE_SCROLL,
} pointing_mode_t;

void            pointing_init_user_state(void);
void            pointing_task_user_state(void);
bool            pointing_process_record_user(uint16_t keycode, keyrecord_t *record);
void            pointing_set_mode(pointing_mode_t mode);
void            pointing_set_button_mask(uint8_t mask);
pointing_mode_t pointing_current_mode(void);
uint8_t         pointing_button_mask(void);
