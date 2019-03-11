#include <iostream>
#include <vector>
#include <cmath>

#include "Particle.h"
#include "ARPSOServices.h"

int main()
{
	int DIM = 10;
	const int NPART = 20; // Number of particles.
	float RANGE[2] = { -50, 50 };
	double STOPC = 1e-10;
	int k = 1;
	double DT[2] = { 1e-6, .25 };
	int dir = 1;
	float IWMIN = .4f;
	float IWMAX = .7f;
	const int MAXITER = 5000;
	const int SC = 2;
	const int CC = 2;
	std::string functionName("ackley");

	double diagonalLength = 0; // Diagonal length of the search space.
	for (int i = 0; i < DIM; i++)
	{
		diagonalLength += std::pow(RANGE[1] - RANGE[0], 2);
	}
	diagonalLength = std::sqrt(diagonalLength);

	const float VMAX = k * (RANGE[1] - RANGE[0]) / 2;
	const float VMAXSet[2] = { -VMAX, VMAX };

	std::vector<double> IW(MAXITER);

	//Iteration dependant inertial weight.
	for (int i = 0; i < MAXITER; i++)
	{
		IW[i] = IWMAX - (i + 1) * (IWMAX - IWMIN) / MAXITER;
	}

	std::vector<Particle> swarm;

	ARPSOServices services(functionName);

	for (int i = 0; i < NPART; i++)
	{
		Particle particle;

		particle.setPosition(services.generateRandomSet(DIM, RANGE));
		particle.setVelocity(services.generateRandomSet(DIM, VMAXSet));
		particle.setFitness(services.evaluateParticle(particle.getPosition()));
		particle.setPersonalBestPosition(particle.getPosition());
		particle.setPersonalBestFitness(particle.getFitness());

		swarm.push_back(particle);
	}

	int globalBest = services.getGlobalBest(swarm);
	double diversity = 0; 
	int sr = 0;

	clock_t tStart = clock();

	//////////////////////////EXCLUIR
	int genencontrado = 0;
	//////////////////////////////////

	for (int i = 0; i < MAXITER; i++)
	{
		diversity = services.getDiversity(swarm, diagonalLength, swarm.size(), DIM);

		dir = services.getDirection(dir, diversity, DT);

		for (int j = 0; j < NPART; j++)
		{
			services.updateVelocity(swarm[j], swarm[globalBest].getPosition(), IW[i], SC, CC, dir, VMAX);

			services.updatePosition(swarm[j]);
			services.truncSpace(swarm[j], RANGE);

			swarm[j].setFitness(services.evaluateParticle(swarm[j].getPosition()));

			services.updatePersonalBest(swarm[j]);

			if (swarm[j].getPersonalBestFitness() < swarm[globalBest].getPersonalBestFitness())
			{
				globalBest = j;
				genencontrado = i;
			}
		}
		
		std::cout << "Iteration: " << i << "\n Best Fitness: " << swarm[globalBest].getPersonalBestFitness() << "\n Diversity: " << diversity << "\n";

		if (swarm[globalBest].getPersonalBestFitness() < STOPC)
			break;

	}

	std::cout << "\nExecution time: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "\n\n";

	std::cout << "\nEncontrado: " << genencontrado << "\n\n";

	system("PAUSE");
}