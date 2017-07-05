//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
#include "ofMain.h"
#include "Effects.h"
#include "ofxNetwork.h"
#include "ofxNeoPixelStrip.h"
#include "ofxNeoPixelRing.h"
#include "ofxNeoPixelGrid.h"
#include "ofxNeoPixelCustomObject.h"

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
class ofxOPC
{
    public:
	
		//--------------------------------------------------------------
		/// \brief Setup Fadecandy
		/**
			@param string address : fadecandy address
			@param int port : fadycandy port
			@param int numberOfFadecandys : how many devices are attached to the server
		*/
		//--------------------------------------------------------------
		void setup(string address,int port,int _numberOfFadecandys = 1);
	
		//--------------------------------------------------------------
		/// \brief Setup without the Fadecandy
		/** */
		//--------------------------------------------------------------
		void setupWithoutFadecandy();
	
		//--------------------------------------------------------------
		/// \brief Update
		//--------------------------------------------------------------
		void update();
	
		//--------------------------------------------------------------
		/// \brief Draw
		//--------------------------------------------------------------
        void draw();

		//--------------------------------------------------------------
		/// \brief Setup the Pixel Stage
		/** 
			@param width : width of the stage
			@param height : height of the stage
		*/
		//--------------------------------------------------------------
        void setupStage(int width, int height);
    
        // New Method of Accessing screen pixels
		//--------------------------------------------------------------
		/// \brief Open the Pixel Stage Buffer
		//--------------------------------------------------------------
        void beginStage();
	
		//--------------------------------------------------------------
		/// \brief Close the Pixel Stage Buffer
		//--------------------------------------------------------------
        void endStage();
	
		//--------------------------------------------------------------
		/// \brief Draw Stage
		/**
			@param bool drawGrid : whether to draw the grid or not
			@param int gridSpace : size of the grid
		*/
		//--------------------------------------------------------------
        void drawStage(bool drawGrid,int gridSpace = 50);
	
		//--------------------------------------------------------------
		// \brief Get the Stage Width
		//--------------------------------------------------------------
        int getStageWidth();
	
		//--------------------------------------------------------------
		// \brief Get the Stage Height
		//--------------------------------------------------------------
		int getStageHeight();
	
		//--------------------------------------------------------------
		// \brief Get the Stage Center X
		//--------------------------------------------------------------
		int getStageCenterX();
	
		//--------------------------------------------------------------
		// \brief Get the Stage Center Y
		//--------------------------------------------------------------
		int getStageCenterY();
	
		//--------------------------------------------------------------
		// \brief Get the Stage Center
		//--------------------------------------------------------------
        ofPoint getStageCenter();
	
		//--------------------------------------------------------------
		// \brief Get a raw representation of the stage pixels
		//--------------------------------------------------------------
        ofPixels getStagePixels();
	
		//--------------------------------------------------------------
		// \brief Get the Stage pixels from specific points
		/**
			@param vector <ofPoint> pixels : position of pixels on the stage
			@param vector <ofColor> colorData : color data from the specific points on the stage
		*/
		//--------------------------------------------------------------
        void getStagePixels(vector<ofPoint> pixels,vector <ofColor> &colorData);

		//--------------------------------------------------------------
		/// \brief Setup Fadecandy?
		/** */
		//--------------------------------------------------------------
		void setFadecandyActive(bool active);
	
		//--------------------------------------------------------------
		/// \brief Clean Data
		//--------------------------------------------------------------
        void cleanup();
	
		//--------------------------------------------------------------
		/// \brief Close
		//--------------------------------------------------------------
        void close();
	
		//--------------------------------------------------------------
		/// \brief Are we connected to the Fadecandy
		//--------------------------------------------------------------
        bool isConnected();
	
		//--------------------------------------------------------------
		/// \brief Function that tries to reconnect
		//--------------------------------------------------------------
        void tryConnecting();
	
        void retryConnecting();
        void sendFirmwareConfigPacket(); // Not used
	
		//--------------------------------------------------------------
		/// \brief Splits the color data into automatically
		/**
			@param vector <ofColor> pix : color data to send
		*/
		//--------------------------------------------------------------
		void autoWriteData(vector <ofColor> pix);
	
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
    
    
        // Function to Chain the data together
        vector <ofColor> getChainedPixelData(vector<vector<ofColor> > colors);
    
        // Chain Three Units
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
        vector <string> error;
        int _port;
        int _w,_h;

    private:
        ofTrueTypeFont labels;
		int numberOfFadecandys;
        void connect();
        void disconnect();
        ofFbo screenCapture;
        int _stageWidth;
        int _stageHeight;
        unsigned char * screenPixels;
	
		bool bSetupWithFadecandy;
    
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
        static const int CHANNEL_ONE = 1;
        static const int CHANNEL_TWO = 2;
        static const int CHANNEL_THREE = 3;
        static const int CHANNEL_FOUR = 4;
        static const int CHANNEL_FIVE = 5;
        static const int CHANNEL_SIX = 6;
        static const int CHANNEL_SEVEN = 7;
        static const int CHANNEL_EIGHT = 8;
};

