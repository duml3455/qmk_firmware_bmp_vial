// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdbool.h>

#ifdef OLED_ENABLE
#    include "oled_driver.h"
void            oled_status_init(void);
void            oled_status_set_advertising_ui_enabled(bool enabled);
oled_rotation_t oled_status_init_user(oled_rotation_t rotation);
bool            oled_status_task_user(void);
#endif
