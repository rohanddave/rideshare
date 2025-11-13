#include "DriverClientStub.h"
#include <iostream>
#include <cstring>

DriverClientStub::DriverClientStub() : id(0), latitude(0.0f), longitude(0.0f) {}

int DriverClientStub::InitHeartbeatConnection(std::string server_ip, int server_port) {
	std::cout << "[Driver " << id << "] Connecting heartbeat socket to "
	          << server_ip << ":" << server_port << std::endl;

	int result = heartbeat_socket.Init(server_ip, server_port);

	if (result) {
		std::cout << "[Driver " << id << "] Heartbeat connection established" << std::endl;
	} else {
		std::cout << "[Driver " << id << "] Failed to establish heartbeat connection" << std::endl;
	}

	return result;
}

int DriverClientStub::InitRequestConnection(std::string server_ip, int server_port) {
	std::cout << "[Driver " << id << "] Connecting ride request socket to "
	          << server_ip << ":" << server_port << std::endl;

	int result = request_socket.Init(server_ip, server_port);

	if (result) {
		std::cout << "[Driver " << id << "] Ride request connection established" << std::endl;
	} else {
		std::cout << "[Driver " << id << "] Failed to establish ride request connection" << std::endl;
	}

	return result;
}

bool DriverClientStub::SendHeartbeat() {
	HeartbeatMessage msg(id, latitude, longitude);
	char buffer[HeartbeatMessage::Size()];

	msg.Marshal(buffer);

	int bytes_sent = heartbeat_socket.Send(buffer, HeartbeatMessage::Size(), 0);

	if (bytes_sent != HeartbeatMessage::Size()) {
		std::cout << "[Driver " << id << "] Failed to send heartbeat" << std::endl;
		return false;
	}

	std::cout << "[Driver " << id << "] Heartbeat sent (lat: " << latitude
	          << ", lon: " << longitude << ")" << std::endl;
	return true;
}

RideRequestMessage DriverClientStub::ReceiveRideRequest() {
	RideRequestMessage msg;
	char buffer[RideRequestMessage::Size()];

	int bytes_received = request_socket.Recv(buffer, RideRequestMessage::Size(), 0);

	if (bytes_received != RideRequestMessage::Size()) {
		std::cout << "[Driver " << id << "] Failed to receive ride request or connection closed" << std::endl;
		msg.request_id = -1;  // Indicate error
		return msg;
	}

	msg.Unmarshal(buffer);

	std::cout << "[Driver " << id << "] Received ride request #" << msg.request_id
	          << " (pickup: " << msg.pickup_latitude << ", " << msg.pickup_longitude << ")" << std::endl;

	return msg;
}

bool DriverClientStub::SendAcknowledgment(int request_id, bool accepted) {
	AcknowledgmentMessage msg(request_id, id, accepted);
	char buffer[AcknowledgmentMessage::Size()];

	msg.Marshal(buffer);

	int bytes_sent = request_socket.Send(buffer, AcknowledgmentMessage::Size(), 0);

	if (bytes_sent != AcknowledgmentMessage::Size()) {
		std::cout << "[Driver " << id << "] Failed to send acknowledgment" << std::endl;
		return false;
	}

	std::cout << "[Driver " << id << "] Sent acknowledgment for request #" << request_id
	          << " (accepted: " << (accepted ? "yes" : "no") << ")" << std::endl;

	return true;
}

int DriverClientStub::GetID() {
	return id;
}

std::string DriverClientStub::GetName() {
	return name;
}

float DriverClientStub::GetLatitude() {
	return latitude;
}

float DriverClientStub::GetLongitude() {
	return longitude;
}

void DriverClientStub::SetLocation(float lat, float lon) {
	latitude = lat;
	longitude = lon;
}