//
//  ofxNeoPixelStrip.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"
#include "ofxGenericNeoPixelObject.hpp"

class ofxNeoPixelStrip : public ofxGenericNeoPixelObject {
    public:
        ofxNeoPixelStrip();
        virtual ~ofxNeoPixelStrip();
    
        //! Constructor
        ofxNeoPixelStrip(int posx, int posy,int numberOfLeds,int spacing);
    
        //! Setup Strip
        void setupLedStrip(int posx, int posy,int numberOfLeds,int spacing);
    
        void drawGrabRegion(bool hideArea);
        void draw(int x, int y);

    private:
    
    
        // Draw Unit
        void ledStrip();
};
