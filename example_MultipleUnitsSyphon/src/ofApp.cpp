#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);

    // Setup Units
    ring60px.setupLedRing();
    strip1.setupLedStrip(60, false);
    strip2.setupLedStrip(60, false);
    ring24pxlefteye.setupLedRing();
    ring24pxrighteye.setupLedRing();
    ring16px.setupLedRing();
    
    //setup our directory
	dir.setup();
    //setup our client
    client.setup();
    
    //register for our directory's callbacks
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    
    dirIdx = -1;
}
//--------------------------------------------------------------
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
}
//--------------------------------------------------------------
void ofApp::update()
{
    
    ofSetWindowTitle("ofxOPC:SyphonClient : FPS: "+ofToString(ofGetFrameRate()));
    
    ring60px.grabImageData(ofPoint(ofGetWidth()/2-100,ofGetHeight()/2-50));
    ring24pxlefteye.grabImageData(ofPoint(ofGetWidth()/2-100-200,ofGetHeight()/2-50));
    ring24pxrighteye.grabImageData(ofPoint(ofGetWidth()/2-100+200,ofGetHeight()/2-50));
    ring16px.grabImageData(ofPoint(ofGetWidth()/2-100,ofGetHeight()/2-50+200));

    strip1.grabImageData(ofPoint(ofGetWidth()/2-100-300,ofGetHeight()/2-50-30*5));

    strip2.grabImageData(ofPoint(ofGetWidth()/2-100+300,ofGetHeight()/2-50-30*5));
    
    ring60px.update();
    ring24pxlefteye.update();
    ring24pxrighteye.update();
    ring16px.update();
    strip1.update();
    strip2.update();
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else
    {
        // Write out the data
        opcClient.writeChannelOne(ring24pxlefteye.colorData());
        opcClient.writeChannelTwo(ring60px.colorData());
        opcClient.writeChannelThree(ring24pxrighteye.colorData());
        opcClient.writeChannelFour(ring16px.colorData());
        opcClient.writeChannelFive(strip1.colorData());
        opcClient.writeChannelSix(strip2.colorData());
    }
    opcClient.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    ofColor(255, 255, 255, 255);
    ofEnableAlphaBlending();
    
    if(dir.isValidIndex(dirIdx))
    {
        client.draw(0, 0,ofGetWidth()-200,ofGetHeight()-100);
    }
    
    ofPushStyle();
    // Visual Representation of the Grab Area
    ring60px.drawGrabRegion(true);
    ring24pxlefteye.drawGrabRegion(true);
    ring24pxrighteye.drawGrabRegion(true);
    ring16px.drawGrabRegion(true);
    strip1.drawGrabRegion(true);
    strip2.drawGrabRegion(true);
    
    // Show what the leds should be doing!
    ring60px.drawRing(ofGetWidth()-120, 60);
    ring24pxlefteye.drawRing(ofGetWidth()-140, 210);

    ring24pxrighteye.drawRing(ofGetWidth()-140, 310);
    ring16px.drawRing(ofGetWidth()-140, 410);
    strip1.drawStrip(ofGetWidth()-75, 165);
    strip2.drawStrip(ofGetWidth()-50, 165);
    ofPopStyle();
    ofDrawBitmapString("Press any key to cycle through all available Syphon servers.", ofPoint(20, ofGetHeight()-85));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //press any key to move through all available Syphon servers
    dirIdx++;
    if(dirIdx > dir.size() - 1)
        dirIdx = 0;
    
    client.set(dir.getDescription(dirIdx));
    string serverName = client.getServerName();
    string appName = client.getApplicationName();
    
    if(serverName == ""){
        serverName = "null";
    }
    if(appName == ""){
        appName = "null";
    }
    ofSetWindowTitle(serverName + ":" + appName);
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}
//-------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
//-------------------------------------------------------------
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}
//-------------------------------------------------------------
void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}
//-------------------------------------------------------------
void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}
