#include "IoAddressFamily.h"
#include "IoState.h"

#define ADDRESS(self) ((Address *)IoObject_dataPointer(self))

IoAddressFamily *IoMessage_locals_addressFamilyArgAt_(IoMessage *self, IoObject *locals, int n)
{
	IoObject *v = IoMessage_locals_valueArgAt_(self, locals, n);

	if (!ISADDRESSFAMILY(v))
	{
		IoMessage_locals_numberArgAt_errorForType_(self, locals, n, "AddressFamily");
	}

	return v;
}

Address *IoMessage_locals_rawAddressArgAt_(IoMessage *self, IoObject *locals, int n)
{
	return IoAddressFamily_rawAddress(IoMessage_locals_addressFamilyArgAt_(self, locals, n));
}

Address *IoAddressFamily_rawAddress(IoAddressFamily *self)
{
	return ADDRESS(self);
}

IoTag *IoAddressFamily_newTag(void *state)
{
	IoTag *tag = IoTag_newWithName_("AddressFamily");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoAddressFamily_rawClone);
	IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoAddressFamily_free);
	//IoTag_markFunc_(tag, (IoTagMarkFunc *)IoAddress_mark);
	return tag;
}

IoAddressFamily *IoAddressFamily_proto(void *state)
{
	IoObject *self = IoObject_new(state);

	IoObject_tag_(self, IoAddressFamily_newTag(state));
	IoObject_setDataPointer_(self, Address_new());

	IoState_registerProtoWithFunc_((IoState *)state, self, IoAddressFamily_proto);

	{
		IoMethodTable methodTable[] = {
		{"setAddress", IoAddressFamily_setAddress},

		{NULL, NULL},
		};
		IoObject_addMethodTable_(self, methodTable);
	}

	return self;
}

IoAddressFamily *IoAddressFamily_rawClone(IoAddressFamily *proto)
{
	IoObject *self = IoObject_rawClonePrimitive(proto);
	Address *addr = Address_new();
	memcpy(addr, ADDRESS(proto), sizeof(Address));
	IoObject_setDataPointer_(self, addr);
	return self;
}

IoAddressFamily *IoAddressFamily_new(void *state)
{
	IoObject *proto = IoState_protoWithInitFunction_((IoState *)state, IoAddressFamily_proto);
	return IOCLONE(proto);
}

void IoAddressFamily_free(IoAddressFamily *self)
{
	Address_free(ADDRESS(self));
}

void IoAddressFamily_mark(IoAddressFamily *self)
{
}


// -----------------------------------------------------------

IoObject *IoAddressFamily_setAddress(IoAddressFamily *self, IoObject *locals, IoMessage *m)
{
	IoObject *addr = IoMessage_locals_valueArgAt_(m, locals, 0);

	if(ISIPADDRESS(addr)) {
		IPAddress *ipAddr = (IPAddress *)IoObject_dataPointer(addr);
		ADDRESS(self)->addr = ipAddr;
		ADDRESS(self)->addrSockaddrFunc = (Address_sockaddr_func *)IPAddress_sockaddr;
		ADDRESS(self)->addrSizeFunc = (Address_size_func *)IPAddress_size;
		ADDRESS(self)->addrSetSizeFunc = (Address_setSize_func *)IPAddress_setSize_;
	}
	else if(ISUNIXPATH(addr)) {
		UnixPath *unixPath = (UnixPath *)IoObject_dataPointer(addr);
		ADDRESS(self)->addr = unixPath;
		ADDRESS(self)->addrSockaddrFunc = (Address_sockaddr_func *)UnixPath_sockaddr;
		ADDRESS(self)->addrSizeFunc = (Address_size_func *)UnixPath_size;
		ADDRESS(self)->addrSetSizeFunc = (Address_setSize_func *)UnixPath_setSize_;
	}
	else {
		IoState_error_(IOSTATE, m, "Invalid address");
	}

	IoObject_setSlot_to_(self, IOSYMBOL("address"), addr);

	return self;
}

