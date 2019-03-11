#pragma once

#include "Services.h"

class ARPSOServices : public Services
{
private:
	Rand randomizer;
public:
	ARPSOServices(std::string functionName) : Services(functionName) { randomizer.SetSeed(time(NULL)); }
	int getDirection(int dir, double diversity, const double *DT);
	void updateVelocity(Particle &particle, std::vector<double> globalBest, float iw, int sc, double cc, int dir, const float VMAX);
};