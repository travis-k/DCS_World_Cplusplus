#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>

class Aircraft {
public:
	double t, latitude, longitude, altitude, heading, pitch, bank;
	std::string callsign;
	void decode(std::string);
};