#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "aesp8-ppc.h"

char string[1024];

char *array2str(char *array, int size) {
	int i;
	char *str_ptr = string;

	for (i = 0; i < size; i++)
	{
		if (i != 0 && i % 4 == 0) sprintf(str_ptr++, " ");
		sprintf(str_ptr += 2, "%x", *(array + i));
	}
	str_ptr = 0;
	return string;
}

int main(int argc, char **argv) {
	unsigned char key[16] = {0x2b,0x7e,0x15,0x16,
		                     0x28,0xae,0xd2,0xa6,
		                     0xab,0xf7,0x15,0x88,
							 0x09,0xcf,0x4f,0x3c};
	int keylen = 16;
	struct aes_key enc_key;
	struct aes_key dec_key;
	int ret = 0;

	ret += aes_p8_set_encrypt_key(key, keylen * 8, &enc_key);
	ret += aes_p8_set_decrypt_key(key, keylen * 8, &dec_key);

	printf("string: %s\n", array2str(key, keylen));

	return ret;
}
