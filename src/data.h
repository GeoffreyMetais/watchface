#pragma once
#include <pebble.h>

#define PULSE_DEFAULT true
#define BT_ICON_DEFAUT true

typedef enum {
  AppKeyPulse = 0,
  AppKeyDisconnectIcon = 1,
} AppKey;

typedef enum {
  DataKeyPulse = 0,
  DataKeyBtIcon = 1,
} DataKey;

bool get_pulse_pref();
bool get_bt_icon_pref();
