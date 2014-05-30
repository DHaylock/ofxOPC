//
//  NeoPixelStrip.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelStrip {
    
    public:
        NeoPixelStrip(){}
        virtual ~NeoPixelStrip(){}
        
        void setupLedStrip(int length);
        void update();
        vector <ofColor> colorData();
        
        void grabImageData(ofPoint grabPoint);
        void drawGrabRegion();
        void drawStrip(int x, int y);
       
        int size;
        float x;
        float y;
        
    private:
        void ledStrip();
        
        vector <ofColor> colors;
        vector <ofVec2f> pos;
        
        ofPoint _pos;
        ofImage img;
        ofPixels pixels;
};