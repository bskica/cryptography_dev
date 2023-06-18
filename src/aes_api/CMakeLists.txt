set(TARGET AES_API_LIB)

add_library(${TARGET} SHARED src/aes_api.cpp)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
