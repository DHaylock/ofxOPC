//
//  NeoPixelShield5x8.cpp
//
//  Created by David Haylock on 27/05/2014.
//

#include "NeoPixelShield5x8.h"
//--------------------------------------------------------------
void NeoPixelShield5x8::setupLedShield()
{
    size = 5*8;
    x = 2;
    y = 2;
    spacing = 7;
    
    pixels.allocate(70,70,GL_RGB);
    float ry;
    float rx;
    for (int i = 0; i < size; i++)
    {
        if (i <= 4) {
            rx = x+(i*spacing);
            ry = y+spacing;
        }
        if ((i >= 5)&&(i <= 9)) {
            rx = x+((i-5)*spacing);
            ry = y+(spacing*2);
        }
        if ((i >= 10)&&(i <= 14)) {
            rx = x+((i-10)*spacing);
            ry = y+(spacing*3);
        }
        if ((i >= 15)&&(i <= 19)) {
            rx = x+((i-15)*spacing);
            ry = y+(spacing*4);
        }
        if ((i >= 20)&&(i <= 24)) {
            rx = x+((i-20)*spacing);
            ry = y+(spacing*5);
        }
        if ((i >= 25)&&(i <= 29)) {
            rx = x+((i-25)*spacing);
            ry = y+(spacing*6);
        }
        if ((i >= 30)&&(i <= 34)) {
            rx = x+((i-30)*spacing);
            ry = y+(spacing*7);
        }
        if ((i >= 35)&&(i <= 39)) {
            rx = x+((i-35)*spacing);
            ry = y+(spacing*8);
        }
        
        
        pos.push_back(ofVec2f(rx,ry));
    }
    
}
//--------------------------------------------------------------
void NeoPixelShield5x8::update()
{
    colors.clear();
    pixels.clear();
    
    pixels = img.getPixelsRef();
    
    for (int i = 0; i < pos.size(); i++)
    {
        colors.push_back(pixels.getColor(pos[i].x, pos[i].y));
    }
}
//--------------------------------------------------------------
vector <ofColor> NeoPixelShield5x8::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelShield5x8::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofRect(_pos.x-x-5,_pos.y-y-5,44,70);
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
    
    ofRect(_pos.x-x-2,_pos.y-y+2,37,65);
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelShield5x8::grabImageData(ofPoint grabPos)
{
    _pos = grabPos;
    img.clear();
    img.grabScreen(_pos.x,_pos.y,70,70);
    
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
}
//--------------------------------------------------------------
void NeoPixelShield5x8::ledShield()
{
    ofFill();
    ofSetColor(0,175);
    ofRect(-2, 4, 39,60);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],3);
    }
}
//--------------------------------------------------------------
void NeoPixelShield5x8::drawShield(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-2,-2,100,100);
    ledShield();
    ofPopMatrix();
}