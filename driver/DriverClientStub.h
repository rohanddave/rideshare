#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>
#include "DriverSocket.h"
#include "Messages.h"

class DriverClientStub {
private:
	DriverSocket heartbeat_socket;
	DriverSocket request_socket;
	int id;
	std::string name;
	float latitude;
	float longitude;
public:
	DriverClientStub();

	// Initialize both socket connections
	int InitHeartbeatConnection(std::string server_ip, int server_port);
	int InitRequestConnection(std::string server_ip, int server_port);

	// Heartbeat operations (fire-and-forget)
	bool SendHeartbeat();

	// Ride request operations (blocking)
	RideRequestMessage ReceiveRideRequest();
	bool SendAcknowledgment(int request_id, bool accepted);

	// Getters and setters
	int GetID();
	void SetID(int driver_id) { id = driver_id; }
	std::string GetName();
	float GetLatitude();
	float GetLongitude();
	void SetLocation(float lat, float lon);
};


#endif // end of #ifndef __CLIENT_STUB_H__
