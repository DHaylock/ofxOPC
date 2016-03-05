#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    
    // You define the stage size and draw into the stage
    opcClient.setupStage(500, 500);
    
    defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
    
    grid5x7.setupLedGrid(5, 7, 10, 10, 8);
    grid8x8.setupLedGrid(8, 8, 10+(7*8), 10, 8);
    grid32x32.setupLedGrid(32, 32, 10, 10+(10*8), 8);
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("example_ofxNeoPixelGrids");
    
    opcClient.update();
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    
    // Draw what you want rendered here
    // For now here are some default effects
    defaultEffects.draw(effect);
    
    opcClient.endStage();
    
    // New Get Method
    opcClient.getStagePixels(grid5x7.getPixelCoordinates(), grid5x7.colors);
    opcClient.getStagePixels(grid8x8.getPixelCoordinates(), grid8x8.colors);
    opcClient.getStagePixels(grid32x32.getPixelCoordinates(), grid32x32.colors);
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else {
        // Write out the first set of data
        opcClient.writeChannelOne(grid5x7.colorData());
        opcClient.writeChannelTwo(grid8x8.colorData());
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    opcClient.drawStage(hide);
    
    // Show the grabber area
    grid5x7.drawGrabRegion(hide);
    grid8x8.drawGrabRegion(hide);
    grid32x32.drawGrabRegion(hide);
    
    // Draw the output
    grid5x7.draw(opcClient.getStageWidth()+25, 25);
    grid8x8.draw(opcClient.getStageWidth()+25, 100);
    grid32x32.draw(opcClient.getStageWidth()+25, 175);
    
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