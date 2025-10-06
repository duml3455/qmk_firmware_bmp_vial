// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    OUT_UNKNOWN = 0,
    OUT_USB,
    OUT_BLE,
} output_t;

/* public */
void     status_init(void);
void     status_update_tick(void);

output_t status_current_output(void);
bool     status_is_usb_active(void);
bool     status_ble_is_connected(void);
bool     status_ble_is_advertising(void);
uint8_t  status_ble_slot_index(void); /* 1..N, 0 = unknown */

/* internal setters (used by impl) */
void     status__set_output(output_t out);
void     status__set_ble_connected(bool conn);
void     status__set_ble_advertising(bool adv);
void     status__set_ble_slot(uint8_t slot);

void     status_allow_advertising(bool allow);