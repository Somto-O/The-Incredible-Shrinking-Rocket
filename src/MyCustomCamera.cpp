#include "MyCustomCamera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> // allows quat * vec3

MyCustomCamera::MyCustomCamera() {
	movementSpeed = 75.0f; // units per second
	rotationSpeed = 0.75f; // radians per second (set to a reasonable value)
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // identity quaternion (w,x,y,z)

	// Base axes (local model axes before orientation)
	BASE_SIDE = glm::vec3(1.0f, 0.0f, 0.0f); // +X
	BASE_UP = glm::vec3(0.0f, 1.0f, 0.0f); // +Y
	BASE_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f); // -Z (forward according to right hand rule)

	// initialize ofCamera with our starting transform
	setPosition(position);
	setOrientation(orientation);
}

void MyCustomCamera::update(float deltaTime) {
	glm::vec3 move(0.0f);

	// WASD movement relative to the camera's local axes
	if (ofGetKeyPressed('w')) move += getqForward();
	if (ofGetKeyPressed('s')) move -= getqForward();
	if (ofGetKeyPressed('a')) move -= getqSide();
	if (ofGetKeyPressed('d')) move += getqSide();
	if (ofGetKeyPressed('e')) move += getqUp();
	if (ofGetKeyPressed('q')) move -= getqUp();

	if (glm::length(move) > 0.0f) {
		move = glm::normalize(move) * movementSpeed * deltaTime;
		position += move;
	}

	float rotationamt = rotationSpeed * deltaTime;

	// IJKL rotation
	if (ofGetKeyPressed('i')) pitch(rotationamt);
	if (ofGetKeyPressed('k')) pitch(-rotationamt);
	if (ofGetKeyPressed('j')) yaw(rotationamt);
	if (ofGetKeyPressed('l')) yaw(-rotationamt);
	if (ofGetKeyPressed('o')) roll(rotationamt);
	if (ofGetKeyPressed('u')) roll(-rotationamt);

	// normalize quaternion (avoid drift)
	orientation = glm::normalize(orientation);

	// publish to ofCamera (OF versions that include glm support accept glm::quat)
	setPosition(position);
	setOrientation(orientation);
}

// Rotate around local side (X)
void MyCustomCamera::pitch(float amt) {
	// axis in world coordinates = current local side vector
	glm::vec3 axis = getqSide();
	glm::quat change = glm::angleAxis(amt, glm::normalize(axis));
	orientation = glm::normalize(change * orientation);
}

// Rotate around local up (Y)
void MyCustomCamera::yaw(float amt) {
	glm::vec3 axis = getqUp();
	glm::quat change = glm::angleAxis(amt, glm::normalize(axis));
	orientation = glm::normalize(change * orientation);
}

// Rotate around local forward (Z)
void MyCustomCamera::roll(float amt) {
	glm::vec3 axis = getqForward();
	glm::quat change = glm::angleAxis(amt, glm::normalize(axis));
	orientation = glm::normalize(change * orientation);
}

// local forward (rotated base forward)
glm::vec3 MyCustomCamera::getqForward() {
	glm::vec3 f = orientation * BASE_FORWARD; // rotate base by quaternion
	return glm::normalize(f);
}

// local right/side
glm::vec3 MyCustomCamera::getqSide() {
	glm::vec3 s = orientation * BASE_SIDE;
	return glm::normalize(s);
}

// local up
glm::vec3 MyCustomCamera::getqUp() {
	glm::vec3 u = orientation * BASE_UP;
	return glm::normalize(u);
}
