//
//  NeoPixelStick.cpp
//
//  Created by David Haylock on 27/05/2014.
//


#include "NeoPixelStick.h"
//--------------------------------------------------------------
void NeoPixelStick::setupLedStick()
{
    // Setup Positioning
    size = 8;
    x = 10;
    y = 1;
    
    // Set the pixel data
    pixels.allocate(x,size,GL_RGB);
    
    for (int i = 0; i < size; i++)
    {
        // Generate the position of the grabber points
        float rx = x-5;
        float ry = y + (i*5);
        
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void NeoPixelStick::update()
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
vector <ofColor> NeoPixelStick::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelStick::grabImageData(ofPoint grabPos)
{
    _pos = grabPos;
    img.clear();
    img.grabScreen(_pos.x-x, _pos.y-y,10,size*5);
    
    
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
    
}
//--------------------------------------------------------------
void NeoPixelStick::drawGrabRegion()
{
    // Draw Interaction Area
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(255, 255);
    ofRect(_pos.x-10,_pos.y-2,20,size*5+10);
    ofPopStyle();
    
    // Visualise the Grabber
    ofSetColor(0, 175);
    ofNoFill();
    ofRect(_pos.x-5,_pos.y-y,10,size*5);
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelStick::ledStick()
{
    
    ofFill();
    ofSetColor(0,175);
    ofRect(0, 0, 10, size*5);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],3);
    }
}
//--------------------------------------------------------------
void NeoPixelStick::drawStick(int x, int y)
{
    // Where to draw the Strip!
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-x,-y,100,100);
    ledStick();
    ofPopMatrix();
}