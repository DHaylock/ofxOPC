//
//  ofxNeoPixelRing.cpp
//
//  Created by David Haylock on 29/05/2014.
//
//

#include "ofxNeoPixelRing.h"

//--------------------------------------------------------------
ofxNeoPixelRing::ofxNeoPixelRing()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelRing::~ofxNeoPixelRing()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelRing::ofxNeoPixelRing(int posx,int posy,int numberOfLeds,int radiusOfRing)
{
    // Setup Positioning
    size = numberOfLeds;
    actualX = posx;
    actualY = posy;
    radius = radiusOfRing;
    
    for (int i = 0; i < size; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        // Generate the position of the grabber points
        float rx = actualX + (radius * cos(angle));
        float ry = actualY + (radius * sin(angle));
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void ofxNeoPixelRing::setupLedRing(int posx,int posy,int numberOfLeds,int radiusOfRing)
{
    // Setup Positioning
    size = numberOfLeds;
    actualX = posx;
    actualY = posy;
    radius = radiusOfRing;
    
    for (int i = 0; i < size; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        // Generate the position of the grabber points
        float rx = actualX + (radius * cos(angle));
        float ry = actualY + (radius * sin(angle));
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void ofxNeoPixelRing::drawGrabRegion(bool hideArea)
{
    if (hideArea == true) {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(255, 255);
        ofDrawCircle(actualX,actualY,radius+6);
        ofDrawCircle(actualX,actualY,radius-6);
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
    ofDrawCircle(actualX,actualY,radius+6);
    ofDrawCircle(actualX,actualY,radius-6);
    
    for (int i = 0; i < pos.size(); i++) {
        ofDrawCircle(pos[i],2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelRing::ledRing()
{
    ofPushMatrix();

    ofFill();
    ofSetColor(50,175);
    ofDrawCircle(actualX,actualY,radius+6);
    ofSetColor(0);
    ofDrawCircle(actualX,actualY,radius-6);
    for (int i = 0; i < size; i++) {
        ofFill();
        if (!colors.empty()) {
            ofSetColor(colors[i]);
        }
        else {
            ofSetColor(ofColor::red);
        }
        ofDrawCircle(pos[i].x, pos[i].y,2);
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofxNeoPixelRing::draw(int x, int y)
{
    // Where to draw the ring!
    ofPushMatrix();
    ofTranslate(x-actualX, y-actualY);
    ledRing();
    ofPopMatrix();
}