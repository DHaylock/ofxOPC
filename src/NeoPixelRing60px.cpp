//
//  NeoPixelRing60px.cpp
//  example_NeoPixelRing24px
//
//  Created by David Haylock on 29/05/2014.
//
//

#include "NeoPixelRing60px.h"

//--------------------------------------------------------------
void NeoPixelRing60px::setupLedRing()
{
    // Setup Positioning
    size = 60;
    x = 75;
    y = 75;
    radius = 60;
    
    // Set the pixel data
    pixels.allocate(radius*2+10, radius*2+10,GL_RGB);
    
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * PI)/(1.0 * size);
        
        // Generate the position of the grabber points
        float rx = x + (radius * cos(angle));
        float ry = y + (radius * sin(angle));
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void NeoPixelRing60px::update()
{
    // Clear the colors and pixels each frame
    colors.clear();
    pixels.clear();
    
    // Transfer grab data to the pixel array
    pixels = img.getPixelsRef();
    
    for (int i = 0; i < pos.size(); i++)
    {
        colors.push_back(pixels.getColor(pos[i].x, pos[i].y));
    }
}
//--------------------------------------------------------------
vector <ofColor> NeoPixelRing60px::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelRing60px::grabImageData(ofPoint grabPos)
{
    // Change Capture Location
    _pos = grabPos;
    img.clear();
    img.grabScreen(_pos.x-x, _pos.y-y,150,150);
    
    // Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
}
//--------------------------------------------------------------
void NeoPixelRing60px::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofCircle(_pos.x, _pos.y, radius+12);
        ofCircle(_pos.x, _pos.y, radius-12);
        ofPopStyle();
        
        // Visualise the Grabber
        ofSetColor(255, 175);
        ofNoFill();
    }
    else
    {
        // Visualise the Grabber
        ofSetColor(0, 175);
        ofNoFill();
    }
    ofCircle(_pos.x, _pos.y, radius+6);
    ofCircle(_pos.x, _pos.y, radius-6);
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelRing60px::ledRing()
{
    ofPushMatrix();
    ofTranslate(8, 8);
    ofSetColor(0, 175);
    ofBeginShape();
    
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * PI)/(1.0 * size-1);
        
        // Make Circle Points
        float rx = x-x + ((radius+6) * cos(angle));
        float ry = y-y + ((radius+6) * sin(angle));
        ofVertex(rx, ry);
    }
    
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * PI)/(1.0 * size-1);
        
        // Make Circle Points
        float rx = x-x + ((radius-6)  * cos(angle));
        float ry = y-y + ((radius-6)  * sin(angle));
        ofVertex(rx, ry);
    }
    
    ofEndShape(true);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i].x-x, pos[i].y-y,4);
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void NeoPixelRing60px::drawRing(int x, int y)
{
    // Where to draw the ring!
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-70,-70,150,150);
    ledRing();
    ofPopMatrix();
}