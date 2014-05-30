//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxNeoPixels.h"

//------------------------------------------------------------------------------
typedef struct OPCPacket_Header {
    // Standard OPC-packet header
    uint8_t channel;
    uint8_t command;
    uint16_t data_length;
} OPCPacket_Header_t;
//------------------------------------------------------------------------------
typedef struct OPCPacket_SPCData {
    // OPC "Set Pixel Colours" data structure
    unsigned char r;
    unsigned char g;
    unsigned char b;
} *OPCPacket_SPCData_t;
//------------------------------------------------------------------------------
typedef struct OPCPacket_SEData {
    // OPC "System Exlcusive" data structure
    uint16_t system_id;
    uint16_t command_id;
    unsigned char payload[];
} *OPCPacket_SEData_t;
//------------------------------------------------------------------------------
typedef struct OPCPacket {
    // An amalgamation of a header and a data-section
    OPCPacket_Header_t header;
    unsigned char data[];
} *OPCPacket_t;

//--------------------------------------------------------------
class ofxOPC  {
    
    public:
        void setup(string address,int port);
        void close();
        void sendFirmwareConfigPacket();
        
        void draw();
        void update();
        
        void writeChannelOne(vector <ofColor> pix);
        void writeChannelTwo(vector <ofColor> pix);
    
        bool isConnected();
        void tryConnecting();
        void retryConnecting();
    
        vector <ofColor> colors;
        string _address;
        int _port;
        int _w,_h;
        
    private:
        void connect();
        void disconnect();
        
        ofxTCPClient client;
        float timer;
        bool tryReconnecting;
        float startTime;
        float endTime;
        int connectionAttempts;
};