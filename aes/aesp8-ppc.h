
#define AES_MAX_KEYLENGTH	(15 * 16)

struct aes_key {
	uint8_t key[AES_MAX_KEYLENGTH];
	int rounds;
};

int aes_p8_set_encrypt_key(const uint8_t *userKey, const int bits,
			   struct aes_key *key);
int aes_p8_set_decrypt_key(const uint8_t *userKey, const int bits,
			   struct aes_key *key);

void aes_p8_encrypt(const uint8_t *in, uint8_t *out, const struct aes_key *key);
void aes_p8_decrypt(const uint8_t *in, uint8_t *out, const struct aes_key *key);
void aes_p8_cbc_encrypt(const uint8_t *in, uint8_t *out, uint16_t len,
			const struct aes_key *key, uint8_t *iv, const int enc);
void aes_p8_ctr32_encrypt_blocks(const uint8_t *in, uint8_t *out,
				 uint16_t len, const struct aes_key *key,
				 const uint8_t *iv);
void aes_p8_xts_encrypt(const uint8_t *in, uint8_t *out, uint16_t len,
			const struct aes_key *key1, const struct aes_key *key2, uint8_t *iv);
void aes_p8_xts_decrypt(const uint8_t *in, uint8_t *out, uint16_t len,
			const struct aes_key *key1, const struct aes_key *key2, uint8_t *iv);
