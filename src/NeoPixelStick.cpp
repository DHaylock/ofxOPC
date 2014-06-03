//
//  NeoPixelStick.cpp
//
//  Created by David Haylock on 27/05/2014.
//


#include "NeoPixelStick.h"
//--------------------------------------------------------------
void NeoPixelStick::setupLedStick(bool rotateH)
{
    // Setup Positioning
    size = 8;
    x = 5;
    y = 1;
    _rotated = rotateH;
    
    if (_rotated == true)
    {
        // Set the pixel data
        pixels.allocate(size,x,GL_RGB);
        img.allocate(size*5,10,OF_IMAGE_COLOR);
        
        for (int i = 0; i < size; i++)
        {
            // Generate the position of the grabber points
            float rx = x + (i*5);
            float ry = y;
            
            pos.push_back(ofVec2f(rx,ry));
        }
    }
    else if(_rotated == false)
    {
        // Set the pixel data
        pixels.allocate(x,size,GL_RGB);
        img.allocate(10,size*5,OF_IMAGE_COLOR);
        
        for (int i = 0; i < size; i++)
        {
            // Generate the position of the grabber points
            float rx = x;
            float ry = y + (i*5);
            
            pos.push_back(ofVec2f(rx,ry));
        }
    }
    else
    {
        
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
    if (_rotated == true)
    {
        img.grabScreen(_pos.x-x,_pos.y-y,size*5,10);
        
        //Update the position of the ring pixels
        for (int i = 0; i < pos.size(); i++)
        {
            pos[i] + ofVec2f(_pos.x,_pos.y);
        }
    }
    else if(_rotated == false)
    {
        img.grabScreen(_pos.x-x,_pos.y-y,10,size*5);
        
        //Update the position of the ring pixels
        for (int i = 0; i < pos.size(); i++)
        {
            pos[i] + ofVec2f(_pos.x,_pos.y);
        }
    }
    else
    {
        
    }
}
//--------------------------------------------------------------
void NeoPixelStick::drawGrabRegion(bool hideArea)
{
    
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        if (_rotated == true)
        {
            ofRect(_pos.x-9,_pos.y-9,size*5+12,20);
        }
        else
        {
            ofRect(_pos.x-9,_pos.y-6,20,size*5+12);
        }
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
  
    if (_rotated == true) {
        ofRect(_pos.x-5,_pos.y-y-4,size*5+7,10);
    }
    else
    {
        ofRect(_pos.x-5,_pos.y-y-1,10,size*5+7);
    }
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelStick::ledStick()
{
    
    if (_rotated == true)
    {
        ofFill();
        ofSetColor(100,175);
        ofRect(-x/2-2, y-6, size*5+5,10);
        
        for (int i = 0; i < size; i++)
        {
            ofFill();
            ofSetColor(colors[i]);
            ofCircle(pos[i].x-x,pos[i].y-y,3);
        }
    }
    else if(_rotated == false)
    {
        ofFill();
        ofSetColor(100,175);
        ofRect(-x/2-2, y-6, 10, size*5+5);
        
        for (int i = 0; i < size; i++)
        {
            ofFill();
            ofSetColor(colors[i]);
            ofCircle(pos[i].x-x,pos[i].y-y,3);
        }
    }
}
//--------------------------------------------------------------
void NeoPixelStick::drawStick(int x, int y)
{
    // Where to draw the Strip!
    ofPushMatrix();
    ofTranslate(x, y);
    ledStick();
    ofPopMatrix();
}