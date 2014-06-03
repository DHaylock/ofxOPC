//
//  NeoPixelGrid8x8.h
//
//  Created by David Haylock on 27/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelGrid8x8 {
   
    public:
    
        void setupLedGrid();
        void update();
    
        void grabImageData(ofPoint grabPos);
        void drawGrabRegion(bool hideArea);
        void drawGrid(int x, int y);

        // Return Data Method
        vector <ofColor> colorData();

    private:
    
        // Hold the Captured Colors
        vector <ofColor> colors;
    
        // Hold the Position of our Capture points
        vector <ofVec2f> pos;
    
        // Variables
        ofPoint _pos;
        float x;
        float y;
        int size;
        int spacing;
    
        // Capture Objects
        ofImage img;
        ofPixels pixels;
    
        // Draw Unit
        void ledGrid(int x, int y);
};