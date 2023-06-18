set(TARGET STRING_OPS)

add_library(${TARGET} STATIC src/string_ops.cpp)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
