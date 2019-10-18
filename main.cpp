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

const char* input = "\x54\x68\x69\x73\x20\x69\x73\x20\x61\x20\x74\x65\x73\x74\x20\x54\x68\x69\x73\x20\x69\x73"
	"\x20\x61\x20\x74\x65\x73\x74\x20\x54\x68\x69\x73\x20\x69\x73\x20\x61\x20\x74\x65\x73\x74";

const char* test_hash = "\xfc\xa1\x7d\x44\x37\x70\x9b\x4a\x3b\xd7\x1e\xf3\xed\x21\xb4\x17\xca\x93\xdc\x86\x79\xce\x81\xdf\xd3\xcb\xdd\x0a\x22\xd7\x58\xba";
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

	cn_gpu_hash v3;
	cn_v7l_hash v2 = cn_gpu_hash::make_borrowed(v3);

	v2.software_hash(input, 44, hash);
	if(!cmp_hash(hash, test_hash))
	{
		printf("V7 lite - SOFTWARE HASH FAILED!\n");
		print_hash(hash);
		exit(0);
	}

	if(hw_check_aes())
	{
		v2.hardware_hash(input, 44, hash);
		if(!cmp_hash(hash, test_hash))
		{
			printf("V7 lite - HARDWARE HASH FAILED!\n");
			print_hash(hash);
			exit(0);
		}
	}

	v3.software_hash_3("", 0, hash);
	if(!cmp_hash(hash, zero_hash))
	{
		printf("CN-GPU - SOFTWARE HASH FAILED!\n");
		print_hash(hash);
		exit(0);
	}

	if(hw_check_aes())
	{
		v3.hardware_hash_3("", 0, hash);
		if(!cmp_hash(hash, zero_hash))
		{
			printf("CN-GPU - HARDWARE HASH FAILED!\n");
			print_hash(hash);
			exit(0);
		}
	}

	printf("Verify ok.\n");
	return 0;
}
