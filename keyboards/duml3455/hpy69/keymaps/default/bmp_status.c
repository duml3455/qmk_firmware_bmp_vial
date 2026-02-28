// SPDX-License-Identifier: GPL-2.0-or-later
#include "bmp_status.h"

/* state */
static volatile output_t g_out  = OUT_BLE;     /* default to BLE unless USB says otherwise */
static volatile bool     g_ble  = false;       /* connected flag */
static volatile bool     g_adv  = false;       /* advertising flag */
static volatile uint8_t  g_slot = SLOT_WOL;    /* 0..7 valid, 0xFF = WOL/unknown */

/* keep state consistent */
static inline void status_sanitize(void) {
    if (g_ble) g_adv = false;                  /* no advertising while connected */
    if (g_out != OUT_USB && g_out != OUT_BLE) g_out = OUT_BLE;
    if (g_slot > 7 && g_slot != SLOT_WOL) g_slot = SLOT_WOL;
}

/* fact setters */
void status_set_output(output_t out)           { g_out  = out;  status_sanitize(); }
void status_set_ble_connected(bool conn)       { g_ble  = conn; status_sanitize(); }
void status_set_ble_advertising(bool adv)      { g_adv  = adv;  status_sanitize(); }
void status_set_ble_slot(uint8_t slot)         { g_slot = (slot <= 7 || slot == SLOT_WOL) ? slot : SLOT_WOL; status_sanitize(); }

/* getters */
output_t status_current_output(void)            { return g_out; }
bool     status_is_usb_active(void)             { return g_out == OUT_USB; }
bool     status_ble_is_connected(void)          { return g_ble; }
bool     status_ble_is_advertising(void)        { return g_adv && !g_ble; }
uint8_t  status_ble_slot_index(void)            { return g_slot; }

/* note: init() and tick() are defined in bmp_status_impl.c */
