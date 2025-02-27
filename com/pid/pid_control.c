#include "pid_control.h"

void pid_init(PID_Controller *pid, double Kp, double Ki, double Kd, double setpoint, double output_min, double output_max) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->setpoint = setpoint;
    pid->prev_error = 0;
    pid->integral = 0;
    pid->output_min = output_min;
    pid->output_max = output_max;
}

double pid_compute(PID_Controller *pid, double input) {
    double error = pid->setpoint - input;
    pid->integral += error;
    double derivative = error - pid->prev_error;
    pid->prev_error = error;

    double output = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative);

    if (output > pid->output_max) output = pid->output_max;
    if (output < pid->output_min) output = pid->output_min;

    return output;
}
