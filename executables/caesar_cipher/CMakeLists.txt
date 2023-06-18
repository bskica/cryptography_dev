set(TARGET CAESAR_TEST)
add_executable(${TARGET} caesar_encrypt.cpp)
add_executable(${TARGET} caesar_decrypt.cpp)


target_link_libraries(${TARGET} PUBLIC CAESAR_LIB)
