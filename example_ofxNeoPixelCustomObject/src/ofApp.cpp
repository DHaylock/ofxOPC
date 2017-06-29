#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	effect = 0;
	hide = false;
	
	// Connect
	opcClient.setup("127.0.0.1", 7890);
	
	// You define the stage size and draw into the stage
	opcClient.setupStage(500, 500);
	
	defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
	
	ofPoint center = ofPoint(250,250); // Half the size of the Stage

	// Lets make a spiral
	vector <ofPoint> pts;
	int pixels = 64*2;
	for(int i = 0; i < pixels; i++)
	{
		float angle = ofMap(i, 0, pixels, 0, M_PI*8);
		float x = center.x + (pixels - i) * sin(angle);
		float y = center.y + (pixels - i) * cos(angle);
		pts.push_back(ofPoint(x, y));
	}
	
	neoPixelObjects.insert(std::pair<int, ofxNeoPixelObject*>(0,new ofxNeoPixelCustomObject(0,0,pts,pixels,5)));
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle("example_custom_neopixel_object");
	
	opcClient.update();
	
	// Now Draw the effects to the stage
	opcClient.beginStage();
	defaultEffects.draw(effect);
	opcClient.endStage();
	
	// Get Objects
	for (int i = 0; i < neoPixelObjects.size(); i++)
	{
		opcClient.getStagePixels(neoPixelObjects.at(i)->getPixelCoordinates(), neoPixelObjects.at(i)->colors);
	}
	
	// If the client is not connected do not try and send information
	if (!opcClient.isConnected())
	{
		// Will continue to try and reconnect to the Pixel Server
		opcClient.tryConnecting();
	}
	else
	{
		// Write out the first set of data
		for (int i = 0; i < neoPixelObjects.size(); i++)
		{
			opcClient.writeChannel(i, neoPixelObjects[i]->colorData());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);
	opcClient.drawStage(hide);
	
	for (int i = 0; i < neoPixelObjects.size(); i++)
	{
		neoPixelObjects[i]->drawGrabRegion(hide);
	}
	
	for(int i = 0; i < neoPixelObjects.size(); i++)
	{
		neoPixelObjects.at(i)->draw(opcClient.getStageWidth()+(i*25), 10);
	}
	
	// Report Messages
	stringstream ss;
	ss << "Press Left and Right to Change Effect Mode" << endl;
	ss << "FPS: " << ofToString((int)(ofGetFrameRate())) << endl;
	ofDrawBitmapStringHighlight(ss.str(), 5,ofGetHeight()-30);
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
void ofApp::exit()
{
	
}
