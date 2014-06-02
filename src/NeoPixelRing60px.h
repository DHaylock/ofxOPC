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
    vector <ofColor> colorData();
    int indexPos();
    
    int size;
    float x;
    float y;
    float radius;
    
    void grabImageData(ofPoint grabPos);
    void drawGrabRegion(bool hideArea);
    
    void drawRing(int x, int y);
    void ledRing();
    
private:
    vector <ofColor> colors;
    vector <ofVec2f> pos;
    int _rw,_rh;
    int _radius;
    int _size;
    int _index;
    ofPoint _pos;
    
    ofImage img;
    ofPixels pixels;
};

