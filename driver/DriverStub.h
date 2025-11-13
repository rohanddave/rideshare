#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>
#include "DriverSocket.h"

class DriverStub {
private:
	DriverSocket socket;
public:
	DriverStub();
	int Init(std::string ip, int port);
};


#endif // end of #ifndef __CLIENT_STUB_H__
