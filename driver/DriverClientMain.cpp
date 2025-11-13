#include <iostream>
#include <thread>
#include <vector>

#include "DriverClientThread.h"

int main(int argc, char *argv[]) {
	std::string server_ip;
	int server_port;
	int num_drivers;

	std::vector<std::thread> thread_vector;

	if (argc < 4) {
		std::cout << "Usage: " << argv[0] << " [server_ip] [server_port] [num_drivers]" << std::endl;
		std::cout << "Example: " << argv[0] << " 127.0.0.1 8080 5" << std::endl;
		return 1;
	}

	server_ip = argv[1];
	server_port = atoi(argv[2]);
	num_drivers = atoi(argv[3]);

	std::cout << "Starting " << num_drivers << " driver(s) to connect to "
	          << server_ip << ":" << server_port << std::endl;

	// Create and start driver threads
	for (int i = 0; i < num_drivers; i++) {
		DriverClientThread* driver_thread = new DriverClientThread();
		std::thread t(&DriverClientThread::ThreadBody, driver_thread,
		              server_ip, server_port, i);
		thread_vector.push_back(std::move(t));
	}

	// Wait for all driver threads to complete
	for (auto& th : thread_vector) {
		if (th.joinable()) {
			th.join();
		}
	}

	return 0;
}
