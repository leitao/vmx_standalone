#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "aesp8-ppc.h"

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
	unsigned char key[BLOCK] = {0x2b, 0x7e, 0x15, 0x16,
	                            0x28, 0xae, 0xd2, 0xa6,
	                            0xab, 0xf7, 0x15, 0x88,
	                            0x09, 0xcf, 0x4f, 0x3c};

	unsigned char txt[BLOCK] = {0x32, 0x43, 0xf6, 0xa8,
	                            0x88, 0x5a, 0x30, 0x8d,
	                            0x31, 0x31, 0x98, 0xa2,
	                            0xe0, 0x37, 0x07, 0x34};

	int keylen = 16;
	struct aes_key enc_key;
	struct aes_key dec_key;
	int ret = 0;
	char encoded[BLOCK];
	char decoded[BLOCK];

	printf("key:\n%s\n\n", array2str(key, keylen));

	ret += aes_p8_set_encrypt_key(key, keylen * 8, &enc_key);
	printf("key encode:\n%s\n\n", array2str(enc_key.key, 16*11));

	ret += aes_p8_set_decrypt_key(key, keylen * 8, &dec_key);
	printf("key decode:\n%s\n\n", array2str(dec_key.key, 16*11));

	printf("string:\n%s\n\n", array2str(txt, BLOCK));

	aes_p8_encrypt(txt, encoded, &enc_key);
	printf("string encoded:\n%s\n\n", array2str(encoded, BLOCK));

	aes_p8_decrypt(encoded, decoded, &dec_key);
	printf("string decoded:\n%s\n\n", array2str(decoded, BLOCK));

	return ret;
}
