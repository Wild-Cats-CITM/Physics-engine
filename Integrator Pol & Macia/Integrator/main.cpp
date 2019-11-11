#include <iostream>

#define GRAVITY -9.8
#define MAX_FRAMES 30

//void eulerIntegrator(float* initialPos, float* initV, float initA, float deltatime);

void eulerIntegrator(float* initialPos, float* initV, float initA, float deltatime) {
	printf("InitP: %f, InitV: %f Deltatime: %f \n", *initialPos, *initV, deltatime);
	float finalVelocity;
	float finalPosition;

	//Calculate final velocity each frame
	finalVelocity = *initV + deltatime * GRAVITY;
	*initV = finalVelocity;

	//Calculate final position each frame
	finalPosition = *initialPos + deltatime * finalVelocity;
	*initialPos = finalPosition;
}


int main() {

	float pos;
	float vel;
	pos = 10.2f;
	vel = 5.1f;
	float ace = 6.3f;
	bool bucle = true;
	float deltatime = 1.0f / MAX_FRAMES;


	while (bucle != false)
	{
		//Function
		eulerIntegrator(&pos, &vel, ace, deltatime);
		printf("Pos: %f, Vel: %f\n", pos, vel);
		if (pos < 0) bucle = false;
	}
	
	system("pause");
	return 0;
}