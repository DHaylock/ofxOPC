#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    grid5x8.setupLedShield();
    
    // Load the dot image
    dot.loadImage("dot.png");
    movie.loadMovie("fingers.mov");
    movie.play();
    movie.setLoopState(OF_LOOP_NORMAL);
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("ofxOPC:NeoPixelShield5x8: FPS: " +ofToString((int)(ofGetFrameRate())));
    movie.update();
    grid5x8.grabImageData(ofPoint(ofGetWidth()/2-22,ofGetHeight()/2-32));
    
    grid5x8.update();
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else
    {
        // Write out the first set of data
        opcClient.writeChannelOne(grid5x8.colorData());
    }
    opcClient.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    //Should be black otherwise the addon grabs the background pixels
    ofBackground(0);
    
    // As it says
    drawEffects(effect);
    
    // Visual Representation of the Grab Area
    grid5x8.drawGrabRegion(hide);
    grid5x8.drawShield(30, 30);
    
    // Report Messages
    ofDrawBitmapStringHighlight("Output", 1,115);
    ofDrawBitmapStringHighlight("Input Area", ofGetWidth()/2-35,ofGetHeight()/2+120);
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
            ofRect(mouseX,mouseY,50,70);
            ofPopStyle();
        }
        break;
            
        case 1:
        {
            // Like the processing example draw dot images and rotate
            int size = 120;
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
            ofRect(ofGetWidth()/2-25,ofGetHeight()/2-35,40,60);
            ofPopStyle();
        }
        break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofRect(ofGetWidth()/2-25,ofGetHeight()/2-35,40,60);
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
            ofCircle(ofGetWidth()/2, ofGetHeight()/2-10, 20);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2+10, 20);
            ofPopMatrix();
            ofPopMatrix();
            ofDisableBlendMode();
            
        }
        break;
        case 5:
        {
            ofSetColor(255, 255,255);
            movie.draw(ofGetWidth()/2-30, ofGetHeight()/2-30, 60, 60);
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
    if (key == ' ') {
        hide = !hide;
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