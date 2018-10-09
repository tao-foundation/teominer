/*
  (C)TAO.Foundation for TETHASHV1 modification. GPL V3 License term.
  https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash

  FNV_hash0 is depricated
  use FNV1 hash

use hash offset
FNV-1a hash
The FNV-1a hash differs from the FNV-1 hash by only the order in which the multiply and XOR is performed:[8][10]

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

#define __TETHASHV1__
#undef  __ETHASH__

#define FNV_PRIME	0x01000193
#define FNV_OFFSET_BASIS  0x811c9dc5

#ifdef __ETHASH__
#define fnv(x, y)        ((x) * FNV_PRIME ^ (y))
#else  // default __TETHASHV1__
#define fnv(x, y)         ( ( ((FNV_OFFSET_BASIS) ^ (x)) * (FNV_PRIME) ^ (y) ) * FNV_PRIME)
#endif

__device__ uint4 fnv4(uint4 a, uint4 b)
{
	uint4 c;
#ifdef ETHASH
	c.x = a.x * FNV_PRIME ^ b.x;
	c.y = a.y * FNV_PRIME ^ b.y;
	c.z = a.z * FNV_PRIME ^ b.z;
	c.w = a.w * FNV_PRIME ^ b.w;
#else // TETHASHV1
	c.x = ( ((((FNV_OFFSET_BASIS)^(a.x))*FNV_PRIME) ^ (b.x)) * FNV_PRIME );
	c.y = ( ((((FNV_OFFSET_BASIS)^(a.y))*FNV_PRIME) ^ (b.y)) * FNV_PRIME );
	c.z = ( ((((FNV_OFFSET_BASIS)^(a.z))*FNV_PRIME) ^ (b.z)) * FNV_PRIME );
	c.w = ( ((((FNV_OFFSET_BASIS)^(a.w))*FNV_PRIME) ^ (b.w)) * FNV_PRIME );
#endif

	return c;
}

__device__ uint32_t fnv_reduce(uint4 v)
{
	return fnv(fnv(fnv(v.x, v.y), v.z), v.w);
}

