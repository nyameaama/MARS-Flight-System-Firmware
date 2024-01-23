#ifndef PID
#define PID

//#include"../util/defi.h"

#include <stdint.h>
#include <string.h>

// Different instances of PID computation will be called from this class so each unique process will
// need to have constants stored so individual processes can be continued after end of class call

class PROPORTIONAL_INTEGRAL_DERIVATIVE
{
  private:
    uint8_t dt;

  private:
    void updateConstants(char* Process);

    double getProportional();

    double getIntegral();

    double getDerivative();

    bool compare(char* x, char* y);

    bool checkforInstance(char* tag);

  public:
    //
    double PID_MAIN(char* Process, double rocketPos, double setpoint);

    void createPIDinstance(char* tag, double kp, double ki, double kd);
};

#endif