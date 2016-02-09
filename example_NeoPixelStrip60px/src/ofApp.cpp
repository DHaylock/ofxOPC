#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);

    
    opcClient.setupStage(480, 480);
    // Load the dot image
    dot.load("dot.png");
    
    strip.setupLedStrip(opcClient.getStageCenterX(),opcClient.getStageCenterY()-(30*5),60, 5);
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("ofxOPC:NeoPixelRing60px: FPS: " +ofToString((int)(ofGetFrameRate())));
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else
    {
        // Write out the first set of data
        opcClient.writeChannelOne(strip.colorData());
    }
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    drawEffects(effect);
    opcClient.endStage();
    
    vector<ofColor> a;
    for (int i = 0; i < strip.pixelCoordinates().size(); i++) {
        a.push_back(opcClient.getStagePixels().getColor(strip.pixelCoordinates()[i].x, strip.pixelCoordinates()[i].y));
    }
    strip.setColors(a);
    
    opcClient.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    opcClient.drawStage();
    // Visual Representation of the Grab Area
    strip.drawGrabRegion(hide);
    
    // Show what the leds should be doing!
    strip.drawStrip(opcClient.getStageWidth(), 10);
    
    // Report Messages
    ofDrawBitmapStringHighlight("Output", 1,155);
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
            ofDrawCircle(mouseX,mouseY,70);
            ofPopStyle();
        }
            break;
            
        case 1:
        {
            // Like the processing example draw dot images and rotate
            int size = 160;
            ofPushMatrix();
            ofTranslate(0, 0);
            ofPushMatrix();
            ofTranslate(opcClient.getStageCenterX(),opcClient.getStageCenterY());
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
            ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,70);
            ofPopStyle();
        }
            break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,70);
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
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2-40, 40);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2+40, 40);
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
            dot.draw(mouseX-75, mouseY-75, 150,150);
            ofPopStyle();
        }
            break;
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == OF_KEY_LEFT)
    {
        effect--;
    }
    if (key == OF_KEY_RIGHT)
    {
        effect++;
    }
    if (key == ' ')
    {
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