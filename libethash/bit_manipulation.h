/* ethash: C/C++ implementation of Ethash, the Ethereum Proof of Work algorithm.
 * Copyright 2018 Pawel Bylica.
 * Licensed under the Apache License, Version 2.0. See the LICENSE file.
 */

/*
  (C)TAO.Foundation for TETHASHV1 modification. GPL V3 License term.
  https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash

  FNV_hash0 is depricated
  use FNV1 hash

use hash offset
FNV-1a hash
The FNV-1a hash differs from the FNV-1 hash by only the order in which the multiply and XOR is
performed:[8][10]

   hash = FNV_offset_basis
   for each byte_of_data to be hashed
    hash = hash XOR byte_of_data
    hash = hash × FNV_prime
   return hash

Size in bits
{\displaystyle n=2^{s}} {\displaystyle n=2^{s}}

FNV prime	FNV offset basis
32	224 + 28 + 0x93 = 16777619

2166136261 = 0x811c9dc5
*/

#pragma once

#include "builtins.h"

#include <stdint.h>

#if __clang__
#define ATTRIBUTE_NO_SANITIZE_UNSIGNED_INTEGER_OVERFLOW \
    __attribute__((no_sanitize("unsigned-integer-overflow")))
#else
#define ATTRIBUTE_NO_SANITIZE_UNSIGNED_INTEGER_OVERFLOW
#endif

#define __TETHASHV1__
#undef __ETHASH__

#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t rotl32(uint32_t n, unsigned int c)
{
    const unsigned int mask = 31;

    c &= mask;
    unsigned int neg_c = (unsigned int)(-(int)c);
    return (n << c) | (n >> (neg_c & mask));
}

static inline uint32_t rotr32(uint32_t n, unsigned int c)
{
    const unsigned int mask = 31;

    c &= mask;
    unsigned int neg_c = (unsigned int)(-(int)c);
    return (n >> c) | (n << (neg_c & mask));
}

static inline uint32_t clz32(uint32_t x)
{
    return x ? (uint32_t)__builtin_clz(x) : 32;
}

static inline uint32_t popcount32(uint32_t x)
{
    return (uint32_t)__builtin_popcount(x);
}

static inline uint32_t mul_hi32(uint32_t x, uint32_t y)
{
    return (uint32_t)(((uint64_t)x * (uint64_t)y) >> 32);
}


#define FNV_PRIME 0x01000193
#define FNV_OFFSET_BASIS 0x811c9dc5

#ifdef __ETHASH__
#define fnv(x, y) ((x)*FNV_PRIME ^ (y))
#define fnv_reduce(v) fnv(fnv(fnv(v.x, v.y), v.z), v.w)
#else  // default __TETHASHV1__
#define fnv(x, y) ((((FNV_OFFSET_BASIS ^ (x)) * FNV_PRIME) ^ (y)) * FNV_PRIME)
#define fnv_reduce(v) fnv(fnv(fnv(v.x, v.y), v.z), v.w)
#endif

/**
 * The implementation of FNV-1 hash.
 *
 * See https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash.
 */
ATTRIBUTE_NO_SANITIZE_UNSIGNED_INTEGER_OVERFLOW
static inline uint32_t fnv1(uint32_t u, uint32_t v) noexcept
{
#ifdef __ETHASH__
    return (u * FNV_PRIME) ^ v;
#else  // __TETHASHV1__
    return ((((FNV_OFFSET_BASIS ^ u) * FNV_PRIME) ^ v) * FNV_PRIME);
#endif
}

/**
 * The implementation of FNV-1a hash.
 *
 * See https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash.
 */
ATTRIBUTE_NO_SANITIZE_UNSIGNED_INTEGER_OVERFLOW
static inline uint32_t fnv1a(uint32_t u, uint32_t v) noexcept
{
    return (u ^ v) * FNV_PRIME;
}

#ifdef __cplusplus
}
#endif
