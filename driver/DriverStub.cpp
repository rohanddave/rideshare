#include "DriverStub.h"
#include <iostream>

DriverStub::DriverStub() {}

int DriverStub::Init(std::string ip, int port) {
	// std::cout << "[ClientStub] Connecting to " << ip << ":" << port << std::endl;
	int result = socket.Init(ip, port);
	if (result) {
		// std::cout << "[ClientStub] Successfully connected to server" << std::endl;
	} else {
		// std::cout << "[ClientStub] Failed to connect to server" << std::endl;
	}
	return result;
}
