#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    
    // You define the stage size and draw into the stage
    opcClient.setupStage(480, 480);
    
    stick.setupLedStrip(10, 10, 8, 7);
    strip40px.setupLedStrip(50,10, 40, 7);
    strip60px.setupLedStrip(100,10, 60, 7);
    strip144px.setupLedStrip(150,10, 144, 3);
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("example_ofxNeoPixelStrips");
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    
    // Draw what you want rendered here
    
    // For now here are some default effects
    opcClient.drawDefaultEffects(effect);
    
    opcClient.endStage();
    
    // New Get Method
    opcClient.getStagePixels(stick.getPixelCoordinates(), stick.colors);
    opcClient.getStagePixels(strip40px.getPixelCoordinates(), strip40px.colors);
    opcClient.getStagePixels(strip60px.getPixelCoordinates(), strip60px.colors);
    opcClient.getStagePixels(strip144px.getPixelCoordinates(), strip144px.colors);
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else {
        // Write out the first set of data
        opcClient.writeChannelOne(stick.colorData());
        opcClient.writeChannelTwo(strip40px.colorData());
        opcClient.writeChannelThree(strip60px.colorData());
    }
    
    opcClient.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    opcClient.drawStage();
    
    // Show the grabber area
    stick.drawGrabRegion(hide);
    strip40px.drawGrabRegion(hide);
    strip60px.drawGrabRegion(hide);
    strip144px.drawGrabRegion(hide);
    
    // Draw the output
    stick.drawStrip(opcClient.getStageWidth()+50, 10);
    strip40px.drawStrip(opcClient.getStageWidth()+70, 10);
    strip60px.drawStrip(opcClient.getStageWidth()+100, 10);
    strip144px.drawStrip(opcClient.getStageWidth()+130, 10);
    
    // Report Messages
    stringstream ss;
    ss << "Press Left and Right to Change Effect Mode" << endl;
    ss << "FPS: " << ofToString((int)(ofGetFrameRate())) << endl;
    ofDrawBitmapStringHighlight(ss.str(), 5,ofGetHeight()-30);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == OF_KEY_LEFT) {
        effect--;
    }
    if (key == OF_KEY_RIGHT) {
        effect++;
    }
    if (key == ' ') {
        hide = !hide;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}
//--------------------------------------------------------------
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
}