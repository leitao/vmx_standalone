#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "chacha-ppc.h"

#define BLOCK 16

struct chacha_t {

} chacha_t;

char buffer[512];

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

	uint32_t key[8] = {
		0x707e11a5, 0xbf683595, 0xdf620875, 0xaf926f9e,
		0x3a7c6781, 0x79848e18, 0x15a9a417, 0x2e79a7bd};
	uint32_t counter[4] = {
		0x00000001, 0xb5399012, 0x7a8a2e57, 0x6af73181};
	uint8_t plaintext[512];
	uint8_t encrypted[512];
	uint32_t text_size = 512;

	memset((char *) plaintext, 0, 512);

	hexprint("plaintext", plaintext, text_size);
	ChaCha20_ctr32_vmx(encrypted, plaintext, text_size, key, counter);
	hexprint("encrypted", encrypted, text_size);
	memset((char *) plaintext, 0, 512);
	ChaCha20_ctr32_vmx(plaintext, encrypted, text_size, key, counter);
	hexprint("plaintext", plaintext, text_size);

	return 0;
}
