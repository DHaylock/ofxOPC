//
//  NeoPixelStick.h
//
//  Created by David Haylock on 27/05/2014.
//

#include <iostream>
#include "ofMain.h"

class NeoPixelStick {
    
public:
    NeoPixelStick(){}
    virtual ~NeoPixelStick(){}
    
    void setupLedStick(bool rotateH);
    void update();
    void grabImageData(ofPoint grabPos);
    void drawGrabRegion(bool hideArea);
    void drawStick(int x, int y);
    
    // Return Data Method
    vector <ofColor> colorData();
private:
    
    // Hold the Captured Colors
    vector <ofColor> colors;
    
    // Hold the Position of our Capture points
    vector <ofVec2f> pos;
   
    // Variables
    int size;
    float x;
    float y;
    bool _rotated;
    ofPoint _pos;
    
    // Capture Objects
    ofImage img;
    ofPixels pixels;
   
    // Draw Unit
    void ledStick();
};