// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "print.h"

#ifdef HPY69_DEBUG_BLE
#    define HPY69_LOG_BLE(...) uprintf(__VA_ARGS__)
#else
#    define HPY69_LOG_BLE(...) ((void)0)
#endif

#ifdef HPY69_DEBUG_OLED
#    define HPY69_LOG_OLED(...) uprintf(__VA_ARGS__)
#else
#    define HPY69_LOG_OLED(...) ((void)0)
#endif

#ifdef HPY69_DEBUG_POINTING
#    define HPY69_LOG_POINTING(...) uprintf(__VA_ARGS__)
#else
#    define HPY69_LOG_POINTING(...) ((void)0)
#endif
