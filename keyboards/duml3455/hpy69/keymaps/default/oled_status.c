// SPDX-License-Identifier: GPL-2.0-or-later

#include "oled_status.h"

#ifdef OLED_ENABLE

#    include "bmp_status.h"
#    include "hpy69_debug.h"
#    include "images.h"

static bool g_show_advertising_ui = true;

static const uint8_t *IMG_ADV[8] = {
    IMG_BLE_ADV_0, IMG_BLE_ADV_1, IMG_BLE_ADV_2, IMG_BLE_ADV_3,
    IMG_BLE_ADV_4, IMG_BLE_ADV_5, IMG_BLE_ADV_6, IMG_BLE_ADV_7,
};

static const uint8_t *IMG_CONN[8] = {
    IMG_BLE_CONN_0, IMG_BLE_CONN_1, IMG_BLE_CONN_2, IMG_BLE_CONN_3,
    IMG_BLE_CONN_4, IMG_BLE_CONN_5, IMG_BLE_CONN_6, IMG_BLE_CONN_7,
};

void oled_status_init(void) {
    g_show_advertising_ui = true;
}

void oled_status_set_advertising_ui_enabled(bool enabled) {
    g_show_advertising_ui = enabled;
}

oled_rotation_t oled_status_init_user(oled_rotation_t rotation) {
    return rotation;
}

bool oled_status_task_user(void) {
    const uint8_t *img = IMG_BLE_IDLE;
    bool           conn;
    bool           adv;
    uint8_t        slot;
    output_t       out = status_current_output();

    static const uint8_t *prev_img  = NULL;
    static bool           prev_conn = false;
    static bool           prev_adv  = false;
    static uint8_t        prev_slot = SLOT_WOL;
    static output_t       prev_out  = OUT_UNKNOWN;

    if (out == OUT_USB) {
        img  = IMG_USB;
        conn = false;
        adv  = false;
        slot = SLOT_WOL;
    } else {
        conn = status_ble_is_connected();
        adv  = status_ble_is_advertising();
        slot = status_ble_slot_index();

        bool show_adv_ui = g_show_advertising_ui && (adv || (conn && (slot > 7)));

        if (conn && !show_adv_ui) {
            img = IMG_CONN[slot & 7];
        } else if (show_adv_ui) {
            img = (slot == SLOT_WOL) ? IMG_BLE_ADV_WOL
            : ((slot <= 7) ? IMG_ADV[slot & 7] : IMG_BLE_ADV_WOL);
        } else {
            img = IMG_BLE_IDLE;
        }
    }

    if (img != prev_img || conn != prev_conn || adv != prev_adv || slot != prev_slot || out != prev_out) {
        HPY69_LOG_OLED("hpy69: oled out=%u conn=%u adv=%u slot=%u img=%p\n",
                       (unsigned)out,
                       (unsigned)conn,
                       (unsigned)adv,
                       (unsigned)slot,
                       img);
        prev_img  = img;
        prev_conn = conn;
        prev_adv  = adv;
        prev_slot = slot;
        prev_out  = out;
    }

    oled_write_raw_P((const char *)img, IMG_BYTES);
    return false;
}

#endif
