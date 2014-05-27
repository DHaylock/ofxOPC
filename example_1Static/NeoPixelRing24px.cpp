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
    radius = 30;
    
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
    colors.clear();
    pixels.clear();
    
    pixels = img.getPixelsRef();
    
    for (int i = 0; i < pos.size(); i++)
    {
        colors.push_back(pixels.getColor(pos[i].x, pos[i].y));
    }
}
//--------------------------------------------------------------
void NeoPixelRing24px::grabImageData(ofRectangle r)
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
void NeoPixelRing24px::drawGrabRegion()
{
    
    ofSetColor(0, 175);
    ofNoFill();
    ofCircle(_r.x+50, _r.y+50, radius+6);
    ofCircle(_r.x+50, _r.y+50, radius-6);
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_r.x,_r.y),2);
    }
    
}
//--------------------------------------------------------------
void NeoPixelRing24px::ledRing()
{
    ofSetColor(0, 175);
    ofBeginShape();
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
        
        //Make Circle Points
        float rx = x + ((radius+6) * cos(angle));
        float ry = y + ((radius+6) * sin(angle));
        ofVertex(rx, ry);
    }
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
        
        //Make Circle Points
        float rx = x + ((radius-6)  * cos(angle));
        float ry = y + ((radius-6)  * sin(angle));
        ofVertex(rx, ry);
    }
    
    ofEndShape(true);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i],4);
    }
}
//--------------------------------------------------------------
void NeoPixelRing24px::drawRing(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ledRing();
    ofPopMatrix();
}