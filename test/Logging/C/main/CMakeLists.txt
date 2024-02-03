idf_component_register(SRCS "logger_unittest.c"
    "../logger.c"
    "../../../PTAM/C/_ptam.c"
    )

#target_compile_definitions(${COMPONENT_TARGET} PUBLIC "-DLOG_VERBOSITY_LOW")
