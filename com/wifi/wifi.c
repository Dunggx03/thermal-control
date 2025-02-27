#include "wifi.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"

void wifi_init() {
    printf("Initializing WiFi...\n");
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
}
