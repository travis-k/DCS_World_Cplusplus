#include "stdafx.h"
#include "Aircraft.h" 
#include <iostream>
#include <ws2tcpip.h>

void Aircraft::decode(std::string msg)
{
	int start = 0;
	int finish = 0;

	int len = msg.length();

	while (true)
	{
		// Finding name of value
		size_t found = msg.find('=', start);

		if (found > len)
			break;

		std::string var_name = msg.substr(start, found - start);

		// Cleaning string name
		var_name.erase(std::remove(var_name.begin(), var_name.end(), ','), var_name.end());
		var_name.erase(std::remove(var_name.begin(), var_name.end(), ' '), var_name.end());

		// Getting value
		finish = msg.find(',', found);
		std::string val = msg.substr(found + 1, finish - found + 1);
		val.erase(std::remove(val.begin(), val.end(), ','), val.end());
		val.erase(std::remove(val.begin(), val.end(), ' '), val.end());

		// Finding and sorting the values
		// This is a little convoluted but it allows us to change the
		// msg format a little easier
		// Change later?
		if (var_name.compare("t") == 0)
			t = atof(val.c_str());
		else if (var_name.compare("name") == 0)
			callsign = val;
		else if (var_name.compare("latitude") == 0)
			latitude = atof(val.c_str());
		else if (var_name.compare("longitude") == 0)
			longitude = atof(val.c_str());
		else if (var_name.compare("altitude") == 0)
			altitude = atof(val.c_str())*3.28084;
		else if (var_name.compare("radar_altitude") == 0)
			radar_altitude = atof(val.c_str())*3.28084;
		else if (var_name.compare("heading") == 0)
			heading = atof(val.c_str())*57.2958;
		else if (var_name.compare("pitch") == 0)
			pitch = atof(val.c_str())*57.2958;
		else if (var_name.compare("bank") == 0)
			bank = atof(val.c_str())*57.2958;
		else if (var_name.compare("indicated_airspeed") == 0)
			indicated_airspeed = atof(val.c_str())*1.9349;
		else if (var_name.compare("gyro_x") == 0)
			gyro_x = atof(val.c_str());
		else if (var_name.compare("gyro_y") == 0)
			gyro_y = atof(val.c_str());
		else if (var_name.compare("gyro_z") == 0)
			gyro_z = atof(val.c_str());
		else if (var_name.compare("accel_x") == 0)
			accel_x = atof(val.c_str());
		else if (var_name.compare("accel_y") == 0)
			accel_y = atof(val.c_str());
		else if (var_name.compare("accel_z") == 0)
			accel_z = atof(val.c_str());

		start = finish;

		if (start > len)
			break;

	}
}

void Aircraft::encode(unsigned char* msg_out, int subject) 
{
	uint8_t *vp;

	ZeroMemory(msg_out, 41);

	msg_out[0] = 68;
	msg_out[1] = 65;
	msg_out[2] = 84;
	msg_out[3] = 65;
	msg_out[4] = 0;

	// Subject of the message
	msg_out[5] = subject;

	// Lat, long, alt, radalt
	if (subject == 20)
	{
		vp = (uint8_t*)&latitude;
		msg_out[9] = vp[0];
		msg_out[10] = vp[1];
		msg_out[11] = vp[2];
		msg_out[12] = vp[3];

		vp = (uint8_t*)&longitude;
		msg_out[13] = vp[0];
		msg_out[14] = vp[1];
		msg_out[15] = vp[2];
		msg_out[16] = vp[3];

		vp = (uint8_t*)&altitude;
		msg_out[17] = vp[0];
		msg_out[18] = vp[1];
		msg_out[19] = vp[2];
		msg_out[20] = vp[3];

		vp = (uint8_t*)&radar_altitude;
		msg_out[21] = vp[0];
		msg_out[22] = vp[1];
		msg_out[23] = vp[2];
		msg_out[24] = vp[3];
	}
	else if (subject == 3)
	{
		vp = (uint8_t*)&indicated_airspeed;
		msg_out[13] = vp[0];
		msg_out[14] = vp[1];
		msg_out[15] = vp[2];
		msg_out[16] = vp[3];
	}
	else if (subject == 17)
	{
		vp = (uint8_t*)&pitch;
		msg_out[9] = vp[0];
		msg_out[10] = vp[1];
		msg_out[11] = vp[2];
		msg_out[12] = vp[3];

		vp = (uint8_t*)&bank;
		msg_out[13] = vp[0];
		msg_out[14] = vp[1];
		msg_out[15] = vp[2];
		msg_out[16] = vp[3];

		vp = (uint8_t*)&heading;
		msg_out[17] = vp[0];
		msg_out[18] = vp[1];
		msg_out[19] = vp[2];
		msg_out[20] = vp[3];
	}
	else if (subject == 16)
	{
		vp = (uint8_t*)&gyro_x;
		msg_out[9] = vp[0];
		msg_out[10] = vp[1];
		msg_out[11] = vp[2];
		msg_out[12] = vp[3];

		vp = (uint8_t*)&gyro_y;
		msg_out[13] = vp[0];
		msg_out[14] = vp[1];
		msg_out[15] = vp[2];
		msg_out[16] = vp[3];

		vp = (uint8_t*)&gyro_z;
		msg_out[17] = vp[0];
		msg_out[18] = vp[1];
		msg_out[19] = vp[2];
		msg_out[20] = vp[3];
	}
	else if (subject == 4)
	{
		vp = (uint8_t*)&accel_x;
		msg_out[25] = vp[0];
		msg_out[26] = vp[1];
		msg_out[27] = vp[2];
		msg_out[28] = vp[3];

		vp = (uint8_t*)&accel_y;
		msg_out[29] = vp[0];
		msg_out[30] = vp[1];
		msg_out[31] = vp[2];
		msg_out[32] = vp[3];

		vp = (uint8_t*)&accel_z;
		msg_out[33] = vp[0];
		msg_out[34] = vp[1];
		msg_out[35] = vp[2];
		msg_out[36] = vp[3];
	}
	return;

}