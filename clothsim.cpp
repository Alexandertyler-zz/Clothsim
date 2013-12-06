#include "clothsim.h"


/*NOTES FOR OTHER TEAM MEMBERS


*/

/*GLOBAL VARIABLES*/


std::vector<Particle> particleVector;

float particleSide = 10.0f;
int numParticles = particleSide*particleSide;
float clothSide = 10.0f;
glm::vec3 gravity(0, 0, 0);
float damp = .1f;
float timeStep = .5f*.5f;

float structConstraint = clothSide/(particleSide-1.0f); // lizzie: the rest length between two particles (?)
float shearConstraint = sqrt(2.0f*pow(structConstraint, 2));
float bendConstraint = 2.0f*structConstraint;

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


void Particle::changePos(glm::vec3 p)
{
	if(canMove){
		pos += p;
	}

}

ParticleSystem::ParticleSystem()
{
	//clear the vector because we are making a new system
	particleVector.clear();
	return;
}

void ParticleSystem::addParticle(Particle part)
{
	particleVector.push_back(part);
	sysPartCount += 1;
	return;
}

//Use this when system is full to initialize all constraints
void ParticleSystem::initializeConstraints()
{
	if(sysPartCount != numParticles)
	{
		std::cerr << "Particle System count is diff from global count." << std::endl;
	}
	else 
	{
		//for i, j make constraint(particleVector(i), (j));
	}
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

//Lizzie: should we be passing in pointers *part1 and *part2? not sure...
void Constraint::makeConstraint(Particle part1, Particle part2)
{

	// getting the position vector from particle 1's pos - particle 2's pos
	glm::vec3 v = part1.pos - part2.pos;
	//float length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); //geting the length of the vector
	//getting the length of the vector
	float dist = glm::length(v);
	//setting the structural constraing / resting length of the 2 particles
	structConstraint = dist;
}

//Ensures that the structural constraint is satisfied.
void Constraint::evalConstraint()
{
	//getting the vector from particle1 to particle2
	glm::vec3 vec12 = part2.pos - part1.pos;
	//the distance between particle1 and particle2
	float dist = glm::length(vec12); 
	//getting the difference between the particle1's distance from particle2, with the structConstraint/resting distance.
	glm::vec3 structDifference = vec12 * (1 - structConstraint/dist);
	glm::vec3 shearDifference = vec12 * (1 - shearConstraint/dist); //? do we need to do these?
	glm::vec3 bendDifference = vec12 * (1 - bendConstraint/dist); //?
	//The distance each particle must move to satisfy the the structConstraint length:
	glm::vec3 distToMove = (structDifference/2.0f);
	//Moving particle1's position to the correct resting length, structConstraint
	part1.changePos(distToMove);
	//Moving particle2's position to the correct resting length, but in the NEGATIVE direction
	part2.changePos(-distToMove);

}



/* NOTES/THINGS TO CONSIDER

- for the particle numerical integration, we were thinking about doing either Euler or Verlet,
though verlet seems more desirable.
- should we be thinking about the optimal number of particles?  -> right now,
we're thinking about going with having a system that can work with an number of particles
(will use an integer variable, numParticles)


*/

void initializeCloth(){
	for (int i=0; i < numParticles; i++)
	{
		//initialize a new particle and add it to the vector	
		Particle currParticle;
		particleVector.push_back(currParticle);
		
	}
}

int main(int argc, char *argv[])
{
	ParticleSystem cloth;
	//loop for particles
	for(int i=0; i < numParticles; i++)
	{
		//Particle part(mass, pos);
		//cloth.addParticle(part);
		
	}
	cloth.initializeConstraints();
	//timeloop
	//evalforce
	//for #of evals:
		//eval
		//spherecollision
	
	return 1;
}
