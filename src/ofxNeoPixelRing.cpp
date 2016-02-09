//
//  ofxNeoPixelRing.cpp
//
//  Created by David Haylock on 29/05/2014.
//
//

#include "ofxNeoPixelRing.h"

//--------------------------------------------------------------
void ofxNeoPixelRing::setupLedRing(int posx,int posy,int numberOfLeds,int radiusOfRing)
{
    // Setup Positioning
    size = numberOfLeds;
    centerX = posx;
    centerY = posy;
    radius = radiusOfRing;
    
    for (int i = 0; i < size; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        // Generate the position of the grabber points
        float rx = centerX + (radius * cos(angle));
        float ry = centerY + (radius * sin(angle));
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
vector <ofColor> ofxNeoPixelRing::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
vector<ofVec2f> ofxNeoPixelRing::pixelCoordinates()
{
    colors.clear();
    return pos;
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
        ofDrawCircle(centerX,centerY,radius+6);
        ofDrawCircle(centerX,centerY,radius-6);
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
    ofDrawCircle(centerX,centerY,radius+6);
    ofDrawCircle(centerX,centerY,radius-6);
    
    for (int i = 0; i < pos.size(); i++) {
        ofDrawCircle(pos[i],2);
    }
}
//--------------------------------------------------------------
void ofxNeoPixelRing::ledRing()
{
    ofPushMatrix();
    ofSetColor(50,175);
    ofDrawCircle(centerX,centerY,radius+6);
    ofSetColor(0);
    ofDrawCircle(centerX,centerY,radius-6);
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
void ofxNeoPixelRing::drawRing(int x, int y)
{
    // Where to draw the ring!
    ofPushMatrix();
    ofTranslate(x-centerX, y-centerY);
    ledRing();
    ofPopMatrix();
}