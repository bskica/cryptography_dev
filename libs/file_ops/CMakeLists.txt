set(TARGET FILE_OPS)

add_library(${TARGET} STATIC src/file_ops.cpp)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
