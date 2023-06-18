set(TARGET GENERATORS)

add_library(${TARGET} STATIC src/generators.cpp)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
