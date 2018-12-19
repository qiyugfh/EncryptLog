cmake_minimum_required(VERSION 3.2)

project(EncryptLog)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")

aux_source_directory(. SRCS)
add_executable(EncryptLog ${SRCS})

