//
//  NeoPixelRing12px.cpp
//
//  Created by David Haylock on 27/05/2014.
//

#include "NeoPixelRing12px.h"

//--------------------------------------------------------------
void NeoPixelRing12px::setupLedRing()
{
    size = 12;
    x = 50; // Offset Value for grabber
    y = 50; // Offset Value for grabber
    radius = 23;
    
    pixels.allocate(radius*2+10, radius*2+10,GL_RGB);
    
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        
        // Generate the position of the grabber points
        float rx = x + (radius * cos(angle));
        float ry = y + (radius * sin(angle));
        
        pos.push_back(ofVec2f(rx,ry));
    }
}
//--------------------------------------------------------------
void NeoPixelRing12px::update()
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
vector <ofColor> NeoPixelRing12px::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
void NeoPixelRing12px::grabImageData(ofPoint grabPos)
{
    _pos = grabPos;
    img.clear();
    img.grabScreen(_pos.x-x, _pos.y-y,100,100);
    
    //Update the position of the ring pixels
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i] + ofVec2f(_pos.x,_pos.y);
    }
}
//--------------------------------------------------------------
void NeoPixelRing12px::drawGrabRegion(bool hideArea)
{
    if (hideArea == true)
    {
        // Draw Interaction Area
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(255, 255);
        ofCircle(_pos.x, _pos.y, radius+12);
        ofCircle(_pos.x, _pos.y, radius-12);
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

    ofCircle(_pos.x, _pos.y, radius+6);
    ofCircle(_pos.x, _pos.y, radius-6);
    
    for (int i = 0; i < pos.size(); i++)
    {
        ofCircle(pos[i]+ofVec2f(_pos.x-x, _pos.y-y),2);
    }
}
//--------------------------------------------------------------
void NeoPixelRing12px::ledRing()
{
    ofFill();
    ofSetColor(0, 175);
    ofBeginShape();
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
        
        //Make Circle Points
        float rx = x-x + ((radius+6)  * cos(angle));
        float ry = y-y + ((radius+6)  * sin(angle));
        ofVertex(rx, ry);
    }
    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size-1);
        
        //Make Circle Points
        float rx = x-x + ((radius-6)  * cos(angle));
        float ry = y-y + ((radius-6)  * sin(angle));
        ofVertex(rx, ry);
    }
    ofEndShape(true);
    
    for (int i = 0; i < size; i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(pos[i].x-x,pos[i].y-y,4);
    }
}
//--------------------------------------------------------------
void NeoPixelRing12px::drawRing(int x, int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(100);
    ofRect(-50,-50,100,100);
    ledRing();
    ofPopMatrix();
}