#include "motor_control.h"
#include "driver/gpio.h"

#define MOTOR_PIN 18

void motor_init() {
    printf("Initializing motor control...\n");
    gpio_pad_select_gpio(MOTOR_PIN);
    gpio_set_direction(MOTOR_PIN, GPIO_MODE_OUTPUT);
}

void control_motor(double output, float temperature) {
    printf("Setting motor output to: %.2f\n", output);
    gpio_set_level(MOTOR_PIN, output > 0 ? 1 : 0);
}
