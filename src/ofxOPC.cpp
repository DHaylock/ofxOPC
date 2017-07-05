//
//  ofxOPC.cpp
//  openPixelControl
//
//  Created by David Haylock on 25/05/2014.
//
#include "ofxOPC.h"
//--------------------------------------------------------------
void ofxOPC::setup(string address, int port,int _numberOfFadecandys)
{
	numberOfFadecandys = _numberOfFadecandys;
	bSetupWithFadecandy = false;
    // Copy the Address and port to the variables
    _port = port;
    _address = address;

    // If this an example it will use this resource
    labels.load( "../../../resources/Verdana.ttf", 13);

    // If not it will searching the data directory for the resource5
    if (!labels.isLoaded()) {
        labels.load("Verdana.ttf", 13);
    }
    
    connectionAttempts = 0;
    tryReconnecting = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = 5000;// in milliseconds
    
    // Connect to the Server
    connect();
    
    // Determine the length of the data section, as a multiple of the SPCData type
    uint16_t data_length = (numberOfFadecandys * 8) * 64 * sizeof(OPCPacket_SPCData_t);
    
    // Add the header-section's length to the data-section's to determine the total packet length; allocate the packet
    OPC_SPC_packet_length = sizeof(OPCPacket_Header_t) + data_length;
    OPC_SPC_packet = (OPCPacket_t)malloc(OPC_SPC_packet_length);

    // Ensure all LEDs are initially off
    memset(&OPC_SPC_packet->data, 0, data_length);
    
    // Fill out the header
    OPC_SPC_packet->header.channel = 0x00;
    OPC_SPC_packet->header.command = 0x00; // Set Pixel Colour
    OPC_SPC_packet->header.data_length = htons(data_length); // Convert the 16bit number into two bytes (High-, then Low-byte)
    
    // Create an alias for code-readability
    OPC_SPC_packet_data = (OPCPacket_SPCData_t)(&OPC_SPC_packet->data);
}
//--------------------------------------------------------------
void ofxOPC::setupStage(int width,int height)
{
	// If this an example it will use this resource
	labels.load( "../../../resources/Verdana.ttf", 13);
	
	// If not it will searching the data directory for the resource5
	if (!labels.isLoaded())
	{
		labels.load("Verdana.ttf", 13);
	}
	
	connectionAttempts = 0;
	tryReconnecting = false;
	startTime = ofGetElapsedTimeMillis();  // get the start time
	endTime = 5000;// in
	
    _stageWidth = width;
    _stageHeight = height;
    
    screenPixels = new unsigned char [_stageWidth*_stageHeight*4];
    screenCapture.allocate(_stageWidth, _stageHeight,GL_RGBA);
    screenCapture.begin();
        ofClear(0);
    screenCapture.end();
}

//--------------------------------------------------------------
void ofxOPC::setFadecandyActive(bool active)
{
	bSetupWithFadecandy = active;
}

