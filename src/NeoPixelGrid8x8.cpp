//
//  NeoPixelGrid8x8.cpp
//
//  Created by David Haylock on 27/05/2014.
//


#include "NeoPixelGrid8x8.h"
//--------------------------------------------------------------
void NeoPixelGrid8x8::setupLedGrid()
{
    // Setup Positioning
    size = 8*8;
    x = 2;
    y = 2;
    spacing = 7;
    
    // Set the pixel data
    pixels.allocate(70,70,GL_RGB);

    float ry;
    float rx;
    
    for (int i = 0; i < size; i++)
    {
        // First Row
        if (i <= 7)
        {
            rx = x+(i*spacing);
            ry = y+spacing;
        }
        // Second Row
        if ((i >= 8)&&(i <= 15))
        {
            rx = x+((i-8)*spacing);
            ry = y+(spacing*2);
        }
        // Third Row
        if ((i >= 16)&&(i <= 23))
        {
            rx = x+((i-16)*spacing);
            ry = y+(spacing*3);
        }
        // Fourth Row
        if ((i >= 24)&&(i <= 31))
        {
            rx = x+((i-24)*spacing);
            ry = y+(spacing*4);
        }
        // Fifth Row
        if ((i >= 32)&&(i <= 39))
        {
            rx = x+((i-32)*spacing);
            ry = y+(spacing*5);
        }
        // Sixth Row
        if ((i >= 40)&&(i <= 47))
        {
            rx = x+((i-40)*spacing);
            ry = y+(spacing*6);
        }
        // Seventh Row
        if ((i >= 48)&&(i <= 55))
        {
            rx = x+((i-48)*spacing);
            ry = y+(spacing*7);
        }
        // Eighth Row
        if ((i >= 56)&&(i <= 63))
        {
            rx = x+((i-56)*spacing);
            ry = y+(spacing*8);
        }
        // Push Points of Grabber
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::update()
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
vector <ofColor> NeoPixelGrid8x8::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::grabImageData(ofPoint grabPos)
{
    // Change Capture Location
    _pos = grabPos;
    img.clear();
    img.grabScreen(_pos.x-x,_pos.y-y,70,70);
    
    //Update the position of the Grid
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::drawGrabRegion()
{
    
    // Show what the leds should be doing!
    ofFill();
    ofSetColor(100);
    ofRect(0,0,120,120);
    
    // Visualise the Grabber
    ofSetColor(0, 175);
    ofNoFill();
    ofRect(_pos.x-5, _pos.y+2,60,60);
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::ledGrid()
{
    ofFill();
    ofSetColor(0,175);
    ofRect(-3, 4, 60,60);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],3);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::drawGrid(int x, int y)
{
    // Where to draw the Grid!
    ofPushMatrix();
    ofTranslate(x, y);
    ledGrid();
    ofPopMatrix();
}