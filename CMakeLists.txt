cmake_minimum_required (VERSION 3.25)
set(CMAKE_CXX_STANDARD 20) 
project (DEMO_PROGRAM)
set(CXX_STANDARD_REQUIRED ON)
add_executable(DEMO_PROGRAM
    main.cc
)
target_compile_features(DEMO_PROGRAM PUBLIC cxx_std_20)

add_library(lib_io
    ${CMAKE_CURRENT_SOURCE_DIR}/commandline_interface/input_interface.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/commandline_interface/output_interface.cc
)

add_library(lib_model
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card/card.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card/rank.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card/suit.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/deck.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/hand.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/collision.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/utils/utils.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/demo_program.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/map.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/move.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/position.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/world.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/user/user.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/user/commandline_interface.cc
)

# add_library(lib_collision_handler
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/collision_handler/collision_handler.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/collision_handler/hero_fire_handler.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/collision_handler/hero_water_handler.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/collision_handler/same_type_handler.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/collision_handler/water_fire_handler.cc
# )

# add_library(lib_sprite
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/sprite/sprite.cc
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/sprite/water.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/sprite/fire.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/sprite/hero.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/models/sprite/hp.h
# )

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC lib_io lib_model)
                      #/home/tim/Downloads/gcc-13.1.0/build/lib64/libstdc++.so.6)

target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           /home/tim/Downloads/gcc-13.1.0/build/include
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/models)