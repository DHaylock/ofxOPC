//
//  NeoPixelRing16px.h
//  example_1Static
//
//  Created by David Haylock on 27/05/2014.
//
//

#ifndef __example_1Static__NeoPixelRing16px__
#define __example_1Static__NeoPixelRing16px__

#include <iostream>
#include "ofMain.h"

class NeoPixelRing16px {
    
public:
    
    NeoPixelRing16px(){}
    virtual ~NeoPixelRing16px(){}
    
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
#endif /* defined(__example_1Static__NeoPixelRing16px__) */
