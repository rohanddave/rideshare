#include "DriverClientStub.h"
#include <iostream>

DriverClientStub::DriverClientStub() {}

int DriverClientStub::Init(std::string server_ip, int server_port) {
	std::cout << "[DriverClientStub] Connecting to " << server_ip << ":" << server_port << std::endl;
	int result = socket.Init(server_ip, server_port);
	if (result) {
		std::cout << "[DriverClientStub] Successfully connected to server" << std::endl;
	} else {
		std::cout << "[DriverClientStub] Failed to connect to server" << std::endl;
	}
	return result;
}

int DriverClientStub::GetID() {
	return id;
}

std::string DriverClientStub::GetName() {
	return name;
}