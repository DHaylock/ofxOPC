        #include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    hide = false;
    syphonActive = false;
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    
    // You define the stage size and draw into the stage
    opcClient.setupStage(500, 500);
    
    defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
    
    //Construct the objects
    leftStrip.setupLedStrip(50, opcClient.getStageCenterY()-(30*5), 60, 5);
    rightStrip.setupLedStrip(opcClient.getStageWidth()-50, opcClient.getStageCenterY()-(30*5), 60, 5);
    leftRing.setupLedRing(150, opcClient.getStageCenterY(), 24, 25);
    rightRing.setupLedRing(opcClient.getStageWidth()-150, opcClient.getStageCenterY(), 24, 25);
    centerRing.setupLedRing(opcClient.getStageCenterX(), opcClient.getStageCenterY(), 60, 50);
    centerGrid.setupLedGrid(8, 8, opcClient.getStageCenterX()-(4*25)+(25/2), opcClient.getStageCenterY()-(4*25)+(25/2), 25);
    
    // Setup Syphon
    dir.setup();
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    
    directoryId = -1;
    
    syphonClient.setup();
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("example_syphon_input");
    
    opcClient.update();
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    if (syphonActive) {
        if (dir.isValidIndex(directoryId))
            ofEnableAlphaBlending();
            ofSetColor(ofColor::white);
            syphonClient.draw(0, 0);
    }
    else {
        defaultEffects.draw(effect);
    }

    opcClient.endStage();
    
    // Get Strips
    opcClient.getStagePixels(leftStrip.getPixelCoordinates(), leftStrip.colors);
    opcClient.getStagePixels(rightStrip.getPixelCoordinates(), rightStrip.colors);
    
    // Get Rings
    opcClient.getStagePixels(leftRing.getPixelCoordinates(), leftRing.colors);
    opcClient.getStagePixels(rightRing.getPixelCoordinates(), rightRing.colors);
    opcClient.getStagePixels(centerRing.getPixelCoordinates(), centerRing.colors);
    
    // Get Grid
    opcClient.getStagePixels(centerGrid.getPixelCoordinates(), centerGrid.colors);
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else {
        // Write out the first set of data
        opcClient.writeChannelOne(leftRing.colorData());
        opcClient.writeChannelTwo(rightRing.colorData());
        opcClient.writeChannelThree(centerRing.colorData());
        opcClient.writeChannelFour(leftStrip.colorData());
        opcClient.writeChannelFive(rightStrip.colorData());
        opcClient.writeChannelSix(centerGrid.colorData());
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    opcClient.drawStage(hide);
    
    leftRing.drawGrabRegion(hide);
    rightRing.drawGrabRegion(hide);
    centerRing.drawGrabRegion(hide);
    leftStrip.drawGrabRegion(hide);
    rightStrip.drawGrabRegion(hide);
    centerGrid.drawGrabRegion(hide);
    
    leftRing.draw(opcClient.getStageWidth()+40, 40);
    rightRing.draw(opcClient.getStageWidth()+120, 40);
    centerRing.draw(opcClient.getStageWidth()+75, 150);
    leftStrip.draw(opcClient.getStageWidth()+225, 25);
    rightStrip.draw(opcClient.getStageWidth()+250, 25);
    centerGrid.draw(opcClient.getStageWidth()+40, 250);
    
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
    if (key == 's') {
        syphonActive = !syphonActive;
    }
    if (key == 'c') {
        //press any key to move through all available Syphon servers
        if (dir.size() > 0)
        {
            directoryId++;
            if(directoryId > dir.size() - 1)
                directoryId = 0;
            
            syphonClient.set(dir.getDescription(directoryId));
            string serverName = syphonClient.getServerName();
            string appName = syphonClient.getApplicationName();
            
            if(serverName == ""){
                serverName = "null";
            }
            if(appName == ""){
                appName = "null";
            }
        }
        else
        {

        }
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
//--------------------------------------------------------------
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    directoryId = 0;
}
//--------------------------------------------------------------
void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    directoryId = 0;
}
//--------------------------------------------------------------
void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    directoryId = 0;
}
