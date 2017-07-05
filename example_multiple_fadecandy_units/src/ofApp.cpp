#include "ofApp.h"
const static int numberofleds = 64;
const static int fadecandys = 2;
//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	effect = 0;
	hide = false;
	
	// Connect to the fcserver
	opcClient.setup("127.0.0.1", 7890, fadecandys);
	
	// You define the stage size and draw into the stage
	opcClient.setupStage(500, 500);
	
	defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
	
	ofPoint center1 = ofPoint(250,125);
	ofPoint center2 = ofPoint(250,375);
	
	for (int i = 0; i < 8; i++)
	{
		float angle = ofMap(i, 0, 8, 0, M_TWO_PI);
		int startX = center1.x + 25 * sin(angle);
		int startY = center1.y + 25 * cos(angle);
		
		ofPoint st = ofPoint(startX,startY);
		ofPoint dir = center1 - st;
		
		vector <ofPoint> pts;
		for (int e = 0; e < numberofleds; e++)
		{
			ofPoint p(startX-(e*(dir.x/numberofleds)*3),startY-(e*(dir.y/numberofleds)*3));
			pts.push_back(p);
		}
		neoPixelObjects.insert(std::pair<int, ofxNeoPixelObject*>(i,new ofxNeoPixelCustomObject(0,0,pts,numberofleds,5)));
	}
	
	
	for (int i = 0; i < 8; i++)
	{
		float angle = ofMap(i, 0, 8, 0, M_TWO_PI);
		int startX = center2.x + 25 * sin(angle);
		int startY = center2.y + 25 * cos(angle);
		
		ofPoint st = ofPoint(startX,startY);
		ofPoint dir = center2 - st;
		
		vector <ofPoint> pts;
		for (int e = 0; e < numberofleds; e++)
		{
			ofPoint p(startX-(e*(dir.x/numberofleds)*3),startY-(e*(dir.y/numberofleds)*3));
			pts.push_back(p);
		}
		neoPixelObjects.insert(std::pair<int, ofxNeoPixelObject*>(i+8,new ofxNeoPixelCustomObject(0,0,pts,numberofleds,5)));
	}
}
//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle("example_multiple_fadecandy_units");
	opcClient.update();
	
	// Now Draw the effects to the stage
	opcClient.beginStage();
	
	defaultEffects.draw(effect);
	
	opcClient.endStage();
//	
//	mergedColor.clear();
//	
	// Get Objects
	for (int i = 0; i < neoPixelObjects.size(); i++)
	{
		opcClient.getStagePixels(neoPixelObjects.at(i)->getPixelCoordinates(), neoPixelObjects.at(i)->colors);
	}
//	
//	// If the client is not connected do not try and send information
//	if (!opcClient.isConnected())
//	{
//		// Will continue to try and reconnect to the Pixel Server
//		opcClient.tryConnecting();
//	}
//	else
//	{
//		// Loop through the NeoPixel Objects and store the number of pixels in each one
//		// Then copy the color data across from each object on to the end of the merge vector
//		for (int i = 0; i < neoPixelObjects.size(); i++)
//		{
//			// I know this is resource heavy but insert was causing odd issues with the size of the Vector
//			for(int e = 0; e < neoPixelObjects.at(i)->colorData().size(); e++)
//			{
//				mergedColor.push_back(neoPixelObjects.at(i)->colorData()[e]);
//			}
//		}
//		
//		opcClient.autoWriteData(mergedColor);
//	}
	
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
			opcClient.writeChannel(i+1, neoPixelObjects[i]->colorData());
		}
	}
}
//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);
	ofPushStyle();
	opcClient.drawStage(hide);
	
	for (int i = 0; i < neoPixelObjects.size(); i++)
	{
		neoPixelObjects[i]->drawGrabRegion(hide);
	}
	
	for(int i = 0; i < neoPixelObjects.size(); i++)
	{
		neoPixelObjects.at(i)->draw(opcClient.getStageWidth()+(i*25), 10);
	}
	ofPopStyle();
	// Report Messages
	stringstream ss;
	ss << "Press Left and Right to Change Effect Mode" << endl;
	ss << "FPS: " << ofToString((int)(ofGetFrameRate())) << endl;
	ofDrawBitmapStringHighlight(ss.str(), 5,ofGetHeight()-30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case OF_KEY_LEFT:
			effect--;
			break;
		case OF_KEY_RIGHT:
			effect++;
			break;
		case ' ':
			hide = !hide;
			break;
			
		default:
			break;
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
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
void ofApp::exit()
{
	// Close Connection
	opcClient.close();
}
