#pragma once
#include <pebble.h>
#include "include/data.h"
#include "windows/main_window.h"
#include "intl/localization.h"

static bool pulse, bt_icon;

void init_comm(void);
void setup_events_services(void);
void bluetooth_callback(bool connected);
void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void inbox_received_handler(DictionaryIterator *iter, void *context);
