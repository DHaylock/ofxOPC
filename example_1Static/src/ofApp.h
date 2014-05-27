#pragma once

#include "ofMain.h"
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
		
        ofxOPC pixelServer;
        float counter;
        NeoPixelRing24px ring;
        NeoPixelRing16px ring1;
        NeoPixelRing12px ring2;
        NeoPixelStrip strip;
        NeoPixelGrid8x8 grid;
        NeoPixelShield5x8 shield;
    void drawGraphics(int mode);
        int s;
};
