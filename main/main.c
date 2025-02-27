#include <stdio.h>
#include "wifi.h"
#include "ntp_time.h"
#include "sensor.h"
#include "pid_control.h"
#include "motor_control.h"
#include "deep_sleep.h"
#include "lcd_i2c.h"

PID_Controller pid_cooling;  // PID cho chế độ làm mát
PID_Controller pid_heating;  // PID cho chế độ làm nóng

void app_main() {
    printf("Initializing system...\n");
    
    wifi_init();
    ntp_init();
    sensor_init();

    // Khởi tạo PID: Kp, Ki, Kd, setpoint, min_output, max_output
    pid_init(&pid_cooling, 40, 5, 1, 24, 0, 255);
    pid_init(&pid_heating, 30, 4, 1.5, 24, 0, 255);

    motor_init();
    lcd_init();

    lcd_clear();
    lcd_print("System Start!");

    while (1) {
        float temperature = read_temperature();
        printf("Temperature: %.2f C\n", temperature);

        if (isnan(temperature)) {
            printf("Sensor error, entering deep sleep...\n");
            enter_deep_sleep();
        }

        double output;
        if (temperature > 24) {
            output = pid_compute(&pid_cooling, temperature);  // Nếu nhiệt độ cao → Làm mát
        } else {
            output = pid_compute(&pid_heating, temperature);  // Nếu nhiệt độ thấp → Làm nóng
        }

        control_motor(output, temperature);

        char buffer[16];
        snprintf(buffer, sizeof(buffer), "Temp: %.2f C", temperature);
        lcd_clear();
        lcd_print(buffer);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
