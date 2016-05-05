#include "localization.h"

void localization_setup(void) {
  sys_locale = setlocale(LC_ALL, "");
}

char * get_time_format(void) {
  return clock_is_24h_style() ? "%H:%M" : "%I:%M";
}

char * get_date_format(void) {
  if (strcmp("en_US", sys_locale) == 0)
    return "%a %h %e";
  else
    return "%a %e %h";
  
}