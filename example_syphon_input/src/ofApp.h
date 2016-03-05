#pragma once

#include "ofMain.h"
#include "ofxOPC.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void exit();
    
        void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
        void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
        void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
        ofxOPC opcClient;
    	ofxSyphonClient syphonClient;
        ofxSyphonServerDirectory dir;
        int directoryId;

        ofxNeoPixelStrip leftStrip;
        ofxNeoPixelStrip rightStrip;
        ofxNeoPixelRing centerRing;
        ofxNeoPixelRing leftRing;
        ofxNeoPixelRing rightRing;
        ofxNeoPixelGrid centerGrid;
    
        Effects defaultEffects;
    
        int effect;
        bool hide;
        bool syphonActive;
};
