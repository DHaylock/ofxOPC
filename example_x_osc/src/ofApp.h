#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOPC.h"

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}NeoPixel;

class ofApp : public ofBaseApp{

	public:
	
//		ofApp() : transmitSocket( osc::IpEndpointName( "127.0.0.1", 9000) ){}
	
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		void exit();
	
		ofxOPC opcClient;
		Effects defaultEffects;
		map<int, ofxNeoPixelObject*> neoPixelObjects;
	
		vector<ofColor> mergedColor;
	
		int effect;
		bool hide;
	
	protected:
		static const int BufferSize = 2048;
		char buffer[BufferSize];
		osc::UdpTransmitSocket *transmitSocket;
};
