#ifndef PID_H
#define PID_H

#include <numeric>
#include <vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(std::vector<double> &k);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  bool Twiddle(double cte);

  bool ShouldSendMsg() { return iter < tuning_samples; }

 private:
  typedef std::vector<double> VD;

  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  VD dp;
  int dp_len = 3;
  int cur_idx = 0;
  int tuning_samples = 800;
  int iter = 0;
  int state = 0;
  double accumulated_error = 0.0;

  double tol = 0.001;
  double best_error = std::numeric_limits<double>::max();

  /**
   * PID Coefficients
   */
  VD K;
  double Kp;
  double Ki;
  double Kd;
};

#endif  // PID_H