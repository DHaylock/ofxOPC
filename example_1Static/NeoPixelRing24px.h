//
//  NeoPixelRing24px.h
//  example_1Static
//
//  Created by David Haylock on 25/05/2014.
//
//

#ifndef __example_1Static__NeoPixelRing24px__
#define __example_1Static__NeoPixelRing24px__

#include <iostream>
#include "ofMain.h"

class NeoPixelRing24px {
    
public:
   
    NeoPixelRing24px(){}
    virtual ~NeoPixelRing24px(){}
    
    void setupLedRing();
    void update();
    
    int size;
    float x;
    float y;
    float radius;
    void begin();
    void end();
    
    void drawRing(int x, int y);
    void ledRing();

    vector <ofColor> colors;
    vector <ofVec2f> pos;
    int _rw,_rh;
    int _radius;
    int _size;
    
    ofFbo texture;
    ofPixels pixels;
private:
    
    
};
#endif /* defined(__example_1Static__NeoPixelRing24px__) */
