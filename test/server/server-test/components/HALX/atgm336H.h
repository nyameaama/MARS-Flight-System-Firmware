#ifndef ATGM336HX
#define ATGM336HX

#include<vector>

class ATGM336H {
    public:
        static void init_ATGM_module();

        static char* pullATGM_data();

        static void updateStack();

        static double getLatitude();

        static double getLongitude();

        static double getAltitude();

        static double getSpeed();

        std::vector<int> getTimeVector();
};

#endif //ATGM336HX