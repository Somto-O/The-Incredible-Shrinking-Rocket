
#include "ring.h"

ring::ring(float R, float r, int majorRes, int minorRes, glm::vec3 pos){
	outerR = R;
	innerR = r;
	outerRes = majorRes;
	innerRes = minorRes;
	position = pos;

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
				outerR * cos(theta) + innerR * N.x + position.x,
				outerR * sin(theta) + innerR * N.y + position.y,
				innerR * N.z + position.z);


			ofColor c = ofColor(255 * (i + 0.001) / outerRes, 255 * (j + 0.001) / innerRes, 255 * 0.5);

			mesh.addVertex(v);
			mesh.addNormal(N); // applies to most recent vertex
			mesh.addColor(c); // applies to most recent vertex
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

	return mesh;
}

void ring::draw() {
	mesh.draw();
}
