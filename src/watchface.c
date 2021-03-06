#include <pebble.h>
#include "windows/main_window.h"
#include "intl/localization.h"
#include "events_manager.h"

static void init(void) {
  localization_setup();
  main_window_setup();
  setup_events_services(NULL);
  init_comm();
}

static void deinit(void) {
  main_window_destroy();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
