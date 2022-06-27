cmake_minimum_required(VERSION 3.12)
project(kaon VERSION 0.1)
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
# K Engine
configure_file(src/kaonConfig.h.in kaonConfig.h)
set(KAON_EXE kaon)
set(KAON_SRC
    src/main.cpp
    src/log.cpp
    src/window/xlib_window.cpp)
add_executable(${KAON_EXE} ${KAON_SRC})
target_include_directories(${KAON_EXE}
                           PUBLIC ${CMAKE_BINARY_DIR}/
                           src/)
target_link_libraries(${KAON_EXE} X11 GL GLU)

# Tests
if(${BUILD_TESTING})
    set(TEST_LOG_EXE test_log)
    add_executable(${TEST_LOG_EXE} tests/log.cpp src/log.cpp)
    target_include_directories(${TEST_LOG_EXE} PUBLIC src/)
    target_link_libraries(${TEST_LOG_EXE} gtest)
    add_test(NAME TestLog COMMAND ${TEST_LOG_EXE})
endif()
