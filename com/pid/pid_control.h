#ifndef PID_CONTROL_H
#define PID_CONTROL_H

typedef struct {
    double Kp, Ki, Kd;
    double setpoint;
    double prev_error;
    double integral;
    double output_min, output_max;
} PID_Controller;

void pid_init(PID_Controller *pid, double Kp, double Ki, double Kd, double setpoint, double output_min, double output_max);
double pid_compute(PID_Controller *pid, double input);

#endif
