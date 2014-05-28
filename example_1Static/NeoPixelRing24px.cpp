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
    
    txPixels.allocate(size, 1, GL_RGB);
    pixels.allocate(radius*2+10, radius*2+10,GL_RGB);
    //txPixels.allocate(size, 1, GL_RGB);
    
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
vector <ofColor> NeoPixelRing24px::colorData()
{
    
    /*for (int i = 0; i < colors.size(); i++)
    {
        txPixels.setImageType(OF_IMAGE_COLOR);
        txPixels.setColor(i, 0, colors[i]);
    }*/
    //cout << txPixels.getPixels() <<endl;
    /*ofPushMatrix();
    ofScale(10, 10);
    for (int i = 0; i < colors.size(); i++)
    {
        ofFill();
        ofSetColor(colors[i]);
        ofRect(i, 0, 1, 1);
    }
    ofPopMatrix();*/
    //ias.clear();
    //txPixels.clear();
    //if (!colors.empty()) {
        
    
    //for (int i = 0; i < colors.size(); i++) {
    //    txPixels.setColor(i,1, colors[i]);
    //}
    //ias.setFromPixels(txPixels.getPixels(), 23, 1, OF_IMAGE_COLOR);
    //}
    /* unsigned char * data[3+size*3];
    uint8_t channel = 1;
    uint8_t ; = 0;
    uint8_t highByte = (colors.size()*3);
    uint8_t lowByte = 0;
    data[0] = &channel;
    data[1] = &commmand;
    data[2] = &highByte;
    data[3] = &lowByte;
    
    vector <uint8_t> date;
    
    for (int i = 0; i < colors.size();i++)
    {
        date.push_back(colors[i].r);
        date.push_back(colors[i].g);
        date.push_back(colors[i].b);
    }
    cout << &date << endl;*/
    //txPixels.clear();
    return colors;
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