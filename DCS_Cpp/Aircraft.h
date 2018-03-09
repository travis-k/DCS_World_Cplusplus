#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>

class Aircraft {
public:
	float t, latitude, longitude, altitude, radar_altitude, heading, pitch, bank, indicated_airspeed, gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z;
	std::string callsign;
	void decode(std::string);
	void encode(unsigned char*, int);
};