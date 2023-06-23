# Cryptography_Dev 

This repo contains various cryptographic CLI utilities.


## Build Instructions
First ensure that OpenSSL is correctly installed (exists by default on most UNIX-like systems)
To build and run the existing encryption and decryption methods:
```
$ mkdir build && cd build
$ cmake .. && cmake --build . --target install
$ ./install/release/encrypt_caesar -k <key> -m <message>
$ ./install/release/decrypt_caesar -k <key>
```


## Future Plans
Implemented are:
*  Caesar cipher 

Planned additions:
*  AES
*  PGP tools
*  Twofish (via OpenSSL and possibly from scratch) 
*  AES from scratch
*  Passkey generator with true RNG via quantum computer
