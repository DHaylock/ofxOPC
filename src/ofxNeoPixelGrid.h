//
//  ofxNeoPixelGrid.h
//
//  Created by David Haylock on 15/01/2015.
//
//

#include <iostream>
#include "ofMain.h"

class ofxNeoPixelGrid {
    public:
        ofxNeoPixelGrid(){}
        virtual ~ofxNeoPixelGrid(){}
    
        //! Setup the grid cols = number of X rows = number of Y
        void setupLedGrid(int cols,int rows,int posx,int posy,int spacing);
    
        void drawGrabRegion(bool hideArea);
        void drawGrid(int x, int y);
        
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
        float offsetX;
        float offsetY;
        float actualX;
        float actualY;
        int size;
        int _cols;
        int _rows;
        
        ofPoint _pos;
        int _spacing;
        
        // Draw Unit
        void ledGrid(int x, int y);
};
