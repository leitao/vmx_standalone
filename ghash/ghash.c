#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ghashp8-ppc.h"
#include "../aes/aesp8-ppc.h"

#define BLOCK 16

char buffer[512];

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
	unsigned char key[16] = {
		0x11, 0x75, 0x4c, 0xd7, 0x2a, 0xec, 0x30, 0x9b,
		0xf5, 0x2f, 0x76, 0x87, 0x21, 0x2e, 0x89, 0x57};
	unsigned char plain[16] = {};
	unsigned char product_key[16*16] = {};
	int ret = 0;
	struct aes_key enc_key;

	ret += aes_p8_set_encrypt_key(key, 16 * 8, &enc_key);
	printf("key encoded:\n%s\n\n", array2str(enc_key.key, 16));

	aes_p8_encrypt(plain, plain, &enc_key);
	printf("h:\n%s\n\n", array2str(plain, 16));

	printf("product_key:\n%s\n\n", array2str(product_key, 16*16));
	gcm_init_p8(product_key, plain);
	printf("product_key:\n%s\n\n", array2str(product_key, 16*16));

	return ret;
}
