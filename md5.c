#include<stdio.h>
#include<stdint.h>

// Section 4.1.2
 uint32_t  Ch(uint32_t x,uint32_t y, uint32_t z){

	return (x & y)^(~x & z);
 }
// Section 4.1.2
 uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){

	return (x & y)^(x & z)^(y & z);
 }

// Section 3.2
 uint32_t SHR(uint32_t x, int n){


	 return x >> n;
 }

// Section 3.2
 uint32_t ROTR(uint32_t x, int n){

	 return (x >> n) | (x << (32-n));
 }

 int main(int argc, char * argv[]){


	uint32_t x = 0x0f0f0f0f;
	uint32_t y = 0xcccccccc;
	uint32_t z = 0x55555555;

	printf("x         = %08x\n",x);
	printf("y         = %08x\n",y);
	printf("z         = %08x\n",z);


	printf("Ch(x,y,z) = %08x\n",Ch(x,y,z));
	printf("Maj(x,y,z)= %08x\n",Maj(x,y,z));
	printf("SHR(x,4)  = %08x\n",SHR(x,4));
	printf("ROTR(x,4) = %08x\n",ROTR(x,4));

	return 0;
}
