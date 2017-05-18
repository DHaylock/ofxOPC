//
//  ofxNeoPixelObject.h
//  Created by David Haylock on 15/02/2016.
//
//

#ifndef ofxNeoPixelObject_h
#define ofxNeoPixelObject_h

#include <stdio.h>
#include "ofMain.h"

class ofxNeoPixelObject {
    public:
    
        ofxNeoPixelObject(){}
        virtual ~ofxNeoPixelObject(){}
        //! Return Data Method
        vector <ofColor> colorData();
        
        //! Return the locations of the Pixels
        vector <ofPoint> getPixelCoordinates();
        
        // Variables
        int size;
        int radius;
        int _spacing;
        float offsetX;
        float offsetY;
        float actualX;
        float actualY;
        ofPoint _pos;
        int _cols;
        int _rows;
    
    
        // Hold the Captured Colors
        vector <ofColor> colors;
        // Hold the Position of our Capture points
        vector <ofPoint> pos;
    
        virtual void drawGrabRegion(bool hideArea);
        virtual void draw(int x,int y);
    
    private:


};



#endif /* ofxGenericNeoPixelObject_h */
