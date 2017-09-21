#define CHACHA_BLK_SIZE		64

void ChaCha20_ctr32_int(uint32_t *output, uint32_t *input);
void ChaCha20_ctr32_vmx(unsigned char *out, const unsigned char *inp,
		size_t len, const unsigned int key[8], const unsigned int counter[4]);

