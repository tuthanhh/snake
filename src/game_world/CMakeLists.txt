add_library(game_world STATIC
    world.cpp
    snake.cpp
    food.cpp
)

target_include_directories(game_world PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
