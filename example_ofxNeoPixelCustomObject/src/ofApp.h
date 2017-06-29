#pragma once

#include "ofMain.h"
#include "ofxOPC.h"

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
	
		void exit();
		
		ofxOPC opcClient;
		Effects defaultEffects;
		map<int, ofxNeoPixelObject*> neoPixelObjects;
		
		vector<ofColor> mergedColor;
		
		int effect;
		bool hide;
	
};
