//
//  NeoPixelGrid8x8.cpp
//  example_1Static
//
//  Created by David Haylock on 27/05/2014.
//
//

#include "NeoPixelGrid8x8.h"
//--------------------------------------------------------------
void NeoPixelGrid8x8::setupLedGrid()
{
    size = 8*8;
    x = 2;
    y = 2;
    spacing = 7;
    
    pixels.allocate(70,70,GL_RGB);
    float ry;
    float rx;
    for (int i = 0; i < size; i++)
    {
        if (i <= 7) {
            rx = x+(i*spacing);
            ry = y+spacing;
        }
        if ((i >= 8)&&(i <= 15)) {
            rx = x+((i-8)*spacing);
            ry = y+(spacing*2);
        }
        
        if ((i >= 16)&&(i <= 23)) {
            rx = x+((i-16)*spacing);
            ry = y+(spacing*3);
        }
        if ((i >= 24)&&(i <= 31)) {
            rx = x+((i-24)*spacing);
            ry = y+(spacing*4);
        }
        if ((i >= 32)&&(i <= 39)) {
            rx = x+((i-32)*spacing);
            ry = y+(spacing*5);
        }
        if ((i >= 40)&&(i <= 47)) {
            rx = x+((i-40)*spacing);
            ry = y+(spacing*6);
        }
        if ((i >= 48)&&(i <= 55)) {
            rx = x+((i-48)*spacing);
            ry = y+(spacing*7);
        }
        if ((i >= 56)&&(i <= 63)) {
            rx = x+((i-56)*spacing);
            ry = y+(spacing*8);
        }
        
        
        pos.push_back(ofVec2f(rx,ry));
    }
    
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::update()
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
void NeoPixelGrid8x8::drawGrabRegion()
{
    ofSetColor(0, 175);
    ofNoFill();
    ofRect(_r.x-3,_r.y+4,60,60);
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_r.x,_r.y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelGrid8x8::grabImageData(ofRectangle r)
{
    
    _r = r;
    img.clear();
    img.grabScreen(r.x, r.y,r.width,r.height);
    
    
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(r.x,r.y);
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
    ofPushMatrix();
    ofTranslate(x, y);
    ledGrid();
    ofPopMatrix();
}