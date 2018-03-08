#include "stdafx.h"
#include "Aircraft.h" 

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
			altitude = atof(val.c_str());
		else if (var_name.compare("heading") == 0)
			heading = atof(val.c_str());
		else if (var_name.compare("pitch") == 0)
			pitch = atof(val.c_str());
		else if (var_name.compare("bank") == 0)
			bank = atof(val.c_str());

		start = finish;

		if (start > len)
			break;

	}
}
