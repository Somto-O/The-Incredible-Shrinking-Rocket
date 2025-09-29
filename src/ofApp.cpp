#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
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

	//ring* ring1 = new ring(100.0f, 5.0f, 50, 50, glm::vec3(0, 200, 0)); //thin ring to make as a gate for checkpoints
	//rings.push_back(ring1);

	//ring * ring2 = new ring(100.0f, 5.0f, 50, 50, glm::vec3(100, 100, 0));
	//rings.push_back(ring2);

	for (int i = 0; i < 10; i++) {
		glm::vec3 pos = glm::vec3(ofRandom(-800, 800),
			ofRandom(-600, 600),
			ofRandom(-600, 600));

		glm::vec3 rot = glm::vec3(ofRandom(0, 360),
			ofRandom(0, 360),
			ofRandom(0, 360)); // random orientation

		ring * r = new ring(100.0f, 15.0f, 100, 100, pos, rot);
		rings.push_back(r);
	}


	
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update(0.016); // 60 fps



	for (int i = rings.size() - 1; i >= 0; i--) {
		ring * g = rings[i];

		glm::vec3 playerPos = cam.getPosition();
		glm::vec3 toPlayer = playerPos - g->getPosition();

		// Step 1: distance from plane
		glm::vec3 n = g->getNormal();
		float distFromPlane = glm::dot(toPlayer, n);

		// Step 2: reject if too far from plane
		if (fabs(distFromPlane) > 20.0f) // tolerance (gate thickness)
			continue;

		// Step 3: project onto plane
		glm::vec3 proj = playerPos - distFromPlane * n;
		float distFromCentre = glm::length(proj - g->getPosition());

		// Step 4: check ring radius
		if (distFromCentre <= g->getOuterR()) {
			gatesPassed++;
			cout << "Gate passed! Total: " << gatesPassed << endl;

			delete g;
			rings.erase(rings.begin() + i);
		}
	}






	//for (ring* ring : rings) {

	//	glm::vec2 playerXY(cam.getPosition().x, cam.getPosition().y);
	//	glm::vec2 ringXY(ring->getPosition().x, ring->getPosition().y);

	//	float distXY = glm::distance(playerXY, ringXY);
	//	float zDist = abs(cam.getPosition().z - ring->getPosition().z);
	//	if (zDist < ring->getInnerR()) {
	//		// Inside vertical tube
	//	}


	//	if (distXY > ring->getOuterR() - ring->getInnerR() && distXY < ring->getOuterR() + ring->getInnerR()) {
	//		// Player is passing through the ring horizontally
	//		// Optionally also check Z if you want a height range
	//		gatesPassed++;
	//	}


	//	//if (glm::distance(cam.getGlobalPosition(), ring->getPosition()) < ring->getOuterR()) { //right now has a spherical detction influence
	//	//	gatesPassed += 1; //this wont work since you can go through the same gate right now
	//	//	cout << gatesPassed << endl;
	//	//}
	//}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	for (int i = 0; i < asteroids; i++)
		body[i].draw();

	for (ring* ring : rings) {
		ring->draw(true); //draw every created ring

	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

