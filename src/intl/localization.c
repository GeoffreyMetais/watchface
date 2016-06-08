#include "localization.h"

static char * sys_locale, *date_format, *time_format;

void localization_setup(void) {
  sys_locale = setlocale(LC_ALL, "");
  if (!strcmp("en_US", sys_locale) || !strcmp("en_CN", sys_locale) || !strcmp("en_TW", sys_locale))
    date_format = "%a %h %e";
  else
    date_format = "%a %e %h";
  time_format = clock_is_24h_style() ? "%H:%M" : "%I:%M";
}

char * get_time_format(void) {
  return time_format;
}

char * get_date_format(void) {
  return date_format;
}
