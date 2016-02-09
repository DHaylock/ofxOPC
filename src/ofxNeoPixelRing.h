//
//  ofxNeoPixelRing.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"

class ofxNeoPixelRing {
    
public:
    ofxNeoPixelRing(){}
    virtual ~ofxNeoPixelRing(){}
    
    void setupLedRing(int posx,int posy,int numberOfLeds,int radiusOfRing);
    void drawGrabRegion(bool hideArea);
    void drawRing(int x, int y);
    
    // Return Data Method
    vector <ofColor> colorData();
    vector <ofVec2f> pixelCoordinates();

    // Hold the Captured Colors
    vector <ofColor> colors;
private:

    // Hold the Position of our Capture points
    vector <ofVec2f> pos;
    
    // Variables
    int size;
    float centerX;
    float centerY;
    float radius;
    ofPoint _pos;
    
    // Draw Unit
    void ledRing();
};




