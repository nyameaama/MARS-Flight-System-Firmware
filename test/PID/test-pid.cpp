<<<<<<< Updated upstream:test/PID/test-pid.cpp
#include"_pid.h"
=======
//#include"../_pid.h"
>>>>>>> Stashed changes:src/Control/test-pid.cpp
#include<iostream>
#include<string.h>

int main(){
    //Setup Object
    //PROPORTIONAL_INTEGRAL_DERIVATIVE *pObj = new PROPORTIONAL_INTEGRAL_DERIVATIVE();
    //pObj -> createPIDinstance("testInstance",0.5,0.1,0.3);
    //Run API
<<<<<<< Updated upstream:test/PID/test-pid.cpp
    double res = pObj -> PID_MAIN("testInstance", 70, 90);
    uint8_t f = pObj -> retTests();
    std::cout << res << std::endl;
    std::cout << f << std::endl;
=======
    //double res = pObj -> PID_MAIN("testInstance", 70, 90);
    //std::cout << res << std::endl;
>>>>>>> Stashed changes:src/Control/test-pid.cpp
}