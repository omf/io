//metadoc IPAddress copyright Steve Dekorte 2002
//metadoc IPAddress license BSD revised

#ifndef IOUNIXPATH_DEFINED
#define IOUNIXPATH_DEFINED 1

#include "IoObject.h"
#include "IoSeq.h"
#include "IPAddress.h"
#include "UnixPath.h"

#define ISUNIXPATH(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoUnixPath_rawClone)

typedef IoObject IoUnixPath;

IoUnixPath *IoMessage_locals_addressArgAt_(IoMessage *self, IoObject *locals, int n);
IPAddress *IoMessage_locals_rawIPAddressArgAt_(IoMessage *self, IoObject *locals, int n);

IoUnixPath *IoUnixPath_proto(void *state);
IoUnixPath *IoUnixPath_new(void *state);
IoUnixPath *IoUnixPath_rawClone(IoUnixPath *self);
void IoUnixPath_free(IoUnixPath *self);

IPAddress *IoUnixPath_rawIPAddress(IoUnixPath *self);

// path

IoObject *IoUnixPath_path(IoUnixPath *self, IoObject *locals, IoMessage *m);
IoObject *IoUnixPath_setPath(IoUnixPath *self, IoObject *locals, IoMessage *m);

// ip

IoObject *IoUnixPath_setIp(IoUnixPath *self, IoObject *locals, IoMessage *m);
IoObject *IoUnixPath_ip(IoUnixPath *self, IoObject *locals, IoMessage *m);

// port

IoObject *IoUnixPath_setPort(IoUnixPath *self, IoObject *locals, IoMessage *m);
IoObject *IoUnixPath_port(IoUnixPath *self, IoObject *locals, IoMessage *m);

#endif