//--------------------------------------------------------------
void ofxOPC::beginStage()
{
    screenCapture.begin();
    ofPushStyle();
    ofFill();
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 0, _stageWidth, _stageHeight);
    ofPopStyle();
}
//--------------------------------------------------------------
void ofxOPC::endStage()
{
    glReadPixels(0, 0,screenCapture.getWidth(),screenCapture.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, screenPixels);
    screenCapture.end();
}
//--------------------------------------------------------------
int ofxOPC::getStageWidth()
{
    return _stageWidth;
}
//--------------------------------------------------------------
int ofxOPC::getStageHeight()
{
    return _stageHeight;
}
//--------------------------------------------------------------
int ofxOPC::getStageCenterX()
{
    return _stageWidth/2;
}
//--------------------------------------------------------------
int ofxOPC::getStageCenterY()
{
    return _stageHeight/2;
}
//--------------------------------------------------------------
ofPoint ofxOPC::getStageCenter()
{
    return ofPoint(_stageWidth/2,_stageHeight/2);
}
//--------------------------------------------------------------
ofPixels ofxOPC::getStagePixels()
{
    ofPixels tempPixs;
    tempPixs.setFromPixels(screenPixels, _stageWidth, _stageHeight, OF_IMAGE_COLOR_ALPHA);
    return tempPixs;
}
//--------------------------------------------------------------
void ofxOPC::getStagePixels(vector<ofPoint> pixels,vector <ofColor> &colorData)
{
    ofPixels tempPixs;
    tempPixs.setFromPixels(screenPixels, _stageWidth, _stageHeight, OF_IMAGE_COLOR_ALPHA);
    
    for (int i = 0; i < pixels.size(); i++)
	{
        if (pixels[i].x < 0 || pixels[i].x > getStageWidth() || pixels[i].y < 0 || pixels[i].y > getStageHeight())
		{
            error.push_back("Pixels are outside the Stage Area");
            return;
        }
        else
		{
            colorData.push_back(tempPixs.getColor(pixels[i].x, pixels[i].y));
        }
    }
}
//--------------------------------------------------------------
vector<ofColor> ofxOPC::getChainedPixelData(vector<vector<ofColor> > colors)
{
    vector<ofColor> returnData;
    for (int i = 0; i < colors.size(); i++)
	{
        for (int e = 0 ; e < colors[i].size(); e++)
		{
            returnData.push_back(colors[i][e]);
        }
    }
//    error.push_back(ofToString(returnData.size()));
    return returnData;
}
//--------------------------------------------------------------
void ofxOPC::drawStage(bool drawGrid,int gridSpace)
{
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(0, 0, _stageWidth, _stageHeight);
    ofFill();
    screenCapture.draw(0,0);
    ofSetColor(ofColor::white);
	
	stringstream ss;
	ss << "Input Stage" << endl;
	
	if (bSetupWithFadecandy)
	{
		string st = (isConnected()) ? "Fade Candy Connected " : "Fade Candy Not Connected";
		ss << st << endl;
	}
	
	
	for (int i = 0; i < error.size(); i++) ss << error[i] << endl;
	
    labels.drawString(ss.str(),10, _stageHeight+labels.getLineHeight());
    ofPopStyle();
    ofPopMatrix();
    
    if (drawGrid)
	{
        for (int y = 0; y < _stageHeight; y+=gridSpace)
		{
            for (int x = 0; x < _stageWidth; x+=gridSpace)
			{
                ofSetColor(50);
                ofDrawLine(x,0,x,_stageHeight);
                ofDrawLine(0,y,_stageWidth,y);
            }
        }
    }
}
//--------------------------------------------------------------
void ofxOPC::cleanup()
{
    // Clean-up
    free(OPC_SPC_packet);
}
//--------------------------------------------------------------
void ofxOPC::update()
{
    error.clear();
    timer = ofGetElapsedTimeMillis() - startTime;
}
//--------------------------------------------------------------
void ofxOPC::writeChannelOne(vector<ofColor>pix)
{
    writeChannel(CHANNEL_ONE, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelTwo(vector<ofColor>pix)
{
    writeChannel(CHANNEL_TWO, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelThree(vector<ofColor>pix)
{
    writeChannel(CHANNEL_THREE, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelFour(vector<ofColor>pix)
{
    writeChannel(CHANNEL_FOUR, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelFive(vector<ofColor>pix)
{
    writeChannel(CHANNEL_FIVE, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelSix(vector<ofColor>pix)
{
    writeChannel(CHANNEL_SIX, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelSeven(vector<ofColor>pix)
{
    writeChannel(CHANNEL_SEVEN, pix);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelEight(vector<ofColor>pix)
{
    writeChannel(CHANNEL_EIGHT, pix);
}

//--------------------------------------------------------------
void ofxOPC::autoWriteData(vector<ofColor>pix)
{
	// Bail early if there's no pixel data or there is too much data
	if(pix.empty())
	{
		ofLogError() << "No Data";
		return;
	}
	
	// If there is more than 64 pixels per channel limit the amount to 60
	if (pix.size() > 64)
	{
		int a = (int)(ofGetElapsedTimef()*100);
		int channelsToWriteTo = pix.size() / 64;
		if(a % 500 == 0) ofLogNotice() << "Auto Splitting " << channelsToWriteTo;
		
		for (int c = 1; c < channelsToWriteTo; c++)
		{
			uint8_t channel = c;
			uint16_t channel_offset = (channel - 1) * 64;
			for (unsigned int i = 0; i < 64; i++)
			{
				OPC_SPC_packet_data[channel_offset + i].r = pix[channel_offset+i].r;
				OPC_SPC_packet_data[channel_offset + i].g = pix[channel_offset+i].g;
				OPC_SPC_packet_data[channel_offset + i].b = pix[channel_offset+i].b;
			}
			client.sendRawBytes((char *)(OPC_SPC_packet), OPC_SPC_packet_length);
		}
	}
}

//--------------------------------------------------------------
void ofxOPC::writeChannel(uint8_t channel, vector<ofColor>pix)
{

    // Bail early if there's no pixel data or there is too much data
    if(pix.empty())
    {
        ofLogError() << "No Data";
        return;

    }
	else if(channel < 1 || channel > (8*numberOfFadecandys))
	{
		ofLogError() << "Channel Number "+ofToString(unsigned(channel))+" Exceeds Server Capacity";
        return;
    }

    uint16_t channel_offset = (channel - 1) * 64;
    // If there is more than 64 pixels per channel limit the amount to 60
    if (pix.size() > 64)
	{
        ofLogError() << "Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels";
        error.push_back("Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels");
        for (unsigned int i = 0; i < 64; i++)
		{
            OPC_SPC_packet_data[channel_offset + i].r = pix[i].r;
            OPC_SPC_packet_data[channel_offset + i].g = pix[i].g;
            OPC_SPC_packet_data[channel_offset + i].b = pix[i].b;
        }
    }
    else
	{
        for (unsigned int i = 0; i < pix.size(); i++)
		{
            OPC_SPC_packet_data[channel_offset + i].r = pix[i].r;
            OPC_SPC_packet_data[channel_offset + i].g = pix[i].g;
            OPC_SPC_packet_data[channel_offset + i].b = pix[i].b;
        }
    }
    
    // Send the data
    client.sendRawBytes((char *)(OPC_SPC_packet), OPC_SPC_packet_length);
}
//--------------------------------------------------------------
void ofxOPC::writeChannel(uint8_t channel, vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    pix1.insert(pix1.end(), pix2.begin(),pix2.end());
    pix1.insert(pix1.end(), pix3.begin(),pix3.end());
    
    // Bail early if there's no pixel data
    if(pix1.empty() && pix2.empty() && pix3.empty())
	{
        return;
    }
	else if(channel < 1 || channel > (8*numberOfFadecandys))
	{
		ofLogError() << "Channel Number "+ofToString(unsigned(channel))+" Exceeds Server Capacity";
		return;
	}
	
    uint16_t channel_offset = (channel - 1) * 64;

    // If there is more than 64 pixels per channel limit the amount to 60
    if (pix1.size() > 64)
	{
        ofLogError() << "Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels";
        error.push_back("Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels");
        for (unsigned int i = 0; i < 64; i++)
		{
            OPC_SPC_packet_data[channel_offset + i].r = pix1[i].r;
            OPC_SPC_packet_data[channel_offset + i].g = pix1[i].g;
            OPC_SPC_packet_data[channel_offset + i].b = pix1[i].b;
        }
    }
    else
	{
        for (unsigned int i = 0; i < pix1.size(); i++)
		{
            OPC_SPC_packet_data[channel_offset + i].r = pix1[i].r;
            OPC_SPC_packet_data[channel_offset + i].g = pix1[i].g;
            OPC_SPC_packet_data[channel_offset + i].b = pix1[i].b;
        }
    }
    
    // Send the data
    client.sendRawBytes((char *)(OPC_SPC_packet), OPC_SPC_packet_length);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelOne(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_ONE, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelTwo(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_TWO, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelThree(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_THREE, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelFour(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_FOUR, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelFive(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_FIVE, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelSix(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_SIX, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelSeven(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_SEVEN, pix1,pix2,pix3);
}
//--------------------------------------------------------------
void ofxOPC::writeChannelEight(vector <ofColor> pix1,vector <ofColor> pix2,vector <ofColor> pix3)
{
    writeChannel(CHANNEL_EIGHT, pix1,pix2,pix3);
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
    cleanup();
}
