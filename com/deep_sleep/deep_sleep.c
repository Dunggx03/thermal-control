#include "deep_sleep.h"
#include "esp_sleep.h"

void enter_deep_sleep() {
    printf("Entering deep sleep mode...\n");
    esp_sleep_enable_timer_wakeup(10000000);
    esp_deep_sleep_start();
}