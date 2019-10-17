#ifndef TWIDDLE_H
#define TWIDDLE_H
#include <vector>
#include "PID.h"

class TWIDDLE {
    
public:

    std::vector<double> dp;
    int step, param_index;
    int twiddle_after_step;
    double best_error;
    bool adding, substracting, tried_adding, tried_subtracting;    
    
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
  
  
  void tune(PID* pid,double total_error);

};

#endif /* Twiddle_H */
