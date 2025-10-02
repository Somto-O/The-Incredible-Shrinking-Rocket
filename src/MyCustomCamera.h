#pragma once
#include "ofCamera.h"
#include "ofMain.h"
#include "ship.h"

class MyCustomCamera : public ofCamera {
public:
	MyCustomCamera();

	void update(const Ship& ship, float deltaTime);

	// rotated (local) axes
	//glm::vec3 getqForward();
	//glm::vec3 getqSide();
	//glm::vec3 getqUp();

	// rotate about local axes (amount in radians)
	//void pitch(float a); // rotate about local side (X) - nose up/down
	//void roll(float a); // rotate about local forward (Z) - tilt
	//void yaw(float a); // rotate about local up (Y) - turn left/right

	//setters
	//void setSpeed(float speed) { movementSpeed = speed; }
	void setFollowDistance(float dist) { followDistance = dist; }
	void setFollowHeight(float h) { followHeight = h; }

	// getters
	glm::vec3 getPosition() { return position; }
	glm::quat getOrientation() { return orientation; }
	//float getSpeed() { return movementSpeed; }

private:
	//float movementSpeed;
	//float rotationSpeed;
	glm::vec3 position;
	glm::quat orientation;

	//glm::vec3 BASE_UP;
	//glm::vec3 BASE_SIDE;
	//glm::vec3 BASE_FORWARD;
	float followDistance;
	float followHeight;
};
