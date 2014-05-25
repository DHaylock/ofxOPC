//
//  NeoPixelRing24px.cpp
//  example_1Static
//
//  Created by David Haylock on 25/05/2014.
//
//

#include "NeoPixelRing24px.h"


//--------------------------------------------------------------
void NeoPixelRing24px::setupLedRing()
{
    size = 24;
    x = 50;
    y = 50;
    radius = 49;
    
    texture.allocate(radius*2+10, radius*2+10,GL_RGB);
    pixels.allocate(radius*2+10, radius*2+10,GL_RGB);
    
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        
        //Make Circle Points
        float rx = x + (radius * cos(angle));
        float ry = y + (radius * sin(angle));
        
        pos.push_back(ofVec2f(rx,ry));
    }
    
}
//--------------------------------------------------------------
void NeoPixelRing24px::update()
{

    

    texture.readToPixels(pixels);

    for (int i = 0; i < pos.size(); i++)
    {
        colors.push_back(pixels.getColor(pos[i].x, pos[i].y));
    }
    colors.clear();
    pixels.clear();
}
//--------------------------------------------------------------
void NeoPixelRing24px::begin()
{
    texture.begin();
    ofClear(0,0,0);
}
//--------------------------------------------------------------
void NeoPixelRing24px::end()
{
    texture.end();
}
//--------------------------------------------------------------
void NeoPixelRing24px::ledRing()
{
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],4);
        
        ofNoFill();
        ofSetColor(255,150);
        ofCircle(x, y, radius-6);
        ofCircle(x, y, radius+6);
    }
    ofRect(x-(radius)-5, y-(radius)-5, radius*2+10, radius*2+10);
}
//--------------------------------------------------------------
void NeoPixelRing24px::drawRing(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ledRing();
    ofPopMatrix();
    texture.draw(0,0);
}



