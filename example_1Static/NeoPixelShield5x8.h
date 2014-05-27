//
//  NeoPixelShield5x8.h
//  example_1Static
//
//  Created by David Haylock on 27/05/2014.
//
//

#ifndef __example_1Static__NeoPixelShield5x8__
#define __example_1Static__NeoPixelShield5x8__

#include <iostream>
#include "ofMain.h"

class NeoPixelShield5x8 {
public:
    
    NeoPixelShield5x8(){}
    virtual ~NeoPixelShield5x8(){}
    
    void setupLedShield();
    void update();
    void grabImageData(ofRectangle r);
    void drawGrabRegion();
    void drawShield(int x, int y);
    
    float x;
    float y;
    int size;
    int spacing;
private:
    vector <ofColor> colors;
    vector <ofVec2f> pos;
    
    ofRectangle _r;
    ofImage img;
    ofPixels pixels;
    void ledShield();
};
#endif /* defined(__example_1Static__NeoPixelShield5x8__) */
