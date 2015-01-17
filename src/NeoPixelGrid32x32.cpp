//
//  NeoPixelGrid32x32.cpp
//  example_NeoPixelGrid32x32
//
//  Created by David Haylock on 15/01/2015.
//
//

#include "NeoPixelGrid32x32.h"

//--------------------------------------------------------------
void NeoPixelGrid32x32::setupLedGrid()
{
    // Setup Positioning
    size = 32*32;
    x = 2;
    y = 2;
    spacing = 7;
    
    // Set the pixel data
    pixels.allocate(230,230,GL_RGB);
    
    float ry;
    float rx;
    
    for (int i = 0; i < size; i++)
    {
            for (int row = 0; row < 32; row++)
            {
                if((i >= (row*32))&&(i <= ((row*32)+31)))
                {
                    rx = x+((i-(row*32))*spacing);
                    ry = y+(spacing*row);
                }
            }
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void NeoPixelGrid32x32::update()
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
vector <ofColor> NeoPixelGrid32x32::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelGrid32x32::grabImageData(ofPoint grabPos)
{
    // Change Capture Location
    _pos = grabPos;
    img.clear();
    img.grabScreen(_pos.x-x,_pos.y-y,230,230);
    
    //Update the position of the Grid
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid32x32::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofRect(_pos.x-7,_pos.y-6,230,234);
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
    
    ofRect(_pos.x-5, _pos.y-4,230,224);
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid32x32::ledGrid(int x, int y)
{
    ofPushMatrix();
    ofTranslate(-x+8, -y+8);
    ofFill();
    ofSetColor(0,175);
    ofRect(-4, -2, 230,226);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],3);
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void NeoPixelGrid32x32::drawGrid(int x, int y)
{
    // Where to draw the Grid!
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-x,-y,240,235);
    ledGrid(x,y);
    ofPopMatrix();
}