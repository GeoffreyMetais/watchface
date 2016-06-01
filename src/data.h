#pragma once
#include <pebble.h>

#define PULSE_DEFAULT true
#define BT_ICON_DEFAUT true
#define TIME_FONT_DEFAUT "RESOURCE_ID_BITHAM_42_LIGHT"
#define DATE_FONT_DEFAUT "RESOURCE_ID_ROBOTO_CONDENSED_21"

typedef enum {
  AppKeyPulse = 0,
  AppKeyDisconnectIcon = 1,
  AppKeyTimeFont = 2,
  AppKeyDateFont = 3,
} AppKey;

typedef enum {
  DataKeyPulse = 0,
  DataKeyBtIcon = 1,
  DataKeyTimeFont = 2,
  DataKeyDateFont = 3,
} DataKey;


bool get_pulse_pref();
bool get_bt_icon_pref();
void get_time_font_pref(char *, int);
void get_date_font_pref(char *, int);
