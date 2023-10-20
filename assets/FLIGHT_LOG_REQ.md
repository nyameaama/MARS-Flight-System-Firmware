# Flight Logs Requirements

### Periodic Sensor-Data-Dump (SDD)

Log event is periodic and triggered by event handler in main loop. Data dump expected every ~10 secs. 

Ex LOG SUBSYTEM API FUNCTION:
    uint8_t EVENT_LOGTYPE_SDD(void)

Function takes no parameters as this log event will query PTAM registers for all sensor data and the ID will remain the same for this process.

LOG_EVENT_SDD_#1
{
	ID: UAV-UNIT-23; // <- ID can remain the same
	TIME: 1692551000;
	MACHINE STATE: 5;
    WINGFL POS: xx;
    WINGFR POS: xx;
    WINGRL POS: xx;
    WINGRR POS: xx;
    CONTROLLER-TEMP: xx;
    PRESSURE: xx;
    LATITUDE: xx;
    LONGITUDE: xx;
    SATELLITES: xx;
    ALTITUDE: xx;
    ACCX: xx;
    ACCY: xx;
    ACCZ: xx;
    GYROX: xx;
    GYROY: xx;
    GYROZ: xx;
}


### Periodic System State Logs (SSL)

Log event is periodic and triggered by event handler in main loop. State logs expected every ~10 secs.

Ex LOG SUBSYTEM API FUNCTION:
    uint8_t EVENT_LOGTYPE_SSL(void)

Function takes no parameters as this log event will query PTAM registers for all system data and the ID will remain the same for this process.


LOG_EVENT_SSL_#1
{
    ID: UAV-UNIT-25;
	TIME: 1692551000;
	MACHINE STATE: 5;
    STATE: "ARMED";
    FAN-STATE: 0;
    BATTERY-VOLTAGE: 3.2;
    BATTERY-CALCULATED-PERCENT: 50;
    
}


### On Demand System Error Logs (SEL)

Log event is not periodic and is initiated by a failing routine in a submodule.

Ex LOG SUBSYTEM API FUNCTION:
    uint8_t LOG_EXCEPTION_TYPE(std::string ID, mars_exception_type _param1, std::string _info)

mars_exception_type is a struct with expected error types:
ROUTINE_SOFT_FAIL
ROUTINE_HARD_FAIL

This log event will take all data as parameters from calling subroutine.

LOG_EVENT_SEL#1
{
    ID: UAV-UNIT-33; //<-- ID will change based on calling subroutine
	TIME: 1692551000;
	MACHINE STATE: 5;
    EXCEPTION-TYPE: "";
    ADDITIONAL-INFO: "";
}