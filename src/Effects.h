//
//  Effects.h
//
//  Created by David Haylock on 05/03/2016.
//
//

#ifndef Effects_h
#define Effects_h
#include "ofMain.h"

class Ring {
public:
    
    Ring() {}
    ~Ring() {}
    
    void respawn(int stageHeight,float x1,float y1,float x2,float y2) {
        
        _stageHeight = stageHeight;
        // Start at the newer mouse position
        x = x2;
        y = y2;
        
        // Intensity is just the distance between mouse points
        intensity = ofDist(x1, y1, x2, y2);
        intensity = intensity * 5;
        
        // Hue is the angle of mouse movement, scaled from -PI..PI to 0..100
        hue = ofMap(atan2(y2 - y1, x2 - x1), -PI, PI, 0, 255);
        
        // Default size is based on the screen size
        size = _stageHeight * 0.1;
    }
    
    void draw(ofImage ringImage) {
        ofPushStyle();
        // Particles fade each frame
        intensity *= 0.95;
        
        // They grow at a rate based on their intensity
        size += _stageHeight * intensity * 0.01;
        
        // If the particle is still alive, draw it
        if (intensity >= 1) {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofColor c;
            c.setHsb(hue, 200, intensity);
            ofSetColor(c);
            ringImage.draw(x - size/2, y - size/2, size,size);
            ofDisableBlendMode();
        }
        ofPopStyle();
    }
private:
    float x, y, size, intensity, hue,_stageHeight;
};

//class Particle {
//	public:
//	
//	void spawn(ofPoint startPoint,int startSize)
//	{
//		pos = startPoint;
//		size = startSize;
//	}
//	
//	void draw()
//	{
//		size += 2;
//		ofPushStyle();
//		ofNoFill();
//		ofSetLineWidth(4);
//		ofEnableBlendMode(OF_BLENDMODE_ADD);
//		ofSetColor(255,200);
//		ofDrawCircle(pos,size);
//		ofDisableBlendMode();
//		ofPopStyle();
//	}
//	
//	ofPoint pos;
//	float size;
//};

class Effects {
    
    public:
	
		//----------------------------------------------------------
		Effects()
		{
			modes[0] = "Mouse Follower";
			modes[1] = "Spinning Dots";
			modes[2] = "Block Color";
			modes[3] = "Fade To White";
			modes[4] = "Rotating Circles";
			modes[5] = "Gradient Image";
			modes[6] = "Rotating Lines";
			modes[7] = "Noise";
			modes[8] = "Waves";
			modes[9] = "Horizontal Lines";
			modes[10] = "Vertical Lines";
			modes[11] = "Horizontal Wipe";
			modes[12] = "Vertical Wipe";
			modes[13] = "Color Scroll";
			modes[14] = "Strobe";
			modes[15] = "Gradient Lines";
			modes[16] = "Video";
			modes[17] = "Particles";
			modes[18] = "Mouse Box";
		}
	
		//----------------------------------------------------------
		~Effects() {}
	
