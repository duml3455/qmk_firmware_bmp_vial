// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <stdint.h>
#include "progmem.h"

// All images are 128x32 -> 512 bytes
#define IMG_BYTES (128 * 32 / 8)

// USB
extern const uint8_t PROGMEM IMG_USB[IMG_BYTES];

// BLE: disconnected/idle
extern const uint8_t PROGMEM IMG_BLE_IDLE[IMG_BYTES];

// BLE: advertising without whitelist
extern const uint8_t PROGMEM IMG_BLE_ADV_WOL[IMG_BYTES];

// BLE: advertising slot 0 to 7
extern const uint8_t PROGMEM IMG_BLE_ADV_0[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_1[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_2[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_3[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_4[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_5[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_6[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_ADV_7[IMG_BYTES];

// BLE: connected slot 0 to 7
extern const uint8_t PROGMEM IMG_BLE_CONN_0[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_1[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_2[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_3[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_4[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_5[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_6[IMG_BYTES];
extern const uint8_t PROGMEM IMG_BLE_CONN_7[IMG_BYTES];
