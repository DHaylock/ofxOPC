#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
    pixelServer.close();
}
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    pixelServer.setup("127.0.0.1", 7890);
    counter = 0;
    s =0;
    ring.setupLedRing();
    ring1.setupLedRing();
    ring2.setupLedRing();
    strip.setupLedStrip(60);
    grid.setupLedGrid();
    shield.setupLedShield();
    
    
    //ofEnableAlphaBlending();
}
//--------------------------------------------------------------
void ofApp::update()
{
   
    if (counter >= ofGetWidth()) {
        counter = 0;
    }
    else{
        counter++;
    }
    
    ring.grabImageData(ofRectangle(100, 100, 100, 100));
    ring1.grabImageData(ofRectangle(100, 200, 100, 100));
    ring2.grabImageData(ofRectangle(100, 300,100, 100));
    strip.grabImageData(ofRectangle(200,100, 10, 100));
    grid.grabImageData(ofRectangle(250, 100, 70,70));
    shield.grabImageData(ofRectangle(350, 100, 70,70));
 

    ring.update();
    ring1.update();
    ring2.update();
    strip.update();
    grid.update();
    shield.update();
    
    
    pixelServer.writeChannelOne(ring.colorData());
    //cout << ring.colorData() << endl; //
}
//--------------------------------------------------------------
void ofApp::draw()
{
    
    ofBackground(100);
    drawGraphics(s);
    ofFill();
    ofSetColor(100,175);
    ofRect(ofGetWidth()-200,0,200,ofGetHeight());
    
    ring.drawRing(ofGetWidth()-100,50);
    ring.drawGrabRegion();
    ring1.drawRing(ofGetWidth()-100,120);
    ring1.drawGrabRegion();
    ring2.drawRing(ofGetWidth()-100,180);
    ring2.drawGrabRegion();
    strip.drawStrip(ofGetWidth()-180,50);
    strip.drawGrabRegion();
    grid.drawGrid(ofGetWidth()-150,300);
    grid.drawGrabRegion();
    shield.drawShield(ofGetWidth()-150,400);
    shield.drawGrabRegion();
    
    
    //ring.colorData();
    //pixelServer.draw();
    //pixelServer.drawRing(ofGetWidth()/2,ofGetHeight()/2);
}
//--------------------------------------------------------------
void ofApp::drawGraphics(int mode)
{
    ofFill();
    switch (mode)
    {
        case 0:
        {
            ofPushMatrix();
            ofTranslate(50, 50);
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-50, -50);
            for (int i = 0; i < 24; i++)
            {
                float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * 24);
                
                //Make Circle Points
                float rx = 50 + (50 * cos(angle));
                float ry = 50 + (50 * sin(angle));
                ofSetColor(0+(i*10), 0, 255-(i*10));
                ofCircle(rx, ry,8);
            }
            ofPopMatrix();
            ofPopMatrix();
        }
            break;
        case 1:
        {
            ofPushMatrix();
            ofTranslate(50, 50);
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-50, -50);
            for (int i = 0; i < 24; i++)
            {
                float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * 24);
                
                //Make Circle Points
                float rx = 50 + (50 * cos(angle));
                float ry = 50 + (50 * sin(angle));
                ofSetColor(0,255-(i*10), 255-(i*10));
                ofCircle(rx, ry, 8);
            }
            ofPopMatrix();
            ofPopMatrix();
        }
            break;
            
        case 2:
        {
            ofPushMatrix();
            float hue1 = fmodf(ofGetElapsedTimef()*2.5,255);
            float hue2 = fmodf(ofGetElapsedTimef()*5.0,255);
            float hue3 = fmodf(ofGetElapsedTimef()*7.5,255);
            float hue4 = fmodf(ofGetElapsedTimef()*10,255);
                  
          
             ofFloatColor c1 = ofColor::fromHsb(hue1, 255, 255);
             ofFloatColor c2 = ofColor::fromHsb(hue2, 255, 255);
             ofFloatColor c3 = ofColor::fromHsb(hue3, 255, 255);
             ofFloatColor c4 = ofColor::fromHsb(hue4, 255, 255);
            
             glBegin(GL_QUADS);
             glVertex2f(0, 0);
             glColor3f(c1.r,c1.g,c1.b);
             glVertex2f(ofGetWidth(), 0);
             glColor3f(c2.r,c2.g,c2.b);
             glVertex2f(ofGetWidth(), ofGetHeight());
             glColor3f(c3.r,c3.g,c3.b);
             glVertex2f(0, ofGetHeight());
             glColor3f(c4.r,c4.g,c4.b);
             glVertex2f(0, 0);
             glColor3f(c1.r,c1.g,c1.b);
             glEnd();
            ofPopMatrix();
        }
            break;
            
        case 3:
        {
            ofPushStyle();
            ofSetLineWidth(5);
            ofSetColor(255, 255);
            ofLine(counter, 0, counter, ofGetHeight());
            ofPopStyle();
        }
        break;
        case 4:
        {
            ofPushStyle();
            ofSetLineWidth(5);
            ofSetColor(255, 255);
            ofLine(0, counter, counter, 0);
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
    if (key == OF_KEY_LEFT) {
        s--;
    }
    if (key == OF_KEY_RIGHT) {
        s++;
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
