//
//  ofxNeoPixelGrid.h
//
//  Created by David Haylock on 15/01/2015.
//
//

#include <iostream>
#include "ofMain.h"
#include "ofxNeoPixelObject.h"

class ofxNeoPixelGrid : public ofxNeoPixelObject {
    public:
        ofxNeoPixelGrid();
        virtual ~ofxNeoPixelGrid();

        ofxNeoPixelGrid(int cols,int rows,int posx,int posy,int spacing);
    
        //! Setup the grid cols = number of X rows = number of Y
        void setupLedGrid(int cols,int rows,int posx,int posy,int spacing);
        void drawGrabRegion(bool hideArea);
        void draw(int x, int y);
    
    private:
    
        // Draw Unit
        void ledGrid();
};
