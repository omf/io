//metadoc IoAddressFamily

#ifndef IOADDRESSFAMILY_DEFINED
#define IOADDRESS_DEFINED 1

#include "IoIPAddress.h"
#include "IoUnixPath.h"
#include "Address.h"

#define ISADDRESSFAMILY(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoAddressFamily_rawClone)

typedef IoObject IoAddressFamily;

IoAddressFamily *IoMessage_locals_addressFamilyArgAt_(IoMessage *self, IoObject *locals, int n);
Address *IoMessage_locals_rawAddressArgAt_(IoMessage *self, IoObject *locals, int n);
Address *IoAddressFamily_rawAddress(IoAddressFamily *self);

IoAddressFamily *IoAddressFamily_proto(void *state);
IoAddressFamily *IoAddressFamily_new(void *state);
IoAddressFamily *IoAddressFamily_rawClone(IoAddressFamily *self);
void IoAddressFamily_free(IoAddressFamily *self);
void IoAddressFamily_mark(IoAddressFamily *self);

IoObject *IoAddressFamily_setAddress(IoAddressFamily *self, IoObject *locals, IoMessage *m);

#endif
