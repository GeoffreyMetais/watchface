#pragma once
#include <pebble.h>
#include "windows/main_window.h"
#include "intl/localization.h"
#include "user_preferences.h"

static bool pulse = true, bt_icon = true;
void init_comm(void);
void setup_events_services(void);
void bluetooth_callback(bool connected);
void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void inbox_received_handler(DictionaryIterator *iter, void *context);
