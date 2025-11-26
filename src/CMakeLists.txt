add_subdirectory(log)
add_subdirectory(game_world)

add_executable(main
	main.cpp
	application.cpp
	state/game-state.cpp
	state/menu-state.cpp
	state/pause-state.cpp
)
target_include_directories(main PRIVATE .)  # Include current directory for headers
target_link_libraries(main PRIVATE log game_world)

target_compile_features(main PRIVATE cxx_std_17)

set_target_properties(main PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}"
)
