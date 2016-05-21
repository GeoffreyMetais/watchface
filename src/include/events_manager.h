#include <pebble.h>
#include "windows/main_window.h"
#include "intl/localization.h"

void setup_events_services(void);
void bluetooth_callback(bool connected);
void tick_handler(struct tm *tick_time, TimeUnits units_changed);
