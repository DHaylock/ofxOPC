//
//  ofxNeoPixelGrid.cpp
//
//  Created by David Haylock on 15/01/2015.
//
//

#include "ofxNeoPixelGrid.h"

//--------------------------------------------------------------
void ofxNeoPixelGrid::setupLedGrid(int cols,int rows,int posx,int posy,int spacing)
{
    // Setup Positioning
    size = cols*rows;
    actualX = posx;
    actualY = posy;
    _cols = cols;
    _rows = rows;
    
    offsetX = 5;
    offsetY = 5;
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
vector <ofColor> ofxNeoPixelGrid::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
vector<ofVec2f> ofxNeoPixelGrid::getPixelCoordinates()
{
    colors.clear();
    return pos;
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
    ofDrawRectangle(actualX-(offsetX/2),actualY-(offsetY/2),_cols*_spacing,_rows*_spacing);
    
    for (int i = 0; i < pos.size(); i++) {
        ofDrawCircle(pos[i],2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelGrid::ledGrid()
{
    ofFill();
    ofSetColor(50,175);
    ofDrawRectangle(actualX-(offsetX/2),actualY-(offsetY/2),_cols*_spacing,_rows*_spacing);
    
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
void ofxNeoPixelGrid::drawGrid(int x, int y)
{
    // Where to draw the Grid!
    ofPushMatrix();
    ofTranslate(x-pos[0].x, y-pos[0].y);
    ledGrid();
    ofPopMatrix();
}