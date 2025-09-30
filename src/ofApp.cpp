#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	/* -z is forward from camera start
	y is above camera start
	x is to the right of camera start */
	asteroids = 200;
	for (int i = 0; i < asteroids; i++)
	{
		body[i].setPosition(
			glm::vec3(
				ofRandom(-800,800),
				ofRandom(-800,800),
				ofRandom(-800,800))); // random somwhere in space
	}


	gatesPassed = 0;
	cout << gatesPassed << endl;


	ring* r;
	glm::vec3 pos;
	glm::vec3 rot;

	ofSpherePrimitive * s;

	//checkpoint 1
	pos = glm::vec3(0, 50, -400);
	rot = glm::vec3(230, 23, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(true);
	rings.push_back(r);

	//checkpoint 2
	pos = glm::vec3(400, 400, -650);
	rot = glm::vec3(100, 310, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 3
	pos = glm::vec3(360, 400, -170);
	rot = glm::vec3(200, 15, -65);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 4
	pos = glm::vec3(310, 265, 235);
	rot = glm::vec3(150, 0, -90);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 5
	pos = glm::vec3(-280, 120, 550);
	rot = glm::vec3(80, 160, 100);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 6
	pos = glm::vec3(160, -600, 320);
	rot = glm::vec3(25, 45, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//////////////////////////////////////////////

	s = new ofSpherePrimitive();
	s->setPosition(glm::vec3(-300, -200, -700));
	powerups.push_back(s);

}

//--------------------------------------------------------------
void ofApp::update() {
	cam.update(0.016); // 60 fps


	/*Shrinking and Scaling attempts right here...*/
	/*for (ofNode& asteroid : body) {
		asteroid.setScale(glm::distance(cam.getPosition(), asteroid.getPosition()) * 0.005);
	}*/


	// Ring Collision
	for (int i = 0; i < rings.size(); i++) {
		ring * r = rings[i];

		glm::vec3 playerPos = cam.getPosition();
		glm::vec3 toPlayer = playerPos - r->getPosition();

		// Step 1: distance from plane
		glm::vec3 n = r->getNormal();
		float distFromPlane = glm::dot(toPlayer, n);

		// Step 2: reject if too far from plane
		if (fabs(distFromPlane) > 20.0f) // tolerance (gate thickness)
			continue;

		// Step 3: project onto plane
		glm::vec3 proj = playerPos - distFromPlane * n;
		float distFromCentre = glm::length(proj - r->getPosition());

		// Step 4: check ring radius
		if (distFromCentre <= r->getOuterR() && r->getNext() == true) {
			gatesPassed++;
			cout << "Gate passed! Total: " << gatesPassed << endl;

			// If there’s another ring after this one, set it as the next goal
			if (i + 1 < rings.size()) {
				rings[i + 1]->setAsNext(true);
			}

			delete r;
			rings.erase(rings.begin() + i);
			break; //stops indexing out of range error
		}
	}

	// PowerUp Collision

	for (int i = 0; i < powerups.size(); i++) {
		if (glm::distance(cam.getPosition(), powerups[i]->getPosition()) < powerups[i]->getRadius()) {
			cam.setSpeed(cam.getSpeed() + 25);
			delete powerups[i];
			powerups.erase(powerups.begin() + i);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	for (int i = 0; i < asteroids; i++)
		body[i].draw();

	for (ring* ring : rings)
		ring->draw(true); //draw every created ring

	for (ofSpherePrimitive* powerup : powerups) {
		ofPushStyle();
		ofSetColor(255, 242, 59);
		powerup->draw();
		ofPopStyle();
	}

	glm::vec3 pos = cam.getPosition();
	glm::vec3 forward = cam.getqForward(); // camera's local forward (unit)
	glm::vec3 modelForward = glm::vec3(0.0f, 0.0f, -1.0f); // our cube model faces -Z by convention

	// compute axis/angle to rotate modelForward -> forward
	glm::vec3 axis = glm::cross(modelForward, forward);
	float dot = glm::dot(modelForward, forward);
	// clamp dot to [-1,1] to be numerically safe
	if (dot > 1.0f) dot = 1.0f;
	if (dot < -1.0f) dot = -1.0f;
	float angleRad = acos(dot);
	float angleDeg = glm::degrees(angleRad);

	ofPushMatrix();
	ofTranslate(pos.x, pos.y, pos.z);

	// handle nearly parallel/opposite cases robustly
	if (glm::length(axis) < 1e-6f) {
		// axis too small: either vectors are identical (no rotation)
		// or opposite (180°) — handle 180° as rotate around up-vector
		if (dot < 0.0f) {
			// rotate 180 degrees around some perpendicular axis (use world Y)
			ofRotateDeg(180.0f, 0.0f, 1.0f, 0.0f);
		}
		// else dot > 0 -> no rotation needed
	} else {
		axis = glm::normalize(axis);
		ofRotateDeg(angleDeg, axis.x, axis.y, axis.z);
	}

	// optional: apply additional roll so the cube's up aligns with camera up
	// (unnecessary for simple ship cube; skip unless you want roll alignment)

	ofSetColor(255, 150, 100);
	float cubeSize = 40.0f;
	ofDrawBox(0.0f, 0.0f, 0.0f, cubeSize); // centered cube

	ofPopMatrix();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key){ 
		case ('m'):
			cout << cam.getPosition() << endl;
		case ('n'):
			cout << cam.getOrientation() << endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

