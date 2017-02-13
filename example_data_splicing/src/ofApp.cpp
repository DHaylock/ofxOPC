#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	effect = 0;
	
	// Connect to the fcserver
	opcClient.setup("127.0.0.1", 7890);
	
	// You define the stage size and draw into the stage
	opcClient.setupStage(500, 500);
	
	defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
	
	int spacing = 15;
	
	grid12x15.setupLedGrid(12, 15, opcClient.getStageCenterX()-((12*spacing)/2), opcClient.getStageCenterY()-((15*spacing)/2), spacing);
}
//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle("example_data_splicing");
	
	opcClient.update();
	
	// Now Draw the effects to the stage
	opcClient.beginStage();
	
	// Draw what you want rendered here
	// For now here are some default effects
	defaultEffects.draw(effect);
	
	opcClient.endStage();
	
	// New Get Method
	opcClient.getStagePixels(grid12x15.getPixelCoordinates(), grid12x15.colors);
	
	// Clear the Containers
	channelOne.clear();
	channelTwo.clear();
	channelThree.clear();
	
	// Loop through the grid colors and put 60 colors into seperate containers
	for (int i = 0; i < grid12x15.colorData().size(); i++)
	{
		if (i < 59)
		{
			channelOne.push_back(grid12x15.colorData()[i]);
		}
		else if (i > 59 && i < (59+60))
		{
			channelTwo.push_back(grid12x15.colorData()[i]);
		}
		else if (i > (59+60) && i < (59+(60*2)))
		{
			channelThree.push_back(grid12x15.colorData()[i]);
		}
	}
	
	// If the client is not connected do not try and send information
	if (!opcClient.isConnected())
	{
		// Will continue to try and reconnect to the Pixel Server
		opcClient.tryConnecting();
	}
	else
	{
		opcClient.writeChannelOne(channelOne);
		opcClient.writeChannelTwo(channelTwo);
		opcClient.writeChannelThree(channelThree);
	}
}
//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);
	opcClient.drawStage(hide);
	grid12x15.drawGrabRegion(hide);
	grid12x15.draw(opcClient.getStageWidth()+25, 50);
	
	// Report Messages
	stringstream ss;
	ss << "Press Left and Right to Change Effect Mode" << endl;
	ss << "FPS: " << ofToString((int)(ofGetFrameRate())) << endl;
	ofDrawBitmapStringHighlight(ss.str(), 5,ofGetHeight()-30);
	
	
	for (int i = 0; i < channelOne.size(); i++)
	{
		ofSetColor(channelOne[i]);
		ofDrawCircle(25+(i*10), opcClient.getStageHeight()+50, 4);
	}
	
	for (int i = 0; i < channelTwo.size(); i++)
	{
		ofSetColor(channelTwo[i]);
		ofDrawCircle(25+(i*10), opcClient.getStageHeight()+60, 4);
	}
	
	for (int i = 0; i < channelThree.size(); i++)
	{
		ofSetColor(channelThree[i]);
		ofDrawCircle(25+(i*10), opcClient.getStageHeight()+70, 4);
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
void ofApp::exit()
{
	// Close Connection
	opcClient.close();
}
