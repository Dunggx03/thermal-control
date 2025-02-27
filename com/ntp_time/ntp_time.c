#include "ntp_time.h"
#include "lwip/apps/sntp.h"

void ntp_init() {
    printf("Initializing NTP...\n");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}