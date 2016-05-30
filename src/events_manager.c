#include "events_manager.h"

void init_comm(void) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(64, 64);
}

void setup_events_services(void) {
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  tick_handler(localtime(&(time_t){ time(NULL) }), MINUTE_UNIT|DAY_UNIT);

  pulse = get_pulse_pref();
  bt_icon = get_bt_icon_pref();
  if (pulse || bt_icon)
    connection_service_subscribe((ConnectionHandlers) {
      .pebble_app_connection_handler = bluetooth_callback
  });
  layer_set_hidden((Layer *)s_bitmap_layer, !bt_icon || connection_service_peek_pebble_app_connection());

  char buffer[TIME_FONT_BUFFER_SIZE];
  get_time_font_pref(buffer, TIME_FONT_BUFFER_SIZE);
  text_layer_set_font(s_time_layer, fonts_get_system_font(buffer));
}

void bluetooth_callback(bool connected) {
  if (bt_icon)
    layer_set_hidden((Layer *)s_bitmap_layer, connected);
  if (pulse)
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

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  // Read boolean preferences
  Tuple *pulse_t = dict_find(iter, AppKeyPulse);
  if (pulse_t)
    pulse = pulse_t->value->int32 == 1;

  Tuple *bt_icon_t = dict_find(iter, AppKeyDisconnectIcon);
  if (bt_icon_t)
    bt_icon = bt_icon_t->value->int32 == 1;

  Tuple *time_font_t = dict_find(iter, AppKeyTimeFont);
  if (time_font_t)
    persist_write_string(DataKeyTimeFont, time_font_t->value->cstring);

  persist_write_bool(DataKeyPulse, pulse);
  persist_write_bool(DataKeyBtIcon, bt_icon);

  setup_events_services();
}
