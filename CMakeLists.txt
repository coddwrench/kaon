cmake_minimum_required(VERSION 3.12)
project(kaon VERSION 0.1)
include(CTest)

configure_file(src/kaonConfig.h.in kaonConfig.h)
set(KAON_SRC
    src/main.cpp
    src/log.cpp)
add_executable(kaon ${KAON_SRC})
add_executable(test_log tests/log.cpp src/log.cpp)

target_include_directories(kaon
                           PUBLIC ${CMAKE_BINARY_DIR}/)
target_include_directories(test_log
                           PUBLIC src/)
target_link_libraries(test_log gtest)

add_test(NAME TestLog
         COMMAND test_log)
