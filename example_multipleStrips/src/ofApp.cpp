#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    effect = 0;
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);

    for (int i = 0; i <= 7; i++)
    {
        NeoPixelStrip strip;
        strip.setupLedStrip(60,false);
        strips.push_back(strip);
    }
    
    // Load the dot image
    dot.loadImage("dot.png");
    video.loadMovie("fingers.mov");
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("ofxOPC:MultipleNeoPixelStrip: FPS: " +ofToString((int)(ofGetFrameRate())));
    if (!strips.empty())
    {
        for (int i = 0; i <= 7; i++)
        {
            strips[i].grabImageData(ofPoint(ofGetWidth()/2-(4*25)+(i*25),ofGetHeight()/2-(30*5)));
            strips[i].update();
        }
    }
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
    }
    else
    {
        // Write out the first set of data
        if (!strips.empty())
        {
            for (int i = 0; i <= 7; i++)
            {
                //Offset to Channel One
                opcClient.writeChannel(i+1, strips[i].colorData());
            }
        }
    }
    video.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    //Should be black otherwise the addon grabs the background pixels
    ofBackground(0);
    
    // As it says
    drawEffects(effect);
    
    // Visual Representation of the Grab Area
    if (!strips.empty())
    {
        for (int i = 0; i <= 7; i++)
        {
            strips[i].drawGrabRegion(hide);
        }
    }
  
    if (!strips.empty())
    {
        for (int i = 0; i <= 7; i++)
        {
            strips[i].drawStrip(20+(i*25), 20);
        }
    }
    
    // Report Messages
    ofDrawBitmapStringHighlight("Output", 1,345);
    ofDrawBitmapStringHighlight("Input Area", ofGetWidth()/2-35,ofGetHeight()-50);
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
            ofCircle(mouseX,mouseY,40);
            ofPopStyle();
        }
        break;
            
        case 1:
        {
            // Like the processing example draw dot images and rotate
            int size = 300;
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
            ofRect(ofGetWidth()/2-110, ofGetHeight()/2-30*5, 200,300);
            ofPopStyle();
        }
        break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofRect(ofGetWidth()/2-110, ofGetHeight()/2-30*5, 200,300);
            ofPopStyle();
        }
        break;
        
        case 4:
        {
            ofPushStyle();
            
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofRect(ofGetWidth()/2-110,ofGetHeight()/2 + (int)(150 * sin(ofGetElapsedTimef()*3)),200,20);
            float hue1 = fmodf(ofGetElapsedTimef()*5,255);
            ofColor c1 = ofColor::fromHsb(hue1, 255, 255);
            ofSetColor(c1);
            ofRect(ofGetWidth()/2-110,ofGetHeight()/2 + (int)(150 * sin(ofGetElapsedTimef()*2)),200,20);
            float hue2 = fmodf(ofGetElapsedTimef(),255);
            ofColor c2 = ofColor::fromHsb(hue2, 255, 255);
            ofSetColor(c2);
            ofRect(ofGetWidth()/2-110,ofGetHeight()/2 + (int)(150 * sin(ofGetElapsedTimef()*1)),200,20);
            float hue3 = fmodf(ofGetElapsedTimef(),255);
            ofColor c3 = ofColor::fromHsb(hue3, 255, 255);
            ofSetColor(c3);
            ofRect(ofGetWidth()/2-110,ofGetHeight()/2 + (int)(150 * sin(ofGetElapsedTimef()*4)),200,20);
            ofDisableBlendMode();
            ofPopStyle();
        }
        break;
        
        case 5:
        {
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofEnableAlphaBlending();
            dot.draw(mouseX-100, mouseY-100, 200, 200);
            ofDisableAlphaBlending();
            ofPopStyle();
        }
        break;
    
        case 6:
        {
            ofPushStyle();
            
            ofSetColor(ofColor::white);
            video.draw(ofGetWidth()/2-160, ofGetHeight()/2-30*5, 320, 300);
            
            ofPopStyle();
            
        }
            
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