#include "DriverServerStub.h"

DriverServerStub::DriverServerStub() {}

void DriverServerStub::Init(std::unique_ptr<ServerSocket> socket) {
	this->socket = std::move(socket);
}
