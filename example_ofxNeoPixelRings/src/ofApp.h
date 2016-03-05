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
        ofxNeoPixelRing ring12px;
        ofxNeoPixelRing ring16px;
        ofxNeoPixelRing ring24px;
        ofxNeoPixelRing ring60px;
        ofxNeoPixelJewel jewel;
    
        Effects defaultEffects;
    
        int effect;
        bool hide;
};
