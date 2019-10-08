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

#include <chrono>
#include <iostream>
#include <string.h>
#include "pow_hash/cn_slow_hash.hpp"

const char* zero_hash = "\xe5\xf5\xbe\xab\xad\x63\x7c\x1b\x34\x65\x47\xb2\x4b\x27\x4d\x83\xc6\xf8\xa9\x63\x9c\xb2\x31\xd7\xbd\xe8\x51\x1f\xc2\x84\x23\xe9";

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
	
	cn_pow_hash_v4 v4;

	v4.software_hash("", 0, hash);
	if(!cmp_hash(hash, zero_hash))
	{
		printf("HASH FAILED!\n");
		print_hash(hash);
		return 0;
	}

	v4.hardware_hash("", 0, hash);
	if(!cmp_hash(hash, zero_hash))
	{
		printf("HASH FAILED!\n");
		print_hash(hash);
		return 0;
	}

	v4.hash("", 0, hash);
	if(!cmp_hash(hash, zero_hash))
	{
		printf("HASH FAILED!\n");
		print_hash(hash);
		return 0;
	}
	printf("HASH OK!\n");

	auto start = std::chrono::steady_clock::now();
	for(size_t i=0; i < 1000; i++)
	{
		v4.hash(&i, sizeof(i), hash);
	}
	auto delta_time = std::chrono::steady_clock::now() - start;
	std::cout << "Speed: " << 1000.0 / std::chrono::duration<double>(delta_time).count() << " H/s" << std::endl;

	return 0;
}
