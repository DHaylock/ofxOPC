#include "ofApp.h"
const static int numberofleds = 64;
//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	effect = 0;
	hide = false;
	defaultFX = true;
	// Connect to the fcserver
	opcClient.setup("127.0.0.1", 7890);
	
	// You define the stage size and draw into the stage
	opcClient.setupStage(500, 500);
	
	defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
	
	ofPoint center = ofPoint(250,250);
	
	for (int i = 0; i < 8; i++)
	{
		float angle = ofMap(i, 0, 8, 0, M_TWO_PI);
		int startX = center.x + 25 * sin(angle);
		int startY = center.y + 25 * cos(angle);
		
		ofPoint st = ofPoint(startX,startY);
		ofPoint dir = center - st;
		
		vector <ofPoint> pts;
		for (int e = 0; e < numberofleds; e++)
		{
			ofPoint p(startX-(e*(dir.x/numberofleds)*6),startY-(e*(dir.y/numberofleds)*6));
			pts.push_back(p);
		}
		neoPixelObjects.insert(std::pair<int, ofxNeoPixelObject*>(i,new ofxNeoPixelCustomObject(0,0,pts,numberofleds,5)));
	}
	
	loadShaders();
	shaderNumber = 0;
	
	fbo.allocate(500,500);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();
}
//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle("example_shaders");
	shaderNumber = ofClamp(shaderNumber,0,shaders.size());
	opcClient.update();
	drawStage();
	
	// Now Draw the effects to the stage
	opcClient.beginStage();
	
	if(!defaultFX) fbo.draw(0,0);
	else defaultEffects.draw(effect);
	
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
void ofApp::drawStage()
{
	fbo.begin();
	ofClear(0);
	shaders[shaderNumber].begin();
	shaders[shaderNumber].setUniform1f("u_time", ofGetElapsedTimef() );
	shaders[shaderNumber].setUniform2f("u_resolution", ofVec2f(500, 500));
	ofPushStyle();
	ofColor(255);
	ofFill();
	ofDrawRectangle(0, 0, 500, 500);
	ofPopStyle();
	shaders[shaderNumber].end();
	fbo.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case OF_KEY_RETURN:
			defaultFX = !defaultFX;
			break;
		case OF_KEY_LEFT:
			if(defaultFX) effect--;
			else shaderNumber--;
			break;
		case OF_KEY_RIGHT:
			if(defaultFX) effect++;
			else shaderNumber++;
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

//--------------------------------------------------------------
void ofApp::loadShaders()
{
	ofDirectory dir;
	duplicateCheck = "";
	string folder = "Shaders/";
	dir.listDir(folder);
	
	if ( dir.size() ) shaders.assign(dir.size(), ofxAutoReloadedShader());
	for (int i = 0; i < dir.size(); i++)
	{
		shaders[i].load(folder+dir.getFile(i).getBaseName()+"/"+dir.getFile(i).getBaseName());
	}
}

