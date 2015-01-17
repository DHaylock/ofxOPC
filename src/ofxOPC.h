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
        void update();
        void draw();
    
        void cleanup();
        void close();
        bool isConnected();
        void tryConnecting();
        void retryConnecting();
        void sendFirmwareConfigPacket(); // Not used
    
        // For writing custom channels
        void writeChannel(uint8_t channel, vector <ofColor> pix);
    
        // Write Channels or Pin data
        void writeChannelOne(vector <ofColor> pix);
        void writeChannelTwo(vector <ofColor> pix);
        void writeChannelThree(vector <ofColor> pix);
        void writeChannelFour(vector <ofColor> pix);
        void writeChannelFive(vector <ofColor> pix);
        void writeChannelSix(vector <ofColor> pix);
        void writeChannelSeven(vector <ofColor> pix);
        void writeChannelEight(vector <ofColor> pix);
    
        //Chaining TODO:
        void writeChannel(uint8_t channel, vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelOne(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelTwo(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelThree(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelFour(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelFive(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelSix(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelSeven(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);
        void writeChannelEight(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3);

        string _address;
        int _port;
        int _w,_h;

    private:
    
        void connect();
        void disconnect();
    
        // For sending our data packets out to the Server
        ofxTCPClient client;
    
        // Reconnection Stuff
        float timer;
        bool tryReconnecting;
        float startTime;
        float endTime;
        int connectionAttempts;
    
        // Data Packets
        OPCPacket_t OPC_SPC_packet;
        size_t OPC_SPC_packet_length;
        OPCPacket_SPCData_t OPC_SPC_packet_data;
    
        // CHANNEL NUMBERS
        const int CHANNEL_ONE = 1;
        const int CHANNEL_TWO = 2;
        const int CHANNEL_THREE = 3;
        const int CHANNEL_FOUR = 4;
        const int CHANNEL_FIVE = 5;
        const int CHANNEL_SIX = 6;
        const int CHANNEL_SEVEN = 7;
        const int CHANNEL_EIGHT = 8;
};