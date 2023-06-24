cmake_minimum_required (VERSION 3.25)
set(CMAKE_CXX_STANDARD 20) 
project (DEMO_PROGRAM)
set(CXX_STANDARD_REQUIRED ON)
add_executable(DEMO_PROGRAM
    main.cc
)
target_compile_features(DEMO_PROGRAM PUBLIC cxx_std_20)

add_library(lib_play_strategy
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/play_strategy/null_strategy.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/play_strategy/smallest_first_single.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/play_strategy/smallest_first_pair.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/play_strategy/smallest_first_full_house.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/play_strategy/strategy_utility.cc
)

add_library(lib_player
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/human_player.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/ai_player.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player/play_strategy/play_strategy.cc
)

add_library(lib_io
    ${CMAKE_CURRENT_SOURCE_DIR}/io_interface/input_interface_terminal.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/io_interface/input_interface_file.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/io_interface/input_interface.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/io_interface/output_interface.cc
)

add_library(lib_model
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card/card.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card/rank.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card/suit.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/deck.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/hand.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/player.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/big2.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/turn_move.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern/card_pattern.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern_parser/card_pattern_parser.cc
)

add_library(lib_parser
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern_parser/null_parser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern_parser/single_parser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern_parser/pair_parser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern_parser/straight_parser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern_parser/full_house_parser.cc
)

add_library(lib_pattern
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern/null_pattern.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern/single.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern/pair.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern/straight.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/models/card_pattern/full_house.cc
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC lib_io lib_model lib_parser lib_pattern lib_player lib_play_strategy)

target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/models)