cmake_minimum_required( VERSION 3.0 )

project( "Tank" )

set(SRCS
    "${CMAKE_SOURCE_DIR}/main.c++"
    "${CMAKE_SOURCE_DIR}/src/xwing.c++"
    "${CMAKE_SOURCE_DIR}/src/obstacle.c++"
    "${CMAKE_SOURCE_DIR}/src/explosion.c++"
    "${CMAKE_SOURCE_DIR}/src/loader.c++"
    "${CMAKE_SOURCE_DIR}/src/game.c++"
    "${CMAKE_SOURCE_DIR}/src/main_menu.c++"
    "${CMAKE_SOURCE_DIR}/src/button.c++"
    "${CMAKE_SOURCE_DIR}/src/bg.c++"
)

add_executable(tank ${SRCS})

set_target_properties(tank PROPERTIES COMPILE_FLAGS "-Wno-psabi")

target_link_libraries(tank sfml-system sfml-window sfml-graphics sfml-audio)