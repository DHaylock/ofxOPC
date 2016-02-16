//
//  ofxNeoPixelStrip.cpp
//
//  Created by David Haylock on 25/05/2014.
//

#include "ofxNeoPixelStrip.h"

//--------------------------------------------------------------
ofxNeoPixelStrip::ofxNeoPixelStrip()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelStrip::~ofxNeoPixelStrip()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelStrip::ofxNeoPixelStrip(int posx, int posy,int numberOfLeds,int spacing)
{
    // Setup Positioning
    size = numberOfLeds;
    offsetX = 5;
    offsetY = 5;
    _spacing = spacing;
    
    actualX = offsetX+posx;
    actualY = offsetY+posy;
    
    for (int i = 0; i < size; i++) {
        // Generate the position of the grabber points
        float rx = (offsetX+posx);
        float ry = (offsetY+posy) + (i*spacing);
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void ofxNeoPixelStrip::setupLedStrip(int posx, int posy,int numberOfLeds,int spacing)
{
    // Setup Positioning
    size = numberOfLeds;
    offsetX = 5;
    offsetY = 5;
    _spacing = spacing;
    
    actualX = offsetX+posx;
    actualY = offsetY+posy;
    
    for (int i = 0; i < size; i++) {
        // Generate the position of the grabber points
        float rx = (offsetX+posx);
        float ry = (offsetY+posy) + (i*spacing);
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void ofxNeoPixelStrip::drawGrabRegion(bool hideArea)
{
    if (hideArea == true) {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(255, 255);
        ofPopStyle();
   
        // Visualise the Grabber
        ofSetColor(255, 175);
        ofNoFill();
    }
    else {
        // Visualise the Grabber
        ofSetColor(0, 175);
        ofNoFill();
    }
    
    ofDrawRectangle(actualX-offsetX,actualY-(offsetY/2),10,size*_spacing);
    
    for (int i = 0; i < pos.size(); i++) {
        ofDrawCircle(pos[i],2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelStrip::ledStrip()
{
    ofFill();
    ofSetColor(100,175);
    ofDrawRectangle(-offsetX,actualY-(offsetY/2), 10,size*_spacing);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        if (!colors.empty()) {
            ofSetColor(colors[i]);
        }
        else {
            ofSetColor(ofColor::red);
        }
        ofDrawCircle(0,pos[i].y,2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelStrip::draw(int x, int y)
{
    // Where to draw the Strip!
    ofPushMatrix();
    ofTranslate(offsetX+x, y-pos[0].y);
    ledStrip();
    ofPopMatrix();
}