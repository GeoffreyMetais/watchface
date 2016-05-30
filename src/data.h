#pragma once
#include <pebble.h>

#define PULSE_DEFAULT true
#define BT_ICON_DEFAUT true
#define TIME_FONT_DEFAUT "RESOURCE_ID_BITHAM_42_LIGHT"

typedef enum {
  AppKeyPulse = 0,
  AppKeyDisconnectIcon = 1,
  AppKeyTimeFont = 2,
} AppKey;

typedef enum {
  DataKeyPulse = 0,
  DataKeyBtIcon = 1,
  DataKeyTimeFont = 2,
} DataKey;


bool get_pulse_pref();
bool get_bt_icon_pref();
void get_time_font_pref(char *, int);
