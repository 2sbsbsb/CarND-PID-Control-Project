#include "PID.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    // initializing all the errors variables to zero
    p_error = 0;
    i_error = 0;
    d_error = 0;
}

void PID::UpdateError(double cte) {
    
    // Assuming that delta time is always constant between measurement so that the effect of it is neligible (1)
    double dt = 1;
    
    // previous cte is stored in p_error so using it to calculate the d_error
    d_error = (cte - p_error)/dt;
    p_error = cte;
    i_error += (cte * dt);
}

double PID::TotalError() {
    // Total error is summation of the three components (proportional, integral and differential)
    return (Kp * p_error + Ki * i_error + Kd * d_error);
}
  

void PID::UpdateK(cofficients k, double delta) {
    
    std::cout << "UpdateK " << k << std::endl;   

    if (k == KP) {
        Kp += delta;
        std::cout << "New Kp :" << Kp << std::endl;
    }
    else if (k == KI) {
        Ki += delta;
        std::cout << "New Ki :" << Ki << std::endl;
    }
    else if (k == KD) {
        Kd += delta;
        std::cout << "New Kd :" << Kd << std::endl;
    }
    else {
        std::cout << "UpdateP index out of bounds";
    }

    //printValues();
}


    void PID::printValues() {
        std::cout <<"Kp: " << this->Kp << " Ki: " << this->Ki << " Kd: " << this->Kd << std::endl;        
    }
