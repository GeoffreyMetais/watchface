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
