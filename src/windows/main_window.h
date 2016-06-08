#pragma once
#include <pebble.h>

#if defined(PBL_ROUND)
  #define TIME_Y 48
  #define DATE_Y 103
  #define BT_X 55
#else
  #define TIME_Y 42
  #define DATE_Y 97
  #define BT_X 5
#endif

void main_window_setup();
void main_window_destroy(void);
void hide_bt(bool);
void set_time_text(const char *);
void set_date_text(const char *);
void set_time_font(GFont);
void set_date_font(GFont);
