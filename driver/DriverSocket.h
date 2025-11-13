#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKET_H__

#include <string>

#include "../common/Socket.h"

class DriverSocket: public Socket {
public:
	DriverSocket() {}
	~DriverSocket() {}

	int Init(std::string ip, int port);
};


#endif // end of #ifndef __CLIENTSOCKET_H__
