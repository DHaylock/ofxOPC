//
//  ofxGenericNeoPixelObject.cpp
//
//  Created by David Haylock on 15/02/2016.
//
//

#include "ofxGenericNeoPixelObject.hpp"
//--------------------------------------------------------------
vector <ofColor> ofxGenericNeoPixelObject::colorData()
{
    // Transmit Data
    return colors;
}
//--------------------------------------------------------------
vector<ofVec2f> ofxGenericNeoPixelObject::getPixelCoordinates()
{
    colors.clear();
    return pos;
}
//--------------------------------------------------------------
void ofxGenericNeoPixelObject::drawGrabRegion(bool hideArea)
{
    
}
//--------------------------------------------------------------
void ofxGenericNeoPixelObject::draw(int x, int y)
{

}