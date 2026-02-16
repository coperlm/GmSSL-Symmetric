/*
 *  Copyright 2014-2023 The GmSSL Project. All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the License); you may
 *  not use this file except in compliance with the License.
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 */



#include <stdio.h>
#include <gmssl/sm3.h>
// #include <gmssl/oid.h>  // Removed OID dependency
#include <gmssl/digest.h>
#include <gmssl/error.h>


typedef struct {
	int oid;
	char *short_name;
	char *display_name;
} DIGEST_TABLE;

DIGEST_TABLE digest_table[] = {
	{ 0, "sm3", "SM3" },  // OID removed
};

const char *digest_name(const DIGEST *digest)
{
	int i;
	for (i = 0; i < sizeof(digest_table)/sizeof(digest_table[0]); i++) {
		if (digest->oid == digest_table[i].oid) {
			return digest_table[i].short_name;
		}
	}
	return NULL;
}

int digest_init(DIGEST_CTX *ctx, const DIGEST *algor)
{
	memset(ctx, 0, sizeof(DIGEST_CTX));
	if (algor == NULL) {
		error_print();
		return -1;
	}
	ctx->digest = algor;
	ctx->digest->init(ctx);
	return 1;
}

int digest_update(DIGEST_CTX *ctx, const uint8_t *data, size_t datalen)
{
	if (data == NULL || datalen == 0) {
		return 0;
	}
	ctx->digest->update(ctx, data, datalen);
	return 1;
}

int digest_finish(DIGEST_CTX *ctx, uint8_t *dgst, size_t *dgstlen)
{
	if (dgst == NULL || dgstlen == NULL) {
		error_print();
		return -1;
	}
	ctx->digest->finish(ctx, dgst);
	*dgstlen = ctx->digest->digest_size;
	return 1;
}

int digest(const DIGEST *digest, const uint8_t *data, size_t datalen,
	uint8_t *dgst, size_t *dgstlen)
{
	DIGEST_CTX ctx;
	if (digest_init(&ctx, digest) != 1
		|| digest_update(&ctx, data, datalen) < 0
		|| digest_finish(&ctx, dgst, dgstlen) != 1) {
		error_print();
		return -1;
	}
	memset(&ctx, 0, sizeof(DIGEST_CTX));
	return 1;
}

const DIGEST *digest_from_name(const char *name)
{
	if (!strcmp(name, "sm3") || !strcmp(name, "SM3")) {
		return DIGEST_sm3();
#ifdef ENABLE_SHA1
	} else if (!strcmp(name, "sha1") || !strcmp(name, "SHA1")) {
		return DIGEST_sha1();
#endif
#ifdef ENABLE_SHA2
	} else if (!strcmp(name, "sha224") || !strcmp(name, "SHA224")) {
		return DIGEST_sha224();
	} else if (!strcmp(name, "sha256") || !strcmp(name, "SHA256")) {
		return DIGEST_sha256();
	} else if (!strcmp(name, "sha384") || !strcmp(name, "SHA384")) {
		return DIGEST_sha384();
	} else if (!strcmp(name, "sha512") || !strcmp(name, "SHA512")) {
		return DIGEST_sha512();
	} else if (!strcmp(name, "sha512-224") || !strcmp(name, "SHA512-224")) {
		return DIGEST_sha512_224();
	} else if (!strcmp(name, "sha512-256") || !strcmp(name, "SHA512-256")) {
		return DIGEST_sha512_256();
#endif
	}
	return NULL;
}

static int _sm3_digest_init(DIGEST_CTX *ctx)
{
	if (!ctx) {
		error_print();
		return -1;
	}
	sm3_init(&ctx->u.sm3_ctx);
	return 1;
}

static int _sm3_digest_update(DIGEST_CTX *ctx, const uint8_t *in, size_t inlen)
{
	if (!ctx || (!in && inlen != 0)) {
		error_print();
		return -1;
	}
	sm3_update(&ctx->u.sm3_ctx, in, inlen);
	return 1;
}

static int _sm3_digest_finish(DIGEST_CTX *ctx, uint8_t *dgst)
{
	if (!ctx || !dgst) {
		error_print();
		return -1;
	}
	sm3_finish(&ctx->u.sm3_ctx, dgst);
	return 1;
}

static const DIGEST sm3_digest_object = {
	0,  // OID removed
	SM3_DIGEST_SIZE,
	SM3_BLOCK_SIZE,
	sizeof(SM3_CTX),
	_sm3_digest_init,
	_sm3_digest_update,
	_sm3_digest_finish,
};

const DIGEST *DIGEST_sm3(void)
{
        return &sm3_digest_object;
}
