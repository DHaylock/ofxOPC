#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    
    effect = 0;
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    ring16px.setupLedRing();
    
    // Load the dot image
    dot.loadImage("dot.png");
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("ofxOPC NeoPixel16px: FPS: " +ofToString((int)(ofGetFrameRate())));
    
    ring16px.grabImageData(ofPoint(ofGetWidth()/2,ofGetHeight()/2));
    
    ring16px.update();
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
    }
    else
    {
        // Write out the first set of data
        opcClient.writeChannelOne(ring16px.colorData());
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    //Should be black otherwise the addon grabs the background pixels
    ofBackground(0);
    
    // As it says
    drawEffects(effect);
  
    // Visual Representation of the Grab Area
    ring16px.drawGrabRegion();
    
    // Show what the leds should be doing!
    ofFill();
    ofSetColor(100);
    ofRect(0,0,100,100);
    ring16px.drawRing(50, 50);
    
    // Report Messages
    ofDrawBitmapStringHighlight("Output", 1,115);
    ofDrawBitmapStringHighlight("Input Area", ofGetWidth()/2-35,ofGetHeight()/2+60);
    ofDrawBitmapStringHighlight("Press Left and Right to Change Effect Mode", 5,ofGetHeight()-15);
    ofDrawBitmapStringHighlight("Is the Client Connected: " + ofToString(opcClient.isConnected()), 5,ofGetHeight()-30);
}
//--------------------------------------------------------------
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
}
//--------------------------------------------------------------
void ofApp::drawEffects(int mode)
{
    switch (mode) {
        case 0:
        {
            // Mouse Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofCircle(mouseX,mouseY,30);
            ofPopStyle();
        }
            break;
            
        case 1:
        {
            // Like the processing example draw dot images and rotate
            int size = 70;
            ofPushMatrix();
            ofTranslate(0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-size,-size);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
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
            ofCircle(ofGetWidth()/2,ofGetHeight()/2,30);
            ofPopStyle();
        }
            break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofCircle(ofGetWidth()/2,ofGetHeight()/2,30);
            ofPopStyle();
        }
            break;
        case 4:
        {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            float rotationAmount = ofGetElapsedTimeMillis()/10;
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2-20, 20);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2+20, 20);
            ofPopMatrix();
            ofPopMatrix();
            ofDisableBlendMode();
        }
            break;
        default:
            break;
    }
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
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}