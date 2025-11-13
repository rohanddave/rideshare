#include "DriverHeartbeatHandler.h"
#include <iostream>
#include <cstring>

DriverHeartbeatHandler::DriverHeartbeatHandler() {}

void DriverHeartbeatHandler::HandleConnection(std::unique_ptr<ServerSocket> socket, int connection_id) {
	std::cout << "[HeartbeatHandler " << connection_id << "] Started handling heartbeat connection" << std::endl;

	HeartbeatMessage msg;

	while (true) {
		// Receive heartbeat message
		int bytes_received = socket->Recv((char*)&msg, sizeof(HeartbeatMessage), 0);

		if (bytes_received != sizeof(HeartbeatMessage)) {
			if (bytes_received == 0) {
				std::cout << "[HeartbeatHandler " << connection_id << "] Driver disconnected" << std::endl;
			} else {
				std::cout << "[HeartbeatHandler " << connection_id << "] Error receiving heartbeat" << std::endl;
			}
			break;
		}

		// Process the heartbeat
		std::cout << "[HeartbeatHandler " << connection_id << "] Received heartbeat from driver "
		          << msg.driver_id << " at (" << msg.latitude << ", " << msg.longitude
		          << ") timestamp: " << msg.timestamp << std::endl;

		// In a real system, you would:
		// - Update driver location in a shared data structure
		// - Update driver availability status
		// - Use this info for ride matching
	}

	std::cout << "[HeartbeatHandler " << connection_id << "] Connection closed" << std::endl;
}
