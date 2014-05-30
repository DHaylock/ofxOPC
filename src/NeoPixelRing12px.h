//
//  NeoPixelRing12px.h
//
//  Created by David Haylock on 27/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelRing12px {
    
    public:
        NeoPixelRing12px(){}
        virtual ~NeoPixelRing12px(){}
        
        void setupLedRing();
        void update();
        vector <ofColor> colorData();
        
        int size;
        float x;
        float y;
        float radius;
        
        void grabImageData(ofPoint grabPos);
        void drawGrabRegion();
        
        void drawRing(int x, int y);
        void ledRing();
        
    private:
        vector <ofColor> colors;
        vector <ofVec2f> pos;
        int _rw,_rh;
        int _radius;
        int _size;
        ofPoint _pos;
        
        ofImage img;
        ofPixels pixels;
    
};
