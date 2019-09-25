// Copyright (c) 2019, Ryo Currency Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2014-2017, SUMOKOIN
// Parts of this file are originally copyright (c) 2014-2017, The Monero Project
// Parts of this file are originally copyright (c) 2012-2013, The Cryptonote developers

#include <iostream>
#include <string.h>
#include "pow_hash/cn_slow_hash.hpp"

#include "hashes.h"

const char* zero_hash = "\x55\x5e\x0a\xee\x78\x79\x31\x6d\x7d\xef\xf7\x72\x97\x3c\xb9\x11\x8e\x38\x95\x70\x9d\xb2\x54\x7a\xc0\x72\xd5\xb9\x13\x10\x01\xd8";

inline bool cmp_hash(const uint8_t* calc, const char* exp)
{
	return memcmp(calc, exp, 32) == 0;
}

inline void print_hash(const void* hash)
{
	uint8_t* h = (uint8_t*)hash;
	printf("\t\"");
	for(size_t i=0; i < 32; i++)
		printf("\\x%.2x", h[i]);
	printf("\",\n");
}

int main(int argc, char **argv) 
{
	uint8_t hash[32];
	
	cn_pow_hash_v3 v3;

	v3.hash("", 0, hash);
	if(!cmp_hash(hash, zero_hash))
	{
		printf("HASH FAILED!\n");
		print_hash(hash);
	}

	for(uint32_t i=0; i < 1000; i++)
	{
		v3.hash(&i, sizeof(i), hash);
		if(!cmp_hash(hash, good_hashes[i]))
		{
			printf("HASH FAILED (%u)!\n", i);
			print_hash(hash);
		}
	}

	printf("Verify ok.\n");
	return 0;
}
