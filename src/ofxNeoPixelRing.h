//
//  ofxNeoPixelRing.h
//  &
//  ofxNeoPixelJewel
//
//  Created by David Haylock on 25/05/2014.
//

#include <iostream>
#include "ofMain.h"
#include "ofxNeoPixelObject.h"
#include <math.h>
//-------------------------------------------------------------------------------
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
        vector<ofPoint> innerRadius;
        vector<ofPoint> outerRadius;
        ofMesh mesh;
        // Draw Unit
        void ledRing();
};
//-------------------------------------------------------------------------------
class ofxNeoPixelJewel : public ofxNeoPixelObject{
    public:
        ofxNeoPixelJewel();
        virtual ~ofxNeoPixelJewel();
        
        //! Constructor
        ofxNeoPixelJewel(int posx,int posy,int radiusOfJewel);
        
        //! Setup
        void setupLedJewel(int posx,int posy,int radiusOfJewel);
        void drawGrabRegion(bool hideArea);
        void draw(int x, int y);
        
    private:
        
        // Draw Unit
        void ledJewel();
};
