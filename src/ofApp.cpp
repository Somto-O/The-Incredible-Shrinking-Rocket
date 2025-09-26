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

	ring * ring1 = new ring(200.0f, 5.0f, 50, 50, glm::vec3(50, 100, 200)); //thin ring to make as a gate for checkpoints
	rings.push_back(ring1);

	
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update(0.016); // 60 fps

	for (ring* ring : rings) {

		if (glm::distance(cam.getGlobalPosition(), ring->getPosition()) < ring->getOuterR()) { //right now has a spherical detction influence
			gatesPassed += 1; //this wont work since you can go through the same gate right now
			cout << gatesPassed << endl;
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	for (int i = 0; i < asteroids; i++)
		body[i].draw();

	for (ring* ring : rings) {
		ring->draw(); //draw every created ring
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

