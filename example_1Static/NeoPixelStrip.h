//
//  NeoPixelStrip.h
//  example_1Static
//
//  Created by David Haylock on 25/05/2014.
//
//

#ifndef __example_1Static__NeoPixelStrip__
#define __example_1Static__NeoPixelStrip__

#include <iostream>
#include "ofMain.h"

class NeoPixelStrip {
    
public:
    
    NeoPixelStrip(){}
    virtual ~NeoPixelStrip(){}
    
    void setupLedStrip(int length);
    void update();
    void grabImageData(ofRectangle r);
    void drawGrabRegion();
    void drawStrip(int x, int y);
   
    int size;
    float x;
    float y;
    
private:
    void ledStrip();
    
    vector <ofColor> colors;
    vector <ofVec2f> pos;
    
    ofRectangle _r;
    ofImage img;
    ofPixels pixels;
};
#endif /* defined(__example_1Static__NeoPixelStrip__) */
