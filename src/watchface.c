#include <pebble.h>
#include "windows/main_window.h"
#include "intl/localization.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
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

static void bluetooth_callback(bool connected) {
  layer_set_hidden((Layer *)s_bitmap_layer, connected);
  vibes_double_pulse();
}

static void init(void) {
  localization_setup();
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  tick_handler(localtime(&(time_t){ time(NULL) }), MINUTE_UNIT|DAY_UNIT);

  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetooth_callback
  });
}

static void deinit(void) {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
