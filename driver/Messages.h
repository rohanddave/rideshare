#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <cstring>
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

	void Marshal(char *buffer) {
		int offset = 0;
		memcpy(buffer + offset, &driver_id, sizeof(int));
		offset += sizeof(int);
		memcpy(buffer + offset, &latitude, sizeof(float));
		offset += sizeof(float);
		memcpy(buffer + offset, &longitude, sizeof(float));
		offset += sizeof(float);
		memcpy(buffer + offset, &timestamp, sizeof(time_t));
	}

	void Unmarshal(char *buffer) {
		int offset = 0;
		memcpy(&driver_id, buffer + offset, sizeof(int));
		offset += sizeof(int);
		memcpy(&latitude, buffer + offset, sizeof(float));
		offset += sizeof(float);
		memcpy(&longitude, buffer + offset, sizeof(float));
		offset += sizeof(float);
		memcpy(&timestamp, buffer + offset, sizeof(time_t));
	}

	static constexpr int Size() {
		return sizeof(int) + sizeof(float) + sizeof(float) + sizeof(time_t);
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

	void Marshal(char *buffer) {
		int offset = 0;
		memcpy(buffer + offset, &request_id, sizeof(int));
		offset += sizeof(int);
		memcpy(buffer + offset, &pickup_latitude, sizeof(float));
		offset += sizeof(float);
		memcpy(buffer + offset, &pickup_longitude, sizeof(float));
		offset += sizeof(float);
		memcpy(buffer + offset, &destination_latitude, sizeof(float));
		offset += sizeof(float);
		memcpy(buffer + offset, &destination_longitude, sizeof(float));
	}

	void Unmarshal(char *buffer) {
		int offset = 0;
		memcpy(&request_id, buffer + offset, sizeof(int));
		offset += sizeof(int);
		memcpy(&pickup_latitude, buffer + offset, sizeof(float));
		offset += sizeof(float);
		memcpy(&pickup_longitude, buffer + offset, sizeof(float));
		offset += sizeof(float);
		memcpy(&destination_latitude, buffer + offset, sizeof(float));
		offset += sizeof(float);
		memcpy(&destination_longitude, buffer + offset, sizeof(float));
	}

	static constexpr int Size() {
		return sizeof(int) + 4 * sizeof(float);
	}
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

	void Marshal(char *buffer) {
		int offset = 0;
		memcpy(buffer + offset, &request_id, sizeof(int));
		offset += sizeof(int);
		memcpy(buffer + offset, &driver_id, sizeof(int));
		offset += sizeof(int);
		memcpy(buffer + offset, &accepted, sizeof(bool));
	}

	void Unmarshal(char *buffer) {
		int offset = 0;
		memcpy(&request_id, buffer + offset, sizeof(int));
		offset += sizeof(int);
		memcpy(&driver_id, buffer + offset, sizeof(int));
		offset += sizeof(int);
		memcpy(&accepted, buffer + offset, sizeof(bool));
	}

	static constexpr int Size() {
		return sizeof(int) + sizeof(int) + sizeof(bool);
	}
};

#endif // end of #ifndef __MESSAGES_H__
