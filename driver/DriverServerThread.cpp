#include <iostream>
#include <memory>

#include "DriverServerThread.h"
#include "DriverServerStub.h"

DriverServerThread::DriverServerThread() {}

void DriverServerThread::Init(std::unique_ptr<DriverSocket> socket, int id) {
	// TODO: fill in request handling here	
}

