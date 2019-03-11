#include "ARPSOServices.h"

int ARPSOServices::getDirection(int dir, double diversity, const double *DT)
{
	if (dir > 0 && diversity < DT[0])
	{
		return -1;
	}
	else if (dir < 0 && diversity > DT[1])
	{
		return 1;
	}
}

void ARPSOServices::updateVelocity(Particle &particle, std::vector<double> globalBest, float iw, int cc, double sc, int dir, const float VMAX)
{
	std::vector<double> velocity = particle.getVelocity();
	std::vector<double> personalBestPosition = particle.getPersonalBestPosition();
	std::vector<double> currentPosition = particle.getPosition();

	for (int i = 0; i < velocity.size(); i++)
	{
		velocity[i] = iw * velocity[i] + dir * (
			cc * randomizer.Uniform() * (personalBestPosition[i] - currentPosition[i]) + 
			sc * randomizer.Uniform() * (globalBest[i] - currentPosition[i]));
	}

	velocity = trunc(velocity, VMAX);

	particle.setVelocity(velocity);
}