// Copyright (c) 2018, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// Ryo changes to this code are in public domain. Please note, other licences may apply to the file.
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
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#pragma once

#if !defined(__cplusplus)

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#pragma pack(push, 1)
union hash_state {
	uint8_t b[200];
	uint64_t w[25];
};
#pragma pack(pop)
static_assert(sizeof(union hash_state) == 200, "Invalid structure size");

void hash_process(union hash_state *state, const uint8_t *buf, size_t count);

#endif

enum
{
	HASH_SIZE = 32,
	HASH_DATA_AREA = 136
};

void cn_fast_hash(const void *data, size_t length, char *hash);
void tree_hash(const char (*hashes)[HASH_SIZE], size_t count, char *root_hash);
