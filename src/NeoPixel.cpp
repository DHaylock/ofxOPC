//
//  NeoPixel.cpp
//
//  Created by David Haylock on 16/07/2014.
//
#include "NeoPixel.h"
//--------------------------------------------------------------
void NeoPixel::setupPixel(int x, int y)
{
    // Setup Positioning
    _x = x+1;
    _y = y+1;
   
    // Set the pixel data
    pixels.allocate(1,1,GL_RGB);
    img.allocate(1,1,OF_IMAGE_COLOR);
   
    // Generate the position of the grabber points
    float rx = _x;
    float ry = _y;
}
//--------------------------------------------------------------
void NeoPixel::update()
{
    // Clear the colors and pixels each frame
    pixels.clear();
    
    // Transfer grab data to the pixel array
    pixels = img.getPixelsRef();
    colors = pixels.getColor(_x, _y);
}
//--------------------------------------------------------------
ofColor NeoPixel::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixel::grabImageData()
{
    img.clear();
    img.grabScreen(_x,_y,2,2);
}
//--------------------------------------------------------------
void NeoPixel::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofRect(_x-9,_y-6,20,size*5+10);
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

        ofCircle(ofVec2f(_x, _y),2);
}
//--------------------------------------------------------------
void NeoPixel::ledPixel()
{
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors);
        ofCircle(_x,_y,3);
    }
}
//--------------------------------------------------------------
void NeoPixel::drawLed(int x, int y)
{
    // Where to draw the Strip!
    ofPushMatrix();
    ofTranslate(x, y);
    ledPixel();
    ofPopMatrix();
}