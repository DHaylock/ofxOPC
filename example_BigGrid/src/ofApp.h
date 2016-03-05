#pragma once

#include "ofMain.h"
#include "ofxOPC.h"
#include "Effects.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
        void exit();
        
        ofxOPC opcClient;
        Effects defaultEffects;
        ofxNeoPixelGrid grid32x32;
        
        int effect;
        bool hide;
};
