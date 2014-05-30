//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
#include "ofxOPC.h"
//--------------------------------------------------------------
void ofxOPC::setup(string address, int port)
{
    // Copy the Address and port to the variables
    _port = port;
    _address = address;
    connectionAttempts = 0;
    tryReconnecting = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = 5000;// in milliseconds
    
    // Connect to the Server
    connect();
}
//--------------------------------------------------------------
void ofxOPC::update()
{
      timer = ofGetElapsedTimeMillis() - startTime;
}
//--------------------------------------------------------------
void ofxOPC::writeChannelOne(vector<ofColor>pix)
{
    // Bail early if there's no pixel data
    if(pix.empty())
    {
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
    for (int i = 0; i < pix.size(); i++)
    {
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
void ofxOPC::writeChannelTwo(vector<ofColor>pix)
{
    // Bail early if there's no pixel data
    if(pix.empty())
    {
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
    for (int i = 0; i < pix.size(); i++)
    {
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
    // Redundant unless color data needs to be drawn into strings
    // Or data about the connected unit
}
//--------------------------------------------------------------
bool ofxOPC::isConnected()
{
    bool _isThere = client.isConnected();
    return _isThere;
}
//--------------------------------------------------------------
void ofxOPC::tryConnecting()
{
    if (!client.isConnected())
    {
        if (connectionAttempts <= 3)
        {
            if(timer >= endTime && !tryReconnecting)
            {
                tryReconnecting = true;
                ofLog(OF_LOG_NOTICE, "Trying to Reconnect: Attempt "+ofToString(connectionAttempts));
                connect();
                startTime = ofGetElapsedTimeMillis();
                connectionAttempts++;
                tryReconnecting = false;
            }
            else
            {
                
            }
        }
    }
}
//--------------------------------------------------------------
void ofxOPC::retryConnecting()
{
    ofLog(OF_LOG_NOTICE, "Will Try Reconnecting");
    connectionAttempts = 0;
}
//--------------------------------------------------------------
void ofxOPC::connect()
{
    client.setup(_address, _port);
    ofLog(OF_LOG_NOTICE, "Opening Connection to Server @"+ofToString(_address)+ ":" + ofToString(_port));
    if (client.isConnected()) {
        ofLog(OF_LOG_NOTICE, "Connected to Server @"+ofToString(_address)+ ":" + ofToString(_port));
    }
}
//--------------------------------------------------------------
void ofxOPC::close()
{
    disconnect();
    ofLog(OF_LOG_NOTICE, "Closing Connection @"+ofToString(_address)+ ":" + ofToString(_port));
}
//--------------------------------------------------------------
void ofxOPC::disconnect()
{
    client.close();
}
