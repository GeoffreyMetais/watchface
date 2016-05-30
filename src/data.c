#include "data.h"

bool get_pulse_pref() {
  if (persist_exists(DataKeyPulse))
    return persist_read_bool(DataKeyPulse);
  return PULSE_DEFAULT;
}

bool get_bt_icon_pref() {
  if (persist_exists(DataKeyBtIcon))
    return persist_read_bool(DataKeyBtIcon);
  return BT_ICON_DEFAUT;
}

void get_time_font_pref(char *buffer, int buffer_size) {
  if (persist_exists(DataKeyTimeFont)){
    persist_read_string(DataKeyTimeFont, buffer, buffer_size);
    return;
  }
  buffer = TIME_FONT_DEFAUT;
}
