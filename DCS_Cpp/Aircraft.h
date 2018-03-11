#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>

class Aircraft {
public:
	float Time, Vind_keas, Norml, Axial, Side, Q, P, R, Pitch, Roll, Hding, Lat, Lon, Alt, RAlt, Pos_E, Pos_U, Pos_S, Vel_E, Vel_U, Vel_S, Elev, Ailr, Rudd;
	std::string callsign;
	void decode(std::string);
	void encode(unsigned char*, int);
};