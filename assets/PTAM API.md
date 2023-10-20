# Program Temporary Access Memory (PTAM)

### PTAM member functions 

* storeString(): 
* storeDouble():
* storeInt():
* getStringData():
* getDoubleData(): 
* getIntData():
* clearData():
* clearAllData():
* getLastString():
* getLastDouble():
* getLastInt():

### Function Documentation

            void storeString(const std::string& id, const std::string& data)

<b> Returns: </b>
    None

<b> Parameters:</b>

* Designated ID - This creates the PTAM register with this ID an can only be referenced with this ID string
* Data Value <std::string> - Data value of type <std::string>


---------------------------------------------------------

            void storeDouble(const std::string& id, double data)

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This creates the PTAM register with this ID an can only be referenced with this ID string
* Data Value <double> - Data value of type <double>

---------------------------------------------------------

            void storeInt(const std::string& id, int data)

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This creates the PTAM register with this ID an can only be referenced with this ID string
* Data Value <int> - Data value of type <int>

---------------------------------------------------------

            std::vector<std::string> getStringData(const std::string& id)

<b> Returns: </b>
    std::vector<std::string>
    Function returns a vector of all the values stored in the specific PTAM register since program boot

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

--------------------------------------------------------

            std::vector<double> getDoubleData(const std::string& id)

<b> Returns: </b>
    std::vector<double>
    Function returns a vector of all the values stored in the specific PTAM register since program boot

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            std::vector<int> getIntData(const std::string& id)

<b> Returns: </b>
    std::vector<int>
    Function returns a vector of all the values stored in the specific PTAM register since program boot

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            void clearData(const std::string& id)

Function clears all data stored in a vector from a specific PTAM register

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            void clearAllData()

Function clears all data in all PTAM reggisters (!! Danger Zone !!)

<b> Returns: </b>
    None

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            std::string getLastString(const std::string& id)

<b> Returns: </b>
    std::string
    Function returns the most recent value stored in the PTAM register of type<std::string>. 

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

--------------------------------------------------------

            double getLastDouble(const std::string& id)

<b> Returns: </b>
    double
    Function returns the most recent value stored in the PTAM register of type<double>.

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

            int getLastInt(const std::string& id)

<b> Returns: </b>
    double
    Function returns the most recent value stored in the PTAM register of type<int>.

<b> Parameters: </b>

* Designated ID - This references the PTAM register assigned with this ID

---------------------------------------------------------

PTAM REGISTERS

"state" -> <int>
- Register to store the vehile current state as integer (0 - 2) (Used in main statemchine)

"stateDescript" -> <string>
- Register to store the vehicle current state as string (STANDBY, ARMED, BYPASS)

"GPScheck" -> <int>
- Register for sensor validator submodule (GPS flag)

"IMUcheck" -> <int>
- Register for sensor validator submodule (IMU flag)

"BMPcheck" -> <int>
- Register for sensor validator submodule (Barometer flag)

"setupSFlag" -> <int>
- Register for initialization process

"TLat" -> <double>
- Register for web interface target latitude input

"TLong" -> <double>
- Register for web interface target longitude input

"TAlt" -> <double>
- Register for web interface target altitude input

"CAlt" -> <double>
- Register for web interface cruise altitude input

"TVel" -> <double>
- Register for web interface cruise velocity input

"WingFL" -> <double>
- Register for current wing position (Front Left Servo)

"FL-ref-byp" -> <double>
- Reference Register for FL wing (Direct servo access subroutine requires  a reference register to determine if user has requested movement of wing or throttle)

"WingFR" -> <double>
- Register for current wing position (Front Right Servo)

"FR-ref-byp" -> <double>
- Reference Register for FR wing (Direct servo access subroutine requires  a reference register to determine if user has requested movement of wing or throttle)

"WingRL" -> <double>
- Register for current wing position (Rear Left Servo)

"RL-ref-byp" -> <double>
- Reference Register for RL wing (Direct servo access subroutine requires  a reference register to determine if user has requested movement of wing or throttle)

"WingRR" -> <double>
- Register for current wing position (Rear Right Servo)

"RR-ref-byp" -> <double>
- Reference Register for RR wing (Direct servo access subroutine requires  a reference register to determine if user has requested movement of wing or throttle)

"THR" -> <double>
- Register for current throttle position

"THR-ref-byp" -> <double>
- Reference Register for throttle (Direct servo access subroutine requires  a reference register to determine if user has requested movement of wing or throttle)