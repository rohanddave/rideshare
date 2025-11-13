#include "DriverClientThread.h"

#include <iostream>
#include <thread>
#include <chrono>

DriverClientThread::DriverClientThread() {}

void DriverClientThread::ThreadBody(std::string ip, int port, int id) {
	stub.SetID(id);

	std::cout << "[Driver " << id << "] Connecting to server at " << ip << ":" << port << std::endl;

	if (!stub.Init(ip, port)) {
		std::cout << "[Driver " << id << "] Failed to connect to server" << std::endl;
		return;
	}

	std::cout << "[Driver " << id << "] Successfully connected to server" << std::endl;

	// Keep the connection alive (simulate driver being online)
	// In a real implementation, this would handle incoming ride requests
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// TODO: Add logic to receive and handle ride requests from server
	}
}
