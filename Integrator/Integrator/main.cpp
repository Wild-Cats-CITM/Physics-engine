#include <iostream>

#define GRAVITY -10
#define MAX_FRAMES 30

//void eulerIntegrator(float* initialPos, float* initV, float initA, float deltatime);

void eulerIntegrator(float& posx, float& posy, float& velx, float& vely, float accx, float accy, float deltatime) {
	
	float finalVelocityx;
	float finalVelocityy;

	float finalPositionx;
	float finalPositiony;

	float initVx = velx;
	float initVy = vely;
	float initialPosx = posx;
	float initialPosy = posy;

	//Calculate final velocity each frame
	finalVelocityx = initVx + deltatime * accx;
	finalVelocityy = initVy + deltatime * (accy + GRAVITY);

	//finalVelocityx = initVx + deltatime * GRAVITY;
	//finalVelocityy = initVy + deltatime * GRAVITY;

	//Calculate final position each frame
	finalPositionx = initialPosx + deltatime * finalVelocityx;
	finalPositiony = initialPosy + deltatime * finalVelocityy;

	velx = finalVelocityx;
	posx = finalPositionx;

	vely = finalVelocityy;
	posy = finalPositiony;
	
}


int main() {

	float posx = 0.0f;
	float posy = 0.0f;

	float velx = 20.0f;
	float vely = 10.0f;
	
	float acex = 6.3f;
	float acey = 9.814f;
	bool bucle = true;
	float deltatime = 1.0 / 30;


	while (posx >= 0)
	{
		//Function
		eulerIntegrator(posx, posy, velx, vely, acex, acey, deltatime);
	
		printf("PosX: %f, VelX: %f\n PosY: %f, VelY: %f\n ", posx, velx, posy, vely);
	
	}
	system("pause");
	return 0;
}