
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
Name :Vyacheslav Lukyanov
id : G00339839
Program Description : MD5 message-digest algorithm
version 1.0.0

adopted from https://en.wikipedia.org/wiki/MD5

*/

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "getopt.h"
#include "help.h"

// ROTATE_LEFT rotates x left n bits
#define ROTATE_LEFT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
uint32_t h0, h1, h2, h3;

void md5(uint8_t *msg, size_t len);

void test_hashes_md5();

int main(int argc, char *argv[])
{
	//variables declaration
	int opt;
	int hflag = 0;
	int tflag = 0;
	int dflag = 0;
	int vflag = 0;
	char *fvalue = NULL;
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "htdvf:")) != -1)

		switch (c)
		{
		case 'h':

			hflag = 1;

			break;

		case 't':

			tflag = 1;

			break;
		case 'd':

			dflag = 1;

			break;

		case 'v':

			vflag = 1;

			break;

		case 'f':

			fvalue = optarg;
			break;
		case '?':
			if (optopt == 'f')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option '-%c'.\n", optopt);
			else
				fprintf(stderr,
						"Unknown option character '\\x%x'.\n",
						optopt);
			return 1;
		default:
			abort();
		}

	for (int i = optind; i < argc; i++)
	{

		printf("\nNon-option argument %s\n", argv[i]);
		exit(0);
	}

	if (hflag == 1)
	{
		help();
	}
	if (tflag == 1)
	{
		test_hashes_md5();
	}
	if (dflag == 1)
	{

		cwd();
	}
	if (vflag == 1)
	{
		version();
	}

	//open file
	FILE *infile = fopen(fvalue, "r");
	//exit the app if file is null
	if (infile == NULL)
	{
		printf("Error: couldn't open file %s.\n", fvalue);
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

		fclose(infile);
	}
	else
	{
		text = "";
	}

	md5(text, file_len);

	// free memory from leak
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

	//Initialize new length ,length in bits plus 1
	int new_len = len * 8 + 1;

	// if length of message more than in bits ≡ 448 (mod 512) allocate another block to accommodate "0" padding
	for (; new_len % 512 != 448; new_len++)
		;
	// length in bytes
	new_len /= 8;

	// allocate memory filled with zeros in bytes
	msg = calloc(new_len, sizeof(int));

	//copy original msg into msg with zeros
	memcpy(msg, init_msg, len);

	// append the "1" bit; most significant bit is "first"
	msg[len] = 0x80;

	// length in bits
	uint32_t bits_len = len * 8;

	// set the last 64 bits to the number of bits in the file (should be little-endian)
	memcpy(msg + new_len, &bits_len, sizeof(bits_len));

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

void test_hashes_md5()
{
	// test cases copied from appendix A.5 of RFC 1321
	char *tests[7];
	tests[0] = "";
	tests[1] = "a";
	tests[2] = "abc";
	tests[3] = "message digest";
	tests[4] = "abcdefghijklmnopqrstuvwxyz";
	tests[5] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	tests[6] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";

	// test cases copied from appendix A.5 of RFC 1321
	char *results[7];
	results[0] = "d41d8cd98f00b204e9800998ecf8427e";
	results[1] = "0cc175b9c0f1b6a831c399e269772661";
	results[2] = "900150983cd24fb0d6963f7d28e17f72";
	results[3] = "f96b697d7cb7938d525a2f31aaf161d0";
	results[4] = "c3fcd3d76192e4007dfb496cca67e13b";
	results[5] = "d174ab98d277d9f5a5611c2c9f419d9f";
	results[6] = "57edf4a22be3c955ac49da2e2107b67a";

	for (int i = 0; i < 7; i++)
	{

		char str[256];

		md5(tests[i], strlen(tests[i]));

		uint8_t *p = (uint8_t *)&h0;
		uint8_t *p1 = (uint8_t *)&h1;
		uint8_t *p2 = (uint8_t *)&h2;
		uint8_t *p3 = (uint8_t *)&h3;

		// format hashed string
		sprintf(str, "%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], p1[0], p1[1], p1[2], p1[3], p2[0], p2[1], p2[2], p2[3], p3[0], p3[1], p3[2], p3[3]);

		// compare results
		assert(strcmp(str, results[i]) == 0);
		// print results if passed
		printf("Hashed of %s --> %s\n", tests[i], str);
	}

	exit(0);
}