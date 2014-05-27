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

    connect();
}

//--------------------------------------------------------------
void ofxOPC::update()
{
  
}
//--------------------------------------------------------------
void ofxOPC::writeData()
{
    int totalPixels = _w*_h*3;


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
  
}
//--------------------------------------------------------------
void ofxOPC::end()
{
 
}
//--------------------------------------------------------------
void ofxOPC::draw()
{
    

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
