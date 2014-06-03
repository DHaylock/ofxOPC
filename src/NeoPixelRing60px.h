//
//  NeoPixelRing60px.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelRing60px {
    
public:
    NeoPixelRing60px(){}
    virtual ~NeoPixelRing60px(){}
    
    void setupLedRing();
    void update();
    void grabImageData(ofPoint grabPos);
    void drawGrabRegion(bool hideArea);
    void drawRing(int x, int y);
    
    // Return Data Method
    vector <ofColor> colorData();
   
private:
    
    // Hold the Captured Colors
    vector <ofColor> colors;
    
    // Hold the Position of our Capture points
    vector <ofVec2f> pos;
    
    // Variables
    int size;
    float x;
    float y;
    float radius;
    ofPoint _pos;
    
    // Capture Objects
    ofImage img;
    ofPixels pixels;
    
    // Draw Unit
    void ledRing();
};




