#ifndef __SERVER_STUB_H__
#define __SERVER_STUB_H__

#include <memory>

#include "../common/ServerSocket.h"

class DriverServerStub {
private:
	std::unique_ptr<ServerSocket> socket;
public:
	DriverServerStub();
	void Init(std::unique_ptr<ServerSocket> socket);
};

#endif // end of #ifndef __SERVER_STUB_H__
