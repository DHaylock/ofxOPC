//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
//
#include "ofxOPC.h"
//--------------------------------------------------------------
void ofxOPC::setup(string address, int port, ofVec2f layout)
{
    _port = port;
    _address = address;
    
    _w = layout.x;
    _h = layout.y;
    
    windowTexture.allocate(_w,_h+1,GL_RGBA);
    pixels.allocate(_w,_h,GL_RGBA);
    
    connect();
}
//--------------------------------------------------------------
void ofxOPC::setupLedRing(int size, float x, float y, float radius)
{
    
    ringTexture.allocate(radius*2, radius*2,GL_RGB);
    ringPixels.allocate(radius*2, radius*2,GL_RGB);
    
    
    _rw = x;
    _rh = y;
    _radius = radius;
    _size = size;
    for (int i = 0; i < _size; i++)
    {
        float angles = (1.0 * i) * (2.0 * M_PI)/(1.0 * _size);
        
        //Make Circle Points
        float xScale = x + (_radius * cos(angles));
        float yScale = y + (_radius * sin(angles));
        
        ringPos.push_back(ofVec2f(xScale,yScale));
    }
    
}
//--------------------------------------------------------------
void ofxOPC::update()
{
    ringColors.clear();
    ringPixels.clear();
    windowTexture.readToPixels(pixels);
    
    ringTexture.readToPixels(ringPixels);
    
    for (int i = 0; i < ringPos.size(); i++) {
        ringColors.push_back(ringPixels.getColor(ringPos[i].x, ringPos[i].y));
    }
}
//--------------------------------------------------------------
void ofxOPC::writeData()
{
    int totalPixels = _w*_h*3;
    unsigned char * decodePixels = pixels.getPixels();
    
    client.sendRawBytes((const char*)decodePixels,totalPixels);
    
    
    cout << decodePixels << endl;
    for (int i=0; i< _w; i++)
    {
    
        //uint8_t pixel[3] = { (colors[i].g >>1) | 0x00, (colors[i].r >> 1) | 0x00, (colors[i].b >> 1) | 0x00};
        //memcpy(&txData[4+(3*i)], pixel, 3);
        
    }
    //cout << colors[i] << endl;
    //client.send((char*)(txData.data()));
}
//--------------------------------------------------------------
void ofxOPC::begin()
{
    //windowTexture.begin();
    ringTexture.begin();
    ofClear(0,0,0,0);
}
//--------------------------------------------------------------
void ofxOPC::end()
{
    ringTexture.end();
    //windowTexture.end();
}
//--------------------------------------------------------------
void ofxOPC::draw()
{
    
    ringTexture.draw(0, 0);
    for (int i = 0; i < _size; i++) {
        ofDrawBitmapString(ofToString(ringColors[i]),10,115+(i*15)); // Change this to the Pixel Grab
    }
}
//--------------------------------------------------------------
bool ofxOPC::isConnected()
{
    bool _isThere = false;
    
    if (client.isConnected()) {
        _isThere = true;
    }
    else
    {
        _isThere = false;
    }
    return _isThere;
}
//--------------------------------------------------------------
void ofxOPC::connect()
{
    client.setup(_address, _port);
    ofLog(OF_LOG_NOTICE, "Opening Socket @ " + ofToString(_port));
}
//--------------------------------------------------------------
void ofxOPC::close()
{
    disconnect();
    ofLog(OF_LOG_NOTICE, "Closing Socket @ " + ofToString(_port));
}
//--------------------------------------------------------------
void ofxOPC::disconnect()
{
    client.close();
}
//--------------------------------------------------------------
void ofxOPC::ledStrip(int count, float x, float y, float spacing)
{
    
    
    
}
//--------------------------------------------------------------
void ofxOPC::ledRing(int count, float x, float y, float radius)
{
    for (int i = 0; i < count; i++)
    {
        ofFill();
        ofSetColor(ringColors[i]);
        ofCircle(ringPos[i],4);
        
        ofNoFill();
        ofSetColor(255,150);
        ofCircle(x, y, radius-6);
        ofCircle(x, y, radius+6);
    }
    ofRect(x-(radius)-5, y-(radius)-5, radius*2+10, radius*2+10);
}
//--------------------------------------------------------------
void ofxOPC::drawRing(int x, int y)
{
    
    ofPushMatrix();
    ofTranslate(x, y);
    ledRing( _size, _rw, _rh, _radius);
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofxOPC::ledGrid(int index, int stripLength, int numStrips, float x, float y,float ledSpacing, float stripSpacing, float angle, bool zigzag)
{
    

}
//--------------------------------------------------------------
void ofxOPC::ledGrid8x8(int index, float x, float y, float spacing, float angle, bool zigzag)
{
    
    
    
}
//--------------------------------------------------------------
void led(int index, int x, int y)
{
    /* For convenience, automatically grow the pixelLocations array. We do want this to be an array,
    // instead of a HashMap, to keep draw() as fast as it can be.
    if (pixelLocations == null) {
        pixelLocations = new int[index + 1];
    } else if (index >= pixelLocations.length) {
        pixelLocations = Arrays.copyOf(pixelLocations, index + 1);
    }
    
    pixelLocations[index] = x + width * y;*/
}
