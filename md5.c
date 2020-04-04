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

// Initial hash values
uint32_t h0 = 0x67452301;
uint32_t h1 = 0xefcdab89;
uint32_t h2 = 0x98badcfe;
uint32_t h3 = 0x10325476;

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

int main(int argc, char *argv[])
{
	//declare variables
	int choice, input;
	char *msg, *str;
	char *file;
	size_t MAX_SIZE = 512;
	FILE *infile;

	//allocate memory for file name
	file = (char *)malloc(64);
	//allocate memory for string
	str = (char *)malloc(MAX_SIZE);
	//allocate memory for string
	msg = (char *)malloc(MAX_SIZE * 2);
	//	msg = (char *)malloc(2 ^ 64);
	//prompt user for input
	printf("Please enter 1 to Input some free text\n");
	printf("Please enter 2 to Input a full path to some file\n");
	printf("Please enter 3 to Exit the application\n");

	input = scanf("%d", &choice);

	//check user input if not digit terminate the programme
	if (input == 0)
	{

		exit(0);
	}

	while (choice != 3)
	{

		switch (choice)
		{

		case 1:
			//get input from user
			printf("Enter some text : ");

			scanf(" %[^\n]s", str);

			printf("%s\n", str);

			//free allocated memory from leak
			free(str);

			break;

		case 2:

			printf("Enter a file name : ");
			scanf(" %s", file);

			infile = fopen(file, "r");
			if (!infile)
			{
				printf("Error: couldn't open file %s.\n\n", file);
			}
			else
			{
				fscanf(infile, "%s", msg);

				printf("%s\n", msg);
			}
			//close file
			if (infile != NULL)
			{

				fclose(infile);
			}

			//free allocated memory from leak
			free(msg);
			free(file);

			break;

		case 3:
			exit(0);

		default:

			printf("Invalid input\n");
		}
		//prompt user for input
		printf("Please enter 1 to Input some free text\n");
		printf("Please enter 2 to Input a full path to some file\n");
		printf("Please enter 3 to Exit the application\n");

		input = scanf("%d", &choice);

		//check user input if not digit terminate the programme
		if (input == 0)
		{

			exit(0);
		}
	}
}
