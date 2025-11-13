#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "../common/ServerSocket.h"
#include "DriverServerStub.h"

// Thread function to handle each driver connection
void HandleDriverConnection(std::unique_ptr<ServerSocket> socket, int driver_id) {
	DriverServerStub stub;
	stub.Init(std::move(socket));
}

int main(int argc, char *argv[]) {
	int port;
	ServerSocket server_socket;
	std::unique_ptr<ServerSocket> client_socket;
	std::vector<std::thread> thread_vector;
	int driver_count = 0;

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

	// Accept driver connections and spawn a thread for each
	while ((client_socket = server_socket.Accept())) {
		std::cout << "Driver " << driver_count << " connected" << std::endl;

		std::thread driver_thread(HandleDriverConnection, std::move(client_socket), driver_count);
		thread_vector.push_back(std::move(driver_thread));

		driver_count++;
	}

	// Wait for all threads to complete (optional - won't reach here in normal operation)
	for (auto &thread : thread_vector) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	return 0;
}
