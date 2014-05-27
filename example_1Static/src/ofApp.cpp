#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
    pixelServer.close();
}
//--------------------------------------------------------------
void ofApp::setup()
{
    //pixelServer.setup("127.0.0.1", 7980, ofVec2f(24,1));
    //pixelServer.setupLedRing(24, 50, 50, 49);
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
    //pixelServer.begin();

    ring.grabImageData(ofRectangle(mouseX, mouseY, 100, 100));
    ring1.grabImageData(ofRectangle(mouseX, mouseY+100, 100, 100));
    ring2.grabImageData(ofRectangle(mouseX, mouseY+200, 100, 100));
    strip.grabImageData(ofRectangle(mouseX+200, mouseY, 10, 100));
    grid.grabImageData(ofRectangle(mouseX+400, mouseY, 70,70));
    shield.grabImageData(ofRectangle(mouseX+500, mouseY, 70,70));
    /*float hue1 = fmodf(ofGetElapsedTimef()*2.5,255);
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
    glVertex2f(100, 0);
    glColor3f(c2.r,c2.g,c2.b);
    glVertex2f(100, 100);
    glColor3f(c3.r,c3.g,c3.b);
    glVertex2f(0, 100);
    glColor3f(c4.r,c4.g,c4.b);
    glEnd();*/
    
    
  //  strip.begin();
   // ofSetColor(255,0,0);
   // ofRect(10,0,10,100);
    
   // strip.end();
    
    //strip.update();
    /*
    ofSetColor(255,0,0);
    ofRect(counter,0,2,100);
    ofSetColor(0, 255, 0);
    ofRect(counter-5,0,2,100);
    ofSetColor(0, 0, 255);
    ofRect(counter-10,0,2,100);*/
    
    //ofRect(ofGetWidth()/2-50, ofGetHeight()/2-50, 100,100);
    /*ofSetColor(255, 255, 255);
    ofPushMatrix();
    ofTranslate(mouseX, 0);
    for (int i = 0; i < 24; i++) {
        ofSetColor(255-(i*2), 0, 0+(i*3));
        ofRect(0+(i*1), 0, 1, 1);
    }
    ofPopMatrix();
    //ofRect(mouseX, 0, 1, 1);
    */
    //pixelServer.end();
    
    //pixelServer.update();
    ring.update();
    ring1.update();
    ring2.update();
    strip.update();
    grid.update();
    shield.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    drawGraphics(s);
    
    
    ring.drawRing(ofGetWidth()/2,ofGetHeight()/2);
    ring.drawGrabRegion();
    ring1.drawRing(ofGetWidth()/2+50,ofGetHeight()/2);
    ring1.drawGrabRegion();
    ring2.drawRing(ofGetWidth()/2+100,ofGetHeight()/2);
    ring2.drawGrabRegion();
    strip.drawStrip(100, 100);
    strip.drawGrabRegion();
    grid.drawGrid(200, 200);
    grid.drawGrabRegion();
    shield.drawShield(300, 300);
    shield.drawGrabRegion();
    //pixelServer.draw();
    //pixelServer.drawRing(ofGetWidth()/2,ofGetHeight()/2);
}
//--------------------------------------------------------------
void ofApp::drawGraphics(int mode)
{
    ofFill();
    switch (mode) {
        case 0:
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
                ofCircle(rx, ry, 8);
            }
            ofPopMatrix();
            ofPopMatrix();
            break;
        case 1:
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
            break;
            
        case 2:
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
