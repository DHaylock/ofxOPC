#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    hide = false; 
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    
    // You define the stage size and draw into the stage
    opcClient.setupStage(250, 250);
    
    defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
    
    // Setup the Grabbing positions
    for (int y = 0; y < 5; y++)
	{
        for (int x = 0; x < 5; x++)
		{
            ringOrigins.push_back(ofVec2f(25+(x*50),25+(y*50)));
        }
    }
    
    // Setup the rings
    for (int i = 0; i < ringOrigins.size(); i++)
	{
        neoPixels.insert(std::pair<int, ofxNeoPixelObject*>(i,new ofxNeoPixelRing(ringOrigins[i].x,ringOrigins[i].y, 12, 20)));
    }
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("example_chaining");
    opcClient.update();
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    
    // Draw what you want rendered here
    // For now here are some default effects
    defaultEffects.draw(effect);
    
    opcClient.endStage();
    
    // New Get Method
    for (int i = 0; i < neoPixels.size(); i++)
	{
        opcClient.getStagePixels(neoPixels.at(i)->getPixelCoordinates(), neoPixels.at(i)->colors);
    }
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
	{
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else
	{
		for (int i = 0; i < 5; i++)
		{
			vector <vector<ofColor> > desiredPixels;
			for (int unit = 0+(i*4); unit < 4+(i*4); unit++)
			{
				desiredPixels.push_back(neoPixels[unit]->colorData());
			}
			opcClient.writeChannel(i+1,opcClient.getChainedPixelData(desiredPixels));
		}
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    opcClient.drawStage(hide);
    
    // Show the grabber area
    for (int i = 0; i < neoPixels.size(); i++)
	{
        neoPixels.at(i)->drawGrabRegion(hide);
        neoPixels.at(i)->draw(opcClient.getStageWidth()+ringOrigins[i].x+25,ringOrigins[i].y);
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
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
}
