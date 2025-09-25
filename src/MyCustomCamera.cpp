#include "MyCustomCamera.h"
#include "ofMain.h"
#include <glm/gtc/quaternion.hpp>


MyCustomCamera::MyCustomCamera() {
    movementSpeed = 50.0f; // units per second
    rotationSpeed = 0.05f;   // rads per second
    position = glm::vec3(0, 0, 0);
    orientation = glm::quat(1, 0, 0, 0); // nothing

    BASE_SIDE = glm::vec3(1, 0, 0);
    BASE_UP = glm::vec3(0, 1, 0);
    BASE_FORWARD = glm::vec3(0, 0, 1); // don't need to store all three, note
}

void MyCustomCamera::update(float deltaTime) {
    glm::vec3 move(0.0f);

    // WASD movement
    if (ofGetKeyPressed('w')) move += getqForward();
    if (ofGetKeyPressed('s')) move -= getqForward();
    if (ofGetKeyPressed('a')) move -= getqSide();
    if (ofGetKeyPressed('d')) move += getqSide();
    if (ofGetKeyPressed('q')) move += getqUp();
    if (ofGetKeyPressed('e')) move -= getqUp();

    if (glm::length(move) > 0.0f)  // did it move at all?
    {
        move = glm::normalize(move) * movementSpeed * deltaTime;
        position = position + move;
    }

    float rotationamt = rotationSpeed * deltaTime;

    // IJKL rotation
    if (ofGetKeyPressed('i')) pitch(rotationamt);
    if (ofGetKeyPressed('k')) pitch(-rotationamt);
    if (ofGetKeyPressed('j')) yaw(rotationamt);
    if (ofGetKeyPressed('l')) yaw(-rotationamt);
    if (ofGetKeyPressed('u')) roll(rotationamt);
    if (ofGetKeyPressed('o')) roll(-rotationamt);
    orientation = orientation / length(orientation); // normalize

    // need to set ofCamera parameters using internal position, orientation
    setPosition(position);
    setOrientation(orientation);

}

// TODO: getqForward, getqSide, getqUp;
// TODO: pitch, yaw, roll

void MyCustomCamera::pitch(float amt) {
    glm::quat change = glm::angleAxis(amt, glm::vec3(0,1,0));
    orientation = change*orientation;

}


void MyCustomCamera::yaw(float amt) {
    glm::vec3 silly = glm::vec3(ofRandom(10), ofRandom(10), ofRandom(10));
    glm::quat change = glm::angleAxis(amt, silly);
    orientation = orientation*change;
    
}


void MyCustomCamera::roll(float amt) {
    glm::vec3 silly = glm::vec3(ofRandom(10), ofRandom(10), ofRandom(10));
    glm::quat change = glm::angleAxis(amt, silly);
    orientation = change;
}

glm::vec3 MyCustomCamera::getqForward() {


    return ((-BASE_FORWARD)); // because we look down -z axis
}


glm::vec3 MyCustomCamera::getqSide() {

    return BASE_SIDE;
}


glm::vec3 MyCustomCamera::getqUp() {

    return BASE_UP;
}

