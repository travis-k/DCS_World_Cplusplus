#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "Aircraft.h"

int main()
{
	Aircraft AC1;

	std::string msg = "t = 0.3720, name = New callsign, latitude = 42.7268, longitude = 42.6386, altitude = 6096.1011, heading = 2.4470, pitch = 0.1528, bank = 0.0000\n";

	AC1.decode(msg);

	return 0;
}