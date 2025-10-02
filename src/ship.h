#pragma once
#include "ofMain.h"

class Ship {
public:
	Ship();

	void update(float deltaTime);

	// getters
	glm::vec3 getPosition() const { return position; }
	glm::quat getOrientation() const { return orientation; }
	glm::vec3 getForward() const;
	glm::vec3 getUp() const;
	glm::vec3 getSide() const;
	float getSpeed() const;
	float getEffectiveSpeed() const;
	float getScale() const { return scale; }

	// setter
	void setSpeed(float speed);

	// movement + rotation
	void moveForward(float amt);
	void moveRight(float amt);
	void moveUp(float amt);

	void pitch(float amt); // nose up/down
	void yaw(float amt); // turn left/right
	void roll(float amt); // bank left/right

	// draw the ship
	void draw();

	void grow(float factor);
	void shrink(float factor);

private:
	glm::vec3 position;
	glm::quat orientation;

	float movementSpeed;
	float rotationSpeed;

	float currentSpeed;
	float maxSpeed;
	float accelRate;
	float decelRate;

	// base axes
	glm::vec3 BASE_FORWARD;
	glm::vec3 BASE_UP;
	glm::vec3 BASE_SIDE;

	float scale;
};
