#pragma once

#include "ofMain.h"
#include "ofxOPC.h"
#include "NeoPixelRing24px.h"
#include "NeoPixelStrip.h"
#include "NeoPixelGrid8x8.h"

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
		
        ofxOPC pixelServer;
        float counter;
        NeoPixelRing24px ring;
        NeoPixelStrip strip;
        NeoPixelGrid8x8 grid;
    void drawGraphics(int mode);
        int s;
};
