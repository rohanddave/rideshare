#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>
#include "DriverSocket.h"

class DriverClientStub {
private:
	DriverSocket socket;
	int id; 
	std::string name;
public:
	DriverClientStub();
	int Init(std::string server_ip, int server_port);
	int GetID();
	std::string GetName();
};


#endif // end of #ifndef __CLIENT_STUB_H__
