#include "DriverClientThread.h"

#include <iostream>
#include <thread>
#include <chrono>

DriverClientThread::DriverClientThread() {}

void DriverClientThread::ThreadBody(std::string ip, int port, int id) {
	stub.SetID(id);

	// Initialize a random starting location for this driver (simulate GPS)
	float base_lat = 37.7749f + (id * 0.01f);  // San Francisco area
	float base_lon = -122.4194f + (id * 0.01f);
	stub.SetLocation(base_lat, base_lon);

	std::cout << "[Driver " << id << "] Starting at location (" << base_lat << ", " << base_lon << ")" << std::endl;

	// Connect both sockets to the server
	std::cout << "[Driver " << id << "] Connecting to server at " << ip << ":" << port << std::endl;

	if (!stub.InitHeartbeatConnection(ip, port)) {
		std::cout << "[Driver " << id << "] Failed to establish heartbeat connection" << std::endl;
		return;
	}

	if (!stub.InitRequestConnection(ip, port)) {
		std::cout << "[Driver " << id << "] Failed to establish ride request connection" << std::endl;
		return;
	}

	std::cout << "[Driver " << id << "] Both connections established successfully" << std::endl;

	// Spawn two threads: one for heartbeats, one for ride requests
	std::thread heartbeat_thread(&DriverClientThread::HeartbeatThread, this);
	std::thread request_thread(&DriverClientThread::RequestHandlerThread, this);

	// Wait for both threads (they run indefinitely)
	heartbeat_thread.join();
	request_thread.join();
}

void DriverClientThread::HeartbeatThread() {
	std::cout << "[Driver " << stub.GetID() << "] Heartbeat thread started" << std::endl;

	while (true) {
		// Simulate slight location changes (driver moving)
		float lat = stub.GetLatitude() + ((rand() % 100 - 50) / 10000.0f);
		float lon = stub.GetLongitude() + ((rand() % 100 - 50) / 10000.0f);
		stub.SetLocation(lat, lon);

		// Send heartbeat with current location
		if (!stub.SendHeartbeat()) {
			std::cout << "[Driver " << stub.GetID() << "] Heartbeat failed, connection may be lost" << std::endl;
			break;
		}

		// Wait 5 seconds before next heartbeat
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	std::cout << "[Driver " << stub.GetID() << "] Heartbeat thread exiting" << std::endl;
}

void DriverClientThread::RequestHandlerThread() {
	std::cout << "[Driver " << stub.GetID() << "] Request handler thread started" << std::endl;

	while (true) {
		// Blocking recv() waiting for ride requests
		RideRequestMessage request = stub.ReceiveRideRequest();

		if (request.request_id == -1) {
			std::cout << "[Driver " << stub.GetID() << "] Connection closed or error occurred" << std::endl;
			break;
		}

		std::cout << "[Driver " << stub.GetID() << "] Processing ride request #" << request.request_id << std::endl;

		// Accept the ride request and send acknowledgment
		bool accepted = true;
		if (!stub.SendAcknowledgment(request.request_id, accepted)) {
			std::cout << "[Driver " << stub.GetID() << "] Failed to send acknowledgment" << std::endl;
			break;
		}

		std::cout << "[Driver " << stub.GetID() << "] Ride request #" << request.request_id << " accepted" << std::endl;
	}

	std::cout << "[Driver " << stub.GetID() << "] Request handler thread exiting" << std::endl;
}
