#include "clothsim.h"


/*NOTES FOR OTHER TEAM MEMBERS
	1. Need to move shit to a header.

*/

/*GLOBAL VARIABLES*/


std::vector<Particle> particleVector;
int particleSide = 10;
int numParticles = particleSide*particleSide;
int clothSize = 100;
glm::vec3 gravity = [0;
float damp = .1;
float timeStep = .5*.5;
int constraintIter = 15;

Particle::Particle()
{
	return;
}

Particle::Particle(float _mass, glm::vec3 _pos)
{
  	mass = _mass;
  	pos = _pos;
}

//evaluate the force acting on each particle
void Particle::evalForce()
{
	//pseudocode:
	//foreach particle, add the gravity force
	//foreach triangle in the cloth plane, calculate and add the wind
	//foreach spring, calculate and add in spring force to particles
	pos = pos + gravity;
	//vertlet integration
	glm::vec3 tmp;
	tmp = pos;
	pos = (pos-oldPos)*(1.0f*damp) + accel*timeStep;
	oldPos = tmp; 
}

ParticleSystem::ParticleSystem()
{
	return;
}

//we should do an evalForce function in each class for the different objects. Makes it 
//more specialized that way.


Sphere::Sphere()
{
	
}

Constraint::Constraint()
{

}

Constraint::makeConstraint(Particle part1, Particle part2)
{
	
}

Constraint::evalConstraint()
{

}



/* NOTES/THINGS TO CONSIDER

- for the particle numerical integration, we were thinking about doing either Euler or Verlet,
though verlet seems more desirable.
- should we be thinking about the optimal number of particles?  -> right now,
we're thinking about going with having a system that can work with an number of particles
(will use an integer variable, numParticles)


*/

void initializeCloth() 
{
	for (int i=0; i<numParticles; i++)
	{
		//initialize a new particle and add it to the vector
		Particle currParticle;
		particleVector.push_back(currParticle);
		
	}
}

int main(int argc, char *argv[])
{
	return 1;
}
