//
//  NeoPixelGrid8x8.h
//  example_1Static
//
//  Created by David Haylock on 27/05/2014.
//
//

#ifndef __example_1Static__NeoPixelGrid8x8__
#define __example_1Static__NeoPixelGrid8x8__

#include <iostream>
#include "ofMain.h"

class NeoPixelGrid8x8 {
    public:
    
        NeoPixelGrid8x8(){}
        virtual ~NeoPixelGrid8x8(){}

        void setupLedGrid();
        void update();
        void grabImageData(ofRectangle r);
        void drawGrabRegion();
        void drawGrid(int x, int y);
    
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
        void ledGrid();
};


#endif /* defined(__example_1Static__NeoPixelGrid8x8__) */
