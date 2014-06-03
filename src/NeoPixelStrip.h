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
        
        void setupLedStrip(int length,bool rotateH);
        void update();
        void grabImageData(ofPoint grabPoint);
        void drawGrabRegion(bool hideArea);
        void drawStrip(int x, int y);
       
        // Return Data Method
        vector <ofColor> colorData();
    
    private:
        // Hold the Captured Colors
        vector <ofColor> colors;
    
        // Hold the Position of our Capture points
        vector <ofVec2f> pos;
    
        // Variables
        int size;
        float x;
        float y;
        ofPoint _pos;
        bool _rotated;
    
        // Capture Objects
        ofImage img;
        ofPixels pixels;
    
        // Draw Unit
        void ledStrip();
};