        //----------------------------------------------------------
        void setup(int stageCenterX,int stageCenterY,int stageWidth,int stageHeight){

            _stageCenterX = stageCenterX;
            _stageCenterY = stageCenterY;
            _stageWidth = stageWidth;
            _stageHeight = stageHeight;
			
            moveCounter = 0;
            
            dot.load("../../../resources/dot.png");
            ringImage.load("../../../resources/ring.png");
            lineImage.load("../../../resources/line.png");
            
            videoPlayer.load("../../../resources/fingers.mov");
            videoPlayer.setLoopState(OF_LOOP_NORMAL);
            videoPlayer.play();
            
            
            if (!dot.isAllocated() || !ringImage.isAllocated() || !lineImage.isAllocated()) {
                dot.load("dot.png");
                ringImage.load("ring.png");
                lineImage.load("line.png");
//                videoPlayer.load("fingers.mov");
            }
            
            
            noiseImage.allocate(stageWidth/4, stageHeight/4, OF_IMAGE_GRAYSCALE);
            colorFadeImage.allocate(stageWidth/4, stageHeight/4, OF_IMAGE_COLOR_ALPHA);
            
            ofSetCircleResolution(200);
            
            for(int x = 0; x < noiseImage.getWidth(); x++) {
                for(int y = 0; y < noiseImage.getHeight(); y++) {
                    ofColor initialColor = ofColor(255*ofNoise(x/100.0,y/100.0,ofGetElapsedTimef()),255);
                    noiseImage.setColor((int)(x+y*noiseImage.getWidth()), initialColor);
                }
            }
            
            pos_y = 0;
            noiseImage.update();
            for(int y = 0; y < colorFadeImage.getHeight(); y++) {
                for(int x = 0; x < colorFadeImage.getWidth(); x++) {
                    ofColor initialColor;
                    int value = 255*(float)x/colorFadeImage.getWidth();
                    initialColor.setHsb(value, 200, 200);
                    colorFadeImage.setColor((int)(x+y*colorFadeImage.getWidth()), initialColor);
                }
            }
            colorFadeImage.update();
        }
	
	
		//----------------------------------------------------------
		map <int,string> getModes()
		{
			return modes;
		}
	
