// SPDX-License-Identifier: GPL-2.0-or-later
#include "bmp_status.h"

static volatile output_t g_out  = OUT_BLE;
static volatile bool     g_ble  = false;
static volatile bool     g_adv  = false;
static volatile uint8_t  g_slot = 0;

/* setters */
void status__set_output(output_t out)        { g_out  = out; }
void status__set_ble_connected(bool conn)    { g_ble  = conn; }
void status__set_ble_advertising(bool adv)   { g_adv  = adv; }
void status__set_ble_slot(uint8_t slot)      { g_slot = slot; }

/* getters */
output_t status_current_output(void)         { return g_out; }
bool     status_is_usb_active(void)          { return g_out == OUT_USB; }
bool     status_ble_is_connected(void)       { return g_ble; }
bool     status_ble_is_advertising(void)     { return g_adv; }
uint8_t  status_ble_slot_index(void)         { return g_slot; }

/* note: status_init() and status_update_tick() are in bmp_status_impl.c */
