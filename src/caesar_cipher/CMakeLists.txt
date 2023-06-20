set(TARGET CAESAR_LIB)

add_library(${TARGET} SHARED src/caesar_cipher.cpp)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)


target_link_libraries(${TARGET} STRING_OPS GENERATORS OpenSSL::Crypto)