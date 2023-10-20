#include"_wingDynamics.h"
#include<iostream>

int main(){
    _WING_DYNAMICS *obj = new _WING_DYNAMICS();
    std::cout << obj ->_translateDown(20,SIMULTANEOUS);
    delete obj;
}