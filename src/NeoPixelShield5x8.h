//
//  NeoPixelShield5x8.h
//
//  Created by David Haylock on 27/05/2014.
//


#include <iostream>
#include "ofMain.h"

class NeoPixelShield5x8 {
    
    public:
        NeoPixelShield5x8(){}
        virtual ~NeoPixelShield5x8(){}
        
        void setupLedShield();
        void update();
        vector <ofColor> colorData();
        
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

