#ifndef _STRIBOG_H
#define _STRIBOG_H

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "types.h"

#define BLOCK_SIZE      64
#define BLOCK_BIT_SIZE  (BLOCK_SIZE * 8)

#define HASH256         0
#define HASH512         1


struct stribog {
    u8 h[BLOCK_SIZE];
	u8 N[BLOCK_SIZE];
	u8 S[BLOCK_SIZE];
};

extern void init(struct stribog *ctx, u8 size_);
extern void stribog(struct stribog *ctx, u8 *message, u64 len);
extern void print_hash(struct stribog *ctx, std::ostream &output_stream);

#endif
