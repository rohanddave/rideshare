#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>
#include "DriverSocket.h"

class DriverClientStub {
private:
	DriverSocket socket;
	int id; 
	std::string name;
	float latitude;
	float longitude;
public:
	DriverClientStub();
	int Init(std::string server_ip, int server_port);
	int GetID();
	void SetID(int driver_id) { id = driver_id; }
	std::string GetName();
	float GetLatitude();
	float GetLongitude();
	void SetLocation(float lat, float lon);
};


#endif // end of #ifndef __CLIENT_STUB_H__
