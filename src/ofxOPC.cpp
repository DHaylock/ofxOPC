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
    
    windowTexture.allocate(_w,_h,GL_RGBA);
    pixels.allocate(_w,_h,GL_RGBA);
    
    connect();
}

//--------------------------------------------------------------
void ofxOPC::update()
{
    colors.clear();
    windowTexture.readToPixels(pixels);
    
    for (int i = 0; i < _w; i++) {
        colors.push_back(pixels.getColor(i, 0));
    }

    
    //pixels.clear();
}//--------------------------------------------------------------
void ofxOPC::writeData(vector<uint8_t> &data)
{
    
    for (int i=0; i< _w; i++)
    {
        uint8_t pixel[3] = { (colors[i].g >>1) | 0x00, (colors[i].r >> 1) | 0x00, (colors[i].b >> 1) | 0x00};
            
            cout << pixel[i] << endl;
    }
}
//--------------------------------------------------------------
void ofxOPC::begin()
{
    windowTexture.begin();
    ofClear(0,0,0,0);
}
//--------------------------------------------------------------
void ofxOPC::end()
{
    windowTexture.end();
}
//--------------------------------------------------------------
void ofxOPC::draw()
{
    
    ofPushMatrix();
    ofScale(4,20);
    ofFill();
    for (int i = 0; i< _w; i++) {
        ofSetColor(colors[i]); // Change this to the Pixel Grab
        ofRect(0+(i*1), 0, 1, 1);
    }

    ofSetColor(255);
    ofNoFill();
    ofRect(0,0,_w,_h);
    ofPopMatrix();

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

