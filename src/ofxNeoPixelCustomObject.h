//
//  ofxNeoPixelCustomObject.h
//
//  Created by David Haylock on 17/05/2017.
//
//

#ifndef ofxNeoPixelCustomObject_h
#define ofxNeoPixelCustomObject_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxNeoPixelObject.h"

class ofxNeoPixelCustomObject : public ofxNeoPixelObject {
public:
	ofxNeoPixelCustomObject();
	virtual ~ofxNeoPixelCustomObject();
	
	//! Constructor
	ofxNeoPixelCustomObject(int offsetx, int offsety,vector<ofPoint> positions,int numberOfLeds,int spacing);
	
	//! Setup Strip
	void setupLedObject(int offsetx, int offsety,vector<ofPoint> positions,int numberOfLeds,int spacing);
	void drawGrabRegion(bool hideArea);
	void draw(int x, int y);
	
private:
	
	// Draw Unit
	void ledObject();
	
	ofMesh mesh;
};


#endif /* ofxNeoPixelCustomObject_h */
