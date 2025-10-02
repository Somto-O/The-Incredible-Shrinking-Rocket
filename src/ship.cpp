#include "Ship.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Ship::Ship() {
	position = glm::vec3(0, 0, 0);
	orientation = glm::quat(1, 0, 0, 0);

	movementSpeed = 300.0f; // tune as needed
	rotationSpeed = 1.0f;

	BASE_FORWARD = glm::vec3(0, 0, -1);
	BASE_UP = glm::vec3(0, 1, 0);
	BASE_SIDE = glm::vec3(1, 0, 0);
}

void Ship::update(float deltaTime) {
	glm::vec3 move(0);

	if (ofGetKeyPressed('w')) move += getForward();
	if (ofGetKeyPressed('s')) move -= getForward();
	if (ofGetKeyPressed('a')) move -= getSide();
	if (ofGetKeyPressed('d')) move += getSide();
	if (ofGetKeyPressed('q')) move += getUp();
	if (ofGetKeyPressed('e')) move -= getUp();

	if (glm::length(move) > 0.0f) {
		move = glm::normalize(move) * movementSpeed * deltaTime;
		position += move;
	}

	float rot = rotationSpeed * deltaTime;

	if (ofGetKeyPressed('i')) pitch(rot);
	if (ofGetKeyPressed('k')) pitch(-rot);
	if (ofGetKeyPressed('j')) yaw(rot);
	if (ofGetKeyPressed('l')) yaw(-rot);
	if (ofGetKeyPressed('u')) roll(-rot);
	if (ofGetKeyPressed('o')) roll(rot);

	orientation = glm::normalize(orientation);
}

glm::vec3 Ship::getForward() const {
	return glm::normalize(orientation * BASE_FORWARD);
}

glm::vec3 Ship::getUp() const {
	return glm::normalize(orientation * BASE_UP);
}

glm::vec3 Ship::getSide() const {
	return glm::normalize(orientation * BASE_SIDE);
}

float Ship::getSpeed() const {
	return movementSpeed;
}

void Ship::setSpeed(float speed) {
	movementSpeed = speed;
}

void Ship::moveForward(float amt) { position += getForward() * amt; }
void Ship::moveRight(float amt) { position += getSide() * amt; }
void Ship::moveUp(float amt) { position += getUp() * amt; }

void Ship::pitch(float amt) {
	glm::quat q = glm::angleAxis(amt, getSide());
	orientation = glm::normalize(q * orientation);
}

void Ship::yaw(float amt) {
	glm::quat q = glm::angleAxis(amt, getUp());
	orientation = glm::normalize(q * orientation);
}

void Ship::roll(float amt) {
	glm::quat q = glm::angleAxis(amt, getForward());
	orientation = glm::normalize(q * orientation);
}

void Ship::draw() {
	ofPushMatrix();
	ofPushStyle();

	ofTranslate(position);

	// apply orientation
	glm::mat4 m = glm::toMat4(orientation);
	ofMultMatrix(ofMatrix4x4(m));

	ofSetColor(255, 100, 100);
	ofDrawBox(0, 0, 0, 40); // placeholder cube

	ofPopStyle();
	ofPopMatrix();
}
