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

	started = false; //determines if the player has through the first gate


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
	pos = glm::vec3(-300, -400, 550);
	rot = glm::vec3(100, 70, 60);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 7
	pos = glm::vec3(160, -600, 320);
	rot = glm::vec3(125, 45, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 8
	pos = glm::vec3(500, -300, 50);
	rot = glm::vec3(70, 50, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//checkpoint 9
	pos = glm::vec3(175, -160, -75);
	rot = glm::vec3(100, 70, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);


	//checkpoint 10
	pos = glm::vec3(0, 0, -150);
	rot = glm::vec3(0, 0, 0);
	r = new ring(75.0f, 5.0f, 100, 100, pos, rot);
	r->setAsNext(false);
	rings.push_back(r);

	//////////////////////////////////////////////

	//placed near checkpoint 1
	s = new ofSpherePrimitive();
	s->setPosition(glm::vec3(-100, -50, -300));
	powerups.push_back(s);

	//placed near checkpoint 3
	s = new ofSpherePrimitive();
	s->setPosition(glm::vec3(300, 450, -200));
	powerups.push_back(s);

	//placed near checkpoint 5
	s = new ofSpherePrimitive();
	s->setPosition(glm::vec3(-300, 100, 600));
	powerups.push_back(s);

	//placed near checkpoint 7
	s = new ofSpherePrimitive();
	s->setPosition(glm::vec3(100, -550, 275));
	powerups.push_back(s);

}

//--------------------------------------------------------------
void ofApp::update() {
	cam.update(0.016); // 60 fps //120fps on my pc

	if (started)
		timeElapsed += 0.008;


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
			started = true;
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

	if (rings.size() == 0 && started == true) {
		started = false; //race has finished
		cout << "Race Finished!!! Here is your time: " << timeElapsed << " seconds" << endl;
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

