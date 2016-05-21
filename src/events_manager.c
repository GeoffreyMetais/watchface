#include "include/events_manager.h"

void setup_events_services(void) {
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  tick_handler(localtime(&(time_t){ time(NULL) }), MINUTE_UNIT|DAY_UNIT);
  
  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetooth_callback
  });
}

void bluetooth_callback(bool connected) {
  layer_set_hidden((Layer *)s_bitmap_layer, connected);
  vibes_double_pulse();
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed & DAY_UNIT) {
    static char s_date_buffer[12];
    strftime(s_date_buffer, sizeof(s_date_buffer), get_date_format(), tick_time);
    text_layer_set_text(s_date_layer, s_date_buffer);
  }
  if (units_changed & MINUTE_UNIT) {
    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), get_time_format() , tick_time);
    text_layer_set_text(s_time_layer, s_buffer);
  }
}
