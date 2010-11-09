//metadoc Address

#ifndef ADDRESS_DEFINED
#define ADDRESS_DEFINED 1

//#include "Socket.h"
#include "Common.h"
#include "IPAddress.h"
#include "UnixPath.h"


typedef struct sockaddr * (Address_sockaddr_func) (void *self);
typedef socklen_t (Address_size_func)(void *self);
typedef void (Address_setSize_func)(void *self, socklen_t size);

typedef struct
{
	void *addr;
	Address_sockaddr_func *addrSockaddrFunc;
	Address_size_func *addrSizeFunc;
	Address_setSize_func *addrSetSizeFunc;
} Address;

Address *Address_new(void);
void Address_free(Address *self);

struct sockaddr *Address_sockaddr(Address *self);
socklen_t Address_size(Address *self);
void Address_setSize_(Address *self, socklen_t size);

#endif
