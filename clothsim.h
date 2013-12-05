#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "glm.hpp"

#include <sys/time.h>

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <stdexcept>
#include <time.h>
#include <math.h>

/** Particle class definition. Defines a particle with a mass, position, and velocity attributes. */
class Particle
{
public:
	//Particle constructor:
	Particle();
	Particle(float _mass, glm::vec3 _pos);
	void evalForce(glm::vec3 _force);

private:
	bool canMove;
	float mass;
	glm::vec3  pos, oldPos, vel, accel;
	
};

/** Particle system, sets up system of particle linking. */
//cloth

class ParticleSystem
{
public:
	ParticleSystem();
	
	//we should add the particles into a vector when we initialize them. Because
	//we only have one object utilizing this vector, it shouldn't be a problem.
	//somehow, set up linking system: iterate through all particles, and link them.
	//THINK ABOUT HOW TO DO LINKING SYSTEM???
private:
	int numParticles;
};


class Sphere
{
	Sphere();
};


class Constraint
{
public:
	void makeConstraint(Particle part1, Particle part2);
	void evalConstraint();	
	
private:
	Particle part1, part2;
	
};




//Functions
void initializeCloth();
