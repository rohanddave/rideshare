#include "DriverHeartbeatHandler.h"
#include <iostream>
#include <cstring>

DriverHeartbeatHandler::DriverHeartbeatHandler() {}

void DriverHeartbeatHandler::HandleConnection(std::unique_ptr<ServerSocket> socket, int connection_id) {
	std::cout << "[HeartbeatHandler " << connection_id << "] Started handling heartbeat connection" << std::endl;

	HeartbeatMessage msg;
	char buffer[HeartbeatMessage::Size()];

	while (true) {
		// Receive heartbeat message
		int result = socket->Recv(buffer, HeartbeatMessage::Size(), 0);

		if (!result) {
			std::cout << "[HeartbeatHandler " << connection_id << "] Driver disconnected or error receiving heartbeat" << std::endl;
			break;
		}

		// Unmarshal the message
		msg.Unmarshal(buffer);

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
