#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxOPC.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
        void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
        void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
        
        ofxSyphonServerDirectory dir;
        ofxSyphonClient client;
        int dirIdx;
    
        ofxOPC opcClient;
        NeoPixelRing60px ring60px;
        NeoPixelRing24px ring24pxlefteye;
        NeoPixelRing24px ring24pxrighteye;
        NeoPixelRing16px ring16px;
        NeoPixelStrip strip1;
        NeoPixelStrip strip2;
    
};
