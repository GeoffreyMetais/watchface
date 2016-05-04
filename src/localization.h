#pragma once
#include <pebble.h>

char * sys_locale;

void localization_setup(void);
char * get_time_format(void);
char * get_date_format(void);