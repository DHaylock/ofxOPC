//
//  ofxNeoPixelRing.cpp
//  &
//  ofxNeoPixelJewel
//  Created by David Haylock on 29/05/2014.
//
//

#include "ofxNeoPixelRing.h"

#pragma mark - Neopixel Ring
//--------------------------------------------------------------
// *
// *    Neopixel Ring
// *
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
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for (int i = 0; i < size; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        // Generate the position of the grabber points
        float rx = actualX + (radius * cos(angle));
        float ry = actualY + (radius * sin(angle));
        
        float innerX = actualX + ((radius-6) * cos(angle));
        float innerY = actualY + ((radius-6) * sin(angle));

        float outerX = actualX + ((radius+6) * cos(angle));
        float outerY = actualY + ((radius+6) * sin(angle));
        
        innerRadius.push_back(ofVec2f(innerX, innerY));
        outerRadius.push_back(ofVec2f(outerX, outerY));
        
        pos.push_back(ofVec2f(rx,ry));
    }
    
    for (int i = 0; i < size; i++) {
        if (i == size-1) {
            mesh.addVertex(innerRadius[i]);
            mesh.addVertex(outerRadius[i]);
            mesh.addVertex(innerRadius[0]);
            mesh.addVertex(outerRadius[0]);
        }
        else {
            mesh.addVertex(innerRadius[i]);
            mesh.addVertex(outerRadius[i]);
        }
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
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for (int i = 0; i < size; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        // Generate the position of the grabber points
        float rx = actualX + (radius * cos(angle));
        float ry = actualY + (radius * sin(angle));
        
        float innerX = actualX + ((radius-6) * cos(angle));
        float innerY = actualY + ((radius-6) * sin(angle));
        
        float outerX = actualX + ((radius+6) * cos(angle));
        float outerY = actualY + ((radius+6) * sin(angle));
        
        innerRadius.push_back(ofVec2f(innerX, innerY));
        outerRadius.push_back(ofVec2f(outerX, outerY));
        
        pos.push_back(ofVec2f(rx,ry));
    }
    for (int i = 0; i < size; i++) {
        if (i == size-1) {
            mesh.addVertex(innerRadius[i]);
            mesh.addVertex(outerRadius[i]);
            mesh.addVertex(innerRadius[0]);
            mesh.addVertex(outerRadius[0]);
        }
        else {
            mesh.addVertex(innerRadius[i]);
            mesh.addVertex(outerRadius[i]);
        }
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
    mesh.draw(); 
    
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


#pragma mark - Neopixel Jewel
//--------------------------------------------------------------
// *
// *    Neopixel Jewel
// *
//--------------------------------------------------------------
ofxNeoPixelJewel::ofxNeoPixelJewel()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelJewel::~ofxNeoPixelJewel()
{
    
}
//--------------------------------------------------------------
ofxNeoPixelJewel::ofxNeoPixelJewel(int posx,int posy,int radiusOfJewel)
{
    // Setup Positioning
    size = 7;
    actualX = posx;
    actualY = posy;
    radius = radiusOfJewel;
    
    pos.push_back(ofVec2f(actualX,actualY));
    
    for (int i = 0; i < size-1; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
        // Generate the position of the grabber points
        float rx = actualX + (radius * cos(angle));
        float ry = actualY + (radius * sin(angle));
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void ofxNeoPixelJewel::setupLedJewel(int posx,int posy,int radiusOfJewel)
{
    // Setup Positioning
    size = 7;
    actualX = posx;
    actualY = posy;
    radius = radiusOfJewel;
    
    pos.push_back(ofVec2f(actualX,actualY));
    
    for (int i = 0; i < size-1; i++) {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
        // Generate the position of the grabber points
        float rx = actualX + (radius * cos(angle));
        float ry = actualY + (radius * sin(angle));
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void ofxNeoPixelJewel::drawGrabRegion(bool hideArea)
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
void ofxNeoPixelJewel::ledJewel()
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
void ofxNeoPixelJewel::draw(int x, int y)
{
    // Where to draw the ring!
    ofPushMatrix();
    ofTranslate(x-actualX, y-actualY);
    ledJewel();
    ofPopMatrix();
}
