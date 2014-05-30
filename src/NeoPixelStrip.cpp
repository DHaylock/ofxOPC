//
//  NeoPixelStrip.cpp
//
//  Created by David Haylock on 25/05/2014.
//

#include "NeoPixelStrip.h"

//--------------------------------------------------------------
void NeoPixelStrip::setupLedStrip(int length)
{
    // Setup Positioning
    size = length;
    x = 10;
    y = 1;
    
    // Set the pixel data
    pixels.allocate(x,length,GL_RGB);
    
    for (int i = 0; i < size; i++)
    {
        // Generate the position of the grabber points
        float rx = x-5;
        float ry = y + (i*5);
        
        pos.push_back(ofVec2f(rx,ry));
    }
    
}
//--------------------------------------------------------------
void NeoPixelStrip::update()
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
vector <ofColor> NeoPixelStrip::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelStrip::grabImageData(ofPoint grabPoint)
{
    
    _pos = grabPoint;
    img.clear();
    img.grabScreen(_pos.x,_pos.y,10,size*5);
    
    
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
    
}
//--------------------------------------------------------------
void NeoPixelStrip::drawGrabRegion()
{
    // Draw Interaction Area
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(255, 255);
    ofRect(_pos.x-5,_pos.y-5,20,size*5+20);
    ofPopStyle();
    
    // Visualise the Grabber
    ofSetColor(0, 175);
    ofNoFill();
    ofRect(_pos.x,_pos.y,10,size*5);
    
    for (int i = 0; i < pos.size(); i++)
    {
         ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelStrip::ledStrip()
{
    
    ofFill();
    ofSetColor(0,175);
    ofRect(0, 0, 10, size*5);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i].x-x,pos[i].y-y,3);
    }
}
//--------------------------------------------------------------
void NeoPixelStrip::drawStrip(int x, int y)
{
    // Where to draw the Strip!
    ofPushMatrix();
    ofTranslate(x, y);
    ledStrip();
    ofPopMatrix();
}



