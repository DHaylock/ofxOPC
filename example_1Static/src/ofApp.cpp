#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
    pixelServer.close();
}
//--------------------------------------------------------------
void ofApp::setup()
{
    pixelServer.setup("127.0.0.1", 7980, ofVec2f(65,1));
}
//--------------------------------------------------------------
void ofApp::update()
{
    
    pixelServer.begin();
    ofSetColor(255, 255, 255);
    ofRect(mouseX, 0, 1, 1);
    pixelServer.end();
    
    pixelServer.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    pixelServer.draw();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

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
