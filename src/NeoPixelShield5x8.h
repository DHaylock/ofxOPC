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
        void grabImageData(ofPoint grabPos);
        void drawGrabRegion(bool hideArea);
        void drawShield(int x, int y);
    
        // Return Data Method
        vector <ofColor> colorData();
    
    private:
    
        // Hold the Captured Colors
        vector <ofColor> colors;
    
        // Hold the Position of our Capture points
        vector <ofVec2f> pos;
    
        // Variables
        float x;
        float y;
        int size;
        int spacing;
        ofPoint _pos;
    
        // Capture Objects
        ofImage img;
        ofPixels pixels;
    
        // Draw Unit
        void ledShield();
};







