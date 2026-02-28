// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <stdbool.h>
#include <stdint.h>

/* special value for "advertise without whitelist" or unknown */
#define SLOT_WOL 0xFF

typedef enum {
    OUT_UNKNOWN = 0,
    OUT_USB,
    OUT_BLE,
} output_t;

/* lifecycle */
void     status_init(void);
void     status_update_tick(void);

/* getters */
output_t status_current_output(void);
bool     status_is_usb_active(void);
bool     status_ble_is_connected(void);
bool     status_ble_is_advertising(void);
uint8_t  status_ble_slot_index(void); /* 0..7 valid, 0xFF = WOL or unknown */

/* fact setters */
void     status_set_output(output_t out);
void     status_set_ble_connected(bool conn);
void     status_set_ble_advertising(bool adv);
void     status_set_ble_slot(uint8_t slot);
