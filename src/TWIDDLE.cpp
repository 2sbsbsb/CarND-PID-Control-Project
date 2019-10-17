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
    dp = {0.1,0.1,0.1};
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
void TWIDDLE::tune(PID* pid, double total_error) {


     if (step % (twiddle_after_step) == 0) {  	     	
  		cout << "step: " << step << endl;
        cout << "total error: " << total_error << endl;
        cout << "best error: " << best_error << endl;        
        cofficients cofficient = cofficients(param_index);

        if (total_error < best_error) {
            cout << "improvement!" << endl;
            best_error = total_error;
            dp[param_index] *= 1.1;			                    
		} else {			
			// If it happened due to adding, reduce the amount 
			if(adding) {
				pid->UpdateK(cofficient,-dp[param_index]);
			}
			// If it happened due to substracting, reduce the amount 
			else if(substracting) {
				pid->UpdateK(cofficient,+dp[param_index]);
			}
			if(tried_adding && tried_subtracting) {
				// Decrease the step size 
				dp[param_index] *= 0.95;			
			}

		}

		if (!tried_adding && !tried_subtracting) {
            pid->UpdateK(cofficient,dp[param_index]);
            adding = true; 
            substracting = false; 
            tried_adding = true;
        }
        else if (tried_adding && !tried_subtracting) {
            // try subtracting dp[i] from params[i]
            pid->UpdateK(cofficient,-dp[param_index]);
            substracting = true; 
            adding = false; 
            tried_subtracting = true;         
        } else {

        }

		// Once adding and substrating is tried out, try now with the next parameters
        if(tried_adding && tried_subtracting) {
      	  // Next parameter
          param_index = (param_index + 1) % 3; 
          tried_adding = false;
          tried_subtracting = false;
        }

	}
    
    step++; 
    return;
}