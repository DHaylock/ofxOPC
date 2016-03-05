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
    
    // Setup the rings
    ring12px.setupLedRing(opcClient.getStageCenterX(),opcClient.getStageCenterY(), 12, 12);
    jewel.setupLedJewel(opcClient.getStageCenterX(),opcClient.getStageCenterY(), 28);
    ring16px.setupLedRing(opcClient.getStageCenterX(),opcClient.getStageCenterY(), 16, 48);
    ring24px.setupLedRing(opcClient.getStageCenterX(),opcClient.getStageCenterY(), 24, 70);
    ring60px.setupLedRing(opcClient.getStageCenterX(),opcClient.getStageCenterY(), 60, 100);

}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("example_ofxNeoPixelRings");
    opcClient.update();
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    
    // Draw what you want rendered here
    // For now here are some default effects
    defaultEffects.draw(effect);
    
    opcClient.endStage();
    
    // New Get Method
    opcClient.getStagePixels(ring12px.getPixelCoordinates(), ring12px.colors);
    opcClient.getStagePixels(ring16px.getPixelCoordinates(), ring16px.colors);
    opcClient.getStagePixels(ring24px.getPixelCoordinates(), ring24px.colors);
    opcClient.getStagePixels(ring60px.getPixelCoordinates(), ring60px.colors);
    opcClient.getStagePixels(jewel.getPixelCoordinates(), jewel.colors);
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else {
        // Write out the first set of data
        opcClient.writeChannelOne(ring12px.colorData());
        opcClient.writeChannelTwo(ring16px.colorData());
        opcClient.writeChannelThree(ring24px.colorData());
        opcClient.writeChannelFour(ring60px.colorData());
        opcClient.writeChannelFive(jewel.colorData());
    }
    

}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    opcClient.drawStage(hide);
    
    // Show the grabber area
    ring12px.drawGrabRegion(hide);
    ring16px.drawGrabRegion(hide);
    ring24px.drawGrabRegion(hide);
    ring60px.drawGrabRegion(hide);
    jewel.drawGrabRegion(hide);
    
    int x = opcClient.getStageWidth()+150;
    int y = 200;
    // Draw the output
    ring60px.draw(x,y);
    ring24px.draw(x,y);
    ring16px.draw(x,y);
    jewel.draw(x,y);
    ring12px.draw(x,y);
    
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
