#pragma once
#include "ofMain.h"

class ring {
	public:
		ring(float, float, int, int, glm::vec3 pos, glm::vec3 rot);
		ofMesh createRing(); //from first assignment
		void draw(bool flag);
		void setAsNext(bool flag) { nextGoal = flag; }
		glm::vec3 getNormal() const;

		glm::vec3 getPosition() { return position; }
		float getOuterR() { return outerR; }
		float getInnerR() { return innerR; }
		int getOuterRes() { return outerRes; }
		int getInnerRes() { return innerRes; }
		glm::vec3 getRotation() { return rotation; }
		bool getNext() { return nextGoal; }

	private:
		ofMesh mesh;
		glm::vec3 position;
		glm::vec3 rotation;
		float outerR;
		float innerR;
		int outerRes;
		int innerRes;
		bool nextGoal;
};

