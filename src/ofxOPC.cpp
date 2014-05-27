//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
//
#include "ofxOPC.h"
//--------------------------------------------------------------
void ofxOPC::setup(string address, int port)
{
    _port = port;
    _address = address;

    connect();
}

//--------------------------------------------------------------
void ofxOPC::update()
{
  
}
//--------------------------------------------------------------
void ofxOPC::writeChannelOne(ofPixels pix)
{
    
    client.sendRawBytes((const char *)(pix.getPixels()), 72);
  /*  unsigned char * outData[4+data.size()];
    uint8_t channel = 1;
    uint8_t commmand = 0;
    uint8_t highByte = (data.size());
    uint8_t lowByte = 0;
    outData[0] = &channel;
    outData[1] = &commmand;
    outData[2] = &highByte;
    outData[3] = &lowByte;
    if (!data.empty()) {
        
    
    for (int i = 0; i < data.size(); i+=3) {
        
        int offset = 4;
        
        
        packetData[offset] = (unsigned char*)(data[i] >> 16);
        packetData[offset + i + 1] = (unsigned char*)(data[i+1] >> 8);
        packetData[offset + i + 2] = (unsigned char*)(data[i+2]);
        
        //outData[4+i] = &data[i];
        //outData[4+i+1] = &data[i];
        //outData[4+i+2] = &data[i];
        //memcpy(&txData[4+(i*3)], &data, 3);
    }
    
    for (int i = 0; i < 76; i++) {
        cout << packetData[i] << endl;
    }
    
    
    }*/
    if (isConnected() == true) {
    
        
        //client.sendRawMsg((unsigned char*)(outData), data.size()+4);
    }
    else {
        //Nothing
        
    }
    
    //int totalPixels = _w*_h*3;


    //for (int i=0; i< _w; i++)
    //{
    
        //uint8_t pixel[3] = { (colors[i].g >>1) | 0x00, (colors[i].r >> 1) | 0x00, (colors[i].b >> 1) | 0x00};
        //memcpy(&txData[4+(3*i)], pixel, 3);
        
    //}
    //cout << colors[i] << endl;
    //client.send((char*)(txData.data()));
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
        connect();
        _isThere = false;
    }
    return _isThere;
}
//--------------------------------------------------------------
void ofxOPC::tryConnecting()
{
   
    
}
//--------------------------------------------------------------
void ofxOPC::connect()
{
    client.setup(_address, _port);
    //client.setup(_port);
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
