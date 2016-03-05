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
        ofxNeoPixelGrid grid8x8;
        ofxNeoPixelGrid grid5x7;
        ofxNeoPixelGrid grid32x32;
    
        Effects defaultEffects;
    
        int effect;
        bool hide;
};
