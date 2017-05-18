//
//  ofxNeoPixelObject.cpp
//
//  Created by David Haylock on 15/02/2016.
//
//

#include "ofxNeoPixelObject.h"
//--------------------------------------------------------------
vector <ofColor> ofxNeoPixelObject::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
vector<ofPoint> ofxNeoPixelObject::getPixelCoordinates()
{
    colors.clear();
    return pos;
}
//--------------------------------------------------------------
void ofxNeoPixelObject::drawGrabRegion(bool hideArea)
{
    
}
//--------------------------------------------------------------
void ofxNeoPixelObject::draw(int x, int y)
{

}
