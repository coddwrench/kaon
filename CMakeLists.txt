cmake_minimum_required(VERSION 3.12)
project(kaon VERSION 0.1)
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
# K Engine
configure_file(src/kaonConfig.h.in kaonConfig.h)
set(KAON_EXE kaon)
set(KAON_SRC
    src/main.cpp
    src/window/xlib_window.cpp)
add_executable(${KAON_EXE} ${KAON_SRC})
target_include_directories(${KAON_EXE}
                           PUBLIC ${CMAKE_BINARY_DIR}/
                           src/)
target_link_libraries(${KAON_EXE} X11 GL GLU)

# Unit tests
if(${BUILD_UNIT_TESTS})
    # Logging
    set(TEST_LOG_EXE log)
    add_executable(${TEST_LOG_EXE}
                   tests/log.cpp)
    target_include_directories(${TEST_LOG_EXE} PUBLIC src/)
    target_link_libraries(${TEST_LOG_EXE} gtest)
    add_test(NAME LogUnitTest COMMAND ${TEST_LOG_EXE})

    # Vector
    set(TEST_VECTOR_EXE vector)
    add_executable(${TEST_VECTOR_EXE}
                   tests/vector.cpp)
    target_include_directories(${TEST_VECTOR_EXE} PUBLIC src/)
    target_link_libraries(${TEST_VECTOR_EXE} gtest)
    add_test(NAME VectorUnitTest COMMAND ${TEST_VECTOR_EXE})
endif()
