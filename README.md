# Cryptography_Dev 

This repo serves as a learning implementation of various cryptography concepts.


## Build Instructions
First ensure that OpenSSL is correctly installed (exists by default on most UNIX-like systems)
To build and run the existing encryption and decryption methods:
```
$ cmake .. && cmake --build . --target install
$ ./build/executables/caesar_cipher/encrypt_caesar -k <key> -m <message>
$ ./build/executables/caesar_cipher/decrypt_caesar -k <key>
```


## Future Plans
Implemented are:
    - Caesar cipher 

Planned additions:
    -  AES
    -  PGP tools
    -  Twofish (via OpenSSL and possibly from scratch) 
    -  AES from scratch
    -  Passkey generator with true RNG via quantum computer