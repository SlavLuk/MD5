#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Macros functions
//Section 3.4 Step 4 process message in 16- word blocks
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// ROTATE_LEFT rotates x left n bits
#define ROTATE_LEFT(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// These vars will contain the hash
uint32_t h0, h1, h2, h3;

// r specifies the per-round shift amounts
uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
				4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
				6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

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

void md5(uint8_t *msg, size_t len);

int main(int argc, char *argv[])
{
	printf("Enter a file name:\n");

	scanf("%s", argv[0]);
	//open file
	FILE *infile = fopen(argv[0], "r");
	//exit the app if file is null
	if (infile == NULL)
	{
		printf("Error: couldn't open file %s.\n", argv[0]);
		return 1;
	}

	char *msg = NULL;
	size_t size = 0;

	//iterate until end of file
	while (!feof(infile))
	{
		//read file by line
		getline(&msg, &size, infile);
		printf("%s\n", msg);
	}

	size_t len = strlen(msg);

	printf("Str len %d\n", len);

	free(msg);

	//close file
	if (infile != NULL)
	{
		fclose(infile);
	}
}

void md5(uint8_t *init_msg, size_t len)
{
	// Initial hash values
	h0 = 0x67452301;
	h1 = 0xefcdab89;
	h2 = 0x98badcfe;
	h3 = 0x10325476;

	// Message (to prepare)
	uint8_t *msg = NULL;
	// Pre-processing: adding a single 1 bit
	//append "1" bit to message

	// Pre-processing: padding with zeros
	//append "0" bit until message length in bit ≡ 448 (mod 512)
	//append length mod (2 pow 64) to message
	int new_len;
	for (new_len = len * 8 + 1; new_len % 512 != 448; new_len++)
		;
	new_len /= 8;
}