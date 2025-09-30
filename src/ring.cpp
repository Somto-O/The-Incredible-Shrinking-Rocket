
#include "ring.h"

ring::ring(float R, float r, int majorRes, int minorRes, glm::vec3 pos, glm::vec3 rot){
	outerR = R;
	innerR = r;
	outerRes = majorRes;
	innerRes = minorRes;
	position = pos;
	rotation = rot;


	createRing();
}


ofMesh ring::createRing() {
	mesh.setMode(OF_PRIMITIVE_TRIANGLES); // bunch of individual triangles

	for (int i = 0; i < outerRes; i++) {
		float theta = TWO_PI * i / outerRes;

		for (int j = 0; j < innerRes; j++) {
			float phi = TWO_PI * j / innerRes;

			glm::vec3 N = glm::vec3(
				cos(theta) * cos(phi),
				sin(theta) * cos(phi),
				sin(phi));

			glm::vec3 v = glm::vec3( //now sets torus origin at a given point and not at (0, 0, 0)
				outerR * cos(theta) + innerR * N.x,
				outerR * sin(theta) + innerR * N.y,
				innerR * N.z);

			mesh.addVertex(v);
			mesh.addNormal(N); // applies to most recent vertex
		}
	}

	for (int i = 0; i < outerRes; i++) {
		for (int j = 0; j < innerRes; j++) {
			int iNext = (i + 1) % outerRes;
			int jNext = (j + 1) % innerRes;

			int id0 = i * innerRes + j;
			int id1 = i * innerRes + jNext;
			int id2 = iNext * innerRes + jNext;
			int id3 = iNext * innerRes + j;

			mesh.addIndex(id0);
			mesh.addIndex(id1);
			mesh.addIndex(id2);

			mesh.addIndex(id0);
			mesh.addIndex(id2);
			mesh.addIndex(id3);
		}
	}

	//clearing colours just in case
	mesh.clearColors();

	return mesh;
}


void ring::draw(bool debugCollision = false) {
	ofPushMatrix();
	ofTranslate(position);
	ofRotateDeg(rotation.x, 1, 0, 0);
	ofRotateDeg(rotation.y, 0, 1, 0);
	ofRotateDeg(rotation.z, 0, 0, 1);


	ofPushStyle();
	ofFill();
	if (nextGoal) {
		ofSetColor(255, 240, 60);
		
	} else {
		ofSetColor(160);
	}
	mesh.drawFaces();
	ofPopStyle();

	/*// Optionally draw a wireframe overlay so the ring shape stays visible at any brightness
	if (nextGoal) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(40); // darker outline
		mesh.drawWireframe();
		ofPopStyle();
	}*/

	if (debugCollision) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(0, 255, 0, 150); // semi-transparent green


		// draw a circle in XY plane as the “collision plane”
		float radiusOuter = outerR + innerR;
		float radiusInner = outerR - innerR;
		ofDrawCircle(glm::vec3(0, 0, 0), radiusOuter);
		ofDrawCircle(glm::vec3(0, 0, 0), radiusInner);

		ofPopStyle();
	}

	ofPopMatrix();
}

glm::vec3 ring::getNormal() const {
	// start with local Z axis
	glm::mat4 rot(1.0f);
	rot = glm::rotate(rot, ofDegToRad(rotation.x), glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, ofDegToRad(rotation.y), glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, ofDegToRad(rotation.z), glm::vec3(0, 0, 1));
	return glm::normalize(glm::vec3(rot * glm::vec4(0, 0, 1, 0))); // local forward
}
