//
//  NeoPixel.h
//
//  Created by David Haylock on 16/07/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixel {
	
	public:

		void setupPixel(int x, int y);
		void update();
		void grabImageData();
		void drawGrabRegion(bool hideArea);
		void drawLed(int x, int y);

        // Return Data Method
        ofColor colorData();
        
    private:
        // Hold the Captured Colors
        ofColor colors;
        // Variables
        int size;
        float _x;
        float _y;
        ofPoint _pos;
        bool _rotated;
    
        // Capture Objects
        ofImage img;
        ofPixels pixels;
    
        // Draw Unit
        void ledPixel();


};