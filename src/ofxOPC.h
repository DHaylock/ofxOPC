#include "ofMain.h"
#include "ofxNetwork.h"
#include "NeoPixelRing24px.h"
#include "NeoPixelRing16px.h"
#include "NeoPixelRing12px.h"
#include "NeoPixelStrip.h"
#include "NeoPixelGrid8x8.h"
#include "NeoPixelShield5x8.h"

class ofxOPC  {
    
public:
    
    string _address;
    int _port;
    int _w,_h;
    
    void setup(string address,int port,ofVec2f layout);
    void setup(string address, int port, int layout);
    void draw();
    void update();
    
    
    // Draw into the FBO
    void begin();
    void end();
    
    void writeData();
    void writeData(uint8_t data,int size);
    void close();

    bool isConnected();
    bool tryConnecting();
    
  
    vector <uint8_t> txData;
    vector <ofColor> colors;

    
private:
    void connect();
    void disconnect();
    ofxTCPClient client;
};