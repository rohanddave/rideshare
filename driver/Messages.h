#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <ctime>

// Message types
enum MessageType {
	MSG_HEARTBEAT = 1,
	MSG_RIDE_REQUEST = 2,
	MSG_ACKNOWLEDGMENT = 3
};

// Heartbeat message structure
// Sent from driver client to server every 5 seconds
struct HeartbeatMessage {
	int driver_id;
	float latitude;
	float longitude;
	time_t timestamp;

	HeartbeatMessage() : driver_id(0), latitude(0.0f), longitude(0.0f), timestamp(0) {}

	HeartbeatMessage(int id, float lat, float lon)
		: driver_id(id), latitude(lat), longitude(lon) {
		timestamp = time(nullptr);
	}
};

// Ride request message structure
// Sent from server to driver client when a ride is requested
struct RideRequestMessage {
	int request_id;
	float pickup_latitude;
	float pickup_longitude;
	float destination_latitude;
	float destination_longitude;

	RideRequestMessage()
		: request_id(0),
		  pickup_latitude(0.0f),
		  pickup_longitude(0.0f),
		  destination_latitude(0.0f),
		  destination_longitude(0.0f) {}

	RideRequestMessage(int id, float p_lat, float p_lon, float d_lat, float d_lon)
		: request_id(id),
		  pickup_latitude(p_lat),
		  pickup_longitude(p_lon),
		  destination_latitude(d_lat),
		  destination_longitude(d_lon) {}
};

// Acknowledgment message structure
// Sent from driver client to server after receiving a ride request
struct AcknowledgmentMessage {
	int request_id;
	int driver_id;
	bool accepted;

	AcknowledgmentMessage() : request_id(0), driver_id(0), accepted(false) {}

	AcknowledgmentMessage(int req_id, int drv_id, bool acc)
		: request_id(req_id), driver_id(drv_id), accepted(acc) {}
};

#endif // end of #ifndef __MESSAGES_H__
