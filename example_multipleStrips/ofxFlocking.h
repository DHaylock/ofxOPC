/*
 *  Flock.h
 *
 *  Created by Jeffrey Crouse on 3/30/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *  Modified by Takara Hokao
 */

#pragma once

#include "ofMain.h"
#include "Boid.h"

enum drawModes
{
	OFX_FLOCKING_DRAWMODE_DEFAULT = 0,
    OFX_FLOCKING_DRAWMODE_SQUARES = 1,
    OFX_FLOCKING_DRAWMODE_CIRCLES = 2,
    OFX_FLOCKING_DRAWMODE_IMAGE = 3,
    OFX_FLOCKING_DRAWMODE_CUSTOM = 4
};

class ofxFlocking {
public:
	void update();
	void draw(int drawMode = OFX_FLOCKING_DRAWMODE_DEFAULT);
	void addBoid();
	void addBoid(int x, int y);
    void removeBoid(int x, int y, int radius);
    void removeBoid(int numTodelete);
    
    void FlockSeekTarget(ofVec2f pos);
    void FlockAvoidTarget(ofVec2f pos);
    void FlockAvoidTarget(vector<ofVec2f> pos);
    void FlockSeekTarget(vector<ofVec2f> pos);
    void updateVars(float vDs, float vAd,float vCd);
    
    void updateFlockAccelaration(ofVec2f accel);
    void updateFlockMaxSpeed(float mxSpeed);
    void updateFlockMaxForce(float mxForce);
    
    int flockSize();
    
    	
	vector<Boid> boids;
};
