//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxNeoPixelStrip.h"
#include "ofxNeoPixelRing.h"
#include "ofxNeoPixelGrid.h"

class Ring {
public:
    
    Ring() {}
    ~Ring() {}
    
    void respawn(int stageHeight,float x1,float y1,float x2,float y2) {
        
        _stageHeight = stageHeight;
        // Start at the newer mouse position
        x = x2;
        y = y2;
        
        // Intensity is just the distance between mouse points
        intensity = ofDist(x1, y1, x2, y2);
        
        // Hue is the angle of mouse movement, scaled from -PI..PI to 0..100
        hue = ofMap(atan2(y2 - y1, x2 - x1), -PI, PI, 0, 100);
        
        // Default size is based on the screen size
        size = _stageHeight * 0.1;
    }
    
    void draw(ofImage ringImage) {
        ofPushStyle();
        // Particles fade each frame
        intensity *= 0.95;
        
        // They grow at a rate based on their intensity
        size += _stageHeight * intensity * 0.01;
        
        // If the particle is still alive, draw it
        if (intensity >= 1) {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofColor c;
            c.setHsb(hue, 200, intensity);
            ofSetColor(c);
            ringImage.draw(x - size/2, y - size/2, size,size);
            ofDisableBlendMode();
        }
        ofPopStyle();
    }
private:
    float x, y, size, intensity, hue,_stageHeight;
};

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
        void drawDefaultEffects(int mode);
        ofImage dot;

        //! Set the FBOS Size
        void setupStage(int width, int height);
    
        // New Method of Accessing screen pixels
        //! Open Fbo
        void beginStage();
        //! Close Fbo
        void endStage();
        //! Draw Fbo
        void drawStage(bool drawGrid,int gridSpace = 50);
    
        int getStageWidth();
        int getStageHeight();
        int getStageCenterX();
        int getStageCenterY();
        ofPoint getStageCenter();
        ofPixels getStagePixels();
        void getStagePixels(vector<ofVec2f> pixels,vector <ofColor> &colorData);

    
        void cleanup();
        void close();
        bool isConnected();
        void tryConnecting();
        void retryConnecting();
        void sendFirmwareConfigPacket(); // Not used
    
        //! For writing custom channels
        void writeChannel(uint8_t channel, vector <ofColor> pix);
    
        //! Write Channels or Pin data
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
        ofTrueTypeFont labels;
    
        void connect();
        void disconnect();
        int moveCounter;
        ofFbo screenCapture;
        int _stageWidth;
        int _stageHeight;
        unsigned char * screenPixels;
    
        ofImage noiseImage;
        ofImage colorFadeImage;
        ofImage ringImage;
        deque<ofColor> gloriousColor;
        // For sending our data packets out to the Server
        ofxTCPClient client;
    
        Ring rings[100];
        float smoothX, smoothY;
    
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
        static const int CHANNEL_ONE = 1;
        static const int CHANNEL_TWO = 2;
        static const int CHANNEL_THREE = 3;
        static const int CHANNEL_FOUR = 4;
        static const int CHANNEL_FIVE = 5;
        static const int CHANNEL_SIX = 6;
        static const int CHANNEL_SEVEN = 7;
        static const int CHANNEL_EIGHT = 8;
};

