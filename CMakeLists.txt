cmake_minimum_required(VERSION 3.15)
project(snake LANGUAGES CXX)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE) # Requests ncursesw (Wide character support)

# 1. Define where the Vcpkg files are (Manifest Mode location)
set(VCPKG_INSTALLED "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}")

# 2. Find the library inside Vcpkg specifically (Release version)
find_library(CURSES_NCURSES_LIBRARY 
    NAMES ncursesw ncurses libncursesw libncurses
    PATHS "${VCPKG_INSTALLED}/lib"
    NO_DEFAULT_PATH # <--- This is the magic. It ignores /usr/lib
)

# 3. Find the include header inside Vcpkg specifically
find_path(CURSES_INCLUDE_PATH 
    NAMES ncurses.h ncursesw/ncurses.h
    PATHS "${VCPKG_INSTALLED}/include"
    NO_DEFAULT_PATH
)

# 4. Run the standard package finder
# Because we already set the variables above, this command effectively
# just "verifies" them and creates the target for us.
find_package(Curses REQUIRED)

add_subdirectory(src)

# 5. Link using the standard variables or target
if(TARGET Curses::Curses)
    target_link_libraries(main PRIVATE Curses::Curses)
else()
    target_include_directories(main PRIVATE ${CURSES_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${CURSES_LIBRARIES})
endif()