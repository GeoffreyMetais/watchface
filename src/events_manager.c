#include "events_manager.h"

static bool pulse, bt_icon;

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  setup_events_services(iter);

  // Read boolean preferences
  Tuple *pulse_t = dict_find(iter, AppKeyPulse);
  if (pulse_t)
    persist_write_bool(DataKeyPulse, pulse_t->value->int32);

  Tuple *bt_icon_t = dict_find(iter, AppKeyDisconnectIcon);
  if (bt_icon_t)
    persist_write_bool(DataKeyBtIcon, bt_icon_t->value->int32);

  Tuple *time_font_t = dict_find(iter, AppKeyTimeFont);
  if (time_font_t)
    persist_write_string(DataKeyTimeFont, time_font_t->value->cstring);

  Tuple *date_font_t = dict_find(iter, AppKeyDateFont);
  if (date_font_t)
    persist_write_string(DataKeyDateFont, date_font_t->value->cstring);
}

void init_comm(void) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(128, 0);
}

void setup_events_services(DictionaryIterator *iter) {
  char *time_font, *date_font;

  if (iter == NULL) {
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    tick_handler(localtime(&(time_t){ time(NULL) }), MINUTE_UNIT|DAY_UNIT);

    pulse = get_pulse_pref();
    bt_icon = get_bt_icon_pref();
    char buffer[FONT_BUFFER_SIZE];
    get_time_font_pref(buffer, FONT_BUFFER_SIZE);
    time_font = buffer;
    char date_buffer[FONT_BUFFER_SIZE];
    get_date_font_pref(date_buffer, FONT_BUFFER_SIZE);
    date_font = date_buffer;
  } else {
    // Read boolean preferences
    Tuple *pulse_t = dict_find(iter, AppKeyPulse);
    if (pulse_t)
      pulse = pulse_t->value->int32;

    Tuple *bt_icon_t = dict_find(iter, AppKeyDisconnectIcon);
    if (bt_icon_t)
      bt_icon = bt_icon_t->value->int32;

    Tuple *time_font_t = dict_find(iter, AppKeyTimeFont);
    if (time_font_t)
      time_font = time_font_t->value->cstring;
    else time_font = TIME_FONT_DEFAUT;

    Tuple *date_font_t = dict_find(iter, AppKeyDateFont);
    if (date_font_t)
      date_font = date_font_t->value->cstring;
    else date_font = TIME_FONT_DEFAUT;
  }

  if (pulse || bt_icon)
    connection_service_subscribe((ConnectionHandlers) {
      .pebble_app_connection_handler = bluetooth_callback
    });
  else
    connection_service_unsubscribe();

  hide_bt(!bt_icon || connection_service_peek_pebble_app_connection());

  set_time_font(fonts_get_system_font(time_font));
  set_date_font(fonts_get_system_font(date_font));
}

void bluetooth_callback(bool connected) {
  if (bt_icon)
    hide_bt(connected);
  if (pulse)
    vibes_double_pulse();
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed & DAY_UNIT) {
    static char s_date_buffer[12];
    strftime(s_date_buffer, sizeof(s_date_buffer), get_date_format(), tick_time);
    set_date_text(s_date_buffer);
  }
  if (units_changed & MINUTE_UNIT) {
    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), get_time_format() , tick_time);
    set_time_text(s_buffer);
  }
}
