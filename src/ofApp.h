#pragma once

#include "ofMain.h"
#include "MyCustomCamera.h"
#include "ring.h"
#include "ship.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		
		int asteroids;
		int gatesPassed;
		float timeElapsed;
		bool started;
		float speed;
		bool gameOver = false;
		bool victory = false;
		float endTimer = 0.0f;

		std::vector<ring*> rings;
		std::vector<ofSpherePrimitive*> powerups;
		std::vector<ofSpherePrimitive*> enemies;


		ofNode body[500];

		MyCustomCamera cam;
		Ship ship;
};
