add_library(log STATIC
	log.cpp
)

target_include_directories(log PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(log
    PRIVATE LOG_OUTPUT_PATH="${CMAKE_BINARY_DIR}/application.log")
