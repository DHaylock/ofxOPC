//
//  ofxNeoPixelRing.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"
#include "ofxNeoPixelObject.h"

class ofxNeoPixelRing : public ofxNeoPixelObject{
    public:
        ofxNeoPixelRing();
        virtual ~ofxNeoPixelRing();
    
        //! Constructor
        ofxNeoPixelRing(int posx,int posy,int numberOfLeds,int radiusOfRing);
    
        //! Setup
        void setupLedRing(int posx,int posy,int numberOfLeds,int radiusOfRing);
        void drawGrabRegion(bool hideArea);
        void draw(int x, int y);
    
    private:

        // Draw Unit
        void ledRing();
};




