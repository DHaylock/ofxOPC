//
//  NeoPixelGrid8x8.h
//
//  Created by David Haylock on 27/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelGrid8x8 {
   
    public:
    
        NeoPixelGrid8x8(){}
        virtual ~NeoPixelGrid8x8(){}

        void setupLedGrid();
        void update();
        vector <ofColor> colorData();
    
        void grabImageData(ofPoint grabPos);
        void drawGrabRegion(bool hideArea);
        void drawGrid(int x, int y);
    
        float x;
        float y;
        int size;
        int spacing;
    
    private:
        vector <ofColor> colors;
        vector <ofVec2f> pos;
        
        ofPoint _pos;
        ofImage img;
        ofPixels pixels;
        void ledGrid(int x, int y);
};