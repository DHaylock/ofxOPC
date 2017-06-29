//
//  ofxNeoPixelCustomObject.cpp
//
//  Created by David Haylock on 17/05/2017.
//
//

#include "ofxNeoPixelCustomObject.h"

//--------------------------------------------------------------
ofxNeoPixelCustomObject::ofxNeoPixelCustomObject()
{
	
}
//--------------------------------------------------------------
ofxNeoPixelCustomObject::~ofxNeoPixelCustomObject()
{
	
}
//--------------------------------------------------------------
ofxNeoPixelCustomObject::ofxNeoPixelCustomObject(int offsetx, int offsety,vector<ofPoint> positions,int numberOfLeds,int spacing)
{
	// Setup Positioning
	size = numberOfLeds;
	offsetX = 5;
	offsetY = 5;
	_spacing = spacing;
	
	actualX = offsetX+offsetx;
	actualY = offsetY+offsety;

	pos = positions;
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for (unsigned int i = 1; i < pos.size(); i++)
	{
		ofPoint thisPoint = pos[i-1];
		ofPoint nextPoint = pos[i];
		ofPoint direction = (nextPoint - thisPoint);
		
		float distance = direction.length();
		ofVec3f unitDirection = direction.getNormalized();
		ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
		ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
		
		ofVec3f leftPoint = thisPoint+toTheLeft*5;
		ofVec3f rightPoint = thisPoint+toTheRight*5;
		mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
		mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
	}
	
}
//--------------------------------------------------------------
void ofxNeoPixelCustomObject::setupLedObject(int offsetx, int offsety,vector<ofPoint> positions,int numberOfLeds,int spacing)
{
	// Setup Positioning
	size = numberOfLeds;
	offsetX = 5;
	offsetY = 5;
	_spacing = spacing;
	
	actualX = offsetX+offsetx;
	actualY = offsetY+offsety;

	pos = positions;
}
//--------------------------------------------------------------
void ofxNeoPixelCustomObject::drawGrabRegion(bool hideArea)
{
	if (hideArea == true) {
		// Draw Interaction Area
		ofPushStyle();
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 255);
		ofPopStyle();
		
		// Visualise the Grabber
		ofSetColor(255, 175);
		ofNoFill();
	}
	else
	{
		// Visualise the Grabber
		ofSetColor(0, 175);
		ofNoFill();
	}
	
	ofPushStyle();
	ofSetColor(0, 50);
	mesh.draw();
	ofPopStyle();
	
	for (int i = 0; i < pos.size(); i++)
	{
		ofDrawCircle(pos[i],2);
	}
}
//--------------------------------------------------------------
void ofxNeoPixelCustomObject::ledObject()
{
	ofFill();
	ofSetColor(100,175);
	ofDrawRectangle(0, 0, 10, size*_spacing);
	
	for (int i = 0; i < size; i++)
	{
		ofFill();
		if (!colors.empty()) {
			ofSetColor(colors[i]);
		}
		else {
			ofSetColor(ofColor::red);
		}
		ofDrawCircle(5,0+(i*_spacing),2);
	}
}
//--------------------------------------------------------------
void ofxNeoPixelCustomObject::draw(int x, int y)
{
	// Where to draw the Strip!
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushMatrix();
	ofTranslate(offsetX+5,0);
	ledObject();
	ofPopMatrix();
	ofPopMatrix();
}
