/*   copyright: Oscar Martinez, 2010
 *   All rights reserved. See _BSDLicense.txt.
 */

#ifndef IoSHA256_DEFINED
#define IoSHA256_DEFINED 1

#include "IoObject.h"
#include "IoNumber.h"
#include "sha2.h"

#define ISSHA256(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoSHA256_rawClone)

typedef IoObject IoSHA256;

typedef struct
{
	SHA256_CTX context;
	u_int8_t digest[SHA256_DIGEST_LENGTH];
	char isDone;
} IoSHA256Data;

IoSHA256 *IoSHA256_rawClone(IoSHA256 *self);
IoSHA256 *IoSHA256_proto(void *state);
IoSHA256 *IoSHA256_new(void *state);

void IoSHA256_free(IoSHA256 *self);
void IoSHA256_mark(IoSHA256 *self);

/* ----------------------------------------------------------- */

IoObject *IoSHA256_appendSeq(IoSHA256 *self, IoObject *locals, IoMessage *m);
IoObject *IoSHA256_sha256(IoSHA256 *self, IoObject *locals, IoMessage *m);
IoObject *IoSHA256_sha256String(IoSHA256 *self, IoObject *locals, IoMessage *m);

IoObject *IoSHA256_hmac(IoSHA256 *self, IoObject *locals, IoMessage *m);

#endif
