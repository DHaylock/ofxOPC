/*
 *  ofxFlocking.cpp
 *  flock
 *
 *  Created by Jeffrey Crouse on 3/30/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *  Modified by Takara Hokao
 */

#include "ofxFlocking.h"
//--------------------------------------------------------------
void ofxFlocking::update()
{
    int i;
	for(i = 0; i < boids.size(); i++) {
		boids[i].update(boids);
	}
}
//--------------------------------------------------------------
void ofxFlocking::draw(int drawMode)
{
    int i;
	for(i = 0; i < boids.size(); i++) {
		boids[i].draw(drawMode);
	}
}
//-------------------------------------------------------------
void ofxFlocking::FlockSeekTarget(ofVec2f pos)
{
    for (int i = 0; i < boids.size(); i++) {
        boids[i].seek(pos);
        boids[i].update(boids);
    }
    
}

//-------------------------------------------------------------
void ofxFlocking::FlockAvoidTarget(ofVec2f pos)
{
    for (int i = 0; i < boids.size(); i++) {
        boids[i].avoid(pos);
        boids[i].update(boids);
    }
    
}
//-------------------------------------------------------------
void ofxFlocking::FlockSeekTarget(vector <ofVec2f> pos)
{
    if (pos.size() > 0) {
        
        for (int p = 0; p < pos.size(); p++) {
            for (int i = 0; i < boids.size(); i++) {
                boids[i].seek(pos[p]);
                boids[i].update(boids);
            }
        }
    }
}

//-------------------------------------------------------------
void ofxFlocking::FlockAvoidTarget(vector <ofVec2f> pos)
{
    if (pos.size() > 0) {
        
        for (int p = 0; p < pos.size(); p++) {
            for (int i = 0; i < boids.size(); i++) {
                boids[i].avoid(pos[p]);
                boids[i].update(boids);
            }
        }
    }
}
//--------------------------------------------------------------
void ofxFlocking::updateVars(float vDs, float vAd, float vCd)
{
    
    for (int i =0 ; i < boids.size(); i++) {
        boids[i].setVariables(vDs, vAd, vCd);
        boids[i].update(boids);
    }
}
//--------------------------------------------------------------
void ofxFlocking::addBoid()
{
	boids.push_back(Boid());
}
//--------------------------------------------------------------
void ofxFlocking::addBoid(int x, int y)
{
	boids.push_back(Boid(x, y));
}
//--------------------------------------------------------------
void ofxFlocking::removeBoid(int x, int y, int radius)
{
    int i;
    for (i=0; i<boids.size(); i++) {
        if(boids[i].isHit(x, y, radius)) {
            boids.erase(boids.begin()+i);
        }
    }
}
//--------------------------------------------------------------
void ofxFlocking::removeBoid(int numTodelete) {
    
    for (int i=0; i< numTodelete; i++) {
        boids.erase(boids.begin()+i);
    }
}
//--------------------------------------------------------------
void ofxFlocking::updateFlockAccelaration(ofVec2f accel)
{
    for (int i=0; i< boids.size(); i++) {
        boids[i].acc = accel;
        boids[i].update(boids);
    }
}
//--------------------------------------------------------------
void ofxFlocking::updateFlockMaxForce(float mxForce)
{
    for (int i=0; i< boids.size(); i++) {
        boids[i].maxforce = mxForce;
        boids[i].update(boids);
    }
}
//--------------------------------------------------------------
void ofxFlocking::updateFlockMaxSpeed(float mxSpeed)
{
    for (int i=0; i< boids.size(); i++) {
        boids[i].maxspeed = mxSpeed;
        boids[i].update(boids);
    }
}
//--------------------------------------------------------------
int ofxFlocking::flockSize()
{
    return boids.size();
}