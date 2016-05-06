#pragma once
#include <pebble.h>

Window *s_main_window;
TextLayer *s_time_layer;
TextLayer *s_date_layer;
BitmapLayer *s_bitmap_layer;
static GBitmap *s_bitmap;

void main_window_load(Window *window);
void main_window_unload(Window *window);
