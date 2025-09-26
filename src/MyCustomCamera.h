#pragma once
#include "ofCamera.h"
#include "ofMain.h"

class MyCustomCamera : public ofCamera {
public:
	MyCustomCamera();

	void update(float deltaTime);

	// rotated (local) axes
	glm::vec3 getqForward();
	glm::vec3 getqSide();
	glm::vec3 getqUp();

	// rotate about local axes (amount in radians)
	void pitch(float a); // rotate about local side (X) - nose up/down
	void roll(float a); // rotate about local forward (Z) - tilt
	void yaw(float a); // rotate about local up (Y) - turn left/right

private:
	float movementSpeed;
	float rotationSpeed;
	glm::vec3 position;
	glm::quat orientation;

	glm::vec3 BASE_UP;
	glm::vec3 BASE_SIDE;
	glm::vec3 BASE_FORWARD;
};
