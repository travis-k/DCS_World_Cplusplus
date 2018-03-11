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
		if (var_name.compare("Time") == 0)
			Time = atof(val.c_str());
		else if (var_name.compare("name") == 0)
			callsign = val;

		else if (var_name.compare("Vind_keas") == 0)
			Vind_keas = atof(val.c_str());

		else if (var_name.compare("Norml") == 0)
			Norml = atof(val.c_str());
		else if (var_name.compare("Axial") == 0)
			Axial = atof(val.c_str())*-1;
		else if (var_name.compare("Side") == 0)
			Side = atof(val.c_str());

		else if (var_name.compare("Q") == 0)
			Q = atof(val.c_str());
		else if (var_name.compare("P") == 0)
			P = atof(val.c_str());
		else if (var_name.compare("R") == 0)
			R = atof(val.c_str());

		else if (var_name.compare("Pitch") == 0)
			Pitch = atof(val.c_str());
		else if (var_name.compare("Roll") == 0)
			Roll = atof(val.c_str());
		else if (var_name.compare("Hding") == 0)
			Hding = atof(val.c_str());

		else if (var_name.compare("Lat") == 0)
			Lat = atof(val.c_str());
		else if (var_name.compare("Lon") == 0)
			Lon = atof(val.c_str());
		else if (var_name.compare("Alt") == 0)
			Alt = atof(val.c_str());
		else if (var_name.compare("RAlt") == 0)
			RAlt = atof(val.c_str());

		else if (var_name.compare("Pos_E") == 0)
			Pos_E = atof(val.c_str());
		else if (var_name.compare("Pos_U") == 0)
			Pos_U = atof(val.c_str());
		else if (var_name.compare("Pos_S") == 0)
			Pos_S = atof(val.c_str());

		else if (var_name.compare("Vel_E") == 0)
			Vel_E = atof(val.c_str());
		else if (var_name.compare("Vel_U") == 0)
			Vel_U = atof(val.c_str());
		else if (var_name.compare("Vel_S") == 0)
			Vel_S = atof(val.c_str());

		else if (var_name.compare("Elev") == 0)
			Elev = atof(val.c_str());
		else if (var_name.compare("Ailr") == 0)
			Ailr = atof(val.c_str());
		else if (var_name.compare("Rudd") == 0)
			Rudd = atof(val.c_str());

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
		vp = (unsigned char*)&Lat;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&Lon;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&Alt;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];

		vp = (unsigned char*)&RAlt;
		msg_out_section[16] = vp[0];
		msg_out_section[17] = vp[1];
		msg_out_section[18] = vp[2];
		msg_out_section[19] = vp[3];
	}
	else if (subject == 3)
	{
		vp = (unsigned char*)&Vind_keas;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];
	}
	else if (subject == 1)
	{
		vp = (unsigned char*)&Time;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	else if (subject == 17)
	{
		vp = (unsigned char*)&Pitch;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&Roll;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&Hding;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	else if (subject == 16)
	{
		vp = (unsigned char*)&Q;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&P;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&R;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	else if (subject == 21)
	{
		vp = (unsigned char*)&Pos_E;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&Pos_U;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&Pos_S;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];

		vp = (unsigned char*)&Vel_E;
		msg_out_section[16] = vp[0];
		msg_out_section[17] = vp[1];
		msg_out_section[18] = vp[2];
		msg_out_section[19] = vp[3];

		vp = (unsigned char*)&Vel_U;
		msg_out_section[20] = vp[0];
		msg_out_section[21] = vp[1];
		msg_out_section[22] = vp[2];
		msg_out_section[23] = vp[3];

		vp = (unsigned char*)&Vel_S;
		msg_out_section[24] = vp[0];
		msg_out_section[25] = vp[1];
		msg_out_section[26] = vp[2];
		msg_out_section[27] = vp[3];
	}
	else if (subject == 4)
	{
		vp = (unsigned char*)&Norml;
		msg_out_section[20] = vp[0];
		msg_out_section[21] = vp[1];
		msg_out_section[22] = vp[2];
		msg_out_section[23] = vp[3];

		vp = (unsigned char*)&Axial;
		msg_out_section[24] = vp[0];
		msg_out_section[25] = vp[1];
		msg_out_section[26] = vp[2];
		msg_out_section[27] = vp[3];

		vp = (unsigned char*)&Side;
		msg_out_section[28] = vp[0];
		msg_out_section[29] = vp[1];
		msg_out_section[30] = vp[2];
		msg_out_section[31] = vp[3];
	}
	else if (subject == 8)
	{
		vp = (unsigned char*)&Elev;
		msg_out_section[4] = vp[0];
		msg_out_section[5] = vp[1];
		msg_out_section[6] = vp[2];
		msg_out_section[7] = vp[3];

		vp = (unsigned char*)&Ailr;
		msg_out_section[8] = vp[0];
		msg_out_section[9] = vp[1];
		msg_out_section[10] = vp[2];
		msg_out_section[11] = vp[3];

		vp = (unsigned char*)&Rudd;
		msg_out_section[12] = vp[0];
		msg_out_section[13] = vp[1];
		msg_out_section[14] = vp[2];
		msg_out_section[15] = vp[3];
	}
	return;

}