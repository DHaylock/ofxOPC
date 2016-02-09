//
//  ofxNeoPixelStrip.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"

class ofxNeoPixelStrip {
    
    public:
        ofxNeoPixelStrip(){}
        virtual ~ofxNeoPixelStrip(){}
        void setupLedStrip(int posx, int posy,int length,int spacing);
        void drawGrabRegion(bool hideArea);
        void drawStrip(int x, int y);

        // Return Data Method
        vector <ofColor> colorData();
        vector <ofVec2f> pixelCoordinates();

        // Hold the Captured Colors
        vector <ofColor> colors;
    private:

    
        // Hold the Position of our Capture points
        vector <ofVec2f> pos;
    
        // Variables
        int size;
        float offsetX;
        float offsetY;
        float actualX;
        float actualY;
        ofPoint _pos;
        int _spacing;
    
        // Draw Unit
        void ledStrip();
};
