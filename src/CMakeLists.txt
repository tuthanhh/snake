add_executable(main
	main.cpp
	menu-state.cpp
	application.cpp
	game-state.cpp
	game/world.cpp
	game/snake.cpp
	game/food.cpp
)
target_include_directories(main PRIVATE .)  # Include current directory for headers


target_compile_features(main PRIVATE cxx_std_17)

set_target_properties(main PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}"
)
