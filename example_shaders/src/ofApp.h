#pragma once

#include "ofMain.h"
#include "ofxOPC.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();
		void drawStage();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mouseDragged(int x,int y,int button);
		void mousePressed(int x,int y,int button);
		void mouseReleased(int x,int y,int button);
	
		void exit();

		ofxOPC opcClient;
		Effects defaultEffects;
		map<int, ofxNeoPixelObject*> neoPixelObjects;
		
		int effect;
		bool hide;
		bool defaultFX;
	
		int shaderNumber;
	
		void loadShaders();
		vector <ofxAutoReloadedShader> shaders;
		string duplicateCheck;
		ofFbo fbo;
};
