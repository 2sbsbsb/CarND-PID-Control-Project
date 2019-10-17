#ifndef PID_H
#define PID_H
#include <chrono>

enum cofficients{KP, KI, KD}; 

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);
  
  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  
  /**
   * Updating cofficients
   */
  void UpdateK(cofficients k, double delta);


  void printValues();
  
};

#endif /* PID_H */
