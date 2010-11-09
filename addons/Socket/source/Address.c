#include "Address.h"
#include <stdlib.h>
#include <string.h>

Address *Address_new(void)
{
	Address *self = io_calloc(1, sizeof(Address));
	memset(self, 0, sizeof(Address));
	return self;
}

void Address_free(Address *self)
{
	io_free(self);
}

// access

struct sockaddr *Address_sockaddr(Address *self)
{
	return (struct sockaddr *)(self->addrSockaddrFunc(self->addr));
}

socklen_t Address_size(Address *self)
{
	return self->addrSizeFunc(self->addr);
}

void Address_setSize_(Address *self, socklen_t size)
{
	self->addrSetSizeFunc(self->addr, size);
}
