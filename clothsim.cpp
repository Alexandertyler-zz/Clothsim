#include "clothsim.h"
/*NOTES FOR OTHER TEAM MEMBERS
	1. Need to move shit to a header.

*/

/*GLOBAL VARIABLES*/
std::vector<Particle> particleVector;

Particle(){
	return;
}

Particle(float _mass, vector<float> _pos, vector<float> _velocity) {
  	mass = _mass;
  	pos = _pos;
  	vel = _velocity; //velocity will not be needed if we go with Verlet integration
}

ParticleSystem()
{
	return;
}

//we should do an evalForce function in each class for the different objects. Makes it 
//more specialized that way.




//evaluate the force acting on each particle
void evalForce(){
	//pseudocode:
	
	

	//foreach particle, add the gravity force
	//foreach triangle in the cloth plane, calculate and add the wind
	//foreach spring, calculate and add in spring force to particles

}

class Sphere
{

};
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
		Particle currParticle();
		particleVector.push_back(currParticle);
		
		

}
