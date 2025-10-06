// SPDX-License-Identifier: GPL-2.0-or-later
#include "bmp_status.h"
#include "apidef.h"
#include <stddef.h>

static inline int fn_ok(void *p) { return p != NULL; }
static bool g_adv_allowed = false;

void status_allow_advertising(bool allow) {
    g_adv_allowed = allow;
    if (!allow) {
        status__set_ble_advertising(false);
        status__set_ble_connected(false);
    }
}

/* event handler from BMP */
static bmp_error_t on_bmp_event(bmp_api_event_t ev) {
    switch (ev) {
        case USB_CONNECTED:
        case USB_CDC_ACM_OPEND:
        case USB_HID_READY:
            status__set_output(OUT_USB);
            status__set_ble_advertising(false);
            status__set_ble_connected(false);
            break;

        case USB_DISCONNECTED:
            status__set_output(OUT_BLE);
            status__set_ble_advertising(false);
            status__set_ble_connected(false);
            break;

        case BLE_ADVERTISING_START:
            if (!g_adv_allowed) {
                status__set_ble_advertising(false);
                status__set_ble_connected(false);
                break;
            }
            status__set_output(OUT_BLE);
            status__set_ble_advertising(true);
            status__set_ble_connected(false);
            break;

        case BLE_ADVERTISING_STOP:
            status__set_ble_advertising(false);
            break;

        case BLE_CONNECTED:
            status__set_output(OUT_BLE);
            status__set_ble_advertising(false);
            status__set_ble_connected(true);
            break;

        case BLE_DISCONNECTED:
            status__set_ble_connected(false);
            status__set_ble_advertising(false);
            break;

        default:
            break;
    }
    return 0;
}

void status_init(void) {
    if (BMPAPI && fn_ok(BMPAPI->app.set_state_change_cb)) {
        BMPAPI->app.set_state_change_cb(on_bmp_event);
    }
}

/* optional: keep "connected" in sync by polling */
void status_update_tick(void) {
    if (BMPAPI && fn_ok(BMPAPI->ble.get_connection_status)) {
        uint16_t st = BMPAPI->ble.get_connection_status();
        if (st == 0) {
            status__set_ble_connected(false);
        }
        /* do not change advertising flag here */
    }
}
