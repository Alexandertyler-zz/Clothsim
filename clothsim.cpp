#include "clothsim.h"


/*NOTES FOR OTHER TEAM MEMBERS
 
 
 */

/*GLOBAL VARIABLES*/

//number of particles per side of the cloth
float particleSide = 10.0f;
int numParticles = particleSide*particleSide;
//the size of the cloth length
float clothSide = 10.0f;
glm::vec3 gravity(0, 0, 0);
float damp = .1f;
float timeStep = .5f*.5f;

std::vector<std::vector<Particle> > particleVector(particleSide);
std::vector<Constraint> constraintVector;

float structConstraint = clothSide/(particleSide-1.0f); // lizzie: the rest length between two particles (?)
float shearConstraint = sqrt(2.0f*pow(structConstraint, 2));
float bendConstraint = 2.0f*structConstraint;

Particle::Particle()
{
	return;
}

Particle::Particle(glm::vec3 _pos)
{
  	pos = _pos;
  	mass = 1.0f;
  	oldPos = _pos;
  	canMove = true;
}

//evaluate the force acting on each particle
void Particle::evalForce()
{
	//pseudocode:
	//foreach particle, add the gravity force
	//foreach triangle in the cloth plane, calculate and add the wind
	//foreach spring, calculate and add in spring force to particles
	glm::vec3 tmp;
	tmp = pos;
	pos = pos + gravity;
	//vertlet integration
	pos = (pos-oldPos)*(1.0f*damp) + accel*timeStep;
	oldPos = tmp;
}


void Particle::changePos(glm::vec3 p)
{
	if(canMove){
		pos += p;
	}
    
}




//we should do an evalForce function in each class for the different objects. Makes it
//more specialized that way.


Sphere::Sphere()
{
	
}



Constraint::Constraint()
{
	
}

//creates a constraint between particle 1 and particle 2
Constraint::Constraint(Particle _part1, Particle _part2) : part1(_part1), part2(_part2)
{
    
	// getting the position vector from particle 1's pos - particle 2's pos
	glm::vec3 v = part1.pos - part2.pos;
	//getting the length of the vector
	float dist = glm::length(v);
	//setting the structural distance / resting length of the 2 particles
	structDistance = dist;
    
}

//Ensures that the structural constraint is satisfied.
void Constraint::evalConstraint()
{
	//getting the vector from particle1 to particle2
	glm::vec3 vec12 = part2.pos - part1.pos;
	//the distance between particle1 and particle2
	float dist = glm::length(vec12);
	//getting the difference between the particle1's distance from particle2, with the structConstraint/resting distance.
	glm::vec3 structDifference = vec12 * (1 - structDistance/dist);
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


ParticleSystem::ParticleSystem()
{
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
		for(int i=0; i < particleSide; i++)
		{
			for(int j=0; j < particleSide; j++)
			{
				Particle p1, p2;
				p1 = particleVector[i][j];
				if(j != particleSide-1)
				{
					p2 = particleVector[i+1][j];
					newConstraint(p1, p2);
				} else {

				}
			}
		}
		//struct loop
		//bend loop
		//shear loop
	}
	return;
}




ParticleSystem initializeVerticalCloth(){
	ParticleSystem cloth;
	for (int y = 0; y < particleSide; y++)
	{
		for (int x = 0; x < particleSide; x++) {
			//initialize a new particle and add it to the vector	
			glm::vec3 particlePos = glm::vec3(clothSide/((float) (particleSide - 1)) * x,
				-clothSide/((float) (particleSide - 1)) * y,
				0);
			Particle currParticle(particlePos);
			particleVector[x].push_back(currParticle);
			cloth.sysPartCount += 1;
		}
	}
}

ParticleSystem initializeHorizCloth(){
	ParticleSystem cloth;
	for (int z = 0; z < particleSide; z++)
	{
		for (int x = 0; x < particleSide; x++) {
			//now, the y position of the cloth does not change, since it's horizontal
			glm::vec3 particlePos = glm::vec3(clothSide/((float) (particleSide - 1)) * x,
				0,
				-clothSide/((float) (particleSide - 1)) * z);
			Particle currParticle(particlePos);
			particleVector[x].push_back(currParticle);
			cloth.sysPartCount += 1;
		}
	}
}


//Gets the normal of the triangle created by three particles PART1, PART2, PART3
glm::vec3 getTriangleNormal(Particle part1, Particle part2, Particle part3) {
	glm::vec3 v12 = part2.pos - part1.pos;
	glm::vec3 v13 = part3.pos - part1.pos;
	glm::vec3 crossProd = glm::cross(v12, v13);
	return crossProd;
    
}

void newConstraint(Particle part1, Particle part2)
{
	Constraint constraint(part1, part2);
	constraintVector.push_back(constraint);
}




/*Kristin: NEED TO MOVE FUNCTION WHERE CAN ACCESS PARTICLE POSITIONS
 POSSIBLY PUT IN PARTICLE CLASS AND CALL FROM EVALCONSTRAINT ON BOTH PARTICLES?
 void sphereCollision () {
 //if distance from point to origin of sphere less than radius 2
 if (sqrt( sqr(pos.x) + sqr(pos.y) + sqr(pos.z) ) < 2) {
 pos = glm::normalize(pos) * 2; //push position to surface of sphere (if change radius, change 2 to new radius value here)
 }
 }
 */




//FUNCTIONS TO CREATE WINDOW AND RENDER SCENE//

class Viewport {
public:
    int w, h; // width and height
};

Viewport viewport;

void initScene(){
    
    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
}

void myReshape(int w, int h) {
    viewport.w = w;
    viewport.h = h;
    
    glViewport (0,0,viewport.w,viewport.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, 5, -5);
    
}

void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0, 0, 5,  //look from 0, 0, 5 (along z axis)
              0, 0, 0,  //look at origin
              0, 1, 0); //y up vector
    
    glutSolidSphere(2, 25, 25); //sphere with center at origin, radius 2
    
    glFlush();
    glutSwapBuffers();
    
}


//CLOSE WINDOW WITH SPACEBAR//
void idleInput (unsigned char key, int xmouse, int ymouse) {
    switch (key)
    {
        case ' ':
            exit(0);
        default:
            break;
    }
}




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    
	ParticleSystem cloth;
	cloth = initializeVerticalCloth();
	cloth.initializeConstraints();
	//timeloop
	//evalforce
	//for #of evals:
    //eval
    //spherecollision
    
    
    //CREATE WINDOW AND DRAW SCENE
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Initalize theviewport size
    viewport.w = 400;
    viewport.h = 400;
    glutInitWindowSize(viewport.w, viewport.h);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cloth Simulation");
    
    initScene();
    
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(idleInput);
    glutMainLoop();
    
	
	return 1;
}
