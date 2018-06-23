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
    dp = {1,1,1};
    step = 1;
    param_index = 1;
    increased_P = false;
    reduced_P = false;
    best_error = 1000;
}

/**
 * @brief 
 * @param pid
 */
void TWIDDLE::tune(PID pid) {
    
    return;
}