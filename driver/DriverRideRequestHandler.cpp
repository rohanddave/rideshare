#include "DriverRideRequestHandler.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

DriverRideRequestHandler::DriverRideRequestHandler() {}

void DriverRideRequestHandler::HandleConnection(std::unique_ptr<ServerSocket> socket, int connection_id) {
	std::cout << "[RideRequestHandler " << connection_id << "] Started handling ride request connection" << std::endl;

	// For demonstration, send a test ride request after a short delay
	std::this_thread::sleep_for(std::chrono::seconds(10));

	// Create a sample ride request
	RideRequestMessage request(
		connection_id,           // request_id
		37.7849f,               // pickup_latitude
		-122.4094f,             // pickup_longitude
		37.7949f,               // destination_latitude
		-122.3994f              // destination_longitude
	);

	std::cout << "[RideRequestHandler " << connection_id << "] Sending ride request #"
	          << request.request_id << " to driver" << std::endl;

	// Send ride request to driver
	int bytes_sent = socket->Send((char*)&request, sizeof(RideRequestMessage), 0);

	if (bytes_sent != sizeof(RideRequestMessage)) {
		std::cout << "[RideRequestHandler " << connection_id << "] Failed to send ride request" << std::endl;
		return;
	}

	std::cout << "[RideRequestHandler " << connection_id << "] Ride request sent, waiting for acknowledgment..." << std::endl;

	// Wait for acknowledgment
	AcknowledgmentMessage ack;
	int bytes_received = socket->Recv((char*)&ack, sizeof(AcknowledgmentMessage), 0);

	if (bytes_received != sizeof(AcknowledgmentMessage)) {
		std::cout << "[RideRequestHandler " << connection_id << "] Failed to receive acknowledgment" << std::endl;
		return;
	}

	std::cout << "[RideRequestHandler " << connection_id << "] Received acknowledgment from driver "
	          << ack.driver_id << " for request #" << ack.request_id
	          << " - " << (ack.accepted ? "ACCEPTED" : "REJECTED") << std::endl;

	// Keep connection open for potential future ride requests
	std::cout << "[RideRequestHandler " << connection_id << "] Connection remains open for future requests" << std::endl;

	// In a real system, this would:
	// - Listen for incoming ride matching events
	// - Send ride requests when matches are found
	// - Handle multiple requests over the connection lifetime
	// - Coordinate with the booking service

	// For now, just keep the connection alive
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(30));
	}
}
