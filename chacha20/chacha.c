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

int main(int argc, char **argv) {
	uint32_t key[8] = {
		0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
		0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
	uint32_t nonce[3] = {0x00, 0x4a000000, 0x0};
	uint32_t counter = 0x1;
	uint32_t input[16];
	uint32_t output[16];
	uint8_t plaintext[256];
	uint8_t encrypted[256];
	uint16_t text_size;

	memset((char *) plaintext, 0, 256);
	memset((char *) encrypted, 0, 256);
	memset((uint8_t *) output, 0, 4*16);
	sprintf((char *) plaintext, "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.");
	text_size = strlen((char *) plaintext);

	/* sigma constant "expand 32-byte k" in little-endian encoding */
	input[0] = ((uint32_t)'e') | ((uint32_t)'x'<<8) | ((uint32_t)'p'<<16) | ((uint32_t)'a'<<24);
	input[1] = ((uint32_t)'n') | ((uint32_t)'d'<<8) | ((uint32_t)' '<<16) | ((uint32_t)'3'<<24);
	input[2] = ((uint32_t)'2') | ((uint32_t)'-'<<8) | ((uint32_t)'b'<<16) | ((uint32_t)'y'<<24);
	input[3] = ((uint32_t)'t') | ((uint32_t)'e'<<8) | ((uint32_t)' '<<16) | ((uint32_t)'k'<<24);

	input[4] = key[0];
	input[5] = key[1];
	input[6] = key[2];
	input[7] = key[3];
	input[8] = key[4];
	input[9] = key[5];
	input[10] = key[6];
	input[11] = key[7];

	input[12] = counter;
	input[13] = nonce[0];
	input[14] = nonce[1];
	input[15] = nonce[2];

	hexprint32("input", input, 16);
	hexprint("plaintext", plaintext, text_size);
	ChaCha20_ctr32_vmx(encrypted, plaintext, text_size, key, &counter);
	hexprint("encrypted", encrypted, text_size);
	memset((char *) plaintext, 0, 256);
	ChaCha20_ctr32_vmx(plaintext, encrypted, text_size, key, &counter);
	hexprint("plaintext", plaintext, text_size);

	return 0;
}
