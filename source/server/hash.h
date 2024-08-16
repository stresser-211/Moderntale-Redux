#ifndef HASH_H
#define HASH_H

#include "incl.h"

/* taken from https://github.com/CTrabant/teeny-sha1 */

enum DeeDee {
	a, b, c, d, e, f, k, idx, lidx, widx, didx, temp
};

static int sha1digest(uint8_t *digest, char *hexdigest, const uint8_t *data, size_t databytes) { //d 20 b | h 41 b
#define SHA1ROTATELEFT(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))
	uint32_t W[80];
	uint32_t H[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
	uint32_t A[12];
	A[f] = 0;
	A[k] = 0;
	A[didx] = 0;
	int32_t wcount;
	uint64_t databits = ((uint64_t)databytes) * 8;
	uint32_t loopcount = (databytes + 8) / 64 + 1;
	uint32_t tailbytes = 64 * loopcount - databytes;
	uint8_t datatail[128] = {0};
	{
		if (!digest && !hexdigest) return -1;
		if (!data) return -2;
	}
	datatail[0] = 0x80; {
		datatail[tailbytes - 8] = (uint8_t) (databits >> 56 & 0xFF);
		datatail[tailbytes - 7] = (uint8_t) (databits >> 48 & 0xFF);
		datatail[tailbytes - 6] = (uint8_t) (databits >> 40 & 0xFF);
		datatail[tailbytes - 5] = (uint8_t) (databits >> 32 & 0xFF);
		datatail[tailbytes - 4] = (uint8_t) (databits >> 24 & 0xFF);
		datatail[tailbytes - 3] = (uint8_t) (databits >> 16 & 0xFF);
		datatail[tailbytes - 2] = (uint8_t) (databits >> 8 & 0xFF);
		datatail[tailbytes - 1] = (uint8_t) (databits >> 0 & 0xFF);
	}
	for (A[lidx] = 0; A[lidx] < loopcount; A[lidx]++) {
		memset (W, 0, 80 * sizeof (uint32_t));
		for (A[widx] = 0; A[widx] <= 15; A[widx]++) {
			wcount = 24;
			while (A[didx] < databytes && wcount >= 0) {
				W[A[widx]] += (((uint32_t)data[A[didx]]) << wcount);
				A[didx]++;
				wcount -= 8;
			}
			while (wcount >= 0) {
				W[A[widx]] += (((uint32_t)datatail[A[didx] - databytes]) << wcount);
				A[didx]++;
				wcount -= 8;
			}
		}
		for (A[widx] = 16; A[widx] <= 31; A[widx]++) {
			W[A[widx]] = SHA1ROTATELEFT ((W[A[widx] - 3] ^ W[A[widx] - 8] ^ W[A[widx] - 14] ^ W[A[widx] - 16]), 1);
		}
		for (A[widx] = 32; A[widx] <= 79; A[widx]++) {
			W[A[widx]] = SHA1ROTATELEFT ((W[A[widx] - 6] ^ W[A[widx] - 16] ^ W[A[widx] - 28] ^ W[A[widx] - 32]), 2);
		}
	/* Main loop */
		A[a] = H[0];
		A[b] = H[1];
		A[c] = H[2];
		A[d] = H[3];
		A[e] = H[4];
		for (A[idx] = 0; A[idx] <= 79; A[idx]++) {
			if (A[idx] <= 19) {
				A[f] = (A[b] & A[c]) | ((~A[b]) & A[d]);
				A[k] = 0x5A827999;
			} else if (A[idx] >= 20 && A[idx] <= 39) {
				A[f] = A[b] ^ A[c] ^ A[d];
				A[k] = 0x6ED9EBA1;
			} else if (A[idx] >= 40 && A[idx] <= 59) {
				A[f] = (A[b] & A[c]) | (A[b] & A[d]) | (A[c] & A[d]);
				A[k] = 0x8F1BBCDC;
			} else if (A[idx] >= 60 && A[idx] <= 79) {
				A[f] = A[b] ^ A[c] ^ A[d];
				A[k] = 0xCA62C1D6;
			}
			A[temp] = SHA1ROTATELEFT (A[a], 5) + A[f] + A[e] + A[k] + W[A[idx]];
			A[e] = A[d];
			A[d] = A[c];
			A[c] = SHA1ROTATELEFT (A[b], 30);
			A[b] = A[a];
			A[a] = A[temp];
		}
		H[0] += A[a];
		H[1] += A[b];
		H[2] += A[c];
		H[3] += A[d];
		H[4] += A[e];
	}
	if (digest) {
		for (A[idx] = 0; A[idx] < 5; A[idx]++) {
			digest[A[idx] * 4 + 0] = (uint8_t) (H[A[idx]] >> 24);
			digest[A[idx] * 4 + 1] = (uint8_t) (H[A[idx]] >> 16);
			digest[A[idx] * 4 + 2] = (uint8_t) (H[A[idx]] >> 8);
			digest[A[idx] * 4 + 3] = (uint8_t) (H[A[idx]]);
		}
	}
	if (hexdigest) {
		snprintf(hexdigest, 41, "%08x%08x%08x%08x%08x", H[0], H[1], H[2], H[3], H[4]);
	}
	return 0;
}
char* hash(const char data[88]) {
	char hexdigest[41];
	sha1digest(NULL, hexdigest, (uint8_t*)data, strlen(data));
	return hexdigest;
}

#endif // HASH_H
