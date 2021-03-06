#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "chacha-ppc.h"

#define BLOCK 16

struct chacha_t {

} chacha_t;

char buffer[256];

void hexprint(char *title, uint8_t *value, uint16_t size) {
	printf("%s\n-----------------------------------------------------", title);
	int n;
	for (n = 0; n < size; n++) {
		if (n % 16 == 0) printf("\n%3d ", n);
		printf(" %02x", (uint8_t) *(value+n));
	}
	printf("\n\n");
}

void hexprint32(char *title, uint32_t *value, uint16_t size) {
	printf("%s\n-----------------------------------------------------", title);
	int n;
	for (n = 0; n < size; n++) {
		if (n % 4 == 0) printf("\n%3d ", n);
		printf("  %08x", (uint32_t) *(value+n));
	}
	printf("\n\n");
}

char *array2str(char *array, int size) {
	int i;
	char *buffer_ptr = buffer;

	for (i = 0; i < size; i++)
	{
		if (i != 0 && i % 4 == 0) {
			if (i % 16 == 0) sprintf(buffer_ptr, "\n");
			else sprintf(buffer_ptr, " ");
			buffer_ptr++;
		}
		sprintf(buffer_ptr, "%02x", *(array + i));
		buffer_ptr += 2;
	}
	buffer_ptr = 0;
	return buffer;
}

int main(int argc, char **argv) {
	/*uint32_t key[8] = {*/
		/*0x83828180, 0x87868584, 0x8b8a8988, 0x8f8e8d8c,*/
		/*0x93929190, 0x97969594, 0x9b9a9998, 0x9f9e9d9c};*/
	/*uint32_t counter[4] = {*/
		/*0x00000001, 0x00000007, 0x43424140, 0x47464544};*/
	/*uint8_t plaintext[0x72] = {*/
		/*0x4c, 0x61, 0x64, 0x69, 0x65, 0x73, 0x20, 0x61,*/
		/*0x6e, 0x64, 0x20, 0x47, 0x65, 0x6e, 0x74, 0x6c,*/
		/*0x65, 0x6d, 0x65, 0x6e, 0x20, 0x6f, 0x66, 0x20,*/
		/*0x74, 0x68, 0x65, 0x20, 0x63, 0x6c, 0x61, 0x73,*/
		/*0x73, 0x20, 0x6f, 0x66, 0x20, 0x27, 0x39, 0x39,*/
		/*0x3a, 0x20, 0x49, 0x66, 0x20, 0x49, 0x20, 0x63,*/
		/*0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6f, 0x66, 0x66,*/
		/*0x65, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x6f,*/
		/*0x6e, 0x6c, 0x79, 0x20, 0x6f, 0x6e, 0x65, 0x20,*/
		/*0x74, 0x69, 0x70, 0x20, 0x66, 0x6f, 0x72, 0x20,*/
		/*0x74, 0x68, 0x65, 0x20, 0x66, 0x75, 0x74, 0x75,*/
		/*0x72, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x73,*/
		/*0x63, 0x72, 0x65, 0x65, 0x6e, 0x20, 0x77, 0x6f,*/
		/*0x75, 0x6c, 0x64, 0x20, 0x62, 0x65, 0x20, 0x69,*/
		/*0x74, 0x2e};*/
	/*uint8_t encrypted[0x72];*/
	/*uint32_t text_size = 0x72;*/


/*length: 256,*/
/*key:    [8]uint32{0x7dec8e64, 0x9f12b14, 0x6c70df2a, 0xeae0aa0d, 0x27b1ac14, 0x7a00d833, 0xe63c0aca, 0x189438e2},*/
/*nonce:  [3]uint32{0x79cd7a62, 0xae619be, 0x7d96d236},*/
/*input:  "0cfd93b195e37dd15dfae83132c24ed5bfce7fe6fad4064b213b2c31a39e39ddad2f977e904c9c5b055ed03db46fcdd845bbb6ff0ab5a8c92e89295b6801f36ae63eba61fba24a3858aeb36f2da226b23b24d7b2c7d2670f23a9a1b60db85c0ecee584bef1b00e42d10ca17432    a74bbb220d88356d82c850da4c09dd5baf413caf8f9479e02a330065fb865489c0f59605d56146ec8434182345de2d15e2a1dceeeee2fe94871d41913f6788738947ed9849ca0ae985e3e19a97bee82b96feeddceb196c9b6012264661945981c279f43db9599a4ef01116f592478619690daa64387    290484d21e8d2444751194e1f361fb37f04014a3c7e4b409e5c828d8990",*/
/*output: "0502848571d1472ff10bec06c1299fad23a2cb824d88bf91b5447c5139500bd837a2fddc629e4a964e84907c1e6740263f1fef4f5ed41062982c150d9e77a1047b7d86c0e191945e8db00ca3845a39560857fc9e0e4a394eea4ba80a689cb5714c4bab7124ffdbfa8bbb91c3eb    3caa1621f49dba1eea3ebf1d547ee337f9085638a12317b86c11aa1525813445107038942fc519eebdc1b98d313ad822bf0b94a054259aa8cf1be4b3a68f974269729941747f9a23fa5d83453071b431dac62274c24f6a32248b0785ff90aad5840fadc89af0aef7553d9352cfb00d3999ffbe28cd9    fde7854e95710f4532b8bf5011e518c93361e58d22a2302182e00e8bccd",*/

	uint32_t key[8] = {
		0xe9124c25, 0x4fd1a373, 0x7945f7bb, 0xeed5f064,
		0x29c4185d, 0x3c9acf13, 0x4c94a367, 0x7c2c2c53};
	uint32_t counter[4] = {
		0x00000000, 0x512a6b49, 0x8df9af6d, 0x5336a2a5};
	uint8_t plaintext[2] = {
		0x54, 0xa6};
	uint8_t encrypted[2];
	uint32_t text_size = 2;

	/*memset((char *) plaintext, 0, 256);*/
	hexprint("plaintext", plaintext, text_size);
	ChaCha20_ctr32_vmx(encrypted, plaintext, text_size, key, counter);
	hexprint("encrypted", encrypted, text_size);
	/*memset((char *) plaintext, 0, 256);*/
	ChaCha20_ctr32_vmx(plaintext, encrypted, text_size, key, counter);
	hexprint("plaintext", plaintext, text_size);

	return 0;
}
