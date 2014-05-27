//
//  NeoPixelStrip.cpp
//  example_1Static
//
//  Created by David Haylock on 25/05/2014.
//
//

#include "NeoPixelStrip.h"

//--------------------------------------------------------------
void NeoPixelStrip::setupLedStrip(int length)
{
    size = length;
    x = 10;
    y = 1;
    
    pixels.allocate(x,length,GL_RGB);
    
    for (int i = 0; i < size; i++)
    {
        float rx = x-5;
        float ry = y + (i*5);
        
        pos.push_back(ofVec2f(rx,ry));
    }
    
}
//--------------------------------------------------------------
void NeoPixelStrip::update()
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
void NeoPixelStrip::drawGrabRegion()
{
    ofSetColor(0, 175);
    ofNoFill();
    ofRect(_r.x,_r.y,_r.width,0+(size*5));
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_r.x,_r.y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelStrip::grabImageData(ofRectangle r)
{
    
    _r = r;
    img.clear();
    img.grabScreen(r.x, r.y,r.width,size*5);
    
    
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(r.x,r.y);
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
        ofCircle(pos[i],3);
    }
    
}
//--------------------------------------------------------------
void NeoPixelStrip::drawStrip(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ledStrip();
    ofPopMatrix();
}



