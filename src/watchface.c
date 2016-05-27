#include <pebble.h>
#include "include/windows/main_window.h"
#include "include/intl/localization.h"
#include "include/events_manager.h"

static void init(void) {
  localization_setup();
  setup_events_services();
  main_window_setup();
  init_comm();
}

static void deinit(void) {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
