#ifndef __EULERINTEGRATOR_H__
#define __EULERINTEGRATOR_H__

#define GRAVITY 9.8f

#include <math.h>
#include "p2Point.h"
#include "p2List.h"

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
	Object(float Weight, iPoint Position, uint width, uint height) {
		mass = Weight;
		speed.x = .0f;
		speed.y = .0f;
		acc.x = .0f;
		acc.y = .0f;
		force.x = .0f;
		force.y = .0f;
		pos.x = Position.x;
		pos.y = Position.y;
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

class World {
private:

	p2List<Object*> Objects;

public:

	World() {

	}

	~World() {
		DeleteObjects();
	}

	Object* AddObject(float Weight, iPoint Position, uint width, uint height) {
		Object* set = new Object( Weight, Position , width,  height);
		Objects.add(set);
		return set;
	}

	void DeleteObjects() {

		/*p2List_item<Object*> item;
		item = data.Objects.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}*/
	}

};



#endif // __EULERINTEGRATOR_H__