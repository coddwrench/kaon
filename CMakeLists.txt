cmake_minimum_required(VERSION 3.10)
project(kaon VERSION 0.1)
configure_file(src/kaonConfig.h.in kaonConfig.h)
set(KAON_SRC
    src/main.cpp
    src/log.cpp)
add_executable(kaon ${KAON_SRC})
target_include_directories(kaon
                           PUBLIC ${CMAKE_BINARY_DIR}/)
