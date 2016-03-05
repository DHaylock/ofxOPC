#pragma once

#include "ofMain.h"
#include "ofxOPC.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void exit();
    
    ofxOPC opcClient;
    map<int,ofxNeoPixelObject*> neoPixels;
    vector<ofVec2f> ringOrigins;
    
    Effects defaultEffects;
    
    int effect;
    bool hide;
};
