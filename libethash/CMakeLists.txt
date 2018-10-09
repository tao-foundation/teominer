# Copyright 2018 trustfarm , TAO.Foundation
# Licensed under the Apache License, Version 2.0. See the LICENSE file.
# fork from https://github.com/chfast/ethash and combined on main source tree.

set(include_dir ${PROJECT_SOURCE_DIR}/libethash/include)

set(SOURCES 
    bit_manipulation.h
    builtins.h
    endianness.hpp
    ${include_dir}/ethash/ethash.h
    ${include_dir}/ethash/ethash.hpp
    ethash-internal.hpp
    ethash.cpp
    ${include_dir}/ethash/hash_types.h
    managed.cpp
    ${include_dir}/ethash/keccak.h
    ${include_dir}/ethash/keccak.hpp
    keccak.c
    keccakf800.c
    keccakf1600.c
    kiss99.c
    kiss99.h
    primes.h
    primes.c
    progpow-internal.hpp
    progpow.cpp
)



include_directories(BEFORE ${include_dir})
include_directories(BEFORE .)

add_library(ethash ${SOURCES})
target_link_libraries(ethash PUBLIC devcore)
# target_link_libraries(apicore PRIVATE ethcore devcore ethminer-buildinfo mongoose::mongoose Boost::filesystem)

