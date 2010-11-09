//metadoc IPAddress copyright Steve Dekorte, 2004
//metadoc IPAddress license BSD revised
//metadoc IPAddress description Object representation of an Internet Protocol Address.
//metadoc IPAddress category Networking

/*doc IPAddress setHostName(hostName)
	Translates hostName to an IP using asynchronous DNS and 
	sets the host attribute. Returns self.
*/

#include "IoUnixPath.h"
#include "IoState.h"
#include "IoNumber.h"
#include "IoSeq.h"

#define UNIXPATH(self) ((UnixPath *)IoObject_dataPointer(self))

/*IoUnixPath *IoMessage_locals_addressArgAt_(IoMessage *self, IoObject *locals, int n)
{
	IoObject *v = IoMessage_locals_valueArgAt_(self, locals, n);

	if (!ISIPADDRESS(v))
	{
		IoMessage_locals_numberArgAt_errorForType_(self, locals, n, "address");
	}

	return v;
}

Address *IoMessage_locals_rawAddressArgAt_(IoMessage *self, IoObject *locals, int n)
{
	return IoUnixPath_rawAddress(IoMessage_locals_addressArgAt_(self, locals, n));
}

Address *IoUnixPath_rawAddress(IoUnixPath *self)
{
	return ADDRESS(self);
}
*/

IoTag *IoUnixPath_newTag(void *state)
{
	IoTag *tag = IoTag_newWithName_("UnixPath");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoUnixPath_rawClone);
	IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoUnixPath_free);
	return tag;
}

IoUnixPath *IoUnixPath_proto(void *state)
{
	IoObject *self = IoObject_new(state);

	IoObject_tag_(self, IoUnixPath_newTag(state));
	IoObject_setDataPointer_(self, UnixPath_new());

	IoState_registerProtoWithFunc_((IoState *)state, self, IoUnixPath_proto);

	{
		IoMethodTable methodTable[] = {
		{"path", IoUnixPath_path},
		{"setPath", IoUnixPath_setPath},
		{"setIp", IoUnixPath_setIp},
		{"ip", IoUnixPath_ip},

		{"setPort", IoUnixPath_setPort},
		{"port", IoUnixPath_port},

		{NULL, NULL},
		};
		IoObject_addMethodTable_(self, methodTable);
	}

	return self;
}

IoUnixPath *IoUnixPath_rawClone(IoUnixPath *proto)
{
	IoObject *self = IoObject_rawClonePrimitive(proto);
	IoObject_setDataPointer_(self, UnixPath_new());
	return self;
}

IoUnixPath *IoUnixPath_new(void *state)
{
	IoObject *proto = IoState_protoWithInitFunction_((IoState *)state, IoUnixPath_proto);
	return IOCLONE(proto);
}

void IoUnixPath_free(IoUnixPath *self)
{
	UnixPath_free(UNIXPATH(self));
}

// -----------------------------------------------------------

/*
IoUnixPath *IoUnixPath_newWithIPAddress_size_(void *state,
								  struct sockaddr *address,
								  size_t size)
{
	IoUnixPath *self = IoUnixPath_new(state);
	io_free(DATA(self)->address);
	DATA(self)->address = io_malloc(size);
	DATA(self)->size = size;
	memcpy(DATA(self)->address, address, size);
	return self;
}
*/

// path

IoObject *IoUnixPath_setPath(IoUnixPath *self, IoObject *locals, IoMessage *m)
{
	char *pathString = IoSeq_asCString(IoMessage_locals_seqArgAt_(m, locals, 0));
	UnixPath_setPath_(UNIXPATH(self), pathString);
	return self;
}

IoObject *IoUnixPath_path(IoUnixPath *self, IoObject *locals, IoMessage *m)
{
	return IOSYMBOL(UnixPath_path(UNIXPATH(self)));
}

// ip

IoObject *IoUnixPath_setIp(IoUnixPath *self, IoObject *locals, IoMessage *m)
{
	return IONIL(self);
}

IoObject *IoUnixPath_ip(IoUnixPath *self, IoObject *locals, IoMessage *m)
{
	return IONIL(self);
}

// port

IoObject *IoUnixPath_setPort(IoUnixPath *self, IoObject *locals, IoMessage *m)
{
	return IONIL(self);
}

IoObject *IoUnixPath_port(IoUnixPath *self, IoObject *locals, IoMessage *m)
{
	return IONIL(self);
}
