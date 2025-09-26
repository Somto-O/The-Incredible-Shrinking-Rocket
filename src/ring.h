#pragma once
#include "ofMain.h"

class ring{
	public:
		ring(float, float, int, int, glm::vec3 pos);
		ofMesh createRing(); //from first assignment
		void draw();

		glm::vec3 getPosition() { return position; }
		float getOuterR() { return outerR; }
		float getInnerR() { return innerR; }
		int getOuterRes() { return outerRes; }
		int getInnerRes() { return innerRes; }

	private:
		ofMesh mesh;
		glm::vec3 position;
		float outerR;
		float innerR;
		int outerRes;
		int innerRes;
};

