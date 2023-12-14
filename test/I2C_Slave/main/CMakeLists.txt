idf_component_register(SRCS   "I2C_Slave_testing.cpp"
                              #"i2c_cxx_main.cpp"
                            "../i2c_slave.cpp"
                            #"home/alucard/esp/esp-idf-cxx/i2c_cxx.cpp"
                       INCLUDE_DIRS "/home/alucard/esp/esp-idf-cxx/" "/home/alucard/esp/esp-idf-cxx/include"
                                   "/home/alucard/esp/esp-idf-cxx/host_test/fixtures/" "/home/alucard/esp/esp-idf/tools/catch/"
                       # Add any other relevant configuration options
)
idf_build_get_property("PROJECT_COMPONENT_DIRS" PROJECT_COMPONENT_DIRS)
foreach(COMPONENT_DIR ${PROJECT_COMPONENT_DIRS})
    target_compile_definitions(${COMPONENT_TARGET} PRIVATE -DCONFIG_SOC_I2C_SUPPORT_SLAVE=1)
endforeach()
