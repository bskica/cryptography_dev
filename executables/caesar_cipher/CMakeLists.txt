set(TARGET_ENCRYPT encrypt_caesar)
set(TARGET_DECRYPT decrypt_caesar)

add_executable(${TARGET_ENCRYPT} caesar_encrypt.cpp)
add_executable(${TARGET_DECRYPT} caesar_decrypt.cpp)

target_link_libraries(${TARGET_ENCRYPT} PUBLIC CAESAR_LIB)
target_link_libraries(${TARGET_DECRYPT} PUBLIC CAESAR_LIB)


install(TARGETS ${TARGET_ENCRYPT} ${TARGET_DECRYPT}
        RUNTIME DESTINATION release)