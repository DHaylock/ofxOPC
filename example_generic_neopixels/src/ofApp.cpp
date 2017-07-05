#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    hide = false;
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    
    // You define the stage size and draw into the stage
    opcClient.setupStage(500, 500);
    
    defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
    
    // Construct the objects
    neoPixelObjects.insert( std::pair<int, ofxNeoPixelObject*>(0,new ofxNeoPixelStrip(50, opcClient.getStageCenterY()-(30*5), 60, 5)) );
    neoPixelObjects.insert( std::pair<int, ofxNeoPixelObject*>(1,new ofxNeoPixelStrip(opcClient.getStageWidth()-50, opcClient.getStageCenterY()-(30*5), 60, 5)) );
    neoPixelObjects.insert( std::pair<int, ofxNeoPixelObject*>(2,new ofxNeoPixelRing(150, opcClient.getStageCenterY(), 24, 25)) );
    neoPixelObjects.insert( std::pair<int, ofxNeoPixelObject*>(3,new ofxNeoPixelRing(opcClient.getStageWidth()-150, opcClient.getStageCenterY(), 24, 25)) );
    neoPixelObjects.insert( std::pair<int, ofxNeoPixelObject*>(4,new ofxNeoPixelRing(opcClient.getStageCenterX(), opcClient.getStageCenterY(), 60, 50)) );
    neoPixelObjects.insert( std::pair<int, ofxNeoPixelObject*>(5,new ofxNeoPixelGrid(8, 8, opcClient.getStageCenterX()-(4*25)+(25/2), opcClient.getStageCenterY()-(4*25)+(25/2), 25)));
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("example_generic_neopixels");
    
    opcClient.update();
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    defaultEffects.draw(effect);
    opcClient.endStage();
    
    // Get Objects
    for (int i = 0; i < neoPixelObjects.size(); i++) {
        opcClient.getStagePixels(neoPixelObjects.at(i)->getPixelCoordinates(), neoPixelObjects.at(i)->colors);
    }

    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else {
        // Write out the first set of data
        for (int i = 0; i < neoPixelObjects.size(); i++)
		{
            opcClient.writeChannel(i+1, neoPixelObjects[i]->colorData());
        }
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    opcClient.drawStage(hide);

    for (int i = 0; i < neoPixelObjects.size(); i++) {
        neoPixelObjects[i]->drawGrabRegion(hide);
    }
    
    neoPixelObjects.at(0)->draw(opcClient.getStageWidth()+50, 40);
    neoPixelObjects.at(1)->draw(opcClient.getStageWidth()+75, 40);
    neoPixelObjects.at(2)->draw(opcClient.getStageWidth()+150, 300);
    neoPixelObjects.at(3)->draw(opcClient.getStageWidth()+225, 300);
    neoPixelObjects.at(4)->draw(opcClient.getStageWidth()+350, 300);
    neoPixelObjects.at(5)->draw(opcClient.getStageWidth()+125+(25/2), 40+(25/2));
    
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

