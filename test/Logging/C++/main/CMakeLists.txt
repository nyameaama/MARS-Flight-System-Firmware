idf_component_register(SRCS "unittest_logger.cpp"
    "../logger.cpp"
    "../../../statemachine/_ptam.cpp")

#target_compile_definitions(${COMPONENT_TARGET} PUBLIC "-DLOG_VERBOSITY_LOW")
