#include "pid.h"
#include "constants.h"
#include <Arduino.h>

PIDController::PIDController(double p_gain, double i_gain, double d_gain, long interval) {
  this->p_gain = p_gain;
  this->i_gain = i_gain;
  this->d_gain = d_gain;
  this->prev_error = 0;
  this->prev_i_out = 0;
  interval_in_millis = interval;
}

double PIDController::pid(double error, double *p_out, double *i_out, double *d_out) {
  *p_out = error * p_gain;
  *i_out = prev_i_out + (error * PID_INTERVAL_IN_MILLIS * i_gain);
  *d_out = (error - prev_error) * d_gain;

  // cut i value for safety
  //p_out = constrain(p_out, -P_MAX, P_MAX);
  *i_out = constrain(*i_out, -I_MAX, I_MAX);
  //d_out = constrain(d_out, -D_MAX, D_MAX);

  prev_error = error;
  prev_i_out = *i_out;
  return *p_out + *i_out + *d_out;
}

double PIDController::pid(double error) {
  double p_out, i_out, d_out;
  
  return pid(error, &p_out, &i_out, &d_out);
}

