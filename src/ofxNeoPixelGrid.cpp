//
//  ofxNeoPixelGrid.cpp
//
//  Created by David Haylock on 15/01/2015.
//
//

#include "ofxNeoPixelGrid.h"

//--------------------------------------------------------------
ofxNeoPixelGrid::ofxNeoPixelGrid()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelGrid::~ofxNeoPixelGrid()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelGrid::ofxNeoPixelGrid(int cols,int rows,int posx,int posy,int spacing)
{
    // Setup Positioning
    size = cols*rows;
    actualX = posx;
    actualY = posy;
    _cols = cols;
    _rows = rows;
    
    offsetX = spacing/2;
    offsetY = spacing/2;
    _spacing = spacing;
    
    float ry;
    float rx;
    
    
    for (int y = 0; y < _rows; y++) {
        for (int x = 0; x < _cols; x++) {
            rx = actualX+(x*_spacing);
            ry = actualY+(y*_spacing);
            pos.push_back(ofVec2f(rx,ry));
        }
    }
}
//--------------------------------------------------------------
void ofxNeoPixelGrid::setupLedGrid(int cols,int rows,int posx,int posy,int spacing)
{
    // Setup Positioning
    size = cols*rows;
    actualX = posx;
    actualY = posy;
    _cols = cols;
    _rows = rows;
    
    offsetX = spacing/2;
    offsetY = spacing/2;
    _spacing = spacing;
    
    float ry;
    float rx;
    
    
    for (int y = 0; y < _rows; y++) {
        for (int x = 0; x < _cols; x++) {
            rx = actualX+(x*_spacing);
            ry = actualY+(y*_spacing);
            pos.push_back(ofVec2f(rx,ry));
        }
    }
}
//--------------------------------------------------------------
void ofxNeoPixelGrid::drawGrabRegion(bool hideArea)
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
    ofDrawRectangle(actualX-(offsetX),actualY-(offsetY),_cols*_spacing,_rows*_spacing);
    
    for (int i = 0; i < pos.size(); i++) {
        ofDrawCircle(pos[i],2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelGrid::ledGrid()
{
    ofFill();
    ofSetColor(50,175);
    ofDrawRectangle(actualX-(offsetX),actualY-(offsetY),_cols*_spacing,_rows*_spacing);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        if (!colors.empty()) {
            ofSetColor(colors[i]);
        }
        else {
            ofSetColor(ofColor::red);
        }
        ofDrawCircle(pos[i],2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelGrid::draw(int x, int y)
{
    // Where to draw the Grid!
    ofPushMatrix();
    ofTranslate(x-pos[0].x, y-pos[0].y);
    ledGrid();
    ofPopMatrix();
}