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
			altitude = (atof(val.c_str())*3.28084)/100;
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
		// This isnt a mistake either
		else if (var_name.compare("gyro_y") == 0)
			gyro_z = atof(val.c_str())*-1;
		else if (var_name.compare("gyro_z") == 0)
			gyro_y = atof(val.c_str());
		else if (var_name.compare("accel_x") == 0)
			accel_x = atof(val.c_str());
		// The below is not a mistake
		else if (var_name.compare("accel_y") == 0)
			accel_z = atof(val.c_str());
		else if (var_name.compare("accel_z") == 0)
			accel_y = atof(val.c_str())*-1;

		start = finish;

		if (start > len)
			break;

	}
}

void Aircraft::encode(unsigned char* msg_out_section, int subject)
{
	unsigned char* vp;

	ZeroMemory(msg_out_section, 36);

	// Subject of the message
	msg_out_section[0] = subject;

	// Lat, long, alt, radalt
	if (subject == 20)
	{
		vp = (unsigned char*)&latitude;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&longitude;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&altitude;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];

		vp = (unsigned char*)&radar_altitude;
		msg_out_section[16] = vp[0];
		msg_out_section[17] = vp[1];
		msg_out_section[18] = vp[2];
		msg_out_section[19] = vp[3];
	}
	else if (subject == 3)
	{
		vp = (unsigned char*)&indicated_airspeed;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];
	}
	else if (subject == 1)
	{
		vp = (unsigned char*)&t;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	else if (subject == 17)
	{
		vp = (unsigned char*)&pitch;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&bank;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&heading;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	else if (subject == 16)
	{
		vp = (unsigned char*)&gyro_y;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&gyro_x;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&gyro_z;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	else if (subject == 4)
	{
		vp = (unsigned char*)&accel_z;
		msg_out_section[20] = vp[0];
		msg_out_section[21] = vp[1];
		msg_out_section[22] = vp[2];
		msg_out_section[23] = vp[3];

		vp = (unsigned char*)&accel_x;
		msg_out_section[24] = vp[0];
		msg_out_section[25] = vp[1];
		msg_out_section[26] = vp[2];
		msg_out_section[27] = vp[3];

		vp = (unsigned char*)&accel_y;
		msg_out_section[28] = vp[0];
		msg_out_section[29] = vp[1];
		msg_out_section[30] = vp[2];
		msg_out_section[31] = vp[3];
	}
	return;

}