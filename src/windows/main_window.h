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

Window *s_main_window;
TextLayer *s_time_layer;
TextLayer *s_date_layer;
BitmapLayer *s_bitmap_layer;
static GBitmap *s_bitmap;

static void main_window_load(Window *window);
static void main_window_unload(Window *window);
void main_window_setup();
