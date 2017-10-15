#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "chacha-ppc.h"

#define BLOCK 16

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

#define TEXT_SIZE 128

int main(int argc, char **argv) {
	uint32_t key[8] = {
		0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
		0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
	uint32_t counter[4] = {
		0x00000001, 0x09000000, 0x4a000000, 0x00000000};
	uint8_t plaintext[TEXT_SIZE];
	uint8_t encrypted[TEXT_SIZE];
	uint32_t text_size;

	memset((char *) plaintext, 0, TEXT_SIZE);
	memset((char *) encrypted, 0, TEXT_SIZE);

	/*sprintf((char *) plaintext, "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.");*/
	/*text_size = strlen((char *) plaintext);*/
	text_size = TEXT_SIZE;

	hexprint("plaintext", plaintext, text_size);
	ChaCha20_ctr32_vmx(encrypted, plaintext, text_size, key, counter);
	hexprint("encrypted", encrypted, text_size);
	memset((char *) plaintext, 0, TEXT_SIZE);
	ChaCha20_ctr32_vmx(plaintext, encrypted, text_size, key, counter);
	hexprint("plaintext", plaintext, text_size);

	return 0;
}
