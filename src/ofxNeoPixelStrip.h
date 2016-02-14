//
//  ofxNeoPixelStrip.h
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"

class ofxNeoPixelStrip {
    public:
        ofxNeoPixelStrip();
        virtual ~ofxNeoPixelStrip();
    
        //! Constructor
        ofxNeoPixelStrip(int posx, int posy,int numberOfLeds,int spacing);
    
        //! Setup Strip
        void setupLedStrip(int posx, int posy,int numberOfLeds,int spacing);
    
        void drawGrabRegion(bool hideArea);
        void drawStrip(int x, int y);

        //! Return Data Method
        vector <ofColor> colorData();
        
        //! Return the locations of the Pixels
        vector <ofVec2f> getPixelCoordinates();

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
