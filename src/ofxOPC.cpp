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
void ofxOPC::writeChannelOne(vector<ofColor>pix)
{
    // Bail early if there's no pixel data
    if(pix.size() <= 0) {
        return;
    }

    // Determine the length of the data section, as a multiple of the SPCData type
    uint16_t data_length = pix.size() * sizeof(OPCPacket_SPCData_t);

    // Add the header-section's length to the data-section's to determine the total packet length; allocate the packet
    size_t packet_length = sizeof(OPCPacket_Header_t) + data_length;
    OPCPacket_t packet = (OPCPacket_t)malloc(packet_length);
    
    // Fill out the header
    packet->header.channel = 0x00;
    packet->header.command = 0x00; // Set Pixel Colour
    packet->header.data_length = htons(data_length); // Convert the 16bit number into two bytes (High-, then Low-byte)
    
    // Create an alias for code-readability
    OPCPacket_SPCData_t data = (OPCPacket_SPCData_t)(&packet->data);
    
    // Copy the data
    for (int i = 0; i < pix.size(); i++) {
        data[i].r = pix[i].r;
        data[i].g = pix[i].g;
        data[i].b = pix[i].b;
    }
    
    // Send the data
    client.sendRawBytes((char *)(packet), packet_length);

    // Clean-up
    free(packet);
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
