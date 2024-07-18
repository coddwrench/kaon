cmake_minimum_required(VERSION 3.12)
project(kaon VERSION 0.1)
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(nlohmann_json CONFIG REQUIRED)

if (MSVC)
    add_compile_options(/std:c++17)
endif()


# K Engine
configure_file(src/kaonConfig.h.in kaonConfig.h)
set(KAON_EXE kaon)
set(KAON_SRC
    src/main.cpp
    src/engine/engine.cpp
    src/scene/scene.cpp
    src/scene/scene.cpp
    src/scene/loader/model/bin.cpp
    src/scene/loader/model/obj.cpp
)

if (MSVC)
    list(APPEND KAON_SRC 
    src/window/win_window.cpp
    src/render/directx_render.cpp
)
else()
    list(APPEND KAON_SRC 
    src/window/xlib_window.cpp
    src/render/ogl_render.cpp
)
endif()

add_executable(${KAON_EXE} ${KAON_SRC})
target_include_directories(${KAON_EXE}
                           PUBLIC ${CMAKE_BINARY_DIR}/
                           src/)

if (MSVC)
    target_link_libraries(${KAON_EXE} PRIVATE nlohmann_json::nlohmann_json)
else()
    target_link_libraries(${KAON_EXE} X11 GL GLU GLEW)
endif()

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
