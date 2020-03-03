#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Macros functions
//Section 3.4 Step 4 process message in 16- word blocks
 #define F(x,y,z)(((x) & (y)) | ((~x) & (z)))
 #define G(x,y,z)(((x) & (z)) | ((y) & (~z)))
 #define H(x,y,z,)((x) ^ (y) ^ (z))
 #define I(x,y,z)((y) ^ ((x) | (~z)))

// ROTATE_LEFT rotates x left n bits
#define ROTATE_LEFT(x,n)(((x) << (n)) | ((x) >> (32-(n))))



	int main(int argc,char *argv[]){
	
	
	printf("Hello Worlds");
	
	
	
	
	
	}
