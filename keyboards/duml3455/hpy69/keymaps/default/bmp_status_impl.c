// SPDX-License-Identifier: GPL-2.0-or-later
#include "bmp_status.h"
#include "tmk_core/protocol/bmp/apidef.h"
#include <stddef.h>
#include <stdint.h>

static inline int ptr_not_null(void *p) { return p != NULL; }

static inline bool status_can_read_connection(void) {
    return BMPAPI && ptr_not_null(BMPAPI->ble.get_connection_status);
}

static uint8_t status_read_connected_slot(void) {
    if (!status_can_read_connection()) {
        return SLOT_WOL;
    }

    uint16_t st = BMPAPI->ble.get_connection_status();
    if (st == 0) {
        return SLOT_WOL;
    }

    uint8_t slot = (uint8_t)(st & 0xff);
    return (slot <= 7) ? slot : SLOT_WOL;
}

static bool status_is_ble_connected_now(void) {
    return status_can_read_connection() && BMPAPI->ble.get_connection_status() != 0;
}

/* clamp slot to known value when advertising starts */
static inline void adv_start_defaults(void) {
    uint8_t s = status_ble_slot_index();
    if (s > 7 && s != SLOT_WOL) {
        status_set_ble_slot(SLOT_WOL);
    }
}

static void status_sync_connected_state(void) {
    if (!status_can_read_connection()) {
        return;
    }

    if (status_is_ble_connected_now()) {
        status_set_ble_connected(true);
        status_set_ble_slot(status_read_connected_slot());
    } else {
        status_set_ble_connected(false);
    }
}

/* BMP -> UI event bridge */
static bmp_error_t on_bmp_event(bmp_api_event_t ev) {
    switch (ev) {
        /* USB */
        case USB_CONNECTED:
        case USB_CDC_ACM_OPEND:
        case USB_HID_READY:
            status_set_output(OUT_USB);
            status_set_ble_advertising(false);
            status_set_ble_connected(false);
            break;

        case USB_CDC_ACM_CLOSED:
        case USB_DISCONNECTED:
            status_set_output(OUT_BLE);
            status_set_ble_advertising(false);
            status_set_ble_connected(false);
            break;

        /* BLE advertising */
        case BLE_ADVERTISING_START:
            status_set_output(OUT_BLE);
            adv_start_defaults();
            status_set_ble_connected(false);
            status_set_ble_advertising(true);
            break;

        case BLE_ADVERTISING_STOP:
            status_set_ble_advertising(false);
            break;

        /* BLE connection */
        case BLE_CONNECTED:
            status_set_output(OUT_BLE);
            status_set_ble_advertising(false);
            status_sync_connected_state();
            break;

        case BLE_DISCONNECTED:
            status_set_ble_connected(false);
            status_set_ble_advertising(false);
            break;

        default:
            break;
    }
    return 0;
}

/* init: hook callback and allow advertising by default */
void status_init(void) {
    status_set_output(OUT_BLE);
    status_set_ble_connected(false);
    status_set_ble_advertising(false);

    if (BMPAPI && ptr_not_null(BMPAPI->app.set_state_change_cb)) {
        BMPAPI->app.set_state_change_cb(on_bmp_event);
    }
}

/* tick: drop "connected" if link is gone */
void status_update_tick(void) {
    status_sync_connected_state();
}
