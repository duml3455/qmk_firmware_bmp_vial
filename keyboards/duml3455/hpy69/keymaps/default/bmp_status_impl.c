// SPDX-License-Identifier: GPL-2.0-or-later
#include "bmp_status.h"
#include "apidef.h"
#include <stddef.h>
#include <stdint.h>

static inline int ptr_not_null(void *p) { return p != NULL; }

/* whether UI is allowed to show "advertising" */
static bool g_adv_allowed = false;

/* clamp slot to known value when advertising starts */
static inline void adv_start_defaults(void) {
    uint8_t s = status_ble_slot_index();
    if (s > 7 && s != SLOT_WOL) {
        status__set_ble_slot(SLOT_WOL);
    }
}

/* policy: allow/deny advertising indicator */
void status_allow_advertising(bool allow) {
    g_adv_allowed = allow;
    if (!allow) {
        status__set_ble_advertising(false);
        status__set_ble_connected(false);
    }
}

/* BMP -> UI event bridge */
static bmp_error_t on_bmp_event(bmp_api_event_t ev) {
    switch (ev) {
        /* USB */
        case USB_CONNECTED:
        case USB_CDC_ACM_OPEND:
        case USB_HID_READY:
            status__set_output(OUT_USB);
            status__set_ble_advertising(false);
            status__set_ble_connected(false);
            break;

        case USB_CDC_ACM_CLOSED:
        case USB_DISCONNECTED:
            status__set_output(OUT_BLE);
            status__set_ble_advertising(false);
            status__set_ble_connected(false);
            break;

        /* BLE advertising */
        case BLE_ADVERTISING_START:
            if (!g_adv_allowed) {
                status__set_ble_advertising(false);
                status__set_ble_connected(false);
                break;
            }
            status__set_output(OUT_BLE);
            adv_start_defaults();
            status__set_ble_connected(false);
            status__set_ble_advertising(true);
            break;

        case BLE_ADVERTISING_STOP:
            status__set_ble_advertising(false);
            break;

        /* BLE connection */
        case BLE_CONNECTED:
            status__set_output(OUT_BLE);
            status__set_ble_advertising(false);
            status__set_ble_connected(true);
            /* do not modify slot here; keep the last advertised slot */
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

/* init: hook callback and allow advertising by default */
void status_init(void) {
    status__set_output(OUT_BLE);
    status__set_ble_connected(false);
    status__set_ble_advertising(false);

    if (BMPAPI && ptr_not_null(BMPAPI->app.set_state_change_cb)) {
        BMPAPI->app.set_state_change_cb(on_bmp_event);
    }
    status_allow_advertising(true);
}

/* tick: drop "connected" if link is gone */
void status_update_tick(void) {
    if (BMPAPI && ptr_not_null(BMPAPI->ble.get_connection_status)) {
        uint16_t st = BMPAPI->ble.get_connection_status();
        if (st == 0) {
            status__set_ble_connected(false);
        }
    }
}
