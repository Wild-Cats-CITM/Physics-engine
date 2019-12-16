#ifndef __EULERINTEGRATOR_H__
#define __EULERINTEGRATOR_H__

#define GRAVITY 9.8f
#define WATERDENSITY 1
#define AIRDENSITY 0.01f
#define LAVADENSITY 3.2f
#define SPACEDENSITY 0
/*#define AIRDRAG 
#define WATERDRAG 
#define LAVADRAG */
#define SPACEDRAG 0

#include <math.h>
#include <cmath> 
#include "p2Point.h"
#include "p2List.h"

typedef unsigned int uint;

//Object class, which will do all the physical calculations
class WcObject
{
private:

	
public:

	float mass;
	fPoint speed;
	fPoint acc;
	fPoint force;
	fPoint pos; 
	fPoint initpos;
	float restitution;
	int w, h;
	bool collided;
	bool isdynamic;
	bool OnFloor;
	WcObject* collider;
	public:
	 
	//Constructor
	WcObject();
	//Overload
	WcObject(float Weight, fPoint Position, int width, int height);

	~WcObject();

	//Functions
	//Receive a vector and updates object force
	void AddForce(iPoint vec);

	//Updates acceleration
	void updateAcc();

	//Modifies acceleration depending on the objects current speed, the ambient's density, the surface of the object and the drag
	//Basically changes acceleration depending of the fluid the object is travelling through
	void aerodinamics(float density, float speedx, float speedy, float groundx, float groundy, float coefAero, float dt);

	//Integrates euler formula, using acceleration, initial position and speed and a deltatime
	void eulerIntegrator(float deltatime);

	//Cheks if there was a collision between two objects in this world
	void CheckCollision(WcObject* object1, WcObject* object2, float deltatime);

	//When an object collides, this method is called, and it receives a speed ,according to the masses and speeds of the colliding objects
	//The object returns to it's previous position before the collision even happened, so we can avoid overlapping
	void OnCollision(WcObject* object, char direction);

	//if the collision ended, free the stored object, and resets OnFloor bool which will allow gravity to act upon this object once again
	void AfterCollision(WcObject* object2);
};

//World class, which will mainly store all objects
class WcWorld {

public:
	p2List<WcObject*> Objects;
	WcWorld();

	~WcWorld();

	//Cals object constructor and stores it's pointer in a list
	WcObject* AddObject(float Weight, fPoint Position, int width, int height);

	//Aerodinamics values, dependant of the world
	float density;
	float coefAero;

	//This is called on world destructor, which will free all objects in memory or cazn be called to delete all current objects
	void DeleteObjects();
};



#endif // __EULERINTEGRATOR_H__