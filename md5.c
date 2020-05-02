
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
Name :Vyacheslav Lukyanov
id : G00339839
Program Description : MD5 message-digest algorithm


adopted from https://en.wikipedia.org/wiki/MD5

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"

// ROTATE_LEFT rotates x left n bits
#define ROTATE_LEFT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
uint32_t h0, h1, h2, h3;

void md5(uint8_t *msg, size_t len);

int main(int argc, char *argv[])
{
	say();

	printf("Please enter a file name:\n");

	scanf("%s", argv[0]);
	//open file
	FILE *infile = fopen(argv[0], "r");
	//exit the app if file is null
	if (infile == NULL)
	{
		printf("Error: couldn't open file %s.\n", argv[0]);
		return 1;
	}

	char *text;
	//scan to the end of file
	fseek(infile, 0, SEEK_END);
	//give back the file length
	int file_len = ftell(infile);

	//allocate memory required
	text = (char *)malloc(file_len);

	//bring pointer back to the beginning
	rewind(infile);

	//if file has something
	if (file_len > 0)
	{
		//read file at once
		int count = fread(text, sizeof(char), file_len, infile);

		//close file
		if (infile != NULL)
		{
			fclose(infile);
		}
	}
	else
	{
		text = "";
	}

	md5(text, file_len);

	free(text);

	//var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
	uint8_t *p;

	// display result

	p = (uint8_t *)&h0;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);

	p = (uint8_t *)&h1;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);

	p = (uint8_t *)&h2;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);

	p = (uint8_t *)&h3;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);

	return 0;
}

void md5(uint8_t *init_msg, size_t len)
{

	// r specifies the per-round shift amounts
	uint32_t r[] = {
		7, 12, 17, 22,
		7, 12, 17, 22,
		7, 12, 17, 22,
		7, 12, 17, 22,

		5, 9, 14, 20,
		5, 9, 14, 20,
		5, 9, 14, 20,
		5, 9, 14, 20,

		4, 11, 16, 23,
		4, 11, 16, 23,
		4, 11, 16, 23,
		4, 11, 16, 23,

		6, 10, 15, 21,
		6, 10, 15, 21,
		6, 10, 15, 21,
		6, 10, 15, 21};

	// Initial hash values
	h0 = 0x67452301;
	h1 = 0xefcdab89;
	h2 = 0x98badcfe;
	h3 = 0x10325476;

	// Message to prepare
	uint8_t *msg = NULL;

	// Use binary integer part of the sines of integers (in radians) as constants
	// Initialize variables:
	uint32_t k[] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	// Pre-processing: adding a single 1 bit
	//append "1" bit to message

	// Pre-processing: padding with zeros
	//append "0" bit until message length in bit ≡ 448 (mod 512)
	//append length mod (2 pow 64) to message

	int new_len = ((((len + 8) / 64) + 1) * 64) - 8;
	// also appends "0" bits
	//we alloc also 64 extra bytes
	msg = calloc(new_len + 64, 1);
	//copy original msg into msg with zeros
	memcpy(msg, init_msg, len);
	// append the "1" bit; most significant bit is "first"
	msg[len] = 0x80;
	// len in bits
	uint32_t bits_len = 8 * len;

	memcpy(msg + new_len, &bits_len, 4);

	// Process the message in successive 512-bit chunks:
	//for each 512-bit chunk of message
	int offset;
	for (offset = 0; offset < new_len; offset += (512 / 8))
	{
		// break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
		uint32_t *w = (uint32_t *)(msg + offset);

		// Initialize hash value for this chunk
		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;

		//Main loop
		uint32_t i;
		//operations on basic MD5 functions.
		for (i = 0; i < 64; i++)
		{
			uint32_t f, g;

			if (i < 16)
			{
				f = (b & c) | ((~b) & d);
				g = i;
			}
			else if (i < 32)
			{
				f = (d & b) | ((~d) & c);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = c ^ (b | (~d));
				g = (7 * i) % 16;
			}

			uint32_t temp = d;
			d = c;
			c = b;
			b = b + ROTATE_LEFT((a + f + k[i] + w[g]), r[i]);
			a = temp;
		}

		// Add this chunk's hash to result so far:

		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
	}

	//cleanup
	free(msg);
}