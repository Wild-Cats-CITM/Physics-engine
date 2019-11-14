#ifndef __EULERINTEGRATOR_H__
#define __EULERINTEGRATOR_H__

#define GRAVITY 9.8f

#include <math.h>
#include "p2Point.h"

typedef unsigned int uint;


class Object
{
private:

	float mass;
	iPoint pos;
	iPoint speed;
	iPoint acc;
	iPoint force;
	uint w, h;

	public:
	 
	//Constructor
	Object() {
		mass = .0f;
		speed.x = .0f;
		speed.y = .0f;
		acc.x = .0f;
		acc.y = .0f;
		force.x = .0f;
		force.y = .0f;
		w = 0;
		h = 0;
	}

	//Overload
	Object(float Weight, iPoint Position, iPoint Vel, iPoint Acceleration, iPoint Force, uint width, uint height) {
		mass = Weight;
		speed.x = Vel.x;
		speed.y = Vel.y;
		acc.x = Acceleration.x;
		acc.y = Acceleration.y;
		force.x = Force.x;
		force.y = Force.y;
		w = width;
		h = height;
	}

	~Object(){}


	//Functions
	void updateAcc() {
		acc.x = force.x / mass;
		acc.y = (force.y / mass) + GRAVITY;
	}

	void eulerIntegrator(float deltatime) {

		iPoint finalSpeed;
		iPoint finalPosition;
		
		iPoint initSpeed;
		iPoint initPosition;

		initSpeed.x = speed.x;
		initSpeed.y = speed.y;

		initPosition.x = pos.x;
		initPosition.y = pos.y;

	
		//Calculate final speed each frame
		finalSpeed.x = initSpeed.x + deltatime * acc.x;
		finalSpeed.y = initSpeed.y + deltatime * (acc.y + GRAVITY);

		//Calculate final position each frame
		finalPosition.x = initPosition.x + deltatime * finalSpeed.x;
		finalPosition.y = initPosition.y + deltatime * finalSpeed.y;

		speed.x = finalSpeed.x;
		pos.x = finalPosition.x;

		speed.y = finalSpeed.y;
		pos.y = finalPosition.y;

	}
};

#endif // __EULERINTEGRATOR_H__