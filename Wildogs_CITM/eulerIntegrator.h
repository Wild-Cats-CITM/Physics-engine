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
	float restitution = 1;
	int w, h;
	bool collided = false;
	bool isdynamic = true;
	bool OnFloor = false;
	WcObject* collider = NULL;
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
		acc.y = (force.y / mass);
		force.x = 0;
		force.y = 0;
		
	}

	void aerodinamics(float density, float speedx, float speedy, float groundx, float groundy, float drag, float dt) {


		if (this->speed.y < 0) {
			acc.y += 0.5 * density * (speedy * speedy) * groundy * drag * dt;
		}
		if (this->speed.y >= 0) {
			acc.y -= 0.5 * density * (speedy * speedy) * groundy * drag * dt;
		}
		if (this->speed.x < 0) {
			acc.x += 0.5 * density * (speedx * speedx) * groundx * drag * dt;
		}
		if (this->speed.x >= 0) {
			acc.x -= 0.5 * density * (speedx * speedx) * groundx * drag * dt;
		}
		
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
		//Gravity doesn't apply if on land
		finalSpeed.y = initSpeed.y + deltatime * (acc.y);
	}
		//Calculate final position each frame
		finalPosition.x = initPosition.x + finalSpeed.x*1.5;
		finalPosition.y = initPosition.y + finalSpeed.y*1.5;

		speed.x = finalSpeed.x;
		pos.x = finalPosition.x;

		speed.y = finalSpeed.y;
		pos.y = finalPosition.y;

	}
	void OnCollision(WcObject* object, char direction) {

		pos.y = initpos.y;
		pos.x = initpos.x;
		collided = true;
		switch (direction){
		case 'N':
			speed.x = (speed.x*-(mass - object->mass) + 2 * object->speed.x*object->mass) / (mass + object->mass)*restitution;
			speed.y = (speed.y*(mass - object->mass) + 2 * object->speed.y*object->mass) / (mass + object->mass)*restitution;
		
			break;
		case 'S': 
			speed.x = (speed.x*(mass - object->mass) + 2 * object->speed.x*object->mass) / (mass + object->mass)*restitution;
			speed.y = (speed.y*(mass - object->mass) + 2 * object->speed.y*object->mass) / (mass + object->mass)*restitution;
		
			break;
		case 'L':
			speed.x = (speed.x*(mass - object->mass) + 2 * object->speed.x*object->mass) / (mass + object->mass)*restitution;
			speed.y = (speed.y*(mass - object->mass) + 2 * object->speed.y*object->mass) / (mass + object->mass)*restitution;
			
			break;
		case 'R':
			speed.x = (speed.x*(mass - object->mass) + 2 * object->speed.x*object->mass) / (mass + object->mass)*restitution;
			speed.y = (speed.y*(mass - object->mass) + 2 * object->speed.y*object->mass) / (mass + object->mass)*restitution;
			
			break;
		}
		
	};

	void CheckCollision(WcObject* object1, WcObject* object2, float deltatime) {

		if (object1->pos.x == object2->pos.x && object1->pos.y == object2->pos.y || (object1->pos.x + object1->w < object2->pos.x || object1->pos.x > object2->pos.x + object2->w || object1->pos.y + object1->h < object2->pos.y || object1->pos.y > object2->pos.y + object2->h)) {

		}
		else
		{
			collider = object2;
			
			if (object1->pos.y < object2->pos.y) 
			{ //UP DOWN
				OnCollision(object2, 'N');
				if (collided && abs(speed.y) < 1.5f)
				{
					speed.y = 0;
					OnFloor = true;
				}
			}
			else if (object1->pos.y > object2->pos.y) { //DOWN UP

				OnCollision(object2, 'S');
				}
			else if (object1->pos.x < object2->pos.x) { //LEFT
				OnCollision(object2, 'L');
				}
			else if (object1->pos.x > object2->pos.y) { //RIGHT
				OnCollision(object2, 'R');
				}
			
			
		}
	}
	void AfterCollision(WcObject* object2) 
	{
		if (object2 != NULL){
		if (pos.x + w < object2->pos.x || pos.x > object2->pos.x + object2->w || pos.y + h < object2->pos.y || pos.y > object2->pos.y + object2->h) {
		if(!collided) OnFloor = false;
			}
		object2 = NULL;
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
	float drag = 0.5f;

	void DeleteObjects() {

		p2List_item<WcObject*>* item;
		item = Objects.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}
		Objects.clear();
	}

};



#endif // __EULERINTEGRATOR_H__