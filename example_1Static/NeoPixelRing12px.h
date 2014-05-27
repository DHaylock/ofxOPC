//
//  NeoPixelRing12px.h
//  example_1Static
//
//  Created by David Haylock on 27/05/2014.
//
//

#ifndef __example_1Static__NeoPixelRing12px__
#define __example_1Static__NeoPixelRing12px__

#include <iostream>
#include "ofMain.h"

class NeoPixelRing12px {
    
public:
    
    NeoPixelRing12px(){}
    virtual ~NeoPixelRing12px(){}
    
    void setupLedRing();
    void update();
    
    int size;
    float x;
    float y;
    float radius;
    
    void grabImageData(ofRectangle r);
    void drawGrabRegion();
    
    void drawRing(int x, int y);
    void ledRing();
    
private:
    vector <ofColor> colors;
    vector <ofVec2f> pos;
    int _rw,_rh;
    int _radius;
    int _size;
    ofRectangle _r;
    
    ofImage img;
    ofPixels pixels;
    
};
#endif /* defined(__example_1Static__NeoPixelRing12px__) */
