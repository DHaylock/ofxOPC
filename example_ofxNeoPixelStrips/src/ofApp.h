#pragma once

#include "ofMain.h"
#include "ofxOPC.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
        void exit();

        ofxOPC opcClient;
        ofxNeoPixelStrip stick;
        ofxNeoPixelStrip strip40px;
        ofxNeoPixelStrip strip60px;
        ofxNeoPixelStrip strip144px;

        Effects defaultEffects;
    
        int effect;
        bool hide;
};
