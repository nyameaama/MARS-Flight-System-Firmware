idf_component_register(SRCS   "I2C_Slave_testing.cpp"
                              #"i2c_cxx_main.cpp"
                              "../i2c_slave.cpp"
                              "../../Logging/logger.cpp"
                              "../../statemachine/_ptam.cpp"
                       INCLUDE_DIRS "/home/alucard/esp/esp-idf-cxx/" "/home/alucard/esp/esp-idf-cxx/include"
)