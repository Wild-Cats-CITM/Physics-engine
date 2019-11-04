#include <iostream>

#define GRAVITY -10
#define MAX_FRAMES 30

//void eulerIntegrator(float* initialPos, float* initV, float initA, float deltatime);

void eulerIntegrator(float& pos, float& vel, float acc, float deltatime) {
	
	float finalVelocity;
	float finalPosition;
	float initV = vel;
	float initialPos = pos;


	//Calculate final velocity each frame
	finalVelocity = initV + deltatime * GRAVITY;
	

	//Calculate final position each frame
	finalPosition = initialPos + deltatime * finalVelocity;

	vel = finalVelocity;
	pos = finalPosition;
	
}


int main() {

	float pos = 0.0f;
	float vel = 20.0f;
	
	float ace = 6.3f;
	bool bucle = true;
	float deltatime = 1.0 / 30;


	while (pos >= 0)
	{
		//Function
		eulerIntegrator(pos, vel, ace, deltatime);
	
		printf("Pos: %f, Vel: %f\n", pos, vel);
	
	}
	system("pause");
	return 0;
}