        //----------------------------------------------------------
        void update()
		{
            videoPlayer.update();
        }
        //----------------------------------------------------------
        void draw(int mode){
            update();
            switch (mode) {
                case 0:
                {
                    // Mouse Circle
                    ofPushStyle();
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofDrawCircle(ofGetMouseX(),ofGetMouseY(),10);
                    ofPopStyle();
                }
                    break;
                    // Rotating Dots
                case 1:
                {
                    // Like the processing example draw dot images and rotate
                    int size = (_stageWidth+_stageHeight)/2;
                    ofPushMatrix();
                    ofTranslate(0, 0);
                    ofPushMatrix();
                    ofTranslate(_stageCenterX,_stageCenterY);
                    ofRotateZ(ofGetElapsedTimeMillis()/10);
                    ofPushMatrix();
                    ofTranslate(-size,-size);
                    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
                    ofSetColor(0, 255,20);
                    dot.draw(size/4, size/4, size,size);
                    ofSetColor(255, 0,20);
                    dot.draw((size/4*3), size/4, size,size);
                    ofSetColor(0, 0,255);
                    dot.draw(size/4, (size/4*3), size,size);
                    ofSetColor(255, 0,255);
                    dot.draw((size/4*3),(size/4*3), size,size);
                    ofDisableBlendMode();
                    ofPopMatrix();
                    ofPopMatrix();
                    ofPopMatrix();
                }
                    break;
                    // Block Circle
                case 2:
                {
                    // Changes the color of a Circle
                    ofPushStyle();
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofDrawRectangle(0,0,_stageWidth,_stageHeight);
                    ofPopStyle();
                }
                    break;
                    // Fade to White
                case 3:
                {
                    // Fade to full brightness then to zero
                    ofPushStyle();
                    ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
                    ofDrawRectangle(0,0,_stageWidth,_stageHeight);
                    ofPopStyle();
                }
                    break;
                    // Rotating Circle
                case 4:
                {
                    ofEnableBlendMode(OF_BLENDMODE_ADD);
                    float rotationAmount = ofGetElapsedTimeMillis()/10;
					float circ1Size = 40 + 40 * abs(sin(ofGetElapsedTimef()));
					float circ2Size = 40 + 40 * abs(cos(ofGetElapsedTimef()));
                    ofSetColor(255, 0, 0);
                    ofPushMatrix();
                    ofTranslate(_stageCenterX, _stageCenterY);
                    ofRotateZ(rotationAmount);
                    ofPushMatrix();
                    ofTranslate(-_stageCenterX, -_stageCenterY);
                    ofDrawCircle(_stageCenterX, _stageCenterY-circ1Size, circ1Size);
                    ofPopMatrix();
                    ofPopMatrix();
                    ofSetColor(0, 0, 255);
                    ofPushMatrix();
                    ofTranslate(_stageCenterX, _stageCenterY);
                    ofRotateZ(-rotationAmount);
                    ofPushMatrix();
                    ofTranslate(-_stageCenterX, -_stageCenterY);
                    ofDrawCircle(_stageCenterX, _stageCenterY+circ2Size, circ2Size);
                    ofPopMatrix();
                    ofPopMatrix();
                    ofDisableBlendMode();
                }
                    break;
                    // Dot Image
                case 5:
                {
                    int w = 300;
                    int h = 300;
                    ofPushStyle();
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    dot.draw(ofGetMouseX()-(w*0.5), ofGetMouseY()-(h*0.5), w,h);
                    ofPopStyle();
                }
                    break;
                    // Rotating Line
                case 6:
                {
                    float rotationAmount = ofGetElapsedTimeMillis()/5;
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofPushMatrix();
                    ofTranslate(_stageCenterX, _stageCenterY);
                    ofRotateZ(rotationAmount);
                    ofPushMatrix();
                    ofTranslate(-_stageCenterX, -_stageCenterY);
                    int w = (int)(28 + 128 * sin(ofGetElapsedTimef()));
                    ofDrawRectangle(_stageCenterX-(w/2), _stageCenterY-_stageHeight, w, _stageHeight*2);
                    ofPopMatrix();
                    ofPopMatrix();
                }
                    break;
                    // Noise Image
                case 7:
                {
                    for(int x = 0; x < noiseImage.getWidth(); x++) {
                        for(int y = 0; y < noiseImage.getHeight(); y++) {
                            ofColor initialColor = ofColor(255*ofNoise(x/100.0,y/100.0,ofGetElapsedTimef()),255);
                            noiseImage.setColor((int)(x+y*noiseImage.getWidth()), initialColor);
                        }
                    }
                    noiseImage.update();
                    ofPushMatrix();
                    ofScale(4, 4);
                    ofSetColor(255, 255, 255);
                    noiseImage.draw(0, 0);
                    ofPopMatrix();
                }
                    break;
                    // Wavefront
                case 8:
                {
                    float prevX = smoothX;
                    float prevY = smoothY;
                    smoothX += (ofGetMouseX() - smoothX) * 0.1;
                    smoothY += (ofGetMouseY() - smoothY) * 0.1;
                    
                    // At every frame, randomly respawn one ring
                    rings[int(ofRandom(100))].respawn(_stageHeight,prevX, prevY, smoothX, smoothY);
                    
                    // Give each ring a chance to redraw and update
                    for (int i = 0; i < 100; i++) {
                        rings[i].draw(ringImage);
                    }
                }
                    break;
                    // Color changing moving lines (horizontal)
                case 9:
                {
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofPushMatrix();
                    int x = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()));
                    int x1 = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()*2));
                    int x2 = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()*4));
                    int w = (int)(35 + 30 * sin(ofGetElapsedTimef()*0.6));
                    ofDrawRectangle(x, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    ofDrawRectangle(x1, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    ofDrawRectangle(x2, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    ofPopMatrix();
                }
                    break;
                    // Color changing moving lines (vertical)
                case 10:
                {
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofPushMatrix();
                    int y = (int)(_stageHeight/2 + _stageHeight/2 * sin(ofGetElapsedTimef()));
                    int y1 = (int)(_stageHeight/2 + _stageHeight/2 * sin(ofGetElapsedTimef()*2));
                    int y2 = (int)(_stageHeight/2 + _stageHeight/2 * sin(ofGetElapsedTimef()*4));
                    int h = (int)(35 + 30 * sin(ofGetElapsedTimef()*0.6));
                    ofDrawRectangle(_stageCenterX-(_stageWidth/2), y, _stageWidth, h);
                    ofDrawRectangle(_stageCenterX-(_stageWidth/2), y1, _stageWidth, h);
                    ofDrawRectangle(_stageCenterX-(_stageWidth/2), y2, _stageWidth, h);
                    ofPopMatrix();
                }
                    break;
                    // Horizontal Filling Box
                case 11:
                {
                    float hue = fmodf(ofGetElapsedTimef()*2,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofPushMatrix();
                    int x = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()));
                    int w = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()*0.1));
                    ofDrawRectangle(0, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    ofPopMatrix();
                }
                    break;
                    // Vertical Filling Box
                case 12:
                {
                    float hue = fmodf(ofGetElapsedTimef()*2,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofPushMatrix();
                    int h = (int)(_stageHeight/2 + _stageHeight/2 * sin(ofGetElapsedTimef()*0.1));
                    ofDrawRectangle(0, 0, _stageWidth, h);
                    ofPopMatrix();
                }
                    break;
                    // Color Scroll
                case 13:
                {
                    ofPushMatrix();
                    ofPushStyle();
                    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
                    int linesInterval = _stageHeight/2;
                    int step = 255/linesInterval;
                    int indents = _stageHeight/linesInterval;
                    pos_y = int(ofGetElapsedTimef()*32);
                    for (int y = 0; y < _stageHeight; y++) {
                        
                        ofColor c = ofColor::fromHsb((pos_y+y*step)%255, 255, 255);
                        ofSetColor(c);
                        ofDrawRectangle(0, y, _stageWidth, y);
                    }
                    ofDisableBlendMode();
                    ofPopMatrix();
                    ofPopStyle();
                }
                    break;
                    // Strobe
                case 14:
                {
                    ofPushMatrix();
                    ofPushStyle();
                    
                    int probability = 100-10;
                    if (ofRandom(0,100) > probability) {
                        ofSetColor(ofColor::white);
                    }
                    else {
                        ofSetColor(ofColor::black);
                    }
                    ofDrawRectangle(0, 0, _stageWidth, _stageHeight);
                    ofPopStyle();
                    ofPopMatrix();
                }
                    break;
                case 15:
                {
                    float hue = fmodf(ofGetElapsedTimef()*10,255);
                    ofColor c = ofColor::fromHsb(hue, 255, 255);
                    ofSetColor(c);
                    ofPushMatrix();
                    int x = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()));
                    int x1 = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()*2));
                    int x2 = (int)(_stageWidth/2 + _stageWidth/2 * sin(ofGetElapsedTimef()*4));
                    int w = (int)(60 + 150 * sin(ofGetElapsedTimef()*0.5));
                    ofPushStyle();
                    ofEnableBlendMode(OF_BLENDMODE_ADD);
                    lineImage.draw(x, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    lineImage.draw(x1, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    lineImage.draw(x2, _stageCenterY-_stageHeight, w, _stageHeight*2);
                    ofDisableBlendMode();
                    ofPopStyle();
                    ofPopMatrix();
                }
                    break;
                case 16:
                {
                    ofPushStyle();
                    ofSetColor(ofColor::white);
                    videoPlayer.draw(0,0,_stageWidth,_stageHeight);
                    ofPopStyle();
                }
                    break;
					
				case 17:
				{
//					int r = ofRandom(5,60);
//					if(ofGetFrameNum() % r == 0) pts[int(ofRandom(100))].spawn(ofPoint(_stageWidth/2,_stageHeight/2),1);
//					
//					ofPushStyle();
//					for(int i = 0; i < 100; i++)
//					{
//						pts[i].draw();
//					}
//					ofPopStyle();
				}
					break;
				case 18:
				{
					ofPushStyle();
					ofSetColor(255);
					ofDrawRectangle(0, 0, _stageWidth, ofGetMouseY());
					ofPopStyle();
					
				}
					break;
					
                default:
                    break;
            }
			
        }
	
    private:
        int _stageWidth;
        int _stageHeight;
        int _stageCenterX;
        int _stageCenterY;
    
        ofImage dot;
        Ring rings[100];
//		Particle pts[100];
        float smoothX, smoothY;
        
        ofImage noiseImage;
        ofImage colorFadeImage;
        ofImage ringImage;
        ofImage lineImage;
        deque<ofColor> gloriousColor;
        ofVideoPlayer videoPlayer;
	
		map<int,string> modes;
	
        int pos_y;
        int moveCounter;
    protected:
    
    
};
#endif /* Effects_h */
