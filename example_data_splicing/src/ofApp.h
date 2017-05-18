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
	ofxNeoPixelGrid grid12x15;
	Effects defaultEffects;
	
	vector<ofColor> channelOne;
	vector<ofColor> channelTwo;
	vector<ofColor> channelThree;
	
	void spliceAndReverse(vector<ofColor> &tmpPixels,int spliceIndex,vector<int> invertedRows);
	
	int effect;
	bool hide;
};
