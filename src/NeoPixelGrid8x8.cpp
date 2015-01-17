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
        for (int row = 0; row < 8; row++)
        {
            if((i >= (row*8))&&(i <= ((row*8)+7)))
            {
                rx = x+((i-(row*8))*spacing);
                ry = y+(spacing*row);
            }
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
void NeoPixelGrid8x8::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofRect(_pos.x-7,_pos.y-6,65,65);
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
    
    ofRect(_pos.x-5, _pos.y-4,60,60);
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::ledGrid(int x, int y)
{
    ofPushMatrix();
    ofTranslate(-x/4, -y/4);
    ofFill();
    ofSetColor(0,175);
    ofRect(-4, -4, 62,62);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],3);
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::drawGrid(int x, int y)
{
    // Where to draw the Grid!
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-x,-y,124,124);
    ledGrid(x,y);
    ofPopMatrix();
}