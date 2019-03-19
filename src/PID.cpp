#include "PID.h"
#include <math.h>
#include <limits>
#include <iostream>
#include <vector>

PID::PID() {}

PID::~PID() {}

void PID::Init(std::vector<double> &k) {
  K = k;
  dp = {.5, .5, .5};
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
}

/**
 * Update PID errors based on cte.
 */
void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
  double steer = -K[0] * p_error - K[1] * i_error - K[2] * d_error;
  return steer;
}

bool PID::Twiddle(double cte) {
  if ((dp[0]+dp[1]+dp[2])<=tol) {
    return true;
  }
  double mse;
  if (iter++ < tuning_samples && state != 0) {
    accumulated_error += pow(cte, 2);
  } else {
    switch (state) {
      case 0:
        K[cur_idx] += dp[cur_idx];
        state = 1;
        break;
      case 1:
        mse = accumulated_error/tuning_samples;
        if (mse < best_error) {
          best_error = mse;
          dp[cur_idx] *= 1.1;
          cur_idx = (cur_idx+1) % dp_len;
          state = 0;
        } else {
          K[cur_idx] -= 2*dp[cur_idx];
          state = 2;
        }
        break;
      case 2:
        mse = accumulated_error/tuning_samples;
        if (mse < best_error) {
          best_error = mse;
          dp[cur_idx] *= 1.1;
        } else {
          K[cur_idx] += dp[cur_idx];
          dp[cur_idx] *= 0.9;
        }
        state = 0;
        cur_idx = (cur_idx+1) % dp_len;
        break;
      default:
        std::cout<< "default" << std::endl;
        break;
    }
    std::cout << best_error <<","<<K[0] <<","<<K[1]<<","<<K[2]<< " cur_idx: " << cur_idx << std::endl;
    std::cout <<dp[0] <<","<<dp[1]<<","<<dp[2]<< " state: " << state << " mse: " << mse << std::endl;
    iter = 0;
    accumulated_error = 0.0;
    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;
  }
  return false;
}