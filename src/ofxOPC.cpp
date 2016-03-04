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
    
    moveCounter = 0;
    labels.load( "../../../resources/Verdana.ttf", 13);
    dot.load("../../../resources/dot.png");
    ringImage.load("../../../resources/ring.png");
    connectionAttempts = 0;
    tryReconnecting = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = 5000;// in milliseconds
    
    // Connect to the Server
    connect();
    
    // Determine the length of the data section, as a multiple of the SPCData type
    uint16_t data_length = 8 * 64 * sizeof(OPCPacket_SPCData_t);
    
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
    _stageWidth = width;
    _stageHeight = height;
    noiseImage.allocate(_stageWidth/4, _stageHeight/4, OF_IMAGE_GRAYSCALE);
    colorFadeImage.allocate(_stageWidth/4, _stageHeight/4, OF_IMAGE_COLOR_ALPHA);
 
    ofSetCircleResolution(200);
    
    for(int x = 0; x < noiseImage.getWidth(); x++) {
        for(int y = 0; y < noiseImage.getHeight(); y++) {
            ofColor initialColor = ofColor(255*ofNoise(x/100.0,y/100.0,ofGetElapsedTimef()),255);
            noiseImage.setColor((int)(x+y*noiseImage.getWidth()), initialColor);
        }
    }
    
    pos_y = 0;
    noiseImage.update();
    for(int y = 0; y < colorFadeImage.getHeight(); y++) {
        for(int x = 0; x < colorFadeImage.getWidth(); x++) {
            ofColor initialColor;
            int value = 255*(float)x/colorFadeImage.getWidth();
            initialColor.setHsb(value, 200, 200);
            colorFadeImage.setColor((int)(x+y*colorFadeImage.getWidth()), initialColor);
        }
    }
    colorFadeImage.update();
    screenPixels = new unsigned char [_stageWidth*_stageHeight*4];
    screenCapture.allocate(_stageWidth, _stageHeight,GL_RGBA);
    screenCapture.begin();
        ofClear(0);
    screenCapture.end();
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
void ofxOPC::getStagePixels(vector<ofVec2f> pixels,vector <ofColor> &colorData)
{
    ofPixels tempPixs;
    tempPixs.setFromPixels(screenPixels, _stageWidth, _stageHeight, OF_IMAGE_COLOR_ALPHA);
    
    for (int i = 0; i < pixels.size(); i++) {
        if (pixels[i].x < 0 || pixels[i].x > getStageWidth() || pixels[i].y < 0 || pixels[i].y > getStageHeight()) {
            error.push_back("Pixels are outside the Stage Area");
            return;
        }
        else {
            colorData.push_back(tempPixs.getColor(pixels[i].x, pixels[i].y));
        }
    }
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
    string st = (isConnected()) ? "Fade Candy Connected " : "Fade Candy Not Connected";
    ss << "Input Stage" << endl;
    ss << st << endl;
    for (int i = 0; i < error.size(); i++) {
        ss << error[i] << endl;
    }
    labels.drawString(ss.str(),10, _stageHeight+labels.getLineHeight());
    ofPopStyle();
    ofPopMatrix();
    
    if (drawGrid) {
        for (int y = 0; y < _stageHeight; y+=gridSpace) {
            for (int x = 0; x < _stageWidth; x+=gridSpace) {
                ofSetColor(255,100);
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
void ofxOPC::writeChannel(uint8_t channel, vector<ofColor>pix)
{
    // Bail early if there's no pixel data or there is too much data
    if(pix.empty())
    {
        ofLogError() << "No Data";
        return;

    } else if(channel < 1 || channel > 8) {
        // TODO: Emit error
        return;
    }

    uint16_t channel_offset = (channel - 1) * 64;
    // If there is more than 64 pixels per channel limit the amount to 60
    if (pix.size() > 64) {
        ofLogError() << "Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels";
        error.push_back("Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels");
        for (unsigned int i = 0; i < 64; i++) {
            OPC_SPC_packet_data[channel_offset + i].r = pix[i].r;
            OPC_SPC_packet_data[channel_offset + i].g = pix[i].g;
            OPC_SPC_packet_data[channel_offset + i].b = pix[i].b;
        }
    }
    else {
        for (unsigned int i = 0; i < pix.size(); i++) {
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
        
    } else if(channel < 1 || channel > 8) {
        // TODO: Emit error
        return;
    }
    
    uint16_t channel_offset = (channel - 1) * 64;

    // If there is more than 64 pixels per channel limit the amount to 60
    if (pix1.size() > 64) {
        ofLogError() << "Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels";
        error.push_back("Too Much Data on Channel: "+ofToString(unsigned(channel))+" Limiting to 64 pixels");
        for (unsigned int i = 0; i < 64; i++) {
            OPC_SPC_packet_data[channel_offset + i].r = pix1[i].r;
            OPC_SPC_packet_data[channel_offset + i].g = pix1[i].g;
            OPC_SPC_packet_data[channel_offset + i].b = pix1[i].b;
        }
    }
    else {
        for (unsigned int i = 0; i < pix1.size(); i++) {
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
//--------------------------------------------------------------
void ofxOPC::drawDefaultEffects(int mode)
{
    switch (mode) {
        case 0:
        {
            // Mouse Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofDrawCircle(ofGetMouseX(),ofGetMouseY(),70);
            ofPopStyle();
        }
            break;
            
        case 1:
        {
            // Like the processing example draw dot images and rotate
            int size = (_stageWidth+_stageHeight)/2;
            ofPushMatrix();
            ofTranslate(0, 0);
            ofPushMatrix();
            ofTranslate(getStageCenterX(),getStageCenterY());
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-size,-size);
            ofEnableBlendMode(OF_BLENDMODE_SCREEN);
            ofSetColor(0, 255,20);
            dot.draw(size/4, size/4, size,size);
            ofSetColor(255, 0,20);
            dot.draw((size/4*3), size/4, size,size);
            ofSetColor(0, 0,255);
            dot.draw(size/4, (size/4*3), size,size);
            ofSetColor(255, 0,255);
            dot.draw((size/4*3),(size/4*3), size,size);
            ofDisableBlendMode();
            ofPopMatrix();
            ofPopMatrix();
            ofPopMatrix();
        }
            break;
            
        case 2:
        {
            // Changes the color of a Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofDrawRectangle(0,0,_stageWidth,_stageHeight);
            ofPopStyle();
        }
            break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofDrawRectangle(0,0,_stageWidth,_stageHeight);
            ofPopStyle();
        }
            break;
            
        case 4:
        {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            float rotationAmount = ofGetElapsedTimeMillis()/10;
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            ofTranslate(getStageCenterX(), getStageCenterY());
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-getStageCenterX(), -getStageCenterY());
            ofDrawCircle(getStageCenterX(), getStageCenterY()-40, 40);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(getStageCenterX(), getStageCenterY());
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-getStageCenterX(), -getStageCenterY());
            ofDrawCircle(getStageCenterX(), getStageCenterY()+40, 40);
            ofPopMatrix();
            ofPopMatrix();
            ofDisableBlendMode();
        }
            break;
            
        case 5:
        {
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            dot.draw(ofGetMouseX()-75, ofGetMouseY()-75, 150,150);
            ofPopStyle();
        }
            break;
        case 6:
        {
            float rotationAmount = ofGetElapsedTimeMillis()/5;
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            ofTranslate(getStageCenterX(), getStageCenterY());
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-getStageCenterX(), -getStageCenterY());
            int w = (int)(28 + 128 * sin(ofGetElapsedTimef()));
            ofDrawRectangle(getStageCenterX()-(w/2), getStageCenterY()-_stageHeight, w, _stageHeight*2);
            ofPopMatrix();
            ofPopMatrix();
        }
            break;
        case 7:
        {
            if (moveCounter < -labels.getStringBoundingBox("Hello World", 0, 0).width) {
                moveCounter = _stageWidth;
            }
            else {
                moveCounter--;
            }
            
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            ofScale(4, 4);
            ofTranslate(moveCounter, _stageHeight/8);
            labels.drawString("Hello World", 0, 0);
            ofPopMatrix();
        }
            break;
        case 8:
        {
            for(int x = 0; x < noiseImage.getWidth(); x++) {
                for(int y = 0; y < noiseImage.getHeight(); y++) {
                    ofColor initialColor = ofColor(255*ofNoise(x/100.0,y/100.0,ofGetElapsedTimef()),255);
                    noiseImage.setColor((int)(x+y*noiseImage.getWidth()), initialColor);
                }
            }
            noiseImage.update();
            ofPushMatrix();
            ofScale(4, 4);
            ofSetColor(255, 255, 255);
            noiseImage.draw(0, 0);
            ofPopMatrix();
        }
            break;
        case 9:
        {
            float prevX = smoothX;
            float prevY = smoothY;
            smoothX += (ofGetMouseX() - smoothX) * 0.1;
            smoothY += (ofGetMouseY() - smoothY) * 0.1;
            
            // At every frame, randomly respawn one ring
            rings[int(ofRandom(100))].respawn(getStageHeight(),prevX, prevY, smoothX, smoothY);
            
            // Give each ring a chance to redraw and update
            for (int i = 0; i < 100; i++) {
                rings[i].draw(ringImage);
            }
        }
            break;
        case 10:
        {
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            int x = (int)(getStageWidth()/2 + getStageWidth()/2 * sin(ofGetElapsedTimef()));
            int x1 = (int)(getStageWidth()/2 + getStageWidth()/2 * sin(ofGetElapsedTimef()*2));
            int x2 = (int)(getStageWidth()/2 + getStageWidth()/2 * sin(ofGetElapsedTimef()*4));
            int w = (int)(35 + 30 * sin(ofGetElapsedTimef()*0.6));
            ofDrawRectangle(x, getStageCenterY()-_stageHeight, w, _stageHeight*2);
            ofDrawRectangle(x1, getStageCenterY()-_stageHeight, w, _stageHeight*2);
            ofDrawRectangle(x2, getStageCenterY()-_stageHeight, w, _stageHeight*2);
            ofPopMatrix();
        }
            break;
        case 11:
        {
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            int y = (int)(getStageHeight()/2 + getStageHeight()/2 * sin(ofGetElapsedTimef()));
            int y1 = (int)(getStageHeight()/2 + getStageHeight()/2 * sin(ofGetElapsedTimef()*2));
            int y2 = (int)(getStageHeight()/2 + getStageHeight()/2 * sin(ofGetElapsedTimef()*4));
            int h = (int)(35 + 30 * sin(ofGetElapsedTimef()*0.6));
            ofDrawRectangle(getStageCenterX()-(_stageWidth/2), y, _stageWidth, h);
            ofDrawRectangle(getStageCenterX()-(_stageWidth/2), y1, _stageWidth, h);
            ofDrawRectangle(getStageCenterX()-(_stageWidth/2), y2, _stageWidth, h);
            ofPopMatrix();
        }
            break;
        case 12:
        {
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            int x = (int)(getStageWidth()/2 + getStageWidth()/2 * sin(ofGetElapsedTimef()));
            int w = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()*0.6));
            ofDrawRectangle(0, getStageCenterY()-_stageHeight, w, _stageHeight*2);
            ofPopMatrix();
        }
            break;
        case 13:
        {
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofPushMatrix();
            int h = (int)(_stageHeight/2 + _stageHeight/2 * sin(ofGetElapsedTimef()*0.6));
            ofDrawRectangle(0, 0, _stageWidth, h);
            ofPopMatrix();
        }
            break;
        case 14:
        {
            
            ofPushMatrix();
            ofPushStyle();
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            int linesInterval = getStageHeight()/2;
            int step = 255/linesInterval;
            int indents = getStageHeight()/linesInterval;
            pos_y = int(ofGetElapsedTimef()*32);
            for (int y = 0; y < getStageHeight(); y++) {
                
                ofColor c = ofColor::fromHsb((pos_y+y*step)%255, 255, 255);
                ofSetColor(c);
                ofDrawRectangle(0, y, _stageWidth, y);
            }
            ofDisableBlendMode();
            ofPopMatrix();
            ofPopStyle();
        }
            break;
        default:
            break;
    }
}
