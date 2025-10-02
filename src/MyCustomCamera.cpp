#include "MyCustomCamera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> // allows quat * vec3

MyCustomCamera::MyCustomCamera() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // identity quaternion (w,x,y,z)

	followDistance = 200.0f;
	followHeight = 80.0f;
}

void MyCustomCamera::update(const Ship& ship, float deltaTime) {

	glm::vec3 shipForward = ship.getForward();
	glm::vec3 shipUp = ship.getUp();
	glm::vec3 shipPos = ship.getPosition();

	// Offset behind and above the ship
	glm::vec3 camPos = shipPos - shipForward * followDistance + shipUp * followHeight;

	// Update camera transform
	setPosition(camPos);

	// Look at the ship’s position, but keep camera upright by using world-up (0,1,0)
	// If you want slight banking, you could use shipUp instead.
	lookAt(shipPos, shipUp);

	position = camPos;
	orientation = ship.getOrientation();
}

