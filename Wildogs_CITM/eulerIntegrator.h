#ifndef __EULERINTEGRATOR_H__
#define __EULERINTEGRATOR_H__

#define GRAVITY 9.8f
#define WATERDENSITY 1
#define AIRDENSITY 1.2f
#define LAVADENSITY 3.1f

#include <math.h>
#include <cmath> 
#include "p2Point.h"
#include "p2List.h"

typedef unsigned int uint;


class WcObject
{
private:

	
public:

	float mass;
	fPoint speed;
	fPoint acc;
	fPoint force;

	fPoint pos; 
	float restitution = 0.5;
	int w, h;
	bool collided = false;
	bool isdynamic = true;
	bool OnFloor = false;

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
		pos.x = .0f;
		pos.y = .0f;
		w = 0;
		h = 0;
	}

	//Overload
	WcObject(float Weight, fPoint Position, int width, int height) {
		mass = Weight;
		speed.x = .0f;
		speed.y = .0f;
		acc.x = .0f;
		acc.y = 9.8f;
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
		acc.y = force.y / mass;
		force.x = 0;
		force.y = 0;
		
	}

	float aerodinamics(float density, float speed, float ground, float drag) {

		float ret = 0.5 * density * (speed * speed) * ground * drag;

		return ret;
	}

	void eulerIntegrator(float deltatime) {

		fPoint finalSpeed;
		fPoint finalPosition;
		
		fPoint initSpeed;
		fPoint initPosition;

		initSpeed.x = speed.x;
		initSpeed.y = speed.y;

		initPosition.x = pos.x;
		initPosition.y = pos.y;

	
		//Calculate final speed each frame
		finalSpeed.x = initSpeed.x + deltatime * acc.x;
	if(!OnFloor)	finalSpeed.y = initSpeed.y + deltatime * (acc.y + GRAVITY);
	else {
		finalSpeed.y = 0;
	}
		//Calculate final position each frame
		finalPosition.x = initPosition.x + finalSpeed.x*2;
		finalPosition.y = initPosition.y + finalSpeed.y*2;

		speed.x = finalSpeed.x;
		pos.x = finalPosition.x;

		speed.y = finalSpeed.y;
		pos.y = finalPosition.y;

	}
	void OnCollision(WcObject* object) {
		LOG("%f", speed.y);
		object->speed.x = -object->speed.x * restitution;
		object->speed.y = -object->speed.y * restitution;
	};
	void CheckCollision(WcObject* object1, WcObject* object2, float deltatime) {

		if (object1->pos.x == object2->pos.x && object1->pos.y == object2->pos.y || (object1->pos.x + object1->w < object2->pos.x || object1->pos.x > object2->pos.x + object2->w || object1->pos.y + object1->h < object2->pos.y || object1->pos.y > object2->pos.y + object2->h)) {
			collided = false;
		//	
		}
		else
		{
			if(!collided)
			{
				OnFloor = false;
			collided = true;
			if (object1->pos.y < object2->pos.y) { //UP DOWN
				OnCollision(object1);
				}
			else if (object1->pos.y > object2->pos.y) { //DOWN UP
				OnCollision(object1);
				}
			else if (object1->pos.x < object2->pos.x) { //LEFT
				OnCollision(object1);
				}
			else if (object1->pos.x > object2->pos.y) { //RIGHT
				OnCollision(object1);
				}
			}
			if (collided && abs(speed.y)< 1.5f) 
			{
				OnFloor = true;
			}
		}
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

	WcObject* AddObject(float Weight, fPoint Position, int width, int height) {
		WcObject* set = new WcObject( Weight, Position , width,  height);
		Objects.add(set);
		return set;
	}

	float density;
	float drag = 0;

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