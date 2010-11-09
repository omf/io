
//metadoc SHA2 copyright Oscar Martinez 2010
//metadoc SHA2 license BSD revised
/*metadoc SHA2 description

<p>
Example:
<pre>
</pre>

*/
//metadoc SHA2 category Digests

#include "IoSHA256.h"
#include "IoState.h"
#include "IoSeq.h"

#define DATA(self) ((IoSHA256Data *)IoObject_dataPointer(self))

IoTag *IoSHA256_newTag(void *state)
{
	IoTag *tag = IoTag_newWithName_("SHA256");
	IoTag_state_(tag, state);
	IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoSHA256_free);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoSHA256_rawClone);
	return tag;
}

IoSHA256 *IoSHA256_proto(void *state)
{
	IoObject *self = IoObject_new(state);
	IoObject_tag_(self, IoSHA256_newTag(state));

	IoObject_setDataPointer_(self, calloc(1, sizeof(IoSHA256Data)));
	SHA256_Init(&(DATA(self)->context));

	IoState_registerProtoWithFunc_(state, self, IoSHA256_proto);

	{
		IoMethodTable methodTable[] = {
		{"appendSeq", IoSHA256_appendSeq},
		{"sha256", IoSHA256_sha256},
		{"sha256String", IoSHA256_sha256String},
		{"hmac", IoSHA256_hmac},
		{NULL, NULL},
		};
		IoObject_addMethodTable_(self, methodTable);
	}
	return self;
}

IoSHA256 *IoSHA256_rawClone(IoSHA256 *proto)
{
	IoObject *self = IoObject_rawClonePrimitive(proto);
	IoObject_setDataPointer_(self, calloc(1, sizeof(IoSHA256Data)));
	SHA256_Init(&(DATA(self)->context));
	return self;
}

IoSHA256 *IoSHA256_new(void *state)
{
	IoSHA256 *proto = IoState_protoWithInitFunction_(state, IoSHA256_proto);
	return IOCLONE(proto);
}

void IoSHA256_free(IoSHA256 *self)
{
	free(IoObject_dataPointer(self));
}

/* ----------------------------------------------------------- */

IoObject *IoSHA256_appendSeq(IoSHA256 *self, IoObject *locals, IoMessage *m)
{
	/*doc SHA256 appendSeq(aSequence)
	Appends aSequence to the hash calculation. Returns self.
	 */

	IoSeq *buffer = IoMessage_locals_seqArgAt_(m, locals, 0);
	IOASSERT(DATA(self)->isDone == 0, "cannot append to an already calculated SHA256");
	SHA256_Update(&(DATA(self)->context),
			 (unsigned char const *)IoSeq_rawBytes(buffer),
			 IoSeq_rawSize(buffer));
	return self;
}

UArray *IoSHA256_SHA256UArray(IoSHA256 *self)
{
	if (DATA(self)->isDone == 0)
	{
		SHA256_Final(DATA(self)->digest, &(DATA(self)->context));
		DATA(self)->isDone = 1;
	}

	return UArray_newWithData_type_size_copy_(DATA(self)->digest, CTYPE_uint8_t, SHA256_DIGEST_LENGTH, 1);
}

IoObject *IoSHA256_sha256(IoSHA256 *self, IoObject *locals, IoMessage *m)
{
	/*doc SHA256 sha256
	Completes the sha256 calculation and returns the hash as a Buffer.
	Once this method is called, append() should not be called again on the receiver or it will raise an exception.
	*/
	
	return IoSeq_newWithUArray_copy_(IOSTATE, IoSHA256_SHA256UArray(self), 0);
}

IoObject *IoSHA256_sha256String(IoSHA256 *self, IoObject *locals, IoMessage *m)
{
	/*doc SHA256 sha256String
	Returns a string containing a hexadecimal representation of the sha256 hash.
	*/
	
	UArray *ba = IoSHA256_SHA256UArray(self);
	UArray *baString = UArray_asNewHexStringUArray(ba);
	UArray_free(ba);
	return IoState_symbolWithUArray_copy_(IOSTATE, baString, 0);
}

/*
SHA256(key XOR opad, SHA256(key XOR ipad, text))	 
*/

void *memxor(void * dest, const void * src, size_t n)
{
	char const *s = src;
	char *d = dest;
	
	for (; n > 0; n--)
		*d++ ^= *s++;
	
	return dest;
}

void hmac_sha256(const void *key, size_t keylen, const void *text, size_t textlen, void *resbuf)
{
    SHA256_CTX context;
    char pad[64];
    char hash[32];
    char keyhash[32];

    if(keylen > 64) {
    	SHA256_Init(&context);
        SHA256_Update(&context, (unsigned char const *)key, keylen);
		SHA256_Final(keyhash, &context);

        keylen = 32;
        key = keyhash;
    }
    
    memset(pad, 0x36, 64);
    memxor(pad, key, keylen);
    
	SHA256_Init(&context);
    SHA256_Update(&context, (unsigned char const *)pad, 64);
    SHA256_Update(&context, (unsigned char const *)text, textlen);
	SHA256_Final(hash, &context);

    memset(pad, 0x5c, 64);
    memxor(pad, key, keylen);

	SHA256_Init(&context);
    SHA256_Update(&context, (unsigned char const *)pad, 64);
    SHA256_Update(&context, (unsigned char const *)hash, 32);
	SHA256_Final(resbuf, &context);
}


IoObject *IoSHA256_hmac(IoSHA256 *self, IoObject *locals, IoMessage *m)
{
	/*doc SHA256 hmac(key, data)
	Returns a hmac signature sequence or nil on error.
	*/
	
	IoSeq *key = IoMessage_locals_seqArgAt_(m, locals, 0);
	IoSeq *text = IoMessage_locals_seqArgAt_(m, locals, 1);
	char resbuf[32];
	memset(resbuf, 0x0, 32);
	hmac_sha256(
		IOSEQ_BYTES(key), IOSEQ_LENGTH(key),
		IOSEQ_BYTES(text), IOSEQ_LENGTH(text), 
		(void *)resbuf);

	//if(ok != 0) return IONIL(self);
	return IOSEQ(resbuf, 32);

}


