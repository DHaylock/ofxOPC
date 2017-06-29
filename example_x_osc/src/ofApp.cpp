#include "ofApp.h"

const static int numberofleds = 16;

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	effect = 0;
	hide = false;
	
	// Open a osc socket
	transmitSocket = new osc::UdpTransmitSocket( osc::IpEndpointName( "127.0.0.1", 9000) );
	
	// You dont acutally need to connect to the fadecandy but theoretically it could
	opcClient.setup("127.0.0.254", 7890);
	
	// You define the stage size and draw into the stage
	opcClient.setupStage(500, 500);
	
	defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
	
	// Make a ring of led strips
	//-------------------------
	/*
	       *     *     *
			 *   *   *
			   * * *
		   * * * c * * *
			   * * *
			 *	 *   *
		   *	 *     *
	*/
	//-------------------------
	
	ofPoint center = ofPoint(250,250); // Half the size of the Stage
	for (int i = 0; i < 8; i++)
	{
		float angle = ofMap(i, 0, 8, M_PI, M_TWO_PI+M_PI);
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
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle("example_x-osc");
	
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

	// Set to Zero
	int size = 0;
	
	// New Color Combiner
	mergedColor.clear();
	
	// Loop through the NeoPixel Objects and store the number of pixels in each one
	// Then copy the color data across from each object on to the end of the merge vector
	for (int i = 0; i < neoPixelObjects.size(); i++)
	{
		size += neoPixelObjects.at(i)->colorData().size();
	
		// I know this is resource heavy but insert was causing odd issues with the size of the Vector
		for(int e = 0; e < neoPixelObjects.at(i)->colorData().size(); e++)
		{
			mergedColor.push_back(neoPixelObjects.at(i)->colorData()[e]);
		}
	}
	
	//-------------------------------------------
	//*
	//* Reworked from X-IO Technologies
	//*
	//-------------------------------------------
	
	// Create a new Neopixel pointer
	// Resize to size of pixels
	NeoPixel *outPixelArray;
	outPixelArray = new NeoPixel[size];

	// Loop through the Merged Color Vector and return the rgb values and store in the outBoundPixels
	for(int i = 0; i < size; i++)
	{
		outPixelArray[i].r = mergedColor[i].r * 0.25; // Quarter Brightness
		outPixelArray[i].g = mergedColor[i].g * 0.25; // Quarter Brightness
		outPixelArray[i].b = mergedColor[i].b * 0.25; // Quarter Brightness
	}
	
	// I'm still playing with ofxOsc to get Blobs working this works
	osc::OutboundPacketStream p(buffer,BufferSize);
	p << osc::BeginMessage("/outputs/rgb/16") // Check x-IO's documentation for message addressing
	<< osc::Blob(outPixelArray,size*3)
	<< osc::EndMessage;
	
	// Send the Blob Data over
	transmitSocket->Send(p.Data(), p.Size());
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
void ofApp::exit()
{
	
}
