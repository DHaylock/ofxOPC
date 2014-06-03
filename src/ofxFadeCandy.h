//
//  ofxFadeCandy.h
//
//  Created by David Haylock on 28/05/2014.
//


// NOT USED YET FOR FUTURE DEVELOPMENT
#include <iostream>
#include "ofMain.h"
#include "ofxNetwork.h"

class ofxFadeCandy {
    
    public:
    
        void setup();
        void setConfigData();
        void setStatusLED(bool value);
    
        void setDithering(bool enabled = true);
        void setInterpolation(bool enabled = true);
    
        void update();
        void transferAllData();
    
        void getDataChannelZero();
        void getDataChannelOne();
        void getDataChannelTwo();
        void getDataChannelThree();
        void getDataChannelFour();
        void getDataChannelFive();
        void getDataChannelSix();
        void getDataChannelSeven();
        
        bool isUnitConnected();
    
    private:
        ofxTCPClient client;
    
    
};
