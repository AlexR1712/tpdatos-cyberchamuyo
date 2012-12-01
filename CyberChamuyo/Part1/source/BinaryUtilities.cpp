/*
 * BinaryUtilities.cpp
 *
 *  Created on: 17/11/2012
 *      Author: sebastian
 */

#include <vector>
#include <math.h>
#include "../include/BinaryUtilities.h"

#ifndef __BINARY_UTILITIES__
#define __BINARY_UTILITIES__

#define MSB 0x80
#define FFFFFFFF 0xffffffff
#define FF1 0xff000000
#define FF2 0x00ff0000
#define FF3 0x0000ff00
#define FF4 0x000000ff

namespace BinaryUtilities {

std::vector<unsigned char> encodeGamma(long l) {
	int n = log2(l);
	std::vector<unsigned char> encoded;
	int byte_size = n/8;
	if((n % 8) > 0)
		++byte_size;
	for(int i = 0; i < byte_size; ++i) {
		encoded.push_back(0);
	}
	for(int i = 0; i < n; ++i) {
		char msb = MSB;
		msb = msb >> n;
		int pos = n / 8;
		encoded[pos] = encoded[pos] | msb;
	}
	int b = exp2(n);
	unsigned int res = l - b;
	unsigned int dif = FFFFFFFF - res;
	unsigned int bit_size = log2(dif);
	res = res << bit_size;
	unsigned int byte_cant = bit_size / 8;
	if(bit_size % 8)
		byte_cant++;
	for(unsigned int i = 0; i < byte_cant; ++i) {
		encoded[n + i] = encoded[n + i] + (FF1 >> (8 * (i/4)));
	}
	return encoded;
}

}

#endif
