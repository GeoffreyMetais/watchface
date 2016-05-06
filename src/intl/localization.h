#pragma once
#include <pebble.h>

static char * sys_locale, *date_format, *time_format;

void localization_setup(void);
char * get_time_format(void);
char * get_date_format(void);
