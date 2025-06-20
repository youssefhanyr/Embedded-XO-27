cmake_minimum_required(VERSION 3.14)
project(xo_project_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GoogleTest as a subdirectory (assuming it's in external/googletest)
add_subdirectory(external/googletest)

# Define a library for all AI components
# This collects all your AI-related .cpp files
add_library(ai_logic
    src/minimax.cpp
    src/easy_move.cpp
    src/medium_move.cpp
    src/hard_move.cpp
)

# Ensure the AI logic library and any executables using it can find headers in src/
target_include_directories(ai_logic PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Test executable for AI opponent (test_ai)
# add_executable(test_ai tests/test_ai.cpp)
# target_link_libraries(test_ai ai_logic gtest_main) # Link to your new ai_logic library and gtest
# target_include_directories(test_ai PRIVATE ${CMAKE_SOURCE_DIR}/src) # Ensure test_ai.cpp can find headers

# Test executable for Move Validation (test_move_validation)
add_executable(test_move_validation tests/test_move_validation.cpp)
target_link_libraries(test_move_validation ai_logic gtest_main) # Link to your new ai_logic library and gtest
target_include_directories(test_move_validation PRIVATE ${CMAKE_SOURCE_DIR}/src) # Ensure test_move_validation.cpp can find headers

# Test executable for Win Detection
add_executable(test_win_detection tests/test_win_detection.cpp)
target_link_libraries(test_win_detection ai_logic gtest_main) # Link to ai_logic library
target_include_directories(test_win_detection PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Test executable for Game State/Turns
add_executable(test_game_state tests/test_game_state.cpp)
target_link_libraries(test_game_state ai_logic gtest_main) # Link to ai_logic library
target_include_directories(test_game_state PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Enable test discovery for ctest
enable_testing()
add_test(NAME test_ai COMMAND test_ai)
add_test(NAME test_move_validation COMMAND test_move_validation)
add_test(NAME test_win_detection COMMAND test_win_detection) 
add_test(NAME test_game_state COMMAND test_game_state)