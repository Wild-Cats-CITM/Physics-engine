#ifndef __EULERINTEGRATOR_H__
#define __EULERINTEGRATOR_H__

#define GRAVITY 9.8f

#include <math.h>
#include "p2Point.h"
#include "p2List.h"

typedef unsigned int uint;


class WcObject
{
private:

	float mass;
	iPoint speed;
	iPoint acc;
	iPoint force;
	
public:
	iPoint pos; 
	uint w, h;

	public:
	 
	//Constructor
	WcObject() {
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
	WcObject(float Weight, iPoint Position, uint width, uint height) {
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

	~WcObject(){}


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

class WcWorld {
private:

	

public:
	p2List<WcObject*> Objects;
	WcWorld() {

	}

	~WcWorld() {
		DeleteObjects();
	}

	WcObject* AddObject(float Weight, iPoint Position, uint width, uint height) {
		WcObject* set = new WcObject( Weight, Position , width,  height);
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