idf_component_register(SRCS "logger_unittest.c"
    "../logger.cpp"
    #"../../statemachine/_ptam.cpp"
    )

#target_compile_definitions(${COMPONENT_TARGET} PUBLIC "-DLOG_VERBOSITY_LOW")
