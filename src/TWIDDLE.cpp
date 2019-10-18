#include "TWIDDLE.h"
#include <stdlib.h>
#include "PID.h"
#include <iostream>
#include <math.h>  

using namespace std;

TWIDDLE::TWIDDLE() {}

TWIDDLE::~TWIDDLE() {}

void TWIDDLE::Init() {
    //
    twiddle_after_step = 100;
    dp = {0.001,0.001,0.001};
    step = 1;
    param_index = 0;
    best_error = std::numeric_limits<double>::max();    
    adding = false; 
    substracting = false;
    tried_adding = false; 
    tried_subtracting = false;
}

/**
 * The twiddle alogorithm is independent of algorithm. pid in paramer is just to update the cofficient Kpid 
 */
void TWIDDLE::tune(PID* pid, double cte) {

      double error = cte * cte; 

     if (step % (twiddle_after_step) == 0) {  	     	
  		cout << "step: " << step << endl;
        cout << "total error: " << error << endl;
        cout << "best error: " << error << endl;        
        pid->printValues();

        cofficients cofficient = cofficients(param_index);

        if (error < best_error) {
            cout << "Improvement while adding " << adding << " substracting " << substracting << " for " << cofficient << endl;
            best_error = error;
            dp[param_index] *= 1.1;			                    
		} else {			
			// If it happened due to adding, reduce the amount 
			if(adding) {
                cout << "Adding didn't worked out ";
				pid->UpdateK(cofficient,-1 * dp[param_index]);
			}
			// If it happened due to substracting, increase the amount 
			else if(substracting) {
                cout << "substracting didn't worked out ";
				pid->UpdateK(cofficient, dp[param_index]);
			}
			if(tried_adding && tried_subtracting) {
				// Decrease the step size 
                cout << "Reducing the step size didn't worked out ";
				dp[param_index] *= 0.95;			
			}

		}

		if (!tried_adding && !tried_subtracting) {
            cout << "Trying adding";
            pid->UpdateK(cofficient,dp[param_index]);
            adding = true; 
            substracting = false; 
            tried_adding = true;
        }
        else if (tried_adding && !tried_subtracting) {
            // try substracting dp[i] from params[i]
            cout << "Trying substracting";
            pid->UpdateK(cofficient,-dp[param_index]);
            substracting = true; 
            adding = false; 
            tried_subtracting = true;         
        } else {

        }

		// Once adding and substracting is tried out, try now with the next parameters
        if(tried_adding && tried_subtracting) {
          cout << "Try moving to the next cofficient" << cofficient << endl;
      	  // Next parameter
          param_index = (param_index + 1) % 3; 
          adding = false; 
          substracting = false;
          tried_adding = false;
          tried_subtracting = false;
        }

	}
    
    step++; 
    return;
}