//
//  NeoPixelStick.h
//
//  Created by David Haylock on 27/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelStick {
    
public:
    NeoPixelStick(){}
    virtual ~NeoPixelStick(){}
    
    void setupLedStick();
    void update();
    vector <ofColor> colorData();
    
    void grabImageData(ofRectangle r);
    void drawGrabRegion();
    void drawStick(int x, int y);
    
    int size;
    float x;
    float y;
    
private:
    void ledStick();
    
    vector <ofColor> colors;
    vector <ofVec2f> pos;
    
    ofRectangle _r;
    ofImage img;
    ofPixels pixels;
};