#pragma once
#include <pebble.h>

Window *s_main_window;
TextLayer *s_time_layer;
TextLayer *s_date_layer;

void main_window_load(Window *window);
void main_window_unload(Window *window);
