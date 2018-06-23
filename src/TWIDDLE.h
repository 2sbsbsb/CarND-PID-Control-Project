#ifndef TWIDDLE_H
#define TWIDDLE_H
#include <vector>
#include "PID.h"

class TWIDDLE {
    
public:

    std::vector<double> dp;
    int step, param_index;
    double best_err;
    bool increased_P, reduced_P;
    double best_error = 999.9;
    
  /*
  * Constructor
  */
  TWIDDLE();

  /*
  * Destructor.
  */
  virtual ~TWIDDLE();

  /*
  * Initialize Twiddle.
  */
  void Init();
  
  
  void tune(PID pid);

};

#endif /* Twiddle_H */
