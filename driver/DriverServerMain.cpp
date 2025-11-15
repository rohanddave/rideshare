#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "../common/ServerSocket.h"
#include "DriverHeartbeatHandler.h"
#include "DriverRideRequestHandler.h"

int main(int argc, char *argv[]) {
	int port;
	ServerSocket server_socket;
	std::unique_ptr<ServerSocket> client_socket;
	std::vector<std::thread> thread_vector;
	int connection_count = 0;

	// Parse command line arguments
	// Format: ./server [port #]
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " [port #]" << std::endl;
		return 1;
	}

	port = atoi(argv[1]);

	// Initialize server socket
	if (!server_socket.Init(port)) {
		std::cout << "ERROR: Socket initialization failed on port " << port << std::endl;
		return 1;
	}

	std::cout << "Driver server listening on port " << port << std::endl;
	std::cout << "Waiting for driver connections..." << std::endl;
	std::cout << "Each driver will establish TWO connections:" << std::endl;
	std::cout << "  1. Heartbeat connection (for location updates)" << std::endl;
	std::cout << "  2. Ride request connection (for receiving ride assignments)" << std::endl;

	// Accept driver connections and spawn appropriate handler threads
	// Each driver will connect twice: once for heartbeats, once for ride requests
	while ((client_socket = server_socket.Accept())) {
		std::cout << "\n[Server] Connection #" << connection_count << " accepted" << std::endl;

		// Alternate between heartbeat and ride request handlers
		// Odd connections (0, 2, 4...) are heartbeat connections
		// Even connections (1, 3, 5...) are ride request connections
		if (connection_count % 2 == 0) {
			// This is a heartbeat connection
			std::cout << "[Server] Routing connection #" << connection_count << " to HeartbeatHandler" << std::endl;

			DriverHeartbeatHandler* handler = new DriverHeartbeatHandler();
			std::thread handler_thread(&DriverHeartbeatHandler::HandleConnection,
			                          handler, std::move(client_socket), connection_count);
			thread_vector.push_back(std::move(handler_thread));
		} else {
			// This is a ride request connection
			std::cout << "[Server] Routing connection #" << connection_count << " to RideRequestHandler" << std::endl;

			DriverRideRequestHandler* handler = new DriverRideRequestHandler();
			std::thread handler_thread(&DriverRideRequestHandler::HandleConnection,
			                          handler, std::move(client_socket), connection_count);
			thread_vector.push_back(std::move(handler_thread));
		}

		connection_count++;
	}

	// Wait for all threads to complete (won't reach here in normal operation)
	for (auto &thread : thread_vector) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	return 0;
}
